#include "polyf.h"
#include "3d.h"
#include "polytex.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <stdbool.h>
//-------------------------------------------------------------------------------------------------

void twpoly(tPoint *vertices, int16 nColor)
{
  int16 nEdge1Dx; // ax
  int16 nEdge2Dx; // di
  int16 nEdge2Dy; // si
  int16 nEdge3Dy; // bx
  double dIntersectionX2; // st6
  double dIntersectionY2; // st7
  int iNumVerts; // edx
  tPoint *vertices2; // eax
  int16 nColor2; // bx
  double dIntersectionX; // st6
  double dIntersectionY; // st7
  int iCrossProductResult2; // ebp
  double dIntersectionY3; // st7
  int16 nColor3; // bp
  double dIntersectionY4; // st7
  tPoint pTempPoint2; // [esp+0h] [ebp-68h]
  tPoint pTempPoint5; // [esp+8h] [ebp-60h]
  tPoint pTempPoint3; // [esp+8h] [ebp-60h]
  tPoint pTempPoint4; // [esp+8h] [ebp-60h]
  tPoint pTempPoint; // [esp+10h] [ebp-58h]
  int iCrossProductResult2_2; // [esp+20h] [ebp-48h]
  float fCrossProduct2; // [esp+24h] [ebp-44h]
  float fCrossProduct1; // [esp+28h] [ebp-40h]
  float fIntersectionParam2; // [esp+2Ch] [ebp-3Ch]
  float fIntersectionParam; // [esp+30h] [ebp-38h]
  int iCrossProductResult1; // [esp+34h] [ebp-34h]
  int16 nEdge1Dy; // [esp+38h] [ebp-30h]
  int16 nSumEdge23Dy; // [esp+3Ch] [ebp-2Ch]
  int16 nSumEdge23Dx; // [esp+40h] [ebp-28h]
  int16 SumEdge23Dy2; // [esp+44h] [ebp-24h]
  int16 nSumEdge23Dx2; // [esp+48h] [ebp-20h]
  int16 nEdge3Dx; // [esp+4Ch] [ebp-1Ch]

  nEdge1Dx = (int16)(vertices[1].x) - (int16)(vertices->x);
  nEdge2Dx = (int16)(vertices[2].x) - (int16)(vertices->x);
  nEdge3Dx = (int16)(vertices[3].x) - (int16)(vertices[2].x);
  nSumEdge23Dx = nEdge2Dx + nEdge3Dx;
  nSumEdge23Dx2 = nEdge1Dx - nEdge2Dx;
  nEdge1Dy = (int16)(vertices[1].y) - (int16)(vertices->y);
  nEdge2Dy = (int16)(vertices[2].y) - (int16)(vertices->y);
  nEdge3Dy = (int16)(vertices[3].y) - (int16)(vertices[2].y);
  nSumEdge23Dy = nEdge2Dy + nEdge3Dy;
  SumEdge23Dy2 = nEdge1Dy - nEdge2Dy;
  iCrossProductResult1 = 0;
  iCrossProductResult2_2 = 0;
  fCrossProduct1 = (float)(nEdge3Dy * nEdge1Dx - nEdge1Dy * nEdge3Dx);

  // Check if quadrilateral is concave by testing edge intersections
  if (fabsf(fCrossProduct1) > FLT_EPSILON)
  {
    iCrossProductResult1 = nEdge1Dy * nEdge2Dx - nEdge2Dy * nEdge1Dx;
    fIntersectionParam = (float)((double)iCrossProductResult1 / (double)fCrossProduct1);

    // Valid intersection point found 0 < t < 1
    if (fIntersectionParam > 0.0 && fIntersectionParam < 1.0) {
      pTempPoint = *vertices;
      if (iCrossProductResult1 <= 0) {
        // Case 1: Split into triangles P01-P1-P* and P0-P*-P3
        *vertices = vertices[2];                // move P2 to P0 position

        // Calculate intersection point P*
        dIntersectionX = (double)nEdge3Dx * fIntersectionParam + (double)vertices[2].x;
        dIntersectionX = round(dIntersectionX); //_CHP()
        vertices[2].x = (int)dIntersectionX;
        dIntersectionY = fIntersectionParam * (double)nEdge3Dy + (double)vertices[2].y;
        dIntersectionY = round(dIntersectionY); //_CHP()
        vertices[2].y = (int)dIntersectionY;

        // Render first triangle (P2, P3, P*)
        poly(vertices, 3, nColor);

        // Prepare second triangle (P0, P*, P3)
        *vertices = vertices[3];                // Original P3
        vertices[1] = pTempPoint;               // Original P0
        poly(vertices, 3, nColor);
        return;
      }
      // Case 2: Split into triangles P0-P1-P* and P1-P2-P*
      *vertices = vertices[1];                  // Move P1 to P0 position
      vertices[1] = vertices[2];                // Move P2 to P1 position

      // Calculate intersection point P*
      dIntersectionX2 = (double)nEdge3Dx * fIntersectionParam + (double)vertices[2].x;
      dIntersectionX2 = round(dIntersectionX2); //_CHP();
      vertices[2].x = (int)dIntersectionX2;
      dIntersectionY2 = fIntersectionParam * (double)nEdge3Dy + (double)vertices[2].y;
      dIntersectionY2 = round(dIntersectionY2); //_CHP();
      vertices[2].y = (int)dIntersectionY2;

      // Render first triangle (P1, P2, P*)
      poly(vertices, 3, nColor);

      // Prepare second triangle (P0, P*, P3)
      *vertices = vertices[3];                  // Original P3
      iNumVerts = 3;
      vertices2 = vertices;
      nColor2 = nColor;
      vertices[1] = pTempPoint;                 // Original P0
      goto LABEL_18;
    }
  }

  // Secondary concave test using different edge combination
  fCrossProduct2 = (float)(SumEdge23Dy2 * nSumEdge23Dx - nSumEdge23Dy * nSumEdge23Dx2);
  if (fabsf(fCrossProduct2) > FLT_EPSILON
    || (iCrossProductResult2 = nEdge2Dx * nSumEdge23Dy - nEdge2Dy * nSumEdge23Dx,
        iCrossProductResult2_2 = iCrossProductResult2,
        fIntersectionParam2 = (float)((double)iCrossProductResult2 / (double)fCrossProduct2),
        fIntersectionParam2 <= 0.0)             // Valid intersection point found (0 < t < 1)
    || fIntersectionParam2 >= 1.0) {

    // Convex quadrilateral handling
    if (iCrossProductResult1 < 0 || iCrossProductResult2_2 > 0) {
      // Swap P1 and P3 to fix winding order
      pTempPoint2 = vertices[1];
      vertices[1] = vertices[3];
      vertices[3] = pTempPoint2;
    }
    nColor2 = nColor;
    vertices2 = vertices;
    iNumVerts = 4;
  LABEL_18:
      // Render as convex quadrilateral
    poly(vertices2, iNumVerts, nColor2);
    return;
  }
  if (iCrossProductResult2 <= 0) {
    // Case 3: Swap vertices and split
    pTempPoint3 = *vertices;
    *vertices = vertices[1];                    // Swap P0 and P1
    vertices[1] = pTempPoint3;
    pTempPoint4 = vertices[2];
    //_CHP();
    // Calculate intersection point P*
    vertices[2].x = (int)((double)nSumEdge23Dx2 * fIntersectionParam2 + (double)pTempPoint4.x);
    dIntersectionY4 = fIntersectionParam2 * (double)SumEdge23Dy2 + (double)vertices[2].y;
    dIntersectionY4 = round(dIntersectionY4); //_CHP();
    vertices[2].y = (int)dIntersectionY4;
    nColor3 = nColor;

    // Render first triangle
    poly(vertices, 3, nColor);

    // Prepare second triangle
    vertices[1] = vertices[3];
    *vertices = pTempPoint4;
  } else {
    // Case 4: Standard split at intersection
    pTempPoint5 = vertices[2];
    //_CHP();
    // Calculate intersection point P*
    vertices[2].x = (int)((double)nSumEdge23Dx2 * fIntersectionParam2 + (double)pTempPoint5.x);
    dIntersectionY3 = fIntersectionParam2 * (double)SumEdge23Dy2 + (double)vertices[2].y;
    dIntersectionY3 = round(dIntersectionY3); //_CHP();
    vertices[2].y = (int)dIntersectionY3;
    nColor3 = nColor;

    // Render first triangle
    poly(vertices, 3, nColor);

    // Prepare second triangle
    *vertices = vertices[3];                    // Original P3
    vertices[1] = pTempPoint5;                  // Original P2
  }
  poly(vertices, 3, nColor3);
}

//-------------------------------------------------------------------------------------------------

int16 POLYFLAT(int a1, int *a2)
{
  return 0; /*
  _DWORD *v3; // eax
  int v4; // ebx
  int v5; // edx
  int v6; // ecx
  int v7; // ebp
  int v8; // edx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  int v15; // [esp+0h] [ebp-18h]

  v3 = a2;
  v4 = *a2;
  if ((((unsigned int)&loc_1FFFD + 3) & *a2) == 0) {
    if ((v4 & 0x2000) != 0) {
      v5 = a2[2];
      v6 = v3[3];
      v15 = v5 - v3[4];
      v7 = v6 - v3[5];
      if (v3[4] == v3[6] && v3[5] == v3[7]) {
        v8 = v5 - v3[8];
        v9 = v6 - v3[9];
      } else {
        v8 = v5 - v3[6];
        v9 = v6 - v3[7];
      }
      if (v15 * v9 > v7 * v8) {
        v10 = v3[2];
        v3[2] = v3[8];
        v3[8] = v10;
        v11 = v3[3];
        v3[3] = v3[9];
        v3[9] = v11;
        v12 = v3[4];
        v3[4] = v3[6];
        v3[6] = v12;
        v13 = v3[5];
        v3[5] = v3[7];
        v3[7] = v13;
      }
    }
    scrptr = a1;
    ++num_pols;
    if ((v4 & 0x200000) != 0) {
      LOWORD(v3) = shadow_poly(v3 + 2, v3[1], (unsigned __int8)v4);
    } else if ((v4 & 0x4000) != 0) {
      LOWORD(v3) = twpoly((int16 *)v3 + 4, (unsigned __int8)v4);
    } else {
      LOWORD(v3) = poly(v3 + 2, v3[1], (unsigned __int8)v4);
    }
  }
  return (__int16)v3;*/
}

//-------------------------------------------------------------------------------------------------

void poly(tPoint *vertices, int iVertexCount, int16 nfillColor)
{
  // Preserve original screen width since it might be modified during drawing
  int iOriginalScreenWidth = winw;

  // Vertex indices and bounding box variables
  int iTopVertexIndex = 0;          // Index of top-most vertex
  int iMinX = vertices[0].x;        // Minimum polygon X
  int iMaxX = vertices[0].x;        // Maximum polygon X
  int iMinY = vertices[0].y;        // Minimum polygon Y
  int iMaxY = vertices[0].y;        // Maximum polygon Y

  // Edge tracking variables
  int iCurrentScanlineY;            // Current scanline being processed
  int iLeftEdgeX;                   // Current left edge X position
  int iRightEdgeX;                  // Current right edge X position
  int iLeftEdgeDx;                  // Left edge X step per scanline
  int iRightEdgeDx;                 // Right edge X step per scanline
  int iLeftEdgeRemaining;           // Scanlines remaining for current left edge segment
  int iRightEdgeRemaining;          // Scanlines remaining for current right edge segment
  int iLeftVertexIndex;             // Current left vertex index
  int iRightVertexIndex;            // Current right vertex index
  int iLeftErrorTerm;               // Bresenham error term for left edge
  int iRightErrorTerm;              // Bresenham error term for right edge

  // Temporary variables for intermediate calculations
  int iDeltaX;
  int iDeltaY;
  tPoint *pCurrentVertex;

  // find bounding box and top vertex
  for (int i = 1; i < iVertexCount; i++) {
    int iVertexX = vertices[i].x;
    int iVertexY = vertices[i].y;

    // Update bounding box coordinates
    if (iVertexX > iMaxX) iMaxX = iVertexX;
    if (iVertexX < iMinX) iMinX = iVertexX;
    if (iVertexY > iMaxY) iMaxY = iVertexY;
    if (iVertexY < iMinY) {
      iMinY = iVertexY;
      iTopVertexIndex = i;
    }
  }

  // Early exit for off-screen polygons
  if (iMaxX < 0 || iMaxY < 0 || iOriginalScreenWidth <= iMinX || iMinY >= winh) {
    goto RESTORE_AND_RETURN;
  }

  // Initialize starting points
  pCurrentVertex = &vertices[iTopVertexIndex];
  iCurrentScanlineY = pCurrentVertex->y;
  iLeftVertexIndex = iTopVertexIndex;
  iRightVertexIndex = iTopVertexIndex;

  // Initialize edge tracking
  if (iCurrentScanlineY >= 0) {
    // starting at or below screen top
    iLeftEdgeX = pCurrentVertex->x;
    iRightEdgeX = pCurrentVertex->x;

    // Initialize left edge
    do {
      iLeftVertexIndex = (iLeftVertexIndex + 1) % iVertexCount;
    } while (vertices[iLeftVertexIndex].y == iCurrentScanlineY);

    iLeftEdgeRemaining = vertices[iLeftVertexIndex].y - iCurrentScanlineY;
    iLeftEdgeDx = vertices[iLeftVertexIndex].x - iLeftEdgeX;

    // Initialize right edge
    do {
      iRightVertexIndex = (iRightVertexIndex - 1 + iVertexCount) % iVertexCount;
    } while (vertices[iRightVertexIndex].y == iCurrentScanlineY);

    iRightEdgeRemaining = vertices[iRightVertexIndex].y - iCurrentScanlineY;
    iRightEdgeDx = vertices[iRightVertexIndex].x - iRightEdgeX;

    // Calculate Bresenham error terms
    iLeftErrorTerm = abs(iLeftEdgeDx) % abs(iLeftEdgeRemaining);
    iRightErrorTerm = abs(iRightEdgeDx) % abs(iRightEdgeRemaining);

    // Precompute step values
    iLeftEdgeDx /= iLeftEdgeRemaining;
    iRightEdgeDx /= iRightEdgeRemaining;
  } else {
      // starting above screen top (negative Y)
    int iInitialY = pCurrentVertex->y;

    // Traverse downward to find first visible edge segment
    do {
      iLeftVertexIndex = (iLeftVertexIndex + 1) % iVertexCount;
    } while (vertices[iLeftVertexIndex].y < 0);

    // Calculate edge parameters for left side
    iDeltaY = vertices[iLeftVertexIndex].y - iInitialY;
    iDeltaX = vertices[iLeftVertexIndex].x - vertices[iTopVertexIndex].x;
    iLeftEdgeRemaining = iDeltaY;
    iLeftEdgeDx = iDeltaX / iDeltaY;
    iLeftErrorTerm = iDeltaX % iDeltaY;

    // Adjust starting position for negative Y
    iLeftEdgeX = vertices[iTopVertexIndex].x - iLeftEdgeDx * iInitialY;

    // Repeat for right edge
    do {
      iRightVertexIndex = (iRightVertexIndex - 1 + iVertexCount) % iVertexCount;
    } while (vertices[iRightVertexIndex].y < 0);

    // Calculate edge parameters for right side
    iDeltaY = vertices[iRightVertexIndex].y - iInitialY;
    iDeltaX = vertices[iRightVertexIndex].x - vertices[iTopVertexIndex].x;
    iRightEdgeRemaining = iDeltaY;
    iRightEdgeDx = iDeltaX / iDeltaY;
    iRightErrorTerm = iDeltaX % iDeltaY;

    // Adjust starting position for negative Y
    iRightEdgeX = vertices[iTopVertexIndex].x - iRightEdgeDx * iInitialY;
    iCurrentScanlineY = 0;  // Start at top of screen
  }

  // Main scanline processing loop
  while (iCurrentScanlineY < winh) {
    // Clipping and drawing
    if (iLeftEdgeX < iOriginalScreenWidth &&
        iRightEdgeX > 0 &&
        iLeftEdgeX < iRightEdgeX) {

      // Calculate clipped segment boundaries
      int iStartX = (iLeftEdgeX > 0) ? iLeftEdgeX : 0;
      int iEndX = (iRightEdgeX < iOriginalScreenWidth) ? iRightEdgeX : iOriginalScreenWidth;
      int iSegmentLength = iEndX - iStartX;

      // Only draw if segment is visible
      if (iSegmentLength > 0) {
        uint8 *pDest = scrptr + iCurrentScanlineY * iOriginalScreenWidth + iStartX;
        memset(pDest, nfillColor, iSegmentLength);
      }
    }

    // Update edge positions
    // Update left edge with Bresenham algorithm
    iLeftErrorTerm += iLeftEdgeDx;
    while (iLeftErrorTerm >= 1) {
      iLeftEdgeDx++;
      iLeftErrorTerm--;
    }
    while (iLeftErrorTerm <= -1) {
      iLeftEdgeDx--;
      iLeftErrorTerm++;
    }

    // Update right edge with Bresenham algorithm
    iRightErrorTerm += iRightEdgeDx;
    while (iRightErrorTerm >= 1) {
      iRightEdgeDx++;
      iRightErrorTerm--;
    }
    while (iRightErrorTerm <= -1) {
      iRightEdgeDx--;
      iRightErrorTerm++;
    }

    // Move to next scanline
    iCurrentScanlineY++;
    iLeftEdgeRemaining--;
    iRightEdgeRemaining--;

    // Edge segment transition
    // Check if left edge segment is exhausted
    if (iLeftEdgeRemaining == 0) {
      // Move to next vertex
      iLeftVertexIndex = (iLeftVertexIndex + 1) % iVertexCount;

      // Skip horizontal edges
      while (vertices[(iLeftVertexIndex + 1) % iVertexCount].y == iCurrentScanlineY) {
        iLeftVertexIndex = (iLeftVertexIndex + 1) % iVertexCount;
      }

      // Calculate new edge parameters
      tPoint *pNextVertex = &vertices[(iLeftVertexIndex + 1) % iVertexCount];
      iLeftEdgeRemaining = pNextVertex->y - iCurrentScanlineY;
      iLeftEdgeDx = pNextVertex->x - vertices[iLeftVertexIndex].x;

      // Reinitialize Bresenham parameters
      if (iLeftEdgeRemaining != 0) {
        iLeftErrorTerm = abs(iLeftEdgeDx) % abs(iLeftEdgeRemaining);
        iLeftEdgeDx /= iLeftEdgeRemaining;
      }
    }

    // Check if right edge segment is exhausted
    if (iRightEdgeRemaining == 0) {
      // Move to next vertex
      iRightVertexIndex = (iRightVertexIndex - 1 + iVertexCount) % iVertexCount;

      // Skip horizontal edges
      while (vertices[(iRightVertexIndex - 1 + iVertexCount) % iVertexCount].y == iCurrentScanlineY) {
        iRightVertexIndex = (iRightVertexIndex - 1 + iVertexCount) % iVertexCount;
      }

      // Calculate new edge parameters
      tPoint *pNextVertex = &vertices[(iRightVertexIndex - 1 + iVertexCount) % iVertexCount];
      iRightEdgeRemaining = pNextVertex->y - iCurrentScanlineY;
      iRightEdgeDx = pNextVertex->x - vertices[iRightVertexIndex].x;

      // Reinitialize Bresenham parameters
      if (iRightEdgeRemaining != 0) {
        iRightErrorTerm = abs(iRightEdgeDx) % abs(iRightEdgeRemaining);
        iRightEdgeDx /= iRightEdgeRemaining;
      }
    }

    // Stop processing if edges meet
    if (iLeftVertexIndex == iRightVertexIndex) {
      break;
    }
  }

RESTORE_AND_RETURN:
  // Restore original screen width before returning
  winw = iOriginalScreenWidth;
}

//-------------------------------------------------------------------------------------------------

void shadow_poly(tPoint *vertices, int iNumVertices, int iPaletteIndex)
{
  int iOldWinW; // ebp
  int iMinX; // edi
  int iMinYIdx; // esi
  int iVertX; // ebx
  int iY; // eax
  tPoint *pMinYVert; // eax
  int iCurrScanline; // ebx
  int iBackwardIdx; // edi
  int16 nTempX; // ax
  int iTempY_1; // eax
  int iTempY_2; // ebx
  int16 nTempX_1; // ax
  int iCalculatedStep_1; // eax
  int iCalculatedStep; // eax
  int iStepOffset; // edx
  int16 nTempX_2; // ax
  int iTempY_3; // eax
  int iTempY_4; // ebx
  int16 nTempX_3; // ax
  int iRightCalcStep; // eax
  int iRightCalculatedStep; // eax
  int iRightStepOffset; // edx
  tPoint *pVertex; // edx
  int iStep_3; // eax
  int iStep; // eax
  int iRemainder_1; // edx
  tPoint *pVertex_1; // eax
  int iStep_1; // eax
  int iRightEdgeUpdate; // edx
  int iTempVal; // eax
  bool bZeroFlag; // zf
  int iVertexX; // edx
  int16 nTempX_4; // ax
  tPoint *pVertex_10; // eax
  int iNewStep; // eax
  int iTempVal_7; // eax
  int16 nTempX_5; // ax
  tPoint *pVertex_2; // eax
  int iStep_4; // eax
  int iStepOffset_1; // edx
  int iVertexIdx_2; // edx
  int16 nTempX_13; // ax
  tPoint *pVertex_9; // eax
  int iNewStep_4; // eax
  int iTempVal_6; // eax
  int16 nTempX_14; // ax
  tPoint *pVertex_8; // eax
  int iStep_7; // eax
  int iPixelIdx_2; // edx
  int iStep_2; // edx
  int nTempX_10; // edx
  int16 nTempX_11; // ax
  tPoint *pVertex_6; // eax
  int iNewStep_3; // eax
  int iTempVal_5; // eax
  int16 nTempX_12; // ax
  tPoint *pVertex_7; // eax
  int iStep_8; // eax
  int iPixelIdx_1; // edx
  int iRightEdgeTemp_1; // edx
  int iTempVal_3; // eax
  int iTempY_5; // edx
  int16 nTempX_8; // ax
  tPoint *pVertex_4; // eax
  int iNewStep_2; // eax
  int iTempVal_4; // eax
  int16 nTempX_9; // ax
  tPoint *pVertex_5; // eax
  int iStep_6; // eax
  int iRightEdgeTemp; // edx
  int iTempVal_1; // eax
  int iVertexIdx_1; // edx
  int16 nTempX_6; // ax
  tPoint *pVertex_11; // eax
  int iNewStep_1; // eax
  int iTempVal_2; // eax
  int16 nTempX_7; // ax
  tPoint *pVertex_3; // eax
  int iStep_5; // eax
  int iMaxY; // [esp+4h] [ebp-6Ch]
  int iMaxX; // [esp+8h] [ebp-68h]
  int iPixelIdx_3; // [esp+10h] [ebp-60h]
  int iPixelIdx; // [esp+14h] [ebp-5Ch]
  char *pShadePalette; // [esp+1Ch] [ebp-54h]
  int iMinY; // [esp+20h] [ebp-50h]
  uint8 *pDest4; // [esp+24h] [ebp-4Ch]
  uint8 *pDest3; // [esp+28h] [ebp-48h]
  uint8 *pDest2; // [esp+2Ch] [ebp-44h]
  uint8 *pDest; // [esp+30h] [ebp-40h]
  int iTempY; // [esp+34h] [ebp-3Ch]
  int iTempY2; // [esp+38h] [ebp-38h]
  int iRemainder; // [esp+40h] [ebp-30h]
  int iRightEdgeDx; // [esp+40h] [ebp-30h]
  int iLeftEdgeDx; // [esp+40h] [ebp-30h]
  int iTempEdgeDx; // [esp+40h] [ebp-30h]
  int iTempEdgeDx2; // [esp+40h] [ebp-30h]
  int iTempEdgeDx3; // [esp+40h] [ebp-30h]
  int iTempEdgeDx4; // [esp+40h] [ebp-30h]
  int iTempEdgeDx5; // [esp+40h] [ebp-30h]
  int iLeftEdgeDxTemp; // [esp+44h] [ebp-2Ch]
  int iLeftEdgeDx_1; // [esp+44h] [ebp-2Ch]
  int iLeftEdgeDxTemp2; // [esp+44h] [ebp-2Ch]
  int iLeftEdgeDxTemp3; // [esp+44h] [ebp-2Ch]
  int iLeftEdgeDxTemp4; // [esp+44h] [ebp-2Ch]
  int iLeftEdgeDxTemp5; // [esp+44h] [ebp-2Ch]
  int iLeftEdgeDxTemp6; // [esp+44h] [ebp-2Ch]
  int iLeftEdgeDxTemp7; // [esp+44h] [ebp-2Ch]
  int iRightEdgeXTemp; // [esp+48h] [ebp-28h]
  int iRightEdgeX; // [esp+48h] [ebp-28h]
  int iLeftEdgeXTemp; // [esp+4Ch] [ebp-24h]
  int iLeftEdgeX; // [esp+4Ch] [ebp-24h]
  int iVertexIdx; // [esp+50h] [ebp-20h]
  int iRightRemain; // [esp+54h] [ebp-1Ch]
  int iLeftRemain; // [esp+58h] [ebp-18h]
  int16 nSegmentWidth; // [esp+5Ch] [ebp-14h]

  iOldWinW = winw;
  iMinX = vertices->x;
  iMinYIdx = 0;
  iMaxX = vertices->x;
  pShadePalette = &shade_palette[256 * iPaletteIndex];
  iVertexIdx = 1;
  iMinY = vertices->y;
  iMaxY = iMinY;

  // Find bouding box and min Y vertex
  while ((int16)iVertexIdx < iNumVertices) {
    iVertX = vertices[(int16)iVertexIdx].x;
    iY = vertices[(int16)iVertexIdx].y;

    // Update X boundaries
    if (iVertX <= iMaxX) {
      if (iVertX < iMinX)
        iMinX = vertices[(int16)iVertexIdx].x;
    } else {
      iMaxX = vertices[(int16)iVertexIdx].x;
    }

    // Update Y boundaries and get min Y vertex index
    if (iY <= iMaxY) {
      if (iY < iMinY) {
        iMinYIdx = iVertexIdx;
        iMinY = vertices[(int16)iVertexIdx].y;
      }
    } else {
      iMaxY = vertices[(int16)iVertexIdx].y;
    }
    ++iVertexIdx;
  }

  // Check if polygon is completely off-screen
  if (iMaxX < 0 || iMaxY < 0 || iMinX >= winw || iMinY >= winh)
    goto RESTORE_AND_RETURN;

  pMinYVert = &vertices[(int16)iMinYIdx];
  iCurrScanline = pMinYVert->y;
  iBackwardIdx = iMinYIdx;

  if (iCurrScanline >= 0) {
    // Initialize edges starting from min Y vertex (16.16 fixed point)
    iRightEdgeX = (iRightEdgeX & 0x0000FFFF) | ((pMinYVert->x & 0xFFFF) << 16);
    iLeftEdgeX = (iLeftEdgeX & 0x0000FFFF) | ((pMinYVert->x & 0xFFFF) << 16);
    iLeftEdgeDx &= 0xFFFF0000;
    iRightEdgeX &= 0xFFFF0000;
    iLeftEdgeDxTemp2 &= 0xFFFF0000;
    iLeftEdgeX &= 0xFFFF0000;

    while (1) {
      // Process left edge
      if ((int16)++iMinYIdx == iNumVertices)
        iMinYIdx = 0;
      iStep_3 = 8 * (int16)iMinYIdx;
      pVertex = (tPoint *)((char *)vertices + iStep_3);
      
      int16 *yArray = (int16 *)&vertices->y;
      int16 yValue = yArray[iStep_3 / 2];
      iStep_3 = (iStep_3 & 0xFFFF0000) | ((yValue - iCurrScanline) & 0xFFFF);

      iLeftRemain = iStep_3;
      if ((int16)iStep_3)
        break;                                  // found non-horizontal edge
      if ((int16)iMinYIdx == (int16)iBackwardIdx)
        goto RESTORE_AND_RETURN;
      iLeftEdgeX = (iLeftEdgeX & 0x0000FFFF) | ((pVertex->x & 0xFFFF) << 16);
    }

    // Calculate left edge step
    iLeftEdgeDxTemp2 = (iLeftEdgeDxTemp2 & 0x0000FFFF) | (((pVertex->x & 0xFFFF) - (iLeftEdgeX >> 16)) << 16);
    iStep = iLeftEdgeDxTemp2 / (int16)iStep_3;
    iRemainder_1 = iLeftEdgeDxTemp2 % (int16)iLeftRemain;
    iLeftEdgeDx_1 = iStep;
    if (iStep < 0)
      iLeftEdgeX += iStep;                      // adjust for negative slope
                                                // 
    while (1) {
      // Process right edge
      if ((int16)--iBackwardIdx == -1)
        iBackwardIdx = iNumVertices - 1;
      pVertex_1 = &vertices[(int16)iBackwardIdx];
      iRemainder_1 = (iRemainder_1 & 0xFFFF0000) | (((pVertex_1->y & 0xFFFF) - iCurrScanline) & 0xFFFF);// deltaY
      iRightRemain = iRemainder_1;
      if ((int16)iRemainder_1)                // found non-horizontal edge
        break;
      if ((int16)iMinYIdx == (int16)iBackwardIdx)
        goto RESTORE_AND_RETURN;
      iRightEdgeX = (iRightEdgeX & 0x0000FFFF) | ((pVertex_1->x & 0xFFFF) << 16);
    }

    // Calculate right edge step
    iLeftEdgeDx = (iLeftEdgeDx & 0x0000FFFF) | (((pVertex_1->x & 0xFFFF) - (iRightEdgeX >> 16)) << 16);
    iStep_1 = iLeftEdgeDx / (int16)iRemainder_1;
    iRightEdgeDx = iStep_1;
    if (iStep_1 > 0)
      iRightEdgeX += iStep_1;
  } else {
    // handle starting above screen
    iTempY = pMinYVert->y;
    iTempY2 = iTempY;
    iRightEdgeXTemp &= 0xFFFF0000;
    iRemainder &= 0xFFFF0000;
    iLeftEdgeXTemp &= 0xFFFF0000;
    iLeftEdgeDxTemp &= 0xFFFF0000;

    // Find first visible left vertex
    do {
      nTempX = vertices[(int16)iMinYIdx++].x;
      iLeftEdgeXTemp = (iLeftEdgeXTemp & 0x0000FFFF) | (nTempX << 16);
      if ((int16)iMinYIdx == iNumVertices)
        iMinYIdx = 0;
      iTempY_1 = vertices[(int16)iMinYIdx].y;
      iTempY_2 = iTempY2;
      iTempY2 = iTempY_1;
    } while (iTempY_1 < 0);

    // Handle zero-length segments
    if (!iTempY_1) {
      do {
        nTempX_1 = vertices[(int16)iMinYIdx++].x;
        iLeftEdgeXTemp = (iLeftEdgeXTemp & 0x0000FFFF) | (nTempX_1 << 16);
        if ((int16)iMinYIdx == iNumVertices)
          iMinYIdx = 0;
        iCalculatedStep_1 = vertices[(int16)iMinYIdx].y;
        iTempY_2 = iTempY2;
        iTempY2 = iCalculatedStep_1;
      } while (!iCalculatedStep_1);
      if (iCalculatedStep_1 < 0)
        goto RESTORE_AND_RETURN;
    }

    // Calculate left edge parameters for clipped start
    iLeftEdgeDxTemp = (iLeftEdgeDxTemp & 0x0000FFFF) | (((vertices[(int16)iMinYIdx].x & 0xFFFF) - (iLeftEdgeXTemp >> 16)) << 16);
    iLeftRemain = iTempY2;
    iCalculatedStep = iLeftEdgeDxTemp / ((int16)iTempY2 - iTempY_2);
    iStepOffset = iLeftEdgeXTemp - iCalculatedStep * iTempY_2;
    iLeftEdgeDx_1 = iCalculatedStep;
    iLeftEdgeX = iStepOffset;
    if (iCalculatedStep < 0)
      iLeftEdgeX = iCalculatedStep + iStepOffset;

    // Find first visible right vertex
    do {
      nTempX_2 = vertices[(int16)iBackwardIdx--].x;
      iRightEdgeXTemp = (iRightEdgeXTemp & 0x0000FFFF) | (nTempX_2 << 16);
      if ((int16)iBackwardIdx == -1)
        iBackwardIdx = iNumVertices - 1;
      iTempY_3 = vertices[(int16)iBackwardIdx].y;
      iTempY_4 = iTempY;
      iTempY = iTempY_3;
    } while (iTempY_3 < 0);

    // Handle zero-length segments
    if (!iTempY_3) {
      do {
        nTempX_3 = vertices[(int16)iBackwardIdx--].x;
        iRightEdgeXTemp = (iRightEdgeXTemp & 0x0000FFFF) | (nTempX_3 << 16);
        if ((int16)iBackwardIdx == -1)
          iBackwardIdx = iNumVertices - 1;
        iRightCalcStep = vertices[(int16)iBackwardIdx].y;
        iTempY_4 = iTempY;
        iTempY = iRightCalcStep;
      } while (!iRightCalcStep);
      if (iRightCalcStep < 0)
        goto RESTORE_AND_RETURN;
    }

    // Calculate right edge parameters for clipped start
    iRemainder = ((vertices[(int16)iBackwardIdx].x & 0xFFFF) - (iRightEdgeXTemp >> 16)) << 16;
    iRightRemain = iTempY;
    iRightCalculatedStep = iRemainder / ((int16)iTempY - iTempY_4);
    iRightStepOffset = iRightEdgeXTemp - iRightCalculatedStep * iTempY_4;
    iRightEdgeDx = iRightCalculatedStep;
    iRightEdgeX = iRightStepOffset;
    if (iRightCalculatedStep > 0)
      iRightEdgeX = iRightCalculatedStep + iRightStepOffset;
    iCurrScanline = 0;                          // Start rendering at top of screen
  }

  // Edge processing and clipping
  while (((iLeftEdgeX >> 16) & 0xFFFF) >= winw || iRightEdgeX < 0 || iLeftEdgeX > iRightEdgeX) {
    // Advance edges
    iLeftEdgeX += iLeftEdgeDx_1;
    ++iCurrScanline;
    iRightEdgeUpdate = iRightEdgeDx + iRightEdgeX;
    iTempVal = (iTempVal & 0x0000FFFF) | (iLeftRemain & 0xFFFF0000);
    iRightEdgeX += iRightEdgeDx;
    iTempVal = (iTempVal & 0xFFFF0000) | ((iLeftRemain - 1) & 0xFFFF);
    bZeroFlag = (int16)iLeftRemain == 1;
    iLeftRemain = iTempVal;

    // Process left edge segment completion
    if (bZeroFlag) {
      while ((int16)iMinYIdx != (int16)iBackwardIdx) {
        iVertexX = (iVertexX & 0x0000FFFF) | (iNumVertices & 0xFFFF0000);
        nTempX_4 = vertices[(int16)iMinYIdx++].x;
        iLeftEdgeX = (iLeftEdgeX & 0x0000FFFF) | (nTempX_4 << 16);
        if ((int16)iMinYIdx == iNumVertices)
          iMinYIdx = 0;
        pVertex_10 = &vertices[(int16)iMinYIdx];
        iVertexX = (iVertexX & 0xFFFF0000) | (pVertex_10->y & 0xFFFF);
        iLeftRemain = iVertexX - iCurrScanline;
        if ((int16)(iVertexX - iCurrScanline) > 0) {
          iLeftEdgeDxTemp3 = (iLeftEdgeDxTemp3 & 0x0000FFFF) | (((pVertex_10->x & 0xFFFF) - (iLeftEdgeX >> 16)) << 16);
          iLeftEdgeX &= 0xFFFF0000;
          iLeftEdgeDxTemp3 &= 0xFFFF0000;
          iNewStep = iLeftEdgeDxTemp3 / (int16)iLeftRemain;
          iRightEdgeUpdate = iLeftEdgeDxTemp3 % (int16)iLeftRemain;
          iLeftEdgeDx_1 = iNewStep;
          if (iNewStep < 0)
            iLeftEdgeX += iNewStep;
          goto EDGE_ADVANCE_1;
        }
      }
      goto RESTORE_AND_RETURN;
    }
  EDGE_ADVANCE_1:
    iTempVal_7 = (iTempVal_7 & 0x0000FFFF) | (iRightRemain & 0xFFFF0000);
    iTempVal_7 = (iTempVal_7 & 0xFFFF0000) | ((iRightRemain - 1) & 0xFFFF);
    bZeroFlag = (int16)iRightRemain == 1;
    iRightRemain = iTempVal_7;

    // Process right edge segment completion
    if (bZeroFlag) {
      while ((int16)iMinYIdx != (int16)iBackwardIdx) {
        nTempX_5 = vertices[(int16)iBackwardIdx--].x;
        iRightEdgeX = (iRightEdgeX & 0x0000FFFF) | (nTempX_5 << 16);
        if ((int16)iBackwardIdx == -1)
          iBackwardIdx = iNumVertices - 1;
        pVertex_2 = &vertices[(int16)iBackwardIdx];
        iRightEdgeUpdate = (iRightEdgeUpdate & 0xFFFF0000) | (pVertex_2->y & 0xFFFF);
        iRightEdgeUpdate -= iCurrScanline;
        iRightRemain = iRightEdgeUpdate;
        if ((int16)iRightEdgeUpdate > 0) {
          iTempEdgeDx = (iTempEdgeDx & 0x0000FFFF) | (((pVertex_2->x & 0xFFFF) - (iRightEdgeX >> 16)) << 16);
          iRightEdgeX &= 0xFFFF0000;
          iTempEdgeDx &= 0xFFFF0000;
          iStep_4 = iTempEdgeDx / (int16)iRightEdgeUpdate;
          iRightEdgeDx = iStep_4;
          if (iStep_4 > 0)
            iRightEdgeX += iStep_4;
          goto EDGE_ADVANCE_2;
        }
      }
      goto RESTORE_AND_RETURN;
    }
  EDGE_ADVANCE_2:
      // Screen boundary check
    if (iCurrScanline >= winh)
      goto RESTORE_AND_RETURN;
  }
  // Check right edge against screen
  while (1) {
    if (((int16)(iLeftEdgeX >> 16)) >= iOldWinW) {
      if (((int16)(iLeftEdgeX >> 16)) >= iOldWinW)    // Left-clipped scanline
        goto RESTORE_AND_RETURN;
      if (((int16)(iRightEdgeX >> 16)) < iOldWinW)
        goto RENDER_LEFT_VISIBLE_SEGMENT;
    FULL_WIDTH_RENDER:
      if (iRightEdgeX < 0)
        goto RESTORE_AND_RETURN;
      while (1) {
        // Fully on-screen scanline
      FULL_WIDTH_LOOP:
        pDest = &scrptr[iOldWinW * iCurrScanline];
        for (iPixelIdx = 0; iOldWinW > iPixelIdx; ++iPixelIdx) {
          *pDest = pShadePalette[*pDest];
          ++pDest;
        }

        // Advance to next scanline
        iLeftEdgeX += iLeftEdgeDx_1;
        ++iCurrScanline;
        iRightEdgeTemp = iRightEdgeDx + iRightEdgeX;
        iTempVal_1 = (iTempVal_1 & 0x0000FFFF) | (iLeftRemain & 0xFFFF0000);
        iRightEdgeX += iRightEdgeDx;
        iTempVal_1 = (iTempVal_1 & 0xFFFF0000) | ((iLeftRemain - 1) & 0xFFFF);
        bZeroFlag = (int16)iLeftRemain == 1;
        iLeftRemain = iTempVal_1;

        // Left edge segment completion
        if (bZeroFlag) {
          while ((int16)iMinYIdx != (int16)iBackwardIdx) {
            iVertexIdx_1 = (iVertexIdx_1 & 0x0000FFFF) | (iNumVertices & 0xFFFF0000);
            nTempX_6 = vertices[(int16)iMinYIdx++].x;
            iLeftEdgeX = (iLeftEdgeX & 0x0000FFFF) | (nTempX_6 << 16);
            if ((int16)iMinYIdx == iNumVertices)
              iMinYIdx = 0;
            pVertex_11 = &vertices[(int16)iMinYIdx];
            iVertexIdx_1 = (iVertexIdx_1 & 0xFFFF0000) | (pVertex_11->y & 0xFFFF);
            iLeftRemain = iVertexIdx_1 - iCurrScanline;
            if ((int16)(iVertexIdx_1 - iCurrScanline) > 0) {
              iLeftEdgeDxTemp7 = (iLeftEdgeDxTemp7 & 0x0000FFFF) | (((pVertex_11->x & 0xFFFF) - (iLeftEdgeX >> 16)) << 16);
              iLeftEdgeX &= 0xFFFF0000;
              iLeftEdgeDxTemp7 &= 0xFFFF0000;
              iNewStep_1 = iLeftEdgeDxTemp7 / (int16)iLeftRemain;
              iRightEdgeTemp = iLeftEdgeDxTemp7 % (int16)iLeftRemain;
              iLeftEdgeDx_1 = iNewStep_1;
              if (iNewStep_1 < 0)
                iLeftEdgeX += iNewStep_1;
              goto LEFT_EDGE_COMPLETE;
            }
          }
          goto RESTORE_AND_RETURN;
        }
      LEFT_EDGE_COMPLETE:
        iTempVal_2 = (iTempVal_2 & 0x0000FFFF) | (iRightRemain & 0xFFFF0000);
        iTempVal_2 = (iTempVal_2 & 0xFFFF0000) | ((iRightRemain - 1) & 0xFFFF);
        bZeroFlag = (int16)iRightRemain == 1;
        iRightRemain = iTempVal_2;

        // Process right edge segment
        if (bZeroFlag) {
          while ((int16)iMinYIdx != (int16)iBackwardIdx) {
            nTempX_7 = vertices[(int16)iBackwardIdx--].x;
            iRightEdgeX = (iRightEdgeX & 0x0000FFFF) | (nTempX_7 << 16);
            if ((int16)iBackwardIdx == -1)
              iBackwardIdx = iNumVertices - 1;
            pVertex_3 = &vertices[(int16)iBackwardIdx];
            iRightEdgeTemp = (iRightEdgeTemp & 0xFFFF0000) | (pVertex_3->y & 0xFFFF);
            iRightEdgeTemp -= iCurrScanline;
            iRightRemain = iRightEdgeTemp;
            if ((int16)iRightEdgeTemp > 0) {
              iTempEdgeDx5 = (iTempEdgeDx5 & 0x0000FFFF) | (((pVertex_3->x & 0xFFFF) - (iRightEdgeX >> 16)) << 16);
              iRightEdgeX &= 0xFFFF0000;
              iTempEdgeDx5 &= 0xFFFF0000;
              iStep_5 = iTempEdgeDx5 / (int16)iRightEdgeTemp;
              iRightEdgeDx = iStep_5;
              if (iStep_5 > 0)
                iRightEdgeX += iStep_5;
              goto SCANLINE_CHECK;
            }
          }
          goto RESTORE_AND_RETURN;
        }
      SCANLINE_CHECK:
              // Exit if at bottom of screen
        if (iCurrScanline >= winh)
          goto RESTORE_AND_RETURN;
        // Check if left edge is on-screen
        if (((int16)(iLeftEdgeX >> 16)) < iOldWinW)
          break;
        // Check if right edge is off-screen right
        if (((int16)(iRightEdgeX >> 16)) < iOldWinW)
          goto RENDER_RIGHT_VISIBLE;
      }
      // Verify left edge position
      if (((int16)(iLeftEdgeX >> 16)) >= iOldWinW)
        goto RESTORE_AND_RETURN;
      // Verify right edge position
      if (((int16)(iRightEdgeX >> 16)) >= iOldWinW)
        goto RIGHT_CLIPPED_RENDER;
    RENDER_LEFT_VISIBLE:
      if (iRightEdgeX < 0)
        goto RESTORE_AND_RETURN;
    } else {

      // Handle right-clipped scanlines
      while (((int16)(iRightEdgeX >> 16)) >= iOldWinW) {
        if (iRightEdgeX < 0)
          goto RESTORE_AND_RETURN;
        while (1) {
          // Right clipped scanline processing
        RIGHT_CLIPPED_RENDER:
          pDest3 = &scrptr[((int16)(iLeftEdgeX >> 16)) + iOldWinW * iCurrScanline];
          for (iPixelIdx_1 = 0; iOldWinW - ((int16)(iLeftEdgeX >> 16)) > iPixelIdx_1; ++iPixelIdx_1) {
            *pDest3 = pShadePalette[*pDest3];
            ++pDest3;
          }
          // Advance to next scanline
          iLeftEdgeX += iLeftEdgeDx_1;
          ++iCurrScanline;
          iRightEdgeTemp_1 = iRightEdgeDx + iRightEdgeX;
          iTempVal_3 = (iTempVal_3 & 0x0000FFFF) | (iLeftRemain & 0xFFFF0000);
          iRightEdgeX += iRightEdgeDx;
          iTempVal_3 = (iTempVal_3 & 0xFFFF0000) | ((iLeftRemain - 1) & 0xFFFF);
          bZeroFlag = (int16)iLeftRemain == 1;
          iLeftRemain = iTempVal_3;

          // Process left edge segment completion
          if (bZeroFlag) {
            while ((int16)iMinYIdx != (int16)iBackwardIdx) {
              iTempY_5 = (iTempY_5 & 0x0000FFFF) | (iNumVertices & 0xFFFF0000);
              nTempX_8 = vertices[(int16)iMinYIdx++].x;
              iLeftEdgeX = (iLeftEdgeX & 0x0000FFFF) | ((nTempX_8 & 0xFFFF) << 16);
              if ((int16)iMinYIdx == iNumVertices)
                iMinYIdx = 0;
              pVertex_4 = &vertices[(int16)iMinYIdx];
              iTempY_5 = (iTempY_5 & 0xFFFF0000) | (pVertex_4->y & 0xFFFF);
              iLeftRemain = iTempY_5 - iCurrScanline;
              if ((int16)(iTempY_5 - iCurrScanline) > 0) {
                iLeftEdgeDxTemp6 = (iLeftEdgeDxTemp6 & 0x0000FFFF) | (((pVertex_4->x & 0xFFFF) - (iLeftEdgeX >> 16)) << 16);
                iLeftEdgeX &= 0xFFFF0000;
                iLeftEdgeDxTemp6 &= 0xFFFF0000;
                iNewStep_2 = iLeftEdgeDxTemp6 / (int16)iLeftRemain;
                iRightEdgeTemp_1 = iLeftEdgeDxTemp6 % (int16)iLeftRemain;
                iLeftEdgeDx_1 = iNewStep_2;
                if (iNewStep_2 < 0)
                  iLeftEdgeX += iNewStep_2;
                goto LEFT_EDGE_COMPLETE_2;
              }
            }
            goto RESTORE_AND_RETURN;
          }
        LEFT_EDGE_COMPLETE_2:
          iTempVal_4 = (iTempVal_4 & 0x0000FFFF) | (iRightRemain & 0xFFFF0000);
          iTempVal_4 = (iTempVal_4 & 0xFFFF0000) | ((iRightRemain - 1) & 0xFFFF);
          bZeroFlag = (int16)iRightRemain == 1;
          iRightRemain = iTempVal_4;

          // Process right edge segment completion
          if (bZeroFlag) {
            while ((int16)iMinYIdx != (int16)iBackwardIdx) {
              nTempX_9 = vertices[(int16)iBackwardIdx--].x;
              iRightEdgeX = (iRightEdgeX & 0x0000FFFF) | ((nTempX_9 & 0xFFFF) << 16);
              if ((int16)iBackwardIdx == -1)
                iBackwardIdx = iNumVertices - 1;
              pVertex_5 = &vertices[(int16)iBackwardIdx];
              iRightEdgeTemp_1 = (iRightEdgeTemp_1 & 0xFFFF0000) | (pVertex_5->y & 0xFFFF);
              iRightEdgeTemp_1 -= iCurrScanline;
              iRightRemain = iRightEdgeTemp_1;
              if ((int16)iRightEdgeTemp_1 > 0) {
                iTempEdgeDx4 = (iTempEdgeDx4 & 0x0000FFFF) | (((pVertex_5->x & 0xFFFF) - (iRightEdgeX >> 16)) << 16);
                iRightEdgeX &= 0xFFFF0000;
                iTempEdgeDx4 &= 0xFFFF0000;
                iStep_6 = iTempEdgeDx4 / (int16)iRightEdgeTemp_1;
                iRightEdgeDx = iStep_6;
                if (iStep_6 > 0)
                  iRightEdgeX += iStep_6;
                goto SCANLINE_CHECK_2;
              }
            }
            goto RESTORE_AND_RETURN;
          }
        SCANLINE_CHECK_2:
                  // Exit if at bottom of screen
          if (iCurrScanline >= winh) {
            winw = iOldWinW;
            return;
          }
          // Check if left edge is off-screen right
          if (((int16)(iLeftEdgeX >> 16)) >= iOldWinW)
            break;
          // Check if right edge is on-screen
          if (((int16)(iRightEdgeX >> 16)) < iOldWinW)
            goto RENDER_LEFT_VISIBLE;
        }

        // Handle partially visible scanlines
        if (((int16)(iLeftEdgeX >> 16)) >= iOldWinW)
          goto RESTORE_AND_RETURN;
        if (((int16)(iRightEdgeX >> 16)) >= iOldWinW)
          goto FULL_WIDTH_LOOP;
      RENDER_RIGHT_VISIBLE:
        if (iRightEdgeX < 0)
          goto RESTORE_AND_RETURN;
        while (1) {
          // Left-visible scanline processing
        RENDER_LEFT_VISIBLE_SEGMENT:
          pDest2 = &scrptr[iOldWinW * iCurrScanline];
          for (iPixelIdx_2 = 0; ((int16)(iRightEdgeX >> 16)) + 1 > iPixelIdx_2; ++iPixelIdx_2) {
            *pDest2 = pShadePalette[*pDest2];
            ++pDest2;
          }

          // Advance to next scanline
          iLeftEdgeX += iLeftEdgeDx_1;
          iRightEdgeX += iRightEdgeDx;
          iStep_2 = (iStep_2 & 0x0000FFFF) | (iLeftRemain & 0xFFFF0000);
          ++iCurrScanline;
          iStep_2 = (iStep_2 & 0xFFFF0000) | ((iLeftRemain - 1) & 0xFFFF);
          bZeroFlag = (int16)iLeftRemain == 1;
          iLeftRemain = iStep_2;

          // Process left edge segment completion
          if (bZeroFlag) {
            while ((int16)iMinYIdx != (int16)iBackwardIdx) {
              nTempX_10 = (nTempX_10 & 0x0000FFFF) | (iNumVertices & 0xFFFF0000);
              nTempX_11 = vertices[(int16)iMinYIdx++].x;
              iLeftEdgeX = (iLeftEdgeX & 0x0000FFFF) | ((nTempX_11 & 0xFFFF) << 16);
              if ((int16)iMinYIdx == iNumVertices)
                iMinYIdx = 0;
              pVertex_6 = &vertices[(int16)iMinYIdx];
              nTempX_10 = (nTempX_10 & 0xFFFF0000) | (pVertex_6->y & 0xFFFF);
              iLeftRemain = nTempX_10 - iCurrScanline;
              if ((int16)(nTempX_10 - iCurrScanline) > 0) {
                iLeftEdgeDxTemp5 = (iLeftEdgeDxTemp5 & 0x0000FFFF) | ((((pVertex_6->x & 0xFFFF) - (iLeftEdgeX >> 16)) & 0xFFFF) << 16);
                iLeftEdgeX &= 0xFFFF0000;
                iLeftEdgeDxTemp5 &= 0xFFFF0000;
                iNewStep_3 = iLeftEdgeDxTemp5 / (int16)iLeftRemain;
                iStep_2 = iLeftEdgeDxTemp5 % (int16)iLeftRemain;
                iLeftEdgeDx_1 = iNewStep_3;
                if (iNewStep_3 < 0)
                  iLeftEdgeX += iNewStep_3;
                goto LEFT_EDGE_COMPLETE_3;
              }
            }
            goto RESTORE_AND_RETURN;
          }
        LEFT_EDGE_COMPLETE_3:
          iTempVal_5 = (iTempVal_5 & 0x0000FFFF) | (iRightRemain & 0xFFFF0000);
          iTempVal_5 = (iTempVal_5 & 0xFFFF0000) | ((iRightRemain - 1) & 0xFFFF);
          bZeroFlag = (int16)iRightRemain == 1;
          iRightRemain = iTempVal_5;

          // Process right edge segment completion
          if (bZeroFlag) {
            while ((int16)iMinYIdx != (int16)iBackwardIdx) {
              nTempX_12 = vertices[(int16)iBackwardIdx--].x;
              iRightEdgeX = (iRightEdgeX & 0x0000FFFF) | ((nTempX_12 & 0xFFFF) << 16);
              if ((int16)iBackwardIdx == -1)
                iBackwardIdx = iNumVertices - 1;
              pVertex_7 = &vertices[(int16)iBackwardIdx];
              iStep_2 = (iStep_2 & 0xFFFF0000) | (pVertex_7->y & 0xFFFF);
              iStep_2 -= iCurrScanline;
              iRightRemain = iStep_2;
              if ((int16)iStep_2 > 0) {
                iTempEdgeDx3 = (iTempEdgeDx3 & 0x0000FFFF) | ((((pVertex_7->x & 0xFFFF) - (iRightEdgeX >> 16)) & 0xFFFF) << 16);
                iRightEdgeX &= 0xFFFF0000;
                iTempEdgeDx3 &= 0xFFFF0000;
                iStep_8 = iTempEdgeDx3 / (int16)iStep_2;
                iRightEdgeDx = iStep_8;
                if (iStep_8 > 0)
                  iRightEdgeX += iStep_8;
                goto SCANLINE_CHECK_3;
              }
            }
            goto RESTORE_AND_RETURN;
          }
        SCANLINE_CHECK_3:
                  // Exit if at bottom of screen
          if (iCurrScanline >= winh) {
            winw = iOldWinW;
            return;
          }
          // Check if left edge is on-screen
          if (((int16)(iLeftEdgeX >> 16)) < iOldWinW)
            break;
          // Check if right edge is off-screen right
          if (((int16)(iRightEdgeX >> 16)) >= iOldWinW)
            goto FULL_WIDTH_RENDER;
        }
        // Verify left edge position
        if (((int16)(iLeftEdgeX >> 16)) >= iOldWinW)
          goto RESTORE_AND_RETURN;
      }
    }

    // Calculate visible segment width
    nSegmentWidth = (int16)(((uint16)(iRightEdgeX >> 16)) - ((uint16)(iLeftEdgeX >> 16)) + 1);
    if (nSegmentWidth < 0)                    // Negative width check
      goto RESTORE_AND_RETURN;

    // Process visible scanline segment
    pDest4 = &scrptr[((int16)(iLeftEdgeX >> 16)) + iOldWinW * iCurrScanline];
    for (iPixelIdx_3 = 0; nSegmentWidth > iPixelIdx_3; ++iPixelIdx_3) {
      *pDest4 = pShadePalette[*pDest4];         // Apply palette
      ++pDest4;
    }

    // Advance to next scanline
    iLeftEdgeX += iLeftEdgeDx_1;
    iRightEdgeX += iRightEdgeDx;
    iStepOffset_1 = (iStepOffset_1 & 0x0000FFFF) | (iLeftRemain & 0xFFFF0000);
    ++iCurrScanline;
    iStepOffset_1 = (iStepOffset_1 & 0xFFFF0000) | ((iLeftRemain - 1) & 0xFFFF);
    bZeroFlag = (int16)iLeftRemain == 1;
    iLeftRemain = iStepOffset_1;

    // Process left edge segment completion
    if (bZeroFlag)
      break;
  PROCESS_RIGHT_EDGE:
      // Process right edge segment
    iTempVal_6 = (iTempVal_6 & 0x0000FFFF) | (iRightRemain & 0xFFFF0000);
    iTempVal_6 = (iTempVal_6 & 0xFFFF0000) | ((iRightRemain - 1) & 0xFFFF);
    bZeroFlag = (int16)iRightRemain == 1;
    iRightRemain = iTempVal_6;

    // Process right edge segment completion
    if (bZeroFlag) {
      while ((int16)iMinYIdx != (int16)iBackwardIdx) {
        nTempX_14 = vertices[(int16)iBackwardIdx--].x;
        iRightEdgeX = (iRightEdgeX & 0x0000FFFF) | (nTempX_14 << 16);
        if ((int16)iBackwardIdx == -1)
          iBackwardIdx = iNumVertices - 1;
        pVertex_8 = &vertices[(int16)iBackwardIdx];
        iStepOffset_1 = (iStepOffset_1 & 0xFFFF0000) | (pVertex_8->y & 0xFFFF);
        iStepOffset_1 -= iCurrScanline;
        iRightRemain = iStepOffset_1;
        if ((int16)iStepOffset_1 > 0) {
          iTempEdgeDx2 = (iTempEdgeDx2 & 0x0000FFFF) | ((((pVertex_8->x & 0xFFFF) - ((iRightEdgeX >> 16) & 0xFFFF)) & 0xFFFF) << 16);
          iRightEdgeX &= 0xFFFF0000;
          iTempEdgeDx2 &= 0xFFFF0000;
          iStep_7 = iTempEdgeDx2 / (int16)iStepOffset_1;
          iRightEdgeDx = iStep_7;
          if (iStep_7 > 0)
            iRightEdgeX += iStep_7;
          goto NEXT_SCANLINE;
        }
      }
      goto RESTORE_AND_RETURN;
    }
  NEXT_SCANLINE:
      // Exit if at bottom of screen
    if (iCurrScanline >= winh) {
      winw = iOldWinW;
      return;
    }
  }

  // Process left edge segment completion
  while ((int16)iMinYIdx != (int16)iBackwardIdx) {
    iVertexIdx_2 = (iVertexIdx_2 & 0x0000FFFF) | (iNumVertices & 0xFFFF0000);
    nTempX_13 = vertices[(int16)iMinYIdx++].x;
    iLeftEdgeX = (iLeftEdgeX & 0x0000FFFF) | (nTempX_13 << 16);
    if ((int16)iMinYIdx == iNumVertices)
      iMinYIdx = 0;
    pVertex_9 = &vertices[(int16)iMinYIdx];
    iVertexIdx_2 = (iVertexIdx_2 & 0xFFFF0000) | (pVertex_9->y & 0xFFFF);
    iLeftRemain = iVertexIdx_2 - iCurrScanline;
    if ((int16)(iVertexIdx_2 - iCurrScanline) > 0) {
      iLeftEdgeDxTemp4 = (iLeftEdgeDxTemp4 & 0x0000FFFF) | ((((pVertex_9->x & 0xFFFF) - ((iLeftEdgeX >> 16) & 0xFFFF)) & 0xFFFF) << 16);
      iLeftEdgeX &= 0xFFFF0000;
      iLeftEdgeDxTemp4 &= 0xFFFF0000;
      iNewStep_4 = iLeftEdgeDxTemp4 / (int16)iLeftRemain;
      iStepOffset_1 = iLeftEdgeDxTemp4 % (int16)iLeftRemain;
      iLeftEdgeDx_1 = iNewStep_4;
      if (iNewStep_4 < 0)
        iLeftEdgeX += iNewStep_4;
      goto PROCESS_RIGHT_EDGE;
    }
  }
RESTORE_AND_RETURN:
  winw = iOldWinW;
}

//-------------------------------------------------------------------------------------------------

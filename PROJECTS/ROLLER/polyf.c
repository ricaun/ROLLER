#include "polyf.h"
#include "3d.h"
#include "polytex.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
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
      LOWORD(v3) = twpoly((_WORD *)v3 + 4, (unsigned __int8)v4);
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

int16 shadow_poly(int *a1, int a2, int a3)
{
  return 0; /*
  unsigned int v3; // ebp
  int v5; // edi
  int v6; // esi
  int v7; // eax
  int v8; // ebx
  int *v9; // eax
  int v10; // ebx
  int v11; // edi
  __int16 v12; // ax
  int v13; // eax
  int v14; // ebx
  __int16 v15; // ax
  int v16; // eax
  int v17; // edx
  __int16 v18; // ax
  int v19; // eax
  int v20; // ebx
  __int16 v21; // ax
  int v22; // eax
  int v23; // edx
  _WORD *v24; // edx
  int v25; // eax
  int v26; // edx
  int v27; // eax
  int v28; // edx
  _BOOL1 v29; // zf
  int v30; // edx
  __int16 v31; // ax
  int v32; // eax
  __int16 v33; // ax
  int v34; // edx
  int v35; // edx
  __int16 v36; // ax
  int v37; // eax
  __int16 v38; // ax
  int k; // edx
  int v40; // edx
  int v41; // edx
  __int16 v42; // ax
  int v43; // eax
  __int16 v44; // ax
  signed int j; // edx
  int v46; // edx
  int v47; // edx
  __int16 v48; // ax
  int v49; // eax
  __int16 v50; // ax
  int v51; // edx
  int v52; // edx
  __int16 v53; // ax
  int v54; // eax
  __int16 v55; // ax
  int v57; // [esp+4h] [ebp-6Ch]
  int v58; // [esp+8h] [ebp-68h]
  int m; // [esp+10h] [ebp-60h]
  signed int i; // [esp+14h] [ebp-5Ch]
  char *v61; // [esp+1Ch] [ebp-54h]
  int v62; // [esp+20h] [ebp-50h]
  _BYTE *v63; // [esp+24h] [ebp-4Ch]
  _BYTE *v64; // [esp+28h] [ebp-48h]
  _BYTE *v65; // [esp+2Ch] [ebp-44h]
  _BYTE *v66; // [esp+30h] [ebp-40h]
  int v67; // [esp+34h] [ebp-3Ch]
  int v68; // [esp+38h] [ebp-38h]
  int v70; // [esp+40h] [ebp-30h]
  int v71; // [esp+40h] [ebp-30h]
  int v72; // [esp+40h] [ebp-30h]
  int v73; // [esp+40h] [ebp-30h]
  int v74; // [esp+40h] [ebp-30h]
  int v75; // [esp+40h] [ebp-30h]
  int v76; // [esp+40h] [ebp-30h]
  int v77; // [esp+40h] [ebp-30h]
  int v78; // [esp+44h] [ebp-2Ch]
  int v79; // [esp+44h] [ebp-2Ch]
  int v80; // [esp+44h] [ebp-2Ch]
  int v81; // [esp+44h] [ebp-2Ch]
  int v82; // [esp+44h] [ebp-2Ch]
  int v83; // [esp+44h] [ebp-2Ch]
  int v84; // [esp+44h] [ebp-2Ch]
  int v85; // [esp+44h] [ebp-2Ch]
  int v86; // [esp+48h] [ebp-28h]
  int v87; // [esp+48h] [ebp-28h]
  int v88; // [esp+4Ch] [ebp-24h]
  int v89; // [esp+4Ch] [ebp-24h]
  int v90; // [esp+50h] [ebp-20h]
  int v91; // [esp+54h] [ebp-1Ch]
  int v92; // [esp+58h] [ebp-18h]

  v3 = winw;
  v5 = *a1;
  v6 = 0;
  v58 = *a1;
  v61 = (char *)&shade_palette + 256 * a3;
  v7 = a1[1];
  v90 = 1;
  v62 = v7;
  v57 = v7;
  while ((__int16)v90 < a2) {
    v8 = a1[2 * (__int16)v90];
    v7 = a1[2 * (__int16)v90 + 1];
    if (v8 <= v58) {
      if (v8 < v5)
        v5 = a1[2 * (__int16)v90];
    } else {
      v58 = a1[2 * (__int16)v90];
    }
    if (v7 <= v57) {
      if (v7 < v62) {
        v6 = v90;
        v62 = a1[2 * (__int16)v90 + 1];
      }
    } else {
      v57 = a1[2 * (__int16)v90 + 1];
    }
    ++v90;
  }
  if (v58 < 0)
    goto LABEL_177;
  if (v57 < 0)
    goto LABEL_177;
  if (v5 >= winw)
    goto LABEL_177;
  LOWORD(v7) = v62;
  if (v62 >= winh)
    goto LABEL_177;
  v9 = &a1[2 * (__int16)v6];
  v10 = v9[1];
  v11 = v6;
  if (v10 >= 0) {
    HIWORD(v87) = *(_WORD *)v9;
    HIWORD(v89) = *(_WORD *)v9;
    LOWORD(v72) = 0;
    LOWORD(v87) = 0;
    LOWORD(v80) = 0;
    LOWORD(v89) = 0;
    while (1) {
      if ((__int16)++v6 == a2)
        v6 = 0;
      v7 = 8 * (__int16)v6;
      v24 = (_WORD *)((char *)a1 + v7);
      LOWORD(v7) = *(_WORD *)((char *)a1 + v7 + 4) - v10;
      v92 = v7;
      if ((_WORD)v7)
        break;
      if ((_WORD)v6 == (_WORD)v11)
        goto LABEL_177;
      HIWORD(v89) = *v24;
    }
    HIWORD(v80) = *v24 - HIWORD(v89);
    v25 = v80 / (__int16)v7;
    v26 = v80 % (__int16)v92;
    v79 = v25;
    if (v25 < 0)
      v89 += v25;
    while (1) {
      if ((__int16)--v11 == -1)
        v11 = a2 - 1;
      v7 = (int)&a1[2 * (__int16)v11];
      LOWORD(v26) = *(_WORD *)(v7 + 4) - v10;
      v91 = v26;
      if ((_WORD)v26)
        break;
      if ((_WORD)v6 == (_WORD)v11)
        goto LABEL_177;
      HIWORD(v87) = *(_WORD *)v7;
    }
    HIWORD(v72) = *(_WORD *)v7 - HIWORD(v87);
    v27 = v72 / (__int16)v26;
    v71 = v27;
    if (v27 > 0)
      v87 += v27;
  } else {
    v67 = v9[1];
    v68 = v67;
    LOWORD(v86) = 0;
    LOWORD(v70) = 0;
    LOWORD(v88) = 0;
    LOWORD(v78) = 0;
    do {
      v12 = a1[2 * (__int16)v6++];
      HIWORD(v88) = v12;
      if ((__int16)v6 == a2)
        v6 = 0;
      v13 = a1[2 * (__int16)v6 + 1];
      v14 = v68;
      v68 = v13;
    } while (v13 < 0);
    if (!v13) {
      do {
        v15 = a1[2 * (__int16)v6++];
        HIWORD(v88) = v15;
        if ((__int16)v6 == a2)
          v6 = 0;
        v7 = a1[2 * (__int16)v6 + 1];
        v14 = v68;
        v68 = v7;
      } while (!v7);
      if (v7 < 0)
        goto LABEL_177;
    }
    HIWORD(v78) = LOWORD(a1[2 * (__int16)v6]) - HIWORD(v88);
    v92 = v68;
    v16 = v78 / ((__int16)v68 - v14);
    v17 = v88 - v16 * v14;
    v79 = v16;
    v89 = v17;
    if (v16 < 0)
      v89 = v16 + v17;
    do {
      v18 = a1[2 * (__int16)v11--];
      HIWORD(v86) = v18;
      if ((__int16)v11 == -1)
        v11 = a2 - 1;
      v19 = a1[2 * (__int16)v11 + 1];
      v20 = v67;
      v67 = v19;
    } while (v19 < 0);
    if (!v19) {
      do {
        v21 = a1[2 * (__int16)v11--];
        HIWORD(v86) = v21;
        if ((__int16)v11 == -1)
          v11 = a2 - 1;
        v7 = a1[2 * (__int16)v11 + 1];
        v20 = v67;
        v67 = v7;
      } while (!v7);
      if (v7 < 0)
        goto LABEL_177;
    }
    HIWORD(v70) = LOWORD(a1[2 * (__int16)v11]) - HIWORD(v86);
    v91 = v67;
    v22 = v70 / ((__int16)v67 - v20);
    v23 = v86 - v22 * v20;
    v71 = v22;
    v87 = v23;
    if (v22 > 0)
      v87 = v22 + v23;
    v10 = 0;
  }
  while (SHIWORD(v89) >= winw || v87 < 0 || v89 > v87) {
    v89 += v79;
    ++v10;
    v28 = v71 + v87;
    HIWORD(v7) = HIWORD(v92);
    v87 += v71;
    LOWORD(v7) = v92 - 1;
    v29 = (_WORD)v92 == 1;
    v92 = v7;
    if (v29) {
      while ((_WORD)v6 != (_WORD)v11) {
        HIWORD(v30) = HIWORD(a2);
        v31 = a1[2 * (__int16)v6++];
        HIWORD(v89) = v31;
        if ((__int16)v6 == a2)
          v6 = 0;
        v7 = (int)&a1[2 * (__int16)v6];
        LOWORD(v30) = *(_WORD *)(v7 + 4);
        v92 = v30 - v10;
        if ((__int16)(v30 - v10) > 0) {
          HIWORD(v81) = *(_WORD *)v7 - HIWORD(v89);
          LOWORD(v89) = 0;
          LOWORD(v81) = 0;
          v32 = v81 / (__int16)v92;
          v28 = v81 % (__int16)v92;
          v79 = v32;
          if (v32 < 0)
            v89 += v32;
          goto LABEL_64;
        }
      }
      goto LABEL_177;
    }
  LABEL_64:
    HIWORD(v7) = HIWORD(v91);
    LOWORD(v7) = v91 - 1;
    v29 = (_WORD)v91 == 1;
    v91 = v7;
    if (v29) {
      while ((_WORD)v6 != (_WORD)v11) {
        v33 = a1[2 * (__int16)v11--];
        HIWORD(v87) = v33;
        if ((__int16)v11 == -1)
          v11 = a2 - 1;
        v7 = (int)&a1[2 * (__int16)v11];
        LOWORD(v28) = *(_WORD *)(v7 + 4);
        v28 -= v10;
        v91 = v28;
        if ((__int16)v28 > 0) {
          HIWORD(v73) = *(_WORD *)v7 - HIWORD(v87);
          LOWORD(v87) = 0;
          LOWORD(v73) = 0;
          v7 = v73 / (__int16)v28;
          v71 = v7;
          if (v7 > 0)
            v87 += v7;
          goto LABEL_71;
        }
      }
      goto LABEL_177;
    }
  LABEL_71:
    if (v10 >= winh)
      goto LABEL_177;
  }
  do {
    if (SHIWORD(v89) >= v3) {
      LOWORD(v7) = HIWORD(v89);
      if (SHIWORD(v89) >= (int)v3)
        goto LABEL_177;
      LOWORD(v7) = HIWORD(v87);
      if (SHIWORD(v87) < v3)
        goto LABEL_107;
    LABEL_158:
      if (v87 < 0)
        goto LABEL_177;
      while (1) {
      LABEL_159:
        v66 = (_BYTE *)(v3 * v10 + scrptr);
        for (i = 0; (int)v3 > i; ++i) {
          *v66 = v61[(unsigned __int8)*v66];
          ++v66;
        }
        v89 += v79;
        ++v10;
        v51 = v71 + v87;
        HIWORD(v7) = HIWORD(v92);
        v87 += v71;
        LOWORD(v7) = v92 - 1;
        v29 = (_WORD)v92 == 1;
        v92 = v7;
        if (v29) {
          while ((_WORD)v6 != (_WORD)v11) {
            HIWORD(v52) = HIWORD(a2);
            v53 = a1[2 * (__int16)v6++];
            HIWORD(v89) = v53;
            if ((__int16)v6 == a2)
              v6 = 0;
            v7 = (int)&a1[2 * (__int16)v6];
            LOWORD(v52) = *(_WORD *)(v7 + 4);
            v92 = v52 - v10;
            if ((__int16)(v52 - v10) > 0) {
              HIWORD(v85) = *(_WORD *)v7 - HIWORD(v89);
              LOWORD(v89) = 0;
              LOWORD(v85) = 0;
              v54 = v85 / (__int16)v92;
              v51 = v85 % (__int16)v92;
              v79 = v54;
              if (v54 < 0)
                v89 += v54;
              goto LABEL_169;
            }
          }
          goto LABEL_177;
        }
      LABEL_169:
        HIWORD(v7) = HIWORD(v91);
        LOWORD(v7) = v91 - 1;
        v29 = (_WORD)v91 == 1;
        v91 = v7;
        if (v29)
          break;
      LABEL_176:
        if (v10 >= winh)
          goto LABEL_177;
        if (SHIWORD(v89) < v3) {
          LOWORD(v7) = HIWORD(v89);
          if (SHIWORD(v89) >= (int)v3)
            goto LABEL_177;
          LOWORD(v7) = HIWORD(v87);
          if (SHIWORD(v87) >= v3)
            goto LABEL_133;
        LABEL_79:
          if (v87 < 0)
            goto LABEL_177;
          goto LABEL_80;
        }
        LOWORD(v7) = HIWORD(v87);
        if (SHIWORD(v87) < v3)
          goto LABEL_106;
      }
      while ((_WORD)v6 != (_WORD)v11) {
        v55 = a1[2 * (__int16)v11--];
        HIWORD(v87) = v55;
        if ((__int16)v11 == -1)
          v11 = a2 - 1;
        v7 = (int)&a1[2 * (__int16)v11];
        LOWORD(v51) = *(_WORD *)(v7 + 4);
        v51 -= v10;
        v91 = v51;
        if ((__int16)v51 > 0) {
          HIWORD(v77) = *(_WORD *)v7 - HIWORD(v87);
          LOWORD(v87) = 0;
          LOWORD(v77) = 0;
          v7 = v77 / (__int16)v51;
          v71 = v7;
          if (v7 > 0)
            v87 += v7;
          goto LABEL_176;
        }
      }
    LABEL_177:
      winw = v3;
      return v7;
    }
    for (LOWORD(v7) = HIWORD(v87); SHIWORD(v87) >= v3; LOWORD(v7) = HIWORD(v87)) {
      if (v87 < 0)
        goto LABEL_177;
      while (1) {
      LABEL_133:
        v64 = (_BYTE *)(v3 * v10 + scrptr + SHIWORD(v89));
        for (j = 0; (int)(v3 - SHIWORD(v89)) > j; ++j) {
          *v64 = v61[(unsigned __int8)*v64];
          ++v64;
        }
        v89 += v79;
        ++v10;
        v46 = v71 + v87;
        HIWORD(v7) = HIWORD(v92);
        v87 += v71;
        LOWORD(v7) = v92 - 1;
        v29 = (_WORD)v92 == 1;
        v92 = v7;
        if (v29) {
          while ((_WORD)v6 != (_WORD)v11) {
            HIWORD(v47) = HIWORD(a2);
            v48 = a1[2 * (__int16)v6++];
            HIWORD(v89) = v48;
            if ((__int16)v6 == a2)
              v6 = 0;
            v7 = (int)&a1[2 * (__int16)v6];
            LOWORD(v47) = *(_WORD *)(v7 + 4);
            v92 = v47 - v10;
            if ((__int16)(v47 - v10) > 0) {
              HIWORD(v84) = *(_WORD *)v7 - HIWORD(v89);
              LOWORD(v89) = 0;
              LOWORD(v84) = 0;
              v49 = v84 / (__int16)v92;
              v46 = v84 % (__int16)v92;
              v79 = v49;
              if (v49 < 0)
                v89 += v49;
              goto LABEL_143;
            }
          }
          goto LABEL_177;
        }
      LABEL_143:
        HIWORD(v7) = HIWORD(v91);
        LOWORD(v7) = v91 - 1;
        v29 = (_WORD)v91 == 1;
        v91 = v7;
        if (v29) {
          while ((_WORD)v6 != (_WORD)v11) {
            v50 = a1[2 * (__int16)v11--];
            HIWORD(v87) = v50;
            if ((__int16)v11 == -1)
              v11 = a2 - 1;
            v7 = (int)&a1[2 * (__int16)v11];
            LOWORD(v46) = *(_WORD *)(v7 + 4);
            v46 -= v10;
            v91 = v46;
            if ((__int16)v46 > 0) {
              HIWORD(v76) = *(_WORD *)v7 - HIWORD(v87);
              LOWORD(v87) = 0;
              LOWORD(v76) = 0;
              v7 = v76 / (__int16)v46;
              v71 = v7;
              if (v7 > 0)
                v87 += v7;
              goto LABEL_150;
            }
          }
          goto LABEL_177;
        }
      LABEL_150:
        if (v10 >= winh) {
          winw = v3;
          return v7;
        }
        if (SHIWORD(v89) >= v3)
          break;
        LOWORD(v7) = HIWORD(v87);
        if (SHIWORD(v87) < v3)
          goto LABEL_79;
      }
      LOWORD(v7) = HIWORD(v89);
      if (SHIWORD(v89) >= (int)v3)
        goto LABEL_177;
      LOWORD(v7) = HIWORD(v87);
      if (SHIWORD(v87) >= v3)
        goto LABEL_159;
    LABEL_106:
      if (v87 < 0)
        goto LABEL_177;
      while (1) {
      LABEL_107:
        v65 = (_BYTE *)(scrptr + v3 * v10);
        for (k = 0; SHIWORD(v87) + 1 > k; ++k) {
          *v65 = v61[(unsigned __int8)*v65];
          ++v65;
        }
        LOWORD(v7) = v71;
        v89 += v79;
        v87 += v71;
        HIWORD(v40) = HIWORD(v92);
        ++v10;
        LOWORD(v40) = v92 - 1;
        v29 = (_WORD)v92 == 1;
        v92 = v40;
        if (v29) {
          while ((_WORD)v6 != (_WORD)v11) {
            HIWORD(v41) = HIWORD(a2);
            v42 = a1[2 * (__int16)v6++];
            HIWORD(v89) = v42;
            if ((__int16)v6 == a2)
              v6 = 0;
            v7 = (int)&a1[2 * (__int16)v6];
            LOWORD(v41) = *(_WORD *)(v7 + 4);
            v92 = v41 - v10;
            if ((__int16)(v41 - v10) > 0) {
              HIWORD(v83) = *(_WORD *)v7 - HIWORD(v89);
              LOWORD(v89) = 0;
              LOWORD(v83) = 0;
              v43 = v83 / (__int16)v92;
              v40 = v83 % (__int16)v92;
              v79 = v43;
              if (v43 < 0)
                v89 += v43;
              goto LABEL_117;
            }
          }
          goto LABEL_177;
        }
      LABEL_117:
        HIWORD(v7) = HIWORD(v91);
        LOWORD(v7) = v91 - 1;
        v29 = (_WORD)v91 == 1;
        v91 = v7;
        if (v29) {
          while ((_WORD)v6 != (_WORD)v11) {
            v44 = a1[2 * (__int16)v11--];
            HIWORD(v87) = v44;
            if ((__int16)v11 == -1)
              v11 = a2 - 1;
            v7 = (int)&a1[2 * (__int16)v11];
            LOWORD(v40) = *(_WORD *)(v7 + 4);
            v40 -= v10;
            v91 = v40;
            if ((__int16)v40 > 0) {
              HIWORD(v75) = *(_WORD *)v7 - HIWORD(v87);
              LOWORD(v87) = 0;
              LOWORD(v75) = 0;
              v7 = v75 / (__int16)v40;
              v71 = v7;
              if (v7 > 0)
                v87 += v7;
              goto LABEL_124;
            }
          }
          goto LABEL_177;
        }
      LABEL_124:
        if (v10 >= winh) {
          winw = v3;
          return v7;
        }
        if (SHIWORD(v89) < v3)
          break;
        LOWORD(v7) = HIWORD(v87);
        if (SHIWORD(v87) >= v3)
          goto LABEL_158;
      }
      LOWORD(v7) = HIWORD(v89);
      if (SHIWORD(v89) >= (int)v3)
        goto LABEL_177;
    }
  LABEL_80:
    LOWORD(v7) = HIWORD(v87) - HIWORD(v89) + 1;
    if ((v7 & 0x8000u) != 0)
      goto LABEL_177;
    v63 = (_BYTE *)(v3 * v10 + SHIWORD(v89) + scrptr);
    for (m = 0; (__int16)v7 > m; ++m) {
      *v63 = v61[(unsigned __int8)*v63];
      ++v63;
    }
    LOWORD(v7) = v71;
    v89 += v79;
    v87 += v71;
    HIWORD(v34) = HIWORD(v92);
    ++v10;
    LOWORD(v34) = v92 - 1;
    v29 = (_WORD)v92 == 1;
    v92 = v34;
    if (v29) {
      while ((_WORD)v6 != (_WORD)v11) {
        HIWORD(v35) = HIWORD(a2);
        v36 = a1[2 * (__int16)v6++];
        HIWORD(v89) = v36;
        if ((__int16)v6 == a2)
          v6 = 0;
        v7 = (int)&a1[2 * (__int16)v6];
        LOWORD(v35) = *(_WORD *)(v7 + 4);
        v92 = v35 - v10;
        if ((__int16)(v35 - v10) > 0) {
          HIWORD(v82) = *(_WORD *)v7 - HIWORD(v89);
          LOWORD(v89) = 0;
          LOWORD(v82) = 0;
          v37 = v82 / (__int16)v92;
          v34 = v82 % (__int16)v92;
          v79 = v37;
          if (v37 < 0)
            v89 += v37;
          goto LABEL_91;
        }
      }
      goto LABEL_177;
    }
  LABEL_91:
    HIWORD(v7) = HIWORD(v91);
    LOWORD(v7) = v91 - 1;
    v29 = (_WORD)v91 == 1;
    v91 = v7;
    if (v29) {
      while ((_WORD)v6 != (_WORD)v11) {
        v38 = a1[2 * (__int16)v11--];
        HIWORD(v87) = v38;
        if ((__int16)v11 == -1)
          v11 = a2 - 1;
        v7 = (int)&a1[2 * (__int16)v11];
        LOWORD(v34) = *(_WORD *)(v7 + 4);
        v34 -= v10;
        v91 = v34;
        if ((__int16)v34 > 0) {
          HIWORD(v74) = *(_WORD *)v7 - HIWORD(v87);
          LOWORD(v87) = 0;
          LOWORD(v74) = 0;
          v7 = v74 / (__int16)v34;
          v71 = v7;
          if (v7 > 0)
            v87 += v7;
          goto LABEL_98;
        }
      }
      goto LABEL_177;
    }
  LABEL_98:
    ;
  } while (v10 < winh);
  winw = v3;
  return v7;*/
}

//-------------------------------------------------------------------------------------------------

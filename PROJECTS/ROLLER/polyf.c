#include "polyf.h"
#include "3d.h"
#include "polytex.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//-------------------------------------------------------------------------------------------------

int twpoly(void *a1, int16 a2)
{
  return 0; /*
  __int16 v3; // ax
  __int16 v4; // di
  __int16 v5; // si
  __int16 v6; // bx
  int v7; // eax
  __int16 v8; // fps
  _BOOL1 v9; // c0
  char v10; // c2
  _BOOL1 v11; // c3
  double v12; // st6
  double v13; // st7
  int v14; // eax
  int v15; // ebp
  int v16; // edx
  _WORD *v17; // eax
  int v18; // ebx
  double v19; // st6
  double v20; // st7
  int v21; // eax
  int v23; // eax
  int v24; // ebp
  __int16 v25; // fps
  _BOOL1 v26; // c0
  char v27; // c2
  _BOOL1 v28; // c3
  double v29; // st7
  int v30; // eax
  int v31; // ebp
  double v32; // st7
  int v33; // eax
  int v34; // [esp+0h] [ebp-68h]
  int v35; // [esp+4h] [ebp-64h]
  int v36; // [esp+8h] [ebp-60h]
  int v37; // [esp+8h] [ebp-60h]
  int v38; // [esp+8h] [ebp-60h]
  int v39; // [esp+Ch] [ebp-5Ch]
  int v40; // [esp+Ch] [ebp-5Ch]
  int v41; // [esp+Ch] [ebp-5Ch]
  int v42; // [esp+10h] [ebp-58h]
  int v43; // [esp+14h] [ebp-54h]
  int v44; // [esp+20h] [ebp-48h]
  float v45; // [esp+24h] [ebp-44h]
  float v46; // [esp+28h] [ebp-40h]
  float v47; // [esp+2Ch] [ebp-3Ch]
  float v48; // [esp+30h] [ebp-38h]
  int v49; // [esp+34h] [ebp-34h]
  __int16 v50; // [esp+38h] [ebp-30h]
  __int16 v51; // [esp+3Ch] [ebp-2Ch]
  __int16 v52; // [esp+40h] [ebp-28h]
  __int16 v53; // [esp+44h] [ebp-24h]
  __int16 v54; // [esp+48h] [ebp-20h]
  __int16 v55; // [esp+4Ch] [ebp-1Ch]

  v3 = a1[4] - *a1;
  v4 = a1[8] - *a1;
  v55 = a1[12] - a1[8];
  v52 = v4 + v55;
  v54 = v3 - v4;
  v50 = a1[6] - a1[2];
  v5 = a1[10] - a1[2];
  v6 = a1[14] - a1[10];
  v51 = v5 + v6;
  v53 = v50 - v5;
  v49 = 0;
  v44 = 0;
  v46 = (float)(v6 * v3 - v50 * v55);
  if ((LODWORD(v46) & 0x7FFFFFFF) != 0) {
    v7 = v50 * v4 - v5 * v3;
    v49 = v7;
    v48 = (double)v7 / v46;
    if (v48 > 0.0) {
      v9 = v48 > 1.0;
      v10 = 0;
      v11 = 1.0 == v48;
      LOWORD(v7) = v8;
      if (v48 < 1.0) {
        v42 = *(_DWORD *)a1;
        v43 = *((_DWORD *)a1 + 1);
        if (v49 <= 0) {
          *(_DWORD *)a1 = *((_DWORD *)a1 + 4);
          *((_DWORD *)a1 + 1) = *((_DWORD *)a1 + 5);
          v19 = (double)v55 * v48 + (double)*((int *)a1 + 4);
          _CHP(v7, a2);
          *((_DWORD *)a1 + 4) = (int)v19;
          v20 = v48 * (double)v6 + (double)*((int *)a1 + 5);
          _CHP(v21, a2);
          *((_DWORD *)a1 + 5) = (int)v20;
          poly(a1, 3, a2);
          *(_DWORD *)a1 = *((_DWORD *)a1 + 6);
          *((_DWORD *)a1 + 1) = *((_DWORD *)a1 + 7);
          *((_DWORD *)a1 + 2) = v42;
          *((_DWORD *)a1 + 3) = v43;
          return poly(a1, 3, a2);
        }
        *(_DWORD *)a1 = *((_DWORD *)a1 + 2);
        *((_DWORD *)a1 + 1) = *((_DWORD *)a1 + 3);
        *((_DWORD *)a1 + 2) = *((_DWORD *)a1 + 4);
        *((_DWORD *)a1 + 3) = *((_DWORD *)a1 + 5);
        v12 = (double)v55 * v48 + (double)*((int *)a1 + 4);
        _CHP(v7, a2);
        *((_DWORD *)a1 + 4) = (int)v12;
        v13 = v48 * (double)v6 + (double)*((int *)a1 + 5);
        _CHP(v14, a2);
        *((_DWORD *)a1 + 5) = (int)v13;
        v15 = a2;
        poly(a1, 3, a2);
        *(_DWORD *)a1 = *((_DWORD *)a1 + 6);
        *((_DWORD *)a1 + 1) = *((_DWORD *)a1 + 7);
        v16 = 3;
        v17 = a1;
        v18 = v15;
        *((_DWORD *)a1 + 2) = v42;
        *((_DWORD *)a1 + 3) = v43;
        return poly(v17, v16, v18);
      }
    }
  }
  v23 = v53 * v52 - v51 * v54;
  v45 = (float)v23;
  if ((LODWORD(v45) & 0x7FFFFFFF) == 0
    || (v24 = v4 * v51 - v5 * v52, v44 = v24, v47 = (double)v24 / v45, v47 <= 0.0)
    || (v26 = v47 > 1.0, v27 = 0, v28 = 1.0 == v47, LOWORD(v23) = v25, v47 >= 1.0)) {
    if (v49 < 0 || v44 > 0) {
      v34 = *((_DWORD *)a1 + 2);
      v35 = *((_DWORD *)a1 + 3);
      *((_DWORD *)a1 + 2) = *((_DWORD *)a1 + 6);
      *((_DWORD *)a1 + 3) = *((_DWORD *)a1 + 7);
      *((_DWORD *)a1 + 6) = v34;
      *((_DWORD *)a1 + 7) = v35;
    }
    v18 = a2;
    v17 = a1;
    v16 = 4;
    return poly(v17, v16, v18);
  }
  if (v24 <= 0) {
    v37 = *(_DWORD *)a1;
    v40 = *((_DWORD *)a1 + 1);
    *(_DWORD *)a1 = *((_DWORD *)a1 + 2);
    *((_DWORD *)a1 + 1) = *((_DWORD *)a1 + 3);
    *((_DWORD *)a1 + 2) = v37;
    *((_DWORD *)a1 + 3) = v40;
    v38 = *((_DWORD *)a1 + 4);
    v41 = *((_DWORD *)a1 + 5);
    _CHP(v23, a2);
    *((_DWORD *)a1 + 4) = (int)((double)v54 * v47 + (double)v38);
    v32 = v47 * (double)v53 + (double)*((int *)a1 + 5);
    _CHP(v33, a2);
    *((_DWORD *)a1 + 5) = (int)v32;
    v31 = a2;
    poly(a1, 3, a2);
    *((_DWORD *)a1 + 2) = *((_DWORD *)a1 + 6);
    *((_DWORD *)a1 + 3) = *((_DWORD *)a1 + 7);
    *(_DWORD *)a1 = v38;
    *((_DWORD *)a1 + 1) = v41;
  } else {
    v36 = *((_DWORD *)a1 + 4);
    v39 = *((_DWORD *)a1 + 5);
    _CHP(v23, a2);
    *((_DWORD *)a1 + 4) = (int)((double)v54 * v47 + (double)v36);
    v29 = v47 * (double)v53 + (double)*((int *)a1 + 5);
    _CHP(v30, a2);
    *((_DWORD *)a1 + 5) = (int)v29;
    v31 = a2;
    poly(a1, 3, a2);
    *(_DWORD *)a1 = *((_DWORD *)a1 + 6);
    *((_DWORD *)a1 + 1) = *((_DWORD *)a1 + 7);
    *((_DWORD *)a1 + 2) = v36;
    *((_DWORD *)a1 + 3) = v39;
  }
  return poly(a1, 3, v31);*/
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

void poly(tPoint *vertices, int iVertexCount, int16 nColor)
{
  int iWinWidth = winw;
  int iWinHeight = winh;
  uint8 *pScrBuf = scrptr;

  // Find bounding box and top vertex
  int iMinX = vertices[0].x;
  int iMaxX = vertices[0].x;
  int iMinY = vertices[0].y;
  int iMaxY = vertices[0].y;
  short nTopIdx = 0;

  for (short i = 1; i < iVertexCount; i++) {
    if (vertices[i].x > iMaxX) iMaxX = vertices[i].x;
    if (vertices[i].x < iMinX) iMinX = vertices[i].x;
    if (vertices[i].y > iMaxY) iMaxY = vertices[i].y;
    if (vertices[i].y < iMinY) {
      iMinY = vertices[i].y;
      nTopIdx = i;
    }
  }

  // Check if polygon is completely off-screen
  if (iMaxX < 0 || iMaxY < 0 || iMinX >= iWinWidth || iMinY >= iWinHeight) {
    return;
  }

  // Initialize edge tracking
  short nLeftIdx = nTopIdx;
  short nRightIdx = nTopIdx;
  short nCurrY = iMinY;

  // Left edge tracking
  int iLeftX = vertices[nTopIdx].x;
  int iLeftDx = 0;
  int iLeftErr = 0;
  int iLeftRemain = 0;

  // Right edge tracking
  int iRightX = vertices[nTopIdx].x;
  int iRightDx = 0;
  int iRightErr = 0;
  int iRightRemain = 0;

  // Initialize edges
  // Find first downward left edge
  short nNextLeft = (nLeftIdx + 1) % iVertexCount;
  while (vertices[nNextLeft].y == nCurrY) {
    nLeftIdx = nNextLeft;
    nNextLeft = (nLeftIdx + 1) % iVertexCount;
  }
  iLeftRemain = vertices[nNextLeft].y - nCurrY;
  iLeftDx = vertices[nNextLeft].x - vertices[nLeftIdx].x;
  if (iLeftRemain != 0) {
    iLeftErr = abs(iLeftDx) % abs(iLeftRemain);
    iLeftDx = iLeftDx / iLeftRemain;
  }

  // Find first downward right edge
  short nNextRight = (nRightIdx - 1 + iVertexCount) % iVertexCount;
  while (vertices[nNextRight].y == nCurrY) {
    nRightIdx = nNextRight;
    nNextRight = (nRightIdx - 1 + iVertexCount) % iVertexCount;
  }
  iRightRemain = vertices[nNextRight].y - nCurrY;
  iRightDx = vertices[nNextRight].x - vertices[nRightIdx].x;
  if (iRightRemain != 0) {
    iRightErr = abs(iRightDx) % abs(iRightRemain);
    iRightDx = iRightDx / iRightRemain;
  }

  // Main scanline loop
  while (nCurrY < iWinHeight) {
      // Draw horizontal line between edges
    if (iLeftX < iWinWidth && iRightX > 0 && iLeftX < iRightX) {
      int iStartX = max(iLeftX, 0);
      int iEndX = min(iRightX, iWinWidth);
      if (iStartX < iEndX) {
        uint8 *pDest = pScrBuf + nCurrY * iWinWidth + iStartX;
        memset(pDest, nColor, iEndX - iStartX);
      }
    }

    // Update left edge
    iLeftErr += iLeftDx;
    while (iLeftErr >= 1) {
      iLeftX++;
      iLeftErr--;
    }
    while (iLeftErr <= -1) {
      iLeftX--;
      iLeftErr++;
    }

    // Update right edge
    iRightErr += iRightDx;
    while (iRightErr >= 1) {
      iRightX++;
      iRightErr--;
    }
    while (iRightErr <= -1) {
      iRightX--;
      iRightErr++;
    }

    // Move to next scanline
    nCurrY++;
    iLeftRemain--;
    iRightRemain--;

    // Switch to next left edge if current finished
    if (iLeftRemain == 0) {
      nLeftIdx = nNextLeft;
      nNextLeft = (nLeftIdx + 1) % iVertexCount;

      // Skip horizontal edges
      while (vertices[nNextLeft].y == nCurrY) {
        nLeftIdx = nNextLeft;
        nNextLeft = (nLeftIdx + 1) % iVertexCount;
      }

      iLeftRemain = vertices[nNextLeft].y - nCurrY;
      iLeftDx = vertices[nNextLeft].x - vertices[nLeftIdx].x;
      if (iLeftRemain != 0) {
        iLeftErr = abs(iLeftDx) % abs(iLeftRemain);
        iLeftDx = iLeftDx / iLeftRemain;
      }
    }

    // Switch to next right edge if current finished
    if (iRightRemain == 0) {
      nRightIdx = nNextRight;
      nNextRight = (nRightIdx - 1 + iVertexCount) % iVertexCount;

      // Skip horizontal edges
      while (vertices[nNextRight].y == nCurrY) {
        nRightIdx = nNextRight;
        nNextRight = (nRightIdx - 1 + iVertexCount) % iVertexCount;
      }

      iRightRemain = vertices[nNextRight].y - nCurrY;
      iRightDx = vertices[nNextRight].x - vertices[nRightIdx].x;
      if (iRightRemain != 0) {
        iRightErr = abs(iRightDx) % abs(iRightRemain);
        iRightDx = iRightDx / iRightRemain;
      }
    }

    // Check if polygon is complete
    if (nLeftIdx == nRightIdx) break;
  }
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

#ifdef ENABLE_PSEUDO
//-------------------------------------------------------------------------------------------------

int __fastcall twpoly(_WORD *a1, __int16 a2)
{
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
  return poly(a1, 3, v31);
}

//-------------------------------------------------------------------------------------------------

__int16 __fastcall POLYFLAT(int a1, _DWORD *a2)
{
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
  return (__int16)v3;
}

//-------------------------------------------------------------------------------------------------

__int16 __fastcall poly(int *a1, int a2, __int16 a3)
{
  unsigned int v3; // ebp
  int v5; // edi
  int v6; // ecx
  int v7; // ebx
  int v8; // eax
  int *v9; // eax
  int v10; // ecx
  int v11; // ebx
  __int16 v12; // ax
  int v13; // eax
  int v14; // ecx
  __int16 v15; // ax
  int v16; // ecx
  int v17; // ebx
  int v18; // edx
  int v19; // edx
  __int16 v20; // ebx^2
  int v21; // edx
  int *v22; // eax
  int v23; // ebx
  int v24; // edx
  int v25; // edx
  int v26; // ebx
  _BOOL1 v27; // zf
  __int16 v28; // ax
  int v29; // ebx
  int v30; // ebx
  __int16 v31; // bx
  __int16 v32; // ebx^2
  int v33; // edx
  __int16 v34; // ax
  int v35; // edx
  int v36; // edx
  int v37; // edx
  unsigned int v38; // ebx
  int v39; // edx
  int v40; // eax
  int v41; // edx
  __int16 v42; // ebx^2
  int v43; // edx
  __int16 v44; // ax
  int v45; // edx
  int v46; // edx
  int v47; // edx
  int v48; // edx
  int v49; // eax
  int v50; // ecx
  int v51; // eax
  int v52; // edx
  __int16 v53; // ebx^2
  int v54; // edx
  __int16 v55; // ax
  int v56; // edx
  int v57; // edx
  int v58; // edx
  int v59; // edx
  __int16 v60; // ebx^2
  int v61; // edx
  __int16 v62; // ax
  int v63; // edx
  int v64; // edx
  int v65; // edx
  int v67; // [esp+0h] [ebp-68h]
  int v68; // [esp+0h] [ebp-68h]
  int v69; // [esp+4h] [ebp-64h]
  int v70; // [esp+4h] [ebp-64h]
  int v71; // [esp+4h] [ebp-64h]
  int v72; // [esp+4h] [ebp-64h]
  int v73; // [esp+8h] [ebp-60h]
  int v74; // [esp+Ch] [ebp-5Ch]
  int v75; // [esp+14h] [ebp-54h]
  int v76; // [esp+18h] [ebp-50h]
  int v77; // [esp+1Ch] [ebp-4Ch]
  int v78; // [esp+20h] [ebp-48h]
  int v79; // [esp+24h] [ebp-44h]
  int v80; // [esp+28h] [ebp-40h]
  int v81; // [esp+2Ch] [ebp-3Ch]
  int v82; // [esp+30h] [ebp-38h]
  int v83; // [esp+30h] [ebp-38h]
  int v84; // [esp+30h] [ebp-38h]
  int v85; // [esp+30h] [ebp-38h]
  int v86; // [esp+30h] [ebp-38h]
  int v87; // [esp+30h] [ebp-38h]
  int v88; // [esp+30h] [ebp-38h]
  int v89; // [esp+30h] [ebp-38h]
  int v90; // [esp+34h] [ebp-34h]
  int v91; // [esp+34h] [ebp-34h]
  int v92; // [esp+34h] [ebp-34h]
  int v93; // [esp+34h] [ebp-34h]
  int v94; // [esp+34h] [ebp-34h]
  int v95; // [esp+34h] [ebp-34h]
  int v96; // [esp+34h] [ebp-34h]
  int v97; // [esp+34h] [ebp-34h]
  int v98; // [esp+38h] [ebp-30h]
  int v99; // [esp+38h] [ebp-30h]
  int v100; // [esp+3Ch] [ebp-2Ch]
  int v101; // [esp+3Ch] [ebp-2Ch]
  int v102; // [esp+40h] [ebp-28h]
  int v103; // [esp+44h] [ebp-24h]
  int v105; // [esp+4Ch] [ebp-1Ch]
  int v106; // [esp+50h] [ebp-18h]

  v3 = winw;
  v5 = 0;
  v80 = *a1;
  v77 = *a1;
  v103 = 1;
  v79 = a1[1];
  v78 = v79;
  while (1) {
    LOWORD(v8) = v103;
    if ((__int16)v103 >= (__int16)a2)
      break;
    v6 = a1[2 * (__int16)v103];
    v7 = a1[2 * (__int16)v103 + 1];
    if (v6 <= v77) {
      if (v6 < v80)
        v80 = a1[2 * (__int16)v103];
    } else {
      v77 = a1[2 * (__int16)v103];
    }
    if (v7 <= v78) {
      if (v7 < v79) {
        v5 = v103;
        v79 = a1[2 * (__int16)v103 + 1];
      }
    } else {
      v78 = a1[2 * (__int16)v103 + 1];
    }
    ++v103;
  }
  if (v77 < 0)
    goto LABEL_257;
  if (v78 < 0)
    goto LABEL_257;
  if (winw <= v80)
    goto LABEL_257;
  LOWORD(v8) = v79;
  if (v79 >= winh)
    goto LABEL_257;
  v9 = &a1[2 * (__int16)v5];
  v10 = v9[1];
  v102 = v5;
  if (v10 >= 0) {
    HIWORD(v99) = *(_WORD *)v9;
    HIWORD(v101) = *(_WORD *)v9;
    LOWORD(v99) = -1;
    LOWORD(v101) = 0;
    LOWORD(v92) = 0;
    LOWORD(v84) = 0;
    while (1) {
      HIWORD(v19) = HIWORD(a2);
      ++v5;
      v20 = HIWORD(v101);
      if ((_WORD)v5 == (_WORD)a2)
        v5 ^= a2;
      v8 = (int)&a1[2 * (__int16)v5];
      LOWORD(v19) = *(_WORD *)(v8 + 4) - v10;
      v106 = v19;
      if ((_WORD)v19)
        break;
      if ((_WORD)v5 == (_WORD)v102)
        goto LABEL_119;
      HIWORD(v101) = *(_WORD *)v8;
    }
    HIWORD(v84) = *(_WORD *)v8 - HIWORD(v101);
    if (v84 >= 0) {
      ++HIWORD(v84);
      v83 = v84 / ((__int16)v19 + 1);
    } else {
      --HIWORD(v84);
      v68 = (__int16)v19 + 1;
      v101 += v84 / v68;
      v83 = v84 / v68;
      ++HIWORD(v101);
    }
    while (1) {
      v21 = --v102;
      if ((__int16)v102 == -1)
        v102 = a2 - 1;
      v22 = &a1[2 * (__int16)v102];
      LOWORD(v21) = *((_WORD *)v22 + 2) - v10;
      v105 = v21;
      if ((_WORD)v21)
        break;
      if ((_WORD)v5 == (_WORD)v102) {
        LOWORD(v8) = -1;
        HIWORD(v101) = v20;
        goto LABEL_119;
      }
      HIWORD(v99) = *(_WORD *)v22;
    }
    HIWORD(v92) = *(_WORD *)v22 - HIWORD(v99);
    if (v92 <= 0) {
      --HIWORD(v92);
      v91 = v92 / ((__int16)v21 + 1);
      ++HIWORD(v99);
    } else {
      ++HIWORD(v92);
      v23 = (__int16)v21 + 1;
      v24 = v92 / v23 + v99;
      v91 = v92 / v23;
      v99 = v24;
    }
  } else {
    v11 = v9[1];
    v81 = v11;
    LOWORD(v90) = 0;
    LOWORD(v82) = 0;
    LOWORD(v100) = 0;
    LOWORD(v98) = -1;
    do {
      v12 = a1[2 * (__int16)v5++];
      HIWORD(v100) = v12;
      if ((_WORD)v5 == (_WORD)a2)
        v5 ^= a2;
      v13 = a1[2 * (__int16)v5 + 1];
      v14 = v81;
      v81 = v13;
    } while (v13 < 0);
    if (!v13) {
      do {
        v15 = a1[2 * (__int16)v5++];
        HIWORD(v100) = v15;
        if ((_WORD)v5 == (_WORD)a2)
          v5 ^= a2;
        v8 = a1[2 * (__int16)v5 + 1];
        v14 = v81;
        v81 = v8;
      } while (!v8);
      if (v8 < 0)
        goto LABEL_257;
    }
    HIWORD(v82) = LOWORD(a1[2 * (__int16)v5]) - HIWORD(v100);
    v106 = v81;
    if (v82 >= 0) {
      ++HIWORD(v82);
      v83 = v82 / ((__int16)v81 - v14 + 1);
    } else {
      --HIWORD(v82);
      v67 = (__int16)v81 - v14 + 1;
      v100 += v82 / v67;
      v83 = v82 / v67;
      ++HIWORD(v100);
    }
    v101 = v100 - v83 * v14;
    do {
      HIWORD(v98) = a1[2 * (__int16)v102--];
      if ((__int16)v102 == -1)
        v102 = a2 - 1;
      v16 = v11;
      v11 = a1[2 * (__int16)v102 + 1];
    } while (v11 < 0);
    if (!v11) {
      do {
        HIWORD(v98) = a1[2 * (__int16)v102--];
        if ((__int16)v102 == -1)
          v102 = a2 - 1;
        LOWORD(v8) = v102;
        v16 = v11;
        v11 = a1[2 * (__int16)v102 + 1];
      } while (!v11);
      if (v11 < 0)
        goto LABEL_257;
    }
    HIWORD(v90) = LOWORD(a1[2 * (__int16)v102]) - HIWORD(v98);
    v105 = v11;
    if (v90 <= 0) {
      --HIWORD(v90);
      v91 = v90 / ((__int16)v11 - v16 + 1);
      ++HIWORD(v98);
    } else {
      ++HIWORD(v90);
      v17 = (__int16)v11 - v16 + 1;
      v18 = v90 / v17 + v98;
      v91 = v90 / v17;
      v98 = v18;
    }
    v99 = v98 - v91 * v16;
    v10 = 0;
  }
  while (SHIWORD(v101) >= winw || SHIWORD(v99) <= 0) {
    LOWORD(v8) = v83;
    v25 = v83 + v101;
    ++v10;
    v99 += v91;
    HIWORD(v26) = HIWORD(v106);
    v101 += v83;
    LOWORD(v26) = v106 - 1;
    v27 = (_WORD)v106 == 1;
    v106 = v26;
    if (v27) {
      while ((_WORD)v5 != (_WORD)v102) {
        v28 = a1[2 * (__int16)v5++];
        HIWORD(v101) = v28;
        if ((_WORD)v5 == (_WORD)a2)
          v5 ^= a2;
        v8 = (int)&a1[2 * (__int16)v5];
        LOWORD(v25) = *(_WORD *)(v8 + 4);
        v25 -= v10;
        v106 = v25;
        if ((__int16)v25 > 0) {
          HIWORD(v85) = *(_WORD *)v8 - HIWORD(v101);
          LOWORD(v85) = 0;
          LOWORD(v101) = 0;
          if (v85 >= 0) {
            ++HIWORD(v85);
            v30 = (__int16)v25 + 1;
            v25 = v85 % v30;
            v83 = v85 / v30;
          } else {
            --HIWORD(v85);
            v29 = (__int16)v25 + 1;
            v25 = v85 % v29;
            v101 += v85 / v29;
            v83 = v85 / v29;
            ++HIWORD(v101);
          }
          goto LABEL_72;
        }
        if ((v25 & 0x8000u) != 0)
          goto LABEL_257;
      }
      goto LABEL_257;
    }
  LABEL_72:
    HIWORD(v8) = HIWORD(v105);
    LOWORD(v8) = v105 - 1;
    v27 = (_WORD)v105 == 1;
    v105 = v8;
    if (v27) {
      while (1) {
        v31 = v102;
        if ((_WORD)v5 == (_WORD)v102)
          goto LABEL_257;
        HIWORD(v99) = a1[2 * (__int16)v102--];
        if ((__int16)(v31 - 1) == -1)
          v102 = a2 - 1;
        v8 = (int)&a1[2 * (__int16)v102];
        LOWORD(v25) = *(_WORD *)(v8 + 4);
        v25 -= v10;
        v105 = v25;
        if ((__int16)v25 > 0) {
          HIWORD(v93) = *(_WORD *)v8 - HIWORD(v99);
          LOWORD(v93) = 0;
          LOWORD(v99) = -1;
          if (v93 <= 0) {
            --HIWORD(v93);
            v8 = v93 / ((__int16)v25 + 1);
            v91 = v8;
            ++HIWORD(v99);
          } else {
            ++HIWORD(v93);
            v91 = v93 / ((__int16)v25 + 1);
            LOWORD(v8) = v91;
            v99 += v91;
          }
          break;
        }
        if ((v25 & 0x8000u) != 0)
          goto LABEL_257;
      }
    }
    if (v10 >= winh)
      goto LABEL_257;
  }
  while (1) {
    if (SHIWORD(v101) < v3) {
      LOWORD(v8) = HIWORD(v99);
      if (SHIWORD(v99) <= v3)
        goto LABEL_91;
      goto LABEL_181;
    }
    LOWORD(v8) = HIWORD(v101);
    if (SHIWORD(v101) >= (int)v3)
      goto LABEL_257;
    LOWORD(v8) = HIWORD(v99);
    if (SHIWORD(v99) > v3) {
    LABEL_222:
      if (SHIWORD(v99) > 0)
        goto LABEL_223;
      goto LABEL_257;
    }
    while (1) {
    LABEL_136:
      LOWORD(v8) = HIWORD(v99);
      if (SHIWORD(v99) > 0) {
        winw = v3;
        memset(v3 * v10 + scrptr, a3, SHIWORD(v99));
        v3 = winw;
      } else if (v99 < 0) {
        goto LABEL_257;
      }
      ++v10;
      v41 = v83 + v101;
      v101 = v41;
      HIWORD(v8) = HIWORD(v106);
      v99 += v91;
      v42 = HIWORD(v41);
      LOWORD(v8) = v106 - 1;
      v27 = (_WORD)v106 == 1;
      v106 = v8;
      if (v27) {
        if ((_WORD)v5 == (_WORD)v102) {
          HIWORD(v101) = HIWORD(v41);
        LABEL_165:
          if (v10 >= winh)
            goto LABEL_257;
          if (SHIWORD(v101) < v3) {
            LOWORD(v8) = HIWORD(v101);
            if (SHIWORD(v101) >= (int)v3)
              goto LABEL_257;
            LOWORD(v8) = HIWORD(v99);
            if (SHIWORD(v99) <= v3)
              goto LABEL_127;
            goto LABEL_214;
          }
          LOWORD(v8) = HIWORD(v99);
          if (SHIWORD(v99) <= v3) {
          LABEL_173:
            if (SHIWORD(v99) > 0) {
              v49 = v3 * v10;
              v39 = a3;
              v50 = scrptr;
              v38 = SHIWORD(v99);
              goto LABEL_255;
            }
            goto LABEL_257;
          }
        LABEL_253:
          if (SHIWORD(v99) <= 0)
            goto LABEL_257;
          goto LABEL_254;
        }
        while (1) {
          HIWORD(v43) = HIWORD(a2);
          v44 = a1[2 * (__int16)v5++];
          HIWORD(v101) = v44;
          if ((_WORD)v5 == (_WORD)a2)
            v5 ^= a2;
          v8 = (int)&a1[2 * (__int16)v5];
          LOWORD(v43) = *(_WORD *)(v8 + 4);
          v45 = v43 - v10;
          v106 = v45;
          if ((__int16)v45 > 0)
            break;
          if ((v45 & 0x8000u) != 0)
            goto LABEL_257;
          if ((_WORD)v5 == (_WORD)v102) {
            HIWORD(v101) = v42;
            goto LABEL_165;
          }
        }
        HIWORD(v87) = *(_WORD *)v8 - HIWORD(v101);
        LOWORD(v87) = 0;
        LOWORD(v101) = 0;
        if (v87 >= 0) {
          ++HIWORD(v87);
          v83 = v87 / ((__int16)v45 + 1);
        } else {
          --HIWORD(v87);
          v70 = (__int16)v45 + 1;
          v101 += v87 / v70;
          v83 = v87 / v70;
          ++HIWORD(v101);
        }
      }
      LOWORD(v8) = v99;
      HIWORD(v46) = HIWORD(v105);
      v74 = v99;
      LOWORD(v46) = v105 - 1;
      v27 = (_WORD)v105 == 1;
      v105 = v46;
      if (v27) {
        while (1) {
          v47 = v102;
          if ((_WORD)v5 == (_WORD)v102) {
            LOWORD(v8) = v74;
            HIWORD(v101) = v42;
            HIWORD(v99) = HIWORD(v74);
            goto LABEL_165;
          }
          HIWORD(v99) = a1[2 * (__int16)v102--];
          if ((__int16)(v47 - 1) == -1)
            v102 = a2 - 1;
          v8 = (int)&a1[2 * (__int16)v102];
          LOWORD(v47) = *(_WORD *)(v8 + 4);
          v48 = v47 - v10;
          v105 = v48;
          if ((__int16)v48 > 0)
            break;
          if ((v48 & 0x8000u) != 0)
            goto LABEL_257;
        }
        HIWORD(v95) = *(_WORD *)v8 - HIWORD(v99);
        LOWORD(v95) = 0;
        LOWORD(v99) = -1;
        if (v95 <= 0) {
          --HIWORD(v95);
          v8 = v95 / ((__int16)v48 + 1);
          v91 = v8;
          ++HIWORD(v99);
        } else {
          ++HIWORD(v95);
          v91 = v95 / ((__int16)v48 + 1);
          LOWORD(v8) = v91;
          v99 += v91;
        }
      }
      if (v10 >= winh) {
        winw = v3;
        return v8;
      }
      if (SHIWORD(v101) < v3)
        break;
      LOWORD(v8) = HIWORD(v99);
      if (SHIWORD(v99) > v3)
        goto LABEL_222;
    }
    LOWORD(v8) = HIWORD(v101);
    if (SHIWORD(v101) >= (int)v3)
      goto LABEL_257;
    LOWORD(v8) = HIWORD(v99);
    if (SHIWORD(v99) <= v3)
      goto LABEL_91;
  LABEL_181:
    if (SHIWORD(v99) <= 0)
      goto LABEL_257;
  LABEL_182:
    winw = v3;
    v51 = v3 * v10++ + scrptr + SHIWORD(v101);
    memset(v51, a3, v3 - SHIWORD(v101));
    v3 = winw;
    v52 = v83 + v101;
    v101 = v52;
    HIWORD(v8) = HIWORD(v106);
    v99 += v91;
    v53 = HIWORD(v52);
    LOWORD(v8) = v106 - 1;
    v27 = (_WORD)v106 == 1;
    v106 = v8;
    if (v27) {
      if ((_WORD)v5 == (_WORD)v102) {
        HIWORD(v101) = HIWORD(v52);
      LABEL_207:
        if (v10 >= winh)
          goto LABEL_257;
        if (SHIWORD(v101) < (unsigned int)winw) {
          LOWORD(v8) = HIWORD(v99);
          if (SHIWORD(v99) > (unsigned int)winw)
            goto LABEL_215;
        LABEL_126:
          if (SHIWORD(v99) <= 0)
            goto LABEL_257;
          goto LABEL_127;
        }
        LOWORD(v8) = HIWORD(v101);
        if (SHIWORD(v101) >= winw)
          goto LABEL_257;
      LABEL_251:
        LOWORD(v8) = HIWORD(v99);
        if (SHIWORD(v99) <= v3) {
          if (SHIWORD(v99) <= 0)
            goto LABEL_257;
          goto LABEL_173;
        }
      LABEL_254:
        v49 = v3 * v10;
        v39 = a3;
        v50 = scrptr;
        v38 = v3;
        goto LABEL_255;
      }
      while (1) {
        HIWORD(v54) = HIWORD(a2);
        v55 = a1[2 * (__int16)v5++];
        HIWORD(v101) = v55;
        if ((_WORD)v5 == (_WORD)a2)
          v5 ^= a2;
        v8 = (int)&a1[2 * (__int16)v5];
        LOWORD(v54) = *(_WORD *)(v8 + 4);
        v56 = v54 - v10;
        v106 = v56;
        if ((__int16)v56 > 0)
          break;
        if ((v56 & 0x8000u) != 0)
          goto LABEL_257;
        if ((_WORD)v5 == (_WORD)v102) {
          HIWORD(v101) = v53;
          goto LABEL_207;
        }
      }
      HIWORD(v88) = *(_WORD *)v8 - HIWORD(v101);
      LOWORD(v88) = 0;
      LOWORD(v101) = 0;
      if (v88 >= 0) {
        ++HIWORD(v88);
        v83 = v88 / ((__int16)v56 + 1);
      } else {
        --HIWORD(v88);
        v71 = (__int16)v56 + 1;
        v101 += v88 / v71;
        v83 = v88 / v71;
        ++HIWORD(v101);
      }
    }
    LOWORD(v8) = v99;
    HIWORD(v57) = HIWORD(v105);
    v76 = v99;
    LOWORD(v57) = v105 - 1;
    v27 = (_WORD)v105 == 1;
    v105 = v57;
    if (!v27)
      goto LABEL_205;
    while (1) {
      v58 = v102;
      if ((_WORD)v5 == (_WORD)v102) {
        LOWORD(v8) = v76;
        HIWORD(v101) = v53;
        HIWORD(v99) = HIWORD(v76);
        goto LABEL_207;
      }
      HIWORD(v99) = a1[2 * (__int16)v102--];
      if ((__int16)(v58 - 1) == -1)
        v102 = a2 - 1;
      v8 = (int)&a1[2 * (__int16)v102];
      LOWORD(v58) = *(_WORD *)(v8 + 4);
      v59 = v58 - v10;
      v105 = v59;
      if ((__int16)v59 > 0)
        break;
      if ((v59 & 0x8000u) != 0)
        goto LABEL_257;
    }
    HIWORD(v96) = *(_WORD *)v8 - HIWORD(v99);
    LOWORD(v96) = 0;
    LOWORD(v99) = -1;
    if (v96 <= 0) {
      --HIWORD(v96);
      v8 = v96 / ((__int16)v59 + 1);
      v91 = v8;
      ++HIWORD(v99);
    } else {
      ++HIWORD(v96);
      v91 = v96 / ((__int16)v59 + 1);
      LOWORD(v8) = v91;
      v99 += v91;
    }
  LABEL_205:
    if (v10 >= winh)
      return v8;
    if (SHIWORD(v101) >= (unsigned int)winw)
      break;
    LOWORD(v8) = HIWORD(v99);
    if (SHIWORD(v99) > (unsigned int)winw)
      goto LABEL_182;
  LABEL_90:
    if (SHIWORD(v99) <= 0)
      goto LABEL_257;
  LABEL_91:
    LOWORD(v8) = HIWORD(v101);
    if ((__int16)(HIWORD(v99) - HIWORD(v101)) > 0) {
      winw = v3;
      memset(v3 * v10 + SHIWORD(v101) + scrptr, a3, (__int16)(HIWORD(v99) - HIWORD(v101)));
      v3 = winw;
    } else if ((__int16)(HIWORD(v99) - HIWORD(v101)) < 0) {
      goto LABEL_257;
    }
    LOWORD(v8) = v83;
    v101 += v83;
    v99 += v91;
    v32 = HIWORD(v101);
    HIWORD(v33) = HIWORD(v106);
    ++v10;
    LOWORD(v33) = v106 - 1;
    v27 = (_WORD)v106 == 1;
    v106 = v33;
    if (v27) {
      if ((_WORD)v5 != (_WORD)v102) {
        while (1) {
          v34 = a1[2 * (__int16)v5++];
          HIWORD(v101) = v34;
          if ((_WORD)v5 == (_WORD)a2)
            v5 ^= a2;
          v8 = (int)&a1[2 * (__int16)v5];
          LOWORD(v33) = *(_WORD *)(v8 + 4);
          v33 -= v10;
          v106 = v33;
          if ((__int16)v33 > 0)
            break;
          if ((v33 & 0x8000u) != 0)
            goto LABEL_257;
          if ((_WORD)v5 == (_WORD)v102) {
            HIWORD(v101) = v32;
            goto LABEL_119;
          }
        }
        HIWORD(v86) = *(_WORD *)v8 - HIWORD(v101);
        LOWORD(v86) = 0;
        LOWORD(v101) = 0;
        if (v86 >= 0) {
          ++HIWORD(v86);
          v83 = v86 / ((__int16)v33 + 1);
        } else {
          --HIWORD(v86);
          v69 = (__int16)v33 + 1;
          v101 += v86 / v69;
          v83 = v86 / v69;
          ++HIWORD(v101);
        }
        goto LABEL_106;
      }
    LABEL_119:
      if (v10 >= winh)
        goto LABEL_257;
      if (SHIWORD(v101) < v3) {
        LOWORD(v8) = HIWORD(v99);
        if (SHIWORD(v99) <= v3) {
        LABEL_127:
          LOWORD(v8) = HIWORD(v99) - HIWORD(v101);
          if ((__int16)(HIWORD(v99) - HIWORD(v101)) > 0) {
            v38 = (__int16)v8;
            v39 = a3;
            v40 = SHIWORD(v101) + scrptr + v3 * v10;
            goto LABEL_256;
          }
          goto LABEL_257;
        }
      LABEL_214:
        if (SHIWORD(v99) > 0)
          goto LABEL_215;
        goto LABEL_257;
      }
      LOWORD(v8) = HIWORD(v101);
      if (SHIWORD(v101) >= (int)v3)
        goto LABEL_257;
      LOWORD(v8) = HIWORD(v99);
      if (SHIWORD(v99) <= v3)
        goto LABEL_173;
      goto LABEL_253;
    }
  LABEL_106:
    LOWORD(v8) = v99;
    HIWORD(v35) = HIWORD(v105);
    v73 = v99;
    LOWORD(v35) = v105 - 1;
    v27 = (_WORD)v105 == 1;
    v105 = v35;
    if (v27) {
      while (1) {
        v36 = v102;
        if ((_WORD)v5 == (_WORD)v102) {
          LOWORD(v8) = v73;
          HIWORD(v101) = v32;
          HIWORD(v99) = HIWORD(v73);
          goto LABEL_119;
        }
        HIWORD(v99) = a1[2 * (__int16)v102--];
        if ((__int16)(v36 - 1) == -1)
          v102 = a2 - 1;
        v8 = (int)&a1[2 * (__int16)v102];
        LOWORD(v36) = *(_WORD *)(v8 + 4);
        v37 = v36 - v10;
        v105 = v37;
        if ((__int16)v37 > 0)
          break;
        if ((v37 & 0x8000u) != 0)
          goto LABEL_257;
      }
      HIWORD(v94) = *(_WORD *)v8 - HIWORD(v99);
      LOWORD(v94) = 0;
      LOWORD(v99) = -1;
      if (v94 <= 0) {
        --HIWORD(v94);
        v8 = v94 / ((__int16)v37 + 1);
        v91 = v8;
        ++HIWORD(v99);
      } else {
        ++HIWORD(v94);
        v91 = v94 / ((__int16)v37 + 1);
        LOWORD(v8) = v91;
        v99 += v91;
      }
    }
    if (v10 >= winh) {
      winw = v3;
      return v8;
    }
  }
  LOWORD(v8) = HIWORD(v101);
  if (SHIWORD(v101) >= winw)
    goto LABEL_257;
  LOWORD(v8) = HIWORD(v99);
  if (SHIWORD(v99) <= (unsigned int)winw) {
  LABEL_135:
    if (SHIWORD(v99) > 0)
      goto LABEL_136;
    goto LABEL_257;
  }
  while (1) {
  LABEL_223:
    winw = v3;
    memset(v3 * v10 + scrptr, a3, v3);
    LOWORD(v8) = v91;
    ++v10;
    v101 += v83;
    v99 += v91;
    v60 = HIWORD(v101);
    HIWORD(v61) = HIWORD(v106);
    v3 = winw;
    LOWORD(v61) = v106 - 1;
    v27 = (_WORD)v106 == 1;
    v106 = v61;
    if (!v27)
      goto LABEL_234;
    if ((_WORD)v5 == (_WORD)v102)
      break;
    while (1) {
      v62 = a1[2 * (__int16)v5++];
      HIWORD(v101) = v62;
      if ((_WORD)v5 == (_WORD)a2)
        v5 ^= a2;
      v8 = (int)&a1[2 * (__int16)v5];
      LOWORD(v61) = *(_WORD *)(v8 + 4);
      v61 -= v10;
      v106 = v61;
      if ((__int16)v61 > 0)
        break;
      if ((v61 & 0x8000u) != 0)
        goto LABEL_257;
      if ((_WORD)v5 == (_WORD)v102) {
        HIWORD(v101) = v60;
        goto LABEL_247;
      }
    }
    HIWORD(v89) = *(_WORD *)v8 - HIWORD(v101);
    LOWORD(v89) = 0;
    LOWORD(v101) = 0;
    if (v89 >= 0) {
      ++HIWORD(v89);
      v83 = v89 / ((__int16)v61 + 1);
    } else {
      --HIWORD(v89);
      v72 = (__int16)v61 + 1;
      v101 += v89 / v72;
      v83 = v89 / v72;
      ++HIWORD(v101);
    }
  LABEL_234:
    LOWORD(v8) = v99;
    HIWORD(v63) = HIWORD(v105);
    v75 = v99;
    LOWORD(v63) = v105 - 1;
    v27 = (_WORD)v105 == 1;
    v105 = v63;
    if (v27) {
      while (1) {
        v64 = v102;
        if ((_WORD)v5 == (_WORD)v102) {
          LOWORD(v8) = v75;
          HIWORD(v101) = v60;
          HIWORD(v99) = HIWORD(v75);
          goto LABEL_247;
        }
        HIWORD(v99) = a1[2 * (__int16)v102--];
        if ((__int16)(v64 - 1) == -1)
          v102 = a2 - 1;
        v8 = (int)&a1[2 * (__int16)v102];
        LOWORD(v64) = *(_WORD *)(v8 + 4);
        v65 = v64 - v10;
        v105 = v65;
        if ((__int16)v65 > 0)
          break;
        if ((v65 & 0x8000u) != 0)
          goto LABEL_257;
      }
      HIWORD(v97) = *(_WORD *)v8 - HIWORD(v99);
      LOWORD(v97) = 0;
      LOWORD(v99) = -1;
      if (v97 <= 0) {
        --HIWORD(v97);
        v8 = v97 / ((__int16)v65 + 1);
        v91 = v8;
        ++HIWORD(v99);
      } else {
        ++HIWORD(v97);
        v91 = v97 / ((__int16)v65 + 1);
        LOWORD(v8) = v91;
        v99 += v91;
      }
    }
    if (v10 >= winh)
      return v8;
    if (SHIWORD(v101) < (unsigned int)winw) {
      LOWORD(v8) = HIWORD(v101);
      if (SHIWORD(v101) >= winw)
        goto LABEL_257;
      LOWORD(v8) = HIWORD(v99);
      if (SHIWORD(v99) <= (unsigned int)winw)
        goto LABEL_90;
      goto LABEL_182;
    }
    LOWORD(v8) = HIWORD(v99);
    if (SHIWORD(v99) <= (unsigned int)winw)
      goto LABEL_135;
  }
LABEL_247:
  if (v10 >= winh)
    goto LABEL_257;
  if (SHIWORD(v101) >= (unsigned int)winw)
    goto LABEL_251;
  LOWORD(v8) = HIWORD(v101);
  if (SHIWORD(v101) >= winw)
    goto LABEL_257;
  LOWORD(v8) = HIWORD(v99);
  if (SHIWORD(v99) <= (unsigned int)winw)
    goto LABEL_126;
LABEL_215:
  v50 = v3 * v10;
  v38 = v3 - SHIWORD(v101);
  v49 = scrptr + SHIWORD(v101);
  v39 = a3;
LABEL_255:
  v40 = v50 + v49;
LABEL_256:
  winw = v3;
  LOWORD(v8) = memset(v40, v39, v38);
  v3 = winw;
LABEL_257:
  winw = v3;
  return v8;
}

//-------------------------------------------------------------------------------------------------

__int16 __fastcall shadow_poly(int *a1, int a2, int a3)
{
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
  return v7;
}

//-------------------------------------------------------------------------------------------------
#endif
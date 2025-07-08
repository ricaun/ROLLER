#include "horizon.h"
//-------------------------------------------------------------------------------------------------

int test_y1;

//-------------------------------------------------------------------------------------------------

void DrawHorizon(int a1)
{
  /*
  int v1; // edx
  int v2; // ecx
  unsigned __int8 v3; // dl
  int v4; // eax
  int v5; // eax
  double v6; // st7
  double v7; // st6
  double v8; // st7
  int v9; // eax
  int v10; // esi
  int v11; // edi
  int v12; // eax
  int v13; // eax
  int v14; // eax
  __int16 v15; // fps
  _BOOL1 v16; // c0
  char v17; // c2
  _BOOL1 v18; // c3
  int v19; // eax
  int v20; // edx
  int v21; // edi
  int v22; // esi
  double v23; // st7
  double v24; // st6
  int v25; // edx
  int v26; // edi
  int v27; // ebp
  double v28; // st7
  double v29; // st7
  double v30; // st6
  int v31; // esi
  int v32; // esi
  int v33; // ecx
  int v34; // eax
  int v35; // edi
  int v36; // esi
  double v37; // st7
  int v38; // ebp
  double v39; // st7
  double v40; // st6
  int v41[2]; // [esp+14h] [ebp-70h] BYREF
  int v42[2]; // [esp+1Ch] [ebp-68h] BYREF
  double v43; // [esp+24h] [ebp-60h]
  float v44; // [esp+2Ch] [ebp-58h]
  int v45; // [esp+38h] [ebp-4Ch]
  int v46; // [esp+3Ch] [ebp-48h]
  int v47; // [esp+40h] [ebp-44h]
  int v48; // [esp+44h] [ebp-40h]
  int v49; // [esp+48h] [ebp-3Ch]
  float v50; // [esp+4Ch] [ebp-38h]
  float v51; // [esp+50h] [ebp-34h]
  float v52; // [esp+54h] [ebp-30h]
  float v53; // [esp+58h] [ebp-2Ch]
  int v54; // [esp+5Ch] [ebp-28h]
  int v55; // [esp+60h] [ebp-24h]
  unsigned __int8 v56; // [esp+64h] [ebp-20h]
  unsigned __int8 v57; // [esp+68h] [ebp-1Ch]

  v48 = a1;
  v1 = worldelev & 0x3FFF;
  v43 = tsin[v1];
  v2 = a1;
  v56 = -111;
  v57 = HorizonColour[4 * front_sec];
  if (v43 > horizon_c_variable_1 || v43 < horizon_c_variable_2 || (textures_off & 0x10) != 0) {
    if (tsin[worldelev & 0x3FFF] <= horizon_c_variable_1)
      v3 = v57;
    else
      v3 = v56;
    if ((textures_off & 0x10) != 0)
      v3 = v56;
    memset(a1, v3, winh * winw);
  } else {
    v4 = worldtilt & 0x3FFF;
    v53 = -tsin[v4];
    v52 = tcos[v4];
    upside_down = tcos[worldelev & 0x3FFF] < 0.0 != v52 < 0.0;
    ground_left = v53 < 0.0;
    if (tcos[worldelev & 0x3FFF] < 0.0)
      ground_left = v53 >= 0.0;
    v5 = worldelev & 0x3FFF;
    v6 = (double)VIEWDIST * ptan[v5];
    v7 = v6 * v53 + (double)xbase;
    _CHP(v5, v1 * 4);
    v47 = (int)v7;
    v45 = 199 - ybase;
    v8 = (double)(199 - ybase) + v6 * v52;
    _CHP(v9, 199 - ybase);
    v49 = (int)v8;
    if ((LODWORD(v53) & 0x7FFFFFFF) != 0)
      v50 = v52 / v53;
    else
      v50 = 41.0;
    if (v50 <= (double)horizon_c_variable_3 && v50 >= (double)horizon_c_variable_4) {
      v51 = (double)scr_size * horizon_c_variable_5;
      v19 = worldelev & 0x3FFF;
      v16 = tcos[v19] > 0.0;
      v17 = 0;
      v18 = 0.0 == tcos[v19];
      LOWORD(v19) = v15;
      if (!v16 && !v18) {
        HIBYTE(v52) ^= 0x80u;
        HIBYTE(v53) ^= 0x80u;
      }
      v20 = winh;
      *(float *)&v54 = ((double)v49 * v50 + (double)v47) * v51;
      if (winh > 0) {
        v21 = 4 * winh;
        v22 = 0;
        v23 = v50;
        do {
          v24 = *(float *)&v54 - v23;
          v22 += 4;
          v19 = v54;
          GroundPt_variable_7[v22 / 4u] = v54;
          *(float *)&v54 = v24;
        } while (v22 < v21);
      }
      if (ground_left) {
        v25 = winh;
        v26 = 0;
        if (winh > 0) {
          v27 = 0;
          do {
            v28 = hor_scan[v27];
            _CHP(v19, v25);
            v46 = (int)v28;
            if ((int)v28 <= winw) {
              if ((int)v28 >= 0) {
                v31 = v46;
                v19 = memset(v2, v57, v46);
                v2 += v31;
              } else {
                v29 = (double)v46;
                v30 = 1.0 / v51;
                v44 = -v52 * v29 * v30;
                modf(v29 * v53 * v30, (int)v41);
                modf(v44, (int)v42);
                v19 = 0;
                v46 = 0;
              }
              v25 = v46;
              v32 = winw - v46;
              if (winw - v46 >= 0) {
                v25 = v56;
                v19 = memset(v2, v56, winw - v46);
                v2 += v32;
              }
            } else {
              v25 = v57;
              v19 = memset(v2, v57, winw);
              v2 += winw;
            }
            ++v26;
            ++v27;
          } while (v26 < winh);
        }
      } else {
        v33 = winw - 1 + v2;
        v34 = winh;
        v35 = 0;
        if (winh > 0) {
          v36 = 0;
          do {
            v37 = hor_scan[v36];
            _CHP(v34, v20);
            v55 = (int)v37;
            v38 = (int)v37;
            if ((int)v37 >= 0) {
              if (v38 <= winw) {
                v33 -= winw - v38;
                v20 = v57;
                memset(v33 + 1, v57, winw - v38);
              } else {
                v20 = v38 - (winw - 1);
                v45 = v20;
                v39 = (double)v20;
                v40 = 1.0 / v51;
                v44 = -v52 * v39 * v40;
                modf(v39 * v53 * v40, (int)v41);
                modf(v44, (int)v42);
                v55 = winw;
              }
              if (v55 >= 0) {
                v33 -= v55;
                v20 = v56;
                memset(v33 + 1, v56, v55);
              }
              v34 = 2 * winw;
              v33 += 2 * winw;
            } else {
              v20 = v57;
              v34 = memset(v33 - winw + 1, v57, winw);
              v33 += winw;
            }
            ++v35;
            ++v36;
          } while (v35 < winh);
        }
      }
    } else {
      if (upside_down) {
        v10 = (v49 * scr_size + 32 - (__CFSHL__((v49 * scr_size + 32) >> 31, 6) + ((v49 * scr_size + 32) >> 31 << 6))) >> 6;
        if (v10 > winh)
          v10 = winh;
        if (v10 > 0) {
          memset(v2, v57, v10 * winw);
          v2 += v10 * winw;
        }
      } else {
        v10 = (v49 * scr_size - (__CFSHL__((v49 * scr_size) >> 31, 6) + ((v49 * scr_size) >> 31 << 6))) >> 6;
        v11 = v10;
        if (v10 > winh)
          v10 = winh;
        if (v11 > winh)
          v11 = winh;
        if (v11 > 0) {
          memset(v2, v56, v11 * winw);
          v2 += winw * v11;
        }
      }
      if (upside_down) {
        v12 = (v49 * scr_size + 32 - (__CFSHL__((v49 * scr_size + 32) >> 31, 6) + ((v49 * scr_size + 32) >> 31 << 6))) >> 6;
        if (v12 > winh)
          v12 = winh;
        v13 = winh - v12;
        if (v13 > winh)
          v13 = winh;
        if (v13 > 0)
          memset(v2, v56, v13 * winw);
      } else {
        v14 = winh - v10;
        if (winh - v10 > winh)
          v14 = winh;
        if (v14 > 0)
          memset(v2, v57, v14 * winw);
      }
    }
  }
  if ((textures_off & 8) == 0)
    displayclouds();*/
}

//-------------------------------------------------------------------------------------------------

void initclouds(int a1)
{/*
  int i; // edi
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // ebp
  int v6; // eax
  int v7; // esi
  double v8; // st6
  double v9; // st5
  float v10; // eax
  double v11; // st4
  double v12; // st6
  int v13; // ecx
  double v14; // st6
  double v15; // st3
  double v16; // st2
  double v17; // rt1
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // edx
  double v22; // st7
  double v23; // st6
  double v24; // st7
  double v25; // st6
  __int16 v26; // fps
  _BOOL1 v27; // c0
  char v28; // c2
  _BOOL1 v29; // c3
  float v30; // [esp+8h] [ebp-80h]
  float v31; // [esp+Ch] [ebp-7Ch]
  float v32; // [esp+10h] [ebp-78h]
  float v33; // [esp+14h] [ebp-74h]
  float v34; // [esp+18h] [ebp-70h]
  float v35; // [esp+1Ch] [ebp-6Ch]
  float v36; // [esp+20h] [ebp-68h]
  float v37; // [esp+24h] [ebp-64h]
  float v38; // [esp+28h] [ebp-60h]
  float v39; // [esp+2Ch] [ebp-5Ch]
  float v40; // [esp+30h] [ebp-58h]
  float v41; // [esp+34h] [ebp-54h]
  float v42; // [esp+38h] [ebp-50h]
  float v43; // [esp+3Ch] [ebp-4Ch]
  float v44; // [esp+40h] [ebp-48h]
  float v45; // [esp+44h] [ebp-44h]
  float v46; // [esp+48h] [ebp-40h]
  float v47; // [esp+4Ch] [ebp-3Ch]
  float v48; // [esp+50h] [ebp-38h]
  float v49; // [esp+58h] [ebp-30h]
  float v50; // [esp+5Ch] [ebp-2Ch]
  float v51; // [esp+60h] [ebp-28h]
  float v52; // [esp+64h] [ebp-24h]
  float v53; // [esp+68h] [ebp-20h]
  float v54; // [esp+6Ch] [ebp-1Ch]

  for (i = 0; i < 40; ++i) {
    v52 = 1800000.0;
    do {
      v2 = rand(a1);
      v3 = 3400 * ((v2 * v2 - (__CFSHL__((v2 * v2) >> 31, 15) + ((v2 * v2) >> 31 << 15))) >> 15);
      v4 = (v3 - (__CFSHL__(v3 >> 31, 15) + (v3 >> 31 << 15))) >> 15;
      v5 = v4 + 520;
      v6 = rand(v4);
      v7 = ((v6 << 14) - (__CFSHL__(v6 << 14 >> 31, 15) + (v6 << 14 >> 31 << 15))) >> 15;
      v30 = tcos[v7] * tcos[v5];
      v32 = tsin[v7] * tcos[v5];
      v49 = -tsin[v7];
      v43 = tsin[v5];
      v50 = tcos[v7];
      v47 = -v50 * v43;
      v46 = v49 * v43;
      v51 = -v52;
      v45 = horizon_c_variable_7 * v30;
      v33 = v51 * v49;
      v40 = v45 + v33;
      v8 = v52 * v47;
      cloud[17 * i] = v40 + v8;
      v44 = horizon_c_variable_7 * v32;
      v36 = v51 * v50;
      v41 = v44 + v36;
      v9 = v52 * v46;
      cloud_variable_1[17 * i] = v41 + v9;
      v48 = horizon_c_variable_7 * v43;
      v35 = 0.0 * v51;
      v38 = v48 + v35;
      v10 = tcos[v5];
      v42 = v52 * v10;
      cloud_variable_2[17 * i] = v38 + v42;
      v31 = v52 * v49;
      v11 = v45 + v31;
      v39 = v11;
      cloud_variable_3[17 * i] = v8 + v11;
      v34 = v52 * v50;
      v12 = v44 + v34;
      v37 = v12;
      v13 = -1;
      cloud_variable_4[17 * i] = v9 + v12;
      v14 = 0.0 * v52 + v48;
      cloud_variable_5[17 * i] = v14 + v42;
      v15 = v51 * v47;
      cloud_variable_6[17 * i] = v39 + v15;
      v16 = v51 * v46;
      cloud_variable_7[17 * i] = v37 + v16;
      v17 = v51 * v10;
      cloud_variable_8[17 * i] = v14 + v17;
      cloud_variable_9[17 * i] = v15 + v40;
      cloud_variable_10[17 * i] = v16 + v41;
      cloud_variable_11[17 * i] = v17 + v38;
      cloud_variable_12[17 * i] = v47 * 0.0 + 0.0 * v49 + v45;
      cloud_variable_13[17 * i] = 0.0 * v50 + v44 + 0.0 * v46;
      cloud_variable_14[17 * i] = v48 + 0.0 * v10;
      v18 = rand(LODWORD(v10));
      v19 = (5 * v18 - (__CFSHL__((5 * v18) >> 31, 15) + ((5 * v18) >> 31 << 15))) >> 15;
      *((_DWORD *)&cloud_variable_15 + 17 * i) = v19;
      *((_DWORD *)&cloud_variable_15 + 17 * i) = v19 + 1288;
      v20 = rand(v19);
      if (v20 < 0x4000)
        *((_DWORD *)&cloud_variable_15 + 17 * i) += 4096;
      if ((int)rand(v20) < 0x4000)
        *((_WORD *)&cloud_variable_16 + 34 * i) += 4;
      HIWORD(a1) = HIWORD(v52);
      cloud_variable_17[17 * i] = v52;
      if (i > 0) {
        v21 = 0;
        do {
          if (v13) {
            v22 = cloud_variable_12[v21] - cloud_variable_12[17 * i];
            v23 = cloud_variable_13[v21] - cloud_variable_13[17 * i];
            v24 = v22 * v22 + v23 * v23;
            v25 = cloud_variable_14[v21] - cloud_variable_14[17 * i];
            v54 = sqrt(v24 + v25 * v25);
          }
          v53 = v52 + cloud_variable_17[17 * i];
          if (v54 < v53 * horizon_c_variable_6)
            v13 = 0;
          v21 += 17;
        } while (v21 < 17 * i);
      }
      if (!v13)
        v52 = v52 + horizon_c_variable_8;
      v27 = v52 < (double)horizon_c_variable_9;
      v28 = 0;
      v29 = v52 == horizon_c_variable_9;
      LOWORD(a1) = v26;
      if (v52 < (double)horizon_c_variable_9)
        v52 = 1000000.0;
    } while (!v13);
  }*/
}

//-------------------------------------------------------------------------------------------------

void displayclouds()
{/*
  int v0; // eax
  int i; // esi
  double v2; // st7
  double v3; // st6
  double v4; // st5
  double v5; // st7
  __int16 v6; // fps
  int v7; // edx
  _BOOL1 v8; // c0
  char v9; // c2
  _BOOL1 v10; // c3
  double v11; // st7
  double v12; // st6
  double v13; // st5
  double v14; // st7
  int v15; // ecx
  int v16; // eax
  __int16 v17; // fps
  _BOOL1 v18; // c0
  char v19; // c2
  _BOOL1 v20; // c3
  int v21; // eax
  double v22; // st7
  double v23; // st6
  double v24; // st5
  double v25; // st7
  __int16 v26; // fps
  _BOOL1 v27; // c0
  char v28; // c2
  _BOOL1 v29; // c3
  double v30; // st7
  double v31; // st6
  double v32; // st5
  double v33; // st7
  int v34; // ebx
  int v35; // eax
  __int16 v36; // fps
  _BOOL1 v37; // c0
  char v38; // c2
  _BOOL1 v39; // c3
  int v40; // eax
  double v41; // st7
  double v42; // st6
  double v43; // st5
  double v44; // st7
  __int16 v45; // fps
  _BOOL1 v46; // c0
  char v47; // c2
  _BOOL1 v48; // c3
  double v49; // st7
  double v50; // st6
  double v51; // st5
  double v52; // st7
  int v53; // ebx
  int v54; // eax
  __int16 v55; // fps
  _BOOL1 v56; // c0
  char v57; // c2
  _BOOL1 v58; // c3
  int v59; // eax
  double v60; // st7
  double v61; // st6
  double v62; // st5
  double v63; // st7
  __int16 v64; // fps
  _BOOL1 v65; // c0
  char v66; // c2
  _BOOL1 v67; // c3
  double v68; // st7
  double v69; // st6
  double v70; // st5
  double v71; // st7
  int v72; // ebx
  int v73; // eax
  __int16 v74; // fps
  _BOOL1 v75; // c0
  char v76; // c2
  _BOOL1 v77; // c3
  int v78; // eax
  float v79; // [esp+3Ch] [ebp-6Ch]
  float v80; // [esp+40h] [ebp-68h]
  float v81; // [esp+44h] [ebp-64h]
  float v82; // [esp+48h] [ebp-60h]
  float v83; // [esp+4Ch] [ebp-5Ch]
  float v84; // [esp+50h] [ebp-58h]
  float v85; // [esp+54h] [ebp-54h]
  float v86; // [esp+58h] [ebp-50h]
  float v87; // [esp+5Ch] [ebp-4Ch]
  float v88; // [esp+60h] [ebp-48h]
  float v89; // [esp+64h] [ebp-44h]
  float v90; // [esp+68h] [ebp-40h]
  float v91; // [esp+6Ch] [ebp-3Ch]
  float v92; // [esp+70h] [ebp-38h]
  float v93; // [esp+74h] [ebp-34h]
  float v94; // [esp+78h] [ebp-30h]
  float v95; // [esp+7Ch] [ebp-2Ch]
  float v96; // [esp+80h] [ebp-28h]
  float v97; // [esp+84h] [ebp-24h]
  float v98; // [esp+88h] [ebp-20h]

  v0 = set_starts(0);
  if ((textures_off & 8) == 0) {
    for (i = 0; i != 680; i += 17) {
      v2 = cloud[i] - viewx;
      v3 = cloud_variable_1[i] - viewy;
      v4 = cloud_variable_2[i] * horizon_c_variable_10 - viewz;
      v79 = v2 * vk1 + v3 * vk4 + v4 * vk7;
      v80 = v2 * vk2 + v3 * vk5 + v4 * vk8;
      v5 = v2 * vk3 + v3 * vk6 + v4 * vk9;
      v88 = v5;
      v7 = 0;
      v8 = v5 < horizon_c_variable_11;
      v9 = 0;
      v10 = v5 == horizon_c_variable_11;
      LOWORD(v0) = v6;
      if (v5 < horizon_c_variable_11) {
        v7 = 1;
        v88 = 80.0;
      }
      v11 = (double)VIEWDIST;
      v12 = 1.0 / v88;
      v13 = v11 * v79 * v12 + (double)xbase;
      _CHP(v0, v7);
      xp = (int)v13;
      v14 = v12 * (v11 * v80) + (double)ybase;
      v15 = scr_size;
      _CHP(scr_size * (int)v13, v7);
      yp = (int)v14;
      v87 = (float)(v16 >> 6);
      v0 = (v15 * (199 - (int)v14)) >> 6;
      v89 = (float)v0;
      if (v7
        || v87 >= (double)horizon_c_variable_12
        && v87 <= (double)horizon_c_variable_13
        && v89 >= (double)horizon_c_variable_12
        && (v18 = v89 < (double)horizon_c_variable_13,
            v19 = 0,
            v20 = v89 == horizon_c_variable_13,
            LOWORD(v0) = v17,
            v89 <= (double)horizon_c_variable_13)) {
        _CHP(v0, v7);
        _CHP(v21, v7);
      } else {
        v7 = 1;
      }
      if (!v7) {
        v22 = cloud_variable_3[i] - viewx;
        v23 = cloud_variable_4[i] - viewy;
        v24 = cloud_variable_5[i] * horizon_c_variable_10 - viewz;
        v86 = v22 * vk1 + v23 * vk4 + v24 * vk7;
        v81 = v22 * vk2 + v23 * vk5 + v24 * vk8;
        v25 = v22 * vk3 + v23 * vk6 + v24 * vk9;
        v94 = v25;
        v27 = v25 < horizon_c_variable_11;
        v28 = 0;
        v29 = v25 == horizon_c_variable_11;
        LOWORD(v0) = v26;
        if (v25 < horizon_c_variable_11) {
          v0 = 1117782016;
          v7 = 1;
          v94 = 80.0;
        }
        v30 = (double)VIEWDIST;
        v31 = 1.0 / v94;
        v32 = v30 * v86 * v31 + (double)xbase;
        _CHP(v0, v7);
        xp = (int)v32;
        v33 = v31 * (v30 * v81) + (double)ybase;
        v34 = scr_size;
        _CHP(scr_size * (int)v32, v7);
        yp = (int)v33;
        v91 = (float)(v35 >> 6);
        v0 = (v34 * (199 - (int)v33)) >> 6;
        v96 = (float)v0;
        if (v7
          || v91 >= (double)horizon_c_variable_12
          && v91 <= (double)horizon_c_variable_13
          && v96 >= (double)horizon_c_variable_12
          && (v37 = v96 < (double)horizon_c_variable_13,
              v38 = 0,
              v39 = v96 == horizon_c_variable_13,
              LOWORD(v0) = v36,
              v96 <= (double)horizon_c_variable_13)) {
          _CHP(v0, v7);
          _CHP(v40, v7);
        } else {
          v7 = 1;
        }
        if (!v7) {
          v41 = cloud_variable_6[i] - viewx;
          v42 = cloud_variable_7[i] - viewy;
          v43 = cloud_variable_8[i] * horizon_c_variable_10 - viewz;
          v83 = v41 * vk1 + v42 * vk4 + v43 * vk7;
          v85 = v41 * vk2 + v42 * vk5 + v43 * vk8;
          v44 = v41 * vk3 + v42 * vk6 + v43 * vk9;
          v93 = v44;
          v46 = v44 < horizon_c_variable_11;
          v47 = 0;
          v48 = v44 == horizon_c_variable_11;
          LOWORD(v0) = v45;
          if (v44 < horizon_c_variable_11) {
            v7 = 1;
            v93 = 80.0;
          }
          v49 = (double)VIEWDIST;
          v50 = 1.0 / v93;
          v51 = v49 * v83 * v50 + (double)xbase;
          _CHP(v0, v7);
          xp = (int)v51;
          v52 = v50 * (v49 * v85) + (double)ybase;
          v53 = scr_size;
          _CHP(scr_size * (int)v51, v7);
          yp = (int)v52;
          v90 = (float)(v54 >> 6);
          v0 = (v53 * (199 - (int)v52)) >> 6;
          v98 = (float)v0;
          if (v7
            || v90 >= (double)horizon_c_variable_12
            && v90 <= (double)horizon_c_variable_13
            && v98 >= (double)horizon_c_variable_12
            && (v56 = v98 < (double)horizon_c_variable_13,
                v57 = 0,
                v58 = v98 == horizon_c_variable_13,
                LOWORD(v0) = v55,
                v98 <= (double)horizon_c_variable_13)) {
            _CHP(v0, v7);
            _CHP(v59, v7);
          } else {
            v7 = 1;
          }
          if (!v7) {
            v60 = cloud_variable_9[i] - viewx;
            v61 = cloud_variable_10[i] - viewy;
            v62 = cloud_variable_11[i] * horizon_c_variable_10 - viewz;
            v82 = v60 * vk1 + v61 * vk4 + v62 * vk7;
            v84 = v60 * vk2 + v61 * vk5 + v62 * vk8;
            v63 = v60 * vk3 + v61 * vk6 + v62 * vk9;
            v92 = v63;
            v65 = v63 < horizon_c_variable_11;
            v66 = 0;
            v67 = v63 == horizon_c_variable_11;
            LOWORD(v0) = v64;
            if (v63 < horizon_c_variable_11) {
              v7 = 1;
              v92 = 80.0;
            }
            v68 = (double)VIEWDIST;
            v69 = 1.0 / v92;
            v70 = v68 * v82 * v69 + (double)xbase;
            _CHP(v0, v7);
            xp = (int)v70;
            v71 = v69 * (v68 * v84) + (double)ybase;
            v72 = scr_size;
            _CHP(scr_size * (int)v70, v7);
            yp = (int)v71;
            v95 = (float)(v73 >> 6);
            v0 = (v72 * (199 - (int)v71)) >> 6;
            v97 = (float)v0;
            if (v7
              || v95 >= (double)horizon_c_variable_12
              && v95 <= (double)horizon_c_variable_13
              && v97 >= (double)horizon_c_variable_12
              && (v75 = v97 < (double)horizon_c_variable_13,
                  v76 = 0,
                  v77 = v97 == horizon_c_variable_13,
                  LOWORD(v0) = v74,
                  v97 <= (double)horizon_c_variable_13)) {
              _CHP(v0, v7);
              _CHP(v78, v7);
            } else {
              v7 = 1;
            }
            if (!v7)
              v0 = POLYTEX(gfx_size);
          }
        }
      }
    }
  }*/
}

//-------------------------------------------------------------------------------------------------
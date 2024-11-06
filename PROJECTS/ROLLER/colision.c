#ifdef ENABLE_PSEUDO
//-------------------------------------------------------------------------------------------------

void testcollisions()
{
  int v0; // esi
  float *v1; // ecx
  int v2; // ebx
  float *v3; // edx
  float *v4; // eax
  int v5; // [esp+0h] [ebp-20h]
  unsigned int v6; // [esp+4h] [ebp-1Ch]

  v5 = 0;
  if (numcars > 0) {
    v6 = 0;
    do {
      if (Car_variable_17[v6 / 4] == 3 && (Car_variable_33[v6] & 2) == 0) {
        v0 = v5 + 1;
        if (v5 + 1 < numcars) {
          v1 = &Car[77 * v0];
          do {
            if (Car_variable_17[77 * v0] == 3 && (Car_variable_33[308 * v0] & 2) == 0) {
              v2 = Car_variable_3[154 * v0] - Car_variable_3[v6 / 2];
              if (v2 < 0)
                v2 += TRAK_LEN;
              if (v2 > TRAK_LEN / 2)
                v2 -= TRAK_LEN;
              if ((int)abs32(v2) < 4) {
                v3 = &Car[v6 / 4];
                if (v2 < 0) {
                  v2 = -v2;
                  v4 = v1;
                } else {
                  v4 = &Car[v6 / 4];
                  v3 = v1;
                }
                testcoll(v4, v3, v2);
              }
            }
            ++v0;
            v1 += 77;
          } while (v0 < numcars);
        }
      }
      v6 += 308;
      ++v5;
    } while (v5 < numcars);
  }
}

//-------------------------------------------------------------------------------------------------

void __fastcall testcoll(int a1, int a2, int a3)
{
  float *v6; // eax
  double v7; // st7
  double v8; // st6
  double v9; // st5
  float *v10; // eax
  double v11; // rt0
  double v12; // st5
  double v13; // st4
  double v14; // st7
  double v15; // rt2
  double v16; // st4
  int v17; // ebx
  int v18; // eax
  int i; // edx
  int v20; // ecx
  int v21; // ebx
  int v22; // ebp
  __int16 v23; // ax
  int v24; // ecx
  int v25; // eax
  int v26; // edx
  int v27; // edx
  float *v28; // eax
  double v29; // st7
  double v30; // st6
  double v31; // st5
  float *v32; // eax
  double v33; // rt0
  double v34; // st5
  double v35; // st4
  double v36; // st7
  double v37; // rt2
  double v38; // st4
  int v39; // eax
  __int16 v40; // dx
  int v41; // ecx
  int v42; // ebp
  int v43; // eax
  int v44; // edx
  double v45; // st7
  double v46; // st6
  double v47; // st5
  __int16 v48; // ax
  float *v49; // edx
  int v50; // eax
  int v51; // ebx
  unsigned int v52; // edx
  double v53; // st4
  double v54; // st7
  double v55; // st6
  double v56; // st7
  unsigned int v57; // eax
  unsigned int v58; // eax
  double v59; // st6
  double v60; // st5
  double v61; // st7
  int v62; // eax
  int v63; // edx
  double v64; // st6
  int v65; // eax
  int v66; // eax
  int v67; // eax
  int v68; // eax
  int v69; // eax
  long double v70; // st7
  int v71; // edx
  int v72; // ebx
  int v73; // eax
  long double v74; // st7
  int v75; // eax
  double v76; // st7
  double v77; // st7
  int v78; // eax
  int v79; // ecx
  int v80; // eax
  int v81; // ecx
  float v82; // [esp+0h] [ebp-CCh]
  float v83; // [esp+0h] [ebp-CCh]
  float v84; // [esp+0h] [ebp-CCh]
  int v85; // [esp+4h] [ebp-C8h]
  int v86; // [esp+4h] [ebp-C8h]
  int v87; // [esp+4h] [ebp-C8h]
  float v88; // [esp+4h] [ebp-C8h]
  float v89; // [esp+4h] [ebp-C8h]
  float v90; // [esp+4h] [ebp-C8h]
  float v91; // [esp+4h] [ebp-C8h]
  float v92; // [esp+18h] [ebp-B4h]
  float v93; // [esp+20h] [ebp-ACh]
  float v94; // [esp+28h] [ebp-A4h]
  float v95; // [esp+2Ch] [ebp-A0h]
  float v96; // [esp+38h] [ebp-94h]
  float v97; // [esp+38h] [ebp-94h]
  float v98; // [esp+44h] [ebp-88h]
  float v99; // [esp+44h] [ebp-88h]
  float v100; // [esp+50h] [ebp-7Ch]
  float v101; // [esp+58h] [ebp-74h]
  float v102; // [esp+5Ch] [ebp-70h]
  float v103; // [esp+60h] [ebp-6Ch]
  float v104; // [esp+64h] [ebp-68h]
  float v105; // [esp+68h] [ebp-64h]
  __int16 v106; // [esp+6Ch] [ebp-60h]
  int v107; // [esp+70h] [ebp-5Ch]
  int v108; // [esp+74h] [ebp-58h]
  float v109; // [esp+78h] [ebp-54h]
  int v110; // [esp+7Ch] [ebp-50h]
  float v111; // [esp+80h] [ebp-4Ch]
  float v112; // [esp+84h] [ebp-48h]
  float v113; // [esp+88h] [ebp-44h]
  float v114; // [esp+8Ch] [ebp-40h]
  float v115; // [esp+90h] [ebp-3Ch]
  float v116; // [esp+94h] [ebp-38h]
  float v117; // [esp+98h] [ebp-34h]
  float v118; // [esp+9Ch] [ebp-30h]
  float v119; // [esp+A0h] [ebp-2Ch]
  float v120; // [esp+A4h] [ebp-28h]
  int v121; // [esp+A8h] [ebp-24h]
  float v122; // [esp+ACh] [ebp-20h]
  int v123; // [esp+B0h] [ebp-1Ch]
  float v124; // [esp+B4h] [ebp-18h]
  float v125; // [esp+B4h] [ebp-18h]

  v117 = *(float *)a1;
  v114 = *(float *)(a1 + 4);
  v6 = (float *)((char *)&localdata + 128 * *(__int16 *)(a2 + 12));
  v7 = v6[1] * *(float *)(a2 + 4) + *v6 * *(float *)a2 + v6[2] * *(float *)(a2 + 8) - v6[9];
  v8 = v6[4] * *(float *)(a2 + 4) + v6[3] * *(float *)a2 + v6[5] * *(float *)(a2 + 8) - v6[10];
  v9 = v6[7] * *(float *)(a2 + 4) + v6[6] * *(float *)a2 + v6[8] * *(float *)(a2 + 8) - v6[11];
  v10 = (float *)((char *)&localdata + 128 * *(__int16 *)(a1 + 12));
  v11 = v9;
  v12 = v8 + v10[10];
  v13 = v7 + v10[9];
  v14 = v10[3] * v12 + *v10 * v13;
  v15 = v13;
  v16 = v11 + v10[11];
  v96 = v14 + v10[6] * v16;
  v98 = v16 * v10[7] + v15 * v10[1] + v12 * v10[4];
  v113 = v96;
  v115 = v98;
  v17 = *(__int16 *)(a2 + 20);
  v106 = *(_WORD *)(a1 + 20);
  v18 = *(__int16 *)(a1 + 12);
  for (i = 0; i < a3; ++i) {
    v20 = v18++ << 7;
    v17 += *(int *)((char *)&localdata_variable_7 + v20);
    if (v18 == TRAK_LEN)
      v18 ^= TRAK_LEN;
  }
  *(float *)&v85 = v98 - v114;
  v82 = v96 - v117;
  v21 = v17 & 0x3FFF;
  v22 = 0;
  v23 = getangle(v18, v21, v82, v85);
  v24 = (v106 - v23) & 0x3FFF;
  v25 = ((_WORD)v21 - v23) & 0x3FFF;
  v26 = v24;
  if (v24 > 0x2000)
    v26 = v24 - 0x2000;
  if (v25 > 0x2000)
    v25 -= 0x2000;
  if (v26 > 4096)
    v26 -= 0x2000;
  if (v25 > 4096)
    v25 -= 0x2000;
  v27 = 33 * (((v26 << 6) + 270336) >> 14);
  if (coldist[(((v25 << 6) + 270336) >> 14) + v27] > sqrt((v96 - v117) * (v96 - v117) + (v98 - v114) * (v98 - v114)))
    v22 = -1;
  if (v22) {
    v93 = *(float *)(a1 + 52);
    v94 = *(float *)(a1 + 56);
    v28 = (float *)((char *)&localdata + 128 * *(__int16 *)(a2 + 14));
    v29 = v28[1] * *(float *)(a2 + 56) + *v28 * *(float *)(a2 + 52) + v28[2] * *(float *)(a2 + 60) - v28[9];
    v30 = v28[3] * *(float *)(a2 + 52) + v28[4] * *(float *)(a2 + 56) + v28[5] * *(float *)(a2 + 60) - v28[10];
    v31 = v28[6] * *(float *)(a2 + 52) + v28[7] * *(float *)(a2 + 56) + v28[8] * *(float *)(a2 + 60) - v28[11];
    v32 = (float *)((char *)&localdata + 128 * *(__int16 *)(a1 + 14));
    v33 = v31;
    v34 = v30 + v32[10];
    v35 = v29 + v32[9];
    v36 = v32[3] * v34 + *v32 * v35;
    v37 = v35;
    v38 = v33 + v32[11];
    v97 = v36 + v32[6] * v38;
    v99 = v38 * v32[7] + v37 * v32[1] + v34 * v32[4];
    *(float *)&v86 = v115 - v114;
    v83 = v113 - v117;
    v39 = getangle((int)v32, v27, v83, v86);
    *(float *)&v87 = v99 - v94;
    v84 = v97 - v93;
    v40 = v39;
    v41 = v39;
    v107 = getangle(v39, v39, v84, v87);
    v42 = (v106 - v40) & 0x3FFF;
    v43 = ((_WORD)v21 - v40) & 0x3FFF;
    v44 = v42;
    if (v42 > 0x2000)
      v44 = v42 - 0x2000;
    if (v43 > 0x2000)
      v43 -= 0x2000;
    if (v44 > 4096)
      v44 -= 0x2000;
    if (v43 > 4096)
      v43 -= 0x2000;
    v45 = coldist[33 * (((v44 << 6) + 270336) >> 14) + (((v43 << 6) + 270336) >> 14)] + colision_c_variable_1;
    v46 = (v117 + v113) * colision_c_variable_2;
    v47 = (v114 + v115) * colision_c_variable_2;
    *(float *)a1 = v46 - v45 * tcos[v41] * colision_c_variable_2;
    *(float *)(a1 + 4) = v47 - v45 * tsin[v41] * colision_c_variable_2;
    *(float *)a2 = v46 + v45 * tcos[v41] * colision_c_variable_2;
    *(float *)(a2 + 4) = v47 + v45 * tsin[v41] * colision_c_variable_2;
    v48 = *(_WORD *)(a1 + 12);
    *(_WORD *)(a2 + 12) = v48;
    v49 = (float *)((char *)&localdata + 128 * v48);
    if (fabs(*(float *)a1) > v49[12])
      scansection(a1);
    if (fabs(*(float *)a2) > v49[12])
      scansection(a2);
    v92 = *(float *)(a1 + 24);
    v50 = (v106 - (_WORD)v107) & 0x3FFF;
    v116 = v92 * tcos[v50];
    v105 = v92 * tsin[v50];
    v95 = *(float *)(a2 + 24);
    v51 = ((_WORD)v21 - (_WORD)v107) & 0x3FFF;
    v112 = v95 * tcos[v51];
    v101 = v95 * tsin[v51];
    if (v112 < (double)v116) {
      v52 = *(unsigned __int8 *)(a2 + 102);
      v119 = *(float *)&CarEngines_variable_11[28 * *(unsigned __int8 *)(a1 + 102)];
      v118 = *(float *)&CarEngines_variable_11[28 * v52];
      v53 = 1.0 / (v119 + v118);
      v54 = ((v119 - v118 * colision_c_variable_3) * v116 + v118 * colision_c_variable_4 * v112) * v53;
      v111 = v54 * tcos[v107] - v105 * tsin[v107];
      v55 = v54 * tsin[v107] + v105 * tcos[v107];
      v56 = (v112 * (v118 - v119 * colision_c_variable_3) + v116 * (v119 * colision_c_variable_4)) * v53;
      *(float *)&v108 = v55;
      v109 = v56 * tcos[v107] - v101 * tsin[v107];
      v57 = ((unsigned __int16)*(_DWORD *)(a1 + 64) - (_WORD)v41) & 0x3FFF;
      v121 = v57;
      *(float *)&v110 = v56 * tsin[v107] + v101 * tcos[v107];
      if (v57 > 0x2000) {
        v52 = v57 - 0x4000;
        v121 = v57 - 0x4000;
      }
      v58 = ((unsigned __int16)*(_DWORD *)(a2 + 64) - (_WORD)v41) & 0x3FFF;
      v123 = v58;
      if (v58 > 0x2000)
        v123 = v58 - 0x4000;
      v124 = fabs(v112 - v116);
      v59 = 1.0 / ((v118 + v119) * colision_c_variable_6);
      v60 = v118 * colision_c_variable_5 * (double)v123 * v124 * v59;
      _CHP(v58, v52);
      *(_DWORD *)(a1 + 68) = (int)v60;
      v61 = v59 * (v119 * colision_c_variable_5 * (double)v121 * v124);
      _CHP(v62, v52);
      *(_DWORD *)(a2 + 68) = (int)v61;
      if (*(int *)(a1 + 68) > 1300)
        *(_DWORD *)(a1 + 68) = 1300;
      if (*(int *)(a2 + 68) > 1300)
        *(_DWORD *)(a2 + 68) = 1300;
      if (*(int *)(a1 + 68) < -1300)
        *(_DWORD *)(a1 + 68) = -1300;
      if (*(int *)(a2 + 68) < -1300)
        *(_DWORD *)(a2 + 68) = -1300;
      if (ViewType[0] == *(_DWORD *)(a1 + 32) || ViewType[0] == *(_DWORD *)(a2 + 32))
        v63 = ViewType[0];
      else
        v63 = *(_DWORD *)(a1 + 32);
      v64 = v124 * colision_c_variable_7 * colision_c_variable_8;
      _CHP(ViewType[0], v63);
      if (v124 >= (double)colision_c_variable_9)
        v65 = 8;
      else
        v65 = 7;
      v66 = sfxpend(v65, v63, (int)v64);
      v67 = getangle(v66, v63, v111, v108);
      *(_DWORD *)(a1 + 64) = v67;
      *(_DWORD *)(a2 + 64) = getangle(v67, v63, v109, v110);
      v88 = sqrt(v111 * v111 + *(float *)&v108 * *(float *)&v108);
      SetEngine(a1, v88);
      v89 = sqrt(v109 * v109 + *(float *)&v110 * *(float *)&v110);
      SetEngine(a2, v89);
      v68 = *(_DWORD *)(a1 + 192);
      if (v68) {
        if (v68 != 2)
          changestrategy(a1);
        v71 = 0;
      } else {
        v69 = v121 & 0x3FFF;
        v70 = fabs(tsin[v69]);
        _CHP(v69, v63);
        v71 = 18 * (int)v70;
      }
      v72 = *(_DWORD *)(a2 + 192);
      if (v72) {
        if (v72 != 2)
          changestrategy(a2);
        v75 = 0;
      } else {
        v73 = v123 & 0x3FFF;
        v74 = fabs(tsin[v73]);
        _CHP(v73, v71);
        v75 = 18 * (int)v74;
      }
      if (human_control[*(_DWORD *)(a1 + 32)] && *(_BYTE *)(a2 + 102) != 13)
        v75 += 18;
      if (human_control[*(_DWORD *)(a2 + 32)] && *(_BYTE *)(a1 + 102) != 13)
        v71 += 18;
      if (*(int *)(a1 + 176) < 144)
        *(_DWORD *)(a1 + 176) = v71;
      if (*(int *)(a1 + 176) < 0)
        *(_DWORD *)(a1 + 176) = 0;
      if (*(int *)(a2 + 176) < 144)
        *(_DWORD *)(a2 + 176) = v75;
      if (*(int *)(a2 + 176) < 0)
        *(_DWORD *)(a2 + 176) = 0;
      v76 = -v112;
      v120 = v76;
      v122 = v116;
      if (v76 < colision_c_variable_10)
        v120 = 0.0099999998;
      if (v116 < colision_c_variable_10)
        v122 = 0.0099999998;
      v104 = v122 * colision_c_variable_11;
      if (v120 > (double)v104)
        v120 = v122 * colision_c_variable_11;
      v102 = v120 * colision_c_variable_11;
      if (v122 > (double)v102)
        v122 = v120 * colision_c_variable_11;
      v125 = v124 + damage_levels[damage_level];
      v77 = 1.0 / (v120 + v122);
      v100 = v120 * v125 * colision_c_variable_12 * v77;
      v103 = v77 * (v122 * v125 * colision_c_variable_12);
      if (v100 >= 1.0) {
        if ((__int16)player1_car == *(_DWORD *)(a2 + 32) || player2_car == *(_DWORD *)(a2 + 32)) {
          v78 = 48;
        LABEL_87:
          speechonly(v78, 0x8000, 18, *(_DWORD *)(a1 + 32));
          goto LABEL_88;
        }
        v79 = *(_DWORD *)(a1 + 32);
        if ((__int16)player1_car == v79 || player2_car == v79) {
          v78 = 47;
          goto LABEL_87;
        }
      }
    LABEL_88:
      if (v103 >= 1.0) {
        if ((__int16)player1_car == *(_DWORD *)(a1 + 32) || player2_car == *(_DWORD *)(a1 + 32)) {
          v80 = 48;
        } else {
          v81 = *(_DWORD *)(a2 + 32);
          if ((__int16)player1_car != v81 && player2_car != v81)
            goto LABEL_96;
          v80 = 47;
        }
        speechonly(v80, 0x8000, 18, *(_DWORD *)(a2 + 32));
      }
    LABEL_96:
      if (*(float *)(a1 + 28) > 0.0)
        *(_BYTE *)(a1 + 185) = *(_BYTE *)(a2 + 32);
      *(_BYTE *)(a1 + 187) = -40;
      if (*(float *)(a2 + 28) > 0.0)
        *(_BYTE *)(a2 + 185) = *(_BYTE *)(a1 + 32);
      *(_BYTE *)(a2 + 187) = -40;
      v90 = v100 * damage_levels[damage_level];
      dodamage(a1, v90);
      v91 = v103 * damage_levels[damage_level];
      dodamage(a2, v91);
    }
  }
}

//-------------------------------------------------------------------------------------------------

int initcollisions()
{
  int v0; // ecx
  int v1; // esi
  int v2; // ebx
  int result; // eax
  double v4; // [esp+38h] [ebp-38h]
  double v5; // [esp+40h] [ebp-30h]
  int i; // [esp+4Ch] [ebp-24h]
  int v7; // [esp+50h] [ebp-20h]
  int v8; // [esp+54h] [ebp-1Ch]

  v4 = *(float *)&CarBaseX;
  v0 = -4096;
  v1 = 0;
  v5 = *(float *)&CarBaseY;
  do {
    v2 = v1;
    for (i = -4096; i != 4352; i += 256) {
      v7 = 1600;
      v8 = 1024;
      do {
        if (!checkintersect(0.0, 0.0, (double)v0, (double)v7 - (double)v8, 0.0, (double)i, v4, v5))
          v7 -= v8;
        result = v8 / 2;
        v8 = result;
      } while (result);
      v2 += 4;
      *(float *)((char *)&result_p1_pos + v2) = (float)v7;
    }
    v0 += 256;
    v1 += 132;
  } while (v0 != 4352);
  return result;
}

//-------------------------------------------------------------------------------------------------

int __stdcall checkintersect(
        double a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        long double a7,
        long double a8)
{
  long double v8; // st6
  long double v9; // rt2
  int v10; // edx
  long double v11; // rt1
  double v13; // [esp+48h] [ebp-3Ch]
  double v14; // [esp+50h] [ebp-34h]
  double v15; // [esp+58h] [ebp-2Ch]
  double v16; // [esp+60h] [ebp-24h]
  double v17; // [esp+68h] [ebp-1Ch]
  double v18; // [esp+70h] [ebp-14h]
  long double v19; // [esp+78h] [ebp-Ch]
  long double v20; // [esp+78h] [ebp-Ch]

  v8 = (a3 - a6) * colision_c_variable_13;
  v17 = cos(v8);
  v18 = sin(v8);
  v9 = cos(a6 * colision_c_variable_13);
  v19 = sin(a6 * colision_c_variable_13);
  v13 = (a1 - a4) * v9 + (a2 - a5) * v19;
  v15 = v9 * (a2 - a5) + (a4 - a1) * v19;
  v10 = 0;
  if (fabs(v17 * a7 - v18 * a8 + v13) <= a7 && fabs(a8 * v17 + v18 * a7 + v15) <= a8)
    v10 = -1;
  if (fabs(v17 * a7 - v18 * -a8 + v13) <= a7 && fabs(-a8 * v17 + v18 * a7 + v15) <= a8)
    v10 = -1;
  if (fabs(v17 * -a7 - v18 * a8 + v13) <= a7 && fabs(-a7 * v18 + a8 * v17 + v15) <= a8)
    v10 = -1;
  if (fabs(v17 * -a7 - v18 * -a8 + v13) <= a7 && fabs(-a7 * v18 + v17 * -a8 + v15) <= a8)
    v10 = -1;
  if (fabs(v13) <= a7 && fabs(v15) <= a8)
    v10 = -1;
  HIBYTE(v18) ^= 0x80u;
  v11 = cos(a3 * colision_c_variable_13);
  v20 = sin(a3 * colision_c_variable_13);
  v16 = (a4 - a1) * v11 + (a5 - a2) * v20;
  v14 = v11 * (a5 - a2) + (a1 - a4) * v20;
  if (fabs(v17 * a7 - v18 * a8 + v16) <= a7 && fabs(v18 * a7 + a8 * v17 + v14) <= a8)
    v10 = -1;
  if (fabs(v17 * a7 - v18 * -a8 + v16) <= a7 && fabs(-a8 * v17 + v18 * a7 + v14) <= a8)
    v10 = -1;
  if (fabs(v17 * -a7 - v18 * a8 + v16) <= a7 && fabs(-a7 * v18 + a8 * v17 + v14) <= a8)
    v10 = -1;
  if (fabs(v17 * -a7 - v18 * -a8 + v16) <= a7 && fabs(-a7 * v18 + v17 * -a8 + v14) <= a8)
    v10 = -1;
  if (fabs(v16) <= a7 && fabs(v14) <= a8)
    return -1;
  return v10;
}

//-------------------------------------------------------------------------------------------------
#endif
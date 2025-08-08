#include "colision.h"
//-------------------------------------------------------------------------------------------------

int damage_level; //00189944

//-------------------------------------------------------------------------------------------------
//0005F8F0
void testcollisions()
{/*
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
  }*/
}

//-------------------------------------------------------------------------------------------------
//0005FA00
void testcoll(tCar *pCar1, tCar *pCar2, int a3)
{/*
  tData *pData2; // eax
  double v7; // st7
  double v8; // st6
  double v9; // st5
  tData *pData1; // eax
  double v11; // rt0
  double v12; // st5
  double v13; // st4
  double v14; // st7
  double v15; // rt2
  double v16; // st4
  int nDirection; // ebx
  int nCurrChunk; // eax
  int i; // edx
  int v20; // ecx
  __int16 v21; // bx
  int v22; // ebp
  __int16 v23; // ax
  int v24; // ecx
  int v25; // eax
  int v26; // edx
  tData *pData2_2; // eax
  double v28; // st7
  double v29; // st6
  double v30; // st5
  tData *pData1_1; // eax
  double v32; // rt0
  double v33; // st5
  double v34; // st4
  double v35; // st7
  double v36; // rt2
  double v37; // st4
  int v38; // eax
  __int16 v39; // dx
  int v40; // ecx
  int v41; // ebp
  int v42; // eax
  int v43; // edx
  double v44; // st7
  double v45; // st6
  double v46; // st5
  int16 v47; // ax
  tData *v48; // edx
  int v49; // eax
  int v50; // ebx
  double v51; // st4
  double v52; // st7
  double v53; // st6
  double v54; // st7
  double v55; // st6
  double v56; // st5
  double v57; // st7
  int iUnk10; // edx
  double v59; // st6
  int v60; // eax
  int iUnk45; // eax
  long double v62; // st7
  int v63; // edx
  int v64; // ebx
  long double v65; // st7
  int v66; // eax
  double v67; // st7
  double v68; // st7
  int v69; // eax
  int v70; // ecx
  int v71; // eax
  int v72; // ecx
  float v73; // [esp+0h] [ebp-CCh]
  float v74; // [esp+0h] [ebp-CCh]
  float v75; // [esp+0h] [ebp-CCh]
  float v76; // [esp+4h] [ebp-C8h]
  float v77; // [esp+4h] [ebp-C8h]
  float v78; // [esp+4h] [ebp-C8h]
  float v79; // [esp+4h] [ebp-C8h]
  float v80; // [esp+4h] [ebp-C8h]
  float v81; // [esp+4h] [ebp-C8h]
  float v82; // [esp+4h] [ebp-C8h]
  float fMaxSpeed; // [esp+18h] [ebp-B4h]
  float v84; // [esp+20h] [ebp-ACh]
  float v85; // [esp+28h] [ebp-A4h]
  float v86; // [esp+2Ch] [ebp-A0h]
  float v87; // [esp+38h] [ebp-94h]
  float v88; // [esp+38h] [ebp-94h]
  float v89; // [esp+44h] [ebp-88h]
  float v90; // [esp+44h] [ebp-88h]
  float v91; // [esp+50h] [ebp-7Ch]
  float v92; // [esp+58h] [ebp-74h]
  float v93; // [esp+5Ch] [ebp-70h]
  float v94; // [esp+60h] [ebp-6Ch]
  float v95; // [esp+64h] [ebp-68h]
  float v96; // [esp+68h] [ebp-64h]
  int16 v97; // [esp+6Ch] [ebp-60h]
  int v98; // [esp+70h] [ebp-5Ch]
  float v99; // [esp+74h] [ebp-58h]
  float v100; // [esp+78h] [ebp-54h]
  float v101; // [esp+7Ch] [ebp-50h]
  float v102; // [esp+80h] [ebp-4Ch]
  float v103; // [esp+84h] [ebp-48h]
  float v104; // [esp+88h] [ebp-44h]
  float fY; // [esp+8Ch] [ebp-40h]
  float v106; // [esp+90h] [ebp-3Ch]
  float v107; // [esp+94h] [ebp-38h]
  float fX; // [esp+98h] [ebp-34h]
  float v109; // [esp+9Ch] [ebp-30h]
  float fUnk25; // [esp+A0h] [ebp-2Ch]
  float v111; // [esp+A4h] [ebp-28h]
  int v112; // [esp+A8h] [ebp-24h]
  float v113; // [esp+ACh] [ebp-20h]
  int v114; // [esp+B0h] [ebp-1Ch]
  float v115; // [esp+B4h] [ebp-18h]
  float v116; // [esp+B4h] [ebp-18h]

  fX = pCar1->pos.fX;
  fY = pCar1->pos.fY;
  pData2 = &localdata[pCar2->nCurrChunk];
  v7 = pData2->pointAy[0].fY * pCar2->pos.fY
    + pData2->pointAy[0].fX * pCar2->pos.fX
    + pData2->pointAy[0].fZ * pCar2->pos.fZ
    - pData2->pointAy[3].fX;
  v8 = pData2->pointAy[1].fY * pCar2->pos.fY
    + pData2->pointAy[1].fX * pCar2->pos.fX
    + pData2->pointAy[1].fZ * pCar2->pos.fZ
    - pData2->pointAy[3].fY;
  v9 = pData2->pointAy[2].fY * pCar2->pos.fY
    + pData2->pointAy[2].fX * pCar2->pos.fX
    + pData2->pointAy[2].fZ * pCar2->pos.fZ
    - pData2->pointAy[3].fZ;
  pData1 = &localdata[pCar1->nCurrChunk];
  v11 = v9;
  v12 = v8 + pData1->pointAy[3].fY;
  v13 = v7 + pData1->pointAy[3].fX;
  v14 = pData1->pointAy[1].fX * v12 + pData1->pointAy[0].fX * v13;
  v15 = v13;
  v16 = v11 + pData1->pointAy[3].fZ;
  v87 = v14 + pData1->pointAy[2].fX * v16;
  v89 = v16 * pData1->pointAy[2].fY + v15 * pData1->pointAy[0].fY + v12 * pData1->pointAy[1].fY;
  v104 = v87;
  v106 = v89;
  nDirection = pCar2->nDirection;
  v97 = pCar1->nDirection;
  nCurrChunk = pCar1->nCurrChunk;
  for (i = 0; i < a3; ++i) {
    v20 = nCurrChunk++ << 7;
    nDirection += *(int *)((char *)&localdata[0].iUnk16 + v20);
    if (nCurrChunk == TRAK_LEN)
      nCurrChunk ^= TRAK_LEN;
  }
  v76 = v89 - fY;
  v73 = v87 - fX;
  v21 = nDirection & 0x3FFF;
  v22 = 0;
  v23 = getangle(v73, v76);
  v24 = (v97 - v23) & 0x3FFF;
  v25 = (v21 - v23) & 0x3FFF;
  v26 = v24;
  if (v24 > 0x2000)
    v26 = v24 - 0x2000;
  if (v25 > 0x2000)
    v25 -= 0x2000;
  if (v26 > 4096)
    v26 -= 0x2000;
  if (v25 > 4096)
    v25 -= 0x2000;
  if (coldist[33 * (((v26 << 6) + 270336) >> 14) + (((v25 << 6) + 270336) >> 14)] > sqrt(
    (v87 - fX) * (v87 - fX)
    + (v89 - fY) * (v89 - fY)))
    v22 = -1;
  if (v22) {
    v84 = pCar1->pos2.fX;
    v85 = pCar1->pos2.fY;
    pData2_2 = &localdata[pCar2->nUnk4];
    v28 = pData2_2->pointAy[0].fY * pCar2->pos2.fY
      + pData2_2->pointAy[0].fX * pCar2->pos2.fX
      + pData2_2->pointAy[0].fZ * pCar2->pos2.fZ
      - pData2_2->pointAy[3].fX;
    v29 = pData2_2->pointAy[1].fX * pCar2->pos2.fX
      + pData2_2->pointAy[1].fY * pCar2->pos2.fY
      + pData2_2->pointAy[1].fZ * pCar2->pos2.fZ
      - pData2_2->pointAy[3].fY;
    v30 = pData2_2->pointAy[2].fX * pCar2->pos2.fX
      + pData2_2->pointAy[2].fY * pCar2->pos2.fY
      + pData2_2->pointAy[2].fZ * pCar2->pos2.fZ
      - pData2_2->pointAy[3].fZ;
    pData1_1 = &localdata[pCar1->nUnk4];
    v32 = v30;
    v33 = v29 + pData1_1->pointAy[3].fY;
    v34 = v28 + pData1_1->pointAy[3].fX;
    v35 = pData1_1->pointAy[1].fX * v33 + pData1_1->pointAy[0].fX * v34;
    v36 = v34;
    v37 = v32 + pData1_1->pointAy[3].fZ;
    v88 = v35 + pData1_1->pointAy[2].fX * v37;
    v90 = v37 * pData1_1->pointAy[2].fY + v36 * pData1_1->pointAy[0].fY + v33 * pData1_1->pointAy[1].fY;
    v77 = v106 - fY;
    v74 = v104 - fX;
    v38 = getangle(v74, v77);
    v78 = v90 - v85;
    v75 = v88 - v84;
    v39 = v38;
    v40 = v38;
    v98 = getangle(v75, v78);
    v41 = (v97 - v39) & 0x3FFF;
    v42 = (v21 - v39) & 0x3FFF;
    v43 = v41;
    if (v41 > 0x2000)
      v43 = v41 - 0x2000;
    if (v42 > 0x2000)
      v42 -= 0x2000;
    if (v43 > 4096)
      v43 -= 0x2000;
    if (v42 > 4096)
      v42 -= 0x2000;
    v44 = coldist[33 * (((v43 << 6) + 270336) >> 14) + (((v42 << 6) + 270336) >> 14)] + colision_c_variable_1;
    v45 = (fX + v104) * colision_c_variable_2;
    v46 = (fY + v106) * colision_c_variable_2;
    pCar1->pos.fX = v45 - v44 * tcos[v40] * colision_c_variable_2;
    pCar1->pos.fY = v46 - v44 * tsin[v40] * colision_c_variable_2;
    pCar2->pos.fX = v45 + v44 * tcos[v40] * colision_c_variable_2;
    pCar2->pos.fY = v46 + v44 * tsin[v40] * colision_c_variable_2;
    v47 = pCar1->nCurrChunk;
    pCar2->nCurrChunk = v47;
    v48 = &localdata[v47];
    if (fabs(pCar1->pos.fX) > v48->fUnk13)
      scansection(pCar1);
    if (fabs(pCar2->pos.fX) > v48->fUnk13)
      scansection(pCar2);
    fMaxSpeed = pCar1->fMaxSpeed;
    v49 = (v97 - (_WORD)v98) & 0x3FFF;
    v107 = fMaxSpeed * tcos[v49];
    v96 = fMaxSpeed * tsin[v49];
    v86 = pCar2->fMaxSpeed;
    v50 = (v21 - (_WORD)v98) & 0x3FFF;
    v103 = v86 * tcos[v50];
    v92 = v86 * tsin[v50];
    if (v103 < (double)v107) {
      fUnk25 = CarEngines.engines[pCar1->byCarDesignIdx].fUnk25;
      v109 = CarEngines.engines[pCar2->byCarDesignIdx].fUnk25;
      v51 = 1.0 / (fUnk25 + v109);
      v52 = ((fUnk25 - v109 * colision_c_variable_3) * v107 + v109 * colision_c_variable_4 * v103) * v51;
      v102 = v52 * tcos[v98] - v96 * tsin[v98];
      v53 = v52 * tsin[v98] + v96 * tcos[v98];
      v54 = (v103 * (v109 - fUnk25 * colision_c_variable_3) + v107 * (fUnk25 * colision_c_variable_4)) * v51;
      v99 = v53;
      v100 = v54 * tcos[v98] - v92 * tsin[v98];
      v112 = ((unsigned __int16)pCar1->iAngleIdx15 - (_WORD)v40) & 0x3FFF;
      v101 = v54 * tsin[v98] + v92 * tcos[v98];
      if ((unsigned int)v112 > 0x2000)
        v112 = (((unsigned __int16)pCar1->iAngleIdx15 - (_WORD)v40) & 0x3FFF) - 0x4000;
      v114 = ((unsigned __int16)pCar2->iAngleIdx15 - (_WORD)v40) & 0x3FFF;
      if ((unsigned int)v114 > 0x2000)
        v114 = (((unsigned __int16)pCar2->iAngleIdx15 - (_WORD)v40) & 0x3FFF) - 0x4000;
      v115 = fabs(v103 - v107);
      v55 = 1.0 / ((v109 + fUnk25) * colision_c_variable_6);
      v56 = v109 * colision_c_variable_5 * (double)v114 * v115 * v55;
      _CHP();
      pCar1->iUnk16 = (int)v56;
      v57 = v55 * (fUnk25 * colision_c_variable_5 * (double)v112 * v115);
      _CHP();
      pCar2->iUnk16 = (int)v57;
      if (pCar1->iUnk16 > 1300)
        pCar1->iUnk16 = 1300;
      if (pCar2->iUnk16 > 1300)
        pCar2->iUnk16 = 1300;
      if (pCar1->iUnk16 < -1300)
        pCar1->iUnk16 = -1300;
      if (pCar2->iUnk16 < -1300)
        pCar2->iUnk16 = -1300;
      if (ViewType[0] == pCar1->iUnk10 || ViewType[0] == pCar2->iUnk10)
        iUnk10 = ViewType[0];
      else
        iUnk10 = pCar1->iUnk10;
      v59 = v115 * colision_c_variable_7 * colision_c_variable_8;
      _CHP();
      if (v115 >= (double)colision_c_variable_9)
        v60 = 8;
      else
        v60 = 7;
      sfxpend(v60, iUnk10, (int)v59);
      pCar1->iAngleIdx15 = getangle(v102, v99);
      pCar2->iAngleIdx15 = getangle(v100, v101);
      v79 = sqrt(v102 * v102 + v99 * v99);
      SetEngine((int)pCar1, v79);
      v80 = sqrt(v100 * v100 + v101 * v101);
      SetEngine((int)pCar2, v80);
      iUnk45 = pCar1->iUnk45;
      if (iUnk45) {
        if (iUnk45 != 2)
          changestrategy((int)pCar1);
        v63 = 0;
      } else {
        v62 = fabs(tsin[v112 & 0x3FFF]);
        _CHP();
        v63 = 18 * (int)v62;
      }
      v64 = pCar2->iUnk45;
      if (v64) {
        if (v64 != 2)
          changestrategy((int)pCar2);
        v66 = 0;
      } else {
        v65 = fabs(tsin[v114 & 0x3FFF]);
        _CHP();
        v66 = 18 * (int)v65;
      }
      if (human_control[pCar1->iUnk10] && pCar2->byCarDesignIdx != 13)
        v66 += 18;
      if (human_control[pCar2->iUnk10] && pCar1->byCarDesignIdx != 13)
        v63 += 18;
      if (pCar1->iPadding13 < 144)
        pCar1->iPadding13 = v63;
      if (pCar1->iPadding13 < 0)
        pCar1->iPadding13 = 0;
      if (pCar2->iPadding13 < 144)
        pCar2->iPadding13 = v66;
      if (pCar2->iPadding13 < 0)
        pCar2->iPadding13 = 0;
      v67 = -v103;
      v111 = v67;
      v113 = v107;
      if (v67 < colision_c_variable_10)
        v111 = 0.0099999998;
      if (v107 < colision_c_variable_10)
        v113 = 0.0099999998;
      v95 = v113 * colision_c_variable_11;
      if (v111 > (double)v95)
        v111 = v113 * colision_c_variable_11;
      v93 = v111 * colision_c_variable_11;
      if (v113 > (double)v93)
        v113 = v111 * colision_c_variable_11;
      v116 = v115 + damage_levels[damage_level];
      v68 = 1.0 / (v111 + v113);
      v91 = v111 * v116 * colision_c_variable_12 * v68;
      v94 = v68 * (v113 * v116 * colision_c_variable_12);
      if (v91 >= 1.0) {
        if (player1_car == pCar2->iUnk10 || player2_car == pCar2->iUnk10) {
          v69 = 48;
        LABEL_87:
          speechonly(v69, 0x8000, 18, pCar1->iUnk10);
          goto LABEL_88;
        }
        v70 = pCar1->iUnk10;
        if (player1_car == v70 || player2_car == v70) {
          v69 = 47;
          goto LABEL_87;
        }
      }
    LABEL_88:
      if (v94 >= 1.0) {
        if (player1_car == pCar1->iUnk10 || player2_car == pCar1->iUnk10) {
          v71 = 48;
        } else {
          v72 = pCar2->iUnk10;
          if (player1_car != v72 && player2_car != v72)
            goto LABEL_96;
          v71 = 47;
        }
        speechonly(v71, 0x8000, 18, pCar2->iUnk10);
      }
    LABEL_96:
      if (pCar1->fUnk9 > 0.0)
        pCar1->byUnk41 = pCar2->iUnk10;
      pCar1->byUnk43 = -40;
      if (pCar2->fUnk9 > 0.0)
        pCar2->byUnk41 = pCar1->iUnk10;
      pCar2->byUnk43 = -40;
      v81 = v91 * damage_levels[damage_level];
      dodamage((int)pCar1, v81);
      v82 = v94 * damage_levels[damage_level];
      dodamage((int)pCar2, v82);
    }
  }*/
}

//-------------------------------------------------------------------------------------------------
//000604B0
void initcollisions()
{/*
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
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//000605C0
int checkintersect(
        double a1,
        double a2,
        double dAngleIdx1,
        double a4,
        double a5,
        double dAngleIdx2,
        long double ldCarBaseX,
        long double ldCarBaseY)
{
  return 0;/*
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
  return v10;*/
}

//-------------------------------------------------------------------------------------------------
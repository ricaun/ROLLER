
//-------------------------------------------------------------------------------------------------

int __fastcall calculateview(int a1, int a2, int a3)
{
  int v4; // esi
  unsigned int v5; // eax
  int v6; // eax
  float *v7; // eax
  int v8; // edx
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  double v13; // st7
  int v14; // eax
  double v15; // st7
  double v16; // st6
  double v17; // st4
  long double v18; // st3
  int v19; // eax
  int result; // eax
  float v21; // edx
  int v22; // eax
  float *v23; // eax
  int v24; // eax
  float *v25; // eax
  int v26; // eax
  int v27; // edi
  int v28; // edi
  int v29; // [esp-18h] [ebp-E4h]
  int v30; // [esp-14h] [ebp-E0h]
  int v31; // [esp-10h] [ebp-DCh]
  double v32; // [esp+0h] [ebp-CCh]
  double v33; // [esp+8h] [ebp-C4h]
  double v34; // [esp+10h] [ebp-BCh]
  float v35; // [esp+2Ch] [ebp-A0h]
  float v36; // [esp+30h] [ebp-9Ch]
  float v37; // [esp+34h] [ebp-98h]
  float v38; // [esp+38h] [ebp-94h]
  float v39; // [esp+3Ch] [ebp-90h]
  float v40; // [esp+40h] [ebp-8Ch]
  float v41; // [esp+44h] [ebp-88h]
  int v42; // [esp+48h] [ebp-84h]
  int v43; // [esp+4Ch] [ebp-80h]
  float v44; // [esp+50h] [ebp-7Ch]
  float v45; // [esp+54h] [ebp-78h]
  int v46; // [esp+58h] [ebp-74h]
  float v47; // [esp+5Ch] [ebp-70h]
  float v48; // [esp+60h] [ebp-6Ch]
  float v49; // [esp+64h] [ebp-68h]
  int v50; // [esp+6Ch] [ebp-60h]
  float v51; // [esp+70h] [ebp-5Ch]
  float v52; // [esp+74h] [ebp-58h]
  float v53; // [esp+78h] [ebp-54h]
  float v54; // [esp+7Ch] [ebp-50h]
  float v55; // [esp+80h] [ebp-4Ch]
  float v56; // [esp+84h] [ebp-48h]
  float v57; // [esp+88h] [ebp-44h]
  float v58; // [esp+8Ch] [ebp-40h]
  float v59; // [esp+90h] [ebp-3Ch]
  int v60; // [esp+94h] [ebp-38h]
  float v61; // [esp+98h] [ebp-34h]
  float v62; // [esp+9Ch] [ebp-30h]
  float v63; // [esp+A0h] [ebp-2Ch]
  int v64; // [esp+A4h] [ebp-28h]
  int v65; // [esp+A8h] [ebp-24h]
  float v66; // [esp+ACh] [ebp-20h]
  float v67; // [esp+B0h] [ebp-1Ch]
  float v68; // [esp+B4h] [ebp-18h]
  float v69; // [esp+B8h] [ebp-14h]
  float v70; // [esp+B8h] [ebp-14h]

  VIEWDIST = 200;
  v4 = -1;
  if (a1 < -1) {
    if (a1 != -2)
      goto LABEL_8;
  LABEL_6:
    ext_x = 1093664768;
    ext_y = 0;
    ext_z = 1091567616;
    goto LABEL_9;
  }
  if (a1 <= 0) {
    ext_x = 0;
    ext_y = 0;
    ext_z = 1077936128;
    goto LABEL_9;
  }
  if (a1 == 1)
    goto LABEL_6;
LABEL_8:
  ext_x = -1082130432;
  ext_y = -1082130432;
  ext_z = -1082130432;
LABEL_9:
  v5 = 154 * a2;
  if (a1 < 3) {
    if (a1 >= 0) {
      mirror = 0;
      if (a1 == 1) {
        if (Car_variable_48[77 * a2])
          v27 = Car_variable_36[77 * a2] + Car_variable_6[154 * a2];
        else
          v27 = Car_variable_34[77 * a2] + Car_variable_36[77 * a2] + Car_variable_6[154 * a2];
        v64 = ((_WORD)v27 + 0x2000) & 0x3FFF;
        v26 = Car_variable_35[77 * a2] + Car_variable_37[77 * a2] + Car_variable_5[154 * a2] + 0x2000;
      } else {
        if (Car_variable_48[77 * a2])
          v28 = Car_variable_36[77 * a2] + Car_variable_6[154 * a2];
        else
          v28 = Car_variable_34[77 * a2] + Car_variable_36[77 * a2] + Car_variable_6[154 * a2];
        v64 = ((_WORD)v28 + 455) & 0x3FFF;
        v26 = Car_variable_35[77 * a2] + Car_variable_37[77 * a2] + Car_variable_5[154 * a2];
      }
    } else {
      mirror = -1;
      v64 = (LOWORD(Car_variable_36[77 * a2]) + Car_variable_6[154 * a2] + 0x2000) & 0x3FFF;
      v26 = Car_variable_37[77 * a2] + Car_variable_5[154 * a2] + 0x2000;
    }
    v60 = v26 & 0x3FFF;
    NearTow = -1;
    if (a1 == 2)
      return newchaseview(a2, a3);
    v36 = *(float *)&ext_y * view_c_variable_1;
    v37 = *(float *)&ext_z * view_c_variable_2;
    v35 = *(float *)&ext_x * view_c_variable_1;
    v38 = DDX + v36;
    v40 = DDY + v37;
    v39 = DDZ - v35;
    if (a1 == 1) {
      v31 = LODWORD(Car_variable_2[77 * a2]);
      v30 = LODWORD(Car_variable_1[77 * a2]);
      v29 = LODWORD(Car[77 * a2]);
      VIEWDIST = 120;
      calculatetransform(v29, v30, v31, v38, v40, v39);
      if (Car_variable_3[154 * a2] == -1) {
        worlddirn = Car_variable_7[154 * a2];
        worldelev = v64;
        result = v60;
        worldtilt = v60;
        return result;
      }
    } else {
      calculatetransform(
        LODWORD(Car[77 * a2]),
        LODWORD(Car_variable_1[77 * a2]),
        LODWORD(Car_variable_2[77 * a2]),
        v38,
        v40,
        v39);
      if (Car_variable_3[154 * a2] == -1) {
        worlddirn = Car_variable_7[154 * a2];
        worldelev = v64;
        result = v60;
        worldtilt = v60;
        return result;
      }
    }
    return getworldangles(&worlddirn, &worldelev, &worldtilt);
  } else if (a1 == 3) {
    v55 = Car[77 * a2];
    v49 = Car_variable_1[77 * a2];
    v6 = Car_variable_3[154 * a2];
    v52 = Car_variable_2[77 * a2];
    v65 = v6;
    if (v6 == -1) {
      v62 = Car[77 * a2];
      v63 = Car_variable_2[77 * a2];
      v61 = Car_variable_1[77 * a2];
    } else {
      v7 = (float *)((char *)&localdata + 128 * v6);
      v62 = v7[1] * v49 + *v7 * v55 + v7[2] * v52 - v7[9];
      v61 = v7[3] * v55 + v7[4] * v49 + v7[5] * v52 - v7[10];
      v63 = v49 * v7[7] + v55 * v7[6] + v52 * v7[8] - v7[11];
    }
    if (NumTowers <= 0) {
      v13 = v63 + view_c_variable_4;
      worldx = LODWORD(v62);
      v12 = LODWORD(v61);
      worldy = LODWORD(v61);
    LABEL_39:
      *(float *)&worldz = v13;
    } else {
      if (v65 == -1)
        v65 = Car_variable_51[77 * a2];
      v4 = 0;
      v8 = 0;
      v67 = 9.9999998e17;
      if (NumTowers > 0) {
        v9 = 0;
        do {
          v69 = (float)TowerBase[v9];
          v70 = (double)v65 - v69;
          v66 = (float)TRAK_LEN;
          v34 = fabs(v70 - v66);
          v32 = fabs(v70);
          if (v32 >= v34) {
            v10 = HIDWORD(v34);
            LODWORD(v33) = LODWORD(v34);
          } else {
            v10 = HIDWORD(v32);
            LODWORD(v33) = LODWORD(v32);
          }
          HIDWORD(v33) = v10;
          if (v33 < v67) {
            v4 = v8;
            v68 = v33;
            v67 = v68;
          }
          ++v8;
          v9 += 5;
        } while (v8 < NumTowers);
      }
      worldx = LODWORD(TowerX[v4]);
      worldy = LODWORD(TowerY[v4]);
      v11 = TowerBase_variable_4[5 * v4] - 1;
      worldz = SLODWORD(TowerZ[v4]);
      switch (v11) {
        case 0:
          VIEWDIST = 120;
          break;
        case 1:
          VIEWDIST = 75;
          break;
        case 2:
          VIEWDIST = 500;
          break;
        case 3:
          VIEWDIST = 750;
          break;
        default:
          break;
      }
      v12 = 20 * v4;
      a2 = TowerBase_variable_3[5 * v4] + 5;
      switch (TowerBase_variable_3[5 * v4]) {
        case -5:
          v12 = TowerBase_variable_2[5 * v4] << 7;
          v13 = (double)v12 + v63;
          worldx = LODWORD(v62);
          a2 = LODWORD(v61);
          worldy = LODWORD(v61);
          goto LABEL_39;
        case -4:
          v14 = TowerBase[5 * v4] - 2;
          if (v14 < 0)
            v14 += TRAK_LEN;
          v12 = (int)&localdata + 128 * v14;
          v62 = -*(float *)(v12 + 36);
          v61 = -*(float *)(v12 + 40);
          v63 = -*(float *)(v12 + 44);
          break;
        case -3:
        case 2:
          v15 = *(float *)&worldx - v62;
          v16 = *(float *)&worldy - v61;
          v17 = *(float *)&worldz - v63;
          v18 = 1.0 / sqrt(v15 * v15 + v16 * v16 + v17 * v17);
          *(float *)&worldx = v15 * view_c_variable_7 * v18 + v62;
          *(float *)&worldy = v16 * view_c_variable_7 * v18 + v61;
          *(float *)&worldz = v18 * (v17 * view_c_variable_7) + v63;
          break;
        case -2:
        case 1:
          *(float *)&worldx = (*(float *)&worldx - v62) * view_c_variable_6 + v62;
          *(float *)&worldy = v61 + (*(float *)&worldy - v61) * view_c_variable_6;
          v13 = (*(float *)&worldz - v63) * view_c_variable_6 + v63;
          goto LABEL_39;
        case 0:
          v13 = *(float *)&worldz + view_c_variable_5;
          goto LABEL_39;
        default:
          break;
      }
    }
    TowerGx = worldx;
    TowerGy = worldy;
    TowerGz = worldz;
    v48 = v62 - *(float *)&worldx;
    *(float *)&v50 = v61 - *(float *)&worldy;
    NearTow = v4;
    *(float *)&v43 = v63 - *(float *)&worldz;
    if ((LODWORD(v48) & 0x7FFFFFFF) != 0 || fabs(v61 - *(float *)&worldy)) {
      v12 = getangle(v12, a2, v48, v50);
      vdirection = v12;
    } else {
      vdirection = 0;
    }
    v44 = sqrt(v48 * v48 + *(float *)&v50 * *(float *)&v50);
    if ((LODWORD(v44) & 0x7FFFFFFF) != 0 || (v43 & 0x7FFFFFFF) != 0)
      v19 = getangle(v12, a2, v44, v43);
    else
      v19 = 0;
    velevation = v19;
    vtilt = 0;
    calculatetransform(worldx, worldy, worldz, DDX, DDY, DDZ);
    worlddirn = vdirection;
    worldelev = velevation;
    result = vtilt;
    worldtilt = vtilt;
  } else {
    if (a1 == 6) {
      *(float *)&worldx = -localdata_variable_16;
      *(float *)&worldy = -localdata_variable_17;
      VIEWDIST = 400;
      v51 = Car[77 * a2];
      v53 = Car_variable_1[77 * a2];
      v21 = Car_variable_2[77 * a2];
      v56 = Car_variable_2[v5 / 2];
      v22 = Car_variable_3[v5];
      *(float *)&worldz = view_c_variable_3 - localdata_variable_18;
      if (v22 == -1) {
        v58 = v51;
        v23 = (float *)LODWORD(v53);
        v57 = v21;
        v59 = v53;
      } else {
        v23 = (float *)((char *)&localdata + 128 * v22);
        v58 = v23[1] * v53 + *v23 * v51 + v23[2] * v56 - v23[9];
        v59 = v23[3] * v51 + v23[4] * v53 + v23[5] * v56 - v23[10];
        v57 = v53 * v23[7] + v51 * v23[6] + v56 * v23[8] - v23[11];
      }
    } else {
      v54 = Car[77 * a2];
      v47 = Car_variable_1[77 * a2];
      v21 = Car_variable_2[77 * a2];
      v24 = Car_variable_3[v5];
      if (v24 == -1) {
        v58 = v54;
        v57 = v21;
        v59 = v47;
      } else {
        v25 = (float *)((char *)&localdata + 128 * v24);
        v58 = v25[1] * v47 + *v25 * v54 + v25[2] * v21 - v25[9];
        v59 = v25[3] * v54 + v25[4] * v47 + v25[5] * v21 - v25[10];
        v57 = v47 * v25[7] + v54 * v25[6] + v21 * v25[8] - v25[11];
      }
      worldx = LODWORD(v58);
      v23 = (float *)LODWORD(v59);
      worldy = LODWORD(v59);
      *(float *)&worldz = TopViewHeight + v57;
    }
    v45 = v58 - *(float *)&worldx;
    *(float *)&v46 = v59 - *(float *)&worldy;
    NearTow = -1;
    *(float *)&v42 = v57 - *(float *)&worldz;
    if ((LODWORD(v45) & 0x7FFFFFFF) != 0 || fabs(v59 - *(float *)&worldy)) {
      v23 = (float *)getangle((int)v23, SLODWORD(v21), v45, v46);
      vdirection = (int)v23;
    } else {
      vdirection = 0;
    }
    v41 = sqrt(v45 * v45 + *(float *)&v46 * *(float *)&v46);
    if ((LODWORD(v41) & 0x7FFFFFFF) != 0 || (v42 & 0x7FFFFFFF) != 0)
      velevation = getangle((int)v23, SLODWORD(v21), v41, v42);
    else
      velevation = 0;
    vtilt = 0;
    calculatetransform(worldx, worldy, worldz, DDX, DDY, DDZ);
    worlddirn = vdirection;
    worldelev = velevation;
    result = vtilt;
    worldtilt = vtilt;
  }
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall initcarview(int result, int a2)
{
  int v2; // ecx
  int v3; // esi
  unsigned int v4; // ebx
  float v5; // esi
  int v6; // esi
  int v7; // edi
  int v8; // ecx
  double v9; // st7
  double v10; // st7
  int v11; // eax
  float *v12; // eax
  double v13; // st7
  double v14; // st7
  float v15; // [esp+0h] [ebp-3Ch]
  float v16; // [esp+4h] [ebp-38h]
  float v17; // [esp+8h] [ebp-34h]
  float v18; // [esp+Ch] [ebp-30h]
  float v19; // [esp+10h] [ebp-2Ch]
  float v20; // [esp+14h] [ebp-28h]
  float v21; // [esp+18h] [ebp-24h]
  float v22; // [esp+1Ch] [ebp-20h]
  float v23; // [esp+20h] [ebp-1Ch]

  v2 = SelectedView[a2];
  if (v2 != 1 && v2 != 3 && result >= 0)
    return result;
  if (result >= 0) {
    v3 = chaseview[a2];
    CHASE_DIST[a2] = viewdata[6 * v3];
    CHASE_MIN[a2] = viewdata_variable_1[6 * v3];
    LODWORD(LOOKZ[a2]) = viewdata_variable_5[6 * v3];
  } else {
    CHASE_DIST[0] = viewdata_variable_6;
    CHASE_MIN[0] = viewdata_variable_7;
    a2 = 0;
    result = -result - 1;
    LOOKZ[0] = viewdata_variable_8;
  }
  v4 = Car_variable_17[77 * result];
  if (!v4) {
    v5 = viewdata_variable_4[6 * chaseview[a2]];
  LABEL_14:
    PULLZ[a2] = v5;
    goto LABEL_15;
  }
  if (v4 >= 2 && v4 <= 3) {
    if (Car_variable_48[77 * result])
      v5 = viewdata_variable_3[6 * chaseview[a2]];
    else
      v5 = viewdata_variable_2[6 * chaseview[a2]];
    goto LABEL_14;
  }
LABEL_15:
  if (Car_variable_3[154 * result] == -1) {
    v6 = Car_variable_7[154 * result];
    v7 = Car_variable_6[154 * result];
    v8 = Car_variable_5[154 * result];
  } else {
    v6 = 0;
    v7 = 0;
    v8 = 0;
  }
  v20 = tsin[v7];
  if (replaytype == 2 && replaydirection == -1)
    v9 = -*(float *)&CHASE_DIST[a2];
  else
    v9 = *(float *)&CHASE_DIST[a2];
  v10 = -(v9 * view_c_variable_8);
  v15 = -tcos[v6] * v20 * tcos[v8] - tsin[v6] * tsin[v8];
  v16 = tcos[v6] * tcos[v7];
  v21 = v10 * v16 + PULLZ[a2] * v15 + Car[77 * result];
  v17 = tsin[v6] * tcos[v7];
  v18 = -tsin[v6] * v20 * tcos[v8] + tcos[v6] * tsin[v8];
  v23 = v10 * v17 + PULLZ[a2] * v18 + Car_variable_1[77 * result];
  v19 = tcos[v7] * tcos[v8];
  v22 = v10 * v20 + PULLZ[a2] * v19 + Car_variable_2[77 * result];
  v11 = Car_variable_3[154 * result];
  if (v11 == -1) {
    chase_x = v21;
    chase_y = v23;
    lastpos_variable_3[256 * a2] = 0;
    chase_z = v22;
    *(float *)&lastpos[256 * a2] = v21;
    lastpos_variable_1[256 * a2] = v23;
    lastpos_variable_2[256 * a2] = v22;
  } else {
    v12 = (float *)((char *)&localdata + 128 * v11);
    chase_x = v12[1] * v23 + *v12 * v21 + v12[2] * v22 - v12[9];
    chase_y = v12[3] * v21 + v12[4] * v23 + v12[5] * v22 - v12[10];
    chase_z = v12[6] * v21 + v12[7] * v23 + v12[8] * v22 - v12[11];
    lastpos[256 * a2] = LODWORD(chase_x);
    lastpos_variable_1[256 * a2] = v12[3] * v21 + v12[4] * v23 + v12[5] * v22 - v12[10];
    v13 = v23 * v12[7] + v21 * v12[6] + v22 * v12[8] - v12[11];
    lastpos_variable_3[256 * a2] = 0;
    lastpos_variable_2[256 * a2] = v13;
  }
  result = a2 << 10;
  *(int *)((char *)&lastpos_variable_4 + result) = lastpos[256 * a2];
  *(int *)((char *)&lastpos_variable_5 + result) = LODWORD(lastpos_variable_1[256 * a2]);
  *(int *)((char *)&lastpos_variable_6 + result) = LODWORD(lastpos_variable_2[256 * a2]);
  v14 = *(float *)&lastpos_variable_3[256 * a2];
  nextpoint[a2] = 1;
  *(float *)((char *)&lastpos_variable_7 + result) = v14;
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall newchaseview(int a1, int a2)
{
  unsigned int v3; // eax
  int v4; // ebx
  int v5; // ecx
  int v6; // edx
  double v7; // st7
  double v8; // st6
  double v9; // st5
  int v10; // eax
  float *v11; // eax
  float v12; // edx
  double v13; // st7
  float v14; // edx
  float v15; // edx
  double v16; // st7
  float v17; // edx
  int v18; // eax
  int v19; // eax
  int v20; // edx
  long double v21; // st7
  int v22; // edx
  int v23; // edx
  int v24; // ebx
  int v25; // edx
  double v26; // st7
  int v27; // eax
  int v28; // edi
  int v29; // edx
  int v30; // eax
  int v31; // eax
  int v32; // edi
  int v33; // eax
  int v34; // edx
  int v35; // eax
  int v36; // eax
  int result; // eax
  float v38; // [esp+8h] [ebp-88h]
  float v39; // [esp+8h] [ebp-88h]
  float v40; // [esp+18h] [ebp-78h]
  float v41; // [esp+24h] [ebp-6Ch]
  float v42; // [esp+28h] [ebp-68h]
  float v43; // [esp+2Ch] [ebp-64h]
  float v44; // [esp+30h] [ebp-60h]
  float v45; // [esp+34h] [ebp-5Ch]
  float v46; // [esp+38h] [ebp-58h]
  int v47; // [esp+3Ch] [ebp-54h]
  float v48; // [esp+40h] [ebp-50h]
  float v49; // [esp+44h] [ebp-4Ch]
  int v50; // [esp+48h] [ebp-48h]
  int v51; // [esp+4Ch] [ebp-44h]
  int v52; // [esp+50h] [ebp-40h]
  int v53; // [esp+54h] [ebp-3Ch]
  float v54; // [esp+58h] [ebp-38h]
  int v55; // [esp+5Ch] [ebp-34h]
  float v56; // [esp+60h] [ebp-30h]
  float v57; // [esp+64h] [ebp-2Ch]
  int v58; // [esp+68h] [ebp-28h]
  float v59; // [esp+6Ch] [ebp-24h]
  float v60; // [esp+70h] [ebp-20h]
  float v61; // [esp+74h] [ebp-1Ch]
  float v62; // [esp+78h] [ebp-18h]

  v3 = 308 * a1;
  v4 = Car_variable_7[v3 / 2];
  v5 = Car_variable_6[v3 / 2];
  v42 = Car[v3 / 4];
  v41 = Car_variable_1[v3 / 4];
  v40 = Car_variable_2[v3 / 4];
  v6 = Car_variable_5[v3 / 2];
  v7 = -tcos[v4] * tsin[v5] * tcos[v6] - tsin[v4] * tsin[v6];
  v8 = -tsin[v4] * tsin[v5] * tcos[v6] + tcos[v4] * tsin[v6];
  v9 = tcos[v5] * tcos[v6];
  *(float *)&v58 = PULLZ[a2] * v7 + v42;
  v59 = PULLZ[a2] * v8 + v41;
  v60 = PULLZ[a2] * v9 + v40;
  v54 = v7 * LOOKZ[a2] + v42;
  v56 = v8 * LOOKZ[a2] + v41;
  v10 = Car_variable_3[v3 / 2];
  v57 = v9 * LOOKZ[a2] + v40;
  if (v10 != -1) {
    v11 = (float *)((char *)&localdata + 128 * v10);
    v12 = v7 * LOOKZ[a2] + v42;
    v54 = v11[1] * v56 + *v11 * v54 + v11[2] * v57 - v11[9];
    v38 = v12;
    v13 = v11[3] * v12 + v11[4] * v56 + v11[5] * v57 - v11[10];
    v14 = v8 * LOOKZ[a2] + v41;
    v56 = v13;
    v57 = v11[6] * v38 + v11[7] * v14 + v11[8] * v57 - v11[11];
    v15 = *(float *)&v58;
    *(float *)&v58 = v11[1] * v59 + *v11 * *(float *)&v58 + v11[2] * v60 - v11[9];
    v39 = v15;
    v16 = v11[3] * v15 + v11[4] * v59 + v11[5] * v60 - v11[10];
    v17 = PULLZ[a2] * v8 + v41;
    v59 = v16;
    v60 = v11[6] * v39 + v11[7] * v17 + v11[8] * v60 - v11[11];
  }
  v18 = nextpoint[a2] - 1;
  if (v18 < 0)
    v18 = 63;
  v19 = 4 * v18;
  v20 = 16 * nextpoint[a2] + (a2 << 10);
  v45 = *(float *)((char *)lastpos + v20);
  v44 = *(float *)((char *)lastpos_variable_1 + v20);
  v43 = *(float *)((char *)lastpos_variable_2 + v20);
  v21 = sqrt(
          (*(float *)&v58 - *(float *)&lastpos[256 * a2 + v19]) * (*(float *)&v58 - *(float *)&lastpos[256 * a2 + v19])
        + (v59 - lastpos_variable_1[256 * a2 + v19]) * (v59 - lastpos_variable_1[256 * a2 + v19])
        + (v60 - lastpos_variable_2[256 * a2 + v19]) * (v60 - lastpos_variable_2[256 * a2 + v19]));
  if (v21 >= view_c_variable_9) {
    v22 = nextpoint[a2] + 1;
    nextpoint[a2] = v22;
    if (v22 == 64)
      nextpoint[a2] = 0;
    v23 = 16 * nextpoint[a2] + (a2 << 10);
    *(int *)((char *)lastpos + v23) = v58;
    *(float *)((char *)lastpos_variable_1 + v23) = v59;
    *(float *)((char *)lastpos_variable_2 + v23) = v60;
    *(float *)((char *)lastpos_variable_3 + v23) = sqrt(
                                                     (v45 - *(float *)&v58) * (v45 - *(float *)&v58)
                                                   + (v44 - v59) * (v44 - v59)
                                                   + (v43 - v60) * (v43 - v60));
  } else {
    *(int *)((char *)lastpos + v20) = v58;
    *(float *)((char *)lastpos_variable_1 + v20) = v59;
    *(float *)((char *)lastpos_variable_2 + v20) = v60;
    v46 = v21;
    *(float *)((char *)lastpos_variable_3 + v20) = v46;
  }
  v24 = 62;
  v61 = 0.0;
  v25 = nextpoint[a2];
  while (1) {
    v26 = v61 + *(float *)&lastpos_variable_3[256 * a2 + 4 * v25];
    if (v26 >= CHASE_DIST[a2] || v24 < 0)
      break;
    v62 = v26;
    v61 = v62;
    v25 = v25 - 1 + (v25 - 1 < 0 ? 0x40 : 0);
    --v24;
  }
  if (v24 <= 0) {
    v31 = nextpoint[a2] + 1;
    if (nextpoint[a2] == 63)
      v31 = 0;
    v32 = a2 << 10;
    v33 = 16 * v31;
    v52 = *(int *)((char *)lastpos + v32 + v33);
    v34 = *(_DWORD *)((char *)lastpos_variable_1 + v32 + v33);
    v30 = *(_DWORD *)((char *)lastpos_variable_2 + v32 + v33);
    v51 = v34;
    v50 = v30;
  } else {
    v27 = v25 - 1;
    v49 = (*(float *)&lastpos_variable_3[256 * a2 + 4 * v25] + v61 - CHASE_DIST[a2])
      / *(float *)&lastpos_variable_3[256 * a2 + 4 * v25];
    v28 = a2 << 10;
    v29 = 4 * v25;
    v30 = 16 * (v27 + (v27 < 0 ? 0x40 : 0));
    *(float *)&v52 = (*(float *)((char *)&lastpos[v29] + v28) - *(float *)((char *)lastpos + v28 + v30)) * v49
      + *(float *)((char *)lastpos + v28 + v30);
    *(float *)&v51 = (*(float *)((char *)&lastpos_variable_1[v29] + v28)
                    - *(float *)((char *)lastpos_variable_1 + v28 + v30))
      * v49
      + *(float *)((char *)lastpos_variable_1 + v28 + v30);
    *(float *)&v50 = v49
      * (*(float *)((char *)&lastpos_variable_2[v29] + v28)
       - *(float *)((char *)lastpos_variable_2 + v28 + v30))
      + *(float *)((char *)lastpos_variable_2 + v28 + v30);
  }
  *(float *)&v53 = v54 - *(float *)&v52;
  *(float *)&v55 = v56 - *(float *)&v51;
  if ((v53 & 0x7FFFFFFF) != 0 || fabs(v56 - *(float *)&v51))
    v35 = getangle(v30, v53, *(float *)&v53, v55);
  else
    v35 = lastcamdirection;
  vdirection = v35;
  v48 = sqrt(*(float *)&v53 * *(float *)&v53 + *(float *)&v55 * *(float *)&v55);
  if ((LODWORD(v48) & 0x7FFFFFFF) != 0 || fabs(v57 - *(float *)&v50)) {
    *(float *)&v47 = v57 - *(float *)&v50;
    v36 = getangle(v35, v53, v48, v47);
  } else {
    v36 = lastcamelevation;
  }
  velevation = v36;
  vtilt = 0;
  calculatetransform(v52, v51, v50, DDX, DDY, DDZ);
  lastcamdirection = vdirection;
  lastcamelevation = velevation;
  worlddirn = vdirection;
  worldelev = velevation;
  result = vtilt;
  worldtilt = vtilt;
  return result;
}

//-------------------------------------------------------------------------------------------------
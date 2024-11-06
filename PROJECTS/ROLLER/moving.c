
//-------------------------------------------------------------------------------------------------

_DWORD *__fastcall initramp(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10)
{
  _DWORD *result; // eax
  _DWORD *v12; // [esp+0h] [ebp-10h] BYREF

  result = (_DWORD *)getbuffer(0x54u);
  v12 = result;
  if (result) {
    memset(result, 0, 84);
    v12[20] = getbuffer(176 * a2);
    if (v12[20]) {
      memset(v12[20], 0, 176 * a2);
      v12[2] = a3;
      v12[10] = a4;
      v12[3] = a4;
      *v12 = a1;
      v12[1] = a2;
      v12[11] = a5;
      v12[4] = a5;
      v12[6] = a7;
      v12[7] = a8;
      v12[12] = 0;
      v12[8] = a9;
      v12[5] = a6;
      v12[9] = a10;
      reinitramp(v12);
      return v12;
    } else {
      fre(&v12);
      v12 = 0;
      return 0;
    }
  }
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall reinitramp(float *a1)
{
  int v2; // ebx
  int v3; // eax
  int v4; // edi
  int v5; // eax
  float *v6; // ebp
  int v7; // esi
  _DWORD *v8; // ebx
  double v9; // st7
  double v10; // st6
  double v11; // st5
  double v12; // st4
  int v13; // eax
  double v14; // st7
  int v15; // eax
  double v16; // st7
  double v17; // st6
  double v18; // st5
  double v19; // st4
  double v20; // st7
  int v21; // ebx
  _DWORD *v22; // esi
  double v23; // st7
  double v24; // st6
  double v25; // st5
  int v26; // eax
  double v27; // st7
  int v28; // eax
  double v29; // st7
  double v30; // st6
  double v31; // st5
  double v32; // st7
  float v34; // [esp+0h] [ebp-88h]
  int v35; // [esp+4h] [ebp-84h]
  int v36; // [esp+1Ch] [ebp-6Ch]
  int v37; // [esp+20h] [ebp-68h]
  int v38; // [esp+20h] [ebp-68h]
  int v39; // [esp+24h] [ebp-64h]
  int v40; // [esp+28h] [ebp-60h]
  int j; // [esp+30h] [ebp-58h]
  int v42; // [esp+34h] [ebp-54h]
  int v43; // [esp+38h] [ebp-50h]
  float *v44; // [esp+3Ch] [ebp-4Ch]
  float *v45; // [esp+3Ch] [ebp-4Ch]
  float v46; // [esp+54h] [ebp-34h]
  float v47; // [esp+58h] [ebp-30h]
  float v48; // [esp+60h] [ebp-28h]
  int i; // [esp+64h] [ebp-24h]
  int k; // [esp+68h] [ebp-20h]
  int v51; // [esp+6Ch] [ebp-1Ch]

  a1[10] = a1[3];
  a1[11] = a1[4];
  v2 = *(_DWORD *)a1;
  v40 = *((_DWORD *)a1 + 1);
  v3 = 9 * (*(_DWORD *)a1 - v40);
  a1[12] = 0.0;
  a1[13] = (TrakPt_variable_3[2 * v3] + TrakPt_variable_6[2 * v3]) * moving_c_variable_1;
  a1[14] = (TrakPt_variable_4[2 * v3] + TrakPt_variable_7[2 * v3]) * moving_c_variable_1;
  a1[15] = (TrakPt_variable_5[2 * v3] + TrakPt_variable_8[2 * v3]) * moving_c_variable_1;
  a1[16] = (TrakPt_variable_3[18 * v2 + 18 + 18 * v40] + TrakPt_variable_6[18 * v2 + 18 + 18 * v40])
    * moving_c_variable_1;
  a1[17] = (TrakPt_variable_4[18 * v2 + 18 + 18 * v40] + TrakPt_variable_7[18 * v2 + 18 + 18 * v40])
    * moving_c_variable_1;
  a1[18] = (TrakPt_variable_5[18 * v2 + 18 + 18 * v40] + TrakPt_variable_8[18 * v2 + 18 + 18 * v40])
    * moving_c_variable_1;
  v4 = *((_DWORD *)a1 + 9);
  *(float *)&v35 = (TrakPt_variable_4[18 * v2] + TrakPt_variable_7[18 * v2]) * moving_c_variable_1 - a1[14];
  v34 = (TrakPt_variable_3[18 * v2] + TrakPt_variable_6[18 * v2]) * moving_c_variable_1 - a1[13];
  v5 = getangle(9 * v2, (int)a1, v34, v35);
  *((_DWORD *)a1 + 19) = v5;
  v39 = v2 - v40 + 1;
  v48 = tsin[v5];
  v46 = tcos[v5];
  v6 = (float *)*((_DWORD *)a1 + 20);
  v44 = (float *)((char *)&localdata + 128 * v39 - 128);
  v47 = -v48;
  if (v40 > 0) {
    v43 = 72 * v39;
    do {
      v7 = v43;
      v8 = v6;
      for (i = 0; i < 6; ++i) {
        if (((1 << i) & v4) != 0) {
          v9 = *(float *)((char *)TrakPt + v7) - a1[13];
          v10 = *(float *)((char *)TrakPt_variable_1 + v7) - a1[14];
          v11 = *(float *)((char *)TrakPt_variable_2 + v7) - a1[15];
          v12 = 0.0 * v11;
          _CHP(1 << i, a1);
          v37 = (int)(v46 * v9 + v48 * v10 + v12);
          _CHP(v13, a1);
          v51 = (int)(v12 + v47 * v9 + v46 * v10);
          v14 = v9 * 0.0 + v10 * 0.0 + v11;
          _CHP(v15, a1);
          *v8 = v37;
          v8[1] = v51;
          v8[2] = (int)v14;
        }
        v8 += 3;
        v7 += 12;
      }
      v16 = -v44[9] - a1[13];
      v17 = -v44[10] - a1[14];
      v18 = -v44[11] - a1[15];
      v19 = 0.0 * v18;
      v6[18] = v46 * v16 + v48 * v17 + v19;
      v6[19] = v19 + v47 * v16 + v46 * v17;
      v6[20] = v16 * 0.0 + v17 * 0.0 + v18;
      v20 = v44[12];
      v6 += 22;
      v44 += 32;
      v43 += 72;
      *(v6 - 1) = v20;
    } while (v43 < 72 * v40 + 72 * v39);
  }
  v45 = v44 + 32;
  v42 = 72 * v39 + 72 * v40;
  for (j = 144 * v40 + 72 * v39; v42 < j; *(v6 - 1) = v32) {
    v21 = v42;
    v22 = v6;
    for (k = 0; k < 6; ++k) {
      if (((1 << k) & v4) != 0) {
        v23 = *(float *)((char *)TrakPt + v21) - a1[16];
        v24 = *(float *)((char *)TrakPt_variable_1 + v21) - a1[17];
        v25 = *(float *)((char *)TrakPt_variable_2 + v21) - a1[18];
        _CHP(1 << k, a1);
        v36 = (int)(v46 * v23 + v48 * v24 + 0.0 * v25);
        _CHP(v26, a1);
        v38 = (int)(v47 * v23 + v46 * v24 + 0.0 * v25);
        v27 = v23 * 0.0 + v24 * 0.0 + v25 * 1.0;
        _CHP(v28, a1);
        *v22 = v36;
        v22[1] = v38;
        v22[2] = (int)v27;
      }
      v22 += 3;
      v21 += 12;
    }
    v29 = -v45[9] - a1[16];
    v30 = -v45[10] - a1[17];
    v31 = -v45[11] - a1[18];
    v6[18] = v46 * v29 + v48 * v30 + 0.0 * v31;
    v6[19] = v47 * v29 + v46 * v30 + 0.0 * v31;
    v6[20] = v29 * 0.0 + v30 * 0.0 + v31 * 1.0;
    v32 = v45[12];
    v6 += 22;
    v45 += 32;
    v42 += 72;
  }
  return updateramp(a1);
}

//-------------------------------------------------------------------------------------------------

int __fastcall updateramp(int result)
{
  int v1; // edx
  int v2; // ecx
  int v3; // ebx
  int v4; // edx
  double v5; // st7
  int v6; // esi
  int v7; // edx
  float *v8; // edi
  int v9; // ecx
  int v10; // ebx
  int *v11; // edx
  double v12; // st7
  double v13; // st6
  double v14; // st5
  double v15; // st6
  float *v16; // edi
  int v17; // ecx
  int v18; // ebx
  int *v19; // edx
  double v20; // st7
  double v21; // st6
  double v22; // st5
  double v23; // st6
  double v24; // st6
  int v25; // ebx
  double v26; // st7
  double v27; // st6
  double v28; // st5
  double v29; // st4
  double v30; // st3
  double v31; // st2
  float *v32; // edx
  float v33; // [esp+14h] [ebp-A0h]
  float v34; // [esp+18h] [ebp-9Ch]
  float v35; // [esp+24h] [ebp-90h]
  float v36; // [esp+28h] [ebp-8Ch]
  float v37; // [esp+2Ch] [ebp-88h]
  float v38; // [esp+2Ch] [ebp-88h]
  float v39; // [esp+30h] [ebp-84h]
  float v40; // [esp+30h] [ebp-84h]
  int v41; // [esp+38h] [ebp-7Ch]
  float v42; // [esp+3Ch] [ebp-78h]
  float v43; // [esp+40h] [ebp-74h]
  float v44; // [esp+44h] [ebp-70h]
  float v45; // [esp+48h] [ebp-6Ch]
  float v46; // [esp+4Ch] [ebp-68h]
  int *v47; // [esp+50h] [ebp-64h]
  int v48; // [esp+54h] [ebp-60h]
  int v49; // [esp+58h] [ebp-5Ch]
  int *v50; // [esp+5Ch] [ebp-58h]
  int v51; // [esp+60h] [ebp-54h]
  int v52; // [esp+64h] [ebp-50h]
  float *v53; // [esp+68h] [ebp-4Ch]
  float v54; // [esp+78h] [ebp-3Ch]
  float v55; // [esp+7Ch] [ebp-38h]
  float v56; // [esp+80h] [ebp-34h]
  float v57; // [esp+8Ch] [ebp-28h]
  float v58; // [esp+90h] [ebp-24h]
  float v59; // [esp+94h] [ebp-20h]
  float v60; // [esp+94h] [ebp-20h]
  float v61; // [esp+98h] [ebp-1Ch]

  v1 = *(_DWORD *)(result + 40);
  if (replaytype != 2) {
    v2 = *(_DWORD *)(result + 48);
    if (v2) {
      *(_DWORD *)(result + 48) = v2 - 1;
    } else if (*(_DWORD *)(result + 44) == 1) {
      if (v1 == *(_DWORD *)(result + 8) - 1) {
        *(_DWORD *)(result + 44) = -1;
        *(_DWORD *)(result + 48) = *(_DWORD *)(result + 24);
      } else {
        ++v1;
      }
    } else if (v1) {
      --v1;
    } else {
      *(_DWORD *)(result + 44) = 1;
      *(_DWORD *)(result + 48) = *(_DWORD *)(result + 28);
    }
  }
  if (v1 != *(_DWORD *)(result + 40) || replaytype == 2) {
    v3 = v1 * *(_DWORD *)(result + 20);
    *(_DWORD *)(result + 40) = v1;
    v4 = *(_DWORD *)(result + 76);
    v41 = v3;
    v36 = tsin[v4];
    v35 = tcos[v4];
    v33 = tcos[v3];
    v56 = v33 * v35;
    v55 = v33 * v36;
    v54 = -v36;
    v34 = tsin[v3];
    v5 = -v34;
    v57 = v5 * v35;
    v58 = v5 * v36;
    v42 = v34 * moving_c_variable_2;
    v44 = v33 * moving_c_variable_2;
    v59 = (double)*(int *)(result + 32) * moving_c_variable_3;
    v6 = *(_DWORD *)(result + 36);
    v61 = v34;
    v53 = *(float **)(result + 80);
    v7 = *(_DWORD *)result - *(_DWORD *)(result + 4) + 1;
    v48 = v7;
    v8 = (float *)((char *)&localdata + 128 * v7 - 128);
    v60 = (double)*(int *)(result + 40) * (v59 + moving_c_variable_4) / (double)*(int *)(result + 8) + 1.0;
    if (v7 <= *(_DWORD *)result) {
      v47 = (int *)(v53 + 18);
      v51 = 72 * v7;
      do {
        v9 = 1;
        v10 = v51;
        v11 = (int *)v53;
        do {
          if ((v9 & v6) != 0) {
            v12 = (double)*v11 * v60;
            v13 = (double)v11[1];
            v14 = (double)v11[2];
            *(float *)((char *)TrakPt + v10) = v56 * v12 + v54 * v13 + v57 * v14 + *(float *)(result + 52);
            *(float *)((char *)TrakPt_variable_1 + v10) = v55 * v12 + v35 * v13 + v58 * v14 + *(float *)(result + 56);
            *(float *)((char *)TrakPt_variable_2 + v10) = v12 * v34 + v13 * 0.0 + v14 * v33 + *(float *)(result + 60);
          }
          v10 += 12;
          v11 += 3;
          v9 *= 2;
        } while (v11 != v47);
        v15 = v53[18] * v60;
        v39 = v53[19];
        v37 = v53[20];
        v8[9] = -v56 * v15 - v54 * v39 - v57 * v37 - *(float *)(result + 52);
        v8[10] = -v55 * v15 - v35 * v39 - v58 * v37 - *(float *)(result + 56);
        v8[11] = v15 * -v34 - 0.0 * v39 - v33 * v37 - *(float *)(result + 60);
        v8[12] = v60 * v53[21];
        v8 += 32;
        *(v8 - 25) = 0.0;
        *(v8 - 32) = v56;
        *(v8 - 31) = v54;
        *(v8 - 30) = v57;
        *(v8 - 29) = v55;
        *(v8 - 28) = v35;
        *(v8 - 27) = v58;
        *(v8 - 26) = v34;
        v51 += 72;
        *(v8 - 24) = v33;
        ++v48;
        *(v8 - 13) = v42;
        v53 += 22;
        *(v8 - 11) = v44;
        *(v8 - 12) = 0.0;
        v47 += 22;
      } while (v48 <= *(_DWORD *)result);
    }
    HIBYTE(v61) = HIBYTE(v34) ^ 0x80;
    v43 = v61 * moving_c_variable_2;
    v46 = 0.0 * moving_c_variable_2;
    HIBYTE(v57) ^= 0x80u;
    v52 = *(_DWORD *)result + 1;
    HIBYTE(v58) ^= 0x80u;
    v50 = (int *)(v53 + 18);
    v16 = v8 + 32;
    v49 = 72 * v52;
    v45 = v33 * moving_c_variable_2;
    while (*(_DWORD *)(result + 4) + *(_DWORD *)result >= v52) {
      v17 = 1;
      v18 = v49;
      v19 = (int *)v53;
      do {
        if ((v17 & v6) != 0) {
          v20 = (double)*v19 * v60;
          v21 = (double)v19[1];
          v22 = (double)v19[2];
          *(float *)((char *)TrakPt + v18) = v56 * v20 + v54 * v21 + v57 * v22 + *(float *)(result + 64);
          *(float *)((char *)TrakPt_variable_1 + v18) = v55 * v20 + v35 * v21 + v58 * v22 + *(float *)(result + 68);
          *(float *)((char *)TrakPt_variable_2 + v18) = v20 * v61 + v21 * 0.0 + v22 * v33 + *(float *)(result + 72);
        }
        v18 += 12;
        v19 += 3;
        v17 *= 2;
      } while (v19 != v50);
      v23 = v53[18] * v60;
      v40 = v53[19];
      v38 = v53[20];
      v16[9] = -v56 * v23 - v54 * v40 - v57 * v38 - *(float *)(result + 64);
      v16[10] = -v55 * v23 - v35 * v40 - v58 * v38 - *(float *)(result + 68);
      v16[11] = v23 * -v61 - 0.0 * v40 - v33 * v38 - *(float *)(result + 72);
      v16 += 32;
      v24 = v53[21];
      *(v16 - 32) = v56;
      *(v16 - 31) = v54;
      *(v16 - 30) = v57;
      *(v16 - 29) = v55;
      *(v16 - 28) = v35;
      *(v16 - 27) = v58;
      *(v16 - 26) = v61;
      *(v16 - 25) = 0.0;
      *(v16 - 24) = v33;
      *(v16 - 13) = v43;
      v49 += 72;
      *(v16 - 12) = v46;
      ++v52;
      *(v16 - 11) = v45;
      v53 += 22;
      *(v16 - 20) = v60 * v24;
      v50 += 22;
    }
    HorizonColour_variable_1[32 * (*(_DWORD *)result - *(_DWORD *)(result + 4))] = v41;
    HorizonColour_variable_1[32 * *(_DWORD *)result] = -v41;
    localdata_variable_6[32 * *(_DWORD *)result] = -v41;
    localdata_variable_6[32 * (*(_DWORD *)(result + 4) + *(_DWORD *)result)] = v41;
    v25 = *(_DWORD *)result;
    v26 = (TrakPt_variable_3[18 * *(_DWORD *)result] + TrakPt_variable_6[18 * *(_DWORD *)result]) * moving_c_variable_5;
    v27 = (TrakPt_variable_4[18 * *(_DWORD *)result] + TrakPt_variable_7[18 * *(_DWORD *)result]) * moving_c_variable_5;
    v28 = (TrakPt_variable_5[18 * *(_DWORD *)result] + TrakPt_variable_8[18 * *(_DWORD *)result]) * moving_c_variable_5;
    result = 9 * (*(_DWORD *)result + 1);
    v29 = (TrakPt_variable_3[2 * result] + TrakPt_variable_6[2 * result]) * moving_c_variable_5;
    v30 = (TrakPt_variable_4[2 * result] + TrakPt_variable_7[2 * result]) * moving_c_variable_5;
    v31 = (TrakPt_variable_5[2 * result] + TrakPt_variable_8[2 * result]) * moving_c_variable_5;
    v32 = (float *)((char *)&localdata + 128 * v25);
    v32[9] = -(v26 + v29) * moving_c_variable_5;
    v32[10] = -(v27 + v30) * moving_c_variable_5;
    v32[11] = -(v28 + v31) * moving_c_variable_5;
    v32[12] = sqrt((v29 - v26) * (v29 - v26) + (v30 - v27) * (v30 - v27) + (v31 - v28) * (v31 - v28))
      * moving_c_variable_6;
  }
  return result;
}

//-------------------------------------------------------------------------------------------------

int updatestunts()
{
  int *v0; // edx
  int result; // eax
  int v2; // ecx

  v0 = ramp;
  if (ramp[0]) {
    do {
      result = updateramp(*v0);
      v2 = v0[1];
      ++v0;
    } while (v2);
  }
  return result;
}

//-------------------------------------------------------------------------------------------------

int reinitstunts()
{
  int *v0; // edx
  int result; // eax
  int v2; // ecx

  v0 = ramp;
  if (ramp[0]) {
    do {
      result = reinitramp((float *)*v0);
      v2 = v0[1];
      ++v0;
    } while (v2);
  }
  return result;
}

//-------------------------------------------------------------------------------------------------

_DWORD *__fastcall freeramp(_DWORD *result)
{
  _DWORD *v1; // [esp+0h] [ebp-4h] BYREF

  v1 = result;
  if (result) {
    if (result[20])
      fre(result + 20);
    return fre(&v1);
  }
  return result;
}

//-------------------------------------------------------------------------------------------------

void __fastcall freestunts(int a1, int a2, int a3, int a4)
{
  int *v4; // edx
  int v5; // eax
  int v6; // ecx
  _DWORD v7[4]; // [esp+0h] [ebp-10h] BYREF

  v7[2] = a4;
  v7[1] = a2;
  v4 = ramp;
  if (ramp[0]) {
    do {
      v5 = *v4;
      v7[0] = v5;
      if (v5) {
        if (*(_DWORD *)(v5 + 80))
          fre((_DWORD *)(v5 + 80));
        fre(v7);
      }
      v6 = v4[1];
      ++v4;
    } while (v6);
  }
}

//-------------------------------------------------------------------------------------------------

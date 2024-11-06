
//-------------------------------------------------------------------------------------------------

int InitCarStructs()
{
  int v0; // ebx
  int v1; // esi
  int v2; // ecx
  int v3; // edi
  float *v4; // ebx
  int j; // ecx
  double v6; // st7
  int v7; // ebx
  int v8; // ecx
  int v9; // esi
  int v10; // ebp
  int v11; // edx
  __int16 k; // di
  int v13; // eax
  int m; // ebx
  double v15; // st7
  float v17; // [esp+0h] [ebp-20h]
  float v18; // [esp+0h] [ebp-20h]
  __int16 i; // [esp+4h] [ebp-1Ch]

  for (i = 0; i < 14; ++i) {
    v0 = 28 * i;
    v1 = 0;
    v2 = 0;
    v3 = CarEngines[v0];
    v4 = *(float **)((char *)&CarEngines_variable_2 + v0 * 4);
    while (v1 < i) {
      if (v4 == (float *)*(_UNKNOWN **)((char *)&CarEngines_variable_2 + v2))
        v3 = -1;
      v2 += 112;
      ++v1;
    }
    for (j = 0; j < v3; *(v4 - 1) = v6) {
      v6 = *v4++ * car_c_variable_1;
      ++j;
    }
    v7 = 0;
    if (v3 > 0) {
      v8 = 0;
      do {
        v9 = 112 * i;
        v10 = 12 * i;
        v17 = (float)*(int *)(*(char **)((char *)&CarEngines_variable_3 + v9) + v8 * 4);
        eng_chg_revs[v8 + v10] = calc_revs(*(int *)((char *)&CarEngines_variable_1 + v9), v7, v17);
        v18 = (float)*(int *)(*(char **)((char *)&CarEngines_variable_3 + v9) + v8 * 4 + 4);
        v8 += 2;
        v11 = v7++;
        trial_times_variable_1[v8 + v10] = calc_revs(*(int *)((char *)&CarEngines_variable_1 + v9), v11, v18);
      } while (v7 < v3);
    }
  }
  for (k = 0; k < 14; ++k) {
    v13 = CarEngines[28 * k];
    if (v13 > 0) {
      for (m = 0; m < v13; driver_names_variable_1[6 * k + m] = v15) {
        v15 = *(float *)((char *)*(&CarEngines_variable_2 + 28 * k) + m * 4);
        ++m;
      }
    }
  }
  return CalcCarSizes();
}

//-------------------------------------------------------------------------------------------------

int CalcCarSizes()
{
  __int16 i; // cx
  __int16 v1; // bx
  float *v2; // edx
  double v3; // st7
  float *v4; // edx
  double v5; // st7
  float *v6; // edx
  int v7; // eax
  int *v8; // edx
  __int16 j; // bx
  int result; // eax
  int v11; // [esp+0h] [ebp-28h]
  int v12; // [esp+4h] [ebp-24h]
  int v13; // [esp+8h] [ebp-20h]
  int v14; // [esp+Ch] [ebp-1Ch]
  int v15; // [esp+10h] [ebp-18h]
  int v16; // [esp+14h] [ebp-14h]

  for (i = 0; i < 14; ++i) {
    *(float *)&v11 = 1073741800.0;
    *(float *)&v15 = 1073741800.0;
    *(float *)&v16 = 1073741800.0;
    *(float *)&v12 = -1073741800.0;
    *(float *)&v13 = -1073741800.0;
    *(float *)&v14 = -1073741800.0;
    v1 = 0;
    v2 = (float *)*(&CarDesigns_variable_3 + 7 * i);
    while (v1 < (unsigned __int8)CarDesigns_variable_1[28 * i]) {
      if (*v2 < (double)*(float *)&v16)
        v16 = *(int *)v2;
      if (*v2 > (double)*(float *)&v14)
        v14 = *(int *)v2;
      v3 = v2[1];
      v4 = v2 + 1;
      if (v3 < *(float *)&v15)
        v15 = *(int *)v4;
      if (*v4 > (double)*(float *)&v13)
        v13 = *(int *)v4;
      v5 = v4[1];
      v6 = v4 + 1;
      if (v5 < *(float *)&v11)
        v11 = *(int *)v6;
      if (*v6 > (double)*(float *)&v12)
        v12 = *(int *)v6;
      v2 = v6 + 1;
      ++v1;
    }
    if ((cheat_mode & 0x8000) != 0) {
      *(float *)&v16 = *(float *)&v16 * car_c_variable_2;
      *(float *)&v15 = *(float *)&v15 * car_c_variable_2;
      *(float *)&v14 = *(float *)&v14 * car_c_variable_2;
      *(float *)&v13 = *(float *)&v13 * car_c_variable_2;
    }
    v7 = 24 * i;
    CarBox[v7] = v16;
    CarBox_variable_1[v7] = v15;
    CarBox_variable_2[v7] = v11;
    CarBox_variable_3[v7] = v14;
    CarBox_variable_4[v7] = v15;
    CarBox_variable_5[v7] = v11;
    CarBox_variable_6[v7] = v14;
    CarBox_variable_7[v7] = v13;
    CarBox_variable_8[v7] = v11;
    CarBox_variable_9[v7] = v16;
    CarBox_variable_10[v7] = v13;
    CarBox_variable_11[v7] = v11;
    CarBox_variable_12[v7] = v16;
    CarBox_variable_13[v7] = v15;
    CarBox_variable_14[v7] = v12;
    CarBox_variable_15[v7] = v14;
    CarBox_variable_16[v7] = v15;
    CarBox_variable_17[v7] = v12;
    CarBox_variable_18[v7] = v14;
    CarBox_variable_19[v7] = v13;
    CarBox_variable_20[v7] = v12;
    CarBox_variable_21[v7] = v16;
    CarBox_variable_22[v7] = v13;
    CarBox_variable_23[v7] = v12;
  }
  v8 = (int *)CarDesigns_variable_3;
  CarBaseX = 0;
  CarBaseY = 0;
  for (j = 0; j < (unsigned __int8)CarDesigns_variable_1[0]; ++j) {
    if (*(float *)v8 > (double)*(float *)&CarBaseX)
      CarBaseX = *v8;
    if (*((float *)v8 + 1) > (double)*(float *)&CarBaseY)
      CarBaseY = v8[1];
    v8 += 3;
  }
  result = cheat_mode;
  if ((cheat_mode & 0x8000) != 0) {
    *(float *)&CarBaseX = *(float *)&CarBaseX * car_c_variable_2;
    *(float *)&CarBaseY = *(float *)&CarBaseY * car_c_variable_2;
  }
  CarDiag = sqrt(*(float *)&CarBaseX * *(float *)&CarBaseX + *(float *)&CarBaseY * *(float *)&CarBaseY);
  return result;
}

//-------------------------------------------------------------------------------------------------

int InitCars()
{
  __int16 i; // si
  __int16 v1; // di
  __int16 j; // bx
  __int16 k; // bx
  int v4; // eax
  char v5; // dl
  int v6; // eax
  int v7; // edx
  __int16 v8; // di
  int v9; // eax
  int v10; // esi
  int v11; // edx
  int v12; // ecx
  __int16 m; // [esp+0h] [ebp-1Ch]

  for (i = 0; i < 14; ++i) {
    v1 = CarEngines[28 * i];
    for (j = 0; j < v1; ++j) {
      if (((unsigned int)cstart_branch_1 & textures_off) != 0)
        *((float *)*(&CarEngines_variable_2 + 28 * i) + j) = StoreEngines[6 * i + j] * car_c_variable_3;
      else
        *((float *)*(&CarEngines_variable_2 + 28 * i) + j) = StoreEngines[6 * i + j];
    }
  }
  for (k = 0; k < numcars; ++k) {
    v4 = 308 * k;
    v5 = Drivers_Car[k];
    Car_variable_22[v4] = v5;
  }
  v6 = 1;
  car_texs_loaded[0] = 0;
  do {
    v7 = (__int16)v6++;
    car_texs_loaded[v7] = -1;
  } while ((__int16)v6 < 16);
  v8 = 1;
  for (m = 0; m < numcars; ++m) {
    if (!non_competitors[m]) {
      v9 = CarDesigns_variable_5[7 * (unsigned __int8)Car_variable_22[308 * m]];
      v10 = v9;
      v11 = car_texs_loaded[v9];
      if (v11 == -1) {
        v12 = v8;
        LoadCarTexture(v9, v8++, (char *)(4 * m));
        car_texmap[m] = v12;
        car_texs_loaded[v10] = v12;
      } else {
        car_texmap[m] = v11;
      }
    }
  }
  LoadCarTextures = v8;
  return CalcCarSizes();
}

//-------------------------------------------------------------------------------------------------

__int16 placecars()
{
  unsigned int v0; // ecx
  __int16 result; // ax
  int v2; // edi
  int v3; // eax
  char v4; // dl
  char v5; // dl
  unsigned int v6; // eax
  int v7; // esi
  __int16 v8; // dx
  unsigned int v9; // ebx
  int v10; // eax
  int v11; // eax
  unsigned int v12; // eax
  int v13; // esi
  float *v14; // eax
  double v15; // st7
  int v16; // ebx
  int *v17; // eax
  char v18; // dl
  double v19; // st7
  int v20; // edx
  float *v21; // ebp
  double v22; // st7
  int v23; // edi
  int v24; // ebp
  int v25; // esi
  unsigned int v26; // eax
  unsigned int v27; // edx
  double v28; // st7
  double v29; // st7
  int v30; // ebx
  float *v31; // ebx
  double v32; // st7
  double v33; // st7
  double v34; // st6
  double v35; // st7
  double v36; // st7
  double v37; // st6
  long double v38; // st7
  _DWORD v39[4]; // [esp+0h] [ebp-50h]
  float v40; // [esp+10h] [ebp-40h]
  float *v41; // [esp+14h] [ebp-3Ch]
  float v42; // [esp+18h] [ebp-38h]
  float v43; // [esp+1Ch] [ebp-34h]
  int v44; // [esp+20h] [ebp-30h]
  int v45; // [esp+24h] [ebp-2Ch]
  unsigned int v46; // [esp+28h] [ebp-28h]
  int v47; // [esp+2Ch] [ebp-24h]
  int v48; // [esp+30h] [ebp-20h]
  int v49; // [esp+34h] [ebp-1Ch]

  v39[0] = 0;
  v39[1] = *(&dword_52260 + 1);
  v39[2] = *(&dword_52260 + 2);
  v39[3] = *(&dword_52260 + 3);
  memset(Car, 0, 308 * numcars);
  v0 = 1;
  result = memset(CarSpray, 0, 1408 * (numcars + 2));
  v47 = 0;
  if (numcars > 0) {
    v48 = 4 * v47;
    v46 = 0;
    v49 = 2 * v47;
    do {
      v2 = grid[v46 / 4];
      v3 = 77 * v2;
      v4 = Drivers_Car[v2];
      Car_variable_10[v3] = v2;
      finished_car[v2] = 0;
      Car_variable_22[v3 * 4] = v4;
      v5 = v47;
      Car[v3] = 0.0;
      if ((v5 & 1) != 0)
        Car_variable_1[77 * v2] = 500.0;
      else
        Car_variable_1[77 * v2] = -500.0;
      v6 = 308 * v2;
      Car_variable_2[v6 / 4] = 0.0;
      Car_variable_53[v6 / 4] = 1176256502;
      Car_variable_5[v6 / 2] = 0;
      Car_variable_7[v6 / 2] = 0;
      Car_variable_8[v6 / 4] = 0.0;
      Car_variable_30[v6] = -1;
      v7 = champ_mode;
      Car_variable_6[v6 / 2] = 0;
      if (v7)
        v8 = TRAK_LEN - 56 - v49;
      else
        v8 = TRAK_LEN - 2 - v48;
      Car_variable_3[154 * v2] = v8;
      v9 = 308 * v2;
      Car_variable_51[v9 / 4] = Car_variable_3[154 * v2];
      Car_variable_4[v9 / 2] = Car_variable_3[154 * v2];
      Car_variable_20[v9 / 4] = -1;
      Car_variable_31[v9] = 0;
      Car_variable_75[v9] = 0;
      Car_variable_24[v9] = 0;
      v10 = 28 * (unsigned __int8)Car_variable_22[308 * v2];
      Car_variable_39[v9 / 4] = CarEngines_variable_10[v10];
      Car_variable_17[v9 / 4] = 3;
      Car_variable_45[v9 / 4] = 0;
      Car_variable_44[v9 / 4] = 0;
      Car_variable_46[v9 / 4] = -1;
      v11 = rand(v10 * 4);
      Car_variable_49[77 * v2] = -1;
      Car_variable_9[77 * v2] = 100.0;
      Car_variable_56[154 * v2] = -1;
      Car_variable_70[154 * v2] = -1;
      Car_variable_38[77 * v2] = (v11 - (__CFSHL__(v11 >> 31, 13) + (v11 >> 31 << 13))) >> 13;
      Car_variable_48[77 * v2] = 0;
      Car_variable_34[77 * v2] = 0;
      Car_variable_35[77 * v2] = 0;
      Car_variable_69[77 * v2] = 0;
      Car_variable_32[308 * v2] = v47;
      Car_variable_57[154 * v2] = 1080;
      Car_variable_58[308 * v2] = 0;
      v12 = v46;
      Car_variable_23[308 * v2] = 3;
      *(int *)((char *)carorder + v12) = v2;
      Car_variable_59[308 * v2] = 0;
      Car_variable_61[308 * v2] = 0;
      Car_variable_60[308 * v2] = 0;
      Car_variable_62[308 * v2] = 0;
      Car_variable_76[308 * v2] = 0;
      Car_variable_63[308 * v2] = 0;
      Car_variable_64[308 * v2] = 0;
      Car_variable_65[308 * v2] = 0;
      Car_variable_66[308 * v2] = 8;
      Car_variable_71[154 * v2] = 0;
      v13 = non_competitors[v2];
      Car_variable_67[308 * v2] = 0;
      if (v13) {
        Car_variable_23[308 * v2] = -1;
        finished_car[v2] = -1;
        v14 = (float *)((char *)&localdata + 128 * Car_variable_3[154 * v2]);
        Car_variable_17[77 * v2] = 0;
        Car[77 * v2] = 0.0 * v14[1] + 0.0 * *v14 + 0.0 * v14[2] - v14[9];
        Car_variable_1[77 * v2] = 0.0 * v14[3] + 0.0 * v14[4] + 0.0 * v14[5] - v14[10];
        v15 = 0.0 * v14[6] + 0.0 * v14[7] + 0.0 * v14[8] - v14[11] + car_c_variable_7;
        Car_variable_8[77 * v2] = 0.0;
        LOWORD(v14) = Car_variable_3[154 * v2];
        Car_variable_27[77 * v2] = 0;
        Car_variable_4[154 * v2] = (__int16)v14;
        Car_variable_3[154 * v2] = -1;
        Car_variable_2[77 * v2] = v15;
      }
      if (champ_mode && v2 == ViewType[0]) {
        v16 = 77 * ViewType[0];
        v17 = &CarEngines[28 * (unsigned __int8)Car_variable_22[v16 * 4]];
        Car_variable_28[v16] = 1.0;
        v18 = *(_BYTE *)v17 - 1;
        Car_variable_30[v16 * 4] = v18;
        Car_variable_8[v16] = *(float *)(v17[2] + 4 * v18);
        Car_variable_26[v16] = LODWORD(Car_variable_8[v16]);
        v19 = calc_pow((unsigned __int8)Car_variable_22[v16 * 4], Car_variable_30[v16 * 4], Car_variable_28[v16]);
        Car_variable_27[v16] = 0;
        Car_variable_58[v16 * 4] = -1;
        Car_variable_61[v16 * 4] = 36;
        *(float *)&Car_variable_29[v16] = v19;
      }
      v20 = Car_variable_3[154 * v2];
      v21 = (float *)((char *)&localdata + 128 * v20);
      v41 = (float *)&TrackInfo[9 * v20];
      while ((TrakColour_variable_1[12 * Car_variable_3[154 * v2]
              + 2 * *(_DWORD *)((char *)v39 + Car_variable_3[154 * v2])] & 0x800) != 0) {
        if (++v0 == 4)
          v0 = 0;
      }
      if (v0 <= 3) {
        switch (v0) {
          case 0u:
            v22 = *v41 * car_c_variable_4 + v21[13];
            break;
          case 1u:
            v22 = v21[13] * car_c_variable_4;
            break;
          case 2u:
            v22 = -v21[13] * car_c_variable_4;
            break;
          case 3u:
            v22 = -v21[13] - v41[2] * car_c_variable_4;
            break;
        }
        Car_variable_1[77 * v2] = v22;
      }
      ++v0;
      result = putflat((int)&Car[77 * v2]);
      if (v0 == 4)
        v0 = 0;
      v48 += 4;
      v49 += 2;
      v46 += 4;
      ++v47;
    } while (v47 < numcars);
  }
  v23 = 0;
  if (local_players > 0) {
    v24 = 144;
    v25 = 0;
    do {
      v26 = 154 * ViewType[v25];
      v27 = 144 * v23;
      *(float *)&v44 = Car[v26 / 2] + car_c_variable_8;
      SLight_variable_4[v27 / 4] = Car_variable_1[v26 / 2];
      *(float *)&v45 = car_c_variable_9 + Car_variable_2[v26 / 2];
      SLight_variable_3[v27 / 4] = *(float *)&v44;
      SLight[v27 / 4] = SLight_variable_3[36 * v23] + car_c_variable_10;
      SLight_variable_1[v27 / 4] = SLight_variable_4[36 * v23];
      SLight_variable_5[v27 / 4] = *(float *)&v45;
      SLight_variable_2[v27 / 4] = SLight_variable_5[36 * v23] + car_c_variable_11;
      SLight_variable_14[v27 / 4] = Car_variable_1[v26 / 2] + car_c_variable_12;
      SLight_variable_6[v27 / 4] = 1120403456;
      SLight_variable_7[v27 / 4] = 1120403456;
      SLight_variable_8[v27 / 4] = 1109393408;
      SLight_variable_13[v27 / 4] = v44;
      SLight_variable_10[v27 / 4] = *(float *)&SLight_variable_13[36 * v23] + car_c_variable_10;
      SLight_variable_11[v27 / 4] = SLight_variable_14[36 * v23] + car_c_variable_13;
      SLight_variable_15[v27 / 4] = v45;
      SLight_variable_12[v27 / 4] = *(float *)&SLight_variable_15[36 * v23] + car_c_variable_11;
      SLight_variable_24[v27 / 4] = Car_variable_1[v26 / 2] + car_c_variable_9;
      SLight_variable_23[v27 / 4] = v44;
      SLight_variable_20[v27 / 4] = *(float *)&SLight_variable_23[36 * v23] + car_c_variable_10;
      SLight_variable_21[v27 / 4] = SLight_variable_24[36 * v23] + car_c_variable_7;
      SLight_variable_9[v27 / 4] = 0;
      SLight_variable_19[v27 / 4] = 0;
      SLight_variable_25[v27 / 4] = v45;
      v28 = *(float *)&SLight_variable_25[36 * v23];
      SLight_variable_16[v27 / 4] = 1120403456;
      SLight_variable_17[v27 / 4] = 1120403456;
      SLight_variable_18[v27 / 4] = 1109393408;
      SLight_variable_26[v27 / 4] = 1120403456;
      v29 = v28 + car_c_variable_11;
      SLight_variable_27[v27 / 4] = 1120403456;
      SLight_variable_29[v27 / 4] = 0;
      v30 = Car_variable_3[v26];
      SLight_variable_28[v27 / 4] = 1109393408;
      v31 = (float *)((char *)&localdata + 128 * v30);
      SLight_variable_22[v27 / 4] = v29;
      do {
        v32 = v31[1];
        v40 = SLight[v27 / 4];
        v43 = SLight_variable_1[v27 / 4];
        v33 = v32 * v43 + *v31 * v40;
        v34 = v31[2];
        v42 = SLight_variable_2[v27 / 4];
        SLight[v27 / 4] = v33 + v34 * v42 - v31[9];
        SLight_variable_1[v27 / 4] = v31[3] * v40 + v31[4] * v43 + v31[5] * v42 - v31[10];
        SLight_variable_2[v27 / 4] = v31[6] * v40 + v31[7] * v43 + v31[8] * v42 - v31[11];
        v35 = v31[1];
        v40 = SLight_variable_3[v27 / 4];
        v43 = SLight_variable_4[v27 / 4];
        v36 = v35 * v43 + *v31 * v40;
        v37 = v31[2];
        v42 = SLight_variable_5[v27 / 4];
        SLight_variable_3[v27 / 4] = v36 + v37 * v42 - v31[9];
        SLight_variable_4[v27 / 4] = v31[3] * v40 + v31[4] * v43 + v31[5] * v42 - v31[10];
        SLight_variable_5[v27 / 4] = v31[6] * v40 + v31[7] * v43 + v31[8] * v42 - v31[11];
        *(float *)&SLight_variable_6[v27 / 4] = fabs(SLight_variable_3[v27 / 4] - SLight[v27 / 4]) * car_c_variable_5;
        *(float *)&SLight_variable_7[v27 / 4] = fabs(SLight_variable_4[v27 / 4] - SLight_variable_1[v27 / 4])
          * car_c_variable_5;
        v38 = fabs(SLight_variable_5[v27 / 4] - SLight_variable_2[v27 / 4]) * car_c_variable_6;
        v27 += 48;
        StoreEngines_variable_1[v27 / 4] = v38;
      } while (v27 != v24);
      result = local_players;
      v24 += 144;
      ++v23;
      ++v25;
    } while (v23 < local_players);
  }
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall DrawCars(int result, int a2)
{
  int v2; // ebp
  int v3; // esi
  int v4; // edi
  int v5; // edx
  int v6; // ebx
  int v7; // eax
  int v8; // edx
  float *v9; // ebx
  float *v10; // ecx
  double v11; // st7
  int v12; // edi
  float v13; // [esp+0h] [ebp-74h]
  float v14; // [esp+4h] [ebp-70h]
  float v15; // [esp+8h] [ebp-6Ch]
  float v16; // [esp+Ch] [ebp-68h]
  float v17; // [esp+10h] [ebp-64h]
  int v18; // [esp+14h] [ebp-60h]
  float v19; // [esp+18h] [ebp-5Ch]
  int v20; // [esp+1Ch] [ebp-58h]
  int v22; // [esp+24h] [ebp-50h]
  float *v23; // [esp+28h] [ebp-4Ch]
  float v24; // [esp+2Ch] [ebp-48h]
  float v25; // [esp+30h] [ebp-44h]
  float v26; // [esp+34h] [ebp-40h]
  float v27; // [esp+38h] [ebp-3Ch]
  float v28; // [esp+3Ch] [ebp-38h]
  float v29; // [esp+40h] [ebp-34h]
  float v30; // [esp+44h] [ebp-30h]
  float v31; // [esp+48h] [ebp-2Ch]
  float v32; // [esp+4Ch] [ebp-28h]
  float v33; // [esp+50h] [ebp-24h]
  float v34; // [esp+54h] [ebp-20h]
  float v35; // [esp+58h] [ebp-1Ch]
  float v36; // [esp+5Ch] [ebp-18h]

  v20 = result;
  v22 = 0;
  if (numcars > 0) {
    v23 = Car;
    v2 = 0;
    do {
      v25 = *v23;
      v3 = *((__int16 *)v23 + 6);
      v34 = v23[1];
      v4 = v3;
      v33 = v23[2];
      if (v3 == -1)
        v4 = *((_DWORD *)v23 + 54);
      if (backwards) {
        if (front_sec <= back_sec) {
          if (v4 <= front_sec || v4 >= back_sec) {
            v5 = -1;
            goto LABEL_32;
          }
        } else if (v4 <= front_sec && v4 >= back_sec) {
          v5 = -1;
        LABEL_32:
          if (!v5 || mid_sec < 0 || next_front < 0)
            goto LABEL_42;
          if (mid_sec <= next_front) {
            if (v4 >= mid_sec && v4 <= next_front)
              goto LABEL_42;
          } else if (v4 >= mid_sec || v4 <= next_front) {
            goto LABEL_42;
          }
          goto LABEL_41;
        }
        v5 = 0;
        goto LABEL_32;
      }
      if (front_sec >= back_sec) {
        if (v4 > back_sec && v4 < front_sec) {
        LABEL_13:
          v5 = 0;
          goto LABEL_14;
        }
        v5 = -1;
      } else {
        if (v4 < front_sec || v4 > back_sec)
          goto LABEL_13;
        v5 = -1;
      }
    LABEL_14:
      if (!v5 || mid_sec < 0 || next_front < 0)
        goto LABEL_42;
      if (mid_sec >= next_front) {
        if (v4 <= mid_sec && v4 >= next_front)
          goto LABEL_42;
      } else if (v4 <= mid_sec || v4 >= next_front) {
        goto LABEL_42;
      }
    LABEL_41:
      v5 = 0;
    LABEL_42:
      if (v5 && *((char *)v23 + 103) >= 0) {
        v18 = (*((_DWORD *)v23 + 34) + *((__int16 *)v23 + 8)) & 0x3FFF;
        v6 = *((__int16 *)v23 + 10);
        v7 = ((unsigned __int16)*((_DWORD *)v23 + 33) + *((_WORD *)v23 + 9)) & 0x3FFF;
        v26 = tcos[v6] * tcos[v7];
        v31 = tsin[v6] * tcos[v7];
        v35 = tsin[v7];
        v29 = tcos[v6] * v35 * tsin[v18] - tsin[v6] * tcos[v18];
        v28 = tsin[v6] * v35 * tsin[v18] + tcos[v6] * tcos[v18];
        v24 = -tsin[v18] * tcos[v7];
        v27 = -tcos[v6] * v35 * tcos[v18] - tsin[v6] * tsin[v18];
        v30 = -tsin[v6] * v35 * tcos[v18] + tcos[v6] * tsin[v18];
        v32 = tcos[v7] * tcos[v18];
        v8 = 0;
        v36 = 1073676300.0;
        v9 = (float *)((char *)&localdata + 128 * v3);
        v10 = (float *)&CarBox[24 * *((unsigned __int8 *)v23 + 102)];
        do {
          v15 = *v10;
          v14 = v10[1];
          v13 = v10[2];
          CarPt_variable_2[v8] = *v10 * v26 + v14 * v29 + v13 * v27 + v25;
          CarPt_variable_3[v8] = v15 * v31 + v14 * v28 + v13 * v30 + v34;
          v10 += 3;
          CarPt_variable_4[v8] = v15 * v35 + v14 * v24 + v13 * v32 + v33;
          if (v3 != -1) {
            v19 = CarPt_variable_2[v8];
            v17 = CarPt_variable_3[v8];
            v16 = CarPt_variable_4[v8];
            CarPt_variable_2[v8] = v9[1] * v17 + *v9 * v19 + v9[2] * v16 - v9[9];
            CarPt_variable_3[v8] = v9[3] * v19 + v9[4] * v17 + v9[5] * v16 - v9[10];
            CarPt_variable_4[v8] = v9[6] * v19 + v9[7] * v17 + v9[8] * v16 - v9[11];
          }
          k1 = CarPt_variable_2[v8] - viewx;
          k2 = CarPt_variable_3[v8] - viewy;
          k3 = CarPt_variable_4[v8] - viewz;
          v11 = k1 * vk3 + k2 * vk6 + k3 * vk9;
          CarPt_variable_7[v8] = v11;
          if (v11 < v36)
            v36 = CarPt_variable_7[v8];
          v8 += 8;
        } while (v8 != 64);
        *(float *)&car_draw_order_variable_2[v2] = v36;
        car_draw_order[v2] = v4;
        if (v22 == v20 && (!a2 || a2 == -1))
          car_draw_order[v2] = -2;
      } else {
        car_draw_order[v2] = -2;
        car_draw_order_variable_2[v2] = -1082130432;
      }
      result = v22;
      v12 = numcars;
      v2 += 3;
      CarZOrder_variable_3[v2] = v22;
      v23 += 77;
      ++v22;
    } while (v22 < v12);
  }
  return result;
}

//-------------------------------------------------------------------------------------------------

__int16 __fastcall DisplayCar(int a1, int a2, float a3)
{
  int v6; // ebx
  int v7; // esi
  int v8; // edi
  __int16 v9; // cx
  int v10; // edx
  int v11; // ebp
  double v12; // st7
  int v13; // ecx
  double v14; // st7
  float v15; // eax
  int v16; // edi
  float *v17; // esi
  unsigned __int8 v18; // dh
  double v19; // st7
  float *v20; // edx
  int v21; // eax
  double v22; // st7
  double v23; // st6
  double v24; // st5
  double v25; // st4
  double v26; // st3
  double v27; // st2
  int i; // eax
  double v29; // st7
  float *v30; // edx
  int v31; // eax
  double v32; // st7
  double v33; // st6
  double v34; // st5
  double v35; // st4
  double v36; // st3
  double v37; // st2
  int v38; // eax
  float *v39; // eax
  double v40; // st7
  double v41; // st5
  double v42; // st4
  int v43; // ecx
  int v44; // ecx
  int v45; // ebx
  int v46; // ecx
  __int64 v47; // rax
  __int64 v48; // rax
  int v49; // ebx
  int v50; // ebp
  double v51; // st7
  __int16 v52; // fps
  double v53; // st7
  _BOOL1 v54; // c0
  char v55; // c2
  _BOOL1 v56; // c3
  __int16 v57; // fps
  double v58; // st7
  _BOOL1 v59; // c0
  char v60; // c2
  _BOOL1 v61; // c3
  __int16 v62; // fps
  double v63; // st7
  _BOOL1 v64; // c0
  char v65; // c2
  _BOOL1 v66; // c3
  int v67; // edi
  int j; // edx
  int m; // eax
  double v70; // st7
  int n; // edx
  double v72; // st7
  int k; // edx
  double v74; // st7
  int v75; // ebp
  int v76; // edx
  __int16 v77; // fps
  double v78; // st7
  _BOOL1 v79; // c0
  char v80; // c2
  _BOOL1 v81; // c3
  int v82; // eax
  __int16 v83; // fps
  double v84; // st7
  _BOOL1 v85; // c0
  char v86; // c2
  _BOOL1 v87; // c3
  double v88; // st7
  int v89; // eax
  double v90; // st7
  int v91; // ecx
  int ii; // edx
  double v93; // st7
  double v94; // st6
  double v95; // st5
  double v96; // st7
  __int16 v97; // fps
  _BOOL1 v98; // c0
  char v99; // c2
  _BOOL1 v100; // c3
  double v101; // st7
  double v102; // st6
  double v103; // st5
  double v104; // st7
  int v105; // eax
  double v106; // st7
  double v107; // st7
  int v108; // eax
  double v109; // st7
  int v110; // eax
  double v111; // st7
  int v112; // eax
  double v113; // st7
  int v114; // eax
  double v115; // st7
  int v116; // eax
  double v117; // st7
  int v118; // eax
  double v119; // st7
  int v120; // eax
  float *v121; // ebx
  unsigned __int8 *v122; // ecx
  unsigned int v123; // esi
  int v124; // edi
  float *v125; // edx
  float v126; // eax
  float *v127; // ebx
  float v128; // eax
  float v129; // eax
  double v130; // st7
  double v131; // st5
  double v132; // st6
  int v133; // ebp
  double v134; // st7
  double v135; // st7
  double v136; // st6
  double v137; // st7
  double v138; // st7
  double v139; // st6
  double v140; // st5
  double v141; // st7
  __int16 v142; // fps
  _BOOL1 v143; // c0
  char v144; // c2
  _BOOL1 v145; // c3
  int v146; // eax
  double v147; // st7
  double v148; // st6
  double v149; // st5
  double v150; // st7
  int v151; // eax
  int v152; // esi
  int v153; // edi
  unsigned __int8 *v154; // edx
  int jj; // eax
  int *v156; // ebx
  double v157; // st7
  double v158; // st6
  double v159; // st5
  double v160; // st4
  double v161; // st3
  unsigned __int8 v162; // dh
  int v163; // eax
  float v164; // eax
  float v165; // eax
  float v166; // eax
  float v167; // eax
  float v168; // eax
  int v169; // eax
  int v170; // edi
  int v171; // ecx
  int v172; // edi
  int v173; // ebx
  int kk; // eax
  int v175; // edx
  int v176; // ebp
  float *v177; // ebx
  float *v178; // ecx
  int v179; // edx
  int v180; // edi
  int v181; // eax
  double v182; // st7
  double v183; // st7
  double v184; // st6
  double v185; // st7
  double v186; // st7
  double v187; // st6
  double v188; // st5
  double v189; // st7
  __int16 v190; // fps
  _BOOL1 v191; // c0
  char v192; // c2
  _BOOL1 v193; // c3
  int v194; // eax
  double v195; // st7
  double v196; // st6
  double v197; // st5
  double v198; // st7
  int v199; // eax
  int v200; // eax
  double v201; // st7
  double v202; // st7
  double v203; // st6
  double v204; // st7
  double v205; // st7
  double v206; // st6
  double v207; // st5
  double v208; // st7
  __int16 v209; // fps
  _BOOL1 v210; // c0
  char v211; // c2
  _BOOL1 v212; // c3
  int v213; // eax
  double v214; // st7
  double v215; // st6
  double v216; // st5
  double v217; // st7
  int v218; // eax
  unsigned int v219; // edi
  int v220; // ebx
  int v221; // edx
  float *v222; // eax
  double v223; // st7
  int v224; // ecx
  int v225; // ebx
  int v226; // edx
  int v227; // eax
  int v228; // eax
  double v229; // st7
  int v230; // eax
  int v231; // esi
  int v232; // ebx
  int v233; // edx
  int v234; // esi
  unsigned __int8 *v235; // edx
  int v236; // ecx
  int mm; // eax
  int *v238; // ebx
  double v239; // st7
  int v240; // eax
  int v241; // eax
  int v242; // eax
  float v243; // eax
  int v244; // eax
  bool v245; // ebx
  int v246; // eax
  int v247; // ecx
  int v248; // eax
  int v249; // eax
  int v250; // edx
  double v251; // st7
  double v252; // st6
  double v253; // st5
  double v254; // st7
  __int16 v255; // fps
  _BOOL1 v256; // c0
  char v257; // c2
  _BOOL1 v258; // c3
  int v259; // eax
  double v260; // st7
  double v261; // st6
  double v262; // st5
  double v263; // st7
  int v264; // ebx
  int v265; // eax
  int v266; // ebx
  int v267; // eax
  int v269; // ecx
  int v270; // esi
  int v271; // edi
  int v272; // eax
  float v274[9]; // [esp+0h] [ebp-298h] BYREF
  float v275; // [esp+24h] [ebp-274h]
  float v276; // [esp+28h] [ebp-270h]
  float v277; // [esp+2Ch] [ebp-26Ch]
  int v278; // [esp+7Ch] [ebp-21Ch]
  int v279; // [esp+80h] [ebp-218h]
  int v280; // [esp+84h] [ebp-214h]
  int v281; // [esp+88h] [ebp-210h]
  int v282; // [esp+8Ch] [ebp-20Ch]
  float v283; // [esp+90h] [ebp-208h]
  int v284; // [esp+94h] [ebp-204h]
  int v285; // [esp+98h] [ebp-200h]
  float *v286; // [esp+9Ch] [ebp-1FCh]
  int v287; // [esp+A0h] [ebp-1F8h]
  int v288; // [esp+A4h] [ebp-1F4h]
  int v289; // [esp+A8h] [ebp-1F0h]
  int v290; // [esp+ACh] [ebp-1ECh]
  float v291; // [esp+B0h] [ebp-1E8h]
  float v292; // [esp+B4h] [ebp-1E4h]
  int *v293; // [esp+B8h] [ebp-1E0h]
  int v294; // [esp+BCh] [ebp-1DCh] BYREF
  int v295; // [esp+C0h] [ebp-1D8h]
  float v296; // [esp+C4h] [ebp-1D4h]
  float v297; // [esp+CCh] [ebp-1CCh]
  float *v298; // [esp+D4h] [ebp-1C4h]
  float v299; // [esp+D8h] [ebp-1C0h]
  float v300; // [esp+DCh] [ebp-1BCh]
  int v301; // [esp+E0h] [ebp-1B8h]
  float v302; // [esp+E4h] [ebp-1B4h]
  int v303; // [esp+E8h] [ebp-1B0h]
  int v304; // [esp+F0h] [ebp-1A8h]
  float v305; // [esp+F4h] [ebp-1A4h]
  float v306; // [esp+F8h] [ebp-1A0h]
  float v307; // [esp+FCh] [ebp-19Ch]
  char v308[4]; // [esp+100h] [ebp-198h] BYREF
  char v309[4]; // [esp+104h] [ebp-194h] BYREF
  int v310; // [esp+108h] [ebp-190h]
  int v311; // [esp+10Ch] [ebp-18Ch]
  float v312; // [esp+110h] [ebp-188h]
  float v313; // [esp+114h] [ebp-184h]
  float v314; // [esp+118h] [ebp-180h]
  float v315; // [esp+11Ch] [ebp-17Ch]
  float v316; // [esp+120h] [ebp-178h]
  float v317; // [esp+124h] [ebp-174h]
  float v318; // [esp+128h] [ebp-170h]
  float v319; // [esp+12Ch] [ebp-16Ch]
  float v320; // [esp+130h] [ebp-168h]
  float v321; // [esp+134h] [ebp-164h]
  int v322; // [esp+138h] [ebp-160h]
  int v323; // [esp+13Ch] [ebp-15Ch]
  int v324; // [esp+140h] [ebp-158h]
  float v325; // [esp+144h] [ebp-154h]
  float v326; // [esp+148h] [ebp-150h]
  float v327; // [esp+14Ch] [ebp-14Ch]
  float v328; // [esp+150h] [ebp-148h]
  float v329; // [esp+154h] [ebp-144h]
  int v330; // [esp+158h] [ebp-140h]
  int v331; // [esp+15Ch] [ebp-13Ch]
  int v332; // [esp+160h] [ebp-138h]
  unsigned int v333; // [esp+164h] [ebp-134h]
  unsigned int v334; // [esp+168h] [ebp-130h]
  int v335; // [esp+16Ch] [ebp-12Ch]
  int v336; // [esp+170h] [ebp-128h]
  float v337; // [esp+174h] [ebp-124h]
  float v338; // [esp+178h] [ebp-120h]
  float v339; // [esp+17Ch] [ebp-11Ch]
  float v340; // [esp+180h] [ebp-118h]
  int v341; // [esp+184h] [ebp-114h]
  float v342; // [esp+188h] [ebp-110h]
  int v343; // [esp+18Ch] [ebp-10Ch]
  float v344; // [esp+190h] [ebp-108h]
  int v345; // [esp+194h] [ebp-104h]
  float v346; // [esp+198h] [ebp-100h]
  int v347; // [esp+19Ch] [ebp-FCh]
  int v348; // [esp+1A0h] [ebp-F8h]
  int v349; // [esp+1A4h] [ebp-F4h]
  int v350; // [esp+1A8h] [ebp-F0h]
  int v351; // [esp+1ACh] [ebp-ECh]
  int v352; // [esp+1B0h] [ebp-E8h]
  int v353; // [esp+1B4h] [ebp-E4h]
  int v354; // [esp+1B8h] [ebp-E0h]
  int v355; // [esp+1BCh] [ebp-DCh]
  float v356; // [esp+1C0h] [ebp-D8h]
  float v357; // [esp+1C4h] [ebp-D4h]
  float v358; // [esp+1C8h] [ebp-D0h]
  float v359; // [esp+1CCh] [ebp-CCh]
  float v360; // [esp+1D0h] [ebp-C8h]
  int v361; // [esp+1D4h] [ebp-C4h]
  float v362; // [esp+1D8h] [ebp-C0h]
  float v363; // [esp+1DCh] [ebp-BCh]
  float v364; // [esp+1E0h] [ebp-B8h]
  int v365; // [esp+1E4h] [ebp-B4h]
  int v366; // [esp+1E8h] [ebp-B0h]
  float v367; // [esp+1ECh] [ebp-ACh]
  float v368; // [esp+1F0h] [ebp-A8h]
  float v369; // [esp+1F4h] [ebp-A4h]
  float v370; // [esp+200h] [ebp-98h]
  float v371; // [esp+204h] [ebp-94h]
  float v372; // [esp+208h] [ebp-90h]
  float v373; // [esp+20Ch] [ebp-8Ch]
  float v374; // [esp+210h] [ebp-88h]
  float v375; // [esp+214h] [ebp-84h]
  float v376; // [esp+218h] [ebp-80h]
  float v377; // [esp+21Ch] [ebp-7Ch]
  float v378; // [esp+220h] [ebp-78h]
  int v379; // [esp+224h] [ebp-74h]
  int v380; // [esp+228h] [ebp-70h]
  float v381; // [esp+22Ch] [ebp-6Ch]
  float v382; // [esp+230h] [ebp-68h]
  float v383; // [esp+234h] [ebp-64h]
  float v384; // [esp+238h] [ebp-60h]
  float v385; // [esp+23Ch] [ebp-5Ch]
  float v386; // [esp+240h] [ebp-58h]
  float v387; // [esp+244h] [ebp-54h]
  float v388; // [esp+248h] [ebp-50h]
  float v389; // [esp+24Ch] [ebp-4Ch]
  int v390; // [esp+250h] [ebp-48h]
  float *v391; // [esp+254h] [ebp-44h]
  float v392; // [esp+264h] [ebp-34h]
  float v393; // [esp+268h] [ebp-30h]
  int v394; // [esp+278h] [ebp-20h]
  int v395; // [esp+27Ch] [ebp-1Ch]
  float v396; // [esp+280h] [ebp-18h]

  v284 = a1;
  v287 = a2;
  set_starts(0);
  v391 = &Car[77 * a1];
  v303 = *((unsigned __int8 *)v391 + 102);
  v380 = (unsigned __int8)CarDesigns_variable_1[28 * v303];
  v395 = (unsigned __int8)CarDesigns[28 * v303];
  if (*((__int16 *)v391 + 6) == -1 || paused) {
    LOWORD(v6) = 0;
    LOWORD(v7) = 0;
    LOWORD(v8) = 0;
  } else {
    v6 = *((_DWORD *)v391 + 41);
    v7 = *((_DWORD *)v391 + 42);
    v8 = *((_DWORD *)v391 + 43);
  }
  v9 = *((_DWORD *)v391 + 39) + v6 + *((_WORD *)v391 + 8) + *((_DWORD *)v391 + 34);
  v10 = ((_WORD)v8 + *((_WORD *)v391 + 10)) & 0x3FFF;
  v11 = ((unsigned __int16)*((_DWORD *)v391 + 37)
       + (_WORD)v7
       + (unsigned __int16)*((_DWORD *)v391 + 33)
       + *((_WORD *)v391 + 9)) & 0x3FFF;
  v389 = tcos[v10] * tcos[v11];
  v388 = tsin[v10] * tcos[v11];
  v12 = tcos[v10];
  v390 = v10;
  v387 = tsin[v11];
  v13 = v9 & 0x3FFF;
  v386 = v12 * v387 * tsin[v13] - tsin[v10] * tcos[v13];
  v385 = tsin[v10] * v387 * tsin[v13] + tcos[v10] * tcos[v13];
  v384 = -tsin[v13] * tcos[v11];
  v383 = -tcos[v10] * v387 * tcos[v13] - tsin[v10] * tsin[v13];
  v382 = -tsin[v10] * v387 * tcos[v13] + tcos[v10] * tsin[v13];
  v14 = tcos[v11] * tcos[v13];
  v378 = *v391;
  v377 = v391[1];
  v15 = v391[2];
  v381 = v14;
  v376 = v15;
  v379 = *((__int16 *)v391 + 6);
  v290 = car_flat_remap[2 * v303];
  v289 = car_flat_remap_variable_1[2 * v303];
  v394 = (int)*(&CarDesigns_variable_7 + 7 * v303);
  if (a3 >= (double)car_c_variable_15 && VisibleCars >= 4
    || (textures_off & 0x100) != 0
    || a3 <= 0.0
    || (*((_BYTE *)v391 + 131) & 2) != 0) {
    goto LABEL_117;
  }
  v16 = *((__int16 *)v391 + 6);
  if (v16 == -1)
    v16 = *((_DWORD *)v391 + 54);
  v17 = (float *)((char *)&localdata + 128 * v16);
  if (*((__int16 *)v391 + 6) == -1)
    getlocalangles(v309, v308, &v294);
  else
    v294 = v13;
  v18 = *((_BYTE *)v391 + 102);
  v292 = *(float *)CarBox_variable_20 - *(float *)CarBox_variable_11;
  if (v18 > 7u)
    v304 = CarBaseY;
  else
    *(float *)&v304 = *(float *)&CarBaseY + car_c_variable_16;
  if (*((__int16 *)v391 + 6) == -1) {
    if (v294 > 4096) {
      if (v294 <= 0x2000) {
        carpoint[0] = *(float *)&CarBaseX;
        *(float *)carpoint_variable_1 = -*(float *)&v304;
        carpoint_variable_3 = -*(float *)&CarBaseX;
        carpoint_variable_4 = carpoint_variable_1[0];
        carpoint_variable_6 = carpoint_variable_3;
        *(float *)carpoint_variable_2 = v292;
        carpoint_variable_5 = LODWORD(v292);
        carpoint_variable_8 = 0;
        carpoint_variable_11[0] = 0;
        LODWORD(carpoint_variable_7) = v304;
        carpoint_variable_10 = v304;
        carpoint_variable_9 = *(float *)&CarBaseX;
        goto LABEL_28;
      }
      if (v294 <= 12288) {
        carpoint[0] = *(float *)&CarBaseX;
        *(float *)carpoint_variable_1 = -*(float *)&v304;
        carpoint_variable_3 = -*(float *)&CarBaseX;
        carpoint_variable_4 = carpoint_variable_1[0];
        carpoint_variable_2[0] = 0;
        carpoint_variable_5 = 0;
        carpoint_variable_6 = carpoint_variable_3;
        LODWORD(carpoint_variable_7) = v304;
        carpoint_variable_8 = LODWORD(v292);
        carpoint_variable_10 = v304;
        *(float *)carpoint_variable_11 = v292;
        carpoint_variable_9 = *(float *)&CarBaseX;
        goto LABEL_28;
      }
      carpoint[0] = *(float *)&CarBaseX;
      carpoint_variable_3 = -*(float *)&CarBaseX;
      carpoint_variable_6 = carpoint_variable_3;
      carpoint_variable_7 = -*(float *)&v304;
      carpoint_variable_9 = *(float *)&CarBaseX;
      v19 = carpoint_variable_7;
      carpoint_variable_1[0] = v304;
      carpoint_variable_2[0] = 0;
      carpoint_variable_4 = v304;
      carpoint_variable_5 = 0;
      carpoint_variable_8 = LODWORD(v292);
      *(float *)carpoint_variable_11 = v292;
    } else {
      carpoint[0] = *(float *)&CarBaseX;
      carpoint_variable_3 = -*(float *)&CarBaseX;
      carpoint_variable_6 = carpoint_variable_3;
      carpoint_variable_7 = -*(float *)&v304;
      carpoint_variable_9 = *(float *)&CarBaseX;
      carpoint_variable_1[0] = v304;
      v19 = carpoint_variable_7;
      *(float *)carpoint_variable_2 = v292;
      carpoint_variable_8 = 0;
      carpoint_variable_4 = v304;
      carpoint_variable_11[0] = 0;
      carpoint_variable_5 = LODWORD(v292);
    }
  } else {
    carpoint[0] = *(float *)&CarBaseX;
    carpoint_variable_3 = -*(float *)&CarBaseX;
    carpoint_variable_6 = carpoint_variable_3;
    carpoint_variable_7 = -*(float *)&v304;
    carpoint_variable_9 = *(float *)&CarBaseX;
    v19 = carpoint_variable_7;
    carpoint_variable_1[0] = v304;
    carpoint_variable_2[0] = 0;
    carpoint_variable_4 = v304;
    carpoint_variable_5 = 0;
    carpoint_variable_8 = 0;
    carpoint_variable_11[0] = 0;
  }
  *(float *)&carpoint_variable_10 = v19;
LABEL_28:
  if (*((__int16 *)v391 + 6) == -1) {
    v20 = v391;
    v21 = 0;
    v22 = v381;
    v23 = v387;
    v24 = v384;
    v25 = v382;
    v26 = v388;
    do {
      carworld[v21] = *(float *)&carpoint_variable_1[v21] * v386
        + carpoint[v21] * v389
        + *(float *)&carpoint_variable_2[v21] * v383
        + *v20;
      carworld_variable_1[v21] = *(float *)&carpoint_variable_1[v21] * v385
        + carpoint[v21] * v26
        + *(float *)&carpoint_variable_2[v21] * v25
        + v20[1];
      v27 = *(float *)&carpoint_variable_1[v21] * v24
        + carpoint[v21] * v23
        + *(float *)&carpoint_variable_2[v21] * v22
        + v20[2];
      v21 += 3;
      wConsoleNode_variable_1[v21] = v27;
    } while (v21 != 12);
    for (i = 0; i != 12; *(float *)&carpoint_variable_11[i] = v29) {
      carlocal[i] = (carworld_variable_1[i] + v17[10]) * v17[3]
        + (carworld[i] + v17[9]) * *v17
        + (carworld_variable_2[i] + v17[11]) * v17[6];
      carlocal_variable_1[i] = (carworld_variable_1[i] + v17[10]) * v17[4]
        + (carworld[i] + v17[9]) * v17[1]
        + (carworld_variable_2[i] + v17[11]) * v17[7];
      v29 = (carworld_variable_1[i] + v17[10]) * v17[5]
        + (carworld[i] + v17[9]) * v17[2]
        + (carworld_variable_2[i] + v17[11]) * v17[8];
      i += 3;
    }
  } else {
    v30 = v391;
    v31 = 0;
    v32 = v381;
    v33 = v387;
    v34 = v384;
    v35 = v382;
    v36 = v388;
    do {
      carlocal[v31] = v386 * *(float *)&carpoint_variable_1[v31]
        + v389 * carpoint[v31]
        + v383 * *(float *)&carpoint_variable_2[v31]
        + *v30;
      carlocal_variable_1[v31] = v385 * *(float *)&carpoint_variable_1[v31]
        + v36 * carpoint[v31]
        + v35 * *(float *)&carpoint_variable_2[v31]
        + v30[1];
      v37 = v34 * *(float *)&carpoint_variable_1[v31]
        + v33 * carpoint[v31]
        + v32 * *(float *)&carpoint_variable_2[v31]
        + v30[2];
      v31 += 3;
      *(float *)&carpoint_variable_11[v31] = v37;
    } while (v31 != 12);
  }
  v38 = *((__int16 *)v391 + 6);
  v293 = &TrackInfo[9 * v16];
  if (v38 == -1) {
    v291 = v378;
    v283 = v377;
    v307 = v376;
  } else {
    v39 = (float *)((char *)&localdata + 128 * v38);
    v291 = v39[1] * v377 + *v39 * v378 + v39[2] * v376 - v39[9];
    v283 = v39[3] * v378 + v39[4] * v377 + v39[5] * v376 - v39[10];
    v307 = v377 * v39[7] + v378 * v39[6] + v376 * v39[8] - v39[11];
  }
  v40 = v291 + v17[9];
  v41 = v283 + v17[10];
  v42 = v307 + v17[11];
  v306 = v17[1] * v40 + v17[4] * v41 + v17[7] * v42;
  v305 = v40 * v17[2] + v41 * v17[5] + v42 * v17[8];
  v336 = 0;
  if (v306 <= 0.0) {
    if (-v17[13] < v306) {
      v44 = v293[7];
      if ((v44 == 5 || v44 == 6 || v44 == 9) && v305 < (double)*((float *)v293 + 8))
        goto LABEL_51;
    }
  } else if (v306 < (double)v17[13]) {
    v43 = v293[6];
    if ((v43 == 5 || v43 == 6 || v43 == 9) && v305 < (double)*((float *)v293 + 8))
      LABEL_51:
    v336 = -1;
  }
  v45 = *((_DWORD *)v391 + 53);
  v288 = -1;
  v46 = 0;
  v47 = *((int *)&TrakColour + 6 * v16 + v45);
  if ((((HIDWORD(v47) ^ (unsigned int)v47) - HIDWORD(v47)) & 0x20000) != 0 && GroundColour_variable_4[5 * v16] < 0)
    v288 = 0;
  HIDWORD(v48) = GroundColour_variable_4[5 * v16];
  if (HIDWORD(v48) == -2) {
    v75 = v336;
    v76 = 0;
    while (1) {
      HIWORD(v82) = HIWORD(v293);
      v78 = v17[13] + *(float *)v293;
      v79 = v78 < carlocal_variable_1[v76];
      v80 = 0;
      v81 = v78 == carlocal_variable_1[v76];
      LOWORD(v82) = v77;
      if (v78 < carlocal_variable_1[v76]
        || (HIWORD(v82) = HIWORD(v293),
            v84 = -v17[13] - *((float *)v293 + 2),
            v85 = v84 < carlocal_variable_1[v76],
            v86 = 0,
            v87 = v84 == carlocal_variable_1[v76],
            LOWORD(v82) = v83,
            v84 > carlocal_variable_1[v76])) {
        if (!v75) {
          v88 = getbankz(carlocal_variable_1[v76], v16, 0);
          goto LABEL_101;
        }
      } else if (!v336) {
        v88 = getgroundz(v82, carlocal[v76], carlocal_variable_1[v76], v16);
        goto LABEL_101;
      }
      v88 = getroadz(v82, v76 * 4, carlocal[v76], carlocal_variable_1[v76], v16);
    LABEL_101:
      v297 = v88;
      if (v297 >= (double)carlocal_variable_2[v76])
        ++v46;
      else
        carlocal_variable_2[v76] = v297;
      v76 += 3;
      if (v76 == 12)
        goto LABEL_105;
    }
  }
  v285 = 0;
  if (HIDWORD(v48) == -1)
    v285 = -1;
  v49 = 0;
  LODWORD(v48) = 24 * v16;
  v50 = 0;
  v311 = 24 * v16;
  do {
    if (v336)
      v51 = getroadz(v48, SHIDWORD(v48), carlocal[v49], carlocal_variable_1[v49], v16);
    else
      v51 = getgroundz(v48, carlocal[v49], carlocal_variable_1[v49], v16);
    roadheight[v50] = v51;
    WORD1(v48) = HIWORD(v293);
    v53 = v17[13] + *(float *)v293;
    v54 = v53 < carlocal_variable_1[v49];
    v55 = 0;
    v56 = v53 == carlocal_variable_1[v49];
    LOWORD(v48) = v52;
    if (v53 >= carlocal_variable_1[v49]) {
      WORD1(v48) = HIWORD(v293);
      v58 = -v17[13] - *((float *)v293 + 2);
      v59 = v58 < carlocal_variable_1[v49];
      v60 = 0;
      v61 = v58 == carlocal_variable_1[v49];
      LOWORD(v48) = v57;
      if (v58 <= carlocal_variable_1[v49]) {
        v361 = 4 * *((_DWORD *)v391 + 53);
        v48 = *(int *)((char *)&TrakColour + v361 + v311);
        LODWORD(v48) = abs32(*(_DWORD *)((char *)&TrakColour + v361 + v311));
        if ((v48 & 0x20000) == 0) {
          v63 = roadheight[v50] + car_c_variable_21;
          v64 = v63 < carlocal_variable_2[v49];
          v65 = 0;
          v66 = v63 == carlocal_variable_2[v49];
          LOWORD(v48) = v62;
          if (v63 <= carlocal_variable_2[v49])
            v285 = -1;
        }
      }
    }
    ++v50;
    v49 += 3;
  } while (v50 != 4);
  if (v285) {
    v67 = 0;
    for (j = 0; j != 4; ++j) {
      v337 = roadheight[j];
      if (v337 >= (double)carlocal_variable_2[v67])
        ++v46;
      else
        carlocal_variable_2[v67] = v337;
      v67 += 3;
    }
  } else if (GroundColour_variable_4[5 * v16] < 2 || *((_DWORD *)v391 + 18) == 3) {
    for (k = 0; k != 12; k += 3) {
      if (v336)
        v74 = getroadz(v336, k * 4, carlocal[k], carlocal_variable_1[k], v16);
      else
        v74 = getbankz(carlocal_variable_1[k], v16, 0);
      v339 = v74;
      if (v339 >= (double)carlocal_variable_2[k])
        ++v46;
      else
        carlocal_variable_2[k] = v339;
    }
  } else {
    v17 = v274;
    calculateseparatedcoordinatesystem(v16, (int)v274);
    for (m = 0; m != 12; *(float *)&carpoint_variable_11[m] = v70) {
      carlocal[m] = (carworld_variable_1[m] + v276) * v274[3]
        + (carworld[m] + v275) * v274[0]
        + (carworld_variable_2[m] + v277) * v274[6];
      carlocal_variable_1[m] = (carworld_variable_1[m] + v276) * v274[4]
        + (carworld[m] + v275) * v274[1]
        + (carworld_variable_2[m] + v277) * v274[7];
      v70 = (carworld_variable_1[m] + v276) * v274[5]
        + (carworld[m] + v275) * v274[2]
        + (carworld_variable_2[m] + v277) * v274[8];
      m += 3;
    }
    for (n = 0; n != 12; n += 3) {
      v72 = getbankz(carlocal_variable_1[n], v16, v274);
      v338 = v72;
      if (v72 < carlocal_variable_2[n])
        carlocal_variable_2[n] = v338;
    }
  }
LABEL_105:
  if (v288 && *((_DWORD *)v391 + 18) != 3 && v46 >= 2)
    v288 = 0;
  if (v288) {
    *(float *)&v89 = 0.0;
    do {
      *(float *)((char *)carworld + v89) = v17[1] * *(float *)((char *)carlocal_variable_1 + v89)
        + *v17 * *(float *)((char *)carlocal + v89)
        + v17[2] * *(float *)((char *)carlocal_variable_2 + v89)
        - v17[9];
      *(float *)((char *)carworld_variable_1 + v89) = v17[4] * *(float *)((char *)carlocal_variable_1 + v89)
        + v17[3] * *(float *)((char *)carlocal + v89)
        + v17[5] * *(float *)((char *)carlocal_variable_2 + v89)
        - v17[10];
      v90 = v17[7] * *(float *)((char *)carlocal_variable_1 + v89)
        + v17[6] * *(float *)((char *)carlocal + v89)
        + v17[8] * *(float *)((char *)carlocal_variable_2 + v89)
        - v17[11];
      v89 += 12;
      *(float *)((char *)wConsoleNode_variable_1 + v89) = v90;
    } while (v89 != 48);
    v91 = scr_size;
    for (ii = 0; ii != 12; carworld_variable_3[ii] = (float)v89) {
      v93 = carworld[ii] - viewx;
      v94 = carworld_variable_1[ii] - viewy;
      v95 = carworld_variable_2[ii] - viewz;
      v302 = v93 * vk1 + v94 * vk4 + v95 * vk7;
      v369 = v93 * vk2 + v94 * vk5 + v95 * vk8;
      v96 = v93 * vk3 + v94 * vk6 + v95 * vk9;
      v300 = v96;
      v98 = v96 < car_c_variable_20;
      v99 = 0;
      v100 = v96 == car_c_variable_20;
      LOWORD(v89) = v97;
      if (v96 < car_c_variable_20)
        v300 = 80.0;
      v101 = (double)VIEWDIST;
      v102 = 1.0 / v300;
      v103 = v101 * v302 * v102 + (double)xbase;
      _CHP(v89, ii * 4);
      xp = (int)v103;
      v104 = v102 * (v101 * v369) + (double)ybase;
      _CHP(v91 * (int)v103, ii * 4);
      yp = (int)v104;
      carpoint[ii] = (float)(v105 >> 6);
      v89 = (v91 * (199 - (int)v104)) >> 6;
      v361 = v89;
      ii += 3;
    }
    v106 = carpoint[0];
    _CHP(v89, 48);
    CarPol_variable_3 = (int)v106;
    v107 = *(float *)carpoint_variable_1;
    _CHP(v108, 48);
    CarPol_variable_4 = (int)v107;
    v109 = carpoint_variable_3;
    _CHP(v110, 48);
    CarPol_variable_5 = (int)v109;
    v111 = *(float *)&carpoint_variable_4;
    _CHP(v112, 48);
    CarPol_variable_6 = (int)v111;
    v113 = carpoint_variable_6;
    _CHP(v114, 48);
    CarPol_variable_7 = (int)v113;
    v115 = carpoint_variable_7;
    _CHP(v116, 48);
    CarPol_variable_8 = (int)v115;
    v117 = carpoint_variable_9;
    _CHP(v118, 48);
    CarPol_variable_9 = (int)v117;
    v119 = *(float *)&carpoint_variable_10;
    _CHP(v120, 48);
    CarPol_variable_2 = 4;
    CarPol = 2105346;
    CarPol_variable_10 = (int)v119;
    POLYFLAT(v287, &CarPol);
  }
LABEL_117:
  v121 = (float *)*(&CarDesigns_variable_3 + 7 * v303);
  v122 = (unsigned __int8 *)*(&CarDesigns_variable_2 + 7 * v303);
  if ((Car_variable_33[308 * v284] & 2) != 0) {
    v395 = 0;
    v380 = 0;
  }
  v368 = tsin[((_WORD)warp_angle + ((_WORD)v284 << 11)) & 0x3FFF] * car_c_variable_17;
  if (v380 > 0) {
    v123 = 0;
    v124 = 32 * v380;
    v125 = (float *)((char *)&localdata + 128 * v379);
    do {
      v126 = *v121;
      v127 = v121 + 1;
      v372 = v126;
      v128 = *v127++;
      v371 = v128;
      v129 = *v127;
      v121 = v127 + 1;
      v370 = v129;
      if ((cheat_mode & 0x8000) != 0) {
        v372 = v372 * car_c_variable_18;
        v371 = car_c_variable_18 * v371;
      }
      if (((unsigned int)cstart_branch_1 & cheat_mode) != 0) {
        v372 = v372 * v368 + v372;
        v371 = v371 * v368 + v371;
        v370 = v368 * v370 + v370;
      }
      v130 = v372;
      v131 = v371;
      v132 = v370;
      CarPt_variable_2[v123 / 4] = v372 * v389 + v371 * v386 + v370 * v383 + v378;
      CarPt_variable_3[v123 / 4] = v130 * v388 + v131 * v385 + v132 * v382 + v377;
      v133 = v379;
      CarPt_variable_4[v123 / 4] = v130 * v387 + v131 * v384 + v132 * v381 + v376;
      if (v133 != -1) {
        v134 = v125[1];
        v375 = CarPt_variable_2[v123 / 4];
        v374 = CarPt_variable_3[v123 / 4];
        v135 = v134 * v374 + *v125 * v375;
        v136 = v125[2];
        v373 = CarPt_variable_4[v123 / 4];
        CarPt_variable_2[v123 / 4] = v135 + v136 * v373 - v125[9];
        CarPt_variable_3[v123 / 4] = v125[3] * v375 + v125[4] * v374 + v125[5] * v373 - v125[10];
        v137 = v125[6] * v375 + v125[7] * v374 + v125[8] * v373 - v125[11];
        v298 = v125;
        CarPt_variable_4[v123 / 4] = v137;
      }
      v138 = CarPt_variable_2[v123 / 4] - viewx;
      v139 = CarPt_variable_3[v123 / 4] - viewy;
      v140 = CarPt_variable_4[v123 / 4] - viewz;
      *(float *)&v355 = v138 * vk1 + v139 * vk4 + v140 * vk7;
      *(float *)&v351 = v138 * vk2 + v139 * vk5 + v140 * vk8;
      v141 = v138 * vk3 + v139 * vk6 + v140 * vk9;
      *(float *)&v347 = v141;
      HIWORD(v146) = HIWORD(v347);
      v343 = v347;
      v143 = v141 < car_c_variable_20;
      v144 = 0;
      v145 = v141 == car_c_variable_20;
      LOWORD(v146) = v142;
      if (v141 < car_c_variable_20)
        *(float *)&v347 = 80.0;
      v147 = (double)VIEWDIST;
      v148 = 1.0 / *(float *)&v347;
      v149 = v147 * *(float *)&v355 * v148 + (double)xbase;
      _CHP(v146, v125);
      xp = (int)v149;
      v150 = v148 * (v147 * *(float *)&v351) + (double)ybase;
      _CHP(scr_size * (int)v149, v125);
      yp = (int)v150;
      CarPt[v123 / 4] = v151 >> 6;
      v123 += 32;
      carlocal_variable_3[v123 / 4] = (scr_size * (199 - yp)) >> 6;
      roadheight_variable_1[v123 / 4] = v355;
      roadheight_variable_2[v123 / 4] = v351;
      roadheight_variable_3[v123 / 4] = v343;
    } while ((int)v123 < v124);
  }
  v152 = 0;
  v366 = 0;
  if (v395 > 0) {
    v153 = 0;
    do {
      v154 = v122;
      for (jj = 0; jj != 16; *(int *)((char *)&v278 + jj) = (int)v156) {
        jj += 4;
        v156 = &CarPt[8 * *v154++];
      }
      v157 = *(float *)(v281 + 20) - *(float *)(v279 + 20);
      v299 = *(float *)(v281 + 24) - *(float *)(v279 + 24);
      v158 = *(float *)(v281 + 28) - *(float *)(v279 + 28);
      v393 = *(float *)(v280 + 20);
      v296 = *(float *)(v280 + 24);
      v392 = *(float *)(v280 + 28);
      v159 = v393 - *(float *)(v282 + 20);
      v160 = v296 - *(float *)(v282 + 24);
      v161 = v392 - *(float *)(v282 + 28);
      v162 = v122[5];
      v367 = (v299 * v161 - v158 * v160) * v393
        + (v158 * v159 - v161 * v157) * v296
        + (v160 * v157 - v159 * v299) * v392;
      if ((v162 & 0x20) != 0 || v367 <= 0.0) {
        if (v367 > 0.0 && (v122[5] & 8) != 0)
          v163 = -v366 - 1;
        else
          v163 = v366;
        CarZOrder_variable_1[v153] = v163;
        CarZOrder[v153] = *((__int16 *)v122 + 4);
        if ((v122[5] & 0x80u) == 0) {
          if (CarPt_variable_7[8 * v122[2]] <= (double)CarPt_variable_7[8 * v122[3]])
            v167 = CarPt_variable_7[8 * v122[3]];
          else
            v167 = CarPt_variable_7[8 * v122[2]];
          v317 = v167;
          if (CarPt_variable_7[8 * *v122] <= (double)CarPt_variable_7[8 * v122[1]])
            v168 = CarPt_variable_7[8 * v122[1]];
          else
            v168 = CarPt_variable_7[8 * *v122];
          v318 = v168;
          if (v168 <= (double)v317) {
            if (CarPt_variable_7[8 * v122[2]] <= (double)CarPt_variable_7[8 * v122[3]])
              v166 = CarPt_variable_7[8 * v122[3]];
            else
              v166 = CarPt_variable_7[8 * v122[2]];
            v321 = v166;
          } else {
            if (CarPt_variable_7[8 * *v122] <= (double)CarPt_variable_7[8 * v122[1]])
              v166 = CarPt_variable_7[8 * v122[1]];
            else
              v166 = CarPt_variable_7[8 * *v122];
            v320 = v166;
          }
          v319 = v166;
        } else {
          if (CarPt_variable_7[8 * v122[2]] >= (double)CarPt_variable_7[8 * v122[3]])
            v164 = CarPt_variable_7[8 * v122[3]];
          else
            v164 = CarPt_variable_7[8 * v122[2]];
          v312 = v164;
          if (CarPt_variable_7[8 * *v122] >= (double)CarPt_variable_7[8 * v122[1]])
            v165 = CarPt_variable_7[8 * v122[1]];
          else
            v165 = CarPt_variable_7[8 * *v122];
          v313 = v165;
          if (v165 >= (double)v312) {
            if (CarPt_variable_7[8 * v122[2]] >= (double)CarPt_variable_7[8 * v122[3]])
              v166 = CarPt_variable_7[8 * v122[3]];
            else
              v166 = CarPt_variable_7[8 * v122[2]];
            v316 = v166;
          } else {
            if (CarPt_variable_7[8 * *v122] >= (double)CarPt_variable_7[8 * v122[1]])
              v166 = CarPt_variable_7[8 * v122[1]];
            else
              v166 = CarPt_variable_7[8 * *v122];
            v315 = v166;
          }
          v314 = v166;
        }
        CarZOrder_variable_2[v153] = v166;
        v153 += 3;
        ++v152;
      }
      v122 += 12;
      ++v366;
    } while (v366 < v395);
  }
  if (v152 > 0) {
    v365 = 0;
    v323 = 28 * v303;
    v169 = (int)*(&CarDesigns_variable_2 + 7 * v303);
    v334 = 0;
    v322 = v169;
    do {
      v170 = CarZOrder_variable_1[v334 / 4];
      if (v170 < 0)
        v170 = -1 - v170;
      v171 = *(__int16 *)(v322 + 12 * v170 + 8);
      v172 = v365;
      if (v171 >= 0) {
        v324 = *(int *)((char *)&CarDesigns_variable_2 + v323);
        do {
          v173 = -1;
          for (kk = 0; kk < v152; ++kk) {
            v175 = CarZOrder_variable_1[3 * kk];
            if (v175 < 0)
              v175 = -1 - v175;
            if (v171 == v175) {
              v173 = kk;
              kk = v152;
            }
          }
          if (v173 > 0)
            CarZOrder_variable_2[3 * v173] = CarZOrder_variable_2[3 * v172] + car_c_variable_22;
          v171 = *(__int16 *)(v324 + 12 * v171 + 8);
          v172 = v173;
        } while (v171 >= 0);
      }
      v334 += 12;
      ++v365;
    } while (v152 > v365);
  }
  if (v152 > 0 || (Car_variable_33[308 * v284] & 2) != 0) {
    v176 = 0;
    v177 = (float *)((char *)&localdata + 128 * v379);
    v286 = (float *)&CarSpray[1408 * v284];
    v178 = v286;
    v179 = 0;
    v180 = 3 * v152;
    do {
      if (*((int *)v178 + 7) > 0) {
        v358 = *v178;
        v357 = v178[1];
        v356 = v178[2];
        SmokePt_variable_2[v179] = v358 * v389 + v357 * v386 + v356 * v383 + v378;
        SmokePt_variable_3[v179] = v358 * v388 + v357 * v385 + v356 * v382 + v377;
        v181 = v379;
        SmokePt_variable_4[v179] = v358 * v387 + v357 * v384 + v356 * v381 + v376;
        if (v181 != -1) {
          v182 = v177[1];
          v396 = SmokePt_variable_2[v179];
          v363 = SmokePt_variable_3[v179];
          v183 = v182 * v363 + *v177 * v396;
          v184 = v177[2];
          v361 = SLODWORD(SmokePt_variable_4[v179]);
          SmokePt_variable_2[v179] = v183 + v184 * *(float *)&v361 - v177[9];
          SmokePt_variable_3[v179] = v177[3] * v396 + v177[4] * v363 + v177[5] * *(float *)&v361 - v177[10];
          v185 = v177[6] * v396 + v177[7] * v363 + v177[8] * *(float *)&v361 - v177[11];
          v298 = v177;
          SmokePt_variable_4[v179] = v185;
        }
        v186 = SmokePt_variable_2[v179] - viewx;
        v187 = SmokePt_variable_3[v179] - viewy;
        v188 = SmokePt_variable_4[v179] - viewz;
        *(float *)&v354 = v186 * vk1 + v187 * vk4 + v188 * vk7;
        *(float *)&v350 = v186 * vk2 + v187 * vk5 + v188 * vk8;
        v189 = v186 * vk3 + v187 * vk6 + v188 * vk9;
        v346 = v189;
        HIWORD(v194) = HIWORD(v346);
        v342 = v346;
        v191 = v189 < car_c_variable_20;
        v192 = 0;
        v193 = v189 == car_c_variable_20;
        LOWORD(v194) = v190;
        if (v189 < car_c_variable_20)
          v346 = 80.0;
        v195 = (double)VIEWDIST;
        v196 = 1.0 / v346;
        v197 = v195 * *(float *)&v354 * v196 + (double)xbase;
        _CHP(v194, v179 * 4);
        xp = (int)v197;
        v198 = v196 * (v195 * *(float *)&v350) + (double)ybase;
        _CHP(scr_size * (int)v197, v179 * 4);
        yp = (int)v198;
        SmokePt[v179] = v199 >> 6;
        SmokePt_variable_1[v179] = (scr_size * (199 - yp)) >> 6;
        SmokePt_variable_5[v179] = v354;
        SmokePt_variable_6[v179] = v350;
        SmokePt_variable_7[v179] = v342;
        if (*((_BYTE *)v178 + 40) == 1) {
          v358 = v358 + v178[3];
          v357 = v357 + v178[4];
          v356 = v356 + v178[5];
          SmokePt_variable_10[v179] = v358 * v389 + v357 * v386 + v356 * v383 + v378;
          SmokePt_variable_11[v179] = v358 * v388 + v357 * v385 + v356 * v382 + v377;
          v200 = v379;
          SmokePt_variable_12[v179] = v358 * v387 + v357 * v384 + v356 * v381 + v376;
          if (v200 != -1) {
            v201 = v177[1];
            v396 = SmokePt_variable_10[v179];
            v363 = SmokePt_variable_11[v179];
            v202 = v201 * v363 + *v177 * v396;
            v203 = v177[2];
            v361 = SLODWORD(SmokePt_variable_12[v179]);
            SmokePt_variable_10[v179] = v202 + v203 * *(float *)&v361 - v177[9];
            SmokePt_variable_11[v179] = v177[3] * v396 + v177[4] * v363 + v177[5] * *(float *)&v361 - v177[10];
            v204 = v177[6] * v396 + v177[7] * v363 + v177[8] * *(float *)&v361 - v177[11];
            v298 = v177;
            SmokePt_variable_12[v179] = v204;
          }
          v205 = SmokePt_variable_10[v179] - viewx;
          v206 = SmokePt_variable_11[v179] - viewy;
          v207 = SmokePt_variable_12[v179] - viewz;
          *(float *)&v353 = v205 * vk1 + v206 * vk4 + v207 * vk7;
          *(float *)&v349 = v205 * vk2 + v206 * vk5 + v207 * vk8;
          v208 = v205 * vk3 + v206 * vk6 + v207 * vk9;
          *(float *)&v345 = v208;
          HIWORD(v213) = HIWORD(v345);
          v341 = v345;
          v210 = v208 < car_c_variable_20;
          v211 = 0;
          v212 = v208 == car_c_variable_20;
          LOWORD(v213) = v209;
          if (v208 < car_c_variable_20)
            *(float *)&v345 = 80.0;
          v214 = (double)VIEWDIST;
          v215 = 1.0 / *(float *)&v345;
          v216 = v214 * *(float *)&v353 * v215 + (double)xbase;
          _CHP(v213, v179 * 4);
          xp = (int)v216;
          v217 = v215 * (v214 * *(float *)&v349) + (double)ybase;
          _CHP(scr_size * (int)v216, v179 * 4);
          yp = (int)v217;
          SmokePt_variable_8[v179] = v218 >> 6;
          SmokePt_variable_9[v179] = (scr_size * (199 - yp)) >> 6;
          SmokePt_variable_13[v179] = v353;
          SmokePt_variable_14[v179] = v349;
          SmokePt_variable_15[v179] = v341;
        }
        CarZOrder_variable_1[v180] = v176;
        CarZOrder[v180] = -2;
        if (*((_BYTE *)v178 + 40) == 2)
          CarZOrder_variable_2[v180] = SmokePt_variable_7[v179] + car_c_variable_23;
        else
          CarZOrder_variable_2[v180] = SmokePt_variable_7[v179];
        v180 += 3;
        ++v152;
      }
      v179 += 8;
      ++v176;
      v178 += 11;
    } while (v176 < 32);
    qsort(CarZOrder, v152, 12, carZcmp);
    if (CarZOrder_variable_2[0] <= (double)car_c_variable_19 || VisibleCars < 5)
      v301 = -1;
    else
      v301 = 0;
    if ((textures_off & 0x40) != 0)
      v301 = 0;
    if (v152 > 0) {
      v332 = v284 + 3;
      v333 = 4 * v284;
      v330 = 28 * v303;
      v331 = 4 * (v284 & 1);
      v219 = 0;
      v335 = 12 * v152;
      do {
        if (CarZOrder[v219 / 4] >= -1) {
          CarZOrder_variable_2[v219 / 4] = -1.0;
          v234 = CarZOrder_variable_1[v219 / 4];
          CarZOrder[v219 / 4] = -1;
          if (v234 >= 0) {
            v310 = 0;
          } else {
            v310 = -1;
            v234 = -1 - v234;
          }
          v235 = (unsigned __int8 *)(*(char **)((char *)&CarDesigns_variable_2 + v330) + 12 * v234);
          v236 = *((_DWORD *)v235 + 1);
          for (mm = 0; mm != 16; *(int *)((char *)&v278 + mm) = (int)v238) {
            mm += 4;
            v238 = &CarPt[8 * *v235++];
          }
          v239 = *(float *)(v281 + 28);
          CarPol_variable_2 = 4;
          if (v239 >= *(float *)(v282 + 28))
            v240 = v282;
          else
            v240 = v281;
          v325 = *(float *)(v240 + 28);
          if (*(float *)(v279 + 28) >= (double)*(float *)(v280 + 28))
            v241 = v280;
          else
            v241 = v279;
          v326 = *(float *)(v241 + 28);
          if (v326 >= (double)v325) {
            if (*(float *)(v281 + 28) >= (double)*(float *)(v282 + 28))
              v244 = v282;
            else
              v244 = v281;
            v329 = *(float *)(v244 + 28);
            v243 = v329;
          } else {
            if (*(float *)(v279 + 28) >= (double)*(float *)(v280 + 28))
              v242 = v280;
            else
              v242 = v279;
            v328 = *(float *)(v242 + 28);
            v243 = v328;
          }
          v327 = v243;
          CarPol_variable_3 = *(_DWORD *)v279;
          CarPol_variable_4 = *(_DWORD *)(v279 + 4);
          CarPol_variable_5 = *(_DWORD *)v280;
          CarPol_variable_6 = *(_DWORD *)(v280 + 4);
          CarPol_variable_7 = *(_DWORD *)v281;
          CarPol_variable_8 = *(_DWORD *)(v281 + 4);
          CarPol_variable_9 = *(_DWORD *)v282;
          CarPol_variable_10 = *(_DWORD *)(v282 + 4);
          v245 = v243 < 1.0;
          v246 = (unsigned __int8)v236;
          if (v310) {
            v236 = (*(_DWORD **)((char *)&CarDesigns_variable_4 + v330))[v234];
            BYTE1(v236) |= 0x20u;
          } else if ((v236 & 0x200) != 0) {
            v247 = v394 + 68 * (unsigned __int8)v236;
            if (v246 >= 4)
              v236 = *(_DWORD *)(v331 + v247 + 4);
            else
              v236 = *(_DWORD *)(v247 + 4 * *((char *)v391 + 278) + 4);
          }
          if ((v236 & 0x800) != 0)
            BYTE1(v236) ^= 8u;
          if ((v236 & 0x100) != 0 && !v301) {
            v248 = (unsigned __int8)v236;
            LOWORD(v236) = v236 & 0xFE00;
            v236 += car_remap[256 * car_texmap[v333 / 4] - 256 + v248];
          }
          if (((unsigned int)cstart_branch_1 & textures_off) != 0
            && (v236 & 0x100) == 0
            && (unsigned __int8)v236 == v290) {
            v236 = v289;
          }
          CarPol = v236;
          if (!v245) {
            if ((v236 & 0x100) == 0 || !v301)
              goto LABEL_267;
          LABEL_266:
            POLYTEX(gfx_size);
            goto LABEL_268;
          }
          subdivide(
            v287,
            (int)&CarPol,
            *(float *)(v279 + 20),
            *(float *)(v279 + 24),
            *(float *)(v279 + 28),
            *(float *)(v280 + 20),
            *(float *)(v280 + 24),
            *(float *)(v280 + 28),
            *(float *)(v281 + 20),
            *(float *)(v281 + 24),
            *(float *)(v281 + 28),
            *(float *)(v282 + 20),
            *(float *)(v282 + 24),
            *(float *)(v282 + 28),
            v332,
            gfx_size);
        } else {
          CarZOrder[v219 / 4] = -1;
          v220 = CarZOrder_variable_1[v219 / 4];
          CarZOrder_variable_2[v219 / 4] = -1.0;
          v221 = 8 * v220;
          v360 = SmokePt_variable_7[8 * v220];
          if (v360 > (double)car_c_variable_20) {
            v222 = &v286[11 * v220];
            if (*((_BYTE *)v222 + 40) == 1) {
              v223 = (double)VIEWDIST * v222[6] / v360;
              _CHP(v222, v221 * 4);
              v361 = (int)v223;
              v224 = SmokePt[8 * v220];
              v225 = SmokePt_variable_8[8 * v220];
              CarPol_variable_8 = SmokePt_variable_1[v221];
              v226 = SmokePt_variable_9[v221];
              CarPol_variable_10 = CarPol_variable_8;
              CarPol_variable_4 = v226;
              CarPol_variable_6 = v226;
              v228 = *(_DWORD *)(v227 + 36);
              v361 = (scr_size * (int)v223) >> 6;
              BYTE1(v228) |= 0x20u;
              CarPol_variable_3 = v225 + v361;
              CarPol = v228;
              CarPol_variable_7 = v224 - v361;
              CarPol_variable_5 = v225 - v361;
              CarPol_variable_2 = 4;
              CarPol_variable_9 = v224 + v361;
              if ((v228 & 0x100) == 0)
                goto LABEL_267;
            } else {
              v229 = (double)VIEWDIST * v222[6] / v360;
              _CHP(v222, v221 * 4);
              v295 = (int)v229;
              v231 = (int)v229;
              if ((int)v229 <= 0 || v231 >= 100)
                goto LABEL_268;
              CarPol = *(_DWORD *)(v230 + 36);
              v295 = (scr_size * v231) >> 6;
              CarPol_variable_2 = 4;
              v232 = SmokePt[8 * v220];
              v233 = SmokePt_variable_1[v221];
              CarPol_variable_3 = v232 + v295;
              CarPol_variable_5 = v232 - v295;
              CarPol_variable_7 = v232 - v295;
              CarPol_variable_4 = v233 - v295;
              CarPol_variable_6 = v233 - v295;
              CarPol_variable_8 = v295 + v233;
              CarPol_variable_10 = v295 + v233;
              CarPol_variable_9 = v232 + v295;
              if ((CarPol_variable_1 & 1) == 0) {
              LABEL_267:
                POLYFLAT(v287, &CarPol);
                goto LABEL_268;
              }
            }
            goto LABEL_266;
          }
        }
      LABEL_268:
        v219 += 12;
      } while ((int)v219 < v335);
    }
  }
  LOWORD(v249) = NamesLeft;
  if (NamesLeft < 5 && NamesLeft >= -2) {
    if (names_on == 1 || names_on == 2 && (v249 = *((_DWORD *)v391 + 8), human_control[v249])) {
      if (replaytype != 2) {
        LOWORD(v249) = (_WORD)v391;
        if ((*((_BYTE *)v391 + 131) & 2) == 0 && !winner_mode) {
          v250 = v303;
          v361 = CarBox_variable_14[24 * v303];
          v364 = *(float *)&v361 * v383 + v378;
          v362 = *(float *)&v361 * v382 + v377;
          v359 = *(float *)&v361 * v381 + v376;
          if (v379 == -1) {
            CarPt_variable_2[0] = v364;
            CarPt_variable_3[0] = v362;
            CarPt_variable_4[0] = v359;
          } else {
            CarPt_variable_2[0] = v298[1] * v362 + *v298 * v364 + v298[2] * v359 - v298[9];
            CarPt_variable_3[0] = v298[3] * v364 + v298[4] * v362 + v298[5] * v359 - v298[10];
            CarPt_variable_4[0] = v362 * v298[7] + v364 * v298[6] + v359 * v298[8] - v298[11];
          }
          v251 = CarPt_variable_2[0] - viewx;
          v252 = CarPt_variable_3[0] - viewy;
          v253 = CarPt_variable_4[0] - viewz;
          *(float *)&v352 = v251 * vk1 + v252 * vk4 + v253 * vk7;
          *(float *)&v348 = v251 * vk2 + v252 * vk5 + v253 * vk8;
          v254 = v251 * vk3 + v252 * vk6 + v253 * vk9;
          v344 = v254;
          HIWORD(v259) = HIWORD(v344);
          v340 = v344;
          v256 = v254 < car_c_variable_20;
          v257 = 0;
          v258 = v254 == car_c_variable_20;
          LOWORD(v259) = v255;
          if (v254 < car_c_variable_20)
            v344 = 80.0;
          v260 = (double)VIEWDIST;
          v261 = 1.0 / v344;
          v262 = v260 * *(float *)&v352 * v261 + (double)xbase;
          _CHP(v259, v303);
          xp = (int)v262;
          v263 = v261 * (v260 * *(float *)&v348) + (double)ybase;
          v264 = scr_size;
          _CHP(scr_size * (int)v262, v250);
          yp = (int)v263;
          CarPt[0] = v265 >> 6;
          CarPt_variable_1 = (v264 * (199 - (int)v263)) >> 6;
          CarPt_variable_5 = v352;
          CarPt_variable_6 = v348;
          CarPt_variable_7[0] = v340;
          v266 = 0;
          if (*((unsigned __int8 *)v391 + 130) < racers - 1 || racers == 1)
            sprintf(
              &buffer,
              "%s (%s)",
              &driver_names[9 * v284],
              (const char *)&language_buffer + 64 * *((unsigned __int8 *)v391 + 130) + 384);
          else
            sprintf(&buffer, "%s (%s)", &driver_names[9 * v284], language_buffer_variable_21);
          v267 = 0;
          if (buffer) {
            do
              v266 += 5;
            while (buffer_variable_1[v267++]);
          }
          v249 = v266 / 2;
          if (mirror)
            v269 = v249 + CarPt[0];
          else
            v269 = CarPt[0] - v249;
          v270 = CarPt_variable_1 - 16;
          if (v269 >= 0) {
            LOWORD(v249) = winw - v266;
            if (v269 < winw - v266 && v270 > 0) {
              LOWORD(v249) = winh - 16;
              if (v270 < winh - 16 && v266 > 0 && !intro) {
                v271 = scr_size;
                scr_size = 64;
                if (mirror)
                  mini_prt_string_rev(rev_vga, &buffer);
                else
                  mini_prt_string(rev_vga, &buffer);
                CarPol_variable_3 = CarPt[0] + 6;
                CarPol_variable_4 = CarPt_variable_1 - 7;
                CarPol_variable_5 = CarPt[0] - 5;
                CarPol_variable_6 = CarPt_variable_1 - 7;
                CarPol_variable_7 = CarPt[0];
                CarPol_variable_8 = CarPt_variable_1 - 1;
                CarPol_variable_9 = CarPt[0] + 6;
                CarPol_variable_10 = CarPt_variable_1 - 7;
                v272 = *((unsigned __int8 *)v391 + 102);
                scr_size = v271;
                CarPol = team_col[v272];
                CarPol_variable_2 = 4;
                LOWORD(v249) = POLYFLAT(v287, &CarPol);
              }
            }
          }
        }
      }
    }
  }
  return v249;
}

//-------------------------------------------------------------------------------------------------

int __fastcall carZcmp(int a1, int a2)
{
  float v3; // [esp+0h] [ebp-8h]
  float v4; // [esp+4h] [ebp-4h]

  v3 = *(float *)(a1 + 8);
  v4 = *(float *)(a2 + 8);
  if (v3 == v4)
    return 0;
  if (v3 >= (double)v4)
    return -1;
  return 1;
}

//-------------------------------------------------------------------------------------------------

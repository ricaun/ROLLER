//-------------------------------------------------------------------------------------------------

int InitTowers()
{
  return 0; /*
  int result; // eax
  int v1; // esi
  int v2; // edx
  int v3; // ebx
  int v4; // edi
  int v5; // ecx
  float *v6; // eax
  float *v7; // ebp
  double v8; // st7
  int v9; // ecx
  float v10; // [esp+4h] [ebp-34h]
  float v11; // [esp+8h] [ebp-30h]
  float v12; // [esp+Ch] [ebp-2Ch]
  float v13; // [esp+10h] [ebp-28h]
  float v14; // [esp+14h] [ebp-24h]
  float v15; // [esp+18h] [ebp-20h]
  int v16; // [esp+1Ch] [ebp-1Ch]

  result = memset(TowerSect, 255, sizeof(TowerSect));
  v1 = 0;
  if (NumTowers > 0) {
    v2 = 0;
    v3 = 0;
    do {
      v4 = TowerBase[v2];
      v5 = v4 + 1;
      v13 = (float)TowerBase_variable_1[v2];
      if (v4 + 1 >= TRAK_LEN)
        v5 -= TRAK_LEN;
      v6 = (float *)((char *)&localdata + 128 * v4);
      v11 = -v6[10];
      v7 = (float *)((char *)&localdata + 128 * v5);
      *(float *)&v16 = (double)(32 * TowerBase_variable_2[v2]) - v6[11];
      v14 = v6[9] - v7[9];
      v15 = v6[10] - v7[10];
      v12 = sqrt(v14 * v14 + v15 * v15);
      if ((LODWORD(v14) & 0x7FFFFFFF) != 0)
        v14 = v14 / v12;
      if (fabs(v6[10] - v7[10]))
        v15 = v15 / v12;
      v10 = -v6[9];
      TowerX[v3] = v10 - v13 * v15 * tower_c_variable_1;
      v8 = v13 * v14 * tower_c_variable_1 + v11;
      result = v16;
      v9 = NumTowers;
      v2 += 5;
      ++v3;
      TowerSect[v4] = v1++;
      TowerY_variable_1[v3] = v16;
      TowerX_variable_1[v3] = v8;
    } while (v1 < v9);
  }
  TowerPol_variable_1 = 4;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void DrawTower(int a1, int a2)
{/*
  double v2; // st7
  double v3; // st6
  double v4; // st5
  double v5; // st7
  __int16 v6; // fps
  _BOOL1 v7; // c0
  char v8; // c2
  _BOOL1 v9; // c3
  int v10; // eax
  double v11; // st7
  double v12; // st6
  double v13; // st5
  double v14; // st7
  int v15; // ebp
  int v16; // ecx
  int v17; // eax
  int v18; // ecx
  int v19; // ebx
  float v20; // [esp+20h] [ebp-20h]
  float v21; // [esp+24h] [ebp-1Ch]
  float v22; // [esp+28h] [ebp-18h]
  float v23; // [esp+2Ch] [ebp-14h]

  if (a1 != NearTow && TowerBase_variable_3[5 * a1] > -1) {
    v2 = TowerX[a1] - viewx;
    v3 = TowerY[a1] - viewy;
    v4 = TowerZ[a1] - viewz;
    v21 = v2 * vk1 + v3 * vk4 + v4 * vk7;
    v20 = v2 * vk2 + v3 * vk5 + v4 * vk8;
    v5 = v2 * vk3 + v3 * vk6 + v4 * vk9;
    v23 = v5;
    HIWORD(v10) = HIWORD(v23);
    v22 = v23;
    v7 = v5 < tower_c_variable_2;
    v8 = 0;
    v9 = v5 == tower_c_variable_2;
    LOWORD(v10) = v6;
    if (v5 < tower_c_variable_2)
      v23 = 80.0;
    v11 = (double)VIEWDIST;
    v12 = 1.0 / v23;
    v13 = v11 * v21 * v12 + (double)xbase;
    _CHP(v10, a2);
    xp = (int)v13;
    v14 = v12 * (v11 * v20) + (double)ybase;
    v15 = scr_size;
    v16 = scr_size * (int)v13;
    _CHP(v17, a2);
    yp = (int)v14;
    v18 = v16 >> 6;
    v19 = (v15 * (199 - (int)v14)) >> 6;
    if (v22 >= (double)tower_c_variable_3 && xp >= -50 && xp < 370 && yp >= -50 && yp < 250
      || v22 >(double)tower_c_variable_4
      && v22 < (double)tower_c_variable_3
      && (v21 > (double)tower_c_variable_4 && v21 < (double)tower_c_variable_5 || xp > -200 && xp < 520)) {
      TowerPol_variable_2 = v18 + 3;
      TowerPol_variable_4 = v18 - 3;
      TowerPol_variable_6 = v18 - 3;
      TowerPol_variable_3 = v19 - 3;
      TowerPol_variable_5 = v19 - 3;
      TowerPol_variable_7 = v19 + 3;
      TowerPol_variable_9 = v19 + 3;
      TowerPol_variable_8 = v18 + 3;
      TowerPol = 8423;
      TowerPol_variable_1 = 4;
      POLYFLAT(a2, &TowerPol);
    }
  }*/
}

//-------------------------------------------------------------------------------------------------
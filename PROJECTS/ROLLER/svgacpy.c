#ifdef ENABLE_PSEUDO
//-------------------------------------------------------------------------------------------------

int __fastcall vesastart(int a1, int a2)
{
  RMI_variable_3 = a1;
  RMI_variable_2 = a2;
  RMI_variable_5 = vmode_inf >> 4;
  RMI_variable_1 = 0;
  RMI_variable_4 = 20231;
  realmode(16, a2, 20231, 0);
  if ((unsigned __int8)RMI_variable_4 == 79)
    return BYTE1(RMI_variable_4) != 0;
  puts(aVesaFunctionNo);
  return 2;
}

//-------------------------------------------------------------------------------------------------

int __fastcall tryvesa(int a1, int a2, int a3, int a4)
{
  RMI_variable_3 = a1;
  RMI_variable_5 = vmode_inf >> 4;
  RMI_variable_4 = 20225;
  RMI = 0;
  realmode(16, 0, 20225, a4);
  if ((unsigned __int8)RMI_variable_4 == 79)
    return BYTE1(RMI_variable_4) != 0;
  puts(aVesaFunctionNo);
  return 2;
}

//-------------------------------------------------------------------------------------------------

int __fastcall VESASource(int a1, int a2, int a3)
{
  int v3; // ecx
  int v4; // esi
  _DWORD v6[11]; // [esp+0h] [ebp-2Ch] BYREF

  v3 = Vbytesperline * a3 + ((int)*(unsigned __int8 *)(vmode_inf + 25) >> 3) * a2 + a1;
  v4 = v3 / winrange;
  if (v3 / winrange != vmode_inf_variable_1) {
    v6[3] = v3 / winrange;
    v6[1] = 1;
    v6[0] = 20229;
    int386(16, (int)v6, (int)v6);
    vmode_inf_variable_1 = v4;
  }
  return v3 % winrange + VesaSBase;
}

//-------------------------------------------------------------------------------------------------

int __fastcall VESADest(int a1, int a2, int a3)
{
  int v3; // ecx
  int v4; // esi
  _DWORD v6[11]; // [esp+0h] [ebp-2Ch] BYREF

  v3 = Vbytesperline * a3 + ((int)*(unsigned __int8 *)(vmode_inf + 25) >> 3) * a2 + a1;
  v4 = v3 / winrange;
  if (v3 / winrange != vmode_inf_variable_2) {
    v6[3] = v3 / winrange;
    v6[1] = 0;
    v6[0] = 20229;
    int386(16, (int)v6, (int)v6);
    vmode_inf_variable_2 = v4;
  }
  return v3 % winrange + VesaDBase;
}

//-------------------------------------------------------------------------------------------------

int __fastcall VESAmode(_DWORD *a1, int a2, int a3, _BYTE *a4)
{
  int v6; // ebx
  unsigned int v7; // ecx
  __int16 *i; // edx
  int v9; // eax
  unsigned __int16 v10; // ax
  unsigned __int16 v11; // [esp+0h] [ebp-3Ch] BYREF
  __int16 v12; // [esp+4h] [ebp-38h]
  int v13; // [esp+18h] [ebp-24h]
  _BYTE v14[24]; // [esp+1Ch] [ebp-20h] BYREF
  _BYTE *v15; // [esp+34h] [ebp-8h]

  v15 = a4;
  memset(v14, 0, 12);
  if (!vesa_inf) {
    a4 = v14;
    v11 = 256;
    v12 = 16;
    int386x(49, (int)&v11, (int)&v11, (int)v14);
    vesa_inf = 16 * v11;
    if (v13) {
      puts(aInternalErrorV);
      return -1;
    }
    RMI = 0;
    RMI_variable_5 = (16 * v11) >> 4;
    RMI_variable_4 = 20224;
    realmode(16, (int)&v11, 0, (int)v14);
    if ((unsigned __int8)RMI_variable_4 != 79)
      goto LABEL_5;
    if (BYTE1(RMI_variable_4)) {
    LABEL_7:
      puts(aVesaFunctionCa);
      return -1;
    }
    if (strncmp(vesa_inf, aVesa, 4))
      puts(aInternalErrorV_0);
  }
  if (vmode_inf
    || (v11 = 256, a4 = v14, v12 = 16, int386x(49, (int)&v11, (int)&v11, (int)v14), vmode_inf = 16 * v11, !v13)) {
    v6 = -1;
    if (*a1 != -1) {
      do {
        if (v6 != -1)
          break;
        v7 = (unsigned int)&unk_FFFF0 & (*(int *)(vesa_inf + 14) >> 12);
        for (i = (__int16 *)(v7 + (unsigned __int16)*(_DWORD *)(vesa_inf + 14)); ; ++i) {
          v9 = *i;
          if (v9 == -1)
            break;
          if (v9 == *a1 && !tryvesa(v9, (int)i, -1, v7)) {
            v6 = *i;
            break;
          }
        }
        a4 = (_BYTE *)a1[1];
        ++a1;
      } while (a4 != (_BYTE *)-1);
    }
    if (v6 <= -1) {
      puts(&aConoSupportedV[2]);
    } else {
      winrange = *(__int16 *)(vmode_inf + 4) << 10;
      Vbytesperline = *(__int16 *)(vmode_inf + 16);
      v10 = *(_WORD *)(vmode_inf + 10);
      VesaSBase = 16 * *(unsigned __int16 *)(vmode_inf + 8);
      RMI_variable_1 = v6;
      VesaDBase = 16 * v10;
      RMI_variable_4 = 20226;
      realmode(16, VesaSBase, v6, (int)a4);
      if ((unsigned __int8)RMI_variable_4 != 79) {
      LABEL_5:
        puts(aVesaFunctionNo);
        return -1;
      }
      if (BYTE1(RMI_variable_4))
        goto LABEL_7;
    }
    return v6;
  } else {
    puts(aInternalErrorV_1);
    return -1;
  }
}

//-------------------------------------------------------------------------------------------------

int __fastcall svgacopy(char *a1, __int16 a2, __int16 a3, int a4, int a5)
{
  int v6; // edx
  int v7; // eax
  int i; // edx
  int v9; // edx
  int v10; // eax
  __int16 v11; // di
  char *v13; // [esp-4h] [ebp-40h]
  int v14; // [esp+0h] [ebp-3Ch] BYREF
  int v15; // [esp+4h] [ebp-38h]
  int v16; // [esp+Ch] [ebp-30h]
  int v17; // [esp+1Ch] [ebp-20h]
  char *v18; // [esp+20h] [ebp-1Ch]
  int v19; // [esp+24h] [ebp-18h]
  int v20; // [esp+28h] [ebp-14h]
  unsigned __int8 v21; // [esp+2Ch] [ebp-10h]

  v20 = a4;
  v21 = (a3 * Vbytesperline + a2) / winrange;
  v6 = (a3 * Vbytesperline + a2) % winrange;
  v15 = 0;
  v18 = (char *)&off_A0000 + v6;
  v17 = v6;
  v16 = v21;
  v14 = 20229;
  int386(16, (int)&v14, (int)&v14);
  do {
    v7 = (winrange - v17) / Vbytesperline;
    if (v7 >= (__int16)a5)
      LOWORD(v7) = a5;
    for (i = 0; (__int16)i < (__int16)v7; --a5) {
      v13 = v18;
      qmemcpy(v18, a1, (__int16)v20);
      ++i;
      v18 = &v13[Vbytesperline];
      a1 += winw;
    }
    if ((_WORD)a5) {
      v9 = Vbytesperline * ((__int16)v7 + 1) + v17;
      v17 = v9 % winrange;
      v10 = (__int16)v20;
      if (Vbytesperline - v9 % winrange < (__int16)v20)
        v10 = Vbytesperline - v9 % winrange;
      v19 = v10;
      qmemcpy(v18, a1, (__int16)v10);
      ++v21;
      v14 = 20229;
      v15 = 0;
      v16 = v21;
      v11 = v20;
      int386(16, (int)&v14, (int)&v14);
      if ((_WORD)v19 != v11)
        qmemcpy(&off_A0000, &a1[(__int16)v19], v11 - (__int16)v19);
      v18 = (char *)&off_A0000 + v17;
      a1 += winw;
      --a5;
    }
  } while ((_WORD)a5);
  v14 = 20229;
  v15 = 0;
  v16 = 0;
  return int386(16, (int)&v14, (int)&v14);
}

//-------------------------------------------------------------------------------------------------
#endif
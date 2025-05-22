#include "svgacpy.h"
//-------------------------------------------------------------------------------------------------

int vesastart(int a1, int a2)
{
  return 0; /*
  RMI_variable_3 = a1;
  RMI_variable_2 = a2;
  RMI_variable_5 = vmode_inf >> 4;
  RMI_variable_1 = 0;
  RMI_variable_4 = 20231;
  realmode(16, a2, 20231, 0);
  if ((unsigned __int8)RMI_variable_4 == 79)
    return BYTE1(RMI_variable_4) != 0;
  puts(aVesaFunctionNo);
  return 2;*/
}

//-------------------------------------------------------------------------------------------------

int tryvesa(int a1, int a2, int a3, int a4)
{
  return 0; /*
  RMI_variable_3 = a1;
  RMI_variable_5 = vmode_inf >> 4;
  RMI_variable_4 = 20225;
  RMI = 0;
  realmode(16, 0, 20225, a4);
  if ((unsigned __int8)RMI_variable_4 == 79)
    return BYTE1(RMI_variable_4) != 0;
  puts(aVesaFunctionNo);
  return 2;*/
}

//-------------------------------------------------------------------------------------------------

int VESASource(int a1, int a2, int a3)
{
  return 0; /*
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
  return v3 % winrange + VesaSBase;*/
}

//-------------------------------------------------------------------------------------------------

int VESADest(int a1, int a2, int a3)
{
  return 0; /*
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
  return v3 % winrange + VesaDBase;*/
}

//-------------------------------------------------------------------------------------------------

int VESAmode(int *vesaModes, int iSvgaPossible)
{
  return 0x101;
  /*
  int v2; // ecx
  int v5; // ebx
  unsigned int v6; // ecx
  __int16 *i; // edx
  int v8; // eax
  int v9; // ecx
  unsigned __int16 v10; // ax
  union REGS regs; // [esp+0h] [ebp-3Ch] BYREF
  struct SREGS v12; // [esp+1Ch] [ebp-20h] BYREF
  int iSvgaPossible2; // [esp+30h] [ebp-Ch]
  int v14; // [esp+34h] [ebp-8h]

  v14 = v2;
  iSvgaPossible2 = iSvgaPossible;
  memset(&v12, 0, sizeof(v12));
  if (!vesa_inf) {
    regs.w.ax = 256;
    regs.w.bx = 16;
    int386x(49, &regs, &regs, &v12);
    vesa_inf = 16 * regs.w.ax;
    if (regs.x.cflag) {
      puts(aInternalErrorV);
      return -1;
    }
    RMI.edi = 0;
    RMI.es = (16 * regs.w.ax) >> 4;
    RMI.eax = 20224;
    realmode(0x10u);
    if (LOBYTE(RMI.eax) != 79)
      goto LABEL_5;
    if (BYTE1(RMI.eax)) {
    LABEL_7:
      puts(aVesaFunctionCa);
      return -1;
    }
    if (strncmp(vesa_inf, aVesa, 4))
      puts(aInternalErrorV_0);
  }
  if (vmode_inf
    || (regs.w.ax = 256, regs.w.bx = 16, int386x(49, &regs, &regs, &v12), vmode_inf = 16 * regs.w.ax, !regs.x.cflag)) {
    v5 = -1;
    if (*vesaModes != -1) {
      do {
        if (v5 != -1)
          break;
        v6 = (unsigned int)&unk_FFFF0 & (*(int *)(vesa_inf + 14) >> 12);
        for (i = (__int16 *)(v6 + (unsigned __int16)*(_DWORD *)(vesa_inf + 14)); ; ++i) {
          v8 = *i;
          if (v8 == -1)
            break;
          if (v8 == *vesaModes && !tryvesa(v8, (int)i, -1, v6)) {
            v5 = *i;
            break;
          }
        }
        v9 = vesaModes[1];
        ++vesaModes;
      } while (v9 != -1);
    }
    if (v5 <= -1) {
      puts(&aConoSupportedV[2]);
    } else {
      winrange = *(__int16 *)(vmode_inf + 4) << 10;
      Vbytesperline = *(__int16 *)(vmode_inf + 16);
      v10 = *(_WORD *)(vmode_inf + 10);
      VesaSBase = 16 * *(unsigned __int16 *)(vmode_inf + 8);
      RMI.ebx = v5;
      VesaDBase = 16 * v10;
      RMI.eax = 20226;
      realmode(0x10u);
      if (LOBYTE(RMI.eax) != 79) {
      LABEL_5:
        puts(aVesaFunctionNo);
        return -1;
      }
      if (BYTE1(RMI.eax))
        goto LABEL_7;
    }
    return v5;
  } else {
    puts(aInternalErrorV_1);
    return -1;
  }*/
}

//-------------------------------------------------------------------------------------------------

int svgacopy(uint8 *pBuf, __int16 a2, __int16 a3, int a4, int a5)
{
  return 0; /*
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
  return int386(16, (int)&v14, (int)&v14);*/
}

//-------------------------------------------------------------------------------------------------
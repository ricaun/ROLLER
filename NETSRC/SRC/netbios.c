
//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETBIOSInitSystem(int a1)
{
  int v1; // eax
  int v2; // eax
  const time_t *v4; // [esp+0h] [ebp-54h]
  int v5; // [esp+0h] [ebp-54h]
  int v6; // [esp+4h] [ebp-50h]
  int v7; // [esp+8h] [ebp-4Ch]
  _BYTE v8[20]; // [esp+24h] [ebp-30h] BYREF
  int v10; // [esp+3Ch] [ebp-18h]
  unsigned int i; // [esp+40h] [ebp-14h]
  int v12; // [esp+4Ch] [ebp-8h]
  int v13; // [esp+50h] [ebp-4h]

  wActiveNodes_mod_190 = 0;
  if (!hmiNETNOWAllocateRealMem(0x9000u, &pSendPacketPtr_mod_190, &wSendSegment_mod_190))
    return 1;
  if (!hmiNETNOWAllocateRealMem(0x9000u, &pListenPacketPtr_mod_190, &wListenSegment_mod_190))
    return 1;
  wSendSequence_mod_190 = 0;
  wMaxNodes_mod_190 = a1;
  pSendPacket_mod_190 = pSendPacketPtr_mod_190;
  pListenPacket_mod_190 = pListenPacketPtr_mod_190;
  if (!hmiNETBIOSInstalled())
    return 2;
  v10 = time(0);
  gmtime(v4);
  i = 0;
  itoa(v7, v8);
  v1 = strlen(v8);
  i += v1;
  itoa(v6, &v8[i]);
  v2 = strlen(&v8[i]);
  i += v2;
  itoa(v5, &v8[i]);
  if (!hmiNETBIOSAddName(v8))
    return 3;
  hmiNETBIOSGetAdapterStatus();
  if (!hmiNETBIOSDeleteName(v8))
    return 3;
  memcpy(&sNetNOWAddr_mod_190, &sNetworkAddr_mod_190, 16);
  hmiNETBIOSAddNode((int)&sNetNOWAddr_mod_190);
  v13 = 0;
  v12 = 0;
  for (i = 0; i < 0x40; ++i) {
    *((_WORD *)&pSendElements_mod_190 + 39 * i) = 0;
    pSendElements_mod_190_variable_2[39 * i] = v13;
    *(int *)((char *)&pSendElements_mod_190_variable_3 + 78 * i) = 0;
    v13 += 576;
  }
  for (i = 0; i < 0x40; ++i) {
    *((_WORD *)&pListenElements_mod_190 + 39 * i) = 0;
    pListenElements_mod_190_variable_2[39 * i] = v12;
    *(int *)((char *)&pListenElements_mod_190_variable_4 + 78 * i) = 0;
    if (i >= 0x20)
      pListenElements_mod_190_variable_3[78 * i] = -93;
    else
      pListenElements_mod_190_variable_3[78 * i] = -95;
    v12 += 576;
  }
  memset(&sNodes_mod_190_variable_1, 255, 6);
  return 0;
}

//-------------------------------------------------------------------------------------------------

int hmiNETBIOSUnInitSystem()
{
  hmiNETBIOSCancelAll();
  pListenPacket_mod_190 = pListenPacketPtr_mod_190;
  wNCBOffset = 0;
  if (hmiNETBIOSDeleteName(&sNetworkAddr_mod_190))
    return 1;
  else
    return 3;
}

//-------------------------------------------------------------------------------------------------

int hmiNETBIOSGetActiveNodes()
{
  return wActiveNodes_mod_190;
}

//-------------------------------------------------------------------------------------------------

int hmiNETBIOSGetConsoleNode()
{
  return wConsoleNode_mod_190;
}

//-------------------------------------------------------------------------------------------------

unsigned int hmiNETBIOSSortNodes()
{
  unsigned int result; // eax
  _BYTE v1[16]; // [esp+0h] [ebp-18h] BYREF
  int v2; // [esp+10h] [ebp-8h]
  unsigned int i; // [esp+14h] [ebp-4h]

  do {
    v2 = 0;
    for (i = 0; wActiveNodes_mod_190 - 1 > i; ++i) {
      if (memcmp((char *)&sNodes_mod_190 + 16 * i, (char *)&sNodes_mod_190 + 16 * i + 16, 16) < 0) {
        v2 = 1;
        memcpy(v1, (char *)&sNodes_mod_190 + 16 * i, sizeof(v1));
        memcpy((char *)&sNodes_mod_190 + 16 * i, (char *)&sNodes_mod_190 + 16 * i + 16, 16);
        memcpy((char *)&sNodes_mod_190 + 16 * i + 16, v1, 16);
      }
    }
  } while (v2);
  for (i = 0; ; ++i) {
    result = i;
    if (i >= wActiveNodes_mod_190)
      break;
    if (!memcmp((char *)&sNodes_mod_190 + 16 * i, &sNetworkAddr_mod_190, 16))
      wConsoleNode_mod_190 = i;
  }
  return result;
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETBIOSGetNetworkAddr(int a1)
{
  memcpy(a1, &sNetworkAddr_mod_190, 16);
  return 1;
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETBIOSAddNode(int a1)
{
  unsigned int i; // [esp+4h] [ebp-4h]

  if (wActiveNodes_mod_190) {
    if (wActiveNodes_mod_190 == wMaxNodes_mod_190) {
      return 2;
    } else {
      for (i = 0; ; ++i) {
        if (i >= wActiveNodes_mod_190) {
          memcpy((char *)&sNodes_mod_190 + 16 * wActiveNodes_mod_190, a1, 16);
          ++wActiveNodes_mod_190;
          return 0;
        }
        if (!memcmp((char *)&sNodes_mod_190 + 16 * i, a1, 16))
          break;
      }
      return 1;
    }
  } else {
    memcpy(&sNodes_mod_190, a1, 16);
    ++wActiveNodes_mod_190;
    return 0;
  }
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETBIOSAddNode(int a1)
{
  unsigned int i; // [esp+4h] [ebp-4h]

  if (wActiveNodes_mod_190) {
    if (wActiveNodes_mod_190 == wMaxNodes_mod_190) {
      return 2;
    } else {
      for (i = 0; ; ++i) {
        if (i >= wActiveNodes_mod_190) {
          memcpy((char *)&sNodes_mod_190 + 16 * wActiveNodes_mod_190, a1, 16);
          ++wActiveNodes_mod_190;
          return 0;
        }
        if (!memcmp((char *)&sNodes_mod_190 + 16 * i, a1, 16))
          break;
      }
      return 1;
    }
  } else {
    memcpy(&sNodes_mod_190, a1, 16);
    ++wActiveNodes_mod_190;
    return 0;
  }
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETBIOSDeleteNode(unsigned int a1)
{
  if (a1 >= wActiveNodes_mod_190)
    return 1;
  memcpy((char *)&sNodes_mod_190 + 16 * a1, (char *)&sNodes_mod_190 + 16 * a1 + 16, 16 * (wActiveNodes_mod_190 - a1));
  --wActiveNodes_mod_190;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETBIOSNetAddrToNode(int a1)
{
  unsigned int i; // [esp+4h] [ebp-4h]

  if (!wActiveNodes_mod_190)
    return -1;
  for (i = 0; ; ++i) {
    if (i >= wActiveNodes_mod_190)
      return -1;
    if (!memcmp((char *)&sNodes_mod_190 + 16 * i, a1, 16))
      break;
  }
  return i;
}

//-------------------------------------------------------------------------------------------------

bool hmiNETBIOSInstalled()
{
  int v0; // eax
  _BYTE v2[64]; // [esp+0h] [ebp-70h] BYREF
  _WORD v3[10]; // [esp+40h] [ebp-30h] BYREF
  void *v4; // [esp+54h] [ebp-1Ch]
  _WORD v5[6]; // [esp+5Ch] [ebp-14h] BYREF
  int v6; // [esp+68h] [ebp-8h]

  memset(&sRMIRegs_mod_190, 0, 52);
  memset(v5, 0, sizeof(v5));
  memset(v2, 0, sizeof(v2));
  v2[0] = 127;
  v2[49] = -1;
  memcpy(pListenPacket_mod_190, v2, 64);
  HIWORD(v0) = HIWORD(pListenPacket_mod_190);
  v6 = pListenPacket_mod_190;
  LOWORD(v0) = wListenSegment_mod_190;
  sRMIRegs_mod_190_variable_3 = wListenSegment_mod_190;
  sRMIRegs_mod_190_variable_1 = 0;
  sRMIRegs_mod_190_variable_2 = 256;
  v3[0] = 768;
  v3[2] = 92;
  v3[4] = 0;
  v5[0] = hmiGetDS(v0);
  v4 = &sRMIRegs_mod_190;
  hmiINT386x(49, v3, v3, v5);
  return *(_BYTE *)(v6 + 49) == 3;
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETBIOSGetData(int a1, int a2, int a3, int a4)
{
  int v6; // [esp+4h] [ebp-10h]
  int v7; // [esp+4h] [ebp-10h]
  int v8; // [esp+8h] [ebp-Ch]
  unsigned int v9; // [esp+Ch] [ebp-8h]
  unsigned int i; // [esp+10h] [ebp-4h]

  v9 = -1;
  v8 = -1;
  for (i = 0; i < 0x40; ++i) {
    v6 = *(int *)((char *)&pListenElements_mod_190_variable_4 + 78 * i);
    if (*(_BYTE *)(v6 + 49) != 0xFF && *(_DWORD *)(v6 + 64) < v9) {
      v9 = *(_DWORD *)(v6 + 64);
      v8 = i;
    }
  }
  if (v8 == -1)
    return 0;
  v7 = *(int *)((char *)&pListenElements_mod_190_variable_4 + 78 * v8);
  memcpy(a1, v7 + 64, a2);
  if (a4)
    memcpy(a3, a2 + v7 + 64, a4);
  *((_WORD *)&pListenElements_mod_190 + 39 * v8) = 0;
  hmiNETBIOSPostListen();
  return 1;
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETBIOSGetHeader(int a1, int a2, _DWORD *a3)
{
  int v5; // [esp+4h] [ebp-10h]
  int v6; // [esp+4h] [ebp-10h]
  int v7; // [esp+8h] [ebp-Ch]
  unsigned int v8; // [esp+Ch] [ebp-8h]
  unsigned int i; // [esp+10h] [ebp-4h]

  v8 = -1;
  v7 = -1;
  for (i = 0; i < 0x40; ++i) {
    v5 = *(int *)((char *)&pListenElements_mod_190_variable_4 + 78 * i);
    if (*(_BYTE *)(v5 + 49) != 0xFF && *(_DWORD *)(v5 + 64) < v8) {
      v8 = *(_DWORD *)(v5 + 64);
      v7 = i;
    }
  }
  if (v7 == -1)
    return 0;
  v6 = *(int *)((char *)&pListenElements_mod_190_variable_4 + 78 * v7);
  memcpy(a1, v6 + 64, a2);
  *a3 = v6 + 64 + a2;
  *((_WORD *)&pListenElements_mod_190 + 39 * v7) = 0;
  return 1;
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETBIOSSendData(int *a1, int a2, int a3, __int16 a4, unsigned int a5)
{
  int v5; // edx
  char *v8; // [esp+8h] [ebp-8h]
  unsigned int i; // [esp+Ch] [ebp-4h]

  if (a5 >= wActiveNodes_mod_190 && a5 != 21)
    return 0;
  for (i = 0; i < 0x40 && *((char *)&pSendElements_mod_190_variable_1 + 78 * i) < 0; ++i)
    ;
  if (i != 64)
    goto LABEL_17;
  for (i = 0; i < 0x40 && *(_BYTE *)(*(int *)((char *)&pSendElements_mod_190_variable_3 + 78 * i) + 49) == 0xFF; ++i)
    ;
  if (i == 64)
    return 0;
LABEL_17:
  v8 = (char *)&pSendElements_mod_190 + 78 * i;
  *(_WORD *)v8 = -28672;
  pSendPacket_mod_190 = *((unsigned __int16 *)v8 + 1) + pSendPacketPtr_mod_190;
  wNCBOffset = *((_WORD *)v8 + 1);
  memset(v8 + 4, 0, 64);
  if (a5 == 21)
    v8[4] = -94;
  else
    v8[4] = -96;
  v8[7] = sNCBAddName_variable_1;
  *((_WORD *)v8 + 6) = a4;
  *((_DWORD *)v8 + 2) = a3;
  v8[53] = -1;
  if (a5 != 21)
    memcpy(v8 + 14, (char *)&sNodes_mod_190 + 16 * a5, 16);
  v5 = wSendSequence_mod_190++;
  *a1 = v5;
  hmiNETBIOSSendPacket(v8 + 4, v8 + 68, a1, a2);
  return 1;
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETBIOSSendDataDirect(int *a1, int a2, int a3, __int16 a4, int a5)
{
  int v5; // edx
  char *v8; // [esp+8h] [ebp-8h]
  unsigned int i; // [esp+Ch] [ebp-4h]

  for (i = 0; i < 0x40 && *((char *)&pSendElements_mod_190_variable_1 + 78 * i) < 0; ++i)
    ;
  if (i != 64)
    goto LABEL_14;
  for (i = 0; i < 0x40 && *(_BYTE *)(*(int *)((char *)&pSendElements_mod_190_variable_3 + 78 * i) + 49) == 0xFF; ++i)
    ;
  if (i == 64)
    return 0;
LABEL_14:
  v8 = (char *)&pSendElements_mod_190 + 78 * i;
  *(_WORD *)v8 = -28672;
  pSendPacket_mod_190 = *((unsigned __int16 *)v8 + 1) + pSendPacketPtr_mod_190;
  wNCBOffset = *((_WORD *)v8 + 1);
  memset(v8 + 4, 0, 64);
  v8[4] = -96;
  v8[7] = sNCBAddName_variable_1;
  *((_WORD *)v8 + 6) = a4;
  *((_DWORD *)v8 + 2) = a3;
  v8[53] = -1;
  memcpy(v8 + 14, a5, 16);
  v5 = wSendSequence_mod_190++;
  *a1 = v5;
  hmiNETBIOSSendPacket(v8 + 4, v8 + 68, a1, a2);
  return 1;
}

//-------------------------------------------------------------------------------------------------

int hmiNETBIOSPostListen()
{
  char *v2; // [esp+4h] [ebp-Ch]
  unsigned int i; // [esp+8h] [ebp-8h]
  char v4; // [esp+Ch] [ebp-4h]

  for (i = 0; i < 0x40 && *((char *)&pListenElements_mod_190_variable_1 + 78 * i) < 0; ++i)
    ;
  if (i == 64)
    return 0;
  v2 = (char *)&pListenElements_mod_190 + 78 * i;
  *(_WORD *)v2 = -24576;
  pListenPacket_mod_190 = *((unsigned __int16 *)v2 + 1) + pListenPacketPtr_mod_190;
  wNCBOffset = *((_WORD *)v2 + 1);
  v4 = v2[4];
  memset(v2 + 4, 0, 64);
  v2[4] = v4;
  v2[7] = -1;
  *((_WORD *)v2 + 6) = 512;
  *((_DWORD *)v2 + 2) = 0;
  v2[53] = -1;
  hmiNETBIOSListenForPacket(v2 + 4, v2 + 68);
  return 1;
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETBIOSSendPacket(int a1, _DWORD *a2, int a3, int a4)
{
  _WORD v5[10]; // [esp+0h] [ebp-30h] BYREF
  void *v6; // [esp+14h] [ebp-1Ch]
  _WORD v7[6]; // [esp+1Ch] [ebp-14h] BYREF
  int v8; // [esp+28h] [ebp-8h]
  _WORD *v9; // [esp+2Ch] [ebp-4h]

  v9 = (_WORD *)pSendPacket_mod_190;
  v8 = pSendPacket_mod_190 + 64;
  *a2 = pSendPacket_mod_190;
  memcpy(v9, a1, 64);
  if (a3) {
    memcpy(v8, a3, a4);
    if (*(_WORD *)(a1 + 8))
      memcpy(a4 + v8, *(_DWORD *)(a1 + 4), *(unsigned __int16 *)(a1 + 8));
    v9[4] += a4;
  } else if (*(_WORD *)(a1 + 8)) {
    memcpy(v8, *(_DWORD *)(a1 + 4), *(unsigned __int16 *)(a1 + 8));
  }
  v9[2] = wNCBOffset + 64;
  v9[3] = wSendSegment_mod_190;
  memset(&sRMIRegs_mod_190, 0, 52);
  memset(v7, 0, sizeof(v7));
  sRMIRegs_mod_190_variable_3 = wSendSegment_mod_190;
  sRMIRegs_mod_190_variable_1 = (unsigned __int16)wNCBOffset;
  sRMIRegs_mod_190_variable_2 = 256;
  v5[0] = 768;
  v5[2] = 92;
  v5[4] = 0;
  v7[0] = hmiGetDS((unsigned __int16)wNCBOffset);
  v6 = &sRMIRegs_mod_190;
  return hmiINT386x(49, v5, v5, v7);
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETBIOSListenForPacket(int a1, _DWORD *a2)
{
  _WORD v3[10]; // [esp+0h] [ebp-30h] BYREF
  void *v4; // [esp+14h] [ebp-1Ch]
  _WORD v5[6]; // [esp+1Ch] [ebp-14h] BYREF
  int v6; // [esp+28h] [ebp-8h]
  int v7; // [esp+2Ch] [ebp-4h]

  v7 = pListenPacket_mod_190;
  v6 = pListenPacket_mod_190 + 64;
  *a2 = pListenPacket_mod_190;
  memcpy(v7, a1, 64);
  *(_WORD *)(v7 + 4) = wNCBOffset + 64;
  *(_WORD *)(v7 + 6) = wListenSegment_mod_190;
  memset(&sRMIRegs_mod_190, 0, 52);
  memset(v5, 0, sizeof(v5));
  sRMIRegs_mod_190_variable_3 = wListenSegment_mod_190;
  sRMIRegs_mod_190_variable_1 = (unsigned __int16)wNCBOffset;
  sRMIRegs_mod_190_variable_2 = 256;
  v3[0] = 768;
  v3[2] = 92;
  v3[4] = 0;
  v5[0] = hmiGetDS((unsigned __int16)wNCBOffset);
  v4 = &sRMIRegs_mod_190;
  return hmiINT386x(49, v3, v3, v5);
}

//-------------------------------------------------------------------------------------------------

bool __cdecl hmiNETBIOSAddName(int a1)
{
  int v1; // eax
  _BYTE v3[26]; // [esp+0h] [ebp-90h] BYREF
  _BYTE v4[38]; // [esp+1Ah] [ebp-76h] BYREF
  _BYTE v5[32]; // [esp+40h] [ebp-50h] BYREF
  _WORD v6[10]; // [esp+60h] [ebp-30h] BYREF
  void *v7; // [esp+74h] [ebp-1Ch]
  _WORD v8[6]; // [esp+7Ch] [ebp-14h] BYREF
  int v9; // [esp+8Ch] [ebp-4h]

  strcpy(v5, a1);
  while ((unsigned int)strlen(v5) < 0xF)
    strcat(v5, netbios_c_variable_1);
  memset(&sRMIRegs_mod_190, 0, 52);
  memset(v8, 0, sizeof(v8));
  memset(v3, 0, 64);
  v3[0] = -80;
  v4[23] = -1;
  strcpy(v4, v5);
  memcpy(pListenPacket_mod_190, v3, 64);
  HIWORD(v1) = HIWORD(pListenPacket_mod_190);
  v9 = pListenPacket_mod_190;
  LOWORD(v1) = wListenSegment_mod_190;
  sRMIRegs_mod_190_variable_3 = wListenSegment_mod_190;
  sRMIRegs_mod_190_variable_1 = 0;
  sRMIRegs_mod_190_variable_2 = 256;
  v6[0] = 768;
  v6[2] = 92;
  v6[4] = 0;
  v8[0] = hmiGetDS(v1);
  v7 = &sRMIRegs_mod_190;
  hmiINT386x(49, v6, v6, v8);
  while (*(unsigned __int8 *)(v9 + 49) == 255)
    ;
  memcpy(&sNCBAddName, pListenPacket_mod_190, 64);
  return sNCBAddName_variable_3 == 0;
}

//-------------------------------------------------------------------------------------------------

bool __cdecl hmiNETBIOSDeleteName(int a1)
{
  int v1; // eax
  _BYTE v3[26]; // [esp+0h] [ebp-90h] BYREF
  _BYTE v4[38]; // [esp+1Ah] [ebp-76h] BYREF
  _BYTE v5[32]; // [esp+40h] [ebp-50h] BYREF
  _WORD v6[10]; // [esp+60h] [ebp-30h] BYREF
  void *v7; // [esp+74h] [ebp-1Ch]
  _WORD v8[6]; // [esp+7Ch] [ebp-14h] BYREF
  int v9; // [esp+8Ch] [ebp-4h]

  strcpy(v5, a1);
  while ((unsigned int)strlen(v5) < 0xF)
    strcat(v5, netbios_c_variable_1);
  memset(&sRMIRegs_mod_190, 0, 52);
  memset(v8, 0, sizeof(v8));
  memset(v3, 0, 64);
  v3[0] = -79;
  v4[23] = -1;
  strcpy(v4, v5);
  memcpy(pListenPacket_mod_190, v3, 64);
  HIWORD(v1) = HIWORD(pListenPacket_mod_190);
  v9 = pListenPacket_mod_190;
  LOWORD(v1) = wListenSegment_mod_190;
  sRMIRegs_mod_190_variable_3 = wListenSegment_mod_190;
  sRMIRegs_mod_190_variable_1 = 0;
  sRMIRegs_mod_190_variable_2 = 256;
  v6[0] = 768;
  v6[2] = 92;
  v6[4] = 0;
  v8[0] = hmiGetDS(v1);
  v7 = &sRMIRegs_mod_190;
  hmiINT386x(49, v6, v6, v8);
  while (*(unsigned __int8 *)(v9 + 49) == 255)
    ;
  return *(_BYTE *)(v9 + 49) == 0;
}

//-------------------------------------------------------------------------------------------------

bool hmiNETBIOSGetAdapterStatus()
{
  int v0; // eax
  char v2[4]; // [esp+0h] [ebp-74h] BYREF
  __int16 v3; // [esp+4h] [ebp-70h]
  __int16 v4; // [esp+6h] [ebp-6Eh]
  __int16 v5; // [esp+8h] [ebp-6Ch]
  _BYTE v6[54]; // [esp+Ah] [ebp-6Ah] BYREF
  _WORD v7[10]; // [esp+40h] [ebp-34h] BYREF
  void *v8; // [esp+54h] [ebp-20h]
  _WORD v9[6]; // [esp+5Ch] [ebp-18h] BYREF
  unsigned int i; // [esp+6Ch] [ebp-8h]
  int v11; // [esp+70h] [ebp-4h]

  memset(&sRMIRegs_mod_190, 0, 52);
  memset(v9, 0, sizeof(v9));
  memset(v2, 0, 64);
  v2[0] = -77;
  v6[39] = -1;
  v5 = 420;
  v4 = wListenSegment_mod_190;
  v3 = 64;
  strcpy(v6, &sNCBAddName_variable_2);
  memcpy(pListenPacket_mod_190, v2, 64);
  HIWORD(v0) = HIWORD(pListenPacket_mod_190);
  v11 = pListenPacket_mod_190;
  LOWORD(v0) = wListenSegment_mod_190;
  sRMIRegs_mod_190_variable_3 = wListenSegment_mod_190;
  sRMIRegs_mod_190_variable_1 = 0;
  sRMIRegs_mod_190_variable_2 = 256;
  v7[0] = 768;
  v7[2] = 92;
  v7[4] = 0;
  v9[0] = hmiGetDS(v0);
  v8 = &sRMIRegs_mod_190;
  hmiINT386x(49, v7, v7, v9);
  while (*(unsigned __int8 *)(v11 + 49) == 255)
    ;
  memcpy(&sAdapterStatus, pListenPacket_mod_190 + 64, 420);
  memcpy(sNetworkAddr_mod_190, &sAdapterStatus, 6);
  for (i = 0; i < 6; ++i) {
    if (!sNetworkAddr_mod_190[i])
      sNetworkAddr_mod_190[i] = 1;
  }
  for (i = 6; i < 0xF; ++i)
    sNetworkAddr_mod_190[i] = 32;
  return hmiNETBIOSAddName((int)sNetworkAddr_mod_190);
}

//-------------------------------------------------------------------------------------------------

int hmiNETBIOSCancelAll()
{
  int v0; // eax
  char v2[4]; // [esp+0h] [ebp-74h] BYREF
  __int16 v3; // [esp+4h] [ebp-70h]
  __int16 v4; // [esp+6h] [ebp-6Eh]
  char v5; // [esp+31h] [ebp-43h]
  _WORD v6[10]; // [esp+40h] [ebp-34h] BYREF
  void *v7; // [esp+54h] [ebp-20h]
  _WORD v8[6]; // [esp+5Ch] [ebp-18h] BYREF
  int v9; // [esp+68h] [ebp-Ch]
  unsigned int i; // [esp+70h] [ebp-4h]

  for (i = 0; i < 0x40; ++i) {
    if (*(int *)((char *)&pListenElements_mod_190_variable_4 + 78 * i)
      && *(_BYTE *)(*(int *)((char *)&pListenElements_mod_190_variable_4 + 78 * i) + 49) == 0xFF) {
      memset(&sRMIRegs_mod_190, 0, 52);
      memset(v8, 0, sizeof(v8));
      memset(v2, 0, 64);
      v2[0] = 53;
      v5 = -1;
      v4 = wListenSegment_mod_190;
      v3 = pListenElements_mod_190_variable_2[39 * i];
      v0 = memcpy(pSendPacketPtr_mod_190, v2, 64);
      LOWORD(v0) = wSendSegment_mod_190;
      sRMIRegs_mod_190_variable_3 = wSendSegment_mod_190;
      sRMIRegs_mod_190_variable_1 = 0;
      sRMIRegs_mod_190_variable_2 = 256;
      v6[0] = 768;
      v6[2] = 92;
      v6[4] = 0;
      v8[0] = hmiGetDS(v0);
      v7 = &sRMIRegs_mod_190;
      hmiINT386x(49, v6, v6, v8);
    }
  }
  v9 = 1;
  return 1;
}

//-------------------------------------------------------------------------------------------------
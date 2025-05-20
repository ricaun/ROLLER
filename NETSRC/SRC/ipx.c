/*
//-------------------------------------------------------------------------------------------------

int __cdecl hmiIPXInitSystem(int a1, unsigned int a2)
{
  unsigned int i; // [esp+4h] [ebp-14h]
  unsigned int j; // [esp+4h] [ebp-14h]
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  if (!hmiIPXInstalled())
    return 2;
  wActiveNodes = 0;
  wIPXSocket = ((_WORD)a2 << 8) | (a2 >> 8);
  if (hmiIPXOpenSocket((unsigned __int16)wIPXSocket))
    return 3;
  if (!hmiNETNOWAllocateRealMem(0x9380u, &pSendPacketPtr, &wSendSegment))
    return 1;
  if (!hmiNETNOWAllocateRealMem(0x9380u, &pListenPacketPtr, &wListenSegment))
    return 1;
  pSendPacket = pSendPacketPtr;
  pListenPacket = pListenPacketPtr;
  hmiIPXGetInternetworkAddr(&sNetworkAddr_mod_189);
  hmiIPXGetLocalTarget(&sNetworkAddr_mod_189);
  memcpy(&sNetNOWAddr, &sNetworkAddr_mod_189, 16);
  hmiIPXAddNode((int)&sNetNOWAddr);
  wSendSequence = 0;
  wMaxNodes = a1;
  v7 = 0;
  v6 = 0;
  for (i = 0; i < 0x40; ++i) {
    *((_WORD *)&pSendElements + 48 * i) = 0;
    pSendElements_variable_2[48 * i] = v7;
    pSendElements_variable_3[24 * i] = 0;
    v7 += 590;
  }
  for (j = 0; j < 0x40; ++j) {
    *((_WORD *)&pListenElements + 48 * j) = 0;
    pListenElements_variable_2[48 * j] = v6;
    pListenElements_variable_3[24 * j] = 0;
    v6 += 590;
  }
  memset(&sNodes_variable_3, 255, 6);
  memset(&sNodes_variable_2, 255, 6);
  memset(&sNodes_variable_1, 0, 4);
  return 0;
}

//-------------------------------------------------------------------------------------------------

int hmiIPXUnInitSystem()
{
  hmiIPXCloseSocket((unsigned __int16)wIPXSocket);
  return 1;
}

//-------------------------------------------------------------------------------------------------

int hmiIPXGetActiveNodes()
{
  return wActiveNodes;
}

//-------------------------------------------------------------------------------------------------

int hmiIPXGetConsoleNode()
{
  return wConsoleNode_mod_189;
}

//-------------------------------------------------------------------------------------------------

unsigned int hmiIPXSortNodes()
{
  unsigned int result; // eax
  _BYTE v1[16]; // [esp+0h] [ebp-18h] BYREF
  int v2; // [esp+10h] [ebp-8h]
  unsigned int i; // [esp+14h] [ebp-4h]

  do {
    v2 = 0;
    for (i = 0; wActiveNodes - 1 > i; ++i) {
      if (memcmp((char *)&sNodes + 16 * i, (char *)&sNodes + 16 * i + 16, 16) < 0) {
        v2 = 1;
        memcpy(v1, (char *)&sNodes + 16 * i, sizeof(v1));
        memcpy((char *)&sNodes + 16 * i, (char *)&sNodes + 16 * i + 16, 16);
        memcpy((char *)&sNodes + 16 * i + 16, v1, 16);
      }
    }
  } while (v2);
  for (i = 0; ; ++i) {
    result = i;
    if (i >= wActiveNodes)
      break;
    if (!memcmp((char *)&sNodes + 16 * i, &sNetworkAddr_mod_189, 16))
      wConsoleNode_mod_189 = i;
  }
  return result;
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiIPXGetNetworkAddr(int a1)
{
  memcpy(a1, &sNetworkAddr_mod_189, 16);
  return 1;
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiIPXAddNode(int a1)
{
  unsigned int i; // [esp+4h] [ebp-4h]

  if (wActiveNodes) {
    if (wActiveNodes == wMaxNodes) {
      return 2;
    } else {
      for (i = 0; ; ++i) {
        if (i >= wActiveNodes) {
          memcpy((char *)&sNodes + 16 * wActiveNodes, a1, 16);
          ++wActiveNodes;
          return 0;
        }
        if (!memcmp((char *)&sNodes + 16 * i, a1, 16))
          break;
      }
      return 1;
    }
  } else {
    memcpy(&sNodes, a1, 16);
    ++wActiveNodes;
    return 0;
  }
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiIPXDeleteNode(unsigned int a1)
{
  if (a1 >= wActiveNodes)
    return 1;
  memcpy((char *)&sNodes + 16 * a1, (char *)&sNodes + 16 * a1 + 16, 16 * (wActiveNodes - a1));
  --wActiveNodes;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiIPXNetAddrToNode(int a1)
{
  unsigned int i; // [esp+4h] [ebp-4h]

  if (!wActiveNodes)
    return -1;
  for (i = 0; ; ++i) {
    if (i >= wActiveNodes)
      return -1;
    if (!memcmp((char *)&sNodes + 16 * i, a1, 16))
      break;
  }
  return i;
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiIPXGetData(int a1, int a2, int a3, int a4)
{
  int v6; // [esp+4h] [ebp-10h]
  int v7; // [esp+4h] [ebp-10h]
  int v8; // [esp+8h] [ebp-Ch]
  unsigned int v9; // [esp+Ch] [ebp-8h]
  unsigned int i; // [esp+10h] [ebp-4h]

  v9 = -1;
  v8 = -1;
  for (i = 0; i < 0x40; ++i) {
    v6 = pListenElements_variable_3[24 * i];
    if (!*(_BYTE *)(v6 + 8) && *(_DWORD *)(v6 + 78) < v9) {
      v9 = *(_DWORD *)(v6 + 78);
      v8 = i;
    }
  }
  if (v8 == -1)
    return 0;
  v7 = pListenElements_variable_3[24 * v8];
  memcpy(a1, v7 + 78, a2);
  if (a4)
    memcpy(a3, a2 + v7 + 78, a4);
  *((_WORD *)&pListenElements + 48 * v8) = 0;
  hmiIPXPostListen();
  return 1;
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiIPXGetHeader(int a1, int a2, _DWORD *a3)
{
  int v5; // [esp+4h] [ebp-10h]
  int v6; // [esp+4h] [ebp-10h]
  int v7; // [esp+8h] [ebp-Ch]
  unsigned int v8; // [esp+Ch] [ebp-8h]
  unsigned int i; // [esp+10h] [ebp-4h]

  v8 = -1;
  v7 = -1;
  for (i = 0; i < 0x40; ++i) {
    v5 = pListenElements_variable_3[24 * i];
    if (!*(_BYTE *)(v5 + 8) && *(_DWORD *)(v5 + 78) < v8) {
      v8 = *(_DWORD *)(v5 + 78);
      v7 = i;
    }
  }
  if (v7 == -1)
    return 0;
  v6 = pListenElements_variable_3[24 * v7];
  memcpy(a1, v6 + 78, a2);
  *a3 = v6 + 78 + a2;
  *((_WORD *)&pListenElements + 48 * v7) = 0;
  return 1;
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiIPXSendData(int *a1, int a2, int a3, __int16 a4, unsigned int a5)
{
  int v5; // edx
  char *v8; // [esp+8h] [ebp-8h]
  unsigned int i; // [esp+Ch] [ebp-4h]

  if (a5 >= wActiveNodes && a5 != 21)
    return 0;
  for (i = 0; i < 0x40 && *((char *)&pSendElements_variable_1 + 96 * i) < 0; ++i)
    ;
  if (i != 64)
    goto LABEL_17;
  for (i = 0; i < 0x40 && *(_BYTE *)(pSendElements_variable_3[24 * i] + 8); ++i)
    ;
  if (i == 64)
    return 0;
LABEL_17:
  v8 = (char *)&pSendElements + 96 * i;
  *(_WORD *)v8 = -28672;
  pSendPacket = pSendPacketPtr + *((unsigned __int16 *)v8 + 1);
  wECBOffset = *((_WORD *)v8 + 1);
  memset(v8 + 4, 0, 30);
  memset(v8 + 34, 0, 48);
  *((_WORD *)v8 + 2) = -1;
  v8[9] = 4;
  *((_WORD *)v8 + 10) = wIPXSocket;
  *((_WORD *)v8 + 16) = wIPXSocket;
  memcpy(v8 + 10, &sNetworkAddr_mod_189, 4);
  memcpy(v8 + 22, &sNetworkAddr_mod_189, 4);
  memcpy(v8 + 14, (char *)&sNodes + 16 * a5 + 4, 6);
  memcpy(v8 + 26, &sNetworkAddr_mod_189_variable_1, 6);
  *((_WORD *)v8 + 22) = wIPXSocket;
  *((_WORD *)v8 + 34) = 2;
  v8[42] = 29;
  *(_DWORD *)(v8 + 70) = v8 + 4;
  *((_WORD *)v8 + 37) = 30;
  *((_DWORD *)v8 + 19) = a3;
  *((_WORD *)v8 + 40) = a4;
  memcpy(v8 + 62, (char *)&sNodes + 16 * a5 + 4, 6);
  v5 = wSendSequence++;
  *a1 = v5;
  hmiIPXSendPacket(v8 + 34, v8 + 82, a1, a2);
  *(_DWORD *)(v8 + 86) = *(_DWORD *)(v8 + 82) + 48;
  return 1;
}

int __cdecl hmiIPXSendDataDirect(int *a1, int a2, int a3, __int16 a4, int a5)
{
  int v5; // edx
  char *v8; // [esp+8h] [ebp-8h]
  unsigned int i; // [esp+Ch] [ebp-4h]

  for (i = 0; i < 0x40 && *((char *)&pSendElements_variable_1 + 96 * i) < 0; ++i)
    ;
  if (i != 64)
    goto LABEL_14;
  for (i = 0; i < 0x40 && *(_BYTE *)(pSendElements_variable_3[24 * i] + 8); ++i)
    ;
  if (i == 64)
    return 0;
LABEL_14:
  v8 = (char *)&pSendElements + 96 * i;
  *(_WORD *)v8 = -28672;
  pSendPacket = *((unsigned __int16 *)v8 + 1) + pSendPacketPtr;
  wECBOffset = *((_WORD *)v8 + 1);
  memset(v8 + 4, 0, 30);
  memset(v8 + 34, 0, 48);
  *((_WORD *)v8 + 2) = -1;
  v8[9] = 4;
  *((_WORD *)v8 + 10) = wIPXSocket;
  *((_WORD *)v8 + 16) = wIPXSocket;
  memcpy(v8 + 10, &sNetworkAddr_mod_189, 4);
  memcpy(v8 + 22, &sNetworkAddr_mod_189, 4);
  memcpy(v8 + 14, a5 + 4, 6);
  memcpy(v8 + 26, &sNetworkAddr_mod_189_variable_1, 6);
  *((_WORD *)v8 + 22) = wIPXSocket;
  *((_WORD *)v8 + 34) = 2;
  v8[42] = 29;
  *(_DWORD *)(v8 + 70) = v8 + 4;
  *((_WORD *)v8 + 37) = 30;
  *((_DWORD *)v8 + 19) = a3;
  *((_WORD *)v8 + 40) = a4;
  memcpy(v8 + 62, a5 + 4, 6);
  v5 = wSendSequence++;
  *a1 = v5;
  hmiIPXSendPacket(v8 + 34, v8 + 82, a1, a2);
  *(_DWORD *)(v8 + 86) = *(_DWORD *)(v8 + 82) + 48;
  return 1;
}

//-------------------------------------------------------------------------------------------------

int hmiIPXPostListen()
{
  char *v2; // [esp+4h] [ebp-8h]
  unsigned int i; // [esp+8h] [ebp-4h]

  for (i = 0; i < 0x40 && *((char *)&pListenElements_variable_1 + 96 * i) < 0; ++i)
    ;
  if (i == 64)
    return 0;
  v2 = (char *)&pListenElements + 96 * i;
  *(_WORD *)v2 = -24576;
  pListenPacket = *((unsigned __int16 *)v2 + 1) + pListenPacketPtr;
  wECBOffset = *((_WORD *)v2 + 1);
  memset(v2 + 4, 0, 30);
  memset(v2 + 34, 0, 48);
  *((_WORD *)v2 + 2) = -1;
  v2[9] = 4;
  *((_WORD *)v2 + 10) = wIPXSocket;
  *((_WORD *)v2 + 16) = wIPXSocket;
  memcpy(v2 + 10, &sNetworkAddr_mod_189, 4);
  memcpy(v2 + 22, &sNetworkAddr_mod_189, 4);
  memset(v2 + 14, 255, 6);
  memcpy(v2 + 26, &sNetworkAddr_mod_189_variable_1, 6);
  *((_WORD *)v2 + 22) = wIPXSocket;
  *((_WORD *)v2 + 34) = 2;
  v2[42] = 29;
  *(_DWORD *)(v2 + 70) = v2 + 4;
  *((_WORD *)v2 + 37) = 30;
  *((_DWORD *)v2 + 19) = 0;
  *((_WORD *)v2 + 40) = 512;
  memset(v2 + 62, 255, 6);
  hmiIPXListenForPacket(v2 + 34, v2 + 82);
  *(_DWORD *)(v2 + 86) = *(_DWORD *)(v2 + 82) + 48;
  return 1;
}

//-------------------------------------------------------------------------------------------------

bool hmiIPXInstalled()
{
  int v0; // eax
  _WORD v2[10]; // [esp+0h] [ebp-2Ch] BYREF
  int *v3; // [esp+14h] [ebp-18h]
  _WORD v4[6]; // [esp+1Ch] [ebp-10h] BYREF

  memset(&sRMIRegs, 0, 52);
  memset(v4, 0, sizeof(v4));
  v0 = memset(v2, 0, 28);
  sRMIRegs_variable_4 = 31232;
  v2[0] = 768;
  v2[2] = 47;
  v2[4] = 0;
  v4[0] = hmiGetDS(v0);
  v3 = &sRMIRegs;
  hmiINT386x(49, v2, v2, v4);
  return (_BYTE)sRMIRegs_variable_4 == 0xFF;
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiIPXOpenSocket(int a1)
{
  _WORD v2[10]; // [esp+0h] [ebp-2Ch] BYREF
  int *v3; // [esp+14h] [ebp-18h]
  _WORD v4[6]; // [esp+1Ch] [ebp-10h] BYREF

  memset(&sRMIRegs, 0, 52);
  memset(v4, 0, sizeof(v4));
  sRMIRegs_variable_4 = 255;
  sRMIRegs_variable_2 = 0;
  sRMIRegs_variable_3 = a1;
  v2[0] = 768;
  v2[2] = 122;
  v2[4] = 0;
  v4[0] = hmiGetDS(a1);
  v3 = &sRMIRegs;
  hmiINT386x(49, v2, v2, v4);
  return (unsigned __int8)sRMIRegs_variable_4;
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiIPXCloseSocket(int a1)
{
  _WORD v2[10]; // [esp+0h] [ebp-2Ch] BYREF
  int *v3; // [esp+14h] [ebp-18h]
  _WORD v4[6]; // [esp+1Ch] [ebp-10h] BYREF

  memset(&sRMIRegs, 0, 52);
  memset(v4, 0, sizeof(v4));
  sRMIRegs_variable_2 = 1;
  sRMIRegs_variable_3 = a1;
  v2[0] = 768;
  v2[2] = 122;
  v2[4] = 0;
  v4[0] = hmiGetDS(a1);
  v3 = &sRMIRegs;
  hmiINT386x(49, v2, v2, v4);
  return 1;
}

//-------------------------------------------------------------------------------------------------

int hmiIPXRelinquishControl()
{
  int v0; // eax
  _WORD v2[10]; // [esp+0h] [ebp-28h] BYREF
  int *v3; // [esp+14h] [ebp-14h]
  _WORD v4[6]; // [esp+1Ch] [ebp-Ch] BYREF

  memset(&sRMIRegs, 0, 52);
  v0 = memset(v4, 0, sizeof(v4));
  sRMIRegs_variable_2 = 10;
  v2[0] = 768;
  v2[2] = 122;
  v2[4] = 0;
  v4[0] = hmiGetDS(v0);
  v3 = &sRMIRegs;
  return hmiINT386x(49, v2, v2, v4);
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiIPXListenForPacket(int a1, _DWORD *a2)
{
  int v2; // eax
  _WORD v4[10]; // [esp+0h] [ebp-30h] BYREF
  int *v5; // [esp+14h] [ebp-1Ch]
  _WORD v6[6]; // [esp+1Ch] [ebp-14h] BYREF
  _WORD *v7; // [esp+28h] [ebp-8h]
  int v8; // [esp+2Ch] [ebp-4h]

  v7 = (_WORD *)pListenPacket;
  v8 = pListenPacket + 48;
  *a2 = pListenPacket;
  memcpy(v7, a1, 48);
  memset(v8, 0, 30);
  v7[18] = wECBOffset + 48;
  v7[19] = wListenSegment;
  v7[21] = wECBOffset + 78;
  v7[22] = wListenSegment;
  memset(&sRMIRegs, 0, 52);
  memset(v6, 0, sizeof(v6));
  sRMIRegs_variable_2 = 4;
  v2 = (unsigned __int16)wECBOffset;
  sRMIRegs_variable_1 = (unsigned __int16)wECBOffset;
  LOWORD(v2) = wListenSegment;
  sRMIRegs_variable_5 = wListenSegment;
  v4[0] = 768;
  v4[2] = 122;
  v4[4] = 0;
  v6[0] = hmiGetDS(v2);
  v5 = &sRMIRegs;
  return hmiINT386x(49, v4, v4, v6);
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiIPXGetListenData(int a1, int a2, int a3)
{
  int result; // eax

  if (a2) {
    memcpy(a2, (unsigned __int16)wECBOffset + pListenPacket + 78, a3);
    result = a1;
    if (*(_WORD *)(a1 + 46))
      return memcpy(
               *(_DWORD *)(a1 + 42),
               pListenPacket + a3 + (unsigned __int16)wECBOffset + 78,
               *(unsigned __int16 *)(a1 + 46) - a3);
  } else {
    result = a1;
    if (*(_WORD *)(a1 + 46))
      return memcpy(
               *(_DWORD *)(a1 + 42),
               (unsigned __int16)wECBOffset + pListenPacket + 78,
               *(unsigned __int16 *)(a1 + 46));
  }
  return result;
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiIPXSendPacket(int a1, _DWORD *a2, int a3, int a4)
{
  int v4; // eax
  _WORD v6[10]; // [esp+0h] [ebp-34h] BYREF
  int *v7; // [esp+14h] [ebp-20h]
  _WORD v8[6]; // [esp+1Ch] [ebp-18h] BYREF
  int v9; // [esp+28h] [ebp-Ch]
  _WORD *v10; // [esp+2Ch] [ebp-8h]
  int v11; // [esp+30h] [ebp-4h]

  v10 = (_WORD *)pSendPacket;
  v11 = pSendPacket + 48;
  v9 = pSendPacket + 78;
  *a2 = pSendPacket;
  memcpy(v10, a1, 48);
  memcpy(v11, *(_DWORD *)(a1 + 36), *(unsigned __int16 *)(a1 + 40));
  if (a3) {
    memcpy(v9, a3, a4);
    if (*(_WORD *)(a1 + 46))
      memcpy(a4 + v9, *(_DWORD *)(a1 + 42), *(unsigned __int16 *)(a1 + 46));
    v10[23] += a4;
  } else if (*(_WORD *)(a1 + 46)) {
    memcpy(v9, *(_DWORD *)(a1 + 42), *(unsigned __int16 *)(a1 + 46));
  }
  v10[18] = wECBOffset + 48;
  v10[19] = wSendSegment;
  v10[21] = wECBOffset + 78;
  v10[22] = wSendSegment;
  memset(&sRMIRegs, 0, 52);
  memset(v8, 0, sizeof(v8));
  sRMIRegs_variable_2 = 3;
  v4 = (unsigned __int16)wECBOffset;
  sRMIRegs_variable_1 = (unsigned __int16)wECBOffset;
  LOWORD(v4) = wSendSegment;
  sRMIRegs_variable_5 = wSendSegment;
  v6[0] = 768;
  v6[2] = 122;
  v6[4] = 0;
  v8[0] = hmiGetDS(v4);
  v7 = &sRMIRegs;
  return hmiINT386x(49, v6, v6, v8);
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiIPXGetInternetworkAddr(int a1)
{
  int v1; // eax
  _WORD v3[10]; // [esp+0h] [ebp-28h] BYREF
  int *v4; // [esp+14h] [ebp-14h]
  _WORD v5[6]; // [esp+1Ch] [ebp-Ch] BYREF

  memset(&sRMIRegs, 0, 52);
  v1 = memset(v5, 0, sizeof(v5));
  LOWORD(v1) = wListenSegment;
  sRMIRegs_variable_5 = wListenSegment;
  sRMIRegs_variable_1 = 0;
  sRMIRegs_variable_2 = 9;
  v3[0] = 768;
  v3[2] = 122;
  v3[4] = 0;
  v5[0] = hmiGetDS(v1);
  v4 = &sRMIRegs;
  hmiINT386x(49, v3, v3, v5);
  return memcpy(a1, pListenPacket, 10);
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiIPXGetLocalTarget(int a1)
{
  int v1; // eax
  _WORD v3[10]; // [esp+0h] [ebp-28h] BYREF
  int *v4; // [esp+14h] [ebp-14h]
  _WORD v5[6]; // [esp+1Ch] [ebp-Ch] BYREF

  memset(&sRMIRegs, 0, 52);
  memset(v5, 0, sizeof(v5));
  v1 = memcpy(pListenPacket, a1, 16);
  LOWORD(v1) = wListenSegment;
  sRMIRegs_variable_5 = wListenSegment;
  sRMIRegs_variable_1 = 0;
  sRMIRegs = 10;
  sRMIRegs_variable_2 = 2;
  v3[0] = 768;
  v3[2] = 122;
  v3[4] = 0;
  v5[0] = hmiGetDS(v1);
  v4 = &sRMIRegs;
  hmiINT386x(49, v3, v3, v5);
  return memcpy(a1, pListenPacket, 16);
}

//-------------------------------------------------------------------------------------------------
*/
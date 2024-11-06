#ifdef ENABLE_NETSRC_PSEUDO
//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETNOWInitSystem(int a1)
{
  int v2; // [esp+0h] [ebp-8h]
  unsigned int v3; // [esp+4h] [ebp-4h]

  switch (hmiIPXInitSystem(a1, 17733)) {
    case 0:
      wNETNOWType = 4;
      pfnNETNOWSendData = (int)hmiIPXSendData;
      pfnNETNOWSendDataDirect = (int)hmiIPXSendDataDirect;
      pfnNETNOWGetData = (int)hmiIPXGetData;
      pfnNETNOWGetConsoleNode = (int)hmiIPXGetConsoleNode;
      pfnNETNOWGetActiveNodes = (int)hmiIPXGetActiveNodes;
      pfnNETNOWUnInitSystem = (int)hmiIPXUnInitSystem;
      pfnNETNOWPostListen = (int)hmiIPXPostListen;
      pfnNETNOWSortNodes = (int)hmiIPXSortNodes;
      pfnNETNOWAddNode = (int)hmiIPXAddNode;
      pfnNETNOWDeleteNode = (int)hmiIPXDeleteNode;
      pfnNETNOWNetAddrToNode = (int)hmiIPXNetAddrToNode;
      pfnNETNOWGetNetworkAddr = (int)hmiIPXGetNetworkAddr;
      pfnNETNOWGetHeader = (int)hmiIPXGetHeader;
      hmiNETNOWGetNetworkAddr(&sNetworkAddr);
      v2 = 0;
      break;
    case 1:
      v2 = 3;
      break;
    case 3:
      v2 = 2;
      break;
    default:
      v3 = hmiNETBIOSInitSystem(a1);
      if (v3) {
        if (v3 <= 1) {
          v2 = 3;
        } else if (v3 == 3) {
          v2 = 2;
        } else {
          v2 = 1;
        }
      } else {
        wNETNOWType = 5;
        pfnNETNOWSendData = (int)hmiNETBIOSSendData;
        pfnNETNOWSendDataDirect = (int)hmiNETBIOSSendDataDirect;
        pfnNETNOWGetData = (int)hmiNETBIOSGetData;
        pfnNETNOWGetConsoleNode = (int)hmiNETBIOSGetConsoleNode;
        pfnNETNOWGetActiveNodes = (int)hmiNETBIOSGetActiveNodes;
        pfnNETNOWUnInitSystem = (int)hmiNETBIOSUnInitSystem;
        pfnNETNOWPostListen = (int)hmiNETBIOSPostListen;
        pfnNETNOWSortNodes = (int)hmiNETBIOSSortNodes;
        pfnNETNOWAddNode = (int)hmiNETBIOSAddNode;
        pfnNETNOWDeleteNode = (int)hmiNETBIOSDeleteNode;
        pfnNETNOWNetAddrToNode = (int)hmiNETBIOSNetAddrToNode;
        pfnNETNOWGetNetworkAddr = (int)hmiNETBIOSGetNetworkAddr;
        pfnNETNOWGetHeader = (int)hmiNETBIOSGetHeader;
        hmiNETNOWGetNetworkAddr(&sNetworkAddr);
        v2 = 0;
      }
      break;
  }
  return v2;
}

//-------------------------------------------------------------------------------------------------

int hmiNETNOWUnInitSystem()
{
  return pfnNETNOWUnInitSystem();
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETNOWSendData(int a1, int a2, int a3, int a4, int a5)
{
  return pfnNETNOWSendData(a1, a2, a3, a4, a5);
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETNOWSendDataDirect(int a1, int a2, int a3, int a4, int a5)
{
  return pfnNETNOWSendDataDirect(a1, a2, a3, a4, a5);
}

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETNOWGetData(int a1, int a2, int a3, int a4)
{
  return pfnNETNOWGetData(a1, a2, a3, a4);
}

//-------------------------------------------------------------------------------------------------

int hmiNETNOWGetConsoleNode()
{
  return pfnNETNOWGetConsoleNode();
}

//-------------------------------------------------------------------------------------------------

int hmiNETNOWGetActiveNodes()
{
  return pfnNETNOWGetActiveNodes();
}

//-------------------------------------------------------------------------------------------------

bool __cdecl hmiNETNOWFindNodes(unsigned int a1)
{
  const time_t *v2[9]; // [esp+0h] [ebp-78h] BYREF
  _BYTE v3[4]; // [esp+24h] [ebp-54h] BYREF
  int v4; // [esp+28h] [ebp-50h]
  _BYTE v5[4]; // [esp+3Ch] [ebp-3Ch] BYREF
  int v6; // [esp+40h] [ebp-38h]
  _BYTE v7[16]; // [esp+54h] [ebp-24h] BYREF
  const time_t *v8; // [esp+68h] [ebp-10h]
  unsigned int v9; // [esp+6Ch] [ebp-Ch]
  int v10; // [esp+70h] [ebp-8h]
  int v11; // [esp+74h] [ebp-4h]

  while (hmiNETNOWPostListen())
    ;
  v11 = 3;
  v9 = 1;
  v8 = (const time_t *)-1;
  v6 = 2;
  while (!kbhit(0) && v9 < a1) {
    v10 = time(0);
    gmtime(v2[0]);
    if (v2[0] != v8) {
      cputs(asc_A2BD8, v2);
      v8 = v2[0];
      hmiNETNOWSendData((int)v5, 24, (int)&sNetworkAddr, 16, 21);
    }
    while (hmiNETNOWGetData((int)v3, 24, (int)v7, 16)) {
      if (v4 == 2 && !hmiNETNOWAddNode(v7))
        ++v9;
    }
  }
  if (v9 == a1) {
    do {
      v10 = time(0);
      gmtime(v2[0]);
      if (v2[0] != v8) {
        cputs(asc_A2BD8, v2);
        v8 = v2[0];
        hmiNETNOWSendData((int)v5, 24, (int)&sNetworkAddr, 16, 21);
        --v11;
      }
    } while (v11);
  }
  hmiNETNOWSortNodes();
  return v9 == a1;
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETNOWAddNode(int a1)
{
  return pfnNETNOWAddNode(a1);
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETNOWNetAddrToNode(int a1)
{
  return pfnNETNOWNetAddrToNode(a1);
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETNOWDeleteNode(int a1)
{
  return pfnNETNOWDeleteNode(a1);
}

//-------------------------------------------------------------------------------------------------

int hmiNETNOWSortNodes()
{
  return pfnNETNOWSortNodes();
}

//-------------------------------------------------------------------------------------------------

int hmiNETNOWPostListen()
{
  return pfnNETNOWPostListen();
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETNOWGetNetworkAddr(int a1)
{
  return pfnNETNOWGetNetworkAddr(a1);
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETNOWAllocateRealMem(unsigned int a1, int *a2, _DWORD *a3)
{
  _WORD v4[14]; // [esp+0h] [ebp-3Ch] BYREF
  _BYTE v5[12]; // [esp+1Ch] [ebp-20h] BYREF
  int v6; // [esp+28h] [ebp-14h]

  memset(v5, 0, sizeof(v5));
  v4[0] = 256;
  v4[2] = (a1 >> 4) + 256;
  hmiINT386x(49, v4, v4, v5);
  v6 = 16 * v4[0];
  *a3 = v4[0];
  *a2 = v6;
  return 1;
}

//-------------------------------------------------------------------------------------------------

int hmiNETNOWGetNetworkType()
{
  return wNETNOWType;
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETNOWGetBlock(int a1, int a2, int a3)
{
  memcpy(a2, a1, a3);
  return hmiNETNOWPostListen();
}

//-------------------------------------------------------------------------------------------------

int __cdecl hmiNETNOWGetHeader(int a1, int a2, int a3)
{
  return pfnNETNOWGetHeader(a1, a2, a3);
}

//-------------------------------------------------------------------------------------------------
#endif
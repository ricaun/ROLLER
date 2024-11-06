
//-------------------------------------------------------------------------------------------------

void sosDIGILoad_Start()
{
  ;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGILoadDriver(
        unsigned int a1,
        unsigned int a2,
        unsigned int a3,
        int a4,
        unsigned int a5,
        int a6,
        int a7,
        _BYTE *a8,
        _DWORD *a9)
{
  _DWORD *v9; // edx
  __int64 v10; // rax
  __int64 AliasCS; // rax
  unsigned int v13; // [esp+8h] [ebp-40h]
  unsigned __int16 v14; // [esp+Ch] [ebp-3Ch]
  unsigned int v15; // [esp+10h] [ebp-38h]
  int v19; // [esp+24h] [ebp-24h] BYREF
  _BYTE v20[8]; // [esp+28h] [ebp-20h] BYREF
  unsigned int v21; // [esp+30h] [ebp-18h]
  int v22; // [esp+34h] [ebp-14h]
  int v23; // [esp+38h] [ebp-10h]
  int v24; // [esp+3Ch] [ebp-Ch]
  int v25; // [esp+40h] [ebp-8h]
  int v26; // [esp+44h] [ebp-4h]

  v24 = 44;
  v23 = 48;
  v22 = 0;
  v21 = 0;
  if (a2 > 5)
    return 10;
  if (_wSOSDriverLoaded[a2])
    return 9;
  if (a1 < 0xE000 || a1 > 0xE200)
    return 6;
  strcpy(&_pSOSTempDriverPath, &_pSOSDriverPath);
  strcat(&_pSOSTempDriverPath, aHmidrv386);
  v26 = open(&_pSOSTempDriverPath, 512);
  if (v26 != -1) {
    v9 = &sLOADFileHeader;
    read(v26, &sLOADFileHeader, v24);
    while (1) {
      if (v21 > sLOADFileHeader_variable_1 || v22) {
        close(v26, v9);
        _wSOSDriverType[a2] = sLOADDriverHeader_variable_2;
        _wSOSDriverLoaded[a2] = 1;
        return 0;
      }
      read(v26, &sLOADDriverHeader, v23);
      v25 = sLOADDriverHeader_variable_1;
      if (sLOADDriverHeader_variable_2 == a1 && sLOADDriverHeader_variable_3 < 0) {
        v22 = 1;
        v10 = sosAllocateFarMem(v25, a7, &v19);
        v14 = WORD2(v10);
        v13 = v10;
        AliasCS = sosCreateAliasCS(v10, SWORD2(v10));
        v15 = AliasCS;
        if (sosDRVLockMemory(v19, v25))
          return 5;
        dos_read(v20);
        __writegsword(a3 + 4, WORD2(AliasCS));
        __writegsdword(a3, v15);
        __writegsword(a5 + 4, v14);
        __writegsdword(a5, v13);
        *a8 = v25;
        v9 = a9;
        *a9 = v19;
      } else {
        v9 = (_DWORD *)v25;
        lseek(v26, v25, 1);
      }
      ++v21;
    }
  }
  return 15;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIUnLoadDriver(unsigned int a1)
{
  if (a1 > 5)
    return 10;
  if (!_wSOSDriverLoaded[a1])
    return 10;
  _wSOSDriverLoaded[a1] = 0;
  if (sosDRVUnLockMemory(_wSOSDriverLinear[a1], _wSOSDriverSize[a1]))
    return 5;
  sosFreeSelector(
    *(int *)((char *)&_lpSOSDriver + 6 * a1),
    (unsigned __int16)_lpSOSDriver_variable_1[3 * a1],
    _wSOSDriverMemHandle[a1]);
  sosFreeSelector(
    *(int *)((char *)&_lpSOSDriverCS + 6 * a1),
    (unsigned __int16)_lpSOSDriverCS_variable_1[3 * a1],
    _wSOSDriverMemHandle[a1]);
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGILoadTimer(
        unsigned int a1,
        int a2,
        unsigned int a3,
        int a4,
        unsigned int a5,
        int a6,
        int a7,
        _BYTE *a8,
        _DWORD *a9)
{
  _DWORD *v9; // edx
  __int64 v10; // rax
  __int64 AliasCS; // rax
  unsigned int v13; // [esp+8h] [ebp-3Ch]
  unsigned __int16 v14; // [esp+Ch] [ebp-38h]
  unsigned int v15; // [esp+10h] [ebp-34h]
  int v18; // [esp+20h] [ebp-24h] BYREF
  _BYTE v19[8]; // [esp+24h] [ebp-20h] BYREF
  unsigned int v20; // [esp+2Ch] [ebp-18h]
  int v21; // [esp+30h] [ebp-14h]
  int v22; // [esp+34h] [ebp-10h]
  int v23; // [esp+38h] [ebp-Ch]
  int v24; // [esp+3Ch] [ebp-8h]
  int v25; // [esp+40h] [ebp-4h]

  v23 = 44;
  v22 = 48;
  v21 = 0;
  v20 = 0;
  if (a1 < 0x1000 || a1 > 0x1023)
    return 6;
  strcpy(&_pSOSTempDriverPath, &_pSOSDriverPath);
  strcat(&_pSOSTempDriverPath, aHmidrv386);
  v25 = open(&_pSOSTempDriverPath, 512);
  if (v25 != -1) {
    v9 = &sLOADFileHeader;
    read(v25, &sLOADFileHeader, v23);
    while (1) {
      if (v20 > sLOADFileHeader_variable_1 || v21) {
        close(v25, v9);
        return 0;
      }
      read(v25, &sLOADDriverHeader, v22);
      v24 = sLOADDriverHeader_variable_1;
      if (sLOADDriverHeader_variable_2 == a1 && (sLOADDriverHeader_variable_3 & 0x40) != 0) {
        v21 = 1;
        v24 += 0x4000;
        v10 = sosAllocateFarMem(v24, a7, &v18);
        v14 = WORD2(v10);
        v13 = v10;
        AliasCS = sosCreateAliasCS(v10, SWORD2(v10));
        v15 = AliasCS;
        if (sosDRVLockMemory(v18, v24))
          return 5;
        dos_read(v19);
        __writegsword(a3 + 4, WORD2(AliasCS));
        __writegsdword(a3, v15);
        __writegsword(a5 + 4, v14);
        __writegsdword(a5, v13);
        *a8 = v24;
        v9 = a9;
        *a9 = v18;
      } else {
        v9 = (_DWORD *)v24;
        lseek(v25, v24, 1);
      }
      ++v20;
    }
  }
  return 15;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIUnLoadTimer(int a1)
{
  if (sosDRVUnLockMemory(_wSOSTimerLinear[a1], _wSOSTimerSize[a1]))
    return 5;
  sosFreeSelector(
    *(int *)((char *)&_lpSOSTimer + 6 * a1),
    (unsigned __int16)_lpSOSTimer_variable_1[3 * a1],
    _wSOSTimerMemHandle[a1]);
  sosFreeSelector(
    *(int *)((char *)&_lpSOSTimerCS + 6 * a1),
    (unsigned __int16)_lpSOSTimerCS_variable_1[3 * a1],
    _wSOSTimerMemHandle[a1]);
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __stdcall sosDIGISetActiveTimer(int a1, int a2)
{
  return 0;
}

//-------------------------------------------------------------------------------------------------

void sosDIGILoad_End()
{
  ;
}

//-------------------------------------------------------------------------------------------------
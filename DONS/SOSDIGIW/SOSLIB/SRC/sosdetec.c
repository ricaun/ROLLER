#ifdef ENABLE_SOSLIB_PSEUDO
//-------------------------------------------------------------------------------------------------

void sosDIGIDetec_Start()
{
  ;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIDetectInit(int a1, __int16 a2)
{
  __int64 FarMem; // rax
  __int64 AliasCS; // rax

  if (_wDETInitialized)
    return 3;
  if (a1 || a2) {
    strcpy(&_pSOSTempDriverPath, a1);
    strcat(&_pSOSTempDriverPath, aHmidet386);
  } else {
    strcpy(&_pSOSTempDriverPath, aHmidet386);
  }
  _hDETFile = open(&_pSOSTempDriverPath, 512);
  if (_hDETFile == -1)
    return 15;
  read(_hDETFile, &_sDETFileHeader, 44);
  FarMem = sosAllocateFarMem(4096, &_wDETMemHandle, &_wDETLinear);
  _lpDETDriverBuffer_variable_1 = WORD2(FarMem);
  _lpDETDriverBuffer = FarMem;
  AliasCS = sosCreateAliasCS(FarMem, SWORD2(FarMem));
  _lpDETDriverBufferCS_variable_1 = WORD2(AliasCS);
  _lpDETDriverBufferCS = AliasCS;
  if (sosDRVLockMemory(_wDETLinear, 4096))
    return 5;
  lseek(_hDETFile, 0, 0);
  _wDETInitialized = 1;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIDetectUnInit(int a1, int a2)
{
  _wDETInitialized = 0;
  close(_hDETFile, a2);
  if (sosDRVUnLockMemory(_wDETLinear, 4096))
    return 5;
  sosFreeSelector(_lpDETDriverBuffer, (unsigned __int16)_lpDETDriverBuffer_variable_1, _wDETMemHandle);
  sosFreeSelector(_lpDETDriverBufferCS, (unsigned __int16)_lpDETDriverBufferCS_variable_1, _wDETMemHandle);
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIDetectFindHardware(unsigned int a1, int a2, int a3, unsigned __int16 a4, unsigned int a5, int a6)
{
  __int64 v6; // rax
  int i; // [esp+14h] [ebp-1Ch]
  _BYTE v11[4]; // [esp+18h] [ebp-18h] BYREF
  int v12; // [esp+1Ch] [ebp-14h]
  int v13; // [esp+20h] [ebp-10h]
  unsigned int v14; // [esp+24h] [ebp-Ch]
  int v15; // [esp+28h] [ebp-8h]
  int v16; // [esp+2Ch] [ebp-4h]

  v13 = 48;
  if (!a3 && !a4)
    return 2;
  if (a1 < 0xE000 || a1 > 0xE200)
    return 6;
  v15 = 0;
  v14 = 0;
  _wDETDriverIndexCur = 0;
  lseek(_hDETFile, 0, 0);
  read(_hDETFile, &_sDETFileHeader, 44);
  while (_wDETDriverIndexCur <= (unsigned int)_sDETFileHeader_variable_1 && !v15) {
    v12 = lseek(_hDETFile, 0, 1);
    read(_hDETFile, &_sDETDriverHeader, v13);
    v16 = _sDETDriverHeader_variable_1;
    if (_sDETDriverHeader_variable_2 == a1 && _sDETDriverHeader_variable_3 < 0) {
      v15 = 1;
      dos_read(v11);
    } else {
      lseek(_hDETFile, v16, 1);
    }
    ++_wDETDriverIndexCur;
  }
  if (v15 != 1)
    return 7;
  HIDWORD(v6) = (unsigned __int16)_lpDETDriverBufferCS_variable_1;
  sosDetDRVGetCapsInfo(
    _lpDETDriverBufferCS,
    (unsigned __int16)_lpDETDriverBufferCS_variable_1,
    _lpDETDriverBuffer,
    (unsigned __int16)_lpDETDriverBuffer_variable_1,
    &_sDETCaps,
    (unsigned __int16)__DS__);
  if ((_sDETCaps_variable_2 & 1) != 0) {
    sosDetDRVEnvStringInit(
      _lpDETDriverBufferCS,
      (unsigned __int16)_lpDETDriverBufferCS_variable_1,
      _lpDETDriverBuffer,
      _lpDETDriverBuffer_variable_1);
    for (i = 0; sosDetDRVGetEnvString(i); ++i) {
      LODWORD(v6) = sosDetDRVGetEnvString(i);
      v6 = getenv(v6, HIDWORD(v6));
      sosDetDRVSetEnvString(i, v6);
    }
  }
  v14 = sosDetDRVExist(
          _lpDETDriverBufferCS,
          (unsigned __int16)_lpDETDriverBufferCS_variable_1,
          _lpDETDriverBuffer,
          (unsigned __int16)_lpDETDriverBuffer_variable_1);
  if (!v14)
    return 8;
  sosDetDRVGetCapsInfo(
    _lpDETDriverBufferCS,
    (unsigned __int16)_lpDETDriverBufferCS_variable_1,
    _lpDETDriverBuffer,
    (unsigned __int16)_lpDETDriverBuffer_variable_1,
    a3,
    a4);
  *(_WORD *)&_lpDETDeviceCaps[4] = a4;
  *(_DWORD *)_lpDETDeviceCaps = a3;
  __writegsdword(a5, v14);
  _dwDETDriverIndex = v12;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIDetectGetCaps(unsigned int a1, int a2, int a3, unsigned __int16 a4)
{
  _BYTE v7[4]; // [esp+10h] [ebp-18h] BYREF
  int v8; // [esp+14h] [ebp-14h]
  int v9; // [esp+18h] [ebp-10h]
  int v10; // [esp+1Ch] [ebp-Ch]
  int v11; // [esp+20h] [ebp-8h]
  int v12; // [esp+24h] [ebp-4h]

  v9 = 48;
  if (!a3 && !a4)
    return 2;
  if (a1 < 0xE000 || a1 > 0xE200)
    return 6;
  v11 = 0;
  v10 = 0;
  _wDETDriverIndexCur = 0;
  lseek(_hDETFile, 0, 0);
  read(_hDETFile, &_sDETFileHeader, 44);
  while (_wDETDriverIndexCur <= (unsigned int)_sDETFileHeader_variable_1 && !v11) {
    v8 = lseek(_hDETFile, 0, 1);
    read(_hDETFile, &_sDETDriverHeader, v9);
    v12 = _sDETDriverHeader_variable_1;
    if (_sDETDriverHeader_variable_2 == a1 && _sDETDriverHeader_variable_3 < 0) {
      v11 = 1;
      dos_read(v7);
    } else {
      lseek(_hDETFile, v12, 1);
    }
    ++_wDETDriverIndexCur;
  }
  if (v11 != 1)
    return 7;
  sosDetDRVGetCapsInfo(
    _lpDETDriverBufferCS,
    (unsigned __int16)_lpDETDriverBufferCS_variable_1,
    _lpDETDriverBuffer,
    (unsigned __int16)_lpDETDriverBuffer_variable_1,
    a3,
    a4);
  *(_WORD *)&_lpDETDeviceCaps[4] = a4;
  *(_DWORD *)_lpDETDeviceCaps = a3;
  _dwDETDriverIndex = v8;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIDetectFindFirst(int a1, unsigned __int16 a2, unsigned int a3)
{
  __int64 v3; // rax
  int i; // [esp+18h] [ebp-20h]
  _BYTE v9[4]; // [esp+1Ch] [ebp-1Ch] BYREF
  int v10; // [esp+20h] [ebp-18h]
  int v11; // [esp+24h] [ebp-14h]
  unsigned int v12; // [esp+28h] [ebp-10h]
  int v13; // [esp+2Ch] [ebp-Ch]
  int v14; // [esp+30h] [ebp-8h]
  int v15; // [esp+34h] [ebp-4h]

  v14 = -1;
  v11 = 48;
  if (a1 || a2) {
    v13 = 0;
    v12 = 0;
    _wDETDriverIndexCur = 0;
    lseek(_hDETFile, 0, 0);
    read(_hDETFile, &_sDETFileHeader, 44);
    while (1) {
      if (_wDETDriverIndexCur > (unsigned int)_sDETFileHeader_variable_1 || v13)
        return 7;
      v10 = lseek(_hDETFile, 0, 1);
      read(_hDETFile, &_sDETDriverHeader, v11);
      v15 = _sDETDriverHeader_variable_1;
      v14 = _sDETDriverHeader_variable_2;
      if (_sDETDriverHeader_variable_3 >= 0) {
        lseek(_hDETFile, v15, 1);
      } else {
        dos_read(v9);
        HIDWORD(v3) = (unsigned __int16)__DS__;
        sosDetDRVGetCapsInfo(
          _lpDETDriverBufferCS,
          (unsigned __int16)_lpDETDriverBufferCS_variable_1,
          _lpDETDriverBuffer,
          (unsigned __int16)_lpDETDriverBuffer_variable_1,
          &_sDETCaps,
          (unsigned __int16)__DS__);
        if ((_sDETCaps_variable_2 & 1) != 0) {
          sosDetDRVEnvStringInit(
            _lpDETDriverBufferCS,
            (unsigned __int16)_lpDETDriverBufferCS_variable_1,
            _lpDETDriverBuffer,
            _lpDETDriverBuffer_variable_1);
          for (i = 0; sosDetDRVGetEnvString(i); ++i) {
            LODWORD(v3) = sosDetDRVGetEnvString(i);
            v3 = getenv(v3, HIDWORD(v3));
            sosDetDRVSetEnvString(i, v3);
          }
        }
        v12 = sosDetDRVExist(
                _lpDETDriverBufferCS,
                (unsigned __int16)_lpDETDriverBufferCS_variable_1,
                _lpDETDriverBuffer,
                (unsigned __int16)_lpDETDriverBuffer_variable_1);
        if (v12) {
          _dwDETDriverIndex = v10;
          sosDetDRVGetCapsInfo(
            _lpDETDriverBufferCS,
            (unsigned __int16)_lpDETDriverBufferCS_variable_1,
            _lpDETDriverBuffer,
            (unsigned __int16)_lpDETDriverBuffer_variable_1,
            a1,
            a2);
          *(_WORD *)&_lpDETDeviceCaps[4] = a2;
          *(_DWORD *)_lpDETDeviceCaps = a1;
          __writegsdword(a3, v12);
          return 0;
        }
      }
      ++_wDETDriverIndexCur;
    }
  }
  return 2;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIDetectFindNext(int a1, unsigned __int16 a2, unsigned int a3)
{
  __int64 v3; // rax
  int i; // [esp+18h] [ebp-20h]
  _BYTE v9[4]; // [esp+1Ch] [ebp-1Ch] BYREF
  int v10; // [esp+20h] [ebp-18h]
  int v11; // [esp+24h] [ebp-14h]
  unsigned int v12; // [esp+28h] [ebp-10h]
  int v13; // [esp+2Ch] [ebp-Ch]
  int v14; // [esp+30h] [ebp-8h]
  int v15; // [esp+34h] [ebp-4h]

  v14 = -1;
  v11 = 48;
  if (a1 || a2) {
    v13 = 0;
    v12 = 0;
    while (1) {
      if (_wDETDriverIndexCur > (unsigned int)_sDETFileHeader_variable_1 || v13)
        return 7;
      v10 = lseek(_hDETFile, 0, 1);
      read(_hDETFile, &_sDETDriverHeader, v11);
      v15 = _sDETDriverHeader_variable_1;
      v14 = _sDETDriverHeader_variable_2;
      if (_sDETDriverHeader_variable_3 >= 0) {
        lseek(_hDETFile, v15, 1);
      } else {
        dos_read(v9);
        HIDWORD(v3) = (unsigned __int16)__DS__;
        sosDetDRVGetCapsInfo(
          _lpDETDriverBufferCS,
          (unsigned __int16)_lpDETDriverBufferCS_variable_1,
          _lpDETDriverBuffer,
          (unsigned __int16)_lpDETDriverBuffer_variable_1,
          &_sDETCaps,
          (unsigned __int16)__DS__);
        if ((_sDETCaps_variable_2 & 1) != 0) {
          sosDetDRVEnvStringInit(
            _lpDETDriverBufferCS,
            (unsigned __int16)_lpDETDriverBufferCS_variable_1,
            _lpDETDriverBuffer,
            _lpDETDriverBuffer_variable_1);
          for (i = 0; sosDetDRVGetEnvString(i); ++i) {
            LODWORD(v3) = sosDetDRVGetEnvString(i);
            v3 = getenv(v3, HIDWORD(v3));
            sosDetDRVSetEnvString(i, v3);
          }
        }
        v12 = sosDetDRVExist(
                _lpDETDriverBufferCS,
                (unsigned __int16)_lpDETDriverBufferCS_variable_1,
                _lpDETDriverBuffer,
                (unsigned __int16)_lpDETDriverBuffer_variable_1);
        if (v12) {
          _dwDETDriverIndex = v10;
          sosDetDRVGetCapsInfo(
            _lpDETDriverBufferCS,
            (unsigned __int16)_lpDETDriverBufferCS_variable_1,
            _lpDETDriverBuffer,
            (unsigned __int16)_lpDETDriverBuffer_variable_1,
            a1,
            a2);
          *(_WORD *)&_lpDETDeviceCaps[4] = a2;
          *(_DWORD *)_lpDETDeviceCaps = a1;
          __writegsdword(a3, v12);
          return 0;
        }
      }
      ++_wDETDriverIndexCur;
    }
  }
  return 2;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIDetectGetSettings(unsigned int a1, __int16 a2)
{
  int i; // [esp+10h] [ebp-1Ch]
  int j; // [esp+10h] [ebp-1Ch]

  if (!a1 && !a2)
    return 2;
  lseek(_hDETFile, _dwDETDriverIndex, 0);
  for (i = 0; __readgsword(__readgsdword(*(_DWORD *)_lpDETDeviceCaps + 72) + 2 * i) != 0xFFFF; ++i)
    sosDIGIInitForWindows((__int16)__readgsword(__readgsdword(*(_DWORD *)_lpDETDeviceCaps + 72) + 2 * i));
  sosDetDRVGetSettings(
    _lpDETDriverBufferCS,
    (unsigned __int16)_lpDETDriverBufferCS_variable_1,
    _lpDETDriverBuffer,
    (unsigned __int16)_lpDETDriverBuffer_variable_1);
  for (j = 0; __readgsword(__readgsdword(*(_DWORD *)_lpDETDeviceCaps + 72) + 2 * j) != 0xFFFF; ++j)
    sosDIGIUnInitForWindows((__int16)__readgsword(__readgsdword(*(_DWORD *)_lpDETDeviceCaps + 72) + 2 * j));
  __writegsdword(a1, wDetectPort);
  __writegsdword(a1 + 8, wDetectDMA);
  __writegsdword(a1 + 4, wDetectIRQ);
  __writegsdword(a1 + 12, wDetectParam);
  if ((_sDETCaps_variable_1 & 1) != 0)
    return 0;
  if ((unsigned int)wDetectIRQ > 1 && (unsigned int)wDetectIRQ < 0x10)
    return 0;
  return 17;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIDetectVerifySettings(unsigned int a1, __int16 a2)
{
  int v5; // [esp+Ch] [ebp-1Ch]
  unsigned int v6; // [esp+1Ch] [ebp-Ch]
  unsigned int v7; // [esp+20h] [ebp-8h]
  unsigned int v8; // [esp+24h] [ebp-4h]

  if (!a1 && !a2)
    return 2;
  v8 = __readgsdword(a1);
  v6 = __readgsdword(a1 + 8);
  v7 = __readgsdword(a1 + 4);
  if ((_sDETCaps_variable_1 & 1) == 0 && (v7 < 2 || v7 > 0xF))
    return 17;
  sosDIGIInitForWindows(__readgsdword(a1 + 8));
  v5 = sosDetDRVVerifySettings(
         _lpDETDriverBufferCS,
         (unsigned __int16)_lpDETDriverBufferCS_variable_1,
         v8,
         v7,
         v6,
         _lpDETDriverBuffer,
         (unsigned __int16)_lpDETDriverBuffer_variable_1);
  sosDIGIUnInitForWindows(__readgsdword(a1 + 8));
  return v5;
}

//-------------------------------------------------------------------------------------------------

void sosDIGIDetec_End()
{
  ;
}

//-------------------------------------------------------------------------------------------------
#endif
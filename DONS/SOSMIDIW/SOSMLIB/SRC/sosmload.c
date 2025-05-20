/*
//-------------------------------------------------------------------------------------------------

void sosMIDILoad_Start()
{
  ;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDILoadDriver(
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
  unsigned int v13; // [esp+0h] [ebp-48h]
  unsigned int v14; // [esp+10h] [ebp-38h]
  unsigned __int16 v15; // [esp+14h] [ebp-34h]
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
  if (_wSOSMIDIDriverLoaded[a2])
    return 9;
  if (a1 < 0xA000 || a1 > 0xA200)
    return 6;
  strcpy(&_pSOSMIDITempDriverPath, &_pSOSMIDIDriverPath);
  strcat(&_pSOSMIDITempDriverPath, _szSOSMIDIDrvFile);
  v26 = open(&_pSOSMIDITempDriverPath, 512);
  if (v26 == -1)
    return 15;
  v9 = &_sSOSMIDIDRVFileHeader;
  read(v26, &_sSOSMIDIDRVFileHeader, v24);
  while (v21 <= _sSOSMIDIDRVFileHeader_variable_1 && !v22) {
    read(v26, &_sSOSMIDIDRVDriverHeader, v23);
    v25 = _sSOSMIDIDRVDriverHeader_variable_1;
    if (_sSOSMIDIDRVDriverHeader_variable_2 == a1) {
      v22 = 1;
      v10 = sosAllocateFarMem(v25 + 16, a7, &v19);
      v15 = WORD2(v10);
      v14 = v10;
      AliasCS = sosCreateAliasCS(v10, SWORD2(v10));
      v13 = AliasCS;
      sosDRVLockMemory(v19, v25);
      dos_read(v20);
      __writegsword(a3 + 4, WORD2(AliasCS));
      __writegsdword(a3, v13);
      __writegsword(a5 + 4, v15);
      __writegsdword(a5, v14);
      *a8 = v25;
      v9 = a9;
      *a9 = v19;
    } else {
      v9 = (_DWORD *)v25;
      lseek(v26, v25, 1);
    }
    ++v21;
  }
  close(v26, v9);
  _wSOSMIDIDriverType[a2] = _sSOSMIDIDRVDriverHeader_variable_2;
  _wSOSMIDIDriverLoaded[a2] = 1;
  if (v22)
    return 0;
  else
    return 7;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIUnLoadDriver(unsigned int a1)
{
  if (a1 > 5)
    return 10;
  if (!_wSOSMIDIDriverLoaded[a1])
    return 10;
  _wSOSMIDIDriverLoaded[a1] = 0;
  sosDRVUnLockMemory(_wSOSMIDIDriverLinear[a1], _wSOSMIDIDriverSize[a1]);
  sosFreeSelector(
    *(int *)((char *)&_lpSOSMIDIDriver + 6 * a1),
    (unsigned __int16)_lpSOSMIDIDriver_variable_1[3 * a1],
    _wSOSMIDIMemHandle[a1]);
  sosFreeSelector(
    *(int *)((char *)&_lpSOSMIDIDriverCS + 6 * a1),
    (unsigned __int16)_lpSOSMIDIDriverCS_variable_1[3 * a1],
    _wSOSMIDIMemHandle[a1]);
  return 0;
}

//-------------------------------------------------------------------------------------------------

void sosMIDILoad_End()
{
  ;
}

//-------------------------------------------------------------------------------------------------
*/
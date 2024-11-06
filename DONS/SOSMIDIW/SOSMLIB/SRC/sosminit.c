#ifdef ENABLE_SOSMLIB_PSEUDO
//-------------------------------------------------------------------------------------------------

void sosMIDIInit_Start()
{
  ;
}

//-------------------------------------------------------------------------------------------------

int sosMIDILockMemory()
{
  if (sosDRVLockMemory(sosMIDICaps_Start, (char *)sosMIDICaps_End - (char *)sosMIDICaps_Start))
    return 5;
  if (sosDRVLockMemory(sosMIDICbck_Start, (char *)sosMIDICbck_End - (char *)sosMIDICbck_Start))
    return 5;
  if (sosDRVLockMemory(&sosMIDIData_Start, &sosMIDIData_End - &sosMIDIData_Start))
    return 5;
  if (sosDRVLockMemory(sosMIDIDigi_Start, (char *)sosMIDIDigi_End - (char *)sosMIDIDigi_Start))
    return 5;
  if (sosDRVLockMemory(sosMIDIDone_Start, (char *)sosMIDIDone_End - (char *)sosMIDIDone_Start))
    return 5;
  if (sosDRVLockMemory(sosMIDIDq_Start, (char *)sosMIDIDq_End - (char *)sosMIDIDq_Start))
    return 5;
  if (sosDRVLockMemory(sosMIDIInit_Start, (char *)sosMIDIInit_End - (char *)sosMIDIInit_Start))
    return 5;
  if (sosDRVLockMemory(sosMIDIIns_Start, (char *)sosMIDIIns_End - (char *)sosMIDIIns_Start))
    return 5;
  if (sosDRVLockMemory(sosMIDILoad_Start, (char *)sosMIDILoad_End - (char *)sosMIDILoad_Start))
    return 5;
  if (sosDRVLockMemory(sosMIDIPause_Start, (char *)sosMIDIPause_End - (char *)sosMIDIPause_Start))
    return 5;
  if (sosDRVLockMemory(sosMIDIPtr_Start, (char *)sosMIDIPtr_End - (char *)sosMIDIPtr_Start))
    return 5;
  if (sosDRVLockMemory(sosMIDISong_Start, (char *)sosMIDISong_End - (char *)sosMIDISong_Start))
    return 5;
  if (sosDRVLockMemory(sosMIDISt_Start, (char *)sosMIDISt_End - (char *)sosMIDISt_Start))
    return 5;
  if (sosDRVLockMemory(sosMIDITmpo_Start, (char *)sosMIDITmpo_End - (char *)sosMIDITmpo_Start))
    return 5;
  if (sosDRVLockMemory(sosMIDITmr_Start, (char *)sosMIDITmr_End - (char *)sosMIDITmr_Start))
    return 5;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int sosMIDIUnLockMemory()
{
  if (sosDRVUnLockMemory(sosMIDICaps_Start, (char *)sosMIDICaps_End - (char *)sosMIDICaps_Start))
    return 5;
  if (sosDRVUnLockMemory(sosMIDICbck_Start, (char *)sosMIDICbck_End - (char *)sosMIDICbck_Start))
    return 5;
  if (sosDRVUnLockMemory(&sosMIDIData_Start, &sosMIDIData_End - &sosMIDIData_Start))
    return 5;
  if (sosDRVUnLockMemory(sosMIDIDigi_Start, (char *)sosMIDIDigi_End - (char *)sosMIDIDigi_Start))
    return 5;
  if (sosDRVUnLockMemory(sosMIDIDone_Start, (char *)sosMIDIDone_End - (char *)sosMIDIDone_Start))
    return 5;
  if (sosDRVUnLockMemory(sosMIDIDq_Start, (char *)sosMIDIDq_End - (char *)sosMIDIDq_Start))
    return 5;
  if (sosDRVUnLockMemory(sosMIDIInit_Start, (char *)sosMIDIInit_End - (char *)sosMIDIInit_Start))
    return 5;
  if (sosDRVUnLockMemory(sosMIDIIns_Start, (char *)sosMIDIIns_End - (char *)sosMIDIIns_Start))
    return 5;
  if (sosDRVUnLockMemory(sosMIDILoad_Start, (char *)sosMIDILoad_End - (char *)sosMIDILoad_Start))
    return 5;
  if (sosDRVUnLockMemory(sosMIDIPause_Start, (char *)sosMIDIPause_End - (char *)sosMIDIPause_Start))
    return 5;
  if (sosDRVUnLockMemory(sosMIDIPtr_Start, (char *)sosMIDIPtr_End - (char *)sosMIDIPtr_Start))
    return 5;
  if (sosDRVUnLockMemory(sosMIDISong_Start, (char *)sosMIDISong_End - (char *)sosMIDISong_Start))
    return 5;
  if (sosDRVUnLockMemory(sosMIDISt_Start, (char *)sosMIDISt_End - (char *)sosMIDISt_Start))
    return 5;
  if (sosDRVUnLockMemory(sosMIDITmpo_Start, (char *)sosMIDITmpo_End - (char *)sosMIDITmpo_Start))
    return 5;
  if (sosDRVUnLockMemory(sosMIDITmr_Start, (char *)sosMIDITmr_End - (char *)sosMIDITmr_Start))
    return 5;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIInitSystem(int a1, __int16 a2)
{
  int v5; // [esp+10h] [ebp-4h]

  v5 = sosMIDILockMemory();
  if (v5)
    return v5;
  if (a1 || a2)
    fstrcpy(&_pSOSMIDIDriverPath, __DS__, a1, a2);
  else
    _pSOSMIDIDriverPath = 0;
  _lpSOSMIDICBCKDrvFunctions_variable_1 = __CS__;
  _lpSOSMIDICBCKDrvFunctions = (int)callbackSendData;
  _lpSOSMIDICBCKDrvFunctions_variable_3 = __CS__;
  _lpSOSMIDICBCKDrvFunctions_variable_2 = (int)callbackInit;
  _lpSOSMIDICBCKDrvFunctions_variable_5 = __CS__;
  _lpSOSMIDICBCKDrvFunctions_variable_4 = (int)callbackUnInit;
  _lpSOSMIDICBCKDrvFunctions_variable_7 = __CS__;
  _lpSOSMIDICBCKDrvFunctions_variable_6 = (int)callbackReset;
  _lpSOSMIDICBCKDrvFunctions_variable_9 = __CS__;
  _lpSOSMIDICBCKDrvFunctions_variable_8 = (int)callbackSetInstrumentData;
  _lpMIDIDIGIDrvFunctions_variable_1 = __CS__;
  _lpMIDIDIGIDrvFunctions = (int)digiSendData;
  _lpMIDIDIGIDrvFunctions_variable_3 = __CS__;
  _lpMIDIDIGIDrvFunctions_variable_2 = (int)digiInit;
  _lpMIDIDIGIDrvFunctions_variable_5 = __CS__;
  _lpMIDIDIGIDrvFunctions_variable_4 = (int)digiUnInit;
  _lpMIDIDIGIDrvFunctions_variable_7 = __CS__;
  _lpMIDIDIGIDrvFunctions_variable_6 = (int)digiReset;
  _lpMIDIDIGIDrvFunctions_variable_9 = __CS__;
  _lpMIDIDIGIDrvFunctions_variable_8 = (int)digiSetInstrumentData;
  _lpMIDIWAVEDrvFunctions_variable_1 = __CS__;
  _lpMIDIWAVEDrvFunctions = (int)waveSendData;
  _lpMIDIWAVEDrvFunctions_variable_3 = __CS__;
  _lpMIDIWAVEDrvFunctions_variable_2 = (int)waveInit;
  _lpMIDIWAVEDrvFunctions_variable_5 = __CS__;
  _lpMIDIWAVEDrvFunctions_variable_4 = (int)waveUnInit;
  _lpMIDIWAVEDrvFunctions_variable_7 = __CS__;
  _lpMIDIWAVEDrvFunctions_variable_6 = (int)waveReset;
  _lpMIDIWAVEDrvFunctions_variable_9 = __CS__;
  _lpMIDIWAVEDrvFunctions_variable_8 = (int)waveSetInstrumentData;
  _wSOSMIDISysInititalized = 1;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int sosMIDIUnInitSystem()
{
  if (sosMIDIUnLockMemory())
    return 5;
  _wSOSMIDISysInititalized = 0;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIInitDriver(int a1, int a2, unsigned int a3, int a4, int a5, int a6, unsigned int a7, int a8)
{
  unsigned int v8; // eax
  int v9; // ecx
  unsigned int v10; // edx
  int v11; // eax
  unsigned int v12; // eax
  int v13; // ecx
  int v14; // eax
  unsigned int v15; // eax
  int v16; // ecx
  int v17; // eax
  unsigned __int16 v18; // ax
  unsigned int v19; // edx
  unsigned int v20; // edx
  unsigned int v21; // edx
  unsigned int v22; // edx
  unsigned int v24; // [esp+4h] [ebp-60h]
  int v25; // [esp+8h] [ebp-5Ch]
  unsigned __int16 v26; // [esp+Ch] [ebp-58h]
  int v27; // [esp+20h] [ebp-44h]
  int v28; // [esp+30h] [ebp-34h] BYREF
  int v29; // [esp+34h] [ebp-30h]
  int v30; // [esp+38h] [ebp-2Ch]
  int v31; // [esp+3Ch] [ebp-28h]
  unsigned int v33; // [esp+48h] [ebp-1Ch]
  unsigned int i; // [esp+50h] [ebp-14h]
  unsigned int v35; // [esp+5Ch] [ebp-8h]
  unsigned int v36; // [esp+60h] [ebp-4h]

  v30 = a1;
  v36 = __readgsdword(a5 + 28);
  v35 = __readgsdword(a5 + 32);
  v33 = 6;
  for (i = 0; i < 5; ++i) {
    if (!_wSOSMIDIDriverID[i]) {
      v33 = i;
      break;
    }
  }
  if (v33 == 6)
    return 11;
  _wSOSMIDIDriverID[v33] = v30;
  for (i = 0; i < 0x10; ++i)
    _bSOSMIDIDeviceChannelAvailable[16 * v33 + i] = *((_BYTE *)&off_A0000 + 16 * v30 + i - 573371);
  v24 = _wSOSMIDIDriverID[v33];
  if (v24 < 0xA005) {
    if (v24 == 40963) {
      callbackGetCallTable();
      for (i = 0; i < 0xC; ++i) {
        v12 = 72 * v33 + 6 * i;
        v13 = *(int *)((char *)&_lpSOSMIDICBCKDrvFunctions + 6 * i);
        *(_WORD *)&_lpSOSMIDIDrvFunction[v12 + 4] = _lpSOSMIDICBCKDrvFunctions_variable_1[3 * i];
        *(_DWORD *)&_lpSOSMIDIDrvFunction[v12] = v13;
      }
      v10 = 72 * v33;
      v14 = MK_FP(
              *(_WORD *)&_lpSOSMIDIDrvFunction_variable_2[v10 + 4],
              *(_DWORD *)&_lpSOSMIDIDrvFunction_variable_2[v10])(
              __readgsdword(a5 + 20),
              __readgsword(a5 + 24),
              v33,
              wFake);
      v31 = v14;
      if (v14)
        return v31;
      goto LABEL_46;
    }
  } else {
    if (v24 <= 0xA005) {
      digiGetCallTable();
      for (i = 0; i < 0xC; ++i) {
        v8 = 72 * v33 + 6 * i;
        v9 = *(int *)((char *)&_lpMIDIDIGIDrvFunctions + 6 * i);
        *(_WORD *)&_lpSOSMIDIDrvFunction[v8 + 4] = _lpMIDIDIGIDrvFunctions_variable_1[3 * i];
        *(_DWORD *)&_lpSOSMIDIDrvFunction[v8] = v9;
      }
      v10 = 72 * v33;
      v11 = MK_FP(
              *(_WORD *)&_lpSOSMIDIDrvFunction_variable_2[v10 + 4],
              *(_DWORD *)&_lpSOSMIDIDrvFunction_variable_2[v10])(
              __readgsdword(a5 + 20),
              __readgsword(a5 + 24),
              v33,
              wFake);
      v31 = v11;
      if (v11)
        return v31;
      goto LABEL_46;
    }
    if (v24 == 40967) {
      waveGetCallTable();
      for (i = 0; i < 0xC; ++i) {
        v15 = 72 * v33 + 6 * i;
        v16 = *(int *)((char *)&_lpMIDIWAVEDrvFunctions + 6 * i);
        *(_WORD *)&_lpSOSMIDIDrvFunction[v15 + 4] = _lpMIDIWAVEDrvFunctions_variable_1[3 * i];
        *(_DWORD *)&_lpSOSMIDIDrvFunction[v15] = v16;
      }
      v10 = 72 * v33;
      v17 = MK_FP(
              *(_WORD *)&_lpSOSMIDIDrvFunction_variable_2[v10 + 4],
              *(_DWORD *)&_lpSOSMIDIDrvFunction_variable_2[v10])(
              __readgsdword(a5 + 20),
              __readgsword(a5 + 24),
              v33,
              wFake);
      v31 = v17;
      if (v17)
        return v31;
      goto LABEL_46;
    }
  }
  lpFake_variable_1 = 0;
  lpFake = 0;
  v18 = __readgsword(a5 + 8);
  if (!__readgsdword(a5 + 4) && v18 == lpFake_variable_1) {
    v31 = sosMIDILoadDriver(
            (char)&v28,
            (unsigned __int16)__SS__,
            &_wSOSMIDIMemHandle[v33],
            &_wSOSMIDIDriverSize[v33],
            &_wSOSMIDIDriverLinear[v33]);
    if (v31)
      return v31;
    __writegsword(a5 + 8, v29);
    __writegsdword(a5 + 4, v28);
    __writegsword(a5 + 16, v26);
    __writegsdword(a5 + 12, v25);
    v21 = 3 * v33;
    _lpSOSMIDIDriver_variable_1[v21] = v29;
    *(int *)((char *)&_lpSOSMIDIDriver + v21 * 2) = v28;
    v22 = 3 * v33;
    _lpSOSMIDIDriverCS_variable_1[v22] = v26;
    *(int *)((char *)&_lpSOSMIDIDriverCS + v22 * 2) = v25;
  } else {
    LOWORD(v29) = __readgsword(a5 + 8);
    v28 = __readgsdword(a5 + 4);
    v26 = __readgsword(a5 + 16);
    v25 = __readgsdword(a5 + 12);
    v19 = 3 * v33;
    _lpSOSMIDIDriver_variable_1[v19] = v29;
    *(int *)((char *)&_lpSOSMIDIDriver + v19 * 2) = v28;
    v20 = 3 * v33;
    _lpSOSMIDIDriverCS_variable_1[v20] = v26;
    *(int *)((char *)&_lpSOSMIDIDriverCS + v20 * 2) = v25;
  }
  sosMIDIGetDeviceCaps(v33, (char *)&_lpSOSMIDIDriverCaps + 6 * v33, (char *)&_lpSOSMIDIDriverCaps + 6 * v33, __DS__);
  sosMIDIDRVGetFuncsPtr(
    v25,
    v26,
    v28,
    (unsigned __int16)v29,
    &_lpSOSMIDIDrvFunction[72 * v33],
    (unsigned __int16)__DS__);
  _wSOSMIDIDriverLoaded[v33] = 1;
  __writegsdword(a7, v33);
  v10 = __readgsdword(a3 + 8);
  v31 = MK_FP(
          *(_WORD *)&_lpSOSMIDIDrvFunction_variable_2[72 * v33 + 4],
          *(_DWORD *)&_lpSOSMIDIDrvFunction_variable_2[72 * v33])(
          v10,
          (unsigned __int16)__DS__,
          __readgsdword(a3 + 4),
          __readgsdword(a3));
  if (v31)
    return v31;
LABEL_46:
  if (_wSOSMIDIDriverID[v33] == 40970) {
    v27 = sosMIDIDRVSpecialFunction(v25, v26, v28, (unsigned __int16)v29, 2);
    sosTIMERRegisterEvent(0x78u, v27, v27, v10, (unsigned int)&_wSOSGravisTimerHandle, (unsigned __int16)__DS__);
  }
  _wSOSMIDIDriverLoaded[v33] = 1;
  __writegsdword(a7, v33);
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIUnInitDriver(int a1, int a2)
{
  int v2; // edx
  int v3; // eax
  int v4; // eax
  unsigned int v6; // [esp+4h] [ebp-18h]

  if (!_wSOSMIDIDriverLoaded[a1])
    return 1;
  v2 = (unsigned __int16)lpFake_variable_1;
  MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction_variable_3[72 * a1 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction_variable_3[72 * a1])(
    lpFake,
    (unsigned __int16)lpFake_variable_1,
    a1,
    wFake);
  if (a2) {
    v6 = _wSOSMIDIDriverID[a1];
    if (v6 < 0xA005) {
      if (v6 == 40963)
        goto LABEL_11;
    } else if (v6 <= 0xA005 || v6 == 40967) {
      goto LABEL_11;
    }
    sosMIDIUnLoadDriver(a1);
  }
LABEL_11:
  if (_wSOSMIDIDriverID[a1] == 40970)
    sosTIMERRemoveEvent(_wSOSGravisTimerHandle, v2);
  v3 = 3 * a1;
  _lpSOSMIDIDriver_variable_1[v3] = 0;
  *(int *)((char *)&_lpSOSMIDIDriver + v3 * 2) = 0;
  v4 = 3 * a1;
  _lpSOSMIDIDriverCS_variable_1[v4] = 0;
  *(int *)((char *)&_lpSOSMIDIDriverCS + v4 * 2) = 0;
  _wSOSMIDIDriverID[a1] = 0;
  _wSOSMIDIDriverLoaded[a1] = 0;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIResetDriver(int a1)
{
  unsigned int i; // [esp+Ch] [ebp-4h]

  for (i = 0; i < 0x10; ++i) {
    _bSOSMIDIData = i | 0xB0;
    _bSOSMIDIData_variable_1 = 121;
    _bSOSMIDIData_variable_2 = 0;
    MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * a1 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * a1])(
      &_bSOSMIDIData,
      (unsigned __int16)__DS__,
      3,
      a1);
    _bSOSMIDIData = i | 0xB0;
    _bSOSMIDIData_variable_1 = 123;
    _bSOSMIDIData_variable_2 = 0;
    MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * a1 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * a1])(
      &_bSOSMIDIData,
      (unsigned __int16)__DS__,
      3,
      a1);
  }
  MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction_variable_4[72 * a1 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction_variable_4[72 * a1])(
    lpFake,
    (unsigned __int16)lpFake_variable_1,
    a1,
    wFake);
  return 0;
}

//-------------------------------------------------------------------------------------------------

void sosMIDIInit_End()
{
  ;
}

//-------------------------------------------------------------------------------------------------
#endif
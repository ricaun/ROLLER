
//-------------------------------------------------------------------------------------------------

void sosDIGIInit_Start()
{
  ;
}

//-------------------------------------------------------------------------------------------------

int sosDIGILockMemory()
{
  if (sosDRVLockMemory(sosDIGIErr_Start, (char *)sosDIGIErr_End - (char *)sosDIGIErr_Start))
    return 5;
  if (sosDRVLockMemory(sosDIGICaps_Start, (char *)sosDIGICaps_End - (char *)sosDIGICaps_Start))
    return 5;
  if (sosDRVLockMemory(sosDIGIDone_Start, (char *)sosDIGIDone_End - (char *)sosDIGIDone_Start))
    return 5;
  if (sosDRVLockMemory(sosDIGIInit_Start, (char *)sosDIGIInit_End - (char *)sosDIGIInit_Start))
    return 5;
  if (sosDRVLockMemory(sosDIGILoad_Start, (char *)sosDIGILoad_End - (char *)sosDIGILoad_Start))
    return 5;
  if (sosDRVLockMemory(sosDIGIPlyng_Start, (char *)sosDIGIPlyng_End - (char *)sosDIGIPlyng_Start))
    return 5;
  if (sosDRVLockMemory(sosDIGIRate_Start, (char *)sosDIGIRate_End - (char *)sosDIGIRate_Start))
    return 5;
  if (sosDRVLockMemory(sosDIGIStart_Start, (char *)sosDIGIStart_End - (char *)sosDIGIStart_Start))
    return 5;
  if (sosDRVLockMemory(sosDIGITmr_Start, (char *)sosDIGITmr_End - (char *)sosDIGITmr_Start))
    return 5;
  if (sosDRVLockMemory(sosDIGICntl_Start, (char *)sosDIGICntl_End - (char *)sosDIGICntl_Start))
    return 5;
  if (sosDRVLockMemory(sosDIGIDetec_Start, (char *)sosDIGIDetec_End - (char *)sosDIGIDetec_Start))
    return 5;
  if (sosDRVLockMemory(sosDIGITimer_Start, (char *)sosDIGITimer_End - (char *)sosDIGITimer_Start))
    return 5;
  if (sosDRVLockMemory(sosDIGIDrv_Start, (char *)sosDIGIDrv_End - (char *)sosDIGIDrv_Start))
    return 5;
  if (sosDRVLockMemory(&_sosDIGIData_Start, &_sosDIGIData_End - &_sosDIGIData_Start))
    return 5;
  if (sosDRVLockMemory(&_sosDIGIData1_Start, &_sosDIGIData1_End - &_sosDIGIData1_Start))
    return 5;
  if (sosDRVLockMemory(&_sosDIGIData2_Start, &_sosDIGIData2_End - &_sosDIGIData2_Start))
    return 5;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int sosDIGIUnLockMemory()
{
  if (sosDRVUnLockMemory(sosDIGIErr_Start, (char *)sosDIGIErr_End - (char *)sosDIGIErr_Start))
    return 5;
  if (sosDRVUnLockMemory(sosDIGICaps_Start, (char *)sosDIGICaps_End - (char *)sosDIGICaps_Start))
    return 5;
  if (sosDRVUnLockMemory(sosDIGIDone_Start, (char *)sosDIGIDone_End - (char *)sosDIGIDone_Start))
    return 5;
  if (sosDRVUnLockMemory(sosDIGIInit_Start, (char *)sosDIGIInit_End - (char *)sosDIGIInit_Start))
    return 5;
  if (sosDRVUnLockMemory(sosDIGILoad_Start, (char *)sosDIGILoad_End - (char *)sosDIGILoad_Start))
    return 5;
  if (sosDRVUnLockMemory(sosDIGIPlyng_Start, (char *)sosDIGIPlyng_End - (char *)sosDIGIPlyng_Start))
    return 5;
  if (sosDRVUnLockMemory(sosDIGIRate_Start, (char *)sosDIGIRate_End - (char *)sosDIGIRate_Start))
    return 5;
  if (sosDRVUnLockMemory(sosDIGIStart_Start, (char *)sosDIGIStart_End - (char *)sosDIGIStart_Start))
    return 5;
  if (sosDRVUnLockMemory(sosDIGITmr_Start, (char *)sosDIGITmr_End - (char *)sosDIGITmr_Start))
    return 5;
  if (sosDRVUnLockMemory(sosDIGICntl_Start, (char *)sosDIGICntl_End - (char *)sosDIGICntl_Start))
    return 5;
  if (sosDRVUnLockMemory(sosDIGIDetec_Start, (char *)sosDIGIDetec_End - (char *)sosDIGIDetec_Start))
    return 5;
  if (sosDRVUnLockMemory(sosDIGITimer_Start, (char *)sosDIGITimer_End - (char *)sosDIGITimer_Start))
    return 5;
  if (sosDRVUnLockMemory(sosDIGIDrv_Start, (char *)sosDIGIDrv_End - (char *)sosDIGIDrv_Start))
    return 5;
  if (sosDRVUnLockMemory(&_sosDIGIData_Start, &_sosDIGIData_End - &_sosDIGIData_Start))
    return 5;
  if (sosDRVUnLockMemory(&_sosDIGIData1_Start, &_sosDIGIData1_End - &_sosDIGIData1_Start))
    return 5;
  if (sosDRVUnLockMemory(&_sosDIGIData2_Start, &_sosDIGIData2_End - &_sosDIGIData2_Start))
    return 5;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIInitSystem(int a1, __int16 a2)
{
  int v5; // [esp+10h] [ebp-4h]

  v5 = sosDIGILockMemory();
  if (v5)
    return v5;
  _wSOSSystemInitialized = 1;
  if (a1 || a2)
    fstrcpy(&_pSOSDriverPath, __DS__, a1, a2);
  else
    _pSOSDriverPath = 0;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int sosDIGIUnInitSystem()
{
  if (!sosDIGIUnLockMemory())
    _wSOSSystemInitialized = 0;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIInitDriver(
        int a1,
        int a2,
        unsigned int a3,
        int a4,
        unsigned int a5,
        int a6,
        unsigned int a7,
        int a8)
{
  unsigned int v8; // edx
  unsigned int v9; // edx
  unsigned int v10; // edx
  unsigned int v11; // edx
  __int64 v12; // rcx
  unsigned int v13; // edx
  unsigned int v14; // edx
  unsigned int v15; // edx
  unsigned int v16; // edx
  unsigned int v17; // eax
  int v18; // ebx
  unsigned int v19; // eax
  int v20; // ebx
  unsigned int v21; // eax
  unsigned int v22; // ebx
  unsigned int v23; // eax
  unsigned int v24; // ebx
  unsigned int v25; // eax
  unsigned int v26; // ebx
  unsigned int v27; // eax
  unsigned int v28; // ebx
  unsigned int v29; // eax
  unsigned int v30; // ebx
  unsigned int v31; // eax
  unsigned int v32; // ebx
  unsigned int v33; // eax
  unsigned int v34; // ebx
  int v37; // [esp+10h] [ebp-74h]
  unsigned __int16 v38; // [esp+14h] [ebp-70h]
  int v39; // [esp+18h] [ebp-6Ch] BYREF
  int v40; // [esp+1Ch] [ebp-68h]
  int v41; // [esp+20h] [ebp-64h]
  int v42; // [esp+24h] [ebp-60h]
  int v43; // [esp+28h] [ebp-5Ch] BYREF
  int v44; // [esp+2Ch] [ebp-58h]
  int v45; // [esp+30h] [ebp-54h]
  __int16 v46; // [esp+34h] [ebp-50h]
  int v47; // [esp+38h] [ebp-4Ch]
  int v48; // [esp+3Ch] [ebp-48h]
  unsigned int j; // [esp+40h] [ebp-44h]
  unsigned int v50; // [esp+44h] [ebp-40h]
  unsigned int v51; // [esp+48h] [ebp-3Ch] BYREF
  unsigned int v52; // [esp+4Ch] [ebp-38h]
  int v53; // [esp+50h] [ebp-34h]
  int v54; // [esp+54h] [ebp-30h]
  unsigned int v55; // [esp+58h] [ebp-2Ch]
  unsigned int i; // [esp+5Ch] [ebp-28h]
  unsigned int v58; // [esp+64h] [ebp-20h]
  unsigned int v59; // [esp+68h] [ebp-1Ch]
  unsigned int v60; // [esp+6Ch] [ebp-18h]
  unsigned int v61; // [esp+70h] [ebp-14h]
  unsigned int v62; // [esp+74h] [ebp-10h]
  unsigned int v63; // [esp+78h] [ebp-Ch]
  unsigned int v64; // [esp+7Ch] [ebp-8h]
  unsigned int v65; // [esp+80h] [ebp-4h]

  v53 = a1;
  v65 = __readgsdword(a5);
  v64 = __readgsdword(a5 + 16);
  LOWORD(v48) = __readgsword(a5 + 8);
  v47 = __readgsdword(a5 + 4);
  v62 = __readgsdword(a5 + 12);
  v61 = v64;
  v60 = __readgsdword(a5 + 20);
  v59 = __readgsdword(a5 + 24);
  v55 = 6;
  for (i = 0; i < 5; ++i) {
    if (!_wSOSDriverID[i]) {
      v55 = i;
      break;
    }
  }
  if (v55 == 6)
    return 11;
  _wSOSDriverID[v55] = v53;
  if (__readgsdword(a5 + 36) || __readgsword(a5 + 40)) {
    LOWORD(v44) = __readgsword(a5 + 40);
    v43 = __readgsdword(a5 + 36);
    LOWORD(v42) = __readgsword(a5 + 48);
    v41 = __readgsdword(a5 + 44);
    v8 = 3 * v55;
    _lpSOSDriver_variable_1[v8] = v44;
    *(int *)((char *)&_lpSOSDriver + v8 * 2) = v43;
    v9 = 3 * v55;
    _lpSOSDriverCS_variable_1[v9] = v42;
    *(int *)((char *)&_lpSOSDriverCS + v9 * 2) = v41;
  } else {
    v54 = sosDIGILoadDriver(
            (char)&v43,
            (unsigned __int16)__SS__,
            &_wSOSDriverMemHandle[v55],
            &_wSOSDriverSize[v55],
            &_wSOSDriverLinear[v55]);
    if (v54)
      return v54;
    __writegsword(a5 + 40, v44);
    __writegsdword(a5 + 36, v43);
    __writegsword(a5 + 48, v42);
    __writegsdword(a5 + 44, v41);
    v10 = 3 * v55;
    _lpSOSDriver_variable_1[v10] = v44;
    *(int *)((char *)&_lpSOSDriver + v10 * 2) = v43;
    v11 = 3 * v55;
    _lpSOSDriverCS_variable_1[v11] = v42;
    *(int *)((char *)&_lpSOSDriverCS + v11 * 2) = v41;
  }
  v54 = sosDIGIGetDeviceCaps(v55, (char *)&_sSOSDriverCaps + 108 * v55, (char *)&_sSOSDriverCaps + 108 * v55, __DS__);
  if (!v54) {
    if ((unsigned int)_wSOSDriverID[v55] >= 0xE106) {
      v21 = 3 * v55;
      _lpSOSFillHandler_variable_1[v21] = 0;
      *(int *)((char *)&_lpSOSFillHandler + v21 * 2) = 0;
    } else {
      _wSOSDMABuffersize[v55] = v65;
      if (v62) {
        _wSOSBufferAllocated[v55] = 1;
        v12 = sosDIGIAllocateBuffer(v65, &v51, &_wSOSRealSeg[v55]);
        LOWORD(v48) = WORD2(v12);
        v47 = v12;
        if (!(_DWORD)v12 && !(_WORD)v48) {
          sosDIGIUnLoadDriver(v55);
          _wSOSDriverID[v55] = 0;
          return 5;
        }
        v13 = 3 * v55;
        _lpSOSDMABuffer_variable_1[v13] = v48;
        *(int *)((char *)&_lpSOSDMABuffer + v13 * 2) = v47;
        if (_sSOSDriverCaps_variable_1[27 * v55] == 8) {
          if (_sSOSDriverCaps_variable_2[108 * v55] >= 0) {
            for (j = 0; j < v65; ++j)
              __writegsbyte(j + v47, 0x80u);
          } else {
            for (j = 0; j < v65; ++j)
              __writegsbyte(j + v47, 0);
          }
        } else {
          for (j = 0; j < v65; ++j)
            __writegsbyte(j + v47, 0);
        }
      } else {
        v14 = 3 * v55;
        _lpSOSDMABuffer_variable_1[v14] = v48;
        *(int *)((char *)&_lpSOSDMABuffer + v14 * 2) = v47;
        v51 = __readgsdword(a5 + 72);
      }
      __writegsword(a5 + 8, v48);
      __writegsdword(a5 + 4, v47);
      __writegsdword(a5 + 72, v51);
      if (__readgsdword(a5 + 52) || __readgsword(a5 + 56)) {
        LOWORD(v40) = __readgsword(a5 + 56);
        v39 = __readgsdword(a5 + 52);
        v38 = __readgsword(a5 + 64);
        v37 = __readgsdword(a5 + 60);
      } else if (__readgsdword(a5 + 68)) {
        v54 = sosDIGILoadTimer(
                (char)&v39,
                (unsigned __int16)__SS__,
                &_wSOSTimerMemHandle[v55],
                &_wSOSTimerSize[v55],
                &_wSOSTimerLinear[v55]);
        if (v54)
          return v54;
      } else {
        v54 = sosDIGILoadTimer(
                (char)&v39,
                (unsigned __int16)__SS__,
                &_wSOSTimerMemHandle[v55],
                &_wSOSTimerSize[v55],
                &_wSOSTimerLinear[v55]);
        if (v54)
          return v54;
      }
      if ((_sSOSDriverCaps_variable_2[108 * v55] & 2) != 0)
        sosDRVSetupCallFunctions(
          v37,
          v38,
          v39,
          (unsigned __int16)v40,
          v41,
          (unsigned __int16)v42,
          v43,
          (unsigned __int16)v44);
      __writegsword(a5 + 56, v40);
      __writegsdword(a5 + 52, v39);
      __writegsword(a5 + 64, v38);
      __writegsdword(a5 + 60, v37);
      v15 = 3 * v55;
      _lpSOSTimer_variable_1[v15] = v40;
      *(int *)((char *)&_lpSOSTimer + v15 * 2) = v39;
      v16 = 3 * v55;
      _lpSOSTimerCS_variable_1[v16] = v38;
      *(int *)((char *)&_lpSOSTimerCS + v16 * 2) = v37;
      _wSOSTimerLoaded[v55] = 1;
      v52 = __readgsdword(a3 + 8);
      v52 = _wSOSDMAPortList[v52];
      sosDRVGetFillInfo(v37, v38, v39, v40, v47, (unsigned __int16)v48, v65, v52, v55, &_sSOSFillInfo);
      v17 = 3 * v55;
      v18 = _sSOSFillInfo;
      _lpSOSFillHandler_variable_1[v17] = _sSOSFillInfo_variable_1;
      *(int *)((char *)&_lpSOSFillHandler + v17 * 2) = v18;
      v19 = 6 * v55;
      v20 = _sSOSFillInfo_variable_2;
      *(_WORD *)&_lpSOSDMAFillCount[v19 + 4] = _sSOSFillInfo_variable_3;
      *(_DWORD *)&_lpSOSDMAFillCount[v19] = v20;
      v46 = _sSOSFillInfo_variable_5;
      v45 = _sSOSFillInfo_variable_4;
      sosFillSampleStructs(
        &_lpSOSSampleList[192 * v55],
        _sSOSFillInfo_variable_4,
        (unsigned __int16)_sSOSFillInfo_variable_5);
    }
    v22 = *(int *)((char *)&_lpSOSFillHandler + 6 * v55);
    __writegsword(a5 + 32, _lpSOSFillHandler_variable_1[3 * v55]);
    __writegsdword(a5 + 28, v22);
    sosDIGIInitForWindows(__readgsdword(a3 + 8));
    _dwSOSDMABufferPhysical[v55] = v51;
    v50 = __readgsdword(a3);
    v63 = __readgsdword(a3 + 4);
    v52 = __readgsdword(a3 + 8);
    v58 = __readgsdword(a3 + 12);
    _bSOSDMAChannel[v55] = v52;
    sosDRVInit(v41, (unsigned __int16)v42, v43, (unsigned __int16)v44, v50, v63, v52, v60, v59, v58);
    sosDRVSetAction(v41, (unsigned __int16)v42, v43, (unsigned __int16)v44);
    sosDRVSetRate(v41, (unsigned __int16)v42, v43, (unsigned __int16)v44, v61);
    v51 = _dwSOSDMABufferPhysical[v55];
    sosDRVStart(v41, (unsigned __int16)v42, v43, (unsigned __int16)v44, v51, v65);
    _wSOSDriverLoaded[v55] = 1;
    _wSOSDriverInitialized[v55] = 1;
    _sSOSDIGIInitDriver[19 * v55] = __readgsdword(a5);
    v23 = 76 * v55;
    v24 = __readgsdword(a5 + 4);
    _sSOSDIGIInitDriver_variable_2[v23 / 2] = __readgsword(a5 + 8);
    _sSOSDIGIInitDriver_variable_1[v23 / 4] = v24;
    _sSOSDIGIInitDriver_variable_3[19 * v55] = __readgsdword(a5 + 12);
    _sSOSDIGIInitDriver_variable_4[19 * v55] = __readgsdword(a5 + 16);
    _sSOSDIGIInitDriver_variable_5[19 * v55] = v53;
    _sSOSDIGIInitDriver_variable_6[19 * v55] = __readgsdword(a5 + 24);
    v25 = 76 * v55;
    v26 = __readgsdword(a5 + 28);
    _sSOSDIGIInitDriver_variable_8[v25 / 2] = __readgsword(a5 + 32);
    _sSOSDIGIInitDriver_variable_7[v25 / 4] = v26;
    v27 = 76 * v55;
    v28 = __readgsdword(a5 + 36);
    _sSOSDIGIInitDriver_variable_10[v27 / 2] = __readgsword(a5 + 40);
    _sSOSDIGIInitDriver_variable_9[v27 / 4] = v28;
    v29 = 76 * v55;
    v30 = __readgsdword(a5 + 52);
    _sSOSDIGIInitDriver_variable_14[v29 / 2] = __readgsword(a5 + 56);
    _sSOSDIGIInitDriver_variable_13[v29 / 4] = v30;
    v31 = 76 * v55;
    v32 = __readgsdword(a5 + 44);
    _sSOSDIGIInitDriver_variable_12[v31 / 2] = __readgsword(a5 + 48);
    _sSOSDIGIInitDriver_variable_11[v31 / 4] = v32;
    v33 = 76 * v55;
    v34 = __readgsdword(a5 + 60);
    _sSOSDIGIInitDriver_variable_16[v33 / 2] = __readgsword(a5 + 64);
    _sSOSDIGIInitDriver_variable_15[v33 / 4] = v34;
    _sSOSDIGIInitDriver_variable_17[19 * v55] = __readgsdword(a5 + 68);
    __writegsdword(a7, v55);
    return 0;
  }
  return v54;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIUnInitDriver(int a1, int a2, int a3)
{
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v9; // [esp+0h] [ebp-28h]
  unsigned __int16 v10; // [esp+4h] [ebp-24h]
  unsigned __int16 v11; // [esp+Ch] [ebp-1Ch]
  int v12; // [esp+10h] [ebp-18h]
  unsigned __int16 v13; // [esp+14h] [ebp-14h]

  if (!_wSOSDriverLoaded[a1])
    return 1;
  _wSOSDriverInitialized[a1] = 0;
  if ((unsigned int)_wSOSDriverType[a1] < 0xE106 && _wSOSBufferAllocated[a1] && a2) {
    v11 = _lpSOSDMABuffer_variable_1[3 * a1];
    if ((unsigned __int8)sosDRVIsWindowsActive() == 3)
      sosFreeVDSPage(v11, _wSOSRealSeg[a1], _dwSOSDMABufferPhysical[a1]);
    else
      sosRealFree(v11);
    _wSOSBufferAllocated[a1] = 0;
  }
  v10 = _lpSOSDriver_variable_1[3 * a1];
  v9 = *(int *)((char *)&_lpSOSDriver + 6 * a1);
  v13 = _lpSOSDriverCS_variable_1[3 * a1];
  v12 = *(int *)((char *)&_lpSOSDriverCS + 6 * a1);
  sosDRVStop(v12, v13, v9, v10);
  sosDRVUnInit(v12, v13, v9, v10);
  sosDIGIUnInitForWindows((unsigned __int8)_bSOSDMAChannel[a1]);
  if (a3) {
    sosDIGIUnLoadDriver(a1);
    sosDIGIUnLoadTimer(a1);
  }
  v3 = 3 * a1;
  _lpSOSDriver_variable_1[v3] = 0;
  *(int *)((char *)&_lpSOSDriver + v3 * 2) = 0;
  v4 = 3 * a1;
  _lpSOSDriverCS_variable_1[v4] = 0;
  *(int *)((char *)&_lpSOSDriverCS + v4 * 2) = 0;
  v5 = 3 * a1;
  _lpSOSFillHandler_variable_1[v5] = 0;
  *(int *)((char *)&_lpSOSFillHandler + v5 * 2) = 0;
  v6 = 3 * a1;
  _lpSOSTimer_variable_1[v6] = 0;
  *(int *)((char *)&_lpSOSTimer + v6 * 2) = 0;
  v7 = 3 * a1;
  _lpSOSTimerCS_variable_1[v7] = 0;
  *(int *)((char *)&_lpSOSTimerCS + v7 * 2) = 0;
  _wSOSDriverID[a1] = 0;
  _wSOSDriverLoaded[a1] = 0;
  return 0;
}

//-------------------------------------------------------------------------------------------------

__int64 __fastcall sosDIGIAllocateBuffer(unsigned int a1, _DWORD *a2, _DWORD *a3)
{
  __int64 v4; // [esp+0h] [ebp-30h]
  int v5; // [esp+8h] [ebp-28h] BYREF
  int v6; // [esp+Ch] [ebp-24h]
  _DWORD *v7; // [esp+10h] [ebp-20h]
  unsigned int v8; // [esp+14h] [ebp-1Ch]
  _DWORD *v9; // [esp+18h] [ebp-18h]
  int v10; // [esp+1Ch] [ebp-14h] BYREF
  int v11; // [esp+20h] [ebp-10h] BYREF
  int v12; // [esp+24h] [ebp-Ch] BYREF
  int v13; // [esp+2Ch] [ebp-4h] BYREF

  v8 = a1;
  v9 = a2;
  v7 = a3;
  v12 = 0;
  if ((unsigned __int8)sosDRVIsWindowsActive() == 3) {
    if (sosAllocVDSPage(&v5, &v11, &v10)) {
      WORD2(v4) = 0;
      LODWORD(v4) = 0;
    } else {
      *v9 = v10;
      *v7 = v11;
      WORD2(v4) = v6;
      LODWORD(v4) = v5;
    }
  } else {
    do {
      sosRealAlloc((v8 >> 4) + 4, &v13, &v12);
      *v9 = v13;
    } while ((unsigned __int16)v13 > 0xFFFF - v8);
    WORD2(v4) = v12;
    LODWORD(v4) = 0;
  }
  return v4;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosAllocVDSPage(int a1, _DWORD *a2, int *a3)
{
  int v6; // [esp+14h] [ebp-18h]
  int v7; // [esp+18h] [ebp-14h]
  int v8; // [esp+20h] [ebp-Ch] BYREF
  int v9; // [esp+28h] [ebp-4h] BYREF

  *(_WORD *)(a1 + 4) = 0;
  *(_DWORD *)a1 = 0;
  *a2 = 0;
  *a3 = 0;
  v9 = 0;
  if (sosDRVAllocVDSStruct(32, &v8, &v9))
    return 0;
  __writegsdword(0, 0x1000u);
  v6 = sosDRVVDSGetBuffer(v9);
  fmemcpy(16);
  sosDRVFreeVDSStruct(v8);
  if (v6)
    return 5;
  LOWORD(_sSOSVDSInfo_variable_1) = _sSOSVDSInfo_variable_1 & 0xF000;
  v8 = sosDRVMakeDMASelector(_sSOSVDSInfo_variable_1);
  v7 = _sSOSVDSInfo_variable_1;
  *(_WORD *)(a1 + 4) = v8;
  *(_DWORD *)a1 = 0;
  *a3 = v7;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosFreeVDSPage(__int16 a1, int a2, int a3)
{
  int v4; // [esp+10h] [ebp-Ch] BYREF
  _DWORD v5[2]; // [esp+14h] [ebp-8h] BYREF

  v5[1] = a3;
  sosDRVFreeDMASelector(a1);
  sosDRVAllocVDSStruct(32, v5, &v4);
  fmemcpy(16);
  sosDRVVDSFreeBuffer(v4);
  return sosDRVFreeVDSStruct(v5[0]);
}

//-------------------------------------------------------------------------------------------------

void sosDIGIInit_End()
{
  ;
}

//-------------------------------------------------------------------------------------------------
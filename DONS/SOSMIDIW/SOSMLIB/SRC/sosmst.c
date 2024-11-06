
//-------------------------------------------------------------------------------------------------

void sosMIDISt_Start()
{
  ;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIHandleMIDIData(int a1, int a2, unsigned int a3, unsigned __int16 a4, int a5)
{
  unsigned __int8 v5; // al
  unsigned __int8 v7; // [esp+0h] [ebp-4Ch]
  unsigned __int8 v8; // [esp+4h] [ebp-48h]
  int v11; // [esp+28h] [ebp-24h]
  int v12; // [esp+30h] [ebp-1Ch]
  unsigned int k; // [esp+30h] [ebp-1Ch]
  unsigned int n; // [esp+30h] [ebp-1Ch]
  unsigned int ii; // [esp+30h] [ebp-1Ch]
  unsigned int j; // [esp+34h] [ebp-18h]
  unsigned int m; // [esp+34h] [ebp-18h]
  unsigned __int8 v18; // [esp+38h] [ebp-14h]
  unsigned __int8 v19; // [esp+3Ch] [ebp-10h]
  unsigned __int8 v20; // [esp+40h] [ebp-Ch]
  unsigned __int8 i; // [esp+44h] [ebp-8h]
  unsigned __int8 v22; // [esp+48h] [ebp-4h]

  v19 = 0;
  v18 = -1;
  v11 = -1;
  v20 = __readgsbyte(a3);
  v22 = v20 & 0xF;
  if (_wSOSMIDIChannelStealing) {
    for (i = _bSOSMIDIChannelRemap[128 * a2 + 16 * a1 + v22]; ; i = 9) {
    LABEL_12:
      if (i != 0xFF) {
        __writegsbyte(a3, v20 & 0xF0 | i);
        goto LABEL_69;
      }
      if (v22 != 9)
        break;
      _bSOSMIDIChannelRemap[128 * a2 + 9 + 16 * a1] = 9;
    }
    for (j = 0; j < 0x10; ++j) {
      while (!_bSOSMIDIDeviceChannelAvailable[16 * a2 + j] && j < 0x10)
        ++j;
      if (j < 0x10 && _bSOSMIDIOwnerChannel[16 * a2 + j] == -1) {
        _bSOSMIDIChannelRemap[128 * a2 + 16 * a1 + v22] = j;
        i = j;
        _bSOSMIDIOwnerChannel[16 * a2 + j] = v22;
        _bSOSMIDIOwnerSong[16 * a2 + j] = a1;
        _bSOSMIDIChannelPriority[16 * a2 + j] = __readgsbyte(*(_DWORD *)&_sSOSMIDISongHeader[6 * a1] + 4 * v22 + 64);
        v12 = (unsigned __int8)_bSOSMIDIChannelDataIndex[128 * a2 + 16 * a1 + v22];
        if (v12 == 255) {
          for (k = 0; k < 4; ++k) {
            if (_sSOSMIDIChannelData[320 * a2 + 20 * v22 + 5 * k] == -1) {
              _sSOSMIDIChannelData[320 * a2 + 20 * v22 + 5 * k] = 1;
              _bSOSMIDIChannelDataIndex[128 * a2 + 16 * a1 + v22] = k;
              goto LABEL_12;
            }
          }
        } else {
          _bSOSMIDIDeviceChannelVolume[16 * a2 + (unsigned __int8)j] = 127;
          _bSOSMIDIData = j | 0xB0;
          _bSOSMIDIData_variable_1 = 121;
          _bSOSMIDIData_variable_2 = 0;
          MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * a2 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * a2])(
            &_bSOSMIDIData,
            (unsigned __int16)__DS__,
            3,
            a2);
          if (_sSOSMIDIChannelData_variable_3[320 * a2 + 20 * v22 + 5 * v12] != -1) {
            _bSOSMIDIData = j | 0xC0;
            _bSOSMIDIData_variable_1 = _sSOSMIDIChannelData_variable_3[320 * a2 + 20 * v22 + 5 * v12];
            MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * a2 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * a2])(
              &_bSOSMIDIData,
              (unsigned __int16)__DS__,
              2,
              a2);
          }
          if (_sSOSMIDIChannelData_variable_1[320 * a2 + 20 * v22 + 5 * v12] != -1) {
            _bSOSMIDIData = j | 0xE0;
            _bSOSMIDIData_variable_1 = 0;
            _bSOSMIDIData_variable_2 = _sSOSMIDIChannelData_variable_1[320 * a2 + 20 * v22 + 5 * v12];
            MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * a2 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * a2])(
              &_bSOSMIDIData,
              (unsigned __int16)__DS__,
              2,
              a2);
          }
          if (_sSOSMIDIChannelData_variable_2[320 * a2 + 20 * v22 + 5 * v12] != -1) {
            _bSOSMIDIData = j | 0xB0;
            _bSOSMIDIData_variable_1 = 7;
            _bSOSMIDIData_variable_2 = _sSOSMIDIChannelData_variable_2[320 * a2 + 20 * v22 + 5 * v12];
            MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * a2 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * a2])(
              &_bSOSMIDIData,
              (unsigned __int16)__DS__,
              3,
              a2);
          }
          if (_sSOSMIDIChannelData_variable_4[320 * a2 + 20 * v22 + 5 * v12] != -1) {
            _bSOSMIDIData = j | 0xB0;
            _bSOSMIDIData_variable_1 = 64;
            _bSOSMIDIData_variable_2 = _sSOSMIDIChannelData_variable_4[320 * a2 + 20 * v22 + 5 * v12];
            MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * a2 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * a2])(
              &_bSOSMIDIData,
              (unsigned __int16)__DS__,
              3,
              a2);
          }
        }
        goto LABEL_12;
      }
    }
    for (m = 0; m < 0x10; ++m) {
      while (!_bSOSMIDIDeviceChannelAvailable[16 * a2 + m] && m < 0x10)
        ++m;
      if (m < 0x10
        && (unsigned __int8)_bSOSMIDIChannelPriority[16 * a2 + m] > v19
        && _bSOSMIDIChannelPriority[16 * a2 + m] != -1) {
        v19 = _bSOSMIDIChannelPriority[16 * a2 + m];
        v18 = m;
      }
    }
    if (v18 == 0xFF)
      goto LABEL_69;
    if (v19 > __readgsdword(*(_DWORD *)&_sSOSMIDISongHeader[6 * a1] + 4 * v22 + 64)) {
      _bSOSMIDIChannelRemap[128 * a2 + 16 * a1 + v22] = v18;
      _bSOSMIDIChannelRemap[128 * a2
        + 16 * (unsigned __int8)_bSOSMIDIOwnerSong[16 * a2 + v18]
        + (unsigned __int8)_bSOSMIDIOwnerChannel[16 * a2 + v18]] = -1;
      _bSOSMIDIOwnerChannel[16 * a2 + v18] = v22;
      _bSOSMIDIOwnerSong[16 * a2 + v18] = a1;
      i = v18;
      _bSOSMIDIChannelPriority[16 * a2 + v18] = __readgsbyte(*(_DWORD *)&_sSOSMIDISongHeader[6 * a1] + 4 * v22 + 64);
      _bSOSMIDIDeviceChannelVolume[16 * a2 + v18] = 127;
      _bSOSMIDIData = v18 | 0xB0;
      _bSOSMIDIData_variable_1 = 123;
      _bSOSMIDIData_variable_2 = 0;
      MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * a2 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * a2])(
        &_bSOSMIDIData,
        (unsigned __int16)__DS__,
        3,
        a2);
      _bSOSMIDIData = v18 | 0xB0;
      _bSOSMIDIData_variable_1 = 121;
      _bSOSMIDIData_variable_2 = 0;
      MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * a2 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * a2])(
        &_bSOSMIDIData,
        (unsigned __int16)__DS__,
        3,
        a2);
      if (_bSOSMIDIChannelDataIndex[128 * a2 + 16 * a1 + v22] == -1) {
        for (n = 0; n < 4; ++n) {
          if (_sSOSMIDIChannelData[320 * a2 + 20 * v22 + 5 * n] == -1) {
            _sSOSMIDIChannelData[320 * a2 + 20 * v22 + 5 * n] = 1;
            _bSOSMIDIChannelDataIndex[128 * a2 + 16 * a1 + v22] = n;
            goto LABEL_12;
          }
        }
      }
      goto LABEL_12;
    }
    if (_bSOSMIDIChannelDataIndex[128 * a2 + 16 * a1 + v22] == -1) {
      for (ii = 0; ii < 4; ++ii) {
        if (_sSOSMIDIChannelData[320 * a2 + 20 * v22 + 5 * ii] == -1) {
          _sSOSMIDIChannelData[320 * a2 + 20 * v22 + 5 * ii] = 1;
          _bSOSMIDIChannelDataIndex[128 * a2 + 16 * a1 + v22] = ii;
          break;
        }
      }
    }
  LABEL_69:
    if (v22 == 9) {
      if (v20 == 0xB9 && __readgsbyte(a3 + 1) == 7) {
        v5 = __readgsbyte(a3 + 2);
        v11 = v5;
        _bSOSMIDIDeviceChannelVolume_variable_1[16 * a2] = v5;
      }
    } else {
      v7 = v20 & 0xF0;
      if ((v20 & 0xF0u) < 0xC0) {
        if (v7 == 0xB0) {
          v8 = __readgsbyte(a3 + 1);
          if (v8 >= 7u) {
            if (v8 <= 7u) {
              _sSOSMIDIChannelData_variable_2[320 * a2
                + 20 * v22
                + 5 * (unsigned __int8)_bSOSMIDIChannelDataIndex[128 * a2 + 16 * a1 + v22]] = __readgsbyte(a3 + 2);
              v11 = __readgsbyte(a3 + 2);
              _bSOSMIDIDeviceChannelVolume[16 * a2 + i] = v11;
            } else if (v8 == 64) {
              _sSOSMIDIChannelData_variable_4[320 * a2
                + 20 * v22
                + 5 * (unsigned __int8)_bSOSMIDIChannelDataIndex[128 * a2 + 16 * a1 + v22]] = __readgsbyte(a3 + 2);
            }
          }
        }
      } else if (v7 <= 0xC0u) {
        _sSOSMIDIChannelData_variable_3[320 * a2
          + 20 * v22
          + 5 * (unsigned __int8)_bSOSMIDIChannelDataIndex[128 * a2 + 16 * a1 + v22]] = __readgsbyte(a3 + 1);
      } else if (v7 == 0xE0) {
        _sSOSMIDIChannelData_variable_1[320 * a2
          + 20 * v22
          + 5 * (unsigned __int8)_bSOSMIDIChannelDataIndex[128 * a2 + 16 * a1 + v22]] = __readgsbyte(a3 + 2);
      }
    }
    if (i == 0xFF) {
      return -1;
    } else {
      if (v11 != -1) {
        if (_wSOSMIDISongMuted[a1])
          __writegsbyte(a3 + 2, 0);
        else
          __writegsbyte(
            a3 + 2,
            (((unsigned int)(_wSOSMIDISongVolume[a1] * v11) >> 7) * (unsigned __int8)_bSOSMIDIMasterVolume) >> 7);
      }
      MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * a2 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * a2])(a3, a4, a5, a2);
      __writegsbyte(a3, v20);
      if (v11 != -1)
        __writegsbyte(a3 + 2, v11);
      return 0;
    }
  } else {
    if ((__readgsbyte(a3) & 0xF0) == 0xB0) {
      if (__readgsbyte(a3 + 1) == 7) {
        _bSOSMIDIData = __readgsbyte(a3);
        _bSOSMIDIData_variable_1 = 7;
        _bSOSMIDIData_variable_2 = ((((unsigned int)__readgsbyte(a3 + 2) * _wSOSMIDISongVolume[a1]) >> 7)
                                  * (unsigned __int8)_bSOSMIDIMasterVolume) >> 7;
        _bSOSMIDIDeviceChannelVolume[16 * a2 + v22] = __readgsbyte(a3 + 2);
        if (_wSOSMIDISongMuted[a1])
          _bSOSMIDIData_variable_2 = 0;
      } else {
        _bSOSMIDIData = __readgsbyte(a3);
        _bSOSMIDIData_variable_1 = __readgsbyte(a3 + 1);
        _bSOSMIDIData_variable_2 = __readgsbyte(a3 + 2);
        _bSOSMIDIData_variable_3 = __readgsbyte(a3 + 3);
      }
      MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * a2 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * a2])(
        &_bSOSMIDIData,
        (unsigned __int16)__DS__,
        a5,
        a2);
    } else {
      MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * a2 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * a2])(a3, a4, a5, a2);
    }
    return 1;
  }
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIResetChannelStealing(int a1)
{
  unsigned int i; // [esp+10h] [ebp-14h]
  unsigned int v4; // [esp+14h] [ebp-10h]
  unsigned __int8 v5; // [esp+18h] [ebp-Ch]
  unsigned __int8 v6; // [esp+1Ch] [ebp-8h]
  unsigned __int8 v7; // [esp+20h] [ebp-4h]

  for (i = 1; i < _wSOSMIDITotalTracks[a1]; ++i) {
    v4 = __readgsdword(*(int *)((char *)&_sSOSMIDITrackMap + 6 * a1) + 4 * i);
    if (v4 != -1 && v4 != 255) {
      v5 = __readgsbyte(*(int *)((char *)&_lpSOSMIDITrackHeaders[48 * a1] + 6 * i) + 8);
      if (_wSOSMIDIChannelStealing) {
        v7 = _bSOSMIDIChannelRemap[128 * v4 + 16 * a1 + v5];
        _bSOSMIDIChannelRemap[128 * v4 + 16 * a1 + v5] = -1;
        v6 = _bSOSMIDIChannelDataIndex[128 * v4 + 16 * a1 + v5];
        _bSOSMIDIOwnerChannel[16 * v4 + v7] = -1;
        _bSOSMIDIOwnerSong[16 * v4 + v7] = -1;
        _bSOSMIDIData = v7 | 0xB0;
        _bSOSMIDIData_variable_1 = 123;
        _bSOSMIDIData_variable_2 = 0;
        MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * v4 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * v4])(
          &_bSOSMIDIData,
          (unsigned __int16)__DS__,
          3,
          v4);
        _bSOSMIDIData = v7 | 0xB0;
        _bSOSMIDIData_variable_1 = 121;
        _bSOSMIDIData_variable_2 = 0;
        MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * v4 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * v4])(
          &_bSOSMIDIData,
          (unsigned __int16)__DS__,
          3,
          v4);
        _bSOSMIDIData = v7 | 0xE0;
        _bSOSMIDIData_variable_1 = 64;
        _bSOSMIDIData_variable_2 = 64;
        MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * v4 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * v4])(
          &_bSOSMIDIData,
          (unsigned __int16)__DS__,
          3,
          v4);
        _bSOSMIDIData = v7 | 0xB0;
        _bSOSMIDIData_variable_1 = 7;
        _bSOSMIDIData_variable_2 = 0;
        MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * v4 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * v4])(
          &_bSOSMIDIData,
          (unsigned __int16)__DS__,
          3,
          v4);
        if (v6 != 0xFF) {
          _sSOSMIDIChannelData_variable_3[320 * v4 + 20 * v5 + 5 * v6] = -1;
          _sSOSMIDIChannelData_variable_1[320 * v4 + 20 * v5 + 5 * v6] = -1;
          _sSOSMIDIChannelData_variable_2[320 * v4 + 20 * v5 + 5 * v6] = -1;
          _sSOSMIDIChannelData_variable_4[320 * v4 + 20 * v5 + 5 * v6] = -1;
          _sSOSMIDIChannelData[320 * v4 + 20 * v5 + 5 * v6] = -1;
          _bSOSMIDIChannelDataIndex[128 * v4 + 16 * a1 + v5] = -1;
        }
      } else {
        _bSOSMIDIData = v5 | 0xB0;
        _bSOSMIDIData_variable_1 = 123;
        _bSOSMIDIData_variable_2 = 0;
        MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * v4 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * v4])(
          &_bSOSMIDIData,
          (unsigned __int16)__DS__,
          3,
          v4);
        _bSOSMIDIData = v5 | 0xB0;
        _bSOSMIDIData_variable_1 = 121;
        _bSOSMIDIData_variable_2 = 0;
        MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * v4 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * v4])(
          &_bSOSMIDIData,
          (unsigned __int16)__DS__,
          3,
          v4);
        _bSOSMIDIData = v5 | 0xE0;
        _bSOSMIDIData_variable_1 = 64;
        _bSOSMIDIData_variable_2 = 64;
        MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * v4 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * v4])(
          &_bSOSMIDIData,
          (unsigned __int16)__DS__,
          3,
          v4);
        _bSOSMIDIData = v5 | 0xB0;
        _bSOSMIDIData_variable_1 = 7;
        _bSOSMIDIData_variable_2 = 0;
        MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * v4 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * v4])(
          &_bSOSMIDIData,
          (unsigned __int16)__DS__,
          3,
          v4);
      }
    }
  }
  return 1;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDISendMIDIData(int a1, int a2, int a3, unsigned __int16 a4)
{
  MK_FP(*(_WORD *)&_lpSOSMIDIDrvFunction[72 * a1 + 4], *(_DWORD *)&_lpSOSMIDIDrvFunction[72 * a1])(a3, a4, a2, a1);
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIEnableChannelStealing(int a1)
{
  int v2; // [esp+8h] [ebp-4h]

  v2 = _wSOSMIDIChannelStealing;
  _wSOSMIDIChannelStealing = a1;
  return v2;
}

//-------------------------------------------------------------------------------------------------

void sosMIDISt_End()
{
  ;
}

//-------------------------------------------------------------------------------------------------
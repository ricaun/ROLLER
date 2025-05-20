/*
//-------------------------------------------------------------------------------------------------

void sosMIDIDigi_Start()
{
  ;
}

//-------------------------------------------------------------------------------------------------

int *digiGetCallTable()
{
  return &_lpMIDIDIGIDrvFunctions;
}

//-------------------------------------------------------------------------------------------------

int __cdecl digiSendData(unsigned int a1, int a2, int a3, int a4)
{
  unsigned int v5; // [esp+0h] [ebp-2Ch]
  unsigned int v6; // [esp+4h] [ebp-28h]
  int v7; // [esp+4h] [ebp-28h]
  int v8; // [esp+Ch] [ebp-20h]
  unsigned int v9; // [esp+10h] [ebp-1Ch]
  unsigned __int8 v10; // [esp+14h] [ebp-18h]
  int v11; // [esp+18h] [ebp-14h]
  int i; // [esp+1Ch] [ebp-10h]
  int j; // [esp+1Ch] [ebp-10h]
  unsigned int v14; // [esp+28h] [ebp-4h]
  unsigned int Item; // [esp+28h] [ebp-4h]
  unsigned int v16; // [esp+28h] [ebp-4h]
  unsigned int v17; // [esp+28h] [ebp-4h]
  unsigned int v18; // [esp+28h] [ebp-4h]
  _BYTE retaddr[8]; // [esp+38h] [ebp+Ch]

  v10 = __readgsbyte(a1);
  v9 = __readgsbyte(a1 + 1);
  v8 = __readgsbyte(a1 + 2);
  v11 = v10 & 0xF;
  v5 = v10 & 0xF0;
  if (v5 < 0x90) {
    if (v5 == 128) {
      v7 = *(_DWORD *)&_sMIDIDIGIStartSample[768 * a4 + 6 * v9];
      if (v7) {
        if (__readgsdword(v7 + 36) != -32768) {
          v17 = digiQueueDeleteItemMIDI(a4, v9, v11);
          if (v17 != -1)
            sosDIGIStopSample(_wMIDIDIGIDriverHandle[a4], v17);
        }
      }
    }
  } else if (v5 <= 0x90) {
    v6 = *(_DWORD *)&_sMIDIDIGIStartSample[768 * a4 + 6 * v9];
    if (v6) {
      if (v8) {
        if (__readgsdword(v6 + 36) != -32768) {
          v14 = digiQueueDeleteItemMIDI(a4, v9, v11);
          if (v14 != -1)
            sosDIGIStopSample(_wMIDIDIGIDriverHandle[a4], v14);
        }
        if (_wMIDIDIGIUsedSamples[a4] >= (unsigned int)_wMIDIDIGIMaxSamples[a4]) {
          Item = digiQueueGetItem(a4, v11);
          if (Item != -1)
            sosDIGIStopSample(_wMIDIDIGIDriverHandle[a4], Item);
        }
        if (_wMIDIDIGIVelocitySensing[a4]) {
          __writegsdword(v6 + 20, (unsigned int)(v8 * _sMIDIDIGIChannel[3 * a4]) >> 7);
          __writegsdword(v6 + 20, __readgsdword(v6 + 20) << 8);
        }
        __writegsdword(v6 + 24, v9);
        if (SLOBYTE(_sMIDIDIGIChannel_variable_1[3 * a4]) >= 0)
          __writegsdword(v6 + 64, _sMIDIDIGIChannel_variable_1[3 * a4] << 9);
        if (sosDIGIStartSample(_wMIDIDIGIDriverHandle[a4], v6, v6) != -1)
          digiQueueAddItem(v11);
      } else if (__readgsdword(v6 + 36) != -32768) {
        v16 = digiQueueDeleteItemMIDI(a4, v9, v11);
        if (v16 != -1)
          sosDIGIStopSample(_wMIDIDIGIDriverHandle[a4], v16);
      }
    }
  } else if (v5 == 176) {
    if (v9 < 0xA) {
      if (v9 == 7) {
        _sMIDIDIGIChannel[3 * a4] = v8;
        for (i = _wMIDIDIGISampleQueueTail[a4]; i != _wMIDIDIGISampleQueueHead[a4]; i = ((_BYTE)i + 1) & 0x1F) {
          if (_sMIDIDIGIQueue[128 * a4 + 4 * i] != -1)
            sosDIGISetSampleVolume(
              _wMIDIDIGIDriverHandle[a4],
              _sMIDIDIGIQueue[128 * a4 + 4 * i],
              2 * LOWORD(_sMIDIDIGIQueue_variable_2[128 * a4 + 4 * i]) * v8);
        }
      }
    } else if (v9 <= 0xA) {
      _sMIDIDIGIChannel_variable_1[3 * a4] = v8;
      for (j = _wMIDIDIGISampleQueueTail[a4]; j != _wMIDIDIGISampleQueueHead[a4]; j = ((_BYTE)j + 1) & 0x1F)
        sosDIGISetPanLocation(_wMIDIDIGIDriverHandle[a4], _sMIDIDIGIQueue[128 * a4 + 4 * j], (_WORD)v8 << 9);
    } else if (v9 == 123) {
      while (1) {
        v18 = digiQueueGetItem(a4, v11);
        if (v18 == -1)
          break;
        sosDIGIStopSample(_wMIDIDIGIDriverHandle[a4], v18);
      }
    }
  }
  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(0);
}

//-------------------------------------------------------------------------------------------------

int __cdecl digiInit(unsigned int a1, int a2, int a3)
{
  int v3; // ebx
  int v4; // ecx
  unsigned int v5; // ebx
  unsigned int v7; // eax
  int v8; // ebx
  int v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+1Ch] [ebp-8h] BYREF
  unsigned int i; // [esp+20h] [ebp-4h]
  _BYTE retaddr[8]; // [esp+30h] [ebp+Ch]

  for (i = 0; i < 5; ++i) {
    if (_sSOSDIGIInitDriver_variable_5[19 * i] == __readgsdword(a1)) {
      _wMIDIDIGIDriverHandle[a3] = i;
      v10 = i;
      break;
    }
  }
  if (i == 5) {
    _wMIDIDIGIDriverInitMIDI[a3] = 1;
    HIWORD(v3) = HIWORD(a1);
    LOWORD(v3) = __readgsword(a1 + 32);
    v4 = v3;
    v5 = __readgsdword(a1 + 28);
    v9 = sosDIGIInitDriver(
           __readgsdword(a1),
           v5,
           v5,
           v4,
           __readgsdword(a1 + 20),
           __readgsword(a1 + 24),
           (unsigned int)&v10,
           (unsigned __int16)__SS__);
    if (v9)
      return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(v9);
    _wMIDIDIGIDriverHandle[a3] = v10;
    v7 = __readgsdword(a1 + 20);
    v8 = __readgsdword(v7 + 28);
    v9 = sosTIMERRegisterEvent(
           __readgsdword(a1 + 4),
           v8,
           v8,
           __readgsword(v7 + 32),
           (unsigned int)&_wMIDIDIGITimerEventHandle[a3],
           (unsigned __int16)__DS__);
    if (v9)
      return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(v9);
    _wMIDIDIGIDriverInitialized[a3] = 1;
  } else {
    _wMIDIDIGIDriverInitMIDI[a3] = 0;
  }
  _wMIDIDIGIVelocitySensing[a3] = __readgsdword(a1 + 16);
  digiQueueInit(a3, __readgsdword(a1 + 12));
  _wSOSDIGIMIDIHandle[v10] = a3;
  for (i = 0; i < 5; ++i)
    LOBYTE(_sMIDIDIGIChannel_variable_1[3 * i]) |= 0x80u;
  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(0);
}

//-------------------------------------------------------------------------------------------------

int __usercall digiUnInit@<eax>(int a1@<edx>, int a2, int a3, int a4)
{
  _BYTE retaddr[8]; // [esp+10h] [ebp+Ch]

  if (_wMIDIDIGIDriverInitialized[a4]) {
    _wMIDIDIGIDriverInitialized[a4] = 0;
    if (_wMIDIDIGIDriverInitMIDI[a4]) {
      sosTIMERRemoveEvent(_wMIDIDIGITimerEventHandle[a4], a1);
      a1 = 1;
      sosDIGIUnInitDriver(_wMIDIDIGIDriverHandle[a4], 1, 1);
    }
  }
  digiQueueUnInit(a4);
  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(0, a1);
}

//-------------------------------------------------------------------------------------------------

int __cdecl digiReset(int a1, int a2, int a3)
{
  _BYTE retaddr[8]; // [esp+10h] [ebp+Ch]

  digiQueueInit(a3, _wMIDIDIGIMaxSamples[a3]);
  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(0);
}

//-------------------------------------------------------------------------------------------------

int __cdecl digiSetInstrumentData(int a1, unsigned __int16 a2, int a3)
{
  int v3; // edx
  int v4; // eax
  int v6; // eax
  int v7; // eax
  int v8; // ebx
  int v9; // eax
  unsigned int v10; // eax
  unsigned int v11; // ebx
  unsigned int v12; // eax
  int v13; // eax
  unsigned int i; // [esp+4h] [ebp-Ch]
  unsigned int v15; // [esp+8h] [ebp-8h]
  int j; // [esp+Ch] [ebp-4h]
  unsigned int v17; // [esp+Ch] [ebp-4h]
  _BYTE retaddr[8]; // [esp+1Ch] [ebp+Ch]

  v3 = 6 * a3;
  *(_WORD *)&_sMIDIDIGIInsFileHeader[v3 + 4] = a2;
  *(_DWORD *)&_sMIDIDIGIInsFileHeader[v3] = a1;
  for (i = 0; i < 0x80; ++i) {
    v4 = 768 * a3 + 6 * i;
    *(_WORD *)&_sMIDIDIGIStartSample[v4 + 4] = 0;
    *(_DWORD *)&_sMIDIDIGIStartSample[v4] = 0;
  }
  for (j = 0; _szMIDIDIGIInsFileID[j]; ++j) {
    if (_szMIDIDIGIInsFileID[j] != __readgsbyte(j + a1))
      return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(14);
  }
  v17 = 40;
  do {
    sosMIDINormalizePtr();
    v15 = __readgsdword(v6 + 24);
    sosMIDINormalizePtr();
    v8 = v7;
    v9 = 6 * v15 + 768 * a3;
    *(_WORD *)&_sMIDIDIGIStartSample[v9 + 4] = a2;
    *(_DWORD *)&_sMIDIDIGIStartSample[v9] = v8;
    sosMIDINormalizePtr();
    v11 = v10;
    v12 = *(_DWORD *)&_sMIDIDIGIStartSample[768 * a3 + 6 * v15];
    __writegsword(v12 + 4, a2);
    __writegsdword(v12, v11);
    v13 = *(_DWORD *)&_sMIDIDIGIStartSample[768 * a3 + 6 * v15];
    __writegsword(v13 + 32, __CS__);
    __writegsdword(v13 + 28, (unsigned int)digiSampleCallback);
    v17 += __readgsdword(*(_DWORD *)&_sMIDIDIGIStartSample[768 * a3 + 6 * v15] + 8) + 116;
  } while (v17 < __readgsdword(*(_DWORD *)&_sMIDIDIGIInsFileHeader[6 * a3] + 36));
  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(0);
}

//-------------------------------------------------------------------------------------------------

int __cdecl digiSampleCallback(int a1, int a2, int a3)
{
  _BYTE retaddr[8]; // [esp+Ch] [ebp+Ch]

  if (a2 == 2)
    digiQueueDeleteItem(_wSOSDIGIMIDIHandle[a1], a3);
  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)();
}

//-------------------------------------------------------------------------------------------------

void sosMIDIDigi_End()
{
  ;
}

//-------------------------------------------------------------------------------------------------
*/

//-------------------------------------------------------------------------------------------------

void sosMIDIPause_Start()
{
  ;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIPauseSong(int a1, int a2)
{
  int v2; // eax
  int v5; // [esp+Ch] [ebp-10h]
  unsigned int i; // [esp+10h] [ebp-Ch]
  unsigned __int8 v7; // [esp+14h] [ebp-8h]
  unsigned __int8 v8; // [esp+18h] [ebp-4h]

  _wSOSMIDISongPaused[a1] = 1;
  if (a2) {
    _wSOSMIDISongMuted[a1] = 1;
    for (i = 0; i < 0x20; ++i) {
      v2 = 192 * a1 + 6 * i;
      if (*(_DWORD *)&_lpSOSMIDITrack[v2] || *(_WORD *)&_lpSOSMIDITrack[v2 + 4]) {
        v7 = __readgsbyte(*(int *)((char *)&_lpSOSMIDITrackHeaders[48 * a1] + 6 * i) + 8);
        v5 = __readgsdword(*(int *)((char *)&_sSOSMIDITrackMap + 6 * a1) + 4 * i);
        if (_wSOSMIDIChannelStealing)
          v8 = _bSOSMIDIChannelRemap[128 * v5 + 16 * a1 + v7];
        else
          v8 = v7;
        _bSOSMIDIData1 = v7 | 0xB0;
        _bSOSMIDIData1_variable_1 = 7;
        _bSOSMIDIData1_variable_2 = _bSOSMIDIDeviceChannelVolume[16 * v5 + v8];
        sosMIDIHandleMIDIData(a1, v5, (unsigned int)&_bSOSMIDIData1, __DS__, 3);
        _wSOSMIDIChannelMuted[16 * v5 + v8] = 1;
      }
    }
  }
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIResumeSong(int a1)
{
  int v1; // eax
  unsigned int i; // [esp+8h] [ebp-10h]
  int v5; // [esp+Ch] [ebp-Ch]
  unsigned __int8 v6; // [esp+10h] [ebp-8h]
  unsigned __int8 v7; // [esp+14h] [ebp-4h]

  _wSOSMIDISongPaused[a1] = 0;
  if (_wSOSMIDISongMuted[a1]) {
    _wSOSMIDISongMuted[a1] = 0;
    for (i = 0; i < 0x20; ++i) {
      v1 = 192 * a1 + 6 * i;
      if (*(_DWORD *)&_lpSOSMIDITrack[v1] || *(_WORD *)&_lpSOSMIDITrack[v1 + 4]) {
        v5 = __readgsdword(*(int *)((char *)&_sSOSMIDITrackMap + 6 * a1) + 4 * i);
        v6 = __readgsbyte(*(int *)((char *)&_lpSOSMIDITrackHeaders[48 * a1] + 6 * i) + 8);
        if (_wSOSMIDIChannelStealing)
          v7 = _bSOSMIDIChannelRemap[128 * v5 + 16 * a1 + v6];
        else
          v7 = v6;
        _bSOSMIDIData1 = v6 | 0xB0;
        _bSOSMIDIData1_variable_1 = 7;
        _bSOSMIDIData1_variable_2 = _bSOSMIDIDeviceChannelVolume[16 * v5 + v7];
        sosMIDIHandleMIDIData(a1, v5, (unsigned int)&_bSOSMIDIData1, __DS__, 3);
        _wSOSMIDIChannelMuted[16 * v5 + v7] = 0;
      }
    }
  }
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIMuteSong(int a1)
{
  int v1; // eax
  unsigned int i; // [esp+8h] [ebp-8h]

  for (i = 0; i < 0x20; ++i) {
    v1 = 192 * a1 + 6 * i;
    if (*(_DWORD *)&_lpSOSMIDITrack[v1] || *(_WORD *)&_lpSOSMIDITrack[v1 + 4]) {
      _bSOSMIDIData1 = __readgsbyte(*(int *)((char *)&_lpSOSMIDITrackHeaders[48 * a1] + 6 * i) + 8) | 0xB0;
      _bSOSMIDIData1_variable_1 = 7;
      _bSOSMIDIData1_variable_2 = 0;
      sosMIDIHandleMIDIData(
        a1,
        __readgsdword(*(int *)((char *)&_sSOSMIDITrackMap + 6 * a1) + 4 * i),
        (unsigned int)&_bSOSMIDIData1,
        __DS__,
        3);
    }
  }
  _wSOSMIDISongMuted[a1] = 1;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIUnMuteSong(int a1)
{
  int v1; // eax
  unsigned int i; // [esp+8h] [ebp-10h]
  int v5; // [esp+Ch] [ebp-Ch]
  unsigned __int8 v6; // [esp+10h] [ebp-8h]
  unsigned __int8 v7; // [esp+14h] [ebp-4h]

  _wSOSMIDISongMuted[a1] = 0;
  for (i = 0; i < 0x20; ++i) {
    v1 = 192 * a1 + 6 * i;
    if (*(_DWORD *)&_lpSOSMIDITrack[v1] || *(_WORD *)&_lpSOSMIDITrack[v1 + 4]) {
      v5 = __readgsdword(*(int *)((char *)&_sSOSMIDITrackMap + 6 * a1) + 4 * i);
      v6 = __readgsbyte(*(int *)((char *)&_lpSOSMIDITrackHeaders[48 * a1] + 6 * i) + 8);
      if (_wSOSMIDIChannelStealing)
        v7 = _bSOSMIDIChannelRemap[128 * v5 + 16 * a1 + v6];
      else
        v7 = v6;
      _bSOSMIDIData1 = v6 | 0xB0;
      _bSOSMIDIData1_variable_1 = 7;
      _bSOSMIDIData1_variable_2 = _bSOSMIDIDeviceChannelVolume[16 * v5 + v7];
      sosMIDIHandleMIDIData(a1, v5, (unsigned int)&_bSOSMIDIData1, __DS__, 3);
    }
  }
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDISetSongVolume(int a1, unsigned __int8 a2)
{
  int v2; // eax
  unsigned int v5; // [esp+4h] [ebp-18h]
  unsigned int i; // [esp+Ch] [ebp-10h]
  unsigned __int8 v7; // [esp+14h] [ebp-8h]
  unsigned __int8 v8; // [esp+18h] [ebp-4h]

  _wSOSMIDISongVolume[a1] = a2;
  for (i = 0; i < 0x20; ++i) {
    v2 = 192 * a1 + 6 * i;
    if (*(_DWORD *)&_lpSOSMIDITrack[v2] || *(_WORD *)&_lpSOSMIDITrack[v2 + 4]) {
      v7 = __readgsbyte(*(int *)((char *)&_lpSOSMIDITrackHeaders[48 * a1] + 6 * i) + 8);
      v5 = __readgsdword(*(int *)((char *)&_sSOSMIDITrackMap + 6 * a1) + 4 * i);
      if (_wSOSMIDIChannelStealing)
        v8 = _bSOSMIDIChannelRemap[128 * v5 + 16 * a1 + v7];
      else
        v8 = v7;
      _bSOSMIDIData1 = v7 | 0xB0;
      _bSOSMIDIData1_variable_1 = 7;
      _bSOSMIDIData1_variable_2 = _bSOSMIDIDeviceChannelVolume[16 * v5 + v8];
      sosMIDIHandleMIDIData(
        a1,
        __readgsdword(*(int *)((char *)&_sSOSMIDITrackMap + 6 * a1) + 4 * i),
        (unsigned int)&_bSOSMIDIData1,
        __DS__,
        3);
    }
  }
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIFadeSong(
        unsigned int a1,
        int a2,
        int a3,
        unsigned __int8 a4,
        unsigned __int8 a5,
        unsigned int a6)
{
  unsigned int v8; // [esp+Ch] [ebp-1Ch]
  unsigned int v9; // [esp+10h] [ebp-18h]
  int v10; // [esp+20h] [ebp-8h]

  if ((a2 & 1) != 0)
    v10 = a5 - a4;
  else
    v10 = a4 - a5;
  v8 = 0x640000u / sosTIMERGetEventRate(_wSOSMIDIEventHandle[a1]);
  v9 = (a3 << 16) / v8 / a6;
  if (v9) {
    sosMIDISetSongVolume(a1, a4);
    _wSOSMIDIVolumeFadeDirection[a1] = a2;
    _dwSOSMIDIVolumeFadeFraction[a1] = (v10 << 16) / v9;
    _dwSOSMIDIVolumeFadeVolume[a1] = a4 << 16;
    _wSOSMIDIVolumeFadeTicks[a1] = v9;
  } else if ((a2 & 4) != 0) {
    sosMIDIStopSong(a1, (a3 << 16) / v8 % a6);
  } else {
    sosMIDISetSongVolume(a1, a5);
  }
  return 0;
}

//-------------------------------------------------------------------------------------------------

void sosMIDIPause_End()
{
  ;
}

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------

void sosMIDISong_Start()
{
  ;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIInitSong(unsigned int a1, int a2, int a3, __int16 a4, unsigned int a5, int a6)
{
  int v6; // eax
  int v7; // eax
  __int64 v8; // rax
  int v9; // ecx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  __int64 v13; // rax
  unsigned int v14; // ebx
  __int64 v15; // rax
  int v16; // ecx
  __int64 v17; // rax
  int v18; // ecx
  int v19; // ecx
  int v20; // edx
  int v21; // eax
  int v22; // eax
  int v26; // [esp+18h] [ebp-4Ch]
  unsigned int v27; // [esp+20h] [ebp-44h]
  int v28; // [esp+20h] [ebp-44h]
  __int16 v29; // [esp+24h] [ebp-40h]
  unsigned int v30; // [esp+28h] [ebp-3Ch]
  int v31; // [esp+30h] [ebp-34h]
  __int16 v32; // [esp+34h] [ebp-30h]
  unsigned int jj; // [esp+3Ch] [ebp-28h]
  int i; // [esp+40h] [ebp-24h]
  unsigned int mm; // [esp+48h] [ebp-1Ch]
  unsigned int v37; // [esp+4Ch] [ebp-18h]
  unsigned int j; // [esp+50h] [ebp-14h]
  unsigned int nn; // [esp+50h] [ebp-14h]
  unsigned int i1; // [esp+50h] [ebp-14h]
  int v41; // [esp+58h] [ebp-Ch]
  int v42; // [esp+5Ch] [ebp-8h]
  unsigned int k; // [esp+60h] [ebp-4h]
  unsigned int m; // [esp+60h] [ebp-4h]
  unsigned int n; // [esp+60h] [ebp-4h]
  unsigned int ii; // [esp+60h] [ebp-4h]
  unsigned int kk; // [esp+60h] [ebp-4h]

  v42 = 0;
  for (i = 0; _szMIDIMIDIFileID[i]; ++i) {
    if (_szMIDIMIDIFileID[i] != __readgsbyte(__readgsdword(a1) + i))
      return 14;
  }
  for (j = 0; j < 8; ++j) {
    if (!*(_DWORD *)&_sSOSMIDISongHeader[6 * j] && !*(_WORD *)&_sSOSMIDISongHeader[6 * j + 4]) {
      v37 = j;
      break;
    }
  }
  if (j == 8)
    return 11;
  for (k = 0; k < 0x20; ++k) {
    v6 = 192 * j + 6 * k;
    *(_WORD *)&_lpSOSMIDITrack[v6 + 4] = 0;
    *(_DWORD *)&_lpSOSMIDITrack[v6] = 0;
  }
  HIWORD(v7) = HIWORD(a1);
  LOWORD(v7) = __readgsword(a1 + 4);
  v8 = sosMIDINormalizePtr(__readgsdword(a1), v7);
  v9 = v8;
  LODWORD(v8) = 6 * v37;
  *(_WORD *)&_sSOSMIDISongHeader[v8 + 4] = WORD2(v8);
  *(_DWORD *)&_sSOSMIDISongHeader[v8] = v9;
  for (m = 0; m < 0x7F; ++m) {
    v10 = 762 * v37 + 6 * m;
    *(_WORD *)&_lpSOSMIDITriggerCallback[v10 + 4] = 0;
    *(_DWORD *)&_lpSOSMIDITriggerCallback[v10] = 0;
  }
  v11 = 6 * v37;
  *(_WORD *)&_lpSOSMIDIBranchCallback[v11 + 4] = 0;
  *(_DWORD *)&_lpSOSMIDIBranchCallback[v11] = 0;
  v12 = 6 * v37;
  *(_WORD *)&_lpSOSMIDILoopCallback[v12 + 4] = 0;
  *(_DWORD *)&_lpSOSMIDILoopCallback[v12] = 0;
  HIWORD(v12) = HIWORD(a1);
  LOWORD(v12) = __readgsword(a1 + 4);
  v13 = sosMIDINormalizePtr(__readgsdword(*(_DWORD *)&_sSOSMIDISongHeader[6 * v37] + 32) + __readgsdword(a1), v12);
  v29 = WORD2(v13);
  v27 = v13;
  v32 = *(_WORD *)&_sSOSMIDISongHeader[6 * v37 + 4];
  v31 = *(_DWORD *)&_sSOSMIDISongHeader[6 * v37] + 904;
  HIDWORD(v13) = 6 * v37;
  *(__int16 *)((char *)&_sSOSMIDITrackMap_variable_1 + HIDWORD(v13)) = a4;
  *(int *)((char *)&_sSOSMIDITrackMap + HIDWORD(v13)) = a3;
  _wSOSMIDIActiveTracks[v37] = __readgsdword(*(_DWORD *)&_sSOSMIDISongHeader[6 * v37] + 48);
  _wSOSMIDITotalTracks[v37] = _wSOSMIDIActiveTracks[v37];
  LODWORD(v13) = *(_DWORD *)&_sSOSMIDISongHeader[6 * v37];
  v14 = __readgsdword(a1 + 8);
  __writegsword(v13 + 900, __readgsword(a1 + 12));
  __writegsdword(v13 + 896, v14);
  for (n = 0; n < _wSOSMIDIActiveTracks[v37]; ++n) {
    _dwSOSMIDITrackDeltaTime[32 * v37 + n] = 0;
    v15 = sosMIDINormalizePtr(v42 + v31, v32);
    v16 = v15;
    LODWORD(v15) = 6 * n + 192 * v37;
    *(__int16 *)((char *)&_lpSOSMIDITrackHeaders_variable_1 + v15) = WORD2(v15);
    *(int *)((char *)&_lpSOSMIDITrackHeaders + v15) = v16;
    v17 = sosMIDINormalizePtr(v31 + v42 + 12, v32);
    v18 = v17;
    LODWORD(v17) = 192 * v37 + 6 * n;
    *(_WORD *)&_lpSOSMIDITrack[v17 + 4] = WORD2(v17);
    *(_DWORD *)&_lpSOSMIDITrack[v17] = v18;
    LODWORD(v17) = 192 * v37;
    v19 = 192 * v37 + 6 * n;
    LOWORD(v17) = *(_WORD *)&_lpSOSMIDITrack[v19 + 4];
    v26 = sosMIDIGetDeltaTime(*(_DWORD *)&_lpSOSMIDITrack[v19], v17, &_dwSOSMIDITrackDeltaCurrent[32 * v37 + n], __DS__)
      + *(_DWORD *)&_lpSOSMIDITrack[v19];
    *(_WORD *)&_lpSOSMIDITrack[v19 + 4] = *(_WORD *)&_lpSOSMIDITrack[v19 + 4];
    *(_DWORD *)&_lpSOSMIDITrack[v19] = v26;
    v42 += __readgsdword(sosMIDINormalizePtr(v42 + v31, v32) + 4);
  }
  v30 = v27;
  v28 = _wSOSMIDIActiveTracks[v37] + v27;
  for (ii = 0; ii < _wSOSMIDIActiveTracks[v37]; ++ii) {
    if (__readgsbyte(v30)) {
      v20 = 192 * v37 + 6 * ii;
      *(__int16 *)((char *)&_lpMIDIBranchData_variable_1 + v20) = v29;
      *(int *)((char *)_lpMIDIBranchData + v20) = v28;
    }
    for (jj = 0; __readgsbyte(v30) > jj; ++jj) {
      HIWORD(v21) = HIWORD(a1);
      LOWORD(v21) = __readgsword(a1 + 4);
      __writegsdword(v28 + 24 * jj + 8, sosMIDINormalizePtr(__readgsdword(v28 + 24 * jj + 12) + __readgsdword(a1), v21));
    }
    v28 += 24 * __readgsbyte(v30++);
  }
  for (kk = 0; kk < _wSOSMIDITotalTracks[v37]; ++kk) {
    if (__readgsdword(*(int *)((char *)&_sSOSMIDITrackMap + 6 * v37) + 4 * kk) == 255) {
      v41 = 0;
      for (mm = 0; __readgsdword(*(_DWORD *)&_sSOSMIDISongHeader[6 * v37] + 20 * kk + 4 * mm + 128) && !v41 && mm < 5; ++mm) {
        for (nn = 0; nn < 5; ++nn) {
          if (__readgsdword(*(_DWORD *)&_sSOSMIDISongHeader[6 * v37] + 20 * kk + 4 * mm + 128) == 40960) {
            if (_wSOSMIDIDriverID[nn] == 40960 || _wSOSMIDIDriverID[nn] == 40961 || _wSOSMIDIDriverID[nn] == 40968)
              goto LABEL_57;
          } else if (__readgsdword(*(_DWORD *)&_sSOSMIDISongHeader[6 * v37] + 20 * kk + 4 * mm + 128) == 40962) {
            if (_wSOSMIDIDriverID[nn] == 40962 || _wSOSMIDIDriverID[nn] == 40969) {
            LABEL_57:
              __writegsdword(*(int *)((char *)&_sSOSMIDITrackMap + 6 * v37) + 4 * kk, nn);
              v41 = 1;
              break;
            }
          } else if (_wSOSMIDIDriverID[nn] == __readgsdword(*(_DWORD *)&_sSOSMIDISongHeader[6 * v37] + 20 * kk + 4 * mm + 128)) {
            goto LABEL_57;
          }
        }
      }
      if (__readgsdword(*(_DWORD *)&_sSOSMIDISongHeader[6 * v37] + 20 * kk + 128)) {
        if (!v41) {
          v22 = 6 * kk + 192 * v37;
          *(_WORD *)&_lpSOSMIDITrack[v22 + 4] = 0;
          *(_DWORD *)&_lpSOSMIDITrack[v22] = 0;
          __writegsdword(*(int *)((char *)&_sSOSMIDITrackMap + 6 * v37) + 4 * kk, 0xFFu);
          --_wSOSMIDIActiveTracks[v37];
        }
      } else {
        __writegsdword(*(int *)((char *)&_sSOSMIDITrackMap + 6 * v37) + 4 * kk, 0);
      }
    }
  }
  for (i1 = 0; i1 < 0x80; ++i1)
    __writegsbyte(*(_DWORD *)&_sSOSMIDISongHeader[6 * v37] + i1 + 768, 1u);
  __writegsdword(a5, v37);
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIUnInitSong(unsigned int a1)
{
  unsigned int v1; // eax

  if (a1 >= 8)
    return 10;
  v1 = 6 * a1;
  *(_WORD *)&_sSOSMIDISongHeader[v1 + 4] = 0;
  *(_DWORD *)&_sSOSMIDISongHeader[v1] = 0;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIStartSong(int a1)
{
  int v4; // [esp+8h] [ebp-4h]

  v4 = sosTIMERRegisterEvent(
         __readgsdword(*(_DWORD *)&_sSOSMIDISongHeader[6 * a1] + 56),
         (int)sosMIDISongHandler,
         (int)sosMIDISongHandler,
         __CS__,
         (unsigned int)&_wSOSMIDIEventHandle[a1],
         (unsigned __int16)__DS__);
  if (v4)
    return v4;
  _bSOSMIDITimerSongHandler[_wSOSMIDIEventHandle[a1]] = a1;
  _wSOSMIDISongActive[a1] = 1;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIStopSong(unsigned int a1, int a2)
{
  unsigned int v2; // eax

  if (a1 >= 8)
    return 10;
  if (_wSOSMIDIEventHandle[a1] != -1)
    sosTIMERRemoveEvent(_wSOSMIDIEventHandle[a1], a2);
  _bSOSMIDITimerSongHandler[_wSOSMIDIEventHandle[a1]] = -1;
  _wSOSMIDIEventHandle[a1] = -1;
  if (_wSOSMIDISongActive[a1]) {
    sosMIDIResetChannelStealing(a1);
    _wSOSMIDISongActive[a1] = 0;
    v2 = 6 * a1;
    *(_WORD *)&_sSOSMIDISongHeader[v2 + 4] = 0;
    *(_DWORD *)&_sSOSMIDISongHeader[v2] = 0;
    sosMIDIResetSong();
  }
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIResetSong(int a1, int a2, unsigned int a3)
{
  int v3; // eax
  __int64 v4; // rax
  int v5; // ebx
  unsigned int v6; // ebx
  __int64 v7; // rax
  int v8; // ecx
  __int64 v9; // rax
  int v10; // ecx
  int v11; // ecx
  int v12; // eax
  int v14; // [esp+8h] [ebp-2Ch]
  int v16; // [esp+18h] [ebp-1Ch]
  __int16 v17; // [esp+1Ch] [ebp-18h]
  int v19; // [esp+2Ch] [ebp-8h]
  unsigned int i; // [esp+30h] [ebp-4h]
  unsigned int j; // [esp+30h] [ebp-4h]

  v19 = 0;
  HIWORD(v3) = HIWORD(a3);
  LOWORD(v3) = __readgsword(a3 + 4);
  v4 = sosMIDINormalizePtr(__readgsdword(a3), v3);
  v5 = v4;
  LODWORD(v4) = 6 * a1;
  *(_WORD *)&_sSOSMIDISongHeader[v4 + 4] = WORD2(v4);
  *(_DWORD *)&_sSOSMIDISongHeader[v4] = v5;
  v17 = *(_WORD *)&_sSOSMIDISongHeader[6 * a1 + 4];
  v16 = *(_DWORD *)&_sSOSMIDISongHeader[6 * a1] + 904;
  _wSOSMIDIActiveTracks[a1] = __readgsdword(*(_DWORD *)&_sSOSMIDISongHeader[6 * a1] + 48);
  _wSOSMIDITotalTracks[a1] = _wSOSMIDIActiveTracks[a1];
  LODWORD(v4) = *(_DWORD *)&_sSOSMIDISongHeader[6 * a1];
  v6 = __readgsdword(a3 + 8);
  __writegsword(v4 + 900, __readgsword(a3 + 12));
  __writegsdword(v4 + 896, v6);
  for (i = 0; i < _wSOSMIDIActiveTracks[a1]; ++i) {
    _dwSOSMIDITrackDeltaTime[32 * a1 + i] = 0;
    v7 = sosMIDINormalizePtr(v19 + v16, v17);
    v8 = v7;
    LODWORD(v7) = 6 * i + 192 * a1;
    *(__int16 *)((char *)&_lpSOSMIDITrackHeaders_variable_1 + v7) = WORD2(v7);
    *(int *)((char *)&_lpSOSMIDITrackHeaders + v7) = v8;
    v9 = sosMIDINormalizePtr(v16 + v19 + 12, v17);
    v10 = v9;
    LODWORD(v9) = 192 * a1 + 6 * i;
    *(_WORD *)&_lpSOSMIDITrack[v9 + 4] = WORD2(v9);
    *(_DWORD *)&_lpSOSMIDITrack[v9] = v10;
    LODWORD(v9) = 192 * a1;
    v11 = 192 * a1 + 6 * i;
    LOWORD(v9) = *(_WORD *)&_lpSOSMIDITrack[v11 + 4];
    v14 = sosMIDIGetDeltaTime(*(_DWORD *)&_lpSOSMIDITrack[v11], v9, &_dwSOSMIDITrackDeltaCurrent[32 * a1 + i], __DS__)
      + *(_DWORD *)&_lpSOSMIDITrack[v11];
    *(_WORD *)&_lpSOSMIDITrack[v11 + 4] = *(_WORD *)&_lpSOSMIDITrack[v11 + 4];
    *(_DWORD *)&_lpSOSMIDITrack[v11] = v14;
    v19 += __readgsdword(sosMIDINormalizePtr(v19 + v16, v17) + 4);
  }
  for (j = 0; j < _wSOSMIDITotalTracks[a1]; ++j) {
    if (__readgsdword(*(int *)((char *)&_sSOSMIDITrackMap + 6 * a1) + 4 * j) == 255) {
      v12 = 192 * a1 + 6 * j;
      *(_WORD *)&_lpSOSMIDITrack[v12 + 4] = 0;
      *(_DWORD *)&_lpSOSMIDITrack[v12] = 0;
      --_wSOSMIDIActiveTracks[a1];
    }
  }
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIGetDeltaTime(unsigned int a1, int a2, unsigned int a3)
{
  unsigned int v3; // eax
  int v6; // [esp+14h] [ebp-14h]
  unsigned int v7; // [esp+18h] [ebp-10h]
  int v8; // [esp+1Ch] [ebp-Ch]
  int v9; // [esp+20h] [ebp-8h]
  char v10; // [esp+24h] [ebp-4h]

  v9 = 0;
  v8 = 0;
  v7 = 0;
  v6 = 0;
  do {
    ++v6;
    v3 = a1++;
    v10 = __readgsbyte(v3);
    if (v10 < 0)
      v9 = 1;
    v7 |= (v10 & 0x7F) << v8;
    v8 += 7;
  } while (!v9);
  __writegsdword(a3, v7);
  return v6;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDISetMasterVolume(char a1)
{
  unsigned int i; // [esp+4h] [ebp-8h]

  _bSOSMIDIMasterVolume = a1;
  for (i = 0; i < 8; ++i) {
    if (_wSOSMIDISongActive[i])
      sosMIDISetSongVolume(i, LOBYTE(_wSOSMIDISongVolume[i]));
  }
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIRegisterLoopFunction(int a1, int a2, int a3, __int16 a4)
{
  int v4; // edx

  v4 = 6 * a1;
  *(_WORD *)&_lpSOSMIDILoopCallback[v4 + 4] = a4;
  *(_DWORD *)&_lpSOSMIDILoopCallback[v4] = a3;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIRegisterBranchFunction(int a1, int a2, int a3, __int16 a4)
{
  int v4; // edx

  v4 = 6 * a1;
  *(_WORD *)&_lpSOSMIDIBranchCallback[v4 + 4] = a4;
  *(_DWORD *)&_lpSOSMIDIBranchCallback[v4] = a3;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIRegisterTriggerFunction(int a1, unsigned __int8 a2, int a3, __int16 a4)
{
  int v4; // edx

  v4 = 6 * a2 + 762 * a1;
  *(_WORD *)&_lpSOSMIDITriggerCallback[v4 + 4] = a4;
  *(_DWORD *)&_lpSOSMIDITriggerCallback[v4] = a3;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIBranchToTrackLocation(int a1, unsigned __int8 a2, char a3)
{
  int v3; // eax
  __int16 v4; // dx
  unsigned int v5; // ecx
  int v6; // eax
  int i; // [esp+10h] [ebp-10h]
  unsigned __int8 j; // [esp+1Ch] [ebp-4h]

  for (i = 0; a3 != __readgsbyte(*(int *)((char *)&_lpMIDIBranchData[48 * a1] + 6 * a2) + 24 * i + 4); ++i)
    ;
  v3 = 192 * a1 + 6 * a2;
  v4 = *(__int16 *)((char *)&_lpSOSMIDITrackHeaders_variable_1 + v3);
  v5 = *(int *)((char *)&_lpSOSMIDITrackHeaders + v3)
    + __readgsdword(*(int *)((char *)&_lpMIDIBranchData[48 * a1] + 6 * a2) + 24 * i)
    + 12;
  v6 = 192 * a1 + 6 * a2;
  *(_WORD *)&_lpSOSMIDITrack[v6 + 4] = v4;
  *(_DWORD *)&_lpSOSMIDITrack[v6] = v5;
  _bSOSMIDIData = __readgsbyte(*(int *)((char *)&_lpSOSMIDITrackHeaders + v6) + 8) | 0xB0;
  for (j = 0; j < __readgsbyte(*(int *)((char *)&_lpMIDIBranchData[48 * a1] + 6 * a2) + 24 * i + 7); j += 2) {
    _bSOSMIDIData_variable_1 = __readgsbyte(__readgsdword(*(int *)((char *)&_lpMIDIBranchData[48 * a1] + 6 * a2)
                                                          + 24 * i + 8) + j);
    _bSOSMIDIData_variable_2 = __readgsbyte(
                                 __readgsdword(*(int *)((char *)&_lpMIDIBranchData[48 * a1] + 6 * a2) + 24 * i + 8)
                               + j
                               + 1);
    sosMIDIHandleMIDIData(3);
  }
  _bSOSMIDIBranchOccurred = 0;
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIBranchToSongLocation(int a1, char a2)
{
  int v2; // eax
  int v3; // edx
  unsigned int v4; // ecx
  int v5; // eax
  int v6; // ecx
  int j; // [esp+10h] [ebp-10h]
  char v10; // [esp+14h] [ebp-Ch]
  unsigned __int8 i; // [esp+1Ch] [ebp-4h]

  v10 = a2 | 0x80;
  for (i = 1; i < (unsigned int)_wSOSMIDITotalTracks[a1]; ++i) {
    v2 = 192 * a1 + 6 * i;
    if (*(_DWORD *)&_lpSOSMIDITrack[v2] || *(_WORD *)&_lpSOSMIDITrack[v2 + 4]) {
      for (j = 0; v10 != __readgsbyte(*(int *)((char *)&_lpMIDIBranchData[48 * a1] + 6 * i) + 24 * j + 4); ++j)
        ;
      v3 = 6 * i + 192 * a1;
      v4 = *(int *)((char *)&_lpSOSMIDITrackHeaders + v3)
        + __readgsdword(*(int *)((char *)_lpMIDIBranchData + v3) + 24 * j)
        + 12;
      *(_WORD *)&_lpSOSMIDITrack[v3 + 4] = *(__int16 *)((char *)&_lpSOSMIDITrackHeaders_variable_1 + v3);
      *(_DWORD *)&_lpSOSMIDITrack[v3] = v4;
      v5 = 192 * a1;
      LOWORD(v5) = *(_WORD *)&_lpSOSMIDITrack[v3 + 4];
      v6 = sosMIDIGetDeltaTime(
             *(_DWORD *)&_lpSOSMIDITrack[v3],
             v5,
             (unsigned int)&_dwSOSMIDITrackDeltaCurrent[32 * a1 + i])
        + *(_DWORD *)&_lpSOSMIDITrack[v3];
      *(_WORD *)&_lpSOSMIDITrack[v3 + 4] = *(_WORD *)&_lpSOSMIDITrack[v3 + 4];
      *(_DWORD *)&_lpSOSMIDITrack[v3] = v6;
      _dwSOSMIDITrackDeltaTime[32 * a1 + i] = 0;
      sosMIDISetTrackState(a1, i, j);
    }
  }
  _bSOSMIDIBranchOccurred = 0;
  return 0;
}

//-------------------------------------------------------------------------------------------------

void sosMIDISong_End()
{
  ;
}

//-------------------------------------------------------------------------------------------------
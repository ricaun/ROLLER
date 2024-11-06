#ifdef ENABLE_SOSMLIB_PSEUDO
//-------------------------------------------------------------------------------------------------

void sosMIDITmr_Start()
{
  ;
}

//-------------------------------------------------------------------------------------------------

int sosMIDISongHandler()
{
  char v0; // dl
  int v1; // edx
  int v2; // edx
  int v3; // edx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // edx
  int v13; // ebx
  int v14; // eax
  int v15; // ecx
  __int16 v16; // bx
  unsigned int v17; // ecx
  int v18; // eax
  int v19; // eax
  unsigned int v20; // ecx
  int v21; // eax
  int v22; // ecx
  int v23; // eax
  int v24; // ecx
  __int16 v25; // bx
  unsigned int v26; // ecx
  int v27; // eax
  int v28; // eax
  unsigned int v29; // ecx
  int v30; // eax
  int v31; // ecx
  int v32; // ebx
  int v33; // eax
  unsigned int v34; // ebx
  int v35; // eax
  int v36; // eax
  unsigned int v37; // ebx
  int v38; // eax
  int v39; // edx
  int v40; // eax
  int v41; // ecx
  int v42; // ecx
  unsigned __int8 v44; // [esp+Ch] [ebp-54h]
  unsigned int v45; // [esp+10h] [ebp-50h]
  int v46; // [esp+14h] [ebp-4Ch] BYREF
  __int16 v47; // [esp+18h] [ebp-48h]
  unsigned int v48; // [esp+1Ch] [ebp-44h]
  unsigned __int16 v49; // [esp+20h] [ebp-40h]
  unsigned int v50; // [esp+24h] [ebp-3Ch]
  unsigned __int16 v51; // [esp+28h] [ebp-38h]
  int v52; // [esp+2Ch] [ebp-34h]
  int v53; // [esp+30h] [ebp-30h]
  int v54; // [esp+34h] [ebp-2Ch]
  int v55; // [esp+3Ch] [ebp-24h]
  int j; // [esp+40h] [ebp-20h]
  unsigned int v57; // [esp+44h] [ebp-1Ch]
  int v58; // [esp+48h] [ebp-18h]
  unsigned int k; // [esp+4Ch] [ebp-14h]
  int v60; // [esp+50h] [ebp-10h]
  unsigned __int8 i; // [esp+5Ch] [ebp-4h]
  _BYTE retaddr[8]; // [esp+78h] [ebp+18h]

  v58 = 1;
  if (!_wSOSMIDISongActive[(unsigned __int8)_bSOSMIDISongHandle]
    || _wSOSMIDISongPaused[(unsigned __int8)_bSOSMIDISongHandle]) {
    return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)();
  }
  if (!_wSOSMIDIVolumeFadeTicks[(unsigned __int8)_bSOSMIDISongHandle])
    goto LABEL_22;
  v0 = _bSOSMIDIHandleVolumeFade[(unsigned __int8)_bSOSMIDISongHandle];
  _bSOSMIDIHandleVolumeFade[(unsigned __int8)_bSOSMIDISongHandle] = v0 - 1;
  if (v0)
    goto LABEL_22;
  _bSOSMIDIHandleVolumeFade[(unsigned __int8)_bSOSMIDISongHandle] = 3;
  --_wSOSMIDIVolumeFadeTicks[(unsigned __int8)_bSOSMIDISongHandle];
  v45 = _wSOSMIDIVolumeFadeDirection[(unsigned __int8)_bSOSMIDISongHandle];
  if (v45 < 2) {
    if (v45 == 1) {
      _dwSOSMIDIVolumeFadeVolume[(unsigned __int8)_bSOSMIDISongHandle] += _dwSOSMIDIVolumeFadeFraction[(unsigned __int8)_bSOSMIDISongHandle];
      sosMIDISetSongVolume(
        (unsigned __int8)_bSOSMIDISongHandle,
        (unsigned __int8)BYTE2(_dwSOSMIDIVolumeFadeVolume[(unsigned __int8)_bSOSMIDISongHandle]));
    }
  LABEL_22:
    for (i = 0; ; ++i) {
      if (i >= (unsigned int)_wSOSMIDITotalTracks[(unsigned __int8)_bSOSMIDISongHandle])
        return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)();
      v4 = ((unsigned __int8)_bSOSMIDISongHandle << 7) + 4 * i;
      ++*(int *)((char *)_dwSOSMIDITrackDeltaTime + v4);
      v5 = 192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * i;
      if ((*(_DWORD *)&_lpSOSMIDITrack[v5] || *(_WORD *)&_lpSOSMIDITrack[v5 + 4])
        && _dwSOSMIDITrackDeltaCurrent[32 * (unsigned __int8)_bSOSMIDISongHandle + i] <= (unsigned int)_dwSOSMIDITrackDeltaTime[32 * (unsigned __int8)_bSOSMIDISongHandle + i]) {
        break;
      }
    LABEL_156:
      ;
    }
    while (1) {
      _bSOSMIDIBranchOccurred = 0;
      v58 = 1;
      if (__readgsbyte(*(_DWORD *)&_lpSOSMIDITrack[192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * i]) >= 0xF0u)
        v6 = (unsigned __int8)_bSOSMIDIEventSizeControl[__readgsbyte(*(_DWORD *)&_lpSOSMIDITrack[192
                                                                                               * (unsigned __int8)_bSOSMIDISongHandle
                                                                                               + 6 * i]) & 0xF];
      else
        v6 = (unsigned __int8)_bSOSMIDIEventSize[(int)__readgsbyte(*(_DWORD *)&_lpSOSMIDITrack[192
                                                                                             * (unsigned __int8)_bSOSMIDISongHandle
                                                                                             + 6 * i]) >> 4];
      v60 = v6;
      if (__readgsbyte(*(_DWORD *)&_lpSOSMIDITrack[192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * i]) == 0xFF) {
        v44 = __readgsbyte(*(_DWORD *)&_lpSOSMIDITrack[192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * i] + 1);
        if (v44 >= 0x2Fu) {
          if (v44 <= 0x2Fu) {
            v7 = 192 * (unsigned __int8)_bSOSMIDISongHandle;
            v8 = v7 + 6 * i;
            *(_WORD *)&_lpSOSMIDITrack[v8 + 4] = 0;
            *(_DWORD *)&_lpSOSMIDITrack[v8] = 0;
            if (_wSOSMIDIActiveTracks[(unsigned __int8)_bSOSMIDISongHandle] == 2
              && (*(_DWORD *)&_lpSOSMIDITrack[192 * (unsigned __int8)_bSOSMIDISongHandle]
                  || *(_WORD *)&_lpSOSMIDITrack[192 * (unsigned __int8)_bSOSMIDISongHandle + 4])) {
              --_wSOSMIDIActiveTracks[(unsigned __int8)_bSOSMIDISongHandle];
              v9 = 192 * (unsigned __int8)_bSOSMIDISongHandle;
              *(_WORD *)&_lpSOSMIDITrack[v9 + 4] = 0;
              *(_DWORD *)&_lpSOSMIDITrack[v9] = 0;
            }
            v10 = (unsigned __int8)_bSOSMIDISongHandle;
            if (!--_wSOSMIDIActiveTracks[v10]) {
              _wSOSMIDISongActive[(unsigned __int8)_bSOSMIDISongHandle] = 0;
              sosMIDIResetChannelStealing((unsigned __int8)_bSOSMIDISongHandle);
              if (_wSOSMIDIEventHandle[(unsigned __int8)_bSOSMIDISongHandle] != -1)
                sosTIMERRemoveEvent(_wSOSMIDIEventHandle[(unsigned __int8)_bSOSMIDISongHandle], v7);
              _bSOSMIDITimerSongHandler[_wSOSMIDIEventHandle[(unsigned __int8)_bSOSMIDISongHandle]] = -1;
              _wSOSMIDIEventHandle[(unsigned __int8)_bSOSMIDISongHandle] = -1;
              v11 = *(_DWORD *)&_sSOSMIDISongHeader[6 * (unsigned __int8)_bSOSMIDISongHandle];
              v51 = __readgsword(v11 + 900);
              v50 = __readgsdword(v11 + 896);
              v12 = 6 * (unsigned __int8)_bSOSMIDISongHandle;
              v47 = *(_WORD *)&_sSOSMIDISongHeader[v12 + 4];
              v46 = *(_DWORD *)&_sSOSMIDISongHeader[v12];
              v49 = v51;
              v48 = v50;
              *(_WORD *)&_sSOSMIDISongHeader[v12 + 4] = 0;
              *(_DWORD *)&_sSOSMIDISongHeader[v12] = 0;
              sosMIDIResetSong();
              if (v50 || v51)
                MK_FP(v51, v50)((unsigned __int8)_bSOSMIDISongHandle, &v46, &v46, __SS__);
              return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)();
            }
            v60 = 3;
          } else if (v44 == 81) {
            v60 = 5;
          }
        }
      } else if ((__readgsbyte(*(_DWORD *)&_lpSOSMIDITrack[192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * i]) & 0xF0) == 0xB0) {
        switch (__readgsbyte(*(_DWORD *)&_lpSOSMIDITrack[192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * i] + 1)) {
          case 'g':
            __writegsbyte(
              *(_DWORD *)&_sSOSMIDISongHeader[6 * (unsigned __int8)_bSOSMIDISongHandle]
            + __readgsbyte(*(_DWORD *)&_lpSOSMIDITrack[192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * i] + 2)
            + 768,
              0);
            break;
          case 'h':
            __writegsbyte(
              *(_DWORD *)&_sSOSMIDISongHeader[6 * (unsigned __int8)_bSOSMIDISongHandle]
            + __readgsbyte(*(_DWORD *)&_lpSOSMIDITrack[192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * i] + 2)
            + 768,
              1u);
            break;
          case 'l':
          case 'n':
          case 'q':
          case 't':
          case 'x':
            break;
          case 'm':
            v55 = __readgsbyte(*(_DWORD *)&_lpSOSMIDITrack[192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * i] + 2);
            for (j = 0;
                  __readgsbyte(*(int *)((char *)&_lpMIDIBranchData[48 * (unsigned __int8)_bSOSMIDISongHandle] + 6 * i)
                               + 24 * j + 4) != v55;
                  ++j) {
              ;
            }
            goto LABEL_57;
          case 'o':
          case 'p':
            v55 = __readgsbyte(*(_DWORD *)&_lpSOSMIDITrack[192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * i] + 2);
            for (j = 0;
                  __readgsbyte(*(int *)((char *)&_lpMIDIBranchData[48 * (unsigned __int8)_bSOSMIDISongHandle] + 6 * i)
                               + 24 * j + 4) != v55;
                  ++j) {
              ;
            }
            v54 = __readgsbyte(*(int *)((char *)&_lpMIDIBranchData[48 * (unsigned __int8)_bSOSMIDISongHandle] + 6 * i)
                             + 24 * j + 6);
            if (v54 != 255 && v54) {
              v13 = *(int *)((char *)&_lpMIDIBranchData[48 * (unsigned __int8)_bSOSMIDISongHandle] + 6 * i);
              __writegsbyte(v13 + 24 * j + 6, __readgsbyte(v13 + 24 * j + 6) - 1);
              --v54;
            }
            if (*(_DWORD *)&_lpSOSMIDILoopCallback[6 * (unsigned __int8)_bSOSMIDISongHandle]
              || *(_WORD *)&_lpSOSMIDILoopCallback[6 * (unsigned __int8)_bSOSMIDISongHandle + 4]) {
              _bSOSMIDIBranchOccurred = 1;
              if (!MK_FP(
                *(_WORD *)&_lpSOSMIDILoopCallback[6 * (unsigned __int8)_bSOSMIDISongHandle + 4],
                *(_DWORD *)&_lpSOSMIDILoopCallback[6 * (unsigned __int8)_bSOSMIDISongHandle])(
                  (unsigned __int8)_bSOSMIDISongHandle,
                  i,
                  (unsigned __int8)v55,
                  (unsigned __int8)v54))
                v54 = 0;
              if (_bSOSMIDIBranchOccurred) {
                _bSOSMIDIBranchOccurred = 0;
              } else {
                v58 = 0;
                v60 = 0;
              }
            }
            if (v54) {
              for (k = 1; k < _wSOSMIDITotalTracks[(unsigned __int8)_bSOSMIDISongHandle]; ++k) {
                v14 = 6 * k + 192 * (unsigned __int8)_bSOSMIDISongHandle;
                if (*(_DWORD *)&_lpSOSMIDITrack[v14] || *(_WORD *)&_lpSOSMIDITrack[v14 + 4]) {
                  for (j = 0;
                        __readgsbyte(
                          *(int *)((char *)&_lpMIDIBranchData[48 * (unsigned __int8)_bSOSMIDISongHandle] + 6 * k)
                          + 24 * j
                          + 4) != v55;
                          ++j) {
                    ;
                  }
                  v57 = __readgsdword(
                          *(int *)((char *)&_lpMIDIBranchData[48 * (unsigned __int8)_bSOSMIDISongHandle] + 6 * k)
                        + 24 * j)
                    + 12;
                  v15 = 192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * k;
                  v16 = *(__int16 *)((char *)&_lpSOSMIDITrackHeaders_variable_1 + v15);
                  v17 = v57 + *(int *)((char *)&_lpSOSMIDITrackHeaders + v15);
                  v18 = 6 * k + 192 * (unsigned __int8)_bSOSMIDISongHandle;
                  *(_WORD *)&_lpSOSMIDITrack[v18 + 4] = v16;
                  *(_DWORD *)&_lpSOSMIDITrack[v18] = v17;
                  v19 = 192 * (unsigned __int8)_bSOSMIDISongHandle;
                  v20 = v19 + 6 * k;
                  LOWORD(v19) = *(_WORD *)&_lpSOSMIDITrack[v20 + 4];
                  v60 = sosMIDIGetDeltaTime(
                          *(_DWORD *)&_lpSOSMIDITrack[v20],
                          v19,
                          &_dwSOSMIDITrackDeltaCurrent[32 * (unsigned __int8)_bSOSMIDISongHandle + k],
                          __DS__);
                  v21 = 192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * k;
                  v22 = v60 + *(_DWORD *)&_lpSOSMIDITrack[v21];
                  *(_WORD *)&_lpSOSMIDITrack[v21 + 4] = *(_WORD *)&_lpSOSMIDITrack[v21 + 4];
                  *(_DWORD *)&_lpSOSMIDITrack[v21] = v22;
                  _dwSOSMIDITrackDeltaTime[32 * (unsigned __int8)_bSOSMIDISongHandle + k] = 0;
                  v58 = 0;
                  sosMIDISetTrackState((unsigned __int8)_bSOSMIDISongHandle, k, j);
                }
              }
              v60 = 0;
            }
            break;
          case 'r':
            v55 = __readgsbyte(*(_DWORD *)&_lpSOSMIDITrack[192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * i] + 2) | 0x80;
            for (j = 0;
                  __readgsbyte(*(int *)((char *)&_lpMIDIBranchData[48 * (unsigned __int8)_bSOSMIDISongHandle] + 6 * i)
                               + 24 * j + 4) != v55;
                  ++j) {
              ;
            }
            v54 = 1;
            if (*(_DWORD *)&_lpSOSMIDIBranchCallback[6 * (unsigned __int8)_bSOSMIDISongHandle]
              || *(_WORD *)&_lpSOSMIDIBranchCallback[6 * (unsigned __int8)_bSOSMIDISongHandle + 4]) {
              _bSOSMIDIBranchOccurred = 1;
              if (!MK_FP(
                *(_WORD *)&_lpSOSMIDIBranchCallback[6 * (unsigned __int8)_bSOSMIDISongHandle + 4],
                *(_DWORD *)&_lpSOSMIDIBranchCallback[6 * (unsigned __int8)_bSOSMIDISongHandle])(
                  (unsigned __int8)_bSOSMIDISongHandle,
                  i,
                  (unsigned __int8)v55))
                v54 = 0;
              if (_bSOSMIDIBranchOccurred) {
                _bSOSMIDIBranchOccurred = 0;
              } else {
                v58 = 0;
                v60 = 0;
              }
            }
            if (v54) {
              for (k = 1; k < _wSOSMIDITotalTracks[(unsigned __int8)_bSOSMIDISongHandle]; ++k) {
                v23 = 6 * k + 192 * (unsigned __int8)_bSOSMIDISongHandle;
                if (*(_DWORD *)&_lpSOSMIDITrack[v23] || *(_WORD *)&_lpSOSMIDITrack[v23 + 4]) {
                  for (j = 0;
                        __readgsbyte(
                          *(int *)((char *)&_lpMIDIBranchData[48 * (unsigned __int8)_bSOSMIDISongHandle] + 6 * k)
                          + 24 * j
                          + 4) != v55;
                          ++j) {
                    ;
                  }
                  v57 = __readgsdword(
                          *(int *)((char *)&_lpMIDIBranchData[48 * (unsigned __int8)_bSOSMIDISongHandle] + 6 * k)
                        + 24 * j)
                    + 12;
                  v24 = 192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * k;
                  v25 = *(__int16 *)((char *)&_lpSOSMIDITrackHeaders_variable_1 + v24);
                  v26 = v57 + *(int *)((char *)&_lpSOSMIDITrackHeaders + v24);
                  v27 = 6 * k + 192 * (unsigned __int8)_bSOSMIDISongHandle;
                  *(_WORD *)&_lpSOSMIDITrack[v27 + 4] = v25;
                  *(_DWORD *)&_lpSOSMIDITrack[v27] = v26;
                  v28 = 192 * (unsigned __int8)_bSOSMIDISongHandle;
                  v29 = v28 + 6 * k;
                  LOWORD(v28) = *(_WORD *)&_lpSOSMIDITrack[v29 + 4];
                  v60 = sosMIDIGetDeltaTime(
                          *(_DWORD *)&_lpSOSMIDITrack[v29],
                          v28,
                          &_dwSOSMIDITrackDeltaCurrent[32 * (unsigned __int8)_bSOSMIDISongHandle + k],
                          __DS__);
                  v30 = 192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * k;
                  v31 = v60 + *(_DWORD *)&_lpSOSMIDITrack[v30];
                  *(_WORD *)&_lpSOSMIDITrack[v30 + 4] = *(_WORD *)&_lpSOSMIDITrack[v30 + 4];
                  *(_DWORD *)&_lpSOSMIDITrack[v30] = v31;
                  _dwSOSMIDITrackDeltaTime[32 * (unsigned __int8)_bSOSMIDISongHandle + k] = 0;
                  v58 = 0;
                  sosMIDISetTrackState((unsigned __int8)_bSOSMIDISongHandle, k, j);
                }
              }
              v60 = 0;
            }
            break;
          case 's':
            v55 = __readgsbyte(*(_DWORD *)&_lpSOSMIDITrack[192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * i] + 2);
            for (j = 0;
                  __readgsbyte(*(int *)((char *)&_lpMIDIBranchData[48 * (unsigned __int8)_bSOSMIDISongHandle] + 6 * i)
                               + 24 * j + 4) != v55;
                  ++j) {
              ;
            }
          LABEL_57:
            __writegsbyte(
              *(int *)((char *)&_lpMIDIBranchData[48 * (unsigned __int8)_bSOSMIDISongHandle] + 6 * i) + 24 * j + 6,
              __readgsbyte(*(_DWORD *)&_lpSOSMIDITrack[192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * i] + 6));
            break;
          case 'u':
          case 'v':
            v55 = __readgsbyte(*(_DWORD *)&_lpSOSMIDITrack[192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * i] + 2);
            for (j = 0;
                  __readgsbyte(*(int *)((char *)&_lpMIDIBranchData[48 * (unsigned __int8)_bSOSMIDISongHandle] + 6 * i)
                               + 24 * j + 4) != v55;
                  ++j) {
              ;
            }
            v54 = __readgsbyte(*(int *)((char *)&_lpMIDIBranchData[48 * (unsigned __int8)_bSOSMIDISongHandle] + 6 * i)
                             + 24 * j + 6);
            if (v54 != 255 && v54) {
              v32 = *(int *)((char *)&_lpMIDIBranchData[48 * (unsigned __int8)_bSOSMIDISongHandle] + 6 * i);
              __writegsbyte(v32 + 24 * j + 6, __readgsbyte(v32 + 24 * j + 6) - 1);
              --v54;
            }
            if (*(_DWORD *)&_lpSOSMIDILoopCallback[6 * (unsigned __int8)_bSOSMIDISongHandle]
              || *(_WORD *)&_lpSOSMIDILoopCallback[6 * (unsigned __int8)_bSOSMIDISongHandle + 4]) {
              _bSOSMIDIBranchOccurred = 1;
              if (!MK_FP(
                *(_WORD *)&_lpSOSMIDILoopCallback[6 * (unsigned __int8)_bSOSMIDISongHandle + 4],
                *(_DWORD *)&_lpSOSMIDILoopCallback[6 * (unsigned __int8)_bSOSMIDISongHandle])(
                  (unsigned __int8)_bSOSMIDISongHandle,
                  i,
                  (unsigned __int8)v55,
                  (unsigned __int8)v54))
                v54 = 0;
              if (_bSOSMIDIBranchOccurred)
                _bSOSMIDIBranchOccurred = 0;
              else
                v60 = 0;
            }
            if (v54) {
              v57 = __readgsdword(*(int *)((char *)&_lpMIDIBranchData[48 * (unsigned __int8)_bSOSMIDISongHandle] + 6 * i) + 24 * j)
                + 12;
              v33 = 6 * i + 192 * (unsigned __int8)_bSOSMIDISongHandle;
              v34 = v57 + *(int *)((char *)&_lpSOSMIDITrackHeaders + v33);
              *(_WORD *)&_lpSOSMIDITrack[v33 + 4] = *(__int16 *)((char *)&_lpSOSMIDITrackHeaders_variable_1 + v33);
              *(_DWORD *)&_lpSOSMIDITrack[v33] = v34;
              sosMIDISetTrackState((unsigned __int8)_bSOSMIDISongHandle, i, j);
              v60 = 0;
            }
            break;
          case 'w':
            v54 = __readgsbyte(*(_DWORD *)&_lpSOSMIDITrack[192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * i] + 2);
            v35 = 762 * (unsigned __int8)_bSOSMIDISongHandle + 6 * v54;
            if (*(_DWORD *)&_lpSOSMIDITriggerCallback[v35] || *(_WORD *)&_lpSOSMIDITriggerCallback[v35 + 4]) {
              _bSOSMIDIBranchOccurred = 1;
              MK_FP(
                *(_WORD *)&_lpSOSMIDITriggerCallback[762 * (unsigned __int8)_bSOSMIDISongHandle + 4 + 6 * v54],
                *(_DWORD *)&_lpSOSMIDITriggerCallback[762 * (unsigned __int8)_bSOSMIDISongHandle + 6 * v54])(
                (unsigned __int8)_bSOSMIDISongHandle,
                i,
                (unsigned __int8)v54);
              if (_bSOSMIDIBranchOccurred) {
                _bSOSMIDIBranchOccurred = 0;
              } else {
                v58 = 0;
                v60 = 0;
              }
            }
            break;
          case 'y':
            v55 = __readgsbyte(*(_DWORD *)&_lpSOSMIDITrack[192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * i] + 2);
            for (j = 0;
                  __readgsbyte(*(int *)((char *)&_lpMIDIBranchData[48 * (unsigned __int8)_bSOSMIDISongHandle] + 6 * i)
                               + 24 * j + 4) != v55;
                  ++j) {
              ;
            }
            v54 = 1;
            if (*(_DWORD *)&_lpSOSMIDIBranchCallback[6 * (unsigned __int8)_bSOSMIDISongHandle]
              || *(_WORD *)&_lpSOSMIDIBranchCallback[6 * (unsigned __int8)_bSOSMIDISongHandle + 4]) {
              _bSOSMIDIBranchOccurred = 1;
              if (!MK_FP(
                *(_WORD *)&_lpSOSMIDIBranchCallback[6 * (unsigned __int8)_bSOSMIDISongHandle + 4],
                *(_DWORD *)&_lpSOSMIDIBranchCallback[6 * (unsigned __int8)_bSOSMIDISongHandle])(
                  (unsigned __int8)_bSOSMIDISongHandle,
                  i,
                  (unsigned __int8)v55))
                v54 = 0;
              if (_bSOSMIDIBranchOccurred)
                _bSOSMIDIBranchOccurred = 0;
              else
                v60 = 0;
            }
            if (v54) {
              v57 = __readgsdword(*(int *)((char *)&_lpMIDIBranchData[48 * (unsigned __int8)_bSOSMIDISongHandle] + 6 * i) + 24 * j)
                + 12;
              v36 = 6 * i + 192 * (unsigned __int8)_bSOSMIDISongHandle;
              v37 = v57 + *(int *)((char *)&_lpSOSMIDITrackHeaders + v36);
              *(_WORD *)&_lpSOSMIDITrack[v36 + 4] = *(__int16 *)((char *)&_lpSOSMIDITrackHeaders_variable_1 + v36);
              *(_DWORD *)&_lpSOSMIDITrack[v36] = v37;
              sosMIDISetTrackState((unsigned __int8)_bSOSMIDISongHandle, i, j);
              v60 = 0;
            }
            break;
          default:
            goto LABEL_147;
        }
      } else {
      LABEL_147:
        if (i)
          sosMIDIHandleMIDIData(v60);
      }
      if (!_bSOSMIDIBranchOccurred)
        _dwSOSMIDITrackDeltaTime[32 * (unsigned __int8)_bSOSMIDISongHandle + i] = 0;
      v38 = 192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * i;
      if (*(_DWORD *)&_lpSOSMIDITrack[v38] || *(_WORD *)&_lpSOSMIDITrack[v38 + 4]) {
        v39 = 192 * (unsigned __int8)_bSOSMIDISongHandle + 6 * i;
        LOWORD(v53) = *(_WORD *)&_lpSOSMIDITrack[v39 + 4];
        v52 = v60 + *(_DWORD *)&_lpSOSMIDITrack[v39];
        *(_WORD *)&_lpSOSMIDITrack[v39 + 4] = v53;
        *(_DWORD *)&_lpSOSMIDITrack[v39] = v52;
        if (v58) {
          v40 = 6 * i;
          v41 = v40 + 192 * (unsigned __int8)_bSOSMIDISongHandle;
          LOWORD(v40) = *(_WORD *)&_lpSOSMIDITrack[v41 + 4];
          v60 = sosMIDIGetDeltaTime(
                  *(_DWORD *)&_lpSOSMIDITrack[v41],
                  v40,
                  &_dwSOSMIDITrackDeltaCurrent[32 * (unsigned __int8)_bSOSMIDISongHandle + i],
                  __DS__);
          v42 = 6 * i + 192 * (unsigned __int8)_bSOSMIDISongHandle;
          LOWORD(v53) = *(_WORD *)&_lpSOSMIDITrack[v42 + 4];
          v52 = v60 + *(_DWORD *)&_lpSOSMIDITrack[v42];
          *(_WORD *)&_lpSOSMIDITrack[v42 + 4] = v53;
          *(_DWORD *)&_lpSOSMIDITrack[v42] = v52;
        }
        if (!_dwSOSMIDITrackDeltaCurrent[32 * (unsigned __int8)_bSOSMIDISongHandle + i])
          continue;
      }
      goto LABEL_156;
    }
  }
  if (v45 > 2 && v45 != 4)
    goto LABEL_22;
  _dwSOSMIDIVolumeFadeVolume[(unsigned __int8)_bSOSMIDISongHandle] -= _dwSOSMIDIVolumeFadeFraction[(unsigned __int8)_bSOSMIDISongHandle];
  v1 = (unsigned __int8)BYTE2(_dwSOSMIDIVolumeFadeVolume[(unsigned __int8)_bSOSMIDISongHandle]);
  sosMIDISetSongVolume((unsigned __int8)_bSOSMIDISongHandle, v1);
  if ((_wSOSMIDIVolumeFadeDirection[(unsigned __int8)_bSOSMIDISongHandle] & 4) == 0
    || _wSOSMIDIVolumeFadeTicks[(unsigned __int8)_bSOSMIDISongHandle]) {
    goto LABEL_22;
  }
  _wSOSMIDISongActive[(unsigned __int8)_bSOSMIDISongHandle] = 0;
  sosMIDIResetChannelStealing((unsigned __int8)_bSOSMIDISongHandle);
  if (_wSOSMIDIEventHandle[(unsigned __int8)_bSOSMIDISongHandle] != -1)
    sosTIMERRemoveEvent(_wSOSMIDIEventHandle[(unsigned __int8)_bSOSMIDISongHandle], v1);
  _bSOSMIDITimerSongHandler[_wSOSMIDIEventHandle[(unsigned __int8)_bSOSMIDISongHandle]] = -1;
  _wSOSMIDIEventHandle[(unsigned __int8)_bSOSMIDISongHandle] = -1;
  v2 = *(_DWORD *)&_sSOSMIDISongHeader[6 * (unsigned __int8)_bSOSMIDISongHandle];
  v51 = __readgsword(v2 + 900);
  v50 = __readgsdword(v2 + 896);
  v3 = 6 * (unsigned __int8)_bSOSMIDISongHandle;
  v47 = *(_WORD *)&_sSOSMIDISongHeader[v3 + 4];
  v46 = *(_DWORD *)&_sSOSMIDISongHeader[v3];
  v49 = v51;
  v48 = v50;
  *(_WORD *)&_sSOSMIDISongHeader[v3 + 4] = 0;
  *(_DWORD *)&_sSOSMIDISongHeader[v3] = 0;
  sosMIDIResetSong();
  if (v50 || v51)
    MK_FP(v51, v50)((unsigned __int8)_bSOSMIDISongHandle, &v46, &v46, __SS__);
  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)();
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDISetTrackState(int a1, int a2, int a3)
{
  int result; // eax
  unsigned int i; // [esp+18h] [ebp-4h]

  if (__readgsbyte(*(_DWORD *)&_sSOSMIDISongHeader[6 * a1] + 876))
    sosMIDIHandleMIDIData(2);
  for (i = 0; ; i += 2) {
    result = __readgsbyte(*(int *)((char *)&_lpMIDIBranchData[48 * a1] + 6 * a2) + 24 * a3 + 7);
    if ((unsigned __int8)result <= i)
      break;
    if (__readgsbyte(
      *(_DWORD *)&_sSOSMIDISongHeader[6 * a1]
      + __readgsbyte(__readgsdword(*(int *)((char *)&_lpMIDIBranchData[48 * a1] + 6 * a2) + 24 * a3 + 8) + i)
      + 768)) {
      sosMIDIHandleMIDIData(3);
    }
  }
  return result;
}

//-------------------------------------------------------------------------------------------------

void sosMIDITmr_End()
{
  ;
}

//-------------------------------------------------------------------------------------------------
#endif
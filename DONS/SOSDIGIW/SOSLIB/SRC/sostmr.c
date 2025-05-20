/*
//-------------------------------------------------------------------------------------------------

void sosDIGITmr_Start()
{
  ;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosTIMERInitSystem(unsigned int a1, int (__far *a2)())
{
  int v2; // eax
  char v5; // [esp+4h] [ebp-Ch]

  v5 = (char)a2;
  LOBYTE(_bTIMERDPMI) = ((unsigned __int8)a2 & 2) != 0;
  if (((unsigned __int8)a2 & 1) != 0) {
    LOBYTE(_bTIMERInstalled) = 0;
  } else {
    LOBYTE(_bTIMERInstalled) = 1;
    sosTIMERDRVDisable();
    a2 = sosTIMERHandler;
    v2 = sosTIMERDRVInit(0xFFFF, sosTIMERHandler, (unsigned __int16)__CS__);
    sosTIMERDRVEnable(v2);
  }
  if (a1 && (v5 & 1) == 0) {
    if (a1 == 65280) {
      sosTIMERSetRate(0xFFFF, (_BYTE)a2);
      _wTIMEREventRate_variable_1 = 65280;
    } else {
      sosTIMERSetRate((unsigned int)&unk_1234DC / a1, (unsigned __int8)((unsigned int)&unk_1234DC % a1));
      _wTIMEREventRate_variable_1 = a1;
    }
    _lpTIMEREvents_variable_3 = __CS__;
    _lpTIMEREvents_variable_2 = (int)sosTIMEROldHandler;
    _dwTIMEREventFraction_variable_1 = (int)cstart_branch_1;
  } else {
    _wTIMERValue = 0xFFFF;
  }
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosTIMERUnInitSystem(int a1)
{
  int v1; // eax
  int v2; // eax

  if ((_BYTE)_bTIMERInstalled) {
    v1 = sosTIMERDRVDisable(a1);
    v2 = sosTIMERDRVUnInit(v1);
    sosTIMERDRVEnable(v2);
  }
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosTIMERRegisterEvent(unsigned int a1, int a2, int a3, __int16 a4, unsigned int a5, int a6)
{
  int v6; // edx
  unsigned int v7; // eax
  int v9; // [esp+0h] [ebp-20h]
  unsigned int v12; // [esp+14h] [ebp-Ch]
  unsigned int v13; // [esp+18h] [ebp-8h]
  unsigned int i; // [esp+1Ch] [ebp-4h]
  unsigned int j; // [esp+1Ch] [ebp-4h]

  v9 = a3;
  v12 = 0;
  for (i = 0; i < 0x10 && (*(_DWORD *)&_lpTIMEREvents[6 * i] || *(_WORD *)&_lpTIMEREvents[6 * i + 4]); ++i)
    ;
  if (i >= 0x10)
    return 11;
  if ((_BYTE)_bTIMERInstalled)
    sosTIMERDRVDisable(a3);
  v13 = i;
  v6 = 6 * i;
  *(_WORD *)&_lpTIMEREvents[v6 + 4] = a4;
  *(_DWORD *)&_lpTIMEREvents[v6] = v9;
  _wTIMEREventRate[i] = a1;
  v7 = (unsigned int)&unk_1234DC / a1;
  if ((unsigned int)&unk_1234DC / a1 < _wTIMERValue) {
    sosTIMERSetRate((unsigned int)&unk_1234DC / a1, (unsigned int)&unk_1234DC % a1);
    v7 = (_wTIMERValue << 16) / ((unsigned int)&unk_1234DC / a1);
    v12 = v7;
  }
  for (j = 0; j < 0x10; ++j) {
    v7 = 6 * j;
    if (*(_DWORD *)&_lpTIMEREvents[6 * j] || *(_WORD *)&_lpTIMEREvents[6 * j + 4]) {
      if (_wTIMEREventRate[j] == 65280) {
        v7 = 4 * j;
        if (_wTIMERValue == 0xFFFF)
          _dwTIMEREventFraction[j] = (int)cstart_branch_1;
        else
          _dwTIMEREventFraction[j] = (unsigned int)&unk_123333 / ((unsigned int)&unk_1234DC / _wTIMERValue);
      } else {
        v7 = 4 * j;
        _dwTIMEREventFraction[j] = (_wTIMEREventRate[j] << 16) / ((unsigned int)&unk_1234DC / _wTIMERValue);
      }
      if (v12) {
        v7 = ((unsigned int)(HIWORD(v12) * _dwTIMEREventFractionCurrent[j]) >> 16)
          + (((unsigned int)(unsigned __int16)v12 * _dwTIMEREventFractionCurrent[j]) >> 16);
        _dwTIMEREventFractionCurrent[j] = v7;
      }
    }
  }
  if ((_BYTE)_bTIMERInstalled)
    sosTIMERDRVEnable(v7);
  __writegsdword(a5, v13);
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosTIMERAlterEventRate(unsigned int a1, unsigned int a2)
{
  unsigned int v2; // eax
  unsigned int v4; // [esp+0h] [ebp-10h]
  unsigned int i; // [esp+Ch] [ebp-4h]

  v4 = a1;
  if (a1 >= 0x10)
    return 10;
  if (!*(_DWORD *)&_lpTIMEREvents[6 * a1] && !*(_WORD *)&_lpTIMEREvents[6 * a1 + 4])
    return 10;
  if ((_BYTE)_bTIMERInstalled)
    sosTIMERDRVDisable(a1);
  _wTIMEREventRate[v4] = a2;
  v2 = (unsigned int)&unk_1234DC / a2;
  if ((unsigned int)&unk_1234DC / a2 < _wTIMERValue)
    v2 = sosTIMERSetRate((unsigned int)&unk_1234DC / a2, (unsigned int)&unk_1234DC % a2);
  for (i = 0; i < 0x10; ++i) {
    v2 = 6 * i;
    if (*(_DWORD *)&_lpTIMEREvents[6 * i] || *(_WORD *)&_lpTIMEREvents[6 * i + 4]) {
      if (_wTIMEREventRate[i] == 65280) {
        if (_wTIMERValue == 0xFFFF)
          _dwTIMEREventFraction[i] = (int)cstart_branch_1;
        else
          _dwTIMEREventFraction[i] = (unsigned int)&unk_123333 / ((unsigned int)&unk_1234DC / _wTIMERValue);
      } else {
        _dwTIMEREventFraction[i] = (_wTIMEREventRate[i] << 16) / ((unsigned int)&unk_1234DC / _wTIMERValue);
      }
      v2 = 4 * i;
      _dwTIMEREventFractionCurrent[i] = 0;
    }
  }
  if ((_BYTE)_bTIMERInstalled)
    sosTIMERDRVEnable(v2);
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosTIMERRemoveEvent(int a1, int a2)
{
  int v2; // eax
  int v3; // eax
  unsigned int v6; // [esp+8h] [ebp-8h]
  unsigned int i; // [esp+Ch] [ebp-4h]
  unsigned int j; // [esp+Ch] [ebp-4h]

  v6 = 0;
  v2 = 6 * a1;
  *(_WORD *)&_lpTIMEREvents[v2 + 4] = 0;
  *(_DWORD *)&_lpTIMEREvents[v2] = 0;
  for (i = 0; i < 0x10; ++i) {
    if ((*(_DWORD *)&_lpTIMEREvents[6 * i] || *(_WORD *)&_lpTIMEREvents[6 * i + 4])
      && _wTIMEREventRate[i] > v6
      && _wTIMEREventRate[i] != 65280) {
      v6 = _wTIMEREventRate[i];
    }
  }
  if (v6)
    v3 = sosTIMERSetRate((unsigned int)&unk_1234DC / v6, (unsigned int)&unk_1234DC % v6);
  else
    v3 = sosTIMERSetRate(0xFFFF, a2);
  if ((_BYTE)_bTIMERInstalled)
    v3 = sosTIMERDRVDisable(a1);
  for (j = 0; j < 0x10; ++j) {
    v3 = 6 * j;
    if (*(_DWORD *)&_lpTIMEREvents[6 * j] || *(_WORD *)&_lpTIMEREvents[6 * j + 4]) {
      if (_wTIMEREventRate[j] == 65280) {
        if (_wTIMERValue == 0xFFFF)
          _dwTIMEREventFraction[j] = (int)cstart_branch_1;
        else
          _dwTIMEREventFraction[j] = (unsigned int)&unk_123333 / ((unsigned int)&unk_1234DC / _wTIMERValue);
      } else {
        _dwTIMEREventFraction[j] = (_wTIMEREventRate[j] << 16) / ((unsigned int)&unk_1234DC / _wTIMERValue);
      }
      v3 = 4 * j;
      _dwTIMEREventFractionCurrent[j] = 0;
    }
  }
  if ((_BYTE)_bTIMERInstalled)
    sosTIMERDRVEnable(v3);
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosTIMERGetEventRate(int a1)
{
  return _wTIMEREventRate[a1];
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosTIMERSetRate(int a1)
{
  _wTIMERValue = a1;
  sosTIMERDRVSetRate(a1);
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosTIMERHandler(int a1, int a2, int a3, int a4)
{
  _BYTE retaddr[8]; // [esp+18h] [ebp+18h]

  ++_wSOSTimerEntered;
  for (_wSOSTimerEventIndex = 0; (unsigned int)_wSOSTimerEventIndex < 0x10; ++_wSOSTimerEventIndex) {
    a1 = 6 * _wSOSTimerEventIndex;
    if (*(_DWORD *)&_lpTIMEREvents[6 * _wSOSTimerEventIndex] || *(_WORD *)&_lpTIMEREvents[6 * _wSOSTimerEventIndex + 4]) {
      a2 = _dwTIMEREventFraction[_wSOSTimerEventIndex];
      _dwTIMEREventFractionCurrent[_wSOSTimerEventIndex] += a2;
      a1 = 4 * _wSOSTimerEventIndex;
      if ((_dwTIMEREventFractionCurrent[_wSOSTimerEventIndex] & 0x10000) != 0) {
        HIWORD(_dwTIMEREventFractionCurrent[_wSOSTimerEventIndex]) = 0;
        if (_bSOSMIDITimerSongHandler[_wSOSTimerEventIndex] != -1)
          _bSOSMIDISongHandle = _bSOSMIDITimerSongHandler[_wSOSTimerEventIndex];
        a1 = MK_FP(
               *(_WORD *)&_lpTIMEREvents[6 * _wSOSTimerEventIndex + 4],
               *(_DWORD *)&_lpTIMEREvents[6 * _wSOSTimerEventIndex])();
      }
    }
  }
  --_wSOSTimerEntered;
  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(a1, a2, a3, a4);
}

//-------------------------------------------------------------------------------------------------

void sosDIGITmr_End()
{
  ;
}

//-------------------------------------------------------------------------------------------------
*/
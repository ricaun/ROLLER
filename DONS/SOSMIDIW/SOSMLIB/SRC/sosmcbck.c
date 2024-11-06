
//-------------------------------------------------------------------------------------------------

void sosMIDICbck_Start()
{
  ;
}

//-------------------------------------------------------------------------------------------------

int *callbackGetCallTable()
{
  return &_lpSOSMIDICBCKDrvFunctions;
}

//-------------------------------------------------------------------------------------------------

int __cdecl callbackSendData(int a1, unsigned __int16 a2, int a3, int a4)
{
  _BYTE retaddr[8]; // [esp+10h] [ebp+Ch]

  MK_FP(*((_WORD *)&_lpSOSMIDICBCKFunctions + 2), _lpSOSMIDICBCKFunctions)(a1, a2, a3, a4);
  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(0);
}

//-------------------------------------------------------------------------------------------------

int callbackInit()
{
  _BYTE retaddr[8]; // [esp+10h] [ebp+Ch]

  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(0);
}

//-------------------------------------------------------------------------------------------------

int callbackUnInit()
{
  _BYTE retaddr[8]; // [esp+10h] [ebp+Ch]

  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(0);
}

//-------------------------------------------------------------------------------------------------

int callbackReset()
{
  _BYTE retaddr[8]; // [esp+10h] [ebp+Ch]

  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(0);
}

//-------------------------------------------------------------------------------------------------

int __cdecl callbackSetInstrumentData(int(__cdecl *a1)(_DWORD, _DWORD, _DWORD, _DWORD), __int16 a2)
{
  _BYTE retaddr[8]; // [esp+10h] [ebp+Ch]

  *((_WORD *)&_lpSOSMIDICBCKFunctions + 2) = a2;
  _lpSOSMIDICBCKFunctions = a1;
  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(0);
}

//-------------------------------------------------------------------------------------------------

void sosMIDICbck_End()
{
  ;
}

//-------------------------------------------------------------------------------------------------
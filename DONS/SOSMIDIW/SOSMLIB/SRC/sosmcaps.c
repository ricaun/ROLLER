/*
//-------------------------------------------------------------------------------------------------

void sosMIDICaps_Start()
{
  ;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIGetDeviceCaps(int a1, int a2, int a3, unsigned __int16 a4)
{
  if (!_wSOSMIDIDriverLoaded[a1])
    return 1;
  if (!a3 && !a4)
    return 2;
  sosMIDIDRVGetCapsInfo(
    *(int *)((char *)&_lpSOSMIDIDriverCS + 6 * a1),
    (unsigned __int16)_lpSOSMIDIDriverCS_variable_1[3 * a1],
    *(int *)((char *)&_lpSOSMIDIDriver + 6 * a1),
    (unsigned __int16)_lpSOSMIDIDriver_variable_1[3 * a1],
    a3,
    a4);
  return 0;
}

//-------------------------------------------------------------------------------------------------

void sosMIDICaps_End()
{
  ;
}

//-------------------------------------------------------------------------------------------------
*/
#ifdef ENABLE_SOSLIB_PSEUDO
//-------------------------------------------------------------------------------------------------

void sosDIGICaps_Start()
{
  ;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIGetDeviceCaps(int a1, int a2, int a3, unsigned __int16 a4)
{
  int v4; // eax

  v4 = 3 * a1;
  if (!*(int *)((char *)&_lpSOSDriver + v4 * 2) && !_lpSOSDriver_variable_1[v4])
    return 1;
  if (!a3 && !a4)
    return 2;
  sosDRVGetCapsPtr(
    *(int *)((char *)&_lpSOSDriverCS + 6 * a1),
    (unsigned __int16)_lpSOSDriverCS_variable_1[3 * a1],
    *(int *)((char *)&_lpSOSDriver + 6 * a1),
    (unsigned __int16)_lpSOSDriver_variable_1[3 * a1],
    a3,
    a4);
  return 0;
}

//-------------------------------------------------------------------------------------------------

void sosDIGICaps_End()
{
  ;
}

//-------------------------------------------------------------------------------------------------
#endif
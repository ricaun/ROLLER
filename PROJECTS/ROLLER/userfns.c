#ifdef ENABLE_PSEUDO
//-------------------------------------------------------------------------------------------------

double __stdcall getdirection(double a1, double a2)
{
  if ((HIDWORD(a1) & 0x7FFFFFFF) == 0 && !LODWORD(a1) && (HIDWORD(a2) & 0x7FFFFFFF) == 0 && !LODWORD(a2))
    return -1.0;
  IF_DATAN2(a1);
  return a1;
}

//-------------------------------------------------------------------------------------------------
#endif
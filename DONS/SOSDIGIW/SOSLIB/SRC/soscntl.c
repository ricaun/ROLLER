/*
//-------------------------------------------------------------------------------------------------

void sosDIGICntl_Start()
{
  ;
}

//-------------------------------------------------------------------------------------------------

unsigned int __fastcall sosDIGIGetDMAPosition(int a1)
{
  return __readgsdword(*(_DWORD *)&_lpSOSDMAFillCount[6 * a1]);
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGISetSampleVolume(int a1, int a2, unsigned __int16 a3)
{
  int v5; // [esp+10h] [ebp-4h]

  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  v5 = (__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 50);
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 50, a3);
  return v5;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIGetSampleVolume(int a1, int a2)
{
  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  else
    return (__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 50);
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGISetChannel(int a1, int a2, unsigned __int16 a3)
{
  int v5; // [esp+10h] [ebp-4h]

  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  v5 = (__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 54);
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 54, a3);
  return v5;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIGetChannel(int a1, int a2)
{
  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  else
    return (__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 54);
}

//-------------------------------------------------------------------------------------------------

unsigned int __fastcall sosDIGIGetBytesProcessed(int a1, int a2)
{
  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  else
    return __readgsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 76);
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIGetLoopCount(int a1, int a2)
{
  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  else
    return (__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 56);
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGISetPanLocation(int a1, int a2, unsigned __int16 a3)
{
  int v5; // [esp+10h] [ebp-4h]

  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  v5 = (__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 84);
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 84, a3);
  return v5;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIGetPanLocation(int a1, int a2)
{
  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  else
    return (__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 84);
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGISetPanSpeed(int a1, int a2, unsigned __int16 a3)
{
  int v5; // [esp+10h] [ebp-4h]

  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  v5 = (__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 86);
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 86, a3);
  return v5;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIGetPanSpeed(int a1, int a2)
{
  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  else
    return (__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 86);
}

//-------------------------------------------------------------------------------------------------

unsigned int __fastcall sosDIGISetPitch(int a1, int a2, unsigned int a3)
{
  unsigned int v5; // [esp+10h] [ebp-4h]

  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  v5 = __readgsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 68);
  __writegsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 68, a3);
  return v5;
}

//-------------------------------------------------------------------------------------------------

unsigned int __fastcall sosDIGIGetPitch(int a1, int a2)
{
  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  else
    return __readgsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 68);
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIGetSampleID(int a1, int a2)
{
  return (__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 52);
}

//-------------------------------------------------------------------------------------------------

unsigned int __fastcall sosDIGIGetSampleHandle(int a1, int a2)
{
  unsigned int i; // [esp+Ch] [ebp-4h]

  for (i = 0; ; ++i) {
    if (i >= 0x20)
      return -1;
    if ((__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 52) == a2)
      break;
  }
  return i;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGISetMasterVolume(int a1, unsigned __int16 a2)
{
  __writegsword(*(_DWORD *)&_lpSOSDMAFillCount[6 * a1] + 4, a2);
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGISetMasterVolume(int a1, unsigned __int16 a2)
{
  __writegsword(*(_DWORD *)&_lpSOSDMAFillCount[6 * a1] + 4, a2);
  return 0;
}

//-------------------------------------------------------------------------------------------------
*/
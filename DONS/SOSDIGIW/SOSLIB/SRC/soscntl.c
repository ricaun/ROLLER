#include "soscntl.h"
//-------------------------------------------------------------------------------------------------

void sosDIGICntl_Start()
{
  ;
}

//-------------------------------------------------------------------------------------------------

unsigned int sosDIGIGetDMAPosition(int a1)
{
  return 0;
  //return __readgsdword(*(_DWORD *)&_lpSOSDMAFillCount[6 * a1]);
}

//-------------------------------------------------------------------------------------------------

int sosDIGISetSampleVolume(int a1, int a2, uint16 a3)
{
  return 0;
  /*int v5; // [esp+10h] [ebp-4h]

  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  v5 = (__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 50);
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 50, a3);
  return v5;*/
}

//-------------------------------------------------------------------------------------------------

int sosDIGIGetSampleVolume(int a1, int a2)
{
  return 0;
  /*
  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  else
    return (__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 50);*/
}

//-------------------------------------------------------------------------------------------------

int sosDIGISetChannel(int a1, int a2, uint16 a3)
{
  return 0;
  /*
  int v5; // [esp+10h] [ebp-4h]

  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  v5 = (__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 54);
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 54, a3);
  return v5;*/
}

//-------------------------------------------------------------------------------------------------

int sosDIGIGetChannel(int a1, int a2)
{
  return 0;
  /*
  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  else
    return (__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 54);*/
}

//-------------------------------------------------------------------------------------------------

unsigned int sosDIGIGetBytesProcessed(int a1, int a2)
{
  return 0;
  /*
  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  else
    return __readgsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 76);*/
}

//-------------------------------------------------------------------------------------------------

int sosDIGIGetLoopCount(int a1, int a2)
{
  return 0;
  /*
  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  else
    return (__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 56);*/
}

//-------------------------------------------------------------------------------------------------

int sosDIGISetPanLocation(int a1, int a2, uint16 a3)
{
  return 0;
  /*
  int v5; // [esp+10h] [ebp-4h]

  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  v5 = (__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 84);
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 84, a3);
  return v5;*/
}

//-------------------------------------------------------------------------------------------------

int sosDIGIGetPanLocation(int a1, int a2)
{
  return 0;
  /*
  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  else
    return (__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 84);*/
}

//-------------------------------------------------------------------------------------------------

int sosDIGISetPanSpeed(int a1, int a2, uint16 a3)
{
  return 0;
  /*
  int v5; // [esp+10h] [ebp-4h]

  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  v5 = (__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 86);
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 86, a3);
  return v5;*/
}

//-------------------------------------------------------------------------------------------------

int sosDIGIGetPanSpeed(int a1, int a2)
{
  return 0;
  /*
  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  else
    return (__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 86);*/
}

//-------------------------------------------------------------------------------------------------

unsigned int sosDIGISetPitch(int a1, int a2, unsigned int a3)
{
  return 0;
  /*
  unsigned int v5; // [esp+10h] [ebp-4h]

  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  v5 = __readgsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 68);
  __writegsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 68, a3);
  return v5;*/
}

//-------------------------------------------------------------------------------------------------

unsigned int sosDIGIGetPitch(int a1, int a2)
{
  return 0;
  /*
  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0)
    return 0;
  else
    return __readgsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 68);*/
}

//-------------------------------------------------------------------------------------------------

int sosDIGIGetSampleID(int a1, int a2)
{
  return 0;
  /*
  return (__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 52);*/
}

//-------------------------------------------------------------------------------------------------

unsigned int sosDIGIGetSampleHandle(int a1, int a2)
{
  return 0;
  /*
  unsigned int i; // [esp+Ch] [ebp-4h]

  for (i = 0; ; ++i) {
    if (i >= 0x20)
      return -1;
    if ((__int16)__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 52) == a2)
      break;
  }
  return i;*/
}

//-------------------------------------------------------------------------------------------------

int sosDIGISetMasterVolume(int a1, uint16 a2)
{
  return 0;
  /*
  __writegsword(*(_DWORD *)&_lpSOSDMAFillCount[6 * a1] + 4, a2);
  return 0;*/
}

//-------------------------------------------------------------------------------------------------
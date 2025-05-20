/*
//-------------------------------------------------------------------------------------------------

void sosDIGIStart_Start()
{
  ;
}

//-------------------------------------------------------------------------------------------------

unsigned int __fastcall sosDIGIStartSample(int a1, int a2, unsigned int a3)
{
  unsigned int v3; // eax
  unsigned int v4; // ebx
  int v5; // eax
  unsigned int v6; // ebx
  unsigned int v7; // ecx
  int v8; // eax
  unsigned __int16 v9; // bx
  int v10; // eax
  unsigned int v11; // ebx
  unsigned int i; // [esp+2Ch] [ebp-4h]

  if ((unsigned int)_wSOSDriverType[a1] >= 0xE106)
    return 0;
  for (i = 0; ; ++i) {
    if (i >= 0x20)
      return -1;
    if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 48) >> 8) & 0x80u) == 0)
      break;
  }
  v3 = *(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i];
  v4 = __readgsdword(a3);
  __writegsword(v3 + 4, __readgsword(a3 + 4));
  __writegsdword(v3, v4);
  v5 = *(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i];
  v6 = __readgsdword(a3);
  __writegsword(v5 + 12, __readgsword(a3 + 4));
  __writegsdword(v5 + 8, v6);
  v7 = __readgsdword(a3 + 48) + __readgsdword(a3);
  v8 = *(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i];
  __writegsword(v8 + 20, __readgsword(a3 + 4));
  __writegsdword(v8 + 16, v7);
  if ((__readgsbyte(a3 + 40) & 0x40) != 0) {
    __writegsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 24, __readgsdword(a3 + 48));
    __writegsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 28, __readgsdword(a3 + 48));
    __writegsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 32, __readgsdword(a3 + 52));
    __writegsdword(
      *(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 44,
      __readgsdword(a3 + 44) - (__readgsdword(a3 + 52) + __readgsdword(a3 + 48)));
  } else {
    __writegsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 24, __readgsdword(a3 + 8));
    __writegsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 28, __readgsdword(a3 + 8));
  }
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 50, __readgsword(a3 + 20));
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 52, __readgsword(a3 + 24));
  v9 = __readgsword(a3 + 40);
  HIBYTE(v9) |= 0xA0u;
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 48, v9);
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 54, __readgsword(a3 + 16));
  v10 = *(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i];
  v11 = __readgsdword(a3 + 28);
  __writegsword(v10 + 64, __readgsword(a3 + 32));
  __writegsdword(v10 + 60, v11);
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 56, __readgsword(a3 + 12));
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 74, __readgsword(a3 + 36));
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 58, 0);
  __writegsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 68, __readgsdword(a3 + 56));
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 72, 0);
  __writegsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 76, 0);
  __writegsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 80, __readgsdword(a3 + 8));
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 84, __readgsword(a3 + 64));
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 86, __readgsword(a3 + 68));
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 88, __readgsword(a3 + 72));
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 90, __readgsword(a3 + 76));
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 92, __readgsword(a3 + 80));
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 94, __readgsword(a3 + 84));
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 96, __readgsword(a3 + 88));
  __writegsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 100, 0);
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * i] + 104, 0);
  return i;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIStopSample(int a1, unsigned int a2)
{
  if (a2 >= 0x20)
    return 10;
  if (((__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48) >> 8) & 0x80u) == 0
    || (__readgsbyte(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 49) & 0x10) != 0) {
    return 0;
  }
  __writegsbyte(
    *(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 49,
    __readgsbyte(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 49) & 0x7F);
  __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 52, 0);
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosDIGIContinueSample(int a1, int a2, unsigned int a3)
{
  unsigned int v3; // edx
  unsigned int v4; // ebx
  int v5; // edx
  unsigned int v6; // ebx
  unsigned int v7; // ebx
  int v8; // edx
  unsigned __int16 v9; // bx
  int v10; // eax
  unsigned int v11; // ebx

  if ((unsigned int)_wSOSDriverType[a1] < 0xE106) {
    v3 = *(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2];
    v4 = __readgsdword(a3);
    __writegsword(v3 + 4, __readgsword(a3 + 4));
    __writegsdword(v3, v4);
    v5 = *(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2];
    v6 = __readgsdword(a3);
    __writegsword(v5 + 12, __readgsword(a3 + 4));
    __writegsdword(v5 + 8, v6);
    v7 = __readgsdword(a3 + 48) + __readgsdword(a3);
    v8 = *(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2];
    __writegsword(v8 + 20, __readgsword(a3 + 4));
    __writegsdword(v8 + 16, v7);
    __writegsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 80, __readgsdword(a3 + 8));
    if ((__readgsbyte(a3 + 40) & 0x40) != 0) {
      __writegsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 24, __readgsdword(a3 + 48));
      __writegsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 28, __readgsdword(a3 + 48));
      __writegsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 32, __readgsdword(a3 + 52));
      __writegsdword(
        *(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 44,
        __readgsdword(a3 + 44) - (__readgsdword(a3 + 52) + __readgsdword(a3 + 48)));
    } else {
      __writegsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 24, __readgsdword(a3 + 8));
      __writegsdword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 28, __readgsdword(a3 + 8));
    }
    __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 52, __readgsword(a3 + 24));
    v9 = __readgsword(a3 + 40);
    HIBYTE(v9) |= 0x88u;
    __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 48, v9);
    v10 = *(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2];
    v11 = __readgsdword(a3 + 28);
    __writegsword(v10 + 64, __readgsword(a3 + 32));
    __writegsdword(v10 + 60, v11);
    __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 56, __readgsword(a3 + 12));
    __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * a1 + 6 * a2] + 74, __readgsword(a3 + 36));
  }
  return 0;
}

//-------------------------------------------------------------------------------------------------

void sosDIGIStart_End()
{
  ;
}

//-------------------------------------------------------------------------------------------------
*/
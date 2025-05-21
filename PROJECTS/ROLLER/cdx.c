#include "cdx.h"
//-------------------------------------------------------------------------------------------------

int track_playing = 0;    //000A7510
int last_audio_track = 0; //000A7514
int numCDdrives = 0;      //000A7518

//-------------------------------------------------------------------------------------------------

int FinishedAudio()
{
  return 0; /*
  int result; // eax
  char v1[20]; // [esp+0h] [ebp-14h] BYREF

  v1[0] = 12;
  WriteIOCTL(3, 11, v1);
  if ((io_variable_4 & 2) != 0)
    return 0;
  result = -1;
  track_playing = 0;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int OpenDoor()
{
  return 0; /*
  _BYTE v1[12]; // [esp+0h] [ebp-Ch] BYREF

  v1[0] = 0;
  return WriteIOCTL(12, 1, v1);*/
}

//-------------------------------------------------------------------------------------------------

void CloseDoor(int a1, int a2)
{
  /*
  char v2[12]; // [esp+0h] [ebp-Ch] BYREF

  *(_DWORD *)&v2[4] = a2;
  v2[0] = 5;
  WriteIOCTL(12, 1, v2);
  ResetDrive();*/
}

//-------------------------------------------------------------------------------------------------

void ResetDrive()
{
  ;
}

//-------------------------------------------------------------------------------------------------

int GetCDStatus()
{
  return 0; /*
  char v1; // [esp+0h] [ebp-10h] BYREF
  int v2; // [esp+1h] [ebp-Fh]

  v1 = 6;
  v2 = 0;
  WriteIOCTL(3, 5, &v1);
  printf(aStatus);
  if ((v2 & 1) != 0)
    printf(aDoorOpen);
  else
    printf(aDoorClosed);
  if ((v2 & 2) != 0)
    printf(aDoorUnlocked);
  else
    printf(aDoorLocked);
  if ((v2 & 4) != 0)
    printf(aSupportsCooked);
  else
    printf(aSupportsOnlyCo);
  if ((v2 & 8) != 0)
    printf(aReadWrite);
  else
    printf(aReadOnly);
  if ((v2 & 0x10) != 0)
    printf(aCanPlayAudioTr);
  else
    printf(aCannotPlayAudi);
  if ((v2 & 0x20) != 0)
    printf(&aOoSupportsInte[2]);
  else
    printf(&aKNoInterleavin[1]);
  if ((v2 & 0x80u) == 0)
    printf(&aAwNoPrefetchin[2]);
  else
    printf(aSupprotsPrefet);
  if ((v2 & 0x100) != 0)
    printf(aSupportsAudioC);
  else
    printf(&aCanNoAudioChan[3]);
  if ((v2 & 0x200) != 0)
    printf(aSupportsHsgAnd);
  else
    printf(&aInSupportsOnly[2]);
  fflush(&__iob_variable_1);
  return v2;*/
}

//-------------------------------------------------------------------------------------------------

int WriteIOCTL(char a1, unsigned int a2, void *a3)
{
  return 0; /*
  int v3; // edi
  int result; // eax

  io_variable_2 = a1;
  io_variable_3 = 0;
  io_variable_8 = 0;
  io = a2 + 13;
  io_variable_1 = 0;
  io_variable_5 = 0;
  io_variable_9 = 0;
  io_variable_7 = a2;
  qmemcpy((void *)cdbuffer, a3, a2);
  v3 = iobuffer;
  io_variable_6 = (cdbuffer - (__CFSHL__(cdbuffer >> 31, 4) + 16 * (cdbuffer >> 31))) >> 4 << 16;
  qmemcpy((void *)iobuffer, &io, 0x18u);
  qmemcpy((void *)(v3 + 24), &io + 24, 2u);
  memset(&RMIcd, 0, 50);
  RMIcd_variable_2 = (unsigned __int8)drive;
  RMIcd_variable_1 = 0;
  RMIcd_variable_4 = (iobuffer - (__CFSHL__(iobuffer >> 31, 4) + 16 * (iobuffer >> 31))) >> 4;
  RMIcd_variable_3 = 5392;
  intRM(47, &RMIcd);
  qmemcpy(a3, (const void *)cdbuffer, a2);
  result = 26;
  qmemcpy(&io, (const void *)iobuffer, 0x18u);
  qmemcpy(&io + 24, (const void *)(iobuffer + 24), 2u);
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int AllocDOSMemory(int a1, void *a2)
{
  return 0; /*
  memset(&sregs, 0, 12);
  regs = 256;
  regs_variable_1 = ((a1 - (__CFSHL__(a1 >> 31, 4) + 16 * (a1 >> 31))) >> 4) + 1;
  int386x(49, (int)&regs, (int)&regs, (int)&sregs);
  if (regs_variable_6) {
    *a2 = -1;
    return 0;
  } else {
    *a2 = (unsigned __int16)regs_variable_4;
    return 16 * (unsigned __int16)regs;
  }*/
}

//-------------------------------------------------------------------------------------------------

int GetAudioInfo(int a1, int a2, int a3, int a4)
{
  return 0; /*
  int v4; // ecx
  int v5; // esi
  int v6; // ebx
  int result; // eax
  int v8; // esi
  int v9; // ecx
  int v10; // edx
  int v11; // esi
  int v12; // edi
  _DWORD v13[100]; // [esp+0h] [ebp-1B4h]
  _BYTE v14[2]; // [esp+190h] [ebp-24h] BYREF
  int v15; // [esp+192h] [ebp-22h]
  char v16; // [esp+198h] [ebp-1Ch] BYREF
  unsigned __int8 v17; // [esp+199h] [ebp-1Bh]
  unsigned __int8 v18; // [esp+19Ah] [ebp-1Ah]
  int v19; // [esp+19Bh] [ebp-19h]
  int v20; // [esp+1ACh] [ebp-8h]

  v20 = a4;
  v16 = 10;
  WriteIOCTL(3, 7u, &v16);
  first_track = v17;
  v4 = v17;
  last_track = v18;
  if (v17 <= (int)v18) {
    v5 = v17;
    do {
      v14[0] = 11;
      v14[1] = v4;
      WriteIOCTL(3, 7u, v14);
      ++v5;
      ++v4;
      v13[v5] = (unsigned __int8)v15 + 4500 * (v15 >> 16) + 75 * BYTE1(v15) - 150;
      v6 = last_track;
      thevtoc[v5] = v15;
    } while (v4 <= v6);
  }
  result = last_track;
  v8 = 4 * last_track;
  v13[last_track + 2] = 4500 * (v19 >> 16) + 75 * BYTE1(v19) + (unsigned __int8)v19 - 150;
  v9 = first_track;
  if (first_track <= result) {
    result = 4 * first_track;
    v10 = v8;
    do {
      v11 = *(_DWORD *)((char *)&v13[2] + result);
      v12 = *(_DWORD *)((char *)&v13[1] + result);
      result += 4;
      ++v9;
      *(int *)((char *)&sector_size + result) = v11 - v12;
    } while (result <= v10);
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int PlayTrack(int a1)
{
  return 0; /*
  int result; // eax

  play_variable_4 = 1;
  play_variable_5 = trackstarts[a1];
  play_variable_6 = tracklengths[a1];
  AudioIOCTL(132, -1);
  track_playing = -1;
  result = tracklengths[a1];
  last_audio_track = a1;
  track_duration = result;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int PlayTrack4(int a1)
{
  return 0; /*
  int v2; // ebx
  int v3; // ecx
  int v4; // ecx
  int v5; // ebx
  int result; // eax

  v2 = tracklengths[a1];
  v3 = tracklengths_variable_1[a1];
  play_variable_4 = 1;
  v4 = v3 + v2 + tracklengths_variable_2[a1];
  v5 = tracklengths_variable_3[a1];
  play_variable_5 = trackstarts[a1];
  track_duration = v5 + v4;
  play_variable_6 = v5 + v4;
  result = AudioIOCTL(132, a1);
  track_playing = -1;
  last_audio_track = a1;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int RepeatTrack()
{
  return 0; /*
  int result; // eax

  play_variable_4 = 1;
  play_variable_5 = trackstarts[last_audio_track];
  play_variable_6 = track_duration;
  result = AudioIOCTL(132, -1);
  track_playing = -1;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int StopTrack()
{
  return 0; /*
  int result; // eax

  result = AudioIOCTL(133, 0);
  track_playing = 0;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int SetAudioVolume(int a1)
{
  return 0; /*
  int v1; // eax
  _BYTE v3[20]; // [esp+0h] [ebp-14h] BYREF

  v1 = 2 * a1;
  if (v1 < 1)
    v1 = 1;
  if (v1 > 255)
    LOBYTE(v1) = -1;
  v3[2] = v1;
  v3[4] = v1;
  v3[6] = v1;
  v3[8] = v1;
  v3[0] = 3;
  v3[1] = 0;
  v3[3] = 1;
  v3[5] = 2;
  v3[7] = 3;
  return WriteIOCTL(12, 9u, v3);*/
}

//-------------------------------------------------------------------------------------------------

int AudioIOCTL(char a1)
{
  return 0; /*
  int v1; // edi
  int result; // eax

  v1 = iobuffer;
  play_variable_2 = a1;
  play = 22;
  play_variable_1 = 0;
  play_variable_3 = 0;
  qmemcpy((void *)iobuffer, &play, 0x14u);
  qmemcpy((void *)(v1 + 20), &play + 20, 2u);
  memset(&RMIcd, 0, 50);
  RMIcd_variable_2 = (unsigned __int8)drive;
  RMIcd_variable_3 = 5392;
  RMIcd_variable_4 = (iobuffer - (__CFSHL__(iobuffer >> 31, 4) + 16 * (iobuffer >> 31))) >> 4;
  RMIcd_variable_1 = 0;
  intRM(47, &RMIcd);
  result = 22;
  qmemcpy(&play, (const void *)iobuffer, 0x14u);
  qmemcpy(&play + 20, (const void *)(iobuffer + 20), 2u);
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int FreeDOSMemory(unsigned __int16 a1)
{
  return 0; /*
  memset(&sregs, 0, sizeof(sregs));
  regs.w.dx = a1;
  regs.w.ax = 257;
  return int386x(49, &regs, &regs, &sregs);*/
}

//-------------------------------------------------------------------------------------------------

int intRM(unsigned __int8 a1)
{
  return 0; /*
  regs.w.ax = 768;
  regs.w.bx = a1;
  regs.w.cx = 0;
  sregs.es = __DS__;
  regs.x.edi = (unsigned int)&RMIcd;
  return int386x(49, &regs, &regs, &sregs);*/
}

//-------------------------------------------------------------------------------------------------

int GetFirstCDDrive()
{
  return 0; /*
  regs = 5376;
  regs_variable_1 = 0;
  int386(47, (int)&regs, (int)&regs);
  if (!regs_variable_1)
    return 0;
  drive = regs_variable_3;
  firstCDdrive = (unsigned __int8)regs_variable_3;
  numCDdrives = regs_variable_1;
  return -1;*/
}

//-------------------------------------------------------------------------------------------------

void cdxinit()
{/*
  int v0; // edx
  double v1; // st7
  __int16 v2; // fps
  _BOOL1 v3; // c0
  char v4; // c2
  _BOOL1 v5; // c3
  int v6; // eax
  float v7; // [esp+0h] [ebp-14h]
  int i; // [esp+4h] [ebp-10h]

  iobuffer = AllocDOSMemory(256, &ioselector);
  v0 = 0;
  cdbuffer = AllocDOSMemory(1024, &cdselector);
  for (i = 0; i < 129; ++i) {
    v1 = cdx_c_variable_21;
    IF_POW(cdx_c_variable_21);
    v3 = v1 < cdx_c_variable_22;
    v4 = 0;
    v5 = v1 == cdx_c_variable_22;
    LOWORD(v6) = v2;
    if (v1 > cdx_c_variable_22) {
      v0 = i;
      volscale[i] = 127;
    } else {
      _CHP(v6, v0);
      v0 = i;
      v7 = v1;
      volscale[i] = (int)v7;
    }
  }*/
}

//-------------------------------------------------------------------------------------------------

int cdxdone()
{
  return 0; /*
  __int16 v0; // cx
  __int16 v1; // cx

  v0 = cdselector;
  memset(&sregs, 0, 12);
  regs_variable_4 = v0;
  regs = 257;
  int386x(49, (int)&regs, (int)&regs, (int)&sregs);
  v1 = ioselector;
  memset(&sregs, 0, 12);
  regs_variable_4 = v1;
  regs = 257;
  return int386x(49, (int)&regs, (int)&regs, (int)&sregs);*/
}

//-------------------------------------------------------------------------------------------------

int cdpresent()
{
  return 0; /*
  int result; // eax
  int i; // edx

  result = 0;
  for (i = 0; i < numCDdrives; ++i) {
    if (!result)
      result = checkCD(i + firstCDdrive);
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int checkCD(char a1, int a2, int a3, int a4)
{
  return 0; /*
  int result; // eax
  int v5; // esi
  int v6; // edx
  char v7; // [esp+0h] [ebp-8Ch] BYREF
  char v8[99]; // [esp+1h] [ebp-8Bh] BYREF
  _BYTE v9[32]; // [esp+64h] [ebp-28h] BYREF
  int v10; // [esp+84h] [ebp-8h]

  v10 = a4;
  v7 = a1 + 65;
  strcpy(v8, ":\\FATAL.EXE");
  result = fopen(&v7, aRb_1);
  v5 = result;
  if (result) {
    v6 = fread(v9, 1, 20, result);
    fclose(v5);
    if (v6 == 20)
      return -1;
    else
      return 0;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int criticalhandler()
{
  return 0; /*
  _BYTE retaddr[8]; // [esp+0h] [ebp+0h]

  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(3);*/
}

//-------------------------------------------------------------------------------------------------
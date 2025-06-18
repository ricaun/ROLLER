#include "cdx.h"
#include "roller.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#ifdef IS_WINDOWS
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/cdrom.h>
#include <unistd.h>
#include <sys/ioctl.h>
#endif
//-------------------------------------------------------------------------------------------------

int track_playing = 0;    //000A7510
int last_audio_track = 0; //000A7514
int numCDdrives = 0;      //000A7518
int firstCDdrive;         //001A1B4C
void *iobuffer;           //001A1CEC
void *cdbuffer;           //001A1CF0
int16 ioselector;         //001A1E88
int16 cdselector;         //001A1E8C
int drive;                //001A1F9F
char volscale[129];       //001A1F1E

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

void GetCDStatus()
{
  uint8 szBuf[16]; // [esp+0h] [ebp-10h] BYREF
  memset(szBuf, 0, sizeof(szBuf));

  szBuf[0] = 6;
  WriteIOCTL(3u, 5u, szBuf);
  printf("\n\nStatus:\n");
  if ((szBuf[1] & 1) != 0)
    printf("\nDoor Open");
  else
    printf("\nDoor Closed");
  if ((szBuf[1] & 2) != 0)
    printf("\nDoor unlocked");
  else
    printf("\nDoor locked");
  if ((szBuf[1] & 4) != 0)
    printf("\nSupports Cooked and Raw");
  else
    printf("\nSupports only Cooked");
  if ((szBuf[1] & 8) != 0)
    printf("\nRead/Write");
  else
    printf("\nRead only");
  if ((szBuf[1] & 0x10) != 0)
    printf("\nCan play Audio tracks");
  else
    printf("\nCannot play Audio tracks");
  if ((szBuf[1] & 0x20) != 0)
    printf("\nSupports interleaving");
  else
    printf("\nNo interleaving");
  if ((szBuf[1] & 0x80u) == 0)
    printf("\nNo prefetching");
  else
    printf("\nSupprots prefetching");
  if ((szBuf[2] & 1) != 0)
    printf("\nSupports audio channel manipulation");
  else
    printf("\nNo audio channel manipulation");
  if ((szBuf[2] & 2) != 0)
    printf("\nSupports HSG and Red Book addressing");
  else
    printf("\nSupports only HSG addressing, no Red Book");
  fflush(stdout);
}

//-------------------------------------------------------------------------------------------------

void WriteIOCTL(uint8 bySubCommand, unsigned int uiSize, void *pBuffer)
{
  /*
  char *v3; // edi

  io_variable_2 = bySubCommand;
  io_variable_3 = 0;
  io_variable_8 = 0;
  io = uiSize + 13;
  io_variable_1 = 0;
  io_variable_5 = 0;
  io_variable_9 = 0;
  io_variable_7 = uiSize;
  qmemcpy(cdbuffer, pBuffer, uiSize);
  v3 = (char *)iobuffer;
  io_variable_6 = (int)((char *)cdbuffer - __CFSHL__((int)cdbuffer >> 31, 4) + -16 * ((int)cdbuffer >> 31)) >> 4 << 16;
  qmemcpy(iobuffer, &io, 0x18u);
  qmemcpy(v3 + 24, &io + 24, 2u);
  memset(&RMIcd, 0, sizeof(RMIcd));
  RMIcd.ecx = (unsigned __int8)drive;
  RMIcd.ebx = 0;
  RMIcd.es = (int)((char *)iobuffer - __CFSHL__((int)iobuffer >> 31, 4) + -16 * ((int)iobuffer >> 31)) >> 4;
  RMIcd.eax = 5392;
  intRM(0x2Fu);
  qmemcpy(pBuffer, cdbuffer, uiSize);
  qmemcpy(&io, iobuffer, 0x18u);
  qmemcpy(&io + 24, (char *)iobuffer + 24, 2u);*/
}

//-------------------------------------------------------------------------------------------------

void *AllocDOSMemory(int iSizeBytes, int16 *pOutSegment)
{
  pOutSegment = NULL;
  return malloc(iSizeBytes);

  //memset(&sregs, 0, sizeof(sregs));             // clear sregs
  //regs.w.ax = 0x100;                            // allocate DOS memory block
  //regs.w.bx = ((iSizeBytes - (__CFSHL__(iSizeBytes >> 31, 4) + 16 * (iSizeBytes >> 31))) >> 4) + 1;// compute number of 16-byte paragraphs needed to hold iSizeBytes
  //int386x(0x31, &regs, &regs, &sregs);
  //
  //// if carry flag is set, alloc failed
  //if (regs.x.cflag) {
  //  *(_DWORD *)pOutSegment = -1;
  //  return 0;
  //} else {
  //  // alloc succeeded
  //  *(_DWORD *)pOutSegment = regs.w.dx;
  //  return (void *)(16 * regs.w.ax);
  //}
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

void RepeatTrack()
{/*
  play.subCmd.reserved2[8] = 1;
  play.subCmd.start_lba = trackstarts[last_audio_track];
  play.subCmd.duration = track_duration;
  AudioIOCTL(0x84u);
  track_playing = -1;*/
}

//-------------------------------------------------------------------------------------------------

void StopTrack()
{
  AudioIOCTL(0x85); //stop track
  track_playing = 0;
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

void AudioIOCTL(uint8 bySubCommand)
{
  /*
  char *pIoBuffer; // edi

  pIoBuffer = (char *)iobuffer;
  play_variable_2 = bySubCommand;
  play = 0x16;                                  // Send Audio Command
  play_variable_1 = 0;
  play_variable_3 = 0;
  qmemcpy(iobuffer, &play, 0x14u);
  qmemcpy(pIoBuffer + 20, (char *)&play + 20, 2u);
  memset(&RMIcd, 0, sizeof(RMIcd));
  RMIcd.ecx = (unsigned __int8)drive;           // CD drive number
  RMIcd.eax = 0x1510;                           //  (Function: Get CD-ROM Drive Information)
  RMIcd.es = (int)((char *)iobuffer - __CFSHL__((int)iobuffer >> 31, 4) + -16 * ((int)iobuffer >> 31)) >> 4;// segment_of(iobuffer)
  RMIcd.ebx = 0;
  intRM(0x2Fu);                                 // Get address of the driver for a specific CD-ROM drive
  qmemcpy(&play, iobuffer, 0x14u);
  qmemcpy((char *)&play + 20, (char *)iobuffer + 20, 2u);*/
}

//-------------------------------------------------------------------------------------------------

void FreeDOSMemory(uint16 unSegment)
{
  //memset(&sregs, 0, sizeof(sregs));
  //regs.w.dx = nSegment;
  //regs.w.ax = 0x101;
  //int386x(0x31, &regs, &regs, &sregs);
}

//-------------------------------------------------------------------------------------------------

void intRM(uint8 byInterruptNumber)
{
  /*
  regs.w.ax = 768;                              // DPMI: Simulate Real Mode Interrupt
  regs.w.bx = byInterruptNumber;                // Interrupt number to simulate
  regs.w.cx = 0;                                // Reserved
  sregs.es = __DS__;                            // Segment of RMIcd
  regs.x.edi = (unsigned int)&RMIcd;            // Offset of RMIcd (real mode register set)
  int386x(0x31, &regs, &regs, &sregs);*/
}

//-------------------------------------------------------------------------------------------------

void GetFirstCDDrive()
{
  firstCDdrive = -1;
#ifdef IS_WINDOWS
  uint32 uiDrives = GetLogicalDrives();
  if (uiDrives == 0)
    return;

  int iCount = 0;
  for (char cDrive = 'A'; cDrive <= 'Z'; cDrive++) {
    if (!(uiDrives & (1 << (cDrive - 'A'))))
      continue;

    char szRootPath[] = { cDrive, ':', '\\', '\0' };
    uint32 uiType = GetDriveTypeA(szRootPath);
    if (uiType == DRIVE_CDROM) {
      if (firstCDdrive == -1) {
        firstCDdrive = cDrive - 'A';
        drive = cDrive - 'A';
      }
      iCount++;
    }
  }

  numCDdrives = iCount;
#else
  const char *szDevPrefix = "/dev/";
  const char *targets[] = { "cdrom", "sr0", "sr1", "sr2", "sr3", NULL };
  int iCount = 0;

  for (int i = 0; targets[i] != NULL; ++i) {
    char fullPath[64];
    snprintf(fullPath, sizeof(fullPath), "%s%s", szDevPrefix, targets[i]);
    if (IsCDROMDevice(fullPath)) {
      if (firstCDdrive == -1) {
        firstCDdrive = i;
        drive = i;
      }
      iCount++;
    }
  }

  numCDdrives = iCount;
#endif
  /*
  regs.w.ax = 0x1500;
  regs.w.bx = 0;
  int386(47, &regs, &regs);
  if (regs.w.bx) {
    drive = regs.h.cl;
    firstCDdrive = regs.h.cl;
    numCDdrives = regs.w.bx;
  }*/
}

//-------------------------------------------------------------------------------------------------

void cdxinit()
{
  iobuffer = AllocDOSMemory(256, &ioselector);
  cdbuffer = AllocDOSMemory(1024, &cdselector);

  // Initialize the volume scaling table
  for (int i = 0; i < 129; i++) {
    double dPow = pow(i * 127.0 * 127.0, 1.0 / 3.0);

    if (dPow <= 127.0f) {
      float fPow = (float)dPow;
      volscale[i] = (uint8)round(fPow);
    } else {
      volscale[i] = 127;  // Cap to 127 if over the limit
    }
  }
}
//-------------------------------------------------------------------------------------------------

void cdxdone()
{
  free(cdbuffer);
  free(iobuffer);
  cdbuffer = NULL;
  iobuffer = NULL;

  //memset(&sregs, 0, sizeof(sregs));
  //regs.w.dx = cdselector;
  //regs.w.ax = 257;
  //int386x(49, &regs, &regs, &sregs);
  //memset(&sregs, 0, sizeof(sregs));
  //regs.w.dx = ioselector;
  //regs.w.ax = 257;
  //int386x(49, &regs, &regs, &sregs);
}

//-------------------------------------------------------------------------------------------------

int cdpresent()
{
  int iSuccess = 0;

  for (int i = 0; i < numCDdrives; ++i) {
    if (!iSuccess)
      iSuccess = checkCD(i + firstCDdrive);
  }
  return iSuccess;
}

//-------------------------------------------------------------------------------------------------

int checkCD(uint8 byDriveIdx)
{
  char szFilename[128];
  char buffer[20];
  FILE *fp;
  uint32 uiBytesRead;

  // Construct filename
  //TODO: linux compatibility
  sprintf(szFilename, "%c:/FATAL.EXE", byDriveIdx + 'A');

  // Try to open the file
  fp = ROLLERfopen(szFilename, "rb");
  if (!fp)
    return 0;

  // Read 20 bytes
  uiBytesRead = (int)fread(buffer, 1, 20, fp);
  fclose(fp);

  // Return -1 if read was exactly 20 bytes, else 0
  return (uiBytesRead == 20) ? -1 : 0;
}

//-------------------------------------------------------------------------------------------------

int criticalhandler()
{
  return 3;
  /*
  _BYTE retaddr[8]; // [esp+0h] [ebp+0h]

  // returning 3 is sending a signal "Ignore" to DOS critical error handler
  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(3);*/
}

//-------------------------------------------------------------------------------------------------

#ifndef _ROLLER_CDX_H
#define _ROLLER_CDX_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

extern int track_playing;
extern int last_audio_track;
extern int numCDdrives;
extern int firstCDdrive;
extern void *iobuffer;
extern void *cdbuffer;
extern int16 ioselector;
extern int16 cdselector;
extern char volscale[129];

//-------------------------------------------------------------------------------------------------

int FinishedAudio();
int OpenDoor();
void CloseDoor(int a1, int a2);
void ResetDrive();
void GetCDStatus();
void WriteIOCTL(uint8 bySubCommand, unsigned int uiSize, void *pBuffer);
void *AllocDOSMemory(int iSizeBytes, int16 *pOutSegment);
int GetAudioInfo(int a1, int a2, int a3, int a4);
int PlayTrack(int a1);
int PlayTrack4(int a1);
void RepeatTrack();
void StopTrack();
int SetAudioVolume(int a1);
void AudioIOCTL(uint8 bySubCommand);
int FreeDOSMemory(uint16 a1);
void intRM(uint8 byInterruptNumber);
void GetFirstCDDrive();
void cdxinit();
void cdxdone();
int cdpresent();
int checkCD(uint8 byDriveIdx);
int criticalhandler();

//-------------------------------------------------------------------------------------------------
#endif

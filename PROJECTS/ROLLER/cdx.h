#ifndef _ROLLER_CDX_H
#define _ROLLER_CDX_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

extern int track_playing;
extern int last_audio_track;
extern int numCDdrives;

//-------------------------------------------------------------------------------------------------

int FinishedAudio();
int OpenDoor();
void CloseDoor(int a1, int a2);
void ResetDrive();
void GetCDStatus();
void WriteIOCTL(uint8 bySubCommand, unsigned int uiSize, void *pBuffer);
int AllocDOSMemory(int a1, void *a2);
int GetAudioInfo(int a1, int a2, int a3, int a4);
int PlayTrack(int a1);
int PlayTrack4(int a1);
void RepeatTrack();
void StopTrack();
int SetAudioVolume(int a1);
void AudioIOCTL(uint8 bySubCommand);
int FreeDOSMemory(unsigned __int16 a1);
void intRM(uint8 byInterruptNumber);
void GetFirstCDDrive();
void cdxinit();
int cdxdone();
int cdpresent();
int checkCD(char a1, int a2, int a3, int a4);
int criticalhandler();

//-------------------------------------------------------------------------------------------------
#endif
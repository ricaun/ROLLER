#ifndef _ROLLER_CDX_H
#define _ROLLER_CDX_H
//-------------------------------------------------------------------------------------------------

int FinishedAudio();
int OpenDoor();
void CloseDoor(int a1, int a2);
void ResetDrive();
int GetCDStatus();
int WriteIOCTL(char a1, unsigned int a2, void *a3);
int AllocDOSMemory(int a1, void *a2);
int GetAudioInfo(int a1, int a2, int a3, int a4);
int PlayTrack(int a1);
int PlayTrack4(int a1);
int RepeatTrack();
int StopTrack();
int SetAudioVolume(int a1);
int AudioIOCTL(char a1);
int FreeDOSMemory(unsigned __int16 a1);
int intRM(unsigned __int8 a1);
int GetFirstCDDrive();
void cdxinit();
int cdxdone();
int cdpresent();
int checkCD(char a1, int a2, int a3, int a4);
int criticalhandler();

//-------------------------------------------------------------------------------------------------
#endif
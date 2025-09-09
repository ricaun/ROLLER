#ifndef _ROLLER_SOSCNTL_H
#define _ROLLER_SOSCNTL_H
//-------------------------------------------------------------------------------------------------
#include "../../../../PROJECTS/ROLLER/types.h"
//-------------------------------------------------------------------------------------------------

void sosDIGICntl_Start();
unsigned int sosDIGIGetDMAPosition(int a1);
int sosDIGISetSampleVolume(int a1, int a2, uint16 a3);
int sosDIGIGetSampleVolume(int a1, int a2);
int sosDIGISetChannel(int a1, int a2, uint16 a3);
int sosDIGIGetChannel(int a1, int a2);
unsigned int sosDIGIGetBytesProcessed(int a1, int a2);
int sosDIGIGetLoopCount(int a1, int a2);
int sosDIGISetPanLocation(int a1, int a2, uint16 a3);
int sosDIGIGetPanLocation(int a1, int a2);
int sosDIGISetPanSpeed(int a1, int a2, uint16 a3);
int sosDIGIGetPanSpeed(int a1, int a2);
unsigned int sosDIGISetPitch(int a1, int a2, unsigned int a3);
unsigned int sosDIGIGetPitch(int a1, int a2);
int sosDIGIGetSampleID(int a1, int a2);
unsigned int sosDIGIGetSampleHandle(int a1, int a2);
int sosDIGISetMasterVolume(int a1, uint16 a2);

//-------------------------------------------------------------------------------------------------
#endif
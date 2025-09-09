#ifndef _ROLLER_SOSMWAVE_H
#define _ROLLER_SOSMWAVE_H
//-------------------------------------------------------------------------------------------------
#include "../../../../PROJECTS/ROLLER/types.h"
//-------------------------------------------------------------------------------------------------

#pragma pack(push, 2)
typedef struct
{
  uint8 byPlaying;
  uint8 byMidiNote;
  uint8 byBaseNote;
  uint8 byReserved;
  int iPitchValue;
  int iMidiChannel;
  int iVelocity;
  int iQueueHandle;
} tWaveVoice;
#pragma pack(pop)

//-------------------------------------------------------------------------------------------------

#pragma pack(push, 2)
typedef struct
{
  uint8 byProgram;
  uint8 byVolume;
  uint8 byPitchBend;
  uint8 byController102;
  uint8 bySustainPedal;
  uint8 byPanPosition;
} tWaveChannel;
#pragma pack(pop)

//-------------------------------------------------------------------------------------------------

extern int dwWAVEPitchTable[180];
extern tWaveVoice waveVoice[32];
extern tWaveChannel waveChannel[16];

//-------------------------------------------------------------------------------------------------

int waveSendData(unsigned int a1, int a2, int a3, int a4);
int *waveGetCallTable();
int waveInit(unsigned int a1, int a2, int a3);
int waveUnInit(int a1, int a2, int a3, int a4);
int waveReset(int a1, int a2, int a3);
int waveSetInstrumentData(int a1, int16 a2);
int waveSampleCallback(int a1, int a2, int a3);
int sosWAVEPStopSample(int a1, int a2);
int waveChannelResetControllers(uint8 a1, int a2);
int waveChannelSetVolume(uint8 a1, int a2);
int waveChannelSetPan(uint8 a1, int a2);
void waveChannelSetBend(uint8 byMidiChannel, int iDriverIdx);
int waveChannelNotesOff(uint8 a1, int a2);
uint8 *StringOut(uint8 a1, uint8 a2, uint8 *a3, uint8 a4);
unsigned int waveCalculatePitchBend(uint8 byMidiChannel, int iBasePitch, unsigned int uiMidiNote, unsigned int uiBaseNote);
int64 waveGetBestSample(int a1, uint8 a2);

//-------------------------------------------------------------------------------------------------
#endif
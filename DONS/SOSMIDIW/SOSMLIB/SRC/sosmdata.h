#ifndef _ROLLER_SOSMDATA_H
#define _ROLLER_SOSMDATA_H
//-------------------------------------------------------------------------------------------------
#include "../../../../PROJECTS/ROLLER/types.h"
//-------------------------------------------------------------------------------------------------

typedef struct
{
  int iSampleHandle;
  int iMidiNote;
  int iVelocity;
  int iMidiChannel;
} tMIDIDIGIQueue;

//-------------------------------------------------------------------------------------------------

extern tMIDIDIGIQueue _sMIDIDIGIQueue[5][32];
extern int _wMIDIDIGISampleQueueHead[5];
extern int _wMIDIDIGISampleQueueTail[5];
extern int _wMIDIDIGIDriverHandle[5];

//-------------------------------------------------------------------------------------------------
#endif
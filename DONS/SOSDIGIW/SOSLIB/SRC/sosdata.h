#ifndef _ROLLER_SOSDATA_H
#define _ROLLER_SOSDATA_H
//-------------------------------------------------------------------------------------------------
#include "../../../../PROJECTS/ROLLER/types.h"
//-------------------------------------------------------------------------------------------------

#pragma pack(push, 2)
typedef struct
{
  uint8 *pSample;

  //unused, purely to maintain 16-bit alignment
  uint8 byReserved1;
  uint8 byReserved2;
} tSOSSampleEntry;
#pragma pack(pop)

//-------------------------------------------------------------------------------------------------

extern tSOSSampleEntry _lpSOSSampleList[5][32];

//-------------------------------------------------------------------------------------------------
#endif
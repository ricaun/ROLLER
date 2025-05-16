#ifndef _ROLLER_3D_H
#define _ROLLER_3D_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

typedef struct
{
  void *pBuf;
  uint32 uiSize;
  void *pAlsoBuf; //seems to be set to the same thing as pBuf in W95
  int iRegsDi;    //unused by W95
} tMemBlock;

//-------------------------------------------------------------------------------------------------

extern uint32 textures_off;

//-------------------------------------------------------------------------------------------------

void * malloc2(int iSize, void *pPtr, int *pRegsDi);
void free2(void *ptr);
void doexit(int a1, int a2, void *pBuf);
 
//-------------------------------------------------------------------------------------------------
#endif
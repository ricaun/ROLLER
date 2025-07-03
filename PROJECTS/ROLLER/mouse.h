#ifndef _ROLLER_MOUSE_H
#define _ROLLER_MOUSE_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

void initmouse();
void mousexy();
int mousebut(uint16 unMask);
void checkmouse();
void drmouse(int iX0, int iY0, uint8 *pData, uint8 *pScreenBase);
void plotmouse();

//-------------------------------------------------------------------------------------------------
#endif

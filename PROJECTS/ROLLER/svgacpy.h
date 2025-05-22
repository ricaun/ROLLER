#ifndef _ROLLER_SVGACPY_H
#define _ROLLER_SVGACPY_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

int vesastart(int a1, int a2);
int tryvesa(int a1, int a2, int a3, int a4);
int VESASource(int a1, int a2, int a3);
int VESADest(int a1, int a2, int a3);
int VESAmode(int *vesaModes, int iSvgaPossible);
int svgacopy(uint8 *pBuf, __int16 a2, __int16 a3, int a4, int a5);

//-------------------------------------------------------------------------------------------------
#endif
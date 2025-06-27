#ifndef _ROLLER_SVGACPY_H
#define _ROLLER_SVGACPY_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

extern int Vbytesperline;
extern int winrange;

//-------------------------------------------------------------------------------------------------

int vesastart(uint32 uiX, uint32 uiY);
int tryvesa(int a1, int a2, int a3, int a4);
int VESASource(int a1, int a2, int a3);
int VESADest(int a1, int a2, int a3);
int VESAmode(int *vesaModes, int iSvgaPossible);
void svgacopy(uint8 *pSrc, int16 iX, int16 iY, int iWidth, int iHeight);

//-------------------------------------------------------------------------------------------------
#endif

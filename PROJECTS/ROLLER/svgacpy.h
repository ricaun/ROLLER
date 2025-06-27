#ifndef _ROLLER_SVGACPY_H
#define _ROLLER_SVGACPY_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

extern int Vbytesperline;
extern int winrange;

//-------------------------------------------------------------------------------------------------

int vesastart(int iX, int iY);
int tryvesa(int iModeNumber);
void *VESASource(int iX, int iY, int iOffset);
void *VESADest(int iX, int iY, int iOffset);
int VESAmode(int *vesaModes, int iSvgaPossible);
void svgacopy(uint8 *pSrc, int16 iX, int16 iY, int iWidth, int iHeight);

//-------------------------------------------------------------------------------------------------
#endif

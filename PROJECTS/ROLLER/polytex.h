#ifndef _ROLLER_POLYTEX_H
#define _ROLLER_POLYTEX_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
#include "polyf.h"
//-------------------------------------------------------------------------------------------------

extern fixed16_16 startsx[4];
extern fixed16_16 startsy[4];
extern int texture_back[4608];
extern uint8 *scrptr;
extern uint8 *scrptr1;
extern uint8 *mapsel[4884];

//-------------------------------------------------------------------------------------------------

void remove_mapsels();
void setmapsel(uint8 *pBase, int iIndex, int iMode, int iCount);
int twpolym(void *a1, int16 a2);
void POLYTEX(uint8 *pTexture, uint8 *pScrBuf, tPolyParams *pPolyParams, int iTexIdx, int iGfxSize);
char polym(int *a1, int a2, int a3);
int polyt(int result, int a2, int a3);

//-------------------------------------------------------------------------------------------------
#endif

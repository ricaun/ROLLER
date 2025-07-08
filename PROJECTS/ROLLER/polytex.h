#ifndef _ROLLER_POLYTEX_H
#define _ROLLER_POLYTEX_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

extern fixed16_16 startsx[4];
extern fixed16_16 startsy[4];
extern uint8 *scrptr;

//-------------------------------------------------------------------------------------------------

int remove_mapsels();
int setmapsel(int iBase, int iIndex, int iMode, int iCount);
int twpolym(void *a1, int16 a2);
char POLYTEX(int a1, int a2, int *a3, int a4, int a5);
char polym(int *a1, int a2, int a3);
int polyt(int result, int a2, int a3);

//-------------------------------------------------------------------------------------------------
#endif

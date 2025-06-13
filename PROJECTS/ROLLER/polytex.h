#ifndef _ROLLER_POLYTEX_H
#define _ROLLER_POLYTEX_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

extern float startsx[4];
extern float startsy[4];

//-------------------------------------------------------------------------------------------------

int remove_mapsels();
int setmapsel(int a1, int a2, int a3, int a4);
int twpolym(void *a1, int16 a2);
char POLYTEX(int a1, int a2, int *a3, int a4, int a5);
char polym(int *a1, int a2, int a3);
int polyt(int result, int a2, int a3);

//-------------------------------------------------------------------------------------------------
#endif

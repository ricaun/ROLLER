#ifndef _ROLLER_MOVING_H
#define _ROLLER_MOVING_H
//-------------------------------------------------------------------------------------------------

void *initramp(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);
int reinitramp(float *a1);
int updateramp(int result);
int updatestunts();
int reinitstunts();
void *freeramp(void *result);
void freestunts(int a1, int a2, int a3, int a4);

//-------------------------------------------------------------------------------------------------
#endif
#ifndef _ROLLER_FUNCTION_H
#define _ROLLER_FUNCTION_H
//-------------------------------------------------------------------------------------------------
#include "3d.h"
#include <stdbool.h>
//-------------------------------------------------------------------------------------------------

void finish_race();
double getbankz(float fInput, int iChunkIdx, tData *pData);
int calculate_aheadbehindtime(int a1, float *a2, float *a3);
int initnearcars();
void initpits();
void dodamage(int a1, float a2);
void doviewtend(int a1, int a2, int a3);
int changemateto(int result, int a2);
bool linevalid(int iChunkIdx, float fStartCoord, float fEndCoord);
void analysefalloff(int a1);
int showmap(int a1, int a2);
int firework_display();

//-------------------------------------------------------------------------------------------------
#endif

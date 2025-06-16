#ifndef _ROLLER_CONTROL_H
#define _ROLLER_CONTROL_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
#include "engines.h"
#include "car.h"

//-------------------------------------------------------------------------------------------------

extern int level;
extern float eng_chg_revs[168];
extern int JBYmax;
extern int JBYmin;
extern int JBXmin;
extern int JBXmax;
extern int JAYmax;
extern int JAXmax;
extern int JAYmin;
extern int JAXmin;
extern float RecordLaps[25];
extern int RecordCars[25];
extern int RecordKills[25];
extern char RecordNames[228];

//-------------------------------------------------------------------------------------------------

void humancar(int a1);
void GoUpGear(int a1);
void GoDownGear(int a1, int a2);
void control();
double calc_revs(tRev *pRevs, int iGear, float fChg);
double calc_pow(int iCarDesignIdx, int iGearAyMax, float a3);
void Accelerate(float *a1);
int Decelerate(int a1);
int FreeWheel(int a1);
void SetEngine(int a1, float a2);
double change_gear(int a1, int a2, int a3, int a4);
void updatecar2(int a1, int a2, int a3);
int16 check_crossed_line(int a1);
char checkplacement(int a1);
int testteaminit(int a1);
int doteaminit();
int16 hitleft(int a1, int a2, int a3);
int16 hitright(int a1, int a2, int a3);
int scansection(tCar *pCar);
double getgroundz(float a1, float a2, int iChunkIdx);
double getroadz(float a1, float a2, int iChunkIdx);
int16 putflat(tCar *pCar);
float *findnearcars(float *a1, float *a2, float *a3, float *a4, float *a5, float *a6, float *a7);
int findnearcarsforce(int a1, int *a2, float *a3, int *a4, void *a5, float *a6, float *a7);
double interpolatesteer(float a1, float a2, float a3, int a4, int a5);
double avoid(int a1, int a2, float a3, int a4, float a5, float a6, void *a7);
double block(int a1, float a2, int a3, float a4, float a5);
void autocar2(int a1);
void changestrategy(int a1);
int getangle(float fX, float fY);
void landontrack(int a1);
int16 converttoair(int a1, int a2, int a3, int a4);
void ordercars();
void changeline(int a1);
unsigned int driverange(int a1, float *a2, float *a3);
int updatesmokeandflames(int a1, unsigned int a2, int a3, unsigned int a4);
void dospray(int64 a1, int a2);
int calculateseparatedcoordinatesystem(int a1, int a2);
int *findnearsection(int a1, int *a2);
void dozoomstuff(int a1);
int findcardistance(int a1, float a2);

//-------------------------------------------------------------------------------------------------
#endif

#ifndef _ROLLER_CONTROL_H
#define _ROLLER_CONTROL_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
#include "engines.h"
//-------------------------------------------------------------------------------------------------

extern float eng_chg_revs[];
extern float RecordLaps[];
extern int RecordCars[];
extern int RecordKills[];
extern char RecordNames[];

double calc_revs(tRev *pRevs, int iGear, float fChg);
int getangle(float fX, float fY);

//-------------------------------------------------------------------------------------------------
#endif
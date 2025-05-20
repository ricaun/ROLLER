#ifndef _ROLLER_COLISION_H
#define _ROLLER_COLISION_H
//-------------------------------------------------------------------------------------------------
#include "car.h"
//-------------------------------------------------------------------------------------------------

void testcollisions();
void testcoll(tCar *pCar1, tCar *pCar2, int a3);
void initcollisions();
int checkintersect(
        double a1,
        double a2,
        double dAngleIdx1,
        double a4,
        double a5,
        double dAngleIdx2,
        long double ldCarBaseX,
        long double ldCarBaseY);

//-------------------------------------------------------------------------------------------------
#endif
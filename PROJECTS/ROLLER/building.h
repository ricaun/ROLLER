#ifndef _ROLLER_BUILDING_H
#define _ROLLER_BUILDING_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

extern float BuildingAngles[768];
extern int BuildingBase[1024];
extern int16 advert_list[256];
extern int NumBuildings;
extern int NumVisibleBuildings;

//-------------------------------------------------------------------------------------------------

void InitBuildings();
int CalcVisibleBuildings();
void DrawBuilding(int a1, int a2);
void init_animate_ads();
int bldZcmp(int a1, int a2);

//-------------------------------------------------------------------------------------------------
#endif
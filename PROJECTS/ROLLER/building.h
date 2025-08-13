#ifndef _ROLLER_BUILDING_H
#define _ROLLER_BUILDING_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

typedef struct
{
  int iBuildingIdx;
  float fDepth;
} tVisibleBuilding;

//-------------------------------------------------------------------------------------------------

extern int BuildingSect[MAX_TRACK_CHUNKS];
extern float BuildingAngles[768];
extern int BuildingBase[256][4];
extern tVec3 BuildingBox[256][8];
extern tVisibleBuilding VisibleBuildings[256];
extern int16 advert_list[256];
extern int NumBuildings;
extern int NumVisibleBuildings;

//-------------------------------------------------------------------------------------------------

void InitBuildings();
void CalcVisibleBuildings();
void DrawBuilding(int a1, int a2);
void init_animate_ads();
int bldZcmp(int a1, int a2);

//-------------------------------------------------------------------------------------------------
#endif
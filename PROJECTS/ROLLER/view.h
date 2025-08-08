#ifndef _ROLLER_VIEW_H
#define _ROLLER_VIEW_H
//-------------------------------------------------------------------------------------------------

typedef struct
{
  float fChaseDistance;
  float fChaseMinDistance;
  float fChasePullNormal;
  float fChasePullCrash;
  float fChasePullDefault;
  float fChaseLookAhead;
} tViewData;

//-------------------------------------------------------------------------------------------------

extern tViewData viewdata[2];
extern int chaseview[2];
extern float CHASE_DIST[2];
extern float CHASE_MIN[2];
extern float PULLZ[2];
extern float LOOKZ[2];
extern int nextpoint[2];
extern float lastpos[2][256];
extern int NearTow;
extern float chase_x;
extern float chase_y;
extern float chase_z;

//-------------------------------------------------------------------------------------------------

int calculateview(int a1, int a2, int a3);
void initcarview(int iCarIdx, int iPlayer);
int newchaseview(int a1, int a2);

//-------------------------------------------------------------------------------------------------
#endif
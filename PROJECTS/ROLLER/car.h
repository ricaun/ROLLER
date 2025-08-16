#ifndef _ROLLER_CAR_H
#define _ROLLER_CAR_H
//-------------------------------------------------------------------------------------------------
#include "carplans.h"
#include "frontend.h"
#include "polyf.h"
//-------------------------------------------------------------------------------------------------

#define CAR_STATUS_DEATH  0x02
#define CAR_STATUS_ACTIVE 0x04
#define CAR_STATUS_PIT    0x08

//-------------------------------------------------------------------------------------------------

typedef struct
{
  tVec3 hitboxAy[16][8];
} tCarBox;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  tVec3 pos;
  int16 nCurrChunk;
  int16 nChunk2;
  int16 nRoll;
  int16 nPitch;
  int16 nYaw;
  int16 nPadding1;
  float fFinalSpeed;
  float fHealth;
  int iDriverIdx;
  int iUnk6;
  int iUnk7;
  int iUnk8;
  float fUnk9;
  tVec3 pos2;
  int nYaw3;
  int iUnk10;
  int iControlType;
  int iUnk18;
  int iUnk18_2;
  float fCarHalfWidth;
  int iPadding3;
  int iUnk20;
  int iUnk20_2;
  int16 nUnk21;
  uint8 byCarDesignIdx;
  uint8 byLives;
  uint8 byUnk24;
  uint8 byPadding5;
  int16 nUnk25;
  int iUnk25_2;
  float fBaseSpeed;
  float fSpeedOverflow;
  float fRPMRatio;
  float fPower;
  uint8 byGearAyMax;
  char byLap;
  uint8 byRacePosition;
  uint8 byStatusFlags;
  int iPitchDynamicOffset;
  int iRollDynamicOffset;
  int iUnk35_2;
  int iUnk35_3;
  int iPitchCameraOffset;
  int iUnk36_2;
  int iRollCameraOffset;
  int iUnk37;
  int iRollMotion;
  int iPitchMotion;
  int iYawMotion;
  int iUnk38_4;
  float fUnk39;
  uint8 byDebugDamage;
  uint8 byUnk41;
  uint8 byKills;
  uint8 byUnk43;
  int iUnk44;
  int iUnk45;
  int iUnk46;
  int iUnk47;
  int iStunned;
  int iAITargetCar;
  int iLaneType;
  int iLastValidChunk;
  float fRunningLapTime;
  float fBestLapTime;
  float fPreviousLapTime;
  float fTotalRaceTime;
  int16 nTargetChunk;
  int16 nChangeMateCooldown;
  uint8 byUnk58;
  uint8 byUnk59;
  uint8 byUnk60;
  uint8 byUnk61;
  uint8 byUnk62[28];
  uint8 byUnk63;
  uint8 byUnk64;
  uint8 byUnk65;
  uint8 byPadding14;
  uint8 byCheatAmmo;
  uint8 byUnk67;
  uint8 byUnk68;
  uint8 byPadding15;
  int iUnk69;
  int16 nUnk70;
  int16 nUnk71;
  int iUnk72;
  float fUnk73;
  float fUnk73_2;
  int iUnk74;
  uint8 byUnk75;
  uint8 byUnk76;
  uint8 byUnk77;
  uint8 byPadding17;
} tCar;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  float speeds[6];
} tStoreEngine;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  tPoint screen;
  tVec3 world;
  tVec3 view;
} tCarPt;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  int iPolygonLink;
  int iPolygonIndex;
  float fZDepth;
} tCarZOrderEntry;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  float fPosX;
  float fPosY;
  float fState;
  float fVelX;
  float fVelY;
  float fUnk5;
  float fSize;
  int iLifeTime;
  float fTimer;
  int iColor;
  int iType;
} tCarSpray;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  int iChunkIdx;
  int iCarIdx;
  float fMinZDepth;
} tCarDrawOrder;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  tVec3 currentPos;
  tVec3 targetPos;
  tVec3 speed;
  uint32 uiRotation;
  float fUnk1;
  float fUnk2;
} tSLight;

//-------------------------------------------------------------------------------------------------

extern int numcars;
extern int team_col[16];
extern char default_names[16][9];
extern int16 ViewType[2];
extern tVec3 carworld[4];
extern tVec3 carpoint[4];
extern tVec3 carlocal[4];
extern float roadheight[4];
extern tCarPt CarPt[128];
extern tCarZOrderEntry CarZOrder[MAX_TRACK_CHUNKS];
extern tCarDrawOrder car_draw_order[16];
extern int car_texmap[16];
extern tCarBox CarBox;
extern tCar Car[16];
extern int car_persps[128];
extern tCarPt SmokePt[2][64];
extern int car_texs_loaded[16];
extern tCarSpray CarSpray[18][32];
extern char driver_names[16][9];
extern tStoreEngine StoreEngines[14];
extern tSLight SLight[2][3];
extern int finished_car[16];
extern int grid[16];
extern int cars_drawn;
extern tPolyParams CarPol;
extern float CarBaseX;
extern float CarBaseY;
extern int LoadCarTextures;
extern float CarDiag;

//-------------------------------------------------------------------------------------------------

void InitCarStructs();
void CalcCarSizes();
void InitCars();
void placecars();
void DrawCars(int iCarIdx, int iViewMode);
void DisplayCar(int iCarIndex, uint8 *pScreenBuffer, float fDistanceToCar);
int carZcmp(const void *pCar1, const void *pCar2);

//-------------------------------------------------------------------------------------------------
#endif

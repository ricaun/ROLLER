#ifndef _ROLLER_CAR_H
#define _ROLLER_CAR_H
//-------------------------------------------------------------------------------------------------
#include "carplans.h"
//-------------------------------------------------------------------------------------------------

typedef struct
{
  tVec3 hitboxAy[112];
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
  float fMaxSpeed;
  float fUnk4;
  int iUnk5;
  int iUnk6;
  int iUnk7;
  int iUnk8;
  float fUnk9;
  tVec3 pos2;
  int nYaw3;
  int iUnk10;
  int iUnk17;
  int iUnk18;
  int iUnk18_2;
  float fUnk19;
  int iPadding3;
  int iUnk20;
  int iUnk20_2;
  int16 nUnk21;
  uint8 byCarDesignIdx;
  uint8 byUnk23;
  uint8 byUnk24;
  uint8 byPadding5;
  int16 nUnk25;
  int iUnk25_2;
  float fMaxSpeed2;
  int iUnk27;
  float fUnk28;
  float fPower;
  uint8 byGearAyMax;
  uint8 byUnk31;
  uint8 byUnk32;
  uint8 byUnk33;
  int iUnk34;
  int iUnk35;
  int iUnk35_2;
  int iUnk35_3;
  int iUnk36;
  int iUnk36_2;
  int iUnk37;
  int iUnk38;
  int iUnk38_1;
  int iUnk38_2;
  int iUnk38_3;
  int iUnk38_4;
  float fUnk39;
  uint8 byUnk40;
  uint8 byUnk41;
  uint8 byUnk42;
  uint8 byUnk43;
  int iUnk44;
  int iUnk45;
  int iUnk46;
  int iUnk47;
  int iUnk48;
  int iUnk49;
  int iUnk50;
  int iLastValidChunk;
  float iUnk52;
  float fUnk53;
  int iUnk54;
  int iUnk55;
  int16 nUnk56;
  int16 nUnk57;
  uint8 byUnk58;
  uint8 byUnk59;
  uint8 byUnk60;
  uint8 byUnk61;
  uint8 byUnk62[28];
  uint8 byUnk63;
  uint8 byUnk64;
  uint8 byUnk65;
  uint8 byPadding14;
  uint8 byUnk66;
  uint8 byUnk67;
  uint8 byUnk68;
  uint8 byPadding15;
  int iUnk69;
  int16 nUnk70;
  int16 nUnk71;
  int iUnk72;
  float fUnk73;
  int iUnk73_2;
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

extern int numcars;
extern char default_names[16][9];
extern int16 ViewType[2];
extern float CarBaseX;
extern float CarBaseY;
extern float CarDiag;
extern int car_texmap[16];
extern tCarBox CarBox;
extern tCar Car[16];
extern int car_texs_loaded[16];
extern tStoreEngine StoreEngines[14];
extern int finished_car[16];
extern int grid[16];
extern int LoadCarTextures;

//-------------------------------------------------------------------------------------------------

void InitCarStructs();
void CalcCarSizes();
void InitCars();
int16 placecars();
int DrawCars(int result, int a2);
int16 DisplayCar(int iCarIdx, int a2, float a3);
int carZcmp(tCar *pCar1, tCar *pCar2);

//-------------------------------------------------------------------------------------------------
#endif

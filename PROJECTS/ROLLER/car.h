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
  float fUnk0;
  float fUnk1;
  float fUnk2;
  int16 nUnk3;
  int16 nUnk4;
  int16 nUnk5;
  int16 nUnk6;
  int16 nUnk7;
  int16 nPadding1;
  float fUnk8;
  float fUnk9;
  int iUnk10;
  int iUnk11;
  int iUnk12;
  int iUnk13;
  int iUnk14;
  int iPadding18;
  int iPadding19;
  int iPadding20;
  int iUnk15;
  int iUnk16;
  int iUnk17;
  int iUnk18;
  int iPadding2;
  float fUnk19;
  int iPadding3;
  int iUnk20;
  int iPadding4;
  int16 nUnk21;
  uint8 byCarDesignIdx;
  uint8 byUnk23;
  uint8 byUnk24;
  uint8 byPadding5;
  int16 nUnk25;
  int iPadding6;
  int iUnk26;
  int iUnk27;
  float fUnk28;
  int iUnk29;
  uint8 byUnk30;
  uint8 byUnk31;
  uint8 byUnk32;
  uint8 byUnk33;
  int iUnk34;
  int iUnk35;
  int iPadding7;
  int iPadding8;
  int iUnk36;
  int iPadding9;
  int iUnk37;
  int iUnk38;
  int iPadding10;
  int iPadding11;
  int iPadding12;
  int iPadding13;
  int iUnk39;
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
  int iUnk51;
  int iUnk52;
  int iUnk53;
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
  int iPadding16;
  int iUnk74;
  uint8 byUnk75;
  uint8 byUnk76;
  int16 nPadding17;
} tCar;

//-------------------------------------------------------------------------------------------------

extern int CalcCarSizes();

//-------------------------------------------------------------------------------------------------
#endif
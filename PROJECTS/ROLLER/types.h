#ifndef _ROLLER_TYPES_H
#define _ROLLER_TYPES_H
//-------------------------------------------------------------------------------------------------
#include <stddef.h>
//-------------------------------------------------------------------------------------------------

typedef signed __int8 int8;
typedef signed __int16 int16;
typedef signed int int32;
typedef signed __int64 int64;
typedef unsigned __int8 uint8;
typedef unsigned __int16 uint16;
typedef unsigned int uint32;
typedef unsigned __int64 uint64;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  uint32 uiCount;
  uint32 framesAy[16];
} tAnimation;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  uint8 byVert1;
  uint8 byVert2;
  uint8 byVert3;
  uint8 byVert4;
  uint32 uiTex;
  uint8 byUnknown1;
  uint8 byUnknown2;
  uint8 byUnknown3;
  uint8 byUnknown4;
} tPolygon;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  float fX;
  float fY;
  float fZ;
} tVec3;

//-------------------------------------------------------------------------------------------------

typedef enum
{
  CAR_AUTO = 0x1,
  CAR_DESILVA = 0x2,
  CAR_PULSE = 0x3,
  CAR_GLOBAL = 0x4,
  CAR_MILLION = 0x5,
  CAR_MISSION = 0x6,
  CAR_ZIZIN = 0x7,
  CAR_REISE = 0x8,
  CAR_F1WACK = 0x9,
  CAR_DEATH = 0xA,
} eCarType;

//-------------------------------------------------------------------------------------------------

typedef enum
{
  CAR_DESIGN_AUTO = 0x0,
  CAR_DESIGN_DESILVA = 0x1,
  CAR_DESIGN_PULSE = 0x2,
  CAR_DESIGN_GLOBAL = 0x3,
  CAR_DESIGN_MILLION = 0x4,
  CAR_DESIGN_MISSION = 0x5,
  CAR_DESIGN_ZIZIN = 0x6,
  CAR_DESIGN_REISE = 0x7,
  CAR_DESIGN_ZIZIN2 = 0x8,
  CAR_DESIGN_AUTO2 = 0x9,
  CAR_DESIGN_PULSE2 = 0xA,
  CAR_DESIGN_REISE2 = 0xB,
  CAR_DESIGN_F1WACK = 0xC,
  CAR_DESIGN_DEATH = 0xD,
} eCarDesignIndex;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  tVec3 hitboxAy[112];
} tCarBox;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  float fUnk1;
  float fUnk2;
  float fUnk3;
  float fUnk4;
  float fUnk5;
  float fUnk6;
  float fUnk7;
  float fUnk8;
} tRev;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  int iNumGears;
  tRev *pRevs;
  float *pSpds;                         ///< maximum speed at each gear
  int iUnk2;
  float *pChgs;
  int iUnk3;
  float fUnk4;
  float fUnk5;
  int iUnk6;
  int iUnk7;
  int iUnk8;
  int iUnk9;
  int iUnk10;
  int iUnk11;
  int iUnk12;
  int iUnk13;
  int iUnk14;
  int iUnk15;
  int iUnk16;
  int iUnk17;
  int iUnk18;
  int iUnk19;
  int iUnk20;
  int iUnk21;
  float fUnk22;
  float fUnk23;
  float fUnk24;
  float fUnk25;
} tCarEngine;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  tCarEngine engines[14];
} tCarEngines;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  uint8 byNumPols;
  uint8 byNumCoords;
  uint8 byUnk3;
  uint8 byUnk4;
  tPolygon *pPols;
  tVec3 *pCoords;
  uint32 *pBacks;
  eCarType carType;
  int *pPlaces;
  tAnimation *pAnms;
} tCarDesign;

//-------------------------------------------------------------------------------------------------
#endif
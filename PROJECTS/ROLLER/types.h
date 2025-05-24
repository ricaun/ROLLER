#ifndef _ROLLER_TYPES_H
#define _ROLLER_TYPES_H
//-------------------------------------------------------------------------------------------------
#include <stddef.h>
//-------------------------------------------------------------------------------------------------

#define ONE_OVER_TRIG_LOOKUP_AY_COUNT 0.00006103515625
#define ONE_OVER_TATN_LOOKUP_AY_COUNT 0.0009765625
#define TWO_PI 6.28318530718

//-------------------------------------------------------------------------------------------------

#if defined(IS_WINDOWS)
typedef signed char      int8;
typedef signed short     int16;
typedef signed int       int32;
typedef signed __int64   int64;
typedef unsigned char    uint8;
typedef unsigned short   uint16;
typedef unsigned int     uint32;
typedef unsigned __int64 uint64;
#else
typedef signed char        int8;
typedef signed short       int16;
typedef signed int         int32;
typedef signed long long   int64;
typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;
typedef unsigned int       DWORD;
typedef unsigned short     WORD;
#endif

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
#endif

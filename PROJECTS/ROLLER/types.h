#ifndef _ROLLER_TYPES_H
#define _ROLLER_TYPES_H
//-------------------------------------------------------------------------------------------------
#include <stddef.h>
//-------------------------------------------------------------------------------------------------

#if defined (WIN32) || defined (_WIN32)
#define IS_WINDOWS
#elif defined(__linux__) || defined(linux) || defined(__linux)
#define IS_LINUX
#endif

//-------------------------------------------------------------------------------------------------

#define ONE_OVER_TRIG_LOOKUP_AY_COUNT 0.00006103515625
#define ONE_OVER_TATN_LOOKUP_AY_COUNT 0.0009765625
#define TWO_PI 6.28318530718
#define HZ_TO_NS(x) ((x) > 0 ? (1000000000UL / (x)) : 0)
#define TRIG_SCALE 25600.0f
#define MAX_CARS 16
#define MAX_PLAYERS 16

//-------------------------------------------------------------------------------------------------

#define SURFACE_FLAG_WALL_31       0x80000000
#define SURFACE_FLAG_BOUNCE_30     0x40000000
#define SURFACE_FLAG_ECHO          0x20000000
#define SURFACE_FLAG_28            0x10000000 //todo
#define SURFACE_FLAG_27            0x08000000 //todo
#define SURFACE_FLAG_PIT_2         0x04000000
#define SURFACE_FLAG_PIT           0x02000000
#define SURFACE_FLAG_YELLOW_MAP    0x01000000
#define SURFACE_FLAG_23            0x00800000 //todo
#define SURFACE_FLAG_WALL_22       0x00400000
#define SURFACE_FLAG_TRANSPARENT   0x00200000
#define SURFACE_FLAG_BOUNCE_20     0x00100000
#define SURFACE_FLAG_NON_MAGNETIC  0x00080000
#define SURFACE_FLAG_FLIP_VERT     0x00040000
#define SURFACE_FLAG_SKIP_RENDER   0x00020000
#define SURFACE_FLAG_TEXTURE_PAIR  0x00010000
#define SURFACE_FLAG_ANMS_LIVERY   0x00008000
#define SURFACE_FLAG_CONCAVE       0x00004000
#define SURFACE_FLAG_FLIP_BACKFACE 0x00002000
#define SURFACE_FLAG_FLIP_HORIZ    0x00001000
#define SURFACE_FLAG_BACK          0x00000800
#define SURFACE_FLAG_PARTIAL_TRANS 0x00000400
#define SURFACE_FLAG_ANMS_LOOKUP   0x00000200
#define SURFACE_FLAG_APPLY_TEXTURE 0x00000100
#define SURFACE_MASK_FLAGS         0xFFFFFF00
#define SURFACE_MASK_TEXTURE_INDEX 0x000000FF

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

//16.16 point math helpers
typedef int32 fixed16_16;
#define TO_FIXED(x) ((fixed16_16)((x) * 65536.0f))
#define FROM_FIXED(x) ((float)(x) / 65536.0f)

#define GET_HIWORD(x) (((x) >> 16) & 0xFFFF)
#define SET_HIWORD(lval, rval) (lval = (lval & 0x0000FFFF) | ((uint32)(rval) << 16))
#define GET_LOWORD(x) ((x) & 0xFFFF)
#define SET_LOWORD(lval, rval) (lval = (lval & 0xFFFF0000) | ((rval) & 0x0000FFFF))
#define INC_HIWORD(x) (SET_HIWORD(x, GET_HIWORD(x) + 1))
#define DEC_HIWORD(x) (SET_HIWORD(x, GET_HIWORD(x) - 1))
#define INC_LOWORD(x) (SET_LOWORD(x, GET_LOWORD(x) + 1))
#define DEC_LOWORD(x) (SET_LOWORD(x, GET_LOWORD(x) - 1))

#define GET_BYTE1(x) (((x) >> 8) & 0xFF)
#define SET_BYTE1(lval, rval) (lval = (lval & 0xFFFF00FF) | ((rval) & 0x0000FF00))
#define SET_LOBYTE(lval, rval) (lval = (lval & 0xFFFFFF00) | ((rval) & 0x000000FF))
#define SET_BYTE1_64(lval, rval)  (lval = (lval & 0xFFFFFFFFFFFF00FF) | ((rval) & 0x000000000000FF00))
#define SET_LOWORD_64(lval, rval) (lval = (lval & 0xFFFFFFFFFFFF0000) | ((rval) & 0x000000000000FFFF))

#define GET_SHIWORD(x) (int16)GET_HIWORD(x)
#define GET_SLOWORD(x) (int16)GET_LOWORD(x)

#define __PAIR64__(high, low) (((uint64)(uint32)(high) << 32) | (uint32)(low))

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
  uint8 byR;
  uint8 byB;
  uint8 byG;
} tColor;

//-------------------------------------------------------------------------------------------------
#endif

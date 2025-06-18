#ifndef _ROLLER_ENGINES_H
#define _ROLLER_ENGINES_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

typedef struct
{
  float fRev1;
  float fRev2;
  float fRev3;
  float fRev4;
  float fRev5;
  float fRev6;
  float fRev7;
  float fRev8;
} tRev;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  int iNumGears;
  tRev *pRevs;
  float *pSpds;                         ///< maximum speed at each gear
  int iUnk2;
  int *pChgs;
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

extern tRev AUTO_A_revs[];
extern float AUTO_A_spds[];
extern int AUTO_A_chgs[];

extern tRev DESILVA_revs[];
extern float DESILVA_spds[];
extern int DESILVA_chgs[];

extern tRev PULSE_E_revs[];
extern float PULSE_E_spds[];
extern int PULSE_E_chgs[];

extern tRev GLOBAL_revs[];
extern float GLOBAL_spds[];
extern int GLOBAL_chgs[];

extern tRev MILLION_revs[];
extern float MILLION_spds[];
extern int MILLION_chgs[];

extern tRev MISSION_revs[];
extern float MISSION_spds[];
extern int MISSION_chgs[];

extern tRev ZIZIN_revs[];
extern float ZIZIN_spds[];
extern int ZIZIN_chgs[];

extern tRev REISE_W_revs[];
extern float REISE_W_spds[];
extern int REISE_W_chgs[];

extern tRev fast_revs[];
extern float fast_spds[];
extern int fast_chgs[];

extern tCarEngines CarEngines;

//-------------------------------------------------------------------------------------------------
#endif
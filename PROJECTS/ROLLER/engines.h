#ifndef _ROLLER_ENGINES_H
#define _ROLLER_ENGINES_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

typedef struct
{
  float fRPM;
  float fPower;
} tRevCurvePoint;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  tRevCurvePoint points[4];
} tRevCurve;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  int iNumGears;
  tRevCurve *pRevs;
  float *pSpds;                         ///< maximum speed at each gear
  float fDragCoefficient;
  int *pChgs;
  int iUnk3;
  float fUnk4;
  float fUnk5;
  int iUnk6;
  int iPitchAccelRate;
  int iMaxPitchOffset;
  int iPitchDecayRate;
  int iMinPitchOffset;
  int iNoseUpRecoveryRate;
  int iNoseDownRecoveryRate;
  int iUnk13;
  int iUnk14;
  int iUnk15;
  int iMaxTurnRate;
  int iTurnDecayRate;
  int iUnk18;
  int iWheelCenteringRate;
  int iUnk20;
  int iSteeringSensitivity;
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

extern tRevCurve AUTO_A_revs[];
extern float AUTO_A_spds[];
extern int AUTO_A_chgs[];

extern tRevCurve DESILVA_revs[];
extern float DESILVA_spds[];
extern int DESILVA_chgs[];

extern tRevCurve PULSE_E_revs[];
extern float PULSE_E_spds[];
extern int PULSE_E_chgs[];

extern tRevCurve GLOBAL_revs[];
extern float GLOBAL_spds[];
extern int GLOBAL_chgs[];

extern tRevCurve MILLION_revs[];
extern float MILLION_spds[];
extern int MILLION_chgs[];

extern tRevCurve MISSION_revs[];
extern float MISSION_spds[];
extern int MISSION_chgs[];

extern tRevCurve ZIZIN_revs[];
extern float ZIZIN_spds[];
extern int ZIZIN_chgs[];

extern tRevCurve REISE_W_revs[];
extern float REISE_W_spds[];
extern int REISE_W_chgs[];

extern tRevCurve fast_revs[];
extern float fast_spds[];
extern int fast_chgs[];

extern tCarEngines CarEngines;

//-------------------------------------------------------------------------------------------------
#endif
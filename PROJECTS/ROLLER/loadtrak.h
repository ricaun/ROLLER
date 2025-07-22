#ifndef _ROLLER_LOADTRAK_H
#define _ROLLER_LOADTRAK_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------

typedef struct
{
  int16 nForwardExtraStart;
  uint8 byForwardMainChunks;
  uint8 byForwardExtraChunks;
  int16 nBackwardExtraStart;
  uint8 byBackwardMainChunks;
  uint8 byBackwardExtraChunks;
} tTrakView;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  tVec3 center;
  int iUnk1;
  int iUnk2;
  int iUnk3;
  int iLeftSurfaceType;
  int iRightSurfaceType;
  float fUnk6;
} tTrackInfo;

//-------------------------------------------------------------------------------------------------

extern uint8 TrackSelect;
extern char *delims;
extern tTrakView TrakView[500];
extern int cur_laps[6];
extern int meof;
extern tTrackInfo TrackInfo[500];
extern float cur_TrackZ;
extern int TRAK_LEN;

//-------------------------------------------------------------------------------------------------

void loadtrack(int iTrackIdx, int a2);
int read_backs(int *a1, int a2, int a3, int a4);
char *read_texturemap(int a1);
char *read_bldmap(char **a1);
int readstuntdata(int a1, int a2, int a3, int a4);
void activatestunts();
int ReadAnimData(int result, int a2);
void readline(FILE *pFile, const char *szFmt, ...);
uint8 *memgets(uint8 *dst, uint8 **ppSrc);
void readline2(uint8 **ppFileHandle, const char *pszFormat, ...);
void rotatepoint(double dX, double dY, double dZ, double dYaw, double dPitch, double dRoll, double *pdOutX, double *pdOutY, double *pdOutZ);
void setpoint(int iChunkIdx, int iPointIdx, double dX, double dY, double dZ);
void setgpoint(int iChunkIdx, int iPointIdx, double dX, double dY, double dZ);
int resetcars();
char *min_skip_stuff(int *a1);

//-------------------------------------------------------------------------------------------------
#endif
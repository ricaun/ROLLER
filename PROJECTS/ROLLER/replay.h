#ifndef _ROLLER_REPLAY_H
#define _ROLLER_REPLAY_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
#include "func3.h"
#include "frontend.h"
#include <stdio.h>
#include <stdlib.h>
//-------------------------------------------------------------------------------------------------

#define REPLAY_SPEED_MIN      -8192
#define REPLAY_SPEED_MAX      8192
#define REPLAY_NORMAL_SPEED   256

//-------------------------------------------------------------------------------------------------

#pragma pack(push, 1)
typedef struct
{
  uint8 byView;
  uint8 byCarIdx;
  int iFrame;
} tReplayCamera;
#pragma pack(pop)

//-------------------------------------------------------------------------------------------------

typedef struct
{
  int16 nX;
  int16 nY;
  void *pFunc;
} tRIcon;

//-------------------------------------------------------------------------------------------------

extern int disciconpressed;
extern int rotpoint;
extern int replaypanel;
extern int controlicon;
extern int replayspeeds[9];
extern char *replayname[9];
extern int filingmenu;
extern int replaysetspeed;
extern int replaydirection;
extern int lastfile;
extern int lastautocut;
extern int pend_view_init;
extern int replayedit;
extern char replayfilename[32];
extern char *views[8];
extern int loading_replay;
extern tRIcon ricon[26];
extern char *replayhelp[26];
extern int lsdsel;
extern tPoint rrotate[8];
extern tReplayCamera camera[100];
extern int disabled[4096];
extern char temp_names[16][9];
extern char newrepsample[16];
extern char repsample[16];
extern int oldtrack;
extern int oldtextures;
extern FILE *replayfile;
extern int replayspeed;
extern int oldcars;
extern int replayframes;
extern int currentreplayframe;
extern int lastreplayframe;
extern int introfiles;
extern int replayselect;
extern int slowing;
extern int rewinding;
extern int forwarding;
extern int replaystart;
extern int cuts;
extern char rememberfilename[34];

//-------------------------------------------------------------------------------------------------;

void setreplaytrack();
int startreplay();
void stopreplay();
int DoReplayData(int a1, int a2, int a3, int a4);
void Rplay();
void Rreverseplay();
void Rframeplus();
void Rframeminus();
void Rspeedplus();
void Rspeedminus();
void DoRstop();
void Rstop();
void Rrewindstart();
void Rforwardstart();
void ROldStatus();
void Rstart();
void Rend();
unsigned int readdisable(int iFrame);
void cleardisable(int iFrame);
void setdisable(int iFrame);
void deleteframes(int iStartFrame, int iEndFrame);
void undeleteframes(int iStartFrame, int iEndFrame);
void findnextvalid();
void findlastvalid();
void Rassemble();
void storecut();
void removecut();
int readcut();
int displayreplay();
int compare(const char *szStr1, const char *szStr2);
void warning(int iX1, int iY1, int iX2, int iY2, char *szWarning);
void lsd(int iX1, int iY1, int iX2, int iY2);
int scandirectory(int a1);
char fileselect(int a1, int a2, int a3, int a4, int a5, int a6, char *a7, int a8, int a9);
void previouscut();
void nextcut();
int loadreplay();
int savereplay();
int deletereplay(int a1, int a2, int a3, int a4);
char updatedirectory();
void findintrofiles();
void displaycontrolpanel();
void rtoggleedit();
void rstartblock();
void rselectblock();
void rdeleteblock();
void rstoreview();
void rremoveview();
void rpreviouscut();
void rnextcut();
void rstartassemble();
void replayicon(uint8 *pDest, tBlockHeader *pBlockHeader, int iBlockIdx, int iX, int iY, int iScreenWidth, int byTransparentColor);
void replaypanelletter(char c, int *piX, int *piY, int iScreenWidth);
void replaypanelstring(const char *szStr, int iX, int iY, int iScreenWidth);
void displaypaneltime(int iTime, int iX, int iY, int iScreenWidth);
void discmenu();
void initsoundlag(uint32 uiTicks);
void resetsmoke();

//-------------------------------------------------------------------------------------------------
#endif

#ifndef _ROLLER_REPLAY_H
#define _ROLLER_REPLAY_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
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

extern int rotpoint;
extern int replayspeeds[9];
extern int filingmenu;
extern int replaysetspeed;
extern int replaydirection;
extern int lastfile;
extern int lastautocut;
extern int pend_view_init;
extern int replayedit;
extern tReplayCamera camera[100];
extern int disabled[4096];
extern int replayspeed;
extern int replayframes;
extern int currentreplayframe;
extern int lastreplayframe;
extern int introfiles;
extern char newrepsample[16];
extern char repsample[16];
extern int replayselect;
extern int slowing;
extern int rewinding;
extern int forwarding;
extern int replaystart;
extern int cuts;

//-------------------------------------------------------------------------------------------------;

void setreplaytrack();
int startreplay();
void stopreplay(int a1, int a2, int a3, int a4);
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
int deleteframes(int result, int a2);
int undeleteframes(int result, int a2);
void findnextvalid();
unsigned int findlastvalid();
void Rassemble();
void storecut();
void removecut();
int readcut();
int displayreplay();
int compare(int a1, int a2);
int warning(int a1, int a2, int a3, int a4, char *a5);
char lsd(int a1, int a2, int a3, int a4);
int scandirectory(int a1);
char fileselect(int a1, int a2, int a3, int a4, int a5, int a6, char *a7, int a8, int a9);
void previouscut();
void nextcut();
int loadreplay();
int savereplay();
int deletereplay(int a1, int a2, int a3, int a4);
char updatedirectory();
void findintrofiles();
int displaycontrolpanel();
void rtoggleedit();
void rstartblock();
void rselectblock();
void rdeleteblock();
void rstoreview();
void rremoveview();
void rpreviouscut();
void rnextcut();
void rstartassemble();
uint8 *replayicon(int a1, int a2, int a3, int a4, int a5, int a6, int a7);
int replaypanelletter(int result, int *a2, int *a3, int a4);
int replaypanelstring(const char *a1, int a2, int a3, int a4);
int displaypaneltime(int a1, int a2, int a3, int a4);
int discmenu(int a1, unsigned int a2, int a3, unsigned int a4);
void initsoundlag(uint32 uiTicks);
void resetsmoke();

//-------------------------------------------------------------------------------------------------
#endif

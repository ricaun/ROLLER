#ifndef _ROLLER_3D_H
#define _ROLLER_3D_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
#include "engines.h"
//-------------------------------------------------------------------------------------------------

typedef struct
{
  void *pBuf;
  uint32 uiSize;
  void *pAlsoBuf; //seems to be set to the same thing as pBuf in W95
  int iRegsDi;    //unused by W95
} tMemBlock;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  tVec3 pointAy[4];
  float fTrackHalfLength;
  float fTrackHalfWidth;
  int iPitch;
  int iYaw;
  int iRoll;
  int iInnerLanePitchAngle;
  int iOuterLanePitchAngle;
  tVec3 gravity;
  int iBankDelta;
  int iBankAngleDelta;
  float fUnk25;
  float fUnk26;
  float fUnk27;
  float fUnk28;
  float fUnk29;
  float fUnk30;
  int iUnk1;
  int iUnk2;
} tData;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  tVec3 pointAy[6];
} tGroundPt;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  uint32 uiSurfType1;
  uint32 uiSurfType2;
  uint32 uiSurfType3;
  uint32 uiSurfType4;
  uint32 uiSurfType5;
  uint32 uiSurfType6;
} tTrakColour;

//-------------------------------------------------------------------------------------------------

extern int exiting;
extern int dontrestart;
extern int champ_mode;
extern int cd_error;
extern int game_svga;
extern int game_size;
extern int game_view[2];
extern int svga_possible;
extern int hibuffers;
extern uint32 mem_used;
extern int current_mode;
extern int names_on;
extern tCarEngine *p_eng[2];
extern int messages;
extern int SVGA_ON;
extern int TrackLoad;
extern int paused;
extern int pause_request;
extern char alltrackflag;
extern int dxmouse;
extern int dymouse;
extern int mousex;
extern int mousey;
extern int mbut;
extern int oldbut;
extern int mclick;
extern int mouse;
extern int network_on;
extern int mirror;
extern int mpressed;
extern int jpressed;
extern uint8 *screen;
extern uint8 *scrbuf;
extern void *mirbuf;
extern uint8 *texture_vga;
extern uint8 *building_vga;
extern uint8 *horizon_vga;
extern uint8 *cartex_vga[16];
extern uint8 *cargen_vga;
extern uint8 *rev_vga[16];
extern int firstrun;
extern int language;
extern tTrakColour TrakColour[500];
extern tData localdata[500];
extern tGroundPt GroundPt[500];
extern tGroundPt TrakPt[500];
extern uint8 shade_palette[4096];
extern tColor palette[256];
extern float tsin[16384];
extern float ptan[16384];
extern float tcos[16384];
extern char buffer[128];
extern uint8 blank_line[640];
extern int p_joyk1[2];
extern int p_joyk2[2];
extern tMemBlock mem_blocks[128];
extern volatile int ticks;
extern float k1;
extern float k2;
extern float k3;
extern float k4;
extern float k5;
extern float k6;
extern float k7;
extern float k8;
extern float k9;
extern float tatn[1025];
extern uint32 textures_off;
extern int tex_count;
extern int vtilt;
extern int worldtilt;
extern float worldx;
extern float worldy;
extern float worldz;
extern int worldelev;
extern int velevation;
extern int vdirection;
extern int scr_size;
extern int ybase;
extern int xbase;
extern int winx;
extern int winy;
extern float ext_y;
extern float ext_z;
extern float viewx;
extern float viewy;
extern float viewz;
extern int worlddirn;
extern char keys[140];
extern int oldmode;
extern int clear_borders;
extern float DDX;
extern float DDY;
extern float DDZ;
extern float ext_x;
extern int test_f1;
extern int test_f2;
extern int test_f3;
extern int print_data;
extern int demo_control;
extern int tick_on;
extern int old_mode;
extern int demo_mode;
extern int demo_count;
extern int start_race;
extern int NoOfLaps;
extern int human_finishers;
extern int countdown;
extern int max_mem;
extern int scrmode;
extern int intro;
extern int control_edit;
extern int req_edit;
extern int controlrelease;
extern int fatal_ini_loaded;
extern int machine_speed;
extern int netCD;
extern int localCD;
extern int I_Want_Out;
extern int winner_mode;
extern int network_mes_mode;
extern int network_slot;
extern int w95;
extern int send_finished;
extern int winh;
extern int winw;
extern int VIEWDIST;
extern int YMAX;
extern int XMAX;
extern int time_shown;
extern int player2_car;
extern int player1_car;

//-------------------------------------------------------------------------------------------------

void copypic(uint8 *pSrc, uint8 *pDest);
void init_screen();
void init();
void *getbuffer(uint32 uiSize);
void *trybuffer(uint32 uiSize);
void fre(void **ppData);
void doexit();
void *malloc2(int iSize, void *pPtr, int *pRegsDi);
void free2(void *ptr);
void firework_screen();
void updatescreen();
void draw_road(uint8 *a1, char *a2, float *a3, int a4, int a5);
int main(int argc, const char **argv, const char **envp);
int play_game_init();
void play_game_uninit(int a1, int a2, int a3, int a4);
int winner_race();
int champion_race();
void play_game(int a1, int a2, int a3);
void game_keys(int64 a1);
int mesminus();
int mesplus();
int carminus(int a1, int a2, int a3);
int carplus(int a1, unsigned int a2, int a3, unsigned int a4);
int viewminus(int a1);
int viewplus(int a1);
void game_copypic(uint8 *a1, uint8 *a2, char *a3);
void test_w95();
void *malloc2(int iSize, void *pPtr, int *pRegsDi);
void free2(void *ptr);

//-------------------------------------------------------------------------------------------------
#endif

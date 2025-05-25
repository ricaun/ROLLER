#ifndef _ROLLER_3D_H
#define _ROLLER_3D_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
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
  float fUnk13;
  float fUnk14;
  int iUnk15;
  int iUnk16;
  float fUnk17;
  int iUnk18;
  int iUnk19;
  float fUnk20;
  float fUnk21;
  float fUnk22;
  float fUnk23;
  float fUnk24;
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

extern int game_size;
extern int svga_possible;
extern int hibuffers;
extern uint32 mem_used;
extern int current_mode;
extern int SVGA_ON;
extern int TrackLoad;
extern void *scrbuf;
extern int firstrun;
extern int language;
extern tData localdata[];
extern tGroundPt GroundPt[];
extern float tsin[];
extern float ptan[];
extern float tcos[];
extern uint8 blank_line[];
extern tMemBlock mem_blocks[];
extern float tatn[];
extern uint32 textures_off;
extern int tex_count;
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
extern int oldmode;
extern int start_race;
extern int NoOfLaps;
extern int countdown;
extern int max_mem;
extern int scrmode;
extern int intro;
extern int fatal_ini_loaded;
extern int machine_speed;
extern int winner_mode;
extern int network_slot;
extern int w95;
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
void fre(void *pData);
void doexit(int a1, int a2, void *pBuf);
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

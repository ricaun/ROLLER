#ifndef _ROLLER_3D_H
#define _ROLLER_3D_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
#include "engines.h"
#include "frontend.h"
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
  float fAILine1;
  float fAILine2;
  float fAILine3;
  float fAILine4;
  int iCenterGrip;
  int iLeftShoulderGrip;
  int iRightShoulderGrip;
  float fAIMaxSpeed;
} tData;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  tVec3 pointAy[6];
} tGroundPt;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  tPoint screen;
  tVec3 projected;
} tScreenPt;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  int iLeftSurfType;
  int iCenterSurfType;
  int iRightSurfType;
  int iLeftWallType;
  int iRightWallType;
  int iRoofType;
} tTrakColour;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  int iUnk1;
  int iClipCount;
  tScreenPt screenPtAy[6];
} tTrackScreenXYZ;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  int iLUOWallType;
  int iLLOWallType;
  int iOFloorType;
  int iRLOWallType;
  int iRUOWallType;
} tGroundColour;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  int16 nRenderPriority;
  int16 nChunkIdx;
  float fZDepth;
} tTrackZOrderEntry;

//-------------------------------------------------------------------------------------------------

extern int exiting;
extern int dontrestart;
extern int champ_mode;
extern int cd_error;
extern int game_count[2];
extern int lastblip[2];
extern float game_scale[2];
extern int define_mode;
extern int calibrate_mode;
extern int graphic_mode;
extern int calibrate_select;
extern int sound_edit;
extern int showversion;
extern int game_svga;
extern int game_size;
extern int game_view[2];
extern int svga_possible;
extern int autoswitch;
extern int hibuffers;
extern int lobuffers;
extern int mem_used;
extern int mem_used_low;
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
extern char Banks_On;
extern char Buildings_On;
extern char Road_On;
extern char Walls_On;
extern char Play_View;
extern int DriveView[2];
extern int mirror;
extern float TopViewHeight;
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
extern tBlockHeader *rev_vga[16];
extern int firstrun;
extern int language;
extern tGroundColour GroundColour[MAX_TRACK_CHUNKS];
extern tTrakColour TrakColour[MAX_TRACK_CHUNKS];
extern int HorizonColour[MAX_TRACK_CHUNKS];
extern tData localdata[MAX_TRACK_CHUNKS];
extern tGroundPt GroundPt[MAX_TRACK_CHUNKS];
extern float hor_scan[800];
extern tGroundPt TrakPt[MAX_TRACK_CHUNKS];
extern tTrackScreenXYZ GroundScreenXYZ[MAX_TRACK_CHUNKS];
extern tTrackScreenXYZ TrackScreenXYZ[MAX_TRACK_CHUNKS];
extern uint8 shade_palette[4096];
extern tColor palette[256];
extern float tsin[16384];
extern float ptan[16384];
extern float tcos[16384];
extern char buffer[128];
extern uint8 blank_line[640];
extern tTrackZOrderEntry TrackView[6500];
extern int p_joyk1[2];
extern int p_joyk2[2];
extern tMemBlock mem_blocks[128];
extern int zoom_size[2];
extern char zoom_mes[2][24];
extern int sub_on[2];
extern char zoom_sub[2][24];
extern int game_overs;
extern int averagesectionlen;
extern int racing;
extern int totaltrackdistance;
extern int disable_messages;
extern int curr_time;
extern volatile int ticks;
extern int frame_rate;
extern int frame_count;
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
extern int finishers;
extern int countdown;
extern int screenready;
extern int shown_panel;
extern int game_level;
extern int max_mem;
extern int game_req;
extern int game_dam;
extern int pausewindow;
extern int scrmode;
extern int control_select;
extern int req_size;
extern int intro;
extern int fadedin;
extern int control_edit;
extern int req_edit;
extern int controlrelease;
extern int fatal_ini_loaded;
extern int machine_speed;
extern int netCD;
extern int localCD;
extern int dead_humans;
extern int I_Want_Out;
extern int champ_car;
extern int champ_zoom;
extern int replay_player;
extern int team_mate;
extern int winner_done;
extern int winner_mode;
extern int network_mes_mode;
extern int cdchecked;
extern int network_slot;
extern int trying_to_exit;
extern int local_players;
extern int draw_type;
extern int network_buggered;
extern int replay_cheat;
extern int w95;
extern int gave_up;
extern int send_finished;
extern int game_frame;
extern int game_track;
extern int prev_track;
extern int view0_cnt;
extern int view1_cnt;
extern int I_Would_Like_To_Quit;
extern int Quit_Count;
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
void firework_screen();
void updatescreen();
void draw_road(uint8 *a1, char *a2, float *a3, int a4, int a5);
int main(int argc, const char **argv, const char **envp);
void play_game_init();
void play_game_uninit();
void winner_race();
int champion_race();
void play_game(int a1, int a2, int a3);
void game_keys(int64 a1);
void mesminus();
void mesplus();
void carminus();
void carplus();
void viewminus(int iPlayer);
void viewplus(int iPlayer);
void game_copypic(uint8 *pSrc, uint8 *pDest, int iCarIdx);
void test_w95();
void *malloc2(int iSize, void *pPtr, int *pRegsDi);
void free2(void *ptr);

//-------------------------------------------------------------------------------------------------
#endif

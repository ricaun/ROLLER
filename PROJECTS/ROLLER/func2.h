#ifndef _ROLLER_FUNC2_H
#define _ROLLER_FUNC2_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

typedef struct
{
  uint8 byP1left;
  uint8 byP1right;
  uint8 byP1up;
  uint8 byP1down;
  uint8 byP1upgear;
  uint8 byP1downgear;
  uint8 byP1cheat;
  uint8 byP2left;
  uint8 byP2right;
  uint8 byP2up;
  uint8 byP2down;
  uint8 byP2upgear;
  uint8 byP2downgear;
  uint8 byP2cheat;
} tUserKey;

//-------------------------------------------------------------------------------------------------

extern int write_key;
extern int read_key;
extern uint8 mapping[];
extern int twoparter;
extern tUserKey userkey;
extern uint8 key_buffer[];
extern char config_buffer[8192];
extern char language_buffer[8192];
extern int no_mem;

//-------------------------------------------------------------------------------------------------

int draw_smoke(int a1, int a2);
int test_panel(int a1, char *a2);
void ZoomString(char *a1, int a2, int a3, int a4, int a5);
void ZoomSub(char *a1, int a2, int a3, int a4, int a5);
int zoom_letter(int a1, uint8 a2, void *a3, void *a4, char *a5, float a6);
int print_block(char *a1, int a2, int a3);
int print_damage(uint8 *a1, int *a2, int a3);
int print_pos(int result, int a2, int a3);
void free_game_memory();
int readmode();
void key_handler(
        int a1,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7);
void claim_key_int();
int fatkbhit();
int fatgetch();
void release_key_int();
int clear_border(int a1, int a2, int a3, int a4);
int DisplayFree();
void setdirectory(const char *szAppPath);
int FindShades();
int nearest_colour(int a1, int a2, int a3);
int select_view(int a1);
int mini_prt_string(int a1, char *a2);
int mini_prt_string_rev(int a1, char *a2);
char mini_prt_right(int a1, char *a2, int a3, int a4);
char mini_prt_centre(int a1, char *a2, int a3, int a4);
char prt_right(int a1, char *a2, int a3);
int prt_string(int a1, char *a2);
int prt_letter(int a1, uint8 a2, void *a3, void *a4, int a5);
int prt_letter_rev(int a1, uint8 a2, void *a3, void *a4, int a5);
int prt_stringcol(int a1, char *a2, int a3, int a4, char a5);
char prt_rightcol(int a1, char *a2, int a3, int a4, char a5);
char prt_centrecol(int a1, char *a2, int a3, int a4, char a5);
int prt_lettercol(int a1, uint8 a2, void *a3, void *a4, char a5);
char display_paused();
void enable_keyboard();
void disable_keyboard();
void *save_fatal_config();
void load_fatal_config();
void getconfigvalue(const char *szConfigText, const char *szVarName, int *piOutVal, int iMin, int iMax);
void getconfigvalueuc(const char *szConfigText, const char *szVarName, uint8 *pbyOutVal, int iMin, int iMax);
int displaycalibrationbar(int a1, int a2, int a3);
int blankwindow(int a1, int a2, int a3, int a4);
int volumebar(int a1, int a2);
void remove_uncalibrated();
void LoadRecords();
void *SaveRecords();
int copy_int(int a1, int a2);
int ShowATime(int a1, int a2, float a3, int a4, int a5);
void setmodex();
uint8 modexsethardware();
void modexclearscreen();
void copyscreenmodex(uint8 *pSrc, uint8 *pDest);
char start_zoom(char *a1, int a2);
char small_zoom(char *a1);
char subzoom(char *a1);
void make_time(char *a1, int a2, float a3);
int check_machine_speed();
void load_language_file(const char *szFilename, int iUseConfigBuffer);
int do_blip(int a1, int a2);

//-------------------------------------------------------------------------------------------------
#endif

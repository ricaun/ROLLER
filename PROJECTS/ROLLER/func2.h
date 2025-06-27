#ifndef _ROLLER_FUNC2_H
#define _ROLLER_FUNC2_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

typedef enum
{
  USERKEY_P1LEFT = 0,
  USERKEY_P1RIGHT = 1,
  USERKEY_P1UP = 2,
  USERKEY_P1DOWN = 3,
  USERKEY_P1UPGEAR = 4,
  USERKEY_P1DOWNGEAR = 5,
  USERKEY_P1CHEAT = 6,
  USERKEY_P2LEFT = 7,
  USERKEY_P2RIGHT = 8,
  USERKEY_P2UP = 9,
  USERKEY_P2DOWN = 10,
  USERKEY_P2UPGEAR = 11,
  USERKEY_P2DOWNGEAR = 12,
  USERKEY_P2CHEAT = 13
} eUserKey;

//-------------------------------------------------------------------------------------------------

extern int write_key;
extern int read_key;
extern uint8 mapping[];
extern int twoparter;
extern int userkey[14];
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
void FindShades();
int nearest_colour(int iR, int iB, int iG);
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
void save_fatal_config();
void load_fatal_config();
void getconfigvalue(const char *szConfigText, const char *szVarName, int *piOutVal, int iMin, int iMax);
void getconfigvalueuc(const char *szConfigText, const char *szVarName, uint8 *pbyOutVal, int iMin, int iMax);
int displaycalibrationbar(int a1, int a2, int a3);
int blankwindow(int a1, int a2, int a3, int a4);
int volumebar(int a1, int a2);
void remove_uncalibrated();
void LoadRecords();
void SaveRecords();
uint8 *copy_int(uint8 *pDest, uint32 uiValue);
int ShowATime(int a1, int a2, float a3, int a4, int a5);
void setmodex();
uint8 modexsethardware();
void modexclearscreen();
void copyscreenmodex(uint8 *pSrc, uint8 *pDest);
char start_zoom(char *a1, int a2);
char small_zoom(char *a1);
char subzoom(char *a1);
void make_time(char *a1, int a2, float a3);
void check_machine_speed();
void load_language_file(const char *szFilename, int iUseConfigBuffer);
int do_blip(int a1, int a2);

//-------------------------------------------------------------------------------------------------
#endif

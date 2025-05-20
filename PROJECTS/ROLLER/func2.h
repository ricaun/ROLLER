#ifndef _ROLLER_FUNC2_H
#define _ROLLER_FUNC2_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

int draw_smoke(int a1, int a2);
int test_panel(int a1, char *a2);
void ZoomString(char *a1, int a2, int a3, int a4, int a5);
void ZoomSub(char *a1, int a2, int a3, int a4, int a5);
int zoom_letter(int a1, unsigned __int8 a2, void *a3, void *a4, char *a5, float a6);
int print_block(char *a1, int a2, int a3);
int print_damage(unsigned __int8 *a1, int *a2, int a3);
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
int claim_key_int(int a1, int a2);
int fatkbhit();
int fatgetch();
int release_key_int();
int clear_border(int a1, int a2, int a3, int a4);
int DisplayFree();
int setdirectory(char *a1);
int FindShades();
int nearest_colour(int a1, int a2, int a3);
int select_view(int a1);
int mini_prt_string(int a1, char *a2);
int mini_prt_string_rev(int a1, char *a2);
char mini_prt_right(int a1, char *a2, int a3, int a4);
char mini_prt_centre(int a1, char *a2, int a3, int a4);
char prt_right(int a1, char *a2, int a3);
int prt_string(int a1, char *a2);
int prt_letter(int a1, unsigned __int8 a2, void *a3, void *a4, int a5);
int prt_letter_rev(int a1, unsigned __int8 a2, void *a3, void *a4, int a5);
int prt_stringcol(int a1, char *a2, int a3, int a4, char a5);
char prt_rightcol(int a1, char *a2, int a3, int a4, char a5);
char prt_centrecol(int a1, char *a2, int a3, int a4, char a5);
int prt_lettercol(int a1, unsigned __int8 a2, void *a3, void *a4, char a5);
char display_paused();
void enable_keyboard();
void disable_keyboard();
void *save_fatal_config();
int load_fatal_config();
int getconfigvalue(int a1, int a2, int *a3, int a4, int a5);
char getconfigvalueuc(int a1, int a2, char *a3, int a4, int a5);
int displaycalibrationbar(int a1, int a2, int a3);
int blankwindow(int a1, int a2, int a3, int a4);
int volumebar(int a1, int a2);
int remove_uncalibrated();
void LoadRecords();
void *SaveRecords();
int copy_int(int a1, int a2);
int ShowATime(int a1, int a2, float a3, int a4, int a5);
void setmodex();
unsigned __int8 modexsethardware();
void modexclearscreen();
void copyscreenmodex(uint8 *pSrc, uint8 *pDest);
char start_zoom(char *a1, int a2);
char small_zoom(char *a1);
char subzoom(char *a1);
void make_time(char *a1, int a2, float a3);
int check_machine_speed();
void load_language_file(int a1, int a2);
int do_blip(int a1, int a2);

//-------------------------------------------------------------------------------------------------
#endif
#ifndef _ROLLER_FRONTEND_H
#define _ROLLER_FRONTEND_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

extern int non_competitors[];
extern int player_started[];
extern int player_invul[];
extern int p_texs_off;
extern int p_tex_size;
extern int quit_game;
extern int players;
extern int front_fade;
extern int frontend_on;
extern int cd_cheat;
extern int my_control;
extern int my_car;
extern int my_number;
extern int my_invul;
extern int FastestLap;
extern int racers;
extern uint32 cheat_mode;
extern int Race;
extern int switch_types;
extern int players_waiting;
extern int switch_sets;
extern int time_to_start;
extern int I_Quit;
extern int StartPressed;
extern int waste;
extern int switch_same;
extern int car_request;
extern uint8 oldkeys[];
extern char my_name[];

//-------------------------------------------------------------------------------------------------

int *title_screens(unsigned int a1, short *a2, char *a3, unsigned int a4);
void copy_screens(int a1, int a2, int a3, char *a4);
void select_screen(int a1);
void select_disk(int a1, int a2, int a3);
int select_car(int a1, int a2, unsigned int a3, int a4);
void select_configure(int a1, int a2, int a3, int a4);
int front_displaycalibrationbar(int result, int a2, int a3);
int front_volumebar(int a1, int a2, int a3);
void select_players(int a1, int a2, int a3, int a4);
void *select_type(int a1, int a2, int a3, int a4);
void *select_track(int a1, int a2, int a3, int a4);
void save_params();
void reset_params();
int NetworkWait(int a1, int a2, int a3, int a4);
char *loadcheatnames(int a1, int a2, int a3, int a4);
int CheckNames(char *a1, int a2);
int restart_net_game(int a1);

//-------------------------------------------------------------------------------------------------
#endif
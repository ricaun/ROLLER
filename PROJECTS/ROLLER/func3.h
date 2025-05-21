#ifndef _ROLLER_FUNC3_H
#define _ROLLER_FUNC3_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

int winner_screen(int a1, char a2, void *a3);
int StoreResult();
void RaceResult(int a1, int a2, int a3, char *a4);
void TimeTrials(int a1, int a2, int a3, char *a4);
void ChampionshipStandings(int a1, int a2, int a3, char *a4);
void TeamStandings(int a1, int a2, int a3, char *a4);
void ShowLapRecords(int a1, int a2, int a3, char *a4);
void show_3dmap(float a1, int a2, int a3);
void DrawCar(int a1, int a2, float a3, int a4, char a5);
void *championship_winner(int a1, int a2, int a3, char *a4);
int print_mem_used();
uint8 *try_load_picture(const char *szFile);
void *save_champ(int a1);
int load_champ(int a1);
unsigned __int8 *lod_champ_char(unsigned __int8 *a1, void *a2);
void *sav_champ_char(int *a1, void *a2);
int sav_champ_int(int a1, int a2);
int check_saves(int a1, int a2, int a3);
void ResultRoundUp(int a1, int a2, int a3, char *a4);
int RollCredits(void *a1, void *a2, unsigned int a3);
int ChampionshipOver(int a1, int a2, int a3, char *a4);
void *EndChampSequence(int a1, int a2, int a3, int a4);
void network_fucked(int a1, int a2, int a3);
void no_cd(int a1, int a2, int a3, char *a4);
int name_cmp(char *szName1, char *szName2);
void name_copy(char *szDest, char *szSrc);
int loadtracksample(int a1);
void *front_letter(int a1, unsigned __int8 a2, void *a3, void *a4, int a5, char a6);
int scale_letter(int a1, unsigned __int8 a2, void *a3, void *a4, int a5, char a6, int a7);
int front_text(int a1, unsigned __int8 *a2, int a3, int a4, int a5, int a6, char a7, unsigned int a8);
unsigned __int8 scale_text(
        int a1,
        char *a2,
        int a3,
        int a4,
        int a5,
        int a6,
        char a7,
        unsigned int a8,
        int a9,
        int a10);
int clear_screen(int a1, int a2);
void display_picture(void *pDest, const void *pSrc);
unsigned __int8 *display_block(int a1, int a2, int a3, unsigned int a4, int a5, int a6);
uint8 *load_picture(const char *szFile);
int AllocateCars(int a1);
int check_cars(int a1, int a2, int a3);
char *select_messages();
void show_received_mesage();
int select_netslot();

//-------------------------------------------------------------------------------------------------
#endif
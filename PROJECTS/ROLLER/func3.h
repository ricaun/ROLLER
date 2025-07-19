#ifndef _ROLLER_FUNC3_H
#define _ROLLER_FUNC3_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

extern char save_slots[4][13];
extern int send_message_to;
extern char rec_mes_buf[32];
extern int result_order[16];
extern int result_design[16];
extern int result_control[16];
extern int send_status;
extern int restart_net;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  int iWidth;
  int iHeight;
  int iDataOffset;
} tBlockHeader;

//-------------------------------------------------------------------------------------------------

int winner_screen(int a1, char a2, void *a3);
int StoreResult();
void RaceResult(int a1, int a2, int a3, char *a4);
void TimeTrials(int a1, int a2, int a3, char *a4);
void ChampionshipStandings(int a1, int a2, int a3, char *a4);
void TeamStandings(int a1, int a2, int a3, char *a4);
void ShowLapRecords(int a1, int a2, int a3, char *a4);
void show_3dmap(float a1, int a2, int a3);
void DrawCar(uint8 *pScrBuf, eCarDesignIndex iCarDesignIndex, float fDistance, int iAngle, char byAnimFrame);
void *championship_winner(int a1, int a2, int a3, char *a4);
int print_mem_used();
uint8 *try_load_picture(const char *szFile);
void *save_champ(int a1);
int load_champ(int iSlot);
uint8 *lod_champ_char(uint8 *pSrc, int *piValue);
uint8 *sav_champ_char(uint8 *pSrc, int *piValue); //actually loads an int
uint8 *sav_champ_int(uint8 *pDest, int iValue);
int check_saves(int a1, int a2, int a3);
void ResultRoundUp(int a1, int a2, int a3, char *a4);
int RollCredits(void *a1, void *a2, unsigned int a3);
int ChampionshipOver(int a1, int a2, int a3, char *a4);
void *EndChampSequence(int a1, int a2, int a3, int a4);
void network_fucked(int a1, int a2, int a3);
void no_cd();
int name_cmp(char *szName1, char *szName2);
void name_copy(char *szDest, char *szSrc);
void loadtracksample(int track_number);
void front_letter(tBlockHeader *pFont, uint8 byCharIdx, int *iX, int *iY, const char *szStr, uint8 byColorReplace);
void scale_letter(tBlockHeader *pFont, uint8 byChar, int *iCursorX, int *iCursorY, char *mappingTable, char byColorReplace, int iScaleSize);
void front_text(tBlockHeader *pFont,
                const char *szText,
                const uint8 *mappingTable,
                int *pCharVOffsets,
                int iX,
                int iY,
                uint8 byColorReplace,
                int iAlignment);
void scale_text(tBlockHeader *pFont,
                char *szText,
                const char *mappingTable,
                int *pCharVOffsets,
                int iX,
                int iY,
                char byColorReplace,
                unsigned int uiAlignment,
                int iClipLeft,
                int iClipRight);
int clear_screen(int a1, int a2);
void display_picture(void *pDest, const void *pSrc);
void display_block(uint8 *pDest, tBlockHeader *pSrc, int iBlockIdx, int iX, int iY, int iTransparentColor);
uint8 *load_picture(const char *szFile);
int AllocateCars();
void check_cars();
char *select_messages();
void show_received_mesage();
int select_netslot();

//-------------------------------------------------------------------------------------------------
#endif

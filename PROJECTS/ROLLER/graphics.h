#ifndef _ROLLER_GRAPHICS_H
#define _ROLLER_GRAPHICS_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

extern int gfx_size;
extern int NoOfTextures;

//-------------------------------------------------------------------------------------------------

void plotxyz(float a1, float a2, float a3, char a4);
void linexyz(float fX1, float fY1, float fZ1, float fX2, float fY2, float fZ2, char a7);
void compout(uint8 *pScrBuf, int iX0, int iY0, int iX1, int iY1, uint8 byColor);
void line(uint8 *pScrBuf, int iX0, int iY0, int iX1, int iY1, char byColor);
void LoadPanel();
int InitRemaps();
int LoadGenericCarTextures(int a1, int a2, int a3, int a4);
int LoadCarTexture(int a1, char a2);
int LoadBldTextures(int a1, int a2, int a3, int a4);
int LoadTextures(int a1, int a2, int a3);
int init_remap(int result, int a2, int a3, int a4);
int sort_small_texture(int a1, char *a2, int a3);
void *sort_texture(char *a1, int a2);
void *sort_mini_texture(char *a1, int a2);
int drbox(int a1, int a2, int a3, int a4, char a5);
char *box(int a1, int a2, int a3, int a4, char a5);
int SetVideoMode(char a1);

//-------------------------------------------------------------------------------------------------
#endif
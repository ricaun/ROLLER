#ifndef _ROLLER_GRAPHICS_H
#define _ROLLER_GRAPHICS_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

extern char revs_files1[6][13];
extern char revs_files2[6][13];
extern int car_remap[4096];
extern int cargen_remap[256];
extern int bld_remap[256];
extern int num_textures[32];
extern int remap_tex[256];
extern int mode_c[256];
extern int gfx_size;
extern int NoOfTextures;

//-------------------------------------------------------------------------------------------------

void plotxyz(float fWorldX, float fWorldY, float fWorldZ, char byColor);
void linexyz(uint8 *pScrBuf, float fX1, float fY1, float fZ1, float fX2, float fY2, float fZ2, uint8 byColor);
void compout(uint8 *pScrBuf, int iX0, int iY0, int iX1, int iY1, uint8 byColor);
void line(uint8 *pScrBuf, int iX0, int iY0, int iX1, int iY1, uint8 byColor);
void LoadPanel();
void InitRemaps();
int LoadGenericCarTextures(int a1, int a2, int a3, int a4);
int LoadCarTexture(int a1, char a2);
int LoadBldTextures(int a1, int a2, int a3, int a4);
int LoadTextures(int a1, int a2, int a3);
void init_remap(uint8 *pTextureBaseAddr, int iRemapType, int iNumBlocks, int iIsLowRes);
void sort_small_texture(uint8 *pDest, uint8 *pSrc, int iNumBlocks);
void sort_texture(uint8 *pTexData, int iNumTextures);
void *sort_mini_texture(char *a1, int a2);
int drbox(int a1, int a2, int a3, int a4, char a5);
char *box(int a1, int a2, int a3, int a4, char a5);
int SetVideoMode(char a1);

//-------------------------------------------------------------------------------------------------
#endif
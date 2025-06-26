#ifndef _ROLLER_TRANSFRM_H
#define _ROLLER_TRANSFRM_H
//-------------------------------------------------------------------------------------------------

extern float vk1;
extern int xp;
extern float vk2;
extern float vk3;
extern float vk4;
extern float vk5;
extern float vk6;
extern float vk7;
extern float vk8;
extern float vk9;
extern int yp;

//-------------------------------------------------------------------------------------------------

void calculatetransform(
        int iTrackChunkIdx,
        int iDirection,
        int iElevation,
        int iTilt,
        float fViewX,
        float fViewY,
        float fViewZ,
        float fPosX,
        float fPosY,
        float fPosZ);
void initlocaltrack();
void initlocalsection(int iChunkIdx);
void dopitchchanges(int a1, int a2);
int getpitchchange(int a1, int a2, int a3);
void getworldangles(int iYaw, int iPitch, int iRoll, int iChunkIdx, int *iAzimuth, int *iElevation, int *iBank);
int getlocalangles(int a1, int a2, int a3, int iChunkIdx, int *a5, int *a6, int *a7);

//-------------------------------------------------------------------------------------------------
#endif
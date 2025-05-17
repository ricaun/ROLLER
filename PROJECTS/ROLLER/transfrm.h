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

//-------------------------------------------------------------------------------------------------
#endif
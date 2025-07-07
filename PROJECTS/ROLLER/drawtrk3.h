#ifndef _ROLLER_DRAWTRK3_H
#define _ROLLER_DRAWTRK3_H
//-------------------------------------------------------------------------------------------------

extern int view_limit;
extern int num_pols;

//-------------------------------------------------------------------------------------------------

int CalcVisibleTrack(int a1, unsigned int a2);
int DrawTrack3(int *a1, int a2, int a3, float *a4, char *a5);
void subdivide(
        int a1,
        int a2,
        float a3,
        float a4,
        float a5,
        float a6,
        float a7,
        float a8,
        float a9,
        float a10,
        float a11,
        float a12,
        float a13,
        float a14,
        int a15,
        int a16);
int dodivide(
        float a1,
        float a2,
        float a3,
        float a4,
        float a5,
        float a6,
        float a7,
        float a8,
        float a9,
        float a10,
        float a11,
        float a12,
        int a13,
        int a14,
        int a15,
        int a16,
        int a17,
        int a18,
        int a19,
        int a20,
        int a21,
        int a22,
        int a23,
        int a24);
int facing_ok(
        float a1,
        float a2,
        float a3,
        float a4,
        float a5,
        float a6,
        float a7,
        float a8,
        float a9,
        float a10,
        float a11,
        float a12);
int Zcmp(float *a1, float *a2);
void set_starts(unsigned int uiType);

//-------------------------------------------------------------------------------------------------
#endif
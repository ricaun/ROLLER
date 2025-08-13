#ifndef _ROLLER_DRAWTRK3_H
#define _ROLLER_DRAWTRK3_H
//-------------------------------------------------------------------------------------------------
#include "polyf.h"
#include "types.h"
//-------------------------------------------------------------------------------------------------

extern int showsub;
extern int view_limit;
extern int divtype;
extern int tex_hgt;
extern int polyysize;
extern int polyxsize;
extern uint8 *subptr;
extern int fliptype;
extern int subpolytype;
extern tPolyParams *subpoly;
extern int tex_wid;
extern int flatpol;
extern tPolyParams RoadPoly;
extern int start_sect;
extern int gap_size;
extern int first_size;
extern int TrackSize;
extern int backwards;
extern int next_front;
extern int mid_sec;
extern int back_sec;
extern int front_sec;
extern int min_sub_size;
extern int num_pols;
extern int small_poly;

//-------------------------------------------------------------------------------------------------

int CalcVisibleTrack(int iCarIdx, unsigned int uiViewMode);
int DrawTrack3(int *a1, int a2, int a3, float *a4, char *a5);
void subdivide(uint8 *pDest, tPolyParams *polyParams,
               float fX0_3D, float fY0_3D, float fZ0_3D,
               float fX1_3D, float fY1_3D, float fZ1_3D,
               float fX2_3D, float fY2_3D, float fZ2_3D,
               float fX3_3D, float fY3_3D, float fZ3_3D,
               int iSubpolyType, int bHalfResTex);
void dodivide(float fX0_3D, float fY0_3D, float fZ0_3D,
              float fX1_3D, float fY1_3D, float fZ1_3D,
              float fX2_3D, float fY2_3D, float fZ2_3D,
              float fX3_3D, float fY3_3D, float fZ3_3D,
              int iScreenX0, int iScreenY0, int iScreenX1, int iScreenY1, int iScreenX2, int iScreenY2, int iScreenX3, int iScreenY3,
              int iTexU, int iTexV, int iTexWid, int iTexHgt);
int facing_ok(float fX0, float fY0, float fZ0,
              float fX1, float fY1, float fZ1,
              float fX2, float fY2, float fZ2,
              float fX3, float fY3, float fZ3);
int Zcmp(const void *pTrackView1, const void *pTrackView2);
void set_starts(unsigned int uiType);

//-------------------------------------------------------------------------------------------------
#endif
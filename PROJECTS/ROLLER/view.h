#ifndef _ROLLER_VIEW_H
#define _ROLLER_VIEW_H
//-------------------------------------------------------------------------------------------------

extern int chaseview[2];
extern int NearTow;

//-------------------------------------------------------------------------------------------------

int calculateview(int a1, int a2, int a3);
int initcarview(int result, int a2);
int newchaseview(int a1, int a2);

//-------------------------------------------------------------------------------------------------
#endif
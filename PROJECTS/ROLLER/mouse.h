#ifndef _ROLLER_MOUSE_H
#define _ROLLER_MOUSE_H
//-------------------------------------------------------------------------------------------------

int initmouse();
int mousexy();
int mousebut(unsigned __int16 a1, int a2, int a3, int a4);
int checkmouse(int a1, int a2, int a3, int a4);
int drmouse(int a1, int a2, int a3, int a4);
void *plotmouse();

//-------------------------------------------------------------------------------------------------
#endif
#ifndef _ROLLER_COMMS_H
#define _ROLLER_COMMS_H
//-------------------------------------------------------------------------------------------------

int select_comport(unsigned __int16 a1, char *a2, unsigned int a3);
int stringwidth(char *a1);
int select_modemstuff(int a1);
int loadmodemnames();
void select_modem();
char *getprintstring(char *a1, int a2);
__int64 display_essentials(int a1, int a2, int a3);
void check16550(int iPort, int a2);

//-------------------------------------------------------------------------------------------------
#endif
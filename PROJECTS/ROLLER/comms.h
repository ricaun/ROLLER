#ifndef _ROLLER_COMMS_H
#define _ROLLER_COMMS_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

extern int serial_port;
extern int modem_port;
extern int modem_baud;
extern int no_16550;
extern int current_modem;
extern char modem_initstring[51];
extern char modem_phone[53];
extern int modem_tone;
extern int modem_call;

//-------------------------------------------------------------------------------------------------

int select_comport(uint16 a1, char *a2, unsigned int a3);
int stringwidth(char *a1);
int select_modemstuff(int a1);
int loadmodemnames();
void select_modem();
char *getprintstring(char *a1, int a2);
int64 display_essentials(int a1, int a2, int a3);
void check16550(int iPort, int a2);

//-------------------------------------------------------------------------------------------------
#endif

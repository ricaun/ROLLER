#ifndef _ROLLER_LOADTRAK_H
#define _ROLLER_LOADTRAK_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

extern uint8 TrackSelect;

//-------------------------------------------------------------------------------------------------

void loadtrack(void *result, int a2);
int read_backs(int *a1, int a2, int a3, int a4);
char *read_texturemap(int a1);
char *read_bldmap(char **a1);
int readstuntdata(int a1, int a2, int a3, int a4);
void activatestunts();
int ReadAnimData(int result, int a2);
int readline(int a1, const char *a2, double *a3);
char *memgets(char *a1, int *a2);
char *readline2(int *a1, const char *a2, ...);
double *rotatepoint(
        double a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double *a7,
        double *a8,
        double *a9);
int setpoint(int a1, int a2, double a3, double a4, double a5);
int setgpoint(int a1, int a2, double a3, double a4, double a5);
int resetcars();
char *min_skip_stuff(int *a1);

//-------------------------------------------------------------------------------------------------
#endif
#ifndef _ROLLER_ROLLER_H
#define _ROLLER_ROLLER_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------

// functions added by ROLLER
int InitSDL();
void ShutdownSDL();
void UpdateSDL();
FILE *ROLLERfopen(const char *szFile, const char *szMode); //tries to open file with both all caps and all lower case
int IsCDROMDevice(const char *szPath);

//-------------------------------------------------------------------------------------------------
#endif
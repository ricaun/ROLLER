#ifndef _ROLLER_SOUND_H
#define _ROLLER_SOUND_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

int getcompactedfilelength(const char *szFile);
int initmangle(const char *szFile);
int uninitmangle();
int loadcompactedfile(const char *szFile, void *pBuf);
void readmangled(uint8 *pBufRet, int iLength);
void loadcompactedfilepart(uint8 *pDestination, int iDestLength);
uint8 *unmangleGet(unsigned int uiPos, unsigned int uiCount);

//-------------------------------------------------------------------------------------------------
#endif
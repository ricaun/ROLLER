#ifndef _ROLLER_SOUND_H
#define _ROLLER_SOUND_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
//-------------------------------------------------------------------------------------------------

typedef struct
{
  DWORD edi, esi, ebp, reserved, ebx, edx, ecx, eax;
  WORD  flags, es, ds, fs, gs, ip, cs, sp, ss;
} DPMI_RMI;

//-------------------------------------------------------------------------------------------------

extern unsigned int musicon;
extern unsigned int soundon;
extern int palette_brightness;
extern int MusicCard;
extern int MusicCD;
extern int MusicPort;
extern int SongPtr;
extern int SongHandle;
extern uint8 unmangleinbuf[];
extern int unmangleinpoff;
extern uint8 *unmangledst;
extern int unmangleoverflow;
extern FILE *unmanglefile;
extern int unmanglebufpos;
extern DPMI_RMI RMI;
extern int optionssong;
extern int titlesong;

//-------------------------------------------------------------------------------------------------

void realmode(uint8 byRealModeInterrupt);
int loadDOS(int a1, void *a2, int *a3);
int claimDOS(int a1, void *a2);
int releaseDOS(__int16 a1, int a2, int a3, int a4);
int setpal(int a1, int a2, void *a3, void *a4);
void resetpal();
int Initialise_SOS();
int updatejoy();
int readuserdata(int result);
int tickhandler(int a1, int a2, int a3, int a4);
void claim_ticktimer();
int release_ticktimer();
int Uninitialise_SOS();
void loadsamples();
int loadfatalsample();
void *releasesamples();
int play();
void stop(int a1, int a2);
int devicespecificinit(int a1, int a2, int a3, int a4);
int initgus();
void *devicespecificuninit();
int readsoundconfig(int a1);
char *FindConfigVar(char *a1, const char *a2);
void loadfile(const char *szFile, void *pBuf, unsigned int uiSize, int iIsSound);
int ReadJoys(int *a1);
int check_joystickpresence();
int initsounds();
int stopallsamples();
int pannedsample(int result, int a2, int a3);
int speechonly(int result, int a2, int a3, int a4);
int speechsample(int result, int a2, int a3, int a4);
int analysespeechsamples();
int dospeechsample(__int64 a1);
int loadfrontendsample(int result);
int frontendsample(int a1);
void *remove_frontendspeech();
int sfxplaying(int a1);
int cheatsampleok(int a1);
int sfxsample(__int64 a1);
int sample2(
        __int64 rax0,
        int ecx0,
        int ebx0,
        __int64 a1,
        int a2,
        int a3,
        int a4,
        int a5);
int sfxpend(int a1, int a2, int a3);
int enginesounds2(int result, int a2);
int enginesounds(int result);
int loopsample(int result, unsigned int a2, int a3, int a4, int a5);
void enginesound(int a1, float a2, float a3, float a4, int a5);
int startmusic(int result);
int stopmusic(int a1, int a2);
int load_language_map();
int initmusic();
void fade_palette(int a1, int a2, int j, int a4);
int set_palette(int result);
int check_joystick_usage();
char convertname(char *a1);
char *decode(char *result, int a2, int a3, int a4);
int loadasample(int a1);
int select8bitdriver(int result, int a2);
int resetsamplearray();
void reinitmusic(int a1, int a2);
int waitsampledone(int result);
int getcompactedfilelength(const char *szFile);
int initmangle(const char *szFile);
int uninitmangle();
int loadcompactedfile(const char *szFile, void *pBuf);
void readmangled(uint8 *pBufRet, int iLength);
void loadcompactedfilepart(uint8 *pDestination, int iDestLength);
uint8 *unmangleGet(unsigned int uiPos, unsigned int uiCount);

//-------------------------------------------------------------------------------------------------
#endif
#ifndef _ROLLER_SOUND_H
#define _ROLLER_SOUND_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifdef IS_WINDOWS
#include <Windows.h>
#endif
//-------------------------------------------------------------------------------------------------

typedef struct
{
  DWORD edi, esi, ebp, reserved, ebx, edx, ecx, eax;
  WORD  flags, es, ds, fs, gs, ip, cs, sp, ss;
} DPMI_RMI;

//-------------------------------------------------------------------------------------------------

extern int musicon;
extern int soundon;
extern int allengines;
extern int palette_brightness;
extern void *pal_selector;
extern int writeptr;
extern int readptr;
extern int SoundCard;
extern int MusicVolume;
extern int MusicCard;
extern int MusicCD;
extern int MusicPort;
extern int SongPtr;
extern int SongHandle;
extern uint8 unmangleinbuf[1024];
extern char lang[512];
extern int TrackMap[32];
extern char TextExt[64];
extern char SampleExt[64];
extern int copy_multiple[8192];
extern int unmangleinpoff;
extern uint8 *unmangledst;
extern int unmangleoverflow;
extern FILE *unmanglefile;
extern int unmanglebufpos;
extern int s7;
extern int MIDIHandle;
extern tColor *pal_addr;
extern int DIGIHandle;
extern int frames;
extern uint32 tickhandle;
extern DPMI_RMI RMI;
extern int optionssong;
extern int titlesong;
extern int delaywrite;
extern int delayread;
extern int languages;

//-------------------------------------------------------------------------------------------------

void realmode(uint8 byRealModeInterrupt);
bool loadDOS(const char *szFilename, void **out_buffer);
int claimDOS(int a1, void *a2);
int releaseDOS(int16 a1, int a2, int a3, int a4);
bool setpal(const char *szFilename);
void blankpal();
void resetpal();
void Initialise_SOS();
int updatejoy();
int readuserdata(int result);
int tickhandler(int a1, int a2, int a3, int a4);
void claim_ticktimer(unsigned int uiRateHz, int a2);
void release_ticktimer();
void Uninitialise_SOS();
void loadsamples();
int loadfatalsample();
void *releasesamples();
int play();
void stop();
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
int dospeechsample(int64 a1);
int loadfrontendsample(int result);
int frontendsample(int a1);
void *remove_frontendspeech();
int sfxplaying(int a1);
int cheatsampleok(int a1);
int sfxsample(int64 a1);
int sample2(
        int64 rax0,
        int ecx0,
        int ebx0,
        int64 a1,
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
void load_language_map();
int initmusic();
void fade_palette(int iPaletteBrightness);
void set_palette(int iBrightness);
int check_joystick_usage();
char convertname(char *a1);
char *decode(char *result, int a2, int a3, int a4);
int loadasample(int a1);
void select8bitdriver();
int resetsamplearray();
void reinitmusic(int a1, int a2);
int waitsampledone(int result);
int getcompactedfilelength(const char *szFile);
int initmangle(const char *szFile);
int uninitmangle();
int loadcompactedfile(const char *szFile, uint8 *pBuf);
void readmangled(uint8 *pBufRet, int iLength);
void loadcompactedfilepart(uint8 *pDestination, uint32 uiDestLength);
uint8 *unmangleGet(unsigned int uiPos, unsigned int uiCount);

//-------------------------------------------------------------------------------------------------
#endif

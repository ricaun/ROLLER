#ifndef _ROLLER_SOUND_H
#define _ROLLER_SOUND_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

int realmode(char a1, int a2, int a3, int a4);
int loadDOS(int a1, void *a2, int *a3);
int claimDOS(int a1, void *a2);
int releaseDOS(__int16 a1, int a2, int a3, int a4);
int setpal(int a1, int a2, void *a3, void *a4);
int blankpal(int a1, int a2, int a3, int a4);
int resetpal();
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
int stop(int a1, int a2, int a3, int a4);
int devicespecificinit(int a1, int a2, int a3, int a4);
int initgus();
void *devicespecificuninit();
int readsoundconfig(int a1);
char *FindConfigVar(char *a1, const char *a2);
int loadfile(int a1, void *a2, unsigned int *a3, int a4);
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
int reinitmusic(int result, int a2, int a3, int a4);
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
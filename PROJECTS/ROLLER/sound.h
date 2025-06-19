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

typedef struct
{
  int handles[16];
} tSampleHandleCar;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  void *pSample;
  uint16 unSegment;
  int iLength;
  int iByteOffset;
  int iUnk2;
  int iVolume;
  int iSampleIndex;
  int unknown[7];
  int iPitch;
  int iUnk3;
  int iPan;
  int unknown2[13];
} tSampleData;

//-------------------------------------------------------------------------------------------------

extern int samplespending;
extern int writesample;
extern int readsample;
extern int lastsample;
extern int musicon;
extern int soundon;
extern int allengines;
extern int cheat_samples;
extern int palette_brightness;
extern void *pal_selector;
extern char SourcePath[64];
extern char DestinationPath[64];
extern char languagename[32];
extern int writeptr;
extern int readptr;
extern int SoundCard;
extern int SoundPort;
extern int SoundIRQ;
extern int SoundDMA;
extern int EngineVolume;
extern int SFXVolume;
extern int SpeechVolume;
extern int MusicVolume;
extern int MusicCard;
extern int MusicCD;
extern int MusicPort;
extern int SongPtr;
extern int SongHandle;
extern int CDSong[20];
extern int GMSong[21];
extern int Joy1used;
extern int Joy2used;
extern int x1ok;
extern int y1ok;
extern int x2ok;
extern int y2ok;
extern int bitaccept;
extern int holdmusic;
extern uint8 unmangleinbuf[1024];
extern int lastvolume[16];
extern int lastpitch[16];
extern int lastpan[16];
extern uint32 SampleLen[120];
extern uint8 *SamplePtr[120];
extern char Sample[120][15];
extern char lang[16][32];
extern int TrackMap[32];
extern char TextExt[64];
extern char SampleExt[64];
extern int HandleCar[32];
extern int HandleSample[32];
extern int car_to_player[8][2];
extern int player_to_car[16];
extern int copy_multiple[512][16];
extern int unmangleinpoff;
extern uint8 *unmangledst;
extern int unmangleoverflow;
extern FILE *unmanglefile;
extern int unmanglebufpos;
extern volatile int s7;
extern void *MT32Data;
extern void *FMDrums;
extern void *FMInstruments;
extern int MIDIHandle;
extern tColor *pal_addr;
extern int DIGIHandle;
extern volatile int frames;
extern char Song[20][15];
extern uint32 tickhandle;
extern DPMI_RMI RMI;
extern int nummusictracks;
extern int winchampsong;
extern int winsong;
extern int leaderboardsong;
extern int optionssong;
extern int titlesong;
extern int delaywrite;
extern int delayread;
extern int numsamples;
extern int cheatsample;
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
void claim_ticktimer(unsigned int uiRateHz);
void release_ticktimer();
void Uninitialise_SOS();
void loadsamples();
void loadfatalsample();
void freefatalsample();
void releasesamples();
int play();
void stop();
int devicespecificinit(int a1, int a2, int a3, int a4);
int initgus();
void devicespecificuninit();
void readsoundconfig();
char *FindConfigVar(const char *szConfigText, const char *szVarName);
void loadfile(const char *szFile, void **pBuf, unsigned int *uiSize, int iIsSound);
int ReadJoys(int *a1);
int check_joystickpresence();
int initsounds();
int stopallsamples();
int pannedsample(int result, int a2, int a3);
int speechonly(int result, int a2, int a3, int a4);
int speechsample(int result, int a2, int a3, int a4);
int analysespeechsamples();
void dospeechsample(int iSampleIdx, int iVolume);
int loadfrontendsample(int result);
int frontendsample(int a1);
void *remove_frontendspeech();
int sfxplaying(int a1);
int cheatsampleok(int a1);
void sfxsample(int iSample, int iVol);
void sample2(int iCarIndex, int iSampleIndex, int iVolume, int iPitch, int iPan, int iByteOffset);
int sfxpend(int a1, int a2, int a3);
int enginesounds2(int result, int a2);
int enginesounds(int result);
void loopsample(int iCarIdx, int iSampleIdx, int iVolume, int iPitch, int iPan);
void enginesound(int a1, float a2, float a3, float a4, int a5);
int startmusic(int result);
int stopmusic(int a1, int a2);
void load_language_map();
void initmusic();
void fade_palette(int iPaletteBrightness);
void set_palette(int iBrightness);
int check_joystick_usage();
void convertname(char *szFilename);
void decode(uint8 *pData, int iLength, int iStep, int iOffset);
void loadasample(int iIndex);
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

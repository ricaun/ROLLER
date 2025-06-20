#ifndef _ROLLER_ROLLER_H
#define _ROLLER_ROLLER_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
#include "sound.h"
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_gamepad.h>
//-------------------------------------------------------------------------------------------------

extern SDL_Gamepad *g_pController1;
extern SDL_Gamepad *g_pController2;

//-------------------------------------------------------------------------------------------------

// functions added by ROLLER
int InitSDL();
void ShutdownSDL();
void UpdateSDL();

int DIGISampleStart(tSampleData *data);
boolean DIGISampleDone(int index);
int DIGISampleAvailable(int index);
void DIGISampleClear(int index);

void PlayAudioSampleWait(int iIndex);
void PlayAudioDataWait(Uint8 *buffer, Uint32 length);
FILE *ROLLERfopen(const char *szFile, const char *szMode); //tries to open file with both all caps and all lower case
uint32 ROLLERAddTimer(Uint32 uiFrequencyHz, SDL_TimerCallback callback, void *userdata);
uint32 SDLTickTimerCallback(void *userdata, SDL_TimerID timerID, Uint32 interval);
uint32 SDLS7TimerCallback(void *userdata, SDL_TimerID timerID, Uint32 interval);
int IsCDROMDevice(const char *szPath);
int GetAxisValue(SDL_Gamepad *pController, SDL_GamepadAxis axis);

//-------------------------------------------------------------------------------------------------
#endif
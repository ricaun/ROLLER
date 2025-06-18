#include "sound.h"
#include "SDL3/SDL_events.h"
#include "frontend.h"
#include "moving.h"
#include "cdx.h"
#include "func2.h"
#include "3d.h"
#include "loadtrak.h"
#include "roller.h"
#include <memory.h>
#include <ctype.h>
#include <SDL3/SDL.h>
#include <fcntl.h>
#ifdef IS_WINDOWS
#include <io.h>
#define open _open
#define close _close
#else
#include <inttypes.h>
#include <unistd.h>
#define O_BINARY 0 //linux does not differentiate between text and binary
#endif

//-------------------------------------------------------------------------------------------------

int samplespending = 0;     //000A4690
int writesample = 0;        //000A4694
int readsample = 0;         //000A4698
int lastsample = 0;         //000A469C
int musicon = -1;           //000A46A0
int soundon = -1;           //000A46A4
int allengines = -1;        //000A46A8
int cheat_samples = 0;      //000A46AC
int palette_brightness = 32;//000A46B0
void *pal_selector = (void *)-1; //000A46B4
char SourcePath[64] = { 0 }; //000A46C4
char DestinationPath[64] = { 0 }; //000A4704
char languagename[32] = { 0 }; //000A4744
int writeptr = 0;           //000A476C
int readptr = 0;            //000A4770
int SoundCard = 0;          //000A4774
int SoundPort = 0;          //000A4778
int SoundIRQ = 0;           //000A477C
int SoundDMA = 0;           //000A4780
int EngineVolume = 32;      //000A4784
int SFXVolume = 56;         //000A4788
int SpeechVolume = 127;     //000A478C
int MusicVolume = 108;      //000A4790
int MusicCard = 0;          //000A4794
int MusicCD = 0;            //000A4798
int MusicPort = 0;          //000A479C
int SongPtr = 0;            //000A47A0
int SongHandle = 0;         //000A47A4
int CDSong[20] = { 10, 10, 10, 2, 3, 4, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0 }; //000A47A8
int GMSong[21] = { 0, 1, 2, 3, 4, 5, 6, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0, 0 }; //000A47F8
tSampleData SampleData = { NULL, 0u, 0, 0, 2, 32767, 0, { 0, 0, 0, 18176, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1701995379 } }; //000A484C
tSampleData SampleFixed = { NULL, 0u, 0, 0, 2, 32767, 0, { 0, 0, 0, 256, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } }; //000A48C4
tSampleData SamplePanned = { NULL, 0u, 0, 0, 2, 32767, 0, { 0, 0, 0, 768, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } }; //000A493C
int Joy1used = 0;           //000A4A0C
int Joy2used = 0;           //000A4A0C
int x1ok = 0;               //000A4A30
int y1ok = 0;               //000A4A34
int x2ok = 0;               //000A4A38
int y2ok = 0;               //000A4A3C
int bitaccept = 0;          //000A4A40
int holdmusic = 0;          //000A4A4C
uint8 unmangleinbuf[1024];  //00149EF0
uint32 SampleLen[120];      //00160560
uint8 *SamplePtr[120];      //00160750
tSampleHandleCar SampleHandleCar[120]; //00160930
char Sample[120][15];       //00162730
char lang[16][32];          //00162E38
int TrackMap[32];           //00163038
char TextExt[64];           //001630CA
char SampleExt[64];         //0016310A
int HandleCar[32];          //00163B8C
int HandleSample[32];       //00163C0C
int car_to_player[8][2];    //0016748C
int copy_multiple[8192];    //0016764C
int unmangleinpoff;         //0016F64C
uint8 *unmangledst;         //0016F650
int unmangleoverflow;       //0016F654
FILE *unmanglefile;         //0016F658
int unmanglebufpos;         //0016F65C
int s7;                     //0016F660
int MIDIHandle;             //0016F68C
tColor *pal_addr;           //0016F86C
int DIGIHandle;             //0016F690
int frames;                 //0016F694
char Song[20][15];          //0016F708
uint32 tickhandle;          //0016F834
DPMI_RMI RMI;               //0016F838
int nummusictracks;         //0016F8A8
int winchampsong;           //0016F8AC
int winsong;                //0016F8B0
int leaderboardsong;        //0016F8BC
int optionssong;            //0016F8C0
int titlesong;              //0016F8C4
int delaywrite;             //0016F8C8
int delayread;              //0016F8CC
int numsamples;             //0016F8D0
int cheatsample;            //0016F8D4
int languages;              //0016F8D8

//-------------------------------------------------------------------------------------------------
/***
* ADDED BY ROLLER
***/
//-------------------------------------------------------------------------------------------------

uint32 SDLTickTimerCallback(void *userdata, SDL_TimerID timerID, Uint32 interval)
{
  tickhandler(0, 0, 0, 0);
  ++ticks;
  return interval;
}

uint32 SDLS7TimerCallback(void *userdata, SDL_TimerID timerID, Uint32 interval)
{
  ++s7;
  return interval;
}

//-------------------------------------------------------------------------------------------------
/***
* END ROLLER CODE
***/
//-------------------------------------------------------------------------------------------------

void realmode(uint8 byRealModeInterrupt)
{
  /*union REGS regs; // [esp+0h] [ebp-34h] BYREF
  struct SREGS sregs; // [esp+1Ch] [ebp-18h] BYREF

  // 49 is DPMI interrupt
  // 768 Simulate Real Mode Interrupt
  // bx is being set to the real mode interrupt to simulate
  // all calls to this function set it to 0x10
  //   to simulate a BIOS video interrupt in real mode
  // __DS__ represents the current value of the DS (Data Segment)
  //   register in your program's segment context
  // By setting sregs.es = __DS__; and regs.x.edi = (unsigned int)&RMI;,
  //   we are telling the DPMI host that the RMI structure is located
  //   at offset &RMI in the segment __DS__
  memset(&sregs, 0, sizeof(sregs));
  regs.w.bx = byRealModeInterrupt;
  regs.w.ax = 768;
  regs.w.cx = 0;
  sregs.es = __DS__;
  regs.x.edi = (unsigned int)&RMI;
  int386x(49, &regs, &regs, &sregs);*/
}

//-------------------------------------------------------------------------------------------------

bool loadDOS(const char *szFilename, void **out_buffer)
{
  FILE *file = ROLLERfopen(szFilename, "rb");
  if (!file) {
    *out_buffer = NULL;
    return false;
  }

  // Get file size
  fseek(file, 0, SEEK_END);
  long iFileSize = ftell(file);
  rewind(file);

  if (iFileSize <= 0) {
    fclose(file);
    *out_buffer = NULL;
    return false;
  }

  // Allocate memory
  void *pBuffer = malloc(iFileSize);
  if (!pBuffer) {
    fclose(file);
    *out_buffer = NULL;
    return false;
  }

  // Read file into buffer
  int iReadBytes = (int)fread(pBuffer, 1, iFileSize, file);
  fclose(file);

  if (iReadBytes != iFileSize) {
    free(pBuffer);
    *out_buffer = NULL;
    return false;
  }

  *out_buffer = pBuffer;
  return true;
  /*
  union REGS regs;
  struct SREGS sregs;

  int handle = open_(szFilename, 0x200); // read-only
  if (handle == -1) {
    *out_segment = (void *)-1;
    return false;
  }

  long file_size = filelength_(handle);
  if (file_size <= 0) {
    close_(handle);
    *out_segment = (void *)-1;
    return false;
  }

  // Allocate a DOS memory block using int 31h AX=0100h
  unsigned short paragraphs = (file_size + 15) / 16; // round up to paragraphs
  memset(&sregs, 0, sizeof(sregs));
  regs.w.ax = 0x0100;
  regs.w.bx = paragraphs;
  int386x(0x31, &regs, &regs, &sregs);

  if (regs.x.cflag || regs.w.ax == 0) {
    close_(handle);
    *out_segment = (void *)-1;
    return false;
  }

  unsigned short seg = regs.w.ax;
  *out_segment = (void *)(uintptr_t)seg;

  // Convert segment:offset to linear address and read into it
  void *dst = (void *)((uintptr_t)seg << 4);
  read_(handle, dst, (unsigned int)file_size);
  close_(handle);

  return true;*/
}

//-------------------------------------------------------------------------------------------------

int claimDOS(int a1, void *a2)
{
  return 0; /*
  int v3; // ecx
  unsigned __int16 v5; // dx
  int v6; // [esp+0h] [ebp-34h] BYREF
  __int16 v7; // [esp+4h] [ebp-30h]
  unsigned __int16 v8; // [esp+Ch] [ebp-28h]
  int v9; // [esp+18h] [ebp-1Ch]
  _BYTE v10[24]; // [esp+1Ch] [ebp-18h] BYREF

  v3 = ((a1 - (__CFSHL__(a1 >> 31, 4) + 16 * (a1 >> 31))) >> 4) + 1;
  memset(v10, 0, 12);
  v7 = v3;
  LOWORD(v6) = 256;
  int386x(49, (int)&v6, (int)&v6, (int)v10);
  if (v9) {
    *a2 = -1;
    return 0;
  } else {
    v5 = v6;
    *a2 = v8;
    return 16 * v5;
  }*/
}

//-------------------------------------------------------------------------------------------------

int releaseDOS(int16 a1, int a2, int a3, int a4)
{
  return 0; /*
  _WORD v6[14]; // [esp+0h] [ebp-34h] BYREF
  _BYTE v7[16]; // [esp+1Ch] [ebp-18h] BYREF
  int v8; // [esp+2Ch] [ebp-8h]

  v8 = a4;
  memset(v7, 0, 12);
  v6[6] = a1;
  v6[0] = 257;
  return int386x(49, (int)v6, (int)v6, (int)v7);*/
}

//-------------------------------------------------------------------------------------------------

bool setpal(const char *szFilename)
{
  void *pFileData = NULL;

  // Free old palette memory, if it was set
  if ((int64)pal_selector >= 0 && pal_addr) {
    free(pal_addr);
    pal_addr = NULL;
    pal_selector = (void *)-1;
  }
  /*if ( (int)pal_selector >= 0 )
  {
    v4 = (unsigned __int16)pal_selector;
    memset(&sregs, 0, sizeof(sregs));
    regs.w.dx = v4;
    regs.w.ax = 257;
    int386x(0x31, &regs, &regs, &sregs);
    pal_selector = (void *)-1;
  }*/

  // Load palette file into memory
  if (!loadDOS(szFilename, &pFileData)) {
    fprintf(stderr, "Failed to load palette file: %s\n", szFilename);
    return false;
  }

  // Assign palette globals
  pal_addr = pFileData;
  pal_selector = pFileData; // For compatibility

  uint8 *pRaw = (uint8 *)pFileData;

  // Copy RGB triplets into the structured palette array
  for (int i = 0; i < 256; ++i) {
    palette[i].byR = pRaw[i * 3 + 0];
    palette[i].byG = pRaw[i * 3 + 1];
    palette[i].byB = pRaw[i * 3 + 2];
  }

  // If cheat mode flag is set, apply grayscale filter
  if (cheat_mode & CHEAT_MODE_GRAYSCALE) {
    for (int i = 0; i < 256; ++i) {
      uint8 byAvg = (palette[i].byR + palette[i].byB + palette[i].byG) / 3;
      palette[i].byR = byAvg;
      palette[i].byB = byAvg;
      palette[i].byG = byAvg;
    }
  }

  palette_brightness = 0;
  return true;
}

//-------------------------------------------------------------------------------------------------

void blankpal()
{
  if (!pal_addr)
    return;

  memset(pal_addr, 0, sizeof(tColor) * 256);

  /*
  unsigned int uiLinearAddress; // ecx
  unsigned __int16 unDx; // si
  union REGS regs; // [esp+0h] [ebp-64h] BYREF
  REGS regs2; // [esp+1Ch] [ebp-48h] BYREF
  struct SREGS sregs; // [esp+38h] [ebp-2Ch] BYREF
  SREGS sregs2; // [esp+44h] [ebp-20h] BYREF

  memset(&sregs, 0, sizeof(sregs));
  regs.w.ax = 256;
  regs.w.bx = 48;

  // allocate 48 LDT selectors
  // * If successful, AX contains the first selector allocated.
  // * If failed, the carry flag is set and AX contains an error code.
  int386x(49, &regs, &regs, &sregs);

  // Multiplying by 16 (* 16) converts a segment
  // selector value to a linear address in real
  // mode (segment:offset addressing), because in
  // real mode, the physical address is
  // segment * 16 + offset.
  uiLinearAddress = 16 * regs.w.ax;
  unDx = regs.w.dx;
  memset((void *)uiLinearAddress, 0, 0x300u);
  RMI.ecx = 256;
  RMI.eax = 4114;
  RMI.ebx = 0;
  RMI.edx = 0;

  // Shifting the address right by 4 (>> 4) converts
  // the linear address back to a segment value
  // (since segment = address / 16).
  RMI.es = uiLinearAddress >> 4;
  realmode(0x10u);
  memset(&sregs2, 0, sizeof(sregs2));
  regs2.w.dx = unDx;
  regs2.w.ax = 257;
  int386x(49, &regs2, &regs2, &sregs2);
  */
  palette_brightness = 0;
}

//-------------------------------------------------------------------------------------------------

void resetpal()
{
  /*
  RMI.eax = 4114;
  RMI.ebx = 0;
  RMI.ecx = 256;
  RMI.es = (unsigned int)pal_addr >> 4;
  RMI.edx = 0;
  realmode(0x10u);
  */

  // Clean up heap-allocated palette memory
  if (pal_addr) {
    free(pal_addr);
    pal_addr = NULL;
  }
}

//-------------------------------------------------------------------------------------------------

void Initialise_SOS()
{
  //sosTIMERInitSystem(0xFF00, 0);                // 0xFF00 maybe a special case for a slow rate timer?
  if (MusicCD)
    SetAudioVolume(MusicVolume);
  if (MusicCard) {
    if (MusicCard == 40970)
      initgus();
    printf("Initialising MIDI device %4X...", MusicCard);
    fflush(stdout);
    memset(TrackMap, 255, 0x20 * sizeof(unsigned int));
    //sosMIDIInitSystem(0, 0);
    //MIDIInitDriver_variable_1 = 0;
    //MIDIHardware = MusicPort;
    //MIDIInitDriver_variable_2 = 0;
    //if (sosMIDIInitDriver(
    //  MusicCard,
    //  0,
    //  (unsigned int)&MIDIHardware,
    //  __DS__,
    //  (int)&MIDIInitDriver,
    //  (unsigned __int16)__DS__,
    //  (unsigned int)&MIDIHandle,
    //  (unsigned __int16)__DS__)) {
    //  MusicCard = 0;
    //  sosMIDIUnInitSystem();
    //  printf("Failed\n");
    //} else {
    //  printf("OK\n");
    //  devicespecificinit();
    //  sosMIDISetMasterVolume(MusicVolume);
    //}
  }
  if (SoundCard) {
    printf("Initialising DIGI device %4X...", SoundCard);
    fflush(stdout);
    //sosDIGIInitSystem(0, 0);
    printf("OK\n");
  }
  select8bitdriver();
  ticks = 0;
  frames = 0;

  // start 36Hz timer that calls tickhandler
  claim_ticktimer(36u);
}

//-------------------------------------------------------------------------------------------------

int updatejoy()
{
  return 0; /*
  int result; // eax
  int v1; // eax
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax

  result = memset(&joyvalue, 0, 32);
  if (Joy1used || Joy2used)
    result = ReadJoys(&rud_Joy_pos);
  if (Joy1used) {
    keys_variable_10 = rud_Joy_pos;
    keys_variable_11 = rud_Joy_pos_variable_1;
    v1 = ((2 * rud_Joy_pos_variable_2 - JAXmax - JAXmin) << 10) / (JAXmax - JAXmin);
    if (v1 >= 0) {
      v3 = v1 - 100;
      if (v3 < 0)
        v3 = 0;
      joyvalue_variable_1 = v3;
    } else {
      v2 = v1 + 100;
      if (v2 > 0)
        v2 = 0;
      joyvalue = -v2;
    }
    v4 = ((2 * rud_Joy_pos_variable_3 - JAYmax - JAYmin) << 10) / (JAYmax - JAYmin);
    if (v4 >= 0) {
      result = v4 - 100;
      if (result < 0)
        result = 0;
      joyvalue_variable_3 = result;
    } else {
      result = v4 + 100;
      if (result > 0)
        result = 0;
      joyvalue_variable_2 = -result;
    }
  }
  if (Joy2used) {
    keys_variable_12 = rud_Joy_pos_variable_4;
    keys_variable_13 = rud_Joy_pos_variable_5;
    v5 = ((2 * rud_Joy_pos_variable_6 - JBXmax - JBXmin) << 10) / (JBXmax - JBXmin);
    if (v5 >= 0) {
      v7 = v5 - 100;
      if (v7 < 0)
        v7 = 0;
      joyvalue_variable_5 = v7;
    } else {
      v6 = v5 + 100;
      if (v6 > 0)
        v6 = 0;
      joyvalue_variable_4 = -v6;
    }
    v8 = ((2 * rud_Joy_pos_variable_7 - JBYmax - JBYmin) << 10) / (JBYmax - JBYmin);
    if (v8 >= 0) {
      result = v8 - 100;
      if (result < 0)
        result = 0;
      joyvalue_variable_7 = result;
    } else {
      v9 = v8 + 100;
      if (v9 > 0)
        v9 = 0;
      result = -v9;
      joyvalue_variable_6 = result;
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int readuserdata(int result)
{
  return 0; /*
  int v1; // ecx
  int v2; // esi
  int v3; // ebx
  int v4; // esi
  unsigned int v5; // eax
  unsigned int v6; // eax
  unsigned __int8 v7; // bl
  int v8; // ebp
  int v9; // edx
  int v10; // eax
  int v11; // ebx
  int v12; // edi
  int v13; // edx
  int v14; // ebx
  int v15; // edx
  int v16; // eax
  int v17; // edx
  int v18; // edx
  unsigned int v19; // eax
  unsigned int v20; // ebx
  int v21; // eax
  int v22; // eax
  int v23; // ebx
  int v24; // eax
  unsigned int v25; // edx
  unsigned int v26; // edx
  int v27; // edx
  int v28; // eax
  char v29; // [esp+0h] [ebp-1Ch]

  v1 = result;
  if (countdown >= 140) {
    user_inp_variable_1 = 0;
    user_inp = 0;
    return result;
  }
  v2 = 3 * result;
  result *= 4;
  v3 = *(int *)((char *)p_eng + result);
  v4 = 2 * v2;
  if (!v3) {
    user_inp = 0;
    user_inp_variable_1 = 0;
    return result;
  }
  *(int *)((char *)rud_steer + result) = *(_DWORD *)(v3 + 92) << 8;
  v29 = 0;
  *(int *)((char *)rud_swheel + result) = *(__int16 *)((char *)&last_inp + result);
  v5 = (unsigned __int8)userkey_variable_2[v4];
  if (v5 > 0x83) {
    if ((unsigned int)musicbuffer_variable_1[v5] <= 0xC8)
      goto LABEL_9;
  } else if (!keys[v5]) {
    goto LABEL_9;
  }
  v29 = 1;
LABEL_9:
  v6 = (unsigned __int8)userkey_variable_3[v4];
  if (v6 > 0x83) {
    if ((unsigned int)musicbuffer_variable_1[v6] <= 0xC8)
      goto LABEL_14;
  } else if (!keys[v6]) {
    goto LABEL_14;
  }
  v29 -= 2;
LABEL_14:
  v7 = userkey[v4];
  if (v7 > 0x83u) {
    v19 = (unsigned int)(80 * musicbuffer_variable_1[v7]) >> 8;
    if (v19 > 0x102)
      v19 = 258;
    v20 = (unsigned int)(80 * musicbuffer_variable_1[(unsigned __int8)userkey_variable_1[v4]]) >> 8;
    v21 = (int)(p_joyk1[v1] * ((int)(v19 * v19 * v19) >> 8) + p_joyk2[v1] * v19) >> 16;
    if (v20 > 0x102)
      v20 = 258;
    rud_swheel[v1] = v21 - ((int)(p_joyk1[v1] * ((int)(v20 * v20 * v20) >> 8) + p_joyk2[v1] * v20) >> 16);
    v22 = -rud_steer[v1];
    if (v22 > rud_swheel[v1])
      rud_swheel[v1] = v22;
    v10 = v1;
    v12 = rud_steer[v1];
    if (rud_swheel[v1] > v12)
      goto LABEL_43;
  } else if (keys[v7]) {
    v8 = rud_turn[v1];
    if (v8 >= 0)
      rud_turn[v1] = 32 * *(_DWORD *)(p_eng[v1] + 76) + v8;
    else
      rud_turn[v1] = (int)(abs32(rud_swheel[v1])
                         * ((*(_DWORD *)(p_eng[v1] + 72) << 8) - 32 * *(_DWORD *)(p_eng[v1] + 76)))
      / rud_steer[v1];
    v9 = *(_DWORD *)(p_eng[v1] + 72) << 8;
    if (v9 < rud_turn[v1])
      rud_turn[v1] = v9;
    v10 = v1;
    v11 = rud_turn[v1] + rud_swheel[v1];
    v12 = rud_steer[v1];
    rud_swheel[v1] = v11;
    if (v11 > v12)
      LABEL_43:
    rud_swheel[v10] = v12;
  } else if (keys[(unsigned __int8)userkey_variable_1[v4]]) {
    if (rud_turn[v1] >= 0)
      rud_turn[v1] += 32 * *(_DWORD *)(p_eng[v1] + 76);
    else
      rud_turn[v1] = (int)(abs32(rud_swheel[v1])
                         * ((*(_DWORD *)(p_eng[v1] + 72) << 8) - 32 * *(_DWORD *)(p_eng[v1] + 76)))
      / rud_steer[v1];
    v13 = *(_DWORD *)(p_eng[v1] + 72) << 8;
    if (v13 < rud_turn[v1])
      rud_turn[v1] = v13;
    v14 = rud_swheel[v1] - rud_turn[v1];
    v15 = -rud_steer[v1];
    rud_swheel[v1] = v14;
    if (v15 > v14)
      rud_swheel[v1] = v15;
  } else {
    v16 = rud_swheel[v1];
    rud_turn[v1] = -1;
    if (v16 <= 0) {
      v18 = (*(_DWORD *)(p_eng[v1] + 84) << 8) + rud_swheel[v1];
      rud_swheel[v1] = v18;
      if (v18 > 0)
        rud_swheel[v1] = 0;
    } else {
      v17 = rud_swheel[v1] - (*(_DWORD *)(p_eng[v1] + 84) << 8);
      rud_swheel[v1] = v17;
      if (v17 < 0)
        rud_swheel[v1] = 0;
    }
  }
  user_inp = rud_swheel[v1];
  v23 = v29 > 0;
  if (v29 < 0)
    LOBYTE(v23) = v23 | 2;
  v24 = v23;
  if (v1) {
    if ((unsigned __int8)userkey_variable_13 > 0x83u) {
      if ((unsigned int)musicbuffer_variable_1[(unsigned __int8)userkey_variable_13] <= 0xC8)
        goto LABEL_57;
    } else if (!keys[(unsigned __int8)userkey_variable_13]) {
      goto LABEL_57;
    }
  } else if ((unsigned __int8)userkey_variable_12 > 0x83u) {
    if ((unsigned int)musicbuffer_variable_1[(unsigned __int8)userkey_variable_12] <= 0xC8)
      goto LABEL_57;
  } else if (!keys[(unsigned __int8)userkey_variable_12]) {
    goto LABEL_57;
  }
  LOBYTE(v24) = v23 | 0x20;
  v23 = v24;
LABEL_57:
  v25 = (unsigned __int8)userkey_variable_4[v4];
  result = 0;
  if (v25 > 0x83) {
    if ((unsigned int)musicbuffer_variable_1[v25] <= 0xC8)
      goto LABEL_62;
  } else if (!keys[v25]) {
    goto LABEL_62;
  }
  result = 1;
LABEL_62:
  v26 = (unsigned __int8)userkey_variable_5[v4];
  if (v26 > 0x83) {
    if ((unsigned int)musicbuffer_variable_1[v26] <= 0xC8)
      goto LABEL_67;
  } else if (!keys[v26]) {
    goto LABEL_67;
  }
  result = -1;
LABEL_67:
  if (!result)
    rud_gr[v1] = 0;
  if (rud_gr[v1])
    result = 0;
  if (result > 0) {
    LOBYTE(v23) = v23 | 4;
    rud_gr[v1] = -1;
  }
  if (result < 0) {
    LOBYTE(v23) = v23 | 8;
    rud_gr[v1] = -1;
  }
  if (lastsample >= 0)
    goto LABEL_107;
  result = 0;
  if (keys_variable_6) {
    result = 64;
  } else if (keys_variable_7) {
    result = 128;
  } else if (keys_variable_8) {
    result = 256;
  } else if (keys_variable_9) {
    result = 512;
  }
  if (!result)
    rud_strat[v1] = 0;
  if (rud_strat[v1])
    result = 0;
  if (!result)
    goto LABEL_107;
  if (network_on) {
    message_node = network_mes_mode;
    if (network_mes_mode >= 0) {
      if (human_control[message_node])
        message_node = car_to_player[message_node];
      else
        message_node = -2;
    }
    if (message_node > -2 && !finished_car[(__int16)player1_car]) {
      if ((result & 0x40) != 0) {
        v27 = message_node;
        v28 = 0;
      } else if ((result & 0x80u) == 0) {
        if ((result & 0x100) != 0) {
          v27 = message_node;
          v28 = 2;
        } else {
          if ((result & 0x200) == 0) {
          LABEL_105:
            result = 0;
            goto LABEL_106;
          }
          v27 = message_node;
          v28 = 3;
        }
      } else {
        v27 = message_node;
        v28 = 1;
      }
      send_mes(v28, v27, v23);
      goto LABEL_105;
    }
  }
LABEL_106:
  LOWORD(v23) = result | v23;
  rud_strat[v1] = -1;
LABEL_107:
  if (I_Want_Out && !already_quit) {
    I_Want_Out = 0;
    already_quit = -1;
    result = wConsoleNode;
    if (wConsoleNode == master)
      BYTE1(v23) |= 8u;
    else
      BYTE1(v23) |= 4u;
  }
  user_inp_variable_1 = v23;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int tickhandler(int a1, int a2, int a3, int a4)
{
  return 0; /*
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  unsigned int v14; // eax
  int v15; // eax
  unsigned int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // edx
  int v20; // eax
  int v21; // edi
  int v22; // esi
  int v23; // eax
  int v24; // edi
  int *v25; // ebp
  int *v26; // esi
  int *v27; // esi
  int v28; // edi
  int *v29; // ebp
  int *v30; // esi
  int *v31; // esi
  int *v32; // esi
  int *v33; // esi
  int v34; // edi
  int *v35; // ebp
  int *v36; // esi
  _BYTE retaddr[8]; // [esp+18h] [ebp+0h]

  if (network_on && syncleft) {
    v4 = do_sync_stuff(a1, a2, a3, a4);
  } else {
    a4 = network_on;
    if (network_on)
      net_loading = 0;
    else
      broadcast_mode = 0;
    ++frames;
    if (replaytype == 2) {
      if (forwarding) {
        if (slowing) {
          replayspeed = 4 * replayspeed / 5;
          if (replayspeed < 256) {
            ROldStatus();
            slowing = 0;
          }
        } else {
          replayspeed = (17 * replayspeed - (__CFSHL__((17 * replayspeed) >> 31, 4) + 16 * ((17 * replayspeed) >> 31))) >> 4;
          if (replayspeed > 0x2000)
            replayspeed = 0x2000;
        }
      }
      if (rewinding) {
        if (slowing) {
          replayspeed = 4 * replayspeed / 5;
          if (replayspeed > -256) {
            a4 = 0;
            ROldStatus();
            slowing = 0;
          }
        } else {
          replayspeed = (17 * replayspeed - (__CFSHL__((17 * replayspeed) >> 31, 4) + 16 * ((17 * replayspeed) >> 31))) >> 4;
          if (replayspeed < -8192)
            replayspeed = -8192;
        }
      }
      a2 = (replayspeed + fraction) >> 31 << 8;
      v5 = (replayspeed + fraction - (__CFSHL__((replayspeed + fraction) >> 31, 8) + a2)) >> 8;
      ticks += v5;
      a3 = replayspeed + fraction - (v5 << 8);
      fraction = a3;
      if (ticks < 0)
        ticks = 0;
      if (replayframes - 1 < ticks)
        ticks = replayframes - 1;
      if (!ticks && fraction < 0)
        fraction = ticks;
      v4 = replayframes - 1;
      if (replayframes - 1 == ticks && fraction >= 0)
        fraction = 0;
    } else {
      v4 = ticks++;
      if (!paused && !frontend_on)
        v4 = updatejoy();
    }
    if (tick_on && network_on && (replaytype == 2 || game_type > 2)) {
      v6 = CheckNewNodes(v4);
      v7 = SendAMessage(v6);
      v4 = BroadcastNews(v7);
    }
    if (tick_on && replaytype != 2 && game_type < 3) {
      if (frontend_on) {
        if (network_on) {
          v8 = CheckNewNodes(v4);
          v9 = SendAMessage(v8);
          v4 = BroadcastNews(v9);
        }
      } else {
        if (network_on && winner_mode) {
          v10 = CheckNewNodes(v4);
          v11 = SendAMessage(v10);
          v4 = BroadcastNews(v11);
        }
        if (!network_on || winner_mode) {
          if (start_race) {
            v4 = paused;
            if (!paused) {
              readuserdata(0);
              last_inp = user_inp;
              a2 = 4 * (__int16)player1_car + (writeptr << 6);
              *(int *)((char *)copy_multiple + a2) = user_inp;
              if (player_type == 2) {
                readuserdata(1);
                last_inp_variable_1 = user_inp;
                a2 = (writeptr << 6) + 4 * player2_car;
                *(int *)((char *)copy_multiple + a2) = user_inp;
              }
              v4 = ((_WORD)writeptr + 1) & 0x1FF;
              writeptr = v4;
              if (soundon && !paused) {
                if (delayread < delaywrite) {
                  delayreadx = delayread & 0x1F;
                  if (player_type == 2) {
                    v32 = &enginedelay[224 * ViewType[0] + 7 * delayreadx];
                    if (v32[1] >= 0) {
                      a4 = *v32;
                      loopsample(v32[6]);
                    }
                    if (v32[3] >= 0) {
                      a4 = v32[2];
                      loopsample(v32[6]);
                    }
                    if (v32[5] >= 0) {
                      a4 = v32[4];
                      loopsample(v32[6]);
                    }
                    a3 = delayreadx;
                    v33 = &enginedelay[224 * ViewType_variable_1 + 7 * delayreadx];
                    if (v33[1] >= 0) {
                      a3 = v33[1];
                      a4 = *v33;
                      loopsample(v33[6]);
                    }
                    a2 = v33[3];
                    if (a2 >= 0) {
                      a4 = v33[2];
                      a3 = v33[3];
                      a2 = 1;
                      loopsample(v33[6]);
                    }
                    if (v33[5] >= 0) {
                      a2 = 3;
                      a4 = v33[4];
                      a3 = v33[5];
                      loopsample(v33[6]);
                    }
                  } else if (allengines) {
                    a2 = numcars;
                    v28 = 0;
                    if (numcars > 0) {
                      v29 = enginedelay;
                      do {
                        v30 = &v29[7 * delayreadx];
                        if (v30[1] >= 0) {
                          a4 = *v30;
                          a3 = v30[1];
                          loopsample(v30[6]);
                        }
                        if (v30[3] >= 0) {
                          a4 = v30[2];
                          a3 = v30[3];
                          loopsample(v30[6]);
                        }
                        a2 = v30[5];
                        if (a2 >= 0) {
                          a4 = v30[4];
                          a3 = v30[5];
                          a2 = 3;
                          loopsample(v30[6]);
                        }
                        ++v28;
                        v29 += 224;
                      } while (v28 < numcars);
                    }
                  } else {
                    a2 = ViewType[0];
                    a3 = delayreadx;
                    v31 = &enginedelay[224 * ViewType[0] + 7 * delayreadx];
                    if (v31[1] >= 0) {
                      a4 = *v31;
                      a3 = v31[1];
                      a2 = 0;
                      loopsample(v31[6]);
                    }
                    if (v31[3] >= 0) {
                      a2 = 1;
                      a4 = v31[2];
                      a3 = v31[3];
                      loopsample(v31[6]);
                    }
                    if (v31[5] >= 0) {
                      a2 = 3;
                      a3 = v31[5];
                      a4 = v31[4];
                      loopsample(v31[6]);
                    }
                  }
                }
                v4 = delaywrite - delayread;
                if (delaywrite - delayread >= 6)
                  v4 = delayread++;
              }
            }
          }
        } else {
          ticks_received = 0;
          a4 = master;
          if (wConsoleNode == master) {
            a2 = 0;
            if (network_on > 0) {
              v12 = master ^ wConsoleNode;
              do {
                if (paused) {
                  a3 = frames;
                  *(int *)((char *)net_time + v12) = frames;
                }
                if (a2 != master
                  && *(int *)((char *)net_players + v12)
                  && network_limit + *(int *)((char *)net_time + v12) < frames
                  && !send_finished) {
                  network_error = 222;
                }
                v12 += 4;
                ++a2;
              } while (a2 < network_on);
            }
            if (network_error && network_error != 666)
              send_net_error();
            if (network_on - 1 == start_multiple) {
              v13 = numcars;
              qmemcpy(&copy_multiple[16 * writeptr], &copy_multiple[16 * (((_WORD)writeptr - 1) & 0x1FF)], 0x40u);
              a4 = 0;
              if (v13 > 0) {
                v14 = 0;
                a3 = 4 * numcars;
                do {
                  if ((copy_multiple[16 * writeptr + v14 / 4] & 0x4000000) != 0) {
                    LOWORD(a4) = HIWORD(copy_multiple[16 * writeptr + v14 / 4]);
                    BYTE1(a4) ^= 4u;
                    HIWORD(copy_multiple[16 * writeptr + v14 / 4]) = a4;
                  }
                  if ((copy_multiple[16 * writeptr + v14 / 4] & 0x8000000) != 0) {
                    LOWORD(a4) = HIWORD(copy_multiple[16 * writeptr + v14 / 4]);
                    BYTE1(a4) = BYTE1(a4) ^ 8 | 4;
                    HIWORD(copy_multiple[16 * writeptr + v14 / 4]) = a4;
                  }
                  v14 += 4;
                } while ((int)v14 < a3);
              }
              readuserdata(0);
              a2 = user_inp;
              copy_multiple[16 * writeptr + (__int16)player1_car] = user_inp;
              last_inp = a2;
              receive_all_singles();
            }
            if (countdown >= 0) {
              a2 = 0;
              active_nodes = 0;
              if (network_on > 0) {
                v15 = 0;
                do {
                  if (player_ready[v15])
                    ++active_nodes;
                  if (player_ready[v15] == 666 && net_players[v15]) {
                    a4 = writeptr << 6;
                    HIWORD(copy_multiple[16 * writeptr + player_to_car[v15]]) |= 0x400u;
                    a3 = 0;
                    net_players[v15] = 0;
                  }
                  ++v15;
                  ++a2;
                } while (a2 < network_on);
              }
            }
            v4 = active_nodes;
            if (active_nodes == network_on) {
              net_loading = 0;
              v4 = network_on - 1;
              if (network_on - 1 != start_multiple || !paused) {
                if (start_race) {
                  if (!paused) {
                    if (send_finished) {
                      a4 = numcars;
                      if (numcars > 0) {
                        a3 = 4 * numcars;
                        v16 = 0;
                        do {
                          LOWORD(a4) = HIWORD(copy_multiple[16 * writeptr + v16 / 4]);
                          BYTE1(a4) |= 0x10u;
                          a2 = writeptr << 6;
                          v16 += 4;
                          load_times_variable_1[32 * writeptr + v16 / 2] = a4;
                        } while ((int)v16 < a3);
                      }
                    }
                  }
                }
                send_multiple();
                v4 = network_on - 1;
                if (network_on - 1 == start_multiple) {
                  v17 = start_multiple ^ v4;
                  a3 = 4 * numcars;
                  while (1) {
                    a2 = writeptr << 6;
                    if (v17 >= a3)
                      break;
                    if ((*((_BYTE *)copy_multiple + a2 + v17 + 3) & 4) != 0) {
                      a4 = 0;
                      net_players[*(int *)((char *)car_to_player + v17)] = 0;
                      network_timeout = frames;
                    }
                    v17 += 4;
                  }
                  if ((*((_BYTE *)&copy_multiple[(__int16)player1_car] + a2 + 3) & 8) != 0) {
                    read_check = -1;
                    write_check = -1;
                    net_players[master] = 0;
                    while (!net_players[master])
                      ++master;
                    v18 = 0;
                    if (network_on > 0) {
                      v19 = 0;
                      do {
                        HIWORD(a3) = HIWORD(frames);
                        ++v19;
                        ++v18;
                        lastpan_variable_1[v19] = frames;
                      } while (v18 < network_on);
                    }
                    LOWORD(a3) = HIWORD(copy_multiple[16 * (writeptr & 0x1FF) + (__int16)player1_car]);
                    BYTE1(a3) ^= 4u;
                    a2 = (((_WORD)writeptr + 1) & 0x1FF) << 6;
                    *(_WORD *)((char *)&copy_multiple[(__int16)player1_car] + a2 + 2) = a3;
                    network_timeout = frames;
                  }
                  writeptr = ((_WORD)writeptr + 1) & 0x1FF;
                  v4 = ticks_received++;
                }
              }
            }
          } else if (wConsoleNode > master && net_players[wConsoleNode]) {
            if (paused)
              network_timeout = frames;
            if (network_limit + network_timeout < frames && human_finishers < players)
              network_error = 123;
            readuserdata(0);
            send_single(user_inp);
            last_inp = user_inp;
            receive_multiple();
            v4 = (((_WORD)writeptr - 1) & 0x1FF) << 6;
            a2 = player_to_car[master];
            if ((*((_BYTE *)&copy_multiple[a2] + v4 + 3) & 8) != 0) {
              read_check = -1;
              write_check = -1;
              a3 = 0x4000;
              memset(player_checks, -1, sizeof(player_checks));
              a2 = 0;
              net_players[master] = 0;
              while (!net_players[master])
                ++master;
              active_nodes = network_on;
              start_multiple = network_on - 1;
              v20 = 0;
              if (network_on > 0) {
                a2 = 0;
                do {
                  a3 = frames;
                  a2 += 4;
                  ++v20;
                  *(int *)((char *)lastpan_variable_1 + a2) = frames;
                } while (v20 < network_on);
              }
              v4 = frames;
              network_timeout = frames;
            }
            a4 = numcars;
            v21 = 0;
            if (numcars > 0) {
              v22 = 0;
              do {
                if ((copy_multiple[16 * (((_WORD)writeptr - 1) & 0x1FF) + v22] & 0x10000000) != 0)
                  network_error = 0;
                v4 = (((_WORD)writeptr - 1) & 0x1FF) << 6;
                if ((*((_BYTE *)&copy_multiple[v22] + v4 + 3) & 4) != 0) {
                  net_players[car_to_player[v22]] = 0;
                  network_timeout = frames;
                  a2 = -1;
                  memset(player_checks, -1, sizeof(player_checks));
                  a3 = 0;
                  read_check = 0;
                  v4 = 0;
                  write_check = 0;
                }
                ++v21;
                ++v22;
              } while (v21 < numcars);
            }
          } else {
            read_check = -1;
            write_check = -1;
            readuserdata(0);
            last_inp = user_inp;
            v23 = (__int16)player1_car;
            a3 = (writeptr << 6) + v23 * 4;
            *(int *)((char *)copy_multiple + a3) = user_inp;
            LOWORD(a3) = HIWORD(copy_multiple[16 * writeptr + v23]);
            BYTE1(a3) |= 4u;
            a2 = writeptr << 6;
            HIWORD(copy_multiple[16 * writeptr + v23]) = a3;
            v4 = ((_WORD)writeptr + 1) & 0x1FF;
            writeptr = v4;
          }
          if (soundon) {
            v24 = paused;
            if (!paused) {
              if (delayread < delaywrite) {
                delayreadx = delayread & 0x1F;
                if (allengines) {
                  if (numcars > 0) {
                    v25 = enginedelay;
                    do {
                      v26 = &v25[7 * delayreadx];
                      if (v26[1] >= 0) {
                        a3 = v26[1];
                        loopsample(v26[6]);
                      }
                      if (v26[3] >= 0) {
                        a3 = v26[3];
                        loopsample(v26[6]);
                      }
                      a2 = v26[5];
                      if (a2 >= 0) {
                        a3 = v26[5];
                        a2 = 3;
                        loopsample(v26[6]);
                      }
                      a4 = numcars;
                      ++v24;
                      v25 += 224;
                    } while (v24 < numcars);
                  }
                } else {
                  a2 = ViewType[0];
                  v27 = &enginedelay[224 * ViewType[0] + 7 * delayreadx];
                  a3 = v27[1];
                  if (a3 >= 0) {
                    a2 = 0;
                    a4 = *v27;
                    loopsample(v27[6]);
                  }
                  if (v27[3] >= 0) {
                    a2 = 1;
                    a3 = v27[3];
                    a4 = v27[2];
                    loopsample(v27[6]);
                  }
                  if (v27[5] >= 0) {
                    a3 = v27[5];
                    a4 = v27[4];
                    a2 = 3;
                    loopsample(v27[6]);
                  }
                }
              }
              v4 = ticks_received;
              delayread += ticks_received;
            }
          }
        }
      }
    }
    if (replaytype == 2 && replayspeed == 256) {
      if (delayread < delaywrite) {
        delayreadx = delayread & 0x1F;
        v34 = 0;
        if (numcars > 0) {
          v35 = enginedelay;
          do {
            v36 = &v35[7 * delayreadx];
            if (v36[1] >= 0) {
              a4 = *v36;
              a3 = v36[1];
              loopsample(v36[6]);
            }
            if (v36[3] >= 0) {
              a4 = v36[2];
              a3 = v36[3];
              loopsample(v36[6]);
            }
            if (v36[5] >= 0) {
              a4 = v36[4];
              a3 = v36[5];
              loopsample(v36[6]);
            }
            a2 = numcars;
            ++v34;
            v35 += 224;
          } while (v34 < numcars);
        }
      }
      v4 = delaywrite - delayread;
      if (delaywrite - delayread >= 6)
        v4 = delayread++;
    }
  }
  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(v4, a2, a3, a4);*/
}

//-------------------------------------------------------------------------------------------------

void claim_ticktimer(unsigned int uiRateHz)
{
  /***
  * ADDED BY ROLLER
  ***/
  tickhandle = SDL_AddTimer(uiRateHz, SDLTickTimerCallback, NULL); //may as well re-use tickhandle, it is also a uint32
  /***
  * END ROLLER CODE
  ***/

  /*
  if (sosTIMERRegisterEvent(
    uiRateHz,
    a2,
    (int)tickhandler,
    __CS__,
    (unsigned int)&tickhandle,
    (unsigned __int16)__DS__)) {
    printf("Unable to set timer\n");
    doexit(1, a2, tickhandler);
  }*/
}

//-------------------------------------------------------------------------------------------------

void release_ticktimer()
{
  /***
  * ADDED BY ROLLER
  ***/
  SDL_RemoveTimer(tickhandle); //may as well re-use tickhandle, it is also a uint32
  /***
  * END ROLLER CODE
  ***/

  //sosTIMERRemoveEvent(tickhandle);
}

//-------------------------------------------------------------------------------------------------

void Uninitialise_SOS()
{
  /***
  * ADDED BY ROLLER
  ***/
  SDL_RemoveTimer(tickhandle); //may as well re-use tickhandle, it is also a uint32
  /***
  * END ROLLER CODE
  ***/

  /*
  sosTIMERRemoveEvent(tickhandle);
  sosTIMERRemoveEvent(TimerEventHandle);
  sosTIMERUnInitSystem(0);
  if (SoundCard) {
    sosDIGIUnInitDriver(DIGIHandle, 1, 1);
    sosDIGIUnInitSystem();
  }
  if (MusicCard) {
    devicespecificuninit();
    sosMIDIUnInitDriver(MIDIHandle, 1);
    sosMIDIUnInitSystem();
  }*/
}

//-------------------------------------------------------------------------------------------------

void loadsamples()
{/*
  int v0; // edx
  int v1; // ecx
  int v2; // ebx
  int v3; // edx
  int v4; // eax
  int v5; // eax
  int v6; // edx

  v0 = winner_mode;
  if (winner_mode) {
    if (champ_mode) {
      loadasample(0);
      loadasample(1);
      loadasample(3);
      loadasample(9);
      loadasample(10);
      loadasample(11);
      loadasample(12);
      loadasample(6);
      v5 = total_wins[champorder[0]];
      if (v5 > 0)
        loadasample(v5 + 88);
      v6 = total_kills[champorder[0]];
      if (v6 > 0 && v6 < 17)
        loadasample(v6 + 96);
      if (v6 >= 17)
        loadasample(113);
      v4 = 118;
    } else {
      loadasample(0);
      loadasample(1);
      loadasample(3);
      loadasample(9);
      loadasample(10);
      loadasample(11);
      loadasample(12);
      loadasample(114);
      loadasample(115);
      loadasample(116);
      loadasample(117);
      v3 = result_kills[result_order[0]];
      if (v3 > 0 && v3 < 17)
        loadasample(v3 + 96);
      if (v3 < 17)
        goto LABEL_30;
      v4 = 113;
    }
    loadasample(v4);
    goto LABEL_30;
  }
  if (numsamples > 0) {
    v1 = -71;
    v2 = 0;
    do {
      if (!winner_mode) {
        if (v0 >= 71 && (v0 <= 78 || v0 >= 89)) {
          if ((unsigned __int8)Car_variable_22[308 * ViewType[0]] != v1 || SamplePtr[v2])
            goto LABEL_13;
        LABEL_12:
          loadasample(v0);
          goto LABEL_13;
        }
        if (!SamplePtr[v2])
          goto LABEL_12;
      }
    LABEL_13:
      ++v1;
      ++v0;
      ++v2;
    } while (v0 < numsamples);
  }
LABEL_30:
  samplespending = 0;
  writesample = 0;
  readsample = 0;
  lastsample = -10000;*/
}

//-------------------------------------------------------------------------------------------------

void loadfatalsample()
{
  if (!SamplePtr[88])
    loadasample(88);
  if (!SamplePtr[83])
    loadasample(83);
  if (!SamplePtr[87])
    loadasample(87);
  if (!SamplePtr[84])
    loadasample(84);
  if (!SamplePtr[85])
    loadasample(85);
  if (!SamplePtr[86])
    loadasample(86);
  samplespending = 0;
  writesample = 0;
  readsample = 0;
  lastsample = -10000;
}

//-------------------------------------------------------------------------------------------------

void freefatalsample()
{
  fre(SamplePtr[88]);
  fre(SamplePtr[83]);
  fre(SamplePtr[87]);
  fre(SamplePtr[84]);
  fre(SamplePtr[85]);
  fre(SamplePtr[86]);
}

//-------------------------------------------------------------------------------------------------

void *releasesamples()
{
  return 0; /*
  int *v0; // ebx
  int i; // edx
  _DWORD *result; // eax

  if (SoundCard) {
    v0 = SamplePtr;
    for (i = 0; i < 120; Hardware_variable_3[i] = 0) {
      result = fre(v0);
      ++i;
      ++v0;
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int play()
{
  return 0; /*
  int result; // eax

  if (musicon) {
    if (SongPtr) {
      InitSong_variable_1 = __DS__;
      InitSong = SongPtr;
      InitSong_variable_3 = 0;
      InitSong_variable_2 = 0;
      return sosMIDIStartSong(SongHandle);
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void stop()
{
  if (MusicCard) {
    if (SongPtr) {
      //sosMIDIStopSong(SongHandle, a2);
      //sosMIDIResetSong(SongHandle, a2, (unsigned int)&InitSong);
    }
  }
}

//-------------------------------------------------------------------------------------------------

int devicespecificinit(int a1, int a2, int a3, int a4)
{
  return 0; /*
  int result; // eax
  int inited; // eax
  int i; // esi
  _BYTE v7[12]; // [esp+0h] [ebp-14h] BYREF
  int v8; // [esp+Ch] [ebp-8h]

  v8 = a4;
  result = MusicCard - 40961;
  switch (MusicCard) {
    case 40961:
      printf(&aIngresettingSc[3]);
      fflush(&__iob_variable_1);
      sosMIDISendMIDIData(MIDIHandle, 11, &SCreset, __DS__);
      result = printf(&sound_c_variable_3);
      break;
    case 40962:
    case 40969:
      printf(&aTCloadingInstr[3]);
      fflush(&__iob_variable_1);
      loadfile(aMelodicBnk, &FMInstruments, v7, 0);
      if (FMInstruments) {
        printf(&sound_c_variable_3);
        sosMIDISetInsData(MIDIHandle, 1, FMInstruments, __DS__);
      } else {
        printf(aFailed);
        MusicCard = 0;
      }
      printf(aLoadingDrumsBa);
      fflush(&__iob_variable_1);
      loadfile(aDrumBnk, &FMDrums, v7, 0);
      if (FMDrums) {
        printf(&sound_c_variable_3);
        result = sosMIDISetInsData(MIDIHandle, 1, FMDrums, __DS__);
      } else {
        result = printf(aFailed);
        MusicCard = 0;
      }
      if (!MusicCard) {
        inited = sosMIDIUnInitDriver(MIDIHandle, 1);
        result = sosMIDIUnInitSystem(inited);
      }
      break;
    case 40964:
      printf(aResettingLapc1);
      sosMIDISendMIDIData(MIDIHandle, 11, &MT32reset, __DS__);
      fflush(&__iob_variable_1);
      loadfile(aMt32mapMtx, &MT32Data, v7, 0);
      if (MT32Data) {
        fflush(&__iob_variable_1);
        for (i = 0; i != 1104; i += 138) {
          sosMIDISendMIDIData(MIDIHandle, 138, i + MT32Data, __DS__);
          printf(sound_c_variable_13);
          fflush(&__iob_variable_1);
        }
        result = printf(&sound_c_variable_3);
      } else {
        result = printf(aFailed);
      }
      break;
    default:
      return result;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int initgus()
{
  return 0; /*
  printf(&aCedownloadingG[2]);
  fflush(&__iob_variable_1);
  system((int)&aCLoadpatsQIfat[1]);
  return printf(aDone);*/
}

//-------------------------------------------------------------------------------------------------

void *devicespecificuninit()
{
  return 0; /*
  _DWORD *result; // eax
  int *v1; // eax

  result = (_DWORD *)(MusicCard - 40961);
  switch (MusicCard) {
    case 40961:
      result = (_DWORD *)sosMIDISendMIDIData(MIDIHandle, 11, &SCreset, __DS__);
      break;
    case 40962:
    case 40969:
      fre(&FMInstruments);
      v1 = &FMDrums;
      goto LABEL_5;
    case 40964:
      sosMIDISendMIDIData(MIDIHandle, 11, &MT32reset, __DS__);
      v1 = &MT32Data;
    LABEL_5:
      result = fre(v1);
      break;
    default:
      return result;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void readsoundconfig(void)
{
  FILE *fp = ROLLERfopen("../config.ini", "rb");
  char *pBuffer = NULL;
  long iSize;

  if (!fp) return;

  // Determine file size
  fseek(fp, 0, SEEK_END);
  iSize = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  pBuffer = (char *)getbuffer(iSize + 1);
  if (!pBuffer) {
    fclose(fp);
    return;
  }

  fread(pBuffer, 1, iSize, fp);
  pBuffer[iSize] = '\0'; // Null-terminate for string parsing

  // Parse Language
  char *szVar = FindConfigVar(pBuffer, "Language");
  if (szVar) sscanf(szVar, "%s", languagename);

  // Match language index
  language = 0;
  for (int i = 0; i < languages; i++) {
    if (strcmp(languagename, lang[i]) == 0) {
      language = i;
      break;
    }
  }

  // SourcePath
  szVar = FindConfigVar(pBuffer, "SourcePath");
  if (szVar) sscanf(szVar, "%s", SourcePath);

  // DestinationPath
  szVar = FindConfigVar(pBuffer, "DestinationPath");
  if (szVar) sscanf(szVar, "%s", DestinationPath);

  // Sound settings
  szVar = FindConfigVar(pBuffer, "SoundCard");
  if (szVar) sscanf(szVar, "%hi", &SoundCard);

  szVar = FindConfigVar(pBuffer, "SoundPort");
  if (szVar) sscanf(szVar, "%hi", &SoundPort);

  szVar = FindConfigVar(pBuffer, "SoundIRQ");
  if (szVar) sscanf(szVar, "%hi", &SoundIRQ);

  szVar = FindConfigVar(pBuffer, "SoundDMA");
  if (szVar) sscanf(szVar, "%hi", &SoundDMA);

  // Music settings
  szVar = FindConfigVar(pBuffer, "MusicCard");
  if (szVar) sscanf(szVar, "%hi", &MusicCard);

  szVar = FindConfigVar(pBuffer, "MusicPort");
  if (szVar) sscanf(szVar, "%hi", &MusicPort);

  // Cleanup
  fre(pBuffer);
  fclose(fp);

  // Special MusicCard case
  if (MusicCard == 0xCD) {
    MusicCard = 0;
    MusicCD = -1;
  }

  // Set flags
  if (MusicCard == 0 && MusicCD == 0)
    musicon = 0;

  if (SoundCard == 0)
    soundon = 0;
}

//-------------------------------------------------------------------------------------------------

char *FindConfigVar(const char *szConfigText, const char *szVarName)
{
  char *szMatch = strstr(szConfigText, szVarName);
  if (!szMatch)
    return NULL;

  if (szMatch != szConfigText) {
    // check that the match is at the start of a line or preceded by whitespace.
    char cPrev = szMatch[-1];
    if (isalpha((uint8)cPrev) || isdigit((uint8)cPrev) || cPrev == '_')
      return NULL;
  }

  // move 'edx' to point past the matched variable name
  char *szEnd = szMatch;
  uint32 uiLen = (uint32)strlen(szVarName) + 1;
  szEnd += uiLen;

  // skip any trailing spaces
  while (isspace((uint8)(*szEnd + 1)))
    szEnd++;

  // make sure it's followed by '='
  if (szEnd[-1] != '=')
    return NULL;

  return szEnd;
}

//-------------------------------------------------------------------------------------------------

void loadfile(const char *szFile, void **pBuf, unsigned int *uiSize, int iIsSound)
{
  int iFile; // eax
  void *pBuf2; // eax
  uint8 *pUint8Buf; // edx

  *pBuf = 0;
  *uiSize = 0;
  iFile = open(szFile, O_RDONLY | O_BINARY); //0x200 is O_BINARY in WATCOM/h/fcntl.h
  if (iFile == -1) {
    *uiSize = 0;
    *pBuf = 0;
  } else {
    close(iFile);
    *uiSize = getcompactedfilelength(szFile);
    if (!iIsSound || iIsSound == 1 && soundon) {
      pBuf2 = trybuffer(*uiSize);
      *pBuf = pBuf2;
      if (pBuf2) {
        pUint8Buf = (uint8 *)pBuf2;
        initmangle(szFile);
        loadcompactedfilepart(pUint8Buf, *uiSize);
        uninitmangle();
      }
    }
  }
}

//-------------------------------------------------------------------------------------------------

int ReadJoys(int *a1)
{
  return 0; /*
  unsigned __int8 v2; // al
  int v3; // ebx
  int v4; // eax
  int v5; // esi
  int v6; // ecx
  int v7; // edi
  int v8; // eax
  int v9; // ebx
  int result; // eax
  int v12; // [esp+4h] [ebp-2Ch]
  int v13; // [esp+8h] [ebp-28h]
  int v14; // [esp+Ch] [ebp-24h]
  int v15; // [esp+10h] [ebp-20h]
  int v16; // [esp+14h] [ebp-1Ch]

  v2 = __inbyte(0x201u);
  v3 = 0;
  v15 = 0;
  v16 = 0;
  v4 = (int)(unsigned __int8)~v2 >> 4;
  v13 = 0;
  *a1 = v4 & 1;
  a1[1] = (v4 & 3) >> 1;
  v5 = 0;
  a1[4] = (v4 >> 2) & 1;
  a1[5] = ((v4 >> 2) & 3) >> 1;
  _disable();
  __outbyte(0x201u, 0xFFu);
  v14 = x1ok;
  v6 = y1ok;
  v12 = x2ok;
  v7 = y2ok;
  do {
    v8 = 0;
    LOBYTE(v8) = __inbyte(0x201u);
    if (x1ok) {
      v14 = v8 & 1;
      if ((v8 & 1) != 0)
        ++v15;
    }
    if (y1ok) {
      v6 = v8 & 2;
      if ((v8 & 2) != 0)
        ++v16;
    }
    if (x2ok) {
      v12 = v8 & 4;
      if ((v8 & 4) != 0)
        ++v5;
    }
    if (y2ok) {
      v7 = v8 & 8;
      if ((v8 & 8) != 0)
        ++v13;
    }
    ++v3;
  } while ((v8 & bitaccept) != 0 && v3 < 10000);
  v9 = v14;
  _enable();
  if (v9) {
    a1[2] = 0;
    x1ok = 0;
    bitaccept = y2ok | y1ok | x2ok;
  } else {
    a1[2] = v15;
  }
  if (v6) {
    a1[3] = 0;
    y1ok = 0;
    bitaccept = y2ok | x1ok | x2ok;
  } else {
    a1[3] = v16;
  }
  if (v12) {
    a1[6] = 0;
    x2ok = 0;
    bitaccept = y2ok | y1ok | x1ok;
  } else {
    a1[6] = v5;
  }
  if (v7) {
    a1[7] = 0;
    y2ok = 0;
    result = x2ok | y1ok | x1ok;
    bitaccept = result;
  } else {
    result = v13;
    a1[7] = v13;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int check_joystickpresence()
{
  return 0; /*
  int v0; // ebx
  int v1; // esi
  int v2; // ecx
  int v3; // edi
  int v4; // eax
  int result; // eax
  int v6; // [esp+0h] [ebp-18h]

  v0 = 0;
  x1ok = 1;
  y1ok = 2;
  x2ok = 4;
  y2ok = 8;
  bitaccept = 15;
  JAXmin = 10000;
  JAXmax = -10000;
  JAYmin = 10000;
  JAYmax = -10000;
  JBXmin = 10000;
  JBXmax = -10000;
  JBYmin = 10000;
  JBYmax = -10000;
  __outbyte(0x201u, 0xFFu);
  v6 = x1ok;
  v1 = y1ok;
  v2 = x2ok;
  v3 = y2ok;
  do {
    v4 = 0;
    LOBYTE(v4) = __inbyte(0x201u);
    if (x1ok)
      v6 = v4 & 1;
    if (y1ok)
      v1 = v4 & 2;
    if (x2ok)
      v2 = v4 & 4;
    if (y2ok)
      v3 = v4 & 8;
    ++v0;
  } while ((v4 & bitaccept) != 0 && v0 < 10000);
  if (v6)
    x1ok = 0;
  if (v2)
    x2ok = 0;
  if (v1)
    y1ok = 0;
  if (v3)
    y2ok = 0;
  result = y2ok;
  bitaccept = y2ok | y1ok | x1ok | x2ok;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int initsounds()
{
  return 0; /*
  int v0; // ebx
  int result; // eax
  int i; // ecx
  int v3; // edx

  v0 = numcars;
  result = 8;
  HandleSample = -1;
  HandleCar = -1;
  HandleSample_variable_1 = -1;
  HandleCar_variable_1 = -1;
  do {
    result += 20;
    *(int *)((char *)&HandleCar_variable_2 + result) = -1;
    *(int *)((char *)&SamplePending_variable_3 + result) = -1;
    *(int *)((char *)&HandleCar_variable_3 + result) = -1;
    *(int *)((char *)&SamplePending_variable_4 + result) = -1;
    *(int *)((char *)&HandleCar_variable_4 + result) = -1;
    *(int *)((char *)&SamplePending_variable_5 + result) = -1;
    *(int *)((char *)&HandleCar_variable_5 + result) = -1;
    *(int *)((char *)&SamplePending_variable_6 + result) = -1;
    *(int *)((char *)&HandleCar_variable_6 + result) = -1;
    *(int *)((char *)&SamplePending_variable_7 + result) = -1;
  } while (result != 128);
  for (i = 0; i != 7680; i += 64) {
    v3 = 0;
    if (v0 > 0) {
      result = i;
      do {
        result += 4;
        ++v3;
        *(int *)((char *)&SamplePtr_variable_15 + result) = -1;
      } while (v3 < v0);
    }
  }
  if (v0 > 0) {
    result = 0;
    do {
      result += 4;
      *(int *)((char *)&SampleExt_variable_1 + result) = 0;
    } while (result < 4 * v0);
  }
  numcars = v0;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int stopallsamples()
{
  return 0; /*
  int i; // edx
  int v1; // ebx
  int v2; // ebp
  int v3; // eax
  int result; // eax
  int j; // esi
  int v6; // ecx
  int v7; // ebx
  int v8; // ecx

  _disable();
  for (i = 0; i != 896; i += 28) {
    v1 = 0;
    if (numcars > 0) {
      v2 = numcars;
      v3 = i;
      do {
        *(int *)((char *)&enginedelay_variable_1 + v3) = -1;
        *(int *)((char *)&enginedelay_variable_3 + v3) = -1;
        *(int *)((char *)&enginedelay_variable_5 + v3) = -1;
        ++v1;
        v3 += 896;
      } while (v1 < v2);
    }
  }
  result = numcars;
  for (j = 0; j < numcars; ++j) {
    v6 = 0;
    if (numsamples > 0) {
      v7 = j;
      do {
        if (SampleHandleCar[v7] != -1)
          sosDIGIStopSample(DIGIHandle);
        v7 += 16;
        result = numsamples;
        ++v6;
        SamplePtr_variable_14[v7] = -1;
      } while (v6 < result);
    }
  }
  v8 = 2;
  HandleSample = -1;
  HandleCar = -1;
  HandleSample_variable_1 = -1;
  HandleCar_variable_1 = -1;
  do {
    v8 += 5;
    HandleCar_variable_2[v8] = -1;
    SamplePending_variable_3[v8] = -1;
    HandleCar_variable_3[v8] = -1;
    SamplePending_variable_4[v8] = -1;
    HandleCar_variable_4[v8] = -1;
    SamplePending_variable_5[v8] = -1;
    HandleCar_variable_5[v8] = -1;
    SamplePending_variable_6[v8] = -1;
    HandleCar_variable_6[v8] = -1;
    SamplePending_variable_7[v8] = -1;
  } while (v8 != 32);
  lastsample = -1000;
  _enable();
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int pannedsample(int result, int a2, int a3)
{
  return 0; /*
  int v3; // esi
  int v4; // edi
  int v6; // ebp
  unsigned int v7; // ebx
  int v8; // eax
  unsigned int v9; // ebx
  unsigned int v10; // ecx

  v3 = result;
  v4 = a2;
  if (soundon && SamplePtr[result]) {
    v6 = result << 6;
    v7 = SampleHandleCar[16 * result];
    if (v7 != -1) {
      _disable();
      a2 = SampleHandleCar[16 * result];
      if (!sosDIGISampleDone(DIGIHandle, v7)) {
        a2 = v7;
        sosDIGIStopSample(DIGIHandle);
        *(int *)((char *)SampleHandleCar + v6) = -1;
        HandleSample[v7] = -1;
      }
      _enable();
    }
    SamplePanned_variable_1 = __DS__;
    SamplePanned_variable_4 = v3;
    SamplePanned_variable_3 = v4;
    v8 = SamplePtr[v3];
    SamplePanned_variable_5 = a3;
    SamplePanned = v8;
    SamplePanned_variable_2 = SampleLen[v3];
    _disable();
    v9 = sosDIGIStartSample(DIGIHandle, a2, &SamplePanned, __DS__);
    result = v3 << 6;
    SampleHandleCar[16 * v3] = v9;
    _enable();
    if (v9 != -1) {
      if (v9 >= 0x20)
        _assert(0, aS0S32, &aDpsoundC[2], 2071);
      v10 = HandleSample[v9];
      if (v10 != -1) {
        if (v10 >= 0x78)
          _assert(0, &aIHandlesampleS[3], &aDpsoundC[2], 2075);
        if ((unsigned int)HandleCar[v9] >= 0x10)
          _assert(0, aHandlecarS0Han, &aDpsoundC[2], 2076);
        SampleHandleCar[16 * HandleSample[v9] + HandleCar[v9]] = -1;
      }
      result = 0;
      HandleSample[v9] = v3;
      HandleCar[v9] = 0;
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int speechonly(int result, int a2, int a3, int a4)
{
  return 0; /*
  if (readsample == writesample && -a3 > lastsample)
    return speechsample(result, a2, a3, a4);
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int speechsample(int result, int a2, int a3, int a4)
{
  return 0; /*
  int v4; // edi
  int v5; // esi

  v4 = writesample;
  v5 = result;
  if (!disable_messages) {
    if (result == 30) {
      result = ++game_overs;
      if (player_type != 2 || result == 2)
        disable_messages = -1;
    }
    if (!winner_mode || v5 >= 89) {
      result = 16 * writesample;
      *(int *)((char *)&speechinfo + result) = v5;
      *(int *)((char *)&speechinfo_variable_1 + result) = a2;
      *(int *)((char *)&speechinfo_variable_2 + result) = a3;
      ++v4;
      *(int *)((char *)&speechinfo_variable_3 + result) = a4;
      if (v4 == 16)
        v4 = 0;
    }
  }
  writesample = v4;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int analysespeechsamples()
{
  return 0; /*
  int result; // eax
  int v1; // ecx
  int v2; // esi
  int v3; // edx
  char *v4; // eax
  char *v5; // eax
  int v6; // eax
  int v7; // edx
  int v8; // edi
  int v9; // ecx
  int v10; // eax

  result = readsample;
  --lastsample;
  if (readsample != writesample) {
    result = -speechinfo_variable_2[4 * readsample];
    if (result > lastsample) {
      v1 = (unsigned __int8)speechinfo_variable_3[4 * readsample];
      v2 = speechinfo_variable_3[4 * readsample] >> 8;
      v3 = player_type == 2 && v1 != (__int16)player1_car;
      switch (speechinfo[4 * readsample]) {
        case 14:
          start_zoom(language_buffer_variable_30, v3);
          if (Car_variable_43[308 * v1])
            goto LABEL_13;
          goto LABEL_61;
        case 15:
          v6 = Car_variable_31[308 * v1];
          if (NoOfLaps == v6)
            goto LABEL_15;
          sprintf(&buffer, "%i %s", NoOfLaps + 1 - v6, language_buffer_variable_58);
          v5 = &buffer;
          goto LABEL_60;
        case 16:
        case 17:
        case 18:
        LABEL_15:
          v5 = (char *)&language_buffer_variable_35;
          goto LABEL_60;
        case 21:
          if (Car_variable_23[308 * Victim] <= 0)
            v4 = language_buffer_variable_31;
          else
            v4 = language_buffer_variable_30;
          start_zoom(v4, v3);
          sprintf(&buffer, "%s %s", language_buffer_variable_32, &driver_names[9 * Victim]);
          subzoom(&buffer);
          goto LABEL_61;
        case 22:
          v5 = language_buffer_variable_40;
          goto LABEL_60;
        case 23:
        case 24:
        case 25:
          v5 = (char *)&language_buffer + 64 * (unsigned __int8)Car_variable_32[308 * v1] + 384;
          goto LABEL_60;
        case 26:
          v5 = (char *)&language_buffer_variable_41;
          goto LABEL_60;
        case 30:
          v5 = (char *)&language_buffer_variable_33;
          goto LABEL_60;
        case 37:
        case 38:
          start_zoom(language_buffer_variable_43, v3);
          make_time(&buffer, v3, *(float *)&Car_variable_53[77 * v1]);
          subzoom(&buffer);
          goto LABEL_61;
        case 39:
          start_zoom(language_buffer_variable_44, v3);
          make_time(&buffer, v3, *(float *)&Car_variable_53[77 * v1]);
          subzoom(&buffer);
          goto LABEL_61;
        case 40:
          start_zoom(language_buffer_variable_45, v3);
          make_time(&buffer, v3, *(float *)&Car_variable_53[77 * v1]);
          subzoom(&buffer);
          goto LABEL_61;
        case 43:
          v5 = (char *)&language_buffer_variable_46;
          goto LABEL_60;
        case 44:
          v5 = (char *)&language_buffer_variable_47;
          goto LABEL_60;
        case 45:
          start_zoom(language_buffer_variable_31, v3);
          if (Car_variable_43[308 * v1]) {
          LABEL_13:
            sprintf(
              &buffer,
              "%s %s",
              language_buffer_variable_34,
              &driver_names[9 * (unsigned __int8)Car_variable_41[308 * v1]]);
            subzoom(&buffer);
          }
          goto LABEL_61;
        case 46:
          v5 = (char *)&language_buffer_variable_42;
          goto LABEL_60;
        case 51:
          v5 = (char *)&language_buffer_variable_95;
          goto LABEL_60;
        case 52:
          v5 = (char *)&language_buffer_variable_96;
          goto LABEL_60;
        case 53:
          v5 = (char *)&language_buffer_variable_39;
          goto LABEL_60;
        case 54:
          v5 = (char *)&language_buffer_variable_38;
          goto LABEL_60;
        case 55:
          v5 = (char *)&language_buffer_variable_37;
          goto LABEL_60;
        case 56:
          v5 = (char *)&language_buffer_variable_36;
          goto LABEL_60;
        case 57:
        case 58:
        case 59:
        case 60:
          small_zoom(language_buffer_variable_78);
          subzoom((_BYTE *)&language_buffer + 64 * speechinfo[4 * readsample] + 1408);
          goto LABEL_61;
        case 65:
        case 66:
          small_zoom(language_buffer_variable_77);
          subzoom((_BYTE *)&language_buffer + 64 * v2 + 1152);
          goto LABEL_61;
        case 71:
        case 72:
        case 73:
        case 74:
        case 75:
        case 76:
        case 77:
        case 78:
          small_zoom((_BYTE *)&language_buffer + 64 * speechinfo[4 * readsample] + 768);
          switch (v2) {
            case '=':
            case '>':
            case '?':
            case '@':
              subzoom((_BYTE *)&language_buffer + 64 * v2 + 1152);
              break;
            case 'C':
              subzoom(language_buffer_variable_93);
              break;
            case 'D':
              subzoom(language_buffer_variable_94);
              break;
            case 'E':
              subzoom(language_buffer_variable_92);
              break;
            case 'F':
              subzoom(language_buffer_variable_91);
              break;
            default:
              goto LABEL_61;
          }
          goto LABEL_61;
        case 89:
        case 90:
        case 91:
        case 92:
        case 93:
        case 94:
        case 95:
        case 96:
          v7 = total_wins[champorder[0]];
          if (v7 == 1)
            sprintf(&buffer, "%s", config_buffer_variable_85);
          else
            sprintf(&buffer, "%s %i %s", config_buffer_variable_83, v7, config_buffer_variable_84);
          v5 = &buffer;
          goto LABEL_59;
        case 97:
        case 98:
        case 99:
        case 100:
        case 101:
        case 102:
        case 103:
        case 104:
        case 105:
        case 106:
        case 107:
        case 108:
        case 109:
        case 110:
        case 111:
        case 112:
        case 113:
          if (champ_mode) {
            v8 = total_kills[champorder[0]];
            if (v8 == 1)
              sprintf(&buffer, "%s", config_buffer_variable_80);
            else
              sprintf(&buffer, "%s %i %s", config_buffer_variable_81, v8, config_buffer_variable_82);
            v5 = &buffer;
          } else {
            v9 = result_kills[result_order[0]];
            if (v9 != 1) {
              sprintf(&buffer, "%s %i %s", config_buffer_variable_81, v9, config_buffer_variable_82);
              v3 = 0;
              v5 = &buffer;
              goto LABEL_60;
            }
            v5 = config_buffer_variable_80;
          }
        LABEL_59:
          v3 = 0;
        LABEL_60:
          start_zoom(v5, v3);
        LABEL_61:
          if (soundon) {
            v10 = speechinfo[4 * readsample];
            if (SamplePtr[v10])
              dospeechsample(v10, speechinfo_variable_1[4 * readsample]);
          }
          result = 36 * SampleLen[speechinfo[4 * readsample++]] / 11025;
          lastsample = result;
          if (readsample == 16)
            readsample = 0;
          break;
        case 115:
          if (result_kills[result_order[0]] <= 0 && result_order[0] != FastestLap)
            goto LABEL_61;
          v5 = (char *)&config_buffer_variable_74;
          goto LABEL_59;
        case 116:
          v5 = (char *)&config_buffer_variable_75;
          goto LABEL_59;
        case 117:
          v5 = (char *)&config_buffer_variable_76;
          goto LABEL_59;
        default:
          goto LABEL_61;
      }
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void dospeechsample(int iSampleIdx, int iVolume)
{
  int iUseVolume;
  int iHandle, iSampleHandle;

  // Check sample pointer is valid
  if (SamplePtr[iSampleIdx] == 0)
    return;

  // Clamp volume to 0x7FFF
  if (iVolume > 0x7FFF)
    iVolume = 0x7FFF;

  // Scale volume by speech volume setting (div 127)
  iUseVolume = (SpeechVolume * iVolume) / 127;

  // Abort if sound is off or paused
  if (!soundon || paused)
    return;

  iSampleHandle = SampleHandleCar[iSampleIdx].handles[0];

  // If a sample is already assigned
  if (iSampleHandle != -1) {
    //if (sosDIGISampleDone(DIGIHandle, iSampleHandle) == 0) {
    //  // Stop previous sample if it's still playing
    //  sosDIGIStopSample(DIGIHandle, iSampleHandle);
    //  SampleHandleCar[iSampleIndex].handles[0] = -1;
    //  HandleSample[iSampleHandle] = -1;
    //}
  }

  // Setup sample parameters
  //SampleFixed.unSegment = __DS__;
  SampleFixed.iSampleIndex = iSampleIdx;
  SampleFixed.iVolume = iUseVolume;
  SampleFixed.pSample = SamplePtr[iSampleIdx];
  SampleFixed.iLength = SampleLen[iSampleIdx];

  // Start sample
  iHandle = -1;// sosDIGIStartSample(DIGIHandle, iSampleIndex << 6, &SampleFixed);
  SampleHandleCar[iSampleIdx].handles[0] = iHandle;

  if (iHandle == -1)
    return;

  int iPrevHandle = HandleSample[iHandle];

  // If that handle was previously used for another sample
  if (iPrevHandle != -1)
    SampleHandleCar[iPrevHandle].handles[HandleCar[iHandle]] = -1;

  HandleSample[iHandle] = iSampleIdx;
  HandleCar[iHandle] = 0;
}

//-------------------------------------------------------------------------------------------------

int loadfrontendsample(int result)
{
  return 0; /*
  char *v1; // esi
  char *v2; // edi
  char v3; // al
  char v4; // al
  int v5; // esi
  int v6; // ecx
  char *v7; // ebx
  int v8; // edi
  char v9; // dh
  char v10; // dl
  int i; // ebx
  int v12; // ecx
  int j; // ebx
  _BYTE v14[32]; // [esp+0h] [ebp-3Ch] BYREF
  int v15; // [esp+20h] [ebp-1Ch]

  v1 = (char *)result;
  if (SoundCard) {
    if (frontendspeechhandle != -1) {
      _disable();
      sosDIGIStopSample(DIGIHandle);
      _enable();
      frontendspeechhandle = -1;
    }
    if (frontendspeechptr)
      fre(&frontendspeechptr);
    v2 = v14;
    do {
      v3 = *v1;
      *v2 = *v1;
      if (!v3)
        break;
      v4 = v1[1];
      v1 += 2;
      v2[1] = v4;
      v2 += 2;
    } while (v4);
    convertname(v14, &frontendspeechptr, &frontendlen, 0);
    result = loadfile((int)v14, &frontendspeechptr, (unsigned int *)&frontendlen, 0);
    if (cheatsample) {
      result = frontendspeechptr;
      if (frontendspeechptr) {
        v5 = 7283;
        v6 = 2198;
        v7 = (char *)frontendspeechptr;
        v8 = frontendlen;
        for (result = 0; result < v8; *(v7 - 1) = v10 ^ v9) {
          ++result;
          v9 = *v7;
          v15 = v6 + v5;
          ++v7;
          v10 = v6 + v5;
          v5 = v6;
          v6 = v15;
        }
      }
    }
    if (frontendspeechptr && (cheat_mode & 0x800) != 0) {
      if ((cheat_mode & 0x2000) != 0) {
        for (i = 0; i < frontendlen; i += 2)
          *(_BYTE *)(frontendspeechptr + i / 2) = *(_BYTE *)(frontendspeechptr + i);
        result = frontendlen / 2;
        frontendlen /= 2;
      } else {
        v12 = 0;
        for (j = 0; j < frontendlen; ++j) {
          result = j / 3;
          if (j % 3 != 2) {
            result = frontendspeechptr;
            *(_BYTE *)(++v12 + frontendspeechptr - 1) = *(_BYTE *)(j + frontendspeechptr);
          }
        }
        frontendlen = v12;
      }
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int frontendsample(int a1)
{
  return 0; /*
  int v1; // edx
  int result; // eax

  v1 = a1;
  result = resetsamplearray(a1, a1);
  if (soundon && frontendspeechptr) {
    if (v1 > 0x7FFF)
      v1 = 0x7FFF;
    SampleFixed_variable_1 = __DS__;
    SampleFixed_variable_4 = 0;
    SampleFixed = frontendspeechptr;
    SampleFixed_variable_3 = SpeechVolume * v1 / 127;
    SampleFixed_variable_2 = frontendlen;
    _disable();
    result = sosDIGIStartSample(DIGIHandle, SampleFixed_variable_3, &SampleFixed, __DS__);
    frontendspeechhandle = result;
    _enable();
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void *remove_frontendspeech()
{
  return 0; /*
  _DWORD *result; // eax

  if (SoundCard) {
    if (frontendspeechhandle != -1) {
      _disable();
      result = (_DWORD *)sosDIGIStopSample(DIGIHandle);
      _enable();
      frontendspeechhandle = -1;
    }
    if (frontendspeechptr)
      return fre(&frontendspeechptr);
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int sfxplaying(int a1)
{
  return 0; /*
  int v1; // ecx
  unsigned int v2; // ebx
  int result; // eax

  v1 = a1 << 6;
  v2 = SampleHandleCar[16 * a1];
  if (v2 == -1)
    return 0;
  if (!sosDIGISampleDone(DIGIHandle, v2))
    return -1;
  result = 0;
  *(int *)((char *)SampleHandleCar + v1) = -1;
  HandleSample[v2] = -1;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int cheatsampleok(int a1)
{
  if (a1 == player1_car || a1 == player2_car)
    return -1;
  else
    return 0;
}

//-------------------------------------------------------------------------------------------------

int sfxsample(int64 a1)
{
  return 0; /*
  int v1; // ebx
  int v2; // esi
  int v3; // ebx
  int v4; // ecx

  v1 = HIDWORD(a1);
  v2 = a1;
  if (SamplePtr[(_DWORD)a1]) {
    if (SHIDWORD(a1) > 0x7FFF)
      v1 = 0x7FFF;
    LODWORD(a1) = v1 * SFXVolume / 127;
    v3 = a1;
    if (soundon && !paused) {
      v4 = SampleHandleCar[16 * v2];
      if (v4 != -1) {
        _disable();
        if (!sosDIGISampleDone(DIGIHandle, SampleHandleCar[16 * v2])) {
          sosDIGIStopSample(DIGIHandle);
          SampleHandleCar[16 * v2] = -1;
          HandleSample[v4] = -1;
        }
        _enable();
      }
      SampleFixed_variable_1 = __DS__;
      SampleFixed_variable_4 = v2;
      SampleFixed_variable_3 = v3;
      SampleFixed = SamplePtr[v2];
      SampleFixed_variable_2 = SampleLen[v2];
      _disable();
      a1 = sosDIGIStartSample(DIGIHandle, v2 << 6, &SampleFixed, __DS__);
      *(int *)((char *)SampleHandleCar + HIDWORD(a1)) = a1;
      _enable();
      if ((_DWORD)a1 != -1) {
        HIDWORD(a1) = HandleSample[(_DWORD)a1];
        if (HIDWORD(a1) != -1)
          SampleHandleCar[16 * HIDWORD(a1) + HandleCar[(_DWORD)a1]] = -1;
        HandleSample[(_DWORD)a1] = v2;
        HandleCar[(_DWORD)a1] = 0;
      }
    }
  }
  return a1;*/
}

//-------------------------------------------------------------------------------------------------

int sample2(
        int64 rax0,
        int ecx0,
        int ebx0,
        int64 a1,
        int a2,
        int a3,
        int a4,
        int a5)
{
  return 0; /*
  int v8; // esi
  int v9; // edi
  int v10; // ecx
  int v12; // [esp+0h] [ebp-14h]

  v8 = rax0;
  if (soundon) {
    if (!paused) {
      LODWORD(rax0) = 4 * rax0;
      v9 = rax0 + (HIDWORD(rax0) << 6);
      if (*(int *)((char *)SampleHandleCar + v9) == -1) {
        SampleData_variable_5 = HIDWORD(rax0);
        SampleData_variable_6 = ecx0;
        v12 = SamplePtr[HIDWORD(rax0)];
        SampleData_variable_2 = SampleLen[HIDWORD(rax0)];
        SampleData_variable_1 = __DS__;
        SampleData_variable_7 = a1;
        SampleData = v12;
        SampleData_variable_3 = HIDWORD(a1);
        SampleData_variable_4 = ebx0;
        rax0 = sosDIGIStartSample(DIGIHandle, HIDWORD(rax0), &SampleData, __DS__);
        *(int *)((char *)SampleHandleCar + v9) = rax0;
        if ((_DWORD)rax0 != -1) {
          v10 = HandleSample[(_DWORD)rax0];
          if (v10 != -1)
            SampleHandleCar[16 * v10 + HandleCar[(_DWORD)rax0]] = -1;
          HandleSample[(_DWORD)rax0] = HIDWORD(rax0);
          HandleCar[(_DWORD)rax0] = v8;
        }
      }
    }
  }
  return rax0;*/
}

//-------------------------------------------------------------------------------------------------

int sfxpend(int a1, int a2, int a3)
{
  return 0; /*
  int v5; // edi
  int result; // eax
  int v7; // edi
  int v8; // esi
  int i; // edx
  int v10; // ecx

  v5 = a3;
  if (a3 > 0x7FFF)
    v5 = 0x7FFF;
  if (replaytype != 2) {
    newrepsample[a2] = a1;
    repvolume[a2] = (unsigned __int16)(v5 - (__CFSHL__(v5 >> 31, 8) + ((unsigned __int16)(v5 >> 31) << 8))) >> 8;
  }
  result = v5 * SFXVolume / 127;
  v7 = result;
  if (soundon) {
    result = 4 * a2;
    if (Pending[a2] != 5) {
      v8 = 0;
      result = 160 * a2;
      for (i = 0; i < Pending[a2]; result += 8) {
        if (a1 == *(int *)((char *)&SamplePending + result))
          v8 = -1;
        ++i;
      }
      if (!v8) {
        result = 160 * a2 + 8 * Pending[a2];
        *(int *)((char *)&SamplePending + result) = a1;
        v10 = Pending[a2] + 1;
        *(int *)((char *)&SamplePending_variable_1 + result) = v7;
        Pending[a2] = v10;
      }
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int enginesounds2(int result, int a2)
{
  return 0; /*
  int v2; // ecx
  int v3; // ecx

  if (soundon) {
    delaywritex = delaywrite & 0x1F;
    v2 = 224 * result;
    enginedelay_variable_1[7 * (delaywrite & 0x1F) + v2] = -1;
    enginedelay_variable_3[7 * delaywritex + v2] = -1;
    enginedelay_variable_5[7 * delaywritex + v2] = -1;
    v3 = 224 * a2;
    enginedelay_variable_1[7 * delaywritex + v3] = -1;
    enginedelay_variable_3[7 * delaywritex + v3] = -1;
    enginedelay_variable_5[7 * delaywritex + v3] = -1;
    enginesound(0.0, 0.0, 2000.0, 0x8000);
    enginesound(0.0, 0.0, 2000.0, 0x8000);
    return delaywrite++;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int enginesounds(int result)
{
  return 0; /*
  int v1; // edi
  unsigned int v2; // eax
  int v3; // ebp
  float *v4; // eax
  int v5; // edx
  float *v6; // edx
  int v7; // ebx
  double v8; // st7
  double v9; // st6
  int v10; // ebp
  double v11; // st7
  int v12; // ecx
  float *v13; // ebx
  int v14; // eax
  int v15; // esi
  int v16; // esi
  __int64 v17; // rax
  int v18; // eax
  int v19; // esi
  double v20; // st7
  double v21; // st6
  int v22; // edx
  int v23; // eax
  int v24; // eax
  double v25; // st7
  int v26; // [esp+0h] [ebp-9Ch]
  int v27; // [esp+4h] [ebp-98h] BYREF
  int v28; // [esp+8h] [ebp-94h] BYREF
  int v29; // [esp+10h] [ebp-8Ch] BYREF
  float v30; // [esp+14h] [ebp-88h]
  float v31; // [esp+18h] [ebp-84h]
  float v32; // [esp+20h] [ebp-7Ch]
  float v33; // [esp+24h] [ebp-78h]
  float v34; // [esp+28h] [ebp-74h]
  float v35; // [esp+2Ch] [ebp-70h]
  float v36; // [esp+30h] [ebp-6Ch]
  float v37; // [esp+34h] [ebp-68h]
  float v38; // [esp+38h] [ebp-64h]
  float v39; // [esp+3Ch] [ebp-60h]
  float v40; // [esp+40h] [ebp-5Ch]
  int v41; // [esp+44h] [ebp-58h]
  float v42; // [esp+48h] [ebp-54h]
  int v43; // [esp+4Ch] [ebp-50h]
  float v44; // [esp+50h] [ebp-4Ch]
  float v45; // [esp+54h] [ebp-48h]
  float v46; // [esp+58h] [ebp-44h]
  float v47; // [esp+5Ch] [ebp-40h]
  float v48; // [esp+60h] [ebp-3Ch]
  float v49; // [esp+64h] [ebp-38h]
  float v50; // [esp+68h] [ebp-34h]
  int v51; // [esp+6Ch] [ebp-30h]
  int v52; // [esp+70h] [ebp-2Ch]
  int v53; // [esp+74h] [ebp-28h]
  float v54; // [esp+78h] [ebp-24h]
  float v55; // [esp+7Ch] [ebp-20h]
  float v56; // [esp+80h] [ebp-1Ch]

  v1 = result;
  if (soundon) {
    delaywritex = delaywrite & 0x1F;
    if (numcars > 0) {
      v2 = 0;
      v3 = 896 * numcars;
      do {
        enginedelay_variable_1[7 * delaywritex + v2 / 4] = -1;
        enginedelay_variable_3[7 * delaywritex + v2 / 4] = -1;
        v2 += 896;
        SamplePending_variable_2[7 * delaywritex + v2 / 4] = -1;
      } while ((int)v2 < v3);
    }
    if (DriveView[0] == 3 || DriveView[0] == 6) {
      if (DriveView[0] == 6) {
        v42 = -localdata_variable_16;
        *(float *)&v43 = -localdata_variable_17;
        v10 = 2;
        *(float *)&v41 = sound_c_variable_37 - localdata_variable_18;
      } else {
        v10 = TowerBase[5 * NearTow];
        v42 = *(float *)&TowerGx;
        v43 = TowerGy;
        v41 = TowerGz;
      }
      v39 = 0.0;
      v38 = 0.0;
      v40 = 0.0;
    } else {
      enginesound(0.0, 0.0, 2000.0, 0x8000);
      v4 = &Car[77 * v1];
      v5 = *((__int16 *)v4 + 6);
      if (v5 == -1) {
        v42 = *v4;
        v43 = *((int *)v4 + 1);
        v41 = *((int *)v4 + 2);
        v39 = v4[10];
        v38 = v4[11];
        v40 = v4[12];
      } else {
        v6 = (float *)((char *)&localdata + 128 * v5);
        v42 = v6[1] * v4[1] + *v6 * *v4 + v6[2] * v4[2] - v6[9];
        *(float *)&v43 = v6[4] * v4[1] + v6[3] * *v4 + v6[5] * v4[2] - v6[10];
        *(float *)&v41 = v6[7] * v4[1] + v6[6] * *v4 + v6[8] * v4[2] - v6[11];
        v7 = *((_DWORD *)v4 + 16);
        v8 = v4[6] * tcos[v7];
        v9 = v4[6] * tsin[v7];
        v39 = v6[1] * v9 + *v6 * v8;
        v38 = v6[3] * v8 + v6[4] * v9;
        v40 = v8 * v6[6] + v9 * v6[7];
      }
      v10 = *((__int16 *)v4 + 6);
      if (v10 == -1)
        v10 = *((__int16 *)v4 + 7);
    }
    if (DriveView[0] != 3 && DriveView[0] != 6) {
      if (Car_variable_17[77 * v1] == 3) {
        getworldangles(&v28, &v29, &v27);
      } else {
        v28 = Car_variable_7[154 * v1];
        v29 = Car_variable_6[154 * v1];
        v27 = Car_variable_5[154 * v1];
      }
      v32 = tcos[v28] * tcos[v29];
      v37 = tcos[v28] * tsin[v29] * tsin[v27] - tsin[v28] * tcos[v27];
      v35 = tsin[v28] * tcos[v29];
      v36 = tsin[v28] * tsin[v29] * tsin[v27] + tcos[v28] * tcos[v27];
      v11 = -tsin[v27] * tcos[v29];
      v34 = tsin[v29];
      v33 = v11;
    }
    v12 = 0;
    if (numcars > 0) {
      v13 = Car;
      do {
        v14 = -1;
        if (Car_variable_23[308 * v12] < 0)
          v14 = 0;
        if (DriveView[0] == 3 || DriveView[0] == 6) {
          if (v12 == v1 || allengines)
            goto LABEL_34;
        } else if (v12 != v1 && allengines) {
          goto LABEL_34;
        }
        v14 = 0;
      LABEL_34:
        if (v14) {
          v15 = Car_variable_3[154 * v12];
          if (v15 == -1)
            v15 = Car_variable_4[154 * v12];
          v16 = v15 - v10;
          if (v16 < 0)
            v16 += TRAK_LEN;
          if (v16 > TRAK_LEN / 2)
            v16 -= TRAK_LEN;
          v17 = v16;
          if ((int)abs32(v16) >= 40) {
            enginesound(0.0, 0.0, 1048576.0, 0x8000);
          } else {
            v18 = *((__int16 *)v13 + 6);
            if (v18 == -1) {
              v47 = *v13;
              v55 = v13[1];
              v49 = v13[2];
              v56 = v13[10];
              v46 = v13[11];
              *(float *)&v17 = v13[12];
              v48 = *(float *)&v17;
            } else {
              LODWORD(v17) = (char *)&localdata + 128 * v18;
              v47 = *(float *)(v17 + 4) * v13[1]
                + *(float *)v17 * *v13
                + *(float *)(v17 + 8) * v13[2]
                - *(float *)(v17 + 36);
              v55 = *(float *)(v17 + 16) * v13[1]
                + *(float *)(v17 + 12) * *v13
                + *(float *)(v17 + 20) * v13[2]
                - *(float *)(v17 + 40);
              v49 = *(float *)(v17 + 28) * v13[1]
                + *(float *)(v17 + 24) * *v13
                + *(float *)(v17 + 32) * v13[2]
                - *(float *)(v17 + 44);
              v19 = *((_DWORD *)v13 + 16);
              v20 = v13[6] * tcos[v19];
              v21 = v13[6] * tsin[v19];
              v56 = *(float *)(v17 + 4) * v21 + *(float *)v17 * v20;
              v46 = *(float *)(v17 + 12) * v20 + *(float *)(v17 + 16) * v21;
              v48 = v20 * *(float *)(v17 + 24) + v21 * *(float *)(v17 + 28);
            }
            v54 = v47 - v42;
            *(float *)&v52 = v55 - *(float *)&v43;
            *(float *)&v53 = v49 - *(float *)&v41;
            v30 = v54 * v54 + *(float *)&v52 * *(float *)&v52;
            v50 = *(float *)&v53 * *(float *)&v53 + v30;
            v30 = sqrt(v30);
            v50 = sqrt(v50);
            v22 = getangle(v17, SHIDWORD(v17), v54, v52);
            v23 = getangle(v22, v22, v30, v53);
            v44 = (v39 * tcos[v22] + v38 * tsin[v22]) * tcos[v23] + v40 * tsin[v23];
            v45 = -(v56 * tcos[v22] + v46 * tsin[v22]) * tcos[v23] + v48 * tsin[v23];
            if (DriveView[0] == 3 || DriveView[0] == 6) {
              v51 = 0x8000;
            } else {
              v31 = v54 * v32 + *(float *)&v52 * v35 + *(float *)&v53 * v34;
              *(float *)&v26 = v54 * v37 + *(float *)&v52 * v36 + *(float *)&v53 * v33;
              v24 = getangle(v23, v22, v31, v26);
              v25 = (1.0 - tsin[v24]) * sound_c_variable_38;
              _CHP(v24, v22);
              v51 = (int)v25;
              if ((int)v25 >= (int)cstart_branch_1)
                v51 = 0xFFFF;
            }
            enginesound(v44, v45, v50, v51);
          }
        }
        ++v12;
        v13 += 77;
      } while (v12 < numcars);
    }
    return delaywrite++;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int loopsample(int result, unsigned int a2, int a3, int a4, int a5)
{
  return 0; /*
  unsigned int v5; // ebp
  unsigned int v7; // ebx
  int v8; // esi
  int v9; // ecx
  unsigned int v10; // ebp
  __int64 v11; // [esp-8h] [ebp-18h]
  int v12; // [esp+0h] [ebp-10h]
  int v13; // [esp+4h] [ebp-Ch]
  int v14; // [esp+8h] [ebp-8h]
  int v15; // [esp+Ch] [ebp-4h]
  int v16; // [esp+14h] [ebp+4h]

  v5 = result;
  if (soundon && SamplePtr[a2]) {
    v7 = 4 * result + (a2 << 6);
    if (*(int *)((char *)SampleHandleCar + v7) != -1 && !a3)
      goto LABEL_9;
    result = a2 << 6;
    v7 = (a2 << 6) + 4 * v5;
    if (*(int *)((char *)SampleHandleCar + v7) == -1) {
      if (a3) {
        HIDWORD(v11) = *(int *)((char *)SampleHandleCar + v7);
        LODWORD(v11) = a5;
        return sample2(__SPAIR64__(a2, v5), a4, a3, v11, v12, v13, v14, v15);
      }
      return result;
    }
    if (!a3) {
    LABEL_9:
      sosDIGIStopSample(DIGIHandle);
      result = *(int *)((char *)SampleHandleCar + v7);
      HandleSample[result] = -1;
      *(int *)((char *)SampleHandleCar + v7) = -1;
      return result;
    }
    if (a4 < 2048)
      a4 = 2048;
    if (a4 > 0x80000)
      a4 = 0x80000;
    v8 = a3 >> 10;
    v9 = a4 >> 10;
    v16 = a5 >> 12;
    if (v8 != lastvolume[v5]) {
      sosDIGISetSampleVolume(DIGIHandle, SampleHandleCar[16 * a2 + v5], v8 << 10, v9);
      lastvolume[v5] = v8;
    }
    if (v9 != lastpitch[v5]) {
      sosDIGISetPitch(DIGIHandle, SampleHandleCar[16 * a2 + v5], v9 << 10);
      lastpitch[v5] = v9;
    }
    v10 = v5;
    result = v16;
    if (v16 != lastpan[v10]) {
      sosDIGISetPanLocation(DIGIHandle, SampleHandleCar[16 * a2 + v10], v16 << 12);
      result = v16;
      lastpan[v10] = v16;
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void enginesound(int a1, float a2, float a3, float a4, int a5)
{/*
  int v8; // ebp
  int v9; // edx
  __int16 v10; // fps
  double v11; // st7
  _BOOL1 v12; // c0
  char v13; // c2
  _BOOL1 v14; // c3
  double v15; // st7
  int v16; // ebx
  int v17; // edx
  int v18; // eax
  int v19; // eax
  __int16 v20; // fps
  _BOOL1 v21; // c0
  char v22; // c2
  _BOOL1 v23; // c3
  int v24; // edx
  double v25; // st7
  double v26; // st7
  int v27; // eax
  int v28; // eax
  double v29; // st7
  int v30; // eax
  int v31; // edx
  int v32; // edx
  int v33; // edx
  double v34; // st7
  float v35; // eax
  int v36; // edx
  double v37; // st7
  __int64 v38; // rax
  int v39; // ebx
  double v41; // st7
  double v42; // st7
  int v43; // edx
  double v44; // st7
  int v45; // eax
  double v46; // st7
  int v47; // ecx
  int v48; // ebp
  int v49; // esi
  int v50; // edx
  int v51; // ecx
  int v52; // eax
  double v53; // st7
  float v54; // [esp+Ch] [ebp-4Ch]
  float v55; // [esp+10h] [ebp-48h]
  int v56; // [esp+14h] [ebp-44h]
  int v57; // [esp+18h] [ebp-40h]
  float v58; // [esp+20h] [ebp-38h]
  int v59; // [esp+24h] [ebp-34h]
  int v60; // [esp+24h] [ebp-34h]
  int v61; // [esp+24h] [ebp-34h]
  int v62; // [esp+28h] [ebp-30h]
  int v63; // [esp+28h] [ebp-30h]
  int v64; // [esp+28h] [ebp-30h]
  int v65; // [esp+28h] [ebp-30h]
  int v66; // [esp+2Ch] [ebp-2Ch]
  float v67; // [esp+30h] [ebp-28h]
  float v68; // [esp+34h] [ebp-24h]
  float v69; // [esp+38h] [ebp-20h]
  int v70; // [esp+3Ch] [ebp-1Ch]

  v8 = a1;
  if (soundon) {
    v55 = (a2 + sound_c_variable_39) / (sound_c_variable_39 - a3);
    v9 = 77 * a1;
    v67 = sound_c_variable_40 / (a4 * a4 + sound_c_variable_40);
    v11 = Car_variable_28[77 * a1];
    v12 = v11 < sound_c_variable_41;
    v13 = 0;
    v14 = v11 == sound_c_variable_41;
    LOWORD(a1) = v10;
    if (v11 >= sound_c_variable_41) {
      v59 = 258 * EngineVolume;
    } else {
      v15 = Car_variable_28[v9] * sound_c_variable_42 * sound_c_variable_43 * (double)EngineVolume;
      _CHP(a1, v9 * 4);
      v59 = (int)v15;
    }
    v16 = Car_variable_72[77 * v8];
    v17 = 8 * ((v16 * v59) >> 31);
    v18 = (v16 * v59 - (__CFSHL__((v16 * v59) >> 31, 3) + v17)) >> 3;
    v60 = v18;
    if (v18 > 0x7FFF)
      v60 = 0x7FFF;
    _CHP(v18, v17);
    v61 = (int)((double)v60 * v67);
    if (v61 < 256)
      v61 = 0;
    v21 = a4 < (double)sound_c_variable_44;
    v22 = 0;
    v23 = a4 == sound_c_variable_44;
    LOWORD(v19) = v20;
    if (a4 >= (double)sound_c_variable_44)
      v61 = 0;
    v24 = 77 * v8;
    v25 = Car_variable_28[77 * v8] * sound_c_variable_45 + sound_c_variable_46;
    _CHP(v19, 308 * v8);
    v26 = Car_variable_73[v24] * sound_c_variable_47 / (Car_variable_73[v24] + sound_c_variable_48) + (double)(int)v25;
    _CHP(v27, 308 * v8);
    v58 = (Car_variable_9[77 * v8] + sound_c_variable_49) * sound_c_variable_50;
    if (v58 > 1.0)
      v58 = 1.0;
    v28 = Car_variable_74[77 * v8];
    v29 = tsin[v28] * (1.0 - v58) * sound_c_variable_51 + (double)(6 * Car_variable_36[77 * v8] + (int)v26);
    _CHP(v28, v24 * 4);
    _CHP(v30, v24 * 4);
    v56 = 0;
    v31 = Car_variable_3[154 * v8];
    v57 = Car_variable_50[77 * v8];
    v66 = (int)(v29 * v55);
    if (v31 != -1 && (TrakColour_variable_1[12 * v31 + 2 * v57] & 0x2000) != 0) {
      v56 = -1;
      v68 = localdata_variable_4[32 * v31] + Car[77 * v8];
      v32 = v31 - 1;
      if (!v32)
        v32 = TRAK_LEN - 1;
      while ((TrakColour_variable_1[12 * v32 + 2 * v57] & 0x2000) != 0 && v68 < (double)sound_c_variable_52) {
        v68 = sound_c_variable_61 * localdata_variable_4[32 * v32--] + v68;
        if (!v32)
          v32 = TRAK_LEN - 1;
      }
      v33 = Car_variable_3[154 * v8] + 1;
      v69 = localdata_variable_4[32 * Car_variable_3[154 * v8]] - Car[77 * v8];
      if (v33 == TRAK_LEN)
        v33 ^= TRAK_LEN;
      while ((TrakColour_variable_1[12 * v33 + 2 * v57] & 0x2000) != 0 && v69 < (double)sound_c_variable_52) {
        v34 = sound_c_variable_61 * localdata_variable_4[32 * v33++] + v69;
        v69 = v34;
        if (v33 == TRAK_LEN)
          v33 ^= TRAK_LEN;
      }
      if (v69 >= (double)v68)
        v35 = v68;
      else
        v35 = v69;
      v54 = v35;
      if (v35 > (double)sound_c_variable_52)
        v54 = 6400.0;
    }
    v36 = 224 * v8;
    enginedelay_variable_6[224 * v8 + 7 * delaywritex] = a5;
    enginedelay[224 * v8 + 7 * delaywritex] = v66;
    enginedelay_variable_1[7 * delaywritex + v36] = v61;
    enginedelay_variable_2[7 * delaywritex + v36] = v66;
    if (v56) {
      v37 = v54 * sound_c_variable_53 * sound_c_variable_54 * (double)v61;
      _CHP(v66, v36 * 4);
      enginedelay_variable_3[7 * delaywritex + v36] = (int)v37;
    } else {
      enginedelay_variable_3[7 * delaywritex + v36] = 0;
    }
    if (Car_variable_17[77 * v8] != 3
      || (HIDWORD(v38) = Car_variable_7[154 * v8], v39 = Car_variable_15[77 * v8], HIDWORD(v38) == v39)) {
      v65 = 0;
    } else {
      LODWORD(v38) = HIDWORD(v38) - v39 + (HIDWORD(v38) - v39 < 0 ? 0x4000 : 0);
      if ((int)v38 > 0x2000)
        LODWORD(v38) = v38 - 0x4000;
      v38 = (int)v38;
      LODWORD(v38) = abs32(v38);
      if ((int)v38 >= 200) {
        v41 = (double)((int)v38 - 400) * sound_c_variable_55 * sound_c_variable_56 * sound_c_variable_57;
        _CHP(v38 - 400, HIDWORD(v38));
        v62 = (int)v41;
      } else {
        v62 = 0;
      }
      v42 = (double)v62 * Car_variable_8[77 * v8] * sound_c_variable_58;
      _CHP(308 * v8, HIDWORD(v38));
      v63 = (int)v42;
      if ((int)v42 > 0x7FFF)
        v63 = 0x7FFF;
      v43 = SFXVolume * v63 % 127;
      v64 = SFXVolume * v63 / 127;
      _CHP(v64, v43);
      v65 = (int)((double)v64 * v67);
      if (v65 < 256)
        v65 = 0;
      v44 = v55 * sound_c_variable_59;
      _CHP(308 * v8, v43);
      v46 = (*(float *)((char *)Car_variable_8 + v45) + sound_c_variable_52) * sound_c_variable_60 * (double)(int)v44;
      _CHP(v45, v43);
      v66 = (int)v46;
    }
    enginedelay_variable_4[224 * v8 + 7 * delaywritex] = v66;
    enginedelay_variable_5[224 * v8 + 7 * delaywritex] = v65;
    v47 = 5 * v8;
    v48 = v8;
    v49 = 0;
    v50 = Pending[v48];
    v51 = 8 * v47;
    if (v50 > 0) {
      do {
        v52 = SamplePending_variable_1[v51];
        v70 = v52;
        if (v52 > 0x8000)
          v70 = 0x8000;
        v53 = (double)v70 * v67;
        _CHP(v52, v50);
        if ((int)v53 >= 256) {
          v50 = (int)v53;
          pannedsample(SamplePending[v51], (int)v53, a5);
        }
        ++v49;
        v51 += 2;
      } while (v49 < Pending[v48]);
    }
    Pending[v48] = 0;
  }*/
}

//-------------------------------------------------------------------------------------------------

int startmusic(int result)
{
  return 0; /*
  int v1; // edx
  int v2; // ebx
  int v3; // edx
  int v4; // eax
  int v5; // eax

  v1 = result;
  v2 = 0;
  if (MusicCD && track_playing) {
    result = StopTrack();
  } else if (MusicCard && SongPtr) {
    stop(result, result, 0, MusicCD);
    sosMIDIUnInitSong(SongHandle);
    result = 0;
    SongPtr = 0;
  }
  if (musicon)
    result = sosMIDISetMasterVolume((unsigned __int8)MusicVolume);
  if (MusicCD)
    result = SetAudioVolume(MusicVolume);
  if (v1 >= 0) {
    v2 = -1;
    result = (nummusictracks + v1 - 1) / nummusictracks;
    v3 = (nummusictracks + v1 - 1) % nummusictracks;
  } else {
    v3 = -v1;
  }
  if (MusicCD && musicon) {
    ResetDrive();
    GetAudioInfo();
    if (cd_cheat) {
      v4 = cd_cheat;
    } else {
      if (v2) {
        PlayTrack4(CDSong[v3], v3);
      LABEL_22:
        result = frames;
        start_cd = frames;
        return result;
      }
      v4 = CDSong[v3];
    }
    PlayTrack(v4, v3, v2);
    goto LABEL_22;
  }
  if (musicon) {
    initmangle((char *)&Song + 15 * GMSong[v3]);
    v5 = loadcompactedfilepart(&musicbuffer, 1000000000);
    result = uninitmangle(v5);
    SongPtr = (int)&musicbuffer;
    if (&musicbuffer) {
      InitSong_variable_1 = __DS__;
      InitSong_variable_3 = 0;
      InitSong_variable_2 = 0;
      InitSong = (int)&musicbuffer;
      result = sosMIDIInitSong((char)&SongHandle, (unsigned __int16)__DS__);
      if (musicon) {
        if (SongPtr) {
          InitSong_variable_1 = __DS__;
          InitSong = SongPtr;
          InitSong_variable_2 = 0;
          InitSong_variable_3 = 0;
          return sosMIDIStartSong(SongHandle);
        }
      }
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int stopmusic(int a1, int a2)
{
  return 0; /*
  int result; // eax

  if (MusicCD && track_playing)
    return StopTrack();
  if (MusicCard && SongPtr) {
    if (MusicCard) {
      if (SongPtr) {
        sosMIDIStopSong(SongHandle, a2, &InitSong);
        sosMIDIResetSong();
      }
    }
    sosMIDIUnInitSong(SongHandle);
    result = 0;
    SongPtr = 0;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void load_language_map()
{
  FILE *pFile;
  int i;

  // open file
  pFile = ROLLERfopen("LANGUAGE.INI", "r");
  if (!pFile) return;

  // read number of languages into languages
  readline(pFile, "i", &languages);

  // check if languages is valid
  if (languages <= 0) {
    fclose(pFile);
    return;
  }

  // Set up pointers to global buffers
  char *szLangPtr = lang[0];
  char *szTextExtPtr = TextExt;
  char *szSampleExtPtr = SampleExt;

  // loop through each language and read settings
  for (i = 0; i < languages; i++) {
    readline(pFile, "ccc", szLangPtr, szTextExtPtr, szSampleExtPtr);

    // Move pointers forward to next slots
    szLangPtr += 32;        // Each lang entry is 32 bytes
    szTextExtPtr += 4;       // Each extension is 4 bytes
    szSampleExtPtr += 4;
  }

  // close the file
  fclose(pFile);
}

//-------------------------------------------------------------------------------------------------

void initmusic()
{
  FILE *pFile = ROLLERfopen("SOUND.INI", "r");
  if (!pFile) return;

  readline(pFile, "i", &numsamples);
  int iSongCount = 0;
  readline(pFile, "i", &iSongCount);
  readline(pFile, "i", &nummusictracks);

  // read sample filenames
  for (int i = 0; i < numsamples; i++) {
    char szBuf[20];
    readline(pFile, "c", szBuf);

    // add extension ".RAW"
    char *szEnd = &szBuf[strlen(szBuf)];
    if (szEnd) strcpy(szEnd, ".RAW");

    strncpy(Sample[i], szBuf, 15);
    Sample[i][14] = '\0';
  }

  // read song filenames
  for (int i = 0; i < iSongCount; i++) {
    char szBuf[20];
    readline(pFile, "c", szBuf);

    // add extension ".HMP"
    char *szEnd = &szBuf[strlen(szBuf)];
    if (szEnd) strcpy(szEnd, ".HMP");

    strncpy(Song[i], szBuf, 15);
    Song[i][14] = '\0';
  }

  // read GMSong/CDSong values for each track (+5 entries)
  for (int i = 0; i < nummusictracks + 5; i++) {
    readline(pFile, "ii", &GMSong[i], &CDSong[i]);
  }

  // set special track indices (stored as negative values)
  titlesong = -nummusictracks;
  optionssong = -(nummusictracks + 1);
  leaderboardsong = -(nummusictracks + 2);
  winsong = -(nummusictracks + 3);
  winchampsong = -(nummusictracks + 4);

  fclose(pFile);
}

//-------------------------------------------------------------------------------------------------

void fade_palette(int iTargetBrightness)
{
  int iOriginalTickOn = tick_on;
  int iOriginalTicks = ticks;
  uint32 uiTimerHandle = 0;

  if (iTargetBrightness == 0)
    disable_keyboard();

  if (iTargetBrightness == 32 && soundon) {
    //sosDIGISetMasterVolume(DIGIHandle, 0x7FFF);
  }

  int iCurrentBrightness = palette_brightness;

  if (iTargetBrightness == iCurrentBrightness)
    return;

  tick_on = 0;
  s7 = 0;

  if (current_mode != 0) {
    uiTimerHandle = SDL_AddTimer(70, SDLS7TimerCallback, NULL); //added by ROLLER
  }

  if (iTargetBrightness > iCurrentBrightness) {
      // FADE IN LOOP
    for (int iStep = iCurrentBrightness; iStep <= iTargetBrightness; iStep++) {
      for (int i = 0; i < 256; i++) {
        pal_addr[i].byR = (palette[i].byR * iStep) >> 5;
        pal_addr[i].byB = (palette[i].byB * iStep) >> 5;
        pal_addr[i].byG = (palette[i].byG * iStep) >> 5;
      }

      if (current_mode != 0) {
        //could also do this instead of SDL timer
        //uint32 uiStartTime = SDL_GetTicks();
        //while (SDL_GetTicks() - uiStartTime < 70) {
        //  SDL_Delay(1);
        //}
        int iPrev = s7;
        while (s7 == iPrev); // Wait for timer tick
      } else {
        //wait for retrace
        //aka VSYNC for DOS
      }

      //set dac palette
      UpdateSDL();
    }
  } else {
      // FADE OUT LOOP
    int iVolumeStep = (iTargetBrightness << 15) - iTargetBrightness;

    for (int iStep = iCurrentBrightness; iStep >= iTargetBrightness; iStep--) {
      if (iTargetBrightness == 0 && !holdmusic) {
        if (musicon) {
          //sosMIDISetMasterVolume(((MusicVolume * iStep) >> 5) & 0xFF);
        }

        if (soundon) {
          //sosDIGISetMasterVolume(DIGIHandle, (iVolumeStep >> 5));
        }

        if (MusicCD) {
          //SetAudioVolume(((MusicVolume * iStep) >> 5) & 0xFF);
        }
      }

      for (int i = 0; i < 256; i++) {
        pal_addr[i].byR = (palette[i].byR * iStep) >> 5;
        pal_addr[i].byB = (palette[i].byB * iStep) >> 5;
        pal_addr[i].byG = (palette[i].byG * iStep) >> 5;
      }

      if (current_mode != 0) {
        int iPrevS7 = s7;
        while (s7 == iPrevS7); // Wait for timer tick
      } else {
        //wait for retrace
        //aka VSYNC for DOS
      }

      //set dac palette
      UpdateSDL();

      iVolumeStep -= 0x7FFF;
    }
  }

  if (current_mode != 0) {
    SDL_RemoveTimer(uiTimerHandle); //added by ROLLER
  }

  memcpy(pal_addr, palette, 768);
  palette_brightness = iTargetBrightness;
  tick_on = iOriginalTickOn;
  ticks = iOriginalTicks;

  if (iTargetBrightness == 0)
    enable_keyboard();

  if (iTargetBrightness == 0 && !holdmusic) {
    if (MusicCD && track_playing)
      StopTrack();
    else if (MusicCard && SongPtr) {
      stop();
      //sosMIDIUnInitSong(SongHandle);
      SongPtr = 0;
    }
  }
}

//-------------------------------------------------------------------------------------------------

void set_palette(int iBrightness)
{
  if (iBrightness == palette_brightness)
    return;

  if (iBrightness < 0) iBrightness = 0;
  if (iBrightness > 31) iBrightness = 31;

  for (int i = 0; i < 256; ++i) {
    pal_addr[i].byR = (palette[i].byR * iBrightness) / 31;
    pal_addr[i].byG = (palette[i].byG * iBrightness) / 31;
    pal_addr[i].byB = (palette[i].byB * iBrightness) / 31;
  }

  // Update the SDL palette
  //SDL_Color sdl_colors[256];
  //
  //for (int i = 0; i < 256; ++i) {
  //  sdl_colors[i].r = pal_addr[i].r;
  //  sdl_colors[i].g = pal_addr[i].g;
  //  sdl_colors[i].b = pal_addr[i].b;
  //  sdl_colors[i].a = 255;
  //}
  //SDL_SetPaletteColors(sdl_palette, sdl_colors, 0, 256);

  palette_brightness = iBrightness;
}

//-------------------------------------------------------------------------------------------------

int check_joystick_usage()
{
  return 0; /*
  int result; // eax
  char v1; // dl
  char v2; // cl

  Joy1used = 0;
  Joy2used = 0;
  for (result = 0; result < 12; ++result) {
    v1 = userkey[result];
    if (v1 == (char)0x80 || v1 == -127 || (unsigned __int8)v1 >= 0x84u && (unsigned __int8)v1 <= 0x87u)
      Joy1used = -1;
    v2 = userkey[result];
    if (v2 == -126 || v2 == -125 || (unsigned __int8)v2 >= 0x88u && (unsigned __int8)v2 <= 0x8Bu)
      Joy2used = -1;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void convertname(char *szFilename)
{
  char szTemp[32];
  char *p = szTemp;
  char *s = szFilename;

  cheatsample = 0;

  // copy filename to temp buffer (word-wise copy, handling 2 bytes at a time)
  while (1) {
    *p++ = *s;
    if (*s++ == '\0') break;
    *p++ = *s;
    if (*s++ == '\0') break;
  }

  // check for cheat sample conversion
  if (cheat_samples && language == 0) {
    char *ext = strstr(szFilename, ".RAW");
    if (ext) {
      ext[1] = 'K';   // Change to ".KC"
      ext[2] = 'C';
      ext[3] = '\0';

      FILE *fp = ROLLERfopen(szFilename, "rb");
      if (fp) {
        cheatsample = -1;
        fclose(fp);
        return;
      }
    }
  }

  // language-specific sample override
  if (language != 0) {
    char *szExt = strstr(szFilename, ".RAW");
    if (szExt) {
      const char *szLangExt = (const char *)SampleExt[language];
      strcpy(szExt + 1, szLangExt);

      FILE *fp = ROLLERfopen(szFilename, "rb");
      if (fp) {
        fclose(fp);
        return;
      }
    }
  }

  // restore original filename from temp if all else fails
  s = szTemp;
  p = szFilename;
  while (1) {
    *p++ = *s;
    if (*s++ == '\0') break;
    *p++ = *s;
    if (*s++ == '\0') break;
  }
}

//-------------------------------------------------------------------------------------------------

void decode(uint8 *pData, int iLength, int iStep, int iOffset)
{
  int i; // edx
  uint8 byOriginal; // bh
  uint8 byXorValue; // bl
  int iNextOffset; // [esp+0h] [ebp-Ch]

  for (i = 0; i < iLength; *(pData - 1) = byXorValue ^ byOriginal) {
    ++i;
    byOriginal = *pData;
    iNextOffset = iOffset + iStep;
    ++pData;
    byXorValue = iOffset + iStep;
    iStep = iOffset;
    iOffset = iNextOffset;
  }
}

//-------------------------------------------------------------------------------------------------

void loadasample(int iIndex)
{
  char szFilenameBuf[32];

  // construct sample filename
  char *szSrc = Sample[iIndex];
  char *szDst = szFilenameBuf;
  while (*szSrc) {
    *szDst++ = *szSrc++;
    if (!*szSrc) break;
    *szDst++ = *szSrc++;
  }
  *szDst = '\0';

  // convert sample name to real path or cheat version
  convertname(szFilenameBuf);

  // load file into memory
  loadfile(szFilenameBuf, &SamplePtr[iIndex], &SampleLen[iIndex], 1);

  // check if cheat sample flag is set and process if needed
  if (cheatsample && SamplePtr[iIndex]) {
    uint8 *pData= SamplePtr[iIndex];
    int iLen = SampleLen[iIndex];
    uint32 uiSeed = 0x1C73;
    uint32 uiStep = 0x896;
    int i;

    for (i = 0; i < iLen; ++i) {
      uiSeed += uiStep;
      pData[i] ^= (uint8)uiSeed;
    }
  }

  // if the index is between 79 and 82 apply a second xor pass
  if (iIndex >= 79 && iIndex <= 82 && SamplePtr[iIndex]) {
    uint8 *pData = SamplePtr[iIndex];
    int iLen = SampleLen[iIndex];
    uint32 uiSeed = 0x4D;
    uint32 uiStep = 0x57;

    for (int i = 0; i < iLen; ++i) {
      uiSeed += uiStep;
      pData[i] ^= (uint8)uiSeed;
    }
  }

  // if using 50Hz timer
  if (SamplePtr[iIndex] && (cheat_mode & CHEAT_MODE_50HZ_TIMER)) {
    if (cheat_mode & CHEAT_MODE_100HZ_TIMER) { //100Hz timer
      // halve the sample length, keep only even-indexed bytes
      int iLen = SampleLen[iIndex];
      uint8 *pData = SamplePtr[iIndex];
      for (int i = 0; i < iLen; i += 2) {
        pData[i / 2] = pData[i];
      }
      SampleLen[iIndex] = iLen / 2;
    } else {
      // remove every third byte
      int iLen = SampleLen[iIndex];
      uint8 *pData = SamplePtr[iIndex];
      int iNewLen = 0;
      for (int i = 0; i < iLen; ++i) {
        if (i % 3 != 2) {
          pData[iNewLen++] = pData[i];
        }
      }
      SampleLen[iIndex] = iNewLen;
    }
  }
}

//-------------------------------------------------------------------------------------------------

void select8bitdriver()
{
  /*
  int v0; // edx

  if (SoundCard) {
    if (drivertype == 1) {
      sosTIMERRemoveEvent(TimerEventHandle, v0);
      sosDIGIUnInitDriver(DIGIHandle, 1, 1);
    }
    resetsamplearray();
    if (drivertype) {
      drivertype = 0;
      memset(&InitDriver, 0, 0x4Cu);
      InitDriver = 4096;
      InitDriver_variable_1 = -1;
      InitDriver_variable_2 = 11025;
      Hardware = SoundPort;
      Hardware_variable_1 = SoundIRQ;
      Hardware_variable_2 = SoundDMA;
      InitDriver_variable_5 = 0;
      if (sosDIGIInitDriver(
        SoundCard,
        0,
        (unsigned int)&Hardware,
        __DS__,
        (unsigned int)&InitDriver,
        (unsigned __int16)__DS__,
        (unsigned int)&DIGIHandle,
        (unsigned __int16)__DS__)) {
        sosDIGIUnInitSystem();
        SoundCard = 0;
      } else {
        sosTIMERRegisterEvent(
          0x12Cu,
          0x7FFF,
          InitDriver_variable_3,
          InitDriver_variable_4,
          (unsigned int)&TimerEventHandle,
          (unsigned __int16)__DS__);
        sosDIGISetMasterVolume(DIGIHandle, 0x7FFFu);
      }
    }
  }*/
}

//-------------------------------------------------------------------------------------------------

int resetsamplearray()
{
  return 0; /*
  int v0; // ebx
  int i; // ecx
  int v2; // edx
  int v3; // eax
  int v4; // eax
  int v5; // esi
  int j; // ecx
  int result; // eax

  v0 = numcars;
  for (i = 0; i != 896; i += 28) {
    v2 = 0;
    if (v0 > 0) {
      v3 = i;
      do {
        *(int *)((char *)enginedelay_variable_1 + v3) = -1;
        *(int *)((char *)enginedelay_variable_3 + v3) = -1;
        *(int *)((char *)enginedelay_variable_5 + v3) = -1;
        ++v2;
        v3 += 896;
      } while (v2 < v0);
    }
  }
  v4 = 2;
  HandleSample[0] = -1;
  HandleCar[0] = -1;
  HandleSample_variable_1 = -1;
  HandleCar_variable_1 = -1;
  do {
    v4 += 5;
    HandleCar_variable_2[v4] = -1;
    SamplePending_variable_3[v4] = -1;
    HandleCar_variable_3[v4] = -1;
    SamplePending_variable_4[v4] = -1;
    HandleCar_variable_4[v4] = -1;
    SamplePending_variable_5[v4] = -1;
    HandleCar_variable_5[v4] = -1;
    SamplePending_variable_6[v4] = -1;
    HandleCar_variable_6[v4] = -1;
    SamplePending_variable_7[v4] = -1;
  } while (v4 != 32);
  v5 = 64;
  for (j = 0; j < 120; ++j) {
    result = j << 6;
    do {
      result += 4;
      *(int *)((char *)&SamplePtr_variable_15 + result) = -1;
    } while (result != v5);
    v5 += 64;
  }
  numcars = v0;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void reinitmusic(int a1, int a2)
{
  int iSong; // eax

  if (musicon) {
    if (frontend_on) {
      iSong = optionssong;
    } else if (replaytype == 2) {
      iSong = titlesong;
    } else {
      iSong = TrackLoad;
    }
    startmusic(iSong);
  } else if (MusicCD && track_playing) {
    StopTrack();
  } else if (MusicCard) {
    if (SongPtr) {
      stop(a1, a2);
      //sosMIDIUnInitSong(SongHandle);
      SongPtr = 0;
    }
  }
}

//-------------------------------------------------------------------------------------------------

int waitsampledone(int result)
{
  return 0; /*
  int v1; // ebx

  if (soundon) {
    if (SamplePtr[result]) {
      v1 = result << 6;
      if (SampleHandleCar[16 * result] != -1) {
        do
          result = sosDIGISampleDone(DIGIHandle, *(int *)((char *)SampleHandleCar + v1));
        while (!result);
      }
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int getcompactedfilelength(const char *szFile)
{
  FILE *pFile; // esi
  int iLength; // [esp+0h] [ebp-14h] BYREF

  pFile = ROLLERfopen(szFile, "rb");
  fread(&iLength, 1u, 4u, pFile);
  fclose(pFile);
  return iLength;
}

//-------------------------------------------------------------------------------------------------

int initmangle(const char *szFile)
{
  unmangleinpoff = 4;
  unmanglebufpos = 4;
  unmangleoverflow = 0;
  unmanglefile = ROLLERfopen(szFile, "rb");
  fseek(unmanglefile, unmanglebufpos, 0);
  return (int)fread(unmangleinbuf, 1u, 0x400u, unmanglefile);
}

//-------------------------------------------------------------------------------------------------

int uninitmangle()
{
  return fclose(unmanglefile);
}

//-------------------------------------------------------------------------------------------------

int loadcompactedfile(const char *szFile, uint8 *pBuf)
{
  initmangle(szFile);
  uint32 uiSize = getcompactedfilelength(szFile);
  loadcompactedfilepart(pBuf, uiSize);
  return fclose(unmanglefile);
}

//-------------------------------------------------------------------------------------------------

void readmangled(uint8 *pBufRet, int iLength)
{
  int iLengthToRead; // ebp
  uint8 *pBufUnit8; // ebx
  int iOverflow; // ecx
  int iDelta; // esi

  iLengthToRead = iLength;
  pBufUnit8 = pBufRet + 40000;
  if (unmangleoverflow) {
    memcpy(pBufUnit8, pBufRet, unmangleoverflow);
    iOverflow = unmangleoverflow;
    unmangleoverflow = 0;
    pBufUnit8 += iOverflow;
    iLengthToRead = iLength - iOverflow;
  }
  if (iLengthToRead > 0) {
    loadcompactedfilepart(pBufUnit8, iLengthToRead);
    iDelta = (int)(unmangledst - pBufUnit8);
    if (unmangledst - pBufUnit8 > iLengthToRead) {
      unmangleoverflow = iDelta - iLengthToRead;
      memcpy(pBufRet, &pBufUnit8[iLengthToRead], iDelta - iLengthToRead);
    }
    memcpy(pBufRet + 20000, &pBufUnit8[iLengthToRead - 20000], 0x4E20u);
  }
}

//-------------------------------------------------------------------------------------------------

void loadcompactedfilepart(uint8 *pDest, uint32 uiDestLength)
{
  uint32 uiOutputPos = 0;

  while (uiOutputPos < uiDestLength) {
    uint8 *pByte = unmangleGet(unmangleinpoff, 1);
    uint8 b = *pByte;
    unmangleinpoff++;

    if (b <= 0x3F) {
        // Literal copy
      uint32 uiCount = b;
      if (unmangleinpoff + uiCount > (uint32)unmangleinpoff + 0x400 || uiOutputPos + uiCount > uiDestLength)
        break;
      uint8 *pData = unmangleGet(unmangleinpoff, uiCount);
      memcpy(&pDest[uiOutputPos], pData, uiCount);
      unmangleinpoff += uiCount;
      uiOutputPos += uiCount;
    } else if (b <= 0x4F) {
        // Linear extrapolation (bytes)
      uint32 uiCount = (b & 0x0F) + 3;
      if (uiOutputPos < 2 || uiOutputPos + uiCount > uiDestLength)
        break;
      int iDelta = pDest[uiOutputPos - 1] - pDest[uiOutputPos - 2];
      for (uint32 i = 0; i < uiCount; ++i) {
        pDest[uiOutputPos] = (uint8)((pDest[uiOutputPos - 1] + iDelta) & 0xFF);
        uiOutputPos++;
      }
    } else if (b <= 0x5F) {
        // Linear extrapolation (words)
      uint32 uiCount = (b & 0x0F) + 2;
      if (uiOutputPos < 4 || uiOutputPos + uiCount * 2 > uiDestLength)
        break;
      int16 nPrev = (int16)(pDest[uiOutputPos - 2] | (pDest[uiOutputPos - 1] << 8));
      int16 nPrev2 = (int16)(pDest[uiOutputPos - 4] | (pDest[uiOutputPos - 3] << 8));
      int16 nDelta = nPrev - nPrev2;
      for (uint32 i = 0; i < uiCount; ++i) {
        int16 nNewVal = nPrev + nDelta;
        pDest[uiOutputPos++] = nNewVal & 0xFF;
        pDest[uiOutputPos++] = (nNewVal >> 8) & 0xFF;
        nPrev = nNewVal;
      }
    } else if (b <= 0x6F) {
        // Repeat last byte
      uint32 uiCount = (b & 0x0F) + 3;
      if (uiOutputPos == 0 || uiOutputPos + uiCount > uiDestLength)
        break;
      uint8 val = pDest[uiOutputPos - 1];
      memset(&pDest[uiOutputPos], val, uiCount);
      uiOutputPos += uiCount;
    } else if (b <= 0x7F) {
        // Repeat last word
      uint32 uiCount = (b & 0x0F) + 2;
      if (uiOutputPos < 2 || uiOutputPos + uiCount * 2 > uiDestLength)
        break;
      for (uint32 i = 0; i < uiCount; ++i) {
        pDest[uiOutputPos] = pDest[uiOutputPos - 2];
        pDest[uiOutputPos + 1] = pDest[uiOutputPos - 1];
        uiOutputPos += 2;
      }
    } else if (b <= 0xBF) {
        // Copy 3 bytes from offset
      int iOffset = (b & 0x3F) + 3;
      if ((int)uiOutputPos - iOffset < 0 || uiOutputPos + 3 > uiDestLength)
        break;
      for (int i = 0; i < 3; ++i)
        pDest[uiOutputPos++] = pDest[uiOutputPos - iOffset];
    } else if (b <= 0xDF) {
        // Copy from offset and length from next byte
      uint8 *pLen = unmangleGet(unmangleinpoff, 1);
      uint8 lenByte = *pLen;
      unmangleinpoff++;

      int iOffset = (((b & 0x03) << 8) | lenByte) + 3;
      int length = ((b >> 2) & 0x07) + 4;
      if ((int)uiOutputPos - iOffset < 0 || uiOutputPos + length > uiDestLength)
        break;

      for (int i = 0; i < length; ++i)
        pDest[uiOutputPos++] = pDest[uiOutputPos - iOffset];
    } else {
        // Copy from offset and length from next 2 bytes
      uint8 *pBytes = unmangleGet(unmangleinpoff, 2);
      uint8 offsetLo = pBytes[0];
      uint8 lengthByte = pBytes[1];
      unmangleinpoff += 2;

      int iOffset = (((b & 0x1F) << 8) | offsetLo) + 3;
      int iLength = lengthByte + 5;
      if ((int)uiOutputPos - iOffset < 0 || uiOutputPos + iLength > uiDestLength)
        break;

      for (int i = 0; i < iLength; ++i)
        pDest[uiOutputPos++] = pDest[uiOutputPos - iOffset];
    }
  }
}

//-------------------------------------------------------------------------------------------------

uint8 *unmangleGet(unsigned int uiPos, unsigned int uiLookahead)
{
  // if what we want to read is not currently in the
  // buffer load it into the buffer from the file
  if (uiPos < (uint32)unmanglebufpos || uiPos + uiLookahead >(uint32)unmanglebufpos + 1024) {
    unmanglebufpos = uiPos;
    fseek(unmanglefile, uiPos, 0);
    fread(unmangleinbuf, 1u, 0x400u, unmanglefile);
  }
  return &unmangleinbuf[uiPos - (uint32)unmanglebufpos];// return new pos
}

//-------------------------------------------------------------------------------------------------

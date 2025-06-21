#include "roller.h"
#include "3d.h"
#include "sound.h"
#include "frontend.h"
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <SDL3_image/SDL_image.h>
#include <fcntl.h>
#ifdef IS_WINDOWS
#include <io.h>
#define open _open
#define close _close
#else
#include <inttypes.h>
#include <dirent.h>
#include <sys/stat.h>
#include <linux/cdrom.h>
#include <unistd.h>
#include <sys/ioctl.h>
#define O_BINARY 0 //linux does not differentiate between text and binary
#endif

//-------------------------------------------------------------------------------------------------

static SDL_Window *s_pWindow = NULL;
static SDL_Renderer *s_pRenderer = NULL;
static SDL_Texture *s_pWindowTexture = NULL;
SDL_Gamepad *g_pController1 = NULL;
SDL_Gamepad *g_pController2 = NULL;
static uint8 *s_pRGBBuffer = NULL;
uint64 ullTargetSDLTicksNS = 0;
uint64 ullLastSDLTicksNS = 0;
uint64 ullCurrSDLTicksNS = 0;

//-------------------------------------------------------------------------------------------------

void ConvertIndexedToRGB(const uint8 *pIndexed, const tColor *pPalette, uint8 *pRGB, int width, int height)
{
  if (!pIndexed || !pPalette || !pRGB)
    return;

  for (int i = 0; i < width * height; ++i) {
    const tColor *c = &pPalette[pIndexed[i]];
    pRGB[i * 3 + 0] = (c->byR * 255) / 63;
    pRGB[i * 3 + 1] = (c->byG * 255) / 63;
    pRGB[i * 3 + 2] = (c->byB * 255) / 63;
  }
}

//-------------------------------------------------------------------------------------------------

void UpdateSDLWindow()
{
  ConvertIndexedToRGB(scrbuf, pal_addr, s_pRGBBuffer, 640, 400);

  SDL_UpdateTexture(s_pWindowTexture, NULL, s_pRGBBuffer, 640 * 3);

  // Get current window size
  int iWindowWidth, iWindowHeight;
  SDL_GetCurrentRenderOutputSize(s_pRenderer, &iWindowWidth, &iWindowHeight);

  // Get original texture size
  int iTexWidth = 640;
  int iTexHeight = 400;

  // Calculate aspect ratio-preserving destination rectangle
  SDL_FRect dst;
  float fWindowAspect = (float)iWindowWidth / (float)iWindowHeight;
  float fTextureAspect = (float)iTexWidth / (float)iTexHeight;

  if (fWindowAspect > fTextureAspect) {
      // Window is wider than texture
    dst.h = (float)iWindowHeight;
    dst.w = fTextureAspect * iWindowHeight;
    dst.x = (iWindowWidth - dst.w) / 2;
    dst.y = 0;
  } else {
      // Window is taller than texture
    dst.w = (float)iWindowWidth;
    dst.h = iWindowWidth / fTextureAspect;
    dst.x = 0;
    dst.y = (iWindowHeight - dst.h) / 2;
  }

  SDL_RenderClear(s_pRenderer);
  SDL_RenderTexture(s_pRenderer, s_pWindowTexture, NULL, &dst);
  SDL_RenderPresent(s_pRenderer);
}

//-------------------------------------------------------------------------------------------------

void ToggleFullscreen()
{
  static bool s_bIsFullscreen = false;
  s_bIsFullscreen = !s_bIsFullscreen;
  SDL_SetWindowFullscreen(s_pWindow, s_bIsFullscreen ? SDL_WINDOW_FULLSCREEN : 0);
}

//-------------------------------------------------------------------------------------------------

int InitSDL()
{
  if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!SDL_CreateWindowAndRenderer("ROLLER", 640, 400, SDL_WINDOW_RESIZABLE, &s_pWindow, &s_pRenderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  s_pWindowTexture = SDL_CreateTexture(s_pRenderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, 640, 400);
  SDL_SetTextureScaleMode(s_pWindowTexture, SDL_SCALEMODE_NEAREST);
  s_pRGBBuffer = malloc(640 * 400 * 3);
  SDL_Surface *pIcon = IMG_Load("roller.ico");
  SDL_SetWindowIcon(s_pWindow, pIcon);

  SDL_InitSubSystem(SDL_INIT_GAMEPAD);

  // Open game controllers
  int iCount;
  SDL_GetGamepads(&iCount);
  if (!g_pController1 && iCount > 0) {
    g_pController1 = SDL_OpenGamepad(0);
  }
  if (!g_pController2 && iCount > 1) {
    g_pController2 = SDL_OpenGamepad(1);
  }

  return SDL_APP_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

void ShutdownSDL()
{
  if (g_pController1) SDL_CloseGamepad(g_pController1);
  if (g_pController2) SDL_CloseGamepad(g_pController2);
  SDL_QuitSubSystem(SDL_INIT_GAMEPAD);

  SDL_DestroyRenderer(s_pRenderer);
  SDL_DestroyWindow(s_pWindow);
  SDL_DestroyTexture(s_pWindowTexture);
  free(s_pRGBBuffer);
}

//-------------------------------------------------------------------------------------------------

void UpdateSDL()
{
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_EVENT_QUIT:
        quit_game = 1;
        doexit();
        break;
      case SDL_EVENT_KEY_DOWN:
        if (e.key.key == SDLK_ESCAPE) {
          quit_game = 1;
        } else if (e.key.key == SDLK_SPACE) {
          //PlayAudioSampleWait(SOUND_SAMPLE_FATAL); // Test play FATAL.RAW sample, requires 'config.ini' to select correct language file.
          PlayAudioSampleWait(SOUND_SAMPLE_DRIVERS);
          PlayAudioSampleWait(SOUND_SAMPLE_ENGINES);
          PlayAudioSampleWait(SOUND_SAMPLE_GO);
        } else if (e.key.key == SDLK_F11) {
          ToggleFullscreen();
        } else if (e.key.key == SDLK_RETURN) {
          SDL_Keymod mod = SDL_GetModState();
          if (mod & (SDL_KMOD_LALT | SDL_KMOD_RALT)) {
            ToggleFullscreen();
          }
        }
        break;
    }
  }
  UpdateSDLWindow();
}

//-------------------------------------------------------------------------------------------------
#define NUM_DIGI_STREAMS 32
SDL_AudioStream *digi_stream[NUM_DIGI_STREAMS];

int DIGISampleStart(tSampleData *data)
{
  int index = -1;
  for (int i = 0; i < NUM_DIGI_STREAMS; ++i) {
    if (!digi_stream[i] || DIGISampleDone(i)) {
      index = i;
      break;
    }
  }
  if (index < 0) {
    SDL_Log("No available audio stream slots for digital sample.");
    return index; // No available stream slots
  }

  float volume = (float)data->iVolume / 0x7FFF; // Convert volume to [0.0, 1.0] range
  // show data info
  SDL_Log("ROLLER_DIGIStartSample: %i, length: %i, offset: %i, volume: %f, pitch: %i, pan: %i", data->iSampleIndex, data->iLength, data->iByteOffset, volume, data->iPitch, data->iPan);

  if (!digi_stream[index]) {
    SDL_AudioSpec spec;
    spec.channels = 1; // Mono
    spec.freq = 11025; // Sample rate
    spec.format = SDL_AUDIO_U8; // 8-bit unsigned audio
    SDL_Log("ROLLER_DIGIStartSample: channels: %i, freq: %i, format: %i", spec.channels, spec.freq, spec.format);
    digi_stream[index] = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
    if (!digi_stream[index]) {
      SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
      return -1;
    }
  }

  SDL_AudioDeviceID device = SDL_GetAudioStreamDevice(digi_stream[index]);
  SDL_Log("ROLLER_DIGIStartSample: device: %u", device);

  // Set pitch in the stream
  SDL_SetAudioStreamFrequencyRatio(digi_stream[index], 1.0); // pitch

  // Set the gain for the audio stream
  SDL_SetAudioStreamGain(digi_stream[index], volume); 

  // Put audio data into the stream
  SDL_PutAudioStreamData(digi_stream[index], ((Uint8 *)data->pSample), data->iLength);
  SDL_ResumeAudioStreamDevice(digi_stream[index]);

  SDL_Log("ROLLER_DIGIStartSample: index: %d", index);
  return index;
}

/// <summary>
/// Check if a digital sample is done playing.
/// </summary>
/// <param name="index"></param>
bool DIGISampleDone(int index)
{
  return DIGISampleAvailable(index) == 0;
}

int DIGISampleAvailable(int index)
{
  if (index < 0 || index >= NUM_DIGI_STREAMS) {
    return 0;
  }
  if (digi_stream[index]) {
    return SDL_GetAudioStreamAvailable(digi_stream[index]);
  }
  return 0;
}

void DIGISampleClear(int index)
{
  if (index < 0 || index >= NUM_DIGI_STREAMS) {
    SDL_Log("Invalid stream index: %d", index);
    return;
  }

  if (digi_stream[index]) {
    SDL_PauseAudioStreamDevice(digi_stream[index]);
    SDL_ClearAudioStream(digi_stream[index]);
    digi_stream[index] = NULL;
  }
}

void PlayAudioSampleWait(int iIndex)
{
  if (iIndex >= 120) return;
  SDL_Log("Play Sample[%i]: %s", iIndex, Sample[iIndex]);
  loadasample(iIndex);
  PlayAudioDataWait(SamplePtr[iIndex], SampleLen[iIndex]);
}

void PlayAudioDataWait(Uint8 *buffer, Uint32 length)
{
  // https://wiki.libsdl.org/SDL3/QuickReference
  SDL_AudioSpec wav_spec;
  wav_spec.channels = 1; // Stereo
  wav_spec.freq = 11025; // Sample rate
  wav_spec.format = SDL_AUDIO_U8; // 8-bit unsigned audio

  SDL_AudioStream *stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &wav_spec, NULL, NULL);
  if (!stream) {
    SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
    return;
  }

  float volume = 0.5f;
  SDL_SetAudioStreamGain(stream, volume); // Set the gain for the audio stream
  SDL_PutAudioStreamData(stream, buffer, length);
  SDL_ResumeAudioStreamDevice(stream);

  // wait from the audio stream to finish playing
  while (SDL_GetAudioStreamAvailable(stream) > 0) {
    SDL_Delay(10);
  }

  SDL_ClearAudioStream(stream);
}

//-------------------------------------------------------------------------------------------------

FILE *ROLLERfopen(const char *szFile, const char *szMode)
{
  FILE *pFile = fopen(szFile, szMode);
  if (pFile) return pFile;

  char szUpper[260] = { 0 };
  char szLower[260] = { 0 };
  int iLength = (int)strlen(szFile);

  for (int i = 0; i < iLength && i < sizeof(szUpper); ++i) {
    szUpper[i] = toupper(szFile[i]);
    szLower[i] = tolower(szFile[i]);
  }

  pFile = fopen(szUpper, szMode);
  if (pFile) return pFile;

  return fopen(szLower, szMode);
}

//-------------------------------------------------------------------------------------------------

int ROLLERopen(const char *szFile, int iOpenFlags)
{
  int iHandle = open(szFile, iOpenFlags);
  if (iHandle != -1) return iHandle;

  char szUpper[260] = { 0 };
  char szLower[260] = { 0 };
  int iLength = (int)strlen(szFile);

  for (int i = 0; i < iLength && i < sizeof(szUpper); ++i) {
    szUpper[i] = toupper(szFile[i]);
    szLower[i] = tolower(szFile[i]);
  }

  iHandle = open(szUpper, iOpenFlags);
  if (iHandle != -1) return iHandle;

  return open(szLower, iOpenFlags);
}

//-------------------------------------------------------------------------------------------------

uint32 ROLLERAddTimer(Uint32 uiFrequencyHz, SDL_TimerCallback callback, void *userdata)
{
  ullTargetSDLTicksNS = 1000000000 / uiFrequencyHz;
  ullLastSDLTicksNS = SDL_GetTicksNS();
  return SDL_AddTimer(HZ_TO_MS(uiFrequencyHz), callback, userdata); //NOTE: this may be too fast since we are rounding down, ex 36Hz = 27.777777ms instead of 27ms
}

//-------------------------------------------------------------------------------------------------

uint32 SDLTickTimerCallback(void *userdata, SDL_TimerID timerID, Uint32 interval)
{
  tickhandler(0, 0, 0, 0);
  ++ticks; //TODO remove
  ++frames; //TODO remove

  ullCurrSDLTicksNS = SDL_GetTicksNS();
  int64 llNSSinceLast = (int64)ullCurrSDLTicksNS - (int64)ullLastSDLTicksNS;
  int64 llDelta = llNSSinceLast - (int64)ullTargetSDLTicksNS;
  if (llDelta < 0)
    llDelta = 0;
  ullLastSDLTicksNS = ullCurrSDLTicksNS;

  return (uint32)((ullTargetSDLTicksNS - llDelta) / 1000000);
}

//-------------------------------------------------------------------------------------------------

uint32 SDLS7TimerCallback(void *userdata, SDL_TimerID timerID, Uint32 interval)
{
  ++s7;

  ullCurrSDLTicksNS = SDL_GetTicksNS();
  int64 llNSSinceLast = (int64)ullCurrSDLTicksNS - (int64)ullLastSDLTicksNS;
  int64 llDelta = llNSSinceLast - (int64)ullTargetSDLTicksNS;
  if (llDelta < 0)
    llDelta = 0;
  ullLastSDLTicksNS = ullCurrSDLTicksNS;

  return (uint32)((ullTargetSDLTicksNS - llDelta) / 1000000);
}

//-------------------------------------------------------------------------------------------------

int IsCDROMDevice(const char *szPath)
{
#ifdef IS_WINDOWS
  assert(0);
  return 0;
#else
  int fd = open(szPath, O_RDONLY | O_NONBLOCK);
  if (fd < 0)
    return 0;

  int result = ioctl(fd, CDROM_GET_CAPABILITY, 0);
  close(fd);
  return (result != -1);
#endif
}

//-------------------------------------------------------------------------------------------------

int GetAxisValue(SDL_Gamepad *pController, SDL_GamepadAxis axis)
{
  if (!pController || !SDL_GamepadHasAxis(pController, axis)) {
    return 0;
  }
  // Convert from [-32768, 32767] to [0, 10000]
  const int value = SDL_GetGamepadAxis(pController, axis);
  return ((value + 32768) * 10000) / 65536;
}

//-------------------------------------------------------------------------------------------------

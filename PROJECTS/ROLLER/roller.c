#include "roller.h"
#include "3d.h"
#include "sound.h"
#include "frontend.h"
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#ifndef IS_WINDOWS
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/cdrom.h>
#include <unistd.h>
#include <sys/ioctl.h>
#endif
//-------------------------------------------------------------------------------------------------

static SDL_Window *s_pWindow = NULL;
static SDL_Renderer *s_pRenderer = NULL;
static SDL_Texture *s_pWindowTexture = NULL;
static uint8 *s_pRGBBuffer = NULL;

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
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)) {
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
  return SDL_APP_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

void ShutdownSDL()
{
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

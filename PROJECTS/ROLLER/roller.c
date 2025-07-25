#include "roller.h"
#include "3d.h"
#include "sound.h"
#include "frontend.h"
#include "func2.h"
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <SDL3_image/SDL_image.h>
#include <wildmidi_lib.h>
#include <fcntl.h>
#ifdef IS_WINDOWS
#include <io.h>
#include <direct.h>
#define chdir _chdir
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

#define MAX_TIMERS 16

//-------------------------------------------------------------------------------------------------

typedef struct
{
  uint32 uiHandle;
  uint64 ullTargetSDLTicksNS;
  uint64 ullLastSDLTicksNS;
  uint64 ullCurrSDLTicksNS;
} tTimerData;

//-------------------------------------------------------------------------------------------------

static SDL_Window *s_pWindow = NULL;
static SDL_Renderer *s_pRenderer = NULL;
static SDL_Texture *s_pWindowTexture = NULL;
static SDL_Texture *s_pDebugTexture = NULL;
SDL_Gamepad *g_pController1 = NULL;
SDL_Gamepad *g_pController2 = NULL;
bool g_bPaletteSet = false;
uint8 testbuf[4096];
static uint8 *s_pRGBBuffer = NULL;
static uint8 *s_pDebugBuffer = NULL;

SDL_Mutex *g_pTimerMutex = NULL;
tTimerData timerDataAy[MAX_TIMERS] = { 0 };

// Scancode translation table (SDL scancode -> PC set1 scancode)
uint8 sdl_to_set1[] = {
    [SDL_SCANCODE_ESCAPE] = 0x01,
    [SDL_SCANCODE_1] = 0x02,
    [SDL_SCANCODE_2] = 0x03,
    [SDL_SCANCODE_3] = 0x04,
    [SDL_SCANCODE_4] = 0x05,
    [SDL_SCANCODE_5] = 0x06,
    [SDL_SCANCODE_6] = 0x07,
    [SDL_SCANCODE_7] = 0x08,
    [SDL_SCANCODE_8] = 0x09,
    [SDL_SCANCODE_9] = 0x0A,
    [SDL_SCANCODE_0] = 0x0B,
    [SDL_SCANCODE_MINUS] = 0x0C,
    [SDL_SCANCODE_EQUALS] = 0x0D,
    [SDL_SCANCODE_BACKSPACE] = 0x0E,
    [SDL_SCANCODE_TAB] = 0x0F,
    [SDL_SCANCODE_Q] = 0x10,
    [SDL_SCANCODE_W] = 0x11,
    [SDL_SCANCODE_E] = 0x12,
    [SDL_SCANCODE_R] = 0x13,
    [SDL_SCANCODE_T] = 0x14,
    [SDL_SCANCODE_Y] = 0x15,
    [SDL_SCANCODE_U] = 0x16,
    [SDL_SCANCODE_I] = 0x17,
    [SDL_SCANCODE_O] = 0x18,
    [SDL_SCANCODE_P] = 0x19,
    [SDL_SCANCODE_LEFTBRACKET] = 0x1A,
    [SDL_SCANCODE_RIGHTBRACKET] = 0x1B,
    [SDL_SCANCODE_RETURN] = 0x1C,
    [SDL_SCANCODE_LCTRL] = 0x1D,
    [SDL_SCANCODE_A] = 0x1E,
    [SDL_SCANCODE_S] = 0x1F,
    [SDL_SCANCODE_D] = 0x20,
    [SDL_SCANCODE_F] = 0x21,
    [SDL_SCANCODE_G] = 0x22,
    [SDL_SCANCODE_H] = 0x23,
    [SDL_SCANCODE_J] = 0x24,
    [SDL_SCANCODE_K] = 0x25,
    [SDL_SCANCODE_L] = 0x26,
    [SDL_SCANCODE_SEMICOLON] = 0x27,
    [SDL_SCANCODE_APOSTROPHE] = 0x28,
    [SDL_SCANCODE_GRAVE] = 0x29,
    [SDL_SCANCODE_LSHIFT] = 0x2A,
    [SDL_SCANCODE_BACKSLASH] = 0x2B,
    [SDL_SCANCODE_Z] = 0x2C,
    [SDL_SCANCODE_X] = 0x2D,
    [SDL_SCANCODE_C] = 0x2E,
    [SDL_SCANCODE_V] = 0x2F,
    [SDL_SCANCODE_B] = 0x30,
    [SDL_SCANCODE_N] = 0x31,
    [SDL_SCANCODE_M] = 0x32,
    [SDL_SCANCODE_COMMA] = 0x33,
    [SDL_SCANCODE_PERIOD] = 0x34,
    [SDL_SCANCODE_SLASH] = 0x35,
    [SDL_SCANCODE_RSHIFT] = 0x36,
    [SDL_SCANCODE_KP_MULTIPLY] = 0x37,
    [SDL_SCANCODE_LALT] = 0x38,
    [SDL_SCANCODE_SPACE] = 0x39,
    [SDL_SCANCODE_CAPSLOCK] = 0x3A,
    [SDL_SCANCODE_F1] = 0x3B,
    [SDL_SCANCODE_F2] = 0x3C,
    [SDL_SCANCODE_F3] = 0x3D,
    [SDL_SCANCODE_F4] = 0x3E,
    [SDL_SCANCODE_F5] = 0x3F,
    [SDL_SCANCODE_F6] = 0x40,
    [SDL_SCANCODE_F7] = 0x41,
    [SDL_SCANCODE_F8] = 0x42,
    [SDL_SCANCODE_F9] = 0x43,
    [SDL_SCANCODE_F10] = 0x44,
    [SDL_SCANCODE_NUMLOCKCLEAR] = 0x45,
    [SDL_SCANCODE_SCROLLLOCK] = 0x46,
    [SDL_SCANCODE_KP_7] = 0x47,
    [SDL_SCANCODE_KP_8] = 0x48,
    [SDL_SCANCODE_KP_9] = 0x49,
    [SDL_SCANCODE_KP_MINUS] = 0x4A,
    [SDL_SCANCODE_KP_4] = 0x4B,
    [SDL_SCANCODE_KP_5] = 0x4C,
    [SDL_SCANCODE_KP_6] = 0x4D,
    [SDL_SCANCODE_KP_PLUS] = 0x4E,
    [SDL_SCANCODE_KP_1] = 0x4F,
    [SDL_SCANCODE_KP_2] = 0x50,
    [SDL_SCANCODE_KP_3] = 0x51,
    [SDL_SCANCODE_KP_0] = 0x52,
    [SDL_SCANCODE_KP_PERIOD] = 0x53,
    [SDL_SCANCODE_RIGHT] = 0x4D,
    [SDL_SCANCODE_LEFT] = 0x4B,
    [SDL_SCANCODE_DOWN] = 0x50,
    [SDL_SCANCODE_UP] = 0x48,
};

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
  if (!g_bPaletteSet)
    return;

  ConvertIndexedToRGB(scrbuf, pal_addr, s_pRGBBuffer, 640, 400);
  ConvertIndexedToRGB(testbuf, pal_addr, s_pDebugBuffer, 64, 64);

  SDL_UpdateTexture(s_pWindowTexture, NULL, s_pRGBBuffer, 640 * 3);
  SDL_UpdateTexture(s_pDebugTexture, NULL, s_pDebugBuffer, 64 * 3);

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

  //SDL_FRect debugRect;
  //debugRect.h = 64;
  //debugRect.w = 64;
  //debugRect.x = 0;
  //debugRect.y = 0;
  //SDL_RenderTexture(s_pRenderer, s_pDebugTexture, NULL, &debugRect);

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

  // Change to the base path of the application
  const char *home_dir = SDL_GetBasePath();
  if (home_dir) {
    chdir(home_dir);
    SDL_free((void *)home_dir);
  }

  // check if the ./FATDATA/FATAL.INI to ensure the game can run
  if (!ROLLERfexists("./FATDATA/FATAL.INI")) {
    ErrorBoxExit("The folder FATDATA does not exist.\nROLLER requires the FATDATA folder assets from a retail copy of the game.");
  }

  g_pTimerMutex = SDL_CreateMutex();

  if (!SDL_CreateWindowAndRenderer("ROLLER", 640, 400, SDL_WINDOW_RESIZABLE, &s_pWindow, &s_pRenderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  s_pWindowTexture = SDL_CreateTexture(s_pRenderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, 640, 400);
  SDL_SetTextureScaleMode(s_pWindowTexture, SDL_SCALEMODE_NEAREST);
  s_pDebugTexture = SDL_CreateTexture(s_pRenderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, 64, 64);
  SDL_SetTextureScaleMode(s_pDebugTexture, SDL_SCALEMODE_NEAREST);
  s_pRGBBuffer = malloc(640 * 400 * 3);
  s_pDebugBuffer = malloc(64 * 64 * 3);
  SDL_Surface *pIcon = IMG_Load("roller.ico");
  SDL_SetWindowIcon(s_pWindow, pIcon);

  // Move the window to the display where the mouse is currently located
  float mouseX, mouseY;
  SDL_GetGlobalMouseState(&mouseX, &mouseY);
  int displayIndex = SDL_GetDisplayForPoint(&(SDL_Point) { (int)mouseX, (int)mouseY });
  int sdl_window_centered = SDL_WINDOWPOS_CENTERED_DISPLAY(displayIndex);
  SDL_SetWindowPosition(s_pWindow, sdl_window_centered, sdl_window_centered);

  // Initialize game controllers
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

  // Initialize MIDI with WildMidi
  if (!MIDI_Init("./midi/wildmidi.cfg")) {
    SDL_Log("Failed to initialize WildMidi. Please check your configuration file ./midi/wildmidi.cfg.");
  }

  return SDL_APP_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

void ShutdownSDL()
{
  MIDI_Shutdown();

  if (g_pController1) SDL_CloseGamepad(g_pController1);
  if (g_pController2) SDL_CloseGamepad(g_pController2);
  SDL_QuitSubSystem(SDL_INIT_GAMEPAD);

  SDL_DestroyRenderer(s_pRenderer);
  SDL_DestroyWindow(s_pWindow);
  SDL_DestroyTexture(s_pWindowTexture);
  SDL_DestroyTexture(s_pDebugTexture);

  free(s_pRGBBuffer);
  free(s_pDebugBuffer);
}

uint8 songId = 4;
void playMusic()
{
  MIDIDigi_ClearBuffer();
  MIDISetMasterVolume(127);
  uint8 *songBuffer;
  uint32 songLen;
  SDL_Log("Song[%i]: %s", songId, Song[songId]);
  loadfile((const char *)&Song[songId], (void *)&songBuffer, &songLen, 0);
  MIDIDigi_PlayBuffer(songBuffer, songLen);
  free(songBuffer);
  songId = (songId + 1) % 9;
}

//-------------------------------------------------------------------------------------------------

bool debugEnable = false;

void UpdateDebugLoop()
{
  if (debugEnable) {
    /*blankpal();
    setpal("frontend.pal");*/
    //copy_screens();

    //void *front_vga = load_picture("trkname.bm");
    //display_block(scrbuf, (tBlockHeader *)front_vga, 0, 190, 356 - 100, 0);
    //copypic(scrbuf, (uint8 *)screen);
    //void *front_vga_frontend = load_picture("frontend.bm");
    //display_picture(scrbuf, front_vga_frontend);

    void *front_vga_font1 = load_picture("font1.bm");
    void *front_vga_font2 = load_picture("font2.bm");
    void *front_vga_font3 = load_picture("font3.bm");
    void *front_vga_font4 = load_picture("font4.bm");

    void *front_vga_font = front_vga_font1;
    void *font_ascii = &font1_ascii;
    void *font_offsets = &font1_offsets;

    char buffer[256] = { 0 };
    char text[32] = { 0 };
    int value = 0;
    int font = 0;

    char szInGameEng[] = "ingame.eng";
    char szSelectEng[] = "select.eng";
    char szConfigEng[] = "config.eng";
    load_language_file(szInGameEng, 1);
    //load_language_file("ingame.eng", 1);

    int font3_offsets[72] =
    {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      -1, -6, 0, -6, 0, -6, -6, -6, -6, -6, -7, 0,
      0, -6, -6, -6, -6, -6, -6, -6, -6, 0, -6, -6,
      -6, -6, -6, -6, 0, -6, -6, -6, -6, -6, 0, 0,
    };

    unsigned char  object_3_variable_1648[] = { // Font3
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0x24, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1A, 0x1B,
0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x01, 0x02, 0x03, 0x04,
0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
0x19, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x01, 0x02,
0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C,
0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
0x17, 0x18, 0x19, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x30, 0xFF,
0xFF, 0x2B, 0x2D, 0x2A, 0x2C, 0xFF, 0x33, 0x34, 0x32, 0x38,
0x37, 0x35, 0x2D, 0x2E, 0x31, 0x2F, 0x2F, 0x3D, 0x3F, 0x3C,
0x43, 0x42, 0x27, 0x3E, 0x44, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x29, 0x36, 0x3B, 0x41, 0x3A, 0x3A, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0x29, 0x2A, 0x2B, 0x2C, 0x46, 0xFF, 0xFF, 0x30,
0x31, 0x32, 0x33, 0xFF, 0xFF, 0x36, 0xFF, 0xFF, 0xFF, 0x3A,
0xFF, 0x3C, 0xFF, 0x3E, 0xFF, 0xFF, 0xFF, 0x41, 0x42, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x47, 0xFF, 0xFF, 0xFF, 0xFF,
0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x36, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    };

    while (debugEnable) {

      uint8 size = 24; // Font size

      if (value < 0) value = 0;
      if (font < 0) font = 0;
      if (font > 3) font = 3;

      // Set font
      if (font == 0) {
        front_vga_font = front_vga_font1;
        font_ascii = &font1_ascii;
        font_offsets = &font1_offsets;
      } else if (font == 1) {
        front_vga_font = front_vga_font2;
        font_ascii = &font2_ascii;
        font_offsets = &font2_offsets;
      } else if (font == 2) {
        front_vga_font = front_vga_font3;
        font_ascii = &object_3_variable_1648;
        font_offsets = &font3_offsets;
        size = 40;
      } else {
        front_vga_font = front_vga_font4;
        font_ascii = &font4_ascii;
        font_offsets = &font4_offsets;
        size = 40;
      }

      if (value < 10) {
        strcpy(text, szInGameEng);
        load_language_file(szInGameEng, 1);
      } else if (value < 20) {
        strcpy(text, szSelectEng);
        load_language_file(szSelectEng, 1);
      } else if (value < 30) {
        strcpy(text, szConfigEng);
        load_language_file(szConfigEng, 1);
      }

      // clear screen - set scrbuf to 0 - black
      memset(scrbuf, 0, SVGA_ON ? 256000 : 64000);

      /*int tick = (SDL_GetTicks() / 10) % 360;
      front_text((tBlockHeader *)front_vga_font, "EDITOR", font_ascii, font_offsets, 190, tick, 0x8Fu, 0);*/

      uint8 color_white = 0x8Fu;
      uint8 color_red = 0xE7u;

      sprintf(buffer, "%s - %i-%i", text, value, font);
      front_text((tBlockHeader *)front_vga_font, buffer, font_ascii, font_offsets, 640 - size / 2, size / 2, color_white, 2);

      if (value == 0)
        for (size_t j = 0; j < 8; j++) {
          for (size_t i = 0; i < 32; i++) {
            buffer[i] = (char)(i + 32 * j);
          }
          buffer[32] = '\0';
          front_text((tBlockHeader *)front_vga_font, buffer, font_ascii, font_offsets, 640 - size / 2, size / 2 + size * (j + 1), color_white, 2);
        }


      /*for (size_t i = 0; i < 16; i++) {
        int index = (i * 64) + (value * 64 * 16);
        if (language_buffer[index] != '\0')
          front_text((tBlockHeader *)front_vga_font1, &language_buffer[index], font2_ascii, font2_offsets, 0, 0 + i * 24 + 12, 0x8Fu, 0);
      }*/

      if (size <= 24) {

        for (size_t i = 0; i < 16; i++) {
          int index = (i * 64) + ((value % 10) * 64 * 16);
          if (index >= 8192) break;
          if (config_buffer[index] != '\0') {
            front_text((tBlockHeader *)front_vga_font, &config_buffer[index], font_ascii, font_offsets, 0, 0 + i * size + size / 2, 0x8Fu, 0);

          }
        }
      } else {
        front_text((tBlockHeader *)front_vga_font, &config_buffer[value*64], font_ascii, font_offsets, 0, 0 + size + size / 2, 0x8Fu, 0);
      }

        //if (value >= 10)
        //  for (size_t i = 0; i < 16; i++) {
        //    int index = (i * 64) + ((value - 10) * 64 * 16);
        //    if (index >= 8192) break;
        //    if (language_buffer[index] != '\0') {
        //      if (font == 0)
        //        front_text((tBlockHeader *)front_vga_font1, &language_buffer[index], font1_ascii, font1_offsets, 0, 0 + i * 24 + 12, 0x8Fu, 0);
        //      else
        //        front_text((tBlockHeader *)front_vga_font2, &language_buffer[index], font2_ascii, font2_offsets, 0, 0 + i * 24 + 12, 0x8Fu, 0);
        //    }
        //  }

          // config_buffer

          //int value = ((SDL_GetTicks() / 100) * 64) % 8192;



      SDL_Event e;
      while (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_QUIT) {
          quit_game = 1;
          doexit();
        }
        if (e.type == SDL_EVENT_KEY_DOWN) {
          if (e.key.key == SDLK_UP) {
            value++;
          }
          if (e.key.key == SDLK_DOWN) {
            value--;
          }

          if (e.key.key == SDLK_LEFT) {
            font--;
          }
          if (e.key.key == SDLK_RIGHT) {
            font++;
          }

          if (e.key.key == SDLK_D) {
            debugEnable = !debugEnable;
            continue;
          }
          if (e.key.key == SDLK_ESCAPE) {
            debugEnable = !debugEnable;
            continue;
          }
        }
      }
      UpdateSDLWindow();
    }

    load_language_file(szConfigEng, 1); // Rollback config name.
    //fre((void **)&front_vga_frontend);
    fre((void **)&front_vga_font4);
    fre((void **)&front_vga_font3);
    fre((void **)&front_vga_font2);
    fre((void **)&front_vga_font1);
  }
}

void UpdateSDL()
{
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_EVENT_QUIT) {
      quit_game = 1;
      doexit();
    }
    if (e.type == SDL_EVENT_KEY_DOWN) {

#if _DEBUG
      if (e.key.key == SDLK_D) { // Add by ROLLER
        if (SDL_GetModState() & (SDL_KMOD_LCTRL | SDL_KMOD_RCTRL)) {
          if (front_vga[2] != NULL) { // Check if front_vga is loaded, loaded in main menu.
            //if (MIDIPlaying()) 
            {
              debugEnable = !debugEnable;
              continue;
            }
          }
        }
      }
#endif // _DEBUG

      if (e.key.key == SDLK_ESCAPE) {
        quit_game = 1;
      //} else if (e.key.key == SDLK_SPACE) {
      //  //PlayAudioSampleWait(SOUND_SAMPLE_FATAL); // Test play FATAL.RAW sample, requires 'config.ini' to select correct language file.
      //  PlayAudioSampleWait(SOUND_SAMPLE_DRIVERS);
      //  PlayAudioSampleWait(SOUND_SAMPLE_ENGINES);
      //  PlayAudioSampleWait(SOUND_SAMPLE_GO);
      //  continue;
      //} else if (e.key.key == SDLK_M) {
      //  playMusic();
      //  continue;
      //} else if (e.key.key == SDLK_F11) {
      //  ToggleFullscreen();
      //  continue;
      } else if (e.key.key == SDLK_RETURN) {
        SDL_Keymod mod = SDL_GetModState();
        if (mod & (SDL_KMOD_LALT | SDL_KMOD_RALT)) {
          ToggleFullscreen();
          continue;
        }
      }
    }

    if (e.type == SDL_EVENT_KEY_DOWN || e.type == SDL_EVENT_KEY_UP) {
      SDL_Scancode sc = e.key.scancode;

      // Handle pause key as a special sequence
      if (sc == SDL_SCANCODE_PAUSE) {
        if (e.type == SDL_EVENT_KEY_DOWN) {
          key_handler(0xE1);
          key_handler(0x1D);
          key_handler(0x45);
        } else {
          key_handler(0xE1 | 0x80);
          key_handler(0x1D | 0x80);
          key_handler(0x45 | 0x80);
        }
        return;
      }

      // Translate SDL scancode to set1 scancode
      if (sc < SDL_arraysize(sdl_to_set1) && sdl_to_set1[sc]) {
        uint8 byRawCode = sdl_to_set1[sc];
        if (e.type == SDL_EVENT_KEY_UP) {
          byRawCode |= 0x80;  // Set high bit for release
        }
        key_handler(byRawCode);
      }
    }
  }
  //UpdateSDLWindow();
#if _DEBUG
  UpdateDebugLoop(); // Add by ROLLER
#endif // _DEBUG
}

//--------------------------------------------------------------------------------------------------
#pragma region MIDI

#define MIDI_RATE 44100 // not sure if this is the correct rate
SDL_AudioStream *midi_stream;
float midi_volume;
midi *midi_music;

void MIDI_AudioStreamCallback(void *userdata, SDL_AudioStream *stream, int additional_amount, int total_amount)
{
  //int available = SDL_GetAudioStreamAvailable(stream);
  //SDL_Log("MIDI_AudioStreamCallback[%i]: %i - %i", available, additional_amount, total_amount);

  //if (available != 0) return;

  if (midi_music) {
    void *output_buffer;
    int32_t res = 0;
    uint32_t samples = total_amount;

    output_buffer = malloc(samples);
    if (output_buffer != NULL)
      memset(output_buffer, 0, samples);

    if ((res = WildMidi_GetOutput(midi_music, output_buffer, samples)) > 0) {
      SDL_PutAudioStreamData(stream, output_buffer, res);
    }

    free(output_buffer);
  }
}

bool MIDI_Init(const char *config_file)
{
  long version = WildMidi_GetVersion();
  SDL_Log("MIDI_Init: Initializing libWildMidi %ld.%ld.%ld",
                      (version >> 16) & 255,
                      (version >> 8) & 255,
                      (version) & 255);

  uint16_t rate = MIDI_RATE;
  uint16_t mixer_options = 0;

  if (WildMidi_Init(config_file, rate, mixer_options) == -1) {
    SDL_Log("MIDI_Init: WildMidi_GetError: %s", WildMidi_GetError());
    WildMidi_ClearError();
    return false;
  }

  SDL_AudioSpec wav_spec;
  wav_spec.channels = 2;
  wav_spec.freq = MIDI_RATE;
  wav_spec.format = SDL_AUDIO_S16;

  midi_stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &wav_spec, MIDI_AudioStreamCallback, NULL);
  midi_volume = 1.0f; // Default volume

  return true;
}

void MIDIDigi_PlayBuffer(uint8 *midi_buffer, uint32 midi_length)
{
  midi *midi_ptr = WildMidi_OpenBuffer(midi_buffer, midi_length);
  if (!midi_ptr) {
    SDL_Log("WildMidi_OpenBuffer failed: %s", WildMidi_GetError());
    return;
  }

  // Enable Loop
  WildMidi_SetOption(midi_ptr, WM_MO_LOOP, WM_MO_LOOP);
  // Disable Loop
  WildMidi_SetOption(midi_ptr, WM_MO_LOOP, 0);

  struct _WM_Info *wm_info = WildMidi_GetInfo(midi_ptr);
  if (wm_info) {

    int apr_mins = wm_info->approx_total_samples / (MIDI_RATE * 60);
    int apr_secs = (wm_info->approx_total_samples % (MIDI_RATE * 60)) / MIDI_RATE;

    SDL_Log("MIDIDigi_PlayBuffer: [Approx %2um %2us Total]", apr_mins, apr_secs);

    SDL_Log("MIDIDigi_PlayBuffer: Total Samples %i", wm_info->approx_total_samples);
    SDL_Log("MIDIDigi_PlayBuffer: Current Samples %i", wm_info->current_sample);
    SDL_Log("MIDIDigi_PlayBuffer: Total Midi time %i", wm_info->total_midi_time);
    SDL_Log("MIDIDigi_PlayBuffer: Mix Options %i", wm_info->mixer_options);
  }

  SDL_AudioStream *stream = midi_stream;

  if (stream != NULL) {
    float master_volume = (float)MIDIGetMasterVolume() / 127.0f; // Normalize to [0.0, 1.0] range
    SDL_SetAudioStreamGain(stream, midi_volume * master_volume); // Set the gain for the audio stream
    SDL_Log("MIDIDigi_PlayBuffer: Volume: %f", midi_volume * master_volume);

    void *output_buffer;
    uint32_t len = 0;
    int32_t res = 0;
    uint32_t samples = 16384;

    output_buffer = malloc(samples);
    if (output_buffer != NULL)
      memset(output_buffer, 0, samples);

    uint32_t total_pcm_bytes = 0;

    while ((res = WildMidi_GetOutput(midi_ptr, output_buffer, samples)) > 0) {
      SDL_PutAudioStreamData(stream, output_buffer, res);
      total_pcm_bytes += res;
      if (total_pcm_bytes > 64e6) {
        SDL_Log("MIDIDigi_PlayBuffer: Stopping put audio stream due to large buffer size.");
        break;
      }
    }

    free(output_buffer);

    SDL_ResumeAudioStreamDevice(stream);

    SDL_Log("MIDIDigi_PlayBuffer: Total: %i", total_pcm_bytes);
  }

  WildMidi_Close(midi_ptr);
}

void MIDIDigi_ClearBuffer()
{
  if (midi_stream) {
    SDL_PauseAudioStreamDevice(midi_stream);
    SDL_ClearAudioStream(midi_stream);
  }
  MIDI_CloseMidiBuffer();
}

void MIDI_Shutdown()
{
  if (midi_stream) {
    SDL_PauseAudioStreamDevice(midi_stream);
    SDL_DestroyAudioStream(midi_stream);
    midi_stream = NULL;
  }
  MIDI_CloseMidiBuffer();
  WildMidi_Shutdown();
}

/// <summary>
/// Close midi buffer
/// </summary>
void MIDI_CloseMidiBuffer()
{
  if (midi_music) {
    WildMidi_Close(midi_music);
    midi_music = NULL;
  }
}

/// <summary>
/// Initializes a MIDI song for playback using the provided song data.
/// This function closes any currently loaded MIDI song, opens the new song buffer,
/// enables looping, logs song information, and sets the audio stream volume.
/// </summary>
/// <param name="data">Pointer to a tInitSong structure containing the MIDI song data and its length.</param>
void MIDIInitSong(tInitSong *data)
{
  SDL_Log("MIDIInitSong: Midi - Length: %i", data->iLength);

  MIDI_CloseMidiBuffer();

  midi_music = WildMidi_OpenBuffer(((uint8 *)data->pData), data->iLength);
  if (!midi_music) {
    SDL_Log("MIDIInitSong: WildMidi_OpenBuffer failed: %s", WildMidi_GetError());
    return;
  }
  // Enable WildMidi_GetOutput Loop
  WildMidi_SetOption(midi_music, WM_MO_LOOP, WM_MO_LOOP);

  // Get Info
  struct _WM_Info *wm_info = WildMidi_GetInfo(midi_music);
  if (wm_info) {

    int apr_mins = wm_info->approx_total_samples / (MIDI_RATE * 60);
    int apr_secs = (wm_info->approx_total_samples % (MIDI_RATE * 60)) / MIDI_RATE;

    SDL_Log("MIDIInitSong: Approx %2um %2us Total", apr_mins, apr_secs);

    SDL_Log("MIDIInitSong: Total Samples %i", wm_info->approx_total_samples);
    SDL_Log("MIDIInitSong: Current Samples %i", wm_info->current_sample);
    SDL_Log("MIDIInitSong: Total Midi time %i", wm_info->total_midi_time);
    SDL_Log("MIDIInitSong: Mix Options %i", wm_info->mixer_options);
  }

  if (!midi_stream) {
    SDL_Log("MIDIInitSong: 'midi_stream' is not initialized.");
    return;
  }

  // Set Volume Stream
  float master_volume = (float)MIDIGetMasterVolume() / 127.0f; // Normalize to [0.0, 1.0] range
  SDL_SetAudioStreamGain(midi_stream, midi_volume * master_volume); // Set the gain for the audio stream
  SDL_Log("MIDIInitSong: Volume: %f", midi_volume * master_volume);
}

void MIDIStartSong()
{
  if (!midi_stream) {
    SDL_Log("MIDIStartSong: 'midi_stream' is not initialized.");
    return;
  }

  SDL_Log("MIDIStartSong: Play Audio Stream.");
  SDL_ResumeAudioStreamDevice(midi_stream);
}

void MIDIStopSong()
{
  if (!midi_stream) {
    SDL_Log("MIDIStopSong: 'midi_stream' is not initialized.");
    return;
  }

  SDL_Log("MIDIStopSong: Pause Audio Stream.");
  SDL_PauseAudioStreamDevice(midi_stream);
}

int8 MIDIMasterVolume = 127; // Default master volume (0-127)
/// <summary>
/// Set the master volume for MIDI playback. (0-127)
/// </summary>
void MIDISetMasterVolume(int8 volume)
{
  if (volume > 127) volume = 127;
  if (volume < 0) volume = 0;
  MIDIMasterVolume = volume;

  SDL_Log("MIDISetMasterVolume: %i", volume);

  float master_volume = (float)volume / 127.0f; // Normalize to [0.0, 1.0] range

  // Change the gain for the MIDI stream
  SDL_SetAudioStreamGain(midi_stream, midi_volume * master_volume);
}

/// <summary>
/// Get the current master volume level for MIDI playback. (0-127)
/// </summary>
int MIDIGetMasterVolume()
{
  return MIDIMasterVolume;
}

#pragma endregion
//-------------------------------------------------------------------------------------------------
#pragma region DIGI
#define NUM_DIGI_STREAMS 32
SDL_AudioStream *digi_stream[NUM_DIGI_STREAMS];
float digi_volume[NUM_DIGI_STREAMS];

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
    SDL_Log("DIGISampleStart: No available audio stream slots for digital sample.");
    return index; // No available stream slots
  }

  float volume = (float)data->iVolume / 0x7FFF; // Convert volume to [0.0, 1.0] range
  // show data info
  SDL_Log("DIGISampleStart: %i, length: %i, offset: %i, volume: %f, pitch: %i, pan: %i", data->iSampleIndex, data->iLength, data->iByteOffset, volume, data->iPitch, data->iPan);

  if (!digi_stream[index]) {
    SDL_AudioSpec spec;
    spec.channels = 1; // Mono
    spec.freq = 11025; // Sample rate
    spec.format = SDL_AUDIO_U8; // 8-bit unsigned audio
    SDL_Log("DIGISampleStart: channels: %i, freq: %i, format: %i", spec.channels, spec.freq, spec.format);
    digi_stream[index] = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
    if (!digi_stream[index]) {
      SDL_Log("DIGISampleStart: Couldn't create audio stream: %s", SDL_GetError());
      return -1;
    }
  }

  SDL_AudioDeviceID device = SDL_GetAudioStreamDevice(digi_stream[index]);
  SDL_Log("DIGISampleStart: device: %u", device);

  // Set pitch in the stream
  SDL_SetAudioStreamFrequencyRatio(digi_stream[index], 1.0); // pitch

  // Remember the volume for this stream
  digi_volume[index] = volume;

  // Set the gain for the audio stream
  float master_volume = (float)DIGIGetMasterVolume() / 0x7FFF; // Normalize to [0.0, 1.0] range
  SDL_SetAudioStreamGain(digi_stream[index], volume * master_volume);

  // Put audio data into the stream
  SDL_PutAudioStreamData(digi_stream[index], ((Uint8 *)data->pSample), data->iLength);
  SDL_ResumeAudioStreamDevice(digi_stream[index]);

  SDL_Log("DIGISampleStart: index: %d", index);
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

int DIGIMasterVolume = 0x7FFF; // Default master volume (0-0x7FFF)
/// <summary>
/// Set the master volume for all digital audio streams.
/// </summary>
/// <param name="volume">Volume level (0-0x7FFF).</param>
void DIGISetMasterVolume(int volume)
{
  if (volume > 0x7FFF) volume = 0x7FFF;
  if (volume < 0) volume = 0;
  DIGIMasterVolume = volume;

  SDL_Log("DIGISetMasterVolume: %x", volume);

  float normalized_volume = (float)volume / 0x7FFF; // Normalize to [0.0, 1.0] range

  for (size_t i = 0; i < NUM_DIGI_STREAMS; i++) {
    if (digi_stream[i]) {
      SDL_SetAudioStreamGain(digi_stream[i], digi_volume[i] * normalized_volume);
    }
  }
}

/// <summary>
/// Get the current master volume level.
/// </summary>
/// <returns>The master volume level (0-0x7FFF).</returns>
int DIGIGetMasterVolume()
{
  return DIGIMasterVolume;
}

void DIGIStopSample(int index)
{
  if (index < 0 || index >= NUM_DIGI_STREAMS) {
    SDL_Log("DIGIStopSample: Invalid stream index: %d", index);
    return;
  }

  if (digi_stream[index]) {
    SDL_PauseAudioStreamDevice(digi_stream[index]);
    SDL_DestroyAudioStream(digi_stream[index]);
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
#pragma endregion
//-------------------------------------------------------------------------------------------------

bool ROLLERfexists(const char *szFile)
{
  FILE *pFile = fopen(szFile, "r");
  if (pFile) {
    fclose(pFile);
    return true;
  }

  char szUpper[260] = { 0 };
  char szLower[260] = { 0 };
  int iLength = (int)strlen(szFile);

  for (int i = 0; i < iLength && i < sizeof(szUpper); ++i) {
    szUpper[i] = toupper(szFile[i]);
    szLower[i] = tolower(szFile[i]);
  }

  pFile = fopen(szUpper, "r");
  if (pFile) {
    fclose(pFile);
    return true;
  }

  pFile = fopen(szLower, "r");
  if (pFile) {
    fclose(pFile);
    return true;
  }

  return false;
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

  pFile = fopen(szLower, szMode);
  return pFile;
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

  iHandle = open(szLower, iOpenFlags);
  return iHandle;
}

//-------------------------------------------------------------------------------------------------

uint32 ROLLERAddTimer(Uint32 uiFrequencyHz, SDL_NSTimerCallback callback, void *userdata)
{
  SDL_LockMutex(g_pTimerMutex);
  uint32 uiHandle = SDL_AddTimerNS(HZ_TO_NS(uiFrequencyHz), callback, userdata);

  //find empty timer slot
  bool bFoundSlot = false;
  for (int i = 0; i < MAX_TIMERS; ++i) {
    if (timerDataAy[i].uiHandle == 0) {
      bFoundSlot = true;
      timerDataAy[i].uiHandle = uiHandle;
      timerDataAy[i].ullTargetSDLTicksNS = HZ_TO_NS(uiFrequencyHz);
      timerDataAy[i].ullLastSDLTicksNS = SDL_GetTicksNS();
      break;
    }
  }
  SDL_UnlockMutex(g_pTimerMutex);

  if (!bFoundSlot) {
    //too many timers!
    assert(0);
    ErrorBoxExit("Too many timers!");
  }

  return uiHandle;
}

//-------------------------------------------------------------------------------------------------

void ROLLERRemoveTimer(uint32 uiHandle)
{
  SDL_LockMutex(g_pTimerMutex);
  SDL_RemoveTimer(uiHandle);
  //clear timer data
  for (int i = 0; i < MAX_TIMERS; ++i) {
    if (timerDataAy[i].uiHandle == uiHandle) {
      memset(&timerDataAy[i], 0, sizeof(tTimerData));
    }
  }
  SDL_UnlockMutex(g_pTimerMutex);
}

//-------------------------------------------------------------------------------------------------

int ROLLERfilelength(const char *szFile)
{
#ifdef IS_WINDOWS
  int iFileHandle = ROLLERopen(szFile, O_RDONLY | O_BINARY); //0x200 is O_BINARY in WATCOM/h/fcntl.h

  if (iFileHandle == -1)
    return -1;

  int iSize = _filelength(iFileHandle);

  close(iFileHandle);
  return iSize;
#else
  FILE *fp = ROLLERfopen(szFile, "rb");
  if (!fp)
    return -1;

  fseek(fp, 0, SEEK_END);
  int iSize = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  fclose(fp);
  return iSize;
#endif
}

//-------------------------------------------------------------------------------------------------
//g_pTimerMutex MUST BE LOCKED before calling this function
tTimerData *GetTimerData(SDL_TimerID timerID)
{
  for (int i = 0; i < MAX_TIMERS; ++i) {
    if (timerDataAy[i].uiHandle == timerID) {
      return &timerDataAy[i];
    }
  }
  return NULL;
}

//-------------------------------------------------------------------------------------------------

Uint64 SDLTickTimerCallback(void *userdata, SDL_TimerID timerID, Uint64 interval)
{
  tickhandler();
  uint64 ullRet = 0;

  SDL_LockMutex(g_pTimerMutex);
  tTimerData *pTimerData = GetTimerData(timerID);
  if (!pTimerData) {
    assert(0);
    ErrorBoxExit("Tick timer handle not found!");
  }

  pTimerData->ullCurrSDLTicksNS = SDL_GetTicksNS();
  int64 llNSSinceLast = (int64)pTimerData->ullCurrSDLTicksNS - (int64)pTimerData->ullLastSDLTicksNS;
  int64 llDelta = llNSSinceLast - (int64)pTimerData->ullTargetSDLTicksNS;
  if (llDelta < 0)
    llDelta = 0;
  pTimerData->ullLastSDLTicksNS = pTimerData->ullCurrSDLTicksNS;
  ullRet = pTimerData->ullTargetSDLTicksNS - llDelta;
  SDL_UnlockMutex(g_pTimerMutex);

  return ullRet;
}

//-------------------------------------------------------------------------------------------------

Uint64 SDLS7TimerCallback(void *userdata, SDL_TimerID timerID, Uint64 interval)
{
  ++s7;
  uint64 ullRet = 0;

  SDL_LockMutex(g_pTimerMutex);
  tTimerData *pTimerData = GetTimerData(timerID);
  if (!pTimerData) {
    assert(0);
    ErrorBoxExit("S7 timer handle not found!");
  }

  pTimerData->ullCurrSDLTicksNS = SDL_GetTicksNS();
  int64 llNSSinceLast = (int64)pTimerData->ullCurrSDLTicksNS - (int64)pTimerData->ullLastSDLTicksNS;
  int64 llDelta = llNSSinceLast - (int64)pTimerData->ullTargetSDLTicksNS;
  if (llDelta < 0)
    llDelta = 0;
  pTimerData->ullLastSDLTicksNS = pTimerData->ullCurrSDLTicksNS;
  ullRet = pTimerData->ullTargetSDLTicksNS - llDelta;
  SDL_UnlockMutex(g_pTimerMutex);

  return ullRet;
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

void ReplaceExtension(char *szFilename, const char *szNewExt)
{
  char *szDot = strrchr(szFilename, '.');
  char *szSlash = strrchr(szFilename, '/');
  char *szBackslash = strrchr(szFilename, '\\');

  char *szLastSeparator = (szSlash > szBackslash) ? szSlash : szBackslash;

  if (szDot && (szLastSeparator == NULL || szDot > szLastSeparator)) {
    strcpy(szDot, szNewExt);
  } else {
    strcat(szFilename, szNewExt);
  }
}

//-------------------------------------------------------------------------------------------------

void ErrorBoxExit(const char *szErrorMsgFormat, ...)
{
  va_list args;
  va_start(args, szErrorMsgFormat);
  char szErrorMsg[2048];
  int iLen = vsnprintf(szErrorMsg, sizeof(szErrorMsg) - 1, szErrorMsgFormat, args);
  if (iLen >= 0)
    szErrorMsg[iLen] = '\0';
  va_end(args);

  SDL_ShowMessageBox(&(SDL_MessageBoxData)
  {
    .title = "ROLLER",
      .message = szErrorMsg,
      .flags = SDL_MESSAGEBOX_ERROR,
      .numbuttons = 1,
      .buttons = (SDL_MessageBoxButtonData[]){
        {.flags = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, .text = "OK" }
    },
  }, NULL);

  ShutdownSDL();
  quick_exit(0);
}

//-------------------------------------------------------------------------------------------------

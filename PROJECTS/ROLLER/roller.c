#include "roller.h"
#include "3d.h"
#include "sound.h"
#include "frontend.h"
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <SDL3_image/SDL_image.h>
#include "cdx.h"

#include <wildmidi/wildmidi_lib.h>

const char *config_txt =
"dir /usr/share/midi/freepats\n"
"\n"
"# Automatically generated on Sun Feb 19 19:22:39 EST 2006\n"
"# by http://freepats.opensrc.org/mkcfg.sh.txt\n"
"\n"
"drumset 0\n"
"\n"
" 25\tDrum_000/025_Snare_Roll.pat \n"
" 26\tDrum_000/026_Snap.pat \n"
" 27\tDrum_000/027_High_Q.pat \n"
" 31\tDrum_000/031_Sticks.pat \n"
" 32\tDrum_000/032_Square_Click.pat \n"
" 33\tDrum_000/033_Metronome_Click.pat \n"
" 34\tDrum_000/034_Metronome_Bell.pat \n"
" 35\tDrum_000/035_Kick_1.pat amp=100\n"
" 36\tDrum_000/036_Kick_2.pat amp=100\n"
" 37\tDrum_000/037_Stick_Rim.pat \n"
" 38\tDrum_000/038_Snare_1.pat \n"
" 39\tDrum_000/039_Clap_Hand.pat amp=100\n"
" 40\tDrum_000/040_Snare_2.pat \n"
" 41\tDrum_000/041_Tom_Low_2.pat amp=100\n"
" 42\tDrum_000/042_Hi-Hat_Closed.pat \n"
" 43\tDrum_000/043_Tom_Low_1.pat amp=100\n"
" 44\tDrum_000/044_Hi-Hat_Pedal.pat \n"
" 45\tDrum_000/045_Tom_Mid_2.pat amp=100\n"
" 46\tDrum_000/046_Hi-Hat_Open.pat \n"
" 47\tDrum_000/047_Tom_Mid_1.pat amp=100\n"
" 48\tDrum_000/048_Tom_High_2.pat amp=100\n"
" 49\tDrum_000/049_Cymbal_Crash_1.pat \n"
" 50\tDrum_000/050_Tom_High_1.pat amp=100\n"
" 51\tDrum_000/051_Cymbal_Ride_1.pat \n"
" 52\tDrum_000/052_Cymbal_Chinese.pat \n"
" 53\tDrum_000/053_Cymbal_Ride_Bell.pat amp=100\n"
" 54\tDrum_000/054_Tombourine.pat \n"
" 55\tDrum_000/055_Cymbal_Splash.pat \n"
" 56\tDrum_000/056_Cow_Bell.pat \n"
" 57\tDrum_000/057_Cymbal_Crash_2.pat \n"
" 58\tDrum_000/058_Vibra-Slap.pat \n"
" 59\tDrum_000/059_Cymbal_Ride_2.pat \n"
" 60\tDrum_000/060_Bongo_High.pat \n"
" 61\tDrum_000/061_Bongo_Low.pat \n"
" 62\tDrum_000/062_Conga_High_1_Mute.pat \n"
" 63\tDrum_000/063_Conga_High_2_Open.pat \n"
" 64\tDrum_000/064_Conga_Low.pat \n"
" 65\tDrum_000/065_Timbale_High.pat \n"
" 66\tDrum_000/066_Timbale_Low.pat \n"
" 67\tDrum_000/067_Agogo_High.pat \n"
" 68\tDrum_000/068_Agogo_Low.pat \n"
" 69\tDrum_000/069_Cabasa.pat amp=100\n"
" 70\tDrum_000/070_Maracas.pat \n"
" 71\tDrum_000/071_Whistle_1_High_Short.pat \n"
" 72\tDrum_000/072_Whistle_2_Low_Long.pat \n"
" 73\tDrum_000/073_Guiro_1_Short.pat \n"
" 74\tDrum_000/074_Guiro_2_Long.pat \n"
" 75\tDrum_000/075_Claves.pat amp=100\n"
" 76\tDrum_000/076_Wood_Block_1_High.pat \n"
" 77\tDrum_000/077_Wood_Block_2_Low.pat \n"
" 78\tDrum_000/078_Cuica_1_Mute.pat amp=100\n"
" 79\tDrum_000/079_Cuica_2_Open.pat amp=100\n"
" 80\tDrum_000/080_Triangle_1_Mute.pat \n"
" 81\tDrum_000/081_Triangle_2_Open.pat \n"
" 82\tDrum_000/082_Shaker.pat \n"
" 84\tDrum_000/084_Belltree.pat \n"
"\n"
"bank 0\n"
"\n"
" 0\tTone_000/000_Acoustic_Grand_Piano.pat amp=120 pan=center\n"
" 1\tTone_000/001_Acoustic_Brite_Piano.pat \n"
" 2\tTone_000/002_Electric_Grand_Piano.pat \n"
" 4\tTone_000/004_Electric_Piano_1_Rhodes.pat \n"
" 5\tTone_000/005_Electric_Piano_2_Chorused_Yamaha_DX.pat \n"
" 6\tTone_000/006_Harpsichord.pat \n"
" 7\tTone_000/007_Clavinet.pat \n"
" 8\tTone_000/008_Celesta.pat \n"
" 9\tTone_000/009_Glockenspiel.pat \n"
" 13\tTone_000/013_Xylophone.pat \n"
" 14\tTone_000/014_Tubular_Bells.pat \n"
" 15\tTone_000/015_Dulcimer.pat \n"
" 16\tTone_000/016_Hammond_Organ.pat \n"
" 19\tTone_000/019_Church_Organ.pat \n"
" 21\tTone_000/021_Accordion.pat \n"
" 23\tTone_000/023_Tango_Accordion.pat \n"
" 24\tTone_000/024_Nylon_Guitar.pat \n"
" 25\tTone_000/025_Steel_Guitar.pat \n"
" 26\tTone_000/026_Jazz_Guitar.pat \n"
" 27\tTone_000/027_Clean_Electric_Guitar.pat \n"
" 28\tTone_000/028_Muted_Electric_Guitar.pat \n"
" 29\tTone_000/029_Overdriven_Guitar.pat \n"
" 30\tTone_000/030_Distortion_Guitar.pat \n"
" 32\tTone_000/032_Acoustic_Bass.pat \n"
" 33\tTone_000/033_Finger_Bass.pat \n"
" 34\tTone_000/034_Pick_Bass.pat \n"
" 35\tTone_000/035_Fretless_Bass.pat \n"
" 36\tTone_000/036_Slap_Bass_1.pat \n"
" 37\tTone_000/037_Slap_Bass_2.pat \n"
" 38\tTone_000/038_Synth_Bass_1.pat \n"
" 40\tTone_000/040_Violin.pat \n"
" 42\tTone_000/042_Cello.pat \n"
" 44\tTone_000/044_Tremolo_Strings.pat \n"
" 45\tTone_000/045_Pizzicato_Strings.pat \n"
" 46\tTone_000/046_Harp.pat \n"
" 47\tTone_000/047_Timpani.pat \n"
" 48\tTone_000/048_String_Ensemble_1_Marcato.pat \n"
" 53\tTone_000/053_Voice_Oohs.pat \n"
" 56\tTone_000/056_Trumpet.pat \n"
" 57\tTone_000/057_Trombone.pat \n"
" 58\tTone_000/058_Tuba.pat \n"
" 59\tTone_000/059_Muted_Trumpet.pat \n"
" 60\tTone_000/060_French_Horn.pat \n"
" 61\tTone_000/061_Brass_Section.pat \n"
" 64\tTone_000/064_Soprano_Sax.pat \n"
" 65\tTone_000/065_Alto_Sax.pat \n"
" 66\tTone_000/066_Tenor_Sax.pat \n"
" 67\tTone_000/067_Baritone_Sax.pat \n"
" 68\tTone_000/068_Oboe.pat \n"
" 69\tTone_000/069_English_Horn.pat \n"
" 70\tTone_000/070_Bassoon.pat \n"
" 71\tTone_000/071_Clarinet.pat \n"
" 72\tTone_000/072_Piccolo.pat \n"
" 73\tTone_000/073_Flute.pat \n"
" 74\tTone_000/074_Recorder.pat \n"
" 75\tTone_000/075_Pan_Flute.pat \n"
" 76\tTone_000/076_Bottle_Blow.pat \n"
" 79\tTone_000/079_Ocarina.pat \n"
" 80\tTone_000/080_Square_Wave.pat \n"
" 84\tTone_000/084_Charang.pat \n"
" 88\tTone_000/088_New_Age.pat \n"
" 94\tTone_000/094_Halo_Pad.pat \n"
" 95\tTone_000/095_Sweep_Pad.pat \n"
" 98\tTone_000/098_Crystal.pat \n"
" 101\tTone_000/101_Goblins--Unicorn.pat \n"
" 102\tTone_000/102_Echo_Voice.pat \n"
" 104\tTone_000/104_Sitar.pat \n"
" 114\tTone_000/114_Steel_Drums.pat \n"
" 115\tTone_000/115_Wood_Block.pat \n"
" 120\tTone_000/120_Guitar_Fret_Noise.pat \n"
" 122\tTone_000/122_Seashore.pat \n"
" 125\tTone_000/125_Helicopter.pat \n"
;


#define TML_IMPLEMENTATION
#include "tml.h"

#define TSF_IMPLEMENTATION
#include "tsf.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include <fluidsynth.h>

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
#ifdef IS_WINDOWS
  if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
#else
  //TODO linux audio
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
#endif
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

boolean debug = 1;


void play_midi_file(const char *midi_filename)
{
  MCI_OPEN_PARMS mciOpenParms;
  MCI_PLAY_PARMS mciPlayParms;
  //char command[256];

  mciOpenParms.lpstrDeviceType = "sequencer";
  mciOpenParms.lpstrElementName = midi_filename;
  if (mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
                     (DWORD_PTR)&mciOpenParms)) {
    //MessageBox(NULL, "Cannot open MIDI file.", "Error", MB_OK);
    SDL_Log("Cannot open MIDI file.");
    return;
  }

  UINT deviceID = mciOpenParms.wDeviceID;

  // play the MIDI file
  mciSendCommand(deviceID, MCI_PLAY, 0, (DWORD_PTR)&mciPlayParms);
}

// Holds the global instance pointer
static tsf *g_TinySoundFont;

// Holds global MIDI playback state
static double g_Msec;               //current playback time
static tml_message *g_MidiMessage;  //next message to be played

// Callback function called by the audio thread
static void AudioCallback(void *data, Uint8 *stream, int len)
{
        //Number of samples to process
  int SampleBlock, SampleCount = (len / (2 * sizeof(float))); //2 output channels
  for (SampleBlock = TSF_RENDER_EFFECTSAMPLEBLOCK; SampleCount; SampleCount -= SampleBlock, stream += (SampleBlock * (2 * sizeof(float)))) {
          //We progress the MIDI playback and then process TSF_RENDER_EFFECTSAMPLEBLOCK samples at once
    if (SampleBlock > SampleCount) SampleBlock = SampleCount;

    //Loop through all MIDI messages which need to be played up until the current playback time
    for (g_Msec += SampleBlock * (1000.0 / 44100.0); g_MidiMessage && g_Msec >= g_MidiMessage->time; g_MidiMessage = g_MidiMessage->next) {
      switch (g_MidiMessage->type) {
        case TML_PROGRAM_CHANGE: //channel program (preset) change (special handling for 10th MIDI channel with drums)
          tsf_channel_set_presetnumber(g_TinySoundFont, g_MidiMessage->channel, g_MidiMessage->program, (g_MidiMessage->channel == 9));
          break;
        case TML_NOTE_ON: //play a note
          tsf_channel_note_on(g_TinySoundFont, g_MidiMessage->channel, g_MidiMessage->key, g_MidiMessage->velocity / 127.0f);
          break;
        case TML_NOTE_OFF: //stop a note
          tsf_channel_note_off(g_TinySoundFont, g_MidiMessage->channel, g_MidiMessage->key);
          break;
        case TML_PITCH_BEND: //pitch wheel modification
          tsf_channel_set_pitchwheel(g_TinySoundFont, g_MidiMessage->channel, g_MidiMessage->pitch_bend);
          break;
        case TML_CONTROL_CHANGE: //MIDI controller messages
          tsf_channel_midi_control(g_TinySoundFont, g_MidiMessage->channel, g_MidiMessage->control, g_MidiMessage->control_value);
          break;
      }
    }

    // Render the block of audio samples in float format
    tsf_render_float(g_TinySoundFont, (float *)stream, SampleBlock, 0);
  }
}

void UpdateSDL()
{
  if (debug) {
    debug = 0;

      /*MCIERROR mciError;
      mciError = mciSendString("status cd number of tracks", buffer, sizeof(buffer), NULL);
      SDL_Log("Number of tracks on CD: %s, error: %d", buffer, mciError);*/
    SDL_Log("Number of CD: %i", numCDdrives);
    SDL_Log("Number of CD: %i", numCDdrives);
    SDL_Log("Number of CD: %i", numCDdrives);


     // Create settings and synth
    fluid_settings_t *settings = new_fluid_settings();
    fluid_synth_t *synth = new_fluid_synth(settings);
    fluid_player_t *player = new_fluid_player(synth);
    fluid_audio_driver_t *adriver = new_fluid_audio_driver(settings, synth);

    if (settings == NULL) {
      SDL_Log("Failed to create FluidSynth settings.");
      return;
    }

    if (synth == NULL) {
      SDL_Log("Failed to create FluidSynth synth.");
      delete_fluid_settings(settings);
      return;
    }

    if (player == NULL) {
      SDL_Log("Failed to create FluidSynth player.");
      delete_fluid_synth(synth);
      delete_fluid_settings(settings);
      return;
    }

    if (adriver == NULL) {
      SDL_Log("Failed to create FluidSynth audio driver.");
      delete_fluid_player(player);
      delete_fluid_synth(synth);
      delete_fluid_settings(settings);
      return;
    }

    //char *soundfont_path = "C:\\Users\\ricau\\Downloads\\SoundFont\\GeneralUser-GS.sf2"; // Path to your SoundFont file
    //char *soundfont_path = "C:\\Users\\ricau\\Downloads\\SoundFont\\FluidR3_GM.sf2"; // Path to your SoundFont file
    //char *soundfont_path = "C:\\Users\\ricau\\Downloads\\SoundFont\\GeneralUser GS 1.35.sf2"; // Path to your SoundFont file
        //char *soundfont_path = "C:\\Users\\ricau\\Downloads\\SoundFont\\VintageDreamsWaves-v2.sf2"; // Path to your SoundFont file

    //char *soundfont_path = "C:\\Users\\ricau\\Downloads\\SoundFont\\gm.sf2"; // Path to your SoundFont file
    //char *soundfont_path = "C:\\Windows\\System32\\drivers\\gm.dls";

    char *soundfont_path = "C:\\Users\\ricau\\Downloads\\SoundFont\\GMGSx.sf2"; // Path to your SoundFont file

    char *midipath = "C:\\Users\\ricau\\Downloads\\wildmidi-0.4.6-win64\\Music\\TITLE.HMP.mid"; // Path to your MIDI file
    //midipath = "C:\\Users\\ricau\\Downloads\\wildmidi-0.4.6-win64\\Music\\OPTIONS.HMP.mid"; // Path to your MIDI file
    midipath = "C:\\Users\\ricau\\Downloads\\wildmidi-0.4.6-win64\\Music\\WINONE.HMP.mid";
    midipath = "C:\\Users\\ricau\\Downloads\\wildmidi-0.4.6-win64\\Music\\WINTWO.HMP.mid";
    midipath = "C:\\Users\\ricau\\Downloads\\wildmidi-0.4.6-win64\\Music\\LEADBORD.HMP.mid";
    midipath = "C:\\Users\\ricau\\Downloads\\wildmidi-0.4.6-win64\\Music\\INGAME1.HMP.mid";
    midipath = "C:\\Users\\ricau\\Downloads\\wildmidi-0.4.6-win64\\Music\\INGAME2.HMP.mid";
    midipath = "C:\\Users\\ricau\\Downloads\\wildmidi-0.4.6-win64\\Music\\INGAME3.HMP.mid";
    midipath = "C:\\Users\\ricau\\Downloads\\wildmidi-0.4.6-win64\\Music\\INGAME4.HMP.mid";
    midipath = "C:\\Users\\ricau\\Downloads\\wildmidi-0.4.6-win64\\t.mid";
    midipath = "C:\\Users\\ricau\\Downloads\\wildmidi-0.4.6-win64\\song.mid";

    midipath = "C:\\Users\\ricau\\Downloads\\wildmidi-0.4.6-win64\\Music\\TITLE.HMP.mid"; // Path to your MIDI file

    midipath = "C:\\Users\\ricau\\Downloads\\wildmidi-0.4.6-win64\\Music\\TITLE.HMP.mid";

    tml_message *TinyMidiLoader = tml_load_filename(midipath);
    tsf *g_TinySoundFont = tsf_load_filename(soundfont_path);

    if (!TinyMidiLoader) {
      SDL_Log("Could not load MIDI file\n");
    }

    if (!g_TinySoundFont) {
      SDL_Log("Could not load SoundFont\n");
    }

    //Initialize preset on special 10th MIDI channel to use percussion sound bank (128) if available
    tsf_channel_set_bank_preset(g_TinySoundFont, 9, 128, 0);

    // Set the SoundFont rendering output mode
    tsf_set_output(g_TinySoundFont, TSF_STEREO_INTERLEAVED, 44100, -10.0f);
   
    tml_message *g_MidiMessage = TinyMidiLoader;


    //// Holds global MIDI playback state
    //static double g_Msec;               //current playback time
    //Uint8 *stream;
    //int len;
    ////Number of samples to process
    //int SampleBlock, SampleCount = (len / (2 * sizeof(float))); //2 output channels
    //for (SampleBlock = TSF_RENDER_EFFECTSAMPLEBLOCK; SampleCount; SampleCount -= SampleBlock, stream += (SampleBlock * (2 * sizeof(float)))) {
    //        //We progress the MIDI playback and then process TSF_RENDER_EFFECTSAMPLEBLOCK samples at once
    //  if (SampleBlock > SampleCount) SampleBlock = SampleCount;

    //  //Loop through all MIDI messages which need to be played up until the current playback time
    //  for (g_Msec += SampleBlock * (1000.0 / 44100.0); g_MidiMessage && g_Msec >= g_MidiMessage->time; g_MidiMessage = g_MidiMessage->next) {
    //    switch (g_MidiMessage->type) {
    //      case TML_PROGRAM_CHANGE: //channel program (preset) change (special handling for 10th MIDI channel with drums)
    //        tsf_channel_set_presetnumber(g_TinySoundFont, g_MidiMessage->channel, g_MidiMessage->program, (g_MidiMessage->channel == 9));
    //        break;
    //      case TML_NOTE_ON: //play a note
    //        tsf_channel_note_on(g_TinySoundFont, g_MidiMessage->channel, g_MidiMessage->key, g_MidiMessage->velocity / 127.0f);
    //        break;
    //      case TML_NOTE_OFF: //stop a note
    //        tsf_channel_note_off(g_TinySoundFont, g_MidiMessage->channel, g_MidiMessage->key);
    //        break;
    //      case TML_PITCH_BEND: //pitch wheel modification
    //        tsf_channel_set_pitchwheel(g_TinySoundFont, g_MidiMessage->channel, g_MidiMessage->pitch_bend);
    //        break;
    //      case TML_CONTROL_CHANGE: //MIDI controller messages
    //        tsf_channel_midi_control(g_TinySoundFont, g_MidiMessage->channel, g_MidiMessage->control, g_MidiMessage->control_value);
    //        break;
    //    }
    //  }

    //  // Render the block of audio samples in float format
    //  tsf_render_float(g_TinySoundFont, (float *)stream, SampleBlock, 0);
    //}

#define SAMPLE_RATE 44100
#define BLOCK_SIZE 64

    double time = 0;
    double delta = 1.0 / SAMPLE_RATE;
    double currTempo = 120.0; // BPM
    double secondsPerBeat = 60.0 / currTempo;
    double ticksPerBeat = 120.0; // default, overridden by tml

    tml_message *seq = TinyMidiLoader;


    float buffer[BLOCK_SIZE * 2];

    while (g_MidiMessage->next != NULL) {
      //if (g_MidiMessage->type == TML_PROGRAM_CHANGE)
      SDL_Log("TinyMidiLoader %i - program: %i - channel: %i  key: %i  -- time: %i", g_MidiMessage->type, g_MidiMessage->program, g_MidiMessage->channel, g_MidiMessage->key, g_MidiMessage->time);

      switch (g_MidiMessage->type) {
        case TML_PROGRAM_CHANGE: //channel program (preset) change (special handling for 10th MIDI channel with drums)
          tsf_channel_set_presetnumber(g_TinySoundFont, g_MidiMessage->channel, g_MidiMessage->program, (g_MidiMessage->channel == 9));
          break;
        case TML_NOTE_ON: //play a note
          tsf_channel_note_on(g_TinySoundFont, g_MidiMessage->channel, g_MidiMessage->key, g_MidiMessage->velocity / 127.0f);
          break;
        case TML_NOTE_OFF: //stop a note
          tsf_channel_note_off(g_TinySoundFont, g_MidiMessage->channel, g_MidiMessage->key);
          break;
        case TML_PITCH_BEND: //pitch wheel modification
          tsf_channel_set_pitchwheel(g_TinySoundFont, g_MidiMessage->channel, g_MidiMessage->pitch_bend);
          break;
        case TML_CONTROL_CHANGE: //MIDI controller messages
          tsf_channel_midi_control(g_TinySoundFont, g_MidiMessage->channel, g_MidiMessage->control, g_MidiMessage->control_value);
          break;
      }

      //tsf_render_float(g_TinySoundFont, (float *)stream, SampleBlock, 0);

      g_MidiMessage = g_MidiMessage->next;
    }

    SDL_Log("Finish");

    //return;


    // Load soundfont
    if (fluid_synth_sfload(synth, soundfont_path, 1) == FLUID_FAILED) {
      SDL_Log("Failed to load SoundFont: %s\n", soundfont_path);
      return 1;
    }


    // https://github.com/schellingb/TinySoundFont/blob/main/examples/example3.c

    if (fluid_player_add(player, midipath) != FLUID_OK) {
      SDL_Log("Failed to load MIDI: %s\n", midipath);
      return 1;
    }

    SDL_Log("Run: %s\n", midipath);

    // Start the MIDI player
    fluid_player_play(player);

    //play_midi_file(midipath);

    //while (fluid_player_get_status(player) == FLUID_PLAYER_PLAYING) {
    //  SDL_Log("Status: %i\n", fluid_player_get_status(player));
    //  Sleep(1000); // Wait for 1 second
    //}

    //play_midi_file("C:\\Users\\ricau\\Downloads\\wildmidi-0.4.6-win64\\TITLE.HMP.mid");

//uint8 *musicbuffer;
//int songId = 1;
//uint32 uiSize = getcompactedfilelength(&Song[GMSong[songId]]);
//SDL_Log("Song: %s - %i", Song[GMSong[songId]], uiSize);


/*int len = initmangle(&Song[GMSong[songId]])*4;
len = 0x3B9ACA00u;
len = 4000;
SDL_Log("Song len: %i", len);
musicbuffer = malloc(len);
memset(musicbuffer, 0, len);
loadcompactedfilepart(&musicbuffer, len);*/



//loadcompactedfile(&Song[GMSong[songId]] ,&musicbuffer);

//play_midi_file("D:\\Games\\Fatal\\Whiptools\\Whiptools\\bin\\Debug\\app.publish\\INGAME1.HMP.TXT");
//play_midi_file("C:\\Users\\ricau\\Downloads\\wildmidi-0.4.6-win64\\TITLE.HMP.mid");
//play_midi_file("C:\\Users\\ricau\\Downloads\\wildmidi-0.4.6-win64\\TITLE.HMP.hmp");

//SDL_Log(" WildMidi_GetError: %s\r\n", WildMidi_GetError());

    long libraryver = WildMidi_GetVersion();
    SDL_Log("Initializing libWildMidi %ld.%ld.%ld\n\n",
                        (libraryver >> 16) & 255,
                        (libraryver >> 8) & 255,
                        (libraryver) & 255);

    static char config_file[1024];
    static unsigned int rate = 32072;
    uint16_t mixer_options = 0;

    //mixer_options = WM_MO_LOG_VOLUME | WM_MO_ENHANCED_RESAMPLING | WM_MO_REVERB | WM_MO_LOOP | WM_MO_SAVEASTYPE0 | WM_MO_ROUNDTEMPO | WM_MO_STRIPSILENCE | WM_MO_TEXTASLYRIC;


    //rate = 44100;

    // create file path for config file
    char *home_dir = SDL_GetBasePath();
    if (home_dir) {
      snprintf(config_file, sizeof(config_file), "%swildmidi.cfg", home_dir);
      SDL_free(home_dir);
    } else {
      SDL_Log("Failed to get base path: %s", SDL_GetError());
      snprintf(config_file, sizeof(config_file), "wildmidi.cfg");
    }

    // write default config file if it doesn't exist
    FILE *file = fopen(config_file, "r");
    if (!file) {
      SDL_Log("Config file not found, creating default config: %s", config_file);
      file = fopen(config_file, "w");
      if (file) {
        fputs(config_txt, file);
        fclose(file);
      } else {
        SDL_Log("Failed to create config file: %s", SDL_GetError());
        return;
      }
    } else {
      fclose(file);
    }

    if (WildMidi_Init(config_file, rate, mixer_options) == -1) {
      SDL_Log(stderr, "WildMidi_GetError: %s\r\n", WildMidi_GetError());
      WildMidi_ClearError();
      return;
    }

    //// delete file config_file
    //if (remove(config_file) != 0) {
    //  SDL_Log("Failed to delete config file: %s", config_file);
    //} else {
    //  SDL_Log("Deleted config file: %s", config_file);
    //}

    //midi *midi_ptr = WildMidi_Open("C:\\Users\\ricau\\Downloads\\wildmidi-0.4.6-win64\\TITLE.HMP.hmp");
    //midi *midi_ptr = WildMidi_Open("C:\\Users\\ricau\\Downloads\\wildmidi-0.4.6-win64\\song.mid");
    midi *midi_ptr = WildMidi_Open("C:\\Users\\ricau\\Downloads\\wildmidi-0.4.6-win64\\TITLE.HMP.hmp");

    //midi *midi_ptr = WildMidi_Open("C:\\Users\\ricau\\Downloads\\wildmidi-0.4.6-win64\\song.mid");

    SDL_Log(" WildMidi_Open");
    if (midi_ptr == NULL) {
      SDL_Log(" WildMidi_GetError: %s\r\n", WildMidi_GetError());
    }

    //WildMidi_MasterVolume(127);
    struct _WM_Info *wm_info = WildMidi_GetInfo(midi_ptr);
    char *lyric = WildMidi_GetLyric(midi_ptr);

    if (wm_info) {

      int apr_mins = wm_info->approx_total_samples / (rate * 60);
      int apr_secs = (wm_info->approx_total_samples % (rate * 60)) / rate;

      SDL_Log("[%s]", lyric);
      SDL_Log("[Approx %2um %2us Total]", apr_mins, apr_secs);

      SDL_Log("Total Samples %i", wm_info->approx_total_samples);
      SDL_Log("Current Samples %i", wm_info->current_sample);
      SDL_Log("Total Midi time %i", wm_info->total_midi_time);
      SDL_Log("Mix Options %i", wm_info->mixer_options);


      //int8_t *output_buffer;
      //uint32_t len = 0;
      //int32_t res = 0;

      //uint32_t samples = 16000;
      //output_buffer = malloc(samples);
      //memset(output_buffer, 0, samples);

      ////res = WildMidi_GetOutput(midi_ptr, output_buffer, samples);
      //uint32_t total_pcm_bytes = 0;

      //while ((res = WildMidi_GetOutput(midi_ptr, output_buffer, samples)) > 0) {
      //  SDL_Log("Res: %i Samples: %i", res, wm_info->current_sample);
      //  PlayAudioDataWait(output_buffer, res);
      //  total_pcm_bytes += res;
      //}

      //SDL_Log("Total: %i", total_pcm_bytes);

      ////SDL_Log("Res: %i Samples: %i", res, wm_info->current_sample);

      //if (res > 0) {
      //  PlayAudioDataWait(output_buffer, res);

      //  for (size_t i = 0; i < res; i++) {
      //    SDL_Log("[%i] %i", i, (output_buffer)[i]);
      //  }

      //}

      //int8_t *getmidibuffer = NULL;
      //uint32_t getmidisize = 0;
      //int32_t getmidiret = 0;

      //getmidiret = WildMidi_GetMidiOutput(midi_ptr, &getmidibuffer, &getmidisize);

      //if (getmidiret == -1) {
      //  SDL_Log("\r\n\nFAILED to convert events to midi\r\n");
      //  SDL_Log("GetError: %s\r\n", WildMidi_GetError());
      //  WildMidi_ClearError();
      //} else {
      //  snprintf(config_file, sizeof(config_file), "%ssample-test2.mid", home_dir);
      //  SDL_Log("Create! %s", config_file);
      //  file = fopen(config_file, "wb");

      //  if (fwrite(getmidibuffer, 1, getmidisize, file) != getmidisize) {
      //    SDL_Log("Failed to write MIDI output to file: %s", config_file);
      //  }

      //  fclose(file);

      //  SDL_Log("WildMidi_GetMidiOutput! %i", getmidisize);
      //  play_midi_file(config_file);
      //  // free(getmidibuffer);
      //}



    }

    /*
    MCIERROR err;

    err = mciSendString("open \"D:\\Games\\Fatal\\Whiptools\\Whiptools\\bin\\Debug\\app.publish\\INGAME1.HMP.TXT\" type sequencer alias music", NULL, 0, NULL);
    if (err != 0) {
      SDL_Log("Failed to open TITLE.HMP %i\n", err);
    }
    mciSendString("play music", NULL, 0, NULL);
    Sleep(30000); // let it play for 30 seconds
    mciSendString("close music", NULL, 0, NULL);
    */
    /*
    MCIERROR err;

    err = mciSendString("open \"F:\\FATDATA\\TITLE.HMP\" type sequencer alias music", NULL, 0, NULL);
    if (err != 0) {
      SDL_Log("Failed to open TITLE.HMP %i\n", err);
    }
    mciSendString("play music", NULL, 0, NULL);
    Sleep(30000); // let it play for 30 seconds
    mciSendString("close music", NULL, 0, NULL);


    char driveLetter = 'F';
    char rootPath[4] = { driveLetter, ':', '\\', '\0' };

    char openCmd[64];
    sprintf(openCmd, "open %s type cdaudio alias cd", rootPath);
    err = mciSendString(openCmd, NULL, 0, NULL);
    if (err != 0) {
      SDL_Log("Failed to open CD on drive %s\n", rootPath);

    }
    mciSendString("status cd number of tracks", buffer, sizeof(buffer), NULL);

    int numTracks = atoi(buffer);
    SDL_Log("Number of tracks: %d\n", numTracks);




    // Play first track if available
    if (numTracks > 0) {
      SDL_Log("Playing track 1...\n");
      mciSendString("play cd from 1", NULL, 0, NULL);
      //SDL_Log("Press ENTER to stop playback...\n");
      //getchar();
      //mciSendString("stop cd", NULL, 0, NULL);
    }
    */
  }

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
boolean DIGISampleDone(int index)
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

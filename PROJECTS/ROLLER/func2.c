#include "func2.h"
#include "control.h"
#include "sound.h"
#include "3d.h"
#include "frontend.h"
#include "car.h"
#include "colision.h"
#include "drawtrk3.h"
#include "comms.h"
#include "roller.h"
#include "polytex.h"
#include "types.h"
#include "view.h"
#include "function.h"
#include "date.h"
#include "moving.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <float.h>
#ifdef IS_WINDOWS
#include <io.h>
#include <direct.h>
#define chdir _chdir
#define read _read
#define close _close
#else
#include <unistd.h>
#define O_BINARY 0 //linux does not differentiate between text and binary
#endif
//-------------------------------------------------------------------------------------------------

// Symbol names defined by ROLLER
char szKey1[] = "1";
char szKey2[] = "2";
char szKey3[] = "3";
char szKey4[] = "4";
char szKey5[] = "5";
char szKey6[] = "6";
char szKey7[] = "7";
char szKey8[] = "8";
char szKey9[] = "9";
char szKey0[] = "0";
char szKeyMinus[] = "-";
char szKeyPlus[] = "+";
char szKeyBackspace[] = "BACKSPACE";
char szKeyTab[] = "TAB";
char szKeyQ[] = "Q";
char szKeyW[] = "W";
char szKeyE[] = "E";
char szKeyR[] = "R";
char szKeyT[] = "T";
char szKeyY[] = "Y";
char szKeyU[] = "U";
char szKeyI[] = "I";
char szKeyO[] = "O";
char szKeyP[] = "P";
char szKeyLeftBracket[] = "[";
char szKeyRightBracket[] = "]";
char szKeyEnter[] = "ENTER";
char szKeyControl[] = "CONTROL";
char szKeyA[] = "A";
char szKeyS[] = "S";
char szKeyD[] = "D";
char szKeyF[] = "F";
char szKeyG[] = "G";
char szKeyH[] = "H";
char szKeyJ[] = "J";
char szKeyK[] = "K";
char szKeyL[] = "L";
char szKeySemicolon[] = ";";
char szKeyQuote[] = "'";
char szKeyTilde[] = "`";
char szKeyLeftShift[] = "LEFT SHIFT";
char szKeyBackslash[] = "\\";
char szKeyZ[] = "Z";
char szKeyX[] = "X";
char szKeyC[] = "C";
char szKeyV[] = "V";
char szKeyB[] = "B";
char szKeyN[] = "N";
char szKeyM[] = "M";
char szKeyComma[] = ",";
char szKeyPeriod[] = ".";
char szKeySlash[] = "/";
char szKeyRightShift[] = "RIGHT SHIFT";
char szKeyNumMult[] = "*";
char szKeyAlt[] = "ALT";
char szKeySpace[] = "SPACE";
char szKeyCapsLock[] = "CAPS LOCK";
char szKeyF1[] = "F1";
char szKeyF2[] = "F2";
char szKeyF3[] = "F3";
char szKeyF4[] = "F4";
char szKeyF5[] = "F5";
char szKeyF6[] = "F6";
char szKeyF7[] = "F7";
char szKeyF8[] = "F8";
char szKeyF9[] = "F9";
char szKeyF10[] = "F10";
char szKeyNumLock[] = "NUM LOCK";
char szKeyScrollLock[] = "SCROLL LOCK";
char szKeyHome[] = "HOME";
char szKeyUpArrow[] = "UP ARROW";
char szKeyPageUp[] = "PAGE UP";
char szKeyNumMinus[] = "-";
char szKeyLeftArrow[] = "LEFT ARROW";
char szKeyCenter[] = "CENTER";
char szKeyRightArrow[] = "RIGHT ARROW";
char szKeyNumPlus[] = "+";
char szKeyEnd[] = "END";
char szKeyDownArrow[] = "DOWN ARROW";
char szKeyPageDown[] = "PAGE DOWN";
char szKeyInsert[] = "INSERT";
char szKeyDelete[] = "DELETE";
char szKeyF11[] = "F11";
char szKeyF12[] = "F12";
char szKeyJoy1Fire1[] = "JOY 1 FIRE 1";
char szKeyJoy1Fire2[] = "JOY 1 FIRE 2";
char szKeyJoy2Fire1[] = "JOY 2 FIRE 1";
char szKeyJoy2Fire2[] = "JOY 2 FIRE 2";
char szKeyJoy1Up[] = "JOY 1 UP";
char szKeyJoy1Down[] = "JOY 1 DOWN";
char szKeyJoy1Left[] = "JOY 1 LEFT";
char szKeyJoy1Right[] = "JOY 1 RIGHT";
char szKeyJoy2Up[] = "JOY 2 UP";
char szKeyJoy2Down[] = "JOY 2 DOWN";
char szKeyJoy2Left[] = "JOY 2 LEFT";
char szKeyJoy2Right[] = "JOY 2 RIGHT";

char szKmh[4] = "kmh";
char szMph[4] = "mph";

//-------------------------------------------------------------------------------------------------

int dam_remap[256] = //000A35E4
{
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, 8, 7, 6, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, 5, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, 13, 12, 11, 10, 9,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, 4, 3, 2, 1
};
int write_key = 0;          //000A39E4
int read_key = 0;           //000A39E8
int zoom_ascii_variable_1 = 0; //000A3AEC no symbols for these?
int zoom_ascii_variable_2 = 0; //000A3AF0 no symbols for these?
int zoom_ascii_variable_3 = 0; //000A3AF4 no symbols for these?
uint8 mapping[] =           //000A3AF8
{
  0x7F, 0x1B, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
  0x39, 0x30, 0x2D, 0x3D, 0x08, 0x09, 0x51, 0x57, 0x45, 0x52,
  0x54, 0x59, 0x55, 0x49, 0x4F, 0x50, 0x5B, 0x5D, 0x0D, 0x7F,
  0x41, 0x53, 0x44, 0x46, 0x47, 0x48, 0x4A, 0x4B, 0x4C, 0x3B,
  0x27, 0x60, 0x7F, 0x23, 0x5A, 0x58, 0x43, 0x56, 0x42, 0x4E,
  0x4D, 0x2C, 0x2E, 0x2F, 0x7F, 0x7F, 0x7F, 0x20, 0x7F, 0xC5,
  0xC4, 0xC3, 0xC2, 0xC1, 0xC0, 0xBF, 0xBE, 0xBD, 0xBC, 0x7F,
  0x7F, 0xB9, 0xB8, 0xB7, 0x2D, 0xB5, 0x7F, 0xB3, 0x7F, 0xB1,
  0xB0, 0xAF, 0xAE, 0xAD, 0x7F, 0x7F, 0x5C, 0xBB, 0xBA, 0x7F,
  0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
  0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
  0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
  0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F
};
int twoparter = 0;          //000A3B78
int font6_offsets[88] =     //000A3B7C
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, -3, -2, -3, -3,
  -3, -3, -3, -3, -3, -3, -3, -3,
  -3, -3, -3, -3, -3, 0, -3, -1,
  -3, -3, -3, -3, -3, 0, 0, -3,
  -3, -3, -3, 0, 0, 0, 0, 0
};
char font6_ascii[256] =     //000A3CDC
{
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x31, 0xFF, 0x53, 0xFF, 0x30,
  0xFF, 0xFF, 0x2B, 0x2D, 0x27, 0x2C, 0x26, 0x28, 0x1A, 0x1B,
  0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x2F, 0xFF,
  0xFF, 0x24, 0xFF, 0xFF, 0xFF, 0x00, 0x01, 0x02, 0x03, 0x04,
  0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
  0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
  0x19, 0x29, 0x25, 0x2A, 0xFF, 0x32, 0x2E, 0x00, 0x01, 0x02,
  0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C,
  0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
  0x17, 0x18, 0x19, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x4D, 0xFF,
  0xFF, 0x37, 0x38, 0x36, 0x39, 0xFF, 0x3E, 0x3F, 0x3D, 0x43,
  0x42, 0x40, 0x38, 0x3A, 0x3C, 0x3B, 0x3B, 0x50, 0x51, 0x4F,
  0x49, 0x48, 0x34, 0x52, 0x4A, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x35, 0x41, 0x4E, 0x47, 0x45, 0x45, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0x33, 0xFF, 0x44, 0x4B, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x46, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
char ascii_conv3[256] =
{
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x26, 0xFF, 0xFF, 0x1A, 0x1B,
  0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x01, 0x02, 0x03, 0x04,
  0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
  0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
  0x19, 0xFF, 0xFF, 0xFF, 0xFF, 0x27, 0xFF, 0x00, 0x01, 0x02,
  0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C,
  0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
  0x17, 0x18, 0x19, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x25, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
char *keyname[140] = {      //000A3EDC
  NULL,                    /* 0x00 */
  NULL,                    /* 0x01 */
  szKey1,                  /* 0x02 */
  szKey2,                  /* 0x03 */
  szKey3,                  /* 0x04 */
  szKey4,                  /* 0x05 */
  szKey5,                  /* 0x06 */
  szKey6,                  /* 0x07 */
  szKey7,                  /* 0x08 */
  szKey8,                  /* 0x09 */
  szKey9,                  /* 0x0A */
  szKey0,                  /* 0x0B */
  szKeyMinus,              /* 0x0C */
  szKeyPlus,               /* 0x0D */
  szKeyBackspace,          /* 0x0E */
  szKeyTab,                /* 0x0F */
  szKeyQ,                  /* 0x10 */
  szKeyW,                  /* 0x11 */
  szKeyE,                  /* 0x12 */
  szKeyR,                  /* 0x13 */
  szKeyT,                  /* 0x14 */
  szKeyY,                  /* 0x15 */
  szKeyU,                  /* 0x16 */
  szKeyI,                  /* 0x17 */
  szKeyO,                  /* 0x18 */
  szKeyP,                  /* 0x19 */
  szKeyLeftBracket,        /* 0x1A */
  szKeyRightBracket,       /* 0x1B */
  szKeyEnter,              /* 0x1C */
  szKeyControl,            /* 0x1D */
  szKeyA,                  /* 0x1E */
  szKeyS,                  /* 0x1F */
  szKeyD,                  /* 0x20 */
  szKeyF,                  /* 0x21 */
  szKeyG,                  /* 0x22 */
  szKeyH,                  /* 0x23 */
  szKeyJ,                  /* 0x24 */
  szKeyK,                  /* 0x25 */
  szKeyL,                  /* 0x26 */
  szKeySemicolon,          /* 0x27 */
  szKeyQuote,              /* 0x28 */
  szKeyTilde,              /* 0x29 */
  szKeyLeftShift,          /* 0x2A */
  szKeyBackslash,          /* 0x2B */
  szKeyZ,                  /* 0x2C */
  szKeyX,                  /* 0x2D */
  szKeyC,                  /* 0x2E */
  szKeyV,                  /* 0x2F */
  szKeyB,                  /* 0x30 */
  szKeyN,                  /* 0x31 */
  szKeyM,                  /* 0x32 */
  szKeyComma,              /* 0x33 */
  szKeyPeriod,             /* 0x34 */
  szKeySlash,              /* 0x35 */
  szKeyRightShift,         /* 0x36 */
  szKeyNumMult,            /* 0x37 */
  szKeyAlt,                /* 0x38 */
  szKeySpace,              /* 0x39 */
  szKeyCapsLock,           /* 0x3A */
  szKeyF1,                 /* 0x3B */
  szKeyF2,                 /* 0x3C */
  szKeyF3,                 /* 0x3D */
  szKeyF4,                 /* 0x3E */
  szKeyF5,                 /* 0x3F */
  szKeyF6,                 /* 0x40 */
  szKeyF7,                 /* 0x41 */
  szKeyF8,                 /* 0x42 */
  szKeyF9,                 /* 0x43 */
  szKeyF10,                /* 0x44 */
  szKeyNumLock,            /* 0x45 */
  szKeyScrollLock,         /* 0x46 */
  szKeyHome,               /* 0x47 */
  szKeyUpArrow,            /* 0x48 */
  szKeyPageUp,             /* 0x49 */
  szKeyNumMinus,           /* 0x4A */
  szKeyLeftArrow,          /* 0x4B */
  szKeyCenter,             /* 0x4C */
  szKeyRightArrow,         /* 0x4D */
  szKeyNumPlus,            /* 0x4E */
  szKeyEnd,                /* 0x4F */
  szKeyDownArrow,          /* 0x50 */
  szKeyPageDown,           /* 0x51 */
  szKeyInsert,             /* 0x52 */
  szKeyDelete,             /* 0x53 */
  NULL,                    /* 0x54 */
  NULL,                    /* 0x55 */
  NULL,                    /* 0x56 */
  szKeyF11,                /* 0x57 */
  szKeyF12,                /* 0x58 */
  NULL,                    /* 0x59 */
  NULL,                    /* 0x5A */
  NULL,                    /* 0x5B */
  NULL,                    /* 0x5C */
  NULL,                    /* 0x5D */
  NULL,                    /* 0x5E */
  NULL,                    /* 0x5F */
  NULL,                    /* 0x60 */
  NULL,                    /* 0x61 */
  NULL,                    /* 0x62 */
  NULL,                    /* 0x63 */
  NULL,                    /* 0x64 */
  NULL,                    /* 0x65 */
  NULL,                    /* 0x66 */
  NULL,                    /* 0x67 */
  NULL,                    /* 0x68 */
  NULL,                    /* 0x69 */
  NULL,                    /* 0x6A */
  NULL,                    /* 0x6B */
  NULL,                    /* 0x6C */
  NULL,                    /* 0x6D */
  NULL,                    /* 0x6E */
  NULL,                    /* 0x6F */
  NULL,                    /* 0x70 */
  NULL,                    /* 0x71 */
  NULL,                    /* 0x72 */
  NULL,                    /* 0x73 */
  NULL,                    /* 0x74 */
  NULL,                    /* 0x75 */
  NULL,                    /* 0x76 */
  NULL,                    /* 0x77 */
  NULL,                    /* 0x78 */
  NULL,                    /* 0x79 */
  NULL,                    /* 0x7A */
  NULL,                    /* 0x7B */
  NULL,                    /* 0x7C */
  NULL,                    /* 0x7D */
  NULL,                    /* 0x7E */
  NULL,                    /* 0x7F */
  szKeyJoy1Fire1,          /* 0x80 */
  szKeyJoy1Fire2,          /* 0x81 */
  szKeyJoy2Fire1,          /* 0x82 */
  szKeyJoy2Fire2,          /* 0x83 */
  szKeyJoy1Up,             /* 0x84 */
  szKeyJoy1Down,           /* 0x85 */
  szKeyJoy1Left,           /* 0x86 */
  szKeyJoy1Right,          /* 0x87 */
  szKeyJoy2Up,             /* 0x88 */
  szKeyJoy2Down,           /* 0x89 */
  szKeyJoy2Left,           /* 0x8A */
  szKeyJoy2Right           /* 0x8B */
};
int userkey[14] = {44u, 45u, 20u, 33u, 19u, 32u, 79u, 80u, 73u, 77u, 72u, 76u, 21u, 79u}; //000A410C
uint8 key_buffer[64];       //0013FB90
int new_zoom[2];            //0013FBD0
char config_buffer[8192];   //0013FBD8
char language_buffer[8192]; //00141BD8
int zoom_x;                 //00143BD8
int zoom_y;                 //00143BDC
int no_mem;                 //00143BE0
uint8 *screen_pointer;      //00143BE4
int lots_of_mem;            //00143BE8

//-------------------------------------------------------------------------------------------------

int draw_smoke(int a1, int a2)
{
  (void)(a1); (void)(a2);
  return 0;
  /*
  bool v3; // ebx
  int result; // eax
  int v5; // ecx
  float *v6; // ebx
  __int64 v7; // rax
  int v8; // ebp
  float *v9; // esi
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  double v14; // st7
  int v15; // ecx
  int v16; // eax
  double v17; // st7
  double v18; // st7
  double v19; // st7
  int v20; // ebx
  int v21; // [esp+0h] [ebp-34h]
  int v22; // [esp+0h] [ebp-34h]
  int v23; // [esp+4h] [ebp-30h]
  int v24; // [esp+4h] [ebp-30h]
  float *v25; // [esp+8h] [ebp-2Ch]
  int v26; // [esp+10h] [ebp-24h]
  int v27; // [esp+14h] [ebp-20h]
  int v28; // [esp+14h] [ebp-20h]
  int v29; // [esp+1Ch] [ebp-18h]

  v3 = a2 != ViewType[0];
  result = 4 * v3;
  v5 = SelectedView[v3];
  if (!v5 || v5 == 2 || v5 == 7) {
    set_starts(0, a2);
    if (player_type == 2)
      a2 = v3 + 16;
    LODWORD(v7) = 1408 * a2;
    v6 = (float *)&CarSpray[1408 * a2];
    HIDWORD(v7) = 0;
    if (player_type == 2 || (cheat_mode & 0x40) != 0) {
      v7 = -winh;
      LODWORD(v7) = (int)v7 / 2;
      v8 = v7;
    } else {
      v8 = 0;
    }
    v9 = v6;
    v25 = v6 + 352;
    while (1) {
      if (*((int *)v9 + 7) > 0) {
        if (*((_BYTE *)v9 + 40) == 1) {
          v10 = *v9;
          _CHP(v7, HIDWORD(v7));
          v26 = (int)v10;
          v11 = v9[1];
          _CHP(v7, HIDWORD(v7));
          v27 = (int)v11;
          v12 = (double)v26 + v9[3];
          _CHP(v7, HIDWORD(v7));
          v23 = (int)v12;
          v13 = (double)v27 - v9[4];
          _CHP(v7, HIDWORD(v7));
          v21 = (int)v13;
          v14 = v9[6];
          _CHP(v7, HIDWORD(v7));
          LODWORD(v7) = v23;
          v28 = v8 + v27;
          v15 = (int)v14;
          if ((int)v14 <= 0 || v15 >= 100)
            goto LABEL_21;
          CarPol_variable_5 = v23 - v15;
          CarPol_variable_7 = v26 - v15;
          CarPol_variable_8 = v28;
          CarPol_variable_9 = v15 + v26;
          CarPol_variable_4 = v8 + v21;
          CarPol_variable_10 = v28;
          v16 = *((_DWORD *)v9 + 9);
          CarPol_variable_6 = v8 + v21;
          BYTE1(v16) |= 0x20u;
          CarPol_variable_3 = v15 + v23;
          CarPol = v16;
          CarPol_variable_2 = 4;
          if ((v16 & 0x100) == 0) {
          LABEL_20:
            LODWORD(v7) = POLYFLAT(a1, &CarPol);
            goto LABEL_21;
          }
        } else {
          v17 = *v9;
          _CHP(v7, HIDWORD(v7));
          v22 = (int)v17;
          v18 = v9[1];
          _CHP(v7, HIDWORD(v7));
          v24 = (int)v18;
          v19 = v9[6];
          _CHP(v7, HIDWORD(v7));
          v29 = (int)v19;
          LODWORD(v7) = v22;
          v20 = (int)v19;
          HIDWORD(v7) = v8 + v24;
          if ((int)v19 <= 0 || v20 >= 100)
            goto LABEL_21;
          CarPol_variable_3 = v22 + v20;
          CarPol_variable_5 = v22 - v29;
          CarPol_variable_7 = v22 - v29;
          CarPol_variable_8 = v29 + HIDWORD(v7);
          CarPol_variable_9 = v22 + v20;
          CarPol_variable_10 = v29 + HIDWORD(v7);
          *(float *)&v7 = v9[9];
          CarPol_variable_4 = HIDWORD(v7) - v29;
          CarPol = v7;
          CarPol_variable_6 = HIDWORD(v7) - v29;
          CarPol_variable_2 = 4;
          if ((v7 & 0x100) == 0)
            goto LABEL_20;
        }
        LODWORD(v7) = POLYTEX(gfx_size);
      }
    LABEL_21:
      HIDWORD(v7) = v25;
      v9 += 11;
      if (v9 == v25)
        return set_starts(0, v25);
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void test_panel(uint8 *pScrBuf, int iPlayerCarIdx)
{
  int iCarIndex; // ecx
  uint8 byCarDesignIdx; // dl
  int iAmmoBarIdx; // ebp
  uint8 *byAmmoBarPtr; // esi
  int iAmmoBarRowIdx; // edi
  uint8 *byAmmoBarRowPtr; // esi
  int iWinWidth; // eax
  char *szSpeedUnit; // edx
  int8 byGearAyMax; // dh
  uint8 *byRPMBarPtr; // ecx
  double dCameraDist; // st7
  int i; // esi
  int iRPMBarIdx; // edx
  uint8 *byRPMBarFillPtr; // eax
  unsigned int uiRPMBarWidth; // ebx
  uint8 *byDamageBarPtr; // ecx
  double dDamage; // st7
  int j; // esi
  int iDamageBarIdx; // edx
  uint8 *byDamageBarFillPtr; // eax
  unsigned int uiDamageBarWidth; // ebx
  int byLap; // eax
  int iLapNumber; // edi
  int iLapTimeYPos; // esi
  int iTrialTimeIdx; // ebp
  double dLapTime; // st7
  //int64 llLapTimeInt; // rtt
  double dRunningLapTime; // st7
  //int64 llRunningLapTimeInt; // rtt
  int iMainCarIdx; // ecx
  int iAmmoBarIdx2; // ebp
  uint8 *byAmmoBarPtr2; // esi
  uint8 *byAmmoBarRowPtr2; // esi
  int iAmmoBarRowIdx2; // edi
  int iWinWidth2; // eax
  long double dSpeedometer; // st7
  int iSpeedDisplayValue; // ebx
  int iSpeedDigitIdx; // esi
  int iDigitArrayIdx; // ecx
  int iLastDigitIdx; // esi
  tBlockHeader *pBlockHdr; // eax
  int iScaledSize; // esi
  int iWidth; // ebp
  uint8 *byDigitPixelPtr; // edi
  uint8 *bySpriteDataPtr; // edx
  int iPixelXOffset; // eax
  int iPixelXIdx; // ebx
  int iSpeedUnitBlkIdx; // ebx
  tBlockHeader *pLifeIconBlockHdr; // esi
  int iLifeIconIdx; // edi
  int iLifeIconYPos; // ebp
  int iKillsDisplayValue; // ecx
  tBlockHeader *pKillBlockHdr; // edx
  int iKillIconIdx; // ebx
  tBlockHeader *pPositionBlockHdr; // edi
  int iRacePosition; // ecx
  int iKillIconLoopIdx; // esi
  int iCarIdxForKills; // ebp
  uint8 *byKillIconPtr; // eax
  int byKills; // ecx
  uint8 *byKillsScreenPtr; // ebp
  tBlockHeader *pKillsDigitBlockHdr; // edi
  int iGearCarIdx; // edi
  uint8 *byGearScreenPtr; // ebp
  tBlockHeader *pLapBlockHdr; // esi
  int iCurrentLap; // ecx
  tBlockHeader *pLapDigitBlockHdr; // ebp
  int iLapDigitWidth; // edx
  int iLapXOffset; // eax
  uint8 *byLapDisplayPtr; // edi
  int iLapDigitIdx; // ebx
  uint8 *byRaceScreenPtr; // esi
  int iTimingCarIdx; // ebp
  tBlockHeader *pPositionDigitBlockHdr; // esi
  int iPositionValue; // ecx
  int iPositionDigitWidth; // edx
  int iPositionXOffset; // eax
  uint8 *byPositionDisplayPtr; // edi
  int iPositionDigitIdx; // ebx
  int iPositionCarIdx; // ecx
  int iLapNum2; // edi
  int iLapTimeYPos2; // esi
  int iTrialTimeIdx2; // ebp
  double dLapTime2; // st7
  //int64 llLapTimeInt2; // rtt
  double dRunningLapTime2; // st7
  //int64 llRunningLapTimeInt2; // rtt
  int iSelectedView; // ebp
  int iTimingXPos; // esi
  int iLapTimeCarIdx; // edi
  int iTimingBaseXPos; // edi
  double dAheadTimeLaps; // st7
  double dBehindTimeLaps; // st7
  char *szMessageSender; // [esp+4h] [ebp-A4h]
  int iDigitArray[3]; // [esp+8h] [ebp-A0h]
  uint8 *byScreenPtr; // [esp+14h] [ebp-94h]
  int iCarIndex_1; // [esp+18h] [ebp-90h]
  uint8 *bySpriteRowPtr; // [esp+1Ch] [ebp-8Ch]
  uint8 *byPixelRowPtr; // [esp+20h] [ebp-88h]
  int iCarIdx; // [esp+24h] [ebp-84h]
  float fAheadTime; // [esp+28h] [ebp-80h] BYREF
  float fBehindTime; // [esp+2Ch] [ebp-7Ch] BYREF
  float fBestLapTime; // [esp+30h] [ebp-78h]
  int iBaseXPos; // [esp+34h] [ebp-74h]
  int iLapsAheadCnt; // [esp+38h] [ebp-70h]
  tBlockHeader *pSpeedDigitBlockHdr; // [esp+3Ch] [ebp-6Ch]
  int iHeight; // [esp+40h] [ebp-68h]
  int iSavedScrSize; // [esp+44h] [ebp-64h]
  int iSpeedometerValue; // [esp+48h] [ebp-60h]
  int iTotalDigitWidth; // [esp+4Ch] [ebp-5Ch]
  uint8 *bySpeedometerPtr; // [esp+50h] [ebp-58h]
  tBlockHeader *pDigitBlockHdr; // [esp+54h] [ebp-54h]
  unsigned int uiCarDataOffset; // [esp+58h] [ebp-50h]
  uint8 *byAmmoBarPtr3; // [esp+5Ch] [ebp-4Ch]
  unsigned int uiCarDataOffset2; // [esp+60h] [ebp-48h]
  unsigned int uiCarDataOffset3; // [esp+64h] [ebp-44h]
  unsigned int uiCarDataOffset4; // [esp+68h] [ebp-40h]
  unsigned int uiCarDataOffset5; // [esp+6Ch] [ebp-3Ch]
  uint8 *byAmmoBarPtr4; // [esp+70h] [ebp-38h]
  unsigned int uiDigitArrayOffset; // [esp+74h] [ebp-34h]
  int iBehindLapCnt; // [esp+78h] [ebp-30h]
  tBlockHeader *pLapDigitBlockHdr2; // [esp+7Ch] [ebp-2Ch]
  int iLastDigitIdx2; // [esp+80h] [ebp-28h]
  int iDamage; // [esp+84h] [ebp-24h]
  int v126; // [esp+88h] [ebp-20h]
  int iTimeMinutes; // [esp+8Ch] [ebp-1Ch]
  int iSpriteRowIdx; // [esp+90h] [ebp-18h]

  byScreenPtr = pScrBuf;
  iCarIndex_1 = iPlayerCarIdx;
  iCarIdx = ViewType[0] != iPlayerCarIdx;
  if (winh < 200 || (textures_off & TEX_OFF_PANEL_RESTRICTED) != 0)// TEX_OFF_PANEL_RESTRICTED
  {
    iSavedScrSize = scr_size;
    iCarIndex = iCarIndex_1;
    byCarDesignIdx = Car[iCarIndex_1].byCarDesignIdx;// Get car design index for ammo display
    scr_size = 64;
    if (byCarDesignIdx >= 8u)                 // Check if car has cheat weapons (design index 8+)
    {
      iAmmoBarIdx = 0;
      byAmmoBarPtr4 = byScreenPtr + 1;
      do {
        byAmmoBarPtr = &byAmmoBarPtr4[winw * (winh - 8)];// Draw ammo bar border (top)
        memset(byAmmoBarPtr, 112, 7u);
        iAmmoBarRowIdx = 0;
        byAmmoBarRowPtr = &byAmmoBarPtr[winw];
        do {
          *byAmmoBarRowPtr = 112;               // Draw ammo bar fill based on remaining ammunition
          if (Car[iCarIndex].byCheatAmmo > iAmmoBarIdx)
            memset(byAmmoBarRowPtr + 1, 171, 5u);
          iWinWidth = winw;
          ++iAmmoBarRowIdx;
          byAmmoBarRowPtr[6] = 112;
          byAmmoBarRowPtr += iWinWidth;
        } while (iAmmoBarRowIdx < 5);
        memset(byAmmoBarRowPtr, 112, 7u);
        ++iAmmoBarIdx;
        byAmmoBarPtr4 += 8;
      } while (iAmmoBarIdx < 8);
    }
    if ((textures_off & TEX_OFF_KMH) != 0)          // TEX_OFF_KMH
    {
      sprintf(buffer, "%3.0f", (double)fabs(Car[iCarIndex_1].fMaxSpeed * 15.0 * 0.041666668));// Display speed in km/h (convert from internal units)
      mini_prt_string(rev_vga[0], buffer, winw - 34, winh - 8);
      szSpeedUnit = szKmh;
    } else {
      sprintf(buffer, "%3.0f", (double)fabs(Car[iCarIndex_1].fMaxSpeed * 0.3333333333333333));// Display speed in mph (convert from internal units)
      mini_prt_string(rev_vga[0], buffer, winw - 34, winh - 8);
      szSpeedUnit = szMph;
    }
    mini_prt_string(rev_vga[0], szSpeedUnit, winw - 18, winh - 8);
    mini_prt_right(rev_vga[0], &language_buffer[1536], winw - 10, winh - 16);
    byGearAyMax = Car[iCarIndex_1].byGearAyMax; // Display current gear (N, R, or 1-max)
    if (byGearAyMax < 0) {
      if (byGearAyMax == -1)
        sprintf(buffer, "N");
      else
        sprintf(buffer, "R");
    } else {
      sprintf(buffer, "%1i", byGearAyMax + 1);
    }
    mini_prt_string(rev_vga[0], buffer, winw - 8, winh - 16);
    mini_prt_string(rev_vga[0], "R", winw - 30, winh - 24);
    byRPMBarPtr = &byScreenPtr[winw - 24 + winw * (winh - 24)];
    dCameraDist = Car[iCarIndex_1].fCameraDistance * 21.0;// Calculate RPM bar length from camera distance
    //_CHP();
    v126 = (int)dCameraDist;
    if ((int)dCameraDist > 20)
      v126 = 20;
    for (i = 0; i < 7; ++i) {
      if (i && i != 6) {
        uiRPMBarWidth = v126;
        byRPMBarFillPtr = byRPMBarPtr + 1;
        *byRPMBarPtr = 112;
        iRPMBarIdx = 255;
        byRPMBarPtr[21] = 112;
      } else {
        iRPMBarIdx = 112;
        byRPMBarFillPtr = byRPMBarPtr;
        uiRPMBarWidth = 22;
      }
      memset(byRPMBarFillPtr, iRPMBarIdx, uiRPMBarWidth);
      byRPMBarPtr += winw;
    }
    do_blip(iCarIdx);
    mini_prt_string(rev_vga[0], "D", winw - 30, winh - 32);
    byDamageBarPtr = &byScreenPtr[winw - 24 + winw * (winh - 32)];
    dDamage = (100.0 - Car[iCarIndex_1].fHealth) * 21.0 * 0.0099999998;// Calculate damage bar length from car health (100 - health)
    //_CHP();
    iDamage = (int)dDamage;
    if ((int)dDamage > 20)
      iDamage = 20;
    for (j = 0; j < 7; ++j) {
      if (j && j != 6) {
        uiDamageBarWidth = iDamage;
        byDamageBarFillPtr = byDamageBarPtr + 1;
        *byDamageBarPtr = 112;
        iDamageBarIdx = 231;
        byDamageBarPtr[21] = 112;
      } else {
        iDamageBarIdx = 112;
        byDamageBarFillPtr = byDamageBarPtr;
        uiDamageBarWidth = 22;
      }
      memset(byDamageBarFillPtr, iDamageBarIdx, uiDamageBarWidth);
      byDamageBarPtr += winw;
    }
    mini_prt_right(rev_vga[0], &language_buffer[256], winw - 14, 4);
    byLap = (char)Car[iCarIndex_1].byLap;
    if (byLap <= 0)
      byLap = 1;
    if (byLap > 99)
      byLap = 99;
    sprintf(buffer, "%2i", byLap);
    mini_prt_string(rev_vga[0], buffer, winw - 12, 4);
    if (game_type >= 2) {
      iLapNumber = 1;
      uiCarDataOffset3 = sizeof(tCar) * iCarIndex_1;
      uiCarDataOffset = sizeof(tCar) * iCarIndex_1;
      iLapTimeYPos = 8;
      iTrialTimeIdx = 24 * iCarIndex_1 + 4;
      do {
        sprintf(buffer, "%s %i", &language_buffer[256], iLapNumber);
        mini_prt_string(rev_vga[0], buffer, 2, iLapTimeYPos);
        if (iLapNumber < (char)Car[uiCarDataOffset / 0x134].byLap) {
          dLapTime = trial_times[iTrialTimeIdx / sizeof(float)] * 100.0;
          //dLapTime = *(float *)((char *)trial_times + iTrialTimeIdx) * 100.0;
          //_CHP();

          int iLapTimeCentiseconds = (int)dLapTime;
          int iMinutes = iLapTimeCentiseconds / 6000;  // 60 seconds * 100 centiseconds
          int iSeconds = (iLapTimeCentiseconds / 100) % 60;
          int iCentiseconds = iLapTimeCentiseconds % 100;
          sprintf(buffer, "%02d:%02d:%02d", iMinutes, iSeconds, iCentiseconds);
          mini_prt_string(rev_vga[0], buffer, 30, iLapTimeYPos);
          //buffer[8] = 0;
          //LODWORD(llLapTimeInt) = (int)dLapTime;
          //HIDWORD(llLapTimeInt) = (int)dLapTime >> 31;
          //buffer[7] = llLapTimeInt % 10 + 48;
          //LODWORD(llLapTimeInt) = (int)dLapTime;
          //buffer[6] = (int)(llLapTimeInt / 10) % 10 + 48;
          //buffer[5] = 58;
          //buffer[4] = (int)(llLapTimeInt / 10) / 10 % 10 + 48;
          //buffer[3] = (int)(llLapTimeInt / 10) / 10 / 10 % 6 + 48;
          //iTimeMinutes = (int)(llLapTimeInt / 10) / 10 / 10 / 6;
          //buffer[1] = iTimeMinutes % 10 + 48;
          //buffer[2] = 58;
          //buffer[0] = iTimeMinutes / 10 % 10 + 48;
          //mini_prt_string(rev_vga[0], buffer, 30, iLapTimeYPos);
        }
        if (iLapNumber == (char)Car[uiCarDataOffset3 / 0x134].byLap) {
          dRunningLapTime = Car[uiCarDataOffset3 / 0x134].fRunningLapTime * 100.0;
          //_CHP();

          int iLapTimeCentiseconds = (int)dRunningLapTime;
          int iMinutes = iLapTimeCentiseconds / 6000;  // 60 seconds * 100 centiseconds
          int iSeconds = (iLapTimeCentiseconds / 100) % 60;
          int iCentiseconds = iLapTimeCentiseconds % 100;
          sprintf(buffer, "%02d:%02d:%02d", iMinutes, iSeconds, iCentiseconds);
          mini_prt_string(rev_vga[0], buffer, 30, iLapTimeYPos);
          //LODWORD(llRunningLapTimeInt) = (int)dRunningLapTime;
          //HIDWORD(llRunningLapTimeInt) = (int)dRunningLapTime >> 31;
          //buffer[7] = llRunningLapTimeInt % 10 + 48;
          //LODWORD(llRunningLapTimeInt) = (int)dRunningLapTime;
          //buffer[5] = 58;
          //buffer[6] = (int)(llRunningLapTimeInt / 10) % 10 + 48;
          //buffer[4] = (int)(llRunningLapTimeInt / 10) / 10 % 10 + 48;
          //buffer[2] = 58;
          //buffer[3] = (int)(llRunningLapTimeInt / 10) / 10 / 10 % 6 + 48;
          //iTimeMinutes = (int)(llRunningLapTimeInt / 10) / 10 / 10 / 6;
          //buffer[1] = iTimeMinutes % 10 + 48;
          //buffer[8] = 0;
          //buffer[0] = iTimeMinutes / 10 % 10 + 48;
          //mini_prt_string(rev_vga[0], buffer, 30, iLapTimeYPos);
        }
        iTrialTimeIdx += 4;
        ++iLapNumber;
        iLapTimeYPos += 8;
      } while (iLapNumber < 6);
      scr_size = iSavedScrSize;
    } else {
      mini_prt_right(rev_vga[0], &language_buffer[1408], winw - 14, 12);
      sprintf(buffer, "%2i", Car[iCarIndex_1].byRacePosition + 1);
      mini_prt_string(rev_vga[0], buffer, winw - 12, 12);
      mini_prt_right(rev_vga[0], &language_buffer[1472], winw - 14, 20);
      sprintf(buffer, "%2i", (char)Car[iCarIndex_1].byLives);
      mini_prt_string(rev_vga[0], buffer, winw - 12, 20);
      scr_size = iSavedScrSize;
    }
  } else {
    if (showversion)
      prt_string(rev_vga[1], VersionString, 150, 190);
    iMainCarIdx = iCarIndex_1;                  // Full resolution panel mode - render detailed HUD elements
    if (Car[iCarIndex_1].byCarDesignIdx >= 8u) {
      iAmmoBarIdx2 = 0;
      byAmmoBarPtr3 = byScreenPtr + 1;
      do {
        byAmmoBarPtr2 = &byAmmoBarPtr3[winw * (winh - 8)];
        memset(byAmmoBarPtr2, 112, 7u);
        byAmmoBarRowPtr2 = &byAmmoBarPtr2[winw];
        for (iAmmoBarRowIdx2 = 0; iAmmoBarRowIdx2 < 5; ++iAmmoBarRowIdx2) {
          *byAmmoBarRowPtr2 = 112;
          if (Car[iMainCarIdx].byCheatAmmo > iAmmoBarIdx2)
            memset(byAmmoBarRowPtr2 + 1, 171, 5u);
          iWinWidth2 = winw;
          byAmmoBarRowPtr2[6] = 112;
          byAmmoBarRowPtr2 += iWinWidth2;
        }
        memset(byAmmoBarRowPtr2, 112, 7u);
        ++iAmmoBarIdx2;
        byAmmoBarPtr3 += 8;
      } while (iAmmoBarIdx2 < 8);
    }
    if (player_type == 2 || (cheat_mode & CHEAT_MODE_WIDESCREEN) != 0)// CHEAT_MODE_WIDESCREEN
      iBaseXPos = (winw / 4) + 157;  // Calculate base X position for speedometer (adjusted for widescreen)
      //iBaseXPos = ((winw - (__CFSHL__(winw >> 31, 2) + 4 * (winw >> 31))) >> 2) + 157;// Calculate base X position for speedometer (adjusted for widescreen)
    else
      iBaseXPos = 157;
    pDigitBlockHdr = rev_vga[2];
    pSpeedDigitBlockHdr = rev_vga[2];
    if ((textures_off & TEX_OFF_KMH) != 0)          // TEX_OFF_KMH
      dSpeedometer = fabs(Car[iCarIndex_1].fMaxSpeed * 0.33333334) * 15.0 * 0.125;// Calculate speedometer value (km/h with additional scaling factor)
    else
      dSpeedometer = fabs(Car[iCarIndex_1].fMaxSpeed * 0.33333334);// Calculate speedometer value (mph)
    //_CHP();
    iSpeedometerValue = (int)dSpeedometer;
    iSpeedDisplayValue = (int)dSpeedometer;
    iSpeedDigitIdx = 0;
    iDigitArrayIdx = 0;
    iTotalDigitWidth = 0;
    do {
      iDigitArray[iDigitArrayIdx] = iSpeedDisplayValue % 10;// Extract individual digits and calculate total width for centering
      iTotalDigitWidth += pSpeedDigitBlockHdr[iSpeedDisplayValue % 10 + 9].iWidth - 1;
      ++iDigitArrayIdx;
      ++iSpeedDigitIdx;
      iSpeedDisplayValue /= 10;
    } while (iSpeedDisplayValue > 0);
    iLastDigitIdx = iSpeedDigitIdx - 1;
    iLastDigitIdx2 = iLastDigitIdx;
    bySpeedometerPtr = &byScreenPtr[winw * ((155 * scr_size) >> 6) + winw - ((44 * scr_size) >> 6)];
    if (iTotalDigitWidth > 0) {
      uiDigitArrayOffset = 4 * iLastDigitIdx;
      do {
        iSpriteRowIdx = 0;                      // Render each digit sprite with scaling
        pBlockHdr = &pSpeedDigitBlockHdr[iDigitArray[uiDigitArrayOffset / 4] + 9];// Render speedometer digits using sprite blocks
        iScaledSize = scr_size;
        iWidth = pBlockHdr->iWidth;
        iHeight = pBlockHdr->iHeight;
        byDigitPixelPtr = bySpeedometerPtr;
        bySpriteDataPtr = (uint8 *)pDigitBlockHdr + pBlockHdr->iDataOffset;
        bySpeedometerPtr += (scr_size * (iWidth - 1)) >> 6;
        if (iHeight > 0) {
          do {
            iPixelXOffset = scr_size;
            byPixelRowPtr = byDigitPixelPtr;
            bySpriteRowPtr = bySpriteDataPtr;
            iPixelXIdx = 0;
            while (iPixelXIdx < iWidth) {
              if (*bySpriteDataPtr)
                *byDigitPixelPtr = *bySpriteDataPtr;
              iPixelXOffset -= 64;
              ++byDigitPixelPtr;
              for (; iPixelXOffset <= 0; ++iPixelXIdx) {
                ++bySpriteDataPtr;
                iPixelXOffset += scr_size;
              }
            }
            iScaledSize -= 64;
            for (bySpriteDataPtr = bySpriteRowPtr; iScaledSize <= 0; ++iSpriteRowIdx) {
              bySpriteDataPtr += iWidth;
              iScaledSize += scr_size;
            }
            byDigitPixelPtr = &byPixelRowPtr[winw];
          } while (iSpriteRowIdx < iHeight);
        }
        iTotalDigitWidth -= iWidth;
        uiDigitArrayOffset -= 4;
        --iLastDigitIdx2;
      } while (iTotalDigitWidth > 0);
    }
    if ((textures_off & TEX_OFF_KMH) != 0)          // TEX_OFF_KMH
      iSpeedUnitBlkIdx = 32;
    else
      iSpeedUnitBlkIdx = 33;
    print_block(&byScreenPtr[winw * ((172 * scr_size) >> 6) + winw - ((25 * scr_size) >> 6)], rev_vga[2], iSpeedUnitBlkIdx);// Display speed unit icon (km/h or mph)
    pLifeIconBlockHdr = rev_vga[4];
    iLifeIconIdx = 0;
    iLifeIconYPos = 54;
    uiCarDataOffset5 = 308 * iCarIndex_1;
    iKillsDisplayValue = Car[iCarIndex_1].byCarDesignIdx;
    while (iLifeIconIdx < (char)Car[uiCarDataOffset5 / 0x134].byLives) {                                           // Draw life icons for current car
      if (iKillsDisplayValue >= 8) {
        iKillIconIdx = 8;
        pKillBlockHdr = pLifeIconBlockHdr;
      } else {
        pKillBlockHdr = pLifeIconBlockHdr;
        iKillIconIdx = iKillsDisplayValue;
      }
      print_block(&byScreenPtr[winw * ((iLifeIconYPos * scr_size) >> 6) + ((8 * scr_size) >> 6)], pKillBlockHdr, iKillIconIdx);
      iLifeIconYPos += 20;
      ++iLifeIconIdx;
    }
    pPositionBlockHdr = rev_vga[4];
    if (Car[uiCarDataOffset5 / 0x134].byKills >= 9u)// Display kills - either as individual icons or as two-digit number
    {
      print_block(&byScreenPtr[winw * ((178 * scr_size) >> 6) + winw - ((144 * scr_size) >> 6)], rev_vga[4], 8);
      byKills = Car[uiCarDataOffset5 / 0x134].byKills;
      byKillsScreenPtr = byScreenPtr;
      pKillsDigitBlockHdr = rev_vga[2];
      print_block(&byScreenPtr[winw * ((178 * scr_size) >> 6) + winw - ((122 * scr_size) >> 6)], rev_vga[2], byKills / 10 + 9);
      print_block(&byKillsScreenPtr[winw * ((178 * scr_size) >> 6) + winw - ((110 * scr_size) >> 6)], pKillsDigitBlockHdr, byKills % 10 + 9);
    } else {
      iRacePosition = 100;
      iKillIconLoopIdx = 0;
      iCarIdxForKills = iCarIndex_1;
      while (iKillIconLoopIdx < Car[iCarIdxForKills].byKills) {
        ++iKillIconLoopIdx;
        byKillIconPtr = &byScreenPtr[winw * ((178 * scr_size) >> 6) + winw - ((iRacePosition * scr_size) >> 6)];
        iRacePosition += 22;
        print_block(byKillIconPtr, pPositionBlockHdr, 8);
      }
    }
    iGearCarIdx = iCarIndex_1;
    print_damage(&byScreenPtr[winw * (scr_size << 7 >> 6) + winw - ((80 * scr_size) >> 6)], rev_vga[2], iCarIdx);// Display damage indicator and gear display
    byGearScreenPtr = byScreenPtr;
    print_block(&byScreenPtr[winw * ((181 * scr_size) >> 6) + winw - ((14 * scr_size) >> 6)], rev_vga[2], (char)Car[iGearCarIdx].byGearAyMax + 3);
    print_block(&byGearScreenPtr[winw * ((21 * scr_size) >> 6) + winw - ((67 * scr_size) >> 6)], rev_vga[2], 19);
    pLapBlockHdr = rev_vga[2];
    iCurrentLap = (char)Car[iGearCarIdx].byLap;
    pLapDigitBlockHdr = rev_vga[2];
    if (iCurrentLap <= 0)
      iCurrentLap = 1;
    if (iCurrentLap > 99)
      iCurrentLap = 99;
    if (iCurrentLap >= 10)
      iLapDigitWidth = rev_vga[2][iCurrentLap / 10 + 22].iWidth + rev_vga[2][iCurrentLap % 10 + 22].iWidth - 1;
    else
      iLapDigitWidth = rev_vga[2][iCurrentLap + 22].iWidth;
    iLapXOffset = (scr_size * (iLapDigitWidth / 2 + 36)) >> 6;
    byLapDisplayPtr = &byScreenPtr[winw * ((25 * scr_size) >> 6) + winw - iLapXOffset];
    if (iCurrentLap >= 10) {
      iTimeMinutes = iCurrentLap / 10 + 22;
      print_block(&byScreenPtr[winw * ((25 * scr_size) >> 6) + winw - iLapXOffset], rev_vga[2], iTimeMinutes);
      byLapDisplayPtr += winw * (pLapDigitBlockHdr[iTimeMinutes].iWidth - 1) / 320;
      iLapDigitIdx = iCurrentLap % 10 + 22;
    } else {
      iLapDigitIdx = iCurrentLap + 22;
    }
    print_block(byLapDisplayPtr, pLapBlockHdr, iLapDigitIdx);
    byRaceScreenPtr = byScreenPtr;
    print_block(&byScreenPtr[winw * ((5 * scr_size) >> 6) + winw - ((52 * scr_size) >> 6)], rev_vga[2], 20);
    iTimingCarIdx = iCarIndex_1;
    if (game_type >= 2)                       // Time trial mode - display lap times for multiple laps
    {
      iLapNum2 = 1;
      uiCarDataOffset4 = 308 * iCarIndex_1;
      uiCarDataOffset2 = 308 * iCarIndex_1;
      iLapTimeYPos2 = 8;
      iTrialTimeIdx2 = 24 * iCarIndex_1 + 4;
      do {
        sprintf(buffer, "%s %i", &language_buffer[256], iLapNum2);
        mini_prt_string(rev_vga[0], buffer, 8, iLapTimeYPos2);
        if (iLapNum2 < (char)Car[uiCarDataOffset2 / 0x134].byLap) {
          dLapTime2 = trial_times[iTrialTimeIdx2 / sizeof(float)] * 100.0;
          //dLapTime2 = *(float *)((char *)trial_times + iTrialTimeIdx2) * 100.0;
          //_CHP();
          int iLapTimeCentiseconds = (int)dLapTime2;
          int iMinutes = iLapTimeCentiseconds / 6000;  // 60 seconds * 100 centiseconds
          int iSeconds = (iLapTimeCentiseconds / 100) % 60;
          int iCentiseconds = iLapTimeCentiseconds % 100;
          sprintf(buffer, "%02d:%02d:%02d", iMinutes, iSeconds, iCentiseconds);
          mini_prt_string(rev_vga[0], buffer, 40, iLapTimeYPos2);
          //buffer[8] = 0;
          //LODWORD(llLapTimeInt2) = (int)dLapTime2;
          //HIDWORD(llLapTimeInt2) = (int)dLapTime2 >> 31;
          //buffer[7] = llLapTimeInt2 % 10 + 48;
          //LODWORD(llLapTimeInt2) = (int)dLapTime2;
          //buffer[6] = (int)(llLapTimeInt2 / 10) % 10 + 48;
          //buffer[5] = 58;
          //buffer[4] = (int)(llLapTimeInt2 / 10) / 10 % 10 + 48;
          //buffer[3] = (int)(llLapTimeInt2 / 10) / 10 / 10 % 6 + 48;
          //buffer[2] = 58;
          //iTimeMinutes = (int)(llLapTimeInt2 / 10) / 10 / 10 / 6;
          //buffer[1] = iTimeMinutes % 10 + 48;
          //buffer[0] = iTimeMinutes / 10 % 10 + 48;
          //mini_prt_string(rev_vga[0], buffer, 40, iLapTimeYPos2);
        }
        if (iLapNum2 == (char)Car[uiCarDataOffset4 / 0x134].byLap) {
          dRunningLapTime2 = Car[uiCarDataOffset4 / 0x134].fRunningLapTime * 100.0;// Display current running lap time
          //_CHP();
          int iLapTimeCentiseconds = (int)dRunningLapTime2;
          int iMinutes = iLapTimeCentiseconds / 6000;  // 60 seconds * 100 centiseconds
          int iSeconds = (iLapTimeCentiseconds / 100) % 60;
          int iCentiseconds = iLapTimeCentiseconds % 100;
          sprintf(buffer, "%02d:%02d:%02d", iMinutes, iSeconds, iCentiseconds);
          mini_prt_string(rev_vga[0], buffer, 40, iLapTimeYPos2);
          //LODWORD(llRunningLapTimeInt2) = (int)dRunningLapTime2;
          //HIDWORD(llRunningLapTimeInt2) = (int)dRunningLapTime2 >> 31;
          //buffer[7] = llRunningLapTimeInt2 % 10 + 48;
          //LODWORD(llRunningLapTimeInt2) = (int)dRunningLapTime2;
          //buffer[6] = (int)(llRunningLapTimeInt2 / 10) % 10 + 48;
          //buffer[4] = (int)(llRunningLapTimeInt2 / 10) / 10 % 10 + 48;
          //buffer[3] = (int)(llRunningLapTimeInt2 / 10) / 10 / 10 % 6 + 48;
          //iTimeMinutes = (int)(llRunningLapTimeInt2 / 10) / 10 / 10 / 6;
          //buffer[1] = iTimeMinutes % 10 + 48;
          //buffer[8] = 0;
          //buffer[5] = 58;
          //buffer[2] = 58;
          //buffer[0] = iTimeMinutes / 10 % 10 + 48;
          //mini_prt_string(rev_vga[0], buffer, 40, iLapTimeYPos2);
        }
        iTrialTimeIdx2 += 4;
        ++iLapNum2;
        iLapTimeYPos2 += 8;
      } while (iLapNum2 < 6);
    } else {
      print_block(&byRaceScreenPtr[winw * ((8 * scr_size) >> 6)], rev_vga[2], 21);// Race mode - display position and lap information
      pPositionDigitBlockHdr = rev_vga[2];
      iPositionValue = Car[iTimingCarIdx].byRacePosition + 1;
      pLapDigitBlockHdr2 = rev_vga[2];
      if (iPositionValue >= 10)
        iPositionDigitWidth = rev_vga[2][23].iWidth + rev_vga[2][iPositionValue % 10 + 22].iWidth - 1;
      else
        iPositionDigitWidth = rev_vga[2][iPositionValue + 22].iWidth;
      iPositionXOffset = (scr_size * (59 - iPositionDigitWidth / 2)) >> 6;
      byPositionDisplayPtr = &byScreenPtr[winw * ((12 * scr_size) >> 6) + iPositionXOffset];
      if (iPositionValue >= 10) {
        print_block(&byScreenPtr[winw * ((12 * scr_size) >> 6) + iPositionXOffset], rev_vga[2], 23);
        byPositionDisplayPtr += (scr_size * (pLapDigitBlockHdr2[23].iWidth - 1)) >> 6;
        iPositionDigitIdx = iPositionValue % 10 + 22;
      } else {
        iPositionDigitIdx = iPositionValue + 22;
      }
      print_block(byPositionDisplayPtr, pPositionDigitBlockHdr, iPositionDigitIdx);
      iPositionCarIdx = iCarIndex_1;
      print_pos(4, 9, Car[iCarIndex_1].byRacePosition - 1);
      print_pos(4, 42, Car[iPositionCarIdx].byRacePosition + 1);
    }
    if (replaytype != 2) {
      iSelectedView = SelectedView[iCarIdx];
      if (iSelectedView != 2 && iSelectedView != 7) {
        iTimingXPos = iBaseXPos - 2;
        prt_right(rev_vga[1], language_buffer, iBaseXPos - 2, 4);
        iLapTimeCarIdx = iCarIndex_1;
        ShowATime(Car[iCarIndex_1].fPreviousLapTime, iBaseXPos, 4);
        prt_right(rev_vga[1], &language_buffer[64], iTimingXPos, 14);
        fBestLapTime = Car[iLapTimeCarIdx].fBestLapTime;
        if (fBestLapTime > 5000.0)
          fBestLapTime = -1.0;
        iTimingBaseXPos = iBaseXPos;
        ShowATime(fBestLapTime, iBaseXPos, 14);
        calculate_aheadbehindtime(iCarIndex_1, &fAheadTime, &fBehindTime);// Calculate time ahead/behind other players
        prt_right(rev_vga[1], &language_buffer[128], iTimingBaseXPos - 2, 24);
        if (fAheadTime >= 10000000.0)         // Display large time differences as lap counts instead of time
        {
          dAheadTimeLaps = fAheadTime * 0.0000001;
          //_CHP();
          iLapsAheadCnt = (int)dAheadTimeLaps;
          if ((int)dAheadTimeLaps == 1)
            sprintf(buffer, "1 %s", &language_buffer[256]);
          else
            sprintf(buffer, "%2i %s", (int)dAheadTimeLaps, &language_buffer[320]);
          prt_string(rev_vga[1], buffer, iBaseXPos, 24);
        } else {
          ShowATime(fAheadTime, iTimingBaseXPos, 24);
        }
        prt_right(rev_vga[1], &language_buffer[192], iBaseXPos - 2, 34);
        if (fBehindTime >= 10000000.0) {
          dBehindTimeLaps = fBehindTime * 0.0000001;
          //_CHP();
          iBehindLapCnt = (int)dBehindTimeLaps;
          if ((int)dBehindTimeLaps == 1)
            sprintf(buffer, "1 %s", &language_buffer[256]);
          else
            sprintf(buffer, "%2i %s", (int)dBehindTimeLaps, &language_buffer[320]);
          prt_string(rev_vga[1], buffer, iBaseXPos, 34);
        } else {
          ShowATime(fBehindTime, iBaseXPos, 34);
        }
      }
    }
    if (network_on && players > 1)            // Display network chat message sender name if in multiplayer
    {
      if (network_mes_mode >= 0)
        szMessageSender = driver_names[network_mes_mode];
      else
        szMessageSender = &language_buffer[3904];
      sprintf(buffer, "%s %s", &language_buffer[3840], szMessageSender);
      prt_string(rev_vga[1], buffer, 2, winh - 12);
    }
  }
  showmap(byScreenPtr, iCarIndex_1);            // Finally render the minimap overlay
}

//-------------------------------------------------------------------------------------------------

void ZoomString(const char *szStr, const char *mappingTable, tBlockHeader *pBlockHeader, int iPlayerIdx, int *pCharVOffsets)
{
  int iSelectedView1; // esi
  int iSelectedView2; // esi
  int iCharIndex; // edx
  double dCharWidth; // st7
  double dNewTextWidth; // st7
  double dScaledWidth; // st7
  const char *pbyCurrentChar; // esi
  int iCharCode; // edx
  uint8 byFontIndex; // bl
  double dSpaceWidth; // st7
  int iSavedZoomY; // [esp+4h] [ebp-24h]
  int iTotalWidth; // [esp+10h] [ebp-18h]
  float fZoomFactor; // [esp+14h] [ebp-14h]
  int iStringDone; // [esp+18h] [ebp-10h]

  if (game_scale[iPlayerIdx] < 32768.0 && zoom_size[iPlayerIdx] || !zoom_size[iPlayerIdx] && game_scale[iPlayerIdx] < 1024.0) {                                             // Check for 2-player mode or widescreen cheat
    if (player_type == 2 || (cheat_mode & CHEAT_MODE_WIDESCREEN) != 0)// CHEAT_MODE_WIDESCREEN
      zoom_x = 320;                             // Set zoom center X to 320 for 2-player/widescreen
    else
      zoom_x = 160;                             // Set zoom center X to 160 for single player
    if (zoom_size[iPlayerIdx])                // Check if large zoom mode is enabled
    {                                           // Check if in intro or 2-player mode
      if (intro || player_type == 2) {
        zoom_y = 84;                            // Set zoom Y to 84 for intro/2-player large zoom
      } else {
        iSelectedView1 = SelectedView[iPlayerIdx];// Get selected view for this player
        if (iSelectedView1 == 1 || iSelectedView1 == 3)// Check if view 1 or 3 (cockpit/bumper views)
          zoom_y = 130;                         // Set zoom Y to 130 for cockpit/bumper large zoom
        else
          zoom_y = 52;                          // Set zoom Y to 52 for external views large zoom
      }
    } else if (intro || player_type == 2)       // Normal zoom: check intro or 2-player mode
    {
      zoom_y = 95;                              // Set zoom Y to 95 for intro/2-player normal zoom
    } else {
      iSelectedView2 = SelectedView[iPlayerIdx];// Get selected view for normal zoom
      if (iSelectedView2 == 1 || iSelectedView2 == 3)// Check if view 1 or 3 for normal zoom
        zoom_y = 130;                           // Set zoom Y to 130 for cockpit/bumper normal zoom
      else
        zoom_y = 63;                            // Set zoom Y to 63 for external views normal zoom
    }
    for (iTotalWidth = 0; *szStr; iTotalWidth = (int)dNewTextWidth)// Calculate total text width for centering
    {
      iCharIndex = (uint8)mappingTable[*(uint8 *)szStr];// Get font index for current character
      if (iCharIndex == 255)                  // Check if character is invalid (255 = space)
        dCharWidth = 512.0;                     // Use fixed 512.0 width for space character
      else
        dCharWidth = (double)((pBlockHeader[iCharIndex].iWidth + 1) << 6);// Get character width from font data, add 1 pixel spacing
      dNewTextWidth = dCharWidth / game_scale[iPlayerIdx] + (double)iTotalWidth;// Scale character width and accumulate total
      //_CHP();
    }
    if (iTotalWidth <= 310)                   // Check if total width fits within 310 pixels
    {
      fZoomFactor = game_scale[iPlayerIdx];     // Use normal game scale factor
    } else {
      dScaledWidth = (double)((iTotalWidth << 6) / 310);// Calculate compressed scale to fit in 310 pixels
      iTotalWidth = 310;                        // Clamp total width to 310 pixels
      fZoomFactor = (float)dScaledWidth;               // Store compressed zoom factor
    }
    pbyCurrentChar = szStr;                     // Initialize text pointer for rendering
    zoom_x -= iTotalWidth / 2;                  // Center text horizontally by subtracting half width
    iStringDone = 0;                            // Initialize string completion flag
    do {                                           // Check if current character is not null terminator
      if (*pbyCurrentChar) {                                         // Check if character is not newline
        if (*pbyCurrentChar != '\n') {
          iCharCode = *(uint8 *)pbyCurrentChar;// Get character code as unsigned byte
          byFontIndex = mappingTable[iCharCode];// Look up font index in mapping table
          if (byFontIndex == 0xFF)            // Check if font index is invalid (0xFF)
          {
            dSpaceWidth = 512.0 / game_scale[iPlayerIdx] + (double)zoom_x;// Calculate space width and advance zoom X
            //_CHP();
            zoom_x = (int)dSpaceWidth;          // Update global zoom X position
          } else {
            iSavedZoomY = zoom_y;               // Save current zoom Y position
            zoom_y += pCharVOffsets[byFontIndex];// Adjust zoom Y by character vertical offset
            zoom_letter(pBlockHeader, iCharCode, &zoom_x, &zoom_y, mappingTable, fZoomFactor);// Render the character with zoom scaling
            zoom_y = iSavedZoomY;               // Restore original zoom Y position
          }
        }
      } else {
        iStringDone = -1;                       // Set string done flag (null terminator found)
      }
      ++pbyCurrentChar;                         // Move to next character in string
    } while (!iStringDone);                     // Continue until string is complete
  }
}

//-------------------------------------------------------------------------------------------------

void ZoomSub(const char *szText, const char *mappingTable, tBlockHeader *pBlockHeader, int iPlayerIdx, int *pCharVOffsets)
{
  double dZoomDivisor; // st7
  double dNewZoomY; // st7
  const char *pbyTextPtr; // eax
  int iCharIndex; // edx
  double dCharWidth; // st7
  double dNewTextWidth; // st7
  double dScaledWidth; // st7
  const char *pbyCurrentChar; // esi
  int iCharCode; // edx
  uint8 byFontIndex; // bl
  double dSpaceWidth; // st7
  int iSavedZoomY; // [esp+4h] [ebp-24h]
  float fZoomFactor; // [esp+10h] [ebp-18h]
  int iStringDone; // [esp+14h] [ebp-14h]
  int iTotalWidth; // [esp+18h] [ebp-10h]

  if (game_scale[iPlayerIdx] < 1024.0) {                                             // Check for 2-player mode or cheat flag 0x40
    if (player_type == 2 || (cheat_mode & CHEAT_MODE_WIDESCREEN) != 0)// CHEAT_MODE_WIDESCREEN
      zoom_x = 320;                             // Set zoom center X to 320 for 2-player/cheat mode
    else
      zoom_x = 160;                             // Set zoom center X to 160 for single player
    if (zoom_size[iPlayerIdx])                // Check zoom size setting for this player
      dZoomDivisor = 2048.0;                    // Use 2048.0 divisor for large zoom
    else
      dZoomDivisor = 1024.0;                    // Use 1024.0 divisor for normal zoom
    dNewZoomY = dZoomDivisor / game_scale[iPlayerIdx] + (double)zoom_y;// Calculate new zoom Y position with scaling
    //_CHP();
    zoom_y = (int)dNewZoomY;                    // Update global zoom Y position

    pbyTextPtr = szText;  // MISSING compiler artifact

    for (iTotalWidth = 0; *pbyTextPtr; iTotalWidth = (int)dNewTextWidth)// Calculate total text width for centering
    {
      iCharIndex = (uint8)mappingTable[*(uint8 *)pbyTextPtr];// Get font index for current character
      if (iCharIndex == 255)                  // Check if character is invalid (255 = space)
        dCharWidth = 512.0;                     // Use fixed 512.0 width for space character
      else
        dCharWidth = (double)((pBlockHeader[iCharIndex].iWidth + 1) << 6);// Get character width from font data, add 1 pixel spacing
      dNewTextWidth = dCharWidth / game_scale[iPlayerIdx] + (double)iTotalWidth;// Scale character width and accumulate total
      //_CHP();
    }
    if (iTotalWidth <= 310)                   // Check if total width fits within 310 pixels
    {
      fZoomFactor = game_scale[iPlayerIdx];     // Use normal game scale factor
    } else {
      dScaledWidth = (double)((iTotalWidth << 6) / 310);// Calculate compressed scale to fit in 310 pixels
      iTotalWidth = 310;                        // Clamp total width to 310 pixels
      fZoomFactor = (float)dScaledWidth;               // Store compressed zoom factor
    }
    pbyCurrentChar = szText;                    // Initialize text pointer for rendering
    zoom_x -= iTotalWidth / 2;                  // Center text horizontally by subtracting half width
    iStringDone = 0;                            // Initialize string completion flag
    do {                                           // Check if current character is not null terminator
      if (*pbyCurrentChar) {                                         // Check if character is not newline (10)
        if (*pbyCurrentChar != '\n') {
          iCharCode = *(uint8 *)pbyCurrentChar;// Get character code as unsigned byte
          byFontIndex = mappingTable[iCharCode];// Look up font index in mapping table
          if (byFontIndex == 0xFF)            // Check if font index is invalid (0xFF)
          {
            dSpaceWidth = 512.0 / game_scale[iPlayerIdx] + (double)zoom_x;// Calculate space width and advance zoom X
            //_CHP();
            zoom_x = (int)dSpaceWidth;          // Update global zoom X position
          } else {
            iSavedZoomY = zoom_y;               // Save current zoom Y position
            zoom_y += pCharVOffsets[byFontIndex];// Adjust zoom Y by character vertical offset
            zoom_letter(pBlockHeader, iCharCode, &zoom_x, &zoom_y, mappingTable, fZoomFactor);// Render the character with zoom scaling
            zoom_y = iSavedZoomY;               // Restore original zoom Y position
          }
        }
      } else {
        iStringDone = -1;                       // Set string done flag (null terminator found)
      }
      ++pbyCurrentChar;                         // Move to next character in string
    } while (!iStringDone);                     // Continue until string is complete
  }
}

//-------------------------------------------------------------------------------------------------

void zoom_letter(tBlockHeader *pBlockHeader, uint8 byCharCode, int *puiXPos, int *puiYPos, const char *mappingTable, float fZoomFactor)
{
  int byCharIndex; // esi
  int iScreenWidth; // ebx
  int iCharWidth; // edi
  uint8 *pbyScreenPos; // ecx
  int iXOffset; // edx
  uint8 *pbyCharData; // eax
  int iRow; // ebp
  uint8 *pbyPixel; // esi
  int iCol; // edx
  int iScaledWidth; // eax
  int *puiXPos_1; // edx
  int iCharHeight; // [esp+Ch] [ebp-20h]
  uint8 *pbyRowStart; // [esp+10h] [ebp-1Ch]
  uint8 *pbyCharRowStart; // [esp+14h] [ebp-18h]
  int iVertZoom; // [esp+18h] [ebp-14h]
  int iHorizZoom; // [esp+1Ch] [ebp-10h]

  byCharIndex = (uint8)mappingTable[byCharCode];// Get character index from font table
  if (byCharIndex == 255)                     // Check if character is invalid (255 = no character)
  {
    *puiXPos += 8;                              // Advance X position by space width (8 pixels)
  } else {                                             // Check if using special ASCII conversion font
    if (mappingTable == ascii_conv3)
      iScreenWidth = 64;                        // Use fixed 64-pixel width for ASCII conversion
    else
      iScreenWidth = scr_size;                  // Use normal screen size for scaling
    iCharWidth = pBlockHeader[byCharIndex].iWidth;// Get character width from font data (12-byte struct per char)
    iCharHeight = pBlockHeader[byCharIndex].iHeight;// Get character height from font data (+4 offset)

    pbyCharData = (uint8 *)pBlockHeader + pBlockHeader[byCharIndex].iDataOffset; //MISSING decompiler artifact

    pbyScreenPos = &screen_pointer[winw * ((scr_size * *puiYPos) >> 6)];// Calculate screen position: Y offset with scaling
    iXOffset = scr_size * *puiXPos;             // Calculate X offset with scaling
    //_CHP();
    iVertZoom = iScreenWidth;                   // Initialize vertical zoom counter
    iRow = 0;                                   // Initialize row counter
    for (pbyPixel = &pbyScreenPos[iXOffset >> 6]; iRow < iCharHeight; pbyPixel = &pbyRowStart[winw])// Loop through each row of the character
    {
      iHorizZoom = iScreenWidth;                // Reset horizontal zoom counter for this row
      pbyRowStart = pbyPixel;
      pbyCharRowStart = pbyCharData;
      iCol = 0;                                 // Initialize column counter
      while (iCol < iCharWidth)               // Loop through each column of the character
      {                                         // Check if pixel is set in character data
        if (*pbyCharData)
          *pbyPixel = *pbyCharData;             // Copy pixel to screen buffer
        //_CHP();
        iHorizZoom = (int)((double)iHorizZoom - fZoomFactor);// Apply horizontal zoom scaling
        ++pbyPixel;                             // Move to next screen pixel
        for (; iHorizZoom <= 0; iHorizZoom += iScreenWidth)// Check if zoom counter requires advancing char data
        {
          ++pbyCharData;                        // Advance to next character data pixel
          ++iCol;
        }
      }
      //_CHP();
      iVertZoom = (int)((double)iVertZoom - fZoomFactor);// Apply vertical zoom scaling
      for (pbyCharData = pbyCharRowStart; iVertZoom <= 0; iVertZoom += iScreenWidth)// Check if zoom counter requires advancing to next row
      {
        ++iRow;                                 // Move to next character row
        pbyCharData += iCharWidth;              // Skip to next row in character data
      }
    }
    if (mappingTable == ascii_conv3)          // Handle different width calculation for ASCII conversion
    {
      iScaledWidth = ((int)((double)(iCharWidth << 6) / fZoomFactor) << 6) / scr_size;// Calculate scaled width with screen size division
      puiXPos_1 = puiXPos;
    } else {
      puiXPos_1 = puiXPos;
      iScaledWidth = (int)((double)(iCharWidth << 6) / fZoomFactor);// Calculate scaled width without screen size division
    }
    *puiXPos_1 += iScaledWidth;                 // Advance X position by calculated character width
  }
}

//-------------------------------------------------------------------------------------------------

void print_block(uint8 *pDest, tBlockHeader *pBlockHeader, int iBlockIdx)
{
  int iScreenSize; // edi
  int iRowScaleAccum; // ebp
  uint8 *pszSourceData; // ebx
  int iFullBytesPerRow; // ebp
  int iRemainingPixels; // edx
  int j; // eax
  uint8 byPixel; // cl
  uint8 *pszSrc1; // ebx
  uint8 *pszDest1; // esi
  uint8 byPixel1; // cl
  uint8 *pszSrc2; // ebx
  uint8 *pbyDest2; // esi
  uint8 byPixel2; // cl
  uint8 *pszSrc3; // ebx
  uint8 *pbyDest3; // esi
  uint8 byPixel3; // cl
  char *pszSrc4; // ebx
  uint8 *pbyDest4; // esi
  uint8 byPixel4; // cl
  char *pszSrc5; // ebx
  uint8 *pbyDest5; // esi
  uint8 byPixel5; // cl
  char *pszSrc6; // ebx
  uint8 *pbyDest6; // esi
  uint8 byPixel6; // cl
  uint8 *pszSrc7; // ebx
  uint8 *pbyDest7; // esi
  uint8 byPixel7; // cl
  int k; // eax
  uint8 byRemPixel; // cl
  int iColScaleAccum; // eax
  int iXPos; // edx
  int iWidth; // [esp+0h] [ebp-28h]
  uint8 *pszRowStart; // [esp+4h] [ebp-24h]
  uint8 *pszDestRow; // [esp+8h] [ebp-20h]
  int iHeight; // [esp+Ch] [ebp-1Ch]
  int i; // [esp+10h] [ebp-18h]
  int m; // [esp+14h] [ebp-14h]

  iScreenSize = scr_size;                       // Store current screen scaling size
  iWidth = pBlockHeader[iBlockIdx].iWidth;      // Extract block dimensions from header
  iHeight = pBlockHeader[iBlockIdx].iHeight;
  iRowScaleAccum = scr_size;
  pszSourceData = (uint8 *)pBlockHeader + pBlockHeader[iBlockIdx].iDataOffset;// Calculate pointer to block pixel data
  if (scr_size == 64)                         // Branch: 64 = 1:1 pixel mode, else = scaled mode
  {
    iFullBytesPerRow = iWidth / 8;  // Number of complete 8-pixel chunks per row
    //iFullBytesPerRow = (iWidth - (__CFSHL__(iWidth >> 31, 3) + 8 * (iWidth >> 31))) >> 3;// Calculate 8-pixel chunks per row (optimized copying)
    iRemainingPixels = iWidth % 8;              // Calculate remaining pixels after 8-pixel chunks
    for (i = 0; i < iHeight; ++i)             // Process each row of the block
    {                                           // Process 8-pixel chunks for efficiency (unrolled loop)
      for (j = 0; j < iFullBytesPerRow; pDest = pbyDest7 + 1) {
        byPixel = *pszSourceData;               // Copy 8 pixels in sequence, skipping transparent (0) pixels
        pszSrc1 = pszSourceData + 1;
        if (byPixel)
          *pDest = byPixel;
        pszDest1 = pDest + 1;
        byPixel1 = *pszSrc1;
        pszSrc2 = pszSrc1 + 1;
        if (byPixel1)
          *pszDest1 = byPixel1;
        pbyDest2 = pszDest1 + 1;
        byPixel2 = *pszSrc2;
        pszSrc3 = pszSrc2 + 1;
        if (byPixel2)
          *pbyDest2 = byPixel2;
        pbyDest3 = pbyDest2 + 1;
        byPixel3 = *pszSrc3;
        pszSrc4 = (char *)(pszSrc3 + 1);
        if (byPixel3)
          *pbyDest3 = byPixel3;
        pbyDest4 = pbyDest3 + 1;
        byPixel4 = *pszSrc4;
        pszSrc5 = pszSrc4 + 1;
        if (byPixel4)
          *pbyDest4 = byPixel4;
        pbyDest5 = pbyDest4 + 1;
        byPixel5 = *pszSrc5;
        pszSrc6 = pszSrc5 + 1;
        if (byPixel5)
          *pbyDest5 = byPixel5;
        pbyDest6 = pbyDest5 + 1;
        byPixel6 = *pszSrc6;
        pszSrc7 = (uint8 *)(pszSrc6 + 1);
        if (byPixel6)
          *pbyDest6 = byPixel6;
        pbyDest7 = pbyDest6 + 1;
        byPixel7 = *pszSrc7;
        pszSourceData = pszSrc7 + 1;
        if (byPixel7)
          *pbyDest7 = byPixel7;
        ++j;
      }
      for (k = 0; k < iRemainingPixels; ++pDest)// Handle remaining pixels (width % 8)
      {
        byRemPixel = *pszSourceData++;
        if (byRemPixel)
          *pDest = byRemPixel;
        ++k;
      }
      pDest += winw - iWidth;                   // Advance to next row (skip to start of next line)
    }
  } else {                                             // Scaled rendering mode - complex pixel interpolation
    for (m = 0; iHeight > m; pDest = &pszDestRow[winw]) {
      iColScaleAccum = iScreenSize;             // Process each row with scaling
      pszDestRow = pDest;
      pszRowStart = pszSourceData;
      iXPos = 0;
      while (iXPos < iWidth)                  // Process each column with horizontal scaling
      {                                         // Copy non-transparent pixels only
        if (*pszSourceData)
          *pDest = *pszSourceData;
        iColScaleAccum -= 64;                   // Update column scaling accumulator
        ++pDest;
        for (; iColScaleAccum <= 0; ++iXPos)  // When accumulator depleted, advance source pixel
        {
          ++pszSourceData;
          iColScaleAccum += iScreenSize;
        }
      }
      iRowScaleAccum -= 64;                     // Update row scaling accumulator
      for (pszSourceData = pszRowStart; iRowScaleAccum <= 0; ++m)// When row accumulator depleted, advance to next source row
      {
        pszSourceData += iWidth;
        iRowScaleAccum += iScreenSize;
      }
    }
  }
  scr_size = iScreenSize;
}

//-------------------------------------------------------------------------------------------------

void print_damage(uint8 *pDest, tBlockHeader *pBlockHeader, int iCarIdx)
{
  int iScreenSize; // esi
  int iViewType; // ecx
  double dZoomThreshold; // st7
  uint8 *pbySourceData; // edx
  double dDamage; // st7
  int iScreenSizeTemp; // esi
  int j; // eax
  uint8 byPixel; // cl
  int iScaleAccum; // eax
  int iXPos; // ebx
  uint8 *pbyRowStart; // [esp+0h] [ebp-38h]
  int k; // [esp+4h] [ebp-34h]
  int iWidth; // [esp+8h] [ebp-30h]
  int iRowScaleAccum; // [esp+Ch] [ebp-2Ch]
  int iHeight; // [esp+10h] [ebp-28h]
  int i; // [esp+14h] [ebp-24h]
  int iZoomThreshold; // [esp+18h] [ebp-20h]
  int iDamage; // [esp+1Ch] [ebp-1Ch]
  uint8 *pbyDestPixel; // [esp+20h] [ebp-18h]
  uint8 byCurrentPixel; // [esp+24h] [ebp-14h]

  iScreenSize = scr_size;                       // Get current screen/sprite scaling size
  iViewType = ViewType[iCarIdx];                // Get view type for the specified car
  dZoomThreshold = Car[iViewType].fCameraDistance * 48.0;// Calculate zoom threshold based on camera distance * 48.0
  //_CHP();
  iZoomThreshold = (int)dZoomThreshold;
  iWidth = pBlockHeader->iWidth;                // Extract sprite dimensions from sprite data header
  iHeight = pBlockHeader->iHeight;
  iRowScaleAccum = iScreenSize;
  pbySourceData = (uint8 *)pBlockHeader + pBlockHeader->iDataOffset;// Get pointer to sprite pixel data (header + offset)
  if (Car[iViewType].fHealth <= 0.0)          // Check if car is destroyed (health <= 0)
  {
    iDamage = 13;                               // Car is destroyed - use maximum damage level (13)
  } else {
    dDamage = (100.0 - Car[iViewType].fHealth) * 0.01 * 13.0;// Calculate damage level: (100-health)% * 13 damage levels
    //_CHP();
    iDamage = (int)dDamage;
  }
  do_blip(iCarIdx);
  if (iScreenSize == 64)                      // Check if using 64-pixel scaling (1:1 pixel copy mode)
  {
    iScreenSizeTemp = scr_size;
    for (i = 0; i < iHeight; pDest += winw - iWidth)// 1:1 scaling - simple row-by-row pixel copy loop
    {                                           // Copy each pixel in the current row
      for (j = 0; j < iWidth; ++pDest) {
        byPixel = *pbySourceData++;             // Read source pixel and advance pointer
        if (byPixel)                          // Skip transparent pixels (value 0)
        {                                       // Check if pixel is damage-mappable (>= 0x31 = 49)
          if (byPixel >= 0x31u) {                                     // Apply damage mapping if damage level allows it
            if (iDamage >= dam_remap[byPixel])
              *pDest = byPixel;
            else
              *pDest = 0x7B;                    // Use default damaged color if damage too low (0x7B is grey)
          } else if (byPixel > iZoomThreshold)  // For non-damage pixels, check zoom threshold
          {
            *pDest = 0xED;                      // 0xED = dark blue in PALETTE.PAL
          } else {
            *pDest = 0xF3;                      // 0xF3 = blue in PALETTE.PAL
          }
        }
        ++j;
      }
      ++i;
    }
  } else {
    iScreenSizeTemp = scr_size;                 // Scaled rendering mode - more complex pixel interpolation
    for (k = 0; k < iHeight; pDest = &pbyDestPixel[winw])// Process each row of the scaled sprite
    {
      iScaleAccum = iScreenSizeTemp;
      pbyDestPixel = pDest;
      pbyRowStart = pbySourceData;
      iXPos = 0;
      while (iXPos < iWidth)                  // Process each column in the current row
      {
        byCurrentPixel = *pbySourceData;
        if (*pbySourceData) {                                       // Same damage mapping logic as 1:1 mode
          if (*pbySourceData >= 0x31u) {
            if (iDamage >= dam_remap[byCurrentPixel])
              *pDest = byCurrentPixel;
            else
              *pDest = 0x7B;                    // 0x7B = grey
          } else if (byCurrentPixel > iZoomThreshold) {
            *pDest = 0xED;                      // 0xED = dark blue
          } else {
            *pDest = 0xF3;                      // 0xF3 = blue
          }
        }
        iScaleAccum -= 64;                      // Advance scaling accumulator and destination pixel
        ++pDest;
        for (; iScaleAccum <= 0; ++iXPos)     // When scale accumulator depleted, advance source pixel
        {
          ++pbySourceData;
          iScaleAccum += iScreenSizeTemp;
        }
      }
      pbySourceData = pbyRowStart;              // Reset source pointer to start of current row
      for (iRowScaleAccum -= 64; iRowScaleAccum <= 0; ++k)// When row scale accumulator depleted, advance to next source row
      {
        pbySourceData += iWidth;
        iRowScaleAccum += iScreenSizeTemp;
      }
    }
  }
  scr_size = iScreenSizeTemp;
}

//-------------------------------------------------------------------------------------------------

void print_pos(int iX, int iY, int iDriverIdx)
{
  if (iDriverIdx >= 0 && iDriverIdx < racers) {
    mini_prt_string(rev_vga[0], &language_buffer[64 * iDriverIdx + 384], iX, iY);
    mini_prt_right(rev_vga[0], driver_names[carorder[iDriverIdx]], iX + 70, iY);
  }
}

//-------------------------------------------------------------------------------------------------

void free_game_memory()
{
  fre((void**)&building_vga);
  fre((void**)&horizon_vga);
  for (int i = 0; i < 16; ++i) {
    fre((void**)&cartex_vga[i]);
    fre((void**)&rev_vga[i]);
  }
  fre((void**)&cargen_vga);
  remove_mapsels();
  fre((void**)&mirbuf);
}

//-------------------------------------------------------------------------------------------------

int readmode()
{
  return 0;
  /*
  REGS regs; // [esp+0h] [ebp-24h] BYREF

  // int386 calling interrupt 0x10 (16 in decimal) which is the BIOS video services interrupt.
  // because regs.h.ah = 15;, it asks for the current video mode.
  // current video mode is returned in regs.h.al
  regs.h.ah = 15;
  int386(16, &regs, &regs);
  return regs.h.al;*/
}

//-------------------------------------------------------------------------------------------------

void key_handler(uint8 byScancode)
{
  // Handle key press/release
  if (byScancode & 0x80) {
    // Key release
    uint8 byCode = byScancode & 0x7F;
    keys[byCode] = 0;
  } else {
      // Key press
    keys[byScancode] = 1;

    // Pause sequence detection
    if (!frontend_on && !intro) {
      zoom_ascii_variable_1 = zoom_ascii_variable_2;
      zoom_ascii_variable_2 = zoom_ascii_variable_3;
      zoom_ascii_variable_3 = byScancode;

      if (zoom_ascii_variable_1 == 0xE1 &&
          zoom_ascii_variable_2 == 0x1D &&
          zoom_ascii_variable_3 == 0x45) {
        pause_request = 0xFFFFFFFF;
      }
    }

    // Buffer handling
    if (byScancode >= 0x48 && byScancode <= 0x50) {
      // Special keys (arrows/numpad) - store as two bytes
      key_buffer[write_key] = 0;
      write_key = (write_key + 1) % 64;
      key_buffer[write_key] = byScancode;
      write_key = (write_key + 1) % 64;
    } else {
      // Normal keys
      uint32 uiNext = (write_key + 1) % 64;
      if (uiNext != read_key) {  // Only store if buffer not full
        key_buffer[write_key] = byScancode;
        write_key = uiNext;
      }
    }
  }
}

//-------------------------------------------------------------------------------------------------

void claim_key_int()
{
  //_prev_int_9 = dos_getvect(9);        // Save current INT 9 handler
  //dos_setvect(9, key_handler_);
}

//-------------------------------------------------------------------------------------------------

int fatkbhit()
{
  if (write_key == read_key && !twoparter)
    return read_key ^ write_key;
  else
    return -1;
}

//-------------------------------------------------------------------------------------------------

int fatgetch()
{
  int iTwoParter; // edx
  int iResult; // eax

  iTwoParter = twoparter;
  // If we have a stored key part from a previous call
  if (twoparter) {
    iResult = twoparter;
    iTwoParter = 0;                             // clear stored value
  } else {

    // Wait until keys are available in the buffer
    while (write_key == read_key)
      UpdateSDL(); //added by ROLLER

    // Read next scancode from buffer and get mapped character
    iResult = (char)mapping[key_buffer[read_key++]];
    read_key &= 0x3Fu;

    // Handle special keys
    if (iResult < 0) {
      iTwoParter = -iResult;                    // Convert to positive value
      iResult = 0;                              // Return 0 for this call, special key value will be returned next call
    }
  }
  twoparter = iTwoParter;                       // Store special key for next call
  return iResult;
}

//-------------------------------------------------------------------------------------------------

void release_key_int()
{
  //dos_setvect(9, _prev_int_9);
}

//-------------------------------------------------------------------------------------------------

void clear_border(int x, int y, int iWidth, int iLines)
{
  int iOldWinX; // edi
  int iOldWinY; // ebp
  int iOldWinH; // esi
  int iLine; // ebx
  int iOldWinW; // [esp+0h] [ebp-10h]

  iOldWinX = winx;
  iOldWinY = winy;
  iOldWinW = winw;

  // Set temporary window dimensions
  winx = x;
  winy = y;
  winw = iWidth;
  iOldWinH = winh;
  iLine = 0;

  // Clear each specified line
  for (winh = 1; iLine < iLines; ++winy) {
    copypic(blank_line, screen);
    ++iLine;
  }

  // Restore original window state
  winh = iOldWinH;
  winx = iOldWinX;
  winy = iOldWinY;
  winw = iOldWinW;
}

//-------------------------------------------------------------------------------------------------

void DisplayFree()
{
  //DPMI_MemInfo memInfo; // [esp+0h] [ebp-88h] BYREF
  //union REGS regs; // [esp+50h] [ebp-38h] BYREF
  //struct SREGS sregs; // [esp+6Ch] [ebp-1Ch] BYREF
  //
  //memset(&sregs, 0, sizeof(sregs));
  //regs.x.eax = 0x500;
  //sregs.es = __DS__;
  //regs.x.edi = (unsigned int)&memInfo;
  //int386x(0x31, &regs, &regs, &sregs);
  //printf("\nLargest block: %d\n", memInfo.largestFreeBlock);
  //printf("Total free   : %d\n\n", memInfo.freeLinearPages << 12);
  //no_mem = 0;
  //lots_of_mem = 0;
  //if ((int)(memInfo.freeLinearPages << 12) >= 4500000) {
  //  printf("RUNNING 8 MEG VERSION.\n");
  //  gfx_size = 0;
  //  lots_of_mem = -1;
  //} else {
  //  printf("RUNNING 4 MEG VERSION.\n");
  //  gfx_size = 1;
  //  if ((int)(memInfo.freeLinearPages << 12) < 2000000)
  //    no_mem = -1;
  //}
}

//-------------------------------------------------------------------------------------------------

void setdirectory(const char *szAppPath)
{
  char szLocalDir[256];
  char *p = szLocalDir;
  const char *s = szAppPath;

  // Copy the path into localPath, 2 bytes at a time
  while (true) {
    *p++ = *s;
    if (*s == '\0') break;
    *p++ = *(s + 1);
    s += 2;
    if (*(s - 1) == '\0') break;
  }

#ifdef IS_WINDOWS
  // Set current drive based on first letter of path (e.g., 'C' -> drive 3)
  char cDriveLetter = szLocalDir[0] & 0xDF; // Convert to uppercase
  int iDrive = (int)(cDriveLetter - '@');  // 'A' => 1, 'C' => 3, etc.
  //dos_setdrive(iDrive, 0);
  _chdrive(iDrive);
#endif

  // Find last backslash in the path
  char *szLastSlash = strrchr(szLocalDir, '\\');
  if (!szLastSlash)
    szLastSlash = strrchr(szLocalDir, '/'); //linux compatibility
  if (szLastSlash && *(szLastSlash - 1) == ':') {
    szLastSlash++;  // skip over ":"
  }

  // trim filename
  if (szLastSlash) {
    *szLastSlash = '\0';
  }

  // set dir to szLocalDir
  chdir(szLocalDir);

  // set dir to FATDATA
  if (chdir("FATDATA") != 0)
    chdir("fatdata"); //linux compatibility
}

//-------------------------------------------------------------------------------------------------

void FindShades()
{
  int iR; // ecx
  int iB; // edi
  int iG; // esi
  int iColorOffset; // ebp
  int iR2; // esi
  int iB2; // edx
  int iDeltaR; // edi
  int iG2; // ebx
  int iDeltaB; // ecx
  int iDeltaG; // eax
  int iMaxOffset; // [esp+0h] [ebp-34h]
  int iColorIdx; // [esp+4h] [ebp-30h]
  int iColor; // [esp+8h] [ebp-2Ch]
  int iStepB; // [esp+Ch] [ebp-28h]
  int iStepG; // [esp+10h] [ebp-24h]
  int iStepR; // [esp+18h] [ebp-1Ch]

  iColorIdx = 1;
  iMaxOffset = 1025;
  iColor = 1;
  do {
    // Read base color components
    iR = palette[iColor].byR;
    iB = palette[iColor].byB;
    iG = palette[iColor].byG;

    // Calculate step sizes for shading
    iStepR = iR / 5;
    iStepB = iB / 5;
    iStepG = iG / 5;
    iColorOffset = iColorIdx;

    // Generate 4 progressive shades
    do {
      iR -= iStepR;
      if (iR < 0)
        iR = 0;
      iB -= iStepB;
      if (iB < 0)
        iB = 0;
      iG -= iStepG;
      if (iG < 0)
        iG = 0;
      iColorOffset += 256;                      // Move to next shade block (256-byte stride)
      shade_palette[iColorOffset] = nearest_colour(iR, iB, iG);
    } while (iColorOffset != iMaxOffset);

    // Generate special blend shade using color 0xDB as reference
    iR2 = palette[iColor].byR;
    iB2 = palette[iColor].byB;
    iDeltaR = palette[0xDB].byR - iR2;          // teal in PALETTE.PAL
    iG2 = palette[iColor].byG;

    // Clamp deltas to [-15, 15]
    if (iDeltaR < -15)
      iDeltaR = -15;
    if (iDeltaR > 15)
      iDeltaR = 15;
    iDeltaB = palette[0xDB].byB - iB2;
    if (iDeltaB < -15)
      iDeltaB = -15;
    if (iDeltaB > 15)
      iDeltaB = 15;
    iDeltaG = palette[0xDB].byG - iG2;
    if (iDeltaG < -15)
      iDeltaG = -15;
    if (iDeltaG > 15)
      iDeltaG = 15;

    // Store in Block 4 (overwriting last progressive shade)
    shade_palette[iColorIdx++ + 0x400] = nearest_colour(iDeltaR + iR2, iDeltaB + iB2, iDeltaG + iG2);
    ++iColor;
    ++iMaxOffset;
  } while (iColorIdx < 256);
}

//-------------------------------------------------------------------------------------------------

int nearest_colour(int iR, int iB, int iG)
{
  int iBestIndex = 0;
  int iBestDistance = 1024;  // large initial value
  int rDiff, bDiff, gDiff;
  int iDistance;

  for (int i = 1; i < 256; ++i) {
    // Calculate distance
    rDiff = abs((int)palette[i].byR - iR);
    bDiff = abs((int)palette[i].byB - iB);
    gDiff = abs((int)palette[i].byG - iG);
    iDistance = rDiff + bDiff + gDiff;

    if (iDistance < iBestDistance) {
      iBestDistance = iDistance;
      iBestIndex = i;
    }
  }

  return iBestIndex;
}

//-------------------------------------------------------------------------------------------------

void select_view(int iPlayer)
{
  int iCurrentViewIndex; // ebx
  int iPlayerIndex; // eax
  int iViewIndexForDrive; // edx
  int iDriveType; // ebx

  iCurrentViewIndex = SelectedView[iPlayer];    // Get the selected view index for this player
  if (iCurrentViewIndex == 2 || iCurrentViewIndex == 7)// Check if view is cockpit (2) or external (7) - these require screen size adjustment
  {                                             // Set screen size based on graphics mode - SVGA gets larger screen
    if (SVGA_ON)
      scr_size = 128;
    else
      scr_size = 64;
  }
  iPlayerIndex = iPlayer;                       // Look up drive configuration for selected view
  iViewIndexForDrive = SelectedView[iPlayerIndex];
  iDriveType = Selected_Drives[iViewIndexForDrive];
  SET_LOBYTE(iViewIndexForDrive, Selected_Play[iViewIndexForDrive]);
  DriveView[iPlayerIndex] = iDriveType;
  Play_View = iViewIndexForDrive;
  if (iDriveType == 5)                        // Drive type 5: Chase camera - enable chase view and switch to drive type 2
  {
    chaseview[iPlayerIndex] = 1;
    DriveView[iPlayerIndex] = 2;
  } else if (iDriveType == 2)                   // Drive type 2: Standard view - disable chase camera
  {
    chaseview[iPlayerIndex] = 0;
  }
  if ((cheat_mode & CHEAT_MODE_WIDESCREEN) != 0)               // CHEAT_MODE_WIDESCREEN: clear screen borders for full display
    clear_borders = -1;
}

//-------------------------------------------------------------------------------------------------

void mini_prt_string(tBlockHeader *pBlockHeader, const char *szStr, int iX, int iY)
{
  int iDone; // ebp
  int iSavedYPos; // [esp+0h] [ebp-18h]
  int iYPos; // [esp+4h] [ebp-14h] BYREF
  int iXPos; // [esp+8h] [ebp-10h] BYREF

  iDone = 0;
  iXPos = (scr_size * iX) >> 6;
  iYPos = (scr_size * iY) >> 6;
  do {
    if (*szStr) {
      if (*szStr != '\n') {
        iSavedYPos = iYPos;
        if (*szStr == -118)
          iYPos -= 2;
        prt_letter(pBlockHeader, *szStr, &iXPos, &iYPos, -1);
        iYPos = iSavedYPos;
      }
    } else {
      iDone = -1;
    }
    ++szStr;
  } while (!iDone);
}

//-------------------------------------------------------------------------------------------------

void mini_prt_string_rev(tBlockHeader *pBlockHeader, const char *szText, int iX, int iY)
{
  int iDone; // ebp
  int iSavedYPos; // [esp+0h] [ebp-18h]
  int piYPos; // [esp+4h] [ebp-14h] BYREF
  int piXPos; // [esp+8h] [ebp-10h] BYREF

  iDone = 0;
  piXPos = (scr_size * iX) >> 6;
  piYPos = (scr_size * iY) >> 6;
  do {
    if (*szText) {
      if (*szText != 10) {
        iSavedYPos = piYPos;
        if (*szText == -118)
          piYPos -= 2;
        prt_letter_rev(pBlockHeader, *szText, &piXPos, &piYPos, -1);
        piYPos = iSavedYPos;
      }
    } else {
      iDone = -1;
    }
    ++szText;
  } while (!iDone);
}

//-------------------------------------------------------------------------------------------------

void mini_prt_right(tBlockHeader *pBlockHeader, const char *szText, int iX, int iY)
{
  const char *i; // esi
  int iCharIdx; // eax
  const char *pCurrChar; // esi
  int iDone; // ebp
  int iSavedYPos; // [esp+0h] [ebp-18h]
  int iYPos; // [esp+4h] [ebp-14h] BYREF
  int iXPos; // [esp+8h] [ebp-10h] BYREF

  iXPos = iX;
  iYPos = iY;
  for (i = szText; *i; ++i) {
    iCharIdx = (uint8)ascii_conv3[*(uint8 *)i];
    if (iCharIdx == 255)
      iXPos -= 4;
    else
      iXPos -= pBlockHeader[iCharIdx].iWidth;
  }
  pCurrChar = szText;
  iXPos = (scr_size * iXPos) >> 6;
  iDone = 0;
  iYPos = (scr_size * iYPos) >> 6;
  do {
    if (*pCurrChar) {
      if (*pCurrChar != '\n') {
        iSavedYPos = iYPos;
        if (*pCurrChar == -118)
          iYPos -= 2;
        prt_letter(pBlockHeader, *pCurrChar, &iXPos, &iYPos, -1);
        iYPos = iSavedYPos;
      }
    } else {
      iDone = -1;
    }
    ++pCurrChar;
  } while (!iDone);
}

//-------------------------------------------------------------------------------------------------

void mini_prt_centre(tBlockHeader *pBlockHeader, const char *szStr, int iX, int iY)
{
  const char *i; // esi
  int iCharIdx; // eax
  const char *pCharItr; // esi
  int iDone; // ebp
  int iSavedYPos; // [esp+0h] [ebp-18h]
  int iYPos; // [esp+4h] [ebp-14h] BYREF
  int iXPos; // [esp+8h] [ebp-10h] BYREF

  iXPos = iX;                                   // Initialize position variables from parameters
  iYPos = iY;
  for (i = szStr; *i; ++i)                    // First pass: calculate total text width for centering
  {
    iCharIdx = (uint8)ascii_conv3[*(uint8 *)i];// Get character index from ascii_conv3 table (mini font)
    if (iCharIdx == 255)                      // Space character: subtract 4 pixels from X position
      iXPos -= 4;
    else
      iXPos -= pBlockHeader[iCharIdx].iWidth / 2;// Regular character: subtract half character width for centering calculation
  }
  iXPos = (scr_size * iXPos) >> 6;              // Apply scaling to calculated X offset and convert to screen coordinates
  pCharItr = szStr;                             // Initialize string iterator for second pass (actual rendering)
  iDone = 0;
  iYPos = (scr_size * iYPos) >> 6;              // Apply scaling to Y position
  do {                                             // Check for end of string (null terminator)
    if (*pCharItr) {                                           // Skip newline characters (not rendered in mini font)
      if (*pCharItr != '\n') {
        iSavedYPos = iYPos;                     // Save Y position for restoration after character rendering
        if (*pCharItr == -118)                // Special character 0x8A (138): render 2 pixels higher (superscript effect)
          iYPos -= 2;
        prt_letter(pBlockHeader, *pCharItr, &iXPos, &iYPos, -1);// Render character using prt_letter with ascii_conv3 font (fontType=-1)
        iYPos = iSavedYPos;                     // Restore Y position after character rendering
      }
    } else {
      iDone = -1;                               // End of string reached: set done flag to exit loop
    }
    ++pCharItr;                                 // Advance to next character in string
  } while (!iDone);                             // Second pass: render each character at calculated centered position
}

//-------------------------------------------------------------------------------------------------

void prt_right(tBlockHeader *pBlockHeader, const char *szStr, int iX, int iY)
{
  char *pCurrChar; // esi
  int iCharIdx; // eax
  int iDone; // ebp
  int iYPos; // [esp+0h] [ebp-14h] BYREF
  int iXPos; // [esp+4h] [ebp-10h] BYREF

  pCurrChar = (char *)szStr;
  iXPos = iX;
  iYPos = iY;
  while (*szStr) {
    iCharIdx = (uint8)font6_ascii[*(uint8 *)szStr++];
    if (iCharIdx == 255)
      iXPos -= 4;
    else
      iXPos -= pBlockHeader[iCharIdx].iWidth;
  }
  iXPos = (scr_size * iXPos) >> 6;
  iDone = 0;
  iYPos = (scr_size * iYPos) >> 6;
  do {
    if (*pCurrChar) {
      if (*pCurrChar != 10)
        prt_letter(pBlockHeader, *pCurrChar, &iXPos, &iYPos, 0);
    } else {
      iDone = -1;
    }
    ++pCurrChar;
  } while (!iDone);
}

//-------------------------------------------------------------------------------------------------

void prt_string(tBlockHeader *pBlockHeader, const char *szStr, int iX, int iY)
{
  int iDone; // ebp
  int piYPos; // [esp+0h] [ebp-14h] BYREF
  int piXPos; // [esp+4h] [ebp-10h] BYREF

  iDone = 0;
  piXPos = (scr_size * iX) >> 6;
  piYPos = (scr_size * iY) >> 6;
  do {
    if (*szStr) {
      if (*szStr != 10)
        prt_letter(pBlockHeader, *szStr, &piXPos, &piYPos, 0);
    } else {
      iDone = -1;
    }
    ++szStr;
  } while (!iDone);
}

//-------------------------------------------------------------------------------------------------

void prt_letter(tBlockHeader *pBlockHeader, char byChar, int *piXPos, int *piYPos, int iFontType)
{
  int iSavedScrSize; // esi
  int iCharIndex; // edi
  int iYOffset; // edx
  tBlockHeader *pCharData; // eax
  int iCharWidth; // edi
  uint8 *pCharBitmap; // ebx
  uint8 *pScreenDest; // eax
  int iRowIdx; // ebp
  int i; // edx
  uint8 byPixel; // cl
  uint8 *pRowStart; // edx
  int iScaleAccum; // edi
  uint8 *pScaledDest; // ebp
  int iTempScale; // eax
  int iScaledColIdx; // ebx
  uint8 *pScaledRowBase; // [esp+0h] [ebp-28h]
  int iCharHeight; // [esp+8h] [ebp-20h]
  int iCharWidth2; // [esp+Ch] [ebp-1Ch]
  uint8 *pBitmapRowStart; // [esp+10h] [ebp-18h]
  int iRowIdx2; // [esp+14h] [ebp-14h]
  int iScaledCharWidth; // [esp+18h] [ebp-10h]

  iSavedScrSize = scr_size;                     // Save current screen scaling factor
  if (iFontType)                              // Check font type selection: a5 != 0 uses ascii_conv3, a5 == 0 uses font6
  {
    iCharIndex = (uint8)ascii_conv3[(int8)byChar];// Use alternate font (ascii_conv3) with no Y offset
    iYOffset = 0;
  } else {
    iCharIndex = (int8)font6_ascii[(uint8)byChar];// Use default font6 with Y offset from font6_offsets table
    iYOffset = font6_offsets[iCharIndex];
  }
  pCharData = &pBlockHeader[iCharIndex];        // Get character data: width, height, bitmap offset (12 bytes per character)
  if (scr_size != 64)                         // Branch: scr_size == 64 uses simple blitting, != 64 uses scaled rendering
  {                                             // Scaled path: Check for space character (index 255)
    if (iCharIndex == 255) {
      *piXPos += (4 * scr_size) >> 6;           // Space character: advance X by scaled width (4 * scr_size / 64)
      scr_size = iSavedScrSize;
      return;
    }
    iScaledCharWidth = pCharData->iWidth;
    iCharWidth2 = pCharData->iHeight;
    pRowStart = (uint8 *)pBlockHeader + pCharData->iDataOffset;
    iScaleAccum = scr_size;
    pScaledRowBase = &screen_pointer[*piXPos + winw * *piYPos];// Calculate destination screen pointer for scaled rendering
    for (iRowIdx2 = 0; iRowIdx2 < iCharWidth2; pScaledRowBase += winw)// Scaled rendering: outer loop for each row of the character
    {
      pScaledDest = pScaledRowBase;
      pBitmapRowStart = pRowStart;
      iTempScale = iSavedScrSize;
      iScaledColIdx = 0;
      while (iScaledColIdx < iScaledCharWidth)// Inner loop: render each column with scaling algorithm
      {                                         // Non-zero pixel: copy to screen buffer (transparent = 0)
        if (*pRowStart)
          *pScaledDest = *pRowStart;
        iTempScale -= 64;
        ++pScaledDest;
        for (; iTempScale <= 0; ++iScaledColIdx) {
          ++pRowStart;
          iTempScale += iSavedScrSize;
        }
      }
      iScaleAccum -= 64;
      for (pRowStart = pBitmapRowStart; iScaleAccum <= 0; ++iRowIdx2) {
        pRowStart += iScaledCharWidth;
        iScaleAccum += iSavedScrSize;
      }
    }
    *piXPos += (iSavedScrSize * iScaledCharWidth) >> 6;// Scaled path: advance X by scaled character width
    goto CLEANUP_AND_RETURN;
  }
  if (iCharIndex == 255) {
    *piXPos += 4;                               // Unscaled path: Space character advances X by 4 pixels
  CLEANUP_AND_RETURN:
    scr_size = iSavedScrSize;
    return;
  }
  iCharHeight = pCharData->iHeight;
  iCharWidth = pCharData->iWidth;
  pCharBitmap = (uint8 *)pBlockHeader + pCharData->iDataOffset;
  pScreenDest = &screen_pointer[*piXPos + winw * (*piYPos + iYOffset)];// Calculate screen destination for unscaled 1:1 rendering
  for (iRowIdx = 0; iRowIdx < iCharHeight; pScreenDest += winw - iCharWidth)// Unscaled rendering: simple row-by-row bitmap copy
  {
    for (i = 0; i < iCharWidth; ++pScreenDest) {
      byPixel = *pCharBitmap++;                 // Copy non-zero pixels (0 = transparent)
      if (byPixel)
        *pScreenDest = byPixel;
      ++i;
    }
    ++iRowIdx;
  }
  *piXPos += iCharWidth;                        // Advance X position by character width
  scr_size = 64;                                // Reset scr_size to 64 (unscaled mode)
}

//-------------------------------------------------------------------------------------------------

void prt_letter_rev(tBlockHeader *pBlockHeader, char byChar, int *piXPos, int *piYPos, int iFontType)
{
  int iSavedScrSize; // esi
  int byCharIndex; // edi
  int iYOffset; // edx
  tBlockHeader *pCharData; // eax
  int iCharWidth; // edi
  uint8 *pCharBitmap; // ebx
  uint8 *pScreenDest; // eax
  int iRowIdx; // ebp
  int i; // edx
  uint8 byPixel; // cl
  uint8 *pRowStart; // edx
  int iScrSize; // edi
  uint8 *pScaledDest; // ebp
  int iTempScale; // eax
  int iScaledColIdx; // ebx
  uint8 *pScaledRowBase; // [esp+0h] [ebp-28h]
  int iCharHeight; // [esp+8h] [ebp-20h]
  int iHeight; // [esp+Ch] [ebp-1Ch]
  uint8 *pBitmapRowStart; // [esp+10h] [ebp-18h]
  int iRowIdx2; // [esp+14h] [ebp-14h]
  int iWidth; // [esp+18h] [ebp-10h]

  iSavedScrSize = scr_size;                     // Save current screen scaling factor
  if (iFontType)                              // Font selection: iFontType != 0 uses ascii_conv3, == 0 uses font6
  {
    byCharIndex = (uint8)ascii_conv3[(uint8)byChar];// Use alternate font (ascii_conv3) with no Y offset
    iYOffset = 0;
  } else {
    byCharIndex = (uint8)font6_ascii[(uint8)byChar];// Use default font6 with Y offset from font6_offsets table
    iYOffset = font6_offsets[byCharIndex];
  }
  pCharData = &pBlockHeader[byCharIndex];       // Get character data block: width, height, bitmap offset
  if (scr_size != 64)                         // Branch: scr_size == 64 uses simple reverse blitting, != 64 uses scaled reverse rendering
  {                                             // Scaled path: Check for space character (index 255)
    if (byCharIndex == 255) {
      *piXPos -= (4 * scr_size) >> 6;           // Space character: move X leftward by scaled width (4 * scr_size / 64)
      scr_size = iSavedScrSize;
      return;
    }
    iWidth = pCharData->iWidth;
    iHeight = pCharData->iHeight;
    pRowStart = (uint8 *)pBlockHeader + pCharData->iDataOffset;
    iScrSize = scr_size;
    pScaledRowBase = &screen_pointer[*piXPos + winw * *piYPos];// Calculate destination screen pointer for scaled reverse rendering
    for (iRowIdx2 = 0; iRowIdx2 < iHeight; pScaledRowBase += winw)// Scaled reverse rendering: outer loop for each row
    {
      pScaledDest = pScaledRowBase;
      pBitmapRowStart = pRowStart;
      iTempScale = iSavedScrSize;
      iScaledColIdx = 0;
      while (iScaledColIdx < iWidth)          // Inner loop: render each column right-to-left with scaling
      {                                         // Non-zero pixel: copy to screen buffer (transparent = 0)
        if (*pRowStart)
          *pScaledDest = *pRowStart;
        iTempScale -= 64;
        --pScaledDest;                          // Move destination pointer leftward (reverse direction)
        for (; iTempScale <= 0; ++iScaledColIdx) {
          ++pRowStart;
          iTempScale += iSavedScrSize;
        }
      }
      iScrSize -= 64;
      for (pRowStart = pBitmapRowStart; iScrSize <= 0; ++iRowIdx2) {
        pRowStart += iWidth;
        iScrSize += iSavedScrSize;
      }
    }
    *piXPos -= (iSavedScrSize * iWidth) >> 6;   // Scaled path: move X leftward by scaled character width
    goto CLEANUP_AND_RETURN;
  }
  if (byCharIndex == 255) {
    *piXPos -= 4;                               // Unscaled path: Space character moves X leftward by 4 pixels
  CLEANUP_AND_RETURN:
    scr_size = iSavedScrSize;
    return;
  }
  iCharHeight = pCharData->iHeight;
  iCharWidth = pCharData->iWidth;
  pCharBitmap = (uint8 *)pBlockHeader + pCharData->iDataOffset;
  pScreenDest = &screen_pointer[*piXPos + winw * (*piYPos + iYOffset)];// Calculate screen destination for unscaled reverse rendering
  for (iRowIdx = 0; iRowIdx < iCharHeight; pScreenDest += iCharWidth + winw)// Unscaled reverse rendering: row-by-row bitmap copy right-to-left
  {
    for (i = 0; i < iCharWidth; --pScreenDest) {
      byPixel = *pCharBitmap++;                 // Copy non-zero pixels, decrement screen pointer (reverse direction)
      if (byPixel)
        *pScreenDest = byPixel;
      ++i;
    }
    ++iRowIdx;
  }
  *piXPos -= iCharWidth;                        // Move X position leftward by character width
  scr_size = 64;                                // Reset scr_size to 64 (unscaled mode)
}

//-------------------------------------------------------------------------------------------------

void prt_stringcol(tBlockHeader *pBlockHeader, const char *szStr, int iX, int iY, char byColor)
{
  int iDone; // ebp
  int iYPos; // [esp+0h] [ebp-14h] BYREF
  int iXPos; // [esp+4h] [ebp-10h] BYREF

  iDone = 0;
  iXPos = (scr_size * iX) >> 6;
  iYPos = (scr_size * iY) >> 6;
  do {
    if (*szStr) {
      if (*szStr != 10)
        prt_lettercol(pBlockHeader, *szStr, &iXPos, &iYPos, byColor);
    } else {
      iDone = -1;
    }
    ++szStr;
  } while (!iDone);
}

//-------------------------------------------------------------------------------------------------

void prt_rightcol(tBlockHeader *pBlockHeader, const char *szStr, int iX, int iY, char byColor)
{
  const char *i; // esi
  int iCharIdx; // eax
  const char *pCharItr; // esi
  int iDone; // ebp
  int iYPos; // [esp+0h] [ebp-14h] BYREF
  int iXPos; // [esp+4h] [ebp-10h] BYREF

  iXPos = iX;
  iYPos = iY;
  for (i = szStr; *i; ++i) {
    iCharIdx = (uint8)font6_ascii[*(uint8 *)i];
    if (iCharIdx == 255)
      iXPos -= 4;
    else
      iXPos -= pBlockHeader[iCharIdx].iWidth;
  }
  pCharItr = szStr;
  iXPos = (scr_size * iXPos) >> 6;
  iDone = 0;
  iYPos = (scr_size * iYPos) >> 6;
  do {
    if (*pCharItr) {
      if (*pCharItr != '\n')
        prt_lettercol(pBlockHeader, *pCharItr, &iXPos, &iYPos, byColor);
    } else {
      iDone = -1;
    }
    ++pCharItr;
  } while (!iDone);
}

//-------------------------------------------------------------------------------------------------

void prt_centrecol(tBlockHeader *pBlockHeader, const char *szStr, int iX, int iY, char byColor)
{
  const char *pCurrChar; // esi
  const char *pCharItr; // eax
  char c; // bl
  int iWidth; // edx
  int iCharIdx; // ebx
  int iDone; // ebp
  int iYPos; // [esp+0h] [ebp-14h] BYREF
  int iXPos; // [esp+4h] [ebp-10h] BYREF

  pCurrChar = szStr;
  iXPos = iX;
  iYPos = iY;
  pCharItr = szStr;
  c = *szStr;
  iWidth = 0;
  if (c) {
    do {
      iCharIdx = (uint8)font6_ascii[*(uint8 *)pCharItr++];
      if (iCharIdx == 255)
        iWidth += 4;
      else
        iWidth += pBlockHeader[iCharIdx].iWidth;
    } while (*pCharItr);
  }
  iXPos = (scr_size * (iXPos - iWidth / 2)) >> 6;
  iDone = 0;
  iYPos = (scr_size * iYPos) >> 6;
  do {
    if (*pCurrChar) {
      if (*pCurrChar != '\n')
        prt_lettercol(pBlockHeader, *pCurrChar, &iXPos, &iYPos, byColor);
    } else {
      iDone = -1;
    }
    ++pCurrChar;
  } while (!iDone);
}

//-------------------------------------------------------------------------------------------------

void prt_lettercol(tBlockHeader *pBlockHeader, char byChar, int *piXPos, int *piYPos, char byColor)
{
  int iSavedScrSize; // esi
  int byCharIndex; // ebx
  uint8 *pCharBitmap; // edx
  int iScaleAccum; // ebp
  uint8 *pScreenDest; // edi
  int iTempScale; // eax
  int iColIdx; // ebx
  uint8 byPixel; // cl
  int iHeight; // [esp+0h] [ebp-24h]
  int iRowIdx; // [esp+4h] [ebp-20h]
  uint8 *pBitmapRowStart; // [esp+Ch] [ebp-18h]
  uint8 *pRowBase; // [esp+10h] [ebp-14h]
  int iWidth; // [esp+14h] [ebp-10h]

  iSavedScrSize = scr_size;                     // Save current screen scaling factor
  byCharIndex = (uint8)font6_ascii[(uint8)byChar];// Only uses font6_ascii (no alternate font support)
  if (byCharIndex == 255)                     // Check for space character (index 255)
  {
    *piXPos += (4 * scr_size) >> 6;             // Space character: advance X by scaled width (4 * scr_size / 64)
  } else {
    iWidth = pBlockHeader[byCharIndex].iWidth;  // Get character dimensions from font data
    iHeight = pBlockHeader[byCharIndex].iHeight;
    pCharBitmap = (uint8 *)pBlockHeader + pBlockHeader[byCharIndex].iDataOffset;// Get pointer to character bitmap data
    iScaleAccum = scr_size;
    pRowBase = &screen_pointer[*piXPos + winw * (font6_offsets[byCharIndex] + *piYPos)];// Calculate screen destination with Y offset from font6_offsets
    for (iRowIdx = 0; iRowIdx < iHeight; pRowBase += winw)// Scaled rendering: outer loop for each row of character
    {
      pScreenDest = pRowBase;
      pBitmapRowStart = pCharBitmap;
      iTempScale = iSavedScrSize;
      iColIdx = 0;
      while (iColIdx < iWidth)                // Inner loop: render each column with scaling and color substitution
      {
        byPixel = *pCharBitmap;                 // Read pixel from bitmap and check for non-zero (non-transparent)
        if (*pCharBitmap) {                                       // Color substitution: replace 0x8F (143) with custom color (a5)
          if (byPixel == 0x8F)
            byPixel = byColor;
          *pScreenDest = byPixel;               // Write pixel to screen buffer
        }
        iTempScale -= 64;                       // Scaling algorithm: decrement scale accumulator
        ++pScreenDest;
        for (; iTempScale <= 0; ++iColIdx)    // Scale loop: advance bitmap pointer when scale threshold reached
        {
          ++pCharBitmap;
          iTempScale += iSavedScrSize;
        }
      }
      iScaleAccum -= 64;                        // Row scaling: decrement row scale accumulator
      for (pCharBitmap = pBitmapRowStart; iScaleAccum <= 0; ++iRowIdx)// Row scale loop: advance to next bitmap row when threshold reached
      {
        pCharBitmap += iWidth;
        iScaleAccum += iSavedScrSize;
      }
    }
    *piXPos += (iSavedScrSize * iWidth) >> 6;   // Advance X position by scaled character width
  }
  scr_size = iSavedScrSize;                     // Restore original screen size
}

//-------------------------------------------------------------------------------------------------

char display_paused()
{
  return 0;
  /*
  int i; // eax
  char v1; // al
  char v2; // al
  char *v3; // edx
  char v4; // al
  char v5; // al
  char v6; // al
  char v7; // al
  char v8; // al
  int v9; // ebx
  int v10; // eax
  int v11; // edx
  char v12; // al
  char v13; // al
  char v14; // al
  int v15; // edi
  int v16; // esi
  char v17; // al
  char v18; // al
  int v19; // edx
  int v20; // esi
  int v21; // edi
  char v22; // al
  char v23; // al
  int v24; // ebx
  int v25; // esi
  int v26; // edi
  char v27; // al
  char v28; // al
  char v29; // al
  int v30; // ebx
  _BYTE *v31; // edx
  char v32; // al
  int v33; // ebx
  _BYTE *v34; // edx
  char v35; // al
  int v36; // ebx
  _BYTE *v37; // edx
  char v38; // al
  int v39; // ebx
  _BYTE *v40; // edx
  char v41; // al
  char v42; // al
  char v43; // al
  char v44; // al
  char v45; // al
  char v46; // al
  _BYTE *v47; // edx
  char v48; // al
  char v49; // al
  _BYTE *v50; // edx
  char v51; // al
  char v52; // al
  _BYTE *v53; // edx
  char v54; // al
  char v55; // al
  char v56; // al
  _BYTE *v57; // edx
  char v58; // al
  char v59; // al
  _BYTE *v60; // edx
  char v61; // al
  char v62; // al
  _BYTE *v63; // edx
  char v64; // al
  char v65; // al
  _BYTE *v66; // edx
  char v67; // al
  char v68; // al
  _BYTE *v69; // edx
  char v70; // al
  char v71; // al
  _BYTE *v72; // edx
  char v73; // al
  char v74; // al
  _BYTE *v75; // edx
  char v76; // al
  char v77; // al
  _BYTE *v78; // edx
  char v79; // al
  char v80; // al
  _BYTE *v81; // edx
  char v82; // al
  char v83; // al
  _BYTE *v84; // edx
  char v85; // al
  char v86; // al
  _BYTE *v87; // edx
  char v88; // al
  char v89; // al
  _BYTE *v90; // edx
  char v91; // al
  char v92; // al
  _BYTE *v93; // edx
  char v94; // al
  char v95; // al
  _BYTE *v96; // edx
  char v97; // al
  int v98; // eax
  char v99; // al
  char v100; // al
  char *v101; // edx
  char v102; // al
  _DWORD v104[2]; // [esp+0h] [ebp-28h] BYREF
  int v105; // [esp+8h] [ebp-20h]
  int v106; // [esp+Ch] [ebp-1Ch]
  int v107; // [esp+10h] [ebp-18h]
  int v108; // [esp+14h] [ebp-14h]
  int v109; // [esp+18h] [ebp-10h]
  int v110; // [esp+1Ch] [ebp-Ch]
  char *v111; // [esp+20h] [ebp-8h]
  char *v112; // [esp+24h] [ebp-4h]

  LOBYTE(i) = pausewindow;
  switch (pausewindow) {
    case 0:
      blankwindow(0, 0, 320, 200);
      prt_centrecol(rev_vga_variable_1, config_buffer, 160, 16, 171);
      if (req_edit)
        v1 = -125;
      else
        v1 = -113;
      prt_centrecol(rev_vga_variable_1, config_buffer_variable_1, 160, 36, v1);
      if (replaytype == 2) {
        if (req_edit == 1)
          v2 = -113;
        else
          v2 = -125;
        v3 = (char *)&config_buffer_variable_3;
      } else {
        if (req_edit == 1)
          v2 = -113;
        else
          v2 = -125;
        v3 = (char *)&config_buffer_variable_2;
      }
      prt_centrecol(rev_vga_variable_1, v3, 160, 48, v2);
      if (req_edit == 2)
        v4 = -113;
      else
        v4 = -125;
      prt_centrecol(rev_vga_variable_1, config_buffer_variable_4, 160, 60, v4);
      if (req_edit == 3)
        v5 = -113;
      else
        v5 = -125;
      prt_centrecol(rev_vga_variable_1, config_buffer_variable_5, 160, 72, v5);
      if (req_edit == 4)
        v6 = -113;
      else
        v6 = -125;
      prt_centrecol(rev_vga_variable_1, config_buffer_variable_6, 160, 84, v6);
      if (req_edit == 5)
        v7 = -113;
      else
        v7 = -125;
      prt_centrecol(rev_vga_variable_1, config_buffer_variable_9, 160, 96, v7);
      if (req_edit == 6)
        v8 = -113;
      else
        v8 = -125;
      LOBYTE(i) = prt_centrecol(rev_vga_variable_1, config_buffer_variable_10, 160, 108, v8);
      break;
    case 1:
      blankwindow(0, 0, 320, 200);
      if (calibrate_mode) {
        ReadJoys(v104);
        _disable();
        if (v105 < JAXmin)
          JAXmin = v105;
        if (v105 > JAXmax)
          JAXmax = v105;
        if (v106 < JAYmin)
          JAYmin = v106;
        if (v106 > JAYmax)
          JAYmax = v106;
        if (v109 < JBXmin)
          JBXmin = v109;
        if (v109 > JBXmax)
          JBXmax = v109;
        if (v110 < JBYmin)
          JBYmin = v110;
        if (v110 > JBYmax)
          JBYmax = v110;
        if (JAXmin == JAXmax)
          JAXmax = JAXmin + 1;
        if (JAYmin == JAYmax)
          JAYmax = JAYmin + 1;
        if (JBXmin == JBXmax)
          JBXmax = JBXmin + 1;
        if (JBYmin == JBYmax)
          JBYmax = JBYmin + 1;
        _enable();
      }
      prt_centrecol(rev_vga_variable_1, config_buffer_variable_5, 160, 16, 171);
      if (calibrate_select != 1 || calibrate_mode)
        v27 = -125;
      else
        v27 = -113;
      prt_centrecol(rev_vga_variable_1, config_buffer_variable_14, 160, 36, v27);
      if (calibrate_select || calibrate_mode)
        v28 = -125;
      else
        v28 = -113;
      prt_centrecol(rev_vga_variable_1, config_buffer_variable_13, 160, 48, v28);
      if (calibrate_mode)
        v29 = -113;
      else
        v29 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_15, 176, 68, v29);
      if (calibrate_mode) {
        if (x1ok && JAXmax - JAXmin >= 100)
          v30 = 140 * (2 * v105 - JAXmax - JAXmin) / (JAXmax - JAXmin);
        else
          v30 = 0;
        displaycalibrationbar(180, 68, v30);
      } else {
        if (x1ok)
          v31 = &config_buffer_variable_20;
        else
          v31 = &config_buffer_variable_19;
        prt_stringcol(rev_vga_variable_1, v31, 180, 68, 131);
      }
      if (calibrate_mode)
        v32 = -113;
      else
        v32 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_16, 176, 80, v32);
      if (calibrate_mode) {
        if (y1ok && JAYmax - JAYmin >= 100)
          v33 = 140 * (2 * v106 - JAYmax - JAYmin) / (JAYmax - JAYmin);
        else
          v33 = 0;
        displaycalibrationbar(180, 80, v33);
      } else {
        if (y1ok)
          v34 = &config_buffer_variable_20;
        else
          v34 = &config_buffer_variable_19;
        prt_stringcol(rev_vga_variable_1, v34, 180, 80, 131);
      }
      if (calibrate_mode)
        v35 = -113;
      else
        v35 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_17, 176, 92, v35);
      if (calibrate_mode) {
        if (x2ok && JBXmax - JBXmin >= 100)
          v36 = 140 * (2 * v109 - JBXmax - JBXmin) / (JBXmax - JBXmin);
        else
          v36 = 0;
        displaycalibrationbar(180, 92, v36);
      } else {
        if (x2ok)
          v37 = &config_buffer_variable_20;
        else
          v37 = &config_buffer_variable_19;
        prt_stringcol(rev_vga_variable_1, v37, 180, 92, 131);
      }
      if (calibrate_mode)
        v38 = -113;
      else
        v38 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_18, 176, 104, v38);
      if (calibrate_mode) {
        if (y2ok && JBYmax - JBYmin >= 100)
          v39 = 140 * (2 * v110 - JBYmax - JBYmin) / (JBYmax - JBYmin);
        else
          v39 = 0;
        LOBYTE(i) = displaycalibrationbar(180, 104, v39);
      } else {
        if (y2ok)
          v40 = &config_buffer_variable_20;
        else
          v40 = &config_buffer_variable_19;
        LOBYTE(i) = prt_stringcol(rev_vga_variable_1, v40, 180, 104, 131);
      }
      if (calibrate_mode) {
        prt_centrecol(rev_vga_variable_1, config_buffer_variable_21, 160, 124, 143);
        LOBYTE(i) = prt_centrecol(rev_vga_variable_1, config_buffer_variable_22, 160, 136, 143);
      }
      break;
    case 2:
      if (controlrelease) {
        v9 = -1;
        v10 = 0;
        v11 = 0;
        do {
          if (keyname[v11] && keys[v10])
            v9 = 0;
          ++v10;
          ++v11;
        } while (v10 < 128);
        if (v9)
          controlrelease = 0;
      }
      blankwindow(0, 0, 320, 200);
      prt_centrecol(rev_vga_variable_1, config_buffer_variable_6, 160, 16, 171);
      if (control_select != 2 || define_mode)
        v12 = -125;
      else
        v12 = -113;
      prt_centrecol(rev_vga_variable_1, config_buffer_variable_11, 160, 36, v12);
      if (control_select != 1 || define_mode)
        v13 = -125;
      else
        v13 = -113;
      prt_centrecol(rev_vga_variable_1, config_buffer_variable_12, 160, 48, v13);
      if (control_select || define_mode)
        v14 = -125;
      else
        v14 = -113;
      prt_centrecol(rev_vga_variable_1, config_buffer_variable_13, 160, 60, v14);
      if (control_select > 1) {
        v20 = 6;
        v21 = 80;
        v111 = &config_buffer[1280];
        do {
          if (v20 == control_edit)
            v22 = -113;
          else
            v22 = 123;
          prt_rightcol(rev_vga_variable_1, v111, 198, v21, v22);
          if (v20 == control_edit)
            v23 = -113;
          else
            v23 = 123;
          v19 = keyname[(unsigned __int8)userkey[v20]];
          LOBYTE(i) = prt_stringcol(rev_vga_variable_1, (_BYTE *)v19, 200, v21, v23);
          ++v20;
          v21 += 12;
          v111 += 64;
        } while (v20 < 12);
      } else {
        v15 = 80;
        v16 = 0;
        v112 = &config_buffer[896];
        do {
          if (v16 == control_edit)
            v17 = -113;
          else
            v17 = 123;
          prt_rightcol(rev_vga_variable_1, v112, 198, v15, v17);
          if (v16 == control_edit)
            v18 = -113;
          else
            v18 = 123;
          LOBYTE(i) = prt_stringcol(
                        rev_vga_variable_1,
                        (_BYTE *)keyname[(unsigned __int8)userkey[v16++]],
                        200,
                        v15,
                        v18);
          v19 = (int)(v112 + 64);
          v15 += 12;
          v112 += 64;
        } while (v16 < 6);
      }
      if (define_mode) {
        if (!controlrelease) {
          v24 = -1;
          i = 0;
          v19 = 0;
          do {
            if (*(int *)((char *)keyname + v19) && keys[i])
              v24 = i;
            ++i;
            v19 += 4;
          } while (i < 128);
          if (v24 == -1) {
            LOBYTE(i) = ReadJoys(v104);
            if (v104[0])
              v24 = 128;
            if (v104[1])
              v24 = 129;
            if (v107)
              v24 = 130;
            if (v108)
              v24 = 131;
          }
          if (v24 == -1) {
            if (y2ok) {
              i = 100 * (2 * v110 - JBYmax - JBYmin) / (JBYmax - JBYmin);
              v19 = 100 * (2 * v110 - JBYmax - JBYmin) % (JBYmax - JBYmin);
              if (i < -50)
                v24 = 138;
              if (i > 50)
                v24 = 139;
            }
            if (x2ok) {
              i = 100 * (2 * v109 - JBXmax - JBXmin) / (JBXmax - JBXmin);
              v19 = 100 * (2 * v109 - JBXmax - JBXmin) % (JBXmax - JBXmin);
              if (i < -50)
                v24 = 136;
              if (i > 50)
                v24 = 137;
            }
            if (y1ok) {
              i = 100 * (2 * v106 - JAYmax - JAYmin) / (JAYmax - JAYmin);
              v19 = 100 * (2 * v106 - JAYmax - JAYmin) % (JAYmax - JAYmin);
              if (i < -50)
                v24 = 134;
              if (i > 50)
                v24 = 135;
            }
            if (x1ok) {
              i = 100 * (2 * v105 - JAXmax - JAXmin) / (JAXmax - JAXmin);
              v19 = 100 * (2 * v105 - JAXmax - JAXmin) % (JAXmax - JAXmin);
              if (i < -50)
                v24 = 132;
              if (i > 50)
                v24 = 133;
            }
          }
          if (v24 != -1 && (control_edit == 1 || control_edit == 7)) {
            if ((LOBYTE(i) = control_edit, *((_BYTE *)&off_A4108 + control_edit + 3) <= 0x83u) && v24 > 131
              || (LOBYTE(i) = control_edit, *((_BYTE *)&off_A4108 + control_edit + 3) > 0x83u) && v24 <= 131) {
              v24 = -1;
            }
          }
          if (v24 != -1) {
            v19 = control_edit;
            v25 = 0;
            for (i = 0; i < control_edit; ++i) {
              v19 = (unsigned __int8)userkey[i];
              if (v19 == v24)
                v25 = -1;
            }
            if (!v25) {
              i = control_edit + 1;
              v26 = control_select;
              controlrelease = -1;
              *((_BYTE *)&off_A4108 + i + 3) = v24;
              control_edit = i;
              if (v26 == 1) {
                if (i == 6) {
                  define_mode = 0;
                  control_edit = -1;
                  while (1) {
                    i = fatkbhit();
                    if (!i)
                      break;
                    fatgetch();
                  }
                }
              } else if (i == 12) {
                v19 = 0;
                control_edit = -1;
                define_mode = 0;
                while (1) {
                  i = fatkbhit();
                  if (!i)
                    break;
                  fatgetch();
                }
              }
            }
          }
        }
        if (keys_variable_1) {
          define_mode = 0;
          qmemcpy(userkey, &oldkeys, 0xCu);
          qmemcpy(&userkey[12], (char *)&oldkeys + 12, 2u);
          while (fatkbhit())
            fatgetch();
          pausewindow = 0;
          LOBYTE(i) = check_joystick_usage(0, v19);
        }
      }
      break;
    case 3:
      blankwindow(0, 0, 320, 200);
      prt_centrecol(rev_vga_variable_1, config_buffer_variable_9, 160, 12, 171);
      if (graphic_mode == 16)
        v55 = -113;
      else
        v55 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_87, 187, 26, v55);
      if ((((unsigned int)&loc_7FFFE + 2) & textures_off) != 0) {
        if (graphic_mode == 16)
          v56 = -113;
        else
          v56 = -125;
        v57 = &config_buffer_variable_30;
      } else {
        if (graphic_mode == 16)
          v56 = -113;
        else
          v56 = -125;
        v57 = &config_buffer_variable_29;
      }
      prt_stringcol(rev_vga_variable_1, v57, 190, 26, v56);
      sprintf(&buffer, "%s:", config_buffer_variable_50);
      if (graphic_mode == 15)
        v58 = -113;
      else
        v58 = -125;
      prt_rightcol(rev_vga_variable_1, &buffer, 187, 36, v58);
      if (names_on) {
        if (names_on == 2) {
          if (graphic_mode == 15)
            v59 = -113;
          else
            v59 = -125;
          v60 = &config_buffer_variable_32;
        } else {
          if (graphic_mode == 15)
            v59 = -113;
          else
            v59 = -125;
          v60 = &config_buffer_variable_29;
        }
      } else {
        if (graphic_mode == 15)
          v59 = -113;
        else
          v59 = -125;
        v60 = &config_buffer_variable_30;
      }
      prt_stringcol(rev_vga_variable_1, v60, 190, 36, v59);
      if (graphic_mode == 14)
        v61 = -113;
      else
        v61 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_35, 187, 46, v61);
      if ((textures_off & 0x200) != 0) {
        if (graphic_mode == 14)
          v62 = -113;
        else
          v62 = -125;
        v63 = &config_buffer_variable_30;
      } else {
        if (graphic_mode == 14)
          v62 = -113;
        else
          v62 = -125;
        v63 = &config_buffer_variable_29;
      }
      prt_stringcol(rev_vga_variable_1, v63, 190, 46, v62);
      if (graphic_mode == 13)
        v64 = -113;
      else
        v64 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_36, 187, 56, v64);
      if ((textures_off & 0x800) != 0) {
        if (graphic_mode == 13)
          v65 = -113;
        else
          v65 = -125;
        v66 = &config_buffer_variable_30;
      } else {
        if (graphic_mode == 13)
          v65 = -113;
        else
          v65 = -125;
        v66 = &config_buffer_variable_29;
      }
      prt_stringcol(rev_vga_variable_1, v66, 190, 56, v65);
      if (graphic_mode == 12)
        v67 = -113;
      else
        v67 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_38, 187, 66, v67);
      if ((textures_off & 0x10) != 0) {
        if (graphic_mode == 12)
          v68 = -113;
        else
          v68 = -125;
        v69 = &config_buffer_variable_30;
      } else {
        if (graphic_mode == 12)
          v68 = -113;
        else
          v68 = -125;
        v69 = &config_buffer_variable_29;
      }
      prt_stringcol(rev_vga_variable_1, v69, 190, 66, v68);
      if (graphic_mode == 11)
        v70 = -113;
      else
        v70 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_37, 187, 76, v70);
      if ((textures_off & 0x40) != 0) {
        if (graphic_mode == 11)
          v71 = -113;
        else
          v71 = -125;
        v72 = &config_buffer_variable_30;
      } else {
        if (graphic_mode == 11)
          v71 = -113;
        else
          v71 = -125;
        v72 = &config_buffer_variable_29;
      }
      prt_stringcol(rev_vga_variable_1, v72, 190, 76, v71);
      if (graphic_mode == 10)
        v73 = -113;
      else
        v73 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_39, 187, 86, v73);
      if ((textures_off & 4) != 0) {
        if (graphic_mode == 10)
          v74 = -113;
        else
          v74 = -125;
        v75 = &config_buffer_variable_30;
      } else {
        if (graphic_mode == 10)
          v74 = -113;
        else
          v74 = -125;
        v75 = &config_buffer_variable_29;
      }
      prt_stringcol(rev_vga_variable_1, v75, 190, 86, v74);
      if (graphic_mode == 9)
        v76 = -113;
      else
        v76 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_40, 187, 96, v76);
      if ((textures_off & 1) != 0) {
        if (graphic_mode == 9)
          v77 = -113;
        else
          v77 = -125;
        v78 = &config_buffer_variable_30;
      } else {
        if (graphic_mode == 9)
          v77 = -113;
        else
          v77 = -125;
        v78 = &config_buffer_variable_29;
      }
      prt_stringcol(rev_vga_variable_1, v78, 190, 96, v77);
      if (graphic_mode == 8)
        v79 = -113;
      else
        v79 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_41, 187, 106, v79);
      if ((textures_off & 0x80u) == 0) {
        if (graphic_mode == 8)
          v80 = -113;
        else
          v80 = -125;
        v81 = &config_buffer_variable_29;
      } else {
        if (graphic_mode == 8)
          v80 = -113;
        else
          v80 = -125;
        v81 = &config_buffer_variable_30;
      }
      prt_stringcol(rev_vga_variable_1, v81, 190, 106, v80);
      if (graphic_mode == 7)
        v82 = -113;
      else
        v82 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_42, 187, 116, v82);
      if ((textures_off & 2) != 0) {
        if (graphic_mode == 7)
          v83 = -113;
        else
          v83 = -125;
        v84 = &config_buffer_variable_30;
      } else {
        if (graphic_mode == 7)
          v83 = -113;
        else
          v83 = -125;
        v84 = &config_buffer_variable_29;
      }
      prt_stringcol(rev_vga_variable_1, v84, 190, 116, v83);
      if (graphic_mode == 6)
        v85 = -113;
      else
        v85 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_43, 187, 126, v85);
      if ((textures_off & 0x100) != 0) {
        if (graphic_mode == 6)
          v86 = -113;
        else
          v86 = -125;
        v87 = &config_buffer_variable_30;
      } else {
        if (graphic_mode == 6)
          v86 = -113;
        else
          v86 = -125;
        v87 = &config_buffer_variable_29;
      }
      prt_stringcol(rev_vga_variable_1, v87, 190, 126, v86);
      if (graphic_mode == 5)
        v88 = -113;
      else
        v88 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_44, 187, 136, v88);
      if ((textures_off & 8) != 0) {
        if (graphic_mode == 5)
          v89 = -113;
        else
          v89 = -125;
        v90 = &config_buffer_variable_30;
      } else {
        if (graphic_mode == 5)
          v89 = -113;
        else
          v89 = -125;
        v90 = &config_buffer_variable_29;
      }
      prt_stringcol(rev_vga_variable_1, v90, 190, 136, v89);
      if (graphic_mode == 4)
        v91 = -113;
      else
        v91 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_45, 187, 146, v91);
      if ((textures_off & 0x20) != 0) {
        if (graphic_mode == 4)
          v92 = -113;
        else
          v92 = -125;
        v93 = &config_buffer_variable_30;
      } else if ((((unsigned int)&loc_3FFFC + 4) & textures_off) != 0) {
        if (graphic_mode == 4)
          v92 = -113;
        else
          v92 = -125;
        v93 = &config_buffer_variable_47;
      } else {
        if (graphic_mode == 4)
          v92 = -113;
        else
          v92 = -125;
        v93 = &config_buffer_variable_29;
      }
      prt_stringcol(rev_vga_variable_1, v93, 190, 146, v92);
      if (graphic_mode == 3)
        v94 = -113;
      else
        v94 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_46, 187, 156, v94);
      if (view_limit) {
        if (graphic_mode == 3)
          v95 = -113;
        else
          v95 = -125;
        v96 = &config_buffer_variable_47;
      } else {
        if (graphic_mode == 3)
          v95 = -113;
        else
          v95 = -125;
        v96 = &config_buffer_variable_48;
      }
      prt_stringcol(rev_vga_variable_1, v96, 190, 156, v95);
      if (graphic_mode == 2)
        v97 = -113;
      else
        v97 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_49, 187, 166, v97);
      if (SVGA_ON)
        v98 = (100 * req_size - (__CFSHL__((100 * req_size) >> 31, 7) + ((100 * req_size) >> 31 << 7))) >> 7;
      else
        v98 = (100 * req_size - (__CFSHL__((100 * req_size) >> 31, 6) + ((100 * req_size) >> 31 << 6))) >> 6;
      sprintf(&buffer, "%3i %%", v98);
      if (graphic_mode == 2)
        v99 = -113;
      else
        v99 = -125;
      prt_stringcol(rev_vga_variable_1, &buffer, 190, 166, v99);
      if (SVGA_ON) {
        if (graphic_mode == 1)
          v100 = -113;
        else
          v100 = -125;
        v101 = (char *)&config_buffer_variable_8;
      } else {
        if (graphic_mode == 1)
          v100 = -113;
        else
          v100 = -125;
        v101 = (char *)&config_buffer_variable_7;
      }
      prt_centrecol(rev_vga_variable_1, v101, 160, 176, v100);
      if (graphic_mode)
        v102 = -125;
      else
        v102 = -113;
      LOBYTE(i) = prt_rightcol(rev_vga_variable_1, config_buffer_variable_13, 187, 186, v102);
      break;
    case 4:
      blankwindow(0, 0, 320, 200);
      prt_centrecol(rev_vga_variable_1, config_buffer_variable_23, 160, 16, 171);
      if (sound_edit == 1)
        v41 = -113;
      else
        v41 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_24, 172, 48, v41);
      volumebar(48, EngineVolume);
      if (sound_edit == 2)
        v42 = -113;
      else
        v42 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_25, 172, 60, v42);
      volumebar(60, SFXVolume);
      if (sound_edit == 3)
        v43 = -113;
      else
        v43 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_26, 172, 72, v43);
      volumebar(72, SpeechVolume);
      if (sound_edit == 4)
        v44 = -113;
      else
        v44 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_27, 172, 84, v44);
      volumebar(84, MusicVolume);
      if (sound_edit == 5)
        v45 = -113;
      else
        v45 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_28, 172, 96, v45);
      if (allengines) {
        if (sound_edit == 5)
          v46 = -113;
        else
          v46 = -125;
        v47 = &config_buffer_variable_31;
      } else {
        if (sound_edit == 5)
          v46 = -113;
        else
          v46 = -125;
        v47 = &config_buffer_variable_32;
      }
      prt_stringcol(rev_vga_variable_1, v47, 175, 96, v46);
      if (sound_edit == 6)
        v48 = -113;
      else
        v48 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_33, 172, 108, v48);
      if (soundon) {
        if (sound_edit == 6)
          v49 = -113;
        else
          v49 = -125;
        v50 = &config_buffer_variable_29;
      } else if (SoundCard) {
        if (sound_edit == 6)
          v49 = -113;
        else
          v49 = -125;
        v50 = &config_buffer_variable_30;
      } else {
        if (sound_edit == 6)
          v49 = -113;
        else
          v49 = -125;
        v50 = &config_buffer_variable_86;
      }
      prt_stringcol(rev_vga_variable_1, v50, 175, 108, v49);
      if (sound_edit == 7)
        v51 = -113;
      else
        v51 = -125;
      prt_rightcol(rev_vga_variable_1, config_buffer_variable_34, 172, 120, v51);
      if (musicon) {
        if (sound_edit == 7)
          v52 = -113;
        else
          v52 = -125;
        v53 = &config_buffer_variable_29;
      } else if (MusicCard || MusicCD) {
        if (sound_edit == 7)
          v52 = -113;
        else
          v52 = -125;
        v53 = &config_buffer_variable_30;
      } else {
        if (sound_edit == 7)
          v52 = -113;
        else
          v52 = -125;
        v53 = &config_buffer_variable_86;
      }
      prt_stringcol(rev_vga_variable_1, v53, 175, 120, v52);
      if (sound_edit)
        v54 = -125;
      else
        v54 = -113;
      LOBYTE(i) = prt_rightcol(rev_vga_variable_1, config_buffer_variable_13, 172, 132, v54);
      break;
    default:
      return i;
  }
  return i;*/
}

//-------------------------------------------------------------------------------------------------

void enable_keyboard()
{
  // Process all pending events first to ensure buffer is current
  UpdateSDL();

  // Flush the keyboard buffer
  while (write_key != read_key || twoparter != 0) {
    fatgetch();
  }
}

//-------------------------------------------------------------------------------------------------

void disable_keyboard()
{
  // Process all pending events first to ensure buffer is current
  UpdateSDL();

  // Flush the keyboard buffer
  while (write_key != read_key || twoparter != 0) {
    fatgetch();
  }
}

//-------------------------------------------------------------------------------------------------

void save_fatal_config()
{
  FILE *fp = ROLLERfopen("FATAL.INI", "w");
  fprintf(fp, "EngineVolume=%d\n", (4 * ((EngineVolume + 1) / 4)));
  fprintf(fp, "SFXVolume=%d\n", (4 * ((SFXVolume + 1) / 4)));
  fprintf(fp, "SpeechVolume=%d\n", (4 * ((SpeechVolume + 1) / 4)));
  fprintf(fp, "MusicVolume=%d\n", (4 * ((MusicVolume + 1) / 4)));
  if (allengines)
    fprintf(fp, "CarE=1\n");
  else
    fprintf(fp, "CarE=0\n");
  if (soundon)
    fprintf(fp, "SfxO=1\n");
  else
    fprintf(fp, "SfxO=0\n");
  if (musicon)
    fprintf(fp, "MusO=1\n");
  else
    fprintf(fp, "MusO=0\n");
  fprintf(fp, "SVGA=%d\n", game_svga ? 1 : 0);
  if (game_svga)
    fprintf(fp, "Size=%d\n", game_size);
  else
    fprintf(fp, "Size=%d\n", 2 * game_size);
  fprintf(fp, "View=%i\n", game_view[0]);
  fprintf(fp, "Names=%i\n", names_on ? 1 : 0);
  fprintf(fp, "P1left=%i\n", userkey[USERKEY_P1LEFT]);
  fprintf(fp, "P1right=%i\n", userkey[USERKEY_P1RIGHT]);
  fprintf(fp, "P1up=%i\n", userkey[USERKEY_P1UP]);
  fprintf(fp, "P1down=%i\n", userkey[USERKEY_P1DOWN]);
  fprintf(fp, "P1upgear=%i\n", userkey[USERKEY_P1UPGEAR]);
  fprintf(fp, "P1downgear=%i\n", userkey[USERKEY_P1DOWNGEAR]);
  fprintf(fp, "P1cheat=%i\n", userkey[USERKEY_P1CHEAT]);
  fprintf(fp, "P2left=%i\n", userkey[USERKEY_P2LEFT]);
  fprintf(fp, "P2right=%i\n", userkey[USERKEY_P2RIGHT]);
  fprintf(fp, "P2up=%i\n", userkey[USERKEY_P2UP]);
  fprintf(fp, "P2down=%i\n", userkey[USERKEY_P2DOWN]);
  fprintf(fp, "P2upgear=%i\n", userkey[USERKEY_P2UPGEAR]);
  fprintf(fp, "P2downgear=%i\n", userkey[USERKEY_P2DOWNGEAR]);
  fprintf(fp, "P2cheat=%i\n", userkey[USERKEY_P2CHEAT]);
  fprintf(fp, "Joy1X=%i\n", x1ok != 0);
  fprintf(fp, "Joy1Y=%i\n", y1ok != 0);
  fprintf(fp, "Joy2X=%i\n", x2ok != 0);
  fprintf(fp, "Joy2Y=%i\n", y2ok != 0);
  if (x1ok) {
    fprintf(fp, "Joy1Xmin=%i\n", JAXmin);
    fprintf(fp, "Joy1Xmax=%i\n", JAXmax);
  }
  if (y1ok) {
    fprintf(fp, "Joy1Ymin=%i\n", JAYmin);
    fprintf(fp, "Joy1Ymax=%i\n", JAYmax);
  }
  if (x2ok) {
    fprintf(fp, "Joy2Xmin=%i\n", JBXmin);
    fprintf(fp, "Joy2Xmax=%i\n", JBXmax);
  }
  if (y2ok) {
    fprintf(fp, "Joy2Ymin=%i\n", JBYmin);
    fprintf(fp, "Joy2Ymax=%i\n", JBYmax);
  }
  name_copy(buffer, player_names[0]);
  fprintf(fp, "Nom=%s\n", buffer);
  fprintf(fp, "Car1=%i\n", Players_Cars[0]);
  if (player_type == 2) {
    name_copy(buffer, player_names[1]);
    fprintf(fp, "Han=%s\n", buffer);
    fprintf(fp, "Car2=%i\n", Players_Cars[1]);
  }
  fprintf(fp, "Level=%i\n", level);
  fprintf(fp, "Damage=%i\n", damage_level);
  fprintf(fp, "Detail=%i\n", textures_off);
  if (view_limit)
    fprintf(fp, "Ahead=1\n");
  else
    fprintf(fp, "Ahead=0\n");
  fprintf(fp, "Record=%i\n", replay_record);
  fprintf(fp, "Game=%i\n", game_type);
  fprintf(fp, "Racers=%i\n", competitors);
  fprintf(fp, "Track=%i\n", TrackLoad);
  fprintf(fp, "Players=%i\n", player_type);
  fprintf(fp, "Ariel1=%s\n", default_names[0]);
  fprintf(fp, "Ariel2=%s\n", default_names[1]);
  fprintf(fp, "DeSilva1=%s\n", default_names[2]);
  fprintf(fp, "DeSilva2=%s\n", default_names[3]);
  fprintf(fp, "Pulse1=%s\n", default_names[4]);
  fprintf(fp, "Pulse2=%s\n", default_names[5]);
  fprintf(fp, "Global1=%s\n", default_names[6]);
  fprintf(fp, "Global2=%s\n", default_names[7]);
  fprintf(fp, "Million1=%s\n", default_names[8]);
  fprintf(fp, "Million2=%s\n", default_names[9]);
  fprintf(fp, "Mission1=%s\n", default_names[10]);
  fprintf(fp, "Mission2=%s\n", default_names[11]);
  fprintf(fp, "Zizin1=%s\n", default_names[12]);
  fprintf(fp, "Zizin2=%s\n", default_names[13]);
  fprintf(fp, "Reise1=%s\n", default_names[14]);
  fprintf(fp, "Reise2=%s\n", default_names[15]);
  fprintf(fp, "NetMes1=%s\n", network_messages[0]);
  fprintf(fp, "NetMes2=%s\n", network_messages[1]);
  fprintf(fp, "NetMes3=%s\n", network_messages[2]);
  fprintf(fp, "NetMes4=%s\n", network_messages[3]);
  fprintf(fp, "ComPort=%i\n", serial_port);
  fprintf(fp, "ModemPort=%i\n", modem_port);
  fprintf(fp, "ModemTone=%i\n", modem_tone);
  fprintf(fp, "ModemInit=%s\n", modem_initstring);
  fprintf(fp, "ModemPhone=%s\n", modem_phone);
  fprintf(fp, "ModemCall=%i\n", modem_call);
  fprintf(fp, "ModemType=%i\n", current_modem);
  fprintf(fp, "NetSlot=%i\n", network_slot);
  fprintf(fp, "ModemBaud=%i\n", modem_baud);
  fclose(fp);
  fp = ROLLERfopen("FATAL.INI", "rb");
  if (fp) {
    fseek(fp, 0, SEEK_END);
    uint32 uiSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *pBuf = (char *)getbuffer(uiSize);
    if (pBuf) {
      fread(pBuf, 1u, uiSize, fp);
      fclose(fp);
      decode((uint8 *)pBuf, uiSize, 77, 101);
      fp = ROLLERfopen("FATAL.INI", "wb");
      if (fp) {
        fwrite(pBuf, 1, uiSize, fp);
        fclose(fp);
      }
      fre((void**)&pBuf);
    } else {
      fclose(fp);
      remove("FATAL.INI");
    }
  }
}

//-------------------------------------------------------------------------------------------------

void load_fatal_config()
{
  // Initialize global variables with default values
  JAXmin = 10000;
  JAXmax = -10000;
  JAYmin = 10000;
  JAYmax = -10000;
  JBXmin = 10000;
  JBXmax = -10000;
  JBYmin = 10000;
  JBYmax = -10000;
  x1ok = 0;
  y1ok = 0;
  x2ok = 0;
  y2ok = 0;
  bitaccept = 0;
  Joy1used = 0;
  Joy2used = 0;
  fatal_ini_loaded = 0;

  // Open FATAL.INI file
  char *pData;
  int iFileSize;
  FILE *pFile;
  char *pDataEnd;
  pFile = ROLLERfopen("FATAL.INI", "rb");
  if (pFile) {
    fatal_ini_loaded = -1;

    // Get file size
    fseek(pFile, 0, SEEK_END);
    iFileSize = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);

    // Allocate buffer and read file
    pData = getbuffer(iFileSize + 1);
    if (pData) {
      fread(pData, 1, iFileSize, pFile);
      fclose(pFile);

      // Decode file contents
      decode(pData, iFileSize, 77, 101);

      // Convert DOS line endings to Unix
      for (int i = 0; i < iFileSize; i++) {
        if (pData[i] == '\r') {
          pData[i] = '\n';
        }
      }

      // Add null terminator
      pDataEnd = pData + iFileSize;
      *pDataEnd = '\0';

      // Read configuration values
      getconfigvalue(pData, "EngineVolume", &EngineVolume, 0, 128);
      getconfigvalue(pData, "SFXVolume", &SFXVolume, 0, 128);
      getconfigvalue(pData, "SpeechVolume", &SpeechVolume, 0, 128);
      getconfigvalue(pData, "MusicVolume", &MusicVolume, 0, 128);
      if (EngineVolume == 128) EngineVolume = 127;
      if (SFXVolume == 128) SFXVolume = 127;
      if (SpeechVolume == 128) SpeechVolume = 127;
      if (MusicVolume == 128) MusicVolume = 127;

      getconfigvalue(pData, "CarE", &allengines, 0, 1);
      if (allengines) allengines = -1;

      getconfigvalue(pData, "SfxO", &soundon, 0, 1);
      if (soundon) soundon = -1;

      getconfigvalue(pData, "MusO", &musicon, 0, 1);
      if (musicon) musicon = -1;

      getconfigvalue(pData, "SVGA", &game_svga, 0, 1);
      if (game_svga == 1) game_svga = -1;
      if (no_mem) game_svga = 0;

      game_size = 128;
      getconfigvalue(pData, "Size", &game_size, 64, 128);
      if (!game_svga) {
        game_size = (game_size - (game_size < 0)) / 2;
      }

      getconfigvalue(pData, "View", &game_view[0], 0, 8);
      getconfigvalue(pData, "Names", &names_on, 0, 2);

      // Read keyboard mappings
      getconfigvalueuc(pData, "P1left",     (uint8 *)&userkey[USERKEY_P1LEFT], 0, 139);
      getconfigvalueuc(pData, "P1right",    (uint8 *)&userkey[USERKEY_P1RIGHT], 0, 139);
      getconfigvalueuc(pData, "P1up",       (uint8 *)&userkey[USERKEY_P1UP], 0, 139);
      getconfigvalueuc(pData, "P1down",     (uint8 *)&userkey[USERKEY_P1DOWN], 0, 139);
      getconfigvalueuc(pData, "P1upgear",   (uint8 *)&userkey[USERKEY_P1UPGEAR], 0, 139);
      getconfigvalueuc(pData, "P1downgear", (uint8 *)&userkey[USERKEY_P1DOWNGEAR], 0, 139);
      getconfigvalueuc(pData, "P1cheat",    (uint8 *)&userkey[USERKEY_P1CHEAT], 0, 139);
      getconfigvalueuc(pData, "P2left",     (uint8 *)&userkey[USERKEY_P2LEFT], 0, 139);
      getconfigvalueuc(pData, "P2right",    (uint8 *)&userkey[USERKEY_P2RIGHT], 0, 139);
      getconfigvalueuc(pData, "P2up",       (uint8 *)&userkey[USERKEY_P2UP], 0, 139);
      getconfigvalueuc(pData, "P2down",     (uint8 *)&userkey[USERKEY_P2DOWN], 0, 139);
      getconfigvalueuc(pData, "P2upgear",   (uint8 *)&userkey[USERKEY_P2UPGEAR], 0, 139);
      getconfigvalueuc(pData, "P2downgear", (uint8 *)&userkey[USERKEY_P2DOWNGEAR], 0, 139);
      getconfigvalueuc(pData, "P2cheat",    (uint8 *)&userkey[USERKEY_P2CHEAT], 0, 139);

      // Read joystick configuration
      int iTemp;
      getconfigvalue(pData, "Joy1X", &iTemp, 0, 1);
      x1ok = iTemp ? 1 : 0;

      getconfigvalue(pData, "Joy1Y", &iTemp, 0, 1);
      y1ok = iTemp ? 2 : 0;

      getconfigvalue(pData, "Joy2X", &iTemp, 0, 1);
      x2ok = iTemp ? 4 : 0;

      getconfigvalue(pData, "Joy2Y", &iTemp, 0, 1);
      y2ok = iTemp ? 8 : 0;

      // Validate calibration values
      if (x1ok) {
        JAXmin = 10000;
        JAXmax = -10000;
        getconfigvalue(pData, "Joy1Xmin", &JAXmin, 0, 0x7FFFFFFF);
        getconfigvalue(pData, "Joy1Xmax", &JAXmax, 0, 0x7FFFFFFF);
        if (JAXmax <= JAXmin) x1ok = 0;
      }
      if (y1ok) {
        JAYmin = 10000;
        JAYmax = -10000;
        getconfigvalue(pData, "Joy1Ymin", &JAYmin, 0, 0x7FFFFFFF);
        getconfigvalue(pData, "Joy1Ymax", &JAYmax, 0, 0x7FFFFFFF);
        if (JAYmax <= JAYmin) y1ok = 0;
      }
      if (x2ok) {
        JBXmin = 10000;
        JBXmax = -10000;
        getconfigvalue(pData, "Joy2Xmin", &JBXmin, 0, 0x7FFFFFFF);
        getconfigvalue(pData, "Joy2Xmax", &JBXmax, 0, 0x7FFFFFFF);
        if (JBXmax <= JBXmin) x2ok = 0;
      }
      if (y2ok) {
        JBYmin = 10000;
        JBYmax = -10000;
        getconfigvalue(pData, "Joy2Ymin", &JBYmin, 0, 0x7FFFFFFF);
        getconfigvalue(pData, "Joy2Ymax", &JBYmax, 0, 0x7FFFFFFF);
        if (JBYmax <= JBYmin) y2ok = 0;
      }

      // Calculate bitmask for accepted joystick axes
      bitaccept = x1ok | y1ok | x2ok | y2ok;

      // Process player names
      char *pNamePos = FindConfigVar(pData, "Nom");
      if (pNamePos) {
        char *pDest = buffer;
        while (*pNamePos != '\n') {
          *pDest++ = *pNamePos++;
        }
        *pDest = '\0';
      }
      if (!buffer[0]) {
        strcpy(buffer, "HUMAN");
      }
      name_copy(player_names[0], buffer);

      // Read various game settings
      getconfigvalue(pData, "Car1", &Players_Cars[0], 0, 15);
      getconfigvalue(pData, "Level", &level, 0, 5);
      getconfigvalue(pData, "Damage", &damage_level, 0, 2);
      getconfigvalue(pData, "Detail", &textures_off, 0, 0x7FFFFFFF);
      getconfigvalue(pData, "Ahead", &view_limit, 0, 1);
      getconfigvalue(pData, "Record", &replay_record, 0, 1);
      getconfigvalue(pData, "Game", &game_type, 0, 2);
      getconfigvalue(pData, "Racers", &competitors, 1, 16);
      getconfigvalue(pData, "Track", &TrackLoad, -1, 24);
      getconfigvalue(pData, "Players", &player_type, 0, 4);

      // Process second player name if needed      
      if (player_type && player_type != 2)
        player_type = 0;
      if (player_type == 2) {
        char *pName2Pos = FindConfigVar(pData, "Han");
        if (pName2Pos) {
          char *pDest = buffer;
          while (*pName2Pos != '\n') {
            *pDest++ = *pName2Pos++;
          }
          *pDest = '\0';
        }
        if (!buffer[0]) {
          strcpy(buffer, "PLAYER 2");
        }
        name_copy(player_names[1], buffer);
        getconfigvalue(pData, "Car2", &Players_Cars[1], -1, 15);
      }

      // Adjust track load for game type
      if (game_type == 1) {
        if (TrackLoad < 1) {
          TrackLoad = 1;
        } else {
          // Clear the lower 3 bits (round down to multiple of 8)
          TrackLoad = ((TrackLoad - 1) & 0xFFFFFFF8) + 1;
        }
      }

      // Process AI driver names
      char *compNameAy[] = {
          "Ariel1", "Ariel2", "DeSilva1", "DeSilva2",
          "Pulse1", "Pulse2", "Global1", "Global2",
          "Million1", "Million2", "Mission1", "Mission2",
          "Zizin1", "Zizin2", "Reise1", "Reise2"
      };
      for (int i = 0; i < 16; i++) {
        char *pNameSrc = FindConfigVar(pData, compNameAy[i]);
        if (pNameSrc) {
          char *pDest = buffer;
          while (*pNameSrc != '\n') {
            *pDest++ = *pNameSrc++;
          }
          *pDest = '\0';
        } else {
          sprintf(buffer, "COMP %d", i + 1);
        }
        name_copy(default_names[i], buffer);
      }

      // Process network messages
      char *netMessageAy[] = {
          "NetMes1", "NetMes2", "NetMes3", "NetMes4"
      };
      for (int i = 0; i < 4; i++) {
        char *pMsgSrc = FindConfigVar(pData, netMessageAy[i]);
        if (pMsgSrc) {
          char *pDest = network_messages[i];
          while (*pMsgSrc != '\n') {
            *pDest++ = *pMsgSrc++;
          }
          *pDest = '\0';
        }
      }

      // Read modem/network settings
      getconfigvalue(pData, "ComPort", &serial_port, 1, 4);
      getconfigvalue(pData, "ModemPort", &modem_port, 1, 4);
      getconfigvalue(pData, "ModemTone", &modem_tone, -10, 10);
      char *pModemInit = FindConfigVar(pData, "ModemInit");
      if (pModemInit) {
        char *pDest = modem_initstring;
        while (*pModemInit != '\n') {
          *pDest++ = *pModemInit++;
        }
        *pDest = '\0';
      }
      char *pModemPhone = FindConfigVar(pData, "ModemPhone");
      if (pModemPhone) {
        char *pDest = modem_phone;
        while (*pModemPhone != '\n') {
          *pDest++ = *pModemPhone++;
        }
        *pDest = '\0';
      }
      getconfigvalue(pData, "ModemCall", &modem_call, -10, 10);
      getconfigvalue(pData, "ModemType", &current_modem, -800, 800);
      getconfigvalue(pData, "ModemBaud", &modem_baud, 9600, 28800);
      getconfigvalue(pData, "NetSlot", &network_slot, 0, 99999999);

      // Free configuration buffer
      fre((void**)&pData);
    } else {
      fclose(pFile);
    }
  }

  remove_uncalibrated();
}

//-------------------------------------------------------------------------------------------------

void getconfigvalue(const char *szConfigText, const char *szVarName, int *piOutVal, int iMin, int iMax)
{
  int iTempVal;
  const char *szValue = FindConfigVar(szConfigText, szVarName);

  if (szValue) {
    if (sscanf(szValue, "%i", &iTempVal) == 1) {
      if (iTempVal < iMin)
        iTempVal = iMin;
      if (iTempVal > iMax)
        iTempVal = iMax;

      *piOutVal = iTempVal;
    }
  }
}

//-------------------------------------------------------------------------------------------------

void getconfigvalueuc(const char *szConfigText, const char *szVarName, uint8 *pbyOutVal, int iMin, int iMax)
{
  short nTempVal;
  const char *szValue = FindConfigVar(szConfigText, szVarName);

  if (szValue) {
    if (sscanf(szValue, "%hi", &nTempVal) == 1) {
      if (nTempVal < iMin)
        nTempVal = iMin;
      if (nTempVal > iMax)
        nTempVal = iMax;
      *pbyOutVal = (unsigned char)nTempVal;
    }
  }
}

//-------------------------------------------------------------------------------------------------

void displaycalibrationbar(int iX, int iY, int iValue)
{
  int iWinW; // esi
  int iUseValue; // ebp
  uint8 *pScrBuf; // ecx
  int iSliderPos; // ebp
  int iRowIdx; // edi
  int iSliderXPos; // eax
  int iSliderPos2; // ebp
  int iRowIdx2; // edi
  int iSliderXPos2; // eax
  int iSavedWinw; // [esp+0h] [ebp-1Ch]

  iWinW = winw;                                 // Save window width for restoration
  iUseValue = iValue;
  if (iValue < -100)                          // Clamp calibration value to valid range [-100, +100]
    iUseValue = -100;
  if (iUseValue > 100)
    iUseValue = 100;
  pScrBuf = &scrbuf[winw * iX / 320 + winw * ((iY * scr_size) >> 6)];// Calculate screen buffer position: scaled X and Y coordinates
  iSavedWinw = (10 * scr_size) >> 6;            // Calculate scaled bar height (10 * scr_size / 64)
  if (current_mode)                           // Branch based on current_mode: different rendering styles
  {
    iSliderPos = iUseValue + 103;               // Mode 1: Calculate slider position (calibration value + 103)
    for (iRowIdx = 0; iRowIdx < iSavedWinw; ++iRowIdx) {                                           // Skip top and bottom border rows
      if (iRowIdx && iRowIdx != iSavedWinw - 1) {
        *pScrBuf = 0x8F;                        // Draw left border (color 0x8F = white)
        pScrBuf[206 * iWinW / 640] = 0x8F;      // Draw right border (color 0x8F = white)
        iSliderXPos = iWinW * iSliderPos / 640; // Calculate slider position in pixels
        pScrBuf[iSliderXPos] = 0xAB;            // Draw slider indicator (center pixel, color 0xAB = orange)
        pScrBuf[iSliderXPos - 1] = -85;         // Draw slider sides (color 0xAB = orange)
        pScrBuf[iSliderXPos - 2] = 0xAB;
        pScrBuf[iSliderXPos + 1] = 0xAB;
        pScrBuf[iSliderXPos + 2] = 0xAB;
        pScrBuf[103 * iWinW / 640] = 0xE7;      // Draw slider scale marks (color 0xE7 = red)
        pScrBuf[104 * iWinW / 640] = 0xE7;
        pScrBuf[102 * iWinW / 640] = 0xE7;
      } else {
        winw = iWinW;                           // Top/bottom border: fill entire bar width with border color
        memset(pScrBuf, 143, 104 * iWinW / 320 - 1);
        iWinW = winw;
      }
      pScrBuf += iWinW;
    }
  } else {
    iSliderPos2 = iUseValue + 105;              // Mode 0: Calculate slider position (calibration value + 105)
    for (iRowIdx2 = 0; iRowIdx2 < iSavedWinw; ++iRowIdx2) {
      if (iRowIdx2 && iRowIdx2 != iSavedWinw - 1) {
        *pScrBuf = 0x8F;                        // Mode 0: Draw borders with color 0x8F (white)
        pScrBuf[208 * iWinW / 640] = 0x8F;
        iSliderXPos2 = iWinW * iSliderPos2 / 640;// Mode 0: Draw slider indicator at calculated position
        pScrBuf[iSliderXPos2] = 0xAB;           // 0xAB = orange
        pScrBuf[iSliderXPos2 - 1] = 0xAB;
        pScrBuf[iSliderXPos2 + 1] = 0xAB;
        pScrBuf[105 * iWinW / 640] = 0xE7;      // Mode 0: Draw center scale mark (color 0xE7 = orange)
      } else {
        winw = iWinW;
        memset(pScrBuf, 143, 104 * iWinW / 320 + 1);
        iWinW = winw;
      }
      pScrBuf += iWinW;
    }
  }
  winw = iWinW;                                 // Restore original window width
}

//-------------------------------------------------------------------------------------------------

void blankwindow(int iX1, int iY1, int iX2, int iY2)
{
  tPolyParams poly; // [esp+0h] [ebp-34h] BYREF

  if (SVGA_ON) {
    iX2 *= 2;
    iY1 *= 2;
    iX1 *= 2;
    iY2 *= 2;
  }
  poly.vertices[0].x = iX2;
  poly.vertices[0].y = iY1;
  poly.vertices[1].x = iX1;
  poly.vertices[1].y = iY1;
  poly.vertices[2].x = iX1;
  poly.vertices[2].y = iY2;
  poly.vertices[3].x = iX2;
  poly.vertices[3].y = iY2;
  poly.uiSurfaceType = 0x200003;
  poly.uiNumVerts = 4;
  POLYFLAT(scrbuf, &poly);
}

//-------------------------------------------------------------------------------------------------

void volumebar(int iX, int iVolume)
{
  uint8 *pScreenRow; // ecx
  int iRowIdx; // esi
  int iBarHeight; // ebp
  unsigned int uiVolumeWidth; // edi

  pScreenRow = &scrbuf[175 * winw / 320 + ((scr_size * iX) >> 6) * winw];// Calculate screen position: Y=175*winw/320, X=scaled position
  iRowIdx = 0;
  iBarHeight = (10 * scr_size) >> 6;            // Calculate scaled bar height (10 * scr_size / 64)
  uiVolumeWidth = 100 * iVolume / 127 * winw / 320;// Calculate volume fill width: volume level (0-127) mapped to 0-100 pixels scaled
  if (iBarHeight > 0)                         // Main rendering loop for each row of the volume bar
  {
    do {                                           // Skip top and bottom rows (draw border only on middle rows)
      if (iRowIdx && iRowIdx != iBarHeight - 1) {
        *pScreenRow = 0x70;                     // Draw left border (0x70 is black in PALETTE.PAL)
        memset(pScreenRow + 1, 0xAB, uiVolumeWidth);// Fill volume level area (0xAB is orange in PALETTE.PAL)
        pScreenRow[101 * winw / 320] = 0x70;    // Draw right border (0x70 is black in PALETTE.PAL)
      } else {
        memset(pScreenRow, 0x70, 102 * winw / 320);// Top/bottom rows: fill entire width with border color (0x70 is black in PALETTE.PAL)
      }
      pScreenRow += winw;                       // Move to next screen row
      ++iRowIdx;
    } while (iRowIdx < iBarHeight);
  }
}

//-------------------------------------------------------------------------------------------------

void remove_uncalibrated()
{
  if (JAXmax - JAXmin < 100)
    x1ok = 0;
  if (JAYmax - JAYmin < 100)
    y1ok = 0;
  if (JBXmax - JBXmin < 100)
    x2ok = 0;
  if (JBYmax - JBYmin < 100)
    y2ok = 0;
  bitaccept = y2ok | y1ok | x1ok | x2ok;
  if (x1ok || y1ok)
    Joy1used = -1;
  else
    Joy1used = x1ok;
  if (x2ok || y2ok)
    Joy2used = -1;
  else
    Joy2used = x2ok;
}

//-------------------------------------------------------------------------------------------------

void LoadRecords()
{
  int iFileHandle; // edx
  int iFileHandle2; // ebp
  //int iRecordNamePos; // edx
  //int iRecordIdx3; // eax
  //int iRecordNamePos2; // edx
  //char *szRecordName2; // edi
  //char *szRecordName3; // edi
  int iFileLength; // eax
  int iFileLength2; // ecx
  //int iRecordNameIdx2; // edx
  //int iRecordIdx2; // eax
  //int iRecordNameIdx3; // edx
  //char *szRecordName4; // edi
  int *pIntBuf; // ebx
  int iRecordNameIdx; // ebp
  int iRecordIdx; // ecx
  int iRecordCarVal; // eax
  int iRecordNamePos4; // esi
  int iRecordNameCharPos; // eax
  //char byNameChar; // dl
  uint8 *pBuf; // [esp+0h] [ebp-24h] BYREF
  int iMaxRecords; // [esp+4h] [ebp-20h]
  int iRecordNamePos3; // [esp+8h] [ebp-1Ch]

  iFileLength = ROLLERfilelength("dgkfc.rec");

  iFileHandle = ROLLERopen("dgkfc.rec", O_BINARY);       // 0x200 = O_BINARY in WATCOM/h/fcntl.h
  iFileHandle2 = iFileHandle;
  if (iFileHandle == -1) {

    //loop without optimizations
    for (int i = 0; i < 25; ++i) {
      int iRecordNamesPos = 9 * i;
      strcpy(RecordNames[iRecordNamesPos], "-----");
      RecordLaps[i] = 128.0f;
      RecordCars[i] = -1;
      RecordKills[i] = 0;
    }
    //iRecordNamePos = 9;
    //RecordCars[0] = -1;
    //RecordLaps[0] = 128.0;
    //RecordKills[0] = 0;
    //iRecordIdx3 = 1;
    //strcpy(RecordNames[0], "----");
    //do {
    //  RecordLaps[iRecordIdx3] = 128.0;
    //  RecordCars[iRecordIdx3] = -1;
    //  RecordKills[iRecordIdx3] = 0;
    //  strcpy(&RecordNames[0][iRecordNamePos], "----");
    //  iRecordNamePos2 = iRecordNamePos + 9;
    //  RecordCars[iRecordIdx3 + 1] = -1;
    //  RecordLaps[iRecordIdx3 + 1] = 128.0;
    //  szRecordName2 = &RecordNames[0][iRecordNamePos2];
    //  RecordKills[iRecordIdx3 + 1] = 0;
    //  iRecordNamePos2 += 9;
    //  strcpy(szRecordName2, "----");
    //  iRecordIdx3 += 3;
    //  szRecordName3 = &RecordNames[0][iRecordNamePos2];
    //  RecordLaps[iRecordIdx3 + 24] = NAN;
    //  *(int *)((char *)&updates + iRecordIdx3 * 4) = 0x43000000;
    //  RecordCars[iRecordIdx3 + 24] = 0;
    //  iRecordNamePos = iRecordNamePos2 + 9;
    //  strcpy(szRecordName3, "----");
    //} while (iRecordIdx3 != 25);
    //// end loop

  } else {
    pBuf = (uint8 *)getbuffer(1024u);
    //iFileLength = filelength(iFileHandle);
    iFileLength2 = iFileLength;
    if (iFileLength == 336 || iFileLength == 504) {
      read(iFileHandle, pBuf, iFileLength);
      close(iFileHandle);
      pIntBuf = (int *)pBuf;
      iRecordNameIdx = 1;
      iMaxRecords = iFileLength2 / 21;
      if (iFileLength2 / 21 >= 1) {
        iRecordIdx = 1;
        iRecordNamePos3 = 18;
        do {
          RecordLaps[iRecordIdx] = (float)((double)*pIntBuf * 0.01);
          iRecordCarVal = pIntBuf[1];
          pIntBuf += 3;
          RecordCars[iRecordIdx] = iRecordCarVal;
          iRecordNamePos4 = iRecordNamePos3;
          RecordKills[iRecordIdx] = *(pIntBuf - 1);
          iRecordNameCharPos = 9 * iRecordNameIdx;

          // Copy 9-character record name
          memcpy(RecordNames[iRecordNameIdx], (uint8*)pIntBuf, 9);
          pIntBuf = (int*)((uint8*)pIntBuf + 9);
          //do {
          //  ++iRecordNameCharPos;
          //  byNameChar = *(_BYTE *)pIntBuf;
          //  pIntBuf = (int *)((char *)pIntBuf + 1);
          //  *((_BYTE *)&fudge_wait + iRecordNameCharPos + 3) = byNameChar;// this is an offset into RecordNames
          //} while (iRecordNameCharPos != iRecordNamePos4);

          if (RecordLaps[iRecordIdx] < 0.4) {
            RecordLaps[iRecordIdx] = 128.0;
            RecordCars[iRecordIdx] = -1;
            RecordKills[iRecordIdx] = 0;
            strcpy(RecordNames[iRecordNameIdx], "----");
          }
          ++iRecordIdx;
          ++iRecordNameIdx;
          iRecordNamePos3 += 9;
        } while (iRecordNameIdx <= iMaxRecords);
      }
      fre((void **)&pBuf);
    } else {

      //loop without optimizations
      for (int i = 0; i < 25; ++i) {
        int iRecordNamesPos = 9 * i;
        strcpy(RecordNames[iRecordNamesPos], "-----");
        RecordLaps[i] = 128.0f;
        RecordCars[i] = -1;
        RecordKills[i] = 0;
      }
      //iRecordNameIdx2 = 9;
      //iRecordIdx2 = 1;
      //RecordKills[0] = 0;
      //RecordLaps[0] = 128.0;
      //RecordCars[0] = -1;
      //strcpy(RecordNames[0], "----");
      //do {
      //  RecordLaps[iRecordIdx2] = 128.0;
      //  RecordKills[iRecordIdx2] = 0;
      //  RecordCars[iRecordIdx2] = -1;
      //  strcpy(&RecordNames[0][iRecordNameIdx2], "----");
      //  iRecordNameIdx3 = iRecordNameIdx2 + 9;
      //  RecordLaps[iRecordIdx2 + 1] = 128.0;
      //  RecordKills[iRecordIdx2 + 1] = 0;
      //  RecordCars[iRecordIdx2 + 1] = -1;
      //  iRecordIdx2 += 3;
      //  strcpy(&RecordNames[0][iRecordNameIdx3], "----");
      //  iRecordNameIdx3 += 9;
      //  *(int *)((char *)&updates + iRecordIdx2 * 4) = 0x43000000;
      //  RecordCars[iRecordIdx2 + 24] = 0;
      //  szRecordName4 = &RecordNames[0][iRecordNameIdx3];
      //  RecordLaps[iRecordIdx2 + 24] = NAN;
      //  iRecordNameIdx2 = iRecordNameIdx3 + 9;
      //  strcpy(szRecordName4, "----");
      //} while (iRecordIdx2 != 25);
      //// end loop

      close(iFileHandle2);
      fre((void **)&pBuf);
    }
  }
}

//-------------------------------------------------------------------------------------------------

void SaveRecords()
{
  uint8 *pBuffer = getbuffer(0x400);  // Get a 1KB buffer
  uint8 *pWritePtr = pBuffer;
  int iNumBytes = 0;

  for (int i = 1; i < 25; ++i) {
    // Convert RecordLaps[i] * 100.0 to int
    double dLaps = (double)RecordLaps[i] * 100.0;
    int iLaps = (int)round(dLaps); //_CHP
    pWritePtr = copy_int(pWritePtr, iLaps);

    // Write RecordCars[i]
    pWritePtr = copy_int(pWritePtr, RecordCars[i]);

    // Write RecordKills[i]
    pWritePtr = copy_int(pWritePtr, RecordKills[i]);

    // Write RecordNames[i]
    for (int j = 0; j < 9; ++j) {
      *pWritePtr++ = RecordNames[i][j];
    }

    iNumBytes += 12 + 9; // 12 bytes from 3 ints, 9 bytes for name
  }

  FILE *f = ROLLERfopen("dgkfc.rec", "rb+"); // Primary mode

  if (!f) {
    f = ROLLERfopen("dgkfc.rec", "wb"); // Fallback mode
  }

  if (f) {
    fwrite(pBuffer, 1, iNumBytes, f);
    fclose(f);
  }

  fre((void**)&pBuffer); // Free the allocated buffer
}

//-------------------------------------------------------------------------------------------------

uint8 *copy_int(uint8 *pDest, uint32 uiValue)
{
  pDest += 3;
  pDest[-3] = (uint8)(uiValue);          // Byte 0 (LSB)
  pDest[-2] = (uint8)(uiValue >> 16);    // Byte 2 (Byte 1 is skipped/overwritten)
  pDest[-1] = (uint8)(uiValue >> 24);    // Byte 3 (MSB)
  return pDest + 1;  // Equivalent to original eax + 4
}

//-------------------------------------------------------------------------------------------------

void ShowATime(float fTime, int iX, int iY)
{
  int iTime; // [esp+0h] [ebp-1Ch]

  //_CHP();
  iTime = (int)(fTime * 100.0);
  if (iTime > 599999)
    iTime = 599999;
  buffer[1] = 0;
  if (iTime >= 0) {
    buffer[0] = iTime % 10 + 48;
    iTime /= 10;
  } else {
    buffer[0] = 45;
  }
  prt_string(rev_vga[1], buffer, iX + 51, iY);
  if (iTime >= 0) {
    buffer[0] = iTime % 10 + 48;
    iTime /= 10;
  } else {
    buffer[0] = 45;
  }
  prt_string(rev_vga[1], buffer, iX + 42, iY);
  prt_string(rev_vga[1], ":", iX + 39, iY);
  if (iTime >= 0) {
    buffer[0] = iTime % 10 + 48;
    iTime /= 10;
  } else {
    buffer[0] = 45;
  }
  prt_string(rev_vga[1], buffer, iX + 30, iY);
  if (iTime >= 0) {
    buffer[0] = iTime % 6 + 48;
    iTime /= 6;
  } else {
    buffer[0] = 45;
  }
  prt_string(rev_vga[1], buffer, iX + 21, iY);
  prt_string(rev_vga[1], ":", iX + 18, iY);
  if (iTime >= 0) {
    buffer[0] = iTime % 10 + 48;
    iTime /= 10;
  } else {
    buffer[0] = 45;
  }
  prt_string(rev_vga[1], buffer, iX + 9, iY);
  if (iTime >= 0)
    buffer[0] = iTime % 10 + 48;
  else
    buffer[0] = 45;
  prt_string(rev_vga[1], buffer, iX, iY);
}

//-------------------------------------------------------------------------------------------------

void setmodex()
{                                               // INT 10h with AX=13h - Set VGA mode 13h (320x200x256) as base
  //__asm { int     10h; INT 10h with AX = 13h - Set VGA mode 13h(320x200x256) as base }
  //modexsethardware();                           // Configure VGA hardware registers for Mode X tweaks
  //__outword(0x3C4u, 0xF02u);                    // Set Sequencer register 02h to 0Fh - enable all 4 bit planes
  //memset(screen, 0, 0x10000u);                  // Clear video memory (64KB) - initialize screen buffer to black
}

//-------------------------------------------------------------------------------------------------

void modexsethardware()
{
  //uint8 bySequencerMemMode; // al
  //uint8 byGraphicsMode; // al
  //uint8 byMemoryMap; // al
  //uint8 byMaxScanLine; // al
  //uint8 byUnderlineLocation; // al
  //uint8 byModeControl; // al
  //
  //__outbyte(0x3C4u, 4u);                        // Sequencer Register 04h (Memory Mode) - configure memory access mode
  //bySequencerMemMode = __inbyte(0x3C5u);
  //__outbyte(0x3C5u, bySequencerMemMode & 3 | 4);// Clear Chain-4 mode, enable planar memory organization for Mode X
  //__outbyte(0x3CEu, 5u);                        // Graphics Controller Register 05h (Graphics Mode) - set read/write mode
  //byGraphicsMode = __inbyte(0x3CFu);
  //__outbyte(0x3CFu, byGraphicsMode & 0xEF);     // Clear bit 4 (Host Odd/Even) - disable odd/even addressing
  //__outbyte(0x3CEu, 6u);                        // Graphics Controller Register 06h (Memory Map) - set memory mapping
  //byMemoryMap = __inbyte(0x3CFu);
  //__outbyte(0x3CFu, byMemoryMap & 0xFD);        // Clear bit 1 (Chain Odd/Even) - disable odd/even chaining
  //__outbyte(0x3D4u, 9u);                        // CRTC Register 09h (Maximum Scan Line) - configure scan line behavior
  //byMaxScanLine = __inbyte(0x3D5u);
  //__outbyte(0x3D5u, byMaxScanLine & 0xE0);      // Clear bits 4-0 (Max Scan Line) - set to 0 for single-scan lines
  //__outbyte(0x3D4u, 0x14u);                     // CRTC Register 14h (Underline Location) - configure memory addressing
  //byUnderlineLocation = __inbyte(0x3D5u);
  //__outbyte(0x3D5u, byUnderlineLocation & 0xBF);// Clear bit 6 (Double Word) - disable double word addressing mode
  //__outbyte(0x3D4u, 0x17u);                     // CRTC Register 17h (Mode Control) - configure display timing mode
  //byModeControl = __inbyte(0x3D5u);
  //__outbyte(0x3D5u, byModeControl | 0x40);
}

//-------------------------------------------------------------------------------------------------

void modexclearscreen()
{
  //__outword(0x3C4u, 0xF02u);                    // Set Sequencer Map Mask to 0Fh - enable writing to all 4 bit planes
  //memset(screen, 0, 0x10000u);                  // Clear all 64KB of video memory to black (color 0)
}

//-------------------------------------------------------------------------------------------------

void copyscreenmodex(uint8 *pSrc, uint8 *pDest)
{
  int x, iBlock;
  for (x = 0; x < 320; x++) {
    int iPlane = x & 3;               // Determine current plane (0-3)
    int iPlaneMask = 1 << iPlane;     // Create bit mask for the plane

    // Set VGA sequencer map mask
    //outportb(0x3C4, 2);              // Select map mask register
    //outportb(0x3C5, iPlaneMask);     // Enable writes to current plane

    unsigned char *pSrcCol = pSrc + (x << 1);  // Source column (every other pixel)
    unsigned char *pDestCol = pDest + (x >> 2); // Destination column group

    // Process 80 blocks (each block = 5 rows)
    for (iBlock = 0; iBlock < 80; iBlock++) {
        // Write 5 rows in unrolled fashion
      pDestCol[0]   = pSrcCol[0];     // Row 0
      pDestCol[80]  = pSrcCol[640];   // Row 1
      pDestCol[160] = pSrcCol[1280];  // Row 2
      pDestCol[240] = pSrcCol[1920];  // Row 3
      pDestCol[320] = pSrcCol[2560];  // Row 4

      pSrcCol += 3200;  // Advance source by 5 rows (5 * 640)
      pDestCol += 400;   // Advance destination by 5 rows (5 * 80)
    }
  }
}

//-------------------------------------------------------------------------------------------------

void start_zoom(const char *szStr, int iPlayerIdx)
{
  int iPlayerIdx_1; // edx
  int iGameCount; // ebp
  char *pszDest; // edi
  char c0; // al
  char c1; // al
  char c0_1; // al
  char c1_1; // al

  iPlayerIdx_1 = iPlayerIdx;
  iGameCount = game_count[iPlayerIdx_1];
  sub_on[iPlayerIdx_1] = 0;
  zoom_size[iPlayerIdx_1] = -1;
  new_zoom[iPlayerIdx_1] = -1;
  pszDest = zoom_mes[iPlayerIdx];
  if (iGameCount == -2) {
    do {
      c0 = *szStr;
      *pszDest = *szStr;
      if (!c0)
        break;
      c1 = szStr[1];
      szStr += 2;
      pszDest[1] = c1;
      pszDest += 2;
    } while (c1);
    game_count[iPlayerIdx_1] = 0;
    game_scale[iPlayerIdx_1] = 32768.0f;
  } else {
    do {
      c0_1 = *szStr;
      *pszDest = *szStr;
      if (!c0_1)
        break;
      c1_1 = szStr[1];
      szStr += 2;
      pszDest[1] = c1_1;
      pszDest += 2;
    } while (c1_1);
    if (game_count[iPlayerIdx_1] == -1) {
      game_count[iPlayerIdx_1] = 0;
    } else if (game_scale[iPlayerIdx_1] == 64.0f) //if (LODWORD(game_scale[iPlayerIdx_1]) == 0x42800000)// 64.0f
    {
      game_count[iPlayerIdx_1] = 72;
    }
  }
}

//-------------------------------------------------------------------------------------------------

void small_zoom(const char *szStr)
{
  char *pszDest; // edi
  char c0; // al
  char c1; // al
  char *pszDest_1; // edi
  char c0_1; // al
  char c1_1; // al

  new_zoom[0] = 0;
  if (game_count[0] == -2) {
    pszDest = zoom_mes[0];
    sub_on[0] = 0;
    zoom_size[0] = 0;
    new_zoom[0] = -1;
    do {
      c0 = *szStr;
      *pszDest = *szStr;
      if (!c0)
        break;
      c1 = szStr[1];
      szStr += 2;
      pszDest[1] = c1;
      pszDest += 2;
    } while (c1);
    game_count[0] = 0;
    game_scale[0] = 32768.0f;
  } else if (!zoom_size[0]) {
    pszDest_1 = zoom_mes[0];
    sub_on[0] = 0;
    zoom_size[0] = 0;
    new_zoom[0] = -1;
    do {
      c0_1 = *szStr;
      *pszDest_1 = *szStr;
      if (!c0_1)
        break;
      c1_1 = szStr[1];
      szStr += 2;
      pszDest_1[1] = c1_1;
      pszDest_1 += 2;
    } while (c1_1);
    if (game_count[0] == -1) {
      game_count[0] = 0;
    } else if (game_scale[0] == 64.0f) //else if (LODWORD(game_scale[0]) == 0x42800000)// 64.0f
    {
      game_count[0] = 72;
    }
  }
}

//-------------------------------------------------------------------------------------------------

void subzoom(const char *szStr)
{
  char *pszDest; // edi
  char c0; // al
  char c1; // al

  if (new_zoom[0]) {
    pszDest = zoom_sub[0];
    sub_on[0] = -1;
    do {
      c0 = *szStr;
      *pszDest = *szStr;
      if (!c0)
        break;
      c1 = szStr[1];
      szStr += 2;
      pszDest[1] = c1;
      pszDest += 2;
    } while (c1);
  }
}

//-------------------------------------------------------------------------------------------------

void make_time(char *szTimeStr, float fTime)
{
  int iTime; // [esp+0h] [ebp-14h]

  //_CHP();
  iTime = (int)(fTime * 100.0);
  if (iTime > 599999)
    iTime = 599999;
  szTimeStr[8] = 0;
  if (iTime >= 0) {
    szTimeStr[7] = iTime % 10 + 48;
    szTimeStr[6] = iTime / 10 % 10 + 48;
    szTimeStr[4] = iTime / 10 / 10 % 10 + 48;
    szTimeStr[3] = iTime / 10 / 10 / 10 % 6 + 48;
    szTimeStr[1] = iTime / 10 / 10 / 10 / 6 % 10 + 48;
    szTimeStr[5] = 58;
    szTimeStr[2] = 58;
    *szTimeStr = iTime / 10 / 10 / 10 / 6 / 10 % 10 + 48;
  } else {
    memcpy(szTimeStr, "--:--:--", 8);
  }
}

//-------------------------------------------------------------------------------------------------

void check_machine_speed()
{
  int iCounter = 0;
  int iTarget = frames + 4;
  int iTimeout = frames + 13;

  // Wait until frames reaches frames + 4
  while (frames != iTarget)
    ;

// Count how many iterations until frames reaches frames + 13
  while (frames != iTimeout) {
    iCounter++;
  }

  // Divide the loop count by 1000 to estimate machine speed
  machine_speed = iCounter / 1000;
}

//-------------------------------------------------------------------------------------------------

void load_language_file(char *szFilename, int iUseConfigBuffer)
{
  FILE *pFile;
  char *szExt;
  char *szTextExt;
  char *szFileExt;
  int i = 0;

  // look for ".eng" in filename
  szExt = strstr(szFilename, ".eng");
  if (szExt) {
    // get translation text extension string based on language index
    szTextExt = (char *)TextExt + language * 4;

    // copy this text extension after the ".eng" part in the filename
    szFileExt = szExt + 1;  // skip the dot
    while (*szTextExt) {
      *szFileExt++ = *szTextExt++;
      if (*szTextExt == 0)
        break;
      *szFileExt++ = *szTextExt++;
    }
    *szFileExt = '\0';
  }

  // try opening the language file
  if (!ROLLERfexists(szFilename)) {
    //Added by ROLLER: compatibility with US release
    ReplaceExtension(szFilename, ".USA");
  }
  pFile = ROLLERfopen(szFilename, "r");
  if (!pFile) {
    ErrorBoxExit("Unable to open file: %s", szFilename);
    //printf("Unable to open file: %s\n", szFilename);
    //doexit(1);
  }

  int iEndFound = 0;
  int iLineOffset = 0;

  while (!iEndFound) {
    // fead a line into buffer
    if (!fgets(buffer, 128, pFile)) break; //512 in original code but buffer is only 128 in size

    // check for "END" keyword
    if (buffer[0] == 'E' && buffer[1] == 'N' && buffer[2] == 'D') {
      iEndFound = 1;
      break;
    }

    // determine destination buffer
    char *szDest;
    if (iUseConfigBuffer == 1) {
      szDest = config_buffer + iLineOffset;
    } else {
      szDest = language_buffer + iLineOffset;
    }

    // copy characters between quotes to dest
    char *szSrc = buffer + 1;  // skip first character
    while (*szSrc != '"' && *szSrc != '\0') {
      *szDest++ = *szSrc++;
    }
    *szDest = '\0';

    // increment iLineOffset
    iLineOffset += 64;
  }

  fclose(pFile);
}

//-------------------------------------------------------------------------------------------------

void do_blip(int iCarIdx)
{
  double dDamage; // st7
  //int iCarOffset; // eax
  int iDamage; // [esp+0h] [ebp-10h]

  // //Calculate car array offset
  // iCarOffset = ViewType[iCarIndex] * sizeof(tCar);

  dDamage = (100.0 - Car[ViewType[iCarIdx]].fHealth) * 0.0099999998 * 13.0;
  //_CHP();
  iDamage = (int)dDamage;

  if (fabs(Car[ViewType[iCarIdx]].fHealth) > FLT_EPSILON)
  //if ((*(_DWORD *)((_BYTE *)&Car[0].fDamage + iCarOffset) & 0x7FFFFFFF) == 0)
    iDamage = 14;

  // Only proceed if car has valid max speed
  if (fabs(Car[ViewType[iCarIdx]].fMaxSpeed) > FLT_EPSILON)
  //if ((LODWORD(Car[ViewType[iCarIdx]].fMaxSpeed) & 0x7FFFFFFF) != 0)
    lastblip[iCarIdx] = iDamage;

  // Play sound effect if conditions are met
  if (iDamage < 14 && iDamage < lastblip[iCarIdx]) {
    if (Car[ViewType[iCarIdx]].byDebugDamage) {
      sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);                    // SOUND_SAMPLE_BUTTON
      lastblip[iCarIdx] = iDamage;
    }
  }
}

//-------------------------------------------------------------------------------------------------
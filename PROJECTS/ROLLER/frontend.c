#include "frontend.h"
#include "graphics.h"
#include "3d.h"
#include "func3.h"
#include "func2.h"
#include "sound.h"
#include "roller.h"
#include "car.h"
#include "moving.h"
#include "network.h"
#include "loadtrak.h"
#include "control.h"
#include "drawtrk3.h"
#include "cdx.h"
#include "polytex.h"
#include "comms.h"
#include "colision.h"
#include "control.h"
#include <fcntl.h>
#include <string.h>
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
//symbol names added by ROLLER
char szSelectEng[] = "select.eng";      //000A1980
char szConfigEng[] = "config.eng";      //000A198C
//char szFArielRaw[] = "FARIEL.RAW";      //000A1A70
//char szFDesilvaRaw[] = "FDESILVA.RAW";  //000A1A7C
//char szFPulseRaw[] = "FPULSE.RAW";      //000A1A8C
//char szFGlobalRaw[] = "FGLOBAL.RAW";    //000A1A98
//char szFMillionRaw[] = "FMILLION.RAW";  //000A1AA4
//char szFMissionRaw[] = "FMISSION.RAW";  //000A1AB4
//char szFZizinRaw[] = "FZIZIN.RAW";      //000A1AC4
//char szFReiseRaw[] = "FREISE.RAW";      //000A1AD0

//-------------------------------------------------------------------------------------------------

int false_starts = -1;    //000A4AB8
int head_x = 186;         //000A4AC0
int head_y = 8;           //000A4AC4
char network_messages[5][14] = { //000A4AC8
  "SLOWCOACH",
  "OUT OF MY WAY",
  "YOU DIE",
  "SUCKER",
  "I WON!"
};
int competitors = 16;     //000A4B70
int manual_control[16] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }; //000A4B74
int infinite_laps = 0;    //000A4C34
int Players_Cars[16] = { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7 }; //000A4C38
int player_type = 0;      //000A4CB8
int cup_won = 0;          //000A4CBC
int game_type = 0;        //000A4CC0
int car_pies[112] =       //000A4CC4
{
  4, 5, 3, 4, 3, 6, 4,
  1, 8, 2, 3, 4, 4, 8,
  5, 3, 4, 2, 7, 5, 4,
  6, 2, 7, 6, 6, 1, 2,
  7, 7, 6, 7, 1, 8, 3,
  2, 6, 1, 4, 2, 7, 7,
  3, 4, 5, 1, 8, 3, 4,
  8, 1, 8, 7, 5, 2, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1
};
int replay_record = 1;    //000A5304
int last_replay = -1;     //000A5308
int last_type = 0;        //000A530C
int network_champ_on = 0; //000A5318
void *font_vga = NULL;    //000A531C
void *title_vga = NULL;   //000A5320
void *front_vga[16] = { NULL }; //000A5324
int font1_offsets[104] =  //000A5364
{
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, -2, 0, 0, 0, 0, 0, 0, -2, -2, 0, 0,
  -2, -2, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2,
  0, 0, 0, 0, 0, 0, -2, 0, -1, -4, 0, -4,
  0, -4, -4, -4, -4, -4, -5, 0, -4, -4, -4,
  -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, 0,
  -4, 0, -4, -4, -4, -4, -4, 0, 0, 0
};
char font1_ascii[256] =   //000A5504
{
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0x24, 0x25, 0x3E, 0x27, 0x28, 0x2A, 0x3D,
  0x2C, 0x2D, 0x2B, 0x2F, 0x3F, 0x38, 0x40, 0x41, 0x1A, 0x1B,
  0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x32, 0x3C,
  0x35, 0x39, 0x36, 0x37, 0x33, 0x00, 0x01, 0x02, 0x03, 0x04,
  0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
  0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
  0x19, 0x3A, 0x43, 0x3B, 0x29, 0x2E, 0xFF, 0x00, 0x01, 0x02,
  0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C,
  0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
  0x17, 0x18, 0x19, 0x30, 0x42, 0x31, 0x34, 0xFF, 0x67, 0xFF,
  0xFF, 0x4B, 0x4D, 0x4A, 0x4C, 0xFF, 0x52, 0x53, 0x50, 0x57,
  0x56, 0x54, 0x4D, 0x4E, 0x51, 0x4F, 0x4F, 0x5A, 0x5C, 0x5A,
  0x62, 0x61, 0x47, 0x5B, 0x63, 0xFF, 0x26, 0xFF, 0xFF, 0x44,
  0x49, 0x55, 0x58, 0x60, 0x5E, 0x5E, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0x45, 0x46, 0x5D, 0x64, 0x65, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x66, 0xFF, 0xFF, 0xFF, 0xFF,
  0x48, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x5F, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
int font2_offsets[96] =   //000A5604
{
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, -1, 0, 0, 0, -2, 0, 0, -2, -2, 0, 0,
  0, 0, -2, -2, 0, 0, 0, 0, 0, 0, 0, -1,
  0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, 0,
  -2, -2, -2, -2, -2, -2, -2, -2, -2, 0, 0, 0,
  -2, -2, -2, -3, -2, -2, 0, 0, 0, 0, 0, 0
};
char font2_ascii[256] =     //000A5784
{
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0x24, 0x25, 0x3C, 0x27, 0x28, 0x2A, 0x3B,
  0x2C, 0x2D, 0x2B, 0x2F, 0x37, 0x3F, 0x38, 0x39, 0x1A, 0x1B,
  0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x5A, 0x3A,
  0x36, 0x40, 0x35, 0x34, 0x31, 0x00, 0x01, 0x02, 0x03, 0x04,
  0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
  0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
  0x19, 0x3D, 0xFF, 0x3E, 0x29, 0x2E, 0xFF, 0x00, 0x01, 0x02,
  0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C,
  0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
  0x17, 0x18, 0x19, 0x32, 0xFF, 0x33, 0x30, 0xFF, 0x42, 0xFF,
  0xFF, 0x44, 0x46, 0x43, 0xFF, 0xFF, 0xFF, 0x48, 0x59, 0x4A,
  0xFF, 0x4B, 0xFF, 0xFF, 0x49, 0xFF, 0x41, 0x4E, 0x50, 0x4C,
  0x56, 0x58, 0xFF, 0xFF, 0x57, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x45, 0x49, 0x4F, 0x55, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0x47, 0x54, 0x53, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x51, 0xFF, 0xFF, 0xFF, 0xFF,
  0x52, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
int font4_offsets[80] =    //000A5AA4
{
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, -5, 0, 0, 0, 0, 0, -7, 0, 0, -6,
  0, -7, -7, -7, -7, -7, -10, 0, -7, -7, -7, -7,
  -7, -7, -7, -7, -7, -1, -7, -7, -7, -7, -7, 0,
  -7, -7, -6, -6, -6, 0, 0, 0
};
char font4_ascii[256] =      //000A5D24
{
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0x29, 0x24, 0x2A, 0x25, 0xFF, 0x1A, 0x1B,
  0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x27, 0xFF,
  0xFF, 0x2B, 0xFF, 0xFF, 0xFF, 0x00, 0x01, 0x02, 0x03, 0x04,
  0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
  0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
  0x19, 0xFF, 0xFF, 0xFF, 0x26, 0x28, 0xFF, 0x00, 0x01, 0x02,
  0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C,
  0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
  0x17, 0x18, 0x19, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0x33, 0x36, 0x32, 0x34, 0xFF, 0x3A, 0x3B, 0x39, 0x3F,
  0x3E, 0x3C, 0x35, 0x36, 0x38, 0x37, 0x37, 0x4A, 0x4C, 0x48,
  0x44, 0xFF, 0x2F, 0x4B, 0x45, 0xFF, 0xFF, 0xFF, 0xFF, 0x2D,
  0x31, 0x3D, 0x49, 0x42, 0x40, 0x40, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0x2C, 0x2E, 0xFF, 0x46, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x47, 0xFF, 0xFF, 0xFF, 0xFF,
  0x30, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x41, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
char font1_ascii_br[256] = // Fatal Brazilian/Saspanish - object_3_variable_1644
{
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0x24, 0x25, 0x3E, 0x27, 0x28, 0x2A, 0x3D,
  0x2C, 0x2D, 0x2B, 0x2F, 0x3F, 0x38, 0x40, 0x41, 0x1A, 0x1B,
  0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x32, 0x3C,
  0x35, 0x39, 0x36, 0x37, 0x33, 0x00, 0x01, 0x02, 0x03, 0x04,
  0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
  0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
  0x19, 0x3A, 0x43, 0x3B, 0x29, 0x2E, 0xFF, 0x00, 0x01, 0x02,
  0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C,
  0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
  0x17, 0x18, 0x19, 0x30, 0x42, 0x31, 0x34, 0xFF, 0x67, 0xFF,
  0xFF, 0x4B, 0x4D, 0x4A, 0x4C, 0xFF, 0x52, 0x53, 0x50, 0x57,
  0x56, 0x54, 0x4D, 0x4E, 0x51, 0x4F, 0x4F, 0x5A, 0x5C, 0x5A,
  0x62, 0x61, 0x47, 0x5B, 0x63, 0xFF, 0x26, 0xFF, 0xFF, 0x44,
  0x49, 0x55, 0x58, 0x60, 0x5E, 0x5E, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0x49, 0x4A, 0x4B, 0x4C, 0x65, 0xFF, 0xFF, 0x67,
  0x50, 0x51, 0x52, 0xFF, 0xFF, 0x55, 0xFF, 0xFF, 0xFF, 0x5E,
  0xFF, 0x59, 0xFF, 0x5B, 0xFF, 0xFF, 0xFF, 0x60, 0x61, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x66, 0xFF, 0xFF, 0xFF, 0xFF,
  0x48, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x55, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
char font2_ascii_br[256] = // Fatal Brazilian/Saspanish - object_3_variable_1646
{
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0x24, 0x25, 0x3C, 0x27, 0x28, 0x2A, 0x3B,
  0x2C, 0x2D, 0x2B, 0x2F, 0x37, 0x3F, 0x38, 0x39, 0x1A, 0x1B,
  0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x5A, 0x3A,
  0x36, 0x40, 0x35, 0x34, 0x31, 0x00, 0x01, 0x02, 0x03, 0x04,
  0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
  0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
  0x19, 0x3D, 0xFF, 0x3E, 0x29, 0x2E, 0xFF, 0x00, 0x01, 0x02,
  0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C,
  0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
  0x17, 0x18, 0x19, 0x32, 0xFF, 0x33, 0x30, 0xFF, 0x42, 0xFF,
  0xFF, 0x44, 0x46, 0x0D, 0xFF, 0xFF, 0xFF, 0x48, 0x59, 0x4A,
  0xFF, 0x4B, 0xFF, 0xFF, 0x49, 0xFF, 0x41, 0x4E, 0x50, 0x4C,
  0x56, 0x58, 0xFF, 0xFF, 0x57, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x45, 0x49, 0x4F, 0x55, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0x45, 0x43, 0x44, 0x46, 0x53, 0xFF, 0xFF, 0x42,
  0x49, 0x59, 0x5B, 0xFF, 0xFF, 0x4A, 0xFF, 0xFF, 0xFF, 0x5C,
  0xFF, 0x4D, 0xFF, 0x50, 0xFF, 0xFF, 0xFF, 0x55, 0x58, 0x26,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x51, 0xFF, 0xFF, 0xFF, 0xFF,
  0x52, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x4A, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
tPoint sel_posns[12] =
{
  { 33, 60 },
  { 33, 82 },
  { 33, 104 },
  { 33, 126 },
  { 33, 148 },
  { 33, 170 },
  { 33, 192 },
  { 33, 214 },
  { 33, 236 },
  { 33, 258 },
  { 33, 280 },
  { 33, 336 }
};
int no_clear = 0;         //000A5E84
char *descript[8] =       //000A5E88
{
  "FARIEL.RAW",
  "FDESILVA.RAW",
  "FPULSE.RAW",
  "FGLOBAL.RAW",
  "FMILLION.RAW",
  "FMISSION.RAW",
  "FZIZIN.RAW",
  "FREISE.RAW"
};
char cheat_names[32][9];  //0016F8F0
char player_names[16][9]; //0016FA10
int teamorder[8];         //0016FAA8
int champorder[16];       //0016FAC8
int team_wins[16];        //0016FB08
int human_control[16];    //0016FB48
int total_wins[16];       //0016FB88
int allocated_cars[14];   //0016FBC8
int team_kills[16];       //0016FC00
int total_kills[16];      //0016FC40
int team_points[8];       //0016FC80
int championship_points[16]; //0016FCA0
int team_fasts[16];       //0016FCE0
int total_fasts[16];      //0016FD20
int non_competitors[16];  //0016FDE0
int player_started[16];   //0016FE20
int player_invul[16];     //0016FE60
int p_texs_off;           //0016FEA0
int p_tex_size;           //0016FEA4
int quit_game;            //0016FEA8
int players;              //0016FEAC
int front_fade;           //0016FEB0
int frontend_on;          //0016FEB4
int cd_cheat;             //0016FEB8
//net_test                //0016FEBC
int my_control;           //0016FEC0
int my_car;               //0016FEC4
int my_number;            //0016FEC8
int my_invul;             //0016FECC
int FastestLap;           //0016FED0
int racers;               //0016FED4
uint32 cheat_mode;        //0016FED8
int Race;                 //0016FEDC
int switch_types;         //0016FEE0
int players_waiting;      //0016FEE4
int switch_sets;          //0016FEE8
int time_to_start;        //0016FEEC
int I_Quit;               //0016FEF0
int StartPressed;         //0016FEF4
int waste;                //0016FEF8
int switch_same;          //0016FEFC
int car_request;          //0016FF00
uint8 oldkeys[14];        //0016FF04
char my_name[14];         //0016FF12

//-------------------------------------------------------------------------------------------------

void title_screens()
{
  winx = 0;
  winy = 0;
  winw = XMAX;
  mirror = 0;
  SVGA_ON = 0;
  winh = YMAX;
  init_screen();
  SVGA_ON = -1;
  init_screen();
  winx = 0;
  winw = XMAX;
  winy = 0;
  winh = YMAX;
  mirror = 0;

  // added by ROLLER, check to see if title.bm and title.pal exist
  // these files were not shipped in the USA localization
  bool bHasTitle = ROLLERfexists("title.bm") && ROLLERfexists("title.pal");

  setpal(bHasTitle ? "title.pal" : "whipped.pal");
  front_vga[0] = load_picture(bHasTitle ? "title.bm" : "whipped.bm");

  if (front_vga[0] && scrbuf) //check added by ROLLER
    display_picture(scrbuf, front_vga[0]);

  copypic(scrbuf, screen);
  loadfatalsample();
  fade_palette(32);
  if ((cheat_mode & (CHEAT_MODE_KILLER_OPPONENTS | CHEAT_MODE_DEATH_MODE)) != 0)
    dospeechsample(SOUND_SAMPLE_FATAL, 0x8000);
  disable_keyboard();
  if ((cheat_mode & (CHEAT_MODE_KILLER_OPPONENTS | CHEAT_MODE_DEATH_MODE)) != 0)
    waitsampledone(SOUND_SAMPLE_FATAL);
  fre(&front_vga[0]);
  freefatalsample();

  // Add by ROLLER, check language to change font table to support Brazilian / Saspanish.
  if (strcmp(languagename, "Brazilian") == 0 || strcmp(languagename, "Saspanish") == 0) {
    SDL_Log("Language: update font1_ascii and font2_ascii to support '%s'", languagename);
    memcpy(font1_ascii, font1_ascii_br, 256);
    memcpy(font2_ascii, font2_ascii_br, 256);
  } 
}

//-------------------------------------------------------------------------------------------------

void copy_screens()
{
  SVGA_ON = -1;
  init_screen();
  winx = 0;
  winw = XMAX;
  winy = 0;
  winh = YMAX;
  mirror = 0;

  setpal("gremlin.pal");
  front_vga[0] = load_picture("gremlin.bm");
  
  display_picture(scrbuf, front_vga[0]);

  fade_palette(32);
  copypic(scrbuf, screen);
  disable_keyboard();
  ticks = 0;
  while (ticks < 180) {
    UpdateSDL();
    UpdateSDLWindow();
  }
  fre(&front_vga[0]);
  fade_palette(0);
}

//-------------------------------------------------------------------------------------------------

void select_screen()
{
  int iMenuSelection; // esi
  int iContinue; // ebp
  int iQuitConfirmed; // edi
  int iPlayer1Car; // eax
  int iNoClear; // eax
  int iPlayer; // edx
  uint8 *pBuf; // edx
  int iPlayer1Car2; // eax
  eCarType carType; // eax
  eCarType carType2; // ebx
  int iCarTexLoaded; // ecx
  int iLoadCarTextures; // edx
  void **ppCartexVgaItr2; // edx
  eCarType cartype3; // eax
  eCarType cartype4; // ebx
  int iCarTexLoaded2; // edx
  int v17; // eax
  int iBlockIdx2; // ebx
  int iPlayerIdx; // edx
  int iPlayerIdx2; // eax
  uint8 **v26; // edx
  void **v27; // eax
  eCarType v28; // eax
  eCarType v29; // ebx
  int v30; // edx
  int v31; // ecx
  int v32; // eax
  int v33; // edx
  uint8 **ppCartexVgaItr_1; // edx
  void **ppCartexVgaToFree; // eax
  eCarType iCar; // eax
  eCarType v38; // ebx
  int iCartexLoaded; // ecx
  int iLoadCarTextures_1; // edx
  uint8 iKey; // al
  uint8 iKey2; // al
  void **v43; // edx
  eCarType carType_1; // eax
  eCarType v45; // ebx
  int iCartexLoaded2; // edx
  int iControl; // edx
  uint8 **ppFrontVgaItr; // edx
  void **pFrontVgaToFre; // eax
  uint8 **ppCartexVgaItr; // edx
  void **pCartexVgaToFre; // eax
  int j; // eax
  int v54; // edx
  int iMaxRacerOffset; // esi
  int iGridOffset; // ecx
  int iRacersIdx; // esi
  int v58; // edx
  int iRacersOffset2; // ecx
  int iMaxRacersOffset2; // edi
  int v61; // ebx
  unsigned int v62; // eax
  int iRacers; // esi
  int iRacersOffset; // ebp
  int k; // ebx
  int v69 = 0; // edi
  int m; // esi
  int v71; // edx
  int v72; // ebx
  int iGridIdx; // eax
  int n; // eax
  int v75; // ecx
  int v76; // edx
  int iInitScreen; // [esp+0h] [ebp-54h]
  int16 iFrames; // [esp+4h] [ebp-50h]
  int v79; // [esp+Ch] [ebp-48h]
  int iBlockIdx; // [esp+10h] [ebp-44h]
  int iLoadCarTex2; // [esp+2Ch] [ebp-28h]
  int v82; // [esp+30h] [ebp-24h]
  int iLoadCarTextures2; // [esp+34h] [ebp-20h]

  // Initialize game state
  time_to_start = 0;
  StartPressed = 0;
  load_language_file(szSelectEng, 0);
  load_language_file(szConfigEng, 1);
  iInitScreen = -1;
  restart_net = 0;
  if (!time_to_start) {
    while (1) {
      cup_won = (textures_off & 0x1000) != 0;
      if ((textures_off & 0x20000) != 0)
        cup_won = cup_won | 2;
      loadfatalsample();
      iContinue = 0;
      v79 = 0;
      player1_car = 0;
      player2_car = 1;
      if (!network_on) {
        players = 1;
        if (iInitScreen)
          tick_on = 0;
      }
      front_fade = 0;
      frontend_on = -1;
      p_tex_size = gfx_size;

      // Load graphical assets
      front_vga[0] = load_picture("frontend.bm");
      front_vga[1] = load_picture("selhead.bm");
      front_vga[2] = load_picture("font2.bm");
      front_vga[3] = load_picture("carnames.bm");
      front_vga[4] = load_picture("opticon2.bm");
      front_vga[5] = load_picture("selicons.bm");
      front_vga[6] = load_picture("selexit.bm");
      front_vga[15] = load_picture("font1.bm");
      fade_palette(0);
      iQuitConfirmed = 0;
      SVGA_ON = -1;
      if (iInitScreen)
        init_screen();
      winx = 0;
      winw = XMAX;
      winy = 0;
      winh = YMAX;
      mirror = 0;
      setpal("frontend.pal");
      if (network_on) {
        Players_Cars[0] = my_car;
        name_copy(player_names[player1_car], my_name);
        iPlayer1Car = player1_car;
        manual_control[player1_car] = my_control;
        player_invul[iPlayer1Car] = my_invul;
        player_type = 1;
        if ((!game_type || game_type == 2) && last_replay != 2) {
          iNoClear = no_clear;
          if (!no_clear && network_on > 0) {
            iPlayer = 0;
            do {
              Players_Cars[iPlayer++] = -1;
              ++iNoClear;
            } while (iNoClear < network_on);
          }
        }
      }
      if (game_type >= 3)
        game_type = last_type;
      replaytype = 0;
      if (network_on && iInitScreen) {
        remove_messages(-1);
        reset_network(0);
      }
      tick_on = -1;
      FindShades();
      check_cars();
      Car[0].nYaw = 0;
      Car[0].nRoll = 0;
      Car[0].pos.fX = 0.0;
      Car[0].pos.fY = 0.0;
      Car[0].pos.fZ = 0.0;
      intro = 0;
      Car[0].nPitch = 0;
      pBuf = (uint8 *)trybuffer(300000u);
      front_vga[7] = pBuf;
      iMenuSelection = 8;
      if (no_mem)
        goto LABEL_24;
      if (pBuf)
        gfx_size = no_mem;
      else
        LABEL_24:
      gfx_size = 1;
      fre((void **)&front_vga[7]);
      set_starts(0);
      car_texs_loaded[0] = 0;
      for (int i = 0; i < 16; ++i) {
        car_texs_loaded[i] = -1;
      }
      iPlayer1Car2 = Players_Cars[player1_car];
      iBlockIdx = iPlayer1Car2;
      LoadCarTextures = 0;
      if (game_type == 1) {
        //loadtrack((_DWORD *)TrackLoad, -1);
        fre((void **)&front_vga[3]);
        front_vga[3] = load_picture("trkname.bm");
        front_vga[13] = load_picture("bonustrk.bm");
        front_vga[14] = load_picture("cupicons.bm");
      } else if (iPlayer1Car2 >= 0) {
        carType = CarDesigns[iPlayer1Car2].carType;
        carType2 = carType;
        iCarTexLoaded = car_texs_loaded[carType];
        iLoadCarTextures = 1;
        if (iCarTexLoaded == -1) {
          LoadCarTexture(carType, 1);
          car_texmap[iBlockIdx] = 1;
          car_texs_loaded[carType2] = 1;
          iLoadCarTextures = 2;
        } else {
          car_texmap[iBlockIdx] = iCarTexLoaded;
        }
        LoadCarTextures = iLoadCarTextures;
      }
      NoOfTextures = 255;
      if (SVGA_ON)
        scr_size = 128;
      else
        scr_size = 64;
      if (!dontrestart)
        startmusic(optionssong);
      dontrestart = 0;
      holdmusic = -1;
      ticks = 0;
      frames = 0;
      if (network_on && iInitScreen) {
        broadcast_mode = -667;
        while (broadcast_mode)
          UpdateSDL();
        name_copy(player_names[player1_car], my_name);
      }
    LABEL_45:
      if (!iContinue)
        break;
      my_car = Players_Cars[player1_car];
      name_copy(my_name, player_names[player1_car]);
      iControl = manual_control[player1_car];
      my_invul = player_invul[player1_car];
      my_control = iControl;
      last_replay = replaytype;
      if (quit_game && network_on) {
        broadcast_mode = -666;
        while (broadcast_mode)
          UpdateSDL();
        tick_on = 0;
        ticks = 0;
        while (ticks < 3)
          ;
        close_network();
      }
      releasesamples();
      if (game_type != 4 && game_type != 3)
        holdmusic = 0;
      fade_palette(0);
      if (game_type != 4 && game_type != 3)
        stopmusic();
      front_fade = 0;
      Players_Cars[player1_car] = iBlockIdx;

      // for (int i = 0; i < 16; ++i) {
      //   fre(&front_vga[i]);
      // }
      ppFrontVgaItr = (uint8 **)front_vga;
      do {
        pFrontVgaToFre = (void **)ppFrontVgaItr++;
        fre(pFrontVgaToFre);
      } while (ppFrontVgaItr != (uint8**)&front_vga[16]);

      if (iBlockIdx >= 0) {
        // for (int i = 0; i < 16; ++i) {
        //   fre(&cartex_vga[i]);
        // }
        ppCartexVgaItr = (uint8 **)cartex_vga;
        do {
          pCartexVgaToFre = (void **)ppCartexVgaItr++;
          fre(pCartexVgaToFre);
        } while (ppCartexVgaItr != (uint8 **)&cartex_vga[16]);
        remove_mapsels();
      }
      gfx_size = p_tex_size;
      no_clear = 0;
      if (!quit_game && !intro) {
        check_cars();
        if (network_on) {
          if (iMenuSelection == 8 && !intro)
            NetworkWait();
        }
      }
      if (iMenuSelection < 8 || !network_on || intro)
        time_to_start = 45;
      if (time_to_start)
        goto LABEL_232;
    }
    iInitScreen = 0;
    if (switch_types) {
      game_type = switch_types - 1;
      switch_types = 0;
      if (!game_type && competitors == 1)
        competitors = 16;
      if (iBlockIdx >= 0) {
        car_texs_loaded[CarDesigns[iBlockIdx].carType] = -1;
        ppCartexVgaItr2 = (void **)cartex_vga;
        do
          fre(ppCartexVgaItr2++);
        while (ppCartexVgaItr2 != (void **)&cartex_vga[16]);
        remove_mapsels();
      }
      if (game_type == 1) {
        //loadtrack((_DWORD *)TrackLoad, -1);
        fre((void **)&front_vga[3]);
        fre((void **)&front_vga[13]);
        fre((void **)&front_vga[14]);
        front_vga[3] = load_picture("trkname.bm");
        front_vga[13] = load_picture("bonustrk.bm");
        front_vga[14] = load_picture("cupicons.bm");
        //Race = ((_BYTE)TrackLoad - 1) & 7;
      } else {
        fre((void **)&front_vga[3]);
        fre((void **)&front_vga[13]);
        fre((void **)&front_vga[14]);
        front_vga[3] = load_picture("carnames.bm");
        if (iBlockIdx >= 0) {
          cartype3 = CarDesigns[iBlockIdx].carType;
          cartype4 = cartype3;
          iLoadCarTextures2 = 1;
          iCarTexLoaded2 = car_texs_loaded[cartype3];
          if (iCarTexLoaded2 == -1) {
            LoadCarTexture(cartype3, 1);
            car_texs_loaded[cartype4] = 1;
            car_texmap[iBlockIdx] = 1;
            iLoadCarTextures2 = 2;
          } else {
            car_texmap[iBlockIdx] = iCarTexLoaded2;
          }
          LoadCarTextures = iLoadCarTextures2;
        }
        network_champ_on = 0;
      }
    }
    iFrames = frames;
    frames = 0;
    if (ticks > 1080 && !iQuitConfirmed && !network_on) {
      intro = -1;
      iContinue = -1;
      replaytype = 2;
    }
    check_cars();
    
    display_picture(scrbuf, front_vga[0]);
    display_block(scrbuf, (tBlockHeader *)front_vga[1], 0, head_x, head_y, 0);
    display_block(scrbuf, (tBlockHeader *)front_vga[6], 0, 36, 2, 0);
    if (iMenuSelection >= 8) {
      display_block(scrbuf, (tBlockHeader *)front_vga[6], 3, 52, 334, 0);
    } else {
      display_block(scrbuf, (tBlockHeader *)front_vga[6], 1, 52, 334, 0);
      front_text(
        (tBlockHeader *)front_vga[2],
        "~",
        font2_ascii,
        font2_offsets,
        sel_posns[iMenuSelection].x,
        sel_posns[iMenuSelection].y,
        0x8Fu,
        0);
    }
    if (game_type == 1) {
      front_text(
        (tBlockHeader *)front_vga[2],
        language_buffer,
        font2_ascii,
        font2_offsets,
        sel_posns[1].x + 132,
        sel_posns[1].y + 7,
        0x8Fu,
        2u);
      if (Race)
        front_text(
          (tBlockHeader *)front_vga[2],
          &language_buffer[128],
          font2_ascii,
          font2_offsets,
          sel_posns[3].x + 132,
          sel_posns[3].y + 7,
          0x8Fu,
          2u);
      else
        front_text(
          (tBlockHeader *)front_vga[2],
          &language_buffer[64],
          font2_ascii,
          font2_offsets,
          sel_posns[3].x + 132,
          sel_posns[3].y + 7,
          0x8Fu,
          2u);
    } else {
      front_text(
        (tBlockHeader *)front_vga[2],
        &language_buffer[256],
        font2_ascii,
        font2_offsets,
        sel_posns[1].x + 132,
        sel_posns[1].y + 7,
        0x8Fu,
        2u);
      front_text(
        (tBlockHeader *)front_vga[2],
        &language_buffer[320],
        font2_ascii,
        font2_offsets,
        sel_posns[3].x + 132,
        sel_posns[3].y + 7,
        0x8Fu,
        2u);
    }
    front_text(
      (tBlockHeader *)front_vga[2],
      &language_buffer[192],
      font2_ascii,
      font2_offsets,
      sel_posns[0].x + 132,
      sel_posns[0].y + 7,
      0x8Fu,
      2u);
    front_text(
      (tBlockHeader *)front_vga[2],
      config_buffer,
      font2_ascii,
      font2_offsets,
      sel_posns[2].x + 132,
      sel_posns[2].y + 7,
      0x8Fu,
      2u);
    front_text(
      (tBlockHeader *)front_vga[2],
      &language_buffer[384],
      font2_ascii,
      font2_offsets,
      sel_posns[4].x + 132,
      sel_posns[4].y + 7,
      0x8Fu,
      2u);
    front_text(
      (tBlockHeader *)front_vga[2],
      &language_buffer[448],
      font2_ascii,
      font2_offsets,
      sel_posns[5].x + 132,
      sel_posns[5].y + 7,
      0x8Fu,
      2u);
    front_text(
      (tBlockHeader *)front_vga[2],
      &language_buffer[512],
      font2_ascii,
      font2_offsets,
      sel_posns[6].x + 132,
      sel_posns[6].y + 7,
      0x8Fu,
      2u);
    front_text(
      (tBlockHeader *)front_vga[2],
      &config_buffer[640],
      font2_ascii,
      font2_offsets,
      sel_posns[7].x + 132,
      sel_posns[7].y + 7,
      0x8Fu,
      2u);
    if (game_type == 1) {
      //display_block(
      //  scrbuf,
      //  (tBlockHeader *)front_vga[14],
      //  (TrackLoad - 1 - (__CFSHL__((TrackLoad - 1) >> 31, 3) + 8 * ((TrackLoad - 1) >> 31))) >> 3,
      //  500,
      //  300,
      //  0);
      if (TrackLoad <= 0) {
        if (TrackLoad)
          front_text((tBlockHeader *)front_vga[2], "EDITOR", font2_ascii, font2_offsets, 190, 350, 0x8Fu, 0);
        else
          front_text((tBlockHeader *)front_vga[2], "TRACK ZERO", font2_ascii, font2_offsets, 190, 350, 0x8Fu, 0);
      } else if (TrackLoad >= 17) {
        display_block(scrbuf, (tBlockHeader *)front_vga[13], TrackLoad - 17, 190, 356, 0);
      } else {
        display_block(scrbuf, (tBlockHeader *)front_vga[3], TrackLoad - 1, 190, 356, 0);
      }
      show_3dmap(cur_TrackZ, 1280, v79);
      if (game_type < 2) {
        v17 = cur_laps[level];
        NoOfLaps = v17;
        if (competitors == 2)
          NoOfLaps = v17 / 2;
        sprintf(buffer, "%s: %i", &language_buffer[4544], NoOfLaps);
        front_text((tBlockHeader *)front_vga[15], buffer, font1_ascii, font1_offsets, 420, 16, 0x8Fu, 1u);
        front_text(
          (tBlockHeader *)front_vga[15],
          &language_buffer[4608],
          font1_ascii,
          font1_offsets,
          420,
          34,
          0x8Fu,
          1u);
        if (RecordCars[TrackLoad] < 0) {
          sprintf(buffer, "%s", RecordNames[TrackLoad]);
        } else {
          //v18 = RecordLaps[TrackLoad] * 100.0;
          //_CHP();
          //LODWORD(v19) = (int)v18;
          //HIDWORD(v19) = (int)v18 >> 31;
          //v20 = v19 / 6000;
          //LODWORD(v19) = (int)v18;
          //v21 = (int)(v19 / 100) % 60;
          //LODWORD(v19) = (int)v18;
          //sprintf(
          //  buffer,
          //  "%s - %s - %02i:%02i:%02i",
          //  RecordNames[TrackLoad],
          //  CompanyNames[RecordCars[TrackLoad] & 0xF],
          //  v20,
          //  v21,
          //  (unsigned int)(v19 % 100));
        }
        front_text((tBlockHeader *)front_vga[15], buffer, font1_ascii, font1_offsets, 420, 52, 0x8Fu, 1u);
      }
    } else if (iBlockIdx >= 0) {
      if (iBlockIdx == CAR_DESIGN_F1WACK)
        DrawCar(scrbuf + 34640, CAR_DESIGN_F1WACK, 6000.0, 1280, 0);
      else
        DrawCar(scrbuf + 34640, iBlockIdx, 2200.0, 1280, 0);
      if (iBlockIdx < 8)
        display_block(scrbuf, (tBlockHeader *)front_vga[3], iBlockIdx, 190, 356, 0);
    }
    display_block(scrbuf, (tBlockHeader *)front_vga[5], player_type, -4, 247, 0);
    display_block(scrbuf, (tBlockHeader *)front_vga[5], game_type + 5, 135, 247, 0);
    switch (iMenuSelection) {
      case 1:
        if (game_type == 1)
          iBlockIdx2 = 8;
        else
          iBlockIdx2 = 1;
        display_block(scrbuf, (tBlockHeader *)front_vga[4], iBlockIdx2, 76, 257, -1);
        break;
      case 3:
        if (game_type == 1 && Race > 0)
          goto LABEL_102;
        display_block(scrbuf, (tBlockHeader *)front_vga[4], 3, 76, 257, -1);
        break;
      case 6:
      LABEL_102:
        display_block(scrbuf, (tBlockHeader *)front_vga[4], 9, 76, 257, -1);
        break;
      case 7:
        display_block(scrbuf, (tBlockHeader *)front_vga[4], 6, 76, 257, -1);
        break;
      case 8:
        display_block(scrbuf, (tBlockHeader *)front_vga[4], 7, 76, 257, -1);
        break;
      default:
        display_block(scrbuf, (tBlockHeader *)front_vga[4], iMenuSelection, 76, 257, -1);
        break;
    }
    if (iBlockIdx < 0)
      front_text((tBlockHeader *)front_vga[15], &language_buffer[4160], font1_ascii, font1_offsets, 400, 200, 0xE7u, 1u);
    if (iQuitConfirmed)
      front_text((tBlockHeader *)front_vga[15], &language_buffer[3456], font1_ascii, font1_offsets, 400, 250, 0xE7u, 1u);
    show_received_mesage();
    copypic(scrbuf, screen);

    if (switch_same > 0) {
      if (game_type != 1 && switch_same - 666 != iBlockIdx) {
        if (iBlockIdx >= 0) {
          car_texs_loaded[CarDesigns[iBlockIdx].carType] = -1;
          v26 = (uint8 **)cartex_vga;
          do {
            v27 = (void **)v26++;
            fre(v27);
          } while (v26 != (uint8 **)&cartex_vga[16]);
          remove_mapsels();
        }
        v28 = CarDesigns[switch_same - 666].carType;
        v29 = v28;
        v82 = 1;
        v30 = car_texs_loaded[v28];
        v31 = switch_same - 666;
        if (v30 == -1) {
          LoadCarTexture(v28, 1);
          car_texs_loaded[v29] = 1;
          car_texmap[v31] = 1;
          v82 = 2;
        } else {
          car_texmap[v31] = v30;
        }
        LoadCarTextures = v82;
      }
      v32 = 0;
      if (players > 0) {
        v33 = 0;
        do {
          v33 += 4;
          *(int *)((char *)&infinite_laps + v33) = switch_same - 666;
          ++v32;
        } while (v32 < players);
      }
      cheat_mode |= CHEAT_MODE_CLONES;
      iBlockIdx = switch_same - 666;
    } else if (switch_same < 0) {
      switch_same = 0;
      iPlayerIdx = 0;
      if (players > 0) {
        iPlayerIdx2 = 0;
        do {
          Players_Cars[iPlayerIdx2++] = -1;
          ++iPlayerIdx;
        } while (iPlayerIdx < players);
      }
      cheat_mode &= ~CHEAT_MODE_CLONES;
    }
    if (switch_sets) {
      if (game_type != 1 && iBlockIdx >= 0) {
        ppCartexVgaItr_1 = (uint8**)cartex_vga;
        car_texs_loaded[CarDesigns[iBlockIdx].carType] = -1;
        do {
          ppCartexVgaToFree = (void **)ppCartexVgaItr_1++;
          fre(ppCartexVgaToFree);
        } while (ppCartexVgaItr_1 != (uint8 **)&cartex_vga[16]);
        remove_mapsels();
        iCar = CarDesigns[iBlockIdx].carType;
        v38 = iCar;
        iCartexLoaded = car_texs_loaded[iCar];
        iLoadCarTextures_1 = 1;
        if (iCartexLoaded == -1) {
          LoadCarTexture(iCar, 1);
          car_texmap[iBlockIdx] = 1;
          car_texs_loaded[v38] = 1;
          iLoadCarTextures_1 = 2;
        } else {
          car_texmap[iBlockIdx] = iCartexLoaded;
        }
        LoadCarTextures = iLoadCarTextures_1;
      }
      switch_sets = 0;
    }
    if (!front_fade) {
      front_fade = -1;
      fade_palette(32);
      frames = 0;
      if (network_on) {
        while (broadcast_mode)
          UpdateSDL();
        broadcast_mode = -1;
        while (broadcast_mode)
          UpdateSDL();
      }
    }
    print_data = 0;
    while (1) {
      UpdateSDL(); //added by ROLLER
      while (1) {
        UpdateSDL(); //added by ROLLER
        if (!fatkbhit()) {
          int16 nNewYaw = Car[0].nYaw + 32 * iFrames;
          nNewYaw &= 0x3FFF;
          Car[0].nYaw = nNewYaw;
          v79 = ((int16)v79 + 32 * iFrames) & 0x3FFF;
          goto LABEL_45;
        }
        ticks = 0;
        iKey = fatgetch();
        if (iQuitConfirmed)
          break;
        if (iKey) {
          if (iKey == 13)                     // KEY_ENTER
          {
            if (iBlockIdx >= 0) {
              v43 = (void **)cartex_vga;
              car_texs_loaded[CarDesigns[iBlockIdx].carType] = -1;
              do
                fre(v43++);
              while (v43 != (void **)&cartex_vga[16]);
              remove_mapsels();
            }
            fre((void **)&front_vga[3]);
            fre((void **)&front_vga[13]);
            fre((void **)&front_vga[14]);
            switch (iMenuSelection) {
              case 0:
                sfxsample(83, 0x8000);
                select_car();
                break;
              case 1:
                sfxsample(83, 0x8000);
                if (game_type == 1)
                  select_disk();
                else
                  select_track();
                break;
              case 2:
                sfxsample(83, 0x8000);
                select_configure();
                break;
              case 3:
                sfxsample(83, 0x8000);
                if (game_type == 1 && Race > 0) {
                  last_type = game_type;
                  game_type = 3;
                  iContinue = -1;
                } else {
                  select_players();
                }
                break;
              case 4:
                sfxsample(83, 0x8000);
                select_type();
                break;
              case 5:
                iContinue = -1;
                sfxsample(83, 0x8000);
                replaytype = 2;
                break;
              case 6:
                last_type = game_type;
                game_type = 4;
                iContinue = -1;
                break;
              case 7:
                iQuitConfirmed = -1;
                sfxsample(83, 0x8000);
                break;
              case 8:
                if (iBlockIdx >= 0) {
                  iContinue = -1;
                  sfxsample(87, 0x8000);
                  netCD = 0;
                  int iTargetTicks = ticks + 108;
                  if (soundon) {
                    while (iTargetTicks > ticks)
                      UpdateSDL();
                  }
                  while (fatkbhit()) {
                    UpdateSDL(); //added by ROLLER
                    fatgetch();
                  }
                  replaytype = replay_record;
                }
                break;
              default:
                break;
            }
            fre((void **)&front_vga[3]);
            fre((void **)&front_vga[13]);
            fre((void **)&front_vga[14]);
            iBlockIdx = Players_Cars[player1_car];
            if (game_type == 1) {
              //loadtrack((_DWORD *)TrackLoad, -1);
              front_vga[3] = load_picture("trkname.bm");
              front_vga[13] = load_picture("bonustrk.bm");
              front_vga[14] = load_picture("cupicons.bm");
            } else {
              front_vga[3] = load_picture("carnames.bm");
              if (iBlockIdx >= 0) {
                carType_1 = CarDesigns[iBlockIdx].carType;
                iLoadCarTex2 = 1;
                v45 = carType_1;
                iCartexLoaded2 = car_texs_loaded[carType_1];
                if (iCartexLoaded2 == -1) {
                  LoadCarTexture(carType_1, 1);
                  car_texs_loaded[v45] = 1;
                  car_texmap[iBlockIdx] = 1;
                  iLoadCarTex2 = 2;
                } else {
                  car_texmap[iBlockIdx] = iCartexLoaded2;
                }
                LoadCarTextures = iLoadCarTex2;
              }
            }
            ticks = 0;
            frames = 0;
          }
        } else {
          iKey2 = fatgetch();
          if (iKey2 >= 0x48u) {
            if (iKey2 <= 0x48u)               // KEY_DOWN
            {
              if (--iMenuSelection < 0)
                iMenuSelection = 0;
            } else if (iKey2 == 80 && ++iMenuSelection > 8)// KEY_UP
            {
              iMenuSelection = 8;
            }
          }
        }
      }
      if (iKey < 0x59u) {
        if (!iKey)
          fatgetch();
      LABEL_155:
        iQuitConfirmed = 0;
      } else {
        if (iKey > 0x59u && iKey != 0x79)
          goto LABEL_155;
        iContinue = -1;
        quit_game = -1;
      }
    }
  }
LABEL_232:
  tick_on = -1;
  messages = -1;
  demo_count = 0;
  demo_control = -1;
  old_mode = -1;
  demo_mode = 0;
  if (replaytype != 2 && !quit_game && game_type < 3)
    AllocateCars();
  if (iMenuSelection == 8 && time_to_start && !intro) {
    localCD = -1;
    if (replaytype != 2) {
      if (player_type && player_type != 2) {
        localCD = cdpresent();
        if (localCD)
          netCD = -1;
      } else {
        localCD = cdpresent();
        if (!localCD)
          cd_error = -1;
      }
    }
    //Race = ((_BYTE)TrackLoad - 1) & 7;
    if (game_type == 1 && !Race) {
      memset(championship_points, 0, sizeof(championship_points));
      memset(team_points, 0, sizeof(team_points));
      memset(total_kills, 0, sizeof(total_kills));
      memset(total_fasts, 0, sizeof(total_fasts));
      memset(total_wins, 0, sizeof(total_wins));
      memset(team_kills, 0, sizeof(team_kills));
      memset(team_fasts, 0, sizeof(team_fasts));
      memset(team_wins, 0, sizeof(team_wins));
    }
    racers = competitors;
    if (competitors == 2) {
      racers = players;
      if (players < 2)
        racers = competitors;
    }
    if (competitors == 1)
      racers = players;
    j = racers;
    v54 = 0;
    if (racers > 0) {
      iMaxRacerOffset = 4 * racers;
      iGridOffset = 0;
      do {
        for (j = 4 * v54; *(int *)((char *)non_competitors + j); j += 4)
          ++v54;
        grid[iGridOffset / 4u] = v54;
        iGridOffset += 4;
        ++v54;
      } while (iGridOffset < iMaxRacerOffset);
    }
    iRacersIdx = racers;
    v58 = 0;
    if (racers < numcars) {
      iRacersOffset2 = 4 * racers;
      iMaxRacersOffset2 = 4 * numcars;
      do {
        for (j = 4 * v58; !*(int *)((char *)non_competitors + j); j += 4)
          ++v58;
        ++iRacersIdx;
        grid[iRacersOffset2 / 4u] = v58;
        iRacersOffset2 += 4;
        ++v58;
      } while (iRacersOffset2 < iMaxRacersOffset2);
    }
    if (game_type == 1 && Race > 0) {
      if (racers > 0) {
        v61 = 4 * racers;
        v62 = 0;
        do {
          v62 += 4;
          finished_car[v62 / 4 + 15] = teamorder[v62 / 4 + 7];
        } while ((int)v62 < v61);
      }
    } else {
      iRacers = racers;
      iRacersOffset = 6 * racers;
      for (k = 0; k < iRacersOffset; grid[j] = v69) {
        //v66 = rand(j);
        //v67 = (iRacers * v66 - (__CFSHL__((iRacers * v66) >> 31, 15) + ((iRacers * v66) >> 31 << 15))) >> 15;
        //v68 = rand(v67);
        //j = (iRacers * v68 - (__CFSHL__((iRacers * v68) >> 31, 15) + ((iRacers * v68) >> 31 << 15))) >> 15;
        //v69 = grid[v67];
        //grid[v67] = grid[j];
        ++k;
      }
      for (m = 0; m < players; ++m) {
        if (level && (cheat_mode & 2) == 0)
          v71 = racers - 2 * level * players;
        else
          v71 = racers - players;
        if (v71 < 0)
          v71 = 0;
        v72 = 0;
        for (iGridIdx = 0; !human_control[grid[iGridIdx]] && iGridIdx < 16; ++iGridIdx)
          ++v72;
        if (v72 < v71) {
          for (n = v71; ; ++n) {
            v75 = grid[n];
            if (!human_control[v75])
              break;
            ++v71;
          }
          v76 = grid[v72];
          grid[v72] = v75;
          grid[n] = v76;
        }
      }
    }
  }
  StartPressed = 0;
  if (game_type != 4 && game_type != 3)
    stopmusic();
}

//-------------------------------------------------------------------------------------------------

void select_disk()
{
  /*
  unsigned int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // ecx
  unsigned int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  __int64 v15; // rax
  int v16; // ecx
  char *v17; // ebx
  int v18; // eax
  int v19; // ebx
  int v20; // eax
  int v21; // ebx
  int v22; // eax
  __int64 champ; // rax
  unsigned __int8 v24; // al
  unsigned __int8 v25; // al
  int v26; // [esp+0h] [ebp-24h]
  int v27; // [esp+8h] [ebp-1Ch]
  int v28; // [esp+Ch] [ebp-18h]
  int v29; // [esp+10h] [ebp-14h]
  int v30; // [esp+14h] [ebp-10h]
  int v31; // [esp+18h] [ebp-Ch]
  int v32; // [esp+1Ch] [ebp-8h]
  int v33; // [esp+20h] [ebp-4h]

  fade_palette(0, a1, a2, 2);
  v3 = 0;
  front_fade = 0;
  v27 = 0;
  v33 = 2;
  v31 = 0;
  check_saves(v4);
  do {
    if (switch_types) {
      game_type = switch_types - 1;
      if (switch_types == 1 && competitors == 1)
        competitors = 16;
      switch_types = 0;
      if (game_type == 1)
        Race = ((_BYTE)TrackLoad - 1) & 7;
      else
        network_champ_on = 0;
    }
    if (!v3)
      a3 = 0;
    display_picture(scrbuf, front_vga[0], a2);
    display_block(2, 0);
    display_block(head_y, 0);
    display_block(336, -1);
    if (v33 < 2)
      front_text(sel_posns[2 * v33], sel_posns_variable_1[2 * v33], 143, 0);
    front_text(sel_posns[0] + 132, sel_posns_variable_1[0] + 7, 143, 2);
    front_text(sel_posns_variable_2 + 132, sel_posns_variable_3 + 7, 143, 2);
    front_text(400, 270, 171, 1);
    front_text(400, 290, 143, 2);
    front_text(405, 290, 143, 0);
    front_text(400, 308, 143, 2);
    front_text(405, 308, 143, 0);
    front_text(400, 326, 143, 2);
    if ((unsigned int)competitors < 8) {
      if (competitors != 2)
        goto LABEL_19;
    } else if ((unsigned int)competitors > 8 && competitors != 16) {
      goto LABEL_19;
    }
    front_text(405, 326, 143, 0);
  LABEL_19:
    front_text(400, 344, 143, 2);
    front_text(405, 344, 143, 0);
    front_text(400, 362, 143, 2);
    front_text(405, 362, 143, 0);
    front_text(400, 380, 143, 2);
    if (player_type != 1 || !net_type || net_type >= (unsigned int)player_type && (unsigned int)net_type <= 2)
      front_text(405, 380, 143, 0);
    v32 = 0;
    v26 = 56;
    v30 = 0;
    v29 = 74;
    do {
      sprintf(&buffer, "%s %i:", language_buffer_variable_38, v32 + 1);
      if (a3 == v32 + 1)
        v5 = 171;
      else
        v5 = 143;
      front_text(300, v26, v5, 2);
      v6 = v32 + 1;
      if (save_status[v30]) {
        v7 = (save_status_variable_1[v30]
            - 1
            - (__CFSHL__((save_status_variable_1[v30] - 1) >> 31, 3)
               + 8 * ((save_status_variable_1[v30] - 1) >> 31))) >> 3;
        v28 = ((LOBYTE(save_status_variable_1[v30]) - 1) & 7) + 1;
        if (v7) {
          if (v7 <= 1) {
            if (a3 == v6)
              v8 = 171;
            else
              v8 = 143;
          } else {
            if (v7 != 2)
              goto LABEL_44;
            if (a3 == v6)
              v8 = 171;
            else
              v8 = 143;
          }
        } else if (a3 == v6) {
          v8 = 171;
        } else {
          v8 = 143;
        }
        front_text(305, v26, v8, 0);
      LABEL_44:
        sprintf(&buffer, "%s %i", language_buffer_variable_4, v28);
        if (a3 == v32 + 1)
          v9 = 171;
        else
          v9 = 143;
        front_text(470, v26, v9, 0);
        if (a3 == v32 + 1)
          v10 = 171;
        else
          v10 = 143;
        front_text(480, v26, v10, 0);
        if (a3 == v32 + 1)
          v11 = 171;
        else
          v11 = 143;
        front_text(460, v29, v11, 2);
        if (a3 == v32 + 1)
          v12 = 171;
        else
          v12 = 143;
        front_text(470, v29, v12, 0);
        if (a3 == v32 + 1)
          v13 = 171;
        else
          v13 = 143;
        front_text(480, v29, v13, 0);
        goto LABEL_64;
      }
      if (a3 == v6)
        v14 = 171;
      else
        v14 = 143;
      front_text(305, v26, v14, 0);
    LABEL_64:
      HIDWORD(v15) = v26 + 40;
      v16 = v29 + 40;
      v26 += 40;
      v30 += 6;
      v29 += 40;
      ++v32;
    } while (v32 < 4);
    v17 = (char *)v31;
    LODWORD(v15) = v31;
    switch (v31) {
      case 0:
        if (network_on)
          goto LABEL_67;
        break;
      case 1:
      case 2:
      case 4:
      LABEL_67:
        v17 = &font1_ascii;
        v16 = (int)&font1_offsets;
        v15 = front_text(400, 230, 231, 1);
        break;
      default:
        break;
    }
    show_received_mesage(v15, HIDWORD(v15), v17, v16);
    copypic((char *)scrbuf, (int)screen);
    if (switch_same > 0) {
      v21 = 0;
      if (players > 0) {
        v22 = 0;
        do {
          ++v22;
          ++v21;
          infinite_laps[v22] = switch_same - 666;
        } while (v21 < players);
      }
      v20 = cheat_mode;
      BYTE1(v20) = BYTE1(cheat_mode) | 0x40;
    LABEL_78:
      cheat_mode = v20;
    } else if (switch_same < 0) {
      switch_same = 0;
      v18 = 0;
      if (players > 0) {
        v19 = 0;
        do {
          ++v19;
          ++v18;
          infinite_laps[v19] = -1;
        } while (v18 < players);
      }
      v20 = cheat_mode;
      BYTE1(v20) = BYTE1(cheat_mode) & 0xBF;
      goto LABEL_78;
    }
    if (!front_fade) {
      front_fade = -1;
      fade_palette(32, 0, -1, v16);
      frames = 0;
    }
    a2 = 1;
    HIDWORD(champ) = 0;
    while (fatkbhit()) {
      v24 = fatgetch();
      if (v24 < 0xDu) {
        if (!v24) {
          v25 = fatgetch();
          if (v25 >= 0x48u) {
            if (v25 <= 0x48u) {
              if (v3) {
                if (a3 > 1) {
                  v31 = HIDWORD(champ);
                  --a3;
                }
              } else {
                v16 = v33;
                if (SHIDWORD(champ) < v33) {
                  v31 = HIDWORD(champ);
                  --v33;
                }
              }
            } else if (v25 == 80) {
              if (v3) {
                if (a3 < 4) {
                  v31 = HIDWORD(champ);
                  ++a3;
                }
              } else {
                v16 = v33;
                if (v33 < 2) {
                  v31 = HIDWORD(champ);
                  ++v33;
                }
              }
            }
          }
        }
      } else if (v24 <= 0xDu) {
        if (v3) {
          if (v3 <= 1) {
            v16 = 2;
            LODWORD(champ) = save_champ(a3, HIDWORD(champ), 1, 2);
            v3 = HIDWORD(champ);
            check_saves(champ);
            v31 = 2;
          } else if (v3 == 2) {
            v16 = save_status[6 * a3 - 6];
            v31 = 1;
            if (HIDWORD(champ) == v16) {
              v31 = 4;
            } else {
              champ = load_champ(a3, HIDWORD(champ), 1);
              v3 = HIDWORD(champ);
            }
          }
        } else if (v33) {
          if ((unsigned int)v33 <= 1) {
            v3 = 2;
            a3 = 1;
            continue;
          }
          if (v33 == 2) {
          LABEL_115:
            v27 = -1;
            continue;
          }
        } else if (!HIDWORD(champ)) {
          v3 = 1;
          a3 = 1;
        }
      } else if (v24 == 27) {
        if (!v3)
          goto LABEL_115;
        v3 = HIDWORD(champ);
        v31 = HIDWORD(champ);
      }
    }
  } while (!v27);
  fade_palette(0, 0, 1, v16);
  front_fade = 0;*/
}

//-------------------------------------------------------------------------------------------------

// Car selection screen - main function handling player car selection UI, 3D car display, and input processing
void select_car()
{
  eCarType currentCarType; // ebx
  int iSelectedCar; // ebp
  eCarDesignIndex iPlayer1Car; // edi
  eCarType carType; // eax
  int iLoadCarTextures; // edx
  int iCartexLoaded; // esi
  int iCarIdx; // eax
  int iCarPieOffset; // edx
  int iInvertedPieValue; // ebx
  int iCurrentCarSelectorPos; // esi
  int iPlayerNameX; // eax
  int iAnimationCounter; // eax
  int iPieChartIndex; // edx
  int iCarStatsOffset; // ebx
  int iCurrentPieValue; // ecx
  int iNextPieValue; // ecx
  int iNewZoomDistance; // ebx
  int iCarAllocationStatus; // edx
  eCarDesignIndex iCarDesignIndex; // eax
  uint8 **ppTextureArray; // edi
  void **ppCurrentTexture; // eax
  int iPlayerCarIndex; // eax
  eCarType eNewCarType; // eax
  int iTextureLoadedStatus; // ecx
  int iLoadTextureFlag; // edx
  int iPlayerLoopCounter; // edx
  unsigned int uiNavigationDirection; // ebx
  uint8 byInputKey; // al
  int16 nRotationAngle; // ax
  uint8 **ppCleanupTextureArray; // edx
  void **ppCleanupTexture; // eax
  float fCarDrawDistance; // [esp+0h] [ebp-80h]
  unsigned int uiPlayerIndex; // [esp+8h] [ebp-78h]
  int blockIdxAy[7]; // [esp+Ch] [ebp-74h] BYREF
  int iStatAnimationFrame; // [esp+28h] [ebp-58h]
  int iOriginalCarSelection; // [esp+2Ch] [ebp-54h]
  int iActivePlayer; // [esp+30h] [ebp-50h]
  int iDelayBeforeRotation; // [esp+34h] [ebp-4Ch]
  int iZoomSpeed; // [esp+38h] [ebp-48h]
  int iZoomDistance; // [esp+3Ch] [ebp-44h]
  int byMenuExitFlag; // [esp+40h] [ebp-40h]
  unsigned int uiNetworkPlayerIndex; // [esp+44h] [ebp-3Ch]
  char *szPlayerName; // [esp+48h] [ebp-38h]
  char *szCurrentCompanyName; // [esp+4Ch] [ebp-34h]
  int iTargetPieValue; // [esp+50h] [ebp-30h]
  int iNextCarIndex; // [esp+58h] [ebp-28h]
  unsigned int uiNetworkLoop; // [esp+5Ch] [ebp-24h]
  int iPieChartY; // [esp+60h] [ebp-20h]
  int iNetworkPlayerCount; // [esp+64h] [ebp-1Ch]

  fade_palette(0);                              // Initialize screen fade and prepare UI graphics
  front_fade = 0;
  front_vga[3] = load_picture("carnames.bm");   // Load car company name graphics (carnames.bm) and car selection UI (selcar2.bm)
  front_vga[7] = load_picture("selcar2.bm");    // Load car selection UI bitmap
  car_request = 0;
  byMenuExitFlag = 0;                           // Initialize selection state: byMenuExitFlag=0 (stay in menu), iOriginalCarSelection=-1 (no backup)
  iOriginalCarSelection = -1;                   // byExitCode = 0 - stay in selection, -1 = exit to menu
  iPlayer1Car = Players_Cars[player1_car];      // iSavedCarIndex = -1 initially, stores original car selection
  if (game_type == 1)                         // Championship mode: restrict car changes except for first race (Race == 0)
  {
    Race = ((uint8)TrackLoad - 1) & 7;
    if ((((uint8)TrackLoad - 1) & 7) != 0)
      iOriginalCarSelection = iPlayer1Car;
  }
  if (iPlayer1Car >= CAR_DESIGN_AUTO) {
    carType = CarDesigns[iPlayer1Car].carType;
    currentCarType = carType;
    iLoadCarTextures = 1;
    iCartexLoaded = car_texs_loaded[carType];
    if (iCartexLoaded == -1) {
      LoadCarTexture(carType, 1u);              // Car texture not loaded yet - load it now and mark as loaded
      iLoadCarTextures = 2;
      car_texmap[iPlayer1Car] = 1;
      car_texs_loaded[currentCarType] = 1;
    } else {
      car_texmap[iPlayer1Car] = iCartexLoaded;
    }
    LoadCarTextures = iLoadCarTextures;
  }
  if (iPlayer1Car < CAR_DESIGN_AUTO)          // Initialize car statistics pie chart display blocks (7 stats: Speed, Acceleration, etc.)
  {
    memset(blockIdxAy, 8, 7 * sizeof(int));
    //_STOSD(blockIdxAy, 8, currentCarType * 4, 7u);
  } else {
    iCarIdx = 0;
    iCarPieOffset = 7 * iPlayer1Car;
    do {
      ++iCarIdx;
      iInvertedPieValue = 9 - car_pies[iCarPieOffset++];
      blockIdxAy[iCarIdx - 1] = iInvertedPieValue;
    } while (iCarIdx < 7);
  }
  iZoomDistance = 2000;                         // Setup 3D car zoom animation: start at 2000 units, zoom out to 40000 (-2000 speed)
  iZoomSpeed = -2000;
  if (iPlayer1Car >= CAR_DESIGN_ZIZIN2)       // Position car selector cursor
    iCurrentCarSelectorPos = 8;
  else
    iCurrentCarSelectorPos = iPlayer1Car;
  if (iCurrentCarSelectorPos < 0)             // Clamp car selector position to valid range (0-8, where 8 = random)
    iCurrentCarSelectorPos = 8;
  iDelayBeforeRotation = 36;                    // 36-frame delay before starting car rotation animation
  iActivePlayer = 0;
  frames = 0;
  if (!byMenuExitFlag) {
    szCurrentCompanyName = CompanyNames[iOriginalCarSelection];
    do {                                           // Handle game type switches (race type, championship, etc.)
      if (switch_types) {
        game_type = switch_types - 1;
        if (switch_types == 1 && competitors == 1)
          competitors = 16;
        switch_types = 0;
        if (game_type == 1)
          Race = ((uint8)TrackLoad - 1) & 7;
        else
          network_champ_on = 0;
      }
      iStatAnimationFrame = frames;
      frames = 0;
      if (SoundCard
        && front_fade
        && SampleHandleCar[84].handles[0] != -1
        && DIGISampleDone(SampleHandleCar[84].handles[0])) {//DIGISampleDone(*(int *)&DIGIHandle, SampleHandleCar[84].handles[0])) {
        frontendsample(0x8000);
        SampleHandleCar[84].handles[0] = -1;
      }
      display_picture(scrbuf, front_vga[0]);    // RENDER FRAME
      if (player_type == 2)                   // Two-player mode
      {
        if (iActivePlayer)
          display_block(scrbuf, (tBlockHeader *)front_vga[1], 6, head_x, head_y, 0);
        else
          display_block(scrbuf, (tBlockHeader *)front_vga[1], 5, head_x, head_y, 0);
        display_block(scrbuf, (tBlockHeader *)front_vga[1], 7, 200, 56, 0);
      } else {
        display_block(scrbuf, (tBlockHeader *)front_vga[1], 1, head_x, head_y, 0);
      }
      display_block(scrbuf, (tBlockHeader *)front_vga[6], 0, 36, 2, 0);
      if (iPlayer1Car < CAR_DESIGN_AUTO) {
        front_text(
          (tBlockHeader *)front_vga[15],
          &language_buffer[4160],
          font1_ascii,
          font1_offsets,
          400,
          200,
          0xE7u,
          1u);
      } else {                                         // Render 3D car model with zoom/rotation
        if (iPlayer1Car == CAR_DESIGN_F1WACK) {
          DrawCar(scrbuf + 34640, CAR_DESIGN_F1WACK, 6000.0, 1280, 0);
        } else if (iDelayBeforeRotation) {
          DrawCar(scrbuf + 34640, iPlayer1Car, 2200.0, 1280, 0);
        } else {
          fCarDrawDistance = (float)iZoomDistance;
          DrawCar(scrbuf + 34640, iPlayer1Car, fCarDrawDistance, 1280, 0);
        }
        if (iPlayer1Car < CAR_DESIGN_ZIZIN2)
          display_block(scrbuf, (tBlockHeader *)front_vga[3], iPlayer1Car, 190, 356, 0);
      }
      display_block(scrbuf, (tBlockHeader *)front_vga[7], 0, 560, 20, 0);// Draw car statistics as 7 pie chart segments (speed, acceleration, braking, etc.)
      uiNetworkLoop = 0;
      iPieChartY = 19;                          // Draw 7 pie chart segments (iY starts at 19, increments by 51)
      do {
        display_block(scrbuf, (tBlockHeader *)front_vga[7], blockIdxAy[uiNetworkLoop / 4], 568, iPieChartY, 0);
        uiNetworkLoop += 4;
        iPieChartY += 51;
      } while (uiNetworkLoop != 28);
      display_block(scrbuf, (tBlockHeader *)front_vga[5], player_type, -4, 247, 0);
      display_block(scrbuf, (tBlockHeader *)front_vga[5], game_type + 5, 135, 247, 0);
      display_block(scrbuf, (tBlockHeader *)front_vga[4], 0, 76, 257, -1);
      if (iCurrentCarSelectorPos >= 8)        // Draw car selection cursor
      {
        display_block(scrbuf, (tBlockHeader *)front_vga[6], 4, 62, 336, -1);
      } else {
        display_block(scrbuf, (tBlockHeader *)front_vga[6], 2, 62, 336, -1);
        front_text(
          (tBlockHeader *)front_vga[2],
          "~",
          font2_ascii,
          font2_offsets,
          sel_posns[iCurrentCarSelectorPos].x,
          sel_posns[iCurrentCarSelectorPos].y,
          0x8Fu,
          0);
      }
      front_text(
        (tBlockHeader *)front_vga[2],
        "AUTO ARIEL",
        font2_ascii,
        font2_offsets,
        sel_posns[0].x + 132,
        sel_posns[0].y + 7,
        0x8Fu,
        2u);                                    // Draw all car company names
      front_text(
        (tBlockHeader *)front_vga[2],
        "DESILVA",
        font2_ascii,
        font2_offsets,
        sel_posns[1].x + 132,
        sel_posns[1].y + 7,
        0x8Fu,
        2u);
      front_text(
        (tBlockHeader *)front_vga[2],
        "PULSE",
        font2_ascii,
        font2_offsets,
        sel_posns[2].x + 132,
        sel_posns[2].y + 7,
        0x8Fu,
        2u);
      front_text(
        (tBlockHeader *)front_vga[2],
        "GLOBAL",
        font2_ascii,
        font2_offsets,
        sel_posns[3].x + 132,
        sel_posns[3].y + 7,
        0x8Fu,
        2u);
      front_text(
        (tBlockHeader *)front_vga[2],
        "MILLION PLUS",
        font2_ascii,
        font2_offsets,
        sel_posns[4].x + 132,
        sel_posns[4].y + 7,
        0x8Fu,
        2u);
      front_text(
        (tBlockHeader *)front_vga[2],
        "MISSION",
        font2_ascii,
        font2_offsets,
        sel_posns[5].x + 132,
        sel_posns[5].y + 7,
        0x8Fu,
        2u);
      front_text(
        (tBlockHeader *)front_vga[2],
        "ZIZIN",
        font2_ascii,
        font2_offsets,
        sel_posns[6].x + 132,
        sel_posns[6].y + 7,
        0x8Fu,
        2u);
      front_text(
        (tBlockHeader *)front_vga[2],
        "REISE WAGON",
        font2_ascii,
        font2_offsets,
        sel_posns[7].x + 132,
        sel_posns[7].y + 7,
        0x8Fu,
        2u);
      if (iCurrentCarSelectorPos < 8 && network_on && (cheat_mode & 0x4000) == 0)// Network mode: show which players have allocated which cars
      {
        front_text(
          (tBlockHeader *)front_vga[15],
          &language_buffer[4672],
          font1_ascii,
          font1_offsets,
          380,
          380,
          0x8Fu,
          2u);
        if (allocated_cars[iCurrentCarSelectorPos]) {
          iPlayerNameX = 385;
          iNetworkPlayerCount = 0;
          if (players > 0) {
            uiNetworkPlayerIndex = 0;
            szPlayerName = player_names[0];
            do {
              if (iCurrentCarSelectorPos == Players_Cars[uiNetworkPlayerIndex / 4]) {
                if (iPlayerNameX == 385)
                  uiPlayerIndex = 0;
                else
                  uiPlayerIndex = 2;
                front_text(
                  (tBlockHeader *)front_vga[15],
                  szPlayerName,
                  font1_ascii,
                  font1_offsets,
                  iPlayerNameX,
                  380,
                  0x8Fu,
                  uiPlayerIndex);
                iPlayerNameX = 620;
              }
              uiNetworkPlayerIndex += 4;
              szPlayerName += 9;
              ++iNetworkPlayerCount;
            } while (iNetworkPlayerCount < players);
          }
        } else {
          front_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[4736],
            font1_ascii,
            font1_offsets,
            385,
            380,
            0x83u,
            0);
        }
      }
      if (iOriginalCarSelection >= 0)         // Display current player's selected car company name at bottom
      {
        if (iActivePlayer)
          sprintf(buffer, "%s %s", &language_buffer[2880], CompanyNames[Players_Cars[player2_car]]);
        else
          sprintf(buffer, "%s %s", &language_buffer[2816], szCurrentCompanyName);
        scale_text((tBlockHeader *)front_vga[15], buffer, font1_ascii, font1_offsets, 375, 316, 231, 1u, 170, 550);
      }
      show_received_mesage();
      copypic(scrbuf, screen);
      iAnimationCounter = iDelayBeforeRotation; // ANIMATION UPDATE: Rotate pie chart segments during delay period
      if (iDelayBeforeRotation) {
        if (iPlayer1Car >= CAR_DESIGN_AUTO) {
          iPieChartIndex = 0;
          iCarStatsOffset = 7 * iPlayer1Car;
          do {
            iTargetPieValue = 9 - car_pies[iCarStatsOffset];
            iCurrentPieValue = blockIdxAy[iPieChartIndex];
            if (iCurrentPieValue != iTargetPieValue) {
              iNextPieValue = iCurrentPieValue + 1;
              blockIdxAy[iPieChartIndex] = iNextPieValue;
              if (iNextPieValue > 8)
                blockIdxAy[iPieChartIndex] = 1;
            }
            ++iPieChartIndex;
            ++iCarStatsOffset;
          } while (iPieChartIndex < 7);
        }
      } else {
        for (int i = 0; i < 7; i++) {
            blockIdxAy[i]++;
            if (blockIdxAy[i] > 8) {
                blockIdxAy[i] = 1;
            }
        }
        //do {
        //  int iIncrementedPieValue = *(int *)((char *)blockIdxAy + iAnimationCounter) + 1;
        //  *(int *)((char *)blockIdxAy + iAnimationCounter) = iIncrementedPieValue;
        //  if (iIncrementedPieValue > 8)
        //    *(int *)((char *)blockIdxAy + iAnimationCounter) = 1;
        //  iAnimationCounter += 4;
        //} while (iAnimationCounter != 28);
      }
      if (!iDelayBeforeRotation)              // ZOOM ANIMATION: Handle 3D car zoom in/out with car switching logic
      {
        iNewZoomDistance = iStatAnimationFrame * iZoomSpeed + iZoomDistance;
        iZoomDistance = iNewZoomDistance;
        if (iNewZoomDistance <= 40000)        // Handle car zoom in/out animation and car selection
        {
          if (iNewZoomDistance < 4000) {
            iZoomDistance = 4000;
            iDelayBeforeRotation = 72;
          }
        } else {
          iCarAllocationStatus = allocated_cars[iSelectedCar];// Zoom reached maximum - switch cars if available, otherwise restore previous car
          iZoomDistance = 40000;
          iZoomSpeed = -iZoomSpeed;
          if (iCarAllocationStatus < 2) {                                     // Free old car textures and load new car's textures
            if (iPlayer1Car >= CAR_DESIGN_AUTO) {
              iCarDesignIndex = iPlayer1Car;
              ppTextureArray = cartex_vga;
              car_texs_loaded[CarDesigns[iCarDesignIndex].carType] = -1;
              do {
                ppCurrentTexture = (void **)ppTextureArray++;
                fre(ppCurrentTexture);
              } while (ppTextureArray != &cartex_vga[16]);
              remove_mapsels();
              if (frontendspeechptr)
                fre((void **)&frontendspeechptr);
            }
            if (game_type == 1 && Race > 0) {
              iPlayer1Car = iSelectedCar;
            } else {
              if (iActivePlayer)
                iPlayerCarIndex = player2_car;
              else
                iPlayerCarIndex = player1_car;
              iPlayer1Car = iSelectedCar;
              Players_Cars[iPlayerCarIndex] = iSelectedCar;
            }
            if (iPlayer1Car >= CAR_DESIGN_AUTO) {
              eNewCarType = CarDesigns[iPlayer1Car].carType;
              iTextureLoadedStatus = car_texs_loaded[eNewCarType];

              if (iTextureLoadedStatus == -1) {
                  // Texture not loaded yet - load it now
                  LoadCarTexture(eNewCarType, 1u);
                  car_texmap[iPlayer1Car] = 1;
                  car_texs_loaded[eNewCarType] = 1;
                  iLoadTextureFlag = 2;
              } else {
                  // Texture already loaded - use existing
                  car_texmap[iPlayer1Car] = iTextureLoadedStatus;
                  iLoadTextureFlag = 1;
              }
              //eNewCarType = CarDesigns[iPlayer1Car].carType;
              //eCarTypeBackup = eNewCarType;
              //uiCarArrayOffset = 4 * iPlayer1Car;
              //iTextureLoadedStatus = car_texs_loaded[eNewCarType];
              //iLoadTextureFlag = 1;
              //if (iTextureLoadedStatus == -1) {
              //  LoadCarTexture(eNewCarType, 1u);
              //  car_texmap[uiCarArrayOffset / 4] = 1;
              //  car_texs_loaded[eCarTypeBackup] = 1;
              //  iLoadTextureFlag = 2;
              //} else {
              //  car_texmap[uiCarArrayOffset / 4] = iTextureLoadedStatus;
              //}
              LoadCarTextures = iLoadTextureFlag;
              if (!network_on)
                check_cars();
            }
          } else {
            if (iActivePlayer)
              iPlayer1Car = Players_Cars[player2_car];
            else
              iPlayer1Car = Players_Cars[player1_car];
            iSelectedCar = iPlayer1Car;
          }
          if (iPlayer1Car >= CAR_DESIGN_AUTO) {
            sfxsample(84, 0x8000);
            if (iPlayer1Car < CAR_DESIGN_ZIZIN2)
              loadfrontendsample(descript[iPlayer1Car]);
            if (!SamplePtr[84])
              frontendsample(0x8000);
          }
          broadcast_mode = -1;
          while (broadcast_mode) {
            UpdateSDL();
          }
          frames = 0;
        }
      }
      if (car_request < 0)                    // NETWORK CAR REQUESTS: Handle incoming car selection requests from other players
      {
        iDelayBeforeRotation = 0;
        iZoomSpeed = 2000;
        iSelectedCar = -car_request - 1;
        sfxsample(85, 0x8000);
        car_request = 0;
        if ((cheat_mode & 0x4000) != 0)
          switch_same = iSelectedCar + 666;
      }
      if (switch_same > 0)                    // CHEAT MODE: Handle "switch_same" command to force all players to same car
      {
        if (switch_same - 666 != Players_Cars[player1_car]) {
          iSelectedCar = switch_same - 666;
          iZoomSpeed = 2000;
          iDelayBeforeRotation = 0;
          sfxsample(85, 0x8000);

          if (players > 0) {
              for (iPlayerLoopCounter = 0; iPlayerLoopCounter < players; iPlayerLoopCounter++) {
                  Players_Cars[iPlayerLoopCounter] = switch_same - 666;
              }
          }
          //iPlayerLoopCounter = 0;
          //if (players > 0) {
          //  iPlayerArrayOffset = 0;
          //  do {
          //    iPlayerArrayOffset += 4;
          //    ++iPlayerLoopCounter;
          //    *(int *)((char *)&infinite_laps + iPlayerArrayOffset) = switch_same - 666;// offset into Players_Cars
          //  } while (iPlayerLoopCounter < players);
          //}

          cheat_mode |= CHEAT_MODE_CLONES;
        }
      } else if (switch_same < 0) {
        switch_same = 0;
        iDelayBeforeRotation = 0;
        iZoomSpeed = 2000;
        iSelectedCar = -1;
        sfxsample(85, 0x8000);
        cheat_mode &= ~CHEAT_MODE_CLONES;
      }
      if (switch_sets) {
        iSelectedCar = iPlayer1Car;
        iDelayBeforeRotation = 0;
        iZoomSpeed = 2000;
        sfxsample(85, 0x8000);
        switch_sets = 0;
      }
      if (!front_fade)                        // Screen fade-in: Load car voice sample and fade palette to visible
      {
        if ((unsigned int)iPlayer1Car < CAR_DESIGN_ZIZIN2)
          loadfrontendsample(descript[iPlayer1Car]);
        front_fade = -1;
        fade_palette(32);
        frontendsample(0x8000);
        frames = 0;
      }
      uiNavigationDirection = 0;
      iNextCarIndex = iCurrentCarSelectorPos + 1;
      while (fatkbhit())                      // KEYBOARD INPUT PROCESSING: Handle all user input and navigation
      {
        byInputKey = fatgetch();
        if (byInputKey < 0x20u) {
          if (byInputKey < 0xDu) {
            if (!byInputKey) {
              switch ((uint8)fatgetch()) {
                case 0x48u:
                case 0x4Bu:
                  goto LABEL_152;               // Arrow keys: Handle up/down/left/right navigation between cars
                case 0x4Du:
                case 0x50u:
                  goto LABEL_153;
                default:
                  continue;
              }
            }
          } else if (byInputKey <= 0xDu)        // Enter key: Confirm car selection or trigger car switching animation
          {
            if (iCurrentCarSelectorPos != 8 && iCurrentCarSelectorPos != iPlayer1Car || iCurrentCarSelectorPos == 8) {
              remove_frontendspeech();
              sfxsample(83, 0x8000);
            }
            if (iCurrentCarSelectorPos == iPlayer1Car
              && SoundCard
              && frontendspeechhandle != -1
              && DIGISampleDone(frontendspeechhandle)) { //DIGISampleDone(*(int *)&DIGIHandle, frontendspeechhandle)) {
              frontendspeechhandle = -1;
              frontendsample(0x8000);
            }
            if (iCurrentCarSelectorPos == 8) {
              byMenuExitFlag = -1;
            } else if (iPlayer1Car != iCurrentCarSelectorPos
                   && (allocated_cars[iCurrentCarSelectorPos] < 2 || game_type == 1 && Race > 0)) {
              if (network_on) {
                car_request = iNextCarIndex;
                broadcast_mode = -9999;
                while (broadcast_mode)
                  UpdateSDL();
              } else {
                iDelayBeforeRotation = 0;
                iZoomSpeed = 2000;
                iSelectedCar = iCurrentCarSelectorPos;
                sfxsample(85, 0x8000);
              }
            }
          } else if (byInputKey == 27)          // Escape key: Exit to main menu
          {
            byMenuExitFlag = -1;
            remove_frontendspeech();
            sfxsample(83, 0x8000);
          }
        } else if (byInputKey <= 0x20u) {                                       // Space key: Switch between Player 1 and Player 2 in two-player mode
          if (player_type == 2) {
            if (iActivePlayer) {
              iActivePlayer = 0;
              iDelayBeforeRotation = 0;
              iZoomSpeed = 2000;
              iSelectedCar = Players_Cars[player1_car];
            } else {
              iDelayBeforeRotation = 0;
              iActivePlayer = 1;
              iZoomSpeed = 2000;
              iSelectedCar = Players_Cars[player2_car];
            }
          }
        } else if (byInputKey < 0x2Du) {
          if (byInputKey == 43)
            LABEL_153:
          uiNavigationDirection = 1;
        } else {
          if (byInputKey <= 0x2Du)
            goto LABEL_152;
          if (byInputKey >= 0x3Du) {
            if (byInputKey <= 0x3Du)
              goto LABEL_153;
            if (byInputKey == 95)
              LABEL_152:
            uiNavigationDirection = 2;
          }
        }
        UpdateSDL();

      }
      if (uiNavigationDirection)              // Apply navigation input to move car selector cursor
      {
        if (uiNavigationDirection > 1) {
          if (--iCurrentCarSelectorPos < 0)
            iCurrentCarSelectorPos = 0;
        } else if (++iCurrentCarSelectorPos > 8) {
          iCurrentCarSelectorPos = 8;
        }
      }
      nRotationAngle = Car[0].nYaw + 32 * iStatAnimationFrame;// Update 3D car rotation angle for spinning animation
      nRotationAngle &= 0x3FFFu;
      Car[0].nYaw = nRotationAngle;

      UpdateSDL();
    } while (!byMenuExitFlag);                  // MAIN SELECTION LOOP - Handle UI rendering, input, and car switching
  }
  fade_palette(0);                              // CLEANUP: Fade screen, free graphics memory, restore original car selection
  fre((void **)&front_vga[7]);
  if (frontendspeechptr)
    fre((void **)&frontendspeechptr);
  front_fade = 0;
  if (iPlayer1Car >= CAR_DESIGN_AUTO) {
    ppCleanupTextureArray = cartex_vga;
    car_texs_loaded[CarDesigns[iPlayer1Car].carType] = -1;
    do {
      ppCleanupTexture = (void **)ppCleanupTextureArray++;
      fre(ppCleanupTexture);
    } while (ppCleanupTextureArray != &cartex_vga[16]);
    remove_mapsels();
  }
  if (iOriginalCarSelection >= 0)
    Players_Cars[player1_car] = iOriginalCarSelection;
}

//-------------------------------------------------------------------------------------------------

void select_configure()
{
  /*
  int v4; // ebx
  int i; // ecx
  __int64 v6; // rax
  _BYTE *v7; // eax
  int v8; // edx
  int v9; // esi
  char *v10; // edi
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // edi
  int v18; // eax
  int v19; // eax
  int v20; // edi
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int v30; // eax
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // eax
  int v35; // ebx
  int v36; // ebx
  int v37; // ebx
  int v38; // edi
  int v39; // ebx
  int v40; // ebx
  int v41; // ebx
  int v42; // edi
  int v43; // ebx
  int v44; // eax
  int v45; // edx
  int v46; // eax
  int v47; // eax
  int v48; // eax
  int v49; // eax
  int v50; // eax
  int v51; // esi
  char *v52; // edi
  int v53; // eax
  int v54; // eax
  int v55; // eax
  int v56; // eax
  int v57; // esi
  char *v58; // edi
  int v59; // eax
  int v60; // eax
  int v61; // eax
  int v62; // eax
  int v63; // eax
  int v64; // eax
  int v65; // eax
  int v66; // eax
  int v67; // eax
  int v68; // eax
  int v69; // eax
  int v70; // eax
  int v71; // eax
  int v72; // eax
  int v73; // eax
  int v74; // eax
  int v75; // eax
  int v76; // eax
  int v77; // eax
  int v78; // eax
  int v79; // eax
  int v80; // eax
  int v81; // eax
  int v82; // eax
  int v83; // eax
  int v84; // eax
  int v85; // eax
  int v86; // eax
  int v87; // eax
  int v88; // eax
  int v89; // eax
  int v90; // eax
  int v91; // eax
  int v92; // eax
  int v93; // eax
  int v94; // eax
  int v95; // eax
  int v96; // eax
  int v97; // eax
  int v98; // eax
  int v99; // eax
  int v100; // eax
  int v101; // eax
  int v102; // eax
  int v103; // eax
  int v104; // eax
  int v105; // eax
  int v106; // eax
  int v107; // eax
  int v108; // eax
  int v109; // eax
  int v110; // eax
  int v111; // edi
  int v112; // esi
  char *k; // eax
  int v114; // edx
  int v115; // eax
  int v116; // eax
  int v117; // eax
  int v118; // eax
  int v119; // eax
  int v120; // eax
  int v121; // eax
  int v122; // eax
  int v123; // edi
  int v124; // eax
  int v125; // edx
  int v126; // eax
  int v127; // eax
  int v128; // eax
  unsigned int v129; // eax
  unsigned int v130; // eax
  int v131; // edi
  int v132; // edi
  int v133; // eax
  unsigned int v134; // eax
  int v135; // eax
  bool v136; // edi
  int v137; // eax
  int v138; // edx
  char *v139; // eax
  int v140; // eax
  int v141; // eax
  int v142; // eax
  char *v143; // eax
  int v144; // edi
  unsigned int v145; // eax
  int v146; // eax
  int v147; // edi
  bool v148; // eax
  unsigned int v149; // eax
  unsigned int v150; // eax
  unsigned int v151; // eax
  int v152; // edi
  bool v153; // edi
  unsigned int v154; // eax
  int v155; // eax
  int v156; // eax
  int v157; // eax
  int v158; // eax
  unsigned int v159; // eax
  int v160; // eax
  int v161; // esi
  unsigned int v162; // eax
  int v163; // eax
  bool v164; // esi
  unsigned int v165; // eax
  _BOOL1 j; // zf
  int v167; // eax
  int v168; // [esp-10h] [ebp-16h]
  int v169; // [esp-10h] [ebp-16h]
  int v170; // [esp-Ch] [ebp-12h]
  int v171; // [esp-Ch] [ebp-12h]
  __int64 v172; // [esp+0h] [ebp-6h] BYREF
  int v173; // [esp+8h] [ebp+2h]
  int v174; // [esp+Ch] [ebp+6h]
  int v175; // [esp+10h] [ebp+Ah]
  int v176; // [esp+14h] [ebp+Eh]
  int v177; // [esp+18h] [ebp+12h]
  int v178; // [esp+1Ch] [ebp+16h]
  _BYTE v179[12]; // [esp+20h] [ebp+1Ah] BYREF
  int v180; // [esp+2Ch] [ebp+26h]
  int v181; // [esp+30h] [ebp+2Ah]
  int v182; // [esp+34h] [ebp+2Eh]
  int v183; // [esp+38h] [ebp+32h]
  int v184; // [esp+3Ch] [ebp+36h]
  int v185; // [esp+40h] [ebp+3Ah]
  int v186; // [esp+44h] [ebp+3Eh]
  int v187; // [esp+48h] [ebp+42h]
  int v188; // [esp+4Ch] [ebp+46h]
  int v189; // [esp+50h] [ebp+4Ah]
  int v190; // [esp+54h] [ebp+4Eh]
  bool v191; // [esp+58h] [ebp+52h]
  int v192; // [esp+5Ch] [ebp+56h]
  int v193; // [esp+60h] [ebp+5Ah]
  int v194; // [esp+64h] [ebp+5Eh]
  int v195; // [esp+68h] [ebp+62h]
  int v196; // [esp+6Ch] [ebp+66h]
  int v197; // [esp+70h] [ebp+6Ah]
  int v198; // [esp+74h] [ebp+6Eh]
  int v199; // [esp+78h] [ebp+72h]
  int v200; // [esp+7Ch] [ebp+76h]
  int v201; // [esp+80h] [ebp+7Ah]
  int v202; // [esp+84h] [ebp+7Eh]

  v4 = 7;
  fade_palette(0, 0, 7, a4);
  v193 = 0;
  v192 = 7;
  v191 = 0;
  v184 = 0;
  front_fade = 0;
  v189 = 0;
  while (2) {
    if (switch_types) {
      game_type = switch_types - 1;
      if (switch_types == 1 && competitors == 1)
        competitors = 16;
      switch_types = 0;
      if (game_type == 1)
        Race = ((_BYTE)TrackLoad - 1) & 7;
      else
        network_champ_on = 0;
    }
    display_picture(scrbuf, front_vga[0], v4);
    display_block(head_y, 0);
    display_block(2, 0);
    display_block(247, 0);
    display_block(247, 0);
    display_block(257, -1);
    if (v192 >= 7) {
      display_block(336, -1);
    } else {
      display_block(336, -1);
      front_text(sel_posns[2 * v192], sel_posns_variable_1[2 * v192], 143, 0);
    }
    front_text(sel_posns[0] + 132, sel_posns_variable_1[0] + 7, 143, 2);
    front_text(sel_posns_variable_2 + 132, sel_posns_variable_3 + 7, 143, 2);
    front_text(sel_posns_variable_4 + 132, sel_posns_variable_5 + 7, 143, 2);
    front_text(sel_posns_variable_6 + 132, sel_posns_variable_7 + 7, 143, 2);
    front_text(sel_posns_variable_8 + 132, sel_posns_variable_9 + 7, 143, 2);
    v4 = (int)&font2_ascii;
    i = (int)&font2_offsets;
    v6 = front_text(sel_posns_variable_10 + 132, sel_posns_variable_11 + 7, 143, 2);
    if (network_on) {
      v4 = (int)&font2_ascii;
      i = (int)&font2_offsets;
      v6 = front_text(sel_posns_variable_12 + 132, sel_posns_variable_13 + 7, 143, 2);
    }
    LODWORD(v6) = v192;
    switch (v192) {
      case 0:
        if (v191) {
          v201 = 171;
          v200 = 165;
        } else {
          v201 = 165;
          v200 = 171;
        }
        if (v189 != 1) {
          v201 = 143;
          v200 = 143;
        }
        if (v191) {
          v181 = 0;
          v7 = v179;
          while (*v7) {
            v8 = (unsigned __int8)font1_ascii[(unsigned __int8)*v7++];
            if (v8 == 255)
              v181 += 8;
            else
              v181 += *(_DWORD *)(front_vga_variable_10 + 12 * v8) + 1;
          }
          v181 += 430;
          v180 = 374 - 18 * v188;
        }
        v202 = 0;
        v195 = v201 - 2;
        v194 = 15;
        v9 = 18;
        v196 = v200 - 4;
        v10 = aReiseWagon2;
        v199 = 50;
        do {
          if ((v202 & 1) >= allocated_cars[v194 / 2]) {
            if (v9 == v188 && v191) {
              front_text(425, v199, v200, 2);
              if (v9 == v188)
                v12 = v201;
              else
                v12 = 143;
            } else {
              if (v9 == v188)
                v13 = v200;
              else
                v13 = 143;
              front_text(425, v199, v13, 2);
              if (v9 == v188)
                v12 = v201;
              else
                v12 = 143;
            }
          } else {
            if (v9 == v188)
              v11 = v196;
            else
              v11 = 139;
            front_text(425, v199, v11, 2);
            if (v9 == v188)
              v12 = v195;
            else
              v12 = 127;
          }
          front_text(430, v199, v12, 0);
          --v9;
          v10 += 15;
          --v194;
          v199 += 18;
          ++v202;
        } while (v202 < 16);
        if (player_type == 2) {
          if (v188 == 2 && v191) {
            if (v188 == player_type)
              v14 = v200;
            else
              v14 = 143;
            front_text(425, 338, v14, player_type);
            if (v188 == 2)
              v15 = v201;
            else
              v15 = 143;
          } else {
            if (v188 == 2)
              v16 = v200;
            else
              v16 = 143;
            v17 = v188;
            front_text(425, 338, v16, 2);
            if (v17 == 2)
              v15 = v201;
            else
              v15 = 143;
          }
          front_text(430, 338, v15, 0);
        }
        if (v188 == 1 && v191) {
          front_text(425, 356, v200, 2);
          if (v188 == 1)
            v18 = v201;
          else
            v18 = 143;
        } else {
          if (v188 == 1)
            v19 = v200;
          else
            v19 = 143;
          v20 = v188;
          front_text(425, 356, v19, 2);
          if (v20 == 1)
            v18 = v201;
          else
            v18 = 143;
        }
        front_text(430, 356, v18, 0);
        if (v188)
          v21 = 143;
        else
          v21 = v200;
        v4 = (int)font1_ascii;
        i = (int)&font1_offsets;
        v6 = front_text(420, 374, v21, 2);
        if (v191) {
          if ((frames & 0xFu) < 8) {
            v4 = (int)font1_ascii;
            i = (int)&font1_offsets;
            v6 = front_text(v181, v180, 171, 0);
          }
          LODWORD(v6) = v190;
          BYTE1(v4) = 0;
          v179[v190] = 0;
        }
        goto LABEL_623;
      case 1:
        if (v189 != 2)
          v187 = -1;
        if (v187 == 1)
          v22 = 171;
        else
          v22 = 143;
        scale_text(425, 80, v22, 2, 200, 640);
        if (v187 == 2)
          v23 = 171;
        else
          v23 = 143;
        scale_text(425, 104, v23, 2, 200, 640);
        if (v187 == 3)
          v24 = 171;
        else
          v24 = 143;
        scale_text(425, 128, v24, 2, 200, 640);
        if (v187 == 4)
          v25 = 171;
        else
          v25 = 143;
        scale_text(425, 152, v25, 2, 200, 640);
        if (v187 == 5)
          v26 = 171;
        else
          v26 = 143;
        scale_text(425, 176, v26, 2, 200, 640);
        if (allengines) {
          if (v187 == 5)
            v27 = 171;
          else
            v27 = 143;
        } else if (v187 == 5) {
          v27 = 171;
        } else {
          v27 = 143;
        }
        scale_text(430, 176, v27, 0, 200, 640);
        if (v187 == 6)
          v28 = 171;
        else
          v28 = 143;
        scale_text(425, 200, v28, 2, 200, 640);
        if (soundon) {
          v170 = 0;
          if (v187 == 6)
            v29 = 171;
          else
            v29 = 143;
        LABEL_112:
          scale_text(430, 200, v29, v170, 200, 640);
          goto LABEL_121;
        }
        if (!SoundCard) {
          v170 = soundon;
          if (v187 == 6)
            v29 = 171;
          else
            v29 = 143;
          goto LABEL_112;
        }
        if (v187 == 6)
          v30 = 171;
        else
          v30 = 143;
        scale_text(430, 200, v30, soundon, 200, 640);
      LABEL_121:
        if (v187 == 7)
          v31 = 171;
        else
          v31 = 143;
        scale_text(425, 224, v31, 2, 200, 640);
        if (musicon) {
          v171 = 0;
          if (v187 == 7)
            v32 = 171;
          else
            v32 = 143;
        LABEL_128:
          scale_text(430, 224, v32, v171, 200, 640);
          goto LABEL_138;
        }
        if (!MusicCard && !MusicCD) {
          v171 = musicon;
          if (v187 == 7)
            v32 = 171;
          else
            v32 = 143;
          goto LABEL_128;
        }
        if (v187 == 7)
          v33 = 171;
        else
          v33 = 143;
        scale_text(430, 224, v33, 0, 200, 640);
      LABEL_138:
        if (v187)
          v34 = 143;
        else
          v34 = 171;
        scale_text(420, 248, v34, 2, 200, 640);
        if (v187 == 1)
          v35 = 171;
        else
          v35 = 165;
        front_volumebar(80, EngineVolume, v35, &font1_offsets);
        if (v187 == 2)
          v36 = 171;
        else
          v36 = 165;
        front_volumebar(104, SFXVolume, v36, &font1_offsets);
        if (v187 == 3)
          v37 = 171;
        else
          v37 = 165;
        i = v187;
        front_volumebar(128, SpeechVolume, v37, v187);
        if (i == 4)
          v4 = 171;
        else
          v4 = 165;
        HIDWORD(v6) = MusicVolume;
        LODWORD(v6) = front_volumebar(152, MusicVolume, v4, i);
      LABEL_623:
        show_received_mesage(v6, HIDWORD(v6), v4, i);
        v125 = (int)screen;
        copypic((char *)scrbuf, (int)screen);
        if (switch_same > 0) {
          v127 = 0;
          if (players > 0) {
            v125 = 0;
            do {
              v125 += 4;
              i = switch_same - 666;
              ++v127;
              *(int *)((char *)infinite_laps + v125) = switch_same - 666;
            } while (v127 < players);
          }
          v128 = cheat_mode;
          BYTE1(v128) = BYTE1(cheat_mode) | 0x40;
          cheat_mode = v128;
        } else if (switch_same < 0) {
          i = 0;
          switch_same = 0;
          v126 = 0;
          if (players > 0) {
            v4 = -1;
            v125 = 0;
            do {
              v125 += 4;
              ++v126;
              *(int *)((char *)infinite_laps + v125) = -1;
            } while (v126 < players);
          }
          cheat_mode &= ~0x4000u;
        }
        if (!front_fade) {
          front_fade = -1;
          fade_palette(32, v125, v4, i);
          frames = 0;
        }
        if (!v184) {
          while (fatkbhit()) {
            i = v189;
            switch (v189) {
              case 0:
                v129 = fatgetch();
                i = v129;
                if (v129 < 0xD) {
                  if (!v129) {
                    v130 = fatgetch();
                    i = v130;
                    if (v130 >= 0x48) {
                      if (v130 <= 0x48) {
                        v132 = --v192;
                        if (!network_on && v132 == 6)
                          v192 = 5;
                        if (v192 < 0)
                          v192 = 0;
                      } else if (v130 == 80) {
                        v131 = ++v192;
                        if (!network_on && v131 == 6)
                          v192 = 7;
                        if (v192 > 7)
                          v192 = 7;
                      }
                    }
                  }
                } else if (v129 <= 0xD) {
                  v4 = v192;
                  switch (v192) {
                    case 0:
                      i = 1;
                      v189 = 1;
                      v188 = 0;
                      break;
                    case 1:
                      v125 = 2;
                      v4 = 0;
                      v189 = 2;
                      v187 = 0;
                      break;
                    case 2:
                      v189 = 3;
                      check_joystickpresence();
                      break;
                    case 3:
                      v125 = 0;
                      v189 = 4;
                      v185 = 0;
                      v184 = 0;
                      Joy1used = 0;
                      Joy2used = 0;
                      controlrelease = -1;
                      control_edit = -1;
                      break;
                    case 4:
                      i = 5;
                      v189 = 5;
                      v186 = 0;
                      break;
                    case 5:
                      v125 = 6;
                      v4 = 0;
                      v189 = 6;
                      v182 = 0;
                      break;
                    case 6:
                      v189 = 7;
                      v183 = 0;
                      v191 = 0;
                      break;
                    case 7:
                      v125 = 0x8000;
                      i = -1;
                      sfxsample(v172);
                      v193 = -1;
                      break;
                    default:
                      continue;
                  }
                } else if (v129 == 27) {
                  v193 = -1;
                  v125 = 0x8000;
                  sfxsample(v172);
                }
                continue;
              case 1:
                v133 = fatgetch();
                i = v133;
                if ((unsigned int)v133 < 8) {
                  if (v133)
                    goto LABEL_754;
                  v134 = fatgetch();
                  i = v134;
                  if (!v191 && v134 >= 0x48) {
                    if (v134 <= 0x48) {
                      v125 = v188 + 1;
                      v4 = player_type;
                      ++v188;
                      if (player_type != 2 && v125 == 2)
                        v188 = 3;
                      if (v188 > 18)
                        v188 = 18;
                    } else if (v134 == 80) {
                      v125 = v188 - 1;
                      v4 = player_type;
                      --v188;
                      if (player_type != 2 && v125 == 2)
                        v188 = 1;
                      if (v188 < 0)
                        v188 = 0;
                    }
                  }
                } else if ((unsigned int)v133 <= 8) {
                  if (v191) {
                    v135 = v190;
                    BYTE1(i) = 0;
                    v179[v190] = 0;
                    if (v135 > 0) {
                      v125 = v135 - 1;
                      v190 = v125;
                      v179[v125] = 0;
                    }
                  }
                } else if ((unsigned int)v133 < 0xD) {
                LABEL_754:
                  if (v191) {
                    if (v133 >= 97 && v133 <= 122)
                      i = v133 - 32;
                    if ((i == 32 || i >= 65 && i <= 90 || i >= 48 && i <= 57) && v190 < 8) {
                      v144 = v190 + 1;
                      BYTE1(v125) = 0;
                      v179[v190] = i;
                      v190 = v144;
                      v179[v144] = 0;
                    }
                  }
                } else if ((unsigned int)v133 <= 0xD) {
                  v136 = v191;
                  if (v191) {
                    v125 = 0;
                    v4 = v188;
                    v191 = 0;
                    if (v188) {
                      if ((unsigned int)v188 <= 1) {
                        for (i = 0; i < 9; cheat_names_variable_1[i + v137] = v125) {
                          ++i;
                          v137 = 9 * (__int16)player1_car;
                          LOBYTE(v125) = v179[i - 1];
                        }
                        broadcast_mode = -669;
                        while (broadcast_mode)
                          ;
                        if (!network_on) {
                          v125 = (__int16)player1_car;
                          v137 = CheckNames(&player_names[9 * (__int16)player1_car]);
                          waste = v137;
                        }
                        check_cars(v137);
                      } else {
                        if (v188 != 2)
                          goto LABEL_707;
                        v125 = player2_car;
                        for (i = 0; i < 9; cheat_names_variable_1[9 * v125 + i] = v4)
                          LOBYTE(v4) = v179[i++];
                        waste = CheckNames(&player_names[9 * v125]);
                        check_cars(waste);
                      }
                    } else {
                    LABEL_707:
                      v138 = v188 - 3;
                      LOBYTE(v138) = (v188 - 3) ^ 1;
                      i = 0;
                      v125 = 9 * v138;
                      do {
                        LOBYTE(v4) = v179[i++];
                        team_col_variable_1[i + v125] = v4;
                      } while (i < 9);
                      if (!default_names[v125]) {
                        sprintf(&buffer, "comp %i", v188 - 2);
                        v139 = &default_names[v125];
                        v125 = (int)&buffer;
                        name_copy((int)v139, &buffer);
                      }
                      broadcast_mode = -1;
                      while (broadcast_mode)
                        ;
                    }
                  } else {
                    if (!v188)
                      goto LABEL_715;
                    v191 = 1;
                    if (v188 >= 3) {
                      if ((((_BYTE)v188 - 3) & 1) != 0)
                        v191 = allocated_cars[(v188 - 3) / 2] <= 0;
                      else
                        v191 = allocated_cars[(v188 - 3) / 2] <= 1;
                    }
                    v125 = v191;
                    if (v191) {
                      v4 = 0;
                      v190 = 0;
                      if ((unsigned int)v188 <= 1) {
                        for (i = 0; i < 9; v179[i - 1] = cheat_names_variable_1[9 * (__int16)player1_car + i])
                          ++i;
                      } else if (v188 == 2) {
                        for (i = 0; i < 9; v179[i - 1] = cheat_names_variable_1[9 * player2_car + i])
                          ++i;
                      } else {
                        v140 = v188 - 3;
                        LOBYTE(v140) = (v188 - 3) ^ 1;
                        i = 0;
                        v141 = 9 * v140;
                        do {
                          ++i;
                          LOBYTE(v125) = default_names[v141++];
                          v179[i - 1] = v125;
                        } while (i < 9);
                      }
                      while (v179[v190])
                        ++v190;
                    }
                  }
                } else {
                  if (v133 != 27)
                    goto LABEL_754;
                  v136 = v191;
                  if (v191) {
                    v125 = 0;
                    v4 = v188;
                    v191 = 0;
                    if (v188) {
                      if ((unsigned int)v188 <= 1) {
                        for (i = 0; i < 9; cheat_names_variable_1[9 * (__int16)player1_car + i] = v125)
                          LOBYTE(v125) = v179[i++];
                        broadcast_mode = -669;
                        while (broadcast_mode)
                          ;
                        if (!network_on) {
                          v125 = (__int16)player1_car;
                          waste = CheckNames(&player_names[9 * (__int16)player1_car]);
                        }
                      } else {
                        if (v188 != 2)
                          goto LABEL_747;
                        v125 = player2_car;
                        for (i = 0; i < 9; cheat_names_variable_1[9 * v125 + i] = v4)
                          LOBYTE(v4) = v179[i++];
                        waste = CheckNames(&player_names[9 * v125]);
                      }
                    } else {
                    LABEL_747:
                      v142 = v188 - 3;
                      LOBYTE(v142) = (v188 - 3) ^ 1;
                      i = 0;
                      v125 = 9 * v142;
                      do {
                        LOBYTE(v4) = v179[i++];
                        team_col_variable_1[i + v125] = v4;
                      } while (i < 9);
                      if (!default_names[9 * v142]) {
                        sprintf(&buffer, "comp %i", v188 - 2);
                        v143 = &default_names[v125];
                        v125 = (int)&buffer;
                        name_copy((int)v143, &buffer);
                      }
                      broadcast_mode = -1;
                      while (broadcast_mode)
                        ;
                    }
                  } else {
                  LABEL_715:
                    v189 = v136;
                  }
                }
                continue;
              case 2:
                v145 = fatgetch();
                i = v145;
                if (v145 < 0xD) {
                  if (!v145) {
                    v146 = fatgetch();
                    i = v146 - 72;
                    switch (v146) {
                      case 'H':
                        v125 = v187;
                        if (v187) {
                          if (v187 > 1)
                            i = --v187;
                        } else {
                          v187 = 7;
                        }
                        break;
                      case 'K':
                        switch (v187) {
                          case 1:
                            EngineVolume -= 4;
                            if (EngineVolume < 0)
                              EngineVolume = 0;
                            break;
                          case 2:
                            v125 = SFXVolume - 4;
                            SFXVolume = v125;
                            if (v125 < 0) {
                              i = 0;
                              SFXVolume = 0;
                            }
                            break;
                          case 3:
                            SpeechVolume -= 4;
                            if (SpeechVolume < 0)
                              SpeechVolume = 0;
                            break;
                          case 4:
                            MusicVolume -= 4;
                            if (MusicVolume < 0) {
                              v125 = 0;
                              MusicVolume = 0;
                            }
                            if (MusicCard)
                              sosMIDISetMasterVolume((unsigned __int8)MusicVolume);
                            if (MusicCD)
                              goto LABEL_790;
                            break;
                          default:
                            continue;
                        }
                        break;
                      case 'M':
                        switch (v187) {
                          case 1:
                            v4 = EngineVolume + 4;
                            EngineVolume = v4;
                            if (v4 >= 128)
                              EngineVolume = 127;
                            break;
                          case 2:
                            SFXVolume += 4;
                            if (SFXVolume >= 128)
                              SFXVolume = 127;
                            break;
                          case 3:
                            v4 = SpeechVolume + 4;
                            SpeechVolume = v4;
                            if (v4 >= 128)
                              SpeechVolume = 127;
                            break;
                          case 4:
                            i = MusicVolume + 4;
                            MusicVolume = i;
                            if (i >= 128)
                              MusicVolume = 127;
                            if (MusicCard)
                              sosMIDISetMasterVolume((unsigned __int8)MusicVolume);
                            if (MusicCD)
                              LABEL_790:
                            SetAudioVolume(MusicVolume);
                            break;
                          default:
                            continue;
                        }
                        break;
                      case 'P':
                        v147 = v187;
                        if (v187 > 0) {
                          ++v187;
                          if (v147 + 1 > 7) {
                            v4 = 0;
                            v187 = 0;
                          }
                        }
                        break;
                      default:
                        continue;
                    }
                  }
                } else if (v145 <= 0xD) {
                  v125 = v187;
                  switch (v187) {
                    case 0:
                      goto LABEL_806;
                    case 5:
                      allengines = allengines == 0;
                      break;
                    case 6:
                      if (SoundCard) {
                        j = soundon != 0;
                        soundon = soundon == 0;
                        if (!j)
                          loadfatalsample();
                      } else {
                        soundon = 0;
                      }
                      break;
                    case 7:
                      v4 = MusicCard;
                      if (MusicCard || MusicCD) {
                        v148 = musicon == 0;
                        musicon = v148;
                        reinitmusic(v148, v187, MusicCard, i);
                      } else {
                        musicon = MusicCard;
                      }
                      break;
                    default:
                      continue;
                  }
                } else if (v145 == 27) {
                LABEL_804:
                  v189 = 0;
                }
                continue;
              case 3:
                v149 = fatgetch();
                i = v149;
                if (v149 < 0xD) {
                  if (!v149)
                    fatgetch();
                } else if (v149 <= 0xD || v149 == 27) {
                  remove_uncalibrated();
                  v189 = 0;
                }
                continue;
              case 4:
                v150 = fatgetch();
                i = v150;
                if (v150 < 0xD) {
                  if (!v150) {
                    v151 = fatgetch();
                    i = v151;
                    if (v151 >= 0x48) {
                      if (v151 <= 0x48) {
                        if (!v184) {
                          v152 = ++v185;
                          if (player_type == 2) {
                            if (v152 > 4)
                              v185 = 4;
                          } else if (v152 > 2) {
                            v185 = 2;
                          }
                        }
                      } else if (v151 == 80 && !v184) {
                        v125 = v185 - 1;
                        v185 = v125;
                        if (v125 < 0)
                          v185 = v184;
                      }
                    }
                  }
                } else if (v150 <= 0xD) {
                  v4 = v185;
                  switch (v185) {
                    case 0:
                      goto LABEL_841;
                    case 1:
                      v4 = 1;
                      control_edit = 0;
                      disable_keyboard();
                      qmemcpy(&oldkeys, userkey, 0xCu);
                      qmemcpy((char *)&oldkeys + 12, &userkey[12], 2u);
                      i = 0;
                      v184 = 1;
                      controlrelease = -1;
                      break;
                    case 2:
                      if (manual_control[(__int16)player1_car] == 2)
                        manual_control[(__int16)player1_car] = 1;
                      else
                        manual_control[(__int16)player1_car] = 2;
                      broadcast_mode = -1;
                      while (broadcast_mode)
                        ;
                      break;
                    case 3:
                      v125 = 6;
                      v4 = -1;
                      v184 = 2;
                      control_edit = 6;
                      disable_keyboard();
                      qmemcpy(&oldkeys, userkey, 0xCu);
                      qmemcpy((char *)&oldkeys + 12, &userkey[12], 2u);
                      i = 0;
                      controlrelease = -1;
                      break;
                    case 4:
                      if (manual_control[player2_car] == 2)
                        manual_control[player2_car] = 1;
                      else
                        manual_control[player2_car] = 2;
                      break;
                    default:
                      continue;
                  }
                } else if (v150 == 27) {
                  v125 = 0;
                  v189 = 0;
                }
                continue;
              case 5:
                v154 = fatgetch();
                i = v154;
                if (v154 < 0xD) {
                  if (!v154) {
                    v155 = fatgetch();
                    i = v155 - 72;
                    switch (v155) {
                      case 'H':
                        if (++v186 > 16)
                          v186 = 16;
                        break;
                      case 'K':
                        if (v186 == 2) {
                          if (game_svga) {
                            v125 = game_size - 16;
                            game_size = v125;
                            if (v125 < 64)
                              game_size = 64;
                          } else {
                            game_size -= 8;
                            if (game_size < 32)
                              game_size = 32;
                          }
                        }
                        break;
                      case 'M':
                        if (v186 == 2) {
                          if (game_svga) {
                            game_size += 16;
                            if (game_size > 128)
                              game_size = 128;
                          } else {
                            v4 = game_size + 8;
                            game_size = v4;
                            if (v4 > 64)
                              game_size = 64;
                          }
                        }
                        break;
                      case 'P':
                        i = v186 - 1;
                        v186 = i;
                        if (i < 0)
                          v186 = 0;
                        break;
                      default:
                        continue;
                    }
                  }
                } else if (v154 <= 0xD) {
                  switch (v186) {
                    case 0:
                      v4 = 0;
                      v189 = 0;
                      break;
                    case 1:
                      if (game_svga) {
                        game_svga = 0;
                        v125 = game_size >> 31;
                        game_size /= 2;
                      } else if (svga_possible && !no_mem) {
                        game_svga = -1;
                        game_size *= 2;
                      }
                      break;
                    case 2:
                      if (game_svga) {
                        game_size += 16;
                        if (game_size > 128)
                          game_size = 64;
                      } else {
                        v4 = game_size + 8;
                        game_size = v4;
                        if (v4 > 64)
                          game_size = 32;
                      }
                      break;
                    case 3:
                      if (view_limit) {
                        view_limit = 0;
                      } else if (machine_speed >= 2800) {
                        view_limit = 32;
                      } else {
                        view_limit = 24;
                      }
                      break;
                    case 4:
                      v4 = textures_off;
                      if ((textures_off & 0x20) != 0) {
                        v156 = textures_off;
                        LOBYTE(v156) = textures_off ^ 0x20;
                        textures_off = ((unsigned int)&loc_3FFFC + 4) | v156;
                      } else if ((((unsigned int)&loc_3FFFC + 4) & textures_off) != 0) {
                        textures_off ^= (unsigned int)&loc_3FFFC + 4;
                      } else {
                        textures_off |= 0x20u;
                      }
                      break;
                    case 5:
                      v125 = textures_off;
                      LOBYTE(v125) = textures_off ^ 8;
                      textures_off = v125;
                      break;
                    case 6:
                      v157 = textures_off;
                      BYTE1(v157) = BYTE1(textures_off) ^ 1;
                      textures_off = v157;
                      break;
                    case 7:
                      textures_off ^= 2u;
                      break;
                    case 8:
                      textures_off ^= 0x80u;
                      break;
                    case 9:
                      i = textures_off;
                      LOBYTE(i) = textures_off ^ 1;
                      textures_off = i;
                      break;
                    case 10:
                      v4 = textures_off;
                      LOBYTE(v4) = textures_off ^ 4;
                      textures_off = v4;
                      break;
                    case 11:
                      v125 = textures_off;
                      LOBYTE(v125) = textures_off ^ 0x40;
                      textures_off = v125;
                      break;
                    case 12:
                      v158 = textures_off;
                      LOBYTE(v158) = textures_off ^ 0x10;
                      textures_off = v158;
                      break;
                    case 13:
                      textures_off ^= 0x800u;
                      break;
                    case 14:
                      textures_off ^= 0x200u;
                      break;
                    case 15:
                      v125 = names_on + 1;
                      names_on = v125;
                      if (v125 > 2) {
                        i = 0;
                        names_on = 0;
                      }
                      break;
                    case 16:
                      textures_off ^= (unsigned int)&loc_7FFFE + 2;
                      break;
                    default:
                      continue;
                  }
                } else if (v154 == 27) {
                LABEL_806:
                  v189 = 0;
                }
                continue;
              case 6:
                v159 = fatgetch();
                i = v159;
                if (v159 < 0xD) {
                  if (!v159) {
                    v160 = fatgetch();
                    i = v160 - 72;
                    switch (v160) {
                      case 'H':
                        v161 = ++v182;
                        if (player_type == 2) {
                          if (v161 > 6)
                            v182 = 6;
                        } else if (v161 > 5) {
                          v182 = 5;
                        }
                        break;
                      case 'P':
                        v125 = v182 - 1;
                        v182 = v125;
                        if (v125 < 0) {
                          i = 0;
                          v182 = 0;
                        }
                        break;
                      default:
                        continue;
                    }
                  }
                } else if (v159 <= 0xD) {
                  switch (v182) {
                    case 0:
                      goto LABEL_804;
                    case 1:
                      false_starts = false_starts == 0;
                      broadcast_mode = -1;
                      while (broadcast_mode)
                        ;
                      break;
                    case 2:
                      if (lots_of_mem) {
                        if (p_tex_size == 1) {
                          v4 = 0;
                          p_tex_size = 0;
                        } else {
                          p_tex_size = 1;
                        }
                      }
                      break;
                    case 3:
                      if (replay_record) {
                        i = 0;
                        replay_record = 0;
                      } else {
                        replay_record = 1;
                      }
                      break;
                    case 4:
                      v125 = textures_off;
                      BYTE1(v125) = BYTE1(textures_off) ^ 4;
                      textures_off = v125;
                      break;
                    case 5:
                      do {
                        if (++game_view == 9)
                          game_view = 0;
                      } while (!AllowedViews[game_view]);
                      break;
                    case 6:
                      do {
                        if (++game_view_variable_1 == 9) {
                          v4 = 0;
                          game_view_variable_1 = 0;
                        }
                      } while (!AllowedViews[game_view_variable_1]);
                      break;
                    default:
                      continue;
                  }
                } else if (v159 == 27) {
                LABEL_841:
                  v153 = 0;
                  goto LABEL_842;
                }
                continue;
              case 7:
                v162 = fatgetch();
                v125 = v162;
                i = v162;
                if (v162 < 8) {
                  if (v162)
                    goto LABEL_974;
                  v164 = v191;
                  v165 = fatgetch();
                  if (!v164 && v165 >= 0x48) {
                    if (v165 <= 0x48) {
                      v4 = v183 + 1;
                      v183 = v4;
                      if (v4 > 5)
                        v183 = 5;
                    } else if (v165 == 80 && --v183 < 0) {
                      v183 = v125;
                    }
                  }
                } else {
                  v163 = 14 * (4 - v183);
                  if ((unsigned int)v125 <= 8) {
                    if (v191) {
                      v125 = v190;
                      LOBYTE(v4) = 0;
                      aSlowcoach[v190 + v163] = 0;
                      if (v125 > 0) {
                        v4 = --v125;
                        BYTE1(v4) = 0;
                        v190 = v125;
                        aSlowcoach[v125 + v163] = 0;
                      }
                    }
                  } else {
                    if ((unsigned int)v125 < 0xD)
                      goto LABEL_974;
                    if ((unsigned int)v125 <= 0xD) {
                      v4 = v191;
                      if (v191) {
                        i ^= v125;
                        v191 = i;
                      } else if (v183) {
                        if (v183 == 5) {
                          select_messages(v163);
                        } else {
                          v190 = v191;
                          i = 14 * (4 - v183);
                          LOBYTE(v125) = aSlowcoach[v163];
                          v191 = 1;
                          for (j = (_BYTE)v125 == 0; !j; j = (_BYTE)v4 == 0) {
                            LOBYTE(v4) = aSlowcoach[++i];
                            ++v190;
                          }
                        }
                      } else {
                        v189 = v191;
                      }
                    } else if (v125 == 27) {
                      v153 = v191;
                      if (v191) {
                        v125 = 0;
                        v191 = 0;
                      } else {
                      LABEL_842:
                        v189 = v153;
                      }
                    } else {
                    LABEL_974:
                      if (v191 && v190 < 13) {
                        if (i >= 97 && i <= 122)
                          i -= 32;
                        if (i >= 65 && i <= 90 || i >= 48 && i <= 57 || i == 32 || i == 46 || i == 39) {
                          v167 = 14 * (4 - v183);
                          v125 = v190;
                          v4 = v190 + 1;
                          aSlowcoach[v190 + v167] = i;
                          i = v4;
                          LOBYTE(i) = 0;
                          v190 = v4;
                          aSlowcoach[v4 + v167] = 0;
                        }
                      }
                    }
                  }
                }
                break;
              default:
                continue;
            }
          }
        }
        if (!v193)
          continue;
        fade_palette(0, v125, 0, i);
        front_fade = 0;
        return;
      case 2:
        if (v189 == 3) {
          ReadJoys((int *)&v172);
          _disable();
          if (v173 < JAXmin)
            JAXmin = v173;
          if (v173 > JAXmax)
            JAXmax = v173;
          if (v174 < JAYmin)
            JAYmin = v174;
          if (v174 > JAYmax)
            JAYmax = v174;
          if (v177 < JBXmin)
            JBXmin = v177;
          if (v177 > JBXmax)
            JBXmax = v177;
          if (v178 < JBYmin)
            JBYmin = v178;
          if (v178 > JBYmax)
            JBYmax = v178;
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
        if (v189 == 3) {
          scale_text(400, 60, 143, 1, 200, 640);
          scale_text(400, 78, 143, 1, 200, 640);
        }
        v38 = v189;
        scale_text(400, 110, 143, 1, 200, 640);
        if (v38 == 3) {
          if (x1ok && JAXmax - JAXmin >= 100)
            v39 = 140 * (2 * v173 - JAXmax - JAXmin) / (JAXmax - JAXmin);
          else
            v39 = 0;
          front_displaycalibrationbar(300, 128, v39, &font1_offsets);
        } else {
          scale_text(400, 128, 143, 1, 200, 640);
        }
        scale_text(400, 160, 143, 1, 200, 640);
        if (v189 == 3) {
          if (y1ok && JAYmax - JAYmin >= 100)
            v40 = 140 * (2 * v174 - JAYmax - JAYmin) / (JAYmax - JAYmin);
          else
            v40 = 0;
          front_displaycalibrationbar(300, 178, v40, &font1_offsets);
        } else {
          scale_text(400, 178, 143, 1, 200, 640);
        }
        scale_text(400, 210, 143, 1, 200, 640);
        if (v189 == 3) {
          if (x2ok && JBXmax - JBXmin >= 100)
            v41 = 140 * (2 * v177 - JBXmax - JBXmin) / (JBXmax - JBXmin);
          else
            v41 = 0;
          front_displaycalibrationbar(300, 228, v41, &font1_offsets);
        } else {
          scale_text(400, 228, 143, 1, 200, 640);
        }
        i = (int)&font1_offsets;
        v42 = v189;
        scale_text(400, 260, 143, 1, 200, 640);
        if (v42 == 3) {
          if (y2ok && JBYmax - JBYmin >= 100)
            v4 = 140 * (2 * v178 - JBYmax - JBYmin) / (JBYmax - JBYmin);
          else
            v4 = 0;
          v6 = (unsigned int)front_displaycalibrationbar(300, 278, v4, &font1_offsets) | 0x11600000000LL;
        } else {
          i = (int)&font1_offsets;
          v4 = (int)font1_ascii;
          v6 = scale_text(400, 278, 143, 1, 200, 640);
        }
        goto LABEL_623;
      case 3:
        if (v189 == 4) {
          if (controlrelease) {
            v43 = -1;
            v44 = 0;
            v45 = 0;
            do {
              if (keyname[v45] && keys[v44])
                v43 = 0;
              ++v44;
              ++v45;
            } while (v44 < 128);
            if (v43)
              controlrelease = 0;
          }
        } else {
          v185 = -1;
        }
        if (player_type == 2) {
          if (manual_control[player2_car] == 2)
            sprintf(&buffer, "%s %s", config_buffer_variable_57, config_buffer_variable_58);
          else
            sprintf(&buffer, "%s %s", config_buffer_variable_57, config_buffer_variable_59);
          if (v185 == 4)
            v46 = 171;
          else
            v46 = 143;
          scale_text(420, 60, v46, 1, 200, 640);
          if (v185 == 3)
            v47 = 171;
          else
            v47 = 143;
          scale_text(420, 78, v47, 1, 200, 640);
        }
        if (manual_control[(__int16)player1_car] == 2)
          sprintf(&buffer, "%s %s", config_buffer_variable_56, config_buffer_variable_58);
        else
          sprintf(&buffer, "%s %s", config_buffer_variable_56, config_buffer_variable_59);
        if (v185 == 2)
          v48 = 171;
        else
          v48 = 143;
        scale_text(420, 96, v48, 1, 200, 640);
        if (v185 == 1)
          v49 = 171;
        else
          v49 = 143;
        scale_text(420, 114, v49, 1, 200, 640);
        if (v185)
          v50 = 143;
        else
          v50 = 171;
        i = (int)&font1_offsets;
        v6 = scale_text(420, 132, v50, 1, 200, 640);
        v4 = v185;
        if (v185 == 1 || v185 == 2) {
          v51 = 0;
          v52 = &config_buffer[896];
          v198 = 200;
          do {
            if (v51 == control_edit)
              v53 = 171;
            else
              v53 = 143;
            front_text(475, v198, v53, 2);
            if (v51 == control_edit)
              v54 = 171;
            else
              v54 = 143;
            v4 = (int)font1_ascii;
            i = (int)&font1_offsets;
            v6 = scale_text(480, v198, v54, 0, 200, 640);
            v52 += 64;
            ++v51;
            v198 += 18;
          } while (v51 < 6);
          LODWORD(v6) = (__int16)player1_car;
          if (Players_Cars[(__int16)player1_car] >= 8) {
            if (control_edit == 12)
              v55 = 171;
            else
              v55 = 143;
            front_text(475, 308, v55, 2);
            if (control_edit == 12)
              v56 = 171;
            else
              v56 = 143;
            v4 = (int)font1_ascii;
            i = (int)&font1_offsets;
            v6 = scale_text(480, 308, v56, 0, 200, 640);
          }
        } else if (v185 == 3 || v185 == 4) {
          v57 = 6;
          v58 = &config_buffer[1280];
          v197 = 200;
          do {
            if (v57 == control_edit)
              v59 = 171;
            else
              v59 = 143;
            front_text(475, v197, v59, 2);
            if (v57 == control_edit)
              v60 = 171;
            else
              v60 = 143;
            i = (int)&font1_offsets;
            v6 = front_text(480, v197, v60, 0);
            v58 += 64;
            v4 = v197 + 18;
            ++v57;
            v197 += 18;
          } while (v57 < 12);
          LODWORD(v6) = player2_car;
          if (Players_Cars[player2_car] >= 8) {
            if (control_edit == 13)
              v61 = 171;
            else
              v61 = 143;
            front_text(475, 308, v61, 2);
            if (control_edit == 13)
              v62 = 171;
            else
              v62 = 143;
            v4 = (int)font1_ascii;
            i = (int)&font1_offsets;
            v6 = front_text(480, 308, v62, 0);
          }
        }
        if (!v184 || v189 != 4)
          goto LABEL_623;
        LODWORD(v6) = controlrelease;
        if (controlrelease)
          goto LABEL_341;
        v6 = 0LL;
        i = -1;
        do {
          if (*(int *)((char *)keyname + HIDWORD(v6)) && keys[v6])
            i = v6;
          LODWORD(v6) = v6 + 1;
          HIDWORD(v6) += 4;
        } while ((int)v6 < 128);
        if (i == -1) {
          LODWORD(v6) = ReadJoys((int *)&v172);
          if ((_DWORD)v172)
            i = 128;
          if (HIDWORD(v172))
            i = 129;
          if (v175)
            i = 130;
          if (v176)
            i = 131;
        }
        if (i == -1) {
          if (y2ok) {
            v4 = JBYmax - JBYmin;
            LODWORD(v6) = 100 * (2 * v178 - JBYmax - JBYmin) / (JBYmax - JBYmin);
            HIDWORD(v6) = 100 * (2 * v178 - JBYmax - JBYmin) % (JBYmax - JBYmin);
            if ((int)v6 < -50)
              i = 138;
            if ((int)v6 > 50)
              i = 139;
          }
          if (x2ok) {
            v4 = JBXmax - JBXmin;
            LODWORD(v6) = 100 * (2 * v177 - JBXmax - JBXmin) / (JBXmax - JBXmin);
            HIDWORD(v6) = 100 * (2 * v177 - JBXmax - JBXmin) % (JBXmax - JBXmin);
            if ((int)v6 < -50)
              i = 136;
            if ((int)v6 > 50)
              i = 137;
          }
          if (y1ok) {
            v4 = JAYmax - JAYmin;
            LODWORD(v6) = 100 * (2 * v174 - JAYmax - JAYmin) / (JAYmax - JAYmin);
            HIDWORD(v6) = 100 * (2 * v174 - JAYmax - JAYmin) % (JAYmax - JAYmin);
            if ((int)v6 < -50)
              i = 134;
            if ((int)v6 > 50)
              i = 135;
          }
          if (x1ok) {
            v4 = JAXmax - JAXmin;
            LODWORD(v6) = 100 * (2 * v173 - JAXmax - JAXmin) / (JAXmax - JAXmin);
            HIDWORD(v6) = 100 * (2 * v173 - JAXmax - JAXmin) % (JAXmax - JAXmin);
            if ((int)v6 < -50)
              i = 132;
            if ((int)v6 > 50)
              i = 133;
          }
        }
        if (i != -1 && (control_edit == 1 || control_edit == 7)) {
          if ((LODWORD(v6) = control_edit, *((_BYTE *)&off_A4108 + control_edit + 3) <= 0x83u) && i > 131
            || (LODWORD(v6) = control_edit, *((_BYTE *)&off_A4108 + control_edit + 3) > 0x83u) && i <= 131) {
            i = -1;
          }
        }
        if (i == -1)
          goto LABEL_341;
        HIDWORD(v6) = control_edit;
        v4 = 0;
        LODWORD(v6) = 0;
        if (control_edit > 0) {
          do {
            HIDWORD(v6) = (unsigned __int8)userkey[v6];
            if (HIDWORD(v6) == i)
              v4 = -1;
            LODWORD(v6) = v6 + 1;
          } while ((int)v6 < control_edit);
        }
        if (v4)
          goto LABEL_341;
        HIDWORD(v6) = -1;
        LODWORD(v6) = control_edit + 1;
        v4 = v184;
        controlrelease = -1;
        *((_BYTE *)&off_A4108 + v6 + 3) = i;
        control_edit = v6;
        if (v4 == 1) {
          if ((int)v6 < 6)
            goto LABEL_341;
          LODWORD(v6) = (__int16)player1_car;
          if (Players_Cars[(__int16)player1_car] >= 8 && control_edit < 12) {
            control_edit = 12;
            goto LABEL_341;
          }
        } else {
          if ((int)v6 < 12)
            goto LABEL_341;
          LODWORD(v6) = player2_car;
          if (Players_Cars[player2_car] >= 8 && control_edit < 13) {
            control_edit = 13;
            goto LABEL_341;
          }
        }
        HIDWORD(v6) = -1;
        v184 = 0;
        control_edit = -1;
        enable_keyboard();
      LABEL_341:
        if (keys_variable_1) {
          qmemcpy(userkey, &oldkeys, 0xCu);
          qmemcpy(&userkey[12], (char *)&oldkeys + 12, 2u);
          enable_keyboard();
          i = 0;
          v184 = 0;
          control_edit = -1;
          LODWORD(v6) = check_joystick_usage();
        }
        goto LABEL_623;
      case 4:
        if (v189 != 5)
          v186 = -1;
        if (v186 == 16)
          v63 = 171;
        else
          v63 = 143;
        scale_text(435, 60, v63, 2, 200, 640);
        if ((((unsigned int)&loc_7FFFE + 2) & textures_off) != 0) {
          if (v186 == 16)
            v64 = 171;
          else
            v64 = 143;
          v168 = v64;
        } else {
          if (v186 == 16)
            v65 = 171;
          else
            v65 = 143;
          v168 = v65;
        }
        scale_text(440, 60, v168, 0, 200, 640);
        sprintf(&buffer, "%s:", config_buffer_variable_50);
        if (v186 == 15)
          v66 = 171;
        else
          v66 = 143;
        scale_text(435, 80, v66, 2, 200, 640);
        if (names_on) {
          if (names_on == 2) {
            if (v186 == 15)
              v67 = 171;
            else
              v67 = 143;
          } else if (v186 == 15) {
            v67 = 171;
          } else {
            v67 = 143;
          }
        } else if (v186 == 15) {
          v67 = 171;
        } else {
          v67 = 143;
        }
        scale_text(440, 80, v67, 0, 200, 640);
        if (v186 == 14)
          v68 = 171;
        else
          v68 = 143;
        scale_text(435, 100, v68, 2, 200, 640);
        if ((textures_off & 0x200) != 0) {
          if (v186 == 14)
            v69 = 171;
          else
            v69 = 143;
        } else if (v186 == 14) {
          v69 = 171;
        } else {
          v69 = 143;
        }
        scale_text(440, 100, v69, 0, 200, 640);
        if (v186 == 13)
          v70 = 171;
        else
          v70 = 143;
        scale_text(435, 120, v70, 2, 200, 640);
        if ((textures_off & 0x800) != 0) {
          if (v186 == 13)
            v71 = 171;
          else
            v71 = 143;
        } else if (v186 == 13) {
          v71 = 171;
        } else {
          v71 = 143;
        }
        scale_text(440, 120, v71, 0, 200, 640);
        if (v186 == 12)
          v72 = 171;
        else
          v72 = 143;
        scale_text(435, 140, v72, 2, 200, 640);
        if ((textures_off & 0x10) != 0) {
          if (v186 == 12)
            v73 = 171;
          else
            v73 = 143;
        } else if (v186 == 12) {
          v73 = 171;
        } else {
          v73 = 143;
        }
        scale_text(440, 140, v73, 0, 200, 640);
        if (v186 == 11)
          v74 = 171;
        else
          v74 = 143;
        scale_text(435, 160, v74, 2, 200, 640);
        if ((textures_off & 0x40) != 0) {
          if (v186 == 11)
            v75 = 171;
          else
            v75 = 143;
        } else if (v186 == 11) {
          v75 = 171;
        } else {
          v75 = 143;
        }
        scale_text(440, 160, v75, 0, 200, 640);
        if (v186 == 10)
          v76 = 171;
        else
          v76 = 143;
        scale_text(435, 180, v76, 2, 200, 640);
        if ((textures_off & 4) != 0) {
          if (v186 == 10)
            v77 = 171;
          else
            v77 = 143;
        } else if (v186 == 10) {
          v77 = 171;
        } else {
          v77 = 143;
        }
        scale_text(440, 180, v77, 0, 200, 640);
        if (v186 == 9)
          v78 = 171;
        else
          v78 = 143;
        scale_text(435, 200, v78, 2, 200, 640);
        if ((textures_off & 1) != 0) {
          if (v186 == 9)
            v79 = 171;
          else
            v79 = 143;
        } else if (v186 == 9) {
          v79 = 171;
        } else {
          v79 = 143;
        }
        scale_text(440, 200, v79, 0, 200, 640);
        if (v186 == 8)
          v80 = 171;
        else
          v80 = 143;
        scale_text(435, 220, v80, 2, 200, 640);
        if ((textures_off & 0x80u) == 0) {
          if (v186 == 8)
            v81 = 171;
          else
            v81 = 143;
        } else if (v186 == 8) {
          v81 = 171;
        } else {
          v81 = 143;
        }
        scale_text(440, 220, v81, 0, 200, 640);
        if (v186 == 7)
          v82 = 171;
        else
          v82 = 143;
        scale_text(435, 240, v82, 2, 200, 640);
        if ((textures_off & 2) != 0) {
          if (v186 == 7)
            v83 = 171;
          else
            v83 = 143;
        } else if (v186 == 7) {
          v83 = 171;
        } else {
          v83 = 143;
        }
        scale_text(440, 240, v83, 0, 200, 640);
        if (v186 == 6)
          v84 = 171;
        else
          v84 = 143;
        scale_text(435, 260, v84, 2, 200, 640);
        if ((textures_off & 0x100) != 0) {
          if (v186 == 6)
            v85 = 171;
          else
            v85 = 143;
        } else if (v186 == 6) {
          v85 = 171;
        } else {
          v85 = 143;
        }
        scale_text(440, 260, v85, 0, 200, 640);
        if (v186 == 5)
          v86 = 171;
        else
          v86 = 143;
        scale_text(435, 280, v86, 2, 200, 640);
        if ((textures_off & 8) != 0) {
          if (v186 == 5)
            v87 = 171;
          else
            v87 = 143;
        } else if (v186 == 5) {
          v87 = 171;
        } else {
          v87 = 143;
        }
        scale_text(440, 280, v87, 0, 200, 640);
        if (v186 == 4)
          v88 = 171;
        else
          v88 = 143;
        scale_text(435, 300, v88, 2, 200, 640);
        if ((textures_off & 0x20) != 0) {
          if (v186 == 4)
            v89 = 171;
          else
            v89 = 143;
        } else if ((((unsigned int)&loc_3FFFC + 4) & textures_off) != 0) {
          if (v186 == 4)
            v89 = 171;
          else
            v89 = 143;
        } else if (v186 == 4) {
          v89 = 171;
        } else {
          v89 = 143;
        }
        scale_text(440, 300, v89, 0, 200, 640);
        if (v186 == 3)
          v90 = 171;
        else
          v90 = 143;
        scale_text(435, 320, v90, 2, 200, 640);
        if (view_limit) {
          if (v186 == 3)
            v91 = 171;
          else
            v91 = 143;
        } else if (v186 == 3) {
          v91 = 171;
        } else {
          v91 = 143;
        }
        scale_text(440, 320, v91, 0, 200, 640);
        if (v186 == 2)
          v92 = 171;
        else
          v92 = 143;
        scale_text(435, 340, v92, 2, 200, 640);
        if (game_svga)
          v93 = (100 * game_size - (__CFSHL__((100 * game_size) >> 31, 7) + ((100 * game_size) >> 31 << 7))) >> 7;
        else
          v93 = (100 * game_size - (__CFSHL__((100 * game_size) >> 31, 6) + ((100 * game_size) >> 31 << 6))) >> 6;
        sprintf(&buffer, "%i %%", v93);
        if (v186 == 2)
          v94 = 171;
        else
          v94 = 143;
        scale_text(440, 340, v94, 0, 200, 640);
        if (game_svga) {
          if (v186 == 1)
            v95 = 171;
          else
            v95 = 143;
          scale_text(440, 360, v95, 1, 20, 640);
        } else {
          if (v186 == 1)
            v96 = 171;
          else
            v96 = 143;
          scale_text(440, 360, v96, 1, 200, 640);
        }
        if (v186)
          v97 = 143;
        else
          v97 = 171;
        v4 = (int)font1_ascii;
        i = (int)&font1_offsets;
        v6 = scale_text(430, 380, v97, 2, 200, 640);
        goto LABEL_623;
      case 5:
        if (v189 != 6)
          v182 = -1;
        if (player_type == 2) {
          sprintf(&buffer, "%s %s", config_buffer_variable_57, config_buffer_variable_63);
          if (v182 == 6)
            v98 = 171;
          else
            v98 = 143;
          scale_text(435, 78, v98, 2, 200, 640);
          if (v182 == 6)
            v99 = 171;
          else
            v99 = 143;
          scale_text(440, 78, v99, 0, 200, 640);
        }
        sprintf(&buffer, "%s %s", config_buffer_variable_56, config_buffer_variable_63);
        if (v182 == 5)
          v100 = 171;
        else
          v100 = 143;
        scale_text(435, 96, v100, 2, 200, 640);
        if (v182 == 5)
          v101 = 171;
        else
          v101 = 143;
        scale_text(440, 96, v101, 0, 200, 640);
        if (v182 == 4)
          v102 = 171;
        else
          v102 = 143;
        scale_text(435, 114, v102, 2, 200, 640);
        if ((textures_off & 0x400) != 0) {
          if (v182 == 4)
            v103 = 171;
          else
            v103 = 143;
        } else if (v182 == 4) {
          v103 = 171;
        } else {
          v103 = 143;
        }
        scale_text(440, 114, v103, 0, 200, 640);
        if (v182 == 3)
          v104 = 171;
        else
          v104 = 143;
        scale_text(435, 132, v104, 2, 200, 640);
        if (replay_record) {
          if (v182 == 3)
            v105 = 171;
          else
            v105 = 143;
        } else if (v182 == 3) {
          v105 = 171;
        } else {
          v105 = 143;
        }
        scale_text(440, 132, v105, 0, 200, 640);
        if (v182 == 2)
          v106 = 171;
        else
          v106 = 143;
        scale_text(435, 150, v106, 2, 200, 640);
        if (p_tex_size == 1) {
          if (v182 == 2)
            v107 = 171;
          else
            v107 = 143;
        } else if (v182 == 2) {
          v107 = 171;
        } else {
          v107 = 143;
        }
        scale_text(440, 150, v107, 0, 200, 640);
        if (v182 == 1)
          v108 = 171;
        else
          v108 = 143;
        scale_text(435, 168, v108, 2, 200, 640);
        if (false_starts) {
          if (v182 == 1)
            v109 = 171;
          else
            v109 = 143;
        } else if (v182 == 1) {
          v109 = 171;
        } else {
          v109 = 143;
        }
        scale_text(440, 168, v109, 0, 200, 640);
        if (v182)
          v110 = 143;
        else
          v110 = 171;
        v4 = (int)font1_ascii;
        i = (int)&font1_offsets;
        v6 = scale_text(430, 186, v110, 2, 200, 640);
        goto LABEL_623;
      case 6:
        if (v191) {
          v111 = 171;
          v112 = 165;
        } else {
          v111 = 165;
          v112 = 171;
        }
        if (v189 != 7) {
          v111 = 143;
          v112 = 143;
        }
        if (v191) {
          v181 = 0;
          for (k = &aSlowcoach[14 * (4 - v183)]; *k; ++k) {
            v114 = (unsigned __int8)font1_ascii[(unsigned __int8)*k];
            if (v114 == 255)
              v181 += 8;
            else
              v181 += *(_DWORD *)(front_vga_variable_10 + 12 * v114) + 1;
          }
          v181 += 390;
          v180 = 140 - 18 * v183;
        }
        if (v183 == 5)
          v115 = v112;
        else
          v115 = 143;
        front_text(390, 50, v115, 1);
        if (v183 == 4)
          v116 = v112;
        else
          v116 = 143;
        front_text(385, 68, v116, 2);
        if (v183 == 4)
          v117 = v111;
        else
          v117 = 143;
        scale_text(390, 68, v117, 0, 200, 630);
        if (v183 == 3)
          v118 = v112;
        else
          v118 = 143;
        front_text(385, 86, v118, 2);
        if (v183 == 3)
          v119 = v111;
        else
          v119 = 143;
        scale_text(390, 86, v119, 0, 200, 630);
        if (v183 == 2)
          v120 = v112;
        else
          v120 = 143;
        front_text(385, 104, v120, 2);
        if (v183 == 2)
          v121 = v111;
        else
          v121 = 143;
        scale_text(390, 104, v121, 0, 200, 630);
        if (v183 == 1)
          v122 = v112;
        else
          v122 = 143;
        front_text(385, 122, v122, 2);
        if (v183 != 1)
          v111 = 143;
        v169 = v111;
        v123 = v183;
        scale_text(390, 122, v169, 0, 200, 630);
        if (v123)
          v112 = 143;
        v4 = (int)font1_ascii;
        i = (int)&font1_offsets;
        v6 = front_text(390, 140, v112, 1);
        if (v191) {
          LODWORD(v6) = frames & 0xF;
          if ((unsigned int)v6 < 8) {
            v124 = stringwidth(&aSlowcoach[14 * (4 - v183)], HIDWORD(v6), font1_ascii, &font1_offsets) + 390;
            if (v124 <= 620) {
              i = (int)&font1_offsets;
              v4 = (int)font1_ascii;
              v6 = front_text(v124, v180, 171, 0);
            } else {
              v4 = (int)font1_ascii;
              i = (int)&font1_offsets;
              v6 = front_text(621, v180, 171, 0);
            }
          }
        }
        goto LABEL_623;
      default:
        goto LABEL_623;
    }
  }*/
}

//-------------------------------------------------------------------------------------------------

int front_displaycalibrationbar(int result, int a2, int a3)
{
  (void)(result); (void)(a2); (void)(a3);
  return 0;
  /*
  int v3; // edi
  _BYTE *v4; // ecx
  int v5; // edi
  int i; // esi
  int v7; // ebp

  v3 = a3;
  if (a3 < -100)
    v3 = -100;
  if (v3 > 100)
    v3 = 100;
  v4 = (_BYTE *)(winw * a2 + result + scrbuf);
  if (current_mode) {
    v5 = v3 + 103;
    for (i = 0; i < 17; ++i) {
      if (i && i != 16) {
        *v4 = -113;
        v4[206] = -113;
        v4[v5] = -85;
        v4[v5 - 1] = -85;
        v4[v5 - 2] = -85;
        v4[v5 + 1] = -85;
        v4[v5 + 2] = -85;
        v4[103] = -25;
        v4[104] = -25;
        v7 = winw;
        v4[102] = -25;
        v4 += v7;
      } else {
        result = memset(v4, 143, 206);
        v4 += winw;
      }
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int front_volumebar(int a1, int a2, int a3)
{
  (void)(a1); (void)(a2); (void)(a3);
  return 0;/*
  _BYTE *v3; // ecx
  int i; // esi
  int result; // eax

  v3 = (_BYTE *)(winw * a1 + scrbuf + 430);
  for (i = 0; i < 17; ++i) {
    if (i && i != 16) {
      *v3 = -113;
      memset(v3 + 1, a3, 160 * a2 / 127);
      result = winw;
      v3[161] = -113;
      v3 += result;
    } else {
      result = memset(v3, 143, 162);
      v3 += winw;
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void select_players()
{
  unsigned int uiSelectedPlayerType; // esi
  int iNetworkStatus; // edi
  uint32 uiCheatArrayOffset; // eax
  int iCheatPlayerLoop; // edx
  int iCheatPlayerIndex; // edx
  int iPlayerCarIndex; // ecx
  char byMenuColor1; // al
  char byMenuColor2; // al
  char byMenuColor3; // al
  char byMenuColor4; // al
  char byMenuColor5; // al
  uint8 byInputKey; // al
  uint8 byExtendedKey; // al
  int iNetworkMode; // [esp+8h] [ebp-20h]
  int iPlayerIndex; // [esp+Ch] [ebp-1Ch]
  int iY; // [esp+10h] [ebp-18h]
  int iComPortStatus; // [esp+14h] [ebp-14h]
  char *szText; // [esp+18h] [ebp-10h]
  int iPlayerListCount; // [esp+1Ch] [ebp-Ch]
  int iNetworkSetupFlag; // [esp+20h] [ebp-8h]
  int iExitFlag; // [esp+24h] [ebp-4h]

  iComPortStatus = 0;// gss16550(2);                 // Initialize COM port status and screen fade
  iExitFlag = 0;
  fade_palette(0);
  uiSelectedPlayerType = player_type;
  front_fade = 0;
  if (player_type == 1 && net_type)           // Map network types to player selection modes: Serial=3, Modem=4
  {
    if ((unsigned int)net_type <= 1) {
      uiSelectedPlayerType = 3;
    } else if (net_type == 2) {
      uiSelectedPlayerType = 4;
    }
  }
  iNetworkSetupFlag = 0;
  if (uiSelectedPlayerType == 1 || uiSelectedPlayerType == 3 || uiSelectedPlayerType == 4)// Set network mode flag: -1 for single player and network modes, 0 for two-player
    iNetworkMode = -1;
  else
    iNetworkMode = 0;
  iNetworkStatus = 0;
  do {                                             // Handle game type switches (race type, championship, etc.)
    if (switch_types) {
      game_type = switch_types - 1;
      if (switch_types == 1 && competitors == 1)
        competitors = 16;
      switch_types = 0;
      if (game_type == 1)
        Race = ((uint8)TrackLoad - 1) & 7;
      else
        network_champ_on = 0;
    }
    display_picture(scrbuf, front_vga[0]);
    display_block(scrbuf, (tBlockHeader *)front_vga[1], 3, head_x, head_y, 0);
    display_block(scrbuf, (tBlockHeader *)front_vga[6], 0, 36, 2, 0);
    display_block(scrbuf, (tBlockHeader *)front_vga[5], uiSelectedPlayerType, -4, 247, 0);
    display_block(scrbuf, (tBlockHeader *)front_vga[5], game_type + 5, 135, 247, 0);
    display_block(scrbuf, (tBlockHeader *)front_vga[4], 4, 76, 257, -1);
    display_block(scrbuf, (tBlockHeader *)front_vga[6], 4, 62, 336, -1);
    if (iNetworkStatus && (uiSelectedPlayerType == 1 || uiSelectedPlayerType == 3 || uiSelectedPlayerType == 4))// Show connection status message for network modes
      scale_text(
        (tBlockHeader *)front_vga[15],
        &language_buffer[4992],
        font1_ascii,
        font1_offsets,
        400,
        300,
        231,
        1u,
        200,
        640);
    if ((uiSelectedPlayerType == 3 || uiSelectedPlayerType == 4) && !iComPortStatus)// Show COM port error message if networking failed to initialize
      scale_text(
        (tBlockHeader *)front_vga[15],
        &language_buffer[8064],
        font1_ascii,
        font1_offsets,
        400,
        300,
        231,
        1u,
        200,
        640);
    do {
      uiCheatArrayOffset = broadcast_mode;
      UpdateSDL();
    } while (broadcast_mode);
    if (switch_same > 0)                      // CHEAT MODE HANDLING: Process switch_same command for car synchronization
    {
      for (iCheatPlayerIndex = 0;
            iCheatPlayerIndex < players;
            *(int *)((char *)&infinite_laps + uiCheatArrayOffset) = switch_same - 666) {
        uiCheatArrayOffset += 4;
        ++iCheatPlayerIndex;
      }
      if ((cheat_mode & 0x4000) == 0)
        broadcast_mode = -1;
      while (broadcast_mode)
        UpdateSDL();
      cheat_mode |= CHEAT_MODE_CLONES;
    } else if (switch_same < 0) {
      switch_same = broadcast_mode;
      for (iCheatPlayerLoop = 0; iCheatPlayerLoop < players; *(int *)((char *)&infinite_laps + uiCheatArrayOffset) = -1) {
        uiCheatArrayOffset += 4;
        ++iCheatPlayerLoop;
      }
      cheat_mode &= ~CHEAT_MODE_CLONES;
    }
    if (iNetworkMode)                         // NETWORK MODE UI: Show connection info and player list
    {
      if (iNetworkSetupFlag) {
        while (broadcast_mode)
          UpdateSDL();
        broadcast_mode = -667;
        while (broadcast_mode)
          UpdateSDL();
        iNetworkSetupFlag = 0;
      }
      if (net_type) {
        if ((unsigned int)net_type <= 1) {
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[5056],
            font1_ascii,
            font1_offsets,
            400,
            60,
            143,
            1u,
            200,
            640);
        } else if (net_type == 2) {
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[5120],
            font1_ascii,
            font1_offsets,
            400,
            60,
            143,
            1u,
            200,
            640);
        }
      } else {
        scale_text(
          (tBlockHeader *)front_vga[15],
          &language_buffer[4096],
          font1_ascii,
          font1_offsets,
          400,
          60,
          143,
          1u,
          200,
          640);
      }
      iPlayerListCount = 0;
      if (network_on > 0)                     // Display connected players and their selected cars
      {
        iPlayerIndex = 0;
        iY = 80;
        szText = player_names[0];
        do {
          scale_text((tBlockHeader *)front_vga[15], szText, font1_ascii, font1_offsets, 336, iY, 143, 2u, 200, 640);
          iPlayerCarIndex = Players_Cars[iPlayerIndex];
          if (iPlayerCarIndex < 0)
            scale_text(
              (tBlockHeader *)front_vga[15],
              &language_buffer[4160],
              font1_ascii,
              font1_offsets,
              340,
              iY,
              131,
              0,
              200,
              640);
          else
            scale_text(
              (tBlockHeader *)front_vga[15],
              CompanyNames[iPlayerCarIndex],
              font1_ascii,
              font1_offsets,
              342,
              iY,
              143,
              0,
              200,
              640);
          ++iPlayerIndex;
          szText += 9;
          iY += 18;
          ++iPlayerListCount;

          UpdateSDL();
        } while (iPlayerListCount < network_on);
      }
      if (net_type) {
        if ((unsigned int)net_type <= 1) {
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[5184],
            font1_ascii,
            font1_offsets,
            400,
            380,
            231,
            1u,
            200,
            640);
        } else if (net_type == 2) {
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[5248],
            font1_ascii,
            font1_offsets,
            400,
            380,
            231,
            1u,
            200,
            640);
        }
      } else {
        scale_text(
          (tBlockHeader *)front_vga[15],
          &language_buffer[4224],
          font1_ascii,
          font1_offsets,
          400,
          380,
          231,
          1u,
          200,
          640);
      }
      scale_text(
        (tBlockHeader *)front_vga[15],
        &language_buffer[7104],
        font1_ascii,
        font1_offsets,
        400,
        360,
        231,
        1u,
        200,
        640);
    } else {
      scale_text(
        (tBlockHeader *)front_vga[15],
        &language_buffer[2944],
        font1_ascii,
        font1_offsets,
        400,
        75,
        143,
        1u,
        200,
        640);                                   // MENU MODE UI: Show player selection options with highlighting
      scale_text(
        (tBlockHeader *)front_vga[15],
        &language_buffer[3008],
        font1_ascii,
        font1_offsets,
        400,
        93,
        143,
        1u,
        200,
        640);
      if (uiSelectedPlayerType)               // Highlight current selection
        byMenuColor1 = 0x8F;
      else
        byMenuColor1 = 0xAB;
      scale_text(
        (tBlockHeader *)front_vga[15],
        &language_buffer[2112],
        font1_ascii,
        font1_offsets,
        400,
        135,
        byMenuColor1,
        1u,
        200,
        640);
      if (uiSelectedPlayerType == 2)
        byMenuColor2 = 0xAB;
      else
        byMenuColor2 = 0x8F;
      scale_text(
        (tBlockHeader *)front_vga[15],
        &language_buffer[2240],
        font1_ascii,
        font1_offsets,
        400,
        153,
        byMenuColor2,
        1u,
        200,
        640);
      if (uiSelectedPlayerType == 1)
        byMenuColor3 = 0xAB;
      else
        byMenuColor3 = 0x8F;
      scale_text(
        (tBlockHeader *)front_vga[15],
        &language_buffer[2176],
        font1_ascii,
        font1_offsets,
        400,
        171,
        byMenuColor3,
        1u,
        200,
        640);
      if (uiSelectedPlayerType == 3)
        byMenuColor4 = 0xAB;
      else
        byMenuColor4 = 0x8F;
      scale_text(
        (tBlockHeader *)front_vga[15],
        &language_buffer[2304],
        font1_ascii,
        font1_offsets,
        400,
        189,
        byMenuColor4,
        1u,
        200,
        640);
      if (uiSelectedPlayerType == 4)
        byMenuColor5 = 0xAB;
      else
        byMenuColor5 = 0x8F;
      scale_text(
        (tBlockHeader *)front_vga[15],
        &language_buffer[2368],
        font1_ascii,
        font1_offsets,
        400,
        207,
        byMenuColor5,
        1u,
        200,
        640);
    }
    show_received_mesage();
    copypic(scrbuf, screen);
    if (!front_fade)                          // Handle screen fade-in effect
    {
      front_fade = -1;
      fade_palette(32);
      frames = 0;
    }
    while (fatkbhit())                        // KEYBOARD INPUT PROCESSING: Handle navigation and selection
    {
      byInputKey = fatgetch();
      if (byInputKey < 0x4Du) {
        if (byInputKey < 0xDu) {                                       // Handle extended keys (arrow keys for navigation)
          if (!byInputKey) {
            byExtendedKey = fatgetch();
            if (byExtendedKey >= 0x48u) {
              if (byExtendedKey <= 0x48u) {                                 // Up arrow: Navigate through player selection options
                if (!iNetworkMode) {
                  switch (uiSelectedPlayerType) {
                    case 1u:
                      uiSelectedPlayerType = 2;
                      iNetworkStatus = 0;
                      break;
                    case 2u:
                      uiSelectedPlayerType = 0;
                      iNetworkStatus = 0;
                      break;
                    case 3u:
                      uiSelectedPlayerType = 1;
                      iNetworkStatus = 0;
                      break;
                    case 4u:
                      uiSelectedPlayerType = 3;
                      iNetworkStatus = 0;
                      break;
                    default:
                      continue;
                  }
                }
              } else if (byExtendedKey == 80 && !iNetworkMode)// Down arrow: Navigate through player selection options
              {
                switch (uiSelectedPlayerType) {
                  case 0u:
                    uiSelectedPlayerType = 2;
                    iNetworkStatus = 0;
                    break;
                  case 1u:
                    uiSelectedPlayerType = 3;
                    iNetworkStatus = 0;
                    break;
                  case 2u:
                    uiSelectedPlayerType = 1;
                    iNetworkStatus = 0;
                    break;
                  case 3u:
                    uiSelectedPlayerType = 4;
                    iNetworkStatus = 0;
                    break;
                  default:
                    continue;
                }
              }
            }
          }
        } else if (byInputKey <= 0xDu || byInputKey == 27)// Enter/Escape: Confirm selection or exit menu
        {
          switch (uiSelectedPlayerType) {
            case 0u:
            case 2u:
              goto LABEL_128;
            case 1u:
            case 3u:
            case 4u:
              if (uiSelectedPlayerType != 1 && !iComPortStatus)
                continue;
              if (uiSelectedPlayerType == 1)
                net_type = 0;
              if (uiSelectedPlayerType == 3)
                net_type = 1;
              if (uiSelectedPlayerType == 4)
                net_type = 2;
              //gssCommsSetType(net_type);
              if (iNetworkMode) {
              LABEL_128:
                iExitFlag = -1;
                continue;
              }
              if (iNetworkStatus)
                goto LABEL_159;
              if (net_type)                   // NETWORK SETUP: Initialize communication for selected network type
              {
                if ((unsigned int)net_type <= 1) {
                  //TODO
                  //if (select_comport(uiSelectedPlayerType, (char *)3, uiSelectedPlayerType, 1))
                  //  goto LABEL_153;
                } else {
                  if (net_type != 2)
                    goto LABEL_156;
                  //TODO
                  //if (select_modemstuff(uiSelectedPlayerType)) {
                  //LABEL_153:
                  //  network_slot = 0;
                  //  goto LABEL_156;
                  //}
                }
                network_on = 0;
                network_slot = -1;
              } else {
                network_slot = select_netslot();// IPX network: Select network slot and handle connection
                if (network_slot >= 0) {
                  broadcast_mode = -1;
                  while (broadcast_mode)
                    UpdateSDL();
                } else if (network_slot == -2) {
                  broadcast_mode = -666;
                  while (broadcast_mode)
                    UpdateSDL();
                  close_network();
                } else {
                  iNetworkStatus = -1;
                }
              }
            LABEL_156:
              if (uiSelectedPlayerType == 3 && network_slot >= 0)
                Initialise_Network(0);
            LABEL_159:
              if (network_on) {
                iNetworkSetupFlag = -1;
                iNetworkMode = -1;
              }
              break;
            default:
              continue;
          }
        }
      } else if (byInputKey <= 0x4Du) {
      LABEL_119:
        if (network_on)
          select_messages();
      } else if (byInputKey < 0x6Du)            // M/m keys: Open message selection (network mode only)
      {
        if (byInputKey == 81)
          goto LABEL_121;
      } else {
        if (byInputKey <= 0x6Du)
          goto LABEL_119;
        if (byInputKey == 113) {                                       // Q/q keys: Quit network and return to player selection
        LABEL_121:
          if (network_on) {
            broadcast_mode = -666;
            while (broadcast_mode)
              UpdateSDL();
            frames = 0;
            while (frames < 3)
              ;
            close_network();
            iNetworkMode = 0;
            uiSelectedPlayerType = 0;
          }
        }
      }
      UpdateSDL();
    }
    UpdateSDL();
  } while (!iExitFlag);                         // MAIN SELECTION LOOP - Handle UI rendering and input processing
  if (uiSelectedPlayerType < 3)               // CLEANUP: Set final player type and network settings based on selection
  {
    if (uiSelectedPlayerType != 1)
      goto LABEL_169;
    player_type = 1;
    net_type = 0;
  } else if (uiSelectedPlayerType <= 3) {
    player_type = 1;
    net_type = 1;
  } else if (uiSelectedPlayerType == 4) {
    player_type = 1;
    net_type = 2;
  } else {
  LABEL_169:
    player_type = uiSelectedPlayerType;
  }
  fade_palette(0);
  front_fade = 0;
}

//-------------------------------------------------------------------------------------------------

void select_type()
{
  int iMenuSelection; // edi
  int iCurrentOption; // esi
  char *pszTextBuffer; // edx
  char byGameModeColor1; // al
  char byGameModeColor2; // al
  char byGameModeColor3; // al
  char byDifficultyColor1; // al
  char byDifficultyColor2; // al
  char byDifficultyColor3; // al
  char byDifficultyColor4; // al
  char byDifficultyColor5; // al
  char byDifficultyColor6; // al
  char byCompetitorColor1; // al
  char byCompetitorColor2; // al
  char byCompetitorColor3; // al
  char byDamageColor1; // al
  char byDamageColor2; // al
  char byDamageColor3; // al
  char byTextureColor1; // al
  char byTextureColor2; // al
  uint32 uiUpdatedCheatFlags; // eax
  int iCheatSetLoop; // eax
  uint8 byInputKey; // al
  uint8 byExtendedKey; // al
  int iCupIncrement; // edx
  int iTrackUpperLimit; // edx
  int iTrackLowerLimit; // ebx
  int iTextYPosition; // [esp-14h] [ebp-48h]
  char byFinalTextColor; // [esp-10h] [ebp-44h]
  int iCheatModesAvailable; // [esp+0h] [ebp-34h]
  int iExitFlag; // [esp+4h] [ebp-30h]
  int iSkipColor; // [esp+8h] [ebp-2Ch]
  char byCompetitorMenuColor; // [esp+Ch] [ebp-28h]
  char byTextColor; // [esp+10h] [ebp-24h]
  char byDamageMenuColor; // [esp+14h] [ebp-20h]
  char byTextureMenuColor; // [esp+18h] [ebp-1Ch]
  char byDifficultyMenuColor; // [esp+1Ch] [ebp-18h]
  int iNetworkDisplayY; // [esp+20h] [ebp-14h]
  int iY; // [esp+24h] [ebp-10h]
  char *szText; // [esp+28h] [ebp-Ch]
  int iNetworkPlayerCount; // [esp+2Ch] [ebp-8h]
  int iBlockIdx; // [esp+30h] [ebp-4h]

  iExitFlag = 0;                                // Initialize exit flag and check game restrictions
  if (game_type == 1 && Race > 0)             // Championship mode after first race - restrict options to track selection only
    iSkipColor = -1;
  else
    iSkipColor = 0;
  if ((cheat_mode & 0x100) != 0 || (textures_off & 0x8000) != 0)
    iCheatModesAvailable = -1;
  else
    iCheatModesAvailable = 0;
  iBlockIdx = (TrackLoad - 1) / 8;// Calculate cup index from current track (TrackLoad): cups are groups of 8 tracks
  front_vga[14] = load_picture("cupicons.bm");  // Load cup icons graphics and initialize screen
  iMenuSelection = 0;
  fade_palette(0);
  front_fade = 0;
  iCurrentOption = 5;
  do {                                             // Handle game type switches and updates
    if (switch_types) {
      game_type = switch_types - 1;
      if (switch_types == 1 && competitors == 1)
        competitors = 16;
      switch_types = 0;
      if (game_type == 1)
        Race = ((uint8)TrackLoad - 1) & 7;
      else
        network_champ_on = 0;
    }
    display_picture(scrbuf, front_vga[0]);      // RENDER FRAME: Draw background, UI elements, and cup winner icon
    display_block(scrbuf, (tBlockHeader *)front_vga[1], 4, head_x, head_y, 0);
    display_block(scrbuf, (tBlockHeader *)front_vga[6], 0, 36, 2, 0);
    display_block(scrbuf, (tBlockHeader *)front_vga[5], player_type, -4, 247, 0);
    display_block(scrbuf, (tBlockHeader *)front_vga[5], game_type + 5, 135, 247, 0);
    display_block(scrbuf, (tBlockHeader *)front_vga[4], 4, 76, 257, -1);
    if (cup_won && !iSkipColor)
      display_block(scrbuf, (tBlockHeader *)front_vga[1], 8, 200, 56, 0);
    if (iCurrentOption >= 5)                  // Draw selection cursor or \"Random\" indicator (option 5 = Random)
    {
      display_block(scrbuf, (tBlockHeader *)front_vga[6], 4, 62, 336, -1);
    } else {
      display_block(scrbuf, (tBlockHeader *)front_vga[6], 2, 62, 336, -1);
      front_text(
        (tBlockHeader *)front_vga[2],
        "~",
        font2_ascii,
        font2_offsets,
        sel_posns[iCurrentOption].x,
        sel_posns[iCurrentOption].y,
        0x8Fu,
        0);
    }
    if (iSkipColor)                           // OPTION LABELS: Display main option categories (Game Type/Difficulty/etc.)
    {
      front_text(
        (tBlockHeader *)front_vga[2],
        &language_buffer[3136],
        font2_ascii,
        font2_offsets,
        sel_posns[0].x + 132,
        sel_posns[0].y + 7,
        0x8Fu,
        2u);
    } else {
      front_text(
        (tBlockHeader *)front_vga[2],
        &language_buffer[384],
        font2_ascii,
        font2_offsets,
        sel_posns[0].x + 132,
        sel_posns[0].y + 7,
        0x8Fu,
        2u);
      front_text(
        (tBlockHeader *)front_vga[2],
        &language_buffer[3200],
        font2_ascii,
        font2_offsets,
        sel_posns[1].x + 132,
        sel_posns[1].y + 7,
        0x8Fu,
        2u);
      front_text(
        (tBlockHeader *)front_vga[2],
        &language_buffer[3264],
        font2_ascii,
        font2_offsets,
        sel_posns[2].x + 132,
        sel_posns[2].y + 7,
        0x8Fu,
        2u);
      front_text(
        (tBlockHeader *)front_vga[2],
        &language_buffer[3328],
        font2_ascii,
        font2_offsets,
        sel_posns[3].x + 132,
        sel_posns[3].y + 7,
        0x8Fu,
        2u);
      if (iCheatModesAvailable)
        front_text(
          (tBlockHeader *)front_vga[2],
          &language_buffer[4288],
          font2_ascii,
          font2_offsets,
          sel_posns[4].x + 132,
          sel_posns[4].y + 7,
          0x8Fu,
          2u);
    }
    display_block(scrbuf, (tBlockHeader *)front_vga[14], iBlockIdx, 500, 300, 0);// Display cup icon corresponding to current track selection
    if (iSkipColor)                           // CHAMPIONSHIP MODE UI: Show current settings and restrictions
    {
      scale_text(
        (tBlockHeader *)front_vga[15],
        &language_buffer[3392],
        font1_ascii,
        font1_offsets,
        400,
        75,
        143,
        1u,
        200,
        640);
      scale_text(
        (tBlockHeader *)front_vga[15],
        &language_buffer[1280],
        font1_ascii,
        font1_offsets,
        400,
        100,
        143,
        2u,
        200,
        640);
      if ((cheat_mode & 2) != 0)
        scale_text(
          (tBlockHeader *)front_vga[15],
          &language_buffer[2048],
          font1_ascii,
          font1_offsets,
          405,
          100,
          143,
          0,
          200,
          640);
      else
        scale_text(
          (tBlockHeader *)front_vga[15],
          &language_buffer[64 * level + 1472],
          font1_ascii,
          font1_offsets,
          405,
          100,
          143,
          0,
          200,
          640);
      scale_text(
        (tBlockHeader *)front_vga[15],
        &language_buffer[1344],
        font1_ascii,
        font1_offsets,
        400,
        118,
        143,
        2u,
        200,
        640);
      if ((cheat_mode & 2) != 0)
        scale_text(
          (tBlockHeader *)front_vga[15],
          &language_buffer[2048],
          font1_ascii,
          font1_offsets,
          405,
          118,
          143,
          0,
          200,
          640);
      else
        scale_text(
          (tBlockHeader *)front_vga[15],
          &language_buffer[64 * damage_level + 1856],
          font1_ascii,
          font1_offsets,
          405,
          118,
          143,
          0,
          200,
          640);
      scale_text(
        (tBlockHeader *)front_vga[15],
        &language_buffer[1024],
        font1_ascii,
        font1_offsets,
        400,
        136,
        143,
        2u,
        200,
        640);
      if ((unsigned int)competitors < 8) {
        if (competitors == 2)
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[1088],
            font1_ascii,
            font1_offsets,
            405,
            136,
            143,
            0,
            200,
            640);
      } else if ((unsigned int)competitors <= 8) {
        scale_text(
          (tBlockHeader *)front_vga[15],
          &language_buffer[1152],
          font1_ascii,
          font1_offsets,
          405,
          136,
          143,
          0,
          200,
          640);
      } else if (competitors == 16) {
        scale_text(
          (tBlockHeader *)front_vga[15],
          &language_buffer[1216],
          font1_ascii,
          font1_offsets,
          405,
          136,
          143,
          0,
          200,
          640);
      }
      if (network_on)                         // NETWORK MODE: Display connected players list
      {
        scale_text(
          (tBlockHeader *)front_vga[15],
          &language_buffer[4672],
          font1_ascii,
          font1_offsets,
          400,
          154,
          143,
          1u,
          200,
          640);
        iNetworkPlayerCount = 0;
        if (players > 0) {
          szText = player_names[0];
          iY = 28;
          iNetworkDisplayY = 172;
          do {
            if (iNetworkPlayerCount >= 8)
              scale_text((tBlockHeader *)front_vga[15], szText, font1_ascii, font1_offsets, 405, iY, 143, 0, 200, 640);
            else
              scale_text(
                (tBlockHeader *)front_vga[15],
                szText,
                font1_ascii,
                font1_offsets,
                400,
                iNetworkDisplayY,
                143,
                2u,
                200,
                640);
            szText += 9;
            iY += 18;
            iNetworkDisplayY += 18;
            ++iNetworkPlayerCount;

            UpdateSDL();
          } while (iNetworkPlayerCount < players);
        }
      }
    }
    switch (iCurrentOption) {
      case 0:
        if (!iSkipColor)                      // Option 0 - Game Type: Show race modes with highlighting for current selection
        {
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[384],
            font1_ascii,
            font1_offsets,
            400,
            75,
            143,
            1u,
            200,
            640);
          if (iMenuSelection == 1) {
            scale_text(
              (tBlockHeader *)front_vga[15],
              &language_buffer[3584],
              font1_ascii,
              font1_offsets,
              400,
              93,
              143,
              1u,
              200,
              640);
            byTextColor = -85;
          } else {
            byTextColor = -87;
          }
          if (game_type)
            byGameModeColor1 = -113;
          else
            byGameModeColor1 = byTextColor;
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[3648],
            font1_ascii,
            font1_offsets,
            400,
            135,
            byGameModeColor1,
            1u,
            200,
            640);
          if (game_type == 1)
            byGameModeColor2 = byTextColor;
          else
            byGameModeColor2 = -113;
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[3520],
            font1_ascii,
            font1_offsets,
            400,
            153,
            byGameModeColor2,
            1u,
            200,
            640);
          if (game_type == 2)
            byGameModeColor3 = byTextColor;
          else
            byGameModeColor3 = -113;
          byFinalTextColor = byGameModeColor3;
          iTextYPosition = 171;
          pszTextBuffer = &language_buffer[3712];
          goto LABEL_130;
        }
        if (iMenuSelection == 6) {
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[3456],
            font1_ascii,
            font1_offsets,
            400,
            320,
            231,
            1u,
            200,
            640);
          byFinalTextColor = -25;
          iTextYPosition = 338;
          pszTextBuffer = &language_buffer[3520];
          goto LABEL_130;
        }
        break;
      case 1:
        scale_text(
          (tBlockHeader *)front_vga[15],
          &language_buffer[3776],
          font1_ascii,
          font1_offsets,
          400,
          75,
          143,
          1u,
          200,
          640);                                 // Option 1 - Difficulty: Show skill levels with cheat mode override
        if (iMenuSelection == 2) {
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[3840],
            font1_ascii,
            font1_offsets,
            400,
            93,
            143,
            1u,
            200,
            640);
          byDifficultyMenuColor = -85;
        } else {
          byDifficultyMenuColor = -87;
        }
        if ((cheat_mode & 2) == 0) {
          if (level == 5)
            byDifficultyColor1 = byDifficultyMenuColor;
          else
            byDifficultyColor1 = -113;
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[1792],
            font1_ascii,
            font1_offsets,
            400,
            135,
            byDifficultyColor1,
            1u,
            200,
            640);
          if (level == 4)
            byDifficultyColor2 = byDifficultyMenuColor;
          else
            byDifficultyColor2 = -113;
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[1728],
            font1_ascii,
            font1_offsets,
            400,
            153,
            byDifficultyColor2,
            1u,
            200,
            640);
          if (level == 3)
            byDifficultyColor3 = byDifficultyMenuColor;
          else
            byDifficultyColor3 = -113;
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[1664],
            font1_ascii,
            font1_offsets,
            400,
            171,
            byDifficultyColor3,
            1u,
            200,
            640);
          if (level == 2)
            byDifficultyColor4 = byDifficultyMenuColor;
          else
            byDifficultyColor4 = -113;
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[1600],
            font1_ascii,
            font1_offsets,
            400,
            189,
            byDifficultyColor4,
            1u,
            200,
            640);
          if (level == 1)
            byDifficultyColor5 = byDifficultyMenuColor;
          else
            byDifficultyColor5 = -113;
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[1536],
            font1_ascii,
            font1_offsets,
            400,
            207,
            byDifficultyColor5,
            1u,
            200,
            640);
          if (level)
            byDifficultyColor6 = -113;
          else
            byDifficultyColor6 = byDifficultyMenuColor;
          byFinalTextColor = byDifficultyColor6;
          iTextYPosition = 225;
          pszTextBuffer = &language_buffer[1472];
          goto LABEL_130;
        }
        scale_text(
          (tBlockHeader *)front_vga[15],
          &language_buffer[2048],
          font1_ascii,
          font1_offsets,
          400,
          135,
          byDifficultyMenuColor,
          1u,
          200,
          640);
        break;
      case 2:
        scale_text(
          (tBlockHeader *)front_vga[15],
          &language_buffer[3904],
          font1_ascii,
          font1_offsets,
          400,
          75,
          143,
          1u,
          200,
          640);                                 // Option 2 - Competitors: Show number of opponent cars (2/8/16 or \"Just Me\")
        if (iMenuSelection == 3) {
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[3008],
            font1_ascii,
            font1_offsets,
            400,
            93,
            143,
            1u,
            200,
            640);
          byDamageMenuColor = -85;
        } else {
          byDamageMenuColor = -87;
        }
        if (competitors != 1) {
          if (competitors == 2)
            byCompetitorColor1 = byDamageMenuColor;
          else
            byCompetitorColor1 = -113;
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[1088],
            font1_ascii,
            font1_offsets,
            400,
            135,
            byCompetitorColor1,
            1u,
            200,
            640);
          if (competitors == 8)
            byCompetitorColor2 = byDamageMenuColor;
          else
            byCompetitorColor2 = -113;
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[1152],
            font1_ascii,
            font1_offsets,
            400,
            153,
            byCompetitorColor2,
            1u,
            200,
            640);
          if (competitors == 16)
            byCompetitorColor3 = byDamageMenuColor;
          else
            byCompetitorColor3 = -113;
          byFinalTextColor = byCompetitorColor3;
          iTextYPosition = 171;
          pszTextBuffer = &language_buffer[1216];
          goto LABEL_130;
        }
        scale_text(
          (tBlockHeader *)front_vga[15],
          &language_buffer[3968],
          font1_ascii,
          font1_offsets,
          400,
          135,
          byDamageMenuColor,
          1u,
          200,
          640);
        break;
      case 3:
        scale_text(
          (tBlockHeader *)front_vga[15],
          &language_buffer[4032],
          font1_ascii,
          font1_offsets,
          400,
          75,
          143,
          1u,
          200,
          640);                                 // Option 3 - Damage: Show car damage levels (None/Cosmetic/Realistic)
        if (iMenuSelection == 4) {
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[3840],
            font1_ascii,
            font1_offsets,
            400,
            93,
            143,
            1u,
            200,
            640);
          byTextureMenuColor = -85;
        } else {
          byTextureMenuColor = -87;
        }
        if ((cheat_mode & 2) == 0) {
          if (damage_level)
            byDamageColor1 = -113;
          else
            byDamageColor1 = byTextureMenuColor;
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[1856],
            font1_ascii,
            font1_offsets,
            400,
            135,
            byDamageColor1,
            1u,
            200,
            640);
          if (damage_level == 1)
            byDamageColor2 = byTextureMenuColor;
          else
            byDamageColor2 = -113;
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[1920],
            font1_ascii,
            font1_offsets,
            400,
            153,
            byDamageColor2,
            1u,
            200,
            640);
          if (damage_level == 2)
            byDamageColor3 = byTextureMenuColor;
          else
            byDamageColor3 = -113;
          byFinalTextColor = byDamageColor3;
          iTextYPosition = 171;
          pszTextBuffer = &language_buffer[1984];
          goto LABEL_130;
        }
        scale_text(
          (tBlockHeader *)front_vga[15],
          &language_buffer[2048],
          font1_ascii,
          font1_offsets,
          400,
          135,
          byTextureMenuColor,
          1u,
          200,
          640);
        break;
      case 4:
        scale_text(
          (tBlockHeader *)front_vga[15],
          &language_buffer[4288],
          font1_ascii,
          font1_offsets,
          400,
          75,
          143,
          1u,
          200,
          640);                                 // Option 4 - Textures: Show texture quality options (On/Off)
        if (iMenuSelection == 5) {
          scale_text(
            (tBlockHeader *)front_vga[15],
            &language_buffer[4480],
            font1_ascii,
            font1_offsets,
            400,
            93,
            143,
            1u,
            200,
            640);
          byCompetitorMenuColor = -85;
        } else {
          byCompetitorMenuColor = -87;
        }
        if ((textures_off & 0x10000) != 0)
          byTextureColor1 = -113;
        else
          byTextureColor1 = byCompetitorMenuColor;
        scale_text(
          (tBlockHeader *)front_vga[15],
          &language_buffer[4352],
          font1_ascii,
          font1_offsets,
          400,
          135,
          byTextureColor1,
          1u,
          200,
          640);
        if ((textures_off & 0x10000) != 0)
          byTextureColor2 = byCompetitorMenuColor;
        else
          byTextureColor2 = -113;
        byFinalTextColor = byTextureColor2;
        iTextYPosition = 153;
        pszTextBuffer = &language_buffer[4416];
      LABEL_130:
        scale_text(
          (tBlockHeader *)front_vga[15],
          pszTextBuffer,
          font1_ascii,
          font1_offsets,
          400,
          iTextYPosition,
          byFinalTextColor,
          1u,
          200,
          640);
        break;
      default:
        break;                                  // OPTION-SPECIFIC UI: Display details for currently selected option
    }
    show_received_mesage();
    copypic(scrbuf, screen);
    if (switch_same > 0)                      // CHEAT MODE HANDLING: Process switch_same command for player synchronization
    {
      iCheatSetLoop = 0;
      if (players > 0) {
        // Set all players to the same car in cheat mode
        for (int i = 0; i < players; i++) {
            Players_Cars[i] = switch_same - 666;
        }
        //iCheatArrayOffset2 = 0;
        //do {
        //  iCheatArrayOffset2 += 4;
        //  ++iCheatSetLoop;
        //  *(int *)((char *)&infinite_laps + iCheatArrayOffset2) = switch_same - 666;
        //} while (iCheatSetLoop < players);
      }
      uiUpdatedCheatFlags = cheat_mode;
      uiUpdatedCheatFlags |= CHEAT_MODE_CLONES;
    } else {
      if (switch_same >= 0)
        goto LABEL_142;
      switch_same = 0;
      for (int i = 0; i < players; i++) {
        Players_Cars[i] = -1;
      }
      //iCheatResetLoop1 = 0;
      //switch_same = 0;
      //if (players > 0) {
      //  iCheatArrayOffset1 = 0;
      //  do {
      //    iCheatArrayOffset1 += 4;
      //    ++iCheatResetLoop1;
      //    *(int *)((char *)&infinite_laps + iCheatArrayOffset1) = -1;
      //  } while (iCheatResetLoop1 < players);
      //}
      uiUpdatedCheatFlags = cheat_mode;
      uiUpdatedCheatFlags &= ~CHEAT_MODE_CLONES;
    }
    cheat_mode = uiUpdatedCheatFlags;
  LABEL_142:
    if (!front_fade)                          // Handle screen fade-in effect
    {
      front_fade = -1;
      fade_palette(32);
      frames = 0;
    }
    while (fatkbhit())                        // KEYBOARD INPUT PROCESSING: Handle navigation and option changes
    {
      byInputKey = fatgetch();
      if (byInputKey < 0x1Bu) {
        if (byInputKey) {                                       // Enter key: Confirm selection or navigate into sub-options
          if (byInputKey == 13) {
            sfxsample(83, 0x8000);
            if (iMenuSelection) {
              if (game_type == 1) {
                Race = 0;
                TrackLoad = 8 * iBlockIdx + 1;
              }
              iMenuSelection = 0;
              broadcast_mode = -1;
              while (broadcast_mode)
                UpdateSDL();
            } else {
              switch (iCurrentOption) {
                case 0:
                  if (iSkipColor)
                    iMenuSelection = 6;
                  else
                    iMenuSelection = 1;
                  break;
                case 1:
                  iMenuSelection = 2;
                  break;
                case 2:
                  iMenuSelection = 3;
                  break;
                case 3:
                  iMenuSelection = 4;
                  break;
                case 4:
                  iMenuSelection = 5;
                  break;
                case 5:
                  goto LABEL_248;
                default:
                  continue;
              }
            }
          }
        } else {
          byExtendedKey = fatgetch();           // Arrow keys: Navigate through options and change values
          switch (iMenuSelection) {
            case 0:
              if (byExtendedKey >= 0x48u)     // Main menu navigation: Up/Down arrows move between option categories
              {
                if (byExtendedKey <= 0x48u) {
                  if (iSkipColor) {
                    iCurrentOption = 0;
                  } else {
                    --iCurrentOption;
                    if (!iCheatModesAvailable && iCurrentOption == 4)
                      iCurrentOption = 3;
                    if (iCurrentOption < 0)
                      iCurrentOption = 0;
                  }
                } else if (byExtendedKey == 80) {
                  if (iSkipColor) {
                    iCurrentOption = 5;
                  } else {
                    if (iCheatModesAvailable) {
                      ++iCurrentOption;
                    } else if (++iCurrentOption > 3) {
                      iCurrentOption = 5;
                    }
                    if (iCurrentOption > 5)
                      iCurrentOption = 5;
                  }
                }
              }
              break;
            case 1:
              if (byExtendedKey >= 0x48u)     // Game Type option: Navigate between race modes and adjust competitors
              {
                if (byExtendedKey <= 0x48u) {
                  if (--game_type < 0)
                    game_type = 0;
                  if (competitors == 1)
                    goto LABEL_187;
                } else if (byExtendedKey == 80) {
                  if (++game_type < 2) {
                    if (competitors == 1)
                      competitors = 16;
                  } else {
                    game_type = 2;
                    competitors = 1;
                  }
                }
              }
              break;
            case 2:
              if (byExtendedKey >= 0x48u) {
                if (byExtendedKey <= 0x48u) {
                  if (levels[++level] <= 0.0)
                    --level;
                } else if (byExtendedKey == 80 && --level < 0) {
                  level = 0;
                }
              }
              break;
            case 3:
              if (byExtendedKey >= 0x48u) {
                if (byExtendedKey <= 0x48u) {
                  if (game_type < 2 && (unsigned int)competitors >= 8) {
                    if ((unsigned int)competitors <= 8) {
                      competitors = 2;
                    } else if (competitors == 16) {
                      competitors = 8;
                    }
                  }
                } else if (byExtendedKey == 80 && game_type < 2 && (unsigned int)competitors >= 2) {
                  if ((unsigned int)competitors <= 2) {
                    competitors = 8;
                  } else if (competitors == 8) {
                  LABEL_187:
                    competitors = 16;
                  }
                }
              }
              break;
            case 4:
              if (byExtendedKey >= 0x48u) {
                if (byExtendedKey <= 0x48u) {
                  if (--damage_level < 0)
                    damage_level = 0;
                } else if (byExtendedKey == 80 && ++damage_level > 2) {
                  damage_level = 2;
                }
              }
              break;
            case 5:
              if (byExtendedKey >= 0x48u) {
                if (byExtendedKey <= 0x48u) {
                  textures_off &= ~0x10000u;
                } else if (byExtendedKey == 80) {
                  textures_off |= 0x10000u;
                }
              }
              break;
            default:
              continue;
          }
        }
      } else if (byInputKey <= 0x1Bu)           // Escape key: Exit to main menu or back to option selection
      {
        if (iMenuSelection)
          iMenuSelection = 0;
        else
          LABEL_248:
        iExitFlag = -1;
      } else if (byInputKey < 0x59u) {                                         // Space key: Cycle through cups (track groups) if not in championship
        if (byInputKey == 32 && !iSkipColor) {
          iCupIncrement = ++iBlockIdx;
          if ((cup_won & 1) == 0 && iCupIncrement == 1)
            iBlockIdx = 2;
          if ((cup_won & 2) == 0 && iBlockIdx == 2)
            iBlockIdx = 3;
          if (iBlockIdx > 2)
            iBlockIdx = 0;
          TrackLoad = 8 * iBlockIdx + (((uint8)TrackLoad - 1) & 7) + 1;
          broadcast_mode = -1;
          while (broadcast_mode)
            UpdateSDL();
        }
      } else if (byInputKey <= 0x59u || byInputKey == 121) {                                         // Y/y key: \"Yes\" - confirm championship exit and reset to race mode
        if (iSkipColor) {
          if (iMenuSelection == 6) {
            game_type = 0;
            iSkipColor = 0;
            iMenuSelection = 0;
            if (network_on) {
              if (Race <= 0) {
                broadcast_mode = -1;
                while (broadcast_mode)
                  UpdateSDL();
              } else {
                broadcast_mode = -666;
                while (broadcast_mode)
                  UpdateSDL();
                frames = 0;
                while (frames < 3)
                  ;
                close_network();
                network_champ_on = 0;
              }
            }
          }
        }
      }
      UpdateSDL();
    }
    UpdateSDL();
  } while (!iExitFlag);                         // MAIN SELECTION LOOP - Handle UI rendering and input processing
  if (!iSkipColor)                            // CLEANUP: Set final game parameters and track selection based on options
  {
    network_champ_on = 0;
    iTrackUpperLimit = 8 * iBlockIdx + 8;
    iTrackLowerLimit = 8 * iBlockIdx + 1;
    if (game_type)                            // Initialize championship mode: reset all statistics and set starting track
    {
      if ((unsigned int)game_type <= 1) {
        Race = 0;
        memset(championship_points, 0, sizeof(championship_points));
        memset(team_points, 0, sizeof(team_points));
        memset(total_kills, 0, sizeof(total_kills));
        memset(total_fasts, 0, sizeof(total_fasts));
        memset(total_wins, 0, sizeof(total_wins));
        memset(team_kills, 0, sizeof(team_kills));
        memset(team_fasts, 0, sizeof(team_fasts));
        memset(team_wins, 0, sizeof(team_wins));
        TrackLoad = 8 * iBlockIdx + 1;
      } else if (game_type == 2) {
        NoOfLaps = 5;
        competitors = 1;
        if (iTrackLowerLimit > TrackLoad || iTrackUpperLimit < TrackLoad)
          TrackLoad = 8 * iBlockIdx + (((uint8)TrackLoad - 1) & 7) + 1;
      }
    } else if (iTrackLowerLimit > TrackLoad || iTrackUpperLimit < TrackLoad) {
      TrackLoad = 8 * iBlockIdx + (((uint8)TrackLoad - 1) & 7) + 1;
    }
    broadcast_mode = -1;
    while (broadcast_mode)
      UpdateSDL();
  }
  fade_palette(0);
  fre((void **)&front_vga[14]);
  front_fade = 0;
}

//-------------------------------------------------------------------------------------------------

void select_track()
{
  return;
  /*
  int v4; // edi
  int v5; // ebp
  int v6; // esi
  int v7; // eax
  __int64 v8; // rax
  double v9; // st7
  __int64 v10; // rtt
  int v11; // ecx
  int v12; // ebx
  int v13; // ecx
  void *v14; // ebx
  __int64 v15; // rax
  int v16; // eax
  int v17; // edx
  int v18; // eax
  int v19; // eax
  int v20; // edx
  double v21; // st7
  unsigned int v22; // ecx
  unsigned __int8 v23; // al
  unsigned __int8 v24; // al
  int v25; // edx
  _DWORD *result; // eax
  __int64 v27; // [esp+0h] [ebp-50h]
  float v28; // [esp+8h] [ebp-48h]
  int v29; // [esp+Ch] [ebp-44h]
  int v30; // [esp+10h] [ebp-40h]
  int v31; // [esp+14h] [ebp-3Ch]
  int v32; // [esp+18h] [ebp-38h]
  int v33; // [esp+1Ch] [ebp-34h]
  float v34; // [esp+20h] [ebp-30h]
  int v35; // [esp+24h] [ebp-2Ch]
  int v36; // [esp+28h] [ebp-28h]
  int v37; // [esp+2Ch] [ebp-24h]
  int v38; // [esp+30h] [ebp-20h]

  v4 = 36;
  fade_palette(0, 0, a3, a4);
  v31 = 0;
  front_fade = 0;
  v37 = 0;
  if (TrackLoad > 0) {
    v5 = ((_BYTE)TrackLoad - 1) & 7;
    if (game_type == 1)
      v5 = 8;
  } else {
    v5 = 0;
  }
  v6 = TrackLoad;
  fre(&front_vga_variable_3);
  if (TrackLoad >= 0)
    loadtrack(TrackLoad, -1);
  front_vga_variable_3 = load_picture(aTrknameBm);
  front_vga_variable_8 = load_picture(&aBonustrkBm[1]);
  v32 = 0;
  front_vga_variable_9 = load_picture(aCupiconsBm);
  frames = 0;
  v34 = cur_TrackZ;
  *((float *)&v27 + 1) = cur_TrackZ;
  v28 = -(cur_TrackZ + frontend_c_variable_54) * frontend_c_variable_55;
  do {
    if (game_type == 1)
      v5 = 8;
    v29 = frames;
    frames = 0;
    v33 = TrackLoad;
    if (SoundCard
      && front_fade
      && SampleHandleCar_variable_2 != -1
      && sosDIGISampleDone(DIGIHandle, SampleHandleCar_variable_2)) {
      frontendsample(0x8000);
      SampleHandleCar_variable_2 = -1;
    }
    if (switch_types) {
      game_type = switch_types - 1;
      if (switch_types == 1 && competitors == 1)
        competitors = 16;
      switch_types = 0;
      if (game_type == 1)
        Race = ((_BYTE)TrackLoad - 1) & 7;
      else
        network_champ_on = 0;
    }
    display_picture(scrbuf, front_vga[0], 2);
    display_block(head_y, 0);
    if (cup_won)
      display_block(388, 0);
    display_block(2, 0);
    display_block(247, 0);
    display_block(247, 0);
    display_block(257, -1);
    display_block(336, -1);
    if (v5 < 8)
      front_text(sel_posns[2 * v5], sel_posns_variable_1[2 * v5], 143, 0);
    front_text(sel_posns[0] + 132, sel_posns_variable_1[0] + 7, 143, 2);
    front_text(sel_posns_variable_2 + 132, sel_posns_variable_3 + 7, 143, 2);
    front_text(sel_posns_variable_4 + 132, sel_posns_variable_5 + 7, 143, 2);
    front_text(sel_posns_variable_6 + 132, sel_posns_variable_7 + 7, 143, 2);
    front_text(sel_posns_variable_8 + 132, sel_posns_variable_9 + 7, 143, 2);
    front_text(sel_posns_variable_10 + 132, sel_posns_variable_11 + 7, 143, 2);
    front_text(sel_posns_variable_12 + 132, sel_posns_variable_13 + 7, 143, 2);
    front_text(sel_posns_variable_14 + 132, sel_posns_variable_15 + 7, 143, 2);
    v30 = (TrackLoad - 1 - (__CFSHL__((TrackLoad - 1) >> 31, 3) + 8 * ((TrackLoad - 1) >> 31))) >> 3;
    if (TrackLoad >= 0) {
      if (v4)
        show_3dmap(v34, 1280, v32);
      else
        show_3dmap(*((float *)&v27 + 1), 1280, v32);
      if (game_type >= 2) {
        NoOfLaps = 5;
      } else {
        v7 = cur_laps[level];
        NoOfLaps = v7;
        if (competitors == 2)
          NoOfLaps = v7 / 2;
      }
      sprintf(&buffer, "%s: %i", language_buffer_variable_71, NoOfLaps);
      front_text(420, 16, 143, 1);
      v8 = front_text(420, 34, 143, 1);
      if (RecordCars[TrackLoad] < 0) {
        sprintf(&buffer, "%s", &RecordNames[9 * TrackLoad]);
      } else {
        v9 = RecordLaps[TrackLoad] * frontend_c_variable_56;
        _CHP(TrackLoad, HIDWORD(v8));
        LODWORD(v10) = (int)v9;
        HIDWORD(v10) = (int)v9 >> 31;
        v11 = v10 / 6000;
        LODWORD(v10) = (int)v9;
        v12 = (int)(v10 / 100) % 60;
        LODWORD(v10) = (int)v9;
        LODWORD(v27) = v10 % 100;
        sprintf(
          &buffer,
          "%s - %s - %02i:%02i:%02i",
          &RecordNames[9 * TrackLoad],
          &CompanyNames[20 * (RecordCars[TrackLoad] & 0xF)],
          v11,
          v12,
          (_DWORD)v27);
      }
      front_text(420, 52, 143, 1);
    }
    display_block(300, 0);
    if (TrackLoad <= 0) {
      v14 = &font2_ascii;
      v13 = (int)&font2_offsets;
      v15 = front_text(190, 350, 143, 0);
    } else {
      v13 = 190;
      if (TrackLoad >= 17)
        v14 = (void *)(TrackLoad - 17);
      else
        v14 = (void *)(TrackLoad - 1);
      v15 = display_block(356, 0);
    }
    show_received_mesage(v15, HIDWORD(v15), v14, v13);
    copypic((char *)scrbuf, (int)screen);
    if (switch_same > 0) {
      v19 = 0;
      if (players > 0) {
        v20 = 0;
        do {
          ++v20;
          ++v19;
          infinite_laps[v20] = switch_same - 666;
        } while (v19 < players);
      }
      v13 = cheat_mode;
      BYTE1(v13) = BYTE1(cheat_mode) | 0x40;
      cheat_mode = v13;
    } else if (switch_same < 0) {
      v16 = 0;
      switch_same = 0;
      if (players > 0) {
        v17 = 0;
        do {
          ++v17;
          ++v16;
          infinite_laps[v17] = -1;
        } while (v16 < players);
      }
      v18 = cheat_mode;
      BYTE1(v18) = BYTE1(cheat_mode) & 0xBF;
      cheat_mode = v18;
    }
    if (!v4) {
      v21 = (double)v29 * v28 + *((float *)&v27 + 1);
      *((float *)&v27 + 1) = v21;
      if (v21 <= frontend_c_variable_57) {
        if (*((float *)&v27 + 1) < (double)v34) {
          *((float *)&v27 + 1) = v34;
          v4 = 72;
          HIBYTE(v28) ^= 0x80u;
        }
      } else {
        HIDWORD(v27) = 1259902592;
        if (v6 == TrackLoad)
          v33 = -1;
        TrackLoad = v6;
        if (frontendspeechptr)
          fre(&frontendspeechptr);
        if (TrackLoad >= 0)
          loadtrack(TrackLoad, -1);
        loadtracksample(TrackLoad);
        v34 = cur_TrackZ;
        v31 = -1;
        v28 = (cur_TrackZ + frontend_c_variable_54) * frontend_c_variable_55;
        if (v33 != -1) {
          broadcast_mode = -1;
          while (broadcast_mode)
            ;
        }
        v13 = -1;
        v33 = -1;
        frames = 0;
      }
    }
    if (!front_fade) {
      loadtracksample(TrackLoad);
      front_fade = -1;
      fade_palette(32, 0, -1, v13);
      frontendsample(0x8000);
      frames = 0;
    }
    if (TrackLoad != v33) {
      if (!v31)
        sfxsample(v27);
      v31 = 0;
      v6 = TrackLoad;
      v4 = 0;
    }
    v35 = 8 * v30;
    v36 = v5 + 1;
    v22 = 0;
    v38 = 8 * v30 + v5 + 1;
    while (fatkbhit()) {
      v23 = fatgetch();
      if (v23 < 0xDu) {
        if (!v23) {
          v24 = fatgetch();
          if (v24 >= 0x48u) {
            if (v24 <= 0x48u) {
              v22 = 2;
            } else if (v24 == 80) {
              v22 = 1;
            }
          }
        }
      } else if (v23 <= 0xDu) {
        if (v5 != 8 && v6 != v38 || v5 == 8) {
          remove_frontendspeech();
          sfxsample(v27);
        }
        if (v6 == v38 && SoundCard && frontendspeechhandle != -1 && sosDIGISampleDone(DIGIHandle, frontendspeechhandle)) {
          frontendspeechhandle = -1;
          frontendsample(0x8000);
        }
        if (v5 == 8) {
          v37 = -1;
        } else if (game_type != 1 && v6 != v35 + v36) {
          sfxsample(v27);
          v6 = v35 + v36;
          if (v4) {
            v4 = 0;
          } else if (v28 < 0.0) {
            HIBYTE(v28) ^= 0x80u;
          }
        }
      } else if (v23 >= 0x1Bu) {
        if (v23 <= 0x1Bu) {
          remove_frontendspeech();
          sfxsample(v27);
          v37 = -1;
        } else if (v23 == 32 && game_type != 1 && TrackLoad > 0) {
          v6 += 8;
          sfxsample(v27);
          if (v6 > 8 && v6 < 17 && (cup_won & 1) == 0)
            v6 += 8;
          if (v6 > 16 && v6 < 25 && (cup_won & 2) == 0)
            v6 += 8;
          if (v6 > 24)
            v6 -= 24;
          if (v4) {
            v4 = 0;
          } else if (v28 < 0.0) {
            HIBYTE(v28) ^= 0x80u;
          }
        }
      }
    }
    if (v22) {
      if (v22 > 1) {
        if (game_type != 1 && --v5 < 0)
          v5 = 0;
      } else if (game_type != 1 && ++v5 > 8) {
        v5 = 8;
      }
    }
    v25 = v32;
    v32 = ((_WORD)v32 + 32 * (_WORD)v29) & 0x3FFF;
  } while (!v37);
  fade_palette(0, v25, v37, v22);
  front_fade = 0;
  fre(&front_vga_variable_3);
  fre(&front_vga_variable_8);
  fre(&front_vga_variable_9);
  result = (_DWORD *)load_picture(&aCarnamesBm[3]);
  front_vga_variable_3 = (int)result;
  if (frontendspeechptr)
    return fre(&frontendspeechptr);
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void save_params()
{
  p_tex_size = gfx_size;
}

//-------------------------------------------------------------------------------------------------

void reset_params()
{
  gfx_size = p_tex_size;
}

//-------------------------------------------------------------------------------------------------

int NetworkWait()
{
  return 0;
  /*
  int v4; // ebx
  int v5; // eax
  __int64 picture; // rax
  int v7; // esi
  int v8; // eax
  int v9; // eax
  int v10; // esi
  int v11; // eax
  __int64 v12; // rax
  int v13; // ebp
  int v14; // esi
  int v15; // edi
  int v16; // ecx
  int v17; // ebx
  unsigned int v18; // eax
  int result; // eax
  int v20; // [esp+0h] [ebp-2Ch]
  int v21; // [esp+8h] [ebp-24h]
  const char *v22; // [esp+Ch] [ebp-20h]
  int v23; // [esp+10h] [ebp-1Ch]

  v4 = -1;
  v20 = scr_size;
  front_fade = 0;
  tick_on = -1;
  frontend_on = -1;
  v5 = clear_network_game(scr_size);
  netCD = 0;
  cd_error = 0;
  SVGA_ON = -1;
  network_test = 1;
  init_screen(v5, 0, -1);
  front_vga[0] = load_picture(aResultBm);
  front_vga_variable_1 = load_picture(&aFont2Bm[1]);
  front_vga_variable_2 = load_picture(&aLcsmallcarBm[2]);
  front_vga_variable_3 = load_picture(aTabtextBm);
  picture = load_picture(&aZfont1Bm[1]);
  front_vga_variable_10 = picture;
  v21 = -1;
  LODWORD(picture) = setpal((int)&aIresultPal[1], SHIDWORD(picture), (_WORD *)0xFFFFFFFF, (_BYTE *)a4);
  if (network_on) {
    while (1) {
      if (!v21)
        goto LABEL_85;
      if (switch_types) {
        LODWORD(picture) = switch_types - 1;
        game_type = switch_types - 1;
        if (switch_types == 1 && competitors == 1)
          competitors = 16;
        switch_types = 0;
        v4 = game_type;
        if (game_type == 1) {
          LODWORD(picture) = ((_BYTE)TrackLoad - 1) & 7;
          Race = picture;
        } else {
          network_champ_on = 0;
        }
      }
      if (switch_same <= 0)
        break;
      v10 = 0;
      if (players > 0) {
        v11 = 0;
        do {
          ++v11;
          ++v10;
          infinite_laps[v11] = switch_same - 666;
        } while (v10 < players);
      }
      v4 = cheat_mode;
      BYTE1(v4) = BYTE1(cheat_mode) | 0x40;
      cheat_mode = v4;
      LODWORD(picture) = (__int16)player1_car;
      if (Players_Cars[(__int16)player1_car] < 0) {
        StartPressed = 0;
        time_to_start = 0;
        broadcast_mode = -670;
        while (broadcast_mode)
          ;
        v4 = 0;
        v21 = 0;
      LABEL_25:
        --players_waiting;
      }
    LABEL_26:
      check_cars(picture);
      display_picture(scrbuf, front_vga[0], v4);
      sprintf(&buffer, "%s: %i", language_buffer_variable_1, players);
      front_text(16, 4, 143, 0);
      sprintf(&buffer, "%s: %i", language_buffer_variable_4, TrackLoad);
      front_text(16, 24, 143, 0);
      if (game_type) {
        if ((unsigned int)game_type <= 1) {
          sprintf(&buffer, "%s", language_buffer_variable_55);
        } else if (game_type == 2) {
          sprintf(&buffer, "%s", language_buffer_variable_58);
        }
      } else {
        sprintf(&buffer, "%s", language_buffer_variable_57);
      }
      v4 = (int)&font2_ascii;
      a4 = (int)&font2_offsets;
      v12 = front_text(200, 4, 143, 1);
      LODWORD(v12) = players_waiting;
      if (players_waiting == network_on) {
        LODWORD(v12) = frames & 0xF;
        if ((unsigned int)v12 < 8) {
          v4 = (int)&font2_ascii;
          a4 = (int)&font2_offsets;
          v12 = front_text(200, 22, 143, 1);
        }
        if (time_to_start)
          v21 = 0;
      }
      v13 = 0;
      if (players > 0) {
        v14 = 0;
        v23 = 44;
        v22 = player_names;
        v15 = 49;
        do {
          if (player_started[v14] && (!v13 && (frames & 0xFu) < 8 || v13 > 0))
            display_block(v23, 0);
          sprintf(&buffer, "%i", v13 + 1);
          front_text(33, v15, 143, 0);
          sprintf(&buffer, "%s", v22);
          front_text(85, v15, 143, 0);
          v16 = Players_Cars[v14];
          if (v16 >= 0) {
            sprintf(&buffer, "%s", &CompanyNames[20 * v16]);
            front_text(218, v15, 143, 0);
            v17 = Players_Cars[v14];
            if (v17 < 8) {
              a4 = 165;
              if (((unsigned int)cstart_branch_1 & textures_off) != 0)
                v4 = smallcars_variable_1[v17];
              else
                v4 = smallcars[v17];
              display_block(22 * v13 + 46, 0);
            } else {
              v4 = (int)&font2_ascii;
              a4 = (int)&font2_offsets;
              front_text(165, v15, 143, 0);
            }
          } else {
            v4 = (int)&font2_ascii;
            a4 = (int)&font2_offsets;
            front_text(218, v15, 143, 0);
          }
          ++v14;
          v15 += 22;
          ++v13;
          LODWORD(v12) = v23 + 22;
          HIDWORD(v12) = v22 + 9;
          v23 += 22;
          v22 += 9;
        } while (v13 < players);
      }
      if (time_to_start)
        v21 = 0;
      if (v21) {
        show_received_mesage(v12, HIDWORD(v12), v4, a4);
        copypic((char *)scrbuf, (int)screen);
        if (!front_fade) {
          front_fade = -1;
          fade_palette(32, -668, v4, a4);
          broadcast_mode = -668;
          while (broadcast_mode)
            ;
          broadcast_mode = -668;
          while (broadcast_mode)
            ;
          frames = 0;
        }
      }
      HIDWORD(picture) = 0;
      while (1) {
        LODWORD(picture) = fatkbhit();
        if (!(_DWORD)picture)
          break;
        v18 = fatgetch();
        if (v18 < 0xD) {
          if (!v18)
            fatgetch();
        } else if (v18 <= 0xD) {
          if (players_waiting == network_on && !time_to_start) {
            v4 = -671;
            v21 = 0;
            broadcast_mode = -671;
            while (broadcast_mode)
              ;
            broadcast_mode = -671;
            while (broadcast_mode)
              ;
            broadcast_mode = -671;
            while (broadcast_mode)
              ;
            time_to_start = -1;
          }
        } else if (v18 == 27) {
          v4 = time_to_start;
          if (!time_to_start) {
            a4 = restart_net;
            if (!restart_net) {
              StartPressed = 0;
              time_to_start = 0;
              broadcast_mode = -670;
              while (broadcast_mode)
                ;
              v21 = 0;
              --players_waiting;
              no_clear = -1;
            }
          }
        }
      }
    }
    if (switch_same >= 0)
      goto LABEL_26;
    v7 = 0;
    if (players > 0) {
      v8 = 0;
      do {
        ++v8;
        ++v7;
        infinite_laps[v8] = -1;
      } while (v7 < players);
    }
    v9 = cheat_mode;
    BYTE1(v9) = BYTE1(cheat_mode) & 0xBF;
    cheat_mode = v9;
    switch_same = 0;
    StartPressed = 0;
    time_to_start = 0;
    broadcast_mode = -670;
    while (broadcast_mode)
      ;
    LODWORD(picture) = 0;
    v21 = 0;
    goto LABEL_25;
  }
LABEL_85:
  LODWORD(picture) = ticks + 18;
  if (ticks + 18 > ticks) {
    while ((int)picture > ticks)
      ;
  }
  if (time_to_start) {
    broadcast_mode = -314;
    while (broadcast_mode)
      ;
    LODWORD(picture) = wConsoleNode;
    if (wConsoleNode == master) {
      do
        LODWORD(picture) = received_records;
      while (received_records < network_on);
      broadcast_mode = -2718;
      while (broadcast_mode)
        ;
    } else {
      while (!received_seed)
        ;
    }
  }
  check_cars(picture);
  fade_palette(0, SHIDWORD(picture), v4, a4);
  front_fade = 0;
  fre(front_vga);
  fre(&front_vga_variable_1);
  fre(&front_vga_variable_2);
  fre(&front_vga_variable_3);
  fre(&front_vga_variable_10);
  result = v20;
  scr_size = v20;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void loadcheatnames()
{
  char buffer[0x400]; // Temporary buffer for file contents
  FILE *fp;
  int iSize;
  char *szTok;
  int iCheatIdx = 0;

  // Try to open PASSWORD.INI to get its size
  iSize = ROLLERfilelength("PASSWORD.INI");

  fp = ROLLERfopen("PASSWORD.INI", "rb");
  if (!fp)
    return;

  // Read file into buffer
  fread(buffer, iSize, 1, fp);
  fclose(fp);

  // Decode the read contents
  decode((uint8 *)buffer, iSize, 23, 37);

  // Tokenize buffer and load cheat names
  szTok = strtok(buffer, "\n\t\r");

  while (szTok) {
    // Check for end marker string
    if (strcmp(szTok, "#") == 0)
      break;

    // Copy token into cheat_names[iCheatIdx]
    strncpy(cheat_names[iCheatIdx], szTok, 9);

    iCheatIdx++;
    szTok = strtok(NULL, "\n\t\r");
  }

  // Set final cheat name entry to end marker
  cheat_names[iCheatIdx][0] = '#';
  cheat_names[iCheatIdx][1] = '\0';

  // Wipe the buffer
  memset(buffer, 0, 0x57);

  // Perform another decode on cheat_names
  decode((uint8 *)cheat_names, 288, 43, 87);
}

//-------------------------------------------------------------------------------------------------

int CheckNames(char *szPlayerName, int iPlayerIdx)
{
  int iCheatIdx = 0;

  // Decode cheat names list
  decode((uint8*)cheat_names, 288, 43, 87);

  // Skip processing if cheat list is empty
  if (cheat_names[0][0] == '#') {
    // Re-encode cheat names
    decode((uint8*)cheat_names, 288, 43, 87);
    return 0;
  }

  char *szCurrCheat = (char *)cheat_names;

  // Process all cheat names until terminator '#'
  while (*szCurrCheat != '#') {
      // Check if player name matches current cheat name
    if (name_cmp(szPlayerName, szCurrCheat) == 0) {
      // Handle cheats
      if (iCheatIdx <= 25) {
        switch (iCheatIdx) {
          case 0: //SUICYCO (cheat car, explode opponent)
            Players_Cars[iPlayerIdx] = 8;
            name_copy(szPlayerName, "DAMIAN");
            cheat_mode |= CHEAT_MODE_CHEAT_CAR;
            break;
          case 1: //MAYTE (cheat car, top speed)
            Players_Cars[iPlayerIdx] = 9;
            name_copy(szPlayerName, "DAMON");
            cheat_mode |= CHEAT_MODE_CHEAT_CAR;
            break;
          case 2: //2X4B523P (cheat car, flip opponent)
            Players_Cars[iPlayerIdx] = 10;
            name_copy(szPlayerName, "GRAHAM");
            cheat_mode |= CHEAT_MODE_CHEAT_CAR;
            break;
          case 3: //TINKLE (cheat car, jump opponent)
            Players_Cars[iPlayerIdx] = 11;
            name_copy(szPlayerName, "KEV");
            cheat_mode |= CHEAT_MODE_CHEAT_CAR;
            break;
          case 4: //LOVEBUN (formula car)
            Players_Cars[iPlayerIdx] = 12;
            name_copy(szPlayerName, "LISA");
            cheat_mode |= CHEAT_MODE_CHEAT_CAR;
            break;
          case 5: //DR DEATH (death mode)
            name_copy(szPlayerName, "PAT");
            cheat_mode |= CHEAT_MODE_DEATH_MODE;
            break;
          case 6: //SUPERMAN (invincible human car)
            name_copy(szPlayerName, "MARK");
            cheat_mode |= CHEAT_MODE_INVINCIBLE;
            player_invul[iPlayerIdx] = -1;
            break;
          case 7: //REMOVE
            name_copy(szPlayerName, "MRBRUSH");
            if (cheat_mode & CHEAT_MODE_CLONES) {
              // Handle player cars and infinite laps
              short nPlayer1Car = (short)player1_car;
              if ((short)nPlayer1Car == iPlayerIdx) {
                for (int i = 0; i < players; i++) {
                  infinite_laps = -1;
                }
              } else {
                for (int i = 0; i < players; i++) {
                  if (i != (int)nPlayer1Car) {
                    Players_Cars[i] = -1;
                  }
                }
              }
              switch_same = -1;
            }
            if (cheat_mode & CHEAT_MODE_50HZ_TIMER) {
              release_ticktimer();
              claim_ticktimer(36);
            }
            cheat_mode = 0;
            player_invul[iPlayerIdx] = 0;
            CalcCarSizes();
            break;
          case 8: //TOPTUNES (alternate voice)
            name_copy(szPlayerName, "DJ SFX");
            cheat_samples = -1;
            releasesamples();
            loadfatalsample();
            break;
          case 9: //GOLDBOY (unlock premier cup)
            name_copy(szPlayerName, "PHIL");
            cup_won |= 1;
            textures_off |= 0x1000;
            break;
          case 10: //CUP WON (view end sequence)
            name_copy(szPlayerName, "LAZY");
            cheat_mode |= CHEAT_MODE_END_SEQUENCE;
            break;
          case 11: //I WON (view race history)
            name_copy(szPlayerName, "IDOL");
            cheat_mode |= CHEAT_MODE_RACE_HISTORY;
            break;
          case 12: //CINEMA (widescreen)
            name_copy(szPlayerName, "LUMIERE");
            cheat_mode |= CHEAT_MODE_WIDESCREEN;
            break;
          case 13: //ROLL EM (view credits)
            name_copy(szPlayerName, "MR CRED");
            cheat_mode |= CHEAT_MODE_CREDITS;
            break;
          case 14: //FORMULA1 (advanced car set)
            name_copy(szPlayerName, "NEIL");
            cheat_mode |= CHEAT_MODE_ADVANCED_CARS;
            break;
          case 15: //MREPRISE (bonus cup unlocked)
            name_copy(szPlayerName, "MRBONUS");
            textures_off |= 0x20000;
            cup_won |= 2;
            break;
          case 16: //DUEL (killer opponents)
            name_copy(szPlayerName, "MRREVIL");
            cheat_mode |= CHEAT_MODE_KILLER_OPPONENTS;
            break;
          case 17: //PROCESS
            if ((double)(1247486966.0f / 1245708284.0f) * 3145727.0 == 1247486966.0f) {
              name_copy(szPlayerName, "TYPE B");
            } else {
              name_copy(szPlayerName, "TYPE A");
            }
            break;
          case 18: //MRFROSTY (icy roads)
            name_copy(szPlayerName, "SNOWMAN");
            cheat_mode |= CHEAT_MODE_ICY_ROAD;
            break;
          case 19: //MR ZOOM (50Hz timer)
            name_copy(szPlayerName, "SPEEDY");
            cheat_mode |= CHEAT_MODE_50HZ_TIMER;
            release_ticktimer();
            claim_ticktimer(50);
            break;
          case 20: //TACHYONS (100Hz timer)
            name_copy(szPlayerName, "NUCLEAR!");
            cheat_mode |= CHEAT_MODE_100HZ_TIMER | CHEAT_MODE_50HZ_TIMER;
            release_ticktimer();
            claim_ticktimer(100);
            break;
          case 21: //YOTARACE (double track size)
            name_copy(szPlayerName, "GULLIVER");
            cheat_mode |= CHEAT_MODE_DOUBLE_TRACK;
            break;
          case 22: //CLONES
            //removed?
            //cheat_mode |= CHEAT_MODE_CLONES
            break;
          case 23: //TINYTOTS (tiny cars)
            name_copy(szPlayerName, "TINYTIM");
            cheat_mode |= CHEAT_MODE_TINY_CARS;
            CalcCarSizes();
            break;
          case 24: //WARPGATE (warp)
            name_copy(szPlayerName, "HEADACHE");
            cheat_mode |= CHEAT_MODE_WARP;
            break;
          case 25: //FREAKY (invert colors)
            name_copy(szPlayerName, "PAINTER");
            cheat_mode |= CHEAT_MODE_BONUS_UNLOCKED;
            break;
          default:
            break;
        }
      }
    }
    // Handle empty player name
    else if (*szPlayerName == '\0') {
      name_copy(szPlayerName, "MR DULL");
      if (iPlayerIdx == 0) {
        cheat_mode |= CHEAT_MODE_GRAYSCALE;
      }
      break;
    }

    // Move to next cheat name
    szCurrCheat += 9;
    iCheatIdx++;
  }
  // Re-encode cheat names
  decode((uint8*)cheat_names, 288, 43, 87);

  return 0;
}

//-------------------------------------------------------------------------------------------------

void restart_net_game()
{
  /*
  int v1; // eax
  int v2; // eax
  int v3; // edi
  int v4; // edx
  int i; // ecx
  int j; // eax
  int v7; // esi
  int v8; // edx
  int v9; // ecx
  int k; // eax
  int m; // eax
  int v12; // eax
  int n; // ebx
  int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // ebp
  int ii; // esi
  int v19; // edx
  int v20; // ebx
  int jj; // eax
  int kk; // eax
  int v23; // ecx
  int v24; // edx
  int result; // eax
  int v26; // [esp+4h] [ebp-1Ch]

  SVGA_ON = -1;
  init_screen(a1, -1, 0);
  winx = 0;
  winy = 0;
  winw = XMAX;
  mirror = 0;
  winh = YMAX;
  frontend_on = -1;
  time_to_start = 0;
  StartPressed = 0;
  tick_on = -1;
  load_language_file((int)&aSelectEng[1], 0);
  load_language_file((int)&aPconfigEng[1], 1);
  remove_messages(-1, 1, 0);
  v1 = reset_network(0);
  broadcast_mode = -667;
  while (broadcast_mode)
    ;
  no_clear = 0;
  if (!quit_game && !intro) {
    v2 = check_cars(v1);
    v1 = NetworkWait(v2, 0, 0, -1);
  }
  if (replaytype != 2 && !quit_game)
    AllocateCars(v1);
  Race = ((_BYTE)TrackLoad - 1) & 7;
  if (game_type == 1 && !Race) {
    memset(championship_points, 0, sizeof(championship_points));
    memset(team_points, 0, 64);
    memset(total_kills, 0, 64);
    memset(total_fasts, 0, 64);
    memset(total_wins, 0, 64);
    memset(team_kills, 0, 64);
    memset(team_fasts, 0, sizeof(team_fasts));
    memset(team_wins, 0, 64);
  }
  v3 = competitors;
  if (competitors == 2) {
    v3 = players;
    if (players < 2)
      v3 = competitors;
  }
  if (competitors == 1)
    v3 = players;
  v4 = 0;
  if (v3 > 0) {
    for (i = 0; i < v3; ++i) {
      for (j = v4; non_competitors[j]; ++j)
        ++v4;
      grid[i] = v4++;
    }
  }
  v7 = v3;
  v8 = 0;
  if (v3 < numcars) {
    v9 = 4 * v3;
    v26 = 4 * numcars;
    do {
      for (k = v8; !non_competitors[k]; ++k)
        ++v8;
      ++v7;
      grid[v9 / 4u] = v8;
      v9 += 4;
      ++v8;
    } while (v9 < v26);
  }
  if (game_type == 1 && Race > 0) {
    if (v3 > 0) {
      for (m = 0; m < v3; finished_car_variable_1[m] = teamorder_variable_1[m])
        ++m;
    }
  } else {
    racers = v3;
    v12 = 6 * v3;
    for (n = 0; n < 6 * v3; grid[v12] = v17) {
      v14 = rand(v12);
      v15 = (v3 * v14 - (__CFSHL__((v3 * v14) >> 31, 15) + ((v3 * v14) >> 31 << 15))) >> 15;
      v16 = rand(v15);
      v12 = (v3 * v16 - (__CFSHL__((v3 * v16) >> 31, 15) + ((v3 * v16) >> 31 << 15))) >> 15;
      v17 = grid[v15];
      grid[v15] = grid[v12];
      ++n;
    }
    v3 = racers;
    for (ii = 0; ii < players; ++ii) {
      if (level && (cheat_mode & 2) == 0)
        v19 = v3 - 2 * level * players;
      else
        v19 = v3 - players;
      if (v19 < 0)
        v19 = 0;
      v20 = 0;
      for (jj = 0; !human_control[grid[jj]]; ++jj)
        ++v20;
      if (v20 < v19) {
        for (kk = v19; ; ++kk) {
          v23 = grid[kk];
          if (!human_control[v23])
            break;
          ++v19;
        }
        v24 = grid[v20];
        grid[v20] = v23;
        grid[kk] = v24;
      }
    }
  }
  result = 0;
  StartPressed = 0;
  restart_net = 0;
  racers = v3;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

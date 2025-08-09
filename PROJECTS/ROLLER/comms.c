#include "comms.h"
#include "sound.h"
#include "frontend.h"
#include "func2.h"
#include "3d.h"
//-------------------------------------------------------------------------------------------------

int serial_port = 2;    //000AFD98
int modem_port = 2;     //000AFD9C
int modem_baud = 19200; //000AFDA0
int no_16550 = 0;       //000AFDA4
int current_modem = 0;  //000AFDA8
char modem_initstring[51] = "ATX"; //000AFDAC
char modem_phone[53] = { 0 }; //000AFDDF
int modem_tone = -1;    //000AFE14
int modem_call = -1;    //000AFE18
char *modembuffer;      //001A2BA4

//-------------------------------------------------------------------------------------------------
//00075DC0
int select_comport(int iIconIdx)
{                                               // BIOS interrupt 11h - Equipment determination (detect available COM ports)
  unsigned int uiKey; // esi
  int iAvailableComPorts; // edi
  char byCom1Color; // al
  char byCom2Color; // al
  char byCom3Color; // al
  char byCom4Color; // al
  unsigned int uiTempKey; // eax
  unsigned int uiExtendedKey; // eax
  int iExitFlag; // [esp+4h] [ebp-4h]

  //__asm { int     11h; BIOS interrupt 11h - Equipment determination(detect available COM ports) }
  iExitFlag = 0;                                // Initialize exit flag (0 = continue loop, -1 = exit)

  //Set this to 4 for modern systems to always show 4 comm ports
  iAvailableComPorts = 4;// ((int)(unsigned __int16)iIconIdx >> 9) & 7;// Extract COM port count from BIOS equipment word (AX bits 9-11) - DECOMPILER ERROR: uses AX from INT 11h, not parameter a1

  if ((unsigned int)iAvailableComPorts < 2)   // Ensure minimum of 2 COM ports are available
    iAvailableComPorts = 2;
  if (iAvailableComPorts < serial_port)       // Validate current serial port selection against available ports
    serial_port = 2;
  check16550(serial_port);                      // Test 16550 UART availability on selected serial port
  //gssCommsSetComBaudRate(9600);                 // Set communication baud rate to 9600 bps
  do {
    display_picture(scrbuf, front_vga[0]);      // Display main background picture
    display_block(scrbuf, front_vga[1], 3, head_x, head_y, 0);
    display_block(scrbuf, front_vga[6], 0, 36, 2, 0);// Display UI element at position (36, 2)
    display_block(scrbuf, front_vga[5], iIconIdx, -4, 247, 0);// Display gear selection indicator at bottom left
    display_block(scrbuf, front_vga[5], game_type + 5, 135, 247, 0);// Display game type indicator (5 + game_type offset)
    display_block(scrbuf, front_vga[4], 4, 76, 257, -1);// Display UI element at position (76, 257) with special color
    display_block(scrbuf, front_vga[6], 4, 62, 336, -1);// Display UI element at position (62, 336) with special color
    scale_text(front_vga[15], &language_buffer[5312], font1_ascii, font1_offsets, 400, 75, 143, 1u, 200, 640);// Display main menu title text
    scale_text(front_vga[15], &language_buffer[3008], font1_ascii, font1_offsets, 400, 93, 143, 1u, 200, 640);// Display COM port selection instructions
    if (serial_port == 1)                     // Set color for COM 1 text (highlighted if selected)
      byCom1Color = 0xAB;
    else
      byCom1Color = 0x8F;
    scale_text(front_vga[15], "COM 1", font1_ascii, font1_offsets, 400, 135, byCom1Color, 1u, 200, 640);// Display 'COM 1' option text
    if (serial_port == 2)                     // Set color for COM 2 text (highlighted if selected)
      byCom2Color = 0xAB;
    else
      byCom2Color = 0x8F;
    scale_text(front_vga[15], "COM 2", font1_ascii, font1_offsets, 400, 153, byCom2Color, 1u, 200, 640);// Display 'COM 2' option text
    if (iAvailableComPorts >= 3)              // Check if 3 or more COM ports are available
    {                                           // Set color for COM 3 text (highlighted if selected)
      if (serial_port == 3)
        byCom3Color = 0xAB;
      else
        byCom3Color = 0x8F;
      scale_text(front_vga[15], "COM 3", font1_ascii, font1_offsets, 400, 171, byCom3Color, 1u, 200, 640);// Display 'COM 3' option text (if available)
    }
    if (iAvailableComPorts >= 4)              // Check if 4 or more COM ports are available
    {                                           // Set color for COM 4 text (highlighted if selected)
      if (serial_port == 4)
        byCom4Color = 0xAB;
      else
        byCom4Color = 0x8F;
      scale_text(front_vga[15], "COM 4", font1_ascii, font1_offsets, 400, 189, byCom4Color, 1u, 200, 640);// Display 'COM 4' option text (if available)
    }
    if (no_16550)                             // Check if 16550 UART error occurred
      scale_text(front_vga[15], &language_buffer[6976], font1_ascii, font1_offsets, 400, 351, 231, 1u, 200, 640);// Display 16550 error message at bottom of screen
    copypic(scrbuf, screen);                    // Copy completed frame buffer to screen
    while (fatkbhit())                        // Process all pending keyboard input
    {
      uiTempKey = fatgetch();                   // Get next character from keyboard buffer
      uiKey = uiTempKey;
      if (uiTempKey < 0xD)                    // Check if key code is less than 13 (Enter key)
      {                                         // Check for extended key code (0 = function/arrow keys)
        if (!uiTempKey) {
          uiExtendedKey = fatgetch();           // Get extended key code (second byte)
          uiKey = uiExtendedKey;
          if (uiExtendedKey >= 0x48)          // Check if key code is 0x48 or higher (Up arrow = 0x48)
          {                                     // Check for Up arrow key (0x48)
            if (uiExtendedKey <= 0x48) {                                   // Move to previous COM port (minimum COM 1)
              if (serial_port != 1)
                --serial_port;
            LABEL_38:
              check16550(serial_port);          // Test 16550 UART on newly selected COM port
            } else if (uiExtendedKey == 0x50)   // Check for Down arrow key (0x50)
            {                                   // Move to next COM port (maximum available ports)
              if (iAvailableComPorts != serial_port)
                ++serial_port;
              goto LABEL_38;
            }
          }
        }
      } else if (uiTempKey <= 0xD || uiTempKey == 0x1B)// Check for Enter (13) or Escape (27) keys
      {
        iExitFlag = -1;                         // Set exit flag to exit menu loop
      }
    }
  } while (!iExitFlag);                         // Continue loop until user presses Enter or Escape
  //TODO
  //gssCommsSetComPort(serial_port);              // Configure communications system with selected COM port
  return (uiKey != 13) - 1;                     // Return 0 if Enter pressed, -1 if Escape pressed
}

//-------------------------------------------------------------------------------------------------
//00076180
int stringwidth(char *szString)
{
  int iStringWidth; // eax
  int iCharBlockIdx; // ebx

  iStringWidth = 0;
  while (*szString) {
    iCharBlockIdx = (uint8)font1_ascii[(uint8)*szString++];
    if (iCharBlockIdx == 255)
      iStringWidth += 8;
    else
      iStringWidth += front_vga[15][iCharBlockIdx].iWidth + 1;
  }
  return iStringWidth;
}

//-------------------------------------------------------------------------------------------------
//00076270
int select_modemstuff(int a1)
{
  return 0; /*
  bool v1; // ebp
  int v2; // eax
  int v3; // ebp
  char *v4; // edi
  char *v5; // esi
  int v6; // ebx
  __int64 v7; // rax
  int v8; // eax
  unsigned int v9; // kr08_4
  int v10; // ecx
  int v11; // eax
  __int16 v12; // fps
  double v13; // st7
  _BOOL1 v14; // c0
  char v15; // c2
  _BOOL1 v16; // c3
  __int16 v17; // fps
  double v18; // st7
  _BOOL1 v19; // c0
  char v20; // c2
  _BOOL1 v21; // c3
  _DWORD *v22; // eax
  __int64 v24; // rax
  int v25; // [esp+Ch] [ebp-3Ch]
  int v26; // [esp+10h] [ebp-38h]
  int v27; // [esp+14h] [ebp-34h]
  float v28; // [esp+18h] [ebp-30h]
  int v30; // [esp+20h] [ebp-28h]
  float v31; // [esp+24h] [ebp-24h]
  int v32; // [esp+28h] [ebp-20h]
  unsigned int v33; // [esp+2Ch] [ebp-1Ch]

  v30 = 0;
  v33 = 0;
  v26 = 0;
  v28 = 0.0;
  v31 = 0.0;
  v27 = 0;
  v32 = -1;
  v1 = modem_call == 0;
  LOWORD(v2) = loadmodemnames();
  v3 = v1 + 5;
  if (current_modem >= 0) {
    v2 = 51 * *(_DWORD *)(modembuffer + 56 * current_modem + 52);
    v4 = "ATX";
    v5 = (char *)(v2 + modembuffer2);
    do {
      LOBYTE(v2) = *v5;
      *v4 = *v5;
      if (!(_BYTE)v2)
        break;
      LOBYTE(v2) = v5[1];
      v5 += 2;
      v4[1] = v2;
      v4 += 2;
    } while ((_BYTE)v2);
  }
  __asm { int     11h; EQUIPMENT DETERMINATION }
  v25 = ((int)(unsigned __int16)v2 >> 9) & 7;
  if (modem_port < 2)
    v25 = 2;
  if (v25 < modem_port)
    modem_port = 2;
  check16550(modem_port);
  modem_baud = 19200;
  gssCommsSetComBaudRate(19200);
  do {
    v6 = v33;
    display_essentials(a1, v3, v33);
    if (v32 == 93 || v32 == 94 || v32 == 95 || v32 == 96 || v32 == 104) {
      if ((frames & 0xFu) < 8) {
        v6 = (int)font1_ascii;
        scale_text(400, 279, 143, 1, 200, 640);
      }
    } else if (v32 >= 0) {
      v6 = (int)font1_ascii;
      scale_text(400, 279, 231, 1, 200, 640);
    }
    HIDWORD(v7) = screen;
    copypic((char *)scrbuf, (int)screen);
    if (v30 && v30 + 72 < frames)
      v26 = -1;
    while (1) {
      LODWORD(v7) = fatkbhit();
      if (!(_DWORD)v7)
        break;
      LODWORD(v7) = fatgetch();
      v6 = v7;
      HIDWORD(v7) = v7;
      if (v33) {
        if (v33 <= 1) {
          if (v3 == 3)
            v6 = (int)"ATX";
          else
            v6 = (int)&modem_phone;
          v9 = strlen((const char *)v6) + 1;
          v10 = v9 - 1;
          if ((unsigned int)v7 < 8) {
            if (!(_DWORD)v7)
              goto LABEL_57;
          LABEL_63:
            if (keys_variable_3 || keys_variable_4) {
              switch ((int)v7) {
                case '#':
                  HIDWORD(v7) = 126;
                  break;
                case '\'':
                  HIDWORD(v7) = 64;
                  break;
                case ',':
                  HIDWORD(v7) = 60;
                  break;
                case '-':
                  HIDWORD(v7) = 95;
                  break;
                case '.':
                  HIDWORD(v7) = 62;
                  break;
                case '/':
                  HIDWORD(v7) = 63;
                  break;
                case '0':
                  HIDWORD(v7) = 41;
                  break;
                case '1':
                  HIDWORD(v7) = 33;
                  break;
                case '2':
                  HIDWORD(v7) = 34;
                  break;
                case '3':
                  HIDWORD(v7) = 156;
                  break;
                case '4':
                  HIDWORD(v7) = 36;
                  break;
                case '5':
                  HIDWORD(v7) = 37;
                  break;
                case '6':
                  HIDWORD(v7) = 94;
                  break;
                case '7':
                  HIDWORD(v7) = 38;
                  break;
                case '8':
                  HIDWORD(v7) = 42;
                  break;
                case '9':
                  HIDWORD(v7) = 40;
                  break;
                case ';':
                  HIDWORD(v7) = 58;
                  break;
                case '=':
                  HIDWORD(v7) = 43;
                  break;
                default:
                  break;
              }
            }
            if (strlen((const char *)v6) < 0x32 && HIDWORD(v7) != 127) {
              *(_BYTE *)(v9 + v6) = 0;
              *(_BYTE *)(v9 - 1 + v6) = BYTE4(v7);
              if (v3 == 3 && current_modem >= 0)
                current_modem = -current_modem - 1;
            }
          } else if ((unsigned int)v7 <= 8) {
            if (v10 > 0) {
              *(_BYTE *)(v6 + v10 - 1) = 0;
              if (v3 == 3 && current_modem >= 0)
                current_modem = -current_modem - 1;
            }
          } else {
            if ((unsigned int)v7 < 0xD || (unsigned int)v7 > 0xD && (_DWORD)v7 != 27)
              goto LABEL_63;
            v6 = -1;
            v33 = 0;
            v30 = 0;
            v32 = -1;
          }
        } else if ((_DWORD)v7) {
          if ((_DWORD)v7 == 27) {
            v33 = 0;
            v32 = -1;
            v30 = 0;
            v28 = 0.0;
            v31 = 0.0;
            v27 = 0;
            display_essentials(a1, v3, 0);
            v6 = (int)font1_ascii;
            scale_text(400, 279, 143, 1, 200, 640);
            HIDWORD(v7) = screen;
            LODWORD(v7) = copypic((char *)scrbuf, (int)screen);
            close_network(v7, SHIDWORD(v7), (int)font1_ascii);
          }
        } else {
        LABEL_57:
          fatgetch();
        }
      } else {
        v32 = -1;
        if ((unsigned int)v7 < 0xD) {
          if (!(_DWORD)v7) {
            LODWORD(v7) = fatgetch();
            HIDWORD(v7) = v7;
            if ((unsigned int)v7 >= 0x48) {
              if ((unsigned int)v7 <= 0x48) {
                if (v3)
                  --v3;
              } else if ((_DWORD)v7 == 80 && v3 < 6) {
                ++v3;
              }
            }
          }
        } else if ((unsigned int)v7 <= 0xD) {
          HIDWORD(v7) = v3;
          v6 = 0;
          display_essentials(a1, v3, 0);
          switch (v3) {
            case 0:
              select_modem(a1);
              break;
            case 1:
              v6 = modem_port + 1;
              modem_port = v6;
              if (v6 > v25)
                modem_port = 1;
              check16550(modem_port);
              break;
            case 2:
              modem_tone = modem_tone == 0;
              break;
            case 3:
            case 4:
              v33 = 1;
              break;
            case 5:
            case 6:
              v33 = 2;
              v32 = 104;
              v6 = (int)font1_ascii;
              modem_call = (v3 != 5) - 1;
              scale_text(400, 279, 143, 1, 200, 640);
              copypic((char *)scrbuf, (int)screen);
              gssCommsSetComPort(modem_port);
              v8 = Initialise_Network(0);
              v7 = gssModemHangUp(v8);
              v31 = (float)(unsigned int)clock(v7);
              break;
            default:
              continue;
          }
        } else if ((_DWORD)v7 == 27) {
          v26 = -1;
          v30 = 0;
          v28 = 0.0;
          v31 = 0.0;
          v27 = 0;
        }
      }
    }
    if (v33 == 2 && !v30) {
      LODWORD(v7) = gssModemCheckResponse();
      HIDWORD(v7) = v7;
      if ((int)v7 >= 0) {
        switch ((int)v7) {
          case 0:
            if ((LODWORD(v28) & 0x7FFFFFFF) != 0) {
              if (modem_call)
                gssModemDial(&modem_phone, modem_tone);
              HIDWORD(v7) = modem_call;
              v28 = 0.0;
              v6 = -1;
              LODWORD(v7) = (modem_call != 0) + 93;
              v27 = -1;
              v32 = v7;
            }
            if ((LODWORD(v31) & 0x7FFFFFFF) != 0) {
              v11 = gssModemInit("ATX", HIDWORD(v7));
              LODWORD(v7) = clock(v11);
              v31 = 0.0;
              v28 = (float)(unsigned int)v7;
            }
            break;
          case 1:
            v32 = 95;
            LODWORD(v7) = frames;
            v30 = frames;
            break;
          case 2:
            if (v27 && !modem_call) {
              v6 = 96;
              LODWORD(v7) = gssModemAnswer();
              v32 = 96;
            }
            break;
          case 3:
          case 4:
          case 5:
          case 6:
          case 7:
            v32 = v7 + 94;
            LODWORD(v7) = close_network(v7 + 94, v7, v6);
            v33 = 0;
            break;
          default:
            break;
        }
      }
    }
    if ((LODWORD(v28) & 0x7FFFFFFF) != 0) {
      LODWORD(v7) = clock(v7);
      v6 = 0;
      v13 = ((double)(unsigned int)v7 - v28) * comms_c_variable_5;
      v14 = v13 < comms_c_variable_6;
      v15 = 0;
      v16 = v13 == comms_c_variable_6;
      LOWORD(v7) = v12;
      if (v13 > comms_c_variable_6) {
        LODWORD(v7) = close_network(v7, SHIDWORD(v7), 0);
        v28 = 0.0;
        v31 = 0.0;
        v27 = 0;
        v33 = 0;
        v32 = 105;
      }
    }
    if ((LODWORD(v31) & 0x7FFFFFFF) != 0) {
      LODWORD(v7) = clock(v7);
      v18 = ((double)(unsigned int)v7 - v31) * comms_c_variable_5;
      v19 = v18 < comms_c_variable_6;
      v20 = 0;
      v21 = v18 == comms_c_variable_6;
      LOWORD(v7) = v17;
      if (v18 > comms_c_variable_6) {
        close_network(v7, SHIDWORD(v7), v6);
        v28 = 0.0;
        v31 = 0.0;
        v27 = 0;
        v33 = 0;
        v32 = 105;
      }
    }
  } while (!v26);
  fre(&modembuffer);
  v22 = fre(&modembuffer2);
  if (v30)
    return -1;
  v24 = gssModemHangUp(v22);
  close_network(v24, SHIDWORD(v24), v6);
  return 0;*/
}

//-------------------------------------------------------------------------------------------------
//000769D0
int loadmodemnames()
{
  return 0; /*
  int v0; // ecx
  int v1; // eax
  int v2; // ebp
  int v3; // eax
  char *v4; // esi
  char *v5; // edi
  char v6; // al
  char v7; // al
  int v8; // ecx
  int v9; // eax
  int v10; // ebp
  int v11; // eax
  int v12; // edx
  char *v13; // esi
  char *v14; // edi
  char v15; // al
  char v16; // al
  int result; // eax
  _BYTE v18[512]; // [esp+0h] [ebp-224h] BYREF
  char *v19; // [esp+200h] [ebp-24h]
  int v20; // [esp+204h] [ebp-20h]
  int v21; // [esp+208h] [ebp-1Ch]

  v19 = &aTa[2];
  v0 = fopen(&aModemIni[2], &aR_2[2]);
  fgets(v18, 512, v0, v0);
  v1 = strtok(v18, &aTa[2]);
  modems = strtol(v1, 0, 10);
  modembuffer = getbuffer(56 * modems);
  if (!modembuffer)
    modems = 0;
  v21 = 0;
  if (modems > 0) {
    v2 = 0;
    do {
      fgets(v18, 512, v0, v0);
      v3 = strtok(v18, &aR_3[2]);
      *(_DWORD *)(modembuffer + v2 + 52) = strtol(v3, 0, 10) - 1;
      v4 = (char *)strtok(0, &aEa[2]);
      v5 = (char *)(v2 + modembuffer);
      do {
        v6 = *v4;
        *v5 = *v4;
        if (!v6)
          break;
        v7 = v4[1];
        v4 += 2;
        v5[1] = v7;
        v5 += 2;
      } while (v7);
      v2 += 56;
      ++v21;
    } while (v21 < modems);
  }
  fclose(v0);
  v8 = fopen(&aModemstrIni[1], &aR_2[2]);
  fgets(v18, 512, v8, v8);
  v9 = strtok(v18, v19);
  modemstrs = strtol(v9, 0, 10);
  modembuffer2 = getbuffer(51 * modemstrs);
  if (!modembuffer2)
    modemstrs = 0;
  v10 = 0;
  if (modemstrs > 0) {
    v20 = 0;
    do {
      fgets(v18, 512, v8, v8);
      v11 = strtok(v18, &comms_c_variable_13);
      v12 = v20;
      v13 = (char *)v11;
      v14 = (char *)(v20 + modembuffer2);
      ++v10;
      do {
        v15 = *v13;
        *v14 = *v13;
        if (!v15)
          break;
        v16 = v13[1];
        v13 += 2;
        v14[1] = v16;
        v14 += 2;
      } while (v16);
      v20 = v12 + 51;
    } while (v10 < modemstrs);
  }
  fclose(v8);
  if (current_modem >= modems)
    current_modem = modems - 1;
  result = -modems;
  if (-modems > current_modem)
    current_modem = -modems;
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00076C30
void select_modem()
{/*
  int v0; // eax
  int v1; // esi
  int v2; // edi
  int v3; // eax
  unsigned int v4; // eax
  int v5; // kr00_4
  int v6; // eax
  char *v7; // edi
  char *v8; // esi
  char v9; // al
  char v10; // al
  int v11; // [esp+4h] [ebp-10h]
  int v12; // [esp+8h] [ebp-Ch]
  int v13; // [esp+Ch] [ebp-8h]
  int v14; // [esp+10h] [ebp-4h]

  v12 = 0;
  v14 = current_modem;
  if (current_modem < 0)
    v14 = -current_modem - 1;
  while (!v12) {
    display_picture(scrbuf, front_vga[0], 3);
    display_block(head_y, 0);
    display_block(2, 0);
    display_block(247, 0);
    display_block(247, 0);
    display_block(257, -1);
    display_block(336, -1);
    scale_text(400, 75, 143, 1, 200, 640);
    v0 = v14 - 7;
    if (v14 - 7 < 0)
      v0 = 0;
    v11 = v14 + 7;
    if (v14 + 7 >= modems)
      v11 = modems - 1;
    v1 = v0;
    if (v0 <= v11) {
      v13 = 56 * v0;
      v2 = -18 * v14 + 18 * v0 + 237;
      do {
        if (v1 == v14)
          v3 = 171;
        else
          v3 = 143;
        ++v1;
        scale_text(400, v2, v3, 1, 200, 640);
        v2 += 18;
        v13 += 56;
      } while (v1 <= v11);
    }
    copypic((char *)scrbuf, (int)screen);
    while (fatkbhit()) {
      v4 = fatgetch();
      if (v4 < 0xD) {
        if (!v4) {
          v5 = fatgetch() - 71;
          v6 = modems - 1;
          switch (v5) {
            case 0:
              v14 = 0;
              continue;
            case 1:
              if (!v14)
                continue;
              v6 = v14 - 1;
            LABEL_26:
              v14 = v6;
              break;
            case 2:
              v14 -= 15;
              if (v14 < 0)
                v14 = 0;
              continue;
            case 8:
              goto LABEL_26;
            case 9:
              if (v6 > v14)
                ++v14;
              continue;
            case 10:
              v14 += 15;
              if (v6 < v14)
                v14 = modems - 1;
              continue;
            default:
              continue;
          }
        }
      } else if (v4 <= 0xD) {
        current_modem = v14;
        v7 = "ATX";
        v8 = (char *)(51 * *(_DWORD *)(56 * v14 + modembuffer + 52) + modembuffer2);
        v12 = -1;
        do {
          v9 = *v8;
          *v7 = *v8;
          if (!v9)
            break;
          v10 = v8[1];
          v8 += 2;
          v7[1] = v10;
          v7 += 2;
        } while (v10);
      } else if (v4 == 27) {
        v12 = -1;
      }
    }
  }
  JUMPOUT(0x76174);*/
}

//-------------------------------------------------------------------------------------------------
//00076F10
char *getprintstring(char *a1, int a2)
{
  return 0; /*
  char *v3; // edi
  char *v4; // esi
  char v5; // al
  char v6; // al
  unsigned int v7; // ecx
  unsigned int v8; // kr08_4
  unsigned int v9; // ecx
  char *v10; // edi
  char *v11; // esi
  char v12; // al
  char v13; // al
  unsigned int v14; // ecx
  unsigned int v15; // ecx

  v3 = modembuffer2_variable_2;
  v4 = a1;
  do {
    v5 = *v4;
    *v3 = *v4;
    if (!v5)
      break;
    v6 = v4[1];
    v4 += 2;
    v3[1] = v6;
    v3 += 2;
  } while (v6);
  if (a2) {
    v8 = strlen(modembuffer2_variable_2) + 1;
    v9 = v8 - 1;
    modembuffer2_variable_2[v9] = 95;
    modembuffer2_variable_3[v9] = 0;
    if (stringwidth(modembuffer2_variable_2) <= 240) {
      v15 = v8;
    } else {
      v10 = modembuffer2_variable_5;
      v11 = a1;
      modembuffer2_variable_2[0] = 46;
      modembuffer2_variable_3[0] = 46;
      modembuffer2_variable_4[0] = 46;
      do {
        v12 = *v11;
        *v10 = *v11;
        if (!v12)
          break;
        v13 = v11[1];
        v11 += 2;
        v10[1] = v13;
        v10 += 2;
      } while (v13);
      modembuffer2_variable_6[v9] = 0;
      modembuffer2_variable_5[v9] = 95;
      v14 = v8;
      while (stringwidth(modembuffer2_variable_2) > 240)
        memmove(modembuffer2_variable_5, modembuffer2_variable_6, v14--);
      v15 = v14 + 3;
    }
    if ((frames & 0xFu) >= 8)
      *((_BYTE *)&modembuffer2_variable_1 + v15) = 0;
  } else if (stringwidth(a1) > 240) {
    v7 = strlen(modembuffer2_variable_2);
    do {
      *((_BYTE *)&modembuffer2_variable_1 + v7) = 46;
      modembuffer2_variable_2[v7] = 46;
      modembuffer2_variable_3[v7] = 46;
      modembuffer2_variable_4[v7--] = 0;
    } while (stringwidth(modembuffer2_variable_2) > 240);
  }
  return modembuffer2_variable_2;*/
}

//-------------------------------------------------------------------------------------------------
//00077060
void display_essentials(int iSelectedItem, int iHighlightedItem, int iEditMode)
{
  char byTextColor1; // al
  char byTextColor2; // al
  char byTextColor3; // al
  char byTextColor4; // al
  char byTextColor5; // al
  char byTextColor6; // al
  char byTextColor7; // al
  char byTextColor8; // al
  char byTextColor9; // al
  bool bIsInitEditMode; // edx
  char *pszInitString; // eax
  char byTextColor10; // al
  char byTextColor11; // al
  bool bIsPhoneEditMode; // edx
  char *pszPhoneString; // eax
  char byTextColor12; // al
  char byTextColor13; // al
  char byInitTextColor; // [esp-10h] [ebp-78h]
  char byPhoneTextColor; // [esp-10h] [ebp-78h]
  char szText[100]; // [esp+0h] [ebp-68h] BYREF
  int iBlockIdx; // [esp+64h] [ebp-4h]

  iBlockIdx = iSelectedItem;                    // Store selected block index for gear selection display
  display_picture(scrbuf, front_vga[0]);        // Display main background picture (modem config screen)
  display_block(scrbuf, front_vga[1], 3, head_x, head_y, 0);// Display driver head icon at current position
  display_block(scrbuf, front_vga[6], 0, 36, 2, 0);// Display UI element at position (36, 2)
  display_block(scrbuf, front_vga[5], iBlockIdx, -4, 247, 0);// Display selected gear indicator at bottom left
  display_block(scrbuf, front_vga[5], game_type + 5, 135, 247, 0);// Display game type indicator (5 + game_type offset)
  display_block(scrbuf, front_vga[4], 4, 76, 257, -1);// Display UI element at position (76, 257) with special color (-1)
  display_block(scrbuf, front_vga[6], 4, 62, 336, -1);// Display UI element at position (62, 336) with special color (-1)
  scale_text(front_vga[15], &language_buffer[5376], font1_ascii, font1_offsets, 400, 75, 143, 1u, 200, 640);// Display main menu title text
  if (modembuffer)                            // Check if modem data is available
  {                                             // Check if no modem is currently selected (negative index)
    if (current_modem < 0) {                                           // Set color for 'no modem' text based on highlight state
      if (iHighlightedItem)
        byTextColor2 = 0x8F;
      else
        byTextColor2 = 0xAB;
      scale_text(front_vga[15], &language_buffer[6848], font1_ascii, font1_offsets, 400, 117, byTextColor2, 1u, 200, 640);// Display 'no modem selected' message
    } else {                                           // Set color for modem name based on highlight state
      if (iHighlightedItem)
        byTextColor1 = 0x8F;
      else
        byTextColor1 = 0xAB;
      scale_text(front_vga[15], &modembuffer[56 * current_modem], font1_ascii, font1_offsets, 400, 117, byTextColor1, 1u, 200, 640);// Display selected modem name (56 bytes per modem entry)
    }
  }
  sprintf(szText, "COM %d", modem_port);        // Format COM port number into text buffer
  if (iHighlightedItem == 1)                  // Set colors for COM port label (item 1)
    byTextColor3 = 0xAB;
  else
    byTextColor3 = 0x8F;
  scale_text(front_vga[15], &language_buffer[5440], font1_ascii, font1_offsets, 400, 135, byTextColor3, 2u, 200, 640);// Display COM port label text
  if (iHighlightedItem == 1)                  // Set colors for COM port value (item 1)
    byTextColor4 = 0xAB;
  else
    byTextColor4 = 0x8F;
  scale_text(front_vga[15], szText, font1_ascii, font1_offsets, 400, 135, byTextColor4, 0, 200, 640);// Display COM port number (e.g. 'COM 1')
  if (iHighlightedItem == 2)                  // Set colors for dial mode label (item 2)
    byTextColor5 = 0xAB;
  else
    byTextColor5 = 0x8F;
  scale_text(front_vga[15], &language_buffer[5504], font1_ascii, font1_offsets, 400, 153, byTextColor5, 2u, 200, 640);// Display dial mode label text
  if (modem_tone)                             // Check if tone dialing is enabled
  {                                             // Set colors for 'TONE' mode display
    if (iHighlightedItem == 2)
      byTextColor6 = 0xAB;
    else
      byTextColor6 = 0x8F;
    scale_text(front_vga[15], &language_buffer[5568], font1_ascii, font1_offsets, 400, 153, byTextColor6, 0, 200, 640);// Display 'TONE' dialing mode text
  } else {                                             // Set colors for 'PULSE' mode display
    if (iHighlightedItem == 2)
      byTextColor7 = 0xAB;
    else
      byTextColor7 = 0x8F;
    scale_text(front_vga[15], &language_buffer[5632], font1_ascii, font1_offsets, 400, 153, byTextColor7, 0, 200, 640);// Display 'PULSE' dialing mode text
  }
  if (iHighlightedItem == 3)                  // Set colors for modem init string label (item 3)
    byTextColor8 = 0xAB;
  else
    byTextColor8 = 0x8F;
  scale_text(front_vga[15], &language_buffer[5696], font1_ascii, font1_offsets, 400, 171, byTextColor8, 2u, 200, 640);// Display modem initialization string label
  if (iHighlightedItem == 3)                  // Set colors for init string value (item 3)
    byTextColor9 = 0xAB;
  else
    byTextColor9 = 0x8F;
  byInitTextColor = byTextColor9;
  bIsInitEditMode = iHighlightedItem == 3 && iEditMode == 1;// Check if init string is in edit mode (item 3 + edit flag)
  pszInitString = (char *)getprintstring(modem_initstring, bIsInitEditMode);// Get printable version of init string (handles edit cursor)
  scale_text(front_vga[15], pszInitString, font1_ascii, font1_offsets, 400, 171, byInitTextColor, 0, 200, 640);// Display modem initialization string
  if (iHighlightedItem == 4)                  // Set colors for phone number label (item 4)
    byTextColor10 = 0xAB;
  else
    byTextColor10 = 0x8F;
  scale_text(front_vga[15], &language_buffer[5760], font1_ascii, font1_offsets, 400, 189, byTextColor10, 2u, 200, 640);// Display phone number label text
  if (iHighlightedItem == 4)                  // Set colors for phone number value (item 4)
    byTextColor11 = 0xAB;
  else
    byTextColor11 = 0x8F;
  byPhoneTextColor = byTextColor11;
  bIsPhoneEditMode = iHighlightedItem == 4 && iEditMode == 1;// Check if phone number is in edit mode (item 4 + edit flag)
  pszPhoneString = (char *)getprintstring(modem_phone, bIsPhoneEditMode);// Get printable version of phone number (handles edit cursor)
  scale_text(front_vga[15], pszPhoneString, font1_ascii, font1_offsets, 400, 189, byPhoneTextColor, 0, 200, 640);// Display phone number string
  if (iHighlightedItem == 5)                  // Set colors for 'Accept' button (item 5)
    byTextColor12 = 0xAB;
  else
    byTextColor12 = 0x8F;
  scale_text(front_vga[15], &language_buffer[5824], font1_ascii, font1_offsets, 400, 225, byTextColor12, 1u, 200, 640);// Display 'Accept' button text
  if (iHighlightedItem == 6)                  // Set colors for 'Cancel' button (item 6)
    byTextColor13 = 0xAB;
  else
    byTextColor13 = 0x8F;
  scale_text(front_vga[15], &language_buffer[5888], font1_ascii, font1_offsets, 400, 243, byTextColor13, 1u, 200, 640);// Display 'Cancel' button text
  if (no_16550)                               // Check if 16550 UART error occurred
    scale_text(front_vga[15], &language_buffer[64 * no_16550], font1_ascii, font1_offsets, 400, 351, 231, 1u, 200, 640);// Display 16550 error message (64 bytes per error code)
}

//-------------------------------------------------------------------------------------------------
//00077560
void check16550(int iPort)
{                                               // Test if 16550 UART is available at the specified port
  //TODO
  //if (gss16550(iPort)) {
  if (true) {
    no_16550 = 0;                               // 16550 UART detected - clear error flag (0 = success)
  } else if (MusicCD)                           // 16550 not found - check if CD music is enabled
  {
    no_16550 = 110;                             // CD music available - set error code 110 (CD audio fallback)
  } else {
    no_16550 = 109;                             // No 16550 and no CD music - set error code 109 (no audio support)
  }
  if (no_16550 == 109)                        // Check if complete audio failure occurred (code 109)
  {
    musicon = 0;                                // Disable music playback due to hardware failure
    reinitmusic();                              // Reinitialize music system with new settings
  }
  if (no_16550)                               // Check if any 16550 error occurred
    soundon = 0;                                // Disable all sound effects if 16550 hardware issues detected
}

//-------------------------------------------------------------------------------------------------

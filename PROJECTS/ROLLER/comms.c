#include "comms.h"
#include "sound.h"
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

//-------------------------------------------------------------------------------------------------

int select_comport(uint16 a1, char *a2, unsigned int a3)
{
  return 0; /*
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  unsigned int v8; // eax
  unsigned int v9; // eax
  int v11; // [esp+4h] [ebp-4h]

  __asm { int     11h; EQUIPMENT DETERMINATION }
  v11 = 0;
  v3 = ((int)a1 >> 9) & 7;
  if ((unsigned int)v3 < 2)
    v3 = 2;
  if (v3 < serial_port)
    serial_port = 2;
  check16550(serial_port);
  gssCommsSetComBaudRate(9600);
  do {
    display_picture(scrbuf, front_vga[0], a2);
    display_block(head_y, 0);
    display_block(2, 0);
    display_block(247, 0);
    display_block(247, 0);
    display_block(257, -1);
    display_block(336, -1);
    scale_text(400, 75, 143, 1, 200, 640);
    scale_text(400, 93, 143, 1, 200, 640);
    if (serial_port == 1)
      v4 = 171;
    else
      v4 = 143;
    scale_text(400, 135, v4, 1, 200, 640);
    if (serial_port == 2)
      v5 = 171;
    else
      v5 = 143;
    a2 = font1_ascii;
    scale_text(400, 153, v5, 1, 200, 640);
    if (v3 >= 3) {
      if (serial_port == 3)
        v6 = 171;
      else
        v6 = 143;
      a2 = font1_ascii;
      scale_text(400, 171, v6, 1, 200, 640);
    }
    if (v3 >= 4) {
      if (serial_port == 4)
        v7 = 171;
      else
        v7 = 143;
      a2 = font1_ascii;
      scale_text(400, 189, v7, 1, 200, 640);
    }
    if (no_16550) {
      a2 = font1_ascii;
      scale_text(400, 351, 231, 1, 200, 640);
    }
    copypic((char *)scrbuf, (int)screen);
    while (fatkbhit()) {
      v8 = fatgetch();
      a3 = v8;
      if (v8 < 0xD) {
        if (!v8) {
          v9 = fatgetch();
          a3 = v9;
          if (v9 >= 0x48) {
            if (v9 <= 0x48) {
              if (serial_port != 1)
                --serial_port;
            LABEL_38:
              check16550(serial_port);
            } else if (v9 == 80) {
              if (v3 != serial_port)
                ++serial_port;
              goto LABEL_38;
            }
          }
        }
      } else if (v8 <= 0xD || v8 == 27) {
        v11 = -1;
      }
    }
  } while (!v11);
  gssCommsSetComPort(serial_port);
  return (a3 != 13) - 1;*/
}

//-------------------------------------------------------------------------------------------------

int stringwidth(char *a1)
{
  return 0; /*
  int result; // eax
  int v3; // ebx

  result = 0;
  while (*a1) {
    v3 = (unsigned __int8)font1_ascii[(unsigned __int8)*a1++];
    if (v3 == 255)
      result += 8;
    else
      result += *(_DWORD *)(12 * v3 + front_vga_variable_10) + 1;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

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

int64 display_essentials(int a1, int a2, int a3)
{
  return 0; /*
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  bool v11; // edx
  int v12; // eax
  int v13; // eax
  bool v14; // edx
  int v15; // eax
  int v16; // eax
  __int64 result; // rax
  int v18; // [esp-10h] [ebp-78h]
  int v19; // [esp-10h] [ebp-78h]
  _BYTE v20[100]; // [esp+0h] [ebp-68h] BYREF
  int v21; // [esp+64h] [ebp-4h]

  v21 = a1;
  display_picture(scrbuf, front_vga[0], 3);
  display_block(head_y, 0);
  display_block(2, 0);
  display_block(247, 0);
  display_block(247, 0);
  display_block(257, -1);
  display_block(336, -1);
  scale_text(400, 75, 143, 1, 200, 640);
  if (modembuffer) {
    if (current_modem < 0) {
      if (a2)
        v4 = 143;
      else
        v4 = 171;
    } else if (a2) {
      v4 = 143;
    } else {
      v4 = 171;
    }
    scale_text(400, 117, v4, 1, 200, 640);
  }
  sprintf(v20, "COM %d", modem_port);
  if (a2 == 1)
    v5 = 171;
  else
    v5 = 143;
  scale_text(400, 135, v5, 2, 200, 640);
  if (a2 == 1)
    v6 = 171;
  else
    v6 = 143;
  scale_text(400, 135, v6, 0, 200, 640);
  if (a2 == 2)
    v7 = 171;
  else
    v7 = 143;
  scale_text(400, 153, v7, 2, 200, 640);
  if (modem_tone) {
    if (a2 == 2)
      v8 = 171;
    else
      v8 = 143;
  } else if (a2 == 2) {
    v8 = 171;
  } else {
    v8 = 143;
  }
  scale_text(400, 153, v8, 0, 200, 640);
  if (a2 == 3)
    v9 = 171;
  else
    v9 = 143;
  scale_text(400, 171, v9, 2, 200, 640);
  if (a2 == 3)
    v10 = 171;
  else
    v10 = 143;
  v18 = v10;
  v11 = a2 == 3 && a3 == 1;
  getprintstring("ATX", v11);
  scale_text(400, 171, v18, 0, 200, 640);
  if (a2 == 4)
    v12 = 171;
  else
    v12 = 143;
  scale_text(400, 189, v12, 2, 200, 640);
  if (a2 == 4)
    v13 = 171;
  else
    v13 = 143;
  v19 = v13;
  v14 = a2 == 4 && a3 == 1;
  getprintstring(&modem_phone, v14);
  scale_text(400, 189, v19, 0, 200, 640);
  if (a2 == 5)
    v15 = 171;
  else
    v15 = 143;
  scale_text(400, 225, v15, 1, 200, 640);
  if (a2 == 6)
    v16 = 171;
  else
    v16 = 143;
  result = scale_text(400, 243, v16, 1, 200, 640);
  if (no_16550)
    return scale_text(400, 351, 231, 1, 200, 640);
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void check16550(int iPort, int a2)
{
  int v2; // eax

  v2 = 0;// gss16550(iPort);
  if (v2) {
    a2 = 0;
    no_16550 = 0;
  } else if (MusicCD) {
    no_16550 = 110;
  } else {
    no_16550 = 109;
  }
  if (no_16550 == 109) {
    musicon = 0;
    reinitmusic(v2, a2);
  }
  if (no_16550)
    soundon = 0;
}

//-------------------------------------------------------------------------------------------------

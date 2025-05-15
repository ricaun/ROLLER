#include "3d.h"
#include <stdio.h>
#include <stdlib.h>
//-------------------------------------------------------------------------------------------------

int hibuffers;        //000A32E0
uint32 textures_off;  //0013F960

//-------------------------------------------------------------------------------------------------
#ifdef ENABLE_PSEUDO
//-------------------------------------------------------------------------------------------------

int __fastcall copypic(char *a1, int a2)
{
  int result; // eax
  int j; // edx
  char *v6; // esi
  char *v7; // edi
  char *v8; // ecx
  int i; // esi
  int v10; // edx
  int v11; // edi
  char v12; // bl

  if (SVGA_ON) {
    if (SVGA_ON == 1) {
      return (int)copyscreenmodex((int)a1, a2);
    } else if (scrmode == 257) {
      return svgacopy(a1, winx, winy + 40, (__int16)winw, (__int16)winh);
    } else {
      return svgacopy(a1, winx, winy, (__int16)winw, (__int16)winh);
    }
  } else if (winw != XMAX || winx || mirror) {
    if (mirror) {
      v8 = a1;
      result = winw + winx + a2 + XMAX * winy - 1;
      for (i = 0; i < winh; result += XMAX + winw) {
        v10 = 0;
        if (winw > 0) {
          do {
            v11 = winw;
            --result;
            v12 = *v8++;
            ++v10;
            *(_BYTE *)(result + 1) = v12;
          } while (v10 < v11);
        }
        ++i;
      }
    } else {
      result = winh;
      for (j = 0; j < winh; ++j) {
        v6 = &a1[winw * j];
        v7 = (char *)(winx + XMAX * (j + winy) + a2);
        result = winw;
        qmemcpy(v7, v6, winw);
      }
    }
  } else {
    result = winh * winw;
    qmemcpy((void *)(winw * winy + a2), a1, winh * winw);
  }
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall init_screen(int a1, int a2, int a3)
{
  int v3; // edx
  int v4; // ebx
  int i; // esi
  __int16 v6; // bx
  int result; // eax
  _DWORD v8[9]; // [esp+0h] [ebp-24h] BYREF

  v3 = svga_possible;
  v8[0] = threed_c_reference_1[0];
  v8[1] = threed_c_reference_1[1];
  v8[2] = threed_c_reference_1[2];
  if (!svga_possible && SVGA_ON) {
    setmodex();
    SVGA_ON = 1;
    current_mode = -1;
    XMAX = 640;
    YMAX = 400;
    scr_size = 128;
  }
  if (SVGA_ON && current_mode != -1) {
    current_mode = -1;
    v4 = VESAmode(v8, v3, a3, (_BYTE *)0xFFFFFFFF);
    scrmode = v4;
    if (v4 == -1) {
      if (firstrun) {
        if (!language) {
          printf(&aBooThisProgram[3]);
          printf(&aAtItSOptimumLe[1]);
          printf(&aCdmoreInformat[3]);
          printf(aGraphics);
          printf(&aVpressAnyKeyTo[1]);
          fflush(&__iob_variable_1);
          while (fatkbhit())
            fatgetch();
          fatgetch();
        }
        firstrun = 0;
      }
      svga_possible = 0;
      setmodex();
      SVGA_ON = 1;
      XMAX = 640;
      YMAX = 400;
      scr_size = 128;
      current_mode = -1;
    } else {
      current_mode = -1;
      SVGA_ON = -1;
      XMAX = 640;
      YMAX = 400;
      scr_size = 128;
      if (v4 == 257) {
        memset(blank_line, 0, sizeof(blank_line));
        for (i = 0; i < 40; ++i) {
          v6 = i;
          svgacopy(blank_line, 0, v6, 640, 1);
        }
        memset(blank_line, 112, sizeof(blank_line));
      }
    }
  }
  if (!SVGA_ON && current_mode) {
    current_mode = SVGA_ON;
    XMAX = 320;
    YMAX = 200;
    scr_size = 64;
    __asm { int     10h; -VIDEO - SET VIDEO MODE }
  }
  xbase = 159;
  ybase = 115;
  winw = XMAX;
  winx = 0;
  winh = YMAX;
  result = palette_brightness;
  winy = 0;
  if (palette_brightness > 0)
    return resetpal();
  return result;
}

//-------------------------------------------------------------------------------------------------

int init()
{
  int v0; // edx
  int v1; // eax
  char *v2; // edi
  int v3; // edx
  char *v4; // edi
  char *v5; // edi
  int v6; // edx
  int v12; // edx
  int v13; // eax
  __int64 v14; // rax
  double v16; // [esp+0h] [ebp-54h]
  unsigned __int64 v17; // [esp+8h] [ebp-4Ch]
  __int64 v18; // [esp+10h] [ebp-44h]
  unsigned __int64 v19; // [esp+20h] [ebp-34h]
  int v20; // [esp+30h] [ebp-24h]
  int v21; // [esp+34h] [ebp-20h]
  int i; // [esp+38h] [ebp-1Ch]

  test_f1 = 0;
  test_f2 = 0;
  switch_sets = 0;
  switch_same = 0;
  switch_types = 0;
  my_number = -1;
  if (SVGA_ON)
    scr_size = 128;
  else
    scr_size = 64;
  v0 = 9;
  v1 = 1;
  RecordLaps[0] = 128.0;
  RecordCars[0] = -1;
  tex_count = 1;
  RecordKills[0] = 0;
  strcpy(RecordNames, "-----");
  do {
    v2 = &RecordNames[v0];
    v3 = v0 + 9;
    RecordLaps[v1] = 128.0;
    RecordKills[v1] = 0;
    RecordCars[v1] = -1;
    v1 += 3;
    strcpy(v2, "-----");
    v4 = &RecordNames[v3];
    race_started[v1] = 1124073472;
    RecordLaps_variable_2[v1] = -1;
    RecordCars_variable_2[v1] = 0;
    v3 += 9;
    strcpy(v4, "-----");
    v5 = &RecordNames[v3];
    updates[v1] = 1124073472;
    RecordLaps_variable_3[v1] = -1;
    RecordCars_variable_3[v1] = 0;
    v0 = v3 + 9;
    strcpy(v5, "-----");
  } while (v1 != 25);
  NoOfLaps = 0;
  LOWORD(player1_car) = 0;
  player_invul[0] = 0;
  player_invul_variable_1 = 0;
  player2_car = 1;
  _STOSB(blank_line, 1886417008);
  DDY = 160.0;
  DDZ = 270.0;
  v6 = 0;
  clear_borders = 0;
  VIEWDIST = 270;
  DDX = 0.0;
  v21 = 0;
  do {
    __asm
    {
      fild[esp + 4Ch + var_20]
      fmul    dbl_A0126
      fmul    dbl_A012E
      fld     st
      fsincos
      fstp    flt_121128[edx]
    }
    flt_121128[v6] = _ET1;
    __asm { fstp    flt_1010F0[edx] }
    flt_1010F0[v6] = _ET1;
    __asm
    {
      fptan
      fstp1   st
      fst[esp + 4Ch + var_34]
      fcomp   dbl_A0146
      fnstsw  ax
    }
    if ((_AX & 0x100) != 0 || (_AX & 0x4000) != 0) {
      __asm
      {
        fld[esp + 4Ch + var_34]
        fcomp   dbl_A014E
        fnstsw  ax
      }
      if ((_AX & 0x100) != 0)
        v17 = 0xC0E0000000000000LL;
      else
        v17 = v19;
      v18 = v17;
    } else {
      v18 = 0x40DFFFC000000000LL;
    }
    __asm { fld[esp + 4Ch + var_44] }
    ++v6;
    v21 += 2;
    __asm { fstp    flt_1110EC[edx] }
    flt_1110EC[v6] = _ET1;
  } while (v21 != 0x8000);
  v12 = 0;
  dword_13FA54 = 0;
  dword_13F99C = 0;
  dword_13F9A0 = 0;
  for (i = 0; i < 1025; ++i) {
    __asm
    {
      fild[esp + 4Ch + var_1C]
      fmul    dbl_A0136
      fld1
      fpatan
      fmul    dbl_A013E
      fdiv    dbl_A0156
      fadd    dbl_A015E
      fstp[esp + 54h + var_54]; double
    }
    v13 = floor(v16);
    _CHP(v13, v12 * 4);
    __asm { fistp[esp + 4Ch + var_24] }
    dword_13E958[++v12] = v20;
  }
  v14 = getbuffer(256000);
  dword_A353C = v14;
  return LoadRecords(v14, SHIDWORD(v14), 0);
}

//-------------------------------------------------------------------------------------------------

unsigned int __fastcall getbuffer(unsigned int a1)
{
  int v2; // esi
  int v3; // ebx
  unsigned int result; // eax
  int v5; // ebp
  int v6; // ebp
  int v7; // ebx
  int v8; // ecx
  int v9; // ebx
  int v10; // ecx
  unsigned __int16 v11; // [esp+0h] [ebp-4Ch] BYREF
  unsigned __int16 v12; // [esp+4h] [ebp-48h]
  unsigned __int16 v13; // [esp+Ch] [ebp-40h]
  _BYTE v14[12]; // [esp+1Ch] [ebp-30h] BYREF
  int v15; // [esp+28h] [ebp-24h] BYREF
  int v16; // [esp+2Ch] [ebp-20h] BYREF
  int v17; // [esp+30h] [ebp-1Ch]

  v2 = 0;
  if (mem_blocks[0]) {
    do {
      v3 = mem_blocks_variable_4[v2];
      v2 += 4;
    } while (v3);
  }
  result = malloc2(a1, (unsigned int *)&v16, &v15);
  v5 = result;
  if (result) {
    mem_blocks[v2] = result;
    mem_blocks_variable_1[v2] = a1;
    mem_blocks_variable_2[v2] = v16;
    v10 = hibuffers;
    mem_blocks_variable_3[v2] = v15;
    hibuffers = v10 + 1;
    mem_used += a1;
  } else {
    memset(v14, 0, sizeof(v14));
    v11 = 256;
    v12 = -1;
    int386x(49, (int)&v11, (int)&v11, (int)v14);
    v17 = (a1 >> 4) + 1;
    if (v12 - 640 < v17) {
      __asm { int     10h; -VIDEO - SET VIDEO MODE }
      printf(&aDmnotEnoughMem[2]);
      doexit();
    } else {
      memset(v14, 0, sizeof(v14));
      v11 = 256;
      v12 = v17;
      int386x(49, (int)&v11, (int)&v11, (int)v14);
      v6 = v11;
      v7 = mem_used_low;
      mem_blocks_variable_1[v2] = -16 * v17;
      v8 = lobuffers;
      v5 = 16 * v6;
      mem_blocks_variable_2[v2] = v13;
      lobuffers = v8 + 1;
      v9 = 16 * v17 + v7;
      mem_blocks[v2] = v5;
      mem_used_low = v9;
    }
    return v5;
  }
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall trybuffer(unsigned int a1)
{
  int v2; // esi
  int v3; // ebx
  unsigned int v4; // eax
  int v5; // ebx
  int v6; // edi
  int v7; // ebp
  unsigned __int16 v8; // bx
  int v9; // eax
  int v11; // ecx
  __int16 v12; // [esp+0h] [ebp-48h] BYREF
  unsigned __int16 v13; // [esp+4h] [ebp-44h]
  unsigned __int16 v14; // [esp+Ch] [ebp-3Ch]
  _BYTE v15[12]; // [esp+1Ch] [ebp-2Ch] BYREF
  int v16; // [esp+28h] [ebp-20h] BYREF
  int v17[7]; // [esp+2Ch] [ebp-1Ch] BYREF

  v2 = 0;
  if (mem_blocks[0]) {
    do {
      v3 = mem_blocks_variable_4[v2];
      v2 += 4;
    } while (v3);
  }
  v4 = malloc2(a1, (unsigned int *)&v16, v17);
  v5 = v4;
  if (v4) {
    mem_blocks[v2] = v4;
    mem_blocks_variable_1[v2] = a1;
    mem_blocks_variable_2[v2] = v16;
    v11 = mem_used;
    mem_blocks_variable_3[v2] = v17[0];
    mem_used = a1 + v11;
    ++hibuffers;
  } else {
    memset(v15, 0, sizeof(v15));
    v12 = 256;
    v13 = -1;
    int386x(49, (int)&v12, (int)&v12, (int)v15);
    v6 = (a1 >> 4) + 1;
    if (v6 > v13 - 640)
      return 0;
    memset(v15, 0, sizeof(v15));
    v12 = 256;
    v13 = v6;
    int386x(49, (int)&v12, (int)&v12, (int)v15);
    v7 = mem_used_low;
    v8 = v12;
    mem_blocks_variable_1[v2] = -16 * v6;
    v5 = 16 * v8;
    mem_blocks_variable_2[v2] = v14;
    mem_used_low = 16 * v6 + v7;
    v9 = lobuffers + 1;
    mem_blocks[v2] = v5;
    lobuffers = v9;
  }
  return v5;
}

//-------------------------------------------------------------------------------------------------

_DWORD *__fastcall fre(_DWORD *result)
{
  _DWORD *v1; // esi
  int v2; // edx
  int v3; // eax
  int v4; // ebx
  int v5; // eax
  __int16 v6; // ax
  _WORD v7[14]; // [esp+0h] [ebp-40h] BYREF
  _BYTE v8[36]; // [esp+1Ch] [ebp-24h] BYREF

  v1 = result;
  if (*result) {
    v2 = 0;
    v3 = 0;
    if (mem_blocks[0] != *v1) {
      do {
        if (v3 >= 512)
          break;
        v4 = mem_blocks_variable_4[v3];
        v3 += 4;
        ++v2;
      } while (v4 != *v1);
    }
    if (v2 >= 128) {
      __asm { int     10h; -VIDEO - SET VIDEO MODE }
      printf(&aNofailedToFind[3], v7[0]);
      doexit(1);
    } else {
      mem_blocks[4 * v2] = 0;
    }
    v5 = mem_blocks_variable_1[4 * v2];
    if (v5 >= 0) {
      mem_used -= v5;
      result = (_DWORD *)free2(mem_blocks_variable_2[4 * v2], mem_blocks_variable_3[4 * v2]);
    } else {
      mem_used_low += v5;
      memset(v8, 0, 12);
      v6 = mem_blocks_variable_2[4 * v2];
      v7[0] = 257;
      v7[6] = v6;
      result = (_DWORD *)((int(__fastcall *)(int, _WORD *, _WORD *, _BYTE *))int386x)(49, v7, v7, v8);
      --lobuffers;
    }
    *v1 = 0;
  }
  return result;
}

//-------------------------------------------------------------------------------------------------

void doexit()
{
  int v0; // eax
  int *v1; // edx
  int *v2; // eax
  _DWORD *v3; // ebx
  int *v4; // edx
  _DWORD *v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  int v11; // edx

  exiting = -1;
  if (network_on) {
    tick_on = -1;
    frontend_on = -1;
    broadcast_mode = -666;
    while (broadcast_mode == -666)
      ;
  }
  v0 = close_network();
  SaveRecords(v0);
  v1 = &rev_vga;
  fre(&mirbuf);
  do {
    v2 = v1++;
    fre(v2);
  } while (v1 != &rev_vga + 16);
  v3 = &cartex_vga;
  v4 = &front_vga;
  fre(&horizon_vga);
  do {
    fre(v4);
    fre(v3);
    ++v4;
    ++v3;
  } while (v4 != &front_vga + 16);
  fre(&font_vga);
  fre(&title_vga);
  fre(&cargen_vga);
  fre(&texture_vga);
  fre(&building_vga);
  v5 = fre(&scrbuf);
  v6 = release_key_int(v5);
  v7 = Uninitialise_SOS(v6);
  v8 = releasesamples(v7);
  if (MusicCD)
    cdxdone(v8);
  v9 = remove(aReplaysReplayT);
  if ((cheat_mode & 0x40) != 0)
    textures_off |= 0x2000u;
  else
    textures_off &= ~0x2000u;
  if (false_starts) {
    v10 = textures_off;
    BYTE1(v10) = BYTE1(textures_off) | 0x40;
    textures_off = v10;
  } else {
    v11 = textures_off;
    BYTE1(v11) = BYTE1(textures_off) & 0xBF;
    textures_off = v11;
  }
  if (!intro)
    v9 = save_fatal_config(v9);
  while (kbhit(v9))
    v9 = getch();
  chdir(&aNy[2]);
  __atexit();
  __int23_exit();
  __int23_exit();
  __FPE_handler_exit();
  JUMPOUT(0x7A98F);
}

//-------------------------------------------------------------------------------------------------

int firework_screen()
{
  int v0; // esi
  float *v1; // ebx
  unsigned __int8 v2; // al
  int v3; // ecx
  double v4; // st7
  double v5; // st7
  int i; // ecx
  double v7; // st7
  double v8; // st7
  int v9; // eax
  int v10; // edx
  int v12; // [esp+0h] [ebp-30h]
  int v13; // [esp+4h] [ebp-2Ch]
  int v14; // [esp+8h] [ebp-28h]
  int v15; // [esp+Ch] [ebp-24h]
  char v16; // [esp+10h] [ebp-20h]

  v0 = 0;
  memset(scrbuf, 112, winh * winw);
  do {
    v1 = (float *)&CarSpray[v0];
    v2 = CarSpray[v0 + 40];
    if (v2) {
      if (v2 <= 1u) {
        v3 = 0;
        v16 = 0;
        do {
          if (*((_BYTE *)v1 + 40)) {
            v4 = *v1;
            _CHP();
            v14 = (int)v4;
            v5 = v1[1];
            _CHP();
            v13 = (int)v5;
            if (v14 >= 0 && v14 < winw && v13 >= 0 && v13 < winh)
              *(_BYTE *)(winw * v13 + v14 + scrbuf) = *((_BYTE *)v1 + 36) - v16;
          }
          v1 += 11;
          ++v3;
          v16 += 3;
        } while (v3 < 5);
      } else if (v2 == 2) {
        for (i = 0; i < 32; ++i) {
          if (*((int *)v1 + 7) > 0) {
            v7 = *v1;
            _CHP();
            v15 = (int)v7;
            v8 = v1[1];
            _CHP();
            v12 = (int)v8;
            v9 = rand();
            v10 = ((16 * v9 - (__CFSHL__((16 * v9) >> 31, 15) + ((16 * v9) >> 31 << 15))) >> 15) - 4;
            if (v10 < 0)
              LOBYTE(v10) = 0;
            if (v15 >= 0 && v15 < winw && v12 >= 0 && v12 < winh)
              *(_BYTE *)(v15 + winw * v12 + scrbuf) = *((_BYTE *)v1 + 36) - v10;
          }
          v1 += 11;
        }
      }
    }
    v0 += 1408;
  } while (v0 != 25344);
  return game_copypic(scrbuf, screen, ViewType);
}

//-------------------------------------------------------------------------------------------------

int updatescreen()
{
  int v0; // esi
  int v1; // edi
  int v2; // ebp
  int v3; // esi
  int v4; // ecx
  char *v5; // esi
  int v6; // ebx
  _BYTE *k; // ecx
  int v8; // eax
  _BYTE *m; // ecx
  char v10; // dl
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v15; // esi
  int v16; // edi
  int v17; // ebp
  int v18; // ecx
  char *v19; // esi
  int v20; // ebx
  _BYTE *i; // ecx
  int v22; // eax
  _BYTE *j; // ecx
  char v24; // dl
  int v25; // eax
  int v26; // ebx
  int v27; // edx
  int v28; // ecx
  int v29; // [esp+0h] [ebp-24h]
  int v30; // [esp+4h] [ebp-20h]

  mirror = 0;
  shown_panel = 0;
  screenready = -1;
  if (SVGA_ON)
    small_poly = 200;
  else
    small_poly = 100;
  time_shown = 0;
  if (!Play_View)
    goto LABEL_30;
  if ((unsigned __int8)Play_View <= 1u) {
    time_shown = -1;
    v15 = scr_size;
    xbase = 319;
    scr_size = (scr_size - (__CFSHL__(scr_size >> 31, 2) + 4 * (scr_size >> 31))) >> 2;
    winw = (320 * scr_size) >> 5;
    v16 = (320 * scr_size) >> 5;
    winx = 0;
    winy = 0;
    winh = (200 * scr_size) >> 6;
    v17 = (200 * scr_size) >> 6;
    v30 = 0;
    if ((ViewType & 1) != 0) {
      if (Car_variable_23[308 * ViewType - 308] < 0)
        goto LABEL_20;
    } else if (Car_variable_23[308 * ViewType + 308] < 0) {
      goto LABEL_20;
    }
    v30 = -1;
    draw_road(0);
  LABEL_20:
    time_shown = 0;
    shown_panel = 0;
    winw = (320 * v15 + 32) >> 6;
    xbase = 159;
    winh = (200 * v15 + 32) >> 6;
    winx = (XMAX - ((320 * v15 + 32) >> 6)) / 2;
    winy = (YMAX - ((200 * v15 + 32) >> 6)) / 2;
    scr_size = v15;
    v12 = draw_road(0);
    if (clear_borders) {
      clear_borders = 0;
      ((void (*)(void))clear_border)();
      clear_border(0, winy, winx, winh);
      clear_border(winx + winw, winy, winx, winh);
      v12 = clear_border(0, winy + winh, XMAX, YMAX - (winy + winh));
    }
    if (v30) {
      v18 = (winw - v16 - 1) / 2
        + scrbuf
        + winw * ((11 * scr_size - (__CFSHL__((11 * scr_size) >> 31, 6) + ((11 * scr_size) >> 31 << 6))) >> 6);
      v19 = (char *)mirbuf;
      memset(v18, 119, v16 + 2);
      v20 = 0;
      for (i = (_BYTE *)(winw + v18); v20 < v17; i = &j[v25 - v16 - 1]) {
        *i = 119;
        v22 = 0;
        for (j = i + 1; v22 < v16; *(j - 1) = v24) {
          ++j;
          v24 = *v19++;
          ++v22;
        }
        v25 = winw;
        *j = 119;
        ++v20;
      }
      v12 = memset(i, 119, v16 + 2);
    }
    if (screenready)
      goto LABEL_14;
    return init_animate_ads(v12);
  }
  if (Play_View == 2) {
    v0 = scr_size;
    xbase = 159;
    scr_size /= 2;
    winw = (320 * scr_size) >> 6;
    v1 = (320 * scr_size) >> 6;
    time_shown = -1;
    winx = 0;
    winy = 0;
    winh = (200 * scr_size) >> 7;
    v2 = (200 * scr_size) >> 7;
    draw_road(0);
    xbase = 159;
    winw = (320 * v0 + 32) >> 6;
    winh = (200 * v0 + 32) >> 6;
    time_shown = 0;
    shown_panel = 0;
    winx = (XMAX - ((320 * v0 + 32) >> 6)) / 2;
    winy = (YMAX - ((200 * v0 + 32) >> 6)) / 2;
    scr_size = v0;
    draw_road(0);
    v3 = (winw - v1 - 1) / 2;
    v29 = (11 * scr_size - (__CFSHL__((11 * scr_size) >> 31, 6) + ((11 * scr_size) >> 31 << 6))) >> 6;
    if (clear_borders) {
      clear_borders = 0;
      clear_border(0, 0, XMAX, winy);
      clear_border(0, winy, winx, winh);
      clear_border(winx + winw, winy, winx, winh);
      clear_border(0, winh + winy, XMAX, YMAX - (winh + winy));
    }
    v4 = v29 * winw + v3 + scrbuf;
    v5 = (char *)(v1 + mirbuf - 1);
    memset(v4, 112, v1 + 2);
    v6 = 0;
    for (k = (_BYTE *)(winw + v4); v6 < v2; k = &m[v11 - v1 - 1]) {
      *k = 112;
      v8 = 0;
      for (m = k + 1; v8 < v1; *(m - 1) = v10) {
        ++m;
        v10 = *v5--;
        ++v8;
      }
      v11 = winw;
      ++v6;
      *m = 112;
      v5 += 2 * v1;
    }
    v12 = memset(k, 112, v1 + 2);
    if (screenready) {
    LABEL_14:
      v13 = game_copypic(scrbuf, screen, ViewType);
      return init_animate_ads(v13);
    }
    return init_animate_ads(v12);
  }
LABEL_30:
  if (player_type == 2) {
    if (SVGA_ON)
      scr_size = 64;
    else
      scr_size = 32;
    winw = XMAX;
    xbase = 319;
    winx = 0;
    winy = 0;
    winh = YMAX / 2 - 2;
    if (clear_borders)
      memset(scrbuf + winh * winw, 0, 4 * winw);
    draw_road(0);
    shown_panel = 0;
    draw_road(1);
    time_shown = -1;
    if (SVGA_ON)
      scr_size = 128;
    else
      scr_size = 64;
    draw_type = 0;
    winw = XMAX;
    winh = YMAX;
    v12 = game_copypic(scrbuf, screen, ViewType);
    draw_type = 2;
    return init_animate_ads(v12);
  }
  if ((cheat_mode & 0x40) == 0 || paused) {
    if ((cheat_mode & 0x40) != 0) {
      if (SVGA_ON)
        scr_size = 128;
      else
        scr_size = 64;
    }
    winh = (200 * scr_size + 32) >> 6;
    winw = (320 * scr_size + 32) >> 6;
    winx = (XMAX - ((320 * scr_size + 32) >> 6)) / 2;
    xbase = 159;
    winy = (YMAX - ((200 * scr_size + 32) >> 6)) / 2;
    if (clear_borders) {
      clear_borders = 0;
      clear_border(0, 0, XMAX, winy);
      clear_border(0, winy, winx, winh);
      clear_border(winx + winw, winy, winx, winh);
      v28 = YMAX;
      v27 = winh + winy;
      v26 = XMAX;
      goto LABEL_44;
    }
  } else {
    if (SVGA_ON)
      scr_size = 64;
    else
      scr_size = 32;
    winh = YMAX / 2;
    winw = XMAX;
    winx = 0;
    xbase = 319;
    winy = (YMAX - (__CFSHL__(YMAX >> 31, 2) + 4 * (YMAX >> 31))) >> 2;
    if (clear_borders) {
      clear_borders = 0;
      clear_border(0, 0, XMAX, (YMAX - (__CFSHL__(YMAX >> 31, 2) + 4 * (YMAX >> 31))) >> 2);
      v26 = XMAX;
      v27 = winh + winy;
      v28 = YMAX;
    LABEL_44:
      clear_border(0, v27, v26, v28 - v27);
    }
  }
  v12 = draw_road(0);
  if ((cheat_mode & 0x40) == 0)
    return init_animate_ads(v12);
  if (SVGA_ON)
    scr_size = 128;
  else
    scr_size = 64;
  winw = XMAX;
  winh = YMAX;
  return init_animate_ads(YMAX);
}

//-------------------------------------------------------------------------------------------------
int __fastcall draw_road(int a1, int a2, unsigned int a3, int a4, int a5)
{
  double v6; // st7
  double v7; // st7
  int v8; // eax
  int result; // eax

  if ((textures_off & 0x80000) != 0 || game_track == 13) {
    if (gfx_size == 1)
      min_sub_size = 64;
    else
      min_sub_size = 128;
  } else if (gfx_size == 1) {
    min_sub_size = 4;
  } else {
    min_sub_size = 8;
  }
  if (SVGA_ON)
    v6 = (double)scr_size * threed_c_variable_20;
  else
    v6 = (double)scr_size * threed_c_variable_21;
  subscale = v6;
  if ((textures_off & 0x80000) != 0 || game_track == 13) {
    if (SVGA_ON)
      v7 = (double)scr_size * threed_c_variable_22;
    else
      v7 = (double)scr_size * threed_c_variable_23;
    subscale = v7;
  }
  screen_pointer = a1;
  calculateview(a3, a2, a5);
  DrawHorizon(a1);
  CalcVisibleTrack(a2, a3);
  v8 = DrawCars(a2, a3, a2, a5);
  CalcVisibleBuildings(v8);
  result = DrawTrack3(a1, a5);
  if (a4) {
    if (screenready)
      return game_copypic(a1, screen, a2);
  }
  return result;
}

//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------

int __cdecl main(int argc, const char **argv, const char **envp)
{
#ifdef ENABLE_PSEUDO
  int v3; // eax
  char **v4; // edx
  int v5; // ecx
  int inited; // eax
  int v7; // eax
  int v8; // eax
  int v9; // edi
  int v10; // ecx
  char *v11; // eax
  char *v12; // eax
  int v13; // eax
  int v14; // edx
  int v15; // eax
  int v16; // ebx
  int v17; // edx
  int v18; // ecx
  int v19; // eax
  int v20; // edx
  int v21; // eax
  int i; // ebx
  int restarted; // eax
  int v24; // ebx
  int result; // eax

  v5 = v3;
  gssCommsSetCommandBase(1751933793);
  oldmode = readmode();
  blankpal(oldmode, 0, (int)v4, v5);
  SVGA_ON = 0;
  inited = init_screen();
  blankpal(inited, 0, (int)v4, v5);
  SVGA_ON = -1;
  v7 = init_screen();
  v8 = blankpal(v7, 0, (int)v4, v5);
  test_w95(v8, 0, (int)v4, v5);
  v9 = 0;
  harderr((int)criticalhandler, __CS__);
  network_slot = 0;
  if (v5 == 2)
    network_slot = atoi(v4[1]) & 0xFFFFFF;
  v10 = 1;
  LOWORD(player1_car) = 0;
  player2_car = 1;
  name_copy((int)player_names, &aHuman[1]);
  v11 = name_copy((int)&player_names[9 * player2_car], aPlayer2);
  textures_off = 0;
  frontend_on = -1;
  claim_key_int((int)v11, (int)aPlayer2);
  v12 = *v4;
  max_mem = 0;
  setdirectory(v12);
  v13 = 0;
  do {
    v14 = 4 * (__int16)v13++;
    mem_blocks[v14] = 0;
  } while ((__int16)v13 < 128);
  cheat_mode = 0;
  load_language_map();
  load_fatal_config();
  if ((textures_off & 0x2000) != 0) {
    v9 = cheat_mode | 0x40;
    cheat_mode |= 0x40u;
    textures_off ^= 0x2000u;
  }
  if ((textures_off & 0x4000) != 0) {
    false_starts = -1;
    v10 = textures_off;
    BYTE1(v10) = BYTE1(textures_off) ^ 0x40;
    textures_off = v10;
  } else {
    v14 = 0;
    false_starts = 0;
  }
  findintrofiles();
  initmusic();
  tick_on = 0;
  j_unlink(aReplaysReplayT);
  v15 = readsoundconfig(v9);
  loadcheatnames(v15, v14 * 4, 0, v10);
  cdxinit();
  GetFirstCDDrive();
  nullsub_2();
  StopTrack();
  StopTrack();
  print_data = 0;
  TrackSelect = 0;
  Initialise_SOS();
  check_machine_speed();
  if (fatal_ini_loaded) {
    if (view_limit) {
      if (machine_speed >= 2800)
        view_limit = 32;
      else
        view_limit = 24;
    }
  } else {
    if (machine_speed < 9000)
      textures_off |= 0x80000u;
    if (machine_speed < 5000)
      textures_off |= (unsigned int)&loc_3FFFC + 4;
    if (machine_speed < 4600) {
      v16 = textures_off;
      BYTE1(v16) = BYTE1(textures_off) | 8;
      textures_off = v16;
    }
    if (machine_speed < 4300)
      textures_off |= 8u;
    if (machine_speed < 4000)
      view_limit = 32;
    if (machine_speed < 3750) {
      v17 = textures_off;
      LOBYTE(v17) = textures_off | 0x20;
      textures_off = v17;
    }
    if (machine_speed < 3500) {
      v18 = textures_off;
      LOBYTE(v18) = textures_off | 0x10;
      textures_off = v18;
    }
    if (machine_speed < 3250)
      textures_off |= 0x200u;
    if (machine_speed < 3000)
      game_size = 48;
    if (machine_speed < 3800)
      allengines = 0;
    if (machine_speed < 2900)
      replay_record = 0;
    if (machine_speed < 2800)
      view_limit = 24;
  }
  v19 = InitCarStructs();
  init(v19);
  v20 = 0;
  print_data = 0;
  tick_on = 0;
  v21 = copy_screens();
  i = 0;
  title_screens(v21, 0, 0);
  time_to_start = 0;
  replaytype = 2;
  start_race = 0;
  countdown = 144;
  gosound = 3;
  delayread = 0;
  delaywrite = 6;
  writeptr = 0;
  readptr = 0;
  winner_mode = 0;
  intro = -1;
  restarted = play_game(TrackLoad);
  intro = 0;
  VIEWDIST = 270;
  do {
    start_race = 0;
    time_to_start = 0;
    if (restart_net) {
      restarted = restart_net_game();
    } else {
      while (!time_to_start)
        restarted = select_screen(0);
    }
    restart_net = 0;
    countdown = 144;
    gosound = 3;
    delayread = 0;
    delaywrite = 6;
    writeptr = 0;
    readptr = 0;
    if (!quit_game) {
      if (game_type < 3) {
        title_screens(restarted, v20, i);
        v24 = replaytype;
        v20 = -1;
        if (replaytype == 2)
          v20 = 0;
        if (intro)
          v20 = 0;
        net_quit = 0;
        prev_track = TrackLoad;
        restarted = play_game(TrackLoad);
        if (network_buggered) {
          restarted = network_fucked(restarted, v20);
          v20 = 0;
        }
        if (net_quit || network_buggered) {
          v20 = 0;
          if (network_champ_on && (network_buggered != 666 || !restart_net)) {
            game_type = 0;
            network_champ_on = 0;
          }
          if (net_quit)
            restarted = close_network(restarted, 0, v24);
        }
        if (cd_error)
          no_cd();
        i = 270;
        VIEWDIST = 270;
        if (!quit_game) {
          if (v20) {
            restarted = game_type;
            if (game_type) {
              if ((unsigned int)game_type > 1) {
                if (game_type == 2) {
                  StoreResult();
                  for (i = 0; (__int16)i < numcars; ++i) {
                    if (human_control[(__int16)i]) {
                      v20 = 308 * (__int16)i;
                      if (Car_variable_31[v20] > 1)
                        TimeTrials((__int16)i);
                    }
                  }
                  restarted = ShowLapRecords();
                }
                goto LABEL_103;
              }
              finish_race();
              StoreResult();
              if (human_control[carorder[0]] || (cheat_mode & 0x20) != 0) {
                v20 = carorder[0] & 1;
                if (winner_screen((unsigned __int8)Car_variable_22[308 * carorder[0]], v20))
                  winner_race();
              }
              ResultRoundUp();
              RaceResult();
              ChampionshipStandings();
              if (competitors > 8 && (cheat_mode & 0x4000) == 0)
                TeamStandings();
              ShowLapRecords();
              ++Race;
              restarted = prev_track + 1;
              TrackLoad = prev_track + 1;
              if (Race == 8 || (v20 = cheat_mode, (cheat_mode & 0x10) != 0)) {
                restarted = ChampionshipOver();
                goto LABEL_103;
              }
              i = cheat_mode;
              if ((cheat_mode & 0x80u) == 0)
                goto LABEL_103;
            LABEL_83:
              restarted = RollCredits(restarted, v20, i);
              goto LABEL_103;
            }
            if (!gave_up) {
              finish_race();
              StoreResult();
              if (human_control[carorder[0]] || (cheat_mode & 0x20) != 0) {
                v20 = carorder[0] & 1;
                if (winner_screen((unsigned __int8)Car_variable_22[308 * carorder[0]], v20))
                  winner_race();
              }
              ResultRoundUp();
              RaceResult();
              restarted = ShowLapRecords();
            }
            if ((cheat_mode & 0x10) != 0)
              restarted = ChampionshipOver();
            if ((cheat_mode & 0x80) != 0)
              goto LABEL_83;
          LABEL_103:
            if (player_type == 1)
              player_type = 0;
          }
          intro = 0;
        }
      } else if (game_type == 3) {
        restarted = ChampionshipStandings();
        if (competitors > 8) {
          i = cheat_mode;
          if ((cheat_mode & 0x4000) == 0)
            restarted = TeamStandings();
        }
        dontrestart = -1;
      } else {
        restarted = ShowLapRecords();
        dontrestart = -1;
      }
    }
  } while (!quit_game);
  __asm { int     10h; -VIDEO - SET VIDEO MODE }
  doexit();
  return result;
#endif
  return 0;
}

//-------------------------------------------------------------------------------------------------
#ifdef ENABLE_PSEUDO
//-------------------------------------------------------------------------------------------------

int play_game_init()
{
  int v0; // edx
  int v1; // ebx
  int v2; // ebx
  unsigned int v3; // eax
  int v4; // ebp
  int v5; // edx
  int v6; // ebp
  int i; // eax
  int v8; // edx
  int v9; // eax
  __int64 v10; // rax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  __int64 v14; // rax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // ebp
  char *v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // ecx
  int v27; // edx
  int v28; // eax
  int v29; // edx
  int v30; // ecx
  int v31; // edx
  int v32; // eax
  int v33; // eax
  float *v34; // edx
  int v35; // ecx
  double v36; // st7
  double v37; // st6
  int result; // eax
  int v39; // ebp
  int v40; // edx

  DeathView = -1;
  DeathView_variable_1 = -1;
  check_set = 0;
  I_Would_Like_To_Quit = 0;
  Quit_Count = 0;
  dostopsamps = 0;
  my_number = -1;
  network_error = 0;
  network_sync_error = 0;
  network_mistake = 0;
  view1_cnt = 0;
  view0_cnt = 0;
  network_buggered = 0;
  trying_to_exit = 0;
  gave_up = 0;
  define_mode = 0;
  next_resync = -1;
  sync_errors = 0;
  game_frame = -1;
  already_quit = 0;
  if (network_on)
    cd_error = 0;
  send_finished = 0;
  fudge_wait = -1;
  memset(&player_checks, -1, 0x4000);
  memset(&player_syncs, 0, 32);
  read_check = 0;
  write_check = 0;
  if (!svga_possible || no_mem)
    game_svga = 0;
  SVGA_ON = game_svga;
  if (no_mem) {
    fre(&scrbuf);
    scrbuf = getbuffer(64000);
  }
  if (gfx_size == 1)
    min_sub_size = 4;
  else
    min_sub_size = 8;
  cdchecked = 0;
  paused = 0;
  tick_on = 0;
  start_race = 0;
  game_overs = 0;
  if (replaytype != 2) {
    if (game_type == 1 && player_type == 1) {
      network_champ_on = random_seed;
      if (!random_seed)
        network_champ_on = 666;
    } else if (!winner_mode) {
      network_champ_on = 0;
    }
  }
  replay_player = player_type;
  frame_number = 0;
  if (replaytype == 2) {
    replay_cheat = cheat_mode;
    if ((cheat_mode & 0x40) != 0) {
      v0 = textures_off;
      BYTE1(v0) = BYTE1(textures_off) | 0x20;
      textures_off = v0;
      v1 = cheat_mode;
      LOBYTE(v1) = cheat_mode ^ 0x40;
      cheat_mode = v1;
    }
    player_type = 0;
    if (numcars > 0) {
      v2 = 4 * numcars;
      v3 = 0;
      do {
        v3 += 4;
        result_best_variable_1[v3 / 4] = TrackArrow_variable_1[v3 / 4];
      } while ((int)v3 < v2);
    }
  }
  memset(&copy_multiple, 0, 0x8000);
  draw_type = player_type;
  local_players = (player_type == 2) + 1;
  if (network_on) {
    v4 = (player1_car & 1) != 0 ? (__int16)player1_car - 1 : (__int16)player1_car + 1;
    team_mate = v4;
    v5 = non_competitors[v4];
    network_mes_mode = v4;
    if (v5) {
      if (players <= 1) {
        v6 = -1;
      } else {
        v6 = 0;
        for (i = 0; !human_control[i] || v6 == (__int16)player1_car; ++i)
          ++v6;
      }
      network_mes_mode = v6;
      team_mate = -1;
    }
  }
  if (player_type != 2) {
    player2_car = -1;
    ViewType_variable_1 = -1;
  }
  FirstTick = -1;
  dead_humans = 0;
  ticks = 0;
  tick_on = -1;
  load_language_file(aIngameEng);
  v8 = 1;
  v9 = load_language_file(aConfigEng);
  if (frontendspeechptr) {
    printf(&aDfrontEndSpeec[1]);
    doexit();
  }
  if ((cheat_mode & 2) != 0) {
    game_level = level;
    v9 = damage_level;
    game_dam = damage_level;
    damage_level = 3;
    v8 = 0;
    level = 0;
  }
  disable_messages = 0;
  Fatality = -1;
  Destroyed = 0;
  ahead_sect = -2;
  ahead_time = 0;
  game_count = -2;
  game_count_variable_1 = -2;
  game_scale = 1191182336;
  game_scale_variable_1 = 1191182336;
  Joy1used = 0;
  Joy2used = 0;
  check_joystick_usage(v9, v8);
  memset(&repsample, 1, 16);
  qmemcpy(&newrepsample, &repsample, 0x10u);
  autoswitch = -1;
  game_req = 0;
  v10 = getbuffer(32000);
  mirbuf = v10;
  screenready = 0;
  racing = HIDWORD(v10);
  if (replaytype != 2)
    replayedit = 0;
  if (!winner_mode) {
    SelectedView = game_view;
    SelectedView_variable_1 = game_view_variable_1;
  }
  race_started = 0;
  rud_turn = 0;
  finishers = 0;
  human_finishers = 0;
  setreplaytrack();
  v11 = loadtrack(game_track, 0);
  v12 = LoadGenericCarTextures(v11);
  InitCars(v12);
  if (game_type >= 2) {
    NoOfLaps = 5;
    if (network_on)
      countdown = 144;
    else
      countdown = -72;
  } else {
    v13 = cur_laps[level];
    NoOfLaps = v13;
    if (competitors == 2)
      NoOfLaps = v13 / 2;
    if (infinite_laps)
      NoOfLaps = 0;
  }
  v14 = startreplay();
  LODWORD(v14) = LoadPanel(v14, HIDWORD(v14));
  v15 = initclouds(v14);
  if (!w95 || MusicCD) {
    if (!winner_mode && !loading_replay) {
      if (replaytype == 2)
        v16 = titlesong;
      else
        v16 = TrackLoad;
      v15 = startmusic(v16);
    }
    holdmusic = -1;
  }
  v17 = loadsamples(v15);
  v18 = initcollisions(v17);
  initsounds(v18);
  fade_palette(0);
  init_screen();
  if (intro || replaytype == 2) {
    v19 = network_mes_mode;
    if (SVGA_ON)
      scr_size = 128;
    else
      scr_size = 64;
  } else {
    v19 = network_mes_mode;
    scr_size = game_size;
  }
  network_mes_mode = v19;
  clear_borders = -1;
  if ((((unsigned int)&loc_1FFFD + 3) & cheat_mode) != 0)
    v20 = aCheatpalPal;
  else
    v20 = &aNdPalettePal[3];
  v21 = setpal(v20);
  v22 = FindShades(v21);
  InitRemaps(v22);
  if (player_type == 2) {
    if (!DuoViews[SelectedView])
      viewplus(0);
    if (!DuoViews[SelectedView_variable_1])
      viewplus(1);
  } else if (SelectedView == 7) {
    v23 = (ViewType & 1) != 0 ? ViewType - 1 : ViewType + 1;
    if (Car_variable_23[308 * v23] < 0)
      SelectedView = 0;
  }
  v24 = select_view(0);
  if (Play_View == 1)
    v25 = doteaminit(v24);
  else
    v25 = initcarview((__int16)player1_car, 0);
  if (player_type == 2) {
    select_view(1);
    v25 = initcarview(player2_car, 1);
  }
  initnearcars(v25);
  ticks = 0;
  p_eng = (int)&CarEngines[28 * (unsigned __int8)Car_variable_22[308 * (__int16)player1_car]];
  if (player_type == 2)
    p_eng_variable_1 = (int)&CarEngines[28 * (unsigned __int8)Car_variable_22[308 * player2_car]];
  v26 = *(_DWORD *)(p_eng + 72) + 2 * *(_DWORD *)(p_eng + 76);
  v27 = *(_DWORD *)(p_eng + 92);
  p_joyk1 = ((v27 * (*(_DWORD *)(p_eng + 72) - *(_DWORD *)(p_eng + 76))) << 8) / v26;
  v28 = ((3 * v27 * *(_DWORD *)(p_eng + 76)) << 16) / v26;
  v29 = ((3 * v27 * *(_DWORD *)(p_eng + 76)) << 16) % v26;
  p_joyk2 = v28;
  if (player_type == 2) {
    v30 = *(_DWORD *)(p_eng_variable_1 + 72) + 2 * *(_DWORD *)(p_eng_variable_1 + 76);
    v31 = *(_DWORD *)(p_eng_variable_1 + 92);
    p_joyk1_variable_1 = ((v31 * (*(_DWORD *)(p_eng_variable_1 + 72) - *(_DWORD *)(p_eng_variable_1 + 76))) << 8) / v30;
    v32 = ((3 * v31 * *(_DWORD *)(p_eng_variable_1 + 76)) << 16) / v30;
    v29 = ((3 * v31 * *(_DWORD *)(p_eng_variable_1 + 76)) << 16) % v30;
    p_joyk2_variable_1 = v32;
  }
  start_race = -1;
  set_palette(0, v29);
  v33 = 0;
  fadedin = 0;
  totaltrackdistance = 0;
  if (TRAK_LEN > 0) {
    v34 = (float *)&localdata;
    v35 = TRAK_LEN;
    v36 = (double)totaltrackdistance;
    do {
      v37 = threed_c_variable_31 * v34[12] + v36;
      v34 += 32;
      _CHP(v33 + 1, v34);
      v36 = v37;
    } while (v33 < v35);
    totaltrackdistance = (int)v37;
  }
  result = totaltrackdistance / TRAK_LEN;
  v39 = network_mes_mode;
  averagesectionlen = totaltrackdistance / TRAK_LEN;
  if (winner_mode || game_type == 2) {
    if (numcars > 0) {
      result = 0;
      v40 = 308 * numcars;
      do {
        result += 308;
        CarBox_variable_25[result] = 0;
        *(int *)((char *)&CarBox_variable_24 + result) = 0;
      } while (result < v40);
    }
    race_started = -1;
  }
  network_mes_mode = v39;
  return result;
}

//-------------------------------------------------------------------------------------------------

int play_game_uninit()
{
  int v0; // edx
  int v1; // eax
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int result; // eax
  int v6; // eax
  int v7; // ebx

  _disable();
  if (!winner_mode && replaytype != 2 && network_on) {
    name_copy((int)player_names, &player_names[9 * wConsoleNode]);
    manual_control[0] = manual_control[wConsoleNode];
    player_invul[0] = player_invul[wConsoleNode];
    Players_Cars[0] = Players_Cars[wConsoleNode];
    wConsoleNode = 0;
  }
  frontend_on = -1;
  _enable();
  v0 = replaytype;
  if (replaytype == 2)
    cheat_mode = replay_cheat;
  if ((cheat_mode & 2) != 0) {
    level = game_level;
    damage_level = game_dam;
  }
  if (replaytype != 2 && !winner_mode) {
    game_size = scr_size;
    game_svga = SVGA_ON;
    v1 = DeathView;
    if (DeathView < 0)
      v1 = SelectedView[0];
    game_view = v1;
    if (DeathView_variable_1[0] < 0)
      game_view_variable_1 = SelectedView_variable_1;
    else
      game_view_variable_1 = DeathView_variable_1[0];
    result_p1 = (__int16)player1_car;
    if (player_type == 2)
      result_p2 = player2_car;
  }
  if (replaytype == 2) {
    if ((textures_off & 0x2000) != 0) {
      textures_off ^= 0x2000u;
      cheat_mode |= 0x40u;
    }
    player_type = replay_player;
  }
  stopreplay();
  tick_on = 0;
  if (network_error == 666) {
    network_buggered = 666;
  } else if (network_sync_error) {
    network_buggered = 456;
  } else {
    network_buggered = network_error;
  }
  network_error = 0;
  network_sync_error = 0;
  v2 = fade_palette(0);
  if (!loading_replay)
    v2 = stopmusic(v2);
  v3 = stopallsamples(v2);
  v4 = releasesamples(v3);
  result = free_game_memory(v4);
  if (v0 == 2) {
    network_buggered = 0;
    if (numcars > 0) {
      v7 = 4 * numcars;
      result = 0;
      do {
        result += 4;
        *(int *)((char *)TrackArrow_variable_1 + result) = *(int *)((char *)result_best_variable_1 + result);
      } while (result < v7);
    }
  } else {
    v6 = SaveRecords(result);
    result = save_fatal_config(v6);
  }
  if (no_mem) {
    fre(&scrbuf);
    result = getbuffer(0x3E800u);
    scrbuf = result;
  }
  tick_on = -1;
  return result;
}

//-------------------------------------------------------------------------------------------------

int winner_race()
{
  int v0; // ecx
  int v1; // eax
  int v2; // edx
  int v3; // edx
  int v4; // edx
  int v5; // ebx
  int result; // eax
  int v7; // ecx
  int v8; // ebx

  v0 = numcars;
  v1 = 0;
  if (numcars > 0) {
    v2 = 0;
    do {
      finished_car_variable_1[++v2] = v1++;
      TrackArrow_variable_1[v2] = -1;
    } while (v1 < v0);
  }
  v3 = carorder[0];
  winner_mode = -1;
  winner_done = 0;
  ViewType = carorder[0];
  if (prev_track >= 17)
    SelectedView[0] = 1;
  else
    SelectedView[0] = 4;
  grid[0] = carorder[0];
  champ_zoom = 0;
  non_competitors[carorder[0]] = 0;
  human_control[v3] = 0;
  grid[v3] = 0;
  start_race = 0;
  countdown = -36;
  gosound = 3;
  delayread = 0;
  delaywrite = 6;
  writeptr = 0;
  readptr = 0;
  v4 = racers;
  v5 = player_type;
  numcars = v0;
  player_type = 0;
  replaytype = 0;
  racers = 1;
  play_game(prev_track);
  result = 270;
  v7 = numcars;
  winner_mode = 0;
  racers = v4;
  player_type = v5;
  VIEWDIST = 270;
  if (numcars > 0) {
    v8 = 4 * numcars;
    result = 0;
    do {
      result += 4;
      *(int *)((char *)TrackArrow_variable_1 + result) = *(int *)((char *)result_best_variable_1 + result);
    } while (result < v8);
  }
  numcars = v7;
  return result;
}

//-------------------------------------------------------------------------------------------------

int champion_race()
{
  int v0; // ebx
  unsigned int v1; // eax
  int v2; // eax
  int v3; // ecx
  int v4; // ebx
  int v5; // edx
  int v6; // esi
  int v7; // edx
  int v8; // ecx
  int v9; // edi
  int i; // eax
  int v11; // ebx
  int v12; // edx
  int v13; // edx
  unsigned int v14; // eax
  int v15; // ebx
  int result; // eax
  int v17; // [esp+0h] [ebp-20h]
  int v18; // [esp+4h] [ebp-1Ch]

  v17 = TrackLoad;
  champ_size = scr_size;
  if (game_type != 1 && numcars > 0) {
    v0 = 4 * numcars;
    v1 = 0;
    do {
      v1 += 4;
      teamorder_variable_1[v1 / 4] = result_lap_variable_1[v1 / 4];
    } while ((int)v1 < v0);
  }
  v18 = champ_track[champorder[0] / 2];
  v2 = 0;
  if (racers > 0) {
    v3 = racers;
    v4 = 0;
    do {
      ++v4;
      v5 = champorder[v3 - 1 - v2++];
      finished_car_variable_1[v4] = v5;
      non_competitors[v5] = 0;
      human_control[v5] = 0;
    } while (v2 < v3);
  }
  v6 = racers;
  v7 = 0;
  if (racers < numcars) {
    v8 = 4 * racers;
    v9 = 4 * numcars;
    do {
      for (i = v7; !result_competing[i]; ++i)
        ++v7;
      ++v6;
      grid[v8 / 4u] = v7;
      v8 += 4;
      human_control[i] = 0;
      non_competitors[i] = -1;
      ++v7;
    } while (v8 < v9);
  }
  v11 = racers;
  winner_mode = -1;
  winner_done = 0;
  champ_mode = -1;
  champ_zoom = 0;
  SelectedView[0] = 8;
  v12 = teamorder_variable_1[racers];
  champ_car = racers - 1;
  ViewType = v12;
  champ_go[v12] = -1;
  start_race = 0;
  countdown = -36;
  gosound = 3;
  delayread = 0;
  delaywrite = 6;
  writeptr = 0;
  readptr = 0;
  v13 = player_type;
  replaytype = 0;
  player_type = 0;
  play_game(v18);
  VIEWDIST = 270;
  winner_mode = 0;
  champ_mode = 0;
  racers = v11;
  player_type = v13;
  TrackLoad = v17;
  if (numcars > 0) {
    v14 = 0;
    v15 = 4 * numcars;
    do {
      v14 += 4;
      TrackArrow_variable_1[v14 / 4] = result_best_variable_1[v14 / 4];
    } while ((int)v14 < v15);
  }
  result = champ_size;
  scr_size = champ_size;
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall play_game(int a1)
{
  int v1; // eax
  int v2; // eax
  int v3; // ecx
  int v4; // edx
  int v5; // eax
  __int16 i; // bx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  bool v10; // eax
  bool v11; // eax
  bool v12; // eax
  int v13; // eax

  game_track = a1;
  lagdone = 0;
  I_Want_Out = 0;
  v1 = play_game_init();
  reset_net_wait(v1);
  max_mem = mem_used_low + mem_used;
  enable_keyboard();
  pend_view_init = ViewType;
  _disable();
  network_limit = 4320;
  v2 = 0;
  do {
    v3 = (__int16)v2;
    v4 = frames;
    ++v2;
    net_time[v3] = frames;
  } while ((__int16)v2 < 16);
  v5 = frames;
  network_timeout = frames;
  network_error = 0;
  network_sync_error = 0;
  frontend_on = 0;
  _enable();
  while (racing || lastsample > 0) {
    if (dostopsamps) {
      stopallsamples(v5);
      dostopsamps = 0;
    }
    if (network_on) {
      if (frame_number >= 250)
        countdown = -75;
      if (countdown == 144 && replaytype != 2 && fadedin)
        send_ready();
      if (network_limit == 4320 && countdown < 140) {
        v4 = 360;
        _disable();
        network_limit = 360;
        for (i = 0; ; ++i) {
          v7 = i;
          if (i >= network_on)
            break;
          v4 = frames;
          net_time[v7] = frames;
        }
        network_timeout = frames;
        _enable();
      }
    }
    if (player_type == 1 && (network_error || network_sync_error || cd_error))
      racing = 0;
    if (fadedin && !lagdone && (countdown < 140 || replaytype == 2)) {
      initsoundlag(0);
      lagdone = -1;
    }
    if (champ_mode < 16)
      control();
    else
      firework_display();
    if (!replayspeed && intro && !game_req)
      racing = replayspeed;
    if (track_playing) {
      v4 = 36 * track_duration / 75;
      if (frames - start_cd > v4) {
        v8 = StopTrack();
        RepeatTrack(v8);
        start_cd = frames;
      }
    }
    if (network_on) {
      if (net_quit) {
        v4 = intro;
        if (!intro)
          racing = 0;
      }
    }
    if (player_type == 2) {
      if (Car_variable_23[308 * (__int16)player1_car] < 0
        && Car_variable_23[308 * player2_car] < 0
        && lastsample < -72
        && readsample == writesample
        && player_type != replaytype) {
        racing = 0;
      }
    } else if (!network_on
           && Car_variable_23[308 * (__int16)player1_car] < 0
           && lastsample < -72
           && readsample == writesample
           && replaytype != 2) {
      racing = writesample ^ readsample;
    }
    if (winner_mode) {
      if (winner_done && lastsample < -72 && readsample == writesample) {
        racing = 0;
      } else {
        racing = -1;
        if (champ_mode) {
          if (champ_mode >= 16 && champ_zoom > 7 && champ_count < 0 && !winner_done) {
            v4 = 0x8000;
            speechsample(114, 0x8000, 18, (__int16)player1_car);
            winner_done = -1;
          }
          if (!winner_done && champ_mode == 2) {
            v4 = 0x8000;
            speechsample(114, 0x8000, 18, (__int16)player1_car);
            ++champ_mode;
          }
          if (champ_mode == 3 && lastsample < -72) {
            v4 = writesample;
            if (readsample == writesample) {
              holdmusic = -1;
              fade_palette(writesample ^ readsample);
              ++champ_mode;
              firework_screen();
              fade_palette(32);
              champ_count = 720;
              champ_zoom = 3;
              champ_mode = 16;
              memset(CarSpray, 0, 792);
              if (SVGA_ON)
                scr_size = 128;
              else
                scr_size = 64;
              v4 = 0;
              winw = XMAX;
              winx = 0;
              winy = 0;
              winh = YMAX;
            }
          }
        } else if (Car_variable_31[308 * ViewType] > 1 && !winner_done) {
          v4 = 0x8000;
          speechsample(114, 0x8000, 18, (__int16)player1_car);
          winner_done = -1;
        }
      }
    }
    if (champ_mode < 16)
      updatescreen();
    else
      firework_screen();
    if (print_data)
      printf(&threed_c_variable_32);
    print_data = 0;
    if (pause_request && !intro) {
      if (!pausewindow || !paused) {
        if (network_on && replaytype != 2) {
          if (wConsoleNode == master) {
            if (!finished_car[(__int16)player1_car]) {
              v11 = paused == 0;
              paused = v11;
              if (v11)
                stopallsamples(v11);
              if (paused)
                pauser = wConsoleNode;
              transmitpausetoslaves();
            }
          } else if (!finished_car[(__int16)player1_car]) {
            send_pause();
          }
        } else {
          if (game_req) {
            clear_borders = -1;
            scr_size = req_size;
            v9 = remove_uncalibrated(req_size);
            check_joystick_usage(v9, v4);
          } else {
            req_size = scr_size;
            if (SVGA_ON)
              scr_size = 128;
            else
              scr_size = 64;
          }
          control_edit = -1;
          req_edit = 0;
          game_req = game_req == 0;
          pausewindow = 0;
          v10 = paused == 0;
          paused = v10;
          if (v10)
            stopallsamples(v10);
        }
      }
      v4 = 0;
      pause_request = 0;
    }
    if (network_on && slave_pause && wConsoleNode == master) {
      v12 = paused == 0;
      paused = v12;
      if (v12)
        stopallsamples(v12);
      transmitpausetoslaves();
      slave_pause = 0;
    }
    if (!filingmenu)
      game_keys();
    if (replaytype == 2) {
      if (SVGA_ON)
        scr_size = 128;
      else
        scr_size = 64;
    }
    if (!racing && !winner_done && winner_mode) {
      v4 = 0x8000;
      speechsample(114, 0x8000, 18, (__int16)player1_car);
      winner_done = -1;
      racing = -1;
    }
    v5 = keys_variable_3 || keys_variable_4;
    shifting = v5;
    if (v5 && keys_variable_8 || keys_variable_2 && controlicon == 8) {
      if (shifting && keys_variable_8)
        controlicon = 9;
      v4 = 0;
      slowing = 0;
      if (!rewinding)
        v5 = Rrewindstart();
    } else if (rewinding) {
      slowing = -1;
    }
    if (shifting && keys_variable_9 || keys_variable_2 && controlicon == 10) {
      if (shifting && keys_variable_9)
        controlicon = 9;
      v5 = 0;
      v4 = forwarding;
      slowing = 0;
      if (!forwarding)
        v5 = Rforwardstart();
    } else if (forwarding) {
      slowing = -1;
    }
    if (screenready) {
      if (!fadedin) {
        v5 = fade_palette(32);
        v4 = w95;
        fadedin = -1;
        holdmusic = 0;
        if (w95) {
          if (!MusicCD && !winner_mode && !loading_replay) {
            if (replaytype == 2)
              v13 = titlesong;
            else
              v13 = game_track;
            v5 = startmusic(v13);
          }
        }
      }
    }
    if (!intro && replaytype != 2) {
      v5 = player_type;
      if (player_type && player_type != 2) {
        if (!cdchecked) {
          if (active_nodes == network_on)
            cdchecked = -1;
          v5 = wConsoleNode;
          if (wConsoleNode == master && !netCD) {
            v5 = active_nodes;
            if (active_nodes == network_on) {
              v5 = send_nocd_error();
              cd_error = -1;
              cdchecked = -1;
            }
          }
        }
      } else {
        v5 = localCD;
        if (!localCD) {
          racing = 0;
          cd_error = -1;
        }
      }
    }
  }
  return play_game_uninit();
}

//-------------------------------------------------------------------------------------------------

void game_keys()
{
  unsigned int v0; // eax
  int v1; // eax
  int v2; // eax
  int v3; // eax
  int v4; // eax
  _BOOL1 v5; // zf
  bool v6; // eax
  bool v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  bool v12; // eax

  if (define_mode)
    LABEL_328:
  JUMPOUT(0x1381B);
  while (1) {
    do {
      while (1) {
        do {
          while (1) {
            while (1) {
              while (1) {
              LABEL_2:
                if (!fatkbhit())
                  goto LABEL_328;
                v0 = fatgetch();
                if (intro || winner_mode) {
                  if (v0) {
                    v0 = -1;
                    racing = 0;
                  } else {
                    fatgetch();
                    v0 = -1;
                  }
                }
                if (trying_to_exit) {
                  if (v0) {
                    if (v0 == 121 || v0 == 89) {
                      racing = 0;
                      quit_game = -1;
                      scr_size = req_size;
                    }
                    trying_to_exit = 0;
                  } else {
                    trying_to_exit = 0;
                    fatgetch();
                  }
                  v0 = -1;
                }
                if (v0)
                  break;
                v1 = fatgetch();
                if (v1 != 75 && v1 != 77 && v1 != 72 && v1 != 80) {
                  if (keys_variable_3 || keys_variable_4) {
                    v1 += 25;
                  } else if (keys_variable_5) {
                    v1 += 45;
                  }
                }
                v2 = v1 - 59;
                switch (v2) {
                  case 0:
                    if (network_on)
                      v2 = mesminus();
                    if (replaytype == 2)
                      carminus(v2);
                    break;
                  case 1:
                    if (network_on)
                      v2 = mesplus();
                    if (replaytype == 2)
                      carplus(v2);
                    break;
                  case 2:
                    if (view0_cnt < 0) {
                      view0_cnt = 18;
                      viewminus(0);
                    }
                    break;
                  case 3:
                    if (view0_cnt < 0) {
                      view0_cnt = 18;
                      viewplus(0);
                    }
                    break;
                  case 6:
                    if (player_type == 2 && view1_cnt < 0) {
                      view1_cnt = 18;
                      viewminus(1);
                    }
                    break;
                  case 7:
                    if (player_type == 2 && view1_cnt < 0) {
                      view1_cnt = 18;
                      viewplus(1);
                    }
                    break;
                  case 8:
                    if (++names_on > 2)
                      names_on = 0;
                    break;
                  case 9:
                    if (I_Would_Like_To_Quit && Quit_Count <= 0) {
                      I_Want_Out = -1;
                      stopallsamples(v2);
                    }
                    break;
                  case 11:
                    showversion = showversion == 0;
                    break;
                  case 13:
                    if (game_req) {
                      if (!pausewindow && req_edit > 0)
                        --req_edit;
                      if (pausewindow == 1 && !calibrate_mode && calibrate_select < pausewindow)
                        calibrate_select += pausewindow;
                      if (pausewindow == 2 && control_select < 2)
                        ++control_select;
                      if (pausewindow == 3 && graphic_mode < 16)
                        ++graphic_mode;
                      if (pausewindow == 4) {
                        if (sound_edit <= 1) {
                          if (!sound_edit)
                            sound_edit = 7;
                        } else {
                          --sound_edit;
                        }
                      }
                    } else if (replaytype == 2 && game_req != replaypanel) {
                      switch (game_req + controlicon) {
                        case 7:
                        case 8:
                        case 15:
                        case 16:
                        case 17:
                          controlicon -= 6;
                          break;
                        case 9:
                        case 10:
                        case 11:
                        case 12:
                        case 13:
                        case 14:
                          controlicon -= 5;
                          break;
                        default:
                          continue;
                      }
                    }
                    break;
                  case 16:
                    if (game_req) {
                      if (pausewindow == 4) {
                        switch (sound_edit) {
                          case 1:
                            EngineVolume -= pausewindow;
                            if (EngineVolume < 0)
                              EngineVolume = 0;
                            continue;
                          case 2:
                            SFXVolume -= pausewindow;
                            if (SFXVolume < 0)
                              SFXVolume = 0;
                            continue;
                          case 3:
                            SpeechVolume -= pausewindow;
                            if (SpeechVolume < 0)
                              SpeechVolume = 0;
                            continue;
                          case 4:
                            MusicVolume -= pausewindow;
                            if (MusicVolume < 0)
                              MusicVolume = 0;
                            if (MusicCard)
                              sosMIDISetMasterVolume((unsigned __int8)MusicVolume);
                            if (MusicCD)
                              goto LABEL_82;
                            continue;
                          default:
                            continue;
                        }
                      }
                    } else if (replaytype == 2
                           && game_req != replaypanel
                           && controlicon != 1
                           && controlicon != 7
                           && controlicon != 12) {
                      --controlicon;
                    }
                    break;
                  case 18:
                    v3 = game_req;
                    if (game_req) {
                      if (pausewindow == 4) {
                        switch (sound_edit) {
                          case 1:
                            EngineVolume += 4;
                            if (EngineVolume >= 128)
                              EngineVolume = 127;
                            break;
                          case 2:
                            SFXVolume += pausewindow;
                            if (SFXVolume >= 128)
                              SFXVolume = 127;
                            break;
                          case 3:
                            SpeechVolume += pausewindow;
                            if (SpeechVolume >= 128)
                              SpeechVolume = 127;
                            break;
                          case 4:
                            MusicVolume += pausewindow;
                            if (MusicVolume >= 128)
                              MusicVolume = 127;
                            if (MusicCard)
                              sosMIDISetMasterVolume((unsigned __int8)MusicVolume);
                            if (MusicCD)
                              LABEL_82:
                            SetAudioVolume(MusicVolume);
                            break;
                          default:
                            continue;
                        }
                      }
                    } else if (replaytype == 2
                           && game_req != replaypanel
                           && controlicon != 6
                           && controlicon != 11
                           && controlicon != 25) {
                      if (controlicon != 17 || game_req != replayedit)
                        v3 = 1;
                      if (v3)
                        ++controlicon;
                    }
                    break;
                  case 21:
                    if (game_req) {
                      if (!pausewindow && req_edit < 6)
                        ++req_edit;
                      if (pausewindow == 1 && calibrate_select > 0 && !calibrate_mode)
                        calibrate_select -= pausewindow;
                      if (pausewindow == 2 && control_select > 0)
                        --control_select;
                      if (pausewindow == 3 && graphic_mode > 0)
                        --graphic_mode;
                      if (pausewindow == 4 && sound_edit > 0) {
                        if (sound_edit >= 7)
                          sound_edit = 0;
                        else
                          ++sound_edit;
                      }
                    } else if (replaytype == 2 && game_req != replaypanel) {
                      switch (controlicon) {
                        case 1:
                        case 2:
                        case 3:
                        case 9:
                        case 10:
                        case 11:
                          controlicon += 6;
                          break;
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                          controlicon += 5;
                          break;
                        default:
                          continue;
                      }
                    }
                    break;
                  case 25:
                    controlicon = 9;
                    Rreverseplay();
                    break;
                  case 26:
                    controlicon = 9;
                    Rplay();
                    break;
                  case 27:
                    controlicon = 9;
                    Rspeedminus();
                    break;
                  case 28:
                    controlicon = 9;
                    Rspeedplus();
                    break;
                  case 29:
                    controlicon = 9;
                    Rframeminus();
                    break;
                  case 30:
                    controlicon = 9;
                    Rframeplus();
                    break;
                  case 33:
                    controlicon = 9;
                    Rstart();
                    break;
                  case 34:
                    controlicon = 9;
                    Rend();
                    break;
                  case 45:
                    controlicon = 9;
                    rtoggleedit();
                    break;
                  case 46:
                    controlicon = 9;
                    rstartblock();
                    break;
                  case 47:
                    controlicon = 9;
                    rselectblock();
                    break;
                  case 48:
                    controlicon = 9;
                    rdeleteblock();
                    break;
                  case 49:
                    controlicon = 9;
                    rstoreview();
                    break;
                  case 50:
                    controlicon = 9;
                    rremoveview();
                    break;
                  case 51:
                    controlicon = 9;
                    rpreviouscut();
                    break;
                  case 52:
                    controlicon = 9;
                    rnextcut();
                    break;
                  case 53:
                    controlicon = 9;
                    rstartassemble();
                    break;
                  default:
                    continue;
                }
              }
              if (v0 < 0x2D)
                break;
              if (v0 <= 0x2D) {
              LABEL_313:
                if (replaytype != 2) {
                  if (game_req) {
                    if (pausewindow == 3 && graphic_mode == 2) {
                      if (SVGA_ON) {
                        req_size -= 16;
                        if (req_size < 64)
                          req_size = 64;
                      } else {
                        req_size -= 8;
                        if (req_size < 32)
                          req_size = 32;
                      }
                    }
                  } else if (SVGA_ON) {
                    scr_size -= 16;
                    if (scr_size >= 64)
                      goto LABEL_318;
                    scr_size = 64;
                  } else {
                    scr_size -= 8;
                    if (scr_size >= 32)
                      LABEL_318:
                    clear_borders = -1;
                    else
                      scr_size = 32;
                  }
                }
              } else if (v0 < 0x4C) {
                if (v0 >= 0x3D) {
                  if (v0 <= 0x3D) {
                  LABEL_291:
                    if (replaytype != 2) {
                      if (game_req) {
                        if (pausewindow == 3 && graphic_mode == 2) {
                          if (SVGA_ON) {
                            req_size += 16;
                            if (req_size > 128)
                              req_size = 128;
                            if (req_size == 128)
                              replaypanel = -1;
                          } else {
                            req_size += 8;
                            if (req_size > 64)
                              req_size = 64;
                            if (req_size == 64)
                              replaypanel = -1;
                          }
                        }
                      } else if (SVGA_ON) {
                        scr_size += 16;
                        if (scr_size > 128)
                          scr_size = 128;
                        if (scr_size == 128)
                          replaypanel = -1;
                      } else {
                        scr_size += 8;
                        if (scr_size > 64)
                          scr_size = 64;
                        if (scr_size == 64)
                          replaypanel = -1;
                      }
                    }
                  } else if (v0 == 68) {
                    if (keys_variable_5) {
                      controlicon = 9;
                      if (replaytype == 2)
                        filingmenu = 3;
                    }
                  }
                }
              } else if (v0 <= 0x4C) {
                if (keys_variable_5) {
                  controlicon = 9;
                  if (replaytype == 2)
                    filingmenu = 1;
                }
              } else if (v0 >= 0x53) {
                if (v0 <= 0x53) {
                  if (keys_variable_5) {
                    controlicon = 9;
                    if (replaytype == 2)
                      filingmenu = 2;
                  }
                } else if (v0 == 95) {
                  goto LABEL_313;
                }
              }
            }
            if (v0 < 0x1B)
              break;
            if (v0 <= 0x1B) {
              if (game_req && pausewindow) {
                if (pausewindow == 1 || pausewindow == 2)
                  remove_uncalibrated(pausewindow);
                pausewindow = 0;
              } else if (filingmenu) {
                filingmenu = 0;
                lastfile = 0;
              } else if (!network_on || replaytype == 2) {
              LABEL_194:
                pause_request = -1;
              } else if (active_nodes == network_on) {
                if (I_Would_Like_To_Quit == -1) {
                  if (Quit_Count <= 0)
                    I_Would_Like_To_Quit = 0;
                } else {
                  I_Would_Like_To_Quit = -1;
                  Quit_Count = 18;
                }
              }
            } else if (v0 >= 0x20) {
              if (v0 <= 0x20) {
                if (replaytype == 2) {
                  replaypanel = replaypanel == 0;
                  controlicon = 9;
                  rotpoint = currentreplayframe;
                }
              } else if (v0 == 43) {
                goto LABEL_291;
              }
            }
          }
        } while (v0 != 13);
        if (!game_req)
          break;
        switch (pausewindow) {
          case 0:
            switch (req_edit) {
              case 0:
                goto LABEL_194;
              case 1:
                paused = 0;
                racing = 0;
                gave_up = -1;
                scr_size = req_size;
                goto LABEL_2;
              case 2:
                sound_edit = 0;
                pausewindow = 4;
                goto LABEL_2;
              case 3:
                calibrate_select = 0;
                calibrate_mode = 0;
                pausewindow = 1;
                goto LABEL_2;
              case 4:
                pausewindow = 2;
                Joy1used = 0;
                Joy2used = 0;
                controlrelease = -1;
                define_mode = 0;
                control_select = 0;
                control_edit = -1;
                goto LABEL_2;
              case 5:
                graphic_mode = 0;
                pausewindow = 3;
                goto LABEL_2;
              case 6:
                trying_to_exit = -1;
                goto LABEL_2;
              default:
                goto LABEL_2;
            }
          case 1:
            if (calibrate_select) {
              if (calibrate_select == 1) {
                v6 = calibrate_mode == 0;
                v5 = calibrate_mode != 0;
                calibrate_mode = v6;
                if (v5)
                  remove_uncalibrated(v6);
                else
                  check_joystickpresence();
              }
            } else {
              pausewindow = 0;
              v4 = remove_uncalibrated(0);
              check_joystick_usage(v4, 0);
              calibrate_mode = 0;
            }
            break;
          case 2:
            if (control_select) {
              if ((unsigned int)control_select <= 1) {
                define_mode = -1;
                control_edit = 0;
                disable_keyboard(control_select);
                controlrelease = -1;
                qmemcpy(&oldkeys, &userkey, 0xCu);
                qmemcpy((char *)&oldkeys + 12, &userkey + 12, 2u);
              } else if (control_select == 2) {
                define_mode = -1;
                control_edit = 6;
                disable_keyboard(6);
                controlrelease = -1;
                qmemcpy(&oldkeys, &userkey, 0xCu);
                qmemcpy((char *)&oldkeys + 12, &userkey + 12, 2u);
              }
            } else {
            LABEL_212:
              pausewindow = 0;
            }
            break;
          case 3:
            switch (graphic_mode) {
              case 0:
                goto LABEL_212;
              case 1:
                if (svga_possible && !no_mem || SVGA_ON) {
                  v7 = SVGA_ON == 0;
                  SVGA_ON = v7;
                  init_screen(v7, 0, 2);
                  req_size = scr_size;
                }
                goto LABEL_2;
              case 2:
                if (replaytype != 2) {
                  if (SVGA_ON) {
                    req_size += 16;
                    if (req_size > 128)
                      req_size = 64;
                    if (req_size == 128)
                      replaypanel = -1;
                  } else {
                    req_size += 8;
                    if (req_size > 64)
                      req_size = 32;
                    if (req_size == 64)
                      replaypanel = -1;
                  }
                }
                goto LABEL_2;
              case 3:
                if (view_limit) {
                  view_limit = 0;
                } else if (machine_speed >= 2800) {
                  view_limit = 32;
                } else {
                  view_limit = 24;
                }
                goto LABEL_2;
              case 4:
                if ((textures_off & 0x20) != 0) {
                  v8 = textures_off;
                  LOBYTE(v8) = textures_off ^ 0x20;
                  textures_off = ((unsigned int)&loc_3FFFC + 4) | v8;
                } else if ((((unsigned int)&loc_3FFFC + 4) & textures_off) != 0) {
                  textures_off ^= (unsigned int)&loc_3FFFC + 4;
                } else {
                  textures_off |= 0x20u;
                }
                goto LABEL_2;
              case 5:
                textures_off ^= 8u;
                goto LABEL_2;
              case 6:
                textures_off ^= 0x100u;
                goto LABEL_2;
              case 7:
                textures_off ^= 2u;
                goto LABEL_2;
              case 8:
                v9 = textures_off;
                LOBYTE(v9) = textures_off ^ 0x80;
                textures_off = v9;
                goto LABEL_2;
              case 9:
                textures_off ^= 1u;
                goto LABEL_2;
              case 10:
                textures_off ^= 4u;
                goto LABEL_2;
              case 11:
                v10 = textures_off;
                LOBYTE(v10) = textures_off ^ 0x40;
                textures_off = v10;
                goto LABEL_2;
              case 12:
                v11 = textures_off;
                LOBYTE(v11) = textures_off ^ 0x10;
                textures_off = v11;
                goto LABEL_2;
              case 13:
                textures_off ^= 0x800u;
                goto LABEL_2;
              case 14:
                textures_off ^= 0x200u;
                goto LABEL_2;
              case 15:
                if (++names_on > 2)
                  names_on = 0;
                goto LABEL_2;
              case 16:
                textures_off ^= 0x80000u;
                goto LABEL_2;
              default:
                goto LABEL_2;
            }
          case 4:
            switch (sound_edit) {
              case 0:
                goto LABEL_212;
              case 5:
                allengines = allengines == 0;
                goto LABEL_2;
              case 6:
                if (SoundCard) {
                  v12 = soundon == 0;
                  v5 = soundon != 0;
                  soundon = v12;
                  if (!v5)
                    loadsamples(v12);
                } else {
                  soundon = 0;
                }
                goto LABEL_2;
              case 7:
                if (MusicCard || MusicCD) {
                  musicon = musicon == 0;
                  reinitmusic();
                } else {
                  musicon = 0;
                }
                goto LABEL_2;
              default:
                goto LABEL_2;
            }
          default:
            goto LABEL_2;
        }
      }
    } while (replaytype != 2 || game_req == replaypanel && controlicon != 9 || !ricon_variable_2[2 * controlicon]);
    if ((unsigned int)controlicon < 0xE) {
    LABEL_273:
      ((void (*)(void))ricon_variable_2[2 * controlicon])();
    } else if ((unsigned int)controlicon <= 0xE) {
      viewminus(0);
    } else {
      if (controlicon != 15)
        goto LABEL_273;
      viewplus(0);
    }
  }
}

//-------------------------------------------------------------------------------------------------

int mesminus()
{
  int v0; // ecx
  int result; // eax
  int v2; // edx

  v0 = network_mes_mode;
  result = network_mes_mode;
  v2 = network_mes_mode;
  do {
    if (result < 0)
      result = numcars;
    if (--result == team_mate || result < 0 && players > 2 || human_control[result] && result != (__int16)player1_car) {
      v2 = -666;
      v0 = result;
    }
  } while (v2 == v0);
  network_mes_mode = v0;
  return result;
}

//-------------------------------------------------------------------------------------------------

int mesplus()
{
  int v0; // ecx
  int result; // eax
  int v2; // edx

  v0 = network_mes_mode;
  result = network_mes_mode;
  v2 = network_mes_mode;
  do {
    if (++result >= numcars)
      result = -1;
    if (result == team_mate || result < 0 && players > 2 || human_control[result] && result != (__int16)player1_car) {
      v2 = -666;
      v0 = result;
    }
  } while (v2 == v0);
  network_mes_mode = v0;
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall carminus(int a1, int a2, int a3)
{
  int v3; // ebx

  LOWORD(a3) = numcars;
  v3 = a3 - 1;
  do {
    if (--ViewType < 0)
      ViewType = v3;
  } while (Car_variable_23[308 * ViewType] < 0);
  if (Play_View == 1)
    doteaminit(ViewType);
  else
    initcarview(ViewType, 0);
  return sfxsample(83, 0x8000, v3);
}

//-------------------------------------------------------------------------------------------------

int carplus()
{
  int v0; // ebx

  v0 = numcars;
  do {
    if (++ViewType >= numcars)
      ViewType = 0;
  } while (Car_variable_23[308 * ViewType] < 0);
  if (Play_View == 1)
    doteaminit(ViewType);
  else
    initcarview(ViewType, 0);
  return sfxsample(83, 0x8000, v0);
}

//-------------------------------------------------------------------------------------------------

int __fastcall viewminus(int a1)
{
  int result; // eax
  int v3; // edx
  int v4; // ebx
  int v5; // ebx
  int v6; // ebx
  int v7; // eax
  int v8; // edi
  int v9; // ebx
  int v10; // esi

  result = a1;
  v3 = a1;
  if (replaytype != 2) {
    if ((Car_variable_33[308 * ViewType[result]] & 4) != 0)
      return result * 2;
    if (player_type == 2) {
      v6 = v3 * 4;
      do {
        v10 = SelectedView[v3] - 1;
        SelectedView[v3] = v10;
        if (v10 < 0)
          SelectedView[v3] = 8;
      } while (!DuoViews[SelectedView[v3]]);
    } else {
      do {
        v8 = SelectedView[v3] - 1;
        SelectedView[v3] = v8;
        if (v8 == 7) {
          v9 = (ViewType[result] & 1) != 0 ? ViewType[result] - 1 : ViewType[result] + 1;
          if (Car_variable_23[308 * v9] < 0)
            --SelectedView[v3];
        }
        if (SelectedView[v3] < 0)
          SelectedView[v3] = 8;
        v6 = SelectedView[v3];
      } while (!AllowedViews[v6]);
    }
    v7 = select_view(a1);
    if (Play_View != 1)
      goto LABEL_12;
  LABEL_31:
    doteaminit(v7);
    return sfxsample(83, 0x8000, v6);
  }
  do {
    v4 = SelectedView[v3] - 1;
    SelectedView[v3] = v4;
    if (v4 == 7) {
      v5 = (ViewType[result] & 1) != 0 ? ViewType[result] - 1 : ViewType[result] + 1;
      if (Car_variable_23[308 * v5] < 0)
        --SelectedView[v3];
    }
    if (SelectedView[v3] < 0)
      SelectedView[v3] = 8;
    v6 = SelectedView[v3];
  } while (!ReplayViews[v6]);
  v7 = select_view(a1);
  if (Play_View == 1)
    goto LABEL_31;
LABEL_12:
  initcarview(ViewType[a1], a1);
  return sfxsample(83, 0x8000, v6);
}

//-------------------------------------------------------------------------------------------------

int __fastcall viewplus(int a1)
{
  int result; // eax
  int v3; // edx
  int v4; // ebx
  int v5; // ebx
  int v6; // ebx
  int v7; // eax
  int v8; // ebx
  int v9; // ebx
  int v10; // esi

  result = a1;
  v3 = a1;
  if (replaytype != 2) {
    if ((Car_variable_33[308 * ViewType[result]] & 4) != 0)
      return result * 2;
    if (player_type == 2) {
      v6 = v3 * 4;
      do {
        v10 = SelectedView[v3] + 1;
        SelectedView[v3] = v10;
        if (v10 >= 9)
          SelectedView[v3] = 0;
      } while (!DuoViews[SelectedView[v3]]);
    } else {
      do {
        v8 = SelectedView[v3] + 1;
        SelectedView[v3] = v8;
        if (v8 == 7) {
          v9 = (ViewType[result] & 1) != 0 ? ViewType[result] - 1 : ViewType[result] + 1;
          if (Car_variable_23[308 * v9] < 0)
            ++SelectedView[v3];
        }
        if (SelectedView[v3] >= 9)
          SelectedView[v3] = 0;
        v6 = SelectedView[v3];
      } while (!AllowedViews[v6]);
    }
    v7 = select_view(a1);
    if (Play_View != 1)
      goto LABEL_12;
  LABEL_31:
    doteaminit(v7);
    return sfxsample(83, 0x8000, v6);
  }
  do {
    v4 = SelectedView[v3] + 1;
    SelectedView[v3] = v4;
    if (v4 == 7) {
      v5 = (ViewType[result] & 1) != 0 ? ViewType[result] - 1 : ViewType[result] + 1;
      if (Car_variable_23[308 * v5] < 0)
        ++SelectedView[v3];
    }
    if (SelectedView[v3] >= 9)
      SelectedView[v3] = 0;
    v6 = SelectedView[v3];
  } while (!ReplayViews[v6]);
  v7 = select_view(a1);
  if (Play_View == 1)
    goto LABEL_31;
LABEL_12:
  initcarview(ViewType[a1], a1);
  return sfxsample(83, 0x8000, v6);
}

//-------------------------------------------------------------------------------------------------

void __fastcall game_copypic(char *a1, int a2, char *a3)
{
  int v6; // eax
  char v7; // dh
  int j; // edx
  char v9; // bl
  int k; // eax
  int i; // eax
  int v12; // eax
  int v13; // ecx
  char *v14; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // eax
  int v18; // eax
  int v19; // edx
  int v20; // ecx
  int v21; // eax
  char *v22; // edx
  int v23; // ebx
  char *v24; // edx
  int v25; // ebx
  int v26; // edi
  int v27; // edi
  int v28; // edi
  char *v29; // edx
  int v30; // ebx
  int *v31; // [esp-4h] [ebp-14h]

  screen_pointer = (int)a1;
  if (network_on) {
    if (message_received < 0) {
      if (message_sent >= 0) {
        if (message_sent == 4) {
          small_zoom(&language_buffer_variable_103);
        } else {
          small_zoom(&language_buffer_variable_102);
          for (i = 0; i < 24; currentdir_variable_8[i] = *((_BYTE *)&head_y + 14 * message_sent + i + 3))
            ++i;
          subzoom(&buffer);
        }
        message_sent = -1;
      }
    } else {
      v6 = 0;
      if (language_buffer_variable_101[0]) {
        do {
          v7 = language_buffer_variable_101[++v6];
          currentdir_variable_8[v6] = language_buffer_variable_100[v6];
        } while (v7);
      }
      for (j = 0; j < 9; ++j) {
        ++v6;
        v9 = player_names[9 * message_received + j];
        currentdir_variable_8[v6] = v9;
      }
      small_zoom(&buffer);
      for (k = 0; k < 24; currentdir_variable_8[k] = p_data_variable_8[k]) {
        k += 8;
        currentdir_variable_1[k] = p_data_variable_1[k];
        currentdir_variable_2[k] = p_data_variable_2[k];
        currentdir_variable_3[k] = p_data_variable_3[k];
        currentdir_variable_4[k] = p_data_variable_4[k];
        currentdir_variable_5[k] = p_data_variable_5[k];
        currentdir_variable_6[k] = p_data_variable_6[k];
        currentdir_variable_7[k] = p_data_variable_7[k];
      }
      subzoom(&buffer);
      message_received = -1;
    }
  }
  if (Car_variable_40[308 * ViewType[0]]) {
    if (game_count[0] == -2)
      start_zoom(language_buffer_variable_25, 0);
    if (game_count[0] > 0 && Car_variable_9[77 * ViewType[0]] < (double)threed_c_variable_40)
      game_count[0] = 72;
  }
  if (player_type == 2 && Car_variable_40[308 * ViewType_variable_1]) {
    if (game_count_variable_1 == -2)
      start_zoom(language_buffer_variable_25, 1);
    if (game_count_variable_1 > 0 && Car_variable_9[77 * ViewType_variable_1] < (double)threed_c_variable_40)
      game_count_variable_1 = 72;
  }
  if (!time_shown) {
    if (shown_panel || winner_mode) {
    LABEL_58:
      if (winner_mode) {
        if (champ_mode) {
          if (game_count[0] == -2 && !winner_done) {
            switch (champ_zoom) {
              case 0:
                if (racers - 1 == champ_car)
                  v14 = language_buffer_variable_21;
                else
                  v14 = (char *)&language_buffer + 64 * champ_car + 384;
                start_zoom(v14, 0);
                goto LABEL_97;
              case 1:
                start_zoom(&driver_names[9 * champorder[champ_car]], winner_done);
                goto LABEL_97;
              case 3:
                speechsample(118, 0x8000, 18, (__int16)player1_car);
                start_zoom(config_buffer_variable_77, 0);
                goto LABEL_97;
              case 4:
                start_zoom(config_buffer_variable_78, 0);
                goto LABEL_97;
              case 5:
                start_zoom(config_buffer_variable_79, 0);
                goto LABEL_97;
              case 6:
                if (total_wins[champorder[0]] > 0)
                  speechsample(total_wins[champorder[0]] + 88, 0x8000, 18, (__int16)player1_car);
                goto LABEL_97;
              case 7:
                v15 = total_kills[champorder[0]];
                if (v15 > 0) {
                  if (v15 >= 17) {
                    v17 = 113;
                    v16 = (__int16)player1_car;
                  } else {
                    v16 = (__int16)player1_car;
                    v17 = total_kills[champorder[0]] + 96;
                  }
                  speechsample(v17, 0x8000, 18, v16);
                }
                ++champ_zoom;
                break;
              default:
                break;
            }
          }
        } else if (game_count[0] == -2 && !winner_done) {
          switch (champ_zoom) {
            case 0:
              speechsample(114, 0x8000, 18, (__int16)player1_car);
              start_zoom(config_buffer_variable_72, 0);
              goto LABEL_97;
            case 1:
              start_zoom(config_buffer_variable_73, 0);
              goto LABEL_97;
            case 2:
              if (result_kills[result_order[0]] > 0 || result_order[0] == FastestLap)
                speechsample(115, 0x8000, 18, (__int16)player1_car);
              goto LABEL_97;
            case 3:
              if (result_order[0] == FastestLap) {
                if (BestTime == RecordLaps[game_track])
                  v18 = 116;
                else
                  v18 = 117;
                speechsample(v18, 0x8000, 18, (__int16)player1_car);
              }
              goto LABEL_97;
            case 4:
              v19 = result_kills[result_order[0]];
              if (v19 > 0) {
                if (v19 >= 17) {
                  v21 = 113;
                  v20 = (__int16)player1_car;
                } else {
                  v20 = (__int16)player1_car;
                  v21 = result_kills[result_order[0]] + 96;
                }
                speechsample(v21, 0x8000, 18, v20);
              }
            LABEL_97:
              ++champ_zoom;
              break;
            default:
              break;
          }
        }
      }
      if (intro && game_count[0] == -2) {
        start_zoom(language_buffer_variable_28, 0);
        subzoom(language_buffer_variable_29);
      }
      if (network_on && paused) {
        sprintf(&buffer, "%s", language_buffer_variable_98);
        start_zoom(&buffer, 0);
        sprintf(&buffer, "%s", &player_names[9 * pauser]);
        subzoom(&buffer);
        game_scale[0] = 1115684864;
        game_count[0] = 2;
      }
      if (a3 == (char *)(__int16)player1_car || winner_mode || intro) {
        if (zoom_size[0]) {
          v31 = (int *)&font3_offsets;
          v22 = (char *)&font3_ascii;
          v23 = rev_vga_variable_3;
        } else {
          v31 = &font6_offsets;
          if (winh < 200) {
            v22 = &ascii_conv3;
            v23 = rev_vga;
          } else {
            v22 = font6_ascii;
            v23 = rev_vga_variable_1;
          }
        }
        ZoomString(zoom_mes, (int)v22, v23, 0, (int)v31);
        if (sub_on[0]) {
          if (winh < 200) {
            v24 = &ascii_conv3;
            v25 = rev_vga;
          } else {
            v24 = font6_ascii;
            v25 = rev_vga_variable_1;
          }
          ZoomSub((int)&zoom_sub, (int)v24, v25, 0, (int)&font6_offsets);
        }
      }
      if (a3 == (char *)player2_car) {
        if (zoom_size_variable_1) {
          ZoomString(zoom_mes_variable_1, (int)&font3_ascii, rev_vga_variable_3, 1, (int)&font3_offsets);
        } else if (winh < 200) {
          ZoomString(zoom_mes_variable_1, (int)&ascii_conv3, rev_vga, 1, (int)&font6_offsets);
        } else {
          ZoomString(zoom_mes_variable_1, (int)font6_ascii, rev_vga_variable_1, 1, (int)&font6_offsets);
        }
        if (sub_on_variable_1) {
          if (winh < 200)
            ZoomSub((int)&zoom_sub_variable_1, (int)&ascii_conv3, rev_vga, 1, (int)&font6_offsets);
          else
            ZoomSub((int)&zoom_sub_variable_1, (int)font6_ascii, rev_vga_variable_1, 1, (int)&font6_offsets);
        }
      }
      goto LABEL_127;
    }
    shown_panel = -1;
    if (replaytype != 2) {
      if (game_type != 2) {
        if (countdown <= -72)
          goto LABEL_55;
        if (countdown < 0 && gosound >= 1) {
          gosound = 0;
          speechsample(4, 0x8000, 0, (__int16)player1_car);
        }
        if ((unsigned int)countdown < 0x48) {
          if (gosound >= 2) {
            gosound = 1;
            speechsample(49, 0x8000, 0, (__int16)player1_car);
          }
          if (countdown < 18) {
            if (strcmp(language_buffer_variable_26, zoom_mes)) {
              start_zoom(language_buffer_variable_26, 0);
              if (player_type == 2)
                start_zoom(language_buffer_variable_26, 1);
            }
          }
        }
        if (countdown < 72 || countdown >= 144 || !fadedin || gosound < 3)
          goto LABEL_55;
        v12 = 50;
        gosound = 2;
        v13 = (__int16)player1_car;
        goto LABEL_54;
      }
      if (gosound >= 1 && active_nodes == network_on) {
        v12 = 4;
        v13 = (__int16)player1_car;
        gosound = 0;
      LABEL_54:
        speechsample(v12, 0x8000, 0, v13);
      }
    }
  LABEL_55:
    draw_smoke((int)a1, (int)a3);
    if (replaytype != 2 && (textures_off & 0x20) == 0)
      test_panel((int)a1, a3);
    goto LABEL_58;
  }
LABEL_127:
  if (replaytype == 2 && !intro)
    displayreplay();
  if (game_req) {
    if (draw_type != 2) {
      display_paused();
      if (trying_to_exit) {
        if ((frames & 0xFu) < 8)
          prt_centrecol(171);
      }
    }
  }
  if (!winner_mode && replaytype != 2) {
    if (network_on && active_nodes < network_on && (frames & 0xFu) < 8) {
      if (winh >= 200) {
        prt_centrecol(207);
      } else {
        v26 = scr_size;
        scr_size = 64;
        mini_prt_centre(rev_vga, aWaitingForPlay, winw / 2, winh / 2);
        scr_size = v26;
      }
    }
    if (network_on
      && finished_car[(__int16)player1_car]
      && (frames & 0xFu) < 8
      && !I_Would_Like_To_Quit
      && lastsample < -180) {
      v27 = scr_size;
      scr_size = 64;
      mini_prt_centre(rev_vga, aPleaseWait, winw / 2, winh / 2);
      mini_prt_centre(rev_vga, aForRaceToEnd, winw / 2, winh / 2 + 16);
      scr_size = v27;
    }
    if (I_Would_Like_To_Quit && (frames & 0xFu) < 8) {
      v28 = scr_size;
      scr_size = 64;
      if (game_type == 1)
        v29 = aF10ToQuitChamp;
      else
        v29 = &aIngf10ToQuitGa[3];
      mini_prt_centre(rev_vga, v29, winw / 2, winh / 2);
      mini_prt_centre(rev_vga, aEscToCancel, winw / 2, winh / 2 + 14);
      scr_size = v28;
    }
  }
  if (draw_type != 2) {
    curr_time = ticks;
    v30 = ++frame_count;
    if (ticks - start_time >= 36) {
      frame_rate = v30;
      frame_count = 0;
      start_time = curr_time;
    }
  }
  if (draw_type != 2)
    copypic(a1, a2);
}

//-------------------------------------------------------------------------------------------------

int __fastcall test_w95(int a1, int a2, int a3, int a4)
{
  int result; // eax
  unsigned __int8 v5[28]; // [esp+0h] [ebp-34h] BYREF
  _BYTE v6[16]; // [esp+1Ch] [ebp-18h] BYREF
  int v7; // [esp+2Ch] [ebp-8h]

  v7 = a4;
  memset(v6, 0, 12);
  *(_WORD *)v5 = 5632;
  int386x(47, (int)v5, (int)v5, (int)v6);
  result = v5[0];
  w95 = v5[0];
  if (v5[0] < 3u || v5[0] > 4u)
    w95 = 0;
  else
    w95 = -1;
  return result;
}
#endif
//-------------------------------------------------------------------------------------------------

void *__fastcall malloc2(int iSize, void *pPtr, int *pRegsDi)
{
  void *result; // eax
#ifdef IS_WATCOM
  REGS regs; // [esp+0h] [ebp-34h] BYREF
  struct SREGS sregs; // [esp+1Ch] [ebp-18h] BYREF
  
  if (w95) {
#endif
  result = malloc(iSize);
  pPtr = result;
#ifdef IS_WATCOM
  } else {
    memset(&sregs, 0, sizeof(sregs));
    regs.w.ax = 1281;
    regs.w.bx = (iSize - ((unsigned int)__CFSHL__(iSize >> 31, 16) + (iSize >> 31 << 16))) >> 16;
    regs.w.cx = iSize % 0x10000;
    int386x(49, &regs, &regs, &sregs);
    if (regs.x.cflag) {
      return 0;
    } else {
      *(_DWORD *)pPtr = regs.w.si;
      *pRegsDi = regs.w.di;
      return (void *)((regs.w.bx << 16) + regs.w.cx);
    }
  }
#endif
  return result;
}

//-------------------------------------------------------------------------------------------------

void __fastcall free2(void *ptr)
{
#ifdef IS_WATCOM
  unsigned __int16 nDi; // dx
  REGS regs; // [esp+0h] [ebp-34h] BYREF
  SREGS sregs; // [esp+1Ch] [ebp-18h] BYREF

  if (w95) {
    nfree(ptr);
  } else {
    memset(&sregs, 0, sizeof(sregs));
    regs.w.si = (unsigned __int16)ptr;
    regs.w.ax = 1282;
    regs.w.di = nDi;
    int386x(49, &regs, &regs, &sregs);
  }
#endif
  free(ptr);
  --hibuffers;
}

//-------------------------------------------------------------------------------------------------
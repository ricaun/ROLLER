#include "graphics.h"
#include "3d.h"
#include "transfrm.h"
#include <stdbool.h>
#include <math.h>
//-------------------------------------------------------------------------------------------------

int gfx_size;     //00149740
int NoOfTextures; //00149748

//-------------------------------------------------------------------------------------------------

void plotxyz(float fWorldX, float fWorldY, float fWorldZ, char byColor)
{
  double dPerspectiveScale; // st6
  double dScreenX; // st5
  double dScreenY; // st7
  float fTransformedX; // [esp+4h] [ebp-24h]
  float fTransformedY; // [esp+8h] [ebp-20h]
  float fTransformedZ; // [esp+Ch] [ebp-1Ch]
  int iScreenXInt; // [esp+10h] [ebp-18h]
  float fViewDistance; // [esp+14h] [ebp-14h]

  // Transform world coords to camera-relative coords
  k1 = fWorldX - viewx;
  k2 = fWorldY - viewy;
  k3 = fWorldZ - viewz;

  // Frustum culling - only process points within max render distance (5600)
  if (fabs(k1) <= 5600.0 && fabs(k2) <= 5600.0 && fabs(k3) <= 5600.0) {
    // Apply camera transformation mat
    fTransformedY = k1 * vk2 + k2 * vk5 + k3 * vk8;// right vector proj
    fTransformedZ = k1 * vk3 + k2 * vk6 + k3 * vk9;// up vector proj

    fViewDistance = (float)VIEWDIST;

    // Only render points in front of camera (positive z)
    if (fTransformedZ >= (double)fViewDistance) {
      dPerspectiveScale = 1.0 / fTransformedZ;

      // Transform X to camera space using forward vec
      fTransformedX = k1 * vk1 + k2 * vk4 + k3 * vk7;
      dScreenX = fViewDistance * fTransformedX * dPerspectiveScale + (double)xbase;
      dScreenX = round(dScreenX); //_CHP
      iScreenXInt = (int)dScreenX;
      dScreenY = dPerspectiveScale * (fViewDistance * fTransformedY) + (double)ybase;
      dScreenY = round(dScreenY); //_CHP

      // Clip to screen bounds and plot pixel to 320x200 screen
      if ((int)dScreenX >= 0 && iScreenXInt <= 319 && (unsigned int)(int)dScreenY < 200)
        // plot pixel with y coord flipped (199-y for top-down screen layout)
        // screen buffer offset: (x + width*flippedY)
        scrbuf[iScreenXInt + winw * (199 - (int)dScreenY)] = byColor;
    }
  }
}

//-------------------------------------------------------------------------------------------------

void linexyz(float fX1, float fY1, float fZ1, float fX2, float fY2, float fZ2, char a7)
{/*
  double dViewDist; // st7
  double v12; // st6
  double dXbase; // st5
  double dScrSize; // st4
  double v15; // rt2
  double dYBase; // st4
  int v17; // edi
  int v18; // eax
  int v19; // ecx
  double v20; // st7
  int v21; // eax
  float v22; // [esp+4h] [ebp-3Ch]
  float v23; // [esp+8h] [ebp-38h]
  float v24; // [esp+Ch] [ebp-34h]
  float v25; // [esp+10h] [ebp-30h]
  float v26; // [esp+14h] [ebp-2Ch]
  float fViewDist; // [esp+18h] [ebp-28h]
  float v28; // [esp+1Ch] [ebp-24h]
  float v29; // [esp+1Ch] [ebp-24h]
  float v30; // [esp+1Ch] [ebp-24h]
  float v31; // [esp+20h] [ebp-20h]
  float v32; // [esp+20h] [ebp-20h]
  float v33; // [esp+20h] [ebp-20h]
  int v34; // [esp+24h] [ebp-1Ch]

  k1 = fX1 - viewx;
  k2 = fY1 - viewy;
  k3 = fZ1 - viewz;
  k4 = fX2 - viewx;
  k5 = fY2 - viewy;
  k6 = fZ2 - viewz;
  v24 = k1 * vk1 + k2 * vk4 + k3 * vk7;
  v31 = k1 * vk3 + k2 * vk6 + k3 * vk9;
  v26 = vk5 * k5 + k4 * vk2 + k6 * vk8;
  v28 = vk9 * k6 + vk3 * k4 + k5 * vk6;
  dViewDist = (double)VIEWDIST;
  v32 = v31 - dViewDist;
  v29 = v28 - dViewDist;
  if (v32 < 0.0 && v29 > 0.0 || v32 > 0.0 && v29 < 0.0) {
    v12 = 1.0 / (v32 - v29);
    v23 = k1 * vk2 + k2 * vk5 + k3 * vk8;
    v22 = v12 * (v26 * v32 - v29 * v23);
    if (v32 >= 0.0) {
      v29 = 0.0;
      v26 = v22;
    } else {
      v25 = vk4 * k5 + k4 * vk1 + vk7 * k6;
      v24 = (v25 * v32 - v24 * v29) * v12;
      v32 = 0.0;
    }
  }
  fViewDist = (float)VIEWDIST;
  v33 = v32 + fViewDist;
  v30 = v29 + fViewDist;
  if (v33 >= (double)fViewDist && v30 >= (double)fViewDist) {
    dXbase = (double)xbase;
    dScrSize = (double)scr_size;
    _CHP();
    v34 = (int)((fViewDist * v24 * (1.0 / v33) + dXbase) * dScrSize);
    v15 = dScrSize;
    dYBase = (double)ybase;
    _CHP();
    v17 = (v34 - (__CFSHL__(v34 >> 31, 6) + (v34 >> 31 << 6))) >> 6;
    _CHP();
    v19 = v18;
    v20 = (graphics_c_variable_2 - 1.0 / v30 * (fViewDist * v26) - dYBase) * v15;
    _CHP();
    compout(v17, v21, v19, v17, v21, ((int)v20 - (__CFSHL__((int)v20 >> 31, 6) + ((int)v20 >> 31 << 6))) >> 6, a7);
  }*/
}

//-------------------------------------------------------------------------------------------------

void compout(uint8 *pScrBuf, int iX0, int iY0, int iX1, int iY1, uint8 byColor)
{
  int iNewX; // edi
  int iNewY; // esi
  int iX0_1; // ebp
  char byOutcode0; // cl
  char byOutcode1; // dl
  int iDy; // ecx
  int iYOffset; // eax
  char *p_byOutcode; // ecx
  char byOutcode; // dl
  int iDx; // [esp+8h] [ebp-28h]
  char byUseOutcode; // [esp+10h] [ebp-20h]
  char byOutcode1_1; // [esp+14h] [ebp-1Ch] BYREF
  char byOutcode0_1; // [esp+18h] [ebp-18h] BYREF
  char byDone; // [esp+1Ch] [ebp-14h]
  char byDraw; // [esp+20h] [ebp-10h]

  iX0_1 = iX0;
  byOutcode0 = 0;
  byDraw = 0;
  byDone = 0;

  // Get region code for point 0
  if (iY0 < winh) {
    if (iY0 < 0)
      byOutcode0 = 4;                           // bottom
  } else {
    byOutcode0 = 8;                             // top
  }
  if (iX0 < winw) {
    if (iX0 < 0)
      ++byOutcode0;                             // left
  } else {
    byOutcode0 += 2;                            // right
  }
  byOutcode0_1 = byOutcode0;
  byOutcode1 = 0;

  // Get region code for point 1
  if (iY1 < winh) {
    if (iY1 < 0)
      byOutcode1 = 4;                           // bottom
  } else {
    byOutcode1 = 8;                             // top
  }
  if (iX1 < winw) {
    if (iX1 < 0)
      ++byOutcode1;                             // left
  } else {
    byOutcode1 += 2;                            // right
  }
  byOutcode1_1 = byOutcode1;

  // Clipping loop (Cohen-Sutherland algorithm)
  do {
    // Both points inside screen, draw line
    if (!byOutcode0_1 && !byOutcode1_1) {
      byDraw = -1;
      byDone = -1;
      continue;
    }
    // Both points outside screen, don't draw line
    if (((unsigned __int8)byOutcode1_1 & (unsigned __int8)byOutcode0_1) != 0) {
      byDone = -1;
      continue;
    }

    // Select point to clip
    if (byOutcode0_1)
      byUseOutcode = byOutcode0_1;
    else
      byUseOutcode = byOutcode1_1;

    // Calculate intersection with window boundary
    iDx = iX1 - iX0_1;
    iDy = iY1 - iY0;
    if ((byUseOutcode & 8) != 0)              // top
    {
      iNewY = winh - 1;
      iNewX = iDx * (winh - 1 - iY0) / iDy + iX0_1;
    } else {
      if ((byUseOutcode & 4) == 0)            // bottom
      {
        if ((byUseOutcode & 2) != 0)          // right
        {
          iNewX = winw - 1;
          iYOffset = iDy * (winw - 1 - iX0_1) / iDx;
        } else {
          if ((byUseOutcode & 1) == 0)        // left
            goto LABEL_35;
          iYOffset = iDy * -iX0_1 / iDx;
          iNewX = 0;
        }
        iNewY = iY0 + iYOffset;
        goto LABEL_35;
      }
      iNewY = 0;
      iNewX = iDx * -iY0 / iDy + iX0_1;
    }
  LABEL_35:
      // Update clipped point and recompute outcode
    if (byUseOutcode == byOutcode0_1) {
      p_byOutcode = &byOutcode0_1;
      iX0_1 = iNewX;
      iY0 = iNewY;
      byOutcode = 0;
      if (iNewY < winh) {
        if (iNewY < 0)
          byOutcode = 4;
      } else {
        byOutcode = 8;
      }
      if (iNewX < winw) {
        if (iNewX < 0)
          ++byOutcode;
      } else {
        byOutcode += 2;
      }
    } else {
      p_byOutcode = &byOutcode1_1;
      iX1 = iNewX;
      iY1 = iNewY;
      byOutcode = 0;
      if (iNewY < winh) {
        if (iNewY < 0)
          byOutcode = 4;
      } else {
        byOutcode = 8;
      }
      if (iNewX < winw) {
        if (iNewX < 0)
          ++byOutcode;
      } else {
        byOutcode += 2;
      }
    }
    *p_byOutcode = byOutcode;
  } while (!byDone);
  if (byDraw)
    line(pScrBuf, iX0_1, iY0, iX1, iY1, byColor);
}

//-------------------------------------------------------------------------------------------------

void line(uint8 *pScrBuf, int iX0, int iY0, int iX1, int iY1, uint8 byColor)
{
  int iOldWinw; // ebp
  int iTempX; // esi
  int iTempY; // esi
  int iDx; // edi
  uint8 *pDest; // eax
  int iDy; // esi
  int iDy_1; // esi
  int iError_2; // ebx
  int iError_3; // edx
  bool bAboveTarget; // cc
  int iError_1; // ebx
  int iError; // edx
  int iTempX2; // [esp+4h] [ebp-10h]

  iOldWinw = winw;
  iTempX2 = iX1;

  // single point check
  if (iX0 == iX1 && iY0 == iY1) {
    pScrBuf[iX1 + winw * iY0] = byColor;        // draw pixel
  } else {
    // Swap points if needed to ensure left to right drawing
    if (iX0 > iX1) {
      iTempX = iX0;
      iX0 = iX1;
      iTempX2 = iTempX;
      iTempY = iY0;
      iY0 = iY1;
      iY1 = iTempY;
    }
    iDx = iTempX2 - iX0;
    pDest = &pScrBuf[iX0 + winw * iY0];
    iDy = iY1 - iY0;

    // positive slope
    if (iY1 - iY0 >= 0) {
      // steep slope (|m| > 1)
      if (iDx <= iDy) {
        iError = iDy >> 1;
        while (iY0 <= iY1) {
          ++iY0;
          iError -= iDx;
          *pDest = byColor;                     // draw pixel
          pDest += iOldWinw;                    // move down
          if (iError < 0) {
            ++pDest;                            // move right
            iError += iDy;
          }
        }
      } else                                      // gentle slope (|m| <= 1)
      {
        iError_1 = (iTempX2 - iX0) >> 1;
        while (iX0 <= iTempX2) {
          ++pDest;                              // move right
          ++iX0;
          iError_1 -= iDy;
          *(pDest - 1) = byColor;               // draw pixel
          if (iError_1 < 0) {
            iError_1 += iDx;
            pDest += iOldWinw;                  // move down
          }
        }
      }
    } else                                        // negative slope
    {
      iDy_1 = iY0 - iY1;
      // steep slope (|m| > 1)
      if (iDx <= iY0 - iY1) {
        iError_3 = iDy_1 >> 1;
        for (bAboveTarget = iY0 < iY1; !bAboveTarget; bAboveTarget = iY0 < iY1) {
          --iY0;
          iError_3 -= iDx;
          *pDest = byColor;                     // draw pixel
          pDest -= iOldWinw;                    // move up
          if (iError_3 < 0) {
            ++pDest;                            // move right
            iError_3 += iDy_1;
          }
        }
      } else                                      // gentle slope (|m| <= 1)
      {
        iError_2 = (iTempX2 - iX0) >> 1;
        while (iX0 <= iTempX2) {
          ++pDest;                              // move right
          ++iX0;
          iError_2 -= iDy_1;
          *(pDest - 1) = byColor;               // draw pixel
          if (iError_2 < 0) {
            iError_2 += iDx;
            pDest -= iOldWinw;                  // move up
          }
        }
      }
    }
  }
  winw = iOldWinw;
}

//-------------------------------------------------------------------------------------------------

void LoadPanel()
{/*
  int v1; // ebx
  char *v2; // ecx
  int v3; // esi
  __int64 v4; // rax
  int v5; // edi
  unsigned int v6; // eax
  unsigned int v7; // eax
  char *v8; // ecx
  int v9; // esi
  int v10; // edx
  unsigned int v11; // eax
  unsigned int v12; // eax
  char v13; // [esp-10h] [ebp-14h]

  v13 = a1;
  v1 = 0;
  if (((unsigned int)cstart_branch_1 & textures_off) != 0) {
    v2 = revs_files2;
    v3 = 0;
    while (revs_files2[13 * v1]) {
      v4 = open(&revs_files2[13 * v1], 512, v13);
      v5 = v4;
      if ((_DWORD)v4 == -1) {
        printf(aUnableToOpenS);
        doexit();
      }
      close(v5, HIDWORD(v4));
      ++v3;
      v6 = getcompactedfilelength(v2);
      v7 = getbuffer(v6);
      cargen_vga[v3] = v7;
      loadcompactedfile(v2, v7, ++v1, v2);
      v2 += 13;
    }
  } else {
    v8 = revs_files1;
    v9 = 0;
    while (revs_files1[13 * v1]) {
      v10 = open(&revs_files1[13 * v1], 512, v13);
      if (v10 == -1) {
        printf(aUnableToOpenS);
        doexit();
      }
      close(v10, v10);
      ++v9;
      v11 = getcompactedfilelength(v8);
      v12 = getbuffer(v11);
      cargen_vga[v9] = v12;
      loadcompactedfile(v8, v12, ++v1, v8);
      v8 += 13;
    }
  }*/
}

//-------------------------------------------------------------------------------------------------

int InitRemaps()
{
  return 0;/*
  int v0; // edi
  int v1; // esi
  int v2; // ecx

  init_remap(cargen_vga[0], 18, num_textures_variable_2, gfx_size);
  init_remap(building_vga, 17, num_textures_variable_1, gfx_size);
  v0 = 0;
  if (numcars > 0) {
    v1 = 0;
    do {
      v2 = car_texs_loaded[v1];
      if (v2 != -1)
        init_remap(horizon_vga[v2], car_texs_loaded[v1] - 1, bld_remap_variable_1[v2], gfx_size);
      ++v0;
      ++v1;
    } while (v0 < numcars);
  }
  return init_remap(texture_vga, -1, num_textures_variable_3, gfx_size);*/
}

//-------------------------------------------------------------------------------------------------

int LoadGenericCarTextures(int a1, int a2, int a3, int a4)
{
  return 0;/*
  int v4; // edx
  signed int v5; // ecx
  int v6; // eax
  int v7; // esi
  int v8; // ecx
  int v9; // ebx
  int result; // eax
  _DWORD v11[5]; // [esp+0h] [ebp-14h] BYREF

  v11[3] = a4;
  v4 = open(gencartex_name, 512, v11[0]);
  if (v4 == -1) {
    printf(aUnableToOpenTe_0);
    doexit();
  }
  close(v4, v4);
  v5 = getcompactedfilelength(gencartex_name);
  v6 = (v5 - (__CFSHL__(v5 >> 31, 12) + (v5 >> 31 << 12))) >> 12;
  v7 = v6;
  if (gfx_size == 1) {
    cargen_vga[0] = getbuffer((((_WORD)v6 + 7) & 0xFFF8) << 10);
    v11[0] = getbuffer(v5);
    loadcompactedfile(gencartex_name, v11[0], v7, v5);
    v8 = (v5 - (__CFSHL__(v5 >> 31, 12) + (v5 >> 31 << 12))) >> 12;
    sort_small_texture(cargen_vga[0], v11[0]);
    v9 = -1;
    fre(v11);
  } else {
    cargen_vga[0] = getbuffer((((_WORD)v6 + 3) & 0xFFFC) << 12);
    v8 = (v5 - (__CFSHL__(v5 >> 31, 12) + (v5 >> 31 << 12))) >> 12;
    loadcompactedfile(gencartex_name, cargen_vga[0], a3, v7);
    v9 = 0;
    sort_texture(cargen_vga[0], v7, 0);
  }
  result = setmapsel(cargen_vga[0], 18, v9, v8);
  num_textures_variable_2 = v7;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int LoadCarTexture(int a1, char a2)
{
  return 0;/*
  int v3; // edx
  int v4; // ecx
  int v5; // eax
  unsigned int v6; // ebx
  int v7; // ebp
  int v8; // edx
  int v9; // eax
  int v10; // edi
  char *i; // eax
  int j; // esi
  int v13; // edx
  unsigned int v14; // ebx
  char v15; // cl
  char *v16; // eax
  char v17; // cl
  char v18; // cl
  char v19; // cl
  int v20; // edx
  int v21; // eax
  int v22; // edi
  char *k; // eax
  int m; // esi
  int v25; // edx
  unsigned int v26; // ebx
  char v27; // cl
  char *v28; // eax
  char v29; // cl
  char v30; // cl
  char v31; // cl
  int result; // eax
  unsigned int v33; // eax
  int v34; // [esp+0h] [ebp-28h]
  char *v36; // [esp+8h] [ebp-20h]
  char *v37; // [esp+Ch] [ebp-1Ch]
  int v38; // [esp+10h] [ebp-18h]

  v37 = &car_texture_names[256 * a1];
  if (!a1) {
    a3 = car_texture_names;
    printf(aExitingNameIsS);
    doexit();
  }
  if (((unsigned int)cstart_branch_1 & textures_off) != 0 && a1 >= 1 && a1 <= 8)
    *v37 = 121;
  v3 = open(v37, 512, a2);
  if (v3 == -1) {
    printf(aUnableToOpenTe_1);
    doexit();
  }
  close(v3, v3);
  v4 = getcompactedfilelength(v37);
  if (v4 == -1) {
    printf(aFileSizeErrorI);
    doexit();
  }
  v5 = (v4 - (__CFSHL__(v4 >> 31, 12) + (v4 >> 31 << 12))) >> 12;
  v36 = (char *)v5;
  if (gfx_size == 1) {
    initmangle(v37);
    v38 = v4;
    v6 = getbuffer((((_WORD)v36 + 7) & 0xFFF8) << 10);
    horizon_vga[v34] = v6;
    while (v38 > 0) {
      v7 = (v38 - (__CFSHL__(v38 >> 31, 12) + (v38 >> 31 << 12))) >> 12;
      if (no_mem) {
        if (v38 <= 20480) {
          v8 = v38;
          v9 = scrbuf;
        } else {
          v8 = 20480;
          v9 = scrbuf;
          v7 = 5;
        }
        readmangled(v9, v8, v6);
        v10 = 0;
        for (i = (char *)(scrbuf + 40000); v10 < v7; ++v10) {
          for (j = 0; j < 32; ++j) {
            v13 = 0;
            do {
              v14 = v6 + 1;
              v15 = *i;
              v16 = i + 2;
              v13 += 4;
              *(_BYTE *)(v14++ - 1) = v15;
              v17 = *v16;
              v16 += 2;
              *(_BYTE *)(v14++ - 1) = v17;
              v18 = *v16;
              v16 += 2;
              *(_BYTE *)(v14 - 1) = v18;
              v6 = v14 + 1;
              v19 = *v16;
              i = v16 + 2;
              *(_BYTE *)(v6 - 1) = v19;
            } while (v13 < 32);
            i += 64;
          }
        }
        v38 -= 20480;
      } else {
        if (v38 <= 196608) {
          v21 = scrbuf;
          v20 = v38;
        } else {
          v20 = 196608;
          v21 = scrbuf;
          v7 = 48;
        }
        readmangled(v21, v20, v6);
        v22 = 0;
        for (k = (char *)(scrbuf + 40000); v22 < v7; ++v22) {
          for (m = 0; m < 32; ++m) {
            v25 = 0;
            do {
              v26 = v6 + 1;
              v27 = *k;
              v28 = k + 2;
              v25 += 4;
              *(_BYTE *)(v26++ - 1) = v27;
              v29 = *v28;
              v28 += 2;
              *(_BYTE *)(v26++ - 1) = v29;
              v30 = *v28;
              v28 += 2;
              *(_BYTE *)(v26 - 1) = v30;
              v6 = v26 + 1;
              v31 = *v28;
              k = v28 + 2;
              *(_BYTE *)(v6 - 1) = v31;
            } while (v25 < 32);
            k += 64;
          }
        }
        v38 -= 196608;
      }
    }
    uninitmangle();
    sort_mini_texture(horizon_vga[v34], v36, -1, v36);
    setmapsel(horizon_vga[v34], v34, -1, v36);
    result = (int)v36;
    bld_remap_variable_1[v34] = (int)v36;
  } else {
    v33 = getbuffer((((_WORD)v5 + 3) & 0xFFFC) << 12);
    horizon_vga[v34] = v33;
    loadcompactedfile(v37, v33, a3, v36);
    sort_texture(horizon_vga[v34], v36, 0);
    setmapsel(horizon_vga[v34], v34, 0, v36);
    result = (v4 - (__CFSHL__(v4 >> 31, 12) + (v4 >> 31 << 12))) >> 12;
    bld_remap_variable_1[v34] = (int)v36;
  }
  if (((unsigned int)cstart_branch_1 & textures_off) != 0 && a1 >= 1 && a1 <= 8) {
    result = (int)v37;
    *v37 = 120;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int LoadBldTextures(int a1, int a2, int a3, int a4)
{
  return 0;/*
  int v4; // edx
  signed int v5; // ecx
  int v6; // eax
  int v7; // esi
  int v8; // ecx
  int v9; // ebx
  int result; // eax
  _DWORD v11[5]; // [esp+0h] [ebp-14h] BYREF

  v11[3] = a4;
  fre(&building_vga);
  v4 = open(bldtex_file, 512, v11[0]);
  if (v4 == -1) {
    printf(aUnableToOpenBl);
    doexit();
  }
  close(v4, v4);
  v5 = getcompactedfilelength(bldtex_file);
  v6 = (v5 - (__CFSHL__(v5 >> 31, 12) + (v5 >> 31 << 12))) >> 12;
  v7 = v6;
  if (gfx_size == 1) {
    building_vga = getbuffer((((_WORD)v6 + 7) & 0xFFF8) << 10);
    v11[0] = getbuffer(v5);
    loadcompactedfile(bldtex_file, v11[0], v7, v5);
    v8 = (v5 - (__CFSHL__(v5 >> 31, 12) + (v5 >> 31 << 12))) >> 12;
    sort_small_texture(building_vga, v11[0]);
    v9 = -1;
    fre(v11);
  } else {
    building_vga = getbuffer((((_WORD)v6 + 3) & 0xFFFC) << 12);
    v8 = (v5 - (__CFSHL__(v5 >> 31, 12) + (v5 >> 31 << 12))) >> 12;
    loadcompactedfile(bldtex_file, building_vga, a3, v7);
    v9 = 0;
    sort_texture(building_vga, v7, 0);
  }
  BldTextures = v7;
  result = setmapsel(building_vga, 17, v9, v8);
  num_textures_variable_1 = v7;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int LoadTextures(int a1, int a2, int a3)
{
  return 0;/*
  __int64 v3; // rax
  int v4; // ecx
  int v5; // eax
  unsigned int v6; // ebx
  int v7; // ebp
  int v8; // edx
  int v9; // eax
  int v10; // edi
  char *i; // eax
  int j; // esi
  int v13; // edx
  unsigned int v14; // ebx
  char v15; // cl
  char *v16; // eax
  char v17; // cl
  char v18; // cl
  char v19; // cl
  int v20; // edx
  int v21; // eax
  int v22; // edi
  char *k; // eax
  int m; // esi
  int v25; // edx
  unsigned int v26; // ebx
  char v27; // cl
  char *v28; // eax
  char v29; // cl
  char v30; // cl
  char v31; // cl
  int result; // eax
  int v33; // [esp+0h] [ebp-24h]
  int v34; // [esp+4h] [ebp-20h]
  int v35; // [esp+8h] [ebp-1Ch]

  fre(&texture_vga);
  v3 = open(texture_file, 512);
  v33 = v3;
  if ((_DWORD)v3 == -1) {
    printf(&aPunableToOpenT[1]);
    doexit();
  }
  close(v33, HIDWORD(v3));
  v4 = getcompactedfilelength(texture_file);
  v5 = (v4 - (__CFSHL__(v4 >> 31, 12) + (v4 >> 31 << 12))) >> 12;
  v34 = v5;
  if (gfx_size == 1) {
    initmangle(texture_file);
    v35 = v4;
    v6 = getbuffer((((_WORD)v34 + 7) & 0xFFF8) << 10);
    texture_vga = v6;
    while (v35 > 0) {
      v7 = (v35 - (__CFSHL__(v35 >> 31, 12) + (v35 >> 31 << 12))) >> 12;
      if (no_mem) {
        if (v35 <= 20480) {
          v8 = v35;
          v9 = scrbuf;
        } else {
          v8 = 20480;
          v9 = scrbuf;
          v7 = 5;
        }
        readmangled(v9, v8, v6);
        v10 = 0;
        for (i = (char *)(scrbuf + 40000); v10 < v7; ++v10) {
          for (j = 0; j < 32; ++j) {
            v13 = 0;
            do {
              v14 = v6 + 1;
              v15 = *i;
              v16 = i + 2;
              v13 += 4;
              *(_BYTE *)(v14++ - 1) = v15;
              v17 = *v16;
              v16 += 2;
              *(_BYTE *)(v14++ - 1) = v17;
              v18 = *v16;
              v16 += 2;
              *(_BYTE *)(v14 - 1) = v18;
              v6 = v14 + 1;
              v19 = *v16;
              i = v16 + 2;
              *(_BYTE *)(v6 - 1) = v19;
            } while (v13 < 32);
            i += 64;
          }
        }
        v35 -= 20480;
      } else {
        if (v35 <= 196608) {
          v21 = scrbuf;
          v20 = v35;
        } else {
          v20 = 196608;
          v21 = scrbuf;
          v7 = 48;
        }
        readmangled(v21, v20, v6);
        v22 = 0;
        for (k = (char *)(scrbuf + 40000); v22 < v7; ++v22) {
          for (m = 0; m < 32; ++m) {
            v25 = 0;
            do {
              v26 = v6 + 1;
              v27 = *k;
              v28 = k + 2;
              v25 += 4;
              *(_BYTE *)(v26++ - 1) = v27;
              v29 = *v28;
              v28 += 2;
              *(_BYTE *)(v26++ - 1) = v29;
              v30 = *v28;
              v28 += 2;
              *(_BYTE *)(v26 - 1) = v30;
              v6 = v26 + 1;
              v31 = *v28;
              k = v28 + 2;
              *(_BYTE *)(v6 - 1) = v31;
            } while (v25 < 32);
            k += 64;
          }
        }
        v35 -= 196608;
      }
    }
    uninitmangle();
    sort_mini_texture(texture_vga, v34, -1, v34);
    setmapsel(texture_vga, 0, -1, v34);
    NoOfTextures = v34;
    close(v33, 0);
    result = v34;
    num_textures_variable_3 = v34;
  } else {
    texture_vga = getbuffer((((_WORD)v5 + 3) & 0xFFFC) << 12);
    loadcompactedfile(texture_file, texture_vga, a3, v34);
    sort_texture(texture_vga, v34, 0);
    setmapsel(texture_vga, 0, 0, v34);
    result = (v4 - (__CFSHL__(v4 >> 31, 12) + (v4 >> 31 << 12))) >> 12;
    NoOfTextures = result;
    num_textures_variable_3 = result;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int init_remap(int result, int a2, int a3, int a4)
{
  return 0;/*
  int v4; // edi
  int v5; // ebx
  int v6; // eax
  unsigned __int8 *v7; // ebx
  int v8; // ebp
  int i; // ecx
  int j; // eax
  int v11; // edx
  int v12; // edx
  int v13; // eax
  int v14; // ebx
  int v15; // ebx
  int v16; // esi
  int v17; // ebp
  int v18; // eax
  int v19; // edx
  int v20; // [esp+0h] [ebp-40h]
  int v23; // [esp+Ch] [ebp-34h]
  int v24; // [esp+10h] [ebp-30h]
  int v26; // [esp+18h] [ebp-28h]
  int v27; // [esp+1Ch] [ebp-24h]
  int v28; // [esp+28h] [ebp-18h]
  int v29; // [esp+2Ch] [ebp-14h]
  int v30; // [esp+2Ch] [ebp-14h]
  int k; // [esp+30h] [ebp-10h]

  v23 = result;
  if (a4)
    v4 = 32;
  else
    v4 = 64;
  v27 = 0;
  if (a3 > 0) {
    v26 = 0;
    v24 = a2 << 10;
    do {
      if (a4) {
        v5 = (v27 >> 3 << 13) + v23;
        v6 = 32 * (v27 & 7);
      } else {
        v5 = (v27 >> 2 << 14) + v23;
        v6 = (v27 & 3) << 6;
      }
      v7 = (unsigned __int8 *)(v6 + v5);
      _STOSD(mode_c, 0, v7, 256);
      v8 = 0;
      v28 = 0;
      v29 = 0;
      for (i = 0; i < v4; ++i) {
        for (j = 0; j < v4; ++j) {
          v11 = *v7++;
          ++mode_c[v11];
        }
        v7 += 256 - v4;
      }
      v20 = 0;
      for (k = 0; k < 4; ++k) {
        v12 = 0;
        v13 = 0;
        v14 = 0;
        do {
          if (mode_c[v14] > mode_c[v12])
            v12 = v13;
          ++v13;
          ++v14;
        } while (v13 < 256);
        v15 = mode_c[v12];
        if (v15 > 4 * v4) {
          v20 += v15;
          v29 += mode_c[v12] * (unsigned __int8)palette[3 * v12];
          v16 = mode_c[v12];
          v8 += v16 * (unsigned __int8)palette_variable_1[3 * v12];
          v28 += v16 * (unsigned __int8)palette_variable_2[3 * v12];
          mode_c[v12] = 0;
        }
      }
      if (v20 <= 0) {
        v19 = 3 * v12;
        v30 = (unsigned __int8)palette[v19];
        v18 = (unsigned __int8)palette_variable_2[v19];
        v17 = (unsigned __int8)palette_variable_1[v19];
      } else {
        v30 = v29 / v20;
        v17 = v8 / v20;
        v18 = v28 / v20;
      }
      if (a2 < 17) {
        if (a2 == -1) {
          if (v30 > 28 && (v17 <= v30) >= v18)
            v30 = 28;
          if (v17 > 28 && (v17 <= v30) >= v18)
            v17 = 28;
          remap_tex[v26] = nearest_colour(v30, v17, v18);
          goto LABEL_51;
        }
      } else {
        if (a2 <= 17) {
          if (v30 > 28 && (v17 <= v30) >= v18)
            v30 = 28;
          if (v17 > 28 && (v17 <= v30) >= v18)
            v17 = 28;
          bld_remap[v26] = nearest_colour(v30, v17, v18);
          goto LABEL_51;
        }
        if (a2 == 18) {
          if (v30 > 28 && (v17 <= v30) >= v18)
            v30 = 28;
          if (v17 > 28 && (v17 <= v30) >= v18)
            v17 = 28;
          cargen_remap[v26] = nearest_colour(v30, v17, v18);
          goto LABEL_51;
        }
      }
      *(int *)((char *)&car_remap + v24) = nearest_colour(v30, v17, v18);
    LABEL_51:
      result = v27 + 1;
      v24 += 4;
      ++v26;
      v27 = result;
    } while (result < a3);
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int sort_small_texture(int a1, char *a2, int a3)
{
  return 0;/*
  int result; // eax
  int v5; // ebp
  int v6; // ebp
  int v7; // edi
  int v8; // esi
  int v9; // eax
  int v10; // edx
  int v11; // eax
  char v12; // cl
  char *v13; // ebx
  char v14; // cl
  char v15; // cl
  char v16; // cl
  int v17; // [esp+0h] [ebp-20h]
  int v18; // [esp+4h] [ebp-1Ch]
  int v19; // [esp+8h] [ebp-18h]

  result = (a3 - (__CFSHL__(a3 >> 31, 3) + 8 * (a3 >> 31))) >> 3;
  v19 = a3;
  v18 = 0;
  v17 = result;
  if (result >= 0) {
    do {
      if (v19 <= 7)
        v5 = v19;
      else
        v5 = 8;
      if (v5 > 0) {
        v6 = 32 * v5;
        v7 = 0;
        do {
          v8 = 0;
          v9 = v7 + a1;
          do {
            v10 = 0;
            do {
              v11 = v9 + 1;
              v12 = *a2;
              v13 = a2 + 2;
              v10 += 4;
              *(_BYTE *)(v11++ - 1) = v12;
              v14 = *v13;
              v13 += 2;
              *(_BYTE *)(v11++ - 1) = v14;
              v15 = *v13;
              v13 += 2;
              *(_BYTE *)(v11 - 1) = v15;
              v9 = v11 + 1;
              v16 = *v13;
              a2 = v13 + 2;
              *(_BYTE *)(v9 - 1) = v16;
            } while (v10 < 32);
            v9 += 224;
            ++v8;
            a2 += 64;
          } while (v8 < 32);
          v7 += 32;
        } while (v7 < v6);
      }
      result = v18 + 1;
      v19 -= 8;
      a1 += 0x2000;
      v18 = result;
    } while (result <= v17);
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void *sort_texture(char *a1, int a2)
{
  return 0;/*
  int v3; // ebp
  int v4; // esi
  char *v5; // ecx
  int j; // edi
  int v7; // edx
  char *v8; // eax
  char *v9; // ecx
  char v10; // bl
  char *v11; // eax
  char v12; // bl
  char v13; // bl
  char v14; // bl
  char *v16; // [esp+0h] [ebp-34h] BYREF
  int v17; // [esp+4h] [ebp-30h]
  int v18; // [esp+8h] [ebp-2Ch]
  int v19; // [esp+Ch] [ebp-28h]
  char *v20; // [esp+10h] [ebp-24h]
  int v21; // [esp+14h] [ebp-20h]
  int i; // [esp+18h] [ebp-1Ch]
  char *v23; // [esp+1Ch] [ebp-18h]

  v19 = a2;
  v16 = (char *)getbuffer(0x4000u);
  v20 = a1;
  v18 = 0;
  v17 = (a2 - (__CFSHL__(a2 >> 31, 2) + 4 * (a2 >> 31))) >> 2;
  if (v17 >= 0) {
    do {
      v23 = v20;
      if (v19 <= 3)
        v3 = v19;
      else
        v3 = 4;
      v21 = 0;
      if (v3 > 0) {
        for (i = 0; i < 64; ++i) {
          v4 = i << 6;
          v5 = &v16[v21];
          for (j = 0; j < v3; ++j) {
            v7 = 0;
            v8 = &v23[v4];
            do {
              v9 = v5 + 1;
              v10 = *v8;
              v11 = v8 + 1;
              v7 += 4;
              *(v9++ - 1) = v10;
              v12 = *v11++;
              *(v9++ - 1) = v12;
              v13 = *v11++;
              *(v9 - 1) = v13;
              v5 = v9 + 1;
              v14 = *v11;
              v8 = v11 + 1;
              *(v5 - 1) = v14;
            } while (v7 < 64);
            v4 += 4096;
          }
          v21 += 256;
        }
        qmemcpy(v20, v16, 0x4000u);
      }
      v20 += 0x4000;
      v19 -= 4;
      ++v18;
    } while (v18 <= v17);
  }
  return fre(&v16);*/
}

//-------------------------------------------------------------------------------------------------

void *sort_mini_texture(char *a1, int a2)
{
  return 0;/*
  int v3; // ebp
  int v4; // esi
  int v5; // edi
  char *v6; // ecx
  int v7; // edx
  char *v8; // eax
  char *v9; // ecx
  char v10; // bl
  char *v11; // eax
  char v12; // bl
  char v13; // bl
  char v14; // bl
  char *v16; // [esp+0h] [ebp-34h] BYREF
  int v17; // [esp+4h] [ebp-30h]
  int v18; // [esp+8h] [ebp-2Ch]
  char *v19; // [esp+Ch] [ebp-28h]
  int v20; // [esp+10h] [ebp-24h]
  int v21; // [esp+14h] [ebp-20h]
  int i; // [esp+18h] [ebp-1Ch]
  char *v23; // [esp+1Ch] [ebp-18h]

  v20 = a2;
  v16 = (char *)getbuffer(0x2000u);
  v19 = a1;
  v18 = 0;
  v17 = (a2 - (__CFSHL__(a2 >> 31, 3) + 8 * (a2 >> 31))) >> 3;
  if (v17 >= 0) {
    do {
      v23 = v19;
      if (v20 <= 7)
        v3 = v20;
      else
        v3 = 8;
      v21 = 0;
      if (v3 > 0) {
        for (i = 0; i < 32; ++i) {
          v4 = 0;
          v5 = 32 * i;
          v6 = &v16[v21];
          do {
            v7 = 0;
            v8 = &v23[v5];
            do {
              v9 = v6 + 1;
              v10 = *v8;
              v11 = v8 + 1;
              v7 += 4;
              *(v9++ - 1) = v10;
              v12 = *v11++;
              *(v9++ - 1) = v12;
              v13 = *v11++;
              *(v9 - 1) = v13;
              v6 = v9 + 1;
              v14 = *v11;
              v8 = v11 + 1;
              *(v6 - 1) = v14;
            } while (v7 < 32);
            ++v4;
            v5 += 1024;
          } while (v4 < v3);
          v21 += 256;
        }
        qmemcpy(v19, v16, 0x2000u);
      }
      v19 += 0x2000;
      v20 -= 8;
      ++v18;
    } while (v18 <= v17);
  }
  return fre(&v16);*/
}

//-------------------------------------------------------------------------------------------------

int drbox(int a1, int a2, int a3, int a4, char a5)
{
  return 0;/*
  int result; // eax
  int v6; // edi
  int i; // esi
  int v8; // eax
  int j; // edx

  result = scrbuf + a1;
  v6 = result + winw * (199 - a2);
  for (i = 0; i < a4; ++i) {
    v8 = v6;
    v6 += winw;
    for (j = 0; j < a3; *(_BYTE *)(v8 - 1) = a5) {
      ++v8;
      ++j;
    }
    result = a4;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

char *box(int a1, int a2, int a3, int a4, char a5)
{
  return 0;/*
  int v5; // esi
  int v6; // ebp
  int v7; // edi
  int v8; // eax
  _BYTE *v9; // edx
  int i; // ebx
  _BYTE *result; // eax
  _BYTE *v12; // edx
  int j; // ebx

  v5 = winw;
  v6 = 199 - a2;
  v7 = a3 - 2;
  v8 = a1 + scrbuf + winw * (199 - a2);
  v9 = (_BYTE *)(winw * (a4 + 199 - a2 - 1) + a1 + scrbuf);
  for (i = 0; i < v7; *v9 = a5) {
    ++v9;
    *(_BYTE *)++v8 = a5;
    ++i;
  }
  result = (_BYTE *)(v5 * v6 + scrbuf + a1);
  v12 = (_BYTE *)(a3 + a1 - 1 + scrbuf + v5 * v6);
  for (j = 0; j <= a4 - 1; v12 += v5) {
    ++j;
    *result = a5;
    result += v5;
    *v12 = a5;
  }
  winw = v5;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int SetVideoMode(char a1)
{
  return 0;/*
  _BYTE v2[36]; // [esp+0h] [ebp-24h] BYREF

  v2[0] = a1;
  v2[1] = 0;
  return int386(16, (int)v2, (int)v2);*/
}

//-------------------------------------------------------------------------------------------------

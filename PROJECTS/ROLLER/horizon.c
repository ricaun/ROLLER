#include "horizon.h"
#include "3d.h"
#include "graphics.h"
#include "polyf.h"
#include "polytex.h"
#include "transfrm.h"
#include "drawtrk3.h"
#include <math.h>
#include <stdlib.h>
//-------------------------------------------------------------------------------------------------

tCloudData cloud[40]; //00199950
int test_y1;          //0019A3F4

//-------------------------------------------------------------------------------------------------
//0006AB90
void DrawHorizon(int a1)
{
  /*
  int v1; // edx
  int v2; // ecx
  unsigned __int8 v3; // dl
  int v4; // eax
  int v5; // eax
  double v6; // st7
  double v7; // st6
  double v8; // st7
  int v9; // eax
  int v10; // esi
  int v11; // edi
  int v12; // eax
  int v13; // eax
  int v14; // eax
  __int16 v15; // fps
  _BOOL1 v16; // c0
  char v17; // c2
  _BOOL1 v18; // c3
  int v19; // eax
  int v20; // edx
  int v21; // edi
  int v22; // esi
  double v23; // st7
  double v24; // st6
  int v25; // edx
  int v26; // edi
  int v27; // ebp
  double v28; // st7
  double v29; // st7
  double v30; // st6
  int v31; // esi
  int v32; // esi
  int v33; // ecx
  int v34; // eax
  int v35; // edi
  int v36; // esi
  double v37; // st7
  int v38; // ebp
  double v39; // st7
  double v40; // st6
  int v41[2]; // [esp+14h] [ebp-70h] BYREF
  int v42[2]; // [esp+1Ch] [ebp-68h] BYREF
  double v43; // [esp+24h] [ebp-60h]
  float v44; // [esp+2Ch] [ebp-58h]
  int v45; // [esp+38h] [ebp-4Ch]
  int v46; // [esp+3Ch] [ebp-48h]
  int v47; // [esp+40h] [ebp-44h]
  int v48; // [esp+44h] [ebp-40h]
  int v49; // [esp+48h] [ebp-3Ch]
  float v50; // [esp+4Ch] [ebp-38h]
  float v51; // [esp+50h] [ebp-34h]
  float v52; // [esp+54h] [ebp-30h]
  float v53; // [esp+58h] [ebp-2Ch]
  int v54; // [esp+5Ch] [ebp-28h]
  int v55; // [esp+60h] [ebp-24h]
  unsigned __int8 v56; // [esp+64h] [ebp-20h]
  unsigned __int8 v57; // [esp+68h] [ebp-1Ch]

  v48 = a1;
  v1 = worldelev & 0x3FFF;
  v43 = tsin[v1];
  v2 = a1;
  v56 = -111;
  v57 = HorizonColour[4 * front_sec];
  if (v43 > horizon_c_variable_1 || v43 < horizon_c_variable_2 || (textures_off & 0x10) != 0) {
    if (tsin[worldelev & 0x3FFF] <= horizon_c_variable_1)
      v3 = v57;
    else
      v3 = v56;
    if ((textures_off & 0x10) != 0)
      v3 = v56;
    memset(a1, v3, winh * winw);
  } else {
    v4 = worldtilt & 0x3FFF;
    v53 = -tsin[v4];
    v52 = tcos[v4];
    upside_down = tcos[worldelev & 0x3FFF] < 0.0 != v52 < 0.0;
    ground_left = v53 < 0.0;
    if (tcos[worldelev & 0x3FFF] < 0.0)
      ground_left = v53 >= 0.0;
    v5 = worldelev & 0x3FFF;
    v6 = (double)VIEWDIST * ptan[v5];
    v7 = v6 * v53 + (double)xbase;
    _CHP(v5, v1 * 4);
    v47 = (int)v7;
    v45 = 199 - ybase;
    v8 = (double)(199 - ybase) + v6 * v52;
    _CHP(v9, 199 - ybase);
    v49 = (int)v8;
    if ((LODWORD(v53) & 0x7FFFFFFF) != 0)
      v50 = v52 / v53;
    else
      v50 = 41.0;
    if (v50 <= (double)horizon_c_variable_3 && v50 >= (double)horizon_c_variable_4) {
      v51 = (double)scr_size * horizon_c_variable_5;
      v19 = worldelev & 0x3FFF;
      v16 = tcos[v19] > 0.0;
      v17 = 0;
      v18 = 0.0 == tcos[v19];
      LOWORD(v19) = v15;
      if (!v16 && !v18) {
        HIBYTE(v52) ^= 0x80u;
        HIBYTE(v53) ^= 0x80u;
      }
      v20 = winh;
      *(float *)&v54 = ((double)v49 * v50 + (double)v47) * v51;
      if (winh > 0) {
        v21 = 4 * winh;
        v22 = 0;
        v23 = v50;
        do {
          v24 = *(float *)&v54 - v23;
          v22 += 4;
          v19 = v54;
          GroundPt_variable_7[v22 / 4u] = v54;
          *(float *)&v54 = v24;
        } while (v22 < v21);
      }
      if (ground_left) {
        v25 = winh;
        v26 = 0;
        if (winh > 0) {
          v27 = 0;
          do {
            v28 = hor_scan[v27];
            _CHP(v19, v25);
            v46 = (int)v28;
            if ((int)v28 <= winw) {
              if ((int)v28 >= 0) {
                v31 = v46;
                v19 = memset(v2, v57, v46);
                v2 += v31;
              } else {
                v29 = (double)v46;
                v30 = 1.0 / v51;
                v44 = -v52 * v29 * v30;
                modf(v29 * v53 * v30, (int)v41);
                modf(v44, (int)v42);
                v19 = 0;
                v46 = 0;
              }
              v25 = v46;
              v32 = winw - v46;
              if (winw - v46 >= 0) {
                v25 = v56;
                v19 = memset(v2, v56, winw - v46);
                v2 += v32;
              }
            } else {
              v25 = v57;
              v19 = memset(v2, v57, winw);
              v2 += winw;
            }
            ++v26;
            ++v27;
          } while (v26 < winh);
        }
      } else {
        v33 = winw - 1 + v2;
        v34 = winh;
        v35 = 0;
        if (winh > 0) {
          v36 = 0;
          do {
            v37 = hor_scan[v36];
            _CHP(v34, v20);
            v55 = (int)v37;
            v38 = (int)v37;
            if ((int)v37 >= 0) {
              if (v38 <= winw) {
                v33 -= winw - v38;
                v20 = v57;
                memset(v33 + 1, v57, winw - v38);
              } else {
                v20 = v38 - (winw - 1);
                v45 = v20;
                v39 = (double)v20;
                v40 = 1.0 / v51;
                v44 = -v52 * v39 * v40;
                modf(v39 * v53 * v40, (int)v41);
                modf(v44, (int)v42);
                v55 = winw;
              }
              if (v55 >= 0) {
                v33 -= v55;
                v20 = v56;
                memset(v33 + 1, v56, v55);
              }
              v34 = 2 * winw;
              v33 += 2 * winw;
            } else {
              v20 = v57;
              v34 = memset(v33 - winw + 1, v57, winw);
              v33 += winw;
            }
            ++v35;
            ++v36;
          } while (v35 < winh);
        }
      }
    } else {
      if (upside_down) {
        v10 = (v49 * scr_size + 32 - (__CFSHL__((v49 * scr_size + 32) >> 31, 6) + ((v49 * scr_size + 32) >> 31 << 6))) >> 6;
        if (v10 > winh)
          v10 = winh;
        if (v10 > 0) {
          memset(v2, v57, v10 * winw);
          v2 += v10 * winw;
        }
      } else {
        v10 = (v49 * scr_size - (__CFSHL__((v49 * scr_size) >> 31, 6) + ((v49 * scr_size) >> 31 << 6))) >> 6;
        v11 = v10;
        if (v10 > winh)
          v10 = winh;
        if (v11 > winh)
          v11 = winh;
        if (v11 > 0) {
          memset(v2, v56, v11 * winw);
          v2 += winw * v11;
        }
      }
      if (upside_down) {
        v12 = (v49 * scr_size + 32 - (__CFSHL__((v49 * scr_size + 32) >> 31, 6) + ((v49 * scr_size + 32) >> 31 << 6))) >> 6;
        if (v12 > winh)
          v12 = winh;
        v13 = winh - v12;
        if (v13 > winh)
          v13 = winh;
        if (v13 > 0)
          memset(v2, v56, v13 * winw);
      } else {
        v14 = winh - v10;
        if (winh - v10 > winh)
          v14 = winh;
        if (v14 > 0)
          memset(v2, v57, v14 * winw);
      }
    }
  }
  if ((textures_off & 8) == 0)
    displayclouds();*/
}

//-------------------------------------------------------------------------------------------------
//0006B1A0
void initclouds()
{                                               // Loop through all 40 cloud slots
  int iCloudIdx; // edi
  int iRandVal1; // eax
  int iAngle1Calc; // eax
  int iAngle1; // ebp
  int iRandVal2; // eax
  int iAngle2; // esi
  double dRadiusRotComp1; // st6
  double dRadiusRotComp2; // st5
  double dBaseCalcX; // st4
  double dBaseCalcY; // st6
  int iValidPlacement; // ecx
  double dMatrix12; // st6
  double dMatrix20Temp; // st3
  double dMatrix21Temp; // st2
  double dMatrix22Temp; // rt1
  int iRandColorBase; // eax
  int iColorIndex; // eax
  int iCheckIdx; // edx
  double fDeltaX; // st7
  double fDeltaY; // st6
  double fXYDistSq; // st7
  double fDeltaZ; // st6
  float fCos1Cos2; // [esp+8h] [ebp-80h]
  float fTransX2; // [esp+Ch] [ebp-7Ch]
  float fSin1Cos2; // [esp+10h] [ebp-78h]
  float fTransX1; // [esp+14h] [ebp-74h]
  float fTransY2; // [esp+18h] [ebp-70h]
  float fTransZ1; // [esp+1Ch] [ebp-6Ch]
  float fTransY1; // [esp+20h] [ebp-68h]
  float fMatrix11; // [esp+24h] [ebp-64h]
  float fMatrix02; // [esp+28h] [ebp-60h]
  float fMatrix10; // [esp+2Ch] [ebp-5Ch]
  float fMatrix00; // [esp+30h] [ebp-58h]
  float fMatrix01; // [esp+34h] [ebp-54h]
  float fRadiusComp; // [esp+38h] [ebp-50h]
  float fSin2; // [esp+3Ch] [ebp-4Ch]
  float fBaseY; // [esp+40h] [ebp-48h]
  float fBaseX; // [esp+44h] [ebp-44h]
  float fRotComp2; // [esp+48h] [ebp-40h]
  float fRotComp1; // [esp+4Ch] [ebp-3Ch]
  float fBaseZ; // [esp+50h] [ebp-38h]
  float fCos2; // [esp+54h] [ebp-34h]
  float fNegSin1; // [esp+58h] [ebp-30h]
  float fCos1; // [esp+5Ch] [ebp-2Ch]
  float fNegRadius; // [esp+60h] [ebp-28h]
  float fRadius; // [esp+64h] [ebp-24h]
  float fMinDistance; // [esp+68h] [ebp-20h]
  float fDistance; // [esp+6Ch] [ebp-1Ch]

  for (iCloudIdx = 0; iCloudIdx < 40; ++iCloudIdx) {
    fRadius = 1800000.0;                        // Start with maximum radius for placement attempt
    do {
      iRandVal1 = rand();                       // Generate random angle1 (theta) for spherical coordinates
      iAngle1Calc = 3400 * ((iRandVal1 * iRandVal1) % 32768) / 32768;
      //iAngle1Calc = 3400 * ((iRandVal1 * iRandVal1 - (__CFSHL__((iRandVal1 * iRandVal1) >> 31, 15) + ((iRandVal1 * iRandVal1) >> 31 << 15))) >> 15);
      iAngle1 = (iAngle1Calc % 32768) / 32768 + 520;
      //iAngle1 = ((iAngle1Calc - (__CFSHL__(iAngle1Calc >> 31, 15) + (iAngle1Calc >> 31 << 15))) >> 15) + 520;
      iRandVal2 = rand();                       // Generate random angle2 (phi) for spherical coordinates
      iAngle2 = iRandVal2 / 2;
      //iAngle2 = ((iRandVal2 << 14) - (__CFSHL__(iRandVal2 << 14 >> 31, 15) + (iRandVal2 << 14 >> 31 << 15))) >> 15;
      fCos1Cos2 = tcos[iAngle2] * tcos[iAngle1];// Calculate rotation matrix elements using trigonometric tables
      fSin1Cos2 = tsin[iAngle2] * tcos[iAngle1];
      fNegSin1 = -tsin[iAngle2];
      fSin2 = tsin[iAngle1];
      fCos1 = tcos[iAngle2];
      fRotComp1 = -fCos1 * fSin2;               // Calculate rotation matrix components: -cos(phi)*sin(theta) and -sin(phi)*sin(theta)
      fRotComp2 = fNegSin1 * fSin2;
      fNegRadius = -fRadius;                    // Negative radius for translation calculations
      fBaseX = 10000000.0f * fCos1Cos2;          // Calculate 3x4 transformation matrix for cloud positioning
      fTransX1 = fNegRadius * fNegSin1;
      fMatrix00 = fBaseX + fTransX1;
      dRadiusRotComp1 = fRadius * fRotComp1;
      cloud[iCloudIdx].matrix[0][0] = fMatrix00 + (float)dRadiusRotComp1;
      fBaseY = 10000000.0f * fSin1Cos2;
      fTransY1 = fNegRadius * fCos1;
      fMatrix01 = fBaseY + fTransY1;
      dRadiusRotComp2 = fRadius * fRotComp2;
      cloud[iCloudIdx].matrix[0][1] = fMatrix01 + (float)dRadiusRotComp2;
      fBaseZ = 10000000.0f * fSin2;
      fTransZ1 = 0.0f * fNegRadius;
      fMatrix02 = fBaseZ + fTransZ1;
      fCos2 = tcos[iAngle1];
      fRadiusComp = fRadius * fCos2;
      cloud[iCloudIdx].matrix[0][2] = fMatrix02 + fRadiusComp;
      fTransX2 = fRadius * fNegSin1;
      dBaseCalcX = fBaseX + fTransX2;
      fMatrix10 = (float)dBaseCalcX;
      cloud[iCloudIdx].matrix[1][0] = (float)(dRadiusRotComp1 + dBaseCalcX);
      fTransY2 = fRadius * fCos1;
      dBaseCalcY = fBaseY + fTransY2;
      fMatrix11 = (float)dBaseCalcY;
      iValidPlacement = -1;
      cloud[iCloudIdx].matrix[1][1] = (float)(dRadiusRotComp2 + dBaseCalcY);
      dMatrix12 = 0.0 * fRadius + fBaseZ;
      cloud[iCloudIdx].matrix[1][2] = (float)dMatrix12 + fRadiusComp;
      dMatrix20Temp = fNegRadius * fRotComp1;
      cloud[iCloudIdx].matrix[2][0] = fMatrix10 + (float)dMatrix20Temp;
      dMatrix21Temp = fNegRadius * fRotComp2;
      cloud[iCloudIdx].matrix[2][1] = fMatrix11 + (float)dMatrix21Temp;
      dMatrix22Temp = fNegRadius * fCos2;
      cloud[iCloudIdx].matrix[2][2] = (float)(dMatrix12 + dMatrix22Temp);
      cloud[iCloudIdx].matrix[3][0] = (float)dMatrix20Temp + fMatrix00;
      cloud[iCloudIdx].matrix[3][1] = (float)dMatrix21Temp + fMatrix01;
      cloud[iCloudIdx].matrix[3][2] = (float)dMatrix22Temp + fMatrix02;
      cloud[iCloudIdx].world.fX = fRotComp1 * 0.0f + 0.0f * fNegSin1 + fBaseX;// World X coordinate: final cloud position after transformation
      cloud[iCloudIdx].world.fY = 0.0f * fCos1 + fBaseY + 0.0f * fRotComp2;// World Y coordinate: final cloud position after transformation
      cloud[iCloudIdx].world.fZ = fBaseZ + 0.0f * fCos2;// World Z coordinate: final cloud position after transformation
      iRandColorBase = rand();                  // Generate random cloud color/texture index
      iColorIndex = (5 * iRandColorBase) % 32768 / 32768;
      //iColorIndex = (5 * iRandColorBase - (__CFSHL__((5 * iRandColorBase) >> 31, 15) + ((5 * iRandColorBase) >> 31 << 15))) >> 15;
      cloud[iCloudIdx].iSurfaceType = iColorIndex;
      cloud[iCloudIdx].iSurfaceType = iColorIndex + 0x508;
      if (rand() < 0x4000)                    // Randomly modify color properties (50% chance each)
        cloud[iCloudIdx].iSurfaceType += 0x1000;
      if (rand() < 0x4000)
        SET_HIWORD(cloud[iCloudIdx].iSurfaceType, 4 + GET_HIWORD(cloud[iCloudIdx].iSurfaceType));
        //HIWORD(cloud[iCloudIdx].iSurfaceType) += 4;
      cloud[iCloudIdx].fRadius = fRadius;       // Store cloud radius
      if (iCloudIdx > 0) {                                         // Check collision with previously placed clouds
        for (iCheckIdx = 0; iCheckIdx < iCloudIdx; ++iCheckIdx) {
          if (iValidPlacement) {
            fDeltaX = cloud[iCheckIdx].world.fX - cloud[iCloudIdx].world.fX;
            fDeltaY = cloud[iCheckIdx].world.fY - cloud[iCloudIdx].world.fY;
            fXYDistSq = fDeltaX * fDeltaX + fDeltaY * fDeltaY;
            fDeltaZ = cloud[iCheckIdx].world.fZ - cloud[iCloudIdx].world.fZ;
            fDistance = (float)sqrt(fXYDistSq + fDeltaZ * fDeltaZ);// Calculate 3D distance between cloud centers
          }
          fMinDistance = fRadius + cloud[iCloudIdx].fRadius;
          if (fDistance < fMinDistance * 1.3f) // Check if clouds overlap (distance < combined radii * 1.3)
            iValidPlacement = 0;
        }
      }
      if (!iValidPlacement)
        fRadius = fRadius + -2000.0f;            // Reduce radius and retry if collision detected
      if (fRadius < 1000000.0f)                // Minimum radius constraint
        fRadius = 1000000.0f;
    } while (!iValidPlacement);
  }
}

//-------------------------------------------------------------------------------------------------
//0006B530
void displayclouds(uint8 *pScrBuf)
{
  int iCloudIdx; // esi
  double dCorner0X; // st7
  double dCorner0Y; // st6
  double dCorner0Z; // st5
  double dCorner0ViewZ; // st7
  int iBehindCamera; // edx
  double dViewDist; // st7
  double dInvZ0; // st6
  double dProjX0; // st5
  double dProjY0; // st7
  int iScrSizeTemp; // ecx
  //int iXpTemp; // eax
  double dScreenX0; // st7
  double dScreenY0; // st7
  double dCorner1X; // st7
  double dCorner1Y; // st6
  double dCorner1Z; // st5
  double dCorner1ViewZ; // st7
  double dViewDist1; // st7
  double dInvZ1; // st6
  double dProjX1; // st5
  double dProjY1; // st7
  int iScrSize1; // ebx
  //int iXpTemp1; // eax
  double dScreenX1; // st7
  double dScreenY1; // st7
  double dCorner2X; // st7
  double dCorner2Y; // st6
  double dCorner2Z; // st5
  double dCorner2ViewZ; // st7
  double dViewDist2; // st7
  double dInvZ2; // st6
  double dProjX2; // st5
  double dProjY2; // st7
  int iScrSize2; // ebx
  //int iXpTemp2; // eax
  double dScreenX2; // st7
  double dScreenY2; // st7
  double dCorner3X; // st7
  double dCorner3Y; // st6
  double dCorner3Z; // st5
  double dCorner3ViewZ; // st7
  double dViewDist3; // st7
  double dInvZ3; // st6
  double dProjX3; // st5
  double dProjY3; // st7
  int iScrSize3; // ebx
  //int iXpTemp3; // eax
  double dScreenX3; // st7
  double dScreenY3; // st7
  tPolyParams poly; // [esp+0h] [ebp-A8h] BYREF
  int iYCalcTemp; // [esp+38h] [ebp-70h]
  float fViewX0; // [esp+3Ch] [ebp-6Ch]
  float fViewY0; // [esp+40h] [ebp-68h]
  float fViewY1; // [esp+44h] [ebp-64h]
  float fViewX3; // [esp+48h] [ebp-60h]
  float fViewX2; // [esp+4Ch] [ebp-5Ch]
  float fViewY3; // [esp+50h] [ebp-58h]
  float fViewY2; // [esp+54h] [ebp-54h]
  float fViewX1; // [esp+58h] [ebp-50h]
  float fScreenX0; // [esp+5Ch] [ebp-4Ch]
  float fViewZ0; // [esp+60h] [ebp-48h]
  float fScreenY0; // [esp+64h] [ebp-44h]
  float fScreenX2; // [esp+68h] [ebp-40h]
  float fScreenX1; // [esp+6Ch] [ebp-3Ch]
  float fViewZ3; // [esp+70h] [ebp-38h]
  float fViewZ2; // [esp+74h] [ebp-34h]
  float fViewZ1; // [esp+78h] [ebp-30h]
  float fScreenX3; // [esp+7Ch] [ebp-2Ch]
  float fScreenY1; // [esp+80h] [ebp-28h]
  float fScreenY3; // [esp+84h] [ebp-24h]
  float fScreenY2; // [esp+88h] [ebp-20h]
  //int iScreenXTemp; // [esp+8Ch] [ebp-1Ch]

  set_starts(0);                                // Initialize polygon renderer
  if ((textures_off & 8) == 0)                // Skip cloud rendering if textures disabled (bit 3 of textures_off)
  {                                             // Loop through all 40 cloud objects
    for (iCloudIdx = 0; iCloudIdx != 40; ++iCloudIdx) {
      dCorner0X = cloud[iCloudIdx].matrix[0][0] - viewx;// Transform cloud corner 0 from world space to camera space
      dCorner0Y = cloud[iCloudIdx].matrix[0][1] - viewy;
      dCorner0Z = cloud[iCloudIdx].matrix[0][2] * 0.5 - viewz;
      fViewX0 = (float)(dCorner0X * vk1 + dCorner0Y * vk4 + dCorner0Z * vk7);// Apply view matrix transformation to get view coordinates
      fViewY0 = (float)(dCorner0X * vk2 + dCorner0Y * vk5 + dCorner0Z * vk8);
      dCorner0ViewZ = dCorner0X * vk3 + dCorner0Y * vk6 + dCorner0Z * vk9;
      fViewZ0 = (float)dCorner0ViewZ;
      iBehindCamera = 0;                        // Check for near clipping (minimum Z distance = 80.0)
      if (dCorner0ViewZ < 80.0) {
        iBehindCamera = 1;
        fViewZ0 = 80.0;
      }
      dViewDist = (double)VIEWDIST;             // Project 3D coordinates to 2D screen coordinates using perspective division
      dInvZ0 = 1.0 / fViewZ0;
      dProjX0 = dViewDist * fViewX0 * dInvZ0 + (double)xbase;
      //_CHP();
      xp = (int)dProjX0;
      dProjY0 = dInvZ0 * (dViewDist * fViewY0) + (double)ybase;
      iScrSizeTemp = scr_size;
      //_CHP();
      yp = (int)dProjY0;
      fScreenX0 = (float)(xp >> 6);        // Convert to screen space and check clipping bounds (-5000 to +5000)
      iYCalcTemp = (iScrSizeTemp * (199 - (int)dProjY0)) >> 6;
      fScreenY0 = (float)iYCalcTemp;
      if (iBehindCamera || fScreenX0 >= -5000.0 && fScreenX0 <= 5000.0 && fScreenY0 >= -5000.0 && fScreenY0 <= 5000.0) {
        dScreenX0 = fScreenX0;                  // Store vertex 0 coordinates in polygon structure
        //_CHP();
        poly.vertices[0].x = (int)dScreenX0;
        dScreenY0 = fScreenY0;
        //_CHP();
        poly.vertices[0].y = (int)dScreenY0;
      } else {
        iBehindCamera = 1;
      }
      if (!iBehindCamera) {
        dCorner1X = cloud[iCloudIdx].matrix[1][0] - viewx;// Transform cloud corner 1 (repeat process for second vertex)
        dCorner1Y = cloud[iCloudIdx].matrix[1][1] - viewy;
        dCorner1Z = cloud[iCloudIdx].matrix[1][2] * 0.5 - viewz;
        fViewX1 = (float)(dCorner1X * vk1 + dCorner1Y * vk4 + dCorner1Z * vk7);
        fViewY1 = (float)(dCorner1X * vk2 + dCorner1Y * vk5 + dCorner1Z * vk8);
        dCorner1ViewZ = dCorner1X * vk3 + dCorner1Y * vk6 + dCorner1Z * vk9;
        fViewZ1 = (float)dCorner1ViewZ;
        if (dCorner1ViewZ < 80.0) {
          iBehindCamera = 1;
          fViewZ1 = 80.0;
        }
        dViewDist1 = (double)VIEWDIST;
        dInvZ1 = 1.0 / fViewZ1;
        dProjX1 = dViewDist1 * fViewX1 * dInvZ1 + (double)xbase;
        //_CHP();
        xp = (int)dProjX1;
        dProjY1 = dInvZ1 * (dViewDist1 * fViewY1) + (double)ybase;
        iScrSize1 = scr_size;
        //_CHP();
        yp = (int)dProjY1;
        //iScreenXTemp = xp >> 6;
        fScreenX1 = (float)(xp >> 6);
        iYCalcTemp = (iScrSize1 * (199 - (int)dProjY1)) >> 6;
        fScreenY1 = (float)iYCalcTemp;
        if (iBehindCamera || fScreenX1 >= -5000.0 && fScreenX1 <= 5000.0 && fScreenY1 >= -5000.0 && fScreenY1 <= 5000.0) {
          dScreenX1 = fScreenX1;                // Store vertex 1 coordinates in polygon structure
          //_CHP();
          poly.vertices[1].x = (int)dScreenX1;
          dScreenY1 = fScreenY1;
          //_CHP();
          poly.vertices[1].y = (int)dScreenY1;
        } else {
          iBehindCamera = 1;
        }
        if (!iBehindCamera) {
          dCorner2X = cloud[iCloudIdx].matrix[2][0] - viewx;// Transform cloud corner 2 (third vertex of quad)
          dCorner2Y = cloud[iCloudIdx].matrix[2][1] - viewy;
          dCorner2Z = cloud[iCloudIdx].matrix[2][2] * 0.5 - viewz;
          fViewX2 = (float)(dCorner2X * vk1 + dCorner2Y * vk4 + dCorner2Z * vk7);
          fViewY2 = (float)(dCorner2X * vk2 + dCorner2Y * vk5 + dCorner2Z * vk8);
          dCorner2ViewZ = dCorner2X * vk3 + dCorner2Y * vk6 + dCorner2Z * vk9;
          fViewZ2 = (float)dCorner2ViewZ;
          if (dCorner2ViewZ < 80.0) {
            iBehindCamera = 1;
            fViewZ2 = 80.0;
          }
          dViewDist2 = (double)VIEWDIST;
          dInvZ2 = 1.0 / fViewZ2;
          dProjX2 = dViewDist2 * fViewX2 * dInvZ2 + (double)xbase;
          //_CHP();
          xp = (int)dProjX2;
          dProjY2 = dInvZ2 * (dViewDist2 * fViewY2) + (double)ybase;
          iScrSize2 = scr_size;
          //_CHP();
          yp = (int)dProjY2;
          fScreenX2 = (float)(xp >> 6);
          iYCalcTemp = (iScrSize2 * (199 - (int)dProjY2)) >> 6;
          fScreenY2 = (float)iYCalcTemp;
          if (iBehindCamera || fScreenX2 >= -5000.0 && fScreenX2 <= 5000.0 && fScreenY2 >= -5000.0 && fScreenY2 <= 5000.0) {
            dScreenX2 = fScreenX2;              // Store vertex 2 coordinates in polygon structure
            //_CHP();
            poly.vertices[2].x = (int)dScreenX2;
            dScreenY2 = fScreenY2;
            //_CHP();
            poly.vertices[2].y = (int)dScreenY2;
          } else {
            iBehindCamera = 1;
          }
          if (!iBehindCamera) {
            dCorner3X = cloud[iCloudIdx].matrix[3][0] - viewx;// Transform cloud corner 3 (final vertex of quad)
            dCorner3Y = cloud[iCloudIdx].matrix[3][1] - viewy;
            dCorner3Z = cloud[iCloudIdx].matrix[3][2] * 0.5 - viewz;
            fViewX3 = (float)(dCorner3X * vk1 + dCorner3Y * vk4 + dCorner3Z * vk7);
            fViewY3 = (float)(dCorner3X * vk2 + dCorner3Y * vk5 + dCorner3Z * vk8);
            dCorner3ViewZ = dCorner3X * vk3 + dCorner3Y * vk6 + dCorner3Z * vk9;
            fViewZ3 = (float)dCorner3ViewZ;
            if (dCorner3ViewZ < 80.0) {
              iBehindCamera = 1;
              fViewZ3 = 80.0;
            }
            dViewDist3 = (double)VIEWDIST;
            dInvZ3 = 1.0 / fViewZ3;
            dProjX3 = dViewDist3 * fViewX3 * dInvZ3 + (double)xbase;
            //_CHP();
            xp = (int)dProjX3;
            dProjY3 = dInvZ3 * (dViewDist3 * fViewY3) + (double)ybase;
            iScrSize3 = scr_size;
            //_CHP();
            yp = (int)dProjY3;
            fScreenX3 = (float)(xp >> 6);
            iYCalcTemp = (iScrSize3 * (199 - (int)dProjY3)) >> 6;
            fScreenY3 = (float)iYCalcTemp;
            if (iBehindCamera || fScreenX3 >= -5000.0 && fScreenX3 <= 5000.0 && fScreenY3 >= -5000.0 && fScreenY3 <= 5000.0) {
              dScreenX3 = fScreenX3;            // Store vertex 3 coordinates in polygon structure
              //_CHP();
              poly.vertices[3].x = (int)dScreenX3;
              dScreenY3 = fScreenY3;
              //_CHP();
              poly.vertices[3].y = (int)dScreenY3;
            } else {
              iBehindCamera = 1;
            }
            if (!iBehindCamera) {
              poly.iSurfaceType = cloud[iCloudIdx].iSurfaceType;// Set polygon surface type and vertex count (quad = 4 vertices)
              poly.uiNumVerts = -4;
              POLYTEX(cargen_vga, pScrBuf, &poly, 18, gfx_size);// Render textured polygon to screen buffer
            }
          }
        }
      }
    }
  }
}

//-------------------------------------------------------------------------------------------------
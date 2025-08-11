#include "view.h"
#include "3d.h"
#include "car.h"
#include "moving.h"
#include "replay.h"
#include "transfrm.h"
#include "control.h"
#include <math.h>
#include <float.h>
//-------------------------------------------------------------------------------------------------

tViewData viewdata[2] =       //000A74A8
{
  { 4500.0, 500.0, 640.0, -240.0, 200.0, 160.0 },
  { 2000.0, 500.0, 450.0, 350.0, 200.0, 100.0 }
};
int chaseview[2] = { 0, 0 };  //000A74D8
float CHASE_DIST[2] = { 4500.0, 4500.0 }; //000A74E0
float CHASE_MIN[2] = { 500.0, 500.0 };  //000A74E8
float PULLZ[2] = { 640.0, 640.0 }; //000A74F0
float LOOKZ[2] = { 160.0, 160.0 }; //000A74F8
int nextpoint[2] = { 0, 0 };  //000A7500
tCameraPos lastpos[2][64];    //001A1250
int lastcamelevation;         //001A1A60
int lastcamdirection;         //001A1A64
int NearTow;                  //001A1A68
float chase_x;                //001A1A6C
float chase_y;                //001A1A70
float chase_z;                //001A1A74

//-------------------------------------------------------------------------------------------------
//000729C0
int calculateview(int a1, int a2, int a3)
{
  return 0; /*
  int v4; // esi
  unsigned int v5; // eax
  int v6; // eax
  float *v7; // eax
  int v8; // edx
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  double v13; // st7
  int v14; // eax
  double v15; // st7
  double v16; // st6
  double v17; // st4
  long double v18; // st3
  int v19; // eax
  int result; // eax
  float v21; // edx
  int v22; // eax
  float *v23; // eax
  int v24; // eax
  float *v25; // eax
  int v26; // eax
  int v27; // edi
  int v28; // edi
  int v29; // [esp-18h] [ebp-E4h]
  int v30; // [esp-14h] [ebp-E0h]
  int v31; // [esp-10h] [ebp-DCh]
  double v32; // [esp+0h] [ebp-CCh]
  double v33; // [esp+8h] [ebp-C4h]
  double v34; // [esp+10h] [ebp-BCh]
  float v35; // [esp+2Ch] [ebp-A0h]
  float v36; // [esp+30h] [ebp-9Ch]
  float v37; // [esp+34h] [ebp-98h]
  float v38; // [esp+38h] [ebp-94h]
  float v39; // [esp+3Ch] [ebp-90h]
  float v40; // [esp+40h] [ebp-8Ch]
  float v41; // [esp+44h] [ebp-88h]
  int v42; // [esp+48h] [ebp-84h]
  int v43; // [esp+4Ch] [ebp-80h]
  float v44; // [esp+50h] [ebp-7Ch]
  float v45; // [esp+54h] [ebp-78h]
  int v46; // [esp+58h] [ebp-74h]
  float v47; // [esp+5Ch] [ebp-70h]
  float v48; // [esp+60h] [ebp-6Ch]
  float v49; // [esp+64h] [ebp-68h]
  int v50; // [esp+6Ch] [ebp-60h]
  float v51; // [esp+70h] [ebp-5Ch]
  float v52; // [esp+74h] [ebp-58h]
  float v53; // [esp+78h] [ebp-54h]
  float v54; // [esp+7Ch] [ebp-50h]
  float v55; // [esp+80h] [ebp-4Ch]
  float v56; // [esp+84h] [ebp-48h]
  float v57; // [esp+88h] [ebp-44h]
  float v58; // [esp+8Ch] [ebp-40h]
  float v59; // [esp+90h] [ebp-3Ch]
  int v60; // [esp+94h] [ebp-38h]
  float v61; // [esp+98h] [ebp-34h]
  float v62; // [esp+9Ch] [ebp-30h]
  float v63; // [esp+A0h] [ebp-2Ch]
  int v64; // [esp+A4h] [ebp-28h]
  int v65; // [esp+A8h] [ebp-24h]
  float v66; // [esp+ACh] [ebp-20h]
  float v67; // [esp+B0h] [ebp-1Ch]
  float v68; // [esp+B4h] [ebp-18h]
  float v69; // [esp+B8h] [ebp-14h]
  float v70; // [esp+B8h] [ebp-14h]

  VIEWDIST = 200;
  v4 = -1;
  if (a1 < -1) {
    if (a1 != -2)
      goto LABEL_8;
  LABEL_6:
    ext_x = 1093664768;
    ext_y = 0;
    ext_z = 1091567616;
    goto LABEL_9;
  }
  if (a1 <= 0) {
    ext_x = 0;
    ext_y = 0;
    ext_z = 1077936128;
    goto LABEL_9;
  }
  if (a1 == 1)
    goto LABEL_6;
LABEL_8:
  ext_x = -1082130432;
  ext_y = -1082130432;
  ext_z = -1082130432;
LABEL_9:
  v5 = 154 * a2;
  if (a1 < 3) {
    if (a1 >= 0) {
      mirror = 0;
      if (a1 == 1) {
        if (Car_variable_48[77 * a2])
          v27 = Car_variable_36[77 * a2] + Car_variable_6[154 * a2];
        else
          v27 = Car_variable_34[77 * a2] + Car_variable_36[77 * a2] + Car_variable_6[154 * a2];
        v64 = ((_WORD)v27 + 0x2000) & 0x3FFF;
        v26 = Car_variable_35[77 * a2] + Car_variable_37[77 * a2] + Car_variable_5[154 * a2] + 0x2000;
      } else {
        if (Car_variable_48[77 * a2])
          v28 = Car_variable_36[77 * a2] + Car_variable_6[154 * a2];
        else
          v28 = Car_variable_34[77 * a2] + Car_variable_36[77 * a2] + Car_variable_6[154 * a2];
        v64 = ((_WORD)v28 + 455) & 0x3FFF;
        v26 = Car_variable_35[77 * a2] + Car_variable_37[77 * a2] + Car_variable_5[154 * a2];
      }
    } else {
      mirror = -1;
      v64 = (LOWORD(Car_variable_36[77 * a2]) + Car_variable_6[154 * a2] + 0x2000) & 0x3FFF;
      v26 = Car_variable_37[77 * a2] + Car_variable_5[154 * a2] + 0x2000;
    }
    v60 = v26 & 0x3FFF;
    NearTow = -1;
    if (a1 == 2)
      return newchaseview(a2, a3);
    v36 = *(float *)&ext_y * view_c_variable_1;
    v37 = *(float *)&ext_z * view_c_variable_2;
    v35 = *(float *)&ext_x * view_c_variable_1;
    v38 = DDX + v36;
    v40 = DDY + v37;
    v39 = DDZ - v35;
    if (a1 == 1) {
      v31 = LODWORD(Car_variable_2[77 * a2]);
      v30 = LODWORD(Car_variable_1[77 * a2]);
      v29 = LODWORD(Car[77 * a2]);
      VIEWDIST = 120;
      calculatetransform(v29, v30, v31, v38, v40, v39);
      if (Car_variable_3[154 * a2] == -1) {
        worlddirn = Car_variable_7[154 * a2];
        worldelev = v64;
        result = v60;
        worldtilt = v60;
        return result;
      }
    } else {
      calculatetransform(
        LODWORD(Car[77 * a2]),
        LODWORD(Car_variable_1[77 * a2]),
        LODWORD(Car_variable_2[77 * a2]),
        v38,
        v40,
        v39);
      if (Car_variable_3[154 * a2] == -1) {
        worlddirn = Car_variable_7[154 * a2];
        worldelev = v64;
        result = v60;
        worldtilt = v60;
        return result;
      }
    }
    return getworldangles(&worlddirn, &worldelev, &worldtilt);
  } else if (a1 == 3) {
    v55 = Car[77 * a2];
    v49 = Car_variable_1[77 * a2];
    v6 = Car_variable_3[154 * a2];
    v52 = Car_variable_2[77 * a2];
    v65 = v6;
    if (v6 == -1) {
      v62 = Car[77 * a2];
      v63 = Car_variable_2[77 * a2];
      v61 = Car_variable_1[77 * a2];
    } else {
      v7 = (float *)((char *)&localdata + 128 * v6);
      v62 = v7[1] * v49 + *v7 * v55 + v7[2] * v52 - v7[9];
      v61 = v7[3] * v55 + v7[4] * v49 + v7[5] * v52 - v7[10];
      v63 = v49 * v7[7] + v55 * v7[6] + v52 * v7[8] - v7[11];
    }
    if (NumTowers <= 0) {
      v13 = v63 + view_c_variable_4;
      worldx = LODWORD(v62);
      v12 = LODWORD(v61);
      worldy = LODWORD(v61);
    LABEL_39:
      *(float *)&worldz = v13;
    } else {
      if (v65 == -1)
        v65 = Car_variable_51[77 * a2];
      v4 = 0;
      v8 = 0;
      v67 = 9.9999998e17;
      if (NumTowers > 0) {
        v9 = 0;
        do {
          v69 = (float)TowerBase[v9];
          v70 = (double)v65 - v69;
          v66 = (float)TRAK_LEN;
          v34 = fabs(v70 - v66);
          v32 = fabs(v70);
          if (v32 >= v34) {
            v10 = HIDWORD(v34);
            LODWORD(v33) = LODWORD(v34);
          } else {
            v10 = HIDWORD(v32);
            LODWORD(v33) = LODWORD(v32);
          }
          HIDWORD(v33) = v10;
          if (v33 < v67) {
            v4 = v8;
            v68 = v33;
            v67 = v68;
          }
          ++v8;
          v9 += 5;
        } while (v8 < NumTowers);
      }
      worldx = LODWORD(TowerX[v4]);
      worldy = LODWORD(TowerY[v4]);
      v11 = TowerBase_variable_4[5 * v4] - 1;
      worldz = SLODWORD(TowerZ[v4]);
      switch (v11) {
        case 0:
          VIEWDIST = 120;
          break;
        case 1:
          VIEWDIST = 75;
          break;
        case 2:
          VIEWDIST = 500;
          break;
        case 3:
          VIEWDIST = 750;
          break;
        default:
          break;
      }
      v12 = 20 * v4;
      a2 = TowerBase_variable_3[5 * v4] + 5;
      switch (TowerBase_variable_3[5 * v4]) {
        case -5:
          v12 = TowerBase_variable_2[5 * v4] << 7;
          v13 = (double)v12 + v63;
          worldx = LODWORD(v62);
          a2 = LODWORD(v61);
          worldy = LODWORD(v61);
          goto LABEL_39;
        case -4:
          v14 = TowerBase[5 * v4] - 2;
          if (v14 < 0)
            v14 += TRAK_LEN;
          v12 = (int)&localdata + 128 * v14;
          v62 = -*(float *)(v12 + 36);
          v61 = -*(float *)(v12 + 40);
          v63 = -*(float *)(v12 + 44);
          break;
        case -3:
        case 2:
          v15 = *(float *)&worldx - v62;
          v16 = *(float *)&worldy - v61;
          v17 = *(float *)&worldz - v63;
          v18 = 1.0 / sqrt(v15 * v15 + v16 * v16 + v17 * v17);
          *(float *)&worldx = v15 * view_c_variable_7 * v18 + v62;
          *(float *)&worldy = v16 * view_c_variable_7 * v18 + v61;
          *(float *)&worldz = v18 * (v17 * view_c_variable_7) + v63;
          break;
        case -2:
        case 1:
          *(float *)&worldx = (*(float *)&worldx - v62) * view_c_variable_6 + v62;
          *(float *)&worldy = v61 + (*(float *)&worldy - v61) * view_c_variable_6;
          v13 = (*(float *)&worldz - v63) * view_c_variable_6 + v63;
          goto LABEL_39;
        case 0:
          v13 = *(float *)&worldz + view_c_variable_5;
          goto LABEL_39;
        default:
          break;
      }
    }
    TowerGx = worldx;
    TowerGy = worldy;
    TowerGz = worldz;
    v48 = v62 - *(float *)&worldx;
    *(float *)&v50 = v61 - *(float *)&worldy;
    NearTow = v4;
    *(float *)&v43 = v63 - *(float *)&worldz;
    if ((LODWORD(v48) & 0x7FFFFFFF) != 0 || fabs(v61 - *(float *)&worldy)) {
      v12 = getangle(v12, a2, v48, v50);
      vdirection = v12;
    } else {
      vdirection = 0;
    }
    v44 = sqrt(v48 * v48 + *(float *)&v50 * *(float *)&v50);
    if ((LODWORD(v44) & 0x7FFFFFFF) != 0 || (v43 & 0x7FFFFFFF) != 0)
      v19 = getangle(v12, a2, v44, v43);
    else
      v19 = 0;
    velevation = v19;
    vtilt = 0;
    calculatetransform(worldx, worldy, worldz, DDX, DDY, DDZ);
    worlddirn = vdirection;
    worldelev = velevation;
    result = vtilt;
    worldtilt = vtilt;
  } else {
    if (a1 == 6) {
      *(float *)&worldx = -localdata_variable_16;
      *(float *)&worldy = -localdata_variable_17;
      VIEWDIST = 400;
      v51 = Car[77 * a2];
      v53 = Car_variable_1[77 * a2];
      v21 = Car_variable_2[77 * a2];
      v56 = Car_variable_2[v5 / 2];
      v22 = Car_variable_3[v5];
      *(float *)&worldz = view_c_variable_3 - localdata_variable_18;
      if (v22 == -1) {
        v58 = v51;
        v23 = (float *)LODWORD(v53);
        v57 = v21;
        v59 = v53;
      } else {
        v23 = (float *)((char *)&localdata + 128 * v22);
        v58 = v23[1] * v53 + *v23 * v51 + v23[2] * v56 - v23[9];
        v59 = v23[3] * v51 + v23[4] * v53 + v23[5] * v56 - v23[10];
        v57 = v53 * v23[7] + v51 * v23[6] + v56 * v23[8] - v23[11];
      }
    } else {
      v54 = Car[77 * a2];
      v47 = Car_variable_1[77 * a2];
      v21 = Car_variable_2[77 * a2];
      v24 = Car_variable_3[v5];
      if (v24 == -1) {
        v58 = v54;
        v57 = v21;
        v59 = v47;
      } else {
        v25 = (float *)((char *)&localdata + 128 * v24);
        v58 = v25[1] * v47 + *v25 * v54 + v25[2] * v21 - v25[9];
        v59 = v25[3] * v54 + v25[4] * v47 + v25[5] * v21 - v25[10];
        v57 = v47 * v25[7] + v54 * v25[6] + v21 * v25[8] - v25[11];
      }
      worldx = LODWORD(v58);
      v23 = (float *)LODWORD(v59);
      worldy = LODWORD(v59);
      *(float *)&worldz = TopViewHeight + v57;
    }
    v45 = v58 - *(float *)&worldx;
    *(float *)&v46 = v59 - *(float *)&worldy;
    NearTow = -1;
    *(float *)&v42 = v57 - *(float *)&worldz;
    if ((LODWORD(v45) & 0x7FFFFFFF) != 0 || fabs(v59 - *(float *)&worldy)) {
      v23 = (float *)getangle((int)v23, SLODWORD(v21), v45, v46);
      vdirection = (int)v23;
    } else {
      vdirection = 0;
    }
    v41 = sqrt(v45 * v45 + *(float *)&v46 * *(float *)&v46);
    if ((LODWORD(v41) & 0x7FFFFFFF) != 0 || (v42 & 0x7FFFFFFF) != 0)
      velevation = getangle((int)v23, SLODWORD(v21), v41, v42);
    else
      velevation = 0;
    vtilt = 0;
    calculatetransform(worldx, worldy, worldz, DDX, DDY, DDZ);
    worlddirn = vdirection;
    worldelev = velevation;
    result = vtilt;
    worldtilt = vtilt;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00073570
void initcarview(int iCarIdx, int iPlayer)
{
  int iSelectedView; // ecx
  int iChaseViewIdx; // esi
  unsigned int iControlType; // ebx
  float fChasePullDefault; // esi
  int iYaw; // esi
  int iPitch; // edi
  int iRoll; // ecx
  double dChaseDist; // st7
  double dChaseDistMul; // st7
  int iCurrChunk; // eax
  tData *pData; // eax
  double dTransformZ; // st7
  //int iPlayerShift; // eax
  double dLastPosW; // st7
  float fDirX; // [esp+0h] [ebp-3Ch]
  float fDirY; // [esp+4h] [ebp-38h]
  float fDirZ; // [esp+8h] [ebp-34h]
  float fRightX; // [esp+Ch] [ebp-30h]
  float fUpZ; // [esp+10h] [ebp-2Ch]
  float fSinPitch; // [esp+14h] [ebp-28h]
  float fCameraX; // [esp+18h] [ebp-24h]
  float fCameraZ; // [esp+1Ch] [ebp-20h]
  float fCameraY; // [esp+20h] [ebp-1Ch]

  iSelectedView = SelectedView[iPlayer];        // Get the selected view type for the current player
  if (iSelectedView != 1 && iSelectedView != 3 && iCarIdx >= 0)
    return;                                     // Only process if view is cockpit (1) or chase (3) and car index is valid
  if (iCarIdx >= 0) {
    iChaseViewIdx = chaseview[iPlayer];         // Initialize chase camera parameters from viewdata for valid car
    CHASE_DIST[iPlayer] = viewdata[iChaseViewIdx].fChaseDistance;
    CHASE_MIN[iPlayer] = viewdata[iChaseViewIdx].fChaseMinDistance;
    LOOKZ[iPlayer] = viewdata[iChaseViewIdx].fChaseLookAhead;
  } else {
    CHASE_DIST[0] = viewdata[1].fChaseDistance; // Special case: use default chase view for invalid car index
    CHASE_MIN[0] = viewdata[1].fChaseMinDistance;
    iPlayer = 0;
    iCarIdx = -iCarIdx - 1;
    LOOKZ[0] = viewdata[1].fChaseLookAhead;
  }
  iControlType = Car[iCarIdx].iControlType;     // Get car control type (human player, AI, etc)
  if (!iControlType) {
    fChasePullDefault = viewdata[chaseview[iPlayer]].fChasePullDefault;// Human player: use default chase pull factor
  SET_PULL_FACTOR:
    PULLZ[iPlayer] = fChasePullDefault;
    goto CALCULATE_CAMERA_POSITION;
  }
  if (iControlType >= 2 && iControlType <= 3) {                                             // AI cars: choose pull factor based on crash state
    if (Car[iCarIdx].iStunned)
      fChasePullDefault = viewdata[chaseview[iPlayer]].fChasePullCrash;
    else
      fChasePullDefault = viewdata[chaseview[iPlayer]].fChasePullNormal;
    goto SET_PULL_FACTOR;
  }
CALCULATE_CAMERA_POSITION:
  if (Car[iCarIdx].nCurrChunk == -1)          // Get car orientation: use actual angles if not in a chunk
  {
    iYaw = Car[iCarIdx].nYaw;
    iPitch = Car[iCarIdx].nPitch;
    iRoll = Car[iCarIdx].nRoll;
  } else {
    iYaw = 0;                                   // Car is in a chunk: use neutral orientation
    iPitch = 0;
    iRoll = 0;
  }
  fSinPitch = tsin[iPitch];                     // Calculate sine of pitch angle for camera matrix
  if (replaytype == 2 && replaydirection == -1)// Reverse chase distance if in replay mode with reverse direction
    dChaseDist = -CHASE_DIST[iPlayer];
  else
    dChaseDist = CHASE_DIST[iPlayer];
  dChaseDistMul = -(dChaseDist * 2.0);
  fDirX = -tcos[iYaw] * fSinPitch * tcos[iRoll] - tsin[iYaw] * tsin[iRoll];// Calculate camera direction vector X component using rotation matrix
  fDirY = tcos[iYaw] * tcos[iPitch];            // Calculate camera direction vector Y component
  fCameraX = (float)(dChaseDistMul * fDirY + PULLZ[iPlayer] * fDirX + Car[iCarIdx].pos.fX);// Calculate final camera X position with distance and pull factors
  fDirZ = tsin[iYaw] * tcos[iPitch];
  fRightX = -tsin[iYaw] * fSinPitch * tcos[iRoll] + tcos[iYaw] * tsin[iRoll];
  fCameraY = (float)(dChaseDistMul * fDirZ + PULLZ[iPlayer] * fRightX + Car[iCarIdx].pos.fY);// Calculate final camera Y position
  fUpZ = tcos[iPitch] * tcos[iRoll];
  fCameraZ = (float)(dChaseDistMul * fSinPitch + PULLZ[iPlayer] * fUpZ + Car[iCarIdx].pos.fZ);// Calculate final camera Z position
  iCurrChunk = Car[iCarIdx].nCurrChunk;
  if (iCurrChunk == -1)                       // Branch: handle camera position based on chunk state
  {
    chase_x = fCameraX;                         // No chunk: directly set global chase position and lastpos array
    chase_y = fCameraY;
    lastpos[iPlayer][0].fDistance = 0.0;
    chase_z = fCameraZ;
    lastpos[iPlayer][0].pos.fX = fCameraX;
    lastpos[iPlayer][0].pos.fY = fCameraY;
    lastpos[iPlayer][0].pos.fZ = fCameraZ;
  } else {
    pData = &localdata[iCurrChunk];             // In chunk: transform camera position using chunk transformation matrix
    chase_x = pData->pointAy[0].fY * fCameraY + pData->pointAy[0].fX * fCameraX + pData->pointAy[0].fZ * fCameraZ - pData->pointAy[3].fX;
    chase_y = pData->pointAy[1].fX * fCameraX + pData->pointAy[1].fY * fCameraY + pData->pointAy[1].fZ * fCameraZ - pData->pointAy[3].fY;
    chase_z = pData->pointAy[2].fX * fCameraX + pData->pointAy[2].fY * fCameraY + pData->pointAy[2].fZ * fCameraZ - pData->pointAy[3].fZ;
    lastpos[iPlayer][0].pos.fX = chase_x;
    lastpos[iPlayer][0].pos.fY = pData->pointAy[1].fX * fCameraX + pData->pointAy[1].fY * fCameraY + pData->pointAy[1].fZ * fCameraZ - pData->pointAy[3].fY;
    dTransformZ = fCameraY * pData->pointAy[2].fY + fCameraX * pData->pointAy[2].fX + fCameraZ * pData->pointAy[2].fZ - pData->pointAy[3].fZ;
    lastpos[iPlayer][0].fDistance = 0.0;
    lastpos[iPlayer][0].pos.fZ = (float)dTransformZ;
  }

  // Copy current position to backup slots for interpolation
  lastpos[iPlayer][1].pos.fX = lastpos[iPlayer][0].pos.fX;
  lastpos[iPlayer][1].pos.fY = lastpos[iPlayer][0].pos.fY;  
  lastpos[iPlayer][1].pos.fZ = lastpos[iPlayer][0].pos.fZ;
  //iPlayerShift = iPlayer << 10;                 // Copy current position to backup slots for interpolation
  //*(float *)((char *)&lastpos[0][1].pos.fX + iPlayerShift) = lastpos[iPlayer][0].pos.fX;
  //*(float *)((char *)&lastpos[0][1].pos.fY + iPlayerShift) = lastpos[iPlayer][0].pos.fY;
  //*(float *)((char *)&lastpos[0][1].pos.fZ + iPlayerShift) = lastpos[iPlayer][0].pos.fZ;

  dLastPosW = lastpos[iPlayer][0].fDistance;
  nextpoint[iPlayer] = 1;                       // Set nextpoint flag to indicate new camera position is ready

  lastpos[iPlayer][1].fDistance = (float)dLastPosW;
  //*(float *)((char *)&lastpos[0][1].fDistance + iPlayerShift) = dLastPosW;
}

//-------------------------------------------------------------------------------------------------
//00073920
void newchaseview(int iCarIdx, int iChaseCamIdx)
{
  int iCarIndex; // eax
  int nYaw; // ebx
  int nPitch; // ecx
  int nRoll; // edx
  double dBackwardX; // st7
  double dBackwardY; // st6
  double dBackwardZ; // st5
  int iCurrChunk; // eax
  float *pTransformMatrix; // eax
  float fLookTempX; // edx
  double dLookTransformedY; // st7
  float fLookTempY; // edx
  float fPullTempX; // edx
  double dPullTransformedY; // st7
  float fPullTempY; // edx
  int iPrevIndex; // eax
  int iPrevArrayIndex; // eax
  //int iCurrArrayOffset; // edx
  double dDistanceFromPrev; // st7
  int iNextIndex; // edx
  //int iNewArrayOffset; // edx
  int iLoopCounter; // ebx
  int iSearchIndex; // edx
  double dAccumulatedDistance; // st7
  int iPrevSearchIndex; // eax
  //int iCarArrayOffset; // edi
  //int iSearchArrayIndex; // edx
  //int iPrevArrayOffset; // eax
  int iNextPosIndex; // eax
  //int iCarArrayOffset2; // edi
  //int iNextArrayOffset; // eax
  int iCalculatedDirection; // eax
  int iCalculatedElevation; // eax
  float fLookTempX2; // [esp+8h] [ebp-88h]
  float fPullTempX2; // [esp+8h] [ebp-88h]
  float fZ; // [esp+18h] [ebp-78h]
  float fY; // [esp+24h] [ebp-6Ch]
  float fX; // [esp+28h] [ebp-68h]
  float fPrevPosZ; // [esp+2Ch] [ebp-64h]
  float fPrevPosY; // [esp+30h] [ebp-60h]
  float fPrevPosX; // [esp+34h] [ebp-5Ch]
  float fCurrentDistance; // [esp+38h] [ebp-58h]
  float fVerticalDelta; // [esp+3Ch] [ebp-54h]
  float fHorizontalDistance; // [esp+40h] [ebp-50h]
  float fInterpolationFactor; // [esp+44h] [ebp-4Ch]
  float fViewZ; // [esp+48h] [ebp-48h]
  float fViewY; // [esp+4Ch] [ebp-44h]
  float fViewX; // [esp+50h] [ebp-40h]
  float fHorizontalDeltaX; // [esp+54h] [ebp-3Ch]
  float fLookAtX; // [esp+58h] [ebp-38h]
  float fHorizontalDeltaY; // [esp+5Ch] [ebp-34h]
  float fLookAtY; // [esp+60h] [ebp-30h]
  float fLookAtZ; // [esp+64h] [ebp-2Ch]
  float fCameraPosX; // [esp+68h] [ebp-28h]
  float fCameraPosY; // [esp+6Ch] [ebp-24h]
  float fCameraPosZ; // [esp+70h] [ebp-20h]
  float fAccumulatedDist; // [esp+74h] [ebp-1Ch]
  float fTempAccumulatedDist; // [esp+78h] [ebp-18h]

  iCarIndex = iCarIdx;
  nYaw = Car[iCarIndex].nYaw;                   // Get car orientation and position
  nPitch = Car[iCarIndex].nPitch;
  fX = Car[iCarIndex].pos.fX;
  fY = Car[iCarIndex].pos.fY;
  fZ = Car[iCarIndex].pos.fZ;
  nRoll = Car[iCarIndex].nRoll;
  dBackwardX = -tcos[nYaw] * tsin[nPitch] * tcos[nRoll] - tsin[nYaw] * tsin[nRoll];// Calculate backward direction vector from car orientation
                                                // Uses trigonometric transformation to get direction opposite to car's forward vector
  dBackwardY = -tsin[nYaw] * tsin[nPitch] * tcos[nRoll] + tcos[nYaw] * tsin[nRoll];
  dBackwardZ = tcos[nPitch] * tcos[nRoll];
  fCameraPosX = PULLZ[iChaseCamIdx] * (float)dBackwardX + fX;// Calculate camera position (behind car) using PULLZ distance
  fCameraPosY = PULLZ[iChaseCamIdx] * (float)dBackwardY + fY;
  fCameraPosZ = PULLZ[iChaseCamIdx] * (float)dBackwardZ + fZ;
  fLookAtX = (float)dBackwardX * LOOKZ[iChaseCamIdx] + fX;// Calculate look-at position (in front of car) using LOOKZ distance
  fLookAtY = (float)dBackwardY * LOOKZ[iChaseCamIdx] + fY;
  iCurrChunk = Car[iCarIndex].nCurrChunk;
  fLookAtZ = (float)dBackwardZ * LOOKZ[iChaseCamIdx] + fZ;
  if (iCurrChunk != -1)                       // Transform positions to world coordinates if car is on track
  {
    pTransformMatrix = (float *)&localdata[iCurrChunk];// Apply transformation matrix to convert from car-local to world coordinates
    fLookTempX = (float)dBackwardX * LOOKZ[iChaseCamIdx] + fX;
    fLookAtX = pTransformMatrix[1] * fLookAtY + *pTransformMatrix * fLookAtX + pTransformMatrix[2] * fLookAtZ - pTransformMatrix[9];
    fLookTempX2 = fLookTempX;
    dLookTransformedY = pTransformMatrix[3] * fLookTempX + pTransformMatrix[4] * fLookAtY + pTransformMatrix[5] * fLookAtZ - pTransformMatrix[10];
    fLookTempY = (float)dBackwardY * LOOKZ[iChaseCamIdx] + fY;
    fLookAtY = (float)dLookTransformedY;
    fLookAtZ = pTransformMatrix[6] * fLookTempX2 + pTransformMatrix[7] * fLookTempY + pTransformMatrix[8] * fLookAtZ - pTransformMatrix[11];
    fPullTempX = fCameraPosX;
    fCameraPosX = pTransformMatrix[1] * fCameraPosY + *pTransformMatrix * fCameraPosX + pTransformMatrix[2] * fCameraPosZ - pTransformMatrix[9];
    fPullTempX2 = fPullTempX;
    dPullTransformedY = pTransformMatrix[3] * fPullTempX + pTransformMatrix[4] * fCameraPosY + pTransformMatrix[5] * fCameraPosZ - pTransformMatrix[10];
    fPullTempY = PULLZ[iChaseCamIdx] * (float)dBackwardY + fY;
    fCameraPosY = (float)dPullTransformedY;
    fCameraPosZ = pTransformMatrix[6] * fPullTempX2 + pTransformMatrix[7] * fPullTempY + pTransformMatrix[8] * fCameraPosZ - pTransformMatrix[11];
  }
  iPrevIndex = nextpoint[iChaseCamIdx] - 1;     // Get previous position index in circular buffer
  if (iPrevIndex < 0)
    iPrevIndex = 63;
  iPrevArrayIndex = iPrevIndex;

  // Get current position data from position history buffer
  int iPositionIndex = nextpoint[iChaseCamIdx];
  fPrevPosX = lastpos[iChaseCamIdx][iPositionIndex].pos.fX;
  fPrevPosY = lastpos[iChaseCamIdx][iPositionIndex].pos.fY;
  fPrevPosZ = lastpos[iChaseCamIdx][iPositionIndex].pos.fZ;
  //iCurrArrayOffset = 16 * nextpoint[iChaseCamIdx] + (iChaseCamIdx << 10);// Get current position data from position history buffer
  //fPrevPosX = *(float *)((char *)&lastpos[0][0].pos.fX + iCurrArrayOffset);
  //fPrevPosY = *(float *)((char *)&lastpos[0][0].pos.fY + iCurrArrayOffset);
  //fPrevPosZ = *(float *)((char *)&lastpos[0][0].pos.fZ + iCurrArrayOffset);

  dDistanceFromPrev = sqrt(
                        (fCameraPosX - lastpos[iChaseCamIdx][iPrevArrayIndex].pos.fX) * (fCameraPosX - lastpos[iChaseCamIdx][iPrevArrayIndex].pos.fX)
                      + (fCameraPosY - lastpos[iChaseCamIdx][iPrevArrayIndex].pos.fY) * (fCameraPosY - lastpos[iChaseCamIdx][iPrevArrayIndex].pos.fY)
                      + (fCameraPosZ - lastpos[iChaseCamIdx][iPrevArrayIndex].pos.fZ) * (fCameraPosZ - lastpos[iChaseCamIdx][iPrevArrayIndex].pos.fZ));// Calculate distance from previous recorded position
  if (dDistanceFromPrev >= 3200.0)            // Check if car has moved far enough to record new position (3200 units)
  {
    iNextIndex = nextpoint[iChaseCamIdx] + 1;   // Car moved enough - advance to next position in circular buffer
    nextpoint[iChaseCamIdx] = iNextIndex;
    if (iNextIndex == 64)
      nextpoint[iChaseCamIdx] = 0;

    // Store new position and distance in history buffer
    int iNewPositionIndex = nextpoint[iChaseCamIdx];
    lastpos[iChaseCamIdx][iNewPositionIndex].pos.fX = fCameraPosX;
    lastpos[iChaseCamIdx][iNewPositionIndex].pos.fY = fCameraPosY;
    lastpos[iChaseCamIdx][iNewPositionIndex].pos.fZ = fCameraPosZ;
    lastpos[iChaseCamIdx][iNewPositionIndex].fDistance = (float)sqrt(
        (fPrevPosX - fCameraPosX) * (fPrevPosX - fCameraPosX)
      + (fPrevPosY - fCameraPosY) * (fPrevPosY - fCameraPosY)
      + (fPrevPosZ - fCameraPosZ) * (fPrevPosZ - fCameraPosZ));
    //iNewArrayOffset = 16 * nextpoint[iChaseCamIdx] + (iChaseCamIdx << 10);// Store new position and distance in history buffer
    //*(float *)((char *)&lastpos[0][0].pos.fX + iNewArrayOffset) = fCameraPosX;
    //*(float *)((char *)&lastpos[0][0].pos.fY + iNewArrayOffset) = fCameraPosY;
    //*(float *)((char *)&lastpos[0][0].pos.fZ + iNewArrayOffset) = fCameraPosZ;
    //*(float *)((char *)&lastpos[0][0].fDistance + iNewArrayOffset) = sqrt(
    //                                                                   (fPrevPosX - fCameraPosX) * (fPrevPosX - fCameraPosX)
    //                                                                 + (fPrevPosY - fCameraPosY) * (fPrevPosY - fCameraPosY)
    //                                                                 + (fPrevPosZ - fCameraPosZ) * (fPrevPosZ - fCameraPosZ));
  } else {
    // Car hasn't moved enough - update current position in place
    lastpos[iChaseCamIdx][iPositionIndex].pos.fX = fCameraPosX;
    lastpos[iChaseCamIdx][iPositionIndex].pos.fY = fCameraPosY;
    lastpos[iChaseCamIdx][iPositionIndex].pos.fZ = fCameraPosZ;
    fCurrentDistance = (float)dDistanceFromPrev;
    lastpos[iChaseCamIdx][iPositionIndex].fDistance = fCurrentDistance;
    //*(float *)((char *)&lastpos[0][0].pos.fX + iCurrArrayOffset) = fCameraPosX;// Car hasn't moved enough - update current position in place
    //*(float *)((char *)&lastpos[0][0].pos.fY + iCurrArrayOffset) = fCameraPosY;
    //*(float *)((char *)&lastpos[0][0].pos.fZ + iCurrArrayOffset) = fCameraPosZ;
    //fCurrentDistance = dDistanceFromPrev;
    //*(float *)((char *)&lastpos[0][0].fDistance + iCurrArrayOffset) = fCurrentDistance;
  }
  iLoopCounter = 62;                            // Search for chase camera position at specified distance behind car
                                                // Loop through position history to find point at CHASE_DIST distance
  fAccumulatedDist = 0.0;
  iSearchIndex = nextpoint[iChaseCamIdx];
  while (1) {
    dAccumulatedDistance = fAccumulatedDist + lastpos[iChaseCamIdx][iSearchIndex].fDistance;// Accumulate distance from position history
    if (dAccumulatedDistance >= CHASE_DIST[iChaseCamIdx] || iLoopCounter < 0)
      break;                                    // Check if reached target chase distance or exhausted history
    fTempAccumulatedDist = (float)dAccumulatedDistance;
    fAccumulatedDist = fTempAccumulatedDist;
    iSearchIndex = iSearchIndex - 1 + (iSearchIndex - 1 < 0 ? 0x40 : 0);
    --iLoopCounter;
  }
  if (iLoopCounter <= 0) {
    iNextPosIndex = nextpoint[iChaseCamIdx] + 1;// Not enough history - use position ahead of current
    if (nextpoint[iChaseCamIdx] == 63)
      iNextPosIndex = 0;

    fViewX = lastpos[iChaseCamIdx][iNextPosIndex].pos.fX;
    fViewY = lastpos[iChaseCamIdx][iNextPosIndex].pos.fY;
    fViewZ = lastpos[iChaseCamIdx][iNextPosIndex].pos.fZ;
    //iCarArrayOffset2 = iChaseCamIdx << 10;
    //iNextArrayOffset = 16 * iNextPosIndex;
    //fViewX = *(float *)((char *)&lastpos[0][0].pos.fX + iCarArrayOffset2 + iNextArrayOffset);
    //fViewY = *(float *)((char *)&lastpos[0][0].pos.fY + iCarArrayOffset2 + iNextArrayOffset);
    //fViewZ = *(float *)((char *)&lastpos[0][0].pos.fZ + iCarArrayOffset2 + iNextArrayOffset);
  } else {
    iPrevSearchIndex = iSearchIndex - 1;        // Interpolate camera position between two history points
                                                // Calculate exact position at target distance using linear interpolation
    fInterpolationFactor = (lastpos[iChaseCamIdx][iSearchIndex].fDistance + fAccumulatedDist - CHASE_DIST[iChaseCamIdx]) / lastpos[iChaseCamIdx][iSearchIndex].fDistance;


    // Handle circular buffer wraparound for previous index
    int iPrevIndex = (iPrevSearchIndex < 0) ? (iPrevSearchIndex + 64) : iPrevSearchIndex;
    fViewX = (lastpos[iChaseCamIdx][iSearchIndex].pos.fX - lastpos[iChaseCamIdx][iPrevIndex].pos.fX)
           * fInterpolationFactor
           + lastpos[iChaseCamIdx][iPrevIndex].pos.fX;
    fViewY = (lastpos[iChaseCamIdx][iSearchIndex].pos.fY - lastpos[iChaseCamIdx][iPrevIndex].pos.fY)
           * fInterpolationFactor
           + lastpos[iChaseCamIdx][iPrevIndex].pos.fY;
    fViewZ = fInterpolationFactor
           * (lastpos[iChaseCamIdx][iSearchIndex].pos.fZ - lastpos[iChaseCamIdx][iPrevIndex].pos.fZ)
           + lastpos[iChaseCamIdx][iPrevIndex].pos.fZ;
    //iCarArrayOffset = iChaseCamIdx << 10;
    //iSearchArrayIndex = iSearchIndex;
    //iPrevArrayOffset = 16 * (iPrevSearchIndex + (iPrevSearchIndex < 0 ? 64 : 0));
    //fViewX = (*(float *)((char *)&lastpos[0][iSearchArrayIndex].pos.fX + iCarArrayOffset) - *(float *)((char *)&lastpos[0][0].pos.fX + iCarArrayOffset + iPrevArrayOffset))
    //  * fInterpolationFactor
    //  + *(float *)((char *)&lastpos[0][0].pos.fX + iCarArrayOffset + iPrevArrayOffset);
    //fViewY = (*(float *)((char *)&lastpos[0][iSearchArrayIndex].pos.fY + iCarArrayOffset) - *(float *)((char *)&lastpos[0][0].pos.fY + iCarArrayOffset + iPrevArrayOffset))
    //  * fInterpolationFactor
    //  + *(float *)((char *)&lastpos[0][0].pos.fY + iCarArrayOffset + iPrevArrayOffset);
    //fViewZ = fInterpolationFactor
    //  * (*(float *)((char *)&lastpos[0][iSearchArrayIndex].pos.fZ + iCarArrayOffset) - *(float *)((char *)&lastpos[0][0].pos.fZ + iCarArrayOffset + iPrevArrayOffset))
    //  + *(float *)((char *)&lastpos[0][0].pos.fZ + iCarArrayOffset + iPrevArrayOffset);
  }
  fHorizontalDeltaX = fLookAtX - fViewX;        // Calculate direction from camera to look-at point
  fHorizontalDeltaY = fLookAtY - fViewY;
  //if ((LODWORD(fHorizontalDeltaX) & 0x7FFFFFFF) != 0 || fabs(fLookAtY - fViewY))// Calculate horizontal direction angle (yaw)
  if (fabs(fHorizontalDeltaX) > FLT_EPSILON || fabs(fLookAtY - fViewY))// Calculate horizontal direction angle (yaw)
    iCalculatedDirection = getangle(fHorizontalDeltaX, fHorizontalDeltaY);
  else
    iCalculatedDirection = lastcamdirection;    // Use last camera direction if no movement detected
  vdirection = iCalculatedDirection;
  fHorizontalDistance = (float)sqrt(fHorizontalDeltaX * fHorizontalDeltaX + fHorizontalDeltaY * fHorizontalDeltaY);// Calculate elevation angle (pitch) from horizontal distance and height difference
  //if ((LODWORD(fHorizontalDistance) & 0x7FFFFFFF) != 0 || fabs(fLookAtZ - fViewZ)) {
  if (fabs(fHorizontalDistance) > FLT_EPSILON || fabs(fLookAtZ - fViewZ)) {
    fVerticalDelta = fLookAtZ - fViewZ;
    iCalculatedElevation = getangle(fHorizontalDistance, fVerticalDelta);
  } else {
    iCalculatedElevation = lastcamelevation;    // Use last camera elevation if no height difference
  }
  velevation = iCalculatedElevation;
  vtilt = 0;
  calculatetransform(-1, vdirection, iCalculatedElevation, 0, fViewX, fViewY, fViewZ, DDX, DDY, DDZ);// Set up camera transformation matrix with calculated position and orientation
  lastcamdirection = vdirection;                // Save camera angles for next frame to avoid sudden changes
  lastcamelevation = velevation;
  worlddirn = vdirection;                       // Set global world orientation values
  worldelev = velevation;
  worldtilt = vtilt;
}

//-------------------------------------------------------------------------------------------------
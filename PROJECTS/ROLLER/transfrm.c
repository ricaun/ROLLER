#include "transfrm.h"
#include "3d.h"
#include "control.h"
#include "loadtrak.h"
#include "userfns.h"
#include <math.h>
//-------------------------------------------------------------------------------------------------

float vk1;  //00189950
int xp;     //00189954
float vk2;  //00189958
float vk3;  //0018995C
float vk4;  //00189960
float vk5;  //00189964
float vk6;  //00189968
float vk7;  //0018996C
float vk8;  //00189970
float vk9;  //00189974
int yp;     //00189978

//-------------------------------------------------------------------------------------------------

void calculatetransform(
        int iTrackChunkIdx,
        int iDirection,
        int iElevation,
        int iTilt,
        float fViewX,
        float fViewY,
        float fViewZ,
        float fPosX,
        float fPosY,
        float fPosZ)
{
  double v10; // st7
  double v11; // st7
  double dVk9; // st7
  tData *pData; // eax
  double v14; // st6
  double dZ; // st5
  float v16; // [esp+0h] [ebp-2Ch]
  float v17; // [esp+4h] [ebp-28h]
  float v18; // [esp+8h] [ebp-24h]
  float v19; // [esp+Ch] [ebp-20h]
  float v20; // [esp+10h] [ebp-1Ch]
  float v21; // [esp+14h] [ebp-18h]
  float v22; // [esp+1Ch] [ebp-10h]
  float v23; // [esp+20h] [ebp-Ch]
  float v24; // [esp+24h] [ebp-8h]

  v10 = tcos[iDirection] * tsin[iElevation];
  vk1 = tsin[iDirection] * tcos[iTilt] - (float)v10 * tsin[iTilt];
  vk2 = -tsin[iDirection] * tsin[iTilt] - (float)v10 * tcos[iTilt];
  vk3 = tcos[iDirection] * tcos[iElevation];
  v11 = tsin[iDirection] * tsin[iElevation];
  vk4 = -tcos[iDirection] * tcos[iTilt] - (float)v11 * tsin[iTilt];
  vk5 = tcos[iDirection] * tsin[iTilt] - (float)v11 * tcos[iTilt];
  vk6 = tsin[iDirection] * tcos[iElevation];
  vk7 = tcos[iElevation] * tsin[iTilt];
  vk8 = tcos[iElevation] * tcos[iTilt];
  dVk9 = (double)tsin[iElevation];
  viewx = fViewX;
  viewy = fViewY;
  viewz = fViewZ;
  vk9 = (float)dVk9;
  if (iTrackChunkIdx != -1) {
    pData = &localdata[iTrackChunkIdx];
    viewx = pData->pointAy[0].fX * fViewX
      - pData->pointAy[3].fX
      + pData->pointAy[0].fY * fViewY
      + pData->pointAy[0].fZ * fViewZ;
    viewy = pData->pointAy[1].fX * fViewX
      - pData->pointAy[3].fY
      + pData->pointAy[1].fY * fViewY
      + pData->pointAy[1].fZ * fViewZ;
    viewz = fViewY * pData->pointAy[2].fY
      + fViewX * pData->pointAy[2].fX
      - pData->pointAy[3].fZ
      + fViewZ * pData->pointAy[2].fZ;
    v21 = pData->pointAy[0].fY * vk4 + pData->pointAy[0].fX * vk1 + pData->pointAy[0].fZ * vk7;
    v24 = pData->pointAy[0].fY * vk5 + pData->pointAy[0].fX * vk2 + pData->pointAy[0].fZ * vk8;
    v16 = pData->pointAy[0].fY * vk6 + pData->pointAy[0].fX * vk3 + pData->pointAy[0].fZ * vk9;
    v20 = pData->pointAy[1].fX * vk1 + pData->pointAy[1].fY * vk4 + pData->pointAy[1].fZ * vk7;
    v18 = pData->pointAy[1].fX * vk2 + pData->pointAy[1].fY * vk5 + pData->pointAy[1].fZ * vk8;
    v19 = pData->pointAy[1].fX * vk3 + pData->pointAy[1].fY * vk6 + pData->pointAy[1].fZ * vk9;
    v17 = pData->pointAy[2].fX * vk1 + pData->pointAy[2].fY * vk4 + pData->pointAy[2].fZ * vk7;
    v22 = vk8 * pData->pointAy[2].fZ + pData->pointAy[2].fX * vk2 + pData->pointAy[2].fY * vk5;
    v14 = pData->pointAy[2].fX * vk3 + pData->pointAy[2].fY * vk6;
    dZ = pData->pointAy[2].fZ;
    vk1 = v21;
    vk2 = v24;
    vk3 = v16;
    vk4 = v20;
    vk5 = v18;
    vk6 = v19;
    vk7 = v17;
    v23 = vk9 * (float)dZ + (float)v14;
    vk8 = v22;
    vk9 = v23;
  }
  viewx = vk1 * fPosX + vk2 * fPosY + vk3 * fPosZ + viewx;
  viewy = vk4 * fPosX + vk5 * fPosY + vk6 * fPosZ + viewy;
  viewz = fPosX * vk7 + fPosY * vk8 + fPosZ * vk9 + viewz;
}

//-------------------------------------------------------------------------------------------------

void initlocaltrack()
{
/*
  int i; // edx

  for (i = 0; i < TRAK_LEN; ++i)
    initlocalsection(i);
  dopitchchanges(0, 2);
  return dopitchchanges(3, 4);*/
}

//-------------------------------------------------------------------------------------------------

void initlocalsection(int iChunkIdx)
{
  int iNextChunk; // ecx
  int iNextNextChunk; // esi
  int iArrayIndex; // eax
  tData *pData; // edx
  uint32 uiOffset; // eax
  double fTemp; // st7
  int iLoop1; // ebx
  double fAngleY; // st7
  double dSinY; // rt0
  double dTempRot; // st5
  int iLoop2; // ebx
  double fAngleZ; // st7
  double dSinZ; // st6
  double dTempRotZ; // st5
  int iLoop3; // ebx
  double dAngleX; // st6
  double dCosX; // st7
  double dTempRotX; // st5
  //int16 nFpStatus1; // fps
  double fBankAngle; // st7
  //int16 nFpStatus2; // fps
  double fBankDelta; // st7
  double dCosAngleY; // rt0
  double dCosAngleZ; // rt1
  uint32 uiOffset2; // eax
  double dMatrix_2_2; // st7
  double dMatrix_0_2; // st6
  double dMatrix_1_2; // st5
  double dMatrix_2_1; // st4
  double dMatrix_0_1; // st3
  double dTransformedZ; // st2
  int iLoop4; // ebx
  double dNextAngleY; // st7
  double dSinNextY; // rt0
  double dTemPRotNextY; // st5
  int iLoop5; // ebx
  double dNextAngleZ; // st7
  double dSinNextZ; // st6
  double dTempRotNextZ; // st5
  double dAngleYFixed; // st7
  double dAngleZFixed; // st7
  double dAngleXFixed; // st7
  int iYawTemp; // esi
  int iPitchTemp; // ebp
  int iRollTemp; // ebx
  double matrixWork[30]; // [esp+0h] [ebp-2A8h]
  double pointArray[27]; // [esp+F0h] [ebp-1B8h]
  double dRotatedZ; // [esp+1C8h] [ebp-E0h]
  double dRotatedY; // [esp+1D0h] [ebp-D8h]
  double dRotatedX; // [esp+1D8h] [ebp-D0h]
  double dAngleZSaved; // [esp+1E0h] [ebp-C8h]
  double dCosXSaved; // [esp+1E8h] [ebp-C0h]
  double dSinXSaved; // [esp+1F0h] [ebp-B8h]
  double dCosY_1; // [esp+1F8h] [ebp-B0h]
  double dCosYSinZ; // [esp+208h] [ebp-A0h]
  double dSinZMat; // [esp+210h] [ebp-98h]
  double dAngleXBank; // [esp+218h] [ebp-90h]
  double dNextAngleZSaved; // [esp+220h] [ebp-88h]
  double dMatrix00; // [esp+228h] [ebp-80h]
  double dMatrix01; // [esp+230h] [ebp-78h]
  double dSinZSaved; // [esp+238h] [ebp-70h]
  double dMatrix10; // [esp+240h] [ebp-68h]
  double dMatrix12; // [esp+248h] [ebp-60h]
  double dMatrix02; // [esp+250h] [ebp-58h]
  double dMatrix21; // [esp+258h] [ebp-50h]
  double dMatrix10_2; // [esp+260h] [ebp-48h]
  double dCosY; // [esp+268h] [ebp-40h]
  double dNextAngleYSaved; // [esp+270h] [ebp-38h]
  double dMatrix22; // [esp+278h] [ebp-30h]
  double dWorkAngle; // [esp+280h] [ebp-28h]
  double dAngleYSaved; // [esp+288h] [ebp-20h]

  iNextChunk = iChunkIdx + 1;                   // Get next chunk index with wraparound
  if (iChunkIdx + 1 == TRAK_LEN)
    iNextChunk ^= TRAK_LEN;
  iNextNextChunk = iNextChunk + 1;              // Get chunk index two ahead with wraparound
  if (iNextChunk + 1 == TRAK_LEN)
    iNextNextChunk ^= TRAK_LEN;
  iArrayIndex = iChunkIdx;

  // Extract track points for current chunk (left and right edges)
  pointArray[0] = TrakPt[iArrayIndex].pointAy[2].fX;// Point 0: Current left edge
  pointArray[1] = TrakPt[iArrayIndex].pointAy[2].fY;
  pointArray[2] = TrakPt[iArrayIndex].pointAy[2].fZ;
  pointArray[3] = TrakPt[iArrayIndex].pointAy[3].fX;// Point 1: Current right edge
  pointArray[4] = TrakPt[iArrayIndex].pointAy[3].fY;
  pointArray[5] = TrakPt[iArrayIndex].pointAy[3].fZ;
  pointArray[6] = TrakPt[iNextChunk].pointAy[2].fX;// Point 2: Next left edge
  pointArray[7] = TrakPt[iNextChunk].pointAy[2].fY;
  pointArray[8] = TrakPt[iNextChunk].pointAy[2].fZ;
  pointArray[9] = TrakPt[iNextChunk].pointAy[3].fX;// Point 3: Next right edge
  pointArray[10] = TrakPt[iNextChunk].pointAy[3].fY;
  pointArray[11] = TrakPt[iNextChunk].pointAy[3].fZ;
  // Calculate midpoints between left and right track edges
  pointArray[12] = (pointArray[0] + pointArray[3]) * 0.5;
  pointArray[13] = (pointArray[1] + pointArray[4]) * 0.5;
  pointArray[14] = (pointArray[2] + pointArray[5]) * 0.5;
  pointArray[15] = (pointArray[6] + pointArray[9]) * 0.5;
  pointArray[16] = (pointArray[7] + pointArray[10]) * 0.5;
  pointArray[17] = (pointArray[8] + pointArray[11]) * 0.5;
  pointArray[18] = (pointArray[0] + pointArray[6]) * 0.5;
  pointArray[19] = (pointArray[1] + pointArray[7]) * 0.5;
  pointArray[20] = (pointArray[2] + pointArray[8]) * 0.5;
  pointArray[21] = (pointArray[3] + pointArray[9]) * 0.5;
  pointArray[22] = (pointArray[4] + pointArray[10]) * 0.5;
  pointArray[23] = (pointArray[5] + pointArray[11]) * 0.5;
  // Calculate track center position
  pointArray[24] = (pointArray[12] + pointArray[15]) * 0.5;
  pointArray[25] = (pointArray[13] + pointArray[16]) * 0.5;
  pointArray[26] = (pointArray[14] + pointArray[17]) * 0.5;
  pData = &localdata[iChunkIdx];
  // Store negated center position as origin for local coordinate system
  pData->pointAy[3].fX = (float)-pointArray[24];
  pData->pointAy[3].fY = (float)-pointArray[25];
  uiOffset = 0;
  pData->pointAy[3].fZ = (float) - pointArray[26];
  do {
    // Transform all points to local coordinate system (centered at track section)
    pointArray[uiOffset] = pData->pointAy[3].fX + pointArray[uiOffset];
    pointArray[uiOffset + 1] = pData->pointAy[3].fY + pointArray[uiOffset + 1];
    pointArray[uiOffset + 2] = pData->pointAy[3].fZ + pointArray[uiOffset + 2];
    pointArray[uiOffset + 3] = pData->pointAy[3].fX + pointArray[uiOffset + 3];
    pointArray[uiOffset + 4] = pData->pointAy[3].fY + pointArray[uiOffset + 4];
    pointArray[uiOffset + 5] = pData->pointAy[3].fZ + pointArray[uiOffset + 5];
    pointArray[uiOffset + 6] = pData->pointAy[3].fX + pointArray[uiOffset + 6];
    pointArray[uiOffset + 7] = pData->pointAy[3].fY + pointArray[uiOffset + 7];
    fTemp = pData->pointAy[3].fZ + pointArray[uiOffset + 8];

    //moving this above offset increment
    pointArray[uiOffset + 8] = fTemp;
    
    uiOffset += 9u;
    //matrixWork[uiOffset + 29] = fTemp;          // pointArray[uiOffset + 8] = if moved above uiOffset increment
  } while (uiOffset != 27);
  iLoop1 = 0;
  fAngleY = getdirection(pointArray[15] - pointArray[12], pointArray[16] - pointArray[13]);// Calculate Y rotation angle from track direction
  dAngleYSaved = fAngleY;
  do {
    dSinY = sin(-fAngleY);                      // Apply Y-axis rotation to align track with coordinate axes
    dCosY = cos(-fAngleY);
    dTempRot = pointArray[iLoop1 + 1] * dSinY;
    dCosY_1 = dCosY;
    dRotatedX = pointArray[iLoop1] * dCosY - dTempRot;
    dRotatedY = dSinY * pointArray[iLoop1] + pointArray[iLoop1 + 1] * dCosY;

    //moving this above loop increment
    pointArray[iLoop1] = dRotatedX;
    pointArray[iLoop1 + 1] = dRotatedY;

    iLoop1 += 3;
    //LODWORD(matrixWork[iLoop1 + 27]) = LODWORD(dRotatedX);// pointArray[iLoop] = if moved above iLoop increment
    //HIDWORD(matrixWork[iLoop1 + 27]) = HIDWORD(dRotatedX);
    //LODWORD(matrixWork[iLoop1 + 28]) = LODWORD(dRotatedY);
    //HIDWORD(matrixWork[iLoop1 + 28]) = HIDWORD(dRotatedY);
  } while (iLoop1 != 27);
  iLoop2 = 0;
  fAngleZ = getdirection(pointArray[15] - pointArray[12], pointArray[17] - pointArray[14]);// Calculate Z rotation angle (track slope/elevation)
  dAngleZSaved = fAngleZ;
  do {
    dSinZ = sin(fAngleZ);
    dCosY = cos(fAngleZ);
    dTempRotZ = pointArray[iLoop2 + 2] * dSinZ;
    dCosY_1 = dCosY;
    dRotatedX = dTempRotZ + pointArray[iLoop2] * dCosY;
    dRotatedZ = pointArray[iLoop2 + 2] * dCosY + -dSinZ * pointArray[iLoop2];

    //moving this above loop increment
    pointArray[iLoop2] = dRotatedX;
    pointArray[iLoop2 + 2] = dRotatedZ;

    iLoop2 += 3;
    //LODWORD(matrixWork[iLoop2 + 27]) = LODWORD(dRotatedX);// pointArray[iLoop2] = if moved above iLoop2 increment
    //HIDWORD(matrixWork[iLoop2 + 27]) = HIDWORD(dRotatedX);
    //LODWORD(matrixWork[iLoop2 + 29]) = LODWORD(dRotatedZ);
    //HIDWORD(matrixWork[iLoop2 + 29]) = HIDWORD(dRotatedZ);
  } while (iLoop2 != 27);
  iLoop3 = 0;
  dAngleXBank = getdirection(pointArray[19] - pointArray[22], pointArray[23] - pointArray[20]);// Calculate X rotation angle (track banking)
  dAngleX = dAngleXBank;
  do {
    dCosX = cos(dAngleX);
    dCosY = sin(dAngleX);
    dTempRotX = pointArray[iLoop3 + 1] * dCosX;
    dSinXSaved = dCosY;
    dRotatedY = dTempRotX - pointArray[iLoop3 + 2] * dCosY;
    dRotatedZ = pointArray[iLoop3 + 1] * dCosY + pointArray[iLoop3 + 2] * dCosX;

    //moving this above loop increment
    pointArray[iLoop3 + 1] = dRotatedY;
    pointArray[iLoop3 + 2] = dRotatedZ;

    iLoop3 += 3;
    //LODWORD(matrixWork[iLoop3 + 28]) = LODWORD(dRotatedY);// pointArray[iLoop3] = if moved above iLoop3 increment
    //HIDWORD(matrixWork[iLoop3 + 28]) = HIDWORD(dRotatedY);
    //LODWORD(matrixWork[iLoop3 + 29]) = LODWORD(dRotatedZ);
    //HIDWORD(matrixWork[iLoop3 + 29]) = HIDWORD(dRotatedZ);
  } while (iLoop3 != 27);
  dCosXSaved = dCosX;

  // Calculate banking angle difference for physics
  fBankAngle = atan2(pointArray[7] - pointArray[10], pointArray[11] - pointArray[8]);
  //fBankAngle = IF_DATAN2(nFpStatus1, pointArray[7] - pointArray[10], pointArray[11] - pointArray[8]);
  fBankDelta = (fBankAngle - atan2(pointArray[5] - pointArray[2], fBankAngle)) * 16384.0 / 6.28318530718 + 0.5;
  //fBankDelta = (fBankAngle - IF_DATAN2(nFpStatus2, pointArray[5] - pointArray[2], fBankAngle)) * 16384.0 / 6.28318530718 + 0.5;
  floor(fBankDelta);
  //_CHP();
  pData->iBankDelta = (int)-fBankDelta;

  // Store track section dimensions
  pData->fTrackHalfLength = (float)((pointArray[15] - pointArray[12]) * 0.5);
  pData->fTrackHalfWidth = (float)((pointArray[1] - pointArray[4]) * 0.5);

  // Build rotation matrix from three angles
  dCosAngleY = cos(dAngleYSaved);
  dCosY = sin(dAngleYSaved);
  dCosAngleZ = cos(dAngleZSaved);
  dMatrix00 = dCosAngleY * dCosAngleZ;
  dSinZMat = sin(dAngleZSaved);
  dCosYSinZ = dCosAngleY * dSinZMat;
  dWorkAngle = dCosY;
  dMatrix01 = dCosYSinZ * dSinXSaved + -dCosY * dCosXSaved;
  dMatrix02 = -dCosY * dSinXSaved - dCosYSinZ * dCosXSaved;
  dMatrix10_2 = dCosY * dCosAngleZ;
  dMatrix10 = dCosY * dSinZMat * dSinXSaved + dCosAngleY * dCosXSaved;
  dMatrix12 = dCosAngleY * dSinXSaved - dCosY * dSinZMat * dCosXSaved;
  dMatrix21 = dSinXSaved * -dCosAngleZ;
  dMatrix22 = dCosXSaved * dCosAngleZ;

  // Store rotation matrix rows in localdata structure
  pData->pointAy[0].fX = (float)dMatrix00;
  pData->pointAy[0].fY = (float)dMatrix01;
  pData->pointAy[0].fZ = (float)dMatrix02;
  dSinZSaved = dSinZMat;
  pData->pointAy[1].fX = (float)dMatrix10_2;
  pData->pointAy[1].fY = (float)dMatrix10;
  pData->pointAy[1].fZ = (float)dMatrix12;
  pData->pointAy[2].fX = (float)dSinZMat;
  pData->pointAy[2].fY = (float)dMatrix21;
  pData->pointAy[2].fZ = (float)dMatrix22;

  // Process next track section for smooth transitions
  pointArray[0] = TrakPt[iNextChunk].pointAy[2].fX;
  pointArray[1] = TrakPt[iNextChunk].pointAy[2].fY;
  pointArray[2] = TrakPt[iNextChunk].pointAy[2].fZ;
  pointArray[3] = TrakPt[iNextChunk].pointAy[3].fX;
  pointArray[4] = TrakPt[iNextChunk].pointAy[3].fY;
  pointArray[5] = TrakPt[iNextChunk].pointAy[3].fZ;
  pointArray[6] = TrakPt[iNextNextChunk].pointAy[2].fX;
  pointArray[7] = TrakPt[iNextNextChunk].pointAy[2].fY;
  pointArray[8] = TrakPt[iNextNextChunk].pointAy[2].fZ;
  pointArray[9] = TrakPt[iNextNextChunk].pointAy[3].fX;
  pointArray[10] = TrakPt[iNextNextChunk].pointAy[3].fY;
  pointArray[11] = TrakPt[iNextNextChunk].pointAy[3].fZ;
  pointArray[12] = (pointArray[0] + pointArray[3]) * 0.5;
  pointArray[13] = (pointArray[1] + pointArray[4]) * 0.5;
  pointArray[14] = (pointArray[2] + pointArray[5]) * 0.5;
  pointArray[15] = (pointArray[6] + pointArray[9]) * 0.5;
  pointArray[16] = (pointArray[7] + pointArray[10]) * 0.5;
  pointArray[17] = (pointArray[8] + pointArray[11]) * 0.5;
  pointArray[18] = (pointArray[0] + pointArray[6]) * 0.5;
  pointArray[19] = (pointArray[1] + pointArray[7]) * 0.5;
  pointArray[20] = (pointArray[2] + pointArray[8]) * 0.5;
  pointArray[21] = (pointArray[3] + pointArray[9]) * 0.5;
  pointArray[22] = (pointArray[4] + pointArray[10]) * 0.5;
  pointArray[23] = (pointArray[5] + pointArray[11]) * 0.5;
  pointArray[24] = (pointArray[12] + pointArray[15]) * 0.5;
  pointArray[25] = (pointArray[13] + pointArray[16]) * 0.5;
  uiOffset2 = 0;
  pointArray[26] = (pointArray[14] + pointArray[17]) * 0.5;
  dMatrix_2_2 = dMatrix22;
  dMatrix_0_2 = dMatrix02;
  dMatrix_1_2 = dMatrix12;
  dMatrix_2_1 = dMatrix21;
  dMatrix_0_1 = dMatrix01;
  do {
    matrixWork[uiOffset2 + 3] = (pData->pointAy[3].fY + pointArray[uiOffset2 + 1]) * dMatrix10_2
      + (pData->pointAy[3].fX + pointArray[uiOffset2]) * dMatrix00
      + (pData->pointAy[3].fZ + pointArray[uiOffset2 + 2]) * dSinZSaved;
    matrixWork[uiOffset2 + 4] = (pData->pointAy[3].fY + pointArray[uiOffset2 + 1]) * dMatrix10
      + (pData->pointAy[3].fX + pointArray[uiOffset2]) * dMatrix_0_1
      + (pData->pointAy[3].fZ + pointArray[uiOffset2 + 2]) * dMatrix_2_1;
    dTransformedZ = (pData->pointAy[3].fY + pointArray[uiOffset2 + 1]) * dMatrix_1_2
      + (pData->pointAy[3].fX + pointArray[uiOffset2]) * dMatrix_0_2
      + (pData->pointAy[3].fZ + pointArray[uiOffset2 + 2]) * dMatrix_2_2;
    uiOffset2 += 3;
    matrixWork[uiOffset2 + 2] = dTransformedZ;
  } while (uiOffset2 != 27);
  iLoop4 = 0;
  dNextAngleY = getdirection(matrixWork[18] - matrixWork[15], matrixWork[19] - matrixWork[16]);
  dNextAngleYSaved = dNextAngleY;
  do {
    dSinNextY = sin(-dNextAngleY);
    dWorkAngle = cos(-dNextAngleY);
    dTemPRotNextY = matrixWork[iLoop4 + 4] * dSinNextY;
    dCosY = dWorkAngle;
    dRotatedX = matrixWork[iLoop4 + 3] * dWorkAngle - dTemPRotNextY;
    dRotatedY = dSinNextY * matrixWork[iLoop4 + 3] + matrixWork[iLoop4 + 4] * dWorkAngle;
    iLoop4 += 3;

    matrixWork[iLoop4] = dRotatedX;
    matrixWork[iLoop4 + 1] = dRotatedY;
    //LODWORD(matrixWork[iLoop4]) = LODWORD(dRotatedX);
    //HIDWORD(matrixWork[iLoop4]) = HIDWORD(dRotatedX);
    //LODWORD(matrixWork[iLoop4 + 1]) = LODWORD(dRotatedY);
    //HIDWORD(matrixWork[iLoop4 + 1]) = HIDWORD(dRotatedY);
  } while (iLoop4 != 27);
  iLoop5 = 0;
  dNextAngleZ = getdirection(matrixWork[18] - matrixWork[15], matrixWork[20] - matrixWork[17]);
  dNextAngleZSaved = dNextAngleZ;
  do {
    dSinNextZ = sin(dNextAngleZ);
    dWorkAngle = cos(dNextAngleZ);
    dTempRotNextZ = matrixWork[iLoop5 + 5] * dSinNextZ;
    dCosY_1 = dWorkAngle;
    dRotatedX = dTempRotNextZ + matrixWork[iLoop5 + 3] * dWorkAngle;
    dRotatedZ = matrixWork[iLoop5 + 5] * dWorkAngle + -dSinNextZ * matrixWork[iLoop5 + 3];
    iLoop5 += 3;

    matrixWork[iLoop5] = dRotatedX;
    matrixWork[iLoop5 + 2] = dRotatedZ;
    //LODWORD(matrixWork[iLoop5]) = LODWORD(dRotatedX);
    //HIDWORD(matrixWork[iLoop5]) = HIDWORD(dRotatedX);
    //LODWORD(matrixWork[iLoop5 + 2]) = LODWORD(dRotatedZ);
    //HIDWORD(matrixWork[iLoop5 + 2]) = HIDWORD(dRotatedZ);
  } while (iLoop5 != 27);

  dWorkAngle = getdirection(matrixWork[22] - matrixWork[25], matrixWork[26] - matrixWork[23]);
  dCosY = 1.0 / 6.28318530718;                  // Convert angles to internal fixed-point format (16384 = 2pi radians)
  dAngleYFixed = dNextAngleYSaved * 16384.0 * dCosY + 0.5;
  floor(dAngleYFixed);
  //_CHP();
  pData->iYaw = (int)dAngleYFixed;
  dAngleZFixed = dNextAngleZSaved * 16384.0 * dCosY + 0.5;
  floor(dAngleZFixed);
  //_CHP();
  pData->iPitch = (int)dAngleZFixed;
  dAngleXFixed = dWorkAngle * 16384.0 * dCosY + 0.5;
  floor(dAngleXFixed);
  //_CHP();
  pData->iPitch &= 0x3FFFu;
  iYawTemp = pData->iYaw;
  pData->iRoll = (int)dAngleXFixed;
  if (iYawTemp > 0x2000)
    pData->iYaw = iYawTemp - 0x4000;
  iPitchTemp = pData->iPitch;
  if (iPitchTemp > 0x2000)
    pData->iPitch = iPitchTemp - 0x4000;
  iRollTemp = pData->iRoll;
  if (iRollTemp > 0x2000)
    pData->iRoll = iRollTemp - 0x4000;
  pData->gravity.fX = (float)(dSinZSaved * -3.0);        // Store up vector scaled by -3 for physics calculations
  pData->gravity.fY = (float)(dMatrix21 * -3.0);
  pData->gravity.fZ = (float)(dMatrix22 * -3.0);
}

//-------------------------------------------------------------------------------------------------

void dopitchchanges(int a1, int a2)
{/*
  int v2; // esi
  int v3; // ebp
  int v4; // edi
  int v5; // ecx
  float *v6; // ebx
  unsigned int v7; // eax
  double v8; // st7
  int v9; // eax
  int v10; // eax
  unsigned int v11; // eax
  double v12; // st7
  unsigned int v13; // eax
  double v14; // st7
  double v15; // st6
  double v16; // st5
  double v17; // st4
  int v18; // ebx
  double v19; // st7
  long double v20; // rt0
  long double v21; // st5
  int v22; // ebx
  double v23; // st7
  long double v24; // st6
  long double v25; // st5
  int v26; // ebx
  long double v27; // st6
  long double v28; // st7
  long double v29; // st5
  long double v30; // rt2
  long double v31; // st6
  float *v32; // ebx
  unsigned int v33; // eax
  double v34; // st7
  int v35; // eax
  int v36; // eax
  unsigned int v37; // eax
  double v38; // st7
  unsigned int v39; // eax
  long double v40; // st7
  long double v41; // st6
  double v42; // st5
  double v43; // st3
  double v44; // rt2
  int v45; // ebx
  double v46; // st7
  long double v47; // rtt
  long double v48; // st5
  double v49; // st7
  char *v50; // edx
  int v51; // eax
  int v52; // eax
  _DWORD v53[6]; // [esp+0h] [ebp-3DCh]
  double v54; // [esp+18h] [ebp-3C4h]
  double v55; // [esp+20h] [ebp-3BCh]
  double v56; // [esp+28h] [ebp-3B4h]
  int v57; // [esp+30h] [ebp-3ACh]
  int v58; // [esp+34h] [ebp-3A8h]
  double v59; // [esp+38h] [ebp-3A4h]
  double v60; // [esp+40h] [ebp-39Ch]
  int v61; // [esp+48h] [ebp-394h]
  int v62; // [esp+4Ch] [ebp-390h]
  double v63; // [esp+50h] [ebp-38Ch]
  double v64; // [esp+58h] [ebp-384h]
  int v65; // [esp+60h] [ebp-37Ch]
  int v66; // [esp+64h] [ebp-378h]
  double v67; // [esp+68h] [ebp-374h]
  double v68; // [esp+70h] [ebp-36Ch]
  double v69; // [esp+78h] [ebp-364h]
  double v70; // [esp+80h] [ebp-35Ch]
  double v71; // [esp+88h] [ebp-354h]
  double v72; // [esp+90h] [ebp-34Ch]
  double v73; // [esp+98h] [ebp-344h]
  double v74; // [esp+A0h] [ebp-33Ch]
  double v75; // [esp+F0h] [ebp-2ECh]
  double v76; // [esp+F8h] [ebp-2E4h]
  double v77; // [esp+100h] [ebp-2DCh]
  int v78; // [esp+108h] [ebp-2D4h]
  int v79; // [esp+10Ch] [ebp-2D0h]
  double v80; // [esp+110h] [ebp-2CCh]
  double v81; // [esp+118h] [ebp-2C4h]
  int v82; // [esp+120h] [ebp-2BCh]
  int v83; // [esp+124h] [ebp-2B8h]
  double v84; // [esp+128h] [ebp-2B4h]
  double v85; // [esp+130h] [ebp-2ACh]
  int v86; // [esp+138h] [ebp-2A4h]
  int v87; // [esp+13Ch] [ebp-2A0h]
  double v88; // [esp+140h] [ebp-29Ch]
  double v89; // [esp+148h] [ebp-294h]
  _DWORD v90[6]; // [esp+1B0h] [ebp-22Ch]
  double v91; // [esp+1C8h] [ebp-214h]
  double v92; // [esp+1D0h] [ebp-20Ch]
  double v93; // [esp+1D8h] [ebp-204h]
  double v94; // [esp+1E0h] [ebp-1FCh]
  double v95; // [esp+1E8h] [ebp-1F4h]
  double v96; // [esp+1F0h] [ebp-1ECh]
  double v97; // [esp+1F8h] [ebp-1E4h]
  double v98; // [esp+200h] [ebp-1DCh]
  double v99; // [esp+208h] [ebp-1D4h]
  double v100; // [esp+210h] [ebp-1CCh]
  double v101; // [esp+218h] [ebp-1C4h]
  double v102; // [esp+220h] [ebp-1BCh]
  double v103; // [esp+228h] [ebp-1B4h]
  double v104; // [esp+230h] [ebp-1ACh]
  double v105; // [esp+238h] [ebp-1A4h]
  double v106; // [esp+240h] [ebp-19Ch]
  double v107; // [esp+248h] [ebp-194h]
  double v108; // [esp+250h] [ebp-18Ch]
  double v109; // [esp+258h] [ebp-184h]
  double v110; // [esp+260h] [ebp-17Ch]
  double v111; // [esp+268h] [ebp-174h]
  double v112; // [esp+270h] [ebp-16Ch]
  double v113; // [esp+278h] [ebp-164h]
  double v114; // [esp+280h] [ebp-15Ch]
  double v115; // [esp+288h] [ebp-154h]
  double v116; // [esp+290h] [ebp-14Ch]
  double v117; // [esp+298h] [ebp-144h]
  long double v118; // [esp+2A0h] [ebp-13Ch]
  long double v119; // [esp+2A8h] [ebp-134h]
  long double v120; // [esp+2B0h] [ebp-12Ch]
  long double v121; // [esp+2B8h] [ebp-124h]
  long double v122; // [esp+2C0h] [ebp-11Ch]
  long double v123; // [esp+2C8h] [ebp-114h]
  long double v124; // [esp+2D0h] [ebp-10Ch]
  long double v125; // [esp+2D8h] [ebp-104h]
  long double v126; // [esp+2E8h] [ebp-F4h]
  long double v127; // [esp+2F0h] [ebp-ECh]
  double v128; // [esp+2F8h] [ebp-E4h]
  double v129; // [esp+300h] [ebp-DCh]
  double v130; // [esp+308h] [ebp-D4h]
  double v131; // [esp+310h] [ebp-CCh]
  double v132; // [esp+318h] [ebp-C4h]
  long double v133; // [esp+320h] [ebp-BCh]
  double v134; // [esp+328h] [ebp-B4h]
  long double v135; // [esp+330h] [ebp-ACh]
  long double v136; // [esp+338h] [ebp-A4h]
  long double v137; // [esp+340h] [ebp-9Ch]
  long double v138; // [esp+348h] [ebp-94h]
  long double v139; // [esp+350h] [ebp-8Ch]
  long double v140; // [esp+358h] [ebp-84h]
  long double v141; // [esp+360h] [ebp-7Ch]
  long double v142; // [esp+368h] [ebp-74h]
  double v143; // [esp+370h] [ebp-6Ch]
  double v144; // [esp+378h] [ebp-64h]
  double v145; // [esp+380h] [ebp-5Ch]
  long double v146; // [esp+388h] [ebp-54h]
  double v147; // [esp+390h] [ebp-4Ch]
  double v148; // [esp+398h] [ebp-44h]
  double v149; // [esp+3A0h] [ebp-3Ch]
  double v150; // [esp+3A8h] [ebp-34h]
  long double v151; // [esp+3B0h] [ebp-2Ch]
  unsigned int v152; // [esp+3B8h] [ebp-24h]
  unsigned int v153; // [esp+3BCh] [ebp-20h]
  int v154; // [esp+3C0h] [ebp-1Ch]
  int v155; // [esp+3C4h] [ebp-18h]

  v155 = a1;
  v2 = 0;
  if (TRAK_LEN > 0) {
    v152 = 12 * a1;
    v3 = 3 * a1;
    v153 = 12 * a2;
    v4 = 3 * a2;
    do {
      v5 = v2 + 1;
      if (v2 + 1 == TRAK_LEN)
        v5 ^= TRAK_LEN;
      v154 = v5 + 1;
      if (v5 + 1 == TRAK_LEN)
        v154 = 0;
      v91 = TrakPt[v3];
      v92 = TrakPt_variable_1[v3];
      v93 = TrakPt_variable_2[v3];
      v94 = TrakPt[v4];
      v95 = TrakPt_variable_1[v4];
      v96 = TrakPt_variable_2[v4];
      v97 = TrakPt[18 * v5 + v152 / 4];
      v98 = TrakPt_variable_1[18 * v5 + v152 / 4];
      v99 = TrakPt_variable_2[18 * v5 + v152 / 4];
      v100 = TrakPt[18 * v5 + v153 / 4];
      v101 = TrakPt_variable_1[18 * v5 + v153 / 4];
      v6 = (float *)((char *)&localdata + 128 * v2);
      v7 = 0;
      v102 = TrakPt_variable_2[18 * v5 + v153 / 4];
      do {
        *(double *)((char *)&v54 + v7) = (v6[10] + *(double *)((char *)&v92 + v7)) * v6[3]
          + (v6[9] + *(double *)((char *)&v91 + v7)) * *v6
          + (v6[11] + *(double *)((char *)&v93 + v7)) * v6[6];
        *(double *)((char *)&v55 + v7) = (v6[10] + *(double *)((char *)&v92 + v7)) * v6[4]
          + (v6[9] + *(double *)((char *)&v91 + v7)) * v6[1]
          + (v6[11] + *(double *)((char *)&v93 + v7)) * v6[7];
        v8 = (v6[10] + *(double *)((char *)&v92 + v7)) * v6[5]
          + (v6[9] + *(double *)((char *)&v91 + v7)) * v6[2]
          + (v6[11] + *(double *)((char *)&v93 + v7)) * v6[8];
        v7 += 24;
        *(double *)&v53[v7 / 4 + 4] = v8;
      } while (v7 != 96);
      v9 = (-*((_DWORD *)v6 + 22) / 2) & 0x3FFF;
      v150 = tcos[v9];
      v131 = tsin[v9];
      v76 = v55 * v150 - v56 * v131;
      v77 = v55 * v131 + v56 * v150;
      v80 = v59 * v150 - v60 * v131;
      v81 = v59 * v131 + v60 * v150;
      v75 = v54;
      v78 = v57;
      v79 = v58;
      v10 = (*((_DWORD *)v6 + 22) / 2) & 0x3FFF;
      v149 = tcos[v10];
      v128 = tsin[v10];
      v84 = v63 * v149 - v64 * v128;
      v85 = v63 * v128 + v64 * v149;
      v88 = v67 * v149 - v68 * v128;
      v82 = v61;
      v83 = v62;
      v86 = v65;
      v87 = v66;
      v11 = 0;
      v89 = v67 * v128 + v68 * v149;
      do {
        *(double *)((char *)&v91 + v11) = v6[1] * *(double *)((char *)&v76 + v11)
          + *v6 * *(double *)((char *)&v75 + v11)
          + v6[2] * *(double *)((char *)&v77 + v11)
          - v6[9];
        *(double *)((char *)&v92 + v11) = v6[4] * *(double *)((char *)&v76 + v11)
          + v6[3] * *(double *)((char *)&v75 + v11)
          + v6[5] * *(double *)((char *)&v77 + v11)
          - v6[10];
        v12 = v6[7] * *(double *)((char *)&v76 + v11)
          + v6[6] * *(double *)((char *)&v75 + v11)
          + v6[8] * *(double *)((char *)&v77 + v11)
          - v6[11];
        v11 += 24;
        *(double *)&v90[v11 / 4 + 4] = v12;
      } while (v11 != 96);
      v103 = (v91 + v94) * transfrm_c_variable_6;
      v104 = (v92 + v95) * transfrm_c_variable_6;
      v105 = (v93 + v96) * transfrm_c_variable_6;
      v106 = (v97 + v100) * transfrm_c_variable_6;
      v107 = (v98 + v101) * transfrm_c_variable_6;
      v108 = (v99 + v102) * transfrm_c_variable_6;
      v109 = (v91 + v97) * transfrm_c_variable_6;
      v110 = (v92 + v98) * transfrm_c_variable_6;
      v111 = (v93 + v99) * transfrm_c_variable_6;
      v112 = (v94 + v100) * transfrm_c_variable_6;
      v113 = (v95 + v101) * transfrm_c_variable_6;
      v114 = (v96 + v102) * transfrm_c_variable_6;
      v115 = (v103 + v106) * transfrm_c_variable_6;
      v116 = (v104 + v107) * transfrm_c_variable_6;
      v117 = (v105 + v108) * transfrm_c_variable_6;
      v145 = -v115;
      v143 = -v116;
      v144 = -v117;
      v91 = v91 - v115;
      v92 = v92 - v116;
      v13 = 24;
      v93 = v93 - v117;
      v14 = v144;
      v15 = v143;
      v16 = v145;
      do {
        *(double *)((char *)&v91 + v13) = *(double *)((char *)&v91 + v13) + v16;
        *(double *)((char *)&v92 + v13) = *(double *)((char *)&v92 + v13) + v15;
        *(double *)((char *)&v93 + v13) = *(double *)((char *)&v93 + v13) + v14;
        *(double *)((char *)&v94 + v13) = *(double *)((char *)&v94 + v13) + v16;
        *(double *)((char *)&v95 + v13) = *(double *)((char *)&v95 + v13) + v15;
        *(double *)((char *)&v96 + v13) = *(double *)((char *)&v96 + v13) + v14;
        *(double *)((char *)&v97 + v13) = *(double *)((char *)&v97 + v13) + v16;
        *(double *)((char *)&v98 + v13) = *(double *)((char *)&v98 + v13) + v15;
        *(double *)((char *)&v99 + v13) = *(double *)((char *)&v99 + v13) + v14;
        *(double *)((char *)&v100 + v13) = *(double *)((char *)&v100 + v13) + v16;
        *(double *)((char *)&v101 + v13) = *(double *)((char *)&v101 + v13) + v15;
        v17 = *(double *)((char *)&v102 + v13) + v14;
        v13 += 96;
        *(double *)&v90[v13 / 4 + 4] = v17;
      } while (v13 != 216);
      v18 = 0;
      v19 = getdirection(v106 - v103, v107 - v104);
      v133 = v19;
      do {
        v20 = sin(-v19);
        v151 = cos(-v19);
        v21 = *(double *)((char *)&v92 + v18 * 4) * v20;
        v125 = v151;
        v120 = *(double *)((char *)&v91 + v18 * 4) * v151 - v21;
        v119 = v20 * *(double *)((char *)&v91 + v18 * 4) + *(double *)((char *)&v92 + v18 * 4) * v151;
        v18 += 6;
        v90[v18] = LODWORD(v120);
        v90[v18 + 1] = HIDWORD(v120);
        v90[v18 + 2] = LODWORD(v119);
        v90[v18 + 3] = HIDWORD(v119);
      } while (v18 != 54);
      v22 = 0;
      v23 = getdirection(v106 - v103, v108 - v105);
      v140 = v23;
      do {
        v24 = sin(v23);
        v151 = cos(v23);
        v25 = *(double *)((char *)&v93 + v22 * 4) * v24;
        v125 = v151;
        v120 = v25 + *(double *)((char *)&v91 + v22 * 4) * v151;
        v118 = *(double *)((char *)&v93 + v22 * 4) * v151 + -v24 * *(double *)((char *)&v91 + v22 * 4);
        v22 += 6;
        v90[v22] = LODWORD(v120);
        v90[v22 + 1] = HIDWORD(v120);
        v90[v22 + 4] = LODWORD(v118);
        v90[v22 + 5] = HIDWORD(v118);
      } while (v22 != 54);
      v26 = 0;
      v134 = getdirection(v110 - v113, v114 - v111);
      v27 = v134;
      do {
        v28 = cos(v27);
        v151 = sin(v27);
        v29 = *(double *)((char *)&v92 + v26 * 4) * v28;
        v142 = v151;
        v119 = v29 - *(double *)((char *)&v93 + v26 * 4) * v151;
        v118 = *(double *)((char *)&v92 + v26 * 4) * v151 + *(double *)((char *)&v93 + v26 * 4) * v28;
        v26 += 6;
        v90[v26 + 2] = LODWORD(v119);
        v90[v26 + 3] = HIDWORD(v119);
        v90[v26 + 4] = LODWORD(v118);
        v90[v26 + 5] = HIDWORD(v118);
      } while (v26 != 54);
      v141 = v28;
      v30 = cos(v133);
      v146 = sin(v133);
      v31 = cos(v140);
      v139 = v30 * v31;
      v126 = sin(v140);
      v127 = v30 * v126;
      v151 = v146;
      v121 = v127 * v142 + -v146 * v28;
      v137 = -v146 * v142 - v127 * v28;
      v136 = v146 * v31;
      v138 = v146 * v126 * v142 + v30 * v28;
      v122 = v30 * v142 - v146 * v126 * v28;
      v124 = v142 * -v31;
      v135 = v28 * v31;
      v123 = v126;
      v91 = TrakPt[18 * v5 + v152 / 4];
      v92 = TrakPt_variable_1[18 * v5 + v152 / 4];
      v93 = TrakPt_variable_2[18 * v5 + v152 / 4];
      v94 = TrakPt[18 * v5 + v153 / 4];
      v95 = TrakPt_variable_1[18 * v5 + v153 / 4];
      v96 = TrakPt_variable_2[18 * v5 + v153 / 4];
      v97 = TrakPt[18 * v154 + v152 / 4];
      v98 = TrakPt_variable_1[18 * v154 + v152 / 4];
      v99 = TrakPt_variable_2[18 * v154 + v152 / 4];
      v100 = TrakPt[18 * v154 + v153 / 4];
      v101 = TrakPt_variable_1[18 * v154 + v153 / 4];
      v32 = (float *)((char *)&localdata + 128 * v5);
      v33 = 0;
      v102 = TrakPt_variable_2[18 * v154 + v153 / 4];
      do {
        *(double *)((char *)&v54 + v33) = (v32[10] + *(double *)((char *)&v92 + v33)) * v32[3]
          + (v32[9] + *(double *)((char *)&v91 + v33)) * *v32
          + (v32[11] + *(double *)((char *)&v93 + v33)) * v32[6];
        *(double *)((char *)&v55 + v33) = (v32[10] + *(double *)((char *)&v92 + v33)) * v32[4]
          + (v32[9] + *(double *)((char *)&v91 + v33)) * v32[1]
          + (v32[11] + *(double *)((char *)&v93 + v33)) * v32[7];
        v34 = (v32[10] + *(double *)((char *)&v92 + v33)) * v32[5]
          + (v32[9] + *(double *)((char *)&v91 + v33)) * v32[2]
          + (v32[11] + *(double *)((char *)&v93 + v33)) * v32[8];
        v33 += 24;
        *(double *)&v53[v33 / 4 + 4] = v34;
      } while (v33 != 96);
      v35 = (-*((_DWORD *)v32 + 22) / 2) & 0x3FFF;
      v148 = tcos[v35];
      v130 = tsin[v35];
      v76 = v55 * v148 - v56 * v130;
      v77 = v55 * v130 + v56 * v148;
      v80 = v59 * v148 - v60 * v130;
      v81 = v59 * v130 + v60 * v148;
      v75 = v54;
      v78 = v57;
      v79 = v58;
      v36 = (*((_DWORD *)v32 + 22) / 2) & 0x3FFF;
      v132 = tcos[v36];
      v129 = tsin[v36];
      v84 = v63 * v132 - v64 * v129;
      v85 = v63 * v129 + v64 * v132;
      v88 = v67 * v132 - v68 * v129;
      v82 = v61;
      v83 = v62;
      v86 = v65;
      v87 = v66;
      v37 = 0;
      v89 = v67 * v129 + v68 * v132;
      do {
        *(double *)((char *)&v91 + v37) = v32[1] * *(double *)((char *)&v76 + v37)
          + *v32 * *(double *)((char *)&v75 + v37)
          + v32[2] * *(double *)((char *)&v77 + v37)
          - v32[9];
        *(double *)((char *)&v92 + v37) = v32[4] * *(double *)((char *)&v76 + v37)
          + v32[3] * *(double *)((char *)&v75 + v37)
          + v32[5] * *(double *)((char *)&v77 + v37)
          - v32[10];
        v38 = v32[7] * *(double *)((char *)&v76 + v37)
          + v32[6] * *(double *)((char *)&v75 + v37)
          + v32[8] * *(double *)((char *)&v77 + v37)
          - v32[11];
        v37 += 24;
        *(double *)&v90[v37 / 4 + 4] = v38;
      } while (v37 != 96);
      v103 = (v91 + v94) * transfrm_c_variable_6;
      v104 = (v92 + v95) * transfrm_c_variable_6;
      v105 = (v93 + v96) * transfrm_c_variable_6;
      v106 = (v97 + v100) * transfrm_c_variable_6;
      v107 = (v98 + v101) * transfrm_c_variable_6;
      v108 = (v99 + v102) * transfrm_c_variable_6;
      v109 = (v91 + v97) * transfrm_c_variable_6;
      v110 = (v92 + v98) * transfrm_c_variable_6;
      v111 = (v93 + v99) * transfrm_c_variable_6;
      v112 = (v94 + v100) * transfrm_c_variable_6;
      v113 = (v95 + v101) * transfrm_c_variable_6;
      v114 = (v96 + v102) * transfrm_c_variable_6;
      v115 = (v103 + v106) * transfrm_c_variable_6;
      v116 = (v104 + v107) * transfrm_c_variable_6;
      v39 = 0;
      v117 = (v105 + v108) * transfrm_c_variable_6;
      v40 = v137;
      v41 = v121;
      do {
        v42 = *(double *)((char *)&v92 + v39) + v143;
        v43 = *(double *)((char *)&v91 + v39) + v145;
        v44 = *(double *)((char *)&v93 + v39) + v144;
        *(double *)((char *)&v54 + v39) = v136 * v42 + v139 * v43 + v123 * v44;
        *(double *)((char *)&v55 + v39) = v138 * v42 + v41 * v43 + v124 * v44;
        v39 += 24;
        *(long double *)&v53[v39 / 4 + 4] = v42 * v122 + v43 * v40 + v44 * v135;
      } while (v39 != 216);
      v45 = 0;
      v46 = getdirection(v72 - v69, v73 - v70);
      do {
        v47 = sin(-v46);
        v151 = cos(-v46);
        v48 = *(double *)((char *)&v55 + v45 * 4) * v47;
        v146 = v151;
        v120 = *(double *)((char *)&v54 + v45 * 4) * v151 - v48;
        v119 = v47 * *(double *)((char *)&v54 + v45 * 4) + *(double *)((char *)&v55 + v45 * 4) * v151;
        v45 += 6;
        v53[v45] = LODWORD(v120);
        v53[v45 + 1] = HIDWORD(v120);
        v53[v45 + 2] = LODWORD(v119);
        v53[v45 + 3] = HIDWORD(v119);
      } while (v45 != 54);
      v49 = getdirection(v72 - v69, v74 - v71) * transfrm_c_variable_7 / transfrm_c_variable_8 + transfrm_c_variable_6;
      v50 = (char *)&localdata + 128 * v2;
      v147 = v49;
      if (v155) {
        v52 = floor(v147);
        _CHP(v52, v50);
        *((_DWORD *)v50 + 18) = (int)v49;
      } else {
        v51 = floor(v147);
        _CHP(v51, v50);
        *((_DWORD *)v50 + 17) = (int)v49;
      }
      v4 += 18;
      ++v2;
      v3 += 18;
    } while (v2 < TRAK_LEN);
  }*/
}

//-------------------------------------------------------------------------------------------------

int getpitchchange(int a1, int a2, int a3)
{
  return 0; /*
  int v5; // ecx
  float *v6; // ebx
  int v7; // ebp
  int v8; // eax
  int v9; // eax
  unsigned int v10; // eax
  double v11; // st7
  double v12; // st6
  double v13; // st5
  double v14; // st4
  int v15; // edx
  double v16; // st7
  long double v17; // rt0
  long double v18; // st5
  int v19; // edx
  double v20; // st7
  long double v21; // st6
  long double v22; // st5
  int v23; // edx
  long double v24; // st6
  long double v25; // st7
  long double v26; // st5
  double v27; // st7
  double v28; // st6
  double v29; // st7
  int v30; // eax
  int v31; // eax
  int v32; // eax
  double v33; // st7
  double v34; // st6
  double v35; // st5
  double v36; // st3
  double v37; // rt0
  int v38; // edx
  double v39; // st7
  long double v40; // rt1
  long double v41; // st5
  double v42; // st7
  int v43; // eax
  _DWORD v45[6]; // [esp+0h] [ebp-28Ch]
  double v46; // [esp+18h] [ebp-274h]
  double v47; // [esp+20h] [ebp-26Ch]
  double v48; // [esp+28h] [ebp-264h]
  double v49; // [esp+30h] [ebp-25Ch]
  double v50; // [esp+38h] [ebp-254h]
  double v51; // [esp+40h] [ebp-24Ch]
  double v52; // [esp+48h] [ebp-244h]
  double v53; // [esp+50h] [ebp-23Ch]
  double v54; // [esp+58h] [ebp-234h]
  double v55; // [esp+60h] [ebp-22Ch]
  double v56; // [esp+68h] [ebp-224h]
  double v57; // [esp+70h] [ebp-21Ch]
  double v58; // [esp+78h] [ebp-214h]
  double v59; // [esp+80h] [ebp-20Ch]
  double v60; // [esp+88h] [ebp-204h]
  double v61; // [esp+90h] [ebp-1FCh]
  double v62; // [esp+98h] [ebp-1F4h]
  double v63; // [esp+A0h] [ebp-1ECh]
  double v64; // [esp+A8h] [ebp-1E4h]
  double v65; // [esp+B0h] [ebp-1DCh]
  double v66; // [esp+B8h] [ebp-1D4h]
  double v67; // [esp+C0h] [ebp-1CCh]
  double v68; // [esp+C8h] [ebp-1C4h]
  double v69; // [esp+D0h] [ebp-1BCh]
  double v70; // [esp+D8h] [ebp-1B4h]
  double v71; // [esp+E0h] [ebp-1ACh]
  double v72[13]; // [esp+E8h] [ebp-1A4h]
  double v73; // [esp+150h] [ebp-13Ch]
  double v74; // [esp+158h] [ebp-134h]
  double v75; // [esp+160h] [ebp-12Ch]
  double v76; // [esp+168h] [ebp-124h]
  double v77; // [esp+170h] [ebp-11Ch]
  double v78; // [esp+178h] [ebp-114h]
  long double v79; // [esp+1C8h] [ebp-C4h]
  long double v80; // [esp+1D0h] [ebp-BCh]
  long double v81; // [esp+1D8h] [ebp-B4h]
  double v82; // [esp+1E0h] [ebp-ACh]
  double v83; // [esp+1E8h] [ebp-A4h]
  double v84; // [esp+1F0h] [ebp-9Ch]
  double v85; // [esp+1F8h] [ebp-94h]
  double v86; // [esp+200h] [ebp-8Ch]
  double v87; // [esp+208h] [ebp-84h]
  double v88; // [esp+210h] [ebp-7Ch]
  double v89; // [esp+218h] [ebp-74h]
  long double v90; // [esp+220h] [ebp-6Ch]
  long double v91; // [esp+228h] [ebp-64h]
  long double v92; // [esp+230h] [ebp-5Ch]
  double v93; // [esp+238h] [ebp-54h]
  double v94; // [esp+240h] [ebp-4Ch]
  double v95; // [esp+248h] [ebp-44h]
  double v96; // [esp+250h] [ebp-3Ch]
  long double v97; // [esp+258h] [ebp-34h]
  long double v98; // [esp+260h] [ebp-2Ch]
  double v99; // [esp+268h] [ebp-24h]
  int v100; // [esp+270h] [ebp-1Ch]
  int v101; // [esp+274h] [ebp-18h]
  int v102; // [esp+278h] [ebp-14h]

  v5 = a1 + 1;
  v6 = (float *)((char *)&localdata + 128 * a1);
  if (a1 + 1 == TRAK_LEN)
    v5 ^= TRAK_LEN;
  v7 = v5 + 1;
  if (v5 + 1 == TRAK_LEN)
    v7 ^= TRAK_LEN;
  v102 = a1;
  v100 = 72 * a1;
  v101 = 12 * a2;
  v8 = 12 * a2 + 72 * a1;
  v46 = *(float *)((char *)TrakPt + v8);
  v47 = *(float *)((char *)TrakPt_variable_1 + v8);
  v48 = *(float *)((char *)TrakPt_variable_2 + v8);
  v102 = 12 * a3;
  v9 = 12 * a3 + v100;
  v49 = *(float *)((char *)TrakPt + v9);
  v50 = *(float *)((char *)TrakPt_variable_1 + v9);
  v51 = *(float *)((char *)TrakPt_variable_2 + v9);
  v52 = TrakPt[18 * v5 + 3 * a2];
  v53 = TrakPt_variable_1[18 * v5 + 3 * a2];
  v54 = TrakPt_variable_2[18 * v5 + 3 * a2];
  v55 = TrakPt[18 * v5 + 3 * a3];
  v56 = TrakPt_variable_1[18 * v5 + 3 * a3];
  v57 = TrakPt_variable_2[18 * v5 + 3 * a3];
  v58 = (v46 + v49) * transfrm_c_variable_9;
  v59 = (v47 + v50) * transfrm_c_variable_9;
  v60 = (v48 + v51) * transfrm_c_variable_9;
  v61 = (v52 + v55) * transfrm_c_variable_9;
  v62 = (v53 + v56) * transfrm_c_variable_9;
  v63 = (v54 + v57) * transfrm_c_variable_9;
  v64 = (v46 + v52) * transfrm_c_variable_9;
  v65 = (v47 + v53) * transfrm_c_variable_9;
  v66 = (v48 + v54) * transfrm_c_variable_9;
  v67 = (v49 + v55) * transfrm_c_variable_9;
  v68 = (v50 + v56) * transfrm_c_variable_9;
  v69 = (v51 + v57) * transfrm_c_variable_9;
  v70 = (v58 + v61) * transfrm_c_variable_9;
  v71 = (v59 + v62) * transfrm_c_variable_9;
  v72[0] = (v60 + v63) * transfrm_c_variable_9;
  v93 = -v6[9];
  v94 = -v6[10];
  v95 = -v6[11];
  v46 = v46 + v93;
  v47 = v47 + v94;
  v10 = 24;
  v48 = v48 + v95;
  v11 = v95;
  v12 = v94;
  v13 = v93;
  do {
    *(double *)((char *)&v46 + v10) = *(double *)((char *)&v46 + v10) + v13;
    *(double *)((char *)&v47 + v10) = *(double *)((char *)&v47 + v10) + v12;
    *(double *)((char *)&v48 + v10) = *(double *)((char *)&v48 + v10) + v11;
    *(double *)((char *)&v49 + v10) = *(double *)((char *)&v49 + v10) + v13;
    *(double *)((char *)&v50 + v10) = *(double *)((char *)&v50 + v10) + v12;
    *(double *)((char *)&v51 + v10) = *(double *)((char *)&v51 + v10) + v11;
    *(double *)((char *)&v52 + v10) = *(double *)((char *)&v52 + v10) + v13;
    *(double *)((char *)&v53 + v10) = *(double *)((char *)&v53 + v10) + v12;
    *(double *)((char *)&v54 + v10) = *(double *)((char *)&v54 + v10) + v11;
    *(double *)((char *)&v55 + v10) = *(double *)((char *)&v55 + v10) + v13;
    *(double *)((char *)&v56 + v10) = *(double *)((char *)&v56 + v10) + v12;
    v14 = *(double *)((char *)&v57 + v10) + v11;
    v10 += 96;
    *(double *)&v45[v10 / 4 + 4] = v14;
  } while (v10 != 216);
  v15 = 0;
  v16 = getdirection(v61 - v58, v62 - v59);
  do {
    v17 = sin(-v16);
    v90 = cos(-v16);
    v18 = *(double *)((char *)&v47 + v15 * 4) * v17;
    v91 = v90;
    v81 = *(double *)((char *)&v46 + v15 * 4) * v90 - v18;
    v80 = v17 * *(double *)((char *)&v46 + v15 * 4) + *(double *)((char *)&v47 + v15 * 4) * v90;
    v15 += 6;
    v45[v15] = LODWORD(v81);
    v45[v15 + 1] = HIDWORD(v81);
    v45[v15 + 2] = LODWORD(v80);
    v45[v15 + 3] = HIDWORD(v80);
  } while (v15 != 54);
  v19 = 0;
  v20 = getdirection(v61 - v58, v63 - v60);
  do {
    v21 = sin(v20);
    v90 = cos(v20);
    v22 = *(double *)((char *)&v48 + v19 * 4) * v21;
    v91 = v90;
    v81 = v22 + *(double *)((char *)&v46 + v19 * 4) * v90;
    v79 = *(double *)((char *)&v48 + v19 * 4) * v90 + -v21 * *(double *)((char *)&v46 + v19 * 4);
    v19 += 6;
    v45[v19] = LODWORD(v81);
    v45[v19 + 1] = HIDWORD(v81);
    v45[v19 + 4] = LODWORD(v79);
    v45[v19 + 5] = HIDWORD(v79);
  } while (v19 != 54);
  v23 = 0;
  v96 = getdirection(v65 - v68, v69 - v66);
  v24 = v96;
  do {
    v25 = cos(v24);
    v91 = sin(v24);
    v26 = *(double *)((char *)&v47 + v23 * 4) * v25;
    v97 = v91;
    v80 = v26 - *(double *)((char *)&v48 + v23 * 4) * v91;
    v79 = *(double *)((char *)&v47 + v23 * 4) * v91 + *(double *)((char *)&v48 + v23 * 4) * v25;
    v23 += 6;
    v45[v23 + 2] = LODWORD(v80);
    v45[v23 + 3] = HIDWORD(v80);
    v45[v23 + 4] = LODWORD(v79);
    v45[v23 + 5] = HIDWORD(v79);
  } while (v23 != 54);
  v92 = v25;
  v27 = v57 - v54;
  IF_DATAN2(v27);
  v28 = v51 - v48;
  IF_DATAN2(v27);
  v29 = (v27 - v28) * transfrm_c_variable_10 / transfrm_c_variable_11 + transfrm_c_variable_9;
  v30 = floor(v29);
  _CHP(v30, 216);
  *((_DWORD *)v6 + 23) = (int)-v29;
  v85 = *v6;
  v82 = v6[1];
  v99 = v6[2];
  v83 = v6[3];
  v88 = v6[4];
  v86 = v6[5];
  v89 = v6[6];
  v84 = v6[7];
  v87 = v6[8];
  v31 = 72 * v5 + 12 * a2;
  v46 = *(float *)((char *)TrakPt + v31);
  v47 = *(float *)((char *)TrakPt_variable_1 + v31);
  v48 = *(float *)((char *)TrakPt_variable_2 + v31);
  v49 = TrakPt[18 * v5 + 3 * a3];
  v50 = TrakPt_variable_1[18 * v5 + 3 * a3];
  v51 = TrakPt_variable_2[18 * v5 + 3 * a3];
  v52 = TrakPt[18 * v7 + 3 * a2];
  v53 = TrakPt_variable_1[18 * v7 + 3 * a2];
  v54 = TrakPt_variable_2[18 * v7 + 3 * a2];
  v55 = TrakPt[18 * v7 + 3 * a3];
  v56 = TrakPt_variable_1[18 * v7 + 3 * a3];
  v57 = TrakPt_variable_2[18 * v7 + 3 * a3];
  v58 = (v46 + v49) * transfrm_c_variable_9;
  v59 = (v47 + v50) * transfrm_c_variable_9;
  v60 = (v48 + v51) * transfrm_c_variable_9;
  v61 = (v52 + v55) * transfrm_c_variable_9;
  v62 = (v53 + v56) * transfrm_c_variable_9;
  v63 = (v54 + v57) * transfrm_c_variable_9;
  v64 = (v46 + v52) * transfrm_c_variable_9;
  v65 = (v47 + v53) * transfrm_c_variable_9;
  v66 = (v48 + v54) * transfrm_c_variable_9;
  v67 = (v49 + v55) * transfrm_c_variable_9;
  v68 = (v50 + v56) * transfrm_c_variable_9;
  v69 = (v51 + v57) * transfrm_c_variable_9;
  v70 = (v58 + v61) * transfrm_c_variable_9;
  v71 = (v59 + v62) * transfrm_c_variable_9;
  v32 = 0;
  v72[0] = (v60 + v63) * transfrm_c_variable_9;
  v33 = v99;
  v34 = v82;
  do {
    v35 = *(double *)((char *)&v47 + v32 * 8) + v94;
    v36 = *(double *)((char *)&v46 + v32 * 8) + v93;
    v37 = *(double *)((char *)&v48 + v32 * 8) + v95;
    v72[v32 + 1] = v83 * v35 + v85 * v36 + v89 * v37;
    v72[v32 + 2] = v88 * v35 + v34 * v36 + v84 * v37;
    v32 += 3;
    v72[v32] = v35 * v86 + v36 * v33 + v37 * v87;
  } while (v32 != 27);
  v38 = 0;
  v39 = getdirection(v76 - v73, v77 - v74);
  do {
    v40 = sin(-v39);
    v98 = cos(-v39);
    v41 = v72[v38 + 2] * v40;
    v91 = v98;
    v81 = v72[v38 + 1] * v98 - v41;
    v80 = v40 * v72[v38 + 1] + v72[v38 + 2] * v98;
    v38 += 3;
    *(_DWORD *)((char *)&v70 + v38 * 8) = LODWORD(v81);
    *(_DWORD *)((char *)&v70 + v38 * 8 + 4) = HIDWORD(v81);
    LODWORD(v72[v38 - 1]) = LODWORD(v80);
    *(_DWORD *)((char *)&v71 + v38 * 8 + 4) = HIDWORD(v80);
  } while (v38 != 27);
  v42 = getdirection(v76 - v73, v78 - v75) * transfrm_c_variable_10 / transfrm_c_variable_11 + transfrm_c_variable_9;
  v43 = floor(v42);
  _CHP(v43, 216);
  return (int)v42;*/
}

//-------------------------------------------------------------------------------------------------
//outputs represent angles relative to the chunk's geometry, not absolute world orientation
void getworldangles(int iYaw, int iPitch, int iRoll, int iChunkIdx, int *piAzimuth, int *piElevation, int *piBank)
{
  // Get chunk data
  tData *pData = &localdata[iChunkIdx];

  // Precompute direction vector from yaw and pitch angles
  float fCosPitch = tcos[iPitch] * TRIG_SCALE;
  float fSinPitch = tsin[iPitch] * TRIG_SCALE;

  // Compute base vector components
  float fDirX = fCosPitch * tcos[iYaw];
  float fDirY = fCosPitch * tsin[iYaw];
  float fDirZ = fSinPitch;

  // Project reference points onto direction vector
  float fProjX = pData->pointAy[0].fX * fDirX + pData->pointAy[0].fY * fDirY + pData->pointAy[0].fZ * fDirZ;
  float fProjY = pData->pointAy[1].fX * fDirX + pData->pointAy[1].fY * fDirY + pData->pointAy[1].fZ * fDirZ;
  float fProjZ = pData->pointAy[2].fX * fDirX + pData->pointAy[2].fY * fDirY + pData->pointAy[2].fZ * fDirZ;

  // Calculate azimuth
  *piAzimuth = getangle(fProjX, fProjY);

  // Rotate projection into azimuth-aligned coordinate system
  float fRotatedX = fProjX * tcos[*piAzimuth] + fProjY * tsin[*piAzimuth];

  // Calculate elevation
  *piElevation = getangle(fRotatedX, fProjZ);

  // Compute roll-adjusted direction vector
  float fRollCos = tcos[iRoll] * TRIG_SCALE;
  float fRollSin = -tsin[iRoll] * TRIG_SCALE;

  // Apply pitch and yaw transformations to roll vector
  float fRollVecX = -fRollSin * fSinPitch;
  float fRollVecY = fRollVecX * tcos[iYaw] - fRollCos * tsin[iYaw];
  float fRollVecZ = fRollVecX * tsin[iYaw] + fRollCos * tcos[iYaw];
  float fRollVecW = fRollSin * fCosPitch;

  // Project reference points onto roll-adjusted vector
  float fRollProjX = pData->pointAy[0].fX * fRollVecY + pData->pointAy[0].fY * fRollVecZ + pData->pointAy[0].fZ * fRollVecW;
  float fRollProjY = pData->pointAy[1].fX * fRollVecY + pData->pointAy[1].fY * fRollVecZ + pData->pointAy[1].fZ * fRollVecW;
  float fRollProjZ = pData->pointAy[2].fX * fRollVecY + pData->pointAy[2].fY * fRollVecZ + pData->pointAy[2].fZ * fRollVecW;

  // Rotate projections using azimuth
  float fRollRotatedX = fRollProjX * tcos[*piAzimuth] + fRollProjY * tsin[*piAzimuth];
  float fRollRotatedY = -fRollProjX * tsin[*piAzimuth] + fRollProjY * tcos[*piAzimuth];

  // Apply elevation rotation
  float fBankX = fRollRotatedX * tsin[*piElevation] - fRollProjZ * tcos[*piElevation];

  // Calculate bank
  *piBank = getangle(fRollRotatedY, fBankX);
}

//-------------------------------------------------------------------------------------------------
//outputs represent local orientation relative to chunk's basis
void getlocalangles(int iYaw, int iPitch, int iRoll, int iChunkIdx, int *piAzimuth, int *piElevation, int *piBank)
{
  // Get chunk data containing reference points
  tData *pData = &localdata[iChunkIdx];

  // Precompute direction vector components
  float fCosPitch = tcos[iPitch] * TRIG_SCALE;
  float fSinPitch = tsin[iPitch] * TRIG_SCALE;
  float fCosYaw = tcos[iYaw];
  float fSinYaw = tsin[iYaw];

  // Compute basis vector weights
  float fWeightX = fCosPitch * fCosYaw;
  float fWeightY = fCosPitch * fSinYaw;
  float fWeightZ = fSinPitch;

  // Project reference points onto direction vector
  float fProjX = pData->pointAy[0].fX * fWeightX + pData->pointAy[1].fX * fWeightY + pData->pointAy[2].fX * fWeightZ;
  float fProjY = pData->pointAy[0].fY * fWeightX + pData->pointAy[1].fY * fWeightY + pData->pointAy[2].fY * fWeightZ;
  float fProjZ = pData->pointAy[0].fZ * fWeightX + pData->pointAy[1].fZ * fWeightY + pData->pointAy[2].fZ * fWeightZ;

  // Calculate azimuth
  *piAzimuth = getangle(fProjX, fProjY);

  // Rotate into azimuth-aligned coordinate system
  float fRotatedX = fProjX * tcos[*piAzimuth] + fProjY * tsin[*piAzimuth];

  // Calculate elevation
  *piElevation = getangle(fRotatedX, fProjZ);

  // Compute roll-adjusted direction vector
  float fRollCos = tcos[iRoll] * TRIG_SCALE;
  float fRollSin = -tsin[iRoll] * TRIG_SCALE;

  // Apply pitch and yaw transformations to roll vector
  float fRollWeightX = (-fRollSin * fSinPitch) * fCosYaw - fRollCos * fSinYaw;
  float fRollWeightY = (-fRollSin * fSinPitch) * fSinYaw + fRollCos * fCosYaw;
  float fRollWeightZ = fRollSin * fCosPitch;

  // Project reference points onto roll-adjusted vector
  float fRollProjX = pData->pointAy[0].fX * fRollWeightX + pData->pointAy[1].fX * fRollWeightY + pData->pointAy[2].fX * fRollWeightZ;
  float fRollProjY = pData->pointAy[0].fY * fRollWeightX + pData->pointAy[1].fY * fRollWeightY + pData->pointAy[2].fY * fRollWeightZ;
  float fRollProjZ = pData->pointAy[0].fZ * fRollWeightX + pData->pointAy[1].fZ * fRollWeightY + pData->pointAy[2].fZ * fRollWeightZ;

  // Apply azimuth rotation
  float fRollRotatedX = fRollProjX * tcos[*piAzimuth] + fRollProjY * tsin[*piAzimuth];
  float fRollRotatedY = -fRollProjX * tsin[*piAzimuth] + fRollProjY * tcos[*piAzimuth];

  // Apply elevation rotation
  float fBankX = fRollRotatedX * tsin[*piElevation] - fRollProjZ * tcos[*piElevation];

  // Calculate bank
  *piBank = getangle(fRollRotatedY, fBankX);
}

//-------------------------------------------------------------------------------------------------
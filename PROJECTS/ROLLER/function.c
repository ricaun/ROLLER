#include "function.h"
#include "loadtrak.h"
#include "control.h"
#include "sound.h"
#include "func2.h"
#include "view.h"
#include "roller.h"
#include "network.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
//-------------------------------------------------------------------------------------------------

float mapsize[25] =       //000A45C0
{
  6000.0, 6000.0, 3500.0, 4500.0, 6000.0,
  3000.0, 4000.0, 3000.0, 4000.0, 6000.0,
  6000.0, 6000.0, 6000.0, 6000.0, 6000.0,
  6000.0, 6000.0, 6000.0, 6000.0, 6000.0,
  6000.0, 6000.0, 6000.0, 6000.0, 6000.0
};
int mapsect[25] =         //000A4624
{
  10, 10, 10, 10, 10,
  10, 10, 10, 10, 10,
  10, 10, 10, 10, 10,
  10, 10, 10, 10, 10,
  10, 10, 10, 10, 10
};
int invulnerable[16];     //00149EB0

//-------------------------------------------------------------------------------------------------
//00036C00
void finish_race()
{                                               // Initialize random seed for AI behavior if player type is 1
  int iAiCarCount; // edi
  int iLap; // esi
  int iCarOrderIdx; // edx
  int iCurrentCarId; // eax
  int iFinishedCarIndex; // edx
  int ii; // eax
  int iNearCarId; // ecx
  int iFinishingCarId; // eax
  int iCarId; // ebx
  int iTotalLaps; // ebp
  int iChunk2; // ecx
  int iLap_1; // eax
  int iChunk2_1; // ebx
  int iRandomOffset; // eax
  int iTrackLength; // ebp
  int iChunkDistance; // ebx
  int iDistanceCounter; // edx
  int iLapThreshold; // eax
  int iChampAiIndex; // edx
  int j; // ecx
  int k; // eax
  int iChampionshipCarId; // eax
  int iChampPlayerIndex; // edx
  int iPlayerPlaceIndex; // ebx
  int m; // eax
  int iAiPlacementIndex; // ebx
  int iRandomValue; // eax
  int iRandomCarIndex; // eax
  int iRandomPlayerIndex; // edx
  int iPlayerPlacementIndex; // ebx
  int n; // eax
  int iCarIndex; // ebp
  int iCarArrayIndex; // esi
  int iTargetPosition; // eax
  int i; // ebx
  int iTargetCarId; // edx
  int iCurrentPosition; // ebx
  int iPositionIndex; // edx
  int iCar; // ecx
  int iCarBytesTotal; // ebx
  int iCarByteOffset; // edx
  int iCarInitIndex; // eax
  int iLapTimeIndex; // ebx
  int iLapTimeCarIndex; // ecx
  int iLapTimeCarId; // edx
  double dRunningLapTime; // st7
  int iRaceTimeCarId; // edx
  int iAiCarBytes; // edi
  int iByteOffset; // ebx
  char byFinishingLap; // cl
  int iLapAssignCarId; // edx
  double dTimeDiff; // st7
  double dRemainingTime; // st7
  double dLapThreshold; // st6
  int iRacePosition; // [esp+8h] [ebp-3Ch]
  float fTotalRaceTime; // [esp+10h] [ebp-34h]
  float fWinnerTotalTime; // [esp+14h] [ebp-30h]
  int iMaxRacerIndex; // [esp+18h] [ebp-2Ch]
  int iCarCounter; // [esp+1Ch] [ebp-28h]
  int iFinishingCarId_1; // [esp+1Ch] [ebp-28h]
  int iAiOrderIndex; // [esp+1Ch] [ebp-28h]
  int iPlayerOrderIndex; // [esp+1Ch] [ebp-28h]
  int iRandomOrderCounter; // [esp+1Ch] [ebp-28h]
  int iRandomPlayerCounter; // [esp+1Ch] [ebp-28h]
  int iFinishCarIdx; // [esp+1Ch] [ebp-28h]
  int iCarInitCounter; // [esp+1Ch] [ebp-28h]
  int iCarCountera; // [esp+1Ch] [ebp-28h]
  float fReferenceLapTime; // [esp+20h] [ebp-24h]
  float fRandomLapVariation; // [esp+24h] [ebp-20h]
  float fTimeDifference; // [esp+28h] [ebp-1Ch]

  if (player_type == 1)
    srand(random_seed);
  iAiCarCount = 0;                              // Count AI cars (non-human controlled) that are still alive
  iCarCounter = 0;
  iLap = Car[carorder[0]].byLap;
  if (racers > 0) {
    iCarOrderIdx = 0;
    do {
      iCurrentCarId = carorder[iCarOrderIdx];
      if (!human_control[iCurrentCarId] && (char)Car[iCurrentCarId].byLives > 0)
        ++iAiCarCount;
      ++iCarOrderIdx;
      ++iCarCounter;
    } while (iCarOrderIdx < racers);
  }
  if (iLap <= NoOfLaps)                       // Check if race is still in progress (current lap <= total laps)
  {
    iLapThreshold = NoOfLaps - 2;               // Handle near-end-of-race logic (last 2 laps)
    if (NoOfLaps - 2 < 1)
      iLapThreshold = 1;
    if (iLap >= iLapThreshold) {
      iFinishCarIdx = 0;                        // Handle human players finishing race in final laps
      if (racers > 0) {
        iCarIndex = 0;
        iCarArrayIndex = 0;
        iMaxRacerIndex = racers - 1;
        do {                                       // Find human player and update finishing order
          if (human_control[iCarIndex] && !finished_car[iCarIndex]) {
            iRacePosition = Car[iCarArrayIndex].byRacePosition;
            iTargetPosition = iMaxRacerIndex;
            for (i = iMaxRacerIndex; ; --i) {
              iTargetCarId = carorder[i];
              if (!finished_car[iTargetCarId])
                break;
              --iTargetPosition;
            }
            finished_car[iTargetCarId] = -1;
            iCurrentPosition = iRacePosition;
            if (iTargetPosition > iRacePosition) {
              iPositionIndex = iRacePosition;   // Shift car positions in finishing order array
              do {
                iCar = carorder[iPositionIndex + 1];
                carorder[iPositionIndex] = iCar;
                Car[iCar].byRacePosition = iCurrentPosition++;
                ++iPositionIndex;
              } while (iCurrentPosition < iTargetPosition);
            }
            carorder[iTargetPosition] = iFinishCarIdx;
            Car[iCarArrayIndex].byLives = -1;
            Car[iCarArrayIndex].byRacePosition = iFinishCarIdx;
          }
          ++iCarIndex;
          ++iCarArrayIndex;
          ++iFinishCarIdx;
        } while (iFinishCarIdx < racers);
      }
    } else if (game_type == 1 && Race > 0)      // Championship mode: Order AI cars by championship standings
    {
      iChampAiIndex = 0;
      iAiOrderIndex = 0;
      if (iAiCarCount > 0) {
        for (j = 0; j < iAiCarCount; ++j) {
          for (k = iChampAiIndex; ; ++k) {
            ++iChampAiIndex;
            if (!human_control[champorder[k]])
              break;
          }
          iChampionshipCarId = champorder[k];
          carorder[j] = iChampionshipCarId;
          finished_car[iChampionshipCarId] = -1;
          ++iAiOrderIndex;
        }
      }
      iChampPlayerIndex = 0;
      iPlayerOrderIndex = 0;
      if (players > 0) {
        iPlayerPlaceIndex = iAiCarCount;
        do {
          for (m = iChampPlayerIndex; !human_control[m]; ++m)
            ++iChampPlayerIndex;
          if (!finished_car[m]) {
            Car[iChampPlayerIndex].byLives = -1;
            carorder[iPlayerPlaceIndex] = iChampPlayerIndex;
            finished_car[m] = -1;
          }
          ++iChampPlayerIndex;
          ++iPlayerPlaceIndex;
          ++iPlayerOrderIndex;
        } while (iPlayerOrderIndex < players);
      }
    } else {
      iRandomOrderCounter = 0;                  // Random placement mode: Randomly order AI cars for finish
      if (iAiCarCount > 0) {
        iAiPlacementIndex = 0;
        while (1) {
          iRandomValue = rand();
          iRandomCarIndex = GetHighOrderRand(numcars, iRandomValue);
          //iRandomCarIndex = (iRandomValue * numcars - (__CFSHL__((iRandomValue * numcars) >> 31, 15) + ((iRandomValue * numcars) >> 31 << 15))) >> 15;
          if (iRandomCarIndex == numcars)
            iRandomCarIndex = numcars - 1;
          if (!human_control[iRandomCarIndex] && !finished_car[iRandomCarIndex]) {
            carorder[iAiPlacementIndex++] = iRandomCarIndex;
            finished_car[iRandomCarIndex] = -1;
            ++iRandomOrderCounter;
            if (iAiPlacementIndex >= iAiCarCount)
              break;
          }
        }
      }
      iRandomPlayerIndex = 0;
      iRandomPlayerCounter = 0;
      if (players > 0) {
        iPlayerPlacementIndex = iAiCarCount;
        do {
          for (n = iRandomPlayerIndex; !human_control[n]; ++n)
            ++iRandomPlayerIndex;
          if (!finished_car[n]) {
            Car[iRandomPlayerIndex].byLives = -1;
            carorder[iPlayerPlacementIndex] = iRandomPlayerIndex;
            finished_car[n] = -1;
          }
          ++iRandomPlayerIndex;
          ++iPlayerPlacementIndex;
          ++iRandomPlayerCounter;
        } while (iRandomPlayerCounter < players);
      }
    }
    iCarInitCounter = 0;                        // Initialize AI car race times and best lap times
    if (numcars > 0) {
      iCarBytesTotal = 4 * numcars;
      iCarByteOffset = 0;
      iCarInitIndex = 0;
      do {
        if (!human_control[iCarByteOffset / 4u]) {
          Car[iCarInitIndex].fTotalRaceTime = 0.0;
          Car[iCarInitIndex].fBestLapTime = 9.9999998e17f;
        }
        iCarByteOffset += 4;
        ++iCarInitIndex;
        ++iCarInitCounter;
      } while (iCarByteOffset < iCarBytesTotal);
    }
    for (iCarCountera = 0; iCarCountera < NoOfLaps; ++iCarCountera)// Generate lap times for each AI car for all laps
    {
      iLapTimeIndex = 0;
      if (iAiCarCount > 0) {
        iLapTimeCarIndex = 0;
        do {
          iLapTimeCarId = carorder[iLapTimeCarIndex];
          fRandomLapVariation = (float)((double)rand() * 0.000030517578125 + 0.02);// Add random variation (0.02-0.05s) to base lap time
          if (iLapTimeIndex)
            dRunningLapTime = Car[nearcall[3][iLapTimeCarIndex + 3]].fRunningLapTime;
          else
            dRunningLapTime = RecordLaps[game_track];
          Car[iLapTimeCarId].fRunningLapTime = (float)dRunningLapTime + fRandomLapVariation;
          iRaceTimeCarId = iLapTimeCarId;
          Car[iRaceTimeCarId].fTotalRaceTime = Car[iRaceTimeCarId].fRunningLapTime + Car[iRaceTimeCarId].fTotalRaceTime;
          if (Car[iRaceTimeCarId].fBestLapTime > (double)Car[iRaceTimeCarId].fRunningLapTime)
            Car[iRaceTimeCarId].fBestLapTime = Car[iRaceTimeCarId].fRunningLapTime;
          ++iLapTimeIndex;
          ++iLapTimeCarIndex;
        } while (iLapTimeIndex < iAiCarCount);
      }
    }
    fTotalRaceTime = Car[carorder[0]].fTotalRaceTime;// Calculate final race positions based on total race times
    fReferenceLapTime = RecordLaps[game_track];
    if (fReferenceLapTime < 10.0)
      fReferenceLapTime = 10.0;
    if (iAiCarCount > 0) {
      iAiCarBytes = 4 * iAiCarCount;
      iByteOffset = 0;
      byFinishingLap = NoOfLaps + 1;
      do {
        iLapAssignCarId = carorder[iByteOffset / 4u];
        dTimeDiff = Car[iLapAssignCarId].fTotalRaceTime - fTotalRaceTime;
        Car[iLapAssignCarId].byLap = byFinishingLap;
        if (dTimeDiff > fReferenceLapTime)    // Calculate how many laps behind based on time difference
        {
          fTimeDifference = (float)dTimeDiff;
          dRemainingTime = fTimeDifference;
          dLapThreshold = fReferenceLapTime;
          do {
            dRemainingTime = dRemainingTime - dLapThreshold;
            --Car[iLapAssignCarId].byLap;
          } while (dRemainingTime > dLapThreshold);
        }
        iByteOffset += 4;
      } while (iByteOffset < iAiCarBytes);
    }
  } else {                                             // Race in progress: Process cars finishing current lap
    while (finishers < racers) {
      iFinishedCarIndex = 0;
      for (ii = 0; finished_car[carorder[ii]]; ++ii)
        ++iFinishedCarIndex;
      iNearCarId = nearcall[3][iFinishedCarIndex + 3];
      fWinnerTotalTime = Car[iNearCarId].fTotalRaceTime;
      iFinishingCarId = carorder[iFinishedCarIndex];
      iCarId = iFinishingCarId;
      iTotalLaps = NoOfLaps;
      iChunk2 = Car[iNearCarId].nChunk2;
      finished_car[iFinishingCarId] = -1;
      iFinishingCarId_1 = iFinishingCarId;
      iLap_1 = Car[iFinishingCarId].byLap;
      ++finishers;
      if (iLap_1 == iTotalLaps)               // Check if car completed all laps
      {
        Car[iCarId].byLap = NoOfLaps + 1;
        iChunk2_1 = Car[iCarId].nChunk2;
        if (iChunk2 < iChunk2_1) {
          iTrackLength = TRAK_LEN;
          iRandomOffset = 12 * rand() / 0x8000;
          iChunk2 += iTrackLength;
        } else {
          iRandomOffset = 12 * rand() / 0x8000;
        }
        iChunkDistance = iChunk2 - iChunk2_1 + iRandomOffset;
        iDistanceCounter = 0;
        for (Car[iFinishingCarId_1].fTotalRaceTime = fWinnerTotalTime + 0.02f;
              iDistanceCounter < iChunkDistance;
              Car[iFinishingCarId_1].fTotalRaceTime = (float)((double)rand() * 0.1 * 0.000030517578125 + 0.1 + Car[iFinishingCarId_1].fTotalRaceTime))// Adjust finishing time based on track position
        {
          ++iDistanceCounter;
        }
      } else if (iLap_1 < iTotalLaps) {
        ++Car[iCarId].byLap;
      }
    }
  }
}

//-------------------------------------------------------------------------------------------------
//00037250
double getbankz(float fInput, int iChunkIdx, tData *pData)
{
  tData *pUseData; // edx
  tGroundPt *pGroundPt; // ebx
  double dCalcVal; // st7
  int iSelectedPointIdx; // esi
  int iCurrPointIdx; // ecx
  tVec3 *pPoint1; // ebx
  tGroundPt *pGroundPt2; // ecx
  float fPrevCalcVal; // [esp+0h] [ebp-20h]
  float fCurrCalcVal; // [esp+4h] [ebp-1Ch]

  // Default to localdata if pData is NULL
  pUseData = pData;
  if (!pData)
    pUseData = &localdata[iChunkIdx];

  // Get ground points for this chunk
  pGroundPt = &GroundPt[iChunkIdx];

  // Calculate first dot product
  dCalcVal = (pGroundPt->pointAy[0].fY + pUseData->pointAy[3].fY) * pUseData->pointAy[1].fY
    + (pGroundPt->pointAy[0].fX + pUseData->pointAy[3].fX) * pUseData->pointAy[0].fY
    + (pGroundPt->pointAy[0].fZ + pUseData->pointAy[3].fZ) * pUseData->pointAy[2].fY;

  iSelectedPointIdx = 4;                        // default to point 4 if no point found
  iCurrPointIdx = 1;                            // start checking from point 1
  pPoint1 = &pGroundPt->pointAy[1];             // point to second ground point
  fPrevCalcVal = (float)dCalcVal;

  // Loop through ground points to find appropriate interpolation segment
  while (1) {
    fCurrCalcVal = (pPoint1->fY + pUseData->pointAy[3].fY) * pUseData->pointAy[1].fY
      + (pPoint1->fX + pUseData->pointAy[3].fX) * pUseData->pointAy[0].fY
      + (pPoint1->fZ + pUseData->pointAy[3].fZ) * pUseData->pointAy[2].fY;

// If input is greater than current dot product, found segment
    if (fInput > (double)fCurrCalcVal)
      break;

    // Move to next point
    ++pPoint1;
    ++iCurrPointIdx;
    fPrevCalcVal = fCurrCalcVal;
    if (iCurrPointIdx >= 6)
      goto INTERPOLATION_CALC;
  }

  // Use the point before the one that exceeded input value
  iSelectedPointIdx = iCurrPointIdx - 1;
INTERPOLATION_CALC:
  // Calculate interpolated Z value using weighted average of two points
  // First term: contribution from point at selectedPointIndex
  // Second term: contribution from point at selectedPointIndex + 1
  pGroundPt2 = &GroundPt[iChunkIdx];
  return ((pGroundPt2->pointAy[iSelectedPointIdx].fY + pUseData->pointAy[3].fY) * pUseData->pointAy[1].fZ
        + (pGroundPt2->pointAy[iSelectedPointIdx].fX + pUseData->pointAy[3].fX) * pUseData->pointAy[0].fZ
        + (pGroundPt2->pointAy[iSelectedPointIdx].fZ + pUseData->pointAy[3].fZ) * pUseData->pointAy[2].fZ)
    * (fInput - fCurrCalcVal)                // weight for first point
    / (fPrevCalcVal - fCurrCalcVal)          // total range
    + ((pGroundPt2->pointAy[iSelectedPointIdx + 1].fY + pUseData->pointAy[3].fY) * pUseData->pointAy[1].fZ
     + (pGroundPt2->pointAy[iSelectedPointIdx + 1].fX + pUseData->pointAy[3].fX) * pUseData->pointAy[0].fZ
     + (pGroundPt2->pointAy[iSelectedPointIdx + 1].fZ + pUseData->pointAy[3].fZ) * pUseData->pointAy[2].fZ)
    * (fInput - fPrevCalcVal)                // weight for second point
    / (fCurrCalcVal - fPrevCalcVal);         // total range
}

//-------------------------------------------------------------------------------------------------
//000373A0
int calculate_aheadbehindtime(int a1, float *a2, float *a3)
{
  return 0;
  /*
  int result; // eax
  int v5; // esi
  int v6; // edi
  int v7; // esi
  int v8; // edi
  float v9; // eax
  double v10; // st7
  int v11; // esi
  int v12; // eax
  int v13; // ecx
  int v14; // esi
  float v15; // eax
  double v16; // st7
  float v17; // [esp+0h] [ebp-44h]
  float v18; // [esp+0h] [ebp-44h]
  float v19; // [esp+4h] [ebp-40h]
  float v20; // [esp+8h] [ebp-3Ch]
  float v21; // [esp+Ch] [ebp-38h]
  float v22; // [esp+10h] [ebp-34h]
  float v23; // [esp+1Ch] [ebp-28h]
  float v24; // [esp+20h] [ebp-24h]
  float v25; // [esp+24h] [ebp-20h]
  float v26; // [esp+28h] [ebp-1Ch]
  float v27; // [esp+2Ch] [ebp-18h]

  result = 308 * a1;
  if (Car_variable_23[result] > 0) {
    v5 = *(__int16 *)((char *)Car_variable_3 + result);
    if (v5 == -1)
      v5 = *(int *)((char *)Car_variable_51 + result);
    v27 = (float)(averagesectionlen * v5 + totaltrackdistance * Car_variable_24[308 * a1]);
    if (Car_variable_3[154 * a1] != -1)
      v27 = v27 + Car[77 * a1];
    if (Car_variable_32[308 * a1]) {
      v6 = nearcall_variable_4[(unsigned __int8)Car_variable_32[308 * a1]];
      if (Car_variable_23[308 * v6] > 0) {
        v7 = Car_variable_3[154 * v6];
        if (v7 == -1)
          v7 = Car_variable_51[77 * v6];
        v24 = (float)(averagesectionlen * v7 + totaltrackdistance * Car_variable_24[308 * v6]);
        if (Car_variable_3[154 * v6] != -1)
          v24 = v24 + Car[77 * v6];
        v8 = 77 * v6;
        v23 = fabs(v27 - v24);
        if (Car_variable_8[77 * a1] <= (double)Car_variable_8[v8])
          v9 = Car_variable_8[v8];
        else
          v9 = Car_variable_8[77 * a1];
        v21 = v9;
        if (v9 < (double)function_c_variable_5)
          v21 = 100.0;
        v19 = (float)totaltrackdistance;
        if (v23 >= (double)v19)
          v10 = v23 * function_c_variable_6 / v19;
        else
          v10 = v23 / v21 * function_c_variable_7;
        v17 = v10;
        *a2 = v17;
      } else {
        *a2 = -1.0;
      }
    } else {
      *a2 = -1.0;
    }
    result = (unsigned __int8)Car_variable_32[308 * a1];
    if (result == numcars - 1) {
      *a3 = -1.0;
    } else {
      v11 = carorder_variable_1[result];
      if (Car_variable_23[308 * v11] > 0) {
        v12 = Car_variable_3[154 * v11];
        if (v12 == -1)
          v12 = Car_variable_51[77 * v11];
        v26 = (float)(averagesectionlen * v12 + totaltrackdistance * Car_variable_24[308 * v11]);
        if (Car_variable_3[154 * v11] != -1)
          v26 = v26 + Car[77 * v11];
        v13 = 77 * a1;
        v14 = 77 * v11;
        v25 = fabs(v27 - v26);
        if (Car_variable_8[v13] <= (double)Car_variable_8[v14])
          v15 = Car_variable_8[v14];
        else
          v15 = Car_variable_8[v13];
        v22 = v15;
        if (v15 < (double)function_c_variable_5)
          v22 = 100.0;
        v20 = (float)totaltrackdistance;
        if (v25 >= (double)v20)
          v16 = v25 * function_c_variable_6 / v20;
        else
          v16 = v25 / v22 * function_c_variable_7;
        v18 = v16;
        result = LODWORD(v18);
        *a3 = v18;
      } else {
        *a3 = -1.0;
      }
    }
  } else {
    *a2 = -1.0;
    *a3 = -1.0;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//000376B0
void initnearcars()
{
  int iAICarsRemaining; // edi
  int iCarIndex; // ebx
  int iCurrentCarIdx; // ebx
  int iCarsPerGroup; // esi
  //int iGroupCarCount; // ecx
  //int iNearCallOffset; // edx
  //int iTempCarIdx; // eax
  int iGroupSize; // [esp+0h] [ebp-20h]
  //int iGroupOffset; // [esp+4h] [ebp-1Ch]

  memset(nearcall, 255, sizeof(nearcall));      // Initialize nearcall array with -1 (no car assigned)
  iAICarsRemaining = 0;                         // Count total number of AI-controlled cars
  if (numcars > 0) {
    iCarIndex = 0;
    do {                                           // Skip non-competitors and human-controlled cars
      if (!non_competitors[iCarIndex] && !human_control[iCarIndex])
        ++iAICarsRemaining;
      ++iCarIndex;
    } while (iCarIndex < numcars);
  }

  iCurrentCarIdx = 0;
  iGroupSize = 4;                                    // Start with group size 4, distribute AI cars across 4 groups
  for (int iGroup = 0; iGroup < 4; iGroup++)            // Loop through 4 nearcall groups: [0],[1],[2],[3]
  {
    iCarsPerGroup = iAICarsRemaining / iGroupSize; // Calculate how many cars to assign to current group
    for (int iSlot = 0; iSlot < iCarsPerGroup; iSlot++)
    {
      // Find next AI car (skip non-competitors and human players)
      while (non_competitors[iCurrentCarIdx] || human_control[iCurrentCarIdx])
      {
        iCurrentCarIdx++;
      }
      // Assign AI car index to current nearcall group slot
      nearcall[iGroup][iSlot] = iCurrentCarIdx;
      iCurrentCarIdx++;
    }
    iAICarsRemaining -= iCarsPerGroup;             // Subtract assigned cars from remaining count
    iGroupSize--;                                   // Decrease group size for uneven distribution
  }
  //iCurrentCarIdx = 0;
  //iGroupSize = 4;                               // Start with group size 4, distribute AI cars across 4 groups
  //for (iGroupOffset = 0; iGroupOffset != 64; iGroupOffset += 16)// Loop through 4 nearcall groups: [0],[1],[2],[3]
  //{
  //  iCarsPerGroup = iAICarsRemaining / iGroupSize;// Calculate how many cars to assign to current group
  //  iGroupCarCount = 0;
  //  if (iAICarsRemaining / iGroupSize > 0) {
  //    iNearCallOffset = iGroupOffset;
  //    do {                                         // Find next AI car (skip non-competitors and human players)
  //      for (iTempCarIdx = iCurrentCarIdx; non_competitors[iTempCarIdx] || human_control[iTempCarIdx]; ++iTempCarIdx)
  //        ++iCurrentCarIdx;
  //      ++iGroupCarCount;
  //      *(int *)((char *)nearcall[0] + iNearCallOffset) = iCurrentCarIdx;// Assign AI car index to current nearcall group slot
  //      iNearCallOffset += 4;
  //      ++iCurrentCarIdx;
  //    } while (iGroupCarCount < iCarsPerGroup);
  //  }
  //  iAICarsRemaining -= iCarsPerGroup;          // Subtract assigned cars from remaining count
  //  --iGroupSize;                               // Decrease group size for uneven distribution
  //}
  nearcarcheck = 0;                             // Reset near car check counter
}

//-------------------------------------------------------------------------------------------------
//00037780
void initpits()
{
  int iChunkIdx_1; // eax
  int iPitStopCount; // ecx
  int iStopsIdx; // ebx
  int iChunkIdx; // edx


  // Start from last track chunk and work backwards
  iChunkIdx_1 = TRAK_LEN - 1;
  iPitStopCount = 0;

  // Process all track segments
  if (TRAK_LEN - 1 >= 0) {
    iStopsIdx = 0;
    iChunkIdx = iChunkIdx_1;
    do {
      if ((TrakColour[iChunkIdx][TRAK_COLOUR_CENTER] & SURFACE_FLAG_PIT_2) != 0)
      {
        // store pit stop position
        stops[iStopsIdx] = iChunkIdx_1; // reference into stops

        ++iStopsIdx;
        ++iPitStopCount;
      }
      --iChunkIdx_1;
      --iChunkIdx;
    } while (iChunkIdx_1 >= 0);
  }
  numstops = iPitStopCount;
}

//-------------------------------------------------------------------------------------------------
//000377D0
void dodamage(tCar *pCar, float fDamage)
{
  tCarEngine *pCarEngine; // edi
  int iDriverIdx; // eax
  tCarSpray *pCarSpray; // ebx
  int iSprayIdx; // ecx
  int iRandValue1; // eax
  tCarSpray *pPlayerSpray; // ebx
  int i; // ecx
  int iRandValue2; // eax
  uint8 byStatusFlags; // dh
  int iPlayerType; // ebx
  int iDeadDriverIdx; // edi
  int iGameTrack; // eax
  int iCurrentDriverIdx; // ecx
  int iRacePosition; // ebx
  int j; // edx
  int iCurrentPos; // edx
  int iPosIdx; // eax
  int iCarOrderValue; // ebx
  int iFinishers; // edi
  int iHumanControl; // ebp
  int iCheckDriverIdx; // edx
  int iPlayer2DriverIdx; // ebp
  int iPlayerTypeCheck; // eax
  uint8 byCarDesignIdx; // bl
  int iFinalDriverIdx; // edi
  float fHealth; // [esp+0h] [ebp-20h]
  int iDamageIntensity; // [esp+4h] [ebp-1Ch]
  int iRacePosCount; // [esp+4h] [ebp-1Ch]

  pCarEngine = &CarEngines.engines[pCar->byCarDesignIdx];// Get car engine data based on car design
  fHealth = pCar->fHealth;
  iDriverIdx = pCar->iDriverIdx;
  if (!invulnerable[iDriverIdx] && !finished_car[iDriverIdx])// Check if car is vulnerable and not finished
  {                                             // Check if car is not already destroyed (status flag 4)
    if ((pCar->byStatusFlags & 4) == 0) {
      pCarSpray = CarSpray[pCar->iDriverIdx];
      if (fDamage > 0.55)                     // Handle visual spray effects for significant damage (> 0.55)
      {
        //_CHP();
        iDamageIntensity = (int)(fDamage * 16.0);
        pCar->byDamageToggle = 1 - pCar->byDamageToggle;
        iSprayIdx = 0;
        pCar->byDamageIntensity = iDamageIntensity;
        do {
          if (pCarSpray->iLifeTime > 0) {
            rand();
          } else {
            iRandValue1 = rand();
            if (GetHighOrderRand(12, iRandValue1) < iDamageIntensity)
              pCarSpray->iTimer = -1;
          }
          ++iSprayIdx;
          ++pCarSpray;
        } while (iSprayIdx < 32);               // Loop through all 32 spray effects for this car
        if (player_type == 2) {
          pPlayerSpray = 0;
          if (player1_car == pCar->iDriverIdx)
            pPlayerSpray = CarSpray[16];
          if (player2_car == pCar->iDriverIdx)
            pPlayerSpray = CarSpray[17];
          if (pPlayerSpray) {
            for (i = 0; i < 32; ++i) {
              if (pPlayerSpray->iLifeTime <= 0) {
                iRandValue2 = rand();
                if (GetHighOrderRand(12, iRandValue2) < iDamageIntensity)
                  pPlayerSpray->iTimer = -1;
              }
              ++pPlayerSpray;
            }
          }
        }
      }
    }
    pCar->fHealth = pCar->fHealth - fDamage * pCarEngine->fUnk24;// Apply damage to car health (modified by engine durability)
    if (pCar->fHealth < 1.0)                  // Handle car destruction when health drops below 1.0
    {
      byStatusFlags = pCar->byStatusFlags;
      pCar->fHealth = 0.0;
      if ((byStatusFlags & 4) == 0) {
        --pCar->byLives;
        iPlayerType = player_type;
        pCar->nDeathTimer = 18;
        // CHEAT_MODE_CLONES
        if (iPlayerType != 2 && (cheat_mode & CHEAT_MODE_CLONES) == 0) {
          iDeadDriverIdx = pCar->iDriverIdx;
          if (player1_car != iDeadDriverIdx && pCar->byCarDesignIdx == Car[player1_car].byCarDesignIdx && !human_control[iDeadDriverIdx] && pCar->byCarDesignIdx <= 7u) {
            // SOUND_SAMPLE_ARIEL
            speechsample(pCar->byCarDesignIdx + SOUND_SAMPLE_ARIEL, 20000, 18, player1_car + 17152);
            // SOUND_SAMPLE_TGONE
            speechsample(SOUND_SAMPLE_TGONE, 20000, 0, player1_car);
          }
        }
        iGameTrack = game_track;
        pCar->nChangeMateCooldown = 1080;
        ++RecordKills[iGameTrack];
        iCurrentDriverIdx = pCar->iDriverIdx;
        if (iCurrentDriverIdx == ViewType[0]) {
          if (iCurrentDriverIdx == player1_car)
            DeathView[0] = SelectedView[0];
          if (SelectedView[0] != 1 && SelectedView[0] != 3) {
            SelectedView[0] = 1;
            select_view(0);
            initcarview(ViewType[0], 0);
          }
        }
        if (iCurrentDriverIdx == ViewType[1]) {
          if (iCurrentDriverIdx == player2_car)
            DeathView[1] = SelectedView[1];
          if (SelectedView[1] != 1 && SelectedView[1] != 3) {
            SelectedView[1] = 1;
            select_view(1);
            initcarview(ViewType[1], 1);
          }
        }
        if (!pCar->byLives && !finished_car[iCurrentDriverIdx]) {
          iRacePosition = pCar->byRacePosition; // Update race positions when car is eliminated
          ++Destroyed;
          iRacePosCount = racers - 1;
          for (j = racers - 1; finished_car[carorder[j]]; --j)
            --iRacePosCount;
          iCurrentPos = iRacePosition;
          finished_car[iCurrentDriverIdx] = -1;
          if (iRacePosition < iRacePosCount) {
            iPosIdx = iRacePosition;
            do {
              iCarOrderValue = carorder[iPosIdx + 1];
              carorder[iPosIdx] = iCarOrderValue;
              Car[iCarOrderValue].byRacePosition = iCurrentPos++;
              ++iPosIdx;
            } while (iCurrentPos < iRacePosCount);
          }
          carorder[iRacePosCount] = iCurrentDriverIdx;
          iFinishers = finishers;
          pCar->byRacePosition = iRacePosCount;
          iHumanControl = human_control[iCurrentDriverIdx];
          finishers = iFinishers + 1;
          if (iHumanControl)
            ++human_finishers;
          if ((iCurrentDriverIdx == player1_car || iCurrentDriverIdx == player2_car) && (char)pCar->byLives > 0)
            // SOUND_SAMPLE_RUBBISH
            speechsample(SOUND_SAMPLE_RUBBISH, 0x8000, 18, iCurrentDriverIdx);
        }
        iCheckDriverIdx = pCar->iDriverIdx;
        if (player1_car == iCheckDriverIdx || player2_car == iCheckDriverIdx) {
          // SOUND_SAMPLE_FATALITY
          speechsample(SOUND_SAMPLE_FATALITY, 0x8000, 18, pCar->iDriverIdx);// Play death sound effects for human players
          if (!pCar->byLives) {
            // SOUND_SAMPLE_0LEFT
            speechsample(SOUND_SAMPLE_0LEFT, 0x8000, 18, pCar->iDriverIdx);
            // SOUND_SAMPLE_RACEOVER
            speechsample(SOUND_SAMPLE_RACEOVER, 0x8000, 18, pCar->iDriverIdx);
          }
        }
        if (pCar->byDamageSourceTimer)
          ++Car[pCar->byAttacker].byKills;      // Track kills for the attacking car
        if (pCar->byDamageSourceTimer && pCar->byAttacker == player1_car) {
          speechsample(SOUND_SAMPLE_GOTONE, 0x8000, 18, player1_car);
          Victim = pCar->iDriverIdx;
        } else if (player1_car != pCar->iDriverIdx) {
          if ((char)pCar->byLives <= 0)
            sprintf(buffer, "%s %s", &language_buffer[1984], driver_names[pCar->iDriverIdx]);
          else
            sprintf(buffer, "%s %s", &language_buffer[1920], driver_names[pCar->iDriverIdx]);
          small_zoom(buffer);
          if (pCar->byDamageSourceTimer) {
            sprintf(buffer, "%s %s", &language_buffer[2176], driver_names[pCar->byAttacker]);
            subzoom(buffer);
          }
        }
        if (player_type == 2) {
          if (pCar->byDamageSourceTimer && pCar->byAttacker == player2_car) {
            // SOUND_SAMPLE_GOTONE
            speechsample(SOUND_SAMPLE_GOTONE, 0x8000, 18, player2_car);
            Victim = pCar->iDriverIdx;
          } else {
            iPlayer2DriverIdx = pCar->iDriverIdx;
            if (player2_car != iPlayer2DriverIdx) {
              if ((char)pCar->byLives <= 0)
                sprintf(buffer, "%s %s", &language_buffer[1984], driver_names[iPlayer2DriverIdx]);
              else
                sprintf(buffer, "%s %s", &language_buffer[1920], driver_names[iPlayer2DriverIdx]);
              small_zoom(buffer);
              if (pCar->byDamageSourceTimer) {
                sprintf(buffer, "%s %s", &language_buffer[2176], driver_names[pCar->byAttacker]);
                subzoom(buffer);
              }
            }
          }
        }
      }
      pCar->byStatusFlags |= 4u;
    }
    if (pCar->fHealth < 30.0 && fHealth >= 30.0)// Handle transition from healthy to critical health (30.0 threshold)
    {
      iPlayerTypeCheck = player_type;
      pCar->nChangeMateCooldown = 1080;
      // CHEAT_MODE_CLONES
      if (iPlayerTypeCheck != 2 && (cheat_mode & CHEAT_MODE_CLONES) == 0 && player1_car != pCar->iDriverIdx) {
        byCarDesignIdx = pCar->byCarDesignIdx;
        if (byCarDesignIdx == Car[player1_car].byCarDesignIdx && !human_control[pCar->iDriverIdx] && byCarDesignIdx <= 7u) {
          // SOUND_SAMPLE_ARIEL
          speechsample(byCarDesignIdx + SOUND_SAMPLE_ARIEL, 20000, 18, player1_car + 17408);
          // SOUND_SAMPLE_TDAMAGE
          speechsample(SOUND_SAMPLE_TDAMAGE, 20000, 0, player1_car);
        }
      }
    }
  }
  iFinalDriverIdx = pCar->iDriverIdx;
  if ((player1_car == iFinalDriverIdx || player2_car == iFinalDriverIdx) && pCar->fHealth < 30.0 && fHealth >= 30.0 && pCar->byCarDesignIdx <= 7u)
    // SOUND_SAMPLE_BLOWTIME
    speechsample(SOUND_SAMPLE_BLOWTIME, 20000, 18, pCar->iDriverIdx);// Play critical health warning sound for human players
}

//-------------------------------------------------------------------------------------------------
//00037F00
void doviewtend(tCar *pCar, int iFrameDelta, int iViewIdx)
{
  int iSelectedView; // edx
  unsigned int iControlType; // eax
  double dChasePullCrash; // st7
  double dTempPullCrash; // st7
  int iViewIndex; // ebx
  double dTempPullCrash2; // st7
  double dChasePullNormal; // st7
  double dTempPullNormal; // st7
  int iViewIndex2; // ebx
  double dTempPullNormal2; // st7
  double dChasePullDefault; // st7
  double dTempPullDefault; // st7
  int iViewIndex3; // ebx
  double dTempPullDefault2; // st7
  double dHighSpeedCrashPull; // st7
  double dTempHighSpeedCrash; // st7
  int iViewIndex4; // ebx
  double dTempHighSpeedCrash2; // st7
  double dHighSpeedNormalPull; // st7
  double dTempHighSpeedNormal; // st7
  int iViewIndex5; // ebx
  double dTempHighSpeedNormal2; // st7
  int iHighSpeedPullIncrement; // [esp+4h] [ebp-50h]
  int iTargetPullNormal; // [esp+8h] [ebp-4Ch]
  int iTargetPullHighSpeed; // [esp+Ch] [ebp-48h]
  int iTargetPullCrash; // [esp+10h] [ebp-44h]
  int iTargetPullDefault; // [esp+14h] [ebp-40h]
  int iTargetPullHighSpeedCrash; // [esp+18h] [ebp-3Ch]
  float fTargetPullHighSpeed; // [esp+1Ch] [ebp-38h]
  float fTargetPullNormal; // [esp+20h] [ebp-34h]
  float fTargetPullHighSpeedCrash; // [esp+24h] [ebp-30h]
  float fTargetPullDefault; // [esp+28h] [ebp-2Ch]
  int iPullSpeed; // [esp+2Ch] [ebp-28h]
  float fTargetPullDefaultFloat; // [esp+30h] [ebp-24h]
  float fTargetPullCrashFloat; // [esp+34h] [ebp-20h]
  float fTargetPullNormalFloat; // [esp+38h] [ebp-1Ch]
  float fTargetPullCrashLimit; // [esp+3Ch] [ebp-18h]
  float fTargetPullHighSpeedLimit; // [esp+40h] [ebp-14h]
  float fTargetPullHighSpeedCrashLimit; // [esp+44h] [ebp-10h]

  iSelectedView = SelectedView[iViewIdx];       // Get the selected view type for this view index (a3: 0=player1 view, 1=player2 view)
  if (iSelectedView == 1 || iSelectedView == 3)// Only process chase views (view types 1 and 3)
  {
    iControlType = pCar->iControlType;          // Get car control type to determine pull behavior
    iPullSpeed = 40 * iFrameDelta;              // Calculate pull speed increment (40 units per frame) * frame delta
    if (iControlType < 2) {                                           // Control type 0: Autopilot/Default car behavior
      if (!iControlType) {
        dChasePullDefault = viewdata[chaseview[iViewIdx]].fChasePullDefault;// Get default chase pull distance from view data
        //_CHP();
        iTargetPullDefault = (int)dChasePullDefault;
        fTargetPullDefault = (float)dChasePullDefault;
        if (PULLZ[iViewIdx] > (double)fTargetPullDefault) {
          dTempPullDefault = PULLZ[iViewIdx] - (double)iPullSpeed;
          PULLZ[iViewIdx] = (float)dTempPullDefault;
          if (dTempPullDefault < fTargetPullDefault)
            PULLZ[iViewIdx] = fTargetPullDefault;
        }
        fTargetPullDefaultFloat = (float)iTargetPullDefault;
        iViewIndex3 = iViewIdx;
        if (PULLZ[iViewIndex3] < (double)fTargetPullDefaultFloat) {
          dTempPullDefault2 = (double)(40 * iFrameDelta) + PULLZ[iViewIndex3];
          PULLZ[iViewIndex3] = (float)dTempPullDefault2;
          if (dTempPullDefault2 > fTargetPullDefaultFloat)
            PULLZ[iViewIndex3] = fTargetPullDefaultFloat;
        }
      }
    } else if (iControlType <= 3) {                                           // Check if car is stunned/crashed to use crash pull values
      if (pCar->iStunned) {
        dChasePullCrash = viewdata[chaseview[iViewIdx]].fChasePullCrash;// Use crash pull distance for stunned cars
        //_CHP();
        iTargetPullCrash = (int)dChasePullCrash;
        fTargetPullCrashFloat = (float)dChasePullCrash;
        if (PULLZ[iViewIdx] > (double)fTargetPullCrashFloat) {
          dTempPullCrash = PULLZ[iViewIdx] - (double)iPullSpeed;
          PULLZ[iViewIdx] = (float)dTempPullCrash;
          if (dTempPullCrash < fTargetPullCrashFloat)
            PULLZ[iViewIdx] = fTargetPullCrashFloat;
        }
        fTargetPullCrashLimit = (float)iTargetPullCrash;
        iViewIndex = iViewIdx;
        if (PULLZ[iViewIndex] < (double)fTargetPullCrashLimit) {
          dTempPullCrash2 = (double)(40 * iFrameDelta) + PULLZ[iViewIndex];
          PULLZ[iViewIndex] = (float)dTempPullCrash2;
          if (dTempPullCrash2 > fTargetPullCrashLimit)
            PULLZ[iViewIndex] = fTargetPullCrashLimit;
        }
      } else {
        dChasePullNormal = viewdata[chaseview[iViewIdx]].fChasePullNormal;// Use normal pull distance for active cars
        //_CHP();
        iTargetPullNormal = (int)dChasePullNormal;
        fTargetPullNormal = (float)dChasePullNormal;
        if (PULLZ[iViewIdx] > (double)fTargetPullNormal) {
          dTempPullNormal = PULLZ[iViewIdx] - (double)iPullSpeed;
          PULLZ[iViewIdx] = (float)dTempPullNormal;
          if (dTempPullNormal < fTargetPullNormal)
            PULLZ[iViewIdx] = fTargetPullNormal;
        }
        fTargetPullNormalFloat = (float)iTargetPullNormal;
        iViewIndex2 = iViewIdx;
        if (PULLZ[iViewIndex2] < (double)fTargetPullNormalFloat) {
          dTempPullNormal2 = (double)(40 * iFrameDelta) + PULLZ[iViewIndex2];
          PULLZ[iViewIndex2] = (float)dTempPullNormal2;
          if (dTempPullNormal2 > fTargetPullNormalFloat)
            PULLZ[iViewIndex2] = fTargetPullNormalFloat;
        }
      }
    } else if (iControlType == 1002)            // Control type 1002: High-speed mode with modified pull distances
    {
      iHighSpeedPullIncrement = 160 * iFrameDelta;// Use faster pull speed for high-speed mode (160 units per frame)
      if (pCar->iStunned) {
        dHighSpeedCrashPull = viewdata[chaseview[iViewIdx]].fChasePullCrash + -400.0;// High-speed crash: use crash pull distance minus 400 units
        //_CHP();
        iTargetPullHighSpeedCrash = (int)dHighSpeedCrashPull;
        fTargetPullHighSpeedCrash = (float)dHighSpeedCrashPull;
        if (PULLZ[iViewIdx] > (double)fTargetPullHighSpeedCrash) {
          dTempHighSpeedCrash = PULLZ[iViewIdx] - (double)iHighSpeedPullIncrement;
          PULLZ[iViewIdx] = (float)dTempHighSpeedCrash;
          if (dTempHighSpeedCrash < fTargetPullHighSpeedCrash)
            PULLZ[iViewIdx] = fTargetPullHighSpeedCrash;
        }
        fTargetPullHighSpeedCrashLimit = (float)iTargetPullHighSpeedCrash;
        iViewIndex4 = iViewIdx;
        if (PULLZ[iViewIndex4] < (double)fTargetPullHighSpeedCrashLimit) {
          dTempHighSpeedCrash2 = (double)(40 * iFrameDelta) + PULLZ[iViewIndex4];
          PULLZ[iViewIndex4] = (float)dTempHighSpeedCrash2;
          if (dTempHighSpeedCrash2 > fTargetPullHighSpeedCrashLimit)
            PULLZ[iViewIndex4] = fTargetPullHighSpeedCrashLimit;
        }
      } else {
        dHighSpeedNormalPull = viewdata[chaseview[iViewIdx]].fChasePullNormal + 400.0;// High-speed normal: use normal pull distance plus 400 units
        //_CHP();
        iTargetPullHighSpeed = (int)dHighSpeedNormalPull;
        fTargetPullHighSpeed = (float)dHighSpeedNormalPull;
        if (PULLZ[iViewIdx] > (double)fTargetPullHighSpeed) {
          dTempHighSpeedNormal = PULLZ[iViewIdx] - (double)iHighSpeedPullIncrement;
          PULLZ[iViewIdx] = (float)dTempHighSpeedNormal;
          if (dTempHighSpeedNormal < fTargetPullHighSpeed)
            PULLZ[iViewIdx] = fTargetPullHighSpeed;
        }
        fTargetPullHighSpeedLimit = (float)iTargetPullHighSpeed;
        iViewIndex5 = iViewIdx;
        if (PULLZ[iViewIndex5] < (double)fTargetPullHighSpeedLimit) {
          dTempHighSpeedNormal2 = (double)(40 * iFrameDelta) + PULLZ[iViewIndex5];
          PULLZ[iViewIndex5] = (float)dTempHighSpeedNormal2;
          if (dTempHighSpeedNormal2 > fTargetPullHighSpeedLimit)
            PULLZ[iViewIndex5] = fTargetPullHighSpeedLimit;
        }
      }
    }
  }
}

//-------------------------------------------------------------------------------------------------
//00038330
int changemateto(int result, int a2)
{
  return 0;
  /*
  int v2; // ecx
  int v4; // esi
  int v5; // edi
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // esi

  v2 = result;
  if ((result & 1) != 0)
    v4 = result - 1;
  else
    v4 = result + 1;
  if (Car_variable_23[308 * v4] > 0 && !human_control[v4]) {
    result = Car_variable_45[77 * v4];
    v5 = a2 + 57;
    if (a2 == result) {
      if (player_type != 2 && v2 == (__int16)player1_car && (cheat_mode & 0x4000) == 0)
        return speechsample(a2 + 57, 20000, 18, v2);
    } else {
      v6 = rand(result);
      result = (v6 - (__CFSHL__(v6 >> 31, 13) + (v6 >> 31 << 13))) >> 13;
      if (result == 3 || Car_variable_57[154 * v4]) {
        if (player_type == 2
          || (result = (__int16)player1_car, v2 != (__int16)player1_car)
          || (cheat_mode & 0x4000) != 0) {
          result = rand(result);
        } else {
          v7 = (__int16)player1_car + ((Car_variable_45[77 * v4] + 61) << 8);
          v8 = rand((__int16)player1_car);
          speechsample(((v8 - (__CFSHL__(v8 >> 31, 14) + (v8 >> 31 << 14))) >> 14) + 65, 20000, 18, v7);
          result = speechsample(Car_variable_45[77 * v4] + 61, 20000, 0, (__int16)player1_car);
        }
        v9 = 154 * v4;
        if (!Car_variable_57[v9])
          Car_variable_57[v9] = 1080;
      } else {
        Car_variable_45[77 * v4] = a2;
        if (player_type != 2 && v2 == (__int16)player1_car) {
          result = cheat_mode;
          if ((cheat_mode & 0x4000) == 0)
            result = speechsample(v5, 20000, 18, v2);
        }
        Car_variable_57[154 * v4] = 1080;
      }
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//000384C0
// valid when car movement is not blocked by i.e. fence separating track from run-off area
// top-down view, driving up (= start is down, end is up):
/******************************************************************
 *      region=2       f      region=1     f       region=0       *
 *                     e                   e                      *
 *  left-run-off-area  n       track       n  right-run-off-area  *
 *                     c                   c                      *
 *                     e                   e                      *
 ***************  -halfWidth     0     halfWidth  ****************/
bool linevalid(int iChunkIdx, float fStartCoord, float fEndCoord)
{
  tData *pData; // ecx
  tTrackInfo *pTrackInfo; // edx
  unsigned int uiStartRegion; // esi
  unsigned int uiEndRegion; // ebx
  bool iValidResult; // ecx
  int iRightSurfaceType; // edi
  bool iRightBarierPresent; // ebp
  int iLeftSurfaceType; // edi
  bool iLeftBarierPresent; // edi
  unsigned int iNotRendered; // eax

  pData = &localdata[iChunkIdx];
  pTrackInfo = &TrackInfo[iChunkIdx];

  // Classify start coordinate relative to track boundaries
  if (fStartCoord <= (double)pData->fTrackHalfWidth) {
    if (-pData->fTrackHalfWidth <= fStartCoord)
      uiStartRegion = 1;                        // inside track boundaries
    else
      uiStartRegion = 2;                        // outside track (negative side)
  } else {
    uiStartRegion = 0;                          // outside track (positive side)
  }
  if (fEndCoord <= (double)pData->fTrackHalfWidth) {
    if (-pData->fTrackHalfWidth <= fEndCoord)
      uiEndRegion = 1;                          // inside track boundaries
    else
      uiEndRegion = 2;                          // outside track (negative side)
  } else {
    uiEndRegion = 0;                            // outside track (positive side)
  }

  // If both points are in the same region, line doesn't cross track boundaries
  iValidResult = true;
  if (uiStartRegion == uiEndRegion)
    return iValidResult;

  // Check surface types that block visibility
  iRightSurfaceType = pTrackInfo->iLeftSurfaceType;
  if (iRightSurfaceType == 5 || iRightSurfaceType == 6 || iRightSurfaceType == 9)
    iRightBarierPresent = true;                   // surface blocks visibility
  else
    iRightBarierPresent = false;

  iLeftSurfaceType = pTrackInfo->iRightSurfaceType;
  if (iLeftSurfaceType == 5 || iLeftSurfaceType == 6 || iLeftSurfaceType == 9)
    iLeftBarierPresent = true;                  // surface blocks visibility
  else
    iLeftBarierPresent = false;

  // Check if invisible
  iNotRendered = abs(TrakColour[iChunkIdx][TRAK_COLOUR_CENTER]) & 0x20000;// SURFACE_FLAG_SKIP_RENDER

  // Determine line validity based on region crossing and surface blocking
  if (!uiStartRegion)                         // start outside positive side
  {
    if (!uiEndRegion)                         // both outside positive (shouldn't happen)
      return iValidResult;
    if (uiEndRegion > 1)                      // end outside negative side
    {
      // Line crosses entire track, blocked if any barriers present and track rendered
      if (!iRightBarierPresent && !iLeftBarierPresent && !iNotRendered)
        return iValidResult;                  // valid if no barriers and rendered
      return 0;
    }
    goto CHECK_LEFT_SURFACE;                    // Start outside positive, end inside track
  }

  if (uiStartRegion <= 1)                     // start inside track
  {
    if (uiEndRegion) {
      if (uiEndRegion != 2 || !iLeftBarierPresent)
        return iValidResult;                  // valid if crossing to unblocked left surface
      return false;
    }
  CHECK_LEFT_SURFACE:
      // start on track, end outside positive - check right surface
    if (iRightBarierPresent)
      return false;                                 // valid if right surface missing
    return iValidResult;
  }

  // Start=2 = outside negative side
  if (!uiEndRegion)                           // end outside positive
  {
    // Line crosses entire track, blocked if no barriers and not rendered
    if (!iRightBarierPresent && !iLeftBarierPresent && !iNotRendered)
      return iValidResult;                    // valid if no barriers and rendered
    return false;
  }

  if (uiEndRegion != 1)                       // end not inside track
    return iValidResult;

  // Start outside negative, end inside - check left surface
  if (iLeftBarierPresent)
    return false;                                   // valid if left surface missing
  return iValidResult;
}

//-------------------------------------------------------------------------------------------------
//00038640
void analysefalloff(tCar *pCar)
{
  /*
  int v2; // ecx
  double v3; // st7
  char *v4; // esi
  int v5; // eax
  float *v6; // edi
  unsigned int v7; // ecx
  __int64 v8; // rax
  __int64 v9; // rax
  double v10; // st7
  int v11; // edx
  int v12; // ebp
  double v13; // st7
  __int16 v14; // fps
  _BOOL1 v15; // c0
  char v16; // c2
  _BOOL1 v17; // c3
  int v18; // eax
  long double v19; // st7
  int v20; // eax
  double v21; // st7
  __int64 v22; // rax
  __int64 v23; // rax
  double v24; // st7
  int v25; // edx
  int v26; // edx
  double v27; // st7
  __int16 v28; // fps
  _BOOL1 v29; // c0
  char v30; // c2
  _BOOL1 v31; // c3
  int v32; // eax
  long double v33; // st7
  int v34; // eax
  double v35; // st7
  int v36; // eax
  __int64 v37; // rax
  int v38; // eax
  int v39; // edx
  double v40; // st7
  __int16 v41; // fps
  _BOOL1 v42; // c0
  char v43; // c2
  _BOOL1 v44; // c3
  int v45; // eax
  long double v46; // st7
  int v47; // eax
  double v48; // st7
  __int64 v49; // rax
  int v50; // eax
  int v51; // edx
  double v52; // st7
  __int16 v53; // fps
  _BOOL1 v54; // c0
  char v55; // c2
  _BOOL1 v56; // c3
  int v57; // eax
  long double v58; // st7
  int v59; // eax
  double v60; // st7
  float v61; // [esp+0h] [ebp-34h]
  int v62; // [esp+0h] [ebp-34h]
  int v63; // [esp+0h] [ebp-34h]
  float v64; // [esp+4h] [ebp-30h]
  float v65; // [esp+8h] [ebp-2Ch]
  float v66; // [esp+Ch] [ebp-28h]
  float v67; // [esp+10h] [ebp-24h]
  float v68; // [esp+14h] [ebp-20h]
  float v69; // [esp+18h] [ebp-1Ch]
  float v70; // [esp+18h] [ebp-1Ch]

  v2 = *(__int16 *)(a1 + 12);
  v3 = *(float *)(a1 + 4);
  v4 = (char *)&localdata + 128 * v2;
  v5 = 36 * v2;
  *(_DWORD *)(a1 + 200) = 0;
  v6 = (float *)&TrackInfo[9 * v2];
  if (v3 <= *((float *)v4 + 13)) {
    if (-*((float *)v4 + 13) <= *(float *)(a1 + 4))
      v7 = 1;
    else
      v7 = 2;
  } else {
    v7 = 0;
  }
  if (!v7) {
    v10 = *((float *)v4 + 13) + *v6;
    v11 = -1;
    goto LABEL_11;
  }
  if (v7 > 1) {
    v9 = *((int *)&TrakColour_variable_3 + 6 * *(__int16 *)(a1 + 12));
    v5 = (HIDWORD(v9) ^ v9) - HIDWORD(v9);
    v10 = -*((float *)v4 + 13);
    v11 = v5 & 0x20000;
  LABEL_11:
    v69 = v10;
    goto LABEL_12;
  }
  v8 = *((int *)&TrakColour + 6 * *(__int16 *)(a1 + 12));
  HIDWORD(v8) = (HIDWORD(v8) ^ v8) - HIDWORD(v8);
  v5 = *((_DWORD *)v4 + 13);
  v11 = HIDWORD(v8) & 0x20000;
  v69 = *(float *)&v5;
LABEL_12:
  if (v11 && v69 < *(float *)(a1 + 84) * function_c_variable_14 + *(float *)(a1 + 4)) {
    v12 = *(_DWORD *)(a1 + 64);
    v13 = *(float *)(a1 + 24) * tsin[v12];
    v67 = v13;
    if (v13 < function_c_variable_15) {
      v15 = v67 > 0.0;
      v16 = 0;
      v17 = 0.0 == v67;
      LOWORD(v5) = v14;
      if (v67 >= 0.0) {
        v68 = *(float *)(a1 + 24) * tcos[v12];
        v18 = getangle(v5, v11, v68, 1109393408);
        v19 = v68 * v68 + function_c_variable_16;
        *(_DWORD *)(a1 + 64) = v18;
        *(float *)(a1 + 24) = sqrt(v19);
      }
    }
    v20 = *(__int16 *)(a1 + 20);
    v21 = tcos[v20] * function_c_variable_17 + (double)*(int *)(a1 + 200);
    _CHP(v20, v11);
    *(_DWORD *)(a1 + 200) = (int)v21;
  }
  if (v7) {
    if (v7 <= 1) {
      v23 = *((int *)&TrakColour_variable_7 + 6 * *(__int16 *)(a1 + 12));
      v5 = (HIDWORD(v23) ^ v23) - HIDWORD(v23);
      v24 = -*((float *)v4 + 13);
      v25 = v5 & 0x20000;
    } else {
      v24 = -*((float *)v4 + 13) - v6[2];
      v25 = -1;
    }
    v70 = v24;
  } else {
    v22 = *((int *)&TrakColour_variable_3 + 6 * *(__int16 *)(a1 + 12));
    HIDWORD(v22) = (HIDWORD(v22) ^ v22) - HIDWORD(v22);
    v5 = *((_DWORD *)v4 + 13);
    v25 = HIDWORD(v22) & 0x20000;
    v70 = *(float *)&v5;
  }
  if (v25 && v70 > *(float *)(a1 + 4) - *(float *)(a1 + 84) * function_c_variable_14) {
    v26 = *(_DWORD *)(a1 + 64);
    v27 = *(float *)(a1 + 24) * tsin[v26];
    v64 = v27;
    if (v27 > function_c_variable_18) {
      v29 = v64 > 0.0;
      v30 = 0;
      v31 = 0.0 == v64;
      LOWORD(v5) = v28;
      if (v64 <= 0.0) {
        v61 = *(float *)(a1 + 24) * tcos[v26];
        v32 = getangle(v5, v26 * 4, v61, -1038090240);
        v33 = v61 * v61 + function_c_variable_16;
        *(_DWORD *)(a1 + 64) = v32;
        *(float *)(a1 + 24) = sqrt(v33);
      }
    }
    v34 = *(__int16 *)(a1 + 20);
    v35 = (double)*(int *)(a1 + 200) - tcos[v34] * function_c_variable_17;
    _CHP(v34, v26 * 4);
    *(_DWORD *)(a1 + 200) = (int)v35;
  }
  v36 = *(__int16 *)(a1 + 12) - 1;
  if (v36 < 0)
    v36 = TRAK_LEN - 1;
  v37 = *((int *)&TrakColour + 6 * v36 + v7);
  v38 = (HIDWORD(v37) ^ v37) - HIDWORD(v37);
  if ((v38 & 0x20000) != 0 && -*((float *)v4 + 12) > *(float *)a1 - *(float *)(a1 + 88) * function_c_variable_14) {
    v39 = *(_DWORD *)(a1 + 64);
    v40 = *(float *)(a1 + 24) * tcos[v39];
    v66 = v40;
    if (v40 > function_c_variable_18) {
      v42 = v66 > 0.0;
      v43 = 0;
      v44 = 0.0 == v66;
      LOWORD(v38) = v41;
      if (v66 <= 0.0) {
        *(float *)&v62 = *(float *)(a1 + 24) * tsin[v39];
        v45 = getangle(v38, v39 * 4, -40.0, v62);
        v46 = *(float *)&v62 * *(float *)&v62 + function_c_variable_16;
        *(_DWORD *)(a1 + 64) = v45;
        *(float *)(a1 + 24) = sqrt(v46);
      }
    }
    v47 = *(__int16 *)(a1 + 20);
    v48 = tsin[v47] * function_c_variable_17 + (double)*(int *)(a1 + 200);
    _CHP(v47, v39 * 4);
    *(_DWORD *)(a1 + 200) = (int)v48;
  }
  v49 = *((int *)&TrakColour + 6 * *(__int16 *)(a1 + 12) + v7 + 6);
  v50 = (HIDWORD(v49) ^ v49) - HIDWORD(v49);
  if ((v50 & 0x20000) != 0 && *((float *)v4 + 12) < *(float *)(a1 + 88) * function_c_variable_14 + *(float *)a1) {
    v51 = *(_DWORD *)(a1 + 64);
    v52 = *(float *)(a1 + 24) * tcos[v51];
    v65 = v52;
    if (v52 < function_c_variable_15) {
      v54 = v65 > 0.0;
      v55 = 0;
      v56 = 0.0 == v65;
      LOWORD(v50) = v53;
      if (v65 >= 0.0) {
        *(float *)&v63 = *(float *)(a1 + 24) * tsin[v51];
        v57 = getangle(v50, v51 * 4, 40.0, v63);
        v58 = *(float *)&v63 * *(float *)&v63 + function_c_variable_16;
        *(_DWORD *)(a1 + 64) = v57;
        *(float *)(a1 + 24) = sqrt(v58);
      }
    }
    v59 = *(__int16 *)(a1 + 20);
    v60 = (double)*(int *)(a1 + 200) - tsin[v59] * function_c_variable_17;
    _CHP(v59, v51 * 4);
    *(_DWORD *)(a1 + 200) = (int)v60;
  }*/
}

//-------------------------------------------------------------------------------------------------
//00038A80
int showmap(uint8 *a1, int a2)
{
  return 0;/*
  int v2; // esi
  int v4; // edx
  int v5; // eax
  float *v6; // edx
  int v7; // eax
  float *v8; // eax
  double v9; // st5
  double v10; // st7
  double v11; // st6
  double v12; // st5
  double v13; // st7
  int v14; // eax
  int v15; // eax
  int v16; // ebx
  int v17; // edi
  float *v18; // eax
  double v19; // st5
  double v20; // st7
  double v21; // st6
  double v22; // st5
  int v23; // eax
  double v24; // st7
  int v25; // eax
  int v26; // edx
  int v27; // edx
  int v28; // edi
  int v29; // ebx
  float *v30; // eax
  double v31; // st7
  double v32; // st6
  double v33; // st5
  int v34; // eax
  double v35; // st7
  int v36; // eax
  int v37; // eax
  int v38; // esi
  int v39; // edx
  int v40; // eax
  int i; // ebx
  float *v42; // eax
  float *v43; // edi
  int v44; // edx
  float *v45; // edx
  double v46; // st5
  double v47; // st7
  double v48; // st6
  double v49; // st5
  double v50; // st7
  int v51; // ecx
  int v52; // edx
  int v53; // eax
  int v54; // edx
  int v55; // edx
  _BYTE *v56; // ebx
  int v57; // edx
  int result; // eax
  _BYTE *v59; // eax
  float v60; // [esp+0h] [ebp-9Ch]
  int v61; // [esp+4h] [ebp-98h]
  int v62; // [esp+1Ch] [ebp-80h]
  int v63; // [esp+20h] [ebp-7Ch]
  int v64; // [esp+24h] [ebp-78h]
  int v65; // [esp+34h] [ebp-68h]
  int v66; // [esp+3Ch] [ebp-60h]
  int v68; // [esp+44h] [ebp-58h]
  float v69; // [esp+48h] [ebp-54h]
  float v70; // [esp+4Ch] [ebp-50h]
  float v71; // [esp+50h] [ebp-4Ch]
  float v72; // [esp+54h] [ebp-48h]
  int v73; // [esp+58h] [ebp-44h]
  int v74; // [esp+5Ch] [ebp-40h]
  int v75; // [esp+6Ch] [ebp-30h]
  int v76; // [esp+70h] [ebp-2Ch]
  int v77; // [esp+74h] [ebp-28h]
  int v78; // [esp+78h] [ebp-24h]
  float *v79; // [esp+7Ch] [ebp-20h]
  int v80; // [esp+80h] [ebp-1Ch]
  int v81; // [esp+84h] [ebp-18h]

  v2 = winw;
  v70 = *(float *)&cur_mapsize;
  if ((cheat_mode & 0x1000) != 0)
    v70 = *(float *)&cur_mapsize * function_c_variable_19;
  v4 = Car_variable_4[154 * a2];
  v5 = v4 + 1;
  if (v4 + 1 == TRAK_LEN)
    v5 ^= TRAK_LEN;
  v6 = (float *)((char *)&localdata + 128 * v4);
  v7 = v5 << 7;
  *(float *)&v61 = v6[10] - *(float *)((char *)&localdata + v7 + 40);
  v60 = v6[9] - *(float *)((char *)&localdata + v7 + 36);
  v62 = (4096 - (unsigned __int16)getangle(v7, 4096, v60, v61)) & 0x3FFF;
  v8 = (float *)((char *)&localdata + 128 * Car_variable_4[154 * a2]);
  v9 = 1.0 / v70;
  v10 = (v8[9] - localdata_variable_1) * v9;
  v11 = (v8[10] - localdata_variable_2) * v9;
  v79 = v8;
  v12 = v10 * tcos[v62] - v11 * tsin[v62];
  _CHP(v8, 4 * v62);
  v13 = v10 * tsin[v62] + v11 * tcos[v62];
  _CHP(scr_size * ((int)v12 + 38), 4 * v62);
  v15 = v14 >> 6;
  v63 = v15;
  v16 = (scr_size * (160 - (int)v13)) >> 6;
  v17 = cur_mapsect;
  v64 = v16;
  while (1) {
    v26 = v15 + 1;
    if (v17 >= TRAK_LEN)
      break;
    v18 = (float *)((char *)&localdata + 128 * v17);
    v19 = 1.0 / v70;
    v20 = (v79[9] - v18[9]) * v19;
    v21 = (v79[10] - v18[10]) * v19;
    v22 = v20 * tcos[v62] - v21 * tsin[v62];
    _CHP(4 * v62, v26);
    v24 = v20 * *(float *)((char *)tsin + v23) + v21 * *(float *)((char *)tcos + v23);
    _CHP(scr_size * ((int)v22 + 38), v26);
    v75 = v25 >> 6;
    v76 = (scr_size * (160 - (int)v24)) >> 6;
    compout(v26, (v25 >> 6) + 1, v16, v17, v2, v76, 112);
    v15 = v75;
    v16 = v76;
    v17 += cur_mapsect;
  }
  compout(v26, v63 + 1, v16, v17, v2, v64, 112);
  v27 = v63;
  v28 = cur_mapsect;
  v29 = v64;
  if (cur_mapsect < TRAK_LEN) {
    v69 = 1.0 / v70;
    do {
      v30 = (float *)((char *)&localdata + 128 * v28);
      v31 = (v79[9] - v30[9]) * v69;
      v32 = (v79[10] - v30[10]) * v69;
      v33 = v31 * tcos[v62] - v32 * tsin[v62];
      _CHP(4 * v62, v27);
      v35 = v31 * *(float *)((char *)tsin + v34) + v32 * *(float *)((char *)tcos + v34);
      _CHP(scr_size * ((int)v33 + 38), v27);
      v77 = v36 >> 6;
      v78 = (scr_size * (160 - (int)v35)) >> 6;
      if ((TrakColour_variable_1[12 * v28] & 0x100) != 0
        || (TrakColour_variable_5[12 * v28] & 0x100) != 0
        || (TrakColour_variable_8[12 * v28] & 0x100) != 0) {
        compout(v27, v77, v29, v28, v2, v78, 205);
      } else {
        compout(v27, v77, v29, v28, v2, v78, 131);
      }
      v27 = v77;
      v28 += cur_mapsect;
      v29 = v78;
    } while (v28 < TRAK_LEN);
  }
  v37 = 12 * (TRAK_LEN - 1);
  if ((TrakColour_variable_1[v37] & 0x100) != 0
    || (TrakColour_variable_5[v37] & 0x100) != 0
    || (TrakColour_variable_8[v37] & 0x100) != 0) {
    compout(v27, v63, v29, v64, v2, v64, 205);
  } else {
    compout(v27, v63, v29, v28, v2, v64, 131);
  }
  v73 = 0;
  v38 = winw;
  v39 = v64 - 1;
  do {
    v40 = v63 - 1;
    for (i = 0; i < 3; ++i) {
      if (v40 >= 0 && v40 < v38 && v39 >= 0 && v39 < winh)
        *(_BYTE *)(v40 + v38 * v39 + a1) = -117;
      ++v40;
    }
    ++v39;
    ++v73;
  } while (v73 < 3);
  v74 = 0;
  if (numcars > 0) {
    v42 = Car;
    do {
      v43 = v42;
      if (*((char *)v42 + 103) > 0) {
        v44 = *((__int16 *)v42 + 6);
        if (v44 == -1) {
          v71 = *v42;
          v72 = v42[1];
        } else {
          v45 = (float *)((char *)&localdata + 128 * v44);
          v71 = *v45 * *v42 - v45[9];
          v72 = v45[3] * *v42 - v45[10];
        }
        v46 = 1.0 / v70;
        v47 = (v71 + v79[9]) * v46;
        v48 = (v72 + v79[10]) * v46;
        v49 = v47 * tcos[v62] - v48 * tsin[v62];
        _CHP(v42, 4 * v62);
        v50 = v47 * tsin[v62] + v48 * tcos[v62];
        v51 = scr_size;
        v52 = scr_size * ((int)v49 + 38);
        _CHP(v53, v52);
        v81 = v52 >> 6;
        v80 = (v51 * (160 - (int)v50)) >> 6;
        v54 = *((_DWORD *)v43 + 8);
        if (v54 == a2) {
          v55 = a2 ^ v54;
          LOBYTE(v55) = *((_BYTE *)v43 + 102);
          v68 = team_col[v55];
          v66 = v81;
          v65 = (v51 * (160 - (int)v50)) >> 6;
        } else if (v81 > 0 && v38 - 1 > v81 && v80 > 0 && winh - 1 > v80) {
          v56 = (_BYTE *)(a1 + v81 + v38 * v80);
          v57 = team_col[*((unsigned __int8 *)v43 + 102)];
          if (*((_BYTE *)v43 + 130) || (frames & 8) != 0) {
            *(v56 - 1) = v57;
            *v56 = v57;
            v56[1] = v57;
            v56[-v38] = v57;
            v56[v38] = v57;
          }
        }
      }
      v42 += 77;
      ++v74;
    } while (v74 < numcars);
  }
  result = 308 * a2;
  if (Car_variable_23[308 * a2] > 0 && (Car_variable_32[308 * a2] || (frames & 8) != 0)) {
    v59 = (_BYTE *)(v66 + a1 + v38 * v65);
    *(v59 - 1) = v68;
    *(v59 - 2) = v68;
    *v59 = v68;
    v59[1] = v68;
    v59[2] = v68;
    v59[-v38] = v68;
    v59[-2 * v38] = v68;
    v59[v38] = v68;
    result = (int)&v59[2 * v38];
    *(_BYTE *)result = v68;
  }
  winw = v38;
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//000390D0
int firework_display()
{
  return 0;/*
  int result; // eax
  int j; // eax
  int i; // ebp
  _BYTE *v3; // ebx
  int v4; // eax
  int v5; // esi
  __int64 v6; // rax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // esi
  int v13; // eax
  __int64 v14; // rax
  double v15; // st7
  __int64 v16; // rax
  double v17; // st6
  double v18; // st7
  int v19; // edx
  int v20; // ecx
  double v21; // st6
  double v22; // st7
  int v23; // [esp+Ch] [ebp-2Ch]
  int v24; // [esp+Ch] [ebp-2Ch]
  float v25; // [esp+10h] [ebp-28h]
  int v26; // [esp+14h] [ebp-24h]
  float v27; // [esp+18h] [ebp-20h]
  float v28; // [esp+1Ch] [ebp-1Ch]

  updates[0] = 0;
  for (result = readptr; readptr != writeptr; result = readptr) {
    if (!paused)
      ++updates[0];
    dozoomstuff(0);
    if (readptr >= 0) {
      for (i = 0; i != 25344; i += 1408) {
        v3 = &CarSpray[i];
        LOBYTE(j) = CarSpray[i + 40];
        if ((_BYTE)j) {
          if ((unsigned __int8)j <= 1u) {
            j = *((_DWORD *)v3 + 7) - 1;
            *((_DWORD *)v3 + 7) = j;
            if (j > 0) {
              qmemcpy((char *)&CarSpray_variable_4 + i, (char *)&CarSpray_variable_3 + i, 0x2Cu);
              qmemcpy((char *)&CarSpray_variable_3 + i, (char *)&CarSpray_variable_2 + i, 0x2Cu);
              qmemcpy((char *)&CarSpray_variable_2 + i, (char *)&CarSpray_variable_1 + i, 0x2Cu);
              qmemcpy((char *)&CarSpray_variable_1 + i, &CarSpray[i], 0x2Cu);
              v17 = *((float *)v3 + 4) + function_c_variable_21;
              *((float *)v3 + 4) = v17;
              *((float *)v3 + 1) = v17 + *((float *)v3 + 1);
              v18 = *((float *)v3 + 3) + *(float *)v3;
              *((_DWORD *)v3 + 9) = 143;
              *(float *)v3 = v18;
            } else {
              sfxsample(6, 0x8000, v3);
              v27 = *(float *)v3;
              v26 = *((_DWORD *)v3 + 1);
              v28 = *((float *)v3 + 3);
              v25 = *((float *)v3 + 4);
              v10 = rand(LODWORD(v25));
              v11 = 0;
              v12 = firework_colours[(12 * v10 - (__CFSHL__((12 * v10) >> 31, 15) + ((12 * v10) >> 31 << 15))) >> 15];
              do {
                v3[40] = 2;
                *((_DWORD *)v3 + 9) = v12;
                *(float *)v3 = v27;
                *((_DWORD *)v3 + 1) = v26;
                v13 = rand(v26);
                v14 = rand(((v13 << 14) - (__CFSHL__(v13 << 14 >> 31, 15) + (v13 << 14 >> 31 << 15))) >> 15);
                v15 = (double)(int)v14 * function_c_variable_24 * function_c_variable_20;
                *((float *)v3 + 3) = v15 * tcos[HIDWORD(v14)] + v28;
                *((float *)v3 + 4) = v15 * tsin[HIDWORD(v14)] + v25;
                v16 = rand(v14);
                v3 += 44;
                j = ((int)(v16 * HIDWORD(v16)
                           - (__CFSHL__(((int)v16 * HIDWORD(v16)) >> 31, 15)
                              + (((int)v16 * HIDWORD(v16)) >> 31 << 15))) >> 15)
                  + 36;
                ++v11;
                *((_DWORD *)v3 - 4) = j;
              } while (v11 < 32);
            }
          } else if ((_BYTE)j == 2) {
            v19 = 0;
            for (j = 0; j < 32; ++j) {
              v20 = *((_DWORD *)v3 + 7);
              if (v20 > 0) {
                v21 = *((float *)v3 + 4) + function_c_variable_21;
                *((float *)v3 + 4) = v21;
                *((float *)v3 + 1) = v21 + *((float *)v3 + 1);
                v22 = *((float *)v3 + 3) + *(float *)v3;
                *((_DWORD *)v3 + 7) = v20 - 1;
                ++v19;
                *(float *)v3 = v22;
              }
              v3 += 44;
            }
            if (!v19) {
              j = (int)&CarSpray[i];
              do {
                j += 176;
                *(_BYTE *)(j - 136) = 0;
                *(_DWORD *)(j - 144) = 0;
                *(_DWORD *)(j - 168) = 0;
                *(_DWORD *)(j - 140) = 143;
                *(_BYTE *)(j - 92) = 0;
                *(_DWORD *)(j - 100) = 0;
                *(_DWORD *)(j - 124) = 0;
                *(_DWORD *)(j - 96) = 143;
                *(_BYTE *)(j - 48) = 0;
                *(_DWORD *)(j - 56) = 0;
                *(_DWORD *)(j - 80) = 0;
                *(_DWORD *)(j - 52) = 143;
                *(_BYTE *)(j - 4) = 0;
                *(_DWORD *)(j - 12) = 0;
                *(_DWORD *)(j - 36) = 0;
                v19 += 4;
                *(_DWORD *)(j - 8) = 143;
              } while (v19 < 32);
            }
          }
        } else if ((*((_DWORD *)v3 + 2) & 0x7FFFFFFF) != 0) {
          v5 = *((_DWORD *)v3 + 8) - 1;
          *((_DWORD *)v3 + 8) = v5;
          if (v5 < 0) {
            v6 = rand(winw / 3);
            v23 = 2 * winw / 3
              - ((int)(v6 * HIDWORD(v6)
                       - (__CFSHL__(((int)v6 * HIDWORD(v6)) >> 31, 15)
                          + (((int)v6 * HIDWORD(v6)) >> 31 << 15))) >> 15);
            *(float *)v3 = (float)v23;
            *((float *)v3 + 1) = (float)winh;
            v7 = rand(v23);
            v8 = (4 * v7 - (__CFSHL__((4 * v7) >> 31, 15) + ((4 * v7) >> 31 << 15))) >> 15;
            *((float *)v3 + 3) = (float)(2 - v8);
            v24 = rand(v8);
            *((float *)v3 + 4) = function_c_variable_23 - (double)v24 * function_c_variable_22 * function_c_variable_20;
            v9 = rand(v24);
            *((_DWORD *)v3 + 9) = 143;
            v3[40] = 1;
            j = ((48 * v9 - (__CFSHL__((48 * v9) >> 31, 15) + ((48 * v9) >> 31 << 15))) >> 15) + 18;
            *((_DWORD *)v3 + 7) = j;
          }
        } else {
          *((_DWORD *)v3 + 2) = -1082130432;
          v4 = rand(j);
          j = (36 * v4 - (__CFSHL__((36 * v4) >> 31, 15) + ((36 * v4) >> 31 << 15))) >> 15;
          *((_DWORD *)v3 + 8) = j;
        }
      }
    }
    analysespeechsamples(j);
    readptr = ((_WORD)readptr + 1) & 0x1FF;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

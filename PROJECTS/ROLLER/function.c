#include "function.h"
#include "loadtrak.h"
#include "control.h"
#include <stdlib.h>
#include <math.h>
//-------------------------------------------------------------------------------------------------

int invulnerable[16];     //00149EB0

//-------------------------------------------------------------------------------------------------

void finish_race()
{
  /*
  int v0; // edi
  int v1; // esi
  int v2; // edx
  int v3; // eax
  int v4; // edx
  int m; // eax
  unsigned int v6; // ecx
  int v7; // eax
  unsigned int v8; // ebx
  int v9; // ebp
  int v10; // ecx
  int v11; // eax
  int v12; // ebx
  __int64 v13; // rax
  int v14; // ebp
  int v15; // ebx
  __int64 v16; // rax
  int v17; // edx
  int j; // ecx
  int k; // eax
  int v20; // eax
  int v21; // ebx
  int v22; // ebx
  int v23; // ebx
  int v24; // ebp
  int v25; // esi
  int v26; // eax
  int i; // ebx
  int v28; // edx
  int v29; // ebx
  int v30; // edx
  int v31; // ecx
  int v32; // ebx
  int v33; // ebx
  int v34; // ecx
  double v35; // st7
  double v36; // st7
  __int16 v37; // fps
  double v38; // st7
  _BOOL1 v39; // c0
  char v40; // c2
  _BOOL1 v41; // c3
  int v42; // edi
  int v43; // ebx
  char v44; // cl
  unsigned int v45; // edx
  double v46; // st7
  double v47; // st7
  double v48; // st6
  int v49; // [esp+8h] [ebp-3Ch]
  float v50; // [esp+10h] [ebp-34h]
  float v51; // [esp+14h] [ebp-30h]
  int v52; // [esp+18h] [ebp-2Ch]
  int v53; // [esp+1Ch] [ebp-28h]
  int v54; // [esp+1Ch] [ebp-28h]
  int v55; // [esp+1Ch] [ebp-28h]
  int v56; // [esp+1Ch] [ebp-28h]
  int v57; // [esp+1Ch] [ebp-28h]
  int v58; // [esp+1Ch] [ebp-28h]
  int v59; // [esp+1Ch] [ebp-28h]
  int v60; // [esp+1Ch] [ebp-28h]
  int v61; // [esp+1Ch] [ebp-28h]
  float v62; // [esp+20h] [ebp-24h]
  float v63; // [esp+24h] [ebp-20h]
  float v64; // [esp+28h] [ebp-1Ch]

  if (player_type == 1)
    srand(random_seed);
  v0 = 0;
  v53 = 0;
  v1 = Car_variable_31[308 * carorder[0]];
  if (racers > 0) {
    v2 = 0;
    do {
      v3 = carorder[v2];
      if (!human_control[v3] && Car_variable_23[308 * v3] > 0)
        ++v0;
      ++v2;
      ++v53;
    } while (v2 < racers);
  }
  if (v1 <= NoOfLaps) {
    LODWORD(v16) = NoOfLaps - 2;
    if (NoOfLaps - 2 < 1)
      LODWORD(v16) = 1;
    if (v1 >= (int)v16) {
      v59 = 0;
      if (racers > 0) {
        v24 = 0;
        v25 = 0;
        v52 = racers - 1;
        do {
          if (human_control[v24] && !finished_car[v24]) {
            v49 = (unsigned __int8)Car_variable_32[v25];
            v26 = v52;
            for (i = v52; ; --i) {
              v28 = carorder[i];
              if (!finished_car[v28])
                break;
              --v26;
            }
            finished_car[v28] = -1;
            v29 = v49;
            if (v26 > v49) {
              v30 = v49;
              do {
                v31 = carorder_variable_1[v30];
                carorder[v30] = v31;
                Car_variable_32[308 * v31] = v29++;
                ++v30;
              } while (v29 < v26);
            }
            carorder[v26] = v59;
            Car_variable_23[v25] = -1;
            Car_variable_32[v25] = v59;
          }
          ++v24;
          LODWORD(v16) = v59 + 1;
          v25 += 308;
          v59 = v16;
        } while ((int)v16 < racers);
      }
    } else if (game_type == 1 && Race > 0) {
      v17 = 0;
      v55 = 0;
      if (v0 > 0) {
        for (j = 0; j < v0; ++j) {
          for (k = v17; ; ++k) {
            ++v17;
            if (!human_control[champorder[k]])
              break;
          }
          v20 = champorder[k];
          carorder[j] = v20;
          finished_car[v20] = -1;
          LODWORD(v16) = ++v55;
        }
      }
      HIDWORD(v16) = 0;
      v56 = 0;
      if (players > 0) {
        v21 = v0;
        do {
          LODWORD(v16) = 4 * HIDWORD(v16);
          while (!*(int *)((char *)human_control + v16)) {
            LODWORD(v16) = v16 + 4;
            ++HIDWORD(v16);
          }
          if (!*(int *)((char *)finished_car + v16)) {
            Car_variable_23[308 * HIDWORD(v16)] = -1;
            carorder[v21] = HIDWORD(v16);
            *(int *)((char *)finished_car + v16) = -1;
          }
          ++HIDWORD(v16);
          LODWORD(v16) = v56 + 1;
          ++v21;
          v56 = v16;
        } while ((int)v16 < players);
      }
    } else {
      LODWORD(v16) = 0;
      v57 = 0;
      if (v0 > 0) {
        v22 = 0;
        while (1) {
          LODWORD(v16) = rand(v16);
          LODWORD(v16) = (int)(v16 * numcars
                             - (__CFSHL__(((int)v16 * numcars) >> 31, 15)
                                + (((int)v16 * numcars) >> 31 << 15))) >> 15;
          if ((_DWORD)v16 == numcars)
            LODWORD(v16) = numcars - 1;
          HIDWORD(v16) = 4 * v16;
          if (!human_control[(_DWORD)v16] && !finished_car[(_DWORD)v16]) {
            carorder[v22++] = v16;
            LODWORD(v16) = v57 + 1;
            *(int *)((char *)finished_car + HIDWORD(v16)) = -1;
            ++v57;
            if (v22 >= v0)
              break;
          }
        }
      }
      HIDWORD(v16) = 0;
      v58 = 0;
      if (players > 0) {
        v23 = v0;
        do {
          LODWORD(v16) = 4 * HIDWORD(v16);
          while (!*(int *)((char *)human_control + v16)) {
            LODWORD(v16) = v16 + 4;
            ++HIDWORD(v16);
          }
          if (!*(int *)((char *)finished_car + v16)) {
            Car_variable_23[308 * HIDWORD(v16)] = -1;
            carorder[v23] = HIDWORD(v16);
            *(int *)((char *)finished_car + v16) = -1;
          }
          ++HIDWORD(v16);
          LODWORD(v16) = v58 + 1;
          ++v23;
          v58 = v16;
        } while ((int)v16 < players);
      }
    }
    v60 = 0;
    if (numcars > 0) {
      v32 = 4 * numcars;
      v16 = 0LL;
      do {
        if (!*(int *)((char *)human_control + HIDWORD(v16))) {
          *(int *)((char *)Car_variable_55 + v16) = 0;
          *(int *)((char *)Car_variable_53 + v16) = 1566444395;
        }
        HIDWORD(v16) += 4;
        LODWORD(v16) = v16 + 308;
        ++v60;
      } while (SHIDWORD(v16) < v32);
    }
    v61 = 0;
    if (NoOfLaps > 0) {
      do {
        v33 = 0;
        if (v0 > 0) {
          v34 = 0;
          do {
            v16 = rand(v16);
            v35 = (double)(int)v16 * function_c_variable_2;
            LODWORD(v16) = 308 * HIDWORD(v16);
            v63 = v35 + function_c_variable_3;
            if (v33)
              v36 = Car_variable_52[77 * nearcall_variable_4[v34]];
            else
              v36 = RecordLaps[game_track];
            Car_variable_52[77 * HIDWORD(v16)] = v36 + v63;
            HIDWORD(v16) *= 308;
            *(float *)((char *)Car_variable_55 + HIDWORD(v16)) = *(float *)((char *)Car_variable_52 + HIDWORD(v16))
              + *(float *)((char *)Car_variable_55 + HIDWORD(v16));
            v38 = *(float *)((char *)Car_variable_53 + HIDWORD(v16));
            v39 = v38 < *(float *)((char *)Car_variable_52 + HIDWORD(v16));
            v40 = 0;
            v41 = v38 == *(float *)((char *)Car_variable_52 + HIDWORD(v16));
            LOWORD(v16) = v37;
            if (v38 > *(float *)((char *)Car_variable_52 + HIDWORD(v16))) {
              *(float *)&v16 = *(float *)((char *)Car_variable_52 + HIDWORD(v16));
              *(int *)((char *)Car_variable_53 + HIDWORD(v16)) = v16;
            }
            ++v33;
            ++v34;
          } while (v33 < v0);
        }
        LODWORD(v16) = v61 + 1;
        v61 = v16;
      } while ((int)v16 < NoOfLaps);
    }
    v50 = *(float *)&Car_variable_55[77 * carorder[0]];
    v62 = RecordLaps[game_track];
    if (v62 < (double)function_c_variable_1)
      v62 = 10.0;
    if (v0 > 0) {
      v42 = 4 * v0;
      v43 = 0;
      v44 = NoOfLaps + 1;
      do {
        v45 = 308 * carorder[v43 / 4u];
        v46 = *(float *)&Car_variable_55[v45 / 4] - v50;
        Car_variable_31[v45] = v44;
        if (v46 > v62) {
          v64 = v46;
          v47 = v64;
          v48 = v62;
          do {
            v47 = v47 - v48;
            --Car_variable_31[v45];
          } while (v47 > v48);
        }
        v43 += 4;
      } while (v43 < v42);
    }
  } else {
    while (finishers < racers) {
      v4 = 0;
      for (m = 0; finished_car[carorder[m]]; ++m)
        ++v4;
      v6 = 154 * nearcall_variable_4[v4];
      v51 = *(float *)&Car_variable_55[v6 / 2];
      v7 = carorder[v4];
      v8 = 308 * v7;
      v9 = NoOfLaps;
      v10 = Car_variable_4[v6];
      finished_car[v7] = -1;
      v54 = v7;
      v11 = Car_variable_31[308 * v7];
      ++finishers;
      if (v11 == v9) {
        LOBYTE(v11) = NoOfLaps + 1;
        Car_variable_31[v8] = NoOfLaps + 1;
        v12 = Car_variable_4[v8 / 2];
        if (v10 < v12) {
          v14 = TRAK_LEN;
          LODWORD(v13) = (int)(12 * rand(v11)) / 0x8000;
          v10 += v14;
        } else {
          LODWORD(v13) = (int)(12 * rand(v11)) / 0x8000;
        }
        v15 = v10 - v12 + v13;
        *(float *)&Car_variable_55[77 * v54] = v51 + function_c_variable_3;
        if (v15 > 0) {
          do {
            v13 = rand(v13);
            *(float *)&Car_variable_55[77 * v54] = (double)(int)v13 * function_c_variable_4 * function_c_variable_2
              + function_c_variable_4
              + *(float *)&Car_variable_55[77 * v54];
          } while (HIDWORD(v13) + 1 < v15);
        }
      } else if (v11 < v9) {
        ++Car_variable_31[v8];
      }
    }
  }*/
}

//-------------------------------------------------------------------------------------------------

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

int initnearcars()
{
  return 0;
  /*
  int v0; // edi
  int v1; // ebx
  int v2; // ebx
  int v3; // esi
  int v4; // ecx
  int v5; // edx
  int j; // eax
  int result; // eax
  int v8; // [esp+0h] [ebp-20h]
  int i; // [esp+4h] [ebp-1Ch]

  memset(nearcall, 255, 64);
  v0 = 0;
  if (numcars > 0) {
    v1 = 0;
    do {
      if (!non_competitors[v1] && !human_control[v1])
        ++v0;
      ++v1;
    } while (v1 < numcars);
  }
  v2 = 0;
  v8 = 4;
  for (i = 0; i != 64; i += 16) {
    v3 = v0 / v8;
    v4 = 0;
    if (v0 / v8 > 0) {
      v5 = i;
      do {
        for (j = v2; non_competitors[j] || human_control[j]; ++j)
          ++v2;
        ++v4;
        *(int *)((char *)nearcall + v5) = v2;
        v5 += 4;
        ++v2;
      } while (v4 < v3);
    }
    v0 -= v3;
    --v8;
  }
  result = 0;
  nearcarcheck = 0;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

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
      if ((TrakColour[iChunkIdx].uiSurfType2 & SURFACE_FLAG_PIT_2) != 0)
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

void dodamage(int a1, float a2)
{
  /*
  int *v6; // edi
  int v7; // eax
  int v8; // edx
  __int16 v9; // fps
  _BYTE *v10; // ebx
  _BOOL1 v11; // c0
  char v12; // c2
  _BOOL1 v13; // c3
  int v14; // eax
  double v15; // st7
  int v16; // eax
  int v17; // ecx
  int v18; // eax
  _DWORD *v19; // ebx
  int v20; // eax
  int i; // ecx
  int v22; // eax
  char v23; // dh
  int v24; // ebx
  int v25; // edi
  int v26; // eax
  int v27; // ecx
  int v28; // ebx
  int j; // edx
  int v30; // edx
  int v31; // eax
  int v32; // ebx
  int v33; // edi
  int v34; // ebp
  int v35; // edx
  int v36; // ebp
  int v37; // eax
  unsigned __int8 v38; // bl
  int v39; // edi
  float v40; // [esp+0h] [ebp-20h]
  int v41; // [esp+4h] [ebp-1Ch]
  int v42; // [esp+4h] [ebp-1Ch]

  v6 = &CarEngines[28 * *(unsigned __int8 *)(a1 + 102)];
  v40 = *(float *)(a1 + 28);
  v7 = *(_DWORD *)(a1 + 32);
  if (!invulnerable[v7] && !finished_car[v7]) {
    if ((*(_BYTE *)(a1 + 131) & 4) == 0) {
      v8 = *(_DWORD *)(a1 + 32);
      v14 = 1408 * v8;
      v10 = &CarSpray[1408 * v8];
      v11 = a2 < function_c_variable_9;
      v12 = 0;
      v13 = a2 == function_c_variable_9;
      LOWORD(v14) = v9;
      if (a2 > function_c_variable_9) {
        v15 = a2 * function_c_variable_10;
        _CHP(v14, v8);
        v41 = (int)v15;
        *(_BYTE *)(a1 + 273) = 1 - *(_BYTE *)(a1 + 273);
        LOBYTE(v16) = (int)v15;
        v17 = 0;
        *(_BYTE *)(a1 + 275) = v16;
        do {
          if (*((int *)v10 + 7) > 0) {
            v16 = rand(v16);
          } else {
            v18 = rand(v16);
            v16 = (12 * v18 - (__CFSHL__((12 * v18) >> 31, 15) + ((12 * v18) >> 31 << 15))) >> 15;
            if (v16 < v41)
              *((_DWORD *)v10 + 8) = -1;
          }
          ++v17;
          v10 += 44;
        } while (v17 < 32);
        if (player_type == 2) {
          v19 = 0;
          if ((__int16)player1_car == *(_DWORD *)(a1 + 32))
            v19 = &CarSpray_variable_13;
          v20 = player2_car;
          if (player2_car == *(_DWORD *)(a1 + 32))
            v19 = &CarSpray_variable_22;
          if (v19) {
            for (i = 0; i < 32; ++i) {
              if ((int)v19[7] <= 0) {
                v22 = rand(v20);
                v20 = (12 * v22 - (__CFSHL__((12 * v22) >> 31, 15) + ((12 * v22) >> 31 << 15))) >> 15;
                if (v20 < v41)
                  v19[8] = -1;
              }
              v19 += 11;
            }
          }
        }
      }
    }
    *(float *)(a1 + 28) = *(float *)(a1 + 28) - a2 * *((float *)v6 + 26);
    if (*(float *)(a1 + 28) < 1.0) {
      v23 = *(_BYTE *)(a1 + 131);
      *(_DWORD *)(a1 + 28) = 0;
      if ((v23 & 4) == 0) {
        --*(_BYTE *)(a1 + 103);
        v24 = player_type;
        *(_WORD *)(a1 + 100) = 18;
        if (v24 != 2 && (cheat_mode & 0x4000) == 0) {
          v25 = *(_DWORD *)(a1 + 32);
          if ((__int16)player1_car != v25
            && *(_BYTE *)(a1 + 102) == Car_variable_22[308 * (__int16)player1_car]
            && !human_control[v25]
            && *(_BYTE *)(a1 + 102) <= 7u) {
            speechsample(*(unsigned __int8 *)(a1 + 102) + 71, 20000, 18, (__int16)player1_car + 17152);
            speechsample(67, 20000, 0, (__int16)player1_car);
          }
        }
        v26 = game_track;
        *(_WORD *)(a1 + 238) = 1080;
        ++RecordKills[v26];
        v27 = *(_DWORD *)(a1 + 32);
        if (v27 == ViewType[0]) {
          if (v27 == (__int16)player1_car)
            DeathView = SelectedView[0];
          if (SelectedView[0] != 1 && SelectedView[0] != 3) {
            SelectedView[0] = 1;
            select_view(0);
            initcarview(ViewType[0], 0);
          }
        }
        if (v27 == ViewType_variable_1) {
          if (v27 == player2_car)
            DeathView_variable_1[0] = SelectedView_variable_1;
          if (SelectedView_variable_1 != 1 && SelectedView_variable_1 != 3) {
            SelectedView_variable_1 = 1;
            select_view(1);
            initcarview(ViewType_variable_1, 1);
          }
        }
        if (!*(_BYTE *)(a1 + 103) && !finished_car[v27]) {
          v28 = *(unsigned __int8 *)(a1 + 130);
          ++Destroyed;
          v42 = racers - 1;
          for (j = racers - 1; finished_car[carorder[j]]; --j)
            --v42;
          v30 = v28;
          finished_car[v27] = -1;
          if (v28 < v42) {
            v31 = v28;
            do {
              v32 = carorder_variable_1[v31];
              carorder[v31] = v32;
              Car_variable_32[308 * v32] = v30++;
              ++v31;
            } while (v30 < v42);
          }
          carorder[v42] = v27;
          v33 = finishers;
          *(_BYTE *)(a1 + 130) = v42;
          v34 = human_control[v27];
          finishers = v33 + 1;
          if (v34)
            ++human_finishers;
          if ((v27 == (__int16)player1_car || v27 == player2_car) && *(char *)(a1 + 103) > 0)
            speechsample(24, 0x8000, 18, v27);
        }
        v35 = *(_DWORD *)(a1 + 32);
        if ((__int16)player1_car == v35 || player2_car == v35) {
          speechsample(14, 0x8000, 18, *(_DWORD *)(a1 + 32));
          if (!*(_BYTE *)(a1 + 103)) {
            speechsample(45, 0x8000, 18, *(_DWORD *)(a1 + 32));
            speechsample(30, 0x8000, 18, *(_DWORD *)(a1 + 32));
          }
        }
        if (*(_BYTE *)(a1 + 187))
          ++Car_variable_42[308 * *(unsigned __int8 *)(a1 + 185)];
        if (*(_BYTE *)(a1 + 187) && *(unsigned __int8 *)(a1 + 185) == (_WORD)player1_car) {
          speechsample(21, 0x8000, 18, (__int16)player1_car);
          Victim = *(_DWORD *)(a1 + 32);
        } else if ((__int16)player1_car != *(_DWORD *)(a1 + 32)) {
          if (*(char *)(a1 + 103) <= 0)
            sprintf(&buffer, "%s %s", language_buffer_variable_31, &driver_names[9 * *(_DWORD *)(a1 + 32)]);
          else
            sprintf(&buffer, "%s %s", language_buffer_variable_30, &driver_names[9 * *(_DWORD *)(a1 + 32)]);
          small_zoom(&buffer);
          if (*(_BYTE *)(a1 + 187)) {
            sprintf(&buffer, "%s %s", language_buffer_variable_34, &driver_names[9 * *(unsigned __int8 *)(a1 + 185)]);
            subzoom(&buffer);
          }
        }
        if (player_type == 2) {
          if (*(_BYTE *)(a1 + 187) && *(unsigned __int8 *)(a1 + 185) == player2_car) {
            speechsample(21, 0x8000, 18, player2_car);
            Victim = *(_DWORD *)(a1 + 32);
          } else {
            v36 = *(_DWORD *)(a1 + 32);
            if (player2_car != v36) {
              if (*(char *)(a1 + 103) <= 0)
                sprintf(&buffer, "%s %s", language_buffer_variable_31, &driver_names[9 * v36]);
              else
                sprintf(&buffer, "%s %s", language_buffer_variable_30, &driver_names[9 * v36]);
              small_zoom(&buffer);
              if (*(_BYTE *)(a1 + 187)) {
                sprintf(
                  &buffer,
                  "%s %s",
                  language_buffer_variable_34,
                  &driver_names[9 * *(unsigned __int8 *)(a1 + 185)]);
                subzoom(&buffer);
              }
            }
          }
        }
      }
      *(_BYTE *)(a1 + 131) |= 4u;
    }
    if (*(float *)(a1 + 28) < (double)function_c_variable_11 && v40 >= (double)function_c_variable_11) {
      v37 = player_type;
      *(_WORD *)(a1 + 238) = 1080;
      if (v37 != 2 && (cheat_mode & 0x4000) == 0 && (__int16)player1_car != *(_DWORD *)(a1 + 32)) {
        v38 = *(_BYTE *)(a1 + 102);
        if (v38 == Car_variable_22[308 * (__int16)player1_car] && !human_control[*(_DWORD *)(a1 + 32)] && v38 <= 7u) {
          speechsample(v38 + 71, 20000, 18, (__int16)player1_car + 17408);
          speechsample(68, 20000, 0, (__int16)player1_car);
        }
      }
    }
  }
  v39 = *(_DWORD *)(a1 + 32);
  if (((__int16)player1_car == v39 || player2_car == v39)
    && *(float *)(a1 + 28) < (double)function_c_variable_11
    && v40 >= (double)function_c_variable_11
    && *(_BYTE *)(a1 + 102) <= 7u) {
    speechsample(27, 20000, 18, *(_DWORD *)(a1 + 32));
  }*/
}

//-------------------------------------------------------------------------------------------------

void doviewtend(int a1, int a2, int a3)
{/*
  int v5; // edx
  unsigned int v6; // eax
  int v7; // edx
  int v8; // esi
  double v9; // st7
  double v10; // st7
  int v11; // ebx
  double v12; // st7
  int v13; // esi
  double v14; // st7
  double v15; // st7
  int v16; // ebx
  double v17; // st7
  int v18; // esi
  double v19; // st7
  double v20; // st7
  int v21; // ebx
  double v22; // st7
  int v23; // esi
  double v24; // st7
  double v25; // st7
  int v26; // ebx
  double v27; // st7
  int v28; // esi
  double v29; // st7
  double v30; // st7
  int v31; // ebx
  double v32; // st7
  int v33; // [esp+4h] [ebp-50h]
  int v34; // [esp+8h] [ebp-4Ch]
  int v35; // [esp+Ch] [ebp-48h]
  int v36; // [esp+10h] [ebp-44h]
  int v37; // [esp+14h] [ebp-40h]
  int v38; // [esp+18h] [ebp-3Ch]
  float v39; // [esp+1Ch] [ebp-38h]
  float v40; // [esp+20h] [ebp-34h]
  float v41; // [esp+24h] [ebp-30h]
  float v42; // [esp+28h] [ebp-2Ch]
  int v43; // [esp+2Ch] [ebp-28h]
  float v44; // [esp+30h] [ebp-24h]
  float v45; // [esp+34h] [ebp-20h]
  float v46; // [esp+38h] [ebp-1Ch]
  float v47; // [esp+3Ch] [ebp-18h]
  float v48; // [esp+40h] [ebp-14h]
  float v49; // [esp+44h] [ebp-10h]

  v5 = SelectedView[a3];
  if (v5 == 1 || v5 == 3) {
    v6 = *(_DWORD *)(a1 + 72);
    v43 = 40 * a2;
    v7 = 4 * a3;
    if (v6 < 2) {
      if (!v6) {
        v18 = chaseview[a3];
        v19 = viewdata_variable_4[6 * v18];
        _CHP(3 * v18, v7);
        v37 = (int)v19;
        v42 = v19;
        if (PULLZ[a3] > (double)v42) {
          v20 = PULLZ[a3] - (double)v43;
          PULLZ[a3] = v20;
          if (v20 < v42)
            PULLZ[a3] = v42;
        }
        v44 = (float)v37;
        v21 = a3;
        if (PULLZ[v21] < (double)v44) {
          v22 = (double)(40 * a2) + PULLZ[v21];
          PULLZ[v21] = v22;
          if (v22 > v44)
            PULLZ[v21] = v44;
        }
      }
    } else if (v6 <= 3) {
      if (*(_DWORD *)(a1 + 204)) {
        v8 = chaseview[a3];
        v9 = viewdata_variable_3[6 * v8];
        _CHP(3 * v8, v7);
        v36 = (int)v9;
        v45 = v9;
        if (PULLZ[a3] > (double)v45) {
          v10 = PULLZ[a3] - (double)v43;
          PULLZ[a3] = v10;
          if (v10 < v45)
            PULLZ[a3] = v45;
        }
        v47 = (float)v36;
        v11 = a3;
        if (PULLZ[v11] < (double)v47) {
          v12 = (double)(40 * a2) + PULLZ[v11];
          PULLZ[v11] = v12;
          if (v12 > v47)
            PULLZ[v11] = v47;
        }
      } else {
        v13 = chaseview[a3];
        v14 = viewdata_variable_2[6 * v13];
        _CHP(3 * v13, v7);
        v34 = (int)v14;
        v40 = v14;
        if (PULLZ[a3] > (double)v40) {
          v15 = PULLZ[a3] - (double)v43;
          PULLZ[a3] = v15;
          if (v15 < v40)
            PULLZ[a3] = v40;
        }
        v46 = (float)v34;
        v16 = a3;
        if (PULLZ[v16] < (double)v46) {
          v17 = (double)(40 * a2) + PULLZ[v16];
          PULLZ[v16] = v17;
          if (v17 > v46)
            PULLZ[v16] = v46;
        }
      }
    } else if (v6 == 1002) {
      v33 = 160 * a2;
      if (*(_DWORD *)(a1 + 204)) {
        v23 = chaseview[a3];
        v24 = viewdata_variable_3[6 * v23] + function_c_variable_13;
        _CHP(3 * v23, v7);
        v38 = (int)v24;
        v41 = v24;
        if (PULLZ[a3] > (double)v41) {
          v25 = PULLZ[a3] - (double)v33;
          PULLZ[a3] = v25;
          if (v25 < v41)
            PULLZ[a3] = v41;
        }
        v49 = (float)v38;
        v26 = a3;
        if (PULLZ[v26] < (double)v49) {
          v27 = (double)(40 * a2) + PULLZ[v26];
          PULLZ[v26] = v27;
          if (v27 > v49)
            PULLZ[v26] = v49;
        }
      } else {
        v28 = chaseview[a3];
        v29 = viewdata_variable_2[6 * v28] + function_c_variable_12;
        _CHP(3 * v28, v7);
        v35 = (int)v29;
        v39 = v29;
        if (PULLZ[a3] > (double)v39) {
          v30 = PULLZ[a3] - (double)v33;
          PULLZ[a3] = v30;
          if (v30 < v39)
            PULLZ[a3] = v39;
        }
        v48 = (float)v35;
        v31 = a3;
        if (PULLZ[v31] < (double)v48) {
          v32 = (double)(40 * a2) + PULLZ[v31];
          PULLZ[v31] = v32;
          if (v32 > v48)
            PULLZ[v31] = v48;
        }
      }
    }
  }*/
}

//-------------------------------------------------------------------------------------------------

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
  iNotRendered = abs(TrakColour[iChunkIdx].uiSurfType2) & 0x20000;// SURFACE_FLAG_SKIP_RENDER

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

void analysefalloff(int a1)
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

int showmap(int a1, int a2)
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

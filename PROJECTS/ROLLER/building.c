#include "building.h"
#include "3d.h"
#include "loadtrak.h"
#include "drawtrk3.h"
#include "transfrm.h"
#include <float.h>
//-------------------------------------------------------------------------------------------------

int BuildingSect[MAX_TRACK_CHUNKS]; //0018F040
float BuildingAngles[768];  //0018F990
int BuildingBase[256][4];   //00190590
tVec3 BuildingBox[256][8];  //00191590
tVisibleBuilding VisibleBuildings[256]; //00198F10
int16 advert_list[256];     //00199710
int NumBuildings;           //0019993C
int NumVisibleBuildings;    //00199940

//-------------------------------------------------------------------------------------------------
//000691B0
void InitBuildings()
{/*
  int v0; // edi
  int v1; // esi
  unsigned int v2; // eax
  tBuildingPlan *v3; // ecx
  tPolygon *pPols; // ebx
  int v5; // edx
  float *v6; // eax
  tData *v7; // edx
  int v8; // eax
  int byNumPols; // edx
  float *p_fX; // edx
  int i; // ebx
  double v12; // st7
  float *v13; // edx
  double v14; // st7
  float *v15; // edx
  unsigned int v16; // edx
  double v17; // [esp+0h] [ebp-118h]
  double v18; // [esp+18h] [ebp-100h]
  double v19; // [esp+28h] [ebp-F0h]
  double v20; // [esp+38h] [ebp-E0h]
  double v21; // [esp+40h] [ebp-D8h]
  double v22; // [esp+48h] [ebp-D0h]
  double v23; // [esp+50h] [ebp-C8h]
  double v24; // [esp+58h] [ebp-C0h]
  double v25; // [esp+60h] [ebp-B8h]
  float v26; // [esp+70h] [ebp-A8h]
  float v27; // [esp+80h] [ebp-98h]
  float v28; // [esp+84h] [ebp-94h]
  float v29; // [esp+8Ch] [ebp-8Ch]
  float v30; // [esp+90h] [ebp-88h]
  float v31; // [esp+94h] [ebp-84h]
  float v32; // [esp+98h] [ebp-80h]
  int v33; // [esp+9Ch] [ebp-7Ch]
  float v34; // [esp+A0h] [ebp-78h]
  float v35; // [esp+A4h] [ebp-74h]
  int v36; // [esp+A8h] [ebp-70h]
  float v37; // [esp+ACh] [ebp-6Ch]
  int v38; // [esp+B0h] [ebp-68h]
  int v39; // [esp+B4h] [ebp-64h]
  float v40; // [esp+B8h] [ebp-60h]
  float v41; // [esp+BCh] [ebp-5Ch]
  float v42; // [esp+C0h] [ebp-58h]
  float v43; // [esp+C4h] [ebp-54h]
  float v44; // [esp+C8h] [ebp-50h]
  float v45; // [esp+CCh] [ebp-4Ch]
  float v46; // [esp+D0h] [ebp-48h]
  float v47; // [esp+D4h] [ebp-44h]
  float v48; // [esp+D8h] [ebp-40h]
  float v49; // [esp+DCh] [ebp-3Ch]
  float v50; // [esp+E0h] [ebp-38h]
  float v51; // [esp+E4h] [ebp-34h]
  int v52; // [esp+E8h] [ebp-30h]
  int v53; // [esp+ECh] [ebp-2Ch]
  int v54; // [esp+F0h] [ebp-28h]
  int v55; // [esp+F4h] [ebp-24h]
  int v56; // [esp+F8h] [ebp-20h]
  int v57; // [esp+FCh] [ebp-1Ch]

  memset(BuildingSect, 255, sizeof(BuildingSect));
  v39 = 0;
  if (NumBuildings > 0) {
    v38 = 0;
    v0 = 0;
    v1 = 0;
    v33 = 96;
    do {
      v2 = BuildingBase[v0];
      if (v2 <= 0x10) {
        v3 = &BuildingPlans[v2];
        pPols = v3->pPols;
        v36 = BuildingBase_variable_1[v0];
        v5 = v36 + 1;
        v29 = (float)(32 * BuildingBase_variable_2[v0] / 2);
        if (v36 + 1 >= TRAK_LEN)
          v5 -= TRAK_LEN;
        v6 = (float *)&localdata[v36];
        v31 = -v6[9];
        v30 = -v6[10];
        v32 = -v6[11];
        v7 = &localdata[v5];
        v17 = v6[10] - v7->pointAy[3].fY;
        v18 = v6[9] - v7->pointAy[3].fX;
        v25 = sqrt(v18 * v18 + v17 * v17);
        if ((HIDWORD(v18) & 0x7FFFFFFF) != 0 || LODWORD(v18))
          v18 = (v6[9] - v7->pointAy[3].fX) / v25;
        if ((HIDWORD(v17) & 0x7FFFFFFF) != 0 || LODWORD(v17))
          v17 = v17 / v25;
        v8 = 32 * BuildingBase_variable_3[v0] / 2;
        BuildingX[v1] = v31 - v17 * v29;
        BuildingY[v1] = v29 * v18 + v30;
        BuildingSect[v36] = v39;
        byNumPols = 0;
        BuildingZ[v1] = (double)v8 + v32;
        while (byNumPols < v3->byNumPols) {
          if ((pPols->uiTex & 0x200) != 0)
            byNumPols = v3->byNumPols;
          ++pPols;
          ++byNumPols;
        }
        *(float *)&v56 = 1073741800.0;
        *(float *)&v52 = 1073741800.0;
        *(float *)&v54 = 1073741800.0;
        p_fX = &v3->pCoords->fX;
        *(float *)&v53 = -1073741800.0;
        *(float *)&v55 = -1073741800.0;
        *(float *)&v57 = -1073741800.0;
        for (i = 0; i < v3->byNumCoords; ++i) {
          if (*p_fX < (double)*(float *)&v54)
            v54 = *(int *)p_fX;
          if (*p_fX > (double)*(float *)&v57)
            v57 = *(int *)p_fX;
          v12 = p_fX[1];
          v13 = p_fX + 1;
          if (v12 < *(float *)&v52)
            v52 = *(int *)v13;
          if (*v13 > (double)*(float *)&v55)
            v55 = *(int *)v13;
          v14 = v13[1];
          v15 = v13 + 1;
          if (v14 < *(float *)&v56)
            v56 = *(int *)v15;
          if (*v15 > (double)*(float *)&v53)
            v53 = *(int *)v15;
          p_fX = v15 + 1;
        }
        if ((cheat_mode & 0x1000) != 0) {
          *(float *)&v54 = *(float *)&v54 * building_c_variable_1;
          *(float *)&v52 = *(float *)&v52 * building_c_variable_1;
          *(float *)&v56 = *(float *)&v56 * building_c_variable_1;
          *(float *)&v57 = *(float *)&v57 * building_c_variable_1;
          *(float *)&v55 = *(float *)&v55 * building_c_variable_1;
          *(float *)&v53 = *(float *)&v53 * building_c_variable_1;
        }
        v37 = *(float *)&BuildingAngles[v38] * building_c_variable_2;
        v35 = *(float *)&BuildingAngles_variable_1[v38] * building_c_variable_2;
        v34 = BuildingAngles_variable_2[v38] * building_c_variable_2;
        v50 = BuildingX[v1];
        v49 = BuildingY[v1];
        v51 = BuildingZ[v1];
        v20 = cos(v37);
        v19 = cos(v35);
        v22 = sin(v37);
        v24 = sin(v35);
        v23 = sin(v34);
        v21 = cos(v34);
        v16 = 96 * v39;
        BuildingBox[v16 / 4] = v54;
        BuildingBox_variable_1[v16 / 4] = v52;
        BuildingBox_variable_2[v16 / 4] = v56;
        BuildingBox_variable_3[v16 / 4] = v57;
        BuildingBox_variable_4[v16 / 4] = v52;
        BuildingBox_variable_5[v16 / 4] = v56;
        BuildingBox_variable_6[v16 / 4] = v57;
        BuildingBox_variable_7[v16 / 4] = v55;
        BuildingBox_variable_8[v16 / 4] = v56;
        BuildingBox_variable_9[v16 / 4] = v54;
        BuildingBox_variable_10[v16 / 4] = v55;
        BuildingBox_variable_11[v16 / 4] = v56;
        BuildingBox_variable_12[v16 / 4] = v54;
        BuildingBox_variable_13[v16 / 4] = v52;
        BuildingBox_variable_14[v16 / 4] = v53;
        BuildingBox_variable_15[v16 / 4] = v57;
        BuildingBox_variable_16[v16 / 4] = v52;
        BuildingBox_variable_17[v16 / 4] = v53;
        BuildingBox_variable_18[v16 / 4] = v57;
        BuildingBox_variable_19[v16 / 4] = v55;
        BuildingBox_variable_20[v16 / 4] = v53;
        BuildingBox_variable_21[v16 / 4] = v54;
        BuildingBox_variable_22[v16 / 4] = v55;
        BuildingBox_variable_23[v16 / 4] = v53;
        do {
          v28 = *(float *)&BuildingBox[v16 / 4];
          v27 = *(float *)&BuildingBox_variable_1[v16 / 4];
          v26 = *(float *)&BuildingBox_variable_2[v16 / 4];
          v44 = v20 * v19;
          v45 = -v20 * v24 * v21 - v22 * v23;
          v48 = v20 * v24 * v23 - v22 * v21;
          *(float *)&BuildingBox[v16 / 4] = v28 * v44 + v27 * v48 + v26 * v45 + v50;
          v42 = -v22 * v24 * v21 + v20 * v23;
          v43 = v22 * v19;
          v47 = v22 * v24 * v23 + v20 * v21;
          *(float *)&BuildingBox_variable_1[v16 / 4] = v28 * v43 + v27 * v47 + v26 * v42 + v49;
          v16 += 12;
          v40 = v24;
          v46 = v21 * v19;
          v41 = -v23 * v19;
          BuildingBase_variable_4[v16 / 4] = v28 * v40 + v27 * v41 + v26 * v46 + v51;
        } while (v16 != v33);
        BuildingBaseX[v1] = BuildingX[v1];
        BuildingBaseY[v1] = BuildingY[v1];
        BuildingBaseZ[v1] = BuildingZ[v1];
      }
      v0 += 4;
      ++v1;
      v38 += 3;
      v33 += 96;
      ++v39;
    } while (v39 < NumBuildings);
  }*/
}

//-------------------------------------------------------------------------------------------------
//00069960
void CalcVisibleBuildings()
{
  int iTrackLen; // ebp
  tVisibleBuilding *pVisibleBuilding; // edi
  int iTrackSectIdx; // ecx
  int iBuildingCounter; // edx
  int iWrappedSectIdx; // edx
  int iBuildingIdx; // esi
  unsigned int uiBuildingType; // edx
  //int iPointOffset; // edx
  double dPointDepth; // st7
  //int iPointOffset2; // edx
  double dPointDepth2; // st7
  int iCurrentCount; // eax
  //float fTempDepth; // [esp+18h] [ebp-24h]
  //float fTempDepth2; // [esp+1Ch] [ebp-20h]
  float fBuildingDepth; // [esp+20h] [ebp-1Ch]

  iTrackLen = TRAK_LEN;                         // Store track length for later restoration
  pVisibleBuilding = VisibleBuildings;          // Get pointer to visible buildings array
  iTrackSectIdx = TrackSize;
  VisibleBuildings[0].iBuildingIdx = -1;        // Initialize visible buildings array with terminator
  NumVisibleBuildings = 0;                      // Reset visible building count
  for (iBuildingCounter = 0; iBuildingCounter < NumBuildings; ++iBuildingCounter)// Count through all buildings (purpose unclear - possibly validation)
    ;
  if ((textures_off & 0x200) == 0)            // Check if building textures are enabled (bit 9 of textures_off)
  {
    while (1) {
      if (iTrackSectIdx < 0)
        goto FUNCTION_EXIT;                     // Start of main track section loop - iterate backwards through track
      if (iTrackSectIdx <= first_size || iTrackSectIdx >= gap_size)// Skip sections in track gap (between first_size and gap_size)
      {
        iWrappedSectIdx = iTrackSectIdx + start_sect;// Calculate wrapped track section index with start_sect offset
        if (iTrackSectIdx + start_sect < 0)   // Handle negative wraparound
          iWrappedSectIdx += iTrackLen;
        if (iWrappedSectIdx >= iTrackLen)     // Handle positive wraparound
          iWrappedSectIdx -= iTrackLen;
        iBuildingIdx = BuildingSect[iWrappedSectIdx];// Get building index for this track section
        if (iBuildingIdx != -1)
          break;                                // Skip if no building in this section (-1)
      }
    NEXT_TRACK_SECTION:
      --iTrackSectIdx;                          // Continue to next track section
    }
    uiBuildingType = BuildingBase[iBuildingIdx][0];// Get building type from BuildingBase array
    if (uiBuildingType < 4)                   // Check building type - types 0,1 use max depth, others use min depth
    {
      if (uiBuildingType > 1)
        goto CALC_MIN_DEPTH;
    } else if (uiBuildingType > 7 && uiBuildingType != 14)// Types 8+ except 14 use min depth calculation
    {
    CALC_MIN_DEPTH:
      // Calculate min depth
      fBuildingDepth = FLT_MAX;  // Initialize to very large value
      for (int iPointIdx = 0; iPointIdx < 8; iPointIdx++)
      {
        dPointDepth2 = (BuildingBox[iBuildingIdx][iPointIdx].fX - viewx) * vk3
                     + (BuildingBox[iBuildingIdx][iPointIdx].fY - viewy) * vk6  
                     + (BuildingBox[iBuildingIdx][iPointIdx].fZ - viewz) * vk9;
         
        if (dPointDepth2 < fBuildingDepth)
        {
          fBuildingDepth = (float)dPointDepth2;
        }
      }
      //iPointOffset2 = 96 * iBuildingIdx + 12;   // Calculate min depth for other building types - start with first point
      //fBuildingDepth = (BuildingBox[iBuildingIdx][0].fX - viewx) * vk3 + (BuildingBox[iBuildingIdx][0].fY - viewy) * vk6 + (BuildingBox[iBuildingIdx][0].fZ - viewz) * vk9;// Transform first bounding box point to view space depth
      //do {
      //  dPointDepth2 = (*(float *)((char *)&BuildingBox[0][0].fX + iPointOffset2) - viewx) * vk3
      //    + (*(float *)((char *)&BuildingBox[0][0].fY + iPointOffset2) - viewy) * vk6
      //    + (*(float *)((char *)&BuildingBox[0][0].fZ + iPointOffset2) - viewz) * vk9;// Transform current point to view space depth
      //  if (dPointDepth2 < fBuildingDepth)    // Keep minimum depth value
      //  {
      //    fTempDepth = dPointDepth2;
      //    fBuildingDepth = fTempDepth;
      //  }
      //  iPointOffset2 += 12;
      //} while (iPointOffset2 != 96 * iBuildingIdx + 96);// Loop through all 8 bounding box points
    ADD_BUILDING_TO_LIST:
      ++pVisibleBuilding;                       // Add building to visible list - advance pointer
      pVisibleBuilding[-1].fDepth = fBuildingDepth;// Store depth value in array (float)
      iCurrentCount = NumVisibleBuildings;
      pVisibleBuilding[-1].iBuildingIdx = iBuildingIdx;// Store building index in array
      pVisibleBuilding->iBuildingIdx = -1;      // Add array terminator (-1)
      NumVisibleBuildings = iCurrentCount + 1;  // Increment visible building count
      goto NEXT_TRACK_SECTION;
    }

    fBuildingDepth = -FLT_MAX;  // Initialize to very small value
    for (int iPointIdx = 0; iPointIdx < 8; iPointIdx++)
    {
      dPointDepth = (BuildingBox[iBuildingIdx][iPointIdx].fX - viewx) * vk3
                  + (BuildingBox[iBuildingIdx][iPointIdx].fY - viewy) * vk6  
                  + (BuildingBox[iBuildingIdx][iPointIdx].fZ - viewz) * vk9;
        
      if (dPointDepth > fBuildingDepth)
      {
        fBuildingDepth = (float)dPointDepth;
      }
    }
    //iPointOffset = 96 * iBuildingIdx + 12;      // Calculate max depth for building types 0,1 - start with first point
    //fBuildingDepth = (BuildingBox[iBuildingIdx][0].fX - viewx) * vk3 + (BuildingBox[iBuildingIdx][0].fY - viewy) * vk6 + (BuildingBox[iBuildingIdx][0].fZ - viewz) * vk9;// Transform first bounding box point to view space using view matrix
    //do {
    //  dPointDepth = (*(float *)((char *)&BuildingBox[0][0].fX + iPointOffset) - viewx) * vk3
    //    + (*(float *)((char *)&BuildingBox[0][0].fY + iPointOffset) - viewy) * vk6
    //    + (*(float *)((char *)&BuildingBox[0][0].fZ + iPointOffset) - viewz) * vk9;// Transform current point to view space depth
    //  if (dPointDepth > fBuildingDepth)       // Keep maximum depth value
    //  {
    //    fTempDepth2 = dPointDepth;
    //    fBuildingDepth = fTempDepth2;
    //  }
    //  iPointOffset += sizeof(tVec3);
    //} while (iPointOffset != 96 * iBuildingIdx + 96);// Loop through all 8 bounding box points (96 bytes total, 12 per point)
    goto ADD_BUILDING_TO_LIST;
  }
FUNCTION_EXIT:
  TRAK_LEN = iTrackLen;                         // Restore original TRAK_LEN value
}

//-------------------------------------------------------------------------------------------------
//00069C10
void DrawBuilding(int a1, uint8 *a2)
{
  (void)(a1); (void)(a2);
  /*
  int *v2; // esi
  float *v3; // ecx
  unsigned __int8 *v4; // ebx
  float *v5; // edi
  int v6; // ebp
  float *v7; // eax
  float v8; // edx
  double v9; // st5
  double v10; // rt1
  double v11; // st5
  int v12; // eax
  double v13; // rt2
  double v14; // st5
  int v15; // eax
  double v16; // st4
  int v17; // eax
  double v18; // st4
  int v19; // eax
  double v20; // st7
  int v21; // eax
  int v22; // edx
  int *v23; // esi
  int v24; // edi
  int v25; // edx
  float v26; // eax
  float v27; // eax
  float v28; // eax
  float v29; // eax
  float v30; // eax
  int v31; // edx
  int v32; // esi
  int k; // ebx
  int v34; // ebx
  unsigned __int8 *v35; // ebp
  int v36; // eax
  int v37; // edx
  int v38; // eax
  float v39; // edx
  int v40; // eax
  int v41; // eax
  unsigned __int8 *v42; // edi
  int v43; // ebx
  _DWORD *v44; // edx
  unsigned __int8 *v45; // ecx
  _DWORD *v46; // eax
  char *v47; // edx
  unsigned __int8 *v48; // ecx
  _DWORD *v49; // eax
  _DWORD *v50; // edx
  int v51; // ebx
  int v52; // esi
  int v53; // ecx
  int v54; // edx
  float v55; // eax
  float v56; // eax
  float v57; // eax
  int v58; // ebp
  double v59; // [esp+48h] [ebp-190h]
  double v60; // [esp+58h] [ebp-180h]
  double v61; // [esp+70h] [ebp-168h]
  double v62; // [esp+78h] [ebp-160h]
  double v63; // [esp+80h] [ebp-158h]
  double v64; // [esp+88h] [ebp-150h]
  float v65; // [esp+90h] [ebp-148h]
  float v66; // [esp+94h] [ebp-144h]
  int v67; // [esp+98h] [ebp-140h]
  float v68; // [esp+9Ch] [ebp-13Ch]
  float v69; // [esp+A0h] [ebp-138h]
  float v70; // [esp+A4h] [ebp-134h]
  float v71; // [esp+A8h] [ebp-130h]
  int v72; // [esp+ACh] [ebp-12Ch]
  float v73; // [esp+B0h] [ebp-128h]
  float v74; // [esp+B0h] [ebp-128h]
  float v75; // [esp+B4h] [ebp-124h]
  float v76; // [esp+B4h] [ebp-124h]
  int v77; // [esp+B8h] [ebp-120h]
  float v78; // [esp+BCh] [ebp-11Ch]
  float v79; // [esp+C0h] [ebp-118h]
  float v80; // [esp+C0h] [ebp-118h]
  float v81; // [esp+C4h] [ebp-114h]
  float v82; // [esp+C4h] [ebp-114h]
  float v83; // [esp+C8h] [ebp-110h]
  float v84; // [esp+CCh] [ebp-10Ch]
  float v85; // [esp+D0h] [ebp-108h]
  float v86; // [esp+D4h] [ebp-104h]
  float v87; // [esp+D8h] [ebp-100h]
  float v89; // [esp+E0h] [ebp-F8h]
  float v90; // [esp+F8h] [ebp-E0h]
  float v91; // [esp+104h] [ebp-D4h]
  float v92; // [esp+104h] [ebp-D4h]
  int v93; // [esp+108h] [ebp-D0h]
  float v94; // [esp+10Ch] [ebp-CCh]
  float v95; // [esp+10Ch] [ebp-CCh]
  float v96; // [esp+118h] [ebp-C0h]
  float v97; // [esp+11Ch] [ebp-BCh]
  float v98; // [esp+120h] [ebp-B8h]
  float v99; // [esp+124h] [ebp-B4h]
  float v100; // [esp+128h] [ebp-B0h]
  float v102; // [esp+13Ch] [ebp-9Ch]
  float v103; // [esp+13Ch] [ebp-9Ch]
  float v104; // [esp+140h] [ebp-98h]
  float v105; // [esp+154h] [ebp-84h]
  float v106; // [esp+170h] [ebp-68h]
  int v107; // [esp+184h] [ebp-54h]
  float *v108; // [esp+188h] [ebp-50h]
  int j; // [esp+190h] [ebp-48h]
  int v110; // [esp+194h] [ebp-44h]
  unsigned int v111; // [esp+198h] [ebp-40h]
  unsigned int v112; // [esp+1A0h] [ebp-38h]
  float v113; // [esp+1A4h] [ebp-34h]
  float v114; // [esp+1A4h] [ebp-34h]
  float v115; // [esp+1ACh] [ebp-2Ch]
  int i; // [esp+1B0h] [ebp-28h]
  float v117; // [esp+1B4h] [ebp-24h]
  unsigned __int8 v118; // [esp+1BCh] [ebp-1Ch]
  unsigned __int8 v119; // [esp+1C0h] [ebp-18h]

  set_starts(0);
  v111 = BuildingBase[4 * a1];
  v2 = (int *)&BuildingCoords;
  v3 = (float *)BuildingView;
  v118 = BuildingPlans[12 * v111];
  v4 = (unsigned __int8 *)*(&BuildingPlans_variable_2 + 3 * v111);
  v119 = BuildingPlans_variable_1[12 * v111];
  v5 = (float *)*(&BuildingPlans_variable_3 + 3 * v111);
  if (v111 >= 9 && (v111 <= 0xA || v111 == 15)) {
    v94 = *(float *)&BuildingAngles_variable_1[3 * a1];
    v91 = BuildingAngles_variable_2[3 * a1];
    v113 = (float)(360 * worlddirn / 0x3FFF);
  } else {
    v113 = *(float *)&BuildingAngles[3 * a1];
    v94 = *(float *)&BuildingAngles_variable_1[3 * a1];
    v91 = BuildingAngles_variable_2[3 * a1];
  }
  v114 = v113 * building_c_variable_3;
  v95 = v94 * building_c_variable_3;
  v92 = building_c_variable_3 * v91;
  v68 = BuildingX[a1];
  v66 = BuildingZ[a1];
  v59 = cos(v114);
  v63 = cos(v95);
  v61 = sin(v114);
  v62 = sin(v95);
  v64 = sin(v92);
  v60 = cos(v92);
  v71 = BuildingY[a1];
  for (i = 0; v119 > i; ++i) {
    v6 = 0;
    v108 = v5 + 1;
    v7 = v5 + 2;
    if ((cheat_mode & 0x1000) != 0) {
      v69 = *v5 * building_c_variable_4;
      LODWORD(v8) = v5 + 1;
      v65 = *v108 * building_c_variable_4;
      v5 += 3;
      v115 = building_c_variable_4 * *v7;
    } else {
      v69 = *v5;
      v7 = *(float **)v7;
      v5 += 3;
      v8 = *v108;
      v115 = *(float *)&v7;
      v65 = *v108;
    }
    v84 = v59 * v62 * v64 - v61 * v60;
    v87 = v59 * v63;
    v98 = -v59 * v62 * v60 - v61 * v64;
    v9 = v69 * v87 + v65 * v84 + v115 * v98 + v68 - viewx;
    _CHP(v7, LODWORD(v8));
    v10 = v9;
    v86 = v61 * v63;
    v97 = -v61 * v62 * v60 + v59 * v64;
    v100 = v61 * v62 * v64 + v59 * v60;
    v11 = v69 * v86 + v65 * v100 + v115 * v97 + v71 - viewy;
    _CHP(v12, LODWORD(v8));
    v13 = v11;
    v78 = v63 * v60;
    v85 = v62;
    v117 = -v64 * v63;
    v14 = v69 * v85 + v65 * v117 + v115 * v78 + v66 - viewz;
    _CHP(v15, LODWORD(v8));
    v16 = v10 * vk1 + v13 * vk4 + v14 * vk7;
    _CHP(v17, LODWORD(v8));
    v72 = (int)v16;
    v18 = v10 * vk2 + v13 * vk5 + v14 * vk8;
    _CHP(v19, LODWORD(v8));
    v67 = (int)v18;
    v20 = v10 * vk3 + v13 * vk6 + v14 * vk9;
    _CHP(v21, LODWORD(v8));
    v77 = (int)v20;
    if ((int)v20 < 80) {
      v6 = 1;
      v77 = 80;
    }
    xp = v72 * VIEWDIST / v77 + xbase;
    yp = v67 * VIEWDIST / v77 + ybase;
    v22 = v67 * VIEWDIST / v77 + ybase;
    *v2 = (scr_size * (v72 * VIEWDIST / v77 + xbase)) >> 6;
    v2[1] = (scr_size * (199 - v22)) >> 6;
    *v3 = (float)v72;
    v3[1] = (float)v67;
    v3[2] = (float)(int)v20;
    v23 = v2 + 2;
    *v23 = v6;
    v3 += 3;
    v2 = v23 + 1;
  }
  v24 = 0;
  v25 = 0;
  while (v24 < v118) {
    BuildingZOrder_variable_2[v25] = v24;
    BuildingZOrder_variable_1[v25] = *((__int16 *)v4 + 4);
    if ((v4[5] & 0x80u) == 0) {
      if (BuildingView_variable_2[3 * v4[2]] <= (double)BuildingView_variable_2[3 * v4[3]])
        v29 = BuildingView_variable_2[3 * v4[3]];
      else
        v29 = BuildingView_variable_2[3 * v4[2]];
      v105 = v29;
      if (BuildingView_variable_2[3 * *v4] <= (double)BuildingView_variable_2[3 * v4[1]])
        v30 = BuildingView_variable_2[3 * v4[1]];
      else
        v30 = BuildingView_variable_2[3 * *v4];
      if (v30 <= (double)v105) {
        if (BuildingView_variable_2[3 * v4[2]] <= (double)BuildingView_variable_2[3 * v4[3]])
          v28 = BuildingView_variable_2[3 * v4[3]];
        else
          v28 = BuildingView_variable_2[3 * v4[2]];
      } else if (BuildingView_variable_2[3 * *v4] <= (double)BuildingView_variable_2[3 * v4[1]]) {
        v28 = BuildingView_variable_2[3 * v4[1]];
      } else {
        v28 = BuildingView_variable_2[3 * *v4];
      }
    } else {
      if (BuildingView_variable_2[3 * v4[2]] >= (double)BuildingView_variable_2[3 * v4[3]])
        v26 = BuildingView_variable_2[3 * v4[3]];
      else
        v26 = BuildingView_variable_2[3 * v4[2]];
      v104 = v26;
      if (BuildingView_variable_2[3 * *v4] >= (double)BuildingView_variable_2[3 * v4[1]])
        v27 = BuildingView_variable_2[3 * v4[1]];
      else
        v27 = BuildingView_variable_2[3 * *v4];
      if (v27 >= (double)v104) {
        if (BuildingView_variable_2[3 * v4[2]] >= (double)BuildingView_variable_2[3 * v4[3]])
          v28 = BuildingView_variable_2[3 * v4[3]];
        else
          v28 = BuildingView_variable_2[3 * v4[2]];
      } else if (BuildingView_variable_2[3 * *v4] >= (double)BuildingView_variable_2[3 * v4[1]]) {
        v28 = BuildingView_variable_2[3 * v4[1]];
      } else {
        v28 = BuildingView_variable_2[3 * *v4];
      }
    }
    *(float *)&BuildingZOrder[v25] = v28;
    v4 += 12;
    v25 += 3;
    ++v24;
  }
  qsort(BuildingZOrder, v118, 12, bldZcmp);
  for (j = 0; v118 > j; ++j) {
    v31 = 0;
    v110 = -1;
    v32 = -1;
    v89 = -32768.0;
    for (k = 0; k < v118; ++k) {
      if (BuildingZOrder_variable_1[v31] != v32) {
        v32 = BuildingZOrder_variable_1[v31];
        if (v89 < (double)*(float *)&BuildingZOrder[v31]) {
          v93 = k;
          v110 = BuildingZOrder_variable_1[v31];
          v89 = *(float *)&BuildingZOrder[v31];
        }
      }
      v31 += 3;
    }
    if (v110 < 0) {
      j = v118;
    } else {
      v107 = 3 * v93;
      do {
        BuildingZOrder[v107] = -1082130432;
        v34 = BuildingZOrder_variable_2[v107];
        BuildingZOrder_variable_1[v107] = -1;
        v35 = (unsigned __int8 *)*(&BuildingPlans_variable_2 + 3 * v111) + 12 * v34;
        v112 = *((_DWORD *)v35 + 1);
        v36 = 3 * v35[2];
        v81 = *(float *)&BuildingView[v36];
        v37 = BuildingView_variable_1[v36];
        v75 = BuildingView_variable_2[v36];
        v38 = 3 * v35[1];
        v79 = *(float *)&v37;
        v73 = *(float *)&BuildingView[v38];
        v39 = *(float *)&BuildingView_variable_1[v38];
        v102 = BuildingView_variable_2[v38];
        v40 = 3 * *v35;
        v70 = *(float *)&BuildingView[v40];
        v82 = v81 - v70;
        v83 = *(float *)&BuildingView_variable_1[v40];
        v80 = v79 - v83;
        v99 = BuildingView_variable_2[v40];
        v41 = 3 * v35[3];
        v76 = v75 - v99;
        v74 = v73 - *(float *)&BuildingView[v41];
        v96 = v39 - *(float *)&BuildingView_variable_1[v41];
        v103 = v102 - BuildingView_variable_2[v41];
        v90 = (v80 * v103 - v76 * v96) * v70 + (v76 * v74 - v82 * v103) * v83 + (v82 * v96 - v80 * v74) * v99;
        if (v90 < 0.0 || (v112 & 0x2000) != 0) {
          v42 = v35 + 4;
          v43 = 0;
          if (v90 < 0.0) {
            v47 = (char *)&BuildingPol_variable_3;
            v48 = v35;
            do {
              v49 = (_DWORD *)((char *)&BuildingCoords + 12 * *v48);
              v50 = v47 + 4;
              *(v50 - 1) = *v49;
              ++v48;
              *v50 = v49[1];
              v47 = (char *)(v50 + 1);
              v43 += v49[2];
            } while (v48 != v42);
          } else {
            v44 = &BuildingPol_variable_4;
            v45 = v35;
            do {
              v46 = (_DWORD *)((char *)&BuildingCoords + 12 * *v45);
              *v44 = *v46;
              v44 -= 2;
              v44[3] = v46[1];
              ++v45;
              v43 += v46[2];
            } while (v45 != v42);
          }
          if ((v112 & 0x200) != 0)
            v112 = advert_list[a1];
          if ((textures_off & 0x80) != 0 && (v112 & 0x100) != 0)
            v112 = (v112 & 0xFFFFFE00) + bld_remap[(unsigned __int8)v112];
          BuildingPol = v112;
          BuildingPol_variable_2 = 4;
          if (v43 < 4) {
            v51 = *v35;
            v52 = v35[1];
            v53 = v35[2];
            v54 = v35[3];
            if (BuildingView_variable_2[3 * v51] >= (double)BuildingView_variable_2[3 * v52])
              v55 = BuildingView_variable_2[3 * v52];
            else
              v55 = BuildingView_variable_2[3 * v51];
            v106 = v55;
            if (BuildingView_variable_2[3 * v53] >= (double)BuildingView_variable_2[3 * v54])
              v56 = BuildingView_variable_2[3 * v54];
            else
              v56 = BuildingView_variable_2[3 * v53];
            if (v106 >= (double)v56) {
              if (BuildingView_variable_2[3 * v53] >= (double)BuildingView_variable_2[3 * v54])
                v57 = BuildingView_variable_2[3 * v54];
              else
                v57 = BuildingView_variable_2[3 * v53];
            } else if (BuildingView_variable_2[3 * v51] >= (double)BuildingView_variable_2[3 * v52]) {
              v57 = BuildingView_variable_2[3 * v52];
            } else {
              v57 = BuildingView_variable_2[3 * v51];
            }
            if ((double)(unsigned __int8)BuildingSub[v111] * subscale <= v57) {
              if ((BuildingPol_variable_1 & 1) != 0)
                POLYTEX(building_vga, a2, (int *)&BuildingPol, 17, gfx_size);
              else
                POLYFLAT(a2, &BuildingPol);
            } else {
              subdivide(
                a2,
                (int)&BuildingPol,
                *(float *)&BuildingView[3 * v51],
                *(float *)&BuildingView_variable_1[3 * v51],
                BuildingView_variable_2[3 * v51],
                *(float *)&BuildingView[3 * v52],
                *(float *)&BuildingView_variable_1[3 * v52],
                BuildingView_variable_2[3 * v52],
                *(float *)&BuildingView[3 * v53],
                *(float *)&BuildingView_variable_1[3 * v53],
                BuildingView_variable_2[3 * v53],
                *(float *)&BuildingView[3 * v54],
                *(float *)&BuildingView_variable_1[3 * v54],
                BuildingView_variable_2[3 * v54],
                666,
                gfx_size);
            }
          }
        }
        v58 = v107 * 4 + 12;
        v107 += 3;
        ++v93;
      } while (v118 > v93 && v110 == *(int *)((char *)BuildingZOrder_variable_1 + v58));
    }
  }
  init_animate_ads();*/
}

//-------------------------------------------------------------------------------------------------
//0006AB30
void init_animate_ads()
{
  ;
}

//-------------------------------------------------------------------------------------------------
//0006AB40
int bldZcmp(int a1, int a2)
{
  (void)(a1); (void)(a2);
  return 0;
  /*
  int v2; // ecx
  int v3; // ebx
  float v5; // [esp+0h] [ebp-10h]
  float v6; // [esp+4h] [ebp-Ch]

  v2 = *(_DWORD *)(a1 + 4);
  v6 = *(float *)a1;
  v3 = *(_DWORD *)(a2 + 4);
  v5 = *(float *)a2;
  if (v2 < v3)
    return -1;
  if (v2 == v3) {
    if (v6 == v5)
      return 0;
    if (v6 >= (double)v5)
      return -1;
  }
  return 1;*/
}

//-------------------------------------------------------------------------------------------------
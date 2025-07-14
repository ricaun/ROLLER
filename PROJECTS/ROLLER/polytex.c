#include "polytex.h"
#include "graphics.h"
//-------------------------------------------------------------------------------------------------

fixed16_16 startsx[4] = { 0x3FF000, 0x0, 0x0, 0x3FF000 }; //000A7474 0x3FF000 = 64.0 in 16.16 fixed point
fixed16_16 startsy[4] = { 0x0, 0x0, 0x3FF000, 0x3FF000 }; //000A7484 0x3FF000 = 64.0 in 16.16 fixed point
uint8 *scrptr;            //0019EC20
uint8 *mapsel[19][257];   //0019EC28 changed to uint8* by ROLLER, original code these are 16-bit DOS selectors

//-------------------------------------------------------------------------------------------------

void remove_mapsels()
{
  // Clear all mapsel arrays
  memset(mapsel, 0, sizeof(mapsel));
  // Clear texture counts
  memset(num_textures, 0, sizeof(num_textures));

  //int iCarIdx; // ebp
  //int iMapselOffset; // ecx
  //int iCarDataOffset; // edi
  //int iTextureIdx; // esi
  //int iNextCarDataOffset; // esi
  //int iNextMapselOffset; // eax
  //int iTrackTexIdx; // esi
  //int iMapselOffset_1; // ecx
  //int iBldTexIdx; // esi
  //int iBuildingMapselIdx; // ecx
  //int iCarGenTexIdx; // esi
  //int iCarGenMapselIdx; // ecx
  //union REGS regs; // [esp+0h] [ebp-3Ch] BYREF
  //int iCarIdxCounter; // [esp+1Ch] [ebp-20h]
  //int iCarMapselOffset; // [esp+20h] [ebp-1Ch]
  //
  //iCarIdxCounter = 1;
  //
  //// Process car textures
  //if (LoadCarTextures > 1) {
  //  iCarIdx = 1;
  //  iCarMapselOffset = 514;                     // starting offset: 514 = 257*2 (skip types 0 and 1)
  //  do {
  //    iMapselOffset = iCarMapselOffset;
  //    iCarDataOffset = iCarIdx * 4;             // 4 bytes per car entry
  //
  //    // Process all textures for this car
  //    for (iTextureIdx = 0; iTextureIdx < bld_remap[iCarIdx + 255]; iMapselOffset += 2)// reference into num_textures
  //    {
  //      // Check if selector is allocated
  //      if (*(int16 *)((char *)mapsel[0] + iMapselOffset)) {
  //        // Free the selector
  //        regs.w.bx = *(int16 *)((char *)mapsel[0] + iMapselOffset);
  //        regs.w.ax = 1;                        // DPMI function: free LDT descriptor
  //        int386(0x31, &regs, &regs);           // DPMI services
  //        // Clear the selector entry
  //        *(int16 *)((char *)mapsel[0] + iMapselOffset) = 0;
  //      }
  //      ++iTextureIdx;
  //    }
  //
  //    iNextCarDataOffset = iCarMapselOffset;
  //    iNextMapselOffset = LoadCarTextures;
  //    ++iCarIdx;
  //
  //    // Clear tex count for this car
  //    *(int *)((char *)&bld_remap[255] + iCarDataOffset) = 0;// reference into num_textures
  //
  //    // Move to next car's mapsel area
  //    iCarMapselOffset = iNextCarDataOffset + 514;
  //    ++iCarIdxCounter;
  //  } while (iCarIdxCounter < iNextMapselOffset);
  //}
  //
  //// Process track textures
  //iTrackTexIdx = 0;
  //if (num_textures[19] > 0) {
  //  iMapselOffset_1 = 0;
  //  do {
  //    // Check if selector is allocated
  //    if (mapsel[0][iMapselOffset_1]) {
  //      // Free the selector
  //      regs.w.bx = mapsel[0][iMapselOffset_1];
  //      regs.w.ax = 1;
  //      int386(0x31, &regs, &regs);
  //
  //      // Clear the selector entry
  //      mapsel[0][iMapselOffset_1] = 0;
  //    }
  //    ++iTrackTexIdx;
  //    ++iMapselOffset_1;
  //  } while (iTrackTexIdx < num_textures[19]);
  //}
  //iBldTexIdx = 0;
  //num_textures[19] = 0;                         // clear track tex count
  //
  //// Process bld textures
  //if (num_textures[17] > 0) {
  //  iBuildingMapselIdx = 0;
  //  do {
  //    // Check if selector is allocated
  //    if (mapsel[17][iBuildingMapselIdx]) {
  //      // free the selector
  //      regs.w.bx = mapsel[17][iBuildingMapselIdx];
  //      regs.w.ax = 1;
  //      int386(0x31, &regs, &regs);
  //
  //      // Clear the selector entry
  //      mapsel[17][iBuildingMapselIdx] = 0;
  //    }
  //    ++iBldTexIdx;
  //    ++iBuildingMapselIdx;
  //  } while (iBldTexIdx < num_textures[17]);
  //}
  //iCarGenTexIdx = 0;
  //num_textures[17] = 0;                         // clear building tex count
  //
  //// process car gen textures
  //if (num_textures[18] > 0) {
  //  iCarGenMapselIdx = 0;
  //  do {
  //    if (mapsel[18][iCarGenMapselIdx]) {
  //      // Free the selector
  //      regs.w.bx = mapsel[18][iCarGenMapselIdx];
  //      regs.w.ax = 1;
  //      int386(0x31, &regs, &regs);
  //
  //      // Clear the selector entry
  //      mapsel[18][iCarGenMapselIdx] = 0;
  //    }
  //    ++iCarGenTexIdx;
  //    ++iCarGenMapselIdx;
  //  } while (iCarGenTexIdx < num_textures[18]);
  //}
  //
  //// Clear car gen tex count
  //num_textures[18] = 0;
}

//-------------------------------------------------------------------------------------------------

void setmapsel(uint8 *pBase, int iIndex, int iMode, int iCount)
{
  int i;
  int iMapselOffset;
  uint8 *pTextureAddr;

  // Calculate starting offset in mapsel array for this texture type
  iMapselOffset = 257 * iIndex;

  // Store texture addresses for each texture block
  for (i = 0; i < iCount; i++) {
    // Calculate texture address based on mode
    if (iMode) {
      // Mode 1: 32x32 textures, 8 per row
      // Each texture is 1024 bytes, arranged in 8x8 grids
      int row = i >> 3;        // i / 8
      int col = i & 7;         // i % 8
      pTextureAddr = pBase + (row << 13) + (col << 5); // row * 8192 + col * 32
    } else {
      // Mode 0: 64x64 textures, 4 per row  
      // Each texture is 4096 bytes, arranged in 4x4 grids
      int row = i >> 2;        // i / 4
      int col = i & 3;         // i % 4
      pTextureAddr = pBase + (row << 14) + (col << 6); // row * 16384 + col * 64
    }

    // Store the texture address
    mapsel[0][iMapselOffset + i] = pTextureAddr;
  }

  //int iBaseAdjusted; // ebp
  //int iSuccess; // eax
  //int16 nCurrentSelector; // di
  //int i; // ecx
  //int iMapselOffset; // esi
  //int iMode_2; // edx
  //int iCoarseOffset; // ebx
  //int iFineOffset; // eax
  //int iSegmentBase; // ebx
  //union REGS regs; // [esp+0h] [ebp-34h] BYREF
  //int iCount_1; // [esp+1Ch] [ebp-18h]
  //int v15; // [esp+20h] [ebp-14h]
  //int iMode_1; // [esp+24h] [ebp-10h]
  //
  //iBaseAdjusted = iBase;
  //iMode_1 = iMode;
  //
  //// Adjust base address if running w95
  //if (w95)
  //  iBaseAdjusted = iBase - 0x10000;
  //iCount_1 = iCount;
  //regs.w.ax = 0;                                // allocate LDT descriptors
  //regs.w.cx = iCount;                           // Num descriptors to allocate
  //iSuccess = int386(0x31, &regs, &regs);
  //
  //// Check for carry flag set (error)
  //if ((*((_BYTE *)&regs.h + 24) & 1) != 0) {
  //  printf("Error allocating selectors");
  //  goto LABEL_15;
  //}
  //nCurrentSelector = regs.w.ax;
  //i = 0;
  //if (iCount_1 > 0) {
  //  for (iMapselOffset = 257 * iIndex; ; ++iMapselOffset) {
  //    iMode_2 = iMode_1;
  //    mapsel[iMapselOffset] = nCurrentSelector;
  //    // Calculate segment base address (platform-specific)
  //    if (iMode_2) {
  //      // Mode 1: 8-segment grouping
  //      iCoarseOffset = (i >> 3 << 13) + iBaseAdjusted;
  //      iFineOffset = 32 * (i & 7);
  //    } else {
  //      // Mode 0: 4-segment grouping
  //      iCoarseOffset = (i & 3) << 6;
  //      iFineOffset = iBaseAdjusted + (i >> 2 << 14);
  //    }
  //    iSegmentBase = iFineOffset + iCoarseOffset;
  //    v15 = 0x10000;
  //
  //    // Set segment base address
  //    regs.w.dx = iSegmentBase % 0x10000;
  //    regs.w.cx = (iSegmentBase - ((unsigned int)__CFSHL__(iSegmentBase >> 31, 16) + (iSegmentBase >> 31 << 16))) >> 16;
  //    regs.w.ax = 7;                            // set segment base address
  //    regs.w.bx = nCurrentSelector;
  //    int386(0x31, &regs, &regs);
  //    if ((*((_BYTE *)&regs.h + 24) & 1) != 0)
  //      break;
  //
  //    // Set segment limit
  //    regs.w.dx = 0xFFFF;                       // limit = 64KB-1
  //    regs.w.cx = 0;
  //    regs.w.ax = 8;
  //    regs.w.bx = nCurrentSelector;
  //    int386(0x31, &regs, &regs);
  //    if ((*((_BYTE *)&regs.h + 24) & 1) != 0)
  //      break;
  //
  //    // Get selector increment value
  //    regs.w.ax = 3;
  //    int386(0x31, &regs, &regs);
  //    ++i;
  //    nCurrentSelector += regs.w.ax;
  //    iSuccess = iCount_1;
  //    if (i >= iCount_1)
  //      return iSuccess;
  //  }
  //  printf("Error preparing selectors");
  //LABEL_15:
  //  __atexit();
  //  __int23_exit();
  //  __int23_exit();
  //  __FPE_handler_exit();
  //  JUMPOUT(0x7A98F);
  //}
  //return iSuccess;
}

//-------------------------------------------------------------------------------------------------

int twpolym(void *a1, int16 a2)
{
  return 0; /*
  __int16 v3; // bx
  __int16 v4; // si
  __int16 v5; // di
  int v6; // ebx
  int v7; // eax
  double v8; // st6
  double v9; // st6
  int v10; // eax
  int v11; // eax
  int v12; // ebx
  int *v13; // edi
  double v14; // st6
  double v15; // st6
  int v16; // eax
  int v17; // eax
  int result; // eax
  int v19; // ebp
  int v20; // eax
  double v21; // st6
  int v22; // eax
  int v23; // ebx
  _WORD *v24; // edi
  double v25; // st6
  int v26; // eax
  int v27; // eax
  int v28; // ebp
  int v29; // esi
  int v30; // [esp+0h] [ebp-9Ch]
  int v31; // [esp+4h] [ebp-98h]
  int v32; // [esp+8h] [ebp-94h]
  int v33; // [esp+Ch] [ebp-90h]
  int v34; // [esp+10h] [ebp-8Ch]
  int v35; // [esp+10h] [ebp-8Ch]
  int v36; // [esp+14h] [ebp-88h]
  int v37; // [esp+14h] [ebp-88h]
  int v38; // [esp+1Ch] [ebp-80h]
  int v39; // [esp+20h] [ebp-7Ch]
  float v40; // [esp+24h] [ebp-78h]
  float v41; // [esp+28h] [ebp-74h]
  int v42; // [esp+2Ch] [ebp-70h]
  int v43; // [esp+30h] [ebp-6Ch]
  int v44; // [esp+34h] [ebp-68h]
  int v45; // [esp+38h] [ebp-64h]
  int v46; // [esp+3Ch] [ebp-60h]
  int v47; // [esp+40h] [ebp-5Ch]
  int v48; // [esp+44h] [ebp-58h]
  int v49; // [esp+48h] [ebp-54h]
  int v50; // [esp+4Ch] [ebp-50h]
  int v51; // [esp+50h] [ebp-4Ch]
  int v52; // [esp+54h] [ebp-48h]
  int v53; // [esp+58h] [ebp-44h]
  int v54; // [esp+5Ch] [ebp-40h]
  int v55; // [esp+60h] [ebp-3Ch]
  float v56; // [esp+64h] [ebp-38h]
  float v57; // [esp+68h] [ebp-34h]
  __int16 v58; // [esp+6Ch] [ebp-30h]
  __int16 v59; // [esp+70h] [ebp-2Ch]
  __int16 v60; // [esp+74h] [ebp-28h]
  __int16 v61; // [esp+78h] [ebp-24h]
  __int16 v62; // [esp+7Ch] [ebp-20h]
  __int16 v63; // [esp+80h] [ebp-1Ch]
  __int16 v64; // [esp+84h] [ebp-18h]

  v3 = a1[4] - *a1;
  v60 = a1[8] - *a1;
  v58 = a1[12] - a1[8];
  v64 = v60 + v58;
  v61 = v3 - v60;
  v4 = a1[6] - a1[2];
  v5 = a1[10] - a1[2];
  v51 = 0;
  v59 = a1[14] - a1[10];
  v50 = 0;
  v62 = v5 + v59;
  v63 = v4 - v5;
  v41 = (float)(v59 * v3 - v4 * v58);
  if ((LODWORD(v41) & 0x7FFFFFFF) != 0 && (v51 = v60 * v4 - v5 * v3, v56 = (double)v51 / v41, v56 > 0.0) && v56 < 1.0) {
    v49 = startsx;
    v48 = startsy;
    v45 = startsx_variable_1;
    v47 = startsy_variable_1;
    v53 = startsx_variable_2;
    v52 = startsy_variable_2;
    v6 = startsy_variable_2;
    v32 = *(_DWORD *)a1;
    v33 = *((_DWORD *)a1 + 1);
    v38 = startsy_variable_3 - startsy_variable_2;
    v7 = startsx_variable_3 - startsx_variable_2;
    v39 = startsx_variable_3 - startsx_variable_2;
    if (v51 <= 0) {
      *(_DWORD *)a1 = *((_DWORD *)a1 + 4);
      *((_DWORD *)a1 + 1) = *((_DWORD *)a1 + 5);
      v14 = (double)v58 * v56 + (double)*((int *)a1 + 4);
      _CHP(v7, a2);
      *((_DWORD *)a1 + 4) = (int)v14;
      v15 = (double)v59 * v56 + (double)*((int *)a1 + 5);
      _CHP(v16, a2);
      *((_DWORD *)a1 + 5) = (int)v15;
      _CHP(v17, a2);
      startsx_variable_2 = (int)((double)v39 * v56 + (double)v53);
      startsy = v6;
      startsx_variable_1 = v45;
      _CHP(v45, 3);
      startsx = v53;
      startsy_variable_1 = v47;
      startsy_variable_2 = (int)(v56 * (double)v38 + (double)v52);
      polym(a1, 3, a2);
      v12 = a2;
      startsx_variable_1 = startsx_variable_3;
      *(_DWORD *)a1 = *((_DWORD *)a1 + 6);
      *((_DWORD *)a1 + 1) = *((_DWORD *)a1 + 7);
      startsx = v49;
      startsy_variable_1 = startsy_variable_3;
      v13 = (int *)(a1 + 4);
      startsy = v48;
    } else {
      *(_DWORD *)a1 = *((_DWORD *)a1 + 2);
      *((_DWORD *)a1 + 1) = *((_DWORD *)a1 + 3);
      *((_DWORD *)a1 + 2) = *((_DWORD *)a1 + 4);
      *((_DWORD *)a1 + 3) = *((_DWORD *)a1 + 5);
      v8 = (double)v58 * v56 + (double)*((int *)a1 + 4);
      _CHP(v7, a2);
      *((_DWORD *)a1 + 4) = (int)v8;
      v9 = (double)v59 * v56 + (double)*((int *)a1 + 5);
      _CHP(v10, a2);
      *((_DWORD *)a1 + 5) = (int)v9;
      _CHP(v11, a2);
      startsx_variable_2 = (int)((double)v39 * v56 + (double)v53);
      startsy_variable_1 = v6;
      startsx = v45;
      _CHP(v45, 3);
      startsx_variable_1 = v53;
      startsy = v47;
      startsy_variable_2 = (int)(v56 * (double)v38 + (double)v52);
      polym(a1, 3, a2);
      v12 = a2;
      startsx = startsx_variable_3;
      *(_DWORD *)a1 = *((_DWORD *)a1 + 6);
      *((_DWORD *)a1 + 1) = *((_DWORD *)a1 + 7);
      startsx_variable_1 = v49;
      startsy = startsy_variable_3;
      v13 = (int *)(a1 + 4);
      startsy_variable_1 = v48;
    }
    *v13 = v32;
    v13[1] = v33;
    polym(a1, 3, v12);
    startsx = v49;
    startsy = v48;
    startsx_variable_1 = v45;
    startsy_variable_1 = v47;
    startsx_variable_2 = v53;
    result = v52;
    startsy_variable_2 = v52;
  } else {
    v40 = (float)(v63 * v64 - v62 * v61);
    if ((LODWORD(v40) & 0x7FFFFFFF) != 0
      && (v19 = v60 * v62 - v64 * v5, v50 = v19, v57 = (double)v19 / v40, v57 > 0.0)
      && v57 < 1.0) {
      v44 = startsx;
      v46 = startsy;
      v42 = startsx_variable_1;
      v43 = startsy_variable_1;
      v55 = startsx_variable_2;
      v20 = startsy_variable_2;
      v54 = startsy_variable_2;
      if (v19 <= 0) {
        v35 = *(_DWORD *)a1;
        v37 = *((_DWORD *)a1 + 1);
        *(_DWORD *)a1 = *((_DWORD *)a1 + 2);
        *((_DWORD *)a1 + 1) = *((_DWORD *)a1 + 3);
        *((_DWORD *)a1 + 2) = v35;
        *((_DWORD *)a1 + 3) = v37;
        v34 = *((_DWORD *)a1 + 4);
        v36 = *((_DWORD *)a1 + 5);
        _CHP(v20, a2);
        *((_DWORD *)a1 + 4) = (int)((double)v61 * v57 + (double)v34);
        v25 = (double)v63 * v57 + (double)*((int *)a1 + 5);
        _CHP(v26, a2);
        startsx_variable_1 = v44;
        startsx = v42;
        *((_DWORD *)a1 + 5) = (int)v25;
        startsy_variable_1 = v46;
        startsy = v43;
        _CHP(v44 - v55, a2);
        startsx_variable_2 = (int)((double)(v44 - v55) * v57 + (double)v55);
        _CHP(v46 - v54, a2);
        startsy_variable_2 = (int)(v57 * (double)(v46 - v54) + (double)v54);
        polym(a1, 3, a2);
        v23 = a2;
        startsx_variable_1 = startsx_variable_3;
        *((_DWORD *)a1 + 2) = *((_DWORD *)a1 + 6);
        *((_DWORD *)a1 + 3) = *((_DWORD *)a1 + 7);
        startsx = v55;
        startsy_variable_1 = startsy_variable_3;
        v24 = a1;
        startsy = v54;
      } else {
        v34 = *((_DWORD *)a1 + 4);
        v36 = *((_DWORD *)a1 + 5);
        _CHP(startsy_variable_2, a2);
        *((_DWORD *)a1 + 4) = (int)((double)v61 * v57 + (double)v34);
        v21 = (double)v63 * v57 + (double)*((int *)a1 + 5);
        _CHP(v22, a2);
        *((_DWORD *)a1 + 5) = (int)v21;
        _CHP(v42 - v55, a2);
        startsx_variable_2 = (int)((double)(v42 - v55) * v57 + (double)v55);
        _CHP(v43 - v54, a2);
        startsy_variable_2 = (int)(v57 * (double)(v43 - v54) + (double)v54);
        polym(a1, 3, a2);
        v23 = a2;
        startsx = startsx_variable_3;
        *(_DWORD *)a1 = *((_DWORD *)a1 + 6);
        *((_DWORD *)a1 + 1) = *((_DWORD *)a1 + 7);
        startsx_variable_1 = v55;
        startsy = startsy_variable_3;
        v24 = a1 + 4;
        startsy_variable_1 = v54;
      }
      *(_DWORD *)v24 = v34;
      *((_DWORD *)v24 + 1) = v36;
      polym(a1, 3, v23);
      startsx = v44;
      startsy = v46;
      startsx_variable_1 = v42;
      startsy_variable_1 = v43;
      startsx_variable_2 = v55;
      result = v54;
      startsy_variable_2 = v54;
    } else if (v51 >= 0 && v50 <= 0) {
      return polym(a1, 4, a2);
    } else {
      v30 = *((_DWORD *)a1 + 2);
      v31 = *((_DWORD *)a1 + 3);
      v27 = startsx_variable_3;
      *((_DWORD *)a1 + 2) = *((_DWORD *)a1 + 6);
      *((_DWORD *)a1 + 3) = *((_DWORD *)a1 + 7);
      v28 = startsy_variable_1;
      *((_DWORD *)a1 + 6) = v30;
      *((_DWORD *)a1 + 7) = v31;
      v29 = startsx_variable_1;
      startsx_variable_1 = v27;
      startsx_variable_3 = v29;
      startsy_variable_1 = startsy_variable_3;
      startsy_variable_3 = v28;
      polym(a1, 4, a2);
      startsx_variable_3 = startsx_variable_1;
      result = startsy_variable_1;
      startsx_variable_1 = v29;
      startsy_variable_3 = startsy_variable_1;
      startsy_variable_1 = v28;
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

char POLYTEX(int a1, int a2, int *a3, int a4, int a5)
{
  return 0; /*
  int result; // eax
  int v8; // edx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  int v14; // edx
  int v15; // ecx
  int v16; // edx
  int v17; // edx
  int v18; // edx
  int v19; // edx
  int v20; // ecx
  int v21; // eax
  int *v22; // edx
  int v23; // ebx
  int v24; // eax
  int v25; // eax
  int v26; // [esp+4h] [ebp-18h]
  char v27; // [esp+8h] [ebp-14h]
  char v28; // [esp+Ch] [ebp-10h]

  result = *a3;
  if ((unsigned __int8)*a3 >= NoOfTextures && (result & 0x20000) == 0 && !a4
    || (unsigned __int8)result >= BldTextures && (result & 0x20000) == 0 && a4 == 17) {
    *a3 = (unsigned __int8)*a3;
    POLYFLAT(a2, a3);
    result = 0x20000;
  }
  if ((result & 0x20000) == 0) {
    scrptr = a2;
    scrptr1 = winw + a2;
    if ((result & 0x1000) != 0)
      v28 = -1;
    else
      v28 = 0;
    if ((result & 0x40000) != 0)
      v27 = -1;
    else
      v27 = 0;
    if ((result & 0x2000) != 0) {
      v8 = a3[2];
      v9 = a3[3];
      v26 = v9 - a3[5];
      if (a3[4] == a3[6] && a3[5] == a3[7]) {
        v10 = v8 - a3[8];
        v11 = v9 - a3[9];
      } else {
        v10 = v8 - a3[6];
        v11 = v9 - a3[7];
      }
      if ((a3[2] - a3[4]) * v11 > v26 * v10) {
        v12 = a3[2];
        a3[2] = a3[4];
        a3[4] = v12;
        v13 = a3[3];
        a3[3] = a3[5];
        a3[5] = v13;
        v14 = a3[6];
        a3[6] = a3[8];
        a3[8] = v14;
        v15 = a3[7];
        a3[7] = a3[9];
        a3[9] = v15;
        v28 = v28 == 0;
        if ((result & 0x800) != 0) {
          result = texture_back[256 * a4 + (unsigned __int8)result];
          BYTE1(result) |= 0x20u;
        }
      }
    }
    if (v28) {
      v16 = startsx_variable_1;
      startsx_variable_1 = startsx;
      startsx = v16;
      v17 = startsx_variable_3;
      startsx_variable_3 = startsx_variable_2;
      startsx_variable_2 = v17;
    }
    if (v27) {
      v18 = startsy_variable_2;
      startsy_variable_2 = startsy;
      startsy = v18;
      v19 = startsy_variable_3;
      startsy_variable_3 = startsy_variable_1;
      startsy_variable_1 = v19;
    }
    ++num_pols;
    if ((result & 0x400) != 0) {
      if (a5) {
        v20 = (int)(unsigned __int8)result >> 3 << 13;
        v21 = 32 * (result & 7);
      } else {
        v20 = (int)(unsigned __int8)result >> 2 << 14;
        v21 = (result & 3) << 6;
      }
      result = polyt(a3 + 2, 4, v20 + v21 + a1);
    } else {
      v22 = a3 + 2;
      v23 = 514 * a4 + 2 * (unsigned __int8)result;
      if ((result & 0x4000) != 0)
        result = twpolym(v22, *(__int16 *)((char *)mapsel + v23));
      else
        result = polym(v22, 4, *(__int16 *)((char *)mapsel + v23));
    }
    if (v28) {
      v24 = startsx_variable_1;
      startsx_variable_1 = startsx;
      startsx = v24;
      result = startsx_variable_3;
      startsx_variable_3 = startsx_variable_2;
      startsx_variable_2 = result;
    }
    if (v27) {
      v25 = startsy_variable_2;
      startsy_variable_2 = startsy;
      startsy = v25;
      result = startsy_variable_3;
      startsy_variable_3 = startsy_variable_1;
      startsy_variable_1 = result;
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

char polym(int *a1, int a2, int a3)
{
  return 0; /*
  int *v3; // ebp
  int v4; // ecx
  int v5; // esi
  int v6; // edx
  int v7; // edi
  int *v8; // eax
  int v9; // ebx
  int v10; // eax
  signed int v11; // eax
  int *v12; // edx
  int v13; // ebx
  int v14; // edx
  int v15; // ecx
  int v16; // edx
  __int16 v17; // dx
  int v18; // esi
  int v19; // eax
  int v20; // edx
  int v21; // esi
  int v22; // edx
  int v23; // edx
  int v24; // ebx
  int v25; // eax
  int v26; // edx
  int v27; // ebx
  int v28; // edx
  int v29; // eax
  int v30; // edx
  int v31; // edx
  int v32; // eax
  int v33; // esi
  signed int v34; // eax
  int *v35; // edx
  __int16 v36; // ax
  int v37; // ecx
  int v38; // edx
  int v39; // eax
  int v40; // edx
  int v41; // ecx
  int v42; // edx
  int v43; // eax
  int *v44; // edx
  int v45; // ecx
  int v46; // edx
  int v47; // eax
  int v48; // ecx
  int v49; // edx
  __int64 v50; // rtt
  int v51; // edx
  signed int v52; // ebx
  int v53; // edx
  int v54; // edx
  int v55; // ecx
  int v56; // edx
  int v57; // eax
  int v58; // edx
  int v59; // ecx
  int v60; // edx
  int v61; // edx
  __int16 v62; // cx
  int v63; // edx
  int v64; // eax
  int v65; // edx
  __int16 v66; // ax
  int v67; // ecx
  int v68; // edx
  int v69; // eax
  int v70; // ecx
  int v71; // edx
  __int64 v72; // rtt
  int v73; // edx
  int v74; // ecx
  int v75; // edx
  int v76; // eax
  int v77; // edx
  unsigned int v78; // eax
  int v79; // ebx
  unsigned int v80; // esi
  __int16 v81; // di
  _DWORD *v82; // ebp
  _BOOL1 v83; // cf
  _BYTE *v84; // ebx
  int v85; // ecx
  unsigned int v86; // edx
  _BYTE *v87; // ebx
  unsigned int v88; // kr00_4
  unsigned int v89; // edx
  _BYTE *v90; // ebx
  int v91; // ett
  unsigned __int32 v92; // eax
  unsigned int v93; // edx
  bool v94; // ett
  _BYTE *v95; // ebx
  bool v96; // ett
  unsigned int v97; // edx
  bool v98; // ett
  _BYTE *v99; // ebx
  bool v100; // ett
  __int16 v101; // ax
  int v102; // ebx
  unsigned int v103; // esi
  unsigned __int16 v104; // di
  _WORD *v105; // ebp
  char *v106; // ebx
  int v107; // ecx
  unsigned int v108; // edx
  char v109; // al
  __int16 v110; // ax
  _BYTE *v111; // ebx
  unsigned int v112; // kr18_4
  _BYTE *v113; // ebx
  int v114; // ett
  _BYTE *v115; // ebx
  unsigned int v116; // kr20_4
  unsigned int v117; // edx
  _BYTE *v118; // ebx
  int v119; // ett
  unsigned int v120; // edx
  bool v121; // ett
  _BYTE *v122; // ebx
  bool v123; // ett
  unsigned int v124; // edx
  bool v125; // ett
  _BYTE *v126; // ebx
  bool v127; // ett
  unsigned __int16 i; // di
  _BYTE *v129; // ebx
  unsigned int v130; // kr28_4
  unsigned int v131; // edx
  _BYTE *v132; // ebx
  int v133; // ett
  unsigned int v134; // eax
  unsigned int v135; // edx
  bool v136; // ett
  _BYTE *v137; // ebx
  bool v138; // ett
  unsigned int v139; // edx
  bool v140; // ett
  _BYTE *v141; // ebx
  bool v142; // ett
  unsigned int v143; // edx
  bool v144; // ett
  _BYTE *v145; // ebx
  bool v146; // ett
  unsigned int v147; // edx
  bool v148; // ett
  _BYTE *v149; // ebx
  bool v150; // ett
  unsigned int v151; // edx
  bool v152; // ett
  _BYTE *v153; // ebx
  bool v154; // ett
  int v155; // edx
  bool v156; // ett
  _BYTE *v157; // ebx
  bool v158; // ett
  _BYTE *v159; // ebx
  unsigned int v160; // kr30_4
  unsigned int v161; // edx
  _BYTE *v162; // ebx
  int v163; // ett
  unsigned __int32 v164; // eax
  unsigned int v165; // edx
  bool v166; // ett
  _BYTE *v167; // ebx
  bool v168; // ett
  unsigned int v169; // edx
  bool v170; // ett
  _BYTE *v171; // ebx
  bool v172; // ett
  __int16 v173; // ax
  int v174; // edx
  int v175; // ebx
  int v176; // ecx
  int v177; // esi
  int v178; // eax
  int v179; // edi
  int v180; // edx
  int v181; // eax
  int v182; // ebx
  int v183; // eax
  int v184; // ecx
  int v185; // eax
  int v186; // ecx
  int v187; // esi
  int v188; // eax
  int v189; // edi
  int v190; // esi
  int v191; // eax
  int v192; // eax
  int v193; // ecx
  int v194; // ebx
  int v195; // edx
  int v196; // eax
  int v197; // ebx
  int v198; // edx
  int v199; // eax
  int v200; // ebx
  int v201; // edi
  int v202; // ecx
  int v203; // eax
  int v204; // edi
  int v205; // edi
  int v206; // eax
  int v207; // edx
  int v208; // ebx
  int v209; // eax
  int v210; // ecx
  int v211; // edx
  int v212; // eax
  int v213; // ecx
  int v214; // ebx
  int v215; // edx
  int v216; // eax
  int v217; // ebx
  int v218; // edx
  int v219; // edx
  int v220; // eax
  int v221; // ebx
  int v222; // ecx
  int v223; // ecx
  int v224; // eax
  int v225; // esi
  int v226; // edx
  int v227; // edi
  int v228; // eax
  int v229; // edx
  int v230; // ecx
  int v231; // eax
  int v232; // esi
  int v233; // edx
  __int64 v234; // rtt
  int v235; // edx
  int v236; // ecx
  int v237; // esi
  int v238; // edx
  int v239; // eax
  int v240; // edx
  int v241; // ebx
  unsigned int v242; // esi
  __int16 v243; // di
  _DWORD *v244; // ebp
  _BYTE *v245; // ebx
  int v246; // ecx
  unsigned int v247; // edx
  _BYTE *v248; // ebx
  unsigned int v249; // kr40_4
  unsigned int v250; // edx
  _BYTE *v251; // ebx
  int v252; // ett
  unsigned int v253; // edx
  bool v254; // ett
  _BYTE *v255; // ebx
  bool v256; // ett
  unsigned int v257; // edx
  bool v258; // ett
  _BYTE *v259; // ebx
  bool v260; // ett
  int v261; // ebx
  int v262; // ecx
  int v263; // edx
  int v264; // edx
  unsigned int v265; // eax
  int v266; // ebx
  unsigned int v267; // esi
  __int16 v268; // di
  _DWORD *v269; // ebp
  _BYTE *v270; // ebx
  int v271; // ecx
  unsigned int v272; // edx
  _BYTE *v273; // ebx
  unsigned int v274; // kr50_4
  unsigned int v275; // edx
  _BYTE *v276; // ebx
  int v277; // ett
  unsigned __int32 v278; // eax
  unsigned int v279; // edx
  bool v280; // ett
  _BYTE *v281; // ebx
  bool v282; // ett
  unsigned int v283; // edx
  bool v284; // ett
  _BYTE *v285; // ebx
  bool v286; // ett
  __int16 v287; // ax
  int v288; // ebx
  unsigned int v289; // esi
  unsigned __int16 v290; // di
  _WORD *v291; // ebp
  char *v292; // ebx
  int v293; // ecx
  unsigned int v294; // edx
  char v295; // al
  __int16 v296; // ax
  _BYTE *v297; // ebx
  unsigned int v298; // kr68_4
  _BYTE *v299; // ebx
  int v300; // ett
  _BYTE *v301; // ebx
  unsigned int v302; // kr70_4
  unsigned int v303; // edx
  _BYTE *v304; // ebx
  int v305; // ett
  unsigned int v306; // edx
  bool v307; // ett
  _BYTE *v308; // ebx
  bool v309; // ett
  unsigned int v310; // edx
  bool v311; // ett
  _BYTE *v312; // ebx
  bool v313; // ett
  unsigned __int16 j; // di
  _BYTE *v315; // ebx
  unsigned int v316; // kr78_4
  unsigned int v317; // edx
  _BYTE *v318; // ebx
  int v319; // ett
  unsigned int v320; // eax
  unsigned int v321; // edx
  bool v322; // ett
  _BYTE *v323; // ebx
  bool v324; // ett
  unsigned int v325; // edx
  bool v326; // ett
  _BYTE *v327; // ebx
  bool v328; // ett
  unsigned int v329; // edx
  bool v330; // ett
  _BYTE *v331; // ebx
  bool v332; // ett
  unsigned int v333; // edx
  bool v334; // ett
  _BYTE *v335; // ebx
  bool v336; // ett
  unsigned int v337; // edx
  bool v338; // ett
  _BYTE *v339; // ebx
  bool v340; // ett
  int v341; // edx
  bool v342; // ett
  _BYTE *v343; // ebx
  bool v344; // ett
  _BYTE *v345; // ebx
  unsigned int v346; // kr80_4
  unsigned int v347; // edx
  _BYTE *v348; // ebx
  int v349; // ett
  unsigned __int32 v350; // eax
  unsigned int v351; // edx
  bool v352; // ett
  _BYTE *v353; // ebx
  bool v354; // ett
  unsigned int v355; // edx
  bool v356; // ett
  _BYTE *v357; // ebx
  bool v358; // ett
  __int16 v359; // ax
  int v360; // edx
  int v361; // ebx
  int v362; // ecx
  int v363; // esi
  int v364; // eax
  int v365; // edi
  int v366; // edx
  int v367; // eax
  int v368; // ebx
  int v369; // eax
  int v370; // ecx
  int v371; // eax
  int v372; // esi
  int v373; // eax
  int v374; // esi
  int v375; // edi
  int v376; // eax
  int v377; // edi
  int v378; // eax
  int v379; // ecx
  int v380; // ebx
  int v381; // edx
  int v382; // eax
  int v383; // ebx
  int v384; // edx
  int v385; // eax
  int v386; // ebx
  int v387; // edi
  int v388; // ecx
  int v389; // eax
  int v390; // edi
  int v391; // edi
  int v392; // eax
  int v393; // edx
  int v394; // ebx
  int v395; // eax
  int v396; // ecx
  int v397; // edx
  int v398; // eax
  int v399; // ecx
  int v400; // ebx
  int v401; // edx
  int v402; // eax
  int v403; // ebx
  int v404; // edx
  int v405; // edx
  int v406; // eax
  int v407; // ebx
  int v408; // ecx
  int v409; // ecx
  int v410; // eax
  int v411; // esi
  int v412; // edx
  int v413; // edi
  int v414; // eax
  int v415; // edx
  int v416; // ecx
  int v417; // eax
  int v418; // esi
  int v419; // edx
  __int64 v420; // rtt
  int v421; // edx
  int v422; // ebx
  int v423; // ecx
  int v424; // edx
  int v425; // edx
  int v426; // ebx
  unsigned int v427; // esi
  __int16 v428; // di
  _DWORD *v429; // ebp
  _BYTE *v430; // ebx
  int v431; // ecx
  unsigned int v432; // edx
  _BYTE *v433; // ebx
  unsigned int v434; // kr90_4
  unsigned int v435; // edx
  _BYTE *v436; // ebx
  int v437; // ett
  unsigned int v438; // edx
  bool v439; // ett
  _BYTE *v440; // ebx
  bool v441; // ett
  unsigned int v442; // edx
  bool v443; // ett
  _BYTE *v444; // ebx
  bool v445; // ett
  int v446; // edx
  int v447; // ebx
  int v448; // ecx
  int v449; // eax
  int v450; // edx
  int v451; // ebx
  unsigned int v452; // eax
  int v453; // ebx
  unsigned int v454; // esi
  __int16 v455; // di
  _DWORD *v456; // ebp
  _BYTE *v457; // ebx
  int v458; // ecx
  unsigned int v459; // edx
  _BYTE *v460; // ebx
  unsigned int v461; // krA0_4
  unsigned int v462; // edx
  _BYTE *v463; // ebx
  int v464; // ett
  unsigned __int32 v465; // eax
  unsigned int v466; // edx
  bool v467; // ett
  _BYTE *v468; // ebx
  bool v469; // ett
  unsigned int v470; // edx
  bool v471; // ett
  _BYTE *v472; // ebx
  bool v473; // ett
  __int16 v474; // ax
  int v475; // ebx
  unsigned int v476; // esi
  unsigned __int16 v477; // di
  _WORD *v478; // ebp
  char *v479; // ebx
  int v480; // ecx
  unsigned int v481; // edx
  char v482; // al
  __int16 v483; // ax
  _BYTE *v484; // ebx
  unsigned int v485; // krB8_4
  _BYTE *v486; // ebx
  int v487; // ett
  _BYTE *v488; // ebx
  unsigned int v489; // krC0_4
  unsigned int v490; // edx
  _BYTE *v491; // ebx
  int v492; // ett
  unsigned int v493; // edx
  bool v494; // ett
  _BYTE *v495; // ebx
  bool v496; // ett
  unsigned int v497; // edx
  bool v498; // ett
  _BYTE *v499; // ebx
  bool v500; // ett
  unsigned __int16 m; // di
  _BYTE *v502; // ebx
  unsigned int v503; // krC8_4
  unsigned int v504; // edx
  _BYTE *v505; // ebx
  int v506; // ett
  unsigned int v507; // eax
  unsigned int v508; // edx
  bool v509; // ett
  _BYTE *v510; // ebx
  bool v511; // ett
  unsigned int v512; // edx
  bool v513; // ett
  _BYTE *v514; // ebx
  bool v515; // ett
  unsigned int v516; // edx
  bool v517; // ett
  _BYTE *v518; // ebx
  bool v519; // ett
  unsigned int v520; // edx
  bool v521; // ett
  _BYTE *v522; // ebx
  bool v523; // ett
  unsigned int v524; // edx
  bool v525; // ett
  _BYTE *v526; // ebx
  bool v527; // ett
  int v528; // edx
  bool v529; // ett
  _BYTE *v530; // ebx
  bool v531; // ett
  _BYTE *v532; // ebx
  unsigned int v533; // krD0_4
  unsigned int v534; // edx
  _BYTE *v535; // ebx
  int v536; // ett
  unsigned __int32 v537; // eax
  unsigned int v538; // edx
  bool v539; // ett
  _BYTE *v540; // ebx
  bool v541; // ett
  unsigned int v542; // edx
  bool v543; // ett
  _BYTE *v544; // ebx
  bool v545; // ett
  __int16 v546; // ax
  int v547; // ebx
  int v548; // ecx
  int v549; // esi
  int v550; // edi
  int v551; // eax
  int v552; // edx
  int v553; // ebx
  int v554; // eax
  int v555; // ecx
  int v556; // eax
  int v557; // ebx
  int v558; // esi
  int v559; // eax
  int v560; // esi
  int v561; // edi
  int v562; // eax
  int v563; // edi
  int v564; // eax
  int v565; // ebx
  _WORD *v566; // edx
  int v567; // ecx
  int v568; // edx
  int v569; // eax
  int v570; // ebx
  int v571; // edx
  __int16 v572; // ax
  int v573; // ebx
  int v574; // eax
  int v575; // ecx
  int v576; // eax
  int v577; // edx
  int v578; // edi
  int v579; // eax
  int v580; // edx
  int v581; // ebx
  int v582; // eax
  int v583; // ecx
  int v584; // edx
  int v585; // eax
  int v586; // ecx
  int v587; // ebx
  int v588; // edx
  int v589; // eax
  int v590; // ebx
  int v591; // edx
  int v592; // edx
  int v593; // eax
  int v594; // ebx
  int v595; // ecx
  int v596; // ecx
  int v597; // eax
  int v598; // esi
  int v599; // edx
  int v600; // edi
  int v601; // eax
  int v602; // edx
  int v603; // ecx
  int v604; // eax
  int v605; // esi
  int v606; // edx
  __int64 v607; // rtt
  int v608; // edx
  int v609; // ecx
  int v610; // esi
  int v611; // edx
  int v612; // edi
  int v613; // eax
  int v614; // ebx
  int v615; // ebx
  unsigned int v616; // esi
  __int16 v617; // di
  _DWORD *v618; // ebp
  _BYTE *v619; // ebx
  int v620; // ecx
  unsigned int v621; // edx
  _BYTE *v622; // ebx
  unsigned int v623; // krE0_4
  unsigned int v624; // edx
  _BYTE *v625; // ebx
  int v626; // ett
  unsigned int v627; // edx
  bool v628; // ett
  _BYTE *v629; // ebx
  bool v630; // ett
  unsigned int v631; // edx
  bool v632; // ett
  _BYTE *v633; // ebx
  bool v634; // ett
  int v635; // edi
  int v636; // edx
  int v637; // eax
  unsigned int v638; // eax
  int v639; // ebx
  unsigned int v640; // esi
  __int16 v641; // di
  _DWORD *v642; // ebp
  _BYTE *v643; // ebx
  int v644; // ecx
  unsigned int v645; // edx
  _BYTE *v646; // ebx
  unsigned int v647; // krF0_4
  unsigned int v648; // edx
  _BYTE *v649; // ebx
  int v650; // ett
  unsigned __int32 v651; // eax
  unsigned int v652; // edx
  bool v653; // ett
  _BYTE *v654; // ebx
  bool v655; // ett
  unsigned int v656; // edx
  bool v657; // ett
  _BYTE *v658; // ebx
  bool v659; // ett
  __int16 v660; // ax
  int v661; // ebx
  unsigned int v662; // esi
  unsigned __int16 v663; // di
  _WORD *v664; // ebp
  char *v665; // ebx
  int v666; // ecx
  unsigned int v667; // edx
  char v668; // al
  __int16 v669; // ax
  _BYTE *v670; // ebx
  unsigned int v671; // kr108_4
  _BYTE *v672; // ebx
  int v673; // ett
  _BYTE *v674; // ebx
  unsigned int v675; // kr110_4
  unsigned int v676; // edx
  _BYTE *v677; // ebx
  int v678; // ett
  unsigned int v679; // edx
  bool v680; // ett
  _BYTE *v681; // ebx
  bool v682; // ett
  unsigned int v683; // edx
  bool v684; // ett
  _BYTE *v685; // ebx
  bool v686; // ett
  unsigned __int16 k; // di
  _BYTE *v688; // ebx
  unsigned int v689; // kr118_4
  unsigned int v690; // edx
  _BYTE *v691; // ebx
  int v692; // ett
  unsigned int v693; // eax
  unsigned int v694; // edx
  bool v695; // ett
  _BYTE *v696; // ebx
  bool v697; // ett
  unsigned int v698; // edx
  bool v699; // ett
  _BYTE *v700; // ebx
  bool v701; // ett
  unsigned int v702; // edx
  bool v703; // ett
  _BYTE *v704; // ebx
  bool v705; // ett
  unsigned int v706; // edx
  bool v707; // ett
  _BYTE *v708; // ebx
  bool v709; // ett
  unsigned int v710; // edx
  bool v711; // ett
  _BYTE *v712; // ebx
  bool v713; // ett
  int v714; // edx
  bool v715; // ett
  _BYTE *v716; // ebx
  bool v717; // ett
  _BYTE *v718; // ebx
  unsigned int v719; // kr120_4
  unsigned int v720; // edx
  _BYTE *v721; // ebx
  int v722; // ett
  unsigned __int32 v723; // eax
  unsigned int v724; // edx
  bool v725; // ett
  _BYTE *v726; // ebx
  bool v727; // ett
  unsigned int v728; // edx
  bool v729; // ett
  _BYTE *v730; // ebx
  bool v731; // ett
  __int16 v732; // ax
  int v733; // edi
  int v734; // edx
  int v735; // ebx
  int v736; // ecx
  int v737; // eax
  int v738; // esi
  int v739; // edi
  int v740; // eax
  int v741; // edx
  int v742; // eax
  int v743; // edi
  int v744; // ebx
  int v745; // eax
  int v746; // ecx
  int v747; // eax
  int v748; // esi
  int v749; // eax
  int v750; // esi
  int v751; // eax
  int v752; // edi
  int v753; // ecx
  __int16 v754; // dx
  int v755; // edx
  int v756; // eax
  int v757; // ebx
  int v758; // edx
  int v759; // eax
  int v760; // ebx
  int v761; // edi
  int v762; // ecx
  int v763; // eax
  int v764; // edi
  int v765; // edi
  int v766; // eax
  int v767; // edx
  int v768; // ebx
  int v769; // eax
  int v770; // ecx
  int v771; // edx
  int v772; // eax
  int v773; // edx
  int v774; // ecx
  int v775; // ebx
  int v776; // eax
  int v777; // ebx
  int v778; // ecx
  int v779; // ecx
  int v780; // ebx
  __int16 v781; // ax
  int v782; // esi
  int v783; // ecx
  int v784; // eax
  int v785; // esi
  int v786; // edx
  int v787; // edi
  int v788; // eax
  int v789; // edx
  int v790; // ecx
  int v791; // edx
  int v792; // eax
  int v793; // edx
  int v794; // ebx
  int v795; // ecx
  int v796; // eax
  int v797; // edx
  int v798; // ebx
  unsigned int v799; // esi
  __int16 v800; // di
  _DWORD *v801; // ebp
  _BYTE *v802; // ebx
  int v803; // ecx
  unsigned int v804; // edx
  _BYTE *v805; // ebx
  unsigned int v806; // kr130_4
  unsigned int v807; // edx
  _BYTE *v808; // ebx
  int v809; // ett
  unsigned int v810; // edx
  bool v811; // ett
  _BYTE *v812; // ebx
  bool v813; // ett
  unsigned int v814; // edx
  bool v815; // ett
  _BYTE *v816; // ebx
  bool v817; // ett
  int v818; // ebx
  unsigned int v819; // esi
  unsigned __int16 v820; // di
  _WORD *v821; // ebp
  _BYTE *v822; // ebx
  int v823; // ecx
  unsigned int v824; // edx
  _BYTE *v825; // ebx
  unsigned int v826; // kr148_4
  _BYTE *v827; // ebx
  int v828; // ett
  _BYTE *v829; // ebx
  unsigned int v830; // kr150_4
  unsigned int v831; // edx
  _BYTE *v832; // ebx
  int v833; // ett
  unsigned int v834; // edx
  bool v835; // ett
  _BYTE *v836; // ebx
  bool v837; // ett
  unsigned int v838; // edx
  bool v839; // ett
  _BYTE *v840; // ebx
  bool v841; // ett
  unsigned __int16 n; // di
  _BYTE *v843; // ebx
  unsigned int v844; // kr158_4
  unsigned int v845; // edx
  _BYTE *v846; // ebx
  int v847; // ett
  unsigned int v848; // eax
  unsigned int v849; // edx
  bool v850; // ett
  _BYTE *v851; // ebx
  bool v852; // ett
  unsigned int v853; // edx
  bool v854; // ett
  _BYTE *v855; // ebx
  bool v856; // ett
  unsigned int v857; // edx
  bool v858; // ett
  _BYTE *v859; // ebx
  bool v860; // ett
  unsigned int v861; // edx
  bool v862; // ett
  _BYTE *v863; // ebx
  bool v864; // ett
  unsigned int v865; // edx
  bool v866; // ett
  _BYTE *v867; // ebx
  bool v868; // ett
  int v869; // edx
  bool v870; // ett
  _BYTE *v871; // ebx
  bool v872; // ett
  _BYTE *v873; // ebx
  unsigned int v874; // kr160_4
  unsigned int v875; // edx
  _BYTE *v876; // ebx
  int v877; // ett
  unsigned int v878; // edx
  bool v879; // ett
  _BYTE *v880; // ebx
  bool v881; // ett
  unsigned int v882; // edx
  bool v883; // ett
  _BYTE *v884; // ebx
  bool v885; // ett
  __int16 v887; // [esp-8h] [ebp-64h]
  __int16 v888; // [esp-8h] [ebp-64h]
  __int16 v889; // [esp-8h] [ebp-64h]
  __int16 v890; // [esp-8h] [ebp-64h]
  __int16 v891; // [esp-8h] [ebp-64h]
  __int16 v892; // [esp-8h] [ebp-64h]
  __int16 v893; // [esp-8h] [ebp-64h]
  __int16 v894; // [esp-8h] [ebp-64h]
  int *v895; // [esp-4h] [ebp-60h]
  int *v896; // [esp-4h] [ebp-60h]
  int *v897; // [esp-4h] [ebp-60h]
  int *v898; // [esp-4h] [ebp-60h]
  int *v899; // [esp-4h] [ebp-60h]
  int *v900; // [esp-4h] [ebp-60h]
  int *v901; // [esp-4h] [ebp-60h]
  int *v902; // [esp-4h] [ebp-60h]
  int v903; // [esp+4h] [ebp-58h]
  int v904; // [esp+8h] [ebp-54h]
  int v905; // [esp+Ch] [ebp-50h]
  int v906; // [esp+10h] [ebp-4Ch]
  int *v907; // [esp+14h] [ebp-48h]
  int v908; // [esp+18h] [ebp-44h]
  int v909; // [esp+1Ch] [ebp-40h]
  int v910; // [esp+20h] [ebp-3Ch]
  int v911; // [esp+24h] [ebp-38h]
  int v912; // [esp+28h] [ebp-34h]
  int v913; // [esp+2Ch] [ebp-30h]
  int v914; // [esp+30h] [ebp-2Ch]
  int v915; // [esp+34h] [ebp-28h]
  int v916; // [esp+38h] [ebp-24h]
  int v917; // [esp+3Ch] [ebp-20h]
  int v918; // [esp+44h] [ebp-18h]
  int v919; // [esp+48h] [ebp-14h]
  signed int v920; // [esp+4Ch] [ebp-10h]
  int v921; // [esp+50h] [ebp-Ch]
  int v922; // [esp+54h] [ebp-8h]
  int v923; // [esp+58h] [ebp-4h]
  int vars0; // [esp+5Ch] [ebp+0h] BYREF

  v3 = &vars0;
  v907 = a1;
  v918 = a2;
  v923 = a3;
  v4 = *a1;
  v919 = 0;
  v5 = v4;
  v6 = a1[1];
  v922 = 1;
  v7 = v6;
  while (1) {
    LOBYTE(v11) = v922;
    if ((__int16)v922 >= (__int16)v918)
      break;
    v8 = &v907[2 * (__int16)v922];
    v9 = *v8;
    v10 = v8[1];
    if (v9 <= v5) {
      if (v9 < v4)
        v4 = v9;
    } else {
      v5 = v9;
    }
    if (v10 <= v7) {
      if (v10 < v6) {
        v6 = v10;
        v919 = v922;
      }
    } else {
      v7 = v10;
    }
    ++v922;
  }
  if (v5 >= 0 && v7 >= 0 && v4 < winw && v6 < winh) {
    v921 = v919;
    v12 = &v907[2 * (__int16)v919];
    v13 = v12[1];
    v910 = v13;
    if (v13 >= 0) {
      HIWORD(v916) = *(_WORD *)v12;
      HIWORD(v915) = HIWORD(v916);
      LOWORD(v915) = 0;
      LOWORD(v916) = -1;
      LOWORD(v913) = 0;
      v31 = startsx[(__int16)v919];
      LOWORD(v914) = 0;
      v911 = v31;
      v32 = startsy[(__int16)v919];
      v909 = v31;
      v912 = v32;
      while (1) {
        v908 = v32;
        v33 = v915;
        if ((_WORD)++v919 == (_WORD)v918)
          v919 = 0;
        HIWORD(v34) = HIWORD(v907);
        v35 = &v907[2 * (__int16)v919];
        LOWORD(v34) = *((_WORD *)v35 + 2) - v910;
        v920 = v34;
        if ((_WORD)v34)
          break;
        if ((_WORD)v919 == (_WORD)v921)
          goto LABEL_140;
        HIWORD(v915) = *(_WORD *)v35;
        v909 = startsx[(__int16)v919];
        v32 = startsy[(__int16)v919];
      }
      v36 = *(_WORD *)v35 - HIWORD(v915);
      HIWORD(v914) = v36;
      if (v914 >= 0) {
        HIWORD(v914) = v36 + 1;
        v41 = (__int16)v920 + 1;
        v42 = startsx[(__int16)v919] - v909;
        v914 /= v41;
        v903 = v42 / v41;
        v906 = (startsy[(__int16)v919] - v908) / v41;
      } else {
        HIWORD(v914) = v36 - 1;
        v37 = (__int16)v920 + 1;
        v915 += v914 / v37;
        ++HIWORD(v915);
        v38 = startsx[(__int16)v919] - v909;
        v914 /= v37;
        v39 = v38 / v37;
        v909 += v38 / v37;
        v40 = startsy[(__int16)v919];
        v903 = v39;
        v906 = (v40 - v908) / v37;
        v908 += v906;
      }
      while (1) {
        v43 = (__int16)--v921;
        if ((__int16)v921 == -1) {
          v43 = v918 - 1;
          v921 = v918 - 1;
        }
        v44 = &v907[2 * (__int16)v921];
        LOWORD(v43) = *((_WORD *)v44 + 2) - v910;
        v917 = v43;
        if ((_WORD)v43) {
          HIWORD(v913) = *(_WORD *)v44 - HIWORD(v916);
          if (v913 <= 0) {
            --HIWORD(v913);
            v48 = (__int16)v917 + 1;
            v49 = startsx[(__int16)v921] - v911;
            v913 /= v48;
            v50 = v49;
            ++HIWORD(v916);
            v51 = startsy[(__int16)v921] - v912;
            v904 = v50 / v48;
            v905 = v51 / v48;
          } else {
            ++HIWORD(v913);
            v45 = (__int16)v917 + 1;
            v916 += v913 / v45;
            v46 = startsx[(__int16)v921] - v911;
            v913 /= v45;
            v904 = v46 / v45;
            v47 = (startsy[(__int16)v921] - v912) / v45;
            v911 += v46 / v45;
            v905 = v47;
            v912 += v47;
          }
          goto LABEL_60;
        }
        if ((_WORD)v919 == (_WORD)v921)
          break;
        HIWORD(v916) = *(_WORD *)v44;
        v911 = startsx[(__int16)v921];
        v912 = startsy[(__int16)v921];
      }
      v915 = v33;
    LABEL_140:
      v11 = *(v3 - 15);
      if (v11 < winh) {
        if (*((__int16 *)v3 - 19) < (unsigned int)winw) {
        LABEL_144:
          v11 = *((__int16 *)v3 - 17);
          if (v11 <= (unsigned int)winw) {
          LABEL_147:
            v11 = *(int *)((char *)v3 - 34) - *(int *)((char *)v3 - 38);
            *((_WORD *)v3 - 14) = v11;
            if (*((__int16 *)v3 - 14) <= 0)
              return v11;
            v236 = *(v3 - 14);
            v237 = *(v3 - 13);
            v238 = *(v3 - 17);
            *(int *)((char *)&startsy_variable_8 + 2) = (*(v3 - 16) - v236) / *((__int16 *)v3 - 14);
            v239 = (v238 - v237) / *((__int16 *)v3 - 14);
            v240 = *((__int16 *)v3 - 17);
            *(int *)((char *)&startsy_variable_10 + 2) = v239;
            v11 = winw * *(v3 - 15);
            *(int *)((char *)&startsy_variable_4 + 2) = v236;
            *(int *)((char *)&startsy_variable_6 + 2) = v237;
            *(v3 - 23) = v11 + scrptr + v240;
            if (*((__int16 *)v3 - 14) <= 7) {
              HIWORD(v247) = HIWORD(startsy_variable_4);
              HIWORD(v241) = HIWORD(startsy_variable_6);
              BYTE1(v247) = BYTE1(startsy_variable_8);
              HIWORD(v242) = HIWORD(startsy_variable_8);
              v246 = startsy_variable_10;
              LOWORD(v242) = startsy_variable_12;
              v243 = *((_WORD *)v3 - 14);
              LOWORD(v11) = *((_WORD *)v3 - 2);
              __DS__ = v11;
              v244 = (_DWORD *)*(v3 - 23);
              LOWORD(v241) = startsy_variable_6 - startsy_variable_10;
              v83 = __CFADD__(startsy_variable_10, v241);
              v245 = (_BYTE *)(startsy_variable_10 + v241);
              BYTE1(v245) = startsy_variable_8;
              BYTE1(v246) = 0;
              LOBYTE(v247) = v83 + startsy_variable_8;
              if ((v243 & 4) != 0) {
                LOBYTE(v11) = *MK_FP(v11, (_WORD)v245);
                v83 = __CFADD__(__PAIR64__(v246, v242), __PAIR64__((unsigned int)v245, v247));
                v249 = v242 + v247;
                v248 = (_BYTE *)((__PAIR64__(v246, v242) + __PAIR64__((unsigned int)v245, v247)) >> 32);
                BYTE1(v248) = startsy_variable_12 + v247;
                BYTE1(v11) = *v248;
                v250 = v242 + v83 + v242 + v247;
                v252 = __CFADD__(v83, v249) | __CFADD__(v242, v83 + v249);
                v83 = __CFADD__(v252, v248);
                v251 = &v248[v252];
                v83 |= __CFADD__(v246, v251);
                v251 += v246;
                BYTE1(v251) = v250;
                v11 = _byteswap_ulong(v11);
                BYTE1(v11) = *v251;
                v254 = v83;
                v83 = __CFADD__(v83, v250);
                v253 = v254 + v250;
                v83 |= __CFADD__(v242, v253);
                v253 += v242;
                v256 = v83;
                v83 = __CFADD__(v83, v251);
                v255 = &v251[v256];
                v83 |= __CFADD__(v246, v255);
                v255 += v246;
                BYTE1(v255) = v253;
                LOBYTE(v11) = *v255;
                v258 = v83;
                v83 = __CFADD__(v83, v253);
                v257 = v258 + v253;
                v83 |= __CFADD__(v242, v257);
                v247 = v242 + v257;
                v260 = v83;
                v83 = __CFADD__(v83, v255);
                v259 = &v255[v260];
                v83 |= __CFADD__(v246, v259);
                v245 = &v259[v246];
                BYTE1(v245) = v247;
                LOBYTE(v247) = v83 + v247;
                *--v244 = v11;
              }
              if ((v243 & 2) != 0) {
                BYTE1(v11) = *v245;
                v83 = __CFADD__(__PAIR64__(v246, v242), __PAIR64__((unsigned int)v245, v247));
                v245 = (_BYTE *)((__PAIR64__(v246, v242) + __PAIR64__((unsigned int)v245, v247)) >> 32);
                BYTE1(v245) = v242 + v247;
                LOBYTE(v11) = *v245;
                LOBYTE(v245) = v246 + (__CFADD__(v83, v242 + v247) | __CFADD__(v242, v83 + v242 + v247)) + (_BYTE)v245;
                BYTE1(v245) = v242 + v83 + v242 + v247;
                v244 = (_DWORD *)((char *)v244 - 2);
                *(_WORD *)v244 = v11;
              }
              if ((v243 & 1) != 0) {
                LOBYTE(v11) = *v245;
                *((_BYTE *)v244 - 1) = *v245;
              }
              return v11;
            }
            goto LABEL_364;
          }
          if (*((__int16 *)v3 - 17) <= 0)
            return v11;
          goto LABEL_288;
        }
        v11 = *((__int16 *)v3 - 19);
        if (v11 >= winw)
          return v11;
      LABEL_216:
        v11 = *((__int16 *)v3 - 17);
        if (v11 > (unsigned int)winw) {
          if (*((__int16 *)v3 - 17) <= 0)
            return v11;
        LABEL_356:
          *((_WORD *)v3 - 14) = *(int *)((char *)v3 - 34) - *(int *)((char *)v3 - 38);
          v793 = *(v3 - 17);
          v794 = *(v3 - 13);
          *(int *)((char *)&startsy_variable_8 + 2) = (*(v3 - 16) - *(v3 - 14)) / *((__int16 *)v3 - 14);
          v795 = winw;
          *(int *)((char *)&startsy_variable_10 + 2) = (v793 - v794) / *((__int16 *)v3 - 14);
          v796 = *((__int16 *)v3 - 17) - winw;
          v797 = *(v3 - 13);
          *(int *)((char *)&startsy_variable_4 + 2) = v796 * *(int *)((char *)&startsy_variable_8 + 2) + *(v3 - 14);
          *(int *)((char *)&startsy_variable_6 + 2) = *(int *)((char *)&startsy_variable_10 + 2) * v796 + v797;
          *((_WORD *)v3 - 14) = winw;
          v11 = v795 * *(v3 - 15) + scrptr1;
          *(v3 - 23) = v11;
          if (*((__int16 *)v3 - 14) > 7)
            goto LABEL_364;
          HIWORD(v804) = HIWORD(startsy_variable_4);
          HIWORD(v798) = HIWORD(startsy_variable_6);
          BYTE1(v804) = BYTE1(startsy_variable_8);
          HIWORD(v799) = HIWORD(startsy_variable_8);
          v803 = startsy_variable_10;
          LOWORD(v799) = startsy_variable_12;
          v800 = *((_WORD *)v3 - 14);
          LOWORD(v11) = *((_WORD *)v3 - 2);
          __DS__ = v11;
          v801 = (_DWORD *)*(v3 - 23);
          LOWORD(v798) = startsy_variable_6 - startsy_variable_10;
          v83 = __CFADD__(startsy_variable_10, v798);
          v802 = (_BYTE *)(startsy_variable_10 + v798);
          BYTE1(v802) = startsy_variable_8;
          BYTE1(v803) = 0;
          LOBYTE(v804) = v83 + startsy_variable_8;
          if ((v800 & 4) != 0) {
            LOBYTE(v11) = *MK_FP(v11, (_WORD)v802);
            v83 = __CFADD__(__PAIR64__(v803, v799), __PAIR64__((unsigned int)v802, v804));
            v806 = v799 + v804;
            v805 = (_BYTE *)((__PAIR64__(v803, v799) + __PAIR64__((unsigned int)v802, v804)) >> 32);
            BYTE1(v805) = startsy_variable_12 + v804;
            BYTE1(v11) = *v805;
            v807 = v799 + v83 + v799 + v804;
            v809 = __CFADD__(v83, v806) | __CFADD__(v799, v83 + v806);
            v83 = __CFADD__(v809, v805);
            v808 = &v805[v809];
            v83 |= __CFADD__(v803, v808);
            v808 += v803;
            BYTE1(v808) = v807;
            v11 = _byteswap_ulong(v11);
            BYTE1(v11) = *v808;
            v811 = v83;
            v83 = __CFADD__(v83, v807);
            v810 = v811 + v807;
            v83 |= __CFADD__(v799, v810);
            v810 += v799;
            v813 = v83;
            v83 = __CFADD__(v83, v808);
            v812 = &v808[v813];
            v83 |= __CFADD__(v803, v812);
            v812 += v803;
            BYTE1(v812) = v810;
            LOBYTE(v11) = *v812;
            v815 = v83;
            v83 = __CFADD__(v83, v810);
            v814 = v815 + v810;
            v83 |= __CFADD__(v799, v814);
            v804 = v799 + v814;
            v817 = v83;
            v83 = __CFADD__(v83, v812);
            v816 = &v812[v817];
            v83 |= __CFADD__(v803, v816);
            v802 = &v816[v803];
            BYTE1(v802) = v804;
            LOBYTE(v804) = v83 + v804;
            *--v801 = v11;
          }
          if ((v800 & 2) != 0) {
            BYTE1(v11) = *v802;
            v83 = __CFADD__(__PAIR64__(v803, v799), __PAIR64__((unsigned int)v802, v804));
            v802 = (_BYTE *)((__PAIR64__(v803, v799) + __PAIR64__((unsigned int)v802, v804)) >> 32);
            BYTE1(v802) = v799 + v804;
            LOBYTE(v11) = *v802;
            LOBYTE(v802) = v803 + (__CFADD__(v83, v799 + v804) | __CFADD__(v799, v83 + v799 + v804)) + (_BYTE)v802;
            BYTE1(v802) = v799 + v83 + v799 + v804;
            v801 = (_DWORD *)((char *)v801 - 2);
            *(_WORD *)v801 = v11;
          }
          if ((v800 & 1) != 0) {
            LOBYTE(v11) = *v802;
            *((_BYTE *)v801 - 1) = *v802;
          }
        } else {
        LABEL_219:
          v11 = *(int *)((char *)v3 - 34);
          *((_WORD *)v3 - 14) = v11;
          if (*((__int16 *)v3 - 14) <= 0)
            return v11;
          v422 = (__int16)(v11 - *((_WORD *)v3 - 19));
          v423 = *(v3 - 13);
          v424 = *(v3 - 17) - v423;
          *(int *)((char *)&startsy_variable_8 + 2) = (*(v3 - 16) - *(v3 - 14)) / v422;
          *(int *)((char *)&startsy_variable_10 + 2) = v424 / v422;
          *(int *)((char *)&startsy_variable_4 + 2) = *(v3 - 14);
          v425 = *((__int16 *)v3 - 17) + scrptr;
          v11 = winw * *(v3 - 15);
          *(int *)((char *)&startsy_variable_6 + 2) = v423;
          *(v3 - 23) = v11 + v425;
          if (*((__int16 *)v3 - 14) > 7)
            goto LABEL_364;
          HIWORD(v432) = HIWORD(startsy_variable_4);
          HIWORD(v426) = HIWORD(startsy_variable_6);
          BYTE1(v432) = BYTE1(startsy_variable_8);
          HIWORD(v427) = HIWORD(startsy_variable_8);
          v431 = startsy_variable_10;
          LOWORD(v427) = startsy_variable_12;
          v428 = *((_WORD *)v3 - 14);
          LOWORD(v11) = *((_WORD *)v3 - 2);
          __DS__ = v11;
          v429 = (_DWORD *)*(v3 - 23);
          LOWORD(v426) = startsy_variable_6 - startsy_variable_10;
          v83 = __CFADD__(startsy_variable_10, v426);
          v430 = (_BYTE *)(startsy_variable_10 + v426);
          BYTE1(v430) = startsy_variable_8;
          BYTE1(v431) = 0;
          LOBYTE(v432) = v83 + startsy_variable_8;
          if ((v428 & 4) != 0) {
            LOBYTE(v11) = *MK_FP(v11, (_WORD)v430);
            v83 = __CFADD__(__PAIR64__(v431, v427), __PAIR64__((unsigned int)v430, v432));
            v434 = v427 + v432;
            v433 = (_BYTE *)((__PAIR64__(v431, v427) + __PAIR64__((unsigned int)v430, v432)) >> 32);
            BYTE1(v433) = startsy_variable_12 + v432;
            BYTE1(v11) = *v433;
            v435 = v427 + v83 + v427 + v432;
            v437 = __CFADD__(v83, v434) | __CFADD__(v427, v83 + v434);
            v83 = __CFADD__(v437, v433);
            v436 = &v433[v437];
            v83 |= __CFADD__(v431, v436);
            v436 += v431;
            BYTE1(v436) = v435;
            v11 = _byteswap_ulong(v11);
            BYTE1(v11) = *v436;
            v439 = v83;
            v83 = __CFADD__(v83, v435);
            v438 = v439 + v435;
            v83 |= __CFADD__(v427, v438);
            v438 += v427;
            v441 = v83;
            v83 = __CFADD__(v83, v436);
            v440 = &v436[v441];
            v83 |= __CFADD__(v431, v440);
            v440 += v431;
            BYTE1(v440) = v438;
            LOBYTE(v11) = *v440;
            v443 = v83;
            v83 = __CFADD__(v83, v438);
            v442 = v443 + v438;
            v83 |= __CFADD__(v427, v442);
            v432 = v427 + v442;
            v445 = v83;
            v83 = __CFADD__(v83, v440);
            v444 = &v440[v445];
            v83 |= __CFADD__(v431, v444);
            v430 = &v444[v431];
            BYTE1(v430) = v432;
            LOBYTE(v432) = v83 + v432;
            *--v429 = v11;
          }
          if ((v428 & 2) != 0) {
            BYTE1(v11) = *v430;
            v83 = __CFADD__(__PAIR64__(v431, v427), __PAIR64__((unsigned int)v430, v432));
            v430 = (_BYTE *)((__PAIR64__(v431, v427) + __PAIR64__((unsigned int)v430, v432)) >> 32);
            BYTE1(v430) = v427 + v432;
            LOBYTE(v11) = *v430;
            LOBYTE(v430) = v431 + (__CFADD__(v83, v427 + v432) | __CFADD__(v427, v83 + v427 + v432)) + (_BYTE)v430;
            BYTE1(v430) = v427 + v83 + v427 + v432;
            v429 = (_DWORD *)((char *)v429 - 2);
            *(_WORD *)v429 = v11;
          }
          if ((v428 & 1) != 0) {
            LOBYTE(v11) = *v430;
            *((_BYTE *)v429 - 1) = *v430;
          }
        }
      }
    } else {
      v11 = v13;
      LOWORD(v913) = 0;
      LOWORD(v914) = 0;
      LOWORD(v915) = 0;
      LOWORD(v916) = -1;
      do {
        v14 = (__int16)v919;
        HIWORD(v915) = v907[2 * (__int16)v919++];
        v15 = startsx[v14];
        v16 = startsy[v14];
        v909 = v15;
        v908 = v16;
        if ((_WORD)v919 == (_WORD)v918)
          v919 = 0;
        v910 = v11;
        v11 = v907[2 * (__int16)v919 + 1];
      } while (v11 < 0);
      if (v11)
        goto LABEL_37;
      do {
        HIWORD(v915) = v907[2 * (__int16)v919];
        v909 = startsx[(__int16)v919];
        v908 = startsy[(__int16)v919++];
        if ((_WORD)v919 == (_WORD)v918)
          v919 = 0;
        v910 = v11;
        v11 = v907[2 * (__int16)v919 + 1];
      } while (!v11);
      if (v11 >= 0) {
      LABEL_37:
        v17 = LOWORD(v907[2 * (__int16)v919]) - HIWORD(v915);
        HIWORD(v914) = v17;
        v920 = v11;
        if (v914 >= 0) {
          HIWORD(v914) = v17 + 1;
          v21 = (__int16)v11 - v910 + 1;
          v22 = startsx[(__int16)v919] - v909;
          v914 /= v21;
          v903 = v22 / v21;
          v906 = (startsy[(__int16)v919] - v908) / v21;
        } else {
          HIWORD(v914) = v17 - 1;
          v18 = (__int16)v11 - v910 + 1;
          v914 /= v18;
          v19 = (startsx[(__int16)v919] - v909) / v18;
          v909 += v19;
          v20 = startsy[(__int16)v919];
          v903 = v19;
          v915 += v914;
          ++HIWORD(v915);
          v906 = (v20 - v908) / v18;
          v908 += v906;
        }
        v915 -= v914 * v910;
        v909 -= v903 * v910;
        v908 -= v906 * v910;
        do {
          HIWORD(v916) = v907[2 * (__int16)v921];
          v23 = startsx[(__int16)v921];
          v912 = startsy[(__int16)v921--];
          v911 = v23;
          if ((__int16)v921 == -1)
            v921 = v918 - 1;
          v910 = v13;
          v13 = v907[2 * (__int16)v921 + 1];
        } while (v13 < 0);
        if (v13)
          goto LABEL_38;
        do {
          HIWORD(v916) = v907[2 * (__int16)v921];
          v911 = startsx[(__int16)v921];
          v912 = startsy[(__int16)v921--];
          if ((__int16)v921 == -1)
            v921 = v918 - 1;
          LOBYTE(v11) = v921;
          v910 = v13;
          v13 = v907[2 * (__int16)v921 + 1];
        } while (!v13);
        if (v13 >= 0) {
        LABEL_38:
          HIWORD(v913) = LOWORD(v907[2 * (__int16)v921]) - HIWORD(v916);
          if (v913 <= 0) {
            --HIWORD(v913);
            v917 = v13;
            v27 = (__int16)v13 - v910 + 1;
            v913 /= v27;
            v28 = startsx[(__int16)v921];
            ++HIWORD(v916);
            v29 = (v28 - v911) / v27;
            v30 = startsy[(__int16)v921] - v912;
            v904 = v29;
            v905 = v30 / v27;
          } else {
            v917 = v13;
            ++HIWORD(v913);
            v24 = (__int16)v13 - v910 + 1;
            v913 /= v24;
            v25 = (startsx[(__int16)v921] - v911) / v24;
            v911 += v25;
            v26 = startsy[(__int16)v921];
            v904 = v25;
            v916 += v913;
            v905 = (v26 - v912) / v24;
            v912 += v905;
          }
          v916 -= v913 * v910;
          v911 -= v904 * v910;
          v912 -= v905 * v910;
          v910 = 0;
        LABEL_60:
          while (SHIWORD(v915) >= winw || SHIWORD(v916) <= 0) {
            v915 += v914;
            v909 += v903;
            v908 += v906;
            ++v910;
            HIWORD(v52) = HIWORD(v920);
            v916 += v913;
            v911 += v904;
            v912 += v905;
            LOWORD(v52) = v920 - 1;
            v920 = v52;
            if (!(_WORD)v52) {
              while (1) {
                LOWORD(v11) = v919;
                if ((_WORD)v919 == (_WORD)v921)
                  return v11;
                HIWORD(v915) = v907[2 * (__int16)v919];
                v53 = startsx[(__int16)v919++];
                v909 = v53;
                HIWORD(v53) = HIWORD(v918);
                v908 = startsy[(__int16)v11];
                if ((_WORD)v919 == (_WORD)v918)
                  v919 = 0;
                v11 = (signed int)&v907[2 * (__int16)v919];
                LOWORD(v53) = *(_WORD *)(v11 + 4);
                v54 = v53 - v910;
                v920 = v54;
                if ((__int16)v54 > 0) {
                  HIWORD(v914) = *(_WORD *)v11 - HIWORD(v915);
                  LOWORD(v914) = 0;
                  LOWORD(v915) = 0;
                  if (v914 >= 0) {
                    ++HIWORD(v914);
                    v59 = (__int16)v54 + 1;
                    v914 /= v59;
                    v60 = startsy[(__int16)v919] - v908;
                    v903 = (startsx[(__int16)v919] - v909) / v59;
                    v906 = v60 / v59;
                  } else {
                    --HIWORD(v914);
                    v55 = (__int16)v54 + 1;
                    v915 += v914 / v55;
                    v914 /= v55;
                    v56 = startsx[(__int16)v919] - v909;
                    ++HIWORD(v915);
                    v57 = v56 / v55;
                    v909 += v56 / v55;
                    v58 = startsy[(__int16)v919];
                    v903 = v57;
                    v906 = (v58 - v908) / v55;
                    v908 += v906;
                  }
                  break;
                }
                if ((v54 & 0x8000u) != 0)
                  return v11;
              }
            }
            HIWORD(v61) = HIWORD(v917);
            LOWORD(v61) = v917 - 1;
            v917 = v61;
            if (!(_WORD)v61) {
              while (1) {
                LOBYTE(v11) = v919;
                v62 = v921;
                if ((_WORD)v919 == (_WORD)v921)
                  return v11;
                HIWORD(v916) = v907[2 * (__int16)v921];
                v63 = startsx[(__int16)v921];
                v64 = startsy[(__int16)v921--];
                v912 = v64;
                v911 = v63;
                if ((__int16)(v62 - 1) == -1)
                  v921 = v918 - 1;
                v11 = (signed int)&v907[2 * (__int16)v921];
                LOWORD(v63) = *(_WORD *)(v11 + 4);
                v65 = v63 - v910;
                v917 = v65;
                if ((__int16)v65 > 0) {
                  v66 = *(_WORD *)v11 - HIWORD(v916);
                  LOWORD(v913) = 0;
                  HIWORD(v913) = v66;
                  LOWORD(v916) = -1;
                  if (v913 <= 0) {
                    --HIWORD(v913);
                    v70 = (__int16)v65 + 1;
                    ++HIWORD(v916);
                    v71 = startsx[(__int16)v921] - v911;
                    v913 /= v70;
                    v72 = v71;
                    v73 = startsy[(__int16)v921] - v912;
                    v904 = v72 / v70;
                    v905 = v73 / v70;
                  } else {
                    ++HIWORD(v913);
                    v67 = (__int16)v65 + 1;
                    v916 += v913 / v67;
                    v68 = startsx[(__int16)v921] - v911;
                    v913 /= v67;
                    v904 = v68 / v67;
                    v69 = (startsy[(__int16)v921] - v912) / v67;
                    v911 += v68 / v67;
                    v905 = v69;
                    v912 += v69;
                  }
                  break;
                }
                if ((v65 & 0x8000u) != 0)
                  return v11;
              }
            }
            LOBYTE(v11) = v910;
            if (v910 >= winh)
              return v11;
          }
          while (*((__int16 *)v3 - 19) < (unsigned int)winw) {
          LABEL_87:
            v11 = *((__int16 *)v3 - 17);
            if (v11 > (unsigned int)winw) {
              if (*((__int16 *)v3 - 17) > 0)
                goto LABEL_234;
              return v11;
            }
          LABEL_90:
            v11 = *(int *)((char *)v3 - 34) - *(int *)((char *)v3 - 38);
            *(v3 - 7) = v11;
            if (*((__int16 *)v3 - 14) > 0) {
              v74 = *(v3 - 13);
              v75 = *(v3 - 17);
              *(int *)((char *)&startsy_variable_8 + 2) = (*(v3 - 16) - *(v3 - 14)) / *((__int16 *)v3 - 14);
              *(int *)((char *)&startsy_variable_10 + 2) = (v75 - v74) / *((__int16 *)v3 - 14);
              *(int *)((char *)&startsy_variable_4 + 2) = *(v3 - 14);
              v76 = scrptr + *((__int16 *)v3 - 17);
              v77 = winw * *(v3 - 15);
              *(int *)((char *)&startsy_variable_6 + 2) = v74;
              v78 = v77 + v76;
              *(v3 - 23) = v78;
              if (*((__int16 *)v3 - 14) > 7) {
                v896 = v3;
                v888 = __DS__;
                HIWORD(v108) = HIWORD(startsy_variable_4);
                HIWORD(v102) = HIWORD(startsy_variable_6);
                BYTE1(v108) = BYTE1(startsy_variable_8);
                HIWORD(v103) = HIWORD(startsy_variable_8);
                v107 = startsy_variable_10;
                LOWORD(v103) = startsy_variable_12;
                v104 = *((_WORD *)v3 - 14);
                __DS__ = *((_WORD *)v3 - 2);
                v105 = (_WORD *)*(v3 - 23);
                LOWORD(v102) = startsy_variable_6 - startsy_variable_10;
                v83 = __CFADD__(startsy_variable_10, v102);
                v106 = (char *)(startsy_variable_10 + v102);
                BYTE1(v106) = startsy_variable_8;
                BYTE1(v107) = 0;
                LOBYTE(v108) = v83 + startsy_variable_8;
                if (((unsigned __int8)v105 & 1) != 0) {
                  v109 = *v106;
                  v83 = __CFADD__(__PAIR64__(v107, v103), __PAIR64__((unsigned int)v106, v108));
                  v106 = (char *)((__PAIR64__(v107, v103) + __PAIR64__((unsigned int)v106, v108)) >> 32);
                  v108 += v103;
                  BYTE1(v106) = v108;
                  LOBYTE(v108) = v83 + v108;
                  v105 = (_WORD *)((char *)v105 - 1);
                  *(_BYTE *)v105 = v109;
                  --v104;
                }
                if (((unsigned __int8)v105 & 2) != 0) {
                  HIBYTE(v110) = *v106;
                  v83 = __CFADD__(__PAIR64__(v107, v103), __PAIR64__((unsigned int)v106, v108));
                  v112 = v103 + v108;
                  v111 = (_BYTE *)((__PAIR64__(v107, v103) + __PAIR64__((unsigned int)v106, v108)) >> 32);
                  BYTE1(v111) = v103 + v108;
                  LOBYTE(v110) = *v111;
                  v108 += v103 + v83 + v103;
                  v114 = __CFADD__(v83, v112) | __CFADD__(v103, v83 + v112);
                  v83 = __CFADD__(v114, v111);
                  v113 = &v111[v114];
                  v83 |= __CFADD__(v107, v113);
                  v106 = &v113[v107];
                  BYTE1(v106) = v108;
                  LOBYTE(v108) = v83 + v108;
                  *--v105 = v110;
                  v104 -= 2;
                }
                if (((unsigned __int8)v105 & 4) != 0) {
                  LOBYTE(v78) = *v106;
                  v83 = __CFADD__(__PAIR64__(v107, v103), __PAIR64__((unsigned int)v106, v108));
                  v116 = v103 + v108;
                  v115 = (_BYTE *)((__PAIR64__(v107, v103) + __PAIR64__((unsigned int)v106, v108)) >> 32);
                  BYTE1(v115) = v103 + v108;
                  BYTE1(v78) = *v115;
                  v117 = v103 + v83 + v103 + v108;
                  v119 = __CFADD__(v83, v116) | __CFADD__(v103, v83 + v116);
                  v83 = __CFADD__(v119, v115);
                  v118 = &v115[v119];
                  v83 |= __CFADD__(v107, v118);
                  v118 += v107;
                  BYTE1(v118) = v117;
                  v78 = _byteswap_ulong(v78);
                  BYTE1(v78) = *v118;
                  v121 = v83;
                  v83 = __CFADD__(v83, v117);
                  v120 = v121 + v117;
                  v83 |= __CFADD__(v103, v120);
                  v120 += v103;
                  v123 = v83;
                  v83 = __CFADD__(v83, v118);
                  v122 = &v118[v123];
                  v83 |= __CFADD__(v107, v122);
                  v122 += v107;
                  BYTE1(v122) = v120;
                  LOBYTE(v78) = *v122;
                  v125 = v83;
                  v83 = __CFADD__(v83, v120);
                  v124 = v125 + v120;
                  v83 |= __CFADD__(v103, v124);
                  v108 = v103 + v124;
                  v127 = v83;
                  v83 = __CFADD__(v83, v122);
                  v126 = &v122[v127];
                  v83 |= __CFADD__(v107, v126);
                  v106 = &v126[v107];
                  BYTE1(v106) = v108;
                  LOBYTE(v108) = v83 + v108;
                  v105 -= 2;
                  *(_DWORD *)v105 = v78;
                  v104 -= 4;
                }
                v83 = v104 < 8u;
                for (i = v104 - 8; !v83; i -= 8) {
                  LOBYTE(v78) = *v106;
                  v83 = __CFADD__(__PAIR64__(v107, v103), __PAIR64__((unsigned int)v106, v108));
                  v130 = v103 + v108;
                  v129 = (_BYTE *)((__PAIR64__(v107, v103) + __PAIR64__((unsigned int)v106, v108)) >> 32);
                  BYTE1(v129) = v103 + v108;
                  BYTE1(v78) = *v129;
                  v131 = v103 + v83 + v103 + v108;
                  v133 = __CFADD__(v83, v130) | __CFADD__(v103, v83 + v130);
                  v83 = __CFADD__(v133, v129);
                  v132 = &v129[v133];
                  v83 |= __CFADD__(v107, v132);
                  v132 += v107;
                  BYTE1(v132) = v131;
                  v134 = _byteswap_ulong(v78);
                  BYTE1(v134) = *v132;
                  v136 = v83;
                  v83 = __CFADD__(v83, v131);
                  v135 = v136 + v131;
                  v83 |= __CFADD__(v103, v135);
                  v135 += v103;
                  v138 = v83;
                  v83 = __CFADD__(v83, v132);
                  v137 = &v132[v138];
                  v83 |= __CFADD__(v107, v137);
                  v137 += v107;
                  BYTE1(v137) = v135;
                  LOBYTE(v134) = *v137;
                  v140 = v83;
                  v83 = __CFADD__(v83, v135);
                  v139 = v140 + v135;
                  v83 |= __CFADD__(v103, v139);
                  v139 += v103;
                  v142 = v83;
                  v83 = __CFADD__(v83, v137);
                  v141 = &v137[v142];
                  v83 |= __CFADD__(v107, v141);
                  v141 += v107;
                  BYTE1(v141) = v139;
                  *((_DWORD *)v105 - 1) = v134;
                  LOBYTE(v134) = *v141;
                  v144 = v83;
                  v83 = __CFADD__(v83, v139);
                  v143 = v144 + v139;
                  v83 |= __CFADD__(v103, v143);
                  v143 += v103;
                  v146 = v83;
                  v83 = __CFADD__(v83, v141);
                  v145 = &v141[v146];
                  v83 |= __CFADD__(v107, v145);
                  v145 += v107;
                  BYTE1(v145) = v143;
                  BYTE1(v134) = *v145;
                  v148 = v83;
                  v83 = __CFADD__(v83, v143);
                  v147 = v148 + v143;
                  v83 |= __CFADD__(v103, v147);
                  v147 += v103;
                  v150 = v83;
                  v83 = __CFADD__(v83, v145);
                  v149 = &v145[v150];
                  v83 |= __CFADD__(v107, v149);
                  v149 += v107;
                  BYTE1(v149) = v147;
                  v78 = _byteswap_ulong(v134);
                  BYTE1(v78) = *v149;
                  v152 = v83;
                  v83 = __CFADD__(v83, v147);
                  v151 = v152 + v147;
                  v83 |= __CFADD__(v103, v151);
                  v151 += v103;
                  v154 = v83;
                  v83 = __CFADD__(v83, v149);
                  v153 = &v149[v154];
                  v83 |= __CFADD__(v107, v153);
                  v153 += v107;
                  BYTE1(v153) = v151;
                  LOBYTE(v78) = *v153;
                  v156 = v83;
                  v83 = __CFADD__(v83, v151);
                  v155 = v156 + v151;
                  v83 |= __CFADD__(v103, v155);
                  v108 = v103 + v155;
                  v158 = v83;
                  v83 = __CFADD__(v83, v153);
                  v157 = &v153[v158];
                  v83 |= __CFADD__(v107, v157);
                  v106 = &v157[v107];
                  BYTE1(v106) = v108;
                  LOBYTE(v108) = v83 + v108;
                  v105 -= 4;
                  *(_DWORD *)v105 = v78;
                  v83 = i < 8u;
                }
                if ((i & 4) != 0) {
                  LOBYTE(v78) = *v106;
                  v83 = __CFADD__(__PAIR64__(v107, v103), __PAIR64__((unsigned int)v106, v108));
                  v160 = v103 + v108;
                  v159 = (_BYTE *)((__PAIR64__(v107, v103) + __PAIR64__((unsigned int)v106, v108)) >> 32);
                  BYTE1(v159) = v103 + v108;
                  BYTE1(v78) = *v159;
                  v161 = v103 + v83 + v103 + v108;
                  v163 = __CFADD__(v83, v160) | __CFADD__(v103, v83 + v160);
                  v83 = __CFADD__(v163, v159);
                  v162 = &v159[v163];
                  v83 |= __CFADD__(v107, v162);
                  v162 += v107;
                  BYTE1(v162) = v161;
                  v164 = _byteswap_ulong(v78);
                  BYTE1(v164) = *v162;
                  v166 = v83;
                  v83 = __CFADD__(v83, v161);
                  v165 = v166 + v161;
                  v83 |= __CFADD__(v103, v165);
                  v165 += v103;
                  v168 = v83;
                  v83 = __CFADD__(v83, v162);
                  v167 = &v162[v168];
                  v83 |= __CFADD__(v107, v167);
                  v167 += v107;
                  BYTE1(v167) = v165;
                  LOBYTE(v164) = *v167;
                  v170 = v83;
                  v83 = __CFADD__(v83, v165);
                  v169 = v170 + v165;
                  v83 |= __CFADD__(v103, v169);
                  v108 = v103 + v169;
                  v172 = v83;
                  v83 = __CFADD__(v83, v167);
                  v171 = &v167[v172];
                  v83 |= __CFADD__(v107, v171);
                  v106 = &v171[v107];
                  BYTE1(v106) = v108;
                  LOBYTE(v108) = v83 + v108;
                  v105 -= 2;
                  *(_DWORD *)v105 = v164;
                }
                if ((i & 2) != 0) {
                  HIBYTE(v173) = *v106;
                  v83 = __CFADD__(__PAIR64__(v107, v103), __PAIR64__((unsigned int)v106, v108));
                  v106 = (char *)((__PAIR64__(v107, v103) + __PAIR64__((unsigned int)v106, v108)) >> 32);
                  BYTE1(v106) = v103 + v108;
                  LOBYTE(v173) = *v106;
                  LOBYTE(v106) = v107 + (__CFADD__(v83, v103 + v108) | __CFADD__(v103, v83 + v103 + v108)) + (_BYTE)v106;
                  BYTE1(v106) = v103 + v83 + v103 + v108;
                  *--v105 = v173;
                }
                if ((i & 1) != 0)
                  *((_BYTE *)v105 - 1) = *v106;
                __DS__ = v888;
                v3 = v896;
              } else {
                v895 = v3;
                v887 = __DS__;
                HIWORD(v86) = HIWORD(startsy_variable_4);
                HIWORD(v79) = HIWORD(startsy_variable_6);
                BYTE1(v86) = BYTE1(startsy_variable_8);
                HIWORD(v80) = HIWORD(startsy_variable_8);
                v85 = startsy_variable_10;
                LOWORD(v80) = startsy_variable_12;
                v81 = *((_WORD *)v3 - 14);
                __DS__ = *((_WORD *)v3 - 2);
                v82 = (_DWORD *)*(v3 - 23);
                LOWORD(v79) = startsy_variable_6 - startsy_variable_10;
                v83 = __CFADD__(startsy_variable_10, v79);
                v84 = (_BYTE *)(startsy_variable_10 + v79);
                BYTE1(v84) = startsy_variable_8;
                BYTE1(v85) = 0;
                LOBYTE(v86) = v83 + startsy_variable_8;
                if ((v81 & 4) != 0) {
                  LOBYTE(v78) = *v84;
                  v83 = __CFADD__(__PAIR64__(v85, v80), __PAIR64__((unsigned int)v84, v86));
                  v88 = v80 + v86;
                  v87 = (_BYTE *)((__PAIR64__(v85, v80) + __PAIR64__((unsigned int)v84, v86)) >> 32);
                  BYTE1(v87) = startsy_variable_12 + v86;
                  BYTE1(v78) = *v87;
                  v89 = v80 + v83 + v80 + v86;
                  v91 = __CFADD__(v83, v88) | __CFADD__(v80, v83 + v88);
                  v83 = __CFADD__(v91, v87);
                  v90 = &v87[v91];
                  v83 |= __CFADD__(v85, v90);
                  v90 += v85;
                  BYTE1(v90) = v89;
                  v92 = _byteswap_ulong(v78);
                  BYTE1(v92) = *v90;
                  v94 = v83;
                  v83 = __CFADD__(v83, v89);
                  v93 = v94 + v89;
                  v83 |= __CFADD__(v80, v93);
                  v93 += v80;
                  v96 = v83;
                  v83 = __CFADD__(v83, v90);
                  v95 = &v90[v96];
                  v83 |= __CFADD__(v85, v95);
                  v95 += v85;
                  BYTE1(v95) = v93;
                  LOBYTE(v92) = *v95;
                  v98 = v83;
                  v83 = __CFADD__(v83, v93);
                  v97 = v98 + v93;
                  v83 |= __CFADD__(v80, v97);
                  v86 = v80 + v97;
                  v100 = v83;
                  v83 = __CFADD__(v83, v95);
                  v99 = &v95[v100];
                  v83 |= __CFADD__(v85, v99);
                  v84 = &v99[v85];
                  BYTE1(v84) = v86;
                  LOBYTE(v86) = v83 + v86;
                  *--v82 = v92;
                }
                if ((v81 & 2) != 0) {
                  HIBYTE(v101) = *v84;
                  v83 = __CFADD__(__PAIR64__(v85, v80), __PAIR64__((unsigned int)v84, v86));
                  v84 = (_BYTE *)((__PAIR64__(v85, v80) + __PAIR64__((unsigned int)v84, v86)) >> 32);
                  BYTE1(v84) = v80 + v86;
                  LOBYTE(v101) = *v84;
                  LOBYTE(v84) = v85 + (__CFADD__(v83, v80 + v86) | __CFADD__(v80, v83 + v80 + v86)) + (_BYTE)v84;
                  BYTE1(v84) = v80 + v83 + v80 + v86;
                  v82 = (_DWORD *)((char *)v82 - 2);
                  *(_WORD *)v82 = v101;
                }
                if ((v81 & 1) != 0)
                  *((_BYTE *)v82 - 1) = *v84;
                __DS__ = v887;
                v3 = v895;
              }
            } else if (*((__int16 *)v3 - 14) < 0) {
              return v11;
            }
            v174 = *(v3 - 16);
            v175 = *(v3 - 17);
            v176 = *(v3 - 9);
            v177 = *(v3 - 14);
            v178 = *(v3 - 22);
            *(v3 - 10) += *(v3 - 11);
            v179 = *(v3 - 13);
            v180 = v178 + v174;
            v181 = *(v3 - 19);
            *(v3 - 16) = v180;
            v182 = v181 + v175;
            v183 = *(v3 - 12);
            *(v3 - 17) = v182;
            v184 = v183 + v176;
            v185 = *(v3 - 21);
            *(v3 - 9) = v184;
            v186 = *(v3 - 4);
            v187 = v185 + v177;
            v188 = *(v3 - 20);
            *(v3 - 14) = v187;
            v189 = v188 + v179;
            v190 = *(v3 - 10);
            v191 = *(v3 - 15) + 1;
            *(v3 - 13) = v189;
            *(v3 - 15) = v191;
            LOWORD(v186) = v186 - 1;
            *(v3 - 4) = v186;
            if (!(_WORD)v186) {
              while (1) {
                v192 = *(v3 - 5);
                if ((_WORD)v192 == *((_WORD *)v3 - 6)) {
                  *(v3 - 10) = v190;
                  goto LABEL_140;
                }
                v193 = *(v3 - 6);
                v194 = *(v3 - 5) + 1;
                *((_WORD *)v3 - 19) = *(_WORD *)(*(v3 - 18) + 8 * (__int16)v192);
                *(v3 - 5) = v194;
                v195 = startsx[(__int16)v192];
                v196 = startsy[(__int16)v192];
                *(v3 - 16) = v195;
                *(v3 - 17) = v196;
                if ((_WORD)v194 == (_WORD)v193)
                  *(v3 - 5) = 0;
                v197 = *((__int16 *)v3 - 10);
                v11 = *(v3 - 18) + 8 * v197;
                LOWORD(v195) = *(_WORD *)(v11 + 4);
                v198 = v195 - *(v3 - 15);
                *(v3 - 4) = v198;
                if ((__int16)v198 > 0)
                  break;
                if ((v198 & 0x8000u) != 0)
                  return v11;
              }
              LOWORD(v11) = *(_WORD *)v11;
              v199 = v11 - *(int *)((char *)v3 - 38);
              *((_WORD *)v3 - 22) = 0;
              *((_WORD *)v3 - 21) = v199;
              v200 = v197;
              v201 = *(v3 - 11);
              *((_WORD *)v3 - 20) = 0;
              if (v201 >= 0) {
                *((_WORD *)v3 - 21) = v199 + 1;
                v210 = *((__int16 *)v3 - 8) + 1;
                *(v3 - 11) /= v210;
                v211 = startsy[v200] - *(v3 - 17);
                *(v3 - 22) = (startsx[v200] - *(v3 - 16)) / v210;
                *(v3 - 19) = v211 / v210;
              } else {
                *((_WORD *)v3 - 21) = v199 - 1;
                v202 = *((__int16 *)v3 - 8) + 1;
                v203 = *(v3 - 11) / v202;
                v204 = *(v3 - 10);
                *(v3 - 11) = v203;
                v205 = v203 + v204;
                v206 = (startsx[v200] - *(v3 - 16)) / v202;
                *(v3 - 16) += v206;
                v207 = startsy[v200];
                v208 = *(v3 - 17);
                *(v3 - 22) = v206;
                v209 = (v207 - v208) / v202;
                *(v3 - 10) = v205;
                ++*((_WORD *)v3 - 19);
                *(v3 - 19) = v209;
                *(v3 - 17) = v208 + v209;
              }
            }
            v212 = *(v3 - 8);
            v213 = *(v3 - 9);
            LOWORD(v212) = v212 - 1;
            *(v3 - 8) = v212;
            if (!(_WORD)v212) {
              while (1) {
                v214 = *(v3 - 3);
                if ((unsigned __int16)*(v3 - 5) == (_WORD)v214) {
                  *(v3 - 10) = v190;
                  *(v3 - 9) = v213;
                  goto LABEL_140;
                }
                *((_WORD *)v3 - 17) = *(_WORD *)(*(v3 - 18) + 8 * (__int16)v214);
                v215 = startsx[(__int16)v214];
                v216 = startsy[(__int16)v214];
                *(v3 - 3) = v214 - 1;
                *(v3 - 13) = v216;
                *(v3 - 14) = v215;
                if ((__int16)(v214 - 1) == -1)
                  *(v3 - 3) = *(v3 - 6) - 1;
                v217 = *((__int16 *)v3 - 6);
                v218 = *(v3 - 18);
                v11 = v218 + 8 * v217;
                LOWORD(v218) = *(_WORD *)(v11 + 4);
                v219 = v218 - *(v3 - 15);
                *(v3 - 8) = v219;
                if ((__int16)v219 > 0)
                  break;
                if ((v219 & 0x8000u) != 0)
                  return v11;
              }
              LOWORD(v11) = *(_WORD *)v11;
              v220 = v11 - *(int *)((char *)v3 - 34);
              *((_WORD *)v3 - 24) = 0;
              *((_WORD *)v3 - 23) = v220;
              v221 = v217;
              v222 = *(v3 - 12);
              *((_WORD *)v3 - 18) = -1;
              if (v222 <= 0) {
                *((_WORD *)v3 - 23) = v220 - 1;
                v230 = (__int16)v219 + 1;
                v231 = *(v3 - 12) / v230;
                v232 = *(v3 - 14);
                *((_WORD *)v3 - 17) = *(int *)((char *)v3 - 34) + 1;
                v233 = startsx[v221] - v232;
                *(v3 - 12) = v231;
                v234 = v233;
                v235 = startsy[v221] - *(v3 - 13);
                *(v3 - 21) = v234 / v230;
                *(v3 - 20) = v235 / v230;
              } else {
                *((_WORD *)v3 - 23) = v220 + 1;
                v223 = (__int16)v219 + 1;
                v224 = *(v3 - 12) / v223;
                v225 = *(v3 - 14);
                *(v3 - 9) += v224;
                v226 = startsx[v221] - v225;
                *(v3 - 12) = v224;
                *(v3 - 21) = v226 / v223;
                v227 = v225 + v226 / v223;
                v228 = (startsy[v221] - *(v3 - 13)) / v223;
                v229 = *(v3 - 13);
                *(v3 - 14) = v227;
                *(v3 - 20) = v228;
                *(v3 - 13) = v228 + v229;
              }
            }
            v11 = *(v3 - 15);
            if (v11 >= winh)
              return v11;
          }
          v11 = *((__int16 *)v3 - 19);
          if (v11 >= winw)
            return v11;
          while (1) {
            v11 = *((__int16 *)v3 - 17);
            if (v11 > (unsigned int)winw)
              break;
          LABEL_162:
            v11 = *(int *)((char *)v3 - 34);
            *((_WORD *)v3 - 14) = v11;
            if (*((__int16 *)v3 - 14) > 0) {
              v261 = (__int16)(*((_WORD *)v3 - 17) - *((_WORD *)v3 - 19));
              v262 = *(v3 - 13);
              v263 = *(v3 - 17) - v262;
              *(int *)((char *)&startsy_variable_8 + 2) = (*(v3 - 16) - *(v3 - 14)) / v261;
              *(int *)((char *)&startsy_variable_10 + 2) = v263 / v261;
              v264 = *((__int16 *)v3 - 17);
              *(int *)((char *)&startsy_variable_4 + 2) = *(v3 - 14);
              v265 = winw * *(v3 - 15);
              *(int *)((char *)&startsy_variable_6 + 2) = v262;
              *(v3 - 23) = v265 + scrptr + v264;
              if (*((__int16 *)v3 - 14) > 7) {
                v898 = v3;
                v890 = __DS__;
                HIWORD(v294) = HIWORD(startsy_variable_4);
                HIWORD(v288) = HIWORD(startsy_variable_6);
                BYTE1(v294) = BYTE1(startsy_variable_8);
                HIWORD(v289) = HIWORD(startsy_variable_8);
                v293 = startsy_variable_10;
                LOWORD(v289) = startsy_variable_12;
                v290 = *((_WORD *)v3 - 14);
                __DS__ = *((_WORD *)v3 - 2);
                v291 = (_WORD *)*(v3 - 23);
                LOWORD(v288) = startsy_variable_6 - startsy_variable_10;
                v83 = __CFADD__(startsy_variable_10, v288);
                v292 = (char *)(startsy_variable_10 + v288);
                BYTE1(v292) = startsy_variable_8;
                BYTE1(v293) = 0;
                LOBYTE(v294) = v83 + startsy_variable_8;
                if (((unsigned __int8)v291 & 1) != 0) {
                  v295 = *v292;
                  v83 = __CFADD__(__PAIR64__(v293, v289), __PAIR64__((unsigned int)v292, v294));
                  v292 = (char *)((__PAIR64__(v293, v289) + __PAIR64__((unsigned int)v292, v294)) >> 32);
                  v294 += v289;
                  BYTE1(v292) = v294;
                  LOBYTE(v294) = v83 + v294;
                  v291 = (_WORD *)((char *)v291 - 1);
                  *(_BYTE *)v291 = v295;
                  --v290;
                }
                if (((unsigned __int8)v291 & 2) != 0) {
                  HIBYTE(v296) = *v292;
                  v83 = __CFADD__(__PAIR64__(v293, v289), __PAIR64__((unsigned int)v292, v294));
                  v298 = v289 + v294;
                  v297 = (_BYTE *)((__PAIR64__(v293, v289) + __PAIR64__((unsigned int)v292, v294)) >> 32);
                  BYTE1(v297) = v289 + v294;
                  LOBYTE(v296) = *v297;
                  v294 += v289 + v83 + v289;
                  v300 = __CFADD__(v83, v298) | __CFADD__(v289, v83 + v298);
                  v83 = __CFADD__(v300, v297);
                  v299 = &v297[v300];
                  v83 |= __CFADD__(v293, v299);
                  v292 = &v299[v293];
                  BYTE1(v292) = v294;
                  LOBYTE(v294) = v83 + v294;
                  *--v291 = v296;
                  v290 -= 2;
                }
                if (((unsigned __int8)v291 & 4) != 0) {
                  LOBYTE(v265) = *v292;
                  v83 = __CFADD__(__PAIR64__(v293, v289), __PAIR64__((unsigned int)v292, v294));
                  v302 = v289 + v294;
                  v301 = (_BYTE *)((__PAIR64__(v293, v289) + __PAIR64__((unsigned int)v292, v294)) >> 32);
                  BYTE1(v301) = v289 + v294;
                  BYTE1(v265) = *v301;
                  v303 = v289 + v83 + v289 + v294;
                  v305 = __CFADD__(v83, v302) | __CFADD__(v289, v83 + v302);
                  v83 = __CFADD__(v305, v301);
                  v304 = &v301[v305];
                  v83 |= __CFADD__(v293, v304);
                  v304 += v293;
                  BYTE1(v304) = v303;
                  v265 = _byteswap_ulong(v265);
                  BYTE1(v265) = *v304;
                  v307 = v83;
                  v83 = __CFADD__(v83, v303);
                  v306 = v307 + v303;
                  v83 |= __CFADD__(v289, v306);
                  v306 += v289;
                  v309 = v83;
                  v83 = __CFADD__(v83, v304);
                  v308 = &v304[v309];
                  v83 |= __CFADD__(v293, v308);
                  v308 += v293;
                  BYTE1(v308) = v306;
                  LOBYTE(v265) = *v308;
                  v311 = v83;
                  v83 = __CFADD__(v83, v306);
                  v310 = v311 + v306;
                  v83 |= __CFADD__(v289, v310);
                  v294 = v289 + v310;
                  v313 = v83;
                  v83 = __CFADD__(v83, v308);
                  v312 = &v308[v313];
                  v83 |= __CFADD__(v293, v312);
                  v292 = &v312[v293];
                  BYTE1(v292) = v294;
                  LOBYTE(v294) = v83 + v294;
                  v291 -= 2;
                  *(_DWORD *)v291 = v265;
                  v290 -= 4;
                }
                v83 = v290 < 8u;
                for (j = v290 - 8; !v83; j -= 8) {
                  LOBYTE(v265) = *v292;
                  v83 = __CFADD__(__PAIR64__(v293, v289), __PAIR64__((unsigned int)v292, v294));
                  v316 = v289 + v294;
                  v315 = (_BYTE *)((__PAIR64__(v293, v289) + __PAIR64__((unsigned int)v292, v294)) >> 32);
                  BYTE1(v315) = v289 + v294;
                  BYTE1(v265) = *v315;
                  v317 = v289 + v83 + v289 + v294;
                  v319 = __CFADD__(v83, v316) | __CFADD__(v289, v83 + v316);
                  v83 = __CFADD__(v319, v315);
                  v318 = &v315[v319];
                  v83 |= __CFADD__(v293, v318);
                  v318 += v293;
                  BYTE1(v318) = v317;
                  v320 = _byteswap_ulong(v265);
                  BYTE1(v320) = *v318;
                  v322 = v83;
                  v83 = __CFADD__(v83, v317);
                  v321 = v322 + v317;
                  v83 |= __CFADD__(v289, v321);
                  v321 += v289;
                  v324 = v83;
                  v83 = __CFADD__(v83, v318);
                  v323 = &v318[v324];
                  v83 |= __CFADD__(v293, v323);
                  v323 += v293;
                  BYTE1(v323) = v321;
                  LOBYTE(v320) = *v323;
                  v326 = v83;
                  v83 = __CFADD__(v83, v321);
                  v325 = v326 + v321;
                  v83 |= __CFADD__(v289, v325);
                  v325 += v289;
                  v328 = v83;
                  v83 = __CFADD__(v83, v323);
                  v327 = &v323[v328];
                  v83 |= __CFADD__(v293, v327);
                  v327 += v293;
                  BYTE1(v327) = v325;
                  *((_DWORD *)v291 - 1) = v320;
                  LOBYTE(v320) = *v327;
                  v330 = v83;
                  v83 = __CFADD__(v83, v325);
                  v329 = v330 + v325;
                  v83 |= __CFADD__(v289, v329);
                  v329 += v289;
                  v332 = v83;
                  v83 = __CFADD__(v83, v327);
                  v331 = &v327[v332];
                  v83 |= __CFADD__(v293, v331);
                  v331 += v293;
                  BYTE1(v331) = v329;
                  BYTE1(v320) = *v331;
                  v334 = v83;
                  v83 = __CFADD__(v83, v329);
                  v333 = v334 + v329;
                  v83 |= __CFADD__(v289, v333);
                  v333 += v289;
                  v336 = v83;
                  v83 = __CFADD__(v83, v331);
                  v335 = &v331[v336];
                  v83 |= __CFADD__(v293, v335);
                  v335 += v293;
                  BYTE1(v335) = v333;
                  v265 = _byteswap_ulong(v320);
                  BYTE1(v265) = *v335;
                  v338 = v83;
                  v83 = __CFADD__(v83, v333);
                  v337 = v338 + v333;
                  v83 |= __CFADD__(v289, v337);
                  v337 += v289;
                  v340 = v83;
                  v83 = __CFADD__(v83, v335);
                  v339 = &v335[v340];
                  v83 |= __CFADD__(v293, v339);
                  v339 += v293;
                  BYTE1(v339) = v337;
                  LOBYTE(v265) = *v339;
                  v342 = v83;
                  v83 = __CFADD__(v83, v337);
                  v341 = v342 + v337;
                  v83 |= __CFADD__(v289, v341);
                  v294 = v289 + v341;
                  v344 = v83;
                  v83 = __CFADD__(v83, v339);
                  v343 = &v339[v344];
                  v83 |= __CFADD__(v293, v343);
                  v292 = &v343[v293];
                  BYTE1(v292) = v294;
                  LOBYTE(v294) = v83 + v294;
                  v291 -= 4;
                  *(_DWORD *)v291 = v265;
                  v83 = j < 8u;
                }
                if ((j & 4) != 0) {
                  LOBYTE(v265) = *v292;
                  v83 = __CFADD__(__PAIR64__(v293, v289), __PAIR64__((unsigned int)v292, v294));
                  v346 = v289 + v294;
                  v345 = (_BYTE *)((__PAIR64__(v293, v289) + __PAIR64__((unsigned int)v292, v294)) >> 32);
                  BYTE1(v345) = v289 + v294;
                  BYTE1(v265) = *v345;
                  v347 = v289 + v83 + v289 + v294;
                  v349 = __CFADD__(v83, v346) | __CFADD__(v289, v83 + v346);
                  v83 = __CFADD__(v349, v345);
                  v348 = &v345[v349];
                  v83 |= __CFADD__(v293, v348);
                  v348 += v293;
                  BYTE1(v348) = v347;
                  v350 = _byteswap_ulong(v265);
                  BYTE1(v350) = *v348;
                  v352 = v83;
                  v83 = __CFADD__(v83, v347);
                  v351 = v352 + v347;
                  v83 |= __CFADD__(v289, v351);
                  v351 += v289;
                  v354 = v83;
                  v83 = __CFADD__(v83, v348);
                  v353 = &v348[v354];
                  v83 |= __CFADD__(v293, v353);
                  v353 += v293;
                  BYTE1(v353) = v351;
                  LOBYTE(v350) = *v353;
                  v356 = v83;
                  v83 = __CFADD__(v83, v351);
                  v355 = v356 + v351;
                  v83 |= __CFADD__(v289, v355);
                  v294 = v289 + v355;
                  v358 = v83;
                  v83 = __CFADD__(v83, v353);
                  v357 = &v353[v358];
                  v83 |= __CFADD__(v293, v357);
                  v292 = &v357[v293];
                  BYTE1(v292) = v294;
                  LOBYTE(v294) = v83 + v294;
                  v291 -= 2;
                  *(_DWORD *)v291 = v350;
                }
                if ((j & 2) != 0) {
                  HIBYTE(v359) = *v292;
                  v83 = __CFADD__(__PAIR64__(v293, v289), __PAIR64__((unsigned int)v292, v294));
                  v292 = (char *)((__PAIR64__(v293, v289) + __PAIR64__((unsigned int)v292, v294)) >> 32);
                  BYTE1(v292) = v289 + v294;
                  LOBYTE(v359) = *v292;
                  LOBYTE(v292) = v293 + (__CFADD__(v83, v289 + v294) | __CFADD__(v289, v83 + v289 + v294)) + (_BYTE)v292;
                  BYTE1(v292) = v289 + v83 + v289 + v294;
                  *--v291 = v359;
                }
                if ((j & 1) != 0)
                  *((_BYTE *)v291 - 1) = *v292;
                __DS__ = v890;
                v3 = v898;
              } else {
                v897 = v3;
                v889 = __DS__;
                HIWORD(v272) = HIWORD(startsy_variable_4);
                HIWORD(v266) = HIWORD(startsy_variable_6);
                BYTE1(v272) = BYTE1(startsy_variable_8);
                HIWORD(v267) = HIWORD(startsy_variable_8);
                v271 = startsy_variable_10;
                LOWORD(v267) = startsy_variable_12;
                v268 = *((_WORD *)v3 - 14);
                __DS__ = *((_WORD *)v3 - 2);
                v269 = (_DWORD *)*(v3 - 23);
                LOWORD(v266) = startsy_variable_6 - startsy_variable_10;
                v83 = __CFADD__(startsy_variable_10, v266);
                v270 = (_BYTE *)(startsy_variable_10 + v266);
                BYTE1(v270) = startsy_variable_8;
                BYTE1(v271) = 0;
                LOBYTE(v272) = v83 + startsy_variable_8;
                if ((v268 & 4) != 0) {
                  LOBYTE(v265) = *v270;
                  v83 = __CFADD__(__PAIR64__(v271, v267), __PAIR64__((unsigned int)v270, v272));
                  v274 = v267 + v272;
                  v273 = (_BYTE *)((__PAIR64__(v271, v267) + __PAIR64__((unsigned int)v270, v272)) >> 32);
                  BYTE1(v273) = startsy_variable_12 + v272;
                  BYTE1(v265) = *v273;
                  v275 = v267 + v83 + v267 + v272;
                  v277 = __CFADD__(v83, v274) | __CFADD__(v267, v83 + v274);
                  v83 = __CFADD__(v277, v273);
                  v276 = &v273[v277];
                  v83 |= __CFADD__(v271, v276);
                  v276 += v271;
                  BYTE1(v276) = v275;
                  v278 = _byteswap_ulong(v265);
                  BYTE1(v278) = *v276;
                  v280 = v83;
                  v83 = __CFADD__(v83, v275);
                  v279 = v280 + v275;
                  v83 |= __CFADD__(v267, v279);
                  v279 += v267;
                  v282 = v83;
                  v83 = __CFADD__(v83, v276);
                  v281 = &v276[v282];
                  v83 |= __CFADD__(v271, v281);
                  v281 += v271;
                  BYTE1(v281) = v279;
                  LOBYTE(v278) = *v281;
                  v284 = v83;
                  v83 = __CFADD__(v83, v279);
                  v283 = v284 + v279;
                  v83 |= __CFADD__(v267, v283);
                  v272 = v267 + v283;
                  v286 = v83;
                  v83 = __CFADD__(v83, v281);
                  v285 = &v281[v286];
                  v83 |= __CFADD__(v271, v285);
                  v270 = &v285[v271];
                  BYTE1(v270) = v272;
                  LOBYTE(v272) = v83 + v272;
                  *--v269 = v278;
                }
                if ((v268 & 2) != 0) {
                  HIBYTE(v287) = *v270;
                  v83 = __CFADD__(__PAIR64__(v271, v267), __PAIR64__((unsigned int)v270, v272));
                  v270 = (_BYTE *)((__PAIR64__(v271, v267) + __PAIR64__((unsigned int)v270, v272)) >> 32);
                  BYTE1(v270) = v267 + v272;
                  LOBYTE(v287) = *v270;
                  LOBYTE(v270) = v271 + (__CFADD__(v83, v267 + v272) | __CFADD__(v267, v83 + v267 + v272)) + (_BYTE)v270;
                  BYTE1(v270) = v267 + v83 + v267 + v272;
                  v269 = (_DWORD *)((char *)v269 - 2);
                  *(_WORD *)v269 = v287;
                }
                if ((v268 & 1) != 0)
                  *((_BYTE *)v269 - 1) = *v270;
                __DS__ = v889;
                v3 = v897;
              }
            } else if (*((__int16 *)v3 - 14) < 0) {
              return v11;
            }
            v360 = *(v3 - 16);
            v361 = *(v3 - 17);
            v362 = *(v3 - 9);
            v363 = *(v3 - 14);
            v364 = *(v3 - 22);
            *(v3 - 10) += *(v3 - 11);
            v365 = *(v3 - 13);
            v366 = v364 + v360;
            v367 = *(v3 - 19);
            *(v3 - 16) = v366;
            v368 = v367 + v361;
            v369 = *(v3 - 12);
            *(v3 - 17) = v368;
            v370 = v369 + v362;
            v371 = *(v3 - 21);
            *(v3 - 9) = v370;
            v372 = v371 + v363;
            v373 = *(v3 - 20);
            *(v3 - 14) = v372;
            v374 = *(v3 - 10);
            v375 = v373 + v365;
            v376 = *(v3 - 15);
            *(v3 - 13) = v375;
            v377 = *(v3 - 4);
            *(v3 - 15) = v376 + 1;
            LOWORD(v377) = v377 - 1;
            *(v3 - 4) = v377;
            if (!(_WORD)v377) {
              while (1) {
                v378 = *(v3 - 5);
                if ((_WORD)v378 == *((_WORD *)v3 - 6))
                  break;
                v379 = *(v3 - 6);
                v380 = *(v3 - 5) + 1;
                *((_WORD *)v3 - 19) = *(_WORD *)(*(v3 - 18) + 8 * (__int16)v378);
                *(v3 - 5) = v380;
                v381 = startsx[(__int16)v378];
                v382 = startsy[(__int16)v378];
                *(v3 - 16) = v381;
                *(v3 - 17) = v382;
                if ((_WORD)v380 == (_WORD)v379)
                  *(v3 - 5) = 0;
                v383 = *((__int16 *)v3 - 10);
                v11 = *(v3 - 18) + 8 * v383;
                LOWORD(v381) = *(_WORD *)(v11 + 4);
                v384 = v381 - *(v3 - 15);
                *(v3 - 4) = v384;
                if ((__int16)v384 > 0) {
                  LOWORD(v11) = *(_WORD *)v11;
                  v385 = v11 - *(int *)((char *)v3 - 38);
                  *((_WORD *)v3 - 22) = 0;
                  *((_WORD *)v3 - 21) = v385;
                  v386 = v383;
                  v387 = *(v3 - 11);
                  *((_WORD *)v3 - 20) = 0;
                  if (v387 >= 0) {
                    *((_WORD *)v3 - 21) = v385 + 1;
                    v396 = *((__int16 *)v3 - 8) + 1;
                    *(v3 - 11) /= v396;
                    v397 = startsy[v386] - *(v3 - 17);
                    *(v3 - 22) = (startsx[v386] - *(v3 - 16)) / v396;
                    *(v3 - 19) = v397 / v396;
                  } else {
                    *((_WORD *)v3 - 21) = v385 - 1;
                    v388 = *((__int16 *)v3 - 8) + 1;
                    v389 = *(v3 - 11) / v388;
                    v390 = *(v3 - 10);
                    *(v3 - 11) = v389;
                    v391 = v389 + v390;
                    v392 = (startsx[v386] - *(v3 - 16)) / v388;
                    *(v3 - 16) += v392;
                    v393 = startsy[v386];
                    v394 = *(v3 - 17);
                    *(v3 - 22) = v392;
                    v395 = (v393 - v394) / v388;
                    *(v3 - 10) = v391;
                    ++*((_WORD *)v3 - 19);
                    *(v3 - 19) = v395;
                    *(v3 - 17) = v394 + v395;
                  }
                  goto LABEL_199;
                }
                if ((v384 & 0x8000u) != 0)
                  return v11;
              }
              *(v3 - 10) = v374;
            LABEL_212:
              v11 = *(v3 - 15);
              if (v11 < winh) {
                if (*((__int16 *)v3 - 19) >= (unsigned int)winw)
                  goto LABEL_216;
                v11 = *((__int16 *)v3 - 19);
                if (v11 >= winw)
                  return v11;
                goto LABEL_144;
              }
              return v11;
            }
          LABEL_199:
            v398 = *(v3 - 8);
            v399 = *(v3 - 9);
            LOWORD(v398) = v398 - 1;
            *(v3 - 8) = v398;
            if (!(_WORD)v398) {
              while (1) {
                v400 = *(v3 - 3);
                if ((unsigned __int16)*(v3 - 5) == (_WORD)v400) {
                  *(v3 - 10) = v374;
                  *(v3 - 9) = v399;
                  goto LABEL_212;
                }
                *((_WORD *)v3 - 17) = *(_WORD *)(*(v3 - 18) + 8 * (__int16)v400);
                v401 = startsx[(__int16)v400];
                v402 = startsy[(__int16)v400];
                *(v3 - 3) = v400 - 1;
                *(v3 - 13) = v402;
                *(v3 - 14) = v401;
                if ((__int16)(v400 - 1) == -1)
                  *(v3 - 3) = *(v3 - 6) - 1;
                v403 = *((__int16 *)v3 - 6);
                v404 = *(v3 - 18);
                v11 = v404 + 8 * v403;
                LOWORD(v404) = *(_WORD *)(v11 + 4);
                v405 = v404 - *(v3 - 15);
                *(v3 - 8) = v405;
                if ((__int16)v405 > 0)
                  break;
                if ((v405 & 0x8000u) != 0)
                  return v11;
              }
              LOWORD(v11) = *(_WORD *)v11;
              v406 = v11 - *(int *)((char *)v3 - 34);
              *((_WORD *)v3 - 24) = 0;
              *((_WORD *)v3 - 23) = v406;
              v407 = v403;
              v408 = *(v3 - 12);
              *((_WORD *)v3 - 18) = -1;
              if (v408 <= 0) {
                *((_WORD *)v3 - 23) = v406 - 1;
                v416 = (__int16)v405 + 1;
                v417 = *(v3 - 12) / v416;
                v418 = *(v3 - 14);
                *((_WORD *)v3 - 17) = *(int *)((char *)v3 - 34) + 1;
                v419 = startsx[v407] - v418;
                *(v3 - 12) = v417;
                v420 = v419;
                v421 = startsy[v407] - *(v3 - 13);
                *(v3 - 21) = v420 / v416;
                *(v3 - 20) = v421 / v416;
              } else {
                *((_WORD *)v3 - 23) = v406 + 1;
                v409 = (__int16)v405 + 1;
                v410 = *(v3 - 12) / v409;
                v411 = *(v3 - 14);
                *(v3 - 9) += v410;
                v412 = startsx[v407] - v411;
                *(v3 - 12) = v410;
                *(v3 - 21) = v412 / v409;
                v413 = v411 + v412 / v409;
                v414 = (startsy[v407] - *(v3 - 13)) / v409;
                v415 = *(v3 - 13);
                *(v3 - 14) = v413;
                *(v3 - 20) = v414;
                *(v3 - 13) = v414 + v415;
              }
            }
            v11 = *(v3 - 15);
            if (v11 >= winh)
              return v11;
            if (*((__int16 *)v3 - 19) < (unsigned int)winw) {
              v11 = *((__int16 *)v3 - 19);
              if (v11 >= winw)
                return v11;
              goto LABEL_87;
            }
          }
          if (*((__int16 *)v3 - 17) <= 0)
            return v11;
          while (1) {
            *((_WORD *)v3 - 14) = *(int *)((char *)v3 - 34) - *(int *)((char *)v3 - 38);
            v635 = *(v3 - 14);
            v636 = *(v3 - 17);
            *(int *)((char *)&startsy_variable_8 + 2) = (*(v3 - 16) - v635) / *((__int16 *)v3 - 14);
            *(int *)((char *)&startsy_variable_10 + 2) = (v636 - *(v3 - 13)) / *((__int16 *)v3 - 14);
            v637 = *((__int16 *)v3 - 17) - winw;
            *(int *)((char *)&startsy_variable_4 + 2) = v635 + v637 * *(int *)((char *)&startsy_variable_8 + 2);
            *(int *)((char *)&startsy_variable_6 + 2) = *(int *)((char *)&startsy_variable_10 + 2) * v637 + *(v3 - 13);
            *((_WORD *)v3 - 14) = winw;
            v638 = winw * *(v3 - 15);
            *(v3 - 23) = v638 + scrptr1;
            if (*((__int16 *)v3 - 14) > 7) {
              v902 = v3;
              v894 = __DS__;
              HIWORD(v667) = HIWORD(startsy_variable_4);
              HIWORD(v661) = HIWORD(startsy_variable_6);
              BYTE1(v667) = BYTE1(startsy_variable_8);
              HIWORD(v662) = HIWORD(startsy_variable_8);
              v666 = startsy_variable_10;
              LOWORD(v662) = startsy_variable_12;
              v663 = *((_WORD *)v3 - 14);
              __DS__ = *((_WORD *)v3 - 2);
              v664 = (_WORD *)*(v3 - 23);
              LOWORD(v661) = startsy_variable_6 - startsy_variable_10;
              v83 = __CFADD__(startsy_variable_10, v661);
              v665 = (char *)(startsy_variable_10 + v661);
              BYTE1(v665) = startsy_variable_8;
              BYTE1(v666) = 0;
              LOBYTE(v667) = v83 + startsy_variable_8;
              if (((unsigned __int8)v664 & 1) != 0) {
                v668 = *v665;
                v83 = __CFADD__(__PAIR64__(v666, v662), __PAIR64__((unsigned int)v665, v667));
                v665 = (char *)((__PAIR64__(v666, v662) + __PAIR64__((unsigned int)v665, v667)) >> 32);
                v667 += v662;
                BYTE1(v665) = v667;
                LOBYTE(v667) = v83 + v667;
                v664 = (_WORD *)((char *)v664 - 1);
                *(_BYTE *)v664 = v668;
                --v663;
              }
              if (((unsigned __int8)v664 & 2) != 0) {
                HIBYTE(v669) = *v665;
                v83 = __CFADD__(__PAIR64__(v666, v662), __PAIR64__((unsigned int)v665, v667));
                v671 = v662 + v667;
                v670 = (_BYTE *)((__PAIR64__(v666, v662) + __PAIR64__((unsigned int)v665, v667)) >> 32);
                BYTE1(v670) = v662 + v667;
                LOBYTE(v669) = *v670;
                v667 += v662 + v83 + v662;
                v673 = __CFADD__(v83, v671) | __CFADD__(v662, v83 + v671);
                v83 = __CFADD__(v673, v670);
                v672 = &v670[v673];
                v83 |= __CFADD__(v666, v672);
                v665 = &v672[v666];
                BYTE1(v665) = v667;
                LOBYTE(v667) = v83 + v667;
                *--v664 = v669;
                v663 -= 2;
              }
              if (((unsigned __int8)v664 & 4) != 0) {
                LOBYTE(v638) = *v665;
                v83 = __CFADD__(__PAIR64__(v666, v662), __PAIR64__((unsigned int)v665, v667));
                v675 = v662 + v667;
                v674 = (_BYTE *)((__PAIR64__(v666, v662) + __PAIR64__((unsigned int)v665, v667)) >> 32);
                BYTE1(v674) = v662 + v667;
                BYTE1(v638) = *v674;
                v676 = v662 + v83 + v662 + v667;
                v678 = __CFADD__(v83, v675) | __CFADD__(v662, v83 + v675);
                v83 = __CFADD__(v678, v674);
                v677 = &v674[v678];
                v83 |= __CFADD__(v666, v677);
                v677 += v666;
                BYTE1(v677) = v676;
                v638 = _byteswap_ulong(v638);
                BYTE1(v638) = *v677;
                v680 = v83;
                v83 = __CFADD__(v83, v676);
                v679 = v680 + v676;
                v83 |= __CFADD__(v662, v679);
                v679 += v662;
                v682 = v83;
                v83 = __CFADD__(v83, v677);
                v681 = &v677[v682];
                v83 |= __CFADD__(v666, v681);
                v681 += v666;
                BYTE1(v681) = v679;
                LOBYTE(v638) = *v681;
                v684 = v83;
                v83 = __CFADD__(v83, v679);
                v683 = v684 + v679;
                v83 |= __CFADD__(v662, v683);
                v667 = v662 + v683;
                v686 = v83;
                v83 = __CFADD__(v83, v681);
                v685 = &v681[v686];
                v83 |= __CFADD__(v666, v685);
                v665 = &v685[v666];
                BYTE1(v665) = v667;
                LOBYTE(v667) = v83 + v667;
                v664 -= 2;
                *(_DWORD *)v664 = v638;
                v663 -= 4;
              }
              v83 = v663 < 8u;
              for (k = v663 - 8; !v83; k -= 8) {
                LOBYTE(v638) = *v665;
                v83 = __CFADD__(__PAIR64__(v666, v662), __PAIR64__((unsigned int)v665, v667));
                v689 = v662 + v667;
                v688 = (_BYTE *)((__PAIR64__(v666, v662) + __PAIR64__((unsigned int)v665, v667)) >> 32);
                BYTE1(v688) = v662 + v667;
                BYTE1(v638) = *v688;
                v690 = v662 + v83 + v662 + v667;
                v692 = __CFADD__(v83, v689) | __CFADD__(v662, v83 + v689);
                v83 = __CFADD__(v692, v688);
                v691 = &v688[v692];
                v83 |= __CFADD__(v666, v691);
                v691 += v666;
                BYTE1(v691) = v690;
                v693 = _byteswap_ulong(v638);
                BYTE1(v693) = *v691;
                v695 = v83;
                v83 = __CFADD__(v83, v690);
                v694 = v695 + v690;
                v83 |= __CFADD__(v662, v694);
                v694 += v662;
                v697 = v83;
                v83 = __CFADD__(v83, v691);
                v696 = &v691[v697];
                v83 |= __CFADD__(v666, v696);
                v696 += v666;
                BYTE1(v696) = v694;
                LOBYTE(v693) = *v696;
                v699 = v83;
                v83 = __CFADD__(v83, v694);
                v698 = v699 + v694;
                v83 |= __CFADD__(v662, v698);
                v698 += v662;
                v701 = v83;
                v83 = __CFADD__(v83, v696);
                v700 = &v696[v701];
                v83 |= __CFADD__(v666, v700);
                v700 += v666;
                BYTE1(v700) = v698;
                *((_DWORD *)v664 - 1) = v693;
                LOBYTE(v693) = *v700;
                v703 = v83;
                v83 = __CFADD__(v83, v698);
                v702 = v703 + v698;
                v83 |= __CFADD__(v662, v702);
                v702 += v662;
                v705 = v83;
                v83 = __CFADD__(v83, v700);
                v704 = &v700[v705];
                v83 |= __CFADD__(v666, v704);
                v704 += v666;
                BYTE1(v704) = v702;
                BYTE1(v693) = *v704;
                v707 = v83;
                v83 = __CFADD__(v83, v702);
                v706 = v707 + v702;
                v83 |= __CFADD__(v662, v706);
                v706 += v662;
                v709 = v83;
                v83 = __CFADD__(v83, v704);
                v708 = &v704[v709];
                v83 |= __CFADD__(v666, v708);
                v708 += v666;
                BYTE1(v708) = v706;
                v638 = _byteswap_ulong(v693);
                BYTE1(v638) = *v708;
                v711 = v83;
                v83 = __CFADD__(v83, v706);
                v710 = v711 + v706;
                v83 |= __CFADD__(v662, v710);
                v710 += v662;
                v713 = v83;
                v83 = __CFADD__(v83, v708);
                v712 = &v708[v713];
                v83 |= __CFADD__(v666, v712);
                v712 += v666;
                BYTE1(v712) = v710;
                LOBYTE(v638) = *v712;
                v715 = v83;
                v83 = __CFADD__(v83, v710);
                v714 = v715 + v710;
                v83 |= __CFADD__(v662, v714);
                v667 = v662 + v714;
                v717 = v83;
                v83 = __CFADD__(v83, v712);
                v716 = &v712[v717];
                v83 |= __CFADD__(v666, v716);
                v665 = &v716[v666];
                BYTE1(v665) = v667;
                LOBYTE(v667) = v83 + v667;
                v664 -= 4;
                *(_DWORD *)v664 = v638;
                v83 = k < 8u;
              }
              if ((k & 4) != 0) {
                LOBYTE(v638) = *v665;
                v83 = __CFADD__(__PAIR64__(v666, v662), __PAIR64__((unsigned int)v665, v667));
                v719 = v662 + v667;
                v718 = (_BYTE *)((__PAIR64__(v666, v662) + __PAIR64__((unsigned int)v665, v667)) >> 32);
                BYTE1(v718) = v662 + v667;
                BYTE1(v638) = *v718;
                v720 = v662 + v83 + v662 + v667;
                v722 = __CFADD__(v83, v719) | __CFADD__(v662, v83 + v719);
                v83 = __CFADD__(v722, v718);
                v721 = &v718[v722];
                v83 |= __CFADD__(v666, v721);
                v721 += v666;
                BYTE1(v721) = v720;
                v723 = _byteswap_ulong(v638);
                BYTE1(v723) = *v721;
                v725 = v83;
                v83 = __CFADD__(v83, v720);
                v724 = v725 + v720;
                v83 |= __CFADD__(v662, v724);
                v724 += v662;
                v727 = v83;
                v83 = __CFADD__(v83, v721);
                v726 = &v721[v727];
                v83 |= __CFADD__(v666, v726);
                v726 += v666;
                BYTE1(v726) = v724;
                LOBYTE(v723) = *v726;
                v729 = v83;
                v83 = __CFADD__(v83, v724);
                v728 = v729 + v724;
                v83 |= __CFADD__(v662, v728);
                v667 = v662 + v728;
                v731 = v83;
                v83 = __CFADD__(v83, v726);
                v730 = &v726[v731];
                v83 |= __CFADD__(v666, v730);
                v665 = &v730[v666];
                BYTE1(v665) = v667;
                LOBYTE(v667) = v83 + v667;
                v664 -= 2;
                *(_DWORD *)v664 = v723;
              }
              if ((k & 2) != 0) {
                HIBYTE(v732) = *v665;
                v83 = __CFADD__(__PAIR64__(v666, v662), __PAIR64__((unsigned int)v665, v667));
                v665 = (char *)((__PAIR64__(v666, v662) + __PAIR64__((unsigned int)v665, v667)) >> 32);
                BYTE1(v665) = v662 + v667;
                LOBYTE(v732) = *v665;
                LOBYTE(v665) = v666 + (__CFADD__(v83, v662 + v667) | __CFADD__(v662, v83 + v662 + v667)) + (_BYTE)v665;
                BYTE1(v665) = v662 + v83 + v662 + v667;
                *--v664 = v732;
              }
              if ((k & 1) != 0)
                *((_BYTE *)v664 - 1) = *v665;
              __DS__ = v894;
              v3 = v902;
            } else {
              v901 = v3;
              v893 = __DS__;
              HIWORD(v645) = HIWORD(startsy_variable_4);
              HIWORD(v639) = HIWORD(startsy_variable_6);
              BYTE1(v645) = BYTE1(startsy_variable_8);
              HIWORD(v640) = HIWORD(startsy_variable_8);
              v644 = startsy_variable_10;
              LOWORD(v640) = startsy_variable_12;
              v641 = *((_WORD *)v3 - 14);
              __DS__ = *((_WORD *)v3 - 2);
              v642 = (_DWORD *)*(v3 - 23);
              LOWORD(v639) = startsy_variable_6 - startsy_variable_10;
              v83 = __CFADD__(startsy_variable_10, v639);
              v643 = (_BYTE *)(startsy_variable_10 + v639);
              BYTE1(v643) = startsy_variable_8;
              BYTE1(v644) = 0;
              LOBYTE(v645) = v83 + startsy_variable_8;
              if ((v641 & 4) != 0) {
                LOBYTE(v638) = *v643;
                v83 = __CFADD__(__PAIR64__(v644, v640), __PAIR64__((unsigned int)v643, v645));
                v647 = v640 + v645;
                v646 = (_BYTE *)((__PAIR64__(v644, v640) + __PAIR64__((unsigned int)v643, v645)) >> 32);
                BYTE1(v646) = startsy_variable_12 + v645;
                BYTE1(v638) = *v646;
                v648 = v640 + v83 + v640 + v645;
                v650 = __CFADD__(v83, v647) | __CFADD__(v640, v83 + v647);
                v83 = __CFADD__(v650, v646);
                v649 = &v646[v650];
                v83 |= __CFADD__(v644, v649);
                v649 += v644;
                BYTE1(v649) = v648;
                v651 = _byteswap_ulong(v638);
                BYTE1(v651) = *v649;
                v653 = v83;
                v83 = __CFADD__(v83, v648);
                v652 = v653 + v648;
                v83 |= __CFADD__(v640, v652);
                v652 += v640;
                v655 = v83;
                v83 = __CFADD__(v83, v649);
                v654 = &v649[v655];
                v83 |= __CFADD__(v644, v654);
                v654 += v644;
                BYTE1(v654) = v652;
                LOBYTE(v651) = *v654;
                v657 = v83;
                v83 = __CFADD__(v83, v652);
                v656 = v657 + v652;
                v83 |= __CFADD__(v640, v656);
                v645 = v640 + v656;
                v659 = v83;
                v83 = __CFADD__(v83, v654);
                v658 = &v654[v659];
                v83 |= __CFADD__(v644, v658);
                v643 = &v658[v644];
                BYTE1(v643) = v645;
                LOBYTE(v645) = v83 + v645;
                *--v642 = v651;
              }
              if ((v641 & 2) != 0) {
                HIBYTE(v660) = *v643;
                v83 = __CFADD__(__PAIR64__(v644, v640), __PAIR64__((unsigned int)v643, v645));
                v643 = (_BYTE *)((__PAIR64__(v644, v640) + __PAIR64__((unsigned int)v643, v645)) >> 32);
                BYTE1(v643) = v640 + v645;
                LOBYTE(v660) = *v643;
                LOBYTE(v643) = v644 + (__CFADD__(v83, v640 + v645) | __CFADD__(v640, v83 + v640 + v645)) + (_BYTE)v643;
                BYTE1(v643) = v640 + v83 + v640 + v645;
                v642 = (_DWORD *)((char *)v642 - 2);
                *(_WORD *)v642 = v660;
              }
              if ((v641 & 1) != 0)
                *((_BYTE *)v642 - 1) = *v643;
              __DS__ = v893;
              v3 = v901;
            }
            v733 = *(v3 - 16);
            v734 = *(v3 - 17);
            v735 = *(v3 - 9);
            v736 = *(v3 - 14);
            v737 = *(v3 - 22);
            *(v3 - 10) += *(v3 - 11);
            v738 = *(v3 - 13);
            v739 = v737 + v733;
            v740 = *(v3 - 19);
            *(v3 - 16) = v739;
            v741 = v740 + v734;
            v742 = *(v3 - 12);
            v743 = *(v3 - 15) + 1;
            *(v3 - 17) = v741;
            *(v3 - 15) = v743;
            v744 = v742 + v735;
            v745 = *(v3 - 21);
            *(v3 - 9) = v744;
            v746 = v745 + v736;
            v747 = *(v3 - 20);
            *(v3 - 14) = v746;
            v748 = v747 + v738;
            v749 = *(v3 - 4);
            *(v3 - 13) = v748;
            v750 = *(v3 - 10);
            LOWORD(v749) = v749 - 1;
            *(v3 - 4) = v749;
            if (!(_WORD)v749)
              break;
          LABEL_336:
            v772 = *(v3 - 8);
            v773 = *(v3 - 9);
            LOWORD(v772) = v772 - 1;
            *(v3 - 8) = v772;
            if (!(_WORD)v772) {
              while (1) {
                v774 = *(v3 - 3);
                if ((unsigned __int16)*(v3 - 5) == (_WORD)v774) {
                  *(v3 - 10) = v750;
                  *(v3 - 9) = v773;
                  goto LABEL_349;
                }
                *((_WORD *)v3 - 17) = *(_WORD *)(*(v3 - 18) + 8 * (__int16)v774);
                v775 = startsx[(__int16)v774];
                v776 = startsy[(__int16)v774];
                *(v3 - 3) = v774 - 1;
                *(v3 - 13) = v776;
                *(v3 - 14) = v775;
                if ((__int16)(v774 - 1) == -1)
                  *(v3 - 3) = *(v3 - 6) - 1;
                v777 = *((__int16 *)v3 - 6);
                v778 = *(v3 - 18);
                v11 = v778 + 8 * v777;
                LOWORD(v778) = *(_WORD *)(v11 + 4);
                v779 = v778 - *(v3 - 15);
                *(v3 - 8) = v779;
                if ((__int16)v779 > 0)
                  break;
                if ((v779 & 0x8000u) != 0)
                  return v11;
              }
              v780 = v777;
              v781 = *(_WORD *)v11 - *(int *)((char *)v3 - 34);
              *((_WORD *)v3 - 24) = 0;
              *((_WORD *)v3 - 23) = v781;
              v782 = *(v3 - 12);
              *((_WORD *)v3 - 18) = -1;
              if (v782 <= 0) {
                --*((_WORD *)v3 - 23);
                v790 = (__int16)v779 + 1;
                v791 = startsx[v780] - *(v3 - 14);
                *(v3 - 12) /= v790;
                *(v3 - 21) = v791 / v790;
                v792 = (startsy[v780] - *(v3 - 13)) / v790;
                ++*((_WORD *)v3 - 17);
                *(v3 - 20) = v792;
              } else {
                ++*((_WORD *)v3 - 23);
                v783 = (__int16)v779 + 1;
                v784 = *(v3 - 12) / v783;
                v785 = *(v3 - 14);
                *(v3 - 9) += v784;
                v786 = startsx[v780] - v785;
                *(v3 - 12) = v784;
                *(v3 - 21) = v786 / v783;
                v787 = v785 + v786 / v783;
                v788 = (startsy[v780] - *(v3 - 13)) / v783;
                v789 = *(v3 - 13);
                *(v3 - 14) = v787;
                *(v3 - 20) = v788;
                *(v3 - 13) = v788 + v789;
              }
            }
            v11 = *(v3 - 15);
            if (v11 >= winh)
              return v11;
            if (*((__int16 *)v3 - 19) < (unsigned int)winw) {
              v11 = *((__int16 *)v3 - 19);
              if (v11 < winw) {
                while (1) {
                  v11 = *((__int16 *)v3 - 17);
                  if (v11 <= (unsigned int)winw) {
                    if (*((__int16 *)v3 - 17) <= 0)
                      return v11;
                    goto LABEL_90;
                  }
                LABEL_234:
                  *((_WORD *)v3 - 14) = *(int *)((char *)v3 - 34) - *(int *)((char *)v3 - 38);
                  v446 = *(v3 - 17);
                  v447 = *(v3 - 13);
                  *(int *)((char *)&startsy_variable_8 + 2) = (*(v3 - 16) - *(v3 - 14)) / *((__int16 *)v3 - 14);
                  v448 = winw;
                  *(int *)((char *)&startsy_variable_10 + 2) = (v446 - v447) / *((__int16 *)v3 - 14);
                  v449 = *((__int16 *)v3 - 17) - winw;
                  v450 = *(v3 - 13);
                  *(int *)((char *)&startsy_variable_4 + 2) = v449 * *(int *)((char *)&startsy_variable_8 + 2)
                    + *(v3 - 14);
                  v451 = *(int *)((char *)v3 - 38);
                  *(int *)((char *)&startsy_variable_6 + 2) = *(int *)((char *)&startsy_variable_10 + 2) * v449 + v450;
                  *((_WORD *)v3 - 14) = winw - v451;
                  v452 = v448 * *(v3 - 15) + scrptr1;
                  *(v3 - 23) = v452;
                  if (*((__int16 *)v3 - 14) > 7) {
                    v900 = v3;
                    v892 = __DS__;
                    HIWORD(v481) = HIWORD(startsy_variable_4);
                    HIWORD(v475) = HIWORD(startsy_variable_6);
                    BYTE1(v481) = BYTE1(startsy_variable_8);
                    HIWORD(v476) = HIWORD(startsy_variable_8);
                    v480 = startsy_variable_10;
                    LOWORD(v476) = startsy_variable_12;
                    v477 = *((_WORD *)v3 - 14);
                    __DS__ = *((_WORD *)v3 - 2);
                    v478 = (_WORD *)*(v3 - 23);
                    LOWORD(v475) = startsy_variable_6 - startsy_variable_10;
                    v83 = __CFADD__(startsy_variable_10, v475);
                    v479 = (char *)(startsy_variable_10 + v475);
                    BYTE1(v479) = startsy_variable_8;
                    BYTE1(v480) = 0;
                    LOBYTE(v481) = v83 + startsy_variable_8;
                    if (((unsigned __int8)v478 & 1) != 0) {
                      v482 = *v479;
                      v83 = __CFADD__(__PAIR64__(v480, v476), __PAIR64__((unsigned int)v479, v481));
                      v479 = (char *)((__PAIR64__(v480, v476) + __PAIR64__((unsigned int)v479, v481)) >> 32);
                      v481 += v476;
                      BYTE1(v479) = v481;
                      LOBYTE(v481) = v83 + v481;
                      v478 = (_WORD *)((char *)v478 - 1);
                      *(_BYTE *)v478 = v482;
                      --v477;
                    }
                    if (((unsigned __int8)v478 & 2) != 0) {
                      HIBYTE(v483) = *v479;
                      v83 = __CFADD__(__PAIR64__(v480, v476), __PAIR64__((unsigned int)v479, v481));
                      v485 = v476 + v481;
                      v484 = (_BYTE *)((__PAIR64__(v480, v476) + __PAIR64__((unsigned int)v479, v481)) >> 32);
                      BYTE1(v484) = v476 + v481;
                      LOBYTE(v483) = *v484;
                      v481 += v476 + v83 + v476;
                      v487 = __CFADD__(v83, v485) | __CFADD__(v476, v83 + v485);
                      v83 = __CFADD__(v487, v484);
                      v486 = &v484[v487];
                      v83 |= __CFADD__(v480, v486);
                      v479 = &v486[v480];
                      BYTE1(v479) = v481;
                      LOBYTE(v481) = v83 + v481;
                      *--v478 = v483;
                      v477 -= 2;
                    }
                    if (((unsigned __int8)v478 & 4) != 0) {
                      LOBYTE(v452) = *v479;
                      v83 = __CFADD__(__PAIR64__(v480, v476), __PAIR64__((unsigned int)v479, v481));
                      v489 = v476 + v481;
                      v488 = (_BYTE *)((__PAIR64__(v480, v476) + __PAIR64__((unsigned int)v479, v481)) >> 32);
                      BYTE1(v488) = v476 + v481;
                      BYTE1(v452) = *v488;
                      v490 = v476 + v83 + v476 + v481;
                      v492 = __CFADD__(v83, v489) | __CFADD__(v476, v83 + v489);
                      v83 = __CFADD__(v492, v488);
                      v491 = &v488[v492];
                      v83 |= __CFADD__(v480, v491);
                      v491 += v480;
                      BYTE1(v491) = v490;
                      v452 = _byteswap_ulong(v452);
                      BYTE1(v452) = *v491;
                      v494 = v83;
                      v83 = __CFADD__(v83, v490);
                      v493 = v494 + v490;
                      v83 |= __CFADD__(v476, v493);
                      v493 += v476;
                      v496 = v83;
                      v83 = __CFADD__(v83, v491);
                      v495 = &v491[v496];
                      v83 |= __CFADD__(v480, v495);
                      v495 += v480;
                      BYTE1(v495) = v493;
                      LOBYTE(v452) = *v495;
                      v498 = v83;
                      v83 = __CFADD__(v83, v493);
                      v497 = v498 + v493;
                      v83 |= __CFADD__(v476, v497);
                      v481 = v476 + v497;
                      v500 = v83;
                      v83 = __CFADD__(v83, v495);
                      v499 = &v495[v500];
                      v83 |= __CFADD__(v480, v499);
                      v479 = &v499[v480];
                      BYTE1(v479) = v481;
                      LOBYTE(v481) = v83 + v481;
                      v478 -= 2;
                      *(_DWORD *)v478 = v452;
                      v477 -= 4;
                    }
                    v83 = v477 < 8u;
                    for (m = v477 - 8; !v83; m -= 8) {
                      LOBYTE(v452) = *v479;
                      v83 = __CFADD__(__PAIR64__(v480, v476), __PAIR64__((unsigned int)v479, v481));
                      v503 = v476 + v481;
                      v502 = (_BYTE *)((__PAIR64__(v480, v476) + __PAIR64__((unsigned int)v479, v481)) >> 32);
                      BYTE1(v502) = v476 + v481;
                      BYTE1(v452) = *v502;
                      v504 = v476 + v83 + v476 + v481;
                      v506 = __CFADD__(v83, v503) | __CFADD__(v476, v83 + v503);
                      v83 = __CFADD__(v506, v502);
                      v505 = &v502[v506];
                      v83 |= __CFADD__(v480, v505);
                      v505 += v480;
                      BYTE1(v505) = v504;
                      v507 = _byteswap_ulong(v452);
                      BYTE1(v507) = *v505;
                      v509 = v83;
                      v83 = __CFADD__(v83, v504);
                      v508 = v509 + v504;
                      v83 |= __CFADD__(v476, v508);
                      v508 += v476;
                      v511 = v83;
                      v83 = __CFADD__(v83, v505);
                      v510 = &v505[v511];
                      v83 |= __CFADD__(v480, v510);
                      v510 += v480;
                      BYTE1(v510) = v508;
                      LOBYTE(v507) = *v510;
                      v513 = v83;
                      v83 = __CFADD__(v83, v508);
                      v512 = v513 + v508;
                      v83 |= __CFADD__(v476, v512);
                      v512 += v476;
                      v515 = v83;
                      v83 = __CFADD__(v83, v510);
                      v514 = &v510[v515];
                      v83 |= __CFADD__(v480, v514);
                      v514 += v480;
                      BYTE1(v514) = v512;
                      *((_DWORD *)v478 - 1) = v507;
                      LOBYTE(v507) = *v514;
                      v517 = v83;
                      v83 = __CFADD__(v83, v512);
                      v516 = v517 + v512;
                      v83 |= __CFADD__(v476, v516);
                      v516 += v476;
                      v519 = v83;
                      v83 = __CFADD__(v83, v514);
                      v518 = &v514[v519];
                      v83 |= __CFADD__(v480, v518);
                      v518 += v480;
                      BYTE1(v518) = v516;
                      BYTE1(v507) = *v518;
                      v521 = v83;
                      v83 = __CFADD__(v83, v516);
                      v520 = v521 + v516;
                      v83 |= __CFADD__(v476, v520);
                      v520 += v476;
                      v523 = v83;
                      v83 = __CFADD__(v83, v518);
                      v522 = &v518[v523];
                      v83 |= __CFADD__(v480, v522);
                      v522 += v480;
                      BYTE1(v522) = v520;
                      v452 = _byteswap_ulong(v507);
                      BYTE1(v452) = *v522;
                      v525 = v83;
                      v83 = __CFADD__(v83, v520);
                      v524 = v525 + v520;
                      v83 |= __CFADD__(v476, v524);
                      v524 += v476;
                      v527 = v83;
                      v83 = __CFADD__(v83, v522);
                      v526 = &v522[v527];
                      v83 |= __CFADD__(v480, v526);
                      v526 += v480;
                      BYTE1(v526) = v524;
                      LOBYTE(v452) = *v526;
                      v529 = v83;
                      v83 = __CFADD__(v83, v524);
                      v528 = v529 + v524;
                      v83 |= __CFADD__(v476, v528);
                      v481 = v476 + v528;
                      v531 = v83;
                      v83 = __CFADD__(v83, v526);
                      v530 = &v526[v531];
                      v83 |= __CFADD__(v480, v530);
                      v479 = &v530[v480];
                      BYTE1(v479) = v481;
                      LOBYTE(v481) = v83 + v481;
                      v478 -= 4;
                      *(_DWORD *)v478 = v452;
                      v83 = m < 8u;
                    }
                    if ((m & 4) != 0) {
                      LOBYTE(v452) = *v479;
                      v83 = __CFADD__(__PAIR64__(v480, v476), __PAIR64__((unsigned int)v479, v481));
                      v533 = v476 + v481;
                      v532 = (_BYTE *)((__PAIR64__(v480, v476) + __PAIR64__((unsigned int)v479, v481)) >> 32);
                      BYTE1(v532) = v476 + v481;
                      BYTE1(v452) = *v532;
                      v534 = v476 + v83 + v476 + v481;
                      v536 = __CFADD__(v83, v533) | __CFADD__(v476, v83 + v533);
                      v83 = __CFADD__(v536, v532);
                      v535 = &v532[v536];
                      v83 |= __CFADD__(v480, v535);
                      v535 += v480;
                      BYTE1(v535) = v534;
                      v537 = _byteswap_ulong(v452);
                      BYTE1(v537) = *v535;
                      v539 = v83;
                      v83 = __CFADD__(v83, v534);
                      v538 = v539 + v534;
                      v83 |= __CFADD__(v476, v538);
                      v538 += v476;
                      v541 = v83;
                      v83 = __CFADD__(v83, v535);
                      v540 = &v535[v541];
                      v83 |= __CFADD__(v480, v540);
                      v540 += v480;
                      BYTE1(v540) = v538;
                      LOBYTE(v537) = *v540;
                      v543 = v83;
                      v83 = __CFADD__(v83, v538);
                      v542 = v543 + v538;
                      v83 |= __CFADD__(v476, v542);
                      v481 = v476 + v542;
                      v545 = v83;
                      v83 = __CFADD__(v83, v540);
                      v544 = &v540[v545];
                      v83 |= __CFADD__(v480, v544);
                      v479 = &v544[v480];
                      BYTE1(v479) = v481;
                      LOBYTE(v481) = v83 + v481;
                      v478 -= 2;
                      *(_DWORD *)v478 = v537;
                    }
                    if ((m & 2) != 0) {
                      HIBYTE(v546) = *v479;
                      v83 = __CFADD__(__PAIR64__(v480, v476), __PAIR64__((unsigned int)v479, v481));
                      v479 = (char *)((__PAIR64__(v480, v476) + __PAIR64__((unsigned int)v479, v481)) >> 32);
                      BYTE1(v479) = v476 + v481;
                      LOBYTE(v546) = *v479;
                      LOBYTE(v479) = v480
                        + (__CFADD__(v83, v476 + v481) | __CFADD__(v476, v83 + v476 + v481))
                        + (_BYTE)v479;
                      BYTE1(v479) = v476 + v83 + v476 + v481;
                      *--v478 = v546;
                    }
                    if ((m & 1) != 0)
                      *((_BYTE *)v478 - 1) = *v479;
                    __DS__ = v892;
                    v3 = v900;
                  } else {
                    v899 = v3;
                    v891 = __DS__;
                    HIWORD(v459) = HIWORD(startsy_variable_4);
                    HIWORD(v453) = HIWORD(startsy_variable_6);
                    BYTE1(v459) = BYTE1(startsy_variable_8);
                    HIWORD(v454) = HIWORD(startsy_variable_8);
                    v458 = startsy_variable_10;
                    LOWORD(v454) = startsy_variable_12;
                    v455 = *((_WORD *)v3 - 14);
                    __DS__ = *((_WORD *)v3 - 2);
                    v456 = (_DWORD *)*(v3 - 23);
                    LOWORD(v453) = startsy_variable_6 - startsy_variable_10;
                    v83 = __CFADD__(startsy_variable_10, v453);
                    v457 = (_BYTE *)(startsy_variable_10 + v453);
                    BYTE1(v457) = startsy_variable_8;
                    BYTE1(v458) = 0;
                    LOBYTE(v459) = v83 + startsy_variable_8;
                    if ((v455 & 4) != 0) {
                      LOBYTE(v452) = *v457;
                      v83 = __CFADD__(__PAIR64__(v458, v454), __PAIR64__((unsigned int)v457, v459));
                      v461 = v454 + v459;
                      v460 = (_BYTE *)((__PAIR64__(v458, v454) + __PAIR64__((unsigned int)v457, v459)) >> 32);
                      BYTE1(v460) = startsy_variable_12 + v459;
                      BYTE1(v452) = *v460;
                      v462 = v454 + v83 + v454 + v459;
                      v464 = __CFADD__(v83, v461) | __CFADD__(v454, v83 + v461);
                      v83 = __CFADD__(v464, v460);
                      v463 = &v460[v464];
                      v83 |= __CFADD__(v458, v463);
                      v463 += v458;
                      BYTE1(v463) = v462;
                      v465 = _byteswap_ulong(v452);
                      BYTE1(v465) = *v463;
                      v467 = v83;
                      v83 = __CFADD__(v83, v462);
                      v466 = v467 + v462;
                      v83 |= __CFADD__(v454, v466);
                      v466 += v454;
                      v469 = v83;
                      v83 = __CFADD__(v83, v463);
                      v468 = &v463[v469];
                      v83 |= __CFADD__(v458, v468);
                      v468 += v458;
                      BYTE1(v468) = v466;
                      LOBYTE(v465) = *v468;
                      v471 = v83;
                      v83 = __CFADD__(v83, v466);
                      v470 = v471 + v466;
                      v83 |= __CFADD__(v454, v470);
                      v459 = v454 + v470;
                      v473 = v83;
                      v83 = __CFADD__(v83, v468);
                      v472 = &v468[v473];
                      v83 |= __CFADD__(v458, v472);
                      v457 = &v472[v458];
                      BYTE1(v457) = v459;
                      LOBYTE(v459) = v83 + v459;
                      *--v456 = v465;
                    }
                    if ((v455 & 2) != 0) {
                      HIBYTE(v474) = *v457;
                      v83 = __CFADD__(__PAIR64__(v458, v454), __PAIR64__((unsigned int)v457, v459));
                      v457 = (_BYTE *)((__PAIR64__(v458, v454) + __PAIR64__((unsigned int)v457, v459)) >> 32);
                      BYTE1(v457) = v454 + v459;
                      LOBYTE(v474) = *v457;
                      LOBYTE(v457) = v458
                        + (__CFADD__(v83, v454 + v459) | __CFADD__(v454, v83 + v454 + v459))
                        + (_BYTE)v457;
                      BYTE1(v457) = v454 + v83 + v454 + v459;
                      v456 = (_DWORD *)((char *)v456 - 2);
                      *(_WORD *)v456 = v474;
                    }
                    if ((v455 & 1) != 0)
                      *((_BYTE *)v456 - 1) = *v457;
                    __DS__ = v891;
                    v3 = v899;
                  }
                  v547 = *(v3 - 16);
                  v548 = *(v3 - 17);
                  v549 = *(v3 - 9);
                  v550 = *(v3 - 14);
                  v551 = *(v3 - 22);
                  *(v3 - 10) += *(v3 - 11);
                  v552 = *(v3 - 13);
                  v553 = v551 + v547;
                  v554 = *(v3 - 19);
                  *(v3 - 16) = v553;
                  v555 = v554 + v548;
                  v556 = *(v3 - 12);
                  v557 = *(v3 - 15) + 1;
                  *(v3 - 17) = v555;
                  *(v3 - 15) = v557;
                  v558 = v556 + v549;
                  v559 = *(v3 - 21);
                  *(v3 - 9) = v558;
                  v560 = *(v3 - 10);
                  v561 = v559 + v550;
                  v562 = *(v3 - 20);
                  *(v3 - 14) = v561;
                  v563 = *(v3 - 4);
                  *(v3 - 13) = v562 + v552;
                  LOWORD(v563) = v563 - 1;
                  *(v3 - 4) = v563;
                  if (!(_WORD)v563)
                    break;
                LABEL_268:
                  v585 = *(v3 - 8);
                  v586 = *(v3 - 9);
                  LOWORD(v585) = v585 - 1;
                  *(v3 - 8) = v585;
                  if (!(_WORD)v585) {
                    while (1) {
                      v587 = *(v3 - 3);
                      if ((unsigned __int16)*(v3 - 5) == (_WORD)v587) {
                        *(v3 - 10) = v560;
                        *(v3 - 9) = v586;
                        goto LABEL_281;
                      }
                      *((_WORD *)v3 - 17) = *(_WORD *)(*(v3 - 18) + 8 * (__int16)v587);
                      v588 = startsx[(__int16)v587];
                      v589 = startsy[(__int16)v587];
                      *(v3 - 3) = v587 - 1;
                      *(v3 - 13) = v589;
                      *(v3 - 14) = v588;
                      if ((__int16)(v587 - 1) == -1)
                        *(v3 - 3) = *(v3 - 6) - 1;
                      v590 = *((__int16 *)v3 - 6);
                      v591 = *(v3 - 18);
                      v11 = v591 + 8 * v590;
                      LOWORD(v591) = *(_WORD *)(v11 + 4);
                      v592 = v591 - *(v3 - 15);
                      *(v3 - 8) = v592;
                      if ((__int16)v592 > 0)
                        break;
                      if ((v592 & 0x8000u) != 0)
                        return v11;
                    }
                    LOWORD(v11) = *(_WORD *)v11;
                    v593 = v11 - *(int *)((char *)v3 - 34);
                    *((_WORD *)v3 - 24) = 0;
                    *((_WORD *)v3 - 23) = v593;
                    v594 = v590;
                    v595 = *(v3 - 12);
                    *((_WORD *)v3 - 18) = -1;
                    if (v595 <= 0) {
                      *((_WORD *)v3 - 23) = v593 - 1;
                      v603 = (__int16)v592 + 1;
                      v604 = *(v3 - 12) / v603;
                      v605 = *(v3 - 14);
                      *((_WORD *)v3 - 17) = *(int *)((char *)v3 - 34) + 1;
                      v606 = startsx[v594] - v605;
                      *(v3 - 12) = v604;
                      v607 = v606;
                      v608 = startsy[v594] - *(v3 - 13);
                      *(v3 - 21) = v607 / v603;
                      *(v3 - 20) = v608 / v603;
                    } else {
                      *((_WORD *)v3 - 23) = v593 + 1;
                      v596 = (__int16)v592 + 1;
                      v597 = *(v3 - 12) / v596;
                      v598 = *(v3 - 14);
                      *(v3 - 9) += v597;
                      v599 = startsx[v594] - v598;
                      *(v3 - 12) = v597;
                      *(v3 - 21) = v599 / v596;
                      v600 = v598 + v599 / v596;
                      v601 = (startsy[v594] - *(v3 - 13)) / v596;
                      v602 = *(v3 - 13);
                      *(v3 - 14) = v600;
                      *(v3 - 20) = v601;
                      *(v3 - 13) = v601 + v602;
                    }
                  }
                  v11 = *(v3 - 15);
                  if (v11 >= winh)
                    return v11;
                  if (*((__int16 *)v3 - 19) >= (unsigned int)winw) {
                    v11 = *((__int16 *)v3 - 19);
                    if (v11 < winw)
                      goto LABEL_299;
                    return v11;
                  }
                }
                while (1) {
                  v564 = *(v3 - 5);
                  if ((_WORD)v564 == *((_WORD *)v3 - 6))
                    break;
                  v565 = *(v3 - 5) + 1;
                  v566 = (_WORD *)(*(v3 - 18) + 8 * (__int16)v564);
                  *(v3 - 5) = v565;
                  v567 = *(v3 - 6);
                  *((_WORD *)v3 - 19) = *v566;
                  v568 = startsx[(__int16)v564];
                  v569 = startsy[(__int16)v564];
                  *(v3 - 16) = v568;
                  *(v3 - 17) = v569;
                  if ((_WORD)v565 == (_WORD)v567)
                    *(v3 - 5) = 0;
                  v570 = *((__int16 *)v3 - 10);
                  v11 = *(v3 - 18) + 8 * v570;
                  LOWORD(v568) = *(_WORD *)(v11 + 4);
                  v571 = v568 - *(v3 - 15);
                  *(v3 - 4) = v571;
                  if ((__int16)v571 > 0) {
                    v572 = *(_WORD *)v11 - *(int *)((char *)v3 - 38);
                    *((_WORD *)v3 - 22) = 0;
                    *((_WORD *)v3 - 21) = v572;
                    v573 = v570;
                    v574 = *(v3 - 11);
                    *((_WORD *)v3 - 20) = 0;
                    if (v574 >= 0) {
                      ++*((_WORD *)v3 - 21);
                      v583 = *((__int16 *)v3 - 8) + 1;
                      v584 = startsx[v573] - *(v3 - 16);
                      *(v3 - 11) /= v583;
                      *(v3 - 22) = v584 / v583;
                      *(v3 - 19) = (startsy[v573] - *(v3 - 17)) / v583;
                    } else {
                      --*((_WORD *)v3 - 21);
                      v575 = *((__int16 *)v3 - 8) + 1;
                      v576 = *(v3 - 11) / v575;
                      *(v3 - 10) += v576;
                      v577 = startsx[v573];
                      *((_WORD *)v3 - 19) = *(int *)((char *)v3 - 38) + 1;
                      v578 = *(v3 - 16);
                      *(v3 - 11) = v576;
                      v579 = (v577 - v578) / v575;
                      *(v3 - 16) = v578 + v579;
                      v580 = startsy[v573];
                      v581 = *(v3 - 17);
                      *(v3 - 22) = v579;
                      v582 = (v580 - v581) / v575;
                      *(v3 - 19) = v582;
                      *(v3 - 17) = v581 + v582;
                    }
                    goto LABEL_268;
                  }
                  if ((v571 & 0x8000u) != 0)
                    return v11;
                }
                *(v3 - 10) = v560;
              LABEL_281:
                v11 = *(v3 - 15);
                if (v11 < winh) {
                  if (*((__int16 *)v3 - 19) < (unsigned int)winw)
                    goto LABEL_285;
                  v11 = *((__int16 *)v3 - 19);
                  if (v11 < winw) {
                  LABEL_353:
                    v11 = *((__int16 *)v3 - 17);
                    if (v11 > (unsigned int)winw)
                      goto LABEL_356;
                    if (*((__int16 *)v3 - 17) <= 0)
                      return v11;
                    goto LABEL_219;
                  }
                }
              }
              return v11;
            }
          LABEL_299:
            v11 = *((__int16 *)v3 - 17);
            if (v11 <= (unsigned int)winw) {
              if (*((__int16 *)v3 - 17) > 0)
                goto LABEL_162;
              return v11;
            }
          }
          while (1) {
            v751 = *(v3 - 5);
            if ((_WORD)v751 == *((_WORD *)v3 - 6))
              break;
            v752 = *(v3 - 6);
            v753 = *(v3 - 5) + 1;
            v754 = *(_WORD *)(*(v3 - 18) + 8 * (__int16)v751);
            *(v3 - 5) = v753;
            *((_WORD *)v3 - 19) = v754;
            v755 = startsx[(__int16)v751];
            v756 = startsy[(__int16)v751];
            *(v3 - 16) = v755;
            *(v3 - 17) = v756;
            if ((_WORD)v753 == (_WORD)v752)
              *(v3 - 5) = 0;
            v757 = *((__int16 *)v3 - 10);
            v11 = *(v3 - 18) + 8 * v757;
            LOWORD(v755) = *(_WORD *)(v11 + 4);
            v758 = v755 - *(v3 - 15);
            *(v3 - 4) = v758;
            if ((__int16)v758 > 0) {
              LOWORD(v11) = *(_WORD *)v11;
              v759 = v11 - *(int *)((char *)v3 - 38);
              *((_WORD *)v3 - 22) = 0;
              *((_WORD *)v3 - 21) = v759;
              v760 = v757;
              v761 = *(v3 - 11);
              *((_WORD *)v3 - 20) = 0;
              if (v761 >= 0) {
                *((_WORD *)v3 - 21) = v759 + 1;
                v770 = *((__int16 *)v3 - 8) + 1;
                *(v3 - 11) /= v770;
                v771 = startsy[v760] - *(v3 - 17);
                *(v3 - 22) = (startsx[v760] - *(v3 - 16)) / v770;
                *(v3 - 19) = v771 / v770;
              } else {
                *((_WORD *)v3 - 21) = v759 - 1;
                v762 = *((__int16 *)v3 - 8) + 1;
                v763 = *(v3 - 11) / v762;
                v764 = *(v3 - 10);
                *(v3 - 11) = v763;
                v765 = v763 + v764;
                v766 = (startsx[v760] - *(v3 - 16)) / v762;
                *(v3 - 16) += v766;
                v767 = startsy[v760];
                v768 = *(v3 - 17);
                *(v3 - 22) = v766;
                v769 = (v767 - v768) / v762;
                *(v3 - 10) = v765;
                ++*((_WORD *)v3 - 19);
                *(v3 - 19) = v769;
                *(v3 - 17) = v768 + v769;
              }
              goto LABEL_336;
            }
            if ((v758 & 0x8000u) != 0)
              return v11;
          }
          *(v3 - 10) = v750;
        LABEL_349:
          v11 = *(v3 - 15);
          if (v11 >= winh)
            return v11;
          if (*((__int16 *)v3 - 19) >= (unsigned int)winw)
            goto LABEL_353;
          v11 = *((__int16 *)v3 - 19);
          if (v11 >= winw)
            return v11;
        LABEL_285:
          v11 = *((__int16 *)v3 - 17);
          if (v11 <= (unsigned int)winw) {
            if (*((__int16 *)v3 - 17) <= 0)
              return v11;
            goto LABEL_147;
          }
        LABEL_288:
          *((_WORD *)v3 - 14) = *(int *)((char *)v3 - 34) - *(int *)((char *)v3 - 38);
          v609 = *(v3 - 14);
          v610 = *(v3 - 13);
          v611 = *(v3 - 17);
          *(int *)((char *)&startsy_variable_8 + 2) = (*(v3 - 16) - v609) / *((__int16 *)v3 - 14);
          v612 = winw;
          *(int *)((char *)&startsy_variable_10 + 2) = (v611 - v610) / *((__int16 *)v3 - 14);
          v613 = *((__int16 *)v3 - 17) - winw;
          *(int *)((char *)&startsy_variable_4 + 2) = v609 + v613 * *(int *)((char *)&startsy_variable_8 + 2);
          v614 = *(int *)((char *)v3 - 38);
          *(int *)((char *)&startsy_variable_6 + 2) = v610 + *(int *)((char *)&startsy_variable_10 + 2) * v613;
          *((_WORD *)v3 - 14) = winw - v614;
          v11 = v612 * *(v3 - 15);
          *(v3 - 23) = v11 + scrptr1;
          if (*((__int16 *)v3 - 14) <= 7) {
            HIWORD(v621) = HIWORD(startsy_variable_4);
            HIWORD(v615) = HIWORD(startsy_variable_6);
            BYTE1(v621) = BYTE1(startsy_variable_8);
            HIWORD(v616) = HIWORD(startsy_variable_8);
            v620 = startsy_variable_10;
            LOWORD(v616) = startsy_variable_12;
            v617 = *((_WORD *)v3 - 14);
            LOWORD(v11) = *((_WORD *)v3 - 2);
            __DS__ = v11;
            v618 = (_DWORD *)*(v3 - 23);
            LOWORD(v615) = startsy_variable_6 - startsy_variable_10;
            v83 = __CFADD__(startsy_variable_10, v615);
            v619 = (_BYTE *)(startsy_variable_10 + v615);
            BYTE1(v619) = startsy_variable_8;
            BYTE1(v620) = 0;
            LOBYTE(v621) = v83 + startsy_variable_8;
            if ((v617 & 4) != 0) {
              LOBYTE(v11) = *MK_FP(v11, (_WORD)v619);
              v83 = __CFADD__(__PAIR64__(v620, v616), __PAIR64__((unsigned int)v619, v621));
              v623 = v616 + v621;
              v622 = (_BYTE *)((__PAIR64__(v620, v616) + __PAIR64__((unsigned int)v619, v621)) >> 32);
              BYTE1(v622) = startsy_variable_12 + v621;
              BYTE1(v11) = *v622;
              v624 = v616 + v83 + v616 + v621;
              v626 = __CFADD__(v83, v623) | __CFADD__(v616, v83 + v623);
              v83 = __CFADD__(v626, v622);
              v625 = &v622[v626];
              v83 |= __CFADD__(v620, v625);
              v625 += v620;
              BYTE1(v625) = v624;
              v11 = _byteswap_ulong(v11);
              BYTE1(v11) = *v625;
              v628 = v83;
              v83 = __CFADD__(v83, v624);
              v627 = v628 + v624;
              v83 |= __CFADD__(v616, v627);
              v627 += v616;
              v630 = v83;
              v83 = __CFADD__(v83, v625);
              v629 = &v625[v630];
              v83 |= __CFADD__(v620, v629);
              v629 += v620;
              BYTE1(v629) = v627;
              LOBYTE(v11) = *v629;
              v632 = v83;
              v83 = __CFADD__(v83, v627);
              v631 = v632 + v627;
              v83 |= __CFADD__(v616, v631);
              v621 = v616 + v631;
              v634 = v83;
              v83 = __CFADD__(v83, v629);
              v633 = &v629[v634];
              v83 |= __CFADD__(v620, v633);
              v619 = &v633[v620];
              BYTE1(v619) = v621;
              LOBYTE(v621) = v83 + v621;
              *--v618 = v11;
            }
            if ((v617 & 2) != 0) {
              BYTE1(v11) = *v619;
              v83 = __CFADD__(__PAIR64__(v620, v616), __PAIR64__((unsigned int)v619, v621));
              v619 = (_BYTE *)((__PAIR64__(v620, v616) + __PAIR64__((unsigned int)v619, v621)) >> 32);
              BYTE1(v619) = v616 + v621;
              LOBYTE(v11) = *v619;
              LOBYTE(v619) = v620 + (__CFADD__(v83, v616 + v621) | __CFADD__(v616, v83 + v616 + v621)) + (_BYTE)v619;
              BYTE1(v619) = v616 + v83 + v616 + v621;
              v618 = (_DWORD *)((char *)v618 - 2);
              *(_WORD *)v618 = v11;
            }
            if ((v617 & 1) != 0) {
              LOBYTE(v11) = *v619;
              *((_BYTE *)v618 - 1) = *v619;
            }
            return v11;
          }
        LABEL_364:
          HIWORD(v824) = HIWORD(startsy_variable_4);
          HIWORD(v818) = HIWORD(startsy_variable_6);
          BYTE1(v824) = BYTE1(startsy_variable_8);
          HIWORD(v819) = HIWORD(startsy_variable_8);
          v823 = startsy_variable_10;
          LOWORD(v819) = startsy_variable_12;
          v820 = *((_WORD *)v3 - 14);
          LOWORD(v11) = *((_WORD *)v3 - 2);
          __DS__ = v11;
          v821 = (_WORD *)*(v3 - 23);
          LOWORD(v818) = startsy_variable_6 - startsy_variable_10;
          v83 = __CFADD__(startsy_variable_10, v818);
          v822 = (_BYTE *)(startsy_variable_10 + v818);
          BYTE1(v822) = startsy_variable_8;
          BYTE1(v823) = 0;
          LOBYTE(v824) = v83 + startsy_variable_8;
          if (((unsigned __int8)v821 & 1) != 0) {
            LOBYTE(v11) = *MK_FP(v11, (_WORD)v822);
            v83 = __CFADD__(__PAIR64__(v823, v819), __PAIR64__((unsigned int)v822, v824));
            v822 = (_BYTE *)((__PAIR64__(v823, v819) + __PAIR64__((unsigned int)v822, v824)) >> 32);
            v824 += v819;
            BYTE1(v822) = v824;
            LOBYTE(v824) = v83 + v824;
            v821 = (_WORD *)((char *)v821 - 1);
            *(_BYTE *)v821 = v11;
            --v820;
          }
          if (((unsigned __int8)v821 & 2) != 0) {
            BYTE1(v11) = *v822;
            v83 = __CFADD__(__PAIR64__(v823, v819), __PAIR64__((unsigned int)v822, v824));
            v826 = v819 + v824;
            v825 = (_BYTE *)((__PAIR64__(v823, v819) + __PAIR64__((unsigned int)v822, v824)) >> 32);
            BYTE1(v825) = v819 + v824;
            LOBYTE(v11) = *v825;
            v824 += v819 + v83 + v819;
            v828 = __CFADD__(v83, v826) | __CFADD__(v819, v83 + v826);
            v83 = __CFADD__(v828, v825);
            v827 = &v825[v828];
            v83 |= __CFADD__(v823, v827);
            v822 = &v827[v823];
            BYTE1(v822) = v824;
            LOBYTE(v824) = v83 + v824;
            *--v821 = v11;
            v820 -= 2;
          }
          if (((unsigned __int8)v821 & 4) != 0) {
            LOBYTE(v11) = *v822;
            v83 = __CFADD__(__PAIR64__(v823, v819), __PAIR64__((unsigned int)v822, v824));
            v830 = v819 + v824;
            v829 = (_BYTE *)((__PAIR64__(v823, v819) + __PAIR64__((unsigned int)v822, v824)) >> 32);
            BYTE1(v829) = v819 + v824;
            BYTE1(v11) = *v829;
            v831 = v819 + v83 + v819 + v824;
            v833 = __CFADD__(v83, v830) | __CFADD__(v819, v83 + v830);
            v83 = __CFADD__(v833, v829);
            v832 = &v829[v833];
            v83 |= __CFADD__(v823, v832);
            v832 += v823;
            BYTE1(v832) = v831;
            v11 = _byteswap_ulong(v11);
            BYTE1(v11) = *v832;
            v835 = v83;
            v83 = __CFADD__(v83, v831);
            v834 = v835 + v831;
            v83 |= __CFADD__(v819, v834);
            v834 += v819;
            v837 = v83;
            v83 = __CFADD__(v83, v832);
            v836 = &v832[v837];
            v83 |= __CFADD__(v823, v836);
            v836 += v823;
            BYTE1(v836) = v834;
            LOBYTE(v11) = *v836;
            v839 = v83;
            v83 = __CFADD__(v83, v834);
            v838 = v839 + v834;
            v83 |= __CFADD__(v819, v838);
            v824 = v819 + v838;
            v841 = v83;
            v83 = __CFADD__(v83, v836);
            v840 = &v836[v841];
            v83 |= __CFADD__(v823, v840);
            v822 = &v840[v823];
            BYTE1(v822) = v824;
            LOBYTE(v824) = v83 + v824;
            v821 -= 2;
            *(_DWORD *)v821 = v11;
            v820 -= 4;
          }
          v83 = v820 < 8u;
          for (n = v820 - 8; !v83; n -= 8) {
            LOBYTE(v11) = *v822;
            v83 = __CFADD__(__PAIR64__(v823, v819), __PAIR64__((unsigned int)v822, v824));
            v844 = v819 + v824;
            v843 = (_BYTE *)((__PAIR64__(v823, v819) + __PAIR64__((unsigned int)v822, v824)) >> 32);
            BYTE1(v843) = v819 + v824;
            BYTE1(v11) = *v843;
            v845 = v819 + v83 + v819 + v824;
            v847 = __CFADD__(v83, v844) | __CFADD__(v819, v83 + v844);
            v83 = __CFADD__(v847, v843);
            v846 = &v843[v847];
            v83 |= __CFADD__(v823, v846);
            v846 += v823;
            BYTE1(v846) = v845;
            v848 = _byteswap_ulong(v11);
            BYTE1(v848) = *v846;
            v850 = v83;
            v83 = __CFADD__(v83, v845);
            v849 = v850 + v845;
            v83 |= __CFADD__(v819, v849);
            v849 += v819;
            v852 = v83;
            v83 = __CFADD__(v83, v846);
            v851 = &v846[v852];
            v83 |= __CFADD__(v823, v851);
            v851 += v823;
            BYTE1(v851) = v849;
            LOBYTE(v848) = *v851;
            v854 = v83;
            v83 = __CFADD__(v83, v849);
            v853 = v854 + v849;
            v83 |= __CFADD__(v819, v853);
            v853 += v819;
            v856 = v83;
            v83 = __CFADD__(v83, v851);
            v855 = &v851[v856];
            v83 |= __CFADD__(v823, v855);
            v855 += v823;
            BYTE1(v855) = v853;
            *((_DWORD *)v821 - 1) = v848;
            LOBYTE(v848) = *v855;
            v858 = v83;
            v83 = __CFADD__(v83, v853);
            v857 = v858 + v853;
            v83 |= __CFADD__(v819, v857);
            v857 += v819;
            v860 = v83;
            v83 = __CFADD__(v83, v855);
            v859 = &v855[v860];
            v83 |= __CFADD__(v823, v859);
            v859 += v823;
            BYTE1(v859) = v857;
            BYTE1(v848) = *v859;
            v862 = v83;
            v83 = __CFADD__(v83, v857);
            v861 = v862 + v857;
            v83 |= __CFADD__(v819, v861);
            v861 += v819;
            v864 = v83;
            v83 = __CFADD__(v83, v859);
            v863 = &v859[v864];
            v83 |= __CFADD__(v823, v863);
            v863 += v823;
            BYTE1(v863) = v861;
            v11 = _byteswap_ulong(v848);
            BYTE1(v11) = *v863;
            v866 = v83;
            v83 = __CFADD__(v83, v861);
            v865 = v866 + v861;
            v83 |= __CFADD__(v819, v865);
            v865 += v819;
            v868 = v83;
            v83 = __CFADD__(v83, v863);
            v867 = &v863[v868];
            v83 |= __CFADD__(v823, v867);
            v867 += v823;
            BYTE1(v867) = v865;
            LOBYTE(v11) = *v867;
            v870 = v83;
            v83 = __CFADD__(v83, v865);
            v869 = v870 + v865;
            v83 |= __CFADD__(v819, v869);
            v824 = v819 + v869;
            v872 = v83;
            v83 = __CFADD__(v83, v867);
            v871 = &v867[v872];
            v83 |= __CFADD__(v823, v871);
            v822 = &v871[v823];
            BYTE1(v822) = v824;
            LOBYTE(v824) = v83 + v824;
            v821 -= 4;
            *(_DWORD *)v821 = v11;
            v83 = n < 8u;
          }
          if ((n & 4) != 0) {
            LOBYTE(v11) = *v822;
            v83 = __CFADD__(__PAIR64__(v823, v819), __PAIR64__((unsigned int)v822, v824));
            v874 = v819 + v824;
            v873 = (_BYTE *)((__PAIR64__(v823, v819) + __PAIR64__((unsigned int)v822, v824)) >> 32);
            BYTE1(v873) = v819 + v824;
            BYTE1(v11) = *v873;
            v875 = v819 + v83 + v819 + v824;
            v877 = __CFADD__(v83, v874) | __CFADD__(v819, v83 + v874);
            v83 = __CFADD__(v877, v873);
            v876 = &v873[v877];
            v83 |= __CFADD__(v823, v876);
            v876 += v823;
            BYTE1(v876) = v875;
            v11 = _byteswap_ulong(v11);
            BYTE1(v11) = *v876;
            v879 = v83;
            v83 = __CFADD__(v83, v875);
            v878 = v879 + v875;
            v83 |= __CFADD__(v819, v878);
            v878 += v819;
            v881 = v83;
            v83 = __CFADD__(v83, v876);
            v880 = &v876[v881];
            v83 |= __CFADD__(v823, v880);
            v880 += v823;
            BYTE1(v880) = v878;
            LOBYTE(v11) = *v880;
            v883 = v83;
            v83 = __CFADD__(v83, v878);
            v882 = v883 + v878;
            v83 |= __CFADD__(v819, v882);
            v824 = v819 + v882;
            v885 = v83;
            v83 = __CFADD__(v83, v880);
            v884 = &v880[v885];
            v83 |= __CFADD__(v823, v884);
            v822 = &v884[v823];
            BYTE1(v822) = v824;
            LOBYTE(v824) = v83 + v824;
            v821 -= 2;
            *(_DWORD *)v821 = v11;
          }
          if ((n & 2) != 0) {
            BYTE1(v11) = *v822;
            v83 = __CFADD__(__PAIR64__(v823, v819), __PAIR64__((unsigned int)v822, v824));
            v822 = (_BYTE *)((__PAIR64__(v823, v819) + __PAIR64__((unsigned int)v822, v824)) >> 32);
            BYTE1(v822) = v819 + v824;
            LOBYTE(v11) = *v822;
            LOBYTE(v822) = v823 + (__CFADD__(v83, v819 + v824) | __CFADD__(v819, v83 + v819 + v824)) + (_BYTE)v822;
            BYTE1(v822) = v819 + v83 + v819 + v824;
            *--v821 = v11;
          }
          if ((n & 1) != 0) {
            LOBYTE(v11) = *v822;
            *((_BYTE *)v821 - 1) = *v822;
          }
        }
      }
    }
  }
  return v11;*/
}

//-------------------------------------------------------------------------------------------------

int polyt(int result, int a2, int a3)
{
  return 0; /*
  __int16 *v3; // ebp
  int v4; // edx
  int v5; // ecx
  int i; // esi
  int *v7; // ebx
  int v8; // ebx
  int v9; // eax
  int v10; // ebx
  int v11; // edx
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // ecx
  int v16; // edx
  int v17; // edx
  __int64 v18; // rtt
  int v19; // edx
  int v20; // edx
  int v21; // ecx
  int v22; // eax
  int v23; // eax
  _WORD *v24; // edx
  int v25; // edx
  int v26; // eax
  _WORD *v27; // edx
  int v28; // edx
  int v29; // ebx
  int v30; // edx
  _WORD *v31; // eax
  __int16 v32; // ax
  int v33; // edx
  int v34; // edi
  int v35; // edx
  int v36; // eax
  int v37; // edx
  _WORD *v38; // eax
  __int16 v39; // ax
  int v40; // edx
  __int64 v41; // rtt
  int v42; // edx
  int v43; // ebx
  int v44; // esi
  _BYTE *v45; // edi
  int v46; // esi
  int v47; // eax
  int v48; // ebx
  int v49; // ecx
  __int16 *v50; // edx
  int v51; // ebp
  int v52; // ecx
  int v53; // esi
  int v54; // edi
  int v55; // edx
  int v56; // eax
  int v57; // ebx
  int v58; // ecx
  int v59; // eax
  int v60; // esi
  int v61; // eax
  int v62; // ecx
  int v63; // edi
  int v64; // eax
  int v65; // edx
  int v66; // eax
  int v67; // edx
  int v68; // edi
  int v69; // esi
  int v70; // edx
  int v71; // eax
  int v72; // ecx
  _WORD *v73; // eax
  int v74; // edx
  int v75; // ebx
  int v76; // eax
  int v77; // edx
  int v78; // ecx
  int v79; // esi
  int v80; // edx
  int v81; // eax
  int v82; // ebx
  int v83; // esi
  int v84; // edx
  int v85; // eax
  int v86; // ecx
  _WORD *v87; // eax
  int v88; // edx
  int v89; // ebx
  int v90; // eax
  int v91; // edi
  int v92; // edx
  int v93; // edx
  int v94; // esi
  int v95; // ecx
  int v96; // eax
  int v97; // ecx
  int v98; // ebx
  int v99; // esi
  _BYTE *v100; // edi
  int v101; // esi
  int v102; // eax
  int v103; // ebx
  int v104; // ecx
  __int16 *v105; // edx
  int v106; // ebp
  int v107; // ecx
  int v108; // esi
  int v109; // edi
  int v110; // edx
  int v111; // eax
  int v112; // ebx
  int v113; // ecx
  int v114; // eax
  int v115; // ecx
  int v116; // esi
  int v117; // eax
  int v118; // edi
  int v119; // edx
  int v120; // eax
  int v121; // ebx
  int v122; // edi
  int v123; // edx
  int v124; // edx
  int v125; // ecx
  _WORD *v126; // eax
  int v127; // edx
  __int16 v128; // ax
  int v129; // eax
  int v130; // ebx
  int v131; // eax
  int v132; // edx
  int v133; // ecx
  int v134; // esi
  int v135; // edx
  int v136; // eax
  int v137; // edi
  int v138; // edx
  int v139; // eax
  int v140; // ebx
  int v141; // edx
  int v142; // eax
  int v143; // ecx
  _WORD *v144; // eax
  int v145; // edx
  __int16 v146; // ax
  int v147; // eax
  int v148; // ebx
  int v149; // edi
  int v150; // edx
  int v151; // edx
  int v152; // esi
  int v153; // ecx
  int v154; // eax
  int v155; // ebx
  int v156; // edi
  int v157; // esi
  _BYTE *v158; // edi
  int v159; // esi
  int v160; // eax
  int v161; // ebx
  int v162; // ecx
  __int16 *v163; // edx
  int v164; // ebp
  int v165; // edx
  int v166; // ebx
  int v167; // ecx
  int v168; // esi
  int v169; // eax
  int v170; // edi
  int v171; // edx
  int v172; // eax
  int v173; // ebx
  int v174; // eax
  int v175; // ecx
  int v176; // ebx
  int v177; // esi
  int v178; // eax
  int v179; // edi
  int v180; // eax
  int v181; // edi
  int v182; // edx
  int v183; // edx
  int v184; // ecx
  _WORD *v185; // eax
  int v186; // edx
  __int16 v187; // ax
  int v188; // eax
  int v189; // ebx
  int v190; // edi
  int v191; // edx
  int v192; // edx
  int v193; // esi
  int v194; // ecx
  int v195; // eax
  int v196; // edi
  int v197; // edx
  int v198; // eax
  int v199; // ebx
  int v200; // edx
  int v201; // eax
  int v202; // ecx
  int v203; // edx
  _WORD *v204; // eax
  int v205; // edx
  __int16 v206; // ax
  int v207; // eax
  int v208; // ebx
  int v209; // esi
  int v210; // edx
  __int64 v211; // rtt
  int v212; // edi
  int v213; // edx
  int v214; // eax
  int v215; // edx
  int v216; // ebx
  int v217; // eax
  int v218; // ebx
  int v219; // esi
  _BYTE *v220; // edi
  int v221; // esi
  int v222; // eax
  int v223; // ebx
  int v224; // ecx
  __int16 *v225; // edx
  int v226; // ebp
  int v227; // ebx
  int v228; // ecx
  int v229; // esi
  int v230; // edi
  int v231; // eax
  int v232; // edx
  int v233; // ebx
  int v234; // eax
  int v235; // ebx
  int v236; // ecx
  int v237; // eax
  int v238; // esi
  int v239; // edi
  int v240; // eax
  int v241; // edx
  int v242; // edi
  int v243; // esi
  __int16 v244; // dx
  int v245; // edx
  int v246; // eax
  int v247; // ecx
  _WORD *v248; // eax
  int v249; // edx
  int v250; // ebx
  int v251; // eax
  int v252; // edi
  int v253; // edx
  int v254; // edx
  int v255; // esi
  int v256; // ecx
  int v257; // eax
  int v258; // ebx
  int v259; // esi
  int v260; // edx
  int v261; // eax
  int v262; // ecx
  int v263; // edx
  _WORD *v264; // eax
  int v265; // edx
  int v266; // ebx
  int v267; // eax
  int v268; // esi
  int v269; // edx
  __int64 v270; // rtt
  int v271; // edi
  int v272; // edx
  int v273; // eax
  int v274; // edx
  int v275; // ebx
  int v276; // eax
  __int16 *v277; // [esp-4h] [ebp-6Ch]
  __int16 *v278; // [esp-4h] [ebp-6Ch]
  __int16 *v279; // [esp-4h] [ebp-6Ch]
  __int16 *v280; // [esp-4h] [ebp-6Ch]
  int v281; // [esp+8h] [ebp-60h]
  int v282; // [esp+14h] [ebp-54h]
  int v283; // [esp+18h] [ebp-50h]
  int v284; // [esp+1Ch] [ebp-4Ch]
  int v285; // [esp+20h] [ebp-48h]
  int v286; // [esp+24h] [ebp-44h]
  int v287; // [esp+28h] [ebp-40h]
  int v288; // [esp+2Ch] [ebp-3Ch]
  int v289; // [esp+30h] [ebp-38h]
  int v290; // [esp+34h] [ebp-34h]
  int v291; // [esp+38h] [ebp-30h]
  int v292; // [esp+3Ch] [ebp-2Ch]
  int v293; // [esp+40h] [ebp-28h]
  int v294; // [esp+44h] [ebp-24h]
  int v295; // [esp+48h] [ebp-20h]
  int v296; // [esp+4Ch] [ebp-1Ch]
  int v297; // [esp+50h] [ebp-18h]
  int v298; // [esp+54h] [ebp-14h]
  int v299; // [esp+58h] [ebp-10h]
  int v300; // [esp+5Ch] [ebp-Ch]
  int v301; // [esp+60h] [ebp-8h]
  int v302; // [esp+64h] [ebp-4h]
  _DWORD savedregs[4]; // [esp+68h] [ebp+0h] BYREF

  v3 = (__int16 *)savedregs;
  v289 = result;
  v300 = a2;
  v281 = a3;
  v299 = 0;
  v4 = *(_DWORD *)result;
  v283 = *(_DWORD *)result;
  v5 = *(_DWORD *)(result + 4);
  v282 = v5;
  for (i = 1; (__int16)i < (__int16)v300; ++i) {
    v7 = (int *)(8 * (__int16)i + v289);
    result = *v7;
    v8 = v7[1];
    if (result <= v283) {
      if (result < v4)
        v4 = result;
    } else {
      v283 = result;
    }
    if (v8 <= v282) {
      if (v8 < v5) {
        v5 = v8;
        v299 = i;
      }
    } else {
      v282 = v8;
    }
  }
  if (v283 < 0 || v282 < 0 || v4 >= winw || v5 >= winh)
    return result;
  v298 = v299;
  v9 = v289 + 8 * (__int16)v299;
  v10 = *(_DWORD *)(v9 + 4);
  v292 = v10;
  if (v10 >= 0) {
    HIWORD(v297) = *(_WORD *)v9;
    HIWORD(v296) = HIWORD(v297);
    LOWORD(v293) = 0;
    LOWORD(v297) = 0;
    v22 = startsx[(__int16)v299];
    LOWORD(v294) = 0;
    v290 = v22;
    v295 = v22;
    v23 = startsy[(__int16)v299];
    LOWORD(v296) = 0;
    v291 = v23;
    while (1) {
      v284 = v23;
      if ((_WORD)++v299 == (_WORD)v300)
        v299 = 0;
      v24 = (_WORD *)(v289 + 8 * (__int16)v299);
      LOWORD(v23) = v24[2] - v292;
      v301 = v23;
      if ((_WORD)v23)
        break;
      result = v299;
      if ((_WORD)v299 == (_WORD)v298)
        return result;
      HIWORD(v296) = *v24;
      v295 = startsx[(__int16)v299];
      v23 = startsy[(__int16)v299];
    }
    HIWORD(v294) = *v24 - HIWORD(v296);
    v25 = startsx[(__int16)v299] - v295;
    v294 /= (__int16)v301;
    v287 = v25 / (__int16)v301;
    v285 = (startsy[(__int16)v299] - v284) / (__int16)v301;
    if (v294 < 0) {
      v296 += v294;
      v295 += v287;
      v284 += v285;
    }
    while (1) {
      v26 = (__int16)--v298;
      if ((__int16)v298 == -1) {
        v26 = v300 - 1;
        v298 = v300 - 1;
      }
      v27 = (_WORD *)(v289 + 8 * (__int16)v298);
      LOWORD(v26) = v27[2] - v292;
      v302 = v26;
      if ((_WORD)v26)
        break;
      result = v299;
      if ((_WORD)v299 == (_WORD)v298)
        return result;
      HIWORD(v297) = *v27;
      v290 = startsx[(__int16)v298];
      v291 = startsy[(__int16)v298];
    }
    HIWORD(v293) = *v27 - HIWORD(v297);
    v293 /= (__int16)v302;
    v28 = startsy[(__int16)v298];
    v286 = (startsx[(__int16)v298] - v290) / (__int16)v302;
    v288 = (v28 - v291) / (__int16)v302;
    if (v293 > 0) {
      v297 += v293;
      v290 += v286;
      v291 += v288;
    }
  } else {
    result = v10;
    LOWORD(v297) = 0;
    LOWORD(v293) = 0;
    LOWORD(v296) = 0;
    LOWORD(v294) = 0;
    do {
      v11 = (__int16)v299;
      HIWORD(v296) = *(_WORD *)(v289 + 8 * (__int16)v299);
      v12 = startsx[(__int16)v299++];
      v295 = v12;
      v284 = startsy[v11];
      if ((_WORD)v299 == (_WORD)v300)
        v299 = 0;
      v292 = result;
      result = *(_DWORD *)(v289 + 8 * (__int16)v299 + 4);
    } while (result < 0);
    if (!result) {
      do {
        v13 = (__int16)v299;
        HIWORD(v296) = *(_WORD *)(v289 + 8 * (__int16)v299);
        v14 = startsx[(__int16)v299++];
        v295 = v14;
        v284 = startsy[v13];
        if ((_WORD)v299 == (_WORD)v300)
          v299 = 0;
        v292 = result;
        result = *(_DWORD *)(v289 + 8 * (__int16)v299 + 4);
      } while (!result);
      if (result < 0)
        return result;
    }
    v301 = result;
    HIWORD(v294) = *(_WORD *)(v289 + 8 * (__int16)v299) - HIWORD(v296);
    v282 = (__int16)result - v292;
    v294 /= v282;
    v296 += (v294 >> 1) - v294 * v292;
    v287 = (startsx[(__int16)v299] - v295) / v282;
    v285 = (startsy[(__int16)v299] - v284) / v282;
    v15 = v284 - v285 * v292;
    v295 -= v287 * v292;
    v284 = v15;
    if (v294 < 0) {
      v296 += v294;
      v295 += v287;
      v284 = v285 + v15;
    }
    do {
      HIWORD(v297) = *(_WORD *)(v289 + 8 * (__int16)v298);
      v16 = startsx[(__int16)v298];
      v291 = startsy[(__int16)v298--];
      v290 = v16;
      if ((__int16)v298 == -1)
        v298 = v300 - 1;
      v292 = v10;
      v10 = *(_DWORD *)(v289 + 8 * (__int16)v298 + 4);
    } while (v10 < 0);
    if (!v10) {
      do {
        HIWORD(v297) = *(_WORD *)(v289 + 8 * (__int16)v298);
        v290 = startsx[(__int16)v298];
        v291 = startsy[(__int16)v298--];
        if ((__int16)v298 == -1)
          v298 = v300 - 1;
        result = (__int16)v298;
        v292 = v10;
        v10 = *(_DWORD *)(v289 + 8 * (__int16)v298 + 4);
      } while (!v10);
      if (v10 < 0)
        return result;
    }
    HIWORD(v293) = *(_WORD *)(v289 + 8 * (__int16)v298) - HIWORD(v297);
    v302 = v10;
    v282 = (__int16)v10 - v292;
    v293 /= v282;
    v17 = startsx[(__int16)v298] - v290;
    v297 += (v293 >> 1) - v293 * v292;
    v18 = v17;
    v19 = startsy[(__int16)v298];
    v286 = v18 / v282;
    v288 = (v19 - v291) / v282;
    v20 = v290 - v286 * v292;
    v21 = v291 - v288 * v292;
    v290 = v20;
    v291 = v21;
    if (v293 > 0) {
      v291 = v21 + v288;
      v297 += v293;
      v290 = v286 + v20;
    }
    v292 = 0;
  }
  while (SHIWORD(v296) >= winw || v297 < 0 || v296 > v297) {
    v296 += v294;
    v295 += v287;
    v284 += v285;
    ++v292;
    HIWORD(v29) = HIWORD(v301);
    v297 += v293;
    v290 += v286;
    v291 += v288;
    LOWORD(v29) = v301 - 1;
    v301 = v29;
    if (!(_WORD)v29) {
      while (1) {
        result = v299;
        if ((_WORD)v299 == (_WORD)v298)
          return result;
        HIWORD(v296) = *(_WORD *)(v289 + 8 * (__int16)v299);
        v30 = startsx[(__int16)v299++];
        v295 = v30;
        HIWORD(v30) = HIWORD(v300);
        v284 = startsy[(__int16)result];
        if ((_WORD)v299 == (_WORD)v300)
          v299 = 0;
        v31 = (_WORD *)(v289 + 8 * (__int16)v299);
        LOWORD(v30) = v31[2];
        v301 = v30 - v292;
        if ((__int16)(v30 - v292) > 0) {
          v32 = *v31 - HIWORD(v296);
          LOWORD(v294) = 0;
          HIWORD(v294) = v32;
          LOWORD(v296) = 0;
          v33 = startsx[(__int16)v299] - v295;
          v294 /= (__int16)v301;
          v287 = v33 / (__int16)v301;
          v285 = (startsy[(__int16)v299] - v284) / (__int16)v301;
          if (v294 < 0) {
            v296 += v294;
            v295 += v287;
            v284 += v285;
          }
          break;
        }
      }
    }
    HIWORD(v34) = HIWORD(v302);
    LOWORD(v34) = v302 - 1;
    v302 = v34;
    if (!(_WORD)v34) {
      while (1) {
        result = v299;
        if ((_WORD)v299 == (_WORD)v298)
          return result;
        HIWORD(v297) = *(_WORD *)(v289 + 8 * (__int16)v298);
        v35 = startsx[(__int16)v298];
        v36 = startsy[(__int16)v298--];
        v291 = v36;
        v290 = v35;
        if ((__int16)v298 == -1)
          v298 = v300 - 1;
        HIWORD(v37) = HIWORD(v289);
        v38 = (_WORD *)(v289 + 8 * (__int16)v298);
        LOWORD(v37) = v38[2];
        v302 = v37 - v292;
        if ((__int16)(v37 - v292) > 0) {
          v39 = *v38 - HIWORD(v297);
          LOWORD(v293) = 0;
          HIWORD(v293) = v39;
          LOWORD(v297) = 0;
          v40 = startsx[(__int16)v298] - v290;
          v293 /= (__int16)v302;
          v41 = v40;
          v42 = startsy[(__int16)v298] - v291;
          v286 = v41 / (__int16)v302;
          v288 = v42 / (__int16)v302;
          if (v293 > 0) {
            v297 += v293;
            v290 += v286;
            v291 += v288;
          }
          break;
        }
      }
    }
    result = v292;
    if (v292 >= winh)
      return result;
  }
  while (*(v3 - 13) >= (unsigned int)winw) {
    result = *(v3 - 13);
    if (result >= winw)
      return result;
    while (1) {
      result = *(v3 - 11);
      if (result >= (unsigned int)winw)
        break;
    LABEL_106:
      *((_DWORD *)v3 - 23) = *(v3 - 11) + 1;
      v97 = *((_DWORD *)v3 - 8);
      v98 = (__int16)(*((_DWORD *)v3 - 23) - *(_DWORD *)(v3 - 13));
      *((_DWORD *)v3 - 20) = (*((_DWORD *)v3 - 13) - v97) / v98;
      v99 = *((_DWORD *)v3 - 19);
      *((_DWORD *)v3 - 21) = (*((_DWORD *)v3 - 12) - v99) / v98;
      *((_DWORD *)v3 - 22) = winw * *((_DWORD *)v3 - 11) + scrptr;
      v102 = *(v3 - 13);
      *((_DWORD *)v3 - 26) = v97 - v102 * *((_DWORD *)v3 - 20);
      *((_DWORD *)v3 - 25) = v99 - *((_DWORD *)v3 - 21) * v102;
      v278 = v3;
      v100 = (_BYTE *)*((_DWORD *)v3 - 22);
      v101 = *((_DWORD *)v3 - 24);
      HIWORD(v102) = 0;
      v103 = *((_DWORD *)v3 - 20);
      v104 = *((_DWORD *)v3 - 21);
      v105 = v3 - 52;
      v106 = *((_DWORD *)v3 - 23);
      do {
        BYTE1(v102) = *((_BYTE *)v105 + 6);
        LOBYTE(v102) = *((_BYTE *)v105 + 2);
        LOBYTE(v102) = *(_BYTE *)(v101 + v102);
        if ((_BYTE)v102)
          *v100 = v102;
        ++v100;
        *(_DWORD *)v105 += v103;
        *((_DWORD *)v105 + 1) += v104;
        --v106;
      } while (v106);
      v3 = v278;
      v107 = *((_DWORD *)v278 - 8);
      v108 = *((_DWORD *)v278 - 19);
      v109 = *((_DWORD *)v278 - 6);
      v110 = *((_DWORD *)v278 - 13);
      v111 = *((_DWORD *)v278 - 16);
      *((_DWORD *)v278 - 7) += *((_DWORD *)v278 - 9);
      v112 = *((_DWORD *)v278 - 12);
      v113 = v111 + v107;
      v114 = *((_DWORD *)v278 - 18);
      *((_DWORD *)v278 - 8) = v113;
      v115 = *((_DWORD *)v278 - 11);
      v116 = v114 + v108;
      v117 = *((_DWORD *)v278 - 10);
      *((_DWORD *)v278 - 19) = v116;
      v118 = v117 + v109;
      v119 = *((_DWORD *)v278 - 17) + v110;
      v120 = *((_DWORD *)v278 - 15);
      *((_DWORD *)v278 - 11) = v115 + 1;
      *((_DWORD *)v278 - 6) = v118;
      *((_DWORD *)v278 - 12) = v120 + v112;
      v121 = *((_DWORD *)v278 - 2);
      *((_DWORD *)v278 - 13) = v119;
      LOWORD(v121) = v121 - 1;
      *((_DWORD *)v278 - 2) = v121;
      if (!(_WORD)v121) {
        while (1) {
          result = *((_DWORD *)v278 - 4);
          if ((_WORD)result == *(v278 - 10))
            return result;
          v122 = *((_DWORD *)v278 - 4) + 1;
          *(v278 - 13) = *(_WORD *)(*((_DWORD *)v278 - 14) + 8 * (__int16)result);
          v123 = startsx[(__int16)result];
          *((_DWORD *)v278 - 4) = v122;
          *((_DWORD *)v278 - 8) = v123;
          v124 = *((_DWORD *)v278 - 3);
          *((_DWORD *)v278 - 19) = startsy[(__int16)result];
          if ((_WORD)v122 == (_WORD)v124)
            *((_DWORD *)v278 - 4) = 0;
          v125 = *(v278 - 8);
          v126 = (_WORD *)(*((_DWORD *)v278 - 14) + 8 * v125);
          LOWORD(v124) = v126[2];
          v127 = v124 - *((_DWORD *)v278 - 11);
          *((_DWORD *)v278 - 2) = v127;
          if ((__int16)v127 > 0) {
            v128 = *v126 - *(_DWORD *)(v278 - 13);
            *(v278 - 18) = 0;
            *(v278 - 17) = v128;
            v129 = *((_DWORD *)v278 - 9);
            *(v278 - 14) = 0;
            v130 = *(v278 - 4);
            *((_DWORD *)v278 - 9) = v129 / v130;
            v131 = (startsx[v125] - *((_DWORD *)v278 - 8)) / v130;
            v132 = startsy[v125];
            v133 = *((_DWORD *)v278 - 19);
            *((_DWORD *)v278 - 16) = v131;
            v134 = *((_DWORD *)v278 - 9);
            *((_DWORD *)v278 - 18) = (v132 - v133) / v130;
            if (v134 < 0) {
              v135 = *((_DWORD *)v278 - 16) + *((_DWORD *)v278 - 8);
              v136 = *((_DWORD *)v278 - 18);
              *((_DWORD *)v278 - 7) += v134;
              *((_DWORD *)v278 - 8) = v135;
              *((_DWORD *)v278 - 19) = v133 + v136;
            }
            break;
          }
        }
      }
      v137 = *((_DWORD *)v278 - 1);
      LOWORD(v137) = v137 - 1;
      *((_DWORD *)v278 - 1) = v137;
      if (!(_WORD)v137) {
        while (1) {
          result = *((_DWORD *)v278 - 4);
          v138 = *((_DWORD *)v278 - 5);
          if ((_WORD)result == (_WORD)v138)
            return result;
          v139 = (__int16)v138;
          v140 = *((_DWORD *)v278 - 5) - 1;
          *(v278 - 11) = *(_WORD *)(*((_DWORD *)v278 - 14) + 8 * (__int16)v138);
          v141 = startsx[(__int16)v138];
          v142 = startsy[v139];
          *((_DWORD *)v278 - 5) = v140;
          *((_DWORD *)v278 - 12) = v142;
          *((_DWORD *)v278 - 13) = v141;
          if ((__int16)v140 == -1)
            *((_DWORD *)v278 - 5) = *((_DWORD *)v278 - 3) - 1;
          v143 = *(v278 - 10);
          v144 = (_WORD *)(*((_DWORD *)v278 - 14) + 8 * v143);
          LOWORD(v141) = v144[2];
          v145 = v141 - *((_DWORD *)v278 - 11);
          *((_DWORD *)v278 - 1) = v145;
          if ((__int16)v145 > 0) {
            v146 = *v144 - *(_DWORD *)(v278 - 11);
            *(v278 - 20) = 0;
            *(v278 - 19) = v146;
            v147 = *((_DWORD *)v278 - 10);
            *(v278 - 12) = 0;
            v148 = *(v278 - 2);
            v149 = *((_DWORD *)v278 - 13);
            v150 = startsx[v143] - v149;
            *((_DWORD *)v278 - 10) = v147 / v148;
            *((_DWORD *)v278 - 17) = v150 / v148;
            v151 = *((_DWORD *)v278 - 10);
            *((_DWORD *)v278 - 15) = (startsy[v143] - *((_DWORD *)v278 - 12)) / v148;
            if (v151 > 0) {
              v152 = *((_DWORD *)v278 - 12);
              v153 = v149 + *((_DWORD *)v278 - 17);
              v154 = *((_DWORD *)v278 - 15);
              *((_DWORD *)v278 - 6) += v151;
              *((_DWORD *)v278 - 13) = v153;
              *((_DWORD *)v278 - 12) = v154 + v152;
            }
            break;
          }
        }
      }
      result = *((_DWORD *)v278 - 11);
      if (result >= winh)
        return result;
      if (*(v278 - 13) < (unsigned int)winw) {
        result = *(v278 - 13);
        if (result >= winw)
          return result;
        goto LABEL_76;
      }
    }
    if (*(v3 - 11) < 0)
      return result;
    while (1) {
      v218 = *(v3 - 13);
      *((_DWORD *)v3 - 23) = *(v3 - 11) - v218;
      *((_DWORD *)v3 - 20) = (*((_DWORD *)v3 - 13) - *((_DWORD *)v3 - 8)) / *((_DWORD *)v3 - 23);
      *((_DWORD *)v3 - 21) = (*((_DWORD *)v3 - 12) - *((_DWORD *)v3 - 19)) / *((_DWORD *)v3 - 23);
      v219 = winw;
      *((_DWORD *)v3 - 22) = winw * *((_DWORD *)v3 - 11) + scrptr;
      *((_DWORD *)v3 - 23) = v219;
      *((_DWORD *)v3 - 26) = *((_DWORD *)v3 - 8) - v218 * *((_DWORD *)v3 - 20);
      *((_DWORD *)v3 - 25) = *((_DWORD *)v3 - 19) - *((_DWORD *)v3 - 21) * v218;
      v280 = v3;
      v220 = (_BYTE *)*((_DWORD *)v3 - 22);
      v221 = *((_DWORD *)v3 - 24);
      HIWORD(v222) = 0;
      v223 = *((_DWORD *)v3 - 20);
      v224 = *((_DWORD *)v3 - 21);
      v225 = v3 - 52;
      v226 = *((_DWORD *)v3 - 23);
      do {
        BYTE1(v222) = *((_BYTE *)v225 + 6);
        LOBYTE(v222) = *((_BYTE *)v225 + 2);
        LOBYTE(v222) = *(_BYTE *)(v221 + v222);
        if ((_BYTE)v222)
          *v220 = v222;
        ++v220;
        *(_DWORD *)v225 += v223;
        *((_DWORD *)v225 + 1) += v224;
        --v226;
      } while (v226);
      v3 = v280;
      v227 = *((_DWORD *)v280 - 8);
      v228 = *((_DWORD *)v280 - 19);
      v229 = *((_DWORD *)v280 - 6);
      v230 = *((_DWORD *)v280 - 13);
      v231 = *((_DWORD *)v280 - 16);
      *((_DWORD *)v280 - 7) += *((_DWORD *)v280 - 9);
      v232 = *((_DWORD *)v280 - 12);
      v233 = v231 + v227;
      v234 = *((_DWORD *)v280 - 18);
      *((_DWORD *)v280 - 8) = v233;
      v235 = *((_DWORD *)v280 - 11);
      v236 = v234 + v228;
      v237 = *((_DWORD *)v280 - 10);
      *((_DWORD *)v280 - 19) = v236;
      v238 = v237 + v229;
      v239 = *((_DWORD *)v280 - 17) + v230;
      v240 = *((_DWORD *)v280 - 15);
      *((_DWORD *)v280 - 11) = v235 + 1;
      *((_DWORD *)v280 - 6) = v238;
      *((_DWORD *)v280 - 12) = v240 + v232;
      v241 = *((_DWORD *)v280 - 2);
      *((_DWORD *)v280 - 13) = v239;
      LOWORD(v241) = v241 - 1;
      *((_DWORD *)v280 - 2) = v241;
      if (!(_WORD)v241) {
        while (1) {
          result = *((_DWORD *)v280 - 4);
          if ((_WORD)result == *(v280 - 10))
            return result;
          v242 = *((_DWORD *)v280 - 3);
          v243 = *((_DWORD *)v280 - 4) + 1;
          v244 = *(_WORD *)(*((_DWORD *)v280 - 14) + 8 * (__int16)result);
          *((_DWORD *)v280 - 4) = v243;
          *(v280 - 13) = v244;
          v245 = startsx[(__int16)result];
          v246 = startsy[(__int16)result];
          *((_DWORD *)v280 - 8) = v245;
          *((_DWORD *)v280 - 19) = v246;
          if ((_WORD)v243 == (_WORD)v242)
            *((_DWORD *)v280 - 4) = 0;
          v247 = *(v280 - 8);
          v248 = (_WORD *)(*((_DWORD *)v280 - 14) + 8 * v247);
          LOWORD(v245) = v248[2];
          v249 = v245 - *((_DWORD *)v280 - 11);
          *((_DWORD *)v280 - 2) = v249;
          if ((__int16)v249 > 0) {
            *(v280 - 17) = *v248 - *(_DWORD *)(v280 - 13);
            *(v280 - 18) = 0;
            *(v280 - 14) = 0;
            v250 = (__int16)v249;
            v251 = *((_DWORD *)v280 - 9) / (__int16)v249;
            v252 = *((_DWORD *)v280 - 8);
            v253 = startsx[v247] - v252;
            *((_DWORD *)v280 - 9) = v251;
            *((_DWORD *)v280 - 16) = v253 / v250;
            v254 = *((_DWORD *)v280 - 9);
            *((_DWORD *)v280 - 18) = (startsy[v247] - *((_DWORD *)v280 - 19)) / v250;
            if (v254 < 0) {
              v255 = *((_DWORD *)v280 - 19);
              v256 = v252 + *((_DWORD *)v280 - 16);
              v257 = *((_DWORD *)v280 - 18);
              *((_DWORD *)v280 - 7) += v254;
              *((_DWORD *)v280 - 8) = v256;
              *((_DWORD *)v280 - 19) = v257 + v255;
            }
            break;
          }
        }
      }
      v258 = *((_DWORD *)v280 - 1);
      LOWORD(v258) = v258 - 1;
      *((_DWORD *)v280 - 1) = v258;
      if (!(_WORD)v258) {
        while (1) {
          result = *((_DWORD *)v280 - 4);
          v259 = *((_DWORD *)v280 - 5);
          if ((_WORD)result == (_WORD)v259)
            return result;
          *(v280 - 11) = *(_WORD *)(*((_DWORD *)v280 - 14) + 8 * (__int16)v259);
          v260 = startsx[(__int16)v259];
          v261 = startsy[(__int16)v259];
          *((_DWORD *)v280 - 5) = v259 - 1;
          *((_DWORD *)v280 - 12) = v261;
          *((_DWORD *)v280 - 13) = v260;
          if ((__int16)(v259 - 1) == -1)
            *((_DWORD *)v280 - 5) = *((_DWORD *)v280 - 3) - 1;
          v262 = *(v280 - 10);
          v263 = *((_DWORD *)v280 - 14);
          v264 = (_WORD *)(v263 + 8 * v262);
          LOWORD(v263) = v264[2];
          v265 = v263 - *((_DWORD *)v280 - 11);
          *((_DWORD *)v280 - 1) = v265;
          if ((__int16)v265 > 0) {
            *(v280 - 19) = *v264 - *(_DWORD *)(v280 - 11);
            *(v280 - 20) = 0;
            *(v280 - 12) = 0;
            v266 = (__int16)v265;
            v267 = *((_DWORD *)v280 - 10) / (__int16)v265;
            v268 = *((_DWORD *)v280 - 13);
            v269 = startsx[v262] - v268;
            *((_DWORD *)v280 - 10) = v267;
            v270 = v269;
            v271 = *((_DWORD *)v280 - 12);
            v272 = startsy[v262] - v271;
            *((_DWORD *)v280 - 17) = v270 / v266;
            *((_DWORD *)v280 - 15) = v272 / v266;
            v273 = *((_DWORD *)v280 - 10);
            if (v273 > 0) {
              v274 = v273 + *((_DWORD *)v280 - 6);
              v275 = v268 + *((_DWORD *)v280 - 17);
              v276 = *((_DWORD *)v280 - 15);
              *((_DWORD *)v280 - 6) = v274;
              *((_DWORD *)v280 - 13) = v275;
              *((_DWORD *)v280 - 12) = v271 + v276;
            }
            break;
          }
        }
      }
      result = *((_DWORD *)v280 - 11);
      if (result >= winh)
        return result;
      if (*(v280 - 13) < (unsigned int)winw)
        break;
    LABEL_155:
      result = *(v3 - 11);
      if (result < (unsigned int)winw) {
        if (*(v3 - 11) >= 0)
          goto LABEL_106;
        return result;
      }
    }
    result = *(v280 - 13);
    if (result >= winw)
      return result;
    while (1) {
      result = *(v3 - 11);
      if (result < (unsigned int)winw)
        break;
    LABEL_132:
      v155 = *(v3 - 13);
      *((_DWORD *)v3 - 23) = *(v3 - 11) - v155;
      *((_DWORD *)v3 - 20) = (*((_DWORD *)v3 - 13) - *((_DWORD *)v3 - 8)) / *((_DWORD *)v3 - 23);
      v156 = *((_DWORD *)v3 - 19);
      *((_DWORD *)v3 - 21) = (*((_DWORD *)v3 - 12) - v156) / *((_DWORD *)v3 - 23);
      v157 = winw;
      *((_DWORD *)v3 - 22) = winw * *((_DWORD *)v3 - 11) + v155 + scrptr;
      *((_DWORD *)v3 - 23) = v157 - v155;
      *((_DWORD *)v3 - 26) = *((_DWORD *)v3 - 8);
      *((_DWORD *)v3 - 25) = v156;
      v279 = v3;
      v158 = (_BYTE *)*((_DWORD *)v3 - 22);
      v159 = *((_DWORD *)v3 - 24);
      HIWORD(v160) = 0;
      v161 = *((_DWORD *)v3 - 20);
      v162 = *((_DWORD *)v3 - 21);
      v163 = v3 - 52;
      v164 = *((_DWORD *)v3 - 23);
      do {
        BYTE1(v160) = *((_BYTE *)v163 + 6);
        LOBYTE(v160) = *((_BYTE *)v163 + 2);
        LOBYTE(v160) = *(_BYTE *)(v159 + v160);
        if ((_BYTE)v160)
          *v158 = v160;
        ++v158;
        *(_DWORD *)v163 += v161;
        *((_DWORD *)v163 + 1) += v162;
        --v164;
      } while (v164);
      v3 = v279;
      v165 = *((_DWORD *)v279 - 8);
      v166 = *((_DWORD *)v279 - 19);
      v167 = *((_DWORD *)v279 - 6);
      v168 = *((_DWORD *)v279 - 13);
      v169 = *((_DWORD *)v279 - 16);
      *((_DWORD *)v279 - 7) += *((_DWORD *)v279 - 9);
      v170 = *((_DWORD *)v279 - 12);
      v171 = v169 + v165;
      v172 = *((_DWORD *)v279 - 18);
      *((_DWORD *)v279 - 8) = v171;
      v173 = v172 + v166;
      v174 = *((_DWORD *)v279 - 10);
      *((_DWORD *)v279 - 19) = v173;
      v175 = v174 + v167;
      v176 = *((_DWORD *)v279 - 2);
      v177 = *((_DWORD *)v279 - 17) + v168;
      v178 = *((_DWORD *)v279 - 15);
      *((_DWORD *)v279 - 6) = v175;
      v179 = v178 + v170;
      v180 = *((_DWORD *)v279 - 11);
      *((_DWORD *)v279 - 13) = v177;
      *((_DWORD *)v279 - 12) = v179;
      *((_DWORD *)v279 - 11) = v180 + 1;
      LOWORD(v176) = v176 - 1;
      *((_DWORD *)v279 - 2) = v176;
      if (!(_WORD)v176) {
        while (1) {
          result = *((_DWORD *)v279 - 4);
          if ((_WORD)result == *(v279 - 10))
            return result;
          v181 = *((_DWORD *)v279 - 4) + 1;
          *(v279 - 13) = *(_WORD *)(*((_DWORD *)v279 - 14) + 8 * (__int16)result);
          v182 = startsx[(__int16)result];
          *((_DWORD *)v279 - 4) = v181;
          *((_DWORD *)v279 - 8) = v182;
          v183 = *((_DWORD *)v279 - 3);
          *((_DWORD *)v279 - 19) = startsy[(__int16)result];
          if ((_WORD)v181 == (_WORD)v183)
            *((_DWORD *)v279 - 4) = 0;
          v184 = *(v279 - 8);
          v185 = (_WORD *)(*((_DWORD *)v279 - 14) + 8 * v184);
          LOWORD(v183) = v185[2];
          v186 = v183 - *((_DWORD *)v279 - 11);
          *((_DWORD *)v279 - 2) = v186;
          if ((__int16)v186 > 0) {
            v187 = *v185 - *(_DWORD *)(v279 - 13);
            *(v279 - 18) = 0;
            *(v279 - 17) = v187;
            v188 = *((_DWORD *)v279 - 9);
            *(v279 - 14) = 0;
            v189 = *(v279 - 4);
            v190 = *((_DWORD *)v279 - 8);
            v191 = startsx[v184] - v190;
            *((_DWORD *)v279 - 9) = v188 / v189;
            *((_DWORD *)v279 - 16) = v191 / v189;
            v192 = *((_DWORD *)v279 - 9);
            *((_DWORD *)v279 - 18) = (startsy[v184] - *((_DWORD *)v279 - 19)) / v189;
            if (v192 < 0) {
              v193 = *((_DWORD *)v279 - 19);
              v194 = v190 + *((_DWORD *)v279 - 16);
              v195 = *((_DWORD *)v279 - 18);
              *((_DWORD *)v279 - 7) += v192;
              *((_DWORD *)v279 - 8) = v194;
              *((_DWORD *)v279 - 19) = v195 + v193;
            }
            break;
          }
        }
      }
      v196 = *((_DWORD *)v279 - 1);
      LOWORD(v196) = v196 - 1;
      *((_DWORD *)v279 - 1) = v196;
      if (!(_WORD)v196) {
        while (1) {
          result = *((_DWORD *)v279 - 4);
          v197 = *((_DWORD *)v279 - 5);
          if ((_WORD)result == (_WORD)v197)
            return result;
          v198 = (__int16)v197;
          v199 = *((_DWORD *)v279 - 5) - 1;
          *(v279 - 11) = *(_WORD *)(*((_DWORD *)v279 - 14) + 8 * (__int16)v197);
          v200 = startsx[(__int16)v197];
          v201 = startsy[v198];
          *((_DWORD *)v279 - 5) = v199;
          *((_DWORD *)v279 - 12) = v201;
          *((_DWORD *)v279 - 13) = v200;
          if ((__int16)v199 == -1)
            *((_DWORD *)v279 - 5) = *((_DWORD *)v279 - 3) - 1;
          v202 = *(v279 - 10);
          v203 = *((_DWORD *)v279 - 14);
          v204 = (_WORD *)(v203 + 8 * v202);
          LOWORD(v203) = v204[2];
          v205 = v203 - *((_DWORD *)v279 - 11);
          *((_DWORD *)v279 - 1) = v205;
          if ((__int16)v205 > 0) {
            v206 = *v204 - *(_DWORD *)(v279 - 11);
            *(v279 - 20) = 0;
            *(v279 - 19) = v206;
            v207 = *((_DWORD *)v279 - 10);
            *(v279 - 12) = 0;
            v208 = *(v279 - 2);
            v209 = *((_DWORD *)v279 - 13);
            v210 = startsx[v202] - v209;
            *((_DWORD *)v279 - 10) = v207 / v208;
            v211 = v210;
            v212 = *((_DWORD *)v279 - 12);
            v213 = startsy[v202] - v212;
            *((_DWORD *)v279 - 17) = v211 / v208;
            *((_DWORD *)v279 - 15) = v213 / v208;
            v214 = *((_DWORD *)v279 - 10);
            if (v214 > 0) {
              v215 = v214 + *((_DWORD *)v279 - 6);
              v216 = v209 + *((_DWORD *)v279 - 17);
              v217 = *((_DWORD *)v279 - 15);
              *((_DWORD *)v279 - 6) = v215;
              *((_DWORD *)v279 - 13) = v216;
              *((_DWORD *)v279 - 12) = v212 + v217;
            }
            break;
          }
        }
      }
      result = *((_DWORD *)v279 - 11);
      if (result >= winh)
        return result;
      if (*(v279 - 13) >= (unsigned int)winw) {
        result = *(v279 - 13);
        if (result < winw)
          goto LABEL_155;
        return result;
      }
    }
    if (*(v3 - 11) < 0)
      return result;
  LABEL_79:
    v43 = *(v3 - 13);
    result = *(v3 - 11) - v43 + 1;
    *((_DWORD *)v3 - 23) = result;
    if (*((int *)v3 - 23) <= 0)
      return result;
    *((_DWORD *)v3 - 20) = (*((_DWORD *)v3 - 13) - *((_DWORD *)v3 - 8)) / *((_DWORD *)v3 - 23);
    v44 = *((_DWORD *)v3 - 19);
    *((_DWORD *)v3 - 21) = (*((_DWORD *)v3 - 12) - v44) / *((_DWORD *)v3 - 23);
    *((_DWORD *)v3 - 22) = winw * *((_DWORD *)v3 - 11) + scrptr + v43;
    *((_DWORD *)v3 - 26) = *((_DWORD *)v3 - 8);
    *((_DWORD *)v3 - 25) = v44;
    v277 = v3;
    v45 = (_BYTE *)*((_DWORD *)v3 - 22);
    v46 = *((_DWORD *)v3 - 24);
    HIWORD(v47) = 0;
    v48 = *((_DWORD *)v3 - 20);
    v49 = *((_DWORD *)v3 - 21);
    v50 = v3 - 52;
    v51 = *((_DWORD *)v3 - 23);
    do {
      BYTE1(v47) = *((_BYTE *)v50 + 6);
      LOBYTE(v47) = *((_BYTE *)v50 + 2);
      LOBYTE(v47) = *(_BYTE *)(v46 + v47);
      if ((_BYTE)v47)
        *v45 = v47;
      ++v45;
      *(_DWORD *)v50 += v48;
      *((_DWORD *)v50 + 1) += v49;
      --v51;
    } while (v51);
    v3 = v277;
    v52 = *((_DWORD *)v277 - 8);
    v53 = *((_DWORD *)v277 - 19);
    v54 = *((_DWORD *)v277 - 6);
    v55 = *((_DWORD *)v277 - 13);
    v56 = *((_DWORD *)v277 - 16);
    *((_DWORD *)v277 - 7) += *((_DWORD *)v277 - 9);
    v57 = *((_DWORD *)v277 - 12);
    v58 = v56 + v52;
    v59 = *((_DWORD *)v277 - 18);
    *((_DWORD *)v277 - 8) = v58;
    v60 = v59 + v53;
    v61 = *((_DWORD *)v277 - 10);
    v62 = *((_DWORD *)v277 - 11) + 1;
    *((_DWORD *)v277 - 19) = v60;
    *((_DWORD *)v277 - 11) = v62;
    v63 = v61 + v54;
    v64 = *((_DWORD *)v277 - 17);
    *((_DWORD *)v277 - 6) = v63;
    v65 = v64 + v55;
    v66 = *((_DWORD *)v277 - 15);
    *((_DWORD *)v277 - 13) = v65;
    v67 = *((_DWORD *)v277 - 2);
    *((_DWORD *)v277 - 12) = v66 + v57;
    LOWORD(v67) = v67 - 1;
    *((_DWORD *)v277 - 2) = v67;
    if (!(_WORD)v67) {
      while (1) {
        result = *((_DWORD *)v277 - 4);
        if ((_WORD)result == *(v277 - 10))
          return result;
        v68 = *((_DWORD *)v277 - 3);
        v69 = *((_DWORD *)v277 - 4) + 1;
        *(v277 - 13) = *(_WORD *)(*((_DWORD *)v277 - 14) + 8 * (__int16)result);
        *((_DWORD *)v277 - 4) = v69;
        v70 = startsx[(__int16)result];
        v71 = startsy[(__int16)result];
        *((_DWORD *)v277 - 8) = v70;
        *((_DWORD *)v277 - 19) = v71;
        if ((_WORD)v69 == (_WORD)v68)
          *((_DWORD *)v277 - 4) = 0;
        v72 = *(v277 - 8);
        v73 = (_WORD *)(*((_DWORD *)v277 - 14) + 8 * v72);
        LOWORD(v70) = v73[2];
        v74 = v70 - *((_DWORD *)v277 - 11);
        *((_DWORD *)v277 - 2) = v74;
        if ((__int16)v74 > 0) {
          *(v277 - 17) = *v73 - *(_DWORD *)(v277 - 13);
          *(v277 - 18) = 0;
          *(v277 - 14) = 0;
          v75 = (__int16)v74;
          *((int *)v277 - 9) /= (__int16)v74;
          v76 = (startsx[v72] - *((_DWORD *)v277 - 8)) / (__int16)v74;
          v77 = startsy[v72];
          v78 = *((_DWORD *)v277 - 19);
          *((_DWORD *)v277 - 16) = v76;
          v79 = *((_DWORD *)v277 - 9);
          *((_DWORD *)v277 - 18) = (v77 - v78) / v75;
          if (v79 < 0) {
            v80 = *((_DWORD *)v277 - 16) + *((_DWORD *)v277 - 8);
            v81 = *((_DWORD *)v277 - 18);
            *((_DWORD *)v277 - 7) += v79;
            *((_DWORD *)v277 - 8) = v80;
            *((_DWORD *)v277 - 19) = v78 + v81;
          }
          break;
        }
      }
    }
    v82 = *((_DWORD *)v277 - 1);
    LOWORD(v82) = v82 - 1;
    *((_DWORD *)v277 - 1) = v82;
    if (!(_WORD)v82) {
      while (1) {
        result = *((_DWORD *)v277 - 4);
        v83 = *((_DWORD *)v277 - 5);
        if ((_WORD)result == (_WORD)v83)
          return result;
        *(v277 - 11) = *(_WORD *)(*((_DWORD *)v277 - 14) + 8 * (__int16)v83);
        v84 = startsx[(__int16)v83];
        v85 = startsy[(__int16)v83];
        *((_DWORD *)v277 - 5) = v83 - 1;
        *((_DWORD *)v277 - 12) = v85;
        *((_DWORD *)v277 - 13) = v84;
        if ((__int16)(v83 - 1) == -1)
          *((_DWORD *)v277 - 5) = *((_DWORD *)v277 - 3) - 1;
        v86 = *(v277 - 10);
        v87 = (_WORD *)(*((_DWORD *)v277 - 14) + 8 * v86);
        LOWORD(v84) = v87[2];
        v88 = v84 - *((_DWORD *)v277 - 11);
        *((_DWORD *)v277 - 1) = v88;
        if ((__int16)v88 > 0) {
          *(v277 - 19) = *v87 - *(_DWORD *)(v277 - 11);
          *(v277 - 20) = 0;
          *(v277 - 12) = 0;
          v89 = (__int16)v88;
          v90 = *((_DWORD *)v277 - 10) / (__int16)v88;
          v91 = *((_DWORD *)v277 - 13);
          v92 = startsx[v86] - v91;
          *((_DWORD *)v277 - 10) = v90;
          *((_DWORD *)v277 - 17) = v92 / v89;
          v93 = *((_DWORD *)v277 - 10);
          *((_DWORD *)v277 - 15) = (startsy[v86] - *((_DWORD *)v277 - 12)) / v89;
          if (v93 > 0) {
            v94 = *((_DWORD *)v277 - 12);
            v95 = v91 + *((_DWORD *)v277 - 17);
            v96 = *((_DWORD *)v277 - 15);
            *((_DWORD *)v277 - 6) += v93;
            *((_DWORD *)v277 - 13) = v95;
            *((_DWORD *)v277 - 12) = v96 + v94;
          }
          break;
        }
      }
    }
    result = *((_DWORD *)v277 - 11);
    if (result >= winh)
      return result;
  }
LABEL_76:
  result = *(v3 - 11);
  if (result < (unsigned int)winw)
    goto LABEL_79;
  if (*(v3 - 11) >= 0)
    goto LABEL_132;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

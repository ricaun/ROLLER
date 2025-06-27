#include "svgacpy.h"
#include "3d.h"
#include <assert.h>
#include <string.h>
//-------------------------------------------------------------------------------------------------

int Vbytesperline;  //00178068
int winrange;       //0017806C

//-------------------------------------------------------------------------------------------------

int vesastart(int iX, int iY)
{
  //RMI.ecx = iX;
  //RMI.edx = iY;
  //RMI.es = vmode_inf >> 4;                      // Convert vmode_inf to segment address
  //RMI.ebx = 0;                                  // Subfunction: Set Display Start
  //RMI.eax = 0x4F07;                             // VESA Function: Set/Get Display Start
  //
  //// Make real-mode interrupt call
  //realmode(0x10u);
  //
  //// Check VESA function support
  //if (LOBYTE(RMI.eax) == 0x4F)
  //  return BYTE1(RMI.eax) != 0;                 // Check function success status
  //puts("VESA function not supported.");
  //return 2;

  return 0;
}

//-------------------------------------------------------------------------------------------------

int tryvesa(int iModeNumber)
{
  //RMI.ecx = iModeNumber;                        // VESA mode number to query
  //RMI.es = vmode_inf >> 4;                      // Convert vmode_inf to segment address
  //RMI.eax = 0x4F01;                             // VESA Function: Get Mode Information
  //RMI.edi = 0;                                  // Offset part of buffer pointer
  //
  //// Make real-mode interrupt call
  //realmode(0x10u);
  //
  //// Check VESA function support
  //if (LOBYTE(RMI.eax) == 0x4F)
  //  return BYTE1(RMI.eax) != 0;                 // Check function success status
  //
  //puts("VESA function not supported.");
  //return 2;

  return 0;
}

//-------------------------------------------------------------------------------------------------

void *VESASource(int iX, int iY, int iOffset)
{
  //// Get bytes per pixel from VESA mode info
  //unsigned char bpp_byte = *(unsigned char *)(vmode_inf[0] + 0x19);
  //int iBytesPerPixel = bpp_byte >> 3;  // Convert bits to bytes
  //
  //// Calculate buffer offset: y * pitch + x * bpp + additional offset
  //int iBufferOffset = iY * Vbytesperline + iX * iBytesPerPixel + iOffset;
  //
  //// Calculate window index and window-relative offset
  //int iWindowIndex = iBufferOffset / winrange;
  //int iWindowOffset = iBufferOffset % winrange;
  //
  //// Set new window if needed
  //if (iWindowIndex != vmode_inf[1]) {
  //  union REGS regs;
  //  regs.x.ax = 0x4F05;      // VESA function: Window Control
  //  regs.x.bx = 0x0001;      // Set window (subfunction 1 for source)
  //  regs.x.dx = window_index; // Window position
  //  int386(0x10, &regs);    // Call VESA BIOS
  //
  //  vmode_inf[1] = window_index; // Update current window index
  //}
  //
  //// Return pointer to source location
  //return (uint8 *)VesaSBase + iWindowOffset;

  return NULL;
}

//-------------------------------------------------------------------------------------------------

void *VESADest(int iX, int iY, int iOffset)
{
  //// Get bytes per pixel from VESA mode info
  //unsigned char bpp_byte = *(unsigned char *)(vmode_inf + 0x19);
  //int iBytesPerPixel = bpp_byte >> 3;  // Convert bits to bytes
  //
  //// Calculate buffer offset: y * pitch + x * bpp + additional offset
  //int iBufferOffset = iY * Vbytesperline + iX * iBytesPerPixel + iOffset;
  //
  //// Calculate window index and window-relative offset
  //int window_index = iBufferOffset / winrange;
  //int window_offset = iBufferOffset % winrange;
  //
  //// Set new window if needed
  //if (window_index != vmode_inf[2]) {
  //  union REGS regs;
  //  regs.x.ax = 0x4F05;      // VESA function: Window Control
  //  regs.x.bx = 0x0000;      // Set window (subfunction 0 for destination)
  //  regs.x.dx = window_index; // Window position
  //  int386(0x10, &regs);    // Call VESA BIOS
  //
  //  vmode_inf[2] = window_index; // Update current window index
  //}
  //
  //// Return pointer to destination location
  //return (char *)VesaDBase + window_offset;

  return NULL;
}

//-------------------------------------------------------------------------------------------------

int VESAmode(int *vesaModes, int iSvgaPossible)
{
  return 0x101;
  /*
  int v2; // ecx
  int v5; // ebx
  unsigned int v6; // ecx
  __int16 *i; // edx
  int v8; // eax
  int v9; // ecx
  unsigned __int16 v10; // ax
  union REGS regs; // [esp+0h] [ebp-3Ch] BYREF
  struct SREGS v12; // [esp+1Ch] [ebp-20h] BYREF
  int iSvgaPossible2; // [esp+30h] [ebp-Ch]
  int v14; // [esp+34h] [ebp-8h]

  v14 = v2;
  iSvgaPossible2 = iSvgaPossible;
  memset(&v12, 0, sizeof(v12));
  if (!vesa_inf) {
    regs.w.ax = 256;
    regs.w.bx = 16;
    int386x(49, &regs, &regs, &v12);
    vesa_inf = 16 * regs.w.ax;
    if (regs.x.cflag) {
      puts(aInternalErrorV);
      return -1;
    }
    RMI.edi = 0;
    RMI.es = (16 * regs.w.ax) >> 4;
    RMI.eax = 20224;
    realmode(0x10u);
    if (LOBYTE(RMI.eax) != 79)
      goto LABEL_5;
    if (BYTE1(RMI.eax)) {
    LABEL_7:
      puts(aVesaFunctionCa);
      return -1;
    }
    if (strncmp(vesa_inf, aVesa, 4))
      puts(aInternalErrorV_0);
  }
  if (vmode_inf
    || (regs.w.ax = 256, regs.w.bx = 16, int386x(49, &regs, &regs, &v12), vmode_inf = 16 * regs.w.ax, !regs.x.cflag)) {
    v5 = -1;
    if (*vesaModes != -1) {
      do {
        if (v5 != -1)
          break;
        v6 = (unsigned int)&unk_FFFF0 & (*(int *)(vesa_inf + 14) >> 12);
        for (i = (__int16 *)(v6 + (unsigned __int16)*(_DWORD *)(vesa_inf + 14)); ; ++i) {
          v8 = *i;
          if (v8 == -1)
            break;
          if (v8 == *vesaModes && !tryvesa(v8, (int)i, -1, v6)) {
            v5 = *i;
            break;
          }
        }
        v9 = vesaModes[1];
        ++vesaModes;
      } while (v9 != -1);
    }
    if (v5 <= -1) {
      puts(&aConoSupportedV[2]);
    } else {
      winrange = *(__int16 *)(vmode_inf + 4) << 10;
      Vbytesperline = *(__int16 *)(vmode_inf + 16);
      v10 = *(_WORD *)(vmode_inf + 10);
      VesaSBase = 16 * *(unsigned __int16 *)(vmode_inf + 8);
      RMI.ebx = v5;
      VesaDBase = 16 * v10;
      RMI.eax = 20226;
      realmode(0x10u);
      if (LOBYTE(RMI.eax) != 79) {
      LABEL_5:
        puts(aVesaFunctionNo);
        return -1;
      }
      if (BYTE1(RMI.eax))
        goto LABEL_7;
    }
    return v5;
  } else {
    puts(aInternalErrorV_1);
    return -1;
  }*/
}

//-------------------------------------------------------------------------------------------------

void svgacopy(uint8 *pSrc, int16 iX, int16 iY, int iWidth, int iHeight)
{
  //added by ROLLER, we should not be calling this function!
  assert(0);
  return;

  // Calculate initial video memory offset
  int iOffset = iX * Vbytesperline + iY;
  int iWindowIdx = iOffset / winrange;
  int iWindowOffset = iOffset % winrange;
  uint8 *pVideoPtr = (uint8 *)0xA0000 + iWindowOffset;

  // Set initial VESA window
  //union REGS regs;
  //regs.x.ax = 0x4F05;      // VESA function 05h: Window Control
  //regs.x.bx = 0x0000;      // BH=0 (Window A), BL=0 (Set window position)
  //regs.x.dx = iWindowIdx;  // Window position in granularity units
  //int386(0x10, &regs, &regs);

  while (iHeight > 0) {
    // Calculate rows that fit in current window
    int iBytesLeft = winrange - iWindowOffset;
    int iRowsInWindow = iBytesLeft / Vbytesperline;

    if (iRowsInWindow <= 0) iRowsInWindow = 1;  // At least 1 partial row
    if (iRowsInWindow > iHeight) iRowsInWindow = iHeight;

    // Copy full rows
    for (int row = 0; row < iRowsInWindow; row++) {
      // Copy entire width
      memcpy(pVideoPtr, pSrc, iWidth);
      pVideoPtr += Vbytesperline;
      pSrc += winw;
    }

    iHeight -= iRowsInWindow;
    if (iHeight <= 0) break;

    // Update position for next segment
    iOffset += iRowsInWindow * Vbytesperline;
    iWindowIdx = iOffset / winrange;
    iWindowOffset = iOffset % winrange;

    // Set new VESA window
    //union REGS regs;
    //regs.x.ax = 0x4F05;      // VESA function 05h: Window Control
    //regs.x.bx = 0x0000;      // BH=0 (Window A), BL=0 (Set window position)
    //regs.x.dx = iWindowIdx;  // Window position in granularity units
    //int386(0x10, &regs, &regs);
    pVideoPtr = (uint8 *)0xA0000 + iWindowOffset;

    // Handle partial row at window boundary
    int iSegment1 = Vbytesperline - iWindowOffset;
    if (iSegment1 > iWidth) iSegment1 = iWidth;

    memcpy(pVideoPtr, pSrc, iSegment1);

    // Handle remainder if row crosses window boundary
    if (iSegment1 < iWidth) {
      int iSegment2 = iWidth - iSegment1;
      //union REGS regs;
      //regs.x.ax = 0x4F05;      // VESA function 05h: Window Control
      //regs.x.bx = 0x0000;      // BH=0 (Window A), BL=0 (Set window position)
      //regs.x.dx = iWindowIdx + 1;  // Window position in granularity units
      //int386(0x10, &regs, &regs);
      memcpy((unsigned char *)0xA0000, pSrc + iSegment1, iSegment2);
      iWindowOffset = iSegment2;
      pVideoPtr = (unsigned char *)0xA0000 + iSegment2;
    }

    // Move to next row
    pSrc += winw;
    iHeight--;
  }

  // Reset to window 0 before returning
  //union REGS regs;
  //regs.x.ax = 0x4F05;      // VESA function 05h: Window Control
  //regs.x.bx = 0x0000;      // BH=0 (Window A), BL=0 (Set window position)
  //regs.x.dx = 0;           // Window position in granularity units
  //int386(0x10, &regs, &regs);
}

//-------------------------------------------------------------------------------------------------

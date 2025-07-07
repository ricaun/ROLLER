#ifndef _ROLLER_POLYF_H
#define _ROLLER_POLYF_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
#include "frontend.h"
//-------------------------------------------------------------------------------------------------

typedef struct
{
  uint32 uiSurfaceType;
  uint32 uiNumVerts;
  tPoint vertices[4];
} tPolyParams;

//-------------------------------------------------------------------------------------------------

void twpoly(tPoint *vertices, int16 nColor);
void POLYFLAT(uint8 *pScrBuf, tPolyParams *polyParams);
void poly(tPoint *vertices, int iVertexCount, int16 nColor);
void shadow_poly(tPoint *vertices, int iNumVertices, int iPaletteIndex);

//-------------------------------------------------------------------------------------------------
#endif

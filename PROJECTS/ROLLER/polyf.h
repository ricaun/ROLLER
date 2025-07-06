#ifndef _ROLLER_POLYF_H
#define _ROLLER_POLYF_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
#include "frontend.h"
//-------------------------------------------------------------------------------------------------

void twpoly(tPoint *vertices, int16 nColor);
int16 POLYFLAT(int a1, int *a2);
void poly(tPoint *vertices, int iVertexCount, int16 nColor);
void shadow_poly(tPoint *vertices, int iNumVertices, int iPaletteIndex);

//-------------------------------------------------------------------------------------------------
#endif

#ifndef _ROLLER_POLYF_H
#define _ROLLER_POLYF_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
#include "frontend.h"
//-------------------------------------------------------------------------------------------------

void twpoly(tPoint *vertices, int16 nColor);
int16 POLYFLAT(int a1, int *a2);
void poly(tPoint *vertices, int iVertexCount, int16 nColor);
int16 shadow_poly(int *a1, int a2, int a3);

//-------------------------------------------------------------------------------------------------
#endif

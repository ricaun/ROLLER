
//-------------------------------------------------------------------------------------------------

int initmouse()
{
  int result; // eax
  unsigned __int8 v1[36]; // [esp+0h] [ebp-24h] BYREF

  *(_WORD *)v1 = 0;
  result = int386(51, (int)v1, (int)v1);
  mouse = v1[0];
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall mousexy(int a1, int a2, int a3, int a4)
{
  int v4; // ecx
  int v5; // esi
  int result; // eax
  _WORD v7[4]; // [esp+0h] [ebp-2Ch] BYREF
  __int16 v8; // [esp+8h] [ebp-24h]
  __int16 v9; // [esp+Ch] [ebp-20h]
  int v10; // [esp+24h] [ebp-8h]

  v10 = a4;
  v7[0] = 11;
  int386(51, (int)v7, (int)v7);
  dxmouse = v8;
  dymouse = v9;
  v4 = v8 + mousex;
  v5 = mousey - v9;
  if (v4 > XMAX - 1)
    v4 = XMAX - 1;
  result = YMAX - 1;
  if (v5 > YMAX - 1)
    v5 = YMAX - 1;
  if (v4 < 0)
    v4 = 0;
  if (v5 < 0)
    v5 = 0;
  mousey = v5;
  mousex = v4;
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall mousebut(unsigned __int16 a1, int a2, int a3, int a4)
{
  _WORD v6[16]; // [esp+0h] [ebp-28h] BYREF
  int v7; // [esp+20h] [ebp-8h]

  v7 = a4;
  if (!mouse)
    return 0;
  v6[0] = 5;
  v6[2] = 0;
  int386(51, (int)v6, (int)v6);
  return a1 & v6[0];
}

//-------------------------------------------------------------------------------------------------

int __fastcall checkmouse(int a1, int a2, int a3, int a4)
{
  int result; // eax
  char v5; // cl
  _WORD v6[14]; // [esp+0h] [ebp-2Ch] BYREF
  char v7; // [esp+1Ch] [ebp-10h]
  int v8; // [esp+24h] [ebp-8h]

  v8 = a4;
  v7 = mpressed;
  if (mouse) {
    v6[0] = 5;
    v6[2] = 0;
    result = int386(51, (int)v6, (int)v6);
    v5 = v6[0] & 3;
  } else {
    v5 = 0;
  }
  mpressed = v5;
  if (v5) {
    if (v7)
      jpressed = 0;
    else
      jpressed = -1;
  } else {
    jpressed = 0;
  }
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall drmouse(int a1, int a2, int a3, int a4)
{
  int v4; // edi
  int v5; // ebx
  int v7; // eax
  unsigned __int8 *v8; // ebx
  int v9; // ebp
  int v10; // esi
  _BYTE *v11; // edx
  int i; // eax
  int v13; // ecx
  int result; // eax
  int v15; // [esp+0h] [ebp-1Ch]
  int v16; // [esp+4h] [ebp-18h]
  int v17; // [esp+8h] [ebp-14h]

  v4 = XMAX;
  v5 = a3 + 1;
  v7 = *(unsigned __int8 *)(v5 - 1);
  v8 = (unsigned __int8 *)(v5 + 1);
  v17 = a1 - v7;
  v9 = a2 - *(v8 - 1);
  v15 = a1 - v7 + a4;
  v10 = a1 - v7 + 16;
  v16 = v9 + 16;
  do {
    v11 = (_BYTE *)(v15 + v4 * v9);
    for (i = v17; i < v10; ++v11) {
      v13 = *v8++;
      if (v13 && i > 0 && i < v4)
        *v11 = v13;
      ++i;
    }
    result = v16;
    ++v9;
  } while (v9 != v16);
  XMAX = v4;
  return result;
}

//-------------------------------------------------------------------------------------------------

_BYTE *plotmouse()
{
  int v0; // ecx
  int v1; // esi
  _BYTE *result; // eax

  v0 = XMAX;
  v1 = mousex;
  result = (_BYTE *)(XMAX * (199 - mousey) + mousex + scrbuf);
  if (mousex > 3)
    *(result - 4) = -113;
  if (v1 > 2)
    *(result - 3) = -113;
  *result = -113;
  if (v1 < v0 - 3)
    result[3] = -113;
  if (v1 < v0 - 4)
    result[4] = -113;
  result[-4 * v0] = -113;
  result[-3 * v0] = -113;
  result[3 * v0] = -113;
  result[4 * v0] = -113;
  mousex = v1;
  XMAX = v0;
  return result;
}

//-------------------------------------------------------------------------------------------------

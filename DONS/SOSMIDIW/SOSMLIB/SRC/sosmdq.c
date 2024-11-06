#ifdef ENABLE_SOSMLIB_PSEUDO
//-------------------------------------------------------------------------------------------------

void sosMIDIDq_Start()
{
  ;
}

//-------------------------------------------------------------------------------------------------

int __fastcall digiQueueInit(int a1, int a2)
{
  int result; // eax
  unsigned int i; // [esp+8h] [ebp-4h]

  for (i = 0; i < 0x20; ++i) {
    _sMIDIDIGIQueue[128 * a1 + 4 * i] = -1;
    _sMIDIDIGIQueue_variable_1[128 * a1 + 4 * i] = -1;
    _sMIDIDIGIQueue_variable_3[128 * a1 + 4 * i] = -1;
    _sMIDIDIGIQueue_variable_2[128 * a1 + 4 * i] = -1;
  }
  _wMIDIDIGISampleQueueHead[a1] = 0;
  _wMIDIDIGISampleQueueTail[a1] = 0;
  _wMIDIDIGIUsedSamples[a1] = 0;
  result = a2;
  _wMIDIDIGIMaxSamples[a1] = a2;
  return result;
}

//-------------------------------------------------------------------------------------------------

void digiQueueUnInit()
{
  ;
}

//-------------------------------------------------------------------------------------------------

int __fastcall digiQueueAddItem(int a1, int a2, int a3, int a4, int a5)
{
  int *v7; // [esp+14h] [ebp-8h]
  int v8; // [esp+18h] [ebp-4h]

  if (_wMIDIDIGIUsedSamples[a1] >= (unsigned int)_wMIDIDIGIMaxSamples[a1])
    return -1;
  v8 = _wMIDIDIGISampleQueueHead[a1];
  v7 = &_sMIDIDIGIQueue[128 * a1 + 4 * v8];
  *v7 = a2;
  v7[1] = a3;
  v7[2] = a4;
  v7[3] = a5;
  ++_wMIDIDIGIUsedSamples[a1];
  ++_wMIDIDIGISampleQueueHead[a1];
  _wMIDIDIGISampleQueueHead[a1] &= 0x1Fu;
  return v8;
}

//-------------------------------------------------------------------------------------------------

int __fastcall digiQueueGetItem(int a1, int a2)
{
  int *v4; // [esp+Ch] [ebp-10h]
  int v5; // [esp+10h] [ebp-Ch]
  unsigned int i; // [esp+18h] [ebp-4h]

  if (!_wMIDIDIGIUsedSamples[a1])
    return -1;
  for (i = 0; i < 0x20; ++i) {
    v4 = &_sMIDIDIGIQueue[128 * a1 + 4 * i];
    if (v4[3] == a2 && *v4 != -1)
      break;
  }
  if (i == 32)
    return -1;
  v5 = *v4;
  while (i != _wMIDIDIGISampleQueueTail[a1]) {
    qmemcpy(&_sMIDIDIGIQueue[128 * a1 + 4 * i], &_sMIDIDIGIQueue[128 * a1 + 4 * (((_BYTE)i - 1) & 0x1F)], 0x10u);
    i = ((_BYTE)i - 1) & 0x1F;
  }
  _sMIDIDIGIQueue[128 * a1 + 4 * i] = -1;
  _sMIDIDIGIQueue_variable_1[128 * a1 + 4 * i] = -1;
  _sMIDIDIGIQueue_variable_3[128 * a1 + 4 * i] = -1;
  _sMIDIDIGIQueue_variable_2[128 * a1 + 4 * i] = -1;
  ++_wMIDIDIGISampleQueueTail[a1];
  _wMIDIDIGISampleQueueTail[a1] &= 0x1Fu;
  --_wMIDIDIGIUsedSamples[a1];
  return v5;
}

//-------------------------------------------------------------------------------------------------

int __fastcall digiQueueDeleteItemMIDI(int a1, int a2, int a3)
{
  int *v5; // [esp+10h] [ebp-10h]
  int v6; // [esp+14h] [ebp-Ch]
  unsigned int i; // [esp+1Ch] [ebp-4h]

  if (!_wMIDIDIGIUsedSamples[a1])
    return -1;
  for (i = 0; i < 0x20; ++i) {
    v5 = &_sMIDIDIGIQueue[128 * a1 + 4 * i];
    if (v5[1] == a2 && v5[3] == a3 && *v5 != -1)
      break;
  }
  if (i == 32)
    return -1;
  v6 = *v5;
  while (i != _wMIDIDIGISampleQueueTail[a1]) {
    qmemcpy(&_sMIDIDIGIQueue[128 * a1 + 4 * i], &_sMIDIDIGIQueue[128 * a1 + 4 * (((_BYTE)i - 1) & 0x1F)], 0x10u);
    i = ((_BYTE)i - 1) & 0x1F;
  }
  _sMIDIDIGIQueue[128 * a1 + 4 * i] = -1;
  _sMIDIDIGIQueue_variable_1[128 * a1 + 4 * i] = -1;
  _sMIDIDIGIQueue_variable_3[128 * a1 + 4 * i] = -1;
  _sMIDIDIGIQueue_variable_2[128 * a1 + 4 * i] = -1;
  ++_wMIDIDIGISampleQueueTail[a1];
  _wMIDIDIGISampleQueueTail[a1] &= 0x1Fu;
  --_wMIDIDIGIUsedSamples[a1];
  return v6;
}

//-------------------------------------------------------------------------------------------------

int __fastcall digiQueueDeleteItem(int a1, int a2)
{
  unsigned int i; // [esp+14h] [ebp-4h]

  if (!_wMIDIDIGIUsedSamples[a1])
    return -1;
  for (i = 0; i < 0x20 && _sMIDIDIGIQueue[128 * a1 + 4 * i] != a2; ++i)
    ;
  if (i == 32)
    return -1;
  while (i != _wMIDIDIGISampleQueueTail[a1]) {
    qmemcpy(&_sMIDIDIGIQueue[128 * a1 + 4 * i], &_sMIDIDIGIQueue[128 * a1 + 4 * (((_BYTE)i - 1) & 0x1F)], 0x10u);
    i = ((_BYTE)i - 1) & 0x1F;
  }
  _sMIDIDIGIQueue[128 * a1 + 4 * i] = -1;
  _sMIDIDIGIQueue_variable_1[128 * a1 + 4 * i] = -1;
  _sMIDIDIGIQueue_variable_3[128 * a1 + 4 * i] = -1;
  _sMIDIDIGIQueue_variable_2[128 * a1 + 4 * i] = -1;
  ++_wMIDIDIGISampleQueueTail[a1];
  _wMIDIDIGISampleQueueTail[a1] &= 0x1Fu;
  --_wMIDIDIGIUsedSamples[a1];
  return a2;
}

//-------------------------------------------------------------------------------------------------

int __fastcall digiQueueFindItemMIDI(int a1, int a2, int a3)
{
  int *v5; // [esp+10h] [ebp-10h]
  unsigned int i; // [esp+1Ch] [ebp-4h]

  if (!_wMIDIDIGIUsedSamples[a1])
    return -1;
  for (i = 0; i < 0x20; ++i) {
    v5 = &_sMIDIDIGIQueue[128 * a1 + 4 * i];
    if (v5[1] == a2 && v5[3] == a3 && *v5 != -1)
      break;
  }
  if (i == 32)
    return -1;
  else
    return *v5;
}

//-------------------------------------------------------------------------------------------------

int __fastcall digiQueueGetItemWAVE(int a1)
{
  int *v3; // [esp+8h] [ebp-10h]
  int v4; // [esp+Ch] [ebp-Ch]
  unsigned int i; // [esp+14h] [ebp-4h]

  if (!_wMIDIDIGIUsedSamples[a1])
    return -1;
  for (i = 0; i < 0x20; ++i) {
    v3 = &_sMIDIDIGIQueue[128 * a1 + 4 * i];
    if (*v3 != -1)
      break;
  }
  if (i == 32)
    return -1;
  v4 = *v3;
  while (i != _wMIDIDIGISampleQueueTail[a1]) {
    qmemcpy(&_sMIDIDIGIQueue[128 * a1 + 4 * i], &_sMIDIDIGIQueue[128 * a1 + 4 * (((_BYTE)i - 1) & 0x1F)], 0x10u);
    i = ((_BYTE)i - 1) & 0x1F;
  }
  _sMIDIDIGIQueue[128 * a1 + 4 * i] = -1;
  _sMIDIDIGIQueue_variable_1[128 * a1 + 4 * i] = -1;
  _sMIDIDIGIQueue_variable_3[128 * a1 + 4 * i] = -1;
  _sMIDIDIGIQueue_variable_2[128 * a1 + 4 * i] = -1;
  ++_wMIDIDIGISampleQueueTail[a1];
  _wMIDIDIGISampleQueueTail[a1] &= 0x1Fu;
  --_wMIDIDIGIUsedSamples[a1];
  return v4;
}

//-------------------------------------------------------------------------------------------------

int __fastcall digiQueueDeleteItemWAVE(int a1, int a2)
{
  if (_wMIDIDIGIUsedSamples[a1]) {
    while (a2 != _wMIDIDIGISampleQueueTail[a1]) {
      qmemcpy(&_sMIDIDIGIQueue[128 * a1 + 4 * a2], &_sMIDIDIGIQueue[128 * a1 + 4 * (((_BYTE)a2 - 1) & 0x1F)], 0x10u);
      a2 = ((_BYTE)a2 - 1) & 0x1F;
    }
    _sMIDIDIGIQueue[128 * a1 + 4 * a2] = -1;
    _sMIDIDIGIQueue_variable_1[128 * a1 + 4 * a2] = -1;
    _sMIDIDIGIQueue_variable_3[128 * a1 + 4 * a2] = -1;
    _sMIDIDIGIQueue_variable_2[128 * a1 + 4 * a2] = -1;
    ++_wMIDIDIGISampleQueueTail[a1];
    _wMIDIDIGISampleQueueTail[a1] &= 0x1Fu;
    --_wMIDIDIGIUsedSamples[a1];
  }
  return -1;
}

//-------------------------------------------------------------------------------------------------

void sosMIDIDq_End()
{
  ;
}

//-------------------------------------------------------------------------------------------------
#endif
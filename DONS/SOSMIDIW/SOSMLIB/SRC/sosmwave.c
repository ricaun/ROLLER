#include "sosmwave.h"
#include "sosmdata.h"
#include "../../../SOSDIGIW/SOSLIB/SRC/sosdata.h"
//-------------------------------------------------------------------------------------------------

int dwWAVEPitchTable[180] =               //000B84E0
{
  512,
  542,
  574,
  608,
  645,
  683,
  724,
  767,
  812,
  861,
  912,
  966,
  1024,
  1085,
  1149,
  1217,
  1290,
  1366,
  1448,
  1534,
  1625,
  1722,
  1824,
  1933,
  2048,
  2170,
  2299,
  2435,
  2580,
  2733,
  2896,
  3068,
  3251,
  3444,
  3649,
  3866,
  4096,
  4340,
  4598,
  4871,
  5160,
  5467,
  5793,
  6137,
  6502,
  6889,
  7299,
  7733,
  8192,
  8680,
  9197,
  9742,
  10321,
  10935,
  11586,
  12275,
  13005,
  13778,
  14599,
  15466,
  16384,
  17361,
  18394,
  19484,
  20642,
  21870,
  23173,
  24550,
  26010,
  27557,
  29198,
  30932,
  32768,
  34722,
  36788,
  38968,
  41285,
  43740,
  46346,
  49101,
  52020,
  55114,
  58396,
  61865,
  65536,
  69444,
  73577,
  77936,
  82571,
  87481,
  92692,
  98203,
  104040,
  110228,
  116792,
  123731,
  131072,
  138888,
  147154,
  155872,
  165142,
  174962,
  185384,
  196406,
  208080,
  220456,
  233584,
  247462,
  262144,
  277776,
  294308,
  311744,
  330284,
  349924,
  370768,
  392812,
  416160,
  440912,
  467168,
  494924,
  524288,
  555552,
  588616,
  623488,
  660568,
  699848,
  741536,
  785624,
  832320,
  881824,
  934336,
  989848,
  1048576,
  1111104,
  1177232,
  1246976,
  1321136,
  1399696,
  1483072,
  1571248,
  1664640,
  1763648,
  1868672,
  1979696,
  2097152,
  2222208,
  2354464,
  2493952,
  2642272,
  2799392,
  2966144,
  3142496,
  3329280,
  3527296,
  3737344,
  3959392,
  4194304,
  4444416,
  4708928,
  4987904,
  5284544,
  5598784,
  5932288,
  6284992,
  6658560,
  7054592,
  7474688,
  7918784,
  8388608,
  8888832,
  9417856,
  9975808,
  10569088,
  11197568,
  11864576,
  12569984,
  13317120,
  14109184,
  14949376,
  15837568
};
tWaveVoice waveVoice[32] =                //000B87B0
{
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 },
  { 0u, 255u, 0u, 0u, 65536, 255, 255, 255 }
};

//-------------------------------------------------------------------------------------------------

int waveSendData(unsigned int a1, int a2, int a3, int a4)
{
  return 0;
  /*
  __int64 BestSample; // rcx
  unsigned int ItemWAVE; // eax
  unsigned int v7; // [esp+0h] [ebp-38h]
  unsigned int v8; // [esp+8h] [ebp-30h]
  unsigned int v9; // [esp+Ch] [ebp-2Ch]
  unsigned __int8 v10; // [esp+10h] [ebp-28h]
  unsigned int v11; // [esp+20h] [ebp-18h]
  int v12; // [esp+20h] [ebp-18h]
  int ItemMIDI; // [esp+20h] [ebp-18h]
  void (__noreturn * v14)(); // [esp+24h] [ebp-14h]
  unsigned int v15; // [esp+2Ch] [ebp-Ch]
  int v16; // [esp+34h] [ebp-4h]
  _BYTE retaddr[8]; // [esp+44h] [ebp+Ch]

  v10 = __readgsbyte(a1);
  v9 = __readgsbyte(a1 + 1);
  v8 = __readgsbyte(a1 + 2);
  v16 = v10 & 0xF;
  v7 = v10 & 0xF0;
  if (v7 < 0xB0) {
    if (v7 >= 0x80) {
      if (v7 <= 0x80) {
        if (!waveChannel_variable_4[6 * v16]) {
          ItemMIDI = digiQueueFindItemMIDI(a4, v9, v16);
          if (ItemMIDI != -1)
            sosWAVEPStopSample(a4, ItemMIDI);
        }
      } else if (v7 == 144) {
        BestSample = waveGetBestSample((unsigned __int8)waveChannel[6 * v16], v9);
        lpWAVEStartSample_variable_1 = WORD2(BestSample);
        lpWAVEStartSample = BestSample;
        if ((_DWORD)BestSample || lpWAVEStartSample_variable_1) {
          if (v8) {
            v15 = __readgsdword(lpWAVEStartSample + 36);
            v14 = dwWAVEPitchTable_variable_2[v9 - v15];
            if (waveChannel_variable_2[6 * v16] == 64)
              __writegsdword(lpWAVEStartSample + 56, (unsigned int)v14);
            else
              __writegsdword(lpWAVEStartSample + 56, waveCalculatePitchBend(v16, v14, v9, v15));
            if (_wMIDIDIGIVelocitySensing[a4])
              __writegsdword(lpWAVEStartSample + 20, 8 * v8 * (unsigned __int8)waveChannel_variable_1[6 * v16]);
            else
              __writegsdword(lpWAVEStartSample + 20, _wSOSMIDISongVolume[0] << 8);
            __writegsdword(lpWAVEStartSample + 24, v9);
            if (waveChannel_variable_5[6 * v16] >= 0)
              __writegsdword(lpWAVEStartSample + 64, (unsigned __int8)waveChannel_variable_5[6 * v16] << 9);
            if (_wMIDIDIGIUsedSamples[a4] >= (unsigned int)_wMIDIDIGIMaxSamples[a4]) {
              ItemWAVE = digiQueueGetItemWAVE(a4);
              sosDIGIStopSample(_wMIDIDIGIDriverHandle[a4], ItemWAVE);
            }
            __writegsbyte(lpWAVEStartSample + 40, __readgsbyte(lpWAVEStartSample + 40) | 0x80);
            v11 = sosDIGIStartSample(_wMIDIDIGIDriverHandle[a4], lpWAVEStartSample, lpWAVEStartSample);
            sosDIGISetMasterVolume(0, 0x7FFFu / _wMIDIDIGIMaxSamples[a4]);
            if (v11 != -1) {
              waveVoice_variable_6[5 * v11] = digiQueueAddItem(a4, v11, __readgsdword(lpWAVEStartSample + 24), v8, v16);
              waveVoice[20 * v11] = 1;
              waveVoice_variable_1[20 * v11] = v9;
              waveVoice_variable_2[20 * v11] = v15;
              *(&waveVoice_variable_3 + 5 * v11) = (void (__noreturn *)())__readgsdword(lpWAVEStartSample + 56);
              waveVoice_variable_4[5 * v11] = v16;
              waveVoice_variable_5[5 * v11] = v8;
            }
          } else if (!waveChannel_variable_4[6 * v16]) {
            v12 = digiQueueFindItemMIDI(a4, v9, v16);
            if (v12 != -1)
              sosWAVEPStopSample(a4, v12);
          }
        }
      }
    }
  } else if (v7 <= 0xB0) {
    if (v9 < 0x40) {
      if (v9 >= 7) {
        if (v9 <= 7) {
          waveChannel_variable_1[6 * v16] = v8;
          waveChannelSetVolume(v16, a4);
        } else if (v9 == 10) {
          waveChannel_variable_5[6 * v16] = v8;
          waveChannelSetPan(v16, a4);
        }
      }
    } else if (v9 <= 0x40) {
      waveChannel_variable_4[6 * v16] = v8;
      if (!waveChannel_variable_4[6 * v16])
        waveChannelNotesOff(v16, a4);
    } else if (v9 < 0x79) {
      if (v9 == 102)
        waveChannel_variable_3[6 * v16] = v8 >> 1;
    } else if (v9 <= 0x79) {
      waveChannelResetControllers(v16, a4);
    } else if (v9 == 123) {
      waveChannelNotesOff(v16, a4);
    }
  } else if (v7 >= 0xC0) {
    if (v7 <= 0xC0) {
      waveChannel[6 * v16] = v9;
    } else if (v7 == 224) {
      waveChannel_variable_2[6 * v16] = v9;
      waveChannelSetBend(v16, a4);
    }
  }
  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(0);*/
}

//-------------------------------------------------------------------------------------------------

int *waveGetCallTable()
{
  return NULL;
  //return &_lpMIDIWAVEDrvFunctions;
}

//-------------------------------------------------------------------------------------------------

int waveInit(unsigned int a1, int a2, int a3)
{
  return 0;
  /*
  int v3; // ebx
  int v4; // ecx
  unsigned int v5; // ebx
  unsigned int v7; // eax
  int v8; // ebx
  int v9; // [esp+14h] [ebp-Ch]
  int v10; // [esp+18h] [ebp-8h] BYREF
  unsigned int i; // [esp+1Ch] [ebp-4h]
  _BYTE retaddr[8]; // [esp+2Ch] [ebp+Ch]

  _wSOSWAVEInsDataSet = 0;
  for (i = 0; i < 5; ++i) {
    if (_sSOSDIGIInitDriver_variable_5[19 * i] == __readgsdword(a1)) {
      _wMIDIDIGIDriverHandle[a3] = i;
      v10 = i;
      break;
    }
  }
  if (i == 5) {
    HIWORD(v3) = HIWORD(a1);
    LOWORD(v3) = __readgsword(a1 + 32);
    v4 = v3;
    v5 = __readgsdword(a1 + 28);
    v9 = sosDIGIInitDriver(
           __readgsdword(a1),
           v5,
           v5,
           v4,
           __readgsdword(a1 + 20),
           __readgsword(a1 + 24),
           (unsigned int)&v10,
           (unsigned __int16)__SS__);
    if (v9)
      return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(v9);
    _wMIDIDIGIDriverHandle[a3] = v10;
    v7 = __readgsdword(a1 + 20);
    v8 = __readgsdword(v7 + 28);
    v9 = sosTIMERRegisterEvent(
           __readgsdword(a1 + 4),
           v8,
           v8,
           __readgsword(v7 + 32),
           (unsigned int)&_wMIDIDIGITimerEventHandle[a3],
           (unsigned __int16)__DS__);
    if (v9)
      return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(v9);
    _wMIDIDIGIDriverInitMIDI[a3] = 1;
    _wMIDIDIGIDriverInitialized[a3] = 1;
  } else {
    _wMIDIDIGIDriverInitMIDI[a3] = 0;
  }
  _wMIDIDIGIVelocitySensing[a3] = __readgsdword(a1 + 16);
  digiQueueInit(a3, __readgsdword(a1 + 12));
  for (i = 0; i < 0x10; ++i)
    waveChannel_variable_5[6 * i] = 0x80;
  waveDIGIMIDIHandle[v10] = a3;
  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(0);*/
}

//-------------------------------------------------------------------------------------------------

int waveUnInit(int a1, int a2, int a3, int a4)
{
  return 0;
  /*
  _BYTE retaddr[8]; // [esp+10h] [ebp+Ch]

  if (_wMIDIDIGIDriverInitialized[a4]) {
    _wMIDIDIGIDriverInitialized[a4] = 0;
    if (_wMIDIDIGIDriverInitMIDI[a4]) {
      sosTIMERRemoveEvent(_wMIDIDIGITimerEventHandle[a4], a1);
      a1 = 1;
      sosDIGIUnInitDriver(_wMIDIDIGIDriverHandle[a4], 1, 1);
    }
  }
  digiQueueUnInit();
  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(0, a1);*/
}

//-------------------------------------------------------------------------------------------------

int waveReset(int a1, int a2, int a3)
{
  return 0;
  /*
  _BYTE retaddr[8]; // [esp+10h] [ebp+Ch]

  digiQueueInit(a3, _wMIDIDIGIMaxSamples[a3]);
  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(0);*/
}

//-------------------------------------------------------------------------------------------------

int waveSetInstrumentData(int a1, int16 a2)
{
  return 0;
  /*
  int v2; // eax
  __int16 v3; // dx
  int v4; // edx
  unsigned int v5; // eax
  unsigned int v6; // eax
  unsigned int v7; // eax
  unsigned int v8; // edx
  unsigned int v9; // eax
  unsigned int v10; // eax
  unsigned __int16 v12; // [esp+4h] [ebp-Ch]
  unsigned int i; // [esp+Ch] [ebp-4h]
  _BYTE retaddr[8]; // [esp+1Ch] [ebp+Ch]

  _wSOSWAVEInsDataSet = 1;
  lpWAVEHeader_variable_1 = a2;
  lpWAVEHeader = a1;
  for (i = 0; i < 0x80; ++i) {
    v2 = lpWAVEHeader + 6 * i;
    if (__readgsdword(v2 + 40) || __readgsword(v2 + 44)) {
      v3 = lpWAVEHeader_variable_1;
      sosMIDINormalizePtr();
      v12 = v3;
      v4 = 6 * i + lpWAVEHeader;
      __writegsword(v4 + 44, v12);
      __writegsdword(v4 + 40, v5);
      lpWAVEStartSample_variable_1 = v12;
      for (lpWAVEStartSample = v5; __readgsdword(lpWAVEStartSample + 44); lpWAVEStartSample = v10) {
        v6 = lpWAVEStartSample;
        __writegsword(lpWAVEStartSample + 32, __CS__);
        __writegsdword(v6 + 28, (unsigned int)waveSampleCallback);
        sosMIDINormalizePtr();
        v8 = v7;
        v9 = lpWAVEStartSample;
        __writegsword(lpWAVEStartSample + 4, v12);
        __writegsdword(v9, v8);
        sosMIDINormalizePtr();
        lpWAVEStartSample_variable_1 = v12;
      }
    }
  }
  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(0);*/
}

//-------------------------------------------------------------------------------------------------

int waveSampleCallback(int a1, int a2, int a3)
{
  return 0;
  /*
  _BYTE retaddr[8]; // [esp+Ch] [ebp+Ch]

  if (a2 == 2)
    digiQueueDeleteItemWAVE(waveDIGIMIDIHandle[a1], waveVoice_variable_6[5 * a3]);
  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)();*/
}

//-------------------------------------------------------------------------------------------------

int sosWAVEPStopSample(int a1, int a2)
{
  return 0;
  /*
  int v3; // [esp+4h] [ebp-4h]

  waveVoice[20 * a2] = 0;
  v3 = _wMIDIDIGIDriverHandle[a1];
  if (__readgsword(*(_DWORD *)&_lpSOSSampleList[192 * v3 + 6 * a2] + 56) > 1u)
    __writegsword(*(_DWORD *)&_lpSOSSampleList[192 * v3 + 6 * a2] + 56, 1u);
  return 0;*/
}

//-------------------------------------------------------------------------------------------------

int waveChannelResetControllers(uint8 a1, int a2)
{
  return 0;
  /*
  waveChannel_variable_1[6 * a1] = 127;
  waveChannel_variable_2[6 * a1] = 64;
  waveChannel_variable_3[6 * a1] = 2;
  waveChannel_variable_4[6 * a1] = 0;
  waveChannelSetVolume(a1, a2);
  waveChannelSetPan(a1, a2);
  waveChannelSetBend(a1, a2);
  return 0;*/
}

//-------------------------------------------------------------------------------------------------

int waveChannelSetVolume(uint8 a1, int a2)
{
  return 0;
  /*
  int *v3; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  for (i = _wMIDIDIGISampleQueueTail[a2]; i != _wMIDIDIGISampleQueueHead[a2]; i = ((_BYTE)i + 1) & 0x1F) {
    v3 = &_sMIDIDIGIQueue[128 * a2 + 4 * i];
    if (*((_BYTE *)v3 + 12) == a1 && *v3 != -1)
      sosDIGISetSampleVolume(
        _wMIDIDIGIDriverHandle[a2],
        *v3,
        8 * *((_WORD *)v3 + 4) * (unsigned __int8)waveChannel_variable_1[6 * a1]);
  }
  return 0;*/
}

//-------------------------------------------------------------------------------------------------

int waveChannelSetPan(uint8 a1, int a2)
{
  return 0;
  /*
  int i; // [esp+Ch] [ebp-4h]

  for (i = _wMIDIDIGISampleQueueTail[a2]; i != _wMIDIDIGISampleQueueHead[a2]; i = ((_BYTE)i + 1) & 0x1F) {
    if (a1 == _sMIDIDIGIQueue[128 * a2 + 3 + 4 * i])
      sosDIGISetPanLocation(
        _wMIDIDIGIDriverHandle[a2],
        _sMIDIDIGIQueue[128 * a2 + 4 * i],
        (unsigned __int8)waveChannel_variable_5[6 * a1] << 9);
  }
  return 0;*/
}

//-------------------------------------------------------------------------------------------------

void waveChannelSetBend(uint8 byMidiChannel, int iDriverIdx)
{                                               // Iterate through MIDI DIGI sample queue (circular buffer, 32 entries max)
  int iPitchBend; // eax
  tMIDIDIGIQueue *pQueueEntry; // [esp+0h] [ebp-1Ch]
  int iQueueIndex; // [esp+8h] [ebp-14h]
  unsigned int uiBaseNote; // [esp+14h] [ebp-8h]
  unsigned int uiMidiNote; // [esp+18h] [ebp-4h]

  for (iQueueIndex = _wMIDIDIGISampleQueueTail[iDriverIdx]; iQueueIndex != _wMIDIDIGISampleQueueHead[iDriverIdx]; iQueueIndex = ((uint8)iQueueIndex + 1) & 0x1F) {
    pQueueEntry = &_sMIDIDIGIQueue[iDriverIdx][iQueueIndex];// Get pointer to current queue entry (4 DWORDs per entry)
    if (byMidiChannel == pQueueEntry->iMidiChannel)  // Check if queue entry matches the specified MIDI channel
    {
      uiMidiNote = waveVoice[pQueueEntry->iSampleHandle].byMidiNote;// Read voice parameters for pitch bend calculation
      uiBaseNote = waveVoice[pQueueEntry->iSampleHandle].byBaseNote;
      if (uiMidiNote < uiBaseNote)            // Calculate pitch table index based on voice parameter relationship
        iPitchBend = 84 - (uiBaseNote - uiMidiNote);
      else
        iPitchBend = uiMidiNote + 84 - uiBaseNote;
      //__writegsdword(
      //  (unsigned int)_lpSOSSampleList[_wMIDIDIGIDriverHandle[iDriverIdx]][pQueueEntry->iSampleHandle].pSample + 68,
      //  waveCalculatePitchBend(byMidiChannel, dwWAVEPitchTable[iPitchBend], uiMidiNote, uiBaseNote));// Apply calculated pitch bend to the active sample (offset +68 = pitch)
    }
  }
}

//-------------------------------------------------------------------------------------------------

int waveChannelNotesOff(uint8 a1, int a2)
{
  return 0;
  /*
  unsigned int Item; // [esp+0h] [ebp-8h]

  while (1) {
    Item = digiQueueGetItem(a2, a1);
    if (Item == -1)
      break;
    sosDIGIStopSample(_wMIDIDIGIDriverHandle[a2], Item);
  }
  return 0;*/
}

//-------------------------------------------------------------------------------------------------

uint8 *StringOut(uint8 a1, uint8 a2, uint8 *a3, uint8 a4)
{
  return NULL;
  /*
  unsigned __int8 *result; // eax
  unsigned __int8 *v5; // eax
  unsigned int v6; // edx
  char *i; // [esp+0h] [ebp-18h]

  xgetES();
  for (i = (char *)&unk_B8000 + 160 * a2 + 2 * a1; ; i += 2) {
    result = a3;
    if (!*a3)
      break;
    v5 = a3++;
    __writegsbyte((unsigned int)i, *v5);
    v6 = (unsigned int)(i + 1);
    __writegsbyte(v6, a4);
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

unsigned int waveCalculatePitchBend(uint8 a1, int a2, unsigned int a3, unsigned int a4)
{
  return 0;
  /*
  int v5; // [esp+0h] [ebp-30h]
  int v6; // [esp+8h] [ebp-28h]
  unsigned int v7; // [esp+10h] [ebp-20h]
  unsigned int v8; // [esp+1Ch] [ebp-14h]

  v5 = abs(a3 - a4);
  if (a3 <= a4)
    v6 = 84 - v5;
  else
    v6 = v5 + 84;
  v7 = (unsigned __int8)waveChannel_variable_2[6 * a1];
  v8 = 64 / (unsigned __int8)waveChannel_variable_3[6 * a1];
  if (v7 >= 0x40)
    return (dwWAVEPitchTable_variable_1[(v7 - 64) / v8 + v6] - dwWAVEPitchTable[(v7 - 64) / v8 + v6])
    / v8
    * ((v7 - 64) % v8)
    + dwWAVEPitchTable[(v7 - 64) / v8 + v6]
    - dwWAVEPitchTable[v6]
    + a2;
  else
    return a2
    - (dwWAVEPitchTable[v6]
     - dwWAVEPitchTable[v6 - (64 - v7) / v8])
    - (dwWAVEPitchTable[v6 - (64 - v7) / v8] - _wSOSWAVEInsDataSet[v6 - (64 - v7) / v8]) / v8 * ((64 - v7) % v8);*/
}

//-------------------------------------------------------------------------------------------------

int64 waveGetBestSample(int a1, uint8 a2)
{
  return 0;/*
  int v2; // eax
  int v3; // edx
  __int64 v5; // [esp+0h] [ebp-20h]
  unsigned int i; // [esp+8h] [ebp-18h]
  unsigned __int16 v7; // [esp+Ch] [ebp-14h]
  unsigned int v8; // [esp+10h] [ebp-10h]
  unsigned __int16 v9; // [esp+14h] [ebp-Ch]
  unsigned int v10; // [esp+1Ch] [ebp-4h]

  if (_wSOSWAVEInsDataSet[0] && ((v2 = lpWAVEHeader + 6 * a1, __readgsdword(v2 + 40)) || __readgsword(v2 + 44))) {
    v3 = 6 * a1 + lpWAVEHeader;
    v9 = __readgsword(v3 + 44);
    v8 = __readgsdword(v3 + 40);
    v7 = v9;
    v10 = abs(__readgsdword(v8 + 36) - a2);
    for (i = v8 + 116 + __readgsdword(v8 + 44); __readgsdword(i + 44); i += 116 + __readgsdword(i + 44)) {
      if (abs(__readgsdword(i + 36) - a2) < v10) {
        v10 = abs(__readgsdword(i + 36) - a2);
        v9 = v7;
        v8 = i;
      }
    }
    WORD2(v5) = v9;
    LODWORD(v5) = v8;
  } else {
    WORD2(v5) = 0;
    LODWORD(v5) = 0;
  }
  return v5;*/
}

//-------------------------------------------------------------------------------------------------
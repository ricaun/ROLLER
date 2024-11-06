
//-------------------------------------------------------------------------------------------------

void sosMIDIIns_Start()
{
  ;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDISetInsData(int a1, int a2, int a3, unsigned __int16 a4)
{
  return MK_FP(_lpSOSMIDIDrvFunction_variable_5[18 * a1 + 1], _lpSOSMIDIDrvFunction_variable_5[18 * a1])(a3, a4, a1, a2);
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDISetMT32InsData(int a1, unsigned int a2, int a3, unsigned __int16 a4)
{
  int (__far * v4)(); // edx
  int v5; // eax
  int v10; // [esp+1Ch] [ebp-8h] BYREF
  unsigned int i; // [esp+20h] [ebp-4h]

  if (!a2)
    return 0;
  for (i = 0; i < 0xFFFF; ++i)
    ;
  v4 = sosMIDIMT32Timer;
  v5 = sosTIMERRegisterEvent(
         0x5DCu,
         (int)sosMIDIMT32Timer,
         (int)sosMIDIMT32Timer,
         __CS__,
         (unsigned int)&v10,
         (unsigned __int16)__SS__);
  if (!v5) {
    for (i = 0; i < a2; ++i) {
      while (!_bSOSMIDIMT32SendData)
        ;
      _bSOSMIDIMT32SendData = 0;
      v4 = (int (__far *)())(i + a3);
      MK_FP(_lpSOSMIDIDrvFunction_variable_5[18 * a1 + 1], _lpSOSMIDIDrvFunction_variable_5[18 * a1])(i + a3, a4, 1, a1);
    }
    sosTIMERRemoveEvent(v10, (int)v4);
    return 0;
  }
  return v5;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDIMT32Timer(int a1, int a2, int a3, int a4)
{
  _BYTE retaddr[8]; // [esp+18h] [ebp+18h]

  _bSOSMIDIMT32SendData = 1;
  return MK_FP(*(_WORD *)retaddr, *(_DWORD *)retaddr)(a1, a2, a3, a4);
}

//-------------------------------------------------------------------------------------------------

void sosMIDIIns_End()
{
  ;
}

//-------------------------------------------------------------------------------------------------
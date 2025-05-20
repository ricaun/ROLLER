/*
//-------------------------------------------------------------------------------------------------

void sosMIDITmpo_Start()
{
  ;
}

//-------------------------------------------------------------------------------------------------

int __fastcall sosMIDISongAlterTempo(int a1, int a2)
{
  unsigned int v5; // [esp+Ch] [ebp-8h]

  if (sosMIDISongDone(a1))
    return 0;
  v5 = (__readgsdword(*(_DWORD *)&_sSOSMIDISongHeader[6 * a1] + 56) * ((a2 << 16) / 0x64u)) >> 16;
  if (!v5)
    v5 = 1;
  sosTIMERAlterEventRate(_wSOSMIDIEventHandle[a1], v5);
  return sosTIMERGetEventRate(_wSOSMIDIEventHandle[a1]);
}

//-------------------------------------------------------------------------------------------------

unsigned int __fastcall sosMIDIGetTimeToPlay(int a1)
{
  return __readgsdword(*(_DWORD *)&_sSOSMIDISongHeader[6 * a1] + 60);
}

//-------------------------------------------------------------------------------------------------

void sosMIDITmpo_End()
{
  ;
}

//-------------------------------------------------------------------------------------------------
*/
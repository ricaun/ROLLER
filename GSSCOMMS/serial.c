#ifdef ENABLE_GSSCOMMS_PSEUDO
//-------------------------------------------------------------------------------------------------

int __fastcall gssCommsSetType(unsigned int a1)
{
  if (a1 > 2)
    return 0;
  gssCommsType = a1;
  return -1;
}

//-------------------------------------------------------------------------------------------------

int gssCommsGetType()
{
  return gssCommsType;
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssCommsSetComPort(int result)
{
  gssCommsPort = result;
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssCommsSetComBaudRate(int result)
{
  gssCommsBaud = result;
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssCommsSetCommandBase(int result)
{
  gssBase = result;
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssCommsInitSystem(int a1)
{
  int result; // eax

  if (gssCommsType)
    return gssSerialInitSystem(a1);
  result = hmiNETNOWInitSystem(a1);
  gssHMI = (result != 0) - 1;
  return result;
}

//-------------------------------------------------------------------------------------------------

int __spoils<> gssCommsUnInitSystem()
{
  int result; // eax

  if (gssCommsType)
    return gssSerialUnInitSystem();
  if (!gssHMI)
    return 0;
  result = hmiNETNOWUnInitSystem();
  if (result) {
    result = 1;
    gssHMI = 0;
  }
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssCommsGetNetworkAddr(int *a1)
{
  if (!gssCommsType)
    return hmiNETNOWGetNetworkAddr((int)a1);
  if (!gssserial_initialised)
    return 0;
  qmemcpy(a1, &gssserial_address[4 * gssserial_consolenode], 0x10u);
  return 1;
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssCommsNetAddrToNode(int a1)
{
  if (gssCommsType)
    return gssSerialNetAddrToNode(a1);
  else
    return hmiNETNOWNetAddrToNode(a1);
}

//-------------------------------------------------------------------------------------------------

int gssCommsGetActiveNodes()
{
  if (gssCommsType)
    return gssserial_activenodes;
  else
    return hmiNETNOWGetActiveNodes();
}

//-------------------------------------------------------------------------------------------------

int gssCommsGetConsoleNode()
{
  if (gssCommsType)
    return gssserial_consolenode;
  else
    return hmiNETNOWGetConsoleNode();
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssCommsAddNode(int a1)
{
  if (gssCommsType)
    return gssSerialAddNode(a1);
  else
    return hmiNETNOWAddNode(a1);
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssCommsDeleteNode(int a1)
{
  if (gssCommsType)
    return gssSerialDeleteNode(a1);
  else
    return hmiNETNOWDeleteNode(a1);
}

//-------------------------------------------------------------------------------------------------

void gssCommsSortNodes()
{
  int v0; // [esp+0h] [ebp-28h]
  int v1; // [esp+4h] [ebp-24h]
  int v2; // [esp+8h] [ebp-20h]
  int v3; // [esp+Ch] [ebp-1Ch]

  if (gssCommsType) {
    if (gssserial_activenodes == 2
      && (int)gssSerialCompareAddress(
        gssserial_address[0],
        gssserial_address_variable_1,
        gssserial_address_variable_2,
        gssserial_address_variable_3,
        gssserial_address_variable_4,
        gssserial_address_variable_5,
        gssserial_address_variable_6,
        gssserial_address_variable_7) > 0) {
      v0 = gssserial_address[0];
      v1 = gssserial_address[1];
      v2 = gssserial_address[2];
      v3 = gssserial_address[3];
      gssserial_address[0] = gssserial_address_variable_4;
      gssserial_address[1] = *(&gssserial_address_variable_4 + 1);
      gssserial_address[2] = *(&gssserial_address_variable_4 + 2);
      gssserial_address[3] = *(&gssserial_address_variable_4 + 3);
      gssserial_address_variable_4 = v0;
      *(&gssserial_address_variable_4 + 1) = v1;
      *(&gssserial_address_variable_4 + 2) = v2;
      *(&gssserial_address_variable_4 + 3) = v3;
      gssserial_consolenode = 1 - gssserial_consolenode;
    }
  } else {
    hmiNETNOWSortNodes();
  }
}

//-------------------------------------------------------------------------------------------------

int gssCommsPostListen()
{
  int result; // eax

  if (!gssCommsType)
    return hmiNETNOWPostListen();
  result = 0;
  gssserial_status = 0;
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssCommsSendData(int a1, int a2, int a3, int a4, int a5)
{
  if (gssCommsType)
    return gssSerialSendData(a5);
  else
    return hmiNETNOWSendData(a1, a2, a3, a4, a5);
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssCommsGetHeader(int a1, int a2, int a3, int a4)
{
  if (gssCommsType)
    return gssSerialGetHeader(a4);
  else
    return hmiNETNOWGetHeader(a1, a2, a3);
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssCommsGetBlock(const void *a1, void *a2, int a3)
{
  int result; // eax

  if (!gssCommsType)
    return hmiNETNOWGetBlock((int)a1, (int)a2, a3);
  result = a3;
  qmemcpy(a2, a1, a3);
  return result;
}

//-------------------------------------------------------------------------------------------------

int gssSerialInitSystem()
{
  int v0; // edx
  int v1; // eax
  int v2; // eax
  unsigned __int8 v3; // al
  __int64 v4; // rtt
  int v5; // ebx
  int result; // eax
  _WORD v7[3]; // [esp+0h] [ebp-20h] BYREF
  unsigned __int16 v8; // [esp+6h] [ebp-1Ah]

  gssModemOnline = 0;
  if (gssBase_variable_1) {
    dos_getdiskfree(0, v7);
    v0 = v7[1] * v7[2];
    gssserial_local = v0 * v8;
    __asm { int     11h; EQUIPMENT DETERMINATION }
    *(&gssserial_local + 1) = (unsigned __int16)(v0 * v8);
    v1 = time(0);
    *(&gssserial_local + 2) = v1;
    v2 = clock(v1);
    gssBase_variable_1 = 0;
    *(&gssserial_local + 3) = v2;
  }
  if (gssserial_initialised)
    return 2;
  qmemcpy(gssserial_address, &gssserial_local, 0x10u);
  memset(&gssserial_address_variable_4, 0, 16);
  gssserial_consolenode = 0;
  gssserial_activenodes = 1;
  gss_ser_init(gssCommsPort);
  v3 = __inbyte(gss_port_address + 3);
  __outbyte(gss_port_address + 3, v3 | 0x80);
  LODWORD(v4) = (char *)&loc_1C1FD + 3;
  HIDWORD(v4) = ((int)&loc_1C1FD + 3) >> 31;
  v5 = v4 / gssCommsBaud;
  _disable();
  __outbyte(gss_port_address, v5 % 256);
  __outbyte(gss_port_address + 1, v5 / 256);
  _enable();
  __outbyte(gss_port_address + 3, v3 & 0x7F);
  gssserial_status = 0;
  i_read = 0;
  i_write = 0;
  gssserial_messsize = 0;
  gssserial_initialised = 1;
  while (1) {
    result = gssrxused();
    if (!result)
      break;
    gssreadchar();
  }
  return result;
}

//-------------------------------------------------------------------------------------------------

int gssSerialUnInitSystem()
{
  int result; // eax

  if (!gssserial_initialised)
    return 0;
  while (gsstxused())
    ;
  if (gssCommsType == 2)
    gssModemHangUp(0);
  _disable();
  gss_ser_uninit(gssCommsPort, 32);
  _enable();
  __outbyte(0x20u, 0x20u);
  result = 1;
  gssserial_initialised = 0;
  gssModemOnline = 0;
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssSerialGetNetworkAddr(int *a1)
{
  if (!gssserial_initialised)
    return 0;
  qmemcpy(a1, &gssserial_address[4 * gssserial_consolenode], 0x10u);
  return 1;
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssSerialNetAddrToNode(_DWORD *a1)
{
  if (!gssSerialCompareAddress(
    *a1,
    a1[1],
    a1[2],
    a1[3],
    gssserial_address[4 * gssserial_consolenode],
    gssserial_address_variable_1[4 * gssserial_consolenode],
    gssserial_address_variable_2[4 * gssserial_consolenode],
    gssserial_address_variable_3[4 * gssserial_consolenode]))
    return gssserial_consolenode;
  if (gssserial_activenodes != 2
    || gssSerialCompareAddress(
      *a1,
      a1[1],
      a1[2],
      a1[3],
      gssserial_address[4 * (1 - gssserial_consolenode)],
      gssserial_address_variable_1[4 * (1 - gssserial_consolenode)],
      gssserial_address_variable_2[4 * (1 - gssserial_consolenode)],
      gssserial_address_variable_3[4 * (1 - gssserial_consolenode)])) {
    return -1;
  }
  return 1 - gssserial_consolenode;
}

//-------------------------------------------------------------------------------------------------

int gssSerialGetActiveNodes()
{
  return gssserial_activenodes;
}

//-------------------------------------------------------------------------------------------------

int gssSerialGetConsoleNode()
{
  return gssserial_consolenode;
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssSerialAddNode(int *a1)
{
  int *v3; // edi
  int *v4; // esi

  if (gssserial_activenodes == 2) {
    if (gssSerialCompareAddress(
      gssserial_address[0],
      gssserial_address_variable_1[0],
      gssserial_address_variable_2[0],
      gssserial_address_variable_3[0],
      *a1,
      a1[1],
      a1[2],
      a1[3])) {
      if (gssSerialCompareAddress(
        gssserial_address_variable_4,
        gssserial_address_variable_5,
        gssserial_address_variable_6,
        gssserial_address_variable_7,
        *a1,
        a1[1],
        a1[2],
        a1[3])) {
        return 2;
      } else {
        return 1;
      }
    } else {
      return 1;
    }
  } else if (gssSerialCompareAddress(
    gssserial_address[4 * gssserial_consolenode],
    gssserial_address_variable_1[4 * gssserial_consolenode],
    gssserial_address_variable_2[4 * gssserial_consolenode],
    gssserial_address_variable_3[4 * gssserial_consolenode],
    *a1,
    a1[1],
    a1[2],
    a1[3])) {
    v3 = &gssserial_address[4 * (1 - gssserial_consolenode)];
    *v3 = *a1;
    v4 = a1 + 1;
    *++v3 = *v4++;
    *++v3 = *v4;
    v3[1] = v4[1];
    gssserial_activenodes = 2;
    return 0;
  } else {
    return 1;
  }
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssSerialDeleteNode(unsigned int a1)
{
  if (gssserial_activenodes < 2 || a1 > 1 || a1 == gssserial_consolenode)
    return 1;
  gssserial_activenodes = 1;
  if (!a1) {
    gssserial_consolenode = 0;
    gssserial_address[0] = gssserial_address_variable_4;
    gssserial_address[1] = *(&gssserial_address_variable_4 + 1);
    gssserial_address[2] = *(&gssserial_address_variable_4 + 2);
    gssserial_address[3] = *(&gssserial_address_variable_4 + 3);
  }
  return 0;
}

//-------------------------------------------------------------------------------------------------

void gssSerialSortNodes()
{
  int v0; // ecx
  int v1; // [esp+0h] [ebp-28h]
  int v2; // [esp+4h] [ebp-24h]
  int v3; // [esp+8h] [ebp-20h]
  int v4; // [esp+Ch] [ebp-1Ch]

  if (gssserial_activenodes == 2
    && (int)gssSerialCompareAddress(
      gssserial_address[0],
      gssserial_address_variable_1[0],
      gssserial_address_variable_2[0],
      gssserial_address_variable_3[0],
      gssserial_address_variable_4,
      gssserial_address_variable_5,
      gssserial_address_variable_6,
      gssserial_address_variable_7) > 0) {
    v1 = gssserial_address[0];
    v2 = gssserial_address[1];
    v3 = gssserial_address[2];
    v4 = gssserial_address[3];
    v0 = gssserial_consolenode;
    gssserial_address[0] = gssserial_address_variable_4;
    gssserial_address[1] = *(&gssserial_address_variable_4 + 1);
    gssserial_address[2] = *(&gssserial_address_variable_4 + 2);
    gssserial_address[3] = *(&gssserial_address_variable_4 + 3);
    gssserial_consolenode = 1 - v0;
    gssserial_address_variable_4 = v1;
    *(&gssserial_address_variable_4 + 1) = v2;
    *(&gssserial_address_variable_4 + 2) = v3;
    *(&gssserial_address_variable_4 + 3) = v4;
  }
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssSerialSendData(int a1, int a2, int a3, int a4, int a5)
{
  int v6; // edi
  char v7; // dl
  int v8; // esi
  int v9; // ebp
  bool v10; // eax
  __int64 v11; // rax
  bool v13; // [esp+0h] [ebp-14h]

  if (gssSendEntered)
    return 0;
  v6 = a1 + 7;
  v7 = *(_BYTE *)(a1 + 4) - gssBase;
  *(_DWORD *)(a1 + 3) = *(_DWORD *)a1;
  *(_BYTE *)(a1 + 7) = v7;
  gssSendEntered = -1;
  v8 = a2 - 7;
  v9 = 1;
  v10 = a5 != gssserial_consolenode || a5 == 21;
  v13 = v10;
  if (v10) {
    v11 = gsstxfree((8 * (a4 + v8 + 1) + 22) / 7, (8 * (a4 + v8 + 1) + 22) / 7);
    if ((int)v11 < SHIDWORD(v11))
      v9 = 0;
  }
  if (!v9) {
    gssSendEntered = 0;
    return 0;
  }
  if (v13)
    gssserialwritecoded(v6, v8);
  gssSendEntered = 0;
  return 1;
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssSerialGetHeader(_DWORD *a1, int a2, _DWORD *a3)
{
  if ((gssCommsType != 2 || gssModemOnline) && !gssHeaderEntered) {
    gssHeaderEntered = -1;
    gssSerialUpdateMessage(a1, a2, a3);
    if (gssserial_status == 3) {
      qmemcpy((char *)a1 + 7, &message_variable_1, a2 - 7);
      a1[1] = gssBase + *((unsigned __int8 *)a1 + 7);
      *a1 = 0;
      *a3 = &message[a2 - 6];
      gssHeaderEntered = 0;
      return 1;
    }
    gssHeaderEntered = 0;
  }
  return 0;
}

//-------------------------------------------------------------------------------------------------

unsigned int __fastcall gssSerialGetBlock(const void *a1, void *a2, unsigned int a3)
{
  unsigned int result; // eax

  result = a3;
  qmemcpy(a2, a1, a3);
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssSerialUpdateMessage(int a1, int a2, int a3)
{
  int v3; // esi
  int result; // eax
  signed int v5; // edx
  unsigned int v6; // ebx
  char *v7; // esi
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  char v12; // cl
  int i; // eax

  v3 = -1;
  while (2) {
    result = gssserial_status;
    switch (gssserial_status) {
      case 0:
        a2 = (unsigned __int8)i_buffer[i_read];
        if ((((_WORD)i_write - (_WORD)i_read + 2048) & 0x7FF) != 0 && ((i_write - i_read + 2048) & 0x7FF) >= a2) {
          ++i_read;
          i_read &= 0x7FFu;
          v5 = a2 - 1;
          v6 = 2048 - i_read;
          v7 = &i_buffer[i_read];
          if (2048 - i_read < v5) {
            qmemcpy(&message_variable_1, v7, v6);
            result = v5 - v6;
            qmemcpy((char *)&message_variable_1 + v6, i_buffer, v5 - v6);
            message[0] = v5;
          } else {
            result = v5;
            qmemcpy(&message_variable_1, v7, v5);
          }
          i_read += v5;
          i_read &= 0x7FFu;
          gssserial_status = 3;
        } else {
          v8 = 0;
          while (1) {
            result = gssrxused();
            if (result <= 0 || v8)
              break;
            serialrbuffer = (int)message;
            serialrbits = 7;
            v9 = gssreadchar();
            a2 = v9;
            serialrvalue = v9;
            if (v9 >= 128) {
              a2 = v9 & 0x7F;
              v10 = 1;
              serialrvalue = a2;
            } else {
              v10 = 0;
            }
            if (v10)
              v8 = -1;
          }
          if (v8) {
            gssserial_status = 1;
            continue;
          }
        }
        break;
      case 1:
        result = gsscharready();
        if (result) {
          if (gssserialrbyte(result, a2, a3)) {
            a3 = 2;
            gssserial_length = *(unsigned __int8 *)(serialrbuffer - 1);
            a2 = gssserial_length + 1;
            gssserial_status = 2;
            gssserial_getdata = gssserial_length + 1;
          } else {
            serialrbuffer = (int)message;
            serialrbits = 7;
            ++gss_errors;
          }
          continue;
        }
        break;
      case 2:
        if (gssserial_getdata > 0) {
          a3 = -1;
          a2 = 0;
          do {
            v11 = gsscharready();
            if (!v11)
              break;
            if (gssserialrbyte(v11, 0, -1)) {
              --gssserial_getdata;
            } else {
              gssserial_status = 1;
              gssserial_getdata = -1;
              serialrbuffer = (int)message;
              serialrbits = 7;
              ++gss_errors;
            }
          } while (gssserial_getdata > 0);
        }
        result = gssserial_getdata;
        if (gssserial_getdata <= 0) {
          if (gssserial_getdata == -1)
            goto LABEL_38;
          a2 = (int)message;
          a3 = gssserial_length;
          v12 = 0;
          for (i = 0; i <= gssserial_length; v12 += a3) {
            LOBYTE(a3) = *(_BYTE *)a2++;
            ++i;
          }
          if (v12 != *(_BYTE *)a2) {
            a2 = 0;
            a3 = gss_errors + 1;
            gssserial_status = 0;
            ++gss_errors;
            continue;
          }
          result = 3;
          v3 = 0;
          gssserial_status = 3;
          goto LABEL_38;
        }
        break;
      case 3:
        return result;
      default:
      LABEL_38:
        if (v3)
          continue;
        break;
    }
    return result;
  }
}

//-------------------------------------------------------------------------------------------------

int __stdcall gssSerialCompareAddress(unsigned int a1, int a2, int a3, int a4, unsigned int a5, int a6, int a7, int a8)
{
  unsigned int *v8; // ebx
  unsigned int *v9; // edx
  int v10; // ecx

  v8 = &a5;
  v9 = &a1;
  v10 = 0;
  if (a1 < a5)
    return -1;
  while (1) {
    if (*v9 > *v8)
      return 1;
    ++v8;
    ++v10;
    ++v9;
    if (v10 >= 4)
      break;
    if (*v9 < *v8)
      return -1;
  }
  return 0;
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssserialwritecoded(unsigned __int8 *a1, unsigned int a2, unsigned __int8 *a3, unsigned int a4)
{
  unsigned int i; // edx
  unsigned int j; // edx
  int result; // eax

  gssserial_accum = 1;
  gssserial_bits = 7;
  serialchk = 0;
  gssserialwbyte((unsigned __int8)(a4 + a2));
  for (i = 0; i < a2; ++i)
    gssserialwbyte(*a1++);
  for (j = 0; j < a4; ++j)
    gssserialwbyte(*a3++);
  result = gssserialwbyte((unsigned __int8)serialchk);
  if (gssserial_bits != 7) {
    gssserial_accum <<= gssserial_bits;
    return gsswritechar((unsigned __int8)gssserial_accum);
  }
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssserialwbyte(unsigned __int8 a1)
{
  int result; // eax
  char v3; // dh

  serialchk += a1;
  gssserial_accum = (gssserial_accum << gssserial_bits) | ((int)a1 >> (8 - gssserial_bits));
  gsswritechar((unsigned __int8)gssserial_accum);
  result = (int)(unsigned __int8)(a1 << gssserial_bits) >> gssserial_bits;
  v3 = result;
  if (!--gssserial_bits) {
    gssserial_accum = result;
    result = gsswritechar((unsigned __int8)result);
    gssserial_bits = 7;
    v3 = 0;
  }
  gssserial_accum = v3;
  return result;
}

//-------------------------------------------------------------------------------------------------

int gsscharready()
{
  int v0; // eax

  v0 = gssrxused();
  if (!serialrbits) {
    if (v0 > 1)
      return 1;
  LABEL_6:
    JUMPOUT(0x77859);
  }
  if (v0 <= 0)
    goto LABEL_6;
  return 1;
}

//-------------------------------------------------------------------------------------------------

int __fastcall gssserialrbyte(int a1, int a2, int a3, __int16 a4)
{
  int result; // eax
  int v5; // edx
  __int16 v6; // cx
  int v7; // ebx
  unsigned __int8 v8; // ch
  int v9; // eax
  int v10; // ebx
  int v11; // edx

  if (!serialrbits) {
    serialrbits = 7;
    a1 = gssreadchar(a1, a2, a3, a4);
    serialrvalue = a1;
    if ((a1 & 0x80u) != 0)
      return 0;
  }
  v5 = 8 - serialrbits;
  HIBYTE(v6) = serialrvalue;
  LOBYTE(v6) = 8 - serialrbits;
  v7 = gssreadchar(a1, 8 - serialrbits, a3, v6);
  serialrvalue = v7;
  v8 = HIBYTE(v6) << v6;
  if ((v7 & 0x80u) != 0)
    return 0;
  v9 = 7 - v5;
  v10 = v8 | (v7 >> (7 - v5));
  v11 = serialrbuffer + 1;
  serialrbits = v9;
  result = 1;
  *(_BYTE *)serialrbuffer = v10;
  serialrbuffer = v11;
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall gss_D32DosMemAlloc(int a1, _WORD *a2, int a3, int a4)
{
  _DWORD v5[3]; // [esp+0h] [ebp-24h] BYREF
  int v6; // [esp+Ch] [ebp-18h]
  int v7; // [esp+18h] [ebp-Ch]
  int v8; // [esp+1Ch] [ebp-8h]

  v8 = a4;
  v5[0] = 256;
  v5[1] = (unsigned int)(a1 + 15) >> 4;
  int386(49, (int)v5, (int)v5);
  if (v7)
    return 0;
  if (a2)
    *a2 = v6;
  return 16 * LOWORD(v5[0]);
}

//-------------------------------------------------------------------------------------------------

int __fastcall gss_DosFree(unsigned __int16 a1)
{
  int result; // eax
  _DWORD v2[9]; // [esp+0h] [ebp-24h] BYREF

  v2[0] = 257;
  v2[3] = a1;
  result = int386(49, (int)v2, (int)v2);
  if (v2[6])
    return printf(aErrorDeallocat);
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall gss_ser_init(int a1, int a2, int a3, int a4)
{
  _WORD *v5; // edi
  int i; // ecx
  int v8; // [esp+0h] [ebp-34h] BYREF
  unsigned int v9; // [esp+4h] [ebp-30h]
  unsigned int v10; // [esp+8h] [ebp-2Ch]
  int (*v11)(); // [esp+Ch] [ebp-28h]
  int v12; // [esp+10h] [ebp-24h]
  int v13; // [esp+14h] [ebp-20h]

  if (a1 < 1 || a1 > 4) {
    printf(aInvalidPort);
  LABEL_14:
    __atexit();
    __int23_exit();
    __int23_exit();
    __FPE_handler_exit();
    JUMPOUT(0x7A98F);
  }
  if (a1 == 1 || a1 == 3)
    gss_com_int = 12;
  else
    gss_com_int = 11;
  v8 = 516;
  LOBYTE(v9) = gss_com_int;
  int386(49, (int)&v8, (int)&v8);
  gss_orig_pm_sel = v10;
  v8 = 512;
  gss_orig_pm_off = (int)v11;
  LOBYTE(v9) = gss_com_int;
  int386(49, (int)&v8, (int)&v8);
  gss_orig_rm_seg = v10;
  gss_orig_rm_off = (__int16)v11;
  gss_rm_irq = gss_D32DosMemAlloc(4628, &gss_lowmem_seg, (int)&v8, a4);
  if (!gss_rm_irq) {
    printf(aCouldnTGetLowM);
    goto LABEL_14;
  }
  qmemcpy((void *)gss_rm_irq, gss_rmhandler, 0x200u);
  v5 = (_WORD *)(gss_rm_irq + 512);
  for (i = 2058; i; --i)
    *v5++ = 0;
  gss_pm_irq_variable_1 = __CS__;
  v8 = 517;
  v9 = (unsigned __int8)gss_com_int;
  gss_pm_irq = (int)gss_pmhandler;
  v10 = (unsigned __int16)__CS__;
  v11 = gss_pmhandler;
  int386(49, (int)&v8, (int)&v8);
  v9 = (unsigned int)gss_pmhandler >> 16;
  v13 = 512;
  v10 = (unsigned int)gss_pmhandler & 0xFFFF;
  v12 = 0;
  v8 = 1536;
  int386(49, (int)&v8, (int)&v8);
  v9 = (unsigned __int8)gss_com_int;
  v10 = (unsigned __int16)((unsigned int)gss_rm_irq >> 4);
  v8 = 513;
  v11 = (int (*)())(gss_rm_irq & 0xF);
  int386(49, (int)&v8, (int)&v8);
  return gss_com_init(a1);
}

//-------------------------------------------------------------------------------------------------

int gss_ser_uninit()
{
  int v1; // [esp+0h] [ebp-24h] BYREF
  int v2; // [esp+4h] [ebp-20h]
  int v3; // [esp+8h] [ebp-1Ch]
  int v4; // [esp+Ch] [ebp-18h]

  gss_com_uninit();
  v2 = (unsigned __int8)gss_com_int;
  v3 = (unsigned __int16)gss_orig_rm_seg;
  v1 = 513;
  v4 = (unsigned __int16)gss_orig_rm_off;
  int386(49, (int)&v1, (int)&v1);
  v2 = (unsigned __int8)gss_com_int;
  v1 = 517;
  v3 = (unsigned __int16)gss_orig_pm_sel;
  v4 = gss_orig_pm_off;
  int386(49, (int)&v1, (int)&v1);
  return gss_DosFree(gss_lowmem_seg);
}

//-------------------------------------------------------------------------------------------------

void __fastcall gssModemInit(int a1, int a2, int a3, int a4)
{
  int v4; // edx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  __int16 v8; // fps
  double v9; // st7
  _BOOL1 v10; // c0
  char v11; // c2
  _BOOL1 v12; // c3
  float v13; // [esp+8h] [ebp-10h]

  v4 = a1;
  if (gssserial_initialised) {
    while (1) {
      v5 = gssrxused(a1, v4);
      if (!v5)
        break;
      a1 = gssreadchar(v5, v4, a3, a4);
    }
    gsssendstring(v4);
    v6 = gsssendstring(serial_c_variable_8);
    v7 = clock(v6);
    v13 = (float)(unsigned int)v7;
    do {
      v7 = clock(v7);
      v9 = ((double)(unsigned int)v7 - v13) * serial_c_variable_9;
      v10 = v9 < serial_c_variable_10;
      v11 = 0;
      v12 = v9 == serial_c_variable_10;
      LOWORD(v7) = v8;
    } while (v9 < serial_c_variable_10);
  }
}

//-------------------------------------------------------------------------------------------------

void __fastcall gssModemDial(int a1, int a2)
{
  int v3; // eax
  __int16 v4; // fps
  double v5; // st7
  _BOOL1 v6; // c0
  char v7; // c2
  _BOOL1 v8; // c3
  char *v9; // eax
  int v10; // eax
  int v11; // eax
  __int16 v12; // fps
  double v13; // st7
  _BOOL1 v14; // c0
  char v15; // c2
  _BOOL1 v16; // c3
  __int64 v17; // [esp+0h] [ebp-20h]
  float v18; // [esp+8h] [ebp-18h]
  float v19; // [esp+Ch] [ebp-14h]

  if (gssserial_initialised) {
    v3 = clock(a1);
    v18 = (float)(unsigned int)v3;
    do {
      v3 = clock(v3);
      v5 = ((double)(unsigned int)v3 - v18) * serial_c_variable_13;
      v6 = v5 < serial_c_variable_14;
      v7 = 0;
      v8 = v5 == serial_c_variable_14;
      LOWORD(v3) = v4;
    } while (v5 < serial_c_variable_14);
    if (a2)
      v9 = aAtdt;
    else
      v9 = aAtdp;
    gsssendstring(v9);
    gsssendstring(a1);
    v10 = gsssendstring(serial_c_variable_8);
    v11 = clock(v10);
    v19 = (float)(unsigned int)v11;
    do {
      v17 = (unsigned int)clock(v11);
      HIWORD(v11) = 0;
      v13 = ((double)v17 - v19) * serial_c_variable_13;
      v14 = v13 < serial_c_variable_14;
      v15 = 0;
      v16 = v13 == serial_c_variable_14;
      LOWORD(v11) = v12;
    } while (v13 < serial_c_variable_14);
  }
}

//-------------------------------------------------------------------------------------------------

void gssModemHangUp()
{
  unsigned __int16 v0; // bx
  unsigned __int16 v1; // dx
  unsigned __int8 v2; // al
  int v3; // eax
  unsigned int v4; // eax
  double v5; // st7
  __int16 v6; // fps
  _BOOL1 v7; // c0
  char v8; // c2
  _BOOL1 v9; // c3
  unsigned __int8 v10; // al
  unsigned int v11; // eax
  __int16 v12; // fps
  double v13; // st7
  _BOOL1 v14; // c0
  char v15; // c2
  _BOOL1 v16; // c3
  int v17; // eax
  unsigned int v18; // eax
  __int16 v19; // fps
  double v20; // st7
  _BOOL1 v21; // c0
  char v22; // c2
  _BOOL1 v23; // c3
  int v24; // eax
  __int64 v25; // rax
  __int16 v26; // fps
  double v27; // st7
  _BOOL1 v28; // c0
  char v29; // c2
  _BOOL1 v30; // c3
  float v31; // [esp+8h] [ebp-24h]
  float v32; // [esp+Ch] [ebp-20h]
  float v33; // [esp+10h] [ebp-1Ch]
  float v34; // [esp+14h] [ebp-18h]

  if (gssserial_initialised) {
    gssModemOnline = 0;
    v0 = gss_port_address + 4;
    v1 = gss_port_address + 4;
    v2 = __inbyte(gss_port_address + 4);
    v3 = v2 & 0xFE;
    __outbyte(v1, v3);
    v4 = clock(v3);
    v31 = (float)v4;
    do {
      v4 = clock(v4);
      v5 = ((double)v4 - v31) * serial_c_variable_17;
      v7 = v5 > 1.0;
      v8 = 0;
      v9 = 1.0 == v5;
      LOWORD(v4) = v6;
    } while (v5 < 1.0);
    v10 = __inbyte(v0);
    v10 |= 1u;
    __outbyte(v0, v10);
    v11 = clock(v10);
    v32 = (float)v11;
    do {
      v11 = clock(v11);
      v13 = ((double)v11 - v32) * serial_c_variable_17;
      v14 = v13 < serial_c_variable_18;
      v15 = 0;
      v16 = v13 == serial_c_variable_18;
      LOWORD(v11) = v12;
    } while (v13 < serial_c_variable_18);
    v17 = gsssendstring(serial_c_variable_15);
    v18 = clock(v17);
    v33 = (float)v18;
    do {
      v18 = clock(v18);
      v20 = ((double)v18 - v33) * serial_c_variable_17;
      v21 = v20 < serial_c_variable_18;
      v22 = 0;
      v23 = v20 == serial_c_variable_18;
      LOWORD(v18) = v19;
    } while (v20 < serial_c_variable_18);
    v24 = gsssendstring(aAth0);
    v25 = clock(v24);
    v34 = (float)v25;
    do {
      LODWORD(v25) = clock(v25);
      v27 = ((double)(unsigned int)v25 - v34) * serial_c_variable_17;
      v28 = v27 < serial_c_variable_18;
      v29 = 0;
      v30 = v27 == serial_c_variable_18;
      LOWORD(v25) = v26;
    } while (v27 < serial_c_variable_18);
  }
}

//-------------------------------------------------------------------------------------------------

void gssModemAnswer()
{
  int v0; // eax
  unsigned int v1; // eax
  __int16 v2; // fps
  double v3; // st7
  _BOOL1 v4; // c0
  char v5; // c2
  _BOOL1 v6; // c3
  float v7; // [esp+8h] [ebp-Ch]

  if (gssserial_initialised) {
    v0 = gsssendstring(&aData[2]);
    v1 = clock(v0);
    v7 = (float)v1;
    do {
      v1 = clock(v1);
      v3 = ((double)v1 - v7) * serial_c_variable_20;
      v4 = v3 < serial_c_variable_21;
      v5 = 0;
      v6 = v3 == serial_c_variable_21;
      LOWORD(v1) = v2;
    } while (v3 < serial_c_variable_21);
  }
}

//-------------------------------------------------------------------------------------------------

int __fastcall gsssendstring(const char *a1)
{
  unsigned int i; // edx
  int v3; // ebx
  unsigned __int8 v4; // bl
  int result; // eax

  for (i = 0; ; ++i) {
    result = 0;
    if (i >= strlen(a1))
      break;
    v3 = (unsigned __int8)a1[i];
    if (v3 == 94 && i < strlen(a1) - 1) {
      v4 = a1[++i];
      v3 = v4 - 64;
    }
    gsswritechar(v3);
  }
  return result;
}

//-------------------------------------------------------------------------------------------------

int __fastcall __spoils<> gssModemCheckResponse(int result, int a2, int a3, int a4)
{
  int v4; // eax

  if (gssserial_initialised) {
    while (1) {
      v4 = gssrxused(result, a2);
      if (!v4)
        break;
      result = gssreadchar(v4, a2, gssresponsebuffer, a4);
      if (result) {
        BYTE1(result) = gssresponselen + 1;
        gssresponsebuffer[(unsigned __int8)gssresponselen] = result;
        gssresponselen = BYTE1(result);
        gssresponsebuffer[BYTE1(result)] = 0;
        while (1) {
          result = gsscheckstring(gssresponsebuffer);
          a2 = result;
          if (result != -2)
            break;
          qmemcpy(gssresponsebuffer, &gssresponsebuffer_variable_1, (unsigned __int8)gssresponselen);
          a4 = 0;
          --gssresponselen;
        }
        if (result >= 0) {
          if (result == 1)
            gssModemOnline = -1;
          gssresponselen = 0;
          return result;
        }
      }
    }
  }
  return -1;
}

//-------------------------------------------------------------------------------------------------

int __fastcall gsscheckstring(const char *a1)
{
  int v2; // ecx
  char *v3; // ebx
  int v4; // ebx
  const char *v5; // edx
  unsigned int i; // esi
  const char *v8; // [esp+0h] [ebp-24h]
  int v9; // [esp+4h] [ebp-20h]
  int v10; // [esp+8h] [ebp-1Ch]

  if (!strlen(a1))
    return -1;
  v3 = gssresponse;
  v2 = 0;
  while (strcmp(a1, v3)) {
    ++v2;
    v3 += 12;
    if (v2 >= 9) {
      v9 = 0;
      v8 = gssresponse;
      do {
        v4 = 12 * v9;
        if (strlen(a1) < strlen(v8)) {
          v5 = a1;
          v10 = -1;
          for (i = 0; i < strlen(a1); ++i) {
            if (*v5 != gssresponse[v4])
              v10 = 0;
            ++v5;
            ++v4;
          }
          if (v10)
            return -1;
        }
        v8 += 12;
        ++v9;
      } while (v9 < 9);
      return -2;
    }
  }
  return v2;
}

//-------------------------------------------------------------------------------------------------

void __fastcall gsswait250(int a1)
{
  unsigned int v1; // eax
  __int16 v2; // fps
  double v3; // st7
  _BOOL1 v4; // c0
  char v5; // c2
  _BOOL1 v6; // c3
  float v7; // [esp+8h] [ebp-Ch]

  v1 = clock(a1);
  v7 = (float)v1;
  do {
    v1 = clock(v1);
    v3 = ((double)v1 - v7) * serial_c_variable_22;
    v4 = v3 < serial_c_variable_23;
    v5 = 0;
    v6 = v3 == serial_c_variable_23;
    LOWORD(v1) = v2;
  } while (v3 < serial_c_variable_23);
}

//-------------------------------------------------------------------------------------------------

int __fastcall gss16550(int a1)
{
  unsigned __int16 v1; // dx
  unsigned __int8 v2; // al
  _DWORD v4[8]; // [esp+0h] [ebp-20h]

  v4[1] = 1016;
  v4[2] = dword_777F0[1];
  v4[3] = dword_777F0[2];
  v4[4] = dword_777F0[3];
  v1 = v4[a1] + 2;
  __outbyte(v1, 7u);
  v2 = __inbyte(v1);
  return ((v2 & 0xC0) == 0) - 1;
}

//-------------------------------------------------------------------------------------------------
#endif
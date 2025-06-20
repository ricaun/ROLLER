#include "network.h"
#include "sound.h"
#include "3d.h"
#include "func3.h"
#include "frontend.h"
#include "moving.h"
#include "car.h"
//-------------------------------------------------------------------------------------------------

int net_type = 1;           //000A6104
int net_started = 0;        //000A610C
int test_mini[2];           //001786C0
int test_multiple[16];      //001786C8
int net_players[16];        //00178718
int16 player_checks[8192];  //00178758
int player_ready[16];       //0017C858
int syncptr;                //0017C928
int syncleft;               //0017C92C
int syncnode;               //0017C930
int syncframe;              //0017C934
int received_seed;          //0017C938
int frame_number;           //0017C940
int broadcast_mode;         //0017C984
tSyncHeader in_header;      //0017C9A4
int active_nodes;           //0017C9B0
int16 wConsoleNode;         //0017C9DA

//-------------------------------------------------------------------------------------------------

int Initialise_Network(int a1)
{
  return 0; /*
  int v2; // ecx
  int v3; // esi
  int i; // ebx
  unsigned int v5; // eax
  int v6; // edx
  int result; // eax
  int v8; // eax
  int NetworkAddr; // eax
  int ConsoleNode; // eax
  int v11; // [esp+0h] [ebp-1Ch]

  v11 = 0;
  active_nodes = 0;
  net_quit = 0;
  master = -667;
  wConsoleNode = 0;
  network_on = 0;
  net_loading = 0;
  v2 = 0x4000;
  memset(copy_multiple, 0, 0x8000);
  v3 = 0;
  for (i = 0; i < 16; ++i) {
    v5 = 2 * i;
    player_ready[v3] = 0;
    v6 = v2;
    do {
      v5 += 32;
      net_players_variable_1[v5 / 2] = -1;
    } while (v5 != v2);
    v2 += 2;
    ++v3;
  }
  message_node = -1;
  message_number = -1;
  message_received = -1;
  message_sent = -1;
  result = v6 ^ v5;
  time_to_start = result;
  received_seed = 0;
  frame_number = 0;
  active_nodes = 0;
  if (net_type || !net_started) {
    result = gssCommsInitSystem(20);
    if (result)
      v11 = -1;
  }
  if (!v11) {
    I_Quit = 0;
    broadcast_mode = 0;
    writeptr = 0;
    readptr = 0;
    remove_messages(-1, 0, -1);
    if (!net_type)
      net_started = -1;
    v8 = 1;
    net_players[0] = 0;
    player_started[0] = 0;
    do {
      v8 += 5;
      test_multiple_variable_1[v8] = 0;
      non_competitors_variable_4[v8] = 0;
      p_record[v8] = 0;
      non_competitors_variable_5[v8] = 0;
      p_record_variable_1[v8] = 0;
      non_competitors_variable_6[v8] = 0;
      p_record_variable_2[v8] = 0;
      non_competitors_variable_7[v8] = 0;
      p_record_variable_3[v8] = 0;
      non_competitors_variable_8[v8] = 0;
    } while (v8 != 16);
    players_waiting = 0;
    if (!network_champ_on)
      Players_Cars[player1_car] = -1;
    my_age = 0;
    NetworkAddr = gssCommsGetNetworkAddr(&address, 0);
    ConsoleNode = gssCommsGetConsoleNode(NetworkAddr);
    network_on = 1;
    if (a1 || network_slot < 0)
      broadcast_mode = -456;
    else
      broadcast_mode = -1;
    tick_on = -1;
    while (broadcast_mode)
      ;
    result = gssCommsSortNodes(ConsoleNode);
    received_records = 1;
    switch_sets = 0;
    switch_same = 0;
    switch_types = 0;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void close_network()
{
  int iNode; // edx
  int i; // edx

  network_slot = -1;
  if (network_on) {
    tick_on = 0;
    //while (gssCommsPostListen())
    //  ;
    iNode = 0;
    wConsoleNode = 0;// gssCommsNetAddrToNode((int)&address);
    while (iNode < wConsoleNode) {
      //if (gssCommsDeleteNode(0)) {
      //  printf("FAILED TO DELETE NODE a (%d)!!!\n", iNode);
      //  doexit();
      //}
      //gssCommsSortNodes();
      ++iNode;
    }
    for (i = wConsoleNode + 1; i < network_on; ++i) {
      //if (gssCommsDeleteNode(1)) {
      //  printf("FAILED TO DELETE NODE b (%d)!!!\n", i);
      //  doexit();
      //}
      //gssCommsSortNodes();
    }
    //gssCommsGetActiveNodes();
    wConsoleNode = 0;// gssCommsNetAddrToNode((int)&address);
    if (exiting)
      goto LABEL_18;
  } else if ((net_started || net_type) && exiting) {
  LABEL_18:
    ;
    //gssCommsSetType(1);
    //gssCommsUnInitSystem();
    //gssCommsSetType(0);
    //gssCommsUnInitSystem();
  }

  for (int i = 0; i < 16; ++i)
      net_players[i] = -667;

  if (network_on && !frontend_on) {
    Players_Cars[0] = my_car;
    name_copy(player_names[0], my_name);
    manual_control[0] = my_control;
    player_invul[0] = my_invul;
  }
  if (network_on)
    player_type = 0;
  network_on = 0;
  player1_car = 0;
  active_nodes = 0;
  wConsoleNode = 0;
  received_seed = 0;
  frame_number = 0;
  time_to_start = 0;
  if (game_type != 1 && replaytype != 2)
    network_champ_on = 0;
  broadcast_mode = 0;
  clear_network_game();
  //if (net_type)
  //  gssCommsUnInitSystem();
}

//-------------------------------------------------------------------------------------------------

int send_net_error()
{
  return 0; /*
  int result; // eax
  int i; // esi

  if (network_on) {
    p_header_variable_2 = wConsoleNode;
    p_header_variable_1 = 1751933804;
    result = wConsoleNode;
    if (wConsoleNode == master) {
      for (i = 0; i < network_on; ++i) {
        result = wConsoleNode;
        if (i != wConsoleNode)
          result = gssCommsSendData(i);
      }
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int send_game_error(int result)
{
  return 0; /*
  int i; // esi

  if (network_on) {
    p_header_variable_2 = wConsoleNode;
    p_header_variable_1 = 1751933806;
    network_mistake = -1;
    if (wConsoleNode == master) {
      for (i = 0; i < network_on; ++i) {
        if (i != wConsoleNode) {
          result = gssCommsSendData(i);
          if (!result)
            i = network_on;
        }
      }
      if (result)
        network_error = 666;
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int send_network_sync_error()
{
  return 0; /*
  int result; // eax
  int i; // esi

  if (network_on) {
    p_header_variable_2 = wConsoleNode;
    p_header_variable_1 = 1751933805;
    result = wConsoleNode;
    if (wConsoleNode == master) {
      for (i = 0; i < network_on; ++i) {
        result = wConsoleNode;
        if (i != wConsoleNode)
          result = gssCommsSendData(i);
      }
    } else {
      return gssCommsSendData(master);
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int send_resync(int result)
{
  return 0; /*
  if (network_on) {
    resync = result;
    p_header_variable_2 = wConsoleNode;
    p_header_variable_1 = 1751933808;
    return gssCommsSendData(master);
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int send_nocd_error()
{
  return 0; /*
  int result; // eax
  int i; // esi

  if (network_on) {
    p_header_variable_2 = wConsoleNode;
    p_header_variable_1 = 1751933807;
    result = wConsoleNode;
    if (wConsoleNode == master) {
      for (i = 0; i < network_on; ++i) {
        result = wConsoleNode;
        if (i != wConsoleNode)
          result = gssCommsSendData(i);
      }
    } else {
      return gssCommsSendData(master);
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void send_quit()
{/*
  int i; // esi

  if (network_on) {
    p_header_variable_2 = wConsoleNode;
    p_header_variable_1 = 1751933796;
    if (wConsoleNode == master) {
      for (i = 0; i < network_on; ++i) {
        if (i != wConsoleNode) {
          while (!gssCommsSendData(i))
            ;
        }
      }
      net_quit = -1;
    } else {
      while (!gssCommsSendData(master))
        ;
    }
  }*/
}

//-------------------------------------------------------------------------------------------------

void send_ready()
{/*
  int v0; // edi
  int v1; // eax

  if (network_on) {
    p_header_variable_2 = wConsoleNode;
    if (localCD)
      p_header_variable_1 = 1751933799;
    else
      p_header_variable_1 = 1751933807;
    if (wConsoleNode != master || player_ready[master]) {
      do {
        _disable();
        v1 = gssCommsSendData(master);
        _enable();
      } while (!v1);
    } else {
      v0 = active_nodes + 1;
      player_ready[master] = -1;
      active_nodes = v0;
    }
  }*/
}

//-------------------------------------------------------------------------------------------------

int send_record_to_master(int result)
{
  return 0; /*
  double v1; // st7
  int *v2; // edx
  int v3; // eax
  char v4; // cl
  int v5; // [esp+0h] [ebp-20h]

  v5 = result;
  if (network_on) {
    p_header_variable_2 = wConsoleNode;
    v1 = RecordLaps[result];
    p_header_variable_1 = 1751933803;
    v2 = p_record;
    v3 = 9 * result;
    *(float *)p_record = v1;
    do {
      v2 = (int *)((char *)v2 + 1);
      v4 = RecordNames[v3++];
      *((_BYTE *)v2 + 3) = v4;
    } while (v3 != 9 * v5 + 9);
    HIWORD(p_record[3]) = RecordCars[v5];
    do
      result = gssCommsSendData(master);
    while (!result);
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int send_record_to_slaves(int result)
{
  return 0; /*
  double v1; // st7
  int *v2; // edx
  int v3; // eax
  char v4; // cl
  int v5; // [esp+0h] [ebp-24h]
  int i; // [esp+8h] [ebp-1Ch]

  v5 = result;
  if (network_on) {
    p_header_variable_2 = wConsoleNode;
    v1 = RecordLaps[result];
    p_header_variable_1 = 1751933803;
    v2 = p_record;
    v3 = 9 * result;
    *(float *)p_record = v1;
    do {
      v2 = (int *)((char *)v2 + 1);
      v4 = RecordNames[v3++];
      *((_BYTE *)v2 + 3) = v4;
    } while (v3 != 9 * v5 + 9);
    HIWORD(p_record[3]) = RecordCars[v5];
    result = 0;
    for (i = 0; i < network_on; ++i) {
      result = wConsoleNode;
      if (wConsoleNode != i) {
        do
          result = gssCommsSendData(i);
        while (!result);
      }
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

char send_mes(char *a1, int a2)
{
  return 0; /*
  char *v2; // esi
  char *v3; // edi
  char *v4; // esi
  char v5; // al
  char v6; // al
  int v7; // esi
  int v8; // edi

  v2 = a1;
  if (network_on) {
    a1 = &aSlowcoach[14 * (_DWORD)a1];
    if (*a1) {
      message_sent = (int)v2;
      v3 = (char *)&p_data;
      v4 = a1;
      do {
        v5 = *v4;
        *v3 = *v4;
        if (!v5)
          break;
        v6 = v4[1];
        v4 += 2;
        v3[1] = v6;
        v3 += 2;
      } while (v6);
      LOBYTE(a1) = wConsoleNode;
      p_header_variable_1 = 1751933795;
      p_header_variable_2 = wConsoleNode;
      if (a2 == -1) {
        v7 = 0;
        if (network_on > 0) {
          v8 = 0;
          do {
            LOBYTE(a1) = wConsoleNode;
            if (v7 != wConsoleNode && net_players[v8]) {
              do
                a1 = (char *)gssCommsSendData(v7);
              while (!a1);
            }
            ++v8;
            ++v7;
          } while (v7 < network_on);
        }
      } else {
        do
          a1 = (char *)gssCommsSendData(a2);
        while (!a1);
      }
    } else {
      message_sent = 4;
    }
  }
  return (char)a1;*/
}

//-------------------------------------------------------------------------------------------------

int send_seed(int result)
{
  return 0; /*
  int v1; // edi
  int v2; // esi

  v1 = result;
  if (network_on) {
    test_seed = result;
    v2 = 0;
    p_header_variable_2 = wConsoleNode;
    for (p_header_variable_1 = 1751933800; v2 < network_on; ++v2) {
      if (v2 != wConsoleNode) {
        while (!gssCommsSendData(v2))
          ;
      }
    }
    result = srand(v1);
    random_seed = v1;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int send_single(int result)
{
  return 0; /*
  if (network_on) {
    p_header_variable_2 = player1_car;
    slave_data = result;
    p_header_variable_1 = 1751933797;
    if (read_check == write_check || read_check < 0)
      *((_WORD *)&slave_data + 2) = -512;
    else
      slave_data_variable_2 = ((player_checks[16 * read_check + player1_car] & 0x7F) << 9) | read_check & 0x1FF;
    gssCommsSendData(master);
    player_checks[16 * read_check + player1_car] = -1;
    result = read_check;
    if (read_check != write_check && read_check >= 0) {
      result = ((_WORD)read_check + 1) & 0x1FF;
      read_check = result;
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int send_pause()
{
  return 0; /*
  int result; // eax

  if (network_on) {
    do
      result = gssCommsSendData(master);
    while (!result);
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int send_slot()
{
  return 0; /*
  int result; // eax

  if (network_on) {
    do
      result = gssCommsSendData(21);
    while (!result);
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void transmitpausetoslaves()
{/*
  int v0; // esi
  int v1; // edi

  if (network_on) {
    v0 = 0;
    if (network_on > 0) {
      v1 = 0;
      do {
        if (v0 != master && net_players[v1]) {
          while (!gssCommsSendData(v0))
            ;
        }
        ++v1;
        ++v0;
      } while (v0 < network_on);
    }
  }*/
}

//-------------------------------------------------------------------------------------------------

void send_multiple()
{/*
  int v0; // eax
  int *v1; // esi
  int v2; // edi
  int v3; // esi
  int v4; // eax
  int v5; // edi
  int v6; // edx
  _DWORD *v7; // esi
  int i; // eax
  int v9; // edx
  int v10; // edi
  int v11; // edi

  if (network_on) {
    p_header_variable_2 = wConsoleNode;
    p_header_variable_1 = 1751933798;
    p_header_variable_3 = frame_number;
    if (net_type) {
      v6 = -1;
      if (memcmp(
        (const char *)&copy_multiple[16 * (((_WORD)writeptr - 1) & 0x1FF) + player_to_car[0]],
        (const char *)&copy_multiple[16 * writeptr + player_to_car[0]],
        4)) {
        v6 = 0;
      }
      if (memcmp(
        (const char *)&copy_multiple[16 * (((_WORD)writeptr - 1) & 0x1FF) + player_to_car_variable_1],
        (const char *)&copy_multiple[16 * writeptr + player_to_car_variable_1],
        4)) {
        v6 = 0;
      }
      if (!frame_number)
        v6 = 0;
      if (v6) {
        *((_DWORD *)&p_header + 1) = 1751933812;
        v3 = abs32(start_multiple);
        v4 = -1;
        if (v3 >= 0) {
          v11 = v3;
          do {
            if (!v4)
              break;
            if (v3 == master || !net_players[v11])
              v4 = -1;
            else
              v4 = gssCommsSendData(v3);
            if (v4) {
              --v11;
              --v3;
            }
          } while (v3 >= 0);
        }
      } else {
        v7 = &test_mini;
        for (i = 0; i < 2; ++i) {
          ++v7;
          v9 = copy_multiple[16 * writeptr + player_to_car[i]];
          *(v7 - 1) = v9;
        }
        v3 = abs32(start_multiple);
        v4 = -1;
        if (v3 >= 0) {
          v10 = v3;
          do {
            if (!v4)
              break;
            if (v3 == master || !net_players[v10])
              v4 = -1;
            else
              v4 = gssCommsSendData(v3);
            if (v4) {
              --v10;
              --v3;
            }
          } while (v3 >= 0);
        }
      }
    } else {
      v0 = 0;
      if (numcars > 0) {
        v1 = (int *)&test_multiple;
        do {
          v2 = copy_multiple[16 * writeptr + v0++];
          *v1++ = v2;
        } while (v0 < numcars);
      }
      v3 = abs32(start_multiple);
      v4 = -1;
      if (v3 >= 0) {
        v5 = v3;
        do {
          if (!v4)
            break;
          v4 = v3 == master || !net_players[v5] ? -1 : gssCommsSendData(v3);
          if (v4) {
            --v5;
            --v3;
          }
        } while (v3 >= 0);
      }
    }
    if (v4) {
      start_multiple = network_on - 1;
      ++frame_number;
    } else {
      start_multiple = -v3;
    }
  }*/
}

//-------------------------------------------------------------------------------------------------

void receive_multiple()
{/*
  int v0; // edx
  int v1; // ebx
  int i; // eax
  int v3; // edx
  int v4; // eax
  int v5; // ebx
  int *v6; // edx
  int *v7; // esi
  int *v8; // edx
  int v9; // eax
  int v10; // edx
  int *v11; // ebx
  int v12; // eax
  int v13; // edx
  int v14; // eax
  int j; // eax
  int v16; // ecx
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // ebx
  int v21; // eax
  int v22; // edx
  int v23; // eax
  char v24[12]; // [esp+0h] [ebp-60h] BYREF
  int v25; // [esp+Ch] [ebp-54h]
  int v26; // [esp+10h] [ebp-50h]
  int v27; // [esp+14h] [ebp-4Ch]
  int v28; // [esp+18h] [ebp-48h]
  int v29; // [esp+1Ch] [ebp-44h]
  int v30; // [esp+20h] [ebp-40h]
  _BYTE v31[4]; // [esp+24h] [ebp-3Ch]
  _BYTE v32[16]; // [esp+28h] [ebp-38h] BYREF
  int v33; // [esp+38h] [ebp-28h] BYREF
  int v34; // [esp+3Ch] [ebp-24h]
  int v35; // [esp+40h] [ebp-20h] BYREF
  int *v36; // [esp+44h] [ebp-1Ch]

  if (network_on && !net_quit) {
    v36 = &test_seed;
    while (1) {
      v0 = 12;
      v1 = (int)&v33;
      if (!gssCommsGetHeader(&in_header, 12, &v33))
        break;
      i = *((_DWORD *)&in_header + 1) - 1751933795;
      switch (*((_DWORD *)&in_header + 1)) {
        case 0x686C6363:
          v0 = (int)v32;
          v1 = 14;
          gssCommsGetBlock(v33, v32, 14);
          message_received = *((unsigned __int8 *)&in_header + 8);
          for (i = 0; i < 14; p_data_variable_8[i] = v0) {
            i += 7;
            p_data_variable_2[i] = v31[i - 3];
            p_data_variable_3[i] = v31[i - 2];
            p_data_variable_4[i] = v31[i - 1];
            p_data_variable_5[i] = v31[i];
            p_data_variable_6[i] = v31[i + 1];
            p_data_variable_7[i] = v31[i + 2];
            LOBYTE(v0) = v31[i + 3];
          }
          goto LABEL_54;
        case 0x686C6364:
          net_quit = -1;
          gssCommsPostListen(i, 12, &v33);
          continue;
        case 0x686C6366:
          if (net_type) {
            v13 = 0;
            if (network_on > 0) {
              v14 = 0;
              do {
                ++v14;
                ++v13;
                address_variable_1[v14] = -1;
              } while (v13 < network_on);
            }
            active_nodes = network_on;
            net_loading = 0;
            gssCommsGetBlock(v33, &test_mini, 8);
            v0 = (int)&test_mini;
            for (j = 0; j < 2; ++j) {
              v0 += 4;
              v16 = (writeptr << 6) + 4 * player_to_car[j];
              v1 = *(_DWORD *)(v0 - 4);
              *(int *)((char *)copy_multiple + v16) = v1;
            }
          } else {
            v10 = 0;
            v11 = &copy_multiple[16 * writeptr];
            if (network_on > 0) {
              v12 = 0;
              do {
                ++v12;
                ++v10;
                address_variable_1[v12] = -1;
              } while (v10 < network_on);
            }
            active_nodes = network_on;
            net_loading = 0;
            v0 = (int)v11;
            v1 = 64;
            gssCommsGetBlock(v33, v0, 64);
          }
          network_timeout = frames;
          ++ticks_received;
          i = *((unsigned __int16 *)&in_header + 5);
          if ((unsigned __int16)i == frame_number) {
            ++frame_number;
            v17 = ((_WORD)writeptr + 1) & 0x1FF;
            writeptr = v17;
            next_resync = -1;
            gssCommsPostListen(v17, v0, v1);
            continue;
          }
          if (i <= frame_number)
            goto LABEL_54;
          ++lost_message;
          gssCommsPostListen(i, v0, v1);
          if (*((unsigned __int16 *)&in_header + 5) - frame_number > 500) {
            v18 = send_network_sync_error();
            network_sync_error = -1;
            gssCommsPostListen(v18, v0, v1);
            continue;
          }
          i = frames;
          if (frames <= next_resync)
            goto LABEL_54;
          if (gssCommsGetType())
            gssclrrx();
          goto LABEL_17;
        case 0x686C6368:
          gssCommsGetBlock(v33, &test_seed, 4);
          srand(*v36);
          random_seed = *v36;
          received_seed = -1;
          gssCommsPostListen(random_seed, &test_seed, 4);
          continue;
        case 0x686C6369:
          v0 = (int)&v35;
          v1 = 4;
          gssCommsGetBlock(v33, &v35, 4);
          if (paused != v35 && v35)
            dostopsamps = -1;
          i = v35;
          paused = v35;
          if (!v35)
            goto LABEL_54;
          v19 = *((unsigned __int8 *)&in_header + 8);
          pauser = v19;
          gssCommsPostListen(v19, &v35, 4);
          continue;
        case 0x686C636A:
          v20 = 40;
          gssCommsGetBlock(v33, v24, 40);
          v21 = v25;
          Players_Cars[*((unsigned __int8 *)&in_header + 8)] = v25;
          check_cars(v21);
          name_copy((int)&player_names[9 * *((unsigned __int8 *)&in_header + 8)], v24);
          TrackLoad = v26;
          game_type = v27;
          competitors = v30;
          level = v29;
          damage_level = v31[0] & 0xF;
          if ((v31[0] & 0x40) != 0) {
            player_invul[*((unsigned __int8 *)&in_header + 8)] = -1;
          } else {
            v20 = 0;
            player_invul[*((unsigned __int8 *)&in_header + 8)] = 0;
          }
          v22 = *((unsigned __int8 *)&in_header + 8);
          v23 = v28;
          manual_control[v22] = v28;
          gssCommsPostListen(v23, v22 * 4, v20);
          continue;
        case 0x686C636C:
          network_error = 999;
          gssCommsPostListen(i, 12, &v33);
          continue;
        case 0x686C636D:
          goto LABEL_13;
        case 0x686C636E:
          network_error = 666;
          gssCommsPostListen(i, 12, &v33);
          continue;
        case 0x686C636F:
          cd_error = -1;
          gssCommsPostListen(i, 12, &v33);
          continue;
        case 0x686C6372:
          v3 = *((unsigned __int8 *)&in_header + 8);
          v4 = *((unsigned __int16 *)&in_header + 5);
          load_times[v3] = v4;
          gssCommsPostListen(v4, v3, &v33);
          continue;
        case 0x686C6374:
          i = *((unsigned __int16 *)&in_header + 5);
          if ((unsigned __int16)i == frame_number) {
            v5 = player_to_car[0];
            v34 = player_to_car_variable_1;
            v6 = &copy_multiple[16 * (((_WORD)writeptr - 1) & 0x1FF)];
            qmemcpy(&copy_multiple[16 * writeptr + player_to_car[0]], &v6[player_to_car[0]], sizeof(int));
            v7 = &v6[v34];
            v8 = &copy_multiple[16 * writeptr];
            qmemcpy(&v8[v34], v7, sizeof(int));
            network_timeout = frames;
            ++ticks_received;
            ++frame_number;
            v9 = ((_WORD)writeptr + 1) & 0x1FF;
            writeptr = v9;
            next_resync = -1;
            gssCommsPostListen(v9, v8, v5);
            continue;
          }
          if (i <= frame_number)
            goto LABEL_54;
          ++lost_message;
          gssCommsPostListen(i, 12, &v33);
          if (*((unsigned __int16 *)&in_header + 5) - frame_number <= 500) {
            i = frames;
            if (frames <= next_resync) {
            LABEL_54:
              gssCommsPostListen(i, v0, v1);
            } else {
              if (gssCommsGetType())
                gssclrrx();
            LABEL_17:
              ++sync_errors;
              send_resync(frame_number);
              next_resync = frames + 16;
              gssCommsPostListen(frames + 16, v0, v1);
            }
          } else {
            i = send_network_sync_error();
          LABEL_13:
            network_sync_error = -1;
            gssCommsPostListen(i, 12, &v33);
          }
          break;
        default:
          ++duff_message;
          goto LABEL_54;
      }
    }
  }*/
}

//-------------------------------------------------------------------------------------------------

void receive_all_singles()
{/*
  int v0; // ebx
  int Block; // eax
  int v2; // edx
  unsigned __int16 v3; // dx
  int v4; // eax
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // ebx
  int v14; // eax
  int v15; // edx
  int v16; // eax
  int v17; // eax
  _DWORD v18[58]; // [esp+0h] [ebp-140h] BYREF
  char v19[12]; // [esp+E8h] [ebp-58h] BYREF
  int v20; // [esp+F4h] [ebp-4Ch]
  int v21; // [esp+F8h] [ebp-48h]
  int v22; // [esp+FCh] [ebp-44h]
  int v23; // [esp+100h] [ebp-40h]
  int v24; // [esp+104h] [ebp-3Ch]
  int v25; // [esp+108h] [ebp-38h]
  _BYTE v26[4]; // [esp+10Ch] [ebp-34h]
  _BYTE v27[16]; // [esp+110h] [ebp-30h] BYREF
  int v28; // [esp+120h] [ebp-20h] BYREF
  _DWORD v29[7]; // [esp+124h] [ebp-1Ch] BYREF

  if (network_on) {
    while (1) {
      v0 = (int)&v28;
      if (!gssCommsGetHeader(&in_header, 12, &v28))
        break;
      Block = 4 * *((unsigned __int8 *)&in_header + 8);
      v2 = *(int *)((char *)car_to_player + Block);
      if (net_players[v2]) {
        v2 = active_nodes + 1;
        switch (*((_DWORD *)&in_header + 1)) {
          case 0x686C6361:
            v2 = (int)v18;
            v0 = 232;
            Block = gssCommsGetBlock(v28, v18, 232);
            if (v18[17] != -456)
              goto LABEL_32;
            v4 = send_slot();
            gssCommsPostListen(v4, v18, 232);
            break;
          case 0x686C6363:
            v2 = (int)v27;
            v0 = 14;
            gssCommsGetBlock(v28, v27, 14);
            message_received = *((unsigned __int8 *)&in_header + 8);
            for (Block = 0; Block < 14; p_data_variable_8[Block] = v2) {
              Block += 7;
              p_data_variable_2[Block] = v26[Block - 3];
              p_data_variable_3[Block] = v26[Block - 2];
              p_data_variable_4[Block] = v26[Block - 1];
              p_data_variable_5[Block] = v26[Block];
              p_data_variable_6[Block] = v26[Block + 1];
              p_data_variable_7[Block] = v26[Block + 2];
              LOBYTE(v2) = v26[Block + 3];
            }
            goto LABEL_32;
          case 0x686C6364:
            gssCommsPostListen(Block, v2, &v28);
            send_quit();
            gssCommsPostListen(v7, v2, &v28);
            break;
          case 0x686C6365:
            gssCommsGetBlock(v28, &slave_data, 6);
            LOWORD(copy_multiple[16 * writeptr + *((unsigned __int8 *)&in_header + 8)]) = slave_data;
            HIWORD(copy_multiple[16 * writeptr + *((unsigned __int8 *)&in_header + 8)]) = slave_data_variable_1;
            v5 = car_to_player[*((unsigned __int8 *)&in_header + 8)];
            v6 = frames;
            net_time[v5] = frames;
            gssCommsPostListen(v5, v6, 6);
            break;
          case 0x686C6367:
            if (player_ready[*((unsigned __int8 *)&in_header + 8)])
              goto LABEL_32;
            ++active_nodes;
            *(int *)((char *)player_ready + Block) = -1;
            netCD = -1;
            gssCommsPostListen(Block, v2, -1);
            break;
          case 0x686C6369:
            slave_pause = -1;
            v9 = *((unsigned __int8 *)&in_header + 8);
            pauser = v9;
            gssCommsPostListen(v9, v2, &v28);
            break;
          case 0x686C636A:
            gssCommsGetBlock(v28, v19, 40);
            v10 = v20;
            Players_Cars[*((unsigned __int8 *)&in_header + 8)] = v20;
            check_cars(v10);
            name_copy((int)&player_names[9 * *((unsigned __int8 *)&in_header + 8)], v19);
            TrackLoad = v21;
            game_type = v22;
            competitors = v25;
            level = v24;
            damage_level = v26[0] & 0xF;
            if ((v26[0] & 0x40) != 0)
              player_invul[*((unsigned __int8 *)&in_header + 8)] = -1;
            else
              player_invul[*((unsigned __int8 *)&in_header + 8)] = 0;
            v11 = *((unsigned __int8 *)&in_header + 8);
            v12 = v23;
            manual_control[v11] = v23;
            gssCommsPostListen(v12, v11, 40);
            break;
          case 0x686C636D:
            gssCommsPostListen(Block, v2, &v28);
            v8 = send_network_sync_error();
            network_sync_error = -1;
            gssCommsPostListen(v8, v2, &v28);
            break;
          case 0x686C636F:
            if (player_ready[*((unsigned __int8 *)&in_header + 8)])
              goto LABEL_32;
            ++active_nodes;
            *(int *)((char *)player_ready + Block) = -1;
            gssCommsPostListen(Block, v2, -1);
            break;
          case 0x686C6370:
            ++lost_message;
            gssCommsPostListen(Block, v2, &v28);
            v13 = 4;
            syncnode = *((unsigned __int8 *)&in_header + 8);
            gssCommsGetBlock(v28, v29, 4);
            syncframe = v29[0];
            if (frame_number - v29[0] <= 500) {
              if (gssCommsGetType())
                gssclrtx();
              v15 = syncframe;
              syncleft = frame_number - syncframe;
              v16 = syncframe & 0x1FF;
              syncptr = v16;
              if (check_set && syncleft > 7) {
                v15 = -1;
                v13 = 0x4000;
                v16 = memset(player_checks, -1, sizeof(player_checks));
                check_set = 0;
              }
              v17 = do_sync_stuff(v16, v15, v13, &in_header);
              gssCommsPostListen(v17, v15, v13);
            } else {
              gssCommsPostListen(frame_number - v29[0], v29, 4);
              v14 = send_network_sync_error();
              network_sync_error = -1;
              gssCommsPostListen(v14, -1, 4);
            }
            break;
          case 0x686C6372:
            v3 = *((_WORD *)&in_header + 5);
            load_times[*((unsigned __int8 *)&in_header + 8)] = v3;
            gssCommsPostListen(Block, v3, &v28);
            break;
          default:
            ++duff_message;
            goto LABEL_32;
        }
      } else {
      LABEL_32:
        gssCommsPostListen(Block, v2, v0);
      }
    }
  }*/
}

//-------------------------------------------------------------------------------------------------

void do_sync_stuff(void)
{
  int *pCopy;
  uint8 byConsoleNode = (uint8)wConsoleNode;
  uint16 unFrame = syncframe;

  if (net_type == 0) {
    // Full sync: send all cars to all nodes
    while (syncleft > 0) {
      in_header.uiId = 0x686C6366;
      in_header.byConsoleNode = byConsoleNode;
      in_header.unFrameId = unFrame;

      // Pack data for all cars
      pCopy = test_multiple;
      for (int i = 0; i < numcars; i++)
        *pCopy++ = copy_multiple[syncptr][player_to_car[i]];

      // Send 64 bytes (16 * 4-byte ints)
      //if (!gssCommsSendData(&in_header, 12, syncnode, test_multiple, 64))
      //  break;

      syncptr = (syncptr + 1) & 0x1FF; // wrap around 512
      syncframe++;
      syncleft--;
    }
  } else {
    // Minimal sync: send only player-to-car pairs
    while (syncleft > 0) {
      in_header.uiId = 0x686C6366;
      in_header.byConsoleNode = byConsoleNode;
      in_header.unFrameId = unFrame;

      // Pack data for player-to-car mappings
      pCopy = test_mini;
      for (int i = 0; i < 2; i++) {
        *pCopy++ = copy_multiple[syncptr][player_to_car[i]];
      }

      // Send 8 bytes (2 * 4-byte ints)
      //if (!gssCommsSendData(&in_header, 12, syncnode, test_mini, 8))
      //  break;

      syncptr = (syncptr + 1) & 0x1FF;
      syncframe++;
      syncleft--;
    }
  }
}

//-------------------------------------------------------------------------------------------------

int TransmitInit(int a1, int a2, int a3, int a4)
{
  return 0; /*
  int result; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  char *v8; // ecx
  char *v9; // ebx
  _BYTE v10[12]; // [esp+10h] [ebp-F8h] BYREF
  int v11; // [esp+1Ch] [ebp-ECh]
  int v12; // [esp+20h] [ebp-E8h]
  int v13; // [esp+24h] [ebp-E4h]
  int v14; // [esp+28h] [ebp-E0h]
  int v15; // [esp+2Ch] [ebp-DCh]
  int v16; // [esp+30h] [ebp-D8h]
  int v17; // [esp+34h] [ebp-D4h]
  int v18; // [esp+38h] [ebp-D0h]
  int v19; // [esp+3Ch] [ebp-CCh]
  int v20; // [esp+40h] [ebp-C8h]
  int v21; // [esp+44h] [ebp-C4h]
  int v22; // [esp+48h] [ebp-C0h]
  bool v23; // [esp+4Ch] [ebp-BCh]
  int v24; // [esp+50h] [ebp-B8h]
  int v25; // [esp+54h] [ebp-B4h]
  char v26; // [esp+58h] [ebp-B0h] BYREF
  int v27; // [esp+ECh] [ebp-1Ch]
  char v28; // [esp+F0h] [ebp-18h]
  int v29; // [esp+100h] [ebp-8h]

  v29 = a4;
  result = -1;
  if (network_on) {
    v28 = player1_car;
    v27 = 1751933793;
    v14 = TrackLoad;
    name_copy((int)v10, &player_names[9 * wConsoleNode]);
    if (broadcast_mode == -9999)
      v5 = car_request - 1;
    else
      v5 = Players_Cars[wConsoleNode];
    v13 = v5;
    if (net_type)
      ++my_age;
    v12 = my_age;
    v11 = network_on;
    if (game_type <= 2)
      v6 = game_type;
    else
      v6 = last_type;
    v15 = v6;
    v18 = competitors;
    v16 = manual_control[wConsoleNode];
    v7 = level;
    if ((cheat_mode & 2) != 0)
      BYTE1(v7) = BYTE1(level) | 1;
    if (player_invul[player1_car])
      BYTE1(v7) |= 2u;
    if ((cheat_mode & 0x200) != 0)
      BYTE1(v7) |= 4u;
    if ((cheat_mode & 0x400) != 0)
      BYTE1(v7) |= 8u;
    if ((cheat_mode & 0x800) != 0)
      BYTE1(v7) |= 0x10u;
    if ((cheat_mode & 0x1000) != 0)
      BYTE1(v7) |= 0x20u;
    if ((cheat_mode & 0x2000) != 0)
      BYTE1(v7) |= 0x40u;
    if ((cheat_mode & 0x4000) != 0)
      BYTE1(v7) |= 0x80u;
    if ((cheat_mode & 0x8000) != 0)
      v7 |= (unsigned int)cstart_branch_1;
    v17 = v7;
    v19 = damage_level;
    v20 = StartPressed;
    if (time_to_start == 45)
      time_to_start = 0;
    v21 = time_to_start;
    v22 = false_starts;
    v23 = ((unsigned int)cstart_branch_1 & textures_off) != 0;
    v24 = network_champ_on;
    v8 = &v26;
    v9 = default_names;
    v25 = network_slot;
    do {
      name_copy((int)v8, v9);
      v9 += 9;
      v8 += 9;
    } while (v9 != &default_names[144]);
    return gssCommsSendData(21);
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int StartNode(int a1)
{
  return 0; /*
  int NetworkAddr; // eax
  int result; // eax

  my_age = 0;
  NetworkAddr = gssCommsGetNetworkAddr(&address, a1);
  result = gssCommsGetConsoleNode(NetworkAddr);
  network_on = 1;
  if (a1 || network_slot < 0)
    broadcast_mode = -456;
  else
    broadcast_mode = -1;
  tick_on = -1;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int CheckNewNodes()
{
  return 0; /*
  int v0; // ebx
  int result; // eax
  __int64 v2; // rax
  int v3; // eax
  int v4; // edx
  __int64 v5; // rax
  char *v6; // eax
  int v7; // ebp
  int v8; // edi
  int v9; // esi
  char *v10; // edi
  char *v11; // eax
  _DWORD *v12; // edi
  char *v13; // eax
  __int64 v14; // rax
  int v15; // ebp
  int i; // edi
  int v17; // esi
  _DWORD *v18; // edi
  unsigned int v19; // eax
  int v20; // ebp
  char *v21; // ebx
  char *v22; // esi
  int v23; // ecx
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int j; // eax
  int v28; // ebp
  __int64 v29; // rax
  __int64 found; // rax
  int v31; // ecx
  int v32; // edx
  int v33; // edx
  int v34; // ebx
  int v35; // eax
  int v36; // edx
  char *v37; // esi
  __int16 v38; // fps
  _BOOL1 v39; // c0
  char v40; // c2
  _BOOL1 v41; // c3
  int v42; // edx
  int v43; // [esp+0h] [ebp-18Ch] BYREF
  int v44; // [esp+4h] [ebp-188h]
  int v45; // [esp+8h] [ebp-184h]
  int v46; // [esp+Ch] [ebp-180h]
  char v47[16]; // [esp+10h] [ebp-17Ch] BYREF
  int v48; // [esp+20h] [ebp-16Ch]
  int v49; // [esp+24h] [ebp-168h]
  int v50; // [esp+28h] [ebp-164h]
  int v51; // [esp+2Ch] [ebp-160h]
  int v52; // [esp+30h] [ebp-15Ch]
  int v53; // [esp+34h] [ebp-158h]
  int v54; // [esp+38h] [ebp-154h]
  int v55; // [esp+3Ch] [ebp-150h]
  int v56; // [esp+40h] [ebp-14Ch]
  unsigned int v57; // [esp+44h] [ebp-148h]
  int v58; // [esp+48h] [ebp-144h]
  int v59; // [esp+4Ch] [ebp-140h]
  int v60; // [esp+50h] [ebp-13Ch]
  int v61; // [esp+54h] [ebp-138h]
  _BYTE v62[144]; // [esp+58h] [ebp-134h] BYREF
  _BYTE v63[32]; // [esp+E8h] [ebp-A4h] BYREF
  char v64[12]; // [esp+108h] [ebp-84h] BYREF
  int v65; // [esp+114h] [ebp-78h]
  char v66[12]; // [esp+118h] [ebp-74h] BYREF
  int v67; // [esp+124h] [ebp-68h]
  int v68; // [esp+128h] [ebp-64h]
  int v69; // [esp+12Ch] [ebp-60h]
  int v70; // [esp+130h] [ebp-5Ch]
  int v71; // [esp+134h] [ebp-58h]
  int v72; // [esp+138h] [ebp-54h]
  int v73; // [esp+13Ch] [ebp-50h]
  float v74[3]; // [esp+140h] [ebp-4Ch] BYREF
  __int16 v75; // [esp+14Eh] [ebp-3Eh]
  char v76[4]; // [esp+150h] [ebp-3Ch] BYREF
  int v77; // [esp+154h] [ebp-38h]
  unsigned __int8 v78; // [esp+158h] [ebp-34h]
  unsigned __int16 v79; // [esp+15Ah] [ebp-32h]
  int v80; // [esp+15Ch] [ebp-30h] BYREF
  int v81; // [esp+160h] [ebp-2Ch]
  int *v82; // [esp+164h] [ebp-28h]
  char *v83; // [esp+168h] [ebp-24h]
  char *v84; // [esp+16Ch] [ebp-20h]
  int v85; // [esp+170h] [ebp-1Ch]

  v82 = &test_seed;
  while (1) {
    v0 = (int)&v80;
    result = gssCommsGetHeader(v76, 12, &v80);
    if (!result)
      return result;
    LODWORD(v2) = v77 - 1751933793;
    HIDWORD(v2) = active_nodes + 1;
    switch (v77) {
      case 1751933793:
        v0 = 232;
        v60 = 0;
        v61 = 0;
        v2 = __PAIR64__(&v43, gssCommsGetBlock(v80, &v43, 232));
        if (network_slot >= 0) {
          if (v61 < 0 && !I_Quit) {
            v14 = send_broadcast(-457);
            test = HIDWORD(v14);
            gssCommsPostListen(v14, HIDWORD(v14), 232);
            continue;
          }
          test = 4;
          v15 = 0;
          for (i = 0; i < network_on; ++i) {
            HIDWORD(v2) = &v43;
            v0 = 0;
            LODWORD(v2) = (char *)&address + 16 * i;
            v17 = v2 + 16;
            do {
              if (*(_BYTE *)v2 != *(_BYTE *)HIDWORD(v2))
                v0 = -1;
              LODWORD(v2) = v2 + 1;
              ++HIDWORD(v2);
            } while ((_DWORD)v2 != v17);
            if (!v0) {
              v15 = i + 10;
              i = network_on + 6;
            }
          }
          if (!v15) {
            test = 5;
            if (time_to_start == -1)
              goto LABEL_163;
            LODWORD(v2) = v60;
            if (v60 != network_champ_on)
              goto LABEL_163;
            LODWORD(v2) = v61;
            if (v61 != network_slot)
              goto LABEL_163;
            if (network_on >= 16)
              goto LABEL_163;
            if (I_Quit)
              goto LABEL_163;
            test = 20;
            LODWORD(v2) = gssCommsAddNode(&v43);
            if ((unsigned int)v2 > 1)
              goto LABEL_163;
            test = 6;
            gssCommsSortNodes(v2);
            v18 = (_DWORD *)((char *)&address + 16 * network_on);
            *v18++ = v43;
            *v18++ = v44;
            *v18 = v45;
            v18[1] = v46;
            v19 = v57;
            switch_types = 0;
            if (v57 == -667)
              v19 = 0;
            if (v19) {
              LODWORD(v2) = time_to_start;
              if (time_to_start != -666)
                goto LABEL_163;
            LABEL_65:
              LODWORD(v2) = reset_network(-1);
              gssCommsPostListen(v2, HIDWORD(v2), v0);
              continue;
            }
            test = 7;
            name_copy((int)&player_names[9 * network_on], v47);
            Players_Cars[network_on] = v49;
            manual_control[network_on] = v52;
            player_started[network_on] = v56;
            HIDWORD(v2) = network_on;
            v20 = CheckNames(&player_names[9 * network_on], network_on);
            check_cars(v20);
            if (my_age < v48) {
              v21 = v62;
              v22 = default_names;
              do {
                name_copy((int)v22, v21);
                v21 += 9;
                v22 += 9;
              } while (v21 != v63);
              my_age = v48;
              TrackLoad = v50;
              game_type = v51;
              if (v51 == 1)
                Race = ((_BYTE)TrackLoad - 1) & 7;
              else
                network_champ_on = 0;
              competitors = v54;
              level = v53;
              v0 = v53;
              if ((v53 & 0x100) != 0) {
                v23 = cheat_mode;
                LOBYTE(v23) = cheat_mode | 2;
                cheat_mode = v23;
              }
              player_invul[network_on] = ((level & 0x200) == 0) - 1;
              if ((level & 0x400) != 0) {
                v24 = cheat_mode;
                BYTE1(v24) = BYTE1(cheat_mode) | 2;
                cheat_mode = v24;
              }
              if ((level & 0x800) != 0) {
                v0 = cheat_mode;
                BYTE1(v0) = BYTE1(cheat_mode) | 4;
                cheat_mode = v0;
              }
              if ((level & 0x1000) != 0) {
                if ((level & 0x4000) != 0) {
                  if ((cheat_mode & 0x2000) == 0) {
                    v0 = cheat_mode;
                    BYTE1(v0) = BYTE1(cheat_mode) | 0x28;
                    cheat_mode = v0;
                    release_ticktimer();
                    goto LABEL_84;
                  }
                } else if ((cheat_mode & 0x800) == 0) {
                  v25 = cheat_mode;
                  BYTE1(v25) = BYTE1(cheat_mode) | 8;
                  cheat_mode = v25;
                  release_ticktimer();
                LABEL_84:
                  claim_ticktimer();
                }
              }
              if ((level & 0x2000) != 0)
                cheat_mode |= 0x1000u;
              if (((unsigned int)cstart_branch_1 & level) != 0) {
                v26 = cheat_mode;
                BYTE1(v26) = BYTE1(cheat_mode) | 0x80;
                cheat_mode = v26;
              }
              HIDWORD(v2) = level;
              if ((level & 0x8000) != 0 && switch_same >= 0)
                switch_same = v49 + 666;
              level &= 0xFu;
              damage_level = v55;
              false_starts = v58;
              if (v59) {
                if (((unsigned int)cstart_branch_1 & textures_off) == 0) {
                  textures_off |= (unsigned int)cstart_branch_1;
                  goto LABEL_97;
                }
              } else if (((unsigned int)cstart_branch_1 & textures_off) != 0) {
                textures_off &= ~0x10000u;
              LABEL_97:
                switch_sets = -1;
              }
            }
            players_waiting = 0;
            for (j = 0; j <= network_on; ++j) {
              if (player_started[j])
                ++players_waiting;
            }
            ++my_age;
            LODWORD(v2) = network_on++;
            if (!I_Quit)
              v2 = send_broadcast(-1);
            if (!v20)
              goto LABEL_163;
            cheat_mode = 0;
            gssCommsPostListen(v2, HIDWORD(v2), 0);
            continue;
          }
          test = 8;
          v28 = v15 - 10;
          ++my_age;
          if (v28 <= 0)
            goto LABEL_163;
          test = 9;
          HIDWORD(v2) = v57;
          if (!v57) {
            test = 10;
            name_copy((int)&player_names[9 * v28], v47);
            Players_Cars[v28] = v49;
            v31 = CheckNames(&player_names[9 * v28], v28);
            check_cars(v31);
            TrackLoad = v50;
            if (v51 < 3) {
              if (v51 == game_type)
                game_type = v51;
              else
                switch_types = v51 + 1;
            }
            competitors = v54;
            level = v53;
            if ((v53 & 0x100) != 0) {
              v32 = cheat_mode;
              LOBYTE(v32) = cheat_mode | 2;
              cheat_mode = v32;
            }
            player_invul[v28] = ((level & 0x200) == 0) - 1;
            if ((level & 0x400) != 0)
              cheat_mode |= 0x200u;
            if ((level & 0x800) != 0) {
              v33 = cheat_mode;
              BYTE1(v33) = BYTE1(cheat_mode) | 4;
              cheat_mode = v33;
            }
            if ((level & 0x1000) != 0) {
              if ((level & 0x4000) != 0) {
                if ((cheat_mode & 0x2000) == 0) {
                  v34 = cheat_mode;
                  BYTE1(v34) = BYTE1(cheat_mode) | 0x28;
                  cheat_mode = v34;
                  release_ticktimer();
                  goto LABEL_131;
                }
              } else if ((cheat_mode & 0x800) == 0) {
                v35 = cheat_mode;
                BYTE1(v35) = BYTE1(cheat_mode) | 8;
                cheat_mode = v35;
                release_ticktimer();
              LABEL_131:
                claim_ticktimer();
              }
            }
            if ((level & 0x2000) != 0)
              cheat_mode |= 0x1000u;
            if (((unsigned int)cstart_branch_1 & level) != 0) {
              v36 = cheat_mode;
              BYTE1(v36) = BYTE1(cheat_mode) | 0x80;
              cheat_mode = v36;
            }
            if ((level & 0x8000) != 0 && switch_same >= 0)
              switch_same = v49 + 666;
            level &= 0xFu;
            damage_level = v55;
            v0 = (int)v62;
            v37 = default_names;
            do {
              HIDWORD(v2) = v0;
              name_copy((int)v37, (char *)v0);
              v0 += 9;
              v37 += 9;
            } while ((_BYTE *)v0 != v63);
            false_starts = v58;
            if (v59) {
              if (((unsigned int)cstart_branch_1 & textures_off) == 0) {
                textures_off |= (unsigned int)cstart_branch_1;
                goto LABEL_146;
              }
            } else if (((unsigned int)cstart_branch_1 & textures_off) != 0) {
              textures_off &= ~0x10000u;
            LABEL_146:
              switch_sets = -1;
            }
            manual_control[v28] = v52;
            player_started[v28] = v56;
            players_waiting = 0;
            LODWORD(v2) = 0;
            if (network_on > 0) {
              do {
                if (player_started[(_DWORD)v2])
                  ++players_waiting;
                LODWORD(v2) = v2 + 1;
              } while ((int)v2 < network_on);
            }
            if (!v31)
              goto LABEL_163;
            cheat_mode = 0;
            gssCommsPostListen(v2, HIDWORD(v2), v0);
            continue;
          }
          if (v57 < 0xFFFFFD66) {
            if (v57 == -667) {
              v29 = send_broadcast(-1);
              gssCommsPostListen(v29, HIDWORD(v29), v0);
              continue;
            }
          } else {
            if (v57 <= 0xFFFFFD66)
              goto LABEL_65;
            if (v57 == -457)
              goto LABEL_163;
          }
          time_to_start = -1;
          found = FoundNodes(v2);
          gssCommsPostListen(found, HIDWORD(found), v0);
        } else {
          v0 = 1;
          test = 1;
          if (v61 < 0)
            goto LABEL_163;
          test = 2;
          LODWORD(v2) = v61 - 1;
          v83 = (char *)(v61 - 1);
          if (v61 - 1 < 0 || (int)v2 > 4)
            goto LABEL_163;
          LODWORD(v2) = v57;
          if (v57 < 0xFFFFFD66)
            goto LABEL_25;
          if (v57 <= 0xFFFFFD66) {
            v5 = send_broadcast(-456);
            LODWORD(v5) = v83;
            gamers_playing[(_DWORD)v83] = 0;
            gssCommsPostListen(v5, HIDWORD(v5), 1);
            continue;
          }
          if (v57 == -1) {
            v6 = v83;
            gamers_playing[(_DWORD)v83] = -2;
            gssCommsPostListen(v6, &v43, 1);
          } else {
          LABEL_25:
            if (v60) {
              gamers_playing[(_DWORD)v83] = -2;
              gssCommsPostListen(v2, &v43, 1);
            } else {
              v85 = 0;
              v7 = gamers_playing[(_DWORD)v83];
              if (v7 < 0) {
                v7 = 0;
                gamers_playing[(_DWORD)v83] = 0;
              }
              v8 = 0;
              if (v7 > 0) {
                v84 = (char *)&gamers_address + 256 * (_DWORD)v83;
                v81 = v7 + 678;
                do {
                  HIDWORD(v2) = &v43;
                  v0 = 0;
                  LODWORD(v2) = &v84[16 * v8];
                  v9 = v2 + 16;
                  do {
                    if (*(_BYTE *)v2 != *(_BYTE *)HIDWORD(v2))
                      v0 = -1;
                    LODWORD(v2) = v2 + 1;
                    ++HIDWORD(v2);
                  } while ((_DWORD)v2 != v9);
                  if (!v0) {
                    v85 = v8 + 678;
                    v8 = v81;
                  }
                  ++v8;
                } while (v8 < v7);
              }
              if (v60)
                goto LABEL_163;
              v10 = v83;
              v11 = (char *)&gamers_names + 144 * (_DWORD)v83;
              if (v85) {
                v13 = name_copy((int)&v11[9 * v85 - 6102], v47);
              } else {
                name_copy((int)&v11[9 * v7], v47);
                v12 = (_DWORD *)((char *)&gamers_address + 256 * (_DWORD)v10 + 16 * v7);
                v13 = v83;
                *v12++ = v43;
                *v12++ = v44;
                *v12 = v45;
                v12[1] = v46;
                ++gamers_playing[(_DWORD)v13];
              }
              gssCommsPostListen(v13, v47, v0);
            }
          }
        }
        break;
      case 1751933796:
        net_quit = -1;
        gssCommsPostListen(v2, HIDWORD(v2), &v80);
        continue;
      case 1751933799:
        LODWORD(v2) = 4 * v78;
        if (*(int *)((char *)player_ready + v2))
          goto LABEL_163;
        ++active_nodes;
        player_ready[v78] = -1;
        netCD = -1;
        gssCommsPostListen(v2, HIDWORD(v2), &v80);
        continue;
      case 1751933800:
        gssCommsGetBlock(v80, &test_seed, 4);
        srand(*v82);
        random_seed = *v82;
        received_seed = -1;
        gssCommsPostListen(random_seed, &test_seed, 4);
        continue;
      case 1751933802:
        v0 = 40;
        gssCommsGetBlock(v80, v66, 40);
        v42 = v78;
        Players_Cars[v78] = v67;
        name_copy((int)&player_names[9 * v42], v66);
        TrackLoad = v68;
        game_type = v69;
        competitors = v72;
        level = v71;
        damage_level = v73 & 0xF;
        if ((v73 & 0x40) != 0)
          player_invul[v78] = -1;
        else
          player_invul[v78] = 0;
        HIDWORD(v2) = v78;
        LODWORD(v2) = v70;
        manual_control[v78] = v70;
        goto LABEL_163;
      case 1751933803:
        ++received_records;
        HIDWORD(v2) = v74;
        v0 = 16;
        gssCommsGetBlock(v80, v74, 16);
        WORD1(v2) = HIWORD(TrackLoad);
        v39 = v74[0] < (double)RecordLaps[TrackLoad];
        v40 = 0;
        v41 = v74[0] == RecordLaps[TrackLoad];
        LOWORD(v2) = v38;
        if (v74[0] < (double)RecordLaps[TrackLoad]) {
          RecordLaps[TrackLoad] = v74[0];
          RecordCars[TrackLoad] = v75;
          LODWORD(v2) = 0;
          do {
            LODWORD(v2) = v2 + 1;
            HIDWORD(v2) = 9 * TrackLoad;
            LOBYTE(v0) = *((_BYTE *)v74 + v2 + 3);
            *((_BYTE *)&fudge_wait + 9 * TrackLoad + v2 + 3) = v0;
          } while ((int)v2 < 9);
        }
        goto LABEL_163;
      case 1751933807:
        LODWORD(v2) = 4 * v78;
        if (*(int *)((char *)player_ready + v2))
          goto LABEL_163;
        ++active_nodes;
        player_ready[v78] = -1;
        gssCommsPostListen(v2, HIDWORD(v2), &v80);
        continue;
      case 1751933809:
        LODWORD(v2) = v78;
        gamers_address_variable_1[v78] = -2;
        gssCommsPostListen(v2, HIDWORD(v2), &v80);
        continue;
      case 1751933810:
        v3 = v78;
        v4 = v79;
        load_times[v78] = v79;
        gssCommsPostListen(v3, v4, &v80);
        continue;
      case 1751933811:
        v0 = 48;
        gssCommsGetBlock(v80, v63, 48);
        v2 = gssCommsNetAddrToNode(&address);
        if (HIDWORD(v2) != (_DWORD)v2) {
          LODWORD(v2) = v65;
          if (v65 == network_slot) {
            rec_status = 36;
            HIDWORD(v2) = v64;
            name_copy((int)&rec_mes_name, v64);
            LODWORD(v2) = 0;
            do {
              LODWORD(v2) = v2 + 1;
              BYTE4(v2) = v62[v2 + 143];
              *((_BYTE *)&LoadCarTextures_variable_1 + v2) = BYTE4(v2);
            } while ((int)v2 < 32);
          }
        }
        goto LABEL_163;
      default:
      LABEL_163:
        gssCommsPostListen(v2, HIDWORD(v2), v0);
        continue;
    }
  }*/
}

//-------------------------------------------------------------------------------------------------

int FoundNodes(int result)
{
  return 0; /*
  int v1; // eax
  __int16 ConsoleNode; // ax
  int v3; // ecx
  char *v4; // edx
  int v5; // edx
  int v6; // edx

  if (master) {
    v1 = gssCommsSortNodes(result);
    network_on = gssCommsGetActiveNodes(v1);
    ConsoleNode = gssCommsGetConsoleNode(network_on);
    wConsoleNode = ConsoleNode;
    master = 0;
    start_multiple = network_on - 1;
    v3 = Players_Cars[player1_car];
    manual_control[ConsoleNode] = manual_control[player1_car];
    v4 = &player_names[9 * player1_car];
    Players_Cars[ConsoleNode] = v3;
    name_copy((int)&player_names[9 * ConsoleNode], v4);
    result = wConsoleNode;
    v5 = player_invul[player1_car];
    player1_car = wConsoleNode;
    player_invul[wConsoleNode] = v5;
    v6 = 0;
    if (network_on > 0) {
      result = 0;
      do {
        result += 4;
        ++v6;
        *(int *)((char *)p_record_variable_3 + result) = -1;
      } while (v6 < network_on);
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void SendPlayerInfo()
{/*
  int v0; // ecx
  _BYTE v1[12]; // [esp+0h] [ebp-44h] BYREF
  int v2; // [esp+Ch] [ebp-38h]
  int v3; // [esp+10h] [ebp-34h]
  int v4; // [esp+14h] [ebp-30h]
  int v5; // [esp+18h] [ebp-2Ch]
  int v6; // [esp+1Ch] [ebp-28h]
  int v7; // [esp+20h] [ebp-24h]
  int v8; // [esp+24h] [ebp-20h]
  int i; // [esp+28h] [ebp-1Ch]

  if (network_on) {
    name_copy((int)v1, &player_names[9 * player1_car]);
    v2 = Players_Cars[player1_car];
    v3 = TrackLoad;
    v4 = game_type;
    v7 = competitors;
    v6 = level;
    v0 = player_invul[player1_car];
    v8 = damage_level;
    if (v0)
      LOBYTE(v8) = v8 | 0x40;
    v5 = manual_control[player1_car];
    *((_BYTE *)&p_header + 8) = wConsoleNode;
    *((_DWORD *)&p_header + 1) = 1751933802;
    for (i = 0; i < network_on; ++i) {
      if (wConsoleNode != i) {
        while (!gssCommsSendData(i))
          ;
      }
    }
  }*/
}

//-------------------------------------------------------------------------------------------------

int prepare_net_message(int result, int a2)
{
  return 0; /*
  message_node = result;
  message_number = a2;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void SendAMessage(int a1, int a2, int a3, int a4)
{/*
  int i; // eax
  _BYTE v5[4]; // [esp+0h] [ebp-50h]
  int v6; // [esp+4h] [ebp-4Ch]
  _BYTE v7[12]; // [esp+28h] [ebp-28h] BYREF
  int v8; // [esp+34h] [ebp-1Ch]
  int v9; // [esp+3Ch] [ebp-14h]
  char v10; // [esp+40h] [ebp-10h]
  int v11; // [esp+44h] [ebp-Ch]
  int v12; // [esp+48h] [ebp-8h]

  v12 = a4;
  v11 = a2;
  if (!broadcast_mode && send_message_to >= 0) {
    v10 = gssCommsNetAddrToNode(&address);
    v9 = 1751933811;
    name_copy((int)v7, &player_names[9 * player1_car]);
    for (i = 0; i < 32; *((_BYTE *)v7 + i + 31) = rec_mes_buf_variable_8[i]) {
      i += 8;
      v5[i] = rec_mes_buf_variable_1[i];
      v5[i + 1] = rec_mes_buf_variable_2[i];
      v5[i + 2] = rec_mes_buf_variable_3[i];
      v5[i + 3] = rec_mes_buf_variable_4[i];
      *((_BYTE *)v7 + i + 28) = rec_mes_buf_variable_5[i];
      *((_BYTE *)v7 + i + 29) = rec_mes_buf_variable_6[i];
      *((_BYTE *)v7 + i + 30) = rec_mes_buf_variable_7[i];
    }
    v8 = network_slot;
    if (send_message_to)
      v6 = gssCommsNetAddrToNode((char *)&address + 16 * send_message_to);
    else
      v6 = 21;
    if (gssCommsSendData(v6))
      send_status = 18;
    else
      send_status = -18;
    send_message_to = -1;
  }*/
}

//-------------------------------------------------------------------------------------------------

void BroadcastNews(int a1, int a2, int a3, int a4)
{/*
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int j; // eax
  int v8; // eax
  int v9; // eax
  int i; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax

  if (!broadcast_mode)
    return;
  if ((unsigned int)broadcast_mode < 0xFFFFFD63) {
    if ((unsigned int)broadcast_mode < 0xFFFFF562) {
      if ((unsigned int)broadcast_mode < 0xFFFFD8F1) {
      LABEL_81:
        v15 = -1;
        if (network_on)
          v15 = TransmitInit(-1, a2, a3, a4);
        if (v15) {
          check_cars(v15);
          broadcast_mode = 0;
        }
        return;
      }
      if ((unsigned int)broadcast_mode <= 0xFFFFD8F1) {
        if (total_wins_variable_1[car_request] < 2) {
          v12 = -1;
          if (network_on)
            v12 = TransmitInit(-1, a2, a3, a4);
          if (!v12)
            return;
          car_request = -car_request;
          check_cars(v12);
        } else {
          car_request = 0;
        }
        broadcast_mode = 0;
        return;
      }
      if (broadcast_mode != -3567)
        goto LABEL_81;
      if (wConsoleNode != master)
        send_record_to_master(TrackLoad);
    } else {
      if ((unsigned int)broadcast_mode <= 0xFFFFF562) {
        send_record_to_slaves(TrackLoad);
        send_seed(random_seed);
        broadcast_mode = 0;
        return;
      }
      if ((unsigned int)broadcast_mode < 0xFFFFFD61)
        goto LABEL_81;
      if ((unsigned int)broadcast_mode <= 0xFFFFFD61) {
        if (master) {
          v11 = -1;
          time_to_start = -1;
          if (network_on)
            v11 = TransmitInit(-1, a2, a3, a4);
          if (!v11) {
            time_to_start = 0;
            return;
          }
          FoundNodes(v11);
        }
        broadcast_mode = 0;
      } else {
        StartPressed = 0;
        v9 = -1;
        if (network_on)
          v9 = TransmitInit(-1, 0, a3, a4);
        if (v9) {
          player_started[0] = 0;
          players_waiting = 0;
          for (i = 0; i < network_on; ++i) {
            if (player_started[i])
              ++players_waiting;
          }
          broadcast_mode = 0;
        }
      }
    }
  } else if ((unsigned int)broadcast_mode <= 0xFFFFFD63) {
    v8 = -1;
    if (network_on)
      v8 = TransmitInit(-1, a2, a3, a4);
    if (v8) {
      waste = CheckNames(&player_names[9 * player1_car], player1_car);
      broadcast_mode = 0;
    }
  } else if ((unsigned int)broadcast_mode < 0xFFFFFD66) {
    if ((unsigned int)broadcast_mode <= 0xFFFFFD64) {
      StartPressed = -1;
      v6 = -1;
      if (network_on)
        v6 = TransmitInit(-1, -1, a3, a4);
      if (v6) {
        player_started[0] = -1;
        players_waiting = 0;
        for (j = 0; j < network_on; ++j) {
          if (player_started[j])
            ++players_waiting;
        }
        broadcast_mode = 0;
      }
    } else {
      time_to_start = -667;
      v5 = -1;
      if (network_on)
        v5 = TransmitInit(-1, a2, a3, a4);
      time_to_start = 0;
      if (v5)
        broadcast_mode = 0;
    }
  } else if ((unsigned int)broadcast_mode <= 0xFFFFFD66) {
    time_to_start = -666;
    v4 = -1;
    if (network_on)
      v4 = TransmitInit(-1, a2, a3, a4);
    time_to_start = 0;
    if (v4) {
      I_Quit = -1;
      broadcast_mode = 0;
    }
  } else {
    if ((unsigned int)broadcast_mode < 0xFFFFFE38) {
      if (broadcast_mode == -457) {
        a2 = time_to_start;
        time_to_start = -457;
        v14 = -1;
        if (network_on)
          v14 = TransmitInit(-1, a2, a3, a4);
        if (v14)
          broadcast_mode = 0;
        time_to_start = a2;
      }
      goto LABEL_81;
    }
    if ((unsigned int)broadcast_mode <= 0xFFFFFE38) {
      time_to_start = -456;
      _STOSD(gamers_playing, 0, a3, 4);
      v13 = -1;
      if (network_on)
        v13 = TransmitInit(-1, 0, a3, 4);
      if (v13)
        broadcast_mode = 0;
      time_to_start = 0;
    } else {
      if (broadcast_mode != -314)
        goto LABEL_81;
      FoundNodes(-314);
      SendPlayerInfo();
      if (wConsoleNode != master)
        send_record_to_master(TrackLoad);
      broadcast_mode = 0;
    }
  }*/
}

//-------------------------------------------------------------------------------------------------

int remove_messages(int Header, int a2, void*a3, int a4)
{
  return 0; /*
  int v4; // ecx
  _DWORD v6[4]; // [esp-Ch] [ebp-10h] BYREF

  v6[2] = a4;
  v4 = Header;
  do {
    gssCommsPostListen(Header, a2, a3);
    a2 = 12;
    a3 = v6;
    Header = gssCommsGetHeader(&in_header, 12, v6);
  } while (Header);
  if (v4) {
    do
      Header = gssCommsPostListen(Header, 12, v6);
    while (Header);
  }
  return clear_network_game(Header);*/
}

//-------------------------------------------------------------------------------------------------

int reset_network(int a1)
{
  return 0; /*
  __int64 v2; // rax
  int i; // edx
  int v4; // eax
  int v5; // eax
  int NetworkAddr; // eax
  __int64 v7; // rax
  int result; // eax

  gamers_playing[0] = 0;
  gamers_playing_variable_1 = 0;
  gamers_playing_variable_2 = 0;
  gamers_playing_variable_3 = 0;
  v2 = gssCommsNetAddrToNode(&address);
  wConsoleNode = v2;
  while (SHIDWORD(v2) < wConsoleNode) {
    LODWORD(v2) = gssCommsDeleteNode(0);
    if ((_DWORD)v2) {
      printf(aFailedToDelete_1);
      doexit();
    }
    gssCommsSortNodes(v2);
    ++HIDWORD(v2);
  }
  for (i = wConsoleNode + 1; i < network_on; ++i) {
    v4 = gssCommsDeleteNode(1);
    if (v4) {
      printf(aFailedToDelete_2);
      doexit();
    }
    gssCommsSortNodes(v4);
  }
  player_started[0] = 0;
  v5 = 1;
  net_players[0] = 0;
  do {
    v5 += 5;
    non_competitors_variable_4[v5] = 0;
    test_multiple_variable_1[v5] = 0;
    non_competitors_variable_5[v5] = 0;
    p_record[v5] = 0;
    non_competitors_variable_6[v5] = 0;
    p_record_variable_1[v5] = 0;
    non_competitors_variable_7[v5] = 0;
    p_record_variable_2[v5] = 0;
    non_competitors_variable_8[v5] = 0;
    p_record_variable_3[v5] = 0;
  } while (v5 != 16);
  player1_car = 0;
  received_seed = 0;
  frame_number = 0;
  time_to_start = 0;
  broadcast_mode = 0;
  players_waiting = 0;
  active_nodes = 0;
  net_quit = 0;
  master = -667;
  wConsoleNode = 0;
  I_Quit = 0;
  my_age = 0;
  NetworkAddr = gssCommsGetNetworkAddr(&address, 0);
  LODWORD(v7) = gssCommsGetConsoleNode(NetworkAddr);
  network_on = 1;
  if (network_slot >= 0)
    broadcast_mode = -1;
  else
    broadcast_mode = -456;
  tick_on = -1;
  if (a1) {
    v7 = send_broadcast(broadcast_mode);
    broadcast_mode = HIDWORD(v7);
  }
  gssCommsSortNodes(v7);
  received_records = 1;
  switch_sets = 0;
  switch_types = 0;
  result = network_on;
  players = network_on;
  message_received = -1;
  message_sent = -1;
  if (StartPressed) {
    player_started[0] = -1;
    players_waiting = 1;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void clear_network_game()
{
  // for (int iPlayer = 0; iPlayer < 16; ++iPlayer) {
  //   player_ready[iPlayer] = 0;
  //   // Start at offset = iPlayer * 2 and step by 32
  //   for (int iOffset = iPlayer * 2; iOffset < 0x4000 / 2; iOffset += 16)  // step is 32 bytes = 16 shorts
  //   {
  //     player_checks[iOffset] = -1;
  //   }
  // }
  // memset(copy_multiple, 0, sizeof(copy_multiple));
}

//-------------------------------------------------------------------------------------------------

int reset_net_wait()
{
  return 0; /*
  int result; // eax

  result = 2;
  player_started_variable_1 = 0;
  do {
    result += 7;
    non_competitors_variable_2[result] = 0;
    non_competitors_variable_3[result] = 0;
    non_competitors_variable_4[result] = 0;
    non_competitors_variable_5[result] = 0;
    non_competitors_variable_6[result] = 0;
    non_competitors_variable_7[result] = 0;
    non_competitors_variable_8[result] = 0;
  } while (result != 16);
  time_to_start = 0;
  players_waiting = 0;
  return result * 4;*/
}

//-------------------------------------------------------------------------------------------------

unsigned int send_broadcast(unsigned int result, int a2, int a3, int a4)
{
  return 0; /*
  int v4; // edx
  int v5; // edx

  if (result < 0xFFFFFE38) {
    if (result == -457) {
      v5 = time_to_start;
      time_to_start = -457;
      do {
        result = -1;
        if (network_on)
          result = TransmitInit(-1, v5, a3, a4);
      } while (!result);
      time_to_start = v5;
    }
  } else if (result <= 0xFFFFFE38) {
    v4 = time_to_start;
    time_to_start = -456;
    do {
      result = -1;
      if (network_on)
        result = TransmitInit(-1, v4, a3, a4);
    } while (!result);
    time_to_start = v4;
  } else if (result == -1) {
    do {
      result = -1;
      if (network_on)
        result = TransmitInit(-1, 0, a3, a4);
    } while (!result);
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int send_here(int result)
{
  return 0; /*
  int i; // esi

  if (network_on) {
    if (result == master) {
      for (i = 0; i < network_on; ++i) {
        if (i != master)
          result = gssCommsSendData(i);
      }
    } else {
      return gssCommsSendData(master);
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

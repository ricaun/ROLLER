#ifndef _ROLLER_NETWORK_H
#define _ROLLER_NETWORK_H
//-------------------------------------------------------------------------------------------------
#include "types.h"
//-------------------------------------------------------------------------------------------------

typedef struct
{
  uint32 uiUnk1;
  uint32 uiId;
  uint8 byConsoleNode;
  uint16 unFrameId;
} tSyncHeader;

//-------------------------------------------------------------------------------------------------

typedef struct {
  int32 address[4];
  char szPlayerName[9];
  //padding byte
  //padding byte
  //padding byte
  int32 iNetworkOn;
  int32 iMyAge;
  int32 iCarIdx;
  int32 iTrackLoad;
  int32 iGameType;
  int32 iManualControl;
  int32 iLevelFlags;
  int32 iCompetitors;
  int32 iDamageLevel;
  int32 iStartPressed;
  int32 iTimeToStart;
  int32 iFalseStart;
  int32 iTextureMode;
  int32 iNetworkChampOn;
  int32 iNetworkSlot;
  char default_names[16][9];
  tSyncHeader header;
} tTransmitInitPacket;

//-------------------------------------------------------------------------------------------------

typedef struct
{
  float fRecordLap;
  char szRecordName[9];
  //padding byte
  uint16 unRecordCar;
} tRecordPacket;

//-------------------------------------------------------------------------------------------------

extern int net_type;
extern int net_started;
extern int test_mini[2];
extern int test_multiple[16];
extern tRecordPacket p_record;
extern int net_players[16];
extern int16 player_checks[8192];
extern int address[64];
extern int player_ready[16];
extern int syncptr;
extern int syncleft;
extern int syncnode;
extern int syncframe;
extern int received_seed;
extern int frame_number;
extern tSyncHeader p_header;
extern int my_age;
extern int broadcast_mode;
extern int master;
extern tSyncHeader in_header;
extern int active_nodes;
extern int16 wConsoleNode;

//-------------------------------------------------------------------------------------------------

int Initialise_Network(int a1);
void close_network();
int send_net_error();
int send_game_error(int result);
int send_network_sync_error();
int send_resync(int result);
int send_nocd_error();
void send_quit();
void send_ready();
void send_record_to_master(int iRecordIdx);
int send_record_to_slaves(int result);
char send_mes(char *a1, int a2);
int send_seed(int result);
int send_single(int result);
int send_pause();
int send_slot();
void transmitpausetoslaves();
void send_multiple();
void receive_multiple();
void receive_all_singles();
void do_sync_stuff();
int TransmitInit();
int StartNode(int a1);
int CheckNewNodes();
int FoundNodes(int result);
void SendPlayerInfo();
int prepare_net_message(int result, int a2);
void SendAMessage(int a1, int a2, int a3, int a4);
void BroadcastNews(int a1, int a2, int a3, int a4);
int remove_messages(int Header, int a2, void *a3, int a4);
int reset_network(int a1);
void clear_network_game();
int reset_net_wait();
unsigned int send_broadcast(unsigned int result, int a2, int a3, int a4);
int send_here(int result);

//-------------------------------------------------------------------------------------------------
#endif
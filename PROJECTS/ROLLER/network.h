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

extern int net_type;
extern int net_started;
extern int test_mini[2];
extern int test_multiple[16];
extern int net_players[16];
extern int16 player_checks[8192];
extern int player_ready[16];
extern int syncptr;
extern int syncleft;
extern int syncnode;
extern int syncframe;
extern int received_seed;
extern int frame_number;
extern int broadcast_mode;
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
int send_record_to_master(int result);
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
int TransmitInit(int a1, int a2, int a3, int a4);
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
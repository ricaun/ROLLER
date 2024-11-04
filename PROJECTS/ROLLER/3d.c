int __cdecl main(int argc, const char **argv, const char **envp)
{
  int v3; // eax
  char **v4; // edx
  int v5; // ecx
  int inited; // eax
  int v7; // eax
  int v8; // eax
  int v9; // edi
  int v10; // ecx
  char *v11; // eax
  char *v12; // eax
  int v13; // eax
  int v14; // edx
  int v15; // eax
  int v16; // ebx
  int v17; // edx
  int v18; // ecx
  int v19; // eax
  int v20; // edx
  int v21; // eax
  int i; // ebx
  int restarted; // eax
  int v24; // ebx
  int result; // eax

  v5 = v3;
  gssCommsSetCommandBase(1751933793);
  oldmode = readmode();
  blankpal(oldmode, 0, (int)v4, v5);
  SVGA_ON = 0;
  inited = init_screen();
  blankpal(inited, 0, (int)v4, v5);
  SVGA_ON = -1;
  v7 = init_screen();
  v8 = blankpal(v7, 0, (int)v4, v5);
  test_w95(v8, 0, (int)v4, v5);
  v9 = 0;
  harderr((int)criticalhandler, __CS__);
  network_slot = 0;
  if (v5 == 2)
    network_slot = atoi(v4[1]) & 0xFFFFFF;
  v10 = 1;
  LOWORD(player1_car) = 0;
  player2_car = 1;
  name_copy((int)player_names, &aHuman[1]);
  v11 = name_copy((int)&player_names[9 * player2_car], aPlayer2);
  textures_off = 0;
  frontend_on = -1;
  claim_key_int((int)v11, (int)aPlayer2);
  v12 = *v4;
  max_mem = 0;
  setdirectory(v12);
  v13 = 0;
  do {
    v14 = 4 * (__int16)v13++;
    mem_blocks[v14] = 0;
  } while ((__int16)v13 < 128);
  cheat_mode = 0;
  load_language_map();
  load_fatal_config();
  if ((textures_off & 0x2000) != 0) {
    v9 = cheat_mode | 0x40;
    cheat_mode |= 0x40u;
    textures_off ^= 0x2000u;
  }
  if ((textures_off & 0x4000) != 0) {
    false_starts = -1;
    v10 = textures_off;
    BYTE1(v10) = BYTE1(textures_off) ^ 0x40;
    textures_off = v10;
  } else {
    v14 = 0;
    false_starts = 0;
  }
  findintrofiles();
  initmusic();
  tick_on = 0;
  j_unlink(aReplaysReplayT);
  v15 = readsoundconfig(v9);
  loadcheatnames(v15, v14 * 4, 0, v10);
  cdxinit();
  GetFirstCDDrive();
  nullsub_2();
  StopTrack();
  StopTrack();
  print_data = 0;
  TrackSelect = 0;
  Initialise_SOS();
  check_machine_speed();
  if (fatal_ini_loaded) {
    if (view_limit) {
      if (machine_speed >= 2800)
        view_limit = 32;
      else
        view_limit = 24;
    }
  } else {
    if (machine_speed < 9000)
      textures_off |= 0x80000u;
    if (machine_speed < 5000)
      textures_off |= (unsigned int)&loc_3FFFC + 4;
    if (machine_speed < 4600) {
      v16 = textures_off;
      BYTE1(v16) = BYTE1(textures_off) | 8;
      textures_off = v16;
    }
    if (machine_speed < 4300)
      textures_off |= 8u;
    if (machine_speed < 4000)
      view_limit = 32;
    if (machine_speed < 3750) {
      v17 = textures_off;
      LOBYTE(v17) = textures_off | 0x20;
      textures_off = v17;
    }
    if (machine_speed < 3500) {
      v18 = textures_off;
      LOBYTE(v18) = textures_off | 0x10;
      textures_off = v18;
    }
    if (machine_speed < 3250)
      textures_off |= 0x200u;
    if (machine_speed < 3000)
      game_size = 48;
    if (machine_speed < 3800)
      allengines = 0;
    if (machine_speed < 2900)
      replay_record = 0;
    if (machine_speed < 2800)
      view_limit = 24;
  }
  v19 = InitCarStructs();
  init(v19);
  v20 = 0;
  print_data = 0;
  tick_on = 0;
  v21 = copy_screens();
  i = 0;
  title_screens(v21, 0, 0);
  time_to_start = 0;
  replaytype = 2;
  start_race = 0;
  countdown = 144;
  gosound = 3;
  delayread = 0;
  delaywrite = 6;
  writeptr = 0;
  readptr = 0;
  winner_mode = 0;
  intro = -1;
  restarted = play_game(TrackLoad);
  intro = 0;
  VIEWDIST = 270;
  do {
    start_race = 0;
    time_to_start = 0;
    if (restart_net) {
      restarted = restart_net_game();
    } else {
      while (!time_to_start)
        restarted = select_screen(0);
    }
    restart_net = 0;
    countdown = 144;
    gosound = 3;
    delayread = 0;
    delaywrite = 6;
    writeptr = 0;
    readptr = 0;
    if (!quit_game) {
      if (game_type < 3) {
        title_screens(restarted, v20, i);
        v24 = replaytype;
        v20 = -1;
        if (replaytype == 2)
          v20 = 0;
        if (intro)
          v20 = 0;
        net_quit = 0;
        prev_track = TrackLoad;
        restarted = play_game(TrackLoad);
        if (network_buggered) {
          restarted = network_fucked(restarted, v20);
          v20 = 0;
        }
        if (net_quit || network_buggered) {
          v20 = 0;
          if (network_champ_on && (network_buggered != 666 || !restart_net)) {
            game_type = 0;
            network_champ_on = 0;
          }
          if (net_quit)
            restarted = close_network(restarted, 0, v24);
        }
        if (cd_error)
          no_cd();
        i = 270;
        VIEWDIST = 270;
        if (!quit_game) {
          if (v20) {
            restarted = game_type;
            if (game_type) {
              if ((unsigned int)game_type > 1) {
                if (game_type == 2) {
                  StoreResult();
                  for (i = 0; (__int16)i < numcars; ++i) {
                    if (human_control[(__int16)i]) {
                      v20 = 308 * (__int16)i;
                      if (Car_variable_31[v20] > 1)
                        TimeTrials((__int16)i);
                    }
                  }
                  restarted = ShowLapRecords();
                }
                goto LABEL_103;
              }
              finish_race();
              StoreResult();
              if (human_control[carorder[0]] || (cheat_mode & 0x20) != 0) {
                v20 = carorder[0] & 1;
                if (winner_screen((unsigned __int8)Car_variable_22[308 * carorder[0]], v20))
                  winner_race();
              }
              ResultRoundUp();
              RaceResult();
              ChampionshipStandings();
              if (competitors > 8 && (cheat_mode & 0x4000) == 0)
                TeamStandings();
              ShowLapRecords();
              ++Race;
              restarted = prev_track + 1;
              TrackLoad = prev_track + 1;
              if (Race == 8 || (v20 = cheat_mode, (cheat_mode & 0x10) != 0)) {
                restarted = ChampionshipOver();
                goto LABEL_103;
              }
              i = cheat_mode;
              if ((cheat_mode & 0x80u) == 0)
                goto LABEL_103;
            LABEL_83:
              restarted = RollCredits(restarted, v20, i);
              goto LABEL_103;
            }
            if (!gave_up) {
              finish_race();
              StoreResult();
              if (human_control[carorder[0]] || (cheat_mode & 0x20) != 0) {
                v20 = carorder[0] & 1;
                if (winner_screen((unsigned __int8)Car_variable_22[308 * carorder[0]], v20))
                  winner_race();
              }
              ResultRoundUp();
              RaceResult();
              restarted = ShowLapRecords();
            }
            if ((cheat_mode & 0x10) != 0)
              restarted = ChampionshipOver();
            if ((cheat_mode & 0x80) != 0)
              goto LABEL_83;
          LABEL_103:
            if (player_type == 1)
              player_type = 0;
          }
          intro = 0;
        }
      } else if (game_type == 3) {
        restarted = ChampionshipStandings();
        if (competitors > 8) {
          i = cheat_mode;
          if ((cheat_mode & 0x4000) == 0)
            restarted = TeamStandings();
        }
        dontrestart = -1;
      } else {
        restarted = ShowLapRecords();
        dontrestart = -1;
      }
    }
  } while (!quit_game);
  __asm { int     10h; -VIDEO - SET VIDEO MODE }
  doexit();
  return result;
}
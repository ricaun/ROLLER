#include "replay.h"
#include "sound.h"
#include "car.h"
#include "3d.h"
#include "moving.h"
#include <string.h>
#ifdef IS_WINDOWS
#include <io.h>
#else
#define _GNU_SOURCE
#include <dirent.h>
#include <fnmatch.h>
#endif
//-------------------------------------------------------------------------------------------------

int rotpoint = 0;         //000A63B0
int replayspeeds[9] = { 16, 32, 64, 128, 256, 512, 1024, 2048, 4096 }; //000A63BC
int filingmenu = 0;       //000A6408
int replaysetspeed = 0;   //000A6414
int replaydirection = 0;  //000A6418
int lastfile = -1;        //000A641C
int lastautocut = -1;     //000A6420
int pend_view_init = -1;  //000A6424
int replayedit = 0;       //000A6428
tReplayCamera camera[100];//00189980
int disabled[4096];       //00189BD8
int replayspeed;          //0018EE40
int replayframes;         //0018EE48
int currentreplayframe;   //0018EE54
int lastreplayframe;      //0018EE58
int introfiles;           //0018EE70
char newrepsample[16];    //0018DC68
char repsample[16];       //0018DC78
int replayselect;         //0018EE60
int slowing;              //0018EE64
int rewinding;            //0018EE68
int forwarding;           //0018EE6C
int replaystart;          //0018EE74
int cuts;                 //0018EE78

//-------------------------------------------------------------------------------------------------
//00063DB0
void setreplaytrack()
{/*
  int v0; // eax
  char *v1; // edi
  char *v2; // esi
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int v7; // ecx
  int v8; // ebx
  int *v9; // esi
  int *v10; // eax
  int v11; // ebp
  int v12; // esi
  unsigned __int8 v13; // al
  int v14; // ecx
  int v15; // [esp+0h] [ebp-20h]
  _BYTE v16[28]; // [esp+4h] [ebp-1Ch] BYREF

  if (replaytype == 2) {
    oldtrack = TrackLoad;
    oldcars = numcars;
    v0 = textures_off;
    oldtextures = textures_off;
    if (intro || replayfilename[0] == 73) {
      v1 = (char *)&rememberfilename;
      v2 = replayfilename;
      do {
        LOBYTE(v0) = *v2;
        *v1 = *v2;
        if (!(_BYTE)v0)
          break;
        LOBYTE(v0) = v2[1];
        v2 += 2;
        v1[1] = v0;
        v1 += 2;
      } while ((_BYTE)v0);
      do {
        v3 = rand(v0);
        v0 = ((v3 * introfiles - (__CFSHL__((v3 * introfiles) >> 31, 15) + ((v3 * introfiles) >> 31 << 15))) >> 15) + 1;
      } while (v0 == lastintro && introfiles != 1);
      lastintro = v0;
      sprintf(replayfilename, "INTRO%d.GSS", v0);
    }
    v4 = fopen(replayfilename, aRb_0);
    v5 = v4;
    if (!v4) {
      do {
        v6 = rand(v4);
        v4 = ((v6 * introfiles - (__CFSHL__((v6 * introfiles) >> 31, 15) + ((v6 * introfiles) >> 31 << 15))) >> 15) + 1;
      } while (v4 == lastintro);
      lastintro = v4;
      sprintf(replayfilename, "INTRO%d.GSS", v4);
      v5 = fopen(replayfilename, aRb_0);
    }
    if (v5) {
      fread(v16, 1, 1, v5);
      TrackLoad = v16[0];
      game_track = v16[0];
      fread(v16, 1, 1, v5);
      if ((v16[0] & 0x20) != 0)
        textures_off |= (unsigned int)cstart_branch_1;
      else
        textures_off &= ~0x10000u;
      cheat_mode = 0;
      if ((v16[0] & 0x40) != 0) {
        v7 = cheat_mode;
        BYTE1(v7) = BYTE1(cheat_mode) | 0x10;
        cheat_mode = v7;
      } else {
        v8 = cheat_mode;
        BYTE1(v8) = BYTE1(cheat_mode) & 0xEF;
        cheat_mode = v8;
      }
      if (v16[0] >= 0)
        cheat_mode &= ~0x8000u;
      else
        cheat_mode |= 0x8000u;
      v9 = non_competitors;
      numcars = v16[0] & 0x1F;
      fseek(v5, 605, 0);
      do {
        v10 = v9++;
        fread(v10, 4, 1, v5);
      } while (v9 != &non_competitors[16]);
      fread(&racers, 4, 1, v5);
      v15 = 0;
      if (numcars > 0) {
        v11 = 0;
        v12 = 0;
        do {
          fread(v16, 1, 1, v5);
          v13 = v16[0];
          Car_variable_22[v12] = v16[0];
          v14 = numcars;
          ++v11;
          v12 += 308;
          car_texture_names_variable_1[v11] = v13;
          ++v15;
        } while (v15 < v14);
      }
    }
    if (v5)
      fclose(v5);
  }*/
}

//-------------------------------------------------------------------------------------------------
//00064040
int startreplay()
{
  return 0; /*
  int result; // eax
  char *v1; // edi
  const char *v2; // esi
  char v3; // al
  char v4; // al
  int *v5; // esi
  int *v6; // eax
  int v7; // edi
  int v8; // esi
  int v9; // edi
  char *v10; // esi
  char *v11; // edx
  char *v12; // ebx
  char *v13; // edi
  char *v14; // esi
  char v15; // al
  char v16; // al
  int v17; // eax
  __int64 v18; // rax
  int v19; // ecx
  int v20; // edx
  int v21; // eax
  int v22; // ecx
  int v23; // ebx
  int *v24; // esi
  int *v25; // eax
  int v26; // ebp
  int v27; // edi
  unsigned int v28; // esi
  char v29; // al
  int v30; // ebx
  double v31; // st7
  double v32; // st7
  int v33; // edi
  char *v34; // esi
  int v35; // esi
  char v36; // al
  int v37; // ebp
  unsigned int v38; // eax
  int v39; // edx
  int v40; // [esp+0h] [ebp-3Ch] BYREF
  _BYTE v41[28]; // [esp+20h] [ebp-1Ch] BYREF

  oldcars = numcars;
  lastreplayframe = -1;
  currentreplayframe = 0;
  lastautocut = -1;
  forwarding = 0;
  rewinding = 0;
  slowing = 0;
  replayedit = 0;
  replaysetspeed = 4;
  replaydirection = 1;
  replaypanel = -1;
  controlicon = 9;
  memset(&disabled, 255, 0x4000);
  memset(&camera, 0, 600);
  result = replaytype;
  cuts = 0;
  if (replaytype) {
    if ((unsigned int)replaytype <= 1) {
      v1 = replayfilename;
      v2 = "..\\REPLAYS\\REPLAY.TMP";
      discfull = 0;
      do {
        v3 = *v2;
        *v1 = *v2;
        if (!v3)
          break;
        v4 = v2[1];
        v2 += 2;
        v1[1] = v4;
        v1 += 2;
      } while (v4);
      result = fopen(replayfilename, &aYwb[1]);
      replayfile = result;
      if (result) {
        v41[0] = TrackLoad;
        fwrite(v41, 1, 1, result);
        v41[0] = numcars;
        if (((unsigned int)cstart_branch_1 & textures_off) != 0)
          v41[0] = numcars | 0x20;
        if ((cheat_mode & 0x1000) != 0)
          v41[0] |= 0x40u;
        if ((cheat_mode & 0x8000) != 0)
          v41[0] |= 0x80u;
        fwrite(v41, 1, 1, replayfile);
        v41[0] = ViewType[0];
        fwrite(v41, 1, 1, replayfile);
        v41[0] = SelectedView[0];
        fwrite(v41, 1, 1, replayfile);
        v5 = non_competitors;
        fwrite(&camera, 6, 100, replayfile);
        v41[0] = cuts;
        fwrite(v41, 1, 1, replayfile);
        do {
          v6 = v5++;
          fwrite(v6, 4, 1, replayfile);
        } while (v5 != &non_competitors[16]);
        fwrite(&racers, 4, 1, replayfile);
        v7 = 0;
        if (numcars > 0) {
          v8 = 0;
          do {
            v41[0] = Car_variable_22[v8];
            ++v7;
            fwrite(v41, 1, 1, replayfile);
            v8 += 308;
          } while (v7 < numcars);
        }
        result = numcars;
        v9 = 0;
        if (numcars > 0) {
          v10 = driver_names;
          do {
            result = fwrite(v10, 9, 1, replayfile);
            ++v9;
            v10 += 9;
          } while (v9 < numcars);
        }
      }
    } else if (replaytype == 2) {
      if (!intro)
        rev_vga_variable_5 = load_picture((int)&aLreplayscBm[1], 0, 600, 9);
      v11 = driver_names;
      v12 = (char *)&temp_names;
      do {
        v13 = v12;
        v14 = v11;
        do {
          v15 = *v14;
          *v13 = *v14;
          if (!v15)
            break;
          v16 = v14[1];
          v14 += 2;
          v13[1] = v16;
          v13 += 2;
        } while (v16);
        v11 += 9;
        v12 += 9;
      } while (v11 != &driver_names[144]);
      v17 = open(replayfilename, 512);
      if (v17 != -1) {
        v18 = filelength(v17, v17, v12);
        replayframes = v18;
        close(HIDWORD(v18), HIDWORD(v18));
      }
      v19 = fopen(replayfilename, aRb_0);
      replayfile = v19;
      if (v19) {
        fread(v41, 1, 1, v19);
        TrackLoad = v41[0];
        game_track = v41[0];
        fread(v41, 1, 1, replayfile);
        if ((v41[0] & 0x20) != 0)
          textures_off |= (unsigned int)cstart_branch_1;
        else
          textures_off &= ~0x10000u;
        cheat_mode = 0;
        if ((v41[0] & 0x40) != 0) {
          v20 = cheat_mode;
          BYTE1(v20) = BYTE1(cheat_mode) | 0x10;
          cheat_mode = v20;
        } else {
          v21 = cheat_mode;
          BYTE1(v21) = BYTE1(cheat_mode) & 0xEF;
          cheat_mode = v21;
        }
        if (v41[0] >= 0) {
          v23 = cheat_mode;
          BYTE1(v23) = BYTE1(cheat_mode) & 0x7F;
          cheat_mode = v23;
        } else {
          v22 = cheat_mode;
          BYTE1(v22) = BYTE1(cheat_mode) | 0x80;
          cheat_mode = v22;
        }
        numcars = v41[0] & 0x1F;
        fread(v41, 1, 1, replayfile);
        ViewType[0] = v41[0];
        fread(v41, 1, 1, replayfile);
        SelectedView[0] = v41[0];
        fread(&camera, 6, 100, replayfile);
        fread(v41, 1, 1, replayfile);
        v24 = non_competitors;
        cuts = v41[0];
        do {
          v25 = v24++;
          fread(v25, 4, 1, replayfile);
        } while (v24 != &non_competitors[16]);
        fread(&racers, 4, 1, replayfile);
        v26 = 0;
        if (numcars > 0) {
          v27 = 0;
          v28 = 0;
          do {
            fread(v41, 1, 1, replayfile);
            v29 = v41[0];
            Car_variable_10[v28 / 4] = v26;
            Car_variable_22[v28] = v29;
            Car_variable_64[v28] = 0;
            v30 = non_competitors[v27];
            Car_variable_65[v28] = 20;
            if (v30) {
              Car[v28 / 4] = -localdata_variable_1;
              Car_variable_1[v28 / 4] = -localdata_variable_2;
              v31 = -localdata_variable_3;
              Car_variable_17[v28 / 4] = 0;
              Car_variable_23[v28] = -1;
              v32 = v31 + replay_c_variable_14;
              Car_variable_8[v28 / 4] = 0.0;
              Car_variable_27[v28 / 4] = 0;
              finished_car[v27] = -1;
              Car_variable_4[v28 / 2] = Car_variable_3[v28 / 2];
              Car_variable_3[v28 / 2] = -1;
              Car_variable_2[v28 / 4] = v32;
            }
            ++v27;
            ++v26;
            v28 += 308;
          } while (v26 < numcars);
        }
        v33 = 0;
        if (numcars > 0) {
          v34 = driver_names;
          do {
            fread(v34, 9, 1, replayfile);
            ++v33;
            v34 += 9;
          } while (v33 < numcars);
        }
        fseek(replayfile, replayheader, 0);
        v35 = 0;
        if (numcars > 0) {
          do {
            fread(&v40, 30, 1, replayfile);
            ++v35;
            v36 = HIBYTE(v40);
            v37 = numcars;
            temp_names_variable_1[v35] = HIBYTE(v40);
            newrepsample_variable_1[v35] = v36;
          } while (v35 < v37);
        }
        replayheader = 10 * numcars + 673;
        replayblock = 30 * racers + 16;
        replayframes = (replayframes - replayheader) / (30 * racers + 16);
      }
      if (numcars > 0) {
        v38 = 0;
        v39 = 308 * numcars;
        do {
          v38 += 308;
          CarBox_variable_31[v38 / 4] = 8;
          CarBox_variable_28[v38 / 4] = 0;
          CarBox_variable_29[v38 / 4] = 0;
          CarBox_variable_26[v38 / 4] = 0;
          CarBox_variable_27[v38 / 4] = 0;
        } while ((int)v38 < v39);
      }
      result = 256;
      replayspeed = 256;
      if (replayfilename[0] == 73 && !intro)
        filingmenu = 1;
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00064730
void stopreplay(int a1, int a2, int a3, int a4)
{/*
  char *v4; // edx
  char *v5; // ebx
  char *v6; // edi
  char *v7; // esi
  char v8; // al
  char v9; // al
  __int64 v10; // rax
  int v11; // ebx
  int v12; // edx
  char *v13; // edi
  char *v14; // esi
  char v15; // al
  char v16; // al
  _WORD v17[8]; // [esp-2h] [ebp-1Ch] BYREF
  int v18; // [esp+Eh] [ebp-Ch]
  int v19; // [esp+12h] [ebp-8h]

  v19 = a4;
  v18 = a2;
  if (replaytype)
    fclose(replayfile);
  if (replaytype == 2) {
    v4 = (char *)&temp_names;
    v5 = driver_names;
    do {
      v6 = v5;
      v7 = v4;
      do {
        v8 = *v7;
        *v6 = *v7;
        if (!v8)
          break;
        v9 = v7[1];
        v7 += 2;
        v6[1] = v9;
        v6 += 2;
      } while (v9);
      v4 += 9;
      v5 += 9;
    } while (v4 != (char *)&temp_names + 144);
    TrackLoad = oldtrack;
    numcars = oldcars;
    textures_off = oldtextures;
  }
  if (replaytype == 1) {
    dos_getdiskfree(0, v17);
    if (v17[1] * v17[2] * v17[3] < (int)&unk_100000) {
      v10 = open(replayfilename, 514);
      v11 = v10;
      if ((_DWORD)v10 != -1) {
        v12 = filelength(v10, HIDWORD(v10), v10) - ((_DWORD)&unk_100000 - HIDWORD(v10));
        if (v12 >= 20480) {
          chsize(v11, v12);
          close(v11, v12);
        } else {
          close(v11, v12);
          remove(replayfilename);
        }
      }
    }
  }
  replaytype = 0;
  if (intro) {
    v13 = replayfilename;
    v14 = (char *)&rememberfilename;
    do {
      v15 = *v14;
      *v13 = *v14;
      if (!v15)
        break;
      v16 = v14[1];
      v14 += 2;
      v13[1] = v16;
      v13 += 2;
    } while (v16);
  }*/
}

//-------------------------------------------------------------------------------------------------
//00064880
int DoReplayData(int a1, int a2, int a3, int a4)
{
  return 0; /*
  int result; // eax
  int v5; // esi
  float *v6; // edi
  int v7; // ebp
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int *v15; // esi
  int i; // edi
  int v17; // eax
  float *v18; // ebp
  int v22; // edx
  __int16 v23; // dx
  __int16 v25; // ax
  int v29; // edx
  int v31; // edx
  int v34; // ecx
  int v35; // eax
  int v36; // edi
  int v38; // ebx
  int v39; // ecx
  float v42; // eax
  int j; // eax
  int v44; // ecx
  _BYTE *v45; // ebx
  int v46; // edi
  int v47; // eax
  int *v48; // esi
  int k; // ebp
  int v50; // ebx
  int v51; // esi
  int v52; // ecx
  int v53; // edx
  unsigned int v54; // edi
  int v55; // eax
  int v56; // ebp
  int v57; // edi
  int v58; // eax
  int v59; // edi
  int v60; // ebp
  int v61; // edx
  unsigned int v62; // edi
  int v63; // edi
  int v64; // eax
  int v65; // ebp
  int v66; // eax
  int v67; // ebp
  int v68; // edi
  int v69; // ebp
  int v70; // edx
  unsigned int v71; // edi
  int v72; // eax
  int v73; // ebp
  int v74; // edi
  int v75; // eax
  int v76; // edi
  int v77; // ebp
  int v78; // edi
  int v79; // edi
  int v80; // eax
  int v81; // ebp
  int v82; // eax
  int v83; // edi
  int v84; // ebp
  int v85; // ecx
  int v86; // eax
  int v87; // edx
  int v88; // ecx
  int v89; // esi
  float *v90; // edi
  int m; // edx
  int v92; // ebx
  int v93; // ecx
  int v94; // esi
  unsigned int v95; // eax
  int v96; // [esp+0h] [ebp-134h] BYREF
  int v97; // [esp+4h] [ebp-130h]
  int v98; // [esp+8h] [ebp-12Ch]
  __int16 v99; // [esp+Ch] [ebp-128h]
  __int16 v100; // [esp+Eh] [ebp-126h]
  __int16 v101; // [esp+10h] [ebp-124h]
  __int16 v102; // [esp+12h] [ebp-122h]
  __int16 v103; // [esp+14h] [ebp-120h]
  __int16 v104; // [esp+16h] [ebp-11Eh]
  unsigned __int8 v105; // [esp+18h] [ebp-11Ch]
  unsigned __int8 v106; // [esp+19h] [ebp-11Bh]
  char v107; // [esp+1Ah] [ebp-11Ah]
  char v108; // [esp+1Bh] [ebp-119h]
  char v109; // [esp+1Ch] [ebp-118h]
  char v110; // [esp+1Dh] [ebp-117h]
  int v111; // [esp+20h] [ebp-114h]
  int v112; // [esp+24h] [ebp-110h]
  int v113; // [esp+28h] [ebp-10Ch]
  unsigned int v114; // [esp+2Ch] [ebp-108h]
  int v115; // [esp+30h] [ebp-104h]
  int v116; // [esp+34h] [ebp-100h]
  int v117; // [esp+38h] [ebp-FCh]
  float v118; // [esp+40h] [ebp-F4h]
  int v119; // [esp+50h] [ebp-E4h]
  int v120; // [esp+54h] [ebp-E0h]
  int v121; // [esp+58h] [ebp-DCh]
  int v122; // [esp+5Ch] [ebp-D8h]
  int v123; // [esp+60h] [ebp-D4h]
  int v124; // [esp+64h] [ebp-D0h] BYREF
  unsigned int v125; // [esp+68h] [ebp-CCh]
  unsigned int v126; // [esp+6Ch] [ebp-C8h]
  unsigned int v127; // [esp+70h] [ebp-C4h]
  unsigned int v128; // [esp+74h] [ebp-C0h]
  unsigned int v129; // [esp+78h] [ebp-BCh]
  unsigned int v130; // [esp+7Ch] [ebp-B8h]
  int v131; // [esp+80h] [ebp-B4h]
  unsigned int v132; // [esp+84h] [ebp-B0h]
  unsigned int v133; // [esp+88h] [ebp-ACh]
  unsigned int v134; // [esp+8Ch] [ebp-A8h]
  unsigned int v135; // [esp+90h] [ebp-A4h]
  unsigned int v136; // [esp+94h] [ebp-A0h]
  int v137; // [esp+98h] [ebp-9Ch]
  int v138; // [esp+9Ch] [ebp-98h]
  int v139; // [esp+A0h] [ebp-94h]
  int v140; // [esp+A4h] [ebp-90h]
  int v141; // [esp+A8h] [ebp-8Ch]
  int v142; // [esp+ACh] [ebp-88h]
  int v143; // [esp+B0h] [ebp-84h]
  int v144; // [esp+B4h] [ebp-80h]
  int v145; // [esp+B8h] [ebp-7Ch]
  int v146; // [esp+BCh] [ebp-78h]
  int v147; // [esp+C0h] [ebp-74h]
  int v148; // [esp+C4h] [ebp-70h]
  int v149; // [esp+C8h] [ebp-6Ch]
  int v150; // [esp+CCh] [ebp-68h]
  int v151; // [esp+D0h] [ebp-64h]
  int v152; // [esp+D4h] [ebp-60h]
  int v153; // [esp+D8h] [ebp-5Ch]
  int v154; // [esp+DCh] [ebp-58h]
  int v155; // [esp+E0h] [ebp-54h]
  int v156; // [esp+E4h] [ebp-50h]
  unsigned int v157; // [esp+E8h] [ebp-4Ch]
  unsigned int v158; // [esp+ECh] [ebp-48h]
  int v159; // [esp+F0h] [ebp-44h]
  int v160; // [esp+F4h] [ebp-40h]
  int v161; // [esp+F8h] [ebp-3Ch]
  int v162; // [esp+FCh] [ebp-38h]
  int v163; // [esp+100h] [ebp-34h]
  int v164; // [esp+104h] [ebp-30h]
  int v165; // [esp+108h] [ebp-2Ch]
  int v166; // [esp+10Ch] [ebp-28h]
  int v167; // [esp+110h] [ebp-24h]
  int v168; // [esp+114h] [ebp-20h] BYREF
  int v169; // [esp+118h] [ebp-1Ch]

  result = replaytype;
  if (replaytype) {
    if ((unsigned int)replaytype <= 1) {
      if (replayfile && !discfull) {
        v5 = 0;
        if (numcars > 0) {
          v6 = Car;
          v7 = 0;
          do {
            if (!non_competitors[v7]) {
              BYTE1(result) = newrepsample[v5];
              _EDX = v6;
              if (BYTE1(result)) {
                if (repsample[v5] > 0)
                  LOBYTE(result) = -BYTE1(result) - 1;
                else
                  LOBYTE(result) = BYTE1(result) + 1;
                repsample[v5] = result;
              }
              __asm { fld     dword ptr[edx] }
              _CHP(result, v6);
              __asm { fistp[esp + 134h + var_24] }
              v96 = (repsample[v5] << 24) | v167 & 0xFFFFFF;
              __asm { fld     dword ptr[edx + 4] }
              _CHP(v96, v6);
              __asm { fistp[esp + 134h + var_24] }
              v97 = ((unsigned __int8)repvolume[v5] << 24) | v167 & 0xFFFFFF;
              __asm { fld     dword ptr[edx + 8] }
              _CHP(v97, v6);
              __asm { fistp[esp + 134h + var_24] }
              v9 = *((_DWORD *)v6 + 19) << 24;
              v98 = v9 | v167 & 0xFFFFFF;
              v10 = *((__int16 *)v6 + 6);
              if (v10 == -1) {
                LOWORD(v10) = *((_WORD *)v6 + 7);
                v9 = -v10;
                v99 = -(__int16)v10;
              } else {
                v99 = *((_WORD *)v6 + 6);
              }
              v102 = *((_WORD *)v6 + 10);
              v103 = *((_WORD *)v6 + 32);
              LOWORD(v10) = *((_WORD *)v6 + 9);
              LOWORD(a4) = *((_WORD *)v6 + 66);
              LOWORD(v9) = *((_WORD *)v6 + 74);
              v11 = v9 + a4 + v10;
              BYTE1(v11) &= 0x3Fu;
              v101 = v11;
              LOWORD(v11) = *((_WORD *)v6 + 8);
              LOWORD(a4) = *((_WORD *)v6 + 68);
              LOWORD(v9) = *((_WORD *)v6 + 78);
              v12 = v9 + a4 + v11;
              BYTE1(v12) &= 0x3Fu;
              v100 = v12;
              __asm
              {
                fld     dword ptr[edx + 18h]
                fabs
              }
              _CHP(v12, v6);
              __asm { fistp[esp + 134h + var_24] }
              v104 = v167 | ((*((char *)v6 + 103) + 2) << 10);
              if ((*((_BYTE *)v6 + 131) & 2) != 0)
                HIBYTE(v104) |= 0x20u;
              if ((*((_BYTE *)v6 + 131) & 4) != 0)
                HIBYTE(v104) |= 0x40u;
              __asm
              {
                fld     dword ptr[edx + 78h]
                fmul    replay_c_variable_15
              }
              _CHP(v13, v6);
              __asm { fistp[esp + 134h + var_24] }
              LOBYTE(v14) = v167;
              v105 = v167;
              __asm { fld     dword ptr[edx + 1Ch] }
              _CHP(v14, v6);
              __asm { fistp[esp + 134h + var_24] }
              v106 = v167 | (*((_BYTE *)v6 + 204) << 7);
              v107 = (*((_BYTE *)v6 + 273) << 7)
                + 8 * *((_BYTE *)v6 + 280)
                + *((_BYTE *)v6 + 128)
                + 2
                + 16 * *((_BYTE *)v6 + 278);
              v108 = *((_BYTE *)v6 + 129);
              if (*((__int16 *)v6 + 50) >= 0)
                v109 = *((_BYTE *)v6 + 100);
              else
                v109 = -1;
              HIWORD(a4) = HIWORD(replayfile);
              v110 = *((_BYTE *)v6 + 275);
              if (!fwrite(&v96, 30, 1, replayfile))
                discfull = -1;
            }
            result = numcars;
            ++v7;
            ++v5;
            v6 += 77;
          } while (v5 < numcars);
        }
        v15 = ramp;
        for (i = 0; i < 8; ++i) {
          v17 = *v15;
          if (*v15) {
            LOWORD(v17) = *(_WORD *)(v17 + 40);
            ++v15;
          } else {
            v17 = 0;
          }
          v168 = v17;
          result = fwrite(&v168, 2, 1, replayfile);
          if (!result)
            discfull = -1;
        }
      }
    } else if (replaytype == 2) {
      if (replayspeed != 256)
        result = stopallsamples();
      newreplayframe = 0;
      if (replayfile) {
        currentreplayframe = ticks;
        v121 = 0;
        if (ticks >= replayframes)
          currentreplayframe = replayframes - 1;
        if (currentreplayframe < 0)
          currentreplayframe = 0;
        if (!rewinding && !forwarding && readdisable(currentreplayframe)) {
          if (replayspeed <= 0) {
            if (replayspeed < 0)
              findlastvalid();
          } else {
            findnextvalid();
          }
          v121 = -1;
        }
        if (replayframes - 1 == currentreplayframe && replayspeed > 0 && replaytype == 2) {
          _disable();
          replayspeed = 0;
          fraction = 0;
          replaydirection = 0;
          ticks = currentreplayframe;
          _enable();
        }
        if (!currentreplayframe && replayspeed < 0 && replaytype == 2) {
          _disable();
          replayspeed = currentreplayframe;
          fraction = currentreplayframe;
          replaydirection = currentreplayframe;
          ticks = currentreplayframe;
          _enable();
        }
        result = lastreplayframe;
        if (lastreplayframe == currentreplayframe) {
          newreplayframe = 0;
        } else {
          newreplayframe = -1;
          fseek(replayfile, replayblock * currentreplayframe + replayheader, 0);
          v123 = 0;
          if (numcars > 0) {
            v18 = Car;
            v136 = 0;
            do {
              if (!non_competitors[v136 / 4]) {
                fread(&v96, 30, 1, replayfile);
                v167 = v96 << 8 >> 8;
                __asm
                {
                  fild[esp + 134h + var_24]
                  fstp    dword ptr[ebp + 0]
                }
                *v18 = _ET1;
                v167 = v97 << 8 >> 8;
                __asm
                {
                  fild[esp + 134h + var_24]
                  fstp    dword ptr[ebp + 4]
                }
                v18[1] = _ET1;
                v167 = v98 << 8 >> 8;
                __asm
                {
                  fild[esp + 134h + var_24]
                  fstp    dword ptr[ebp + 8]
                }
                v18[2] = _ET1;
                v22 = v123;
                newrepsample[v123] = HIBYTE(v96);
                repvolume[v22] = HIBYTE(v97);
                *((_DWORD *)v18 + 19) = v98 >> 24;
                v23 = v99;
                _ESI = v18;
                if (v99 >= 0) {
                  *((_DWORD *)v18 + 18) = 3;
                  *((_WORD *)v18 + 6) = v23;
                  *((_WORD *)v18 + 7) = v23;
                  *((_DWORD *)v18 + 54) = v23;
                } else {
                  *((_WORD *)v18 + 6) = -1;
                  v25 = v99;
                  v18[18] = 0.0;
                  *((_WORD *)v18 + 7) = v25;
                  *((_WORD *)v18 + 7) = -v25;
                  findnearsection((int)v18, &v124);
                }
                if (*((_DWORD *)v18 + 18) == 3) {
                  __asm { fld     dword ptr[esi + 4] }
                  _EDX = (char *)&localdata + 128 * *((__int16 *)v18 + 6);
                  __asm
                  {
                    fcomp   dword ptr[edx + 34h]
                    fnstsw  ax
                  }
                  if ((_AX & 0x100) != 0 || (_AX & 0x4000) != 0) {
                    __asm
                    {
                      fld     dword ptr[edx + 34h]
                      fchs
                      fcomp   dword ptr[esi + 4]
                      fnstsw  ax
                    }
                    if ((_AX & 0x100) != 0 || (_AX & 0x4000) != 0)
                      *((_DWORD *)v18 + 53) = 1;
                    else
                      *((_DWORD *)v18 + 53) = 2;
                  } else {
                    v18[53] = 0.0;
                  }
                }
                *((_WORD *)v18 + 10) = v102;
                *((_DWORD *)v18 + 16) = v103;
                *((_WORD *)v18 + 9) = v101;
                HIWORD(v29) = 0;
                *((_WORD *)v18 + 8) = v100;
                LOWORD(v29) = v104;
                v167 = v104 & 0x2FF;
                __asm { fild[esp + 134h + var_24] }
                *((_BYTE *)v18 + 131) = 0;
                __asm { fstp    dword ptr[esi + 18h] }
                v18[6] = _ET1;
                if ((v29 & 0x2000) != 0)
                  *((_BYTE *)v18 + 131) = 2;
                if ((v29 & 0x4000) != 0)
                  *((_BYTE *)v18 + 131) |= 4u;
                v31 = (v29 >> 10) & 7;
                if (v31) {
                  *((_BYTE *)v18 + 103) = v31 - 2;
                } else {
                  *((_BYTE *)v18 + 131) = 0;
                  *((_BYTE *)v18 + 103) = 3;
                }
                *((_WORD *)v18 + 50) = v109;
                LOWORD(v169) = v105;
                __asm
                {
                  fild    word ptr[esp + 134h + var_1C]
                  fmul    replay_c_variable_16
                  fstp    dword ptr[esi + 78h]
                }
                v18[30] = _ET1;
                v169 = v106 & 0x7F;
                __asm
                {
                  fild    word ptr[esp + 134h + var_1C]
                  fstp    dword ptr[esi + 1Ch]
                }
                v18[7] = _ET1;
                v34 = (int)v106 >> 7;
                *((_DWORD *)v18 + 51) = v34;
                *((_DWORD *)v18 + 51) = -v34;
                *((_BYTE *)v18 + 128) = (v107 & 7) - 2;
                v122 = (v107 & 8) >> 3;
                v35 = (v107 & 0x70) >> 4;
                *((_BYTE *)v18 + 278) = v35;
                if ((unsigned __int8)v35 > 4u)
                  *((_BYTE *)v18 + 278) = 4;
                *((_BYTE *)v18 + 273) = (v107 & 0x80) >> 7;
                v36 = *((_DWORD *)v18 + 70);
                *((_BYTE *)v18 + 275) = v110;
                if (v36 != v122 && ViewType[0] == *((_DWORD *)v18 + 8)) {
                  if (v99 < 0) {
                    _EDX = (char *)&localdata;
                    v160 = 1343554297;
                    v38 = 0;
                    if (TRAK_LEN > 0) {
                      v39 = 0;
                      do {
                        __asm
                        {
                          fld     dword ptr[esi]
                          fadd    dword ptr[edx + 24h]
                          fld     dword ptr[esi + 4]
                          fadd    dword ptr[edx + 28h]
                          fld     dword ptr[esi + 8]
                          fadd    dword ptr[edx + 2Ch]
                          fld     dword ptr[edx + 8]
                          fmul    st, st(3)
                          fld     dword ptr[edx + 14h]
                          fmul    st, st(3)
                          faddp   st(1), st
                          fld     dword ptr[edx + 20h]
                          fmul    st, st(2)
                          faddp   st(1), st
                          fld     st(3)
                          fmulp   st(4), st
                          fld     st(2)
                          fmulp   st(3), st
                          fxch    st(2)
                          faddp   st(3), st
                          fmul    st, st
                          faddp   st(2), st
                          fxch    st(1)
                          fsqrt
                          fsub    dword ptr[edx + 30h]
                          fstp[esp + 134h + var_F4]
                          fcomp   replay_c_variable_17
                          fnstsw  ax
                        }
                        if ((_AX & 0x100) == 0 || GroundColour_variable_4[v39] >= 0) {
                          __asm
                          {
                            fld[esp + 134h + var_F4]
                            fcomp[esp + 134h + var_40]
                            fnstsw  ax
                          }
                          if ((_AX & 0x100) != 0) {
                            v42 = v118;
                            *((_DWORD *)v18 + 54) = v38;
                            v160 = LODWORD(v42);
                          }
                        }
                        _EDX += 128;
                        ++v38;
                        v39 += 5;
                      } while (v38 < TRAK_LEN);
                    }
                    findnearsection((int)v18, &v124);
                  }
                  pend_view_init = ViewType[0];
                }
                j = v122;
                if (v122 != *((_DWORD *)v18 + 70)) {
                  for (j = 0; j != 1408; *(int *)((char *)&car_texs_loaded_variable_2[352 * *((_DWORD *)v18 + 8)] + j) = 0)
                    j += 44;
                  *((_BYTE *)v18 + 274) = *((_BYTE *)v18 + 273);
                }
                LOBYTE(j) = *((_BYTE *)v18 + 273);
                if ((_BYTE)j != *((_BYTE *)v18 + 274)) {
                  v44 = 0;
                  v45 = &CarSpray[1408 * *((_DWORD *)v18 + 8)];
                  v46 = *((unsigned __int8 *)v18 + 275);
                  do {
                    if (*((int *)v45 + 7) <= 0) {
                      v47 = rand(j);
                      j = (12 * v47 - (__CFSHL__((12 * v47) >> 31, 15) + ((12 * v47) >> 31 << 15))) >> 15;
                      if (j < v46)
                        *((_DWORD *)v45 + 8) = -1;
                    }
                    ++v44;
                    v45 += 44;
                  } while (v44 < 32);
                }
                *((_DWORD *)v18 + 70) = v122;
                *((_BYTE *)v18 + 274) = *((_BYTE *)v18 + 273);
                *((_BYTE *)v18 + 129) = v108;
              }
              v18 += 77;
              v136 += 4;
              ++v123;
            } while (v123 < numcars);
          }
          v48 = ramp;
          for (k = 0; k < 8; ++k) {
            fread(&v168, 2, 1, replayfile);
            if (*v48)
              *(_DWORD *)(*v48 + 40) = (unsigned __int16)v168;
            ++v48;
          }
          if (replayspeed == 256) {
            v50 = currentreplayframe - lastreplayframe - 1;
            v120 = ((_BYTE)delaywrite - 1) & 0x1F;
            delaywrite += v50;
            v51 = delaywrite & 0x1F;
            enginesounds(ViewType[0]);
            if (v50 > 0 && numcars > 0) {
              v128 = 28 * v120;
              v129 = 28 * v51;
              v131 = ((_BYTE)v120 + 1) & 0x1F;
              v52 = v50 + 1;
              v157 = 28 * v51;
              v114 = 28 * v120;
              v156 = 0;
              v158 = 0;
              v159 = 4 * numcars;
              do {
                if (!non_competitors[v156 / 4u]) {
                  if (enginedelay_variable_1[v157 / 4] == -1 || enginedelay_variable_1[v128 / 4 + v158 / 4] == -1) {
                    v53 = v131;
                    if (v51 != v131) {
                      v54 = v158;
                      do {
                        *(int *)((char *)&enginedelay_variable_1[7 * v53] + v54) = -1;
                        v53 = ((_BYTE)v53 + 1) & 0x1F;
                      } while (v53 != v51);
                    }
                  } else {
                    v119 = v120;
                    v55 = enginedelay_variable_1[v128 / 4 + v158 / 4];
                    v138 = enginedelay_variable_1[v157 / 4];
                    v137 = v138;
                    v56 = 1;
                    v139 = v55;
                    v132 = v158;
                    v57 = v55 * -v50;
                    do {
                      v119 = ((_BYTE)v119 + 1) & 0x1F;
                      v167 = 28 * v119;
                      *(int *)((char *)&enginedelay_variable_1[7 * v119] + v132) = (v137 - v57) / v52;
                      ++v56;
                      v137 += v138;
                      v57 += v139;
                    } while (v56 <= v50);
                    v58 = *(int *)((char *)&enginedelay[v128 / 4] + v132);
                    v59 = *(int *)((char *)&enginedelay[v129 / 4] + v132);
                    v166 = v120;
                    v117 = 1;
                    v125 = v158;
                    v141 = v58;
                    v140 = v59;
                    v60 = v58 * -v50;
                    do {
                      v166 = ((_BYTE)v166 + 1) & 0x1F;
                      v167 = 28 * v166;
                      *(int *)((char *)&enginedelay[7 * v166] + v125) = (v59 - v60) / v52;
                      v59 += v140;
                      v60 += v141;
                      ++v117;
                    } while (v50 >= v117);
                  }
                  if (enginedelay_variable_3[v157 / 4] == -1 || enginedelay_variable_3[v128 / 4 + v158 / 4] == -1) {
                    v61 = v131;
                    if (v51 != v131) {
                      v62 = v158;
                      do {
                        *(int *)((char *)&enginedelay_variable_3[7 * v61] + v62) = -1;
                        v61 = ((_BYTE)v61 + 1) & 0x1F;
                      } while (v61 != v51);
                    }
                  } else {
                    LOBYTE(v63) = v120;
                    v64 = enginedelay_variable_3[v128 / 4 + v158 / 4];
                    v65 = enginedelay_variable_3[v157 / 4];
                    v162 = 1;
                    v133 = v158;
                    v144 = v64;
                    v142 = v65;
                    v143 = v64 * -v50;
                    do {
                      v63 = ((_BYTE)v63 + 1) & 0x1F;
                      v167 = 28 * v63;
                      *(int *)((char *)&enginedelay_variable_3[7 * v63] + v133) = (v65 - v143) / v52;
                      v65 += v142;
                      v143 += v144;
                      ++v162;
                    } while (v50 >= v162);
                    v66 = *(int *)((char *)&enginedelay_variable_2[v128 / 4] + v133);
                    v67 = *(int *)((char *)&enginedelay_variable_2[v129 / 4] + v133);
                    v68 = 1;
                    v165 = v120;
                    v126 = v158;
                    v146 = v67;
                    v147 = v66;
                    v145 = v67;
                    v69 = v66 * -v50;
                    do {
                      v165 = ((_BYTE)v165 + 1) & 0x1F;
                      v167 = 28 * v165;
                      *(int *)((char *)&enginedelay_variable_2[7 * v165] + v126) = (v145 - v69) / v52;
                      ++v68;
                      v145 += v146;
                      v69 += v147;
                    } while (v68 <= v50);
                  }
                  if (enginedelay_variable_5[v157 / 4] == -1 || enginedelay_variable_5[v128 / 4 + v158 / 4] == -1) {
                    v70 = v131;
                    if (v51 != v131) {
                      v71 = v158;
                      do {
                        *(int *)((char *)&enginedelay_variable_5[7 * v70] + v71) = -1;
                        v70 = ((_BYTE)v70 + 1) & 0x1F;
                      } while (v70 != v51);
                    }
                  } else {
                    v164 = v120;
                    v72 = enginedelay_variable_5[v128 / 4 + v158 / 4];
                    v73 = enginedelay_variable_5[v157 / 4];
                    v116 = 1;
                    v134 = v158;
                    v149 = v72;
                    v148 = v73;
                    v74 = v72 * -v50;
                    do {
                      v164 = ((_BYTE)v164 + 1) & 0x1F;
                      v167 = 28 * v164;
                      *(int *)((char *)&enginedelay_variable_5[7 * v164] + v134) = (v73 - v74) / v52;
                      v73 += v148;
                      v74 += v149;
                      ++v116;
                    } while (v50 >= v116);
                    v75 = *(int *)((char *)&enginedelay_variable_4[v128 / 4] + v134);
                    v76 = *(int *)((char *)&enginedelay_variable_4[v129 / 4] + v134);
                    v77 = 1;
                    v163 = v120;
                    v127 = v158;
                    v151 = v76;
                    v152 = v75;
                    v150 = v76;
                    v78 = v75 * -v50;
                    do {
                      v163 = ((_BYTE)v163 + 1) & 0x1F;
                      v167 = 28 * v163;
                      *(int *)((char *)&enginedelay_variable_4[7 * v163] + v127) = (v150 - v78) / v52;
                      ++v77;
                      v150 += v151;
                      v78 += v152;
                    } while (v77 <= v50);
                  }
                  LOBYTE(v79) = v120;
                  v80 = enginedelay_variable_6[v114 / 4];
                  v154 = enginedelay_variable_6[v157 / 4];
                  v153 = v154;
                  v155 = v80;
                  v115 = 1;
                  v135 = v158;
                  v81 = v80 * -v50;
                  do {
                    v79 = ((_BYTE)v79 + 1) & 0x1F;
                    v167 = 28 * v79;
                    *(int *)((char *)&enginedelay_variable_6[7 * v79] + v135) = (v153 - v81) / v52;
                    v153 += v154;
                    v81 += v155;
                    ++v115;
                  } while (v50 >= v115);
                  v82 = *(int *)((char *)&enginedelay_variable_6[v128 / 4] + v135);
                  v83 = *(int *)((char *)&enginedelay_variable_6[v129 / 4] + v135);
                  LOBYTE(v84) = v120;
                  v161 = 1;
                  v130 = v158;
                  v113 = v82;
                  v111 = v83;
                  v112 = v82 * -v50;
                  do {
                    v84 = ((_BYTE)v84 + 1) & 0x1F;
                    v167 = 28 * v84;
                    *(int *)((char *)&enginedelay_variable_6[7 * v84] + v130) = (v83 - v112) / v52;
                    v83 += v111;
                    v112 += v113;
                    ++v161;
                  } while (v50 >= v161);
                }
                v156 += 4;
                v157 += 896;
                v158 += 896;
                v114 += 896;
              } while (v156 < v159);
            }
          }
          if (!rewinding && !forwarding && replayspeed) {
            v85 = -1;
            if (cuts) {
              v86 = 0;
              if (cuts > 0) {
                v87 = 0;
                do {
                  if (currentreplayframe >= *(int *)((char *)&camera_variable_2 + v87))
                    v85 = v86;
                  ++v86;
                  v87 += 6;
                } while (v86 < cuts);
              }
            }
            if (v85 != -1
              && v85 != lastautocut
              && ((unsigned __int8)camera[6 * v85] != SelectedView[0]
                  || (unsigned __int8)camera_variable_1[6 * v85] != ViewType[0])
              && autoswitch) {
              SelectedView[0] = (unsigned __int8)camera[6 * v85];
              ViewType[0] = (unsigned __int8)camera_variable_1[6 * v85];
              select_view(0);
              lastautocut = v85;
              pend_view_init = ViewType[0];
            }
          }
          if (pend_view_init != -1) {
            if (Play_View == 1) {
              ViewType[0] = pend_view_init;
              doteaminit();
            } else {
              initcarview(pend_view_init, 0);
              ViewType[0] = pend_view_init;
            }
            pend_view_init = -1;
          }
          if (lastreplayframe != -1)
            doviewtend((int)&Car[77 * ViewType[0]], abs32(lastreplayframe - currentreplayframe), 0);
          v88 = abs32(currentreplayframe - lastreplayframe);
          if (v88 > 16)
            v88 = 16;
          v89 = 0;
          if (numcars > 0) {
            v90 = Car;
            do {
              for (m = 0; m < v88; ++m)
                updatesmokeandflames((int)v90);
              ++v89;
              v90 += 77;
            } while (v89 < numcars);
          }
          if (replayspeed < 0) {
            v92 = 0;
            if (numcars > 0) {
              v93 = 1408;
              v94 = 0;
              do {
                if (Car_variable_21[v94] > 126) {
                  v95 = 1408 * v92;
                  do {
                    v95 += 44;
                    car_texs_loaded_variable_2[v95 / 4] = 0;
                  } while (v95 != v93);
                }
                v94 += 154;
                ++v92;
                v93 += 1408;
              } while (v92 < numcars);
            }
          }
          result = currentreplayframe;
          lastreplayframe = currentreplayframe;
        }
        if (v121 || forwarding || rewinding) {
          result = 16;
          qmemcpy(repsample, newrepsample, sizeof(repsample));
        }
      }
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00065BF0
void Rplay()
{
  if (replaytype == 2) {
    // Play sound effect sample 83 at 50% volume (0x8000)
    // Volume 0x8000 = 32768, which is 50 % of full 16-bit volume
    sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);

    // Init replay state
    replaydirection = 1;
    lastautocut = -1;

    // Set replay speed
    replayspeed = replayspeeds[replaysetspeed];

    // copy newrepsample into repsample
    memcpy(repsample, newrepsample, sizeof(repsample));

    // Initialize sound timing if playing at normal speed (0x100 is 1.0 in 8.8 fixed float)
    if (replayspeed == 0x100)
      initsoundlag(currentreplayframe);
  }
}

//-------------------------------------------------------------------------------------------------
//00065C70
void Rreverseplay()
{
  int iCurrSpeed; // eax

  if (replaytype == 2) {
    sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);                      // SOUND_SAMPLE_BUTTON
    iCurrSpeed = replayspeeds[replaysetspeed];
    replaydirection = -1;
    lastautocut = -1;
    replayspeed = -iCurrSpeed;
  }
}

//-------------------------------------------------------------------------------------------------
//00065CC0
void Rframeplus()
{
  if (replaytype == 2) {
    sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);                      // SOUND_SAMPLE_BUTTON
    //_disable();
    replayspeed = 0;
    fraction = 0;
    replaydirection = 0;
    if (replayframes - 1 < ++ticks)
      ticks = replayframes - 1;
    //_enable();
  }
}

//-------------------------------------------------------------------------------------------------
//00065D20
void Rframeminus()
{
  if (replaytype == 2) {
    sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);                      // SOUND_SAMPLE_BUTTON
    //_disable();
    replayspeed = 0;
    fraction = 0;
    replaydirection = 0;
    if (--ticks < 0)
      ticks = 0;
    //_enable();
  }
}

//-------------------------------------------------------------------------------------------------
//00065D70
void Rspeedplus()
{
  int iNewSpeed; // eax

  if (replaytype == 2) {
    sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);                      // SOUND_SAMPLE_BUTTON
    if (++replaysetspeed == 9)
      replaysetspeed = 8;
    if (replayspeed) {
      if (replayspeed >= 0) {
        iNewSpeed = replayspeeds[replaysetspeed];
      } else {
        replayspeed = replayspeeds[replaysetspeed];
        iNewSpeed = -replayspeed;
      }
      replayspeed = iNewSpeed;
    }
    if (replayspeed == 256)
      initsoundlag(currentreplayframe);
  }
}

//-------------------------------------------------------------------------------------------------
//00065E00
void Rspeedminus()
{
  int iNewSpeed; // eax

  if (replaytype == 2) {
    sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);                      // SOUND_SAMPLE_BUTTON
    if (--replaysetspeed < 0)
      replaysetspeed = 0;
    if (replayspeed) {
      if (replayspeed >= 0) {
        iNewSpeed = replayspeeds[replaysetspeed];
      } else {
        replayspeed = replayspeeds[replaysetspeed];
        iNewSpeed = -replayspeed;
      }
      replayspeed = iNewSpeed;
    }
    if (replayspeed == 256)
      initsoundlag(currentreplayframe);
  }
}

//-------------------------------------------------------------------------------------------------
//00065E90
void DoRstop()
{
  if (replaytype == 2) {
    //_disable();
    replayspeed = 0;
    fraction = 0;
    replaydirection = 0;
    ticks = currentreplayframe;
    //_enable();
  }
  sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);                        // SOUND_SAMPLE_BUTTON
}

//-------------------------------------------------------------------------------------------------
//00065ED0
void Rstop()
{
  if (replaytype == 2) {
    //_disable();
    replayspeed = 0;
    fraction = 0;
    replaydirection = 0;
    ticks = currentreplayframe;
    //_enable();
  }
}

//-------------------------------------------------------------------------------------------------
//00065F00
void Rrewindstart()
{
  if (replaytype == 2) {
    sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);                      // SOUND_SAMPLE_BUTTON
    if (replayspeed >= 0)
      replayspeed = -64;
    rewinding = -1;
  }
}

//-------------------------------------------------------------------------------------------------
//00065F40
void Rforwardstart()
{
  if (replaytype == 2) {
    sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);                      // SOUND_SAMPLE_BUTTON
    if (replayspeed <= 0)
      replayspeed = 64;
    forwarding = -1;
  }
}

//-------------------------------------------------------------------------------------------------
//00065F80
void ROldStatus()
{
  if (replaytype == 2) {
    // Calculate effective replay speed (direction * base speed)
    replayspeed = replaydirection * replayspeeds[replaysetspeed];

    //cli(); //disable interrupts
    rewinding = 0;
    forwarding = 0;

    // Synchronize timing system with replay position
    ticks = currentreplayframe;
    fraction = 0;

    //if playing at normal speed (0x100 is 1.0 in 8.8 fixed float)
    if (replayspeed == 0x100)
      Rplay(); //Initialize replay playback
    //sti() //enable interrupts
  }
}

//-------------------------------------------------------------------------------------------------
//00065FE0
void Rstart()
{
  if (ticks) {
    if (replaytype == 2) {
      //_disable();
      replayspeed = 0;
      replaydirection = 0;
      fraction = 0;
      ticks = 0;
      //_enable();
      pend_view_init = ViewType[0];
      sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);
      resetsmoke();
    }
  }
}

//-------------------------------------------------------------------------------------------------
//00066040
void Rend()
{
  if (replayframes - 1 != ticks && replaytype == 2) {
    //_disable();
    replayspeed = 0;
    replaydirection = 0;
    fraction = 0;
    ticks = replayframes - 1;
    //_enable();
    pend_view_init = ViewType[0];
    sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);                      // SOUND_SAMPLE_BUTTON
    resetsmoke();
  }
}

//-------------------------------------------------------------------------------------------------
//000660A0
unsigned int readdisable(int iFrame)
{
  char byBitPosition; // bl
  int iArrayIndex; // eax

  byBitPosition = iFrame;
  if (!replayedit || iFrame > 0x1FFFF)
    return 0;
  iArrayIndex = iFrame / 32;  // Calculate array index: divide by 32 to get DWORD index
  //iArrayIndex = (iFrame - (__CFSHL__(iFrame >> 31, 5) + 32 * (iFrame >> 31))) >> 5;
  return ((unsigned int)disabled[iArrayIndex] >> (byBitPosition - 32 * iArrayIndex)) & 1;
}

//-------------------------------------------------------------------------------------------------
//000660F0
void cleardisable(int iFrame)
{
  char byBitPosition; // bl
  int iArrayIndex; // eax

  byBitPosition = iFrame;                 // Store lower 8 bits of replay index for bit position calculation
  if (iFrame < 0x20000)                 // Check if replay index is within valid range (0-131071)
  {
    iArrayIndex = iFrame / 32;  // Calculate array index: divide by 32 to get DWORD index
    //iArrayIndex = (iFrame - (__CFSHL__(iFrame >> 31, 5) + 32 * (iFrame >> 31))) >> 5;// Calculate array index: divide by 32 to get DWORD index
    disabled[iArrayIndex] &= ~(1 << (byBitPosition - 32 * iArrayIndex));// Clear the specific bit using AND with inverted bit mask
  }
}

//-------------------------------------------------------------------------------------------------
//00066130
void setdisable(int iFrame)
{
  char byBitPosition; // bl
  int iArrayIndex; // eax

  byBitPosition = iFrame;
  if (iFrame < 0x20000) {
    iArrayIndex = iFrame / 32;  // Calculate array index: divide by 32 to get DWORD index
    //iArrayIndex = (iFrame - (__CFSHL__(iFrame >> 31, 5) + 32 * (iFrame >> 31))) >> 5;
    disabled[iArrayIndex] |= 1 << (byBitPosition - 32 * iArrayIndex);
  }
}

//-------------------------------------------------------------------------------------------------
//00066170
int deleteframes(int result, int a2)
{
  return 0; /*
  int v2; // esi
  int v3; // ebx
  int i; // ebx

  v2 = a2;
  if (replaytype == 2) {
    if (a2 < result) {
      v3 = result;
      result = a2;
      v2 = v3;
    }
    for (i = result; i <= v2; ++i) {
      if (i < 0x20000) {
        result = (i - (__CFSHL__(i >> 31, 5) + 32 * (i >> 31))) >> 5;
        disabled[result] |= 1 << (i - 32 * result);
      }
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//000661E0
int undeleteframes(int result, int a2)
{
  return 0; /*
  int v2; // ebx
  int v3; // edx
  int i; // edx
  int v5; // eax

  v2 = a2;
  if (replaytype == 2) {
    if (a2 < result) {
      v3 = result;
      result = v2;
      v2 = v3;
    }
    for (i = result; i <= v2; result = cleardisable(v5))
      v5 = i++;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00066210
void findnextvalid()
{/*
  int v0; // ebx
  int i; // edx
  unsigned int v2; // eax
  int v3; // edx
  unsigned int v4; // eax

  v0 = currentreplayframe;
  for (i = currentreplayframe + 1; currentreplayframe + 1 < replayframes; i = currentreplayframe + 1) {
    currentreplayframe = i;
    v2 = readdisable(i);
    i = currentreplayframe;
    if (!v2)
      break;
  }
  if (i == replayframes) {
    v3 = v0 - 1;
    if (v0 - 1 >= 0) {
      do {
        currentreplayframe = v3;
        v4 = readdisable(v3);
        v3 = currentreplayframe;
        if (!v4)
          break;
        v3 = currentreplayframe - 1;
      } while (currentreplayframe - 1 >= 0);
    }
    if (v3 < 0)
      v3 = v0;
    if (replaytype == 2) {
      currentreplayframe = v3;
      _disable();
      replayspeed = 0;
      fraction = 0;
      replaydirection = 0;
      ticks = currentreplayframe;
      _enable();
      v3 = currentreplayframe;
    }
  } else {
    currentreplayframe = i;
    _disable();
    ticks = currentreplayframe;
    fraction = 0;
    _enable();
    v3 = currentreplayframe;
    if (v0 != currentreplayframe)
      pend_view_init = ViewType[0];
  }
  currentreplayframe = v3;*/
}

//-------------------------------------------------------------------------------------------------
//00066300
unsigned int findlastvalid()
{
  return 0; /*
  int v0; // ebx
  int i; // edx
  unsigned int result; // eax
  int v3; // edx

  v0 = currentreplayframe;
  for (i = currentreplayframe - 1; currentreplayframe - 1 >= 0; i = currentreplayframe - 1) {
    currentreplayframe = i;
    result = readdisable(i);
    i = currentreplayframe;
    if (!result)
      break;
  }
  if (i >= 0) {
    currentreplayframe = i;
    _disable();
    ticks = currentreplayframe;
    fraction = 0;
    _enable();
    v3 = currentreplayframe;
    if (v0 != currentreplayframe) {
      result = ViewType[0];
      pend_view_init = ViewType[0];
    }
  } else {
    v3 = v0 + 1;
    if (v0 + 1 < replayframes) {
      do {
        currentreplayframe = v3;
        result = readdisable(v3);
        v3 = currentreplayframe;
        if (!result)
          break;
        v3 = currentreplayframe + 1;
      } while (currentreplayframe + 1 < replayframes);
    }
    if (v3 == replayframes)
      v3 = v0;
    if (replaytype == 2) {
      currentreplayframe = v3;
      _disable();
      replayspeed = 0;
      fraction = 0;
      replaydirection = 0;
      ticks = currentreplayframe;
      _enable();
      v3 = currentreplayframe;
    }
  }
  currentreplayframe = v3;
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//000663F0
void Rassemble()
{/*
  int v0; // eax
  int v1; // ebp
  int v2; // edx
  char *v3; // esi
  char *v4; // edi
  char v5; // al
  char v6; // al
  char *v7; // esi
  char *v8; // edi
  char v9; // al
  char v10; // al
  int v11; // esi
  int v12; // eax
  int v13; // eax
  int v14; // ebp
  int v15; // esi
  int v16; // edi
  int i; // edx
  int v18; // edx
  int v19; // eax
  int v20; // eax
  char *v21; // eax
  int v22; // ecx
  int v23; // eax
  int v24; // eax
  int v25; // edx
  char *v26; // ebx
  int v27; // ecx
  int v28; // ebp
  int j; // edi
  int v30; // eax
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // edi
  int v35; // eax
  int v36; // ebx
  int v37; // edx
  int v38; // ecx
  int v39; // ebx
  int v40; // edx
  int v41; // ecx
  char v42; // al
  char v43; // ah
  char v44; // al
  int v45; // esi
  int v46; // eax
  int v47; // eax
  int v48; // esi
  int v49; // eax
  _DWORD v50[32]; // [esp+0h] [ebp-134h]
  char v51[64]; // [esp+80h] [ebp-B4h] BYREF
  _BYTE v52[16]; // [esp+C0h] [ebp-74h] BYREF
  int v53; // [esp+D0h] [ebp-64h]
  int v54; // [esp+D4h] [ebp-60h]
  int v55; // [esp+D8h] [ebp-5Ch]
  int v56; // [esp+DCh] [ebp-58h]
  int v57; // [esp+E0h] [ebp-54h]
  int v58; // [esp+E4h] [ebp-50h]
  int v59; // [esp+E8h] [ebp-4Ch]
  char *v60; // [esp+ECh] [ebp-48h]
  int v61; // [esp+F0h] [ebp-44h]
  int v62; // [esp+F4h] [ebp-40h]
  int v63; // [esp+F8h] [ebp-3Ch]
  int v64; // [esp+FCh] [ebp-38h]
  int k; // [esp+100h] [ebp-34h]
  int v66; // [esp+104h] [ebp-30h]
  int v67; // [esp+108h] [ebp-2Ch]
  int v68; // [esp+10Ch] [ebp-28h]
  int v69; // [esp+110h] [ebp-24h]
  _BYTE v70[32]; // [esp+114h] [ebp-20h] BYREF

  v64 = 0;
  v55 = 0;
  if (replaytype == 2) {
    memset(v52, 0, sizeof(v52));
    v59 = scrbuf;
    v0 = 0;
    if (numcars > 0) {
      v1 = numcars;
      v2 = 0;
      do {
        ++v2;
        v51[v0++ + 32] = 1;
        v50[v2 + 15] = 1;
      } while (v0 < v1);
    }
    _disable();
    v67 = -1;
    replayspeed = 0;
    replaydirection = 0;
    fraction = 0;
    ticks = currentreplayframe;
    _enable();
    strcpy(v51, "..\\REPLAYS\\");
    v3 = &selectfilename;
    v4 = &v51[strlen(v51)];
    do {
      v5 = *v3;
      *v4 = *v3;
      if (!v5)
        break;
      v6 = v3[1];
      v3 += 2;
      v4[1] = v6;
      v4 += 2;
    } while (v6);
    v7 = aGss;
    v8 = &v51[strlen(v51)];
    do {
      v9 = *v7;
      *v8 = *v7;
      if (!v9)
        break;
      v10 = v7[1];
      v7 += 2;
      v8[1] = v10;
      v8 += 2;
    } while (v10);
    if (!strcmp(v51, replayfilename)) {
      lastfile = 0;
      screenready = 0;
      filingmenu = 9;
    } else {
      v11 = fopen(v51, &aYwb[1]);
      v66 = v11;
      if (v11) {
        fseek(replayfile, 0, 0);
        fread(v59, 1, replayheader, replayfile);
        v12 = fwrite(v59, 1, replayheader, v11);
        if (v12 != replayheader) {
          v13 = *(_DWORD *)_get_errno_ptr(v12);
          v55 = -1;
          v54 = v13;
        }
        v14 = 0;
        v62 = -1;
        v15 = 0;
        v58 = 64000 / replayblock;
        v53 = 0;
        fseek(v66, 4, 0);
        v63 = 0;
        if (cuts > 0) {
          v60 = camera;
          v61 = -4;
          v16 = 0;
          do {
            for (i = v14; i < *(int *)((char *)&camera_variable_2 + v16); ++i) {
              if (!readdisable(i))
                ++v15;
            }
            v14 = *(int *)((char *)&camera_variable_2 + v16);
            v57 = v14;
            if (v62 == -1 || v15 != v62) {
              v21 = v60;
              v22 = v66;
              *(int *)((char *)&camera_variable_2 + v16) = v15;
              v23 = fwrite(v21, 1, 6, v22);
              if (v23 != 6) {
                v24 = *(_DWORD *)_get_errno_ptr(v23);
                v55 = -1;
                v54 = v24;
              }
              v62 = v15;
              v61 += 6;
              ++v53;
            } else {
              v18 = v61;
              *(int *)((char *)&camera_variable_2 + v16) = v62;
              fseek(v66, v18, 0);
              v19 = fwrite(&camera[v16], 1, 6, v66);
              if (v19 != 6) {
                v20 = *(_DWORD *)_get_errno_ptr(v19);
                v55 = -1;
                v54 = v20;
              }
            }
            v25 = cuts;
            v16 += 6;
            v26 = v60 + 6;
            v27 = v63 + 1;
            *(int *)((char *)&yp_variable_1 + v16) = v57;
            v60 = v26;
            v63 = v27;
          } while (v27 < v25);
        }
        v28 = 100 - v53;
        for (j = 0; j < v28; ++j) {
          v30 = fwrite(v52, 1, 6, v66);
          if (v30 != 6) {
            v31 = *(_DWORD *)_get_errno_ptr(v30);
            v55 = -1;
            v54 = v31;
          }
        }
        v70[0] = v53;
        v32 = fwrite(v70, 1, 1, v66);
        if (v32 != 1) {
          v33 = *(_DWORD *)_get_errno_ptr(v32);
          v55 = -1;
          v54 = v33;
        }
        fseek(v66, replayheader, 0);
        v68 = 0;
        do {
          v34 = v59;
          v35 = fread(v59, replayblock, v58, replayfile);
          v69 = 0;
          for (k = v35; v69 < k; ++v69) {
            if (readdisable(v68)) {
              v67 = -1;
            } else {
              if (v67) {
                v36 = v34;
                v37 = 0;
                if (numcars > 0) {
                  v38 = 0;
                  do {
                    v50[v38] = (((int)*(unsigned __int8 *)(v36 + 26) >> 3) & 1) == v50[v38 + 16];
                    v56 = (unsigned __int8)HIBYTE(*(_DWORD *)v36);
                    v70[4] = v56;
                    if ((char)v56 * v51[v37 + 32] >= 0)
                      v51[v37 + 48] = 1;
                    else
                      v51[v37 + 48] = -1;
                    v36 += 30;
                    ++v37;
                    ++v38;
                  } while (v37 < numcars);
                }
                v67 = 0;
              }
              v39 = v34;
              v40 = 0;
              if (numcars > 0) {
                v41 = 0;
                do {
                  *(_BYTE *)(v39 + 26) ^= 8 * LOBYTE(v50[v41]);
                  v50[v41 + 16] = ((int)*(unsigned __int8 *)(v39 + 26) >> 3) & 1;
                  v56 = (unsigned __int8)HIBYTE(*(_DWORD *)v39);
                  v42 = v56;
                  v43 = v51[v40 + 48];
                  v51[v40 + 32] = v56;
                  v44 = v43 * v42;
                  v39 += 30;
                  ++v41;
                  v51[v40++ + 32] = v44;
                  v45 = numcars;
                  *(_DWORD *)(v39 - 30) = (v44 << 24) | *(_DWORD *)(v39 - 30) & 0xFFFFFF;
                } while (v40 < v45);
              }
              v64 = -1;
              v46 = fwrite(v34, 1, replayblock, v66);
              if (v46 != replayblock) {
                v47 = *(_DWORD *)_get_errno_ptr(v46);
                v55 = -1;
                v54 = v47;
              }
            }
            v34 += replayblock;
            ++v68;
          }
        } while (k == v58 && !v55);
        v48 = v64;
        v49 = fclose(v66);
        if (!v48) {
          *(_DWORD *)_get_errno_ptr(v49) = -1000;
          v55 = -1;
        }
        if (v55)
          remove(v51);
      }
      filingmenu = 0;
      lastfile = 0;
      screenready = 0;
    }
  }
  if (v55) {
    if (v54 == 12) {
      filingmenu = 6;
    } else if (v54 == -1000) {
      filingmenu = 8;
    } else {
      filingmenu = 7;
    }
  }*/
}

//-------------------------------------------------------------------------------------------------
//00066AF0
void storecut()
{
  int iNumCuts; // esi
  int iTargetFrame; // edi
  int iInsertIndex; // ecx
  int iCutCounter; // eax
  int iCameraIndex; // edx
  int iStoreIndex; // eax

  iNumCuts = cuts;                              // Initialize working variables
  iTargetFrame = currentreplayframe;
  if (replaytype == 2 && cuts < 100)          // Only allow cut creation in edit mode and under limit (100 cuts max)
  {
    iInsertIndex = -1;                          // Initialize insertion index to -1 (no position found yet)
    if (cuts)                                 // Search for correct insertion position if cuts exist
    {
      iCutCounter = 0;
      if (cuts > 0) {
        iCameraIndex = 0;                       // Find the last cut that occurs before or at current frame
        do {                                       // Check if this cut frame is <= current frame
          if (camera[iCameraIndex].iFrame <= currentreplayframe)
            iInsertIndex = iCutCounter;
          ++iCutCounter;
          ++iCameraIndex;
        } while (iCutCounter < cuts);
      }
      if (camera[iInsertIndex].iFrame != currentreplayframe || iInsertIndex == -1)// Check if cut already exists at this frame
      {                                         // Calculate insertion position (after last matching cut)
        if (++iInsertIndex != cuts) {
          memmove(&camera[iInsertIndex + 1], &camera[iInsertIndex], 6 * (cuts - iInsertIndex));// Shift existing cuts up to make room for new cut
          iNumCuts = cuts;
        }
        iTargetFrame = currentreplayframe;      // Increment cut count for new cut
        ++iNumCuts;
      }
    } else {
      iNumCuts = 1;                             // First cut - set count to 1 and insert at position 0
      iInsertIndex = 0;
    }
    iStoreIndex = iInsertIndex;                 // Store cut data at calculated index
    camera[iStoreIndex].byView = SelectedView[0];// Store current view settings
    camera[iStoreIndex].iFrame = iTargetFrame;  // Store current frame number
    camera[iStoreIndex].byCarIdx = (uint8)ViewType[0]; // Store current car index for view
  }
  currentreplayframe = iTargetFrame;            // Update global state
  cuts = iNumCuts;
}

//-------------------------------------------------------------------------------------------------
//00066BE0
void removecut()
{
  int iNumCuts; // esi
  int iCutIndex; // ecx
  int iCameraIndex; // edi

  iNumCuts = cuts;                              // Get current number of cuts
  if (replaytype == 2)                        // Only allow cut removal in edit mode (replaytype == 2)
  {
    iCutIndex = 0;
    if (cuts > 0)                             // Search through existing cuts to find match
    {
      iCameraIndex = 0;
      do {                                         // Check if current replay frame matches this cut frame
        if (currentreplayframe == camera[iCameraIndex].iFrame) {                                       // If not the last cut, shift remaining cuts down to fill gap
          if (iCutIndex != iNumCuts - 1) {
            cuts = iNumCuts;
            memmove(&camera[iCameraIndex], &camera[iCameraIndex + 1], 6 * (iNumCuts - iCutIndex - 1));// Move remaining cuts down by 6 bytes each (camera struct size)
            iNumCuts = cuts;
          }
          --iNumCuts;                           // Decrement total cut count
        }
        ++iCutIndex;
        ++iCameraIndex;
      } while (iCutIndex < iNumCuts);
    }
  }
  cuts = iNumCuts;                              // Update global cuts count
}

//-------------------------------------------------------------------------------------------------
//00066C50
int readcut()
{
  return 0; /*
  int v0; // ecx
  int v1; // eax
  int v2; // edx

  v0 = -1;
  if (cuts) {
    v1 = 0;
    if (cuts > 0) {
      v2 = 0;
      do {
        if (*(int *)((char *)&camera_variable_2 + v2) <= currentreplayframe)
          v0 = v1;
        ++v1;
        v2 += 6;
      } while (v1 < cuts);
    }
  }
  return v0;*/
}

//-------------------------------------------------------------------------------------------------
//00066CC0
int displayreplay()
{
  return 0; /*
  int v0; // edi
  int v1; // esi
  int i; // ecx
  int j; // eax
  int v4; // edx
  int v5; // ecx
  int v6; // eax
  int result; // eax

  if (replaytype == 2 && readdisable(currentreplayframe)) {
    v0 = scrbuf;
    v1 = winw;
    for (i = 0; i < winh; i += 2) {
      for (j = 0; j < v1; *(_BYTE *)(v4 + v1 * i) = 0) {
        v4 = v0 + j;
        j += 2;
      }
    }
    v5 = 1;
    winw = v1;
    scrbuf = v0;
    while (v5 < winh) {
      v6 = scrbuf + winw * v5;
      v5 += 2;
      memset(v6, 0, winw);
    }
  }
  if (filingmenu) {
    switch (filingmenu) {
      case 1:
        fileselect(160, 20, &language_buffer_variable_49, aReplaysGss, 1);
        break;
      case 2:
        fileselect(160, 20, &language_buffer_variable_50, aReplaysGss, 2);
        break;
      case 3:
        fileselect(160, 20, &language_buffer_variable_51, aReplaysGss, 3);
        break;
      case 4:
        fileselect(160, 20, &language_buffer_variable_53, aReplaysGss, 4);
        break;
      case 5:
        lsd(40, 37, 280, 107);
        break;
      case 6:
        warning(&language_buffer_variable_54);
        break;
      case 7:
        warning(language_buffer_variable_55);
        break;
      case 8:
        warning(&language_buffer_variable_56);
        break;
      case 9:
        warning(language_buffer_variable_57);
        break;
      default:
        break;
    }
  }
  if (replaypanel) {
    if ((!SVGA_ON || scr_size != 128) && (SVGA_ON || scr_size != 64)) {
      replaypanel = 0;
      controlicon = 9;
    }
  }
  result = replaypanel;
  if (replaypanel)
    return displaycontrolpanel();
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00066F60
// attributes: thunk
int compare(int a1, int a2)
{
  return 0; /*
  return strcmp(a1, a2);*/
}

//-------------------------------------------------------------------------------------------------
//00066F70
int warning(int a1, int a2, int a3, int a4, char *a5)
{
  return 0; /*
  int v5; // esi
  int v6; // edi
  int result; // eax
  _DWORD v8[14]; // [esp+0h] [ebp-38h] BYREF

  v5 = a1;
  v6 = a2;
  if (SVGA_ON) {
    a3 *= 2;
    a2 *= 2;
    v5 = 2 * a1;
    a4 *= 2;
  }
  v8[2] = a3;
  v8[3] = a2;
  v8[4] = v5;
  v8[5] = a2;
  v8[6] = v5;
  v8[7] = a4;
  v8[8] = a3;
  v8[9] = a4;
  v8[0] = 2097155;
  v8[1] = 4;
  POLYFLAT(scrbuf, v8);
  prt_centrecol(rev_vga_variable_1, a5, (v5 + a3) / 2, v6 + 10, 231);
  result = fatkbhit();
  if (result) {
    while (1) {
      result = fatkbhit();
      if (!result)
        break;
      fatgetch();
    }
    filingmenu = 0;
    disciconpressed = 0;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00067020
char lsd(int a1, int a2, int a3, int a4)
{
  return 0; /*
  int v4; // esi
  unsigned __int8 v5; // al
  unsigned __int8 v6; // al
  int v7; // ebp
  char *v8; // edi
  char *v9; // esi
  char v10; // al
  char v11; // al
  char result; // al
  char v13; // [esp-4h] [ebp-40h]
  __int64 v14; // [esp+0h] [ebp-3Ch] BYREF
  int v15; // [esp+8h] [ebp-34h]
  int v16; // [esp+Ch] [ebp-30h]
  int v17; // [esp+10h] [ebp-2Ch]
  int v18; // [esp+14h] [ebp-28h]
  int v19; // [esp+18h] [ebp-24h]
  int v20; // [esp+1Ch] [ebp-20h]
  int v21; // [esp+20h] [ebp-1Ch]
  int v22; // [esp+24h] [ebp-18h]
  int v23; // [esp+2Ch] [ebp-10h]

  v4 = a2;
  if (SVGA_ON) {
    a3 *= 2;
    a2 *= 2;
    a1 *= 2;
    a4 *= 2;
  }
  v15 = a3;
  v16 = a2;
  v17 = a1;
  v18 = a2;
  v19 = a1;
  v20 = a4;
  v21 = a3;
  v22 = a4;
  v14 = 0x400200003LL;
  POLYFLAT(scrbuf, &v14);
  prt_centrecol(rev_vga_variable_1, language_buffer_variable_48, 160, v4 + 10, 231);
  while (fatkbhit()) {
    v5 = fatgetch();
    if (v5) {
      if (v5 >= 0xDu) {
        if (v5 <= 0xDu) {
          sfxsample(v14);
          filingmenu = lsdsel + 1;
        } else if (v5 == 27) {
          filingmenu = 0;
          disciconpressed = 0;
          rotpoint = currentreplayframe;
        }
      }
    } else {
      v6 = fatgetch();
      if (v6 >= 0x48u) {
        if (v6 <= 0x48u) {
          if (lsdsel)
            --lsdsel;
        } else if (v6 == 80 && lsdsel < 2) {
          ++lsdsel;
        }
      }
    }
  }
  v7 = 0;
  v23 = v4 + 30;
  do {
    if (v7) {
      if ((unsigned int)v7 <= 1) {
        v8 = buffer;
        v9 = (char *)&language_buffer_variable_50;
      } else {
        if (v7 != 2)
          goto LABEL_30;
        v8 = buffer;
        v9 = (char *)&language_buffer_variable_51;
      }
    } else {
      v8 = buffer;
      v9 = (char *)&language_buffer_variable_49;
    }
    do {
      v10 = *v9;
      *v8 = *v9;
      if (!v10)
        break;
      v11 = v9[1];
      v9 += 2;
      v8[1] = v11;
      v8 += 2;
    } while (v11);
  LABEL_30:
    if (v7 == lsdsel)
      v13 = -113;
    else
      v13 = -125;
    result = prt_centrecol(rev_vga_variable_1, buffer, 160, v23, v13);
    ++v7;
    v23 += 10;
  } while (v7 < 3);
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//000671D0
int scandirectory(int a1)
{
  return 0; /*
  int v1; // ebp
  char *v2; // eax
  int v3; // edx
  char v4; // bl
  int v5; // eax
  int v7; // [esp+0h] [ebp-44h] BYREF
  char v8; // [esp+1Eh] [ebp-26h] BYREF

  v1 = 0;
  if (!dos_findfirst(a1)) {
    do {
      if (v1 >= 500)
        break;
      v2 = &v8;
      v3 = 0;
      if (v8) {
        do {
          if (*v2 == 46)
            break;
          v4 = *v2++;
          filename[9 * v1 + v3++] = v4;
        } while (*v2);
      }
      filename[9 * v1 + v3] = 0;
      filefiles = v1 + 1;
      v5 = dos_findnext(&v7);
      v1 = filefiles;
    } while (!v5);
  }
  filefiles = v1;
  return qsort(filename, v1, 9, compare);*/
}

//-------------------------------------------------------------------------------------------------
//000672C0
char fileselect(int a1, int a2, int a3, int a4, int a5, int a6, char *a7, int a8, int a9)
{
  return 0; /*
  int v9; // ebp
  char *v10; // edi
  char *v11; // esi
  char v12; // al
  char v13; // al
  char v14; // al
  char v15; // dl
  int v16; // ebp
  char *v17; // edi
  char *v18; // esi
  char v19; // al
  char v20; // al
  int v21; // ebp
  char *v22; // edi
  char *v23; // esi
  char v24; // al
  char v25; // al
  int v26; // ebp
  char *v27; // edi
  char *v28; // esi
  char v29; // al
  char v30; // al
  int v31; // ebp
  char *v32; // edi
  char *v33; // esi
  char v34; // al
  char v35; // al
  unsigned int v36; // kr08_4
  unsigned int v37; // kr0C_4
  int v38; // ecx
  int v39; // ebp
  int v40; // edi
  char *v41; // edx
  unsigned int v42; // kr14_4
  unsigned int v43; // ebx
  int v44; // esi
  char result; // al
  __int64 v46; // [esp+0h] [ebp-48h] BYREF
  int v47; // [esp+8h] [ebp-40h]
  int v48; // [esp+Ch] [ebp-3Ch]
  int v49; // [esp+10h] [ebp-38h]
  int v50; // [esp+14h] [ebp-34h]
  int v51; // [esp+18h] [ebp-30h]
  int v52; // [esp+1Ch] [ebp-2Ch]
  int v53; // [esp+20h] [ebp-28h]
  int v54; // [esp+24h] [ebp-24h]
  int v55; // [esp+2Ch] [ebp-1Ch]
  int v56; // [esp+30h] [ebp-18h]
  int v57; // [esp+34h] [ebp-14h]
  int v58; // [esp+38h] [ebp-10h]

  v57 = a1;
  if (filingmenu == 2 || filingmenu == 4)
    v56 = -1;
  else
    v56 = 0;
  if (SVGA_ON) {
    a3 *= 2;
    a2 *= 2;
    a4 *= 2;
    v57 *= 2;
  }
  v47 = a3;
  v48 = a2;
  v50 = a2;
  v52 = a4;
  v53 = a3;
  v54 = a4;
  v46 = 0x400200003LL;
  v49 = v57;
  v51 = v57;
  POLYFLAT(scrbuf, &v46);
  prt_centrecol(rev_vga_variable_1, a7, a5, a6, 231);
  if (a9 != lastfile) {
    topfile = 0;
    filefile = 0;
    scandirectory(a8);
    v9 = filefile;
    lastfile = a9;
    if (!filefiles)
      v9 = 0;
    if (v9 < topfile)
      topfile -= 3;
    if (v9 >= topfile + 18)
      topfile += 3;
    v10 = selectfilename;
    v11 = &filename[9 * v9];
    filefile = v9;
    do {
      v12 = *v11;
      *v10 = *v11;
      if (!v12)
        break;
      v13 = v11[1];
      v11 += 2;
      v10[1] = v13;
      v10 += 2;
    } while (v13);
  }
  while (fatkbhit()) {
    v14 = fatgetch();
    v15 = v14;
    if (v14) {
      if ((unsigned __int8)v14 < 0xDu) {
        if (v14 == 8) {
          v37 = strlen(selectfilename) + 1;
          if ((int)(v37 - 1) > 0)
            filesel_variable_1[v37 - 1] = 0;
        } else {
        LABEL_85:
          if ((unsigned __int8)v14 > 0x39u)
            v15 = v14 & 0xDF;
          v38 = strlen(selectfilename);
          if (v38 <= 7
            && ((unsigned __int8)v15 >= 0x41u && (unsigned __int8)v15 <= 0x5Au
                || (unsigned __int8)v15 >= 0x30u && (unsigned __int8)v15 <= 0x39u)) {
            selectfilename[v38] = v15;
            selectfilename_variable_1[v38] = 0;
          }
        }
      } else if ((unsigned __int8)v14 <= 0xDu) {
        sfxsample(v46);
        switch (filingmenu) {
          case 1:
            loadreplay();
            replayedit = 0;
            replayselect = 0;
            disciconpressed = 0;
            rotpoint = currentreplayframe;
            break;
          case 2:
            if (selectfilename[0]) {
              savereplay();
              disciconpressed = 0;
              rotpoint = currentreplayframe;
            }
            break;
          case 3:
            deletereplay();
            disciconpressed = 0;
            rotpoint = currentreplayframe;
            break;
          case 4:
            Rassemble();
            disciconpressed = 0;
            rotpoint = currentreplayframe;
            break;
          default:
            continue;
        }
      } else {
        if (v14 != 27)
          goto LABEL_85;
        filingmenu = 0;
        disciconpressed = 0;
        rotpoint = currentreplayframe;
      }
    } else {
      switch ((unsigned __int8)fatgetch()) {
        case 'H':
          v26 = filefile - 3;
          if (filefile - 3 < 0)
            v26 = 0;
          if (!filefiles)
            v26 = 0;
          if (v26 < topfile)
            topfile -= 3;
          if (v26 >= topfile + 18)
            topfile += 3;
          v27 = selectfilename;
          v28 = &filename[9 * v26];
          filefile = v26;
          do {
            v29 = *v28;
            *v27 = *v28;
            if (!v29)
              break;
            v30 = v28[1];
            v28 += 2;
            v27[1] = v30;
            v27 += 2;
          } while (v30);
          break;
        case 'K':
          v16 = filefile - 1;
          if (filefile - 1 < 0)
            v16 = 0;
          if (!filefiles)
            v16 = 0;
          if (v16 < topfile)
            topfile -= 3;
          if (v16 >= topfile + 18)
            topfile += 3;
          v17 = selectfilename;
          v18 = &filename[9 * v16];
          filefile = v16;
          do {
            v19 = *v18;
            *v17 = *v18;
            if (!v19)
              break;
            v20 = v18[1];
            v18 += 2;
            v17[1] = v20;
            v17 += 2;
          } while (v20);
          break;
        case 'M':
          v21 = filefile + 1;
          if (filefile + 1 >= filefiles)
            v21 = filefiles - 1;
          if (!filefiles)
            v21 = 0;
          if (v21 < topfile)
            topfile -= 3;
          if (v21 >= topfile + 18)
            topfile += 3;
          v22 = selectfilename;
          v23 = &filename[9 * v21];
          filefile = v21;
          do {
            v24 = *v23;
            *v22 = *v23;
            if (!v24)
              break;
            v25 = v23[1];
            v23 += 2;
            v22[1] = v25;
            v22 += 2;
          } while (v25);
          break;
        case 'P':
          v31 = filefile + 3;
          if (filefile + 3 >= filefiles)
            v31 = filefiles - 1;
          if (!filefiles)
            v31 = 0;
          if (v31 < topfile)
            topfile -= 3;
          if (v31 >= topfile + 18)
            topfile += 3;
          v32 = selectfilename;
          v33 = &filename[9 * v31];
          filefile = v31;
          do {
            v34 = *v33;
            *v32 = *v33;
            if (!v34)
              break;
            v35 = v33[1];
            v33 += 2;
            v32[1] = v35;
            v32 += 2;
          } while (v35);
          break;
        case 'S':
          v36 = strlen(selectfilename) + 1;
          if ((int)(v36 - 1) > 0)
            filesel_variable_1[v36 - 1] = 0;
          break;
        default:
          continue;
      }
    }
  }
  v55 = v57 + 20;
  v39 = filefile;
  v40 = 0;
  v58 = a6 + 20;
  do {
    filefile = v39;
    if (v40 + topfile < filefiles) {
      v41 = &filename[9 * v40 + 9 * topfile];
      if (v40 == v39 - topfile)
        prt_string(rev_vga_variable_1, v41);
      else
        prt_stringcol(rev_vga_variable_1, v41, 100 * (v40 % 3) + v55, v58 + 10 * (v40 / 3), 131);
    }
    ++v40;
    v39 = filefile;
  } while (v40 < 18);
  if (v56) {
    v42 = strlen(selectfilename) + 1;
    v43 = v42 - 1;
    if (frames % 18 >= 9) {
      selectfilename[v43] = 0;
    } else {
      selectfilename[v43] = 95;
      selectfilename_variable_1[v43] = 0;
    }
    prt_stringcol(rev_vga_variable_1, selectfilename, v57 + 20, a6 + 100, 255);
    selectfilename[v42 - 1] = 0;
  }
  if (SVGA_ON)
    v44 = 640;
  else
    v44 = 320;
  replayicon(a6 - 3, v44, 255);
  result = replayicon(a6 + 82, v44, 255);
  if (!filefiles)
    return prt_centrecol(rev_vga_variable_1, language_buffer_variable_52, a5, a6 + 44, 143);
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//000679E0
void previouscut()
{
  int iSearchFrame; // ebx
  int iCutIndex; // esi
  int iCutCounter; // edx
  int iCameraIndex; // eax
  int iFrame; // edi
  int iTargetFrame; // ebx
  unsigned int uiPrevDisabled; // edx
  unsigned int uiTempDisabled; // eax
  unsigned int uiCurrDisabled; // eax
  unsigned int uiCurrentDisabled; // ecx
  unsigned int uiTempPrevDisabled; // eax

  resetsmoke();                                 // Clear smoke effects for clean transition
  iSearchFrame = currentreplayframe;            // Start search from current frame or previous frame if possible
  if (currentreplayframe > 0)
    iSearchFrame = currentreplayframe - 1;
  iCutIndex = -1;                               // Initialize cut index to -1 (no cut found)
  if (cuts)                                   // Search through camera cuts if any exist
  {
    iCutCounter = 0;
    if (cuts > 0) {
      iCameraIndex = 0;                         // Find the last cut that occurs before or at search frame
      do {                                         // Check if this cut frame is <= search frame
        if (camera[iCameraIndex].iFrame <= iSearchFrame)
          iCutIndex = iCutCounter;
        ++iCutCounter;
        ++iCameraIndex;
      } while (iCutCounter < cuts);
    }
  }
  iFrame = iCutIndex;                           // Set target frame based on found cut
  if (iCutIndex != -1)                        // If cut found, use the cut frame as target
    iFrame = camera[iCutIndex].iFrame;
  if (iSearchFrame >= iFrame)                 // Search backwards from current position to find previous cut boundary
  {                                             // Get disable status of previous and current frames
    if (iSearchFrame) {
      currentreplayframe = iSearchFrame;
      uiTempDisabled = readdisable(iSearchFrame - 1);
      iSearchFrame = currentreplayframe;
      uiPrevDisabled = uiTempDisabled;
    } else {
      uiPrevDisabled = 0;
    }
    currentreplayframe = iSearchFrame;
    uiCurrDisabled = readdisable(iSearchFrame);
    iTargetFrame = currentreplayframe;
    uiCurrentDisabled = uiCurrDisabled;
    while (iTargetFrame > 0)                  // Search backwards until boundary found or target frame reached
    {
      if (!uiCurrentDisabled && uiPrevDisabled)
        break;                                  // Stop if found transition from disabled to enabled frame
      if (iTargetFrame <= iFrame)
        break;                                  // Stop if reached target frame boundary
      --iTargetFrame;
      uiCurrentDisabled = uiPrevDisabled;
      if (iTargetFrame < 1) {
        uiPrevDisabled = 0;
      } else {
        currentreplayframe = iTargetFrame;
        uiTempPrevDisabled = readdisable(iTargetFrame - 1);
        iTargetFrame = currentreplayframe;
        uiPrevDisabled = uiTempPrevDisabled;
      }
    }
  } else {
    iTargetFrame = iFrame;
  }
  ticks = iTargetFrame;                         // Set game timer to target frame
  pend_view_init = ViewType[0];                 // Initialize view system for frame transition
  currentreplayframe = iTargetFrame;
}

//-------------------------------------------------------------------------------------------------
//00067AF0
void nextcut()
{
  int iCutIndex; // esi
  int iCutCounter; // eax
  int iCameraIndex; // edx
  int iSearchFrame; // ebx
  int iNextCutFrame; // esi
  int iTargetFrame; // ebx
  unsigned int uiPrevDisabled; // edx
  unsigned int uiCurrDisabled; // eax

  resetsmoke();                                 // Clear smoke effects for clean transition
  iCutIndex = -1;                               // Initialize cut index to -1 (no cut found)
  if (cuts)                                   // Search through camera cuts if any exist
  {
    iCutCounter = 0;
    if (cuts > 0) {
      iCameraIndex = 0;                         // Find the last cut that occurs before or at current frame
      do {                                         // Check if this cut frame is <= current frame
        if (camera[iCameraIndex].iFrame <= currentreplayframe)
          iCutIndex = iCutCounter;
        ++iCameraIndex;
        ++iCutCounter;
      } while (iCutCounter < cuts);
    }
  }
  iSearchFrame = currentreplayframe;            // Start search from current frame
  if (iCutIndex >= cuts - 1)                  // Determine next cut boundary or end of replay
    iNextCutFrame = replayframes + 1;           // If at last cut, target is end of replay
  else
    iNextCutFrame = camera[iCutIndex + 1].iFrame;// Otherwise target is next cut frame
  if (currentreplayframe < replayframes - 1)  // Advance to next frame if not at end of replay
    iSearchFrame = currentreplayframe + 1;
  if (iSearchFrame <= iNextCutFrame)          // Search forward from current position to find next cut boundary
  {                                             // Get disable status of previous frame for boundary detection
    if (iSearchFrame) {
      currentreplayframe = iSearchFrame;
      uiCurrDisabled = readdisable(iSearchFrame - 1);
      iSearchFrame = currentreplayframe;
      goto SEARCH_LOOP_ENTRY;
    }
    for (uiPrevDisabled = 0; ; uiPrevDisabled = uiCurrDisabled)// Search forward until boundary found or target reached
    {
      currentreplayframe = iSearchFrame;
      uiCurrDisabled = readdisable(iSearchFrame);
      iTargetFrame = currentreplayframe;
      if (currentreplayframe >= replayframes - 1 || !uiCurrDisabled && uiPrevDisabled)
        break;                                  // Stop at end of replay or transition from disabled to enabled
      if (currentreplayframe >= iNextCutFrame)
        break;                                  // Stop if reached next cut frame boundary
      iSearchFrame = currentreplayframe + 1;
    SEARCH_LOOP_ENTRY:
      ;
    }
  } else {
    iTargetFrame = iNextCutFrame;
  }
  ticks = iTargetFrame;                         // Set game timer to target frame
  pend_view_init = ViewType[0];                 // Initialize view system for frame transition
  currentreplayframe = iTargetFrame;
}

//-------------------------------------------------------------------------------------------------
//00067BF0
int loadreplay()
{
  return 0; /*
  char *v0; // esi
  char *v1; // edi
  char v2; // al
  char v3; // al
  char *v4; // esi
  char *v5; // edi
  char v6; // al
  char v7; // al
  int result; // eax

  holdmusic = -1;
  loading_replay = -1;
  filingmenu = 0;
  if (filefiles) {
    play_game_uninit();
    strcpy(replayfilename, "..\\REPLAYS\\");
    v0 = selectfilename;
    v1 = &replayfilename[strlen(replayfilename)];
    do {
      v2 = *v0;
      *v1 = *v0;
      if (!v2)
        break;
      v3 = v0[1];
      v0 += 2;
      v1[1] = v3;
      v1 += 2;
    } while (v3);
    v4 = aGss;
    v5 = &replayfilename[strlen(replayfilename)];
    do {
      v6 = *v4;
      *v5 = *v4;
      if (!v6)
        break;
      v7 = v4[1];
      v4 += 2;
      v5[1] = v7;
      v5 += 2;
    } while (v7);
    replaytype = 2;
    _disable();
    replayspeed = 0;
    fraction = 0;
    replaydirection = 0;
    ticks = currentreplayframe;
    _enable();
    play_game_init();
    result = ViewType[0];
    pend_view_init = ViewType[0];
  }
  screenready = 0;
  lagdone = 0;
  holdmusic = 0;
  loading_replay = 0;
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00067CF0
int savereplay()
{
  return 0; /*
  int v0; // ebp
  char *v1; // esi
  char *v2; // edi
  char v3; // al
  char v4; // al
  char *v5; // esi
  char *v6; // edi
  char v7; // al
  char v8; // al
  int result; // eax
  char *v10; // esi
  char *v11; // edi
  char v12; // al
  char v13; // al
  char *v14; // esi
  char *v15; // edi
  char v16; // al
  char v17; // al
  int v18; // edi
  int v19; // eax
  int v20; // eax
  int v21; // edi
  char v22[32]; // [esp+0h] [ebp-48h] BYREF
  int v23; // [esp+20h] [ebp-28h]
  int v24; // [esp+24h] [ebp-24h]
  int v25; // [esp+28h] [ebp-20h]
  int v26; // [esp+2Ch] [ebp-1Ch]

  v26 = 0;
  v0 = scrbuf;
  if (!strcmp(replayfilename, "..\\REPLAYS\\REPLAY.TMP")) {
    ftell(replayfile);
    fclose(replayfile);
    strcpy(replayfilename, "..\\REPLAYS\\");
    v1 = selectfilename;
    v2 = &replayfilename[strlen(replayfilename)];
    do {
      v3 = *v1;
      *v2 = *v1;
      if (!v3)
        break;
      v4 = v1[1];
      v1 += 2;
      v2[1] = v4;
      v2 += 2;
    } while (v4);
    v5 = aGss;
    v6 = &replayfilename[strlen(replayfilename)];
    do {
      v7 = *v5;
      *v6 = *v5;
      if (!v7)
        break;
      v8 = v5[1];
      v5 += 2;
      v6[1] = v8;
      v6 += 2;
    } while (v8);
    remove(replayfilename);
    rename("..\\REPLAYS\\REPLAY.TMP", replayfilename);
    replayfile = fopen(replayfilename, aRb_0);
    result = fseek(replayfile, 0, 0);
  } else {
    strcpy(v22, "..\\REPLAYS\\");
    v10 = selectfilename;
    v11 = &v22[strlen(v22)];
    do {
      v12 = *v10;
      *v11 = *v10;
      if (!v12)
        break;
      v13 = v10[1];
      v10 += 2;
      v11[1] = v13;
      v11 += 2;
    } while (v13);
    v14 = aGss;
    v15 = &v22[strlen(v22)];
    do {
      v16 = *v14;
      *v15 = *v14;
      if (!v16)
        break;
      v17 = v14[1];
      v14 += 2;
      v15[1] = v17;
      v15 += 2;
    } while (v17);
    result = strcmp(v22, replayfilename);
    if (result) {
      result = fopen(v22, &aYwb[1]);
      v25 = result;
      if (result) {
        v23 = ftell(replayfile);
        fseek(replayfile, 0, 0);
        v26 = 0;
        do {
          v18 = fread(v0, 1, 64000, replayfile);
          v19 = fwrite(v0, 1, v18, v25);
          if (v19 != v18) {
            v20 = *(_DWORD *)_get_errno_ptr(v19);
            v26 = -1;
            v24 = v20;
          }
        } while (v18 && !v26);
        v21 = v26;
        fclose(v25);
        if (v21)
          remove(v22);
        fseek(replayfile, v23, 0);
        result = currentreplayframe;
        ticks = currentreplayframe;
      }
    }
  }
  filingmenu = 0;
  lastfile = 0;
  screenready = 0;
  if (v26) {
    if (v24 == 12)
      filingmenu = 6;
    else
      filingmenu = 7;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00067F50
int deletereplay(int a1, int a2, int a3, int a4)
{
  return 0; /*
  char *v4; // esi
  char *v5; // edi
  char v6; // al
  char v7; // al
  char *v8; // esi
  char *v9; // edi
  char v10; // al
  char v11; // al
  char *v12; // edi
  const char *v13; // esi
  char v14; // al
  char v15; // al
  int result; // eax
  char v17[44]; // [esp-30h] [ebp-34h] BYREF
  int v18; // [esp-4h] [ebp-8h]

  v18 = a4;
  strcpy(v17, "..\\REPLAYS\\");
  v4 = selectfilename;
  v5 = &v17[strlen(v17)];
  do {
    v6 = *v4;
    *v5 = *v4;
    if (!v6)
      break;
    v7 = v4[1];
    v4 += 2;
    v5[1] = v7;
    v5 += 2;
  } while (v7);
  v8 = aGss;
  v9 = &v17[strlen(v17)];
  do {
    v10 = *v8;
    *v9 = *v8;
    if (!v10)
      break;
    v11 = v8[1];
    v8 += 2;
    v9[1] = v11;
    v9 += 2;
  } while (v11);
  if (!strcmp(replayfilename, v17)) {
    remove("..\\REPLAYS\\REPLAY.TMP");
    ftell(replayfile);
    v12 = replayfilename;
    fclose(replayfile);
    v13 = "..\\REPLAYS\\REPLAY.TMP";
    rename(v17, "..\\REPLAYS\\REPLAY.TMP");
    do {
      v14 = *v13;
      *v12 = *v13;
      if (!v14)
        break;
      v15 = v13[1];
      v13 += 2;
      v12[1] = v15;
      v12 += 2;
    } while (v15);
    replayfile = fopen(replayfilename, aRb_0);
    fseek(replayfile, 0, 0);
  } else {
    remove(v17);
  }
  result = currentreplayframe;
  ticks = currentreplayframe;
  filingmenu = 0;
  lastfile = 0;
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00068070
char updatedirectory()
{
  return 0; /*
  int v0; // edx
  char *v1; // edi
  char *v2; // esi
  char result; // al

  v0 = topfile;
  if (!filefiles)
    filefile = 0;
  if (filefile < topfile)
    v0 = topfile - 3;
  if (v0 + 18 <= filefile)
    v0 += 3;
  v1 = selectfilename;
  v2 = &filename[9 * filefile];
  topfile = v0;
  do {
    result = *v2;
    *v1 = *v2;
    if (!result)
      break;
    result = v2[1];
    v2 += 2;
    v1[1] = result;
    v1 += 2;
  } while (result);
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//000680F0
void findintrofiles()
{
  introfiles = 0;
#ifdef IS_WINDOWS
  struct _finddata_t fileinfo;
  intptr_t handle = _findfirst("INTRO*.GSS", &fileinfo);

  if (handle == -1)
    return;

  do {
    introfiles++;
  } while (_findnext(handle, &fileinfo) == 0);

  _findclose(handle);
#else
  DIR *dir = opendir(".");
  if (!dir)
    return;

  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    if (fnmatch("INTRO*.GSS", entry->d_name, FNM_CASEFOLD) == 0) {
      introfiles++;
    }
    if (fnmatch("intro*.gss", entry->d_name, FNM_CASEFOLD) == 0) {
      introfiles++;
    }
  }

  closedir(dir);
#endif
}

//-------------------------------------------------------------------------------------------------
//00068130
int displaycontrolpanel()
{
  return 0; /*
  int v0; // ebp
  int v1; // eax
  int v2; // edi
  int j; // eax
  int i; // eax
  int result; // eax
  int v6; // esi
  int v7; // ebx
  int v8; // eax
  int v9; // edx
  char *v10; // eax
  int v11; // [esp-Ch] [ebp-48h]
  int v12; // [esp+4h] [ebp-38h]
  int v13; // [esp+8h] [ebp-34h]
  int v14; // [esp+18h] [ebp-24h]

  if (SVGA_ON) {
    v0 = 640;
    replayicon(150, 640, -1);
  } else {
    v0 = 320;
    replayicon(150, 320, -1);
  }
  if (!replayedit)
    replayicon(187, v0, -1);
  if (!keys_variable_2 || paused || (v1 = -1, controlicon == 18) && !replayselect)
    v1 = 0;
  replayicon(ricon_variable_1[4 * controlicon] + 150 + v1, v0, -1);
  if (replayspeed > 0 && !forwarding && !rewinding)
    replayicon(ricon_variable_6 + 149, v0, -1);
  if (replayspeed < 0 && !forwarding && !rewinding)
    replayicon(ricon_variable_4 + 149, v0, -1);
  if (replayedit)
    replayicon(ricon_variable_9 + 149, v0, -1);
  if (replayselect)
    replayicon(ricon_variable_11 + 149, v0, -1);
  if (disciconpressed)
    replayicon(ricon_variable_9 + 149, v0, -1);
  replaypanelstring(*(&replayhelp + controlicon), 255, 165, v0);
  if (replayedit) {
    replaypanelstring(&aIewcurrent[3], 164, 165, v0);
    sprintf(buffer, "CAR %d", ViewType[0] + 1);
    replaypanelstring(buffer, 199, 165, v0);
    replaypanelstring(*(&views + SelectedView[0]), 225, 165, v0);
    if (cuts) {
      v7 = -1;
      v8 = 0;
      if (cuts > 0) {
        v9 = 0;
        do {
          if (currentreplayframe >= *(int *)((char *)&camera_variable_2 + v9))
            v7 = v8;
          ++v8;
          v9 += 6;
        } while (v8 < cuts);
      }
      if (v7 != -1) {
        if (*(int *)((char *)&camera_variable_2 + 6 * v7) == currentreplayframe)
          v10 = aNewEdit;
        else
          v10 = &aTEdit[2];
        replaypanelstring(v10, 164, 171, v0);
        sprintf(buffer, "CAR %d", (unsigned __int8)camera_variable_1[6 * v7] + 1);
        replaypanelstring(buffer, 199, 171, v0);
        replaypanelstring(*(&views + (unsigned __int8)camera[6 * v7]), 225, 171, v0);
      }
    }
    if (replayselect) {
      if (replaystart >= currentreplayframe) {
        v13 = currentreplayframe;
        v12 = replaystart;
      } else {
        v13 = replaystart;
        v12 = currentreplayframe;
      }
      replaypanelstring(&aSpblock[2], 164, 159, v0);
      displaypaneltime(v13, 189, 159, v0);
      displaypaneltime(v12, 223, 159, v0);
      return replaypanelstring(&asc_A2767[1], 218, 159, v0);
    } else {
      return displaypaneltime(currentreplayframe, 223, 159, v0);
    }
  } else {
    sprintf(buffer, "X %s", (&replayname)[replaysetspeed]);
    replaypanelstring(buffer, 229, 165, v0);
    displaypaneltime(currentreplayframe, 223, 159, v0);
    if (replayspeed > 0 && !forwarding && !rewinding)
      replayicon(161, v0, 255);
    if (replayspeed < 0 && !forwarding && !rewinding)
      replayicon(161, v0, 255);
    if (forwarding && replayspeed > 0)
      replayicon(161, v0, 255);
    if (rewinding && replayspeed < 0)
      replayicon(161, v0, 255);
    if (!replayspeed)
      replayicon(161, v0, 255);
    replayicon(161, v0, 255);
    if (currentreplayframe <= rotpoint) {
      if (rotpoint - currentreplayframe > 24) {
        v2 = rotpoint - 24;
        for (i = rotpoint - 152; i >= currentreplayframe; v2 -= 64)
          i -= 64;
      } else {
        v2 = currentreplayframe;
      }
    } else if (currentreplayframe - rotpoint > 24) {
      v2 = rotpoint + 24;
      for (j = rotpoint + 152; j <= currentreplayframe; v2 += 64)
        j += 64;
    } else {
      v2 = currentreplayframe;
    }
    result = (v2 - (__CFSHL__(v2 >> 31, 3) + 8 * (v2 >> 31))) >> 3;
    rotpoint = v2;
    v6 = result;
    v14 = result + 3;
    if (!__OFSUB__(result, result + 3)) {
      do {
        v11 = rrotate_variable_1[2 * (v6 % 8)] + 150;
        ++v6;
        result = replayicon(v11, v0, 255);
      } while (v6 < v14);
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00068910
void rtoggleedit()
{
  replayedit = replayedit == 0;
  replayselect = 0;
  if (replaytype == 2) {
    //_disable();
    replayspeed = 0;
    fraction = 0;
    replaydirection = 0;
    ticks = currentreplayframe;
    //_enable();
  }
  rotpoint = currentreplayframe;
  sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);                        // SOUND_SAMPLE_BUTTON
}

//-------------------------------------------------------------------------------------------------
//00068980
void rstartblock()
{
  bool bReplaySelected; // zf

  if (replayedit) {
    if (replaytype == 2) {
      //_disable();
      replayspeed = 0;
      fraction = 0;
      replaydirection = 0;
      ticks = currentreplayframe;
      //_enable();
    }
    bReplaySelected = replayselect != 0;
    replayselect = replayselect == 0;
    if (!bReplaySelected && replaytype == 2) {
      //_disable();
      replayspeed = 0;
      fraction = 0;
      replaydirection = 0;
      ticks = currentreplayframe;
      //_enable();
    }
    replaystart = currentreplayframe;
    sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);                      // SOUND_SAMPLE_BUTTON
  }
}

//-------------------------------------------------------------------------------------------------
//00068A20
void rselectblock()
{                                               // Check if replay editing mode is active
  int iStartFrame; // eax
  int iEndFrame; // ebx
  int iFrameIndex; // edx
  int iCurrentFrame; // eax

  if (replayedit) {                                             // Check if replay type is 2 (selection mode)
    if (replaytype == 2) {
      //_disable();                               // Pause replay playback - disable interrupts
      replayspeed = 0;                          // Stop replay playback
      fraction = 0;
      replaydirection = 0;
      ticks = currentreplayframe;
      //_enable();
    }
    if (!replayselect)                        // If no selection active, start new selection at current frame
      replaystart = currentreplayframe;
    iStartFrame = replaystart;                  // Get frame range for selection block operation
    iEndFrame = currentreplayframe;
    if (replaytype == 2) {                                           // Ensure start frame <= end frame for proper range
      if (currentreplayframe < replaystart) {
        iStartFrame = currentreplayframe;
        iEndFrame = replaystart;
      }
      for (iFrameIndex = iStartFrame; iFrameIndex <= iEndFrame; ++iFrameIndex)// Clear disabled status for all frames in selected range
      {
        iCurrentFrame = iFrameIndex;
        cleardisable(iCurrentFrame);
      }
    }
    replayselect = 0;                           // Clear selection flag
    if (replaytype == 2) {
      //_disable();                               // Reset replay state after selection operation
      replayspeed = 0;
      fraction = 0;
      replaydirection = 0;
      ticks = currentreplayframe;
      //_enable();
    }
    sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);                      // SOUND_SAMPLE_BUTTON
  }
}

//-------------------------------------------------------------------------------------------------
//00068AF0
void rdeleteblock()
{                                               // Check if replay editing mode is active
  int iStartFrame; // ecx
  int iEndFrame; // ebx
  int iFrameIndex; // edx
  int iCurrentFrame; // eax

  if (replayedit) {                                             // Check if replay type is 2 (deletion mode)
    if (replaytype == 2) {
      //_disable();                               // Pause replay playback - disable interrupts
      replayspeed = 0;                          // Stop replay playback
      fraction = 0;
      replaydirection = 0;
      ticks = currentreplayframe;
      //_enable();
    }
    if (!replayselect)                        // If no selection active, start new selection at current frame
      replaystart = currentreplayframe;
    iStartFrame = replaystart;                  // Get frame range for deletion block operation
    iEndFrame = currentreplayframe;
    if (replaytype == 2) {                                           // Ensure start frame <= end frame for proper range
      if (currentreplayframe < replaystart) {
        iStartFrame = currentreplayframe;
        iEndFrame = replaystart;
      }
      for (iFrameIndex = iStartFrame; iFrameIndex <= iEndFrame; ++iFrameIndex)// Mark all frames in selected range as disabled/deleted
      {
        iCurrentFrame = iFrameIndex;
        setdisable(iCurrentFrame);
      }
    }
    replayselect = 0;                           // Clear selection flag
    sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);                      // SOUND_SAMPLE_BUTTON
  }
}

//-------------------------------------------------------------------------------------------------
//00068B90
void rstoreview()
{
  if (replayedit) {
    if (replaytype == 2) {
      //_disable();
      replayspeed = 0;
      fraction = 0;
      replaydirection = 0;
      ticks = currentreplayframe;
      //_enable();
    }
    storecut();
    sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);                      // SOUND_SAMPLE_BUTTON
  }
}

//-------------------------------------------------------------------------------------------------
//00068BE0
void rremoveview()
{
  if (replayedit) {
    if (replaytype == 2) {
      //_disable();
      replayspeed = 0;
      fraction = 0;
      replaydirection = 0;
      ticks = currentreplayframe;
      //_enable();
    }
    removecut();
    sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);                      // SOUND_SAMPLE_BUTTON
  }
}

//-------------------------------------------------------------------------------------------------
//00068C30
void rpreviouscut()
{
  if (replayedit) {
    if (replaytype == 2) {
      //_disable();
      replayspeed = 0;
      fraction = 0;
      replaydirection = 0;
      ticks = currentreplayframe;
      //_enable();
    }
    previouscut();
    sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);                      // SOUND_SAMPLE_BUTTON
  }
}

//-------------------------------------------------------------------------------------------------
//00068C80
void rnextcut()
{
  if (replayedit) {
    if (replaytype == 2) {
      //_disable();
      replayspeed = 0;
      fraction = 0;
      replaydirection = 0;
      ticks = currentreplayframe;
      //_enable();
    }
    nextcut();
    sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);                      // SOUND_SAMPLE_BUTTON
  }
}

//-------------------------------------------------------------------------------------------------
//00068CD0
void rstartassemble()
{
  int iEnabledFramesFound; // ebx
  int iFrameIndex; // edx

  iEnabledFramesFound = 0;                      // Initialize flag - assume no enabled frames found
  if (replaytype == 2 && replayedit)          // Only allow assembly in edit mode with replay editing enabled
  {
    sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);                      // SOUND_SAMPLE_BUTTON
    iFrameIndex = 0;                            // Start searching from first frame
    if (replayframes > 0)                     // Search through all replay frames
    {                                           // Skip disabled frames - look for first enabled frame
      while (readdisable(iFrameIndex)) {
        if (++iFrameIndex >= replayframes)
          goto CHECK_RESULTS;
      }
      iEnabledFramesFound = -1;                 // Found at least one enabled frame
    }
  CHECK_RESULTS:
    if (iEnabledFramesFound)                  // Set appropriate menu state based on search results
      filingmenu = 4;                           // No enabled frames - set menu to error/warning state
    else
      filingmenu = 8;                           // Enabled frames found - proceed with assembly menu
  }
}

//-------------------------------------------------------------------------------------------------
//00068D50
uint8 *replayicon(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
  return 0; /*
  int v8; // edx
  unsigned __int8 *result; // eax
  int v10; // edx
  unsigned __int8 *v11; // edx
  int v12; // esi
  int j; // ebp
  unsigned __int8 v14; // cl
  int v15; // esi
  unsigned __int8 v16; // cl
  unsigned __int8 *v17; // ebp
  unsigned __int8 *v18; // eax
  unsigned __int8 *v19; // ebp
  unsigned __int8 *v20; // eax
  unsigned __int8 *v21; // ebp
  int v22; // [esp+Ch] [ebp-2Ch]
  int v23; // [esp+10h] [ebp-28h]
  int v24; // [esp+14h] [ebp-24h]
  int i; // [esp+18h] [ebp-20h]
  int v26; // [esp+1Ch] [ebp-1Ch]
  unsigned __int8 *v27; // [esp+20h] [ebp-18h]
  int v28; // [esp+24h] [ebp-14h]

  v23 = a4;
  v8 = a5;
  if (SVGA_ON) {
    v8 = 2 * a5;
    v23 = 2 * a4;
  }
  result = (unsigned __int8 *)(a6 * v8 + v23 + a1);
  v26 = *(_DWORD *)(a2 + 12 * a3);
  v10 = a2 + 12 * a3;
  v22 = *(_DWORD *)(v10 + 4);
  v11 = (unsigned __int8 *)(a2 + *(_DWORD *)(v10 + 8));
  if (SVGA_ON) {
    v24 = 0;
    if (v22 <= 0)
      return result;
    while (1) {
      v15 = v23;
      v28 = 0;
      if (v26 > 0)
        break;
    LABEL_24:
      result += 2 * (a6 - v26);
      if (++v24 >= v22)
        return result;
    }
    while (1) {
      v16 = *v11++;
      if (v15 < 0 || v15 >= a6)
        break;
      v17 = &result[a6];
      v27 = &result[a6];
      if (a7 >= 0) {
        if (a7 == v16)
          break;
        *result = v16;
        v20 = result + 1;
        *v27 = v16;
        v21 = &v20[a6];
        *v20 = v16;
        result = v20 + 1;
        *v21 = v16;
      } else {
        *result = v16;
        v18 = result + 1;
        *v17 = v16;
        v19 = &v18[a6];
        *v18 = v16;
        result = v18 + 1;
        *v19 = v16;
      }
    LABEL_23:
      v15 += 2;
      if (++v28 >= v26)
        goto LABEL_24;
    }
    result += 2;
    goto LABEL_23;
  }
  for (i = 0; i < v22; ++i) {
    v12 = v23;
    for (j = 0; j < v26; ++result) {
      v14 = *v11++;
      if (v12 >= 0 && v12 < a6 && (a7 < 0 || a7 != v14))
        *result = v14;
      ++v12;
      ++j;
    }
    result += a6 - v26;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00068EF0
int replaypanelletter(int result, int *a2, int *a3, int a4)
{
  return 0; /*
  int v4; // esi

  v4 = -1;
  if ((unsigned __int8)result >= 0x30u && (unsigned __int8)result <= 0x39u)
    v4 = (unsigned __int8)result - 18;
  if ((unsigned __int8)result >= 0x41u && (unsigned __int8)result <= 0x5Au)
    v4 = (unsigned __int8)result - 25;
  if ((_BYTE)result == 45)
    v4 = 66;
  if ((_BYTE)result == 58)
    v4 = 67;
  if ((_BYTE)result == 47)
    v4 = 68;
  if ((_BYTE)result == 63)
    v4 = 69;
  if (v4 != -1) {
    replayicon(scrbuf, rev_vga_variable_5, v4, *a2, *a3, a4, 255);
    result = *(_DWORD *)(rev_vga_variable_5 + 12 * v4) + 1;
    *a2 += result;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00068F80
int replaypanelstring(const char *a1, int a2, int a3, int a4)
{
  return 0; /*
  const char *v4; // esi
  unsigned int i; // ebp
  int result; // eax
  int v7; // [esp+4h] [ebp-1Ch] BYREF
  int v8; // [esp+8h] [ebp-18h] BYREF
  int v9; // [esp+Ch] [ebp-14h]
  const char *v10; // [esp+10h] [ebp-10h]

  v10 = a1;
  v7 = a2;
  v8 = a3;
  v9 = a4;
  v4 = a1;
  for (i = 0; ; ++i) {
    result = 0;
    if (i >= strlen(v10))
      break;
    if (*v4 == 124) {
      v7 = a2;
      v8 += 6;
    } else if (*v4 == 32) {
      v7 += 2;
    } else {
      replaypanelletter(*(unsigned __int8 *)v4, &v7, &v8, v9);
    }
    ++v4;
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00069000
int displaypaneltime(int a1, int a2, int a3, int a4)
{
  return 0; /*
  sprintf(buffer, "%02d:%02d:%02d", a1 / 36 / 60, a1 / 36 % 60, a1 % 36);
  return replaypanelstring(buffer, a2, a3, a4);*/
}

//-------------------------------------------------------------------------------------------------
//00069080
int discmenu(int a1, unsigned int a2, int a3, unsigned int a4)
{
  return 0; /*
  int result; // eax

  result = sfxsample(__SPAIR64__(a4, a2));
  lsdsel = 0;
  disciconpressed = -1;
  filingmenu = 5;
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//000690C0
void initsoundlag(uint32 uiTicks)
{
  //cli();  // Disable interrupts

  delayread = 0;
  delaywrite = 6;

  int iNumCars = numcars;
  if (iNumCars > 16) iNumCars = 16;

  for (int iCarIdx = 0; iCarIdx < iNumCars; iCarIdx++) {
    // Initialize all 6 entries for this car
    for (int iEntryIdx = 0; iEntryIdx < 6; iEntryIdx++) {
      enginedelay[iCarIdx].engineSoundData[iEntryIdx].iEngineVol = -1;
      enginedelay[iCarIdx].engineSoundData[iEntryIdx].iEngine2Vol = -1;
      enginedelay[iCarIdx].engineSoundData[iEntryIdx].iSkid1Vol = -1;
    }
  }

  // Initialize timing system
  ticks = uiTicks;
  fraction = 0;
  currentreplayframe = uiTicks;
  lastreplayframe = uiTicks;
  replayspeed = 0x100;  // 1.0x speed

  //sti();  // Enable interrupts
}

//-------------------------------------------------------------------------------------------------
//00069160
void resetsmoke()
{
  int iNumCars; // esi
  int iCarIndex; // ebx
  //int iCarSprayEnd; // ecx
  //unsigned int uiOffset; // eax

  iNumCars = numcars;
  iCarIndex = 0;

  for (iCarIndex = 0; iCarIndex < iNumCars; iCarIndex++)
  {
    for (int iSprayIndex = 0; iSprayIndex < 32; iSprayIndex++)
    {
      CarSpray[iCarIndex][iSprayIndex].iLifeTime = 0;
    }
  }
  //if (numcars > 0) {
  //  iCarSprayEnd = 1408;
  //  do {
  //    uiOffset = 1408 * iCarIndex;
  //    do {
  //      uiOffset += sizeof(tCarSpray);
  //      car_texs_loaded[uiOffset / 4 + 12] = 0; // offset into CarSpray
  //    } while (uiOffset != iCarSprayEnd);
  //    ++iCarIndex;
  //    iCarSprayEnd += 1408;
  //  } while (iCarIndex < iNumCars);
  //}

  numcars = iNumCars;
}

//-------------------------------------------------------------------------------------------------

#include "drawtrk3.h"
#include "polytex.h"
#include "graphics.h"
//-------------------------------------------------------------------------------------------------

int view_limit = 0; //000A41B8

//-------------------------------------------------------------------------------------------------

int CalcVisibleTrack(int a1, unsigned int a2)
{
  (void)(a1); (void)(a2);
  return 0;
  /*
  int v3; // esi
  int v4; // edi
  int v5; // ebp
  int v6; // ebx
  int v7; // edx
  float *v8; // eax
  double v9; // st4
  double v10; // st7
  double v11; // st4
  double v12; // st6
  double v13; // st7
  int v14; // eax
  float *v15; // edx
  float *v16; // eax
  double v17; // st7
  double v18; // st6
  unsigned __int8 v20; // al
  int v21; // esi
  int result; // eax
  float v23; // [esp+20h] [ebp-38h]
  int v25; // [esp+28h] [ebp-30h]
  int v26; // [esp+2Ch] [ebp-2Ch]
  int v27; // [esp+30h] [ebp-28h]
  int v28; // [esp+34h] [ebp-24h]
  float i; // [esp+38h] [ebp-20h]
  float v30; // [esp+3Ch] [ebp-1Ch]

  set_starts(0, a2);
  TrackSize = -1;
  v27 = -1;
  v3 = Car_variable_3[154 * a1];
  v25 = 0;
  if (v3 == -1)
    v28 = Car_variable_51[77 * a1];
  else
    v28 = Car_variable_3[154 * a1];
  alltrackflag = 0;
  switch (a2) {
    case 2u:
      v4 = 24;
      v5 = -4;
      v3 = -1;
      goto LABEL_10;
    case 3u:
      v4 = 96;
      v26 = -8;
      v3 = -1;
      break;
    case 4u:
      v4 = 32;
      v26 = -16;
      break;
    case 6u:
      v4 = 96;
      v3 = -1;
      v26 = -4;
      break;
    default:
      v5 = -1;
      v4 = 4;
    LABEL_10:
      v26 = v5;
      break;
  }
  if (v3 >= 0) {
    v23 = tcos[Car_variable_7[154 * a1]];
  } else {
    v6 = -v4;
    for (i = 9.9999998e17; v6 <= v4; ++v6) {
      v7 = v6 + v28;
      if (v6 + v28 < 0)
        v7 += TRAK_LEN;
      if (v7 >= TRAK_LEN)
        v7 -= TRAK_LEN;
      v8 = (float *)((char *)&localdata + 128 * v7);
      v9 = -v8[9] - viewx;
      v10 = v9 * v9;
      v11 = -v8[10] - viewy;
      v12 = -v8[11] - viewz;
      v13 = v10 + v11 * v11 + v12 * v12;
      if (v13 < i) {
        v3 = v7;
        v30 = v13;
        i = v30;
      }
    }
    v14 = v3 + 1;
    if (v3 + 1 >= TRAK_LEN)
      v14 -= TRAK_LEN;
    v15 = (float *)((char *)&localdata + 128 * v14);
    v16 = (float *)((char *)&localdata + 128 * v3);
    v17 = v16[9] - v15[9];
    v18 = v16[10] - v15[10];
    v23 = (v17 * tcos[worlddirn] + v18 * tsin[worlddirn])
      / (sqrt(tcos[worlddirn] * tcos[worlddirn] + tsin[worlddirn] * tsin[worlddirn]) + sqrt(v18 * v18 + v17 * v17));
  }
  if (v23 < drawtrk3_c_variable_1
    && v23 >= drawtrk3_c_variable_2
    && ((TrakColour_variable_1[12 * v3] & 2) == 0
        || (TrakColour_variable_5[12 * v3] & 2) == 0
        || (TrakColour_variable_8[12 * v3] & 2) == 0)) {
    if (a2 >= 3 && (a2 <= 3 || a2 == 6)) {
      TrackSize = 48;
      v26 = -24;
    } else {
      TrackSize = 24;
      v26 = -12;
    }
  }
  test_y1 = v3;
  backwards = (v23 >= 0.0) - 1;
  if (v3 >= 0 && TrackSize < 0) {
    if (backwards) {
      TrackSize = (unsigned __int8)TrakView_variable_4[8 * v3] - v26;
      v27 = TrakView_variable_3[4 * v3];
      v20 = TrakView_variable_5[8 * v3];
    } else {
      TrackSize = (unsigned __int8)TrakView_variable_1[8 * v3] - v26;
      v27 = TrakView[4 * v3];
      v20 = TrakView_variable_2[8 * v3];
    }
    v25 = v20;
  }
  if ((view_limit || player_type == 2) && replaytype != 2 && !winner_mode) {
    v25 = 0;
    v27 = -1;
    if (player_type == 2) {
      if (TrackSize > 28)
        TrackSize = 28;
    } else if (TrackSize > view_limit) {
      TrackSize = view_limit;
    }
  }
  if (mirror || a2 == 1)
    backwards = backwards == 0;
  if (backwards) {
    v21 = v3 - v26;
    front_sec = v21;
    if (v21 >= TRAK_LEN)
      front_sec = v21 - TRAK_LEN;
    if (v25 > 0 && v27 >= 0) {
      mid_sec = front_sec - TrackSize;
      if (front_sec - TrackSize < 0)
        mid_sec = front_sec - TrackSize + TRAK_LEN;
      back_sec = v27 - v25;
      if (front_sec >= v27 || back_sec - 1 > front_sec) {
        if (back_sec < 0)
          back_sec += TRAK_LEN;
        gap_size = mid_sec - back_sec;
        if (mid_sec - back_sec < 0)
          gap_size = mid_sec - back_sec + TRAK_LEN;
        next_front = v27;
        first_size = v25;
      } else {
        front_sec = v27;
        back_sec = mid_sec;
        next_front = -1;
        test_y1 = -2;
        mid_sec = -1;
        gap_size = 6 * TRAK_LEN;
      }
      TrackSize = front_sec - back_sec;
      if (front_sec - back_sec < 0)
        TrackSize = front_sec - back_sec + TRAK_LEN;
      if (mid_sec < 0)
        first_size = TrackSize;
    } else {
      back_sec = front_sec - TrackSize;
      if (front_sec - TrackSize < 0)
        back_sec = front_sec - TrackSize + TRAK_LEN;
      mid_sec = -1;
      first_size = TrackSize;
      next_front = -1;
      gap_size = 6 * TRAK_LEN;
    }
  } else {
    front_sec = v3 + v26;
    if (v3 + v26 < 0)
      front_sec = v3 + v26 + TRAK_LEN;
    if (v25 > 0 && v27 >= 0) {
      first_size = TrackSize;
      mid_sec = TrackSize + front_sec;
      back_sec = v25 + v27;
      if (front_sec <= v27 || back_sec + 1 < front_sec) {
        if (mid_sec >= TRAK_LEN)
          mid_sec -= TRAK_LEN;
        gap_size = v27 - front_sec;
        if (v27 - front_sec < 0)
          gap_size = TRAK_LEN + v27 - front_sec;
        next_front = v27;
      } else {
        gap_size = 6 * TRAK_LEN;
        next_front = -1;
        front_sec = v27;
        test_y1 = -1;
        back_sec = mid_sec;
        mid_sec = -1;
      }
      TrackSize = back_sec - front_sec;
      if (back_sec - front_sec < 0)
        TrackSize = back_sec - front_sec + TRAK_LEN;
      if (mid_sec < 0)
        first_size = TrackSize;
      if (back_sec >= TRAK_LEN)
        back_sec -= TRAK_LEN;
    } else {
      back_sec = TrackSize + front_sec;
      if (TrackSize + front_sec >= TRAK_LEN)
        back_sec = TrackSize + front_sec - TRAK_LEN;
      mid_sec = -1;
      first_size = TrackSize;
      next_front = -1;
      gap_size = 6 * TRAK_LEN;
    }
  }
  if (backwards)
    result = back_sec;
  else
    result = front_sec;
  start_sect = result;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int DrawTrack3(int *a1, int a2, int a3, float *a4, char *a5)
{
  (void)(a1); (void)(a2); (void)(a3); (void)(a4); (void)(a5);
  return 0;
  /*
  int v5; // ecx
  float *v6; // eax
  char *v7; // edx
  float *v8; // esi
  float *v9; // ebx
  double v10; // st7
  double v11; // st6
  double v12; // st5
  double v13; // st7
  __int16 v14; // fps
  _BOOL1 v15; // c0
  char v16; // c2
  _BOOL1 v17; // c3
  int v18; // eax
  double v19; // st7
  double v20; // st6
  double v21; // st5
  double v22; // st7
  int v23; // eax
  int v24; // eax
  double v25; // st7
  double v26; // st6
  double v27; // st5
  double v28; // st7
  __int16 v29; // fps
  _BOOL1 v30; // c0
  char v31; // c2
  _BOOL1 v32; // c3
  int v33; // eax
  double v34; // st7
  double v35; // st6
  double v36; // st5
  double v37; // st7
  int v38; // eax
  int v39; // eax
  float v40; // eax
  double v41; // st7
  double v42; // st6
  double v43; // st5
  double v44; // st7
  __int16 v45; // fps
  _BOOL1 v46; // c0
  char v47; // c2
  _BOOL1 v48; // c3
  int v49; // eax
  double v50; // st7
  double v51; // st6
  double v52; // st5
  double v53; // st7
  int v54; // eax
  int v55; // eax
  float v56; // eax
  double v57; // st7
  double v58; // st6
  double v59; // st5
  double v60; // st7
  __int16 v61; // fps
  _BOOL1 v62; // c0
  char v63; // c2
  _BOOL1 v64; // c3
  int v65; // eax
  double v66; // st7
  double v67; // st6
  double v68; // st5
  double v69; // st7
  int v70; // ebx
  int v71; // eax
  int *v72; // esi
  int v73; // eax
  int *v74; // ebx
  float *v75; // eax
  double v76; // st7
  double v77; // st6
  double v78; // st5
  double v79; // st7
  __int16 v80; // fps
  int v81; // eax
  _BOOL1 v82; // c0
  char v83; // c2
  _BOOL1 v84; // c3
  int v85; // eax
  double v86; // st7
  double v87; // st6
  double v88; // st5
  double v89; // st7
  int v90; // eax
  int v91; // eax
  double v92; // st7
  int v93; // eax
  float *v94; // eax
  double v95; // st7
  double v96; // st6
  double v97; // st5
  double v98; // st7
  __int16 v99; // fps
  int v100; // eax
  _BOOL1 v101; // c0
  char v102; // c2
  _BOOL1 v103; // c3
  int v104; // eax
  double v105; // st7
  double v106; // st6
  double v107; // st5
  double v108; // st7
  int v109; // ebx
  int v110; // eax
  int v111; // eax
  double v112; // st7
  int v113; // eax
  char *v114; // eax
  char *v115; // esi
  float *v116; // edx
  int v117; // eax
  int v118; // ebx
  double v119; // st7
  double v120; // st6
  float *v121; // edx
  double v122; // st5
  double v123; // st7
  __int16 v124; // fps
  _BOOL1 v125; // c0
  char v126; // c2
  _BOOL1 v127; // c3
  int v128; // eax
  double v129; // st7
  double v130; // st6
  double v131; // st5
  double v132; // st7
  int v133; // eax
  int v134; // eax
  int v135; // eax
  int v136; // ecx
  int v137; // eax
  int v138; // ecx
  int v139; // esi
  int v140; // edx
  int v141; // edx
  bool v142; // eax
  int v143; // ebx
  float v144; // eax
  float v145; // eax
  int v146; // eax
  int v147; // eax
  float *v148; // edx
  float v149; // eax
  float v150; // eax
  int v151; // eax
  char *v152; // eax
  int v153; // edx
  int v154; // ebx
  float v155; // eax
  float v156; // eax
  int v157; // eax
  char *v158; // eax
  int v159; // edx
  int v160; // ebx
  float v161; // eax
  float v162; // eax
  int v163; // eax
  char *v164; // eax
  int v165; // edx
  int v166; // ebx
  float v167; // eax
  float v168; // eax
  int v169; // eax
  char *v170; // eax
  int v171; // edx
  int v172; // ebx
  int v173; // edx
  int v174; // eax
  float v175; // eax
  float v176; // eax
  int v177; // eax
  char *v178; // eax
  int v179; // edx
  int v180; // ebx
  double v181; // st7
  double v182; // st7
  float v183; // eax
  float v184; // eax
  char *v185; // eax
  float v186; // edx
  float v187; // eax
  float v188; // eax
  float v189; // eax
  int v190; // ebx
  float v191; // eax
  float v192; // eax
  int v193; // eax
  char *v194; // eax
  int v195; // edx
  float v196; // eax
  float v197; // eax
  int v198; // eax
  char *v199; // eax
  int v200; // edx
  float v201; // eax
  float v202; // eax
  int v203; // eax
  char *v204; // eax
  int v205; // edx
  float v206; // eax
  float v207; // eax
  float v208; // eax
  char *v209; // eax
  float v210; // edx
  float v211; // eax
  float v212; // eax
  int v213; // eax
  char *v214; // eax
  int v215; // edx
  int v216; // ebx
  float v217; // eax
  float v218; // eax
  float v219; // eax
  float *v220; // eax
  int v221; // edx
  int v222; // esi
  int v223; // ebx
  char *v224; // eax
  int v225; // edx
  int v226; // edx
  int v227; // ecx
  int v228; // esi
  int v229; // ebx
  unsigned int v230; // edx
  int v231; // ecx
  int v232; // esi
  int v233; // eax
  int *v234; // ebx
  char *v235; // edx
  int v236; // ecx
  int v237; // eax
  int v238; // esi
  int v239; // ebx
  float *v240; // ecx
  int v241; // edx
  float v242; // eax
  int v243; // esi
  int result; // eax
  float *v245; // eax
  int v246; // esi
  unsigned int v247; // edx
  int v248; // eax
  unsigned int v249; // edx
  float v250; // eax
  float v251; // eax
  float v252; // eax
  float v253; // eax
  float v254; // eax
  float v255; // eax
  int *v256; // edx
  int v257; // eax
  float v258; // eax
  float v259; // eax
  float v260; // eax
  int *v261; // edx
  float v262; // eax
  float v263; // eax
  float v264; // eax
  int v265; // eax
  int v266; // edx
  int v267; // edx
  float v268; // eax
  float v269; // eax
  float v270; // eax
  float v271; // eax
  float v272; // eax
  float v273; // eax
  int v274; // eax
  int v275; // edx
  int v276; // edx
  float v277; // eax
  float v278; // eax
  float v279; // eax
  float v280; // eax
  float v281; // eax
  float v282; // eax
  unsigned int v283; // edx
  int v284; // eax
  float v285; // eax
  float v286; // eax
  float v287; // eax
  float v288; // eax
  float v289; // eax
  float v290; // eax
  unsigned int v291; // edx
  float v292; // eax
  float v293; // eax
  float v294; // eax
  float v295; // eax
  float v296; // eax
  float v297; // eax
  int v298; // edx
  int v299; // eax
  char v300; // bl
  float v301; // eax
  float v302; // eax
  float v303; // eax
  float v304; // eax
  float v305; // eax
  float v306; // eax
  char v307; // bh
  unsigned int v308; // edx
  float v309; // eax
  float v310; // eax
  float v311; // eax
  float v312; // eax
  float v313; // eax
  float v314; // eax
  int v315; // eax
  unsigned int v316; // edx
  float v317; // eax
  float v318; // eax
  float v319; // eax
  float v320; // eax
  float v321; // eax
  float v322; // eax
  int v323; // ebx
  int v324; // edx
  int v325; // eax
  float v326; // eax
  float v327; // eax
  float v328; // eax
  float v329; // eax
  float v330; // eax
  float v331; // eax
  int v332; // edx
  float v333; // eax
  float v334; // eax
  float v335; // eax
  float v336; // eax
  float v337; // eax
  float v338; // eax
  float v339; // eax
  float v340; // eax
  float v341; // eax
  float v342; // eax
  float v343; // eax
  float v344; // eax
  float v345; // eax
  float v346; // eax
  float v347; // eax
  int v348; // edx
  float *v349; // eax
  float *v350; // eax
  float *v351; // eax
  float v352; // eax
  float *v353; // eax
  int *v354; // edx
  float *v355; // eax
  float *v356; // eax
  float *v357; // eax
  float v358; // eax
  float *v359; // eax
  float *v360; // eax
  float *v361; // eax
  float *v362; // eax
  float v363; // eax
  float *v364; // eax
  int v365; // edx
  float *v366; // eax
  float *v367; // eax
  float *v368; // eax
  float v369; // eax
  float *v370; // eax
  float *v371; // eax
  float *v372; // eax
  float *v373; // eax
  float v374; // eax
  float *v375; // eax
  int *v376; // edx
  int v377; // edx
  float *v378; // eax
  float *v379; // eax
  float *v380; // eax
  float v381; // eax
  float *v382; // eax
  int v383; // edx
  float *v384; // eax
  float *v385; // eax
  float *v386; // eax
  float v387; // eax
  float *v388; // eax
  float *v389; // eax
  float *v390; // eax
  float *v391; // eax
  float v392; // eax
  float *v393; // eax
  int v394; // edx
  int v395; // esi
  int v396; // edx
  double v397; // st7
  double v398; // st7
  double v399; // st6
  double v400; // st7
  double v401; // st6
  double v402; // st5
  double v403; // st7
  __int16 v404; // fps
  _BOOL1 v405; // c0
  char v406; // c2
  _BOOL1 v407; // c3
  int v408; // eax
  double v409; // st7
  double v410; // st6
  double v411; // st5
  double v412; // st7
  int v413; // eax
  double v414; // st6
  double v415; // st7
  double v416; // st5
  int v417; // edx
  int v418; // eax
  int v419; // eax
  double v420; // st7
  __int16 v421; // fps
  _BOOL1 v422; // c0
  char v423; // c2
  _BOOL1 v424; // c3
  int v425; // eax
  double v426; // st7
  double v427; // st6
  double v428; // st5
  double v429; // st7
  int v430; // eax
  double v431; // st6
  double v432; // st7
  double v433; // st5
  int v434; // edx
  int v435; // eax
  int v436; // eax
  double v437; // st7
  __int16 v438; // fps
  _BOOL1 v439; // c0
  char v440; // c2
  _BOOL1 v441; // c3
  int v442; // eax
  double v443; // st7
  double v444; // st6
  double v445; // st5
  double v446; // st7
  int v447; // eax
  double v448; // st6
  double v449; // st7
  double v450; // st5
  int v451; // edx
  int v452; // eax
  int v453; // eax
  double v454; // st7
  __int16 v455; // fps
  _BOOL1 v456; // c0
  char v457; // c2
  _BOOL1 v458; // c3
  int v459; // eax
  double v460; // st7
  double v461; // st6
  double v462; // st5
  double v463; // st7
  int v464; // eax
  double v465; // st6
  double v466; // st7
  double v467; // st5
  int v468; // edx
  int v469; // eax
  int v470; // eax
  double v471; // st7
  __int16 v472; // fps
  _BOOL1 v473; // c0
  char v474; // c2
  _BOOL1 v475; // c3
  int v476; // eax
  double v477; // st7
  double v478; // st6
  double v479; // st5
  double v480; // st7
  int v481; // eax
  double v482; // st6
  double v483; // st7
  double v484; // st5
  int v485; // edx
  int v486; // eax
  int v487; // eax
  double v488; // st7
  __int16 v489; // fps
  _BOOL1 v490; // c0
  char v491; // c2
  _BOOL1 v492; // c3
  int v493; // eax
  double v494; // st7
  double v495; // st6
  double v496; // st5
  double v497; // st7
  int v498; // eax
  double v499; // st6
  double v500; // st7
  double v501; // st5
  int v502; // edx
  int v503; // eax
  int v504; // eax
  double v505; // st7
  __int16 v506; // fps
  _BOOL1 v507; // c0
  char v508; // c2
  _BOOL1 v509; // c3
  int v510; // eax
  double v511; // st7
  double v512; // st6
  double v513; // st5
  double v514; // st7
  int v515; // eax
  double v516; // st6
  double v517; // st7
  double v518; // st5
  int v519; // edx
  int v520; // eax
  int v521; // eax
  double v522; // st7
  __int16 v523; // fps
  _BOOL1 v524; // c0
  char v525; // c2
  _BOOL1 v526; // c3
  int v527; // eax
  double v528; // st7
  double v529; // st6
  double v530; // st5
  double v531; // st7
  int v532; // edx
  int v533; // eax
  int v534; // edx
  int v535; // eax
  double v536; // st7
  double v537; // st6
  int v538; // esi
  int v539; // edx
  int v540; // ebx
  int v541; // ebx
  int v542; // eax
  int v543; // edx
  int v544; // ecx
  int v545; // edx
  int v546; // esi
  int v547; // edx
  int v548; // eax
  int v549; // edx
  _DWORD v551[9]; // [esp+4h] [ebp-4F0h]
  float v552; // [esp+28h] [ebp-4CCh]
  float v553; // [esp+2Ch] [ebp-4C8h]
  int v554; // [esp+30h] [ebp-4C4h]
  int v555; // [esp+34h] [ebp-4C0h]
  int v556; // [esp+38h] [ebp-4BCh]
  float v557; // [esp+3Ch] [ebp-4B8h]
  int v558; // [esp+40h] [ebp-4B4h]
  int v559; // [esp+44h] [ebp-4B0h]
  int v560; // [esp+48h] [ebp-4ACh]
  float v561; // [esp+4Ch] [ebp-4A8h]
  float v562; // [esp+50h] [ebp-4A4h]
  int v563; // [esp+54h] [ebp-4A0h]
  int v564; // [esp+58h] [ebp-49Ch]
  int v565; // [esp+5Ch] [ebp-498h]
  float v566; // [esp+60h] [ebp-494h]
  int v567; // [esp+64h] [ebp-490h]
  float v568; // [esp+68h] [ebp-48Ch]
  int v569; // [esp+6Ch] [ebp-488h]
  float v570; // [esp+70h] [ebp-484h]
  float v571; // [esp+74h] [ebp-480h]
  float v572; // [esp+78h] [ebp-47Ch]
  float v573; // [esp+7Ch] [ebp-478h]
  float v574; // [esp+80h] [ebp-474h]
  float v575; // [esp+84h] [ebp-470h]
  float v576; // [esp+88h] [ebp-46Ch]
  float v577; // [esp+8Ch] [ebp-468h]
  int v578; // [esp+90h] [ebp-464h]
  int v579; // [esp+94h] [ebp-460h]
  int v580; // [esp+98h] [ebp-45Ch]
  float v581; // [esp+9Ch] [ebp-458h]
  float v582; // [esp+A0h] [ebp-454h]
  int v583; // [esp+A4h] [ebp-450h]
  int v584; // [esp+A8h] [ebp-44Ch]
  int v585; // [esp+ACh] [ebp-448h]
  float v586; // [esp+B0h] [ebp-444h]
  float v587; // [esp+B4h] [ebp-440h]
  int v588; // [esp+B8h] [ebp-43Ch]
  int v589; // [esp+BCh] [ebp-438h]
  int v590; // [esp+C0h] [ebp-434h]
  float v591; // [esp+C4h] [ebp-430h]
  float v592; // [esp+C8h] [ebp-42Ch]
  float v593; // [esp+CCh] [ebp-428h]
  float v594; // [esp+D0h] [ebp-424h]
  float v595; // [esp+D4h] [ebp-420h]
  float v596; // [esp+D8h] [ebp-41Ch]
  int v597; // [esp+DCh] [ebp-418h]
  int v598; // [esp+E0h] [ebp-414h]
  int v599; // [esp+E4h] [ebp-410h]
  float v600; // [esp+E8h] [ebp-40Ch]
  float v601; // [esp+ECh] [ebp-408h]
  float v602; // [esp+F0h] [ebp-404h]
  float v603; // [esp+F4h] [ebp-400h]
  float v604; // [esp+F8h] [ebp-3FCh]
  unsigned int v605; // [esp+FCh] [ebp-3F8h]
  float v606; // [esp+100h] [ebp-3F4h]
  float v607; // [esp+104h] [ebp-3F0h]
  float v608; // [esp+108h] [ebp-3ECh]
  float v609; // [esp+10Ch] [ebp-3E8h]
  float v610; // [esp+110h] [ebp-3E4h]
  float v611; // [esp+114h] [ebp-3E0h]
  float v612; // [esp+118h] [ebp-3DCh]
  float v613; // [esp+11Ch] [ebp-3D8h]
  float v614; // [esp+120h] [ebp-3D4h]
  float v615; // [esp+124h] [ebp-3D0h]
  float v616; // [esp+128h] [ebp-3CCh]
  float v617; // [esp+12Ch] [ebp-3C8h]
  float v618; // [esp+130h] [ebp-3C4h]
  float *v619; // [esp+134h] [ebp-3C0h]
  float *v620; // [esp+138h] [ebp-3BCh]
  float v621; // [esp+13Ch] [ebp-3B8h]
  float v622; // [esp+140h] [ebp-3B4h]
  float v623; // [esp+144h] [ebp-3B0h]
  float v624; // [esp+148h] [ebp-3ACh]
  float v625; // [esp+14Ch] [ebp-3A8h]
  float v626; // [esp+150h] [ebp-3A4h]
  float v627; // [esp+154h] [ebp-3A0h]
  float v628; // [esp+158h] [ebp-39Ch]
  float v629; // [esp+15Ch] [ebp-398h]
  int i; // [esp+160h] [ebp-394h]
  int v631; // [esp+164h] [ebp-390h]
  int v632; // [esp+168h] [ebp-38Ch]
  int v633; // [esp+16Ch] [ebp-388h]
  int v634; // [esp+170h] [ebp-384h]
  bool v635; // [esp+174h] [ebp-380h]
  float v636; // [esp+178h] [ebp-37Ch]
  float v637; // [esp+17Ch] [ebp-378h]
  float v638; // [esp+180h] [ebp-374h]
  float v639; // [esp+184h] [ebp-370h]
  float v640; // [esp+188h] [ebp-36Ch]
  float v641; // [esp+18Ch] [ebp-368h]
  float v642; // [esp+190h] [ebp-364h]
  float v643; // [esp+194h] [ebp-360h]
  float v644; // [esp+198h] [ebp-35Ch]
  float v645; // [esp+19Ch] [ebp-358h]
  float v646; // [esp+1A0h] [ebp-354h]
  float v647; // [esp+1A4h] [ebp-350h]
  float v648; // [esp+1A8h] [ebp-34Ch]
  float v649; // [esp+1ACh] [ebp-348h]
  float v650; // [esp+1B0h] [ebp-344h]
  float v651; // [esp+1B4h] [ebp-340h]
  float v652; // [esp+1B8h] [ebp-33Ch]
  float v653; // [esp+1BCh] [ebp-338h]
  float v654; // [esp+1C0h] [ebp-334h]
  float v655; // [esp+1C4h] [ebp-330h]
  float v656; // [esp+1C8h] [ebp-32Ch]
  float v657; // [esp+1CCh] [ebp-328h]
  float v658; // [esp+1D0h] [ebp-324h]
  float v659; // [esp+1D4h] [ebp-320h]
  float v660; // [esp+1D8h] [ebp-31Ch]
  float v661; // [esp+1DCh] [ebp-318h]
  float v662; // [esp+1E0h] [ebp-314h]
  float v663; // [esp+1E4h] [ebp-310h]
  float v664; // [esp+1F4h] [ebp-300h]
  float v665; // [esp+1F8h] [ebp-2FCh]
  float v666; // [esp+1FCh] [ebp-2F8h]
  float v667; // [esp+200h] [ebp-2F4h]
  float v668; // [esp+204h] [ebp-2F0h]
  float v669; // [esp+208h] [ebp-2ECh]
  float v670; // [esp+20Ch] [ebp-2E8h]
  float v671; // [esp+210h] [ebp-2E4h]
  int v672; // [esp+214h] [ebp-2E0h]
  int v673; // [esp+218h] [ebp-2DCh]
  int v674; // [esp+21Ch] [ebp-2D8h]
  float v675; // [esp+220h] [ebp-2D4h]
  float v676; // [esp+224h] [ebp-2D0h]
  float v677; // [esp+228h] [ebp-2CCh]
  float v678; // [esp+22Ch] [ebp-2C8h]
  float v679; // [esp+230h] [ebp-2C4h]
  float v680; // [esp+234h] [ebp-2C0h]
  float v681; // [esp+238h] [ebp-2BCh]
  float v682; // [esp+23Ch] [ebp-2B8h]
  int v683; // [esp+240h] [ebp-2B4h]
  int v684; // [esp+244h] [ebp-2B0h]
  int v685; // [esp+248h] [ebp-2ACh]
  float v686; // [esp+24Ch] [ebp-2A8h]
  float v687; // [esp+250h] [ebp-2A4h]
  float v688; // [esp+254h] [ebp-2A0h]
  float v689; // [esp+258h] [ebp-29Ch]
  float v690; // [esp+25Ch] [ebp-298h]
  float v691; // [esp+260h] [ebp-294h]
  float v692; // [esp+264h] [ebp-290h]
  float v693; // [esp+268h] [ebp-28Ch]
  float v694; // [esp+26Ch] [ebp-288h]
  float v695; // [esp+270h] [ebp-284h]
  float v696; // [esp+274h] [ebp-280h]
  float v697; // [esp+278h] [ebp-27Ch]
  float v698; // [esp+27Ch] [ebp-278h]
  float v699; // [esp+280h] [ebp-274h]
  float v700; // [esp+284h] [ebp-270h]
  float v701; // [esp+288h] [ebp-26Ch]
  float v702; // [esp+28Ch] [ebp-268h]
  float v703; // [esp+290h] [ebp-264h]
  float v704; // [esp+294h] [ebp-260h]
  float v705; // [esp+298h] [ebp-25Ch]
  float v706; // [esp+29Ch] [ebp-258h]
  float v707; // [esp+2A0h] [ebp-254h]
  float v708; // [esp+2A4h] [ebp-250h]
  float v709; // [esp+2A8h] [ebp-24Ch]
  float v710; // [esp+2ACh] [ebp-248h]
  float v711; // [esp+2B0h] [ebp-244h]
  float v712; // [esp+2B4h] [ebp-240h]
  float v713; // [esp+2B8h] [ebp-23Ch]
  float v714; // [esp+2BCh] [ebp-238h]
  float v715; // [esp+2C0h] [ebp-234h]
  float v716; // [esp+2C4h] [ebp-230h]
  float v717; // [esp+2C8h] [ebp-22Ch]
  float v718; // [esp+2CCh] [ebp-228h]
  float v719; // [esp+2D0h] [ebp-224h]
  float v720; // [esp+2D4h] [ebp-220h]
  float v721; // [esp+2D8h] [ebp-21Ch]
  int v722; // [esp+2DCh] [ebp-218h]
  int v723; // [esp+2E0h] [ebp-214h]
  int v724; // [esp+2E4h] [ebp-210h]
  float v725; // [esp+2E8h] [ebp-20Ch]
  float v726; // [esp+2ECh] [ebp-208h]
  float v727; // [esp+2F0h] [ebp-204h]
  float v728; // [esp+2F4h] [ebp-200h]
  _DWORD *v729; // [esp+2F8h] [ebp-1FCh]
  float v730; // [esp+2FCh] [ebp-1F8h]
  int v731; // [esp+300h] [ebp-1F4h]
  int v732; // [esp+308h] [ebp-1ECh]
  int v733; // [esp+30Ch] [ebp-1E8h]
  int v734; // [esp+310h] [ebp-1E4h]
  int v735; // [esp+314h] [ebp-1E0h]
  float v736; // [esp+318h] [ebp-1DCh]
  float v737; // [esp+31Ch] [ebp-1D8h]
  float v738; // [esp+320h] [ebp-1D4h]
  float v739; // [esp+324h] [ebp-1D0h]
  int v740; // [esp+328h] [ebp-1CCh]
  float v741; // [esp+32Ch] [ebp-1C8h]
  float v742; // [esp+330h] [ebp-1C4h]
  float v743; // [esp+334h] [ebp-1C0h]
  int v744; // [esp+338h] [ebp-1BCh]
  float v745; // [esp+33Ch] [ebp-1B8h]
  float v746; // [esp+340h] [ebp-1B4h]
  float v747; // [esp+344h] [ebp-1B0h]
  int v748; // [esp+348h] [ebp-1ACh]
  float v749; // [esp+34Ch] [ebp-1A8h]
  float v750; // [esp+350h] [ebp-1A4h]
  float v751; // [esp+354h] [ebp-1A0h]
  float v752; // [esp+358h] [ebp-19Ch]
  float v753; // [esp+35Ch] [ebp-198h]
  float v754; // [esp+360h] [ebp-194h]
  float v755; // [esp+364h] [ebp-190h]
  float v756; // [esp+368h] [ebp-18Ch]
  float v757; // [esp+36Ch] [ebp-188h]
  float v758; // [esp+370h] [ebp-184h]
  float v759; // [esp+374h] [ebp-180h]
  float v760; // [esp+378h] [ebp-17Ch]
  float v761; // [esp+37Ch] [ebp-178h]
  float v762; // [esp+380h] [ebp-174h]
  float v763; // [esp+384h] [ebp-170h]
  float v764; // [esp+388h] [ebp-16Ch]
  float v765; // [esp+38Ch] [ebp-168h]
  float v766; // [esp+390h] [ebp-164h]
  float v767; // [esp+394h] [ebp-160h]
  float v768; // [esp+398h] [ebp-15Ch]
  float v769; // [esp+39Ch] [ebp-158h]
  float v770; // [esp+3A0h] [ebp-154h]
  float v771; // [esp+3A4h] [ebp-150h]
  float v772; // [esp+3A8h] [ebp-14Ch]
  float v773; // [esp+3ACh] [ebp-148h]
  float v774; // [esp+3B0h] [ebp-144h]
  float v775; // [esp+3B4h] [ebp-140h]
  float v776; // [esp+3B8h] [ebp-13Ch]
  float v777; // [esp+3BCh] [ebp-138h]
  float v778; // [esp+3C0h] [ebp-134h]
  float v779; // [esp+3C4h] [ebp-130h]
  float v780; // [esp+3C8h] [ebp-12Ch]
  float v781; // [esp+3CCh] [ebp-128h]
  float v782; // [esp+3D0h] [ebp-124h]
  float v783; // [esp+3D4h] [ebp-120h]
  float v784; // [esp+3D8h] [ebp-11Ch]
  float v785; // [esp+3DCh] [ebp-118h]
  float v786; // [esp+3E0h] [ebp-114h]
  float v787; // [esp+3E4h] [ebp-110h]
  float v788; // [esp+3E8h] [ebp-10Ch]
  float v789; // [esp+3ECh] [ebp-108h]
  float v790; // [esp+3F0h] [ebp-104h]
  float v791; // [esp+3F4h] [ebp-100h]
  float v792; // [esp+3F8h] [ebp-FCh]
  float v793; // [esp+3FCh] [ebp-F8h]
  float v794; // [esp+400h] [ebp-F4h]
  float v795; // [esp+404h] [ebp-F0h]
  float v796; // [esp+408h] [ebp-ECh]
  float v797; // [esp+40Ch] [ebp-E8h]
  float v798; // [esp+410h] [ebp-E4h]
  float v799; // [esp+414h] [ebp-E0h]
  float v800; // [esp+418h] [ebp-DCh]
  float v801; // [esp+41Ch] [ebp-D8h]
  float v802; // [esp+420h] [ebp-D4h]
  float v803; // [esp+424h] [ebp-D0h]
  float v804; // [esp+428h] [ebp-CCh]
  float v805; // [esp+42Ch] [ebp-C8h]
  float v806; // [esp+430h] [ebp-C4h]
  float v807; // [esp+434h] [ebp-C0h]
  float v808; // [esp+438h] [ebp-BCh]
  float v809; // [esp+43Ch] [ebp-B8h]
  float v810; // [esp+440h] [ebp-B4h]
  float v811; // [esp+444h] [ebp-B0h]
  float v812; // [esp+448h] [ebp-ACh]
  float v813; // [esp+44Ch] [ebp-A8h]
  float v814; // [esp+450h] [ebp-A4h]
  float v815; // [esp+454h] [ebp-A0h]
  float v816; // [esp+458h] [ebp-9Ch]
  float v817; // [esp+464h] [ebp-90h]
  float v818; // [esp+468h] [ebp-8Ch]
  float v819; // [esp+46Ch] [ebp-88h]
  float v820; // [esp+470h] [ebp-84h]
  float v821; // [esp+474h] [ebp-80h]
  float v822; // [esp+478h] [ebp-7Ch]
  float v823; // [esp+47Ch] [ebp-78h]
  float v824; // [esp+480h] [ebp-74h]
  float v825; // [esp+484h] [ebp-70h]
  float v826; // [esp+488h] [ebp-6Ch]
  int *v827; // [esp+48Ch] [ebp-68h]
  int v828; // [esp+490h] [ebp-64h]
  int v829; // [esp+494h] [ebp-60h]
  int v830; // [esp+498h] [ebp-5Ch]
  float *v831; // [esp+49Ch] [ebp-58h]
  float *v832; // [esp+4A0h] [ebp-54h]
  _DWORD *v833; // [esp+4A4h] [ebp-50h]
  float v834; // [esp+4A8h] [ebp-4Ch]
  float v835; // [esp+4ACh] [ebp-48h]
  float v836; // [esp+4B0h] [ebp-44h]
  float v837; // [esp+4B4h] [ebp-40h]
  float v838; // [esp+4B8h] [ebp-3Ch]
  float v839; // [esp+4BCh] [ebp-38h]
  float v840; // [esp+4C0h] [ebp-34h]
  float v841; // [esp+4C8h] [ebp-2Ch]
  float v842; // [esp+4CCh] [ebp-28h]
  float v843; // [esp+4D0h] [ebp-24h]
  int v844; // [esp+4E0h] [ebp-14h]

  v827 = a1;
  v828 = a2;
  v829 = a3;
  cars_drawn = 0;
  num_pols = 0;
  for (i = 0; TrackSize + 1 >= i; ++i) {
    if (first_size + 1 >= i || i >= gap_size) {
      v5 = start_sect + i;
      if (start_sect + i >= TRAK_LEN)
        v5 -= TRAK_LEN;
      if (v5 < 0)
        v5 += TRAK_LEN;
      v6 = &TrakPt[18 * v5];
      v7 = (char *)&TrackScreenXYZ + 128 * v5;
      v620 = v6;
      v8 = v6 + 12;
      v619 = v6 + 6;
      v9 = v6 + 9;
      v6 += 6;
      *((_DWORD *)v7 + 1) = 0;
      v10 = *v6 - viewx;
      v11 = v6[1] - viewy;
      v12 = v6[2] - viewz;
      v843 = v10 * vk1 + v11 * vk4 + v12 * vk7;
      v842 = v10 * vk2 + v11 * vk5 + v12 * vk8;
      v13 = v10 * vk3 + v11 * vk6 + v12 * vk9;
      v841 = v13;
      _CHP(v6, v7);
      v631 = (int)v13;
      v15 = v841 < (double)drawtrk3_c_variable_4;
      v16 = 0;
      v17 = v841 == drawtrk3_c_variable_4;
      LOWORD(v18) = v14;
      if (v841 < (double)drawtrk3_c_variable_4) {
        v841 = 80.0;
        ++*((_DWORD *)v7 + 1);
      }
      v19 = (double)VIEWDIST;
      v20 = 1.0 / v841;
      v21 = v19 * v843 * v20 + (double)xbase;
      _CHP(v18, v7);
      xp = (int)v21;
      v22 = v20 * (v19 * v842) + (double)ybase;
      _CHP(scr_size * (int)v21, v7);
      yp = (int)v22;
      *((_DWORD *)v7 + 7) = v23 >> 6;
      v24 = scr_size * (199 - yp);
      *((float *)v7 + 11) = (float)v631;
      *((_DWORD *)v7 + 8) = v24 >> 6;
      *((float *)v7 + 9) = v843;
      *((float *)v7 + 10) = v842;
      v25 = *v620 - viewx;
      v26 = v620[1] - viewy;
      v27 = v620[2] - viewz;
      v843 = v25 * vk1 + v26 * vk4 + v27 * vk7;
      v842 = v25 * vk2 + v26 * vk5 + v27 * vk8;
      v28 = v25 * vk3 + v26 * vk6 + v27 * vk9;
      v841 = v28;
      _CHP(v620, v7);
      v631 = (int)v28;
      v30 = v841 < (double)drawtrk3_c_variable_4;
      v31 = 0;
      v32 = v841 == drawtrk3_c_variable_4;
      LOWORD(v33) = v29;
      if (v841 < (double)drawtrk3_c_variable_4) {
        v841 = 80.0;
        ++*((_DWORD *)v7 + 1);
      }
      v34 = (double)VIEWDIST;
      v35 = 1.0 / v841;
      v36 = v34 * v843 * v35 + (double)xbase;
      _CHP(v33, v7);
      xp = (int)v36;
      v37 = v35 * (v34 * v842) + (double)ybase;
      _CHP(scr_size * (int)v36, v7);
      yp = (int)v37;
      *((_DWORD *)v7 + 2) = v38 >> 6;
      v39 = scr_size * (199 - yp);
      *((float *)v7 + 6) = (float)v631;
      *((_DWORD *)v7 + 3) = v39 >> 6;
      *((float *)v7 + 4) = v843;
      v40 = v842;
      *((float *)v7 + 5) = v842;
      v41 = *v9 - viewx;
      v42 = v9[1] - viewy;
      v43 = v9[2] - viewz;
      v843 = v41 * vk1 + v42 * vk4 + v43 * vk7;
      v842 = v41 * vk2 + v42 * vk5 + v43 * vk8;
      v44 = v41 * vk3 + v42 * vk6 + v43 * vk9;
      v841 = v44;
      _CHP(LODWORD(v40), v7);
      v631 = (int)v44;
      v46 = v841 < (double)drawtrk3_c_variable_4;
      v47 = 0;
      v48 = v841 == drawtrk3_c_variable_4;
      LOWORD(v49) = v45;
      if (v841 < (double)drawtrk3_c_variable_4) {
        v49 = *((_DWORD *)v7 + 1) + 1;
        v841 = 80.0;
        *((_DWORD *)v7 + 1) = v49;
      }
      v50 = (double)VIEWDIST;
      v51 = 1.0 / v841;
      v52 = v50 * v843 * v51 + (double)xbase;
      _CHP(v49, v7);
      xp = (int)v52;
      v53 = v51 * (v50 * v842) + (double)ybase;
      _CHP(scr_size * (int)v52, v7);
      yp = (int)v53;
      *((_DWORD *)v7 + 12) = v54 >> 6;
      v55 = scr_size * (199 - yp);
      *((float *)v7 + 16) = (float)v631;
      *((_DWORD *)v7 + 13) = v55 >> 6;
      *((float *)v7 + 14) = v843;
      v56 = v842;
      *((float *)v7 + 15) = v842;
      v57 = *v8 - viewx;
      v58 = v8[1] - viewy;
      v59 = v8[2] - viewz;
      v843 = v57 * vk1 + v58 * vk4 + v59 * vk7;
      v842 = v57 * vk2 + v58 * vk5 + v59 * vk8;
      v60 = v57 * vk3 + v58 * vk6 + v59 * vk9;
      v841 = v60;
      _CHP(LODWORD(v56), v7);
      v631 = (int)v60;
      v62 = v841 < (double)drawtrk3_c_variable_4;
      v63 = 0;
      v64 = v841 == drawtrk3_c_variable_4;
      LOWORD(v65) = v61;
      if (v841 < (double)drawtrk3_c_variable_4) {
        v65 = *((_DWORD *)v7 + 1) + 1;
        v841 = 80.0;
        *((_DWORD *)v7 + 1) = v65;
      }
      v66 = (double)VIEWDIST;
      v67 = 1.0 / v841;
      v68 = v66 * v843 * v67 + (double)xbase;
      _CHP(v65, v7);
      xp = (int)v68;
      v69 = v67 * (v66 * v842) + (double)ybase;
      v70 = scr_size;
      _CHP(scr_size * (int)v68, v7);
      yp = (int)v69;
      *((_DWORD *)v7 + 17) = v71 >> 6;
      *((_DWORD *)v7 + 18) = (v70 * (199 - yp)) >> 6;
      *((float *)v7 + 19) = v843;
      *((float *)v7 + 20) = v842;
      *((float *)v7 + 21) = (float)v631;
      v72 = (int *)((char *)&TrakColour + 24 * v5 + 12);
      v73 = v5 ? v5 - 1 : TRAK_LEN - 1;
      v74 = (int *)((char *)&TrakColour + 24 * v73 + 12);
      if (*v72 && *v74) {
        v731 = 72 * v5;
        v75 = &TrakPt[18 * v5];
        v76 = v75[3] - viewx;
        v77 = v75[4] - viewy;
        v78 = v75[5] - viewz;
        v747 = v76 * vk1 + v77 * vk4 + v78 * vk7;
        v743 = v76 * vk2 + v77 * vk5 + v78 * vk8;
        v79 = v76 * vk3 + v77 * vk6 + v78 * vk9;
        v739 = v79;
        _CHP(v75, v7);
        v735 = (int)v79;
        v85 = v81 + 12;
        v82 = v739 < (double)drawtrk3_c_variable_4;
        v83 = 0;
        v84 = v739 == drawtrk3_c_variable_4;
        LOWORD(v85) = v80;
        if (v739 < (double)drawtrk3_c_variable_4)
          v739 = 80.0;
        v86 = (double)VIEWDIST;
        v87 = 1.0 / v739;
        v88 = v86 * v747 * v87 + (double)xbase;
        _CHP(v85, v7);
        xp = (int)v88;
        v89 = v87 * (v86 * v743) + (double)ybase;
        _CHP(scr_size * (int)v88, v7);
        yp = (int)v89;
        *((_DWORD *)v7 + 22) = v90 >> 6;
        v91 = scr_size * (199 - yp);
        *((float *)v7 + 26) = (float)v735;
        *((_DWORD *)v7 + 23) = v91 >> 6;
        *((float *)v7 + 24) = v747;
        *((float *)v7 + 25) = v743;
      } else {
        if (*v72 >= 0 && *v74 >= 0) {
          *((_DWORD *)v7 + 24) = *((_DWORD *)v7 + 4);
          *((_DWORD *)v7 + 25) = *((_DWORD *)v7 + 5);
          v92 = *((float *)v7 + 6);
          *((_DWORD *)v7 + 22) = *((_DWORD *)v7 + 2);
          v93 = *((_DWORD *)v7 + 3);
        } else {
          *((_DWORD *)v7 + 24) = *((_DWORD *)v7 + 9);
          *((_DWORD *)v7 + 25) = *((_DWORD *)v7 + 10);
          v92 = *((float *)v7 + 11);
          *((_DWORD *)v7 + 22) = *((_DWORD *)v7 + 7);
          v93 = *((_DWORD *)v7 + 8);
        }
        *((_DWORD *)v7 + 23) = v93;
        *((float *)v7 + 26) = v92;
      }
      if (*((_DWORD *)&TrakColour + 6 * v5 + 4) && v74[1]) {
        v94 = &TrakPt[18 * v5];
        v95 = v94[15] - viewx;
        v96 = v94[16] - viewy;
        v97 = v94[17] - viewz;
        v746 = v95 * vk1 + v96 * vk4 + v97 * vk7;
        v742 = v95 * vk2 + v96 * vk5 + v97 * vk8;
        v98 = v95 * vk3 + v96 * vk6 + v97 * vk9;
        v738 = v98;
        _CHP(v94, v7);
        v734 = (int)v98;
        v104 = v100 + 60;
        v101 = v738 < (double)drawtrk3_c_variable_4;
        v102 = 0;
        v103 = v738 == drawtrk3_c_variable_4;
        LOWORD(v104) = v99;
        if (v738 < (double)drawtrk3_c_variable_4)
          v738 = 80.0;
        v105 = (double)VIEWDIST;
        v106 = 1.0 / v738;
        v107 = v105 * v746 * v106 + (double)xbase;
        _CHP(v104, v7);
        xp = (int)v107;
        v108 = v106 * (v105 * v742) + (double)ybase;
        v109 = scr_size;
        _CHP(scr_size * (int)v107, v7);
        yp = (int)v108;
        *((_DWORD *)v7 + 27) = v110 >> 6;
        v111 = v109 * (199 - yp);
        *((float *)v7 + 31) = (float)v734;
        *((_DWORD *)v7 + 28) = v111 >> 6;
        *((float *)v7 + 29) = v746;
        *((float *)v7 + 30) = v742;
      } else {
        if (*((int *)&TrakColour + 6 * v5 + 4) >= 0 && v74[1] >= 0) {
          *((_DWORD *)v7 + 29) = *((_DWORD *)v7 + 19);
          *((_DWORD *)v7 + 30) = *((_DWORD *)v7 + 20);
          v112 = *((float *)v7 + 21);
          *((_DWORD *)v7 + 27) = *((_DWORD *)v7 + 17);
          v113 = *((_DWORD *)v7 + 18);
        } else {
          *((_DWORD *)v7 + 29) = *((_DWORD *)v7 + 14);
          *((_DWORD *)v7 + 30) = *((_DWORD *)v7 + 15);
          v112 = *((float *)v7 + 16);
          *((_DWORD *)v7 + 27) = *((_DWORD *)v7 + 12);
          v113 = *((_DWORD *)v7 + 13);
        }
        *((_DWORD *)v7 + 28) = v113;
        *((float *)v7 + 31) = v112;
      }
      if (Banks_On) {
        v114 = (char *)&GroundScreenXYZ + 128 * v5;
        v115 = v114 + 8;
        *((_DWORD *)v114 + 1) = 0;
        v116 = &GroundPt[18 * v5];
        v833 = (_DWORD *)((char *)&GroundColour + 20 * v5);
        if (v5)
          v117 = v5 - 1;
        else
          v117 = TRAK_LEN - 1;
        v729 = (_DWORD *)((char *)&GroundColour + 20 * v117);
        v118 = 0;
        v723 = v5 << 7;
        do {
          if (*v833 != -1 || *v729 != -1) {
            if (v118 < 2 || v118 > 3 || *v833 != -2 || *(int *)((char *)&TrackScreenXYZ_variable_1 + v723) == 99) {
              v119 = *v116 - viewx;
              v120 = v116[1] - viewy;
              v121 = v116 + 2;
              v122 = *v121 - viewz;
              v745 = v119 * vk1 + v120 * vk4 + v122 * vk7;
              v741 = v119 * vk2 + v120 * vk5 + v122 * vk8;
              v123 = v119 * vk3 + v120 * vk6 + v122 * vk9;
              v737 = v123;
              _CHP(v121, v121);
              v733 = (int)v123;
              v116 = v121 + 1;
              v125 = v737 < (double)drawtrk3_c_variable_4;
              v126 = 0;
              v127 = v737 == drawtrk3_c_variable_4;
              LOWORD(v128) = v124;
              if (v737 < (double)drawtrk3_c_variable_4)
                v737 = 80.0;
              v129 = (double)VIEWDIST;
              v130 = 1.0 / v737;
              v131 = v129 * v745 * v130 + (double)xbase;
              _CHP(v128, v116);
              xp = (int)v131;
              v132 = v130 * (v129 * v741) + (double)ybase;
              _CHP(scr_size * (int)v131, v116);
              yp = (int)v132;
              *(_DWORD *)v115 = v133 >> 6;
              v134 = scr_size * (199 - yp);
              *((float *)v115 + 4) = (float)v733;
              *((_DWORD *)v115 + 1) = v134 >> 6;
              *((float *)v115 + 2) = v745;
              *((float *)v115 + 3) = v741;
              goto LABEL_58;
            }
            if (v118 == 2) {
              *(_DWORD *)v115 = *(int *)((char *)&TrackScreenXYZ_variable_2 + v723);
              *((_DWORD *)v115 + 1) = *(int *)((char *)&TrackScreenXYZ_variable_3 + v723);
              v135 = v723;
              *((_DWORD *)v115 + 2) = *(int *)((char *)&TrackScreenXYZ_variable_4 + v723);
              *((_DWORD *)v115 + 3) = *(int *)((char *)&TrackScreenXYZ_variable_5 + v135);
              v136 = *(int *)((char *)&TrackScreenXYZ_variable_6 + v135);
            } else {
              *(_DWORD *)v115 = *(int *)((char *)&TrackScreenXYZ_variable_7 + v723);
              *((_DWORD *)v115 + 1) = *(int *)((char *)&TrackScreenXYZ_variable_8 + v723);
              v137 = v723;
              *((_DWORD *)v115 + 2) = *(int *)((char *)&TrackScreenXYZ_variable_9 + v723);
              *((_DWORD *)v115 + 3) = *(int *)((char *)&TrackScreenXYZ_variable_10 + v137);
              v136 = *(int *)((char *)&TrackScreenXYZ_variable_11 + v137);
            }
            *((_DWORD *)v115 + 4) = v136;
          }
          v116 += 3;
        LABEL_58:
          if (v118 != 2) {
            ++v833;
            ++v729;
          }
          ++v118;
          v115 += 20;
        } while (v118 < 6);
      }
    }
  }
  v138 = TrackSize;
  num_bits = 0;
  if (TrackSize >= 0) {
    while (v138 > first_size && v138 < gap_size) {
    LABEL_356:
      if (--v138 < 0)
        goto LABEL_357;
    }
    v139 = v138 + start_sect;
    if (v138 + start_sect < 0)
      v139 += TRAK_LEN;
    if (v139 >= TRAK_LEN)
      v139 -= TRAK_LEN;
    v632 = v139 + 1;
    if (v139 + 1 < 0)
      v632 += TRAK_LEN;
    if (v632 >= TRAK_LEN)
      v632 -= TRAK_LEN;
    v140 = v632;
    NextSect[v139] = v632;
    v140 <<= 7;
    a5 = (char *)&TrackScreenXYZ + 128 * v139;
    v831 = (float *)((char *)&GroundScreenXYZ + v140);
    a4 = (float *)((char *)&TrackScreenXYZ + v140);
    v141 = GroundColour_variable_4[5 * v139];
    v832 = (float *)((char *)&GroundScreenXYZ + 128 * v139);
    v142 = v141 != -1 && GroundColour_variable_4[5 * v632] != -1 && Banks_On;
    v143 = GroundColour_variable_4[5 * v139];
    v635 = v142;
    if (v143 != -2 && v142) {
      if (GroundColour_variable_4[5 * v632] == -2) {
        v147 = v632 + 2;
        if (v632 + 2 >= TRAK_LEN)
          v147 -= TRAK_LEN;
        v148 = (float *)((char *)&TrackScreenXYZ + 128 * v147);
        if (v148[16] <= (double)v148[11])
          v149 = v148[11];
        else
          v149 = v148[16];
        v675 = v149;
        if (a4[16] <= (double)a4[11])
          v150 = a4[11];
        else
          v150 = a4[16];
        v676 = v150;
        if (v675 <= (double)v150) {
          if (a4[16] <= (double)a4[11])
            v151 = *((_DWORD *)a4 + 11);
          else
            v151 = *((_DWORD *)a4 + 16);
          v551[8] = v151;
        } else {
          if (v148[16] <= (double)v148[11])
            v151 = *((_DWORD *)v148 + 11);
          else
            v151 = *((_DWORD *)v148 + 16);
          v551[7] = v151;
        }
        v551[6] = v151;
        v830 = v151;
        a5 = (char *)&TrackScreenXYZ + 128 * v139;
      } else {
        if (v831[16] <= (double)v831[21])
          v144 = v831[21];
        else
          v144 = v831[16];
        v670 = v144;
        if (v832[16] <= (double)v832[21])
          v145 = v832[21];
        else
          v145 = v832[16];
        v671 = v145;
        if (v670 <= (double)v145) {
          if (v832[16] <= (double)v832[21])
            v146 = *((_DWORD *)v832 + 21);
          else
            v146 = *((_DWORD *)v832 + 16);
          v674 = v146;
        } else {
          if (v831[16] <= (double)v831[21])
            v146 = *((_DWORD *)v831 + 21);
          else
            v146 = *((_DWORD *)v831 + 16);
          v673 = v146;
        }
        v672 = v146;
        v830 = v146;
      }
      v152 = (char *)&TrackView + 8 * num_bits;
      v153 = v830;
      v154 = num_bits;
      *(_WORD *)v152 = 2;
      *((_WORD *)v152 + 1) = v139;
      num_bits = v154 + 1;
      *((_DWORD *)v152 + 1) = v153;
    }
    if (*((_DWORD *)a5 + 1) != 99 && *((_DWORD *)a4 + 1) != 99 && Road_On) {
      if (*((float *)a5 + 16) <= (double)*((float *)a5 + 11))
        v155 = *((float *)a5 + 11);
      else
        v155 = *((float *)a5 + 16);
      v552 = v155;
      if (a4[16] <= (double)a4[11])
        v156 = a4[11];
      else
        v156 = a4[16];
      v553 = v156;
      if (v552 <= (double)v156) {
        if (a4[16] <= (double)a4[11])
          v157 = *((_DWORD *)a4 + 11);
        else
          v157 = *((_DWORD *)a4 + 16);
        v556 = v157;
      } else {
        if (*((float *)a5 + 16) <= (double)*((float *)a5 + 11))
          v157 = *((_DWORD *)a5 + 11);
        else
          v157 = *((_DWORD *)a5 + 16);
        v555 = v157;
      }
      v554 = v157;
      v158 = (char *)&TrackView + 8 * num_bits;
      v159 = v554;
      v160 = num_bits;
      *(_WORD *)v158 = 5;
      *((_WORD *)v158 + 1) = v139;
      num_bits = v160 + 1;
      *((_DWORD *)v158 + 1) = v159;
    }
    if (*((_DWORD *)a5 + 1) != 99 && *((_DWORD *)a4 + 1) != 99 && Road_On) {
      if (*((float *)a5 + 6) <= (double)*((float *)a5 + 11))
        v161 = *((float *)a5 + 11);
      else
        v161 = *((float *)a5 + 6);
      v681 = v161;
      if (a4[6] <= (double)a4[11])
        v162 = a4[11];
      else
        v162 = a4[6];
      v682 = v162;
      if (v681 <= (double)v162) {
        if (a4[6] <= (double)a4[11])
          v163 = *((_DWORD *)a4 + 11);
        else
          v163 = *((_DWORD *)a4 + 6);
        v685 = v163;
      } else {
        if (*((float *)a5 + 6) <= (double)*((float *)a5 + 11))
          v163 = *((_DWORD *)a5 + 11);
        else
          v163 = *((_DWORD *)a5 + 6);
        v684 = v163;
      }
      v683 = v163;
      v164 = (char *)&TrackView + 8 * num_bits;
      v165 = v683;
      v166 = num_bits;
      *(_WORD *)v164 = 6;
      *((_WORD *)v164 + 1) = v139;
      num_bits = v166 + 1;
      *((_DWORD *)v164 + 1) = v165;
    }
    if (*((_DWORD *)a5 + 1) != 99 && *((_DWORD *)a4 + 1) != 99 && Road_On) {
      if (*((float *)a5 + 16) <= (double)*((float *)a5 + 21))
        v167 = *((float *)a5 + 21);
      else
        v167 = *((float *)a5 + 16);
      v686 = v167;
      if (a4[16] <= (double)a4[21])
        v168 = a4[21];
      else
        v168 = a4[16];
      v557 = v168;
      if (v686 <= (double)v168) {
        if (a4[16] <= (double)a4[21])
          v169 = *((_DWORD *)a4 + 21);
        else
          v169 = *((_DWORD *)a4 + 16);
        v560 = v169;
      } else {
        if (*((float *)a5 + 16) <= (double)*((float *)a5 + 21))
          v169 = *((_DWORD *)a5 + 21);
        else
          v169 = *((_DWORD *)a5 + 16);
        v559 = v169;
      }
      v558 = v169;
      v170 = (char *)&TrackView + 8 * num_bits;
      v171 = v558;
      v172 = num_bits;
      *(_WORD *)v170 = 7;
      *((_WORD *)v170 + 1) = v139;
      num_bits = v172 + 1;
      *((_DWORD *)v170 + 1) = v171;
    }
    if (*((_DWORD *)a5 + 1) != 99 && *((_DWORD *)a4 + 1) != 99) {
      if (Walls_On) {
        v173 = 24 * v139;
        v174 = TrakColour_variable_12[6 * v139];
        if (v174 != -1 && v634 && v633) {
          if (v174 < 0) {
            if (v831[31] >= (double)v831[6])
              v175 = v831[6];
            else
              v175 = v831[31];
            v561 = v175;
            if (v831[11] >= (double)v831[26])
              v176 = v831[26];
            else
              v176 = v831[11];
            v562 = v176;
            if (v561 >= (double)v176) {
              if (v831[11] >= (double)v831[26])
                v177 = *((_DWORD *)v831 + 26);
              else
                v177 = *((_DWORD *)v831 + 11);
              v565 = v177;
            } else {
              if (v831[31] >= (double)v831[6])
                v177 = *((_DWORD *)v831 + 6);
              else
                v177 = *((_DWORD *)v831 + 31);
              v564 = v177;
            }
            v563 = v177;
            v178 = (char *)&TrackView + 8 * num_bits;
            *(_WORD *)v178 = 10;
            v179 = v563;
            *((_WORD *)v178 + 1) = v139;
            *((_DWORD *)v178 + 1) = v179;
            ++num_bits;
            goto LABEL_238;
          }
          v180 = TrakColour_variable_12[6 * v632];
          if (v180 <= 0) {
            if (v180 >= -1)
              goto LABEL_238;
            if (v832[31] >= (double)v832[6])
              v187 = v832[6];
            else
              v187 = v832[31];
            v571 = v187;
            if (v832[11] >= (double)v832[26])
              v188 = v832[26];
            else
              v188 = v832[11];
            v572 = v188;
            if (v571 >= (double)v188) {
              if (v832[11] >= (double)v832[26])
                v189 = v832[26];
              else
                v189 = v832[11];
              v575 = v189;
            } else {
              if (v832[31] >= (double)v832[6])
                v189 = v832[6];
              else
                v189 = v832[31];
              v574 = v189;
            }
            v573 = v189;
            v185 = (char *)&TrackView + 8 * num_bits;
            v186 = v573;
          } else {
            if (TrakColour_variable_11[6 * v139] >= 0)
              v181 = *((float *)a5 + 21);
            else
              v181 = *((float *)a5 + 16);
            _CHP(24 * v632, v173);
            v633 = (int)v181;
            if (TrakColour_variable_10[6 * v139] >= 0)
              v182 = *((float *)a5 + 6);
            else
              v182 = *((float *)a5 + 11);
            _CHP(24 * v139, v173);
            v634 = (int)v182;
            if (*((float *)a5 + 26) >= (double)*((float *)a5 + 31))
              v183 = *((float *)a5 + 31);
            else
              v183 = *((float *)a5 + 26);
            v566 = v183;
            if (v633 >= v634)
              v567 = v634;
            else
              v567 = v633;
            if ((double)v567 >= v566) {
              if (*((float *)a5 + 26) >= (double)*((float *)a5 + 31))
                v184 = *((float *)a5 + 31);
              else
                v184 = *((float *)a5 + 26);
              v570 = v184;
              v568 = v184;
            } else {
              if (v633 >= v634)
                v569 = v634;
              else
                v569 = v633;
              v568 = (float)v569;
            }
            v185 = (char *)&TrackView + 8 * num_bits;
            v186 = v568;
          }
          v190 = num_bits;
          *(_WORD *)v185 = 10;
          *((_WORD *)v185 + 1) = v139;
          num_bits = v190 + 1;
          *((float *)v185 + 1) = v186;
        }
      }
    }
  LABEL_238:
    if (GroundColour_variable_2[5 * v139] != -1 && v635) {
      if (v831[16] <= (double)v831[11])
        v191 = v831[11];
      else
        v191 = v831[16];
      v576 = v191;
      if (v832[16] <= (double)v832[11])
        v192 = v832[11];
      else
        v192 = v832[16];
      v577 = v192;
      if (v576 <= (double)v192) {
        if (v832[16] <= (double)v832[11])
          v193 = *((_DWORD *)v832 + 11);
        else
          v193 = *((_DWORD *)v832 + 16);
        v580 = v193;
      } else {
        if (v831[16] <= (double)v831[11])
          v193 = *((_DWORD *)v831 + 11);
        else
          v193 = *((_DWORD *)v831 + 16);
        v579 = v193;
      }
      v578 = v193;
      v194 = (char *)&TrackView + 8 * num_bits;
      *(_WORD *)v194 = 3;
      v195 = v578;
      *((_WORD *)v194 + 1) = v139;
      *((_DWORD *)v194 + 1) = v195;
      ++num_bits;
    }
    if (GroundColour_variable_5[5 * v139] != -1 && v635) {
      if (v831[21] <= (double)v831[26])
        v196 = v831[26];
      else
        v196 = v831[21];
      v581 = v196;
      if (v832[21] <= (double)v832[26])
        v197 = v832[26];
      else
        v197 = v832[21];
      v582 = v197;
      if (v581 <= (double)v197) {
        if (v832[21] <= (double)v832[26])
          v198 = *((_DWORD *)v832 + 26);
        else
          v198 = *((_DWORD *)v832 + 21);
        v585 = v198;
      } else {
        if (v831[21] <= (double)v831[26])
          v198 = *((_DWORD *)v831 + 26);
        else
          v198 = *((_DWORD *)v831 + 21);
        v584 = v198;
      }
      v583 = v198;
      v199 = (char *)&TrackView + 8 * num_bits;
      *(_WORD *)v199 = 4;
      v200 = v583;
      *((_WORD *)v199 + 1) = v139;
      *((_DWORD *)v199 + 1) = v200;
      ++num_bits;
    }
    if (*((_DWORD *)a5 + 1) != 99 && *((_DWORD *)a4 + 1) != 99) {
      if (Walls_On) {
        v634 = TrakColour_variable_10[6 * v139];
        if (v634) {
          if (TrackInfo_variable_8[9 * v139] >= 0.0 && TrackInfo_variable_8[9 * v632] >= 0.0) {
            if (v634 >= 0) {
              if (a4[6] <= (double)*((float *)a5 + 6))
                v206 = *((float *)a5 + 6);
              else
                v206 = a4[6];
              v591 = v206;
              if (a4[26] <= (double)*((float *)a5 + 26))
                v207 = *((float *)a5 + 26);
              else
                v207 = a4[26];
              v592 = v207;
              if (v591 <= (double)v207) {
                if (a4[26] <= (double)*((float *)a5 + 26))
                  v208 = *((float *)a5 + 26);
                else
                  v208 = a4[26];
                v595 = v208;
              } else {
                if (a4[6] <= (double)*((float *)a5 + 6))
                  v208 = *((float *)a5 + 6);
                else
                  v208 = a4[6];
                v594 = v208;
              }
              v593 = v208;
              v728 = v208;
            } else {
              v728 = (a4[11] + *((float *)a5 + 11) + a4[26] + *((float *)a5 + 26)) * drawtrk3_c_variable_3;
            }
            v209 = (char *)&TrackView + 8 * num_bits;
            *(_WORD *)v209 = 8;
            v210 = v728;
            *((_WORD *)v209 + 1) = v139;
            *((float *)v209 + 1) = v210;
            ++num_bits;
          } else {
            if (*((float *)a5 + 6) <= (double)*((float *)a5 + 11))
              v201 = *((float *)a5 + 11);
            else
              v201 = *((float *)a5 + 6);
            v586 = v201;
            if (a4[6] <= (double)a4[11])
              v202 = a4[11];
            else
              v202 = a4[6];
            v587 = v202;
            if (v586 <= (double)v202) {
              if (a4[6] <= (double)a4[11])
                v203 = *((_DWORD *)a4 + 11);
              else
                v203 = *((_DWORD *)a4 + 6);
              v590 = v203;
            } else {
              if (*((float *)a5 + 6) <= (double)*((float *)a5 + 11))
                v203 = *((_DWORD *)a5 + 11);
              else
                v203 = *((_DWORD *)a5 + 6);
              v589 = v203;
            }
            v588 = v203;
            v204 = (char *)&TrackView + 8 * num_bits;
            *((_DWORD *)v204 + 1) = v588;
            v205 = num_bits;
            *(_WORD *)v204 = 0;
            *((_WORD *)v204 + 1) = v139;
            num_bits = v205 + 1;
          }
        }
      }
    }
    if (*((_DWORD *)a5 + 1) != 99 && *((_DWORD *)a4 + 1) != 99) {
      if (Walls_On) {
        v633 = TrakColour_variable_11[6 * v139];
        if (v633) {
          if (TrackInfo_variable_8[9 * v139] >= 0.0 && TrackInfo_variable_8[9 * v632] >= 0.0) {
            if (v633 >= 0) {
              if (*((float *)a5 + 21) <= (double)a4[21])
                v217 = a4[21];
              else
                v217 = *((float *)a5 + 21);
              v600 = v217;
              if (*((float *)a5 + 31) <= (double)a4[31])
                v218 = a4[31];
              else
                v218 = *((float *)a5 + 31);
              v601 = v218;
              if (v600 <= (double)v218) {
                if (*((float *)a5 + 31) <= (double)a4[31])
                  v219 = a4[31];
                else
                  v219 = *((float *)a5 + 31);
                v604 = v219;
              } else {
                if (*((float *)a5 + 21) <= (double)a4[21])
                  v219 = a4[21];
                else
                  v219 = *((float *)a5 + 21);
                v603 = v219;
              }
              v602 = v219;
              v727 = v219;
            } else {
              v727 = (*((float *)a5 + 16) + a4[16] + *((float *)a5 + 31) + a4[31]) * drawtrk3_c_variable_3;
            }
            v220 = (float *)((char *)&TrackView + 8 * num_bits);
            v220[1] = v727;
            v221 = num_bits;
            *(_WORD *)v220 = 9;
            *((_WORD *)v220 + 1) = v139;
            num_bits = v221 + 1;
          } else {
            if (*((float *)a5 + 16) <= (double)*((float *)a5 + 21))
              v211 = *((float *)a5 + 21);
            else
              v211 = *((float *)a5 + 16);
            v625 = v211;
            if (a4[16] <= (double)a4[21])
              v212 = a4[21];
            else
              v212 = a4[16];
            v596 = v212;
            if (v625 <= (double)v212) {
              if (a4[16] <= (double)a4[21])
                v213 = *((_DWORD *)a4 + 21);
              else
                v213 = *((_DWORD *)a4 + 16);
              v599 = v213;
            } else {
              if (*((float *)a5 + 16) <= (double)*((float *)a5 + 21))
                v213 = *((_DWORD *)a5 + 21);
              else
                v213 = *((_DWORD *)a5 + 16);
              v598 = v213;
            }
            v597 = v213;
            v214 = (char *)&TrackView + 8 * num_bits;
            v215 = v597;
            v216 = num_bits;
            *(_WORD *)v214 = 1;
            *((_WORD *)v214 + 1) = v139;
            num_bits = v216 + 1;
            *((_DWORD *)v214 + 1) = v215;
          }
        }
      }
    }
    goto LABEL_356;
  }
LABEL_357:
  v222 = 0;
  if (numcars > 0) {
    v223 = 0;
    v224 = (char *)&TrackView + 8 * num_bits;
    do {
      v225 = car_draw_order[v223];
      if (v225 == -3 || v225 >= 0) {
        v226 = car_draw_order_variable_2[v223];
        *(_WORD *)v224 = 11;
        v731 = v226;
        v227 = cars_drawn;
        *((_WORD *)v224 + 1) = car_draw_order_variable_1[v223];
        *((_DWORD *)v224 + 1) = v731;
        v224 += 8;
        cars_drawn = v227 + 1;
        ++num_bits;
      }
      ++v222;
      v223 += 3;
    } while (v222 < numcars);
  }
  v228 = 0;
  v229 = 0;
  NamesLeft = 0;
  VisibleCars = 0;
  VisibleHumans = 0;
  if (numcars > 0) {
    v605 = 12 * v829;
    v230 = 0;
    v724 = 12 * numcars;
    do {
      v231 = car_draw_order[v230 / 4];
      if ((v231 == -3 || v231 >= 0) && v829 != car_draw_order_variable_1[v230 / 4]) {
        if (*(float *)&car_draw_order_variable_2[v230 / 4] < (double)*(float *)&car_draw_order_variable_2[v605 / 4]) {
          if (human_control[car_draw_order_variable_1[v230 / 4]])
            ++VisibleCars;
          ++NamesLeft;
        } else {
          if (human_control[car_draw_order_variable_1[v230 / 4]])
            ++VisibleHumans;
          ++v228;
        }
      }
      v230 += 12;
      ++v229;
    } while ((int)v230 < v724);
  }
  if (NamesLeft <= 1) {
    CarsLeft = v228 + 2 - NamesLeft;
  } else {
    CarsLeft = v228;
    if (v228 < 6) {
      if (NamesLeft >= 4)
        v232 = v228 + 3;
      else
        v232 = NamesLeft + v228;
      CarsLeft = v232;
    }
  }
  if (VisibleCars < 2)
    VisibleHumans = VisibleHumans + 2 - VisibleCars;
  if (!names_on) {
    NamesLeft = 1000;
    goto LABEL_393;
  }
  if ((unsigned int)names_on <= 1) {
    v233 = CarsLeft;
  LABEL_392:
    NamesLeft = v233;
    goto LABEL_393;
  }
  if (names_on == 2) {
    v233 = VisibleHumans;
    goto LABEL_392;
  }
LABEL_393:
  v234 = &VisibleBuildings;
  if (VisibleBuildings != -1) {
    v235 = (char *)&TrackView + 8 * num_bits;
    do {
      v236 = num_bits;
      v237 = v234[1];
      *(_WORD *)v235 = 13;
      v731 = v237;
      LOWORD(v237) = *(_WORD *)v234;
      v234 += 2;
      *((_WORD *)v235 + 1) = v237;
      *((_DWORD *)v235 + 1) = v731;
      v235 += 8;
      v238 = *v234;
      num_bits = v236 + 1;
    } while (v238 != -1);
  }
  if (countdown > -72 && replaytype != 2 && game_type != 2 && !winner_mode) {
    v239 = 0;
    v240 = (float *)((char *)&TrackView + 8 * num_bits);
    v241 = 36 * v828;
    do {
      v726 = (SLight[v241] - viewx) * vk3
        + (SLight_variable_1[v241] - viewy) * vk6
        + (SLight_variable_2[v241] - viewz) * vk9;
      if (v726 > 0.0) {
        *(_WORD *)v240 = 14;
        v240 += 2;
        v242 = v726;
        v243 = num_bits;
        *((_WORD *)v240 - 3) = v239;
        *(v240 - 1) = v242;
        num_bits = v243 + 1;
      }
      ++v239;
      v241 += 12;
    } while (v239 < 3);
  }
  qsort(&TrackView, num_bits, 8, Zcmp);
  result = 0;
  v748 = 0;
  if (num_bits > 0) {
    v722 = 144 * v828;
    while (2) {
      v245 = (float *)((char *)&TrackView + 8 * (num_bits - 1 - v748));
      v725 = v245[1];
      v246 = *((__int16 *)v245 + 1);
      if (*(_WORD *)v245 != 11 && *(_WORD *)v245 != 14) {
        v632 = NextSect[v246];
        a5 = (char *)&TrackScreenXYZ + 128 * v246;
        v832 = (float *)((char *)&GroundScreenXYZ + 128 * v246);
        a4 = (float *)((char *)&TrackScreenXYZ + 128 * v632);
        v831 = (float *)((char *)&GroundScreenXYZ + 128 * v632);
      }
      v247 = 24 * v246;
      switch (*(_WORD *)v245) {
        case 0:
        case 8:
          if (TrakColour_variable_10[6 * v246] < 0) {
            v283 = 4;
            v284 = TrakColour_variable_10[6 * v246];
            LWallPoly_variable_3 = 4;
            LWallPoly = v284;
            if (v284 < 0)
              LWallPoly = -v284;
            LOBYTE(v283) = BYTE1(LWallPoly) | 0x20;
            BYTE1(LWallPoly) |= 0x20u;
            if ((textures_off & 4) != 0) {
              if ((v283 & 1) != 0) {
                v283 = remap_tex[(unsigned __int8)LWallPoly] + (LWallPoly & 0xFFFFFE00);
                LWallPoly = v283;
                goto LABEL_604;
              }
              if ((LWallPoly & 0x200000) == 0)
                goto LABEL_604;
            } else {
              v283 = textures_off;
              if ((textures_off & 0x800) == 0 || (LWallPoly & 0x200000) == 0) {
              LABEL_604:
                LWallPoly_variable_4 = *((_DWORD *)a4 + 22);
                LWallPoly_variable_5 = *((_DWORD *)a4 + 23);
                LWallPoly_variable_6 = *((_DWORD *)a5 + 22);
                LWallPoly_variable_7 = *((_DWORD *)a5 + 23);
                LWallPoly_variable_8 = *((_DWORD *)a5 + 7);
                LWallPoly_variable_9 = *((_DWORD *)a5 + 8);
                LWallPoly_variable_10 = *((_DWORD *)a4 + 7);
                LWallPoly_variable_11 = *((_DWORD *)a4 + 8);
                if ((LWallPoly & 0x10000) != 0 && wide_on && (LWallPoly & 7) != 7) {
                  set_starts(1, v283);
                  if (a4[26] >= (double)*((float *)a5 + 26))
                    v285 = *((float *)a5 + 26);
                  else
                    v285 = a4[26];
                  v775 = v285;
                  if (*((float *)a5 + 11) >= (double)a4[11])
                    v286 = a4[11];
                  else
                    v286 = *((float *)a5 + 11);
                  v776 = v286;
                  if (v775 >= (double)v286) {
                    if (*((float *)a5 + 11) >= (double)a4[11])
                      v287 = a4[11];
                    else
                      v287 = *((float *)a5 + 11);
                    v779 = v287;
                  } else {
                    if (a4[26] >= (double)*((float *)a5 + 26))
                      v287 = *((float *)a5 + 26);
                    else
                      v287 = a4[26];
                    v778 = v287;
                  }
                  v777 = v287;
                  v844 = (unsigned __int8)Subdivide_variable_3[11 * v246];
                  if ((double)(__int16)v844 * subscale <= v287) {
                    if ((LWallPoly & 0x100) != 0)
                      goto LABEL_1090;
                  LABEL_625:
                    v261 = &LWallPoly;
                    POLYFLAT(v827, &LWallPoly);
                    goto LABEL_1197;
                  }
                  subdivide(
                    a4[24],
                    a4[25],
                    a4[26],
                    *((float *)a5 + 24),
                    *((float *)a5 + 25),
                    *((float *)a5 + 26),
                    *((float *)a5 + 9),
                    *((float *)a5 + 10),
                    *((float *)a5 + 11),
                    a4[9],
                    a4[10],
                    a4[11],
                    -1,
                    gfx_size);
                  goto LABEL_1265;
                }
                set_starts(0, v283);
                if (a4[26] >= (double)*((float *)a5 + 26))
                  v288 = *((float *)a5 + 26);
                else
                  v288 = a4[26];
                v780 = v288;
                if (*((float *)a5 + 11) >= (double)a4[11])
                  v289 = a4[11];
                else
                  v289 = *((float *)a5 + 11);
                v781 = v289;
                if (v780 >= (double)v289) {
                  if (*((float *)a5 + 11) >= (double)a4[11])
                    v290 = a4[11];
                  else
                    v290 = *((float *)a5 + 11);
                  v784 = v290;
                } else {
                  if (a4[26] >= (double)*((float *)a5 + 26))
                    v290 = *((float *)a5 + 26);
                  else
                    v290 = a4[26];
                  v783 = v290;
                }
                v782 = v290;
                v844 = (unsigned __int8)Subdivide_variable_3[11 * v246];
                if ((double)(__int16)v844 * subscale > v290) {
                  subdivide(
                    a4[24],
                    a4[25],
                    a4[26],
                    *((float *)a5 + 24),
                    *((float *)a5 + 25),
                    *((float *)a5 + 26),
                    *((float *)a5 + 9),
                    *((float *)a5 + 10),
                    *((float *)a5 + 11),
                    a4[9],
                    a4[10],
                    a4[11],
                    0,
                    gfx_size);
                  goto LABEL_1265;
                }
                if ((LWallPoly & 0x100) == 0)
                  goto LABEL_695;
              LABEL_1113:
                v256 = v827;
                POLYTEX(gfx_size);
                goto LABEL_1221;
              }
            }
            LWallPoly = 0x20000;
            goto LABEL_604;
          }
          LWallPoly = TrakColour_variable_10[6 * v246];
          LWallPoly_variable_3 = 4;
          BYTE1(LWallPoly) |= 0x20u;
          v291 = textures_off;
          if ((textures_off & 4) != 0) {
            if ((LWallPoly & 0x100) != 0) {
              v291 = remap_tex[(unsigned __int8)LWallPoly] + (LWallPoly & 0xFFFFFE00);
              LWallPoly = v291;
              goto LABEL_654;
            }
            if ((LWallPoly & 0x200000) == 0) {
            LABEL_654:
              LWallPoly_variable_4 = *((_DWORD *)a4 + 22);
              LWallPoly_variable_5 = *((_DWORD *)a4 + 23);
              LWallPoly_variable_6 = *((_DWORD *)a5 + 22);
              LWallPoly_variable_7 = *((_DWORD *)a5 + 23);
              LWallPoly_variable_8 = *((_DWORD *)a5 + 2);
              LWallPoly_variable_9 = *((_DWORD *)a5 + 3);
              LWallPoly_variable_10 = *((_DWORD *)a4 + 2);
              LWallPoly_variable_11 = *((_DWORD *)a4 + 3);
              if ((LWallPoly & 0x10000) == 0 || !wide_on || (LWallPoly & 7) == 7) {
                set_starts(0, v291);
                if (a4[26] >= (double)*((float *)a5 + 26))
                  v295 = *((float *)a5 + 26);
                else
                  v295 = a4[26];
                v790 = v295;
                if (*((float *)a5 + 6) >= (double)a4[6])
                  v296 = a4[6];
                else
                  v296 = *((float *)a5 + 6);
                v636 = v296;
                if (v790 >= (double)v296) {
                  if (*((float *)a5 + 6) >= (double)a4[6])
                    v297 = a4[6];
                  else
                    v297 = *((float *)a5 + 6);
                  v639 = v297;
                } else {
                  if (a4[26] >= (double)*((float *)a5 + 26))
                    v297 = *((float *)a5 + 26);
                  else
                    v297 = a4[26];
                  v638 = v297;
                }
                v637 = v297;
                v844 = (unsigned __int8)Subdivide_variable_3[11 * v246];
                if ((double)(__int16)v844 * subscale > v297) {
                  subdivide(
                    a4[24],
                    a4[25],
                    a4[26],
                    *((float *)a5 + 24),
                    *((float *)a5 + 25),
                    *((float *)a5 + 26),
                    *((float *)a5 + 4),
                    *((float *)a5 + 5),
                    *((float *)a5 + 6),
                    a4[4],
                    a4[5],
                    a4[6],
                    0,
                    gfx_size);
                  goto LABEL_1265;
                }
                if ((LWallPoly & 0x100) == 0) {
                LABEL_695:
                  v256 = &LWallPoly;
                  POLYFLAT(v827, &LWallPoly);
                  goto LABEL_1221;
                }
                goto LABEL_1113;
              }
              set_starts(1, v291);
              if (a4[26] >= (double)*((float *)a5 + 26))
                v292 = *((float *)a5 + 26);
              else
                v292 = a4[26];
              v785 = v292;
              if (*((float *)a5 + 6) >= (double)a4[6])
                v293 = a4[6];
              else
                v293 = *((float *)a5 + 6);
              v786 = v293;
              if (v785 >= (double)v293) {
                if (*((float *)a5 + 6) >= (double)a4[6])
                  v294 = a4[6];
                else
                  v294 = *((float *)a5 + 6);
                v789 = v294;
              } else {
                if (a4[26] >= (double)*((float *)a5 + 26))
                  v294 = *((float *)a5 + 26);
                else
                  v294 = a4[26];
                v788 = v294;
              }
              v787 = v294;
              v844 = (unsigned __int8)Subdivide_variable_3[11 * v246];
              if ((double)(__int16)v844 * subscale > v294) {
                subdivide(
                  a4[24],
                  a4[25],
                  a4[26],
                  *((float *)a5 + 24),
                  *((float *)a5 + 25),
                  *((float *)a5 + 26),
                  *((float *)a5 + 4),
                  *((float *)a5 + 5),
                  *((float *)a5 + 6),
                  a4[4],
                  a4[5],
                  a4[6],
                  -1,
                  gfx_size);
                goto LABEL_1265;
              }
              if ((LWallPoly & 0x100) == 0)
                goto LABEL_625;
              goto LABEL_1090;
            }
          } else if ((textures_off & 0x800) == 0 || (LWallPoly & 0x200000) == 0) {
            goto LABEL_654;
          }
          LWallPoly = 0x20000;
          goto LABEL_654;
        case 1:
        case 9:
          if (TrakColour_variable_11[6 * v246] < 0) {
            v298 = 4;
            v299 = TrakColour_variable_11[6 * v246];
            RWallPoly_variable_3 = 4;
            RWallPoly = v299;
            if (v299 < 0)
              RWallPoly = -v299;
            v300 = BYTE1(RWallPoly) | 0x20;
            BYTE1(RWallPoly) |= 0x20u;
            if ((textures_off & 4) != 0) {
              if ((v300 & 1) != 0) {
                v298 = remap_tex[(unsigned __int8)RWallPoly];
                RWallPoly = v298 + (RWallPoly & 0xFFFFFE00);
                goto LABEL_707;
              }
              if ((RWallPoly & 0x200000) == 0) {
              LABEL_707:
                RWallPoly_variable_4 = *((_DWORD *)a5 + 27);
                RWallPoly_variable_5 = *((_DWORD *)a5 + 28);
                RWallPoly_variable_6 = *((_DWORD *)a4 + 27);
                RWallPoly_variable_7 = *((_DWORD *)a4 + 28);
                RWallPoly_variable_8 = *((_DWORD *)a4 + 12);
                RWallPoly_variable_9 = *((_DWORD *)a4 + 13);
                RWallPoly_variable_10 = *((_DWORD *)a5 + 12);
                RWallPoly_variable_11 = *((_DWORD *)a5 + 13);
                if ((RWallPoly & 0x10000) == 0 || !wide_on || (RWallPoly & 7) == 7) {
                  set_starts(0, v298);
                  if (*((float *)a5 + 31) >= (double)a4[31])
                    v304 = a4[31];
                  else
                    v304 = *((float *)a5 + 31);
                  v793 = v304;
                  if (a4[16] >= (double)*((float *)a5 + 16))
                    v305 = *((float *)a5 + 16);
                  else
                    v305 = a4[16];
                  v794 = v305;
                  if (v793 >= (double)v305) {
                    if (a4[16] >= (double)*((float *)a5 + 16))
                      v306 = *((float *)a5 + 16);
                    else
                      v306 = a4[16];
                    v643 = v306;
                  } else {
                    if (*((float *)a5 + 31) >= (double)a4[31])
                      v306 = a4[31];
                    else
                      v306 = *((float *)a5 + 31);
                    v796 = v306;
                  }
                  v795 = v306;
                  v844 = (unsigned __int8)Subdivide_variable_4[11 * v246];
                  if ((double)(__int16)v844 * subscale > v306) {
                    subdivide(
                      *((float *)a5 + 29),
                      *((float *)a5 + 30),
                      *((float *)a5 + 31),
                      a4[29],
                      a4[30],
                      a4[31],
                      a4[14],
                      a4[15],
                      a4[16],
                      *((float *)a5 + 14),
                      *((float *)a5 + 15),
                      *((float *)a5 + 16),
                      0,
                      gfx_size);
                    goto LABEL_1265;
                  }
                  if ((RWallPoly & 0x100) == 0)
                    goto LABEL_798;
                  goto LABEL_1113;
                }
                set_starts(1, v298);
                if (*((float *)a5 + 31) >= (double)a4[31])
                  v301 = a4[31];
                else
                  v301 = *((float *)a5 + 31);
                v791 = v301;
                if (a4[16] >= (double)*((float *)a5 + 16))
                  v302 = *((float *)a5 + 16);
                else
                  v302 = a4[16];
                v640 = v302;
                if (v791 >= (double)v302) {
                  if (a4[16] >= (double)*((float *)a5 + 16))
                    v303 = *((float *)a5 + 16);
                  else
                    v303 = a4[16];
                  v792 = v303;
                } else {
                  if (*((float *)a5 + 31) >= (double)a4[31])
                    v303 = a4[31];
                  else
                    v303 = *((float *)a5 + 31);
                  v642 = v303;
                }
                v641 = v303;
                v844 = (unsigned __int8)Subdivide_variable_4[11 * v246];
                if ((double)(__int16)v844 * subscale > v303) {
                  subdivide(
                    *((float *)a5 + 29),
                    *((float *)a5 + 30),
                    *((float *)a5 + 31),
                    a4[29],
                    a4[30],
                    a4[31],
                    a4[14],
                    a4[15],
                    a4[16],
                    *((float *)a5 + 14),
                    *((float *)a5 + 15),
                    *((float *)a5 + 16),
                    -1,
                    gfx_size);
                  goto LABEL_1265;
                }
                if ((RWallPoly & 0x100) == 0) {
                LABEL_728:
                  v261 = &RWallPoly;
                  POLYFLAT(v827, &RWallPoly);
                  goto LABEL_1197;
                }
                goto LABEL_1090;
              }
            } else {
              v298 = textures_off;
              if ((textures_off & 0x800) == 0 || (RWallPoly & 0x200000) == 0)
                goto LABEL_707;
            }
            RWallPoly = 0x20000;
            goto LABEL_707;
          }
          RWallPoly = TrakColour_variable_11[6 * v246];
          RWallPoly_variable_3 = 4;
          v307 = BYTE1(RWallPoly) | 0x20;
          BYTE1(RWallPoly) |= 0x20u;
          v308 = textures_off;
          if ((textures_off & 4) != 0) {
            if ((v307 & 1) != 0) {
              v308 = remap_tex[(unsigned __int8)RWallPoly] + (RWallPoly & 0xFFFFFE00);
              RWallPoly = v308;
              goto LABEL_757;
            }
            if ((RWallPoly & 0x200000) == 0) {
            LABEL_757:
              RWallPoly_variable_4 = *((_DWORD *)a5 + 27);
              RWallPoly_variable_5 = *((_DWORD *)a5 + 28);
              RWallPoly_variable_6 = *((_DWORD *)a4 + 27);
              RWallPoly_variable_7 = *((_DWORD *)a4 + 28);
              RWallPoly_variable_8 = *((_DWORD *)a4 + 17);
              RWallPoly_variable_9 = *((_DWORD *)a4 + 18);
              RWallPoly_variable_10 = *((_DWORD *)a5 + 17);
              RWallPoly_variable_11 = *((_DWORD *)a5 + 18);
              if ((RWallPoly & 0x10000) == 0 || !wide_on || (RWallPoly & 7) == 7) {
                set_starts(0, v308);
                if (*((float *)a5 + 31) >= (double)a4[31])
                  v312 = a4[31];
                else
                  v312 = *((float *)a5 + 31);
                v648 = v312;
                if (a4[21] >= (double)*((float *)a5 + 21))
                  v313 = *((float *)a5 + 21);
                else
                  v313 = a4[21];
                v649 = v313;
                if (v648 >= (double)v313) {
                  if (a4[21] >= (double)*((float *)a5 + 21))
                    v314 = *((float *)a5 + 21);
                  else
                    v314 = a4[21];
                  v652 = v314;
                } else {
                  if (*((float *)a5 + 31) >= (double)a4[31])
                    v314 = a4[31];
                  else
                    v314 = *((float *)a5 + 31);
                  v651 = v314;
                }
                v650 = v314;
                v844 = (unsigned __int8)Subdivide_variable_4[11 * v246];
                if ((double)(__int16)v844 * subscale > v314) {
                  subdivide(
                    *((float *)a5 + 29),
                    *((float *)a5 + 30),
                    *((float *)a5 + 31),
                    a4[29],
                    a4[30],
                    a4[31],
                    a4[19],
                    a4[20],
                    a4[21],
                    *((float *)a5 + 19),
                    *((float *)a5 + 20),
                    *((float *)a5 + 21),
                    0,
                    gfx_size);
                  goto LABEL_1265;
                }
                if ((RWallPoly & 0x100) == 0) {
                LABEL_798:
                  v256 = &RWallPoly;
                  POLYFLAT(v827, &RWallPoly);
                  goto LABEL_1221;
                }
                goto LABEL_1113;
              }
              set_starts(1, v308);
              if (*((float *)a5 + 31) >= (double)a4[31])
                v309 = a4[31];
              else
                v309 = *((float *)a5 + 31);
              v797 = v309;
              if (a4[21] >= (double)*((float *)a5 + 21))
                v310 = *((float *)a5 + 21);
              else
                v310 = a4[21];
              v644 = v310;
              if (v797 >= (double)v310) {
                if (a4[21] >= (double)*((float *)a5 + 21))
                  v311 = *((float *)a5 + 21);
                else
                  v311 = a4[21];
                v647 = v311;
              } else {
                if (*((float *)a5 + 31) >= (double)a4[31])
                  v311 = a4[31];
                else
                  v311 = *((float *)a5 + 31);
                v646 = v311;
              }
              v645 = v311;
              v844 = (unsigned __int8)Subdivide_variable_4[11 * v246];
              if ((double)(__int16)v844 * subscale > v311) {
                subdivide(
                  *((float *)a5 + 29),
                  *((float *)a5 + 30),
                  *((float *)a5 + 31),
                  a4[29],
                  a4[30],
                  a4[31],
                  a4[19],
                  a4[20],
                  a4[21],
                  *((float *)a5 + 19),
                  *((float *)a5 + 20),
                  *((float *)a5 + 21),
                  -1,
                  gfx_size);
                goto LABEL_1265;
              }
              if ((RWallPoly & 0x100) == 0)
                goto LABEL_728;
              goto LABEL_1090;
            }
          } else if ((textures_off & 0x800) == 0 || (RWallPoly & 0x200000) == 0) {
            goto LABEL_757;
          }
          RWallPoly = 0x20000;
          goto LABEL_757;
        case 2:
          if (!facing_ok(
            v831[14],
            v831[15],
            v831[16],
            v832[14],
            v832[15],
            v832[16],
            v832[19],
            v832[20],
            v832[21],
            v831[19],
            v831[20],
            v831[21]))
            goto LABEL_1265;
          G3Poly = GroundColour_variable_4[5 * v246];
          G3Poly_variable_4 = *((_DWORD *)v831 + 17);
          G3Poly_variable_5 = *((_DWORD *)v831 + 18);
          G3Poly_variable_6 = *((_DWORD *)v831 + 12);
          G3Poly_variable_7 = *((_DWORD *)v831 + 13);
          G3Poly_variable_8 = *((_DWORD *)v832 + 12);
          G3Poly_variable_9 = *((_DWORD *)v832 + 13);
          G3Poly_variable_10 = *((_DWORD *)v832 + 17);
          G3Poly_variable_11 = *((_DWORD *)v832 + 18);
          G3Poly_variable_3 = 4;
          if ((G3Poly & 0x10000) != 0 && (G3Poly & 7) != 7) {
            set_starts(1, v247);
            if ((textures_off & 1) != 0 && (G3Poly & 0x100) != 0)
              G3Poly = remap_tex[(unsigned __int8)G3Poly] + (G3Poly & 0xFFFFFE00);
            if (v831[21] >= (double)v831[16])
              v342 = v831[16];
            else
              v342 = v831[21];
            v819 = v342;
            if (v832[16] >= (double)v832[21])
              v343 = v832[21];
            else
              v343 = v832[16];
            v820 = v343;
            if (v819 >= (double)v343) {
              if (v832[16] >= (double)v832[21])
                v344 = v832[21];
              else
                v344 = v832[16];
              v668 = v344;
            } else {
              if (v831[21] >= (double)v831[16])
                v344 = v831[16];
              else
                v344 = v831[21];
              v667 = v344;
            }
            v821 = v344;
            v844 = (unsigned __int8)Subdivide_variable_8[11 * v246];
            if ((double)(__int16)v844 * subscale > v344) {
              subdivide(
                v831[19],
                v831[20],
                v831[21],
                v831[14],
                v831[15],
                v831[16],
                v832[14],
                v832[15],
                v832[16],
                v832[19],
                v832[20],
                v832[21],
                -1,
                gfx_size);
              goto LABEL_1265;
            }
            if ((G3Poly & 0x100) == 0) {
              v261 = &G3Poly;
              POLYFLAT(v827, &G3Poly);
              goto LABEL_1197;
            }
            goto LABEL_1090;
          }
          if ((textures_off & 1) != 0 && (G3Poly & 0x100) != 0) {
            v247 = G3Poly & 0xFFFFFE00;
            G3Poly = (G3Poly & 0xFFFFFE00) + remap_tex[(unsigned __int8)G3Poly];
          }
          set_starts(0, v247);
          if (v831[21] >= (double)v831[16])
            v345 = v831[16];
          else
            v345 = v831[21];
          v669 = v345;
          if (v832[16] >= (double)v832[21])
            v346 = v832[21];
          else
            v346 = v832[16];
          v822 = v346;
          if (v669 >= (double)v346) {
            if (v832[16] >= (double)v832[21])
              v347 = v832[21];
            else
              v347 = v832[16];
            v825 = v347;
          } else {
            if (v831[21] >= (double)v831[16])
              v347 = v831[16];
            else
              v347 = v831[21];
            v824 = v347;
          }
          v823 = v347;
          v844 = (unsigned __int8)Subdivide_variable_8[11 * v246];
          if ((double)(__int16)v844 * subscale > v347) {
            subdivide(
              v831[19],
              v831[20],
              v831[21],
              v831[14],
              v831[15],
              v831[16],
              v832[14],
              v832[15],
              v832[16],
              v832[19],
              v832[20],
              v832[21],
              0,
              gfx_size);
            goto LABEL_1265;
          }
          if ((G3Poly & 0x100) == 0) {
            v256 = &G3Poly;
            POLYFLAT(v827, &G3Poly);
            goto LABEL_1221;
          }
          goto LABEL_1113;
        case 3:
          if (!facing_ok(
            v831[4],
            v831[5],
            v831[6],
            v832[4],
            v832[5],
            v832[6],
            v832[9],
            v832[10],
            v832[11],
            v831[9],
            v831[10],
            v831[11])
            && (GroundColour_variable_1[20 * v246] & 0x40) == 0) {
            goto LABEL_1063;
          }
          v348 = 20 * v246;
          G1Poly_variable_3 = 4;
          G1Poly = *((_DWORD *)&GroundColour + 5 * v246);
          G1Poly_variable_4 = *((_DWORD *)v831 + 2);
          G1Poly_variable_5 = *((_DWORD *)v831 + 3);
          G1Poly_variable_6 = *((_DWORD *)v832 + 2);
          G1Poly_variable_7 = *((_DWORD *)v832 + 3);
          G1Poly_variable_8 = *((_DWORD *)v832 + 7);
          G1Poly_variable_9 = *((_DWORD *)v832 + 8);
          G1Poly_variable_10 = *((_DWORD *)v831 + 7);
          G1Poly_variable_11 = *((_DWORD *)v831 + 8);
          if (G1Poly == -1 || GroundColour_variable_4[5 * v246] == -1)
            goto LABEL_1063;
          if ((G1Poly & 0x10000) == 0 || (G1Poly & 7) == 7) {
            if ((textures_off & 1) != 0 && (G1Poly & 0x100) != 0) {
              v348 = remap_tex[(unsigned __int8)G1Poly];
              G1Poly = v348 + (G1Poly & 0xFFFFFE00);
            }
            set_starts(0, v348);
            if (v831[6] >= (double)v832[6])
              v355 = v832;
            else
              v355 = v831;
            v687 = v355[6];
            if (v832[11] >= (double)v831[11])
              v356 = v831;
            else
              v356 = v832;
            v688 = v356[11];
            if (v687 >= (double)v688) {
              if (v832[11] >= (double)v831[11])
                v359 = v831;
              else
                v359 = v832;
              v691 = v359[11];
              v358 = v691;
            } else {
              if (v831[6] >= (double)v832[6])
                v357 = v832;
              else
                v357 = v831;
              v690 = v357[6];
              v358 = v690;
            }
            v689 = v358;
            v844 = (unsigned __int8)Subdivide_variable_6[11 * v246];
            if ((double)(__int16)v844 * subscale > v358) {
              subdivide(
                v831[4],
                v831[5],
                v831[6],
                v832[4],
                v832[5],
                v832[6],
                v832[9],
                v832[10],
                v832[11],
                v831[9],
                v831[10],
                v831[11],
                0,
                gfx_size);
              goto LABEL_1063;
            }
            if ((G1Poly & 0x100) != 0) {
              v354 = v827;
              POLYTEX(gfx_size);
            } else {
              v354 = &G1Poly;
              POLYFLAT(v827, &G1Poly);
            }
          } else {
            set_starts(1, v348);
            if ((textures_off & 1) != 0 && (G1Poly & 0x100) != 0)
              G1Poly = (G1Poly & 0xFFFFFE00) + remap_tex[(unsigned __int8)G1Poly];
            if (v831[6] >= (double)v832[6])
              v349 = v832;
            else
              v349 = v831;
            v677 = v349[6];
            if (v832[11] >= (double)v831[11])
              v350 = v831;
            else
              v350 = v832;
            v678 = v350[11];
            if (v677 >= (double)v678) {
              if (v832[11] >= (double)v831[11])
                v353 = v831;
              else
                v353 = v832;
              v826 = v353[11];
              v352 = v826;
            } else {
              if (v831[6] >= (double)v832[6])
                v351 = v832;
              else
                v351 = v831;
              v680 = v351[6];
              v352 = v680;
            }
            v679 = v352;
            v844 = (unsigned __int8)Subdivide_variable_6[11 * v246];
            if ((double)(__int16)v844 * subscale > v352) {
              subdivide(
                v831[4],
                v831[5],
                v831[6],
                v832[4],
                v832[5],
                v832[6],
                v832[9],
                v832[10],
                v832[11],
                v831[9],
                v831[10],
                v831[11],
                -1,
                gfx_size);
              goto LABEL_1063;
            }
            if ((G1Poly & 0x100) != 0) {
              v354 = v827;
              POLYTEX(gfx_size);
            } else {
              v354 = &G1Poly;
              POLYFLAT(v827, &G1Poly);
            }
            set_starts(0, v354);
          }
          set_starts(0, v354);
        LABEL_1063:
          if (!facing_ok(
            v831[9],
            v831[10],
            v831[11],
            v832[9],
            v832[10],
            v832[11],
            v832[14],
            v832[15],
            v832[16],
            v831[14],
            v831[15],
            v831[16])
            && (GroundColour_variable_2[5 * v246] & 0x4000) == 0) {
            goto LABEL_1265;
          }
          G2Poly = GroundColour_variable_2[5 * v246];
          G2Poly_variable_4 = *((_DWORD *)v831 + 7);
          G2Poly_variable_5 = *((_DWORD *)v831 + 8);
          G2Poly_variable_6 = *((_DWORD *)v832 + 7);
          G2Poly_variable_7 = *((_DWORD *)v832 + 8);
          G2Poly_variable_8 = *((_DWORD *)v832 + 12);
          G2Poly_variable_9 = *((_DWORD *)v832 + 13);
          G2Poly_variable_10 = *((_DWORD *)v831 + 12);
          G2Poly_variable_3 = 4;
          G2Poly_variable_11 = *((_DWORD *)v831 + 13);
          if (G2Poly == -1 || GroundColour_variable_4[5 * v246] == -1)
            goto LABEL_1265;
          if ((G2Poly & 0x10000) != 0 && (G2Poly & 7) != 7) {
            set_starts(1, 20 * v246);
            if ((textures_off & 1) != 0 && (G2Poly & 0x100) != 0)
              G2Poly = remap_tex[(unsigned __int8)G2Poly] + (G2Poly & 0xFFFFFE00);
            if (v831[11] >= (double)v832[11])
              v360 = v832;
            else
              v360 = v831;
            v692 = v360[11];
            if (v832[16] >= (double)v831[16])
              v361 = v831;
            else
              v361 = v832;
            v693 = v361[16];
            if (v692 >= (double)v693) {
              if (v832[16] >= (double)v831[16])
                v364 = v831;
              else
                v364 = v832;
              v696 = v364[16];
              v363 = v696;
            } else {
              if (v831[11] >= (double)v832[11])
                v362 = v832;
              else
                v362 = v831;
              v695 = v362[11];
              v363 = v695;
            }
            v694 = v363;
            v844 = (unsigned __int8)Subdivide_variable_7[11 * v246];
            if ((double)(__int16)v844 * subscale > v363) {
              subdivide(
                v831[9],
                v831[10],
                v831[11],
                v832[9],
                v832[10],
                v832[11],
                v832[14],
                v832[15],
                v832[16],
                v831[14],
                v831[15],
                v831[16],
                -1,
                gfx_size);
              goto LABEL_1265;
            }
            if ((G2Poly & 0x100) == 0) {
              v261 = &G2Poly;
              POLYFLAT(v827, &G2Poly);
              goto LABEL_1197;
            }
            goto LABEL_1090;
          }
          v365 = textures_off;
          if ((textures_off & 1) != 0 && (G2Poly & 0x100) != 0) {
            v365 = remap_tex[(unsigned __int8)G2Poly];
            G2Poly = v365 + (G2Poly & 0xFFFFFE00);
          }
          set_starts(0, v365);
          if (v831[11] >= (double)v832[11])
            v366 = v832;
          else
            v366 = v831;
          v697 = v366[11];
          if (v832[16] >= (double)v831[16])
            v367 = v831;
          else
            v367 = v832;
          v698 = v367[16];
          if (v697 >= (double)v698) {
            if (v832[16] >= (double)v831[16])
              v370 = v831;
            else
              v370 = v832;
            v701 = v370[16];
            v369 = v701;
          } else {
            if (v831[11] >= (double)v832[11])
              v368 = v832;
            else
              v368 = v831;
            v700 = v368[11];
            v369 = v700;
          }
          v699 = v369;
          v844 = (unsigned __int8)Subdivide_variable_7[11 * v246];
          if ((double)(__int16)v844 * subscale > v369) {
            subdivide(
              v831[9],
              v831[10],
              v831[11],
              v832[9],
              v832[10],
              v832[11],
              v832[14],
              v832[15],
              v832[16],
              v831[14],
              v831[15],
              v831[16],
              0,
              gfx_size);
            goto LABEL_1265;
          }
          if ((G2Poly & 0x100) == 0) {
            v256 = &G2Poly;
            POLYFLAT(v827, &G2Poly);
            goto LABEL_1221;
          }
          goto LABEL_1113;
        case 4:
          if (!facing_ok(
            v831[24],
            v831[25],
            v831[26],
            v832[24],
            v832[25],
            v832[26],
            v832[29],
            v832[30],
            v832[31],
            v831[29],
            v831[30],
            v831[31])
            && (GroundColour_variable_8[20 * v246] & 0x40) == 0) {
            goto LABEL_1169;
          }
          G5Poly = *((_DWORD *)&GroundColour_variable_7 + 5 * v246);
          G5Poly_variable_4 = *((_DWORD *)v831 + 22);
          G5Poly_variable_5 = *((_DWORD *)v831 + 23);
          G5Poly_variable_6 = *((_DWORD *)v832 + 22);
          G5Poly_variable_7 = *((_DWORD *)v832 + 23);
          G5Poly_variable_8 = *((_DWORD *)v832 + 27);
          G5Poly_variable_9 = *((_DWORD *)v832 + 28);
          G5Poly_variable_10 = *((_DWORD *)v831 + 27);
          G5Poly_variable_3 = 4;
          G5Poly_variable_11 = *((_DWORD *)v831 + 28);
          if (G5Poly == -1 || GroundColour_variable_4[5 * v246] == -1)
            goto LABEL_1169;
          if ((G5Poly & 0x10000) == 0 || (G5Poly & 7) == 7) {
            v377 = textures_off;
            if ((textures_off & 1) != 0 && (G5Poly & 0x100) != 0) {
              v377 = remap_tex[(unsigned __int8)G5Poly];
              G5Poly = v377 + (G5Poly & 0xFFFFFE00);
            }
            set_starts(0, v377);
            if (v831[26] >= (double)v832[26])
              v378 = v832;
            else
              v378 = v831;
            v707 = v378[26];
            if (v832[31] >= (double)v831[31])
              v379 = v831;
            else
              v379 = v832;
            v708 = v379[31];
            if (v707 >= (double)v708) {
              if (v832[31] >= (double)v831[31])
                v382 = v831;
              else
                v382 = v832;
              v711 = v382[31];
              v381 = v711;
            } else {
              if (v831[26] >= (double)v832[26])
                v380 = v832;
              else
                v380 = v831;
              v710 = v380[26];
              v381 = v710;
            }
            v709 = v381;
            v844 = (unsigned __int8)Subdivide_variable_10[11 * v246];
            if ((double)(__int16)v844 * subscale > v381) {
              subdivide(
                v831[24],
                v831[25],
                v831[26],
                v832[24],
                v832[25],
                v832[26],
                v832[29],
                v832[30],
                v832[31],
                v831[29],
                v831[30],
                v831[31],
                0,
                gfx_size);
              goto LABEL_1169;
            }
            if ((G5Poly & 0x100) != 0) {
              v376 = v827;
              POLYTEX(gfx_size);
            } else {
              v376 = &G5Poly;
              POLYFLAT(v827, &G5Poly);
            }
          } else {
            set_starts(1, 20 * v246);
            if ((textures_off & 1) != 0 && (G5Poly & 0x100) != 0)
              G5Poly = remap_tex[(unsigned __int8)G5Poly] + (G5Poly & 0xFFFFFE00);
            if (v831[26] >= (double)v832[26])
              v371 = v832;
            else
              v371 = v831;
            v702 = v371[26];
            if (v832[31] >= (double)v831[31])
              v372 = v831;
            else
              v372 = v832;
            v703 = v372[31];
            if (v702 >= (double)v703) {
              if (v832[31] >= (double)v831[31])
                v375 = v831;
              else
                v375 = v832;
              v706 = v375[31];
              v374 = v706;
            } else {
              if (v831[26] >= (double)v832[26])
                v373 = v832;
              else
                v373 = v831;
              v705 = v373[26];
              v374 = v705;
            }
            v704 = v374;
            v844 = (unsigned __int8)Subdivide_variable_10[11 * v246];
            if ((double)(__int16)v844 * subscale > v374) {
              subdivide(
                v831[24],
                v831[25],
                v831[26],
                v832[24],
                v832[25],
                v832[26],
                v832[29],
                v832[30],
                v832[31],
                v831[29],
                v831[30],
                v831[31],
                -1,
                gfx_size);
              goto LABEL_1169;
            }
            if ((G5Poly & 0x100) != 0) {
              v376 = v827;
              POLYTEX(gfx_size);
            } else {
              v376 = &G5Poly;
              POLYFLAT(v827, &G5Poly);
            }
            set_starts(0, v376);
          }
          set_starts(0, v376);
        LABEL_1169:
          if (!facing_ok(
            v831[19],
            v831[20],
            v831[21],
            v832[19],
            v832[20],
            v832[21],
            v832[24],
            v832[25],
            v832[26],
            v831[24],
            v831[25],
            v831[26])
            && (GroundColour_variable_5[5 * v246] & 0x4000) == 0) {
            goto LABEL_1265;
          }
          v383 = 20 * v246;
          G4Poly = GroundColour_variable_5[5 * v246];
          G4Poly_variable_4 = *((_DWORD *)v831 + 17);
          G4Poly_variable_5 = *((_DWORD *)v831 + 18);
          G4Poly_variable_6 = *((_DWORD *)v832 + 17);
          G4Poly_variable_7 = *((_DWORD *)v832 + 18);
          G4Poly_variable_8 = *((_DWORD *)v832 + 22);
          G4Poly_variable_9 = *((_DWORD *)v832 + 23);
          G4Poly_variable_10 = *((_DWORD *)v831 + 22);
          G4Poly_variable_11 = *((_DWORD *)v831 + 23);
          G4Poly_variable_3 = 4;
          if (G4Poly == -1 || GroundColour_variable_4[5 * v246] == -1)
            goto LABEL_1265;
          if ((G4Poly & 0x10000) != 0 && (G4Poly & 7) != 7) {
            set_starts(1, v383);
            if ((textures_off & 1) != 0 && (G4Poly & 0x100) != 0)
              G4Poly = (G4Poly & 0xFFFFFE00) + remap_tex[(unsigned __int8)G4Poly];
            if (v831[21] >= (double)v832[21])
              v384 = v832;
            else
              v384 = v831;
            v712 = v384[21];
            if (v832[26] >= (double)v831[26])
              v385 = v831;
            else
              v385 = v832;
            v713 = v385[26];
            if (v712 >= (double)v713) {
              if (v832[26] >= (double)v831[26])
                v388 = v831;
              else
                v388 = v832;
              v716 = v388[26];
              v387 = v716;
            } else {
              if (v831[21] >= (double)v832[21])
                v386 = v832;
              else
                v386 = v831;
              v715 = v386[21];
              v387 = v715;
            }
            v714 = v387;
            v844 = (unsigned __int8)Subdivide_variable_9[11 * v246];
            if ((double)(__int16)v844 * subscale > v387) {
              subdivide(
                v831[19],
                v831[20],
                v831[21],
                v832[19],
                v832[20],
                v832[21],
                v832[24],
                v832[25],
                v832[26],
                v831[24],
                v831[25],
                v831[26],
                -1,
                gfx_size);
              goto LABEL_1265;
            }
            if ((G4Poly & 0x100) == 0) {
              v261 = &G4Poly;
              POLYFLAT(v827, &G4Poly);
              goto LABEL_1197;
            }
            goto LABEL_1090;
          }
          if ((textures_off & 1) != 0 && (G4Poly & 0x100) != 0) {
            v383 = remap_tex[(unsigned __int8)G4Poly];
            G4Poly = v383 + (G4Poly & 0xFFFFFE00);
          }
          set_starts(0, v383);
          if (v831[21] >= (double)v832[21])
            v389 = v832;
          else
            v389 = v831;
          v717 = v389[21];
          if (v832[26] >= (double)v831[26])
            v390 = v831;
          else
            v390 = v832;
          v718 = v390[26];
          if (v717 >= (double)v718) {
            if (v832[26] >= (double)v831[26])
              v393 = v831;
            else
              v393 = v832;
            v721 = v393[26];
            v392 = v721;
          } else {
            if (v831[21] >= (double)v832[21])
              v391 = v832;
            else
              v391 = v831;
            v720 = v391[21];
            v392 = v720;
          }
          v719 = v392;
          v844 = (unsigned __int8)Subdivide_variable_9[11 * v246];
          if ((double)(__int16)v844 * subscale > v392) {
            subdivide(
              v831[19],
              v831[20],
              v831[21],
              v832[19],
              v832[20],
              v832[21],
              v832[24],
              v832[25],
              v832[26],
              v831[24],
              v831[25],
              v831[26],
              0,
              gfx_size);
            goto LABEL_1265;
          }
          if ((G4Poly & 0x100) == 0) {
            v256 = &G4Poly;
            POLYFLAT(v827, &G4Poly);
            goto LABEL_1221;
          }
          goto LABEL_1113;
        case 5:
          if (facing_ok(
            a4[14],
            a4[15],
            a4[16],
            a4[9],
            a4[10],
            a4[11],
            *((float *)a5 + 9),
            *((float *)a5 + 10),
            *((float *)a5 + 11),
            *((float *)a5 + 14),
            *((float *)a5 + 15),
            *((float *)a5 + 16))
            || (TrakColour_variable_4[24 * v246] & 0x40) != 0) {
            RoadPoly_variable_3 = 4;
            v248 = *((_DWORD *)&TrakColour_variable_3 + 6 * v246);
            RoadPoly = v248;
            v249 = textures_off;
            if ((textures_off & 2) != 0 && (RoadPoly & 0x100) != 0) {
              v249 = remap_tex[(unsigned __int8)v248] + (RoadPoly & 0xFFFFFE00);
              RoadPoly = v249;
            }
            RoadPoly_variable_4 = *((_DWORD *)a4 + 12);
            RoadPoly_variable_5 = *((_DWORD *)a4 + 13);
            RoadPoly_variable_6 = *((_DWORD *)a4 + 7);
            RoadPoly_variable_7 = *((_DWORD *)a4 + 8);
            RoadPoly_variable_8 = *((_DWORD *)a5 + 7);
            RoadPoly_variable_9 = *((_DWORD *)a5 + 8);
            RoadPoly_variable_10 = *((_DWORD *)a5 + 12);
            BYTE1(v249) = BYTE2(RoadPoly);
            RoadPoly_variable_11 = *((_DWORD *)a5 + 13);
            if ((RoadPoly & 0x10000) != 0 && wide_on && (RoadPoly & 7) != 7) {
              set_starts(1, v249);
              if (a4[16] >= (double)a4[11])
                v250 = a4[11];
              else
                v250 = a4[16];
              v749 = v250;
              if (*((float *)a5 + 11) >= (double)*((float *)a5 + 16))
                v251 = *((float *)a5 + 16);
              else
                v251 = *((float *)a5 + 11);
              v606 = v251;
              if (v749 >= (double)v251) {
                if (*((float *)a5 + 11) >= (double)*((float *)a5 + 16))
                  v252 = *((float *)a5 + 16);
                else
                  v252 = *((float *)a5 + 11);
                v751 = v252;
              } else {
                if (a4[16] >= (double)a4[11])
                  v252 = a4[11];
                else
                  v252 = a4[16];
                v607 = v252;
              }
              v750 = v252;
              v844 = (unsigned __int8)Subdivide_variable_1[11 * v246];
              if ((double)(__int16)v844 * subscale > v252)
                goto LABEL_434;
              if ((RoadPoly & 0x100) == 0)
                goto LABEL_480;
              goto LABEL_1090;
            }
            set_starts(0, v249);
            if (a4[16] >= (double)a4[11])
              v253 = a4[11];
            else
              v253 = a4[16];
            v752 = v253;
            if (*((float *)a5 + 11) >= (double)*((float *)a5 + 16))
              v254 = *((float *)a5 + 16);
            else
              v254 = *((float *)a5 + 11);
            v608 = v254;
            if (v752 >= (double)v254) {
              if (*((float *)a5 + 11) >= (double)*((float *)a5 + 16))
                v255 = *((float *)a5 + 16);
              else
                v255 = *((float *)a5 + 11);
              v610 = v255;
            } else {
              if (a4[16] >= (double)a4[11])
                v255 = a4[11];
              else
                v255 = a4[16];
              v609 = v255;
            }
            v753 = v255;
            v844 = (unsigned __int8)Subdivide_variable_1[11 * v246];
            if ((double)(__int16)v844 * subscale <= v255) {
              if ((RoadPoly & 0x100) != 0)
                goto LABEL_1113;
            LABEL_456:
              v256 = &RoadPoly;
              POLYFLAT(v827, &RoadPoly);
            LABEL_1221:
              set_starts(0, v256);
              goto LABEL_1265;
            }
          } else {
            v257 = *((_DWORD *)&TrakColour_variable_3 + 6 * v246);
            RoadPoly_variable_3 = 4;
            RoadPoly = v257;
            if ((textures_off & 2) != 0 && (RoadPoly & 0x100) != 0) {
              v247 = remap_tex[(unsigned __int8)v257] + (RoadPoly & 0xFFFFFE00);
              RoadPoly = v247;
            }
            RoadPoly_variable_4 = *((_DWORD *)a4 + 7);
            RoadPoly_variable_5 = *((_DWORD *)a4 + 8);
            RoadPoly_variable_6 = *((_DWORD *)a4 + 12);
            RoadPoly_variable_7 = *((_DWORD *)a4 + 13);
            RoadPoly_variable_8 = *((_DWORD *)a5 + 12);
            RoadPoly_variable_9 = *((_DWORD *)a5 + 13);
            RoadPoly_variable_10 = *((_DWORD *)a5 + 7);
            RoadPoly_variable_11 = *((_DWORD *)a5 + 8);
            if ((RoadPoly & 0x10000) != 0 && wide_on && (RoadPoly & 7) != 7) {
              set_starts(1, v247);
              if (a4[16] >= (double)a4[11])
                v258 = a4[11];
              else
                v258 = a4[16];
              v611 = v258;
              if (*((float *)a5 + 11) >= (double)*((float *)a5 + 16))
                v259 = *((float *)a5 + 16);
              else
                v259 = *((float *)a5 + 11);
              v754 = v259;
              if (v611 >= (double)v259) {
                if (*((float *)a5 + 11) >= (double)*((float *)a5 + 16))
                  v260 = *((float *)a5 + 16);
                else
                  v260 = *((float *)a5 + 11);
                v613 = v260;
              } else {
                if (a4[16] >= (double)a4[11])
                  v260 = a4[11];
                else
                  v260 = a4[16];
                v755 = v260;
              }
              v612 = v260;
              v844 = (unsigned __int8)Subdivide_variable_1[11 * v246];
              if ((double)(__int16)v844 * subscale > v260) {
              LABEL_434:
                subdivide(
                  a4[14],
                  a4[15],
                  a4[16],
                  a4[9],
                  a4[10],
                  a4[11],
                  *((float *)a5 + 9),
                  *((float *)a5 + 10),
                  *((float *)a5 + 11),
                  *((float *)a5 + 14),
                  *((float *)a5 + 15),
                  *((float *)a5 + 16),
                  -1,
                  gfx_size);
                goto LABEL_1265;
              }
              if ((RoadPoly & 0x100) == 0) {
              LABEL_480:
                v261 = &RoadPoly;
                POLYFLAT(v827, &RoadPoly);
              LABEL_1197:
                set_starts(0, v261);
                set_starts(0, v261);
                goto LABEL_1265;
              }
            LABEL_1090:
              v261 = v827;
              POLYTEX(gfx_size);
              goto LABEL_1197;
            }
            set_starts(0, v247);
            if (a4[16] >= (double)a4[11])
              v262 = a4[11];
            else
              v262 = a4[16];
            v756 = v262;
            if (*((float *)a5 + 11) >= (double)*((float *)a5 + 16))
              v263 = *((float *)a5 + 16);
            else
              v263 = *((float *)a5 + 11);
            v757 = v263;
            if (v756 >= (double)v263) {
              if (*((float *)a5 + 11) >= (double)*((float *)a5 + 16))
                v264 = *((float *)a5 + 16);
              else
                v264 = *((float *)a5 + 11);
              v758 = v264;
            } else {
              if (a4[16] >= (double)a4[11])
                v264 = a4[11];
              else
                v264 = a4[16];
              v615 = v264;
            }
            v614 = v264;
            v844 = (unsigned __int8)Subdivide_variable_1[11 * v246];
            if ((double)(__int16)v844 * subscale <= v264) {
              if ((RoadPoly & 0x100) != 0)
                goto LABEL_1113;
              goto LABEL_456;
            }
          }
          subdivide(
            a4[14],
            a4[15],
            a4[16],
            a4[9],
            a4[10],
            a4[11],
            *((float *)a5 + 9),
            *((float *)a5 + 10),
            *((float *)a5 + 11),
            *((float *)a5 + 14),
            *((float *)a5 + 15),
            *((float *)a5 + 16),
            0,
            gfx_size);
        LABEL_1265:
          result = v748 + 1;
          v748 = result;
          if (result >= num_bits)
            return result;
          continue;
        case 6:
          v265 = *((_DWORD *)&TrakColour + 6 * v246);
          if (v265 < 0)
            v265 = -v265;
          LeftPoly = v265;
          LeftPoly_variable_3 = 4;
          v266 = textures_off;
          if ((textures_off & 2) != 0 && (v265 & 0x100) != 0) {
            v267 = (unsigned __int8)v265;
            LOWORD(v265) = v265 & 0xFE00;
            v266 = remap_tex[v267];
            LeftPoly = v266 + v265;
          }
          LeftPoly_variable_4 = *((_DWORD *)a4 + 7);
          LeftPoly_variable_5 = *((_DWORD *)a4 + 8);
          LeftPoly_variable_6 = *((_DWORD *)a4 + 2);
          LeftPoly_variable_7 = *((_DWORD *)a4 + 3);
          LeftPoly_variable_8 = *((_DWORD *)a5 + 2);
          LeftPoly_variable_9 = *((_DWORD *)a5 + 3);
          LeftPoly_variable_10 = *((_DWORD *)a5 + 7);
          LOBYTE(v266) = BYTE2(LeftPoly);
          LeftPoly_variable_11 = *((_DWORD *)a5 + 8);
          if ((LeftPoly & 0x10000) != 0 && wide_on && (LeftPoly & 7) != 7) {
            set_starts(1, v266);
            if (a4[11] >= (double)a4[6])
              v268 = a4[6];
            else
              v268 = a4[11];
            v616 = v268;
            if (*((float *)a5 + 6) >= (double)*((float *)a5 + 11))
              v269 = *((float *)a5 + 11);
            else
              v269 = *((float *)a5 + 6);
            v617 = v269;
            if (v616 >= (double)v269) {
              if (*((float *)a5 + 6) >= (double)*((float *)a5 + 11))
                v270 = *((float *)a5 + 11);
              else
                v270 = *((float *)a5 + 6);
              v760 = v270;
            } else {
              if (a4[11] >= (double)a4[6])
                v270 = a4[6];
              else
                v270 = a4[11];
              v759 = v270;
            }
            v618 = v270;
            v844 = (unsigned __int8)Subdivide[11 * v246];
            if ((double)(__int16)v844 * subscale > v270) {
              subdivide(
                a4[9],
                a4[10],
                a4[11],
                a4[4],
                a4[5],
                a4[6],
                *((float *)a5 + 4),
                *((float *)a5 + 5),
                *((float *)a5 + 6),
                *((float *)a5 + 9),
                *((float *)a5 + 10),
                *((float *)a5 + 11),
                -1,
                gfx_size);
              goto LABEL_1265;
            }
            if ((LeftPoly & 0x100) == 0) {
              v261 = &LeftPoly;
              POLYFLAT(v827, &LeftPoly);
              goto LABEL_1197;
            }
            goto LABEL_1090;
          }
          set_starts(0, v266);
          if (a4[11] >= (double)a4[6])
            v271 = a4[6];
          else
            v271 = a4[11];
          v761 = v271;
          if (*((float *)a5 + 6) >= (double)*((float *)a5 + 11))
            v272 = *((float *)a5 + 11);
          else
            v272 = *((float *)a5 + 6);
          v762 = v272;
          if (v761 >= (double)v272) {
            if (*((float *)a5 + 6) >= (double)*((float *)a5 + 11))
              v273 = *((float *)a5 + 11);
            else
              v273 = *((float *)a5 + 6);
            v764 = v273;
          } else {
            if (a4[11] >= (double)a4[6])
              v273 = a4[6];
            else
              v273 = a4[11];
            v624 = v273;
          }
          v763 = v273;
          v844 = (unsigned __int8)Subdivide[11 * v246];
          if ((double)(__int16)v844 * subscale > v273) {
            subdivide(
              a4[9],
              a4[10],
              a4[11],
              a4[4],
              a4[5],
              a4[6],
              *((float *)a5 + 4),
              *((float *)a5 + 5),
              *((float *)a5 + 6),
              *((float *)a5 + 9),
              *((float *)a5 + 10),
              *((float *)a5 + 11),
              0,
              gfx_size);
            goto LABEL_1265;
          }
          if ((LeftPoly & 0x100) == 0) {
            v256 = &LeftPoly;
            POLYFLAT(v827, &LeftPoly);
            goto LABEL_1221;
          }
          goto LABEL_1113;
        case 7:
          v274 = *((_DWORD *)&TrakColour_variable_7 + 6 * v246);
          if (v274 < 0)
            v274 = -v274;
          v275 = 4;
          RightPoly = v274;
          RightPoly_variable_3 = 4;
          if ((textures_off & 2) != 0 && (v274 & 0x100) != 0) {
            v276 = (unsigned __int8)v274;
            LOWORD(v274) = v274 & 0xFE00;
            v275 = remap_tex[v276];
            RightPoly = v275 + v274;
          }
          RightPoly_variable_4 = *((_DWORD *)a4 + 17);
          RightPoly_variable_5 = *((_DWORD *)a4 + 18);
          RightPoly_variable_6 = *((_DWORD *)a4 + 12);
          RightPoly_variable_7 = *((_DWORD *)a4 + 13);
          RightPoly_variable_8 = *((_DWORD *)a5 + 12);
          RightPoly_variable_9 = *((_DWORD *)a5 + 13);
          RightPoly_variable_10 = *((_DWORD *)a5 + 17);
          RightPoly_variable_11 = *((_DWORD *)a5 + 18);
          if ((RightPoly & 0x10000) != 0 && wide_on && (RightPoly & 7) != 7) {
            set_starts(1, v275);
            if (a4[21] >= (double)a4[16])
              v277 = a4[16];
            else
              v277 = a4[21];
            v765 = v277;
            if (*((float *)a5 + 16) >= (double)*((float *)a5 + 21))
              v278 = *((float *)a5 + 21);
            else
              v278 = *((float *)a5 + 16);
            v766 = v278;
            if (v765 >= (double)v278) {
              if (*((float *)a5 + 16) >= (double)*((float *)a5 + 21))
                v279 = *((float *)a5 + 21);
              else
                v279 = *((float *)a5 + 16);
              v769 = v279;
            } else {
              if (a4[21] >= (double)a4[16])
                v279 = a4[16];
              else
                v279 = a4[21];
              v768 = v279;
            }
            v767 = v279;
            v844 = (unsigned __int8)Subdivide_variable_2[11 * v246];
            if ((double)(__int16)v844 * subscale > v279) {
              subdivide(
                a4[19],
                a4[20],
                a4[21],
                a4[14],
                a4[15],
                a4[16],
                *((float *)a5 + 14),
                *((float *)a5 + 15),
                *((float *)a5 + 16),
                *((float *)a5 + 19),
                *((float *)a5 + 20),
                *((float *)a5 + 21),
                -1,
                gfx_size);
              goto LABEL_1265;
            }
            if ((RightPoly & 0x100) == 0) {
              v261 = &RightPoly;
              POLYFLAT(v827, &RightPoly);
              goto LABEL_1197;
            }
            goto LABEL_1090;
          }
          set_starts(0, v275);
          if (a4[21] >= (double)a4[16])
            v280 = a4[16];
          else
            v280 = a4[21];
          v770 = v280;
          if (*((float *)a5 + 16) >= (double)*((float *)a5 + 21))
            v281 = *((float *)a5 + 21);
          else
            v281 = *((float *)a5 + 16);
          v771 = v281;
          if (v770 >= (double)v281) {
            if (*((float *)a5 + 16) >= (double)*((float *)a5 + 21))
              v282 = *((float *)a5 + 21);
            else
              v282 = *((float *)a5 + 16);
            v774 = v282;
          } else {
            if (a4[21] >= (double)a4[16])
              v282 = a4[16];
            else
              v282 = a4[21];
            v773 = v282;
          }
          v772 = v282;
          v844 = (unsigned __int8)Subdivide_variable_2[11 * v246];
          if ((double)(__int16)v844 * subscale > v282) {
            subdivide(
              a4[19],
              a4[20],
              a4[21],
              a4[14],
              a4[15],
              a4[16],
              *((float *)a5 + 14),
              *((float *)a5 + 15),
              *((float *)a5 + 16),
              *((float *)a5 + 19),
              *((float *)a5 + 20),
              *((float *)a5 + 21),
              0,
              gfx_size);
            goto LABEL_1265;
          }
          if ((RightPoly & 0x100) == 0) {
            v256 = &RightPoly;
            POLYFLAT(v827, &RightPoly);
            goto LABEL_1221;
          }
          goto LABEL_1113;
        case 0xA:
          RoofPoly_variable_3 = 4;
          v315 = TrakColour_variable_12[6 * v246];
          RoofPoly = v315;
          if (v315 >= 0) {
            if (!TrakColour_variable_11[6 * v246] || !TrakColour_variable_10[6 * v246])
              goto LABEL_1265;
            v323 = TrakColour_variable_12[6 * v632];
            if (v323 >= -1) {
              if ((textures_off & 4) != 0 && (RoofPoly & 0x100) != 0)
                RoofPoly = remap_tex[(unsigned __int8)RoofPoly] + (RoofPoly & 0xFFFFFE00);
              if ((RoofPoly & 0x10000) == 0) {
                RoofPoly_variable_4 = *((_DWORD *)a5 + 22);
                RoofPoly_variable_5 = *((_DWORD *)a5 + 23);
                RoofPoly_variable_6 = *((_DWORD *)a4 + 22);
                RoofPoly_variable_7 = *((_DWORD *)a4 + 23);
                RoofPoly_variable_8 = *((_DWORD *)a4 + 27);
                RoofPoly_variable_9 = *((_DWORD *)a4 + 28);
                RoofPoly_variable_10 = *((_DWORD *)a5 + 27);
                RoofPoly_variable_11 = *((_DWORD *)a5 + 28);
                set_starts(0, RoofPoly_variable_11);
                if (*((float *)a5 + 26) >= (double)a4[26])
                  v339 = a4[26];
                else
                  v339 = *((float *)a5 + 26);
                v817 = v339;
                if (a4[31] >= (double)*((float *)a5 + 31))
                  v340 = *((float *)a5 + 31);
                else
                  v340 = a4[31];
                v818 = v340;
                if (v817 >= (double)v340) {
                  if (a4[31] >= (double)*((float *)a5 + 31))
                    v341 = *((float *)a5 + 31);
                  else
                    v341 = a4[31];
                  v666 = v341;
                } else {
                  if (*((float *)a5 + 26) >= (double)a4[26])
                    v341 = a4[26];
                  else
                    v341 = *((float *)a5 + 26);
                  v665 = v341;
                }
                v664 = v341;
                v844 = (unsigned __int8)Subdivide_variable_5[11 * v246];
                if ((double)(__int16)v844 * subscale > v341) {
                  subdivide(
                    *((float *)a5 + 24),
                    *((float *)a5 + 25),
                    *((float *)a5 + 26),
                    a4[24],
                    a4[25],
                    a4[26],
                    a4[29],
                    a4[30],
                    a4[31],
                    *((float *)a5 + 29),
                    *((float *)a5 + 30),
                    *((float *)a5 + 31),
                    0,
                    gfx_size);
                  goto LABEL_1265;
                }
                if ((RoofPoly & 0x100) == 0) {
                LABEL_960:
                  v256 = &RoofPoly;
                  POLYFLAT(v827, &RoofPoly);
                  goto LABEL_1221;
                }
                goto LABEL_1113;
              }
              RoofPoly_variable_4 = *((_DWORD *)a4 + 22);
              RoofPoly_variable_5 = *((_DWORD *)a4 + 23);
              RoofPoly_variable_6 = *((_DWORD *)a4 + 27);
              RoofPoly_variable_7 = *((_DWORD *)a4 + 28);
              RoofPoly_variable_8 = *((_DWORD *)a5 + 27);
              RoofPoly_variable_9 = *((_DWORD *)a5 + 28);
              RoofPoly_variable_10 = *((_DWORD *)a5 + 22);
              v332 = *((_DWORD *)a5 + 23);
              RoofPoly_variable_11 = v332;
              if (!wide_on || (RoofPoly & 7) == 7) {
                set_starts(0, v332);
                if (a4[26] >= (double)a4[31])
                  v336 = a4[31];
                else
                  v336 = a4[26];
                v814 = v336;
                if (*((float *)a5 + 31) >= (double)*((float *)a5 + 26))
                  v337 = *((float *)a5 + 26);
                else
                  v337 = *((float *)a5 + 31);
                v815 = v337;
                if (v814 >= (double)v337) {
                  if (*((float *)a5 + 31) >= (double)*((float *)a5 + 26))
                    v338 = *((float *)a5 + 26);
                  else
                    v338 = *((float *)a5 + 31);
                  v663 = v338;
                } else {
                  if (a4[26] >= (double)a4[31])
                    v338 = a4[31];
                  else
                    v338 = a4[26];
                  v662 = v338;
                }
                v816 = v338;
                v844 = (unsigned __int8)Subdivide_variable_5[11 * v246];
                if ((double)(__int16)v844 * subscale > v338) {
                  subdivide(
                    a4[24],
                    a4[25],
                    a4[26],
                    a4[29],
                    a4[30],
                    a4[31],
                    *((float *)a5 + 29),
                    *((float *)a5 + 30),
                    *((float *)a5 + 31),
                    *((float *)a5 + 24),
                    *((float *)a5 + 25),
                    *((float *)a5 + 26),
                    0,
                    gfx_size);
                  goto LABEL_1265;
                }
                if ((RoofPoly & 0x100) == 0)
                  goto LABEL_960;
                goto LABEL_1113;
              }
              set_starts(1, v332);
              if (a4[26] >= (double)a4[31])
                v333 = a4[31];
              else
                v333 = a4[26];
              v660 = v333;
              if (*((float *)a5 + 31) >= (double)*((float *)a5 + 26))
                v334 = *((float *)a5 + 26);
              else
                v334 = *((float *)a5 + 31);
              v661 = v334;
              if (v660 >= (double)v334) {
                if (*((float *)a5 + 31) >= (double)*((float *)a5 + 26))
                  v335 = *((float *)a5 + 26);
                else
                  v335 = *((float *)a5 + 31);
                v813 = v335;
              } else {
                if (a4[26] >= (double)a4[31])
                  v335 = a4[31];
                else
                  v335 = a4[26];
                v812 = v335;
              }
              v811 = v335;
              v844 = (unsigned __int8)Subdivide_variable_5[11 * v246];
              if ((double)(__int16)v844 * subscale > v335) {
                subdivide(
                  a4[24],
                  a4[25],
                  a4[26],
                  a4[29],
                  a4[30],
                  a4[31],
                  *((float *)a5 + 29),
                  *((float *)a5 + 30),
                  *((float *)a5 + 31),
                  *((float *)a5 + 24),
                  *((float *)a5 + 25),
                  *((float *)a5 + 26),
                  -1,
                  gfx_size);
                goto LABEL_1265;
              }
              if ((RoofPoly & 0x100) == 0)
                goto LABEL_823;
            } else {
              RoofPoly = -v323;
              RoofPoly_variable_4 = GroundScreenXYZ_variable_5[32 * v246];
              RoofPoly_variable_5 = GroundScreenXYZ_variable_6[32 * v246];
              RoofPoly_variable_6 = GroundScreenXYZ_variable_3[32 * v246];
              RoofPoly_variable_7 = GroundScreenXYZ_variable_4[32 * v246];
              RoofPoly_variable_8 = GroundScreenXYZ_variable_1[32 * v246];
              RoofPoly_variable_9 = GroundScreenXYZ_variable_2[32 * v246];
              v324 = GroundScreenXYZ_variable_7[32 * v246];
              v325 = GroundScreenXYZ_variable_8[32 * v246];
              RoofPoly_variable_10 = v324;
              RoofPoly_variable_11 = v325;
              if ((-v323 & 0x10000) == 0 || (RoofPoly & 7) == 7) {
                if ((textures_off & 1) != 0 && (RoofPoly & 0x100) != 0) {
                  v324 = remap_tex[(unsigned __int8)RoofPoly];
                  RoofPoly = v324 + (RoofPoly & 0xFFFFFE00);
                }
                set_starts(0, v324);
                if (v832[26] >= (double)v832[11])
                  v329 = v832[11];
                else
                  v329 = v832[26];
                v807 = v329;
                if (v832[6] >= (double)v832[31])
                  v330 = v832[31];
                else
                  v330 = v832[6];
                v808 = v330;
                if (v807 >= (double)v330) {
                  if (v832[6] >= (double)v832[31])
                    v331 = v832[31];
                  else
                    v331 = v832[6];
                  v659 = v331;
                } else {
                  if (v832[26] >= (double)v832[11])
                    v331 = v832[11];
                  else
                    v331 = v832[26];
                  v810 = v331;
                }
                v809 = v331;
                v844 = (unsigned __int8)Subdivide_variable_5[11 * v246];
                if ((double)(__int16)v844 * subscale > v331) {
                  subdivide(
                    v832[24],
                    v832[25],
                    v832[26],
                    v832[9],
                    v832[10],
                    v832[11],
                    v832[4],
                    v832[5],
                    v832[6],
                    v832[29],
                    v832[30],
                    v832[31],
                    0,
                    gfx_size);
                  goto LABEL_1265;
                }
                if ((RoofPoly & 0x100) == 0)
                  goto LABEL_960;
                goto LABEL_1113;
              }
              set_starts(1, v324);
              if ((textures_off & 1) != 0 && (RoofPoly & 0x100) != 0)
                RoofPoly = remap_tex[(unsigned __int8)RoofPoly] + (RoofPoly & 0xFFFFFE00);
              if (v832[26] >= (double)v832[11])
                v326 = v832[11];
              else
                v326 = v832[26];
              v654 = v326;
              if (v832[6] >= (double)v832[31])
                v327 = v832[31];
              else
                v327 = v832[6];
              v655 = v327;
              if (v654 >= (double)v327) {
                if (v832[6] >= (double)v832[31])
                  v328 = v832[31];
                else
                  v328 = v832[6];
                v658 = v328;
              } else {
                if (v832[26] >= (double)v832[11])
                  v328 = v832[11];
                else
                  v328 = v832[26];
                v657 = v328;
              }
              v656 = v328;
              v844 = (unsigned __int8)Subdivide_variable_5[11 * v246];
              if ((double)(__int16)v844 * subscale > v328) {
                subdivide(
                  v832[24],
                  v832[25],
                  v832[26],
                  v832[9],
                  v832[10],
                  v832[11],
                  v832[4],
                  v832[5],
                  v832[6],
                  v832[29],
                  v832[30],
                  v832[31],
                  -1,
                  gfx_size);
                goto LABEL_1265;
              }
              if ((RoofPoly & 0x100) == 0)
                goto LABEL_823;
            }
          } else {
            RoofPoly_variable_8 = GroundScreenXYZ_variable_7[32 * v632];
            RoofPoly_variable_9 = GroundScreenXYZ_variable_8[32 * v632];
            RoofPoly_variable_10 = GroundScreenXYZ_variable_1[32 * v632];
            RoofPoly_variable_11 = GroundScreenXYZ_variable_2[32 * v632];
            RoofPoly_variable_4 = GroundScreenXYZ_variable_3[32 * v632];
            RoofPoly_variable_5 = GroundScreenXYZ_variable_4[32 * v632];
            v316 = GroundScreenXYZ_variable_5[32 * v632];
            RoofPoly = -v315;
            RoofPoly_variable_6 = v316;
            LOBYTE(v316) = (unsigned int)-v315 >> 16;
            RoofPoly_variable_7 = GroundScreenXYZ_variable_6[32 * v632];
            if ((v316 & 1) == 0 || (-(char)v315 & 7) == 7) {
              if ((textures_off & 1) != 0 && (RoofPoly & 0x100) != 0) {
                v316 = RoofPoly & 0xFFFFFE00;
                RoofPoly = (RoofPoly & 0xFFFFFE00) + remap_tex[(unsigned __int8)RoofPoly];
              }
              set_starts(0, v316);
              if (v831[11] >= (double)v831[26])
                v320 = v831[26];
              else
                v320 = v831[11];
              v653 = v320;
              if (v831[31] >= (double)v831[6])
                v321 = v831[6];
              else
                v321 = v831[31];
              v803 = v321;
              if (v653 >= (double)v321) {
                if (v831[31] >= (double)v831[6])
                  v322 = v831[6];
                else
                  v322 = v831[31];
                v806 = v322;
              } else {
                if (v831[11] >= (double)v831[26])
                  v322 = v831[26];
                else
                  v322 = v831[11];
                v805 = v322;
              }
              v804 = v322;
              v844 = (unsigned __int8)Subdivide_variable_5[11 * v246];
              if ((double)(__int16)v844 * subscale > v322) {
                subdivide(
                  v831[9],
                  v831[10],
                  v831[11],
                  v831[24],
                  v831[25],
                  v831[26],
                  v831[29],
                  v831[30],
                  v831[31],
                  v831[4],
                  v831[5],
                  v831[6],
                  0,
                  gfx_size);
                goto LABEL_1265;
              }
              if ((RoofPoly & 0x100) == 0)
                goto LABEL_960;
              goto LABEL_1113;
            }
            set_starts(1, v316);
            if ((textures_off & 1) != 0 && (RoofPoly & 0x100) != 0)
              RoofPoly = remap_tex[(unsigned __int8)RoofPoly] + (RoofPoly & 0xFFFFFE00);
            if (v831[11] >= (double)v831[26])
              v317 = v831[26];
            else
              v317 = v831[11];
            v798 = v317;
            if (v831[31] >= (double)v831[6])
              v318 = v831[6];
            else
              v318 = v831[31];
            v799 = v318;
            if (v798 >= (double)v318) {
              if (v831[31] >= (double)v831[6])
                v319 = v831[6];
              else
                v319 = v831[31];
              v802 = v319;
            } else {
              if (v831[11] >= (double)v831[26])
                v319 = v831[26];
              else
                v319 = v831[11];
              v801 = v319;
            }
            v800 = v319;
            v844 = (unsigned __int8)Subdivide_variable_5[11 * v246];
            if ((double)(__int16)v844 * subscale > v319) {
              subdivide(
                v831[9],
                v831[10],
                v831[11],
                v831[24],
                v831[25],
                v831[26],
                v831[29],
                v831[30],
                v831[31],
                v831[4],
                v831[5],
                v831[6],
                -1,
                gfx_size);
              goto LABEL_1265;
            }
            if ((RoofPoly & 0x100) == 0) {
            LABEL_823:
              v261 = &RoofPoly;
              POLYFLAT(v827, &RoofPoly);
              goto LABEL_1197;
            }
          }
          goto LABEL_1090;
        case 0xB:
          if (CarsLeft < 7 && CarsLeft > -3 || winner_mode || replaytype == 2)
            DisplayCar(v725);
          --CarsLeft;
          if (names_on && (names_on == 1 || human_control[v246]))
            --NamesLeft;
          goto LABEL_1265;
        case 0xC:
          DrawTower(v246, v827);
          goto LABEL_1265;
        case 0xD:
          DrawBuilding(v246, v827);
          goto LABEL_1265;
        case 0xE:
          v394 = v722 + 48 * v246;
          v629 = *(float *)((char *)SLight + v394);
          v628 = *(float *)((char *)SLight_variable_1 + v394);
          v395 = *(int *)((char *)SLight_variable_9 + v394);
          v627 = *(float *)((char *)SLight_variable_2 + v394);
          v396 = ((_WORD)v395 + (_WORD)worlddirn) & 0x3FFF;
          v839 = tcos[v396] * tcos[0];
          v838 = tsin[v396] * tcos[0];
          v397 = tcos[v396];
          v837 = tsin[0];
          v398 = v397 * tsin[0];
          v836 = v398 * tsin[0] - v838;
          v399 = tsin[v396] * tsin[0];
          v835 = v399 * tsin[0] + v839;
          v834 = -tsin[0] * tcos[0];
          v623 = -tcos[v396] * tsin[0] * tcos[0] - v399;
          v622 = v398 + -tsin[v396] * tsin[0] * tcos[0];
          v621 = tcos[0] * tcos[0];
          v626 = drawtrk3_c_variable_5 * v839 + drawtrk3_c_variable_6 * v836 - drawtrk3_c_variable_6 * v623 + v629;
          v840 = drawtrk3_c_variable_5 * tsin[0] + drawtrk3_c_variable_6 * v834 - drawtrk3_c_variable_6 * v621 + v627;
          v400 = v626 - viewx;
          v401 = drawtrk3_c_variable_5 * v838
            + drawtrk3_c_variable_6 * v835
            - drawtrk3_c_variable_6 * v622
            + v628
            - viewy;
          v402 = v840 - viewz;
          *(float *)&v744 = v400 * vk1 + v401 * vk4 + v402 * vk7;
          *(float *)&v740 = v400 * vk2 + v401 * vk5 + v402 * vk8;
          v403 = v400 * vk3 + v401 * vk6 + v402 * vk9;
          v736 = v403;
          _CHP(LODWORD(tsin[0]), v396 * 4);
          v732 = (int)v403;
          v405 = v736 < (double)drawtrk3_c_variable_4;
          v406 = 0;
          v407 = v736 == drawtrk3_c_variable_4;
          LOWORD(v408) = v404;
          if (v736 < (double)drawtrk3_c_variable_4)
            v736 = 80.0;
          v409 = (double)VIEWDIST;
          v410 = 1.0 / v736;
          v411 = v409 * *(float *)&v744 * v410 + (double)xbase;
          _CHP(v408, v396 * 4);
          xp = (int)v411;
          v412 = v410 * (v409 * *(float *)&v740) + (double)ybase;
          _CHP(v413, v396 * 4);
          yp = (int)v412;
          LightXYZ_variable_4[0] = (float)v732;
          v414 = drawtrk3_c_variable_5 * v839
            - drawtrk3_c_variable_6 * v836
            - drawtrk3_c_variable_6 * v623
            + v629
            - viewx;
          v415 = drawtrk3_c_variable_5 * v838
            - drawtrk3_c_variable_6 * v835
            - drawtrk3_c_variable_6 * v622
            + v628
            - viewy;
          v416 = drawtrk3_c_variable_5 * v837
            - drawtrk3_c_variable_6 * v834
            - drawtrk3_c_variable_6 * v621
            + v627
            - viewz;
          v417 = scr_size;
          LightXYZ[0] = (scr_size * xp) >> 6;
          LightXYZ_variable_1[0] = (scr_size * (199 - yp)) >> 6;
          v418 = v744;
          *(float *)&v744 = v414 * vk1 + v415 * vk4 + v416 * vk7;
          LightXYZ_variable_2 = v418;
          v419 = v740;
          *(float *)&v740 = v414 * vk2 + v415 * vk5 + v416 * vk8;
          v420 = v414 * vk3 + v415 * vk6 + v416 * vk9;
          v736 = v420;
          _CHP(v419, scr_size);
          v732 = (int)v420;
          LightXYZ_variable_3 = v425;
          v422 = v736 < (double)drawtrk3_c_variable_4;
          v423 = 0;
          v424 = v736 == drawtrk3_c_variable_4;
          LOWORD(v425) = v421;
          if (v736 < (double)drawtrk3_c_variable_4)
            v736 = 80.0;
          v426 = (double)VIEWDIST;
          v427 = 1.0 / v736;
          v428 = v426 * *(float *)&v744 * v427 + (double)xbase;
          _CHP(v425, v417);
          xp = (int)v428;
          v429 = v427 * (v426 * *(float *)&v740) + (double)ybase;
          _CHP(v430, v417);
          yp = (int)v429;
          LightXYZ_variable_9 = (float)v732;
          v431 = drawtrk3_c_variable_6 * v839
            - drawtrk3_c_variable_6 * v836
            - drawtrk3_c_variable_6 * v623
            + v629
            - viewx;
          v432 = drawtrk3_c_variable_6 * v838
            - drawtrk3_c_variable_6 * v835
            - drawtrk3_c_variable_6 * v622
            + v628
            - viewy;
          v433 = drawtrk3_c_variable_6 * v837
            - drawtrk3_c_variable_6 * v834
            - drawtrk3_c_variable_6 * v621
            + v627
            - viewz;
          v434 = scr_size;
          LightXYZ_variable_5 = (scr_size * xp) >> 6;
          LightXYZ_variable_6 = (scr_size * (199 - yp)) >> 6;
          v435 = v744;
          *(float *)&v744 = v431 * vk1 + v432 * vk4 + v433 * vk7;
          LightXYZ_variable_7 = v435;
          v436 = v740;
          *(float *)&v740 = v431 * vk2 + v432 * vk5 + v433 * vk8;
          v437 = v431 * vk3 + v432 * vk6 + v433 * vk9;
          v736 = v437;
          _CHP(v436, scr_size);
          v732 = (int)v437;
          LightXYZ_variable_8 = v442;
          v439 = v736 < (double)drawtrk3_c_variable_4;
          v440 = 0;
          v441 = v736 == drawtrk3_c_variable_4;
          LOWORD(v442) = v438;
          if (v736 < (double)drawtrk3_c_variable_4)
            v736 = 80.0;
          v443 = (double)VIEWDIST;
          v444 = 1.0 / v736;
          v445 = v443 * *(float *)&v744 * v444 + (double)xbase;
          _CHP(v442, v434);
          xp = (int)v445;
          v446 = v444 * (v443 * *(float *)&v740) + (double)ybase;
          _CHP(v447, v434);
          yp = (int)v446;
          LightXYZ_variable_14 = (float)v732;
          v448 = drawtrk3_c_variable_6 * v839
            + drawtrk3_c_variable_6 * v836
            - drawtrk3_c_variable_6 * v623
            + v629
            - viewx;
          v449 = drawtrk3_c_variable_6 * v838
            + drawtrk3_c_variable_6 * v835
            - drawtrk3_c_variable_6 * v622
            + v628
            - viewy;
          v450 = drawtrk3_c_variable_6 * v837
            + drawtrk3_c_variable_6 * v834
            - drawtrk3_c_variable_6 * v621
            + v627
            - viewz;
          v451 = scr_size;
          LightXYZ_variable_10 = (scr_size * xp) >> 6;
          LightXYZ_variable_11 = (scr_size * (199 - yp)) >> 6;
          v452 = v744;
          *(float *)&v744 = v448 * vk1 + v449 * vk4 + v450 * vk7;
          LightXYZ_variable_12 = v452;
          v453 = v740;
          *(float *)&v740 = v448 * vk2 + v449 * vk5 + v450 * vk8;
          v454 = v448 * vk3 + v449 * vk6 + v450 * vk9;
          v736 = v454;
          _CHP(v453, scr_size);
          v732 = (int)v454;
          LightXYZ_variable_13 = v459;
          v456 = v736 < (double)drawtrk3_c_variable_4;
          v457 = 0;
          v458 = v736 == drawtrk3_c_variable_4;
          LOWORD(v459) = v455;
          if (v736 < (double)drawtrk3_c_variable_4)
            v736 = 80.0;
          v460 = (double)VIEWDIST;
          v461 = 1.0 / v736;
          v462 = v460 * *(float *)&v744 * v461 + (double)xbase;
          _CHP(v459, v451);
          xp = (int)v462;
          v463 = v461 * (v460 * *(float *)&v740) + (double)ybase;
          _CHP(v464, v451);
          yp = (int)v463;
          LightXYZ_variable_19 = (float)v732;
          v465 = drawtrk3_c_variable_5 * v839
            + drawtrk3_c_variable_6 * v836
            + drawtrk3_c_variable_6 * v623
            + v629
            - viewx;
          v466 = drawtrk3_c_variable_5 * v838
            + drawtrk3_c_variable_6 * v835
            + drawtrk3_c_variable_6 * v622
            + v628
            - viewy;
          v467 = drawtrk3_c_variable_5 * v837
            + drawtrk3_c_variable_6 * v834
            + drawtrk3_c_variable_6 * v621
            + v627
            - viewz;
          v468 = scr_size;
          LightXYZ_variable_15 = (scr_size * xp) >> 6;
          LightXYZ_variable_16 = (scr_size * (199 - yp)) >> 6;
          v469 = v744;
          *(float *)&v744 = v465 * vk1 + v466 * vk4 + v467 * vk7;
          LightXYZ_variable_17 = v469;
          v470 = v740;
          *(float *)&v740 = v465 * vk2 + v466 * vk5 + v467 * vk8;
          v471 = v465 * vk3 + v466 * vk6 + v467 * vk9;
          v736 = v471;
          _CHP(v470, scr_size);
          v732 = (int)v471;
          LightXYZ_variable_18 = v476;
          v473 = v736 < (double)drawtrk3_c_variable_4;
          v474 = 0;
          v475 = v736 == drawtrk3_c_variable_4;
          LOWORD(v476) = v472;
          if (v736 < (double)drawtrk3_c_variable_4)
            v736 = 80.0;
          v477 = (double)VIEWDIST;
          v478 = 1.0 / v736;
          v479 = v477 * *(float *)&v744 * v478 + (double)xbase;
          _CHP(v476, v468);
          xp = (int)v479;
          v480 = v478 * (v477 * *(float *)&v740) + (double)ybase;
          _CHP(v481, v468);
          yp = (int)v480;
          LightXYZ_variable_24 = (float)v732;
          v482 = drawtrk3_c_variable_5 * v839
            - drawtrk3_c_variable_6 * v836
            + drawtrk3_c_variable_6 * v623
            + v629
            - viewx;
          v483 = drawtrk3_c_variable_5 * v838
            - drawtrk3_c_variable_6 * v835
            + drawtrk3_c_variable_6 * v622
            + v628
            - viewy;
          v484 = drawtrk3_c_variable_5 * v837
            - drawtrk3_c_variable_6 * v834
            + drawtrk3_c_variable_6 * v621
            + v627
            - viewz;
          v485 = scr_size;
          LightXYZ_variable_20 = (scr_size * xp) >> 6;
          LightXYZ_variable_21 = (scr_size * (199 - yp)) >> 6;
          v486 = v744;
          *(float *)&v744 = v482 * vk1 + v483 * vk4 + v484 * vk7;
          LightXYZ_variable_22 = v486;
          v487 = v740;
          *(float *)&v740 = v482 * vk2 + v483 * vk5 + v484 * vk8;
          v488 = v482 * vk3 + v483 * vk6 + v484 * vk9;
          v736 = v488;
          _CHP(v487, scr_size);
          v732 = (int)v488;
          LightXYZ_variable_23 = v493;
          v490 = v736 < (double)drawtrk3_c_variable_4;
          v491 = 0;
          v492 = v736 == drawtrk3_c_variable_4;
          LOWORD(v493) = v489;
          if (v736 < (double)drawtrk3_c_variable_4)
            v736 = 80.0;
          v494 = (double)VIEWDIST;
          v495 = 1.0 / v736;
          v496 = v494 * *(float *)&v744 * v495 + (double)xbase;
          _CHP(v493, v485);
          xp = (int)v496;
          v497 = v495 * (v494 * *(float *)&v740) + (double)ybase;
          _CHP(v498, v485);
          yp = (int)v497;
          LightXYZ_variable_29 = (float)v732;
          v499 = drawtrk3_c_variable_6 * v839
            - drawtrk3_c_variable_6 * v836
            + drawtrk3_c_variable_6 * v623
            + v629
            - viewx;
          v500 = drawtrk3_c_variable_6 * v838
            - drawtrk3_c_variable_6 * v835
            + drawtrk3_c_variable_6 * v622
            + v628
            - viewy;
          v501 = drawtrk3_c_variable_6 * v837
            - drawtrk3_c_variable_6 * v834
            + drawtrk3_c_variable_6 * v621
            + v627
            - viewz;
          v502 = scr_size;
          LightXYZ_variable_25 = (scr_size * xp) >> 6;
          LightXYZ_variable_26 = (scr_size * (199 - yp)) >> 6;
          v503 = v744;
          *(float *)&v744 = v499 * vk1 + v500 * vk4 + v501 * vk7;
          LightXYZ_variable_27 = v503;
          v504 = v740;
          *(float *)&v740 = v499 * vk2 + v500 * vk5 + v501 * vk8;
          v505 = v499 * vk3 + v500 * vk6 + v501 * vk9;
          v736 = v505;
          _CHP(v504, scr_size);
          v732 = (int)v505;
          LightXYZ_variable_28 = v510;
          v507 = v736 < (double)drawtrk3_c_variable_4;
          v508 = 0;
          v509 = v736 == drawtrk3_c_variable_4;
          LOWORD(v510) = v506;
          if (v736 < (double)drawtrk3_c_variable_4)
            v736 = 80.0;
          v511 = (double)VIEWDIST;
          v512 = 1.0 / v736;
          v513 = v511 * *(float *)&v744 * v512 + (double)xbase;
          _CHP(v510, v502);
          xp = (int)v513;
          v514 = v512 * (v511 * *(float *)&v740) + (double)ybase;
          _CHP(v515, v502);
          yp = (int)v514;
          LightXYZ_variable_34 = (float)v732;
          v516 = drawtrk3_c_variable_6 * v839
            + drawtrk3_c_variable_6 * v836
            + drawtrk3_c_variable_6 * v623
            + v629
            - viewx;
          v517 = drawtrk3_c_variable_6 * v838
            + drawtrk3_c_variable_6 * v835
            + drawtrk3_c_variable_6 * v622
            + v628
            - viewy;
          v518 = drawtrk3_c_variable_6 * v837
            + drawtrk3_c_variable_6 * v834
            + drawtrk3_c_variable_6 * v621
            + v627
            - viewz;
          v519 = scr_size;
          LightXYZ_variable_30 = (scr_size * xp) >> 6;
          LightXYZ_variable_31 = (scr_size * (199 - yp)) >> 6;
          v520 = v744;
          *(float *)&v744 = v516 * vk1 + v517 * vk4 + v518 * vk7;
          LightXYZ_variable_32 = v520;
          v521 = v740;
          *(float *)&v740 = v516 * vk2 + v517 * vk5 + v518 * vk8;
          v522 = v516 * vk3 + v517 * vk6 + v518 * vk9;
          v736 = v522;
          _CHP(v521, scr_size);
          v732 = (int)v522;
          LightXYZ_variable_33 = v527;
          v524 = v736 < (double)drawtrk3_c_variable_4;
          v525 = 0;
          v526 = v736 == drawtrk3_c_variable_4;
          LOWORD(v527) = v523;
          if (v736 < (double)drawtrk3_c_variable_4)
            v736 = 80.0;
          v528 = (double)VIEWDIST;
          v529 = 1.0 / v736;
          v530 = v528 * *(float *)&v744 * v529 + (double)xbase;
          _CHP(v527, v519);
          xp = (int)v530;
          v531 = v529 * (v528 * *(float *)&v740) + (double)ybase;
          v532 = scr_size;
          _CHP(scr_size * (int)v530, scr_size);
          yp = (int)v531;
          LightXYZ_variable_35 = v533 >> 6;
          LightXYZ_variable_36 = (v532 * (199 - (int)v531)) >> 6;
          LightXYZ_variable_37 = v744;
          RoadPoly_variable_3 = 4;
          LightXYZ_variable_38 = v740;
          LightXYZ_variable_39 = (float)v732;
          if (countdown >= 0) {
            if (countdown >= 72)
              RoadPoly = 8449;
            else
              RoadPoly = 8450;
          } else {
            RoadPoly = 8451;
          }
          v534 = 0;
          v535 = 0;
          v536 = drawtrk3_c_variable_3;
          do {
            v537 = (LightXYZ_variable_4[5 * cube_faces[v535]]
                  + LightXYZ_variable_4[5 * cube_faces_variable_1[v535]]
                  + LightXYZ_variable_4[5 * cube_faces_variable_2[v535]]
                  + LightXYZ_variable_4[5 * cube_faces_variable_3[v535]])
              * v536;
            ++v534;
            v535 += 4;
            *(float *)&v551[v534 - 1] = v537;
          } while (v534 != 6);
          v632 = 0;
          set_starts(0, 24);
          do {
            v538 = 1;
            v539 = 1;
            v540 = 0;
            v730 = *(float *)v551;
            do {
              if (*(float *)&v551[v539] > (double)v730) {
                v540 = v538;
                v730 = *(float *)&v551[v539];
              }
              ++v538;
              ++v539;
            } while (v538 < 6);
            v551[v540] = -581039253;
            v541 = 4 * v540;
            v542 = 5 * cube_faces[v541];
            v543 = LightXYZ[v542];
            v544 = cube_faces_variable_1[v541];
            RoadPoly_variable_5 = LightXYZ_variable_1[v542];
            RoadPoly_variable_4 = v543;
            v545 = LightXYZ[5 * v544];
            v546 = cube_faces_variable_2[v541];
            RoadPoly_variable_7 = LightXYZ_variable_1[5 * v544];
            RoadPoly_variable_6 = v545;
            RoadPoly_variable_8 = LightXYZ[5 * v546];
            v547 = cube_faces_variable_3[v541];
            RoadPoly_variable_9 = LightXYZ_variable_1[5 * v546];
            v548 = 5 * v547;
            v549 = LightXYZ[5 * v547];
            RoadPoly_variable_11 = LightXYZ_variable_1[v548];
            RoadPoly_variable_10 = v549;
            if ((RoadPoly & 0x100) != 0)
              POLYTEX(gfx_size);
            else
              POLYFLAT(v827, &RoadPoly);
            ++v632;
          } while (v632 < 6);
          goto LABEL_1265;
        default:
          goto LABEL_1265;
      }
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void subdivide(
        int a1,
        int a2,
        float a3,
        float a4,
        float a5,
        float a6,
        float a7,
        float a8,
        float a9,
        float a10,
        float a11,
        float a12,
        float a13,
        float a14,
        int a15,
        int a16)
{
  (void)a1;
  (void) a2;
  (void) a3;
  (void) a4;
  (void) a5;
  (void) a6;
  (void) a7;
  (void) a8;
  (void) a9;
  (void) a10;
  (void) a11;
  (void) a12;
  (void) a13;
  (void) a14;
  (void) a15;
  (void) a16;
  /*
  int v18; // ebp
  int v19; // edi
  int v20; // esi
  int v21; // ebx
  int v22; // [esp+0h] [ebp-28h]
  int v23; // [esp+4h] [ebp-24h]
  int v24; // [esp+8h] [ebp-20h]
  int v25; // [esp+Ch] [ebp-1Ch]
  int v26; // [esp+10h] [ebp-18h]

  if ((*(_BYTE *)(a2 + 2) & 2) != 0)
    return;
  subptr = a1;
  subpoly = a2;
  v18 = *(_DWORD *)(a2 + 8);
  v19 = *(_DWORD *)(a2 + 16);
  v23 = *(_DWORD *)(a2 + 12);
  v22 = *(_DWORD *)(a2 + 36);
  v24 = *(_DWORD *)(a2 + 20);
  subpolytype = a15;
  v26 = *(_DWORD *)(a2 + 24);
  v25 = *(_DWORD *)(a2 + 28);
  v20 = *(_DWORD *)(a2 + 32);
  fliptype = (*(_BYTE *)(a2 + 1) & 0x10) != 0;
  if ((*(_BYTE *)(a2 + 2) & 4) != 0)
    fliptype += 2;
  flatpol = ((*(_BYTE *)(subpoly + 1) & 1) != 0) - 1;
  if (subpolytype >= 0) {
    v21 = 1024;
    tex_wid = 1024;
    goto LABEL_9;
  }
  if (subpolytype != -1) {
    v21 = 2048;
    tex_wid = 1024;
  LABEL_9:
    tex_hgt = v21;
    goto LABEL_10;
  }
  tex_wid = 2048;
  tex_hgt = 1024;
LABEL_10:
  if (a16) {
    tex_wid >>= 1;
    tex_hgt >>= 1;
  }
  dodivide(
    a3,
    a4,
    a5,
    a6,
    a7,
    a8,
    a9,
    a10,
    a11,
    a12,
    a13,
    a14,
    v18,
    v23,
    v19,
    v24,
    v26,
    v25,
    v20,
    v22,
    0,
    0,
    tex_wid,
    tex_hgt);
  set_starts(0, v24);
  if (showsub) {
    if (a5 >= 1.0 && a8 >= 1.0)
      compout(v24, 243);
    if (a8 >= 1.0 && a11 >= 1.0)
      compout(v25, 243);
    if (a11 >= 1.0 && a14 >= 1.0)
      compout(v22, 243);
    if (a14 >= 1.0 && a5 >= 1.0)
      compout(v23, 243);
  }*/
}

//-------------------------------------------------------------------------------------------------

int dodivide(
        float a1,
        float a2,
        float a3,
        float a4,
        float a5,
        float a6,
        float a7,
        float a8,
        float a9,
        float a10,
        float a11,
        float a12,
        int a13,
        int a14,
        int a15,
        int a16,
        int a17,
        int a18,
        int a19,
        int a20,
        int a21,
        int a22,
        int a23,
        int a24)
{
  (void)a1;
  (void)a2;
  (void)a3;
  (void)a4;
  (void)a5;
  (void)a6;
  (void)a7;
  (void)a8;
  (void)a9;
  (void)a10;
  (void)a11;
  (void)a12;
  (void)a13;
  (void)a14;
  (void)a15;
  (void)a16;
  (void)a17;
  (void)a18;
  (void)a19;
  (void)a20;
  (void)a21;
  (void)a22;
  (void)a23;
  (void)a24;/*
  int v29; // edx
  float v30; // eax
  float v31; // eax
  float v32; // eax
  float v33; // eax
  float v34; // eax
  float v35; // eax
  int result; // eax
  int v37; // eax
  int v38; // eax
  int v39; // eax
  int v40; // eax
  int v41; // eax
  int v42; // eax
  int v43; // eax
  int v44; // edx
  int v45; // edx
  int v46; // eax
  int v47; // eax
  __int16 v48; // fps
  _BOOL1 v49; // c0
  char v50; // c2
  _BOOL1 v51; // c3
  int v52; // eax
  double v53; // st7
  double v54; // st6
  double v55; // st5
  double v56; // st4
  double v57; // st7
  int v58; // eax
  int v59; // eax
  __int16 v60; // fps
  _BOOL1 v61; // c0
  char v62; // c2
  _BOOL1 v63; // c3
  double v64; // st7
  double v65; // st6
  double v66; // st5
  double v67; // st4
  double v68; // st7
  int v69; // eax
  __int16 v70; // fps
  _BOOL1 v71; // c0
  char v72; // c2
  _BOOL1 v73; // c3
  double v74; // st7
  double v75; // st6
  double v76; // st5
  double v77; // st4
  double v78; // st7
  int v79; // eax
  int v80; // eax
  __int16 v81; // fps
  _BOOL1 v82; // c0
  char v83; // c2
  _BOOL1 v84; // c3
  double v85; // st7
  double v86; // st6
  double v87; // st5
  double v88; // st4
  double v89; // st7
  int v90; // eax
  __int16 v91; // fps
  _BOOL1 v92; // c0
  char v93; // c2
  _BOOL1 v94; // c3
  int v95; // eax
  double v96; // st7
  double v97; // st6
  double v98; // st5
  double v99; // st4
  double v100; // st7
  int v101; // eax
  int v102; // eax
  __int16 v103; // fps
  _BOOL1 v104; // c0
  char v105; // c2
  _BOOL1 v106; // c3
  double v107; // st7
  double v108; // st6
  double v109; // st5
  double v110; // st4
  double v111; // st7
  int v112; // eax
  int v113; // eax
  __int16 v114; // fps
  _BOOL1 v115; // c0
  char v116; // c2
  _BOOL1 v117; // c3
  double v118; // st7
  double v119; // st6
  double v120; // st5
  double v121; // st4
  double v122; // st7
  int v123; // eax
  int v124; // eax
  __int16 v125; // fps
  _BOOL1 v126; // c0
  char v127; // c2
  _BOOL1 v128; // c3
  double v129; // st7
  double v130; // st6
  double v131; // st5
  double v132; // st4
  double v133; // st7
  int v134; // eax
  int v135; // eax
  __int16 v136; // fps
  _BOOL1 v137; // c0
  char v138; // c2
  _BOOL1 v139; // c3
  double v140; // st7
  double v141; // st6
  double v142; // st5
  double v143; // st4
  double v144; // st7
  int v145; // eax
  int v146; // edx
  int v147; // [esp-28h] [ebp-180h]
  int v148; // [esp+Ch] [ebp-14Ch]
  float v149; // [esp+10h] [ebp-148h]
  float v150; // [esp+14h] [ebp-144h]
  float v151; // [esp+18h] [ebp-140h]
  int v152; // [esp+1Ch] [ebp-13Ch]
  int v153; // [esp+28h] [ebp-130h]
  int v154; // [esp+30h] [ebp-128h]
  float v155; // [esp+3Ch] [ebp-11Ch]
  float v156; // [esp+54h] [ebp-104h]
  int v157; // [esp+5Ch] [ebp-FCh]
  int v158; // [esp+64h] [ebp-F4h]
  int v159; // [esp+78h] [ebp-E0h]
  float v160; // [esp+7Ch] [ebp-DCh]
  int v161; // [esp+8Ch] [ebp-CCh]
  int v162; // [esp+90h] [ebp-C8h]
  int v163; // [esp+94h] [ebp-C4h]
  int v164; // [esp+98h] [ebp-C0h]
  float v165; // [esp+9Ch] [ebp-BCh]
  float v166; // [esp+A0h] [ebp-B8h]
  int v167; // [esp+A4h] [ebp-B4h]
  float v168; // [esp+A8h] [ebp-B0h]
  float v169; // [esp+ACh] [ebp-ACh]
  float v170; // [esp+B0h] [ebp-A8h]
  float v171; // [esp+B4h] [ebp-A4h]
  float v172; // [esp+B8h] [ebp-A0h]
  float v173; // [esp+BCh] [ebp-9Ch]
  float v174; // [esp+C0h] [ebp-98h]
  float v175; // [esp+C4h] [ebp-94h]
  float v176; // [esp+C8h] [ebp-90h]
  int v177; // [esp+CCh] [ebp-8Ch]
  int v178; // [esp+D0h] [ebp-88h]
  int v179; // [esp+D4h] [ebp-84h]
  int v180; // [esp+D8h] [ebp-80h]
  int v181; // [esp+E4h] [ebp-74h]
  int v182; // [esp+E8h] [ebp-70h]
  int v183; // [esp+ECh] [ebp-6Ch]
  int v184; // [esp+F0h] [ebp-68h]
  int v185; // [esp+F4h] [ebp-64h]
  int v186; // [esp+FCh] [ebp-5Ch]
  int v187; // [esp+100h] [ebp-58h]
  int v188; // [esp+104h] [ebp-54h]
  float v189; // [esp+108h] [ebp-50h]
  float v190; // [esp+10Ch] [ebp-4Ch]
  float v191; // [esp+110h] [ebp-48h]
  float v192; // [esp+114h] [ebp-44h]
  float v193; // [esp+118h] [ebp-40h]
  float v194; // [esp+11Ch] [ebp-3Ch]
  float v195; // [esp+120h] [ebp-38h]
  float v196; // [esp+124h] [ebp-34h]
  float v197; // [esp+128h] [ebp-30h]
  int v198; // [esp+12Ch] [ebp-2Ch]
  float v199; // [esp+130h] [ebp-28h]
  float v200; // [esp+134h] [ebp-24h]
  float v201; // [esp+138h] [ebp-20h]
  int v202; // [esp+13Ch] [ebp-1Ch]

  while (2) {
    v29 = 0;
    divtype = 0;
    if (a3 <= (double)a6)
      v30 = a6;
    else
      v30 = a3;
    v156 = v30;
    if (a9 <= (double)a12)
      v31 = a12;
    else
      v31 = a9;
    if (v156 <= (double)v31) {
      if (a9 <= (double)a12)
        v32 = a12;
      else
        v32 = a9;
    } else if (a3 <= (double)a6) {
      v32 = a6;
    } else {
      v32 = a3;
    }
    if (v32 < (double)drawtrk3_c_variable_9)
      v29 = -1;
    if (a3 >= (double)a6)
      v33 = a6;
    else
      v33 = a3;
    v155 = v33;
    if (a9 >= (double)a12)
      v34 = a12;
    else
      v34 = a9;
    if (v155 >= (double)v34) {
      if (a9 >= (double)a12)
        v35 = a12;
      else
        v35 = a9;
    } else if (a3 >= (double)a6) {
      v35 = a6;
    } else {
      v35 = a3;
    }
    if (v35 >= 1.0) {
      if (a15 >= a13)
        v153 = a15;
      else
        v153 = a13;
      v37 = a17;
      if (a17 <= a19)
        v37 = a19;
      if (v153 <= v37) {
        v38 = a17;
        if (a17 <= a19)
          v38 = a19;
      } else {
        v38 = a13;
        if (a15 >= a13)
          v38 = a15;
      }
      if (v38 < 0)
        v29 = -1;
      if (a15 <= a13)
        v157 = a15;
      else
        v157 = a13;
      v39 = a17;
      if (a17 >= a19)
        v39 = a19;
      if (v157 >= v39) {
        v40 = a17;
        if (a17 >= a19)
          v40 = a19;
      } else {
        v40 = a13;
        if (a15 <= a13)
          v40 = a15;
      }
      if (v40 >= winw)
        v29 = -1;
      if (a14 <= a16)
        v158 = a16;
      else
        v158 = a14;
      v41 = a18;
      if (a18 <= a20)
        v41 = a20;
      if (v158 <= v41) {
        v42 = a18;
        if (a18 <= a20)
          v42 = a20;
      } else if (a14 <= a16) {
        v42 = a16;
      } else {
        v42 = a14;
      }
      if (v42 < 0)
        v29 = -1;
      if (a14 >= a16)
        v154 = a16;
      else
        v154 = a14;
      v43 = a18;
      if (a18 >= a20)
        v43 = a20;
      if (v154 >= v43) {
        result = a18;
        if (a18 >= a20)
          result = a20;
      } else if (a14 >= a16) {
        result = a16;
      } else {
        result = a14;
      }
      if (result >= winh)
        v29 = -1;
      v152 = -1;
    } else {
      if (a23 > min_sub_size)
        ++divtype;
      if (a24 > min_sub_size)
        divtype += 2;
      result = 0;
      v152 = 0;
    }
    if (v29)
      return result;
    if (!divtype && !flatpol) {
      polyxsize = abs32(a20 - a18) + abs32(a14 - a16) + abs32(a19 - a17) + abs32(a13 - a15);
      polyysize = abs32(a16 - a18) + abs32(a14 - a20) + abs32(a15 - a17) + abs32(a13 - a19);
      if (polyxsize > small_poly && a23 > min_sub_size)
        ++divtype;
      if (polyysize > small_poly && a24 > min_sub_size)
        divtype += 2;
    }
    v44 = winw >> 31;
    result = winw / 2;
    v150 = a3 + a6;
    v149 = a2 + a5;
    v151 = a1 + a4;
    v166 = v150 * drawtrk3_c_variable_7;
    v160 = v149 * drawtrk3_c_variable_7;
    v159 = winw / 2;
    v165 = v151 * drawtrk3_c_variable_7;
    switch (divtype) {
      case 0:
        if (!v152)
          return result;
        v148 = subpoly;
        v45 = subpoly;
        *(_DWORD *)(subpoly + 8) = a13;
        *(_DWORD *)(v45 + 24) = a17;
        *(_DWORD *)(v45 + 28) = a18;
        *(_DWORD *)(v45 + 32) = a19;
        *(_DWORD *)(v45 + 36) = a20;
        startsx = (a23 + a21 - 1) << 12;
        startsx_variable_1 = a21 << 12;
        startsx_variable_2 = a21 << 12;
        startsx_variable_3 = (a23 + a21 - 1) << 12;
        startsy = a22 << 12;
        startsy_variable_1 = a22 << 12;
        *(_DWORD *)(v45 + 12) = a14;
        *(_DWORD *)(v45 + 16) = a15;
        startsy_variable_2 = (a24 + a22 - 1) << 12;
        startsy_variable_3 = (a24 + a22 - 1) << 12;
        v46 = subpolytype;
        *(_DWORD *)(v45 + 20) = a16;
        if (v46 < 1) {
          if (v46 < -2)
            goto LABEL_110;
          if ((*(_BYTE *)(v45 + 1) & 1) != 0)
            goto LABEL_111;
          goto LABEL_105;
        }
        if (v46 <= 1)
          goto LABEL_111;
        if (v46 <= 2)
          goto LABEL_106;
        if (v46 == 666) {
          if ((*(_BYTE *)(v45 + 1) & 1) != 0) {
          LABEL_111:
            result = POLYTEX(gfx_size);
            goto LABEL_114;
          }
        LABEL_105:
          v45 = v148;
        LABEL_106:
          v47 = subptr;
          goto LABEL_113;
        }
      LABEL_110:
        if ((*(_BYTE *)(subpoly + 1) & 1) != 0)
          goto LABEL_111;
        v47 = subptr;
        v45 = subpoly;
      LABEL_113:
        result = POLYFLAT(v47, v45);
      LABEL_114:
        if (showsub) {
          compout(*(_DWORD *)(subpoly + 20), 159);
          compout(*(_DWORD *)(subpoly + 28), 159);
          compout(*(_DWORD *)(subpoly + 36), 159);
          return compout(*(_DWORD *)(subpoly + 20), 159);
        }
        return result;
      case 1:
        HIWORD(v52) = HIWORD(v166);
        v49 = v166 > 1.0;
        v50 = 0;
        v51 = 1.0 == v166;
        LOWORD(v52) = v48;
        if (v166 < 1.0) {
          if ((double)v159 <= v165)
            v167 = 20000;
          else
            v167 = -20000;
          v44 = winh >> 31;
          v59 = winh / 2;
          if ((double)(winh / 2) <= v160)
            v179 = 20000;
          else
            v179 = -20000;
        } else {
          v53 = (double)VIEWDIST;
          v54 = 1.0 / v166;
          v55 = (double)scr_size;
          v56 = (v53 * v165 * v54 + (double)xbase) * v55 * drawtrk3_c_variable_8;
          _CHP(v52, v44);
          v167 = (int)v56;
          v57 = v55 * (drawtrk3_c_variable_10 - v54 * (v53 * v160) - (double)ybase) * drawtrk3_c_variable_8;
          _CHP(v58, v44);
          v179 = (int)v57;
        }
        v173 = (a7 + a10) * drawtrk3_c_variable_7;
        v172 = (a8 + a11) * drawtrk3_c_variable_7;
        v171 = (a9 + a12) * drawtrk3_c_variable_7;
        v61 = v171 > 1.0;
        v62 = 0;
        v63 = 1.0 == v171;
        LOWORD(v59) = v60;
        if (v171 < 1.0) {
          if ((double)(winw / 2) <= v173)
            v164 = 20000;
          else
            v164 = -20000;
          if ((double)(winh / 2) <= v172)
            v163 = 20000;
          else
            v163 = -20000;
        } else {
          v64 = (double)VIEWDIST;
          v65 = 1.0 / v171;
          v66 = (double)scr_size;
          v67 = (v64 * v173 * v65 + (double)xbase) * v66 * drawtrk3_c_variable_8;
          _CHP(v59, v44);
          v164 = (int)v67;
          v68 = v66 * (drawtrk3_c_variable_10 - v65 * (v64 * v172) - (double)ybase) * drawtrk3_c_variable_8;
          _CHP(v69, v44);
          v163 = (int)v68;
        }
        a23 >>= 1;
        if ((fliptype & 1) != 0) {
          v147 = a15;
          a15 = v167;
          dodivide(
            v165,
            v160,
            v166,
            a4,
            a5,
            a6,
            a7,
            a8,
            a9,
            v173,
            v172,
            v171,
            v167,
            v179,
            v147,
            a16,
            a17,
            a18,
            v164,
            v163,
            a23 + a21,
            a22,
            a23,
            a24);
          a4 = v165;
          a5 = v160;
          a6 = v166;
          a7 = v173;
          a8 = v172;
          a9 = v171;
        } else {
          dodivide(
            v165,
            v160,
            v166,
            a4,
            a5,
            a6,
            a7,
            a8,
            a9,
            v173,
            v172,
            v171,
            v167,
            v179,
            a15,
            a16,
            a17,
            a18,
            v164,
            v163,
            a21,
            a22,
            a23,
            a24);
          a4 = v165;
          a5 = v160;
          a6 = v166;
          a7 = v173;
          a8 = v172;
          a21 += a23;
          a9 = v171;
          a15 = v167;
        }
        a17 = v164;
        a16 = v179;
        a18 = v163;
        continue;
      case 2:
        v176 = (a4 + a7) * drawtrk3_c_variable_7;
        v175 = (a5 + a8) * drawtrk3_c_variable_7;
        v174 = (a6 + a9) * drawtrk3_c_variable_7;
        v71 = v174 > 1.0;
        v72 = 0;
        v73 = 1.0 == v174;
        LOWORD(result) = v70;
        if (v174 < 1.0) {
          if ((double)v159 <= v176)
            v178 = 20000;
          else
            v178 = -20000;
          v44 = winh >> 31;
          v80 = winh / 2;
          if ((double)(winh / 2) <= v175)
            v177 = 20000;
          else
            v177 = -20000;
        } else {
          v74 = (double)VIEWDIST;
          v75 = 1.0 / v174;
          v76 = (double)scr_size;
          v77 = (v74 * v176 * v75 + (double)xbase) * v76 * drawtrk3_c_variable_8;
          _CHP(result, v44);
          v178 = (int)v77;
          v78 = v76 * (drawtrk3_c_variable_10 - v75 * (v74 * v175) - (double)ybase) * drawtrk3_c_variable_8;
          _CHP(v79, v44);
          v177 = (int)v78;
        }
        v170 = (a10 + a1) * drawtrk3_c_variable_7;
        v169 = (a11 + a2) * drawtrk3_c_variable_7;
        v168 = (a12 + a3) * drawtrk3_c_variable_7;
        v82 = v168 > 1.0;
        v83 = 0;
        v84 = 1.0 == v168;
        LOWORD(v80) = v81;
        if (v168 < 1.0) {
          if ((double)(winw / 2) <= v170)
            v162 = 20000;
          else
            v162 = -20000;
          if ((double)(winh / 2) <= v169)
            v161 = 20000;
          else
            v161 = -20000;
        } else {
          v85 = (double)VIEWDIST;
          v86 = 1.0 / v168;
          v87 = (double)scr_size;
          v88 = (v85 * v170 * v86 + (double)xbase) * v87 * drawtrk3_c_variable_8;
          _CHP(v80, v44);
          v162 = (int)v88;
          v89 = v87 * (drawtrk3_c_variable_10 - v86 * (v85 * v169) - (double)ybase) * drawtrk3_c_variable_8;
          _CHP(v90, v44);
          v161 = (int)v89;
        }
        a24 >>= 1;
        if ((fliptype & 2) != 0) {
          dodivide(
            a1,
            a2,
            a3,
            a4,
            a5,
            a6,
            v176,
            v175,
            v174,
            v170,
            v169,
            v168,
            a13,
            a14,
            a15,
            a16,
            v178,
            v177,
            v162,
            v161,
            a21,
            a24 + a22,
            a23,
            a24);
          a1 = v170;
          a2 = v169;
          a3 = v168;
          a4 = v176;
          a16 = v177;
          a5 = v175;
          a15 = v178;
          a6 = v174;
          a14 = v161;
        } else {
          dodivide(
            a1,
            a2,
            a3,
            a4,
            a5,
            a6,
            v176,
            v175,
            v174,
            v170,
            v169,
            v168,
            a13,
            a14,
            a15,
            a16,
            v178,
            v177,
            v162,
            v161,
            a21,
            a22,
            a23,
            a24);
          a1 = v170;
          a2 = v169;
          a3 = v168;
          a22 += a24;
          a4 = v176;
          a16 = v177;
          a5 = v175;
          a14 = v161;
          a6 = v174;
          a15 = v178;
        }
        a13 = v162;
        continue;
      case 3:
        HIWORD(v95) = HIWORD(v166);
        v92 = v166 > 1.0;
        v93 = 0;
        v94 = 1.0 == v166;
        LOWORD(v95) = v91;
        if (v166 < 1.0) {
          if ((double)v159 <= v165)
            v183 = 20000;
          else
            v183 = -20000;
          v44 = winh >> 31;
          v102 = winh / 2;
          if ((double)(winh / 2) <= v160)
            v181 = 20000;
          else
            v181 = -20000;
        } else {
          v96 = (double)VIEWDIST;
          v97 = 1.0 / v166;
          v98 = (double)scr_size;
          v99 = (v96 * v165 * v97 + (double)xbase) * v98 * drawtrk3_c_variable_8;
          _CHP(v95, v44);
          v183 = (int)v99;
          v100 = v98 * (drawtrk3_c_variable_10 - v97 * (v96 * v160) - (double)ybase) * drawtrk3_c_variable_8;
          _CHP(v101, v44);
          v181 = (int)v100;
        }
        v193 = (a4 + a7) * drawtrk3_c_variable_7;
        v189 = (a5 + a8) * drawtrk3_c_variable_7;
        v190 = (a6 + a9) * drawtrk3_c_variable_7;
        v104 = v190 > 1.0;
        v105 = 0;
        v106 = 1.0 == v190;
        LOWORD(v102) = v103;
        if (v190 < 1.0) {
          if ((double)(winw / 2) <= v193)
            v187 = 20000;
          else
            v187 = -20000;
          v44 = winh >> 31;
          v113 = winh / 2;
          if ((double)(winh / 2) <= v189)
            v182 = 20000;
          else
            v182 = -20000;
        } else {
          v107 = (double)VIEWDIST;
          v108 = 1.0 / v190;
          v109 = (double)scr_size;
          v110 = (v107 * v193 * v108 + (double)xbase) * v109 * drawtrk3_c_variable_8;
          _CHP(v102, v44);
          v187 = (int)v110;
          v111 = v109 * (drawtrk3_c_variable_10 - v108 * (v107 * v189) - (double)ybase) * drawtrk3_c_variable_8;
          _CHP(v112, v44);
          v182 = (int)v111;
        }
        v197 = (a7 + a10) * drawtrk3_c_variable_7;
        v195 = (a8 + a11) * drawtrk3_c_variable_7;
        v196 = (a9 + a12) * drawtrk3_c_variable_7;
        v115 = v196 > 1.0;
        v116 = 0;
        v117 = 1.0 == v196;
        LOWORD(v113) = v114;
        if (v196 < 1.0) {
          if ((double)(winw / 2) <= v197)
            v185 = 20000;
          else
            v185 = -20000;
          v44 = winh >> 31;
          v124 = winh / 2;
          if ((double)(winh / 2) <= v195)
            v184 = 20000;
          else
            v184 = -20000;
        } else {
          v118 = (double)VIEWDIST;
          v119 = 1.0 / v196;
          v120 = (double)scr_size;
          v121 = (v118 * v197 * v119 + (double)xbase) * v120 * drawtrk3_c_variable_8;
          _CHP(v113, v44);
          v185 = (int)v121;
          v122 = v120 * (drawtrk3_c_variable_10 - v119 * (v118 * v195) - (double)ybase) * drawtrk3_c_variable_8;
          _CHP(v123, v44);
          v184 = (int)v122;
        }
        v192 = (a10 + a1) * drawtrk3_c_variable_7;
        v194 = (a11 + a2) * drawtrk3_c_variable_7;
        v191 = (a12 + a3) * drawtrk3_c_variable_7;
        v126 = v191 > 1.0;
        v127 = 0;
        v128 = 1.0 == v191;
        LOWORD(v124) = v125;
        if (v191 < 1.0) {
          if ((double)(winw / 2) <= v192)
            v188 = 20000;
          else
            v188 = -20000;
          v44 = winh >> 31;
          v135 = winh / 2;
          if ((double)(winh / 2) <= v194)
            v186 = 20000;
          else
            v186 = -20000;
        } else {
          v129 = (double)VIEWDIST;
          v130 = 1.0 / v191;
          v131 = (double)scr_size;
          v132 = (v129 * v192 * v130 + (double)xbase) * v131 * drawtrk3_c_variable_8;
          _CHP(v124, v44);
          v188 = (int)v132;
          v133 = v131 * (drawtrk3_c_variable_10 - v130 * (v129 * v194) - (double)ybase) * drawtrk3_c_variable_8;
          _CHP(v134, v44);
          v186 = (int)v133;
        }
        v199 = (v165 + v197) * drawtrk3_c_variable_7;
        v200 = (v160 + v195) * drawtrk3_c_variable_7;
        v201 = (v166 + v196) * drawtrk3_c_variable_7;
        v137 = v201 > 1.0;
        v138 = 0;
        v139 = 1.0 == v201;
        LOWORD(v135) = v136;
        if (v201 < 1.0) {
          if ((double)(winw / 2) <= v199)
            v202 = 20000;
          else
            v202 = -20000;
          if ((double)(winh / 2) <= v200)
            v198 = 20000;
          else
            v198 = -20000;
        } else {
          v140 = (double)VIEWDIST;
          v141 = 1.0 / v201;
          v142 = (double)scr_size;
          v143 = (v140 * v199 * v141 + (double)xbase) * v142 * drawtrk3_c_variable_8;
          _CHP(v135, v44);
          v202 = (int)v143;
          v144 = v142 * (drawtrk3_c_variable_10 - v141 * (v140 * v200) - (double)ybase) * drawtrk3_c_variable_8;
          _CHP(v145, v44);
          v198 = (int)v144;
        }
        result = fliptype;
        a23 >>= 1;
        a24 >>= 1;
        v180 = a24 + a22;
        v146 = a23 + a21;
        switch (fliptype) {
          case 0:
            dodivide(
              v165,
              v160,
              v166,
              a4,
              a5,
              a6,
              v193,
              v189,
              v190,
              v199,
              v200,
              v201,
              v183,
              v181,
              a15,
              a16,
              v187,
              v182,
              v202,
              v198,
              a21,
              a22,
              a23,
              a24);
            dodivide(
              a1,
              a2,
              a3,
              v165,
              v160,
              v166,
              v199,
              v200,
              v201,
              v192,
              v194,
              v191,
              a13,
              a14,
              v183,
              v181,
              v202,
              v198,
              v188,
              v186,
              v146,
              a22,
              a23,
              a24);
            a16 = v198;
            dodivide(
              v199,
              v200,
              v201,
              v193,
              v189,
              v190,
              a7,
              a8,
              a9,
              v197,
              v195,
              v196,
              v202,
              v198,
              v187,
              v182,
              a17,
              a18,
              v185,
              v184,
              a21,
              v180,
              a23,
              a24);
            a1 = v192;
            a2 = v194;
            a3 = v191;
            a4 = v199;
            a5 = v200;
            a6 = v201;
            a7 = v197;
            a8 = v195;
            a9 = v196;
            a13 = v188;
            a21 += a23;
            a17 = v185;
            a15 = v202;
            a18 = v184;
            a14 = v186;
            a22 += a24;
            continue;
          case 1:
            dodivide(
              v165,
              v160,
              v166,
              a4,
              a5,
              a6,
              v193,
              v189,
              v190,
              v199,
              v200,
              v201,
              v183,
              v181,
              a15,
              a16,
              v187,
              v182,
              v202,
              v198,
              a23 + a21,
              a22,
              a23,
              a24);
            dodivide(
              a1,
              a2,
              a3,
              v165,
              v160,
              v166,
              v199,
              v200,
              v201,
              v192,
              v194,
              v191,
              a13,
              a14,
              v183,
              v181,
              v202,
              v198,
              v188,
              v186,
              a21,
              a22,
              a23,
              a24);
            a15 = v202;
            dodivide(
              v199,
              v200,
              v201,
              v193,
              v189,
              v190,
              a7,
              a8,
              a9,
              v197,
              v195,
              v196,
              v202,
              v198,
              v187,
              v182,
              a17,
              a18,
              v185,
              v184,
              v146,
              v180,
              a23,
              a24);
            a1 = v192;
            a2 = v194;
            a3 = v191;
            a4 = v199;
            a5 = v200;
            a6 = v201;
            a7 = v197;
            a8 = v195;
            a9 = v196;
            a13 = v188;
            a17 = v185;
            a16 = v198;
            a18 = v184;
            a14 = v186;
            a22 += a24;
            continue;
          case 2:
            dodivide(
              v165,
              v160,
              v166,
              a4,
              a5,
              a6,
              v193,
              v189,
              v190,
              v199,
              v200,
              v201,
              v183,
              v181,
              a15,
              a16,
              v187,
              v182,
              v202,
              v198,
              a21,
              v180,
              a23,
              a24);
            dodivide(
              a1,
              a2,
              a3,
              v165,
              v160,
              v166,
              v199,
              v200,
              v201,
              v192,
              v194,
              v191,
              a13,
              a14,
              v183,
              v181,
              v202,
              v198,
              v188,
              v186,
              v146,
              v180,
              a23,
              a24);
            a16 = v198;
            dodivide(
              v199,
              v200,
              v201,
              v193,
              v189,
              v190,
              a7,
              a8,
              a9,
              v197,
              v195,
              v196,
              v202,
              v198,
              v187,
              v182,
              a17,
              a18,
              v185,
              v184,
              a21,
              a22,
              a23,
              a24);
            a1 = v192;
            a2 = v194;
            a3 = v191;
            a4 = v199;
            a5 = v200;
            a6 = v201;
            a7 = v197;
            a8 = v195;
            a9 = v196;
            a21 += a23;
            a13 = v188;
            a15 = v202;
            a17 = v185;
            a14 = v186;
            a18 = v184;
            continue;
          case 3:
            dodivide(
              v165,
              v160,
              v166,
              a4,
              a5,
              a6,
              v193,
              v189,
              v190,
              v199,
              v200,
              v201,
              v183,
              v181,
              a15,
              a16,
              v187,
              v182,
              v202,
              v198,
              a23 + a21,
              v180,
              a23,
              a24);
            dodivide(
              a1,
              a2,
              a3,
              v165,
              v160,
              v166,
              v199,
              v200,
              v201,
              v192,
              v194,
              v191,
              a13,
              a14,
              v183,
              v181,
              v202,
              v198,
              v188,
              v186,
              a21,
              v180,
              a23,
              a24);
            a15 = v202;
            dodivide(
              v199,
              v200,
              v201,
              v193,
              v189,
              v190,
              a7,
              a8,
              a9,
              v197,
              v195,
              v196,
              v202,
              v198,
              v187,
              v182,
              a17,
              a18,
              v185,
              v184,
              v146,
              a22,
              a23,
              a24);
            a1 = v192;
            a2 = v194;
            a3 = v191;
            a4 = v199;
            a5 = v200;
            a6 = v201;
            a7 = v197;
            a8 = v195;
            a9 = v196;
            a13 = v188;
            a16 = v198;
            a17 = v185;
            a14 = v186;
            a18 = v184;
            continue;
          default:
            return result;
        }
        return result;
      default:
        return result;
    }
  }*/
  return 0;
}

//-------------------------------------------------------------------------------------------------

int facing_ok(
        float a1,
        float a2,
        float a3,
        float a4,
        float a5,
        float a6,
        float a7,
        float a8,
        float a9,
        float a10,
        float a11,
        float a12)
{
  (void)a1;
  (void)a2;
  (void)a3;
  (void)a4;
  (void)a5;
  (void)a6;
  (void)a7;
  (void)a8;
  (void)a9;
  (void)a10;
  (void)a11;
  (void)a12;
  return 0;/*
  float v13; // [esp+20h] [ebp-4h]

  v13 = a7 - a1;
  return (((a8 - a2) * (a6 - a12) - (a9 - a3) * (a5 - a11)) * a4
        + ((a9 - a3) * (a4 - a10) - (a6 - a12) * v13) * a5
        + ((a5 - a11) * v13 - (a4 - a10) * (a8 - a2)) * a6 >= 0.0)
    - 1;*/
}

//-------------------------------------------------------------------------------------------------

int Zcmp(float *a1, float *a2)
{
  (void)(a1); (void)(a2);
  return 0;
  /*
  int v2; // edx
  int v3; // ebx
  float v5; // [esp+0h] [ebp-Ch]
  float v6; // [esp+4h] [ebp-8h]

  v6 = a1[1];
  v5 = a2[1];
  v2 = *(__int16 *)a2;
  v3 = *(__int16 *)a1;
  if (v6 < (double)v5)
    return -1;
  if (v6 == v5) {
    if (v3 == v2)
      return 0;
    if (v3 >= v2)
      return -1;
  }
  return 1;*/
}

//-------------------------------------------------------------------------------------------------

void set_starts(unsigned int uiType)
{
  startsx[1] = 0;
  startsx[2] = 0;
  startsy[0] = 0;
  startsy[1] = 0;
  if (gfx_size) {
    if (uiType) {
      if (uiType <= 1) {
        startsx[0] = 0x3FF000; //64.0
        startsx[3] = 0x3FF000; //64.0
        startsy[2] = 0x1FF000; //31.875
        startsy[3] = 0x1FF000; //31.875
      } else if (uiType == 2) {
        startsx[0] = 0x1FF000; //31.875
        startsx[3] = 0x1FF000; //31.875
        startsy[2] = 0x3FF000; //64.0
        startsy[3] = 0x3FF000; //64.0
      }
    } else {
      startsx[0] = 0x1FF000; //31.875
      startsx[3] = 0x1FF000; //31.875
      startsy[2] = 0x1FF000; //31.875
      startsy[3] = 0x1FF000; //31.875
    }
  } else if (uiType) {
    if (uiType <= 1) {
      startsx[0] = 0x7FF000; //128.0
      startsx[3] = 0x7FF000; //128.0
      startsy[2] = 0x3FF000; //64.0
      startsy[3] = 0x3FF000; //64.0
    } else if (uiType == 2) {
      startsx[0] = 0x3FF000; //64.0
      startsx[3] = 0x3FF000; //64.0
      startsy[2] = 0x7FF000; //128.0
      startsy[3] = 0x7FF000; //128.0
    }
  } else {
    startsx[0] = 0x3FF000; //64.0
    startsx[3] = 0x3FF000; //64.0
    startsy[2] = 0x3FF000; //64.0
    startsy[3] = 0x3FF000; //64.0
  }
}

//-------------------------------------------------------------------------------------------------
#include "loadtrak.h"
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
//-------------------------------------------------------------------------------------------------

uint8 TrackSelect = 0;      //000A5F9C
char *delims = " ,\n\t\r";  //000A6088
tTrakView TrakView[500];    //0016FF20
int cur_laps[6];            //00176898
int meof;                   //00176AC4
tTrackInfo TrackInfo[500];  //00171E60
float cur_TrackZ;           //00178048
int TRAK_LEN;               //00178050

//-------------------------------------------------------------------------------------------------

void loadtrack(int iTrackIdx, int a2)
{ /*
  int v2; // ebx
  int v3; // ecx
  float *v4; // edi
  int v5; // edx
  int v6; // edx
  int v7; // ebx
  int v8; // eax
  __int64 v9; // rax
  int v10; // ebx
  int v11; // esi
  unsigned int v12; // eax
  unsigned int v13; // eax
  int v14; // ecx
  int v15; // edi
  int v16; // esi
  int v17; // ebp
  char *v18; // edx
  int v19; // ebx
  int v20; // edx
  int v21; // eax
  double v22; // st7
  int v23; // edx
  int v24; // ebx
  int v25; // eax
  unsigned int v26; // edx
  int v27; // ecx
  int v28; // ecx
  unsigned int v29; // edx
  int *v30; // edx
  int *v31; // edx
  _DWORD *v32; // ebx
  int *v33; // ecx
  int *v34; // edx
  int *v35; // eax
  _DWORD *v36; // ebx
  float *v37; // eax
  int v38; // edx
  int v39; // eax
  double v40; // st7
  long double v41; // st6
  long double v42; // st6
  int v43; // eax
  long double v44; // st7
  double v45; // st7
  unsigned int v46; // eax
  unsigned int v47; // edx
  double v48; // st7
  unsigned int v49; // eax
  int v50; // edx
  int v51; // eax
  int v52; // ecx
  int v53; // ebx
  int v54; // edx
  long double v55; // rt1
  int v56; // eax
  int inited; // eax
  int v58; // eax
  int v59; // eax
  int v60; // edx
  double v61; // st7
  __int64 v62; // rax
  __int16 *v63; // [esp+30h] [ebp-25Ch]
  double v64; // [esp+34h] [ebp-258h] BYREF
  int v65[2]; // [esp+3Ch] [ebp-250h] BYREF
  int v66[2]; // [esp+44h] [ebp-248h] BYREF
  double v67; // [esp+4Ch] [ebp-240h] BYREF
  double v68; // [esp+54h] [ebp-238h] BYREF
  double v69; // [esp+5Ch] [ebp-230h] BYREF
  double v70; // [esp+64h] [ebp-228h] BYREF
  double v71; // [esp+6Ch] [ebp-220h] BYREF
  double v72; // [esp+74h] [ebp-218h] BYREF
  double v73; // [esp+7Ch] [ebp-210h] BYREF
  double v74; // [esp+84h] [ebp-208h] BYREF
  double v75; // [esp+8Ch] [ebp-200h] BYREF
  double v76; // [esp+94h] [ebp-1F8h] BYREF
  double v77; // [esp+9Ch] [ebp-1F0h] BYREF
  double v78; // [esp+A4h] [ebp-1E8h] BYREF
  double v79; // [esp+ACh] [ebp-1E0h] BYREF
  double v80; // [esp+B4h] [ebp-1D8h] BYREF
  double v81; // [esp+BCh] [ebp-1D0h] BYREF
  double v82; // [esp+C4h] [ebp-1C8h] BYREF
  double v83; // [esp+CCh] [ebp-1C0h] BYREF
  double v84; // [esp+D4h] [ebp-1B8h] BYREF
  double v85; // [esp+DCh] [ebp-1B0h] BYREF
  double v86; // [esp+E4h] [ebp-1A8h] BYREF
  double v87; // [esp+ECh] [ebp-1A0h] BYREF
  double v88; // [esp+F4h] [ebp-198h] BYREF
  double v89; // [esp+FCh] [ebp-190h] BYREF
  double v90; // [esp+104h] [ebp-188h] BYREF
  double v91; // [esp+10Ch] [ebp-180h] BYREF
  double v92; // [esp+114h] [ebp-178h] BYREF
  double v93; // [esp+11Ch] [ebp-170h] BYREF
  double v94; // [esp+124h] [ebp-168h] BYREF
  long double v95; // [esp+12Ch] [ebp-160h] BYREF
  long double v96; // [esp+134h] [ebp-158h] BYREF
  long double v97; // [esp+13Ch] [ebp-150h] BYREF
  double v98; // [esp+144h] [ebp-148h]
  double v99; // [esp+14Ch] [ebp-140h]
  double v100; // [esp+154h] [ebp-138h]
  double v101; // [esp+15Ch] [ebp-130h]
  double v102; // [esp+164h] [ebp-128h]
  double v103; // [esp+16Ch] [ebp-120h]
  double v104; // [esp+174h] [ebp-118h]
  double v105; // [esp+17Ch] [ebp-110h]
  double v106; // [esp+184h] [ebp-108h]
  double v107; // [esp+18Ch] [ebp-100h]
  double v108; // [esp+194h] [ebp-F8h]
  double v109; // [esp+19Ch] [ebp-F0h]
  double v110; // [esp+1A4h] [ebp-E8h]
  double v111; // [esp+1BCh] [ebp-D0h]
  char *v112; // [esp+1C4h] [ebp-C8h]
  char *v113; // [esp+1C8h] [ebp-C4h]
  int v114; // [esp+1CCh] [ebp-C0h] BYREF
  int v115; // [esp+1D0h] [ebp-BCh] BYREF
  int v116; // [esp+1D4h] [ebp-B8h] BYREF
  char *v117; // [esp+1D8h] [ebp-B4h]
  int v118; // [esp+1DCh] [ebp-B0h] BYREF
  char *v119; // [esp+1E0h] [ebp-ACh]
  int v120; // [esp+1E4h] [ebp-A8h] BYREF
  int v121; // [esp+1E8h] [ebp-A4h] BYREF
  unsigned int v122; // [esp+1ECh] [ebp-A0h] BYREF
  int v123; // [esp+1F0h] [ebp-9Ch] BYREF
  int v124; // [esp+1F4h] [ebp-98h] BYREF
  int v125; // [esp+1F8h] [ebp-94h] BYREF
  int v126; // [esp+1FCh] [ebp-90h] BYREF
  int v127; // [esp+200h] [ebp-8Ch] BYREF
  _DWORD *v128; // [esp+204h] [ebp-88h]
  int v129; // [esp+208h] [ebp-84h] BYREF
  int v130; // [esp+20Ch] [ebp-80h] BYREF
  int v131; // [esp+210h] [ebp-7Ch] BYREF
  int v132; // [esp+214h] [ebp-78h] BYREF
  char *v133; // [esp+218h] [ebp-74h]
  int v134; // [esp+21Ch] [ebp-70h]
  _DWORD *v135; // [esp+220h] [ebp-6Ch]
  int v136; // [esp+224h] [ebp-68h]
  int v137; // [esp+228h] [ebp-64h] BYREF
  int v138; // [esp+22Ch] [ebp-60h]
  char *v139; // [esp+230h] [ebp-5Ch]
  __int16 *v140; // [esp+234h] [ebp-58h]
  __int16 *v141; // [esp+238h] [ebp-54h]
  float *v142; // [esp+23Ch] [ebp-50h]
  __int16 *v143; // [esp+240h] [ebp-4Ch]
  char *v144; // [esp+244h] [ebp-48h]
  char *v145; // [esp+248h] [ebp-44h]
  char *v146; // [esp+24Ch] [ebp-40h]
  char *v147; // [esp+250h] [ebp-3Ch]
  int v148; // [esp+254h] [ebp-38h]
  unsigned int v149; // [esp+258h] [ebp-34h]
  unsigned int v150; // [esp+25Ch] [ebp-30h]
  float *v151; // [esp+260h] [ebp-2Ch]
  unsigned int v152; // [esp+264h] [ebp-28h]
  int *v153; // [esp+268h] [ebp-24h]
  unsigned int v154; // [esp+26Ch] [ebp-20h]
  int *v155; // [esp+270h] [ebp-1Ch]
  unsigned int v156; // [esp+274h] [ebp-18h]

  v128 = result;
  v148 = a2;
  v2 = (int)&BuildingAngles;
  v153 = &BuildingBase;
  v151 = (float *)&BuildingAngles;
  v155 = TowerBase;
  v134 = 0;
  v122 = 0;
  NumBuildings = 0;
  NumTowers = 0;
  v3 = 0;
  if (numcars > 0) {
    v4 = Car;
    do {
      result = (_DWORD *)memset(v4, 0, 308);
      ++v3;
      v2 = numcars;
      v4 += 77;
    } while (v3 < numcars);
  }
  v135 = 0;
  if ((unsigned int)v128 <= 0x18) {
    v5 = fopen(*(&names + (_DWORD)v128), aR_1);
    if (!v5) {
      __asm { int     10h; -VIDEO - SET VIDEO MODE }
      printf(&a0TrackDNotFoun[2]);
      doexit();
    }
    fclose(v5);
    v6 = getcompactedfilelength((int)*(&names + (_DWORD)v128), v5, v2, 0);
    v7 = v6;
    if ((unsigned __int16)v6 == 8224) {
      v8 = open(*(&names + (_DWORD)v128), 0);
      v9 = filelength(v8, v8, v7);
      v10 = v9;
      v11 = v9;
      close(HIDWORD(v9), HIDWORD(v9));
      if (v148)
        v12 = scrbuf;
      else
        v12 = getbuffer(v10 + 1);
      v122 = v12;
      v129 = v12;
      v2 = 1;
      v135 = (_DWORD *)fopen(*(&names + (_DWORD)v128), aRb);
      fread(v122, v11, 1, v135);
      result = 0;
      v134 = 0;
      *(_BYTE *)(v122 + v11) = 26;
    } else {
      if (v148)
        v13 = scrbuf;
      else
        v13 = getbuffer(v6 + 1);
      v122 = v13;
      v129 = v13;
      loadcompactedfile((int)*(&names + (_DWORD)v128), v13);
      result = (_DWORD *)fopen(*(&names + (_DWORD)v128), aR_1);
      *(_BYTE *)(v122 + v7) = 26;
      v2 = -1;
      v135 = result;
      v134 = -1;
    }
  }
  meof = 0;
  if ((int)v128 >= 0)
    result = (_DWORD *)readline2(&v129, &aIddd[1], &TRAK_LEN, &v97, &v96, &v95);
  v14 = 0;
  v15 = 0;
  TrackFlags = 0;
  if (TRAK_LEN > 0) {
    v119 = (char *)&TrakColour + 4;
    v146 = (char *)&TrakColour + 8;
    v147 = (char *)&TrakColour + 12;
    v150 = 0;
    v152 = 0;
    v145 = (char *)&TrakColour + 16;
    v156 = 0;
    v154 = 0;
    v139 = (char *)&TrakColour + 20;
    v138 = 11;
    v142 = GroundLevel;
    v113 = (char *)&GroundColour + 4;
    v140 = samplemax;
    v143 = samplespeed;
    v112 = (char *)&GroundColour + 8;
    v141 = samplemin;
    v133 = (char *)&GroundColour + 12;
    v16 = 0;
    v17 = 0;
    v117 = (char *)&GroundColour + 16;
    v149 = 0;
    v144 = &HorizonColour;
    v110 = loadtrak_c_variable_38 / loadtrak_c_variable_39;
    do {
      if ((int)v128 >= 0) {
        v18 = (char *)&GroundColour + v154;
        GroundLevel[v149 / 4] = 0.0;
        v63 = v141;
        samplemin[v15] = 0;
        samplemax[v15] = 0;
        samplespeed[v15] = 0;
        readline2(
          &v129,
          &aRacddddddddddd[3],
          &v94,
          &v93,
          &v92,
          &v91,
          &v90,
          &v89,
          &v88,
          &v87,
          &v86,
          &v85,
          &v84,
          &v83,
          &v82,
          &v81,
          &v137,
          &v114,
          &v116,
          &v80,
          v142,
          v140,
          v143,
          v63);
        readline2(
          &v129,
          &aKiiiiiiiiiiiii[1],
          (char *)&TrakColour + v17 * 4,
          v119,
          v146,
          v147,
          v145,
          v139,
          v18,
          v113,
          v112,
          v133,
          v117,
          v144,
          &v126,
          &v125,
          &v124,
          &v123,
          &v131,
          &v130);
        v20 = v138;
        v21 = 11 * v15;
        do {
          ++v21;
          *((_BYTE *)&meof_variable_1 + v21) = 0;
        } while (v21 != v20);
        v19 = 11 * v15;
        readline2(
          &v129,
          &aTddddddddddddd[1],
          &v79,
          &v78,
          &v77,
          &v76,
          &v75,
          &v74,
          &v73,
          &v72,
          &v71,
          &v70,
          &v69,
          &v68,
          &v67,
          &v132,
          &v127,
          &v118,
          &Subdivide[v19],
          &Subdivide[v19 + 1],
          &Subdivide[v19 + 2],
          &Subdivide[v19 + 3],
          &Subdivide[v19 + 4],
          &Subdivide[v19 + 5],
          &Subdivide[v19 + 6],
          &Subdivide[v19 + 7],
          &Subdivide[v19 + 8],
          &Subdivide[v19 + 9],
          &Subdivide[v19 + 10],
          &v115,
          &v120,
          &v121);
        if (v148) {
          v93 = v93 * loadtrak_c_variable_40;
          v92 = v92 * loadtrak_c_variable_40;
        }
        if ((cheat_mode & 0x1000) != 0 && !v148) {
          v94 = v94 * loadtrak_c_variable_40;
          v93 = v93 * loadtrak_c_variable_40;
          v92 = v92 * loadtrak_c_variable_40;
          v91 = v91 * loadtrak_c_variable_40;
          v90 = v90 * loadtrak_c_variable_40;
          v89 = v89 * loadtrak_c_variable_40;
          v88 = v88 * loadtrak_c_variable_40;
          v84 = v84 * loadtrak_c_variable_40;
          v83 = v83 * loadtrak_c_variable_40;
          v82 = v82 * loadtrak_c_variable_40;
          v81 = v81 * loadtrak_c_variable_40;
          v79 = v79 * loadtrak_c_variable_40;
          v78 = v78 * loadtrak_c_variable_40;
          v77 = v77 * loadtrak_c_variable_40;
          v76 = v76 * loadtrak_c_variable_40;
          v75 = v75 * loadtrak_c_variable_40;
          v74 = v74 * loadtrak_c_variable_40;
          v73 = v73 * loadtrak_c_variable_40;
          v72 = v72 * loadtrak_c_variable_40;
          v71 = v71 * loadtrak_c_variable_40;
          v70 = v70 * loadtrak_c_variable_40;
          v69 = v69 * loadtrak_c_variable_40;
          v68 = v68 * loadtrak_c_variable_40;
          v67 = v67 * loadtrak_c_variable_40;
          v124 *= 2;
          v22 = GroundLevel[v149 / 4] * loadtrak_c_variable_41;
          v125 *= 2;
          GroundLevel[v149 / 4] = v22;
        }
        v23 = 0;
        v24 = 0;
        v25 = 11 * v15;
        do {
          if (!Subdivide[v25] && (unsigned int)v23 <= 0xA)
            __asm { jmp     cs : off_4AF00[ebx]; jumptable 0004BC6D case 257 }
          v24 += 4;
          ++v23;
          ++v25;
        } while (v23 <= 10);
        if (v132 < 8)
          v132 = 32;
        if (v132 > 128)
          v132 = 32;
        TrakView_variable_1[v150] = v132;
        if (v127 < 0 || v127 > TRAK_LEN || v118 < 8 || v118 > 128) {
          v127 = -1;
          v118 = 0;
        }
        v26 = v150;
        TrakView[v150 / 2] = v127;
        v27 = v115;
        TrakView_variable_2[v26] = v118;
        if (v27 < 8)
          v115 = 32;
        if (v115 > 128)
          v115 = 32;
        v28 = v120;
        TrakView_variable_4[v150] = v115;
        if (v28 < 0 || v28 > TRAK_LEN || v121 < 8 || v121 > 128) {
          v120 = -1;
          v121 = 0;
        }
        v29 = v150;
        TrakView_variable_3[v150 / 2] = v120;
        TrakView_variable_5[v29] = v121;
      }
      if (TrakColour_variable_10[v17] == -1)
        TrakColour_variable_10[v17] = 0;
      if (TrakColour_variable_11[v17] == -1)
        TrakColour_variable_11[v17] = 0;
      if (!v15) {
        v102 = v87;
        v101 = v86;
      }
      v104 = v87;
      v99 = v102;
      if (v87 - v102 > loadtrak_c_variable_45)
        v104 = v87 + loadtrak_c_variable_46;
      if (v104 - v99 < loadtrak_c_variable_47)
        v104 = v104 + loadtrak_c_variable_48;
      v105 = v104 - v99;
      if (v105 > loadtrak_c_variable_45)
        v105 = v105 + loadtrak_c_variable_46;
      if (v105 < loadtrak_c_variable_47)
        v105 = v105 + loadtrak_c_variable_48;
      v108 = v105 * loadtrak_c_variable_42 + v102;
      v103 = v86;
      v98 = v101;
      if (v86 - v101 > loadtrak_c_variable_45)
        v103 = v86 + loadtrak_c_variable_46;
      if (v103 - v98 < loadtrak_c_variable_47)
        v103 = v103 + loadtrak_c_variable_48;
      v106 = v103 - v98;
      if (v106 > loadtrak_c_variable_45)
        v106 = v106 + loadtrak_c_variable_46;
      if (v106 < loadtrak_c_variable_47)
        v106 = v106 + loadtrak_c_variable_48;
      v107 = v106 * loadtrak_c_variable_42 + v101;
      if (v126 != -1) {
        if (v126 < 256) {
          v35 = v153 + 1;
          *v153 = v126;
          *v35 = v15;
          v35[1] = v125;
          v36 = v35 + 2;
          v35[2] = v124;
          v37 = v151;
          *v151 = (float)v123;
          v37[1] = (float)v131;
          v153 = v36 + 1;
          ++v37;
          ++NumBuildings;
          v151 = v37 + 2;
          v37[1] = (float)v130;
        } else {
          *v155++ = v15;
          v30 = v155;
          *v155 = v125;
          v30[1] = v124;
          v31 = v30 + 1;
          v32 = v31 + 1;
          v155 = v31 + 1;
          switch (v126 & 0xFF0F) {
            case 0x101:
              v155 = v31 + 2;
              *v32 = -4;
              break;
            case 0x103:
              v155 = v31 + 2;
              *v32 = -2;
              break;
            case 0x104:
              v155 = v31 + 2;
              *v32 = -5;
              break;
            case 0x105:
              v155 = v31 + 2;
              *v32 = -3;
              break;
            default:
              v33 = v155 + 1;
              *v155 = -1;
              v155 = v33;
              break;
          }
          v34 = v155;
          *v155 = (v126 - 256 - (__CFSHL__((v126 - 256) >> 31, 4) + 16 * ((v126 - 256) >> 31))) >> 4;
          v155 = v34 + 1;
          ++NumTowers;
        }
      }
      rotatepoint(0.0, v94 + v93, v90, v108, v107, v85, (int)v66, (int)v65, (int)&v64);
      setpoint(v97 + *(double *)v66, v96 + *(double *)v65, v95 + v64);
      rotatepoint(0.0, v94 + v93, 0.0, v108, v107, v85, (int)v66, (int)v65, (int)&v64);
      setpoint(v97 + *(double *)v66, v96 + *(double *)v65, v95 + v64);
      rotatepoint(0.0, v93, 0.0, v108, v107, v85, (int)v66, (int)v65, (int)&v64);
      setpoint(v97 + *(double *)v66, v96 + *(double *)v65, v95 + v64);
      rotatepoint(0.0, -v92, 0.0, v108, v107, v85, (int)v66, (int)v65, (int)&v64);
      setpoint(v97 + *(double *)v66, v96 + *(double *)v65, v95 + v64);
      rotatepoint(0.0, -v92 - v91, v89, v108, v107, v85, (int)v66, (int)v65, (int)&v64);
      setpoint(v97 + *(double *)v66, v96 + *(double *)v65, v95 + v64);
      rotatepoint(0.0, -v92 - v91, 0.0, v108, v107, v85, (int)v66, (int)v65, (int)&v64);
      setpoint(v97 + *(double *)v66, v96 + *(double *)v65, v95 + v64);
      if (!v148) {
        if (GroundColour_variable_4[v154 / 4] == -2) {
          v71 = -v90;
          v77 = v94;
          v76 = v91;
          v70 = -v89;
        }
        if (*(int *)((char *)&TrakColour + v17 * 4) < 0) {
          v77 = v94;
          v71 = 0.0;
        }
        if (*(int *)((char *)&TrakColour_variable_7 + v17 * 4) < 0) {
          v76 = v91;
          v70 = 0.0;
        }
        v111 = v79 + v78;
        v100 = v73 + v72;
        v38 = GroundColour_variable_4[v154 / 4];
        v109 = v111 + v77 + v93;
        if (v38 == -2) {
          rotatepoint(0.0, v109, v100 - v71, v108, v107, v85, (int)v66, (int)v65, (int)&v64);
          setgpoint(v97 + *(double *)v66, v96 + *(double *)v65, v95 + v64);
          rotatepoint(0.0, v78 + v77 + v93, v72 - v71, v108, v107, v85, (int)v66, (int)v65, (int)&v64);
          setgpoint(v97 + *(double *)v66, v96 + *(double *)v65, v95 + v64);
          rotatepoint(0.0, v77 + v93, -v71, v108, v107, v85, (int)v66, (int)v65, (int)&v64);
          setgpoint(v97 + *(double *)v66, v96 + *(double *)v65, v95 + v64);
          rotatepoint(0.0, -v76 - v92, -v70, v108, v107, v85, (int)v66, (int)v65, (int)&v64);
          setgpoint(v97 + *(double *)v66, v96 + *(double *)v65, v95 + v64);
          rotatepoint(0.0, -v75 - v76 - v92, v69 - v70, v108, v107, v85, (int)v66, (int)v65, (int)&v64);
          setgpoint(v97 + *(double *)v66, v96 + *(double *)v65, v95 + v64);
          rotatepoint(0.0, -v74 - v75 - v76 - v92, v68 + v69 - v70, v108, v107, v85, (int)v66, (int)v65, (int)&v64);
          setgpoint(v97 + *(double *)v66, v96 + *(double *)v65, v95 + v64);
        } else {
          rotatepoint(0.0, v109, v100 + v71, v108, v107, 0.0, (int)v66, (int)v65, (int)&v64);
          setgpoint(v97 + *(double *)v66, v96 + *(double *)v65, v64);
          rotatepoint(0.0, v78 + v77 + v93, v72 + v71, v108, v107, 0.0, (int)v66, (int)v65, (int)&v64);
          setgpoint(v97 + *(double *)v66, v96 + *(double *)v65, v64);
          rotatepoint(0.0, v77 + v93, v71, v108, v107, 0.0, (int)v66, (int)v65, (int)&v64);
          setgpoint(v97 + *(double *)v66, v96 + *(double *)v65, v64);
          rotatepoint(0.0, -v76 - v92, v70, v108, v107, 0.0, (int)v66, (int)v65, (int)&v64);
          setgpoint(v97 + *(double *)v66, v96 + *(double *)v65, v64);
          rotatepoint(0.0, -v75 - v76 - v92, v69 + v70, v108, v107, 0.0, (int)v66, (int)v65, (int)&v64);
          setgpoint(v97 + *(double *)v66, v96 + *(double *)v65, v64);
          rotatepoint(0.0, -v74 - v75 - v76 - v92, v68 + v69 + v70, v108, v107, 0.0, (int)v66, (int)v65, (int)&v64);
          setgpoint(v97 + *(double *)v66, v96 + *(double *)v65, v64);
        }
        if (TrakColour_variable_10[v17] >= 0) {
          rotatepoint(0.0, v93 + v94, v67 + v90, v108, v107, v85, (int)v66, (int)v65, (int)&v64);
        } else {
          v90 = 0.0;
          rotatepoint(0.0, v93, v67, v108, v107, v85, (int)v66, (int)v65, (int)&v64);
        }
        setpoint(v97 + *(double *)v66, v96 + *(double *)v65, v95 + v64);
        if (TrakColour_variable_11[v17] >= 0) {
          rotatepoint(0.0, -v92 - v91, v67 + v89, v108, v107, v85, (int)v66, (int)v65, (int)&v64);
        } else {
          v89 = 0.0;
          rotatepoint(0.0, -v92, v67, v108, v107, v85, (int)v66, (int)v65, (int)&v64);
        }
        v39 = setpoint(v97 + *(double *)v66, v96 + *(double *)v65, v95 + v64);
        *(float *)&TrackInfo[v16] = v94;
        TrackInfo_variable_1[v16] = v90;
        *(float *)&TrackInfo_variable_2[v16] = v91;
        TrackInfo_variable_3[v16] = v89;
        TrackInfo_variable_8[v16] = v67;
        v40 = v110;
        v41 = atan2(v90 / v94, 1.0) * loadtrak_c_variable_43 * v110;
        _CHP(v39, 5);
        v136 = (int)v41;
        v42 = v89 / v91;
        v43 = v136;
        TrackInfo_variable_4[v16] = v136;
        v44 = v40 * (atan2(v42, 1.0) * loadtrak_c_variable_43);
        _CHP(v43, 5);
        v136 = (int)v44;
        v45 = v84;
        TrackInfo_variable_5[v16] = v136;
        v46 = v152;
        *(float *)&localdata_variable_8[v152 / 4] = v45;
        *(float *)((char *)&localdata_variable_9 + v46) = v83;
        *(float *)((char *)&localdata_variable_10 + v46) = v82;
        *(float *)((char *)&localdata_variable_11 + v46) = v81;
        v47 = v152;
        localdata_variable_12[v152 / 4] = v137;
        v48 = v80;
        *(int *)((char *)localdata_variable_13 + v47) = v114;
        *(int *)((char *)localdata_variable_14 + v47) = v116;
        v49 = v154;
        TrackInfo_variable_6[v16] = -100;
        *(float *)((char *)localdata_variable_15 + v47) = v48;
        v50 = *(int *)((char *)GroundColour_variable_4 + v49);
        TrackInfo_variable_7[v16] = -100;
        if (v50 != -2) {
          TrackInfo_variable_6[v16] = 0;
          TrackInfo_variable_7[v16] = 0;
        }
        if (GroundPt_variable_3[v156 / 4] >= (double)GroundPt_variable_4[v156 / 4]
          && !TrakColour_variable_10[v17]
          && GroundColour_variable_4[v154 / 4] == -2) {
          TrackInfo_variable_6[v16] = 1;
        }
        if (GroundPt_variable_6[v156 / 4] >= (double)GroundPt_variable_5[v156 / 4]
          && !TrakColour_variable_11[v17]
          && GroundColour_variable_4[v154 / 4] == -2) {
          TrackInfo_variable_7[v16] = 1;
        }
        if (GroundPt_variable_3[v156 / 4] < (double)GroundPt_variable_4[v156 / 4]
          && !TrakColour_variable_10[v17]
          && GroundColour_variable_4[v154 / 4] == -2) {
          TrackInfo_variable_6[v16] = 2;
        }
        if (GroundPt_variable_6[v156 / 4] < (double)GroundPt_variable_5[v156 / 4]
          && !TrakColour_variable_11[v17]
          && GroundColour_variable_4[v154 / 4] == -2) {
          TrackInfo_variable_7[v16] = 2;
        }
        if (TrakColour_variable_10[v17] > 0
          && GroundPt_variable_3[v156 / 4] >= (double)GroundPt_variable_4[v156 / 4]
          && GroundColour_variable_4[v154 / 4] == -2) {
          TrackInfo_variable_6[v16] = 3;
        }
        if (TrakColour_variable_11[v17] > 0
          && GroundPt_variable_6[v156 / 4] >= (double)GroundPt_variable_5[v156 / 4]
          && GroundColour_variable_4[v154 / 4] == -2) {
          TrackInfo_variable_7[v16] = 3;
        }
        if (TrakColour_variable_10[v17] > 0
          && GroundPt_variable_3[v156 / 4] < (double)GroundPt_variable_4[v156 / 4]
          && GroundColour_variable_4[v154 / 4] == -2) {
          TrackInfo_variable_6[v16] = 4;
        }
        if (TrakColour_variable_11[v17] > 0
          && GroundPt_variable_6[v156 / 4] < (double)GroundPt_variable_5[v156 / 4]
          && GroundColour_variable_4[v154 / 4] == -2) {
          TrackInfo_variable_7[v16] = 4;
        }
        if (TrakColour_variable_10[v17] < 0
          && GroundPt_variable_3[v156 / 4] >= (double)GroundPt_variable_4[v156 / 4]
          && GroundColour_variable_4[v154 / 4] == -2) {
          TrackInfo_variable_6[v16] = 5;
        }
        if (TrakColour_variable_11[v17] < 0
          && GroundPt_variable_6[v156 / 4] >= (double)GroundPt_variable_5[v156 / 4]
          && GroundColour_variable_4[v154 / 4] == -2) {
          TrackInfo_variable_7[v16] = 5;
        }
        if (TrakColour_variable_10[v17] < 0
          && GroundPt_variable_3[v156 / 4] < (double)GroundPt_variable_4[v156 / 4]
          && GroundColour_variable_4[v154 / 4] == -2) {
          TrackInfo_variable_6[v16] = 6;
        }
        if (TrakColour_variable_11[v17] < 0
          && GroundPt_variable_6[v156 / 4] < (double)GroundPt_variable_5[v156 / 4]
          && GroundColour_variable_4[v154 / 4] == -2) {
          TrackInfo_variable_7[v16] = 6;
        }
        if (GroundColour_variable_4[v154 / 4] == -1 && TrakColour_variable_10[v17] > 0)
          TrackInfo_variable_6[v16] = 7;
        if (GroundColour_variable_4[v154 / 4] == -1 && TrakColour_variable_11[v17] > 0)
          TrackInfo_variable_7[v16] = 7;
        if (GroundColour_variable_4[v154 / 4] >= 0 && TrakColour_variable_10[v17] > 0)
          TrackInfo_variable_6[v16] = 8;
        if (GroundColour_variable_4[v154 / 4] >= 0 && TrakColour_variable_11[v17] > 0)
          TrackInfo_variable_7[v16] = 8;
        if (GroundColour_variable_4[v154 / 4] == -1 && TrakColour_variable_10[v17] < 0)
          TrackInfo_variable_6[v16] = 9;
        if (GroundColour_variable_4[v154 / 4] == -1 && TrakColour_variable_11[v17] < 0)
          TrackInfo_variable_7[v16] = 9;
        v51 = TrackInfo_variable_6[v16];
        if ((!v51 || v51 == 2) && ((unsigned int)&unk_100000 & abs32(*(_DWORD *)((char *)&TrakColour + v17 * 4))) == 0)
          TrackInfo_variable_6[v16] = 1;
        v52 = TrackInfo_variable_7[v16];
        if ((!v52 || v52 == 2)
          && ((unsigned int)&unk_100000 & abs32(*(_DWORD *)((char *)&TrakColour_variable_7 + v17 * 4))) == 0) {
          TrackInfo_variable_7[v16] = 1;
        }
        v53 = TrackInfo_variable_6[v16];
        if ((v53 == 6 || v53 == 9)
          && ((unsigned int)&unk_100000 & abs32(*(_DWORD *)((char *)&TrakColour + v17 * 4))) == 0) {
          TrackInfo_variable_6[v16] = 5;
        }
        v54 = TrackInfo_variable_7[v16];
        if ((v54 == 6 || v54 == 9)
          && ((unsigned int)&unk_100000 & abs32(*(_DWORD *)((char *)&TrakColour_variable_7 + v17 * 4))) == 0) {
          TrackInfo_variable_7[v16] = 5;
        }
        if ((abs32(TrakColour_variable_10[v17]) & 0x20000) != 0) {
          switch (TrackInfo_variable_6[v16]) {
            case 3:
            case 5:
              TrackInfo_variable_6[v16] = 1;
              break;
            case 4:
            case 6:
              TrackInfo_variable_6[v16] = 2;
              break;
            case 7:
            case 8:
            case 9:
              TrackInfo_variable_6[v16] = 0;
              break;
            default:
              break;
          }
        }
        if ((abs32(TrakColour_variable_11[v17]) & 0x20000) != 0) {
          switch (TrackInfo_variable_7[v16]) {
            case 3:
            case 5:
              TrackInfo_variable_7[v16] = 1;
              break;
            case 4:
            case 6:
              TrackInfo_variable_7[v16] = 2;
              break;
            case 7:
            case 8:
            case 9:
              TrackInfo_variable_7[v16] = 0;
              break;
            default:
              break;
          }
        }
      }
      v55 = cos(loadtrak_c_variable_44 * v86);
      v17 += 6;
      v16 += 9;
      ++v15;
      v119 += 24;
      v97 = cos(loadtrak_c_variable_44 * v87) * (v55 * v88) + v97;
      v146 += 24;
      v147 += 24;
      v139 += 24;
      v113 += 20;
      v112 += 20;
      v117 += 20;
      ++v142;
      ++v140;
      v102 = v87;
      ++v141;
      v96 = v55 * v88 * sin(loadtrak_c_variable_44 * v87) + v96;
      v144 += 4;
      v101 = v86;
      v149 += 4;
      v138 += 11;
      v145 += 24;
      v2 = v156 + 72;
      v14 = v154 + 20;
      v133 += 20;
      v152 += 128;
      ++v143;
      v156 += 72;
      v154 += 20;
      v150 += 8;
      result = (_DWORD *)TRAK_LEN;
      v95 = sin(loadtrak_c_variable_44 * v86) * v88 + v95;
    } while (v15 < TRAK_LEN);
  }
  if (!v148)
    result = (_DWORD *)ReadAnimData(v135, &v129);
  if (v148) {
    if ((int)v128 >= 0)
      result = (_DWORD *)min_skip_stuff(&v129);
  } else {
    v56 = initlocaltrack();
    inited = InitTowers(v56);
    v58 = InitBuildings(inited);
    placecars(v58);
    if ((int)v128 >= 0) {
      start_f = v129;
      readstuntdata(&v129);
      read_texturemap(&v129);
      read_bldmap(&v129);
      read_backs(&v129);
    }
    if (Play_View == 1)
      testteaminit((int)&Car[77 * ViewType[0]]);
    else
      initcarview(ViewType[0], 0);
    if (player_type == 2)
      initcarview(ViewType_variable_1, 1);
    result = (_DWORD *)initpits();
  }
  if ((int)v128 >= 0) {
    readline2(&v129, &aTi[1], &actualtrack);
    if (v134 && replaytype != 2 && v128 != (_DWORD *)actualtrack && !v148) {
      __asm { int     10h; -VIDEO - SET VIDEO MODE }
      printf(aCheatTrackDIsR);
      doexit();
    }
    cur_laps[0] = 0;
    if (!meof) {
      readline2(
        &v129,
        &aTiiiiii[2],
        cur_laps,
        &cur_laps_variable_1,
        &cur_laps_variable_2,
        &cur_laps_variable_3,
        &cur_laps_variable_4,
        &cur_laps_variable_5);
      readline2(&v129, &aKfif[1], &cur_mapsize, &cur_mapsect, &cur_TrackZ);
    }
    if (meof) {
      v59 = 0;
      v60 = 6 * actualtrack;
      do {
        ++v59;
        v2 = track_laps[v60++];
        samplemin_variable_1[v59] = v2;
      } while (v59 < 6);
      cur_mapsize = mapsize[actualtrack];
      v61 = TrackZs[actualtrack];
      cur_mapsect = mapsect[actualtrack];
      cur_TrackZ = v61;
    }
    result = (_DWORD *)fclose(v135);
  }
  if (!v148) {
    if (v122)
      result = fre(&v122);
    if ((int)v128 >= 0) {
      v62 = activatestunts(result);
      LODWORD(v62) = LoadBldTextures(v62, SHIDWORD(v62), v2, v14);
      return (_DWORD *)LoadTextures(v62, SHIDWORD(v62), v2);
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int read_backs(int *a1, int a2, int a3, int a4)
{
  return 0; /*
  int v5; // ecx
  int v6; // esi
  int result; // eax
  int v8; // edi
  unsigned int v9; // [esp+0h] [ebp-1Ch] BYREF
  _DWORD v10[6]; // [esp+4h] [ebp-18h] BYREF

  v10[4] = a4;
  v5 = 0;
  v6 = 0;
  do {
    if (v6) {
      result = readline2(a1, &loadtrak_c_variable_49, &v9, v10);
      if (v9 < 0x100) {
        result = v10[0];
        texture_back[v9] = v10[0];
      } else {
        v5 = -1;
      }
    } else {
      v8 = *a1;
      memgets(&fp_buf, a1);
      result = *a1;
      if (v8 == *a1)
        return result;
      if (fp_buf == 66
        && fp_buf_variable_1 == 65
        && fp_buf_variable_2 == 67
        && fp_buf_variable_3 == 75
        && fp_buf_variable_4 == 83) {
        v6 = -1;
      }
    }
  } while (!v5);
  return result;*/
}

//-------------------------------------------------------------------------------------------------

char *read_texturemap(int a1)
{
  return 0; /*
  char *v2; // eax
  char v3; // dh
  char *result; // eax
  int v5; // edx
  char v6; // bl

  do
    memgets(&fp_buf, a1);
  while (fp_buf != 84);
  v2 = &fp_buf;
  do
    v3 = *++v2;
  while (v3 != 58);
  result = v2 + 1;
  v5 = 0;
  do {
    v6 = *result++;
    texture_file[v5] = v6;
    if ((unsigned __int8)v6 >= 0x61u && (unsigned __int8)v6 <= 0x7Au)
      texture_file[v5] = v6 - 32;
    ++v5;
  } while (*result != 13 && *result != 10);
  texture_file[v5] = 0;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

char *read_bldmap(char **a1)
{
  return 0; /*
  char *v2; // ebp
  int v3; // ecx
  char *v4; // esi
  char *result; // eax
  char *v6; // eax
  char v7; // dh
  int v8; // edx
  char v9; // cl

  v2 = *a1;
  v3 = 0;
  *a1 = (char *)start_f;
  do {
    v4 = *a1;
    memgets(&fp_buf, a1);
    result = *a1;
    if (v4 == *a1)
      v3 = -1;
    if (fp_buf == 66 && fp_buf_variable_1 == 76 && fp_buf_variable_2 == 68)
      v3 = -1;
  } while (!v3);
  if (fp_buf == 66 && fp_buf_variable_1 == 76 && fp_buf_variable_2 == 68) {
    v6 = &fp_buf;
    if (fp_buf != 58) {
      do
        v7 = *++v6;
      while (v7 != 58);
    }
    result = v6 + 1;
    v8 = 0;
    do {
      v9 = *result++;
      bldtex_file[v8] = v9;
      if ((unsigned __int8)v9 >= 0x61u && (unsigned __int8)v9 <= 0x7Au)
        bldtex_file[v8] = v9 - 32;
      ++v8;
    } while (*result != 13 && *result != 10);
    bldtex_file[v8] = 0;
  } else {
    strcpy(&fp_buf, "building.drh");
  }
  *a1 = v2;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int readstuntdata(int a1, int a2, int a3, int a4)
{
  return 0; /*
  _DWORD *v5; // edx
  int result; // eax
  _DWORD *v7; // edx
  int v8; // [esp+0h] [ebp-3Ch] BYREF
  int v9; // [esp+4h] [ebp-38h] BYREF
  int v10; // [esp+8h] [ebp-34h] BYREF
  int v11; // [esp+Ch] [ebp-30h] BYREF
  int v12; // [esp+10h] [ebp-2Ch] BYREF
  int v13; // [esp+14h] [ebp-28h] BYREF
  int v14; // [esp+18h] [ebp-24h] BYREF
  int v15; // [esp+1Ch] [ebp-20h] BYREF
  int v16; // [esp+20h] [ebp-1Ch] BYREF
  _DWORD v17[6]; // [esp+24h] [ebp-18h] BYREF

  v17[4] = a4;
  v5 = (_DWORD *)scrbuf;
  totalramps = 0;
  freestunts(a1, scrbuf, a1);
  do {
    result = readline2(a1, &aUuuiiiiiiiiii[3], v17, &v16, &v15, &v14, &v12, &v13, &v11, &v10, &v9, &v8);
    if (v17[0] != -1) {
      v7 = v5 + 1;
      *(v7++ - 1) = v17[0];
      *(v7++ - 1) = v16;
      *(v7++ - 1) = v15;
      *(v7++ - 1) = v14;
      *(v7++ - 1) = v12;
      *(v7++ - 1) = v13;
      *(v7++ - 1) = v11;
      *(v7++ - 1) = v10;
      *(v7 - 1) = v9;
      v5 = v7 + 1;
      result = v8;
      *(v5 - 1) = v8;
    }
  } while (v17[0] != -1);
  *v5 = -1;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void activatestunts()
{/*
  int *v0; // esi
  int v1; // ebp
  int v2; // edi
  int *v3; // esi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // [esp+0h] [ebp-3Ch]
  int v13; // [esp+4h] [ebp-38h]
  int v14; // [esp+Ch] [ebp-30h]
  int v15; // [esp+1Ch] [ebp-20h]
  int v16; // [esp+20h] [ebp-1Ch]

  v0 = (int *)scrbuf;
  v1 = 0;
  totalramps = 0;
  do {
    v2 = *v0++;
    if (v2 == -1) {
      ramp[v1] = 0;
    } else {
      v3 = v0 + 3;
      v4 = *v3++;
      v15 = v4;
      v5 = *v3++;
      v16 = v5;
      v6 = *v3++;
      v13 = v6;
      v7 = *v3++;
      v12 = v7;
      v8 = *v3++;
      v14 = v8;
      v9 = *v3;
      v0 = v3 + 1;
      v10 = initramp(v15, v16, v13, v12, v14, v9);
      v11 = totalramps + 1;
      ramp[v1] = v10;
      totalramps = v11;
    }
    ++v1;
  } while (v2 != -1);*/
}

//-------------------------------------------------------------------------------------------------

int ReadAnimData(int result, int a2)
{
  return 0; /*
  int v2; // [esp+0h] [ebp-14h] BYREF
  int v3[4]; // [esp+4h] [ebp-10h] BYREF

  v2 = 0;
  v3[0] = 0;
  if (result) {
    do {
      readline2(a2, aSs, &v2, v3);
      if ((v2 & 0x8000u) == 0) {
        result = v3[0];
        advert_list[(__int16)v2] = v3[0];
      } else {
        result = (__int16)v2;
        if ((__int16)v2 < -1) {
          result = -(__int16)v2;
          VisibleBuildings_variable_1[-(__int16)v2] = 0;
        }
      }
    } while (SLOWORD(v3[0]) >= 0);
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

void readline(FILE *pFile, const char *szFmt, ...)
{
  char szBuffer[0x200];
  char *szTok;
  va_list args;
  int iFieldIndex = 0;
  char *szDelims = delims;

  va_start(args, szFmt);
  double dScale = 256.0;

  // Skip comments and blank lines
  while (1) {
    if (!fgets(szBuffer, sizeof(szBuffer), pFile)) {
      va_end(args);
      return; // EOF or error
    }

    szTok = strtok(szBuffer, szDelims);
    if (!szTok) continue;

    if (strncmp(szTok, "//", 2) == 0 || strchr(szTok, ';') == szTok) {
      continue;
    }
    break;
  }

  char *szFmtPtr = (char *)szFmt;
  char *szCurrTok = szTok;

  while (*szFmtPtr && szCurrTok) {
    void *pDst = va_arg(args, void *);

    switch (*szFmtPtr) {
      case 'D':
      { // double scaled
        double val = strtod(szCurrTok, NULL) * dScale;
        *(double *)pDst = val;
        break;
      }
      case 'F':
      { // float scaled
        float val = (float)(strtod(szCurrTok, NULL) * dScale);
        *(float *)pDst = val;
        break;
      }
      case 'I':
      { // int shifted
        int val = strtol(szCurrTok, NULL, 10) << 8;
        *(int *)pDst = val;
        break;
      }
      case 'S':
      { // short shifted
        short val = (short)(strtol(szCurrTok, NULL, 10) << 8);
        *(short *)pDst = val;
        break;
      }
      case 'd':
      {
        *(double *)pDst = strtod(szCurrTok, NULL);
        break;
      }
      case 'f':
      {
        *(float *)pDst = (float)strtod(szCurrTok, NULL);
        break;
      }
      case 'i':
      {
        *(int *)pDst = strtol(szCurrTok, NULL, 10);
        break;
      }
      case 's':
      {
        *(short *)pDst = (short)strtol(szCurrTok, NULL, 10);
        break;
      }
      case 'u':
      {
        *(uint8*)pDst = (uint8)strtol(szCurrTok, NULL, 10);
        break;
      }
      case 'C':
      case 'c':
      {
        char *szDest = (char *)pDst;
        const char *szSrc = szCurrTok;
        // Custom wide copy: 2 bytes per char
        while (*szSrc) {
          *szDest++ = *szSrc++;
          if (!*szSrc)
            break;
          *szDest++ = *szSrc++;
        }
        *szDest = '\0';
        break;
      }
    }

    szFmtPtr++;
    szCurrTok = strtok(NULL, szDelims);
    iFieldIndex++;
  }

  va_end(args);
}

//-------------------------------------------------------------------------------------------------

uint8 *memgets(uint8 *pDst, uint8 **ppSrc)
{
  int iEof = 0;
  uint8 *pDstItr = pDst;
  int i = 0;

  while (1) {
    uint8 *pSrc = *ppSrc;
    uint8 byte = *pSrc;
    *pDstItr++ = byte;

    if (byte == 0x1A)  // End-of-input marker
      iEof = -1;

    (*ppSrc)++;  // advance source pointer

    if (byte >= 13) {
      if (!iEof)
        continue;
    }

    if (pDst[0] >= 13)
      continue;

    break;
  }

  meof = iEof;
  return pDst;
}

//-------------------------------------------------------------------------------------------------

void readline2(uint8 **ppFileHandle, const char *pszFormat, ...)
{
  char *pszToken; // ebp
  double dblValue; // st7
  double dblFloatValue; // st7
  char *pDest; // eax
  char **ppArgs; // esi
  int iIntValue; // eax
  uint32 *puiDest; // edx
  int16 nShortValue; // ax
  char **ppArgsDouble; // ebx
  double dblPlainValue; // st7
  double *pdblDest; // eax
  char **ppArgsFloat; // esi
  double dPlainValue; // st7
  float *pfltDest; // eax
  int iPlainValue; // eax
  char **ppArgsShort; // ecx
  int16 nPlainValue; // ax
  int16 *pnDest; // edx
  char *pszSrc; // esi
  char *pszDestStr; // edi
  char byChar1; // al
  char byChar2; // al
  char *pszSrc2; // esi
  char *pszDest2; // edi
  char **ppArgsNext; // ebx
  char byChar3; // al
  char byChar4; // al
  char **ppArgsByte; // esi
  uint8 byByteValue; // al
  uint8 *pbyDest; // edx
  unsigned int uiSavedIndex; // edi
  char szLineBuffer[512]; // [esp+0h] [ebp-220h] BYREF
  char **ppVarArgs; // [esp+200h] [ebp-20h]
  unsigned int uiFormatIndex; // [esp+204h] [ebp-1Ch]
  va_list va; // [esp+22Ch] [ebp+Ch] BYREF

  va_start(va, pszFormat);
  va_copy((va_list)ppVarArgs, va);
  while (1) {
    memgets((uint8 *)szLineBuffer, ppFileHandle);// Read next line from file into buffer
    if (meof)
      break;                                    // Check for end of file
    pszToken = strtok(szLineBuffer, delims);    // Tokenize line using delimiters (whitespace)
    if (strstr(pszToken, "//") == pszToken)   // Skip C++ style comments (//) 
      pszToken = 0;
    if (strstr(pszToken, ";") == pszToken)    // Skip lines starting with semicolon
      pszToken = 0;
    if (szLineBuffer[0] == 10)                // Skip newlines
      pszToken = 0;
    if (szLineBuffer[0] == 13)                // Skip carriage returns
      pszToken = 0;
    if (pszToken) {                                           // Process each format specifier in the format string
      for (uiFormatIndex = 0; strlen(pszFormat) > uiFormatIndex; uiFormatIndex = uiSavedIndex + 1) {                                         // 'D' = double scaled by 256
        if (pszFormat[uiFormatIndex] == 'D') {
          dblValue = strtod(pszToken, 0);
          *(double *)*ppVarArgs++ = dblValue * 256.0;
        }
        if (pszFormat[uiFormatIndex] == 'F')  // 'F' = float scaled by 256
        {
          dblFloatValue = strtod(pszToken, 0);
          pDest = *ppVarArgs++;
          *(float *)pDest = (float)(dblFloatValue * 256.0);
        }
        if (pszFormat[uiFormatIndex] == 'I')  // 'I' = 32-bit integer shifted left by 8
        {
          ppArgs = ppVarArgs + 1;
          iIntValue = strtol(pszToken, 0, 10);
          puiDest = (uint32 *)*(ppArgs - 1);
          ppVarArgs = ppArgs;
          *puiDest = iIntValue << 8;
        }
        if (pszFormat[uiFormatIndex] == 'S')  // 'S' = 16-bit short shifted left by 8
        {
          nShortValue = (int16)strtol(pszToken, 0, 10);
          *(int16 *)*ppVarArgs++ = nShortValue << 8;
        }
        if (pszFormat[uiFormatIndex] == 'd')  // 'd' = double (no scaling)
        {
          ppArgsDouble = ppVarArgs + 1;
          dblPlainValue = strtod(pszToken, 0);
          pdblDest = (double *)*(ppArgsDouble - 1);
          ppVarArgs = ppArgsDouble;
          *pdblDest = dblPlainValue;
        }
        if (pszFormat[uiFormatIndex] == 'f')  // 'f' = float (no scaling)
        {
          ppArgsFloat = ppVarArgs + 1;
          dPlainValue = strtod(pszToken, 0);
          pfltDest = (float *)*(ppArgsFloat - 1);
          ppVarArgs = ppArgsFloat;
          *pfltDest = (float)dPlainValue;
        }
        if (pszFormat[uiFormatIndex] == 'i')  // 'i' = 32-bit integer (no shifting)
        {
          iPlainValue = strtol(pszToken, 0, 10);
          *(int *)*ppVarArgs++ = iPlainValue;
        }
        if (pszFormat[uiFormatIndex] == 's')  // 's' = 16-bit short (no shifting)
        {
          ppArgsShort = ppVarArgs + 1;
          nPlainValue = (int16)strtol(pszToken, 0, 10);
          pnDest = (int16 *)*(ppArgsShort - 1);
          ppVarArgs = ppArgsShort;
          *pnDest = nPlainValue;
        }
        if (pszFormat[uiFormatIndex] == 'C')  // 'C' = copy string (uppercase, likely null-terminated)
        {
          pszSrc = pszToken;
          pszDestStr = *ppVarArgs++;
          do {
            byChar1 = *pszSrc;
            *pszDestStr = *pszSrc;
            if (!byChar1)
              break;
            byChar2 = pszSrc[1];
            pszSrc += 2;
            pszDestStr[1] = byChar2;
            pszDestStr += 2;
          } while (byChar2);
        }
        if (pszFormat[uiFormatIndex] == 'c')  // 'c' = copy string (lowercase)
        {
          pszSrc2 = pszToken;
          pszDest2 = *ppVarArgs;
          ppArgsNext = ppVarArgs + 1;
          do {
            byChar3 = *pszSrc2;
            *pszDest2 = *pszSrc2;
            if (!byChar3)
              break;
            byChar4 = pszSrc2[1];
            pszSrc2 += 2;
            pszDest2[1] = byChar4;
            pszDest2 += 2;
          } while (byChar4);
          ppVarArgs = ppArgsNext;
        }
        if (pszFormat[uiFormatIndex] == 'u')  // 'u' = unsigned byte
        {
          ppArgsByte = ppVarArgs + 1;
          byByteValue = (uint8)strtol(pszToken, 0, 10);
          pbyDest = (uint8 *)*(ppArgsByte - 1);
          ppVarArgs = ppArgsByte;
          *pbyDest = byByteValue;
        }
        uiSavedIndex = uiFormatIndex;
        pszToken = strtok(0, delims);           // Get next token from the line
      }
      return;
    }
  }
}

//-------------------------------------------------------------------------------------------------

double *rotatepoint(
        double a1,
        double a2,
        double a3,
        double a4,
        double a5,
        double a6,
        double *a7,
        double *a8,
        double *a9)
{
  return 0; /*
  long double v9; // st7
  long double v10; // st6
  long double v11; // st5
  double *result; // eax
  double v13; // [esp+8h] [ebp-28h]
  long double v14; // [esp+10h] [ebp-20h]
  double v15; // [esp+18h] [ebp-18h]
  long double v16; // [esp+4Ch] [ebp+1Ch]
  long double v17; // [esp+54h] [ebp+24h]
  long double v18; // [esp+5Ch] [ebp+2Ch]

  v16 = a4 * loadtrak_c_variable_57;
  v17 = a5 * loadtrak_c_variable_57;
  v18 = a6 * loadtrak_c_variable_57;
  v9 = cos(v16);
  v10 = sin(v17);
  v11 = sin(v18);
  v13 = sin(v16);
  v14 = cos(v18);
  v15 = cos(v17);
  *a7 = (v9 * v10 * v11 - v13 * v14) * a2 + a1 * v9 * v15 + (-v9 * v10 * v14 - v13 * v11) * a3;
  *a8 = (v13 * v10 * v11 + v9 * v14) * a2 + a1 * v13 * v15 + (-v13 * v10 * v14 + v9 * v11) * a3;
  result = a9;
  *a9 = v10 * a1 + v11 * (-v15 * a2) + a3 * v15 * v14;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int setpoint(int a1, int a2, double a3, double a4, double a5)
{
  return 0; /*
  int v7; // ebx
  int result; // eax

  v7 = 18 * a1;
  result = 3 * a2;
  TrakPt[result + v7] = a3;
  TrakPt_variable_1[result + v7] = a4;
  TrakPt_variable_2[result + v7] = a5;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int setgpoint(int a1, int a2, double a3, double a4, double a5)
{
  return 0; /*
  int v7; // ebx
  int result; // eax

  v7 = 18 * a1;
  result = 3 * a2;
  GroundPt[result + v7] = a3;
  GroundPt_variable_1[result + v7] = a4;
  GroundPt_variable_2[result + v7] = a5;
  return result;*/
}

//-------------------------------------------------------------------------------------------------

int resetcars()
{
  return 0; /*
  int v0; // esi
  float *v1; // ecx
  int result; // eax

  v0 = 0;
  if (numcars > 0) {
    v1 = Car;
    do {
      result = memset(v1, 0, 308);
      ++v0;
      v1 += 77;
    } while (v0 < numcars);
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------

char *min_skip_stuff(int *a1)
{
  return 0; /*
  _BYTE *result; // eax
  _BYTE v3[256]; // [esp-100h] [ebp-130h] BYREF
  _BYTE v4[4]; // [esp+0h] [ebp-30h] BYREF
  _BYTE v5[4]; // [esp+4h] [ebp-2Ch] BYREF
  _BYTE v6[4]; // [esp+8h] [ebp-28h] BYREF
  _BYTE v7[4]; // [esp+Ch] [ebp-24h] BYREF
  _BYTE v8[4]; // [esp+10h] [ebp-20h] BYREF
  _BYTE v9[4]; // [esp+14h] [ebp-1Ch] BYREF
  _BYTE v10[4]; // [esp+18h] [ebp-18h] BYREF
  _BYTE v11[4]; // [esp+1Ch] [ebp-14h] BYREF
  int v12; // [esp+20h] [ebp-10h] BYREF
  _DWORD v13[3]; // [esp+24h] [ebp-Ch] BYREF

  do {
    do
      readline2(a1, "ii", v13, &v12);
    while (v13[0] != -1);
  } while (v12 != -1);
  do
    readline2(a1, &aUuuiiiiiiiiii[3], v13, &v12, v11, v10, v9, v8, v7, v6, v5, v4);
  while (v13[0] != -1);
  do
    readline2(a1, "c", v3);
  while (!strstr(v3, aBacks));
  do
    result = readline2(a1, "ii", v13, &v12);
  while (v13[0] != -1);
  return result;*/
}

//-------------------------------------------------------------------------------------------------

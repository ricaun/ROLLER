#include "replay.h"
#include "sound.h"
#include "car.h"
#include "3d.h"
#include "moving.h"
#include "func2.h"
#include "roller.h"
#include <string.h>
#include <errno.h>
#ifdef IS_WINDOWS
#include <io.h>
#else
#define _GNU_SOURCE
#include <dirent.h>
#include <fnmatch.h>
#endif
//-------------------------------------------------------------------------------------------------
//symbol names added by ROLLER
char g_szGss[5] = ".GSS";         //000A253C
char g_szNewEdit[10] = "NEW EDIT:"; //000A274C
char g_szEdit[6] = "EDIT:";         //000A2758

//-------------------------------------------------------------------------------------------------

int disciconpressed = 0;  //000A63AC
int rotpoint = 0;         //000A63B0
int replaypanel = -1;     //000A63B4
int controlicon = 9;      //000A63B8
int replayspeeds[9] = { 16, 32, 64, 128, 256, 512, 1024, 2048, 4096 }; //000A63BC
char *replayname[9] = {   //000A63E0
    "1/16",
    "1/8",
    "1/4",
    "1/2",
    "1",
    "2",
    "4",
    "8",
    "16"
};
int lastintro = -1;       //000A6404
int filingmenu = 0;       //000A6408
int filefile = 0;         //000A640C
int filefiles = 0;        //000A6410
int replaysetspeed = 0;   //000A6414
int replaydirection = 0;  //000A6418
int lastfile = -1;        //000A641C
int lastautocut = -1;     //000A6420
int pend_view_init = -1;  //000A6424
int replayedit = 0;       //000A6428
char replayfilename[32] = "INTRO1.GSS"; //000A642C
char *views[8] = {        //000A644C
  "IN CAR",
  "CHASE",
  "MIRROR",
  "BEHIND",
  "CAMERA",
  "ABOVE",
  "BACK",
  "TEAM"
};
int loading_replay = 0;   //000A6470
tRIcon ricon[26] =        //000A6474
{
  { 0, 0, NULL },
  { 7, 5, &Rframeminus },
  { 29, 5, &Rframeplus },
  { 51, 5, &Rreverseplay },
  { 73, 5, &Rplay },
  { 95, 5, &Rspeedminus },
  { 117, 5, &Rspeedplus },
  { 7, 21, &Rstart },
  { 29, 21, NULL },
  { 51, 21, &DoRstop },
  { 95, 21, NULL },
  { 117, 21, &Rend },
  { 7, 37, &carminus },
  { 29, 37, &carplus },
  { 51, 37, &viewminus },
  { 73, 37, &viewplus },
  { 95, 37, &discmenu },
  { 117, 37, &rtoggleedit },
  { 140, 37, &rstartblock },
  { 162, 37, &rselectblock },
  { 184, 37, &rdeleteblock },
  { 206, 37, &rstoreview },
  { 228, 37, &rremoveview },
  { 250, 37, &rpreviouscut },
  { 272, 37, &rnextcut },
  { 294, 37, &rstartassemble }
};
char *replayhelp[26] = {  //000A6544
  "",
  "FRAME|REVERSE",
  "FRAME|FORWARD",
  "REVERSE PLAY",
  "PLAY",
  "DECREASE|PLAY SPEED",
  "INCREASE|PLAY SPEED",
  "GO TO START",
  "REWIND",
  "STOP",
  "FAST FORWARD",
  "GO TO END",
  "SELECT|PREVIOUS CAR",
  "SELECT|NEXT CAR",
  "SELECT|PREVIOUS VIEW",
  "SELECT|NEXT VIEW",
  "FILE|OPERATIONS",
  "SELECT|EDIT MODE",
  "START|BLOCK",
  "SELECT|BLOCK",
  "DESELECT|BLOCK",
  "STORE|NEW CUT",
  "REMOVE|CUT",
  "GO TO|PREVIOUS CUT",
  "GO TO|NEXT CUT",
  "ASSEMBLE|REPLAY"
};
int lsdsel = 0;           //000A646C
tPoint rrotate[8] =       //000A65AC
{
  { 194, 11 },
  { 199, 11 },
  { 203, 15 },
  { 203, 20 },
  { 199, 24 },
  { 194, 24 },
  { 190, 20 },
  { 190, 15 }
};
tReplayCamera camera[100];//00189980
int disabled[4096];       //00189BD8
char temp_names[16][9];   //0018DBD8
char newrepsample[16];    //0018DC68
char repsample[16];       //0018DC78
char repvolume[16];       //0018DC88
int topfile;              //0018DC98
char filename[500][9];    //0018DC9C
int oldtrack;             //0018EE30
int oldtextures;          //0018EE34
int replayheader;         //0018EE38
FILE *replayfile;         //0018EE3C
int replayspeed;          //0018EE40
int oldcars;              //0018EE44
int replayframes;         //0018EE48
int discfull;             //0018EE4C
int replayblock;          //0018EE50
int currentreplayframe;   //0018EE54
int lastreplayframe;      //0018EE58
int introfiles;           //0018EE70
int newreplayframe;       //0018EE5C
int replayselect;         //0018EE60
int slowing;              //0018EE64
int rewinding;            //0018EE68
int forwarding;           //0018EE6C
int replaystart;          //0018EE74
int cuts;                 //0018EE78
char selectfilename[30];  //0018EE80
char rememberfilename[34];//0018EE9E

//-------------------------------------------------------------------------------------------------
//00063DB0
void setreplaytrack()
{
  char *pszRememberFilename; // edi
  char *pszReplayFilename; // esi
  char c1; // al
  char c2; // al
  int iRandValue1; // eax
  int iIntroFileNum1; // eax
  FILE *pFile; // edi
  int iRandValue2; // eax
  int iIntroFileNum2; // eax
  //uint32 iCheatFlags1; // ecx
  //uint32 iCheatFlags2; // ebx
  int *iNonCompetitor; // esi
  int *pReplayNonCompetitor; // eax
  int iByteOffset; // ebp
  int iCarIndex; // esi
  uint8 iCarDesign; // al
  int iNumCarsTemp; // ecx
  int iCarCounter; // [esp+0h] [ebp-20h]
  uint8 buffer[28]; // [esp+4h] [ebp-1Ch] BYREF

  if (replaytype == 2) {
    oldtrack = TrackLoad;                       // Save current game state before loading replay
    oldcars = numcars;
    oldtextures = textures_off;
    if (intro || replayfilename[0] == 73) {
      pszRememberFilename = rememberfilename;   // Copy current filename to remember buffer
      pszReplayFilename = replayfilename;
      do {
        c1 = *pszReplayFilename;
        *pszRememberFilename = *pszReplayFilename;
        if (!c1)
          break;
        c2 = pszReplayFilename[1];
        pszReplayFilename += 2;
        pszRememberFilename[1] = c2;
        pszRememberFilename += 2;
      } while (c2);
      do {
        iRandValue1 = rand();                   // Generate random intro file number (1 to introfiles)
        iIntroFileNum1 = GetHighOrderRand(introfiles, iRandValue1) + 1;
      } while (iIntroFileNum1 == lastintro && introfiles != 1);
      lastintro = iIntroFileNum1;
      sprintf(replayfilename, "INTRO%d.GSS", iIntroFileNum1);
    }
    pFile = fopen(replayfilename, "rb");        // Open the selected intro GSS file
    if (!pFile) {
      do {
        iRandValue2 = rand();                   // Fallback: try different intro file if first failed to open
        iIntroFileNum2 = GetHighOrderRand(introfiles, iRandValue2) + 1;
      } while (iIntroFileNum2 == lastintro);
      lastintro = iIntroFileNum2;
      sprintf(replayfilename, "INTRO%d.GSS", iIntroFileNum2);
      pFile = fopen(replayfilename, "rb");
    }
    if (pFile) {
      fread(buffer, 1u, 1u, pFile);             // Read track number from GSS file
      TrackLoad = buffer[0];
      game_track = buffer[0];
      fread(buffer, 1u, 1u, pFile);             // Read game flags byte from GSS file

      if ((buffer[0] & 0x20) != 0)            // Process texture flag (bit 5 = 0x20)
        textures_off |= TEX_OFF_ADVANCED_CARS;
      else
        textures_off &= ~TEX_OFF_ADVANCED_CARS;
      cheat_mode = 0;

      if ((buffer[0] & 0x40) != 0)            // Process cheat mode flags (bit 6 = 0x40, bit 7 = 0x80)
      {
        cheat_mode |= CHEAT_MODE_DOUBLE_TRACK;
        //iCheatFlags1 = cheat_mode;
        //BYTE1(iCheatFlags1) = BYTE1(cheat_mode) | 0x10;
        //cheat_mode = iCheatFlags1;
      } else {
        cheat_mode &= ~CHEAT_MODE_DOUBLE_TRACK;
        //iCheatFlags2 = cheat_mode;
        //BYTE1(iCheatFlags2) = BYTE1(cheat_mode) & 0xEF;
        //cheat_mode = iCheatFlags2;
      }

      if ((buffer[0] & 0x80u) == 0)
        cheat_mode &= ~CHEAT_MODE_TINY_CARS;
      else
        cheat_mode |= CHEAT_MODE_TINY_CARS;

      iNonCompetitor = non_competitors;
      numcars = buffer[0] & 0x1F;               // Extract number of cars from lower 5 bits (0x1F mask)
      fseek(pFile, 605, 0);                     // Seek to non-competitors data at offset 605
      do {
        pReplayNonCompetitor = iNonCompetitor++;// Read 16 non-competitor entries (4 bytes each)
        fread(pReplayNonCompetitor, 4u, 1u, pFile);
      } while (iNonCompetitor != &non_competitors[16]);
      fread(&racers, 4u, 1u, pFile);            // Read racers data (4 bytes)
      iCarCounter = 0;
      if (numcars > 0) {
        iByteOffset = 0;
        iCarIndex = 0;
        do {
          fread(buffer, 1u, 1u, pFile);         // Read car design index for each car
          iCarDesign = buffer[0];
          Car[iCarIndex].byCarDesignIdx = buffer[0];
          iNumCarsTemp = numcars;
          iByteOffset += 4;
          Drivers_Car[iCarIndex] = iCarDesign;
          ++iCarIndex;
          //*(_DWORD *)&car_texture_names[10][iByteOffset + 252] = iCarDesign;// offset into Drivers_Car
          ++iCarCounter;
        } while (iCarCounter < iNumCarsTemp);
      }
    }
    if (pFile)
      fclose(pFile);                            // Close the GSS file
  }
}

//-------------------------------------------------------------------------------------------------
//00064040
void startreplay()
{
  char *pDestStr; // edi
  const char *pSrcStr; // esi
  char cChar1; // al
  char cChar2; // al
  FILE *pWriteFile; // ecx
  int *pNonCompetitorsWrite; // esi
  int *pCurrentNonCompetitor; // eax
  int iCarWriteCounter; // edi
  int iCarWriteIndex; // esi
  int iDriverNameCounter; // edi
  char *pDriverNamesWrite; // esi
  char *pDriverNamesSrc; // edx
  char *pTempNamesDest; // ebx
  char *pTempPtr1; // edi
  char *pTempPtr2; // esi
  char cTempChar1; // al
  char cTempChar2; // al
  //int iFileHandle; // eax
  //int iFileHandleCopy; // edx
  FILE *pReadFile; // ecx
  //uint32 iCheatFlags1; // edx
  //uint32 iCheatFlags2; // eax
  //uint32 iCheatFlags3; // ecx
  //uint32 iCheatFlags4; // ebx
  int *pNonCompetitorsRead; // esi
  int *pCurrentNonCompetitorRead; // eax
  int iDriverIndex; // ebp
  int iNonCompetitorIndex; // edi
  int iCarArrayIndex; // esi
  uint8 byCarDesignIdx; // al
  int iNonCompetitorValue; // ebx
  double dZCoordinate; // st7
  int iDriverNameIndex; // edi
  char *pDriverNamesRead; // esi
  int iReplayDataIndex; // esi
  char cReplayDataByte; // al
  int iNumCarsLocal; // ebp
  //signed int iCarByteOffset; // eax
  //signed int iTotalCarBytes; // edx
  uint8 replayData[32]; // [esp+0h] [ebp-3Ch] BYREF
  uint8 buffer[28]; // [esp+20h] [ebp-1Ch] BYREF

  oldcars = numcars;                            // Initialize replay state variables
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
  memset(disabled, 255, sizeof(disabled));
  memset(camera, 0, sizeof(camera));
  cuts = 0;
  if (replaytype) {                                             // RECORDING MODE: Set up replay file for writing
    if ((unsigned int)replaytype <= 1) {
      pDestStr = replayfilename;
      pSrcStr = "..\\REPLAYS\\REPLAY.TMP";      // Copy replay temp filename
      discfull = 0;
      do {
        cChar1 = *pSrcStr;
        *pDestStr = *pSrcStr;
        if (!cChar1)
          break;
        cChar2 = pSrcStr[1];
        pSrcStr += 2;
        pDestStr[1] = cChar2;
        pDestStr += 2;
      } while (cChar2);
      pWriteFile = ROLLERfopen(replayfilename, "wb");// Open replay file for writing
      replayfile = pWriteFile;
      if (pWriteFile) {
        buffer[0] = TrackLoad;                  // Write track number to replay file
        fwrite(buffer, 1, 1, pWriteFile);
        buffer[0] = numcars;                    // Write game flags (numcars + texture/cheat flags)
        // TEX_OFF_ADVANCED_CARS
        if ((textures_off & 0x10000) != 0)
          buffer[0] = numcars | 0x20;
        // CHEAT_MODE_DOUBLE_TRACK
        if ((cheat_mode & 0x1000) != 0)
          buffer[0] |= 0x40u;
        // CHEAT_MODE_TINY_CARS
        if ((cheat_mode & 0x8000) != 0)
          buffer[0] |= 0x80u;
        fwrite(buffer, 1, 1, replayfile);
        buffer[0] = (uint8)ViewType[0];                // Write view type and selected view to replay file
        fwrite(buffer, 1, 1, replayfile);
        buffer[0] = SelectedView[0];
        fwrite(buffer, 1, 1, replayfile);
        pNonCompetitorsWrite = non_competitors;
        fwrite(camera, 6, 100, replayfile);     // Write camera data and cuts to replay file
        buffer[0] = cuts;
        fwrite(buffer, 1, 1, replayfile);
        do {
          pCurrentNonCompetitor = pNonCompetitorsWrite++;// Write non-competitors and racers data
          fwrite(pCurrentNonCompetitor, 4, 1, replayfile);
        } while (pNonCompetitorsWrite != &non_competitors[16]);
        fwrite(&racers, 4, 1, replayfile);
        iCarWriteCounter = 0;
        if (numcars > 0) {
          iCarWriteIndex = 0;
          do {
            buffer[0] = Car[iCarWriteIndex].byCarDesignIdx;// Write car design indices for each car
            ++iCarWriteCounter;
            fwrite(buffer, 1, 1, replayfile);
            ++iCarWriteIndex;
          } while (iCarWriteCounter < numcars);
        }
        iDriverNameCounter = 0;
        if (numcars > 0) {
          pDriverNamesWrite = driver_names[0];
          do {
            fwrite(pDriverNamesWrite, 9, 1, replayfile);
            ++iDriverNameCounter;
            pDriverNamesWrite += 9;
          } while (iDriverNameCounter < numcars);
        }
      }
    } else if (replaytype == 2) {                                           // PLAYBACK MODE: Load replay data from GSS file
      if (!intro)
        rev_vga[15] = (tBlockHeader *)load_picture("replaysc.bm");// Load replay screen image if not in intro mode

      int iCounter = 0; //added by ROLLER
      pDriverNamesSrc = driver_names[0];        // Backup current driver names to temp storage
      pTempNamesDest = temp_names[0];
      do {
        pTempPtr1 = pTempNamesDest;
        pTempPtr2 = pDriverNamesSrc;
        do {
          cTempChar1 = *pTempPtr2;
          *pTempPtr1 = *pTempPtr2;
          if (!cTempChar1)
            break;
          cTempChar2 = pTempPtr2[1];
          pTempPtr2 += 2;
          pTempPtr1[1] = cTempChar2;
          pTempPtr1 += 2;
        } while (cTempChar2);
        pDriverNamesSrc += 9;
        pTempNamesDest += 9;

        ++iCounter;
      } while (iCounter < 16);

      replayframes = ROLLERfilelength(replayfilename);
      //iFileHandle = open(replayfilename, 0x200);// Get replay file size to calculate frame count
      //iFileHandleCopy = iFileHandle;
      //if (iFileHandle != -1) {
      //  replayframes = filelength(iFileHandle);
      //  close(iFileHandleCopy);
      //}

      pReadFile = ROLLERfopen(replayfilename, "rb");  // Open replay file for reading
      replayfile = pReadFile;
      if (pReadFile) {
        fread(buffer, 1u, 1u, pReadFile);       // Read track number and game flags from replay file
        TrackLoad = buffer[0];
        game_track = buffer[0];
        fread(buffer, 1u, 1u, replayfile);

        // TEX_OFF_ADVANCED_CARS
        if ((buffer[0] & 0x20) != 0)
          textures_off |= TEX_OFF_ADVANCED_CARS;
        else
          textures_off &= ~TEX_OFF_ADVANCED_CARS;

        cheat_mode = 0;

        // CHEAT_MODE_DOUBLE_TRACK
        if ((buffer[0] & 0x40) != 0) {
          cheat_mode |= CHEAT_MODE_DOUBLE_TRACK;
          //iCheatFlags1 = cheat_mode;
          //BYTE1(iCheatFlags1) = BYTE1(cheat_mode) | 0x10;
          //cheat_mode = iCheatFlags1;
        } else {
          cheat_mode &= ~CHEAT_MODE_DOUBLE_TRACK;
          //iCheatFlags2 = cheat_mode;
          //BYTE1(iCheatFlags2) = BYTE1(cheat_mode) & 0xEF;
          //cheat_mode = iCheatFlags2;
        }

        // CHEAT_MODE_TINY_CARS
        if ((buffer[0] & 0x80u) == 0) {
          cheat_mode |= CHEAT_MODE_TINY_CARS;
          //iCheatFlags4 = cheat_mode;
          //BYTE1(iCheatFlags4) = BYTE1(cheat_mode) & 0x7F;
          //cheat_mode = iCheatFlags4;
        } else {
          cheat_mode &= ~CHEAT_MODE_TINY_CARS;
          //iCheatFlags3 = cheat_mode;
          //BYTE1(iCheatFlags3) = BYTE1(cheat_mode) | 0x80;
          //cheat_mode = iCheatFlags3;
        }

        numcars = buffer[0] & 0x1F;
        fread(buffer, 1u, 1u, replayfile);
        ViewType[0] = buffer[0];
        fread(buffer, 1u, 1u, replayfile);
        SelectedView[0] = buffer[0];
        fread(camera, 6u, 0x64u, replayfile);
        fread(buffer, 1u, 1u, replayfile);
        pNonCompetitorsRead = non_competitors;
        cuts = buffer[0];
        do {
          pCurrentNonCompetitorRead = pNonCompetitorsRead++;
          fread(pCurrentNonCompetitorRead, 4u, 1u, replayfile);
        } while (pNonCompetitorsRead != &non_competitors[16]);
        fread(&racers, 4u, 1u, replayfile);
        iDriverIndex = 0;
        if (numcars > 0) {
          iNonCompetitorIndex = 0;
          iCarArrayIndex = 0;
          do {
            fread(buffer, 1u, 1u, replayfile);  // Initialize each car from replay data
            byCarDesignIdx = buffer[0];
            Car[iCarArrayIndex].iDriverIdx = iDriverIndex;
            Car[iCarArrayIndex].byCarDesignIdx = byCarDesignIdx;
            Car[iCarArrayIndex].byDamageToggle = 0;
            iNonCompetitorValue = non_competitors[iNonCompetitorIndex];
            Car[iCarArrayIndex].byLastDamageToggle = 20;
            if (iNonCompetitorValue)          // Position non-competitor cars off-track
            {
              Car[iCarArrayIndex].pos.fX = -localdata[0].pointAy[3].fX;
              Car[iCarArrayIndex].pos.fY = -localdata[0].pointAy[3].fY;
              dZCoordinate = -localdata[0].pointAy[3].fZ;
              Car[iCarArrayIndex].iControlType = 0;
              Car[iCarArrayIndex].byLives = -1;
              Car[iCarArrayIndex].fFinalSpeed = 0.0;
              Car[iCarArrayIndex].fSpeedOverflow = 0.0;
              finished_car[iNonCompetitorIndex] = -1;
              Car[iCarArrayIndex].nChunk2 = Car[iCarArrayIndex].nCurrChunk;
              Car[iCarArrayIndex].nCurrChunk = -1;
              Car[iCarArrayIndex].pos.fZ = (float)dZCoordinate + 1000.0f;
            }
            ++iNonCompetitorIndex;
            ++iDriverIndex;
            ++iCarArrayIndex;
          } while (iDriverIndex < numcars);
        }
        iDriverNameIndex = 0;
        if (numcars > 0) {
          pDriverNamesRead = driver_names[0];   // Read driver names from replay file
          do {
            fread(pDriverNamesRead, 9u, 1u, replayfile);// Write driver names (9 bytes each)
            ++iDriverNameIndex;
            pDriverNamesRead += 9;
          } while (iDriverNameIndex < numcars);
        }
        fseek(replayfile, replayheader, 0);     // Seek to replay frame data header
        iReplayDataIndex = 0;
        if (numcars > 0) {
          do {
            fread(&replayData, 0x1Eu, 1u, replayfile);// Read initial replay frame data (30 bytes per car)
            ++iReplayDataIndex;
            cReplayDataByte = replayData[3];
            iNumCarsLocal = numcars;

//TODO: ensure this is correct
            newrepsample[iReplayDataIndex - 1] = replayData[3];
            repsample[iReplayDataIndex - 1] = cReplayDataByte;
            //temp_names[15][iReplayDataIndex + 8] = replayData[3];
            //newrepsample[iReplayDataIndex + 15] = cReplayDataByte;
          } while (iReplayDataIndex < iNumCarsLocal);
        }
        replayheader = 10 * numcars + 673;      // Calculate replay header size and frame block size
        replayblock = 30 * racers + 16;
        replayframes = (int)(replayframes - replayheader) / (30 * racers + 16);
      }

      //TODO: ensure this is correct
      for (int iCarIndex = 0; iCarIndex < numcars; iCarIndex++)
      {
        // Initialize car physics data for replay
        Car[iCarIndex].iControlType = 8;           // was the DWORD assignment
        Car[iCarIndex].fHorizontalSpeed = 0.0f;    // was hitboxAy[14][2].fZ
        Car[iCarIndex].direction.fX = 0.0f;        // was hitboxAy[14][3].fY  
        Car[iCarIndex].direction.fY = 0.0f;        // was hitboxAy[14][1].fY
        Car[iCarIndex].direction.fZ = 0.0f;        // was hitboxAy[14][1].fZ
      }
      //if (numcars > 0) {
      //  iCarByteOffset = 0;
      //  iTotalCarBytes = sizeof(tCar) * numcars;
      //  do {
      //    iCarByteOffset += sizeof(tCar);       // Initialize car physics data for replay
      //    *(_DWORD *)((char *)&CarBox.hitboxAy[15][6].fY + iCarByteOffset) = 8;// offset into Car
      //    *(float *)((char *)&CarBox.hitboxAy[14][2].fZ + iCarByteOffset) = 0.0;
      //    *(float *)((char *)&CarBox.hitboxAy[14][3].fY + iCarByteOffset) = 0.0;
      //    *(float *)((char *)&CarBox.hitboxAy[14][1].fY + iCarByteOffset) = 0.0;
      //    *(float *)((char *)&CarBox.hitboxAy[14][1].fZ + iCarByteOffset) = 0.0;
      //  } while (iCarByteOffset < iTotalCarBytes);
      //}

      replayspeed = 256;                        // Set default replay speed and check for intro mode
      if (replayfilename[0] == 73 && !intro)
        filingmenu = 1;
    }
  }
}

//-------------------------------------------------------------------------------------------------
//00064730
void stopreplay()
{
  char *szTempNamePtr; // edx
  char *szDriverNamePtr; // ebx
  char *szDstPtr; // edi
  char *szSrcPtr; // esi
  char byChar1; // al
  char byChar2; // al
  //int uiAvailBytes; // edx
  //int iFileHandle; // eax
  //int iFileHandleCopy; // ebx
  //int iNewFileSize; // edx
  char *szReplayDstPtr; // edi
  char *szRememberSrcPtr; // esi
  char byReplayChar1; // al
  char byReplayChar2; // al
  //_diskfree_t diskfree; // [esp-2h] [ebp-1Ch] BYREF

  if (replaytype) {                            // Close replay file if replay is active
    if (replayfile) //check added by ROLLER
      fclose(replayfile);
  }
  if (replaytype == 2)                        // If replay type is 2 (recording/playback mode), restore driver names
  {
    int iCounter = 0;
    szTempNamePtr = temp_names[0];              // Copy temp driver names back to original driver names array
    szDriverNamePtr = driver_names[0];
    do {
      szDstPtr = szDriverNamePtr;
      szSrcPtr = szTempNamePtr;
      do {
        byChar1 = *szSrcPtr;
        *szDstPtr = *szSrcPtr;
        if (!byChar1)
          break;
        byChar2 = szSrcPtr[1];
        szSrcPtr += 2;
        szDstPtr[1] = byChar2;
        szDstPtr += 2;
      } while (byChar2);
      szTempNamePtr += 9;
      szDriverNamePtr += 9;

      ++iCounter;
    } while (iCounter < 16);
    TrackLoad = oldtrack;                       // Restore original track, car count and texture settings
    numcars = oldcars;
    textures_off = oldtextures;
  }
  if (replaytype == 1)                        // If replay type is 1 (recording mode), manage disk space
  {
    //dos_getdiskfree(0, &diskfree);              // Get disk free space information
    //uiAvailBytes = HIWORD(diskfree.total_clusters) * LOWORD(diskfree.avail_clusters) * HIWORD(diskfree.avail_clusters);// Calculate available disk space in bytes
    //if (uiAvailBytes < 0x100000)              // Check if available space is less than required threshold
    //{
    //  iFileHandle = open(replayfilename, 0x202);// Open replay file for trimming
    //  iFileHandleCopy = iFileHandle;
    //  if (iFileHandle != -1) {
    //    iNewFileSize = filelength(iFileHandle) - (0x100000 - uiAvailBytes);// Calculate new file size to free up disk space
    //    if (iNewFileSize >= 20480)            // If new size >= 20KB, truncate file; otherwise delete it
    //    {
    //      chsize(iFileHandleCopy, iNewFileSize);
    //      close(iFileHandleCopy);
    //    } else {
    //      close(iFileHandleCopy);
    //      remove(replayfilename);
    //    }
    //  }
    //}
  }
  replaytype = 0;                               // Reset replay type to inactive (0)
  if (intro)                                  // If in intro mode, restore original filename
  {
    szReplayDstPtr = replayfilename;            // Copy remembered filename back to replay filename
    szRememberSrcPtr = rememberfilename;
    do {
      byReplayChar1 = *szRememberSrcPtr;
      *szReplayDstPtr = *szRememberSrcPtr;
      if (!byReplayChar1)
        break;
      byReplayChar2 = szRememberSrcPtr[1];
      szRememberSrcPtr += 2;
      szReplayDstPtr[1] = byReplayChar2;
      szReplayDstPtr += 2;
    } while (byReplayChar2);
  }
}

//-------------------------------------------------------------------------------------------------
//00064880
void DoReplayData()
{
  /*
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
void deleteframes(int iStartFrame, int iEndFrame)
{
  int iEndFrameFixed; // esi
  int iTemp; // ebx
  int iCurrentFrame; // ebx
  int iArrayIndex; // eax

  iEndFrameFixed = iEndFrame;
  if (replaytype == 2)                        // Check if we're in replay mode (type 2)
  {                                             // Ensure start frame <= end frame by swapping if necessary
    if (iEndFrame < iStartFrame) {
      iTemp = iStartFrame;
      iStartFrame = iEndFrame;
      iEndFrameFixed = iTemp;
    }
    for (iCurrentFrame = iStartFrame; iCurrentFrame <= iEndFrameFixed; ++iCurrentFrame)// Loop through all frames in the range to mark as disabled
    {                                           // Check frame is within valid range (< 128K frames max)
      if (iCurrentFrame < 0x20000) {
        iArrayIndex = iCurrentFrame / 32;  // Calculate array index: divide by 32 to get DWORD index
        //iArrayIndex = (iCurrentFrame - (__CFSHL__(iCurrentFrame >> 31, 5) + 32 * (iCurrentFrame >> 31))) >> 5;// Calculate array index: iCurrentFrame / 32
        disabled[iArrayIndex] |= 1 << (iCurrentFrame - 32 * iArrayIndex);// Set bit in disabled[] bitfield to mark frame as disabled
      }
    }
  }
}

//-------------------------------------------------------------------------------------------------
//000661E0
void undeleteframes(int iStartFrame, int iEndFrame)
{
  int iEndFrameFixed; // ebx
  int iTemp; // edx
  int iCurrentFrame; // edx
  int iFrameToUndelete; // eax

  iEndFrameFixed = iEndFrame;
  if (replaytype == 2)                        // Check if we're in replay mode (type 2)
  {                                             // Ensure start frame <= end frame by swapping if necessary
    if (iEndFrame < iStartFrame) {
      iTemp = iStartFrame;
      iStartFrame = iEndFrameFixed;
      iEndFrameFixed = iTemp;
    }
    for (iCurrentFrame = iStartFrame; iCurrentFrame <= iEndFrameFixed; ++iCurrentFrame)// Loop through all frames in the range to undelete them
    {
      iFrameToUndelete = iCurrentFrame;
      cleardisable(iFrameToUndelete);           // Clear the disabled bit for this frame
    }
  }
}

//-------------------------------------------------------------------------------------------------
//00066210
void findnextvalid()
{
  int iOriginalFrame; // ebx
  int iTestFrame; // edx
  unsigned int uiDisabledStatus; // eax
  int iBackwardFrame; // edx
  unsigned int uiBackwardDisabled; // eax

  iOriginalFrame = currentreplayframe;          // Store original frame position for potential fallback
  for (iTestFrame = currentreplayframe + 1; currentreplayframe + 1 < replayframes; iTestFrame = currentreplayframe + 1)// Search forward for next valid (non-disabled) frame
  {
    currentreplayframe = iTestFrame;
    uiDisabledStatus = readdisable(iTestFrame); // Check if current frame is disabled
    iTestFrame = currentreplayframe;
    if (!uiDisabledStatus)
      break;                                    // If frame is enabled (not disabled), we found our target
  }
  if (iTestFrame == replayframes)             // If reached end without finding valid frame, search backward
  {
    iBackwardFrame = iOriginalFrame - 1;
    if (iOriginalFrame - 1 >= 0)              // Search backward from original position for valid frame
    {
      do {
        currentreplayframe = iBackwardFrame;
        uiBackwardDisabled = readdisable(iBackwardFrame);// Check if backward frame is disabled
        iBackwardFrame = currentreplayframe;
        if (!uiBackwardDisabled)
          break;
        iBackwardFrame = currentreplayframe - 1;
      } while (currentreplayframe - 1 >= 0);
    }
    if (iBackwardFrame < 0)                   // If no valid frame found, fallback to original position
      iBackwardFrame = iOriginalFrame;
    if (replaytype == 2)                      // If in replay mode, stop playback and reset state
    {
      currentreplayframe = iBackwardFrame;      // Disable interrupts for atomic update
      //_disable();
      replayspeed = 0;                          // Stop replay playback
      fraction = 0;
      replaydirection = 0;
      ticks = currentreplayframe;
      //_enable();
      iBackwardFrame = currentreplayframe;
    }
  } else {
    currentreplayframe = iTestFrame;
    //_disable();                                 // Found valid frame forward - update timing atomically
    ticks = currentreplayframe;
    fraction = 0;
    //_enable();
    iBackwardFrame = currentreplayframe;
    if (iOriginalFrame != currentreplayframe) // If frame changed, trigger view refresh
      pend_view_init = ViewType[0];
  }
  currentreplayframe = iBackwardFrame;
}

//-------------------------------------------------------------------------------------------------
//00066300
void findlastvalid()
{
  int iOriginalFrame; // ebx
  int iTestFrame; // edx
  unsigned int uiDisabledStatus; // eax
  int iForwardFrame; // edx
  unsigned int uiForwardDisabled; // eax

  iOriginalFrame = currentreplayframe;          // Store original frame position for potential fallback
  for (iTestFrame = currentreplayframe - 1; currentreplayframe - 1 >= 0; iTestFrame = currentreplayframe - 1)// Search backward for previous valid (non-disabled) frame
  {
    currentreplayframe = iTestFrame;
    uiDisabledStatus = readdisable(iTestFrame); // Check if current frame is disabled
    iTestFrame = currentreplayframe;
    if (!uiDisabledStatus)
      break;                                    // If frame is enabled (not disabled), we found our target
  }
  if (iTestFrame >= 0)                        // If found valid frame backward, use it
  {
    currentreplayframe = iTestFrame;
    //_disable();                                 // Found valid frame backward - update timing atomically
    ticks = currentreplayframe;
    fraction = 0;
    //_enable();
    iForwardFrame = currentreplayframe;
    if (iOriginalFrame != currentreplayframe) // If frame changed, trigger view refresh
      pend_view_init = ViewType[0];
  } else {
    iForwardFrame = iOriginalFrame + 1;         // No valid frame backward, search forward from original position
    if (iOriginalFrame + 1 < replayframes)    // Search forward from original position for valid frame
    {
      do {
        currentreplayframe = iForwardFrame;
        uiForwardDisabled = readdisable(iForwardFrame);// Check if forward frame is disabled
        iForwardFrame = currentreplayframe;
        if (!uiForwardDisabled)
          break;
        iForwardFrame = currentreplayframe + 1;
      } while (currentreplayframe + 1 < replayframes);
    }
    if (iForwardFrame == replayframes)        // If no valid frame found, fallback to original position
      iForwardFrame = iOriginalFrame;
    if (replaytype == 2)                      // If in replay mode, stop playback and reset state
    {
      currentreplayframe = iForwardFrame;
      //_disable();                               // Disable interrupts for atomic update
      replayspeed = 0;                          // Stop replay playback
      fraction = 0;
      replaydirection = 0;
      ticks = currentreplayframe;
      //_enable();
      iForwardFrame = currentreplayframe;
    }
  }
  currentreplayframe = iForwardFrame;
}

//-------------------------------------------------------------------------------------------------
//000663F0
void Rassemble()
{
  int iCarIndex; // eax
  int iNumCars; // ebp
  int iCarCounter; // edx
  char *szSourcePtr; // esi
  char *szDestPtr; // edi
  char byChar1; // al
  char byChar2; // al
  char *szExtSourcePtr; // esi
  char *szExtDestPtr; // edi
  char byExtChar1; // al
  char byExtChar2; // al
  FILE *pOutputFile; // esi
  int iErrorCode1; // eax
  int iFrame; // ebp
  int iValidFrames; // esi
  int iCutIndex; // edi
  int i; // edx
  int iSeekOffset; // edx
  int iErrorCode2; // eax
  tReplayCamera *pCamera; // eax
  FILE *pWriteFile; // ecx
  int iErrorCode3; // eax
  int iCutsTotal; // edx
  tReplayCamera *pNextCamera; // ebx
  int iCutCounter; // ecx
  int iPaddingCount; // ebp
  int j; // edi
  int iErrorCode4; // eax
  int iErrorCode5; // eax
  uint8 *szDataBuffer; // edi
  unsigned int uiBytesRead; // eax
  uint8 *szCarDataPtr; // ebx
  int iCarLoop1; // edx
  int iCarIndex1; // ecx
  uint8 *szCarDataPtr2; // ebx
  int iCarLoop2; // edx
  int iCarIndex2; // ecx
  char byCarData; // al
  uint8 byDirection; // ah
  uint8 byProcessedData; // al
  int iCarCount; // esi
  int iErrorCode6; // eax
  int iHasData; // esi
  int aiCarDirectionFlags[32]; // [esp+0h] [ebp-134h]
  char szFilename[32]; // [esp+80h] [ebp-B4h] BYREF
  uint8 carVelocityData[32]; // [esp+A0h] [ebp-94h]
  uint8 emptyCameraData[16]; // [esp+C0h] [ebp-74h] BYREF
  int iCutsWritten; // [esp+D0h] [ebp-64h]
  int iLastError; // [esp+D4h] [ebp-60h]
  int iErrorFlag; // [esp+D8h] [ebp-5Ch]
  int iTempData; // [esp+DCh] [ebp-58h]
  int iFrameBackup; // [esp+E0h] [ebp-54h]
  unsigned int uiSize; // [esp+E4h] [ebp-50h]
  void *pData; // [esp+E8h] [ebp-4Ch]
  tReplayCamera *pCameraPtr; // [esp+ECh] [ebp-48h]
  int iOffset; // [esp+F0h] [ebp-44h]
  int iPrevValidFrame; // [esp+F4h] [ebp-40h]
  int iCutProcessed; // [esp+F8h] [ebp-3Ch]
  int iDataWritten; // [esp+FCh] [ebp-38h]
  signed int k; // [esp+100h] [ebp-34h]
  FILE *fp; // [esp+104h] [ebp-30h]
  int iInitFlag; // [esp+108h] [ebp-2Ch]
  int iFrameCounter; // [esp+10Ch] [ebp-28h]
  signed int iBlockCounter; // [esp+110h] [ebp-24h]
  uint8 tempBuffer[32]; // [esp+114h] [ebp-20h] BYREF

  iDataWritten = 0;
  iErrorFlag = 0;
  if (replaytype == 2)                        // Only process if replay type is 2 (assembly mode)
  {
    memset(emptyCameraData, 0, sizeof(emptyCameraData));// Initialize empty camera data buffer and setup car processing arrays
    pData = scrbuf;
    iCarIndex = 0;
    if (numcars > 0)                          // Initialize car data arrays for all cars in replay
    {
      iNumCars = numcars;
      iCarCounter = 0;
      do {
        ++iCarCounter;
        carVelocityData[iCarIndex++] = 1;
        aiCarDirectionFlags[iCarCounter + 15] = 1;
      } while (iCarIndex < iNumCars);
    }
    //_disable();                                 // Disable interrupts and reset replay state for assembly
    iInitFlag = -1;
    replayspeed = 0;
    replaydirection = 0;
    fraction = 0;
    ticks = currentreplayframe;
    //_enable();
    strcpy(szFilename, "..\\REPLAYS\\");        // Build output filename by concatenating path, selected name, and .GSS extension
    szSourcePtr = selectfilename;
    szDestPtr = &szFilename[strlen(szFilename)];
    do {
      byChar1 = *szSourcePtr;
      *szDestPtr = *szSourcePtr;
      if (!byChar1)
        break;
      byChar2 = szSourcePtr[1];
      szSourcePtr += 2;
      szDestPtr[1] = byChar2;
      szDestPtr += 2;
    } while (byChar2);
    szExtSourcePtr = g_szGss;
    szExtDestPtr = &szFilename[strlen(szFilename)];
    do {
      byExtChar1 = *szExtSourcePtr;
      *szExtDestPtr = *szExtSourcePtr;
      if (!byExtChar1)
        break;
      byExtChar2 = szExtSourcePtr[1];
      szExtSourcePtr += 2;
      szExtDestPtr[1] = byExtChar2;
      szExtDestPtr += 2;
    } while (byExtChar2);
    if (!strcmp(szFilename, replayfilename))  // Check if trying to overwrite current replay file
    {
      lastfile = 0;
      screenready = 0;
      filingmenu = 9;
    } else {
      pOutputFile = fopen(szFilename, "wb");    // Open output file and copy replay header from source file
      fp = pOutputFile;
      if (pOutputFile) {
        fseek(replayfile, 0, 0);
        fread(pData, 1u, replayheader, replayfile);
        if (fwrite(pData, 1, replayheader, pOutputFile) != replayheader) {
          iErrorCode1 = errno;
          iErrorFlag = -1;
          iLastError = iErrorCode1;
        }
        iFrame = 0;                             // Initialize frame processing and camera cut handling
        iPrevValidFrame = -1;
        iValidFrames = 0;
        uiSize = 64000 / replayblock;
        iCutsWritten = 0;
        fseek(fp, 4, 0);
        iCutProcessed = 0;
        if (cuts > 0)                         // Process each camera cut, counting valid frames and writing camera data
        {
          pCameraPtr = camera;
          iOffset = -4;
          iCutIndex = 0;
          do {                                     // Count valid frames up to current camera cut
            for (i = iFrame; i < camera[iCutIndex].iFrame; ++i) {
              if (!readdisable(i))
                ++iValidFrames;
            }
            iFrame = camera[iCutIndex].iFrame;
            iFrameBackup = iFrame;
            if (iPrevValidFrame == -1 || iValidFrames != iPrevValidFrame)// Write camera cut data - either new entry or update existing duplicate frame
            {
              pCamera = pCameraPtr;
              pWriteFile = fp;
              camera[iCutIndex].iFrame = iValidFrames;
              if (fwrite(pCamera, 1, 6, pWriteFile) != 6) {
                iErrorCode3 = errno;
                iErrorFlag = -1;
                iLastError = iErrorCode3;
              }
              iPrevValidFrame = iValidFrames;
              iOffset += 6;
              ++iCutsWritten;
            } else {
              iSeekOffset = iOffset;
              camera[iCutIndex].iFrame = iPrevValidFrame;
              fseek(fp, iSeekOffset, 0);
              if (fwrite(&camera[iCutIndex], 1, 6, fp) != 6) {
                iErrorCode2 = errno;
                iErrorFlag = -1;
                iLastError = iErrorCode2;
              }
            }
            iCutsTotal = cuts;
            ++iCutIndex;
            pNextCamera = pCameraPtr + 1;
            iCutCounter = iCutProcessed + 1;
            //TODO ensure this is accurate
            camera[iCutIndex - 1].iFrame = iFrameBackup;
            //*(int *)((char *)&yp_variable_1 + iCutIndex * 6) = iFrameBackup;// reference into adjacent data camera
            pCameraPtr = pNextCamera;
            iCutProcessed = iCutCounter;
          } while (iCutCounter < iCutsTotal);
        }
        iPaddingCount = 100 - iCutsWritten;     // Fill remaining camera slots with empty data (max 100 cuts)
        for (j = 0; j < iPaddingCount; ++j) {
          if (fwrite(emptyCameraData, 1, 6, fp) != 6) {
            iErrorCode4 = errno;
            iErrorFlag = -1;
            iLastError = iErrorCode4;
          }
        }
        tempBuffer[0] = iCutsWritten;           // Write total number of camera cuts to file
        if (fwrite(tempBuffer, 1, 1, fp) != 1) {
          iErrorCode5 = errno;
          iErrorFlag = -1;
          iLastError = iErrorCode5;
        }
        fseek(fp, replayheader, 0);             // Main replay data processing - read blocks and filter/process car data
        iFrameCounter = 0;
        do {
          szDataBuffer = (uint8 *)pData;
          uiBytesRead = (uint32)fread(pData, replayblock, uiSize, replayfile);
          iBlockCounter = 0;
          for (k = uiBytesRead; iBlockCounter < k; ++iBlockCounter) {                                     // Skip disabled frames, process valid frames with car data filtering
            if (readdisable(iFrameCounter)) {
              iInitFlag = -1;
            } else {                                   // First-time setup of car direction tracking arrays
              if (iInitFlag) {
                szCarDataPtr = szDataBuffer;
                iCarLoop1 = 0;
                if (numcars > 0) {
                  iCarIndex1 = 0;
                  do {
                    aiCarDirectionFlags[iCarIndex1] = (((int)szCarDataPtr[26] >> 3) & 1) == aiCarDirectionFlags[iCarIndex1 + 16];
                    iTempData = szCarDataPtr[3];
                    //iTempData = (uint8)HIBYTE(*(_DWORD *)szCarDataPtr);
                    tempBuffer[4] = iTempData;
                    if ((char)iTempData * (char)carVelocityData[iCarLoop1] >= 0)
                      carVelocityData[iCarLoop1 + 16] = 1;
                    else
                      carVelocityData[iCarLoop1 + 16] = -1;
                    szCarDataPtr += 30;
                    ++iCarLoop1;
                    ++iCarIndex1;
                  } while (iCarLoop1 < numcars);
                }
                iInitFlag = 0;
              }
              szCarDataPtr2 = szDataBuffer;     // Process car data - flip direction bits and apply velocity corrections
              iCarLoop2 = 0;
              if (numcars > 0) {
                iCarIndex2 = 0;
                do {
                  szCarDataPtr2[26] ^= 8 * (uint8)(aiCarDirectionFlags[iCarIndex2]);
                  aiCarDirectionFlags[iCarIndex2 + 16] = ((int)szCarDataPtr2[26] >> 3) & 1;
                  iTempData = szCarDataPtr2[3];
                  //iTempData = (uint8)HIBYTE(*(_DWORD *)szCarDataPtr2);
                  byCarData = iTempData;
                  byDirection = carVelocityData[iCarLoop2 + 16];
                  carVelocityData[iCarLoop2] = iTempData;
                  byProcessedData = byDirection * byCarData;
                  szCarDataPtr2 += 30;
                  ++iCarIndex2;
                  carVelocityData[iCarLoop2++] = byProcessedData;
                  iCarCount = numcars;
                  *(int *)(szCarDataPtr2 - 30) = ((char)byProcessedData << 24) | *(int *)(szCarDataPtr2 - 30) & 0xFFFFFF;
                } while (iCarLoop2 < iCarCount);
              }
              iDataWritten = -1;
              if (fwrite(szDataBuffer, 1, replayblock, fp) != replayblock) {
                iErrorCode6 = errno;
                iErrorFlag = -1;
                iLastError = iErrorCode6;
              }
            }
            szDataBuffer += replayblock;
            ++iFrameCounter;
          }
        } while (k == uiSize && !iErrorFlag);
        iHasData = iDataWritten;                // Close file and handle errors - delete incomplete file on failure
        fclose(fp);
        if (!iHasData) {
          errno = -1000;
          iErrorFlag = -1;
        }
        if (iErrorFlag)
          remove(szFilename);
      }
      filingmenu = 0;
      lastfile = 0;
      screenready = 0;
    }
  }
  if (iErrorFlag)                             // Set appropriate error dialog based on failure type
  {
    if (iLastError == 12) {
      filingmenu = 6;
    } else if (iLastError == -1000) {
      filingmenu = 8;
    } else {
      filingmenu = 7;
    }
  }
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
  int iLastValidCut; // ecx
  int iCutIndex; // eax
  int iArrayIndex; // edx

  iLastValidCut = -1;                           // Initialize to -1 (no valid cut found)
  if (cuts)                                   // Check if any camera cuts exist
  {
    iCutIndex = 0;
    if (cuts > 0)                             // Iterate through all camera cuts to find the active one
    {
      iArrayIndex = 0;
      do {                                         // Check if this cut's frame is at or before current replay frame
        if (camera[iArrayIndex].iFrame <= currentreplayframe)
          iLastValidCut = iCutIndex;            // Update to this cut index (keeps the latest valid cut)
        ++iCutIndex;
        ++iArrayIndex;
      } while (iCutIndex < cuts);
    }
  }
  return iLastValidCut;                         // Return index of most recent valid cut, or -1 if none found
}

//-------------------------------------------------------------------------------------------------
//00066CC0
void displayreplay()
{                                               // Apply scanline effect for disabled replay frames (type 2)
  uint8 *pScreenBuffer; // edi
  int iWindowWidth; // esi
  int iHeightLoop; // ecx
  int iWidthLoop; // eax
  uint8 *pPixelPtr; // edx
  int iRowIndex; // ecx
  uint8 *pRowPtr; // eax

  if (replaytype == 2 && readdisable(currentreplayframe)) {
    pScreenBuffer = scrbuf;                     // Get screen buffer and window dimensions for scanline processing
    iWindowWidth = winw;
    for (iHeightLoop = 0; iHeightLoop < winh; iHeightLoop += 2)// First pass: Set every other pixel to black on even rows (scanlines)
    {
      for (iWidthLoop = 0; iWidthLoop < iWindowWidth; pPixelPtr[iWindowWidth * iHeightLoop] = 0) {
        pPixelPtr = &pScreenBuffer[iWidthLoop];
        iWidthLoop += 2;
      }
    }
    iRowIndex = 1;                              // Second pass: Clear entire odd rows to create horizontal scanline effect
    winw = iWindowWidth;
    scrbuf = pScreenBuffer;
    while (iRowIndex < winh) {
      pRowPtr = &scrbuf[winw * iRowIndex];
      iRowIndex += 2;
      memset(pRowPtr, 0, winw);
    }
  }
  if (filingmenu)                             // Handle file menu dialogs for replay management
  {
    switch (filingmenu) {
      case 1:
        fileselect(10, 10, 310, 125, 160, 20, &language_buffer[3136], "..\\REPLAYS\\*.GSS", 1);// Load replay dialog
        break;
      case 2:
        fileselect(10, 10, 310, 140, 160, 20, &language_buffer[3200], "..\\REPLAYS\\*.GSS", 2);// Save replay dialog
        break;
      case 3:
        fileselect(10, 10, 310, 125, 160, 20, &language_buffer[3264], "..\\REPLAYS\\*.GSS", 3);// Delete replay dialog
        break;
      case 4:
        fileselect(10, 10, 310, 140, 160, 20, &language_buffer[3392], "..\\REPLAYS\\*.GSS", 4);// Assemble replay dialog
        break;
      case 5:
        lsd(40, 37, 280, 107);                  // Show LSD (replay statistics) dialog
        break;
      case 6:
        warning(122, 55, 198, 85, &language_buffer[3456]);// Show warning dialogs for various replay operations
        break;
      case 7:
        warning(112, 55, 208, 85, &language_buffer[3520]);
        break;
      case 8:
        warning(82, 55, 238, 85, &language_buffer[3584]);
        break;
      case 9:
        warning(40, 55, 280, 85, &language_buffer[3648]);
        break;
      default:
        break;
    }
  }
  if (replaypanel)                            // Validate replay panel display based on screen mode and size
  {
    if ((!SVGA_ON || scr_size != 128) && (SVGA_ON || scr_size != 64)) {
      replaypanel = 0;
      controlicon = 9;
    }
  }
  if (replaypanel)                            // Display control panel if replay panel is active
    displaycontrolpanel();
}

//-------------------------------------------------------------------------------------------------
//00066F60
int compare(const void *szStr1, const void *szStr2)
{
  return strcmp((const char *)szStr1, (const char *)szStr2);
}

//-------------------------------------------------------------------------------------------------
//00066F70
void warning(int iX1, int iY1, int iX2, int iY2, char *szWarning)
{
  int iX1Scaled; // esi
  int iY1_1; // edi
  tPolyParams poly; // [esp+0h] [ebp-38h] BYREF

  iX1Scaled = iX1;
  iY1_1 = iY1;
  if (SVGA_ON) {
    iX2 *= 2;
    iY1 *= 2;
    iX1Scaled = 2 * iX1;
    iY2 *= 2;
  }
  poly.vertices[0].x = iX2;
  poly.vertices[0].y = iY1;
  poly.vertices[1].x = iX1Scaled;
  poly.vertices[1].y = iY1;
  poly.vertices[2].x = iX1Scaled;
  poly.vertices[2].y = iY2;
  poly.vertices[3].x = iX2;
  poly.vertices[3].y = iY2;
  poly.iSurfaceType = SURFACE_FLAG_TRANSPARENT | 0x3;// 0x200003;
  poly.uiNumVerts = 4;
  POLYFLAT(scrbuf, &poly);
  prt_centrecol(rev_vga[1], szWarning, (iX1Scaled + iX2) / 2, iY1_1 + 10, 231);
  if (fatkbhit()) {
    while (fatkbhit())
      fatgetch();
    filingmenu = 0;
    disciconpressed = 0;
  }
}

//-------------------------------------------------------------------------------------------------
//00067020
void lsd(int iX1, int iY1, int iX2, int iY2)
{
  int iOriginalY1; // esi
  uint8 byKey; // al
  uint8 byExtendedKey; // al
  int iMenuOption; // ebp
  char *pDestBuffer; // edi
  char *pSourceText; // esi
  char byChar1; // al
  char byChar2; // al
  char byTextColor; // [esp-4h] [ebp-40h]
  tPolyParams poly; // [esp+0h] [ebp-3Ch] BYREF
  int iTextY; // [esp+2Ch] [ebp-10h]

  iOriginalY1 = iY1;                            // Save original Y1 coordinate before SVGA scaling
  if (SVGA_ON)                                // Scale coordinates by 2x for SVGA mode
  {
    iX2 *= 2;
    iY1 *= 2;
    iX1 *= 2;
    iY2 *= 2;
  }
  poly.vertices[0].x = iX2;                     // Set up polygon vertices for background rectangle
  poly.vertices[0].y = iY1;
  poly.vertices[1].x = iX1;
  poly.vertices[1].y = iY1;
  poly.vertices[2].x = iX1;
  poly.vertices[2].y = iY2;
  poly.vertices[3].x = iX2;
  poly.vertices[3].y = iY2;
  poly.iSurfaceType = 0x200003;                 // = SURFACE_FLAG_TRANSPARENT | 0x3;
  poly.uiNumVerts = 4;
  POLYFLAT(scrbuf, &poly);
  prt_centrecol(rev_vga[1], &language_buffer[3072], 160, iOriginalY1 + 10, 231);// Display menu title text centered
  while (fatkbhit())                          // Main input loop - process keyboard input
  {
    byKey = fatgetch();                         // Get key press
    if (byKey)                                // Check if regular ASCII key or extended key (0 = extended)
    {                                           // Check for ENTER key (0x0D)
      if (byKey >= 0xDu) {
        if (byKey <= 0xDu) {
          sfxsample(83, 0x8000);                // SOUND_SAMPLE_BUTTON
          filingmenu = lsdsel + 1;
        } else if (byKey == 0x1B)               // Check for ESCAPE key (0x1B)
        {
          filingmenu = 0;                       // ESCAPE: cancel menu and reset state
          disciconpressed = 0;
          rotpoint = currentreplayframe;
        }
      }
    } else {
      byExtendedKey = fatgetch();               // Extended key: get second byte of scancode
      if (byExtendedKey >= 0x48u)             // Check for UP arrow key (0x48)
      {
        if (byExtendedKey <= 0x48u) {                                       // UP arrow: move selection up if not at top
          if (lsdsel)
            --lsdsel;
        } else if (byExtendedKey == 0x50 && lsdsel < 2)// Check for DOWN arrow key (0x50)
        {
          ++lsdsel;                             // DOWN arrow: move selection down if not at bottom
        }
      }
    }
  }
  iMenuOption = 0;                              // Begin menu text rendering loop
  iTextY = iOriginalY1 + 30;                    // Calculate starting Y position for menu text
  do {                                             // Select appropriate menu text based on option index
    if (iMenuOption) {
      if ((unsigned int)iMenuOption <= 1) {
        pDestBuffer = buffer;
        pSourceText = &language_buffer[3200];
      } else {
        if (iMenuOption != 2)
          goto RENDER_MENU_OPTION;
        pDestBuffer = buffer;
        pSourceText = &language_buffer[3264];
      }
    } else {
      pDestBuffer = buffer;
      pSourceText = &language_buffer[3136];
    }
    do {
      byChar1 = *pSourceText;                   // String copy loop: copy 2 bytes at a time until null terminator
      *pDestBuffer = *pSourceText;
      if (!byChar1)
        break;
      byChar2 = pSourceText[1];
      pSourceText += 2;
      pDestBuffer[1] = byChar2;
      pDestBuffer += 2;
    } while (byChar2);
  RENDER_MENU_OPTION:
    if (iMenuOption == lsdsel)                // Set text color based on selection: highlighted vs normal
      byTextColor = 0x8F;                       // Selected item color (0x8F = white)
    else
      byTextColor = 0x83;                       // Normal item color (0x83 = grey)
    prt_centrecol(rev_vga[1], buffer, 160, iTextY, byTextColor);// Draw menu option text centered
    ++iMenuOption;                              // Advance to next menu option and Y position
    iTextY += 10;
  } while (iMenuOption < 3);                    // Continue until all 3 menu options are drawn
}

//-------------------------------------------------------------------------------------------------
//000671D0
void scandirectory(const char *szPattern)
{
  int iFileCount = 0;

#ifdef IS_WINDOWS
  struct _finddata_t fileinfo;
  intptr_t handle = _findfirst(szPattern, &fileinfo);
  if (handle == -1) {
    filefiles = 0;
    return;
  }

  do {
    if (iFileCount >= 500)
      break;

    // Extract filename without extension (stop at first dot)
    const char *szFileNamePtr = fileinfo.name;
    int iCharIndex = 0;
    while (*szFileNamePtr && *szFileNamePtr != '.' && iCharIndex < 8) {
      filename[iFileCount][iCharIndex++] = *szFileNamePtr++;
    }
    filename[iFileCount][iCharIndex] = '\0';

    iFileCount++;
  } while (_findnext(handle, &fileinfo) == 0);

  _findclose(handle);

#else
  // For Unix-like systems, we need to extract directory and pattern from szPattern
  char szDirectory[256];
  char szFilePattern[256];

  // Find the last directory separator
  const char *szLastSlash = strrchr(szPattern, '/');
  const char *szLastBackslash = strrchr(szPattern, '\\');
  const char *szSeparator = (szLastSlash > szLastBackslash) ? szLastSlash : szLastBackslash;

  if (szSeparator) {
    // Extract directory path
    size_t nDirLen = szSeparator - szPattern + 1;
    strncpy(szDirectory, szPattern, nDirLen);
    szDirectory[nDirLen] = '\0';
    // Extract pattern
    strcpy(szFilePattern, szSeparator + 1);
  } else {
    // No directory specified, use current directory
    strcpy(szDirectory, ".");
    strcpy(szFilePattern, szPattern);
  }

  DIR *dir = opendir(szDirectory);
  if (!dir) {
    filefiles = 0;
    return;
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL && iFileCount < 500) {
    // Check if filename matches pattern (case-insensitive)
    if (fnmatch(szFilePattern, entry->d_name, FNM_CASEFOLD) == 0) {
      // Extract filename without extension (stop at first dot)
      const char *szFileNamePtr = entry->d_name;
      int iCharIndex = 0;
      while (*szFileNamePtr && *szFileNamePtr != '.' && iCharIndex < 8) {
        filename[iFileCount][iCharIndex++] = *szFileNamePtr++;
      }
      filename[iFileCount][iCharIndex] = '\0';

      iFileCount++;
    }
  }

  closedir(dir);
#endif

  // Update global file count
  filefiles = iFileCount;

  // Sort filenames alphabetically using compare function
  if (iFileCount > 0) {
    qsort(filename, iFileCount, 9, compare);
  }
}

//-------------------------------------------------------------------------------------------------
//000672C0
void fileselect(int iBoxX0, int iBoxY0, int iBoxX1, int iBoxY1, int iTextX, int iTextY, const char *szText, const char *szPattern, int iFileIdx)
{
  int iCurrentFile; // ebp
  char *szDestPtr; // edi
  char *szSourcePtr; // esi
  char byChar1; // al
  char byChar2; // al
  char byKeyCode; // al
  char byProcessedKey; // dl
  int iLeftNavFile; // ebp
  char *szLeftDestPtr; // edi
  char *szLeftSourcePtr; // esi
  char byLeftChar1; // al
  char byLeftChar2; // al
  int iRightNavFile; // ebp
  char *szRightDestPtr; // edi
  char *szRightSourcePtr; // esi
  char byRightChar1; // al
  char byRightChar2; // al
  int iUpNavFile; // ebp
  char *szUpDestPtr; // edi
  char *szUpSourcePtr; // esi
  char byUpChar1; // al
  char byUpChar2; // al
  int iDownNavFile; // ebp
  char *szDownDestPtr; // edi
  char *szDownSourcePtr; // esi
  char byDownChar1; // al
  char byDownChar2; // al
  unsigned int uiDelStrLen; // kr08_4
  unsigned int uiBackspaceLen; // kr0C_4
  int iInputStrLen; // ecx
  int iDisplayFile; // ebp
  int iLoopCounter; // edi
  int iDisplayX; // ebx
  int iDisplayY; // ecx
  const char *szDisplayName; // edx
  unsigned int uiCursorLen; // kr14_4
  unsigned int uiCursorPos; // ebx
  int iScreenWidth; // esi
  int iUpArrowX; // ecx
  int iDownArrowX; // ecx
  tPolyParams params; // [esp+0h] [ebp-48h] BYREF
  int iRightEdge; // [esp+2Ch] [ebp-1Ch]
  int iEditMode; // [esp+30h] [ebp-18h]
  int iLeftEdge; // [esp+34h] [ebp-14h]
  int iBottomEdge; // [esp+38h] [ebp-10h]

  iLeftEdge = iBoxX0;                           // Store left edge coordinate in local variable
  if (filingmenu == 2 || filingmenu == 4)     // Check if in save mode (2) or assemble mode (4) to enable text editing
    iEditMode = -1;
  else
    iEditMode = 0;
  if (SVGA_ON)                                // Scale coordinates by 2 if SVGA mode is enabled
  {
    iBoxX1 *= 2;
    iBoxY0 *= 2;
    iBoxY1 *= 2;
    iLeftEdge *= 2;
  }
  params.vertices[0].x = iBoxX1;                // Set up polygon vertices for file selection background rectangle
  params.vertices[0].y = iBoxY0;
  params.vertices[1].y = iBoxY0;
  params.vertices[2].y = iBoxY1;
  params.vertices[3].x = iBoxX1;
  params.vertices[3].y = iBoxY1;
  params.iSurfaceType = 2097155;
  params.uiNumVerts = 4;
  params.vertices[1].x = iLeftEdge;
  params.vertices[2].x = iLeftEdge;
  POLYFLAT(scrbuf, &params);
  prt_centrecol(rev_vga[1], szText, iTextX, iTextY, 231);
  if (iFileIdx != lastfile)                   // If different directory selected, rescan files and reset selection
  {
    topfile = 0;
    filefile = 0;
    scandirectory(szPattern);
    iCurrentFile = filefile;
    lastfile = iFileIdx;
    if (!filefiles)
      iCurrentFile = 0;
    if (iCurrentFile < topfile)
      topfile -= 3;
    if (iCurrentFile >= topfile + 18)
      topfile += 3;
    szDestPtr = selectfilename;
    szSourcePtr = filename[iCurrentFile];
    filefile = iCurrentFile;
    do {
      byChar1 = *szSourcePtr;
      *szDestPtr = *szSourcePtr;
      if (!byChar1)
        break;
      byChar2 = szSourcePtr[1];
      szSourcePtr += 2;
      szDestPtr[1] = byChar2;
      szDestPtr += 2;
    } while (byChar2);
  }
  while (fatkbhit())                          // Main keyboard input processing loop
  {
    byKeyCode = fatgetch();
    byProcessedKey = byKeyCode;
    if (byKeyCode) {
      if ((uint8)byKeyCode < 0xDu) {
        if (byKeyCode == 8) {
          uiBackspaceLen = (uint32)strlen(selectfilename) + 1;
          if ((int)(uiBackspaceLen - 1) > 0)
            selectfilename[strlen(selectfilename) - 1] = 0;
            //filesel_variable_1[uiBackspaceLen - 1] = 0;
        } else {
        LABEL_85:
          if ((uint8)byKeyCode > 0x39u)
            byProcessedKey = byKeyCode & 0xDF;
          iInputStrLen = (uint32)strlen(selectfilename);
          if (iInputStrLen <= 7
            && ((uint8)byProcessedKey >= 0x41u && (uint8)byProcessedKey <= 0x5Au
                || (uint8)byProcessedKey >= 0x30u && (uint8)byProcessedKey <= 0x39u)) {
            selectfilename[iInputStrLen] = byProcessedKey;
            selectfilename[iInputStrLen + 1] = 0;
          }
        }
      } else if ((uint8)byKeyCode <= 0xDu) {
        sfxsample(83, 0x8000);
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
            continue;                           // Execute action based on filing menu mode (1=Load, 2=Save, 3=Delete, 4=Assemble)
        }
      } else {
        if (byKeyCode != 27)
          goto LABEL_85;
        filingmenu = 0;
        disciconpressed = 0;
        rotpoint = currentreplayframe;
      }
    } else {
      switch ((uint8)fatgetch()) {
        case 'H':
          iUpNavFile = filefile - 3;
          if (filefile - 3 < 0)
            iUpNavFile = 0;
          if (!filefiles)
            iUpNavFile = 0;
          if (iUpNavFile < topfile)
            topfile -= 3;
          if (iUpNavFile >= topfile + 18)
            topfile += 3;
          szUpDestPtr = selectfilename;
          szUpSourcePtr = filename[iUpNavFile];
          filefile = iUpNavFile;
          do {
            byUpChar1 = *szUpSourcePtr;
            *szUpDestPtr = *szUpSourcePtr;
            if (!byUpChar1)
              break;
            byUpChar2 = szUpSourcePtr[1];
            szUpSourcePtr += 2;
            szUpDestPtr[1] = byUpChar2;
            szUpDestPtr += 2;
          } while (byUpChar2);
          break;
        case 'K':
          iLeftNavFile = filefile - 1;
          if (filefile - 1 < 0)
            iLeftNavFile = 0;
          if (!filefiles)
            iLeftNavFile = 0;
          if (iLeftNavFile < topfile)
            topfile -= 3;
          if (iLeftNavFile >= topfile + 18)
            topfile += 3;
          szLeftDestPtr = selectfilename;
          szLeftSourcePtr = filename[iLeftNavFile];
          filefile = iLeftNavFile;
          do {
            byLeftChar1 = *szLeftSourcePtr;
            *szLeftDestPtr = *szLeftSourcePtr;
            if (!byLeftChar1)
              break;
            byLeftChar2 = szLeftSourcePtr[1];
            szLeftSourcePtr += 2;
            szLeftDestPtr[1] = byLeftChar2;
            szLeftDestPtr += 2;
          } while (byLeftChar2);
          break;
        case 'M':
          iRightNavFile = filefile + 1;
          if (filefile + 1 >= filefiles)
            iRightNavFile = filefiles - 1;
          if (!filefiles)
            iRightNavFile = 0;
          if (iRightNavFile < topfile)
            topfile -= 3;
          if (iRightNavFile >= topfile + 18)
            topfile += 3;
          szRightDestPtr = selectfilename;
          szRightSourcePtr = filename[iRightNavFile];
          filefile = iRightNavFile;
          do {
            byRightChar1 = *szRightSourcePtr;
            *szRightDestPtr = *szRightSourcePtr;
            if (!byRightChar1)
              break;
            byRightChar2 = szRightSourcePtr[1];
            szRightSourcePtr += 2;
            szRightDestPtr[1] = byRightChar2;
            szRightDestPtr += 2;
          } while (byRightChar2);
          break;
        case 'P':
          iDownNavFile = filefile + 3;
          if (filefile + 3 >= filefiles)
            iDownNavFile = filefiles - 1;
          if (!filefiles)
            iDownNavFile = 0;
          if (iDownNavFile < topfile)
            topfile -= 3;
          if (iDownNavFile >= topfile + 18)
            topfile += 3;
          szDownDestPtr = selectfilename;
          szDownSourcePtr = filename[iDownNavFile];
          filefile = iDownNavFile;
          do {
            byDownChar1 = *szDownSourcePtr;
            *szDownDestPtr = *szDownSourcePtr;
            if (!byDownChar1)
              break;
            byDownChar2 = szDownSourcePtr[1];
            szDownSourcePtr += 2;
            szDownDestPtr[1] = byDownChar2;
            szDownDestPtr += 2;
          } while (byDownChar2);
          break;
        case 'S':
          uiDelStrLen = (uint32)strlen(selectfilename) + 1;
          if ((int)(uiDelStrLen - 1) > 0)
            selectfilename[strlen(selectfilename) - 1] = 0;
            //filesel_variable_1[uiDelStrLen - 1] = 0;// reference into selectfilename
          break;
        default:
          continue;                             // Handle arrow key navigation (H=Up, K=Left, M=Right, P=Down, S=Delete)
      }
    }
  }
  iRightEdge = iLeftEdge + 20;
  iDisplayFile = filefile;
  iLoopCounter = 0;
  iBottomEdge = iTextY + 20;
  do {
    filefile = iDisplayFile;                    // Display up to 18 files in a 3x6 grid layout
    if (iLoopCounter + topfile < filefiles) {
      iDisplayX = 100 * (iLoopCounter % 3) + iRightEdge;
      iDisplayY = iBottomEdge + 10 * (iLoopCounter / 3);
      szDisplayName = &filename[iLoopCounter][9 * topfile];
      if (iLoopCounter == iDisplayFile - topfile)
        prt_string(rev_vga[1], szDisplayName, iDisplayX, iDisplayY);
      else
        prt_stringcol(rev_vga[1], szDisplayName, iDisplayX, iDisplayY, 131);
    }
    ++iLoopCounter;
    iDisplayFile = filefile;
  } while (iLoopCounter < 18);
  if (iEditMode) {
    uiCursorLen = (uint32)strlen(selectfilename) + 1;
    uiCursorPos = uiCursorLen - 1;
    if (frames % 18 >= 9)                     // Animate blinking cursor for filename input (shows underscore every 9 frames)
    {
      selectfilename[uiCursorPos] = 0;
    } else {
      selectfilename[uiCursorPos] = 95;
      selectfilename[uiCursorPos + 1] = 0;
    }
    prt_stringcol(rev_vga[1], selectfilename, iLeftEdge + 20, iTextY + 100, 255);
    selectfilename[uiCursorLen - 1] = 0;
  }
  if (SVGA_ON)
    iScreenWidth = 640;
  else
    iScreenWidth = 320;
  iUpArrowX = iTextX + 128;
  if (topfile)                                // Draw scroll up/down arrows based on current position in file list
    replayicon(scrbuf, rev_vga[15], 79, iUpArrowX, iTextY - 3, iScreenWidth, 255);
  else
    replayicon(scrbuf, rev_vga[15], 78, iUpArrowX, iTextY - 3, iScreenWidth, 255);
  iDownArrowX = iTextX + 128;
  if (topfile + 18 >= filefiles)
    replayicon(scrbuf, rev_vga[15], 80, iDownArrowX, iTextY + 82, iScreenWidth, 255);
  else
    replayicon(scrbuf, rev_vga[15], 81, iDownArrowX, iTextY + 82, iScreenWidth, 255);
  if (!filefiles)                             // Show 'no files found' message if directory is empty
    prt_centrecol(rev_vga[1], &language_buffer[3328], iTextX, iTextY + 44, 143);
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
void loadreplay()
{
  char *szSrc; // esi
  char *szDst; // edi
  char byChar1; // al
  char byChar2; // al
  char *szExt; // esi
  char *szExtDst; // edi
  char byExtChar1; // al
  char byExtChar2; // al

  holdmusic = -1;                               // Set initial flags for replay loading
  loading_replay = -1;
  filingmenu = 0;
  if (filefiles)                              // If files are available for replay loading
  {
    play_game_uninit();
    strcpy(replayfilename, "..\\REPLAYS\\");    // Start building replay file path with base directory
    szSrc = selectfilename;                     // Manually copy selected filename to replay path (2 chars at a time)
    szDst = &replayfilename[strlen(replayfilename)];
    do {
      byChar1 = *szSrc;
      *szDst = *szSrc;
      if (!byChar1)
        break;
      byChar2 = szSrc[1];
      szSrc += 2;
      szDst[1] = byChar2;
      szDst += 2;
    } while (byChar2);
    szExt = g_szGss;                            // Append file extension to complete replay filename
    szExtDst = &replayfilename[strlen(replayfilename)];
    do {
      byExtChar1 = *szExt;
      *szExtDst = *szExt;
      if (!byExtChar1)
        break;
      byExtChar2 = szExt[1];
      szExt += 2;
      szExtDst[1] = byExtChar2;
      szExtDst += 2;
    } while (byExtChar2);
    replaytype = 2;                             // Initialize replay playback parameters
    //_disable();                                 // Disable interrupts while setting time-critical replay state
    replayspeed = 0;
    fraction = 0;
    replaydirection = 0;
    ticks = currentreplayframe;
    //_enable();
    play_game_init();
    pend_view_init = ViewType[0];
  }
  screenready = 0;                              // Clear screen and loading flags to complete initialization
  lagdone = 0;
  holdmusic = 0;
  loading_replay = 0;
}

//-------------------------------------------------------------------------------------------------
//00067CF0
void savereplay()
{
  uint8 *pbyBuffer; // ebp
  char *szSrc1; // esi
  char *szDst1; // edi
  char byChar1_1; // al
  char byChar2_1; // al
  char *szExtSrc1; // esi
  char *szExtDst1; // edi
  char byExtChar1_1; // al
  char byExtChar2_1; // al
  char *szSrc2; // esi
  char *szDst2; // edi
  char byChar1_2; // al
  char byChar2_2; // al
  char *szExtSrc2; // esi
  char *szExtDst2; // edi
  char byExtChar1_2; // al
  char byExtChar2_2; // al
  unsigned int uiBytesRead; // edi
  int iError; // eax
  int iErrorCopy; // edi
  char szTempFilename[32]; // [esp+0h] [ebp-48h] BYREF
  int iFilePos; // [esp+20h] [ebp-28h]
  int iErrorNum; // [esp+24h] [ebp-24h]
  FILE *pFile; // [esp+28h] [ebp-20h]
  int iErrorFlag; // [esp+2Ch] [ebp-1Ch]

  iErrorFlag = 0;                               // Initialize error flag and buffer pointer
  pbyBuffer = scrbuf;
  if (!strcmp(replayfilename, "..\\REPLAYS\\REPLAY.TMP"))// Check if currently working with temporary replay file
  {
    ftell(replayfile);                          // Finalize temp replay: close file and rename to permanent location
    fclose(replayfile);
    strcpy(replayfilename, "..\\REPLAYS\\");    // Build final replay filename: path + selected name + extension
    szSrc1 = selectfilename;                    // Copy selected filename to replay path (2 chars at a time)
    szDst1 = &replayfilename[strlen(replayfilename)];
    do {
      byChar1_1 = *szSrc1;
      *szDst1 = *szSrc1;
      if (!byChar1_1)
        break;
      byChar2_1 = szSrc1[1];
      szSrc1 += 2;
      szDst1[1] = byChar2_1;
      szDst1 += 2;
    } while (byChar2_1);
    szExtSrc1 = g_szGss;                        // Append file extension to complete the filename
    szExtDst1 = &replayfilename[strlen(replayfilename)];
    do {
      byExtChar1_1 = *szExtSrc1;
      *szExtDst1 = *szExtSrc1;
      if (!byExtChar1_1)
        break;
      byExtChar2_1 = szExtSrc1[1];
      szExtSrc1 += 2;
      szExtDst1[1] = byExtChar2_1;
      szExtDst1 += 2;
    } while (byExtChar2_1);
    ROLLERremove(replayfilename);                     // Remove existing file and rename temp to final name
    rename("..\\REPLAYS\\REPLAY.TMP", replayfilename);
    replayfile = ROLLERfopen(replayfilename, "rb");
    fseek(replayfile, 0, 0);
  } else {
    strcpy(szTempFilename, "..\\REPLAYS\\");    // Handle non-temp replay: copy current replay to new filename
    szSrc2 = selectfilename;                    // Build target filename: path + selected name + extension
    szDst2 = &szTempFilename[strlen(szTempFilename)];
    do {
      byChar1_2 = *szSrc2;
      *szDst2 = *szSrc2;
      if (!byChar1_2)
        break;
      byChar2_2 = szSrc2[1];
      szSrc2 += 2;
      szDst2[1] = byChar2_2;
      szDst2 += 2;
    } while (byChar2_2);
    szExtSrc2 = g_szGss;
    szExtDst2 = &szTempFilename[strlen(szTempFilename)];
    do {
      byExtChar1_2 = *szExtSrc2;
      *szExtDst2 = *szExtSrc2;
      if (!byExtChar1_2)
        break;
      byExtChar2_2 = szExtSrc2[1];
      szExtSrc2 += 2;
      szExtDst2[1] = byExtChar2_2;
      szExtDst2 += 2;
    } while (byExtChar2_2);
    if (strcmp(szTempFilename, replayfilename))// Only copy if target filename is different from current
    {
      pFile = ROLLERfopen(szTempFilename, "wb");      // Open target file for writing and prepare for copy operation
      if (pFile) {
        iFilePos = ftell(replayfile);
        fseek(replayfile, 0, 0);
        iErrorFlag = 0;                         // Copy file in chunks with error checking
        do {
          uiBytesRead = (uint32)fread(pbyBuffer, 1u, 0xFA00u, replayfile);
          if (fwrite(pbyBuffer, 1, uiBytesRead, pFile) != uiBytesRead) {
            iError = errno;// *(_DWORD *)_get_errno_ptr();// Handle write error - set error flag and save errno
            iErrorFlag = -1;
            iErrorNum = iError;
          }
        } while (uiBytesRead && !iErrorFlag);
        iErrorCopy = iErrorFlag;
        fclose(pFile);                          // Cleanup: close file, remove on error, restore file position
        if (iErrorCopy)
          ROLLERremove(szTempFilename);
        fseek(replayfile, iFilePos, 0);
        ticks = currentreplayframe;
      }
    }
  }
  filingmenu = 0;                               // Reset menu flags and screen state
  lastfile = 0;
  screenready = 0;
  if (iErrorFlag)                             // Set appropriate error menu state based on error type
  {
    if (iErrorNum == 12)
      filingmenu = 6;
    else
      filingmenu = 7;
  }
}

//-------------------------------------------------------------------------------------------------
//00067F50
void deletereplay()
{
  char *szSrc; // esi
  char *szDst; // edi
  char byChar1; // al
  char byChar2; // al
  char *szExtSrc; // esi
  char *szExtDst; // edi
  char byExtChar1; // al
  char byExtChar2; // al
  char *szTmpDst; // edi
  const char *szTmpSrc; // esi
  char byTmpChar1; // al
  char byTmpChar2; // al
  char szTargetFilename[40]; // [esp-30h] [ebp-34h] BYREF

  strcpy(szTargetFilename, "..\\REPLAYS\\");    // Build target filename: path + selected filename + extension
  szSrc = selectfilename;                       // Copy selected filename to path (2 chars at a time)
  szDst = &szTargetFilename[strlen(szTargetFilename)];
  do {
    byChar1 = *szSrc;
    *szDst = *szSrc;
    if (!byChar1)
      break;
    byChar2 = szSrc[1];
    szSrc += 2;
    szDst[1] = byChar2;
    szDst += 2;
  } while (byChar2);
  szExtSrc = g_szGss;                           // Append file extension to complete target filename
  szExtDst = &szTargetFilename[strlen(szTargetFilename)];
  do {
    byExtChar1 = *szExtSrc;
    *szExtDst = *szExtSrc;
    if (!byExtChar1)
      break;
    byExtChar2 = szExtSrc[1];
    szExtSrc += 2;
    szExtDst[1] = byExtChar2;
    szExtDst += 2;
  } while (byExtChar2);
  if (!strcmp(replayfilename, szTargetFilename))// Check if deleting the currently loaded replay file
  {
    ROLLERremove("..\\REPLAYS\\REPLAY.TMP");          // Deleting current replay: cleanup temp files and swap to temp
    ftell(replayfile);                          // Close current replay file and rename target to temp
    szTmpDst = replayfilename;
    fclose(replayfile);
    szTmpSrc = "..\\REPLAYS\\REPLAY.TMP";       // Copy temp filename to current replayfilename (2 chars at a time)
    ROLLERrename(szTargetFilename, "..\\REPLAYS\\REPLAY.TMP");
    do {
      byTmpChar1 = *szTmpSrc;
      *szTmpDst = *szTmpSrc;
      if (!byTmpChar1)
        break;
      byTmpChar2 = szTmpSrc[1];
      szTmpSrc += 2;
      szTmpDst[1] = byTmpChar2;
      szTmpDst += 2;
    } while (byTmpChar2);
    replayfile = ROLLERfopen(replayfilename, "rb");   // Reopen temp file as current replay
    fseek(replayfile, 0, 0);
  } else {
    ROLLERremove(szTargetFilename);                   // Not current replay: simple file deletion
  }
  ticks = currentreplayframe;                   // Reset replay state and clear menu flags
  filingmenu = 0;
  lastfile = 0;
}

//-------------------------------------------------------------------------------------------------
//00068070
void updatedirectory()
{
  int iNewTopFile; // edx
  char *szDst; // edi
  char *szSrc; // esi
  char byChar1; // al
  char byChar2; // al

  iNewTopFile = topfile;                        // Initialize with current top file position
  if (!filefiles)                             // If no files available, reset current file selection
    filefile = 0;
  if (filefile < topfile)                     // If selected file is above view window, scroll up 3 positions
    iNewTopFile = topfile - 3;
  if (iNewTopFile + 18 <= filefile)           // If selected file is below view window (18 files visible), scroll down 3 positions
    iNewTopFile += 3;
  szDst = selectfilename;                       // Copy currently selected filename to selectfilename buffer (2 chars at a time)
  szSrc = filename[filefile];
  topfile = iNewTopFile;                        // Update top file position for scrolled view
  do {
    byChar1 = *szSrc;
    *szDst = *szSrc;
    if (!byChar1)
      break;
    byChar2 = szSrc[1];
    szSrc += 2;
    szDst[1] = byChar2;
    szDst += 2;
  } while (byChar2);
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
void displaycontrolpanel()
{
  int iScreenWidth; // ebp
  int iIconOffset; // eax
  int iCalculatedFrame; // edi
  int iFrameLoop; // eax
  int iFrameLoop2; // eax
  int iRotateIndex; // eax
  int iRotateLoop; // esi
  int iRotateX; // ecx
  int iCurrentCut; // ebx
  int iCutLoop; // eax
  int iCutIndex; // edx
  const char *pEditString; // eax
  int iRotateY; // [esp-Ch] [ebp-48h]
  int iEndFrame; // [esp+4h] [ebp-38h]
  int iStartFrame; // [esp+8h] [ebp-34h]
  int iRotateLimit; // [esp+18h] [ebp-24h]

  if (SVGA_ON) {
    iScreenWidth = 640;
    replayicon(scrbuf, rev_vga[15], 0, 0, 150, 640, -1);
  } else {
    iScreenWidth = 320;
    replayicon(scrbuf, rev_vga[15], 0, 0, 150, 320, -1);
  }
  if (!replayedit)                            // Draw control panel overlay if not in replay edit mode
    replayicon(scrbuf, rev_vga[15], 77, 117, 187, iScreenWidth, -1);
  if (!keys[28] || paused || (iIconOffset = -1, controlicon == 18) && !replayselect)// Calculate icon offset: -1 if ENTER pressed and conditions met, 0 otherwise
    iIconOffset = 0;
  replayicon(scrbuf, rev_vga[15], controlicon, ricon[controlicon].nX, ricon[controlicon].nY + 150 + iIconOffset, iScreenWidth, -1);// Draw current control icon with calculated offset
  if (replayspeed > 0 && !forwarding && !rewinding)// Draw fast forward indicators when replay speed is positive
  {
    if (controlicon == 4)
      replayicon(scrbuf, rev_vga[15], 4, ricon[4].nX, ricon[4].nY + 149, iScreenWidth, -1);
    else
      replayicon(scrbuf, rev_vga[15], 27, ricon[4].nX, ricon[4].nY + 149, iScreenWidth, -1);
  }
  if (replayspeed < 0 && !forwarding && !rewinding)// Draw rewind indicators when replay speed is negative
  {
    if (controlicon == 3)
      replayicon(scrbuf, rev_vga[15], 3, ricon[3].nX, ricon[3].nY + 149, iScreenWidth, -1);
    else
      replayicon(scrbuf, rev_vga[15], 26, ricon[3].nX, ricon[3].nY + 149, iScreenWidth, -1);
  }
  if (replayedit)                             // Draw edit mode indicator icon
  {
    if (controlicon == 17)
      replayicon(scrbuf, rev_vga[15], 17, ricon[17].nX, ricon[17].nY + 149, iScreenWidth, -1);
    else
      replayicon(scrbuf, rev_vga[15], 28, ricon[17].nX, ricon[17].nY + 149, iScreenWidth, -1);
  }
  if (replayselect)                           // Draw replay selection mode indicator icon
  {
    if (controlicon == 18)
      replayicon(scrbuf, rev_vga[15], 18, ricon[18].nX, ricon[18].nY + 149, iScreenWidth, -1);
    else
      replayicon(scrbuf, rev_vga[15], 29, ricon[18].nX, ricon[18].nY + 149, iScreenWidth, -1);
  }
  if (disciconpressed)                        // Draw disc icon when pressed
    replayicon(scrbuf, rev_vga[15], 16, ricon[16].nX, ricon[17].nY + 149, iScreenWidth, -1);
  replaypanelstring(replayhelp[controlicon], 255, 165, iScreenWidth);// Display help text for current control icon
  if (replayedit)                             // EDIT MODE: Display edit mode information panel
  {
    replaypanelstring("CURRENT:", 164, 165, iScreenWidth);// Show current edit info text
    sprintf(buffer, "CAR %d", ViewType[0] + 1); // Display current car number being viewed
    replaypanelstring(buffer, 199, 165, iScreenWidth);
    replaypanelstring(views[SelectedView[0]], 225, 165, iScreenWidth);// Display current camera view type
    if (cuts)                                 // Process camera cuts if they exist
    {
      iCurrentCut = -1;
      iCutLoop = 0;
      if (cuts > 0) {
        iCutIndex = 0;                          // Find the current active camera cut based on replay frame
        do {
          if (currentreplayframe >= camera[iCutIndex].iFrame)
            iCurrentCut = iCutLoop;
          ++iCutLoop;
          ++iCutIndex;
        } while (iCutLoop < cuts);
      }
      if (iCurrentCut != -1)                  // Display camera cut information if one is active
      {                                         // Show different text for exact frame match vs approximate
        if (camera[iCurrentCut].iFrame == currentreplayframe)
          pEditString = g_szNewEdit;
        else
          pEditString = g_szEdit;
        replaypanelstring(pEditString, 164, 171, iScreenWidth);
        sprintf(buffer, "CAR %d", camera[iCurrentCut].byCarIdx + 1);
        replaypanelstring(buffer, 199, 171, iScreenWidth);
        replaypanelstring(views[camera[iCurrentCut].byView], 225, 171, iScreenWidth);
      }
    }
    if (replayselect)                         // Display selection range if in replay select mode
    {                                           // Order start and end frames correctly for display
      if (replaystart >= currentreplayframe) {
        iStartFrame = currentreplayframe;
        iEndFrame = replaystart;
      } else {
        iStartFrame = replaystart;
        iEndFrame = currentreplayframe;
      }
      replaypanelstring("BLOCK:", 164, 159, iScreenWidth);// Display selection block text and time range
      displaypaneltime(iStartFrame, 189, 159, iScreenWidth);
      displaypaneltime(iEndFrame, 223, 159, iScreenWidth);
      replaypanelstring("-", 218, 159, iScreenWidth);
    } else {
      displaypaneltime(currentreplayframe, 223, 159, iScreenWidth);// Just show current time when not selecting
    }
  } else {
    sprintf(buffer, "X %s", replayname[replaysetspeed]);// NORMAL MODE: Display speed multiplier and status icons
    replaypanelstring(buffer, 229, 165, iScreenWidth);
    displaypaneltime(currentreplayframe, 223, 159, iScreenWidth);// Display current replay time
    if (replayspeed > 0 && !forwarding && !rewinding)// Show fast forward icon when playing forward
      replayicon(scrbuf, rev_vga[15], 73, 164, 161, iScreenWidth, 255);
    if (replayspeed < 0 && !forwarding && !rewinding)// Show rewind icon when playing backward
      replayicon(scrbuf, rev_vga[15], 72, 164, 161, iScreenWidth, 255);
    if (forwarding && replayspeed > 0)        // Show fast forward icon when actively fast forwarding
      replayicon(scrbuf, rev_vga[15], 71, 164, 161, iScreenWidth, 255);
    if (rewinding && replayspeed < 0)         // Show rewind icon when actively rewinding
      replayicon(scrbuf, rev_vga[15], 70, 164, 161, iScreenWidth, 255);
    if (!replayspeed)                         // Show pause icon when replay speed is zero
      replayicon(scrbuf, rev_vga[15], 74, 164, 161, iScreenWidth, 255);
    replayicon(scrbuf, rev_vga[15], 75, 190, 161, iScreenWidth, 255);// Draw progress bar background
    if (currentreplayframe <= rotpoint)       // Calculate position for progress bar indicators
    {                                           // Current frame is before rotation point
      if (rotpoint - currentreplayframe > 24) {
        iCalculatedFrame = rotpoint - 24;
        for (iFrameLoop2 = rotpoint - 152; iFrameLoop2 >= currentreplayframe; iCalculatedFrame -= 64)
          iFrameLoop2 -= 64;
      } else {
        iCalculatedFrame = currentreplayframe;
      }
    } else if (currentreplayframe - rotpoint > 24)// Current frame is after rotation point
    {
      iCalculatedFrame = rotpoint + 24;
      for (iFrameLoop = rotpoint + 152; iFrameLoop <= currentreplayframe; iCalculatedFrame += 64)
        iFrameLoop += 64;
    } else {
      iCalculatedFrame = currentreplayframe;
    }
    iRotateIndex = iCalculatedFrame / 8;  // Calculate rotation index for progress bar markers
    //iRotateIndex = (iCalculatedFrame - (__CFSHL__(iCalculatedFrame >> 31, 3) + 8 * (iCalculatedFrame >> 31))) >> 3;// Calculate rotation index for progress bar markers
    rotpoint = iCalculatedFrame;
    iRotateLoop = iRotateIndex;
    iRotateLimit = iRotateIndex + 3;

    do {
      iRotateY = rrotate[iRotateLoop % 8].y + 150;
      iRotateX = rrotate[iRotateLoop % 8].x;
      ++iRotateLoop;
      replayicon(scrbuf, rev_vga[15], 76, iRotateX, iRotateY, iScreenWidth, 255);
    } while (iRotateLoop < iRotateLimit);
  }
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
void replayicon(uint8 *pDest, tBlockHeader *pBlockHeader, int iBlockIdx, int iX, int iY, int iScreenWidth, int byTransparentColor)
{
  int iScaledDestY; // edx
  uint8 *pDestPixel; // eax
  tBlockHeader *pSpriteHeader; // edx
  uint8 *pSpritePixels; // edx
  int iCurrentX; // esi
  int iPixelX; // ebp
  uint8 byPixelColor; // cl
  int iSvgaCurrentX; // esi
  uint8 bySvgaPixelColor; // cl
  uint8 *pNextLineStart; // ebp
  uint8 *pTempPixel1; // eax
  uint8 *pTempPixel2; // ebp
  uint8 *pTempPixel3; // eax
  uint8 *pTempPixel4; // ebp
  int iHeight; // [esp+Ch] [ebp-2Ch]
  int iScaledDestX; // [esp+10h] [ebp-28h]
  int iCurrentRow; // [esp+14h] [ebp-24h]
  int iRowLoop; // [esp+18h] [ebp-20h]
  int iWidth; // [esp+1Ch] [ebp-1Ch]
  uint8 *pSvgaNextLine; // [esp+20h] [ebp-18h]
  int iSvgaPixelX; // [esp+24h] [ebp-14h]

  iScaledDestX = iX;
  iScaledDestY = iY;
  if (SVGA_ON)                                // If SVGA mode is enabled, scale coordinates by 2x
  {
    iScaledDestY = 2 * iY;
    iScaledDestX = 2 * iX;
  }
  pDestPixel = &pDest[iScaledDestX + iScreenWidth * iScaledDestY];// Calculate destination pixel pointer: buffer + (y * width) + x
  iWidth = pBlockHeader[iBlockIdx].iWidth;      // Get sprite width from sprite data header (offset 0)
  pSpriteHeader = &pBlockHeader[iBlockIdx];
  iHeight = pSpriteHeader->iHeight;             // Get sprite height from sprite data header (offset 4)
  pSpritePixels = (uint8 *)pBlockHeader + pSpriteHeader->iDataOffset;// Get pointer to sprite pixel data (offset 8)

  // Branch to SVGA rendering path (2x2 pixel scaling)
  if (SVGA_ON) {
    iCurrentRow = 0;                            // SVGA mode: outer loop for sprite rows with 2x scaling
    if (iHeight <= 0)
      return;
    while (1) {
      iSvgaCurrentX = iScaledDestX;
      iSvgaPixelX = 0;
      if (iWidth > 0)
        break;
    SVGA_NEXT_ROW:
          // SVGA: Move to next row, skip unused portion of screen line
      pDestPixel += 2 * (iScreenWidth - iWidth);// SVGA_NEXT_ROW: Advance to next sprite row and check completion
      if (++iCurrentRow >= iHeight)
        return;
    }
    while (1)                                 // SVGA mode: inner loop for sprite pixels with 2x2 scaling
    {
      bySvgaPixelColor = *pSpritePixels++;
      if (iSvgaCurrentX < 0 || iSvgaCurrentX >= iScreenWidth)
        break;                                  // SVGA bounds check
      pNextLineStart = &pDestPixel[iScreenWidth];
      pSvgaNextLine = &pDestPixel[iScreenWidth];

      // Transparency check branch for SVGA mode
      if (byTransparentColor >= 0) {
        if (byTransparentColor == bySvgaPixelColor)
          break;

        // SVGA: Draw 2x2 pixel block (with transparency check)
        *pDestPixel = bySvgaPixelColor;
        pTempPixel3 = pDestPixel + 1;
        *pSvgaNextLine = bySvgaPixelColor;
        pTempPixel4 = &pTempPixel3[iScreenWidth];
        *pTempPixel3 = bySvgaPixelColor;
        pDestPixel = pTempPixel3 + 1;
        *pTempPixel4 = bySvgaPixelColor;
      } else {

        // SVGA: Draw 2x2 pixel block (no transparency check)
        *pDestPixel = bySvgaPixelColor;
        pTempPixel1 = pDestPixel + 1;
        *pNextLineStart = bySvgaPixelColor;
        pTempPixel2 = &pTempPixel1[iScreenWidth];
        *pTempPixel1 = bySvgaPixelColor;
        pDestPixel = pTempPixel1 + 1;
        *pTempPixel2 = bySvgaPixelColor;
      }
    SVGA_NEXT_PIXEL:
      iSvgaCurrentX += 2;                       // SVGA_NEXT_PIXEL: Advance to next pixel in current row (2x scaling)
      if (++iSvgaPixelX >= iWidth)
        goto SVGA_NEXT_ROW;
    }
    pDestPixel += 2;
    goto SVGA_NEXT_PIXEL;
  }

  // Standard VGA rendering loop - iterate through sprite rows
  for (iRowLoop = 0; iRowLoop < iHeight; ++iRowLoop) {
    iCurrentX = iScaledDestX;
    // Inner loop - iterate through sprite pixels in current row
    for (iPixelX = 0; iPixelX < iWidth; ++pDestPixel) {
      byPixelColor = *pSpritePixels++;

      // Check bounds and transparency: skip if out of bounds or matches transparent color
      if (iCurrentX >= 0 && iCurrentX < iScreenWidth && (byTransparentColor < 0 || byTransparentColor != byPixelColor))
        *pDestPixel = byPixelColor;
      ++iCurrentX;
      ++iPixelX;
    }

    // Move to next row: advance pointer by (screen_width - sprite_width)
    pDestPixel += iScreenWidth - iWidth;
  }
}

//-------------------------------------------------------------------------------------------------
//00068EF0
void replaypanelletter(char c, int *piX, int *piY, int iScreenWidth)
{
  int iCharBlockIdx; // esi

  iCharBlockIdx = -1;
  if (c >= '0' && c <= '9')
    iCharBlockIdx = c - 18;
  if (c >= 'A' && c <= 'Z')
    iCharBlockIdx = c - 25;
  if (c == '-')
    iCharBlockIdx = 66;
  if (c == ':')
    iCharBlockIdx = 67;
  if (c == '/')
    iCharBlockIdx = 68;
  if (c == '?')
    iCharBlockIdx = 69;
  if (iCharBlockIdx != -1) {
    replayicon(scrbuf, rev_vga[15], iCharBlockIdx, *piX, *piY, iScreenWidth, 255);
    *piX += rev_vga[15][iCharBlockIdx].iWidth + 1;
  }
}

//-------------------------------------------------------------------------------------------------
//00068F80
void replaypanelstring(const char *szStr, int iX, int iY, int iScreenWidth)
{
  const char *szStrItr; // esi
  unsigned int i; // ebp
  int iXPos; // [esp+4h] [ebp-1Ch] BYREF
  int iYPos; // [esp+8h] [ebp-18h] BYREF
  int iScreenWidth_1; // [esp+Ch] [ebp-14h]
  const char *szGetStrLen; // [esp+10h] [ebp-10h]

  szGetStrLen = szStr;
  iXPos = iX;
  iYPos = iY;
  iScreenWidth_1 = iScreenWidth;
  szStrItr = szStr;
  for (i = 0; i < strlen(szGetStrLen); ++i) {
    if (*szStrItr == '|') {
      iXPos = iX;
      iYPos += 6;
    } else if (*szStrItr == ' ') {
      iXPos += 2;
    } else {
      replaypanelletter(*szStrItr, &iXPos, &iYPos, iScreenWidth_1);
    }
    ++szStrItr;
  }
}

//-------------------------------------------------------------------------------------------------
//00069000
void displaypaneltime(int iTime, int iX, int iY, int iScreenWidth)
{
  sprintf(buffer, "%02d:%02d:%02d", iTime / 36 / 60, iTime / 36 % 60, iTime % 36);
  replaypanelstring(buffer, iX, iY, iScreenWidth);
}

//-------------------------------------------------------------------------------------------------
//00069080
void discmenu()
{
  sfxsample(SOUND_SAMPLE_BUTTON, 0x8000);                        // SOUND_SAMPLE_BUTTON
  lsdsel = 0;
  disciconpressed = -1;
  filingmenu = 5;
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

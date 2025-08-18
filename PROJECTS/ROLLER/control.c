#include "control.h"
#include "view.h"
#include "loadtrak.h"
#include "sound.h"
#include "function.h"
#include "transfrm.h"
#include "moving.h"
#include "network.h"
#include "func2.h"
#include "replay.h"
#include "colision.h"
#include <math.h>
#include <float.h>
//-------------------------------------------------------------------------------------------------

float levels[7] = { 100.0, 97.0, 94.0, 90.0, 85.0, 80.0, -1.0 }; //000A4290
int level = 3;                    //000A42DC
int carorder[16];                 //00149790
int stops[10];                    //001497D0
float trial_times[96];            //001497F8
float eng_chg_revs[168];          //00149978
int FirstTick;                    //00149C18
int JBYmax;                       //00149C24
int JBYmin;                       //00149C30
int JBXmin;                       //00149C34
int JBXmax;                       //00149C3C
int JAYmax;                       //00149C40
int JAXmax;                       //00149C44
int numstops;                     //00149C48
int JAYmin;                       //00149C4C
int JAXmin;                       //00149C50
int race_started;                 //00149C54
int updates;                      //00149C58
float RecordLaps[25];             //00149C5C
int RecordCars[25];               //00149CC0
int RecordKills[25];              //00149D24
int Destroyed;                    //00149D8C
int nearcarcheck;                 //00149D90
int ahead_sect;                   //00149D94
int ahead_time;                   //00149D98
int Fatality;                     //00149DB0
int Fatality_Count;               //00149DB4
int cheat_control;                //00149DB8
int fudge_wait;                   //00149DC4
char RecordNames[25][9];          //00149DC8

//-------------------------------------------------------------------------------------------------
//00029640
void humancar(int iCarIdx)
{
  int iTrakLen; // ebp
  int iInput; // eax
  int iSteeringInput; // edi
  uint16 unFlags; // ax
  int byCarDesignIdx; // esi
  int iFinisherCount; // edx
  int iCarIndex1; // ecx
  int iCarIndex2; // eax
  uint8 byCheatAmmo_1; // bl
  int iCurrentChunk; // eax
  int iColorIndex; // edx
  int iTrackColor1; // ecx
  int iTrackColor2; // esi
  int iTrackColor3; // ecx
  uint8 byNewCheatAmmo; // ch
  uint8 byCheatAmmo; // bh
  int iSoundEffect1; // eax
  int iTargetCarIdx; // eax
  int iTargetCar1; // edx
  int iTargetCar2; // edx
  int iPlayerIdx; // eax
  uint8 byCheatAmmo_2; // bh
  int iSoundEffect2; // eax
  int iJumpTargetIdx; // eax
  int iJumpTarget; // ebx
  int iJumpTargetCar; // eax
  int iTargetCarDesign; // ecx
  double dNewZ; // st7
  uint8 byCheatAmmo_3; // cl
  int iSoundEffect3; // eax
  int iTeleportTargetIdx; // eax
  int iTeleportTarget; // esi
  int nChunk2; // ecx
  int nPitch; // edx
  int nCurrChunk; // edi
  tVec3 *posAy; // edi
  double dLocalZ; // st7
  float fChunkValue; // eax
  int iPlayerIdx2; // eax
  tCar *pCar; // eax
  int iElevation; // [esp+0h] [ebp-40h] BYREF
  int iAzimuth; // [esp+4h] [ebp-3Ch] BYREF
  int iBank; // [esp+8h] [ebp-38h] BYREF
  float fLocalZ; // [esp+Ch] [ebp-34h]
  int iAzi2; // [esp+10h] [ebp-30h] BYREF
  float fLocalX; // [esp+14h] [ebp-2Ch]
  float fLocalY; // [esp+18h] [ebp-28h]
  int iTeleportTargetIndex; // [esp+1Ch] [ebp-24h]
  int iCarIdx_1; // [esp+20h] [ebp-20h]
  int iControlFlags; // [esp+24h] [ebp-1Ch]

  iTrakLen = TRAK_LEN;                          // Initialize track length and player index
  iCarIdx_1 = iCarIdx;
  iInput = (int16)copy_multiple[readptr][iCarIdx].data.unInput;// Extract steering input and control flags from player input data
  iSteeringInput = iInput / 256;
  //iSteeringInput = (unInput - (__CFSHL__(unInput >> 31, 8) + (unInput >> 31 << 8))) >> 8;
  unFlags = copy_multiple[readptr][iCarIdx_1].data.unFlags;
  byCarDesignIdx = Car[iCarIdx_1].byCarDesignIdx;
  iControlFlags = unFlags;
  //LOWORD(iControlFlags) = unFlags;
  if (byCarDesignIdx < 8)                     // Enable cheat mode for special car designs (8-12), disable for normal cars
    cheat_control = 0;
  else
    cheat_control = unFlags & 0x20;
  if (finished_car[iCarIdx_1] || racers - 1 == finishers && Car[iCarIdx_1].byLap < NoOfLaps && competitors > 1)// Force brake mode if car finished or race is over for this player
    iControlFlags = 2;
    //LOWORD(iControlFlags) = 2;
  //if (racers - 1 == finishers && Car[iCarIdx_1].byLap < NoOfLaps && (LODWORD(Car[iCarIdx_1].fFinalSpeed) & 0x7FFFFFFF) == 0 && competitors > 1)// Handle race finish condition: play finish sounds and mark player as finished
  if (racers - 1 == finishers && Car[iCarIdx_1].byLap < NoOfLaps && fabs(Car[iCarIdx_1].fFinalSpeed) > FLT_EPSILON && competitors > 1)// Handle race finish condition: play finish sounds and mark player as finished
  {
    if (player1_car == iCarIdx_1 || player2_car == iCarIdx_1) {
      if ((char)Car[iCarIdx_1].byLives > 0)
        speechsample(SOUND_SAMPLE_RUBBISH, 0x8000, 18, iCarIdx_1);// SOUND_SAMPLE_RUBBISH
      speechsample(SOUND_SAMPLE_RACEOVER, 0x8000, 18, iCarIdx_1);  // SOUND_SAMPLE_RACEOVER
    }
    iTrakLen = TRAK_LEN;
    iFinisherCount = human_finishers;
    finished_car[iCarIdx_1] = -1;
    human_finishers = iFinisherCount + 1;
    ++finishers;
  }
  if (Car[iCarIdx_1].fHealth <= 0.0)          // Disable controls if car health is zero or below
    iControlFlags = 0;
    //LOWORD(unControlFlags) = 0;
  iCarIndex1 = iCarIdx_1;
  iCarIndex2 = iCarIdx_1;
  Car[iCarIdx_1].iSteeringInput = iSteeringInput;// Store steering input and handle cheat power activation
  if (!cheat_control)
    goto PROCESS_VEHICLE_CONTROLS;
  switch (byCarDesignIdx) {
    case 8:                                     // SUICYCO (explode opponent)
      if (Car[iCarIndex1].byCheatCooldown)    // Car type 8: finds nearest car and applies massive damage
        goto PROCESS_VEHICLE_CONTROLS;
      byCheatAmmo = Car[iCarIndex1].byCheatAmmo;
      TRAK_LEN = iTrakLen;
      if (!byCheatAmmo) {
        if (!cheatsampleok(iCarIndex1))
          goto SET_DAMAGE_COOLDOWN;
        iSoundEffect1 = SOUND_SAMPLE_BLOP;
        goto PLAY_DAMAGE_SOUND;
      }
      if (Car[iCarIndex1].nCurrChunk == -1) {
        if (!cheatsampleok(iCarIndex1))
          goto SET_DAMAGE_COOLDOWN;
        iSoundEffect1 = SOUND_SAMPLE_BRP;
        goto PLAY_DAMAGE_SOUND;
      }
      iTargetCarIdx = findcardistance(iCarIndex1, 8000.0);// Find target car within range (8000 units)
      iTargetCar1 = iTargetCarIdx;
      if (iTargetCarIdx >= 0 && Car[iTargetCarIdx].nCurrChunk != -1 && Car[iTargetCarIdx].byCarDesignIdx != 13) {
        Car[iTargetCarIdx].byAttacker = iCarIdx_1;// Apply damage: 200 damage, stop target car, consume ammo
        Car[iTargetCarIdx].byUnk43 = -40;
        dodamage(&Car[iTargetCarIdx], 200.0);
        Car[iTargetCar1].fFinalSpeed = 0.0;
        Car[iTargetCar1].byGearAyMax = 0;
        Car[iTargetCar1].fBaseSpeed = 0.0;
        Car[iTargetCar1].fSpeedOverflow = 0.0;
        Car[iTargetCar1].fRPMRatio = 0.0;
        iTargetCar2 = iTargetCar1;
        Car[iTargetCar2].fPower = 0.0;
        iPlayerIdx = iCarIdx_1;
        Car[iTargetCar2].nUnk21 = 18;
        --Car[iPlayerIdx].byCheatAmmo;
        goto SET_DAMAGE_COOLDOWN;
      }
      if (cheatsampleok(iCarIdx_1)) {
        iSoundEffect1 = SOUND_SAMPLE_BRP;
      PLAY_DAMAGE_SOUND:
        sfxsample(iSoundEffect1, 0x8000);
      }
    SET_DAMAGE_COOLDOWN:
      iTrakLen = TRAK_LEN;
      Car[iCarIdx_1].byCheatCooldown = 36;      // Set cheat power cooldown (36 frames) after use
      goto PROCESS_VEHICLE_CONTROLS;
    case 9:                                     // MAYTE (top speed)
      iControlFlags = iControlFlags | 1;
      //LOBYTE(unControlFlags) = unControlFlags | 1;
      goto PROCESS_VEHICLE_CONTROLS;
    case 10:                                    // 2X4B523P (flip opponent)
      if (Car[iCarIndex2].byCheatCooldown)
        goto PROCESS_VEHICLE_CONTROLS;
      byCheatAmmo_2 = Car[iCarIndex2].byCheatAmmo;
      TRAK_LEN = iTrakLen;
      if (!byCheatAmmo_2) {
        if (!cheatsampleok(iCarIndex1))
          goto SET_JUMP_COOLDOWN;
        iSoundEffect2 = SOUND_SAMPLE_BLOP;                     // SOUND_SAMPLE_BLOP
        goto PLAY_JUMP_SOUND;
      }
      if (Car[iCarIndex2].nCurrChunk == -1) {
        if (!cheatsampleok(iCarIndex1))
          goto SET_JUMP_COOLDOWN;
      } else {
        iJumpTargetIdx = findcardistance(iCarIndex1, 16000.0);// Find target car within jump range (16000 units)
        iJumpTarget = iJumpTargetIdx;
        if (iJumpTargetIdx >= 0) {
          iJumpTargetCar = iJumpTargetIdx;
          if (Car[iJumpTargetCar].nCurrChunk != -1 && Car[iJumpTargetCar].byCarDesignIdx != 13) {
            iTargetCarDesign = Car[iJumpTargetCar].byCarDesignIdx;// Apply jump effect: launch target car into air with roll and Z-offset
            Car[iJumpTargetCar].nRoll = 0x2000;
            dNewZ = CarBox.hitboxAy[iTargetCarDesign][4].fZ + Car[iJumpTargetCar].pos.fZ;
            Car[iJumpTargetCar].iStunned = -1;
            Car[iJumpTargetCar].iSteeringInput = 0;
            Car[iJumpTargetCar].iJumpMomentum = 2048;
            Car[iJumpTargetCar].pos.fZ = (float)dNewZ;
            if (cheatsampleok(iCarIdx_1))
              sfxsample(SOUND_SAMPLE_BOING, 0x8000);            // SOUND_SAMPLE_BOING
            if (cheatsampleok(iJumpTarget))
              sfxsample(SOUND_SAMPLE_BOING, 0x8000);            // SOUND_SAMPLE_BOING
            --Car[iCarIdx_1].byCheatAmmo;
          SET_JUMP_COOLDOWN:
            iTrakLen = TRAK_LEN;
            Car[iCarIdx_1].byCheatCooldown = 36;
            goto PROCESS_VEHICLE_CONTROLS;
          }
        }
        if (!cheatsampleok(iCarIdx_1))
          goto SET_JUMP_COOLDOWN;
      }
      iSoundEffect2 = SOUND_SAMPLE_BRP;                       // SOUND_SAMPLE_BRP
    PLAY_JUMP_SOUND:
      sfxsample(iSoundEffect2, 0x8000);
      goto SET_JUMP_COOLDOWN;
    case 11:                                    // TINKLE (swap places with opponent)
      if (Car[iCarIndex2].byCheatCooldown)
        goto PROCESS_VEHICLE_CONTROLS;
      byCheatAmmo_3 = Car[iCarIndex2].byCheatAmmo;
      TRAK_LEN = iTrakLen;
      if (!byCheatAmmo_3) {
        if (!cheatsampleok(iCarIdx_1))
          goto SET_TELEPORT_COOLDOWN;
        iSoundEffect3 = SOUND_SAMPLE_BLOP;
        goto PLAY_TELEPORT_SOUND;
      }
      if (Car[iCarIndex2].nCurrChunk == -1) {
        if (!cheatsampleok(iCarIdx_1))
          goto SET_TELEPORT_COOLDOWN;
        goto PLAY_TELEPORT_FAIL_SOUND;
      }
      iTeleportTargetIdx = findcardistance(iCarIdx_1, 16000.0);// Find target car for teleport swap (16000 units)
      iTeleportTargetIndex = iTeleportTargetIdx;
      if (iTeleportTargetIdx < 0 || (iTeleportTarget = iTeleportTargetIdx, Car[iTeleportTargetIdx].nCurrChunk == -1) || Car[iTeleportTargetIdx].byCarDesignIdx == 13) {
        if (!cheatsampleok(iCarIdx_1))
          goto SET_TELEPORT_COOLDOWN;
      PLAY_TELEPORT_FAIL_SOUND:
        iSoundEffect3 = SOUND_SAMPLE_BRP;//SOUND_SAMPLE_BRP
      PLAY_TELEPORT_SOUND:
        sfxsample(iSoundEffect3, 0x8000);
        goto SET_TELEPORT_COOLDOWN;
      }
      Car[iTeleportTargetIdx].iUnk6 = 0;
      nChunk2 = Car[iTeleportTargetIdx].nChunk2;
      Car[iTeleportTargetIdx].iSteeringInput = 0;
      nPitch = Car[iTeleportTargetIdx].nPitch;
      Car[iTeleportTargetIdx].fUnk9 = 128.0f;
      nCurrChunk = Car[iTeleportTargetIdx].nCurrChunk;
      getworldangles(Car[iTeleportTargetIdx].nYaw3, nPitch, Car[iTeleportTargetIdx].nRoll, nChunk2, &iAzimuth, &iElevation, &iBank);// Swap car positions and orientations using world angle transformations
      getworldangles(Car[iTeleportTarget].nYaw, Car[iTeleportTarget].nPitch, Car[iTeleportTarget].nRoll, Car[iTeleportTarget].nChunk2, &iAzi2, &iElevation, &iBank);
      Car[iTeleportTarget].pos.fZ = Car[iTeleportTarget].pos.fZ + 64.0f;
      Car[iTeleportTarget].nYaw = iAzi2;
      Car[iTeleportTarget].nYaw3 = iAzi2;
      Car[iTeleportTarget].nPitch = iElevation;
      posAy = localdata[nCurrChunk].pointAy;
      Car[iTeleportTarget].nRoll = iBank;
      fLocalX = posAy->fY * Car[iTeleportTarget].pos.fY + posAy->fX * Car[iTeleportTarget].pos.fX + posAy->fZ * Car[iTeleportTarget].pos.fZ - posAy[3].fX;
      fLocalY = posAy[1].fY * Car[iTeleportTarget].pos.fY + posAy[1].fX * Car[iTeleportTarget].pos.fX + posAy[1].fZ * Car[iTeleportTarget].pos.fZ - posAy[3].fY;
      dLocalZ = posAy[2].fY * Car[iTeleportTarget].pos.fY + posAy[2].fX * Car[iTeleportTarget].pos.fX + posAy[2].fZ * Car[iTeleportTarget].pos.fZ - posAy[3].fZ;
      Car[iTeleportTarget].pos.fX = fLocalX;
      Car[iTeleportTarget].iUnk47 = 0;
      Car[iTeleportTarget].iUnk7 = 0;
      Car[iTeleportTarget].iUnk8 = 0;
      Car[iTeleportTarget].iControlType = 0;
      Car[iTeleportTarget].fFinalSpeed = 0.0;
      Car[iTeleportTarget].fBaseSpeed = 0.0;
      Car[iTeleportTarget].fSpeedOverflow = 0.0;
      fLocalZ = (float)dLocalZ;
      Car[iTeleportTarget].fRPMRatio = 0.0;
      fChunkValue = fLocalY;
      Car[iTeleportTarget].fPower = 0.0;
      Car[iTeleportTarget].pos.fY = fChunkValue;
      Car[iTeleportTarget].nUnk21 = 18;
      Car[iTeleportTarget].pos.fZ = fLocalZ;
      //LOWORD(fChunkValue) = Car[iTeleportTarget].nCurrChunk;
      int16 nTemp = Car[iTeleportTarget].nCurrChunk;
      Car[iTeleportTarget].nChunk2 = nTemp; //LOWORD(fChunkValue);
      Car[iTeleportTarget].iLastValidChunk = nTemp;// SLOWORD(fChunkValue);
      Car[iTeleportTarget].byAttacker = iCarIdx_1;
      Car[iTeleportTarget].byGearAyMax = 0;
      Car[iTeleportTarget].byUnk43 = -40;
      iPlayerIdx2 = iCarIdx_1;
      Car[iTeleportTarget].nCurrChunk = -1;
      if (cheatsampleok(iPlayerIdx2))
        sfxsample(SOUND_SAMPLE_UP, 0x8000);                  // SOUND_SAMPLE_UP
      if (cheatsampleok(iTeleportTargetIndex))
        sfxsample(SOUND_SAMPLE_UP, 0x8000);                  // SOUND_SAMPLE_UP
      --Car[iCarIdx_1].byCheatAmmo;
    SET_TELEPORT_COOLDOWN:
      iTrakLen = TRAK_LEN;
      Car[iCarIdx_1].byCheatCooldown = 36;
    PROCESS_VEHICLE_CONTROLS:
      TRAK_LEN = iTrakLen;
      if (race_started)                       // Process main vehicle controls: gear changes, material selection, throttle/brake
      {                                         // Handle gear shift controls if race has started
        if ((iControlFlags & 4) != 0)
          GoUpGear(&Car[iCarIdx_1]);
        if ((iControlFlags & 8) != 0)
          GoDownGear(&Car[iCarIdx_1], iControlFlags & 1);
        if (player_type != 2)                 // Handle material selection controls (paint job changes)
        {
          if ((iControlFlags & 0x40) != 0)
            changemateto(iCarIdx_1, 0);
          if ((iControlFlags & 0x80u) != 0)
            changemateto(iCarIdx_1, 1);
          if ((iControlFlags & 0x100) != 0)
            changemateto(iCarIdx_1, 2);
          if ((iControlFlags & 0x200) != 0)
            changemateto(iCarIdx_1, 3);
        }
      }
      pCar = &Car[iCarIdx_1];                   // Apply vehicle physics based on throttle/brake input
      if ((iControlFlags & 2) != 0)          // Check control flags: bit 2=brake, bit 1=accelerate, else=freewheel
      {
        Decelerate(pCar);
      } else if ((iControlFlags & 1) != 0) {
        Accelerate(pCar);
      } else {
        FreeWheel(pCar);
      }
      return;
    case 12:                                    // LOVEBUN (formula car)
      if (!Car[iCarIndex2].byCheatCooldown) {
        byCheatAmmo_1 = Car[iCarIndex2].byCheatAmmo;
        TRAK_LEN = iTrakLen;
        if (byCheatAmmo_1) {
          iCurrentChunk = Car[iCarIndex2].nCurrChunk;
          if (iCurrentChunk != -1) {
            iColorIndex = -12;                  // Modify track surface in 16-chunk range around car position
            do {
              if ((TrakColour[iCurrentChunk][1] & 0x8400000) == 0) {
                iTrackColor1 = TrakColour[iCurrentChunk][1];
                SET_LOWORD(iTrackColor1, iTrackColor1 & 0xFE00);
                TrakColour[iCurrentChunk][1] = (159 - (iColorIndex & 7)) | iTrackColor1;
                localdata[iCurrentChunk].iCenterGrip = 12;
              }
              if ((TrakColour[iCurrentChunk][0] & 0x8400000) == 0) {
                iTrackColor2 = TrakColour[iCurrentChunk][0];
                SET_LOWORD(iTrackColor2, iTrackColor2 & 0xFE00);
                TrakColour[iCurrentChunk][0] = iTrackColor2 | (159 - (iColorIndex & 7));
                localdata[iCurrentChunk].iLeftShoulderGrip = 12;
              }
              if ((TrakColour[iCurrentChunk][2] & 0x8400000) == 0) {
                iTrackColor3 = TrakColour[iCurrentChunk][1];
                SET_LOWORD(iTrackColor3, iTrackColor3 & 0xFE00);
                TrakColour[iCurrentChunk][2] = (159 - (iColorIndex & 7)) | iTrackColor3;
                localdata[iCurrentChunk].iRightShoulderGrip = 12;
              }
              if (++iCurrentChunk >= iTrakLen)
                iCurrentChunk = 0;
              ++iColorIndex;
            } while (iColorIndex < 4);
            byNewCheatAmmo = Car[iCarIdx_1].byCheatAmmo - 1;
            TRAK_LEN = iTrakLen;
            Car[iCarIdx_1].byCheatAmmo = byNewCheatAmmo;
          }
        } else if (cheatsampleok(iCarIndex1)) {
          sfxsample(SOUND_SAMPLE_BLOP, 0x8000);                // SOUND_SAMPLE_BLOP
        }
        iTrakLen = TRAK_LEN;
        Car[iCarIdx_1].byCheatCooldown = 36;
      }
      goto PROCESS_VEHICLE_CONTROLS;
    default:
      goto PROCESS_VEHICLE_CONTROLS;            // Cheat power switch: handle different special car abilities
  }
}

//-------------------------------------------------------------------------------------------------
//0002A060
void GoUpGear(tCar *pCar)
{
  int iCarDesignIdx; // esi
  tCarEngine *pEngineData; // edi
  int byGearAyMax; // ecx
  int iTargetGear; // ecx
  float *pSpds; // edi
  float fNewPowerForward; // [esp+0h] [ebp-2Ch]
  float fNewPowerReverse; // [esp+0h] [ebp-2Ch]
  float fMinShiftSpeed; // [esp+4h] [ebp-28h]
  float fAdjustedSpeed; // [esp+8h] [ebp-24h]
  float fHealthFactor; // [esp+Ch] [ebp-20h]
  float fRPMRatio; // [esp+10h] [ebp-1Ch]

  iCarDesignIdx = pCar->byCarDesignIdx;         // Get car design index and engine data
  pEngineData = &CarEngines.engines[iCarDesignIdx];
  byGearAyMax = (char)pCar->byGearAyMax;
  if (byGearAyMax < pEngineData->iNumGears - 1)// Check if car can upshift (not already in top gear)
  {
    fHealthFactor = (pCar->fHealth + 34.0f) * 0.01f;// Calculate health factor (0-1) based on car damage, capped at 1.0
    iTargetGear = byGearAyMax + 1;
    if (fHealthFactor > 1.0)
      fHealthFactor = 1.0;
    fMinShiftSpeed = -1.0;                      // Initialize minimum shift speed to -1 (no restriction)
    fAdjustedSpeed = (float)(fabs(pCar->fFinalSpeed) / fHealthFactor);// Calculate current speed adjusted by health factor
    if (human_control[pCar->iDriverIdx] != 2 && iTargetGear > 0)// For AI drivers, set minimum speed for upshift (50% of current gear max speed)
      fMinShiftSpeed = pEngineData->pSpds[iTargetGear - 1] * 0.5f;
    if (fAdjustedSpeed >= (double)fMinShiftSpeed)// Check if car is fast enough to upshift
    {
      pSpds = pEngineData->pSpds;
      if (iTargetGear < 0)                    // Handle reverse gear upshift (gear < 0)
      {
        fRPMRatio = fAdjustedSpeed / *pSpds;
        if (fRPMRatio > 1.0)
          fRPMRatio = 1.0;
      } else {
        fRPMRatio = fAdjustedSpeed / pSpds[iTargetGear];// Calculate RPM ratio for target gear
        if (fRPMRatio > 1.0)
          fRPMRatio = 1.0;
      }
      pCar->fRPMRatio = fRPMRatio;
      if (player1_car == pCar->iDriverIdx && !DriveView[0])// Play gear shift sound for human players (not in cockpit view)
        sfxsample(SOUND_SAMPLE_GRSHIFT, 12000);                    // SOUND_SAMPLE_GRSHIFT
      if (player2_car == pCar->iDriverIdx && !DriveView[1])
        sfxsample(SOUND_SAMPLE_GRSHIFT, 12000);                    // SOUND_SAMPLE_GRSHIFT
      if (iTargetGear < 0)                    // Handle upshift to reverse gear (set gear 0)
      {
        fNewPowerReverse = (float)calc_pow(iCarDesignIdx, 0, fRPMRatio);
        pCar->fBaseSpeed = 0.0;
        pCar->byGearAyMax = iTargetGear;
        pCar->fPower = fNewPowerReverse;
      } else {
        fNewPowerForward = (float)calc_pow(iCarDesignIdx, iTargetGear, fRPMRatio);// Handle normal forward gear upshift
        pCar->byGearAyMax = iTargetGear;
        pCar->fPower = fNewPowerForward;
        pCar->fBaseSpeed = pSpds[iTargetGear] * fRPMRatio * fHealthFactor;
      }
      pCar->fSpeedOverflow = pCar->fFinalSpeed - pCar->fBaseSpeed;// Update speed overflow (difference between current and base speed)
    }
  }
}

//-------------------------------------------------------------------------------------------------
//0002A200
void GoDownGear(tCar *pCar, int iUseAutoLogic)
{
  int iCarDesignIdx; // ecx
  tCarEngine *pEngineData; // edi
  int iGearAyMax; // eax
  int iTargetGear; // eax
  int iGearForCalc; // edx
  int iCurrentGear; // eax
  tCar *pCarCopy; // ebx
  double dBaseSpeed; // st7
  float *pSpds; // ecx
  double dMaxSpeed; // st7
  float fRPMRatio; // [esp+0h] [ebp-28h]
  float fDownshiftThreshold; // [esp+4h] [ebp-24h]
  float fHealthFactor; // [esp+8h] [ebp-20h]
  float fCalculatedPower; // [esp+Ch] [ebp-1Ch]
  int iTargetGearIdx; // [esp+10h] [ebp-18h]

  fHealthFactor = (pCar->fHealth + 34.0f) * 0.01f;// Calculate health factor (0-1) based on car damage
  iCarDesignIdx = pCar->byCarDesignIdx;        // Get car design index and engine data
  pEngineData = &CarEngines.engines[iCarDesignIdx];
  if (fHealthFactor > 1.0)
    fHealthFactor = 1.0;
  iGearAyMax = (char)pCar->byGearAyMax;
  if (iGearAyMax > -2)                       // Check if car can downshift (not already in lowest gear -2)
  {
    iTargetGear = iGearAyMax - 1;              // Calculate target gear (current gear - 1)
    iTargetGearIdx = iTargetGear;
    if (iTargetGear < 0)                      // Handle reverse gear downshift (target < 0)
    {
      iCurrentGear = 1;
      pCarCopy = pCar;
      iGearForCalc = 0;
    } else {
      iGearForCalc = iTargetGear;               // Handle forward gear downshift
      iCurrentGear = iTargetGear + 1;
      pCarCopy = pCar;
    }
    fCalculatedPower = (float)change_gear(iCurrentGear, iGearForCalc, pCarCopy, iCarDesignIdx);// Calculate power output for target gear using change_gear function
    fDownshiftThreshold = 1000.0;               // Set downshift threshold: high value for human, gear change value * 1.2 for AI
    if (human_control[pCar->iDriverIdx] != 2 && iUseAutoLogic)
      fDownshiftThreshold = pEngineData->pChgs[2 * iTargetGearIdx] * 1.2f;
    if (fCalculatedPower < (double)fDownshiftThreshold)// Check if calculated power is below downshift threshold
    {
      pCar->fPower = fCalculatedPower;
      pCar->byGearAyMax = iTargetGearIdx;
      if (iTargetGearIdx == -1)               // Handle downshift to reverse gear (-1): zero base speed
      {
        dBaseSpeed = pCar->fBaseSpeed;
        pCar->fBaseSpeed = 0.0;
      } else {
        pSpds = pEngineData->pSpds;
        if (iTargetGearIdx >= 0)              // Handle forward gear downshift: calculate RPM ratio and speeds
        {
          fRPMRatio = (float)calc_revs(pEngineData->pRevs, iTargetGearIdx, fCalculatedPower);// Forward gear: use target gear curve data and positive max speed
          pCar->fRPMRatio = fRPMRatio;
          dMaxSpeed = pSpds[iTargetGearIdx];
        } else {
          fRPMRatio = (float)calc_revs(pEngineData->pRevs, 0, fCalculatedPower);// Reverse gear: use gear 0 curve data, negative max speed
          pCar->fRPMRatio = fRPMRatio;
          dMaxSpeed = -*pSpds;
        }
        pCar->fBaseSpeed = (float)dMaxSpeed * fRPMRatio * fHealthFactor;// Calculate new base speed: max speed * RPM ratio * health factor
        dBaseSpeed = pCar->fFinalSpeed - pCar->fBaseSpeed;// Update speed overflow (difference between final and base speed)
      }
      pCar->fSpeedOverflow = (float)dBaseSpeed;
    }
  }
}

//-------------------------------------------------------------------------------------------------
//0002A350
void control()
{
  int iChecksum; // ebx
  int iCarCounter; // edi
  int iCompetitorIdx; // esi
  int iCarIdx; // ecx
  double dHealth; // st7
  //int iCarArraySize; // ebx
  //int iByteOffset; // eax
  //int iStructOffset; // ecx
  //int iDataValue; // edx
  int iFatalityCounter; // edx
  int iCar; // ecx
  int iCar_1; // eax
  int iCarArrayIdx; // ebx
  int iCarStructIdx; // edx
  int iCarLoopIdx; // ecx
  uint8 byStatusFlags; // ah
  int16 nTimerValue; // ax
  int iUpdateCarIdx; // ecx
  int iCarUpdateIdx; // edx
  uint8 byUnk43; // bh
  int i; // ecx
  unsigned int uiSLightOffset; // edx
  float fLightSpeed; // esi
  double dLightPosX; // st7
  double dLightPosY; // st7
  double dLightPosZ; // st7
  double dLightSpeedZ; // st7
  int iCrossLineIdx; // ebx
  tCar *pCarPtr; // edx
  int iMotionCarIdx; // ecx
  tCar *pCurrentCar; // ebx
  tCar *pMotionCar; // edx
  double dDamageFactor; // st7
  double dRollMotionCalc; // st7
  double dPitchMotionCalc; // st7
  double dYawMotionCalc; // st7
  int iNumCarsTemp; // edi
  int j; // ecx
  char bySampleValue; // ah
  int iNetworkArraySize; // ecx
  int iCarOffset; // edx
  int iMasterCarIdx; // ebx
  int iMasterByteIdx; // edx
  int iSlaveByteIdx; // ebx
  int iSlaveCarIdx; // edx
  int iRacingByteIdx; // ebx
  int iFinalArraySize; // ecx
  int iFinalCarIdx; // edx
  int iFinalByteIdx; // ebx
  int8 byUnk68; // ah
  uint8 byNewValue; // al
  int aiCarStates[17]; // [esp+0h] [ebp-9Ch]
  double dLightDistanceX; // [esp+44h] [ebp-58h]
  double dLightDistanceY; // [esp+4Ch] [ebp-50h]
  double dLightDistanceZ; // [esp+54h] [ebp-48h]
  float fLightDeltaZ; // [esp+5Ch] [ebp-40h]
  float fX; // [esp+60h] [ebp-3Ch]
  float fLightDeltaX; // [esp+64h] [ebp-38h]
  float fDamageMultiplier; // [esp+68h] [ebp-34h]
  float fHealthFactor; // [esp+6Ch] [ebp-30h]
  float fHealthValue; // [esp+70h] [ebp-2Ch]
  int iRandomValue; // [esp+74h] [ebp-28h]
  float fZ; // [esp+78h] [ebp-24h]
  float fY; // [esp+7Ch] [ebp-20h]
  float fLightDeltaY; // [esp+80h] [ebp-1Ch]

  updates = 0;                                  // Initialize update counter and handle replay mode
  if (replaytype == 2)
    readptr = -10000;
  if (readptr == writeptr)
    analysespeechsamples();
  while (readptr != writeptr)                 // Main game update loop - process each frame while data available
  {
    --view1_cnt;                                // Update frame counters and warp animation angle
    --view0_cnt;
    --Quit_Count;
    warp_angle = (warp_angle + 512) & 0x3FFF;
    if (fudge_wait == readptr && wConsoleNode == master)
      racing = master ^ wConsoleNode;
    ++game_frame;
    --countdown;
    if (network_on && replaytype != 2 && write_check >= 0)// Network synchronization: calculate checksums for car state validation
    {
      iChecksum = 0;
      iCarCounter = 0;
      if (numcars > 0) {
        iCompetitorIdx = 0;
        iCarIdx = 0;
        do {
          if (!non_competitors[iCompetitorIdx]) {
            dHealth = Car[iCarIdx].fHealth;
            //_CHP();
            //LODWORD(fHealthValue) = (int)dHealth;
            //iChecksum += abs16(Car[iCarIdx].nCurrChunk)
            //  + LODWORD(Car[iCarIdx].pos.fZ)
            //  + LODWORD(Car[iCarIdx].pos.fY)
            //  + LODWORD(Car[iCarIdx].pos.fX)
            //  + abs8(Car[iCarIdx].byLives)
            //  + abs32((int)dHealth);
            // Calculate network synchronization checksum from car state data
            iChecksum += abs(Car[iCarIdx].nCurrChunk)
              + *(int *)&Car[iCarIdx].pos.fX    // Float bit pattern as int
              + *(int *)&Car[iCarIdx].pos.fY
              + *(int *)&Car[iCarIdx].pos.fZ
              + abs(Car[iCarIdx].byLives)
              + abs((int)dHealth);
          }
          ++iCompetitorIdx;
          ++iCarCounter;
          ++iCarIdx;
        } while (iCarCounter < numcars);
      }
      player_checks[write_check][player1_car] = iChecksum & 0x3F;
      write_check = ((int16)write_check + 1) & 0x1FF;
    }

    if (numcars > 0)
    {
      for (int i = 0; i < numcars; i++)
      {
        // Initialize wheel spin factor to 1.0
        Car[i].fWheelSpinFactor = 1.0;

        // Store byUnk68 value in car states array
        aiCarStates[i] = Car[i].byUnk68;
      }
    }
    //if (numcars > 0)                          // Initialize car state array and copy car data for processing
    //{
    //  iCarArraySize = 4 * numcars;
    //  iByteOffset = 0;
    //  iStructOffset = 0;
    //  do {
    //    iStructOffset += sizeof(tCar);
    //    iByteOffset += 4;
    //    iDataValue = *((char *)&CarBox.hitboxAy[15][5].fY + iStructOffset + 2);// references adjacent data Car
    //    *(float *)((char *)&CarBox.hitboxAy[15][7].fX + iStructOffset) = 1.0;// references adjacent data Car
    //    aiCarStates[iByteOffset / 4u] = iDataValue;
    //  } while (iByteOffset < iCarArraySize);
    //}

    if (!paused)
      ++updates;
    iFatalityCounter = Fatality_Count;          // Handle fatality timer and camera zoom effects
    if (Fatality_Count > 0) {
      --Fatality_Count;
      if (iFatalityCounter == 1)
        Fatality = -1;
    }
    dozoomstuff(0);
    if (player_type == 2)
      dozoomstuff(1);
    if (readptr >= 0) {                                           // Process each car: handle race start, player controls, and network events
      for (iCar = 0; iCar < numcars; ++iCar) {                                         // Race start condition: clear high bit from gear and enable racing
        if (game_frame == 145 && (Car[iCar].byGearAyMax & 0x80u) != 0) {
          Car[iCar].byGearAyMax = 0;
          race_started = -1;
          Car[iCar].fPower = 0.0;
        }
        if (human_control[iCar]) {                                       // Network sync request: reset car to neutral state
          if ((copy_multiple[readptr][iCar].uiFullData & 0x10000000) != 0) {
            iCar_1 = iCar;
            Car[iCar_1].byGearAyMax = -1;
            Car[iCar_1].fPower = 0.0;
            Car[iCar_1].fRPMRatio = 0.0;
            Car[iCar_1].fBaseSpeed = 0.0;
            Car[iCar_1].fSpeedOverflow = 0.0;
            Car[iCar_1].fFinalSpeed = 0.0;
            if (fudge_wait < 0)
              fudge_wait = ((int16)readptr + 1) & 0x1FF;
            stopallsamples();
          }
          if ((copy_multiple[readptr][iCar].uiFullData & 0x4000000) != 0)// Network player quit: cleanup and handle disconnection
          {
            memset(player_checks, -1, sizeof(player_checks));
            read_check = 0;
            write_check = 0;
            --players;
            if (finished_car[iCar])
              --human_finishers;
            if (player1_car == iCar) {
              net_quit = -1;
            } else {
              start_zoom(&language_buffer[3776], 0);
              subzoom(driver_names[iCar]);
            }
            human_control[iCar] = 0;
            initnearcars();
          }
        }
      }
    }
    if (replaytype == 2)                      // Handle replay data and update stunt system
      DoReplayData();
    updatestunts();
    if (replaytype != 2) {
      memset(newrepsample, 0, sizeof(newrepsample));// Process car controls and AI for non-replay mode
      iCarArrayIdx = 0;
      if (numcars > 0) {
        iCarStructIdx = 0;
        iCarLoopIdx = 0;
        do {
          byStatusFlags = Car[iCarStructIdx].byStatusFlags;// Check car status and handle death/damage states
          Car[iCarStructIdx].byAccelerating = 0;
          if ((byStatusFlags & 4) != 0 || !Car[iCarStructIdx].byLives) {
            //if ((LODWORD(Car[iCarStructIdx].fFinalSpeed) & 0x7FFFFFFF) == 0 || Car[iCarStructIdx].nUnk21 < 126) {
            if (fabs(Car[iCarStructIdx].fFinalSpeed) > FLT_EPSILON || Car[iCarStructIdx].nUnk21 < 126) {
              nTimerValue = Car[iCarStructIdx].nUnk25 - 1;
              --Car[iCarStructIdx].nUnk21;
              Car[iCarStructIdx].nUnk25 = nTimerValue;
            }
            if (Car[iCarStructIdx].nUnk21 < 0)
              Car[iCarStructIdx].byStatusFlags |= 2u;
          }
          if ((Car[iCarStructIdx].byLives & 0x80u) == 0) {                                     // Process car controls: human player or AI based on control type
            if (human_control[iCarLoopIdx]) {
              if (Car[iCarStructIdx].iControlType != 2 && !Car[iCarStructIdx].iStunned)
                humancar(iCarArrayIdx);
            } else if (Car[iCarStructIdx].iControlType == 3 && !Car[iCarStructIdx].iStunned) {
              autocar2(&Car[iCarStructIdx]);
            }
          }
          ++iCarStructIdx;
          ++iCarArrayIdx;
          ++iCarLoopIdx;
        } while (iCarArrayIdx < numcars);
      }
      iUpdateCarIdx = 0;                        // Update car physics and damage over time effects
      if (numcars > 0) {
        iCarUpdateIdx = 0;
        do {
          if ((Car[iCarUpdateIdx].byLives & 0x80u) == 0) {
            if (fudge_wait < 0)
              updatecar2(&Car[iCarUpdateIdx], iCarUpdateIdx * 308, iCarArrayIdx, iUpdateCarIdx);
            byUnk43 = Car[iCarUpdateIdx].byUnk43;
            if (byUnk43 && Car[iCarUpdateIdx].fHealth > 0.0)
              Car[iCarUpdateIdx].byUnk43 = byUnk43 - 1;
          }
          iCarArrayIdx = numcars;
          ++iUpdateCarIdx;
          ++iCarUpdateIdx;
        } while (iUpdateCarIdx < numcars);
      }
      if (countdown > -72 && replaytype != 2) // Update dynamic lighting effects for local players
      {
        for (i = 0; i < local_players; ++i) {
          uiSLightOffset = 0x90 * i;
          do {
            fLightDeltaX = SLight[0][uiSLightOffset / 0x30].targetPos.fX - SLight[0][uiSLightOffset / 0x30].currentPos.fX;// Animate lights toward target positions with speed limiting
            fLightSpeed = fLightDeltaX;
            SLight[0][uiSLightOffset / 0x30].uiRotation = (SLight[0][uiSLightOffset / 0x30].uiRotation + 128) & 0x3FFF;
            //if ((LODWORD(fLightSpeed) & 0x7FFFFFFF) != 0) {
            if (fabs(fLightSpeed) > FLT_EPSILON) {
              fX = SLight[0][uiSLightOffset / 0x30].speed.fX;
              dLightDistanceX = fabs(fLightDeltaX);
              if (fX > dLightDistanceX)
                fX = (float)dLightDistanceX;
              if (fLightDeltaX <= 0.0)
                dLightPosX = SLight[0][uiSLightOffset / 0x30].currentPos.fX - fX;
              else
                dLightPosX = SLight[0][uiSLightOffset / 0x30].currentPos.fX + fX;
              SLight[0][uiSLightOffset / 0x30].currentPos.fX = (float)dLightPosX;
            }
            fLightDeltaY = SLight[0][uiSLightOffset / 0x30].targetPos.fY - SLight[0][uiSLightOffset / 0x30].currentPos.fY;
            //if ((LODWORD(fLightDeltaY) & 0x7FFFFFFF) != 0) {
            if (fabs(fLightDeltaY) > FLT_EPSILON) {
              fY = SLight[0][uiSLightOffset / 0x30].speed.fY;
              dLightDistanceY = fabs(fLightDeltaY);
              if (fY > dLightDistanceY)
                fY = (float)dLightDistanceY;
              if (fLightDeltaY <= 0.0)
                dLightPosY = SLight[0][uiSLightOffset / 0x30].currentPos.fY - fY;
              else
                dLightPosY = SLight[0][uiSLightOffset / 0x30].currentPos.fY + fY;
              SLight[0][uiSLightOffset / 0x30].currentPos.fY = (float)dLightPosY;
            }
            fLightDeltaZ = SLight[0][uiSLightOffset / 0x30].targetPos.fZ - SLight[0][uiSLightOffset / 0x30].currentPos.fZ;
            //if ((LODWORD(fLightDeltaZ) & 0x7FFFFFFF) != 0) {
            if (fabs(fLightDeltaZ) > FLT_EPSILON) {
              fZ = SLight[0][uiSLightOffset / 0x30].speed.fZ;
              dLightDistanceZ = fabs(fLightDeltaZ);
              if (fZ > dLightDistanceZ)
                fZ = (float)dLightDistanceZ;
              if (fLightDeltaZ <= 0.0)
                dLightPosZ = SLight[0][uiSLightOffset / 0x30].currentPos.fZ - fZ;
              else
                dLightPosZ = SLight[0][uiSLightOffset / 0x30].currentPos.fZ + fZ;
              SLight[0][uiSLightOffset / 0x30].currentPos.fZ = (float)dLightPosZ;
              if (countdown < 126) {
                dLightSpeedZ = SLight[0][uiSLightOffset / 0x30].speed.fZ + -2.5;
                SLight[0][uiSLightOffset / 0x30].speed.fZ = (float)dLightSpeedZ;
                if (dLightSpeedZ < 20.0)
                  SLight[0][uiSLightOffset / 0x30].speed.fZ = 20.0;
              }
            }
            uiSLightOffset += 48;
          } while (uiSLightOffset != 0x90 * i + 144);
        }
      }
      if (fudge_wait < 0)                     // Test collisions and check lap line crossings
        testcollisions();
      iCrossLineIdx = 0;
      if (numcars > 0) {
        pCarPtr = Car;
        do {
          if (fudge_wait < 0)
            check_crossed_line(pCarPtr);
          ++iCrossLineIdx;
          ++pCarPtr;
        } while (iCrossLineIdx < numcars);
      }
    }
    if (replaytype == 1 && fudge_wait < 0)
      DoReplayData();
    if (replaytype != 2 || newreplayframe)    // Calculate car motion effects based on health and speed
    {
      iMotionCarIdx = 0;
      if (numcars > 0) {
        pCurrentCar = Car;
        do {
          fHealthFactor = (pCurrentCar->fHealth + 34.0f) * 0.01f;// Apply random motion effects: more damage = more erratic movement
          pMotionCar = pCurrentCar;
          if (fHealthFactor > 1.0)
            fHealthFactor = 1.0;
          dDamageFactor = 8.0 - 7.0 * fHealthFactor;
          fDamageMultiplier = (float)dDamageFactor;
          fHealthValue = (float)dDamageFactor * pCurrentCar->fFinalSpeed;
          iRandomValue = rand() - 0x4000;
          dRollMotionCalc = (double)iRandomValue * fHealthValue / (double)CarEngines.engines[pCurrentCar->byCarDesignIdx].iStabilityFactor;
          //_CHP();
          pCurrentCar->iRollMotion = (int)dRollMotionCalc;
          fHealthValue = fDamageMultiplier * pCurrentCar->fFinalSpeed;
          iRandomValue = rand() - 0x4000;
          dPitchMotionCalc = (double)iRandomValue * fHealthValue / (double)CarEngines.engines[pCurrentCar->byCarDesignIdx].iStabilityFactor;
          //_CHP();

          pCurrentCar->iPitchMotion = (int)dPitchMotionCalc;
          fHealthValue = fDamageMultiplier * pCurrentCar->fFinalSpeed;
          iRandomValue = rand() - 0x4000;
          dYawMotionCalc = (double)iRandomValue * fHealthValue / (double)CarEngines.engines[pCurrentCar->byCarDesignIdx].iStabilityFactor;
          //*(float *)&iRandomValue = fDamageMultiplier * pCurrentCar->fFinalSpeed;
          //LODWORD(fHealthValue) = rand() - 0x4000;
          //dYawMotionCalc = (double)SLODWORD(fHealthValue) * *(float *)&iRandomValue / (double)CarEngines.engines[pCurrentCar->byCarDesignIdx].iStabilityFactor;
          //_CHP();
          ++pCurrentCar;
          ++iMotionCarIdx;
          iNumCarsTemp = numcars;
          pMotionCar->iYawMotion = (int)dYawMotionCalc;
        } while (iMotionCarIdx < iNumCarsTemp);
      }
    }
    if (replaytype == 2 && replayspeed == 256)// Handle replay sound effects synchronization
    {
      for (j = 0; j < numcars; ++j) {
        bySampleValue = newrepsample[j];
        if (bySampleValue) {
          if (repsample[j] < 0 && bySampleValue > 0)
            sfxpend(bySampleValue - 1, j, (uint8)repvolume[j] << 8);
          if (repsample[j] > 0 && newrepsample[j] < 0)
            sfxpend(-newrepsample[j] - 1, j, (uint8)repvolume[j] << 8);
          repsample[j] = newrepsample[j];
        }
      }
    }
    analysespeechsamples();                     // Finalize frame: analyze speech, order cars, handle audio
    ordercars();
    if (replaytype != 2) {
      if (paused) {
        stopallsamples();
        delaywrite = delayread + 6;
      } else if (player_type == 2) {
        enginesounds2(ViewType[0], ViewType[1]);
      } else {
        enginesounds(ViewType[0]);
      }
    }
    if (!intro && human_finishers >= players && (disable_messages || network_on))// Check race completion conditions and network state
    {
      iNetworkArraySize = 4 * numcars;
      iCarOffset = network_on;
      if (network_on) {
        if (wConsoleNode == master) {
          send_finished = -1;                   // Network master: check if any human players still racing
          if (numcars > 0) {
            iMasterCarIdx = 0;
            iMasterByteIdx = 0;
            do {
              if ((Car[iMasterCarIdx].byLives & 0x80u) == 0 && Car[iMasterCarIdx].fFinalSpeed > 0.0 && human_control[iMasterByteIdx / 4u])
                send_finished = 0;
              iMasterByteIdx += 4;
              ++iMasterCarIdx;
            } while (iMasterByteIdx < iNetworkArraySize);
          }
        } else {
          iSlaveByteIdx = 0;                    // Network slave: determine local racing state
          racing = 0;
          if (numcars > 0) {
            iSlaveCarIdx = 0;
            do {
              if ((Car[iSlaveCarIdx].byLives & 0x80u) == 0 && Car[iSlaveCarIdx].fFinalSpeed > 0.0 && human_control[iSlaveByteIdx / 4u])
                racing = -1;
              iSlaveByteIdx += 4;
              ++iSlaveCarIdx;
            } while (iSlaveByteIdx < iNetworkArraySize);
          }
        }
      } else if (lastsample < -72)              // Single player: check if any human players still racing
      {
        racing = network_on;
        if (numcars > 0) {
          iRacingByteIdx = 0;
          do {
            if (*((char *)&Car[0].byLives + iCarOffset) >= 0 && *(float *)((char *)&Car[0].fFinalSpeed + iCarOffset) > 0.0 && human_control[iRacingByteIdx / 4u])
              racing = -1;
            iRacingByteIdx += 4;
            iCarOffset += sizeof(tCar);
          } while (iRacingByteIdx < iNetworkArraySize);
        }
      }
    }
    if (++nearcarcheck == 4)                  // Update near car checking counter and advance frame pointer
      nearcarcheck = 0;
    if (replaytype == 2)
      readptr = writeptr;
    else
      readptr = ((int16)readptr + 1) & 0x1FF;
  }
  if (replaytype != 2 && numcars > 0)         // Final processing: handle special car state changes for active cars
  {
    iFinalArraySize = 4 * numcars;
    iFinalCarIdx = 0;
    iFinalByteIdx = 0;
    while (1) {
      if (Car[iFinalCarIdx].fFinalSpeed <= 36.0 || Car[iFinalCarIdx].fFinalSpeed >= 100.0)
        goto LABEL_185;                         // Toggle special car state (byUnk68) based on speed and current state
      byUnk68 = Car[iFinalCarIdx].byUnk68;
      if (byUnk68 > 1)
        break;
      if (byUnk68 == aiCarStates[iFinalByteIdx / 4u + 1]) {
        byNewValue = Car[iFinalCarIdx].byUnk68 ^ 1;
        goto LABEL_184;
      }
    LABEL_185:
      iFinalByteIdx += 4;
      ++iFinalCarIdx;
      if (iFinalByteIdx >= iFinalArraySize)
        return;
    }
    byNewValue = 0;
  LABEL_184:
    Car[iFinalCarIdx].byUnk68 = byNewValue;
    goto LABEL_185;
  }
}

//-------------------------------------------------------------------------------------------------
//0002AEC0
double calc_revs(tRevCurve *pRevs, int iGear, float fChg)
{
  tRevCurve *pCurrentGearCurve; // eax
  double dDelta2; // st7
  double dDelta3; // st3
  float fInterpCoeffA; // [esp+8h] [ebp-40h]
  float fDelta1; // [esp+18h] [ebp-30h]
  float fPower; // [esp+2Ch] [ebp-1Ch]
  float fRevPoint2; // [esp+34h] [ebp-14h]
  float fRevPoint3; // [esp+38h] [ebp-10h]
  float fCalculatedResult; // [esp+3Ch] [ebp-Ch]
  float fRPM; // [esp+40h] [ebp-8h]

  pCurrentGearCurve = &pRevs[iGear];            // Get pointer to RPM/power curve for specified gear
  fRPM = pCurrentGearCurve->points[1].fRPM;     // Load RPM and power values from curve points 1, 2, 3
  fRevPoint2 = pCurrentGearCurve->points[2].fRPM;
  fRevPoint3 = pCurrentGearCurve->points[3].fRPM;
  fPower = pCurrentGearCurve->points[1].fPower;
  if (fChg < 0.0 || fChg >= (double)fRPM)     // Low RPM range: quadratic interpolation between points 0-1
  {                                             // Mid RPM range: quadratic interpolation between points 1-3
    if (fChg < (double)fRPM || fChg >= (double)fRevPoint3) {
      fCalculatedResult = 1.0;                  // High RPM range: return maximum value
    } else {
      fDelta1 = fChg - fRPM;                    // Calculate delta values for quadratic interpolation
      dDelta2 = fChg - fRevPoint2;
      dDelta3 = fChg - fRevPoint3;
      fInterpCoeffA = (float)(dDelta2 * dDelta3 * fPower / ((fRPM - fRevPoint2) * (fRPM - fRevPoint3)));// Calculate first interpolation coefficient
      fCalculatedResult = (float)(dDelta3 * fDelta1 * pCurrentGearCurve->points[2].fPower / ((fRevPoint2 - fRPM) * (fRevPoint2 - fRevPoint3))
        + fInterpCoeffA
        + dDelta2 * fDelta1 * pCurrentGearCurve->points[3].fPower / ((fRevPoint3 - fRPM) * (fRevPoint3 - fRevPoint2)));// Complete quadratic interpolation using all three points
    }
  } else {
    fCalculatedResult = (fChg - fRPM) * fChg * pCurrentGearCurve->points[0].fPower / ((pCurrentGearCurve->points[0].fRPM - fRPM) * pCurrentGearCurve->points[0].fRPM)
      + (fChg - pCurrentGearCurve->points[0].fRPM) * fChg * fPower / (fRPM * (fRPM - pCurrentGearCurve->points[0].fRPM));// Calculate interpolated value using quadratic formula for low range
  }

  // clamp result to between 0.0 and 1.0
  if (fCalculatedResult < 0.0)                // Clamp result to valid range [0.0, 1.0]
    fCalculatedResult = 0.0;
  if (fCalculatedResult > 1.0)
    return 1.0;
  return fCalculatedResult;
}

//-------------------------------------------------------------------------------------------------
//0002B030
double calc_pow(int iCarDesignIdx, int iCurrentGear, float fRPMRatio)
{
  tRevCurve *pfRevData; // eax
  double dLowInterp1; // st5
  double dLowInterp2; // st4
  double dLowCoeffA; // st6
  double dLowCoeffB; // st7
  double dHighInterp1; // st5
  double dHighInterp2; // st3
  double dHighCoeffB; // rtt
  float fHighCoeffA; // [esp+0h] [ebp-4Ch]
  float fHighDenominator; // [esp+Ch] [ebp-40h]
  float fHighInterp3; // [esp+20h] [ebp-2Ch]
  float fRevPoint1; // [esp+24h] [ebp-28h]
  float fPowerPoint3; // [esp+28h] [ebp-24h]
  float fPowerPoint4; // [esp+2Ch] [ebp-20h]
  float fRevPoint0; // [esp+30h] [ebp-1Ch]
  float fPowerPoint2; // [esp+34h] [ebp-18h]
  float fCalculatedPower; // [esp+38h] [ebp-14h]
  float fRevPoint3; // [esp+3Ch] [ebp-10h]
  float fRevPoint4; // [esp+40h] [ebp-Ch]
  float fRevPoint2; // [esp+44h] [ebp-8h]

  pfRevData = CarEngines.engines[iCarDesignIdx].pRevs;// Get pointer to RPM/power curve data for this car and gear
  fRevPoint0 = pfRevData[iCurrentGear].points[0].fRPM;// Load 4 RPM points and 4 power values for power curve interpolation
  fRevPoint2 = pfRevData[iCurrentGear].points[1].fRPM;
  fRevPoint3 = pfRevData[iCurrentGear].points[2].fRPM;
  fRevPoint4 = pfRevData[iCurrentGear].points[3].fRPM;
  fRevPoint1 = pfRevData[iCurrentGear].points[0].fPower;
  fPowerPoint2 = pfRevData[iCurrentGear].points[1].fPower;
  fPowerPoint3 = pfRevData[iCurrentGear].points[2].fPower;
  fPowerPoint4 = pfRevData[iCurrentGear].points[3].fPower;
  if (fRPMRatio < 0.0 || fRPMRatio >= (double)fPowerPoint2)// Low RPM range: quadratic interpolation between points 0-2
  {                                             // Mid RPM range: quadratic interpolation between points 2-4
    if (fRPMRatio < (double)fPowerPoint2 || fRPMRatio >= (double)fPowerPoint4) {
      fCalculatedPower = pfRevData[iCurrentGear].points[3].fRPM;// High RPM range: use maximum power value
    } else {
      fHighDenominator = (fRevPoint4 - fRevPoint2) * (fRevPoint4 - fRevPoint3);// Calculate quadratic interpolation coefficients for mid RPM
      dHighInterp1 = 1.0 / ((fRevPoint2 - fRevPoint3) * (fRevPoint2 - fRevPoint4));
      dHighInterp2 = 1.0 / ((fRevPoint3 - fRevPoint2) * (fRevPoint3 - fRevPoint4));
      fHighInterp3 = 1.0f / fHighDenominator;
      fHighCoeffA = (float)(fPowerPoint2 * dHighInterp1 + fPowerPoint3 * dHighInterp2 + fPowerPoint4 * fHighInterp3);
      dHighCoeffB = (fRevPoint3 + fRevPoint4) * -fPowerPoint2 * dHighInterp1
        - (fRevPoint2 + fRevPoint4) * fPowerPoint3 * dHighInterp2
        - (fRevPoint2 + fRevPoint3) * fPowerPoint4 * fHighInterp3;
      fCalculatedPower = (float)((sqrt(
        dHighCoeffB * dHighCoeffB
        - (dHighInterp1 * (fPowerPoint2 * fRevPoint3 * fRevPoint4)
           + dHighInterp2 * (fRevPoint4 * (fPowerPoint3 * fRevPoint2))
           + fRevPoint3 * (fRevPoint2 * fPowerPoint4) * fHighInterp3
           - fRPMRatio)
        * (fHighCoeffA
           * 4.0))
                        - dHighCoeffB)
        / (fHighCoeffA
         * 2.0));                 // Solve complex quadratic equation for mid-range power
    }
  } else {
    dLowInterp1 = 1.0 / ((fRevPoint0 - fRevPoint2) * fRevPoint0);// Calculate quadratic interpolation coefficients for low RPM
    dLowInterp2 = 1.0 / ((fRevPoint2 - fRevPoint0) * fRevPoint2);
    dLowCoeffA = fRevPoint1 * dLowInterp1 + fPowerPoint2 * dLowInterp2;
    dLowCoeffB = -(dLowInterp1 * (fRevPoint2 * fRevPoint1)) - dLowInterp2 * (fRevPoint0 * fPowerPoint2);
    fCalculatedPower = (float)((sqrt(dLowCoeffB * dLowCoeffB - -fRPMRatio * (dLowCoeffA * 4.0)) - dLowCoeffB) / (dLowCoeffA * 2.0));// Solve quadratic equation using quadratic formula
  }
  if (fCalculatedPower < 0.0)                 // Clamp power output to valid range [0, 1024]
    fCalculatedPower = 0.0;
  if (fCalculatedPower > 1024.0)
    return 1024.0;
  return fCalculatedPower;
}

//-------------------------------------------------------------------------------------------------
//0002B260
void Accelerate(tCar *pCar)
{                                               // Set car complexity factor: 2.0 for advanced cars, 1.0 for simple cars
  int iCarDesignIdx; // ebp
  tCarEngine *pEngineData; // edi
  int nCurrChunk; // eax
  int iNextChunk; // eax
  tData *pTrackData; // edx
  tTrackInfo *pTrackInfo; // ebx
  int iDriverIdx; // ebx
  double dDownshiftPower; // st7
  double dUpshiftPower; // st7
  double dCalculatedRPMRatio; // st7
  int iPitchDelta; // ebp
  int iMaxPitchOffset_1; // eax
  int iPitchDynamicOffset; // eax
  int iMaxPitchOffset; // edx
  int iOldPitchOffset; // eax
  double dPitchDecay; // st6
  int iPitchDeltaNormal; // ecx
  int iMaxPitchNormal; // ebp
  double dMaxRPMChange; // [esp+8h] [ebp-78h]
  float fUpshiftSpeed; // [esp+28h] [ebp-58h]
  float fNegHealthFactor; // [esp+2Ch] [ebp-54h]
  float fTrackHalfWidth; // [esp+30h] [ebp-50h]
  float fDownshiftThreshold; // [esp+34h] [ebp-4Ch]
  float fAdjustedGravity; // [esp+38h] [ebp-48h]
  float fPitchDecayAmount; // [esp+3Ch] [ebp-44h]
  int iGearChanged; // [esp+40h] [ebp-40h]
  float *pSpds; // [esp+44h] [ebp-3Ch]
  float fCarComplexityFactor; // [esp+48h] [ebp-38h]
  float fGravityFactor; // [esp+4Ch] [ebp-34h]
  float fNewRPMRatio; // [esp+50h] [ebp-30h]
  float fCalculatedBaseSpeed; // [esp+50h] [ebp-30h]
  float fRPMRatioChange; // [esp+54h] [ebp-2Ch]
  float fHealthFactor; // [esp+58h] [ebp-28h]
  float fPower; // [esp+5Ch] [ebp-24h]
  int iGearAyMax; // [esp+60h] [ebp-20h]
  int iChunkIdx; // [esp+64h] [ebp-1Ch]

  // TEX_OFF_ADVANCED_CARS
  if ((textures_off & TEX_OFF_ADVANCED_CARS) != 0)
    fCarComplexityFactor = 2.0;
  else
    fCarComplexityFactor = 1.0;
  pCar->byAccelerating = -1;                    // Initialize acceleration state and gear change flag
  iGearChanged = 0;
  if (pCar->byThrottlePressed && !pCar->byUnk61)// Check if car can accelerate (throttle pressed and not crashed)
  {
    fHealthFactor = (pCar->fHealth + 34.0f) * 0.01f;// Calculate health factor (0-1) based on car damage, capped at 1.0
    iCarDesignIdx = pCar->byCarDesignIdx;
    pCar->iEngineState = 10;
    pEngineData = &CarEngines.engines[iCarDesignIdx];
    if (fHealthFactor > 1.0)
      fHealthFactor = 1.0;
    fPower = pCar->fPower;
    iGearAyMax = (char)pCar->byGearAyMax;
    if (pCar->fRPMRatio >= 1.0)               // Check for redline condition (RPM ratio >= 1.0)
    {
      pCar->fWheelSpinFactor = 1.0;             // Redline: limit acceleration and apply engine damage for over-revving
      if (pEngineData->iNumGears - 1 > iGearAyMax && iGearAyMax >= 0 || iGearAyMax == -2 && pCar->fFinalSpeed > 0.0)
        dodamage(pCar, 0.02f);
    } else {
      nCurrChunk = pCar->nCurrChunk;
      if (nCurrChunk == -1)                   // Off-track: apply high acceleration bonus and reduced wheel spin
      {
        pCar->fWheelSpinFactor = 20.0f;
        fPower = fPower + 32.0f;
      } else {
        iNextChunk = nCurrChunk + 1;            // On-track: calculate track physics effects (banking, gravity)
        if (iNextChunk == TRAK_LEN)
          iNextChunk ^= TRAK_LEN;
        iChunkIdx = pCar->nCurrChunk;
        pTrackData = &localdata[iChunkIdx];
        fTrackHalfWidth = ((pCar->pos.fX + pTrackData->fTrackHalfLength) * localdata[iNextChunk].fTrackHalfWidth
                         - (pCar->pos.fX - pTrackData->fTrackHalfLength) * localdata[iChunkIdx].fTrackHalfWidth)
          / (pTrackData->fTrackHalfLength
           * 2.0f);                // Calculate interpolated track half-width at car position
        pTrackInfo = &TrackInfo[iChunkIdx];
        if (pCar->pos.fY <= (double)fTrackHalfWidth)// Select banking angle based on car position (left/right/center of track)
        {
          if (-fTrackHalfWidth <= pCar->pos.fY)
            fAdjustedGravity = pTrackData->gravity.fY;
          else
            fAdjustedGravity = pTrackData->gravity.fY * tcos[pTrackInfo->iRightBankAngle & 0x3FFF] - pTrackData->gravity.fZ * tsin[pTrackInfo->iRightBankAngle & 0x3FFF];
        } else {
          fAdjustedGravity = pTrackData->gravity.fY * tcos[pTrackInfo->iLeftBankAngle & 0x3FFF] + pTrackData->gravity.fZ * tsin[pTrackInfo->iLeftBankAngle & 0x3FFF];
        }
        fGravityFactor = (pTrackData->gravity.fX * tcos[pCar->nYaw] + fAdjustedGravity * tsin[pCar->nYaw]) * 2.0f;// Calculate gravity factor based on track inclination and car orientation
        fNegHealthFactor = -fHealthFactor;
        if (fGravityFactor < (double)fNegHealthFactor)
          fGravityFactor = -fHealthFactor;
        iDriverIdx = pCar->iDriverIdx;
        if (player1_car == iDriverIdx || player2_car == iDriverIdx)// Apply different wheel spin factors for human vs AI players
          pCar->fWheelSpinFactor = (fGravityFactor + 1.0f) * 6.0f;
        else
          pCar->fWheelSpinFactor = 1.0;
        if (cheat_control && iCarDesignIdx == 9)// Special acceleration bonuses: cheat mode, neutral gear, or race position
        {
          fPower = fPower + 32.0f;
        } else if (iGearAyMax == -1) {
          fPower = fCarComplexityFactor * 2.0f + fPower;
        } else if (pCar->fTotalRaceTime >= 20.0f || human_control[pCar->iDriverIdx]) {
          fPower = (fHealthFactor + fCarComplexityFactor + fGravityFactor) * 0.5f + fPower;
        } else {
          fPower = (fHealthFactor + fCarComplexityFactor + fGravityFactor) / (float)(pCar->byRacePosition / 15 + 1) + fPower;
        }
      }
    }
    if (fPower >= 1024.0f)                     // Clamp power output to maximum value (1023)
      fPower = 1023.0f;
    pSpds = pEngineData->pSpds;
    if (iGearAyMax <= 0)
      fDownshiftThreshold = 0.0f;
    else
      fDownshiftThreshold = pSpds[iGearAyMax - 1] * 0.5f;
    if (fabs(pCar->fFinalSpeed / fHealthFactor) < fDownshiftThreshold && human_control[pCar->iDriverIdx] != 2 && iGearAyMax > 0)// Auto downshift: check if speed is too low for current gear
    {
      dDownshiftPower = change_gear(iGearAyMax, iGearAyMax - 1, pCar, iCarDesignIdx);
      --iGearAyMax;
      iGearChanged = -1;
      fPower = (float)dDownshiftPower;
      pCar->byGearAyMax = iGearAyMax;
    }
    if (pEngineData->iNumGears - 1 > iGearAyMax
      && iGearAyMax >= 0
      && human_control[pCar->iDriverIdx] != 2
      && fPower > (double)pEngineData->pChgs[2 * iGearAyMax] * 1.2
      && pCar->fRPMRatio >= (double)eng_chg_revs[12 * iCarDesignIdx + 2 * iGearAyMax])// Auto upshift: check power, RPM, and speed thresholds
    {
      fUpshiftSpeed = pCar->fRPMRatio * pSpds[iGearAyMax] * fHealthFactor * 0.5f;
      if (pCar->fFinalSpeed >= (double)fUpshiftSpeed) {
        dUpshiftPower = change_gear(iGearAyMax, iGearAyMax + 1, pCar, iCarDesignIdx);
        pCar->byGearAyMax = ++iGearAyMax;
        fPower = (float)dUpshiftPower;
        iGearChanged = -1;
      }
    }
    pCar->fPower = fPower;                      // Calculate new RPM ratio using calc_revs function
    if (iGearAyMax < 0)
      dCalculatedRPMRatio = calc_revs(pEngineData->pRevs, 0, fPower);
    else
      dCalculatedRPMRatio = calc_revs(pEngineData->pRevs, iGearAyMax, fPower);
    fNewRPMRatio = (float)dCalculatedRPMRatio;
    fRPMRatioChange = fNewRPMRatio - pCar->fRPMRatio;
    if (pCar->nCurrChunk != -1 && iCarDesignIdx != 9 && iGearAyMax != -1)// Limit RPM ratio changes to realistic values when on track
    {
      if (fRPMRatioChange <= 0.0f) {
        if (fRPMRatioChange < -0.03f)
          fRPMRatioChange = -0.029999999f;
      } else if (fGravityFactor <= 0.0) {
        if (fRPMRatioChange > fCarComplexityFactor * 0.03f)
          fRPMRatioChange = 0.029999999f;
      } else {
        dMaxRPMChange = fCarComplexityFactor * 0.03f + fGravityFactor * 0.02f;
        if (fRPMRatioChange > dMaxRPMChange)
          fRPMRatioChange = (float)dMaxRPMChange;
      }
    }
    pCar->fRPMRatio = pCar->fRPMRatio + fRPMRatioChange;
    if (iGearAyMax == -1)                     // Calculate base speed for different gear types
    {
      pCar->fBaseSpeed = 0.0;
    } else if (iGearAyMax < 0) {
      pCar->fBaseSpeed = -(*pSpds * fNewRPMRatio * fHealthFactor);
    } else {
      fCalculatedBaseSpeed = pSpds[iGearAyMax] * fNewRPMRatio * fHealthFactor;
      pCar->fBaseSpeed = fCalculatedBaseSpeed;
    }
    if (iGearAyMax < 0 && !race_started)      // Reset speed overflow in reverse before race starts
      pCar->fSpeedOverflow = 0.0;
    if (iGearChanged)                         // Update speed overflow when gear changes occur
      pCar->fSpeedOverflow = pCar->fFinalSpeed - pCar->fBaseSpeed;
    if ((char)pCar->byGearAyMax != -1)        // Update car pitch dynamics based on acceleration
    {
      if (iCarDesignIdx == 9) {                                         // Special pitch handling for cheat mode (car design 9)
        if (cheat_control && pCar->fRPMRatio < 1.0) {
          iPitchDelta = 32 * pEngineData->iPitchAccelRate + pCar->iPitchDynamicOffset;
          pCar->iPitchDynamicOffset = iPitchDelta;
          iMaxPitchOffset_1 = pEngineData->iMaxPitchOffset;
          if (12 * iMaxPitchOffset_1 < iPitchDelta)
            pCar->iPitchDynamicOffset = 12 * iMaxPitchOffset_1;
        } else {
          iPitchDynamicOffset = pCar->iPitchDynamicOffset;
          iMaxPitchOffset = pEngineData->iMaxPitchOffset;
          if (iPitchDynamicOffset > iMaxPitchOffset) {
            fPitchDecayAmount = (float)(iPitchDynamicOffset - iMaxPitchOffset);
            if ((double)(48 * pEngineData->iPitchAccelRate) < fPitchDecayAmount)// Handle extreme pitch: reset camera offsets and apply damage
            {
              pCar->iUnk35_3 = 0;
              pCar->iUnk36_2 = 0;
              pCar->iRollCameraOffset = 0;
              iOldPitchOffset = pCar->iPitchDynamicOffset;
              pCar->iPitchDynamicOffset = 0;
              pCar->iPitchCameraOffset = iOldPitchOffset;
              fPitchDecayAmount = 0.0;
              pCar->iPitchBackup = iOldPitchOffset;
            }
            dPitchDecay = (double)pCar->iPitchDynamicOffset - fPitchDecayAmount;
            //_CHP();
            pCar->iPitchDynamicOffset = (int)dPitchDecay;
          } else {
            pCar->iPitchDynamicOffset += pEngineData->iPitchAccelRate;
          }
        }
      } else {
        iPitchDeltaNormal = pEngineData->iPitchAccelRate + pCar->iPitchDynamicOffset;// Normal cars: increase pitch with acceleration, clamp to max
        pCar->iPitchDynamicOffset = iPitchDeltaNormal;
        iMaxPitchNormal = pEngineData->iMaxPitchOffset;
        if (iPitchDeltaNormal > iMaxPitchNormal)
          pCar->iPitchDynamicOffset = iMaxPitchNormal;
      }
    }
  }
}

//-------------------------------------------------------------------------------------------------
//0002B990
void Decelerate(tCar *pCar)
{
  int iCarDesignIdx; // edi
  tCarEngine *pEngineData; // esi
  int byGearAyMax; // ecx
  int iCurrChunk; // eax
  double dInitialDecelerationCalc; // st7
  int iNextChunk; // eax
  tData *pTrackData; // edx
  tTrackInfo *pTrackInfo; // ebp
  double dGravityFactor; // st7
  double dCalculatedPower; // st7
  double dRPMRatioChange; // st7
  int iPitchDelta; // ebp
  int iMinPitchOffset; // edx
  int iPitchDeltaNeg; // esi
  int iPitchDeltaPos; // edx
  float fTrackHalfWidth; // [esp+18h] [ebp-44h]
  float fAdjustedGravity; // [esp+1Ch] [ebp-40h]
  int iNextChunkIdx; // [esp+20h] [ebp-3Ch]
  float fRPMRatioChange; // [esp+24h] [ebp-38h]
  float fDecelerationRate; // [esp+28h] [ebp-34h]
  float fCurrentPower; // [esp+2Ch] [ebp-30h]
  float *pSpds; // [esp+30h] [ebp-2Ch]
  float fGravityMultiplier; // [esp+34h] [ebp-28h]
  float fHealthFactor; // [esp+38h] [ebp-24h]
  float fRPMRatio; // [esp+3Ch] [ebp-20h]
  float fBaseSpeed; // [esp+40h] [ebp-1Ch]
  float fNewBaseSpeed; // [esp+40h] [ebp-1Ch]
  float fNewSpeedOverflow; // [esp+40h] [ebp-1Ch]

  pCar->byAccelerating = 0;                            // Initialize car status flags for deceleration
  pCar->iEngineState = 6;
  fHealthFactor = (pCar->fHealth + 34.0f) * 0.01f;// Calculate health factor (0-1) based on car damage, capped at 1.0
  iCarDesignIdx = pCar->byCarDesignIdx;
  pEngineData = &CarEngines.engines[iCarDesignIdx];
  fBaseSpeed = pCar->fBaseSpeed;
  if (fHealthFactor > 1.0)
    fHealthFactor = 1.0;
  byGearAyMax = (char)pCar->byGearAyMax;
  pSpds = pEngineData->pSpds;
  if (byGearAyMax < 0)                        // Handle reverse gear: calculate base speed using RPM ratio
    fBaseSpeed = pCar->fRPMRatio * *pEngineData->pSpds * fHealthFactor;
  iCurrChunk = pCar->nCurrChunk;
  fDecelerationRate = pSpds[pEngineData->iNumGears - 1] / (pEngineData->fDragCoefficient * 36.0f);// Calculate base deceleration rate from top gear max speed
  if (iCurrChunk == -1)                       // Off-track: apply 3x deceleration penalty
  {
    dInitialDecelerationCalc = fBaseSpeed - fDecelerationRate * 3.0f;
  } else if (human_control[pCar->iDriverIdx])   // Human players: apply track banking and gravity effects
  {
    iNextChunk = iCurrChunk + 1;
    iNextChunkIdx = iNextChunk;
    if (iNextChunk == TRAK_LEN)
      iNextChunkIdx = TRAK_LEN ^ iNextChunk;
    pTrackData = &localdata[pCar->nCurrChunk];
    fTrackHalfWidth = ((pCar->pos.fX + pTrackData->fTrackHalfLength) * localdata[iNextChunkIdx].fTrackHalfWidth
                     - (pCar->pos.fX - pTrackData->fTrackHalfLength) * localdata[pCar->nCurrChunk].fTrackHalfWidth)
      / (pTrackData->fTrackHalfLength
       * 2.0f);                    // Calculate interpolated track half-width at car position
    pTrackInfo = &TrackInfo[pCar->nCurrChunk];
    if (pCar->pos.fY <= (double)fTrackHalfWidth)// Select banking angle based on car position (left/right/center of track)
    {
      if (-fTrackHalfWidth <= pCar->pos.fY)
        fAdjustedGravity = pTrackData->gravity.fY;
      else
        fAdjustedGravity = pTrackData->gravity.fY * tcos[pTrackInfo->iRightBankAngle & 0x3FFF] - pTrackData->gravity.fZ * tsin[pTrackInfo->iRightBankAngle & 0x3FFF];
    } else {
      fAdjustedGravity = pTrackData->gravity.fY * tcos[pTrackInfo->iLeftBankAngle & 0x3FFF] + pTrackData->gravity.fZ * tsin[pTrackInfo->iLeftBankAngle & 0x3FFF];
    }
    dGravityFactor = (pTrackData->gravity.fX * tcos[pCar->nYaw] + fAdjustedGravity * tsin[pCar->nYaw]) * -0.3333333333333333 + 1.0;// Calculate gravity factor based on track inclination and car orientation
    fGravityMultiplier = (float)dGravityFactor;
    if (dGravityFactor < 0.5)
      fGravityMultiplier = 0.5f;
    dInitialDecelerationCalc = fBaseSpeed - fDecelerationRate * fGravityMultiplier;
  } else {
    dInitialDecelerationCalc = fBaseSpeed - fDecelerationRate;// AI players: apply standard deceleration rate
  }
  fNewBaseSpeed = (float)dInitialDecelerationCalc;
  if (fNewBaseSpeed < 0.0)
    fNewBaseSpeed = 0.0;
  if (byGearAyMax >= 0)                       // Calculate RPM ratio and power for current gear
  {
    fRPMRatio = fNewBaseSpeed / (pSpds[byGearAyMax] * fHealthFactor);
    if (fRPMRatio > 1.0)
      fRPMRatio = 1.0f;
    dCalculatedPower = calc_pow(iCarDesignIdx, byGearAyMax, fRPMRatio);
  } else {
    fRPMRatio = fNewBaseSpeed / (*pSpds * fHealthFactor);
    if (fRPMRatio > 1.0)
      fRPMRatio = 1.0f;
    dCalculatedPower = calc_pow(iCarDesignIdx, 0, fRPMRatio);
  }
  fCurrentPower = (float)dCalculatedPower;
  if (byGearAyMax > 0 && human_control[pCar->iDriverIdx] != 2 && (double)pEngineData->pChgs[2 * byGearAyMax - 1] > fCurrentPower)// Auto downshift: check if power is below gear change threshold
  {
    fRPMRatio = fNewBaseSpeed / (pSpds[--byGearAyMax] * fHealthFactor);
    if (fRPMRatio > 1.0)
      fRPMRatio = 1.0f;
    fCurrentPower = (float)calc_pow(iCarDesignIdx, byGearAyMax, fRPMRatio);
  }
  dRPMRatioChange = fRPMRatio - pCar->fRPMRatio;
  pCar->byGearAyMax = byGearAyMax;
  pCar->fPower = fCurrentPower;
  fRPMRatioChange = (float)dRPMRatioChange;
  if (pCar->nCurrChunk != -1 && byGearAyMax != -1) {                                             // Limit RPM ratio changes to realistic values when on track
    if (fRPMRatioChange <= 0.03) {
      if (fRPMRatioChange < -0.1)
        fRPMRatioChange = -0.1f;
    } else {
      fRPMRatioChange = 0.029999999f;
    }
  }
  pCar->fRPMRatio = pCar->fRPMRatio + fRPMRatioChange;
  if (byGearAyMax == -1)                      // Handle special cases: neutral gear (0) and reverse gear (negate speed)
  {
    fNewBaseSpeed = 0.0;
  } else if (byGearAyMax == -2) {
    fNewBaseSpeed = -fNewBaseSpeed;
    //HIBYTE(fNewBaseSpeed) ^= 0x80u;
  }
  pCar->fBaseSpeed = fNewBaseSpeed;
  fNewSpeedOverflow = pCar->fSpeedOverflow - fDecelerationRate;// Update speed overflow, reducing it by deceleration rate
  if (fNewSpeedOverflow < 0.0)
    fNewSpeedOverflow = 0.0;
  pCar->fSpeedOverflow = fNewSpeedOverflow;
  if (byGearAyMax < 0)
    pCar->fSpeedOverflow = 0.0;
  if (pCar->fFinalSpeed <= 0.0)               // Update car pitch dynamics based on movement direction
  {
    if (pCar->iPitchDynamicOffset >= 0) {
      iPitchDeltaPos = pCar->iPitchDynamicOffset - pEngineData->iNoseUpRecoveryRate;
      pCar->iPitchDynamicOffset = iPitchDeltaPos;
      if (iPitchDeltaPos >= 0)
        return;
    } else {
      iPitchDeltaNeg = pEngineData->iNoseDownRecoveryRate + pCar->iPitchDynamicOffset;
      pCar->iPitchDynamicOffset = iPitchDeltaNeg;
      if (iPitchDeltaNeg <= 0)
        return;
    }
    pCar->iPitchDynamicOffset = 0;
  } else {
    iPitchDelta = pCar->iPitchDynamicOffset - pEngineData->iPitchDecayRate;
    pCar->iPitchDynamicOffset = iPitchDelta;
    iMinPitchOffset = pEngineData->iMinPitchOffset;
    if (iPitchDelta < iMinPitchOffset)
      pCar->iPitchDynamicOffset = iMinPitchOffset;
  }
}

//-------------------------------------------------------------------------------------------------
//0002BDD0
void FreeWheel(tCar *pCar)
{
  int iCarDesignIdx; // esi
  int iGearAyMax; // ecx
  tCarEngine *pEngineData; // edi
  int iCurrChunk; // eax
  double dInitialDecelerationCalc; // st7
  int iNextChunk; // eax
  tData *pTrackData; // edx
  tTrackInfo *pTrackInfo; // ebp
  double dGravityFactor; // st7
  double dCalculatedPower; // st7
  double dRPMRatioChange; // st7
  int iPitchDynamicOffset; // esi
  int iPitchDeltaNeg; // edx
  int iNoseUpRecoveryRate; // eax
  float fAdjustedDecelerationRate; // [esp+18h] [ebp-48h]
  float fDecelerationRate; // [esp+1Ch] [ebp-44h]
  float fTrackHalfWidth; // [esp+20h] [ebp-40h]
  float fAdjustedGravity; // [esp+24h] [ebp-3Ch]
  int iNextChunkIdx; // [esp+28h] [ebp-38h]
  float fCurrentPower; // [esp+2Ch] [ebp-34h]
  float fRPMRatioChange; // [esp+30h] [ebp-30h]
  float *pSpds; // [esp+34h] [ebp-2Ch]
  float fGravityMultiplier; // [esp+38h] [ebp-28h]
  float fHealthFactor; // [esp+3Ch] [ebp-24h]
  float fRPMRatio; // [esp+40h] [ebp-20h]
  float fBaseSpeed; // [esp+44h] [ebp-1Ch]
  float fNewBaseSpeed; // [esp+44h] [ebp-1Ch]

  pCar->byAccelerating = 0;                     // Initialize freewheeling state and engine status
  pCar->iEngineState = 8;
  fHealthFactor = (pCar->fHealth + 34.0f) * 0.01f;// Calculate health factor (0-1) based on car damage, capped at 1.0
  iCarDesignIdx = pCar->byCarDesignIdx;
  iGearAyMax = (char)pCar->byGearAyMax;
  fBaseSpeed = pCar->fBaseSpeed;
  pEngineData = &CarEngines.engines[iCarDesignIdx];
  if (fHealthFactor > 1.0)
    fHealthFactor = 1.0;
  pSpds = pEngineData->pSpds;
  if (iGearAyMax < 0)                         // Handle reverse gear: calculate base speed using RPM ratio
    fBaseSpeed = pCar->fRPMRatio * *pEngineData->pSpds * fHealthFactor;
  iCurrChunk = pCar->nCurrChunk;
  fDecelerationRate = pSpds[pEngineData->iNumGears - 1] / (pEngineData->fDragCoefficient * 256.0f);// Calculate base deceleration rate from top gear max speed and drag coefficient
  if (iCurrChunk == -1)                       // Off-track: apply 16x deceleration penalty
  {
    dInitialDecelerationCalc = fBaseSpeed - fDecelerationRate * 16.0;
  } else {
    iNextChunk = iCurrChunk + 1;                // On-track: calculate track physics effects (banking, gravity)
    iNextChunkIdx = iNextChunk;
    if (iNextChunk == TRAK_LEN)
      iNextChunkIdx = TRAK_LEN ^ iNextChunk;
    pTrackData = &localdata[pCar->nCurrChunk];
    fTrackHalfWidth = ((pCar->pos.fX + pTrackData->fTrackHalfLength) * localdata[iNextChunkIdx].fTrackHalfWidth
                     - (pCar->pos.fX - pTrackData->fTrackHalfLength) * localdata[pCar->nCurrChunk].fTrackHalfWidth)
      / (pTrackData->fTrackHalfLength
       * 2.0f);                    // Calculate interpolated track half-width at car position
    pTrackInfo = &TrackInfo[pCar->nCurrChunk];
    if (pCar->pos.fY <= (double)fTrackHalfWidth)// Select banking angle based on car position (left/right/center of track)
    {
      if (-fTrackHalfWidth <= pCar->pos.fY)
        fAdjustedGravity = pTrackData->gravity.fY;// fY = adjusted gravity Y component based on track banking
      else
        fAdjustedGravity = pTrackData->gravity.fY * tcos[pTrackInfo->iRightBankAngle & 0x3FFF] - pTrackData->gravity.fZ * tsin[pTrackInfo->iRightBankAngle & 0x3FFF];
    } else {
      fAdjustedGravity = pTrackData->gravity.fY * tcos[pTrackInfo->iLeftBankAngle & 0x3FFF] + pTrackData->gravity.fZ * tsin[pTrackInfo->iLeftBankAngle & 0x3FFF];
    }
    dGravityFactor = (pTrackData->gravity.fX * tcos[pCar->nYaw] + fAdjustedGravity * tsin[pCar->nYaw]) * -0.3333333333333333f + 1.0f;// Calculate gravity factor based on track inclination and car orientation
    fGravityMultiplier = (float)dGravityFactor;
    if (dGravityFactor < 0.5)
      fGravityMultiplier = 0.5f;
    fAdjustedDecelerationRate = fDecelerationRate * fGravityMultiplier;
    if (iGearAyMax == -1)                     // Apply different deceleration rates: 6x for neutral gear, 1x for forward gears
      dInitialDecelerationCalc = fBaseSpeed - fAdjustedDecelerationRate * 6.0;
    else
      dInitialDecelerationCalc = fBaseSpeed - fAdjustedDecelerationRate;
  }
  fNewBaseSpeed = (float)dInitialDecelerationCalc;
  if (fNewBaseSpeed < 0.0)
    fNewBaseSpeed = 0.0;
  if (iGearAyMax >= 0)                        // Calculate RPM ratio and power for current gear
  {
    fRPMRatio = fNewBaseSpeed / (pSpds[iGearAyMax] * fHealthFactor);
    if (fRPMRatio > 1.0)
      fRPMRatio = 1.0f;
    dCalculatedPower = (float)calc_pow(iCarDesignIdx, iGearAyMax, fRPMRatio);
  } else {
    fRPMRatio = fNewBaseSpeed / (*pSpds * fHealthFactor);
    if (fRPMRatio > 1.0)
      fRPMRatio = 1.0f;
    dCalculatedPower = (float)calc_pow(iCarDesignIdx, 0, fRPMRatio);
  }
  fCurrentPower = (float)dCalculatedPower;
  if (iGearAyMax > 0 && human_control[pCar->iDriverIdx] != 2 && (double)pEngineData->pChgs[2 * iGearAyMax - 1] > fCurrentPower)// Auto downshift: check if power is below gear change threshold
  {
    fRPMRatio = fNewBaseSpeed / (pSpds[--iGearAyMax] * fHealthFactor);
    if (fRPMRatio > 1.0)
      fRPMRatio = 1.0f;
    fCurrentPower = (float)calc_pow(iCarDesignIdx, iGearAyMax, fRPMRatio);
  }
  dRPMRatioChange = fRPMRatio - pCar->fRPMRatio;
  pCar->byGearAyMax = iGearAyMax;
  pCar->fPower = fCurrentPower;
  fRPMRatioChange = (float)dRPMRatioChange;
  if (pCar->nCurrChunk != -1 && iGearAyMax != -1)// Limit RPM ratio changes to realistic values when on track
  {
    if (fRPMRatioChange <= 0.03) {
      if (fRPMRatioChange < -0.1)
        fRPMRatioChange = -0.1f;
    } else {
      fRPMRatioChange = 0.029999999f;
    }
  }
  pCar->fRPMRatio = pCar->fRPMRatio + fRPMRatioChange;
  if (iGearAyMax == -1)                       // Handle special cases: neutral gear (0) and reverse gear (negate speed)
  {
    fNewBaseSpeed = 0.0;
  } else if (iGearAyMax == -2) {
    fNewBaseSpeed = -fNewBaseSpeed;
    //HIBYTE(fNewBaseSpeed) ^= 0x80u;
  }
  iPitchDynamicOffset = pCar->iPitchDynamicOffset;// Update car pitch dynamics: gradual recovery to neutral position
  pCar->fBaseSpeed = fNewBaseSpeed;
  if (iPitchDynamicOffset >= 0) {
    iNoseUpRecoveryRate = pEngineData->iNoseUpRecoveryRate;
    pCar->iPitchDynamicOffset = iPitchDynamicOffset - iNoseUpRecoveryRate;
    if (iPitchDynamicOffset - iNoseUpRecoveryRate >= 0)
      return;
  } else {
    iPitchDeltaNeg = iPitchDynamicOffset + pEngineData->iNoseDownRecoveryRate;
    pCar->iPitchDynamicOffset = iPitchDeltaNeg;
    if (iPitchDeltaNeg <= 0)
      return;
  }
  pCar->iPitchDynamicOffset = 0;
}

//-------------------------------------------------------------------------------------------------
//0002C1A0
void SetEngine(tCar *pCar, float fThrottle)
{
  int byCarDesignIdx; // edi
  float *pSpds; // edx
  int iNumGears; // ecx
  double dThrottleRatio; // st7
  double dCalculatedPower; // st7
  int iCurrentGear; // ebx
  int iGearTableIdx; // ecx
  float *pfCurrentGearSpd; // esi
  double dFinalSpeed; // st7
  float fReverseRatio; // [esp+0h] [ebp-44h]
  float *pfSpeedsArray; // [esp+4h] [ebp-40h]
  float fReverseSpeed; // [esp+8h] [ebp-3Ch]
  float fHealthFactor; // [esp+Ch] [ebp-38h]
  int iMaxGearIdx; // [esp+10h] [ebp-34h]
  tCarEngine *pEngineData; // [esp+14h] [ebp-30h]
  float fGearShiftFlag; // [esp+18h] [ebp-2Ch]
  float fCurrentPower; // [esp+1Ch] [ebp-28h]
  float fAdjustedThrottle; // [esp+20h] [ebp-24h]
  float fSpeedRatio; // [esp+24h] [ebp-20h]
  float fLoopExitFlag; // [esp+28h] [ebp-1Ch]

  fHealthFactor = (pCar->fHealth + 34.0f) * 0.01f;// Calculate health factor (0-1) based on car health, capped at 1.0
  if (fHealthFactor > 1.0)
    fHealthFactor = 1.0;
  byCarDesignIdx = pCar->byCarDesignIdx;
  pCar->fSpeedOverflow = 0.0;
  pEngineData = &CarEngines.engines[byCarDesignIdx];// Get engine data for this car design
  pSpds = pEngineData->pSpds;
  iNumGears = pEngineData->iNumGears;
  pfSpeedsArray = pSpds;
  if (fThrottle >= 0.5)                       // Forward throttle - calculate gear and power
  {
    iCurrentGear = 0;
    fLoopExitFlag = 0.0;
    fAdjustedThrottle = fThrottle / fHealthFactor;// Adjust throttle by health factor
    do {
      if (fAdjustedThrottle > (double)*pSpds) {
        ++iCurrentGear;
        ++pSpds;
        if (iCurrentGear != iNumGears)
          continue;
      }
      fLoopExitFlag = -1.0;
    } while (fabs(fLoopExitFlag) > FLT_EPSILON);// Find appropriate gear for current throttle
    //} while ((LODWORD(fLoopExitFlag) & 0x7FFFFFFF) == 0);// Find appropriate gear for current throttle
    if (iCurrentGear < iNumGears) {
      fSpeedRatio = fAdjustedThrottle / *pSpds;
    } else {
      iCurrentGear = iNumGears - 1;
      fAdjustedThrottle = pfSpeedsArray[iNumGears - 1];
      fSpeedRatio = 1.0;
    }
    fGearShiftFlag = 0.0;
    iMaxGearIdx = iNumGears - 1;
    iGearTableIdx = 2 * iCurrentGear;
    pfCurrentGearSpd = &pfSpeedsArray[iCurrentGear];
    fCurrentPower = (float)calc_pow(byCarDesignIdx, iCurrentGear, fSpeedRatio);// Calculate power for current gear/throttle
    while (iCurrentGear < iMaxGearIdx)        // Check if car can upshift to higher gears
    {
      //if ((LODWORD(fGearShiftFlag) & 0x7FFFFFFF) != 0)
      if (fabs(fGearShiftFlag) > FLT_EPSILON)
        break;
      if ((double)pEngineData->pChgs[iGearTableIdx] * 1.2 >= fCurrentPower) {
        fGearShiftFlag = -1.0;
      } else {
        fSpeedRatio = fAdjustedThrottle / pfCurrentGearSpd[1];
        iGearTableIdx += 2;
        ++iCurrentGear;
        ++pfCurrentGearSpd;
        fCurrentPower = (float)calc_pow(byCarDesignIdx, iCurrentGear, fSpeedRatio);
      }
    }
    pCar->fPower = fCurrentPower;
    pCar->fRPMRatio = fSpeedRatio;
    dFinalSpeed = fSpeedRatio * pfSpeedsArray[iCurrentGear] * fHealthFactor;
    pCar->fBaseSpeed = (float)dFinalSpeed;
    pCar->byGearAyMax = iCurrentGear;
    pCar->fSpeedOverflow = fThrottle - (float)dFinalSpeed;
  } else if (fabs(fThrottle) >= 0.5)            // Reverse throttle - calculate reverse power and speed
  {
    pCar->byGearAyMax = -2;
    fReverseSpeed = *pSpds * fHealthFactor;
    fThrottle = -fThrottle;
    //HIBYTE(fThrottle) ^= 0x80u;
    if (fThrottle <= (double)fReverseSpeed) {
      dThrottleRatio = fThrottle / fReverseSpeed;
      pCar->fSpeedOverflow = 0.0;
      fReverseSpeed = fThrottle;
      fReverseRatio = (float)dThrottleRatio;
    } else {
      fReverseRatio = 1.0;
      pCar->fSpeedOverflow = fReverseSpeed - fThrottle;
    }
    pCar->fBaseSpeed = -fReverseSpeed;
    dCalculatedPower = calc_pow(byCarDesignIdx, 0, fReverseRatio);
    pCar->fRPMRatio = fReverseRatio;
    pCar->fPower = (float)dCalculatedPower;
  } else {
    pCar->byGearAyMax = 0;                      // Neutral/idle - zero all engine output values
    pCar->fPower = 0.0;
    pCar->fRPMRatio = 0.0;
    pCar->fBaseSpeed = 0.0;
    pCar->fSpeedOverflow = 0.0;
    pCar->fFinalSpeed = 0.0;
  }
  pCar->fFinalSpeed = pCar->fBaseSpeed + pCar->fSpeedOverflow;// Final speed = base speed + speed overflow
}

//-------------------------------------------------------------------------------------------------
//0002C420
double change_gear(int iCurrentGear, int iNextGear, tCar *pCar, int iCarDesignIdx)
{
  float fCalculatedPower; // [esp+4h] [ebp-18h]
  float fAdjustedSpeed; // [esp+8h] [ebp-14h]
  float fHealthFactor; // [esp+Ch] [ebp-10h]
  float fSpeedRatio; // [esp+10h] [ebp-Ch]

  fHealthFactor = (pCar->fHealth + 34.0f) * 0.01f;// Calculate health factor (0-1) based on car damage, capped at 1.0
  if (fHealthFactor > 1.0)
    fHealthFactor = 1.0;
  fAdjustedSpeed = (float)fabs(pCar->fFinalSpeed) / fHealthFactor;// Get current speed adjusted by health factor (damaged cars perform worse)
  if (iNextGear < 0)                          // Clamp negative gear to 0 for power curve lookup (reverse uses gear 0 data)
    iNextGear = 0;
  fSpeedRatio = fAdjustedSpeed / CarEngines.engines[iCarDesignIdx].pSpds[iNextGear];// Calculate speed ratio: current speed vs max speed for target gear
  if (fSpeedRatio > 1.0)                      // Clamp speed ratio to 1.0 (can't exceed gear's max RPM)
    fSpeedRatio = 1.0;
  fCalculatedPower = (float)calc_pow(iCarDesignIdx, iNextGear, fSpeedRatio);// Calculate power output for target gear at current speed ratio
  if (player1_car == pCar->iDriverIdx && !DriveView[0])// Play gear shift sound for human players (not in cockpit view)
    sfxsample(SOUND_SAMPLE_GRSHIFT, 12000);                        // SOUND_SAMPLE_GRSHIFT
  if (player2_car == pCar->iDriverIdx && !DriveView[0])
    sfxsample(SOUND_SAMPLE_GRSHIFT, 12000);                        // SOUND_SAMPLE_GRSHIFT
  return fCalculatedPower;                      // Return calculated power for the gear change
}

//-------------------------------------------------------------------------------------------------
//0002C5A0
void updatecar2(tCar *pCar, int a2, int a3, int a4)
{
  /*
  int v4; // edi
  int v5; // ecx
  int v6; // edx
  int v7; // eax
  int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // ecx
  int v12; // ecx
  int v13; // eax
  int v14; // ecx
  int v15; // eax
  int v16; // ebp
  int v17; // edx
  int v18; // edx
  int v19; // edx
  char v20; // cl
  char v21; // al
  char v22; // dl
  int v23; // eax
  double v24; // st7
  int v25; // eax
  int v26; // ebp
  __int16 v27; // dx
  int v28; // ecx
  int v29; // ebp
  int v30; // ebx
  int v31; // edi
  int v32; // eax
  __int16 v33; // di
  double v34; // st7
  __int64 v35; // rax
  double v36; // st7
  double v37; // st6
  double v38; // st7
  double v39; // st6
  double v40; // st7
  int v41; // edx
  double v42; // st7
  int v43; // eax
  long double v44; // st7
  long double v45; // st7
  int v46; // edx
  int v47; // ebx
  int *v48; // eax
  int v49; // eax
  int v50; // ebp
  int *v51; // eax
  int v52; // eax
  int v53; // ebp
  int v54; // eax
  int v55; // edx
  int v56; // ecx
  int *v57; // eax
  int v58; // eax
  int v59; // ebp
  int *v60; // edx
  int v61; // ebx
  int v62; // ebp
  int v63; // eax
  int v64; // edx
  int v65; // eax
  int v66; // edi
  int v67; // edx
  unsigned int v68; // eax
  float *v69; // ecx
  int v70; // ebx
  int v71; // edx
  double v72; // st7
  double v73; // st5
  double v74; // st6
  int v75; // eax
  double v76; // st7
  double v77; // st7
  int v78; // eax
  int v79; // edx
  double v80; // st7
  double v81; // st7
  int v82; // eax
  _BOOL1 v83; // zf
  int v84; // edx
  int v85; // eax
  int v86; // ebp
  int v87; // ecx
  int v88; // edx
  int v89; // edx
  int v90; // ecx
  int v91; // eax
  double v92; // st7
  int v93; // eax
  int v94; // ecx
  int v95; // edx
  double v96; // st7
  char v97; // bl
  int v98; // edx
  int v99; // ebx
  double v100; // st7
  float *v101; // edx
  int *v102; // edi
  int v103; // eax
  int v104; // ebp
  double v105; // st7
  double v106; // st7
  double v107; // st7
  double v108; // st7
  int v109; // eax
  double v110; // st7
  double v111; // st7
  __int64 v112; // rax
  int v113; // ebx
  __int16 v114; // fps
  double v115; // st7
  _BOOL1 v116; // c0
  char v117; // c2
  _BOOL1 v118; // c3
  double v119; // st7
  double v120; // st7
  int v121; // eax
  float *v122; // eax
  double v123; // st7
  int v124; // eax
  int v125; // ebx
  unsigned int v126; // ecx
  int v127; // edx
  double v128; // st7
  double v129; // st7
  int v130; // edx
  __int64 v131; // rax
  int v132; // eax
  long double v133; // st7
  double v134; // st7
  __int16 v135; // fps
  double v136; // st7
  _BOOL1 v137; // c0
  char v138; // c2
  _BOOL1 v139; // c3
  __int64 v140; // rax
  double v141; // st7
  __int16 v142; // fps
  _BOOL1 v143; // c0
  char v144; // c2
  _BOOL1 v145; // c3
  int v146; // eax
  int v147; // eax
  __int64 v148; // rax
  int v149; // ebx
  int v150; // eax
  int v151; // ebp
  __int16 v152; // fps
  double v153; // st7
  _BOOL1 v154; // c0
  char v155; // c2
  _BOOL1 v156; // c3
  double v157; // st7
  __int16 v158; // fps
  _BOOL1 v159; // c0
  char v160; // c2
  _BOOL1 v161; // c3
  __int16 v162; // ax
  __int16 v163; // cx
  double v164; // st7
  int v165; // ebp
  int v166; // eax
  double v167; // st7
  int v168; // eax
  __int16 v169; // ax
  int v170; // ecx
  int v171; // ebx
  __int16 v172; // dx
  int v173; // eax
  double v174; // st7
  double v175; // st5
  double v176; // rtt
  int v177; // ebx
  int v178; // ecx
  double v179; // st7
  int v180; // ecx
  int v181; // ebx
  double v182; // st7
  double v183; // st7
  double v184; // st7
  double v185; // st5
  double v186; // st6
  float v187; // edx
  long double v188; // st7
  int v189; // eax
  int v190; // ebx
  int v191; // eax
  float v192; // [esp+0h] [ebp-190h]
  float v193; // [esp+4h] [ebp-18Ch] BYREF
  float v194; // [esp+8h] [ebp-188h]
  float v195; // [esp+Ch] [ebp-184h]
  float v196; // [esp+10h] [ebp-180h]
  float v197; // [esp+14h] [ebp-17Ch]
  float v198; // [esp+18h] [ebp-178h]
  float v199; // [esp+1Ch] [ebp-174h]
  float v200; // [esp+20h] [ebp-170h]
  float v201; // [esp+24h] [ebp-16Ch]
  float v202; // [esp+28h] [ebp-168h]
  float v203; // [esp+2Ch] [ebp-164h]
  float v204; // [esp+30h] [ebp-160h]
  int v205; // [esp+8Ch] [ebp-104h]
  char v206[4]; // [esp+90h] [ebp-100h] BYREF
  int v207; // [esp+94h] [ebp-FCh]
  int v208; // [esp+98h] [ebp-F8h]
  int v209; // [esp+9Ch] [ebp-F4h]
  float v210; // [esp+A0h] [ebp-F0h]
  int v211; // [esp+A4h] [ebp-ECh]
  float v212; // [esp+A8h] [ebp-E8h]
  float v213; // [esp+ACh] [ebp-E4h]
  float v214; // [esp+B0h] [ebp-E0h]
  float v215; // [esp+B4h] [ebp-DCh]
  float v216; // [esp+B8h] [ebp-D8h]
  float v217; // [esp+BCh] [ebp-D4h]
  int v218; // [esp+C0h] [ebp-D0h]
  float v219; // [esp+C4h] [ebp-CCh]
  float v220; // [esp+C8h] [ebp-C8h]
  float v221; // [esp+CCh] [ebp-C4h]
  float v222; // [esp+D0h] [ebp-C0h]
  int v223; // [esp+D4h] [ebp-BCh]
  int v224; // [esp+D8h] [ebp-B8h]
  float v225; // [esp+DCh] [ebp-B4h]
  int v226; // [esp+E0h] [ebp-B0h]
  int v227; // [esp+E4h] [ebp-ACh]
  int v228; // [esp+E8h] [ebp-A8h]
  int v229; // [esp+ECh] [ebp-A4h]
  float v230; // [esp+F0h] [ebp-A0h]
  float v231; // [esp+F4h] [ebp-9Ch]
  float v232; // [esp+F8h] [ebp-98h]
  float v233; // [esp+FCh] [ebp-94h]
  float v234; // [esp+100h] [ebp-90h]
  float v235; // [esp+104h] [ebp-8Ch]
  float v236; // [esp+108h] [ebp-88h]
  int v237; // [esp+10Ch] [ebp-84h]
  float v238; // [esp+110h] [ebp-80h]
  float v239; // [esp+114h] [ebp-7Ch]
  float v240; // [esp+118h] [ebp-78h]
  float v241; // [esp+11Ch] [ebp-74h]
  float v242; // [esp+120h] [ebp-70h]
  float v243; // [esp+124h] [ebp-6Ch]
  float v244; // [esp+128h] [ebp-68h]
  float v245; // [esp+12Ch] [ebp-64h]
  float v246; // [esp+130h] [ebp-60h]
  float v247; // [esp+134h] [ebp-5Ch]
  float v248; // [esp+138h] [ebp-58h]
  int v249; // [esp+13Ch] [ebp-54h]
  int v250; // [esp+140h] [ebp-50h]
  float v251; // [esp+144h] [ebp-4Ch]
  int v252; // [esp+148h] [ebp-48h]
  int v253; // [esp+14Ch] [ebp-44h]
  int v254; // [esp+150h] [ebp-40h]
  float v255; // [esp+154h] [ebp-3Ch]
  int *v256; // [esp+158h] [ebp-38h]
  int v257; // [esp+15Ch] [ebp-34h]
  float v258; // [esp+160h] [ebp-30h]
  float v259; // [esp+164h] [ebp-2Ch]
  float v260; // [esp+168h] [ebp-28h]
  float v261; // [esp+16Ch] [ebp-24h]
  float v262; // [esp+170h] [ebp-20h]
  int v263; // [esp+174h] [ebp-1Ch]

  v237 = *(unsigned __int8 *)(a1 + 102);
  v229 = *(_DWORD *)(a1 + 64);
  v249 = *(_DWORD *)(a1 + 68);
  v257 = *(__int16 *)(a1 + 20);
  v253 = *(__int16 *)(a1 + 12);
  v256 = &CarEngines[28 * v237];
  if (*(_DWORD *)(a1 + 72) != 3)
    goto LABEL_45;
  BYTE1(a3) = -1;
  v4 = 0;
  v5 = 0;
  v6 = 0;
  v218 = -1;
  if (numcars > 0) {
    v7 = 0;
    while (1) {
      a3 = Car_variable_51[v7];
      if (a3 < 3 || TRAK_LEN - 4 < a3)
        break;
      if (Car_variable_51[v7] + TRAK_LEN * Car_variable_24[v7 * 4] > v5) {
        v4 = v6;
        v5 = Car_variable_51[v7] + TRAK_LEN * Car_variable_24[v7 * 4];
      }
      BYTE1(a3) = BYTE1(numcars);
      ++v6;
      v7 += 77;
      if (v6 >= numcars)
        goto LABEL_10;
    }
    v218 = 0;
  }
LABEL_10:
  if (v4 != *(_DWORD *)(a1 + 32) && Car_variable_17[77 * v4] == 3 && Car_variable_23[308 * v4] > 0 && v218) {
    a3 = *(__int16 *)(a1 + 12) + TRAK_LEN * *(char *)(a1 + 104);
    v8 = Car_variable_3[154 * v4] == -1 ? Car_variable_51[77 * v4] : Car_variable_3[154 * v4];
    v9 = TRAK_LEN * Car_variable_24[308 * v4] + v8;
    if (lastsample < -18) {
      v10 = TRAK_LEN + a3;
      if (*(_BYTE *)(a1 + 305)) {
        if (v9 >= v10 - 1)
          goto LABEL_30;
        v14 = (__int16)player1_car;
        v15 = *(_DWORD *)(a1 + 32);
        *(_BYTE *)(a1 + 305) = 0;
        if (v14 == v15) {
          BYTE1(a3) = 0;
          speechsample(52, 0x8000, 18, v14);
        }
        v12 = player2_car;
        if (player2_car != *(_DWORD *)(a1 + 32))
          goto LABEL_30;
        v13 = 52;
      } else {
        if (v9 <= v10 + 1)
          goto LABEL_30;
        v11 = (__int16)player1_car;
        a3 = *(_DWORD *)(a1 + 32);
        *(_BYTE *)(a1 + 305) = -1;
        if (v11 == a3) {
          BYTE1(a3) = 0;
          speechsample(51, 0x8000, 18, v11);
        }
        v12 = player2_car;
        if (player2_car != *(_DWORD *)(a1 + 32))
          goto LABEL_30;
        v13 = 51;
      }
      BYTE1(a3) = 0;
      speechsample(v13, 0x8000, 18, v12);
    }
  }
LABEL_30:
  v16 = *(_DWORD *)(a1 + 32);
  if ((__int16)player1_car == v16 || player2_car == v16) {
    BYTE1(a3) = BYTE1(NoOfLaps);
    v17 = 0;
    if (*(char *)(a1 + 104) == NoOfLaps) {
      a3 = TRAK_LEN - *(__int16 *)(a1 + 12);
      if (a3 < 200)
        v17 = -1;
    }
    if (death_race)
      v17 = -1;
    if (*(float *)(a1 + 28) < (double)control_c_variable_58 && !v17) {
      v18 = *(__int16 *)(a1 + 12);
      if (v18 != -1) {
        v19 = v18 - 1;
        if (v19 < 0)
          v19 = TRAK_LEN - 1;
        a3 = *(__int16 *)(a1 + 12);
        if ((TrakColour_variable_5[12 * a3] & 0x100) != 0 && (TrakColour_variable_5[12 * v19] & 0x100) == 0) {
          BYTE1(a3) = 0;
          speechonly(46, 0x8000, 18, *(_DWORD *)(a1 + 32));
        }
      }
    }
  }
LABEL_45:
  v20 = *(_BYTE *)(a1 + 243);
  if (v20)
    *(_BYTE *)(a1 + 243) = v20 - 1;
  v21 = *(_BYTE *)(a1 + 306);
  if (v21)
    *(_BYTE *)(a1 + 306) = v21 - 1;
  v22 = *(_BYTE *)(a1 + 272);
  if (v22)
    *(_BYTE *)(a1 + 272) = v22 - 1;
  LOBYTE(a3) = *(_BYTE *)(a1 + 277);
  if ((_BYTE)a3) {
    BYTE1(a3) = a3 - 1;
    *(_BYTE *)(a1 + 277) = a3 - 1;
  }
  if (*(_BYTE *)(a1 + 240)
    && !*(_BYTE *)(a1 + 243)
    && (*(_DWORD *)(a1 + 120) & 0x7FFFFFFF) == 0
    && !*(_BYTE *)(a1 + 241)) {
    *(_BYTE *)(a1 + 240) = 0;
  }
  if (!*(_BYTE *)(a1 + 240) && !*(_BYTE *)(a1 + 243) && *(_BYTE *)(a1 + 241) && *(_DWORD *)(a1 + 72) == 3) {
    *(float *)&v263 = *(float *)(a1 + 28) * control_c_variable_59 * control_c_variable_60;
    v23 = rand();
    v209 = (20 * v23 - (__CFSHL__((20 * v23) >> 31, 15) + ((20 * v23) >> 31 << 15))) >> 15;
    if (*(float *)&v263 + control_c_variable_61 <= (double)v209 && false_starts) {
      if ((__int16)player1_car == *(_DWORD *)(a1 + 32))
        sfxsample(29, 0x8000, (_WORD)a3);
      if (player2_car == *(_DWORD *)(a1 + 32))
        sfxsample(29, 0x8000, (_WORD)a3);
      *(_BYTE *)(a1 + 243) = 72;
    } else {
      if ((__int16)player1_car == *(_DWORD *)(a1 + 32))
        sfxsample(28, 0x8000, (_WORD)a3);
      if (player2_car == *(_DWORD *)(a1 + 32))
        sfxsample(28, 0x8000, (_WORD)a3);
      *(_BYTE *)(a1 + 240) = -1;
      *(_BYTE *)(a1 + 243) = 36;
    }
  }
  if (*(float *)(a1 + 120) < 1.0) {
    *(_DWORD *)(a1 + 292) = 0;
  } else {
    v24 = *(float *)(a1 + 296) + *(float *)(a1 + 292);
    *(float *)(a1 + 292) = v24;
    if (v24 < control_c_variable_62)
      *(_DWORD *)(a1 + 292) = -998637568;
  }
  v25 = rand();
  v26 = ((v25 - (__CFSHL__(v25 >> 31, 13) + (v25 >> 31 << 13))) >> 13) + 512 + *(_DWORD *)(a1 + 300);
  *(_DWORD *)(a1 + 300) = v26;
  if (v26 >= 0x4000)
    *(_DWORD *)(a1 + 300) = v26 - 0x4000;
  v27 = *(_WORD *)(a1 + 286);
  if (v27 > 0)
    *(_WORD *)(a1 + 286) = v27 - 1;
  if (*(float *)(a1 + 24) >= (double)control_c_variable_63 && v253 >= 0) {
    v28 = *(_DWORD *)(a1 + 64);
    if (v28 > 4096 && v28 < 12288 && !*(_WORD *)(a1 + 286)) {
      v29 = *(_DWORD *)(a1 + 32);
      if ((__int16)player1_car == v29 || player2_car == v29)
        speechsample(26, 0x8000, 18, *(_DWORD *)(a1 + 32));
      *(_WORD *)(a1 + 286) = 360;
    }
  }
  v30 = *(_DWORD *)(a1 + 64);
  if (v30 <= 4096 || v30 >= 12288 && *(float *)(a1 + 24) > 0.0)
    *(_WORD *)(a1 + 286) = 180;
  v31 = *(_DWORD *)(a1 + 32);
  if (((__int16)player1_car == v31 || player2_car == v31)
    && (v253 >= 0 && *(int *)(a1 + 64) < 4096 || *(int *)(a1 + 64) > 12288)) {
    if ((double)samplespeed[v253] <= *(float *)(a1 + 24)) {
      v32 = samplemax[v253];
    } else if (*(float *)(a1 + 24) <= (double)control_c_variable_64) {
      v32 = 0;
    } else {
      v32 = samplemin[v253];
    }
    if (v32) {
      if (*(__int16 *)(a1 + 284) != v253) {
        speechonly(v32 - 1, 0x8000, 18, *(_DWORD *)(a1 + 32));
        *(_WORD *)(a1 + 284) = v253;
      }
    } else {
      *(_WORD *)(a1 + 284) = -1;
    }
  }
  v33 = *(_WORD *)(a1 + 238);
  if (v33)
    *(_WORD *)(a1 + 238) = v33 - 1;
  v245 = (*(float *)(a1 + 28) + control_c_variable_65) * control_c_variable_66;
  if (v245 > 1.0)
    v245 = 1.0;
  *(float *)&v209 = CarEngines_variable_5[28 * v237] - CarEngines_variable_6[28 * v237];
  v35 = *(int *)(a1 + 140);
  *(float *)&v263 = COERCE_FLOAT(abs32(*(_DWORD *)(a1 + 140)));
  v34 = (double)v263 * *(float *)&v209 * control_c_variable_67 + CarEngines_variable_6[28 * v237];
  v210 = tcos[((unsigned __int16)CarEngines_variable_4[28 * v237] * (unsigned __int16)*(_DWORD *)(a1 + 144)) & 0x3FFF];
  LODWORD(v35) = *(_DWORD *)(a1 + 72);
  v213 = v34;
  if ((_DWORD)v35 == 2)
    v36 = (double)*(int *)(a1 + 140) * control_c_variable_68;
  else
    v36 = (double)*(int *)(a1 + 140) * v213;
  _CHP(v35, HIDWORD(v35));
  *(_DWORD *)(a1 + 140) = (int)v36;
  v37 = v36;
  v38 = v210;
  _CHP(v35, HIDWORD(v35));
  *(_DWORD *)(a1 + 148) = (int)(v37 * v210);
  v39 = (double)*(int *)(a1 + 152) * control_c_variable_68;
  _CHP(v35, HIDWORD(v35));
  *(_DWORD *)(a1 + 152) = (int)v39;
  v40 = v38 * v39;
  _CHP(v35, HIDWORD(v35));
  *(_DWORD *)(a1 + 156) = (int)v40;
  v41 = *(_DWORD *)(a1 + 72);
  if (v41 == 3 || v41 == 2)
    ++*(_DWORD *)(a1 + 144);
  v42 = *(float *)(a1 + 112);
  v259 = *(float *)(a1 + 116);
  v43 = *(__int16 *)(a1 + 12);
  v239 = v42 + v259 - *(float *)(a1 + 24);
  if (v43 != -1 && *(_BYTE *)(a1 + 102) != 9) {
    if (v239 <= (double)control_c_variable_69) {
      if (v239 < (double)control_c_variable_70)
        v239 = -6.0;
    } else {
      v239 = 2.0;
    }
  }
  v44 = *(float *)(a1 + 24) + v239;
  v258 = v44;
  if (fabs(v44) < control_c_variable_71) {
    v258 = 0.0;
    v259 = 0.0;
  }
  v45 = v258;
  *(float *)(a1 + 24) = v258;
  v258 = fabs(v45);
  updatesmokeandflames(a1);
  if (v258 > 0.0) {
    if (v258 >= (double)control_c_variable_72) {
      *(_BYTE *)(a1 + 278) = 4;
    } else {
      v262 = *(float *)(a1 + 108) - v258;
      if (v262 < 0.0)
        ++*(_BYTE *)(a1 + 278);
      if (v258 >= (double)control_c_variable_73) {
        while (v262 < 0.0)
          v262 = v262 + control_c_variable_72;
        if (*(char *)(a1 + 278) > 3)
          *(_BYTE *)(a1 + 278) = 2;
      } else {
        while (v262 < 0.0)
          v262 = v262 + control_c_variable_58;
        if (*(char *)(a1 + 278) > 1)
          *(_BYTE *)(a1 + 278) = 0;
      }
      *(float *)(a1 + 108) = v262;
    }
  }
  if (v253 != -1)
    *(_WORD *)(a1 + 14) = v253;
  if (v253 != -1)
    *(_DWORD *)(a1 + 216) = v253;
  v46 = *(_DWORD *)(a1 + 76);
  if ((double)v256[22] > v258)
    v46 = 0;
  if ((cheat_mode & 0x8000u) != 0) {
    if (v46 < 0) {
      v47 = *(_DWORD *)(a1 + 136) - 8 * v256[15];
      v48 = v256;
      *(_DWORD *)(a1 + 136) = v47;
      v49 = -8 * v48[16];
      if (v49 > v47)
        *(_DWORD *)(a1 + 136) = v49;
      goto LABEL_171;
    }
    if (v46 > 0) {
      v50 = 8 * v256[15] + *(_DWORD *)(a1 + 136);
      v51 = v256;
      *(_DWORD *)(a1 + 136) = v50;
      v52 = 8 * v51[16];
      if (v52 < v50)
        *(_DWORD *)(a1 + 136) = v52;
      goto LABEL_171;
    }
    v53 = *(_DWORD *)(a1 + 136);
    if (v53 <= 0) {
      v55 = 4 * v256[17] + v53;
      *(_DWORD *)(a1 + 136) = v55;
      if (v55 <= 0)
        goto LABEL_171;
    } else {
      v54 = 4 * v256[17];
      *(_DWORD *)(a1 + 136) = v53 - v54;
      if (v53 - v54 >= 0)
        goto LABEL_171;
    }
  LABEL_170:
    *(_DWORD *)(a1 + 136) = 0;
    goto LABEL_171;
  }
  if (v46 <= 0) {
    if (v46 >= 0) {
      v62 = *(_DWORD *)(a1 + 136);
      if (v62 <= 0) {
        v64 = v256[17] + v62;
        *(_DWORD *)(a1 + 136) = v64;
        if (v64 <= 0)
          goto LABEL_171;
      } else {
        v63 = v256[17];
        *(_DWORD *)(a1 + 136) = v62 - v63;
        if (v62 - v63 >= 0)
          goto LABEL_171;
      }
      goto LABEL_170;
    }
    v59 = v256[15] + *(_DWORD *)(a1 + 136);
    v60 = v256;
    *(_DWORD *)(a1 + 136) = v59;
    v61 = v60[16];
    if (v59 > v61)
      *(_DWORD *)(a1 + 136) = v61;
  } else {
    v56 = *(_DWORD *)(a1 + 136) - v256[15];
    v57 = v256;
    *(_DWORD *)(a1 + 136) = v56;
    v58 = -v57[16];
    if (v58 > v56)
      *(_DWORD *)(a1 + 136) = v58;
  }
LABEL_171:
  *(_DWORD *)(a1 + 52) = *(_DWORD *)a1;
  *(_DWORD *)(a1 + 56) = *(_DWORD *)(a1 + 4);
  v65 = ViewType[0];
  v66 = *(_DWORD *)(a1 + 32);
  *(float *)(a1 + 60) = *(float *)(a1 + 8);
  if (v65 == v66)
    doviewtend(a1, 1, 0);
  if (ViewType_variable_1 == *(_DWORD *)(a1 + 32))
    doviewtend(a1, 1, 1);
  v67 = *(__int16 *)(a1 + 12);
  v68 = *(_DWORD *)(a1 + 72);
  v69 = (float *)((char *)&localdata + 128 * v67);
  if (v68 < 2) {
    if (!v68) {
      *(float *)(a1 + 48) = *(float *)(a1 + 48) + control_c_variable_78;
      *(float *)a1 = *(float *)(a1 + 40) + *(float *)a1;
      *(float *)(a1 + 4) = *(float *)(a1 + 44) + *(float *)(a1 + 4);
      v164 = *(float *)(a1 + 48) + *(float *)(a1 + 8);
      v263 = *(int *)(a1 + 36);
      v224 = *(_DWORD *)(a1 + 48);
      v214 = *(float *)&v263;
      v165 = v263;
      v211 = v224;
      *(float *)(a1 + 8) = v164;
      if ((v165 & 0x7FFFFFFF) != 0 || (v224 & 0x7FFFFFFF) != 0) {
        IF_DATAN2(v214);
        v167 = v214 * control_c_variable_74 / control_c_variable_75;
        _CHP(v168, v67);
        v263 = (int)v167;
        v166 = (int)v167 & 0x3FFF;
      } else {
        LOWORD(v166) = 0;
      }
      *(_WORD *)(a1 + 18) = v166;
      v169 = *(_WORD *)(a1 + 200) + *(_WORD *)(a1 + 16);
      HIBYTE(v169) &= 0x3Fu;
      v170 = *(_DWORD *)(a1 + 64);
      *(_WORD *)(a1 + 16) = v169;
      v171 = ((_WORD)v170 - *(_WORD *)(a1 + 20)) & 0x3FFF;
      v257 = *(__int16 *)(a1 + 20);
      if ((unsigned int)v171 > 0x2000)
        v171 -= 0x4000;
      if ((int)abs32(v171) > 400) {
        if (v171 <= 0)
          v257 -= 400;
        else
          v257 += 400;
        v257 &= 0x3FFFu;
      } else {
        v257 = v170;
      }
      *(_WORD *)(a1 + 20) = v257;
      landontrack(a1);
      if ((*(_DWORD *)(a1 + 28) & 0x7FFFFFFF) == 0 && *(__int16 *)(a1 + 100) < -90)
        goto LABEL_501;
    }
    goto LABEL_502;
  }
  if (v68 > 2) {
    if (v68 != 3)
      goto LABEL_502;
    if ((TrakColour_variable_5[12 * v67] & 0x100) == 0)
      *(_BYTE *)(a1 + 244) = 0;
    v70 = *(__int16 *)(a1 + 12);
    v71 = v70 + 1;
    if (v70 + 1 == TRAK_LEN)
      v71 ^= TRAK_LEN;
    v72 = *(float *)a1 + v69[12];
    v208 = localdata_variable_5[32 * v70];
    v207 = localdata_variable_5[32 * v71];
    v73 = *(float *)a1 - v69[12];
    v74 = 1.0 / (v69[12] * control_c_variable_69);
    v261 = (v72 * *(float *)&v207 - v73 * *(float *)&v208) * v74;
    v208 = TrackInfo[9 * v70];
    v207 = TrackInfo[9 * v71];
    v235 = (v72 * *(float *)&v207 - v73 * *(float *)&v208) * v74;
    v207 = TrackInfo_variable_2[9 * v71];
    v208 = TrackInfo_variable_2[9 * v70];
    leftang = 0;
    rightang = 0;
    v75 = TrackInfo_variable_6[9 * v70] - 1;
    v244 = (v72 * *(float *)&v207 - v73 * *(float *)&v208) * v74;
    switch (v75) {
      case 0:
      case 2:
      case 3:
      case 6:
      case 7:
        v76 = v69[12] * control_c_variable_69;
        goto LABEL_188;
      case 4:
      case 5:
      case 8:
        v76 = v69[12] * control_c_variable_69;
        v208 = localdata_variable_5[32 * v70];
        v207 = localdata_variable_5[32 * v71];
      LABEL_188:
        IF_DATAN2(v76);
        v77 = v76 * control_c_variable_74 / control_c_variable_75;
        _CHP(v78, v71);
        v209 = (int)v77;
        leftang = (int)v77 & 0x3FFF;
        break;
      default:
        break;
    }
    switch (TrackInfo_variable_7[9 * v70]) {
      case 1:
      case 3:
      case 4:
      case 7:
      case 8:
        v79 = v71 << 7;
        v80 = v69[12] * control_c_variable_69;
        goto LABEL_192;
      case 5:
      case 6:
      case 9:
        v80 = v69[12] * control_c_variable_69;
        v208 = localdata_variable_5[32 * v70];
        v79 = v71 << 7;
        v207 = *(int *)((char *)localdata_variable_5 + v79);
      LABEL_192:
        IF_DATAN2(v80);
        v81 = v80 * control_c_variable_74 / control_c_variable_75;
        _CHP(v82, v79);
        v205 = (int)v81;
        rightang = (int)v81 & 0x3FFF;
        break;
      default:
        break;
    }
    if (*(float *)(a1 + 4) <= (double)v261) {
      if (-v261 <= *(float *)(a1 + 4))
        *(_DWORD *)(a1 + 212) = 1;
      else
        *(_DWORD *)(a1 + 212) = 2;
    } else {
      *(_DWORD *)(a1 + 212) = 0;
    }
    if (finished_car[*(_DWORD *)(a1 + 32)] || death_race) {
      v84 = 0;
      v83 = 1;
    } else {
      v84 = *((_DWORD *)&TrakColour + 6 * *(__int16 *)(a1 + 12) + *(_DWORD *)(a1 + 212)) & 0x2000000;
      v83 = v84 == 0;
    }
    if (v83)
      Car_variable_33[0] &= ~8u;
    if ((LODWORD(v258) & 0x7FFFFFFF) != 0)
      *(_BYTE *)(a1 + 304) = 0;
    if ((LODWORD(v258) & 0x7FFFFFFF) != 0 || !v84 || (*(_BYTE *)(a1 + 131) & 4) != 0) {
      *(_BYTE *)(a1 + 184) = 0;
    } else {
      v85 = (__int16)player1_car;
      v86 = *(_DWORD *)(a1 + 32);
      *(_BYTE *)(a1 + 276) = 8;
      if ((v85 == v86 || player2_car == v86)
        && !*(_BYTE *)(a1 + 304)
        && *(float *)(a1 + 28) < (double)control_c_variable_73) {
        v87 = *(_DWORD *)(a1 + 32);
        *(_BYTE *)(a1 + 304) = -1;
        speechonly(41, 0x8000, 18, v87);
      }
      *(_BYTE *)(a1 + 184) = -1;
      v88 = *(__int16 *)(a1 + 12);
      *(_BYTE *)(a1 + 131) |= 8u;
      if ((TrakColour_variable_5[12 * v88] & 0x400) != 0) {
        v89 = 0;
        if (numcars > 0) {
          v90 = numcars;
          v91 = 0;
          do {
            if (v89 != *(_DWORD *)(a1 + 32) && *(__int16 *)(a1 + 12) == Car_variable_49[v91])
              Car_variable_49[v91] = -1;
            ++v89;
            v91 += 77;
          } while (v89 < v90);
        }
        *(_DWORD *)(a1 + 208) = *(__int16 *)(a1 + 12);
      }
      v92 = *(float *)(a1 + 28) + control_c_variable_79;
      *(float *)(a1 + 28) = v92;
      if (v92 >= control_c_variable_73) {
        v93 = (__int16)player1_car;
        v94 = *(_DWORD *)(a1 + 32);
        *(_DWORD *)(a1 + 28) = 1120403456;
        if ((v93 == v94 || player2_car == v94) && *(_BYTE *)(a1 + 304)) {
          speechonly(42, 0x8000, 18, *(_DWORD *)(a1 + 32));
          *(_BYTE *)(a1 + 304) = 0;
        }
        *(_BYTE *)(a1 + 184) = 0;
        *(_BYTE *)(a1 + 131) = 0;
      }
    }
    v95 = localdata_variable_12[32 * *(__int16 *)(a1 + 12)];
    if (*(float *)(a1 + 4) > (double)v261)
      v95 = localdata_variable_13[32 * *(__int16 *)(a1 + 12)];
    if (-v261 > *(float *)(a1 + 4))
      v95 = localdata_variable_14[32 * *(__int16 *)(a1 + 12)];
    if ((cheat_mode & 0x400) != 0)
      v95 = 10;
    v96 = (double)surface_variable_1[4 * v95];
    v241 = *(float *)&surface[4 * v95];
    v97 = *(_BYTE *)(a1 + 131);
    v242 = (v96 + CarEngines_variable_8[28 * v237]) / (control_c_variable_81 - v245 * control_c_variable_80);
    if ((v97 & 4) != 0)
      v246 = 10.0;
    else
      v246 = *(float *)&CarEngines_variable_9[28 * v237];
    if (v242 > (double)v246)
      v242 = v246;
    if (v242 < 0.0)
      v242 = 0.0;
    v98 = 4 * v95;
    v234 = surface_variable_2[v98] * v245;
    v240 = ((double)surface_variable_3[v98] + CarEngines_variable_8[28 * v237])
      / (control_c_variable_81 - v245 * control_c_variable_80);
    v246 = v246 * control_c_variable_82;
    if (v240 > (double)v246)
      v240 = v246;
    if (v240 < 0.0)
      v240 = 0.0;
    v99 = *(__int16 *)(a1 + 12);
    v100 = *(float *)(a1 + 4);
    v101 = (float *)((char *)&localdata + 128 * v99);
    v102 = &TrackInfo[9 * v99];
    v222 = v101[19];
    if (v100 <= v261) {
      if (-v261 <= *(float *)(a1 + 4))
        v236 = v101[20];
      else
        v236 = v101[20] * tcos[v102[5] & 0x3FFF] - v101[21] * tsin[v102[5] & 0x3FFF];
    } else {
      v236 = v101[20] * tcos[v102[4] & 0x3FFF] + v101[21] * tsin[v102[4] & 0x3FFF];
    }
    v103 = *(__int16 *)(a1 + 20);
    v233 = v222 * tcos[v103] + v236 * tsin[v103];
    v212 = -v222 * tsin[v103] + v236 * tcos[v103];
    v104 = *(_DWORD *)(a1 + 120);
    v248 = v258 * control_c_variable_83;
    if (v104 != 1065353216 || *(char *)(a1 + 128) == -1) {
      if ((LODWORD(v233) & 0x7FFFFFFF) == 0) {
        if (v259 >= 0.0) {
          if (v259 > 0.0) {
            v108 = v259 + control_c_variable_84;
            v259 = v108;
            if (v108 <= control_c_variable_71)
              v259 = 0.0;
          }
        } else {
          v107 = v259 + 1.0;
          v259 = v107;
          if (v107 >= control_c_variable_85)
            v259 = 0.0;
        }
      }
    } else if (v259 >= 0.0) {
      if (v259 > 0.0) {
        v106 = v259 + control_c_variable_84;
        v259 = v106;
        if (v106 <= control_c_variable_71)
          v259 = 0.0;
      }
    } else {
      v105 = v259 + 1.0;
      v259 = v105;
      if (v105 >= control_c_variable_85)
        v259 = 0.0;
    }
    *(float *)(a1 + 116) = v259;
    v250 = *(_DWORD *)(a1 + 76);
    if (!v250)
      goto LABEL_272;
    if (*(float *)(a1 + 24) < 0.0) {
      v109 = v250;
      v209 = -v250;
      v110 = (control_c_variable_87 - v258 * control_c_variable_86) * (double)-v250 * control_c_variable_88;
    } else {
      if (v258 >= (double)control_c_variable_89) {
      LABEL_272:
        v111 = (double)v256[22];
        v250 += *(_DWORD *)(a1 + 80);
        if (v111 > v258)
          v250 = 0;
        v257 = ((unsigned __int16)*(_DWORD *)(a1 + 68) + (_WORD)v250 + (_WORD)v257) & 0x3FFF;
        *(_WORD *)(a1 + 20) = v257;
        v112 = v249;
        if ((int)abs32(v249) > 50) {
          if (v249 <= 0)
            v249 += 50;
          else
            v249 -= 50;
        } else {
          HIDWORD(v112) = 0;
          v249 = 0;
        }
        v113 = v257;
        *(_DWORD *)(a1 + 68) = v249;
        if (v113 < 4096 || v113 >= 12288)
          v226 = CarBaseY;
        else
          *(float *)&v226 = -*(float *)&CarBaseY;
        if (v257 >= 0x2000)
          v223 = CarBaseX;
        else
          *(float *)&v223 = -*(float *)&CarBaseX;
        v260 = *(float *)&v226 * tcos[v257] - *(float *)&v223 * tsin[v257];
        if ((((_WORD)v257 + 4096) & 0x3FFFu) < 0x1000 || (((_WORD)v257 + 4096) & 0x3FFFu) >= 0x3000) {
          HIDWORD(v112) = CarBaseY;
          v227 = CarBaseY;
        } else {
          *(float *)&v227 = -*(float *)&CarBaseY;
        }
        if ((((_WORD)v257 + 4096) & 0x3FFFu) >= 0x2000) {
          HIDWORD(v112) = CarBaseX;
          v228 = CarBaseX;
        } else {
          *(float *)&v228 = -*(float *)&CarBaseX;
        }
        *(float *)(a1 + 88) = *(float *)&v227 * tcos[((_WORD)v257 + 4096) & 0x3FFF]
          - *(float *)&v228 * tsin[((_WORD)v257 + 4096) & 0x3FFF];
        v115 = v258;
        *(float *)(a1 + 84) = v260;
        WORD1(v112) = HIWORD(v258);
        v221 = v258;
        v116 = v115 < control_c_variable_73;
        v117 = 0;
        v118 = v115 == control_c_variable_73;
        LOWORD(v112) = v114;
        if (v115 > control_c_variable_73)
          v221 = 100.0;
        v119 = v221 * v212 * control_c_variable_91;
        _CHP(v112, HIDWORD(v112));
        *(_DWORD *)(a1 + 80) = (int)v119;
        if (*(int *)(a1 + 80) > 16)
          *(_DWORD *)(a1 + 80) = 16;
        if (*(int *)(a1 + 80) < -16)
          *(_DWORD *)(a1 + 80) = -16;
        if (race_started[0] && !*(_BYTE *)(a1 + 184)) {
          if ((v233 > 0.0 || v258 > (double)control_c_variable_69) && *(float *)(a1 + 28) > 0.0)
            *(float *)(a1 + 116) = v233 * control_c_variable_92 + *(float *)(a1 + 116);
        } else {
          *(_DWORD *)(a1 + 116) = 0;
        }
        v243 = *(float *)(a1 + 24);
        if (v243 < 1.0 && *(char *)(a1 + 128) >= 0 && *(float *)(a1 + 124) > 0.0)
          v243 = 1.0;
        v120 = v243;
        v121 = v229;
        *(float *)a1 = v243 * tcos[v229] + *(float *)a1;
        *(float *)(a1 + 4) = v120 * tsin[v121] + *(float *)(a1 + 4);
        if (v120 < control_c_variable_63)
          *(float *)(a1 + 8) = v243 * tsin[*(__int16 *)(a1 + 18)] + *(float *)(a1 + 8);
        v122 = (float *)((char *)&localdata + 128 * *(__int16 *)(a1 + 12));
        *(float *)(a1 + 8) = v122[21] + *(float *)(a1 + 8);
        if (fabs(*(float *)a1) > v122[12])
          scansection(a1);
        v123 = *(float *)(a1 + 4);
        v124 = *(__int16 *)(a1 + 12);
        v253 = v124;
        if (v123 <= v261) {
          if (-v261 <= *(float *)(a1 + 4))
            v125 = *((_DWORD *)&TrakColour_variable_3 + 6 * v124);
          else
            v125 = *((_DWORD *)&TrakColour_variable_7 + 6 * v124);
        } else {
          v125 = *((_DWORD *)&TrakColour + 6 * v124);
        }
        v126 = abs32(v125) & 0x80000;
        if (*(float *)(a1 + 24) < 0.0)
          v126 = 0;
        if ((v125 & 0x8000) != 0 && *(float *)(a1 + 24) > (double)control_c_variable_93)
          v126 = 0;
        v127 = 0;
        if ((TrakColour_variable_5[12 * *(__int16 *)(a1 + 12)] & 0x40) != 0 && v261 >= fabs(*(float *)(a1 + 4)) - v260) {
          if (*(float *)(a1 + 4) < 0.0) {
            *(float *)(a1 + 4) = -v261 - v260;
            hitleft(a1, 12, 1, v126);
          } else {
            *(float *)(a1 + 4) = v261 + v260;
            hitright(a1, 12, 0, v126);
          }
          v127 = -1;
        }
        if ((TrakColour_variable_1[12 * *(__int16 *)(a1 + 12)] & 0x40) != 0 && *(float *)(a1 + 4) + v260 >= v261) {
          *(float *)(a1 + 4) = v261 - v260;
          hitleft(a1, 12, 0, v126);
          v127 = -1;
        }
        if ((TrakColour_variable_8[12 * *(__int16 *)(a1 + 12)] & 0x40) != 0 && -v261 >= *(float *)(a1 + 4) - v260) {
          *(float *)(a1 + 4) = v260 - v261;
          hitright(a1, 12, 1, v126);
          v127 = -1;
        }
        if (!v127) {
          v251 = *(float *)(a1 + 8);
          if (*(_DWORD *)(a1 + 204)) {
            LOBYTE(v127) = *(_BYTE *)(a1 + 102);
            v251 = v251 - *(float *)&CarBox_variable_14[24 * v127];
          }
          if (*(float *)(a1 + 4) > 0.0) {
            switch (v102[6]) {
              case 0:
              case 2:
                if (v261 + v235 >= *(float *)(a1 + 4) - v260 * control_c_variable_82) {
                  if (!v126)
                    goto LABEL_344;
                  *(float *)&v209 = v251 - v248;
                  if (getgroundz(*(__int16 *)(a1 + 12), *(float *)a1, *(float *)(a1 + 4), *(__int16 *)(a1 + 12)) >= *(float *)&v209)
                    goto LABEL_344;
                }
                goto LABEL_403;
              case 1:
              case 3:
              case 4:
              case 7:
              case 8:
                v128 = *(float *)(a1 + 4) + v260;
                v217 = v261 + v235;
                if (v128 > v217) {
                  *(float *)(a1 + 4) = v217 - v260;
                  hitleft(a1, 12, 0, v126);
                  goto LABEL_404;
                }
                if (v126) {
                  *(float *)&v263 = v251 - v248;
                  if (getgroundz(*(__int16 *)(a1 + 12), *(float *)a1, *(float *)(a1 + 4), *(__int16 *)(a1 + 12)) < *(float *)&v263)
                    goto LABEL_403;
                }
                goto LABEL_344;
              case 5:
                v129 = *(float *)(a1 + 4) + v260;
                v220 = v261 + v235;
                if (v129 > v220) {
                  *(float *)(a1 + 4) = v220 - v260;
                  hitleft(a1, 12, 0, v126);
                }
                if (*(float *)(a1 + 4) + v260 > v261 && *(_DWORD *)(a1 + 212)) {
                  *(float *)(a1 + 4) = v261 - v260;
                  hitleft(a1, 12, 0, v126);
                }
                if (*(float *)(a1 + 4) - v260 < v261 && !*(_DWORD *)(a1 + 212)) {
                  *(float *)(a1 + 4) = v261 + v260;
                  hitright(a1, 12, 0, v126);
                }
                if (v126) {
                  *(float *)&v263 = v251 - v248;
                  if (getgroundz(*(__int16 *)(a1 + 12), *(float *)a1, *(float *)(a1 + 4), *(__int16 *)(a1 + 12)) < *(float *)&v263)
                    goto LABEL_403;
                }
                goto LABEL_344;
              case 6:
              case 9:
                if (v261 + v235 < *(float *)(a1 + 4) - v260 * control_c_variable_82)
                  goto LABEL_403;
                if (v260 > fabs(*(float *)(a1 + 4) - v261) && *(float *)(a1 + 4) + v260 > v261 && *(_DWORD *)(a1 + 212)) {
                  *(float *)(a1 + 4) = v261 - v260;
                  hitleft(a1, 12, 0, v126);
                }
                if (*(float *)(a1 + 4) - v260 < v261 && !*(_DWORD *)(a1 + 212)) {
                  *(float *)(a1 + 4) = v261 + v260;
                  hitright(a1, 12, 0, v126);
                }
                if (v126) {
                  *(float *)&v209 = v251 - v248;
                  if (getgroundz(*(__int16 *)(a1 + 12), *(float *)a1, *(float *)(a1 + 4), *(__int16 *)(a1 + 12)) < *(float *)&v209)
                    goto LABEL_403;
                }
                goto LABEL_344;
              default:
                goto LABEL_404;
            }
          }
          switch (v102[7]) {
            case 0:
            case 2:
              if (v261 + v244 >= -*(float *)(a1 + 4) - v260 * control_c_variable_82) {
                if (!v126)
                  goto LABEL_344;
                *(float *)&v209 = v251 - v248;
                if (getgroundz(*(__int16 *)(a1 + 12), *(float *)a1, *(float *)(a1 + 4), *(__int16 *)(a1 + 12)) >= *(float *)&v209)
                  goto LABEL_344;
              }
              goto LABEL_403;
            case 1:
            case 3:
            case 4:
            case 7:
            case 8:
              if (v261 + v244 >= v260 - *(float *)(a1 + 4)) {
                if (v126
                  && (*(float *)&v263 = v251 - v248,
                      getgroundz(*(__int16 *)(a1 + 12), *(float *)a1, *(float *)(a1 + 4), *(__int16 *)(a1 + 12)) < *(float *)&v263)) {
                LABEL_403:
                  converttoair(a1);
                } else {
                LABEL_344:
                  putflat(a1);
                }
              } else {
                *(float *)(a1 + 4) = -v261 - v244 + v260;
                hitright(a1, 12, 1, v126);
              }
              break;
            case 5:
              if (v261 + v244 < v260 - *(float *)(a1 + 4)) {
                *(float *)(a1 + 4) = -v261 - v244 + v260;
                hitright(a1, 12, 1, v126);
              }
              if (v260 - *(float *)(a1 + 4) > v261 && *(_DWORD *)(a1 + 212) != 2) {
                *(float *)(a1 + 4) = v260 - v261;
                hitright(a1, 12, 1, v126);
              }
              if (-*(float *)(a1 + 4) - v260 < v261 && *(_DWORD *)(a1 + 212) == 2) {
                *(float *)(a1 + 4) = -v261 - v260;
                hitleft(a1, 12, 1, v126);
              }
              if (v126) {
                *(float *)&v263 = v251 - v248;
                if (getgroundz(*(__int16 *)(a1 + 12), *(float *)a1, *(float *)(a1 + 4), *(__int16 *)(a1 + 12)) < *(float *)&v263)
                  goto LABEL_403;
              }
              goto LABEL_344;
            case 6:
            case 9:
              v219 = -*(float *)(a1 + 4);
              if (v261 + v244 < v219 - v260 * control_c_variable_82)
                goto LABEL_403;
              if (v260 > fabs(v219 - v261) && v260 - *(float *)(a1 + 4) > v261 && *(_DWORD *)(a1 + 212) != 2) {
                *(float *)(a1 + 4) = v260 - v261;
                hitright(a1, 12, 1, v126);
              }
              if (-*(float *)(a1 + 4) - v260 < v261 && *(_DWORD *)(a1 + 212) == 2) {
                *(float *)(a1 + 4) = -v261 - v260;
                hitleft(a1, 12, 1, v126);
              }
              if (v126) {
                *(float *)&v263 = v251 - v248;
                if (getgroundz(*(__int16 *)(a1 + 12), *(float *)a1, *(float *)(a1 + 4), *(__int16 *)(a1 + 12)) < *(float *)&v263)
                  goto LABEL_403;
              }
              goto LABEL_344;
            default:
              break;
          }
        }
      LABEL_404:
        if (*(_DWORD *)(a1 + 72) == 3
          && *((float *)&localdata + 32 * *(__int16 *)(a1 + 12) + 12) * control_c_variable_69 > *(float *)&CarBaseX) {
          if (*(float *)(a1 + 4) <= (double)v261) {
            if (-v261 <= *(float *)(a1 + 4))
              v130 = 1;
            else
              v130 = 2;
          } else {
            v130 = 0;
          }
          v131 = *((int *)&TrakColour + 6 * *(__int16 *)(a1 + 12) + v130);
          if ((((HIDWORD(v131) ^ (unsigned int)v131) - HIDWORD(v131)) & 0x20000) != 0)
            converttoair(a1);
          else
            analysefalloff(a1);
        }
        if (*(_DWORD *)(a1 + 72) == 3) {
          v132 = *(__int16 *)(a1 + 20) - *(_DWORD *)(a1 + 64);
          v254 = v132 + (v132 < 0 ? 0x4000 : 0);
          if (v254 > 0x2000)
            v254 -= 0x4000;
          v133 = fabs(*(float *)(a1 + 24));
          v238 = v133;
          if (v133 <= v241) {
            v255 = v245 * control_c_variable_63;
            v134 = (v242 - v255) / v241 * v238 + v255;
          } else {
            v134 = (v238 - v234) / (v241 - v234) * v242 + (v238 - v241) / (v234 - v241) * v240;
          }
          v255 = v134;
          v140 = v254;
          LODWORD(v140) = abs32(v254);
          v255 = (tsin[(_DWORD)v140] * control_c_variable_94 + 1.0) * v255;
          v136 = (double)v254;
          v137 = v136 < v255;
          v138 = 0;
          v139 = v136 == v255;
          LOWORD(v140) = v135;
          if (v136 > v255) {
            _CHP(v140, HIDWORD(v140));
            v254 = (int)v255;
          }
          v141 = (double)v254;
          v215 = -v255;
          v143 = v141 < v215;
          v144 = 0;
          v145 = v141 == v215;
          LOWORD(v140) = v142;
          if (v141 < v215) {
            _CHP(v140, HIDWORD(v140));
            v254 = (int)v215;
          }
          if (!*(_DWORD *)(a1 + 204)) {
            HIDWORD(v140) = v254;
            *(_DWORD *)(a1 + 64) = ((_WORD)v254 + (unsigned __int16)*(_DWORD *)(a1 + 64)) & 0x3FFF;
          }
          v146 = *(_DWORD *)(a1 + 32);
          if (human_control[v146]) {
            if (!v249) {
              if (!*(_DWORD *)(a1 + 76)
                || (v147 = SLOWORD(copy_multiple[16 * (((_WORD)readptr - 1) & 0x1FF) + v146]),
                    v148 = (v147 - (__CFSHL__(v147 >> 31, 8) + (v147 >> 31 << 8))) >> 8,
                    v149 = (HIDWORD(v148) ^ v148) - HIDWORD(v148),
                    v140 = *(int *)(a1 + 76),
                    (int)(v149 - abs32(*(_DWORD *)(a1 + 76))) < 0)) {
                v150 = *(__int16 *)(a1 + 20);
                v151 = *(_DWORD *)(a1 + 64);
                if (v150 != v151) {
                  LODWORD(v140) = v150 - v151;
                  v252 = v140 + ((int)v140 < 0 ? 0x4000 : 0);
                  if (v252 > 0x2000)
                    v252 -= 0x4000;
                  v153 = (double)v252;
                  v154 = v153 < v255;
                  v155 = 0;
                  v156 = v153 == v255;
                  LOWORD(v140) = v152;
                  if (v153 > v255) {
                    _CHP(v140, HIDWORD(v140));
                    v252 = (int)v255;
                  }
                  v157 = (double)v252;
                  v216 = -v255;
                  v159 = v157 < v216;
                  v160 = 0;
                  v161 = v157 == v216;
                  LOWORD(v140) = v158;
                  if (v157 < v216) {
                    _CHP(v140, HIDWORD(v140));
                    v252 = (int)v216;
                  }
                  v162 = *(_WORD *)(a1 + 20) - v252;
                  HIBYTE(v162) &= 0x3Fu;
                  *(_WORD *)(a1 + 20) = v162;
                }
              }
            }
          }
        }
        if (*(_DWORD *)(a1 + 204) && *(_DWORD *)(a1 + 72) == 3 || (*(_BYTE *)(a1 + 131) & 4) != 0) {
          *(float *)(a1 + 24) = *(float *)(a1 + 24) + control_c_variable_95;
          if (*(float *)(a1 + 24) < 0.0)
            *(_DWORD *)(a1 + 24) = 0;
          if (*(__int16 *)(a1 + 236) == -1 && (*(_DWORD *)(a1 + 24) & 0x7FFFFFFF) == 0)
            *(_WORD *)(a1 + 236) = 72;
          SetEngine(a1, *(float *)(a1 + 24));
          if (((*(_DWORD *)(a1 + 24) & 0x7FFFFFFF) == 0
               || (*(_DWORD *)(a1 + 28) & 0x7FFFFFFF) == 0 && *(__int16 *)(a1 + 100) < -54)
            && !*(_DWORD *)(a1 + 148)
            && !*(_DWORD *)(a1 + 156)
            && !*(_WORD *)(a1 + 236)) {
            checkplacement(a1);
          }
        }
        v163 = *(_WORD *)(a1 + 236);
        if (v163 > 0)
          *(_WORD *)(a1 + 236) = v163 - 1;
        goto LABEL_502;
      }
      v101 = (float *)v250;
      v109 = 6 * v250;
      v209 = 6 * v250;
      v110 = (double)(6 * v250) * (control_c_variable_89 - v258) * control_c_variable_90 + (double)v250;
    }
    _CHP(v109, v101);
    v250 = (int)v110;
    goto LABEL_272;
  }
  if (*(__int16 *)(a1 + 236) == -1 && (LODWORD(v258) & 0x7FFFFFFF) == 0)
    *(_WORD *)(a1 + 236) = 144;
  v172 = *(_WORD *)(a1 + 236);
  if (v172 > 0)
    *(_WORD *)(a1 + 236) = v172 - 1;
  v173 = v229;
  *(float *)a1 = *(float *)(a1 + 24) * tcos[v229] + *(float *)a1;
  *(float *)(a1 + 4) = *(float *)(a1 + 24) * tsin[v173] + *(float *)(a1 + 4);
  calculateseparatedcoordinatesystem(*(_DWORD *)(a1 + 216), &v193);
  v174 = *(float *)(a1 + 4) + v203;
  v175 = *(float *)a1 + v202;
  v176 = *(float *)(a1 + 8) + v204;
  v231 = v196 * v174 + v193 * v175 + v199 * v176;
  v247 = v197 * v174 + v194 * v175 + v200 * v176;
  v177 = *(_DWORD *)(a1 + 216) + 2;
  v178 = *(_DWORD *)(a1 + 216) + 3;
  v232 = v174 * v198 + v175 * v195 + v176 * v201;
  if (v178 >= TRAK_LEN)
    v178 -= TRAK_LEN;
  if (v177 >= TRAK_LEN)
    v177 -= TRAK_LEN;
  v179 = (GroundPt_variable_4[18 * v177]
        + GroundPt_variable_5[18 * v177]
        + GroundPt_variable_4[18 * v178]
        + GroundPt_variable_5[18 * v178])
    * control_c_variable_76;
  _CHP(9 * v178, &v193);
  if (v179 > GroundLevel[v177] + control_c_variable_77)
    *(_DWORD *)(a1 + 24) = 0;
  v180 = *(_DWORD *)(a1 + 216) - 1;
  v181 = *(_DWORD *)(a1 + 216) - 2;
  if (v180 < 0)
    v180 += TRAK_LEN;
  if (v181 < 0)
    v181 += TRAK_LEN;
  v182 = (GroundPt_variable_4[18 * v181]
        + GroundPt_variable_5[18 * v181]
        + GroundPt_variable_4[18 * v180]
        + GroundPt_variable_5[18 * v180])
    * control_c_variable_76;
  _CHP(9 * v180, &v193);
  if (v182 > GroundLevel[v181] + control_c_variable_77)
    *(_DWORD *)(a1 + 24) = 0;
  if (v247 <= 0.0) {
    v230 = (GroundPt[18 * *(_DWORD *)(a1 + 216) + 10] + v203) * v197
      + (GroundPt[18 * *(_DWORD *)(a1 + 216) + 9] + v202) * v194
      + (GroundPt[18 * *(_DWORD *)(a1 + 216) + 11] + v204) * v200;
    if (v247 - *(float *)&CarBaseX >= v230)
      goto LABEL_493;
    v183 = v230 + *(float *)&CarBaseX;
  } else {
    v225 = (GroundPt[18 * *(_DWORD *)(a1 + 216) + 7] + v203) * v197
      + (GroundPt[18 * *(_DWORD *)(a1 + 216) + 6] + v202) * v194
      + (GroundPt[18 * *(_DWORD *)(a1 + 216) + 8] + v204) * v200;
    if (v247 + *(float *)&CarBaseX <= v225)
      goto LABEL_493;
    v183 = v225 - *(float *)&CarBaseX;
  }
  *(_DWORD *)(a1 + 24) = 0;
  v247 = v183;
LABEL_493:
  v184 = v247;
  v185 = v231;
  v186 = v232;
  *(float *)a1 = v194 * v247 + v193 * v231 + v195 * v232 - v202;
  *(float *)(a1 + 4) = v196 * v185 + v197 * v184 + v198 * v186 - v203;
  *(float *)(a1 + 8) = v184 * v200 + v185 * v199 + v186 * v201 - v204;
  findnearsection(a1, v206);
  *(float *)(a1 + 24) = *(float *)(a1 + 24) + control_c_variable_70;
  if (*(float *)(a1 + 24) < 0.0)
    *(_DWORD *)(a1 + 24) = 0;
  v187 = v258;
  SetEngine(a1, *(float *)(a1 + 24));
  if (((LODWORD(v187) & 0x7FFFFFFF) == 0 || (*(_DWORD *)(a1 + 28) & 0x7FFFFFFF) == 0 && *(__int16 *)(a1 + 100) < -54)
    && !*(_DWORD *)(a1 + 148)
    && !*(_DWORD *)(a1 + 156)
    && !*(_WORD *)(a1 + 236)) {
  LABEL_501:
    checkplacement(a1);
  }
LABEL_502:
  if (!*(_DWORD *)(a1 + 72)
    && *(float *)(a1 + 8) < (double)GroundLevel[*(_DWORD *)(a1 + 216)]
    && *(char *)(a1 + 103) > 0) {
    if (death_race)
      v188 = fabs(*(float *)(a1 + 48)) * control_c_variable_96 * control_c_variable_97;
    else
      v188 = fabs(*(float *)(a1 + 48)) * control_c_variable_96;
    v192 = v188;
    dodamage(v192);
    v189 = *(_DWORD *)(a1 + 216);
    *(_DWORD *)(a1 + 72) = 2;
    *(float *)(a1 + 8) = GroundLevel[v189];
    sfxpend(2, *(_DWORD *)(a1 + 32), 0x8000);
    v190 = *(__int16 *)(a1 + 18);
    v191 = *(__int16 *)(a1 + 16);
    *(_DWORD *)(a1 + 64) = *(__int16 *)(a1 + 20);
    if (v191 < 4096 || v191 > 12288) {
      *(_WORD *)(a1 + 16) = 0;
      *(_DWORD *)(a1 + 204) = 0;
    } else {
      *(_DWORD *)(a1 + 204) = -1;
      *(_DWORD *)(a1 + 76) = 0;
      *(_WORD *)(a1 + 16) = 0x2000;
      v191 = v191 - 0x2000 + (v191 - 0x2000 < 0 ? 0x4000 : 0);
      *(float *)(a1 + 8) = *(float *)&CarBox_variable_14[24 * *(unsigned __int8 *)(a1 + 102)] + *(float *)(a1 + 8);
    }
    if (v190 > 0x2000)
      v190 -= 0x4000;
    *(_DWORD *)(a1 + 144) = 0;
    *(_DWORD *)(a1 + 140) = v190;
    *(_DWORD *)(a1 + 148) = v190;
    if (v191 > 0x2000)
      v191 -= 0x4000;
    *(_WORD *)(a1 + 18) = 0;
    *(_DWORD *)(a1 + 152) = v191;
    *(_DWORD *)(a1 + 156) = v191;
  }
  if (!finished_car[*(_DWORD *)(a1 + 32)] && *(float *)(a1 + 220) < (double)control_c_variable_98) {
    if (race_started[0]) {
      *(float *)(a1 + 220) = *(float *)(a1 + 220) + control_c_variable_99;
      *(float *)(a1 + 232) = *(float *)(a1 + 232) + control_c_variable_99;
      if (*(float *)(a1 + 220) > (double)control_c_variable_94 || *(char *)(a1 + 129) <= 1)
        *(_DWORD *)(a1 + 228) = *(_DWORD *)(a1 + 220);
    }
  }*/
}

//-------------------------------------------------------------------------------------------------
//0002F040
int16 check_crossed_line(tCar *a1)
{
  (void)(a1);
  return 0;
  /*
  int v1; // ebp
  __int16 v2; // dx
  int v3; // edx
  int v4; // edx
  int v5; // edx
  int v6; // esi
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // ebx
  int *v11; // eax
  char v12; // dl
  double v13; // st7
  int v14; // ecx
  int v15; // edx
  int v16; // esi
  int v17; // ebx
  int v18; // edx
  char *v19; // esi
  char *v20; // edi
  char v21; // al
  char v22; // al
  int v23; // esi
  int v24; // edx
  int v25; // eax
  int v26; // edx
  int v27; // ebx
  unsigned __int8 v28; // bl
  int v29; // eax
  int v30; // ecx
  double v31; // st7
  int v32; // eax
  int v33; // eax
  int v34; // ebx
  int v35; // esi
  unsigned __int8 v36; // al
  int v37; // eax
  int v38; // eax
  int v39; // edx
  int v40; // ecx
  unsigned __int8 v41; // bh
  int v42; // eax
  int v44; // [esp+0h] [ebp-20h]
  int v45; // [esp+4h] [ebp-1Ch]

  v1 = a1;
  if (champ_mode) {
    a1 = 4 * *(_DWORD *)(a1 + 32);
    if (*(int *)((char *)champ_go + a1)) {
      v2 = *(_WORD *)(v1 + 12);
      if (v2 > 16 && v2 < 64) {
        v3 = racers;
        *(int *)((char *)champ_go + a1) = 0;
        a1 = *(unsigned __int8 *)(v1 + 130);
        if (a1 < v3 - 1) {
          champ_zoom = 0;
          LOWORD(a1) = carorder_variable_1[a1];
          ViewType[0] = a1;
          --champ_car;
        }
      }
    }
  }
  v4 = *(__int16 *)(v1 + 12);
  if (v4 != -1) {
    a1 = *(__int16 *)(v1 + 14);
    if (a1 != -1) {
      if (a1 - v4 > TRAK_LEN / 2 && !finished_car[*(_DWORD *)(v1 + 32)]) {
        if (*(_BYTE *)(v1 + 129) == *(_BYTE *)(v1 + 104)) {
          v5 = *(char *)(v1 + 129);
          if (v5 <= NoOfLaps) {
            if (game_type == 2)
              trial_times[6 * *(_DWORD *)(v1 + 32) + v5] = *(float *)(v1 + 220);
            v6 = champ_mode;
            ++*(_BYTE *)(v1 + 129);
            if (v6) {
              if (champ_car) {
                v8 = *(_DWORD *)(v1 + 32);
                if (ViewType[0] == v8) {
                  v9 = v8 ^ ViewType[0];
                  LOBYTE(v9) = *(_BYTE *)(v1 + 130);
                  if (v9 < racers - 1) {
                    v10 = carorder_variable_1[v9];
                    champ_go[v10] = -1;
                    v10 *= 308;
                    v11 = &CarEngines[28 * (unsigned __int8)Car_variable_22[v10]];
                    *(float *)((char *)Car_variable_28 + v10) = 1.0;
                    v12 = *(_BYTE *)v11 - 1;
                    Car_variable_30[v10] = v12;
                    *(float *)((char *)Car_variable_8 + v10) = *(float *)(v11[2] + 4 * v12);
                    *(int *)((char *)Car_variable_26 + v10) = *(_DWORD *)((char *)Car_variable_8 + v10);
                    v13 = calc_pow(
                            (unsigned __int8)Car_variable_22[v10],
                            Car_variable_30[v10],
                            *(float *)((char *)Car_variable_28 + v10));
                    *(int *)((char *)Car_variable_27 + v10) = 0;
                    Car_variable_61[v10] = 36;
                    Car_variable_58[v10] = -1;
                    *(float *)((char *)Car_variable_29 + v10) = v13;
                  }
                }
              } else {
                v7 = *(_DWORD *)(v1 + 32);
                champ_mode = 2;
                champ_go[v7] = 0;
              }
            }
            v14 = -1;
            v15 = NoOfLaps;
            v44 = -1;
            v45 = -1;
            if (*(char *)(v1 + 129) > NoOfLaps && NoOfLaps) {
              finished_car[*(_DWORD *)(v1 + 32)] = -1;
              v15 = human_control[*(_DWORD *)(v1 + 32)];
              ++finishers;
              if (v15)
                ++human_finishers;
              v16 = *(_DWORD *)(v1 + 32);
              if ((__int16)player1_car == v16 || player2_car == v16) {
                if (*(char *)(v1 + 103) > 0) {
                  LOBYTE(v15) = *(_BYTE *)(v1 + 130);
                  if ((_BYTE)v15) {
                    if ((unsigned __int8)v15 >= 3u) {
                      if ((unsigned __int8)v15 >= 0xDu)
                        v45 = 24;
                      else
                        v45 = 25;
                    } else {
                      v45 = 23;
                    }
                  } else {
                    v45 = 22;
                  }
                  v44 = 30;
                }
              } else if (player_type != 2) {
                if (*(_BYTE *)(v1 + 130))
                  small_zoom((_BYTE *)&language_buffer + 64 * *(unsigned __int8 *)(v1 + 130) + 384);
                else
                  start_zoom(language_buffer_variable_40, 0);
                v15 = *(_DWORD *)(v1 + 32);
                subzoom(&driver_names[9 * v15]);
              }
            }
            if (*(float *)(v1 + 220) < (double)*(float *)(v1 + 224) && *(char *)(v1 + 129) > 1) {
              *(_DWORD *)(v1 + 224) = *(_DWORD *)(v1 + 220);
              if (*(float *)(v1 + 224) >= (double)RecordLaps[game_track]) {
                v23 = -1;
                if (racers > 0) {
                  v24 = 0;
                  do {
                    v25 = carorder[v24];
                    if (v25 != *(_DWORD *)(v1 + 32)
                      && *(float *)&Car_variable_53[77 * v25] <= (double)*(float *)(v1 + 224)) {
                      v23 = 0;
                    }
                    ++v24;
                  } while (v24 < racers);
                }
                v26 = *(_DWORD *)(v1 + 32);
                if ((__int16)player1_car == v26 || player2_car == v26) {
                  if (*(char *)(v1 + 129) > 2) {
                    if (v23)
                      v14 = 40;
                    else
                      v14 = 39;
                  }
                } else if (v23 && *(char *)(v1 + 129) > 2) {
                  sprintf(&buffer, "%s %s", language_buffer_variable_45, &driver_names[9 * v26]);
                  small_zoom(&buffer);
                  make_time(&buffer, v26, *(float *)(v1 + 224));
                  subzoom(&buffer);
                }
              } else {
                v17 = *(_DWORD *)(v1 + 32);
                if ((__int16)player1_car == v17 || player2_car == v17) {
                  if (*(float *)(v1 + 224) >= RecordLaps[game_track] + control_c_variable_101)
                    v14 = 37;
                  else
                    v14 = 38;
                } else if (*(char *)(v1 + 129) > 2) {
                  sprintf(&buffer, "%s %s", language_buffer_variable_43, &driver_names[9 * v17]);
                  small_zoom(&buffer);
                  make_time(&buffer, v15, *(float *)(v1 + 224));
                  subzoom(&buffer);
                }
                if (((unsigned int)cstart_branch_1 & textures_off) != 0)
                  v18 = *(unsigned __int8 *)(v1 + 102) + 16;
                else
                  v18 = *(unsigned __int8 *)(v1 + 102);
                RecordCars[game_track] = v18;
                RecordLaps[game_track] = *(float *)(v1 + 224);
                v19 = &driver_names[9 * *(_DWORD *)(v1 + 32)];
                v20 = &RecordNames[9 * game_track];
                do {
                  v21 = *v19;
                  *v20 = *v19;
                  if (!v21)
                    break;
                  v22 = v19[1];
                  v19 += 2;
                  v20[1] = v22;
                  v20 += 2;
                } while (v22);
              }
            }
            if (v14 != -1)
              speechsample(v14, 0x8000, 18, *(_DWORD *)(v1 + 32));
            if (v45 != -1)
              speechsample(v45, 0x8000, 18, *(_DWORD *)(v1 + 32));
            if (v44 != -1)
              speechsample(v44, 0x8000, 18, *(_DWORD *)(v1 + 32));
            if (*(_BYTE *)(v1 + 129) != 1) {
              v27 = *(_DWORD *)(v1 + 32);
              if (((__int16)player1_car == v27 || player2_car == v27)
                && finishers - Destroyed <= 0
                && !finished_car[*(_DWORD *)(v1 + 32)]
                && competitors > 1) {
                switch (NoOfLaps - *(char *)(v1 + 129)) {
                  case 0:
                    v28 = *(_BYTE *)(v1 + 130);
                    if (v28) {
                      if (v28 >= 5u) {
                        if (!SamplePtr_variable_1)
                          goto LABEL_102;
                        v29 = 16;
                      } else {
                        if (!SamplePtr_variable_2)
                          goto LABEL_102;
                        v29 = 17;
                      }
                      break;
                    }
                    if (!SamplePtr_variable_3)
                      goto LABEL_102;
                    v29 = 18;
                    v30 = *(_DWORD *)(v1 + 32);
                    goto LABEL_104;
                  case 1:
                    if (!SamplePtr_variable_4)
                      goto LABEL_102;
                    v29 = 53;
                    break;
                  case 2:
                    if (!SamplePtr_variable_5)
                      goto LABEL_102;
                    v29 = 54;
                    break;
                  case 3:
                    if (!SamplePtr_variable_6)
                      goto LABEL_102;
                    v29 = 55;
                    break;
                  case 4:
                    if (!SamplePtr_variable_7)
                      goto LABEL_102;
                    v29 = 56;
                    break;
                  default:
                  LABEL_102:
                    v29 = 15;
                    break;
                }
                v30 = *(_DWORD *)(v1 + 32);
              LABEL_104:
                speechsample(v29, 0x8000, 18, v30);
              }
            }
            v31 = *(float *)(v1 + 220);
            *(_DWORD *)(v1 + 220) = 0;
            *(float *)(v1 + 228) = v31;
          }
        }
        v32 = finishers - Destroyed;
        ++*(_BYTE *)(v1 + 104);
        if (v32 > 0) {
          v33 = *(_DWORD *)(v1 + 32);
          if (!finished_car[v33] && competitors > 1) {
            finished_car[v33] = -1;
            v34 = human_control[*(_DWORD *)(v1 + 32)];
            ++finishers;
            if (v34)
              ++human_finishers;
            v35 = *(_DWORD *)(v1 + 32);
            if (((__int16)player1_car == v35 || player2_car == v35) && *(char *)(v1 + 103) > 0) {
              v36 = *(_BYTE *)(v1 + 130);
              if (v36) {
                if (v36 >= 3u) {
                  if (v36 >= 0xDu)
                    v37 = 24;
                  else
                    v37 = 25;
                } else {
                  v37 = 23;
                }
              } else {
                v37 = 22;
              }
              speechsample(v37, 0x8000, 18, *(_DWORD *)(v1 + 32));
              speechsample(30, 0x8000, 18, *(_DWORD *)(v1 + 32));
            }
          }
        }
      }
      a1 = -TRAK_LEN / 2;
      if (*(__int16 *)(v1 + 14) - *(__int16 *)(v1 + 12) < a1) {
        v38 = finishers;
        --*(_BYTE *)(v1 + 104);
        a1 = v38 - Destroyed;
        if (a1 > 0) {
          a1 = 4 * *(_DWORD *)(v1 + 32);
          if (!*(int *)((char *)finished_car + a1) && competitors > 1) {
            *(int *)((char *)finished_car + a1) = -1;
            v39 = human_control[*(_DWORD *)(v1 + 32)];
            ++finishers;
            if (v39)
              ++human_finishers;
            LOWORD(a1) = player1_car;
            v40 = *(_DWORD *)(v1 + 32);
            if ((__int16)player1_car == v40 || (LOWORD(a1) = player2_car, player2_car == v40)) {
              if (*(char *)(v1 + 103) > 0) {
                v41 = *(_BYTE *)(v1 + 130);
                if (v41) {
                  if (v41 >= 3u) {
                    if (v41 >= 0xDu)
                      v42 = 24;
                    else
                      v42 = 25;
                  } else {
                    v42 = 23;
                  }
                } else {
                  v42 = 22;
                }
                speechsample(v42, 0x8000, 18, *(_DWORD *)(v1 + 32));
                LOWORD(a1) = speechsample(30, 0x8000, 18, *(_DWORD *)(v1 + 32));
              }
            }
          }
        }
      }
      if (*(char *)(v1 + 104) < 0)
        *(_BYTE *)(v1 + 104) = 0;
    }
  }
  return a1;*/
}

//-------------------------------------------------------------------------------------------------
//0002F920
char checkplacement(int a1)
{
  (void)(a1);
  return 0;
  /*
  int v2; // eax
  int v3; // eax
  int v4; // edi
  int v5; // ebp
  __int16 v6; // ax
  int v7; // eax
  unsigned int v8; // ebx
  unsigned int v9; // edx
  int v10; // ecx
  int v11; // eax
  double v12; // st7
  int v13; // eax
  int v14; // eax
  int v15; // edx
  int v16; // eax
  float *v17; // eax
  double v18; // st7
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // edx
  int i; // eax
  int v25; // edi
  int v26; // eax
  int v27; // edx
  int v28; // eax
  char v29; // ch
  int v30; // eax
  int v31; // edx
  int v32; // eax
  int v33; // eax
  int v34; // edx
  int v35; // eax
  char v36; // dl
  __int16 v38; // [esp+0h] [ebp-34h]
  float v39; // [esp+4h] [ebp-30h]
  int v40; // [esp+8h] [ebp-2Ch]
  int v41; // [esp+10h] [ebp-24h]
  int v42; // [esp+14h] [ebp-20h]
  int v43; // [esp+18h] [ebp-1Ch]

  v2 = rand();
  v3 = (10 * v2 - (__CFSHL__((10 * v2) >> 31, 15) + ((10 * v2) >> 31 << 15))) >> 15;
  v4 = v3 + *(__int16 *)(a1 + 14);
  if (v4 >= TRAK_LEN)
    v4 = TRAK_LEN - 1;
  if (v4 == -1)
    v4 = 0;
  if ((*(_DWORD *)(a1 + 28) & 0x7FFFFFFF) == 0 && !numstops)
    *(_DWORD *)(a1 + 28) = 1120403456;
  if ((*(_DWORD *)(a1 + 28) & 0x7FFFFFFF) != 0) {
    while ((*((_DWORD *)&TrakColour + 6 * v4) & 0xA420000) != 0
         && (*((_DWORD *)&TrakColour_variable_3 + 6 * v4) & 0xA420000) != 0
         && (*((_DWORD *)&TrakColour_variable_7 + 6 * v4) & 0xA420000) != 0) {
      if (++v4 == TRAK_LEN)
        v4 ^= TRAK_LEN;
    }
    v5 = -1;
    v39 = *(float *)a1;
    *(_DWORD *)a1 = 0;
    v40 = *(_DWORD *)(a1 + 4);
    v6 = *(_WORD *)(a1 + 12);
    *(_DWORD *)(a1 + 4) = 0;
    v38 = v6;
    *(_WORD *)(a1 + 12) = v4;
    do {
      v7 = rand();
      v8 = (3 * v7 - (__CFSHL__((3 * v7) >> 31, 15) + ((3 * v7) >> 31 << 15))) >> 15;
    } while ((TrakColour_variable_1[12 * v4 + 2 * v8] & 0xA42) != 0);
    LOBYTE(v3) = numcars;
    v43 = 0;
    if (numcars > 0) {
      v9 = 0;
      do {
        if (v43 != *(_DWORD *)(a1 + 32) && Car_variable_17[v9 / 4] == 3 && v8 == Car_variable_50[v9 / 4]) {
          v10 = v4 - Car_variable_3[v9 / 2];
          v11 = v10;
          if (v10 < 0)
            v11 = TRAK_LEN + v10;
          if (v11 > TRAK_LEN / 2)
            v11 -= TRAK_LEN;
          if (v11 <= 8 && v11 >= -2)
            v5 = 0;
        }
        LOBYTE(v3) = ++v43;
        v9 += 308;
      } while (v43 < numcars);
    }
    if (!v5)
      goto LABEL_39;
    LOBYTE(v3) = 36 * v4;
    if (v8) {
      if (v8 <= 1) {
        *(_DWORD *)(a1 + 4) = 0;
      LABEL_38:
        *(_DWORD *)(a1 + 212) = v8;
      LABEL_39:
        if (!v5) {
          *(float *)a1 = v39;
          *(_DWORD *)(a1 + 4) = v40;
          LOBYTE(v3) = v38;
          *(_WORD *)(a1 + 12) = v38;
        }
        goto LABEL_113;
      }
      if (v8 != 2)
        goto LABEL_38;
      v12 = -*(float *)&localdata_variable_5[32 * v4] - *(float *)&TrackInfo_variable_2[9 * v4] * control_c_variable_103;
    } else {
      v12 = *(float *)&TrackInfo[9 * v4] * control_c_variable_103 + *(float *)&localdata_variable_5[32 * v4];
    }
    *(float *)(a1 + 4) = v12;
    goto LABEL_38;
  }
  v5 = 0;
  if ((network_on || *(char *)(a1 + 103) > 0 || lastsample >= -144 || (v3 = *(__int16 *)(a1 + 100), v3 >= -64))
    && (!network_on || *(char *)(a1 + 103) > 0 || *(__int16 *)(a1 + 100) >= 0)) {
    if (*(__int16 *)(a1 + 100) < 0 && *(char *)(a1 + 103) > 0) {
      v22 = rand();
      v5 = -1;
      v3 = stops[(v22 * numstops - (__CFSHL__((v22 * numstops) >> 31, 15) + ((v22 * numstops) >> 31 << 15))) >> 15];
      v23 = 0;
      v42 = v3;
      if (numcars > 0) {
        v3 = 0;
        do {
          if (v23 != *(_DWORD *)(a1 + 32) && Car_variable_23[v3] > 0 && *(int *)((char *)Car_variable_17 + v3) == 3) {
            v41 = *(__int16 *)((char *)Car_variable_3 + v3);
            if ((TrakColour_variable_1[12 * v41 + 2 * *(int *)((char *)Car_variable_50 + v3)] & 0x200) != 0) {
              if (v41 == v42)
                v5 = 0;
              if (*(__int16 *)((char *)Car_variable_3 + v3) - 1 == v42)
                v5 = 0;
              if (*(__int16 *)((char *)Car_variable_3 + v3) + 1 == v42)
                v5 = 0;
            }
          }
          ++v23;
          v3 += 308;
        } while (v23 < numcars);
      }
      if (v5) {
        for (i = 0; i != 352; car_texs_loaded_variable_2[352 * *(_DWORD *)(a1 + 32) + i] = 0)
          i += 11;
        if (player_type == 2) {
          v25 = *(_DWORD *)(a1 + 32);
          if ((__int16)player1_car == v25) {
            v26 = v25 ^ (__int16)player1_car;
            do {
              v26 += 352;
              *(int *)((char *)&CarSpray_variable_5 + v26) = 0;
              *(int *)((char *)&CarSpray_variable_6 + v26) = 0;
              *(int *)((char *)&CarSpray_variable_7 + v26) = 0;
              *(int *)((char *)&CarSpray_variable_8 + v26) = 0;
              *(int *)((char *)&CarSpray_variable_9 + v26) = 0;
              *(int *)((char *)&CarSpray_variable_10 + v26) = 0;
              *(int *)((char *)&CarSpray_variable_11 + v26) = 0;
              *(int *)((char *)&CarSpray_variable_12 + v26) = 0;
            } while (v26 != 1408);
          }
          v27 = *(_DWORD *)(a1 + 32);
          if (player2_car == v27) {
            v28 = v27 ^ player2_car;
            do {
              v28 += 352;
              *(int *)((char *)&CarSpray_variable_14 + v28) = 0;
              *(int *)((char *)&CarSpray_variable_15 + v28) = 0;
              *(int *)((char *)&CarSpray_variable_16 + v28) = 0;
              *(int *)((char *)&CarSpray_variable_17 + v28) = 0;
              *(int *)((char *)&CarSpray_variable_18 + v28) = 0;
              *(int *)((char *)&CarSpray_variable_19 + v28) = 0;
              *(int *)((char *)&CarSpray_variable_20 + v28) = 0;
              *(int *)((char *)&CarSpray_variable_21 + v28) = 0;
            } while (v28 != 1408);
          }
        }
        if ((__int16)player1_car == *(_DWORD *)(a1 + 32) && SelectedView[0] != DeathView) {
          SelectedView[0] = DeathView;
          DeathView = -1;
          select_view(0);
          initcarview(ViewType[0], 0);
        }
        if (player2_car == *(_DWORD *)(a1 + 32) && SelectedView_variable_1 != DeathView_variable_1[0]) {
          SelectedView_variable_1 = DeathView_variable_1[0];
          DeathView_variable_1[0] = -1;
          select_view(1);
          initcarview(ViewType_variable_1, 1);
        }
        v4 = v42;
        *(_DWORD *)(a1 + 4) = localdata_variable_8[32 * v42];
        if (*(__int16 *)(a1 + 12) < carorder_variable_2[numstops] - 10) {
          v29 = *(_BYTE *)(a1 + 104) - 1;
          *(_BYTE *)(a1 + 104) = v29;
          if (v29 < 0)
            *(_BYTE *)(a1 + 104) = 0;
        }
        *(_DWORD *)(a1 + 28) = 1120403456;
        v30 = (__int16)player1_car;
        v31 = *(_DWORD *)(a1 + 32);
        *(_BYTE *)(a1 + 276) = 8;
        if (v30 == v31 || (LOBYTE(v3) = player2_car, player2_car == v31)) {
          LOBYTE(v3) = *(_BYTE *)(a1 + 103);
          if ((_BYTE)v3) {
            if ((unsigned __int8)v3 <= 1u) {
              v32 = 44;
            } else {
              if ((_BYTE)v3 != 2)
                goto LABEL_113;
              v32 = 43;
            }
          } else {
            v32 = 45;
          }
          LOBYTE(v3) = speechsample(v32, 0x8000, 18, *(_DWORD *)(a1 + 32));
        }
      }
    }
  } else {
    v13 = SelectedView[0];
    *(_BYTE *)(a1 + 103) = -1;
    if (v13 == 7) {
      v14 = *(_DWORD *)(a1 + 32) & 0xFE;
      v15 = ViewType[0] & 0xFE;
      if ((unsigned __int8)v15 == v14) {
        SelectedView[0] = v14 ^ v15;
        select_view(0);
        initcarview(ViewType[0], 0);
      }
    }
    if (human_control[*(_DWORD *)(a1 + 32)])
      ++dead_humans;
    LOBYTE(v3) = dead_humans;
    if (dead_humans < players) {
      v16 = *(__int16 *)(a1 + 12);
      *(_DWORD *)(a1 + 72) = 0;
      if (v16 == -1) {
        *(_DWORD *)a1 = 0;
        *(_DWORD *)(a1 + 4) = 0;
        *(_DWORD *)(a1 + 8) = 1148846080;
      } else {
        v17 = (float *)((char *)&localdata + 128 * v16);
        *(float *)a1 = 0.0 * v17[1] + 0.0 * *v17 + 0.0 * v17[2] - v17[9];
        *(float *)(a1 + 4) = 0.0 * v17[3] + 0.0 * v17[4] + 0.0 * v17[5] - v17[10];
        v18 = 0.0 * v17[6] + 0.0 * v17[7] + 0.0 * v17[8] - v17[11] + control_c_variable_102;
        *(_WORD *)(a1 + 14) = *(_WORD *)(a1 + 12);
        *(float *)(a1 + 8) = v18;
      }
      v19 = 308 * ViewType[0];
      *(_WORD *)(a1 + 12) = -1;
      *(_DWORD *)(a1 + 24) = 0;
      *(_DWORD *)(a1 + 112) = 0;
      *(_DWORD *)(a1 + 116) = 0;
      *(_BYTE *)(a1 + 128) = 0;
      *(_DWORD *)(a1 + 120) = 0;
      *(_DWORD *)(a1 + 124) = 0;
      if (Car_variable_23[v19] < 0) {
        for (ViewType[0] = 0; !human_control[ViewType[0]] || Car_variable_23[308 * ViewType[0]] < 0; ++ViewType[0])
          ;
        v20 = initcarview(ViewType[0], 0);
        stopallsamples(v20);
      }
      v3 = 308 * ViewType_variable_1;
      if (Car_variable_23[v3] < 0) {
        for (ViewType_variable_1 = 0;
              !human_control[ViewType_variable_1] || Car_variable_23[308 * ViewType_variable_1] < 0;
              ++ViewType_variable_1) {
          ;
        }
        v21 = initcarview(ViewType_variable_1, 0);
        LOBYTE(v3) = stopallsamples(v21);
      }
    }
  }
LABEL_113:
  if (v5 && *(char *)(a1 + 103) > 0) {
    *(_DWORD *)a1 = 0;
    *(_DWORD *)(a1 + 8) = 0;
    *(_WORD *)(a1 + 18) = 0;
    *(_WORD *)(a1 + 20) = 0;
    *(_DWORD *)(a1 + 64) = 0;
    *(_WORD *)(a1 + 16) = 0;
    *(_BYTE *)(a1 + 187) = 0;
    *(_DWORD *)(a1 + 72) = 3;
    *(_DWORD *)(a1 + 68) = 0;
    *(_DWORD *)(a1 + 192) = 0;
    *(_WORD *)(a1 + 238) = 1080;
    *(_DWORD *)(a1 + 188) = 0;
    *(_DWORD *)(a1 + 204) = 0;
    *(_DWORD *)(a1 + 140) = 0;
    *(_DWORD *)(a1 + 144) = 0;
    *(_DWORD *)(a1 + 148) = 0;
    *(_DWORD *)(a1 + 152) = 0;
    *(_DWORD *)(a1 + 156) = 0;
    *(_DWORD *)(a1 + 132) = 0;
    *(_DWORD *)(a1 + 136) = 0;
    *(_DWORD *)(a1 + 176) = 0;
    *(_DWORD *)(a1 + 208) = -1;
    *(_DWORD *)(a1 + 24) = 0;
    *(_DWORD *)(a1 + 124) = 0;
    *(_DWORD *)(a1 + 120) = 0;
    *(_DWORD *)(a1 + 116) = 0;
    *(_DWORD *)(a1 + 112) = 0;
    *(_BYTE *)(a1 + 128) = 0;
    *(_WORD *)(a1 + 286) = 0;
    *(_WORD *)(a1 + 236) = -1;
    *(_BYTE *)(a1 + 240) = 0;
    *(_BYTE *)(a1 + 241) = 0;
    *(_BYTE *)(a1 + 243) = 0;
    *(_WORD *)(a1 + 12) = v4;
    *(_DWORD *)(a1 + 216) = v4;
    *(_WORD *)(a1 + 14) = v4;
    *(_DWORD *)(a1 + 132) = 0;
    *(_DWORD *)(a1 + 136) = 0;
    putflat(a1);
    *(_DWORD *)(a1 + 280) = 1 - *(_DWORD *)(a1 + 280);
    if (Play_View == 1) {
      if ((ViewType[0] & 1) != 0)
        v35 = ViewType[0] - 1;
      else
        v35 = ViewType[0] + 1;
      if (v35 != *(_DWORD *)(a1 + 32))
        goto LABEL_126;
      v34 = 0;
      v33 = -v35 - 1;
    } else {
      if (ViewType[0] == *(_DWORD *)(a1 + 32))
        initcarview(ViewType[0], 0);
      v33 = ViewType_variable_1;
      if (ViewType_variable_1 != *(_DWORD *)(a1 + 32))
        goto LABEL_126;
      v34 = 1;
    }
    initcarview(v33, v34);
  LABEL_126:
    *(_WORD *)(a1 + 284) = -1;
    *(_BYTE *)(a1 + 131) = 0;
    *(_BYTE *)(a1 + 306) = 0;
    v36 = *(_BYTE *)(a1 + 273);
    *(_BYTE *)(a1 + 272) = 0;
    LOBYTE(v3) = 1 - v36;
    *(_BYTE *)(a1 + 273) = 1 - v36;
  }
  return v3;*/
}

//-------------------------------------------------------------------------------------------------
//00030200
void testteaminit(tCar *pCar)
{
  /*
  int result; // eax

  if ((ViewType[0] & 1) != 0)
    result = ViewType[0] - 1;
  else
    result = ViewType[0] + 1;
  if (result == *(_DWORD *)(a1 + 32))
    return initcarview(-result - 1, 0);
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00030230
void doteaminit()
{
  int iViewType; // eax

  if ((ViewType[0] & 1) != 0)
    iViewType = ViewType[0] - 1;
  else
    iViewType = ViewType[0] + 1;
  initcarview(-iViewType - 1, 0);
}

//-------------------------------------------------------------------------------------------------
//00030260
int16 hitleft(int a1, int a2, int a3)
{
  (void)(a1); (void)(a2); (void)(a3);
  return 0;
  /*
  int v3; // ecx
  __int16 v4; // fps
  double v5; // st7
  _BOOL1 v6; // c0
  char v7; // c2
  _BOOL1 v8; // c3
  double v9; // st7
  int v10; // eax
  int v11; // eax
  __int16 v12; // fps
  _BOOL1 v13; // c0
  char v14; // c2
  _BOOL1 v15; // c3
  double v16; // st7
  int v17; // eax
  double v18; // st7
  __int64 v19; // rax
  double v20; // st7
  double v21; // st6
  int v22; // eax
  int v23; // eax
  double v24; // st7
  long double v25; // st7
  int v26; // eax
  double v27; // st7
  int v28; // eax
  int v29; // edx
  int v30; // eax
  __int16 v31; // ax
  __int16 result; // ax
  float v33; // [esp+0h] [ebp-44h]
  float v34; // [esp+0h] [ebp-44h]
  float v35; // [esp+4h] [ebp-40h]
  float v36; // [esp+18h] [ebp-2Ch]
  int v37; // [esp+1Ch] [ebp-28h]
  float v38; // [esp+20h] [ebp-24h]
  float v39; // [esp+24h] [ebp-20h]
  float v40; // [esp+28h] [ebp-1Ch]
  float v41; // [esp+2Ch] [ebp-18h]
  float v42; // [esp+30h] [ebp-14h]
  float v43; // [esp+34h] [ebp-10h]
  float v44; // [esp+34h] [ebp-10h]

  v3 = a1;
  v5 = *(float *)(a1 + 24);
  v6 = v5 < control_c_variable_104;
  v7 = 0;
  v8 = v5 == control_c_variable_104;
  LOWORD(a1) = v4;
  if (v5 >= control_c_variable_104) {
    v37 = 512;
  } else {
    v9 = *(float *)(v3 + 24) * control_c_variable_105 * control_c_variable_106;
    _CHP(a1, a2);
    v37 = (int)v9;
  }
  v10 = *(_DWORD *)(v3 + 64);
  v38 = tcos[v10] * *(float *)(v3 + 24);
  v40 = tsin[v10] * *(float *)(v3 + 24);
  if (a3)
    v11 = rightang;
  else
    v11 = leftang;
  v39 = v38 * tcos[v11] + v40 * tsin[v11];
  v43 = -v38 * tsin[v11] + v40 * tcos[v11];
  if (!*(_BYTE *)(v3 + 272)) {
    v13 = v43 > 0.0;
    v14 = 0;
    v15 = 0.0 == v43;
    LOWORD(v11) = v12;
    if (v43 > 0.0) {
      v16 = v40 * control_c_variable_107 * control_c_variable_108;
      _CHP(v11, a2);
      v17 = a2;
      a2 = *(_DWORD *)(v3 + 32);
      sfxpend(v17, a2, (int)v16);
      if (death_race)
        v18 = v40 * control_c_variable_109 * control_c_variable_110;
      else
        v18 = v40 * control_c_variable_109;
      v33 = v18;
      v11 = dodamage(v33);
    }
    v43 = v43 * control_c_variable_111;
    v39 = v39 * control_c_variable_112;
  }
  _CHP(v11, a2);
  v19 = (int)v43;
  v44 = (float)-abs32((int)v43);
  v20 = v39;
  v21 = v39;
  if (a3)
    v22 = rightang;
  else
    v22 = leftang;
  v41 = v21 * tcos[v22] - v44 * tsin[v22];
  v42 = v20 * tsin[v22] + v44 * tcos[v22];
  if (*(float *)(v3 + 28) <= 0.0 && v42 == control_c_variable_113) {
    *(_DWORD *)(v3 + 24) = 0;
  } else {
    if (*(float *)(v3 + 24) < 0.0) {
      v35 = -v41;
      if ((LODWORD(v35) & 0x7FFFFFFF) != 0 || (v36 = -v42, (LODWORD(v36) & 0x7FFFFFFF) != 0)) {
        IF_DATAN2(v35);
        v27 = v35 * control_c_variable_114 / control_c_variable_115;
        _CHP(v28, LODWORD(v35));
        v26 = (int)v27 & 0x3FFF;
      } else {
        v26 = 0;
      }
      *(_DWORD *)(v3 + 64) = v26;
      v25 = -sqrt(v41 * v41 + v42 * v42);
    } else {
      if (fabs(v21 * tcos[v22] - v44 * tsin[v22]) || fabs(v20 * tsin[v22] + v44 * tcos[v22])) {
        IF_DATAN2(v41);
        v24 = v41 * control_c_variable_114 / control_c_variable_115;
        _CHP(v19, HIDWORD(v19));
        v23 = (int)v24 & 0x3FFF;
      } else {
        v23 = 0;
      }
      *(_DWORD *)(v3 + 64) = v23;
      v25 = sqrt(v41 * v41 + v42 * v42);
    }
    *(float *)(v3 + 24) = v25;
  }
  v29 = *(_DWORD *)(v3 + 64) - *(__int16 *)(v3 + 20);
  v30 = v29 + (v29 < 0 ? 0x4000 : 0);
  if (v30 > 0x2000)
    v30 -= 0x4000;
  if (v30 > v37)
    v30 = v37;
  if (v30 < -v37)
    v30 = -v37;
  v34 = *(float *)(v3 + 24);
  v31 = *(_WORD *)(v3 + 20) + v30;
  HIBYTE(v31) &= 0x3Fu;
  *(_WORD *)(v3 + 20) = v31;
  SetEngine(v3, v34);
  *(_DWORD *)(v3 + 76) = 0;
  result = putflat(v3);
  *(_BYTE *)(v3 + 272) = 18;
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00030590
int16 hitright(int a1, int a2, int a3)
{
  (void)(a1); (void)(a2); (void)(a3);
  return 0;
  /*
  int v3; // ecx
  __int16 v4; // fps
  double v5; // st7
  _BOOL1 v6; // c0
  char v7; // c2
  _BOOL1 v8; // c3
  double v9; // st7
  int v10; // eax
  int v11; // eax
  __int16 v12; // fps
  _BOOL1 v13; // c0
  char v14; // c2
  _BOOL1 v15; // c3
  double v16; // st7
  double v17; // st7
  int v18; // eax
  double v19; // st7
  __int64 v20; // rax
  double v21; // st7
  double v22; // st6
  int v23; // eax
  int v24; // eax
  double v25; // st7
  long double v26; // st7
  int v27; // eax
  double v28; // st7
  int v29; // edx
  int v30; // eax
  __int16 v31; // ax
  __int16 result; // ax
  float v33; // [esp+0h] [ebp-4Ch]
  float v34; // [esp+4h] [ebp-48h]
  float v35; // [esp+18h] [ebp-34h]
  float v36; // [esp+1Ch] [ebp-30h]
  int v37; // [esp+20h] [ebp-2Ch]
  float v38; // [esp+24h] [ebp-28h]
  float v39; // [esp+28h] [ebp-24h]
  float v40; // [esp+2Ch] [ebp-20h]
  float v41; // [esp+30h] [ebp-1Ch]
  float v42; // [esp+34h] [ebp-18h]
  float v43; // [esp+34h] [ebp-18h]
  float v44; // [esp+38h] [ebp-14h]

  v3 = a1;
  v5 = *(float *)(a1 + 24);
  v6 = v5 < control_c_variable_116;
  v7 = 0;
  v8 = v5 == control_c_variable_116;
  LOWORD(a1) = v4;
  if (v5 >= control_c_variable_116) {
    v37 = 512;
  } else {
    v9 = *(float *)(v3 + 24) * control_c_variable_117 * control_c_variable_118;
    _CHP(a1, a2);
    v37 = (int)v9;
  }
  v10 = *(_DWORD *)(v3 + 64);
  v38 = tcos[v10] * *(float *)(v3 + 24);
  v39 = tsin[v10] * *(float *)(v3 + 24);
  if (a3)
    v11 = rightang;
  else
    v11 = leftang;
  v40 = v38 * tcos[v11] + v39 * tsin[v11];
  v42 = -v38 * tsin[v11] + v39 * tcos[v11];
  if (!*(_BYTE *)(v3 + 272)) {
    v13 = v39 > 0.0;
    v14 = 0;
    v15 = 0.0 == v39;
    LOWORD(v11) = v12;
    if (v39 < 0.0) {
      v16 = -v39;
      v36 = v16;
      v17 = v16 * control_c_variable_119 * control_c_variable_120;
      _CHP(v11, a2);
      v18 = a2;
      a2 = *(_DWORD *)(v3 + 32);
      sfxpend(v18, a2, (int)v17);
      if (death_race)
        v19 = v36 * control_c_variable_121 * control_c_variable_122;
      else
        v19 = v36 * control_c_variable_121;
      v33 = v19;
      v11 = dodamage(v33);
    }
    v42 = v42 * control_c_variable_123;
    v40 = v40 * control_c_variable_124;
  }
  _CHP(v11, a2);
  v20 = (int)v42;
  v43 = (float)(int)abs32((int)v42);
  v21 = v40;
  v22 = v40;
  if (a3)
    v23 = rightang;
  else
    v23 = leftang;
  v41 = v22 * tcos[v23] - v43 * tsin[v23];
  v44 = v21 * tsin[v23] + v43 * tcos[v23];
  if (*(float *)(v3 + 28) <= 0.0 && v44 == control_c_variable_125) {
    *(_DWORD *)(v3 + 24) = 0;
  } else {
    if (*(float *)(v3 + 24) < 0.0) {
      v34 = -v41;
      if ((LODWORD(v34) & 0x7FFFFFFF) != 0 || (v35 = -v44, (LODWORD(v35) & 0x7FFFFFFF) != 0)) {
        IF_DATAN2(v34);
        v28 = v34 * control_c_variable_126 / control_c_variable_127;
        _CHP(v20, HIDWORD(v20));
        v27 = (int)v28 & 0x3FFF;
      } else {
        v27 = 0;
      }
      *(_DWORD *)(v3 + 64) = v27;
      v26 = -sqrt(v41 * v41 + v44 * v44);
    } else {
      if (fabs(v22 * tcos[v23] - v43 * tsin[v23]) || fabs(v21 * tsin[v23] + v43 * tcos[v23])) {
        IF_DATAN2(v41);
        v25 = v41 * control_c_variable_126 / control_c_variable_127;
        _CHP(v20, HIDWORD(v20));
        v24 = (int)v25 & 0x3FFF;
      } else {
        v24 = 0;
      }
      *(_DWORD *)(v3 + 64) = v24;
      v26 = sqrt(v41 * v41 + v44 * v44);
    }
    *(float *)(v3 + 24) = v26;
  }
  if (!*(_BYTE *)(v3 + 272)) {
    v29 = *(_DWORD *)(v3 + 64) - *(__int16 *)(v3 + 20);
    v30 = v29 + (v29 < 0 ? 0x4000 : 0);
    if (v30 > 0x2000)
      v30 -= 0x4000;
    if (v30 > v37)
      v30 = v37;
    if (v30 < -v37)
      v30 = -v37;
    v31 = *(_WORD *)(v3 + 20) + v30;
    HIBYTE(v31) &= 0x3Fu;
    *(_WORD *)(v3 + 20) = v31;
  }
  SetEngine(v3, *(float *)(v3 + 24));
  *(_DWORD *)(v3 + 76) = 0;
  result = putflat(v3);
  *(_BYTE *)(v3 + 272) = 18;
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//000308D0
int scansection(tCar *pCar)
{
  return 0;/*
  int v1; // edi
  int iChunkIdx; // ebx
  tData *pData; // edx
  int v5; // ecx
  double v6; // st7
  double v7; // st5
  double v8; // rt0
  double v9; // st7
  double v10; // st5
  double v11; // rt1
  int result; // eax
  float v13; // [esp+4h] [ebp-30h]
  float v14; // [esp+8h] [ebp-2Ch]
  float v15; // [esp+Ch] [ebp-28h]
  float fZ; // [esp+10h] [ebp-24h]
  float fY; // [esp+14h] [ebp-20h]
  float fX; // [esp+18h] [ebp-1Ch]

  v1 = TRAK_LEN;
  fX = pCar->pos.fX;
  fY = pCar->pos.fY;
  iChunkIdx = pCar->nCurrChunk;
  fZ = pCar->pos.fZ;
  pData = &localdata[iChunkIdx];
  v13 = pData->pointAy[0].fY * fY
    + pData->pointAy[0].fX * pCar->pos.fX
    + pData->pointAy[0].fZ * fZ
    - pData->pointAy[3].fX;
  v14 = pData->pointAy[1].fY * fY
    + pData->pointAy[1].fX * pCar->pos.fX
    + pData->pointAy[1].fZ * fZ
    - pData->pointAy[3].fY;
  v15 = pData->pointAy[2].fY * fY
    + pData->pointAy[2].fX * pCar->pos.fX
    + pData->pointAy[2].fZ * fZ
    - pData->pointAy[3].fZ;
  v5 = 0;
  if (pCar->pos.fX < (double)pData->fUnk13) {
    do {
      if (--iChunkIdx == -1)
        iChunkIdx = TRAK_LEN - 1;
      pData = &localdata[iChunkIdx];
      v6 = v14 + pData->pointAy[3].fY;
      v7 = v13 + pData->pointAy[3].fX;
      v8 = v15 + pData->pointAy[3].fZ;
      fX = pData->pointAy[1].fX * v6 + pData->pointAy[0].fX * v7 + pData->pointAy[2].fX * v8;
      fY = pData->pointAy[0].fY * v7 + pData->pointAy[1].fY * v6 + pData->pointAy[2].fY * v8;
      fZ = v6 * pData->pointAy[1].fZ + v7 * pData->pointAy[0].fZ + v8 * pData->pointAy[2].fZ;
      v5 -= pData->iUnk16;
    } while (fX < (double)pData->fUnk13);
  }
  while (fX > (double)pData->fUnk13) {
    ++iChunkIdx;
    v5 += pData->iUnk16;
    if (iChunkIdx == TRAK_LEN)
      iChunkIdx ^= TRAK_LEN;
    pData = &localdata[iChunkIdx];
    v9 = v14 + pData->pointAy[3].fY;
    v10 = v13 + pData->pointAy[3].fX;
    v11 = v15 + pData->pointAy[3].fZ;
    fX = pData->pointAy[1].fX * v9 + pData->pointAy[0].fX * v10 + pData->pointAy[2].fX * v11;
    fY = pData->pointAy[0].fY * v10 + pData->pointAy[1].fY * v9 + pData->pointAy[2].fY * v11;
    fZ = v9 * pData->pointAy[1].fZ + v10 * pData->pointAy[0].fZ + v11 * pData->pointAy[2].fZ;
  }
  pCar->pos.fX = fX;
  pCar->pos.fY = fY;
  pCar->pos.fZ = fZ;
  pCar->nDirection -= v5;
  HIBYTE(pCar->nDirection) &= 0x3Fu;
  result = pCar->iAngleIdx15 - v5;
  pCar->nCurrChunk = iChunkIdx;
  pCar->iAngleIdx15 = result;
  pCar->iAngleIdx15 = result & 0x3FFF;
  TRAK_LEN = v1;
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00030AC0
double getgroundz(float a1, float a2, int iChunkIdx)
{
  return 0.0;/*
  tData *pData; // edx
  double v8; // st7
  tTrackInfo *pTrackInfo; // ebx
  double v10; // st7
  float v12; // [esp+4h] [ebp-14h]
  float v13; // [esp+8h] [ebp-10h]

  pData = &localdata[iChunkIdx];
  v8 = (double)SLODWORD(pData->fUnk23) * a1 / (pData->fUnk13 * control_c_variable_128);
  _CHP();
  pTrackInfo = &TrackInfo[iChunkIdx];
  v13 = -a2 * ptan[(int)v8 & 0x3FFF];
  if (a2 >= (double)pData->fUnk14)
    v13 = (a2 - pData->fUnk14) * pTrackInfo->center.fY / pTrackInfo->center.fX + v13;
  v10 = -a2;
  if (v10 >= pData->fUnk14) {
    v12 = v10;
    return (float)((v12 - pData->fUnk14) * *(float *)&pTrackInfo->iUnk1 / pTrackInfo->center.fZ + v13);
  }
  return v13;*/
};

//-------------------------------------------------------------------------------------------------
//00030B80
double getroadz(float a1, float a2, int iChunkIdx)
{
  return 0.0;/*
  double v7; // st7

  v7 = (double)SLODWORD(localdata[iChunkIdx].fUnk23) * a1 / (localdata[iChunkIdx].fUnk13 * control_c_variable_129);
  _CHP();
  return -a2 * ptan[(int)v7 & 0x3FFF];*/
}

//-------------------------------------------------------------------------------------------------
//00030BD0
void putflat(tCar *pCar)
{
  int nCurrChunk; // esi
  tTrackInfo *pTrackInfo; // edi
  tData *pCurrData; // ecx
  int iPrevChunkIdx; // eax
  int iNextChunkIdx2; // edx
  tData *pPrevData; // ebp
  int iPitch; // eax
  int iLaneType; // edx
  //int64 llSurfaceType1; // rax
  //int64 llSurfaceType2; // rax
  //int64 llSurfaceType3; // rax
  double dPitchFloat; // st7
  int iBankDelta; // esi
  double dInvHalfLength; // st7
  double dBankTerm1; // st6
  double dBankTerm2; // st5
  double dBankAngle; // st7
  //int16 nBankAngleInt; // fps
  double dPitchCorrected; // st7
  double dBankFloat; // st7
  double dLeftBankAdj; // st7
  double dShoulderHeight; // st7
  double dRightBankAdj; // st7
  double dAbsYPos; // st7
  double dPitchForCalc; // st7
  double dPitchResult; // st5
  //int iYawIndex; // eax
  double dRollResult; // st7
  int nPitchFinal; // eax
  int iStunned; // edi
  int nYaw; // [esp+14h] [ebp-40h]
  float fAbsYPos; // [esp+1Ch] [ebp-38h]
  float fNegYPos; // [esp+20h] [ebp-34h]
  int iRollFinal; // [esp+24h] [ebp-30h]
  tData *pNextData; // [esp+28h] [ebp-2Ch]
  int iNextChunkIdx; // [esp+2Ch] [ebp-28h]
  int iBankInt; // [esp+30h] [ebp-24h]
  int iPitchInt; // [esp+34h] [ebp-20h]
  int iPitchFinal; // [esp+34h] [ebp-20h]

  nCurrChunk = pCar->nCurrChunk;                // Get current track chunk and related data
  pTrackInfo = &TrackInfo[nCurrChunk];
  pCurrData = &localdata[nCurrChunk];
  nYaw = pCar->nYaw;
  if (pCar->pos.fX >= 0.0)                    // Determine previous and next chunk indices based on car direction
  {
    iPrevChunkIdx = pCar->nCurrChunk;
    iNextChunkIdx = nCurrChunk + 1;
    if (nCurrChunk + 1 == TRAK_LEN)
      iNextChunkIdx = TRAK_LEN ^ (nCurrChunk + 1);
    iNextChunkIdx2 = iNextChunkIdx;
  } else {
    iPrevChunkIdx = nCurrChunk - 1;
    if (nCurrChunk - 1 < 0)
      iPrevChunkIdx = TRAK_LEN - 1;
    iNextChunkIdx2 = iPrevChunkIdx;
  }
  pNextData = &localdata[iNextChunkIdx2];
  pPrevData = &localdata[iPrevChunkIdx];
  if (pCar->pos.fY <= (double)pCurrData->fTrackHalfWidth)// Determine which lane car is in and get appropriate pitch angle
  {
    if (-pCurrData->fTrackHalfWidth <= pCar->pos.fY) {
      iPitch = pPrevData->iPitch;               // Center lane (on track)
      iLaneType = 1;
    } else {
      iPitch = pPrevData->iOuterLanePitchAngle; // Outer lane (left side of track)
      iLaneType = 2;
    }
  } else {
    iPitch = pPrevData->iInnerLanePitchAngle;   // Inner lane (right side of track)
    iLaneType = 0;
  }
  iPitchInt = iPitch;
  if (pCar->pos.fX < 0.0)                     // Check surface type and apply pitch corrections based on car position
  {

    if ((TrakColour[nCurrChunk][iLaneType] & SURFACE_FLAG_SKIP_RENDER) != 0)
    //llSurfaceType3 = TrakColour[nCurrChunk][iLaneType];
    //if ((((HIDWORD(llSurfaceType3) ^ (unsigned int)llSurfaceType3) - HIDWORD(llSurfaceType3)) & 0x20000) != 0)// SURFACE_FLAG_SKIP_RENDER
      iPitchInt = 0;
  } else {                                             // Steep downhill: zero pitch if car is fast and AI state allows
    if (iPitch < -512 && pCar->fFinalSpeed > 50.0 && (TrakColour[pCar->nCurrChunk][pCar->iLaneType] & 0x80000) != 0)
      iPitchInt = 0;

    if ((TrakColour[nCurrChunk][iLaneType] & SURFACE_FLAG_SKIP_RENDER) != 0)
    //llSurfaceType1 = TrakColour[nCurrChunk][iLaneType];// Check current chunk surface type and zero pitch if needed
    //if ((((HIDWORD(llSurfaceType1) ^ (unsigned int)llSurfaceType1) - HIDWORD(llSurfaceType1)) & 0x20000) != 0)// SURFACE_FLAG_SKIP_RENDER
      iPitchInt = 0;

    if (pCar->fFinalSpeed > 50.0) {

      if ((TrakColour[iNextChunkIdx][pCar->iLaneType] & SURFACE_FLAG_SKIP_RENDER) != 0)
      //llSurfaceType2 = TrakColour[iNextChunkIdx][pCar->iLaneType];// Check next chunk surface type for fast cars
      //if ((((HIDWORD(llSurfaceType2) ^ (unsigned int)llSurfaceType2) - HIDWORD(llSurfaceType2)) & 0x20000) != 0)// SURFACE_FLAG_SKIP_RENDER
        iPitchInt = 0;
    }
  }
  dPitchFloat = (double)iPitchInt * pCar->pos.fX / (pCurrData->fTrackHalfLength * 2.0);// Calculate pitch angle based on car position along track
  //_CHP();
  iPitchFinal = (int)dPitchFloat;
  if ((TrakColour[nCurrChunk][1] & SURFACE_FLAG_BOUNCE_30) != 0)// SURFACE_FLAG_BOUNCE_30
  {
    if (pCar->pos.fX < 0.0) {
      dInvHalfLength = 1.0 / pCurrData->fTrackHalfLength;
      dBankTerm1 = (pCar->pos.fX + pCurrData->fTrackHalfLength) * (double)pCurrData->iBankDelta * dInvHalfLength;
      dBankTerm2 = (double)((pNextData->iBankDelta + pCurrData->iBankDelta) / -2);
    } else {
      iBankDelta = pCurrData->iBankDelta;
      dInvHalfLength = 1.0 / pCurrData->fTrackHalfLength;
      dBankTerm1 = (pCar->pos.fX - pCurrData->fTrackHalfLength) * (double)-iBankDelta * dInvHalfLength;
      dBankTerm2 = (double)((iBankDelta + pNextData->iBankDelta) / 2);
    }
    dBankAngle = dInvHalfLength * (dBankTerm2 * pCar->pos.fX) + dBankTerm1;// Apply special banking interpolation and atan2 correction
    //_CHP();
    dPitchCorrected = (double)iPitchFinal
      - atan2(pCar->pos.fY * tsin[(int)dBankAngle & 0x3FFF], pCurrData->fTrackHalfLength * 2.0) * 16384.0 / 6.28318530718;
    //_CHP();
    iPitchFinal = (int)dPitchCorrected;
  }
  dBankFloat = (double)pCurrData->iBankDelta * pCar->pos.fX / (pCurrData->fTrackHalfLength * 2.0);// Calculate basic banking angle based on car X position
  //_CHP();
  iBankInt = (int)dBankFloat;
  pCar->pos.fZ = -(pCar->pos.fY * ptan[(int)dBankFloat & 0x3FFF]);// Calculate car Z position using banking angle
  if (pCar->pos.fY < 0.0)                     // Apply track banking adjustments based on car Y position
  {
    fNegYPos = -pCar->pos.fY;                   // Right side banking adjustments
    if (pCurrData->fTrackHalfWidth + pCar->fCarHalfWidth > fNegYPos) {
      if (pCurrData->fTrackHalfWidth - pCar->fCarHalfWidth <= fNegYPos) {
        dRightBankAdj = (fNegYPos - pCurrData->fTrackHalfWidth + pCar->fCarHalfWidth) * (double)pTrackInfo->iRightBankAngle / (pCar->fCarHalfWidth * 2.0) + (double)iBankInt;
        //_CHP();
        iBankInt = (int)dRightBankAdj;
      }
    } else {
      iBankInt += pTrackInfo->iRightBankAngle;
    }
    dAbsYPos = -pCar->pos.fY;                   // Add shoulder height if car is off track (right side)
    if (dAbsYPos >= pCurrData->fTrackHalfWidth) {
      fAbsYPos = (float)dAbsYPos;
      dShoulderHeight = (fAbsYPos - pCurrData->fTrackHalfWidth) * pTrackInfo->fRShoulderHeight / pTrackInfo->fRShoulderWidth;
      goto LABEL_43;
    }
  } else {                                             // Left side banking adjustments
    if (pCurrData->fTrackHalfWidth + pCar->fCarHalfWidth > pCar->pos.fY) {
      if (pCurrData->fTrackHalfWidth - pCar->fCarHalfWidth <= pCar->pos.fY) {
        dLeftBankAdj = (double)iBankInt - (pCar->pos.fY - pCurrData->fTrackHalfWidth + pCar->fCarHalfWidth) * (double)pTrackInfo->iLeftBankAngle / (pCar->fCarHalfWidth * 2.0);
        //_CHP();
        iBankInt = (int)dLeftBankAdj;
      }
    } else {
      iBankInt -= pTrackInfo->iLeftBankAngle;
    }
    if (pCar->pos.fY >= (double)pCurrData->fTrackHalfWidth)// Add shoulder height if car is off track (left side)
    {
      dShoulderHeight = (pCar->pos.fY - pCurrData->fTrackHalfWidth) * pTrackInfo->fLShoulderHeight / pTrackInfo->fLShoulderWidth;
    LABEL_43:
      pCar->pos.fZ = (float)dShoulderHeight + pCar->pos.fZ;
    }
  }
  dPitchForCalc = (double)iPitchFinal;          // Transform pitch and bank angles using car yaw rotation
  dPitchResult = dPitchForCalc * tcos[nYaw] - (double)iBankInt * tsin[nYaw];
  //_CHP();
  dRollResult = dPitchForCalc * tsin[nYaw] + (double)iBankInt * tcos[nYaw];
  //_CHP();
  nPitchFinal = (int)dPitchResult;
  nPitchFinal = ((uint16)(int)dPitchResult >> 8) & 0x3FFF;// Mask pitch angle to 14-bit range
  //BYTE1(nPitchFinal) = ((unsigned __int16)(int)dPitchResult >> 8) & 0x3F;// Mask pitch result to 14-bit range (0x3FFF)
  iStunned = pCar->iStunned;
  pCar->nPitch = nPitchFinal;
  iRollFinal = (int)dRollResult;
  if (iStunned)                               // Apply stunned car effects - add roll offset and height adjustment
  {
    iRollFinal = (int16)(iRollFinal) + 0x2000;
    pCar->pos.fZ = CarBox.hitboxAy[pCar->byCarDesignIdx][4].fZ + pCar->pos.fZ;
  }
  pCar->nRoll = (int16)iRollFinal & 0x3FFF;            // Set final roll angle with 14-bit mask
}

//-------------------------------------------------------------------------------------------------
//00031060
float *findnearcars(float *a1, float *a2, float *a3, float *a4, float *a5, float *a6, float *a7)
{
  return 0;/*
  int v8; // eax
  float *result; // eax
  float v10; // [esp+0h] [ebp-18h]
  float v11; // [esp+4h] [ebp-14h]

  v8 = *((_DWORD *)a1 + 8);
  if (v8 == nearcall[4 * nearcarcheck]
    || v8 == nearcall_variable_1[4 * nearcarcheck]
    || v8 == nearcall_variable_2[4 * nearcarcheck]
    || v8 == nearcall_variable_3[4 * nearcarcheck]) {
    findnearcarsforce((int)a1, (int *)a2, a3, (int *)a4, a5, a6, a7);
    a1[62] = *a2;
    a1[63] = *a3;
    a1[64] = *a4;
    a1[65] = *a5;
    a1[66] = *a6;
    result = a7;
    a1[67] = *a7;
  } else {
    *a2 = a1[62];
    v11 = a1[63];
    *a4 = a1[64];
    v10 = a1[65];
    *a6 = a1[66];
    *a7 = a1[67];
    if (*(_DWORD *)a2 != -1) {
      if (v11 < 0.0) {
        v11 = v11 + control_c_variable_134;
      } else {
        v11 = v11 + control_c_variable_134;
        if (v11 < 0.0)
          v11 = 0.0;
      }
    }
    if (*(_DWORD *)a4 != -1) {
      if (v10 < 0.0) {
        v10 = v10 + control_c_variable_134;
      } else {
        v10 = v10 + control_c_variable_134;
        if (v10 < 0.0)
          v10 = 0.0;
      }
    }
    *a3 = v11;
    *a5 = v10;
    a1[63] = v11;
    a1[65] = v10;
    if (Car[*(_DWORD *)a2].nCurrChunk == -1) {
      *a2 = NAN;
      *a3 = -10000.0;
      a1[62] = NAN;
      a1[63] = -10000.0;
    }
    result = (float *)Car[*(_DWORD *)a4].nCurrChunk;
    if (result == (float *)-1) {
      *a4 = NAN;
      result = a5;
      *a5 = -10000.0;
      a1[64] = NAN;
      a1[65] = -10000.0;
    }
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00031250
int findnearcarsforce(int a1, int *a2, float *a3, int *a4, void *a5, float *a6, float *a7)
{
  return 0;/*
  int v7; // esi
  long double v9; // st7
  int v10; // ebx
  tData *v11; // ecx
  double v12; // st7
  double v13; // st7
  int v14; // ebx
  double v15; // st6
  double v16; // rt0
  double v17; // rt1
  double v18; // st5
  tData *v19; // ecx
  int v20; // edi
  int v21; // eax
  int v22; // ebx
  double v23; // st7
  int v24; // esi
  int v25; // ebx
  int v26; // eax
  double v27; // st7
  int nCurrChunk; // ebx
  double v29; // st7
  signed int i; // ecx
  int v31; // ebx
  long double v32; // st7
  _DWORD *v33; // ebx
  int result; // eax
  float v37; // [esp+1Ch] [ebp-54h]
  float v38; // [esp+20h] [ebp-50h]
  float v39; // [esp+24h] [ebp-4Ch]
  float v40; // [esp+28h] [ebp-48h]
  int v41; // [esp+2Ch] [ebp-44h]
  int v42; // [esp+30h] [ebp-40h]
  float v43; // [esp+34h] [ebp-3Ch]
  float v44; // [esp+38h] [ebp-38h]
  float v45; // [esp+3Ch] [ebp-34h]
  float v46; // [esp+40h] [ebp-30h]
  float v47; // [esp+44h] [ebp-2Ch]
  float v48; // [esp+48h] [ebp-28h]
  float v49; // [esp+4Ch] [ebp-24h]
  float v50; // [esp+50h] [ebp-20h]
  int v51; // [esp+54h] [ebp-1Ch]
  float v52; // [esp+58h] [ebp-18h]
  int v53; // [esp+5Ch] [ebp-14h]
  float v54; // [esp+60h] [ebp-10h]
  float j; // [esp+60h] [ebp-10h]
  float v56; // [esp+60h] [ebp-10h]
  float v57; // [esp+60h] [ebp-10h]

  v7 = TRAK_LEN;
  v38 = CarStrategy_variable_1[10 * *(_DWORD *)(a1 + 32)];
  v9 = fabs(*(float *)(a1 + 24));
  if (v9 < control_c_variable_135) {
    v37 = v9;
    v38 = (v38 + control_c_variable_136) * v37 * control_c_variable_137 + control_c_variable_138;
  }
  v49 = -10000.0;
  v50 = -10000.0;
  v10 = *(__int16 *)(a1 + 12);
  v41 = -1;
  v42 = -1;
  if (*(_DWORD *)(a1 + 188)) {
    v48 = *(float *)a1 - localdata[v10].fUnk13 - v38;
    while (control_c_variable_140 * localdata[v10].fUnk13 > v48) {
      v13 = control_c_variable_139 * localdata[v10--].fUnk13 + v48;
      v48 = v13;
      if (v10 < 0)
        v10 = TRAK_LEN - 1;
    }
    v11 = &localdata[v10];
    v12 = v48 + v11->fUnk13;
  } else {
    v47 = v38 + *(float *)a1 + localdata[v10].fUnk13;
    while (1) {
      v44 = control_c_variable_139 * localdata[v10].fUnk13;
      if (v47 <= (double)v44)
        break;
      ++v10;
      v47 = v47 - v44;
      if (v10 == TRAK_LEN)
        v10 ^= TRAK_LEN;
    }
    v11 = &localdata[v10];
    v12 = v47 - v11->fUnk13;
  }
  v39 = v12;
  v14 = v10 + 1;
  if (v14 == TRAK_LEN)
    v14 ^= TRAK_LEN;
  v15 = ((v11->fUnk13 - v39) * *(&v11->fUnk25 + *(_DWORD *)(a1 + 160))
       + (v39 + v11->fUnk13) * *(&localdata[v14].fUnk25 + *(_DWORD *)(a1 + 160)))
    / (v11->fUnk13
     * control_c_variable_139);
  v16 = v11->pointAy[1].fX * v39 + v11->pointAy[1].fY * v15 - v11->pointAy[3].fY;
  v17 = v11->pointAy[0].fY * v15 + v11->pointAy[0].fX * v39 - v11->pointAy[3].fX;
  v18 = v39 * v11->pointAy[2].fX + v15 * v11->pointAy[2].fY - v11->pointAy[3].fZ;
  v19 = &localdata[*(__int16 *)(a1 + 12)];
  *a6 = (v16 + v19->pointAy[3].fY) * v19->pointAy[1].fX
    + (v17 + v19->pointAy[3].fX) * v19->pointAy[0].fX
    + (v18 + v19->pointAy[3].fZ) * v19->pointAy[2].fX;
  *a7 = (v17 + v19->pointAy[3].fX) * v19->pointAy[0].fY
    + (v16 + v19->pointAy[3].fY) * v19->pointAy[1].fY
    + (v18 + v19->pointAy[3].fZ) * v19->pointAy[2].fY;
  v51 = 0;
  v40 = *(float *)(a1 + 24) * tcos[*(_DWORD *)(a1 + 64) & 0x3FFF];
  if (numcars > 0) {
    v20 = 0;
    do {
      v21 = *(_DWORD *)(a1 + 32);
      TRAK_LEN = v7;
      if (v21 == v51 || (char)Car[v20].byUnk23 <= 0)
        goto LABEL_67;
      v22 = Car[v20].nCurrChunk - *(__int16 *)(a1 + 12);
      v53 = v22;
      if (v22 < 0)
        v53 = v22 + v7;
      if (v7 / 2 < v53)
        v53 -= v7;
      v23 = Car[v20].fMaxSpeed * tcos[Car[v20].iAngleIdx15 & 0x3FFF];
      TRAK_LEN = v7;
      v46 = v23;
      if (Car[v20].iUnk17 != 3
        || fabs((double)v53 / (v40 - v46)) >= control_c_variable_141
        || !linevalid(*(__int16 *)(a1 + 12), *(float *)(a1 + 4), Car[v20].pos.fY)) {
        goto LABEL_67;
      }
      v24 = TRAK_LEN;
      if (v53 <= 0) {
        if (v53 >= 0) {
          j = Car[v20].pos.fX - *(float *)a1;
        } else {
          nCurrChunk = Car[v20].nCurrChunk;
          v56 = -(localdata[nCurrChunk].fUnk13 - Car[v20].pos.fX);
          v29 = v56 - (localdata[*(__int16 *)(a1 + 12)].fUnk13 + *(float *)a1);
          for (i = 1; ; ++i) {
            ++nCurrChunk;
            j = v29;
            if (i >= (int)abs32(v53))
              break;
            if (nCurrChunk >= TRAK_LEN)
              nCurrChunk -= TRAK_LEN;
            v29 = j - control_c_variable_139 * localdata[nCurrChunk].fUnk13;
          }
          v24 = TRAK_LEN;
          if (j > 0.0)
            j = 0.0;
        }
      } else {
        v54 = localdata[*(__int16 *)(a1 + 12)].fUnk13 - *(float *)a1;
        v25 = *(__int16 *)(a1 + 12) + 1;
        v26 = 1;
        for (j = localdata[Car[v20].nCurrChunk].fUnk13 + Car[v20].pos.fX + v54; v26 < v53; j = v27) {
          if (v25 >= TRAK_LEN)
            v25 -= TRAK_LEN;
          v27 = control_c_variable_139 * localdata[v25].fUnk13 + j;
          ++v26;
          ++v25;
        }
        if (j < 0.0)
          j = 0.0;
      }
      v43 = control_c_variable_139 * CarBaseX;
      if (j < 0.0) {
        v57 = j + v43;
        v31 = 0;
        if (v57 > 0.0)
          v57 = 0.0;
      } else {
        v57 = j - v43;
        v31 = -1;
        if (v57 < 0.0)
          v57 = 0.0;
      }
      v32 = v40 - v46;
      if (fabs(v32) >= control_c_variable_142) {
        v45 = v32;
        v52 = v57 / (control_c_variable_143 * v45);
      } else {
        v52 = -10000.0;
      }
      TRAK_LEN = v24;
      if (fabs(v52) > control_c_variable_144)
        goto LABEL_67;
      if (v31) {
        if (v52 < 0.0) {
          if (v52 > (double)v50 && v50 < 0.0) {
            v42 = v51;
            v50 = v52;
          }
        } else if (v52 < (double)v50 || v50 < 0.0) {
          v42 = v51;
          v50 = v52;
        }
        goto LABEL_67;
      }
      if (v52 < 0.0) {
        if (v52 <= (double)v49 || v49 >= 0.0)
          goto LABEL_67;
      } else if (v52 >= (double)v49 && v49 >= 0.0) {
        goto LABEL_67;
      }
      v41 = v51;
      v49 = v52;
    LABEL_67:
      v7 = TRAK_LEN;
      ++v20;
      ++v51;
    } while (v51 < numcars);
  }
  if (*(_DWORD *)(a1 + 188)) {
    *a2 = v42;
    *a4 = v41;
    *a3 = v50;
    v33 = a5;
    result = LODWORD(v49);
  } else {
    *a2 = v41;
    *a4 = v42;
    *a3 = v49;
    v33 = a5;
    result = LODWORD(v50);
  }
  *v33 = result;
  TRAK_LEN = v7;
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00031870
double interpolatesteer(float a1, float a2, float a3, int a4, int a5)
{
  return 0.0;
  /*
  long double v5; // st7
  float v8; // [esp+Ch] [ebp+4h]

  v5 = fabs(a1);
  v8 = v5;
  if (v5 <= a2) {
    if (v8 < (double)a3)
      return *(float *)&a5;
    return (float)(((v8 - a3) * *(float *)&a4 - (v8 - a2) * *(float *)&a5) / (a2 - a3));
  } else {
    return *(float *)&a4;
  }*/
}

//-------------------------------------------------------------------------------------------------
//000318F0
double avoid(int a1, int a2, float a3, int a4, float a5, float a6, void *a7)
{
  return 0.0;/*
  int v10; // eax
  double v11; // st7
  int v13; // [esp+0h] [ebp-30h] BYREF
  int v14; // [esp+4h] [ebp-2Ch] BYREF
  float v15; // [esp+8h] [ebp-28h]
  float v16; // [esp+Ch] [ebp-24h]
  int v17; // [esp+10h] [ebp-20h]
  int v18; // [esp+14h] [ebp-1Ch]

  *a7 = 0;
  if (a2 != -1 && a3 < fabs(a5)) {
    *(float *)&v18 = CarBaseY + Car[a2].fUnk19 + control_c_variable_145 + Car[a2].pos.fY;
    *(float *)&v17 = -CarBaseY - Car[a2].fUnk19 + control_c_variable_146 + Car[a2].pos.fY;
    if (*(float *)&a4 < (double)*(float *)&v18 && *(float *)&a4 >(double) * (float *)&v17) {
      driverange((int)&Car[a2], (float *)&v13, (float *)&v14);
      v10 = a1 + Car[a2].iUnk10;
      v15 = (*(float *)&v13 + *(float *)&v14) * control_c_variable_147;
      if ((v10 & 1) != 0)
        v11 = Car[a2].pos.fY + control_c_variable_149;
      else
        v11 = Car[a2].pos.fY + control_c_variable_148;
      v16 = v11;
      if (v16 <= (double)v15) {
        if (*(float *)&v18 > (double)*(float *)&v13) {
          v18 = v13;
          if (a3 > 0.0
            && Car[a1].fMaxSpeed > (double)control_c_variable_150
            && Car[a1].fMaxSpeed > Car[a2].fMaxSpeed * tcos[Car[a2].iAngleIdx15] + control_c_variable_151) {
            *a7 = -1;
          }
        }
        if (*(float *)&a4 <= (double)*(float *)&v18)
          return (float)interpolatesteer(a3, a5, a6, a4, v18);
      } else {
        if (*(float *)&v17 < (double)*(float *)&v14) {
          v17 = v14;
          if (a3 > 0.0
            && Car[a1].fMaxSpeed > (double)control_c_variable_150
            && Car[a1].fMaxSpeed > Car[a2].fMaxSpeed * tcos[Car[a2].iAngleIdx15] + control_c_variable_151) {
            *a7 = -1;
          }
        }
        if (*(float *)&a4 >= (double)*(float *)&v17)
          return (float)interpolatesteer(a3, a5, a6, a4, v17);
      }
    }
  }
  return *(float *)&a4;*/
}

//-------------------------------------------------------------------------------------------------
//00031B40
double block(int a1, float a2, int a3, float a4, float a5)
{
  (void)(a1); (void)(a2); (void)(a3); (void)(a4); (void)(a5);
  return 0.0;
  /*
  if (a1 == -1)
    return *(float *)&a3;
  else
    return (float)interpolatesteer(a2, a4, a5, a3, LODWORD(Car_variable_1[77 * a1]));
    */
}

//-------------------------------------------------------------------------------------------------
//00031BA0
void autocar2(tCar *pCar)
{
  /*
  float *v2; // ebp
  int v3; // ebx
  double v4; // st7
  int v5; // edx
  __int16 v6; // fps
  double v7; // st7
  _BOOL1 v8; // c0
  char v9; // c2
  _BOOL1 v10; // c3
  int v11; // eax
  int v12; // edi
  int v13; // eax
  int v14; // edx
  int v15; // ebx
  int v16; // ecx
  int v17; // eax
  double v18; // st7
  double v19; // st7
  int v20; // eax
  int v21; // eax
  __int16 v22; // fps
  double v23; // st7
  _BOOL1 v24; // c0
  char v25; // c2
  _BOOL1 v26; // c3
  double v27; // st7
  __int16 v28; // fps
  _BOOL1 v29; // c0
  char v30; // c2
  _BOOL1 v31; // c3
  int v32; // eax
  __int16 v33; // fps
  _BOOL1 v34; // c0
  char v35; // c2
  _BOOL1 v36; // c3
  double v37; // st7
  int v38; // edi
  int v39; // edx
  int v40; // eax
  __int16 v41; // fps
  _BOOL1 v42; // c0
  char v43; // c2
  _BOOL1 v44; // c3
  double v45; // st7
  double v46; // st7
  int v47; // eax
  unsigned __int8 v48; // bl
  int v49; // ebx
  int v50; // edx
  int v51; // eax
  int v52; // ebx
  int v53; // eax
  int v54; // eax
  int v55; // eax
  int v56; // eax
  double v57; // st7
  int v58; // eax
  float v59; // eax
  int v60; // eax
  double v61; // st7
  long double v62; // st7
  int v63; // eax
  __int16 v64; // fps
  _BOOL1 v65; // c0
  char v66; // c2
  _BOOL1 v67; // c3
  double v68; // st7
  int v69; // eax
  double v70; // st7
  double v71; // st7
  double v72; // st7
  int v73; // eax
  int v74; // eax
  int v75; // eax
  double v76; // [esp+0h] [ebp-ACh]
  float v77; // [esp+8h] [ebp-A4h] BYREF
  float v78; // [esp+Ch] [ebp-A0h] BYREF
  int v79; // [esp+10h] [ebp-9Ch] BYREF
  int v80; // [esp+14h] [ebp-98h] BYREF
  int v81; // [esp+18h] [ebp-94h] BYREF
  float v82; // [esp+1Ch] [ebp-90h] BYREF
  int v83; // [esp+20h] [ebp-8Ch] BYREF
  int v84; // [esp+24h] [ebp-88h]
  float v85; // [esp+28h] [ebp-84h]
  float v86; // [esp+2Ch] [ebp-80h]
  float v87; // [esp+30h] [ebp-7Ch]
  float v88; // [esp+34h] [ebp-78h]
  float v89; // [esp+38h] [ebp-74h]
  float v90; // [esp+3Ch] [ebp-70h]
  float v91; // [esp+40h] [ebp-6Ch]
  float v92; // [esp+44h] [ebp-68h]
  float v93; // [esp+48h] [ebp-64h]
  float v94; // [esp+4Ch] [ebp-60h]
  float v95; // [esp+50h] [ebp-5Ch]
  float v96; // [esp+54h] [ebp-58h]
  float v97; // [esp+58h] [ebp-54h]
  float v98; // [esp+5Ch] [ebp-50h]
  float v99; // [esp+60h] [ebp-4Ch]
  float v100; // [esp+64h] [ebp-48h]
  int v101; // [esp+68h] [ebp-44h]
  int v102; // [esp+6Ch] [ebp-40h]
  int v103; // [esp+70h] [ebp-3Ch]
  float v104; // [esp+74h] [ebp-38h]
  int *v105; // [esp+78h] [ebp-34h]
  int v106; // [esp+7Ch] [ebp-30h]
  int v107; // [esp+80h] [ebp-2Ch]
  float v108; // [esp+84h] [ebp-28h]
  int v109; // [esp+88h] [ebp-24h]
  int v110; // [esp+8Ch] [ebp-20h]
  int v111; // [esp+90h] [ebp-1Ch]

  v83 = 0;
  v105 = &CarEngines[28 * *(unsigned __int8 *)(a1 + 102)];
  v2 = (float *)((char *)&CarStrategy + 40 * *(_DWORD *)(a1 + 32));
  v86 = *((float *)v105 + 3);
  v3 = *(_DWORD *)(a1 + 176) - 1;
  v104 = *(float *)(4 * *v105 + v105[2] - 4);
  *(_DWORD *)(a1 + 176) = v3;
  if (v3 >= 0)
    return;
  changestrategy(a1);
  changeline(a1);
  v5 = *(__int16 *)(a1 + 12);
  v4 = localdata_variable_15[32 * v5];
  _CHP(v5 << 7, v5);
  LOBYTE(v5) = HIBYTE(TrakColour_variable_5[12 * v5]);
  v107 = (int)v4;
  if ((v5 & 0x10) == 0) {
    if (!winner_mode) {
      HIWORD(v11) = HIWORD(level);
      v104 = v104 * levels[level] * control_c_variable_152;
      v7 = (double)v107;
      v8 = v7 < v104;
      v9 = 0;
      v10 = v7 == v104;
      LOWORD(v11) = v6;
      if (v7 > v104) {
        _CHP(v11, v5);
        v107 = (int)v104;
      }
    }
    v84 = 2 * *(unsigned __int8 *)(a1 + 130);
    v12 = 1000;
    if (*(float *)(a1 + 232) <= control_c_variable_153 - (double)v84)
      goto LABEL_18;
    v111 = -1;
    v13 = 0;
    if (numcars > 0) {
      v14 = 0;
      v15 = 0;
      do {
        if (human_control[v14]) {
          v16 = (unsigned __int8)Car_variable_32[v15];
          if (v16 < v12) {
            v111 = v13;
            v12 = v16;
          }
        }
        ++v14;
        ++v13;
        v15 += 308;
      } while (v13 < numcars);
    }
    v17 = *(char *)(a1 + 104) * TRAK_LEN
      + *(__int16 *)(a1 + 12)
      - (TRAK_LEN * Car_variable_24[308 * v111]
       + Car_variable_3[154 * v111]);
    v5 = 4 * level;
    if (v17 < 80) {
      if (v17 <= 20) {
      LABEL_18:
        if (*(_BYTE *)(a1 + 102) == 13) {
          v20 = *(unsigned __int8 *)(a1 + 130);
          if (v20 < v12) {
            v21 = v20 + 4;
            if (v21 >= v12) {
              v5 = 308 * v111;
              v23 = Car_variable_8[77 * v111];
              v24 = v23 < control_c_variable_155;
              v25 = 0;
              v26 = v23 == control_c_variable_155;
              LOWORD(v21) = v22;
              if (v23 <= control_c_variable_155) {
                v27 = Car_variable_8[77 * v111] + control_c_variable_156;
                _CHP(v21, v5);
                v107 = (int)v27;
              } else {
                v107 = 100;
              }
            }
          }
        }
        goto LABEL_24;
      }
      v84 = v17 - 20;
      v19 = (double)(v17 - 20) * mineff[level];
      v17 -= 80;
      v84 = v17;
      v18 = ((double)v17 - v19) * control_c_variable_154 * (double)v107;
    } else {
      v18 = (double)v107 * mineff[level];
    }
    _CHP(v17, v5);
    v107 = (int)v18;
    goto LABEL_18;
  }
LABEL_24:
  if (*(_DWORD *)(a1 + 188)) {
    v32 = *(__int16 *)(a1 + 20);
    v34 = tcos[v32] > 0.0;
    v35 = 0;
    v36 = 0.0 == tcos[v32];
    LOWORD(v32) = v33;
    if (v34)
      LABEL_28:
    v107 = 25;
  } else {
    v32 = *(__int16 *)(a1 + 20);
    v29 = tcos[v32] > 0.0;
    v30 = 0;
    v31 = 0.0 == tcos[v32];
    LOWORD(v32) = v28;
    if (!v29 && !v31)
      goto LABEL_28;
  }
  v37 = (double)v107 - *(float *)(a1 + 24);
  _CHP(v32, v5);
  v110 = (int)v37;
  v101 = (int)v37;
  findnearcars((float *)a1, (float *)&v79, &v78, (float *)&v81, &v77, &v82, &v80);
  v38 = *(_DWORD *)(a1 + 192);
  if (*(float *)(a1 + 28) >= (double)control_c_variable_157) {
    if (v81 == -1 || v77 < 0.0) {
      if (v79 != -1 && v78 >= 0.0) {
        if (Car_variable_9[77 * v79] < (double)control_c_variable_158 && !finished_car[v79])
          v38 = Car_variable_9[77 * v79] > 0.0
          && ((unsigned __int8)v81 & (*(_DWORD *)(a1 + 32) == 65534) & 0xFE) == 0
          && *(float *)(a1 + 28) >= (double)control_c_variable_159;
        if (human_control[v79] && ((cheat_mode & 2) != 0 || *(_BYTE *)(a1 + 102) == 13)) {
          v39 = 308 * v79;
          if (Car_variable_9[77 * v79] > 0.0) {
            HIWORD(v40) = HIWORD(v79);
            if (!finished_car[v79]) {
              v38 = 1;
              if (*(_BYTE *)(a1 + 102) == 13) {
                v42 = v78 < (double)control_c_variable_160;
                v43 = 0;
                v44 = v78 == control_c_variable_160;
                LOWORD(v40) = v41;
                if (v78 < (double)control_c_variable_160) {
                  v45 = Car_variable_8[77 * v79] + control_c_variable_156;
                  _CHP(v40, v39);
                  v107 = (int)v45;
                  v46 = v45 - *(float *)(a1 + 24);
                  _CHP(v47, v39);
                  v101 = (int)v46;
                }
              }
            }
          }
        }
      }
    } else {
      if (Car_variable_9[77 * v81] < (double)control_c_variable_158 && !finished_car[v81]) {
        if (Car_variable_9[77 * v81] <= 0.0
          || ((unsigned __int8)v81 & (*(_DWORD *)(a1 + 32) == 65534) & 0xFE) != 0
          || *(float *)(a1 + 28) < (double)control_c_variable_159) {
          v38 = 0;
        } else {
          v38 = 3;
        }
      }
      if (human_control[v81]
        && ((cheat_mode & 2) != 0 || *(_BYTE *)(a1 + 102) == 13)
        && Car_variable_9[77 * v81] > 0.0
        && !finished_car[v81]) {
        v38 = 3;
        v101 = 1;
      }
    }
  } else {
    *(_DWORD *)(a1 + 192) = 0;
  }
  if (v81 != -1 && v38 == 3 && Car_variable_40[308 * v81])
    v38 = 0;
  if (v79 != -1 && Car_variable_40[308 * v79] && v38 <= 3)
    v38 = 0;
  if (v79 != -1
    && *(_BYTE *)(a1 + 130) < 4u
    && *(unsigned __int8 *)(a1 + 130) - (unsigned __int8)Car_variable_32[308 * v79] > 2
    && !human_control[v79]) {
    v38 = 0;
  }
  if (v81 != -1) {
    v48 = *(_BYTE *)(a1 + 130);
    if (v48 < 4u && v48 - (unsigned __int8)Car_variable_32[308 * v79] > 2 && !human_control[v79])
      v38 = 0;
  }
  if (SLOBYTE(TrakColour_variable_5[12 * *(__int16 *)(a1 + 12)]) >= 0)
    v110 = v101;
  else
    v38 = 4;
  if (winner_mode)
    v38 = 4;
  v49 = *(__int16 *)(a1 + 12);
  v102 = *((_DWORD *)&TrakColour_variable_3 + 6 * v49) & 0x1000000;
  v50 = NoOfLaps;
  v103 = 0;
  if (*(char *)(a1 + 104) == NoOfLaps && TRAK_LEN - v49 < 200)
    v103 = -1;
  if (death_race) {
    v50 = 0;
    v103 = -1;
    v102 = 0;
  }
  if (!v102 || *(float *)(a1 + 28) >= (double)control_c_variable_161 || v103) {
    *(_DWORD *)(a1 + 208) = -1;
  } else if (*(_DWORD *)(a1 + 208) == -1) {
    v51 = rand();
    v52 = 0;
    v50 = numcars;
    v109 = stops[(v51 * numstops - (__CFSHL__((v51 * numstops) >> 31, 15) + ((v51 * numstops) >> 31 << 15))) >> 15];
    if (numcars > 0) {
      v53 = 0;
      v50 = 308 * numcars;
      do {
        if (Car_variable_49[v53 / 4u] == v109)
          v52 = -1;
        v53 += 308;
      } while (v53 < v50);
    }
    if (!v52)
      *(_DWORD *)(a1 + 208) = v109;
  }
  if (v102 && !*(_DWORD *)(a1 + 160) && !v103) {
    v38 = *(float *)(a1 + 28) >= (double)control_c_variable_161 ? 0 : 5;
    if (*(float *)(a1 + 28) < (double)control_c_variable_162)
      v38 = 5;
  }
  if (*(_BYTE *)(a1 + 184))
    v38 = 5;
  if (v38 == 5) {
    v54 = *(__int16 *)(a1 + 12);
    if (v54 != -1) {
      if (v102) {
        v55 = v54 - 1;
        if (v55 < 0)
          v55 = TRAK_LEN - 1;
        if (!*(_BYTE *)(a1 + 244)) {
          v50 = v55;
          if ((TrakColour_variable_5[12 * v55] & 0x100) == 0) {
            *(_BYTE *)(a1 + 244) = -1;
            v56 = player_type;
            *(_WORD *)(a1 + 238) = 1080;
            if (v56 != 2) {
              v50 = cheat_mode;
              if ((cheat_mode & 0x4000) == 0 && (__int16)player1_car != *(_DWORD *)(a1 + 32)) {
                v50 = 308 * (__int16)player1_car;
                if (*(_BYTE *)(a1 + 102) == Car_variable_22[v50] && *(_BYTE *)(a1 + 102) <= 7u) {
                  v50 = readsample;
                  if (readsample == writesample && lastsample < -18) {
                    speechsample(*(unsigned __int8 *)(a1 + 102) + 71, 20000, 18, (__int16)player1_car + 17920);
                    v50 = 20000;
                    speechsample(70, 20000, 0, (__int16)player1_car);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  switch (v38) {
    case 0:
      if (v81 != -1 && v77 >= 0.0)
        goto LABEL_175;
      if (v79 != *(_DWORD *)(a1 + 92))
        goto LABEL_154;
      goto LABEL_178;
    case 1:
      if (v81 != -1 && v77 >= 0.0)
        goto LABEL_175;
      if (v79 == *(_DWORD *)(a1 + 92) && v78 < 0.0)
        goto LABEL_178;
      LOBYTE(v50) = *(_BYTE *)(a1 + 102);
      if ((_BYTE)v50 == Car_variable_22[308 * v79])
        goto LABEL_154;
      *(_DWORD *)(a1 + 92) = -1;
      v87 = v2[5];
      v94 = v2[6];
      if (v79 == -1)
        v95 = *(float *)&v80;
      else
        v95 = interpolatesteer(v78, v87, v94, v80, LODWORD(Car_variable_1[77 * v79]));
      v59 = v95;
      goto LABEL_156;
    case 2:
      if (v81 == -1 || v77 < 0.0) {
        if (v79 == *(_DWORD *)(a1 + 92) && v78 < 0.0) {
        LABEL_178:
          v50 = v79;
          v108 = avoid(*(_DWORD *)(a1 + 32), v79, v78, v80, v2[7], v2[8], &v83);
        } else {
          LOBYTE(v50) = *(_BYTE *)(a1 + 102);
          if ((_BYTE)v50 == Car_variable_22[308 * v79]) {
          LABEL_154:
            *(_DWORD *)(a1 + 92) = -1;
            goto LABEL_155;
          }
          *(_DWORD *)(a1 + 92) = -1;
          v92 = v2[5];
          v90 = v2[6];
          if (v79 == -1)
            v99 = *(float *)&v80;
          else
            v99 = interpolatesteer(v78, v92, v90, v80, LODWORD(Car_variable_1[77 * v79]));
          v50 = 308 * v79;
          v62 = *(float *)(a1 + 4) - Car_variable_1[77 * v79];
          HIWORD(v63) = HIWORD(v99);
          v108 = v99;
          if (*(float *)&CarBaseY * control_c_variable_163 + control_c_variable_165 > fabs(v62)) {
            v65 = v78 > 0.0;
            v66 = 0;
            v67 = 0.0 == v78;
            LOWORD(v63) = v64;
            if (v78 > 0.0) {
              v68 = Car_variable_8[77 * v79] * control_c_variable_166;
              _CHP(v63, v50);
              v110 = (int)v68;
              if ((int)v68 < 80)
                v110 = 80;
              v69 = v110;
              if (v110 > v107)
                v110 = v107;
              v70 = (double)v110 - *(float *)(a1 + 24);
              _CHP(v69, v50);
              v110 = (int)v70;
            }
          }
        }
      } else {
      LABEL_175:
        v50 = v81;
        v61 = avoid(*(_DWORD *)(a1 + 32), v81, v77, v80, v2[7], v2[8], &v83);
        *(_DWORD *)(a1 + 92) = v81;
        v108 = v61;
      }
      break;
    case 3:
      *(_DWORD *)(a1 + 92) = -1;
      if (v81 == -1
        || v77 < 0.0
        || v77 >(double)v78 && v78 >= 0.0
        || (LOBYTE(v50) = *(_BYTE *)(a1 + 102), (_BYTE)v50 == Car_variable_22[308 * v81])) {
        if (v79 == -1
          || v78 < 0.0
          || v78 >(double)v77 && v77 >= 0.0
          || (LOBYTE(v50) = *(_BYTE *)(a1 + 102), (_BYTE)v50 == Car_variable_22[308 * v79])) {
        LABEL_155:
          v59 = *(float *)&v80;
        } else {
          v89 = v2[5];
          v50 = *((_DWORD *)v2 + 6);
          v96 = interpolatesteer(v78, v89, *(float *)&v50, v80, LODWORD(Car_variable_1[77 * v79]));
          v59 = v96;
        }
      LABEL_156:
        v108 = v59;
      } else {
        v91 = v2[5];
        v50 = *((_DWORD *)v2 + 6);
        v98 = interpolatesteer(v77, v91, *(float *)&v50, v80, LODWORD(Car_variable_1[77 * v81]));
        v108 = v98;
        v110 = 1;
      }
      break;
    case 4:
      v108 = *(float *)&v80;
      *(_DWORD *)(a1 + 92) = -1;
      break;
    case 5:
      if (v81 == -1 || v77 < 0.0) {
        if (v79 == *(_DWORD *)(a1 + 92)) {
          v108 = avoid(*(_DWORD *)(a1 + 32), v79, v78, v80, v2[7], v2[8], &v83);
        } else {
          *(_DWORD *)(a1 + 92) = -1;
          v108 = *(float *)&v80;
        }
      } else {
        v57 = avoid(*(_DWORD *)(a1 + 32), v81, v77, v80, v2[7], v2[8], &v83);
        *(_DWORD *)(a1 + 92) = v81;
        v108 = v57;
      }
      v58 = *(_DWORD *)(a1 + 208);
      if (v58 != -1) {
        v106 = v58 - *(__int16 *)(a1 + 12);
        if (v106 < 0)
          v106 += TRAK_LEN;
        if (TRAK_LEN / 2 < v106)
          v106 -= TRAK_LEN;
        v100 = *(float *)(a1 + 24) * tcos[*(_DWORD *)(a1 + 64) & 0x3FFF];
        v93 = localdata_variable_4[32 * *(__int16 *)(a1 + 12)] * control_c_variable_163 * (double)v106;
        if (v106 < 0 || fabs(v93 / v100) < v86 * control_c_variable_164 * v100 / v104)
          v83 = -1;
      }
      if ((*(_DWORD *)(a1 + 24) & 0x7FFFFFFF) == 0)
        *(_BYTE *)(a1 + 184) = -1;
      v50 = 24 * *(__int16 *)(a1 + 12);
      if ((*((_BYTE *)&TrakColour_variable_1[2 * *(_DWORD *)(a1 + 212)] + v50 + 1) & 2) == 0
        && *(float *)(a1 + 24) < (double)control_c_variable_159) {
        v50 = 0;
        v83 = 0;
      }
      break;
    default:
      break;
  }
  if (*(_BYTE *)(a1 + 184))
    v83 = -1;
  if (v83)
    v110 = -1;
  *(float *)&v84 = v82 - *(float *)a1;
  v97 = v108 - *(float *)(a1 + 4);
  v85 = *(float *)&v84;
  v88 = v97;
  if ((v84 & 0x7FFFFFFF) != 0 || (LODWORD(v97) & 0x7FFFFFFF) != 0) {
    v71 = v85;
    IF_DATAN2(v85);
    v72 = v71 * control_c_variable_167 / control_c_variable_168;
    _CHP(v73, v50);
    v84 = (int)v72;
    v60 = (int)v72 & 0x3FFF;
  } else {
    LOWORD(v60) = 0;
  }
  v74 = ((_WORD)v60 - *(_WORD *)(a1 + 20)) & 0x3FFF;
  if (v74 > 0x2000)
    v74 -= 0x4000;
  if (v74 < -v105[23])
    v74 = -v105[23];
  if (v74 > v105[23])
    v74 = v105[23];
  *(_DWORD *)(a1 + 76) = v74;
  if (*(char *)(a1 + 128) == -1) {
    v76 = *(float *)(a1 + 120);
    if (v76 >= control_c_variable_169) {
      if (v76 < control_c_variable_170) {
        v75 = rand();
        if ((72 * v75 - (__CFSHL__((72 * v75) >> 31, 15) + ((72 * v75) >> 31 << 15))) >> 15) {
          v110 = *(char *)(a1 + 242);
        } else {
          v110 = -*(char *)(a1 + 242);
          *(_BYTE *)(a1 + 242) = v110;
        }
      } else {
        *(_BYTE *)(a1 + 242) = -1;
        v110 = -1;
      }
    } else {
      *(_BYTE *)(a1 + 242) = 1;
      v110 = 1;
    }
  }
  if (v110 > 0 && (*(_DWORD *)(a1 + 28) & 0x7FFFFFFF) == 0)
    v110 = -1;
  if (champ_mode && !champ_go[*(_DWORD *)(a1 + 32)])
    v110 = -1;
  if (v110 <= 0) {
    if (v110 >= 0)
      FreeWheel(a1);
    else
      Decelerate(a1);
  } else {
    Accelerate(a1);
  }*/
}

//-------------------------------------------------------------------------------------------------
//00032BF0
void changestrategy(int a1)
{
  (void)(a1);
  /*
  int v2; // eax
  char *v3; // ecx
  __int16 v4; // fps
  double v5; // st7
  int v6; // edi
  _BOOL1 v7; // c0
  char v8; // c2
  _BOOL1 v9; // c3
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // ebx
  int v14; // edx
  int v15; // ebp
  int v16; // eax
  int v17; // eax
  int v18; // eax
  unsigned int v19; // ebx
  int v20; // ebx
  int v21; // eax
  unsigned __int8 v22; // dl
  int v23; // eax
  unsigned __int8 v24; // bl

  v2 = 40 * *(_DWORD *)(a1 + 32);
  v3 = (char *)&CarStrategy + v2;
  if (*(_WORD *)(a1 + 238))
    return;
  v5 = *(float *)(a1 + 232);
  v6 = *(_DWORD *)(a1 + 192);
  v7 = v5 < control_c_variable_171;
  v8 = 0;
  v9 = v5 == control_c_variable_171;
  LOWORD(v2) = v4;
  if (v5 > control_c_variable_171) {
    v10 = rand(v2);
    v11 = (800 * v10 - (__CFSHL__((800 * v10) >> 31, 15) + ((800 * v10) >> 31 << 15))) >> 15;
    if (v11 == 100) {
      v12 = rand(100);
      v13 = 0;
      v14 = (100 * v12 - (__CFSHL__((100 * v12) >> 31, 15) + ((100 * v12) >> 31 << 15))) >> 15;
      v11 = (int)v3;
      if (v14 >= *(_DWORD *)v3) {
        do {
          v15 = *(_DWORD *)v11;
          v11 += 4;
          v14 -= v15;
          ++v13;
        } while (v14 >= *(_DWORD *)v11);
      }
      if (*(_BYTE *)(a1 + 130) < 4u && v13 == 2)
        v13 = 1;
      *(_DWORD *)(a1 + 192) = v13;
      if (v13) {
        v16 = rand(v11);
        v11 = (100 * v16 - (__CFSHL__((100 * v16) >> 31, 15) + ((100 * v16) >> 31 << 15))) >> 15;
        if (v11 < flipst[level])
          *(_DWORD *)(a1 + 192) = 0;
      }
      if ((cheat_mode & 2) != 0)
        *(_DWORD *)(a1 + 192) = 0;
    }
    v17 = rand(v11);
    if ((720 * v17 - (__CFSHL__((720 * v17) >> 31, 15) + ((720 * v17) >> 31 << 15))) >> 15 != 250)
      goto LABEL_39;
    v18 = cheat_mode;
    if ((cheat_mode & 2) != 0 || level < 4) {
      v19 = *(unsigned __int8 *)(a1 + 130);
      if (v19 >= 7) {
        if ((cheat_mode & 2) != 0) {
          v20 = 50 * v19 - 250;
        } else {
          v18 = (int)(*((_DWORD *)v3 + 4) * (v19 - level)) / 2;
          v20 = v18 + v19 - level;
        }
      } else {
        v20 = -1;
      }
      v21 = rand(v18);
      if ((1000 * v21 - (__CFSHL__((1000 * v21) >> 31, 15) + ((1000 * v21) >> 31 << 15))) >> 15 < v20) {
        if (player_type != 2
          && (cheat_mode & 0x4000) == 0
          && !*(_DWORD *)(a1 + 188)
          && *(_BYTE *)(a1 + 102) == Car_variable_22[308 * (__int16)player1_car]) {
          v22 = *(_BYTE *)(a1 + 102);
          if (v22 <= 7u) {
            speechsample(v22 + 71, 20000, 18, (__int16)player1_car + 17664);
            speechsample(69, 20000, 0, (__int16)player1_car);
          }
        }
        *(_DWORD *)(a1 + 188) = -1;
        goto LABEL_39;
      }
    } else {
      v23 = rand(cheat_mode);
      if ((1000 * v23 - (__CFSHL__((1000 * v23) >> 31, 15) + ((1000 * v23) >> 31 << 15))) >> 15 < *((_DWORD *)v3 + 4)) {
        if (player_type != 2
          && (cheat_mode & 0x4000) == 0
          && !*(_DWORD *)(a1 + 188)
          && *(_BYTE *)(a1 + 102) == Car_variable_22[308 * (__int16)player1_car]
          && *(_BYTE *)(a1 + 102) <= 7u) {
          speechsample(*(unsigned __int8 *)(a1 + 102) + 71, 20000, 18, (__int16)player1_car + 17664);
          speechsample(69, 20000, 0, (__int16)player1_car);
        }
        *(_DWORD *)(a1 + 188) = -1;
        goto LABEL_39;
      }
    }
    *(_DWORD *)(a1 + 188) = 0;
  LABEL_39:
    if (winner_mode)
      *(_DWORD *)(a1 + 188) = 0;
  }
  if (v6 != *(_DWORD *)(a1 + 192)) {
    if (player_type != 2
      && (cheat_mode & 0x4000) == 0
      && *(_BYTE *)(a1 + 102) == Car_variable_22[308 * (__int16)player1_car]) {
      v24 = *(_BYTE *)(a1 + 102);
      if (v24 <= 7u) {
        speechsample(v24 + 71, 20000, 18, ((*(_DWORD *)(a1 + 192) + 61) << 8) + (__int16)player1_car);
        speechsample(*(_DWORD *)(a1 + 192) + 61, 20000, 0, (__int16)player1_car);
      }
    }
    *(_WORD *)(a1 + 238) = 1080;
  }*/
}

//-------------------------------------------------------------------------------------------------
//00032FB0
int getangle(float fX, float fY)
{
  double dAngle; // st7

  // If floats are both zero, return 0
  // Masking off most significant bit so -0 == 0
  // Did this used to be necessary? It doesn't
  // seem to make a difference now.
  //if ((LODWORD(fX) & 0x7FFFFFFF) == 0 && (LODWORD(fY) & 0x7FFFFFFF) == 0)
  if (fX == 0 && fY == 0)
    return 0;

  // IF_DATAN2 is atan2 that returns a double
  dAngle = atan2(fY, fX) * 16384.0 / 6.28318530718;

  // round to integer?
  //_CHP();
  dAngle = round(dAngle);

  // return value is used as an index into tsin/tcos/ptan lookup tables each with 16384 elements 
  // masking off all but the 14 least significant bits ensures this value maxes out at 16383
  return (int)dAngle & 0x3FFF;
}

//-------------------------------------------------------------------------------------------------
//00033000
void landontrack(int a1)
{
  (void)(a1);
  /*
  float *v2; // ebp
  int v3; // eax
  float *v4; // esi
  float *v5; // ecx
  float *v6; // ebx
  double v7; // st7
  double v8; // st5
  double v9; // rt0
  bool v10; // eax
  int v11; // edx
  float v12; // eax
  double v13; // st7
  int v14; // ecx
  double v15; // st7
  __int16 v16; // fps
  _BOOL1 v17; // c0
  char v18; // c2
  _BOOL1 v19; // c3
  double v20; // st7
  double v21; // st7
  double v22; // st5
  double v23; // st6
  double v24; // st6
  double v25; // st7
  double v26; // st7
  int v27; // edx
  int v28; // eax
  double v29; // st7
  double v30; // st7
  int v31; // eax
  bool v32; // eax
  int v33; // edx
  int v34; // eax
  double v35; // st7
  double v36; // st7
  __int16 v37; // fps
  _BOOL1 v38; // c0
  char v39; // c2
  _BOOL1 v40; // c3
  double v41; // st7
  double v42; // st7
  double v43; // st5
  double v44; // st6
  double v45; // st6
  double v46; // st7
  double v47; // st7
  int v48; // ecx
  double v49; // st7
  double v50; // st7
  int v51; // eax
  long double v52; // st7
  double v53; // st7
  int v54; // edx
  __int64 v55; // rax
  int v56; // eax
  __int16 v57; // fps
  double v58; // st7
  _BOOL1 v59; // c0
  char v60; // c2
  _BOOL1 v61; // c3
  __int16 v62; // fps
  double v63; // st7
  _BOOL1 v64; // c0
  char v65; // c2
  _BOOL1 v66; // c3
  int v67; // edx
  double v68; // st7
  double v69; // st7
  int v70; // eax
  int v71; // eax
  double v72; // st7
  double v73; // st7
  int v74; // eax
  int v75; // eax
  __int16 v76; // fps
  _BOOL1 v77; // c0
  char v78; // c2
  _BOOL1 v79; // c3
  double v80; // st7
  int v81; // eax
  double v82; // st7
  int v83; // edx
  double v84; // st7
  double v85; // st5
  double v86; // rt2
  int v87; // edx
  int v88; // eax
  double v89; // st7
  double v90; // st5
  double v91; // st4
  double v92; // st7
  double v93; // st5
  double v94; // st4
  long double v95; // st7
  double v96; // st7
  double v97; // st7
  __int16 v98; // fps
  _BOOL1 v99; // c0
  char v100; // c2
  _BOOL1 v101; // c3
  double v102; // st7
  double v103; // st7
  double v104; // st5
  double v105; // st6
  double v106; // st7
  double v107; // st5
  double v108; // st6
  double v109; // st7
  int v110; // ecx
  int v111; // eax
  double v112; // st7
  double v113; // st7
  int v114; // eax
  double v115; // st7
  double v116; // st5
  double v117; // st4
  long double v118; // st7
  float *v119; // edx
  double v120; // st7
  double v121; // st7
  __int16 v122; // fps
  _BOOL1 v123; // c0
  char v124; // c2
  _BOOL1 v125; // c3
  double v126; // st7
  double v127; // st7
  double v128; // st5
  double v129; // st6
  double v130; // st7
  double v131; // st5
  double v132; // st6
  double v133; // st7
  int v134; // ecx
  double v135; // st7
  double v136; // st7
  int v137; // eax
  double v138; // st7
  double v139; // st5
  double v140; // rt0
  float *v141; // edx
  int v142; // eax
  double v143; // st7
  double v144; // st5
  double v145; // st4
  double v146; // st7
  double v147; // st5
  double v148; // st4
  long double v149; // st7
  float *v150; // edx
  double v151; // st7
  __int16 v152; // fps
  _BOOL1 v153; // c0
  char v154; // c2
  _BOOL1 v155; // c3
  double v156; // st7
  double v157; // st7
  double v158; // st5
  double v159; // st6
  double v160; // st7
  double v161; // st5
  double v162; // st6
  double v163; // st7
  int v164; // ebx
  double v165; // st7
  double v166; // st7
  int v167; // eax
  int v168; // eax
  double v169; // st7
  double v170; // st5
  double v171; // st4
  long double v172; // st7
  double v173; // st7
  __int16 v174; // fps
  _BOOL1 v175; // c0
  char v176; // c2
  _BOOL1 v177; // c3
  double v178; // st7
  double v179; // st7
  double v180; // st5
  double v181; // st6
  double v182; // st7
  double v183; // st5
  double v184; // st6
  double v185; // st7
  int v186; // edx
  double v187; // st7
  double v188; // st7
  int v189; // eax
  long double v190; // st7
  float v191; // [esp+0h] [ebp-1ECh]
  float v192; // [esp+0h] [ebp-1ECh]
  float v193; // [esp+0h] [ebp-1ECh]
  float v194; // [esp+0h] [ebp-1ECh]
  float v195; // [esp+0h] [ebp-1ECh]
  float v196; // [esp+0h] [ebp-1ECh]
  float v197; // [esp+0h] [ebp-1ECh]
  float v198; // [esp+0h] [ebp-1ECh]
  float v199; // [esp+4h] [ebp-1E8h] BYREF
  float v200; // [esp+8h] [ebp-1E4h]
  float v201; // [esp+Ch] [ebp-1E0h]
  float v202; // [esp+10h] [ebp-1DCh]
  float v203; // [esp+14h] [ebp-1D8h]
  float v204; // [esp+18h] [ebp-1D4h]
  float v205; // [esp+1Ch] [ebp-1D0h]
  float v206; // [esp+20h] [ebp-1CCh]
  float v207; // [esp+24h] [ebp-1C8h]
  float v208; // [esp+28h] [ebp-1C4h]
  float v209; // [esp+2Ch] [ebp-1C0h]
  float v210; // [esp+30h] [ebp-1BCh]
  int v211; // [esp+84h] [ebp-168h] BYREF
  int v212; // [esp+88h] [ebp-164h] BYREF
  int v213; // [esp+8Ch] [ebp-160h] BYREF
  int v214; // [esp+90h] [ebp-15Ch] BYREF
  float v215; // [esp+94h] [ebp-158h]
  float v216; // [esp+98h] [ebp-154h]
  float v217; // [esp+9Ch] [ebp-150h]
  int v218; // [esp+A0h] [ebp-14Ch]
  int v219; // [esp+A4h] [ebp-148h]
  float v220; // [esp+A8h] [ebp-144h]
  float v221; // [esp+ACh] [ebp-140h]
  float v222; // [esp+B0h] [ebp-13Ch]
  float v223; // [esp+B4h] [ebp-138h]
  float v224; // [esp+B8h] [ebp-134h]
  int v225; // [esp+BCh] [ebp-130h]
  float v226; // [esp+C0h] [ebp-12Ch]
  int v227; // [esp+C4h] [ebp-128h]
  float v228; // [esp+C8h] [ebp-124h]
  float v229; // [esp+CCh] [ebp-120h]
  float v230; // [esp+D0h] [ebp-11Ch]
  float v231; // [esp+D4h] [ebp-118h]
  float v232; // [esp+D8h] [ebp-114h]
  float v233; // [esp+DCh] [ebp-110h]
  int v234; // [esp+E0h] [ebp-10Ch]
  float v235; // [esp+E4h] [ebp-108h]
  float v236; // [esp+E8h] [ebp-104h]
  float v237; // [esp+ECh] [ebp-100h]
  float v238; // [esp+F0h] [ebp-FCh]
  float v239; // [esp+F4h] [ebp-F8h]
  float v240; // [esp+F8h] [ebp-F4h]
  float v241; // [esp+FCh] [ebp-F0h]
  int v242; // [esp+100h] [ebp-ECh]
  float v243; // [esp+104h] [ebp-E8h]
  float v244; // [esp+108h] [ebp-E4h]
  float v245; // [esp+10Ch] [ebp-E0h]
  int v246; // [esp+110h] [ebp-DCh]
  float v247; // [esp+114h] [ebp-D8h]
  int v248; // [esp+118h] [ebp-D4h]
  int v249; // [esp+11Ch] [ebp-D0h]
  float v250; // [esp+120h] [ebp-CCh]
  float v251; // [esp+124h] [ebp-C8h]
  int v252; // [esp+128h] [ebp-C4h]
  float v253; // [esp+12Ch] [ebp-C0h]
  float v254; // [esp+130h] [ebp-BCh]
  float v255; // [esp+134h] [ebp-B8h]
  float v256; // [esp+138h] [ebp-B4h]
  float v257; // [esp+13Ch] [ebp-B0h]
  float v258; // [esp+140h] [ebp-ACh]
  float v259; // [esp+144h] [ebp-A8h]
  float v260; // [esp+148h] [ebp-A4h]
  float v261; // [esp+14Ch] [ebp-A0h]
  float v262; // [esp+150h] [ebp-9Ch]
  float v263; // [esp+154h] [ebp-98h]
  float v264; // [esp+158h] [ebp-94h]
  float v265; // [esp+15Ch] [ebp-90h]
  float v266; // [esp+160h] [ebp-8Ch]
  float v267; // [esp+164h] [ebp-88h]
  float v268; // [esp+168h] [ebp-84h]
  float v269; // [esp+16Ch] [ebp-80h]
  float v270; // [esp+170h] [ebp-7Ch]
  float v271; // [esp+174h] [ebp-78h]
  float v272; // [esp+178h] [ebp-74h]
  float v273; // [esp+17Ch] [ebp-70h]
  float v274; // [esp+180h] [ebp-6Ch]
  float v275; // [esp+184h] [ebp-68h]
  float v276; // [esp+188h] [ebp-64h]
  float v277; // [esp+18Ch] [ebp-60h]
  float v278; // [esp+190h] [ebp-5Ch]
  float v279; // [esp+194h] [ebp-58h]
  float v280; // [esp+198h] [ebp-54h]
  float v281; // [esp+19Ch] [ebp-50h]
  float v282; // [esp+1A0h] [ebp-4Ch]
  float v283; // [esp+1A4h] [ebp-48h]
  float v284; // [esp+1A8h] [ebp-44h]
  float v285; // [esp+1ACh] [ebp-40h]
  int v286; // [esp+1B0h] [ebp-3Ch]
  float v287; // [esp+1B4h] [ebp-38h]
  float v288; // [esp+1B8h] [ebp-34h]
  float v289; // [esp+1BCh] [ebp-30h]
  float v290; // [esp+1C0h] [ebp-2Ch]
  int v291; // [esp+1C4h] [ebp-28h]
  float v292; // [esp+1C8h] [ebp-24h]
  int v293; // [esp+1CCh] [ebp-20h]
  int v294; // [esp+1D0h] [ebp-1Ch]

  v217 = *(float *)(a1 + 52);
  v226 = *(float *)(a1 + 56);
  v292 = *(float *)(a1 + 60);
  v254 = *(float *)a1;
  v259 = *(float *)(a1 + 4);
  v253 = *(float *)(a1 + 8);
  findnearsection(a1, &v213);
  if (v213 == -1)
    v286 = *(_DWORD *)(a1 + 216);
  else
    v286 = v213;
  v2 = (float *)&TrackInfo[9 * v286];
  v3 = v286 + 1;
  v4 = (float *)((char *)&localdata + 128 * v286);
  if (v286 + 1 >= TRAK_LEN)
    v3 = 0;
  v5 = (float *)&TrackInfo[9 * v3];
  v6 = (float *)((char *)&localdata + 128 * v3);
  if (GroundColour_variable_4[5 * v286] >= 0)
    calculateseparatedcoordinatesystem(v286, &v199);
  v7 = v259 + v4[10];
  v8 = v254 + v4[9];
  v9 = v253 + v4[11];
  v287 = v4[3] * v7 + *v4 * v8 + v4[6] * v9;
  v289 = v4[1] * v8 + v4[4] * v7 + v4[7] * v9;
  v290 = v7 * v4[5] + v8 * v4[2] + v9 * v4[8];
  v244 = (v217 + v4[9]) * v4[2] + (v226 + v4[10]) * v4[5] + (v292 + v4[11]) * v4[8];
  v281 = v4[3] * *(float *)(a1 + 44) + *v4 * *(float *)(a1 + 40) + v4[6] * *(float *)(a1 + 48);
  v288 = v4[1] * *(float *)(a1 + 40) + v4[4] * *(float *)(a1 + 44) + v4[7] * *(float *)(a1 + 48);
  v280 = v4[2] * *(float *)(a1 + 40) + v4[5] * *(float *)(a1 + 44) + v4[8] * *(float *)(a1 + 48);
  if (v289 < 0.0) {
    if (TrakColour_variable_11[6 * v286]) {
      v277 = v2[8];
      if (v277 < 0.0)
        v32 = v290 >= (double)v277 && v290 <= 0.0;
      else
        v32 = v290 <= (double)v277 && v290 >= 0.0;
      if (v32 && v277 > 0.0) {
        v33 = v286;
        v34 = 3 * v286;
        v35 = TrakColour_variable_11[6 * v286] < 0 ? -v4[13] : -v4[13] - v2[2];
        v255 = v35;
        if (v289 - *(float *)&CarBaseY <= v255) {
          if (v288 < 0.0) {
            if (death_race)
              v36 = -v288 * control_c_variable_174 * control_c_variable_175;
            else
              v36 = -v288 * control_c_variable_174;
            v192 = v36;
            v34 = dodamage(v192);
            v33 = -*(_DWORD *)(a1 + 200);
            HIBYTE(v288) ^= 0x80u;
            *(_DWORD *)(a1 + 200) = v33;
          }
          if (v288 < (double)control_c_variable_176)
            v288 = 40.0;
          v38 = v288 < (double)control_c_variable_176;
          v39 = 0;
          v40 = v288 == control_c_variable_176;
          LOWORD(v34) = v37;
          if (v288 > (double)control_c_variable_176 && !*(_BYTE *)(a1 + 306)) {
            v41 = v288 * control_c_variable_177 * control_c_variable_178;
            _CHP(v34, v33);
            v291 = (int)v41;
            v33 = *(_DWORD *)(a1 + 32);
            sfxpend(12, v33, (int)v41);
            *(_BYTE *)(a1 + 306) = 9;
          }
          v42 = v288;
          v43 = v281;
          v44 = v280;
          *(float *)(a1 + 40) = v4[1] * v288 + *v4 * v281 + v4[2] * v280;
          *(float *)(a1 + 44) = v4[3] * v43 + v4[4] * v42 + v4[5] * v44;
          *(float *)(a1 + 48) = v42 * v4[7] + v43 * v4[6] + v44 * v4[8];
          v289 = v255 + *(float *)&CarBaseY;
          v45 = v287;
          v46 = v290;
          *(float *)a1 = v4[1] * v289 + *v4 * v287 + v4[2] * v290 - v4[9];
          *(float *)(a1 + 4) = v4[3] * v45 + v4[4] * v289 + v4[5] * v46 - v4[10];
          v47 = v46 * v4[8] + v45 * v4[6] + v4[7] * v289 - v4[11];
          v291 = *(int *)(a1 + 40);
          v242 = *(_DWORD *)(a1 + 44);
          v216 = *(float *)&v291;
          v48 = v291;
          v219 = v242;
          *(float *)(a1 + 8) = v47;
          if ((v48 & 0x7FFFFFFF) != 0 || (v242 & 0x7FFFFFFF) != 0) {
            v49 = v216;
            IF_DATAN2(v216);
            v50 = v49 * control_c_variable_179 / control_c_variable_180;
            _CHP(v51, v33);
            v291 = (int)v50;
            v28 = (int)v50 & 0x3FFF;
          } else {
            v28 = 0;
          }
          goto LABEL_69;
        }
      }
    }
  } else if (TrakColour_variable_10[6 * v286]) {
    v276 = v2[8];
    if (v276 < 0.0)
      v10 = v290 >= (double)v276 && v290 <= 0.0;
    else
      v10 = v290 <= (double)v276 && v290 >= 0.0;
    if (v10 && v276 > 0.0) {
      v11 = v286;
      LODWORD(v12) = 3 * v286;
      if (TrakColour_variable_10[6 * v286] < 0) {
        v238 = v4[13];
        v12 = v6[13];
        v231 = v12;
      } else {
        v238 = v4[13] + *v2;
        v231 = v6[13] + *v5;
      }
      v251 = ((v287 + v4[12]) * v231 - (v287 - v4[12]) * v238) / (v4[12] * control_c_variable_181);
      if (v289 + *(float *)&CarBaseY >= v251) {
        if (v288 > 0.0) {
          if (death_race)
            v13 = v288 * control_c_variable_182 * control_c_variable_175;
          else
            v13 = v288 * control_c_variable_182;
          v191 = v13;
          v12 = COERCE_FLOAT(dodamage(v191));
          BYTE1(v11) = HIBYTE(v288) ^ 0x80;
          v14 = -*(_DWORD *)(a1 + 200);
          HIBYTE(v288) ^= 0x80u;
          *(_DWORD *)(a1 + 200) = v14;
        }
        if (v288 > (double)control_c_variable_183)
          v288 = -40.0;
        v15 = -v288;
        v236 = v15;
        v17 = v15 < control_c_variable_176;
        v18 = 0;
        v19 = v15 == control_c_variable_176;
        LOWORD(v12) = v16;
        if (v15 > control_c_variable_176 && !*(_BYTE *)(a1 + 306)) {
          v20 = v236 * control_c_variable_177 * control_c_variable_178;
          _CHP(LODWORD(v12), v11);
          v291 = (int)v20;
          sfxpend(12, *(_DWORD *)(a1 + 32), (int)v20);
          *(_BYTE *)(a1 + 306) = 9;
        }
        v21 = v288;
        v22 = v281;
        v23 = v280;
        *(float *)(a1 + 40) = v4[1] * v288 + *v4 * v281 + v4[2] * v280;
        *(float *)(a1 + 44) = v4[3] * v22 + v4[4] * v21 + v4[5] * v23;
        *(float *)(a1 + 48) = v21 * v4[7] + v22 * v4[6] + v23 * v4[8];
        v289 = v251 - *(float *)&CarBaseY;
        v24 = v287;
        v25 = v290;
        *(float *)a1 = v4[1] * v289 + *v4 * v287 + v4[2] * v290 - v4[9];
        *(float *)(a1 + 4) = v4[3] * v24 + v4[4] * v289 + v4[5] * v25 - v4[10];
        v26 = v25 * v4[8] + v24 * v4[6] + v4[7] * v289 - v4[11];
        v291 = *(int *)(a1 + 40);
        v234 = *(_DWORD *)(a1 + 44);
        v224 = *(float *)&v291;
        v27 = v291;
        v225 = v234;
        *(float *)(a1 + 8) = v26;
        if ((v27 & 0x7FFFFFFF) != 0 || (v234 & 0x7FFFFFFF) != 0) {
          v29 = v224;
          IF_DATAN2(v224);
          v30 = v29 * control_c_variable_179 / control_c_variable_180;
          _CHP(v31, v27);
          v291 = (int)v30;
          v28 = (int)v30 & 0x3FFF;
        } else {
          v28 = 0;
        }
      LABEL_69:
        v52 = *(float *)(a1 + 40) * *(float *)(a1 + 40) + *(float *)(a1 + 44) * *(float *)(a1 + 44);
        *(_DWORD *)(a1 + 64) = v28;
        *(float *)(a1 + 36) = sqrt(v52);
      }
    }
  }
  if (v4[13] + *v2 >= v289) {
    v53 = -v4[13];
    v235 = v53;
    if (v53 - v2[2] <= v289) {
      if (v289 <= (double)v4[13])
        v54 = v289 >= (double)v235 ? 1 : 2;
      else
        v54 = 0;
      v55 = *((int *)&TrakColour + 6 * v286 + v54);
      v56 = (HIDWORD(v55) ^ v55) - HIDWORD(v55);
      if ((v56 & 0x20000) == 0)
        goto LABEL_81;
      v58 = v4[12] * control_c_variable_181;
      v59 = v58 < *(float *)&CarBaseX;
      v60 = 0;
      v61 = v58 == *(float *)&CarBaseX;
      LOWORD(v56) = v57;
      if (v58 <= *(float *)&CarBaseX
        || (v63 = v4[13] * control_c_variable_181,
            v64 = v63 < *(float *)&CarBaseX,
            v65 = 0,
            v66 = v63 == *(float *)&CarBaseX,
            LOWORD(v56) = v62,
            v63 <= *(float *)&CarBaseX)) {
      LABEL_81:
        v247 = getgroundz(v56, v287, v289, v286);
        if (v290 <= (double)v247 && v280 * control_c_variable_181 + v247 + control_c_variable_184 <= v290) {
          *(float *)a1 = v287;
          *(float *)(a1 + 4) = v289;
          getlocalangles(&v212, &v214, &v211);
          *(_WORD *)(a1 + 20) = v212;
          *(_DWORD *)(a1 + 64) = v212;
          *(_WORD *)(a1 + 18) = v214;
          *(_WORD *)(a1 + 16) = v211;
          v67 = LODWORD(v281);
          *(_WORD *)(a1 + 12) = v286;
          if ((v67 & 0x7FFFFFFF) != 0 || (LODWORD(v288) & 0x7FFFFFFF) != 0) {
            v68 = v281;
            IF_DATAN2(v281);
            v69 = v68 * control_c_variable_179 / control_c_variable_180;
            _CHP(v70, v67);
            v291 = (int)v69;
            *(_DWORD *)(a1 + 64) = (int)v69 & 0x3FFF;
          }
          if (v211 < 4096 || v211 > 12288) {
            *(_DWORD *)(a1 + 204) = 0;
          } else {
            *(_DWORD *)(a1 + 204) = -1;
            *(_DWORD *)(a1 + 76) = 0;
            v67 = v211 + 0x2000;
            v211 = v67;
            if (v67 >= 0x4000)
              v211 = v67 - 0x4000;
          }
          putflat(a1);
          if (v214 > 0x2000) {
            v67 = v214 - 0x4000;
            v214 -= 0x4000;
          }
          v71 = v214;
          *(_DWORD *)(a1 + 144) = 0;
          *(_DWORD *)(a1 + 140) = v71;
          *(_DWORD *)(a1 + 148) = v214;
          if (v211 > 0x2000)
            v211 -= 0x4000;
          v72 = v244 - v290;
          v232 = v72;
          v73 = v72 * control_c_variable_177 * control_c_variable_178;
          v74 = v211;
          *(_DWORD *)(a1 + 72) = 3;
          *(_DWORD *)(a1 + 152) = v74;
          *(_DWORD *)(a1 + 156) = v74;
          v75 = *(_DWORD *)(a1 + 204);
          v269 = v73;
          if (v75) {
            v82 = v269;
            _CHP(v75, v67);
            v291 = (int)v82;
            sfxpend(13, *(_DWORD *)(a1 + 32), (int)v82);
          } else if (!*(_BYTE *)(a1 + 306)) {
            v77 = v232 < (double)control_c_variable_176;
            v78 = 0;
            v79 = v232 == control_c_variable_176;
            LOWORD(v75) = v76;
            v80 = v269;
            if (v232 <= (double)control_c_variable_176) {
              _CHP(v75, v67);
              v291 = (int)v80;
              v81 = 10;
            } else {
              _CHP(v75, v67);
              v291 = (int)v80;
              v81 = 9;
            }
            sfxpend(v81, *(_DWORD *)(a1 + 32), v291);
            *(_BYTE *)(a1 + 306) = 9;
          }
          v193 = fabs((v244 - v290) * tsin[v214 & 0x3FFF] * control_c_variable_185);
          dodamage(v193);
          v194 = sqrt(v281 * v281 + v288 * v288);
          SetEngine(a1, v194);
        }
      }
    }
  }
  if (*(__int16 *)(a1 + 12) == -1) {
    v83 = GroundColour_variable_4[5 * v286];
    if (v83 != -1) {
      if (v83 >= 0) {
        v84 = v259 + v209;
        v85 = v254 + v208;
        v86 = v253 + v210;
        v287 = v202 * v84 + v199 * v85 + v205 * v86;
        v289 = v200 * v85 + v203 * v84 + v206 * v86;
        v4 = &v199;
        v290 = v84 * v204 + v85 * v201 + v86 * v207;
      }
      if ((GroundColour_variable_4[5 * v286] < 0 || v289 < 0.0)
        && (GroundColour_variable_4[5 * v286] >= 0 || v4[13] + *v2 - *(float *)&CarBaseY > v289)) {
        if (GroundColour_variable_4[5 * v286] >= 0) {
          v138 = v259 + v209;
          v139 = v254 + v208;
          v140 = v253 + v210;
          v287 = v202 * v138 + v199 * v139 + v205 * v140;
          v289 = v200 * v139 + v203 * v138 + v206 * v140;
          v4 = &v199;
          v290 = v138 * v204 + v139 * v201 + v140 * v207;
        }
        if (GroundColour_variable_4[5 * v286] >= 0 && v289 < 0.0
          || GroundColour_variable_4[5 * v286] < 0 && -v4[13] - v2[2] + *(float *)&CarBaseY >= v289) {
          v141 = &GroundPt[18 * v286];
          v142 = (int)(v141 + 12);
          v143 = v141[13] + v4[10];
          v144 = v141[12] + v4[9];
          v145 = v141[14] + v4[11];
          v256 = v4[4] * v143 + v4[1] * v144 + v4[7] * v145;
          v279 = v143 * v4[5] + v144 * v4[2] + v145 * v4[8];
          v245 = v290 - v279;
          if (v290 <= (double)v279) {
            v168 = (int)(v141 + 9);
            v169 = v141[10] + v4[10];
            v170 = v141[9] + v4[9];
            v171 = v141[11] + v4[11];
            v230 = v4[4] * v169 + v4[1] * v170 + v4[7] * v171;
            v257 = v169 * v4[5] + v170 * v4[2] + v171 * v4[8];
            v172 = v279 - v257;
            v250 = v172;
            if (fabs(v172) <= control_c_variable_186)
              v263 = -1000000.0;
            else
              v263 = v245 * v230 / (v257 - v279) + (v290 - v257) * v256 / v250;
            if (v289 - *(float *)&CarBaseY < v263) {
              v275 = v4[3] * *(float *)(a1 + 44) + *v4 * *(float *)(a1 + 40) + v4[6] * *(float *)(a1 + 48);
              v285 = v4[1] * *(float *)(a1 + 40) + v4[4] * *(float *)(a1 + 44) + v4[7] * *(float *)(a1 + 48);
              v260 = v4[2] * *(float *)(a1 + 40) + v4[5] * *(float *)(a1 + 44) + v4[8] * *(float *)(a1 + 48);
              if (v285 < 0.0) {
                HIBYTE(v285) ^= 0x80u;
                if (death_race)
                  v173 = v285 * control_c_variable_182 * control_c_variable_175;
                else
                  v173 = v285 * control_c_variable_182;
                v198 = v173;
                v168 = dodamage(v198);
                *(_DWORD *)(a1 + 200) = -*(_DWORD *)(a1 + 200);
              }
              if (v285 < (double)control_c_variable_176)
                v285 = 40.0;
              v175 = v285 < (double)control_c_variable_176;
              v176 = 0;
              v177 = v285 == control_c_variable_176;
              LOWORD(v168) = v174;
              if (v285 > (double)control_c_variable_176 && !*(_BYTE *)(a1 + 306)) {
                v178 = v285 * control_c_variable_177 * control_c_variable_178;
                _CHP(v168, v141);
                v291 = (int)v178;
                sfxpend(11, *(_DWORD *)(a1 + 32), (int)v178);
                *(_BYTE *)(a1 + 306) = 9;
              }
              v179 = v263 + *(float *)&CarBaseY;
              v180 = v287;
              v181 = v290;
              *(float *)a1 = v4[1] * v179 + *v4 * v287 + v4[2] * v290 - v4[9];
              *(float *)(a1 + 4) = v4[3] * v180 + v4[4] * v179 + v4[5] * v181 - v4[10];
              *(float *)(a1 + 8) = v179 * v4[7] + v180 * v4[6] + v181 * v4[8] - v4[11];
              v182 = v285;
              v183 = v275;
              v184 = v260;
              *(float *)(a1 + 40) = v4[1] * v285 + *v4 * v275 + v4[2] * v260;
              *(float *)(a1 + 44) = v4[3] * v183 + v4[4] * v182 + v4[5] * v184;
              v185 = v182 * v4[7] + v183 * v4[6] + v184 * v4[8];
              v291 = *(int *)(a1 + 40);
              v248 = *(_DWORD *)(a1 + 44);
              v215 = *(float *)&v291;
              v186 = v291;
              v293 = v248;
              *(float *)(a1 + 48) = v185;
              if ((v186 & 0x7FFFFFFF) != 0 || (v248 & 0x7FFFFFFF) != 0) {
                v187 = v215;
                IF_DATAN2(v215);
                v188 = v187 * control_c_variable_179 / control_c_variable_180;
                _CHP(v189, v186);
                v291 = (int)v188;
                v111 = (int)v188 & 0x3FFF;
              } else {
                v111 = 0;
              }
              goto LABEL_192;
            }
          } else if (v289 < (double)v256) {
            v146 = v141[16] + v4[10];
            v147 = v141[15] + v4[9];
            v148 = v141[17] + v4[11];
            v223 = v4[4] * v146 + v4[1] * v147 + v4[7] * v148;
            v262 = v146 * v4[5] + v147 * v4[2] + v148 * v4[8];
            v149 = v279 - v262;
            v239 = v149;
            v150 = v141 + 15;
            v264 = fabs(v149) <= control_c_variable_186
              ? -1000000.0
              : v245 * v223 / (v262 - v279) + (v290 - v262) * v256 / v239;
            if (v289 - *(float *)&CarBaseY < v264) {
              v274 = v4[3] * *(float *)(a1 + 44) + *v4 * *(float *)(a1 + 40) + v4[6] * *(float *)(a1 + 48);
              v284 = v4[1] * *(float *)(a1 + 40) + v4[4] * *(float *)(a1 + 44) + v4[7] * *(float *)(a1 + 48);
              v272 = v4[2] * *(float *)(a1 + 40) + v4[5] * *(float *)(a1 + 44) + v4[8] * *(float *)(a1 + 48);
              if (v284 < 0.0) {
                HIBYTE(v284) ^= 0x80u;
                if (death_race)
                  v151 = v284 * control_c_variable_182 * control_c_variable_175;
                else
                  v151 = v284 * control_c_variable_182;
                v197 = v151;
                v142 = dodamage(v197);
                *(_DWORD *)(a1 + 200) = -*(_DWORD *)(a1 + 200);
              }
              if (v284 < (double)control_c_variable_176)
                v284 = 40.0;
              v153 = v284 < (double)control_c_variable_176;
              v154 = 0;
              v155 = v284 == control_c_variable_176;
              LOWORD(v142) = v152;
              if (v284 > (double)control_c_variable_176 && !*(_BYTE *)(a1 + 306)) {
                v156 = v284 * control_c_variable_177 * control_c_variable_178;
                _CHP(v142, v150);
                v291 = (int)v156;
                v150 = *(float **)(a1 + 32);
                sfxpend(11, v150, (int)v156);
                *(_BYTE *)(a1 + 306) = 9;
              }
              v157 = v264 + *(float *)&CarBaseY;
              v158 = v287;
              v159 = v290;
              *(float *)a1 = v4[1] * v157 + *v4 * v287 + v4[2] * v290 - v4[9];
              *(float *)(a1 + 4) = v4[3] * v158 + v4[4] * v157 + v4[5] * v159 - v4[10];
              *(float *)(a1 + 8) = v157 * v4[7] + v158 * v4[6] + v159 * v4[8] - v4[11];
              v160 = v284;
              v161 = v274;
              v162 = v272;
              *(float *)(a1 + 40) = v4[1] * v284 + *v4 * v274 + v4[2] * v272;
              *(float *)(a1 + 44) = v4[3] * v161 + v4[4] * v160 + v4[5] * v162;
              v163 = v160 * v4[7] + v161 * v4[6] + v162 * v4[8];
              v291 = *(int *)(a1 + 40);
              v252 = *(_DWORD *)(a1 + 44);
              v221 = *(float *)&v291;
              v164 = v291;
              v218 = v252;
              *(float *)(a1 + 48) = v163;
              if ((v164 & 0x7FFFFFFF) != 0 || (v252 & 0x7FFFFFFF) != 0) {
                v165 = v221;
                IF_DATAN2(v221);
                v166 = v165 * control_c_variable_179 / control_c_variable_180;
                _CHP(v167, v150);
                v291 = (int)v166;
                v111 = (int)v166 & 0x3FFF;
              } else {
                v111 = 0;
              }
              goto LABEL_192;
            }
          }
        }
      } else {
        v87 = (int)&GroundPt[18 * v286];
        v88 = v87 + 12;
        v89 = *(float *)(v87 + 16) + v4[10];
        v90 = *(float *)(v87 + 12) + v4[9];
        v91 = *(float *)(v87 + 20) + v4[11];
        v270 = v4[4] * v89 + v4[1] * v90 + v4[7] * v91;
        v278 = v89 * v4[5] + v90 * v4[2] + v91 * v4[8];
        v243 = v290 - v278;
        if (v290 <= (double)v278) {
          v115 = *(float *)(v87 + 28) + v4[10];
          v116 = *(float *)(v87 + 24) + v4[9];
          v117 = *(float *)(v87 + 32) + v4[11];
          v229 = v4[4] * v115 + v4[1] * v116 + v4[7] * v117;
          v261 = v115 * v4[5] + v116 * v4[2] + v117 * v4[8];
          v118 = v278 - v261;
          v233 = v118;
          v119 = (float *)(v87 + 24);
          if (fabs(v118) <= control_c_variable_186)
            v268 = 1000000.0;
          else
            v268 = v243 * v229 / (v261 - v278) + (v290 - v261) * v270 / v233;
          if (v289 + *(float *)&CarBaseY > v268) {
            v266 = v4[3] * *(float *)(a1 + 44) + *v4 * *(float *)(a1 + 40) + v4[6] * *(float *)(a1 + 48);
            v282 = v4[1] * *(float *)(a1 + 40) + v4[4] * *(float *)(a1 + 44) + v4[7] * *(float *)(a1 + 48);
            v271 = v4[2] * *(float *)(a1 + 40) + v4[5] * *(float *)(a1 + 44) + v4[8] * *(float *)(a1 + 48);
            if (v282 > 0.0) {
              if (death_race)
                v120 = v282 * control_c_variable_182 * control_c_variable_175;
              else
                v120 = v282 * control_c_variable_182;
              v196 = v120;
              v88 = dodamage(v196);
              HIBYTE(v282) ^= 0x80u;
              *(_DWORD *)(a1 + 200) = -*(_DWORD *)(a1 + 200);
            }
            if (v282 > (double)control_c_variable_183)
              v282 = -40.0;
            v121 = -v282;
            v240 = v121;
            v123 = v121 < control_c_variable_176;
            v124 = 0;
            v125 = v121 == control_c_variable_176;
            LOWORD(v88) = v122;
            if (v121 > control_c_variable_176 && !*(_BYTE *)(a1 + 306)) {
              v126 = v240 * control_c_variable_177 * control_c_variable_178;
              _CHP(v88, v119);
              v291 = (int)v126;
              v119 = *(float **)(a1 + 32);
              sfxpend(11, v119, (int)v126);
              *(_BYTE *)(a1 + 306) = 9;
            }
            v127 = v268 - *(float *)&CarBaseY;
            v128 = v287;
            v129 = v290;
            *(float *)a1 = v4[1] * v127 + *v4 * v287 + v4[2] * v290 - v4[9];
            *(float *)(a1 + 4) = v4[3] * v128 + v4[4] * v127 + v4[5] * v129 - v4[10];
            *(float *)(a1 + 8) = v127 * v4[7] + v128 * v4[6] + v129 * v4[8] - v4[11];
            v130 = v282;
            v131 = v266;
            v132 = v271;
            *(float *)(a1 + 40) = v4[1] * v282 + *v4 * v266 + v4[2] * v271;
            *(float *)(a1 + 44) = v4[3] * v131 + v4[4] * v130 + v4[5] * v132;
            v133 = v130 * v4[7] + v131 * v4[6] + v132 * v4[8];
            v291 = *(int *)(a1 + 40);
            v249 = *(_DWORD *)(a1 + 44);
            v220 = *(float *)&v291;
            v134 = v291;
            v227 = v249;
            *(float *)(a1 + 48) = v133;
            if ((v134 & 0x7FFFFFFF) != 0 || (v249 & 0x7FFFFFFF) != 0) {
              v135 = v220;
              IF_DATAN2(v220);
              v136 = v135 * control_c_variable_179 / control_c_variable_180;
              _CHP(v137, v119);
              v291 = (int)v136;
              v111 = (int)v136 & 0x3FFF;
            } else {
              v111 = 0;
            }
            goto LABEL_192;
          }
        } else if (v289 > (double)v270) {
          v92 = *(float *)(v87 + 4) + v4[10];
          v93 = *(float *)v87 + v4[9];
          v94 = *(float *)(v87 + 8) + v4[11];
          v228 = v4[4] * v92 + v4[1] * v93 + v4[7] * v94;
          v273 = v92 * v4[5] + v93 * v4[2] + v94 * v4[8];
          v95 = v278 - v273;
          v237 = v95;
          v267 = fabs(v95) <= control_c_variable_186
            ? 1000000.0
            : v243 * v228 / (v273 - v278) + (v290 - v273) * v270 / v237;
          if (v289 + *(float *)&CarBaseY > v267) {
            v265 = v4[3] * *(float *)(a1 + 44) + *v4 * *(float *)(a1 + 40) + v4[6] * *(float *)(a1 + 48);
            v283 = v4[1] * *(float *)(a1 + 40) + v4[4] * *(float *)(a1 + 44) + v4[7] * *(float *)(a1 + 48);
            v258 = v4[2] * *(float *)(a1 + 40) + v4[5] * *(float *)(a1 + 44) + v4[8] * *(float *)(a1 + 48);
            if (v283 > 0.0) {
              if (death_race)
                v96 = v283 * control_c_variable_182 * control_c_variable_175;
              else
                v96 = v283 * control_c_variable_182;
              v195 = v96;
              v88 = dodamage(v195);
              v87 = -*(_DWORD *)(a1 + 200);
              HIBYTE(v283) ^= 0x80u;
              *(_DWORD *)(a1 + 200) = v87;
            }
            if (v283 > (double)control_c_variable_183)
              v283 = -40.0;
            v97 = -v283;
            v241 = v97;
            v99 = v97 < control_c_variable_176;
            v100 = 0;
            v101 = v97 == control_c_variable_176;
            LOWORD(v88) = v98;
            if (v97 > control_c_variable_176 && !*(_BYTE *)(a1 + 306)) {
              v102 = v241 * control_c_variable_177 * control_c_variable_178;
              _CHP(v88, v87);
              v291 = (int)v102;
              v87 = *(_DWORD *)(a1 + 32);
              sfxpend(11, v87, (int)v102);
              *(_BYTE *)(a1 + 306) = 9;
            }
            v103 = v267 - *(float *)&CarBaseY;
            v104 = v287;
            v105 = v290;
            *(float *)a1 = v4[1] * v103 + *v4 * v287 + v4[2] * v290 - v4[9];
            *(float *)(a1 + 4) = v4[3] * v104 + v4[4] * v103 + v4[5] * v105 - v4[10];
            *(float *)(a1 + 8) = v103 * v4[7] + v104 * v4[6] + v105 * v4[8] - v4[11];
            v106 = v283;
            v107 = v265;
            v108 = v258;
            *(float *)(a1 + 40) = v4[1] * v283 + *v4 * v265 + v4[2] * v258;
            *(float *)(a1 + 44) = v4[3] * v107 + v4[4] * v106 + v4[5] * v108;
            v109 = v106 * v4[7] + v107 * v4[6] + v108 * v4[8];
            v291 = *(int *)(a1 + 40);
            v246 = *(_DWORD *)(a1 + 44);
            v222 = *(float *)&v291;
            v110 = v291;
            v294 = v246;
            *(float *)(a1 + 48) = v109;
            if ((v110 & 0x7FFFFFFF) != 0 || (v246 & 0x7FFFFFFF) != 0) {
              v112 = v222;
              IF_DATAN2(v222);
              v113 = v112 * control_c_variable_179 / control_c_variable_180;
              _CHP(v114, v87);
              v291 = (int)v113;
              v111 = (int)v113 & 0x3FFF;
            } else {
              v111 = 0;
            }
          LABEL_192:
            v190 = *(float *)(a1 + 40) * *(float *)(a1 + 40) + *(float *)(a1 + 44) * *(float *)(a1 + 44);
            *(_DWORD *)(a1 + 64) = v111;
            *(float *)(a1 + 36) = sqrt(v190);
          }
        }
      }
    }
  }*/
}

//-------------------------------------------------------------------------------------------------
//00034CF0
int16 converttoair(int a1, int a2, int a3, int a4)
{
  (void)(a1); (void)(a2); (void)(a3); (void)(a4);
  return 0;
  /*
  int v5; // eax
  int v6; // eax
  double v7; // st7
  int v8; // edi
  float *v9; // edi
  double v10; // st7
  double v11; // st7
  __int16 result; // ax
  int v13; // [esp+0h] [ebp-30h] BYREF
  int v14; // [esp+4h] [ebp-2Ch] BYREF
  float v15; // [esp+8h] [ebp-28h]
  float v16; // [esp+Ch] [ebp-24h]
  int v17; // [esp+10h] [ebp-20h] BYREF
  int v18; // [esp+14h] [ebp-1Ch] BYREF
  float v19; // [esp+18h] [ebp-18h]
  int v20; // [esp+28h] [ebp-8h]

  v20 = a4;
  *(_DWORD *)(a1 + 72) = 0;
  v5 = *(__int16 *)(a1 + 12);
  if (v5 == -1)
    v5 = *(__int16 *)(a1 + 14);
  *(_DWORD *)(a1 + 216) = v5;
  if (v5 < 0)
    v5 += TRAK_LEN;
  v6 = v5 << 7;
  v7 = (double)*(int *)((char *)&localdata + v6 + 64) * *(float *)(a1 + 24) * control_c_variable_187
    + (double)*(int *)(a1 + 200);
  _CHP(v6, a2);
  *(_DWORD *)(a1 + 200) = (int)v7;
  v8 = *(__int16 *)(a1 + 12);
  getworldangles(&v14, &v13, &v17);
  getworldangles(&v18, &v13, &v17);
  *(_WORD *)(a1 + 20) = v18;
  *(_DWORD *)(a1 + 64) = v18;
  *(_WORD *)(a1 + 18) = v13;
  v9 = (float *)((char *)&localdata + 128 * v8);
  *(_WORD *)(a1 + 16) = v17;
  v16 = v9[1] * *(float *)(a1 + 4) + *v9 * *(float *)a1 + v9[2] * *(float *)(a1 + 8) - v9[9];
  v19 = v9[4] * *(float *)(a1 + 4) + v9[3] * *(float *)a1 + v9[5] * *(float *)(a1 + 8) - v9[10];
  v15 = v9[7] * *(float *)(a1 + 4) + v9[6] * *(float *)a1 + v9[8] * *(float *)(a1 + 8) - v9[11];
  v10 = *(float *)(a1 + 24);
  *(float *)a1 = v16;
  *(float *)(a1 + 4) = v19;
  *(float *)(a1 + 8) = v15;
  *(float *)(a1 + 40) = v10 * tcos[v14] * tcos[v13];
  *(float *)(a1 + 44) = *(float *)(a1 + 24) * tsin[v14] * tcos[v13];
  *(float *)(a1 + 48) = *(float *)(a1 + 24) * tsin[v13];
  v11 = *(float *)(a1 + 24) * tcos[v13];
  *(_DWORD *)(a1 + 116) = 0;
  result = *(_WORD *)(a1 + 12);
  *(_WORD *)(a1 + 12) = -1;
  *(_WORD *)(a1 + 14) = result;
  *(float *)(a1 + 36) = v11;
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00034EA0
void ordercars()
{
  /*
  int v0; // edi
  unsigned int v1; // edx
  int v2; // esi
  float *v3; // ebx
  float *v4; // eax
  char v5; // cl
  char v6; // ch
  int v7; // eax
  __int16 v8; // cx
  int v9; // ebx
  int v10; // eax
  int v11; // [esp+0h] [ebp-18h]
  int v12; // [esp+0h] [ebp-18h]

  v0 = numcars;
  v1 = 0;
  v2 = 4 * (numcars - 1);
  v11 = 0;
  if (v2 > 0) {
    do {
      v3 = &Car[77 * carorder[v1 / 4]];
      if (!finished_car[*((_DWORD *)v3 + 8)]) {
        v4 = &Car[77 * carorder_variable_1[v1 / 4]];
        if (*((__int16 *)v3 + 6) != -1 && *((__int16 *)v4 + 6) != -1 && !finished_car[*((_DWORD *)v4 + 8)]) {
          v5 = *((_BYTE *)v4 + 104);
          v6 = *((_BYTE *)v3 + 104);
          if (v5 <= v6) {
            if (v5 == v6) {
              v8 = *((_WORD *)v4 + 6);
              if (v8 > *((__int16 *)v3 + 6) || v8 == *((_WORD *)v3 + 6) && *v4 > (double)*v3) {
                v9 = carorder[v1 / 4];
                carorder[v1 / 4] = carorder_variable_1[v1 / 4];
                carorder_variable_1[v1 / 4] = v9;
              }
            }
          } else {
            v7 = carorder[v1 / 4];
            carorder[v1 / 4] = carorder_variable_1[v1 / 4];
            carorder_variable_1[v1 / 4] = v7;
          }
        }
      }
      v1 += 4;
      ++v11;
    } while ((int)v1 < v2);
  }
  v12 = 0;
  if (v0 > 0) {
    v10 = 0;
    do
      Car_variable_32[308 * carorder[v10++]] = v12++;
    while (v0 > v12);
  }
  numcars = v0;*/
}

//-------------------------------------------------------------------------------------------------
//00034FC0
void changeline(int a1)
{
  (void)(a1);
  /*
  int v2; // eax
  char *v3; // ecx
  int v4; // eax
  __int16 v5; // fps
  double v6; // st7
  _BOOL1 v7; // c0
  char v8; // c2
  _BOOL1 v9; // c3
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // ebp
  int v14; // edx
  int v15; // eax
  int v16; // eax

  v2 = *(__int16 *)(a1 + 12);
  v3 = (char *)&localdata + 128 * v2;
  if (*(_DWORD *)(a1 + 196) == -1) {
    v4 = 3 * v2;
    if ((TrakColour_variable_5[4 * v4] & 0x100) != 0) {
      if (*(_DWORD *)(a1 + 208) != -1) {
        v6 = *(float *)(a1 + 28);
        v7 = v6 < control_c_variable_188;
        v8 = 0;
        v9 = v6 == control_c_variable_188;
        LOWORD(v4) = v5;
        if (v6 < control_c_variable_188) {
          *(_DWORD *)(a1 + 196) = 0;
          goto LABEL_13;
        }
      }
      if (!*(_DWORD *)(a1 + 160)) {
        if (*(_BYTE *)(a1 + 130) >= 6u) {
          v10 = rand(v4);
          *(_DWORD *)(a1 + 196) = (v10 - (__CFSHL__(v10 >> 31, 13) + (v10 >> 31 << 13))) >> 13;
          goto LABEL_13;
        }
      LABEL_12:
        *(_DWORD *)(a1 + 196) = 3;
      }
    } else {
      if (*(_BYTE *)(a1 + 130) < 6u)
        goto LABEL_12;
      v11 = rand(v4);
      if ((720 * v11 - (__CFSHL__((720 * v11) >> 31, 15) + ((720 * v11) >> 31 << 15))) >> 15 == 100) {
        v12 = rand(100);
        *(_DWORD *)(a1 + 196) = (v12 - (__CFSHL__(v12 >> 31, 13) + (v12 >> 31 << 13))) >> 13;
      }
    }
  }
LABEL_13:
  v13 = *(_DWORD *)(a1 + 196);
  v14 = 0;
  if (v13 != -1 && linevalid(*(float *)(a1 + 4), *(float *)&v3[4 * v13 + 96])) {
    v15 = *(_DWORD *)(a1 + 196);
    *(_DWORD *)(a1 + 196) = -1;
    v14 = -1;
    *(_DWORD *)(a1 + 160) = v15;
  }
  if (!v14 && !linevalid(*(float *)(a1 + 4), *(float *)&v3[4 * *(_DWORD *)(a1 + 160) + 96])) {
    v16 = rand(0);
    *(_DWORD *)(a1 + 196) = (v16 - (__CFSHL__(v16 >> 31, 13) + (v16 >> 31 << 13))) >> 13;
  }*/
}

//-------------------------------------------------------------------------------------------------
//00035130
unsigned int driverange(int a1, float *a2, float *a3)
{
  (void)(a1); (void)(a2); (void)(a3);
  return 0;
  /*
  int v6; // eax
  int *v7; // esi
  int v8; // edx
  float *v9; // ebx
  int v10; // eax
  unsigned int result; // eax
  double v12; // st7
  double v13; // st7
  unsigned int v14; // [esp+0h] [ebp-28h]
  unsigned int v15; // [esp+4h] [ebp-24h]
  unsigned int v16; // [esp+8h] [ebp-20h]
  int v17; // [esp+Ch] [ebp-1Ch]
  int v18; // [esp+10h] [ebp-18h]

  v6 = *(__int16 *)(a1 + 12);
  v7 = &TrackInfo[9 * v6];
  v8 = v7[6];
  v9 = (float *)((char *)&localdata + 128 * v6);
  if (v8 == 5 || v8 == 6 || v8 == 9)
    v18 = -1;
  else
    v18 = 0;
  v10 = v7[7];
  if (v10 == 5 || v10 == 6 || v10 == 9)
    v17 = -1;
  else
    v17 = 0;
  v14 = abs32(*((_DWORD *)&TrakColour + 6 * *(__int16 *)(a1 + 12))) & 0x20000;
  v16 = abs32(*((_DWORD *)&TrakColour_variable_3 + 6 * *(__int16 *)(a1 + 12))) & 0x20000;
  v15 = abs32(*((_DWORD *)&TrakColour_variable_7 + 6 * *(__int16 *)(a1 + 12))) & 0x20000;
  result = *(_DWORD *)(a1 + 212);
  if (!result) {
    *a2 = v9[13] + *(float *)v7 - *(float *)(a1 + 84);
    if (v18 || v16) {
      *a3 = v9[13] + *(float *)(a1 + 84);
      return result;
    }
    if (v17 || v15) {
      *a3 = *(float *)(a1 + 84) - v9[13];
      return result;
    }
    goto LABEL_21;
  }
  if (result <= 1) {
    if (v18 || v14)
      v12 = v9[13];
    else
      v12 = v9[13] + *(float *)v7;
    *a2 = v12 - *(float *)(a1 + 84);
    if (v17 || v15) {
      *a3 = *(float *)(a1 + 84) - v9[13];
      return result;
    }
  LABEL_21:
    *a3 = -v9[13] - *((float *)v7 + 2) + *(float *)(a1 + 84);
    return result;
  }
  if (result == 2) {
    *a3 = -v9[13] - *((float *)v7 + 2) + *(float *)(a1 + 84);
    if (v17 || v16) {
      v13 = -v9[13];
    } else {
      if (v18 || v14) {
        *a2 = v9[13] - *(float *)(a1 + 84);
        return result;
      }
      v13 = v9[13] + *(float *)v7;
    }
    *a2 = v13 - *(float *)(a1 + 84);
  }
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//00035330
int updatesmokeandflames(int a1, unsigned int a2, int a3, unsigned int a4)
{
  return 0;/*
  int v4; // ecx
  int v5; // esi
  __int64 v7; // [esp-Ch] [ebp-10h]
  __int64 v8; // [esp-Ch] [ebp-10h]
  int v10; // [esp-4h] [ebp-8h]

  v7 = __PAIR64__(a2, a4);
  v4 = a1;
  if (player_type != 2)
    a1 = ViewType[0];
  v5 = rand(a1);
  dospray(v7, a3);
  if (player_type == 2) {
    if (ViewType[0] == *(_DWORD *)(v4 + 32))
      dospray(v8, v10);
    if (ViewType_variable_1 == *(_DWORD *)(v4 + 32))
      dospray(v8, v10);
  }
  return srand(v5);*/
}

//-------------------------------------------------------------------------------------------------
//000353F0
void dospray(int64 a1, int a2)
{
  (void)(a1); (void)(a2);
  /*
  __int64 v2; // kr00_8
  int v4; // ebp
  __int16 v5; // fps
  _BOOL1 v6; // c0
  char v7; // c2
  _BOOL1 v8; // c3
  __int16 v9; // fps
  double v10; // st7
  _BOOL1 v11; // c0
  char v12; // c2
  _BOOL1 v13; // c3
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int v29; // ebx
  int v30; // ebx
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // eax
  int v35; // edx
  int v36; // eax
  int v37; // eax
  int v38; // eax
  int v39; // eax
  int v40; // eax
  int v41; // eax
  int v42; // eax
  int v43; // eax
  int v44; // eax
  int v45; // eax
  int v46; // eax
  int v47; // eax
  int v48; // eax
  int v49; // eax
  int v50; // eax
  int v51; // eax
  int v52; // eax
  unsigned int v53; // eax
  int v54; // eax
  int v55; // edx
  int v56; // eax
  int v57; // eax
  char v58; // fps^1
  _BOOL1 v59; // c0
  char v60; // c2
  _BOOL1 v61; // c3
  __int16 v62; // fps
  _BOOL1 v63; // c0
  char v64; // c2
  _BOOL1 v65; // c3
  __int16 v66; // fps
  double v67; // st7
  _BOOL1 v68; // c0
  char v69; // c2
  _BOOL1 v70; // c3
  __int16 v71; // fps
  _BOOL1 v72; // c0
  char v73; // c2
  _BOOL1 v74; // c3
  int v75; // eax
  int v76; // eax
  int v77; // ebx
  int v78; // eax
  int v79; // eax
  int v80; // eax
  int v81; // eax
  int v82; // eax
  float *v83; // eax
  int v84; // ebx
  int v85; // eax
  int v86; // eax
  int v87; // eax
  int v88; // eax
  __int16 v89; // fps
  _BOOL1 v90; // c0
  char v91; // c2
  _BOOL1 v92; // c3
  int v93; // eax
  int v94; // eax
  float *v95; // eax
  int v96; // eax
  int v97; // eax
  int v98; // eax
  int v99; // eax
  int v100; // eax
  int v101; // eax
  int v102; // eax
  int v103; // eax
  int v104; // eax
  int v105; // eax
  __int64 v106; // rax
  double v107; // st7
  int v108; // eax
  int v109; // eax
  int v110; // eax
  int v111; // eax
  int v112; // edx
  int v113; // eax
  int v114; // eax
  int v115; // eax
  __int16 v116; // fps
  _BOOL1 v117; // c0
  char v118; // c2
  _BOOL1 v119; // c3
  int v120; // eax
  double v121; // st7
  __int16 v122; // fps
  _BOOL1 v123; // c0
  char v124; // c2
  _BOOL1 v125; // c3
  double v126; // st7
  double v127; // [esp+0h] [ebp-3Ch]
  float v128; // [esp+Ch] [ebp-30h]
  float v129; // [esp+10h] [ebp-2Ch]
  float v130; // [esp+14h] [ebp-28h]
  float v131; // [esp+18h] [ebp-24h]
  int v132; // [esp+1Ch] [ebp-20h]
  int v133; // [esp+20h] [ebp-1Ch]
  float v134; // [esp+24h] [ebp-18h]
  int v135; // [esp+28h] [ebp-14h]
  int v136; // [esp+28h] [ebp-14h]
  int v137; // [esp+28h] [ebp-14h]
  int v138; // [esp+28h] [ebp-14h]
  int v139; // [esp+28h] [ebp-14h]
  int v140; // [esp+28h] [ebp-14h]
  int v141; // [esp+28h] [ebp-14h]
  int v142; // [esp+28h] [ebp-14h]
  int v143; // [esp+28h] [ebp-14h]
  int v144; // [esp+28h] [ebp-14h]
  int v145; // [esp+28h] [ebp-14h]
  int v146; // [esp+28h] [ebp-14h]
  int v147; // [esp+28h] [ebp-14h]

  v2 = a1;
  v134 = (*(float *)(a1 + 28) + control_c_variable_189) * control_c_variable_190;
  HIDWORD(a1) = *(unsigned __int8 *)(a1 + 102);
  v133 = CarDesigns_variable_6[7 * HIDWORD(a1)];
  if (v134 > 1.0)
    v134 = 1.0;
  v131 = v134 * control_c_variable_191;
  v128 = v134 * control_c_variable_192;
  v130 = v134 * control_c_variable_193;
  LODWORD(a1) = 28 * HIDWORD(a1);
  v4 = 0;
  v132 = 28 * HIDWORD(a1);
  v129 = v134 * control_c_variable_194;
  do {
    LOBYTE(a1) = *(_BYTE *)(a2 + 40);
    if ((_BYTE)a1) {
      if ((unsigned __int8)a1 <= 1u) {
        v27 = rand(a1);
        v28 = (4 * v27 - (__CFSHL__((4 * v27) >> 31, 15) + ((4 * v27) >> 31 << 15))) >> 15;
        v29 = v28 + 4;
        BYTE1(v29) = ((unsigned __int16)(v28 + 4) >> 8) | 5;
        *(_DWORD *)(a2 + 36) = v29;
        v30 = *(_DWORD *)(a2 + 32);
        if (HIDWORD(v2)) {
          v31 = rand(v28);
          v32 = (((60 * v31 - (__CFSHL__((60 * v31) >> 31, 15) + ((60 * v31) >> 31 << 15))) >> 15) + 20) * scr_size;
          v33 = (v32 - (__CFSHL__(v32 >> 31, 6) + (v32 >> 31 << 6))) >> 6;
          *(float *)(a2 + 24) = (float)v33;
          v34 = rand(v33);
          if (v30 == 1)
            v35 = (((50 * v34 - (__CFSHL__((50 * v34) >> 31, 15) + ((50 * v34) >> 31 << 15))) >> 15) + 40) * scr_size;
          else
            v35 = scr_size * (-40 - ((50 * v34 - (__CFSHL__((50 * v34) >> 31, 15) + ((50 * v34) >> 31 << 15))) >> 15));
          v136 = (v35 - (__CFSHL__(v35 >> 31, 6) + (v35 >> 31 << 6))) >> 6;
          *(float *)(a2 + 12) = (float)v136;
          v36 = rand(v136);
          v37 = (((100 * v36 - (__CFSHL__((100 * v36) >> 31, 15) + ((100 * v36) >> 31 << 15))) >> 15) + 40) * scr_size;
          v137 = (v37 - (__CFSHL__(v37 >> 31, 6) + (v37 >> 31 << 6))) >> 6;
          *(float *)(a2 + 16) = (float)v137;
          rand(v137);
        } else {
          v38 = rand(v28);
          v39 = ((100 * v38 - (__CFSHL__((100 * v38) >> 31, 15) + ((100 * v38) >> 31 << 15))) >> 15) + 100;
          *(float *)(a2 + 24) = (float)v39;
          if (v30) {
            v48 = rand(v39);
            if (v30 == 1) {
              v44 = (300 * v48 - (__CFSHL__((300 * v48) >> 31, 15) + ((300 * v48) >> 31 << 15))) >> 15;
              *(float *)(a2 + 12) = (float)(-100 - v44);
              v45 = rand(v44);
              v46 = (200 * v45 - (__CFSHL__((200 * v45) >> 31, 15) + ((200 * v45) >> 31 << 15))) >> 15;
              *(float *)(a2 + 16) = (float)(-100 - v46);
              v47 = rand(v46);
              v52 = ((200 * v47 - (__CFSHL__((200 * v47) >> 31, 15) + ((200 * v47) >> 31 << 15))) >> 15) + 200;
            } else {
              v49 = (150 * v48 - (__CFSHL__((150 * v48) >> 31, 15) + ((150 * v48) >> 31 << 15))) >> 15;
              *(float *)(a2 + 12) = (float)(-105 - v49);
              v50 = rand(v49);
              v139 = ((400 * v50 - (__CFSHL__((400 * v50) >> 31, 15) + ((400 * v50) >> 31 << 15))) >> 15) - 200;
              *(float *)(a2 + 16) = (float)v139;
              v51 = rand(v139);
              v52 = ((30 * v51 - (__CFSHL__((30 * v51) >> 31, 15) + ((30 * v51) >> 31 << 15))) >> 15) - 20;
            }
          } else {
            v40 = rand(v39);
            v41 = (300 * v40 - (__CFSHL__((300 * v40) >> 31, 15) + ((300 * v40) >> 31 << 15))) >> 15;
            *(float *)(a2 + 12) = (float)(-100 - v41);
            v42 = rand(v41);
            v138 = ((200 * v42 - (__CFSHL__((200 * v42) >> 31, 15) + ((200 * v42) >> 31 << 15))) >> 15) + 100;
            *(float *)(a2 + 16) = (float)v138;
            v43 = rand(v138);
            v52 = ((200 * v43 - (__CFSHL__((200 * v43) >> 31, 15) + ((200 * v43) >> 31 << 15))) >> 15) + 200;
          }
          *(float *)(a2 + 20) = (float)v52;
        }
        LODWORD(a1) = *(_DWORD *)(a2 + 28) - 1;
        *(_DWORD *)(a2 + 28) = a1;
        if ((int)a1 < 0) {
          *(_BYTE *)(a2 + 40) = 0;
          *(_DWORD *)(a2 + 32) = -1;
        }
      } else if ((_BYTE)a1 == 2) {
        v6 = *(float *)(v2 + 28) > 0.0;
        v7 = 0;
        v8 = 0.0 == *(float *)(v2 + 28);
        LOWORD(a1) = v5;
        if (*(float *)(v2 + 28) <= 0.0) {
          if (*(int *)(a2 + 28) <= 0) {
            if (*(__int16 *)(v2 + 106) < 0) {
              if (replaytype != 2)
                LODWORD(a1) = sfxpend(6, *(_DWORD *)(v2 + 32), 0x8000);
              LODWORD(a1) = rand(a1);
              LODWORD(a1) = ((int)(4 * a1 - (__CFSHL__((4 * (int)a1) >> 31, 15) + ((4 * (int)a1) >> 31 << 15))) >> 15)
                + 4;
              *(_WORD *)(v2 + 106) = a1;
            }
            *(_DWORD *)a2 = 0;
            *(_DWORD *)(a2 + 4) = 0;
            *(_DWORD *)(a2 + 8) = 0;
            v14 = rand(a1);
            if ((v4 & 7) != 0) {
              v20 = (100 * v14 - (__CFSHL__((100 * v14) >> 31, 15) + ((100 * v14) >> 31 << 15))) >> 15;
              *(float *)(a2 + 12) = (float)(50 - v20);
              v21 = rand(v20);
              v22 = (60 * v21 - (__CFSHL__((60 * v21) >> 31, 15) + ((60 * v21) >> 31 << 15))) >> 15;
              *(float *)(a2 + 16) = (float)(30 - v22);
              v23 = rand(v22);
              v19 = (((v23 << 6) - (__CFSHL__(v23 << 6 >> 31, 15) + (v23 << 6 >> 31 << 15))) >> 15) + 128;
            } else {
              v15 = (40 * v14 - (__CFSHL__((40 * v14) >> 31, 15) + ((40 * v14) >> 31 << 15))) >> 15;
              *(float *)(a2 + 12) = (float)(20 - v15);
              v16 = rand(v15);
              v17 = (20 * v16 - (__CFSHL__((20 * v16) >> 31, 15) + ((20 * v16) >> 31 << 15))) >> 15;
              *(float *)(a2 + 16) = (float)(10 - v17);
              v18 = rand(v17);
              v19 = ((320 * v18 - (__CFSHL__((320 * v18) >> 31, 15) + ((320 * v18) >> 31 << 15))) >> 15) + 320;
            }
            *(float *)(a2 + 24) = (float)v19;
            if (*(_DWORD *)(v2 + 204)) {
              v24 = rand(v19);
              v25 = (25 * v24 - (__CFSHL__((25 * v24) >> 31, 15) + ((25 * v24) >> 31 << 15))) >> 15;
              v135 = -5 - v25;
            } else {
              v26 = rand(v19);
              v25 = ((25 * v26 - (__CFSHL__((25 * v26) >> 31, 15) + ((25 * v26) >> 31 << 15))) >> 15) + 5;
              v135 = v25;
            }
            *(float *)(a2 + 20) = (float)v135;
            *(_DWORD *)(a2 + 36) = 9485;
            LODWORD(a1) = rand(v25);
            LODWORD(a1) = ((((_DWORD)a1 << 6)
                            - (__CFSHL__((int)((_DWORD)a1 << 6) >> 31, 15)
                               + ((int)((_DWORD)a1 << 6) >> 31 << 15))) >> 15)
              + 32;
            *(_DWORD *)(a2 + 28) = a1;
          } else {
            if (*(float *)a2 * *(float *)a2 + *(float *)(a2 + 4) + *(float *)(a2 + 4) < control_c_variable_201
              && *(float *)(a2 + 8) < (double)control_c_variable_202) {
              v10 = *(float *)(a2 + 8);
              v11 = v10 < control_c_variable_203;
              v12 = 0;
              v13 = v10 == control_c_variable_203;
              LOWORD(a1) = v9;
              if (v10 > control_c_variable_203) {
                LODWORD(a1) = rand(a1);
                LODWORD(a1) = ((int)(12 * a1 - (__CFSHL__((12 * (int)a1) >> 31, 15) + ((12 * (int)a1) >> 31 << 15))) >> 15)
                  + 4;
                *(float *)(a2 + 24) = (double)(int)a1 + *(float *)(a2 + 24);
                *(float *)a2 = *(float *)(a2 + 12) + *(float *)a2;
                *(float *)(a2 + 4) = *(float *)(a2 + 16) + *(float *)(a2 + 4);
                if (*(float *)(a2 + 8) < (double)control_c_variable_202
                  && *(float *)(a2 + 8) > (double)control_c_variable_203) {
                  *(float *)(a2 + 8) = *(float *)(a2 + 20) + *(float *)(a2 + 8);
                }
              }
            }
            -- * (_DWORD *)(a2 + 28);
            BYTE1(a1) = *(_BYTE *)(a2 + 28);
            *(_DWORD *)(a2 + 32) = 0;
            if ((a1 & 0x700) == 0) {
              LODWORD(a1) = (unsigned __int8)(*(_BYTE *)(a2 + 36) + 1);
              ++*(_DWORD *)(a2 + 36);
              if ((int)a1 > 20)
                *(_DWORD *)(a2 + 36) = 9490;
            }
          }
        } else {
          *(_DWORD *)(a2 + 28) = -1;
          *(_BYTE *)(a2 + 40) = 0;
          *(_DWORD *)(a2 + 36) = 9494;
        }
      }
      goto LABEL_136;
    }
    if (*(int *)(a2 + 28) <= 0) {
      v59 = *(float *)(v2 + 28) > 0.0;
      v60 = 0;
      v61 = 0.0 == *(float *)(v2 + 28);
      BYTE1(a1) = v58;
      if (*(float *)(v2 + 28) > 0.0) {
        LODWORD(a1) = *(_DWORD *)(a2 + 32);
        if ((int)a1 <= 0) {
          v63 = v134 > 1.0;
          v64 = 0;
          v65 = 1.0 == v134;
          LOWORD(a1) = v62;
          if (v134 >= 1.0) {
            *(_DWORD *)(a2 + 36) = 1302;
          } else {
            LODWORD(a1) = rand(a1);
            v67 = (double)(int)a1 * v134;
            v68 = v67 < control_c_variable_204;
            v69 = 0;
            v70 = v67 == control_c_variable_204;
            LOWORD(a1) = v66;
            if (v67 < control_c_variable_204) {
              v72 = v134 < control_c_variable_205;
              v73 = 0;
              v74 = v134 == control_c_variable_205;
              LOWORD(a1) = v71;
              if (v134 < control_c_variable_205) {
                *(_BYTE *)(a2 + 40) = 1;
                LODWORD(a1) = rand(a1);
                LODWORD(a1) = ((int)(16 * a1 - (__CFSHL__((16 * (int)a1) >> 31, 15) + ((16 * (int)a1) >> 31 << 15))) >> 15)
                  + 8;
                *(_DWORD *)(a2 + 28) = a1;
                if (v133 == -1) {
                  *(_DWORD *)a2 = 0;
                  *(_DWORD *)(a2 + 4) = 0;
                  *(_DWORD *)(a2 + 8) = 0;
                  *(_DWORD *)(a2 + 32) = -1;
                } else {
                  if (HIDWORD(v2)) {
                    v75 = rand(a1);
                    v76 = (2 * v75 - (__CFSHL__((2 * v75) >> 31, 15) + ((2 * v75) >> 31 << 15))) >> 15;
                    v77 = v76;
                    if (v76 == 2)
                      v77 = 1;
                    v78 = rand(v76);
                    if (v77 == 1) {
                      v140 = (v78 * scr_size - (__CFSHL__((v78 * scr_size) >> 31, 15) + ((v78 * scr_size) >> 31 << 15))) >> 15;
                      v79 = winw / 2;
                      v141 = winw / 2 + v140;
                    } else {
                      v79 = winw / 2
                        - ((v78 * scr_size - (__CFSHL__((v78 * scr_size) >> 31, 15) + ((v78 * scr_size) >> 31 << 15))) >> 15);
                      v141 = v79;
                    }
                    *(float *)a2 = (float)v141;
                    LODWORD(a1) = rand(v79);
                    LODWORD(a1) = (int)(a1 * scr_size
                                      - (__CFSHL__(((int)a1 * scr_size) >> 31, 16)
                                         + (((int)a1 * scr_size) >> 31 << 16))) >> 16;
                    *(float *)(a2 + 4) = (float)(a1 + winh);
                  } else {
                    v80 = rand(a1);
                    v81 = (32 * v80 - (__CFSHL__((32 * v80) >> 31, 15) + ((32 * v80) >> 31 << 15))) >> 15;
                    *(float *)(a2 + 4) = (float)(v81 + winh);
                    v82 = rand(v81);
                    v77 = (4 * v82 - (__CFSHL__((4 * v82) >> 31, 15) + ((4 * v82) >> 31 << 15))) >> 15;
                    if (v77 == 4)
                      v77 = 3;
                    v83 = (float *)(*(char **)((char *)&CarDesigns_variable_3 + v132) + 12 * *(_DWORD *)(v133 + 4 * v77));
                    if ((cheat_mode & 0x8000) == 0) {
                      *(float *)a2 = *v83;
                      *(float *)(a2 + 4) = v83[1];
                      *(float *)(a2 + 8) = v83[2];
                    } else {
                      *(float *)a2 = *v83 * control_c_variable_195;
                      *(float *)(a2 + 4) = v83[1] * control_c_variable_195;
                      *(float *)(a2 + 8) = v83[2] * control_c_variable_196;
                    }
                    LODWORD(a1) = rand(v83);
                  }
                  *(_DWORD *)(a2 + 32) = v77;
                }
              }
            }
            if (*(_BYTE *)(a2 + 40) != 1) {
              v84 = v133;
              if (v133 == -1) {
                *(_DWORD *)a2 = 0;
                *(_DWORD *)(a2 + 4) = 0;
                *(_DWORD *)(a2 + 8) = 0;
              } else if (HIDWORD(v2)) {
                v85 = rand(a1);
                v86 = (2 * v85 - (__CFSHL__((2 * v85) >> 31, 15) + ((2 * v85) >> 31 << 15))) >> 15;
                v84 = v86;
                if (v86 == 2)
                  v84 = 1;
                v87 = rand(v86);
                if (v84 == 1) {
                  v142 = (v87 * scr_size - (__CFSHL__((v87 * scr_size) >> 31, 15) + ((v87 * scr_size) >> 31 << 15))) >> 15;
                  v88 = winw / 2;
                  v143 = winw / 2 + v142;
                } else {
                  v88 = winw / 2
                    - ((v87 * scr_size - (__CFSHL__((v87 * scr_size) >> 31, 15) + ((v87 * scr_size) >> 31 << 15))) >> 15);
                  v143 = v88;
                }
                *(float *)a2 = (float)v143;
                LODWORD(a1) = rand(v88);
                LODWORD(a1) = (int)(a1 * scr_size
                                  - (__CFSHL__(((int)a1 * scr_size) >> 31, 16)
                                     + (((int)a1 * scr_size) >> 31 << 16))) >> 16;
                *(float *)(a2 + 4) = (float)(a1 + winh);
              } else {
                v90 = v134 < (double)control_c_variable_206;
                v91 = 0;
                v92 = v134 == control_c_variable_206;
                LOWORD(a1) = v89;
                if (v134 >= (double)control_c_variable_206) {
                  v94 = rand(a1);
                  v84 = (2 * v94 - (__CFSHL__((2 * v94) >> 31, 15) + ((2 * v94) >> 31 << 15))) >> 15;
                  if (v84 == 2)
                    v84 = 1;
                } else {
                  v93 = rand(a1);
                  v84 = (4 * v93 - (__CFSHL__((4 * v93) >> 31, 15) + ((4 * v93) >> 31 << 15))) >> 15;
                  if (v84 == 4)
                    v84 = 3;
                }
                v95 = (float *)(*(char **)((char *)&CarDesigns_variable_3 + v132) + 12 * *(_DWORD *)(v133 + 4 * v84));
                if ((cheat_mode & 0x8000) == 0) {
                  *(float *)a2 = *v95;
                  *(float *)(a2 + 4) = v95[1];
                  *(float *)(a2 + 8) = v95[2];
                } else {
                  *(float *)a2 = *v95 * control_c_variable_195;
                  *(float *)(a2 + 4) = v95[1] * control_c_variable_195;
                  *(float *)(a2 + 8) = v95[2] * control_c_variable_196;
                }
                v96 = rand(v95);
                LODWORD(a1) = rand(v96);
              }
              v144 = rand(a1);
              *(_DWORD *)(a2 + 36) = 1302;
              v97 = ((24 * v144 - (__CFSHL__((24 * v144) >> 31, 15) + ((24 * v144) >> 31 << 15))) >> 15) + 24;
              *(_DWORD *)(a2 + 28) = v97;
              v98 = rand(v97);
              if (v98 < 0x4000)
                *(_BYTE *)(a2 + 37) |= 0x10u;
              v99 = rand(v98);
              if (v99 < 0x4000)
                *(_BYTE *)(a2 + 38) |= 4u;
              if (HIDWORD(v2)) {
                v100 = rand(v99);
                v101 = (-2 - ((6 * v100 - (__CFSHL__((6 * v100) >> 31, 15) + ((6 * v100) >> 31 << 15))) >> 15))
                  * scr_size;
                v102 = (v101 - (__CFSHL__(v101 >> 31, 6) + (v101 >> 31 << 6))) >> 6;
                *(float *)(a2 + 16) = (float)v102;
                v103 = rand(v102);
                if (v84 == 1) {
                  v104 = ((3 * v103 - (__CFSHL__((3 * v103) >> 31, 15) + ((3 * v103) >> 31 << 15))) >> 15) + 3;
                  v145 = v104;
                } else {
                  v104 = (3 * v103 - (__CFSHL__((3 * v103) >> 31, 15) + ((3 * v103) >> 31 << 15))) >> 15;
                  v145 = -3 - v104;
                }
                *(float *)(a2 + 12) = (float)v145;
                v127 = (1.0 - v134) * control_c_variable_198 + control_c_variable_198;
                v105 = rand(v104);
                *(float *)(a2 + 24) = ((double)v105 * v127 * control_c_variable_199 + control_c_variable_198)
                  * (double)scr_size
                  * control_c_variable_200;
                v106 = rand(v105);
                v107 = (double)(int)v106 * v131 * control_c_variable_197 + control_c_variable_194;
                _CHP(v106, HIDWORD(v106));
                *(_DWORD *)(a2 + 32) = (int)v107;
                a1 = rand(v106);
              } else {
                v108 = rand(v99);
                v109 = (20 * v108 - (__CFSHL__((20 * v108) >> 31, 15) + ((20 * v108) >> 31 << 15))) >> 15;
                *(float *)(a2 + 12) = (float)(-15 - v109);
                if (v84) {
                  v110 = rand(v109);
                  if (v84 == 1) {
                    v111 = (15 * v110 - (__CFSHL__((15 * v110) >> 31, 15) + ((15 * v110) >> 31 << 15))) >> 15;
                    v112 = -5;
                  } else {
                    v111 = (40 * v110 - (__CFSHL__((40 * v110) >> 31, 15) + ((40 * v110) >> 31 << 15))) >> 15;
                    v112 = 20;
                  }
                  v146 = v112 - v111;
                } else {
                  v113 = rand(v109);
                  v111 = ((15 * v113 - (__CFSHL__((15 * v113) >> 31, 15) + ((15 * v113) >> 31 << 15))) >> 15) + 5;
                  v146 = v111;
                }
                *(float *)(a2 + 16) = (float)v146;
                v114 = rand(v111);
                v147 = (10 * v114 - (__CFSHL__((10 * v114) >> 31, 15) + ((10 * v114) >> 31 << 15))) >> 15;
                *(float *)(a2 + 20) = (float)v147;
                v115 = rand(v147);
                v120 = ((10 * v115 - (__CFSHL__((10 * v115) >> 31, 15) + ((10 * v115) >> 31 << 15))) >> 15) + 10;
                *(float *)(a2 + 24) = (float)v120;
                v117 = v134 < control_c_variable_207;
                v118 = 0;
                v119 = v134 == control_c_variable_207;
                LOWORD(v120) = v116;
                if (v134 <= control_c_variable_207) {
                  v123 = *(float *)(v2 + 28) > 0.0;
                  v124 = 0;
                  v125 = 0.0 == *(float *)(v2 + 28);
                  LOWORD(v120) = v122;
                  if (*(float *)(v2 + 28) <= 0.0) {
                    a1 = rand(v120);
                    v126 = (double)(int)a1 * v129 * control_c_variable_197 + control_c_variable_208;
                  } else {
                    a1 = rand(v120);
                    v126 = (double)(int)a1 * v130 * control_c_variable_197 + control_c_variable_209;
                  }
                  _CHP(a1, HIDWORD(a1));
                  *(_DWORD *)(a2 + 32) = (int)v126;
                } else {
                  a1 = rand(v120);
                  v121 = (double)(int)a1 * v128 * control_c_variable_197 + control_c_variable_210;
                  _CHP(a1, HIDWORD(a1));
                  *(_DWORD *)(a2 + 32) = (int)v121;
                }
              }
            }
          }
        } else {
          *(_DWORD *)(a2 + 36) = 1302;
          *(_DWORD *)(a2 + 32) = a1 - 1;
        }
      } else if (*(__int16 *)(v2 + 100) <= 108) {
        *(_DWORD *)(a2 + 28) = -1;
        *(_DWORD *)(a2 + 32) = -1;
        *(_BYTE *)(a2 + 40) = 2;
        *(_WORD *)(v2 + 106) = -1;
      }
      goto LABEL_136;
    }
    if ((*(_BYTE *)(a2 + 28) & 3) == 0) {
      v53 = (unsigned __int8)*(_DWORD *)(a2 + 36);
      if (v53 < 0x15) {
        if (!(unsigned __int8)*(_DWORD *)(a2 + 36)) {
          v54 = 21;
          goto LABEL_57;
        }
      } else if (v53 > 0x15) {
        if (v53 <= 0x16) {
          v54 = 23;
        } else {
          if (v53 != 23)
            goto LABEL_56;
          v54 = 0;
        }
      LABEL_57:
        v55 = *(_DWORD *)(a2 + 36);
        LOBYTE(v55) = 0;
        *(_DWORD *)(a2 + 36) = v54 | v55;
        v56 = rand(v54);
        if (v56 < 0x4000)
          *(_BYTE *)(a2 + 37) ^= 0x10u;
        if ((int)rand(v56) < 0x4000)
          *(_BYTE *)(a2 + 38) ^= 4u;
        goto LABEL_61;
      }
    LABEL_56:
      v54 = 22;
      goto LABEL_57;
    }
  LABEL_61:
    v57 = (unsigned __int8)*(_DWORD *)(a2 + 36);
    if ((unsigned __int8)*(_DWORD *)(a2 + 36) && (unsigned __int8)*(_DWORD *)(a2 + 36) < 0x15u
      || (unsigned __int8)*(_DWORD *)(a2 + 36) > 0x17u) {
      *(_DWORD *)(a2 + 36) = 1302;
    }
    *(float *)a2 = *(float *)(a2 + 12) + *(float *)a2;
    *(float *)(a2 + 4) = *(float *)(a2 + 16) + *(float *)(a2 + 4);
    *(float *)(a2 + 8) = *(float *)(a2 + 20) + *(float *)(a2 + 8);
    if (HIDWORD(v2)) {
      a1 = rand(v57);
    } else {
      if (*(int *)(a2 + 28) <= 8) {
        LODWORD(a1) = rand(v57);
        LODWORD(a1) = (((int)(24 * a1 - (__CFSHL__((24 * (int)a1) >> 31, 15) + ((24 * (int)a1) >> 31 << 15))) >> 15) + 10)
          * scr_size;
        LODWORD(a1) = (int)(a1 - (__CFSHL__((int)a1 >> 31, 6) + ((int)a1 >> 31 << 6))) >> 6;
        *(float *)(a2 + 24) = *(float *)(a2 + 24) - (double)(int)a1;
        --*(_DWORD *)(a2 + 28);
        goto LABEL_136;
      }
      LODWORD(a1) = rand(v57);
      LODWORD(a1) = (((int)(8 * a1 - (__CFSHL__((8 * (int)a1) >> 31, 15) + ((8 * (int)a1) >> 31 << 15))) >> 15) + 8)
        * scr_size;
      LODWORD(a1) = (int)(a1 - (__CFSHL__((int)a1 >> 31, 6) + ((int)a1 >> 31 << 6))) >> 6;
      *(float *)(a2 + 24) = (double)(int)a1 + *(float *)(a2 + 24);
    }
    -- * (_DWORD *)(a2 + 28);
  LABEL_136:
    ++v4;
    a2 += 44;
  } while (v4 < 32);*/
}

//-------------------------------------------------------------------------------------------------
//00036280
void calculateseparatedcoordinatesystem(int iChunk, tData *pChunkData)
{
  int iNextChunk; // ecx
  int iCurrentChunk; // eax
  tData *pLocalData; // ebx
  double dInverseTrackLength; // st5
  double dCenterDeltaY; // st6
  float fTangentX; // [esp+0h] [ebp-28h]
  float fTangentY; // [esp+4h] [ebp-24h]

  iNextChunk = iChunk + 1;                      // Calculate next chunk index
  if (iChunk + 1 >= TRAK_LEN)                 // Wrap around if we've reached the end of the track
    iNextChunk = 0;
  iCurrentChunk = iChunk;
  pLocalData = &localdata[iChunk];              // Get pointer to local data for current chunk
  dInverseTrackLength = 1.0 / (pLocalData->fTrackHalfLength * 2.0);// Calculate inverse track length for normalization
  fTangentX = ((TrakPt[iNextChunk].pointAy[2].fX + TrakPt[iNextChunk].pointAy[3].fX) * 0.5f - (TrakPt[iCurrentChunk].pointAy[2].fX + TrakPt[iCurrentChunk].pointAy[3].fX) * 0.5f)
    * (float)dInverseTrackLength;              // Calculate X component of track tangent vector (normalized)
  dCenterDeltaY = (TrakPt[iNextChunk].pointAy[2].fY + TrakPt[iNextChunk].pointAy[3].fY) * 0.5
    - (TrakPt[iCurrentChunk].pointAy[2].fY + TrakPt[iCurrentChunk].pointAy[3].fY) * 0.5;// Calculate Y difference between track centers
  fTangentY = (float)(dInverseTrackLength * dCenterDeltaY);
  pChunkData->pointAy[0].fY = (float)(-(dInverseTrackLength * dCenterDeltaY));// Set up local coordinate system - pointAy[0] is right vector
  pChunkData->pointAy[0].fZ = 0.0;
  pChunkData->pointAy[1].fZ = 0.0;
  pChunkData->pointAy[2].fX = 0.0;              // Set up local coordinate system - pointAy[2] is up vector (0,0,1)
  pChunkData->pointAy[2].fY = 0.0;
  pChunkData->pointAy[2].fZ = 1.0;
  pChunkData->pointAy[0].fX = fTangentX;        // Set up local coordinate system - pointAy[1] is forward vector
  pChunkData->pointAy[1].fX = fTangentY;
  pChunkData->pointAy[1].fY = fTangentX;
  pChunkData->pointAy[3] = pLocalData->pointAy[3];// Copy track position and dimensions from local data
  pChunkData->fTrackHalfLength = pLocalData->fTrackHalfLength;
  pChunkData->fTrackHalfWidth = pLocalData->fTrackHalfWidth;
}

//-------------------------------------------------------------------------------------------------
//00036390
int *findnearsection(int a1, int *a2)
{
  (void)(a1); (void)(a2);
  return 0;
  /*
  int v2; // ecx
  int v3; // edi
  int v4; // edx
  float *v5; // esi
  int v6; // ebp
  long double v7; // st7
  long double v8; // st6
  long double v9; // st5
  long double v10; // st4
  long double v11; // rt0
  long double v12; // st4
  int v13; // edx
  float *v14; // esi
  int v15; // ebp
  long double v16; // st7
  long double v17; // st6
  long double v18; // st5
  long double v19; // st4
  long double v20; // rt2
  long double v21; // st4
  int v22; // ebp
  int v23; // edx
  float *v24; // esi
  int v25; // ebp
  long double v26; // st7
  long double v27; // st6
  long double v28; // st5
  long double v29; // st4
  long double v30; // rt0
  long double v31; // st4
  int v32; // ebp
  float *v33; // esi
  int v34; // edx
  int v35; // ebp
  long double v36; // st7
  long double v37; // st6
  long double v38; // st5
  long double v39; // st4
  long double v40; // rt2
  long double v41; // st4
  int *result; // eax
  __int16 *v44; // [esp+10h] [ebp-6Ch]
  int v45; // [esp+14h] [ebp-68h]
  int v46; // [esp+18h] [ebp-64h]
  int v47; // [esp+1Ch] [ebp-60h]
  int v48; // [esp+20h] [ebp-5Ch]
  float v49; // [esp+24h] [ebp-58h]
  float v50; // [esp+28h] [ebp-54h]
  float v51; // [esp+2Ch] [ebp-50h]
  float v52; // [esp+30h] [ebp-4Ch]
  float v53; // [esp+34h] [ebp-48h]
  float v54; // [esp+38h] [ebp-44h]
  float v55; // [esp+3Ch] [ebp-40h]
  float v56; // [esp+40h] [ebp-3Ch]
  float v57; // [esp+44h] [ebp-38h]
  float v58; // [esp+48h] [ebp-34h]
  float v59; // [esp+4Ch] [ebp-30h]
  float v60; // [esp+50h] [ebp-2Ch]
  float v61; // [esp+54h] [ebp-28h]
  float v62; // [esp+58h] [ebp-24h]
  float v63; // [esp+5Ch] [ebp-20h]
  float v64; // [esp+5Ch] [ebp-20h]
  int v65; // [esp+60h] [ebp-1Ch]
  float v66; // [esp+64h] [ebp-18h]
  float v67; // [esp+64h] [ebp-18h]

  v2 = TRAK_LEN;
  v62 = 1.0e10;
  v61 = 1.0e10;
  v45 = *(_DWORD *)(a1 + 216);
  v3 = -1;
  v44 = &TrakView[4 * v45];
  v48 = *((unsigned __int8 *)v44 + 2) + v45;
  v4 = v45;
  v5 = (float *)((char *)&localdata + 128 * v45);
  if (v45 < v48) {
    v6 = 5 * v45;
    do {
      v7 = *(float *)a1 + v5[9];
      v66 = v7;
      v8 = *(float *)(a1 + 4) + v5[10];
      v9 = fabs(v8);
      v10 = *(float *)(a1 + 8) + v5[11];
      v52 = v5[2] * *(float *)(a1 + 40) + v5[5] * *(float *)(a1 + 44) + v5[8] * *(float *)(a1 + 48);
      v11 = fabs(v10);
      v56 = v8 * v5[5] + v5[2] * v66 + v10 * v5[8];
      v12 = fabs(v7);
      v58 = sqrt(v12 * v12 + v9 * v9 + v11 * v11) - v5[12];
      if ((v56 >= (double)control_c_variable_214 || GroundColour_variable_4[v6] >= 0) && v58 < (double)v62) {
        v62 = v58;
        if (v4 < v2) {
          if (v4 >= 0)
            *(_DWORD *)(a1 + 216) = v4;
          else
            *(_DWORD *)(a1 + 216) = v2 + v4;
        } else {
          *(_DWORD *)(a1 + 216) = v4 - v2;
        }
      }
      if ((v52 * control_c_variable_213 + control_c_variable_215 <= v56 || GroundColour_variable_4[v6] >= 0)
        && v58 < (double)v61) {
        v61 = v58;
        if (v4 < v2) {
          if (v4 >= 0)
            v3 = v4;
          else
            v3 = v4 + v2;
        } else {
          v3 = v4 - v2;
        }
      }
      if (v4 == v2 - 1)
        v5 = (float *)&localdata;
      else
        v5 += 32;
      ++v4;
      v6 += 5;
    } while (v4 < v48);
  }
  v46 = v45 - *((unsigned __int8 *)v44 + 6);
  v13 = v45;
  v14 = (float *)((char *)&localdata + 128 * v45);
  if (v45 > v46) {
    v15 = 5 * v45;
    do {
      v16 = *(float *)a1 + v14[9];
      v63 = v16;
      v17 = *(float *)(a1 + 4) + v14[10];
      v18 = fabs(v17);
      v19 = *(float *)(a1 + 8) + v14[11];
      v49 = v14[2] * *(float *)(a1 + 40) + v14[5] * *(float *)(a1 + 44) + v14[8] * *(float *)(a1 + 48);
      v20 = fabs(v19);
      v55 = v17 * v14[5] + v14[2] * v63 + v19 * v14[8];
      v21 = fabs(v16);
      v60 = sqrt(v21 * v21 + v18 * v18 + v20 * v20) - v14[12];
      if ((v55 >= (double)control_c_variable_214 || GroundColour_variable_4[v15] >= 0) && v60 < (double)v62) {
        v62 = v60;
        if (v13 < v2) {
          if (v13 >= 0)
            *(_DWORD *)(a1 + 216) = v13;
          else
            *(_DWORD *)(a1 + 216) = v2 + v13;
        } else {
          *(_DWORD *)(a1 + 216) = v13 - v2;
        }
      }
      if ((v49 * control_c_variable_213 + control_c_variable_215 <= v55 || GroundColour_variable_4[v15] >= 0)
        && v60 < (double)v61) {
        v61 = v60;
        if (v13 < v2) {
          if (v13 >= 0)
            v3 = v13;
          else
            v3 = v13 + v2;
        } else {
          v3 = v13 - v2;
        }
      }
      if (v13)
        v14 -= 32;
      else
        v14 = (float *)((char *)&localdata + 128 * v2 - 128);
      --v13;
      v15 -= 5;
    } while (v13 > v46);
  }
  if ((TrakColour_variable_4[24 * v45] & 2) == 0) {
    v22 = *v44;
    v65 = *((unsigned __int8 *)v44 + 3) + v22;
    v23 = v22;
    v24 = (float *)((char *)&localdata + 128 * v22);
    if (v22 < v65) {
      v25 = 5 * v22;
      do {
        v26 = *(float *)a1 + v24[9];
        v64 = v26;
        v27 = *(float *)(a1 + 4) + v24[10];
        v28 = fabs(v27);
        v29 = *(float *)(a1 + 8) + v24[11];
        v50 = v24[2] * *(float *)(a1 + 40) + v24[5] * *(float *)(a1 + 44) + v24[8] * *(float *)(a1 + 48);
        v30 = fabs(v29);
        v54 = v27 * v24[5] + v24[2] * v64 + v29 * v24[8];
        v31 = fabs(v26);
        v57 = sqrt(v31 * v31 + v28 * v28 + v30 * v30) - v24[12];
        if ((v54 >= (double)control_c_variable_214 || GroundColour_variable_4[v25] >= 0) && v57 < (double)v62) {
          v62 = v57;
          if (v23 < v2) {
            if (v23 >= 0)
              *(_DWORD *)(a1 + 216) = v23;
            else
              *(_DWORD *)(a1 + 216) = v2 + v23;
          } else {
            *(_DWORD *)(a1 + 216) = v23 - v2;
          }
        }
        if ((v50 * control_c_variable_213 + control_c_variable_215 <= v54 || GroundColour_variable_4[v25] >= 0)
          && v57 < (double)v61) {
          v61 = v57;
          if (v23 < v2) {
            if (v23 >= 0)
              v3 = v23;
            else
              v3 = v23 + v2;
          } else {
            v3 = v23 - v2;
          }
        }
        if (v23 == v2 - 1)
          v24 = (float *)&localdata;
        else
          v24 += 32;
        ++v23;
        v25 += 5;
      } while (v23 < v65);
    }
    v32 = v44[2];
    v47 = v32 - *((unsigned __int8 *)v44 + 7);
    v33 = (float *)((char *)&localdata + 128 * v32);
    v34 = v32;
    if (v32 > v47) {
      v35 = 5 * v32;
      do {
        v36 = *(float *)a1 + v33[9];
        v67 = v36;
        v37 = *(float *)(a1 + 4) + v33[10];
        v38 = fabs(v37);
        v39 = *(float *)(a1 + 8) + v33[11];
        v51 = v33[2] * *(float *)(a1 + 40) + v33[5] * *(float *)(a1 + 44) + v33[8] * *(float *)(a1 + 48);
        v40 = fabs(v39);
        v53 = v37 * v33[5] + v33[2] * v67 + v39 * v33[8];
        v41 = fabs(v36);
        v59 = sqrt(v41 * v41 + v38 * v38 + v40 * v40) - v33[12];
        if ((v53 >= (double)control_c_variable_214 || GroundColour_variable_4[v35] >= 0) && v59 < (double)v62) {
          v62 = v59;
          if (v34 < v2) {
            if (v34 >= 0)
              *(_DWORD *)(a1 + 216) = v34;
            else
              *(_DWORD *)(a1 + 216) = v2 + v34;
          } else {
            *(_DWORD *)(a1 + 216) = v34 - v2;
          }
        }
        if ((v51 * control_c_variable_213 + control_c_variable_215 <= v53 || GroundColour_variable_4[v35] >= 0)
          && v59 < (double)v61) {
          v61 = v59;
          if (v34 < v2) {
            if (v34 >= 0)
              v3 = v34;
            else
              v3 = v34 + v2;
          } else {
            v3 = v34 - v2;
          }
        }
        if (v34)
          v33 -= 32;
        else
          v33 = (float *)((char *)&localdata + 128 * v2 - 128);
        --v34;
        v35 -= 5;
      } while (v34 > v47);
    }
  }
  result = a2;
  *a2 = v3;
  TRAK_LEN = v2;
  return result;*/
}

//-------------------------------------------------------------------------------------------------
//000369C0
void dozoomstuff(int a1)
{
  (void)(a1);
  /*
  int v1; // ebx
  int v3; // eax
  int v4; // esi
  double v5; // st7
  int v6; // edx
  double v7; // st7
  int v8; // edx

  v1 = champ_mode;
  if (champ_mode >= 16)
    --champ_count;
  v3 = a1;
  v4 = game_count[a1];
  if (v4 <= 0) {
    if (v4 >= 0) {
      if (champ_mode)
        v7 = *(float *)&game_scale[a1] * control_c_variable_217;
      else
        v7 = *(float *)&game_scale[a1] * control_c_variable_216;
      *(float *)&game_scale[a1] = v7;
      v8 = a1;
      if (*(float *)&game_scale[v8] < (double)control_c_variable_218) {
        game_scale[v8] = 1115684864;
        if (v1) {
          game_count[v8] = 36;
          champ_mode = v1;
          return;
        }
        game_count[v8] = 72;
      }
    } else if (v4 > -2) {
      v5 = champ_mode
        ? *(float *)&game_scale[a1] * control_c_variable_220
        : *(float *)&game_scale[a1] * control_c_variable_219;
      *(float *)&game_scale[a1] = v5;
      v6 = a1;
      if (*(float *)&game_scale[v6] > (double)control_c_variable_221) {
        game_scale[v6] = 1191182336;
        game_count[v6] = -2;
        sub_on[v6] = 0;
        champ_mode = v1;
        return;
      }
    }
  } else {
    game_count[v3] = v4 - 1;
    if (v4 == 1 && game_scale[v3] == 1115684864)
      game_count[v3] = -1;
  }
  champ_mode = v1;*/
}

//-------------------------------------------------------------------------------------------------
//00036B10
int findcardistance(int a1, float a2)
{
  (void)(a1); (void)(a2);
  return 0;
  /*
  int v5; // esi
  int v6; // ebx
  unsigned int v7; // edx
  double v8; // st7
  double v9; // st7
  float v11; // [esp+4h] [ebp-24h]
  float v12; // [esp+8h] [ebp-20h]
  float v13; // [esp+Ch] [ebp-1Ch]

  v5 = -1;
  v6 = 0;
  v11 = (double)(averagesectionlen * Car_variable_3[154 * a1]) + Car[77 * a1];
  if (numcars > 0) {
    v7 = 0;
    do {
      if (v6 != a1 && Car_variable_23[v7] > 0 && Car_variable_17[v7 / 4] == 3 && !Car_variable_48[v7 / 4]) {
        v8 = (double)(averagesectionlen * Car_variable_3[v7 / 2]) + Car[v7 / 4];
        v13 = v8;
        if (v8 < v11)
          v13 = (double)totaltrackdistance + v13;
        v9 = v13 - v11;
        if (v9 < a2) {
          v5 = v6;
          v12 = v9;
          a2 = v12;
        }
      }
      ++v6;
      v7 += 308;
    } while (v6 < numcars);
  }
  return v5;*/
}

//-------------------------------------------------------------------------------------------------

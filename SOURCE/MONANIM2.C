/***********************************************************************
        (C) Copyright 1995 by 47-TEK, Inc.

        This program is copyrighted by 47-TEK, Inc. and is  not licensed
        to you under any conditions.  You may not distribute, duplicate,
        or  publish the source code of this program in any form.  You
        may  not incorporate this code in any form in derivative  works.
      

        47-Tek is a registered trademark of 47-TEK, Inc.
        47-TEK Specifically disclaims any implied Warranty of Mer-
        chantability or fitness for a particular use. 47-TEK,  Inc.
        does not Warrant that the operation of the program will be
        uninterrupted or error free.

************************************************************************

Program:        Goman95
File:           monanim2.c
Author:         Bruce Abe
Date:           9-26-95
Version:        1.0003



************************************************************************
REVISION HISTORY        (Add Edits and History to top of list).

Edited By:      Bruce Abe
Edited Date:    11-1-95
Changes:
                Added some typecasting to get rid of bounteous warnings.

Edited By:      Bruce Abe
Edited Date:    10-4-95
Changes:
                changed VERSION_NUMBER from 1.0002 to 1.0003
                modified dont get back up animation, so the monster
                can lay down and die at exactly the right frame.

Edited By:      Bo Yuan 
Edited Date:    9-28-95
Changes:
                added three system header files

Edited By:      Bruce Abe
Edited Date:    9-28-95
Changes:
                changed VERSION_NUMBER from 1.0001 to 1.0002
                added dont get back up animation, so the monster
                can lay down and die.


Edited By:      Bruce Abe
Edited Date:    9-27-95
Changes:
                changed VERSION_NUMBER from 1.0 to 1.0001
                changed monster plasma attacks, so that beams
				come from the right place, and go in the right direction.

***********************************************************************/
#pragma warning( disable : 4244)
#define BruceNotSpudde
//#define BruceSndSystem
#ifdef MINIWIN
#include "miniwin/windows.h"
#else
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#endif

#ifndef __psx__
#define XAFnotXBF
#endif
#define Binary

//replace rl with rl2d3d.h. By Sanfo 5/18/96
//#include "rl.h"
#include "rl2d3d.h"

//#include "qbmp.h"
//#include "altbmp.h"
#include "keycom.h"
#include "boink.h"
#include "Monmove.h"
#include "timing.h"
//#include "psxsound.h"
#include "spritlib.h"
#include "plasma.h"
#include "config.h"
#include "ybsnd.h"
#include "Robotanim.h"
#include "monanim.h"
#include "psystem.h"
#include "gosys.h"
#include "ichars.h"
#include "global.h"
#include "tekanim.h"

#ifndef __psx__
#define PC
#endif
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef PC
#include <math.h>
#ifndef BruceNotSpudde
#define Sound
#endif
#endif

#ifdef PC                //1
#include <math.h>


#include <time.h>
#else                    //1
#ifdef __cd__    //2
#define Sound
#ifndef BruceSndSystem //3
typedef struct {
    long prog;                      // program no 
    long pitch;                     // pitch 
} KON;
extern KON voice[]; 
#endif                  //3
        
#endif                  //2

#endif                  //1
//extern RLFrame Robotspew;
extern struct _moving_object_data_ MonsterData;
extern RLFrame monstspew;
//extern PlasmaData Robotspewdata;
extern ZappaData monstspewdata;
//extern Psystem *monsterplasma;
char* ConstructLevelName(char* name);
extern RLFrame Robotframe;
extern RLFrame monstframe;
extern int monthink;
extern int RobotEngy;
extern RLFrame MonsterScaleFrame;
#define MaxMnstEngy 65536
#define MaxMnstLife 100
static int InitialMonsterLife = 100;
int MnstEngy=MaxMnstEngy;
extern int RobotLife;
extern int MnstLife;
extern int MonsterMotionDamage;

RLValue MonsterArmor=RLVal(1.0);
//int MonsterAttackFerocity=10;
int ZappaHowLong;
int ZappaOnScreen;
extern struct _moving_object_data_ MonsterZappaData;
extern HotSpot BombSpot;
extern HotSpot2 MonsterZappaSpot;

extern RLValue MonsterZapMass;
extern int MonsterZapDamage;
extern RLValue MonsterZapRadius;
extern RLValue MonsterZapLength;

RLValue RoggoshTripleZapMass = RLVal(30);
int RoggoshTripleZapDamage = 20;
RLValue RoggoshTripleZapRadius = RLVal(1.0);
RLValue RoggoshTripleZapLength = RLVal(7.0);

RLValue TolgoWideBeamMass = RLVal(30);
int TolgoWideBeamDamage = 20;
RLValue TolgoWideBeamRadius = RLVal(1.0);
RLValue TolgoWideBeamLength = RLVal(7.0);

RLValue ShagtoqGroundZapMass = RLVal(30);
int ShagtoqGroundZapDamage = 20;
RLValue ShagtoqGroundZapRadius = RLVal(1.0);
RLValue ShagtoqGroundZapLength = RLVal(7.0);

RLValue ShagtoqSpewMass = RLVal(30);
int ShagtoqSpewDamage = 20;
RLValue ShagtoqSpewRadius = RLVal(1.0);
RLValue ShagtoqSpewLength = RLVal(7.0);

RLValue NeallothDiveBombMass = RLVal(30);
int NeallothDiveBombDamage = 20;
RLValue NeallothDiveBombRadius = RLVal(1.0);
RLValue NeallothDiveBombLength = RLVal(7.0);

RLValue GaingrisTripleZapMass = RLVal(30);
int GaingrisTripleZapDamage = 20;
RLValue GaingrisTripleZapRadius = RLVal(1.0);
RLValue GaingrisTripleZapLength = RLVal(7.0);

RLValue KothosJumpAttackMass = RLVal(30);
int KothosJumpAttackDamage = 20;
RLValue KothosJumpAttackRadius = RLVal(1.0);
RLValue KothosJumpAttackLength = RLVal(7.0);

int MonsterFalldownThreshold=5;



extern RLValue GaingrisRadius;
extern RLValue GaingrisNukeVelocity;
extern RLValue GaingrisNukeInitRadius;
extern RLValue GaingrisNukeMaxRadius;

//extern RLValue KothosRadius;
extern RLValue KothosSnowballInitRadius;
extern RLValue KothosSnowballGrowthRate;
extern RLValue KothosSnowballDuration;
extern int KothosSnowballDamage;
extern RLValue KSnowballGradientFactor;


int NumMonsterTaunts;
static int StageNumber = 0;
RLVector MonsterPlasmaDisplacement={0,0,0};
RLValue NRingsHowLong[NumberOfSixShooters];
//RLValue NRingSpeed;
RLVector ShagtoqTarget;
RLVector LightningDirection;
RLVector KothosSnowballVelocity;
RLFrame BombSphere;
RLValue BombHowLong;
extern RLFrame behindthescene;
extern Psystem *NeallothRings;
extern struct _moving_object_data_ NeallothRingsData[NumberOfSixShooters];
extern struct _moving_object_data_ BombData;
extern RLValue MonsterFallDownSpin;
//static int HighAttack1Ferocity = 10;
//static int MediumAttack1Ferocity = 7;
//static int LowAttack1Ferocity = 3;
//static int MediumAttack2Ferocity = 7;
//static int LowAttack2Ferocity = 3;
//static int SpecialAttack1Ferocity = 30;
//static int SpecialAttack2Ferocity = 30;
//static int JumpAttack1Ferocity = 7;
//static int JumpAttack2Ferocity = 7;
//static int ThrowObjectFerocity = 5;
extern char* ConstructMonsterName(char* name);



static RLValue  MonsterWalkForwardDistance  = RLVal(2.2888);

static RLValue  MonsterWalkBackDistance  = RLVal(2.36);
static RLValue  MonsterSideStepLeftDistance  = RLVal(1.99);
static RLValue  MonsterSideStepRightDistance  = RLVal(1.99);
static RLValue  MonsterIntoRunDistance  = RLVal(0.83);
//efine MonsterIntoRunDistance 27500

static RLValue  MonsterRunDistance  = RLVal(3.34);
static RLValue  MonsterSkidDistance  = RLVal(4);
static RLValue  MonsterKnockDown1Distance  = RLVal(3);
static RLValue  MonsterKnockDown2Distance  = RLVal(3);
static RLValue  MonsterKnockDown3Distance  = RLVal(3);

static int  MonsterPause1EnergyDrain            =0;
static int  MonsterWalkForwardEnergyDrain       =0;
static int  MonsterWalkBackEnergyDrain          =0;
static int  MonsterJumpFirstEnergyDrain         =0;
static int  MonsterJumpFreezeEnergyDrain        =0;
static int  MonsterJumpLastEnergyDrain          =0;
static int  MonsterJumpStopEnergyDrain          =0;
static int  MonsterSkidEnergyDrain              =0;
static int  MonsterIntoTravelEnergyDrain        =0;
static int  MonsterTravelEnergyDrain     =0;
static int  MonsterOutoTravelEnergyDrain		=0;
//static int  MonsterTravelBackEnergyDrain        120;
static int  MonsterIntoIntoRunEnergyDrain       =0;
static int  MonsterIntoRunEnergyDrain           =0;
static int  MonsterRunEnergyDrain               =0;
//static int  MonsterHighAttack1EnergyDrain       300;
static int  MonsterHighAttack1EnergyDrain       =30;
static int  MonsterMediumAttack1EnergyDrain     =200;
static int  MonsterLowAttack1EnergyDrain        =60;
static int  MonsterHighAttack2EnergyDrain       =300;
static int  MonsterMediumAttack2EnergyDrain     =200;
static int  MonsterLowAttack2EnergyDrain        =60;
static int  MonsterJumpAttack1EnergyDrain       =90;
static int  MonsterJumpAttack2EnergyDrain       =90;
static int  MonsterSpecialAttack1EnergyDrain    =400;
static int  MonsterSpecialAttack2EnergyDrain    =400;
static int  MonsterBlockMediumFirstEnergyDrain  =0;
static int  MonsterBlockMediumFreezeEnergyDrain =0;
static int  MonsterBlockMediumLastEnergyDrain   =0;
static int  MonsterChestHitLeft2EnergyDrain     =0;
static int  MonsterKnockDown2EnergyDrain        =0;
static int  MonsterGetBackUp2EnergyDrain        =0;
static int  MonsterPickUpObjectFirstEnergyDrain =0;
static int  MonsterPickUpObjectFreezeEnergyDrain= 0;
static int  MonsterPickUpObjectLastEnergyDrain  =0;
static int  MonsterThrowObjectEnergyDrain       =200;
static int  MonsterTaunt1EnergyDrain            =0;
static int  MonsterTaunt2EnergyDrain            =0;
                                                

static int  MonsterPause1EnergyMinimum           = 0;
static int  MonsterWalkForwardEnergyMinimum      = 0;
static int  MonsterWalkBackEnergyMinimum         = 20;
static int  MonsterJumpFirstEnergyMinimum        = 100;
static int  MonsterJumpFreezeEnergyMinimum       = 10;
static int  MonsterJumpLastEnergyMinimum         = 30;
static int  MonsterJumpStopEnergyMinimum         = 40;
static int  MonsterSkidEnergyMinimum             = 0;
static int  MonsterIntoTravelEnergyMinimum       = 0;
static int  MonsterTravelEnergyMinimum		     = 0;
static int  MonsterOutoTravelEnergyMinimum       = 0;
static int  MonsterTravelBackEnergyMinimum       = 120;
static int  MonsterIntoIntoRunEnergyMinimum      = 15;
static int  MonsterIntoRunEnergyMinimum          = 20;
static int  MonsterRunEnergyMinimum              = 60;
static int  MonsterHighAttack1EnergyMinimum      = 6000;
static int  MonsterMediumAttack1EnergyMinimum    = 4000;
static int  MonsterLowAttack1EnergyMinimum       = 1200;
static int  MonsterHighAttack2EnergyMinimum      = 6000;
static int  MonsterMediumAttack2EnergyMinimum    = 4000;
static int  MonsterLowAttack2EnergyMinimum       = 1200;
static int  MonsterJumpAttack1EnergyMinimum      = 1800;
static int  MonsterJumpAttack2EnergyMinimum      = 1800;
static int  MonsterSpecialAttack1EnergyMinimum   = 8000;
static int  MonsterSpecialAttack2EnergyMinimum   = 8000;
static int  MonsterBlockMediumFirstEnergyMinimum = 0;
static int  MonsterBlockMediumFreezeEnergyMinimum= 0;
static int  MonsterBlockMediumLastEnergyMinimum  = 0;
static int  MonsterChestHitLeft2EnergyMinimum    = 0;
static int  MonsterKnockDown2EnergyMinimum       = 0;
static int  MonsterGetBackUp2EnergyMinimum       = 0;
static int  MonsterPickUpObjectFirstEnergyMinimum= 0;
static int  MonsterPickUpObjectFreezeEnergyMinimum= 0;
static int  MonsterPickUpObjectLastEnergyMinimum  =0;
static int  MonsterThrowObjectEnergyMinimum       =4000;
static int  MonsterTaunt1EnergyMinimum            =0;
static int  MonsterTaunt2EnergyMinimum            =0;
static int TailZapDuration = 10;
static RLValue TailZapRotation = RLVal(1.57);
static int RoggoshHomerDuration = 38;
static int TolgoPunchDamage = 10;
static int ShagtoqSpewDuration = 30;
static int NeallothEyeboltDuration = 15;
static int GaingrisMultiblastDuration = 7;
static int RoggoshTripleDuration = 10;
static int KothosJumpAttackDuration = 21;
static int TolgoWideBeamDuration = 27;
static int ShagtoqIntoGroundDuration = 10;
static int ShagtoqOutOfGroundDuration = 13;
static int NeallothRingsDuration = 27;
int NeallothRingsDamage = 10;
extern RLValue NeallothRingsRadius;
RLValue NeallothRingsSpeed = RLVal(0.3);
static int GaingrisNukeDamage = 40;
static int MonsterEnergyToLifeConversion = 16;



/* change 3d model object file extension
 * added by Sanfo 7/3/1996
 */
#define XAF(name)   name##".xaf"
#define X(name)     name##".x"

#define MODEL(name) X(name)
/*comment end*/


#define MonsterPause1FileName           (ConstructMonsterName(MODEL("101")))
#define MonsterPause2FileName           (ConstructMonsterName(MODEL("102")))
#define MonsterWalkForwardFileName      (ConstructMonsterName(MODEL("103")))
#define MonsterWalkBackFileName         (ConstructMonsterName(MODEL("104")))
#define MonsterSideStepLeftFileName     (ConstructMonsterName(MODEL("105")))
#define MonsterSideStepRightFileName    (ConstructMonsterName(MODEL("106")))
#define MonsterTurnLeftFileName         (ConstructMonsterName(MODEL("107")))
#define MonsterTurnRightFileName        (ConstructMonsterName(MODEL("108")))
#define MonsterJumpFileName             (ConstructMonsterName(MODEL("109")))

#define MonsterSkidFileName             (ConstructMonsterName(MODEL("110")))
#define MonsterTravelFileName           (ConstructMonsterName(MODEL("111")))

#define MonsterIntoRunFileName          (ConstructMonsterName(MODEL("115")))
#define MonsterRunFileName              (ConstructMonsterName(MODEL("116")))
#define MonsterHighAttack1FileName      (ConstructMonsterName(MODEL("117")))
#define MonsterMediumAttack1FileName    (ConstructMonsterName(MODEL("118")))
#define MonsterLowAttack1FileName       (ConstructMonsterName(MODEL("119")))
#define MonsterHighAttack2FileName      (ConstructMonsterName(MODEL("120")))
#define MonsterMediumAttack2FileName    (ConstructMonsterName(MODEL("121")))
#define MonsterLowAttack2FileName       (ConstructMonsterName(MODEL("122")))
#define MonsterJumpAttack1FileName      (ConstructMonsterName(MODEL("123")))
#define MonsterJumpAttack2FileName      (ConstructMonsterName(MODEL("124")))
#define MonsterSpecialAttack1FileName   (ConstructMonsterName(MODEL("125")))
#define MonsterSpecialAttack2FileName   (ConstructMonsterName(MODEL("126")))

#define MonsterBlockHighFileName        (ConstructMonsterName(MODEL("127")))
#define MonsterBlockMediumFileName      (ConstructMonsterName(MODEL("128")))
#define MonsterBlockLowFileName         (ConstructMonsterName(MODEL("129")))
#define MonsterHeadHitLeft1FileName     (ConstructMonsterName(MODEL("130")))
#define MonsterHeadHitRight1FileName    (ConstructMonsterName(MODEL("131")))
#define MonsterHeadHitLeft2FileName     (ConstructMonsterName(MODEL("132")))
#define MonsterHeadHitRight2FileName    (ConstructMonsterName(MODEL("133")))
#define MonsterChestHitLeft1FileName    (ConstructMonsterName(MODEL("134")))
#define MonsterChestHitRight1FileName   (ConstructMonsterName(MODEL("135")))
#define MonsterChestHitLeft2FileName    (ConstructMonsterName(MODEL("136")))
#define MonsterChestHitRight2FileName   (ConstructMonsterName(MODEL("137")))
#define MonsterLegHitLeft1FileName      (ConstructMonsterName(MODEL("138")))
#define MonsterLegHitRight1FileName     (ConstructMonsterName(MODEL("139")))
#define MonsterLegHitLeft2FileName      (ConstructMonsterName(MODEL("140")))
#define MonsterLegHitRight2FileName     (ConstructMonsterName(MODEL("141")))
#define MonsterKnockDown1FileName       (ConstructMonsterName(MODEL("142")))
#define MonsterKnockDown2FileName       (ConstructMonsterName(MODEL("143")))
#define MonsterKnockDown3FileName       (ConstructMonsterName(MODEL("144")))
#define MonsterTaunt1FileName           (ConstructMonsterName(MODEL("145")))
#define MonsterTaunt2FileName           (ConstructMonsterName(MODEL("146")))
#define MonsterPickUpObjectFileName     (ConstructMonsterName(MODEL("147")))
#define MonsterPauseWithObjectFileName  (ConstructMonsterName(MODEL("148")))
#define MonsterThrowObjectFileName      (ConstructMonsterName(MODEL("149")))


#define MonsterPause1NumFrames RLVal(30)
#define MonsterPause2NumFrames RLVal(30)
#define MonsterWalkForwardNumFrames RLVal(30)
#define MonsterWalkBackNumFrames RLVal(30)
#define MonsterSideStepLeftNumFrames RLVal(30)
#define MonsterSideStepRightNumFrames RLVal(30)
#define MonsterTurnLeftNumFrames RLVal(20)
#define MonsterTurnRightNumFrames RLVal(20)
#define MonsterJumpNumFrames RLVal(30)

#define MonsterSkidNumFrames RLVal(20)
#define MonsterTravelNumFrames RLVal(65)

#define MonsterIntoRunNumFrames RLVal(15)
#define MonsterRunNumFrames RLVal(30)
#define MonsterHighAttack1NumFrames RLVal(30)
#define MonsterMediumAttack1NumFrames RLVal(40)
#define MonsterLowAttack1NumFrames RLVal(15)
#define MonsterHighAttack2NumFrames RLVal(30)
#define MonsterMediumAttack2NumFrames RLVal(35)
#define MonsterLowAttack2NumFrames RLVal(20)
#define MonsterJumpAttack1NumFrames RLVal(20)
#define MonsterJumpAttack2NumFrames RLVal(20)
#define MonsterSpecialAttack1NumFrames RLVal(75)
#define MonsterSpecialAttack2NumFrames RLVal(55)

#define MonsterBlockHighNumFrames RLVal(10)
#define MonsterBlockMediumNumFrames RLVal(10)
#define MonsterBlockLowNumFrames RLVal(10)
#define MonsterHeadHitLeft1NumFrames RLVal(10)
#define MonsterHeadHitRight1NumFrames RLVal(10)
#define MonsterHeadHitLeft2NumFrames RLVal(10)
#define MonsterHeadHitRight2NumFrames RLVal(10)
#define MonsterChestHitLeft1NumFrames RLVal(10)
#define MonsterChestHitRight1NumFrames RLVal(10)
#define MonsterChestHitLeft2NumFrames RLVal(10)
#define MonsterChestHitRight2NumFrames RLVal(10)
#define MonsterLegHitLeft1NumFrames RLVal(10)
#define MonsterLegHitRight1NumFrames RLVal(10)
#define MonsterLegHitLeft2NumFrames RLVal(10)
#define MonsterLegHitRight2NumFrames RLVal(10)
#define MonsterKnockDown1NumFrames RLVal(60)
#define MonsterKnockDown2NumFrames RLVal(60)
#define MonsterKnockDown3NumFrames RLVal(60)
#define MonsterTaunt1NumFrames RLVal(70)
#define MonsterTaunt2NumFrames RLVal(60)
#define MonsterPickUpObjectNumFrames RLVal(30)
#define MonsterPauseWithObjectNumFrames RLVal(30)
#define MonsterThrowObjectNumFrames RLVal(30)

#define MonsterPause1Distance RLVal(0)
#define MonsterPause2Distance RLVal(0)

//#define MonsterWalkForwardDistance RLVal(2.36)
#define MonsterTurnLeftDistance RLVal(0)
#define MonsterTurnRightDistance RLVal(0)
#define MonsterJumpDistance RLVal(0)

#define MonsterTravelForwardDistance RLVal(0)


#define MonsterHighAttack1Distance RLVal(0)
#define MonsterMediumAttack1Distance RLVal(0)
#define MonsterLowAttack1Distance RLVal(0)
#define MonsterHighAttack2Distance RLVal(0)
#define MonsterMediumAttack2Distance RLVal(0)
#define MonsterLowAttack2Distance RLVal(0)
#define MonsterJumpAttack1Distance RLVal(0)
#define MonsterJumpAttack2Distance RLVal(0)
#define MonsterSpecialAttack1Distance RLVal(0)
#define MonsterSpecialAttack2Distance RLVal(0)

#define MonsterBlockHighDistance RLVal(0)
#define MonsterBlockMediumDistance RLVal(0)
#define MonsterBlockLowDistance RLVal(0)
#define MonsterHeadHitLeft1Distance RLVal(0)
#define MonsterHeadHitRight1Distance RLVal(0)
#define MonsterHeadHitLeft2Distance RLVal(0)
#define MonsterHeadHitRight2Distance RLVal(0)
#define MonsterChestHitLeft1Distance RLVal(0)
#define MonsterChestHitRight1Distance RLVal(0)
#define MonsterChestHitLeft2Distance RLVal(0)
#define MonsterChestHitRight2Distance RLVal(0)
#define MonsterLegHitLeft1Distance RLVal(0)
#define MonsterLegHitRight1Distance RLVal(0)
#define MonsterLegHitLeft2Distance RLVal(0)
#define MonsterLegHitRight2Distance RLVal(0)
#define MonsterTaunt1Distance RLVal(0)
#define MonsterTaunt2Distance RLVal(0)
#define MonsterPickUpObjectDistance RLVal(0)
#define MonsterPauseWithObjectDistance RLVal(0)
#define MonsterThrowObjectDistance RLVal(0)
#define MonsterTravelDistance RLVal(0)

#define MonsterIntoRunStartFrame RLVal(4)
#define MonsterJumpStopFrame RLVal(23)

#define MonsterKnockDown1StopFrame RLVal(29)
#define MonsterKnockDown2StopFrame RLVal(29)
#define MonsterKnockDown3StopFrame RLVal(29)
#define MonsterHeadHitLeft2StopFrame RLVal(6)
#define MonsterHeadHitRight2StopFrame RLVal(6)
#define MonsterChestHitLeft2StopFrame RLVal(6)
#define MonsterChestHitRight2StopFrame RLVal(6)
#define MonsterLegHitLeft2StopFrame RLVal(6)
#define MonsterLegHitRight2StopFrame RLVal(6)
RLValue MonsterTravelFirstFrame = RLVal(15);
RLValue MonsterTravelLastFrame = RLVal(32);



#define MonsterTurnLeftFreezeFrame RLVal(10)
#define MonsterTurnRightFreezeFrame RLVal(10)
#define MonsterJumpFreezeFrame RLVal(15)
#define MonsterBlockHighFreezeFrame RLVal(6)
#define MonsterBlockMediumFreezeFrame RLVal(5)
#define MonsterBlockLowFreezeFrame RLVal(6)
#define MonsterPickUpObjectFreezeFrame RLVal(16)

#define MonsterHighAttack1HitFrame RLVal(12)
#define MonsterHighAttack2HitFrame RLVal(14)
#define MonsterThrowObjectHitFrame RLVal(16)






//This just in, late breaking flash, turning will be handled semi-independently from movement.
//It will check to see that the movement isn't in a bad MonsterAnimationState, and will handle turning from there.
#define MonsterPause1             0
#define MonsterWalkForward        1
#define MonsterWalkBack           2
#define MonsterJumpFirst          3
#define MonsterJumpFreeze         4
#define MonsterJumpLast           5
#define MonsterJumpStop           6
#define MonsterSkid               7
#define MonsterIntoIntoRun        8
#define MonsterIntoRun            9
#define MonsterRun                10
#define MonsterHighAttack1        11
#define MonsterMediumAttack1      12
#define MonsterLowAttack1         13
#define MonsterMediumAttack2      14
#define MonsterLowAttack2         15
#define MonsterJumpAttack1        16
#define MonsterJumpAttack2        17
#define MonsterSpecialAttack1     18
#define MonsterBlockMediumFirst   19
#define MonsterBlockMediumFreeze  20
#define MonsterBlockMediumLast    21
#define MonsterChestHitLeft2      22
#define MonsterKnockDown2         23
#define MonsterGetBackUp2         24
#define MonsterPickUpObjectFirst  25
#define MonsterPickUpObjectFreeze 26
#define MonsterPickUpObjectLast   27
#define MonsterThrowObject        28
#define MonsterDontGetBackUp2     29
#define MonsterTaunt1             30
#define MonsterSpecialAttack2     31
#define MonsterAllDead            32
#define MonsterTravel			  33
#define MonsterTaunt2             34



/*
MonsterPause1            
MonsterPause2            
MonsterWalkForward       
MonsterWalkBack          
MonsterSideStepLeft      
MonsterSideStepRight     
MonsterTurnLeftFirst     
MonsterTurnLeftFreeze    
MonsterTurnLeftLast      
MonsterTurnRightFirst    
MonsterTurnRightFreeze   
MonsterTurnRightLast     
MonsterJumpFirst         
MonsterJumpFreeze        
MonsterJumpLast          
MonsterJumpStop          
MonsterAcrobatic1        
MonsterAcrobatic1End     
MonsterAcrobatic2        
MonsterAcrobatic2End     
MonsterSkid              
MonsterTravelForward     
MonsterTravelBack        
MonsterTravelLeft        
MonsterTravelRight       
MonsterIntoIntoRun       
MonsterIntoRun           
MonsterRun               
MonsterHighAttack1       
MonsterMediumAttack1     
MonsterLowAttack1        
MonsterSuperJab1         
MonsterHighAttack2       
MonsterMediumAttack2     
MonsterLowAttack2        
MonsterSuperKick2        
MonsterJumpAttack1       
MonsterJumpAttack2       
MonsterSpecialAttack1    
MonsterSpecialAttack2    
MonsterSpecialAttack3    
MonsterBlockHighFirst    
MonsterBlockHighFreeze   
MonsterBlockHighLast     
MonsterBlockMediumFirst  
MonsterBlockMediumFreeze 
MonsterBlockMediumLast   
MonsterBlockLowFirst     
MonsterBlockLowFreeze    
MonsterBlockLowLast      
MonsterHeadHitLeft1      
MonsterHeadHitRight1     
MonsterHeadHitLeft2      
MonsterHeadHitRight2     
MonsterChestHitLeft1     
MonsterChestHitRight1    
MonsterChestHitLeft2     
MonsterChestHitRight2    
MonsterLegHitLeft1       
MonsterLegHitRight1      
MonsterLegHitLeft2       
MonsterLegHitRight2      
MonsterKnockDown1        
MonsterGetBackUp1        
MonsterKnockDown2        
MonsterGetBackUp2        
MonsterKnockDown3        
MonsterGetBackUp2        
MonsterTaunt1            
MonsterTaunt2            
MonsterPickUpObjectFirst 
MonsterPickUpObjectFreeze 
MonsterPickUpObjectLast  
MonsterPauseWithObject   
MonsterThrowObject       
*/
//numerical values of cool stuff.
int MonsterAnimationState;               //This is the main control of the state.
RLValue MonsterAnimationFrame;           //This is the current frame of the animation.
RLValue MonsterLastVerticalSpeed;        //I'll go into the jump freeze after a certain number of frames, and come out when 
                                      //downward speed is as big as upward speed is.
//Flags which control whether or not you can affect movement.

#ifdef PC
extern FILE *shithead;
#endif
typedef int (*StateChange) (void);
//StateChange is a function pointer,  There will be one function for each state,
//representing the switch into that state.  Each state will contain as many function
//pointers as there are states it can switch to.  The program will run down the list of these
//functions, and if one of them should return 1, then the program will quit looking.
typedef void (*StateFunction) (void);
//StateFunction is a function pointer.  There will be exactly one of them per state.  This
//is what takes the action appropriate to the state.  Unlike in the movement engine, we don't need
//to take the parameter of the Monster's frame, as we're not doing anything to it.  The animations
//magically link up to the Monster and move it, so all we need to do is set the correct animation
//to the correct time, and have at it.



typedef struct Monster_animation_state_
{
   RLValue Distance;        //How far the Monster will travel during the course of the animation,
   RLValue NumFrames;       //How long the animation is.  All frame numbers will be counted as fixed point numbers, as with RM standards.
   RLValue StopFrame;       //Which frame is the last.  Usually NumFrames, but some animations are more exotic.
   RLValue EnergyDrain;     //How much energy is drained in a frame.
   RLValue EnergyMinimum;   //How much energy is required for an animation.
//   RLValue FirstHitFrame;   //for attacks etc, where there is a specific frame where something interesting happens.
//   RLValue LastHitFrame;    //ditto
   RLAnimationSet Anisette; //this little licorice flavored liqueur is RM's contribution to world peace of mind.
   StateFunction WhatToDo;
   int numchanges;
   StateChange *ChangeList;
}MonsterAnimationStateStructure;

static MonsterAnimationStateStructure MonsterAnimations[35];


/*
 * Monster animation package in a .BIN file
 * Sanfo 8.29
 */
DataPointer TekMonsterData = 0;
PackedAnimations *TekMonsterAnims;
HierarchicalModel *TekMonsterHierarchy;
int TekMonsterNumAnims;


/*
 * play animation from 47Tek.
 */
static
void RLAnimationSetSetTime(RLAnimationSet anim, RLValue time)
{
    TekApplyAnimation( TekMonsterHierarchy, anim, time );
}


//I'll now create the raw materials for the state machine, all the state change functions and the
//state functions.

void NoButReallyPutItHere()
{
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
}

static int ToMonsterPause1(void)
{//No turning, as that will require changes to the movement engine also.
//This function will also be toMonsterpause2, for now.   
   if(MonsterMovementState==MonsterWaiting)
   {//change from any of the movement states to pause.                  
         MonsterAnimationState=MonsterPause1;
         MonsterAnimationFrame=RLVal(0);
         return 1;
   }
   if(MonsterMovementState==MonsterStopped&&MonsterAnimationFrame>=MonsterAnimations[MonsterAnimationState].StopFrame)
   {
      MonsterAnimationState=MonsterPause1;
      MonsterAnimationFrame=RLVal(0);
      MonsterMovementState=MonsterWaiting;
      MonsterDistance=0;
      MonsterNumMovementFrames=0;
//      MonsterHotSpots[RoggoshRightClaw].NumPoints=0;
//      MonsterHotSpots[RoggoshLeftClaw].NumPoints=0;
//      MonsterHotSpots[RoggoshTail].NumPoints=0;
//      MonsterHotSpots[MonsterRightFoot].NumPoints=0;
      return 1;
   }
   if(MonsterAnimationState==MonsterChestHitLeft2 && MonsterAnimationFrame>=MonsterAnimations[MonsterAnimationState].StopFrame)
   {
		MonsterAnimationState=MonsterPause1;
		MonsterAnimationFrame=RLVal(0);
		MonsterMovementState=MonsterWaiting;
		MonsterDistance=0;
		MonsterNumMovementFrames=0;
		return 1;
   }
   return 0;
   
}
static int ToMonsterWalkForward(void)
{
   if(MonsterMovementState==MonsterFAccelerating2||MonsterMovementState==MonsterFTopSpeed1||
      MonsterMovementState==MonsterFAccelerating3||MonsterMovementState==MonsterFTopSpeed2)
   {
      MonsterAnimationState=MonsterWalkForward;
      MonsterAnimationFrame=RLVal(0);
      return 1;
   }
   return 0;
}
static int ToMonsterWalkBack(void)
{
   if(MonsterMovementState==MonsterBAccelerating1||MonsterMovementState==MonsterBAccelerating2
    ||MonsterMovementState==MonsterBTopSpeed1||MonsterMovementState==MonsterBTopSpeed2)
   {
      MonsterAnimationState=MonsterWalkBack;
      MonsterAnimationFrame=RLVal(0);
      return 1;
   }
   return 0;
}
static int ToMonsterJumpFirst(void)
{
   if(MonsterMovementState==MonsterJumping)
   {
      MonsterAnimationState=MonsterJumpFirst;
      MonsterAnimationFrame=RLVal(0);
      return 1;
   }
   return 0;

}
static int ToMonsterJumpFreeze(void)
{
   if(MonsterAnimationFrame>=MonsterAnimations[MonsterAnimationState].StopFrame)
   {
      MonsterAnimationState=MonsterJumpFreeze;
      MonsterAnimationFrame=MonsterAnimations[MonsterAnimationState].StopFrame;
      MonsterLastVerticalSpeed=-MonsterYSpeed;
      return 1;
   }
   return 0;
}
static int ToMonsterJumpLast(void)
{
   if(MonsterAnimationState!=MonsterJumpFreeze && MonsterAnimationState!=MonsterJumpFirst)
   {
      MonsterAnimationState=MonsterJumpLast;
      MonsterAnimationFrame=MonsterJumpStopFrame;
      return 1;
   }
   if(MonsterAnimationState==MonsterJumpFreeze)
   {
      if(MonsterLastVerticalSpeed>=MonsterYSpeed)
      {
         MonsterAnimationState=MonsterJumpLast;
         return 1;
      }
      return 0;
   }
   if(MonsterYSpeed <= RLVal(0))
   {
      MonsterAnimationState=MonsterJumpLast;
      MonsterAnimationFrame=MonsterJumpStopFrame-MonsterAnimationFrame;
      return 1;
   }
   return 0;
}
static int ToMonsterJumpStop(void)
{
   if(MonsterMovementState==MonsterStopped)
   {
      MonsterAnimationState=MonsterJumpStop;
      MonsterAnimationFrame=MonsterJumpStopFrame;
      YBPlay3DSound(MonsterFootStep, monstframe);
      return 1;
   }
   return 0;
}
static int ToMonsterSkid(void)
{
   if(MonsterMovementState==MonsterFBraking)
   {
      MonsterAnimationState=MonsterSkid;
      MonsterAnimationFrame=RLVal(0);
      return 1;
   }
   return 0;
}
static int ToMonsterIntoIntoRun(void)
{
   if(MonsterMovementState==MonsterFAccelerating1)
   {
      MonsterAnimationState=MonsterIntoIntoRun;
      MonsterAnimationFrame=RLVal(0);
      return 1;
   }
   return 0;
}
static int ToMonsterIntoRun(void)
{
   if(MonsterAnimationState==MonsterIntoIntoRun&&MonsterAnimationFrame>=MonsterAnimations[MonsterAnimationState].StopFrame)
   {
      MonsterAnimationState=MonsterIntoRun;
      return 1;
   }
   return 0;

}
static int ToMonsterRun(void)
{
   if(MonsterMovementState==MonsterFTopSpeed3||MonsterMovementState==MonsterFAccelerating4)
   {
      MonsterAnimationState=MonsterRun;
      return 1;
   }
   if(MonsterMovementState==MonsterFTopSpeed4 )
   {
      extern struct _moving_object_data_ MonsterData;
//	  extern int level;
	  extern RLValue sealevel;
   
	  if((GameStates.CurrentLevel==Hawaii) && (SpuddeMapHeight2(MonsterData.CurrentPosition.x,MonsterData.CurrentPosition.z)>sealevel))
	  {
	     MonsterAnimationState=MonsterRun;
	     return 1;
      }
   }
   return 0;
}
static int ToMonsterHighAttack1(void)
{
   if(MnstEngy<MonsterHighAttack1EnergyMinimum)
      return 0;
   if( ((InputInt2&COMMANDZapper) && !(InputInt2&COMMANDDefenseShift)))
   {
//      MonsterAttackFerocity=HighAttack1Ferocity;
      MonsterAnimationState=MonsterHighAttack1;
      MonsterAnimationFrame=0;
      MonsterMovementState=MonsterStopped;
      return 1;
   }
   return 0;
}
/*
static int ToMonsterMediumAttack1(void)
{
   if(MnstEngy<MonsterSpecialAttack1EnergyMinimum)
      return 0;

   //if( (InputInt2&COMMANDHighAttack) && (InputInt2&COMMANDMediumShift) && !(InputInt2&COMMANDDefenseShift))
   if( (InputInt2&COMMANDSpecialOne) && !(InputInt2&COMMANDDefenseShift))
   {
      MonsterAnimationState=MonsterSpecialAttack1;
      MonsterAnimationFrame=0;
      MonsterMovementState=MonsterStopped;
      StageNumber=0;

      return 1;
   }
   return 0;
}
static int ToMonsterLowAttack1(void)
{
//   if(MnstEngy<MonsterLowAttack1EnergyMinimum)
//      return 0;
   if(MnstEngy<MonsterSpecialAttack2EnergyMinimum)
      return 0;

   if( (InputInt2&COMMANDSpecialTwo) && !(InputInt2&COMMANDDefenseShift))
   {
//      MonsterAttackFerocity=LowAttack1Ferocity;
//      MonsterAnimationState=MonsterLowAttack1;
//      MonsterAnimationFrame=0;
//      MonsterMovementState=MonsterStopped;
      MonsterAnimationState=MonsterSpecialAttack2;
      MonsterAnimationFrame=0;
      MonsterMovementState=MonsterStopped;
      StageNumber=0;
      return 1;
   }
   return 0;
}
*/
static int ToMonsterMediumAttack2(void)
{
   if(MnstEngy<MonsterMediumAttack2EnergyMinimum)
      return 0;
   if( (InputInt2&COMMANDLowAttack) && (InputInt2&COMMANDMediumShift) && !(InputInt2&COMMANDDefenseShift))
   {
//      MonsterAttackFerocity=MediumAttack2Ferocity;
      MonsterAnimationState=MonsterMediumAttack2;
      MonsterAnimationFrame=0;
      MonsterMovementState=MonsterStopped;
      return 1;
   }
   return 0;
}
static int ToMonsterLowAttack2(void)
{
   if(MnstEngy<MonsterLowAttack2EnergyMinimum)
      return 0;
   if( (InputInt2&COMMANDLowAttack) && !(InputInt2&COMMANDDefenseShift))
   {
//      MonsterAttackFerocity=LowAttack2Ferocity;
      MonsterAnimationState=MonsterLowAttack2;
      MonsterAnimationFrame=0;
      MonsterMovementState=MonsterStopped;
      return 1;
   }
   return 0;
}
static int ToMonsterJumpAttack1(void)
{
   if(MnstEngy<MonsterJumpAttack1EnergyMinimum)
      return 0;
//      MonsterAttackFerocity=JumpAttack1Ferocity;

   return 0;
}
static int ToMonsterJumpAttack2(void)
{
   if(MnstEngy<MonsterJumpAttack2EnergyMinimum)
      return 0;
//      MonsterAttackFerocity=JumpAttack2Ferocity;
   return 0;
}
static int ToMonsterSpecialAttack1(void)
{
/*   if(MnstEngy<MonsterMediumAttack1EnergyMinimum)
      return 0;
*/
   if(MnstEngy<MonsterSpecialAttack1EnergyMinimum)
      return 0;

   //if( (InputInt2&COMMANDHighAttack) && (InputInt2&COMMANDMediumShift) && !(InputInt2&COMMANDDefenseShift))
   if( (InputInt2&COMMANDSpecialOne) && !(InputInt2&COMMANDDefenseShift))
   {
/*      MonsterAttackFerocity=MediumAttack1Ferocity;
      MonsterAnimationState=MonsterMediumAttack1;
      MonsterAnimationFrame=0;
      MonsterMovementState=MonsterStopped;
*/
      MonsterAnimationState=MonsterSpecialAttack1;
      MonsterAnimationFrame=0;
      MonsterMovementState=MonsterStopped;
      StageNumber=0;

      return 1;
   }
   return 0;
}

static int ToMonsterSpecialAttack2(void)
{
//   if(MnstEngy<MonsterLowAttack1EnergyMinimum)
//      return 0;
   if(MnstEngy<MonsterSpecialAttack2EnergyMinimum)
      return 0;

   if( (InputInt2&COMMANDSpecialTwo) && !(InputInt2&COMMANDDefenseShift))
   {
//      MonsterAttackFerocity=LowAttack1Ferocity;
//      MonsterAnimationState=MonsterLowAttack1;
//      MonsterAnimationFrame=0;
//      MonsterMovementState=MonsterStopped;
      MonsterAnimationState=MonsterSpecialAttack2;
      MonsterAnimationFrame=0;
      MonsterMovementState=MonsterStopped;
      StageNumber=0;
      return 1;
   }
   return 0;
}


static int ToMonsterBlockMediumFirst(void)
{
   if( (InputInt2&COMMANDDefenseShift) && ((InputInt2&COMMANDHighAttack) || (InputInt2&COMMANDLowAttack)) )
   {
      if(MonsterAnimationState==MonsterPause1)
      {
         MonsterAnimationState=MonsterBlockMediumFirst;
         MonsterAnimationFrame=0;
         MonsterMovementState=MonsterStopped;
         return 1;
      }
//      if(MonsterAnimationState==MonsterBlockLowFirst || MonsterAnimationState==MonsterBlockHighFirst)
//      {
//         MonsterAnimationState=MonsterBlockMediumFirst;
//         return 1;
//      }
      if(MonsterAnimationState==MonsterBlockMediumLast /*|| MonsterAnimationState==MonsterBlockHighLast || MonsterAnimationState==MonsterBlockLowLast*/)
      {
         MonsterAnimationFrame=MonsterAnimations[MonsterAnimationState].StopFrame-MonsterAnimationFrame;
         MonsterAnimationState=MonsterBlockMediumFirst;
         return 1;
      }
   }
   return 0;
}
static int ToMonsterBlockMediumFreeze(void)
{
   if( MonsterAnimationState==MonsterBlockMediumFirst && MonsterAnimationFrame>=MonsterAnimations[MonsterAnimationState].StopFrame)
   {
      MonsterAnimationState=MonsterBlockMediumFreeze;
      return 1;
   }
   return 0;
}
static int ToMonsterBlockMediumLast(void)
{
   if( !( (InputInt2&COMMANDDefenseShift) && ((InputInt2&COMMANDHighAttack) || (InputInt2&COMMANDLowAttack) )))
   {
      MonsterAnimationState=MonsterBlockMediumLast;
      MonsterAnimationFrame=MonsterAnimations[MonsterAnimationState].StopFrame-MonsterAnimationFrame;
      return 1;
   }
   return 0;
}
static int ToMonsterKnockDown2(void)
{
   if(MonsterAnimationFrame>=MonsterAnimations[MonsterAnimationState].StopFrame)
   {
      MonsterAnimationState=MonsterKnockDown2;
      MonsterAnimationFrame=RLVal(0);
      MonsterMovementState=MonsterKnockBackward;
		 MonsterFallDownSpin=RLVal(rand()%20-10);
      MonsterDistance=0;
      MonsterNumMovementFrames=0;
      return 1;
   }
   return 0;
}
static int ToMonsterGetBackUp2(void)
{
   extern RLValue Rage;

   if(MonsterAnimationFrame>=MonsterAnimations[MonsterAnimationState].StopFrame)
   {
      YBPlay3DSound(MonsterFallDown, monstframe);
	  Rage += RLVal(10.0);
      MonsterAnimationState=MonsterGetBackUp2;
      MonsterMovementState=MonsterStopped;
      MonsterDistance=0;
      MonsterNumMovementFrames=0;
      return 1;
   }
   return 0;
}
static int ToMonsterDontGetBackUp2(void)
{
   //extern int submonster;
	if(GameStates.CurrentSubmonster==Gamma)
		return 0;
   if((MonsterAnimationFrame>=MonsterAnimations[MonsterAnimationState].StopFrame)&&(MnstLife<=0))
   {
//      extern int level;
      YBPlay3DSound(MonsterFallDown, monstframe);
      KillSubMonster();
	  if(GameStates.IsNetplay)
	  {
	  }
	  else if(!(GameStates.IsAutodemo || GameStates.IsTraining))
	  {
		GameStates.IsMonsterDead[GameStates.CurrentLevel][GameStates.CurrentSubmonster]=1;
	  }
      MonsterAnimationState=MonsterDontGetBackUp2;
      MonsterMovementState=MonsterStopped;
      MonsterDistance=0;
      MonsterNumMovementFrames=0;
      switch(GameStates.CurrentLevel)
      {
         case Trainer:
            MonsterAnimationFrame=RLVal(40);
		 break;
         case Mojave:
            MonsterAnimationFrame=RLVal(17);
         break;
         case Rockies:
            MonsterAnimationFrame=RLVal(27);
         break;
         case Hawaii:
            MonsterAnimationFrame=RLVal(28);
         break;
         case SanFrancisco:
            MonsterAnimationFrame=RLVal(22);
         break;
         case NewYork:
            MonsterAnimationFrame=RLVal(25);
         break;
         case Tokyo:
            MonsterAnimationFrame=RLVal(31);
         break;
      }
      return 1;
   }
   return 0;
}
static int ToMonsterPickUpObjectFirst(void)
{
   if( (InputInt2&COMMANDCrouch) )
   {
      if(MonsterAnimationState==MonsterPickUpObjectLast)
      {
         MonsterAnimationFrame=MonsterAnimations[MonsterAnimationState].StopFrame-MonsterAnimationFrame;
         MonsterAnimationState=MonsterPickUpObjectFirst;
         MonsterMovementState=MonsterStopped;
         return 1;
      }
      MonsterAnimationState=MonsterPickUpObjectFirst;
      MonsterAnimationFrame=0;
      MonsterMovementState=MonsterStopped;
      return 1;
   }
   return 0;
}
static int ToMonsterPickUpObjectFreeze(void)
{
   if( MonsterAnimationFrame>=MonsterAnimations[MonsterAnimationState].StopFrame)
   {
      MonsterAnimationState=MonsterPickUpObjectFreeze;
      return 1;
   }
   return 0;
}
static int ToMonsterPickUpObjectLast(void)
{
   if( !(InputInt2&COMMANDCrouch) )
   {
      MonsterAnimationState=MonsterPickUpObjectLast;
      MonsterAnimationFrame=MonsterAnimations[MonsterAnimationState].StopFrame-MonsterAnimationFrame;
      return 1;
   }
   return 0;
}
static int ToMonsterThrowObject(void)
{
   if(MnstEngy<MonsterThrowObjectEnergyMinimum)
      return 0;
//      MonsterAttackFerocity=ThrowObjectFerocity;
   return 0;
}

static int ToMonsterTaunt1(void)
{
//   if( RobotLife==0)
   if (GameStates.RobotLose)
   {
      MonsterAnimationState=MonsterTaunt1;
      MonsterAnimationFrame=0;
      NumMonsterTaunts=0;
      MonsterMovementState=MonsterStopped;
      YBPlay3DSound(MonsterWail, monstframe);
      return 1;
   }
   return 0;
}

static int ToMonsterTaunt2(void)
{
//   if( RobotLife==0)
   if (((InputInt2&COMMANDWeakShift)&&(InputInt2&COMMANDMediumShift)&&(InputInt2&COMMANDStrongShift)))
   {
      MonsterAnimationState=MonsterTaunt2;
      MonsterAnimationFrame=0;
      //NumMonsterTaunts=0;
      MonsterMovementState=MonsterStopped;
      YBPlay3DSound(MonsterWail, monstframe);
      return 1;
   }
   return 0;
}

static int ToMonsterAllDead(void)
{
//   extern int submonster;
//   extern int level;
   if((MonsterAnimationFrame>=MonsterAnimations[MonsterAnimationState].StopFrame)&&(MnstLife<=0)&&(GameStates.CurrentSubmonster==Gamma))
   {
	   GameStates.MonsterLose=1;
	   if(GameStates.IsNetplay)
	   {
		   GameStates.IsMonsterDead[GameStates.CurrentLevel][GameStates.CurrentSubmonster]++;
	   }
	   else if(!(GameStates.IsTraining||GameStates.IsAutodemo))
	   {
		   GameStates.IsMonsterDead[GameStates.CurrentLevel][GameStates.CurrentSubmonster]=1;
	   }
	   GameStates.MonsterLose=TRUE;

	   YBPlay3DSound(MonsterFallDown, monstframe);
      MonsterAnimationState=MonsterAllDead;
      MonsterAnimationFrame=0;
      MonsterMovementState=MonsterStopped;
      switch(GameStates.CurrentLevel)
      {
         case Trainer:
			 MonsterAnimationFrame=RLVal(40);
		 break;
         case Mojave:
            MonsterAnimationFrame=RLVal(17);
         break;
         case Rockies:
            MonsterAnimationFrame=RLVal(27);
         break;
         case Hawaii:
            MonsterAnimationFrame=RLVal(28);
         break;
         case SanFrancisco:
            MonsterAnimationFrame=RLVal(22);
         break;
         case NewYork:
            MonsterAnimationFrame=RLVal(25);
         break;
         case Tokyo:
            MonsterAnimationFrame=RLVal(31);
         break;
      }
      return 1;
   }
   return 0;
}

static int ToMonsterTravel(void)
{
	extern struct _moving_object_data_ MonsterData;
//	extern int level;
   	extern RLValue sealevel;

   if( MonsterMovementState==MonsterFTopSpeed4)
   {
	   if((GameStates.CurrentLevel==Hawaii) && (SpuddeMapHeight2(MonsterData.CurrentPosition.x,MonsterData.CurrentPosition.z)>sealevel))
	      return 0;
      MonsterAnimationState=MonsterTravel;
      MonsterAnimationFrame=MonsterTravelFirstFrame;
      return 1;
   }
   return 0;   

}


static void MonsterPause1Function(void)
{
//This is the function for when you loop back to yourself automatically,
//and the timing is incremented automatically as time goes by.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);

   MonsterAnimationFrame+=DiffFrame;
   if(MonsterAnimationFrame>=MonsterAnimations[MonsterAnimationState].StopFrame)
      MonsterAnimationFrame-=MonsterAnimations[MonsterAnimationState].NumFrames;
}


static void MonsterWalkForwardFunction(void)
{
//This function loops back to the beginning, and timing is based on distance.
//   static int firsthalf=1;
   RLValue dummy=MonsterAnimations[MonsterAnimationState].Distance;
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   if(MonsterDistance>=dummy)
   {
      MonsterDistance-=dummy;
      YBPlay3DSound(MonsterFootStep, monstframe);
      StageNumber=0;
   }
   if(MonsterDistance>dummy/2 && StageNumber==0)
   {
      YBPlay3DSound(MonsterFootStep, monstframe);
      StageNumber=1;
   }
   MonsterAnimationFrame=RLMultiply(RLDivide(MonsterDistance,dummy),MonsterAnimations[MonsterAnimationState].NumFrames) +
                 MonsterAnimations[MonsterAnimationState].StopFrame-MonsterAnimations[MonsterAnimationState].NumFrames;
   
}
static void MonsterWalkBackFunction(void)
{
//This function loops back to the beginning, and timing is based on distance.
//   static int firsthalf=1;
   RLValue dummy=MonsterAnimations[MonsterAnimationState].Distance;
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   if(MonsterDistance>=dummy)
   {
      MonsterDistance-=dummy;
      YBPlay3DSound(MonsterFootStep, monstframe);
      StageNumber=0;
   }
   if(MonsterDistance>dummy/2&&StageNumber==0)
   {
      YBPlay3DSound(MonsterFootStep, monstframe);
      StageNumber=1;
   }
   MonsterAnimationFrame=RLMultiply(RLDivide(MonsterDistance,dummy),MonsterAnimations[MonsterAnimationState].NumFrames) +
                 MonsterAnimations[MonsterAnimationState].StopFrame-MonsterAnimations[MonsterAnimationState].NumFrames;
   
}
static void MonsterJumpFirstFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
//   MonsterAnimationFrame+=RLVal(1.0);
   MonsterAnimationFrame+=DiffFrame;
   if(MonsterAnimationFrame>MonsterAnimations[MonsterAnimationState].StopFrame)
      MonsterAnimationFrame=MonsterAnimations[MonsterAnimationState].StopFrame;
}
static void MonsterJumpFreezeFunction(void)
{
//This function keeps the frame frozen at the appropriate frame.
   MonsterAnimationFrame=MonsterAnimations[MonsterAnimationState].StopFrame;
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
}

static void MonsterJumpLastFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
   if(MonsterAnimationFrame>MonsterAnimations[MonsterAnimationState].StopFrame)
      MonsterAnimationFrame=MonsterAnimations[MonsterAnimationState].StopFrame;
}

static void MonsterJumpStopFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
}

static void MonsterSkidFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
}



static void MonsterIntoIntoRunFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
}

static void MonsterIntoRunFunction(void)
{
//This is the function for when you loop back to yourself automatically,
//and the timing is incremented automatically as time goes by.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);

   MonsterAnimationFrame+=DiffFrame;
   if(MonsterAnimationFrame>=MonsterAnimations[MonsterAnimationState].StopFrame)
      MonsterAnimationFrame-=MonsterAnimations[MonsterAnimationState].NumFrames;
}


static void MonsterRunFunction(void)
{
//This function loops back to the beginning, and timing is based on distance.
//   static int firsthalf=1;
   RLValue dummy=MonsterAnimations[MonsterAnimationState].Distance;
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   if(MonsterDistance>=dummy)
   {
      MonsterDistance-=dummy;
      YBPlay3DSound(MonsterFootStep, monstframe);
      StageNumber=0;
   }
   if(MonsterDistance>dummy/2&&StageNumber==0)
   {
      YBPlay3DSound(MonsterFootStep, monstframe);
      StageNumber=1;
   }
   MonsterAnimationFrame=RLMultiply(RLDivide(MonsterDistance,dummy),MonsterAnimations[MonsterAnimationState].NumFrames) +
                 MonsterAnimations[MonsterAnimationState].StopFrame-MonsterAnimations[MonsterAnimationState].NumFrames;
   
}

static void MonsterHighAttack1Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
//It represents the tail zapper style attack.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   if(MonsterAnimationFrame>=RLVal(14) && MonsterAnimationFrame<=RLVal(18) && !ZappaOnScreen)
   {
      RLFrame WhereIsIt;
      RLFrame Scene;
//      RLVector position;
//	  extern int level;
      RLMatrix4d matrix=
      {
         {RLVal(1),0,0,0},
         {0,RLVal(1),0,0},
         {0,0,RLVal(-1),0},
         {0,0,0,RLVal(1)}
      };
      MonsterPlasmaDisplacement.x=0;
      MonsterPlasmaDisplacement.y=0;
      MonsterPlasmaDisplacement.z=0;
switch(GameStates.CurrentLevel)
{
   case Trainer:
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
      WhereIsIt=MonsterTailSpots[RoggoshTail].position;
	  Scene=RLFrameGetScene(WhereIsIt);
/*      RLMatrix4d matrix=
      {
         {RLVal(1),0,0,0},
         {0,RLVal(1),0,0},
         {0,0,RLVal(-1),0},
         {0,0,0,RLVal(1)}
      };*/
	  
	  //matrix[1][1]=0;
	  //matrix[1][2]=RLVal(-1);
	  //matrix[2][2]=0;
	  //matrix[2][1]=RLVal(1);
	  
	  matrix[0][0] = RLVal(-1);
	  matrix[1][1] = RLVal(-1);
	  matrix[2][2] = RLVal(1);
	  //matrix[3][3] = RLVal(-1);
      break;
   case Mojave:
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
      WhereIsIt=MonsterTailSpots[RoggoshTail].position;
	  Scene=RLFrameGetScene(WhereIsIt);
//roggosh
   break;
   case Rockies:
//rockies
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
      WhereIsIt=MonsterTailSpots[RoggoshTail].position;
	  Scene=RLFrameGetScene(WhereIsIt);
/*      RLMatrix4d matrix=
      {
         {RLVal(1),0,0,0},
         {0,RLVal(1),0,0},
         {0,0,RLVal(-1),0},
         {0,0,0,RLVal(1)}
      };*/
	  
	  matrix[1][1]=0;
	  matrix[1][2]=RLVal(1);
	  matrix[2][2]=0;
	  matrix[2][1]=RLVal(-1);
	  
//Monkeys and Typewriters guess to switch y and z axes.
   break;
   case Hawaii:
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
      WhereIsIt=MonsterTailSpots[RoggoshTail].position;
	  Scene=RLFrameGetScene(WhereIsIt);
      matrix[3][1]=RLVal(0.57);
      MonsterPlasmaDisplacement.y = RLVal(0.57);
//hawaii
   break;
   case SanFrancisco:
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
      WhereIsIt=MonsterTailSpots[RoggoshTail].position;
	  Scene=RLFrameGetScene(WhereIsIt);
//San Fran
   break;
   case NewYork:
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
      WhereIsIt=MonsterTailSpots[RoggoshTail].position;
	  Scene=RLFrameGetScene(WhereIsIt);
//NYNY
   break;
   case Tokyo:
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
      WhereIsIt=MonsterTailSpots[RoggoshTail].position;
	  Scene=RLFrameGetScene(WhereIsIt);
//Tokyo
   break;
}

      RLFrameAddChild(WhereIsIt,monstspew);
      RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
      ZappaOnScreen=1;
      ZappaHowLong=TailZapDuration;
	  RLFrameSetPosition(monstspew, WhereIsIt, RLVal(0), RLVal(0), RLVal(0));
	  RLFrameGetPosition(monstspew,Scene,&MonsterZappaData.ProjectedPosition);
     MonsterZappaData.CurrentPosition.x=MonsterZappaData.ProjectedPosition.x;
     MonsterZappaData.CurrentPosition.y=MonsterZappaData.ProjectedPosition.y;
     MonsterZappaData.CurrentPosition.z=MonsterZappaData.ProjectedPosition.z;
	 MonsterZappaData.DamageICause = MonsterZapDamage;
//      MonsterZappaData.ProjectedPosition.x=0;
//      MonsterZappaData.ProjectedPosition.y=0;
//      MonsterZappaData.ProjectedPosition.z=0;
      MonsterZappaData.RemoveMeFlag=0;
      MonsterZappaData.collisionflag=0;
      AddMovingObject(&MonsterZappaData);

//      monstspewdata.HowBig=RLVal(1.0);
//      monstspewdata.HasHit=0;
//      monstspewdata.WhatDamage=5;
      YBPlay3DSound(MonsterTailZap, monstframe);
      
      RLFrameSetRotation(monstspew, monstspew, 0, 0, RLVal(1), TailZapRotation);
//      RLFrameAddCallback(monstspew, ZappaCallBack, &monstspewdata);
   }

   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
}

static void MonsterMediumAttack1Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
}

static void MonsterLowAttack1Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
}


static void MonsterMediumAttack2Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   if(MonsterAnimationFrame>=RLVal(16) && MonsterAnimationFrame<= RLVal(24))
   {
//      MonsterHotSpots[RoggoshRightClaw].NumPoints=1;
   }
   else
   {
//      MonsterHotSpots[RoggoshRightClaw].NumPoints=0;
   }
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
}

static void MonsterLowAttack2Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   if(MonsterAnimationFrame>=RLVal(8) && MonsterAnimationFrame<= RLVal(12))
   {
//      MonsterHotSpots[RoggoshRightClaw].NumPoints=1;
   }
   else
   {
//      MonsterHotSpots[RoggoshRightClaw].NumPoints=0;
   }
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
}

static void MonsterJumpAttack1Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
}

static void MonsterJumpAttack2Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
}

static void MonsterSpecialAttack1Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLFrame WhereIsIt;
   RLFrame Scene;
   RLVector position;
//   extern int level;
   RLMatrix4d matrix=
   {
      {RLVal(1),0,0,0},
      {0,RLVal(1),0,0},
      {0,0,RLVal(-1),0},
      {0,0,0,RLVal(1)}
   };
   MonsterPlasmaDisplacement.x=0;
   MonsterPlasmaDisplacement.y=0;
   MonsterPlasmaDisplacement.z=0;
   switch(GameStates.CurrentLevel)
   {
      case Trainer:
	  matrix[0][0] = RLVal(-1);
	  matrix[1][1] = RLVal(-1);
	  matrix[2][2] = RLVal(1);
      case Mojave:
   //roggosh homer
         if(MonsterAnimationFrame>=10 && StageNumber==0)
         {
            StageNumber=1;
            MonsterMovementState=RoggoshHomer;
            MonsterDistance=0;
            MonsterNumMovementFrames=0;
            MonsterHitObstacle=0;

   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
            WhereIsIt=MonsterTailSpots[RoggoshTail].position;
            Scene=RLFrameGetScene(WhereIsIt);
            RLFrameAddChild(WhereIsIt,monstspew);
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            ZappaOnScreen=1;
            ZappaHowLong=RoggoshHomerDuration;
            RLFrameGetPosition(WhereIsIt,Scene,&MonsterZappaData.ProjectedPosition);
            MonsterZappaData.CurrentPosition.x=MonsterZappaData.ProjectedPosition.x;
            MonsterZappaData.CurrentPosition.y=MonsterZappaData.ProjectedPosition.y;
            MonsterZappaData.CurrentPosition.z=MonsterZappaData.ProjectedPosition.z;
            MonsterZappaData.RemoveMeFlag=0;
            MonsterZappaData.collisionflag=0;
            AddMovingObject(&MonsterZappaData);
            YBPlay3DSound(MonsterTailZap, monstframe);
            RLFrameSetRotation(monstspew, monstspew, 0, 0, RLVal(1), TailZapRotation);



         }
         else if(MonsterAnimationFrame>=68 && StageNumber==1)
         {
            StageNumber=2;
            MonsterMovementState=MonsterStopped;
            MonsterDistance=0;
            MonsterNumMovementFrames=0;
            MonsterHitObstacle=0;
         }
   //roggosh
      break;
      case Rockies:
   //Kothos Snowstorm
   //rockies
         if(MonsterAnimationFrame>=30 && StageNumber==0)
         {
//            FILE *shithead;
            RLVector dir,up;
            StageNumber=1;
            Scene=RLFrameGetScene(monstframe);
            RLFrameGetPosition(monstframe,Scene,&position);
            RLFrameGetOrientation(monstframe,Scene,&dir,&up);
            RLFrameAddChild(Scene,BombSphere);
            RLFrameAddScale(BombSphere,RLCombineReplace,RLVal(0.3),RLVal(0.3),RLVal(0.3));
            RLFrameSetPosition(BombSphere,Scene,position.x - 0.6*dir.x ,position.y + 0.15,position.z - 0.6*dir.z);
            BombData.ProjectedPosition.x=position.x - 0.6*dir.x;
            BombData.ProjectedPosition.y=position.y + 0.15;
            BombData.ProjectedPosition.z=position.z- 0.6*dir.z;
            BombData.CurrentPosition.x=position.x- 0.6*dir.x;
            BombData.CurrentPosition.y=position.y + 0.15;
            BombData.CurrentPosition.z=position.z- 0.6*dir.z;
            KothosSnowballVelocity.x=-0.6*dir.x;
            KothosSnowballVelocity.z=-0.6*dir.z;
            KothosSnowballVelocity.y=0;
//            shithead=fopen("shit.out","w");
//            fprintf(shithead,"monster's position is (%.3f, %.3f, %.3f)\n",position.x,position.y,position.z);
//            fprintf(shithead,"Bomb's expected position is (%.3f, %.3f, %.3f)\n",BombData.CurrentPosition.x,BombData.CurrentPosition.y,BombData.CurrentPosition.z);
//            RLFrameGetPosition(BombSphere,Scene,&position);
//            fprintf(shithead,"Bomb's real position is (%.3f, %.3f, %.3f)\n",position.x,position.y,position.z);

//            fclose(shithead);
            BombData.RemoveMeFlag=0;
            BombData.collisionflag=0;
//            BombData.DamageICause=GaingrisNukeDamage;
            AddMovingObject(&BombData);
//            BombSpot.radius=RLVal(0.0);
            BombHowLong=RLVal(0.0);
         }
      break;
      case Hawaii:
   //Tolgo claw punches
         if(MonsterAnimationFrame>=16 && StageNumber==0)
         {
            StageNumber=1;
            MonsterData.NumOffensiveSpheres=1;
            MonsterData.OffensiveSphereList[0]=&(MonsterHotSpots[RoggoshLeftClaw]);
            MonsterData.DamageICause=TolgoPunchDamage;
         }
         else if(MonsterAnimationFrame>=26 && StageNumber==1)
         {
            StageNumber=2;
            MonsterData.NumOffensiveSpheres=0;
            MonsterData.OffensiveSphereList[0]=NULL;
            MonsterData.DamageICause=MonsterMotionDamage;

         }
         else if(MonsterAnimationFrame>=37 && StageNumber==2)
         {
            StageNumber=3;
            MonsterData.NumOffensiveSpheres=1;
            MonsterData.OffensiveSphereList[0]=&(MonsterHotSpots[RoggoshRightClaw]);
            MonsterData.DamageICause=TolgoPunchDamage;
         }
         else if(MonsterAnimationFrame>=47 && StageNumber==3)
         {
            StageNumber=4;
            MonsterData.NumOffensiveSpheres=0;
            MonsterData.OffensiveSphereList[0]=NULL;
            MonsterData.DamageICause=MonsterMotionDamage;
         }
         else if(MonsterAnimationFrame>=58 && StageNumber==4)
         {
            StageNumber=5;
            MonsterData.NumOffensiveSpheres=1;
            MonsterData.OffensiveSphereList[0]=&(MonsterHotSpots[RoggoshLeftClaw]);
            MonsterData.DamageICause=TolgoPunchDamage;
         }
         else if(MonsterAnimationFrame>=68 && StageNumber==5)
         {
            StageNumber=6;
            MonsterData.NumOffensiveSpheres=0;
            MonsterData.OffensiveSphereList[0]=NULL;
            MonsterData.DamageICause=MonsterMotionDamage;
         }
   //hawaii
      break;
      case SanFrancisco:
   //Shagtoq big plasma
		MonsterZappaData.mass = ShagtoqSpewMass;
		MonsterZappaData.DamageICause = ShagtoqSpewDamage;
		MonsterZappaSpot.radius = ShagtoqSpewRadius;
		MonsterZappaSpot.point2.z = ShagtoqSpewLength;

		  if(MonsterAnimationFrame>=32 && StageNumber==0)
         {
            StageNumber=1;
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
            WhereIsIt=MonsterTailSpots[RoggoshTail].position;
            Scene=RLFrameGetScene(WhereIsIt);
            RLFrameAddChild(WhereIsIt,monstspew);
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            ZappaOnScreen=1;
            ZappaHowLong=ShagtoqSpewDuration;
            RLFrameGetPosition(WhereIsIt,Scene,&MonsterZappaData.ProjectedPosition);
            MonsterZappaData.CurrentPosition.x=MonsterZappaData.ProjectedPosition.x;
            MonsterZappaData.CurrentPosition.y=MonsterZappaData.ProjectedPosition.y;
            MonsterZappaData.CurrentPosition.z=MonsterZappaData.ProjectedPosition.z;
            MonsterZappaData.RemoveMeFlag=0;
            MonsterZappaData.collisionflag=0;
            AddMovingObject(&MonsterZappaData);
            YBPlay3DSound(MonsterTailZap, monstframe);
            RLFrameSetRotation(monstspew, monstspew, 0, 0, RLVal(1), TailZapRotation);
         }
         if(MonsterAnimationFrame>=34 && StageNumber==1)
         {
       RLValue SpewScale = RLVal(1.1);
            StageNumber=2;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=36 && StageNumber==2)
         {
       RLValue SpewScale = RLVal(1.3);
            StageNumber=3;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=38 && StageNumber==3)
         {
       RLValue SpewScale = RLVal(1.6);
            StageNumber=4;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=40 && StageNumber==4)
         {
       RLValue SpewScale = RLVal(1.9);
            StageNumber=5;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=42 && StageNumber==5)
         {
       RLValue SpewScale = RLVal(2.2);
            StageNumber=6;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=44 && StageNumber==6)
         {

       RLValue SpewScale = RLVal(2.5);
            StageNumber=7;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=46 && StageNumber==7)
         {
       RLValue SpewScale = RLVal(2.8);
            StageNumber=8;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=48 && StageNumber==8)
         {
       RLValue SpewScale = RLVal(3.1);
            StageNumber=9;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=50 && StageNumber==9)
         {
       RLValue SpewScale = RLVal(3.4);
            StageNumber=10;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=52 && StageNumber==10)
         {
       RLValue SpewScale = RLVal(3.7);
            StageNumber=11;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=54 && StageNumber==11)
         {
       RLValue SpewScale = RLVal(4.0);
            StageNumber=12;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=25+ShagtoqSpewDuration && StageNumber==12)
         {
       RLValue SpewScale = RLVal(3.7);
            StageNumber=13;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=26+ShagtoqSpewDuration && StageNumber==13)
         {
       RLValue SpewScale = RLVal(3.1);
            StageNumber=14;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=27+ShagtoqSpewDuration && StageNumber==14)
         {
       RLValue SpewScale = RLVal(2.5);
            StageNumber=15;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=28+ShagtoqSpewDuration && StageNumber==15)
         {
       RLValue SpewScale = RLVal(1.9);
            StageNumber=16;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=29+ShagtoqSpewDuration && StageNumber==16)
         {
       RLValue SpewScale = RLVal(1.3);
            StageNumber=17;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=30+ShagtoqSpewDuration && StageNumber==17)
         {
       RLValue SpewScale = RLVal(1.0);
            StageNumber=18;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
   //San Fran
      break;
      case NewYork:
   //Nealloth Dive Bomb
		MonsterZappaData.mass = NeallothDiveBombMass;
		MonsterZappaData.DamageICause = NeallothDiveBombDamage;
		MonsterZappaSpot.radius = NeallothDiveBombRadius;
		MonsterZappaSpot.point2.z = NeallothDiveBombLength;

		  if(MonsterAnimationFrame>=9 && StageNumber==0)
         {//launch into the air
            StageNumber=1;
            MonsterMovementState=NeallothDiveBomb;
            MonsterDistance=0;
            MonsterNumMovementFrames=0;
            MonsterHitObstacle=0;
         }
         else if(MonsterAnimationFrame>=26 && StageNumber==1)
         {//maximum height
            StageNumber=2;
            MonsterMovementState=MonsterAirborne;
         }
         else if(MonsterAnimationFrame>=35 && StageNumber==2)
         {//eyebolts
            StageNumber=3;
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
            WhereIsIt=MonsterTailSpots[RoggoshTail].position;
            Scene=RLFrameGetScene(WhereIsIt);
            RLFrameAddChild(WhereIsIt,monstspew);
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            ZappaOnScreen=1;
            ZappaHowLong=NeallothEyeboltDuration;
            RLFrameGetPosition(WhereIsIt,Scene,&MonsterZappaData.ProjectedPosition);
            MonsterZappaData.CurrentPosition.x=MonsterZappaData.ProjectedPosition.x;
            MonsterZappaData.CurrentPosition.y=MonsterZappaData.ProjectedPosition.y;
            MonsterZappaData.CurrentPosition.z=MonsterZappaData.ProjectedPosition.z;
            MonsterZappaData.RemoveMeFlag=0;
            MonsterZappaData.collisionflag=0;
            AddMovingObject(&MonsterZappaData);
            YBPlay3DSound(MonsterTailZap, monstframe);
            RLFrameSetRotation(monstspew, monstspew, 0, 0, RLVal(1), TailZapRotation);

         }
         else if(MonsterAnimationFrame>=69 && StageNumber==3)
         {//lands
            StageNumber=4;
            MonsterMovementState=MonsterStopped;
         }

   //NYNY
      break;
      case Tokyo:
   //Gaingris multiblast
		MonsterZappaData.mass = GaingrisTripleZapMass;
		MonsterZappaData.DamageICause = GaingrisTripleZapDamage;
		MonsterZappaSpot.radius = GaingrisTripleZapRadius;
		MonsterZappaSpot.point2.z = GaingrisTripleZapLength;

		  if(MonsterAnimationFrame>=13 && StageNumber==0)
         {//Roggosh plasmatail
            StageNumber=1;
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
            WhereIsIt=MonsterTailSpots[RoggoshTail].position;
            Scene=RLFrameGetScene(WhereIsIt);
            RLFrameAddChild(WhereIsIt,monstspew);
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            ZappaOnScreen=1;
            ZappaHowLong=GaingrisMultiblastDuration;
            RLFrameGetPosition(WhereIsIt,Scene,&MonsterZappaData.ProjectedPosition);
            MonsterZappaData.CurrentPosition.x=MonsterZappaData.ProjectedPosition.x;
            MonsterZappaData.CurrentPosition.y=MonsterZappaData.ProjectedPosition.y;
            MonsterZappaData.CurrentPosition.z=MonsterZappaData.ProjectedPosition.z;
            MonsterZappaData.RemoveMeFlag=0;
            MonsterZappaData.collisionflag=0;
            AddMovingObject(&MonsterZappaData);
            YBPlay3DSound(MonsterTailZap, monstframe);
            RLFrameSetRotation(monstspew, monstspew, 0, 0, RLVal(1), TailZapRotation);
         }
         else if(MonsterAnimationFrame>=39 && StageNumber==1)
         {//tolgo chest blast
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
            WhereIsIt=MonsterHotSpots[RoggoshRightClaw].position;
            Scene=RLFrameGetScene(WhereIsIt);
            StageNumber=2;
            RLFrameAddChild(WhereIsIt,monstspew);
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            ZappaOnScreen=1;
            ZappaHowLong=GaingrisMultiblastDuration;
            RLFrameGetPosition(WhereIsIt,Scene,&MonsterZappaData.ProjectedPosition);
            MonsterZappaData.CurrentPosition.x=MonsterZappaData.ProjectedPosition.x;
            MonsterZappaData.CurrentPosition.y=MonsterZappaData.ProjectedPosition.y;
            MonsterZappaData.CurrentPosition.z=MonsterZappaData.ProjectedPosition.z;
            MonsterZappaData.RemoveMeFlag=0;
            MonsterZappaData.collisionflag=0;
            AddMovingObject(&MonsterZappaData);
            YBPlay3DSound(MonsterTailZap, monstframe);
            RLFrameSetRotation(monstspew, monstspew, 0, 0, RLVal(1), TailZapRotation);
         }
         else if(MonsterAnimationFrame>=63 && StageNumber==2)
         {//Nealloth Head attack.
            StageNumber=3;
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
            WhereIsIt=MonsterHotSpots[RoggoshLeftClaw].position;
            Scene=RLFrameGetScene(WhereIsIt);
            RLFrameAddChild(WhereIsIt,monstspew);
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            ZappaOnScreen=1;
            ZappaHowLong=GaingrisMultiblastDuration;
            RLFrameGetPosition(WhereIsIt,Scene,&MonsterZappaData.ProjectedPosition);
            MonsterZappaData.CurrentPosition.x=MonsterZappaData.ProjectedPosition.x;
            MonsterZappaData.CurrentPosition.y=MonsterZappaData.ProjectedPosition.y;
            MonsterZappaData.CurrentPosition.z=MonsterZappaData.ProjectedPosition.z;
            MonsterZappaData.RemoveMeFlag=0;
            MonsterZappaData.collisionflag=0;
            AddMovingObject(&MonsterZappaData);
            YBPlay3DSound(MonsterTailZap, monstframe);
            RLFrameSetRotation(monstspew, monstspew, 0, 0, RLVal(1), TailZapRotation);
         }



   //Tokyo
      break;
   }
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
}
static void MonsterSpecialAttack2Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLFrame WhereIsIt;
   RLFrame Scene;
   RLVector position;
   RLVector dir;
   RLVector up;
//   extern int level;
   RLMatrix4d matrix=
   {
      {RLVal(1),0,0,0},
      {0,RLVal(1),0,0},
      {0,0,RLVal(-1),0},
      {0,0,0,RLVal(1)}
   };
   MonsterPlasmaDisplacement.x=0;
   MonsterPlasmaDisplacement.y=0;
   MonsterPlasmaDisplacement.z=0;
   switch(GameStates.CurrentLevel)
   {
      case Trainer:
	  matrix[0][0] = RLVal(-1);
	  matrix[1][1] = RLVal(-1);
	  matrix[2][2] = RLVal(1);

      case Mojave:
   //roggosh triple shot
		MonsterZappaData.mass = RoggoshTripleZapMass;
		MonsterZappaData.DamageICause = RoggoshTripleZapDamage;
		MonsterZappaSpot.radius = RoggoshTripleZapRadius;
		MonsterZappaSpot.point2.z = RoggoshTripleZapLength;

         if(MonsterAnimationFrame>=16 && StageNumber==0)
         {
            StageNumber=1;
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
            WhereIsIt=MonsterTailSpots[RoggoshTail].position;
            Scene=RLFrameGetScene(WhereIsIt);
            RLFrameAddChild(WhereIsIt,monstspew);
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            ZappaOnScreen=1;
            ZappaHowLong=RoggoshTripleDuration;
            RLFrameGetPosition(WhereIsIt,Scene,&MonsterZappaData.ProjectedPosition);
            MonsterZappaData.CurrentPosition.x=MonsterZappaData.ProjectedPosition.x;
            MonsterZappaData.CurrentPosition.y=MonsterZappaData.ProjectedPosition.y;
            MonsterZappaData.CurrentPosition.z=MonsterZappaData.ProjectedPosition.z;
            MonsterZappaData.RemoveMeFlag=0;
            MonsterZappaData.collisionflag=0;

            AddMovingObject(&MonsterZappaData);
            YBPlay3DSound(MonsterTailZap, monstframe);
           RLFrameSetRotation(monstspew, monstspew, 0, 0, RLVal(1), TailZapRotation);
         }
         else if(MonsterAnimationFrame>=32 && StageNumber==1)
         {
            StageNumber=2;
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
            WhereIsIt=MonsterTailSpots[RoggoshTail].position;
            Scene=RLFrameGetScene(WhereIsIt);
            RLFrameAddChild(WhereIsIt,monstspew);
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            ZappaOnScreen=1;
            ZappaHowLong=RoggoshTripleDuration;
            RLFrameGetPosition(WhereIsIt,Scene,&MonsterZappaData.ProjectedPosition);
            MonsterZappaData.CurrentPosition.x=MonsterZappaData.ProjectedPosition.x;
            MonsterZappaData.CurrentPosition.y=MonsterZappaData.ProjectedPosition.y;
            MonsterZappaData.CurrentPosition.z=MonsterZappaData.ProjectedPosition.z;
            MonsterZappaData.RemoveMeFlag=0;
            MonsterZappaData.collisionflag=0;
            AddMovingObject(&MonsterZappaData);
            YBPlay3DSound(MonsterTailZap, monstframe);
            RLFrameSetRotation(monstspew, monstspew, 0, 0, RLVal(1), TailZapRotation);
         }
         else if(MonsterAnimationFrame>=48 && StageNumber==2)
         {
            StageNumber=3;
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
            WhereIsIt=MonsterTailSpots[RoggoshTail].position;
            Scene=RLFrameGetScene(WhereIsIt);
            RLFrameAddChild(WhereIsIt,monstspew);
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            ZappaOnScreen=1;
            ZappaHowLong=RoggoshTripleDuration;
            RLFrameGetPosition(WhereIsIt,Scene,&MonsterZappaData.ProjectedPosition);
            MonsterZappaData.CurrentPosition.x=MonsterZappaData.ProjectedPosition.x;
            MonsterZappaData.CurrentPosition.y=MonsterZappaData.ProjectedPosition.y;
            MonsterZappaData.CurrentPosition.z=MonsterZappaData.ProjectedPosition.z;
            MonsterZappaData.RemoveMeFlag=0;
            MonsterZappaData.collisionflag=0;
            AddMovingObject(&MonsterZappaData);
            YBPlay3DSound(MonsterTailZap, monstframe);
            RLFrameSetRotation(monstspew, monstspew, 0, 0, RLVal(1), TailZapRotation);
         }
   //roggosh
      break;
      case Rockies:
   //Kothos elevated lightning
		MonsterZappaData.mass = KothosJumpAttackMass;
		MonsterZappaData.DamageICause = KothosJumpAttackDamage;
		MonsterZappaSpot.radius = KothosJumpAttackRadius;
		MonsterZappaSpot.point2.z = KothosJumpAttackLength;
         if(MonsterAnimationFrame>=22 && StageNumber==0)
         {
            StageNumber=1;
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
            WhereIsIt=MonsterTailSpots[RoggoshTail].position;
            Scene=RLFrameGetScene(WhereIsIt);

            matrix[1][1]=0;
            matrix[1][2]=RLVal(1);
            matrix[2][2]=0;
            matrix[2][1]=RLVal(-1);

            RLFrameAddChild(WhereIsIt,monstspew);
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            ZappaOnScreen=1;
            ZappaHowLong=KothosJumpAttackDuration;
            RLFrameGetPosition(WhereIsIt,Scene,&MonsterZappaData.ProjectedPosition);
            MonsterZappaData.CurrentPosition.x=MonsterZappaData.ProjectedPosition.x;
            MonsterZappaData.CurrentPosition.y=MonsterZappaData.ProjectedPosition.y;
            MonsterZappaData.CurrentPosition.z=MonsterZappaData.ProjectedPosition.z;
            MonsterZappaData.RemoveMeFlag=0;
            MonsterZappaData.collisionflag=0;
            AddMovingObject(&MonsterZappaData);

            YBPlay3DSound(MonsterTailZap, monstframe);

            RLFrameSetRotation(monstspew, monstspew, 0, 0, RLVal(1), TailZapRotation);

         }
   //rockies
      break;
      case Hawaii:
   //Tolgo wider plasma
		MonsterZappaData.mass = TolgoWideBeamMass;
		MonsterZappaData.DamageICause = TolgoWideBeamDamage;
		MonsterZappaSpot.radius = TolgoWideBeamRadius;
		MonsterZappaSpot.point2.z = TolgoWideBeamLength;

		  matrix[3][1]=RLVal(0.57);
         if(MonsterAnimationFrame>=19 && StageNumber==0)
         {
            StageNumber=1;
            MonsterPlasmaDisplacement.y = RLVal(0.57);
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
            WhereIsIt=MonsterTailSpots[RoggoshTail].position;
            Scene=RLFrameGetScene(WhereIsIt);
            RLFrameAddChild(WhereIsIt,monstspew);
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            ZappaOnScreen=1;
            ZappaHowLong=TolgoWideBeamDuration;
            RLFrameGetPosition(WhereIsIt,Scene,&MonsterZappaData.ProjectedPosition);
            MonsterZappaData.CurrentPosition.x=MonsterZappaData.ProjectedPosition.x;
            MonsterZappaData.CurrentPosition.y=MonsterZappaData.ProjectedPosition.y;
            MonsterZappaData.CurrentPosition.z=MonsterZappaData.ProjectedPosition.z;
            MonsterZappaData.RemoveMeFlag=0;
            MonsterZappaData.collisionflag=0;
            AddMovingObject(&MonsterZappaData);

            YBPlay3DSound(MonsterTailZap, monstframe);

            RLFrameSetRotation(monstspew, monstspew, 0, 0, RLVal(1), TailZapRotation);
         }
         if(MonsterAnimationFrame>=21 && StageNumber==1)
         {
       RLValue SpewScale = RLVal(1.1);
            StageNumber=2;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=23 && StageNumber==2)
         {
       RLValue SpewScale = RLVal(1.3);
            StageNumber=3;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=25 && StageNumber==3)
         {
       RLValue SpewScale = RLVal(1.6);
            StageNumber=4;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=27 && StageNumber==4)
         {
       RLValue SpewScale = RLVal(1.9);
            StageNumber=5;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=29 && StageNumber==5)
         {
       RLValue SpewScale = RLVal(2.2);
            StageNumber=6;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=31 && StageNumber==6)
         {
       RLValue SpewScale = RLVal(2.5);
            StageNumber=7;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=33 && StageNumber==7)
         {
       RLValue SpewScale = RLVal(2.8);
            StageNumber=8;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=35 && StageNumber==8)
         {
       RLValue SpewScale = RLVal(3.1);
            StageNumber=9;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=37 && StageNumber==9)
         {
       RLValue SpewScale = RLVal(3.4);
            StageNumber=10;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=39 && StageNumber==10)
         {
       RLValue SpewScale = RLVal(3.7);
            StageNumber=11;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=41 && StageNumber==11)
         {
       RLValue SpewScale = RLVal(4.0);
            StageNumber=12;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=43 && StageNumber==12)
         {
       RLValue SpewScale = RLVal(3.7);
            StageNumber=13;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=44 && StageNumber==13)
         {
       RLValue SpewScale = RLVal(3.1);
            StageNumber=14;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=45 && StageNumber==14)
         {
       RLValue SpewScale = RLVal(2.5);
            StageNumber=15;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=46 && StageNumber==15)
         {
       RLValue SpewScale = RLVal(1.9);
            StageNumber=16;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=47 && StageNumber==16)
         {
       RLValue SpewScale = RLVal(1.3);
            StageNumber=17;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
         if(MonsterAnimationFrame>=48 && StageNumber==17)
         {
       RLValue SpewScale = RLVal(1.0);
            StageNumber=18;
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            RLFrameAddScale(monstspew,RLCombineBefore,SpewScale,SpewScale,SpewScale);
            MonsterZappaSpot.radius=RLMultiply(SpewScale,MonsterZapRadius);
            MonsterZappaSpot.point2.z=RLMultiply(SpewScale,MonsterZapLength);
            
         }
   //hawaii
      break;
      case SanFrancisco:
   //Shagtoq ground lightning
		MonsterZappaData.mass = ShagtoqGroundZapMass;
		MonsterZappaData.DamageICause = ShagtoqGroundZapDamage;
		MonsterZappaSpot.radius = ShagtoqGroundZapRadius;
		MonsterZappaSpot.point2.z = ShagtoqGroundZapLength;

		  if(MonsterAnimationFrame>=17 && StageNumber==0)
         {
            RLVector Worker1;
            StageNumber=1;
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
            WhereIsIt=MonsterTailSpots[RoggoshTail].position;
            Scene=RLFrameGetScene(WhereIsIt);
            RLFrameAddChild(WhereIsIt,monstspew);
            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            ZappaOnScreen=1;
            ZappaHowLong=ShagtoqIntoGroundDuration;
            RLFrameGetPosition(WhereIsIt,Scene,&MonsterZappaData.ProjectedPosition);
            MonsterZappaData.CurrentPosition.x=MonsterZappaData.ProjectedPosition.x;
            MonsterZappaData.CurrentPosition.y=MonsterZappaData.ProjectedPosition.y;
            MonsterZappaData.CurrentPosition.z=MonsterZappaData.ProjectedPosition.z;
            MonsterZappaData.RemoveMeFlag=0;
            MonsterZappaData.collisionflag=0;
            AddMovingObject(&MonsterZappaData);
            YBPlay3DSound(MonsterTailZap, monstframe);
            RLFrameSetRotation(monstspew, monstspew, 0, 0, RLVal(1), TailZapRotation);
            RLFrameGetPosition(Robotframe,Scene,&Worker1);
            LightningDirection.x=-MonsterZappaData.ProjectedPosition.x+ShagtoqTarget.x;
            LightningDirection.z=-MonsterZappaData.ProjectedPosition.z+ShagtoqTarget.z;
            LightningDirection.y=0;
            RLVectorNormalise(&LightningDirection);
            LightningDirection.y=1;
            ShagtoqTarget.x=Worker1.x-LightningDirection.x;
            ShagtoqTarget.y=Worker1.y;
            ShagtoqTarget.z=Worker1.z-LightningDirection.z;
//            ShagtoqTarget.y+=1;
         }
         else if(MonsterAnimationFrame>=27 && StageNumber==1)
         {
            StageNumber=2;
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
            WhereIsIt=MonsterTailSpots[RoggoshTail].position;
            Scene=RLFrameGetScene(WhereIsIt);
            RLFrameAddChild(Scene,monstspew);
            RLFrameSetPosition(monstspew,Scene,ShagtoqTarget.x,ShagtoqTarget.y,ShagtoqTarget.z);
            RLFrameSetOrientation(monstspew,Scene,
                                  LightningDirection.x,LightningDirection.y,LightningDirection.z,
                                  0,1,0);
//            RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
            ZappaOnScreen=1;
            ZappaHowLong=ShagtoqOutOfGroundDuration;
            RLFrameGetPosition(monstspew,Scene,&MonsterZappaData.ProjectedPosition);
            MonsterZappaData.CurrentPosition.x=MonsterZappaData.ProjectedPosition.x;
            MonsterZappaData.CurrentPosition.y=MonsterZappaData.ProjectedPosition.y;
            MonsterZappaData.CurrentPosition.z=MonsterZappaData.ProjectedPosition.z;
            MonsterZappaData.RemoveMeFlag=0;
            MonsterZappaData.collisionflag=0;
            AddMovingObject(&MonsterZappaData);
            YBPlay3DSound(MonsterTailZap, monstframe);
            RLFrameSetRotation(monstspew, monstspew, 0, 0, RLVal(1), TailZapRotation);
         }

   //San Fran
      break;
      case NewYork:
   //Nealloth sonic mouth rings
         if(MonsterAnimationFrame>=17 && StageNumber==0)
         {
            StageNumber=1;

   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
            WhereIsIt=MonsterHotSpots[RoggoshLeftClaw].position;
            Scene=RLFrameGetScene(WhereIsIt);
            RLFrameGetOrientation(WhereIsIt,Scene,&dir, &up);
            RLFrameGetPosition(WhereIsIt,Scene,&position);
            RLFrameSetPosition(NeallothRings->particles[0]->frame,Scene,position.x,position.y,position.z);
            RLFrameSetOrientation(NeallothRings->particles[0]->frame,Scene,
                                    -dir.x,-dir.y,-dir.z,
                                    up.x,up.y,up.z);
            NeallothRings->particles[0]->active=2;
            NRingsHowLong[0]=NeallothRingsDuration;
//            NRingSpeed=NeallothRingsSpeed;

            NeallothRingsData[0].ProjectedPosition.x=position.x;
            NeallothRingsData[0].ProjectedPosition.y=position.y;
            NeallothRingsData[0].ProjectedPosition.z=position.z;
            NeallothRingsData[0].RemoveMeFlag=0;
            NeallothRingsData[0].collisionflag=0;
            NeallothRingsData[0].DamageICause=NeallothRingsDamage;
            AddMovingObject(&(NeallothRingsData[0]));

            YBPlay3DSound(MonsterSomethin, monstframe);

         }
         else if(MonsterAnimationFrame>=22 && StageNumber==1)
         {
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
            WhereIsIt=MonsterHotSpots[RoggoshLeftClaw].position;
            Scene=RLFrameGetScene(WhereIsIt);
            RLFrameGetOrientation(WhereIsIt,Scene,&dir, &up);
            RLFrameGetPosition(WhereIsIt,Scene,&position);
            RLFrameSetPosition(NeallothRings->particles[StageNumber]->frame,Scene,position.x,position.y,position.z);
            RLFrameSetOrientation(NeallothRings->particles[StageNumber]->frame,Scene,
                                    -dir.x,-dir.y,-dir.z,
                                    up.x,up.y,up.z);

            NeallothRings->particles[StageNumber]->active=2;
            NRingsHowLong[StageNumber]=NeallothRingsDuration;
            NeallothRingsData[StageNumber].ProjectedPosition.x=position.x;
            NeallothRingsData[StageNumber].ProjectedPosition.y=position.y;
            NeallothRingsData[StageNumber].ProjectedPosition.z=position.z;
            NeallothRingsData[StageNumber].RemoveMeFlag=0;
            NeallothRingsData[StageNumber].collisionflag=0;
            NeallothRingsData[StageNumber].DamageICause=NeallothRingsDamage;
            AddMovingObject(&(NeallothRingsData[StageNumber]));

            YBPlay3DSound(MonsterSomethin, monstframe);
            StageNumber=2;
         }
         else if(MonsterAnimationFrame>=27 && StageNumber==2)
         {
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
            WhereIsIt=MonsterHotSpots[RoggoshLeftClaw].position;
            Scene=RLFrameGetScene(WhereIsIt);
            RLFrameGetOrientation(WhereIsIt,Scene,&dir, &up);
            RLFrameGetPosition(WhereIsIt,Scene,&position);
            RLFrameSetPosition(NeallothRings->particles[StageNumber]->frame,Scene,position.x,position.y,position.z);
            RLFrameSetOrientation(NeallothRings->particles[StageNumber]->frame,Scene,
                                    -dir.x,-dir.y,-dir.z,
                                    up.x,up.y,up.z);

            NeallothRings->particles[StageNumber]->active=2;
            NRingsHowLong[StageNumber]=NeallothRingsDuration;
            NeallothRingsData[StageNumber].ProjectedPosition.x=position.x;
            NeallothRingsData[StageNumber].ProjectedPosition.y=position.y;
            NeallothRingsData[StageNumber].ProjectedPosition.z=position.z;
            NeallothRingsData[StageNumber].RemoveMeFlag=0;
            NeallothRingsData[StageNumber].collisionflag=0;
            NeallothRingsData[StageNumber].DamageICause=NeallothRingsDamage;
            AddMovingObject(&(NeallothRingsData[StageNumber]));

            YBPlay3DSound(MonsterSomethin, monstframe);
            StageNumber=3;
         }
         else if(MonsterAnimationFrame>=32 && StageNumber==3)
         {
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
            WhereIsIt=MonsterHotSpots[RoggoshLeftClaw].position;
            Scene=RLFrameGetScene(WhereIsIt);
            RLFrameGetOrientation(WhereIsIt,Scene,&dir, &up);
            RLFrameGetPosition(WhereIsIt,Scene,&position);
            RLFrameSetPosition(NeallothRings->particles[StageNumber]->frame,Scene,position.x,position.y,position.z);
            RLFrameSetOrientation(NeallothRings->particles[StageNumber]->frame,Scene,
                                    -dir.x,-dir.y,-dir.z,
                                    up.x,up.y,up.z);

            NeallothRings->particles[StageNumber]->active=2;
            NRingsHowLong[StageNumber]=NeallothRingsDuration;
            NeallothRingsData[StageNumber].ProjectedPosition.x=position.x;
            NeallothRingsData[StageNumber].ProjectedPosition.y=position.y;
            NeallothRingsData[StageNumber].ProjectedPosition.z=position.z;
            NeallothRingsData[StageNumber].RemoveMeFlag=0;
            NeallothRingsData[StageNumber].collisionflag=0;
            NeallothRingsData[StageNumber].DamageICause=NeallothRingsDamage;
            AddMovingObject(&(NeallothRingsData[StageNumber]));

            YBPlay3DSound(MonsterSomethin, monstframe);
            StageNumber=4;
         }
         else if(MonsterAnimationFrame>=37 && StageNumber==4)
         {
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
            WhereIsIt=MonsterHotSpots[RoggoshLeftClaw].position;
            Scene=RLFrameGetScene(WhereIsIt);
            RLFrameGetOrientation(WhereIsIt,Scene,&dir, &up);
            RLFrameGetPosition(WhereIsIt,Scene,&position);
            RLFrameSetPosition(NeallothRings->particles[StageNumber]->frame,Scene,position.x,position.y,position.z);
            RLFrameSetOrientation(NeallothRings->particles[StageNumber]->frame,Scene,
                                    -dir.x,-dir.y,-dir.z,
                                    up.x,up.y,up.z);

            NeallothRings->particles[StageNumber]->active=2;
            NRingsHowLong[StageNumber]=NeallothRingsDuration;
            NeallothRingsData[StageNumber].ProjectedPosition.x=position.x;
            NeallothRingsData[StageNumber].ProjectedPosition.y=position.y;
            NeallothRingsData[StageNumber].ProjectedPosition.z=position.z;
            NeallothRingsData[StageNumber].RemoveMeFlag=0;
            NeallothRingsData[StageNumber].collisionflag=0;
            NeallothRingsData[StageNumber].DamageICause=NeallothRingsDamage;
            AddMovingObject(&(NeallothRingsData[StageNumber]));

            YBPlay3DSound(MonsterSomethin, monstframe);
            StageNumber=5;
         }
         else if(MonsterAnimationFrame>=42 && StageNumber==5)
         {
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
            WhereIsIt=MonsterHotSpots[RoggoshLeftClaw].position;
            Scene=RLFrameGetScene(WhereIsIt);
            RLFrameGetOrientation(WhereIsIt,Scene,&dir, &up);
            RLFrameGetPosition(WhereIsIt,Scene,&position);
            RLFrameSetPosition(NeallothRings->particles[StageNumber]->frame,Scene,position.x,position.y,position.z);
            RLFrameSetOrientation(NeallothRings->particles[StageNumber]->frame,Scene,
                                    -dir.x,-dir.y,-dir.z,
                                    up.x,up.y,up.z);

            NeallothRings->particles[StageNumber]->active=2;
            NRingsHowLong[StageNumber]=NeallothRingsDuration;
            NeallothRingsData[StageNumber].ProjectedPosition.x=position.x;
            NeallothRingsData[StageNumber].ProjectedPosition.y=position.y;
            NeallothRingsData[StageNumber].ProjectedPosition.z=position.z;
            NeallothRingsData[StageNumber].RemoveMeFlag=0;
            NeallothRingsData[StageNumber].collisionflag=0;
            NeallothRingsData[StageNumber].DamageICause=NeallothRingsDamage;
            AddMovingObject(&(NeallothRingsData[StageNumber]));

            YBPlay3DSound(MonsterSomethin, monstframe);
            StageNumber=6;
         }

   //NYNY
      break;
      case Tokyo:
   //Gaingris powerbomb
         if(MonsterAnimationFrame>=22 && StageNumber==0)
         {//turn on nuke.
//            FILE *shithead;
  //          shithead=fopen("shit.out","a");
    //        fprintf(shithead,"\n\nstarting a new bomb!!!!!!!!!!!!\n");
      //      fclose(shithead);
            StageNumber=1;
            Scene=RLFrameGetScene(monstframe);
            RLFrameGetPosition(monstframe,Scene,&position);
            RLFrameAddChild(Scene,BombSphere);
            RLFrameAddScale(BombSphere,RLCombineReplace,RLVal(1),RLVal(1),RLVal(1));
            RLFrameSetPosition(BombSphere,Scene,position.x,position.y,position.z);
            BombData.ProjectedPosition.x=position.x;
            BombData.ProjectedPosition.y=position.y;
            BombData.ProjectedPosition.z=position.z;
            BombData.CurrentPosition.x=position.x;
            BombData.CurrentPosition.y=position.y;
            BombData.CurrentPosition.z=position.z;
            BombData.RemoveMeFlag=0;
            BombData.collisionflag=0;
            BombData.DamageICause=GaingrisNukeDamage;
            AddMovingObject(&BombData);
            BombSpot.radius=RLVal(1.0);
            BombHowLong=RLVal(0.0);

            YBPlay3DSound(MonsterSomethin, monstframe);

         }
         else if(MonsterAnimationFrame>=51 && StageNumber==1)
         {//turn off nuke.
            StageNumber=2;
            RLFrameAddChild(behindthescene,BombSphere);
            BombData.RemoveMeFlag=1;
         }

   //Tokyo
      break;
   }

   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
}



static void MonsterBlockMediumFirstFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
}

static void MonsterBlockMediumFreezeFunction(void)
{
//This function keeps the frame frozen at the appropriate frame.
   MonsterAnimationFrame=MonsterAnimations[MonsterAnimationState].StopFrame;
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
}

static void MonsterBlockMediumLastFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
}


static void MonsterChestHitLeft2Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
}

static void MonsterKnockDown2Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
}

static void MonsterGetBackUp2Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
}

static void MonsterDontGetBackUp2Function(void)
{
//This function freezes on one frame, 'cause yer dead.
//   MonsterData.RemoveMeFlag=1;
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
}

static void MonsterPickUpObjectFirstFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
}

static void MonsterPickUpObjectFreezeFunction(void)
{
//This function keeps the frame frozen at the appropriate frame.
   MonsterAnimationFrame=MonsterAnimations[MonsterAnimationState].StopFrame;
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
}

static void MonsterPickUpObjectLastFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
}

static void MonsterThrowObjectFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
}

static void MonsterTaunt1Function(void)
{
//This function increments automatically, and loops when it reaches the end.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
//   if(!NumMonsterTaunts)
  // {
      if(MonsterAnimationFrame>=MonsterAnimations[MonsterAnimationState].StopFrame)
      {
    //     NumMonsterTaunts=1;
      //   YBPlay3DSound(MonsterWail, monstframe);
	      YBPlay3DSound(MonsterWail, monstframe);

		  MonsterAnimationFrame-=MonsterAnimations[MonsterAnimationState].NumFrames;
      }
//   }
  // else
//   {
  //    if(MonsterAnimationFrame>=MonsterAnimations[MonsterAnimationState].StopFrame)
    //     MonsterAnimationFrame=MonsterAnimations[MonsterAnimationState].StopFrame;
   //}
}

static void MonsterTaunt2Function(void)
{
//This function increments automatically, and loops when it reaches the end.
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
   if(MonsterAnimationFrame>=MonsterAnimations[MonsterAnimationState].StopFrame)
      MonsterAnimationFrame=MonsterAnimations[MonsterAnimationState].StopFrame;
}

static void MonsterAllDeadFunction(void)
{
//This function freezes on one frame, 'cause yer dead.
//   MonsterData.RemoveMeFlag=1;
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
}

static void MonsterTravelFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
//   extern int level;
      RLMatrix4d matrix=
      {
         {RLVal(1),0,0,0},
         {0,RLVal(1),0,0},
         {0,0,RLVal(-1),0},
         {0,0,0,RLVal(1)}
      };
   
   if(((GameStates.CurrentLevel==Mojave)) && !ZappaOnScreen)
   {
      RLFrame WhereIsIt;
      RLFrame Scene;
   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
      WhereIsIt=MonsterTailSpots[RoggoshTail].position;
	  Scene=RLFrameGetScene(WhereIsIt);
      RLFrameAddChild(WhereIsIt,monstspew);
      RLFrameAddTransform(monstspew,RLCombineReplace,matrix);
      ZappaOnScreen=1;
      ZappaHowLong=TailZapDuration*4;
      RLFrameGetPosition(WhereIsIt,Scene,&MonsterZappaData.ProjectedPosition);
     MonsterZappaData.CurrentPosition.x=MonsterZappaData.ProjectedPosition.x;
     MonsterZappaData.CurrentPosition.y=MonsterZappaData.ProjectedPosition.y;
     MonsterZappaData.CurrentPosition.z=MonsterZappaData.ProjectedPosition.z;
      MonsterZappaData.RemoveMeFlag=0;
      MonsterZappaData.collisionflag=0;
      AddMovingObject(&MonsterZappaData);
      YBPlay3DSound(MonsterTailZap, monstframe);
      
      RLFrameSetRotation(monstspew, monstspew, 0, 0, RLVal(1), TailZapRotation);
   }

   RLAnimationSetSetTime(MonsterAnimations[MonsterAnimationState].Anisette, MonsterAnimationFrame);
   MonsterAnimationFrame+=DiffFrame;
   if(MonsterAnimationFrame>MonsterTravelLastFrame)
      MonsterAnimationFrame=MonsterTravelFirstFrame;
}


extern RLError RLLoadXAFAsList(const char* filename,
            size_t*, RLObject**); /* XXX */

void tenderize(void)
{
   int i;
//   FILE *shithead;
   MnstEngy-=MonsterAnimations[MonsterAnimationState].EnergyDrain;
   if(MnstEngy>MaxMnstEngy)
   {
      MnstLife+=((MnstEngy-MaxMnstEngy)/MonsterEnergyToLifeConversion);
      if(MnstLife>MaxMnstLife) 
         MnstLife=MaxMnstLife;
      MnstEngy=MaxMnstEngy;
   }

   (MonsterAnimations[MonsterAnimationState].WhatToDo)();

   for(i=0;(i<MonsterAnimations[MonsterAnimationState].numchanges) ;i++ )
      if(  (MonsterAnimations[MonsterAnimationState].ChangeList[i]) () )
         break;
}



void GetMonsterAnimInfo(FILE *input)
{
#ifdef ErrorsOut
   FILE *errors;
#endif
   char decision[1];
   char movename[64];
   char dumstring[256];
   extern RLValue MonsterScaleFactor;
#ifdef ErrorsOut
   errors=fopen("error.out","a");
   fprintf(errors,"getting monster animation info.\n");
#endif
   while (!feof(input))
   {
      fscanf(input," %1s",decision);
      
      switch(*decision)
      {
         case '{':
            fscanf(input,"%[^}]",dumstring);
#ifdef ErrorsOut
            fprintf(errors,"comment #%s#\n",dumstring);
#endif
            fscanf(input,"}");
         break;
         case '!':
            fscanf(input," %s",movename);
            if(!stricmp("MonsterWalkForwardDistance",movename))
            {
               fscanf(input," %f",&MonsterWalkForwardDistance);
               MonsterWalkForwardDistance=RLMultiply(MonsterWalkForwardDistance,MonsterScaleFactor);
            }
            else if(!stricmp("MonsterWalkBackDistance",movename))
            {
               fscanf(input," %f",&MonsterWalkBackDistance);
               MonsterWalkBackDistance=RLMultiply(MonsterWalkBackDistance,MonsterScaleFactor);
            }
            else if(!stricmp("MonsterSideStepLeftDistance",movename))
            {
               fscanf(input," %f",&MonsterSideStepLeftDistance);
               MonsterSideStepLeftDistance=RLMultiply(MonsterSideStepLeftDistance,MonsterScaleFactor);
            }
            else if(!stricmp("MonsterSideStepRightDistance",movename))
            {
               fscanf(input," %f",&MonsterSideStepRightDistance);
               MonsterSideStepRightDistance=RLMultiply(MonsterSideStepRightDistance,MonsterScaleFactor);
            }
            else if(!stricmp("MonsterIntoRunDistance",movename))
            {
               fscanf(input," %f",&MonsterIntoRunDistance);
               MonsterIntoRunDistance=RLMultiply(MonsterIntoRunDistance,MonsterScaleFactor);
            }
            else if(!stricmp("MonsterRunDistance",movename))
            {
               fscanf(input," %f",&MonsterRunDistance);
               MonsterRunDistance=RLMultiply(MonsterRunDistance,MonsterScaleFactor);
            }
            else if(!stricmp("MonsterSkidDistance",movename))
            {
               fscanf(input," %f",&MonsterSkidDistance);
               MonsterSkidDistance=RLMultiply(MonsterSkidDistance,MonsterScaleFactor);
            }
            else if(!stricmp("MonsterKnockDown1Distance",movename))
            {
               fscanf(input," %f",&MonsterKnockDown1Distance);
               MonsterKnockDown1Distance=RLMultiply(MonsterKnockDown1Distance,MonsterScaleFactor);
            }
            else if(!stricmp("MonsterKnockDown2Distance",movename))
            {
               fscanf(input," %f",&MonsterKnockDown2Distance);
               MonsterKnockDown2Distance=RLMultiply(MonsterKnockDown2Distance,MonsterScaleFactor);
            }
            else if(!stricmp("MonsterKnockDown3Distance",movename))
            {
               fscanf(input," %f",&MonsterKnockDown3Distance);
               MonsterKnockDown3Distance=RLMultiply(MonsterKnockDown3Distance,MonsterScaleFactor);
            }
            else if(!stricmp("MonsterPause1EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterPause1EnergyDrain);
            }
            else if(!stricmp("MonsterWalkForwardEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterWalkForwardEnergyDrain);
            }
            else if(!stricmp("MonsterWalkBackEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterWalkBackEnergyDrain);
            }
            else if(!stricmp("MonsterJumpFirstEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterJumpFirstEnergyDrain);
            }
            else if(!stricmp("MonsterJumpFreezeEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterJumpFreezeEnergyDrain);
            }
            else if(!stricmp("MonsterJumpLastEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterJumpLastEnergyDrain);
            }
            else if(!stricmp("MonsterJumpStopEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterJumpStopEnergyDrain);
            }
            else if(!stricmp("MonsterSkidEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterSkidEnergyDrain);
            }
            else if(!stricmp("MonsterTravelEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterTravelEnergyDrain);
            }
            else if(!stricmp("MonsterIntoIntoRunEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterIntoIntoRunEnergyDrain);
            }
            else if(!stricmp("MonsterIntoRunEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterIntoRunEnergyDrain);
            }
            else if(!stricmp("MonsterHighAttack1EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterHighAttack1EnergyDrain);
            }
            else if(!stricmp("MonsterMediumAttack1EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterMediumAttack1EnergyDrain);
            }
            else if(!stricmp("MonsterLowAttack1EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterLowAttack1EnergyDrain);
            }
            else if(!stricmp("MonsterHighAttack2EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterHighAttack2EnergyDrain);
            }
            else if(!stricmp("MonsterMediumAttack2EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterMediumAttack2EnergyDrain);
            }
            else if(!stricmp("MonsterLowAttack2EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterLowAttack2EnergyDrain);
            }
            else if(!stricmp("MonsterJumpAttack1EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterJumpAttack1EnergyDrain);
            }
            else if(!stricmp("MonsterJumpAttack2EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterJumpAttack2EnergyDrain);
            }
            else if(!stricmp("MonsterSpecialAttack1EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterSpecialAttack1EnergyDrain);
            }
            else if(!stricmp("MonsterSpecialAttack2EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterSpecialAttack2EnergyDrain);
            }
            else if(!stricmp("MonsterBlockMediumFirstEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterBlockMediumFirstEnergyDrain);
            }
            else if(!stricmp("MonsterBlockMediumFreezeEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterBlockMediumFreezeEnergyDrain);
            }
            else if(!stricmp("MonsterBlockMediumLastEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterBlockMediumLastEnergyDrain);
            }
            else if(!stricmp("MonsterChestHitLeft2EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterChestHitLeft2EnergyDrain);
            }
            else if(!stricmp("MonsterKnockDown2EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterKnockDown2EnergyDrain);
            }
            else if(!stricmp("MonsterGetBackUp2EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterGetBackUp2EnergyDrain);
            }
            else if(!stricmp("MonsterPickUpObjectFirstEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterPickUpObjectFirstEnergyDrain);
            }
            else if(!stricmp("MonsterPickUpObjectFreezeEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterPickUpObjectFreezeEnergyDrain);
            }
            else if(!stricmp("MonsterPickUpObjectLastEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterPickUpObjectLastEnergyDrain);
            }
            else if(!stricmp("MonsterThrowObjectEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterThrowObjectEnergyDrain);
            }
            else if(!stricmp("MonsterTaunt1EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterTaunt1EnergyDrain);
            }
            else if(!stricmp("MonsterRunEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterRunEnergyDrain);
            }
            else if(!stricmp("MonsterPause1EnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterPause1EnergyMinimum);
            }
            else if(!stricmp("MonsterWalkForwardEnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterWalkForwardEnergyMinimum);
            }
            else if(!stricmp("MonsterWalkBackEnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterWalkBackEnergyMinimum);
            }
            else if(!stricmp("MonsterJumpFirstEnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterJumpFirstEnergyMinimum);
            }
            else if(!stricmp("MonsterJumpFreezeEnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterJumpFreezeEnergyMinimum);
            }
            else if(!stricmp("MonsterJumpLastEnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterJumpLastEnergyMinimum);
            }
            else if(!stricmp("MonsterJumpStopEnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterJumpStopEnergyMinimum);
            }
            else if(!stricmp("MonsterSkidEnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterSkidEnergyMinimum);
            }
            else if(!stricmp("MonsterTravelEnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterTravelEnergyMinimum);
            }
            else if(!stricmp("MonsterTravelBackEnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterTravelBackEnergyMinimum);
            }
            else if(!stricmp("MonsterIntoIntoRunEnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterIntoIntoRunEnergyMinimum);
            }
            else if(!stricmp("MonsterIntoRunEnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterIntoRunEnergyMinimum);
            }
            else if(!stricmp("MonsterRunEnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterRunEnergyMinimum);
            }
            else if(!stricmp("MonsterHighAttack1EnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterHighAttack1EnergyMinimum);
            }
            else if(!stricmp("MonsterMediumAttack1EnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterMediumAttack1EnergyMinimum);
            }
            else if(!stricmp("MonsterLowAttack1EnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterLowAttack1EnergyMinimum);
            }
            else if(!stricmp("MonsterHighAttack2EnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterHighAttack2EnergyMinimum);
            }
            else if(!stricmp("MonsterMediumAttack2EnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterMediumAttack2EnergyMinimum);
            }
            else if(!stricmp("MonsterLowAttack2EnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterLowAttack2EnergyMinimum);
            }
            else if(!stricmp("MonsterJumpAttack1EnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterJumpAttack1EnergyMinimum);
            }
            else if(!stricmp("MonsterJumpAttack2EnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterJumpAttack2EnergyMinimum);
            }
            else if(!stricmp("MonsterSpecialAttack1EnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterSpecialAttack1EnergyMinimum);
            }
            else if(!stricmp("MonsterSpecialAttack2EnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterSpecialAttack2EnergyMinimum);
            }
            else if(!stricmp("MonsterBlockMediumFirstEnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterBlockMediumFirstEnergyMinimum);
            }
            else if(!stricmp("MonsterBlockMediumFreezeEnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterBlockMediumFreezeEnergyMinimum);
            }
            else if(!stricmp("MonsterBlockMediumLastEnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterBlockMediumLastEnergyMinimum);
            }
            else if(!stricmp("MonsterChestHitLeft2EnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterChestHitLeft2EnergyMinimum);
            }
            else if(!stricmp("MonsterKnockDown2EnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterKnockDown2EnergyMinimum);
            }
            else if(!stricmp("MonsterGetBackUp2EnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterGetBackUp2EnergyMinimum);
            }
            else if(!stricmp("MonsterPickUpObjectFirstEnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterPickUpObjectFirstEnergyMinimum);
            }
            else if(!stricmp("MonsterPickUpObjectFreezeEnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterPickUpObjectFreezeEnergyMinimum);
            }
            else if(!stricmp("MonsterPickUpObjectLastEnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterPickUpObjectLastEnergyMinimum);
            }
            else if(!stricmp("MonsterThrowObjectEnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterThrowObjectEnergyMinimum);
            }
            else if(!stricmp("MonsterTaunt1EnergyMinimum",movename))
            {
               fscanf(input," %d",&MonsterTaunt1EnergyMinimum);
            }
            else if(!stricmp("TailZapDuration",movename))
            {
               fscanf(input," %d",&TailZapDuration);
            }
            else if(!stricmp("TailZapRotation",movename))
            {
               fscanf(input," %f",&TailZapRotation);
            }
            else if(!stricmp("RoggoshHomerDuration",movename))
            {
               fscanf(input," %d",&RoggoshHomerDuration);
            }
            else if(!stricmp("TolgoPunchDamage",movename))
            {
               fscanf(input," %d",&TolgoPunchDamage);
            }
            else if(!stricmp("ShagtoqSpewDuration",movename))
            {
               fscanf(input," %d",&ShagtoqSpewDuration);
            }
            else if(!stricmp("NeallothEyeboltDuration",movename))
            {
               fscanf(input," %d",&NeallothEyeboltDuration);
            }
            else if(!stricmp("GaingrisMultiblastDuration",movename))
            {
               fscanf(input," %d",&GaingrisMultiblastDuration);
            }
            else if(!stricmp("RoggoshTripleDuration",movename))
            {
               fscanf(input," %d",&RoggoshTripleDuration);
            }
            else if(!stricmp("KothosJumpAttackDuration",movename))
            {
               fscanf(input," %d",&KothosJumpAttackDuration);
            }
            else if(!stricmp("TolgoWideBeamDuration",movename))
            {
               fscanf(input," %d",&TolgoWideBeamDuration);
            }
            else if(!stricmp("ShagtoqIntoGroundDuration",movename))
            {
               fscanf(input," %d",&ShagtoqIntoGroundDuration);
            }
            else if(!stricmp("ShagtoqOutOfGroundDuration",movename))
            {
               fscanf(input," %d",&ShagtoqOutOfGroundDuration);
            }
            else if(!stricmp("NeallothRingsDuration",movename))
            {
               fscanf(input," %d",&NeallothRingsDuration);
            }
            else if(!stricmp("NeallothRingsDamage",movename))
            {
               fscanf(input," %d",&NeallothRingsDamage);
            }
            else if(!stricmp("NeallothRingsSpeed",movename))
            {
               fscanf(input," %f",&NeallothRingsSpeed);
            }
            else if(!stricmp("NeallothRingsRadius",movename))
            {
               fscanf(input," %f",&NeallothRingsRadius);
            }
            else if(!stricmp("RoggoshTripleZapLength",movename))
            {
               fscanf(input," %f",&RoggoshTripleZapLength);
            }
            else if(!stricmp("RoggoshTripleZapRadius",movename))
            {
               fscanf(input," %f",&RoggoshTripleZapRadius);
            }
            else if(!stricmp("RoggoshTripleZapMass",movename))
            {
               fscanf(input," %f",&RoggoshTripleZapMass);
            }
			else if(!stricmp("RoggoshTripleZapDamage",movename))
            {
               fscanf(input," %d",&RoggoshTripleZapDamage);
            }
            else if(!stricmp("TolgoWideBeamLength",movename))
            {
               fscanf(input," %f",&TolgoWideBeamLength);
            }
            else if(!stricmp("TolgoWideBeamRadius",movename))
            {
               fscanf(input," %f",&TolgoWideBeamRadius);
            }
            else if(!stricmp("TolgoWideBeamMass",movename))
            {
               fscanf(input," %f",&TolgoWideBeamMass);
            }
			else if(!stricmp("TolgoWideBeamDamage",movename))
            {
               fscanf(input," %d",&TolgoWideBeamDamage);
            }
            else if(!stricmp("ShagtoqGroundZapLength",movename))
            {
               fscanf(input," %f",&ShagtoqGroundZapLength);
            }
            else if(!stricmp("ShagtoqGroundZapRadius",movename))
            {
               fscanf(input," %f",&ShagtoqGroundZapRadius);
            }
            else if(!stricmp("ShagtoqGroundZapMass",movename))
            {
               fscanf(input," %f",&ShagtoqGroundZapMass);
            }
			else if(!stricmp("ShagtoqGroundZapDamage",movename))
            {
               fscanf(input," %d",&ShagtoqGroundZapDamage);
            }
            else if(!stricmp("ShagtoqSpewLength",movename))
            {
               fscanf(input," %f",&ShagtoqSpewLength);
            }
            else if(!stricmp("ShagtoqSpewRadius",movename))
            {
               fscanf(input," %f",&ShagtoqSpewRadius);
            }
            else if(!stricmp("ShagtoqSpewMass",movename))
            {
               fscanf(input," %f",&ShagtoqSpewMass);
            }
			else if(!stricmp("ShagtoqSpewDamage",movename))
            {
               fscanf(input," %d",&ShagtoqSpewDamage);
            }
            else if(!stricmp("NeallothDiveBombLength",movename))
            {
               fscanf(input," %f",&NeallothDiveBombLength);
            }
            else if(!stricmp("NeallothDiveBombRadius",movename))
            {
               fscanf(input," %f",&NeallothDiveBombRadius);
            }
            else if(!stricmp("NeallothDiveBombMass",movename))
            {
               fscanf(input," %f",&NeallothDiveBombMass);
            }
			else if(!stricmp("NeallothDiveBombDamage",movename))
            {
               fscanf(input," %d",&NeallothDiveBombDamage);
            }
            else if(!stricmp("GaingrisTripleZapLength",movename))
            {
               fscanf(input," %f",&GaingrisTripleZapLength);
            }
            else if(!stricmp("GaingrisTripleZapRadius",movename))
            {
               fscanf(input," %f",&GaingrisTripleZapRadius);
            }
            else if(!stricmp("GaingrisTripleZapMass",movename))
            {
               fscanf(input," %f",&GaingrisTripleZapMass);
            }
			else if(!stricmp("GaingrisTripleZapDamage",movename))
            {
               fscanf(input," %d",&GaingrisTripleZapDamage);
            }
            else if(!stricmp("KothosJumpAttackLength",movename))
            {
               fscanf(input," %f",&KothosJumpAttackLength);
            }
            else if(!stricmp("KothosJumpAttackRadius",movename))
            {
               fscanf(input," %f",&KothosJumpAttackRadius);
            }
            else if(!stricmp("KothosJumpAttackMass",movename))
            {
               fscanf(input," %f",&KothosJumpAttackMass);
            }
			else if(!stricmp("KothosJumpAttackDamage",movename))
            {
               fscanf(input," %d",&KothosJumpAttackDamage);
            }
            else if(!stricmp("MonsterZapLength",movename))
            {
               fscanf(input," %f",&MonsterZapLength);
            }
            else if(!stricmp("MonsterZapRadius",movename))
            {
               fscanf(input," %f",&MonsterZapRadius);
            }
            else if(!stricmp("MonsterZapMass",movename))
            {
               fscanf(input," %f",&MonsterZapMass);
            }
			else if(!stricmp("MonsterZapDamage",movename))
            {
               fscanf(input," %d",&MonsterZapDamage);
            }
			else if(!stricmp("GaingrisNukeDamage",movename))
            {
               fscanf(input," %d",&GaingrisNukeDamage);
            }
            else if(!stricmp("GaingrisNukeMaxRadius",movename))
            {
               fscanf(input," %f",&GaingrisNukeMaxRadius);
            }
            else if(!stricmp("GaingrisNukeVelocity",movename))
            {
               fscanf(input," %f",&GaingrisNukeVelocity);
            }
            else if(!stricmp("GaingrisNukeInitRadius",movename))
            {
               fscanf(input," %f",&GaingrisNukeInitRadius);
            }
            else if(!stricmp("GaingrisRadius",movename))
            {
               fscanf(input," %f",&GaingrisRadius);
            }
            else if(!stricmp("KothosSnowballInitRadius",movename))
            {
               fscanf(input," %f",&KothosSnowballInitRadius);
            }
            else if(!stricmp("KothosSnowballGrowthRate",movename))
            {
               fscanf(input," %f",&KothosSnowballGrowthRate);
            }
            else if(!stricmp("KothosSnowballDuration",movename))
            {
               fscanf(input," %f",&KothosSnowballDuration);
            }
            else if(!stricmp("KothosSnowballDamage",movename))
            {
               fscanf(input," %d",&KothosSnowballDamage);
            }
            else if(!stricmp("KSnowballGradientFactor",movename))
            {
               fscanf(input," %d",&KSnowballGradientFactor);
            }
            else if(!stricmp("MonsterEnergyToLifeConversion",movename))
            {
               fscanf(input," %d",&MonsterEnergyToLifeConversion);
            }
            else if(!stricmp("MonsterArmor",movename))
            {
               fscanf(input," %f",&MonsterArmor);
            }
            else if(!stricmp("InitialMonsterLife",movename))
            {
               fscanf(input," %d",&InitialMonsterLife);
            }
            else if(!stricmp("MonsterFalldownThreshold",movename))
            {
               fscanf(input," %d",&MonsterFalldownThreshold);
            }
            else
            {
#ifdef ErrorsOut
               fprintf(errors,"Unknown keyword: #%s#\n",movename);
#endif
               fgets(dumstring,256,input);
#ifdef ErrorsOut
               fprintf(errors,"ignoring line: #%s#\n",dumstring);
#endif
            }
         break;
         default:
            if(feof(input))
            {
#ifdef ErrorsOut
               fprintf(errors,"Reached an EOF\n");
               fclose(errors);
#endif
               return;
            }
#ifdef ErrorsOut
            fprintf(errors,"Unknown symbol: '%c', %d\n",*decision,*decision);
#endif
            fgets(dumstring,256,input);
#ifdef ErrorsOut
            fprintf(errors,"ignoring line: #%s#\n",dumstring);
#endif
         break;
      }
   }
#ifdef ErrorsOut
   fprintf(errors,"terminated normally\n\n");
   fclose(errors);
#endif
}                                                          










void DefineMonsterAnimationConstants()
{
//   extern int level;
   switch (GameStates.CurrentLevel)
   {
      case Trainer:
      case Mojave:
	     MonsterTravelFirstFrame =RLVal(24);
         MonsterTravelLastFrame = RLVal(42);
	  break;
      case Rockies:
	     MonsterTravelFirstFrame =RLVal(06);
         MonsterTravelLastFrame = RLVal(57);
	  break;
      case Hawaii:
	     MonsterTravelFirstFrame =RLVal(24);
         MonsterTravelLastFrame = RLVal(52);
	  break;
      case SanFrancisco:
	     MonsterTravelFirstFrame =RLVal(8);
         MonsterTravelLastFrame = RLVal(59);
	  break;
      case NewYork:
	     MonsterTravelFirstFrame =RLVal(15);
         MonsterTravelLastFrame = RLVal(32);
	  break;
      case Tokyo:
	     MonsterTravelFirstFrame =RLVal(15);
         MonsterTravelLastFrame = RLVal(33);
	  break;

   }
   MonsterAnimations[MonsterPause1].Distance= MonsterPause1Distance;
   MonsterAnimations[MonsterWalkForward].Distance= MonsterWalkForwardDistance;
   MonsterAnimations[MonsterWalkBack].Distance= MonsterWalkBackDistance;
   MonsterAnimations[MonsterJumpFirst].Distance= MonsterJumpDistance;
   MonsterAnimations[MonsterJumpFreeze].Distance= MonsterJumpDistance;
   MonsterAnimations[MonsterJumpLast].Distance= MonsterJumpDistance;
   MonsterAnimations[MonsterJumpStop].Distance= MonsterJumpDistance;
   MonsterAnimations[MonsterTravel].Distance=MonsterTravelDistance;

   MonsterAnimations[MonsterSkid].Distance= MonsterSkidDistance;

   MonsterAnimations[MonsterIntoIntoRun].Distance= 0;
   MonsterAnimations[MonsterIntoRun].Distance= MonsterIntoRunDistance;
   MonsterAnimations[MonsterRun].Distance= MonsterRunDistance;
   MonsterAnimations[MonsterHighAttack1].Distance= MonsterHighAttack1Distance;
   MonsterAnimations[MonsterMediumAttack1].Distance= MonsterMediumAttack1Distance;
   MonsterAnimations[MonsterLowAttack1].Distance= MonsterLowAttack1Distance;

   MonsterAnimations[MonsterMediumAttack2].Distance= MonsterMediumAttack2Distance;
   MonsterAnimations[MonsterLowAttack2].Distance= MonsterLowAttack2Distance;

   MonsterAnimations[MonsterJumpAttack1].Distance= MonsterJumpAttack1Distance;
   MonsterAnimations[MonsterJumpAttack2].Distance= MonsterJumpAttack2Distance;
   MonsterAnimations[MonsterSpecialAttack1].Distance= MonsterSpecialAttack1Distance;
   MonsterAnimations[MonsterSpecialAttack2].Distance= MonsterSpecialAttack2Distance;

   MonsterAnimations[MonsterBlockMediumFirst].Distance= MonsterBlockMediumDistance;
   MonsterAnimations[MonsterBlockMediumFreeze].Distance= MonsterBlockMediumDistance;
   MonsterAnimations[MonsterBlockMediumLast].Distance= MonsterBlockMediumDistance;
   MonsterAnimations[MonsterChestHitLeft2].Distance= MonsterChestHitLeft2Distance;
   MonsterAnimations[MonsterKnockDown2].Distance= MonsterKnockDown2Distance;
   MonsterAnimations[MonsterGetBackUp2].Distance= 0;
   MonsterAnimations[MonsterPickUpObjectFirst].Distance= MonsterPickUpObjectDistance;
   MonsterAnimations[MonsterPickUpObjectFreeze].Distance= MonsterPickUpObjectDistance;
   MonsterAnimations[MonsterPickUpObjectLast].Distance= MonsterPickUpObjectDistance;
   MonsterAnimations[MonsterThrowObject].Distance= MonsterThrowObjectDistance;
   MonsterAnimations[MonsterTaunt1].Distance=MonsterTaunt1Distance;
   MonsterAnimations[MonsterTaunt2].Distance=MonsterTaunt2Distance;
   MonsterAnimations[MonsterTravel].NumFrames=MonsterTravelNumFrames;
   MonsterAnimations[MonsterPause1].NumFrames = MonsterPause1NumFrames;
   MonsterAnimations[MonsterWalkForward].NumFrames = MonsterWalkForwardNumFrames;
   MonsterAnimations[MonsterWalkBack].NumFrames = MonsterWalkBackNumFrames;
   MonsterAnimations[MonsterJumpFirst].NumFrames = MonsterJumpFreezeFrame;
   MonsterAnimations[MonsterJumpFreeze].NumFrames = RLVal(1);
   MonsterAnimations[MonsterJumpLast].NumFrames = MonsterJumpStopFrame-MonsterJumpFreezeFrame;
   MonsterAnimations[MonsterJumpStop].NumFrames = MonsterJumpNumFrames-MonsterJumpStopFrame;

   MonsterAnimations[MonsterSkid].NumFrames = MonsterSkidNumFrames;

   MonsterAnimations[MonsterIntoIntoRun].NumFrames = MonsterIntoRunStartFrame;
   MonsterAnimations[MonsterIntoRun].NumFrames = MonsterIntoRunNumFrames-MonsterIntoRunStartFrame;
   MonsterAnimations[MonsterRun].NumFrames = MonsterRunNumFrames;
   MonsterAnimations[MonsterHighAttack1].NumFrames = MonsterHighAttack1NumFrames;
   MonsterAnimations[MonsterMediumAttack1].NumFrames = MonsterMediumAttack1NumFrames;
   MonsterAnimations[MonsterLowAttack1].NumFrames = MonsterLowAttack1NumFrames;

   MonsterAnimations[MonsterMediumAttack2].NumFrames = MonsterMediumAttack2NumFrames;
   MonsterAnimations[MonsterLowAttack2].NumFrames = MonsterLowAttack2NumFrames;

   MonsterAnimations[MonsterJumpAttack1].NumFrames = MonsterJumpAttack1NumFrames;
   MonsterAnimations[MonsterJumpAttack2].NumFrames = MonsterJumpAttack2NumFrames;
   MonsterAnimations[MonsterSpecialAttack1].NumFrames = MonsterSpecialAttack1NumFrames;
   MonsterAnimations[MonsterSpecialAttack2].NumFrames = MonsterSpecialAttack2NumFrames;

   MonsterAnimations[MonsterBlockMediumFirst].NumFrames = MonsterBlockMediumFreezeFrame;
   MonsterAnimations[MonsterBlockMediumFreeze].NumFrames = RLVal(1);
   MonsterAnimations[MonsterBlockMediumLast].NumFrames = MonsterBlockMediumNumFrames-MonsterBlockMediumFreezeFrame;
   MonsterAnimations[MonsterChestHitLeft2].NumFrames = MonsterChestHitLeft2StopFrame;
   MonsterAnimations[MonsterKnockDown2].NumFrames = MonsterKnockDown2StopFrame;
   MonsterAnimations[MonsterGetBackUp2].NumFrames = MonsterKnockDown2NumFrames-MonsterKnockDown2StopFrame;
   MonsterAnimations[MonsterPickUpObjectFirst].NumFrames = MonsterPickUpObjectFreezeFrame;
   MonsterAnimations[MonsterPickUpObjectFreeze].NumFrames = RLVal(1);
   MonsterAnimations[MonsterPickUpObjectLast].NumFrames = MonsterPickUpObjectNumFrames-MonsterPickUpObjectFreezeFrame;
   MonsterAnimations[MonsterThrowObject].NumFrames = MonsterThrowObjectNumFrames;
   MonsterAnimations[MonsterTaunt1].NumFrames = MonsterTaunt1NumFrames;
   MonsterAnimations[MonsterTaunt2].NumFrames = MonsterTaunt1NumFrames;

   MonsterAnimations[MonsterTravel].StopFrame=MonsterTravelLastFrame;
   MonsterAnimations[MonsterPause1].StopFrame= MonsterPause1NumFrames;
   MonsterAnimations[MonsterWalkForward].StopFrame= MonsterWalkForwardNumFrames;
   MonsterAnimations[MonsterWalkBack].StopFrame= MonsterWalkBackNumFrames;
   MonsterAnimations[MonsterJumpFirst].StopFrame= MonsterJumpFreezeFrame;
   MonsterAnimations[MonsterJumpFreeze].StopFrame= MonsterJumpFreezeFrame;
   MonsterAnimations[MonsterJumpLast].StopFrame= MonsterJumpStopFrame;
   MonsterAnimations[MonsterJumpStop].StopFrame= MonsterJumpNumFrames;

   MonsterAnimations[MonsterSkid].StopFrame= MonsterSkidNumFrames;

   MonsterAnimations[MonsterIntoIntoRun].StopFrame= MonsterIntoRunStartFrame;
   MonsterAnimations[MonsterIntoRun].StopFrame= MonsterIntoRunNumFrames;
   MonsterAnimations[MonsterRun].StopFrame= MonsterRunNumFrames;
   MonsterAnimations[MonsterHighAttack1].StopFrame= MonsterHighAttack1NumFrames;
   MonsterAnimations[MonsterMediumAttack1].StopFrame= MonsterMediumAttack1NumFrames;
   MonsterAnimations[MonsterLowAttack1].StopFrame= MonsterLowAttack1NumFrames;

   MonsterAnimations[MonsterMediumAttack2].StopFrame= MonsterMediumAttack2NumFrames;
   MonsterAnimations[MonsterLowAttack2].StopFrame= MonsterLowAttack2NumFrames;

   MonsterAnimations[MonsterJumpAttack1].StopFrame= MonsterJumpAttack1NumFrames;
   MonsterAnimations[MonsterJumpAttack2].StopFrame= MonsterJumpAttack2NumFrames;
   MonsterAnimations[MonsterSpecialAttack1].StopFrame= MonsterSpecialAttack1NumFrames;
   MonsterAnimations[MonsterSpecialAttack2].StopFrame= MonsterSpecialAttack2NumFrames;

   MonsterAnimations[MonsterBlockMediumFirst].StopFrame= MonsterBlockMediumFreezeFrame;
   MonsterAnimations[MonsterBlockMediumFreeze].StopFrame= MonsterBlockMediumFreezeFrame;
   MonsterAnimations[MonsterBlockMediumLast].StopFrame= MonsterBlockMediumNumFrames;
   MonsterAnimations[MonsterChestHitLeft2].StopFrame= MonsterChestHitLeft2StopFrame;
   MonsterAnimations[MonsterKnockDown2].StopFrame= MonsterKnockDown2StopFrame;
   MonsterAnimations[MonsterGetBackUp2].StopFrame= MonsterKnockDown2NumFrames;
   MonsterAnimations[MonsterPickUpObjectFirst].StopFrame= MonsterPickUpObjectFreezeFrame;
   MonsterAnimations[MonsterPickUpObjectFreeze].StopFrame= MonsterPickUpObjectFreezeFrame;
   MonsterAnimations[MonsterPickUpObjectLast].StopFrame= MonsterPickUpObjectNumFrames;
   MonsterAnimations[MonsterThrowObject].StopFrame= MonsterThrowObjectNumFrames;
   MonsterAnimations[MonsterTaunt1].StopFrame=MonsterTaunt1NumFrames;
   MonsterAnimations[MonsterTaunt2].StopFrame=MonsterTaunt1NumFrames;

   MonsterAnimations[MonsterPause1].EnergyDrain=MonsterPause1EnergyDrain;
   MonsterAnimations[MonsterWalkForward].EnergyDrain=MonsterWalkForwardEnergyDrain;
   MonsterAnimations[MonsterWalkBack].EnergyDrain=MonsterWalkBackEnergyDrain;
   MonsterAnimations[MonsterJumpFirst].EnergyDrain=MonsterJumpFirstEnergyDrain;
   MonsterAnimations[MonsterJumpFreeze].EnergyDrain=MonsterJumpFreezeEnergyDrain;
   MonsterAnimations[MonsterJumpLast].EnergyDrain=MonsterJumpLastEnergyDrain;
   MonsterAnimations[MonsterJumpStop].EnergyDrain=MonsterJumpStopEnergyDrain;
   MonsterAnimations[MonsterSkid].EnergyDrain=MonsterSkidEnergyDrain;
   MonsterAnimations[MonsterIntoIntoRun].EnergyDrain=MonsterIntoIntoRunEnergyDrain;
   MonsterAnimations[MonsterIntoRun].EnergyDrain=MonsterIntoRunEnergyDrain;
   MonsterAnimations[MonsterRun].EnergyDrain=MonsterRunEnergyDrain;
   MonsterAnimations[MonsterHighAttack1].EnergyDrain=MonsterHighAttack1EnergyDrain;
   MonsterAnimations[MonsterMediumAttack1].EnergyDrain=MonsterMediumAttack1EnergyDrain;
   MonsterAnimations[MonsterLowAttack1].EnergyDrain=MonsterLowAttack1EnergyDrain;
   MonsterAnimations[MonsterMediumAttack2].EnergyDrain=MonsterMediumAttack2EnergyDrain;
   MonsterAnimations[MonsterLowAttack2].EnergyDrain=MonsterLowAttack2EnergyDrain;
   MonsterAnimations[MonsterJumpAttack1].EnergyDrain=MonsterJumpAttack1EnergyDrain;
   MonsterAnimations[MonsterJumpAttack2].EnergyDrain=MonsterJumpAttack2EnergyDrain;
   MonsterAnimations[MonsterSpecialAttack1].EnergyDrain=MonsterSpecialAttack1EnergyDrain;
   MonsterAnimations[MonsterSpecialAttack2].EnergyDrain=MonsterSpecialAttack2EnergyDrain;
   MonsterAnimations[MonsterBlockMediumFirst].EnergyDrain=MonsterBlockMediumFirstEnergyDrain;
   MonsterAnimations[MonsterBlockMediumFreeze].EnergyDrain=MonsterBlockMediumFreezeEnergyDrain;
   MonsterAnimations[MonsterBlockMediumLast].EnergyDrain=MonsterBlockMediumLastEnergyDrain;
   MonsterAnimations[MonsterChestHitLeft2].EnergyDrain=MonsterChestHitLeft2EnergyDrain;
   MonsterAnimations[MonsterKnockDown2].EnergyDrain=MonsterKnockDown2EnergyDrain;
   MonsterAnimations[MonsterGetBackUp2].EnergyDrain=MonsterGetBackUp2EnergyDrain;
   MonsterAnimations[MonsterPickUpObjectFirst].EnergyDrain=MonsterPickUpObjectFirstEnergyDrain;
   MonsterAnimations[MonsterPickUpObjectFreeze].EnergyDrain=MonsterPickUpObjectFreezeEnergyDrain;
   MonsterAnimations[MonsterPickUpObjectLast].EnergyDrain=MonsterPickUpObjectLastEnergyDrain;
   MonsterAnimations[MonsterThrowObject].EnergyDrain=MonsterThrowObjectEnergyDrain;
   MonsterAnimations[MonsterTaunt1].EnergyDrain=MonsterTaunt1EnergyDrain;
   MonsterAnimations[MonsterTaunt2].EnergyDrain=MonsterTaunt2EnergyDrain;
   MonsterAnimations[MonsterTravel].EnergyDrain=MonsterTravelEnergyDrain;

   MonsterAnimations[MonsterPause1].EnergyMinimum=MonsterPause1EnergyMinimum;
   MonsterAnimations[MonsterWalkForward].EnergyMinimum=MonsterWalkForwardEnergyMinimum;
   MonsterAnimations[MonsterWalkBack].EnergyMinimum=MonsterWalkBackEnergyMinimum;
   MonsterAnimations[MonsterJumpFirst].EnergyMinimum=MonsterJumpFirstEnergyMinimum;
   MonsterAnimations[MonsterJumpFreeze].EnergyMinimum=MonsterJumpFreezeEnergyMinimum;
   MonsterAnimations[MonsterJumpLast].EnergyMinimum=MonsterJumpLastEnergyMinimum;
   MonsterAnimations[MonsterJumpStop].EnergyMinimum=MonsterJumpStopEnergyMinimum;
   MonsterAnimations[MonsterSkid].EnergyMinimum=MonsterSkidEnergyMinimum;
   MonsterAnimations[MonsterIntoIntoRun].EnergyMinimum=MonsterIntoIntoRunEnergyMinimum;
   MonsterAnimations[MonsterIntoRun].EnergyMinimum=MonsterIntoRunEnergyMinimum;
   MonsterAnimations[MonsterRun].EnergyMinimum=MonsterRunEnergyMinimum;
   MonsterAnimations[MonsterHighAttack1].EnergyMinimum=MonsterHighAttack1EnergyMinimum;
   MonsterAnimations[MonsterMediumAttack1].EnergyMinimum=MonsterMediumAttack1EnergyMinimum;
   MonsterAnimations[MonsterLowAttack1].EnergyMinimum=MonsterLowAttack1EnergyMinimum;
   MonsterAnimations[MonsterMediumAttack2].EnergyMinimum=MonsterMediumAttack2EnergyMinimum;
   MonsterAnimations[MonsterLowAttack2].EnergyMinimum=MonsterLowAttack2EnergyMinimum;
   MonsterAnimations[MonsterJumpAttack1].EnergyMinimum=MonsterJumpAttack1EnergyMinimum;
   MonsterAnimations[MonsterJumpAttack2].EnergyMinimum=MonsterJumpAttack2EnergyMinimum;
   MonsterAnimations[MonsterSpecialAttack1].EnergyMinimum=MonsterSpecialAttack1EnergyMinimum;
   MonsterAnimations[MonsterSpecialAttack2].EnergyMinimum=MonsterSpecialAttack2EnergyMinimum;
   MonsterAnimations[MonsterBlockMediumFirst].EnergyMinimum=MonsterBlockMediumFirstEnergyMinimum;
   MonsterAnimations[MonsterBlockMediumFreeze].EnergyMinimum=MonsterBlockMediumFreezeEnergyMinimum;
   MonsterAnimations[MonsterBlockMediumLast].EnergyMinimum=MonsterBlockMediumLastEnergyMinimum;
   MonsterAnimations[MonsterChestHitLeft2].EnergyMinimum=MonsterChestHitLeft2EnergyMinimum;
   MonsterAnimations[MonsterKnockDown2].EnergyMinimum=MonsterKnockDown2EnergyMinimum;
   MonsterAnimations[MonsterGetBackUp2].EnergyMinimum=MonsterGetBackUp2EnergyMinimum;
   MonsterAnimations[MonsterPickUpObjectFirst].EnergyMinimum=MonsterPickUpObjectFirstEnergyMinimum;
   MonsterAnimations[MonsterPickUpObjectFreeze].EnergyMinimum=MonsterPickUpObjectFreezeEnergyMinimum;
   MonsterAnimations[MonsterPickUpObjectLast].EnergyMinimum=MonsterPickUpObjectLastEnergyMinimum;
   MonsterAnimations[MonsterThrowObject].EnergyMinimum=MonsterThrowObjectEnergyMinimum;
   MonsterAnimations[MonsterTaunt1].EnergyMinimum=MonsterTaunt1EnergyMinimum;
   MonsterAnimations[MonsterTaunt2].EnergyMinimum=MonsterTaunt2EnergyMinimum;
   MonsterAnimations[MonsterTravel].EnergyMinimum=MonsterTravelEnergyMinimum;
   MonsterAnimationState=MonsterPause1;
   MonsterMovementState=MonsterWaiting;
   MnstLife=InitialMonsterLife;
   //monthink=2;

}

RLAnimationSet LoadAnim(char *filename);    //Sanfo's substitution
extern RLFrame animlocationframe;



int LoadMonsterAnimations()
{

   char anifile[100] = "anm.bin"; 
   //animlocationframe = monstframe;   //Sanfo add for animation file loading 7.31.96 

   // load packaged animations Sanfo 8.29.96 
   if (!LoadPackedAnimation(ConstructMonsterName(anifile), &TekMonsterData))
        return 0;
	GetMonstObjInfo ((unsigned long int *)TekMonsterData);
	MonsterScaleFrame = RLCreateFrame(monstframe);

	LoadModel((char *)ConstructLevelName("110.BIN"),MonsterScaleFrame);

   TekMonsterNumAnims = PreprocessPackedAnimation( monstframe, (unsigned long*)TekMonsterData );
   TekMonsterAnims = (PackedAnimations *)TekMonsterData;
   TekMonsterHierarchy = SabreHierarchy;


   if(!(MonsterAnimations[MonsterPause1].Anisette=LoadAnim((char *)MonsterPause1FileName)))return 0;
   if(!(MonsterAnimations[MonsterWalkForward].Anisette=LoadAnim(MonsterWalkForwardFileName)))return 0;
   if(!(MonsterAnimations[MonsterWalkBack].Anisette=LoadAnim(MonsterWalkBackFileName)))return 0;
   if(!(MonsterAnimations[MonsterJumpFirst].Anisette=LoadAnim(MonsterJumpFileName)))return 0;
   MonsterAnimations[MonsterJumpFreeze].Anisette=MonsterAnimations[MonsterJumpFirst].Anisette;
   MonsterAnimations[MonsterJumpLast].Anisette=MonsterAnimations[MonsterJumpFirst].Anisette;
   MonsterAnimations[MonsterJumpStop].Anisette=MonsterAnimations[MonsterJumpFirst].Anisette;
   if(!(MonsterAnimations[MonsterSkid].Anisette=LoadAnim(MonsterSkidFileName)))return 0;
   if(!(MonsterAnimations[MonsterIntoRun].Anisette=LoadAnim(MonsterIntoRunFileName)))return 0;
   MonsterAnimations[MonsterIntoIntoRun].Anisette=MonsterAnimations[MonsterIntoRun].Anisette;
   if(!(MonsterAnimations[MonsterRun].Anisette=LoadAnim(MonsterRunFileName)))return 0;
   if(!(MonsterAnimations[MonsterHighAttack1].Anisette=LoadAnim(MonsterHighAttack1FileName)))return 0;
//Don't use MonsterMediumAttack1
//   if(!(MonsterAnimations[MonsterMediumAttack1].Anisette=LoadAnim(MonsterMediumAttack1FileName)))return 0;
//Don't use MonsterLowAttack1
//   if(!(MonsterAnimations[MonsterLowAttack1].Anisette=LoadAnim(MonsterLowAttack1FileName)))return 0;
//Don't use MonsterMediumAttack2
//   if(!(MonsterAnimations[MonsterMediumAttack2].Anisette=LoadAnim(MonsterMediumAttack2FileName)))return 0;
//Don't use MonsterLowAttack2
//   if(!(MonsterAnimations[MonsterLowAttack2].Anisette=LoadAnim(MonsterLowAttack2FileName)))return 0;
//Don't use MonsterJumpAttack1
  // if(!(MonsterAnimations[MonsterJumpAttack1].Anisette=LoadAnim(MonsterJumpAttack1FileName)))return 0;
//Don't use MonsterJumpAttack2
   //if(!(MonsterAnimations[MonsterJumpAttack2].Anisette=LoadAnim(MonsterJumpAttack2FileName)))return 0;
//Don't use MonsterSpecialAttack1
   if(!(MonsterAnimations[MonsterSpecialAttack1].Anisette=LoadAnim(MonsterSpecialAttack1FileName)))return 0;
   if(!(MonsterAnimations[MonsterSpecialAttack2].Anisette=LoadAnim(MonsterSpecialAttack2FileName)))return 0;
   if(!(MonsterAnimations[MonsterBlockMediumFirst].Anisette=LoadAnim(MonsterBlockMediumFileName)))return 0;
   MonsterAnimations[MonsterBlockMediumFreeze].Anisette=MonsterAnimations[MonsterBlockMediumFirst].Anisette;
   MonsterAnimations[MonsterBlockMediumLast].Anisette=MonsterAnimations[MonsterBlockMediumFirst].Anisette;
   if(!(MonsterAnimations[MonsterChestHitLeft2].Anisette=LoadAnim(MonsterChestHitLeft2FileName)))return 0;
   if(!(MonsterAnimations[MonsterKnockDown2].Anisette=LoadAnim(MonsterKnockDown2FileName)))return 0;
   MonsterAnimations[MonsterDontGetBackUp2].Anisette=MonsterAnimations[MonsterKnockDown2].Anisette;
   MonsterAnimations[MonsterAllDead].Anisette=MonsterAnimations[MonsterKnockDown2].Anisette;
   MonsterAnimations[MonsterGetBackUp2].Anisette=MonsterAnimations[MonsterKnockDown2].Anisette;
   if(!(MonsterAnimations[MonsterPickUpObjectFirst].Anisette=LoadAnim(MonsterPickUpObjectFileName)))return 0;
   MonsterAnimations[MonsterPickUpObjectFreeze].Anisette=MonsterAnimations[MonsterPickUpObjectFirst].Anisette;
   MonsterAnimations[MonsterPickUpObjectLast].Anisette=MonsterAnimations[MonsterPickUpObjectFirst].Anisette;
   //if(!(MonsterAnimations[MonsterThrowObject].Anisette=LoadAnim(MonsterThrowObjectFileName)))return 0;
   if(!(MonsterAnimations[MonsterTaunt1].Anisette=LoadAnim(MonsterTaunt1FileName)))return 0;
   MonsterAnimations[MonsterTaunt2].Anisette=MonsterAnimations[MonsterTaunt1].Anisette;
   //if(!(MonsterAnimations[MonsterTaunt2].Anisette=LoadAnim(MonsterTaunt2FileName)))return 0;
   if(!(MonsterAnimations[MonsterTravel].Anisette=LoadAnim(MonsterTravelFileName)))return 0;


   return 1;
}    

int ClearMonsterAnimations()
{
/*
   if(RLObjectDestroy(MonsterAnimations[MonsterPause1].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(MonsterAnimations[MonsterWalkForward].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(MonsterAnimations[MonsterWalkBack].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(MonsterAnimations[MonsterJumpFirst].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(MonsterAnimations[MonsterSkid].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(MonsterAnimations[MonsterIntoIntoRun].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(MonsterAnimations[MonsterRun].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(MonsterAnimations[MonsterHighAttack1].Anisette)!=RLNoError)
      return 0;
//   if(RLObjectDestroy(MonsterAnimations[MonsterMediumAttack1].Anisette)!=RLNoError)
//      return 0;
//   if(RLObjectDestroy(MonsterAnimations[MonsterLowAttack1].Anisette)!=RLNoError)
//      return 0;
//   if(RLObjectDestroy(MonsterAnimations[MonsterMediumAttack2].Anisette)!=RLNoError)
//      return 0;
//   if(RLObjectDestroy(MonsterAnimations[MonsterLowAttack2].Anisette)!=RLNoError)
//      return 0;
//   if(RLObjectDestroy(MonsterAnimations[MonsterJumpAttack1].Anisette)!=RLNoError)
//      return 0;
//   if(RLObjectDestroy(MonsterAnimations[MonsterJumpAttack2].Anisette)!=RLNoError)
//      return 0;
   if(RLObjectDestroy(MonsterAnimations[MonsterSpecialAttack1].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(MonsterAnimations[MonsterSpecialAttack2].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(MonsterAnimations[MonsterBlockMediumFirst].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(MonsterAnimations[MonsterChestHitLeft2].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(MonsterAnimations[MonsterKnockDown2].Anisette)!=RLNoError)
      return 0;
//      return 0;
   if(RLObjectDestroy(MonsterAnimations[MonsterPickUpObjectFirst].Anisette)!=RLNoError)
      return 0;
//   if(RLObjectDestroy(MonsterAnimations[MonsterThrowObject].Anisette)!=RLNoError)
//      return 0;
   if(RLObjectDestroy(MonsterAnimations[MonsterTaunt1].Anisette)!=RLNoError)
      return 0;
//   if(RLObjectDestroy(MonsterAnimations[MonsterTaunt2].Anisette)!=RLNoError)
//      return 0;
   if(RLObjectDestroy(MonsterAnimations[MonsterTravel].Anisette)!=RLNoError)
      return 0;
*/

   //Sanfo 8.30.96
   free(TekMonsterHierarchy->ObjectCoordinates);
   TekMonsterHierarchy->ObjectCoordinates = NULL;
   free(TekMonsterHierarchy);
   TekMonsterHierarchy = NULL;
   free(TekMonsterData);   
   TekMonsterData = NULL;

   return 1;
}

//This function will load up Motions with the proper states.
int InitMonsterAnimationEngine()
{

   if(RLMalloc((void **)&(MonsterAnimations[MonsterPause1].ChangeList),10*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterPause1].numchanges=10;
   MonsterAnimations[MonsterPause1].ChangeList[0]=ToMonsterTaunt1;
   MonsterAnimations[MonsterPause1].ChangeList[1]=ToMonsterTaunt2;
   MonsterAnimations[MonsterPause1].ChangeList[2]=ToMonsterWalkBack;
   MonsterAnimations[MonsterPause1].ChangeList[3]=ToMonsterJumpFirst;
   MonsterAnimations[MonsterPause1].ChangeList[4]=ToMonsterIntoIntoRun;
   MonsterAnimations[MonsterPause1].ChangeList[5]=ToMonsterHighAttack1;
   MonsterAnimations[MonsterPause1].ChangeList[6]=ToMonsterSpecialAttack1;
   MonsterAnimations[MonsterPause1].ChangeList[7]=ToMonsterSpecialAttack2;
   MonsterAnimations[MonsterPause1].ChangeList[8]=ToMonsterBlockMediumFirst;
   MonsterAnimations[MonsterPause1].ChangeList[9]=ToMonsterPickUpObjectFirst;

   if(RLMalloc((void **)&(MonsterAnimations[MonsterWalkForward].ChangeList),5*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterWalkForward].numchanges=5;
   MonsterAnimations[MonsterWalkForward].ChangeList[0]=ToMonsterPause1;
   MonsterAnimations[MonsterWalkForward].ChangeList[1]=ToMonsterJumpFirst;
   MonsterAnimations[MonsterWalkForward].ChangeList[2]=ToMonsterSkid;
   MonsterAnimations[MonsterWalkForward].ChangeList[3]=ToMonsterIntoRun;
   MonsterAnimations[MonsterWalkForward].ChangeList[4]=ToMonsterRun;

   if(RLMalloc((void **)&(MonsterAnimations[MonsterWalkBack].ChangeList),1*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterWalkBack].numchanges=1;
   MonsterAnimations[MonsterWalkBack].ChangeList[0]=ToMonsterPause1;
   if(RLMalloc((void **)&(MonsterAnimations[MonsterJumpFirst].ChangeList),6*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterJumpFirst].numchanges=6;
   MonsterAnimations[MonsterJumpFirst].ChangeList[0]=ToMonsterJumpFreeze;
   MonsterAnimations[MonsterJumpFirst].ChangeList[1]=ToMonsterJumpLast;
   MonsterAnimations[MonsterJumpFirst].ChangeList[2]=ToMonsterWalkForward;
   MonsterAnimations[MonsterJumpFirst].ChangeList[3]=ToMonsterRun;
   MonsterAnimations[MonsterJumpFirst].ChangeList[4]=ToMonsterTravel;
   MonsterAnimations[MonsterJumpFirst].ChangeList[5]=ToMonsterSpecialAttack1;

   if(RLMalloc((void **)&(MonsterAnimations[MonsterJumpFreeze].ChangeList),4*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterJumpFreeze].numchanges=4;
   MonsterAnimations[MonsterJumpFreeze].ChangeList[0]=ToMonsterJumpLast;
   MonsterAnimations[MonsterJumpFreeze].ChangeList[1]=ToMonsterWalkForward;
   MonsterAnimations[MonsterJumpFreeze].ChangeList[2]=ToMonsterRun;   
   MonsterAnimations[MonsterJumpFreeze].ChangeList[3]=ToMonsterTravel;   

   if(RLMalloc((void **)&(MonsterAnimations[MonsterJumpLast].ChangeList),4*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterJumpLast].numchanges=4;
   MonsterAnimations[MonsterJumpLast].ChangeList[0]=ToMonsterJumpStop;
   MonsterAnimations[MonsterJumpLast].ChangeList[1]=ToMonsterWalkForward;
   MonsterAnimations[MonsterJumpLast].ChangeList[2]=ToMonsterRun;   
   MonsterAnimations[MonsterJumpLast].ChangeList[3]=ToMonsterTravel;   
   
   if(RLMalloc((void **)&(MonsterAnimations[MonsterJumpStop].ChangeList),6*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterJumpStop].numchanges=6;
   MonsterAnimations[MonsterJumpStop].ChangeList[0]=ToMonsterPause1;
   MonsterAnimations[MonsterJumpStop].ChangeList[1]=ToMonsterWalkForward;
   MonsterAnimations[MonsterJumpStop].ChangeList[2]=ToMonsterSkid;
   MonsterAnimations[MonsterJumpStop].ChangeList[3]=ToMonsterIntoRun;
   MonsterAnimations[MonsterJumpStop].ChangeList[4]=ToMonsterRun;
   MonsterAnimations[MonsterJumpStop].ChangeList[5]=ToMonsterTravel;

   if(RLMalloc((void **)&(MonsterAnimations[MonsterSkid].ChangeList),5*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterSkid].numchanges=5;
   MonsterAnimations[MonsterSkid].ChangeList[0]=ToMonsterPause1;
   MonsterAnimations[MonsterSkid].ChangeList[1]=ToMonsterWalkForward;
   MonsterAnimations[MonsterSkid].ChangeList[2]=ToMonsterJumpFirst;
   MonsterAnimations[MonsterSkid].ChangeList[3]=ToMonsterIntoRun;
   MonsterAnimations[MonsterSkid].ChangeList[4]=ToMonsterRun;
   
   if(RLMalloc((void **)&(MonsterAnimations[MonsterIntoIntoRun].ChangeList),3*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterIntoIntoRun].numchanges=3;
   MonsterAnimations[MonsterIntoIntoRun].ChangeList[0]=ToMonsterPause1;
   MonsterAnimations[MonsterIntoIntoRun].ChangeList[1]=ToMonsterJumpFirst;
   MonsterAnimations[MonsterIntoIntoRun].ChangeList[2]=ToMonsterIntoRun;
   
   if(RLMalloc((void **)&(MonsterAnimations[MonsterIntoRun].ChangeList),4*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterIntoRun].numchanges=4;
   MonsterAnimations[MonsterIntoRun].ChangeList[0]=ToMonsterPause1;
   MonsterAnimations[MonsterIntoRun].ChangeList[1]=ToMonsterWalkForward;
   MonsterAnimations[MonsterIntoRun].ChangeList[2]=ToMonsterJumpFirst;
   MonsterAnimations[MonsterIntoRun].ChangeList[3]=ToMonsterSkid;
   
   if(RLMalloc((void **)&(MonsterAnimations[MonsterRun].ChangeList),6*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterRun].numchanges=6;
   MonsterAnimations[MonsterRun].ChangeList[0]=ToMonsterWalkForward;
   MonsterAnimations[MonsterRun].ChangeList[1]=ToMonsterJumpFirst;
   MonsterAnimations[MonsterRun].ChangeList[2]=ToMonsterSkid;
   MonsterAnimations[MonsterRun].ChangeList[3]=ToMonsterPause1;
   MonsterAnimations[MonsterRun].ChangeList[4]=ToMonsterTravel;
   MonsterAnimations[MonsterRun].ChangeList[5]=ToMonsterTaunt2;

   if(RLMalloc((void **)&(MonsterAnimations[MonsterHighAttack1].ChangeList),2*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterHighAttack1].numchanges=2;
   MonsterAnimations[MonsterHighAttack1].ChangeList[0]=ToMonsterPause1;
   MonsterAnimations[MonsterHighAttack1].ChangeList[1]=ToMonsterSpecialAttack1;

//   if(RLMalloc((void **)&(MonsterAnimations[MonsterMediumAttack1].ChangeList),2*sizeof(StateChange))!=RLNoError)
//      return 0;
//   MonsterAnimations[MonsterMediumAttack1].numchanges=2;
//   MonsterAnimations[MonsterMediumAttack1].ChangeList[0]=ToMonsterPause1;
//   MonsterAnimations[MonsterMediumAttack1].ChangeList[1]=ToMonsterSpecialAttack1;

//   if(RLMalloc((void **)&(MonsterAnimations[MonsterLowAttack1].ChangeList),2*sizeof(StateChange))!=RLNoError)
//      return 0;
//   MonsterAnimations[MonsterLowAttack1].numchanges=2;
//   MonsterAnimations[MonsterLowAttack1].ChangeList[0]=ToMonsterPause1;
//   MonsterAnimations[MonsterLowAttack1].ChangeList[1]=ToMonsterSpecialAttack1;

//   if(RLMalloc((void **)&(MonsterAnimations[MonsterMediumAttack2].ChangeList),2*sizeof(StateChange))!=RLNoError)
//      return 0;
//   MonsterAnimations[MonsterMediumAttack2].numchanges=2;
//   MonsterAnimations[MonsterMediumAttack2].ChangeList[0]=ToMonsterPause1;
//   MonsterAnimations[MonsterMediumAttack2].ChangeList[1]=ToMonsterSpecialAttack1;

//   if(RLMalloc((void **)&(MonsterAnimations[MonsterLowAttack2].ChangeList),2*sizeof(StateChange))!=RLNoError)
//      return 0;
//   MonsterAnimations[MonsterLowAttack2].numchanges=2;
//   MonsterAnimations[MonsterLowAttack2].ChangeList[0]=ToMonsterPause1;
//   MonsterAnimations[MonsterLowAttack2].ChangeList[1]=ToMonsterSpecialAttack1;

   if(RLMalloc((void **)&(MonsterAnimations[MonsterBlockMediumFirst].ChangeList),2*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterBlockMediumFirst].numchanges=2;
   MonsterAnimations[MonsterBlockMediumFirst].ChangeList[0]=ToMonsterBlockMediumFreeze;
   MonsterAnimations[MonsterBlockMediumFirst].ChangeList[1]=ToMonsterBlockMediumLast;

   if(RLMalloc((void **)&(MonsterAnimations[MonsterBlockMediumLast].ChangeList),2*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterBlockMediumLast].numchanges=2;
   MonsterAnimations[MonsterBlockMediumLast].ChangeList[0]=ToMonsterPause1;
   MonsterAnimations[MonsterBlockMediumLast].ChangeList[1]=ToMonsterBlockMediumFirst;

   if(RLMalloc((void **)&(MonsterAnimations[MonsterBlockMediumFreeze].ChangeList),1*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterBlockMediumFreeze].numchanges=1;
   MonsterAnimations[MonsterBlockMediumFreeze].ChangeList[0]=ToMonsterBlockMediumLast;

   if(RLMalloc((void **)&(MonsterAnimations[MonsterPickUpObjectLast].ChangeList),2*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterPickUpObjectLast].numchanges=2;
   MonsterAnimations[MonsterPickUpObjectLast].ChangeList[0]=ToMonsterPause1;
   MonsterAnimations[MonsterPickUpObjectLast].ChangeList[1]=ToMonsterPickUpObjectFirst;
   
   if(RLMalloc((void **)&(MonsterAnimations[MonsterPickUpObjectFirst].ChangeList),3*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterPickUpObjectFirst].numchanges=3;
   MonsterAnimations[MonsterPickUpObjectFirst].ChangeList[0]=ToMonsterPickUpObjectLast;
   MonsterAnimations[MonsterPickUpObjectFirst].ChangeList[1]=ToMonsterPickUpObjectFreeze;
   MonsterAnimations[MonsterPickUpObjectFirst].ChangeList[2]=ToMonsterSpecialAttack1;

   if(RLMalloc((void **)&(MonsterAnimations[MonsterPickUpObjectFreeze].ChangeList),1*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterPickUpObjectFreeze].numchanges=1;
   MonsterAnimations[MonsterPickUpObjectFreeze].ChangeList[0]=ToMonsterPickUpObjectLast;

   if(RLMalloc((void **)&(MonsterAnimations[MonsterChestHitLeft2].ChangeList),sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterChestHitLeft2].numchanges=1;
      MonsterAnimations[MonsterChestHitLeft2].ChangeList[0]=ToMonsterPause1;

   if(RLMalloc((void **)&(MonsterAnimations[MonsterKnockDown2].ChangeList),3*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterKnockDown2].numchanges=3;
   MonsterAnimations[MonsterKnockDown2].ChangeList[0]=ToMonsterDontGetBackUp2;
   MonsterAnimations[MonsterKnockDown2].ChangeList[1]=ToMonsterAllDead;
   MonsterAnimations[MonsterKnockDown2].ChangeList[2]=ToMonsterGetBackUp2;

   if(RLMalloc((void **)&(MonsterAnimations[MonsterGetBackUp2].ChangeList),1*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterGetBackUp2].numchanges=1;
   MonsterAnimations[MonsterGetBackUp2].ChangeList[0]=ToMonsterPause1;

   MonsterAnimations[MonsterDontGetBackUp2].numchanges=0;
   MonsterAnimations[MonsterDontGetBackUp2].ChangeList=0;

   MonsterAnimations[MonsterAllDead].numchanges=0;
   MonsterAnimations[MonsterAllDead].ChangeList=0;

   MonsterAnimations[MonsterTaunt1].numchanges=0;
   MonsterAnimations[MonsterTaunt1].ChangeList=0;

   if(RLMalloc((void **)&(MonsterAnimations[MonsterTaunt2].ChangeList),1*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterTaunt2].numchanges=1;
   MonsterAnimations[MonsterTaunt2].ChangeList[0]=ToMonsterPause1;

   if(RLMalloc((void **)&(MonsterAnimations[MonsterSpecialAttack1].ChangeList),1*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterSpecialAttack1].numchanges=1;
   MonsterAnimations[MonsterSpecialAttack1].ChangeList[0]=ToMonsterPause1;

   if(RLMalloc((void **)&(MonsterAnimations[MonsterSpecialAttack2].ChangeList),1*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterSpecialAttack2].numchanges=1;
   MonsterAnimations[MonsterSpecialAttack2].ChangeList[0]=ToMonsterPause1;

   if(RLMalloc((void **)&(MonsterAnimations[MonsterTravel].ChangeList),4*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterAnimations[MonsterTravel].numchanges=4;
   MonsterAnimations[MonsterTravel].ChangeList[0]=ToMonsterJumpFirst;
   MonsterAnimations[MonsterTravel].ChangeList[1]=ToMonsterSkid;
   MonsterAnimations[MonsterTravel].ChangeList[2]=ToMonsterPause1;
   MonsterAnimations[MonsterTravel].ChangeList[3]=ToMonsterRun;





   MonsterAnimations[MonsterPause1].WhatToDo=MonsterPause1Function;
   MonsterAnimations[MonsterWalkForward].WhatToDo=MonsterWalkForwardFunction;
   MonsterAnimations[MonsterWalkBack].WhatToDo=MonsterWalkBackFunction;
   MonsterAnimations[MonsterJumpFirst].WhatToDo=MonsterJumpFirstFunction;
   MonsterAnimations[MonsterJumpFreeze].WhatToDo=MonsterJumpFreezeFunction;
   MonsterAnimations[MonsterJumpLast].WhatToDo=MonsterJumpLastFunction;
   MonsterAnimations[MonsterJumpStop].WhatToDo=MonsterJumpStopFunction;
   MonsterAnimations[MonsterSkid].WhatToDo=MonsterSkidFunction;
   MonsterAnimations[MonsterIntoIntoRun].WhatToDo=MonsterIntoIntoRunFunction;
   MonsterAnimations[MonsterIntoRun].WhatToDo=MonsterIntoRunFunction;
   MonsterAnimations[MonsterRun].WhatToDo=MonsterRunFunction;
   MonsterAnimations[MonsterHighAttack1].WhatToDo=MonsterHighAttack1Function;
//   MonsterAnimations[MonsterMediumAttack1].WhatToDo=MonsterMediumAttack1Function;
//   MonsterAnimations[MonsterLowAttack1].WhatToDo=MonsterLowAttack1Function;
//   MonsterAnimations[MonsterMediumAttack2].WhatToDo=MonsterMediumAttack2Function;
//   MonsterAnimations[MonsterLowAttack2].WhatToDo=MonsterLowAttack2Function;
//   MonsterAnimations[MonsterJumpAttack1].WhatToDo=MonsterJumpAttack1Function;
//   MonsterAnimations[MonsterJumpAttack2].WhatToDo=MonsterJumpAttack2Function;
   MonsterAnimations[MonsterSpecialAttack1].WhatToDo=MonsterSpecialAttack1Function;
   MonsterAnimations[MonsterSpecialAttack2].WhatToDo=MonsterSpecialAttack2Function;
   MonsterAnimations[MonsterBlockMediumFirst].WhatToDo=MonsterBlockMediumFirstFunction;
   MonsterAnimations[MonsterBlockMediumFreeze].WhatToDo=MonsterBlockMediumFreezeFunction;
   MonsterAnimations[MonsterBlockMediumLast].WhatToDo=MonsterBlockMediumLastFunction;
   MonsterAnimations[MonsterChestHitLeft2].WhatToDo=MonsterChestHitLeft2Function;
   MonsterAnimations[MonsterKnockDown2].WhatToDo=MonsterKnockDown2Function;
   MonsterAnimations[MonsterGetBackUp2].WhatToDo=MonsterGetBackUp2Function;
   MonsterAnimations[MonsterDontGetBackUp2].WhatToDo=MonsterDontGetBackUp2Function;
   MonsterAnimations[MonsterAllDead].WhatToDo=MonsterAllDeadFunction;
   MonsterAnimations[MonsterPickUpObjectFirst].WhatToDo=MonsterPickUpObjectFirstFunction;
   MonsterAnimations[MonsterPickUpObjectFreeze].WhatToDo=MonsterPickUpObjectFreezeFunction;
   MonsterAnimations[MonsterPickUpObjectLast].WhatToDo=MonsterPickUpObjectLastFunction;
//   MonsterAnimations[MonsterThrowObject].WhatToDo=MonsterThrowObjectFunction;
   MonsterAnimations[MonsterTaunt1].WhatToDo=MonsterTaunt1Function;
   MonsterAnimations[MonsterTaunt2].WhatToDo=MonsterTaunt2Function;
   MonsterAnimations[MonsterTravel].WhatToDo=MonsterTravelFunction;

   return 1;

}

void DestroyMonsterAnimationEngine()
{
   int i;
   for(i=MonsterPause1;i<=MonsterTaunt2;++i)
   {
      if(MonsterAnimations[i].numchanges)
         RLFree(MonsterAnimations[i].ChangeList);
   }
}

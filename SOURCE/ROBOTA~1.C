/**********************************************************************
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
File:           Robotani2.c
Author:         Bruce Abe
Date:           9-26-95
Version:        1.0001



************************************************************************
REVISION HISTORY        (Add Edits and History to top of list).

Edited By:      Bruce Abe
Edited Date:    12-20-95
Changes:
                Put in code to allow the Robot to walk on top of buildings.

Edited By:      Bruce Abe
Edited Date:    11-1-95
Changes:
                Added some typecasting to get rid of bounteous warnings.

Edited By:      Jeremiah Spudde Childs
Edited Date:    10/27/95
Changes:
                Altered code in ToRobotBlockMediumFreeze() and 
                RobotBlockMediumFreezeFunction()	to change orientation of
				the Robot defensive sphere and flip its texture coordinates
				with FlipTextureCoords().

Edited By:      Bruce Abe
Edited Date:    10-6-95
Changes:
                Added code to turn on and off the defense sphere
                when you go into and out of the RobotBlockMediumFreeze
                state.  It also sets the position, rotation, and
                makes the sphere wireframe.

Edited By:      Bruce Abe
Edited Date:    10-3-95
Changes:
                edited the Robot staydown deaths to make sure the 
                animation is at the optimal frame, and also put in a
                kludge to set StealthRobot's position below ground 
                in the case of the death, so that she actually rests on
                the ground.  (She was hovering.)
                made it possible to go into a high1 or medium1 attack
                while still skidding to a stop.  I will also put this in
                for the other attacks when I get the other attacks to do
                something interesting.


Edited By:      Bo Yuan
Edited Date:    9-28-95
Changes:
                added three system header files.

Edited By:      Bruce Abe
Edited Date:    9-28-95
Changes:
                changed VERSION_NUMBER from 1.0 to 1.0001.
				turned on the Robot travel sound effects.
            put in the Robot falldown and staydown deaths.


***********************************************************************/
#pragma warning( disable : 4244)

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stdio.h>
#include "imisc.h"
#include "clutter.h"

#include "wrapper.h"
#include "global.h"
#define BruceNotSpudde
//#define BruceSndSystem
typedef enum
{
   UnknownStyle,
   SabreStyle,
   KataStyle,
   StealthStyle,
   KaberStyle,
   MerStyle
}RobotStyle;

//extern RobotStyle WhichKindOfRobot;


#ifndef __psx__
#define XAFnotXBF
#endif
#define Binary

//replace rl with rl2d3d.h. By Sanfo 5/18/96
//#include "rl.h"
#include "rl2d3d.h"

#include "ybsnd.h"
#include "keycom.h"
#include "boink.h"
#include "Robotmove.h"
#include "timing.h"
#include "config.h"
#include "gosys.h"
#include "spritlib.h"
#include "plasma.h"
#include "monanim.h"
#include "psystem.h"
#include "Robotanim.h"

#include "BinLoad.h"
#include "ichars.h"
#include "tekanim.h"

#ifndef BruceNotSpudde
//#include "psxsound.h"
#endif
char RobotName[3]="SA";

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

//#include "boink.h"
extern struct _moving_object_data_ RobotData;

extern RLFrame Robotspew;
//extern RLFrame monstspew;
extern PlasmaData Robotspewdata;
//extern PlasmaData monstspewdata;
//extern Psystem *Robotplasma;
extern Psystem *SixShooter;
extern Psystem *PeaShooter;
extern Psystem *Cussin;
extern RLFrame MonsterScaleFrame;

volatile long int InputInt;
volatile long int InputInt2;
volatile long int InputIntDevNull;
extern void HomingMotionFunction(MovingObjectData movedata);
extern void PlasmaGotHit(MovingObjectData movedata);
static int StageNumber = 0;
extern int ConcussionDamage;
extern RLValue ConcussionRadius;
//extern RLValue RobotCosine(RLValue DiffFrame);
//extern RLValue RobotSine(RLValue DiffFrame);
extern RLValue RobotTheta;
extern RLValue RobotTurnMaximum;
extern RLValue RobotTurnAcceleration;

extern int Vmode;
//extern int RobotMotionDamage;
RLValue RobotConcussionDuration=12;
RLValue RobotConcussionMaxRadius = 8;
RLValue RobotConcussionMinRadius = 1;
RLValue RobotConcussionSpeed = 0.2;
//extern int submonster;

int NumRobotTaunts=0;
RLValue RobotZappaHowLong[6];
int RobotZappaOnScreen;
RLVector Robotspewvelocity;
RLValue HomerHowLong;
BOOL HomerOnScreen=0;
RLFrame RobotBlockSphere;
extern struct _moving_object_data_ RobotHomerData;
extern RLFrame behindthescene;
extern RLFrame Robotframe;
//extern Sprite* SixShooter[6];
#ifndef BruceNotSpudde

#endif
RLValue DiffFrame=RLVal(3.0);
#define MaxRobotEngy 65536
#define MaxMnstEngy 65536
#define MaxRobotLife 100
int RobotEngy=MaxRobotEngy;
extern int MnstEngy;
extern int RobotLife;
extern int MnstLife;
RLValue RobotArmor=RLVal(1.0);
int RobotSlideNextAnimation;
//int RobotAttackFerocity;
int BlockCountDown;
RLValue RapidFireHowLong[NumberOfSixShooters];
RLValue PeaShooterHowLong[NumberOfPeaShooters];
RLValue CussinHowLong[NumberOfSixShooters];
RLVector CussinWhichWay;
RLVector CussinUp;
extern struct _moving_object_data_ RobotRapidFireData[NumberOfSixShooters];
extern struct _moving_object_data_ RobotPeaShooterData[NumberOfPeaShooters];
extern struct _moving_object_data_ RobotCussinData[NumberOfSixShooters];
extern struct _moving_object_data_ RobotZappaData;

int RFCountDown=0;

RLValue RFSpeed=0.2;
static RLValue HomingMissileSpeed = -1.0;
RLValue HomerAngle=0.1396;
RLValue HomerCloseEnough=0.1;
static int MediumAttack1Ferocity = 7;
static RLValue RobotWalkForwardDistance =RLVal(2.2888);
static RLValue RobotIntoRunDistance= RLVal(0.419617);

static RLValue RobotRunDistance= RLVal(3.34);

static RLValue RobotWalkBackDistance =RLVal(2.36);
static RLValue RobotSideStepLeftDistance= RLVal(1.99);
static RLValue RobotSideStepRightDistance= RLVal(1.99);
static RLValue RobotAcrobatic1Distance =RLVal(4.79);
static RLValue RobotAcrobatic2Distance =RLVal(5);
static RLValue RobotSkidDistance =RLVal(4);
static RLValue RobotTravelBackDistance =RLVal(4.272461);
static RLValue RobotTravelLeftDistance= RLVal(3.356934);
static RLValue RobotTravelRightDistance= RLVal(3.356934);
static RLValue RobotKnockDown1Distance =RLVal(3);
static RLValue RobotKnockDown2Distance =RLVal(3);
static RLValue RobotKnockDown3Distance =RLVal(3);
                                                       
int PeaShooterEnergyDrain;
int PeaShooterEnergyMinimum = 200;
static int RobotPause1EnergyDrain=            -64 ;
static int RobotWalkForwardEnergyDrain=       0  ;
static int RobotWalkBackEnergyDrain=          0 ;
static int RobotSideStepLeftEnergyDrain=      0;
static int RobotSideStepRightEnergyDrain=     0                    ;
static int RobotJumpFirstEnergyDrain=         0                   ;
static int RobotJumpFreezeEnergyDrain=        0                  ;
static int RobotJumpLastEnergyDrain=          0                 ;
static int RobotJumpStopEnergyDrain=          0                ;
static int RobotAcrobatic1EnergyDrain=        0               ;
static int RobotAcrobatic1EndEnergyDrain=     0              ;
static int RobotAcrobatic2EnergyDrain=        0             ;
static int RobotAcrobatic2EndEnergyDrain=     0            ;
static int RobotSkidEnergyDrain=              0           ;
static int RobotTravelForwardEnergyDrain=     0          ;
static int RobotTravelBackEnergyDrain=        0         ;
static int RobotTravelLeftEnergyDrain=        0        ;
static int RobotTravelRightEnergyDrain=       0       ;
static int RobotIntoIntoRunEnergyDrain=       0      ;
static int RobotIntoRunEnergyDrain=           0     ;
static int RobotRunEnergyDrain=               0    ;
static int RobotHighAttack1EnergyDrain=       300 ;
static int RobotMediumAttack1EnergyDrain=     200;
static int RobotLowAttack1FirstEnergyDrain=   30;
static int RobotLowAttack1TargetEnergyDrain=  100                   ;
static int RobotLowAttack1LastEnergyDrain=    0                    ;
static int RobotSuperJab1EnergyDrain=         80                  ;
static int RobotHighAttack2EnergyDrain=       300                ;
static int RobotMediumAttack2EnergyDrain=     200               ;
static int RobotLowAttack2EnergyDrain=        60               ;
static int RobotSuperKick2EnergyDrain=        80              ;
static int RobotJumpAttack1EnergyDrain=       90             ;
static int RobotJumpAttack2EnergyDrain=       90            ;
static int RobotSpecialAttack1EnergyDrain=    400          ;
static int RobotSpecialAttack2EnergyDrain=    400         ;
static int RobotSpecialAttack3EnergyDrain=    400        ;
static int RobotBlockMediumFirstEnergyDrain=  0         ;
static int RobotBlockMediumFreezeEnergyDrain= 0        ;
static int RobotBlockMediumLastEnergyDrain=   0       ;
static int RobotChestHitLeft2EnergyDrain=     0      ;
static int RobotPickUpObjectFirstEnergyDrain= 0     ;
static int RobotPickUpObjectFreezeEnergyDrain= 0   ;
static int RobotPickUpObjectLastEnergyDrain=  0   ;
static int RobotThrowObjectEnergyDrain=       200;
static int RobotTaunt1EnergyDrain=            0;
static int RobotTaunt2EnergyDrain=            0;

static int RobotPause1EnergyMinimum=            -64;
static int RobotWalkForwardEnergyMinimum=       0                   ;
static int RobotWalkBackEnergyMinimum=          0                  ;
static int RobotSideStepLeftEnergyMinimum=      0                 ;
static int RobotSideStepRightEnergyMinimum=     0                ;
static int RobotJumpFirstEnergyMinimum=         0               ;
static int RobotJumpFreezeEnergyMinimum=        0              ;
static int RobotJumpLastEnergyMinimum=          0             ;
static int RobotJumpStopEnergyMinimum=          0            ;
static int RobotAcrobatic1EnergyMinimum=        0           ;
static int RobotAcrobatic1EndEnergyMinimum=     0          ;
static int RobotAcrobatic2EnergyMinimum=        0         ;
static int RobotAcrobatic2EndEnergyMinimum=     0        ;
static int RobotSkidEnergyMinimum=              0       ;
static int RobotTravelForwardEnergyMinimum=     0      ;
static int RobotTravelBackEnergyMinimum=        0     ;
static int RobotTravelLeftEnergyMinimum=        0    ;
static int RobotTravelRightEnergyMinimum=       0   ;
static int RobotIntoIntoRunEnergyMinimum=       0  ;
static int RobotIntoRunEnergyMinimum=           0 ;
static int RobotRunEnergyMinimum=               0;
static int RobotHighAttack1EnergyMinimum=       6000                      ;
static int RobotMediumAttack1EnergyMinimum=     4000                     ;
static int RobotLowAttack1FirstEnergyMinimum=   1200                    ;
static int RobotLowAttack1TargetEnergyMinimum=  400                    ;
static int RobotLowAttack1LastEnergyMinimum=    0                     ;
static int RobotSuperJab1EnergyMinimum=         1600                 ;
static int RobotHighAttack2EnergyMinimum=       6000                ;
static int RobotMediumAttack2EnergyMinimum=     4000               ;
static int RobotLowAttack2EnergyMinimum=        1200              ;
static int RobotSuperKick2EnergyMinimum=        1600             ;
static int RobotJumpAttack1EnergyMinimum=       1800            ;
static int RobotJumpAttack2EnergyMinimum=       1800           ;
static int RobotSpecialAttack1EnergyMinimum=    8000          ;
static int RobotSpecialAttack2EnergyMinimum=    8000         ;
static int RobotSpecialAttack3EnergyMinimum=    8000        ;
static int RobotBlockMediumFirstEnergyMinimum=  0          ;
static int RobotBlockMediumFreezeEnergyMinimum= 0         ;
static int RobotBlockMediumLastEnergyMinimum=   0        ;
static int RobotChestHitLeft2EnergyMinimum=     0       ;
static int RobotPickUpObjectFirstEnergyMinimum= 0      ;
static int RobotPickUpObjectFreezeEnergyMinimum= 0    ;
static int RobotPickUpObjectLastEnergyMinimum=  0    ;
static int RobotThrowObjectEnergyMinimum=       4000;
static int RobotTaunt1EnergyMinimum=            0;
static int RobotTaunt2EnergyMinimum=            0;
RLValue RobotBlockSphereHeight=RLVal(1.2);
static RLValue RobotBlockSphereRotation = RLVal(0.5);
static int PowerUpEnergy = MaxRobotEngy;
static int HomerDuration = 10;
static int HomerDamage = 50;
static int RapidFireInterval = 0;
static int RapidFireDuration = 15;
static int RapidFireDamage = 10;
//static int PeaShooterDamage=0;
static int RobotNumTaunts = 2;
static int RobotEnergyToLifeConversion = 1000;
static int InitialMonsterLife = 100;
static int InitialRobotLife = 100;
static RLValue RobotTerminalVelocity = RLVal(-0.885010);



//#define RobotIntoRunDistance RLVal(0.83)

extern FrameSetQuality(RLFrame parent,RLRenderQuality quals);
extern FrameSetColour(RLFrame parent,RLValue r, RLValue g, RLValue b);
char *ConstructRobotName(RobotID RobotNumber, char *name);

/* change 3d model object file extension
 * added by Sanfo 7/3/1996
 */
#define XAF(name)   name##".xaf"
#define X(name)     name##".x"

#define MODEL(name) X(name)
/*comment end*/

#define RobotPause1FileName          (ConstructRobotName(GameStates.CurrentRobot, MODEL("101")))
#define RobotPause2FileName          (ConstructRobotName(GameStates.CurrentRobot, MODEL("102")))
#define RobotWalkForwardFileName     (ConstructRobotName(GameStates.CurrentRobot, MODEL("103")))
#define RobotWalkBackFileName        (ConstructRobotName(GameStates.CurrentRobot, MODEL("104")))
#define RobotSideStepLeftFileName    (ConstructRobotName(GameStates.CurrentRobot, MODEL("105")))
#define RobotSideStepRightFileName   (ConstructRobotName(GameStates.CurrentRobot, MODEL("106")))
#define RobotTurnLeftFileName        (ConstructRobotName(GameStates.CurrentRobot, MODEL("107")))
#define RobotTurnRightFileName       (ConstructRobotName(GameStates.CurrentRobot, MODEL("108")))
#define RobotJumpFileName            (ConstructRobotName(GameStates.CurrentRobot, MODEL("109")))
#define RobotAcrobatic1FileName      (ConstructRobotName(GameStates.CurrentRobot, MODEL("110")))
#define RobotAcrobatic2FileName      (ConstructRobotName(GameStates.CurrentRobot, MODEL("111")))
#define RobotSkidFileName            (ConstructRobotName(GameStates.CurrentRobot, MODEL("112")))
#define RobotTravelForwardFileName   (ConstructRobotName(GameStates.CurrentRobot, MODEL("113")))
#define RobotTravelBackFileName      (ConstructRobotName(GameStates.CurrentRobot, MODEL("114")))
#define RobotTravelLeftFileName      (ConstructRobotName(GameStates.CurrentRobot, MODEL("115")))
#define RobotTravelRightFileName     (ConstructRobotName(GameStates.CurrentRobot, MODEL("116")))
#define RobotIntoRunFileName         (ConstructRobotName(GameStates.CurrentRobot, MODEL("117")))
#define RobotRunFileName             (ConstructRobotName(GameStates.CurrentRobot, MODEL("118")))
#define RobotHighAttack1FileName     (ConstructRobotName(GameStates.CurrentRobot, MODEL("119")))
#define RobotMediumAttack1FileName   (ConstructRobotName(GameStates.CurrentRobot, MODEL("120")))
#define RobotLowAttack1FileName      (ConstructRobotName(GameStates.CurrentRobot, MODEL("121")))
#define RobotHighAttack2FileName     (ConstructRobotName(GameStates.CurrentRobot, MODEL("122")))
#define RobotMediumAttack2FileName   (ConstructRobotName(GameStates.CurrentRobot, MODEL("123")))
#define RobotLowAttack2FileName      (ConstructRobotName(GameStates.CurrentRobot, MODEL("124")))
#define RobotJumpAttack1FileName     (ConstructRobotName(GameStates.CurrentRobot, MODEL("125")))
#define RobotJumpAttack2FileName     (ConstructRobotName(GameStates.CurrentRobot, MODEL("126")))
#define RobotSpecialAttack1FileName  (ConstructRobotName(GameStates.CurrentRobot, MODEL("127")))
#define RobotSpecialAttack2FileName  (ConstructRobotName(GameStates.CurrentRobot, MODEL("128")))
#define RobotSpecialAttack3FileName  (ConstructRobotName(GameStates.CurrentRobot, MODEL("129")))
#define RobotBlockHighFileName       (ConstructRobotName(GameStates.CurrentRobot, MODEL("130")))
#define RobotBlockMediumFileName     (ConstructRobotName(GameStates.CurrentRobot, MODEL("131")))
#define RobotBlockLowFileName        (ConstructRobotName(GameStates.CurrentRobot, MODEL("132")))
#define RobotHeadHitLeft1FileName    (ConstructRobotName(GameStates.CurrentRobot, MODEL("133")))
#define RobotHeadHitRight1FileName   (ConstructRobotName(GameStates.CurrentRobot, MODEL("134")))
#define RobotHeadHitLeft2FileName    (ConstructRobotName(GameStates.CurrentRobot, MODEL("135")))
#define RobotHeadHitRight2FileName   (ConstructRobotName(GameStates.CurrentRobot, MODEL("136")))
#define RobotChestHitLeft1FileName   (ConstructRobotName(GameStates.CurrentRobot, MODEL("137")))
#define RobotChestHitRight1FileName  (ConstructRobotName(GameStates.CurrentRobot, MODEL("138")))
#define RobotChestHitLeft2FileName   (ConstructRobotName(GameStates.CurrentRobot, MODEL("139")))
#define RobotChestHitRight2FileName  (ConstructRobotName(GameStates.CurrentRobot, MODEL("140")))
#define RobotLegHitLeft1FileName     (ConstructRobotName(GameStates.CurrentRobot, MODEL("141")))
#define RobotLegHitRight1FileName    (ConstructRobotName(GameStates.CurrentRobot, MODEL("142")))
#define RobotLegHitLeft2FileName     (ConstructRobotName(GameStates.CurrentRobot, MODEL("143")))
#define RobotLegHitRight2FileName    (ConstructRobotName(GameStates.CurrentRobot, MODEL("144")))
#define RobotKnockDown1FileName      (ConstructRobotName(GameStates.CurrentRobot, MODEL("145")))
#define RobotKnockDown2FileName      (ConstructRobotName(GameStates.CurrentRobot, MODEL("146")))
#define RobotKnockDown3FileName      (ConstructRobotName(GameStates.CurrentRobot, MODEL("147")))
#define RobotTaunt1FileName          (ConstructRobotName(GameStates.CurrentRobot, MODEL("148")))
#define RobotTaunt2FileName          (ConstructRobotName(GameStates.CurrentRobot, MODEL("149")))
#define RobotPickUpObjectFileName    (ConstructRobotName(GameStates.CurrentRobot, MODEL("150")))
#define RobotPauseWithObjectFileName (ConstructRobotName(GameStates.CurrentRobot, MODEL("151")))
#define RobotThrowObjectFileName     (ConstructRobotName(GameStates.CurrentRobot, MODEL("152")))


#define RobotPause1NumFrames RLVal(30)
#define RobotPause2NumFrames RLVal(30)
#define RobotWalkForwardNumFrames RLVal(30)
#define RobotWalkBackNumFrames RLVal(40)
#define RobotSideStepLeftNumFrames RLVal(30)
#define RobotSideStepRightNumFrames RLVal(30)
#define RobotTurnLeftNumFrames RLVal(20)
#define RobotTurnRightNumFrames RLVal(20)
#define RobotJumpNumFrames RLVal(25)
#define RobotAcrobatic1NumFrames RLVal(50)
#define RobotAcrobatic2NumFrames RLVal(50)
#define RobotSkidNumFrames RLVal(20)
#define RobotTravelForwardNumFrames RLVal(10)
#define RobotTravelBackNumFrames RLVal(10)
#define RobotTravelLeftNumFrames RLVal(10)
#define RobotTravelRightNumFrames RLVal(10)
#define RobotIntoRunNumFrames RLVal(15)
#define RobotRunNumFrames RLVal(30)
#define RobotHighAttack1NumFrames RLVal(30)
#define RobotMediumAttack1NumFrames RLVal(40)
#define RobotSuperJab1NumFrames RLVal(15)
#define RobotLowAttack1FirstNumFrames RLVal(13)
#define RobotLowAttack1TargetNumFrames RLVal(16)
#define RobotLowAttack1LastNumFrames RLVal(13)
#define RobotHighAttack2NumFrames RLVal(30)
#define RobotMediumAttack2NumFrames RLVal(35)
#define RobotLowAttack2NumFrames RLVal(60)
#define RobotJumpAttack1NumFrames RLVal(20)
#define RobotJumpAttack2NumFrames RLVal(20)
#define RobotSpecialAttack1NumFrames -RLVal(1)
#define RobotSpecialAttack2NumFrames -RLVal(1)
#define RobotSpecialAttack3NumFrames RLVal(60)
#define RobotBlockHighNumFrames RLVal(10)
#define RobotBlockMediumNumFrames RLVal(10)
#define RobotBlockLowNumFrames RLVal(10)
#define RobotHeadHitLeft1NumFrames RLVal(10)
#define RobotHeadHitRight1NumFrames RLVal(10)
#define RobotHeadHitLeft2NumFrames RLVal(10)
#define RobotHeadHitRight2NumFrames RLVal(10)
#define RobotChestHitLeft1NumFrames RLVal(10)
#define RobotChestHitRight1NumFrames RLVal(10)
#define RobotChestHitLeft2NumFrames RLVal(10)
#define RobotChestHitRight2NumFrames RLVal(10)
#define RobotLegHitLeft1NumFrames RLVal(10)
#define RobotLegHitRight1NumFrames RLVal(10)
#define RobotLegHitLeft2NumFrames RLVal(10)
#define RobotLegHitRight2NumFrames RLVal(10)
#define RobotKnockDown1NumFrames RLVal(60)
#define RobotKnockDown2NumFrames RLVal(60)
#define RobotKnockDown3NumFrames RLVal(60)
#define RobotTaunt1NumFrames RLVal(60)
#define RobotTaunt2NumFrames RLVal(120)
#define RobotPickUpObjectNumFrames RLVal(30)
#define RobotPauseWithObjectNumFrames RLVal(30)
#define RobotThrowObjectNumFrames RLVal(30)

#define RobotPause1Distance RLVal(0)
#define RobotPause2Distance RLVal(0)

//#define RobotWalkForwardDistance RLVal(2.36)
#define RobotTurnLeftDistance RLVal(0)
#define RobotTurnRightDistance RLVal(0)
#define RobotJumpDistance RLVal(0)
#define RobotTravelForwardDistance RLVal(0)
#define RobotHighAttack1Distance RLVal(0)
#define RobotMediumAttack1Distance RLVal(0)
#define RobotLowAttack1Distance RLVal(0)
#define RobotHighAttack2Distance RLVal(0)
#define RobotMediumAttack2Distance RLVal(0)
#define RobotLowAttack2Distance RLVal(0)
#define RobotJumpAttack1Distance RLVal(0)
#define RobotJumpAttack2Distance RLVal(0)
#define RobotSpecialAttack1Distance RLVal(0)
#define RobotSpecialAttack2Distance RLVal(0)
#define RobotSpecialAttack3Distance RLVal(0)
#define RobotBlockHighDistance RLVal(0)
#define RobotBlockMediumDistance RLVal(0)
#define RobotBlockLowDistance RLVal(0)
#define RobotHeadHitLeft1Distance RLVal(0)
#define RobotHeadHitRight1Distance RLVal(0)
#define RobotHeadHitLeft2Distance RLVal(0)
#define RobotHeadHitRight2Distance RLVal(0)
#define RobotChestHitLeft1Distance RLVal(0)
#define RobotChestHitRight1Distance RLVal(0)
#define RobotChestHitLeft2Distance RLVal(0)
#define RobotChestHitRight2Distance RLVal(0)
#define RobotLegHitLeft1Distance RLVal(0)
#define RobotLegHitRight1Distance RLVal(0)
#define RobotLegHitLeft2Distance RLVal(0)
#define RobotLegHitRight2Distance RLVal(0)
#define RobotTaunt1Distance RLVal(0)
#define RobotTaunt2Distance RLVal(0)
#define RobotPickUpObjectDistance RLVal(0)
#define RobotPauseWithObjectDistance RLVal(0)
#define RobotThrowObjectDistance RLVal(0)

#define RobotIntoRunStartFrame RLVal(4)
#define RobotJumpStopFrame RLVal(20)
#define RobotAcrobatic1StopFrame RLVal(30)
#define RobotAcrobatic2StopFrame RLVal(30)
#define RobotKnockDown1StopFrame RLVal(29)
#define RobotKnockDown2StopFrame RLVal(29)
#define RobotKnockDown3StopFrame RLVal(29)
#define RobotHeadHitLeft2StopFrame RLVal(6)
#define RobotHeadHitRight2StopFrame RLVal(6)
#define RobotChestHitLeft2StopFrame RLVal(6)
#define RobotChestHitRight2StopFrame RLVal(6)
#define RobotLegHitLeft2StopFrame RLVal(6)
#define RobotLegHitRight2StopFrame RLVal(6)
#define RobotLowAttack1FirstStopFrame RLVal(13)
#define RobotLowAttack1TargetStartFrame RLVal(5)
#define RobotLowAttack1TargetStopFrame RLVal(20)
#define RobotLowAttack1LastStartFrame RLVal(13)
#define RobotLowAttack1LastStopFrame RLVal(0)


#define RobotTurnLeftFreezeFrame RLVal(10)
#define RobotTurnRightFreezeFrame RLVal(10)
#define RobotJumpFreezeFrame RLVal(10)
#define RobotBlockHighFreezeFrame RLVal(6)
#define RobotBlockMediumFreezeFrame RLVal(6)
#define RobotBlockLowFreezeFrame RLVal(6)
#define RobotPickUpObjectFreezeFrame RLVal(16)

#define RobotHighAttack1HitFrame RLVal(12)
#define RobotHighAttack2HitFrame RLVal(14)
#define RobotThrowObjectHitFrame RLVal(16)




//This just in, late breaking flash, turning will be handled semi-independently from movement.
//It will check to see that the movement isn't in a bad RobotAnimationState, and will handle turning from there.
#define RobotPause1            0
#define RobotWalkForward       1
#define RobotJumpFirst         2
#define RobotJumpFreeze        3
#define RobotJumpLast          4
#define RobotJumpStop          5
#define RobotAcrobatic1        6
#define RobotAcrobatic1End     7
#define RobotAcrobatic2        8
#define RobotAcrobatic2End     9
#define RobotSkid              10
#define RobotTravelForward     11
#define RobotTravelBack        12
#define RobotTravelLeft        13
#define RobotTravelRight       14
#define RobotIntoIntoRun       15
#define RobotIntoRun           16
#define RobotRun               17
#define RobotHighAttack1       18
#define RobotMediumAttack1     19
#define RobotSuperJab1         20
#define RobotMediumAttack2     21
#define RobotLowAttack2        22
#define RobotSuperKick2        23
#define RobotJumpAttack1       24
#define RobotJumpAttack2       25
#define RobotSpecialAttack3    26
#define RobotBlockMediumFirst  27
#define RobotBlockMediumFreeze 28
#define RobotBlockMediumLast   29
#define RobotChestHitLeft2     30
#define RobotPickUpObjectFirst 31
#define RobotPickUpObjectFreeze 32
#define RobotPickUpObjectLast  33
#define RobotThrowObject       34
#define RobotAcrobatic1DontEnd 35
#define RobotAcrobatic2DontEnd 36
#define RobotTaunt2            37
#define RobotLowAttack1First   38
#define RobotLowAttack1Target  39
#define RobotLowAttack1Last    40
#define RobotTaunt1            41



/*
RobotPause1            
RobotPause2            
RobotWalkForward       
RobotWalkBack          
RobotSideStepLeft      
RobotSideStepRight     
RobotTurnLeftFirst     
RobotTurnLeftFreeze    
RobotTurnLeftLast      
RobotTurnRightFirst    
RobotTurnRightFreeze   
RobotTurnRightLast     
RobotJumpFirst         
RobotJumpFreeze        
RobotJumpLast          
RobotJumpStop          
RobotAcrobatic1        
RobotAcrobatic1End     
RobotAcrobatic2        
RobotAcrobatic2End     
RobotSkid              
RobotTravelForward     
RobotTravelBack        
RobotTravelLeft        
RobotTravelRight       
RobotIntoIntoRun       
RobotIntoRun           
RobotRun               
RobotHighAttack1       
RobotMediumAttack1     
RobotLowAttack1        
RobotSuperJab1         
RobotHighAttack2       
RobotMediumAttack2     
RobotLowAttack2        
RobotSuperKick2        
RobotJumpAttack1       
RobotJumpAttack2       
RobotSpecialAttack1    
RobotSpecialAttack2    
RobotSpecialAttack3    
RobotBlockHighFirst    
RobotBlockHighFreeze   
RobotBlockHighLast     
RobotBlockMediumFirst  
RobotBlockMediumFreeze 
RobotBlockMediumLast   
RobotBlockLowFirst     
RobotBlockLowFreeze    
RobotBlockLowLast      
RobotHeadHitLeft1      
RobotHeadHitRight1     
RobotHeadHitLeft2      
RobotHeadHitRight2     
RobotChestHitLeft1     
RobotChestHitRight1    
RobotChestHitLeft2     
RobotChestHitRight2    
RobotLegHitLeft1       
RobotLegHitRight1      
RobotLegHitLeft2       
RobotLegHitRight2      
RobotKnockDown1        
RobotGetBackUp1        
RobotKnockDown2        
RobotGetBackUp2        
RobotKnockDown3        
RobotGetBackUp2        
RobotTaunt1            
RobotTaunt2            
RobotPickUpObjectFirst 
RobotPickUpObjectFreeze 
RobotPickUpObjectLast  
RobotPauseWithObject   
RobotThrowObject       
*/
//numerical values of cool stuff.
int RobotAnimationState;               //This is the main control of the state.
RLValue RobotAnimationFrame;           //This is the current frame of the animation.
RLValue RobotLastVerticalSpeed;        //I'll go into the jump freeze after a certain number of frames, and come out when 
                                      //downward speed is as big as upward speed is.
//Flags which control whether or not you can affect movement.

#ifdef PC
extern FILE *shithead;
#endif
typedef int (*StateChange) (void);
//typedef StateChange *StateChangeList;
//StateChange is a function pointer,  There will be one function for each state,
//representing the switch into that state.  Each state will contain as many function
//pointers as there are states it can switch to.  The program will run down the list of these
//functions, and if one of them should return 1, then the program will quit looking.
typedef void (*StateFunction) (void);
//StateFunction is a function pointer.  There will be exactly one of them per state.  This
//is what takes the action appropriate to the state.  Unlike in the movement engine, we don't need
//to take the parameter of the Robot's frame, as we're not doing anything to it.  The animations
//magically link up to the Robot and move it, so all we need to do is set the correct animation
//to the correct time, and have at it.



typedef struct Robot_animation_state_
{
   RLValue Distance;        //How far the Robot will travel during the course of the animation,
   RLValue NumFrames;       //How long the animation is.  All frame numbers will be counted as fixed point numbers, as with RM standards.
   RLValue StopFrame;       //Which frame is the last.  Usually NumFrames, but some animations are more exotic.
   RLValue EnergyDrain;     //How much energy is drained in a frame.
   RLAnimationSet Anisette; //this little licorice flavored liqueur is RM's contribution to world peace of mind.
   StateFunction WhatToDo;
   int numchanges;
   StateChange *ChangeList;
}RobotAnimationStateStructure;

RobotAnimationStateStructure RobotAnimations[42];


/*
 * Robot animation package in a .BIN file
 * Sanfo 8.29
 */
DataPointer TekRobotData = 0;
PackedAnimations *TekRobotAnims;
HierarchicalModel *TekRobotHierarchy;
int TekRobotNumAnims;


/*
 * play animation from 47Tek.
 */
static
void RLAnimationSetSetTime(RLAnimationSet anim, RLValue time)
{
    TekApplyAnimation( TekRobotHierarchy, anim, time );
}


//I'll now create the raw materials for the state machine, all the state change functions and the
//state functions.

static int ToRobotPause1(void)
{//No turning, as that will require changes to the movement engine also.
   if(RobotMovementState==RobotWaiting||RobotMovementState==RobotWaitingOnBuilding)
   {//change from any of the movement states to pause.                  
         RobotAnimationState=RobotPause1;
         RobotAnimationFrame=RLVal(0.0);
         RFCountDown=0;
         return 1;
   }
   if(RobotAnimationState==RobotLowAttack1Last)
   {
      if(RobotAnimationFrame<=RobotAnimations[RobotAnimationState].StopFrame)
      {
         RobotAnimationState=RobotPause1;
         RobotAnimationFrame=RLVal(0.0);
		 if(RobotMovementState<=RobotSlideDownBuildingSide)
		 {
			RobotMovementState=RobotWaiting;
		 }
		 else
		 {
			 RobotMovementState=RobotWaitingOnBuilding;
		 }
         RobotDistance=RLVal(0.0);
         RobotNumMovementFrames=0;
         RobotData.DamageICause=0;
         RFCountDown=0;
         return 1;
      }
      return 0;
   }
   if((RobotMovementState==RobotStopped)&&(RobotAnimationFrame>=RobotAnimations[RobotAnimationState].StopFrame))
   {
         RobotAnimationState=RobotPause1;
         RobotAnimationFrame=RLVal(0.0);
         RobotMovementState=RobotWaiting;
         RobotDistance=RLVal(0.0);
         RobotNumMovementFrames=0;
         RobotData.NumOffensiveTubes=0;
         RobotData.OffensiveTubeList[0]=NULL;
         RobotData.OffensiveTubeList[1]=NULL;
         RobotData.DamageICause=0;
         RFCountDown=0;

//         RobotSwordSpots[RobotLeftSword].NumPoints=0;
//         RobotSwordSpots[RobotRightSword].NumPoints=0;
//         RobotHotSpots[RobotLeftFoot].NumPoints=0;
//         RobotHotSpots[RobotRightFoot].NumPoints=0;
         return 1;

   }
   if((RobotMovementState==RobotStoppedOnBuilding)&&(RobotAnimationFrame>=RobotAnimations[RobotAnimationState].StopFrame))
   {
	     DeactivateJets();
         RobotAnimationState=RobotPause1;
         RobotAnimationFrame=RLVal(0.0);
         RobotMovementState=RobotWaitingOnBuilding;
         RobotDistance=RLVal(0.0);
         RobotNumMovementFrames=0;
         RobotData.NumOffensiveTubes=0;
         RobotData.OffensiveTubeList[0]=NULL;
         RobotData.OffensiveTubeList[1]=NULL;
         RobotData.DamageICause=0;

//         RobotSwordSpots[RobotLeftSword].NumPoints=0;
//         RobotSwordSpots[RobotRightSword].NumPoints=0;
//         RobotHotSpots[RobotLeftFoot].NumPoints=0;
//         RobotHotSpots[RobotRightFoot].NumPoints=0;
         RFCountDown=0;
         return 1;

   }
   return 0;
   
}
static int ToRobotWalkForward(void)
{
   if(RobotMovementState==RobotFAccelerating2||RobotMovementState==RobotFTopSpeed1||
      RobotMovementState==RobotFAccelerating3||RobotMovementState==RobotFTopSpeed2||
      RobotMovementState==RobotFAccelerating2OnBuilding||RobotMovementState==RobotFTopSpeed1OnBuilding||
      RobotMovementState==RobotFTopSpeed2OnBuilding
      )
   {
      RobotAnimationState=RobotWalkForward;
      RobotAnimationFrame=RLVal(0.0);
      StageNumber=0;
      return 1;
   }
   return 0;
}
static int ToRobotJumpFirst(void)
{
   if(RobotMovementState==RobotJumping)
   {
      RobotAnimationState=RobotJumpFirst;
      RobotAnimationFrame=RLVal(0.0);
      return 1;
   }
   return 0;

}
static int ToRobotJumpFreeze(void)
{
   if(RobotAnimationFrame>=RobotAnimations[RobotAnimationState].StopFrame)
   {
      RobotAnimationState=RobotJumpFreeze;
      RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
      RobotLastVerticalSpeed=-RobotYSpeed;
      return 1;
   }
   return 0;
}
static int ToRobotJumpLast(void)
{
   if(RobotAnimationState!=RobotJumpFreeze && RobotAnimationState!=RobotJumpFirst)
   {
      RobotAnimationState=RobotJumpLast;
      RobotAnimationFrame=RobotJumpStopFrame;
      return 1;
   }
   if(RobotAnimationState==RobotJumpFreeze)
   {
      extern RLFrame Wscene;
	  extern RLValue RobotGravity;
      RLVector RobotPlace;
      RLValue height, t = RobotJumpStopFrame - RobotJumpFreezeFrame;
	  RLFrameGetPosition(Robotframe, Wscene, &RobotPlace);
	  height = RobotPlace.y - SpuddeMapHeight2(RobotPlace.x, RobotPlace.z);
      if ((0.5)*RobotGravity*(t*t)+RobotYSpeed*t < -height)
      //if(RobotLastVerticalSpeed>=RobotYSpeed)
      {
         RobotAnimationState=RobotJumpLast;
         return 1;
      }
      return 0;
   }
   if(RobotYSpeed <= RLVal(0))
   {
      RobotAnimationState=RobotJumpLast;
      RobotAnimationFrame=RobotJumpStopFrame-RobotAnimationFrame;
      return 1;
   }
   return 0;
}
static int ToRobotJumpStop(void)
{
   if(RobotMovementState==RobotStopped)
   {
      RobotAnimationState=RobotJumpStop;
      RobotAnimationFrame=RobotJumpStopFrame;
      YBPlay3DSound(RobotFootStep,Robotframe);
      return 1;
   }
   return 0;
}
static int ToRobotAcrobatic1(void)
{
   return 0;
}
static int ToRobotAcrobatic1End(void)
{
   if(RobotAnimationState==RobotAcrobatic1&&RobotAnimationFrame>=RobotAnimations[RobotAnimationState].StopFrame)
   {
      YBPlay3DSound(RobotFallDown, Robotframe);
      RobotAnimationState=RobotAcrobatic1End;
      RobotMovementState=RobotStopped;
      RobotDistance=RLVal(0.0);
      return 1;
   }
   return 0;

}
static int ToRobotAcrobatic1DontEnd(void)
{
   if(RobotAnimationState==RobotAcrobatic1&&RobotAnimationFrame>=RobotAnimations[RobotAnimationState].StopFrame&&RobotLife<=0)
   {
      YBPlay3DSound(RobotFallDown, Robotframe);
      RobotAnimationState=RobotAcrobatic1DontEnd;
      RobotMovementState=RobotStopped;
      RobotDistance=RLVal(0.0);
      switch(GameStates.CurrentRobot)
      {
         case SabreRobot:
            RobotAnimationFrame=RLVal(30);
         break;
         case KataRobot:
            RobotAnimationFrame=RLVal(26);
         break;
         case StealthRobot:
            RobotPosition.y-=RLVal(.57); 
            RobotAnimationFrame=RLVal(15);
         break;
         case KaberRobot:
            RobotAnimationFrame=RLVal(30);
         break;
         case MerRobot:
            RobotAnimationFrame=RLVal(30);
         break;
      }
      return 1;
   }
   return 0;


}
static int ToRobotAcrobatic2(void)
{
   return 0;
}
static int ToRobotAcrobatic2End(void)
{
   if(RobotAnimationState==RobotAcrobatic2&&RobotAnimationFrame>=RobotAnimations[RobotAnimationState].StopFrame)
   {
      YBPlay3DSound(RobotFallDown, Robotframe);
      RobotAnimationState=RobotAcrobatic2End;
      RobotMovementState=RobotStopped;
      RobotDistance=RLVal(0.0);
      return 1;
   }
   return 0;
}
static int ToRobotAcrobatic2DontEnd(void)
{
   if(RobotAnimationState==RobotAcrobatic2&&RobotAnimationFrame>=RobotAnimations[RobotAnimationState].StopFrame&&RobotLife<=0)
   {
      YBPlay3DSound(RobotFallDown, Robotframe);
      RobotAnimationState=RobotAcrobatic2DontEnd;
      RobotMovementState=RobotStopped;
      RobotDistance=RLVal(0.0);
      switch(GameStates.CurrentRobot)
      {
         case SabreRobot:
            RobotAnimationFrame=RLVal(28);
         break;
         case KataRobot:
            RobotAnimationFrame=RLVal(25);
         break;
         case StealthRobot:
            RobotPosition.y-=RLVal(1.79); 
            RobotAnimationFrame=RLVal(10);
         break;
         case KaberRobot:
            RobotAnimationFrame=RLVal(30);
         break;
         case MerRobot:
            RobotAnimationFrame=RLVal(30);
         break;
      }
      return 1;
   }
   return 0;
}

static int ToRobotSkid(void)
{
   if(RobotMovementState==RobotFBraking)
   {
      RobotAnimationState=RobotSkid;
      RobotAnimationFrame=RLVal(0.0);
      return 1;
   }
   return 0;
}
static int ToRobotTravelForward(void)
{
   if(RobotMovementState==RobotFTopSpeed4)
   {
      RobotAnimationState=RobotTravelForward;
      RobotAnimationFrame=RLVal(0.0);
//   YBPlay3DSound(RobotJets, Robotframe);
      return 1;
   }
   return 0;
}
static int ToRobotTravelBack(void)
{
   if(RobotMovementState==RobotBAccelerating3
   ||RobotMovementState==RobotBAccelerating1||RobotMovementState==RobotBAccelerating2
   ||RobotMovementState==RobotBAccelerating1OnBuilding)
   {
      RobotAnimationState=RobotTravelBack;
      RobotAnimationFrame=RLVal(0.0);
//   YBPlay3DSound(RobotJets, Robotframe);
      return 1;
   }
   return 0;
}
static int ToRobotTravelLeft(void)
{
   if(RobotMovementState==RobotLAccelerating2
   ||RobotMovementState==RobotLAccelerating1
   ||RobotMovementState==RobotLAccelerating1OnBuilding)
   {
      RobotAnimationState=RobotTravelLeft;
      RobotAnimationFrame=RLVal(0.0);
//   YBPlay3DSound(RobotJets, Robotframe );
      return 1;
   }
   return 0;
}
static int ToRobotTravelRight(void)
{
   if(RobotMovementState==RobotRAccelerating2
   ||RobotMovementState==RobotRAccelerating1
   ||RobotMovementState==RobotRAccelerating1OnBuilding)
   {
      RobotAnimationState=RobotTravelRight;
      RobotAnimationFrame=RLVal(0.0);
//   YBPlay3DSound(RobotJets, Robotframe);
      return 1;
   }
   return 0;
}
static int ToRobotIntoIntoRun(void)
{
   if(RobotMovementState==RobotFAccelerating1
      ||RobotMovementState==RobotFAccelerating1OnBuilding)
   {
      RobotAnimationState=RobotIntoIntoRun;
      RobotAnimationFrame=RLVal(0);
      return 1;
   }
   return 0;
}
static int ToRobotIntoRun(void)
{
   if(RobotAnimationState==RobotIntoIntoRun&&RobotAnimationFrame>=RobotAnimations[RobotAnimationState].StopFrame)
   {
      RobotAnimationState=RobotIntoRun;
      return 1;
   }
   return 0;

}
static int ToRobotRun(void)
{
   if(RobotMovementState==RobotFTopSpeed3||RobotMovementState==RobotFAccelerating4)
   {
      RobotAnimationState=RobotRun;
      return 1;
   }
   return 0;
}
static int ToRobotHighAttack1(void)
{
// Plasma Shuriken (homer)

   if(RobotMovementState==RobotWaiting)
   {
      //if( ((InputInt&COMMANDHighAttack)||(InputInt&COMMANDLowAttack)) && (InputInt&COMMANDStrongShift) && !(InputInt&COMMANDDefenseShift))
      if( (InputInt&COMMANDShuriken))
      {
//         RobotAttackFerocity=HighAttack1Ferocity;
	   if(RobotEngy<RobotHighAttack1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotAnimationState=RobotHighAttack1;
         RobotAnimationFrame=0;
         RobotMovementState=RobotStopped;
		 StageNumber=0;
         return 1;
      }
   }
   if(RobotMovementState==RobotWaitingOnBuilding)
   {
      //if( ((InputInt&COMMANDHighAttack)||(InputInt&COMMANDLowAttack)) && (InputInt&COMMANDStrongShift) && !(InputInt&COMMANDDefenseShift))
      if( (InputInt&COMMANDShuriken))
      {
//         RobotAttackFerocity=HighAttack1Ferocity;
	   if(RobotEngy<RobotHighAttack1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotAnimationState=RobotHighAttack1;
         RobotAnimationFrame=0;
         RobotMovementState=RobotStoppedOnBuilding;
		 StageNumber=0;
         return 1;
      }
   }
   else if((RobotMovementState>=RobotFAccelerating1)&&(RobotMovementState<=RobotFBraking))
   {
      //if( ((InputInt&COMMANDHighAttack)||(InputInt&COMMANDLowAttack)) && (InputInt&COMMANDStrongShift) && !(InputInt&COMMANDDefenseShift))
      if( (InputInt&COMMANDShuriken))
      {
//         RobotAttackFerocity=HighAttack1Ferocity;
	   if(RobotEngy<RobotHighAttack1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotAnimationState=RobotHighAttack1;
         RobotAnimationFrame=0;
         RobotMovementState=RobotFBraking;
		 StageNumber=0;
         return 1;
      }
   }
   else if((RobotMovementState>=RobotFAccelerating1OnBuilding)&&(RobotMovementState<=RobotFDeceleratingOnBuilding))
   {
      //if( ((InputInt&COMMANDHighAttack)||(InputInt&COMMANDLowAttack)) && (InputInt&COMMANDStrongShift) && !(InputInt&COMMANDDefenseShift))
      if( (InputInt&COMMANDShuriken))
      {
//         RobotAttackFerocity=HighAttack1Ferocity;
	   if(RobotEngy<RobotHighAttack1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotAnimationState=RobotHighAttack1;
         RobotAnimationFrame=0;
         RobotMovementState=RobotFDeceleratingOnBuilding;
		 StageNumber=0;
         return 1;
      }
   }
   else if((RobotMovementState>=RobotBAccelerating1)&&(RobotMovementState<=RobotBBraking))
   {
      //if( ((InputInt&COMMANDHighAttack)||(InputInt&COMMANDLowAttack)) && (InputInt&COMMANDStrongShift) && !(InputInt&COMMANDDefenseShift))
      if( (InputInt&COMMANDShuriken))
      {
//         RobotAttackFerocity=HighAttack1Ferocity;
	   if(RobotEngy<RobotHighAttack1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotAnimationState=RobotHighAttack1;
         RobotAnimationFrame=0;
         RobotMovementState=RobotBBraking;
		 StageNumber=0;
         return 1;
      }
   }
   else if((RobotMovementState>=RobotBAccelerating1OnBuilding)&&(RobotMovementState<=RobotBDeceleratingOnBuilding))
   {
      //if( ((InputInt&COMMANDHighAttack)||(InputInt&COMMANDLowAttack)) && (InputInt&COMMANDStrongShift) && !(InputInt&COMMANDDefenseShift))
      if( (InputInt&COMMANDShuriken))
      {
//         RobotAttackFerocity=HighAttack1Ferocity;
	   if(RobotEngy<RobotHighAttack1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotAnimationState=RobotHighAttack1;
         RobotAnimationFrame=0;
         RobotMovementState=RobotBDeceleratingOnBuilding;
		 StageNumber=0;
         return 1;
      }
   }
   else if((RobotMovementState>=RobotLAccelerating1)&&(RobotMovementState<=RobotLBraking))
   {
      //if( ((InputInt&COMMANDHighAttack)||(InputInt&COMMANDLowAttack)) && (InputInt&COMMANDStrongShift) && !(InputInt&COMMANDDefenseShift))
      if( (InputInt&COMMANDShuriken))
      {
//         RobotAttackFerocity=HighAttack1Ferocity;
	   if(RobotEngy<RobotHighAttack1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotAnimationState=RobotHighAttack1;
         RobotAnimationFrame=0;
         RobotMovementState=RobotLBraking;
		 StageNumber=0;
         return 1;
      }
   }
   else if((RobotMovementState>=RobotLAccelerating1OnBuilding)&&(RobotMovementState<=RobotLDeceleratingOnBuilding))
   {
      //if( ((InputInt&COMMANDHighAttack)||(InputInt&COMMANDLowAttack)) && (InputInt&COMMANDStrongShift) && !(InputInt&COMMANDDefenseShift))
      if( (InputInt&COMMANDShuriken))
      {
//         RobotAttackFerocity=HighAttack1Ferocity;
	   if(RobotEngy<RobotHighAttack1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotAnimationState=RobotHighAttack1;
         RobotAnimationFrame=0;
         RobotMovementState=RobotLDeceleratingOnBuilding;
		 StageNumber=0;
         return 1;
      }
   }
   else if((RobotMovementState>=RobotRAccelerating1)&&(RobotMovementState<=RobotRBraking))
   {
      //if( ((InputInt&COMMANDHighAttack)||(InputInt&COMMANDLowAttack)) && (InputInt&COMMANDStrongShift) && !(InputInt&COMMANDDefenseShift))
      if( (InputInt&COMMANDShuriken))
      {
//         RobotAttackFerocity=HighAttack1Ferocity;
	   if(RobotEngy<RobotHighAttack1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotAnimationState=RobotHighAttack1;
         RobotAnimationFrame=0;
         RobotMovementState=RobotRBraking;
		 StageNumber=0;
         return 1;
      }
   }
   else if((RobotMovementState>=RobotRAccelerating1OnBuilding)&&(RobotMovementState<=RobotRDeceleratingOnBuilding))
   {
      //if( ((InputInt&COMMANDHighAttack)||(InputInt&COMMANDLowAttack)) && (InputInt&COMMANDStrongShift) && !(InputInt&COMMANDDefenseShift))
      if( (InputInt&COMMANDShuriken))
      {
//         RobotAttackFerocity=HighAttack1Ferocity;
	   if(RobotEngy<RobotHighAttack1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotAnimationState=RobotHighAttack1;
         RobotAnimationFrame=0;
         RobotMovementState=RobotRDeceleratingOnBuilding;
		 StageNumber=0;
         return 1;
      }
   }
   return 0;
}
static int ToRobotMediumAttack1(void)
{
   if(RobotMovementState==RobotWaiting)
   {
      if( (InputInt&COMMANDPlasmaBlades) && !(InputInt&COMMANDDefenseShift))
      {
//         RobotAttackFerocity=MediumAttack1Ferocity;
	   if(RobotEngy<RobotMediumAttack1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotAnimationState=RobotMediumAttack1;
         RobotAnimationFrame=0;
         RobotMovementState=RobotStopped;
         YBPlay3DSound(SwordSwish, Robotframe);
         return 1;
      }
   }
   else if(RobotMovementState==RobotWaitingOnBuilding)
   {
      if( (InputInt&COMMANDPlasmaBlades) && !(InputInt&COMMANDDefenseShift))
      {
//         RobotAttackFerocity=MediumAttack1Ferocity;
	   if(RobotEngy<RobotMediumAttack1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotAnimationState=RobotMediumAttack1;
         RobotAnimationFrame=0;
         RobotMovementState=RobotStoppedOnBuilding;
         YBPlay3DSound(SwordSwish, Robotframe);
         return 1;
      }
   }
   else if((RobotMovementState>=RobotFAccelerating1)&&(RobotMovementState<=RobotFBraking))
   {
      //if( (InputInt&COMMANDHighAttack) && (InputInt&COMMANDMediumShift) && !(InputInt&COMMANDDefenseShift))
      if( (InputInt&COMMANDPlasmaBlades))
      {
//         RobotAttackFerocity=MediumAttack1Ferocity;
	   if(RobotEngy<RobotMediumAttack1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotAnimationState=RobotMediumAttack1;
         RobotAnimationFrame=0;
         RobotMovementState=RobotFBraking;
         YBPlay3DSound(SwordSwish, Robotframe);
         return 1;
      }
   }
   else if((RobotMovementState>=RobotFAccelerating1OnBuilding)&&(RobotMovementState<=RobotFDeceleratingOnBuilding))
   {
      //if( (InputInt&COMMANDHighAttack) && (InputInt&COMMANDMediumShift) && !(InputInt&COMMANDDefenseShift))
      if( (InputInt&COMMANDPlasmaBlades))
      {
//         RobotAttackFerocity=MediumAttack1Ferocity;
	   if(RobotEngy<RobotMediumAttack1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotAnimationState=RobotMediumAttack1;
         RobotAnimationFrame=0;
         RobotMovementState=RobotFDeceleratingOnBuilding;
         YBPlay3DSound(SwordSwish, Robotframe);
         return 1;
      }
   }
   else if((RobotMovementState>=RobotBAccelerating1)&&(RobotMovementState<=RobotBBraking))
   {
      //if( (InputInt&COMMANDHighAttack) && (InputInt&COMMANDMediumShift) && !(InputInt&COMMANDDefenseShift))
      if( (InputInt&COMMANDPlasmaBlades))
      {
//         RobotAttackFerocity=MediumAttack1Ferocity;
	   if(RobotEngy<RobotMediumAttack1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotAnimationState=RobotMediumAttack1;
         RobotAnimationFrame=0;
         RobotMovementState=RobotBBraking;
         YBPlay3DSound(SwordSwish, Robotframe);
         return 1;
      }
   }
   else if((RobotMovementState>=RobotBAccelerating1OnBuilding)&&(RobotMovementState<=RobotBDeceleratingOnBuilding))
   {
      //if( (InputInt&COMMANDHighAttack) && (InputInt&COMMANDMediumShift) && !(InputInt&COMMANDDefenseShift))
      if( (InputInt&COMMANDPlasmaBlades))
      {
//         RobotAttackFerocity=MediumAttack1Ferocity;
	   if(RobotEngy<RobotMediumAttack1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotAnimationState=RobotMediumAttack1;
         RobotAnimationFrame=0;
         RobotMovementState=RobotBDeceleratingOnBuilding;
         YBPlay3DSound(SwordSwish, Robotframe);
         return 1;
      }
   }
   else if((RobotMovementState>=RobotLAccelerating1)&&(RobotMovementState<=RobotLBraking))
   {
      //if( (InputInt&COMMANDHighAttack) && (InputInt&COMMANDMediumShift) && !(InputInt&COMMANDDefenseShift))
      if( (InputInt&COMMANDPlasmaBlades))
      {
//         RobotAttackFerocity=MediumAttack1Ferocity;
	   if(RobotEngy<RobotMediumAttack1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotAnimationState=RobotMediumAttack1;
         RobotAnimationFrame=0;
         RobotMovementState=RobotLBraking;
         return 1;
      }
   }
   else if((RobotMovementState>=RobotLAccelerating1OnBuilding)&&(RobotMovementState<=RobotLDeceleratingOnBuilding))
   {
      //if( (InputInt&COMMANDHighAttack) && (InputInt&COMMANDMediumShift) && !(InputInt&COMMANDDefenseShift))
      if( (InputInt&COMMANDPlasmaBlades))
      {
//         RobotAttackFerocity=MediumAttack1Ferocity;
	   if(RobotEngy<RobotMediumAttack1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotAnimationState=RobotMediumAttack1;
         RobotAnimationFrame=0;
         RobotMovementState=RobotLDeceleratingOnBuilding;
         return 1;
      }
   }
   else if((RobotMovementState>=RobotRAccelerating1)&&(RobotMovementState<=RobotRBraking))
   {
      //if( (InputInt&COMMANDHighAttack) && (InputInt&COMMANDMediumShift) && !(InputInt&COMMANDDefenseShift))
      if( (InputInt&COMMANDPlasmaBlades))
      {
//         RobotAttackFerocity=MediumAttack1Ferocity;
	   if(RobotEngy<RobotMediumAttack1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotAnimationState=RobotMediumAttack1;
         RobotAnimationFrame=0;
         RobotMovementState=RobotRBraking;
         return 1;
      }
   }
   else if((RobotMovementState>=RobotRAccelerating1OnBuilding)&&(RobotMovementState<=RobotRDeceleratingOnBuilding))
   {
      //if( (InputInt&COMMANDHighAttack) && (InputInt&COMMANDMediumShift) && !(InputInt&COMMANDDefenseShift))
      if( (InputInt&COMMANDPlasmaBlades))
      {
//         RobotAttackFerocity=MediumAttack1Ferocity;
	   if(RobotEngy<RobotMediumAttack1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotAnimationState=RobotMediumAttack1;
         RobotAnimationFrame=0;
         RobotMovementState=RobotRDeceleratingOnBuilding;
         return 1;
      }
   }


   return 0;
}
static int ToRobotLowAttack1First(void)
{
   // photon cannon (rapid fire)
   if(RobotMovementState==RobotWaiting)
   {
	   if( (InputInt&COMMANDPhotonCannon) && !(InputInt&COMMANDDefenseShift))
	   {
	//      RobotAttackFerocity=LowAttack1Ferocity;
	   if(RobotEngy<RobotLowAttack1FirstEnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
		  RobotAnimationState=RobotLowAttack1First;
		  RobotAnimationFrame=0;
		  RobotMovementState=RobotStopped;
		  return 1;
	   }
   }
   else if(RobotMovementState==RobotWaitingOnBuilding)
   {
	   if( (InputInt&COMMANDPhotonCannon) && !(InputInt&COMMANDDefenseShift))
	   {
	//      RobotAttackFerocity=LowAttack1Ferocity;
	   if(RobotEngy<RobotLowAttack1FirstEnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
		  RobotAnimationState=RobotLowAttack1First;
		  RobotAnimationFrame=0;
		  RobotMovementState=RobotStoppedOnBuilding;
		  return 1;
	   }
   }
   return 0;
}
static int ToRobotLowAttack1Target(void)
{
   if( (InputInt&COMMANDPhotonCannon) && !(InputInt&COMMANDDefenseShift))
   {
      if(RobotAnimationFrame>=RobotAnimations[RobotAnimationState].StopFrame)
      {
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
   		 RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
         RobotAnimationState=RobotLowAttack1Target;
         RFCountDown=0;
         return 1;
      }
   }
   return 0;
}

static int ToRobotLowAttack1Last(void)
{
   if(RobotEngy<RobotLowAttack1TargetEnergyMinimum)
   {
      RobotAnimationState=RobotLowAttack1Last;
		YBPlay3DSound(RobotClick,Robotframe);
	  //      RobotAnimationFrame=RobotAnimations[RobotAnimationState].StartFrame;
      return 1;
   }
   if(!(InputInt&COMMANDPhotonCannon))
   {
      RobotAnimationState=RobotLowAttack1Last;
  //    RobotAnimationFrame=RobotAnimations[RobotAnimationState].StartFrame;
      return 1;
   }
   return 0;
}
static int ToRobotSuperJab1(void)
{
   if( (InputInt&COMMANDHighAttack) && !(InputInt&COMMANDDefenseShift))
   {
//      RobotAttackFerocity=SuperJab1Ferocity;
	   if(RobotEngy<RobotSuperJab1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
      RobotAnimationState=RobotSuperJab1;
      RobotAnimationFrame=0;
      RobotMovementState=RobotStopped;
      return 1;
   }
   return 0;
}
static int ToRobotMediumAttack2(void)
{
   if( (InputInt&COMMANDLowAttack) && (InputInt&COMMANDMediumShift) && !(InputInt&COMMANDDefenseShift))
   {
//      RobotAttackFerocity=MediumAttack2Ferocity;
	   if(RobotEngy<RobotMediumAttack2EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
      RobotAnimationState=RobotMediumAttack2;
      RobotAnimationFrame=0;
      RobotMovementState=RobotStopped;
      return 1;
   }
   return 0;
}
static int ToRobotLowAttack2(void)
{
   // Ultra Blast (concussion)
   if(RobotMovementState==RobotWaiting)
   {
   if( (InputInt&COMMANDUltraBlast) && !(InputInt&COMMANDDefenseShift))
   {
//      RobotAttackFerocity=LowAttack2Ferocity;
   if(RobotEngy<RobotLowAttack2EnergyMinimum)
	{
		YBPlay3DSound(RobotClick,Robotframe);
		return 0;
	}
      RobotAnimationState=RobotLowAttack2;
      RobotAnimationFrame=0;
      RobotMovementState=RobotStopped;
      StageNumber=0;
      return 1;
   }
   }
   else if(RobotMovementState==RobotWaitingOnBuilding)
   {
   if( (InputInt&COMMANDUltraBlast) && !(InputInt&COMMANDDefenseShift))
   {
//      RobotAttackFerocity=LowAttack2Ferocity;
   if(RobotEngy<RobotLowAttack2EnergyMinimum)
	{
		YBPlay3DSound(RobotClick,Robotframe);
		return 0;
	}
      RobotAnimationState=RobotLowAttack2;
      RobotAnimationFrame=0;
      RobotMovementState=RobotStoppedOnBuilding;
      StageNumber=0;
      return 1;
   }
   }
   return 0;
}
static int ToRobotSuperKick2(void)
{
   if( (InputInt&COMMANDLowAttack) && !(InputInt&COMMANDDefenseShift))
   {
//      RobotAttackFerocity=SuperKick2Ferocity;
   if(RobotEngy<RobotSuperKick2EnergyMinimum)
	{
		YBPlay3DSound(RobotClick,Robotframe);
		return 0;
	}
      RobotAnimationState=RobotSuperKick2;
      RobotAnimationFrame=0;
      RobotMovementState=RobotStopped;
      return 1;
   }
   return 0;
}
static int ToRobotJumpAttack1(void)
{
   return 0;
}
static int ToRobotJumpAttack2(void)
{
   return 0;
}
static int ToRobotSpecialAttack3(void)
{//RobotSpecialAttack3 is currently not in use.
   if((InputInt&COMMANDHighAttack) && (InputInt&COMMANDLowAttack) && (InputInt&COMMANDJump) && (InputInt&COMMANDCrouch) 
        &&((RobotAnimationFrame<RLVal(2.5))||(RobotMovementState==RobotPause1)) && !(InputInt&COMMANDDefenseShift) )
   {
//      RobotAttackFerocity=SpecialAttack3Ferocity;
	   if(RobotEngy<RobotSpecialAttack3EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
      RobotAnimationState=RobotSpecialAttack3;
      RobotAnimationFrame=0;
      RobotMovementState=RobotStopped;
      return 1;
   }
   return 0;
}
static int ToRobotBlockMediumFirst(void)
{
   if( (InputInt&COMMANDDefenseShift) && ((InputInt&COMMANDHighAttack) || (InputInt&COMMANDLowAttack)) )
   {
      if(RobotAnimationState==RobotPause1)
      {
         RobotAnimationState=RobotBlockMediumFirst;
         RobotAnimationFrame=0;
		 if(RobotMovementState==RobotWaiting)
		 {
			RobotMovementState=RobotStopped;
		 }
		 else if(RobotMovementState==RobotWaitingOnBuilding)
		 {
			 RobotMovementState=RobotStoppedOnBuilding;
		 }
         return 1;
      }
//      if(RobotAnimationState==RobotBlockLowFirst || RobotAnimationState==RobotBlockHighFirst)
//      {
//         RobotAnimationState=RobotBlockMediumFirst;
//         return 1;
//      }
      if(RobotAnimationState==RobotBlockMediumLast /*|| RobotAnimationState==RobotBlockHighLast || RobotAnimationState==RobotBlockLowLast*/)
      {
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame-RobotAnimationFrame;
         RobotAnimationState=RobotBlockMediumFirst;
         return 1;
      }
   }
   return 0;
}
static int ToRobotBlockMediumFreeze(void)
{
   if( RobotAnimationState==RobotBlockMediumFirst && RobotAnimationFrame>=RobotAnimations[RobotAnimationState].StopFrame)
   {
      extern int shielddlist;
      RobotAnimationState=RobotBlockMediumFreeze;
      RLFrameAddChild(Robotframe,RobotBlockSphere);

	  
	  RLFrameSetOrientation(RobotBlockSphere,RLFrameGetScene(RobotBlockSphere),
	  	0, 1, 0, 
		0, 0, 1);
      RLFrameSetRotation(RobotBlockSphere,RobotBlockSphere,0,RLVal(0),1,RobotBlockSphereRotation);
      RLFrameSetPosition(RobotBlockSphere,Robotframe,0,RobotBlockSphereHeight,0);

      FlipTextureCoords(shielddlist, 0);
      BlockCountDown=-1;
      return 1;
   }
   return 0;
}
static int ToRobotBlockMediumLast(void)
{
   if( !( (InputInt&COMMANDDefenseShift) && ((InputInt&COMMANDHighAttack) || (InputInt&COMMANDLowAttack) )))
   {
      RLFrameAddChild(behindthescene,RobotBlockSphere);
      RobotAnimationState=RobotBlockMediumLast;
      RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame-RobotAnimationFrame;
      return 1;
   }
   return 0;
}
static int ToRobotPickUpObjectFirst(void)
{
   if( (InputInt&COMMANDCrouch) || (RobotEngy<0) )
   {
      if(RobotAnimationState==RobotPickUpObjectLast)
      {
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame-RobotAnimationFrame;
         RobotAnimationState=RobotPickUpObjectFirst;
//         RobotMovementState=RobotStopped;
         return 1;
      }
      RobotAnimationState=RobotPickUpObjectFirst;
      RobotAnimationFrame=0;
		 if(RobotMovementState==RobotWaiting)
		 {
			RobotMovementState=RobotStopped;
		 }
		 else if(RobotMovementState==RobotWaitingOnBuilding)
		 {
			 RobotMovementState=RobotStoppedOnBuilding;
		 }
      return 1;
   }
   return 0;
}
static int ToRobotPickUpObjectFreeze(void)
{
   if( RobotAnimationFrame>=RobotAnimations[RobotAnimationState].StopFrame)
   {
      if (PowerUpHere(Robotframe)) 
	  {
         RobotEngy += PowerUpEnergy;
		 YBPlay3DSound(RobotSomething, Robotframe);
      }
      RobotAnimationState=RobotPickUpObjectFreeze;
      return 1;
   }
   return 0;
}
static int ToRobotPickUpObjectLast(void)
{
   if(( !(InputInt&COMMANDCrouch) ) && (RobotEngy>0))
   {
      RobotAnimationState=RobotPickUpObjectLast;
      RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame-RobotAnimationFrame;
      return 1;
   }
   return 0;
}
static int ToRobotThrowObject(void)
{
   return 0;
}

static int ToRobotTaunt2(void)
{
   //if(RobotEngy<RobotTaunt2EnergyMinimum)
   //   return 0;
   if(((MonsterAnimationState==MonsterAllDead) && (GameStates.CurrentSubmonster==Gamma)))
   {
	  YBPlay3DSound(RobotSomething, Robotframe);
      RobotAnimationState=RobotTaunt2;
      NumRobotTaunts=1;
      RobotAnimationFrame=0;
		 if(RobotMovementState==RobotWaiting)
		 {
			RobotMovementState=RobotStopped;
		 }
		 else if(RobotMovementState==RobotWaitingOnBuilding)
		 {
			 RobotMovementState=RobotStoppedOnBuilding;
		 }
      return 1;
   }
   return 0;
}

static int ToRobotTaunt1(void)
{
   if(((InputInt&COMMANDWeakShift)&&(InputInt&COMMANDMediumShift)&&(InputInt&COMMANDStrongShift)))
   {
	   if(RobotEngy<RobotTaunt1EnergyMinimum)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
	  YBPlay3DSound(RobotSomething, Robotframe);
      RobotAnimationState=RobotTaunt1;
      RobotAnimationFrame=0;
		 if(RobotMovementState==RobotWaiting)
		 {
			RobotMovementState=RobotStopped;
		 }
		 else if(RobotMovementState==RobotWaitingOnBuilding)
		 {
			 RobotMovementState=RobotStoppedOnBuilding;
		 }
      return 1;
   }
   return 0;
}


static void RobotPause1Function(void)
{
//This is the function for when you loop back to yourself automatically,
//and the timing is incremented automatically as time goes by.
//   FILE *shithead;
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);

//   RobotAnimationFrame+=RLVal(1.0);

   if((InputInt&COMMANDVisorBeam))
   {
      LaunchVisorBeam();
   }

   RobotAnimationFrame+=DiffFrame;
   if(RobotAnimationFrame>=RobotAnimations[RobotAnimationState].StopFrame)
      RobotAnimationFrame-=RobotAnimations[RobotAnimationState].NumFrames;
}

static void RobotWalkForwardFunction(void)
{
//This function loops back to the beginning, and timing is based on distance.
   RLValue dummy=RobotAnimations[RobotAnimationState].Distance;
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);


   if((InputInt&COMMANDVisorBeam))
   {
      LaunchVisorBeam();
   }



   if(RobotDistance>=dummy)
   {
      RobotDistance-=dummy;
      YBPlay3DSound(RobotFootStep, Robotframe);
      StageNumber=0;
   }
   if(RobotDistance>dummy/2 && StageNumber==0)
   {
      YBPlay3DSound(RobotFootStep, Robotframe);
      StageNumber=1;
   }
   RobotAnimationFrame=RLMultiply(RLDivide(RobotDistance,dummy),RobotAnimations[RobotAnimationState].NumFrames) +
                 RobotAnimations[RobotAnimationState].StopFrame-RobotAnimations[RobotAnimationState].NumFrames;
   
}

static void RobotJumpFirstFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
//   RobotAnimationFrame+=RLVal(1.0);
   RobotAnimationFrame+=DiffFrame;
   if(RobotAnimationFrame>RobotAnimations[RobotAnimationState].StopFrame)
      RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
}
static void RobotJumpFreezeFunction(void)
{
//This function keeps the frame frozen at the appropriate frame.
   RLVector dir, pos;
   RLVector up;
   RLVector newdir;
   RLFrame scene = RLFrameGetScene(Robotframe);
   RLFrameGetOrientation(Robotframe,scene,&dir,&up);
   RLFrameGetPosition(Robotframe,scene,&pos);

   if((InputInt&COMMANDVisorBeam))
   {
      LaunchVisorBeam();
   }

//This function keeps the frame frozen at the appropriate frame.
   if( (InputInt&COMMANDLeft) && !(InputInt&COMMANDRight) )
   {
      RobotTurning=1;
	  if(RobotTheta>0)
	  {
		  RobotTheta = -RobotTurnAcceleration;
	  }
	  else
	  {
		  RobotTheta -=(RLMultiply(DiffFrame,RobotTurnAcceleration));
	  }
	  if(RobotTheta< -RobotTurnMaximum)
	  {
		  RobotTheta = -RobotTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(Robotframe,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLMultiply(-RobotTurnRate,DIFFRAME));
   }
   else if( (InputInt&COMMANDRight)  &&!(InputInt&COMMANDLeft) )
   {
      RobotTurning=-1;
	  if(RobotTheta<0)
	  {
		  RobotTheta = RobotTurnAcceleration;
	  }
	  else
	  {
		  RobotTheta += (RLMultiply(DiffFrame,RobotTurnAcceleration));
	  }
	  if(RobotTheta > RobotTurnMaximum)
	  {
		  RobotTheta = RobotTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(Robotframe,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLMultiply(RobotTurnRate,DIFFRAME));
   }
   else
   {
      RobotTurning=0;
	  RobotTheta = 0;
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLVal(0));
   }
   

   RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
}

static void RobotJumpLastFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
   if(RobotAnimationFrame>RobotAnimations[RobotAnimationState].StopFrame)
      RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
}

static void RobotJumpStopFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
}

static void RobotAcrobatic1Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
//printf("I'm in Robotacrobatic function, frame = %d\n",RobotAnimationFrame);
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
//printf("I'm leaving Robotacrobatic function, frame = %d\n",RobotAnimationFrame);
}

static void RobotAcrobatic1EndFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
}

static void RobotAcrobatic1DontEndFunction(void)
{
//This function remains still, because Pore Judd Is Daid.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
}

static void RobotAcrobatic2Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
//printf("I'm in Robotacrobatic function, frame = %d\n",RobotAnimationFrame);
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
//printf("I'm leaving Robotacrobatic function, frame = %d\n",RobotAnimationFrame);
}

static void RobotAcrobatic2EndFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
}
static void RobotAcrobatic2DontEndFunction(void)
{
//This function remains still, because Pore Judd Is Daid.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
}

static void RobotSkidFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
   if(RobotAnimationFrame>RobotAnimations[RobotAnimationState].StopFrame)
      RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
   
}


static void RobotTravelForwardFunction(void)
{
//This is the function for when you loop back to yourself automatically,
//and the timing is incremented automatically as time goes by.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   if((InputInt&COMMANDVisorBeam))
   {
      LaunchVisorBeam();
   }

   RobotAnimationFrame+=DiffFrame;
   if(RobotAnimationFrame>=RobotAnimations[RobotAnimationState].StopFrame)
   {
      RobotAnimationFrame-=RobotAnimations[RobotAnimationState].NumFrames;
//   YBPlay3DSound(RobotJets, Robotframe);
   }
}


/*
static StateFunction RobotTravelBackFunction = RobotTravelForwardFunction;
static StateFunction RobotTravelLeftFunction = RobotTravelForwardFunction;
static StateFunction RobotTravelRightFunction = RobotTravelForwardFunction;
*/
static void RobotTravelBackFunction(void)
{
//This function loops back to the beginning, and timing is based on distance.
   RLValue dummy=RobotAnimations[RobotAnimationState].Distance;
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame=RLMultiply(RLDivide(RobotDistance,dummy),RobotAnimations[RobotAnimationState].NumFrames) +
                 RobotAnimations[RobotAnimationState].StopFrame-RobotAnimations[RobotAnimationState].NumFrames;
}
static void RobotTravelLeftFunction(void)
{
//This function loops back to the beginning, and timing is based on distance.
   RLValue dummy=RobotAnimations[RobotAnimationState].Distance;
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame=RLMultiply(RLDivide(RobotDistance,dummy),RobotAnimations[RobotAnimationState].NumFrames) +
                 RobotAnimations[RobotAnimationState].StopFrame-RobotAnimations[RobotAnimationState].NumFrames;
}
static void RobotTravelRightFunction(void)
{
//This function loops back to the beginning, and timing is based on distance.
   RLValue dummy=RobotAnimations[RobotAnimationState].Distance;
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame=RLMultiply(RLDivide(RobotDistance,dummy),RobotAnimations[RobotAnimationState].NumFrames) +
                 RobotAnimations[RobotAnimationState].StopFrame-RobotAnimations[RobotAnimationState].NumFrames;
}

static void RobotIntoIntoRunFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   if((InputInt&COMMANDVisorBeam))
   {
      LaunchVisorBeam();
   }

   RobotAnimationFrame+=DiffFrame;
}

static void RobotIntoRunFunction(void)
{
//This is the function for when you loop back to yourself automatically,
//and the timing is incremented automatically as time goes by.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   if((InputInt&COMMANDVisorBeam))
   {
      LaunchVisorBeam();
   }

   RobotAnimationFrame+=DiffFrame;
   if(RobotAnimationFrame>=RobotAnimations[RobotAnimationState].StopFrame)
      RobotAnimationFrame-=RobotAnimations[RobotAnimationState].NumFrames;
}


static void RobotRunFunction(void)
{
//This function loops back to the beginning, and timing is based on distance.
   RLValue dummy=RobotAnimations[RobotAnimationState].Distance;
   if((InputInt&COMMANDVisorBeam))
   {
      LaunchVisorBeam();
   }

   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   if(RobotDistance>=dummy)
   {
      RobotDistance-=dummy;
      YBPlay3DSound(RobotFootStep, Robotframe);
      StageNumber=0;
   }
   if(RobotDistance>dummy/2 && StageNumber==0)
   {
      YBPlay3DSound(RobotFootStep, Robotframe);
      StageNumber=1;
   }
   RobotAnimationFrame=RLMultiply(RLDivide(RobotDistance,dummy),RobotAnimations[RobotAnimationState].NumFrames) +
                 RobotAnimations[RobotAnimationState].StopFrame-RobotAnimations[RobotAnimationState].NumFrames;
   
}

static void RobotHighAttack1Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
//This is the Robot's homing missile attack.
   RLFrame WhereIsIt=RobotSwordSpots[RobotLeftSword].position;
   RLFrame Scene=RLFrameGetScene(WhereIsIt);
   RLVector position;
   RLVector dir;
   RLVector up;
   int go=0;
switch(GameStates.CurrentRobot)
{
   case SabreRobot:
   if(RobotAnimationFrame>=RLVal(13.5) && StageNumber==0 )
   {
      if(HomerOnScreen)
	     StageNumber=1;
      else
	  {
	      if(RobotAnimationFrame>RLVal(16))
		  {
		     RobotAnimationFrame=RLVal(16);
	         RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
		  }

		  go=1;
		  StageNumber=1;
		  RLFrameAddChild(Scene,Robotspew);
		  RLFrameGetPosition(WhereIsIt,Scene,&position);
		  RLFrameSetPosition(Robotspew,Scene,position.x,position.y,position.z);
		  RLFrameGetOrientation(Robotframe, Scene, &Robotspewvelocity, &up);
		  Robotspewvelocity.y=0;
		  RLFrameSetOrientation(Robotspew,Scene,Robotspewvelocity.x,Robotspewvelocity.y,Robotspewvelocity.z,up.x,up.y,up.z);

		  RLFrameSetRotation(Robotspew, Robotspew, 0, 1, 0,  RLVal(0.7));
	  }
   }
   break;
   case KataRobot:
   if(RobotAnimationFrame>=RLVal(12.0)&& StageNumber==0)
   {
      if(HomerOnScreen)
	     StageNumber=1;
      else
	  {
	      if(RobotAnimationFrame>RLVal(12))
		  {
		     RobotAnimationFrame=RLVal(12);
	         RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
		  }
		  RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
		  RLFrameGetOrientation(WhereIsIt,Scene,&dir, &up);
		  StageNumber=1;
	      go=1;
		  RLFrameAddChild(Scene,Robotspew);
		  RLFrameGetPosition(WhereIsIt,Scene,&position);
		  RLFrameSetPosition(Robotspew,Scene,position.x,position.y,position.z);
		  RLFrameGetOrientation(Robotframe, Scene, &Robotspewvelocity, &up);
		  Robotspewvelocity.y=0;
		  RLFrameSetOrientation(Robotspew,Scene,Robotspewvelocity.x,Robotspewvelocity.y,Robotspewvelocity.z,up.x,up.y,up.z);

		  RLFrameSetRotation(Robotspew, Robotspew, 1, 1, 1,  RLVal(0.7));
	  }
   }
   break;
   case StealthRobot:
   if(RobotAnimationFrame>=RLVal(14) && StageNumber==0)
   {
      if(HomerOnScreen)
	     StageNumber=1;
      else
	  {
	      if(RobotAnimationFrame>RLVal(15))
		  {
		     RobotAnimationFrame=RLVal(15);
	         RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
		  }
		  StageNumber=1;
	      go=1;
		  RLFrameAddChild(Scene,Robotspew);
		  RLFrameGetPosition(WhereIsIt,Scene,&position);
		  RLFrameSetPosition(Robotspew,Scene,position.x,position.y,position.z);
		  RLFrameGetOrientation(Robotframe, Scene, &Robotspewvelocity, &up);
		  Robotspewvelocity.y=0;
		  RLFrameSetOrientation(Robotspew,Scene,Robotspewvelocity.x,Robotspewvelocity.y,Robotspewvelocity.z,-Robotspewvelocity.z,Robotspewvelocity.y,Robotspewvelocity.x);

		  RLFrameSetRotation(Robotspew, Robotspew, 1, 0, 0,  RLVal(0.7));
	  } 
   }
   break;
   case KaberRobot:
   if(RobotAnimationFrame>=RLVal(13.5)&& StageNumber==0)
   {
      if(HomerOnScreen)
	     StageNumber=1;
      else
	  {
	      if(RobotAnimationFrame>RLVal(16))
		  {
		     RobotAnimationFrame=RLVal(16);
	         RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
		  }
		  StageNumber=1;
	      go=1;
		  RLFrameAddChild(Scene,Robotspew);
		  RLFrameGetPosition(WhereIsIt,Scene,&position);
		  RLFrameSetPosition(Robotspew,Scene,position.x,position.y,position.z);
		  RLFrameGetOrientation(Robotframe, Scene, &Robotspewvelocity, &up);
		  Robotspewvelocity.y=0;
		  RLFrameSetOrientation(Robotspew,Scene,Robotspewvelocity.x,Robotspewvelocity.y,Robotspewvelocity.z,up.x,up.y,up.z);

		  RLFrameSetRotation(Robotspew, Robotspew, 0, 0, 1,  RLVal(0.5));
	  }
   }
   break;
   case MerRobot:
   if(RobotAnimationFrame>=RLVal(13.5)&& StageNumber==0)
   {
      if(HomerOnScreen)
	     StageNumber=1;
      else
	  {
	     if(RobotAnimationFrame>RLVal(16))
		 {
		    RobotAnimationFrame=RLVal(16);
	        RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
		 }
		 StageNumber=1;
	     go=1;
		  RLFrameAddChild(Scene,Robotspew);
		  RLFrameGetPosition(WhereIsIt,Scene,&position);
		  RLFrameSetPosition(Robotspew,Scene,position.x,position.y,position.z);
		  RLFrameGetOrientation(Robotframe, Scene, &Robotspewvelocity, &up);
		  Robotspewvelocity.y=0;
//		  RLFrameSetOrientation(Robotspew,Scene,Robotspewvelocity.x,Robotspewvelocity.y,Robotspewvelocity.z,up.x,up.y,up.z);
		  RLFrameSetOrientation(Robotspew,Scene,Robotspewvelocity.z,Robotspewvelocity.y,-Robotspewvelocity.x,up.x,up.y,up.z);

		 RLFrameSetRotation(Robotspew, Robotspew, 1, 0, 0,  RLVal(0.3));
	  }
   }
   break;
}
   if(go)
   {

      RobotHomerData.ProjectedPosition.x=position.x;
      RobotHomerData.ProjectedPosition.y=position.y;
      RobotHomerData.ProjectedPosition.z=position.z;
      

	  RLVectorNormalise(&Robotspewvelocity);
	  Robotspewvelocity.x*=HomingMissileSpeed;
	  Robotspewvelocity.z*=HomingMissileSpeed;

      RobotHomerData.CurrentPosition.x=position.x-Robotspewvelocity.x;
      RobotHomerData.CurrentPosition.y=position.y;
      RobotHomerData.CurrentPosition.z=position.z-Robotspewvelocity.z;

      HomerHowLong=HomerDuration;
      HomerOnScreen=1;
      RobotHomerData.RemoveMeFlag=0;
      RobotHomerData.collisionflag=0;
	  RobotHomerData.DamageICause=HomerDamage;

      AddMovingObject(&RobotHomerData);

      YBPlay3DSound(RobotShoot, Robotframe);
   }
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
}

static void RobotMediumAttack1Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
switch(GameStates.CurrentRobot)
{
   case SabreRobot:
      if(RobotAnimationFrame<= RLVal(34))
      {
         RobotData.NumOffensiveTubes=2;
         RobotData.OffensiveTubeList[0]=&(RobotSwordSpots[RobotLeftSword]);
         RobotData.OffensiveTubeList[1]=&(RobotSwordSpots[RobotRightSword]);
         RobotData.DamageICause=MediumAttack1Ferocity ;

//         RobotSwordSpots[RobotLeftSword].NumPoints=2;
//         RobotSwordSpots[RobotRightSword].NumPoints=2;
      }
      else
      {
         RobotData.NumOffensiveTubes=0;
         RobotData.OffensiveTubeList[0]=NULL;
         RobotData.OffensiveTubeList[1]=NULL;
         RobotData.DamageICause=0 ;
//         RobotSwordSpots[RobotLeftSword].NumPoints=0;
//         RobotSwordSpots[RobotRightSword].NumPoints=0;
      }
   break;
   case KataRobot:
      if(RobotAnimationFrame<= RLVal(34))
      {
         RobotData.NumOffensiveTubes=1;
         RobotData.OffensiveTubeList[0]=&(RobotSwordSpots[RobotLeftSword]);
         RobotData.DamageICause=MediumAttack1Ferocity ;
//         RobotSwordSpots[RobotLeftSword].NumPoints=2;
      }
      else
      {
         RobotData.NumOffensiveTubes=0;
         RobotData.OffensiveTubeList[0]=NULL;
         RobotData.OffensiveTubeList[1]=NULL;
         RobotData.DamageICause=0;
//         RobotSwordSpots[RobotLeftSword].NumPoints=0;
//         RobotSwordSpots[RobotRightSword].NumPoints=0;
      }
   break;
   case StealthRobot:
      if(RobotAnimationFrame<= RLVal(39))
      {
         RobotData.NumOffensiveTubes=1;
         RobotData.OffensiveTubeList[0]=&(RobotSwordSpots[RobotRightSword]);
         RobotData.DamageICause=MediumAttack1Ferocity ;
//         RobotSwordSpots[RobotRightSword].NumPoints=2;
      }
      else
      {
         RobotData.NumOffensiveTubes=0;
         RobotData.OffensiveTubeList[0]=NULL;
         RobotData.OffensiveTubeList[1]=NULL;
         RobotData.DamageICause=0;
//         RobotSwordSpots[RobotLeftSword].NumPoints=0;
//         RobotSwordSpots[RobotRightSword].NumPoints=0;
      }
   break;
   case KaberRobot:
      if(RobotAnimationFrame<= RLVal(34))
      {
         RobotData.NumOffensiveTubes=1;
         RobotData.OffensiveTubeList[0]=&(RobotSwordSpots[RobotRightSword]);
         RobotData.DamageICause=MediumAttack1Ferocity ;
//         RobotSwordSpots[RobotRightSword].NumPoints=2;
      }
      else
      {
         RobotData.NumOffensiveTubes=0;
         RobotData.OffensiveTubeList[0]=NULL;
         RobotData.OffensiveTubeList[1]=NULL;
         RobotData.DamageICause=0;
//         RobotSwordSpots[RobotLeftSword].NumPoints=0;
//         RobotSwordSpots[RobotRightSword].NumPoints=0;
      }
   break;
   case MerRobot:
      if(RobotAnimationFrame<= RLVal(35))
      {
         RobotData.NumOffensiveTubes=1;
         RobotData.OffensiveTubeList[0]=&(RobotSwordSpots[RobotRightSword]);
         RobotData.DamageICause=MediumAttack1Ferocity ;
//         RobotSwordSpots[RobotRightSword].NumPoints=2;
      }
      else
      {
         RobotData.NumOffensiveTubes=0;
         RobotData.OffensiveTubeList[0]=NULL;
         RobotData.OffensiveTubeList[1]=NULL;
         RobotData.DamageICause=0;
//         RobotSwordSpots[RobotLeftSword].NumPoints=0;
//         RobotSwordSpots[RobotRightSword].NumPoints=0;
      }
   break;
}
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
}

static void RobotLowAttack1FirstFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.

   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
}

static void RobotLowAttack1TargetFunction(void)
{
//This function increments if the user gives instructions to go Left,
//and decrements if the user gives the instructions to go Right, and 
//doesn't change if the user gives no instructions.
//It's the Robot's rapid fire attack.
   if(!RFCountDown)
   {
      extern RLVector SixShooterDirection[];
      int i;
      RLFrame WhereIsIt;
      RLFrame Scene;
      RLVector position;
      RLVector dir;
      RLVector newdir;
      RLVector up;
      RFCountDown=RapidFireInterval;

      RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
      for(i=0;i<NumberOfSixShooters;++i)
      {
         if(SixShooter->particles[i]->active==0)
         {
            SixShooter->particles[i]->active=2;
            switch(GameStates.CurrentRobot)
            {
               case SabreRobot:
                  WhereIsIt=RobotSwordSpots[RobotLeftSword].position;
				  Scene=RLFrameGetScene(WhereIsIt);
                  RLFrameGetOrientation(WhereIsIt,Scene,&dir, &up);
                  RLFrameGetPosition(WhereIsIt,Scene,&position);
                  newdir.x=30*dir.x;
                  newdir.y=30*dir.y;
                  newdir.z=30*dir.z;
               break;
               case KataRobot:
                  WhereIsIt=RobotSwordSpots[RobotRightSword].position;
                  Scene=RLFrameGetScene(WhereIsIt);
                  RLFrameGetOrientation(WhereIsIt,Scene,&dir, &up);
                  RLFrameGetPosition(WhereIsIt,Scene,&position);
                  newdir.x=30*dir.x;
                  newdir.y=30*dir.y;
                  newdir.z=30*dir.z;
               break;
               case StealthRobot:
                  WhereIsIt=RobotSwordSpots[RobotRightSword].position;
                  Scene=RLFrameGetScene(WhereIsIt);
                  RLFrameGetOrientation(WhereIsIt,Scene,&dir, &up);
                  RLFrameGetPosition(WhereIsIt,Scene,&position);
                  newdir.x=30*dir.x;
                  newdir.y=30*dir.y;
                  newdir.z=30*dir.z;
               break;
               case KaberRobot:
                  WhereIsIt=RobotSwordSpots[RobotLeftSword].position;
                  Scene=RLFrameGetScene(WhereIsIt);
                  RLFrameGetOrientation(WhereIsIt,Scene,&dir, &up);
                  RLFrameGetPosition(WhereIsIt,Scene,&position);
                  newdir.x=dir.x;
                  newdir.y=dir.y;
                  newdir.z=dir.z;
               break;
               case MerRobot:
                  WhereIsIt=RobotSwordSpots[RobotLeftSword].position;
                  Scene=RLFrameGetScene(WhereIsIt);
                  RLFrameGetOrientation(WhereIsIt,Scene,&dir, &up);
                  RLFrameGetPosition(WhereIsIt,Scene,&position);
                  newdir.x=dir.x;
                  newdir.y=dir.y;
                  newdir.z=dir.z;
               break;
            }
            RLFrameSetPosition(SixShooter->particles[i]->frame,Scene,position.x,position.y,position.z);
            //RLFrameSetOrientation(SixShooter->particles[i]->frame,Scene,
            //newdir.x,newdir.y,newdir.z,
            //up.x,up.y,up.z);
			SixShooterDirection[i].x = newdir.x;
			SixShooterDirection[i].y = newdir.y;
			SixShooterDirection[i].z = newdir.z;
            RapidFireHowLong[i]=RapidFireDuration;  

            RobotRapidFireData[i].ProjectedPosition.x=position.x;
            RobotRapidFireData[i].ProjectedPosition.y=position.y;
            RobotRapidFireData[i].ProjectedPosition.z=position.z;
            RobotRapidFireData[i].CurrentPosition.x=position.x-SixShooterDirection[i].x;
            RobotRapidFireData[i].CurrentPosition.y=position.y-SixShooterDirection[i].y;
            RobotRapidFireData[i].CurrentPosition.z=position.z-SixShooterDirection[i].z;
            RobotRapidFireData[i].RemoveMeFlag=0;
            RobotRapidFireData[i].collisionflag=0;
            RobotRapidFireData[i].DamageICause=RapidFireDamage;
            AddMovingObject(&(RobotRapidFireData[i]));

      YBPlay3DSound(RobotShoot, Robotframe);


            break;
         }
      }
   }
   else 
      RFCountDown--;

   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   if((InputInt&COMMANDRight)&&!(InputInt&COMMANDLeft))
   {
      RobotAnimationFrame+=1;
      if(RobotAnimationFrame>RobotAnimations[RobotAnimationState].StopFrame)
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
   }
   else if((InputInt&COMMANDLeft) && !(InputInt&COMMANDRight))
   {
      RobotAnimationFrame-=1;
      if(RobotAnimationFrame < RobotLowAttack1TargetStartFrame)
         RobotAnimationFrame = RobotLowAttack1TargetStartFrame;
   }
}

static void RobotLowAttack1LastFunction(void)
{
//This function decrements automatically, and doesn't loop when it reaches the beginning.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame-=DiffFrame;
   
}

static void RobotSuperJab1Function(void)
{
//This function should play through the animation as fast as possible without missing out on stuff.
//If it's way too fast, we'll reset it to be slower, eh?  I may just have it play 4 times normal speed.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
switch(GameStates.CurrentRobot)
{
   case SabreRobot:
      if(RobotAnimationFrame<RLVal(6))
      {
//         RobotSwordSpots[RobotRightSword].NumPoints=0;
         RobotAnimationFrame=RLVal(6);
      }
      else if(RobotAnimationFrame<RLVal(8))
      {
//         RobotSwordSpots[RobotRightSword].NumPoints=1;
         RobotAnimationFrame=RLVal(8);
      }
      else if(RobotAnimationFrame==RLVal(8)) 
      {
//         RobotSwordSpots[RobotRightSword].NumPoints=1;
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
      }
      else
      {
//         RobotSwordSpots[RobotRightSword].NumPoints=0;
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame+1;
      }
   break;
   case KataRobot:
      if(RobotAnimationFrame<RLVal(6))
      {
//         RobotSwordSpots[RobotLeftSword].NumPoints=0;
         RobotAnimationFrame=RLVal(6);
      }
      else if(RobotAnimationFrame<RLVal(8))
      {
//         RobotSwordSpots[RobotLeftSword].NumPoints=1;
         RobotAnimationFrame=RLVal(8);
      }
      else if(RobotAnimationFrame==RLVal(8)) 
      {
//         RobotSwordSpots[RobotLeftSword].NumPoints=1;
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
      }
      else
      {
//         RobotSwordSpots[RobotLeftSword].NumPoints=0;
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame+1;
      }
   break;
   case StealthRobot:
      if(RobotAnimationFrame<RLVal(6))
      {
//         RobotSwordSpots[RobotRightSword].NumPoints=0;
         RobotAnimationFrame=RLVal(6);
      }
      else if(RobotAnimationFrame<RLVal(8))
      {
//         RobotSwordSpots[RobotRightSword].NumPoints=1;
         RobotAnimationFrame=RLVal(8);
      }
      else if(RobotAnimationFrame==RLVal(8)) 
      {
//         RobotSwordSpots[RobotRightSword].NumPoints=1;
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
      }
      else
      {
//         RobotSwordSpots[RobotRightSword].NumPoints=0;
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame+1;
      }
   break;
   case KaberRobot:
      if(RobotAnimationFrame<RLVal(6))
      {
//         RobotSwordSpots[RobotLeftSword].NumPoints=0;
         RobotAnimationFrame=RLVal(6);
      }
      else if(RobotAnimationFrame<RLVal(8))
      {
//         RobotSwordSpots[RobotLeftSword].NumPoints=1;
         RobotAnimationFrame=RLVal(8);
      }
      else if(RobotAnimationFrame==RLVal(8)) 
      {
//         RobotSwordSpots[RobotLeftSword].NumPoints=1;
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
      }
      else
      {
//         RobotSwordSpots[RobotLeftSword].NumPoints=0;
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame+1;
      }
   break;
   case MerRobot:
      if(RobotAnimationFrame<RLVal(6))
      {
//         RobotSwordSpots[RobotLeftSword].NumPoints=0;
         RobotAnimationFrame=RLVal(6);
      }
      else if(RobotAnimationFrame<RLVal(8))
      {
//         RobotSwordSpots[RobotLeftSword].NumPoints=1;
         RobotAnimationFrame=RLVal(8);
      }
      else if(RobotAnimationFrame==RLVal(8)) 
      {
//         RobotSwordSpots[RobotLeftSword].NumPoints=1;
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
      }
      else
      {
//         RobotSwordSpots[RobotLeftSword].NumPoints=0;
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame+1;
      }
   break;
}

}

static void RobotMediumAttack2Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.

/*
switch(GameStates.CurrentRobot)
{
   case SabreStyle:
      if(RobotAnimationFrame>=RLVal(21) && RobotAnimationFrame<= RLVal(28))
      {
//         RobotHotSpots[RobotRightFoot].NumPoints=1;
      }
      else
      {
//         RobotHotSpots[RobotRightFoot].NumPoints=0;
      }
   break;
   case KataStyle:
      if(RobotAnimationFrame>=RLVal(14) && RobotAnimationFrame<= RLVal(20))
      {
//         RobotHotSpots[RobotLeftFoot].NumPoints=1;
      }
      else
      {
//         RobotHotSpots[RobotLeftFoot].NumPoints=0;
      }
   break;
   case StealthStyle:
      if(RobotAnimationFrame>=RLVal(15) && RobotAnimationFrame<= RLVal(28))
      {
//         RobotHotSpots[RobotRightFoot].NumPoints=1;
//         RobotHotSpots[RobotLeftFoot].NumPoints=1;
      }
      else
      {
//         RobotHotSpots[RobotRightFoot].NumPoints=0;
//         RobotHotSpots[RobotLeftFoot].NumPoints=1;
      }
   break;
   case KaberStyle:
      if(RobotAnimationFrame>=RLVal(15) && RobotAnimationFrame<= RLVal(20))
      {
//         RobotHotSpots[RobotRightFoot].NumPoints=1;
      }
      else
      {
//         RobotHotSpots[RobotRightFoot].NumPoints=0;
      }
   break;
   case MerStyle:
      if(RobotAnimationFrame>=RLVal(15) && RobotAnimationFrame<= RLVal(25))
      {
//         RobotHotSpots[RobotRightFoot].NumPoints=1;
      }
      else
      {
//         RobotHotSpots[RobotRightFoot].NumPoints=0;
      }
   break;
}
*/
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
}

static void RobotLowAttack2Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
//This function houses the concussion weapon, quite broken for now.
//   int i;
   int go=0;
   RLFrame WhereIsIt;
   RLFrame Scene = RLFrameGetScene(Robotframe);
   RLVector position;
   RLVector DummyPos;
   RLVector DummyDir;
   RLVector DummyUp;
   RLVector dir;
   RLVector newdir;
   RLVector up;
   RLVector newup;
//   FILE *shithead;
   RFCountDown=3;
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   if(StageNumber<NumberOfSixShooters)
   {
      RLFrameGetPosition(Robotframe,Scene,&DummyPos);
      RLFrameGetOrientation(Robotframe,Scene,&DummyDir,&DummyUp);
      switch(GameStates.CurrentRobot)
      {
         case SabreRobot:
            if(RobotAnimationFrame>=25&&RobotAnimationFrame<40)
            {
               go=1;
               WhereIsIt=RobotHotSpots[RobotChest].position;
               Scene=RLFrameGetScene(WhereIsIt);
               RLFrameGetOrientation(WhereIsIt,Scene,&dir, &up);
               RLFrameGetPosition(WhereIsIt,Scene,&position);
               newdir.x=-up.x;
               newdir.y=0;
               newdir.z=-up.z;
               newup.x=-dir.x;
               newup.y=-dir.y;
               newup.z=-dir.z;
            }
         break;
         case KataRobot:
            if(RobotAnimationFrame>=30&&RobotAnimationFrame<45)
            {
               go=1;
               WhereIsIt=RobotSwordSpots[RobotLeftSword].position;
               Scene=RLFrameGetScene(WhereIsIt);
               RLFrameGetOrientation(WhereIsIt,Scene,&dir, &up);
               RLFrameGetPosition(WhereIsIt,Scene,&position);
               newdir.x=-dir.x;
               newdir.y=0;
               newdir.z=-dir.z;
               newup.x=up.x;
               newup.y=up.y;
               newup.z=up.z;
            }
         break;
         case StealthRobot:
            if(RobotAnimationFrame>=20&&RobotAnimationFrame<35)
            {
               go=1;
               WhereIsIt=RobotHotSpots[RobotChest].position;
               Scene=RLFrameGetScene(WhereIsIt);
               RLFrameGetOrientation(WhereIsIt,Scene,&dir, &up);
               RLFrameGetPosition(WhereIsIt,Scene,&position);
               newdir.x=-up.x;
               newdir.y=0;
               newdir.z=-up.z;
               newup.x=-dir.x;
               newup.y=-dir.y;
               newup.z=-dir.z;
            }
         break;
         case KaberRobot:
            if(RobotAnimationFrame>=25&&RobotAnimationFrame<40)
            {
               go=1;
               WhereIsIt=RobotSwordSpots[RobotRightSword].position;
               Scene=RLFrameGetScene(WhereIsIt);
               RLFrameGetOrientation(WhereIsIt,Scene,&dir, &up);
               RLFrameGetPosition(WhereIsIt,Scene,&position);
               newdir.x=dir.x;
               newdir.y=0;
               newdir.z=dir.z;
               newup.x=up.x;
               newup.y=up.y;
               newup.z=up.z;
            }
         break;
         case MerRobot:
            if(RobotAnimationFrame>=25&&RobotAnimationFrame<40)
            {
               go=1;
               WhereIsIt=RobotHotSpots[RobotChest].position;
               Scene=RLFrameGetScene(WhereIsIt);
               RLFrameGetOrientation(WhereIsIt,Scene,&dir, &up);
               RLFrameGetPosition(WhereIsIt,Scene,&position);
               newdir.x=-up.x;
               newdir.y=0;
               newdir.z=-up.z;
               newup.x=-dir.x;
               newup.y=-dir.y;
               newup.z=-dir.z;
            }
         break;
      }
      if(go)
      {
         Cussin->particles[StageNumber]->active=2;
         RLFrameGetOrientation(Robotframe, Scene, &newdir, &newup);
		 RLVectorNormalise(&newdir);
		 newdir.x = -newdir.x;
		 newdir.z = -newdir.z;
		 newdir.y = 0;
         RLFrameSetPosition(Cussin->particles[StageNumber]->frame,Scene,position.x,position.y,position.z);
         RLFrameSetOrientation(Cussin->particles[StageNumber]->frame,Scene,
         newdir.x,newdir.y,newdir.z,
         newup.x,newup.y,newup.z);
         if(StageNumber==0)
         {
            CussinWhichWay.x=newdir.x;
            CussinWhichWay.y=newdir.y;
            CussinWhichWay.z=newdir.z;
            CussinUp.x=newup.x;
            CussinUp.y=newup.y;
            CussinUp.z=newup.z;
         }
         CussinHowLong[StageNumber]=RobotConcussionDuration;  
         RobotCussinData[StageNumber].data=StageNumber;

         RobotCussinData[StageNumber].ProjectedPosition.x=position.x;
         RobotCussinData[StageNumber].ProjectedPosition.y=position.y;
         RobotCussinData[StageNumber].ProjectedPosition.z=position.z;
         RobotCussinData[StageNumber].CurrentPosition.x=position.x-newdir.x;
         RobotCussinData[StageNumber].CurrentPosition.y=position.y-newdir.y;
         RobotCussinData[StageNumber].CurrentPosition.z=position.z-newdir.z;
         RobotCussinData[StageNumber].RemoveMeFlag=0;
         RobotCussinData[StageNumber].collisionflag=0;
         RobotCussinData[StageNumber].DamageICause=ConcussionDamage;
         AddMovingObject(&(RobotCussinData[StageNumber]));
         YBPlay3DSound(RobotShoot, Robotframe);
         StageNumber++;
      }
   }
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
}

static void RobotSuperKick2Function(void)
{
//This function should play through the animation as fast as possible without missing out on stuff.
//If it's way too fast, we'll reset it to be slower, eh?  I may just have it play 4 times normal speed.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
switch(GameStates.CurrentRobot)
{
   case SabreRobot:
      if(RobotAnimationFrame<RLVal(6))
      {
//         RobotHotSpots[RobotRightFoot].NumPoints=0;
         RobotAnimationFrame=RLVal(6);
      }
      else if(RobotAnimationFrame<RLVal(8))
      {
//         RobotHotSpots[RobotRightFoot].NumPoints=1;
         RobotAnimationFrame=RLVal(8);
      }
      else if(RobotAnimationFrame==RLVal(8)) 
      {
//         RobotHotSpots[RobotRightFoot].NumPoints=1;
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
      }
      else
      {
//         RobotHotSpots[RobotRightFoot].NumPoints=0;
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame+1;
      }
   break;
   case KataRobot:
      if(RobotAnimationFrame<RLVal(6))
      {
//         RobotHotSpots[RobotRightFoot].NumPoints=0;
         RobotAnimationFrame=RLVal(6);
      }
      else if(RobotAnimationFrame<RLVal(8))
      {
//         RobotHotSpots[RobotRightFoot].NumPoints=1;
         RobotAnimationFrame=RLVal(8);
      }
      else if(RobotAnimationFrame==RLVal(8)) 
      {
//         RobotHotSpots[RobotRightFoot].NumPoints=1;
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
      }
      else
      {
//         RobotHotSpots[RobotRightFoot].NumPoints=0;
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame+1;
      }
   break;
   case StealthRobot:
      if(RobotAnimationFrame<RLVal(6))
      {
//         RobotHotSpots[RobotLeftFoot].NumPoints=0;
         RobotAnimationFrame=RLVal(6);
      }
      else if(RobotAnimationFrame<RLVal(8))
      {
//         RobotHotSpots[RobotLeftFoot].NumPoints=1;
         RobotAnimationFrame=RLVal(8);
      }
      else if(RobotAnimationFrame==RLVal(8)) 
      {
//         RobotHotSpots[RobotLeftFoot].NumPoints=1;
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
      }
      else
      {
//         RobotHotSpots[RobotLeftFoot].NumPoints=0;
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame+1;
      }
   break;
   case KaberRobot:
      if(RobotAnimationFrame<RLVal(6))
      {
//         RobotHotSpots[RobotLeftFoot].NumPoints=0;
         RobotAnimationFrame=RLVal(6);
      }
      else if(RobotAnimationFrame<RLVal(8))
      {
//         RobotHotSpots[RobotLeftFoot].NumPoints=1;
         RobotAnimationFrame=RLVal(8);
      }
      else if(RobotAnimationFrame==RLVal(8)) 
      {
//         RobotHotSpots[RobotLeftFoot].NumPoints=1;
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
      }
      else
      {
//         RobotHotSpots[RobotLeftFoot].NumPoints=0;
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame+1;
      }
   break;
   case MerRobot:
      if(RobotAnimationFrame<RLVal(6))
      {
//         RobotHotSpots[RobotRightFoot].NumPoints=0;
         RobotAnimationFrame=RLVal(6);
      }
      else if(RobotAnimationFrame<RLVal(8))
      {
//         RobotHotSpots[RobotRightFoot].NumPoints=1;
         RobotAnimationFrame=RLVal(8);
      }
      else if(RobotAnimationFrame==RLVal(8)) 
      {
//         RobotHotSpots[RobotRightFoot].NumPoints=1;
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
      }
      else
      {
//         RobotHotSpots[RobotRightFoot].NumPoints=0;
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame+1;
      }
   break;
}


}

static void RobotJumpAttack1Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
}

static void RobotJumpAttack2Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
}


static void RobotSpecialAttack3Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
}


static void RobotBlockMediumFirstFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
}

static void RobotBlockMediumFreezeFunction(void)
{
//This function keeps the frame frozen at the appropriate frame.
   RLVector dir, pos;
   RLVector up;
   RLVector newdir;
   RLFrame scene = RLFrameGetScene(Robotframe);
   RLFrameGetOrientation(Robotframe,scene,&dir,&up);
   RLFrameGetPosition(Robotframe,scene,&pos);

   if( (InputInt&COMMANDLeft) && !(InputInt&COMMANDRight) )
   {
      RobotTurning=1;
	  if(RobotTheta>0)
	  {
		  RobotTheta = -RobotTurnAcceleration;
	  }
	  else
	  {
		  RobotTheta -=(RLMultiply(DiffFrame,RobotTurnAcceleration));
	  }
	  if(RobotTheta< -RobotTurnMaximum)
	  {
		  RobotTheta = -RobotTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(Robotframe,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLMultiply(-RobotTurnRate,DIFFRAME));
   }
   else if( (InputInt&COMMANDRight)  &&!(InputInt&COMMANDLeft) )
   {
      RobotTurning=-1;
	  if(RobotTheta<0)
	  {
		  RobotTheta = RobotTurnAcceleration;
	  }
	  else
	  {
		  RobotTheta += (RLMultiply(DiffFrame,RobotTurnAcceleration));
	  }
	  if(RobotTheta > RobotTurnMaximum)
	  {
		  RobotTheta = RobotTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(Robotframe,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLMultiply(RobotTurnRate,DIFFRAME));
   }
   else
   {
      RobotTurning=0;
	  RobotTheta = 0;
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLVal(0));
   }




   if(BlockCountDown==0)
   {
      extern int shielddlist;
//      FrameSetQuality(RobotBlockSphere,RLRenderWireframe);
		FlipTextureCoords(shielddlist, 0);
	  RLFrameSetOrientation(RobotBlockSphere,RLFrameGetScene(RobotBlockSphere),
	  	0, 1, 0, 
		0, 0, 1);
      RLFrameSetRotation(RobotBlockSphere,RobotBlockSphere,0,RLVal(0),1,RobotBlockSphereRotation);

   }
   if(BlockCountDown>=0)BlockCountDown--;
   RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
}

static void RobotBlockMediumLastFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
}


static void RobotChestHitLeft2Function(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
}
static void RobotPickUpObjectFirstFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
}

static void RobotPickUpObjectFreezeFunction(void)
{
//This function keeps the frame frozen at the appropriate frame.
   if((InputInt&COMMANDVisorBeam))
   {
      LaunchVisorBeam();
   }
   
   RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
}

static void RobotPickUpObjectLastFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
}

static void RobotThrowObjectFunction(void)
{
//This function increments automatically, and doesn't loop when it reaches the end.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
}

static void RobotTaunt2Function(void)
{
//This function increments automatically, and loops when it reaches the end.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
   if(NumRobotTaunts<RobotNumTaunts)
   {
      if(RobotAnimationFrame>RobotAnimations[RobotAnimationState].StopFrame)
      {
         RobotAnimationFrame-=RobotAnimations[RobotAnimationState].NumFrames;
         NumRobotTaunts++;
      }
   }
   else
   {
      if(RobotAnimationFrame>RobotAnimations[RobotAnimationState].StopFrame)
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
   }
}

static void RobotTaunt1Function(void)
{
//This function increments automatically, and loops when it reaches the end.
   RLAnimationSetSetTime(RobotAnimations[RobotAnimationState].Anisette, RobotAnimationFrame);
   RobotAnimationFrame+=DiffFrame;
      if(RobotAnimationFrame>RobotAnimations[RobotAnimationState].StopFrame)
         RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
}




extern RLError RLLoadXAFAsList(const char* filename,
            size_t*, RLObject**); /* XXX */

void thresh(void)
{
   int i;
//   FILE *shithead;
//   char OutputString[128];
  // sprintf(OutputString,"Animation Number %d\n",RobotAnimationState);
//   OutputDebugString(OutputString);
   RobotEngy-=(DiffFrame*RobotAnimations[RobotAnimationState].EnergyDrain);
   if(RobotEngy>MaxRobotEngy)
   {
      RobotLife+=((RobotEngy-MaxRobotEngy)/RobotEnergyToLifeConversion);
      if(RobotLife>MaxRobotLife) RobotLife=MaxRobotLife;
      RobotEngy=MaxRobotEngy;
   }
   //if(RobotEngy<0) RobotEngy=0;
   (RobotAnimations[RobotAnimationState].WhatToDo)();
//   shithead=fopen("shit.out","a");
//   fprintf(shithead,"Robot animation %d\n",RobotAnimationState);
//   fclose(shithead);

   for(i=0;(i<RobotAnimations[RobotAnimationState].numchanges) ;i++ )
      if(  (RobotAnimations[RobotAnimationState].ChangeList[i]) () )
         break;
}


void GetRobotAnimInfo(FILE *input)
{
#ifdef ErrorsOut
	FILE *errors;
#endif
   char decision[1];
   char movename[64];
   char dumstring[256];
#ifdef ErrorsOut
   errors=fopen("error.out","a");
   fprintf(errors,"getting Robot animation info.\n");
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
            if(!stricmp("RFSpeed",movename))
            {
               fscanf(input," %f",&RFSpeed);
            }
            else if(!stricmp("MediumAttack1Ferocity",movename))
            {
               fscanf(input," %d",&MediumAttack1Ferocity);
            }
            else if(!stricmp("RobotWalkForwardDistance",movename))
            {
               fscanf(input," %f",&RobotWalkForwardDistance);
            }
            else if(!stricmp("RobotIntoRunDistance",movename))
            {
               fscanf(input," %f",&RobotIntoRunDistance);
            }
            else if(!stricmp("RobotRunDistance",movename))
            {
               fscanf(input," %f",&RobotRunDistance);
            }
            else if(!stricmp("RobotWalkBackDistance",movename))
            {
               fscanf(input," %f",&RobotWalkBackDistance);
            }
            else if(!stricmp("RobotSideStepLeftDistance",movename))
            {
               fscanf(input," %f",&RobotSideStepLeftDistance);
            }
            else if(!stricmp("RobotSideStepRightDistance",movename))
            {
               fscanf(input," %f",&RobotSideStepRightDistance);
            }
            else if(!stricmp("RobotAcrobatic1Distance",movename))
            {
               fscanf(input," %f",&RobotAcrobatic1Distance);
            }
            else if(!stricmp("RobotAcrobatic2Distance",movename))
            {
               fscanf(input," %f",&RobotAcrobatic2Distance);
            }
            else if(!stricmp("RobotSkidDistance",movename))
            {
               fscanf(input," %f",&RobotSkidDistance);
            }
            else if(!stricmp("RobotTravelBackDistance",movename))
            {
               fscanf(input," %f",&RobotTravelBackDistance);
            }
            else if(!stricmp("RobotTravelLeftDistance",movename))
            {
               fscanf(input," %f",&RobotTravelLeftDistance);
            }
            else if(!stricmp("RobotTravelRightDistance",movename))
            {
               fscanf(input," %f",&RobotTravelRightDistance);
            }
            else if(!stricmp("RobotKnockDown1Distance",movename))
            {
               fscanf(input," %f",&RobotKnockDown1Distance);
            }
            else if(!stricmp("RobotKnockDown2Distance",movename))
            {
               fscanf(input," %f",&RobotKnockDown2Distance);
            }
            else if(!stricmp("RobotKnockDown3Distance",movename))
            {
               fscanf(input," %f",&RobotKnockDown3Distance);
            }
            else if(!stricmp("RobotPause1EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotPause1EnergyDrain);
            }
            else if(!stricmp("RobotWalkForwardEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotWalkForwardEnergyDrain);
            }
            else if(!stricmp("RobotWalkBackEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotWalkBackEnergyDrain);
            }
            else if(!stricmp("RobotSideStepLeftEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotSideStepLeftEnergyDrain);
            }
            else if(!stricmp("RobotSideStepRightEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotSideStepRightEnergyDrain);
            }
            else if(!stricmp("RobotJumpFirstEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotJumpFirstEnergyDrain);
            }
            else if(!stricmp("RobotJumpFreezeEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotJumpFreezeEnergyDrain);
            }
            else if(!stricmp("RobotJumpLastEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotJumpLastEnergyDrain);
            }
            else if(!stricmp("RobotJumpStopEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotJumpStopEnergyDrain);
            }
            else if(!stricmp("RobotAcrobatic1EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotAcrobatic1EnergyDrain);
            }
            else if(!stricmp("RobotAcrobatic1EndEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotAcrobatic1EndEnergyDrain);
            }
            else if(!stricmp("RobotAcrobatic2EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotAcrobatic2EnergyDrain);
            }
            else if(!stricmp("RobotAcrobatic2EndEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotAcrobatic2EndEnergyDrain);
            }
            else if(!stricmp("RobotSkidEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotSkidEnergyDrain);
            }
            else if(!stricmp("RobotTravelForwardEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotTravelForwardEnergyDrain);
            }
            else if(!stricmp("RobotTravelBackEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotTravelBackEnergyDrain);
            }
            else if(!stricmp("RobotTravelLeftEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotTravelLeftEnergyDrain);
            }
            else if(!stricmp("RobotTravelRightEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotTravelRightEnergyDrain);
            }
            else if(!stricmp("RobotIntoIntoRunEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotIntoIntoRunEnergyDrain);
            }
            else if(!stricmp("RobotIntoRunEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotIntoRunEnergyDrain);
            }
            else if(!stricmp("RobotRunEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotRunEnergyDrain);
            }
            else if(!stricmp("RobotHighAttack1EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotHighAttack1EnergyDrain);
            }
            else if(!stricmp("RobotMediumAttack1EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotMediumAttack1EnergyDrain);
            }
            else if(!stricmp("RobotLowAttack1FirstEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotLowAttack1FirstEnergyDrain);
            }
            else if(!stricmp("RobotLowAttack1TargetEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotLowAttack1TargetEnergyDrain);
            }
            else if(!stricmp("RobotLowAttack1LastEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotLowAttack1LastEnergyDrain);
            }
            else if(!stricmp("RobotSuperJab1EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotSuperJab1EnergyDrain);
            }
            else if(!stricmp("RobotHighAttack2EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotHighAttack2EnergyDrain);
            }
            else if(!stricmp("RobotMediumAttack2EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotMediumAttack2EnergyDrain);
            }
            else if(!stricmp("RobotLowAttack2EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotLowAttack2EnergyDrain);
            }
            else if(!stricmp("RobotSuperKick2EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotSuperKick2EnergyDrain);
            }
            else if(!stricmp("RobotJumpAttack1EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotJumpAttack1EnergyDrain);
            }
            else if(!stricmp("RobotJumpAttack2EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotJumpAttack2EnergyDrain);
            }
            else if(!stricmp("RobotSpecialAttack1EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotSpecialAttack1EnergyDrain);
            }
            else if(!stricmp("RobotSpecialAttack2EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotSpecialAttack2EnergyDrain);
            }
            else if(!stricmp("RobotSpecialAttack3EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotSpecialAttack3EnergyDrain);
            }
            else if(!stricmp("RobotBlockMediumFirstEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotBlockMediumFirstEnergyDrain);
            }
            else if(!stricmp("RobotBlockMediumFreezeEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotBlockMediumFreezeEnergyDrain);
            }
            else if(!stricmp("RobotBlockMediumLastEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotBlockMediumLastEnergyDrain);
            }
            else if(!stricmp("RobotChestHitLeft2EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotChestHitLeft2EnergyDrain);
            }
            else if(!stricmp("RobotPickUpObjectFirstEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotPickUpObjectFirstEnergyDrain);
            }
            else if(!stricmp("RobotPickUpObjectFreezeEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotPickUpObjectFreezeEnergyDrain);
            }
            else if(!stricmp("RobotPickUpObjectLastEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotPickUpObjectLastEnergyDrain);
            }
            else if(!stricmp("RobotThrowObjectEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotThrowObjectEnergyDrain);
            }
            else if(!stricmp("RobotTaunt2EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotTaunt2EnergyDrain);
            }
            else if(!stricmp("RobotPause1EnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotPause1EnergyMinimum);
            }
            else if(!stricmp("RobotWalkForwardEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotWalkForwardEnergyMinimum);
            }
            else if(!stricmp("RobotWalkBackEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotWalkBackEnergyMinimum);
            }
            else if(!stricmp("RobotSideStepLeftEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotSideStepLeftEnergyMinimum);
            }
            else if(!stricmp("RobotSideStepRightEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotSideStepRightEnergyMinimum);
            }
            else if(!stricmp("RobotJumpFirstEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotJumpFirstEnergyMinimum);
            }
            else if(!stricmp("RobotJumpFreezeEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotJumpFreezeEnergyMinimum);
            }
            else if(!stricmp("RobotJumpLastEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotJumpLastEnergyMinimum);
            }
            else if(!stricmp("RobotJumpStopEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotJumpStopEnergyMinimum);
            }
            else if(!stricmp("RobotAcrobatic1EnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotAcrobatic1EnergyMinimum);
            }
            else if(!stricmp("RobotAcrobatic1EndEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotAcrobatic1EndEnergyMinimum);
            }
            else if(!stricmp("RobotAcrobatic2EnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotAcrobatic2EnergyMinimum);
            }
            else if(!stricmp("RobotAcrobatic2EndEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotAcrobatic2EndEnergyMinimum);
            }
            else if(!stricmp("RobotSkidEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotSkidEnergyMinimum);
            }
            else if(!stricmp("RobotTravelForwardEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotTravelForwardEnergyMinimum);
            }
            else if(!stricmp("RobotTravelBackEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotTravelBackEnergyMinimum);
            }
            else if(!stricmp("RobotTravelLeftEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotTravelLeftEnergyMinimum);
            }
            else if(!stricmp("RobotTravelRightEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotTravelRightEnergyMinimum);
            }
            else if(!stricmp("RobotIntoIntoRunEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotIntoIntoRunEnergyMinimum);
            }
            else if(!stricmp("RobotIntoRunEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotIntoRunEnergyMinimum);
            }
            else if(!stricmp("RobotRunEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotRunEnergyMinimum);
            }
            else if(!stricmp("RobotHighAttack1EnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotHighAttack1EnergyMinimum);
            }
            else if(!stricmp("RobotMediumAttack1EnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotMediumAttack1EnergyMinimum);
            }
            else if(!stricmp("RobotLowAttack1FirstEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotLowAttack1FirstEnergyMinimum);
            }
            else if(!stricmp("RobotLowAttack1TargetEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotLowAttack1TargetEnergyMinimum);
            }
            else if(!stricmp("RobotLowAttack1LastEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotLowAttack1LastEnergyMinimum);
            }
            else if(!stricmp("RobotSuperJab1EnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotSuperJab1EnergyMinimum);
            }
            else if(!stricmp("RobotHighAttack2EnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotHighAttack2EnergyMinimum);
            }
            else if(!stricmp("RobotMediumAttack2EnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotMediumAttack2EnergyMinimum);
            }
            else if(!stricmp("RobotLowAttack2EnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotLowAttack2EnergyMinimum);
            }
            else if(!stricmp("RobotSuperKick2EnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotSuperKick2EnergyMinimum);
            }
            else if(!stricmp("RobotJumpAttack1EnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotJumpAttack1EnergyMinimum);
            }
            else if(!stricmp("RobotJumpAttack2EnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotJumpAttack2EnergyMinimum);
            }
            else if(!stricmp("RobotSpecialAttack1EnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotSpecialAttack1EnergyMinimum);
            }
            else if(!stricmp("RobotSpecialAttack2EnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotSpecialAttack2EnergyMinimum);
            }
            else if(!stricmp("RobotSpecialAttack3EnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotSpecialAttack3EnergyMinimum);
            }
            else if(!stricmp("RobotBlockMediumFirstEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotBlockMediumFirstEnergyMinimum);
            }
            else if(!stricmp("RobotBlockMediumFreezeEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotBlockMediumFreezeEnergyMinimum);
            }
            else if(!stricmp("RobotBlockMediumLastEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotBlockMediumLastEnergyMinimum);
            }
            else if(!stricmp("RobotChestHitLeft2EnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotChestHitLeft2EnergyMinimum);
            }
            else if(!stricmp("RobotPickUpObjectFirstEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotPickUpObjectFirstEnergyMinimum);
            }
            else if(!stricmp("RobotPickUpObjectFreezeEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotPickUpObjectFreezeEnergyMinimum);
            }
            else if(!stricmp("RobotPickUpObjectLastEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotPickUpObjectLastEnergyMinimum);
            }
            else if(!stricmp("RobotThrowObjectEnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotThrowObjectEnergyMinimum);
            }
            else if(!stricmp("RobotTaunt2EnergyMinimum",movename))
            {
               fscanf(input," %d",&RobotTaunt2EnergyMinimum);
            }
            else if(!stricmp("RobotBlockSphereHeight",movename))
            {
               fscanf(input," %f",&RobotBlockSphereHeight);
            }
            else if(!stricmp("RobotBlockSphereRotation",movename))
            {
               fscanf(input," %f",&RobotBlockSphereRotation);
            }
            else if(!stricmp("PowerUpEnergy",movename))
            {
               fscanf(input," %d",&PowerUpEnergy);
            }
            else if(!stricmp("HomerDuration",movename))
            {
               fscanf(input," %d",&HomerDuration);
            }
            else if(!stricmp("HomerDamage",movename))
            {
               fscanf(input," %d",&HomerDamage);
            }
            else if(!stricmp("RapidFireInterval",movename))
            {
               fscanf(input," %d",&RapidFireInterval);
            }
            else if(!stricmp("RapidFireDuration",movename))
            {
               fscanf(input," %d",&RapidFireDuration);
            }
            else if(!stricmp("RapidFireDamage",movename))
            {
               fscanf(input," %d",&RapidFireDamage);
            }
            else if(!stricmp("RobotNumTaunts",movename))
            {
               fscanf(input," %d",&RobotNumTaunts);
            }
            else if(!stricmp("RobotEnergyToLifeConversion",movename))
            {
               fscanf(input," %d",&RobotEnergyToLifeConversion);
            }
            else if(!stricmp("InitialRobotLife",movename))
            {
               fscanf(input," %d",&InitialRobotLife);
            }
            else if(!stricmp("RobotTerminalVelocity",movename))
            {
               fscanf(input," %f",&RobotTerminalVelocity);
            }
            else if(!stricmp("ConcussionDamage",movename))
            {
               fscanf(input," %d",&ConcussionDamage);
            }
            else if(!stricmp("HomingMissileSpeed",movename))
            {
               fscanf(input," %f",&HomingMissileSpeed);
            }
            else if(!stricmp("HomerAngle",movename))
            {
               fscanf(input," %f",&HomerAngle);
            }
            else if(!stricmp("HomerCloseEnough",movename))
            {
               fscanf(input," %f",&HomerCloseEnough);
            }
            else if(!stricmp("ConcussionRadius",movename))
            {
               fscanf(input," %f",&ConcussionRadius);
            }
            else if(!stricmp("RobotConcussionDuration",movename))
            {
               fscanf(input," %f",&RobotConcussionDuration);
            }
            else if(!stricmp("RobotConcussionSpeed",movename))
            {
               fscanf(input," %f",&RobotConcussionSpeed);
            }
            else if(!stricmp("RobotConcussionMaxRadius",movename))
            {
               fscanf(input," %f",&RobotConcussionMaxRadius);
            }
            else if(!stricmp("RobotConcussionMinRadius",movename))
            {
               fscanf(input," %f",&RobotConcussionMinRadius);
            }
            else if(!stricmp("RobotArmor",movename))
            {
				extern short  SysDifficulty;
               
               fscanf(input," %f",&RobotArmor);
			   if (SysDifficulty==1) RobotArmor*=2;
			   if (SysDifficulty==3) RobotArmor/=2;
            }
            else if(!stricmp("PeaShooterDamage",movename))
            {
               extern int PeaShooterDamage;
               fscanf(input," %d",&PeaShooterDamage);
            }
            else if(!stricmp("PeaShooterInterval",movename))
            {
               extern int PeaShooterInterval;
               fscanf(input," %d",&PeaShooterInterval);
            }
            else if(!stricmp("PeaShooterDuration",movename))
            {
               extern int PeaShooterDuration;
               fscanf(input," %d",&PeaShooterDuration);
            }

            else if(!stricmp("PeaShooterEnergyDrain",movename))
            {
               fscanf(input," %d",&PeaShooterEnergyDrain);
            }
            else if(!stricmp("PeaShooterEnergyMinimum",movename))
            {
               fscanf(input," %d",&PeaShooterEnergyMinimum);
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



void DefineRobotAnimationConstants()
{
   RobotAnimations[RobotPause1].Distance= RobotPause1Distance;
   RobotAnimations[RobotWalkForward].Distance= RobotWalkForwardDistance;
   RobotAnimations[RobotJumpFirst].Distance= RobotJumpDistance;
   RobotAnimations[RobotJumpFreeze].Distance= RobotJumpDistance;
   RobotAnimations[RobotJumpLast].Distance= RobotJumpDistance;
   RobotAnimations[RobotJumpStop].Distance= RobotJumpDistance;
   RobotAnimations[RobotAcrobatic1].Distance= RobotAcrobatic1Distance;
   RobotAnimations[RobotAcrobatic1End].Distance= RLVal(0);
   RobotAnimations[RobotAcrobatic2].Distance= RobotAcrobatic2Distance;
   RobotAnimations[RobotAcrobatic2End].Distance= 0;
   RobotAnimations[RobotSkid].Distance= RobotSkidDistance;
   RobotAnimations[RobotTravelForward].Distance= RobotTravelForwardDistance;
   RobotAnimations[RobotTravelBack].Distance= RobotTravelBackDistance;
   RobotAnimations[RobotTravelLeft].Distance= RobotTravelLeftDistance;
   RobotAnimations[RobotTravelRight].Distance= RobotTravelRightDistance;
   RobotAnimations[RobotIntoIntoRun].Distance= 0;
   RobotAnimations[RobotIntoRun].Distance= RobotIntoRunDistance;
   RobotAnimations[RobotRun].Distance= RobotRunDistance;
   RobotAnimations[RobotHighAttack1].Distance= RobotHighAttack1Distance;
   RobotAnimations[RobotMediumAttack1].Distance= RobotMediumAttack1Distance;
   RobotAnimations[RobotLowAttack1First].Distance= 0;
   RobotAnimations[RobotLowAttack1Target].Distance= 0;
   RobotAnimations[RobotLowAttack1Last].Distance= 0;
   RobotAnimations[RobotSuperJab1].Distance= RobotLowAttack1Distance;
   RobotAnimations[RobotMediumAttack2].Distance= RobotMediumAttack2Distance;
   RobotAnimations[RobotLowAttack2].Distance= RobotLowAttack2Distance;
   RobotAnimations[RobotSuperKick2].Distance= RobotLowAttack2Distance;
   RobotAnimations[RobotJumpAttack1].Distance= RobotJumpAttack1Distance;
   RobotAnimations[RobotJumpAttack2].Distance= RobotJumpAttack2Distance;
   RobotAnimations[RobotSpecialAttack3].Distance= RobotSpecialAttack3Distance;
   RobotAnimations[RobotBlockMediumFirst].Distance= RobotBlockMediumDistance;
   RobotAnimations[RobotBlockMediumFreeze].Distance= RobotBlockMediumDistance;
   RobotAnimations[RobotBlockMediumLast].Distance= RobotBlockMediumDistance;
   RobotAnimations[RobotChestHitLeft2].Distance= RobotChestHitLeft2Distance;
   RobotAnimations[RobotPickUpObjectFirst].Distance= RobotPickUpObjectDistance;
   RobotAnimations[RobotPickUpObjectFreeze].Distance= RobotPickUpObjectDistance;
   RobotAnimations[RobotPickUpObjectLast].Distance= RobotPickUpObjectDistance;
   RobotAnimations[RobotThrowObject].Distance= RobotThrowObjectDistance;
   RobotAnimations[RobotTaunt2].Distance=RobotTaunt2Distance;
   RobotAnimations[RobotTaunt1].Distance=RobotTaunt1Distance;
   RobotAnimations[RobotPause1].NumFrames = RobotPause1NumFrames;
   RobotAnimations[RobotWalkForward].NumFrames = RobotWalkForwardNumFrames;
   RobotAnimations[RobotJumpFirst].NumFrames = RobotJumpFreezeFrame;
   RobotAnimations[RobotJumpFreeze].NumFrames = RLVal(1);
   RobotAnimations[RobotJumpLast].NumFrames = RobotJumpStopFrame-RobotJumpFreezeFrame;
   RobotAnimations[RobotJumpStop].NumFrames = RobotJumpNumFrames-RobotJumpStopFrame;
   RobotAnimations[RobotAcrobatic1].NumFrames = RobotAcrobatic1StopFrame;
   RobotAnimations[RobotAcrobatic1End].NumFrames = RobotAcrobatic1NumFrames-RobotAcrobatic1StopFrame;
   RobotAnimations[RobotAcrobatic2].NumFrames = RobotAcrobatic2StopFrame;
   RobotAnimations[RobotAcrobatic2End].NumFrames = RobotAcrobatic2NumFrames-RobotAcrobatic2StopFrame;
   RobotAnimations[RobotSkid].NumFrames = RobotSkidNumFrames;
   RobotAnimations[RobotTravelForward].NumFrames = RobotTravelForwardNumFrames;
   RobotAnimations[RobotTravelBack].NumFrames = RobotTravelBackNumFrames;
   RobotAnimations[RobotTravelLeft].NumFrames = RobotTravelLeftNumFrames;
   RobotAnimations[RobotTravelRight].NumFrames = RobotTravelRightNumFrames;
   RobotAnimations[RobotIntoIntoRun].NumFrames = RobotIntoRunStartFrame;
   RobotAnimations[RobotIntoRun].NumFrames = RobotIntoRunNumFrames-RobotIntoRunStartFrame;
   RobotAnimations[RobotRun].NumFrames = RobotRunNumFrames;
   RobotAnimations[RobotHighAttack1].NumFrames = RobotHighAttack1NumFrames;
   RobotAnimations[RobotMediumAttack1].NumFrames = RobotMediumAttack1NumFrames;
   RobotAnimations[RobotLowAttack1First].NumFrames = RobotLowAttack1FirstNumFrames;
   RobotAnimations[RobotLowAttack1Target].NumFrames = RobotLowAttack1TargetNumFrames;
   RobotAnimations[RobotLowAttack1Last].NumFrames = RobotLowAttack1LastNumFrames;
   RobotAnimations[RobotSuperJab1].NumFrames = RLVal(4);
   RobotAnimations[RobotMediumAttack2].NumFrames = RobotMediumAttack2NumFrames;
   RobotAnimations[RobotLowAttack2].NumFrames = RobotLowAttack2NumFrames;
   RobotAnimations[RobotSuperKick2].NumFrames = RLVal(4);
   RobotAnimations[RobotJumpAttack1].NumFrames = RobotJumpAttack1NumFrames;
   RobotAnimations[RobotJumpAttack2].NumFrames = RobotJumpAttack2NumFrames;
   RobotAnimations[RobotSpecialAttack3].NumFrames = RobotSpecialAttack3NumFrames;
   RobotAnimations[RobotBlockMediumFirst].NumFrames = RobotBlockMediumFreezeFrame;
   RobotAnimations[RobotBlockMediumFreeze].NumFrames = RLVal(1);
   RobotAnimations[RobotBlockMediumLast].NumFrames = RobotBlockMediumNumFrames-RobotBlockMediumFreezeFrame;
   RobotAnimations[RobotChestHitLeft2].NumFrames = RobotChestHitLeft2StopFrame;
   RobotAnimations[RobotPickUpObjectFirst].NumFrames = RobotPickUpObjectFreezeFrame;
   RobotAnimations[RobotPickUpObjectFreeze].NumFrames = RLVal(1);
   RobotAnimations[RobotPickUpObjectLast].NumFrames = RobotPickUpObjectNumFrames-RobotPickUpObjectFreezeFrame;
   RobotAnimations[RobotThrowObject].NumFrames = RobotThrowObjectNumFrames;
   RobotAnimations[RobotTaunt2].NumFrames = RobotTaunt1NumFrames;
   RobotAnimations[RobotTaunt1].NumFrames = RobotTaunt1NumFrames;

   RobotAnimations[RobotPause1].StopFrame= RobotPause1NumFrames;
   RobotAnimations[RobotWalkForward].StopFrame= RobotWalkForwardNumFrames;
   RobotAnimations[RobotJumpFirst].StopFrame= RobotJumpFreezeFrame;
   RobotAnimations[RobotJumpFreeze].StopFrame= RobotJumpFreezeFrame;
   RobotAnimations[RobotJumpLast].StopFrame= RobotJumpStopFrame;
   RobotAnimations[RobotJumpStop].StopFrame= RobotJumpNumFrames;
   RobotAnimations[RobotAcrobatic1].StopFrame= RobotAcrobatic1StopFrame;
   RobotAnimations[RobotAcrobatic1End].StopFrame= RobotAcrobatic1NumFrames;
   RobotAnimations[RobotAcrobatic2].StopFrame= RobotAcrobatic2StopFrame;
   RobotAnimations[RobotAcrobatic2End].StopFrame= RobotAcrobatic2NumFrames;
   RobotAnimations[RobotSkid].StopFrame= RobotSkidNumFrames;
   RobotAnimations[RobotTravelForward].StopFrame= RobotTravelForwardNumFrames;
   RobotAnimations[RobotTravelBack].StopFrame= RobotTravelBackNumFrames;
   RobotAnimations[RobotTravelLeft].StopFrame= RobotTravelLeftNumFrames;
   RobotAnimations[RobotTravelRight].StopFrame= RobotTravelRightNumFrames;
   RobotAnimations[RobotIntoIntoRun].StopFrame= RobotIntoRunStartFrame;
   RobotAnimations[RobotIntoRun].StopFrame= RobotIntoRunNumFrames;
   RobotAnimations[RobotRun].StopFrame= RobotRunNumFrames;
   RobotAnimations[RobotHighAttack1].StopFrame= RobotHighAttack1NumFrames;
   RobotAnimations[RobotMediumAttack1].StopFrame= RobotMediumAttack1NumFrames;
   RobotAnimations[RobotLowAttack1First].StopFrame= RobotLowAttack1FirstNumFrames;
   RobotAnimations[RobotLowAttack1Target].StopFrame= RobotLowAttack1TargetStopFrame;
   RobotAnimations[RobotLowAttack1Last].StopFrame= RobotLowAttack1LastStopFrame;
   RobotAnimations[RobotSuperJab1].StopFrame= RobotSuperJab1NumFrames;
   RobotAnimations[RobotMediumAttack2].StopFrame= RobotMediumAttack2NumFrames;
   RobotAnimations[RobotLowAttack2].StopFrame= RobotLowAttack2NumFrames;
   RobotAnimations[RobotSuperKick2].StopFrame= RobotLowAttack2NumFrames;
   RobotAnimations[RobotJumpAttack1].StopFrame= RobotJumpAttack1NumFrames;
   RobotAnimations[RobotJumpAttack2].StopFrame= RobotJumpAttack2NumFrames;
   RobotAnimations[RobotSpecialAttack3].StopFrame= RobotSpecialAttack3NumFrames;
   RobotAnimations[RobotBlockMediumFirst].StopFrame= RobotBlockMediumFreezeFrame;
   RobotAnimations[RobotBlockMediumFreeze].StopFrame= RobotBlockMediumFreezeFrame;
   RobotAnimations[RobotBlockMediumLast].StopFrame= RobotBlockMediumNumFrames;
   RobotAnimations[RobotChestHitLeft2].StopFrame= RobotChestHitLeft2StopFrame;
   RobotAnimations[RobotPickUpObjectFirst].StopFrame= RobotPickUpObjectFreezeFrame;
   RobotAnimations[RobotPickUpObjectFreeze].StopFrame= RobotPickUpObjectFreezeFrame;
   RobotAnimations[RobotPickUpObjectLast].StopFrame= RobotPickUpObjectNumFrames;
   RobotAnimations[RobotThrowObject].StopFrame= RobotThrowObjectNumFrames;
   RobotAnimations[RobotTaunt2].StopFrame=RobotTaunt1NumFrames;
   RobotAnimations[RobotTaunt1].StopFrame=RobotTaunt1NumFrames;

   RobotAnimations[RobotPause1].EnergyDrain=RobotPause1EnergyDrain;
   RobotAnimations[RobotWalkForward].EnergyDrain=RobotWalkForwardEnergyDrain;
   RobotAnimations[RobotJumpFirst].EnergyDrain=RobotJumpFirstEnergyDrain;
   RobotAnimations[RobotJumpFreeze].EnergyDrain=RobotJumpFreezeEnergyDrain;
   RobotAnimations[RobotJumpLast].EnergyDrain=RobotJumpLastEnergyDrain;
   RobotAnimations[RobotJumpStop].EnergyDrain=RobotJumpStopEnergyDrain;
   RobotAnimations[RobotAcrobatic1].EnergyDrain=RobotAcrobatic1EnergyDrain;
   RobotAnimations[RobotAcrobatic1End].EnergyDrain=RobotAcrobatic1EndEnergyDrain;
   RobotAnimations[RobotAcrobatic2].EnergyDrain=RobotAcrobatic2EnergyDrain;
   RobotAnimations[RobotAcrobatic2End].EnergyDrain=RobotAcrobatic2EndEnergyDrain;
   RobotAnimations[RobotSkid].EnergyDrain=RobotSkidEnergyDrain;
   RobotAnimations[RobotTravelForward].EnergyDrain=RobotTravelForwardEnergyDrain;
   RobotAnimations[RobotTravelBack].EnergyDrain=RobotTravelBackEnergyDrain;
   RobotAnimations[RobotTravelLeft].EnergyDrain=RobotTravelLeftEnergyDrain;
   RobotAnimations[RobotTravelRight].EnergyDrain=RobotTravelRightEnergyDrain;
   RobotAnimations[RobotIntoIntoRun].EnergyDrain=RobotIntoIntoRunEnergyDrain;
   RobotAnimations[RobotIntoRun].EnergyDrain=RobotIntoRunEnergyDrain;
   RobotAnimations[RobotRun].EnergyDrain=RobotRunEnergyDrain;
   RobotAnimations[RobotHighAttack1].EnergyDrain=RobotHighAttack1EnergyDrain;
   RobotAnimations[RobotMediumAttack1].EnergyDrain=RobotMediumAttack1EnergyDrain;
   RobotAnimations[RobotLowAttack1First].EnergyDrain=RobotLowAttack1FirstEnergyDrain;
   RobotAnimations[RobotLowAttack1Target].EnergyDrain=RobotLowAttack1TargetEnergyDrain;
   RobotAnimations[RobotLowAttack1Last].EnergyDrain=RobotLowAttack1LastEnergyDrain;
   RobotAnimations[RobotSuperJab1].EnergyDrain=RobotSuperJab1EnergyDrain;
   RobotAnimations[RobotMediumAttack2].EnergyDrain=RobotMediumAttack2EnergyDrain;
   RobotAnimations[RobotLowAttack2].EnergyDrain=RobotLowAttack2EnergyDrain;
   RobotAnimations[RobotSuperKick2].EnergyDrain=RobotSuperKick2EnergyDrain;
   RobotAnimations[RobotJumpAttack1].EnergyDrain=RobotJumpAttack1EnergyDrain;
   RobotAnimations[RobotJumpAttack2].EnergyDrain=RobotJumpAttack2EnergyDrain;
   RobotAnimations[RobotSpecialAttack3].EnergyDrain=RobotSpecialAttack3EnergyDrain;
   RobotAnimations[RobotBlockMediumFirst].EnergyDrain=RobotBlockMediumFirstEnergyDrain;
   RobotAnimations[RobotBlockMediumFreeze].EnergyDrain=RobotBlockMediumFreezeEnergyDrain;
   RobotAnimations[RobotBlockMediumLast].EnergyDrain=RobotBlockMediumLastEnergyDrain;
   RobotAnimations[RobotChestHitLeft2].EnergyDrain=RobotChestHitLeft2EnergyDrain;
   RobotAnimations[RobotPickUpObjectFirst].EnergyDrain=RobotPickUpObjectFirstEnergyDrain;
   RobotAnimations[RobotPickUpObjectFreeze].EnergyDrain=RobotPickUpObjectFreezeEnergyDrain;
   RobotAnimations[RobotPickUpObjectLast].EnergyDrain=RobotPickUpObjectLastEnergyDrain;
   RobotAnimations[RobotThrowObject].EnergyDrain=RobotThrowObjectEnergyDrain;
   RobotAnimations[RobotAcrobatic1DontEnd].EnergyDrain=0;
   RobotAnimations[RobotAcrobatic2DontEnd].EnergyDrain=0;
   RobotAnimations[RobotTaunt2].EnergyDrain=RobotTaunt2EnergyDrain;
   RobotAnimations[RobotTaunt1].EnergyDrain=RobotTaunt1EnergyDrain;

/*   RobotAnimations[RobotPause1].EnergyMinimum=RobotPause1EnergyMinimum;
   RobotAnimations[RobotWalkForward].EnergyMinimum=RobotWalkForwardEnergyMinimum;
   RobotAnimations[RobotJumpFirst].EnergyMinimum=RobotJumpFirstEnergyMinimum;
   RobotAnimations[RobotJumpFreeze].EnergyMinimum=RobotJumpFreezeEnergyMinimum;
   RobotAnimations[RobotJumpLast].EnergyMinimum=RobotJumpLastEnergyMinimum;
   RobotAnimations[RobotJumpStop].EnergyMinimum=RobotJumpStopEnergyMinimum;
   RobotAnimations[RobotAcrobatic1].EnergyMinimum=RobotAcrobatic1EnergyMinimum;
   RobotAnimations[RobotAcrobatic1End].EnergyMinimum=RobotAcrobatic1EndEnergyMinimum;
   RobotAnimations[RobotAcrobatic2].EnergyMinimum=RobotAcrobatic2EnergyMinimum;
   RobotAnimations[RobotAcrobatic2End].EnergyMinimum=RobotAcrobatic2EndEnergyMinimum;
   RobotAnimations[RobotSkid].EnergyMinimum=RobotSkidEnergyMinimum;
   RobotAnimations[RobotTravelForward].EnergyMinimum=RobotTravelForwardEnergyMinimum;
   RobotAnimations[RobotTravelBack].EnergyMinimum=RobotTravelBackEnergyMinimum;
   RobotAnimations[RobotTravelLeft].EnergyMinimum=RobotTravelLeftEnergyMinimum;
   RobotAnimations[RobotTravelRight].EnergyMinimum=RobotTravelRightEnergyMinimum;
   RobotAnimations[RobotIntoIntoRun].EnergyMinimum=RobotIntoIntoRunEnergyMinimum;
   RobotAnimations[RobotIntoRun].EnergyMinimum=RobotIntoRunEnergyMinimum;
   RobotAnimations[RobotRun].EnergyMinimum=RobotRunEnergyMinimum;
   RobotAnimations[RobotHighAttack1].EnergyMinimum=RobotHighAttack1EnergyMinimum;
   RobotAnimations[RobotMediumAttack1].EnergyMinimum=RobotMediumAttack1EnergyMinimum;
   RobotAnimations[RobotLowAttack1].EnergyMinimum=RobotLowAttack1EnergyMinimum;
   RobotAnimations[RobotSuperJab1].EnergyMinimum=RobotSuperJab1EnergyMinimum;
   RobotAnimations[RobotMediumAttack2].EnergyMinimum=RobotMediumAttack2EnergyMinimum;
   RobotAnimations[RobotLowAttack2].EnergyMinimum=RobotLowAttack2EnergyMinimum;
   RobotAnimations[RobotSuperKick2].EnergyMinimum=RobotSuperKick2EnergyMinimum;
   RobotAnimations[RobotJumpAttack1].EnergyMinimum=RobotJumpAttack1EnergyMinimum;
   RobotAnimations[RobotJumpAttack2].EnergyMinimum=RobotJumpAttack2EnergyMinimum;
   RobotAnimations[RobotSpecialAttack3].EnergyMinimum=RobotSpecialAttack3EnergyMinimum;
   RobotAnimations[RobotBlockMediumFirst].EnergyMinimum=RobotBlockMediumFirstEnergyMinimum;
   RobotAnimations[RobotBlockMediumFreeze].EnergyMinimum=RobotBlockMediumFreezeEnergyMinimum;
   RobotAnimations[RobotBlockMediumLast].EnergyMinimum=RobotBlockMediumLastEnergyMinimum;
   RobotAnimations[RobotChestHitLeft2].EnergyMinimum=RobotChestHitLeft2EnergyMinimum;
   RobotAnimations[RobotPickUpObjectFirst].EnergyMinimum=RobotPickUpObjectFirstEnergyMinimum;
   RobotAnimations[RobotPickUpObjectFreeze].EnergyMinimum=RobotPickUpObjectFreezeEnergyMinimum;
   RobotAnimations[RobotPickUpObjectLast].EnergyMinimum=RobotPickUpObjectLastEnergyMinimum;
   RobotAnimations[RobotThrowObject].EnergyMinimum=RobotThrowObjectEnergyMinimum;
*/





/*
RobotAnimations[RobotPause1].
RobotAnimations[RobotPause2].
RobotAnimations[RobotWalkForward].
RobotAnimations[RobotWalkBack].
RobotAnimations[RobotSideStepLeft].
RobotAnimations[RobotSideStepRight].
RobotAnimations[RobotTurnLeftFirst].
RobotAnimations[RobotTurnLeftFreeze].
RobotAnimations[RobotTurnLeftLast].
RobotAnimations[RobotTurnRightFirst].
RobotAnimations[RobotTurnRightFreeze].
RobotAnimations[RobotTurnRightLast].
RobotAnimations[RobotJumpFirst].
RobotAnimations[RobotJumpFreeze].
RobotAnimations[RobotJumpLast].
RobotAnimations[RobotJumpStop].
RobotAnimations[RobotAcrobatic1].
RobotAnimations[RobotAcrobatic1End].
RobotAnimations[RobotAcrobatic2].
RobotAnimations[RobotAcrobatic2End].
RobotAnimations[RobotSkid].
RobotAnimations[RobotTravelForward].
RobotAnimations[RobotTravelBack].
RobotAnimations[RobotTravelLeft].
RobotAnimations[RobotTravelRight].
RobotAnimations[RobotIntoIntoRun].
RobotAnimations[RobotIntoRun].
RobotAnimations[RobotRun].
RobotAnimations[RobotHighAttack1].
RobotAnimations[RobotMediumAttack1].
RobotAnimations[RobotLowAttack1].
RobotAnimations[RobotSuperJab1].
RobotAnimations[RobotHighAttack2].
RobotAnimations[RobotMediumAttack2].
RobotAnimations[RobotLowAttack2].
RobotAnimations[RobotSuperKick2].
RobotAnimations[RobotJumpAttack1].
RobotAnimations[RobotJumpAttack2].
RobotAnimations[RobotSpecialAttack1].
RobotAnimations[RobotSpecialAttack2].
RobotAnimations[RobotSpecialAttack3].
RobotAnimations[RobotBlockHighFirst].
RobotAnimations[RobotBlockHighFreeze].
RobotAnimations[RobotBlockHighLast].
RobotAnimations[RobotBlockMediumFirst].
RobotAnimations[RobotBlockMediumFreeze].
RobotAnimations[RobotBlockMediumLast].
RobotAnimations[RobotBlockLowFirst].
RobotAnimations[RobotBlockLowFreeze].
RobotAnimations[RobotBlockLowLast].
RobotAnimations[RobotHeadHitLeft1].
RobotAnimations[RobotHeadHitRight1].
RobotAnimations[RobotHeadHitLeft2].
RobotAnimations[RobotHeadHitRight2].
RobotAnimations[RobotChestHitLeft1].
RobotAnimations[RobotChestHitRight1].
RobotAnimations[RobotChestHitLeft2].
RobotAnimations[RobotChestHitRight2].
RobotAnimations[RobotLegHitLeft1].
RobotAnimations[RobotLegHitRight1].
RobotAnimations[RobotLegHitLeft2].
RobotAnimations[RobotLegHitRight2].
RobotAnimations[RobotKnockDown1].
RobotAnimations[RobotGetBackUp1].
RobotAnimations[RobotKnockDown2].
RobotAnimations[RobotGetBackUp2].
RobotAnimations[RobotKnockDown3].
RobotAnimations[RobotGetBackUp3].
RobotAnimations[RobotTaunt1].
RobotAnimations[RobotTaunt2].
RobotAnimations[RobotPickUpObjectFirst].
RobotAnimations[RobotPickUpObjectFreeze].
RobotAnimations[RobotPickUpObjectLast].
RobotAnimations[RobotPauseWithObject].
RobotAnimations[RobotThrowObject].
*/
}
int total = 0;

RLAnimationSet LoadAnim(char *filename);    //Sanfo's substitution
extern RLFrame animlocationframe;


// **********************************************************
// Name:		LoadRobotAnimations
//
// Author:	Bruce Abe
//
// Date:		September 26, 1995
//
// Description:	This function loads all the Robot's animations.  
//
// Arguments:	   None
//
// Return:	      1 if successful, 0 if unsuccessful.
//
// Side Effects:	This function also initializes some global variables for
//                the start of the level.  The variables which are 
//                initialized are:
//
//                RobotLastVerticalSpeed
//                RobotEngy
//                MnstEngy
//                RobotLife
//                MnstLife
//                
//
// Notes:		   For a state which uses an animation which has already 
//                been loaded for another state, a pointer to the already
//                loaded animation will be used, instead of reloading the 
//                animation.  If any animation loading fails, this function
//                will abort.
//
// Known restrictions:  None
//
// Error Number:	If an animation can't be loaded, 0 will be returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************


int LoadRobotAnimations()
{

   char anifile[100] = "anm.bin";
    
   //animlocationframe = Robotframe;   //Sanfo add for animation file loading 7.31.96 

   // load packaged animations Sanfo 8.29.96 
   if (!LoadPackedAnimation(ConstructRobotName(GameStates.CurrentRobot,anifile), &TekRobotData))
   {
	   return 0;
   }
	GetRobotObjInfo ((unsigned long int*)TekRobotData);

	LoadModel((char *)ConstructRobotName(GameStates.CurrentRobot, "190.BIN"),Robotframe);
    TekRobotNumAnims = PreprocessPackedAnimation( Robotframe, (unsigned long*)TekRobotData );
    TekRobotAnims = (PackedAnimations *)TekRobotData;
    TekRobotHierarchy = SabreHierarchy;
   
   if(!(RobotAnimations[RobotPause1].Anisette=LoadAnim(RobotPause1FileName)))return 0;
   if(!(RobotAnimations[RobotWalkForward].Anisette=LoadAnim(RobotWalkForwardFileName)))return 0;
   if(!(RobotAnimations[RobotJumpFirst].Anisette=LoadAnim(RobotJumpFileName)))return 0;
   RobotAnimations[RobotJumpFreeze].Anisette=RobotAnimations[RobotJumpFirst].Anisette;
   RobotAnimations[RobotJumpLast].Anisette=RobotAnimations[RobotJumpFirst].Anisette;
   RobotAnimations[RobotJumpStop].Anisette=RobotAnimations[RobotJumpFirst].Anisette;
   if(!(RobotAnimations[RobotAcrobatic1].Anisette=LoadAnim(RobotAcrobatic1FileName)))return 0;
   RobotAnimations[RobotAcrobatic1End].Anisette=RobotAnimations[RobotAcrobatic1].Anisette;
   RobotAnimations[RobotAcrobatic1DontEnd].Anisette=RobotAnimations[RobotAcrobatic1].Anisette;
   if(!(RobotAnimations[RobotAcrobatic2].Anisette=LoadAnim(RobotAcrobatic2FileName)))return 0;
   RobotAnimations[RobotAcrobatic2End].Anisette=RobotAnimations[RobotAcrobatic2].Anisette;
   RobotAnimations[RobotAcrobatic2DontEnd].Anisette=RobotAnimations[RobotAcrobatic2].Anisette;
   if(!(RobotAnimations[RobotSkid].Anisette=LoadAnim(RobotSkidFileName)))return 0;
   if(!(RobotAnimations[RobotTravelForward].Anisette=LoadAnim(RobotTravelForwardFileName)))return 0;
   if(!(RobotAnimations[RobotTravelBack].Anisette=LoadAnim(RobotTravelBackFileName)))return 0;
   if(!(RobotAnimations[RobotTravelLeft].Anisette=LoadAnim(RobotTravelLeftFileName)))return 0;
   if(!(RobotAnimations[RobotTravelRight].Anisette=LoadAnim(RobotTravelRightFileName)))return 0;
   if(!(RobotAnimations[RobotIntoRun].Anisette=LoadAnim(RobotIntoRunFileName)))return 0;
   RobotAnimations[RobotIntoIntoRun].Anisette=RobotAnimations[RobotIntoRun].Anisette;
   if(!(RobotAnimations[RobotRun].Anisette=LoadAnim(RobotRunFileName)))return 0;

   if(!(RobotAnimations[RobotHighAttack1].Anisette=LoadAnim(RobotHighAttack1FileName)))return 0;
   if(!(RobotAnimations[RobotMediumAttack1].Anisette=LoadAnim(RobotMediumAttack1FileName)))return 0;
   if(!(RobotAnimations[RobotLowAttack1First].Anisette=LoadAnim(RobotLowAttack1FileName)))return 0;
   RobotAnimations[RobotLowAttack1Target].Anisette=RobotAnimations[RobotLowAttack1First].Anisette;
   RobotAnimations[RobotLowAttack1Last].Anisette=RobotAnimations[RobotLowAttack1First].Anisette;
   RobotAnimations[RobotSuperJab1].Anisette=RobotAnimations[RobotLowAttack1First].Anisette;
   if(!(RobotAnimations[RobotLowAttack2].Anisette=LoadAnim(RobotLowAttack2FileName)))return 0;
   RobotAnimations[RobotSuperKick2].Anisette=RobotAnimations[RobotLowAttack2].Anisette;
   if(!(RobotAnimations[RobotBlockMediumFirst].Anisette=LoadAnim(RobotBlockMediumFileName)))return 0;
   RobotAnimations[RobotBlockMediumFreeze].Anisette=RobotAnimations[RobotBlockMediumFirst].Anisette;
   RobotAnimations[RobotBlockMediumLast].Anisette=RobotAnimations[RobotBlockMediumFirst].Anisette;
   if(!(RobotAnimations[RobotChestHitLeft2].Anisette=LoadAnim(RobotChestHitLeft2FileName)))return 0;
   if(!(RobotAnimations[RobotPickUpObjectFirst].Anisette=LoadAnim(RobotPickUpObjectFileName)))return 0;
   RobotAnimations[RobotPickUpObjectFreeze].Anisette=RobotAnimations[RobotPickUpObjectFirst].Anisette;
   RobotAnimations[RobotPickUpObjectLast].Anisette=RobotAnimations[RobotPickUpObjectFirst].Anisette;
   if(!(RobotAnimations[RobotTaunt2].Anisette=LoadAnim(RobotTaunt2FileName)))return 0;
   RobotAnimations[RobotTaunt1].Anisette=RobotAnimations[RobotTaunt2].Anisette;
   RobotAnimationState=RobotJumpFreeze;
   RobotAnimationFrame=RobotAnimations[RobotAnimationState].StopFrame;
   RobotLastVerticalSpeed=RobotTerminalVelocity;
   RobotEngy=MaxRobotEngy;
	MnstEngy=MaxMnstEngy;
	RobotLife=InitialRobotLife;
//	MnstLife=InitialMonsterLife;
   return 1;
}    

// **********************************************************
// Name:		ClearRobotAnimations
//
// Author:	Bruce Abe
//
// Date:		September 26, 1995
//
// Description:	This function frees the memory for all animations.
//
// Arguments:	   None
//
// Return:	      1 if successful, 0 if unsuccessful.
//
// Side Effects:	None
//
// Notes:		   If any of the free operations is unsuccessful, the 
//                function will abort.
//                
//
// Known restrictions:  None
//
// Error Number:	If an animation can't be destroyed, 0 will be returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

int ClearRobotAnimations()
{
/*
   if(RLObjectDestroy(RobotAnimations[RobotPause1].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(RobotAnimations[RobotWalkForward].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(RobotAnimations[RobotJumpFirst].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(RobotAnimations[RobotAcrobatic1].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(RobotAnimations[RobotAcrobatic2].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(RobotAnimations[RobotSkid].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(RobotAnimations[RobotTravelForward].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(RobotAnimations[RobotTravelBack].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(RobotAnimations[RobotTravelLeft].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(RobotAnimations[RobotTravelRight].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(RobotAnimations[RobotIntoIntoRun].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(RobotAnimations[RobotRun].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(RobotAnimations[RobotHighAttack1].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(RobotAnimations[RobotMediumAttack1].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(RobotAnimations[RobotLowAttack1First].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(RobotAnimations[RobotLowAttack2].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(RobotAnimations[RobotBlockMediumFirst].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(RobotAnimations[RobotChestHitLeft2].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(RobotAnimations[RobotPickUpObjectFirst].Anisette)!=RLNoError)
      return 0;
   if(RLObjectDestroy(RobotAnimations[RobotTaunt2].Anisette)!=RLNoError)
      return 0;
*/

	//Sanfo 8.30.96 
	free(TekRobotHierarchy->ObjectCoordinates);
	TekRobotHierarchy->ObjectCoordinates = NULL;
    free(TekRobotHierarchy);
	TekRobotHierarchy = NULL;
    free(TekRobotData);  
	TekRobotData = NULL;

    return 1;
}



// **********************************************************
// Name:		InitRobotAnimationEngine
//
// Author:	Bruce Abe
//
// Date:		September 26, 1995
//
// Description:	This function allocates memory for the change lists in 
//                each state of the animation engine, and fills these lists
//                with the proper functions.  It also sets the number of 
//                state change functions, and the state functions for each
//                state.
//
// Arguments:	   None
//
// Return:	      1 if successful, 0 if unsuccessful.
//
// Side Effects:	Allocated memory for change lists.
//
// Notes:		   
//                
//
// Known restrictions:  None
//
// Error Number:	If memory for a change list can't be allocated, 0 will be
//                returned.  This is the only possible error.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

int InitRobotAnimationEngine()
{

   if(RLMalloc((void **)&(RobotAnimations[RobotPause1].ChangeList),14*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotPause1].numchanges=14;
   RobotAnimations[RobotPause1].ChangeList[0]=ToRobotTaunt2;
   RobotAnimations[RobotPause1].ChangeList[1]=ToRobotSpecialAttack3;
   RobotAnimations[RobotPause1].ChangeList[2]=ToRobotJumpFirst;
   RobotAnimations[RobotPause1].ChangeList[3]=ToRobotTravelBack;
   RobotAnimations[RobotPause1].ChangeList[4]=ToRobotTravelLeft;
   RobotAnimations[RobotPause1].ChangeList[5]=ToRobotTravelRight;
   RobotAnimations[RobotPause1].ChangeList[6]=ToRobotIntoIntoRun;
   RobotAnimations[RobotPause1].ChangeList[7]=ToRobotHighAttack1;
   RobotAnimations[RobotPause1].ChangeList[8]=ToRobotMediumAttack1;
   RobotAnimations[RobotPause1].ChangeList[9]=ToRobotLowAttack1First;
//   RobotAnimations[RobotPause1].ChangeList[10]=ToRobotMediumAttack2;
   RobotAnimations[RobotPause1].ChangeList[10]=ToRobotLowAttack2;
   RobotAnimations[RobotPause1].ChangeList[11]=ToRobotBlockMediumFirst;
   RobotAnimations[RobotPause1].ChangeList[12]=ToRobotPickUpObjectFirst;
   RobotAnimations[RobotPause1].ChangeList[13]=ToRobotTaunt1;


   if(RLMalloc((void **)&(RobotAnimations[RobotWalkForward].ChangeList),7*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotWalkForward].numchanges=7;
   RobotAnimations[RobotWalkForward].ChangeList[0]=ToRobotPause1;
   RobotAnimations[RobotWalkForward].ChangeList[1]=ToRobotJumpFirst;
   RobotAnimations[RobotWalkForward].ChangeList[2]=ToRobotSkid;
   RobotAnimations[RobotWalkForward].ChangeList[3]=ToRobotIntoRun;
   RobotAnimations[RobotWalkForward].ChangeList[4]=ToRobotRun;
   RobotAnimations[RobotWalkForward].ChangeList[5]=ToRobotHighAttack1;
   RobotAnimations[RobotWalkForward].ChangeList[6]=ToRobotMediumAttack1;

   if(RLMalloc((void **)&(RobotAnimations[RobotJumpFirst].ChangeList),7*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotJumpFirst].numchanges=7;
   RobotAnimations[RobotJumpFirst].ChangeList[0]=ToRobotJumpFreeze;
   RobotAnimations[RobotJumpFirst].ChangeList[1]=ToRobotJumpLast;
   RobotAnimations[RobotJumpFirst].ChangeList[2]=ToRobotSkid;
   RobotAnimations[RobotJumpFirst].ChangeList[3]=ToRobotWalkForward;
   RobotAnimations[RobotJumpFirst].ChangeList[4]=ToRobotTravelForward;
   RobotAnimations[RobotJumpFirst].ChangeList[5]=ToRobotRun;
   RobotAnimations[RobotJumpFirst].ChangeList[6]=ToRobotSpecialAttack3;

   if(RLMalloc((void **)&(RobotAnimations[RobotJumpFreeze].ChangeList),5*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotJumpFreeze].numchanges=5;
   RobotAnimations[RobotJumpFreeze].ChangeList[0]=ToRobotJumpLast;
   RobotAnimations[RobotJumpFreeze].ChangeList[1]=ToRobotSkid;
   RobotAnimations[RobotJumpFreeze].ChangeList[2]=ToRobotWalkForward;
   RobotAnimations[RobotJumpFreeze].ChangeList[3]=ToRobotTravelForward;   
   RobotAnimations[RobotJumpFreeze].ChangeList[4]=ToRobotRun;

   if(RLMalloc((void **)&(RobotAnimations[RobotJumpLast].ChangeList),5*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotJumpLast].numchanges=5;
   RobotAnimations[RobotJumpLast].ChangeList[0]=ToRobotJumpStop;
   RobotAnimations[RobotJumpLast].ChangeList[1]=ToRobotSkid;
   RobotAnimations[RobotJumpLast].ChangeList[2]=ToRobotWalkForward;
   RobotAnimations[RobotJumpLast].ChangeList[3]=ToRobotTravelForward;   
   RobotAnimations[RobotJumpLast].ChangeList[4]=ToRobotRun;
   
   if(RLMalloc((void **)&(RobotAnimations[RobotJumpStop].ChangeList),6*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotJumpStop].numchanges=6;
   RobotAnimations[RobotJumpStop].ChangeList[0]=ToRobotPause1;
   RobotAnimations[RobotJumpStop].ChangeList[1]=ToRobotWalkForward;
   RobotAnimations[RobotJumpStop].ChangeList[2]=ToRobotSkid;
   RobotAnimations[RobotJumpStop].ChangeList[3]=ToRobotTravelForward;
   RobotAnimations[RobotJumpStop].ChangeList[4]=ToRobotIntoRun;
   RobotAnimations[RobotJumpStop].ChangeList[5]=ToRobotRun;

   if(RLMalloc((void **)&(RobotAnimations[RobotSkid].ChangeList),7*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotSkid].numchanges=7;
   RobotAnimations[RobotSkid].ChangeList[0]=ToRobotPause1;
   RobotAnimations[RobotSkid].ChangeList[1]=ToRobotWalkForward;
   RobotAnimations[RobotSkid].ChangeList[2]=ToRobotJumpFirst;
   RobotAnimations[RobotSkid].ChangeList[3]=ToRobotIntoRun;
   RobotAnimations[RobotSkid].ChangeList[4]=ToRobotRun;
   RobotAnimations[RobotSkid].ChangeList[5]=ToRobotHighAttack1;
   RobotAnimations[RobotSkid].ChangeList[6]=ToRobotMediumAttack1;

   if(RLMalloc((void **)&(RobotAnimations[RobotTravelForward].ChangeList),4*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotTravelForward].numchanges=4;
   RobotAnimations[RobotTravelForward].ChangeList[0]=ToRobotJumpFirst;
   RobotAnimations[RobotTravelForward].ChangeList[1]=ToRobotHighAttack1;
   RobotAnimations[RobotTravelForward].ChangeList[2]=ToRobotMediumAttack1;
   RobotAnimations[RobotTravelForward].ChangeList[3]=ToRobotSkid;

   if(RLMalloc((void **)&(RobotAnimations[RobotTravelBack].ChangeList),3*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotTravelBack].numchanges=3;
   RobotAnimations[RobotTravelBack].ChangeList[0]=ToRobotPause1;
   RobotAnimations[RobotTravelBack].ChangeList[1]=ToRobotHighAttack1;
   RobotAnimations[RobotTravelBack].ChangeList[2]=ToRobotMediumAttack1;

   if(RLMalloc((void **)&(RobotAnimations[RobotTravelLeft].ChangeList),3*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotTravelLeft].numchanges=3;
   RobotAnimations[RobotTravelLeft].ChangeList[0]=ToRobotPause1;
   RobotAnimations[RobotTravelLeft].ChangeList[1]=ToRobotHighAttack1;
   RobotAnimations[RobotTravelLeft].ChangeList[2]=ToRobotMediumAttack1;

   if(RLMalloc((void **)&(RobotAnimations[RobotTravelRight].ChangeList),3*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotTravelRight].numchanges=3;
   RobotAnimations[RobotTravelRight].ChangeList[0]=ToRobotPause1;
   RobotAnimations[RobotTravelRight].ChangeList[1]=ToRobotHighAttack1;
   RobotAnimations[RobotTravelRight].ChangeList[2]=ToRobotMediumAttack1;

   if(RLMalloc((void **)&(RobotAnimations[RobotIntoIntoRun].ChangeList),5*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotIntoIntoRun].numchanges=5;
   RobotAnimations[RobotIntoIntoRun].ChangeList[0]=ToRobotPause1;
   RobotAnimations[RobotIntoIntoRun].ChangeList[1]=ToRobotJumpFirst;
   RobotAnimations[RobotIntoIntoRun].ChangeList[2]=ToRobotIntoRun;
   RobotAnimations[RobotIntoIntoRun].ChangeList[3]=ToRobotHighAttack1;
   RobotAnimations[RobotIntoIntoRun].ChangeList[4]=ToRobotMediumAttack1;
   
   if(RLMalloc((void **)&(RobotAnimations[RobotIntoRun].ChangeList),6*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotIntoRun].numchanges=6;
   RobotAnimations[RobotIntoRun].ChangeList[0]=ToRobotPause1;
   RobotAnimations[RobotIntoRun].ChangeList[1]=ToRobotWalkForward;
   RobotAnimations[RobotIntoRun].ChangeList[2]=ToRobotJumpFirst;
   RobotAnimations[RobotIntoRun].ChangeList[3]=ToRobotSkid;
   RobotAnimations[RobotIntoRun].ChangeList[4]=ToRobotHighAttack1;
   RobotAnimations[RobotIntoRun].ChangeList[5]=ToRobotMediumAttack1;
   
   if(RLMalloc((void **)&(RobotAnimations[RobotRun].ChangeList),7*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotRun].numchanges=7;
   RobotAnimations[RobotRun].ChangeList[0]=ToRobotWalkForward;
   RobotAnimations[RobotRun].ChangeList[1]=ToRobotJumpFirst;
   RobotAnimations[RobotRun].ChangeList[2]=ToRobotSkid;
   RobotAnimations[RobotRun].ChangeList[3]=ToRobotTravelForward;
   RobotAnimations[RobotRun].ChangeList[4]=ToRobotPause1;
   RobotAnimations[RobotRun].ChangeList[5]=ToRobotHighAttack1;
   RobotAnimations[RobotRun].ChangeList[6]=ToRobotMediumAttack1;

   if(RLMalloc((void **)&(RobotAnimations[RobotHighAttack1].ChangeList),2*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotHighAttack1].numchanges=2;
   RobotAnimations[RobotHighAttack1].ChangeList[0]=ToRobotPause1;
   RobotAnimations[RobotHighAttack1].ChangeList[1]=ToRobotSpecialAttack3;

   if(RLMalloc((void **)&(RobotAnimations[RobotMediumAttack1].ChangeList),2*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotMediumAttack1].numchanges=2;
   RobotAnimations[RobotMediumAttack1].ChangeList[0]=ToRobotPause1;
   RobotAnimations[RobotMediumAttack1].ChangeList[1]=ToRobotSpecialAttack3;

   if(RLMalloc((void **)&(RobotAnimations[RobotLowAttack1First].ChangeList),3*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotLowAttack1First].numchanges=3;
   RobotAnimations[RobotLowAttack1First].ChangeList[0]=ToRobotLowAttack1Target;
   RobotAnimations[RobotLowAttack1First].ChangeList[1]=ToRobotLowAttack1Last;
   RobotAnimations[RobotLowAttack1First].ChangeList[2]=ToRobotSpecialAttack3;

   if(RLMalloc((void **)&(RobotAnimations[RobotLowAttack1Target].ChangeList),1*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotLowAttack1Target].numchanges=1;
   RobotAnimations[RobotLowAttack1Target].ChangeList[0]=ToRobotLowAttack1Last;

   if(RLMalloc((void **)&(RobotAnimations[RobotLowAttack1Last].ChangeList),1*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotLowAttack1Last].numchanges=1;
   RobotAnimations[RobotLowAttack1Last].ChangeList[0]=ToRobotPause1;

   if(RLMalloc((void **)&(RobotAnimations[RobotSuperJab1].ChangeList),2*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotSuperJab1].numchanges=2;
   RobotAnimations[RobotSuperJab1].ChangeList[0]=ToRobotPause1;
   RobotAnimations[RobotSuperJab1].ChangeList[1]=ToRobotSpecialAttack3;
//   if(RLMalloc((void **)&(RobotAnimations[RobotMediumAttack2].ChangeList),2*sizeof(StateChange))!=RLNoError)
//      return 0;
//   RobotAnimations[RobotMediumAttack2].numchanges=2;
//   RobotAnimations[RobotMediumAttack2].ChangeList[0]=ToRobotPause1;
//   RobotAnimations[RobotMediumAttack2].ChangeList[1]=ToRobotSpecialAttack3;

   if(RLMalloc((void **)&(RobotAnimations[RobotLowAttack2].ChangeList),2*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotLowAttack2].numchanges=2;
   RobotAnimations[RobotLowAttack2].ChangeList[0]=ToRobotPause1;
   RobotAnimations[RobotLowAttack2].ChangeList[1]=ToRobotSpecialAttack3;

   if(RLMalloc((void **)&(RobotAnimations[RobotSuperKick2].ChangeList),2*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotSuperKick2].numchanges=2;
   RobotAnimations[RobotSuperKick2].ChangeList[0]=ToRobotPause1;
   RobotAnimations[RobotSuperKick2].ChangeList[1]=ToRobotSpecialAttack3;

   if(RLMalloc((void **)&(RobotAnimations[RobotBlockMediumFirst].ChangeList),2*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotBlockMediumFirst].numchanges=2;
   RobotAnimations[RobotBlockMediumFirst].ChangeList[0]=ToRobotBlockMediumFreeze;
   RobotAnimations[RobotBlockMediumFirst].ChangeList[1]=ToRobotBlockMediumLast;

   if(RLMalloc((void **)&(RobotAnimations[RobotBlockMediumLast].ChangeList),2*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotBlockMediumLast].numchanges=2;
   RobotAnimations[RobotBlockMediumLast].ChangeList[0]=ToRobotPause1;
   RobotAnimations[RobotBlockMediumLast].ChangeList[1]=ToRobotBlockMediumFirst;

   if(RLMalloc((void **)&(RobotAnimations[RobotBlockMediumFreeze].ChangeList),1*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotBlockMediumFreeze].numchanges=1;
   RobotAnimations[RobotBlockMediumFreeze].ChangeList[0]=ToRobotBlockMediumLast;

   if(RLMalloc((void **)&(RobotAnimations[RobotPickUpObjectLast].ChangeList),2*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotPickUpObjectLast].numchanges=2;
   RobotAnimations[RobotPickUpObjectLast].ChangeList[0]=ToRobotPause1;
   RobotAnimations[RobotPickUpObjectLast].ChangeList[1]=ToRobotPickUpObjectFirst;
   
   if(RLMalloc((void **)&(RobotAnimations[RobotPickUpObjectFirst].ChangeList),3*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotPickUpObjectFirst].numchanges=3;
   RobotAnimations[RobotPickUpObjectFirst].ChangeList[0]=ToRobotPickUpObjectLast;
   RobotAnimations[RobotPickUpObjectFirst].ChangeList[1]=ToRobotPickUpObjectFreeze;
   RobotAnimations[RobotPickUpObjectFirst].ChangeList[2]=ToRobotSpecialAttack3;

   if(RLMalloc((void **)&(RobotAnimations[RobotPickUpObjectFreeze].ChangeList),1*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotPickUpObjectFreeze].numchanges=1;
   RobotAnimations[RobotPickUpObjectFreeze].ChangeList[0]=ToRobotPickUpObjectLast;
   if(RLMalloc((void **)&(RobotAnimations[RobotChestHitLeft2].ChangeList),sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotChestHitLeft2].numchanges=1;
      RobotAnimations[RobotChestHitLeft2].ChangeList[0]=ToRobotPause1;

   if(RLMalloc((void **)&(RobotAnimations[RobotAcrobatic1].ChangeList),2*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotAcrobatic1].numchanges=2;
   RobotAnimations[RobotAcrobatic1].ChangeList[0]=ToRobotAcrobatic1DontEnd;
   RobotAnimations[RobotAcrobatic1].ChangeList[1]=ToRobotAcrobatic1End;

   if(RLMalloc((void **)&(RobotAnimations[RobotAcrobatic2].ChangeList),2*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotAcrobatic2].numchanges=2;
   RobotAnimations[RobotAcrobatic2].ChangeList[0]=ToRobotAcrobatic2DontEnd;
   RobotAnimations[RobotAcrobatic2].ChangeList[1]=ToRobotAcrobatic2End;

   if(RLMalloc((void **)&(RobotAnimations[RobotAcrobatic1End].ChangeList),1*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotAcrobatic1End].numchanges=1;
   RobotAnimations[RobotAcrobatic1End].ChangeList[0]=ToRobotPause1;

   RobotAnimations[RobotAcrobatic1DontEnd].numchanges=0;
   RobotAnimations[RobotAcrobatic2DontEnd].numchanges=0;

   if(RLMalloc((void **)&(RobotAnimations[RobotAcrobatic2End].ChangeList),1*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotAcrobatic2End].numchanges=1;
   RobotAnimations[RobotAcrobatic2End].ChangeList[0]=ToRobotPause1;

   if(RLMalloc((void **)&(RobotAnimations[RobotSpecialAttack3].ChangeList),1*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotSpecialAttack3].numchanges=1;
   RobotAnimations[RobotSpecialAttack3].ChangeList[0]=ToRobotPause1;

   RobotAnimations[RobotTaunt2].numchanges=0;

   if(RLMalloc((void **)&(RobotAnimations[RobotTaunt1].ChangeList),1*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotAnimations[RobotTaunt1].numchanges=1;
   RobotAnimations[RobotTaunt1].ChangeList[0]=ToRobotPause1;


   RobotAnimations[RobotPause1].WhatToDo=RobotPause1Function;
   RobotAnimations[RobotWalkForward].WhatToDo=RobotWalkForwardFunction;
   RobotAnimations[RobotJumpFirst].WhatToDo=RobotJumpFirstFunction;
   RobotAnimations[RobotJumpFreeze].WhatToDo=RobotJumpFreezeFunction;
   RobotAnimations[RobotJumpLast].WhatToDo=RobotJumpLastFunction;
   RobotAnimations[RobotJumpStop].WhatToDo=RobotJumpStopFunction;
   RobotAnimations[RobotAcrobatic1].WhatToDo=RobotAcrobatic1Function;
   RobotAnimations[RobotAcrobatic1End].WhatToDo=RobotAcrobatic1EndFunction;
   RobotAnimations[RobotAcrobatic1DontEnd].WhatToDo=RobotAcrobatic1DontEndFunction;
   RobotAnimations[RobotAcrobatic2].WhatToDo=RobotAcrobatic2Function;
   RobotAnimations[RobotAcrobatic2End].WhatToDo=RobotAcrobatic2EndFunction;
   RobotAnimations[RobotAcrobatic2DontEnd].WhatToDo=RobotAcrobatic2DontEndFunction;
   RobotAnimations[RobotSkid].WhatToDo=RobotSkidFunction;
   RobotAnimations[RobotTravelForward].WhatToDo=RobotTravelForwardFunction;
   RobotAnimations[RobotTravelBack].WhatToDo=RobotTravelBackFunction;
   RobotAnimations[RobotTravelLeft].WhatToDo=RobotTravelLeftFunction;
   RobotAnimations[RobotTravelRight].WhatToDo=RobotTravelRightFunction;
   RobotAnimations[RobotIntoIntoRun].WhatToDo=RobotIntoIntoRunFunction;
   RobotAnimations[RobotIntoRun].WhatToDo=RobotIntoRunFunction;
   RobotAnimations[RobotRun].WhatToDo=RobotRunFunction;
   RobotAnimations[RobotHighAttack1].WhatToDo=RobotHighAttack1Function;
   RobotAnimations[RobotMediumAttack1].WhatToDo=RobotMediumAttack1Function;
   RobotAnimations[RobotLowAttack1First].WhatToDo=RobotLowAttack1FirstFunction;
   RobotAnimations[RobotLowAttack1Target].WhatToDo=RobotLowAttack1TargetFunction;
   RobotAnimations[RobotLowAttack1Last].WhatToDo=RobotLowAttack1LastFunction;
   RobotAnimations[RobotSuperJab1].WhatToDo=RobotSuperJab1Function;
//   RobotAnimations[RobotMediumAttack2].WhatToDo=RobotMediumAttack2Function;
   RobotAnimations[RobotLowAttack2].WhatToDo=RobotLowAttack2Function;
   RobotAnimations[RobotSuperKick2].WhatToDo=RobotSuperKick2Function;
   RobotAnimations[RobotJumpAttack1].WhatToDo=RobotJumpAttack1Function;
   RobotAnimations[RobotJumpAttack2].WhatToDo=RobotJumpAttack2Function;
   RobotAnimations[RobotSpecialAttack3].WhatToDo=RobotSpecialAttack3Function;
   RobotAnimations[RobotBlockMediumFirst].WhatToDo=RobotBlockMediumFirstFunction;
   RobotAnimations[RobotBlockMediumFreeze].WhatToDo=RobotBlockMediumFreezeFunction;
   RobotAnimations[RobotBlockMediumLast].WhatToDo=RobotBlockMediumLastFunction;
   RobotAnimations[RobotChestHitLeft2].WhatToDo=RobotChestHitLeft2Function;
   RobotAnimations[RobotPickUpObjectFirst].WhatToDo=RobotPickUpObjectFirstFunction;
   RobotAnimations[RobotPickUpObjectFreeze].WhatToDo=RobotPickUpObjectFreezeFunction;
   RobotAnimations[RobotPickUpObjectLast].WhatToDo=RobotPickUpObjectLastFunction;
   RobotAnimations[RobotThrowObject].WhatToDo=RobotThrowObjectFunction;
   RobotAnimations[RobotTaunt2].WhatToDo=RobotTaunt2Function;
   RobotAnimations[RobotTaunt1].WhatToDo=RobotTaunt1Function;


   return 1;

}

// **********************************************************
// Name:		DestroyRobotAnimationEngine
//
// Author:	Bruce Abe
//
// Date:		September 26, 1995
//
// Description:	This function frees all the memory that was allocated
//                for the change lists in the animation engine.  (This is
//                the only memory allocated for the engine.)
//
// Arguments:	   None
//
// Return:	      None
//
// Side Effects:	None
//
// Notes:		   If the number of animation states changes, this function
//                must be changed accordingly.
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************


void DestroyRobotAnimationEngine()
{
   int i;
   for(i=RobotPause1;i<=RobotTaunt1;++i)
   {
      if(RobotAnimations[i].numchanges)
         RLFree(RobotAnimations[i].ChangeList);
   }
}

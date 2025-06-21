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
File:           Robotmov2.c
Author:         Bruce Abe
Date:           9-26-95
Version:        1.01



************************************************************************
REVISION HISTORY        (Add Edits and History to top of list).

Edited By:      Bruce Abe
Edited Date:    11-1-95
Changes:
                Added some typecasting to get rid of bounteous warnings.

Edited By:      Bruce Abe
Edited Date:    10/3/95
Changes:
                changed VERSION_NUMBER from 1.0 to 1.01.
                gave the Robot the ability to be stopped after it
                finishes a skid, which would happen if it throws
                an attack while it's in motion, which continues
                after it skids to a stop.  
                also made the stopped function put the Robot where it 
                was before.  This is a kludge that allows StealthRobot
                to rest on the ground after death.  To get this to work,
                I went through and made sure that RobotPosition is always
                being updated with the correct position every frame.


***********************************************************************/
#pragma warning( disable : 4244)
#define BruceNotSpudde
#ifndef __psx__
#define PC
#endif

#include <string.h>
#ifdef BruceNotSpudde
#define PC
#endif
#include <stdio.h>
#include <stdlib.h>
#ifdef PC
#include <math.h>
#include <time.h>
#endif

//replace rl with rl2d3d.h. By Sanfo 5/18/96
//#include "rl.h"
#include "rl2d3d.h"

#include "keycom.h"
#include "boink.h"
#include "spudbmp.h"
#include "gosys.h"
#include "Robotmove.h"
#include "Robotanim.h"
#include "timing.h"
#include "building.h"
#include "bldgboom.h"
#include "ybsnd.h"
#include "clutter.h"
#include "global.h"
//#ifdef BruceNotSpudde
//FixMapInfo *LevelMap;
//#else
//extern unsigned char* topo;
//#endif
//extern RLFrame monstframe;

extern RLVector RobotFallDownDirection;
RLValue RobotFallDownSpin=10;//this is going to be a number between -10.0 and 10.0.
RLValue RobotSpinMultiplier;
extern int RobotEngy;
extern int MnstEngy;
extern int RobotLife;
extern int MnstLife;
extern long int Population;
extern RLValue sealevel;
//extern const RLValue RotationBy;
extern RLValue MaxHeightDifference;
extern RLFrame Robotframe;
static int RobotNumFramesBackTravel= 5;
static int RobotNumFramesSideTravel= 5;
#define NumFramesAcrobatic 30
#define NumFramesCrouch 15
static RLValue RobotJumpYAcc= 7000/65536.0;
//static int RobotNumJumpLevels= 5;
static RLValue MaxYVel= 36000/65536.0;
RLValue RobotGravity= -1000/65536.0;
RLValue RobotGradientFactor = -0.3;
//static RLValue RobotTurnRate= 3500/65536.0;


//static RLValue RobotCosine=65161/65536.0;
//static RLValue RobotSine=7000/65536.0;
RLValue RobotTheta=RLVal( 0.01335009395037);
RLValue RobotTurnMaximum = RLVal( 0.01335009395037);
RLValue RobotTurnAcceleration = RLVal(0.001335009395037);
//static RLValue RobotSineTable[10];
//static RLValue RobotCosineTable[10];

RLValue RobotMaxFVel1 = 2500/65536.0;
RLValue RobotMaxFVel2 = 5000/65536.0;
RLValue RobotMaxFVel3 = 10000/65536.0;
static RLValue RobotMaxFVel4 = 15000/65536.0;
static RLValue RobotFAcc1 = 500/65536.0;
static RLValue RobotFAcc2 = 1000/65536.0;
static RLValue RobotFAcc3 = 2000/65536.0;
static RLValue RobotFAcc4 = 3000/65536.0;
static RLValue RobotFDecel = -500/65536.0;
static RLValue RobotFBrake = -750/65536.0;

static RLValue RobotMaxBVel1 = 3000/65536.0;
static RLValue RobotMaxBVel2 = 3500/65536.0;
static RLValue RobotMaxBVel3 = 7500/65536.0;
static RLValue RobotBAcc1 = 1000/65536.0;
static RLValue RobotBAcc2 = 1000/65536.0;
static RLValue RobotBAcc3 = 2000/65536.0;
static RLValue RobotBDecel = -500/65536.0;
static RLValue RobotBBrake = -1500/65536.0;

static RLValue RobotMaxRVel1 = 0.05;
static RLValue RobotMaxRVel2 = 0.1;
static RLValue RobotRAcc1 = 0.01;
static RLValue RobotRAcc2 = 0.02;
static RLValue RobotRDecel = -0.015;
static RLValue RobotRBrake = -0.05;

static RLValue RobotMaxLVel1 = 0.05;
static RLValue RobotMaxLVel2 = 0.1;
static RLValue RobotLAcc1 = 0.01;
static RLValue RobotLAcc2 = 0.02;
static RLValue RobotLDecel = -0.015;
static RLValue RobotLBrake = -0.05;
static RLValue RobotKnockBackSpeed = RLVal(0.07);

static int RobotWaitingEnergyDrain=0;
static int RobotFAccelerating1EnergyDrain=0;
static int RobotFAccelerating2EnergyDrain=30/5;
static int RobotFAccelerating3EnergyDrain=60/5;
static int RobotFAccelerating4EnergyDrain=100/5;
static int RobotFTopSpeed1EnergyDrain=0;
static int RobotFTopSpeed2EnergyDrain=30/5;
static int RobotFTopSpeed3EnergyDrain=60/5;
static int RobotFTopSpeed4EnergyDrain=100/5;
static int RobotFDeceleratingEnergyDrain=0;
static int RobotFBrakingEnergyDrain=0;
static int RobotBAccelerating1EnergyDrain=10/5;
static int RobotBAccelerating2EnergyDrain=40/5;
static int RobotBTopSpeed1EnergyDrain=10/5;
static int RobotBTopSpeed2EnergyDrain=40/5;
static int RobotBDeceleratingEnergyDrain=0;

static int RobotBAccelerating3EnergyDrain=110/5;
static int RobotBTopSpeed3EnergyDrain=110/5;
static int RobotBBrakingEnergyDrain=0;
static int RobotLAccelerating1EnergyDrain=10/5;
static int RobotLAccelerating2EnergyDrain=110/5;
static int RobotLTopSpeed1EnergyDrain=10/5;
static int RobotLTopSpeed2EnergyDrain=110/5;
static int RobotLDeceleratingEnergyDrain=0;
static int RobotLBrakingEnergyDrain=0;
static int RobotRAccelerating1EnergyDrain=10/5;
static int RobotRAccelerating2EnergyDrain=110/5;
static int RobotRTopSpeed1EnergyDrain=10/5;
static int RobotRTopSpeed2EnergyDrain=110/5;
static int RobotRDeceleratingEnergyDrain=0;
static int RobotRBrakingEnergyDrain=0;
static int RobotJumpingEnergyDrain=100/5;
static int RobotAirborneEnergyDrain=0;
static int RobotStoppedEnergyDrain=0;
static int RobotKnockDownEnergyDrain=0;


static int RobotWaitingMinEnergy=0;
static int RobotFAccelerating1MinEnergy=0;
static int RobotFAccelerating2MinEnergy=30;
static int RobotFAccelerating3MinEnergy=60;
static int RobotFAccelerating4MinEnergy=100;
static int RobotFTopSpeed1MinEnergy=0;
static int RobotFTopSpeed2MinEnergy=30;
static int RobotFTopSpeed3MinEnergy=60;
static int RobotFTopSpeed4MinEnergy=100;
static int RobotFDeceleratingMinEnergy=0;
static int RobotFBrakingMinEnergy=0;
static int RobotBAccelerating1MinEnergy=10;
static int RobotBAccelerating2MinEnergy=40;
static int RobotBTopSpeed1MinEnergy=10;
static int RobotBTopSpeed2MinEnergy=40;
static int RobotBDeceleratingMinEnergy=0;

static int RobotBAccelerating3MinEnergy=110;
static int RobotBTopSpeed3MinEnergy=110;
static int RobotBBrakingMinEnergy=0;
static int RobotLAccelerating1MinEnergy=10;
static int RobotLAccelerating2MinEnergy=110;
static int RobotLTopSpeed1MinEnergy=10;
static int RobotLTopSpeed2MinEnergy=110;
static int RobotLDeceleratingMinEnergy=0;
static int RobotLBrakingMinEnergy=0;
static int RobotRAccelerating1MinEnergy=10;
static int RobotRAccelerating2MinEnergy=110;
static int RobotRTopSpeed1MinEnergy=10;
static int RobotRTopSpeed2MinEnergy=110;
static int RobotRDeceleratingMinEnergy=0;
static int RobotRBrakingMinEnergy=0;
static int RobotJumpingMinEnergy=200;
static int RobotAirborneMinEnergy=0;
static int RobotStoppedMinEnergy=0;
static int RobotKnockDownMinEnergy=0;

static RLValue RobotGoopiness = RLVal(2.0);
RLValue RobotSlidingFriction = 0.05;

//This just in, late breaking flash, RobotTurning will be handled semi-independently from movement.
//It will check to see that the movement isn't in a bad state, and will handle RobotTurning from there.
#define RobotWaiting                  0
#define RobotFAccelerating1           1
#define RobotFAccelerating2           2
#define RobotFAccelerating3           3
#define RobotFAccelerating4           4
#define RobotFTopSpeed1               5
#define RobotFTopSpeed2               6
#define RobotFTopSpeed3               7
#define RobotFTopSpeed4               8
#define RobotFDecelerating            9
#define RobotFBraking                 10
#define RobotBAccelerating1           11
#define RobotBAccelerating2           12
#define RobotBTopSpeed1               13
#define RobotBTopSpeed2               14
#define RobotBDecelerating            15
//The states above allow for RobotTurning.  those below don't.
#define RobotBAccelerating3           16
#define RobotBTopSpeed3               17
#define RobotBBraking                 18
#define RobotLAccelerating1           19
#define RobotLAccelerating2           20
#define RobotLTopSpeed1               21
#define RobotLTopSpeed2               22
#define RobotLDecelerating            23
#define RobotLBraking                 24
#define RobotRAccelerating1           25
#define RobotRAccelerating2           26
#define RobotRTopSpeed1               27
#define RobotRTopSpeed2               28
#define RobotRDecelerating            29
#define RobotRBraking                 30
#define RobotJumping                  31
#define RobotAirborne                 32
#define RobotStopped                  33
#define RobotKnockDown                34
#define RobotSlideDownBuildingSide    35
#define RobotWaitingOnBuilding        36
#define RobotFAccelerating1OnBuilding 37
#define RobotFAccelerating2OnBuilding 38
#define RobotFTopSpeed1OnBuilding     39
#define RobotFTopSpeed2OnBuilding     40
#define RobotFDeceleratingOnBuilding  41
#define RobotBAccelerating1OnBuilding 42
#define RobotBTopSpeed1OnBuilding     43
#define RobotBDeceleratingOnBuilding  44
#define RobotLAccelerating1OnBuilding 45
#define RobotLTopSpeed1OnBuilding     46
#define RobotLDeceleratingOnBuilding  47
#define RobotRAccelerating1OnBuilding 48
#define RobotRTopSpeed1OnBuilding     49
#define RobotRDeceleratingOnBuilding  50
#define RobotStoppedOnBuilding        51
#define RobotKnockDownOnBuilding      52
/*
#define RTurning                 28
#define LTurning                 29
#define FAccelerating1RTurning   34
#define FAccelerating2RTurning   35
#define FAccelerating3RTurning   36
#define FAccelerating4RTurning   37
#define FTopSpeed1RTurning       38
#define FTopSpeed2RTurning       39
#define FTopSpeed3RTurning       40
#define FTopSpeed4RTurning       41
#define FDeceleratingRTurning    42
#define FAccelerating1LTurning   43
#define FAccelerating2LTurning   44
#define FAccelerating3LTurning   45
#define FAccelerating4LTurning   46
#define FTopSpeed1LTurning       47
#define FTopSpeed2LTurning       48
#define FTopSpeed3LTurning       49
#define FTopSpeed4LTurning       50
#define FDeceleratingLTurning    51
*/
//numerical values of cool stuff.
int RobotMovementState;               //This is the main control of the Robot's movement state.
int RobotNumMovementFrames;   //This counts the number of frames the current movement state has been active.
int RobotOnBuilding=0;
building *RobotBuilding;

RLValue RobotSpeed;
RLValue RobotDistance;      //RobotDistance = integral of speed, i.e. arclength.
RLValue RobotYSpeed;
RLVector RobotPosition;     //These 5 items are controlled by/used by the state functions
RLVector RobotVelocity;
int RobotMotionDamage=1;
extern int RobotSlideNextAnimation;

//Flags which control whether or not you can affect movement.

int RobotMidair;  //This will be changed by altitude bitmap calculations, and will control entering/leaving the RobotAirborne state.
int RobotIsHit;   //This will be changed by the collision detection module
int RobotIsBusy;   //This will be changed by the animation engine, when something's up.
int RobotTurning;  //This is 0 if not RobotTurning, 1 if RobotTurning left, -1 if RobotTurning right.
int FramesStopped;  //This will be totally obsolete as soon as the animation engine works.
int RobotHitObstacle;    //This is for remembering if the airborne state included a wall collision.
#ifdef PC
FILE *shithead;
#endif
typedef int (*StateChange) (void);
//typedef StateChange *StateChangeList;
//StateChange is a function pointer,  There will be one function for each state,
//representing the switch into that state.  Each state will contain as many function
//pointers as there are states it can switch to.  The program will run down the list of these
//functions, and if one of them should return 1, then the program will quit looking.
typedef void (*StateFunction)
           (
              MovingObjectData mover        //This is the frame containing the model.
           );
//StateFunction is a function pointer.  There will be exactly one of them per state.  This
//is what takes the action appropriate to the state.



typedef struct Robot_movement_state_
{
   RLValue AccelerationValue;
   RLValue YAccelerationValue;
   RLValue TopSpeed;
   RLValue TopYSpeed;
   RLValue EnergyDrain;
   StateFunction WhatToDo;
   int numchanges;
   StateChange *ChangeList;
}RobotMovementStateStructure;

RobotMovementStateStructure RobotMotions[53];

typedef struct Robot_animation_state_
{
   RLValue Distance;        //How far the Robot will travel during the course of the animation,
   RLValue NumFrames;       //How long the animation is.  All frame numbers will be counted as fixed point numbers, as with RM standards.
   RLValue StopFrame;       //Which frame is the last.  Usually NumFrames, but some animations are more exotic.
   RLValue EnergyDrain;     //How much energy is drained in a frame.
//   RLValue EnergyMinimum;     //How much energy is drained in a frame.
//   RLValue FirstHitFrame;   //for attacks etc, where there is a specific frame where something interesting happens.
//   RLValue LastHitFrame;    //ditto
   RLAnimationSet Anisette; //this little licorice flavored liqueur is RM's contribution to world peace of mind.
   StateFunction WhatToDo;
   int numchanges;
   StateChange *ChangeList;
}RobotAnimationStateStructure;
extern RobotAnimationStateStructure RobotAnimations[41];

//RLValue RobotCosine(RLValue DiffFrame)
//{
  // int i=RLInt(RLMultiply(DiffFrame,RLVal(2.0)));
//   if(i>9)i=9;
  // return RobotCosineTable[i];
//}
//RLValue RobotSine(RLValue DiffFrame)
//{
   //int i=RLInt(RLMultiply(DiffFrame,RLVal(2.0)));
//   if(i>9)i=9;
   //return RobotSineTable[i];
//}




//I'll now create the raw materials for the state machine, all the state change functions and the
//state functions.

static int ToRobotFBraking(void)
//I'll rely on this function only being called by accelerating or topspeed forward states,
//so that I won't have to write the checks.
{
   if((RobotMovementState==RobotFTopSpeed4 || RobotMovementState==RobotFAccelerating4) && RobotEngy<RobotFAccelerating4MinEnergy)
   {
		YBPlay3DSound(RobotClick,Robotframe);
      DeactivateJets();
      RobotMovementState=RobotFBraking;
      RobotDistance=0;
      RobotNumMovementFrames=0;
      return 1;
   }

   if(InputInt&COMMANDBack)
   {
      DeactivateJets();
      RobotMovementState=RobotFBraking;
      RobotDistance=0;
      RobotNumMovementFrames=0;
      return 1;
   }
   if((RobotMovementState==RobotFTopSpeed4) && !( (InputInt&COMMANDForward) && (InputInt&COMMANDStrongShift) ))
   {
      DeactivateJets();
      RobotMovementState=RobotFBraking;
      RobotDistance=0;
      RobotNumMovementFrames=0;
      return 1;
   }
   return 0;
}
static int ToRobotFDecelerating(void)
//Unfortunately, this one is intimately connected with current speed, state, and input.
//Except for the case in which the forward button has been taken off, because that will certainly lead to 
//deceleration, as this will only be called by states which have positive forward movement.

{
   if((RobotMovementState==RobotFTopSpeed3 || RobotMovementState==RobotFAccelerating3) && RobotEngy<RobotFAccelerating3MinEnergy)
   {
		YBPlay3DSound(RobotClick,Robotframe);
      RobotMovementState=RobotFDecelerating;
      RobotNumMovementFrames=0;
      return 1;
   }
   if((RobotMovementState==RobotFTopSpeed2 || RobotMovementState==RobotFAccelerating2) && RobotEngy<RobotFAccelerating2MinEnergy)
   {
		YBPlay3DSound(RobotClick,Robotframe);
      RobotMovementState=RobotFDecelerating;
      RobotNumMovementFrames=0;
      return 1;
   }
   if((RobotMovementState==RobotFTopSpeed1 || RobotMovementState==RobotFAccelerating1) && RobotEngy<RobotFAccelerating1MinEnergy)
   {
		YBPlay3DSound(RobotClick,Robotframe);
      RobotMovementState=RobotFDecelerating;
      RobotNumMovementFrames=0;
      return 1;
   }
   if((RobotMovementState==RobotFBraking)&&(!((InputInt&COMMANDBack)||(InputInt&COMMANDDefenseShift))) && (RobotSpeed<=RobotMotions[RobotFAccelerating3].TopSpeed) )
   {
      RobotMovementState=RobotFDecelerating;
      RobotNumMovementFrames=0;
      return 1;
   }

   if( (!(InputInt&COMMANDForward)) && RobotSpeed>0)
   {
      RobotMovementState=RobotFDecelerating;
      RobotNumMovementFrames=0;
      return 1;
   }
   //to get here, input must have forward key held down.
   if( (InputInt & COMMANDStrongShift) || (InputInt & COMMANDMediumShift))
      return 0;
   //Can't be decelerating if the player is trying to move as fast as possible.
   //Also can't decelerate out of a travel, have to brake.  So if Medium Shift
   //is held down, and you're losing speed, you have to be going faster than a 
   //run, and must be skidding  (i.e. braking)
   //Input can't have strong or medium shifts held down.
   if(InputInt&COMMANDWeakShift)
   {
      if(RobotSpeed>RobotMotions[RobotFAccelerating2].TopSpeed)
      {
         RobotMovementState=RobotFDecelerating;
         RobotNumMovementFrames=0;
         return 1;
      }
      return 0;
   }
   //Input can't have any shifts held down.
   if(RobotSpeed > RobotMotions[RobotFAccelerating1].TopSpeed)
   {
      RobotMovementState=RobotFDecelerating;
      RobotNumMovementFrames=0;
      return 1;
   }
   return 0;

}

static int ToRobotFDeceleratingOnBuilding(void)
//Unfortunately, this one is intimately connected with current speed, state, and input.
//Except for the case in which the forward button has been taken off, because that will certainly lead to 
//deceleration, as this will only be called by states which have positive forward movement.

{
   if((RobotMovementState==RobotFTopSpeed2OnBuilding || RobotMovementState==RobotFAccelerating2OnBuilding) && RobotEngy<RobotFAccelerating2MinEnergy)
   {
		YBPlay3DSound(RobotClick,Robotframe);
      DeactivateJets();
      RobotMovementState=RobotFDeceleratingOnBuilding;
      RobotNumMovementFrames=0;
      return 1;
   }
   if((RobotMovementState==RobotFTopSpeed1OnBuilding || RobotMovementState==RobotFAccelerating1OnBuilding) && RobotEngy<RobotFAccelerating1MinEnergy)
   {
		YBPlay3DSound(RobotClick,Robotframe);
      DeactivateJets();
      RobotMovementState=RobotFDeceleratingOnBuilding;
      RobotNumMovementFrames=0;
      return 1;
   }
   if( (!(InputInt&COMMANDForward)) && RobotSpeed>0)
   {
      DeactivateJets();
      RobotMovementState=RobotFDeceleratingOnBuilding;
      RobotNumMovementFrames=0;
      return 1;
   }
   //to get here, input must have forward key held down.
   if( (InputInt & COMMANDStrongShift) || (InputInt & COMMANDMediumShift) || (InputInt&COMMANDWeakShift))
      return 0;
   //Can't be decelerating if the player is trying to move as fast as possible.
   //Also can't decelerate out of a travel, have to brake.  So if Medium Shift
   //is held down, and you're losing speed, you have to be going faster than a 
   //run, and must be skidding  (i.e. braking)
   //Input can't have any shifts held down.
   if(RobotSpeed > RobotMotions[RobotFAccelerating1OnBuilding].TopSpeed)
   {
      DeactivateJets();
      RobotMovementState=RobotFDecelerating;
      RobotNumMovementFrames=0;
      return 1;
   }
   return 0;
}


static int ToRobotFAccelerating4(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if( (InputInt&COMMANDForward) && (InputInt&COMMANDStrongShift) &&(!(InputInt&COMMANDBack)))
      if(RobotSpeed<RobotMotions[RobotFAccelerating4].TopSpeed)
      {
		if(RobotEngy<RobotFAccelerating4MinEnergy)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotMovementState=RobotFAccelerating4;
         RobotNumMovementFrames=0;
         return 1;
      }
   return 0;
}
static int ToRobotFTopSpeed4(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if((RobotEngy<RobotFTopSpeed4MinEnergy)&&(RobotMovementState!=RobotAirborne)&&(RobotMovementState!=RobotJumping) )
   {
		YBPlay3DSound(RobotClick,Robotframe);
      RobotMovementState=RobotFBraking;
      RobotDistance=0;
      RobotNumMovementFrames=0;
      return 1;
   }
   if(RobotMovementState==RobotAirborne)
   {
      if(!RobotMidair)
         if(RobotSpeed>=RobotMotions[RobotFAccelerating4].TopSpeed)
         {
            RobotSpeed=RobotMotions[RobotFAccelerating4].TopSpeed;
            RobotMovementState=RobotFTopSpeed4;
            RobotNumMovementFrames=0;
            return 1;
         }
      return 0;
   }
//   if( (InputInt&COMMANDForward) && (InputInt&COMMANDStrongShift) )
      if(RobotMovementState==RobotFAccelerating4)//should be unnecessary
         if(RobotSpeed>=RobotMotions[RobotFAccelerating4].TopSpeed)
         {
            ActivateJets(JETFORWARD);
            RobotSpeed=RobotMotions[RobotFAccelerating4].TopSpeed;
            RobotMovementState=RobotFTopSpeed4;
            RobotNumMovementFrames=0;
            return 1;
         }
   return 0;
}
static int ToRobotFAccelerating3(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if( (InputInt&COMMANDForward) && (InputInt& (COMMANDMediumShift|COMMANDStrongShift) )&&(!(InputInt&COMMANDBack)) )
      if(RobotSpeed<RobotMotions[RobotFAccelerating3].TopSpeed&&RobotSpeed>=RobotMotions[RobotFAccelerating2].TopSpeed)
      {
		if(RobotEngy<RobotFAccelerating3MinEnergy)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotMovementState=RobotFAccelerating3;
         RobotNumMovementFrames=0;
         return 1;
      }
   return 0;
}
static int ToRobotFTopSpeed3(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if(RobotMovementState==RobotAirborne)
   {
      if(!RobotMidair)
         if(RobotSpeed<RobotMotions[RobotFAccelerating4].TopSpeed && RobotSpeed>=RobotMotions[RobotFAccelerating3].TopSpeed)
         {
			if(RobotEngy<RobotFTopSpeed3MinEnergy)
			{
				YBPlay3DSound(RobotClick,Robotframe);
				return 0;
			}
            RobotSpeed=RobotMotions[RobotFAccelerating3].TopSpeed;
            RobotMovementState=RobotFTopSpeed3;
            RobotNumMovementFrames=0;
            return 1;
         }
      return 0;
   }
   if( (InputInt&COMMANDForward) && (InputInt& (COMMANDMediumShift|COMMANDStrongShift) ) )
      if(RobotMovementState==RobotFAccelerating3)
         if(RobotSpeed>=RobotMotions[RobotFAccelerating3].TopSpeed)
         {
			if(RobotEngy<RobotFTopSpeed3MinEnergy)
			{
				YBPlay3DSound(RobotClick,Robotframe);
				return 0;
			}
            RobotSpeed=RobotMotions[RobotFAccelerating3].TopSpeed;
            RobotMovementState=RobotFTopSpeed3;
            RobotNumMovementFrames=0;
            return 1;
         }
   return 0;
}
static int ToRobotFAccelerating2(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if( (InputInt&COMMANDForward) && (InputInt&(COMMANDWeakShift|COMMANDMediumShift|COMMANDStrongShift)) &&(!(InputInt&COMMANDBack)))
      if(RobotSpeed<RobotMotions[RobotFAccelerating2].TopSpeed && RobotSpeed>=RobotMotions[RobotFAccelerating1].TopSpeed )
      {
		if(RobotEngy<RobotFAccelerating2MinEnergy)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotMovementState=RobotFAccelerating2;
         RobotNumMovementFrames=0;
         return 1;
      }
   return 0;
}

static int ToRobotFAccelerating2OnBuilding(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if( (InputInt&COMMANDForward) && (InputInt&(COMMANDWeakShift|COMMANDMediumShift|COMMANDStrongShift)) &&(!(InputInt&COMMANDBack)))
      if(RobotSpeed<RobotMotions[RobotFAccelerating2OnBuilding].TopSpeed && RobotSpeed>=RobotMotions[RobotFAccelerating1OnBuilding].TopSpeed )
      {
		if(RobotEngy<RobotFAccelerating2MinEnergy)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         DeactivateJets();
         RobotMovementState=RobotFAccelerating2OnBuilding;
         RobotNumMovementFrames=0;
         return 1;
      }
   return 0;
}


static int ToRobotFTopSpeed2(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if(RobotMovementState==RobotAirborne)
   {
      if(!RobotMidair)
         if(RobotSpeed<RobotMotions[RobotFAccelerating3].TopSpeed && RobotSpeed>=RobotMotions[RobotFAccelerating2].TopSpeed)
         {
			if(RobotEngy<RobotFTopSpeed2MinEnergy)
			{
				YBPlay3DSound(RobotClick,Robotframe);
				return 0;
			}
            RobotSpeed=RobotMotions[RobotFAccelerating2].TopSpeed;
            RobotMovementState=RobotFTopSpeed2;
            RobotNumMovementFrames=0;
            return 1;
         }
      return 0;
   }
   if( (InputInt&COMMANDForward) && (InputInt&(COMMANDWeakShift|COMMANDMediumShift|COMMANDStrongShift)) )
      if(RobotMovementState==RobotFAccelerating2)
         if(RobotSpeed>=RobotMotions[RobotFAccelerating2].TopSpeed)
         {
			if(RobotEngy<RobotFTopSpeed2MinEnergy)
			{
				YBPlay3DSound(RobotClick,Robotframe);
				return 0;
			}
            RobotSpeed=RobotMotions[RobotFAccelerating2].TopSpeed;
            RobotMovementState=RobotFTopSpeed2;
            RobotNumMovementFrames=0;
            return 1;
         }
   return 0;
}

static int ToRobotFTopSpeed2OnBuilding(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if( (InputInt&COMMANDForward) && (InputInt&(COMMANDWeakShift|COMMANDMediumShift|COMMANDStrongShift)) )
      if(RobotMovementState==RobotFAccelerating2OnBuilding)
         if(RobotSpeed>=RobotMotions[RobotFAccelerating2OnBuilding].TopSpeed)
         {
			if(RobotEngy<RobotFTopSpeed2MinEnergy)
			{
				YBPlay3DSound(RobotClick,Robotframe);
				return 0;
			}
			DeactivateJets();
            RobotSpeed=RobotMotions[RobotFAccelerating2OnBuilding].TopSpeed;
            RobotMovementState=RobotFTopSpeed2OnBuilding;
            RobotNumMovementFrames=0;
            return 1;
         }
   return 0;
}



static int ToRobotFAccelerating1(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if( (InputInt&COMMANDForward) &&(!(InputInt&COMMANDBack)))
      if(RobotSpeed<RobotMotions[RobotFAccelerating1].TopSpeed)
      {
		if(RobotEngy<RobotFAccelerating1MinEnergy)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotMovementState=RobotFAccelerating1;
         RobotNumMovementFrames=0;
         return 1;
      }
   return 0;
}

static int ToRobotFAccelerating1OnBuilding(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if( (InputInt&COMMANDForward) &&(!(InputInt&COMMANDBack)))
      if(RobotSpeed<RobotMotions[RobotFAccelerating1OnBuilding].TopSpeed)
      {
		if(RobotEngy<RobotFAccelerating1MinEnergy)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
 		 DeactivateJets();
         RobotMovementState=RobotFAccelerating1OnBuilding;
         RobotNumMovementFrames=0;
         return 1;
      }
   return 0;
}


static int ToRobotFTopSpeed1(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if(RobotMovementState==RobotAirborne)
   {
      if(!RobotMidair)
         if(RobotSpeed<RobotMotions[RobotFAccelerating2].TopSpeed && RobotSpeed>=RobotMotions[RobotFAccelerating1].TopSpeed)
         {
			if(RobotEngy<RobotFTopSpeed1MinEnergy)
			{
				YBPlay3DSound(RobotClick,Robotframe);
				return 0;
			}
            RobotSpeed=RobotMotions[RobotFAccelerating1].TopSpeed;
            RobotMovementState=RobotFTopSpeed1;
            RobotNumMovementFrames=0;
            return 1;
         }
      return 0;
   }
   
   
   if(InputInt&COMMANDForward)
      if(RobotMovementState==RobotFAccelerating1)
         if(RobotSpeed>=RobotMotions[RobotFAccelerating1].TopSpeed)
         {
			if(RobotEngy<RobotFTopSpeed1MinEnergy)
			{
				YBPlay3DSound(RobotClick,Robotframe);
				return 0;
			}
            RobotSpeed=RobotMotions[RobotFAccelerating1].TopSpeed;
            RobotMovementState=RobotFTopSpeed1;
            RobotNumMovementFrames=0;
            RobotDistance=0;
            return 1;
         }
   return 0;
}

static int ToRobotFTopSpeed1OnBuilding(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if(InputInt&COMMANDForward)
      if(RobotMovementState==RobotFAccelerating1OnBuilding)
         if(RobotSpeed>=RobotMotions[RobotFAccelerating1OnBuilding].TopSpeed)
         {
			if(RobotEngy<RobotFTopSpeed1MinEnergy)
			{
				YBPlay3DSound(RobotClick,Robotframe);
				return 0;
			}
			DeactivateJets();
            RobotSpeed=RobotMotions[RobotFAccelerating1OnBuilding].TopSpeed;
            RobotMovementState=RobotFTopSpeed1OnBuilding;
            RobotNumMovementFrames=0;
            RobotDistance=0;
            return 1;
         }
   return 0;
}

static int ToRobotBBraking(void)
//I'll rely on this function only being called by accelerating or topspeed backward states,
//so that I won't have to write the checks.
{
   if((RobotMovementState==RobotBTopSpeed3 || RobotMovementState==RobotBAccelerating3) && RobotEngy<RobotBAccelerating3MinEnergy)
   {
		YBPlay3DSound(RobotClick,Robotframe);
      DeactivateJets();
      RobotMovementState=RobotBBraking;
      RobotNumMovementFrames=0;
      return 1;
   }
   if((InputInt&COMMANDForward)||(InputInt&COMMANDDefenseShift))
   {
      DeactivateJets();
      RobotMovementState=RobotBBraking;
      RobotNumMovementFrames=0;
      return 1;
   }
   if( RobotMovementState==RobotBTopSpeed3 && RobotNumMovementFrames>RobotNumFramesBackTravel)
   {
      DeactivateJets();
      RobotMovementState=RobotBBraking;
      RobotNumMovementFrames=0;
      return 1;
   }
   return 0;
}

static int ToRobotBDecelerating(void)
//Unfortunately, this one is intimately connected with current speed, state, and input.
//Except for the case in which the back button has been taken off, because that will certainly lead to 
//deceleration, as this will only be called by states which have positive backward movement.
//Unlike the Forward case. you can't go from braking to decelerating  (This is subject to change)

{
   if((RobotMovementState==RobotBTopSpeed2 || RobotMovementState==RobotBAccelerating2) && RobotEngy<RobotBAccelerating2MinEnergy)
   {
		YBPlay3DSound(RobotClick,Robotframe);
      RobotMovementState=RobotBDecelerating;
      RobotNumMovementFrames=0;
      return 1;
   }
   if((RobotMovementState==RobotBTopSpeed1 || RobotMovementState==RobotBAccelerating1) && RobotEngy<RobotBAccelerating1MinEnergy)
   {
		YBPlay3DSound(RobotClick,Robotframe);
      RobotMovementState=RobotBDecelerating;
      RobotNumMovementFrames=0;
      return 1;
   }
   if( (!(InputInt&COMMANDBack)) && RobotSpeed>0)
   {
      RobotMovementState=RobotBDecelerating;
      RobotNumMovementFrames=0;
      return 1;
   }
   //to get here, input must have back key held down.
   if( InputInt & (COMMANDStrongShift|COMMANDWeakShift) )
      return 0;
   //Can't be decelerating if the player is trying to move as fast as possible.  Either
   //we're moving at top speed or braking.
   //Input can't have strong shift held down.
   //Medium shift has no effect.
   //If we have the weak shift held down, and we're going too fast, we must be travelling
   //backward, or skidding to a halt, or whatever, and we would have to brake rather than decelerate.
   //Input can't have any shifts held down.
   if(RobotSpeed > RobotMotions[RobotBAccelerating1].TopSpeed)
   {
      RobotMovementState=RobotBDecelerating;
      RobotNumMovementFrames=0;
      return 1;
   }
   return 0;

}

static int ToRobotBDeceleratingOnBuilding(void)
//Unfortunately, this one is intimately connected with current speed, state, and input.
//Except for the case in which the back button has been taken off, because that will certainly lead to 
//deceleration, as this will only be called by states which have positive backward movement.
//Unlike the Forward case. you can't go from braking to decelerating  (This is subject to change)

{
   if((RobotMovementState==RobotBTopSpeed1OnBuilding || RobotMovementState==RobotBAccelerating1OnBuilding) && RobotEngy<RobotBAccelerating1MinEnergy)
   {
		YBPlay3DSound(RobotClick,Robotframe);
      DeactivateJets();
      RobotMovementState=RobotBDeceleratingOnBuilding;
      RobotNumMovementFrames=0;
      return 1;
   }
   if( (!(InputInt&COMMANDBack)) && RobotSpeed>0)
   {
      DeactivateJets();
      RobotMovementState=RobotBDeceleratingOnBuilding;
      RobotNumMovementFrames=0;
      return 1;
   }
   return 0;

}


static int ToRobotBAccelerating3(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if( (InputInt&COMMANDBack) && (InputInt&COMMANDStrongShift) )
      if(RobotSpeed<RobotMotions[RobotBAccelerating3].TopSpeed)
      {
		if(RobotEngy<RobotBAccelerating3MinEnergy)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         ActivateJets(JETBACK);
         RobotMovementState=RobotBAccelerating3;
         RobotNumMovementFrames=0;
         return 1;
      }
   return 0;
}
static int ToRobotBTopSpeed3(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if(RobotEngy<RobotBTopSpeed3MinEnergy)
   {
		YBPlay3DSound(RobotClick,Robotframe);
      RobotMovementState=RobotBBraking;
      RobotNumMovementFrames=0;
      return 1;
   }
//   if( (InputInt&COMMANDBack) && (InputInt&COMMANDStrongShift) )
      if(RobotSpeed>=RobotMotions[RobotBAccelerating3].TopSpeed)
      {
         RobotSpeed=RobotMotions[RobotBAccelerating3].TopSpeed;
         RobotMovementState=RobotBTopSpeed3;
         RobotNumMovementFrames=0;
         return 1;
      }
   return 0;
}
static int ToRobotBAccelerating2(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if( (InputInt&COMMANDBack) && (InputInt&COMMANDWeakShift) )
      if(RobotSpeed<RobotMotions[RobotBAccelerating2].TopSpeed&&RobotSpeed>=RobotMotions[RobotBAccelerating1].TopSpeed)
      {
		if(RobotEngy<RobotBAccelerating2MinEnergy)
		{
			YBPlay3DSound(RobotClick,Robotframe);

			return 0;
		}
         RobotMovementState=RobotBAccelerating2;
         RobotNumMovementFrames=0;
         return 1;
      }
   return 0;
}
static int ToRobotBTopSpeed2(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if( (InputInt&COMMANDBack) && (InputInt&COMMANDWeakShift) )
      if(RobotMovementState==RobotBAccelerating2)
         if(RobotSpeed>=RobotMotions[RobotBAccelerating2].TopSpeed)
         {
			if(RobotEngy<RobotBTopSpeed2MinEnergy)
			{
				YBPlay3DSound(RobotClick,Robotframe);
				return 0;
			}
            RobotSpeed=RobotMotions[RobotBAccelerating2].TopSpeed;
            RobotMovementState=RobotBTopSpeed2;
            RobotNumMovementFrames=0;
            return 1;
         }
   return 0;
}
static int ToRobotBAccelerating1(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if( InputInt&COMMANDBack )
      if(RobotSpeed<RobotMotions[RobotBAccelerating1].TopSpeed)
      {
		if(RobotEngy<RobotBAccelerating1MinEnergy)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotMovementState=RobotBAccelerating1;
         RobotNumMovementFrames=0;
         return 1;
      }
   return 0;
}

static int ToRobotBAccelerating1OnBuilding(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if( InputInt&COMMANDBack )
      if(RobotSpeed<RobotMotions[RobotBAccelerating1OnBuilding].TopSpeed)
      {
		if(RobotEngy<RobotBAccelerating1MinEnergy)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         DeactivateJets();
         RobotMovementState=RobotBAccelerating1OnBuilding;
         RobotNumMovementFrames=0;
         return 1;
      }
   return 0;
}

static int ToRobotBTopSpeed1(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if(InputInt&COMMANDBack)
      if(RobotMovementState==RobotBAccelerating1)
         if(RobotSpeed>=RobotMotions[RobotBAccelerating1].TopSpeed)
         {
			if(RobotEngy<RobotBAccelerating1MinEnergy)
			{
				YBPlay3DSound(RobotClick,Robotframe);
				return 0;
			}
            RobotSpeed=RobotMotions[RobotBAccelerating1].TopSpeed;
            RobotMovementState=RobotBTopSpeed1;
            RobotNumMovementFrames=0;
            return 1;
         }
   return 0;
}

static int ToRobotBTopSpeed1OnBuilding(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if(InputInt&COMMANDBack)
      if(RobotMovementState==RobotBAccelerating1OnBuilding)
         if(RobotSpeed>=RobotMotions[RobotBAccelerating1OnBuilding].TopSpeed)
         {
			if(RobotEngy<RobotBAccelerating1MinEnergy)
			{
				YBPlay3DSound(RobotClick,Robotframe);
				return 0;
			}
	        DeactivateJets();
            RobotSpeed=RobotMotions[RobotBAccelerating1OnBuilding].TopSpeed;
            RobotMovementState=RobotBTopSpeed1OnBuilding;
            RobotNumMovementFrames=0;
            return 1;
         }
   return 0;
}


static int ToRobotRBraking(void)
//I'll rely on this function only being called by accelerating or topspeed right states,
//so that I won't have to write the checks.
{
   if((RobotMovementState==RobotRTopSpeed2 || RobotMovementState==RobotRAccelerating2) && RobotEngy<RobotRAccelerating2MinEnergy)
   {
		YBPlay3DSound(RobotClick,Robotframe);
      DeactivateJets();
      RobotMovementState=RobotRBraking;
      RobotNumMovementFrames=0;
      return 1;
   }
   if( RobotMovementState==RobotRTopSpeed2 && RobotNumMovementFrames>RobotNumFramesSideTravel)
   {
      DeactivateJets();
      RobotMovementState=RobotRBraking;
      RobotNumMovementFrames=0;
      return 1;
   }
   return 0;
}

static int ToRobotRDecelerating(void)
//This is different from F and B deceleration, because there is no gradation of movement speeds.
//Either there's a Super Surf, which you brake while leaving, or you're at speed1.  So there's no
//checking of shift keys.  If you're not trying to move right, you're not moving right.  That's all.

{
   if((RobotMovementState==RobotRTopSpeed1 || RobotMovementState==RobotRAccelerating1) && RobotEngy<RobotRAccelerating1MinEnergy)
   {
		YBPlay3DSound(RobotClick,Robotframe);
      DeactivateJets();
      RobotMovementState=RobotRDecelerating;
      RobotNumMovementFrames=0;
      return 1;
   }
   if( (!( (InputInt&COMMANDRight)&&(InputInt&COMMANDDefenseShift) )) && RobotSpeed>0)
   {
      DeactivateJets();
      RobotMovementState=RobotRDecelerating;
      RobotNumMovementFrames=0;
      return 1;
   }

   return 0;

}

static int ToRobotRDeceleratingOnBuilding(void)
//This is different from F and B deceleration, because there is no gradation of movement speeds.
//Either there's a Super Surf, which you brake while leaving, or you're at speed1.  So there's no
//checking of shift keys.  If you're not trying to move right, you're not moving right.  That's all.

{
   if((RobotMovementState==RobotRTopSpeed1OnBuilding || RobotMovementState==RobotRAccelerating1OnBuilding) && RobotEngy<RobotRAccelerating1MinEnergy)
   {
		YBPlay3DSound(RobotClick,Robotframe);
      DeactivateJets();
      RobotMovementState=RobotRDeceleratingOnBuilding;
      RobotNumMovementFrames=0;
      return 1;
   }
   if( (!( InputInt&COMMANDJetRight )) && RobotSpeed>0)
   {
      DeactivateJets();
      RobotMovementState=RobotRDeceleratingOnBuilding;
      RobotNumMovementFrames=0;
      return 1;
   }

   return 0;

}


static int ToRobotRAccelerating2(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if( (InputInt&COMMANDJetRight) )
      if(RobotSpeed<RobotMotions[RobotRAccelerating2].TopSpeed)
      {
		if(RobotEngy<RobotRAccelerating2MinEnergy)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         ActivateJets(JETRIGHT);
         RobotMovementState=RobotRAccelerating2;
         RobotNumMovementFrames=0;
         return 1;
      }
   return 0;
}
static int ToRobotRTopSpeed2(void)
{
//   if( (InputInt&COMMANDRight) && (InputInt&COMMANDStrongShift) )
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if(RobotEngy<RobotRTopSpeed2MinEnergy)
   {
		YBPlay3DSound(RobotClick,Robotframe);
      DeactivateJets();
      RobotMovementState=RobotRBraking;
      RobotNumMovementFrames=0;
      return 1;
   }
      if(RobotSpeed>=RobotMotions[RobotRAccelerating2].TopSpeed)
      {
         ActivateJets(JETRIGHT);
         RobotSpeed=RobotMotions[RobotRAccelerating2].TopSpeed;
         RobotMovementState=RobotRTopSpeed2;
         RobotNumMovementFrames=0;
         return 1;
      }
   return 0;
}
static int ToRobotRAccelerating1(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if((InputInt&COMMANDRight)&&(InputInt&COMMANDDefenseShift))
      if(RobotSpeed<RobotMotions[RobotRAccelerating1].TopSpeed)
      {
		if(RobotEngy<RobotRAccelerating1MinEnergy)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         ActivateJets(JETRIGHT);
         RobotMovementState=RobotRAccelerating1;
         RobotNumMovementFrames=0;
         return 1;
      }
   return 0;
}
static int ToRobotRTopSpeed1(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if((InputInt&COMMANDRight)&&(InputInt&COMMANDDefenseShift))
      if(RobotMovementState==RobotRAccelerating1)
         if(RobotSpeed>=RobotMotions[RobotRAccelerating1].TopSpeed)
         {
			if(RobotEngy<RobotRTopSpeed1MinEnergy)
			{
				YBPlay3DSound(RobotClick,Robotframe);
				return 0;
			}
            ActivateJets(JETRIGHT);
            RobotSpeed=RobotMotions[RobotRAccelerating1].TopSpeed;
            RobotMovementState=RobotRTopSpeed1;
            RobotNumMovementFrames=0;
            return 1;
         }
   return 0;
}

static int ToRobotRAccelerating1OnBuilding(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if((InputInt&COMMANDJetRight))
      if(RobotSpeed<RobotMotions[RobotRAccelerating1OnBuilding].TopSpeed)
      {
		if(RobotEngy<RobotRAccelerating1MinEnergy)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         ActivateJets(JETRIGHT);
         RobotMovementState=RobotRAccelerating1OnBuilding;
         RobotNumMovementFrames=0;
         return 1;
      }
   return 0;
}

static int ToRobotRTopSpeed1OnBuilding(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if((InputInt&COMMANDJetRight))
      if(RobotMovementState==RobotRAccelerating1OnBuilding)
         if(RobotSpeed>=RobotMotions[RobotRAccelerating1OnBuilding].TopSpeed)
         {
			if(RobotEngy<RobotRTopSpeed1MinEnergy)
			{
				YBPlay3DSound(RobotClick,Robotframe);
				return 0;
			}
            ActivateJets(JETRIGHT);
            RobotSpeed=RobotMotions[RobotRAccelerating1OnBuilding].TopSpeed;
            RobotMovementState=RobotRTopSpeed1OnBuilding;
            RobotNumMovementFrames=0;
            return 1;
         }
   return 0;
}


static int ToRobotLBraking(void)
//I'll rely on this function only being called by accelerating or topspeed right states,
//so that I won't have to write the checks.
{
   if((RobotMovementState==RobotLTopSpeed2 || RobotMovementState==RobotLAccelerating2) && RobotEngy<RobotLAccelerating2MinEnergy)
   {
		YBPlay3DSound(RobotClick,Robotframe);
      DeactivateJets();
      RobotMovementState=RobotLBraking;
      RobotNumMovementFrames=0;
      return 1;
   }
   if( RobotMovementState==RobotLTopSpeed2 && RobotNumMovementFrames>RobotNumFramesSideTravel)
   {
      DeactivateJets();
      RobotMovementState=RobotLBraking;
      RobotNumMovementFrames=0;
      return 1;
   }
   return 0;
}

static int ToRobotLDecelerating(void)
//This is different from F and B deceleration, because there is no gradation of movement speeds.
//Either there's a Super Surf, which you brake while leaving, or you're at speed1.  So there's no
//checking of shift keys.  If you're not trying to move right, you're not moving right.  That's all.

{
   if((RobotMovementState==RobotLTopSpeed1 || RobotMovementState==RobotLAccelerating1) && RobotEngy<RobotLAccelerating1MinEnergy)
   {
		YBPlay3DSound(RobotClick,Robotframe);
      DeactivateJets();
      RobotMovementState=RobotLDecelerating;
      RobotNumMovementFrames=0;
      return 1;
   }
   if( (!  ( (InputInt&COMMANDLeft)&& (InputInt&COMMANDDefenseShift) ) ) && RobotSpeed>0)
   {
      DeactivateJets();
      RobotMovementState=RobotLDecelerating;
      RobotNumMovementFrames=0;
      return 1;
   }
   return 0;

}

static int ToRobotLDeceleratingOnBuilding(void)
//This is different from F and B deceleration, because there is no gradation of movement speeds.
//Either there's a Super Surf, which you brake while leaving, or you're at speed1.  So there's no
//checking of shift keys.  If you're not trying to move right, you're not moving right.  That's all.

{
   if((RobotMovementState==RobotLTopSpeed1OnBuilding || RobotMovementState==RobotLAccelerating1OnBuilding) && RobotEngy<RobotLAccelerating1MinEnergy)
   {
		YBPlay3DSound(RobotClick,Robotframe);
      DeactivateJets();
      RobotMovementState=RobotLDeceleratingOnBuilding;
      RobotNumMovementFrames=0;
      return 1;
   }
   if( (!   (InputInt&COMMANDJetLeft)  ) && RobotSpeed>0)
   {
      DeactivateJets();
      RobotMovementState=RobotLDeceleratingOnBuilding;
      RobotNumMovementFrames=0;
      return 1;
   }
   return 0;

}



static int ToRobotLAccelerating2(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if(InputInt&COMMANDJetLeft)
      if(RobotSpeed<RobotMotions[RobotLAccelerating2].TopSpeed)
      {
		if(RobotEngy<RobotLAccelerating2MinEnergy)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         ActivateJets(JETLEFT);
         RobotMovementState=RobotLAccelerating2;
         RobotNumMovementFrames=0;
         return 1;
      }
   return 0;
}
static int ToRobotLTopSpeed2(void)
{
   //if( (InputInt&COMMANDLeft) && (InputInt&COMMANDStrongShift) && (InputInt&COMMANDDefenseShift) )
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if(RobotEngy<RobotLTopSpeed2MinEnergy)
   {
		YBPlay3DSound(RobotClick,Robotframe);
      ActivateJets(JETLEFT);
      RobotMovementState=RobotLBraking;
      RobotNumMovementFrames=0;
      return 1;
   }
   if(RobotSpeed>=RobotMotions[RobotLAccelerating2].TopSpeed)
   {
      ActivateJets(JETLEFT);
      RobotSpeed=RobotMotions[RobotLAccelerating2].TopSpeed;
      RobotMovementState=RobotLTopSpeed2;
      RobotNumMovementFrames=0;
      return 1;
   }
   return 0;
}
static int ToRobotLAccelerating1(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if((InputInt&COMMANDLeft)&&(InputInt&COMMANDDefenseShift))
      if(RobotSpeed<RobotMotions[RobotLAccelerating1].TopSpeed)
      {
		if(RobotEngy<RobotLAccelerating1MinEnergy)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
        ActivateJets(JETLEFT);
         RobotMovementState=RobotLAccelerating1;
         RobotNumMovementFrames=0;
         return 1;
      }
   return 0;
}
static int ToRobotLTopSpeed1(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if((InputInt&COMMANDLeft)&&(InputInt&COMMANDDefenseShift))
      if(RobotMovementState==RobotLAccelerating1)
         if(RobotSpeed>=RobotMotions[RobotLAccelerating1].TopSpeed)
         {
			if(RobotEngy<RobotLTopSpeed1MinEnergy)
			{
				YBPlay3DSound(RobotClick,Robotframe);
				return 0;
			}
            ActivateJets(JETLEFT);
            RobotSpeed=RobotMotions[RobotLAccelerating1].TopSpeed;
            RobotMovementState=RobotLTopSpeed1;
            RobotNumMovementFrames=0;
            return 1;
         }
   return 0;
}

static int ToRobotLAccelerating1OnBuilding(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if(InputInt&COMMANDJetLeft)
      if(RobotSpeed<RobotMotions[RobotLAccelerating1OnBuilding].TopSpeed)
      {
		if(RobotEngy<RobotLAccelerating1MinEnergy)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         ActivateJets(JETLEFT);
         RobotMovementState=RobotLAccelerating1OnBuilding;
         RobotNumMovementFrames=0;
         return 1;
      }
   return 0;
}
static int ToRobotLTopSpeed1OnBuilding(void)
{
   if(RobotAnimationState==RobotHighAttack1 ||
      RobotAnimationState==RobotMediumAttack1||
      RobotAnimationState==RobotMediumAttack2||
      RobotAnimationState==RobotLowAttack2||
      RobotAnimationState==RobotSuperKick2||
      RobotAnimationState==RobotSpecialAttack3||
      RobotAnimationState==RobotJumpAttack1||
      RobotAnimationState==RobotJumpAttack2)
	  return 0;
   if(InputInt&COMMANDJetLeft)
      if(RobotMovementState==RobotLAccelerating1OnBuilding)
         if(RobotSpeed>=RobotMotions[RobotLAccelerating1OnBuilding].TopSpeed)
         {
			if(RobotEngy<RobotLTopSpeed1MinEnergy)
			{
				YBPlay3DSound(RobotClick,Robotframe);
				return 0;
			}
            ActivateJets(JETLEFT);
            RobotSpeed=RobotMotions[RobotLAccelerating1OnBuilding].TopSpeed;
            RobotMovementState=RobotLTopSpeed1OnBuilding;
            RobotNumMovementFrames=0;
            return 1;
         }
   return 0;
}

static int ToRobotStopped(void)
{
   
   if(RobotMovementState==RobotSlideDownBuildingSide)
      if(!RobotMidair)
      {
         DeactivateJets();
         RobotMovementState=RobotStopped;
         RobotDistance=0;
         RobotNumMovementFrames=0;
         RobotAnimationState=RobotSlideNextAnimation;
         RobotAnimationFrame=0;
      }
   
   if((RobotMovementState == RobotAirborne) && !RobotMidair)//Hit something in RobotMidair
   {
/*      if(RobotHitObstacle)
      {
         RobotMovementState=RobotStopped;
         RobotDistance=0;
         RobotNumMovementFrames=0;
         //FramesStopped=NumFramesAcrobatic;
         RobotHitObstacle=0;
         return 1;
      }*/
      if(RobotSpeed<RobotMotions[RobotFAccelerating1].TopSpeed)
      {
         DeactivateJets();
         RobotMovementState=RobotStopped;
         RobotDistance=0;
         RobotNumMovementFrames=0;
//         RobotAnimationState=RobotJumpStop;
//         RobotAnimationFrame=
         return 1;
      }
   }


   
   if( (RobotMovementState!=RobotAirborne) && RobotHitObstacle && (RobotSpeed>RobotMotions[RobotFAccelerating2].TopSpeed) )//Ran into something.
   {
      DeactivateJets();
      RobotMovementState=RobotStopped;
      RobotDistance=0;
      RobotNumMovementFrames=0;
      FramesStopped=NumFramesAcrobatic;
      RobotHitObstacle=0;
      return 1;
   }
   if((RobotAnimationState==RobotHighAttack1||RobotAnimationState==RobotMediumAttack1
      ||RobotAnimationState==RobotLowAttack1First||RobotAnimationState==RobotMediumAttack2
      ||RobotAnimationState==RobotLowAttack2)&&(RobotSpeed <=0))
   {
      DeactivateJets();
      RobotMovementState=RobotStopped;
      RobotDistance=0;
      RobotNumMovementFrames=0;
      RobotHitObstacle=0;
      return 1;
   }
   
/*   if(RobotMovementState==RobotWaiting && (InputInt&(COMMANDCrouch|COMMANDHighAttack|COMMANDLowAttack) ))
   {
      RobotMovementState=RobotStopped;
      RobotDistance=0;
      RobotNumMovementFrames=0;
      FramesStopped=NumFramesCrouch;//This will be meaningless soon, and will have to be replaced
      //with a message from the animation engine that it's ok to move again.
      RobotHitObstacle=0;
      return 1;
   }*/
   return 0;
   
}

//static int ToRobotStoppedOnBuilding(void);
StateChange ToRobotStoppedOnBuilding=ToRobotStopped;

static int ToRobotWaiting(void)
{
   if(RobotMovementState == RobotFDecelerating || RobotMovementState == RobotBDecelerating || RobotMovementState == RobotLDecelerating || RobotMovementState == RobotRDecelerating ||
      RobotMovementState == RobotFBraking      || RobotMovementState == RobotBBraking      || RobotMovementState == RobotLBraking      || RobotMovementState == RobotRBraking)
      if(RobotSpeed <=0)
      {
         RobotMovementState = RobotWaiting;
         RobotDistance=0;
         RobotNumMovementFrames=0;
         return 1;
      }
/*   if(RobotMovementState == RobotStopped)
      if(RobotNumMovementFrames>=FramesStopped)
      {
         RobotMovementState=RobotWaiting;
         RobotDistance=0;
         RobotNumMovementFrames=0;
         return 1;
      }*/
   if(RobotMovementState == RobotAirborne)
   {
      if(!(RobotMidair||RobotHitObstacle))
      {
         RobotMovementState=RobotWaiting;
         RobotDistance=0;
         RobotNumMovementFrames=0;
         return 1;
      }
   }
   else
      if(RobotHitObstacle&&RobotSpeed<=RobotMotions[RobotFAccelerating2].TopSpeed)//walked into something.
      {
         RobotMovementState=RobotWaiting;
         RobotDistance=0;
         RobotNumMovementFrames=0;
         return 1;
      }
   return 0;
}

static int ToRobotWaitingOnBuilding(void)
{
   if(RobotMovementState == RobotFDeceleratingOnBuilding || 
	   RobotMovementState == RobotBDeceleratingOnBuilding || 
	   RobotMovementState == RobotLDeceleratingOnBuilding || 
	   RobotMovementState == RobotRDeceleratingOnBuilding)
      if(RobotSpeed <=0)
      {
         DeactivateJets();
         RobotMovementState = RobotWaitingOnBuilding;
         RobotDistance=0;
         RobotNumMovementFrames=0;
         return 1;
      }
/*   if(RobotMovementState == RobotAirborne)
   {
      if(!(RobotMidair||RobotHitObstacle))
      {
         RobotMovementState=RobotWaiting;
         RobotDistance=0;
         RobotNumMovementFrames=0;
         return 1;
      }
   }
   else
      if(RobotHitObstacle&&RobotSpeed<=RobotMotions[RobotFAccelerating2].TopSpeed)//walked into something.
      {
         RobotMovementState=RobotWaiting;
         RobotDistance=0;
         RobotNumMovementFrames=0;
         return 1;
      }*/
   return 0;
}



static int ToRobotJumping(void)
{
   if((!RobotMidair) && (!RobotIsHit) && (!RobotIsBusy) )
      if(InputInt&COMMANDJump)
      {
		if(RobotEngy<RobotJumpingMinEnergy)
		{
			YBPlay3DSound(RobotClick,Robotframe);
			return 0;
		}
         RobotMovementState=RobotJumping;
         RobotDistance=0;
         RobotNumMovementFrames=0;
         RobotYSpeed=0;
         return 1;
      }
      return 0;
}

static int ToRobotAirborne(void)
{
   if(RobotMovementState==RobotJumping)
   {
/*
      if((!(InputInt&COMMANDJump))|| RobotEngy<RobotJumpingMinEnergy)
      {
         RobotMidair=1;
         RobotMovementState=RobotAirborne;
         RobotDistance=0;
         RobotNumMovementFrames=0;
         return 1;
      }
*/
      if(RobotEngy<RobotJumpingMinEnergy)
     {
		YBPlay3DSound(RobotClick,Robotframe);
         RobotMidair=1;
//         RobotYSpeed=MaxYVel;
         RobotAnimationState=RobotJumpFreeze;
         RobotMovementState=RobotAirborne;
//         RobotDistance=0;
         RobotNumMovementFrames=0;
         return 1;
      }
      if(RobotYSpeed>MaxYVel)
     {
         RobotMidair=1;
         RobotYSpeed=MaxYVel;
         RobotAnimationState=RobotJumpFreeze;
         RobotMovementState=RobotAirborne;
         RobotDistance=0;
         RobotNumMovementFrames=0;
         return 1;
      }
   }
   else if(RobotMidair)
   {
      RobotMovementState=RobotAirborne;
      RobotDistance=0;
      RobotNumMovementFrames=0;
      return 1;
   }
   else if(RobotOnBuilding)
      if(RobotBuilding->cur_damage>=RobotBuilding->max_damage)
      {
         RobotMovementState=RobotAirborne;
         RobotAnimationState=RobotJumpFreeze;
         RobotOnBuilding=0;
         RobotDistance=0;
         RobotNumMovementFrames=0;
         RobotYSpeed=0;
         RobotMidair=1;
         return 1;
      }
   return 0;
}
/*
static int ToRobotKnockDown(void)
{
   return 0;
} *///this function isn't needed because the MKB state is only entered when the animation engine forces it.
//Just like the normal way to enter RobotStopped is from the animation engine, but this is exclusive.

static void RobotWaitingFunction(MovingObjectData mover)
{
   RLVector dir;
   RLVector up;
   RLVector newdir;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);
   if( (InputInt&COMMANDLeft) && !(InputInt&COMMANDDefenseShift)  &&!(InputInt&COMMANDRight) )
   {
      RobotTurning=1;
	  if(RobotTheta>=0)
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
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
   }
   else if( (InputInt&COMMANDRight) && !(InputInt&COMMANDDefenseShift)  &&!(InputInt&COMMANDLeft) )
   {
      RobotTurning=-1;
	  if(RobotTheta<=0)
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
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
   }
   else
   {
      RobotTurning=0;
	  RobotTheta = 0;
   }
   RobotVelocity.x=RobotVelocity.y=RobotVelocity.z=0;
   RobotSpeed=0;
   RobotYSpeed=0;
   RLFrameGetPosition(mover->PositioningFrame,scene,&RobotPosition);
   mover->CurrentPosition.x=RobotPosition.x;
   mover->CurrentPosition.y=RobotPosition.y;
   mover->CurrentPosition.z=RobotPosition.z;
   mover->ProjectedPosition.x=RobotPosition.x;
   mover->ProjectedPosition.y=RobotPosition.y;
   mover->ProjectedPosition.z=RobotPosition.z;
   RobotData.DamageICause = RobotMotionDamage*RobotSpeed/RobotMaxFVel4;
}
static StateFunction RobotWaitingOnBuildingFunction = RobotWaitingFunction;

extern RLBox landbox;   
static void RobotMovingOnBuildingFunction(MovingObjectData mover)
{
   static RLVector CollisionVector;
//   FILE *shithead;
   RLVector   dir;
//   int result;
   RLVector up;
   RLVector newdir;
   RLValue Distance;
   RLValue DIFFRAME;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLValue X2,Z2,Y2;
   RLValue DestructionDistance=RobotAnimations[RobotAnimationState].Distance;
   RLValue HalfDestructionDistance = DestructionDistance/2;
   RLValue NextRobotDistance;
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   DIFFRAME=DiffFrame;
      

   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);
   if( (InputInt&COMMANDLeft) && !(InputInt&COMMANDDefenseShift)  &&!(InputInt&COMMANDRight) )
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
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
   }
   else if( (InputInt&COMMANDRight) && !(InputInt&COMMANDDefenseShift)  &&!(InputInt&COMMANDLeft) )
   {
      RobotTurning=-1;
	  if(RobotTheta<0)
	  {
		  RobotTheta = RobotTurnAcceleration;
	  }
	  else
	  {
		  RobotTheta +=(RLMultiply(DiffFrame,RobotTurnAcceleration));
	  }
	  if(RobotTheta< RobotTurnMaximum)
	  {
		  RobotTheta = RobotTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
   }
   else
   {
	   RobotTheta=0;
      RobotTurning=0;
   }
   if(RobotAnimationState!=RobotIntoIntoRun)
      RobotSpeed+=RLMultiply(RobotMotions[RobotMovementState].AccelerationValue,DIFFRAME);
   if(RobotSpeed>RobotMotions[RobotMovementState].TopSpeed) RobotSpeed=RobotMotions[RobotMovementState].TopSpeed;
   if(RobotSpeed<0) RobotSpeed=0;
   Distance=RLMultiply(RobotSpeed,DIFFRAME);
   switch(RobotMovementState)
   {
      case RobotFAccelerating1OnBuilding:
      case RobotFAccelerating2OnBuilding:
      case RobotFTopSpeed1OnBuilding:
      case RobotFTopSpeed2OnBuilding:
      case RobotFDeceleratingOnBuilding:
         RobotVelocity.x=RLMultiply(-dir.x,Distance);
         RobotVelocity.z=RLMultiply(-dir.z,Distance);
         
      break;

      case RobotBAccelerating1OnBuilding:
      case RobotBTopSpeed1OnBuilding:
      case RobotBDeceleratingOnBuilding:
         RobotVelocity.x=RLMultiply(dir.x,Distance);
         RobotVelocity.z=RLMultiply(dir.z,Distance);
      break;
      
      case RobotLAccelerating1OnBuilding:
      case RobotLTopSpeed1OnBuilding:
      case RobotLDeceleratingOnBuilding:
         RobotVelocity.x=RLMultiply(dir.z,Distance);
         RobotVelocity.z=RLMultiply(-dir.x,Distance);
      break;

      case RobotRAccelerating1OnBuilding:
      case RobotRTopSpeed1OnBuilding:
      case RobotRDeceleratingOnBuilding:
         RobotVelocity.x=RLMultiply(-dir.z,Distance);
         RobotVelocity.z=RLMultiply(dir.x,Distance);
      break;


   }
   NextRobotDistance = RobotDistance+Distance;
   if((RobotDistance<DestructionDistance && NextRobotDistance>=DestructionDistance) ||
      (RobotDistance<HalfDestructionDistance && NextRobotDistance>=HalfDestructionDistance))
   {
      RobotBuilding->cur_damage+=mover->DamageICause;
      if(RobotBuilding->cur_damage>=RobotBuilding->max_damage)
      {
         Population -= RobotBuilding->power_mon_amount * 1000;
         CollisionVector.z=0;
         CollisionVector.x=0;
         CollisionVector.y=RLVal(1.0);
         CowboyDeathMarch(RobotBuilding,&CollisionVector);
//         if (RobotBuilding->building_num == -1) 
//            YBPlay3DSound(SmallBldgBoom, Robotframe);
//         else 
//            YBPlay3DSound(BigBuildingBoom, Robotframe);
      }
   }
   RobotDistance=NextRobotDistance;
   RobotVelocity.y=RLVal(0);

   X2=mover->CurrentPosition.x+RobotVelocity.x;
   Z2=mover->CurrentPosition.z+RobotVelocity.z;
   if(X2>landbox.max.x)
      X2=landbox.max.x;
   if(X2<landbox.min.x)
      X2=landbox.min.x;
   if(Z2<landbox.min.z)
      Z2=landbox.min.z;
   if(Z2>landbox.max.z)
      Z2=landbox.max.z;
   Y2=mover->CurrentPosition.y;

//   shithead=fopen("shit.out","a");
//   fprintf(shithead,"X2 = %.3f, Y2 = %.3f, Z2=%.3f\n",X2,Y2,Z2);
//   fprintf(shithead,"RobotVelocity = (%.3f. %.3f, %.3f)\n",RobotVelocity.x,RobotVelocity.y,RobotVelocity.z);
//   fprintf(shithead,"RobotSpeed = %.3f, RobotDistance = %.3f\n",RobotSpeed,RobotDistance);
//   fprintf(shithead,"Current Position =(%.3f, %.3f, %.3f)\n\n",
//       mover->CurrentPosition.x,mover->CurrentPosition.y,mover->CurrentPosition.z);
//   fprintf(shithead,"RobotMovementState = %d, RobotAnimationState = %d\n",RobotMovementState,RobotAnimationState);
//   fclose(shithead);
   
   if((X2>(RobotBuilding->building.max.x - mover->Volume.min.x)) ||
      (X2<(RobotBuilding->building.min.x - mover->Volume.max.x)) ||
      (Z2>(RobotBuilding->building.max.z - mover->Volume.min.z)) ||
      (Z2<(RobotBuilding->building.min.z - mover->Volume.max.z)))

   {
      RobotMovementState=RobotAirborne;
	  RobotAnimationState=RobotJumpFreeze;
	  RobotMidair=1;
      RobotOnBuilding=0;
      RobotDistance = 0;
   }
   RLFrameGetPosition(mover->PositioningFrame,scene,&RobotPosition);
   mover->ProjectedPosition.x=X2;
   mover->ProjectedPosition.y=Y2;
   mover->ProjectedPosition.z=Z2;
   RobotData.DamageICause = RobotMotionDamage*RobotSpeed/RobotMaxFVel4;

}
static void RobotFAccelerating1Function(MovingObjectData mover)
{
   RLVector   dir;
   int result;
   RLVector up;
   RLVector newdir;
   RLValue Distance;
   RLValue DIFFRAME;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   if(SpuddeMapHeight2(mover->CurrentPosition.x,mover->CurrentPosition.z)<sealevel)
      DIFFRAME=RLDivide(DiffFrame,RobotGoopiness);
   else
      DIFFRAME=DiffFrame;
      

   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);
   if( (InputInt&COMMANDLeft) && !(InputInt&COMMANDDefenseShift)  &&!(InputInt&COMMANDRight) )
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
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLMultiply(-RobotTurnRate,DIFFRAME));
   }
   else if( (InputInt&COMMANDRight) && !(InputInt&COMMANDDefenseShift)  &&!(InputInt&COMMANDLeft) )
   {
      RobotTurning=-1;
	  if(RobotTheta<0)
	  {
		  RobotTheta = RobotTurnAcceleration;
	  }
	  else
	  {
		  RobotTheta +=(RLMultiply(DiffFrame,RobotTurnAcceleration));
	  }
	  if(RobotTheta > RobotTurnMaximum)
	  {
		  RobotTheta = RobotTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLMultiply(RobotTurnRate,DIFFRAME));
   }
   else
   {
      RobotTurning=0;
	  RobotTheta=0;
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLVal(0));
   }
   if(RobotAnimationState!=RobotIntoIntoRun)
      RobotSpeed+=RLMultiply(RobotMotions[RobotMovementState].AccelerationValue,DIFFRAME);
   if(RobotSpeed>RobotMotions[RobotMovementState].TopSpeed) RobotSpeed=RobotMotions[RobotMovementState].TopSpeed;
   if(RobotSpeed<0) RobotSpeed=0;
   Distance=RLMultiply(RobotSpeed,DIFFRAME);
   RobotVelocity.x=RLMultiply(-dir.x,Distance);
   RobotVelocity.z=RLMultiply(-dir.z,Distance);
   RobotDistance+=Distance;
   RobotVelocity.y=RLVal(0);

   result=SpuddeMoveOnGround(mover,&RobotVelocity,&RobotGradientFactor);
   if(result&2)
   {
//   FILE *shithead;
//      RLFrameGetPosition(monstframe,Scene,&MonPos);
//      RLFrameGetPosition(Robotframe,Scene,&RobotPos);
//      RLFrameGetOrientation(Robotframe,Scene,&RobotFace,&RobotUp);
      if(RobotSpeed>RobotMaxFVel2)
      {
//         shithead=fopen("shit.out","a");
//         fprintf(shithead,"Robotspeed = %f, I'm in the big knockdown1.\n",RobotSpeed);
//         fclose(shithead);
         RobotAnimationFrame=RLVal(0);
         RobotMovementState=RobotKnockDown;
		 RobotFallDownSpin=RLVal(rand()%20-10);
         RobotDistance=0;
         RobotNumMovementFrames=0;
         RobotFallDownDirection.x=dir.x;
         RobotFallDownDirection.y=0;
         RobotFallDownDirection.z=dir.z;
//      if(RLVectorDotProduct(&RobotFace,&RobotFallDownDirection)<0 )
//         RobotAnimationState=RobotAcrobatic1;
//      else
         RobotAnimationState=RobotAcrobatic2;
      }
      else
      {
//         shithead=fopen("shit.out","a");
//         fprintf(shithead,"Robotspeed = %f, I'm in the little knockdown1.\n",RobotSpeed);
//         fclose(shithead);
         RobotMovementState=RobotWaiting;
         RobotAnimationState=RobotPause1;
         RobotDistance = 0;
         RobotSpeed=0;
         
      }


   }
   if(result&1)
   {
      RobotMidair=1;
   }
   RLFrameGetPosition(mover->PositioningFrame,scene,&RobotPosition);
   RobotData.DamageICause = RobotMotionDamage*RobotSpeed/RobotMaxFVel4;
}

static void RobotFAccelerating2Function(MovingObjectData mover)
{
   RLVector   dir;
   int result;
   RLVector up;
   RLVector newdir;
   RLValue Distance;
   RLValue DIFFRAME;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   if(SpuddeMapHeight2(mover->CurrentPosition.x,mover->CurrentPosition.z)<sealevel)
      DIFFRAME=RLDivide(DiffFrame,RobotGoopiness);
   else
      DIFFRAME=DiffFrame;

   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);
   if( (InputInt&COMMANDLeft) && !(InputInt&COMMANDDefenseShift)  &&!(InputInt&COMMANDRight) )
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
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLMultiply(-RobotTurnRate,DIFFRAME));
   }
   else if( (InputInt&COMMANDRight) && !(InputInt&COMMANDDefenseShift)  &&!(InputInt&COMMANDLeft) )
   {
      RobotTurning=-1;
	  if(RobotTheta<0)
	  {
		  RobotTheta = RobotTurnAcceleration;
	  }
	  else
	  {
		  RobotTheta +=(RLMultiply(DiffFrame,RobotTurnAcceleration));
	  }
	  if(RobotTheta > RobotTurnMaximum)
	  {
		  RobotTheta = RobotTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLMultiply(RobotTurnRate,DIFFRAME));
   }
   else
   {
      RobotTurning=0;
	  RobotTheta=0;
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLVal(0));
   }
   RobotSpeed+=RLMultiply(RobotMotions[RobotMovementState].AccelerationValue,DIFFRAME);
   if(RobotSpeed>RobotMotions[RobotMovementState].TopSpeed) RobotSpeed=RobotMotions[RobotMovementState].TopSpeed;
   if(RobotSpeed<0) RobotSpeed=0;
   Distance=RLMultiply(RobotSpeed,DIFFRAME);
   RobotVelocity.x=RLMultiply(-dir.x,Distance);
   RobotVelocity.z=RLMultiply(-dir.z,Distance);
   RobotDistance+=Distance;
   RobotVelocity.y=RLVal(0);

   result=SpuddeMoveOnGround(mover,&RobotVelocity,&RobotGradientFactor);
   if(result&2)
   {
      if(RobotSpeed>RobotMaxFVel2)
      {
         RobotAnimationFrame=RLVal(0);
         RobotMovementState=RobotKnockDown;
		 RobotFallDownSpin=RLVal(rand()%20-10);
         RobotDistance=0;
         RobotNumMovementFrames=0;
         RobotFallDownDirection.x=dir.x;
         RobotFallDownDirection.y=0;
         RobotFallDownDirection.z=dir.z;
         RobotAnimationState=RobotAcrobatic2;
      }
      else
      {
         RobotMovementState=RobotWaiting;
         RobotAnimationState=RobotPause1;
         RobotDistance = 0;
         RobotSpeed=0;
         
      }


   }
   if(result&1)
   {
      RobotMidair=1;
   }
   RLFrameGetPosition(mover->PositioningFrame,scene,&RobotPosition);
   RobotData.DamageICause = RobotMotionDamage*RobotSpeed/RobotMaxFVel4;
}


//static StateFunction RobotFAccelerating2Function = RobotFAccelerating1Function;
static StateFunction RobotFAccelerating3Function = RobotFAccelerating2Function;
static StateFunction RobotFAccelerating4Function = RobotFAccelerating2Function;
static StateFunction RobotFTopSpeed1Function = RobotFAccelerating2Function;
static StateFunction RobotFTopSpeed2Function = RobotFAccelerating2Function;
static StateFunction RobotFTopSpeed3Function = RobotFAccelerating2Function;
static StateFunction RobotFTopSpeed4Function = RobotFAccelerating2Function;
static StateFunction RobotFDeceleratingFunction = RobotFAccelerating2Function;
static StateFunction RobotFBrakingFunction = RobotFAccelerating2Function;

static void RobotBAccelerating1Function(MovingObjectData mover)
{
   RLVector   dir;
   int result;
   RLVector up;
   RLVector newdir;
   RLValue Distance;
   RLValue DIFFRAME;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   if(SpuddeMapHeight2(mover->CurrentPosition.x,mover->CurrentPosition.z)<sealevel)
      DIFFRAME=RLDivide(DiffFrame,RobotGoopiness);
   else
      DIFFRAME=DiffFrame;

   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);
   if( (InputInt&COMMANDLeft) && !(InputInt&COMMANDDefenseShift)  &&!(InputInt&COMMANDRight) )
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
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLMultiply(-RobotTurnRate,DIFFRAME));
   }
   else if( (InputInt&COMMANDRight) && !(InputInt&COMMANDDefenseShift)  &&!(InputInt&COMMANDLeft) )
   {
      RobotTurning=-1;
	  if(RobotTheta<0)
	  {
		  RobotTheta = RobotTurnAcceleration;
	  }
	  else
	  {
		  RobotTheta +=(RLMultiply(DiffFrame,RobotTurnAcceleration));
	  }
	  if(RobotTheta > RobotTurnMaximum)
	  {
		  RobotTheta = RobotTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLMultiply(RobotTurnRate,DIFFRAME));
   }
   else
   {
      RobotTurning=0;
	  RobotTheta=0;
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLVal(0));
   }
   RobotSpeed+=RLMultiply(RobotMotions[RobotMovementState].AccelerationValue,DIFFRAME);
   if(RobotSpeed>RobotMotions[RobotMovementState].TopSpeed) RobotSpeed=RobotMotions[RobotMovementState].TopSpeed;
   if(RobotSpeed<0) RobotSpeed=0;
   Distance=RLMultiply(RobotSpeed,DIFFRAME);
   RobotVelocity.x=RLMultiply(dir.x,Distance);
   RobotVelocity.z=RLMultiply(dir.z,Distance);
   RobotVelocity.y=RLVal(0);
   RobotDistance+=Distance;


   result=SpuddeMoveOnGround(mover,&RobotVelocity,&RobotGradientFactor);
   if(result&2)
   {
      if(RobotSpeed>RobotMaxFVel2)
      {
         RobotAnimationFrame=RLVal(0);
         RobotMovementState=RobotKnockDown;
		 RobotFallDownSpin=RLVal(rand()%20-10);
         RobotDistance=0;
         RobotNumMovementFrames=0;
         RobotFallDownDirection.x=dir.x;
         RobotFallDownDirection.y=0;
         RobotFallDownDirection.z=dir.z;
         RobotAnimationState=RobotAcrobatic1;
      }
      else
      {
         RobotMovementState=RobotWaiting;
         RobotAnimationState=RobotPause1;
         RobotDistance = 0;
         RobotSpeed=0;
         
      }
   }
   if(result&1)
   {
      RobotMidair=1;
   }
   RLFrameGetPosition(mover->PositioningFrame,scene,&RobotPosition);
   RobotData.DamageICause = RobotMotionDamage*RobotSpeed/RobotMaxFVel4;
}
static StateFunction RobotBAccelerating2Function = RobotBAccelerating1Function;
static StateFunction RobotBTopSpeed1Function = RobotBAccelerating1Function;
static StateFunction RobotBTopSpeed2Function = RobotBAccelerating1Function;
static StateFunction RobotBDeceleratingFunction = RobotBAccelerating1Function;

static void BAccelerating3Function(MovingObjectData mover)
{
   RLVector   dir;
   int result;
   RLVector up;
   RLValue Distance;
   RLValue DIFFRAME;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   if(SpuddeMapHeight2(mover->CurrentPosition.x,mover->CurrentPosition.z)<sealevel)
      DIFFRAME=RLDivide(DiffFrame,RobotGoopiness);
   else
      DIFFRAME=DiffFrame;

   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);
   RobotSpeed+=RLMultiply(RobotMotions[RobotMovementState].AccelerationValue,DIFFRAME);
   if(RobotSpeed>RobotMotions[RobotMovementState].TopSpeed) RobotSpeed=RobotMotions[RobotMovementState].TopSpeed;
   if(RobotSpeed<0) RobotSpeed=0;
   Distance=RLMultiply(RobotSpeed,DIFFRAME);
   RobotVelocity.x=RLMultiply(dir.x,Distance);
   RobotVelocity.z=RLMultiply(dir.z,Distance);
   RobotVelocity.y=RLVal(0);
   RobotDistance+=Distance;
   
//   shithead=fopen("shit.out","a");
//   fprintf(shithead,"in BACC, Distance = %d\n",RobotDistance);
//   fclose(shithead);
   
   result=SpuddeMoveOnGround(mover,&RobotVelocity,&RobotGradientFactor);

   if(result&2)
   {
      if(RobotSpeed>RobotMaxFVel2)
      {
         RobotAnimationFrame=RLVal(0);
         RobotMovementState=RobotKnockDown;
		 RobotFallDownSpin=RLVal(rand()%20-10);
         RobotDistance=0;
         RobotNumMovementFrames=0;
         RobotFallDownDirection.x=dir.x;
         RobotFallDownDirection.y=0;
         RobotFallDownDirection.z=dir.z;
         RobotAnimationState=RobotAcrobatic1;
      }
      else
      {
         RobotMovementState=RobotWaiting;
         RobotAnimationState=RobotPause1;
         RobotDistance = 0;
         RobotSpeed=0;
         
      }
   }
   if(result&1)
   {
      RobotMidair=1;
   }
   RLFrameGetPosition(mover->PositioningFrame,scene,&RobotPosition);
   RobotData.DamageICause = RobotMotionDamage*RobotSpeed/RobotMaxFVel4;
}
static StateFunction RobotBTopSpeed3Function = BAccelerating3Function;
static StateFunction RobotBBrakingFunction = BAccelerating3Function;
static void RobotLAccelerating1Function(MovingObjectData mover)
{
   RLVector   dir;
   int result;
   RLVector up;
   RLValue Distance;
   RLValue DIFFRAME;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   if(SpuddeMapHeight2(mover->CurrentPosition.x,mover->CurrentPosition.z)<sealevel)
      DIFFRAME=RLDivide(DiffFrame,RobotGoopiness);
   else
      DIFFRAME=DiffFrame;

   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);
   RobotSpeed+=RLMultiply(RobotMotions[RobotMovementState].AccelerationValue,DIFFRAME);
   if(RobotSpeed>RobotMotions[RobotMovementState].TopSpeed) RobotSpeed=RobotMotions[RobotMovementState].TopSpeed;
   if(RobotSpeed<0) RobotSpeed=0;
   Distance=RLMultiply(DIFFRAME,RobotSpeed);
   RobotVelocity.x=RLMultiply(dir.z,Distance);
   RobotVelocity.z=RLMultiply(-dir.x,Distance);
   RobotVelocity.y=RLVal(0);
   RobotDistance+=Distance;
//   shithead=fopen("shit.out","a");
//   fprintf(shithead,"in LACC, Distance = %d\n",RobotDistance);
//   fclose(shithead);


   result=SpuddeMoveOnGround(mover,&RobotVelocity,&RobotGradientFactor);

   if(result&2)
   {
      RobotMovementState=RobotWaiting;
      RobotAnimationState=RobotPause1;
      RobotDistance = 0;
      RobotSpeed=0;
   }
   if(result&1)
   {
      RobotMidair=1;
   }
   RLFrameGetPosition(mover->PositioningFrame,scene,&RobotPosition);
   RobotData.DamageICause = RobotMotionDamage*RobotSpeed/RobotMaxFVel4;
}
static StateFunction RobotLTopSpeed1Function = RobotLAccelerating1Function;
static StateFunction RobotLAccelerating2Function = RobotLAccelerating1Function;
static StateFunction RobotLTopSpeed2Function = RobotLAccelerating1Function;
static StateFunction RobotLDeceleratingFunction = RobotLAccelerating1Function;
static StateFunction RobotLBrakingFunction = RobotLAccelerating1Function;
static void RobotRAccelerating1Function(MovingObjectData mover)
{
   int result;
   RLVector   dir;
   RLVector up;
   RLValue Distance;
   RLValue DIFFRAME;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   if(SpuddeMapHeight2(mover->CurrentPosition.x,mover->CurrentPosition.z)<sealevel)
      DIFFRAME=RLDivide(DiffFrame,RobotGoopiness);
   else
      DIFFRAME=DiffFrame;

   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);
   RobotSpeed+=RLMultiply(RobotMotions[RobotMovementState].AccelerationValue,DIFFRAME);
   if(RobotSpeed>RobotMotions[RobotMovementState].TopSpeed) RobotSpeed=RobotMotions[RobotMovementState].TopSpeed;
   if(RobotSpeed<0) RobotSpeed=0;
   Distance=RLMultiply(RobotSpeed,DIFFRAME);
   RobotVelocity.x=RLMultiply(-dir.z,Distance);
   RobotVelocity.z=RLMultiply(dir.x,Distance);
   RobotVelocity.y=RLVal(0);
   RobotDistance+=Distance;
//   shithead=fopen("shit.out","a");
//   fprintf(shithead,"in RACC, Distance = %d\n",RobotDistance);
//   fclose(shithead);


   result=SpuddeMoveOnGround(mover,&RobotVelocity,&RobotGradientFactor);

   if(result&2)
   {
      RobotMovementState=RobotWaiting;
      RobotAnimationState=RobotPause1;
      RobotDistance = 0;
      RobotSpeed=0;
   }
   if(result&1)
   {
      RobotMidair=1;
   }
   RLFrameGetPosition(mover->PositioningFrame,scene,&RobotPosition);
   RobotData.DamageICause = RobotMotionDamage*RobotSpeed/RobotMaxFVel4;
}

static StateFunction RobotRAccelerating2Function = RobotRAccelerating1Function;
static StateFunction RobotRTopSpeed1Function = RobotRAccelerating1Function;
static StateFunction RobotRTopSpeed2Function = RobotRAccelerating1Function;
static StateFunction RobotRDeceleratingFunction = RobotRAccelerating1Function;
static StateFunction RobotRBrakingFunction = RobotRAccelerating1Function;

static void RobotJumpingFunction(MovingObjectData mover)
{
   int result;
//   extern int In3DMovie;

//   int x1,y1,x2,y2,x3,y3;
//   RLValue X1,Y1,Z1,X2,Y2,Z2,X3,Y3,Z3;
//   int bonk;
   RLValue DIFFRAME;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
//   RLVector   dir;
//   RLVector   RobotPosition;
// RLVector RobotVelocity;
//   RLVector up;

//   RLFrameGetPosition(mover,scene,&RobotPosition);
//   RLFrameGetOrientation(mover,scene,&dir,&up);
//   RLVector position;
//   RLFrameGetPosition(mover,RLFrameGetScene(mover),&position);
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   if(mover->CurrentPosition.y<sealevel)
      DIFFRAME=RLDivide(DiffFrame,RobotGoopiness);
   else
      DIFFRAME=DiffFrame;
   if ((GameStates.Is3DMovie && (Ending3DMovie.stage == 7) && (RobotAnimationState==RobotJumpFreeze)))
      RobotYSpeed-=RLMultiply(RobotMotions[RobotMovementState].YAccelerationValue,DIFFRAME);
   else 
      RobotYSpeed+=RLMultiply(RobotMotions[RobotMovementState].YAccelerationValue,DIFFRAME);
//   if(RobotYSpeed>MaxYVel) RobotYSpeed=MaxYVel;
   
//   shithead=fopen("shit.out","a");
//   fprintf(shithead,"YV = %d, YPos = %d\n",RobotYSpeed,position.y);
//   fprintf(shithead,"RobotAnimationFrame = %.3f\n",RLFloat(RobotAnimationFrame));
//   fclose(shithead);
//   if(RobotYSpeed>RobotMotions[RobotMovementState].TopYSpeed) RobotYSpeed=RobotMotions[RobotMovementState].TopYSpeed;
//   if(RobotYSpeed<0) RobotYSpeed=0;
//   RobotVelocity.x=RLMultiply(dir.x,RobotSpeed);
//   RobotVelocity.z=RLMultiply(dir.z,RobotSpeed);
   RobotVelocity.y=RLMultiply(RobotYSpeed,DIFFRAME);
   RobotHitObstacle=0;
   RobotMidair=0;
   result=SpuddeMoveInAir(mover,&RobotVelocity);
   if(result&2)
   {
      RobotHitObstacle=1;
      RobotSpeed=0;
      RobotYSpeed=0;
   }
   if(result&1)
   {                                                     
      RobotMidair=1;
   }
   RLFrameGetPosition(mover->PositioningFrame,scene,&RobotPosition);

}
static StateFunction RobotAirborneFunction = RobotJumpingFunction;
static StateFunction RobotSlideDownBuildingSideFunction = RobotJumpingFunction;
static void RobotStoppedFunction(MovingObjectData mover)
{
   RLFrame Scene=RLFrameGetScene(mover->PositioningFrame);
   RLFrameSetPosition(mover->PositioningFrame,Scene,RobotPosition.x,RobotPosition.y,RobotPosition.z);
}

static StateFunction RobotStoppedOnBuildingFunction=RobotStoppedFunction;

static void RobotKnockDownFunction(MovingObjectData mover)
{
   RLVector   dir;
   int result;
   RLVector newdir;
   RLVector up;
   RLValue Distance;
   RLValue DIFFRAME;
//   FILE *shithead;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   if(SpuddeMapHeight2(mover->CurrentPosition.x,mover->CurrentPosition.z)<sealevel)
      DIFFRAME=RLDivide(DiffFrame,RobotGoopiness);
   else
      DIFFRAME=DiffFrame;

   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);

   if(RobotTheta>0)
   {
      RobotTurning=1;
	  RobotTheta -=(RLMultiply(DiffFrame,RobotTurnAcceleration));
	  if(RobotTheta< 0)
	  {
		  RobotTheta = 0;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.x);

      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLMultiply(-RobotTurnRate,DIFFRAME));
   }
   else if( RobotTheta<0)
   {
      RobotTurning=-1;
	  RobotTheta +=(RLMultiply(DiffFrame,RobotTurnAcceleration));
	  if(RobotTheta > 0)
	  {
		  RobotTheta = 0;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLMultiply(RobotTurnRate,DIFFRAME));
   }
   else
   {
      RobotTurning=0;
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLVal(0));
   }




//   printf("I'm in Robotknockdownfunction\n");
   //RobotSpeed=RobotKnockBackSpeed;
//   RLFrameGetOrientation(mover,scene,&dir,&up);
   Distance=RLMultiply(RobotSpeed,DIFFRAME);
   //RobotVelocity.x=RLMultiply(RobotFallDownDirection.x,Distance);
   //RobotVelocity.z=RLMultiply(RobotFallDownDirection.z,Distance);
   RLVectorScale(&RobotVelocity, &RobotFallDownDirection, DIFFRAME);
   RobotVelocity.y=RLVal(0);
//   shithead=fopen("shit.out","a");
//   fprintf(shithead,"dir = %.2f, %.2f, %.2f\n",dir.x,dir.y,dir.z);
//   fprintf(shithead,"FallDownDirection = %.2f, %.2f, %.2f\n",RobotFallDownDirection.x,RobotFallDownDirection.y,RobotFallDownDirection.z);
//   fprintf(shithead,"RobotSpeed = %f, Distance = %f\n",RobotSpeed,DIFFRAME);
//   fclose(shithead);
   RobotDistance+=Distance;
   RLVectorScale(&RobotFallDownDirection, &RobotFallDownDirection, RLVal(1.0) - RLMultiply(RLVal(RobotSlidingFriction), DiffFrame));

   result=SpuddeMoveOnGround(mover,&RobotVelocity,&RobotGradientFactor);

   if(result&2)
   {
//      RobotAnimationFrame=RLVal(0);
      RobotMovementState=RobotKnockDown;
		 RobotFallDownSpin=RLVal(rand()%20-10);
//      RobotDistance=0;
//      RobotNumMovementFrames=0;
      RobotFallDownDirection.x=-RobotFallDownDirection.x;
      RobotFallDownDirection.y=0;
      RobotFallDownDirection.z=-RobotFallDownDirection.z;
      if(RobotAnimationState==RobotAcrobatic2)
         RobotAnimationState==RobotAcrobatic1;
      else
         RobotAnimationState==RobotAcrobatic2;
   }
   if(result&1)
   {
      RobotMidair=1;
   }
//   printf("I'm leaving Robotknockdownfunction\n");
   RLFrameGetPosition(mover->PositioningFrame,scene,&RobotPosition);
   RobotData.DamageICause = 0;
}

static void RobotKnockDownOnBuildingFunction(MovingObjectData mover)
{
   RLVector   dir;
//   int result;
   RLVector newdir;
   RLVector up;
   RLValue Distance;
   RLValue DIFFRAME;
   RLValue NextRobotDistance;
   RLValue X2,Z2,Y2;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   if(SpuddeMapHeight2(mover->CurrentPosition.x,mover->CurrentPosition.z)<sealevel)
      DIFFRAME=RLDivide(DiffFrame,RobotGoopiness);
   else
      DIFFRAME=DiffFrame;
   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);
   if(RobotTheta>0)
   {
      RobotTurning=1;
	  RobotTheta -=(RLMultiply(DiffFrame,RobotTurnAcceleration));
	  if(RobotTheta< 0)
	  {
		  RobotTheta = 0;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.x);

      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLMultiply(-RobotTurnRate,DIFFRAME));
   }
   else if( RobotTheta<0)
   {
      RobotTurning=-1;
	  RobotTheta +=(RLMultiply(DiffFrame,RobotTurnAcceleration));
	  if(RobotTheta > 0)
	  {
		  RobotTheta = 0;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(RobotTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(RobotTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLMultiply(RobotTurnRate,DIFFRAME));
   }
   else
   {
      RobotTurning=0;
      //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLVal(0));
   }

   RobotSpeed=RobotKnockBackSpeed;

   Distance=RLMultiply(RobotSpeed,DIFFRAME);
   RobotVelocity.x=RLMultiply(RobotFallDownDirection.x,Distance);
   RobotVelocity.z=RLMultiply(RobotFallDownDirection.z,Distance);
   RobotVelocity.y=RLVal(0);
   
   NextRobotDistance = RobotDistance+Distance;
//   if((RobotDistance<DestructionDistance && NextRobotDistance>=DestructionDistance) ||
//      (RobotDistance<HalfDestructionDistance && NextRobotDistance>=HalfDestructionDistance))
//   {
//      RobotBuilding->cur_damage += mover->DamageICause/5 + 1;
//   }
   RobotVelocity.y=RLVal(0);

   X2=mover->CurrentPosition.x+RobotVelocity.x;
   Z2=mover->CurrentPosition.z+RobotVelocity.z;
   if(X2>landbox.max.x)
      X2=landbox.max.x;
   if(X2<landbox.min.x)
      X2=landbox.min.x;
   if(Z2<landbox.min.z)
      Z2=landbox.min.z;
   if(Z2>landbox.max.z)
      Z2=landbox.max.z;
   Y2=mover->CurrentPosition.y;

   if(X2>RobotBuilding->building.max.x ||
      X2<RobotBuilding->building.min.x ||
      Z2>RobotBuilding->building.max.z ||
      Z2<RobotBuilding->building.min.z )

   {
      RobotMovementState=RobotAirborne;
	  RobotAnimationState=RobotJumpFreeze;
	  RobotMidair=1;
      RobotOnBuilding=0;
      RobotDistance = 0;
   }
   RLFrameGetPosition(mover->PositioningFrame,scene,&RobotPosition);
   mover->ProjectedPosition.x=X2;
   mover->ProjectedPosition.y=Y2;
   mover->ProjectedPosition.z=Z2;
   RobotData.DamageICause = 0;
}


void churn(MovingObjectData mover)
{
   int i;
//   char OutputString[128];
  // sprintf(OutputString,"Movement Number %d\n",RobotMovementState);
//   OutputDebugString(OutputString);
   RobotEngy-=RobotMotions[RobotMovementState].EnergyDrain;
   (RobotMotions[RobotMovementState].WhatToDo)(mover);
   RobotNumMovementFrames++;

   for(i=0;(i<RobotMotions[RobotMovementState].numchanges) ;i++ )
      if(  (RobotMotions[RobotMovementState].ChangeList[i]) () )
         i=RobotMotions[RobotMovementState].numchanges;
}
#ifdef PC
void GetRobotMovementInfo(FILE *input)
{
#ifdef ErrorsOut

	FILE *errors;
#endif
	char decision[1];
   char movename[64];
   char dumstring[256];
#ifdef ErrorsOut
   errors=fopen("error.out","w");
   fprintf(errors,"getting Robot movement info.\n");
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
            if(!stricmp("RobotGradientFactor",movename))
            {
               fscanf(input," %f",&RobotGradientFactor);
            }
            else if(!stricmp("RobotFAcc1",movename))
            {
               fscanf(input," %f",&RobotFAcc1);
            }
            else if(!stricmp("RobotMaxFVel1",movename))
            {
               fscanf(input," %f",&RobotMaxFVel1);
            }
            else if(!stricmp("RobotFAcc2",movename))
            {
               fscanf(input," %f",&RobotFAcc2);
            }
            else if(!stricmp("RobotFAcc3",movename))
            {
               fscanf(input," %f",&RobotFAcc3);
            }
            else if(!stricmp("RobotFAcc4",movename))
            {
               fscanf(input," %f",&RobotFAcc4);
            }
            else if(!stricmp("RobotMaxFVel2",movename))
            {
               fscanf(input," %f",&RobotMaxFVel2);
            }
            else if(!stricmp("RobotMaxFVel3",movename))
            {
               fscanf(input," %f",&RobotMaxFVel3);
            }
            else if(!stricmp("RobotMaxFVel4",movename))
            {
               fscanf(input," %f",&RobotMaxFVel4);
            }
            else if(!stricmp("RobotFDecel",movename))
            {
               fscanf(input," %f",&RobotFDecel);
            }
            else if(!stricmp("RobotFBrake",movename))
            {
               fscanf(input," %f",&RobotFBrake);
            }
            else if(!stricmp("RobotBAcc1",movename))
            {
               fscanf(input," %f",&RobotBAcc1);
            }
            else if(!stricmp("RobotBAcc2",movename))
            {
               fscanf(input," %f",&RobotBAcc2);
            }
            else if(!stricmp("RobotBAcc3",movename))
            {
               fscanf(input," %f",&RobotBAcc3);
            }
            else if(!stricmp("RobotMaxBVel1",movename))
            {
               fscanf(input," %f",&RobotMaxBVel1);
            }
            else if(!stricmp("RobotMaxBVel2",movename))
            {
               fscanf(input," %f",&RobotMaxBVel2);
            }
            else if(!stricmp("RobotMaxBVel3",movename))
            {
               fscanf(input," %f",&RobotMaxBVel3);
            }
            else if(!stricmp("RobotBDecel",movename))
            {
               fscanf(input," %f",&RobotBDecel);
            }
            else if(!stricmp("RobotBBrake",movename))
            {
               fscanf(input," %f",&RobotBBrake);
            }
            else if(!stricmp("RobotLAcc1",movename))
            {
               fscanf(input," %f",&RobotLAcc1);
            }
            else if(!stricmp("RobotLAcc2",movename))
            {
               fscanf(input," %f",&RobotLAcc2);
            }
            else if(!stricmp("RobotMaxLVel1",movename))
            {
               fscanf(input," %f",&RobotMaxLVel1);
            }
            else if(!stricmp("RobotMaxLVel2",movename))
            {
               fscanf(input," %f",&RobotMaxLVel2);
            }
            else if(!stricmp("RobotLDecel",movename))
            {
               fscanf(input," %f",&RobotLDecel);
            }
            else if(!stricmp("RobotLBrake",movename))
            {
               fscanf(input," %f",&RobotLBrake);
            }
            else if(!stricmp("RobotRAcc1",movename))
            {
               fscanf(input," %f",&RobotRAcc1);
            }
            else if(!stricmp("RobotRAcc2",movename))
            {
               fscanf(input," %f",&RobotRAcc2);
            }
            else if(!stricmp("RobotMaxRVel1",movename))
            {
               fscanf(input," %f",&RobotMaxRVel1);
            }
            else if(!stricmp("RobotMaxRVel2",movename))
            {
               fscanf(input," %f",&RobotMaxRVel2);
            }
            else if(!stricmp("RobotRDecel",movename))
            {
               fscanf(input," %f",&RobotRDecel);
            }
            else if(!stricmp("RobotRBrake",movename))
            {
               fscanf(input," %f",&RobotRBrake);
            }
//            else if(!stricmp("RobotTurnRate",movename))
  //          {
    //           fscanf(input," %f",&RobotTurnRate);
      //      }
            else if(!stricmp("RobotGravity",movename))
            {
               fscanf(input," %f",&RobotGravity);
            }
            else if(!stricmp("RobotJumpYAcc",movename))
            {
               fscanf(input," %f",&RobotJumpYAcc);
            }
//            else if(!stricmp("RobotNumFramesBackTravel",movename))
//            {
//               fscanf(input," %d",&RobotNumFramesBackTravel);
//            }
//            else if(!stricmp("RobotNumFramesSideTravel",movename))
//            {
//               fscanf(input," %d",&RobotNumFramesSideTravel);
//            }
            else if(!stricmp("MaxYVel",movename))
            {
               fscanf(input," %f",&MaxYVel);
            }
            else if(!stricmp("RobotTurnMaximum",movename))
            {
               fscanf(input," %f",&RobotTurnMaximum);
            }
            else if(!stricmp("RobotTurnAcceleration",movename))
            {
               fscanf(input," %f",&RobotTurnAcceleration);
            }
//            else if(!stricmp("RobotCosine",movename))
//            {
//               fscanf(input," %*f");
//            }
//            else if(!stricmp("RobotSine",movename))
//            {
//               fscanf(input," %*f");
//            }
            else if(!stricmp("RobotKnockBackSpeed",movename))
            {
               fscanf(input," %f",&RobotKnockBackSpeed);
            }
            else if(!stricmp("RobotGoopiness",movename))
            {
               fscanf(input," %f",&RobotGoopiness);
            }
            else if(!stricmp("RobotWaitingEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotWaitingEnergyDrain);
            }
            else if(!stricmp("RobotFAccelerating1EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotFAccelerating1EnergyDrain);
            }
            else if(!stricmp("RobotFAccelerating2EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotFAccelerating2EnergyDrain);
            }
            else if(!stricmp("RobotFAccelerating3EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotFAccelerating3EnergyDrain);
            }
            else if(!stricmp("RobotFAccelerating4EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotFAccelerating4EnergyDrain);
            }
            else if(!stricmp("RobotFTopSpeed1EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotFTopSpeed1EnergyDrain);
            }
            else if(!stricmp("RobotFTopSpeed2EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotFTopSpeed2EnergyDrain);
            }
            else if(!stricmp("RobotFTopSpeed3EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotFTopSpeed3EnergyDrain);
            }
            else if(!stricmp("RobotFTopSpeed4EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotFTopSpeed4EnergyDrain);
            }
            else if(!stricmp("RobotFDeceleratingEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotFDeceleratingEnergyDrain);
            }
            else if(!stricmp("RobotFBrakingEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotFBrakingEnergyDrain);
            }
            else if(!stricmp("RobotBAccelerating1EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotBAccelerating1EnergyDrain);
            }
            else if(!stricmp("RobotBAccelerating2EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotBAccelerating2EnergyDrain);
            }
            else if(!stricmp("RobotBTopSpeed1EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotBTopSpeed1EnergyDrain);
            }
            else if(!stricmp("RobotBTopSpeed2EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotBTopSpeed2EnergyDrain);
            }
            else if(!stricmp("RobotBDeceleratingEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotBDeceleratingEnergyDrain);
            }
            else if(!stricmp("RobotBAccelerating3EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotBAccelerating3EnergyDrain);
            }
            else if(!stricmp("RobotBTopSpeed3EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotBTopSpeed3EnergyDrain);
            }
            else if(!stricmp("RobotBBrakingEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotBBrakingEnergyDrain);
            }
            else if(!stricmp("RobotLAccelerating1EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotLAccelerating1EnergyDrain);
            }
            else if(!stricmp("RobotLAccelerating2EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotLAccelerating2EnergyDrain);
            }
            else if(!stricmp("RobotLTopSpeed1EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotLTopSpeed1EnergyDrain);
            }
            else if(!stricmp("RobotLTopSpeed2EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotLTopSpeed2EnergyDrain);
            }
            else if(!stricmp("RobotLDeceleratingEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotLDeceleratingEnergyDrain);
            }
            else if(!stricmp("RobotLBrakingEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotLBrakingEnergyDrain);
            }
            else if(!stricmp("RobotRAccelerating1EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotRAccelerating1EnergyDrain);
            }
            else if(!stricmp("RobotRAccelerating2EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotRAccelerating2EnergyDrain);
            }
            else if(!stricmp("RobotRTopSpeed1EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotRTopSpeed1EnergyDrain);
            }
            else if(!stricmp("RobotRTopSpeed2EnergyDrain",movename))
            {
               fscanf(input," %d",&RobotRTopSpeed2EnergyDrain);
            }
            else if(!stricmp("RobotRDeceleratingEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotRDeceleratingEnergyDrain);
            }
            else if(!stricmp("RobotRBrakingEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotRBrakingEnergyDrain);
            }
            else if(!stricmp("RobotJumpingEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotJumpingEnergyDrain);
            }
            else if(!stricmp("RobotAirborneEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotAirborneEnergyDrain);
            }
            else if(!stricmp("RobotStoppedEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotStoppedEnergyDrain);
            }
            else if(!stricmp("RobotKnockDownEnergyDrain",movename))
            {
               fscanf(input," %d",&RobotKnockDownEnergyDrain);
            }
            else if(!stricmp("RobotWaitingMinEnergy",movename))
            {
               fscanf(input," %d",&RobotWaitingMinEnergy);
            }
            else if(!stricmp("RobotFAccelerating1MinEnergy",movename))
            {
               fscanf(input," %d",&RobotFAccelerating1MinEnergy);
            }
            else if(!stricmp("RobotFAccelerating2MinEnergy",movename))
            {
               fscanf(input," %d",&RobotFAccelerating2MinEnergy);
            }
            else if(!stricmp("RobotFAccelerating3MinEnergy",movename))
            {
               fscanf(input," %d",&RobotFAccelerating3MinEnergy);
            }
            else if(!stricmp("RobotFAccelerating4MinEnergy",movename))
            {
               fscanf(input," %d",&RobotFAccelerating4MinEnergy);
            }
            else if(!stricmp("RobotFTopSpeed1MinEnergy",movename))
            {
               fscanf(input," %d",&RobotFTopSpeed1MinEnergy);
            }
            else if(!stricmp("RobotFTopSpeed2MinEnergy",movename))
            {
               fscanf(input," %d",&RobotFTopSpeed2MinEnergy);
            }
            else if(!stricmp("RobotFTopSpeed3MinEnergy",movename))
            {
               fscanf(input," %d",&RobotFTopSpeed3MinEnergy);
            }
            else if(!stricmp("RobotFTopSpeed4MinEnergy",movename))
            {
               fscanf(input," %d",&RobotFTopSpeed4MinEnergy);
            }
            else if(!stricmp("RobotFDeceleratingMinEnergy",movename))
            {
               fscanf(input," %d",&RobotFDeceleratingMinEnergy);
            }
            else if(!stricmp("RobotFBrakingMinEnergy",movename))
            {
               fscanf(input," %d",&RobotFBrakingMinEnergy);
            }
            else if(!stricmp("RobotBAccelerating1MinEnergy",movename))
            {
               fscanf(input," %d",&RobotBAccelerating1MinEnergy);
            }
            else if(!stricmp("RobotBAccelerating2MinEnergy",movename))
            {
               fscanf(input," %d",&RobotBAccelerating2MinEnergy);
            }
            else if(!stricmp("RobotBTopSpeed1MinEnergy",movename))
            {
               fscanf(input," %d",&RobotBTopSpeed1MinEnergy);
            }
            else if(!stricmp("RobotBTopSpeed2MinEnergy",movename))
            {
               fscanf(input," %d",&RobotBTopSpeed2MinEnergy);
            }
            else if(!stricmp("RobotBDeceleratingMinEnergy",movename))
            {
               fscanf(input," %d",&RobotBDeceleratingMinEnergy);
            }
            else if(!stricmp("RobotBAccelerating3MinEnergy",movename))
            {
               fscanf(input," %d",&RobotBAccelerating3MinEnergy);
            }
            else if(!stricmp("RobotBTopSpeed3MinEnergy",movename))
            {
               fscanf(input," %d",&RobotBTopSpeed3MinEnergy);
            }
            else if(!stricmp("RobotBBrakingMinEnergy",movename))
            {
               fscanf(input," %d",&RobotBBrakingMinEnergy);
            }
            else if(!stricmp("RobotLAccelerating1MinEnergy",movename))
            {
               fscanf(input," %d",&RobotLAccelerating1MinEnergy);
            }
            else if(!stricmp("RobotLAccelerating2MinEnergy",movename))
            {
               fscanf(input," %d",&RobotLAccelerating2MinEnergy);
            }
            else if(!stricmp("RobotLTopSpeed1MinEnergy",movename))
            {
               fscanf(input," %d",&RobotLTopSpeed1MinEnergy);
            }
            else if(!stricmp("RobotLTopSpeed2MinEnergy",movename))
            {
               fscanf(input," %d",&RobotLTopSpeed2MinEnergy);
            }
            else if(!stricmp("RobotLDeceleratingMinEnergy",movename))
            {
               fscanf(input," %d",&RobotLDeceleratingMinEnergy);
            }
            else if(!stricmp("RobotLBrakingMinEnergy",movename))
            {
               fscanf(input," %d",&RobotLBrakingMinEnergy);
            }
            else if(!stricmp("RobotRAccelerating1MinEnergy",movename))
            {
               fscanf(input," %d",&RobotRAccelerating1MinEnergy);
            }
            else if(!stricmp("RobotRAccelerating2MinEnergy",movename))
            {
               fscanf(input," %d",&RobotRAccelerating2MinEnergy);
            }
            else if(!stricmp("RobotRTopSpeed1MinEnergy",movename))
            {
               fscanf(input," %d",&RobotRTopSpeed1MinEnergy);
            }
            else if(!stricmp("RobotRTopSpeed2MinEnergy",movename))
            {
               fscanf(input," %d",&RobotRTopSpeed2MinEnergy);
            }
            else if(!stricmp("RobotRDeceleratingMinEnergy",movename))
            {
               fscanf(input," %d",&RobotRDeceleratingMinEnergy);
            }
            else if(!stricmp("RobotRBrakingMinEnergy",movename))
            {
               fscanf(input," %d",&RobotRBrakingMinEnergy);
            }
            else if(!stricmp("RobotJumpingMinEnergy",movename))
            {
               fscanf(input," %d",&RobotJumpingMinEnergy);
            }
            else if(!stricmp("RobotAirborneMinEnergy",movename))
            {
               fscanf(input," %d",&RobotAirborneMinEnergy);
            }
            else if(!stricmp("RobotStoppedMinEnergy",movename))
            {
               fscanf(input," %d",&RobotStoppedMinEnergy);
            }
            else if(!stricmp("RobotKnockDownMinEnergy",movename))
            {
               fscanf(input," %d",&RobotKnockDownMinEnergy);
            }
            else if(!stricmp("RobotMotionDamage",movename))
            {
               fscanf(input," %d",&RobotMotionDamage);
            }
            else if(!stricmp("RobotMass",movename))
            {
               extern struct _moving_object_data_ RobotData;
               fscanf(input," %f",&(RobotData.mass));
            }
            else if(!stricmp("RobotHomerMass",movename))
            {
               extern struct _moving_object_data_ RobotHomerData;
               fscanf(input," %f",&RobotHomerData.mass);
            }
            else if(!stricmp("RobotSpinMultiplier",movename))
            {
               fscanf(input," %f",&RobotSpinMultiplier);
            }
            else if(!stricmp("RobotSlidingFriction",movename))
            {
               fscanf(input," %f",&RobotSlidingFriction);
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
#endif

void DefineRobotMotionConstants()
{
//   int i;
//#ifdef PC   
//   FILE * input;
//   input=fopen("Robotdef.dat","rt");
//   if(input) GetRobotMovementInfo(input);
//   if(input) fclose(input);
//#endif
//   for(i=1;i<11;i++)
  // {
    //  RobotSineTable[i-1]=sin(i*RobotTheta);
      //RobotCosineTable[i-1]=cos(i*RobotTheta);
   //}

   RobotMotions[RobotWaiting].AccelerationValue=0;
   RobotMotions[RobotWaiting].YAccelerationValue=0;
   RobotMotions[RobotWaiting].TopSpeed=0;
   RobotMotions[RobotWaiting].TopYSpeed=0;
   RobotMotions[RobotWaiting].EnergyDrain=RobotWaitingEnergyDrain;

   RobotMotions[RobotFAccelerating1].AccelerationValue=RobotFAcc1;
   RobotMotions[RobotFAccelerating1].YAccelerationValue=0;
   RobotMotions[RobotFAccelerating1].TopSpeed=RobotMaxFVel1;
   RobotMotions[RobotFAccelerating1].TopYSpeed=0;
   RobotMotions[RobotFAccelerating1].EnergyDrain=RobotFAccelerating1EnergyDrain;

   RobotMotions[RobotFAccelerating2].AccelerationValue=RobotFAcc2;
   RobotMotions[RobotFAccelerating2].YAccelerationValue=0;
   RobotMotions[RobotFAccelerating2].TopSpeed=RobotMaxFVel2;
   RobotMotions[RobotFAccelerating2].TopYSpeed=0;
   RobotMotions[RobotFAccelerating2].EnergyDrain=RobotFAccelerating2EnergyDrain;

   RobotMotions[RobotFAccelerating3].AccelerationValue=RobotFAcc3;
   RobotMotions[RobotFAccelerating3].YAccelerationValue=0;
   RobotMotions[RobotFAccelerating3].TopSpeed=RobotMaxFVel3;
   RobotMotions[RobotFAccelerating3].TopYSpeed=0;
   RobotMotions[RobotFAccelerating3].EnergyDrain=RobotFAccelerating3EnergyDrain;

   RobotMotions[RobotFAccelerating4].AccelerationValue=RobotFAcc4;
   RobotMotions[RobotFAccelerating4].YAccelerationValue=0;
   RobotMotions[RobotFAccelerating4].TopSpeed=RobotMaxFVel4;
   RobotMotions[RobotFAccelerating4].TopYSpeed=0;
   RobotMotions[RobotFAccelerating4].EnergyDrain=RobotFAccelerating4EnergyDrain;

   RobotMotions[RobotFTopSpeed1].AccelerationValue=0;
   RobotMotions[RobotFTopSpeed1].YAccelerationValue=0;
   RobotMotions[RobotFTopSpeed1].TopSpeed=RobotMaxFVel1;
   RobotMotions[RobotFTopSpeed1].TopYSpeed=0;
   RobotMotions[RobotFTopSpeed1].EnergyDrain=RobotFTopSpeed1EnergyDrain;

   RobotMotions[RobotFTopSpeed2].AccelerationValue=0;
   RobotMotions[RobotFTopSpeed2].YAccelerationValue=0;
   RobotMotions[RobotFTopSpeed2].TopSpeed=RobotMaxFVel2;
   RobotMotions[RobotFTopSpeed2].TopYSpeed=0;
   RobotMotions[RobotFTopSpeed2].EnergyDrain=RobotFTopSpeed2EnergyDrain;

   RobotMotions[RobotFTopSpeed3].AccelerationValue=0;
   RobotMotions[RobotFTopSpeed3].YAccelerationValue=0;
   RobotMotions[RobotFTopSpeed3].TopSpeed=RobotMaxFVel3;
   RobotMotions[RobotFTopSpeed3].TopYSpeed=0;
   RobotMotions[RobotFTopSpeed3].EnergyDrain=RobotFTopSpeed3EnergyDrain;

   RobotMotions[RobotFTopSpeed4].AccelerationValue=0;
   RobotMotions[RobotFTopSpeed4].YAccelerationValue=0;
   RobotMotions[RobotFTopSpeed4].TopSpeed=RobotMaxFVel4;
   RobotMotions[RobotFTopSpeed4].TopYSpeed=0;
   RobotMotions[RobotFTopSpeed4].EnergyDrain=RobotFTopSpeed4EnergyDrain;

   RobotMotions[RobotFDecelerating].AccelerationValue=RobotFDecel;
   RobotMotions[RobotFDecelerating].YAccelerationValue=0;
   RobotMotions[RobotFDecelerating].TopSpeed=RobotMaxFVel3;
   RobotMotions[RobotFDecelerating].TopYSpeed=0;
   RobotMotions[RobotFDecelerating].EnergyDrain=RobotFDeceleratingEnergyDrain;

   RobotMotions[RobotFBraking].AccelerationValue=RobotFBrake;
   RobotMotions[RobotFBraking].YAccelerationValue=0;
   RobotMotions[RobotFBraking].TopSpeed=RobotMaxFVel4;
   RobotMotions[RobotFBraking].TopYSpeed=0;
   RobotMotions[RobotFBraking].EnergyDrain=RobotFBrakingEnergyDrain;

   RobotMotions[RobotBAccelerating1].AccelerationValue=RobotBAcc1;
   RobotMotions[RobotBAccelerating1].YAccelerationValue=0;
   RobotMotions[RobotBAccelerating1].TopSpeed=RobotMaxBVel1;
   RobotMotions[RobotBAccelerating1].TopYSpeed=0;
   RobotMotions[RobotBAccelerating1].EnergyDrain=RobotBAccelerating1EnergyDrain;

   RobotMotions[RobotBAccelerating2].AccelerationValue=RobotBAcc2;
   RobotMotions[RobotBAccelerating2].YAccelerationValue=0;
   RobotMotions[RobotBAccelerating2].TopSpeed=RobotMaxBVel2;
   RobotMotions[RobotBAccelerating2].TopYSpeed=0;
   RobotMotions[RobotBAccelerating2].EnergyDrain=RobotBAccelerating2EnergyDrain;

   RobotMotions[RobotBAccelerating3].AccelerationValue=RobotBAcc3;
   RobotMotions[RobotBAccelerating3].YAccelerationValue=0;
   RobotMotions[RobotBAccelerating3].TopSpeed=RobotMaxBVel3;
   RobotMotions[RobotBAccelerating3].TopYSpeed=0;
   RobotMotions[RobotBAccelerating3].EnergyDrain=RobotBAccelerating3EnergyDrain;

   RobotMotions[RobotBTopSpeed1].AccelerationValue=0;
   RobotMotions[RobotBTopSpeed1].YAccelerationValue=0;
   RobotMotions[RobotBTopSpeed1].TopSpeed=RobotMaxBVel1;
   RobotMotions[RobotBTopSpeed1].TopYSpeed=0;
   RobotMotions[RobotBTopSpeed1].EnergyDrain=RobotBTopSpeed1EnergyDrain;

   RobotMotions[RobotBTopSpeed2].AccelerationValue=0;
   RobotMotions[RobotBTopSpeed2].YAccelerationValue=0;
   RobotMotions[RobotBTopSpeed2].TopSpeed=RobotMaxBVel2;
   RobotMotions[RobotBTopSpeed2].TopYSpeed=0;
   RobotMotions[RobotBTopSpeed2].EnergyDrain=RobotBTopSpeed2EnergyDrain;

   RobotMotions[RobotBTopSpeed3].AccelerationValue=0;
   RobotMotions[RobotBTopSpeed3].YAccelerationValue=0;
   RobotMotions[RobotBTopSpeed3].TopSpeed=RobotMaxBVel3;
   RobotMotions[RobotBTopSpeed3].TopYSpeed=0;
   RobotMotions[RobotBTopSpeed3].EnergyDrain=RobotBTopSpeed3EnergyDrain;

   RobotMotions[RobotBDecelerating].AccelerationValue=RobotBDecel;
   RobotMotions[RobotBDecelerating].YAccelerationValue=0;
   RobotMotions[RobotBDecelerating].TopSpeed=RobotMaxBVel2;
   RobotMotions[RobotBDecelerating].TopYSpeed=0;
   RobotMotions[RobotBDecelerating].EnergyDrain=RobotBDeceleratingEnergyDrain;

   RobotMotions[RobotBBraking].AccelerationValue=RobotBBrake;
   RobotMotions[RobotBBraking].YAccelerationValue=0;
   RobotMotions[RobotBBraking].TopSpeed=RobotMaxBVel3;
   RobotMotions[RobotBBraking].TopYSpeed=0;
   RobotMotions[RobotBBraking].EnergyDrain=RobotBBrakingEnergyDrain;

   RobotMotions[RobotLAccelerating1].AccelerationValue=RobotLAcc1;
   RobotMotions[RobotLAccelerating1].YAccelerationValue=0;
   RobotMotions[RobotLAccelerating1].TopSpeed=RobotMaxLVel1;
   RobotMotions[RobotLAccelerating1].TopYSpeed=0;
   RobotMotions[RobotLAccelerating1].EnergyDrain=RobotLAccelerating1EnergyDrain;

   RobotMotions[RobotLAccelerating2].AccelerationValue=RobotLAcc2;
   RobotMotions[RobotLAccelerating2].YAccelerationValue=0;
   RobotMotions[RobotLAccelerating2].TopSpeed=RobotMaxLVel2;
   RobotMotions[RobotLAccelerating2].TopYSpeed=0;
   RobotMotions[RobotLAccelerating2].EnergyDrain=RobotLAccelerating2EnergyDrain;

   RobotMotions[RobotLTopSpeed1].AccelerationValue=0;
   RobotMotions[RobotLTopSpeed1].YAccelerationValue=0;
   RobotMotions[RobotLTopSpeed1].TopSpeed=RobotMaxLVel1;
   RobotMotions[RobotLTopSpeed1].TopYSpeed=0;
   RobotMotions[RobotLTopSpeed1].EnergyDrain=RobotLTopSpeed1EnergyDrain;

   RobotMotions[RobotLTopSpeed2].AccelerationValue=0;
   RobotMotions[RobotLTopSpeed2].YAccelerationValue=0;
   RobotMotions[RobotLTopSpeed2].TopSpeed=RobotMaxLVel2;
   RobotMotions[RobotLTopSpeed2].TopYSpeed=0;
   RobotMotions[RobotLTopSpeed2].EnergyDrain=RobotLTopSpeed2EnergyDrain;

   RobotMotions[RobotLDecelerating].AccelerationValue=RobotLDecel;
   RobotMotions[RobotLDecelerating].YAccelerationValue=0;
   RobotMotions[RobotLDecelerating].TopSpeed=RobotMaxLVel1;
   RobotMotions[RobotLDecelerating].TopYSpeed=0;
   RobotMotions[RobotLDecelerating].EnergyDrain=RobotLDeceleratingEnergyDrain;

   RobotMotions[RobotLBraking].AccelerationValue=RobotLBrake;
   RobotMotions[RobotLBraking].YAccelerationValue=0;
   RobotMotions[RobotLBraking].TopSpeed=RobotMaxLVel2;
   RobotMotions[RobotLBraking].TopYSpeed=0;
   RobotMotions[RobotLBraking].EnergyDrain=RobotLBrakingEnergyDrain;

   RobotMotions[RobotRAccelerating1].AccelerationValue=RobotRAcc1;
   RobotMotions[RobotRAccelerating1].YAccelerationValue=0;
   RobotMotions[RobotRAccelerating1].TopSpeed=RobotMaxRVel1;
   RobotMotions[RobotRAccelerating1].TopYSpeed=0;
   RobotMotions[RobotRAccelerating1].EnergyDrain=RobotRAccelerating1EnergyDrain;

   RobotMotions[RobotRAccelerating2].AccelerationValue=RobotRAcc2;
   RobotMotions[RobotRAccelerating2].YAccelerationValue=0;
   RobotMotions[RobotRAccelerating2].TopSpeed=RobotMaxRVel2;
   RobotMotions[RobotRAccelerating2].TopYSpeed=0;
   RobotMotions[RobotRAccelerating2].EnergyDrain=RobotRAccelerating2EnergyDrain;

   RobotMotions[RobotRTopSpeed1].AccelerationValue=0;
   RobotMotions[RobotRTopSpeed1].YAccelerationValue=0;
   RobotMotions[RobotRTopSpeed1].TopSpeed=RobotMaxRVel1;
   RobotMotions[RobotRTopSpeed1].TopYSpeed=0;
   RobotMotions[RobotRTopSpeed1].EnergyDrain=RobotRTopSpeed1EnergyDrain;

   RobotMotions[RobotRTopSpeed2].AccelerationValue=0;
   RobotMotions[RobotRTopSpeed2].YAccelerationValue=0;
   RobotMotions[RobotRTopSpeed2].TopSpeed=RobotMaxRVel2;
   RobotMotions[RobotRTopSpeed2].TopYSpeed=0;
   RobotMotions[RobotRTopSpeed2].EnergyDrain=RobotRTopSpeed2EnergyDrain;

   RobotMotions[RobotRDecelerating].AccelerationValue=RobotRDecel;
   RobotMotions[RobotRDecelerating].YAccelerationValue=0;
   RobotMotions[RobotRDecelerating].TopSpeed=RobotMaxRVel1;
   RobotMotions[RobotRDecelerating].TopYSpeed=0;
   RobotMotions[RobotRDecelerating].EnergyDrain=RobotRDeceleratingEnergyDrain;

   RobotMotions[RobotRBraking].AccelerationValue=RobotRBrake;
   RobotMotions[RobotRBraking].YAccelerationValue=0;
   RobotMotions[RobotRBraking].TopSpeed=RobotMaxRVel2;
   RobotMotions[RobotRBraking].TopYSpeed=0;
   RobotMotions[RobotRBraking].EnergyDrain=RobotRBrakingEnergyDrain;

   RobotMotions[RobotJumping].AccelerationValue=0;
   RobotMotions[RobotJumping].YAccelerationValue=RobotJumpYAcc;
   RobotMotions[RobotJumping].TopSpeed=RobotMaxFVel4;
   RobotMotions[RobotJumping].TopYSpeed= MaxYVel;
   RobotMotions[RobotJumping].EnergyDrain=RobotJumpingEnergyDrain;

   RobotMotions[RobotAirborne].AccelerationValue=0;
   RobotMotions[RobotAirborne].YAccelerationValue=RobotGravity;
   RobotMotions[RobotAirborne].TopSpeed=RobotMaxFVel4;
   RobotMotions[RobotAirborne].TopYSpeed=MaxYVel;
   RobotMotions[RobotAirborne].EnergyDrain=RobotAirborneEnergyDrain;

   RobotMotions[RobotStopped].AccelerationValue=0;
   RobotMotions[RobotStopped].YAccelerationValue=0;
   RobotMotions[RobotStopped].TopSpeed=0;
   RobotMotions[RobotStopped].TopYSpeed=0;
   RobotMotions[RobotStopped].EnergyDrain=RobotStoppedEnergyDrain;

   RobotMotions[RobotStoppedOnBuilding].AccelerationValue=0;
   RobotMotions[RobotStoppedOnBuilding].YAccelerationValue=0;
   RobotMotions[RobotStoppedOnBuilding].TopSpeed=0;
   RobotMotions[RobotStoppedOnBuilding].TopYSpeed=0;
   RobotMotions[RobotStoppedOnBuilding].EnergyDrain=RobotStoppedEnergyDrain;

   RobotMotions[RobotSlideDownBuildingSide].AccelerationValue=0;
   RobotMotions[RobotSlideDownBuildingSide].YAccelerationValue=RobotGravity;
   RobotMotions[RobotSlideDownBuildingSide].TopSpeed=0;
   RobotMotions[RobotSlideDownBuildingSide].TopYSpeed=MaxYVel;
   RobotMotions[RobotSlideDownBuildingSide].EnergyDrain=RobotStoppedEnergyDrain;

   RobotMotions[RobotWaitingOnBuilding].AccelerationValue=0;
   RobotMotions[RobotWaitingOnBuilding].YAccelerationValue=0;
   RobotMotions[RobotWaitingOnBuilding].TopSpeed=0;
   RobotMotions[RobotWaitingOnBuilding].TopYSpeed=0;
   RobotMotions[RobotWaitingOnBuilding].EnergyDrain=RobotWaitingEnergyDrain;

   RobotMotions[RobotFAccelerating1OnBuilding].AccelerationValue=RobotFAcc1;
   RobotMotions[RobotFAccelerating1OnBuilding].YAccelerationValue=0;
   RobotMotions[RobotFAccelerating1OnBuilding].TopSpeed=RobotMaxFVel1;
   RobotMotions[RobotFAccelerating1OnBuilding].TopYSpeed=0;
   RobotMotions[RobotFAccelerating1OnBuilding].EnergyDrain=RobotFAccelerating1EnergyDrain;

   RobotMotions[RobotFAccelerating2OnBuilding].AccelerationValue=RobotFAcc2;
   RobotMotions[RobotFAccelerating2OnBuilding].YAccelerationValue=0;
   RobotMotions[RobotFAccelerating2OnBuilding].TopSpeed=RobotMaxFVel2;
   RobotMotions[RobotFAccelerating2OnBuilding].TopYSpeed=0;
   RobotMotions[RobotFAccelerating2OnBuilding].EnergyDrain=RobotFAccelerating2EnergyDrain;

   RobotMotions[RobotFTopSpeed1OnBuilding].AccelerationValue=0;
   RobotMotions[RobotFTopSpeed1OnBuilding].YAccelerationValue=0;
   RobotMotions[RobotFTopSpeed1OnBuilding].TopSpeed=RobotMaxFVel1;
   RobotMotions[RobotFTopSpeed1OnBuilding].TopYSpeed=0;
   RobotMotions[RobotFTopSpeed1OnBuilding].EnergyDrain=RobotFTopSpeed1EnergyDrain;

   RobotMotions[RobotFTopSpeed2OnBuilding].AccelerationValue=0;
   RobotMotions[RobotFTopSpeed2OnBuilding].YAccelerationValue=0;
   RobotMotions[RobotFTopSpeed2OnBuilding].TopSpeed=RobotMaxFVel2;
   RobotMotions[RobotFTopSpeed2OnBuilding].TopYSpeed=0;
   RobotMotions[RobotFTopSpeed2OnBuilding].EnergyDrain=RobotFTopSpeed2EnergyDrain;

   RobotMotions[RobotFDeceleratingOnBuilding].AccelerationValue=RobotFDecel;
   RobotMotions[RobotFDeceleratingOnBuilding].YAccelerationValue=0;
   RobotMotions[RobotFDeceleratingOnBuilding].TopSpeed=RobotMaxFVel3;
   RobotMotions[RobotFDeceleratingOnBuilding].TopYSpeed=0;
   RobotMotions[RobotFDeceleratingOnBuilding].EnergyDrain=RobotFDeceleratingEnergyDrain;

   RobotMotions[RobotBAccelerating1OnBuilding].AccelerationValue=RobotBAcc1;
   RobotMotions[RobotBAccelerating1OnBuilding].YAccelerationValue=0;
   RobotMotions[RobotBAccelerating1OnBuilding].TopSpeed=RobotMaxBVel1;
   RobotMotions[RobotBAccelerating1OnBuilding].TopYSpeed=0;
   RobotMotions[RobotBAccelerating1OnBuilding].EnergyDrain=RobotBAccelerating1EnergyDrain;

   RobotMotions[RobotBTopSpeed1OnBuilding].AccelerationValue=0;
   RobotMotions[RobotBTopSpeed1OnBuilding].YAccelerationValue=0;
   RobotMotions[RobotBTopSpeed1OnBuilding].TopSpeed=RobotMaxBVel1;
   RobotMotions[RobotBTopSpeed1OnBuilding].TopYSpeed=0;
   RobotMotions[RobotBTopSpeed1OnBuilding].EnergyDrain=RobotBTopSpeed1EnergyDrain;

   RobotMotions[RobotBDeceleratingOnBuilding].AccelerationValue=RobotBDecel;
   RobotMotions[RobotBDeceleratingOnBuilding].YAccelerationValue=0;
   RobotMotions[RobotBDeceleratingOnBuilding].TopSpeed=RobotMaxBVel2;
   RobotMotions[RobotBDeceleratingOnBuilding].TopYSpeed=0;
   RobotMotions[RobotBDeceleratingOnBuilding].EnergyDrain=RobotBDeceleratingEnergyDrain;

   RobotMotions[RobotLAccelerating1OnBuilding].AccelerationValue=RobotLAcc1;
   RobotMotions[RobotLAccelerating1OnBuilding].YAccelerationValue=0;
   RobotMotions[RobotLAccelerating1OnBuilding].TopSpeed=RobotMaxLVel1;
   RobotMotions[RobotLAccelerating1OnBuilding].TopYSpeed=0;
   RobotMotions[RobotLAccelerating1OnBuilding].EnergyDrain=RobotLAccelerating1EnergyDrain;

   RobotMotions[RobotLTopSpeed1OnBuilding].AccelerationValue=0;
   RobotMotions[RobotLTopSpeed1OnBuilding].YAccelerationValue=0;
   RobotMotions[RobotLTopSpeed1OnBuilding].TopSpeed=RobotMaxLVel1;
   RobotMotions[RobotLTopSpeed1OnBuilding].TopYSpeed=0;
   RobotMotions[RobotLTopSpeed1OnBuilding].EnergyDrain=RobotLTopSpeed1EnergyDrain;

   RobotMotions[RobotLDeceleratingOnBuilding].AccelerationValue=RobotLDecel;
   RobotMotions[RobotLDeceleratingOnBuilding].YAccelerationValue=0;
   RobotMotions[RobotLDeceleratingOnBuilding].TopSpeed=RobotMaxLVel1;
   RobotMotions[RobotLDeceleratingOnBuilding].TopYSpeed=0;
   RobotMotions[RobotLDeceleratingOnBuilding].EnergyDrain=RobotLDeceleratingEnergyDrain;

   RobotMotions[RobotRAccelerating1OnBuilding].AccelerationValue=RobotRAcc1;
   RobotMotions[RobotRAccelerating1OnBuilding].YAccelerationValue=0;
   RobotMotions[RobotRAccelerating1OnBuilding].TopSpeed=RobotMaxRVel1;
   RobotMotions[RobotRAccelerating1OnBuilding].TopYSpeed=0;
   RobotMotions[RobotRAccelerating1OnBuilding].EnergyDrain=RobotRAccelerating1EnergyDrain;

   RobotMotions[RobotRTopSpeed1OnBuilding].AccelerationValue=0;
   RobotMotions[RobotRTopSpeed1OnBuilding].YAccelerationValue=0;
   RobotMotions[RobotRTopSpeed1OnBuilding].TopSpeed=RobotMaxRVel1;
   RobotMotions[RobotRTopSpeed1OnBuilding].TopYSpeed=0;
   RobotMotions[RobotRTopSpeed1OnBuilding].EnergyDrain=RobotRTopSpeed1EnergyDrain;

   RobotMotions[RobotRDeceleratingOnBuilding].AccelerationValue=RobotRDecel;
   RobotMotions[RobotRDeceleratingOnBuilding].YAccelerationValue=0;
   RobotMotions[RobotRDeceleratingOnBuilding].TopSpeed=RobotMaxRVel1;
   RobotMotions[RobotRDeceleratingOnBuilding].TopYSpeed=0;
   RobotMotions[RobotRDeceleratingOnBuilding].EnergyDrain=RobotRDeceleratingEnergyDrain;




}
//This function will load up RobotMotions with the proper states.
int InitRobotMotionEngine()
{
    size_t size1,size2;
   size1=RLGetTotalAllocated();

   if(RLMalloc( (void **)&(RobotMotions[RobotWaiting].ChangeList) , 9*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotWaiting].numchanges=7;
   RobotMotions[RobotWaiting].WhatToDo=RobotWaitingFunction;
   RobotMotions[RobotWaiting].ChangeList[0]=ToRobotStopped;
   RobotMotions[RobotWaiting].ChangeList[1]=ToRobotJumping;
   RobotMotions[RobotWaiting].ChangeList[2]=ToRobotFAccelerating1;
   RobotMotions[RobotWaiting].ChangeList[3]=ToRobotBAccelerating3;
   RobotMotions[RobotWaiting].ChangeList[4]=ToRobotLAccelerating2;
   RobotMotions[RobotWaiting].ChangeList[5]=ToRobotRAccelerating2;
   RobotMotions[RobotWaiting].ChangeList[6]=ToRobotBAccelerating1;
//   RobotMotions[RobotWaiting].ChangeList[7]=ToRobotLAccelerating1;
//   RobotMotions[RobotWaiting].ChangeList[8]=ToRobotRAccelerating1;


   if(RLMalloc((void **)&(RobotMotions[RobotFAccelerating1].ChangeList  ),7*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotFAccelerating1].numchanges=7;
   RobotMotions[RobotFAccelerating1].WhatToDo=RobotFAccelerating1Function;
   RobotMotions[RobotFAccelerating1].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotFAccelerating1].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotFAccelerating1].ChangeList[2]=ToRobotWaiting;
   RobotMotions[RobotFAccelerating1].ChangeList[3]=ToRobotJumping;
   RobotMotions[RobotFAccelerating1].ChangeList[4]=ToRobotFBraking;
   RobotMotions[RobotFAccelerating1].ChangeList[5]=ToRobotFDecelerating;
   RobotMotions[RobotFAccelerating1].ChangeList[6]=ToRobotFTopSpeed1;


   if(RLMalloc((void **)&(RobotMotions[RobotFAccelerating2].ChangeList  ),7*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotFAccelerating2].numchanges=7;
   RobotMotions[RobotFAccelerating2].WhatToDo=RobotFAccelerating2Function;
   RobotMotions[RobotFAccelerating2].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotFAccelerating2].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotFAccelerating2].ChangeList[2]=ToRobotWaiting;
   RobotMotions[RobotFAccelerating2].ChangeList[3]=ToRobotJumping;
   RobotMotions[RobotFAccelerating2].ChangeList[4]=ToRobotFBraking;
   RobotMotions[RobotFAccelerating2].ChangeList[5]=ToRobotFDecelerating;
   RobotMotions[RobotFAccelerating2].ChangeList[6]=ToRobotFTopSpeed2;


   if(RLMalloc((void **)&(RobotMotions[RobotFAccelerating3].ChangeList  ),6*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotFAccelerating3].numchanges=6;
   RobotMotions[RobotFAccelerating3].WhatToDo=RobotFAccelerating3Function;
   RobotMotions[RobotFAccelerating3].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotFAccelerating3].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotFAccelerating3].ChangeList[2]=ToRobotJumping;
   RobotMotions[RobotFAccelerating3].ChangeList[3]=ToRobotFBraking;
   RobotMotions[RobotFAccelerating3].ChangeList[4]=ToRobotFDecelerating;
   RobotMotions[RobotFAccelerating3].ChangeList[5]=ToRobotFTopSpeed3;


   if(RLMalloc((void **)&(RobotMotions[RobotFAccelerating4].ChangeList  ),5*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotFAccelerating4].numchanges=5;
   RobotMotions[RobotFAccelerating4].WhatToDo=RobotFAccelerating4Function;
   RobotMotions[RobotFAccelerating4].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotFAccelerating4].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotFAccelerating4].ChangeList[2]=ToRobotJumping;
   RobotMotions[RobotFAccelerating4].ChangeList[3]=ToRobotFBraking;
   RobotMotions[RobotFAccelerating4].ChangeList[4]=ToRobotFTopSpeed4;


   if(RLMalloc((void **)&(RobotMotions[RobotFTopSpeed1].ChangeList      ),7*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotFTopSpeed1].numchanges=7;
   RobotMotions[RobotFTopSpeed1].WhatToDo=RobotFTopSpeed1Function;
   RobotMotions[RobotFTopSpeed1].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotFTopSpeed1].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotFTopSpeed1].ChangeList[2]=ToRobotWaiting;
   RobotMotions[RobotFTopSpeed1].ChangeList[3]=ToRobotJumping;
   RobotMotions[RobotFTopSpeed1].ChangeList[4]=ToRobotFBraking;
   RobotMotions[RobotFTopSpeed1].ChangeList[5]=ToRobotFDecelerating;
   RobotMotions[RobotFTopSpeed1].ChangeList[6]=ToRobotFAccelerating2;


   if(RLMalloc((void **)&(RobotMotions[RobotFTopSpeed2].ChangeList      ),7*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotFTopSpeed2].numchanges=7;
   RobotMotions[RobotFTopSpeed2].WhatToDo=RobotFTopSpeed2Function;
   RobotMotions[RobotFTopSpeed2].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotFTopSpeed2].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotFTopSpeed2].ChangeList[2]=ToRobotWaiting;
   RobotMotions[RobotFTopSpeed2].ChangeList[3]=ToRobotJumping;
   RobotMotions[RobotFTopSpeed2].ChangeList[4]=ToRobotFBraking;
   RobotMotions[RobotFTopSpeed2].ChangeList[5]=ToRobotFDecelerating;
   RobotMotions[RobotFTopSpeed2].ChangeList[6]=ToRobotFAccelerating3;


   if(RLMalloc((void **)&(RobotMotions[RobotFTopSpeed3].ChangeList      ),6*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotFTopSpeed3].numchanges=6;
   RobotMotions[RobotFTopSpeed3].WhatToDo=RobotFTopSpeed3Function;
   RobotMotions[RobotFTopSpeed3].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotFTopSpeed3].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotFTopSpeed3].ChangeList[2]=ToRobotJumping;
   RobotMotions[RobotFTopSpeed3].ChangeList[3]=ToRobotFBraking;
   RobotMotions[RobotFTopSpeed3].ChangeList[4]=ToRobotFDecelerating;
   RobotMotions[RobotFTopSpeed3].ChangeList[5]=ToRobotFAccelerating4;


   if(RLMalloc((void **)&(RobotMotions[RobotFTopSpeed4].ChangeList      ),4*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotFTopSpeed4].numchanges=4;
   RobotMotions[RobotFTopSpeed4].WhatToDo=RobotFTopSpeed4Function;
   RobotMotions[RobotFTopSpeed4].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotFTopSpeed4].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotFTopSpeed4].ChangeList[2]=ToRobotJumping;
   RobotMotions[RobotFTopSpeed4].ChangeList[3]=ToRobotFBraking;


   if(RLMalloc((void **)&(RobotMotions[RobotFDecelerating].ChangeList   ),8*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotFDecelerating].numchanges=8;
   RobotMotions[RobotFDecelerating].WhatToDo=RobotFDeceleratingFunction;
   RobotMotions[RobotFDecelerating].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotFDecelerating].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotFDecelerating].ChangeList[2]=ToRobotJumping;
   RobotMotions[RobotFDecelerating].ChangeList[3]=ToRobotWaiting;
   RobotMotions[RobotFDecelerating].ChangeList[4]=ToRobotFBraking;
   RobotMotions[RobotFDecelerating].ChangeList[5]=ToRobotFAccelerating3;
   RobotMotions[RobotFDecelerating].ChangeList[6]=ToRobotFAccelerating2;
   RobotMotions[RobotFDecelerating].ChangeList[7]=ToRobotFAccelerating1;


   if(RLMalloc((void **)&(RobotMotions[RobotFBraking].ChangeList        ),8*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotFBraking].numchanges=8;
   RobotMotions[RobotFBraking].WhatToDo=RobotFBrakingFunction;
   RobotMotions[RobotFBraking].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotFBraking].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotFBraking].ChangeList[2]=ToRobotWaiting;
   RobotMotions[RobotFBraking].ChangeList[3]=ToRobotJumping;
   RobotMotions[RobotFBraking].ChangeList[4]=ToRobotFDecelerating;
   RobotMotions[RobotFBraking].ChangeList[5]=ToRobotFAccelerating3;
   RobotMotions[RobotFBraking].ChangeList[6]=ToRobotFAccelerating2;
   RobotMotions[RobotFBraking].ChangeList[7]=ToRobotFAccelerating1;


   if(RLMalloc((void **)&(RobotMotions[RobotBAccelerating1].ChangeList  ),7*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotBAccelerating1].numchanges=7;
   RobotMotions[RobotBAccelerating1].WhatToDo=RobotBAccelerating1Function;
   RobotMotions[RobotBAccelerating1].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotBAccelerating1].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotBAccelerating1].ChangeList[2]=ToRobotWaiting;
   RobotMotions[RobotBAccelerating1].ChangeList[3]=ToRobotBBraking;
   RobotMotions[RobotBAccelerating1].ChangeList[4]=ToRobotBDecelerating;
   RobotMotions[RobotBAccelerating1].ChangeList[5]=ToRobotBAccelerating3;
   RobotMotions[RobotBAccelerating1].ChangeList[6]=ToRobotBTopSpeed1;


   if(RLMalloc((void **)&(RobotMotions[RobotBAccelerating2].ChangeList  ),7*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotBAccelerating2].numchanges=7;
   RobotMotions[RobotBAccelerating2].WhatToDo=RobotBAccelerating2Function;
   RobotMotions[RobotBAccelerating2].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotBAccelerating2].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotBAccelerating2].ChangeList[2]=ToRobotWaiting;
   RobotMotions[RobotBAccelerating2].ChangeList[3]=ToRobotBBraking;
   RobotMotions[RobotBAccelerating2].ChangeList[4]=ToRobotBDecelerating;
   RobotMotions[RobotBAccelerating2].ChangeList[5]=ToRobotBAccelerating3;
   RobotMotions[RobotBAccelerating2].ChangeList[6]=ToRobotBTopSpeed2;


   if(RLMalloc((void **)&(RobotMotions[RobotBAccelerating3].ChangeList  ),4*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotBAccelerating3].numchanges=4;
   RobotMotions[RobotBAccelerating3].WhatToDo=BAccelerating3Function;
   RobotMotions[RobotBAccelerating3].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotBAccelerating3].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotBAccelerating3].ChangeList[2]=ToRobotWaiting;
   RobotMotions[RobotBAccelerating3].ChangeList[3]=ToRobotBTopSpeed3;


   if(RLMalloc((void **)&(RobotMotions[RobotBTopSpeed1].ChangeList      ),7*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotBTopSpeed1].numchanges=7;
   RobotMotions[RobotBTopSpeed1].WhatToDo=RobotBTopSpeed1Function;
   RobotMotions[RobotBTopSpeed1].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotBTopSpeed1].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotBTopSpeed1].ChangeList[2]=ToRobotWaiting;
   RobotMotions[RobotBTopSpeed1].ChangeList[3]=ToRobotBBraking;
   RobotMotions[RobotBTopSpeed1].ChangeList[4]=ToRobotBDecelerating;
   RobotMotions[RobotBTopSpeed1].ChangeList[5]=ToRobotBAccelerating3;
   RobotMotions[RobotBTopSpeed1].ChangeList[6]=ToRobotBAccelerating2;

   if(RLMalloc((void **)&(RobotMotions[RobotBTopSpeed2].ChangeList      ),6*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotBTopSpeed2].numchanges=6;
   RobotMotions[RobotBTopSpeed2].WhatToDo=RobotBTopSpeed2Function;
   RobotMotions[RobotBTopSpeed2].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotBTopSpeed2].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotBTopSpeed2].ChangeList[2]=ToRobotWaiting;
   RobotMotions[RobotBTopSpeed2].ChangeList[3]=ToRobotBBraking;
   RobotMotions[RobotBTopSpeed2].ChangeList[4]=ToRobotBDecelerating;
   RobotMotions[RobotBTopSpeed2].ChangeList[5]=ToRobotBAccelerating3;


   if(RLMalloc((void **)&(RobotMotions[RobotBTopSpeed3].ChangeList      ),3*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotBTopSpeed3].numchanges=3;
   RobotMotions[RobotBTopSpeed3].WhatToDo=RobotBTopSpeed3Function;
   RobotMotions[RobotBTopSpeed3].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotBTopSpeed3].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotBTopSpeed3].ChangeList[2]=ToRobotBBraking;


   if(RLMalloc((void **)&(RobotMotions[RobotBDecelerating].ChangeList   ),7*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotBDecelerating].numchanges=7;
   RobotMotions[RobotBDecelerating].WhatToDo=RobotBDeceleratingFunction;
   RobotMotions[RobotBDecelerating].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotBDecelerating].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotBDecelerating].ChangeList[2]=ToRobotWaiting;
   RobotMotions[RobotBDecelerating].ChangeList[3]=ToRobotBBraking;
   RobotMotions[RobotBDecelerating].ChangeList[4]=ToRobotBAccelerating3;
   RobotMotions[RobotBDecelerating].ChangeList[5]=ToRobotBAccelerating2;
   RobotMotions[RobotBDecelerating].ChangeList[6]=ToRobotBAccelerating1;


   if(RLMalloc((void **)&(RobotMotions[RobotBBraking].ChangeList        ),3*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotBBraking].numchanges=3;
   RobotMotions[RobotBBraking].WhatToDo=RobotBBrakingFunction;
   RobotMotions[RobotBBraking].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotBBraking].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotBBraking].ChangeList[2]=ToRobotWaiting;


   if(RLMalloc((void **)&(RobotMotions[RobotLAccelerating1].ChangeList  ),6*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotLAccelerating1].numchanges=6;
   RobotMotions[RobotLAccelerating1].WhatToDo=RobotLAccelerating1Function;
   RobotMotions[RobotLAccelerating1].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotLAccelerating1].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotLAccelerating1].ChangeList[2]=ToRobotWaiting;
   RobotMotions[RobotLAccelerating1].ChangeList[3]=ToRobotLDecelerating;
   RobotMotions[RobotLAccelerating1].ChangeList[4]=ToRobotLAccelerating2;
   RobotMotions[RobotLAccelerating1].ChangeList[5]=ToRobotLTopSpeed1;


   if(RLMalloc((void **)&(RobotMotions[RobotLAccelerating2].ChangeList  ),4*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotLAccelerating2].numchanges=4;
   RobotMotions[RobotLAccelerating2].WhatToDo=RobotLAccelerating2Function;
   RobotMotions[RobotLAccelerating2].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotLAccelerating2].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotLAccelerating2].ChangeList[2]=ToRobotWaiting;
   RobotMotions[RobotLAccelerating2].ChangeList[3]=ToRobotLTopSpeed2;


   if(RLMalloc((void **)&(RobotMotions[RobotLTopSpeed1].ChangeList      ),5*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotLTopSpeed1].numchanges=5;
   RobotMotions[RobotLTopSpeed1].WhatToDo=RobotLTopSpeed1Function;
   RobotMotions[RobotLTopSpeed1].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotLTopSpeed1].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotLTopSpeed1].ChangeList[2]=ToRobotWaiting;
   RobotMotions[RobotLTopSpeed1].ChangeList[3]=ToRobotLDecelerating;
   RobotMotions[RobotLTopSpeed1].ChangeList[4]=ToRobotLAccelerating2;


   if(RLMalloc((void **)&(RobotMotions[RobotLTopSpeed2].ChangeList      ),3*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotLTopSpeed2].numchanges=3;
   RobotMotions[RobotLTopSpeed2].WhatToDo=RobotLTopSpeed2Function;
   RobotMotions[RobotLTopSpeed2].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotLTopSpeed2].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotLTopSpeed2].ChangeList[2]=ToRobotLBraking;


   if(RLMalloc((void **)&(RobotMotions[RobotLDecelerating].ChangeList   ),5*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotLDecelerating].numchanges=4;
   RobotMotions[RobotLDecelerating].WhatToDo=RobotLDeceleratingFunction;
   RobotMotions[RobotLDecelerating].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotLDecelerating].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotLDecelerating].ChangeList[2]=ToRobotWaiting;
   RobotMotions[RobotLDecelerating].ChangeList[3]=ToRobotLAccelerating2;
   //RobotMotions[RobotLDecelerating].ChangeList[4]=ToRobotLAccelerating1;


   if(RLMalloc((void **)&(RobotMotions[RobotLBraking].ChangeList        ),3*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotLBraking].numchanges=3;
   RobotMotions[RobotLBraking].WhatToDo=RobotLBrakingFunction;
   RobotMotions[RobotLBraking].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotLBraking].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotLBraking].ChangeList[2]=ToRobotWaiting;


   if(RLMalloc((void **)&(RobotMotions[RobotRAccelerating1].ChangeList  ),6*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotRAccelerating1].numchanges=6;
   RobotMotions[RobotRAccelerating1].WhatToDo=RobotRAccelerating1Function;
   RobotMotions[RobotRAccelerating1].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotRAccelerating1].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotRAccelerating1].ChangeList[2]=ToRobotWaiting;
   RobotMotions[RobotRAccelerating1].ChangeList[3]=ToRobotRDecelerating;
   RobotMotions[RobotRAccelerating1].ChangeList[4]=ToRobotRAccelerating2;
   RobotMotions[RobotRAccelerating1].ChangeList[5]=ToRobotRTopSpeed1;



   if(RLMalloc((void **)&(RobotMotions[RobotRAccelerating2].ChangeList  ),4*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotRAccelerating2].numchanges=4;
   RobotMotions[RobotRAccelerating2].WhatToDo=RobotRAccelerating2Function;
   RobotMotions[RobotRAccelerating2].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotRAccelerating2].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotRAccelerating2].ChangeList[2]=ToRobotWaiting;
   RobotMotions[RobotRAccelerating2].ChangeList[3]=ToRobotRTopSpeed2;


   if(RLMalloc((void **)&(RobotMotions[RobotRTopSpeed1].ChangeList      ),5*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotRTopSpeed1].numchanges=5;
   RobotMotions[RobotRTopSpeed1].WhatToDo=RobotRTopSpeed1Function;
   RobotMotions[RobotRTopSpeed1].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotRTopSpeed1].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotRTopSpeed1].ChangeList[2]=ToRobotWaiting;
   RobotMotions[RobotRTopSpeed1].ChangeList[3]=ToRobotRDecelerating;
   RobotMotions[RobotRTopSpeed1].ChangeList[4]=ToRobotRAccelerating2;


   if(RLMalloc((void **)&(RobotMotions[RobotRTopSpeed2].ChangeList      ),3*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotRTopSpeed2].numchanges=3;
   RobotMotions[RobotRTopSpeed2].WhatToDo=RobotRTopSpeed2Function;
   RobotMotions[RobotRTopSpeed2].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotRTopSpeed2].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotRTopSpeed2].ChangeList[2]=ToRobotRBraking;


   if(RLMalloc((void **)&(RobotMotions[RobotRDecelerating].ChangeList   ),5*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotRDecelerating].numchanges=4;
   RobotMotions[RobotRDecelerating].WhatToDo=RobotRDeceleratingFunction;
   RobotMotions[RobotRDecelerating].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotRDecelerating].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotRDecelerating].ChangeList[2]=ToRobotWaiting;
   RobotMotions[RobotRDecelerating].ChangeList[3]=ToRobotRAccelerating2;
//   RobotMotions[RobotRDecelerating].ChangeList[4]=ToRobotRAccelerating1;


   if(RLMalloc((void **)&(RobotMotions[RobotRBraking].ChangeList        ),3*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotRBraking].numchanges=3;
   RobotMotions[RobotRBraking].WhatToDo=RobotRBrakingFunction;
   RobotMotions[RobotRBraking].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotRBraking].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotRBraking].ChangeList[2]=ToRobotWaiting;


   if(RLMalloc((void **)&(RobotMotions[RobotJumping].ChangeList         ),2*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotJumping].numchanges=2;
   RobotMotions[RobotJumping].WhatToDo=RobotJumpingFunction;
   RobotMotions[RobotJumping].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotJumping].ChangeList[1]=ToRobotStopped;


   if(RLMalloc((void **)&(RobotMotions[RobotAirborne].ChangeList        ),5*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotAirborne].numchanges=5;
   RobotMotions[RobotAirborne].WhatToDo=RobotAirborneFunction;
   RobotMotions[RobotAirborne].ChangeList[0]=ToRobotStopped;
   RobotMotions[RobotAirborne].ChangeList[1]=ToRobotFTopSpeed4;
   RobotMotions[RobotAirborne].ChangeList[2]=ToRobotFTopSpeed3;
   RobotMotions[RobotAirborne].ChangeList[3]=ToRobotFTopSpeed2;
   RobotMotions[RobotAirborne].ChangeList[4]=ToRobotFTopSpeed1;
//   RobotMotions[RobotAirborne].ChangeList[5]=ToRobotWaiting;
//   RobotMotions[RobotAirborne].ChangeList[6]=ToRobotFBraking;
//   RobotMotions[RobotAirborne].ChangeList[7]=ToRobotFDecelerating;


//   if(RLMalloc((void **)&(RobotMotions[RobotStopped].ChangeList         ),1*sizeof(StateChange))!=RLNoError)
//      return 0;
   RobotMotions[RobotStopped].ChangeList=NULL;
   RobotMotions[RobotStopped].numchanges=0;
   RobotMotions[RobotStopped].WhatToDo=RobotStoppedFunction;

   if(RLMalloc((void **)&(RobotMotions[RobotStoppedOnBuilding].ChangeList         ),1*sizeof(StateChange))!=RLNoError)
	   return 0;
//   RobotMotions[RobotStoppedOnBuilding].ChangeList=NULL;
   RobotMotions[RobotStoppedOnBuilding].numchanges=1;
   RobotMotions[RobotStoppedOnBuilding].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotStoppedOnBuilding].WhatToDo=RobotStoppedOnBuildingFunction;


   if(RLMalloc((void **)&(RobotMotions[RobotKnockDown].ChangeList         ),1*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotKnockDown].numchanges=1;
   RobotMotions[RobotKnockDown].ChangeList[0]=ToRobotStopped;
   RobotMotions[RobotKnockDown].WhatToDo=RobotKnockDownFunction;
//   RobotMotions[RobotStopped].ChangeList[0]=ToRobotWaiting;

   if(RLMalloc((void **)&(RobotMotions[RobotKnockDownOnBuilding].ChangeList         ),2*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotKnockDownOnBuilding].numchanges=2;
   RobotMotions[RobotKnockDownOnBuilding].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotKnockDownOnBuilding].ChangeList[1]=ToRobotStoppedOnBuilding;
   RobotMotions[RobotKnockDownOnBuilding].WhatToDo=RobotKnockDownOnBuildingFunction;


/*
*/
   if(RLMalloc( (void **)&(RobotMotions[RobotWaitingOnBuilding].ChangeList) , 7*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotWaitingOnBuilding].numchanges=7;
   RobotMotions[RobotWaitingOnBuilding].WhatToDo=RobotWaitingOnBuildingFunction;
   RobotMotions[RobotWaitingOnBuilding].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotWaitingOnBuilding].ChangeList[1]=ToRobotStoppedOnBuilding;
   RobotMotions[RobotWaitingOnBuilding].ChangeList[2]=ToRobotJumping;
   RobotMotions[RobotWaitingOnBuilding].ChangeList[3]=ToRobotFAccelerating1OnBuilding;
   RobotMotions[RobotWaitingOnBuilding].ChangeList[4]=ToRobotBAccelerating1OnBuilding;
   RobotMotions[RobotWaitingOnBuilding].ChangeList[5]=ToRobotLAccelerating1OnBuilding;
   RobotMotions[RobotWaitingOnBuilding].ChangeList[6]=ToRobotRAccelerating1OnBuilding;


   if(RLMalloc((void **)&(RobotMotions[RobotFAccelerating1OnBuilding].ChangeList  ),6*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotFAccelerating1OnBuilding].numchanges=6;
   RobotMotions[RobotFAccelerating1OnBuilding].WhatToDo=RobotMovingOnBuildingFunction;
   RobotMotions[RobotFAccelerating1OnBuilding].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotFAccelerating1OnBuilding].ChangeList[1]=ToRobotStoppedOnBuilding;
   RobotMotions[RobotFAccelerating1OnBuilding].ChangeList[2]=ToRobotWaitingOnBuilding;
   RobotMotions[RobotFAccelerating1OnBuilding].ChangeList[3]=ToRobotJumping;
   RobotMotions[RobotFAccelerating1OnBuilding].ChangeList[4]=ToRobotFDeceleratingOnBuilding;
   RobotMotions[RobotFAccelerating1OnBuilding].ChangeList[5]=ToRobotFTopSpeed1OnBuilding;


   if(RLMalloc((void **)&(RobotMotions[RobotFAccelerating2OnBuilding].ChangeList  ),6*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotFAccelerating2OnBuilding].numchanges=6;
   RobotMotions[RobotFAccelerating2OnBuilding].WhatToDo=RobotMovingOnBuildingFunction;
   RobotMotions[RobotFAccelerating2OnBuilding].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotFAccelerating2OnBuilding].ChangeList[1]=ToRobotStopped;
   RobotMotions[RobotFAccelerating2OnBuilding].ChangeList[2]=ToRobotWaitingOnBuilding;
   RobotMotions[RobotFAccelerating2OnBuilding].ChangeList[3]=ToRobotJumping;
   RobotMotions[RobotFAccelerating2OnBuilding].ChangeList[4]=ToRobotFDeceleratingOnBuilding;
   RobotMotions[RobotFAccelerating2OnBuilding].ChangeList[5]=ToRobotFTopSpeed2OnBuilding;


   if(RLMalloc((void **)&(RobotMotions[RobotFTopSpeed1OnBuilding].ChangeList),6*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotFTopSpeed1OnBuilding].numchanges=6;
   RobotMotions[RobotFTopSpeed1OnBuilding].WhatToDo=RobotMovingOnBuildingFunction;
   RobotMotions[RobotFTopSpeed1OnBuilding].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotFTopSpeed1OnBuilding].ChangeList[1]=ToRobotStoppedOnBuilding;
   RobotMotions[RobotFTopSpeed1OnBuilding].ChangeList[2]=ToRobotWaitingOnBuilding;
   RobotMotions[RobotFTopSpeed1OnBuilding].ChangeList[3]=ToRobotJumping;
   RobotMotions[RobotFTopSpeed1OnBuilding].ChangeList[4]=ToRobotFDeceleratingOnBuilding;
   RobotMotions[RobotFTopSpeed1OnBuilding].ChangeList[5]=ToRobotFAccelerating2OnBuilding;


   if(RLMalloc((void **)&(RobotMotions[RobotFTopSpeed2OnBuilding].ChangeList      ),5*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotFTopSpeed2OnBuilding].numchanges=5;
   RobotMotions[RobotFTopSpeed2OnBuilding].WhatToDo=RobotMovingOnBuildingFunction;
   RobotMotions[RobotFTopSpeed2OnBuilding].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotFTopSpeed2OnBuilding].ChangeList[1]=ToRobotStoppedOnBuilding;
   RobotMotions[RobotFTopSpeed2OnBuilding].ChangeList[2]=ToRobotWaitingOnBuilding;
   RobotMotions[RobotFTopSpeed2OnBuilding].ChangeList[3]=ToRobotJumping;
   RobotMotions[RobotFTopSpeed2OnBuilding].ChangeList[4]=ToRobotFDeceleratingOnBuilding;


   if(RLMalloc((void **)&(RobotMotions[RobotFDeceleratingOnBuilding].ChangeList   ),6*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotFDeceleratingOnBuilding].numchanges=6;
   RobotMotions[RobotFDeceleratingOnBuilding].WhatToDo=RobotMovingOnBuildingFunction;
   RobotMotions[RobotFDeceleratingOnBuilding].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotFDeceleratingOnBuilding].ChangeList[1]=ToRobotStoppedOnBuilding;
   RobotMotions[RobotFDeceleratingOnBuilding].ChangeList[2]=ToRobotJumping;
   RobotMotions[RobotFDeceleratingOnBuilding].ChangeList[3]=ToRobotWaitingOnBuilding;
   RobotMotions[RobotFDeceleratingOnBuilding].ChangeList[4]=ToRobotFAccelerating2OnBuilding;
   RobotMotions[RobotFDeceleratingOnBuilding].ChangeList[5]=ToRobotFAccelerating1OnBuilding;


   if(RLMalloc((void **)&(RobotMotions[RobotBAccelerating1OnBuilding].ChangeList  ),5*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotBAccelerating1OnBuilding].numchanges=5;
   RobotMotions[RobotBAccelerating1OnBuilding].WhatToDo=RobotMovingOnBuildingFunction;
   RobotMotions[RobotBAccelerating1OnBuilding].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotBAccelerating1OnBuilding].ChangeList[1]=ToRobotStoppedOnBuilding;
   RobotMotions[RobotBAccelerating1OnBuilding].ChangeList[2]=ToRobotWaitingOnBuilding;
   RobotMotions[RobotBAccelerating1OnBuilding].ChangeList[3]=ToRobotBDeceleratingOnBuilding;
   RobotMotions[RobotBAccelerating1OnBuilding].ChangeList[4]=ToRobotBTopSpeed1OnBuilding;



   if(RLMalloc((void **)&(RobotMotions[RobotBTopSpeed1OnBuilding].ChangeList      ),4*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotBTopSpeed1OnBuilding].numchanges=4;
   RobotMotions[RobotBTopSpeed1OnBuilding].WhatToDo=RobotMovingOnBuildingFunction;
   RobotMotions[RobotBTopSpeed1OnBuilding].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotBTopSpeed1OnBuilding].ChangeList[1]=ToRobotStoppedOnBuilding;
   RobotMotions[RobotBTopSpeed1OnBuilding].ChangeList[2]=ToRobotWaitingOnBuilding;
   RobotMotions[RobotBTopSpeed1OnBuilding].ChangeList[3]=ToRobotBDeceleratingOnBuilding;


   if(RLMalloc((void **)&(RobotMotions[RobotBDeceleratingOnBuilding].ChangeList   ),4*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotBDeceleratingOnBuilding].numchanges=4;
   RobotMotions[RobotBDeceleratingOnBuilding].WhatToDo=RobotMovingOnBuildingFunction;
   RobotMotions[RobotBDeceleratingOnBuilding].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotBDeceleratingOnBuilding].ChangeList[1]=ToRobotStoppedOnBuilding;
   RobotMotions[RobotBDeceleratingOnBuilding].ChangeList[2]=ToRobotWaitingOnBuilding;
   RobotMotions[RobotBDeceleratingOnBuilding].ChangeList[3]=ToRobotBAccelerating1OnBuilding;


   if(RLMalloc((void **)&(RobotMotions[RobotLAccelerating1OnBuilding].ChangeList  ),5*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotLAccelerating1OnBuilding].numchanges=5;
   RobotMotions[RobotLAccelerating1OnBuilding].WhatToDo=RobotMovingOnBuildingFunction;
   RobotMotions[RobotLAccelerating1OnBuilding].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotLAccelerating1OnBuilding].ChangeList[1]=ToRobotStoppedOnBuilding;
   RobotMotions[RobotLAccelerating1OnBuilding].ChangeList[2]=ToRobotWaitingOnBuilding;
   RobotMotions[RobotLAccelerating1OnBuilding].ChangeList[3]=ToRobotLDeceleratingOnBuilding;
   RobotMotions[RobotLAccelerating1OnBuilding].ChangeList[4]=ToRobotLTopSpeed1OnBuilding;


   if(RLMalloc((void **)&(RobotMotions[RobotLTopSpeed1OnBuilding].ChangeList      ),4*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotLTopSpeed1OnBuilding].numchanges=4;
   RobotMotions[RobotLTopSpeed1OnBuilding].WhatToDo=RobotMovingOnBuildingFunction;
   RobotMotions[RobotLTopSpeed1OnBuilding].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotLTopSpeed1OnBuilding].ChangeList[1]=ToRobotStoppedOnBuilding;
   RobotMotions[RobotLTopSpeed1OnBuilding].ChangeList[2]=ToRobotWaitingOnBuilding;
   RobotMotions[RobotLTopSpeed1OnBuilding].ChangeList[3]=ToRobotLDeceleratingOnBuilding;


   if(RLMalloc((void **)&(RobotMotions[RobotLDeceleratingOnBuilding].ChangeList   ),4*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotLDeceleratingOnBuilding].numchanges=4;
   RobotMotions[RobotLDeceleratingOnBuilding].WhatToDo=RobotMovingOnBuildingFunction;
   RobotMotions[RobotLDeceleratingOnBuilding].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotLDeceleratingOnBuilding].ChangeList[1]=ToRobotStoppedOnBuilding;
   RobotMotions[RobotLDeceleratingOnBuilding].ChangeList[2]=ToRobotWaitingOnBuilding;
   RobotMotions[RobotLDeceleratingOnBuilding].ChangeList[3]=ToRobotLAccelerating1OnBuilding;


   if(RLMalloc((void **)&(RobotMotions[RobotRAccelerating1OnBuilding].ChangeList  ),5*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotRAccelerating1OnBuilding].numchanges=5;
   RobotMotions[RobotRAccelerating1OnBuilding].WhatToDo=RobotMovingOnBuildingFunction;
   RobotMotions[RobotRAccelerating1OnBuilding].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotRAccelerating1OnBuilding].ChangeList[1]=ToRobotStoppedOnBuilding;
   RobotMotions[RobotRAccelerating1OnBuilding].ChangeList[2]=ToRobotWaitingOnBuilding;
   RobotMotions[RobotRAccelerating1OnBuilding].ChangeList[3]=ToRobotRDeceleratingOnBuilding;
   RobotMotions[RobotRAccelerating1OnBuilding].ChangeList[4]=ToRobotRTopSpeed1OnBuilding;


   if(RLMalloc((void **)&(RobotMotions[RobotRTopSpeed1OnBuilding].ChangeList      ),4*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotRTopSpeed1OnBuilding].numchanges=4;
   RobotMotions[RobotRTopSpeed1OnBuilding].WhatToDo=RobotMovingOnBuildingFunction;
   RobotMotions[RobotRTopSpeed1OnBuilding].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotRTopSpeed1OnBuilding].ChangeList[1]=ToRobotStoppedOnBuilding;
   RobotMotions[RobotRTopSpeed1OnBuilding].ChangeList[2]=ToRobotWaitingOnBuilding;
   RobotMotions[RobotRTopSpeed1OnBuilding].ChangeList[3]=ToRobotRDeceleratingOnBuilding;


   if(RLMalloc((void **)&(RobotMotions[RobotRDeceleratingOnBuilding].ChangeList   ),4*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotRDeceleratingOnBuilding].numchanges=4;
   RobotMotions[RobotRDeceleratingOnBuilding].WhatToDo=RobotMovingOnBuildingFunction;
   RobotMotions[RobotRDeceleratingOnBuilding].ChangeList[0]=ToRobotAirborne;
   RobotMotions[RobotRDeceleratingOnBuilding].ChangeList[1]=ToRobotStoppedOnBuilding;
   RobotMotions[RobotRDeceleratingOnBuilding].ChangeList[2]=ToRobotWaitingOnBuilding;
   RobotMotions[RobotRDeceleratingOnBuilding].ChangeList[3]=ToRobotRAccelerating1OnBuilding;

   if(RLMalloc((void **)&(RobotMotions[RobotSlideDownBuildingSide].ChangeList),4*sizeof(StateChange))!=RLNoError)
      return 0;
   RobotMotions[RobotSlideDownBuildingSide].numchanges=1;
   RobotMotions[RobotSlideDownBuildingSide].WhatToDo=RobotSlideDownBuildingSideFunction;
   RobotMotions[RobotSlideDownBuildingSide].ChangeList[0]=ToRobotStopped;



/*
*/
   size2=RLGetTotalAllocated();
// printf("loaded movement engine, size %d\n",filename,size2-size1);
   return 1;

}

void DestroyRobotMotionEngine()
{
   int i;
    size_t size1,size2;
   size1=RLGetTotalAllocated();
   for(i=RobotWaiting;i<=RobotKnockDownOnBuilding;++i)
   {
      if(RobotMotions[i].numchanges)
      {
         RLFree(RobotMotions[i].ChangeList);
         RobotMotions[i].ChangeList=NULL;
      }
   }
   size2=RLGetTotalAllocated();
   //intf("unloaded motion engine, size %d\n",filename,size1-size2);
   
}

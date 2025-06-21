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
File:           monmove2.c
Author:         Bruce Abe
Date:           9-26-95
Version:        1.0



************************************************************************
REVISION HISTORY        (Add Edits and History to top of list).

Edited By:      Bruce Abe
Edited Date:    11-1-95
Changes:
                Added some typecasting to get rid of bounteous warnings.



***********************************************************************/
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
#include "math.h"
#include "boink.h"
#include "spudbmp.h"
#include "monmove.h"
#include "monanim.h"
#include "timing.h"
#include "gosys.h"
#include "global.h"
#include <math.h>
//#ifdef BruceNotSpudde
//extern FixMapInfo *LevelMap;
//#else
//#endif
#pragma warning( disable : 4244)
RLValue Turbo=1.5;
extern RLFrame Robotframe;
extern RLVector MonsterFallDownDirection;
extern int RobotEngy;
extern int MnstEngy;
extern int RobotLife;
extern int MnstLife;
extern RLValue sealevel;
extern RLValue MaxHeightDifference;
extern RLValue SpuddeMonstersAltitudeWhenSwimming;
static RLValue MonsterJumpYAcc= RLVal(0.045776);
static RLValue MaxYVel= RLVal(0.274658);
RLValue MonsterGravity= -RLVal(0.045776);
//static RLValue MonsterTurnRate= RLVal(0.053406);
RLValue MonsterFallDownSpin=10;//this is going to be a number between -10.0 and 10.0.
RLValue MonsterSpinMultiplier;
extern struct _moving_object_data_ MonsterData;

//static RLValue MonsterCosine=RLVal(0.998581);
//static RLValue MonsterSine=RLVal(0.053375);
RLValue MonsterTheta = 0;
RLValue MonsterTurnMaximum = RLVal(.07);
RLValue MonsterTurnAcceleration = RLVal(.001);

//static RLValue MonsterSineTable[10];
//static RLValue MonsterCosineTable[10];
RLValue MonsterGradientFactor=0;


static RLValue MonsterMaxFVel1 = RLVal(0.038147);
static RLValue MonsterMaxFVel2 = RLVal(0.076294);
static RLValue MonsterMaxFVel3 = RLVal(0.152588);
static RLValue MonsterMaxFVel4 = RLVal(0.228882);
static RLValue RoggoshHomerTopSpeed = RLVal(0.25);
static RLValue NeallothDiveBombTopSpeed = RLVal(0.25);
static RLValue NeallothDiveBombTopYSpeed = RLVal(0.35);
static RLValue MonsterFAcc1 = RLVal(0.003815);
static RLValue MonsterFAcc2 = RLVal(0.015259);
static RLValue MonsterFAcc3 = RLVal(0.030518);
static RLValue MonsterFAcc4 = RLVal(0.045776);
static RLValue RoggoshHomerAccelerationValue = RLVal(0.05);
static RLValue NeallothDiveBombAccelerationValue = RLVal(0.5);
static RLValue NeallothDiveBombYAccelerationValue = RLVal(0.1);

static RLValue MonsterFDecel = -RLVal(0.030518);
static RLValue MonsterFBrake = -RLVal(0.045776);

static RLValue MonsterMaxBVel1 = RLVal(0.045776);
static RLValue MonsterMaxBVel2 = RLVal(0.053406);
static RLValue MonsterBAcc1 = RLVal(0.015259);
static RLValue MonsterBAcc2 = RLVal(0.015259);
static RLValue MonsterBDecel = -RLVal(0.007629);
static RLValue MonsterBBrake = -RLVal(0.022888);

static RLValue MonsterMaxRVel1 = RLVal(0.022888);
static RLValue MonsterRAcc1 = RLVal(0.006104);
static RLValue MonsterRDecel = -RLVal(0.007629);
static RLValue MonsterRBrake = -RLVal(0.022888);

static RLValue MonsterMaxLVel1 = RLVal(0.022888);
static RLValue MonsterLAcc1 = RLVal(0.006104);
static RLValue MonsterLDecel = -RLVal(0.007629);
static RLValue MonsterLBrake = -RLVal(0.022888);


static RLValue MonsterWaitingEnergyDrain=0;
static RLValue MonsterFAccelerating1EnergyDrain=0;
static RLValue MonsterFAccelerating2EnergyDrain=30/5;
static RLValue MonsterFAccelerating3EnergyDrain=60/5;
static RLValue MonsterFAccelerating4EnergyDrain=100/5;
static RLValue MonsterFTopSpeed1EnergyDrain=0;
static RLValue MonsterFTopSpeed2EnergyDrain=30/5;
static RLValue MonsterFTopSpeed3EnergyDrain=60/5;
static RLValue MonsterFTopSpeed4EnergyDrain=100/5;
static RLValue MonsterFDeceleratingEnergyDrain=0;
static RLValue MonsterFBrakingEnergyDrain=0;
static RLValue MonsterBAccelerating1EnergyDrain=10/5;
static RLValue MonsterBAccelerating2EnergyDrain=20/5;
static RLValue MonsterBTopSpeed1EnergyDrain=10/5;
static RLValue MonsterBTopSpeed2EnergyDrain=20/5;
static RLValue MonsterBDeceleratingEnergyDrain=0;

static RLValue MonsterBBrakingEnergyDrain=0;
static RLValue MonsterLAccelerating1EnergyDrain=0;
static RLValue MonsterLTopSpeed1EnergyDrain=0;
static RLValue MonsterLDeceleratingEnergyDrain=0;
static RLValue MonsterLBrakingEnergyDrain=0;
static RLValue MonsterRAccelerating1EnergyDrain=0;
static RLValue MonsterRTopSpeed1EnergyDrain=0;
static RLValue MonsterRDeceleratingEnergyDrain=0;
static RLValue MonsterRBrakingEnergyDrain=0;
static RLValue MonsterJumpingEnergyDrain=100/5;
static RLValue MonsterAirborneEnergyDrain=0;
static RLValue MonsterStoppedEnergyDrain=0;
static RLValue MonsterKnockBackwardEnergyDrain=0;
static RLValue RoggoshHomerEnergyDrain=0;
static RLValue NeallothDiveBombEnergyDrain=0;

static RLValue MonsterWaitingMinEnergy=0;
static RLValue MonsterFAccelerating1MinEnergy=0;
static RLValue MonsterFAccelerating2MinEnergy=30;
static RLValue MonsterFAccelerating3MinEnergy=60;
static RLValue MonsterFAccelerating4MinEnergy=100;
static RLValue MonsterFTopSpeed1MinEnergy=0;
static RLValue MonsterFTopSpeed2MinEnergy=30;
static RLValue MonsterFTopSpeed3MinEnergy=60;
static RLValue MonsterFTopSpeed4MinEnergy=100;
static RLValue MonsterFDeceleratingMinEnergy=0;
static RLValue MonsterFBrakingMinEnergy=0;
static RLValue MonsterBAccelerating1MinEnergy=10;
static RLValue MonsterBAccelerating2MinEnergy=20;
static RLValue MonsterBTopSpeed1MinEnergy=10;
static RLValue MonsterBTopSpeed2MinEnergy=20;
static RLValue MonsterBDeceleratingMinEnergy=0;

static RLValue MonsterBBrakingMinEnergy=0;
static RLValue MonsterLAccelerating1MinEnergy=0;
static RLValue MonsterLTopSpeed1MinEnergy=0;
static RLValue MonsterLDeceleratingMinEnergy=0;
static RLValue MonsterLBrakingMinEnergy=0;
static RLValue MonsterRAccelerating1MinEnergy=0;
static RLValue MonsterRTopSpeed1MinEnergy=0;
static RLValue MonsterRDeceleratingMinEnergy=0;
static RLValue MonsterRBrakingMinEnergy=0;
static RLValue MonsterJumpingMinEnergy=200;
static RLValue MonsterAirborneMinEnergy=0;
static RLValue MonsterStoppedMinEnergy=0;
static RLValue MonsterKnockBackwardMinEnergy=0;
static RLValue MonsterGoopiness=RLVal(2);
static RLValue MonsterKnockBackwardSpeed=RLVal(0.1);
static RLValue HomingGoodEnough = RLVal(0.1);
static RLValue MonsterSlidingFriction = 0.05;






//This just in, late breaking flash, MonsterTurning will be handled semi-independently from movement.
//It will check to see that the movement isn't in a bad state, and will handle MonsterTurning from there.
#define MonsterWaiting                  0
#define MonsterFAccelerating1           1
#define MonsterFAccelerating2           2
#define MonsterFAccelerating3           3
#define MonsterFAccelerating4           4
#define MonsterFTopSpeed1               5
#define MonsterFTopSpeed2               6
#define MonsterFTopSpeed3               7
#define MonsterFTopSpeed4               8
#define MonsterFDecelerating            9
#define MonsterFBraking                 10
#define MonsterBAccelerating1           11
#define MonsterBAccelerating2           12
#define MonsterBTopSpeed1               13
#define MonsterBTopSpeed2               14
#define MonsterBDecelerating            15
//The states above allow for MonsterTurning.  those below don't.
#define MonsterBBraking                 16
#define MonsterLAccelerating1           17
#define MonsterLTopSpeed1               18
#define MonsterLDecelerating            19
#define MonsterLBraking                 20
#define MonsterRAccelerating1           21
#define MonsterRTopSpeed1               22
#define MonsterRDecelerating            23
#define MonsterRBraking                 24
#define MonsterJumping                  25
#define MonsterAirborne                 26
#define RoggoshHomer                    27
#define NeallothDiveBomb                28
#define MonsterStopped                  29
#define MonsterKnockBackward            30
//numerical values of cool stuff.
int MonsterMovementState;               //This is the main control of the Monster's movement state.
int MonsterNumMovementFrames;   //This counts the number of frames the current movement state has been active.
int MonsterMotionDamage=1;

RLValue MonsterSpeed;
RLValue MonsterDistance;      //MonsterDistance = integral of speed, i.e. arclength.
RLValue MonsterYSpeed;
RLVector MonsterPosition;     //These 4 items are controlled by/used by the state functions
RLVector MonsterVelocity;

//Flags which control whether or not you can affect movement.

int MonsterMidair;  //This will be changed by altitude bitmap calculations, and will control entering/leaving the MonsterAirborne state.
int MonsterIsHit;   //This will be changed by the collision detection module
int MonsterIsBusy;   //This will be changed by the animation engine, when something's up.
int MonsterTurning;  //This is 0 if not MonsterTurning, 1 if MonsterTurning left, -1 if MonsterTurning right.
//int MonsterFramesStopped;  //This will be totally obsolete as soon as the animation engine works.
int MonsterHitObstacle;    //This is for remembering if the airborne state included a wall collision.
#ifdef PC
extern FILE *shithead;
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



typedef struct Monster_movement_state_
{
   RLValue AccelerationValue;
   RLValue YAccelerationValue;
   RLValue TopSpeed;
   RLValue TopYSpeed;
   RLValue EnergyDrain;
   StateFunction WhatToDo;
   int numchanges;
   StateChange *ChangeList;
}MonsterMovementStateStructure;

MonsterMovementStateStructure MonsterMotions[31];

//I'll now create the raw materials for the state machine, all the state change functions and the
//state functions.
//RLValue MonsterCosine(RLValue DiffFrame)
//{
//   int i=RLInt(RLMultiply(DiffFrame,RLVal(2.0)));
//   if(i>9)i=9;
//   return MonsterCosineTable[i];
//}
//RLValue MonsterSine(RLValue DiffFrame)
//{
   //int i=RLInt(RLMultiply(DiffFrame,RLVal(2.0)));
   //if(i>9)i=9;
   //return MonsterSineTable[i];
//}
static int ToMonsterFBraking(void)
//I'll rely on this function only being called by accelerating or topspeed forward states,
//so that I won't have to write the checks.
{
//   if(MnstEngy<MonsterFBrakingMinEnergy)
//      return 0;
   if((MonsterMovementState==MonsterFTopSpeed4 || MonsterMovementState==MonsterFAccelerating4) && MnstEngy<MonsterFAccelerating4MinEnergy)
   {
      MonsterMovementState=MonsterFBraking;
      MonsterDistance=0;
      MonsterNumMovementFrames=0;
      return 1;
   }
   
   
   if((InputInt2&COMMANDBack)||(InputInt2&COMMANDDefenseShift))
   {
      MonsterMovementState=MonsterFBraking;
      MonsterDistance=0;
      MonsterNumMovementFrames=0;
      return 1;
   }
   if((MonsterMovementState==MonsterFTopSpeed4) && !( (InputInt2&COMMANDForward) && (InputInt2&COMMANDStrongShift) ))
   {
      MonsterMovementState=MonsterFBraking;
      MonsterDistance=0;
      MonsterNumMovementFrames=0;
      return 1;
   }
   return 0;
}
static int ToMonsterFDecelerating(void)
//Unfortunately, this one is intimately connected with current speed, state, and input.
//Except for the case in which the forward button has been taken off, because that will certainly lead to 
//deceleration, as this will only be called by states which have positive forward movement.

{
   if((MonsterMovementState==MonsterFTopSpeed3 || MonsterMovementState==MonsterFAccelerating3) && MnstEngy<MonsterFAccelerating3MinEnergy)
   {
      MonsterMovementState=MonsterFDecelerating;
//      MonsterDistance=0;
      MonsterNumMovementFrames=0;
      return 1;
   }
   if((MonsterMovementState==MonsterFTopSpeed2 || MonsterMovementState==MonsterFAccelerating2) && MnstEngy<MonsterFAccelerating2MinEnergy)
   {
      MonsterMovementState=MonsterFDecelerating;
//      MonsterDistance=0;
      MonsterNumMovementFrames=0;
      return 1;
   }
   if((MonsterMovementState==MonsterFTopSpeed1 || MonsterMovementState==MonsterFAccelerating1) && MnstEngy<MonsterFAccelerating1MinEnergy)
   {
      MonsterMovementState=MonsterFDecelerating;
//      MonsterDistance=0;
      MonsterNumMovementFrames=0;
      return 1;
   }

   if((MonsterMovementState==MonsterFBraking)&&(!((InputInt2&COMMANDBack)||(InputInt2&COMMANDDefenseShift))) && (MonsterSpeed<=MonsterMotions[MonsterFAccelerating3].TopSpeed) )
   {
      MonsterMovementState=MonsterFDecelerating;
      MonsterNumMovementFrames=0;
      return 1;
   }

   if( (!(InputInt2&COMMANDForward)) && MonsterSpeed>0)
   {
      MonsterMovementState=MonsterFDecelerating;
      MonsterNumMovementFrames=0;
      return 1;
   }
   //to get here, input must have forward key held down.
   if( (InputInt2 & COMMANDStrongShift) || (InputInt2 & COMMANDMediumShift))
      return 0;
   //Can't be decelerating if the player is trying to move as fast as possible.
   //Also can't decelerate out of a travel, have to brake.  So if Medium Shift
   //is held down, and you're losing speed, you have to be going faster than a 
   //run, and must be skidding  (i.e. braking)
   //Input can't have strong or medium shifts held down.
   if(InputInt2&COMMANDWeakShift)
   {
      if(MonsterSpeed>MonsterMotions[MonsterFAccelerating2].TopSpeed)
      {
         MonsterMovementState=MonsterFDecelerating;
         MonsterNumMovementFrames=0;
         return 1;
      }
      return 0;
   }
   //Input can't have any shifts held down.
   if(MonsterSpeed > MonsterMotions[MonsterFAccelerating1].TopSpeed)
   {
      MonsterMovementState=MonsterFDecelerating;
      MonsterNumMovementFrames=0;
      return 1;
   }
   return 0;

}

static int ToMonsterFAccelerating4(void)
{
//   extern int level;

   if(MnstEngy<MonsterFAccelerating4MinEnergy)
      return 0;
   if( (InputInt2&COMMANDForward) && (InputInt2&COMMANDStrongShift) )
      if(MonsterSpeed<MonsterMotions[MonsterFAccelerating4].TopSpeed)
      {
         if(((GameStates.CurrentLevel!=Hawaii) || (SpuddeMapHeight2(MonsterData.CurrentPosition.x,MonsterData.CurrentPosition.z)<=sealevel))) {
            MonsterMovementState=MonsterFAccelerating4;
            MonsterNumMovementFrames=0;
            return 1;
         }
      }
   return 0;
}
static int ToMonsterFTopSpeed4(void)
{
   if(MnstEngy<MonsterFTopSpeed4MinEnergy)
      return 0;
   if(MonsterMovementState==MonsterAirborne)
   {
      if(!MonsterMidair)
         if(MonsterSpeed>=MonsterMotions[MonsterFAccelerating4].TopSpeed)
         {
            MonsterSpeed=MonsterMotions[MonsterFAccelerating4].TopSpeed;
            MonsterMovementState=MonsterFTopSpeed4;
            MonsterNumMovementFrames=0;
			MonsterYSpeed=0;
            return 1;
         }
      return 0;
   }
//   if( (InputInt2&COMMANDForward) && (InputInt2&COMMANDStrongShift) )
      if(MonsterMovementState==MonsterFAccelerating4)//should be unnecessary
         if(MonsterSpeed>=MonsterMotions[MonsterFAccelerating4].TopSpeed)
         {
            MonsterSpeed=MonsterMotions[MonsterFAccelerating4].TopSpeed;
            MonsterMovementState=MonsterFTopSpeed4;
            MonsterNumMovementFrames=0;
			MonsterYSpeed=0;
            return 1;
         }
   return 0;
}
static int ToMonsterFAccelerating3(void)
{
   if(MnstEngy<MonsterFAccelerating3MinEnergy)
      return 0;
   if( (InputInt2&COMMANDForward) && (InputInt2& (COMMANDMediumShift|COMMANDStrongShift) ) )
      if(MonsterSpeed<MonsterMotions[MonsterFAccelerating3].TopSpeed&&MonsterSpeed>=MonsterMotions[MonsterFAccelerating2].TopSpeed)
      {
         MonsterMovementState=MonsterFAccelerating3;
         MonsterNumMovementFrames=0;
         return 1;
      }
   return 0;
}
static int ToMonsterFTopSpeed3(void)
{
   if(MnstEngy<MonsterFTopSpeed3MinEnergy)
      return 0;
   if(MonsterMovementState==MonsterAirborne)
   {
      if(!MonsterMidair)
         if(MonsterSpeed<MonsterMotions[MonsterFAccelerating4].TopSpeed && MonsterSpeed>=MonsterMotions[MonsterFAccelerating3].TopSpeed)
         {
            MonsterSpeed=MonsterMotions[MonsterFAccelerating3].TopSpeed;
            MonsterMovementState=MonsterFTopSpeed3;
            MonsterNumMovementFrames=0;
            return 1;
         }
      return 0;
   }
   if( (InputInt2&COMMANDForward) && (InputInt2& (COMMANDMediumShift|COMMANDStrongShift) ) )
      if(MonsterMovementState==MonsterFAccelerating3)
         if(MonsterSpeed>=MonsterMotions[MonsterFAccelerating3].TopSpeed)
         {
            MonsterSpeed=MonsterMotions[MonsterFAccelerating3].TopSpeed;
            MonsterMovementState=MonsterFTopSpeed3;
            MonsterNumMovementFrames=0;
            return 1;
         }
   return 0;
}
static int ToMonsterFAccelerating2(void)
{
   if(MnstEngy<MonsterFAccelerating2MinEnergy)
      return 0;

   if( (InputInt2&COMMANDForward) && (InputInt2&(COMMANDWeakShift|COMMANDMediumShift|COMMANDStrongShift)) )
      if(MonsterSpeed<MonsterMotions[MonsterFAccelerating2].TopSpeed && MonsterSpeed>=MonsterMotions[MonsterFAccelerating1].TopSpeed )
      {
         MonsterMovementState=MonsterFAccelerating2;
         MonsterNumMovementFrames=0;
         return 1;
      }
   return 0;
}
static int ToMonsterFTopSpeed2(void)
{
   if(MnstEngy<MonsterFTopSpeed2MinEnergy)
      return 0;
   if(MonsterMovementState==MonsterAirborne)
   {
      if(!MonsterMidair)
         if(MonsterSpeed<MonsterMotions[MonsterFAccelerating3].TopSpeed && MonsterSpeed>=MonsterMotions[MonsterFAccelerating2].TopSpeed)
         {
            MonsterSpeed=MonsterMotions[MonsterFAccelerating2].TopSpeed;
            MonsterMovementState=MonsterFTopSpeed2;
            MonsterNumMovementFrames=0;
            return 1;
         }
      return 0;
   }
   if( (InputInt2&COMMANDForward) && (InputInt2&(COMMANDWeakShift|COMMANDMediumShift|COMMANDStrongShift)) )
      if(MonsterMovementState==MonsterFAccelerating2)
         if(MonsterSpeed>=MonsterMotions[MonsterFAccelerating2].TopSpeed)
         {
            MonsterSpeed=MonsterMotions[MonsterFAccelerating2].TopSpeed;
            MonsterMovementState=MonsterFTopSpeed2;
            MonsterNumMovementFrames=0;
            return 1;
         }
   return 0;
}
static int ToMonsterFAccelerating1(void)
{
   if( InputInt2&COMMANDForward )
      if(MonsterSpeed<MonsterMotions[MonsterFAccelerating1].TopSpeed)
      {
         MonsterMovementState=MonsterFAccelerating1;
         MonsterNumMovementFrames=0;
         return 1;
      }
   return 0;
}
static int ToMonsterFTopSpeed1(void)
{
   if(MonsterMovementState==MonsterAirborne)
   {
      if(!MonsterMidair)
         if(MonsterSpeed<MonsterMotions[MonsterFAccelerating2].TopSpeed && MonsterSpeed>=MonsterMotions[MonsterFAccelerating1].TopSpeed)
         {
            MonsterSpeed=MonsterMotions[MonsterFAccelerating1].TopSpeed;
            MonsterMovementState=MonsterFTopSpeed1;
            MonsterNumMovementFrames=0;
            return 1;
         }
      return 0;
   }
   
   
   if(InputInt2&COMMANDForward)
      if(MonsterMovementState==MonsterFAccelerating1)
         if(MonsterSpeed>=MonsterMotions[MonsterFAccelerating1].TopSpeed)
         {
            MonsterSpeed=MonsterMotions[MonsterFAccelerating1].TopSpeed;
            MonsterMovementState=MonsterFTopSpeed1;
            MonsterNumMovementFrames=0;
            MonsterDistance=0;
            return 1;
         }
   return 0;
}

static int ToMonsterBBraking(void)
//I'll rely on this function only being called by accelerating or topspeed backward states,
//so that I won't have to write the checks.
{
   if((MonsterMovementState==MonsterFTopSpeed4 || MonsterMovementState==MonsterFAccelerating4) && MnstEngy<MonsterFAccelerating4MinEnergy)
   {
      MonsterMovementState=MonsterFBraking;
      MonsterDistance=0;
      MonsterNumMovementFrames=0;
      return 1;
   }
   if((InputInt2&COMMANDForward)||(InputInt2&COMMANDDefenseShift))
   {
      MonsterMovementState=MonsterBBraking;
      MonsterNumMovementFrames=0;
      return 1;
   }
   return 0;
}

static int ToMonsterBDecelerating(void)
//Unfortunately, this one is intimately connected with current speed, state, and input.
//Except for the case in which the back button has been taken off, because that will certainly lead to 
//deceleration, as this will only be called by states which have positive backward movement.
//Unlike the Forward case. you can't go from braking to decelerating  (This is subject to change)

{
   if((MonsterMovementState==MonsterBTopSpeed1 || MonsterMovementState==MonsterBAccelerating1) && MnstEngy<MonsterBAccelerating1MinEnergy)
   {
      MonsterMovementState=MonsterBDecelerating;
//      MonsterDistance=0;
      MonsterNumMovementFrames=0;
      return 1;
   }

   if( (!(InputInt2&COMMANDBack)) && MonsterSpeed>0)
   {
      MonsterMovementState=MonsterBDecelerating;
      MonsterNumMovementFrames=0;
      return 1;
   }
   //to get here, input must have back key held down.
   if( InputInt2 & (COMMANDStrongShift|COMMANDWeakShift) )
      return 0;
   //Can't be decelerating if the player is trying to move as fast as possible.  Either
   //we're moving at top speed or braking.
   //Input can't have strong shift held down.
   //Medium shift has no effect.
   //If we have the weak shift held down, and we're going too fast, we must be travelling
   //backward, or skidding to a halt, or whatever, and we would have to brake rather than decelerate.
   //Input can't have any shifts held down.
   if(MonsterSpeed > MonsterMotions[MonsterBAccelerating1].TopSpeed)
   {
      MonsterMovementState=MonsterBDecelerating;
      MonsterNumMovementFrames=0;
      return 1;
   }
   return 0;

}


static int ToMonsterBAccelerating2(void)
{
   if(MnstEngy<MonsterBAccelerating2MinEnergy)
      return 0;
   if( (InputInt2&COMMANDBack) && (InputInt2&COMMANDWeakShift) )
      if(MonsterSpeed<MonsterMotions[MonsterBAccelerating2].TopSpeed&&MonsterSpeed>=MonsterMotions[MonsterBAccelerating1].TopSpeed)
      {
         MonsterMovementState=MonsterBAccelerating2;
         MonsterNumMovementFrames=0;
         return 1;
      }
   return 0;
}
static int ToMonsterBTopSpeed2(void)
{
   if(MnstEngy<MonsterBTopSpeed2MinEnergy)
      return 0;
   if( (InputInt2&COMMANDBack) && (InputInt2&COMMANDWeakShift) )
      if(MonsterMovementState==MonsterBAccelerating2)
         if(MonsterSpeed>=MonsterMotions[MonsterBAccelerating2].TopSpeed)
         {
            MonsterSpeed=MonsterMotions[MonsterBAccelerating2].TopSpeed;
            MonsterMovementState=MonsterBTopSpeed2;
            MonsterNumMovementFrames=0;
            return 1;
         }
   return 0;
}
static int ToMonsterBAccelerating1(void)
{
   if(MnstEngy<MonsterBAccelerating1MinEnergy)
      return 0;
   if( InputInt2&COMMANDBack )
      if(MonsterSpeed<MonsterMotions[MonsterBAccelerating1].TopSpeed)
      {
         MonsterMovementState=MonsterBAccelerating1;
         MonsterNumMovementFrames=0;
         return 1;
      }
   return 0;
}
static int ToMonsterBTopSpeed1(void)
{
   if(MnstEngy<MonsterBTopSpeed1MinEnergy)
      return 0;
   if(InputInt2&COMMANDBack)
      if(MonsterMovementState==MonsterBAccelerating1)
         if(MonsterSpeed>=MonsterMotions[MonsterBAccelerating1].TopSpeed)
         {
            MonsterSpeed=MonsterMotions[MonsterBAccelerating1].TopSpeed;
            MonsterMovementState=MonsterBTopSpeed1;
            MonsterNumMovementFrames=0;
            return 1;
         }
   return 0;
}


/*static int ToMonsterRBraking(void)
//I'll rely on this function only being called by accelerating or topspeed right states,
//so that I won't have to write the checks.
{
   return 0;
}
  */
static int ToMonsterRDecelerating(void)
//This is different from F and B deceleration, because there is no gradation of movement speeds.
//Either there's a Super Surf, which you brake while leaving, or you're at speed1.  So there's no
//checking of shift keys.  If you're not trying to move right, you're not moving right.  That's all.

{
   if( (!( (InputInt2&COMMANDRight)&&(InputInt2&COMMANDDefenseShift) )) && MonsterSpeed>0)
   {
      MonsterMovementState=MonsterRDecelerating;
      MonsterNumMovementFrames=0;
      return 1;
   }

   return 0;

}


static int ToMonsterRAccelerating1(void)
{
   if(MnstEngy<MonsterRAccelerating1MinEnergy)
      return 0;
   if((InputInt2&COMMANDRight)&&(InputInt2&COMMANDDefenseShift))
      if(MonsterSpeed<MonsterMotions[MonsterRAccelerating1].TopSpeed)
      {
         MonsterMovementState=MonsterRAccelerating1;
         MonsterNumMovementFrames=0;
         return 1;
      }
   return 0;
}
static int ToMonsterRTopSpeed1(void)
{
   if(MnstEngy<MonsterRTopSpeed1MinEnergy)
      return 0;
   if((InputInt2&COMMANDRight)&&(InputInt2&COMMANDDefenseShift))
      if(MonsterMovementState==MonsterRAccelerating1)
         if(MonsterSpeed>=MonsterMotions[MonsterRAccelerating1].TopSpeed)
         {
            MonsterSpeed=MonsterMotions[MonsterRAccelerating1].TopSpeed;
            MonsterMovementState=MonsterRTopSpeed1;
            MonsterNumMovementFrames=0;
            return 1;
         }
   return 0;
}

/*static int ToMonsterLBraking(void)
//I'll rely on this function only being called by accelerating or topspeed right states,
//so that I won't have to write the checks.
{
   return 0;
} */

static int ToMonsterLDecelerating(void)
//This is different from F and B deceleration, because there is no gradation of movement speeds.
//Either there's a Super Surf, which you brake while leaving, or you're at speed1.  So there's no
//checking of shift keys.  If you're not trying to move right, you're not moving right.  That's all.

{
   if( (!  ( (InputInt2&COMMANDLeft)&& (InputInt2&COMMANDDefenseShift) ) ) && MonsterSpeed>0)
   {
      MonsterMovementState=MonsterLDecelerating;
      MonsterNumMovementFrames=0;
      return 1;
   }
   return 0;

}


static int ToMonsterLAccelerating1(void)
{
   if(MnstEngy<MonsterLAccelerating1MinEnergy)
      return 0;
   if((InputInt2&COMMANDLeft)&&(InputInt2&COMMANDDefenseShift))
      if(MonsterSpeed<MonsterMotions[MonsterLAccelerating1].TopSpeed)
      {
         MonsterMovementState=MonsterLAccelerating1;
         MonsterNumMovementFrames=0;
         return 1;
      }
   return 0;
}
static int ToMonsterLTopSpeed1(void)
{
   if(MnstEngy<MonsterLTopSpeed1MinEnergy)
      return 0;
   if((InputInt2&COMMANDLeft)&&(InputInt2&COMMANDDefenseShift))
      if(MonsterMovementState==MonsterLAccelerating1)
         if(MonsterSpeed>=MonsterMotions[MonsterLAccelerating1].TopSpeed)
         {
            MonsterSpeed=MonsterMotions[MonsterLAccelerating1].TopSpeed;
            MonsterMovementState=MonsterLTopSpeed1;
            MonsterNumMovementFrames=0;
            return 1;
         }
   return 0;
}

static int ToMonsterStopped(void)
{
   if((MonsterMovementState == MonsterAirborne) && !MonsterMidair)//Hit something in MonsterMidair
   {
      if(MonsterHitObstacle)
      {
         MonsterMovementState=MonsterStopped;
         MonsterDistance=0;
         MonsterNumMovementFrames=0;
         //MonsterFramesStopped=NumFramesAcrobatic;
         MonsterHitObstacle=0;
         return 1;
      }
      if(MonsterSpeed<MonsterMotions[MonsterFAccelerating1].TopSpeed)
      {
         MonsterMovementState=MonsterStopped;
         MonsterDistance=0;
         MonsterNumMovementFrames=0;
//         MonsterAnimationState=MonsterJumpStop;
//         MonsterAnimationFrame=
         return 1;
      }
   }
   
   if( (MonsterMovementState!=MonsterAirborne) && MonsterHitObstacle && (MonsterSpeed>MonsterMotions[MonsterFAccelerating2].TopSpeed) )//Ran into something.
   {
      MonsterMovementState=MonsterStopped;
      MonsterDistance=0;
      MonsterNumMovementFrames=0;
//      MonsterFramesStopped=NumFramesAcrobatic;
      MonsterHitObstacle=0;
      return 1;
   }
/*   if(MonsterMovementState==MonsterWaiting && (InputInt2&(COMMANDCrouch|COMMANDHighAttack|COMMANDLowAttack) ))
   {
      MonsterMovementState=MonsterStopped;
      MonsterDistance=0;
      MonsterNumMovementFrames=0;
      MonsterFramesStopped=NumFramesCrouch;//This will be meaningless soon, and will have to be replaced
      //with a message from the animation engine that it's ok to move again.
      MonsterHitObstacle=0;
      return 1;
   }*/
   return 0;
   
}

static int ToMonsterWaiting(void)
{
   if(MonsterMovementState == MonsterFDecelerating || MonsterMovementState == MonsterBDecelerating || MonsterMovementState == MonsterLDecelerating || MonsterMovementState == MonsterRDecelerating ||
      MonsterMovementState == MonsterFBraking      || MonsterMovementState == MonsterBBraking      || MonsterMovementState == MonsterLBraking      || MonsterMovementState == MonsterRBraking)
      if(MonsterSpeed <=0)
      {
         MonsterMovementState = MonsterWaiting;
         MonsterDistance=0;
         MonsterNumMovementFrames=0;
         return 1;
      }
/*   if(MonsterMovementState == MonsterStopped)
      if(MonsterNumMovementFrames>=MonsterFramesStopped)
      {
         MonsterMovementState=MonsterWaiting;
         MonsterDistance=0;
         MonsterNumMovementFrames=0;
         return 1;
      }*/
   if(MonsterMovementState == MonsterAirborne)
   {
      if(!(MonsterMidair||MonsterHitObstacle))
      {
         MonsterMovementState=MonsterWaiting;
         MonsterDistance=0;
         MonsterNumMovementFrames=0;
         return 1;
      }
   }
   else
      if(MonsterHitObstacle&&MonsterSpeed<=MonsterMotions[MonsterFAccelerating2].TopSpeed)//walked into something.
      {
         MonsterMovementState=MonsterWaiting;
         MonsterDistance=0;
         MonsterNumMovementFrames=0;
         return 1;
      }
   return 0;
}

static int ToMonsterJumping(void)
{
   if(MnstEngy<MonsterJumpingMinEnergy)
      return 0;
   if((!MonsterMidair) && (!MonsterIsHit) && (!MonsterIsBusy) )
      if(InputInt2&COMMANDJump)
      {
         MonsterMovementState=MonsterJumping;
         MonsterDistance=0;
         MonsterNumMovementFrames=0;
         MonsterYSpeed=0;
         return 1;
      }
      return 0;
}

static int ToMonsterAirborne(void)
{
//   extern int level;
   if(GameStates.CurrentLevel==NewYork||GameStates.CurrentLevel==Tokyo)
   {
      if((MonsterMovementState==MonsterFTopSpeed4) &&( (!( (InputInt2&COMMANDForward) && (InputInt2&COMMANDStrongShift) ))||(MnstEngy<MonsterFAccelerating4MinEnergy)))
      {
         if(SpuddeMapHeight2(MonsterData.CurrentPosition.x,MonsterData.CurrentPosition.z)+RLVal(0.01)<=MonsterData.CurrentPosition.y)
	     {
            MonsterMovementState=MonsterAirborne;
			MonsterAnimationState=MonsterJumpFreeze;
            MonsterDistance=0;
            MonsterNumMovementFrames=0;
            return 1;
	     }
      }
   }

   if(MonsterMovementState==MonsterJumping)
   {
      if((!(InputInt2&COMMANDJump)) || (MnstEngy<MonsterJumpingMinEnergy))
      {
         MonsterMidair=1;
         MonsterMovementState=MonsterAirborne;
         MonsterDistance=0;
         MonsterNumMovementFrames=0;
         return 1;
      }
      if(MonsterYSpeed>MaxYVel)
      {
         MonsterMidair=1;
         MonsterYSpeed=MaxYVel;
         MonsterMovementState=MonsterAirborne;
         MonsterDistance=0;
         MonsterNumMovementFrames=0;
         return 1;
      }
   }
   else if(MonsterMidair)
   {
      MonsterMovementState=MonsterAirborne;
      MonsterDistance=0;
      MonsterNumMovementFrames=0;
      return 1;
   }
   return 0;
}
/*
static int ToMonsterKnockBackward(void)
{
   return 0;
} *///this function isn't needed because the MKB state is only entered when the animation engine forces it.
//Just like the normal way to enter MonsterStopped is from the animation engine, but this is exclusive.

static void MonsterWaitingFunction(MovingObjectData mover)
{
   RLVector dir;
   RLVector up;
   RLVector newdir;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   mover->ProjectedPosition.x=mover->CurrentPosition.x;
   mover->ProjectedPosition.y=mover->CurrentPosition.y;
   mover->ProjectedPosition.z=mover->CurrentPosition.z;
   if( (InputInt2&COMMANDLeft) && !(InputInt2&COMMANDDefenseShift)  &&!(InputInt2&COMMANDRight) )
   {
      MonsterTurning=1;
	  if(MonsterTheta>=0)
	  {
		  MonsterTheta = -MonsterTurnAcceleration;
	  }
	  else
	  {
		  MonsterTheta -= (RLMultiply(DiffFrame,MonsterTurnAcceleration));
	  }
	  if(MonsterTheta < -MonsterTurnMaximum)
	  {
		  MonsterTheta = -MonsterTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
   }
   else if( (InputInt2&COMMANDRight) && !(InputInt2&COMMANDDefenseShift)  &&!(InputInt2&COMMANDLeft) )
   {
      MonsterTurning=-1;
	  if(MonsterTheta<=0)
	  {
		  MonsterTheta = MonsterTurnAcceleration;
	  }
	  else
	  {
		  MonsterTheta += (RLMultiply(DiffFrame,MonsterTurnAcceleration));
	  }
	  if(MonsterTheta > MonsterTurnMaximum)
	  {
		  MonsterTheta = MonsterTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
   }
   else
   {
      MonsterTurning=0;
	  MonsterTheta=0;
   }

   MonsterVelocity.x=MonsterVelocity.y=MonsterVelocity.z=0;
   MonsterSpeed=0;
   MonsterYSpeed=0;
   MonsterData.DamageICause = 0;
}
static void MonsterFAccelerating1Function(MovingObjectData mover)
{
   RLVector   dir,newdir;
   int result;
   RLVector up;
   RLValue Distance;
   RLValue DIFFRAME;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   if(SpuddeMapHeight2(mover->CurrentPosition.x,mover->CurrentPosition.z)<sealevel)
      DIFFRAME=RLDivide(DiffFrame,MonsterGoopiness);
   else
      DIFFRAME=DiffFrame;

   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);
   if( (InputInt2&COMMANDLeft) && !(InputInt2&COMMANDDefenseShift)  &&!(InputInt2&COMMANDRight) )
   {
      MonsterTurning=1;
	  if(MonsterTheta>=0)
	  {
		  MonsterTheta = -MonsterTurnAcceleration;
	  }
	  else
	  {
		  MonsterTheta -= (RLMultiply(DiffFrame,MonsterTurnAcceleration));
	  }
	  if(MonsterTheta < -MonsterTurnMaximum)
	  {
		  MonsterTheta = -MonsterTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
   }
   else if( (InputInt2&COMMANDRight) && !(InputInt2&COMMANDDefenseShift)  &&!(InputInt2&COMMANDLeft) )
   {
      MonsterTurning=-1;
	  if(MonsterTheta<=0)
	  {
		  MonsterTheta = MonsterTurnAcceleration;
	  }
	  else
	  {
		  MonsterTheta += (RLMultiply(DiffFrame,MonsterTurnAcceleration));
	  }
	  if(MonsterTheta > MonsterTurnMaximum)
	  {
		  MonsterTheta = MonsterTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
   }
   else
   {
      MonsterTurning=0;
	  MonsterTheta=0;
   }
   if(MonsterAnimationState!=MonsterIntoIntoRun)
      MonsterSpeed+=RLMultiply(MonsterMotions[MonsterMovementState].AccelerationValue,DIFFRAME);
   if(MonsterSpeed>MonsterMotions[MonsterMovementState].TopSpeed) MonsterSpeed=MonsterMotions[MonsterMovementState].TopSpeed;
   if(MonsterSpeed<0) MonsterSpeed=0;
   Distance=RLMultiply(MonsterSpeed,DIFFRAME);
   MonsterVelocity.x=RLMultiply(-dir.x,Distance);
   MonsterVelocity.z=RLMultiply(-dir.z,Distance);
   MonsterDistance+=Distance;
   MonsterVelocity.y=RLVal(0);

   result=SpuddeMoveOnGround(mover,&MonsterVelocity,&MonsterGradientFactor);
   if(result&2)
   {
      MonsterHitObstacle=1;
      MonsterSpeed=0;
   }
   if(result&1)
   {
      MonsterMidair=1;
   }
   MonsterData.DamageICause = MonsterMotionDamage*MonsterSpeed/MonsterMaxFVel4;
}

static void MonsterFAccelerating2Function(MovingObjectData mover)
{
   RLVector   dir,newdir;
   int result;
   RLVector up;
   RLValue Distance;
   RLValue DIFFRAME;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   if(SpuddeMapHeight2(mover->CurrentPosition.x,mover->CurrentPosition.z)<sealevel)
      DIFFRAME=RLDivide(DiffFrame,MonsterGoopiness);
   else
      DIFFRAME=DiffFrame;

   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);
   if( (InputInt2&COMMANDLeft) && !(InputInt2&COMMANDDefenseShift)  &&!(InputInt2&COMMANDRight) )
   {
      MonsterTurning=1;
	  if(MonsterTheta>=0)
	  {
		  MonsterTheta = -MonsterTurnAcceleration;
	  }
	  else
	  {
		  MonsterTheta -= (RLMultiply(DiffFrame,MonsterTurnAcceleration));
	  }
	  if(MonsterTheta < -MonsterTurnMaximum)
	  {
		  MonsterTheta = -MonsterTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
   }
   else if( (InputInt2&COMMANDRight) && !(InputInt2&COMMANDDefenseShift)  &&!(InputInt2&COMMANDLeft) )
   {
      MonsterTurning=-1;
	  if(MonsterTheta<=0)
	  {
		  MonsterTheta = MonsterTurnAcceleration;
	  }
	  else
	  {
		  MonsterTheta += (RLMultiply(DiffFrame,MonsterTurnAcceleration));
	  }
	  if(MonsterTheta > MonsterTurnMaximum)
	  {
		  MonsterTheta = MonsterTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
   }
   else
   {
      MonsterTurning=0;
	  MonsterTheta=0;
   }
   MonsterSpeed+=RLMultiply(MonsterMotions[MonsterMovementState].AccelerationValue,DIFFRAME);
   if(MonsterSpeed>MonsterMotions[MonsterMovementState].TopSpeed) MonsterSpeed=MonsterMotions[MonsterMovementState].TopSpeed;
   if(MonsterSpeed<0) MonsterSpeed=0;
   Distance=RLMultiply(MonsterSpeed,DIFFRAME);
   MonsterVelocity.x=RLMultiply(-dir.x,Distance);
   MonsterVelocity.z=RLMultiply(-dir.z,Distance);
   MonsterDistance+=Distance;
   MonsterVelocity.y=RLVal(0);

   result=SpuddeMoveOnGround(mover,&MonsterVelocity,&MonsterGradientFactor);
   if(result&2)
   {
      MonsterHitObstacle=1;
      MonsterSpeed=0;
   }
   if(result&1)
   {
      MonsterMidair=1;
   }
   MonsterData.DamageICause = MonsterMotionDamage*MonsterSpeed/MonsterMaxFVel4;
}

static void MonsterFTopSpeed4Function(MovingObjectData mover)
{
   RLVector   dir,newdir;
   int result;
//   extern int level;
   RLVector up;
   RLValue Distance;
   RLValue DIFFRAME;
//   FILE *shithead;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   if(SpuddeMapHeight2(mover->CurrentPosition.x,mover->CurrentPosition.z)<sealevel)
      DIFFRAME=RLDivide(DiffFrame,MonsterGoopiness);
   else
      DIFFRAME=DiffFrame;

   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);
   if( (InputInt2&COMMANDLeft) && !(InputInt2&COMMANDDefenseShift)  &&!(InputInt2&COMMANDRight) )
   {
      MonsterTurning=1;
	  if(MonsterTheta>=0)
	  {
		  MonsterTheta = -MonsterTurnAcceleration;
	  }
	  else
	  {
		  MonsterTheta -= (RLMultiply(DiffFrame,MonsterTurnAcceleration));
	  }
	  if(MonsterTheta < -MonsterTurnMaximum)
	  {
		  MonsterTheta = -MonsterTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
   }
   else if( (InputInt2&COMMANDRight) && !(InputInt2&COMMANDDefenseShift)  &&!(InputInt2&COMMANDLeft) )
   {
      MonsterTurning=-1;
	  if(MonsterTheta<=0)
	  {
		  MonsterTheta = MonsterTurnAcceleration;
	  }
	  else
	  {
		  MonsterTheta += (RLMultiply(DiffFrame,MonsterTurnAcceleration));
	  }
	  if(MonsterTheta > MonsterTurnMaximum)
	  {
		  MonsterTheta = MonsterTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
   }
   else
   {
      MonsterTurning=0;
	  MonsterTheta=0;
   }
   MonsterSpeed+=RLMultiply(MonsterMotions[MonsterMovementState].AccelerationValue,DIFFRAME);
   if(MonsterSpeed>MonsterMotions[MonsterMovementState].TopSpeed) MonsterSpeed=MonsterMotions[MonsterMovementState].TopSpeed;
   if(MonsterSpeed<0) MonsterSpeed=0;
   Distance=RLMultiply(MonsterSpeed,DIFFRAME);
   MonsterVelocity.x=RLMultiply(-dir.x,Distance);
   MonsterVelocity.z=RLMultiply(-dir.z,Distance);
   MonsterDistance+=Distance;
   if(GameStates.CurrentLevel==Hawaii)
   {
      if(SpuddeMapHeight2(MonsterData.CurrentPosition.x,MonsterData.CurrentPosition.z)>sealevel)
      {
	     MonsterSpeed=MonsterMotions[MonsterFTopSpeed3].TopSpeed;
		 MonsterMovementState=MonsterFTopSpeed3;
	  }
      MonsterVelocity.y=RLVal(0);
      result=SpuddeMoveOnGround(mover,&MonsterVelocity,&MonsterGradientFactor);
      if(MonsterData.ProjectedPosition.y<SpuddeMonstersAltitudeWhenSwimming)
	     MonsterData.ProjectedPosition.y=SpuddeMonstersAltitudeWhenSwimming;
   }
   else if(GameStates.CurrentLevel==NewYork|| GameStates.CurrentLevel==Tokyo)
   {
	  if(InputInt2&COMMANDJump)
	  {
         MonsterYSpeed += RLMultiply3(RLVal(0.2), -MonsterGravity,DIFFRAME);
	  }
	  else
	  {
         MonsterYSpeed += RLMultiply3(RLVal(0.2), MonsterGravity,DIFFRAME);
	  }
      MonsterVelocity.y=RLMultiply(MonsterYSpeed,DIFFRAME);

	  if(MonsterVelocity.y<=0)
	  {
	     if(SpuddeMapHeight2(MonsterData.CurrentPosition.x,MonsterData.CurrentPosition.z)+RLVal(0.01)>=MonsterData.CurrentPosition.y)
		 {
		    MonsterYSpeed=0;
			MonsterVelocity.y=0;
			result=SpuddeMoveOnGround(mover,&MonsterVelocity,&MonsterGradientFactor);
		   if(result&2)
		   {
		      MonsterHitObstacle=1;
		      MonsterSpeed=0;
		   }
		   if(result&1)
		   {
		      MonsterMidair=1;
		   }
		   return;
		 }
	  }
	   MonsterHitObstacle=0;
	   MonsterMidair=0;
      result=SpuddeMoveInAir(mover,&MonsterVelocity);
	   if(result&2)
	   {
	      MonsterHitObstacle=1;
	      MonsterSpeed=0;
	      MonsterYSpeed=0;
	   }
	   return;
   }
   else 
   {
      MonsterVelocity.y=RLVal(0);
      result=SpuddeMoveOnGround(mover,&MonsterVelocity,&MonsterGradientFactor);
   }


   if(result&2)
   {
      MonsterHitObstacle=1;
      MonsterSpeed=0;
   }
   if(result&1)
   {
      MonsterMidair=1;
   }
   MonsterData.DamageICause = MonsterMotionDamage*MonsterSpeed/MonsterMaxFVel4;
}



//static StateFunction MonsterFAccelerating2Function = MonsterFAccelerating1Function;
static StateFunction MonsterFAccelerating3Function = MonsterFAccelerating2Function;
static StateFunction MonsterFAccelerating4Function = MonsterFAccelerating2Function;
static StateFunction MonsterFTopSpeed1Function = MonsterFAccelerating2Function;
static StateFunction MonsterFTopSpeed2Function = MonsterFAccelerating2Function;
static StateFunction MonsterFTopSpeed3Function = MonsterFAccelerating2Function;
static StateFunction MonsterFDeceleratingFunction = MonsterFAccelerating2Function;
static StateFunction MonsterFBrakingFunction = MonsterFAccelerating2Function;

static void MonsterBAccelerating1Function(MovingObjectData mover)
{
   RLVector   dir,newdir;
   int result;
   RLVector up;
   RLValue Distance;
   RLValue DIFFRAME;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   if(SpuddeMapHeight2(mover->CurrentPosition.x,mover->CurrentPosition.z)<sealevel)
      DIFFRAME=RLDivide(DiffFrame,MonsterGoopiness);
   else
      DIFFRAME=DiffFrame;

   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);
   if( (InputInt2&COMMANDLeft) && !(InputInt2&COMMANDDefenseShift)  &&!(InputInt2&COMMANDRight) )
   {
      MonsterTurning=1;
	  if(MonsterTheta>=0)
	  {
		  MonsterTheta = -MonsterTurnAcceleration;
	  }
	  else
	  {
		  MonsterTheta -= (RLMultiply(DiffFrame,MonsterTurnAcceleration));
	  }
	  if(MonsterTheta < -MonsterTurnMaximum)
	  {
		  MonsterTheta = -MonsterTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
   }
   else if( (InputInt2&COMMANDRight) && !(InputInt2&COMMANDDefenseShift)  &&!(InputInt2&COMMANDLeft) )
   {
      MonsterTurning=-1;
	  if(MonsterTheta<=0)
	  {
		  MonsterTheta = MonsterTurnAcceleration;
	  }
	  else
	  {
		  MonsterTheta += (RLMultiply(DiffFrame,MonsterTurnAcceleration));
	  }
	  if(MonsterTheta > MonsterTurnMaximum)
	  {
		  MonsterTheta = MonsterTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
   }
   else
   {
      MonsterTurning=0;
	  MonsterTheta=0;
   }
   MonsterSpeed+=RLMultiply(MonsterMotions[MonsterMovementState].AccelerationValue,DIFFRAME);
   if(MonsterSpeed>MonsterMotions[MonsterMovementState].TopSpeed) MonsterSpeed=MonsterMotions[MonsterMovementState].TopSpeed;
   if(MonsterSpeed<0) MonsterSpeed=0;
   Distance=RLMultiply(MonsterSpeed,DIFFRAME);
   MonsterVelocity.x=RLMultiply(dir.x,Distance);
   MonsterVelocity.z=RLMultiply(dir.z,Distance);
   MonsterVelocity.y=RLVal(0);
   MonsterDistance+=Distance;


   result=SpuddeMoveOnGround(mover,&MonsterVelocity,&MonsterGradientFactor);
   if(result&2)
   {
      MonsterHitObstacle=1;
      MonsterSpeed=0;
   }
   if(result&1)
   {
      MonsterMidair=1;
   }
   MonsterData.DamageICause = MonsterMotionDamage*MonsterSpeed/MonsterMaxFVel4;
}
static StateFunction MonsterBAccelerating2Function = MonsterBAccelerating1Function;
static StateFunction MonsterBTopSpeed1Function = MonsterBAccelerating1Function;
static StateFunction MonsterBTopSpeed2Function = MonsterBAccelerating1Function;
static StateFunction MonsterBDeceleratingFunction = MonsterBAccelerating1Function;

static void MonsterBBrakingFunction(MovingObjectData mover)
{
   RLVector   dir;
   int result;
   RLVector up;
   RLValue Distance;
   RLValue DIFFRAME;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   if(SpuddeMapHeight2(mover->CurrentPosition.x,mover->CurrentPosition.z)<sealevel)
      DIFFRAME=RLDivide(DiffFrame,MonsterGoopiness);
   else
      DIFFRAME=DiffFrame;

   MonsterTurning=0;
//   RLFrameSetRotation(mover->PositioningFrame,scene,RLVal(0),RLVal(1),RLVal(0),RLVal(0));
   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);
   MonsterSpeed+=RLMultiply(MonsterMotions[MonsterMovementState].AccelerationValue,DIFFRAME);
   if(MonsterSpeed>MonsterMotions[MonsterMovementState].TopSpeed) MonsterSpeed=MonsterMotions[MonsterMovementState].TopSpeed;
   if(MonsterSpeed<0) MonsterSpeed=0;
   Distance=RLMultiply(MonsterSpeed,DIFFRAME);
   MonsterVelocity.x=RLMultiply(dir.x,Distance);
   MonsterVelocity.z=RLMultiply(dir.z,Distance);
   MonsterVelocity.y=RLVal(0);
   MonsterDistance+=Distance;
   
//   shithead=fopen("shit.out","a");
//   fprintf(shithead,"in BACC, Distance = %d\n",MonsterDistance);
//   fclose(shithead);
   
   result=SpuddeMoveOnGround(mover,&MonsterVelocity,&MonsterGradientFactor);

   if(result&2)
   {
      MonsterHitObstacle=1;
      MonsterSpeed=0;
   }
   if(result&1)
   {
      MonsterMidair=1;
   }
   MonsterData.DamageICause = MonsterMotionDamage*MonsterSpeed/MonsterMaxFVel4;
}
static void MonsterLAccelerating1Function(MovingObjectData mover)
{
   RLVector   dir;
   int result;
   RLVector up;
   RLValue Distance;
   RLValue DIFFRAME;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   if(SpuddeMapHeight2(mover->CurrentPosition.x,mover->CurrentPosition.z)<sealevel)
      DIFFRAME=RLDivide(DiffFrame,MonsterGoopiness);
   else
      DIFFRAME=DiffFrame;

   MonsterTurning=0;
//   RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLVal(0));
   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);
   MonsterSpeed+=RLMultiply(MonsterMotions[MonsterMovementState].AccelerationValue,DIFFRAME);
   if(MonsterSpeed>MonsterMotions[MonsterMovementState].TopSpeed) MonsterSpeed=MonsterMotions[MonsterMovementState].TopSpeed;
   if(MonsterSpeed<0) MonsterSpeed=0;
   Distance=RLMultiply(DIFFRAME,MonsterSpeed);
   MonsterVelocity.x=RLMultiply(dir.z,Distance);
   MonsterVelocity.z=RLMultiply(-dir.x,Distance);
   MonsterVelocity.y=RLVal(0);
   MonsterDistance+=Distance;
//   shithead=fopen("shit.out","a");
//   fprintf(shithead,"in LACC, Distance = %d\n",MonsterDistance);
//   fclose(shithead);


   result=SpuddeMoveOnGround(mover,&MonsterVelocity,&MonsterGradientFactor);

   if(result&2)
   {
      MonsterHitObstacle=1;
      MonsterSpeed=0;
   }
   if(result&1)
   {
      MonsterMidair=1;
   }
   MonsterData.DamageICause = MonsterMotionDamage*MonsterSpeed/MonsterMaxFVel4;
}
static StateFunction MonsterLTopSpeed1Function = MonsterLAccelerating1Function;
static StateFunction MonsterLDeceleratingFunction = MonsterLAccelerating1Function;
static StateFunction MonsterLBrakingFunction = MonsterLAccelerating1Function;
static void MonsterRAccelerating1Function(MovingObjectData mover)
{
   int result;
   RLVector   dir;
   RLVector up;
   RLValue Distance;
   RLValue DIFFRAME;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   if(SpuddeMapHeight2(mover->CurrentPosition.x,mover->CurrentPosition.z)<sealevel)
      DIFFRAME=RLDivide(DiffFrame,MonsterGoopiness);
   else
      DIFFRAME=DiffFrame;

   MonsterTurning=0;
   //RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLVal(0));
   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);
   MonsterSpeed+=RLMultiply(MonsterMotions[MonsterMovementState].AccelerationValue,DIFFRAME);
   if(MonsterSpeed>MonsterMotions[MonsterMovementState].TopSpeed) MonsterSpeed=MonsterMotions[MonsterMovementState].TopSpeed;
   if(MonsterSpeed<0) MonsterSpeed=0;
   Distance=RLMultiply(MonsterSpeed,DIFFRAME);
   MonsterVelocity.x=RLMultiply(-dir.z,Distance);
   MonsterVelocity.z=RLMultiply(dir.x,Distance);
   MonsterVelocity.y=RLVal(0);
   MonsterDistance+=Distance;
//   shithead=fopen("shit.out","a");
//   fprintf(shithead,"in RACC, Distance = %d\n",MonsterDistance);
//   fclose(shithead);


   result=SpuddeMoveOnGround(mover,&MonsterVelocity,&MonsterGradientFactor);

   if(result&2)
   {
      MonsterHitObstacle=1;
      MonsterSpeed=0;
   }
   if(result&1)
   {
      MonsterMidair=1;
   }
   MonsterData.DamageICause = MonsterMotionDamage*MonsterSpeed/MonsterMaxFVel4;
}

static StateFunction MonsterRTopSpeed1Function = MonsterRAccelerating1Function;
static StateFunction MonsterRDeceleratingFunction = MonsterRAccelerating1Function;
static StateFunction MonsterRBrakingFunction = MonsterRAccelerating1Function;

static void MonsterJumpingFunction(MovingObjectData mover)
{
   int result;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLValue DIFFRAME;
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   if(mover->CurrentPosition.y<sealevel)
      DIFFRAME=RLDivide(DiffFrame,MonsterGoopiness);
   else
      DIFFRAME=DiffFrame;
//   int x1,y1,x2,y2,x3,y3;
//   RLValue X1,Y1,Z1,X2,Y2,Z2,X3,Y3,Z3;
//   int bonk;
//   RLFrame scene = RLFrameGetScene(mover);
//   RLVector   dir;
//   RLVector   MonsterPosition;
// RLVector MonsterVelocity;
//   RLVector up;

//   RLFrameGetPosition(mover,scene,&MonsterPosition);
//   RLFrameGetOrientation(mover,scene,&dir,&up);
//   RLVector position;
//   RLFrameGetPosition(mover,RLFrameGetScene(mover),&position);
   MonsterTurning=0;
//   RLFrameSetRotation(mover->PositioningFrame,scene,RLVal(0),RLVal(1),RLVal(0),RLVal(0));
   MonsterYSpeed+=RLMultiply(MonsterMotions[MonsterMovementState].YAccelerationValue,DIFFRAME);
   
//   shithead=fopen("shit.out","a");
//   fprintf(shithead,"YV = %d, YPos = %d\n",MonsterYSpeed,position.y);
//   fprintf(shithead,"MonsterAnimationFrame = %.3f\n",RLFloat(MonsterAnimationFrame));
//   fclose(shithead);
//   if(MonsterYSpeed>MonsterMotions[MonsterMovementState].TopYSpeed) MonsterYSpeed=MonsterMotions[MonsterMovementState].TopYSpeed;
//   if(MonsterYSpeed<0) MonsterYSpeed=0;
//   MonsterVelocity.x=RLMultiply(dir.x,MonsterSpeed);
//   MonsterVelocity.z=RLMultiply(dir.z,MonsterSpeed);
   MonsterVelocity.y=RLMultiply(MonsterYSpeed,DIFFRAME);
//   shithead=fopen("shit.out","a");
//   fprintf(shithead,"MonsterVelocity = %d, %d, %d\n",MonsterVelocity.x,MonsterVelocity.y, MonsterVelocity.z);
//   fprintf(shithead,"MonsterYSpeed = %d, YAcceleration = %d\n",MonsterYSpeed,MonsterMotions[MonsterMovementState].YAccelerationValue);
//   fclose(shithead);
   MonsterHitObstacle=0;
   MonsterMidair=0;
   result=SpuddeMoveInAir(mover,&MonsterVelocity);
   if(result&2)
   {
      MonsterHitObstacle=1;
      MonsterSpeed=0;
      MonsterYSpeed=0;
   }
   if(result&1)
   {                                                     
      MonsterMidair=1;
   }

   MonsterData.DamageICause = MonsterMotionDamage*MonsterSpeed/MonsterMaxFVel4;
}
static StateFunction MonsterAirborneFunction = MonsterJumpingFunction;
static void MonsterStoppedFunction(MovingObjectData mover)
{
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   MonsterTurning=0;
   MonsterData.DamageICause = 0;
//   RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLVal(0));
}

static void MonsterKnockBackwardFunction(MovingObjectData mover)
{
   RLVector newdir, dir;
   int result;
   RLVector up;
   RLValue Distance;
   RLValue DIFFRAME;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   if(SpuddeMapHeight2(mover->CurrentPosition.x,mover->CurrentPosition.z)<sealevel)
      DIFFRAME=RLDivide(DiffFrame,MonsterGoopiness);
   else
      DIFFRAME=DiffFrame;
   //MonsterSpeed=MonsterKnockBackwardSpeed;
   MonsterSpeed=RLVectorModulus(&MonsterFallDownDirection);
//   RLFrameGetOrientation(mover,scene,&dir,&up);
   Distance=RLMultiply(MonsterSpeed,DIFFRAME);
   //MonsterVelocity.x=RLMultiply(MonsterFallDownDirection.x,Distance);
   //MonsterVelocity.z=RLMultiply(MonsterFallDownDirection.z,Distance);
   //MonsterVelocity.y=RLVal(0);
   RLVectorScale(&MonsterVelocity, &MonsterFallDownDirection, DIFFRAME);

   MonsterDistance+=Distance;

   RLVectorScale(&MonsterFallDownDirection, &MonsterFallDownDirection, RLVal(1.0) - RLMultiply(RLVal(MonsterSlidingFriction), DiffFrame));

   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);
   if( MonsterTheta<0 )
   {
      MonsterTurning=1;
		  MonsterTheta += (RLMultiply(DiffFrame,MonsterTurnAcceleration));
	  if(MonsterTheta > 0)
	  {
		  MonsterTheta = 0;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
   }
   else if( MonsterTheta>0 )
   {
      MonsterTurning=-1;
	  MonsterTheta -= (RLMultiply(DiffFrame,MonsterTurnAcceleration));
	  if(MonsterTheta < 0 )
	  {
		  MonsterTheta = 0;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
   }
   else
   {
      MonsterTurning=0;
   }

   

//   RLFrameSetRotation(mover,scene,RLVal(0),RLVal(1),RLVal(0),RLVal(0));
   
   result=SpuddeMoveOnGround(mover,&MonsterVelocity,&MonsterGradientFactor);

   if(result&2)
   {
      MonsterHitObstacle=1;
      MonsterSpeed=0;
   }
   if(result&1)
   {
      MonsterMidair=1;
   }
   MonsterData.DamageICause = 0;
}

static void RoggoshHomerFunction(MovingObjectData mover)
{
   RLVector   dir,newdir;
   int result;
   RLVector up;
   RLVector Position1;
   RLValue Sine;
   RLValue Distance;
   RLValue DIFFRAME;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   DIFFRAME=DiffFrame;

   RLFrameGetPosition(Robotframe,scene,&Position1);
   Position1.x-=mover->CurrentPosition.x;
   Position1.y-=mover->CurrentPosition.y;
   Position1.z-=mover->CurrentPosition.z;

   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);
   Sine=RLMultiply(dir.x,Position1.z) - RLMultiply(Position1.x,dir.z);
   if(Sine<-HomingGoodEnough)
   {
      MonsterTurning=1;
	  if(MonsterTheta>=0)
	  {
		  MonsterTheta = -MonsterTurnAcceleration;
	  }
	  else
	  {
		  MonsterTheta -= (RLMultiply(DiffFrame,MonsterTurnAcceleration));
	  }
	  if(MonsterTheta < -MonsterTurnMaximum)
	  {
		  MonsterTheta = -MonsterTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
   }
   else if(Sine>HomingGoodEnough)
   {
      MonsterTurning=-1;
	  if(MonsterTheta<=0)
	  {
		  MonsterTheta = MonsterTurnAcceleration;
	  }
	  else
	  {
		  MonsterTheta += (RLMultiply(DiffFrame,MonsterTurnAcceleration));
	  }
	  if(MonsterTheta > MonsterTurnMaximum)
	  {
		  MonsterTheta = MonsterTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
   }
   else
   {
      MonsterTurning=0;
   }
   MonsterSpeed+=RLMultiply(MonsterMotions[MonsterMovementState].AccelerationValue,DIFFRAME);
   if(MonsterSpeed>MonsterMotions[MonsterMovementState].TopSpeed) MonsterSpeed=MonsterMotions[MonsterMovementState].TopSpeed;
   if(MonsterSpeed<0) MonsterSpeed=0;
   Distance=RLMultiply(MonsterSpeed,DIFFRAME);
   MonsterVelocity.x=RLMultiply(-dir.x,Distance);
   MonsterVelocity.z=RLMultiply(-dir.z,Distance);
   MonsterDistance+=Distance;
   MonsterVelocity.y=RLVal(0);

   result=SpuddeMoveOnGround(mover,&MonsterVelocity,&MonsterGradientFactor);
   if(result&2)
   {
      MonsterHitObstacle=1;
      MonsterSpeed=0;
   }
   if(result&1)
   {
      MonsterMidair=1;
   }
   MonsterData.DamageICause = MonsterMotionDamage*MonsterSpeed/MonsterMaxFVel4;
}

static void NeallothDiveBombFunction(MovingObjectData mover)
{
   RLVector   dir,newdir;
   int result;
   RLVector up;
   RLVector Position1;
   RLValue Sine;
   RLValue Distance;
   RLValue DIFFRAME;
//   FILE *shithead;
   RLFrame scene = RLFrameGetScene(mover->PositioningFrame);
   RLFrameGetPosition(mover->PositioningFrame,scene,&mover->CurrentPosition);
   DIFFRAME=DiffFrame;

   RLFrameGetPosition(Robotframe,scene,&Position1);
   Position1.x-=mover->CurrentPosition.x;
   Position1.y-=mover->CurrentPosition.y;
   Position1.z-=mover->CurrentPosition.z;

   RLFrameGetOrientation(mover->PositioningFrame,scene,&dir,&up);
   Sine=RLMultiply(dir.x,Position1.z) - RLMultiply(Position1.x,dir.z);
   if(Sine<-HomingGoodEnough)
   {
      MonsterTurning=1;
	  if(MonsterTheta>=0)
	  {
		  MonsterTheta = -MonsterTurnAcceleration;
	  }
	  else
	  {
		  MonsterTheta -= (RLMultiply(DiffFrame,MonsterTurnAcceleration));
	  }
	  if(MonsterTheta < -MonsterTurnMaximum)
	  {
		  MonsterTheta = -MonsterTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
   }
   else if(Sine>HomingGoodEnough)
   {
      MonsterTurning=-1;
	  if(MonsterTheta<=0)
	  {
		  MonsterTheta = MonsterTurnAcceleration;
	  }
	  else
	  {
		  MonsterTheta += (RLMultiply(DiffFrame,MonsterTurnAcceleration));
	  }
	  if(MonsterTheta > MonsterTurnMaximum)
	  {
		  MonsterTheta = MonsterTurnMaximum;
	  }
      newdir.x=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.x) + RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.z);
      newdir.z=RLMultiply(cos(RLMultiply(MonsterTheta,DiffFrame)),dir.z) - RLMultiply(sin(RLMultiply(MonsterTheta,DiffFrame)),dir.x);
      RLFrameSetOrientation(mover->PositioningFrame,scene,newdir.x,dir.y,newdir.z,up.x,up.y,up.z);
   }
   else
   {
      MonsterTurning=0;
   }
   MonsterSpeed+=RLMultiply(MonsterMotions[MonsterMovementState].AccelerationValue,DIFFRAME);
   MonsterYSpeed+=RLMultiply(MonsterMotions[MonsterMovementState].YAccelerationValue,DIFFRAME);
   if(MonsterSpeed>MonsterMotions[MonsterMovementState].TopSpeed) MonsterSpeed=MonsterMotions[MonsterMovementState].TopSpeed;
   if(MonsterYSpeed>MonsterMotions[MonsterMovementState].TopYSpeed) MonsterYSpeed=MonsterMotions[MonsterMovementState].TopYSpeed;
   if(MonsterSpeed<0) MonsterSpeed=0;
   Distance=RLMultiply(MonsterSpeed,DIFFRAME);
   MonsterVelocity.x=RLMultiply(-dir.x,Distance);
   MonsterVelocity.z=RLMultiply(-dir.z,Distance);
   MonsterDistance+=Distance;
   MonsterVelocity.y=RLMultiply(MonsterYSpeed,DIFFRAME);
//   MonsterVelocity.y+=RLMultiply(DIFFRAME,MonsterYSpeed);
//   shithead=fopen("shit.out","a");
//   fprintf(shithead,"speed = %.3f, yspeed = %.3f\n",MonsterSpeed,MonsterYSpeed);
//   fprintf(shithead,"position = (%.2f, %.2f, %.2f)\n",mover->CurrentPosition.x,mover->CurrentPosition.y,mover->CurrentPosition.z);
//   fprintf(shithead,"velocity = (%.2f, %.2f, %.2f)\n\n",MonsterVelocity.x, MonsterVelocity.y, MonsterVelocity.z);
//   fclose(shithead);

   result=SpuddeMoveInAir(mover,&MonsterVelocity);
//   shithead=fopen("shit.out","a");
//   fprintf(shithead,"speed = %.3f, yspeed = %.3f\n",MonsterSpeed,MonsterYSpeed);
//   fprintf(shithead,"position = (%.2f, %.2f, %.2f)\n",mover->CurrentPosition.x,mover->CurrentPosition.y,mover->CurrentPosition.z);
//   fprintf(shithead,"velocity = (%.2f, %.2f, %.2f)\n\n",MonsterVelocity.x, MonsterVelocity.y, MonsterVelocity.z);
//   fclose(shithead);
   if(result&2)
   {
      MonsterHitObstacle=1;
      MonsterSpeed=0;
   }
   if(result&1)
   {
      MonsterMidair=1;
   }
   MonsterData.DamageICause = MonsterMotionDamage*MonsterSpeed/MonsterMaxFVel4;
}




void knead(MovingObjectData mover)
{
   int i;
//   FILE *shithead;
   MnstEngy-=MonsterMotions[MonsterMovementState].EnergyDrain;
   if(MnstEngy<0)MnstEngy=0;
   (MonsterMotions[MonsterMovementState].WhatToDo)(mover);
//   shithead=fopen("shit.out","a");
//   fprintf(shithead,"Monster movement %d\nposition (%.3f, %.3f, %.3f)\nvelocity (%.3f,%.3f,%.3f)\n",MonsterMovementState,
//mover->CurrentPosition.x,mover->CurrentPosition.y,mover->CurrentPosition.z,
//           MonsterVelocity.x,MonsterVelocity.y,MonsterVelocity.z);
//   fclose(shithead);

   MonsterNumMovementFrames++;
   for(i=0;(i<MonsterMotions[MonsterMovementState].numchanges) ;i++ )
      if(  (MonsterMotions[MonsterMovementState].ChangeList[i]) () )
         i=MonsterMotions[MonsterMovementState].numchanges;
}
#ifdef PC
void GetMonsterMovementInfo(FILE *input)
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
   fprintf(errors,"Getting monster movement info.\n");
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
            if(!stricmp("MonsterJumpYAcc",movename))
            {
               fscanf(input," %f",&MonsterJumpYAcc);
            }
            else if(!stricmp("MaxYVel",movename))
            {
               fscanf(input," %f",&MaxYVel);
            }
            else if(!stricmp("MonsterGravity",movename))
            {
               fscanf(input," %f",&MonsterGravity);
            }
//            else if(!stricmp("MonsterTurnRate",movename))
  //          {
    //           fscanf(input," %f",&MonsterTurnRate);
      //      }
            else if(!stricmp("MonsterTurnAcceleration",movename))
            {
               fscanf(input," %f",&MonsterTurnAcceleration);
            }
            else if(!stricmp("MonsterTurnMaximum",movename))
            {
               fscanf(input," %f",&MonsterTurnMaximum);
            }
//            else if(!stricmp("MonsterCosine",movename))
  //          {
    //           fscanf(input," %*f");
      //      }
        //    else if(!stricmp("MonsterSine",movename))
          //  {
            //   fscanf(input," %*f");
            //}
            else if(!stricmp("MonsterGradientFactor",movename))
            {
               fscanf(input," %f",&MonsterGradientFactor);
            }
            else if(!stricmp("MonsterMaxFVel1",movename))
            {
               fscanf(input," %f",&MonsterMaxFVel1);
            }
            else if(!stricmp("MonsterMaxFVel2",movename))
            {
               fscanf(input," %f",&MonsterMaxFVel2);
            }
            else if(!stricmp("MonsterMaxFVel3",movename))
            {
               fscanf(input," %f",&MonsterMaxFVel3);
            }
            else if(!stricmp("MonsterMaxFVel4",movename))
            {
               fscanf(input," %f",&MonsterMaxFVel4);
            }
            else if(!stricmp("RoggoshHomerTopSpeed",movename))
            {
               fscanf(input," %f",&RoggoshHomerTopSpeed);
            }
            else if(!stricmp("NeallothDiveBombTopSpeed",movename))
            {
               fscanf(input," %f",&NeallothDiveBombTopSpeed);
            }
            else if(!stricmp("NeallothDiveBombTopYSpeed",movename))
            {
               fscanf(input," %f",&NeallothDiveBombTopYSpeed);
            }
            else if(!stricmp("MonsterFAcc1",movename))
            {
               fscanf(input," %f",&MonsterFAcc1);
            }
            else if(!stricmp("MonsterFAcc2",movename))
            {
               fscanf(input," %f",&MonsterFAcc2);
            }
            else if(!stricmp("MonsterFAcc3",movename))
            {
               fscanf(input," %f",&MonsterFAcc3);
            }
            else if(!stricmp("MonsterFAcc4",movename))
            {
               fscanf(input," %f",&MonsterFAcc4);
            }
            else if(!stricmp("RoggoshHomerAccelerationValue",movename))
            {
               fscanf(input," %f",&RoggoshHomerAccelerationValue);
            }
            else if(!stricmp("NeallothDiveBombAccelerationValue",movename))
            {
               fscanf(input," %f",&NeallothDiveBombAccelerationValue);
            }
            else if(!stricmp("NeallothDiveBombYAccelerationValue",movename))
            {
               fscanf(input," %f",&NeallothDiveBombYAccelerationValue);
            }
            else if(!stricmp("MonsterFDecel",movename))
            {
               fscanf(input," %f",&MonsterFDecel);
            }
            else if(!stricmp("MonsterFBrake",movename))
            {
               fscanf(input," %f",&MonsterFBrake);
            }
            else if(!stricmp("MonsterMaxBVel1",movename))
            {
               fscanf(input," %f",&MonsterMaxBVel1);
            }
            else if(!stricmp("MonsterMaxBVel2",movename))
            {
               fscanf(input," %f",&MonsterMaxBVel2);
            }
            else if(!stricmp("MonsterBAcc1",movename))
            {
               fscanf(input," %f",&MonsterBAcc1);
            }
            else if(!stricmp("MonsterBAcc2",movename))
            {
               fscanf(input," %f",&MonsterBAcc2);
            }
            else if(!stricmp("MonsterBDecel",movename))
            {
               fscanf(input," %f",&MonsterBDecel);
            }
            else if(!stricmp("MonsterBBrake",movename))
            {
               fscanf(input," %f",&MonsterBBrake);
            }
            else if(!stricmp("MonsterMaxRVel1",movename))
            {
               fscanf(input," %f",&MonsterMaxRVel1);
            }
            else if(!stricmp("MonsterRAcc1",movename))
            {
               fscanf(input," %f",&MonsterRAcc1);
            }
            else if(!stricmp("MonsterRDecel",movename))
            {
               fscanf(input," %f",&MonsterRDecel);
            }
            else if(!stricmp("MonsterRBrake",movename))
            {
               fscanf(input," %f",&MonsterRBrake);
            }
            else if(!stricmp("MonsterMaxLVel1",movename))
            {
               fscanf(input," %f",&MonsterMaxLVel1);
            }
            else if(!stricmp("MonsterLAcc1",movename))
            {
               fscanf(input," %f",&MonsterLAcc1);
            }
            else if(!stricmp("MonsterLDecel",movename))
            {
               fscanf(input," %f",&MonsterLDecel);
            }
            else if(!stricmp("MonsterLBrake",movename))
            {
               fscanf(input," %f",&MonsterLBrake);
            }
            else if(!stricmp("MonsterWaitingEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterWaitingEnergyDrain);
            }
            else if(!stricmp("MonsterFAccelerating1EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterFAccelerating1EnergyDrain);
            }
            else if(!stricmp("MonsterFAccelerating2EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterFAccelerating2EnergyDrain);
            }
            else if(!stricmp("MonsterFAccelerating3EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterFAccelerating3EnergyDrain);
            }
            else if(!stricmp("MonsterFAccelerating4EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterFAccelerating4EnergyDrain);
            }
            else if(!stricmp("MonsterFTopSpeed1EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterFTopSpeed1EnergyDrain);
            }
            else if(!stricmp("MonsterFTopSpeed2EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterFTopSpeed2EnergyDrain);
            }
            else if(!stricmp("MonsterFTopSpeed3EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterFTopSpeed3EnergyDrain);
            }
            else if(!stricmp("MonsterFTopSpeed4EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterFTopSpeed4EnergyDrain);
            }
            else if(!stricmp("MonsterFDeceleratingEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterFDeceleratingEnergyDrain);
            }
            else if(!stricmp("MonsterFBrakingEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterFBrakingEnergyDrain);
            }
            else if(!stricmp("MonsterBAccelerating1EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterBAccelerating1EnergyDrain);
            }
            else if(!stricmp("MonsterBAccelerating2EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterBAccelerating2EnergyDrain);
            }
            else if(!stricmp("MonsterBTopSpeed1EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterBTopSpeed1EnergyDrain);
            }
            else if(!stricmp("MonsterBTopSpeed2EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterBTopSpeed2EnergyDrain);
            }
            else if(!stricmp("MonsterBDeceleratingEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterBDeceleratingEnergyDrain);
            }
            else if(!stricmp("MonsterBBrakingEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterBBrakingEnergyDrain);
            }
            else if(!stricmp("MonsterLAccelerating1EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterLAccelerating1EnergyDrain);
            }
            else if(!stricmp("MonsterLTopSpeed1EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterLTopSpeed1EnergyDrain);
            }
            else if(!stricmp("MonsterLDeceleratingEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterLDeceleratingEnergyDrain);
            }
            else if(!stricmp("MonsterLBrakingEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterLBrakingEnergyDrain);
            }
            else if(!stricmp("MonsterRAccelerating1EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterRAccelerating1EnergyDrain);
            }
            else if(!stricmp("MonsterRTopSpeed1EnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterRTopSpeed1EnergyDrain);
            }
            else if(!stricmp("MonsterRDeceleratingEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterRDeceleratingEnergyDrain);
            }
            else if(!stricmp("MonsterRBrakingEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterRBrakingEnergyDrain);
            }
            else if(!stricmp("MonsterJumpingEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterJumpingEnergyDrain);
            }
            else if(!stricmp("MonsterAirborneEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterAirborneEnergyDrain);
            }
            else if(!stricmp("MonsterStoppedEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterStoppedEnergyDrain);
            }
            else if(!stricmp("MonsterKnockBackwardEnergyDrain",movename))
            {
               fscanf(input," %d",&MonsterKnockBackwardEnergyDrain);
            }
            else if(!stricmp("RoggoshHomerEnergyDrain",movename))
            {
               fscanf(input," %d",&RoggoshHomerEnergyDrain);
            }
            else if(!stricmp("NeallothDiveBombEnergyDrain",movename))
            {
               fscanf(input," %d",&NeallothDiveBombEnergyDrain);
            }
            else if(!stricmp("MonsterWaitingMinEnergy",movename))
            {
               fscanf(input," %d",&MonsterWaitingMinEnergy);
            }
            else if(!stricmp("MonsterFAccelerating1MinEnergy",movename))
            {
               fscanf(input," %d",&MonsterFAccelerating1MinEnergy);
            }
            else if(!stricmp("MonsterFAccelerating2MinEnergy",movename))
            {
               fscanf(input," %d",&MonsterFAccelerating2MinEnergy);
            }
            else if(!stricmp("MonsterFAccelerating3MinEnergy",movename))
            {
               fscanf(input," %d",&MonsterFAccelerating3MinEnergy);
            }
            else if(!stricmp("MonsterFAccelerating4MinEnergy",movename))
            {
               fscanf(input," %d",&MonsterFAccelerating4MinEnergy);
            }
            else if(!stricmp("MonsterFTopSpeed1MinEnergy",movename))
            {
               fscanf(input," %d",&MonsterFTopSpeed1MinEnergy);
            }
            else if(!stricmp("MonsterFTopSpeed2MinEnergy",movename))
            {
               fscanf(input," %d",&MonsterFTopSpeed2MinEnergy);
            }
            else if(!stricmp("MonsterFTopSpeed3MinEnergy",movename))
            {
               fscanf(input," %d",&MonsterFTopSpeed3MinEnergy);
            }
            else if(!stricmp("MonsterFTopSpeed4MinEnergy",movename))
            {
               fscanf(input," %d",&MonsterFTopSpeed4MinEnergy);
            }
            else if(!stricmp("MonsterFDeceleratingMinEnergy",movename))
            {
               fscanf(input," %d",&MonsterFDeceleratingMinEnergy);
            }
            else if(!stricmp("MonsterFBrakingMinEnergy",movename))
            {
               fscanf(input," %d",&MonsterFBrakingMinEnergy);
            }
            else if(!stricmp("MonsterBAccelerating1MinEnergy",movename))
            {
               fscanf(input," %d",&MonsterBAccelerating1MinEnergy);
            }
            else if(!stricmp("MonsterBAccelerating2MinEnergy",movename))
            {
               fscanf(input," %d",&MonsterBAccelerating2MinEnergy);
            }
            else if(!stricmp("MonsterBAccelerating2MinEnergy",movename))
            {
               fscanf(input," %d",&MonsterBAccelerating2MinEnergy);
            }
            else if(!stricmp("MonsterBTopSpeed1MinEnergy",movename))
            {
               fscanf(input," %d",&MonsterBTopSpeed1MinEnergy);
            }
            else if(!stricmp("MonsterBTopSpeed2MinEnergy",movename))
            {
               fscanf(input," %d",&MonsterBTopSpeed2MinEnergy);
            }
            else if(!stricmp("MonsterBDeceleratingMinEnergy",movename))
            {
               fscanf(input," %d",&MonsterBDeceleratingMinEnergy);
            }
            else if(!stricmp("MonsterBBrakingMinEnergy",movename))
            {
               fscanf(input," %d",&MonsterBBrakingMinEnergy);
            }
            else if(!stricmp("MonsterLAccelerating1MinEnergy",movename))
            {
               fscanf(input," %d",&MonsterLAccelerating1MinEnergy);
            }
            else if(!stricmp("MonsterLTopSpeed1MinEnergy",movename))
            {
               fscanf(input," %d",&MonsterLTopSpeed1MinEnergy);
            }
            else if(!stricmp("MonsterLDeceleratingMinEnergy",movename))
            {
               fscanf(input," %d",&MonsterLDeceleratingMinEnergy);
            }
            else if(!stricmp("MonsterLBrakingMinEnergy",movename))
            {
               fscanf(input," %d",&MonsterLBrakingMinEnergy);
            }
            else if(!stricmp("MonsterRAccelerating1MinEnergy",movename))
            {
               fscanf(input," %d",&MonsterRAccelerating1MinEnergy);
            }
            else if(!stricmp("MonsterRTopSpeed1MinEnergy",movename))
            {
               fscanf(input," %d",&MonsterRTopSpeed1MinEnergy);
            }
            else if(!stricmp("MonsterRDeceleratingMinEnergy",movename))
            {
               fscanf(input," %d",&MonsterRDeceleratingMinEnergy);
            }
            else if(!stricmp("MonsterRBrakingMinEnergy",movename))
            {
               fscanf(input," %d",&MonsterRBrakingMinEnergy);
            }
            else if(!stricmp("MonsterJumpingMinEnergy",movename))
            {
               fscanf(input," %d",&MonsterJumpingMinEnergy);
            }
            else if(!stricmp("MonsterAirborneMinEnergy",movename))
            {
               fscanf(input," %d",&MonsterAirborneMinEnergy);
            }
            else if(!stricmp("MonsterStoppedMinEnergy",movename))
            {
               fscanf(input," %d",&MonsterStoppedMinEnergy);
            }
            else if(!stricmp("MonsterKnockBackwardMinEnergy",movename))
            {
               fscanf(input," %d",&MonsterKnockBackwardMinEnergy);
            }
            else if(!stricmp("MonsterGoopiness",movename))
            {
               fscanf(input," %f",&MonsterGoopiness);
            }
            else if(!stricmp("MonsterKnockBackwardSpeed",movename))
            {
               fscanf(input," %f",&MonsterKnockBackwardSpeed);
            }
            else if(!stricmp("HomingGoodEnough",movename))
            {
               fscanf(input," %f",&HomingGoodEnough);
            }
            else if(!stricmp("MonsterMotionDamage",movename))
            {
               fscanf(input," %d",&MonsterMotionDamage);
            }
            else if(!stricmp("MonsterMass",movename))
            {
               extern struct _moving_object_data_ MonsterData;
               fscanf(input," %f",&(MonsterData.mass));
            }
            else if(!stricmp("MonsterSpinMultiplier",movename))
            {
               fscanf(input," %f",&MonsterSpinMultiplier);
            }
            else if(!stricmp("MonsterSlidingFriction",movename))
            {
               fscanf(input," %f",&MonsterSlidingFriction);
            }
            else if(!stricmp("Turbo",movename))
            {
               fscanf(input," %f",&Turbo);
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

void DefineMonsterMotionConstants()
{
//   int i;
#ifdef PC   
   FILE * input;
   input=fopen("Monsterdef.dat","rt");
   if(input) GetMonsterMovementInfo(input);
   if(input) fclose(input);
#endif
//   for(i=1;i<11;i++)
//   {
//      MonsterSineTable[i-1]=sin(i*MonsterTheta);
//      MonsterCosineTable[i-1]=cos(i*MonsterTheta);
//   }
   MonsterMotions[MonsterWaiting].AccelerationValue=0;
   MonsterMotions[MonsterWaiting].YAccelerationValue=0;
   MonsterMotions[MonsterWaiting].TopSpeed=0;
   MonsterMotions[MonsterWaiting].TopYSpeed=0;
   MonsterMotions[MonsterWaiting].EnergyDrain=MonsterWaitingEnergyDrain;

   MonsterMotions[MonsterFAccelerating1].AccelerationValue=MonsterFAcc1;
   MonsterMotions[MonsterFAccelerating1].YAccelerationValue=0;
   MonsterMotions[MonsterFAccelerating1].TopSpeed=MonsterMaxFVel1;
   MonsterMotions[MonsterFAccelerating1].TopYSpeed=0;
   MonsterMotions[MonsterFAccelerating1].EnergyDrain=MonsterFAccelerating1EnergyDrain;

   MonsterMotions[MonsterFAccelerating2].AccelerationValue=MonsterFAcc2;
   MonsterMotions[MonsterFAccelerating2].YAccelerationValue=0;
   MonsterMotions[MonsterFAccelerating2].TopSpeed=MonsterMaxFVel2;
   MonsterMotions[MonsterFAccelerating2].TopYSpeed=0;
   MonsterMotions[MonsterFAccelerating2].EnergyDrain=MonsterFAccelerating2EnergyDrain;

   MonsterMotions[MonsterFAccelerating3].AccelerationValue=MonsterFAcc3;
   MonsterMotions[MonsterFAccelerating3].YAccelerationValue=0;
   MonsterMotions[MonsterFAccelerating3].TopSpeed=MonsterMaxFVel3;
   MonsterMotions[MonsterFAccelerating3].TopYSpeed=0;
   MonsterMotions[MonsterFAccelerating3].EnergyDrain=MonsterFAccelerating3EnergyDrain;

   MonsterMotions[MonsterFAccelerating4].AccelerationValue=MonsterFAcc4;
   MonsterMotions[MonsterFAccelerating4].YAccelerationValue=0;
   MonsterMotions[MonsterFAccelerating4].TopSpeed=MonsterMaxFVel4;
   MonsterMotions[MonsterFAccelerating4].TopYSpeed=0;
   MonsterMotions[MonsterFAccelerating4].EnergyDrain=MonsterFAccelerating4EnergyDrain;

   MonsterMotions[MonsterFTopSpeed1].AccelerationValue=0;
   MonsterMotions[MonsterFTopSpeed1].YAccelerationValue=0;
   MonsterMotions[MonsterFTopSpeed1].TopSpeed=MonsterMaxFVel1;
   MonsterMotions[MonsterFTopSpeed1].TopYSpeed=0;
   MonsterMotions[MonsterFTopSpeed1].EnergyDrain=MonsterFTopSpeed1EnergyDrain;

   MonsterMotions[MonsterFTopSpeed2].AccelerationValue=0;
   MonsterMotions[MonsterFTopSpeed2].YAccelerationValue=0;
   MonsterMotions[MonsterFTopSpeed2].TopSpeed=MonsterMaxFVel2;
   MonsterMotions[MonsterFTopSpeed2].TopYSpeed=0;
   MonsterMotions[MonsterFTopSpeed2].EnergyDrain=MonsterFTopSpeed2EnergyDrain;

   MonsterMotions[MonsterFTopSpeed3].AccelerationValue=0;
   MonsterMotions[MonsterFTopSpeed3].YAccelerationValue=0;
   MonsterMotions[MonsterFTopSpeed3].TopSpeed=MonsterMaxFVel3;
   MonsterMotions[MonsterFTopSpeed3].TopYSpeed=0;
   MonsterMotions[MonsterFTopSpeed3].EnergyDrain=MonsterFTopSpeed3EnergyDrain;

   MonsterMotions[MonsterFTopSpeed4].AccelerationValue=0;
   MonsterMotions[MonsterFTopSpeed4].YAccelerationValue=0;
   MonsterMotions[MonsterFTopSpeed4].TopSpeed=MonsterMaxFVel4;
   MonsterMotions[MonsterFTopSpeed4].TopYSpeed=0;
   MonsterMotions[MonsterFTopSpeed4].EnergyDrain=MonsterFTopSpeed4EnergyDrain;

   MonsterMotions[MonsterFDecelerating].AccelerationValue=MonsterFDecel;
   MonsterMotions[MonsterFDecelerating].YAccelerationValue=0;
   MonsterMotions[MonsterFDecelerating].TopSpeed=MonsterMaxFVel3;
   MonsterMotions[MonsterFDecelerating].TopYSpeed=0;
   MonsterMotions[MonsterFDecelerating].EnergyDrain=MonsterFDeceleratingEnergyDrain;

   MonsterMotions[MonsterFBraking].AccelerationValue=MonsterFBrake;
   MonsterMotions[MonsterFBraking].YAccelerationValue=0;
   MonsterMotions[MonsterFBraking].TopSpeed=MonsterMaxFVel4;
   MonsterMotions[MonsterFBraking].TopYSpeed=0;
   MonsterMotions[MonsterFBraking].EnergyDrain=MonsterFBrakingEnergyDrain;

   MonsterMotions[MonsterBAccelerating1].AccelerationValue=MonsterBAcc1;
   MonsterMotions[MonsterBAccelerating1].YAccelerationValue=0;
   MonsterMotions[MonsterBAccelerating1].TopSpeed=MonsterMaxBVel1;
   MonsterMotions[MonsterBAccelerating1].TopYSpeed=0;
   MonsterMotions[MonsterBAccelerating1].EnergyDrain=MonsterBAccelerating1EnergyDrain;

   MonsterMotions[MonsterBAccelerating2].AccelerationValue=MonsterBAcc2;
   MonsterMotions[MonsterBAccelerating2].YAccelerationValue=0;
   MonsterMotions[MonsterBAccelerating2].TopSpeed=MonsterMaxBVel2;
   MonsterMotions[MonsterBAccelerating2].TopYSpeed=0;
   MonsterMotions[MonsterBAccelerating2].EnergyDrain=MonsterBAccelerating2EnergyDrain;

   MonsterMotions[MonsterBTopSpeed1].AccelerationValue=0;
   MonsterMotions[MonsterBTopSpeed1].YAccelerationValue=0;
   MonsterMotions[MonsterBTopSpeed1].TopSpeed=MonsterMaxBVel1;
   MonsterMotions[MonsterBTopSpeed1].TopYSpeed=0;
   MonsterMotions[MonsterBTopSpeed1].EnergyDrain=MonsterBTopSpeed1EnergyDrain;

   MonsterMotions[MonsterBTopSpeed2].AccelerationValue=0;
   MonsterMotions[MonsterBTopSpeed2].YAccelerationValue=0;
   MonsterMotions[MonsterBTopSpeed2].TopSpeed=MonsterMaxBVel2;
   MonsterMotions[MonsterBTopSpeed2].TopYSpeed=0;
   MonsterMotions[MonsterBTopSpeed2].EnergyDrain=MonsterBTopSpeed2EnergyDrain;

   MonsterMotions[MonsterBDecelerating].AccelerationValue=MonsterBDecel;
   MonsterMotions[MonsterBDecelerating].YAccelerationValue=0;
   MonsterMotions[MonsterBDecelerating].TopSpeed=MonsterMaxBVel2;
   MonsterMotions[MonsterBDecelerating].TopYSpeed=0;
   MonsterMotions[MonsterBDecelerating].EnergyDrain=MonsterBDeceleratingEnergyDrain;

   MonsterMotions[MonsterBBraking].AccelerationValue=MonsterBBrake;
   MonsterMotions[MonsterBBraking].YAccelerationValue=0;
   MonsterMotions[MonsterBBraking].TopSpeed=MonsterMaxBVel2;
   MonsterMotions[MonsterBBraking].TopYSpeed=0;
   MonsterMotions[MonsterBBraking].EnergyDrain=MonsterBBrakingEnergyDrain;

   MonsterMotions[MonsterLAccelerating1].AccelerationValue=MonsterLAcc1;
   MonsterMotions[MonsterLAccelerating1].YAccelerationValue=0;
   MonsterMotions[MonsterLAccelerating1].TopSpeed=MonsterMaxLVel1;
   MonsterMotions[MonsterLAccelerating1].TopYSpeed=0;
   MonsterMotions[MonsterLAccelerating1].EnergyDrain=MonsterLAccelerating1EnergyDrain;

   MonsterMotions[MonsterLTopSpeed1].AccelerationValue=0;
   MonsterMotions[MonsterLTopSpeed1].YAccelerationValue=0;
   MonsterMotions[MonsterLTopSpeed1].TopSpeed=MonsterMaxLVel1;
   MonsterMotions[MonsterLTopSpeed1].TopYSpeed=0;
   MonsterMotions[MonsterLTopSpeed1].EnergyDrain=MonsterLTopSpeed1EnergyDrain;

   MonsterMotions[MonsterLDecelerating].AccelerationValue=MonsterLDecel;
   MonsterMotions[MonsterLDecelerating].YAccelerationValue=0;
   MonsterMotions[MonsterLDecelerating].TopSpeed=MonsterMaxLVel1;
   MonsterMotions[MonsterLDecelerating].TopYSpeed=0;
   MonsterMotions[MonsterLDecelerating].EnergyDrain=MonsterLDeceleratingEnergyDrain;

   MonsterMotions[MonsterLBraking].AccelerationValue=MonsterLBrake;
   MonsterMotions[MonsterLBraking].YAccelerationValue=0;
   MonsterMotions[MonsterLBraking].TopSpeed=MonsterMaxLVel1;
   MonsterMotions[MonsterLBraking].TopYSpeed=0;
   MonsterMotions[MonsterLBraking].EnergyDrain=MonsterLBrakingEnergyDrain;

   MonsterMotions[MonsterRAccelerating1].AccelerationValue=MonsterRAcc1;
   MonsterMotions[MonsterRAccelerating1].YAccelerationValue=0;
   MonsterMotions[MonsterRAccelerating1].TopSpeed=MonsterMaxRVel1;
   MonsterMotions[MonsterRAccelerating1].TopYSpeed=0;
   MonsterMotions[MonsterRAccelerating1].EnergyDrain=MonsterRAccelerating1EnergyDrain;

   MonsterMotions[MonsterRTopSpeed1].AccelerationValue=0;
   MonsterMotions[MonsterRTopSpeed1].YAccelerationValue=0;
   MonsterMotions[MonsterRTopSpeed1].TopSpeed=MonsterMaxRVel1;
   MonsterMotions[MonsterRTopSpeed1].TopYSpeed=0;
   MonsterMotions[MonsterRTopSpeed1].EnergyDrain=MonsterRTopSpeed1EnergyDrain;

   MonsterMotions[MonsterRDecelerating].AccelerationValue=MonsterRDecel;
   MonsterMotions[MonsterRDecelerating].YAccelerationValue=0;
   MonsterMotions[MonsterRDecelerating].TopSpeed=MonsterMaxRVel1;
   MonsterMotions[MonsterRDecelerating].TopYSpeed=0;
   MonsterMotions[MonsterRDecelerating].EnergyDrain=MonsterRDeceleratingEnergyDrain;

   MonsterMotions[MonsterRBraking].AccelerationValue=MonsterRBrake;
   MonsterMotions[MonsterRBraking].YAccelerationValue=0;
   MonsterMotions[MonsterRBraking].TopSpeed=MonsterMaxRVel1;
   MonsterMotions[MonsterRBraking].TopYSpeed=0;
   MonsterMotions[MonsterRBraking].EnergyDrain=MonsterRBrakingEnergyDrain;

   MonsterMotions[MonsterJumping].AccelerationValue=0;
   MonsterMotions[MonsterJumping].YAccelerationValue=MonsterJumpYAcc;
   MonsterMotions[MonsterJumping].TopSpeed=MonsterMaxFVel4;
   MonsterMotions[MonsterJumping].TopYSpeed= MaxYVel;
   MonsterMotions[MonsterJumping].EnergyDrain=MonsterJumpingEnergyDrain;

   MonsterMotions[MonsterAirborne].AccelerationValue=0;
   MonsterMotions[MonsterAirborne].YAccelerationValue=MonsterGravity;
   MonsterMotions[MonsterAirborne].TopSpeed=MonsterMaxFVel4;
   MonsterMotions[MonsterAirborne].TopYSpeed=MaxYVel;
   MonsterMotions[MonsterAirborne].EnergyDrain=MonsterAirborneEnergyDrain;

   MonsterMotions[MonsterStopped].AccelerationValue=0;
   MonsterMotions[MonsterStopped].YAccelerationValue=0;
   MonsterMotions[MonsterStopped].TopSpeed=0;
   MonsterMotions[MonsterStopped].TopYSpeed=0;
   MonsterMotions[MonsterStopped].EnergyDrain=MonsterStoppedEnergyDrain;

   MonsterMotions[RoggoshHomer].AccelerationValue=RoggoshHomerAccelerationValue;
   MonsterMotions[RoggoshHomer].YAccelerationValue=0;
   MonsterMotions[RoggoshHomer].TopSpeed=RoggoshHomerTopSpeed;
   MonsterMotions[RoggoshHomer].TopYSpeed=0;
   MonsterMotions[RoggoshHomer].EnergyDrain=RoggoshHomerEnergyDrain;

   MonsterMotions[NeallothDiveBomb].AccelerationValue=NeallothDiveBombAccelerationValue;
   MonsterMotions[NeallothDiveBomb].YAccelerationValue=NeallothDiveBombYAccelerationValue;
   MonsterMotions[NeallothDiveBomb].TopSpeed=NeallothDiveBombTopSpeed;
   MonsterMotions[NeallothDiveBomb].TopYSpeed=NeallothDiveBombTopYSpeed;
   MonsterMotions[NeallothDiveBomb].EnergyDrain=NeallothDiveBombEnergyDrain;

}
//This function will load up MonsterMotions with the proper states.
int InitMonsterMotionEngine()
{
    size_t size1,size2;
   size1=RLGetTotalAllocated();

   if(RLMalloc( (void **)&(MonsterMotions[MonsterWaiting].ChangeList) , 6*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterWaiting].numchanges=4;
   MonsterMotions[MonsterWaiting].WhatToDo=MonsterWaitingFunction;
   MonsterMotions[MonsterWaiting].ChangeList[0]=ToMonsterStopped;
   MonsterMotions[MonsterWaiting].ChangeList[1]=ToMonsterJumping;
   MonsterMotions[MonsterWaiting].ChangeList[2]=ToMonsterFAccelerating1;
   MonsterMotions[MonsterWaiting].ChangeList[3]=ToMonsterBAccelerating1;
//   MonsterMotions[MonsterWaiting].ChangeList[4]=ToMonsterLAccelerating1;
//   MonsterMotions[MonsterWaiting].ChangeList[5]=ToMonsterRAccelerating1;


   if(RLMalloc((void **)&(MonsterMotions[MonsterFAccelerating1].ChangeList  ),7*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterFAccelerating1].numchanges=7;
   MonsterMotions[MonsterFAccelerating1].WhatToDo=MonsterFAccelerating1Function;
   MonsterMotions[MonsterFAccelerating1].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterFAccelerating1].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterFAccelerating1].ChangeList[2]=ToMonsterWaiting;
   MonsterMotions[MonsterFAccelerating1].ChangeList[3]=ToMonsterJumping;
   MonsterMotions[MonsterFAccelerating1].ChangeList[4]=ToMonsterFBraking;
   MonsterMotions[MonsterFAccelerating1].ChangeList[5]=ToMonsterFDecelerating;
   MonsterMotions[MonsterFAccelerating1].ChangeList[6]=ToMonsterFTopSpeed1;


   if(RLMalloc((void **)&(MonsterMotions[MonsterFAccelerating2].ChangeList  ),7*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterFAccelerating2].numchanges=7;
   MonsterMotions[MonsterFAccelerating2].WhatToDo=MonsterFAccelerating2Function;
   MonsterMotions[MonsterFAccelerating2].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterFAccelerating2].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterFAccelerating2].ChangeList[2]=ToMonsterWaiting;
   MonsterMotions[MonsterFAccelerating2].ChangeList[3]=ToMonsterJumping;
   MonsterMotions[MonsterFAccelerating2].ChangeList[4]=ToMonsterFBraking;
   MonsterMotions[MonsterFAccelerating2].ChangeList[5]=ToMonsterFDecelerating;
   MonsterMotions[MonsterFAccelerating2].ChangeList[6]=ToMonsterFTopSpeed2;


   if(RLMalloc((void **)&(MonsterMotions[MonsterFAccelerating3].ChangeList  ),6*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterFAccelerating3].numchanges=6;
   MonsterMotions[MonsterFAccelerating3].WhatToDo=MonsterFAccelerating3Function;
   MonsterMotions[MonsterFAccelerating3].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterFAccelerating3].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterFAccelerating3].ChangeList[2]=ToMonsterJumping;
   MonsterMotions[MonsterFAccelerating3].ChangeList[3]=ToMonsterFBraking;
   MonsterMotions[MonsterFAccelerating3].ChangeList[4]=ToMonsterFDecelerating;
   MonsterMotions[MonsterFAccelerating3].ChangeList[5]=ToMonsterFTopSpeed3;


   if(RLMalloc((void **)&(MonsterMotions[MonsterFAccelerating4].ChangeList  ),5*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterFAccelerating4].numchanges=5;
   MonsterMotions[MonsterFAccelerating4].WhatToDo=MonsterFAccelerating4Function;
   MonsterMotions[MonsterFAccelerating4].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterFAccelerating4].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterFAccelerating4].ChangeList[2]=ToMonsterJumping;
   MonsterMotions[MonsterFAccelerating4].ChangeList[3]=ToMonsterFBraking;
   MonsterMotions[MonsterFAccelerating4].ChangeList[4]=ToMonsterFTopSpeed4;


   if(RLMalloc((void **)&(MonsterMotions[MonsterFTopSpeed1].ChangeList      ),7*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterFTopSpeed1].numchanges=7;
   MonsterMotions[MonsterFTopSpeed1].WhatToDo=MonsterFTopSpeed1Function;
   MonsterMotions[MonsterFTopSpeed1].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterFTopSpeed1].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterFTopSpeed1].ChangeList[2]=ToMonsterWaiting;
   MonsterMotions[MonsterFTopSpeed1].ChangeList[3]=ToMonsterJumping;
   MonsterMotions[MonsterFTopSpeed1].ChangeList[4]=ToMonsterFBraking;
   MonsterMotions[MonsterFTopSpeed1].ChangeList[5]=ToMonsterFDecelerating;
   MonsterMotions[MonsterFTopSpeed1].ChangeList[6]=ToMonsterFAccelerating2;


   if(RLMalloc((void **)&(MonsterMotions[MonsterFTopSpeed2].ChangeList      ),7*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterFTopSpeed2].numchanges=7;
   MonsterMotions[MonsterFTopSpeed2].WhatToDo=MonsterFTopSpeed2Function;
   MonsterMotions[MonsterFTopSpeed2].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterFTopSpeed2].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterFTopSpeed2].ChangeList[2]=ToMonsterWaiting;
   MonsterMotions[MonsterFTopSpeed2].ChangeList[3]=ToMonsterJumping;
   MonsterMotions[MonsterFTopSpeed2].ChangeList[4]=ToMonsterFBraking;
   MonsterMotions[MonsterFTopSpeed2].ChangeList[5]=ToMonsterFDecelerating;
   MonsterMotions[MonsterFTopSpeed2].ChangeList[6]=ToMonsterFAccelerating3;


   if(RLMalloc((void **)&(MonsterMotions[MonsterFTopSpeed3].ChangeList      ),6*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterFTopSpeed3].numchanges=6;
   MonsterMotions[MonsterFTopSpeed3].WhatToDo=MonsterFTopSpeed3Function;
   MonsterMotions[MonsterFTopSpeed3].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterFTopSpeed3].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterFTopSpeed3].ChangeList[2]=ToMonsterJumping;
   MonsterMotions[MonsterFTopSpeed3].ChangeList[3]=ToMonsterFBraking;
   MonsterMotions[MonsterFTopSpeed3].ChangeList[4]=ToMonsterFDecelerating;
   MonsterMotions[MonsterFTopSpeed3].ChangeList[5]=ToMonsterFAccelerating4;


   if(RLMalloc((void **)&(MonsterMotions[MonsterFTopSpeed4].ChangeList      ),3*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterFTopSpeed4].numchanges=3;
   MonsterMotions[MonsterFTopSpeed4].WhatToDo=MonsterFTopSpeed4Function;
   MonsterMotions[MonsterFTopSpeed4].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterFTopSpeed4].ChangeList[1]=ToMonsterStopped;
//   MonsterMotions[MonsterFTopSpeed4].ChangeList[2]=ToMonsterJumping;
   MonsterMotions[MonsterFTopSpeed4].ChangeList[2]=ToMonsterFBraking;


   if(RLMalloc((void **)&(MonsterMotions[MonsterFDecelerating].ChangeList   ),8*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterFDecelerating].numchanges=8;
   MonsterMotions[MonsterFDecelerating].WhatToDo=MonsterFDeceleratingFunction;
   MonsterMotions[MonsterFDecelerating].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterFDecelerating].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterFDecelerating].ChangeList[2]=ToMonsterJumping;
   MonsterMotions[MonsterFDecelerating].ChangeList[3]=ToMonsterWaiting;
   MonsterMotions[MonsterFDecelerating].ChangeList[4]=ToMonsterFBraking;
   MonsterMotions[MonsterFDecelerating].ChangeList[5]=ToMonsterFAccelerating3;
   MonsterMotions[MonsterFDecelerating].ChangeList[6]=ToMonsterFAccelerating2;
   MonsterMotions[MonsterFDecelerating].ChangeList[7]=ToMonsterFAccelerating1;


   if(RLMalloc((void **)&(MonsterMotions[MonsterFBraking].ChangeList        ),8*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterFBraking].numchanges=8;
   MonsterMotions[MonsterFBraking].WhatToDo=MonsterFBrakingFunction;
   MonsterMotions[MonsterFBraking].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterFBraking].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterFBraking].ChangeList[2]=ToMonsterWaiting;
   MonsterMotions[MonsterFBraking].ChangeList[3]=ToMonsterJumping;
   MonsterMotions[MonsterFBraking].ChangeList[4]=ToMonsterFDecelerating;
   MonsterMotions[MonsterFBraking].ChangeList[5]=ToMonsterFAccelerating3;
   MonsterMotions[MonsterFBraking].ChangeList[6]=ToMonsterFAccelerating2;
   MonsterMotions[MonsterFBraking].ChangeList[7]=ToMonsterFAccelerating1;


   if(RLMalloc((void **)&(MonsterMotions[MonsterBAccelerating1].ChangeList  ),6*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterBAccelerating1].numchanges=6;
   MonsterMotions[MonsterBAccelerating1].WhatToDo=MonsterBAccelerating1Function;
   MonsterMotions[MonsterBAccelerating1].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterBAccelerating1].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterBAccelerating1].ChangeList[2]=ToMonsterWaiting;
   MonsterMotions[MonsterBAccelerating1].ChangeList[3]=ToMonsterBBraking;
   MonsterMotions[MonsterBAccelerating1].ChangeList[4]=ToMonsterBDecelerating;
   MonsterMotions[MonsterBAccelerating1].ChangeList[5]=ToMonsterBTopSpeed1;


   if(RLMalloc((void **)&(MonsterMotions[MonsterBAccelerating2].ChangeList  ),6*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterBAccelerating2].numchanges=6;
   MonsterMotions[MonsterBAccelerating2].WhatToDo=MonsterBAccelerating2Function;
   MonsterMotions[MonsterBAccelerating2].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterBAccelerating2].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterBAccelerating2].ChangeList[2]=ToMonsterWaiting;
   MonsterMotions[MonsterBAccelerating2].ChangeList[3]=ToMonsterBBraking;
   MonsterMotions[MonsterBAccelerating2].ChangeList[4]=ToMonsterBDecelerating;
   MonsterMotions[MonsterBAccelerating2].ChangeList[5]=ToMonsterBTopSpeed2;


   if(RLMalloc((void **)&(MonsterMotions[MonsterBTopSpeed1].ChangeList      ),6*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterBTopSpeed1].numchanges=6;
   MonsterMotions[MonsterBTopSpeed1].WhatToDo=MonsterBTopSpeed1Function;
   MonsterMotions[MonsterBTopSpeed1].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterBTopSpeed1].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterBTopSpeed1].ChangeList[2]=ToMonsterWaiting;
   MonsterMotions[MonsterBTopSpeed1].ChangeList[3]=ToMonsterBBraking;
   MonsterMotions[MonsterBTopSpeed1].ChangeList[4]=ToMonsterBDecelerating;
   MonsterMotions[MonsterBTopSpeed1].ChangeList[5]=ToMonsterBAccelerating2;

   if(RLMalloc((void **)&(MonsterMotions[MonsterBTopSpeed2].ChangeList      ),5*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterBTopSpeed2].numchanges=5;
   MonsterMotions[MonsterBTopSpeed2].WhatToDo=MonsterBTopSpeed2Function;
   MonsterMotions[MonsterBTopSpeed2].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterBTopSpeed2].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterBTopSpeed2].ChangeList[2]=ToMonsterWaiting;
   MonsterMotions[MonsterBTopSpeed2].ChangeList[3]=ToMonsterBBraking;
   MonsterMotions[MonsterBTopSpeed2].ChangeList[4]=ToMonsterBDecelerating;


   if(RLMalloc((void **)&(MonsterMotions[MonsterBDecelerating].ChangeList   ),6*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterBDecelerating].numchanges=6;
   MonsterMotions[MonsterBDecelerating].WhatToDo=MonsterBDeceleratingFunction;
   MonsterMotions[MonsterBDecelerating].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterBDecelerating].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterBDecelerating].ChangeList[2]=ToMonsterWaiting;
   MonsterMotions[MonsterBDecelerating].ChangeList[3]=ToMonsterBBraking;
   MonsterMotions[MonsterBDecelerating].ChangeList[4]=ToMonsterBAccelerating2;
   MonsterMotions[MonsterBDecelerating].ChangeList[5]=ToMonsterBAccelerating1;


   if(RLMalloc((void **)&(MonsterMotions[MonsterBBraking].ChangeList        ),3*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterBBraking].numchanges=3;
   MonsterMotions[MonsterBBraking].WhatToDo=MonsterBBrakingFunction;
   MonsterMotions[MonsterBBraking].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterBBraking].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterBBraking].ChangeList[2]=ToMonsterWaiting;

/*
   if(RLMalloc((void **)&(MonsterMotions[MonsterLAccelerating1].ChangeList  ),5*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterLAccelerating1].numchanges=5;
   MonsterMotions[MonsterLAccelerating1].WhatToDo=MonsterLAccelerating1Function;
   MonsterMotions[MonsterLAccelerating1].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterLAccelerating1].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterLAccelerating1].ChangeList[2]=ToMonsterWaiting;
   MonsterMotions[MonsterLAccelerating1].ChangeList[3]=ToMonsterLDecelerating;
   MonsterMotions[MonsterLAccelerating1].ChangeList[4]=ToMonsterLTopSpeed1;


   if(RLMalloc((void **)&(MonsterMotions[MonsterLTopSpeed1].ChangeList      ),4*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterLTopSpeed1].numchanges=4;
   MonsterMotions[MonsterLTopSpeed1].WhatToDo=MonsterLTopSpeed1Function;
   MonsterMotions[MonsterLTopSpeed1].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterLTopSpeed1].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterLTopSpeed1].ChangeList[2]=ToMonsterWaiting;
   MonsterMotions[MonsterLTopSpeed1].ChangeList[3]=ToMonsterLDecelerating;


   if(RLMalloc((void **)&(MonsterMotions[MonsterLDecelerating].ChangeList   ),4*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterLDecelerating].numchanges=4;
   MonsterMotions[MonsterLDecelerating].WhatToDo=MonsterLDeceleratingFunction;
   MonsterMotions[MonsterLDecelerating].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterLDecelerating].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterLDecelerating].ChangeList[2]=ToMonsterWaiting;
   MonsterMotions[MonsterLDecelerating].ChangeList[3]=ToMonsterLAccelerating1;


   if(RLMalloc((void **)&(MonsterMotions[MonsterLBraking].ChangeList        ),3*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterLBraking].numchanges=3;
   MonsterMotions[MonsterLBraking].WhatToDo=MonsterLBrakingFunction;
   MonsterMotions[MonsterLBraking].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterLBraking].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterLBraking].ChangeList[2]=ToMonsterWaiting;


   if(RLMalloc((void **)&(MonsterMotions[MonsterRAccelerating1].ChangeList  ),5*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterRAccelerating1].numchanges=5;
   MonsterMotions[MonsterRAccelerating1].WhatToDo=MonsterRAccelerating1Function;
   MonsterMotions[MonsterRAccelerating1].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterRAccelerating1].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterRAccelerating1].ChangeList[2]=ToMonsterWaiting;
   MonsterMotions[MonsterRAccelerating1].ChangeList[3]=ToMonsterRDecelerating;
   MonsterMotions[MonsterRAccelerating1].ChangeList[4]=ToMonsterRTopSpeed1;



   if(RLMalloc((void **)&(MonsterMotions[MonsterRTopSpeed1].ChangeList      ),4*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterRTopSpeed1].numchanges=4;
   MonsterMotions[MonsterRTopSpeed1].WhatToDo=MonsterRTopSpeed1Function;
   MonsterMotions[MonsterRTopSpeed1].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterRTopSpeed1].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterRTopSpeed1].ChangeList[2]=ToMonsterWaiting;
   MonsterMotions[MonsterRTopSpeed1].ChangeList[3]=ToMonsterRDecelerating;


   if(RLMalloc((void **)&(MonsterMotions[MonsterRDecelerating].ChangeList   ),4*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterRDecelerating].numchanges=4;
   MonsterMotions[MonsterRDecelerating].WhatToDo=MonsterRDeceleratingFunction;
   MonsterMotions[MonsterRDecelerating].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterRDecelerating].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterRDecelerating].ChangeList[2]=ToMonsterWaiting;
   MonsterMotions[MonsterRDecelerating].ChangeList[3]=ToMonsterRAccelerating1;


   if(RLMalloc((void **)&(MonsterMotions[MonsterRBraking].ChangeList        ),3*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterRBraking].numchanges=3;
   MonsterMotions[MonsterRBraking].WhatToDo=MonsterRBrakingFunction;
   MonsterMotions[MonsterRBraking].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterRBraking].ChangeList[1]=ToMonsterStopped;
   MonsterMotions[MonsterRBraking].ChangeList[2]=ToMonsterWaiting;
*/

   if(RLMalloc((void **)&(MonsterMotions[MonsterJumping].ChangeList         ),2*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterJumping].numchanges=2;
   MonsterMotions[MonsterJumping].WhatToDo=MonsterJumpingFunction;
   MonsterMotions[MonsterJumping].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[MonsterJumping].ChangeList[1]=ToMonsterStopped;


   if(RLMalloc((void **)&(MonsterMotions[MonsterAirborne].ChangeList        ),5*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[MonsterAirborne].numchanges=5;
   MonsterMotions[MonsterAirborne].WhatToDo=MonsterAirborneFunction;
   MonsterMotions[MonsterAirborne].ChangeList[0]=ToMonsterStopped;
   MonsterMotions[MonsterAirborne].ChangeList[1]=ToMonsterFTopSpeed4;
   MonsterMotions[MonsterAirborne].ChangeList[2]=ToMonsterFTopSpeed3;
   MonsterMotions[MonsterAirborne].ChangeList[3]=ToMonsterFTopSpeed2;
   MonsterMotions[MonsterAirborne].ChangeList[4]=ToMonsterFTopSpeed1;
//   MonsterMotions[MonsterAirborne].ChangeList[5]=ToMonsterWaiting;
//   MonsterMotions[MonsterAirborne].ChangeList[6]=ToMonsterFBraking;
//   MonsterMotions[MonsterAirborne].ChangeList[7]=ToMonsterFDecelerating;


//   if(RLMalloc((void **)&(MonsterMotions[MonsterStopped].ChangeList         ),1*sizeof(StateChange))!=RLNoError)
//      return 0;
   MonsterMotions[MonsterStopped].ChangeList=NULL;
   MonsterMotions[MonsterStopped].numchanges=0;
   MonsterMotions[MonsterStopped].WhatToDo=MonsterStoppedFunction;

   MonsterMotions[MonsterKnockBackward].ChangeList=NULL;
   MonsterMotions[MonsterKnockBackward].numchanges=0;
   MonsterMotions[MonsterKnockBackward].WhatToDo=MonsterKnockBackwardFunction;

   if(RLMalloc((void **)&(MonsterMotions[RoggoshHomer].ChangeList         ),2*sizeof(StateChange))!=RLNoError)
      return 0;
   MonsterMotions[RoggoshHomer].WhatToDo=RoggoshHomerFunction;
   MonsterMotions[RoggoshHomer].numchanges=2;
   MonsterMotions[RoggoshHomer].ChangeList[0]=ToMonsterAirborne;
   MonsterMotions[RoggoshHomer].ChangeList[1]=ToMonsterStopped;

//   if(RLMalloc((void **)&(MonsterMotions[NeallothDiveBomb].ChangeList         ),1*sizeof(StateChange))!=RLNoError)
//      return 0;
//   MonsterMotions[NeallothDiveBomb].numchanges=1;
   MonsterMotions[NeallothDiveBomb].ChangeList=NULL;
   MonsterMotions[NeallothDiveBomb].numchanges=0;
   MonsterMotions[NeallothDiveBomb].WhatToDo=NeallothDiveBombFunction;
//   MonsterMotions[NeallothDiveBomb].ChangeList[0]=ToMonsterAirborne;

//   MonsterMotions[MonsterStopped].ChangeList[0]=ToMonsterWaiting;
   size2=RLGetTotalAllocated();
// printf("loaded movement engine, size %d\n",filename,size2-size1);
   return 1;

}

void DestroyMonsterMotionEngine()
{
   int i;
    size_t size1,size2;
   size1=RLGetTotalAllocated();
   for(i=MonsterWaiting;i<MonsterKnockBackward;++i)
   {
      if(MonsterMotions[i].numchanges)
	   RLFree(MonsterMotions[i].ChangeList);
   }
   size2=RLGetTotalAllocated();
   //intf("unloaded motion engine, size %d\n",filename,size1-size2);
   
}

#ifndef _RobotMOVE_H_
#define _RobotMOVE_H_

#ifdef MINIWIN
#include "miniwin/windows.h"
#else
#include <windows.h>
#endif
#include <stdio.h>

void GetRobotMovementInfo(FILE *input);
void DefineRobotMotionConstants();
int InitRobotMotionEngine();
void DestroyRobotMotionEngine();
void churn(MovingObjectData mover);

extern int RobotMovementState;               //This is the main control of the state.
extern int RobotNumMovementFrames;   //This counts the number of frames the current movement state has been active.

extern RLValue RobotSpeed;
extern RLValue RobotDistance;      //RobotDistance = integral of speed, i.e. arclength.
extern RLValue RobotYSpeed;
extern RLVector RobotPosition;     //These 4 items are controlled by/used by the state functions
extern RLVector RobotVelocity;

//Flags which control whether or not you can affect movement.

extern int RobotMidair;  //This will be changed by altitude bitmap calculations, and will control entering/leaving the Airborne state.
extern int RobotIsHit;   //This will be changed by the collision detection module
extern int RobotIsBusy;   //This will be changed by the animation engine, when something's up.
extern int RobotTurning;  //This is 0 if not RobotTurning, 1 if RobotTurning left, -1 if RobotTurning right.

extern int FramesStopped;  //This will be totally obsolete as soon as the animation engine works.
extern int RobotHitObstacle;    //This is for remembering if the airborne state included a wall collision.

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

#endif
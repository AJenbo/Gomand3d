#ifndef _MONMOVE_H_
#define _MONMOVE_H_

#include <windows.h>
#include <stdio.h>

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

void GetMonsterMovementInfo(FILE *input);
void DefineMonsterMotionConstants();
int InitMonsterMotionEngine();
void DestroyMonsterMotionEngine();
void knead(MovingObjectData mover);

extern int MonsterMovementState;               //This is the main control of the state.
extern int MonsterNumMovementFrames;   //This counts the number of frames the current movement state has been active.

extern RLValue MonsterSpeed;
extern RLValue MonsterDistance;      //MonsterDistance = integral of speed, i.e. arclength.
extern RLValue MonsterYSpeed;
extern RLVector MonsterPosition;     //These 4 items are controlled by/used by the state functions
extern RLVector MonsterVelocity;

//Flags which control whether or not you can affect movement.

extern int MonsterMidair;  //This will be changed by altitude bitmap calculations, and will control entering/leaving the Airborne state.
extern int MonsterIsHit;   //This will be changed by the collision detection module
extern int MonsterIsBusy;   //This will be changed by the animation engine, when something's up.
extern int MonsterTurning;  //This is 0 if not MonsterTurning, 1 if MonsterTurning left, -1 if MonsterTurning right.

extern int MonsterFramesStopped;  //This will be totally obsolete as soon as the animation engine works.
extern int MonsterHitObstacle;    //This is for remembering if the airborne state included a wall collision.

#endif
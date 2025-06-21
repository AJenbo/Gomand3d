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
File:           boink.h
Author:         Bruce Abe
Date:           9-29-95
Version:        1.0



************************************************************************
REVISION HISTORY        (Add Edits and History to top of list).

Edited By:      editors_name.here
Edited Date:    edited_date.here
Changes:
                changed VERSION_NUMBER from THIS to THAT.
                changed this item from this to that.
                changed that item from that to that.


***********************************************************************/
#ifndef _BOINK_H_
#define _BOINK_H_

//#define VisualRepresentation

#ifdef _ITC_D3D_
#include "rl2d3d.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _hotspot_
{
   RLFrame position;
   RLValue radius;
//   int NumPoints;
//   int NumSpheres;
   RLVector point1;
//   RLVector point2;//only used for swords.
#ifdef VisualRepresentation

   RLFrame BallFrame1;//For sfx only, will be removed soon.
   RLFrame BallFrame2;
   RLColour BallColor;
#endif
}HotSpot;

typedef struct _hotspot2_
{
   RLFrame position;
   RLValue radius;
   RLVector point1;
   RLVector point2;
#ifdef VisualRepresentation // BSH add in 6.4 !
   RLFrame BallFrame1;//For sfx only, will be removed soon.
   RLFrame BallFrame2;
   RLColour BallColor;
#endif
}HotSpot2;

typedef struct _moving_object_data_ *MovingObjectData;

typedef void (*AnimationFunction) (void);
typedef void (*MotionFunction) (MovingObjectData movedata);
typedef void (*CollisionResolutionFunction) (MovingObjectData movedata);


struct _moving_object_data_
{
//   int ArrayIndex;
   MovingObjectData SafePassageIndex;     //This tells the collision detection to ignore a specific object.
                                          //It's for the case when the monster's plasma would hit the monster, etc.
   int RemoveMeFlag;
   RLFrame PositioningFrame;              
   RLVector CurrentPosition;              //This is a worker, and doesn't need to be initialized.
   RLVector ProjectedPosition;            //This is a worker, and doesn't need to be initialized.
   int NumOffensiveSpheres;
   HotSpot* OffensiveSphereList[5];
   int NumDefensiveSpheres;
   HotSpot* DefensiveSphereList[5];
   int NumOffensiveTubes;
   HotSpot2* OffensiveTubeList[5];
   int DamageICause;
   int DamageIveTaken;
   int collisionflag;
   RLVector CollisionVector;              //This is a worker, and doesn't need to be initialized.
   RLBox Volume;
   RLBox CurrentVolume;                   //This is a worker, and doesn't need to be initialized.
   AnimationFunction AnimateMe;           //This can be null if necessary.
   MotionFunction MoveMe;                 //This must be defined.
   CollisionResolutionFunction HandleMe;  //This must be defined.
   int data;                              //This is just for the case of the rapid fire.
   RLValue mass;						  // 
};

extern MovingObjectData MovingObjects[];
extern int NumMovingObjects;

void ClockworkGod(void);
void LaunchVisorBeam(void);
int AddMovingObject(MovingObjectData newmover);

extern HotSpot RobotHotSpots[5];
extern HotSpot2 RobotSwordSpots[2];
extern HotSpot MonsterHotSpots[4];
extern HotSpot2 MonsterTailSpots[1];
void InitMonsterHotSpots(void);
void InitRobotHotSpots(void);
void InitClockworkGod(void);
void grind();
void HandleMonsterHit(MovingObjectData movedata);
void BootAllRobotFrames();
void BootAllMonsterFrames();


#define RobotLeftSword 0
#define RobotRightSword 1
#define RobotLeftFoot 0
#define RobotRightFoot 1
#define RobotChest 2
#define RobotHead 3
#define RobotPelvis 4

#define RoggoshRightClaw 0
#define RoggoshLeftClaw 1
#define RoggoshBody 2
#define RoggoshHead 3
#define RoggoshTail 0
extern struct _moving_object_data_ MonsterData;
extern struct _moving_object_data_ RobotData;

#ifdef __cplusplus
};
#endif

#endif
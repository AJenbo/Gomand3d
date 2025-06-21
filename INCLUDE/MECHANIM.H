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
File:           Robotanim.h
Author:         Bruce Abe
Date:           9-28-95
Version:        1.0



************************************************************************
REVISION HISTORY        (Add Edits and History to top of list).

Edited By:      
Edited Date:    
Changes:
                changed VERSION_NUMBER 


***********************************************************************/
#ifndef _RobotANIM_H_
#define _RobotANIM_H_

#include <windows.h>
#include <stdio.h>

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

extern int RobotAnimationState;               //This is the main control of the state.
extern RLValue RobotAnimationFrame;           //This is the current frame of the animation.
extern RLValue RobotLastVerticalSpeed;        //I'll go into the jump freeze after a certain number of frames, and come out when 

void GetRobotAnimInfo(FILE *input);
void thresh(void);
void DefineRobotAnimationConstants();
int ClearRobotAnimations();
int InitRobotAnimationEngine();
int LoadRobotAnimations();

void DestroyRobotAnimationEngine();

#endif


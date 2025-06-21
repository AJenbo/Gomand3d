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
File:           monanim.h
Author:         Bruce Abe
Date:           9-26-95
Version:        1.0



************************************************************************
REVISION HISTORY        (Add Edits and History to top of list).

Edited By:      
Edited Date:    
Changes:
***********************************************************************/
#ifndef _MONANIM_H_
#define _MONANIM_H_

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
#define MonsterTravel		      33
#define MonsterTaunt2             34

void tenderize();
void GetMonsterAnimInfo(FILE *input);
void DefineMonsterAnimationConstants();
int ClearMonsterAnimations();
int InitMonsterAnimationEngine();
int LoadMonsterAnimations();
void tenderize(void);

void DestroyMonsterAnimationEngine();

extern int MonsterAnimationState;               //This is the main control of the state.
extern RLValue MonsterAnimationFrame;           //This is the current frame of the animation.
extern RLValue MonsterLastVerticalSpeed;        //I'll go into the jump freeze after a certain number of frames, and come out when 

#endif
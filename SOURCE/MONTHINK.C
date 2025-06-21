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
File:           monthink.c
Author:         Bruce Abe
Date:           9-28-95
Version:        1.0001



************************************************************************
REVISION HISTORY        (Add Edits and History to top of list).

Edited By:      Bruce Abe
Edited Date:    10-2-95
Changes:
                changed VERSION_NUMBER from 1.0 to 1.0001.
                put in a triple-toggle, for three levels of 
                monstermadness.


***********************************************************************/
#include "cars.h"

#define HuntRobot 0
#define HuntMissionBuilding 1
#define HuntAnyBuilding 2
#define EvadeRobot 3
#define DefendAgainstRobot 4

//#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//replace rl with rl2d3d.h. By Sanfo 5/18/96
//#include "rl.h"
#include "rl2d3d.h"
#include "wrapper.h"

#include "keycom.h"
#include "boink.h"
#include "monmove.h"
#include "monanim.h"
#include "Robotanim.h"
#include "monthink.h"
#include "building.h"
#include "timing.h"
#include "gosys.h"
#include "landscap.h"
#include "global.h"    

#define abs(x) ((x)>0?(x):(-x))
static BOOL Aiaeinitted = FALSE;
const int MinMoveFrames=0;
//const RLValue MinDistance=RLVal(0.1);
//const RLValue FiringRange = RLVal(6.5);
RLValue MinDistance;
RLValue FiringRange;
visible_buildings missiontarget, arbitrarytarget;
int targetnum;
int MonsterGoal=0;
int MonsterOffTactic;


RLValue OffensiveTacticMarkedCountDown;
int OffensiveTacticMarked;
int OffensiveTacticMarkedFlag;
int OffensiveTacticAttempts[20];
RLValue OffensiveTacticSuccesses[20];
int OffensiveTacticMarkedRobotLife;
int OffensiveTacticMarkedMnstLife;

extern RLFrame Robotframe,monstframe;
//extern int submonster;
extern int RobotLife;
extern int MnstLife;
extern int RobotEngy;
extern int MnstEngy;
//extern int level;
extern volatile long int *InputIntPtr2;				// Input stream from monster AE
extern volatile long int *InputIntPtr;				// Input stream from player
extern volatile long int *InputIntPtr3;				// Input stream from Robot AE
extern RLVector monstorigin;

int FramesSinceLastInput = 0;
int monthink = 3;

RLValue JoyFromDestruction[7][3] = 
	{
		{ RLVal(0.000), RLVal(0.000), RLVal(0.000) },	// Virtual
		{ RLVal(0.001), RLVal(0.001), RLVal(0.001) },	// Roggosh
		{ RLVal(0.001), RLVal(0.001), RLVal(0.001) },	// Kothos
		{ RLVal(0.001), RLVal(0.001), RLVal(0.001) },	// Tolgo
		{ RLVal(0.002), RLVal(0.001), RLVal(0.001) },	// Shagtoq
		{ RLVal(0.0002), RLVal(0.0001), RLVal(0.000) },	// Nealloth
		{ RLVal(0.002), RLVal(0.002), RLVal(0.002) }	// Gaingris
	};
RLValue JoyFromWinning[7][3] = 
	{
		{ RLVal(0.000), RLVal(0.000), RLVal(0.000) },	// Virtual
		{ RLVal(0.001), RLVal(0.001), RLVal(0.001) },	// Roggosh
		{ RLVal(0.001), RLVal(0.001), RLVal(0.001) },	// Kothos
		{ RLVal(0.001), RLVal(0.001), RLVal(0.001) },	// Tolgo
		{ RLVal(0.001), RLVal(0.001), RLVal(0.001) },	// Shagtoq
		{ RLVal(0.001), RLVal(0.002), RLVal(0.003) },	// Nealloth
		{ RLVal(0.001), RLVal(0.002), RLVal(0.003) }	// Gaingris
	};
RLValue RageDiminshment[7][3] = 
	{
		{ RLVal(5.00), RLVal(5.00), RLVal(5.00) },	// Virtual 
		{ RLVal(0.10), RLVal(0.10), RLVal(0.10) },	// Roggosh 
		{ RLVal(0.05), RLVal(0.05), RLVal(0.05) },	// Kothos 
		{ RLVal(0.025), RLVal(0.025), RLVal(0.025) },	// Tolgo 
		{ RLVal(0.10), RLVal(0.05), RLVal(0.02) },	// Shagtoq 
		{ RLVal(0.025), RLVal(0.025), RLVal(0.025) },	// Nealloth 
		{ RLVal(0.025), RLVal(0.025), RLVal(0.025) }	// Gaingris
	};
RLValue BoredomWithoutRage[7][3] = 
	{
		{ RLVal(0.000), RLVal(0.000), RLVal(0.000) },	// Virtual
		{ RLVal(0.001), RLVal(0.001), RLVal(0.001) },	// Roggosh
		{ RLVal(0.001), RLVal(0.001), RLVal(0.001) },	// Kothos
		{ RLVal(0.001), RLVal(0.001), RLVal(0.001) },	// Tolgo
		{ RLVal(0.005), RLVal(0.010), RLVal(0.025) },	// Shagtoq
		{ RLVal(0.001), RLVal(0.001), RLVal(0.001) },	// Nealloth
		{ RLVal(0.001), RLVal(0.001), RLVal(0.001) }	// Gaingris
	};
RLValue FearDiminishment[7][3] = 
	{
		{ RLVal(5.0), RLVal(5.0), RLVal(5.0) },	// Virtual
		{ RLVal(1.25), RLVal(1.25), RLVal(1.25) },	// Roggosh
		{ RLVal(0.85), RLVal(0.85), RLVal(0.85) },	// Kothos
		{ RLVal(0.85), RLVal(0.85), RLVal(0.85) },	// Tolgo
		{ RLVal(0.80), RLVal(0.82), RLVal(0.81) },	// Shagtoq
		{ RLVal(0.95), RLVal(0.85), RLVal(0.85) },	// Nealloth
		{ RLVal(0.95), RLVal(1.15), RLVal(1.25) }	// Gaingris
	};
RLValue BoredomWithoutFear[7][3] = 
	{
		{ RLVal(0.000), RLVal(0.000), RLVal(0.000) },	// Virtual
		{ RLVal(0.001), RLVal(0.001), RLVal(0.001) },	// Roggosh
		{ RLVal(0.001), RLVal(0.001), RLVal(0.001) },	// Kothos
		{ RLVal(0.001), RLVal(0.001), RLVal(0.001) },	// Tolgo
		{ RLVal(0.005), RLVal(0.005), RLVal(0.010) },	// Shagtoq
		{ RLVal(0.001), RLVal(0.001), RLVal(0.001) },	// Nealloth
		{ RLVal(0.001), RLVal(0.001), RLVal(0.001) }	// Gaingris
	};
RLValue BoredomFarFromRobot[7][3] = 
	{
		{ RLVal(0.00000), RLVal(0.00000), RLVal(0.00000) },	// Virtual
		{ RLVal(0.00001), RLVal(0.00001), RLVal(0.00001) },	// Roggosh
		{ RLVal(0.00001), RLVal(0.00001), RLVal(0.00001) },	// Kothos
		{ RLVal(0.00001), RLVal(0.00001), RLVal(0.00001) },	// Tolgo
		{ RLVal(0.00001), RLVal(0.00001), RLVal(0.00001) },	// Shagtoq
		{ RLVal(0.00001), RLVal(0.00001), RLVal(0.00001) },	// Nealloth
		{ RLVal(0.00001), RLVal(0.00001), RLVal(0.00001) }	// Gaingris
	};
RLValue FearFromAttack[7][3] = 
	{
		{ RLVal(0.000), RLVal(0.000), RLVal(0.000) },	// Virtual
		{ RLVal(1.500), RLVal(1.200), RLVal(1.250) },	// Roggosh
		{ RLVal(0.500), RLVal(0.500), RLVal(0.500) },	// Kothos
		{ RLVal(0.500), RLVal(0.505), RLVal(0.500) },	// Tolgo
		{ RLVal(0.500), RLVal(0.500), RLVal(0.000) },	// Shagtoq
		{ RLVal(0.500), RLVal(0.250), RLVal(0.250) },	// Nealloth
		{ RLVal(0.500), RLVal(0.250), RLVal(0.250) }	// Gaingris
	};
RLValue JoyForHapppyHappyJoyJoy[7][3] = 
	{
		{ RLVal(99), RLVal(99), RLVal(99) },	// Virtual
		{ RLVal(10), RLVal(10), RLVal(10) },	// Roggosh
		{ RLVal(10), RLVal(10), RLVal(10) },	// Kothos
		{ RLVal(10), RLVal(10), RLVal(10) },	// Tolgo
		{ RLVal(10), RLVal(10), RLVal(10) },	// Shagtoq
		{ RLVal(20), RLVal(20), RLVal(20) },	// Nealloth
		{ RLVal(25), RLVal(25), RLVal(25) }	// Gaingris
	};
RLValue Aggressiveness[7][3] = 
	{
		{RLVal(5.0), RLVal(5.0), RLVal(5.0)},	// Virtual
		{RLVal(5.0), RLVal(5.0), RLVal(5.0)},	// Roggosh
		{RLVal(5.0), RLVal(5.0), RLVal(5.0)},	// Kothos
		{RLVal(5.0), RLVal(5.0), RLVal(5.0)},	// Tolgo
		{RLVal(5.0), RLVal(5.0), RLVal(5.0)},	// Shagtoq
		{RLVal(10.0), RLVal(10.0), RLVal(15.0)},	// Nealloth
		{RLVal(10.0), RLVal(10.0), RLVal(20.0)}	// Gaingris
	};
RLValue Cowardliness[7][3] = 
	{ 
		{RLVal(5.0), RLVal(5.0), RLVal(5.0)},	// Virtual
		{RLVal(5.0), RLVal(5.0), RLVal(5.0)},	// Roggosh
		{RLVal(5.0), RLVal(5.0), RLVal(5.0)},	// Kothos
		{RLVal(5.0), RLVal(5.0), RLVal(5.0)},	// Tolgo
		{RLVal(5.0), RLVal(5.0), RLVal(5.0)},	// Shagtoq
		{RLVal(10.0), RLVal(10.0), RLVal(15.0)},	// Nealloth
		{RLVal(10.0), RLVal(10.0), RLVal(20.0)}	// Gaingris
	};
RLValue Conservativeness[7][3] = 
	{ 
		{RLVal(1.0), RLVal(10.0), RLVal(20.0) },	// Virtual
		{RLVal(1.0), RLVal(10.0), RLVal(20.0) },	// Roggosh
		{RLVal(1.0), RLVal(10.0), RLVal(20.0) },	// Kothos
		{RLVal(1.0), RLVal(10.0), RLVal(20.0) },	// Tolgo
		{RLVal(1.0), RLVal(10.0), RLVal(20.0) },	// Shagtoq
		{RLVal(1.0), RLVal(10.0), RLVal(20.0) },	// Nealloth
		{RLVal(1.0), RLVal(10.0), RLVal(20.0) }		// Gaingris
	};

RLValue Frustration[7][3] = 
	{ 
		{RLVal(0.0), RLVal(0.0), RLVal(0.0) },	// Virtual
		{RLVal(1.0), RLVal(1.0), RLVal(1.0) },	// Roggosh
		{RLVal(2.0), RLVal(2.0), RLVal(2.0) },	// Kothos
		{RLVal(4.0), RLVal(4.0), RLVal(5.0) },	// Tolgo
		{RLVal(5.0), RLVal(6.0), RLVal(7.0) },	// Shagtoq
		{RLVal(6.0), RLVal(8.0), RLVal(9.0) },	// Nealloth
		{RLVal(7.0), RLVal(10.0), RLVal(12.0) }		// Gaingris
	};


void EnactOffensiveTactic(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int newtactic);
void EnactDefensiveTactic(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int newtactic);
void EnactEvasiveTactic(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int newtactic);

int  MoveAndShootNormally(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int urgency, int attacktype);
int  MoveAndShootFromBehind(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int urgency);
int  MoveAndShootFromHighGround(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int urgency);
int  MoveAndShootFromLowGround(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int urgency);
int  MoveAndShootFromLevelGround(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int urgency);

void MakeMovementZigzaggy(RLVector* HuntDirection, RLValue zigzaggyness);
int MoveInASpiral(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, RLValue spiralamount);
int MoveInRange(RLVector* HuntDirection, int urgency, int backupok);
void MoveInAStar(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int startagain);
int FlyFromBehind(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int urgency);
int FlyInRange(RLVector* HuntDirection, RLVector* RobotDirection, RLVector* MonstPlace, RLValue tightness, int avoidbuildings);

void RobotMoveAndShootNormally(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition);
int RobotMoveInRange(RLVector* HuntDirection, RLVector* RobotDirection, int urgency);

int PickOffensiveTactic();
void MarkOffensiveTacticStart(int tactic);
void MarkOffensiveTacticComplete();
void MarkOffensiveTacticAborted();
void MarkOffensiveTacticEvaluate();


#define Normally 1
#define ZigZaggy 2
#define FromBehind 3
#define FromHighGround 4
#define FromLowGround 5
#define FromLevelGround 6
#define InASpiral 7
#define InAStar 8
#define FlyingNormally 9
#define FlyingZigZaggy 10
#define FlyingFromBehind 11
#define BodySlam 12

extern char monstername[7][16];


void GetRobotAEInfo(FILE *input, int monsterid, int submonsterid)
{
   char decision[1];
   char movename[64];
   char dumstring[256];
   while (!feof(input))
   {
      fscanf(input," %1s",decision);
      
      switch(*decision)
      {
         case '{':
            fscanf(input,"%[^}]",dumstring);
            fscanf(input,"}");
         break;
         case '!':
            fscanf(input," %s",movename);
            if(!stricmp("JoyFromDestruction",movename))
            {
               fscanf(input," %f",&(JoyFromDestruction[monsterid][submonsterid]));
            }
            else if(!stricmp("JoyFromWinning",movename))
            {
               fscanf(input," %f",&(JoyFromWinning[monsterid][submonsterid]));
            }
            else if(!stricmp("RageDiminshment",movename))
            {
               fscanf(input," %f",&(RageDiminshment[monsterid][submonsterid]));
            }
            else if(!stricmp("BoredomWithoutRage",movename))
            {
               fscanf(input," %f",&(BoredomWithoutRage[monsterid][submonsterid]));
            }
            else if(!stricmp("FearDiminishment",movename))
            {
               fscanf(input," %f",&(FearDiminishment[monsterid][submonsterid]));
            }
            else if(!stricmp("BoredomWithoutFear",movename))
            {
               fscanf(input," %f",&(BoredomWithoutFear[monsterid][submonsterid]));
            }
            else if(!stricmp("BoredomFarFromRobot",movename))
            {
               fscanf(input," %f",&(BoredomFarFromRobot[monsterid][submonsterid]));
            }
            else if(!stricmp("FearFromAttack",movename))
            {
               fscanf(input," %f",&(FearFromAttack[monsterid][submonsterid]));
            }
            else if(!stricmp("JoyForHapppyHappyJoyJoy",movename))
            {
               fscanf(input," %f",&(JoyForHapppyHappyJoyJoy[monsterid][submonsterid]));
            }
            else if(!stricmp("Aggressiveness",movename))
            {
               fscanf(input," %f",&(Aggressiveness[monsterid][submonsterid]));
            }
            else if(!stricmp("Cowardliness",movename))
            {
               fscanf(input," %f",&(Cowardliness[monsterid][submonsterid]));
            }
            else if(!stricmp("Conservativeness",movename))
            {
               fscanf(input," %f",&(Conservativeness[monsterid][submonsterid]));
            }
            else if(!stricmp("Frustration",movename))
            {
               fscanf(input," %f",&(Frustration[monsterid][submonsterid]));
            }
            else
            {
    // Unknown keyword
               fgets(dumstring,256,input);
            }
         break;
         default:
            if(feof(input))
            {
	// Reached an EOF\n");
               return;
            }
	// Unknown symbol
            fgets(dumstring,256,input);
         break;
      }
   }
}                                                          



void WriteAIAEInfo(FILE *file, int monsterid, int submonsterid)
{
	char submonstername[3][7] = { "ALPHA", "BETA", "GAMMA" };

	fprintf(file, "{Artificial Intelligence/Emotion data files for %s (%s)}\n",
		monstername[monsterid], submonstername[submonsterid]);
	fprintf(file, "{This file contains data relating to its emotional profile.}\n\n");
	fprintf(file, "{Note:  'per frame' means 'per 1/30th of a second'}\n\n");
	
	fprintf(file, "\n{Joy value per frame from fraction of population destroyed}\n");
	fprintf(file, "!JoyFromDestruction      %f\n", JoyFromDestruction[monsterid][submonsterid]);
	
	fprintf(file, "\n{Joy value per frame from difference of monster's life and Robot's life}\n");
	fprintf(file, "!JoyFromWinning          %f\n", JoyFromWinning[monsterid][submonsterid]);
	
	fprintf(file, "\n{Amount that rage decreases per frame}\n");
	fprintf(file, "!RageDiminshment         %f\n", RageDiminshment[monsterid][submonsterid]);
	
	fprintf(file, "\n{Amount that boredom increases per frame in the absence of rage}\n");
	fprintf(file, "!BoredomWithoutRage      %f\n", BoredomWithoutRage[monsterid][submonsterid]);
	
	fprintf(file, "\n{Amount that fear decreases per frame}\n");
	fprintf(file, "!FearDiminishment        %f\n", FearDiminishment[monsterid][submonsterid]);
	
	fprintf(file, "\n{Amount that boredom increases per frame in the absence of fear}\n");
	fprintf(file, "!BoredomWithoutFear      %f\n", BoredomWithoutFear[monsterid][submonsterid]);
	
	fprintf(file, "\n{Amount that boredom increases per frame based on distance from Robot}\n");
	fprintf(file, "!BoredomFarFromRobot      %f\n", BoredomFarFromRobot[monsterid][submonsterid]);
	
	fprintf(file, "\n{Amount that fear increases per frame while Robot is in attack animation}\n");
	fprintf(file, "!FearFromAttack          %f\n", FearFromAttack[monsterid][submonsterid]);
	
	fprintf(file, "\n{Amount of joy required to trigger taunt animation}\n");
	fprintf(file, "!JoyForHapppyHappyJoyJoy %f\n", JoyForHapppyHappyJoyJoy[monsterid][submonsterid]);
	
	fprintf(file, "\n{Base value to encourage the desire to hunt the Robot}\n");
	fprintf(file, "!Aggressiveness          %f\n", Aggressiveness[monsterid][submonsterid]);
	
	fprintf(file, "\n{Base value to encourage the desire to evade the Robot}\n");
	fprintf(file, "!Cowardliness            %f\n", Cowardliness[monsterid][submonsterid]);
	
	fprintf(file, "\n{Base value to encourage the desire to eat buildings}\n");
	fprintf(file, "!Conservativeness        %f\n", Conservativeness[monsterid][submonsterid]);
	
	fprintf(file, "\n{Amount that rage is increased if Robot destroys building that monster had targeted}\n");
	fprintf(file, "!Frustration             %f\n", Frustration[monsterid][submonsterid]);
}



extern char DatPath[];


void
CreateAIAEDatFiles(void)
{
	int i, j;
	char datname[256];
	FILE* file;

	for (i=0;i<7;i++) {
		for (j=0;j<3;j++) {
			sprintf(datname,"%s\\monae%d%d.dat",DatPath,i,j);
			file=fopen(datname,"wt");
			if(file)
			  WriteAIAEInfo(file, i, j);
			if(file)
			  fclose(file);
		}
	}
}

void
ReadAIAEDatFiles(void)
{
	int i, j;
	char datname[256];
	FILE* file;

	for (i=0;i<7;i++) {
		for (j=0;j<3;j++) {
			sprintf(datname,"%s\\monae%d%d.dat",DatPath,i,j);
			file=fopen(datname,"rt");
			if(file)
			  GetRobotAEInfo(file, i, j);
			if(file)
			  fclose(file);
		}
	}
}

void InitAE()
{
	int i;

   if (!Aiaeinitted)
   {
	   for (i=0;i<20;i++) 
	   {
		   OffensiveTacticAttempts[i]=1;
		   OffensiveTacticSuccesses[i]=RLVal(1);
	   }
   }
	//CreateAIAEDatFiles();
	ReadAIAEDatFiles();
   Aiaeinitted = TRUE;
}


void cogitate(void)
{
	RLVector MonsterPosition,RobotPosition;
   RLVector HuntDirection;
   //RLValue Distance,DotProduct,CrossProduct;
   RLFrame Scene=RLFrameGetScene(Robotframe);
   	//extern int *InputIntPtr;
   extern volatile long int InputInt2;

   (*InputIntPtr2) = 0;

   //if (((FramesSinceLastInput>MinMoveFrames) && (monthink))
   //      ||(monthink>1))
   //if(FramesSinceLastInput>MinMoveFrames)
   if  (((FramesSinceLastInput>MinMoveFrames) && (monthink==1)) || 
   		((FramesSinceLastInput>MinMoveFrames/4) && (monthink==2)) ||
   		((FramesSinceLastInput>0) && (monthink==3)))
   {
      //if((*InputIntPtr2) && (*InputIntPtr2!=COMMANDForward))
      //{
      //   FramesSinceLastInput=0;
      //   return;
      //}
      //if(MonsterMovementState!=MonsterKnockBackward && MonsterMovementState!=MonsterStopped && MonsterMovementState!=MonsterAirborne)
      if(MonsterMovementState!=MonsterKnockBackward)
      {
         RLFrameGetPosition(Robotframe,Scene,&RobotPosition);
         RLFrameGetPosition(monstframe,Scene,&MonsterPosition);
		 ChooseStrategy(&HuntDirection, &RobotPosition, &MonsterPosition);
		 if (OffensiveTacticMarkedCountDown > RLVal(0)) OffensiveTacticMarkedCountDown-=DiffFrame;
		 else if (OffensiveTacticMarked) MarkOffensiveTacticEvaluate();
		 //if ((*InputIntPtr2)==0) 
		 //{
		 //	(*InputIntPtr2)=COMMANDForward;
			//MonsterGoal = -1;
		//}
      }
	  else
	  {
		 if (OffensiveTacticMarked) MarkOffensiveTacticAborted();
	  }
      //Otherwise it's impossible to move, so do nothing.
   }
   else
   {
      FramesSinceLastInput++;
   }
}

void
Robotruminate()
{
	RLVector MonsterPosition,RobotPosition;
   RLVector HuntDirection;
   //RLValue Distance,DotProduct,CrossProduct;
   RLFrame Scene=RLFrameGetScene(Robotframe);
   	//extern int *InputIntPtr;
	//extern volatile long int InputInt;

	if ((monthink)) {
		MinDistance=RLVal(0.1);
		FiringRange = RLVal(6.5);
		RLFrameGetPosition(Robotframe,Scene,&RobotPosition);
		RLFrameGetPosition(monstframe,Scene,&MonsterPosition);
		HuntDirection.x=MonsterPosition.x-RobotPosition.x;
		HuntDirection.z=MonsterPosition.z-RobotPosition.z;
		HuntDirection.y=RLVal(0);
		RobotMoveAndShootNormally(&HuntDirection, &MonsterPosition, &RobotPosition);
		return;
	}
}

RLValue MonsterDesire;
RLValue HuntDesire, MissionDesire, EvadeDesire, GenericDesire, DefendDesire;
RLValue Rage = RLVal(0);
RLValue Fear = RLVal(0);
RLValue Boredom = RLVal(0);
RLValue Joy = RLVal(0);
RLValue Dist2, InvDist2;

void ChooseStrategy(RLVector* HuntDirection, RLVector* RobotPosition, RLVector *MonsterPosition)
{
	int oldmonstergoal, i;
	RLValue LifeBalance, EngyBalance, Desire, TestDesire;
	RLValue BuildingGoodness, TestBuildingGoodness;
	static unsigned int BuildingRadius = 16;
	extern int MonsterAnimationState;
	extern RLVector monstorigin;
	extern long int PrePopulation;
	extern long int Population;

	oldmonstergoal = MonsterGoal;
	
	HuntDirection->x=RobotPosition->x - MonsterPosition->x;
	HuntDirection->z=RobotPosition->z - MonsterPosition->z;
	HuntDirection->y=RLVal(0);
	Dist2 = RLVectorDotProduct(HuntDirection, HuntDirection);
	InvDist2 = RLDivide(RLVal(350), Dist2);
	LifeBalance = RLVal(2*MnstLife - RobotLife);
	EngyBalance = RLDivide(RLVal(MnstEngy - 65536.0), RLVal(655.36));
	//EngyBalance = RLDivide(RLVal(MnstEngy - RobotEngy), RLVal(655.36));

	// Evaluate Monster's emotional state
	if (MonsterAnimationState != MonsterTaunt2)
	   Joy += 
		   RLMultiply3(DiffFrame, JoyFromDestruction[GameStates.CurrentLevel][GameStates.CurrentSubmonster], RLDivide(PrePopulation - Population, PrePopulation)) +
		   RLMultiply3(DiffFrame, JoyFromWinning[GameStates.CurrentLevel][GameStates.CurrentSubmonster], LifeBalance-RLVal(5+MnstLife));
	if (Rage > RLVal(0.5)) {
		Rage -= RLMultiply(DiffFrame, RageDiminshment[GameStates.CurrentLevel][GameStates.CurrentSubmonster]);
		Joy -= Rage;
	} else 
		Boredom += RLMultiply(DiffFrame, BoredomWithoutRage[GameStates.CurrentLevel][GameStates.CurrentSubmonster]);


	Boredom += RLMultiply3(DiffFrame, RLDivide(Dist2, RLVal(65536.0)), BoredomFarFromRobot[7][3]);

	if ((MonsterPosition->x < landbox.min.x) || (MonsterPosition->x > landbox.max.x) || (MonsterPosition->z < landbox.min.z) || (MonsterPosition->z > landbox.max.z))
	{	// Drastic measures if monster's near the edge of the world.
		//Boredom = Joy = RLVal(0);
		//Rage = RLMultiply(Rage, RLVal(10));
		Fear = RLVal(0);
		BuildingRadius = 256;
	}
	
	if (RobotAnimationState==RobotHighAttack1 ||
		RobotAnimationState==RobotMediumAttack1||
		RobotAnimationState==RobotMediumAttack2||
		RobotAnimationState==RobotLowAttack2||
		RobotAnimationState==RobotSuperKick2||
		RobotAnimationState==RobotSpecialAttack3||
		RobotAnimationState==RobotJumpAttack1||
		RobotAnimationState==RobotJumpAttack2)
		Fear += RLMultiply3(InvDist2, DiffFrame, (FearFromAttack[GameStates.CurrentLevel][GameStates.CurrentSubmonster]));	// EMERGENCY!!! 
	else 
	{
		if (Fear > RLVal(0.5)) 
		{
			//Fear -= Boredom;
			if ((MnstLife > RobotLife) && (MnstEngy > RobotEngy))
				Fear -= RLMultiply3(RLVal(5), DiffFrame, FearDiminishment[GameStates.CurrentLevel][GameStates.CurrentSubmonster]);
			else
				Fear -= RLMultiply(DiffFrame, FearDiminishment[GameStates.CurrentLevel][GameStates.CurrentSubmonster]);
		}
		else 
			Boredom += RLMultiply(DiffFrame, BoredomWithoutFear[GameStates.CurrentLevel][GameStates.CurrentSubmonster]);
		
		if (RobotEngy<RLVal(0)) Fear = RLVal(0);
	}

		if (RobotAnimationState==RobotTaunt1) {
			Rage += Joy;
			Fear += RLMultiply(RLVal(0.1), (Boredom - Rage));
		}
			

	if (Joy > JoyForHapppyHappyJoyJoy[GameStates.CurrentLevel][GameStates.CurrentSubmonster]) {
		if (MonsterAnimationState == MonsterPause1) {
			(*InputIntPtr2)=COMMANDWeakShift|COMMANDMediumShift|COMMANDStrongShift;
			//Joy -= JoyForHapppyHappyJoyJoy[GameStates.CurrentLevel][GameStates.CurrentSubmonster];
         Joy = D3DVAL(0.0);
		} else {
			(*InputIntPtr2)=0;
		}
		return;
	} else if (Joy < RLVal(0)) Joy = RLVal(0);
	

	// Hunt the Robot?  ( 0 )
	Desire =  //200 +  //For testing purposes, I pissed off the monster..
		Rage +										// more if monster angry
		((oldmonstergoal==HuntRobot) ? -Boredom : RLVal(0)) + // less if monster bored with this strategy
		RLMultiply(RLVal(0.2), Boredom) +			// more if monster bored
		RLMultiply(RLVal(0.1), Joy) +				// more if monster happy
		Aggressiveness[GameStates.CurrentLevel][GameStates.CurrentSubmonster] +			// base desire
		RLVal(BuildingRadius/8) +					// more if generic buildings are scarce
		RLMultiply3(RLVal(0.125), LifeBalance, InvDist2) + 		// more if monster healthy
		RLMultiply3(RLVal(0.025), EngyBalance, InvDist2);		// more if monster vital
	HuntDesire = Desire;
	MonsterGoal = HuntRobot;

	// Evade the Robot?	( 3 )
	TestDesire =
		((oldmonstergoal==EvadeRobot) ? -Boredom : RLVal(0)) + 	// less if monster bored with this strategy
		(-Cowardliness[GameStates.CurrentLevel][GameStates.CurrentSubmonster]) +					// base dislike of running away
		-RLVal(BuildingRadius/8) +								// less if generic buildings are scarce
		RLMultiply3(RLVal(0.25), InvDist2, -LifeBalance); 		// more if monster unhealthy and Robot nearby
		//RLMultiply3(RLVal(0.5), InvDist2, EngyBalance);		// more if monster has energy and Robot nearby

	EvadeDesire = TestDesire;
	if (TestDesire > Desire) {
		MonsterGoal = EvadeRobot;
		Desire = TestDesire;
	}


	// Defend against the Robot?	( 4 )
	TestDesire =
		Fear +													// 
		((oldmonstergoal==DefendAgainstRobot) ? -Boredom : RLVal(0)) + 	// less if monster bored with this strategy
		//(-Aggressiveness[level][submonster]) +											// base dislike of running away
		//RLMultiply3(RLVal(0.5), -InvDist2, LifeBalance); 		// more if monster unhealthy and Robot nearby
		//RLMultiply3(RLVal(0.5), InvDist2, EngyBalance);		// more if monster has energy and Robot nearby
		RLVal(0);

	DefendDesire = TestDesire;
	if (TestDesire > Desire) {
		MonsterGoal = DefendAgainstRobot;
		Desire = TestDesire;
	}


	// Hunt the mission target building?  ( 1 )
	TestDesire = 
		RLVal(5.0) +								// base desire
		((oldmonstergoal==HuntMissionBuilding) ? -Boredom : RLVal(0)) + // less if monster bored with this strategy
		RLMultiply(RLVal(0.1), Boredom) +			// more if monster bored
		RLMultiply(RLVal(0.2), Joy) +				// more if monster happy
		RLVal(5.0) +								// base desire
		RLVal(BuildingRadius/8) +					// more if generic buildings are scarce
		RLMultiply(RLVal(0.25), LifeBalance);  		// more if monster healthy
		//RLMultiply(RLVal(0.25), EngyBalance);		// more if monster vital
	MissionDesire = TestDesire;

	if ((TestDesire > Desire) &&
       (missiontarget.building_ptr[GameStates.CurrentSubmonster]->cur_damage < missiontarget.building_ptr[GameStates.CurrentSubmonster]->max_damage))
    {
		MonsterGoal = HuntMissionBuilding;
		Desire = TestDesire;
	}

	// Hunt any old building?  ( 2 )
	TestDesire =
		Conservativeness[GameStates.CurrentLevel][GameStates.CurrentSubmonster] +
		((oldmonstergoal==HuntAnyBuilding) ? -Boredom : RLVal(0)) + // less if monster bored with this strategy
		RLMultiply(RLVal(-0.025), LifeBalance) +		// slightly more if monster lacks life
		RLMultiply(RLVal(-0.25), EngyBalance);		// more if monster lacks energy
	if (RLVal(MnstEngy/655.36) < 50) 				// even more if monster low on energy
		TestDesire += RLMultiply(RLVal(3.0), RLVal(50.0-(MnstEngy/655.36)));
	if (RLVal(MnstEngy/655.36) < 10) 				// even more if monster low on energy
		TestDesire += RLMultiply(RLVal(35.0), RLVal(10.0-(MnstEngy/655.36)));
	if ((RLVal(MnstLife) < 50)) 					// even more if monster needs to get life back
		TestDesire += RLMultiply(RLVal(1.0), RLVal(50.0-MnstLife));
	//TestDesire += RLMultiply(RLDivide(RLVal(MnstEngy), RLVal(65536.0)), RLVal(50.0-MnstLife));

	GenericDesire = TestDesire;
	if ((TestDesire > Desire)) {
		if ((oldmonstergoal == HuntAnyBuilding) && (arbitrarytarget.building_ptr[targetnum]->cur_damage < arbitrarytarget.building_ptr[targetnum]->max_damage))  {
			MonsterGoal = HuntAnyBuilding;
			Desire = TestDesire;
		} else {
			if (oldmonstergoal == HuntAnyBuilding) 	// Monster was hunting a building, but it's gone now...
				Rage += RLMultiply(InvDist2, Frustration[GameStates.CurrentLevel][GameStates.CurrentSubmonster]);					// ...so monster gets mad.
			// search for a new generic victim building
			GetBuildingsInArea(&arbitrarytarget, MonsterPosition->x - BuildingRadius, MonsterPosition->z - BuildingRadius, MonsterPosition->x + BuildingRadius, MonsterPosition->z + BuildingRadius);
			if (arbitrarytarget.count) {
				BuildingGoodness = RLVal(0);
				targetnum = arbitrarytarget.count;
				for (i=0;(i<arbitrarytarget.count);i++) {
					if ((arbitrarytarget.building_ptr[i]->building_num == -1) && (arbitrarytarget.building_ptr[i]->cur_damage < arbitrarytarget.building_ptr[i]->max_damage)) 
						TestBuildingGoodness = 
							arbitrarytarget.building_ptr[i]->power_mon_amount /				// BuildingGoodness is proportional to power received from buildings.
								((MonsterPosition->x - arbitrarytarget.building_ptr[i]->x_world) *	// BuildingGoodness is inversely proportional to square of distance from building.
								 (MonsterPosition->x - arbitrarytarget.building_ptr[i]->x_world) +
								 (MonsterPosition->z - arbitrarytarget.building_ptr[i]->z_world) *
								 (MonsterPosition->z - arbitrarytarget.building_ptr[i]->z_world));
					else TestBuildingGoodness = RLVal(0);
					if (TestBuildingGoodness > BuildingGoodness) {
						targetnum = i;
						BuildingGoodness = TestBuildingGoodness;
					}
				}
				if (targetnum < arbitrarytarget.count) {
					MonsterGoal = HuntAnyBuilding;
					Desire = TestDesire;
					BuildingRadius >>= 1;
				} else if (BuildingRadius < 257) BuildingRadius <<= 1;
			} else if (BuildingRadius < 257) BuildingRadius <<= 1;	
		}
	}


	MonsterDesire = Desire;
	if (MonsterGoal != oldmonstergoal) 
	{
		if ((OffensiveTacticMarked) && (oldmonstergoal == HuntRobot)) MarkOffensiveTacticAborted();

		Boredom -= RLMultiply(DiffFrame, RLVal(3.0));
	}
	if (Boredom < RLVal(0.0)) Boredom = RLVal(0.0);

	switch (MonsterGoal) {
		case HuntRobot:
			EnactOffensiveTactic(HuntDirection, RobotPosition, MonsterPosition, (oldmonstergoal != MonsterGoal));
			break;

		case HuntMissionBuilding:
			MinDistance=RLVal(0.1);
			FiringRange = RLVal(0.0);
			HuntDirection->x = missiontarget.building_ptr[GameStates.CurrentSubmonster]->x_world-LANDXCENTER - MonsterPosition->x;
			HuntDirection->z = missiontarget.building_ptr[GameStates.CurrentSubmonster]->z_world-LANDZCENTER - MonsterPosition->z;
			{
				RLVector ToRobot;
				RLValue CrossProduct, Robotmissiondot;

				ToRobot.x = RobotPosition->x - MonsterPosition->x;
				ToRobot.z = RobotPosition->z - MonsterPosition->z;
				ToRobot.y = RLVal(0);
				RLVectorNormalise(&ToRobot);
				Robotmissiondot = RLDivide(RLVectorDotProduct(&ToRobot, HuntDirection), RLVectorModulus(HuntDirection));
				if (Robotmissiondot > RLVal(0.5))
				{
			         RLValue TargetDist2=RLVectorDotProduct(HuntDirection, HuntDirection);
			         CrossProduct=RLDivide((RLMultiply(HuntDirection->z,ToRobot.x) - RLMultiply(HuntDirection->x,ToRobot.z)),TargetDist2);
					 HuntDirection->x += RLMultiply(CrossProduct, -HuntDirection->z);
					 HuntDirection->z += RLMultiply(CrossProduct, HuntDirection->x);
				}
			}
			MoveAndShootNormally(HuntDirection, RobotPosition, MonsterPosition, 1, 1);
			if (MonsterGoal != oldmonstergoal) {
				char text[80];
				extern int Vmode;
				extern char monstername[7][16];
				extern char targetname[7][3][32];
				sprintf(text, "%s IS HEADING TOWARD THE %s", monstername[GameStates.CurrentLevel], targetname[GameStates.CurrentLevel][GameStates.CurrentSubmonster]);
				YBSetSubTitle2(Vmode, text, RGB(0, 0, 255));
			}

			break;
		case HuntAnyBuilding:
			MinDistance=RLVal(0.2);
			FiringRange = RLVal(0.0);
			HuntDirection->x = arbitrarytarget.building_ptr[targetnum]->x_world-LANDXCENTER - MonsterPosition->x;
			HuntDirection->z = arbitrarytarget.building_ptr[targetnum]->z_world-LANDZCENTER - MonsterPosition->z;
			MoveAndShootNormally(HuntDirection, RobotPosition, MonsterPosition, ((MnstLife>25) ? 1 : 2), 1);
			break;

		case EvadeRobot:
			EnactEvasiveTactic(HuntDirection, RobotPosition, MonsterPosition, oldmonstergoal != MonsterGoal);
			break;
		case DefendAgainstRobot:
			EnactDefensiveTactic(HuntDirection, RobotPosition, MonsterPosition, oldmonstergoal != MonsterGoal);
	}

}

/*
void EnactOffensiveTactic(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int newtactic)
{
	static int tactic=0;

	switch (level) {
		case 0:
		case 1:
			MinDistance=RLVal(0.1);
			FiringRange = RLVal(6.5);
			//MoveAndShootFromBehind(HuntDirection, RobotPosition, MonsterPosition);
			if ((RobotEngy > 65536/2) && (submonster!=0)) {
				MakeMovementZigzaggy(HuntDirection, RLMultiply(RLVal(submonster), RLVal(0.5)));
				tactic = ZigZaggy;
			} else {
				tactic = Normally;
			}
				MoveAndShootNormally(HuntDirection, RobotPosition, MonsterPosition, 1);
			break;
		case 2:
			MinDistance=RLVal(0.1);
			FiringRange = RLVal(6.5);
			switch (submonster) {
				case 0:
					MoveAndShootFromLevelGround(HuntDirection, RobotPosition, MonsterPosition, 1);
					tactic = FromLevelGround;
					break;
				case 1:
					if (RobotPosition->y < MonsterPosition->y) {
						FiringRange = RLVal(7.0);
						MoveAndShootFromHighGround(HuntDirection, RobotPosition, MonsterPosition, 1);
						tactic = FromHighGround;
					} else {
						MoveAndShootFromLevelGround(HuntDirection, RobotPosition, MonsterPosition, 1);
						tactic = FromLevelGround;
					}
					break;
				case 2:
					if (RobotPosition->y > MonsterPosition->y - RLVal(1.0)) {
						FiringRange = RLVal(4.0);
						MoveAndShootFromLowGround(HuntDirection, RobotPosition, MonsterPosition, 1);
						tactic = FromLowGround;
					} else if (RobotPosition->y < MonsterPosition->y + RLVal(1.0)) {
						FiringRange = RLVal(7.0);
						MoveAndShootFromHighGround(HuntDirection, RobotPosition, MonsterPosition, 1);
						tactic = FromHighGround;
					} else {
						MoveAndShootFromLevelGround(HuntDirection, RobotPosition, MonsterPosition, 1);
						tactic = FromLevelGround;
					}
					break;
			}
			break;
		case 3:
			MinDistance=RLVal(0.1);
			FiringRange = RLVal(6.5);
			if ((tactic == ZigZaggy) || (tactic == Normally)) {
				if (RobotEngy > 65536/2) {
					//MoveAndShootZigzaggy(HuntDirection, RobotPosition, MonsterPosition, 2);
					MakeMovementZigzaggy(HuntDirection, RLVal(1.2));
					tactic = ZigZaggy;
					if (rand()&0xff == 0) tactic = InASpiral;
				} else {
					tactic = Normally;
				}
				MoveAndShootNormally(HuntDirection, RobotPosition, MonsterPosition, 2);
			} else {
				if ((RobotEngy > 65536/2)) {
					tactic = InASpiral;
					if (MoveInASpiral(HuntDirection, RobotPosition, MonsterPosition, (RLDivide(RLVal(1), InvDist2) < RLVal(0.8) ? RLDivide(RLVal(1), InvDist2) : RLVal(0.8)))) 
						tactic = Normally;
					if (rand()&0xff == 0) tactic = ZigZaggy;
					if ((fabs(MonsterPosition->x) > RLVal(120)) || (fabs(MonsterPosition->z) > RLVal(120)))
						tactic = 0;
				} else {
					MoveAndShootFromBehind(HuntDirection, RobotPosition, MonsterPosition, 1);
					tactic = FromBehind;
				}
			}
			break;
		case 4:
			MinDistance=RLVal(0.1);
			FiringRange = RLVal(6.5);
			//MoveAndShootFromBehind(HuntDirection, RobotPosition, MonsterPosition);
			//if (newtactic) tactic = 0;
			//if (tactic==0) tactic = rand()%4 + 1;

			if ((tactic == Normally) || (tactic == Normally)) {
				if (RobotEngy > 65536/2) {
					MoveAndShootZigzaggy(HuntDirection, RobotPosition, MonsterPosition, 2);
					tactic = ZigZaggy;
					if (rand()&0xff == 0) tactic = InAStar;
				} else {
					MoveAndShootNormally(HuntDirection, RobotPosition, MonsterPosition, 2);
					tactic = Normally;
				}
			} 
			if ((tactic == InAStar) || (tactic == FromBehind)) {
				if ((RobotEngy > 65536/2)) {
					tactic = InAStar;
					FiringRange = RLVal(4.0);
					MoveInAStar(HuntDirection, RobotPosition, MonsterPosition, newtactic); 
					if ((fabs(MonsterPosition->x) > RLVal(120)) || (fabs(MonsterPosition->z) > RLVal(120)))
						tactic = 0;
					//if (rand()&0xff == 0) tactic = 1;
				} else {
					MoveAndShootFromBehind(HuntDirection, RobotPosition, MonsterPosition, 1);
					tactic = FromBehind;
				}
			}
			break;
		case 5:					// Nealloth
			{
				RLVector RobotDirection;
				//if (newtactic) tactic = 0;
				//if (tactic==0) tactic = rand()%6 + 1;

				RobotDirection.x = MonsterPosition->x - RobotPosition->x;
				RobotDirection.y = MonsterPosition->y - RobotPosition->y;
				RobotDirection.z = MonsterPosition->z - RobotPosition->z;
				if ((tactic == Normally) || (tactic == ZigZaggy) || (tactic == FlyingNormally)) {
					FiringRange = RLVal(10);
					MinDistance = RLVal(0.1);
					tactic = FlyingNormally;

					HuntDirection->y = RLVal(12.0) - MonsterPosition->y;
					if (tactic == ZigZaggy) {
						MakeMovementZigzaggy(HuntDirection, RLDivide((RLVal(100)-MnstLife), RLVal(100)));
						tactic = ZigZaggy;
					}
					if (FlyInRange(HuntDirection, &RobotDirection, MonsterPosition, RLVal(1.5), 0)) 
						tactic = Normally;
					if (tactic == Normally) {
						FiringRange = RLVal(4.0);
						MoveAndShootNormally(HuntDirection, RobotPosition, MonsterPosition, 1);
					}
				}
				if ((RobotEngy > 65536/2)) {
					tactic = InASpiral;
					if (MoveInASpiral(HuntDirection, RobotPosition, MonsterPosition, (RLDivide(RLVal(1), InvDist2) < RLVal(0.8) ? RLDivide(RLVal(1), InvDist2) : RLVal(0.8)))) 
						tactic = Normally;
					if (rand()&0xff == 0) tactic = FlyingNormally;
					if ((fabs(MonsterPosition->x) > RLVal(120)) || (fabs(MonsterPosition->z) > RLVal(120)))
						tactic = 0;
				} else {
					MoveAndShootFromBehind(HuntDirection, RobotPosition, MonsterPosition, 1);
					tactic = FromBehind;
				}
				if ((tactic == ZigZaggy) || (tactic == Normally)) {
					if (RobotEngy > 65536/2) {
						MoveAndShootZigzaggy(HuntDirection, RobotPosition, MonsterPosition, 1);
						tactic = ZigZaggy;
						if (rand()&0xff == 0) tactic = InASpiral;
					} else {
						MoveAndShootNormally(HuntDirection, RobotPosition, MonsterPosition, 1);
						tactic = Normally;
					}
				} 
			}
			break;
		case 6:
			{
				RLVector RobotDirection;
				if (newtactic) tactic = 0;
				if (tactic==0) tactic = rand()%8 + 1;

				RobotDirection.x = MonsterPosition->x - RobotPosition->x;
				RobotDirection.y = MonsterPosition->y - RobotPosition->y;
				RobotDirection.z = MonsterPosition->z - RobotPosition->z;
				if ((tactic == FlyingNormally) || (tactic == FlyingZigZaggy)) {
					FiringRange = RLVal(10);
					MinDistance = RLVal(0.1);
					tactic = FlyingNormally;

					HuntDirection->y = RLVal(12.0) - MonsterPosition->y;
					if (tactic == FlyingZigZaggy) {
						MakeMovementZigzaggy(HuntDirection, RLDivide((RLVal(100)-MnstLife), RLVal(100)));
						tactic = FlyingZigZaggy;
					}
					if (FlyInRange(HuntDirection, &RobotDirection, MonsterPosition, RLVal(1.5), 0)) {
						FiringRange = RLVal(4.0);
						MoveAndShootNormally(HuntDirection, RobotPosition, MonsterPosition, 1);
						tactic = FlyingNormally;
					}
				}
				if ((tactic == InAStar) || (tactic == FromBehind)) {
					if ((RobotEngy > 65536/2)) {
						tactic = InAStar;
						FiringRange = RLVal(4.0);
						MoveInAStar(HuntDirection, RobotPosition, MonsterPosition, newtactic); 
						if ((fabs(MonsterPosition->x) > RLVal(120)) || (fabs(MonsterPosition->z) > RLVal(120)))
							tactic = 0;
						//if (rand()&0xff == 0) tactic = 1;
					} else {
						MoveAndShootFromBehind(HuntDirection, RobotPosition, MonsterPosition, 1);
						tactic = FromBehind;
					}
				}
				if ((tactic == ZigZaggy) || (tactic == Normally)) {
					if (RobotEngy > 65536/2) {
						MoveAndShootZigzaggy(HuntDirection, RobotPosition, MonsterPosition, 1);
						tactic = ZigZaggy;
						if (rand()&0xff == 0) tactic = FromBehind;
					} else {
						MoveAndShootNormally(HuntDirection, RobotPosition, MonsterPosition, 1);
						tactic = Normally;
					}
				} 
				if ((tactic == InASpiral) || (tactic == FromBehind)) {
					if ((RobotEngy > 65536/2)) {
						tactic = InASpiral;
						if (MoveInASpiral(HuntDirection, RobotPosition, MonsterPosition, RLVal(0.8))) 
							tactic = Normally;
						if (rand()&0xff == 0) tactic = InAStar;
						if ((fabs(MonsterPosition->x) > RLVal(120)) || (fabs(MonsterPosition->z) > RLVal(120)))
							tactic = 0;
					} else {
						MoveAndShootFromBehind(HuntDirection, RobotPosition, MonsterPosition, 1);
						tactic = FromBehind;
					}
				}
			}
			break;
	}
}
*/


BOOL IsOffensiveTacticOK[7][3][13] =
{
	{	
		{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },		// Goofy robot Alpha
		{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },		// Goofy robot Beta
		{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }			// Goofy robot Gamma
	},
	{
		{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },		// Roggosh Alpha
		{ 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	},
	{
		{ 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },		// Kothos Alpha
		{ 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 }
	},
	{
		{ 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },		// Tolgo Alpha
		{ 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 }
	},
	{
		{ 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },		// Shagtoq Alpha
		{ 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0 }
	},									 
	{
		{ 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0 },		// Nealloth Alpha
		{ 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0 },
		{ 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1 }
	},
	{
		{ 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1 },		// Gaingris Alpha
		{ 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
		{ 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1 }
	}
};

RLValue MinDistances[7][3] =
{
	{ 	// Trainer
		RLVal(0.1),
		RLVal(0.1), 
		RLVal(0.1)
	},
	{ 	// Roggosh
		RLVal(0.1),		// Zapper
		RLVal(0.3), 	// Zapper whip
		RLVal(0.3)		// Rolling attack
	},
	{ 	// Kothos
		RLVal(0.1),		// Zapper
		RLVal(0.1), 	// Jumping zap
		RLVal(0.1)		// Snowball
	},
	{ 	// Tolgo
		RLVal(0.1),		// Zapper 
		RLVal(0.1), 	// Wide Zapper
		RLVal(0.4)		// Dorky punches
	},
	{ 	// Shagtoq
		RLVal(0.1),		// Zapper
		RLVal(1.0),		// Ground lightening 
		RLVal(0.1)		// Puffy Zapper
	},
	{ 	// Nealloth
		RLVal(0.1),		// Zapper
		RLVal(0.1), 	// Sonic smoke rings
		RLVal(0.1)		// Flying Zapper
	},
	{ 	// Gaingris
		RLVal(0.1),		// Zapper
		RLVal(1.0),		// Nuke 
		RLVal(0.1)		// Multizapper
	}
};

RLValue FiringRanges[7][3] =
{
	{ 	// Trainer
		RLVal(7.0),
		RLVal(7.0), 
		RLVal(9.0)
	},
	{ 	// Roggosh
		RLVal(7.0),		// Zapper
		RLVal(7.0), 	// Zapper whip
		RLVal(10.0)		// Rolling attack
	},
	{ 	// Kothos
		RLVal(7.0),		// Zapper
		RLVal(3.0), 	// Jumping zap
		RLVal(10.0)		// Snowball
	},
	{ 	// Tolgo
		RLVal(7.0),		// Zapper 
		RLVal(7.0), 	// Wide Zapper
		RLVal(2.0)		// Dorky punches
	},
	{ 	// Shagtoq
		RLVal(7.0),		// Zapper
		RLVal(256.0),	// Ground lightening 
		RLVal(8.0)		// Puffy Zapper
	},
	{ 	// Nealloth
		RLVal(7.0),		// Zapper
		RLVal(9.0), 	// Sonic smoke rings
		RLVal(10.0)		// Flying Zapper
	},
	{ 	// Gaingris
		RLVal(7.0),		// Zapper
		RLVal(30.0),	// Nuke 
		RLVal(7.0)		// Multizapper
	}
};

int PickOffensiveTactic()
{
	//char tmp[80];
	int i, tactic=0;
   float diceroll = D3DVAL(0.0);
	
   /*
	while ((!IsOffensiveTacticOK[GameStates.CurrentLevel][GameStates.CurrentSubmonster][tactic]) || 
         (diceroll < (OffensiveTacticSuccesses[tactic]/D3DVAL(OffensiveTacticAttempts[tactic]))))
   {
      tactic=rand()%13;
      sprintf(tmp, "Trying attack #%d", tactic);
      BYDumpInfo(tmp);
      if (IsOffensiveTacticOK[GameStates.CurrentLevel][GameStates.CurrentSubmonster][tactic])
      {
         BYDumpInfo("It's allowed");
         sprintf(tmp, "%.2f for %d (%.3f)\n", 
            OffensiveTacticSuccesses[tactic],OffensiveTacticAttempts[tactic],
            OffensiveTacticSuccesses[tactic]/D3DVAL(OffensiveTacticAttempts[tactic]));
         BYDumpInfo(tmp);
         diceroll = (2.0*(rand()&0xffff)/65536.0);
         sprintf(tmp, "Dice roll is %.3f\n", diceroll);
         BYDumpInfo(tmp);
         if (diceroll > (OffensiveTacticSuccesses[tactic]/D3DVAL(OffensiveTacticAttempts[tactic])))
         {
            BYDumpInfo("++_++_++_ No attack chosen ++_++_++_");
            return 0;
         }
      }
   }
   sprintf(tmp, "+_+_+_+_+_+_ Picked attack #%d +_+_+_+_+_+_+_", tactic);
   BYDumpInfo(tmp);
	MarkOffensiveTacticStart(tactic);
	return tactic;
*/
   for (i=0;i<10;i++)
   {
      diceroll = ((rand()&0x1ffff)/65536.0);
      //sprintf(tmp, "Dice roll is %.3f\n", diceroll);
      //BYDumpInfo(tmp);

      tactic=rand()%13;
      //sprintf(tmp, "Trying attack #%d", tactic);
      //BYDumpInfo(tmp);

      if (IsOffensiveTacticOK[GameStates.CurrentLevel][GameStates.CurrentSubmonster][tactic])
      {
         //BYDumpInfo("It's allowed");
         //sprintf(tmp, "%.2f for %d (%.3f)\n", 
         //   OffensiveTacticSuccesses[tactic],OffensiveTacticAttempts[tactic],
         //   OffensiveTacticSuccesses[tactic]/D3DVAL(OffensiveTacticAttempts[tactic]));
         //BYDumpInfo(tmp);
         if (diceroll < (OffensiveTacticSuccesses[tactic]/D3DVAL(OffensiveTacticAttempts[tactic])))
         {
            //sprintf(tmp, "+_+_+_+_+_+_ Picked attack #%d +_+_+_+_+_+_+_", tactic);
            //BYDumpInfo(tmp);
	         MarkOffensiveTacticStart(tactic);
	         return tactic;
         }
         else
         {
            //BYDumpInfo("++_++_++_ No attack chosen (from bad dice roll) ++_++_++_");
            //return 0;
         }
      }
   }
   //BYDumpInfo("++_++_++_ No attack chosen (from too many tries) ++_++_++_");
   return 0;
}

void MarkOffensiveTacticStart(int tactic)
{
	if (OffensiveTacticMarkedFlag) MarkOffensiveTacticAborted();

	OffensiveTacticMarked = tactic;
	OffensiveTacticMarkedFlag = 1;
	OffensiveTacticMarkedCountDown = RLVal(30);
	OffensiveTacticAttempts[tactic]++;
	OffensiveTacticMarkedRobotLife = RobotLife;
	OffensiveTacticMarkedMnstLife = MnstLife;
}


void MarkOffensiveTacticComplete()
{
	OffensiveTacticMarkedCountDown = RLVal(15);
}

void MarkOffensiveTacticAborted()
{
	MarkOffensiveTacticEvaluate();
}

void MarkOffensiveTacticEvaluate()
{
	if (MnstLife >= OffensiveTacticMarkedMnstLife) OffensiveTacticSuccesses[OffensiveTacticMarked]+= RLVal(0.25);
	if (RobotLife < OffensiveTacticMarkedRobotLife) OffensiveTacticSuccesses[OffensiveTacticMarked]+= RLVal(0.75);
	OffensiveTacticMarked = 0;
	OffensiveTacticMarkedFlag = 0;
	OffensiveTacticMarkedCountDown = RLVal(0);
}

void EnactOffensiveTactic(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int newtactic)
{
	static int tactic=0;
	static int whichattack=-1;
	RLVector RobotDirection;
	int urgency;

	if ((MonsterAnimationState==MonsterSpecialAttack2) || (MonsterAnimationState==MonsterSpecialAttack1) || (MonsterAnimationState==MonsterHighAttack1)) return;
	
	if (newtactic || !IsOffensiveTacticOK[GameStates.CurrentLevel][GameStates.CurrentSubmonster][tactic]) 
      tactic = 0;

	MinDistance=RLVal(0.1);
	FiringRange = RLVal(10.0);
	HuntDirection->x = RobotPosition->x - MonsterPosition->x;
	HuntDirection->y = RobotPosition->y - MonsterPosition->y;
	HuntDirection->z = RobotPosition->z - MonsterPosition->z;

	if (((MnstEngy>RLVal(0.75*65536)) && (MnstLife>RLVal(75))) || 
		((Joy > RLVal(0.25)*JoyForHapppyHappyJoyJoy[GameStates.CurrentLevel][GameStates.CurrentSubmonster]) && (InvDist2>RLVal(1))))
			urgency = 2;
	else
			urgency = 1;

	if (tactic==0) 
	{				// no tactic
		tactic = PickOffensiveTactic();
	}
	switch (tactic) 
	{
      case 0:
         (*InputIntPtr2)=0;
         break;
		case Normally:
			if (whichattack==-1) 
				whichattack = rand()%(GameStates.CurrentSubmonster+1);
			
			MinDistance=MinDistances[GameStates.CurrentLevel][whichattack];
			FiringRange = FiringRanges[GameStates.CurrentLevel][whichattack];
			if (MoveAndShootNormally(HuntDirection, RobotPosition, MonsterPosition, urgency, whichattack))
			{
				MarkOffensiveTacticComplete();
				tactic = 0;
				whichattack = -1;
			}
			break;

		case ZigZaggy:
			MinDistance=MinDistances[GameStates.CurrentLevel][whichattack];
			FiringRange = FiringRanges[GameStates.CurrentLevel][whichattack];
			//MakeMovementZigzaggy(HuntDirection, RLDivide((RLVal(100)-MnstLife), RLVal(100)));
			MakeMovementZigzaggy(HuntDirection, RLVal(0.5));
			//if (MoveAndShootNormally(HuntDirection, RobotPosition, MonsterPosition, 1, rand()%(submonster+1)))
			if (MoveInRange(HuntDirection, urgency, 0))
				tactic = Normally;
			break;

		case FromBehind:
			MinDistance=MinDistances[GameStates.CurrentLevel][whichattack];
			FiringRange = FiringRanges[GameStates.CurrentLevel][whichattack];
			if (MoveAndShootFromBehind(HuntDirection, RobotPosition, MonsterPosition, 1))
				tactic = Normally;
			break;

		case FromHighGround:
			MinDistance=MinDistances[GameStates.CurrentLevel][whichattack];
			FiringRange = FiringRanges[GameStates.CurrentLevel][whichattack];
			if (MoveAndShootFromHighGround(HuntDirection, RobotPosition, MonsterPosition, 1))
			{
				whichattack = 1;
				tactic = Normally;
			}
			if ((IsOffensiveTacticOK[GameStates.CurrentLevel][GameStates.CurrentSubmonster][FromLowGround]) && (HuntDirection->y < RLVal(-1.0))) tactic = FromLowGround;
			if ((IsOffensiveTacticOK[GameStates.CurrentLevel][GameStates.CurrentSubmonster][FromLevelGround]) && (abs(HuntDirection->y) < RLVal(0.3))) tactic = FromLevelGround;
			break;

		case FromLowGround:
			MinDistance=MinDistances[GameStates.CurrentLevel][whichattack];
			FiringRange = FiringRanges[GameStates.CurrentLevel][whichattack];
			if (MoveAndShootFromLowGround(HuntDirection, RobotPosition, MonsterPosition, 1))
			{
				whichattack = 2;
				tactic = Normally;
			}
			if ((IsOffensiveTacticOK[GameStates.CurrentLevel][GameStates.CurrentSubmonster][FromHighGround]) && (HuntDirection->y > RLVal(1.0))) tactic = FromHighGround;
			if ((IsOffensiveTacticOK[GameStates.CurrentLevel][GameStates.CurrentSubmonster][FromLevelGround]) && (abs(HuntDirection->y) < RLVal(0.3))) tactic = FromLevelGround;
			break;

		case FromLevelGround:
			MinDistance=MinDistances[GameStates.CurrentLevel][whichattack];
			FiringRange = FiringRanges[GameStates.CurrentLevel][whichattack];
			if (MoveAndShootFromLevelGround(HuntDirection, RobotPosition, MonsterPosition, 1))
			{
				whichattack = 0;
				tactic = Normally;
			}
			if ((IsOffensiveTacticOK[GameStates.CurrentLevel][GameStates.CurrentSubmonster][FromHighGround]) && (HuntDirection->y > RLVal(1.0))) tactic = FromHighGround;
			if ((IsOffensiveTacticOK[GameStates.CurrentLevel][GameStates.CurrentSubmonster][FromLowGround]) && (HuntDirection->y < RLVal(-1.0))) tactic = FromLowGround;
			break;

		case InASpiral:
			MinDistance=MinDistances[GameStates.CurrentLevel][whichattack];
			FiringRange = FiringRanges[GameStates.CurrentLevel][whichattack];
			if (MoveInASpiral(HuntDirection, RobotPosition, MonsterPosition, (RLDivide(RLVal(1), InvDist2) < RLVal(0.8) ? RLDivide(RLVal(1), InvDist2) : RLVal(0.8)))) 
				tactic = Normally;
			if (Boredom+Rage > Joy) 
			{
				RLVector dir;
				RLFrameGetPosition(Robotframe, monstframe, &dir);
				if (dir.z < RLVal(0)) tactic = FromBehind;
				else tactic = Normally;
			}
			break;

		case InAStar:
			MinDistance=MinDistances[GameStates.CurrentLevel][whichattack];
			FiringRange = FiringRanges[GameStates.CurrentLevel][whichattack];
			MoveInAStar(HuntDirection, RobotPosition, MonsterPosition, newtactic); 
			if (Boredom > Joy) 
			{
				RLVector dir;
				RLFrameGetPosition(Robotframe, monstframe, &dir);
				if (dir.z < RLVal(0)) 
					tactic = FromBehind;
				else 
					if (Rage > Joy + Boredom)
						tactic = Normally;
					else						
						tactic = InASpiral;
				Boredom = RLVal(0);
			}
			break;

		case FlyingNormally:
			MinDistance=MinDistances[GameStates.CurrentLevel][whichattack];
			FiringRange = FiringRanges[GameStates.CurrentLevel][whichattack];
			RobotDirection.x = RobotPosition->x - MonsterPosition->x;
			RobotDirection.y = RobotPosition->y - MonsterPosition->y;
			RobotDirection.z = RobotPosition->z - MonsterPosition->z;
			if (FlyInRange(HuntDirection, &RobotDirection, MonsterPosition, RLVal(1.5), 0)) {
				FiringRange = RLVal(4.0);
				tactic = Normally;
			}
			break;

		case FlyingZigZaggy:
			MinDistance=MinDistances[GameStates.CurrentLevel][whichattack];
			FiringRange = FiringRanges[GameStates.CurrentLevel][whichattack];
			MakeMovementZigzaggy(HuntDirection, RLDivide((RLVal(100)-MnstLife), RLVal(100)));
			if (FlyInRange(HuntDirection, &RobotDirection, MonsterPosition, RLVal(1.5), 0)) {
				FiringRange = RLVal(4.0);
				tactic = Normally;
			}
			break;

		case FlyingFromBehind:
			MinDistance=MinDistances[GameStates.CurrentLevel][whichattack];
			FiringRange = FiringRanges[GameStates.CurrentLevel][whichattack];
			if (FlyInRange(HuntDirection, &RobotDirection, MonsterPosition, RLVal(1.5), 0)) {
				FiringRange = RLVal(4.0);
				tactic = Normally;
			}
			break;
		case BodySlam:
			MinDistance=MinDistances[GameStates.CurrentLevel][whichattack];
			FiringRange = FiringRanges[GameStates.CurrentLevel][whichattack];
			if (MoveAndShootNormally(HuntDirection, RobotPosition, MonsterPosition, urgency, 0))
			{
				MarkOffensiveTacticComplete();
				tactic = 0;
			}
			break;
	}
	MonsterOffTactic = tactic;
}


void EnactDefensiveTactic(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int newtactic)
{
	static int dtactic=0;
	RLVector pos;
//	RLVector RobotDirection;
	
  	RLFrameGetPosition(Robotframe, monstframe, &pos);
	if ((MonsterMovementState==MonsterFTopSpeed4) || (2*fabs(pos.x) > fabs(pos.z)))
		(*InputIntPtr2)=COMMANDForward|COMMANDStrongShift;
  	else
  		//if (-pos.z < pos.x) 
  			(*InputIntPtr2)=COMMANDHighAttack|COMMANDDefenseShift;
		//else
			//(*InputIntPtr2)=COMMANDForward|COMMANDMediumShift;
}

void EnactEvasiveTactic(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int newtactic)
{
	static int dtactic=0;
//	RLVector pos;
//	RLVector RobotDirection;
	
	MinDistance=RLVal(0.5);
	FiringRange = RLVal(0.0);
	HuntDirection->x = -InvDist2 * HuntDirection->x;
	HuntDirection->z = -InvDist2 * HuntDirection->z;
	if (GameStates.CurrentLevel == Hawaii) 
	{
		RLVector gradient;
		GetGradient(&gradient, MonsterPosition->x, MonsterPosition->z);
		HuntDirection->x += gradient.x;		// swing it around downhill (toward the water)
		HuntDirection->z += gradient.z;		
	}
	else
	{
		HuntDirection->x -= MonsterPosition->x - monstorigin.x;		// swing it around towards the center of the world
		HuntDirection->z -= MonsterPosition->z - monstorigin.z;		
	}
	MoveInRange(HuntDirection, 2, 0);
}


int MoveAndShootNormally(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int urgency, int attacktype)
{
	extern RLFrame Wscene;

	if (MoveInRange(HuntDirection, urgency, 1))
	{//if in range, fire off an appropriate weapon.
		switch (attacktype) {
		case 0:
			(*InputIntPtr2)=COMMANDZapper;
			break;
		case 1:
			(*InputIntPtr2)=COMMANDSpecialTwo;
			break;
		case 2:
			(*InputIntPtr2)=COMMANDSpecialOne;
			break;
	  }
	  FramesSinceLastInput=0;
	  return 1;
	}
	return 0;
}

int MoveInRange(RLVector* HuntDirection, int urgency, int backupok)
{
	//RLValue FDistance;
	RLValue Distance, DotProduct, CrossProduct;
	RLVector dir, up;
	extern RLFrame Wscene;

         RLFrameGetOrientation(monstframe,Wscene,&dir,&up);
         Distance=RLVectorModulus(HuntDirection);
         DotProduct=RLVectorDotProduct(HuntDirection,&dir);
         CrossProduct=RLDivide((RLMultiply(HuntDirection->z,dir.x) - RLMultiply(HuntDirection->x,dir.z)),Distance);
         //this is the relevant part of the cross product.  If it's positive, must turn to the right,		   
         //if it's negative, turn to the left.  If it's zero, we're either facing the correct direction or
         //180 degrees off.
         if((DotProduct>0) && (backupok))
         {
            if(CrossProduct<0)
            {
            //turn left
               (*InputIntPtr2)=COMMANDLeft|COMMANDBack;
               return 0;
            }
            else
            {
            //turn right.
               (*InputIntPtr2)=COMMANDRight|COMMANDBack;
               return 0;
            }
         }
         else
         {
            if( abs(CrossProduct) < MinDistance)
            {//we're facing in close enough to the correct direction that we should check to see if we're in range.
//			FILE *shithead;
//			shithead=fopen("shit.out","a");
//			fprintf(shithead,"cross product is %f\n",CrossProduct);
//			fprintf(shithead,"abs is %f\n",abs(CrossProduct));
//			fprintf(shithead,"mindistance is %f\n",MinDistance);
//			fclose(shithead);
               if((Distance<FiringRange))
               {//if in range, fire off an appropriate weapon.
                  FramesSinceLastInput=0;
				  return 1;
               }
               else
               {//if out of range, move forward at warp speed, scotty.
                  if (urgency == 2)
					(*InputIntPtr2)=COMMANDForward|COMMANDStrongShift;
				  else
					(*InputIntPtr2)=COMMANDForward|COMMANDMediumShift;
                  //if(CrossProduct>0)
                  //   (*InputIntPtr2)|=COMMANDRight;
                  //else if(CrossProduct<0)
                  //   (*InputIntPtr2)|=COMMANDLeft;
                  
                  return 0;
               }
            }
            else
            {//need to fine tune the direction some.
               if(CrossProduct>0)
               {
                  if(Distance<FiringRange)
                  {
                     (*InputIntPtr2)=COMMANDRight;
                     return 0;
                  }
                  else
                  {
						if (urgency == 2)
							(*InputIntPtr2)=COMMANDRight|COMMANDForward|COMMANDStrongShift;
						else 
							(*InputIntPtr2)=COMMANDRight|COMMANDForward|COMMANDMediumShift;
                     return 0;
                  }
               }
               else
               {
                  if(Distance<FiringRange)
                  {
                     (*InputIntPtr2)=COMMANDLeft;
                     return 0;
                  }
                  else
                  {
						if (urgency == 2)
							(*InputIntPtr2)=COMMANDLeft|COMMANDForward|COMMANDStrongShift;
						else 
							(*InputIntPtr2)=COMMANDLeft|COMMANDForward|COMMANDMediumShift;
                     return 0;
                  }
               }
                  
               
            }
         }
}

int RobotMoveInRange(RLVector* HuntDirection, RLVector* RobotDirection, int urgency)
{
	RLValue FDistance, Distance, DotProduct, CrossProduct;
	RLVector dir, up;
	extern RLFrame Wscene;


         RLFrameGetOrientation(Robotframe,Wscene,&dir,&up);
         Distance=RLVectorModulus(HuntDirection);
         FDistance=RLVectorModulus(RobotDirection);
         DotProduct=RLVectorDotProduct(HuntDirection,&dir);
         CrossProduct=RLDivide((RLMultiply(HuntDirection->z,dir.x) - RLMultiply(HuntDirection->x,dir.z)),Distance);
         //FCrossProduct=RLDivide((RLMultiply(RobotDirection->z,dir.x) - RLMultiply(RobotDirection->x,dir.z)),FDistance);
         //this is the relevant part of the cross product.  If it's positive, must turn to the right,		   
         //if it's negative, turn to the left.  If it's zero, we're either facing the correct direction or
         //180 degrees off.
         if(DotProduct>0)
         {
            if(CrossProduct<0)
            {
            //turn left
               (*InputIntPtr3)=COMMANDLeft|COMMANDBack;
               return 0;
            }
            else
            {
            //turn right.
               (*InputIntPtr3)=COMMANDRight|COMMANDBack;
               return 0;
            }
         }
         else
         {
            if( abs(CrossProduct) < MinDistance)
            {//we're facing in close enough to the correct direction that we should check to see if we're in range.
//			FILE *shithead;
//			shithead=fopen("shit.out","a");
//			fprintf(shithead,"cross product is %f\n",CrossProduct);
//			fprintf(shithead,"abs is %f\n",abs(CrossProduct));
//			fprintf(shithead,"mindistance is %f\n",MinDistance);
//			fclose(shithead);
               if((FDistance<FiringRange) || (Distance<FiringRange))
               {//if in range, fire off an appropriate weapon.
                  FramesSinceLastInput=0;
                  return 1;
               }
               else
               {//if out of range, move forward at warp speed, scotty.
                  if (urgency == 2)
					(*InputIntPtr3)=COMMANDForward|COMMANDStrongShift;
				  else
					(*InputIntPtr3)=COMMANDForward|COMMANDMediumShift;
                  //if(CrossProduct>0)
                  //   (*InputIntPtr2)|=COMMANDRight;
                  //else if(CrossProduct<0)
                  //   (*InputIntPtr2)|=COMMANDLeft;
                  
                  return 0;
               }
            }
            else
            {//need to fine tune the direction some.
               if(CrossProduct>0)
               {
                  if(Distance<FiringRange)
                  {
                     (*InputIntPtr3)=COMMANDRight;
                     return 0;
                  }
                  else
                  {
						if (urgency == 2)
							(*InputIntPtr3)=COMMANDRight|COMMANDForward|COMMANDStrongShift;
						else 
							(*InputIntPtr3)=COMMANDRight|COMMANDForward|COMMANDMediumShift;
                     return 0;
                  }
               }
               else
               {
                  if(Distance<FiringRange)
                  {
                     (*InputIntPtr3)=COMMANDLeft;
                     return 0;
                  }
                  else
                  {
						if (urgency == 2)
							(*InputIntPtr3)=COMMANDLeft|COMMANDForward|COMMANDStrongShift;
						else 
							(*InputIntPtr3)=COMMANDLeft|COMMANDForward|COMMANDMediumShift;
                     return 0;
                  }
               }
                  
               
            }
         }
}



void MakeMovementZigzaggy(RLVector* HuntDirection, RLValue zigzaggyness)
{
	RLValue Distance;
	RLVector Zigzag;
	extern RLFrame Wscene;
	static RLValue zig=RLVal(0.8);
	int testdist;
	extern RLFrame Wscene;


	Distance=RLVectorModulus(HuntDirection);
	
	testdist = (int)(Distance);
	if (testdist > FiringRange+1) {
		if ((testdist & 0xaa) > (testdist & 0x55)) {			// even bits vs. odd bits -- direction swaps on powers of 2 of distance
			Zigzag.x = RLMultiply(RLVal(-zigzaggyness), HuntDirection->z);
			Zigzag.z = RLMultiply(RLVal( zigzaggyness), HuntDirection->x);
		} else {
			Zigzag.x = RLMultiply(RLVal( zigzaggyness), HuntDirection->z);
			Zigzag.z = RLMultiply(RLVal(-zigzaggyness), HuntDirection->x);
		}
	} else 
		Zigzag.x = Zigzag.z = RLVal(0);

	HuntDirection->x += Zigzag.x;
	HuntDirection->z += Zigzag.z;

}

int MoveAndShootFromLowGround(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int urgency)
{
	RLValue Distance, AltitudeDiff, perterb;
	RLVector gradient, RobotDirection;
	extern RLFrame Wscene;

    Distance = RLVectorModulus(HuntDirection);
	AltitudeDiff = RobotDirection.y;
	GetGradient(&gradient, RobotPosition->x, RobotPosition->z);
	perterb = (MAX(RLMultiply(RLVal(3), RLDivide(Distance, FiringRange)- RLVal(1)), RLVal(0)));
	HuntDirection->x += RLMultiply(-gradient.x, perterb);
	HuntDirection->z += RLMultiply(-gradient.z, perterb);
    //Distance=RLVectorModulus(HuntDirection);

	//if (MoveInRange(HuntDirection, &RobotDirection, 1, 1) == 2)
	//	(*InputIntPtr2)=COMMANDSpecialOne;
	return MoveInRange(HuntDirection, 1, 1);
}

int MoveAndShootFromLevelGround(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int urgency)
{
	RLValue Distance, AltitudeDiff, perterb;
	RLVector gradient, RobotDirection;
	extern RLFrame Wscene;

	AltitudeDiff = RobotDirection.y;
	GetGradient(&gradient, RobotPosition->x, RobotPosition->z);
	Distance=RLVectorModulus(HuntDirection);
	perterb = (MAX(RLMultiply(RLVal(3), RLDivide(Distance, FiringRange)- RLVal(1)), RLVal(0)));
	if (RLMultiply(gradient.z,HuntDirection->x) + RLMultiply(-gradient.x, HuntDirection->z) < RLVal(0)) {
		HuntDirection->x += RLMultiply( gradient.z, perterb);
		HuntDirection->z += RLMultiply(-gradient.x, perterb);
        //Distance=RLVectorModulus(HuntDirection);
	} else {
		HuntDirection->x += RLMultiply(-gradient.z, perterb);
		HuntDirection->z += RLMultiply( gradient.x, perterb);
        //Distance=RLVectorModulus(HuntDirection);
	}

	//if (MoveInRange(HuntDirection, &RobotDirection, 1, 1) == 2)
	//{//if in range, fire off an appropriate weapon.
	//	if ((AltitudeDiff < RLVal(0.5)) && (AltitudeDiff > RLVal(-1.0)))
	//		(*InputIntPtr2)=COMMANDZapper;
	//	else 
	//		(*InputIntPtr2)=COMMANDForward|COMMANDMediumShift;
	//}
	return MoveInRange(HuntDirection, 1, 1);
}

int MoveAndShootFromHighGround(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int urgency)
{
	RLValue Distance, AltitudeDiff, perterb;
	RLVector gradient, RobotDirection;
	extern RLFrame Wscene;

	AltitudeDiff = RobotDirection.y;
    Distance=RLVectorModulus(HuntDirection);
	GetGradient(&gradient, RobotPosition->x, RobotPosition->z);
	perterb = (MAX(RLMultiply(RLVal(4), RLDivide(Distance, FiringRange)- RLVal(1)), RLVal(0)));
	HuntDirection->x += RLMultiply(gradient.x, perterb);
	HuntDirection->z += RLMultiply(gradient.z, perterb);
    Distance=RLVectorModulus(HuntDirection);

	return MoveInRange(HuntDirection, 1, 1);
	//{//if in range, fire off an appropriate weapon.
	//	(*InputIntPtr2)=COMMANDSpecialTwo;
	//}
}

void RobotMoveAndShootNormally(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition)
{
	RLVector MonsterDirection;
	RLVector force;
	RLValue MonsterDistance;
	extern RLFrame Wscene;


	MonsterDirection.x = RobotPosition->x - MonsterPosition->x;
	MonsterDirection.y = RobotPosition->y - MonsterPosition->y;
	MonsterDirection.z = RobotPosition->z - MonsterPosition->z;

	MonsterDistance = RLVectorModulus(&MonsterDirection);

	if (AvoidBuildings(*MonsterPosition, &force))
   {
	   HuntDirection->x += force.x*MonsterDistance;
	   HuntDirection->y += force.y*MonsterDistance;
	   HuntDirection->z += force.z*MonsterDistance;
   }

	if ((RobotEngy > MnstEngy/2) && (MnstLife > 0))
	{
		if (RobotMoveInRange(HuntDirection, &MonsterDirection, 1))
      {//if in range, fire off an appropriate weapon.
			if (rand()&1)
				(*InputIntPtr3)=COMMANDVisorBeam;
			else 
				if (rand()&1)
					(*InputIntPtr3)=COMMANDShuriken;
				else 
					(*InputIntPtr3)=COMMANDUltraBlast;
      }
	}
	else
	{
		(*InputIntPtr3)=0;
	}
}


int MoveAndShootFromBehind(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int urgency)
{
	RLValue Distance;
	extern RLFrame Wscene;
	RLVector relpos;
	RLValue sidemove;

    Distance = RLVectorModulus(HuntDirection);
	RLFrameGetPosition(monstframe, Robotframe, &relpos);
	if (fabs(relpos.x) < (relpos.z)) {
		sidemove = RLDivide(relpos.x, fabs(relpos.z));
	} else {
		if (relpos.x > 0) sidemove = RLVal(1);  //RLDivide(fabs(relpos.z), (relpos.x));
		else sidemove = RLVal(-1);
	}
	HuntDirection->x+= RLMultiply( HuntDirection->z, sidemove);
	HuntDirection->z+= RLMultiply(-HuntDirection->x, sidemove);
	HuntDirection->y=RLVal(0);

	return (MoveInRange(HuntDirection, 1, 1));
		//(*InputIntPtr2)=COMMANDSpecialOne;
}

int FlyFromBehind(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int urgency)
{
	RLValue Distance;
	RLVector RobotDirection;
	extern RLFrame Wscene;
	RLVector relpos;
	RLValue sidemove;

    Distance = RLVectorModulus(HuntDirection);
	RobotDirection.x = MonsterPosition->x - RobotPosition->x;
	RobotDirection.y = MonsterPosition->y - RobotPosition->y;
	RobotDirection.z = MonsterPosition->z - RobotPosition->z;

	RLFrameGetPosition(monstframe, Robotframe, &relpos);
	if (fabs(relpos.x) < (relpos.z)) {
		sidemove = RLDivide(relpos.x, fabs(relpos.z));
	} else {
		if (relpos.x > 0) sidemove = RLVal(1);  //RLDivide(fabs(relpos.z), (relpos.x));
		else sidemove = RLVal(-1);
	}
	HuntDirection->x+= RLMultiply( HuntDirection->z, sidemove);
	HuntDirection->z+= RLMultiply(-HuntDirection->x, sidemove);
	HuntDirection->y=RLVal(0);

	return FlyInRange(HuntDirection, &RobotDirection, MonsterPosition, RLVal(1.5), 0);
		//(*InputIntPtr2)=COMMANDSpecialOne;
}

int MoveInASpiral(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, RLValue spiralamount)
{
	RLVector temp, RobotDirection;
	extern RLFrame Wscene;

	RLFrameGetPosition(Robotframe, monstframe, &RobotDirection);

	if (RobotDirection.x > RLVal(0.0)) {
		temp.x = RLMultiply(+HuntDirection->z, spiralamount);
		temp.z = RLMultiply(-HuntDirection->x, spiralamount);
	} else {
		temp.x = RLMultiply(-HuntDirection->z, spiralamount);
		temp.z = RLMultiply(+HuntDirection->x, spiralamount);
	}
	temp.x += RLMultiply(HuntDirection->x, RLVal(1.0-spiralamount));
	temp.z += RLMultiply(HuntDirection->z, RLVal(1.0-spiralamount));
	HuntDirection->x = temp.x;
	HuntDirection->z = temp.z;
	HuntDirection->y=RLVal(0);

	return MoveInRange(HuntDirection, 2, 0);
}

void MoveInAStar(RLVector* HuntDirection, RLVector* RobotPosition, RLVector* MonsterPosition, int startagain)
{
	RLValue Distance;
	RLVector dir, up;
	extern RLFrame Wscene;
	static int whichpoint=0;
//	RLVector RobotDirection;
	extern RLFrame Wscene;
	RLVector star[5] = {
		{ RLVal( 17.6), RLVal(0), RLVal(-24.3) },
		{ RLVal(0),     RLVal(0), RLVal( 30.0) },
		{ RLVal(-17.6), RLVal(0), RLVal(-24.3) },
		{ RLVal( 28.5), RLVal(0), RLVal(  9.3) },
		{ RLVal(-28.5), RLVal(0), RLVal(  9.3) }
	};

	if (startagain) whichpoint = 0;

	RLFrameGetOrientation(monstframe,Wscene,&dir,&up);
	Distance=RLVectorModulus(HuntDirection);
	
	HuntDirection->x += star[whichpoint].x;
	HuntDirection->z += star[whichpoint].z;

	if (MoveInRange(HuntDirection, 1, 0) == 1) {
		if (whichpoint<4) 
			(*InputIntPtr2)=COMMANDWeakShift|COMMANDMediumShift|COMMANDStrongShift;
		else 
		{
			(*InputIntPtr2)=COMMANDSpecialTwo;
			MarkOffensiveTacticComplete();
		}
		whichpoint = (whichpoint+1)%5;
	}
}

int FlyInRange(RLVector* HuntDirection, RLVector* RobotDirection, RLVector* MonstPlace, RLValue tightness, int avoidbuildings)
{
	//RLValue FDistance;
	RLValue Distance, DotProduct, CrossProduct, groundheight, acc, time, vel;
	RLVector dir, up, force;
	long int flapper;
	extern RLFrame Wscene;
	extern RLValue MonsterYSpeed, MonsterGravity;
	extern RLVector MonsterVelocity;

	if (avoidbuildings) AvoidBuildings(*MonstPlace, &force);
	else force.x = force.y = force.z = RLVal(0.0);

	HuntDirection->x += force.x;
	HuntDirection->y += force.y;
	HuntDirection->z += force.z;

	groundheight = SpuddeMapHeight2(HuntDirection->x + MonstPlace->x, HuntDirection->z + MonstPlace->z);


     RLFrameGetOrientation(monstframe,Wscene,&dir,&up);
     Distance=RLVectorModulus(HuntDirection);
     //FDistance=RLVectorModulus(RobotDirection);
     DotProduct=RLVectorDotProduct(HuntDirection,&dir);
     CrossProduct=RLDivide((RLMultiply(HuntDirection->z,dir.x) - RLMultiply(HuntDirection->x,dir.z)),Distance);
     //FCrossProduct=RLDivide((RLMultiply(RobotDirection->z,dir.x) - RLMultiply(RobotDirection->x,dir.z)),FDistance);
     //this is the relevant part of the cross product.  If it's positive, must turn to the right,		   
     //if it's negative, turn to the left.  If it's zero, we're either facing the correct direction or
     //180 degrees off.

	if (Distance < (MonstPlace->y - groundheight)) 
		HuntDirection->y -= RLMultiply(Distance, RLVal(0.5));
	
	if (MonsterMovementState==MonsterFTopSpeed4) {
		time = RLVal(RLMultiply(tightness, fabs(HuntDirection->y)));
		//acc = RLMultiply(RLVal(0.5), RLMultiply3(RLMultiply(DiffFrame, time), RLMultiply(DiffFrame, time), MonsterGravity));
		acc = RLMultiply(RLVal(0.5), RLMultiply3(MonsterYSpeed, time, time));
		vel = RLMultiply(MonsterVelocity.y, time);
		if ((HuntDirection->y - vel - acc) > RLVal(0))
		//if ((HuntDirection->y) > RLVal(0))
			flapper = COMMANDJump;
		else 
			flapper = 0;
	} else flapper = 0;
     {
        if( abs(CrossProduct) < MinDistance)
        {//we're facing in close enough to the correct direction that we should check to see if we're in range.
//			FILE *shithead;
//			shithead=fopen("shit.out","a");
//			fprintf(shithead,"cross product is %f\n",CrossProduct);
//			fprintf(shithead,"abs is %f\n",abs(CrossProduct));
//			fprintf(shithead,"mindistance is %f\n",MinDistance);
//			fclose(shithead);
           if((Distance<FiringRange))
           {//if in range, fire off an appropriate weapon.
              FramesSinceLastInput=0;
              //if (FDistance<FiringRange) return 2;
			  return 1;
           }
           else
           {//if out of range, move forward at warp speed, scotty.
				(*InputIntPtr2)=COMMANDForward|COMMANDStrongShift|flapper;
              //if(CrossProduct>0)
              //   (*InputIntPtr2)|=COMMANDRight;
              //else if(CrossProduct<0)
              //   (*InputIntPtr2)|=COMMANDLeft;
              
              return 0;
           }
        }
        else
        {//need to fine tune the direction some.
           if(CrossProduct>0)
           {
				(*InputIntPtr2)=COMMANDRight|COMMANDForward|COMMANDStrongShift|flapper;
                 return 0;
           }
           else
           {
				(*InputIntPtr2)=COMMANDLeft|COMMANDForward|COMMANDStrongShift|flapper;
                 return 0;
           }
              
           
        }
     }
}

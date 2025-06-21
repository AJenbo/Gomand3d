#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <windows.h>
#include <stdio.h>
#include "rl2d3d.h" 
#include "gosys.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum Robots
{
	SabreRobot=0,
	StealthRobot,
	MerRobot,
	KataRobot,
	KaberRobot
}RobotID;

typedef enum Levels
{
	Trainer=0,
	Mojave,
	Rockies,
	Hawaii,
	SanFrancisco,
	NewYork,
	Tokyo
}LevelID;

typedef enum Submonsters
{
	Alpha,
	Beta,
	Gamma
}SubmonsterID;

typedef struct 
{
	int CurrentLevel;				//This will be changed in the wrapper 
									//after unloading the last level, if monsters
									//are dead, or if in autodemo, or will be changed
									//in netplay by player2's choice, or in wrapper
									//by choosing to go to the training level or not.
	
	int CurrentRobot;				//This is chosen in the wrapper by player 1.

	int CurrentSubmonster;			//This is chosen entering a level, and changes
									//as submonsters die.

	int Score;						//this is added to at the successful completion of 
									//any level.

	unsigned char Hours;
	unsigned char Minutes;
	unsigned char Seconds;
	
	BOOL IsRobotDead[5];				//Booleans for deaths of the Robots.
									//Not used in netplay, or autodemo, not changed 
									//in trainer,

	BOOL IsMonsterDead[7][3];		//Booleans for deaths of monsters.
									//Not used in netplay, or autodemo, not changed 
									//in trainer,

	BOOL LevelHonor[7];

	BOOL MonsterLose;				//Did the monster lose?  This can't always be told
									//by looking at IMD because monsters don't die if 
									//in netplay or in autodemo

	BOOL RobotLose;				//Did the Robot lose?  See above comment.

	BOOL Is3DMovie;					//Boolean, turned on for very end of 3d sample.
	
	BOOL IsAutodemo;				//Boolean, turned on during Autodemo play.

	BOOL IsTraining;				//Boolean, set in wrapper when going to trainer level.
									//deaths don't count here.

	BOOL IsGame;					//Boolean, for when the game has been sitting around
									//in the hot sun for so long that it gets a bit 
									//gamy
	
	BOOL IsNetplay;					//Are you playing against a remote opponent?
}sGameVariables;

extern sGameVariables GameStates;
extern TARGET targets[];
extern BOOL bFrameMeter; // New Global from Tim


void YBPlayEndingMidi(short Idx);
void YBTextOut(HWND win, char *str, char *font, RECT p1);
void MDFreeD3DFrame(LPDIRECT3DRMFRAME frame);
BOOL BYDumpInfo(char *s);

#ifdef __cplusplus
};

#endif

#endif
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
File:           gosys.h
Author:         Jeremiah Spudde Childs
Date:           9-27-95
Version:        1.0



************************************************************************
REVISION HISTORY        (Add Edits and History to top of list).

Edited By:      Bruce Abe
Edited Date:    11/07/95
Changes:
                Added SpuddeMapHeight2's function declaration.

***********************************************************************/
#ifndef _GOSYS_H_
#define _GOSYS_H_

#include "rl2d3d.h"

#ifdef __cplusplus
extern "C" {
#endif

RLValue MapHeight(int x, int z);
RLValue SpuddeMapHeight(int x, int y);
RLValue SpuddeMapHeight1(int t);
RLValue SpuddeMapHeight2(RLValue x, RLValue y);
void SpuddeGetWorldPosition(int x, int y, RLValue *X, RLValue *Z);
void SpuddeGetBMPPosition(int *x, int *y, RLValue X, RLValue Z);
void GetGradient(RLVector* gradient, RLValue x, RLValue z);

void FreeTexture(RLTexture doomedtex);

void SetBackground(int level);

void PlaceRobot(int level);
void PlaceMonster(int level, int fromthetop);

char* ConstructLevelName(char* name);
char* ConstructRobotName(int Robotint, char* name);
char* ConstructMonsterName(char* name);

void SwapRobotNMonster(int whichone);
void PreserveForTrainer(void);
void RestoreFromTrainer(void);

RLImage* RLLoadRLP(char* name);

int HandleDeath();

#undef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#undef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct _TARGET_ {
    RLVector p;
    short    life;      // 1 = live, 0 = dead
    short    type;      // 1 = monster, 2 = 
} TARGET;

typedef struct _sEnding3DMovieData {
   RLValue SegCountdown;               // Counter for transitions between stages of 3d movie               
	RLValue timemark;                   // Marker to store the time of the last transition
	int stage;                          // Index to the stage of the 3d movie that we're currently in
} sEnding3DMovieData;

extern sEnding3DMovieData Ending3DMovie;

extern unsigned char detail;
extern int GameWindowW, GameWindowH;

BOOL LoadMap(int level);
void FreeMap(void);

void DumpMemoryStatus(char *where);


#ifdef _ITC_D3D_
typedef struct	_PCXHEAD{
	unsigned char Manufacture;
	unsigned char Version;
	unsigned char Encoding;
	unsigned char BitsPerPixel;
	short         MinX, MinY;
	short         MaxX, MaxY;
	short         Hres, Vres;
	unsigned char Palette[48];
	unsigned char Reserved;
	unsigned char ColorPlanes;
	short         BytesPerLine;
	short         PaletteType;
	unsigned char Filler[58];
} PCXHEAD;
#endif 

#ifdef __cplusplus
};
#endif

#endif
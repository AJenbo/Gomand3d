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
File:           gosys.c
Author:         Jeremiah Spudde Childs
Date:           9-27-95
Version:        1.01



************************************************************************
$Header:   H:/pvcs/pvcsproj/gomand3d.prj/GOSYS.C_V   1.26   15 May 1997 17:47:54   Jeremiah  $

$Log:   H:/pvcs/pvcsproj/gomand3d.prj/GOSYS.C_V  $
 * 
 *    Rev 1.26   15 May 1997 17:47:54   Jeremiah
 * Made Robot avoid buildings in 3dmovie.
 * 
 *    Rev 1.25   18 Mar 1997 15:01:18   JEREMIAH
 * Moved the Robot's dropin point further
 * from the phantom hit zone.
 * 
 *    Rev 1.24   14 Mar 1997 15:40:34   JEREMIAH
 * Kludged the phantom hit bug by moving 
 * the Robot dropin point on Mojave to 1,1.
 * 
 *    Rev 1.23   25 Feb 1997 20:21:48   BRUCE
 * set AI input to 0 when the 3d movie starts,
 * so that the monster doesn't just
 * continue doing what it had been doing.
 * 
 *    Rev 1.22   25 Feb 1997 17:13:18   BRUCE
 * replaced OverallScore with
 * GameStates.Score
 * 
 * 
 *    Rev 1.21   21 Feb 1997 16:01:10   BRUCE
 * put honor into gamestates, made one honor
 * for each level.
 * 
 *    Rev 1.20   20 Feb 1997 10:44:30   JEREMIAH
 * Consolidated 3D movie global variables 
 * into a structure. 
 * 
 *    Rev 1.19   14 Feb 1997 23:59:04   BRUCE
 * morged versions 1.17.1.0 and 1.18
 * 
 *    Rev 1.18   14 Feb 1997 19:40:08   BRUCE
 * removed _47TEK_RL_ code
 * removed _ITC_D3D_ conditional
 * included "wrapper.h"
 * changed level to GameStates.CurrentLevel
 * changed levelwereon to GameStates.CurrentLevel
 * changed current_level to GameStates.CurrentLevel
 * changed submonster to GameStates.CurrentSubmonster
 * changed In3DMovie to GameStates.Is3DMovie
 * changed AutoDemoFlag to GameStates.IsAutodemo
 * changed condition from Robotlife==0 to GameStates.RobotLose
 * changed condition from MonsterAnimationState==MonsterAllDead to GameStates.MonsterLose
 * 
 *    Rev 1.17.1.0   14 Feb 1997 11:28:12   JEREMIAH
 * Correctly disabled cars/spores in netplay
 * mode.
 * 
 *    Rev 1.17   10 Feb 1997 12:22:56   JEREMIAH
 * Changed by Bo.
 * - added three midi constants definition
 * - added code to play win/lose midi in 3D movie in each 
 * level.
 * 
 * 
 *    Rev 1.16   07 Feb 1997 10:41:48   BRUCE
 * Changed fog colors.
 * 
 *    Rev 1.15   06 Feb 1997 08:16:52   BRUCE
 * took control of whichRobot
 * 
 *    Rev 1.14   05 Feb 1997 16:40:02   JEREMIAH
 * Improved the printouts in 
 * DumpMemoryStatus.
 * 
 *    Rev 1.13   04 Feb 1997 16:17:18   JEREMIAH
 * Added DumpMemoryStatus() function.
 * 
 *    Rev 1.12   31 Jan 1997 18:04:54   TIM
 * Now determines fog color
 * 
 *    Rev 1.11   31 Jan 1997 10:18:24   JEREMIAH
 * Fixed gameflow bug.  Level was not 
 * being incremented with Robot victory.
 * 
 *    Rev 1.10   30 Jan 1997 16:54:58   JEREMIAH
 * Do not clear level_flag array after level.
 * 
 *    Rev 1.9   27 Jan 1997 10:37:42   JEREMIAH
 * Fixed autodemo timeout.
 * 
 *    Rev 1.8   23 Jan 1997 12:51:50   BRUCE
 * added BYDump for bad altitude map load.
 * 
 *    Rev 1.7   22 Jan 1997 13:22:34   JEREMIAH
 * Cleaned up ending sequences to (hopefully)
 * create fewer side-effects.
 * 
 *    Rev 1.6   16 Jan 1997 22:47:36   BRUCE
 * removed Robot from movingobjects list after
 * it's killed, so it won't be in collisions then.
 * 
 *    Rev 1.5   20 Dec 1996 17:06:40   JEREMIAH
 * Changed filenames of textures to match
 * new filename conventions for level-specific
 * palettes.
 * 
 *    Rev 1.4   18 Dec 1996 09:00:52   BRUCE
 * changed the name of the dat file read in to
 * account for different dat files for different
 * submonsters.
 * 
 *    Rev 1.3   17 Dec 1996 12:55:00   BRUCE
 * doubled landscape poly size, halved 
 * resolution, for significant framerate 
 * jump.
 * 
 *    Rev 1.1   Nov 05 1996 14:59:34   JEREMIAH
 * Made the value of level get changed after
 * end of 3d movie instead of before 3d
 * movie.

***********************************************************************/


#include <windows.h>
#include <stdio.h>

#include "rl2d3d.h"
#include "rmfull.h"

#include "gosys.h"
#include "landscap.h"
#include "ybreg.h"
#include "ybsnd.h"
#include "keycom.h"
#include "camera.h"
#include "boink.h"
#include "monanim.h"
#include "monmove.h"
#include "monthink.h"
#include "Robotmove.h"
#include "building.h"
#include "bldgboom.h"
#include "cars.h"
#include "ichars.h"
#include "global.h"
#include "byglobal.h"
#include "d3dappi.h"
#include "wrapper.h"
#define MID_PLAY 601
#define MID_STOP 602
#define MID_SILENT 603

extern char BmpPath[];
RLImage* RLLoadRLP(char* name);

static unsigned char *topo;
static RLTexture topotex;
static RLImage* topoimg;
//extern RLPaletteEntry *topopal;
static int map_level=-1;
//extern int level;
extern RLFrame Robotframe, monstframe, Wscene, Wcamera;
extern visible_buildings missiontarget;
extern RLFrame MonsterScaleFrame;

//int current_level = 0;
int autodemo = 0;
long int Population;
long int PrePopulation = 1000000;
//unsigned char detail = 2;
int GameWindowW, GameWindowH;
//int honor = 1;
BOOL PlayAsMonster = 0;
BOOL PlayerHasWon = 0;
RLColour theonlycolor;
RLMaterial theonlymaterial;

RLTexture bgtex;
static RLImage* bgimg;
//static int ground_level=0;
RLValue MonsterScaleFactor;

/* change 3d model object file extension
 * added by Sanfo 7/3/1996
 */
#define GIF(name)   name##".gif"
#define PCX(name)   name##".pcx"

#ifdef _ITC_D3D_
#define IMAGE(name) PCX(name)
#else
#define IMAGE(name) GIF(name)
#endif
/*comment end*/

char MapFile[7][10] =
{
	IMAGE("LX101"),   // Level Zero Altitude Map
	IMAGE("LM101"),   // Level One Altitude Map
	IMAGE("LR101"),   // Level Two Altitude Map
	IMAGE("LH101"),   // Level Three Altitude Map
	IMAGE("LS101"),   // Level Four Altitude Map
	IMAGE("LN101"),   // Level Five Altitude Map
	IMAGE("LT101")    // Level Six Altitude Map
};

char monstername[7][16] = {
	"VIRTUAL MONSTER",
	"ROGGOSH", 
	"KOTHOS", 
	"TOLGO", 
	"SHAGTOQ", 
	"NEALLOTH", 
	"GAINGRIS"
};
	
char targetname[7][3][32] = {
	{
		"VIRTUAL BUILDING #1",
		"VIRTUAL BUILDING #2",
		"VIRTUAL BUILDING #3"
	},
	{
		"AGRONOMY CENTER",
		"POWER RELAY",
		"SOLAR POWER ARRAY"
	},
	{
		"VACATION CITY",
		"PAUL BUNYAN MUSEUM",
		"VISITOR'S CENTER"
	},
	{
		"GEOTHERMAL PLANT",
		"FISHERMAN'S GROTTO",
		"DESALINATION PLANT"
	},
	{
		"MUSEUM OF MODERN ART",
		"MEGA HOTEL",
		"TRANSAMERICA PYRAMID"
	},
	{
		"HOSPITAL",
		"WORLD TRADE CENTER",
		"U.E.T. HEADQUARTERS"
	},
	{
		"NEODIET BUILDING",
		"TOKYO DOME",
		"TOKYO TOWER"
	}
};
	


char* ConstructRobotName(int Robotint, char* name)
{
	static char thepath[80];
	//char levelstring[2];
    
	switch (Robotint) {
	case SabreRobot:
		strcpy(thepath, "SA"); break;
	case StealthRobot:
		strcpy(thepath, "ST"); break;
	case MerRobot:
		strcpy(thepath, "ME"); break;
	case KataRobot:
		strcpy(thepath, "KA"); break;
	case KaberRobot:
		strcpy(thepath, "KB"); break;
	}

    //strcpy(thepath, levelstring );
    strcat(thepath, name);
	 if (!strnicmp(strchr(thepath, '.'), ".bmp", 4))
      return ConstructLevelName(thepath);
    else
      return thepath;

}
 

char* ConstructLevelName(char* name)
{
	static char thepath[80];
	//char levelstring[2];
    
	switch (GameStates.CurrentLevel) 
	{
	case Trainer:
		strcpy(thepath, "LX"); 
		break;
	case Mojave:
		strcpy(thepath, "LM"); 
		break;
	case Rockies:
		strcpy(thepath, "LR"); 
		break;
	case Hawaii:
		strcpy(thepath, "LH"); 
		break;
	case SanFrancisco:
		strcpy(thepath, "LS"); 
		break;
	case NewYork:
		strcpy(thepath, "LN"); 
		break;
	case Tokyo:
		strcpy(thepath, "LT"); 
		break;
	}

    //strcpy(thepath, levelstring );
    strcat(thepath, name);
	return thepath;
}
 

char* ConstructMonsterName(char* name)
{
	static char thepath[80];
	//char levelstring[2];
    
	switch (GameStates.CurrentLevel) 
	{
	case Trainer:
		strcpy(thepath, "TR"); 
		break;
	case Mojave:
		strcpy(thepath, "RO"); 
		break;
	case Rockies:
		strcpy(thepath, "KO"); 
		break;
	case Hawaii:
		strcpy(thepath, "TO"); 
		break;
	case SanFrancisco:
		strcpy(thepath, "SH"); 
		break;
	case NewYork:
		strcpy(thepath, "NE"); 
		break;
	case Tokyo:
		strcpy(thepath, "GA"); 
		break;
	}

    //strcpy(thepath, levelstring );
    strcat(thepath, name);
	return thepath;
}
 



void SetBackground(int level)
{

	switch (GameStates.CurrentLevel) 
	{
	case Trainer:
		d3dapprs.FogColor = RGB_MAKE(0, 0, 0);
		break;
	case Mojave:
		d3dapprs.FogColor = RGB_MAKE(87, 80, 70);
		break;
	case Rockies:
		d3dapprs.FogColor = RGB_MAKE(239, 247, 255);
		break;
	case Hawaii:
		d3dapprs.FogColor = RGB_MAKE(130, 150, 150);
		break;
	case SanFrancisco:
		d3dapprs.FogColor = RGB_MAKE(130, 130, 130);
		break;
	case NewYork:
		d3dapprs.FogColor = RGB_MAKE(75, 36, 25);
		break;
	case Tokyo:
		d3dapprs.FogColor = RGB_MAKE(20, 0, 40);
		break;
	}
	return;
}


RLVector Robotorigin, monstorigin;
extern struct _moving_object_data_ 	MonsterData; 
//extern int submonster;

void PlaceRobot(int level)
{
	switch(GameStates.CurrentLevel)
	{
//1            66, 230
		case Trainer:
			Robotorigin.x = RLVal(-2);
			Robotorigin.z = RLVal(4);
		break;
		case Mojave:
			Robotorigin.x = RLVal(5);
			Robotorigin.z = RLVal(5);
		break;
//2            14, 19
		case Rockies:
			Robotorigin.x = RLVal(0);
			Robotorigin.z = RLVal(0);
		break;
//3            92, 221
		case Hawaii:
			Robotorigin.x = RLVal(0);
			Robotorigin.z = RLVal(0);
		break;
//4            238, 35
		case SanFrancisco:
			Robotorigin.x = RLVal(-1);
			Robotorigin.z = RLVal(-10);
		break;
//5            197, 146
		case NewYork:
			Robotorigin.x = RLVal(0);
			Robotorigin.z = RLVal(0);
		break;
//6            121, 31
		case Tokyo:
			Robotorigin.x = RLVal(-2);  
			Robotorigin.z = RLVal(9);  
		break;
	}
	Robotorigin.y = SpuddeMapHeight2(Robotorigin.x, Robotorigin.z);
	RLFrameSetPosition(Robotframe,Wscene,Robotorigin.x,Robotorigin.y+40,Robotorigin.z);
	RLFrameSetPosition(Wcamera,Wscene,Robotorigin.x,SpuddeMapHeight2(Robotorigin.x, Robotorigin.z)+40,Robotorigin.z);
}


extern int MonsterAnimationState;
extern int MonsterMovementState;
void PlaceMonster(int level, int fromthetop)
{
	visible_buildings theegg;
	RLVector dumb;
	char datname[16];
	FILE *shithead;
	extern char DatPath[];
	extern RLValue Rage;
	extern RLValue Fear;
	extern RLValue Boredom;
	extern RLValue Joy;
	extern RLValue MonsterBoxXZ[];
	extern RLValue MonsterHeight[];

	Rage = RLVal(0);
	Fear = RLVal(0);
	Boredom = RLVal(0);
	Joy = RLVal(0);

	dumb.x = RLVal(0.0);
	dumb.y = RLVal(0.0);
	dumb.z = RLVal(0.0);

	switch(GameStates.CurrentLevel)
	{
//1            66x205  103x166
		case Trainer:
		case Mojave:
			monstorigin.z = RLVal(103-128);
			monstorigin.x = RLVal(166-128);
		break;
//2            173x24  69x23
		case Rockies:
			monstorigin.z = RLVal(165-128);
			monstorigin.x = RLVal(151-128);
		break;
	
//3            26x91   103x166
		case Hawaii:
			monstorigin.z = RLVal(103-128);
			monstorigin.x = RLVal(166-128);
		break;
//4            214x238 36x44
		case SanFrancisco:
			monstorigin.z = RLVal(36-128);
			monstorigin.x = RLVal(44-128);
		break;
//5            114x232 148x30
		case NewYork:
		//monstorigin.z = RLVal(148-128);
		//monstorigin.x = RLVal(30-128);
			monstorigin.z = RLVal(48-128);
			monstorigin.x = RLVal(30-128);
		break;
//6            87x52   223x136
		case Tokyo:
			monstorigin.z = RLVal(223-128);
			monstorigin.x = RLVal(136-128);
		break;
	}

	FindOneBuilding(&theegg, 66+GameStates.CurrentSubmonster);
	if (theegg.count == 1) 
	{
		theegg.building_ptr[0]->cur_damage = theegg.building_ptr[0]->max_damage;
		CowboyDeathMarch((theegg.building_ptr[0]),&dumb);
		//RLFrameSetPosition(monstframe, Wscene, RLVal(theegg.building_ptr[0]->x_world-LANDXCENTER), RLVal(theegg.building_ptr[0]->y_world), RLVal(theegg.building_ptr[0]->z_world-LANDZCENTER));
		monstorigin.x = MonsterData.ProjectedPosition.x = RLVal(theegg.building_ptr[0]->x_world-LANDXCENTER);
		MonsterData.ProjectedPosition.y = RLVal(theegg.building_ptr[0]->y_world);
		monstorigin.z = MonsterData.ProjectedPosition.z = RLVal(theegg.building_ptr[0]->z_world-LANDZCENTER);
	}


	monstorigin.y = SpuddeMapHeight2(monstorigin.x, monstorigin.z);
	RLFrameSetPosition(monstframe,Wscene,monstorigin.x,monstorigin.y,monstorigin.z);
	if (fromthetop) {
		RLFrameSetOrientation(Robotframe, Wscene, -RLVal(monstorigin.x-Robotorigin.x), RLVal(0.0), -RLVal(monstorigin.z-Robotorigin.z), RLVal(0), RLVal(1), RLVal(0));
		RLFrameSetOrientation(monstframe, Wscene, RLVal(monstorigin.x-Robotorigin.x), RLVal(0.0), RLVal(monstorigin.z-Robotorigin.z), RLVal(0), RLVal(1), RLVal(0));
		RLFrameSetOrientation(Wcamera, Wscene, -RLVal(monstorigin.x-Robotorigin.x), RLVal(0.0), -RLVal(monstorigin.z-Robotorigin.z), RLVal(0), RLVal(1), RLVal(0)); //Add by DOM on 961003
		//RLFrameSetPosition(Wcamera,Wscene,Robotorigin.x,SpuddeMapHeight2(Robotorigin.x, Robotorigin.z)+40,Robotorigin.z); //Hide by DOM on 961003
		FindSpecificBuildings(&missiontarget);
	}
	//FindOneBuilding(&missiontarget, 13);
	MonsterAnimationState=0;
	MonsterMovementState=0;
	//RLFrameAddScale(MonsterScaleFrame, RLCombineReplace, RLVal(0.5+0.5*submonster), RLVal(0.5+0.5*submonster), RLVal(0.5+0.5*submonster));

	if (GameStates.CurrentSubmonster==Alpha) MonsterScaleFactor = RLVal(0.75);
	if (GameStates.CurrentSubmonster==Beta) MonsterScaleFactor = RLVal(1.0);
	if (GameStates.CurrentSubmonster==Gamma) MonsterScaleFactor = RLVal(1.5);

	RLFrameAddScale(MonsterScaleFrame, RLCombineReplace, MonsterScaleFactor, MonsterScaleFactor, MonsterScaleFactor);
	sprintf(datname,"%s\\monmov%d%d.dat",DatPath,GameStates.CurrentLevel,GameStates.CurrentSubmonster);
    shithead=fopen(datname,"rt");
    if(shithead)
      GetMonsterMovementInfo(shithead);
    if(shithead)
      fclose(shithead);

	DefineMonsterMotionConstants();

	sprintf(datname,"%s\\monani%d%d.dat",DatPath,GameStates.CurrentLevel,GameStates.CurrentSubmonster);
    shithead=fopen(datname,"rt");
    if(shithead)
      GetMonsterAnimInfo(shithead);
    if(shithead)
      fclose(shithead);

	DefineMonsterAnimationConstants();

	MonsterData.Volume.max.x=RLMultiply(MonsterBoxXZ[GameStates.CurrentLevel], MonsterScaleFactor);
	MonsterData.Volume.max.y=RLMultiply(MonsterHeight[GameStates.CurrentLevel], MonsterScaleFactor);
	MonsterData.Volume.max.z=RLMultiply(MonsterBoxXZ[GameStates.CurrentLevel], MonsterScaleFactor);
	MonsterData.Volume.min.x=-RLMultiply(MonsterBoxXZ[GameStates.CurrentLevel], MonsterScaleFactor);
	MonsterData.Volume.min.y=(float)0.0;
	MonsterData.Volume.min.z=-RLMultiply(MonsterBoxXZ[GameStates.CurrentLevel], MonsterScaleFactor);

	if (!GameStates.IsNetplay)
      LaunchAllBadCars();
}


//
RLValue MapHeight(int x, int z)
{
    return SpuddeMapHeight(x+LANDXCENTER, z+LANDZCENTER);
}

RLValue SpuddeMapHeight(int x, int y)
{
   RLValue FHeight;
   int IHeight;
   extern RLValue sealevel;

   if ((GameStates.CurrentLevel == 3) && ((x<0) || (y<0) || (x>=LANDXSIZE) || (y>=LANDZSIZE))) return sealevel-RLVal(0.5);
   if (x<0) x+= LANDXSIZE;
   if (y<0) y+= LANDZSIZE;
   if (x>=LANDXSIZE) x-= LANDXSIZE;
   if (y>=LANDZSIZE) y-= LANDZSIZE;

   x = MIN(MAX(x, 0), LANDXSIZE);
   y = MIN(MAX(y, 0), LANDZSIZE);

   x >>= 1;
   y >>= 1;

   IHeight=topo[x+y*LANDZSIZE/2];
   FHeight = RLDivide(RLVal(IHeight),landscale);
   return(FHeight);
}
extern int cuint;
//#define cuint 2
RLValue SpuddeMapHeight2(RLValue x, RLValue y)
{
   RLValue height1, height2, height3, height4;
   int wx, wy;
   RLValue fx, fy, fHeight;
   

   x+=LANDXCENTER;
   y+=LANDZCENTER;

   if (x<0) x+= LANDXSIZE;
   if (y<0) y+= LANDZSIZE;
   if (x>=LANDXSIZE) x-= LANDXSIZE;
   if (y>=LANDZSIZE) y-= LANDZSIZE;

   /*
   wx = RLInt(x);
   wy = RLInt(y);
   fx = RLVal(1) - x + wx;
   fy = RLVal(1) - y + wy;
   height1 = topo[wx+wy*LANDZSIZE];				   //a
   height2 = topo[(wx+1)+wy*LANDZSIZE];			   //b
   height3 = topo[wx+(wy+1)*LANDZSIZE];			   //d
   height4 = topo[(wx+1)+(wy+1)*LANDZSIZE];		   //c

   fHeight = fx*fy*height1 + (fy-fx*fy)*height2	+ (fx-fx*fy)*height3 + (1-fy-fx+fx*fy)*height4;

   return (RLDivide((fHeight),landscale));
   */
   wx = RLInt(x/cuint)*cuint;
   wy = RLInt(y/cuint)*cuint;
   //fx = x - RLVal(wx);
   //fy = y - RLVal(wy);
   fx = RLDivide((RLVal(cuint) - x + wx), RLVal(cuint));
   fy = RLDivide((RLVal(cuint) - y + wy), RLVal(cuint));
   //height1 = topo[wx+wy*LANDZSIZE];				   //a
   //heightcuint = topo[(wx+1)+wy*LANDZSIZE];			   //b
   //height3 = topo[wx+(wy+1)*LANDZSIZE];			   //d
   //height4 = topo[(wx+1)+(wy+1)*LANDZSIZE];		   //c
   height1 = SpuddeMapHeight(wx, wy);				   //a
   height2 = SpuddeMapHeight(wx+cuint, wy); 			   //b
   height3 = SpuddeMapHeight(wx, wy+cuint);				   //d
   height4 = SpuddeMapHeight(wx+cuint, wy+cuint);			   //c

   //fHeight = fx*fy*height1 + (fy-fx*fy)*height2	+ (fx-fx*fy)*height3 + (1-fy-fx+fx*fy)*height4;
	fHeight = (height1*fx + (RLVal(1)-fx)*height2) * fy + (height3*fx + (RLVal(1)-fx)*height4) * (RLVal(1)-fy);
   //return (RLDivide((fHeight),landscale));
   return fHeight;
}

/*
RLValue SpuddeMapHeight1(int t)
{
   int IHeight=topo[t];
   return (RLDivide(RLVal(IHeight),landscale));
}
*/

void SpuddeGetBMPPosition(int *x, int *y, RLValue X, RLValue Z)
{
   *x=RLInt(X)+LANDXCENTER;
   *y=RLInt(Z)+LANDZCENTER;
}


void SpuddeGetWorldPosition(int x, int y, RLValue *X, RLValue *Z)
{
   *X=RLVal(x-LANDXCENTER);
   *Z=RLVal(y-LANDZCENTER);
}


/*
void FreeTexture(RLTexture doomedtex)
{
	RLImage* doomedimage;

	if (RLObjectExists(doomedtex)==RLNoError) {
		doomedimage = RLTextureGetImage(doomedtex);
		RLFree(doomedimage);
		RLObjectDestroy(doomedtex);
	}
}
*/

void SwapRobotNMonster(int whichone)
{
	extern volatile long int *InputIntPtr, *InputIntPtr2; 
	extern volatile long int InputInt, InputInt2;
	extern RLFrame goodguyframe, badguyframe, targetframe;
	extern Caminfo* camerastuff;

	if (whichone) {
		InputIntPtr = &InputInt;
		InputIntPtr2 = &InputInt2;
		goodguyframe = Robotframe;
		badguyframe = monstframe;
	} else {
		InputIntPtr = &InputInt2;
		InputIntPtr2 = &InputInt;
		goodguyframe = monstframe;
		badguyframe = Robotframe;
	}
	SetCameraTarget(camerastuff, goodguyframe);
	//RLFrameAddChild(goodguyframe, camerastuff->target);
	//RLFrameSetOrientation(camerastuff->target, goodguyframe, RLVal(0), RLVal(0), RLVal(1), RLVal(0), RLVal(1), RLVal(0));
}

RLImage* RLLoadRLP(char* name)
{
	typedef struct _YBPaletteEntry {
		unsigned char red;
		unsigned char green;
		unsigned char blue;
	} YBPaletteEntry;

    int     c, s, s1, s2, s3;
    int     width, height, depth;
    char    *index8;
    char    *index16;
    RLImage *image;
    FILE    *in;
    short int w, h, d; 
    YBPaletteEntry pal[256];
	char  filename[127];

	strcpy(filename, BmpPath);
	strcat(filename, "\\");
	strcat(filename, name);

	in = fopen(filename, "rb");

    if (in == NULL) return NULL;
    
    /* header info */
    fread(&w, sizeof(short int), 1, in);
    fread(&h, sizeof(short int), 1, in);
    fread(&d, sizeof(short int), 1, in);

	s1 = sizeof(RLImage);
	s2 = ((w*d)>>3)*h;
	s3 = (1<<d)*sizeof(RLPaletteEntry);
	s  = s1 + s2 + s3;

    if (RLMalloc(&image, s)) return NULL;

     memset(image, 0, sizeof(RLImage));
    image->width  = width  = (int) w;    
    image->height = height = (int) h;  
    image->depth  = depth  = (int) d;   

    if (depth == 16)
	image->rgb = 1;
    else
	image->rgb = 0;

    image->bytes_per_line = (width * depth) >> 3;
    image->buffer1 = (void*) (image+1);
    image->buffer2 = NULL;
    image->palette_size = 1 << image->depth;
    image->palette = (RLPaletteEntry*)((char*)image->buffer1+
		      image->height * image->bytes_per_line);
    image->red_mask = 0xfc;
    image->green_mask = 0xfc;
    image->blue_mask = 0xfc;
    image->alpha_mask = 0xfc;
	
    index8 = index16 = image->buffer1;

    /* image data */
    switch (depth) {
	case 16:
	    fread(index16, sizeof(short int), width*height, in);
	    break; 
		    
	case 8:
	    fread(index8, sizeof(char), width*height, in);
	    break;  
		    
	case 4:
	    fread(index8, sizeof(char), (width*height)/2, in);
	    break;
    }

    /* CLUT  data */
    if (depth == 8 || depth == 4){
	int size = 1 << image->depth;
    
	fread(pal, sizeof(YBPaletteEntry), size, in);
	fclose(in);
	      
	for (c = 0; c < size; c++) {
	    image->palette[c].red = pal[c].red;
	    image->palette[c].green = pal[c].green;
	    image->palette[c].blue = pal[c].blue;
	}      
    }
    return image;
}

int nummallocs = 0, numfrees = 0;
char whereincode[120];
//#define MEMDEBUG
void *LogMalloc( size_t size )
{
	void *address;
#ifdef MEMDEBUG
	FILE* shithead=NULL;
	
	shithead=fopen("memshit.out", "a");
#endif

	address = malloc(size);
#ifdef MEMDEBUG
	if (shithead) fprintf(shithead, "%lu:  size = %d, malloc #%d (Free #%d) in %s\n", address, size, nummallocs, numfrees, whereincode);
	if (shithead) fclose(shithead);

#endif
	nummallocs++;
	return address;
}

void* FakeRealloc(void* oldaddress, size_t howbig)
{
	FILE* shithead=NULL;
	void* newaddress;
	
	newaddress = realloc( oldaddress, howbig );

#ifdef MEMDEBUG
	shithead=fopen("memshit.out", "a");
	if (shithead) fprintf(shithead, "%lu:  realloced to %lu (malloc #%d, free #%d) in %s\n", oldaddress, newaddress, nummallocs, numfrees, whereincode);
	if (shithead) fprintf(shithead, "%lu:  realloced from %lu (malloc #%d, free #%d) in %s\n", newaddress, oldaddress, nummallocs, numfrees, whereincode);
	if (shithead) fclose(shithead);
#endif
	return newaddress;
}

void LogFree( void *memblock )
{
	FILE* shithead=NULL;
	
	free(memblock);

#ifdef MEMDEBUG
	shithead=fopen("memshit.out", "a");
	if (shithead) fprintf(shithead, "%lu:  free #%d (malloc #%d) in %s\n", memblock, numfrees, nummallocs, whereincode);
	if (shithead) fclose(shithead);
#endif
	numfrees++;
}

void KillRLObject(RLObject theobject)
{
	;
	//if (RLObjectExists(theobject)==RLNoError)
	//	RLObjectDestroy(theobject);
}

USERREC preserverec;

void PreserveForTrainer()
{
//	extern long int OverallScore;
//	extern unsigned short RobotStatus[5];

    preserverec.level = GameStates.CurrentLevel;        
    preserverec.score = GameStates.Score;
//    preserverec.mch  = 0;
//    preserverec.mch  = ((RobotStatus[0]&0xff) << 4);
  //  preserverec.mch |= ((RobotStatus[1]&0xff) << 3);
    //preserverec.mch |= ((RobotStatus[2]&0xff) << 2);
//    preserverec.mch |= ((RobotStatus[3]&0xff) << 1);
  //  preserverec.mch |= ((RobotStatus[4]&0xff));
	preserverec.submonster = GameStates.CurrentSubmonster;
}

void RestoreFromTrainer()
{
//	extern long int OverallScore;
//	extern unsigned short RobotStatus[5];

    GameStates.CurrentLevel = preserverec.level;        
    GameStates.Score = preserverec.score;
//    RobotStatus[0] = ((preserverec.mch & 0x10) >> 4); 
  //  RobotStatus[1] = ((preserverec.mch & 0x8) >> 3); 
    //RobotStatus[2] = ((preserverec.mch & 0x4) >> 2); 
//    RobotStatus[3] = ((preserverec.mch & 0x2) >> 1); 
  //  RobotStatus[4] = ((preserverec.mch & 0x1)); 
	GameStates.CurrentSubmonster = preserverec.submonster;
}


RLValue AutoCountdown = RLVal(0.0);

sEnding3DMovieData Ending3DMovie;

//BOOL In3DMovie=0;
extern int RobotMovementState;

int HandleDeath()
{
	int deathstatus = 0;
	extern Caminfo* camerastuff;
	extern int NextLevel;
	extern int RobotLife;
	extern struct _moving_object_data_ 	MonsterData;
	extern struct _moving_object_data_ RobotData;
	extern RLValue DiffFrame;
	RLVector MonsterDirection, RobotPosition, MonsterPosition, force;
	extern volatile long int *InputIntPtr3;				// Input stream from Robot AE
	extern volatile long int *InputIntPtr2;				// Input stream from monster AE

	RLFrameGetPosition(Robotframe, Wscene, &RobotPosition);
	RLFrameGetPosition(monstframe, Wscene, &MonsterPosition);
			
	MonsterDirection.x = MonsterPosition.x -  RobotPosition.x;
	MonsterDirection.y = MonsterPosition.y -  RobotPosition.y;
	MonsterDirection.z = MonsterPosition.z -  RobotPosition.z;

	if (GameStates.RobotLose) 
   {
		if (!GameStates.Is3DMovie) 
		{
			Ending3DMovie.SegCountdown = RLVal(60);
			Ending3DMovie.stage = 0;
			MidCmd = MID_PLAY;
			MidNewIdx = 19;
			BYMidiCenter();
			(*InputIntPtr2)=0;
			GameStates.Is3DMovie=TRUE;
		}
		deathstatus = 1;
		if (!GameStates.IsNetplay)
         KillAllGoodCars();
		(*InputIntPtr3) = 0;
		if (Ending3DMovie.SegCountdown < RLVal(40))
		{
			NextLevel = 1;
			GameStates.Is3DMovie = 0;
			(*InputIntPtr3) = 0;
			Ending3DMovie.stage = 0;
			Ending3DMovie.SegCountdown = RLVal(0);
         return deathstatus;
		}
		switch (Ending3DMovie.stage)
		{
			case 0:
			{
	        	camerastuff->method = CIRCLE;
				camerastuff->next = camerastuff->current = CIRCLING;
				ResetCameraTarget(camerastuff);
				if (!ExplodeARobot())
					Ending3DMovie.stage = 1;
			}
			break;
			case 1:
			{
		      RobotData.RemoveMeFlag=1;
				SetCameraTarget(camerastuff, monstframe);
				ExplodeARobot();
			}
			break;
		}
	}
   else
	if (GameStates.MonsterLose) 
	{
		if (!GameStates.Is3DMovie) 
 		{
			if (GameStates.LevelHonor[GameStates.CurrentLevel])
				MidNewIdx = GameStates.CurrentLevel + 11;	// ONRWIN.MID
			else
			   MidNewIdx = 18;         // MTWIN.MID
			Ending3DMovie.SegCountdown = RLVal(60); 
			Ending3DMovie.stage = 0;
			MidCmd = MID_PLAY;
			BYMidiCenter();
			GameStates.Is3DMovie=1;
			GameStates.CurrentSubmonster = Alpha;
			(*InputIntPtr3)=0;
		}
		MonsterData.RemoveMeFlag = 1;
		deathstatus = 2;
		if (!GameStates.IsNetplay)
         KillAllBadCars();
		switch (Ending3DMovie.stage) {
			case 0:
			case 1:
			{
				extern RLValue MinDistance, FiringRange;

				Ending3DMovie.stage = 1;

	            camerastuff->method=SLUGDRIFT;
				camerastuff->zone=2;
				ResetCameraTarget(camerastuff);

				MinDistance = RLVal(0.2);
				FiringRange = RLVal(5.0);

	         if (AvoidBuildings(RobotPosition, &force))
            {
	            RLValue MonsterDistance = RLVectorModulus(&MonsterDirection);
               MonsterDirection.x += force.x*MonsterDistance;
	            MonsterDirection.y += force.y*MonsterDistance;
	            MonsterDirection.z += force.z*MonsterDistance;
            }

				if (RobotMoveInRange(&MonsterDirection, &MonsterDirection, 1))
				{
					(*InputIntPtr3) = 0;
					camerastuff->zone=7;
					ResetCameraTarget(camerastuff);
					Ending3DMovie.stage = 2;
					Ending3DMovie.timemark = Ending3DMovie.SegCountdown;
					YBPlaySound(Applause);
				}
			} 
			break;
			case 2:
			{
				(*InputIntPtr3) = COMMANDWeakShift|COMMANDMediumShift|COMMANDStrongShift;
	        	camerastuff->method = CIRCLE;
				camerastuff->next = camerastuff->current = CIRCLING;
				if (Ending3DMovie.SegCountdown < Ending3DMovie.timemark - RLVal(8)) 
				{
					Ending3DMovie.stage = 3;
					Ending3DMovie.timemark = Ending3DMovie.SegCountdown;
				}
			}
			break;
			case 3:
			{
				extern RLFrame monstframe;
				int meltingleft;

				(*InputIntPtr3) = 0;
	            camerastuff->method=SLUGDRIFT;
				camerastuff->zone=3;

				meltingleft = MeltAMonster(0);
				if (meltingleft > 15) 
					SetCameraTarget(camerastuff, monstframe);
				else
					camerastuff->method=HUMANEYE;
				if (meltingleft < 7) 
					ResetCameraTarget(camerastuff);
				if (meltingleft < 1)
				{
					Ending3DMovie.stage = 4;
					Ending3DMovie.timemark = Ending3DMovie.SegCountdown;
				}
			}
			break;
			case 4:
			{
				extern RLVector spiritvelocity, globalobjectivevector;

				{
					extern struct _moving_object_data_ spiritdata;
					RLValue mod;
					int wholemod;
					RLVector whereat, whereup;

					RLFrameGetOrientation(Wcamera, Wscene, &whereat, &whereup);

					globalobjectivevector.x = MonsterPosition.x + RLMultiply(RLVal(40), whereat.x);
					globalobjectivevector.y = MonsterPosition.y;
					globalobjectivevector.z = MonsterPosition.z + RLMultiply(RLVal(40), whereat.z);
			
					RLFrameSetPosition(spiritdata.PositioningFrame, Wscene, MonsterPosition.x, MonsterPosition.y, MonsterPosition.z);
					spiritdata.CurrentPosition.x=spiritdata.ProjectedPosition.x = MonsterPosition.x;
					spiritdata.CurrentPosition.y=spiritdata.ProjectedPosition.y = MonsterPosition.y;
					spiritdata.CurrentPosition.z=spiritdata.ProjectedPosition.z = MonsterPosition.z;
					spiritvelocity.x = globalobjectivevector.x - spiritdata.CurrentPosition.x;
					spiritvelocity.y = globalobjectivevector.y - spiritdata.CurrentPosition.y;
					spiritvelocity.z = globalobjectivevector.z - spiritdata.CurrentPosition.z;
					mod = RLVectorModulus(&spiritvelocity);
					wholemod = RLInt(mod);
					spiritvelocity.x /= wholemod;
					spiritvelocity.y /= wholemod;
					spiritvelocity.z /= wholemod;
					spiritdata.RemoveMeFlag=0;

					AddMovingObject(&spiritdata);
				}
				Ending3DMovie.stage = 5;
				Ending3DMovie.timemark = Ending3DMovie.SegCountdown;
			}
			break;
			case 5:
			{
				(*InputIntPtr3) = COMMANDCrouch;
	         camerastuff->method=HUMANEYE;
				camerastuff->zone=2;
				ResetCameraTarget(camerastuff);
				if (Ending3DMovie.SegCountdown < Ending3DMovie.timemark - RLVal(2)) 
				{
					Ending3DMovie.stage = 6;
					Ending3DMovie.timemark = Ending3DMovie.SegCountdown;
				}
			}
			break;
			case 6:
			{
				extern RLValue MinDistance, FiringRange;
	 			extern RLVector spiritvelocity;

				ResetCameraTarget(camerastuff);
				MonsterDirection.x = spiritvelocity.x;
				MonsterDirection.y = spiritvelocity.y;
				MonsterDirection.z = spiritvelocity.z;
				MinDistance = RLVal(0.2);
				FiringRange = RLVal(0.0);
				RobotMoveInRange(&MonsterDirection, &MonsterDirection, 1);
				if (RobotMovementState == RobotFTopSpeed3)
				{
					(*InputIntPtr3) = COMMANDJump;
					Ending3DMovie.stage = 7;
					Ending3DMovie.timemark = Ending3DMovie.SegCountdown;
				}
			}
			break;
			case 7:
			{
				if (Ending3DMovie.SegCountdown < Ending3DMovie.timemark - RLVal(4)) 
				{
					NextLevel = 1;
					GameStates.Is3DMovie = 0;
					(*InputIntPtr3) = 0;
					Ending3DMovie.stage = 0;
					Ending3DMovie.SegCountdown = RLVal(0);
				}
			}
			break;
		}
	}

	if (GameStates.Is3DMovie)
	{
		Ending3DMovie.SegCountdown -= RLDivide(DiffFrame, RLVal(30));
		if (Ending3DMovie.SegCountdown < RLVal(0))
		{
			NextLevel = 1;
			GameStates.Is3DMovie = 0;
			(*InputIntPtr3) = 0;
			Ending3DMovie.stage = 0;
			Ending3DMovie.SegCountdown = RLVal(0);
		}
	}

   if (GameStates.IsAutodemo)
	{
		AutoCountdown -= RLDivide(DiffFrame, RLVal(30));
		if (AutoCountdown < RLVal(0))
		{
			NextLevel = 1;
			GameStates.Is3DMovie = 0;
			(*InputIntPtr3) = 0;
			Ending3DMovie.stage = 0;
			AutoCountdown = RLVal(0);
		}
	}

	return deathstatus;
}

////////////////////////////////////////////////////////////////////////////
// D3d version by DongMin

#define PcxHeaderSize 128L

void FreeMap(void);
BOOL ReplaceAltitudeTexture(const char *name);
BOOL LoadAltitudeTexture(const char *name);

BOOL LoadMap(int level)
{
	BOOL ret;
	if (map_level == GameStates.CurrentLevel)
	{
		return TRUE;
	}

	if (map_level != GameStates.CurrentLevel && map_level != -1) 
	{
		ret = ReplaceAltitudeTexture(MapFile[GameStates.CurrentLevel]);
	}
	else 
	{
	    ret = LoadAltitudeTexture(MapFile[GameStates.CurrentLevel]);  
	}
	map_level = GameStates.CurrentLevel;
	return ret;
}

void FreeMap()
{
	if (map_level == -1)
	{
		return;
	}
	if (topo)
	{
		free(topo);
		topo = NULL;
	}
	map_level = -1;
} 

BOOL ReplaceAltitudeTexture(const char *name)
{
	BOOL ret;
	FreeMap();
	ret = LoadAltitudeTexture(name);
	return ret;
}


BOOL LoadAltitudeTexture(const char *name)
{
	FILE *fp = NULL;
	BYTE Byte;
	PCXHEAD pcxhead;
	int BytesPerLine;
	int i, j, k;
	int times;
	PALETTEENTRY* topopal = NULL;
	int width, height;
	char pcxname[MAX_PATH];

	strcpy(pcxname, BmpPath);
	strcat(pcxname, "\\");
	strcat(pcxname, name);

	if((fp = fopen(pcxname,"rb")) == NULL)
	{
		goto generic_error;
	}

	memset(&pcxhead, 0, PcxHeaderSize);
	if(fread(&pcxhead, PcxHeaderSize, 1, fp) != 1)
		goto generic_error;
	if (pcxhead.BitsPerPixel != 0x08)
		goto generic_error;

	width  = pcxhead.MaxX - pcxhead.MinX + 1;
	height = pcxhead.MaxY - pcxhead.MinY + 1;

	BytesPerLine = pcxhead.BytesPerLine;
	
	if (fseek(fp, PcxHeaderSize, SEEK_SET) != 0)
		goto generic_error;

	topo = (LPSTR)malloc(width * height);
	if (!topo)
		goto generic_error;

	memset(topo, 0, width * height);

	k = 0;
	for(i = 0; i < height; i++)
	{
		j = 0;
		do 
		{
			Byte = fgetc(fp);
			if ((Byte & 0xc0) == 0xc0)
			{
				times = Byte & 0x3f;
				Byte = fgetc(fp);
				while (times--)
				{
					j++;
					topo[k++] = Byte;
				}
			}
			else
			{
				if (j < width)
				{
					j++;
					topo[k++] = Byte ;
				}
				else
				{
					j++;
					topo[k++] = Byte ;
				}
			}
		}while(j < BytesPerLine);
	}	 

	if (fseek(fp, -769L, SEEK_END) != 0)
		goto generic_error;
	if(fread(&Byte,sizeof(unsigned char),1,fp) != 1)
		goto generic_error;
	
	if(Byte != 0x0c)
		goto generic_error;

	topopal = (PALETTEENTRY*)malloc(sizeof(PALETTEENTRY)*256);
	if (!topopal)
		goto generic_error;
	memset(topopal, 0, sizeof(PALETTEENTRY)*256);

	for (i = 0; i < 256; i++)
    {
		topopal[i].peRed=fgetc(fp)>>2;
		topopal[i].peGreen=fgetc(fp)>>2;
		topopal[i].peBlue=fgetc(fp)>>2;
		topopal[i].peFlags=(BYTE)0;
    }
	
	AssignGroundTextures(topopal);
	free(topopal);

	fclose(fp);
	return TRUE;

generic_error:
	BYDumpInfo("********************");
	BYDumpInfo("Couldn't load altitude map:");
	BYDumpInfo(pcxname);
	BYDumpInfo("********************");
	Msg("There is one ERROR while loading alititude texture");
	if(topo)
	{
		free(topo);
		topo = NULL;
	}
	if(topopal)
		free(topopal);
	if(fp)
		fclose(fp);
	return FALSE;
}


#ifdef _DEBUG
void
DumpMemoryStatus(char *where)
{
   MEMORYSTATUS ms;
   char tempbuf[100];
   static int FirstTimeMemoryDumpStatusIsCalled = 0;
   static int FirstMemoryLoad=0, LastMemoryLoad=0;
   static int FirstAvailPhys=0, LastAvailPhys=0;
   static int FirstAvailPageFile=0, LastAvailPageFile=0;
   static int FirstAvailVirtual=0, LastAvailVirtual=0;

   ms.dwLength = sizeof(MEMORYSTATUS);

	GlobalMemoryStatus(&ms);
   if (FirstTimeMemoryDumpStatusIsCalled==0) 
   {
      FirstTimeMemoryDumpStatusIsCalled = 1;
      FirstMemoryLoad = ms.dwMemoryLoad;
      FirstAvailPhys = ms.dwAvailPhys;
      FirstAvailPageFile = ms.dwAvailPageFile;
      FirstAvailVirtual = ms.dwAvailVirtual;
   }

   BYDumpInfo("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
   BYDumpInfo(where);
   BYDumpInfo("                       Current    Since first  Since Last");
   sprintf(tempbuf, "Memory load:           %10d%% %10d%% %10d%%", 
      ms.dwMemoryLoad, ms.dwMemoryLoad - FirstMemoryLoad, ms.dwMemoryLoad - LastMemoryLoad);
   BYDumpInfo(tempbuf);
   sprintf(tempbuf, "Physical memory:       %10d", 
      ms.dwTotalPhys);
   BYDumpInfo(tempbuf);
   sprintf(tempbuf, "Free physical memory:  %10d  %10d  %10d", 
      ms.dwAvailPhys, ms.dwAvailPhys - FirstAvailPhys, ms.dwAvailPhys - LastAvailPhys);
   BYDumpInfo(tempbuf);
//   sprintf(tempbuf, "Page size:             %d", ms.dwTotalPageFile);
//   BYDumpInfo(tempbuf);
//   sprintf(tempbuf, "Free page size:        %d", ms.dwAvailPageFile);
//   BYDumpInfo(tempbuf);
//   sprintf(tempbuf, "User bytes:            %d", ms.dwTotalVirtual);
//   BYDumpInfo(tempbuf);
   sprintf(tempbuf, "Free user bytes:       %10d  %10d  %10d", 
      ms.dwAvailVirtual, ms.dwAvailVirtual - FirstAvailVirtual, ms.dwAvailVirtual - LastAvailVirtual);
   BYDumpInfo(tempbuf);
   BYDumpInfo("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");

   LastMemoryLoad = ms.dwMemoryLoad;
   LastAvailPhys = ms.dwAvailPhys;
   LastAvailPageFile = ms.dwAvailPageFile;
   LastAvailVirtual = ms.dwAvailVirtual;

}
#endif //_DEBUG

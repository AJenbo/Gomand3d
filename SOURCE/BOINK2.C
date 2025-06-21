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
File:           boink.c
Author:         Bruce Abe
Date:           9-26-95
Version:        1.0001



************************************************************************
REVISION HISTORY        (Add Edits and History to top of list).

Edited By:      Bruce Abe
Edited Date:    12-22-95
Changes:
                put in code to allow the monster to walk right through buildings.


Edited By:      Bruce Abe
Edited Date:    12-20-95
Changes:
                put in code to allow the Robot to land on top of a building.


Edited By:      Bruce Abe
Edited Date:    11-14-95
Changes:
                put in code so that when the plasma hits the ground, it
                explodes.

Edited By:      Bruce Abe
Edited Date:    10-6-95
Changes:
                added code to make the defensive sphere gouraud instead
                of wire frame when the Robot gets hit.  Also made the Robot
                and monster lose energy instead of health if they're 
                blocking when they're hit, and the Robot is only knocked
                down or goes into a hit animation if he fails to completely
                block the monster's attack.


Edited By:      Bruce Abe
Edited Date:    10-3-95
Changes:
                changed the size of 3 Robot's swords and the monsters'
                bodies.

Edited By:      Bruce Abe
Edited Date:    10-2-95
Changes:
                changed plasma movement into a homing missile.

Edited By:      Bo Yuan
Edited Date:    9-28-95
Changes:
                added three system header files

Edited By:      Bruce Abe
Edited Date:    9-28-95
Changes:
                changed VERSION_NUMBER from 1.0 to 1.0002
                made the monster unable to hit the Robot if the Robot's dead,
                and vice versa.

Edited By:      Bruce Abe
Edited Date:    9-27-95
Changes:
                changed VERSION_NUMBER from 1.0 to 1.0001
                changed monster loading so baddies other than
				Roggosh can fire weapons and get hit.


************************************************************************
$Header:   H:/pvcs/pvcsproj/gomand3d.prj/boink2.c_v   1.37   10 Apr 1997 11:03:36   JEREMIAH  $

$Log:   H:/pvcs/pvcsproj/gomand3d.prj/boink2.c_v  $
 * 
 *    Rev 1.37   10 Apr 1997 11:03:36   JEREMIAH
 * Load semitransparent resources for 
 * SEMIFANCY transparency type.
 * 
 *    Rev 1.36   07 Apr 1997 12:47:00   BRUCE
 * changed calls to play the sound 
 * MonsterFallDown to calls to play the sound
 * MonsterGetHit when the monster is hit.
 * 
 *    Rev 1.35   25 Mar 1997 17:03:18   BRUCE
 * Added error message if there are more
 * moving objects than the system will allow
 * 
 * Put in kludge to get rid (hopefully) of the 
 * disappearing peashooter.
 * 
 *    Rev 1.33   21 Mar 1997 14:56:22   BRUCE
 * Play mpwr.wav when the monster gains
 * energy.
 * 
 *    Rev 1.32   21 Mar 1997 10:41:42   BRUCE
 * When removing the Robot's swords, I set
 * numoffensivetubes to zero, to fix crash bug.
 * 
 *    Rev 1.31   20 Mar 1997 17:06:20   BRUCE
 * removed diagnostic printouts.
 * 
 *    Rev 1.30   20 Mar 1997 16:56:46   BRUCE
 * Changed HomingMotionFunction so that
 * the homers change altitude gradually, and
 * home in on the monster's chest.
 * 
 *    Rev 1.29   20 Mar 1997 15:29:56   BRUCE
 * inactivated Robot's swords if the Robot
 * gets hit.
 * 
 *    Rev 1.28   Mar 20 1997 12:19:24   JEREMIAH
 * Removed improper initialization of 
 * SpinMultiplier variables.
 * 
 *    Rev 1.27   19 Mar 1997 21:23:54   BRUCE
 * MonsterFallDownSpin is now used to set
 * MonsterTheta, which is how fast the
 * monster spins when hit.
 * RobotFallDownSpin is now used to set
 * RobotTheta, which is how fast the Robot
 * spins when hit.
 * 
 * 
 *    Rev 1.26   12 Mar 1997 13:32:40   BRUCE
 * added MonsterFalldownThreshold to 
 * the dat files, as the minimal damage
 * needed to knock down the monster.
 * 
 *    Rev 1.25   12 Mar 1997 12:43:00   JEREMIAH
 * Load new pea shooter resource if 
 * semi-transparency is used.
 * 
 *    Rev 1.24   11 Mar 1997 15:38:40   BRUCE
 * Major overhaul of handleRobothit and
 * handlemonsterhit, and minor kluge in the
 * ClockworkGod functions, so that the Robot
 * and monster both fall down when they 
 * collide with each other,  and so that they 
 * fall down in other circumstances based
 * on how much damage they take, or what
 * state they were in, etc.  Also minor fixes
 * to handle landing on buildings, turning off
 * jets, playing appropriate sounds at 
 * appropriate times, etc.
 * 
 * This is basically a last ditch attempt to 
 * prevent us from ever completing Goman.
 * 
 *    Rev 1.23   07 Mar 1997 19:20:42   JEREMIAH
 * Fixed timing of Robot death.
 * Fixed conditions of monster death.
 * 
 *    Rev 1.22   06 Mar 1997 10:50:48   JEREMIAH
 * Reintroduced small gethits for monsters
 * when damage is below 10.
 * Increased peashooter mass to 50.0
 * 
 *    Rev 1.21   05 Mar 1997 18:18:02   BRUCE
 * changed the orientation of the Robot's
 * shield sphere.
 * 
 *    Rev 1.20   25 Feb 1997 21:15:34   BRUCE
 * put in peashooter min energy.
 * 
 *    Rev 1.19   25 Feb 1997 00:02:14   BRUCE
 * removed fliptexturecoords call from 
 * Gaingris' bomb that should have caused
 * massive crash.
 * 
 * Added beaucoup de variables to the 
 * monster's dat files
 * 
 *    Rev 1.18   21 Feb 1997 15:16:02   JEREMIAH
 * Loosened comparisons of RobotLife to 0
 * to be <= instead of = or <.
 * 
 *    Rev 1.17   20 Feb 1997 17:57:48   JEREMIAH
 * Added code to prevent falldowns when
 * Robot is in a pause1 animation state.
 * 
 *    Rev 1.16   20 Feb 1997 09:29:12   JEREMIAH
 * Fixed peashooter energy drain so it is only
 * drained when a peashooter is sucessfully
 * launched.
 * 
 *    Rev 1.15   14 Feb 1997 23:59:32   BRUCE
 * morged versions 1.13.1.1 and 1.14
 * 
 *    Rev 1.13.1.1   14 Feb 1997 15:50:58   JEREMIAH
 * Changed by Bo.
 * - changed array size of RobotBoxXZ and RobotHeight.  
 * 
 * 
 *    Rev 1.13.1.0   14 Feb 1997 11:21:28   JEREMIAH
 * Stopped sharing one frame among all
 * pea shooters.  
 * 
 *    Rev 1.14   14 Feb 1997 19:16:58   BRUCE
 * removed _47TEK_RL_ code
 * removed _ITC_D3D_ conditional
 * replaced level with GameStates.CurrentLevel
 * replaced netPlay with GameStates.isNetplay
 * 
 *    Rev 1.13   07 Feb 1997 09:17:12   BRUCE
 * cleared ZappaOnScreen for the beginning
 * of the level, to remove autodemo zappa
 * disappearing bug.
 * 
 *    Rev 1.12   07 Feb 1997 08:40:24   BRUCE
 * changed HomerOnScreen so that if the 
 * level ends with a homer on screen (Which
 * should rarely happen outside autodemo)
 * the homer won't be missing the rest of the 
 * game.
 * 
 *    Rev 1.11   06 Feb 1997 08:10:14   BRUCE
 * took control of which Robot.
 * 
 *    Rev 1.10   31 Jan 1997 15:42:10   BRUCE
 * Added BootRobotFrames and 
 * BootMonsterFrames to hopefully get rid
 * of camera scaling bug.
 * 
 *    Rev 1.9   20 Jan 1997 18:35:50   BRUCE
 * Added code to make falldowns cumulative
 * and not to change the animation state if 
 * the monster or Robot is already falling.
 * Also, we'll only play a gethit sound the first
 * time a collision occurs, so we won't have
 * the machine gun get hit sound.
 * 
 *    Rev 1.8   16 Jan 1997 22:41:26   BRUCE
 * Massive changes to collision detection.
 * Momentum now works, I hope.
 * Robot will be moved backward if hit, no
 * matter what state it is in.
 * 
 *    Rev 1.7   09 Jan 1997 00:29:56   BRUCE
 * fixed concussion weapon visual.
 * 
 *    Rev 1.6   06 Jan 1997 13:37:32   JEREMIAH
 * Rekludged the momentum equations further
 * to avoid the square root of a negative 
 * number trap.  
 * 
 * 
 *    Rev 1.5   Dec 19 1996 16:32:26   JEREMIAH
 * made peashooter energy drain a datable
 * value
 * 
 *    Rev 1.4   Dec 19 1996 15:30:04   JEREMIAH
 * Rekludged the momentum equations
 * to avoid the square root of a negative 
 * number trap.
 * 
 *    Rev 1.3   Dec 19 1996 10:38:08   JEREMIAH
 * Changed by Tim.  Adjusted size of 
 * concussion weapon.
 * 
 *    Rev 1.2   18 Dec 1996 08:57:38   BRUCE
 * Use HomerAngle instead of HomerSine and
 * HomerCosine to determine steering, so we
 * can adjust for framerate.  Also, used
 * HomerCloseEnough instead of magic number
 * 0.1, so that it can be read from a dat file.
 * 
 *    Rev 1.1   16 Dec 1996 10:47:56   JEREMIAH
 * Changed by ITC.  Added code for netplay.
 * 
 *    Rev 1.0   Oct 18 1996 15:58:10   JEREMIAH
 *  
 * 
 *    Rev 2.20   Apr 10 1996 13:49:12   JEREMIAH
 * Adjusted bounding box of trainer robot.
 * 
 *    Rev 2.19   Mar 19 1996 18:06:22   JEREMIAH
 * Fixed incorrect sound effect 
 * 
 *    Rev 2.18   Mar 15 1996 15:42:56   JEREMIAH
 * Increased weapons masses.
 * 
 *    Rev 2.17   Mar 15 1996 10:59:22   JEREMIAH
 * Moved some constants to dat files.
 * 
 * Disabled collisions if character in falldown
 * or getup.
 * 
 *    Rev 2.16   Mar 14 1996 10:43:24   JEREMIAH
 * Moved sound effect call for building
 * destruction to bldgboom.c
 * 
 * 
 *    Rev 2.15   Mar 12 1996 12:02:56   JEREMIAH
 * Plugged memory leak.
 * 
 * Added peashooter energy drain.
 * 
 * Restored concussion graphic.
 * 
 *    Rev 2.14   Mar 09 1996 11:58:14   JEREMIAH
 * Removed redundant calls of 
 * RLIMInitialiseSurfaceInfo in attempt to
 * reduce memory leaks.
 * 
 *    Rev 2.13   Mar 08 1996 08:40:54   JEREMIAH
 * Eliminated Free'ing and re-Malloc'ing 
 * of texture memory by calling ReplaceGif()
 * to reload existing textures.
 * 
 *    Rev 2.12   Mar 07 1996 10:01:44   JEREMIAH
 * Special case in momentum resolution
 * for Gaingris bomb.
 * 
 * Fix for building damage levels.
 * 
 * Fix for shield animation on gethit.
 * 
 *    Rev 2.11   Mar 05 1996 15:08:40   JEREMIAH
 * Eliminated multiple texture loading on 
 * Robot's pea shooter.
 * 
 *    Rev 2.10   Mar 04 1996 13:44:10   JEREMIAH
 * Bug fixes to collision resolution.
 * 
 * Velocity to sparklies.
 * 
 *    Rev 2.9   Feb 28 1996 16:18:36   JEREMIAH
 * Fixed bug of Robot getting hit when it hits
 * monster with swords.
 * 
 *    Rev 2.8   Feb 27 1996 18:12:44   JEREMIAH
 * Added individualized bounding boxes
 * for all characters.
 * 
 *    Rev 2.7   Feb 24 1996 18:29:20   JEREMIAH
 * Put all momentum calculations in function
 * ResolveMomentum() and revamped 
 * formulae.
 * 
 * Put RobotArmor and MonsterArmor into
 * damage calculations.
 * 
 *    Rev 2.5   Feb 23 1996 09:23:12   JEREMIAH
 * Added trainer text for visor beam.
 * 
 *    Rev 2.4   Feb 22 1996 14:44:54   JEREMIAH
 * Made new attempt at collision resolution
 * formulae.
 * 
 * Removed chesthit reaction to collisions.
 * 
 *    Rev 2.3   Feb 20 1996 18:16:08   JEREMIAH
 * Added tailzapper-like weapon to the 
 * Robots to replace old pea shooter.
 * 
 *    Rev 2.2   Feb 19 1996 10:30:38   JEREMIAH
 * Adjusted momentum equations (not fixed
 * yet)
 * 
 * Adjusted masses of weapons.
 * 
 *    Rev 2.1   Feb 18 1996 12:02:04   JEREMIAH
 * Added momentum calculations (needs 
 * refinement) to collision functions.
 * 
 * Cleaned up building collisions and 
 * concussion weapon movement function.
 * 
 *    Rev 2.0   Feb 09 1996 10:31:58   JEREMIAH
 * Promoted to 2.0 for final QA.
 * 
 *    Rev 1.12   Feb 08 1996 16:16:12   JEREMIAH
 * Ensured defensive sphere doesn't
 * disappear.
 * 
 *    Rev 1.11   Feb 06 1996 18:17:22   JEREMIAH
 * Added rotation to the knockbacks for both
 * Robot and monster.
 * 
 *    Rev 1.10   Feb 01 1996 12:01:58   JEREMIAH
 * Altered snowball attack behavior to
 * grow as it gathers snow.
 * 
 *    Rev 1.9   Jan 29 1996 09:43:28   JEREMIAH
 * Modified damage to monsters to decrease
 * with higher levels and submonsters.
 * 
 *    Rev 1.8   Jan 19 1996 18:14:20   BRUCE
 * Fixed the Robot's concussion weapon
 * 
 *    Rev 1.7   Jan 18 1996 17:54:30   BRUCE
 * fixed Gaingris' bomb
 * 
 *    Rev 1.6   Jan 18 1996 13:28:50   BRUCE
 * changed cowboydeathmarch's collisionvector.
 * 
 *    Rev 1.5   Jan 18 1996 11:40:58   JEREMIAH
 * Added PeaShooter functions.
 * 
 *    Rev 1.4   Jan 17 1996 07:29:04   BRUCE
 * Added Kothos Snowball, partially debugged
 * Gaingris nuke.
 * 
 *    Rev 1.3   Jan 15 1996 20:56:10   BRUCE
 * Just to see if it works
 * 
 *    Rev 1.2   Jan 15 1996 14:12:54   KEVIN
 * Adding Merged File Into Project
 * 
 * 
 *    Rev 1.1   Jan 15 1996 13:47:08   KEVIN
 * Added the $Header and $Log Keywords for
 * PVCS Expansion.
 * 
 ***********************************************************************/
#pragma warning( disable : 4244)
#pragma warning( disable : 4101)

#define BruceNotSpudde

//#define Expressive
#ifdef MINIWIN
#include "miniwin/windows.h"
#else
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#endif
#include <stdio.h>
#include <math.h>


#include "rl2d3d.h"
#include "wrapper.h"

#include "boink.h"
#include "Robotanim.h"
#include "Robotmove.h"
#include "ybsnd.h"
#include "timing.h"
#include "gosys.h"
#include "keycom.h"
#include "spudbmp.h"
#include "monmove.h"
#include "monanim.h"
#include "plasma.h"
#include "spritlib.h"
#include "psystem.h"
#include "clutter.h"
#include "building.h"
#include "bldgboom.h"
#include "imisc.h"
#include "global.h"
#include "d3dappi.h"

#ifndef BruceNotSpudde
//#include "psxsound.h"
#endif
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

#define MaxMovingObjects 32
//#define MaxMovingObjects 100

#define BuildingBumpAmount (RLVal(0.15))

#define LandOnBuilding 1
#define FallForwardOnBuilding 2
#define SlideDownSideOfBuilding 3
#define RunIntoBuilding 4
#define MySwordHitAMonster 47

//Add by Eric 11/12/96
#include "netplay.h"
//end of Eric

extern int RobotLife;
extern int MnstLife;
extern int RobotEngy;
extern int MnstEngy;
//extern int level;
extern RLValue RobotMaxFVel3, RobotMaxFVel2, RobotMaxFVel1;
extern int RobotOnBuilding;
extern int RobotMotionDamage;
extern int MonsterMotionDamage;
extern int RobotSlideNextAnimation;
building *RobotBuilding;
extern long int Population;
RLValue MonsterZapMass=RLVal(30);

extern RLValue HomerAngle;
extern RLValue HomerCloseEnough;
extern RLValue RobotSpinMultiplier;
extern RLValue MonsterSpinMultiplier;
extern int PeaShooterEnergyDrain=640;
extern RLVector RobotPosition;
//add by Helen 11/16/96
extern void  LocalAIZappaLatencyFunction(MovingObjectData movedata);      
extern void  LocalAICussinLatencyFunction(MovingObjectData  movedata);
extern void  LocalAIHomingLatencyFunction(MovingObjectData  movedata);
extern void  LocalAIRapidFireLatencyFunction(MovingObjectData  movedata);

//#include "localai.h"
extern BOOL PlayAsMonster;
extern BOOL LocalAIWorkingFlag;
//end Helen


char RobotChestName[16] = "x3ds_schest";
char RobotPelvisName[16] = "x3ds_spelvis";
char RobotHeadName[16] = "x3ds_shead";
char RobotRightFootName[16] = "x3ds_sritefoot";
char RobotLeftFootName[16] = "x3ds_sleftfoot";
char RobotRightSwordName[16] = "x3ds_skatana";
char RobotLeftSwordName[16] = "x3ds_swakizashi";

char MonsterChestName[16] = "x3ds_body";
char MonsterHeadName[16] = "x3ds_head";
char MonsterRightHandName[16] = "x3ds_riteclaw1";
char MonsterLeftHandName[16] = "x3ds_leftclaw1";
char MonsterWeaponName[16] = "x3ds_plasmatail";

void HandleMonsterHit(MovingObjectData movedata);
void HandleRobotHit(MovingObjectData movedata);
void HomingMotionFunction(MovingObjectData movedata);
void PlasmaGotHit(MovingObjectData movedata);
void RapidFireMotionFunction(MovingObjectData movedata);
void RapidFireGotHit(MovingObjectData movedata);
void CussinMotionFunction(MovingObjectData movedata);
void CussinGotHit(MovingObjectData movedata);
void NRingsMotionFunction(MovingObjectData movedata);
void NRingsGotHit(MovingObjectData movedata);
void ZappaMotionFunction(MovingObjectData movedata);
void RobotZappaMotionFunction(MovingObjectData movedata);
void ZappaGotHit(MovingObjectData movedata);
void RobotZappaGotHit(MovingObjectData movedata);
void BombMotionFunction(MovingObjectData movedata);
void BombGotHit(MovingObjectData movedata);
void SnowballMotionFunction(MovingObjectData movedata);
void SnowballGotHit(MovingObjectData movedata);
int AddMovingObject(MovingObjectData newmover);

extern FrameSetQuality(RLFrame parent,RLRenderQuality quals);
visible_buildings SplodeBuildings;  // Structure of Collision Buildings.


static int HomerDamage = 10;
static RLValue HomerRadius = RLVal(1.3);
static int RapidFireDamage = 5;
static RLValue RapidFireRadius = RLVal(0.7);
int PeaShooterDamage = 1;
int PeaShooterDuration = 30;
int PeaShooterInterval = 5;
static RLValue PeaShooterRadius = RLVal(0.3);
int ConcussionDamage = 5;
RLValue ConcussionRadius = RLVal(0.7);
int MonsterZapDamage = 20;
RLValue MonsterZapRadius = RLVal(1.0);
RLValue MonsterZapLength = RLVal(7.0);
static int RobotZapDamage = 2;
RLValue RobotZapRadius = RLVal(0.25);
RLValue RobotZapLength = RLVal(7.0);
extern int NeallothRingsDamage;
RLValue NeallothRingsRadius = RLVal(0.7);
RLValue GaingrisRadius = RLVal(0.6);
RLValue GaingrisNukeVelocity = RLVal(0.9);
RLValue GaingrisNukeInitRadius = RLVal(1.0);
RLValue GaingrisNukeMaxRadius= RLVal(50.0);

RLValue KothosSnowballInitRadius=RLVal(0.5);
RLValue KothosSnowballGrowthRate=RLVal(0.1);
RLValue KothosSnowballDuration = RLVal(20.0);
int KothosSnowballDamage = 10;
extern RLVector KothosSnowballVelocity;
RLValue KSnowballGradientFactor=-RLVal(0.25);
//RLValue KothosRadius = RLVal(1.4);

extern int MonsterFalldownThreshold;

static RLValue RobotBoxXZ[] = 
{ 
	
	RLVal(0.45), 	// Saber
	RLVal(0.40),  	// Stealth
	RLVal(0.7), 	// MerRobot
	RLVal(0.50), 	// Kata
	RLVal(0.7)	 	// Kaber
};

static RLValue RobotHeight[] = 
{
	
	RLVal(1.7),		// Saber
	RLVal(1.3),		// Stealth
	RLVal(2.0),		// MerRobot
	RLVal(1.8),		// Kata
	RLVal(2.2)		// Kaber
};

RLValue MonsterBoxXZ[7] = 
{
	RLVal(1.0),		// Trainer
	RLVal(0.7), 	// Roggosh
	RLVal(0.8),		// Kothos
	RLVal(0.8),		// Tolgo
	RLVal(1.0),		// Shagtoq
	RLVal(0.7),		// Nealloth
	RLVal(1.0)		// Gaingris
};

RLValue MonsterHeight[7] = 
{
	RLVal(4.0),		// Trainer
	RLVal(1.5), 	// Roggosh
	RLVal(2.0),		// Kothos
	RLVal(2.8),		// Tolgo
	RLVal(1.7),		// Shagtoq
	RLVal(2.0),		// Nealloth
	RLVal(3.0)		// Gaingris
};

static int RobotSmallHit = 5;

//modify by Helen 11/16/96
//static RLValue CruisingUpperAltitude = RLVal(1.5);
//static RLValue CruisingLowerAltitude = RLVal(0.75);
//static RLValue RobotCussinMass = RLVal(500);
RLValue CruisingUpperAltitude = RLVal(0.6);
RLValue CruisingLowerAltitude = RLVal(0.75);
RLValue CruisingYVelocity = RLVal(0.2);
RLValue RobotCussinMass = RLVal(500);
//end Helen

extern RLValue MonsterFallDownSpin;
extern RLValue RobotArmor;
extern RLValue MonsterArmor;
RLVector SixShooterDirection[NumberOfSixShooters];
extern RLValue RobotHomerMass;

/*
typedef enum
{
   UnknownStyle,
   SabreStyle,
   KataStyle,
   StealthStyle,
   KaberStyle,
   MerStyle
}RobotStyle;

RobotStyle WhichKindOfRobot=UnknownStyle;
*/
RLVector MonsterFallDownDirection;
RLVector RobotFallDownDirection;
extern RLFrame behindthescene;
extern RLFrame RobotBlockSphere;
extern Psystem *SixShooter;
extern Psystem *Cussin;
extern Psystem *NeallothRings;
extern RLFrame BombSphere;
#ifdef VISUAL_BBOX
RLFrame Robotboxyframe, monsterboxyframe;
#endif
//#ifndef BruceNotSpudde
extern RLFrame Robotframe,monstframe;
extern RLFrame 
Mexplode;
extern RLFrame Monsplode;
extern ExplosionData MXdata, MonXdata;
extern Psystem *Robotexplosion;
extern Psystem *monsterexplosion;
extern RLFrame Robotspew, monstspew;
//extern PlasmaData Robotspewdata, monstspewdata;
extern RLVector Robotspewvelocity;
extern RLValue HomerHowLong;
extern RLValue RapidFireHowLong[NumberOfSixShooters];
extern RLValue PeaShooterHowLong[NumberOfPeaShooters];
extern RLValue CussinHowLong[NumberOfSixShooters];
extern RLVector CussinWhichWay;
extern RLVector CussinUp;
extern RLValue NRingsHowLong[NumberOfSixShooters];
extern BOOL HomerOnScreen;
extern int ZappaHowLong;
extern int BombHowLong;
extern RLValue RobotZappaHowLong[];
extern int RobotZappaOnScreen;
extern int ZappaOnScreen;
extern RLValue RFSpeed;
extern RLValue NeallothRingsSpeed;
extern int PeaShooterEnergyMinimum;

extern int RobotAttackFerocity;
extern int MonsterAttackFerocity;
extern int BlockCountDown;
typedef struct _moving_object_data_ *MovingObjectData;

typedef void (*AnimationFunction) (void);
typedef void (*MotionFunction) (MovingObjectData movedata);
typedef void (*CollisionResolutionFunction) (MovingObjectData movedata);

struct _moving_object_data_ RobotData;
struct _moving_object_data_ MonsterData;
struct _moving_object_data_ RobotHomerData;
struct _moving_object_data_ RobotRapidFireData[NumberOfSixShooters];
struct _moving_object_data_ RobotCussinData[NumberOfSixShooters];
struct _moving_object_data_ NeallothRingsData[NumberOfSixShooters];
struct _moving_object_data_ BombData;
struct _moving_object_data_ MonsterZappaData;
struct _moving_object_data_ RobotZappaData[6];

MovingObjectData MovingObjects[MaxMovingObjects];
int NumMovingObjects;
static visible_buildings CollideBuildings;  

void GetBuildingsInArea(visible_buildings *vis_bldgs, RLValue minx, RLValue minz, RLValue maxx, RLValue maxz);

void ResolveMomentum(MovingObjectData thisun, MovingObjectData thatun)
{
	RLVector v1, v2, p1, p2, p1p, p2p, p, point1, point2;
	RLValue m1, m2, pmag, p1pmag2, p2pmag2, pmag2, p1mag2, p2mag2, sepmag;
	RLVector sep;
	RLValue d, c, dot1a, dot1b, dot2a, dot2b;
	RLValue Energy, QuadA, QuadB, QuadC, Disc, SqrtDisc, Const1, Const2, Const;
	RLValue VDiff,MaxC,MinC;
	RLVector parallel, perpendicular, p1pa, p1pb, p2pa, p2pb;
	RLValue P1MAG1,P1MAG2,P2MAG1,P2MAG2;
	extern RLValue RobotFallDownSpin, MonsterFallDownSpin;
	char string[256];
	int Case1,Case2;
	Const1 = Const2 = -47.474747;

	m1 = thisun->mass;
	m2 = thatun->mass;

	// find unit vector pointing from thisun to thatun (1 to 2)
	sep.x = (thatun->CurrentPosition.x - thisun->CurrentPosition.x);
	sep.z = (thatun->CurrentPosition.z - thisun->CurrentPosition.z);
	sep.y = RLVal(0);
	//RLVectorNormalise(&sep);
	sepmag = RLVectorModulus(&sep);
	if (sepmag)
	{
		RLVectorScale(&sep, &sep, RLDivide(RLVal(1), sepmag));
	}
	else
	{
		return;
	}

	// sets velocities
	if ((thisun->NumOffensiveTubes==0) || (thisun->NumOffensiveSpheres!=0))
	{
		RLVectorSubtract(&v1, &(thisun->ProjectedPosition), &(thisun->CurrentPosition));
		RLVectorScale(&v1, &v1, RLDivide(RLVal(1), DiffFrame));
	}
	else 
	{
		RLFrameTransform(thisun->PositioningFrame, &point1, &(thisun->OffensiveTubeList[0]->point1));
		RLFrameTransform(thisun->PositioningFrame, &point2, &(thisun->OffensiveTubeList[0]->point2));
		RLVectorSubtract(&v1, &point2, &point1);
	}
	if (thatun == &BombData)
	{
		m1 = RLDivide(RLVal(5000), sepmag);
		v1.x = RLMultiply3(-sep.x, DiffFrame, RLVal(0.9));
		v1.z = RLMultiply3(-sep.z, DiffFrame, RLVal(0.9));
	}
	
	if ((thatun->NumOffensiveTubes==0) || (thatun->NumOffensiveSpheres!=0))
	{
		RLVectorSubtract(&v2, &(thatun->ProjectedPosition), 
			&(thatun->CurrentPosition));
		RLVectorScale(&v2, &v2, RLDivide(RLVal(1), DiffFrame));
	}
	else 
	{
		RLFrameTransform(thatun->PositioningFrame, &point1, 
			&(thatun->OffensiveTubeList[0]->point1));
		RLFrameTransform(thatun->PositioningFrame, &point2, 
			&(thatun->OffensiveTubeList[0]->point2));
		RLVectorSubtract(&v2, &point2, &point1);
	}
	if (thisun == &BombData)
	{
		m2 = RLDivide(RLVal(5000), sepmag);
		v2.x = RLMultiply3(sep.x, DiffFrame, RLVal(0.9));
		v2.z = RLMultiply3(sep.z, DiffFrame, RLVal(0.9));
	}

	v1.y = v2.y = RLVal(0);
	// sets momenta
	RLVectorScale(&p1, &v1, m1);
	RLVectorScale(&p2, &v2, m2);
	RLVectorAdd(&p, &p1, &p2);
	pmag2 = RLVectorDotProduct(&p, &p);
	
	if (pmag2 < RLVal(0.1))			// if net momentum is null
	{
		// swap momenta
		if (m1) 
		{
			RLVectorScale(&(thisun->CollisionVector), &p2, RLDivide(RLVal(1), m1));
		}
		if (m2) 
		{
			RLVectorScale(&(thatun->CollisionVector), &p1, RLDivide(RLVal(1), m2));
		}
		RobotFallDownSpin = MonsterFallDownSpin = 0;
		return;
	}
//	VDiff=sqrt( (v1.x-v2.x)*(v1.x-v2.x) + (v1.z-v2.z)*(v1.z-v2.z) );
	pmag = RLVectorModulus(&p);
	p1mag2 = RLVectorDotProduct(&p1, &p1);
	p2mag2 = RLVectorDotProduct(&p2, &p2);

	Energy = (m1*(v1.x*v1.x + v1.z*v1.z)/2) + (m2*(v2.x*v2.x + v2.z*v2.z)/2);
	QuadA = Energy*Energy*(m1+m2)*(m1+m2)*4;
	QuadB = 4*Energy*( pmag2*(m2-m1) - 2*Energy*m2*(m1+m2) );
	QuadC = pmag2 - 2*Energy*m2 ;
	QuadC = QuadC*QuadC;
	MaxC = m1/(m1+m2);
	MinC = m2/(m1+m2);

	Disc = QuadB*QuadB - 4*QuadA*QuadC;
	if(Disc<0)
	{
		BYDumpInfo("\n**************************\n");
		BYDumpInfo("Discriminant is negative.\n");
		sprintf(string, "QuadA = %f, QuadB = %f, QuadC = %f\n",QuadA,QuadB,QuadC);
		BYDumpInfo(string);
		sprintf(string, "Energy = %f, pmag2 = %f, m1 = %f, m2 = %f\n",Energy,pmag2,m1,m2);
		BYDumpInfo(string);
		sprintf(string,"p1mag2 = %f, p2mag2 = %f\n",p1mag2,p2mag2);
		BYDumpInfo(string);
		sprintf(string, "v1 = (%.3f, %.3f, %.3f), v2 = (%.3f, %.3f, %.3f)\n",v1.x,v1.y,v1.z,v2.x,v2.y,v2.z);
		BYDumpInfo(string);
		BYDumpInfo("**************************\n\n");
		Const = MinC;


	}
	else if(Disc==0)
	{
		BYDumpInfo("\n**************************\n");
		BYDumpInfo("Discriminant is zero.\n");
		sprintf(string, "QuadA = %f, QuadB = %f, QuadC = %f\n",QuadA,QuadB,QuadC);
		BYDumpInfo(string);
		sprintf(string, "Energy = %f, pmag2 = %f, m1 = %f, m2 = %f\n",Energy,pmag2,m1,m2);
		BYDumpInfo(string);
		sprintf(string,"p1mag2 = %f, p2mag2 = %f\n",p1mag2,p2mag2);
		BYDumpInfo(string);
		sprintf(string, "v1 = (%.3f, %.3f, %.3f), v2 = (%.3f, %.3f, %.3f)\n",v1.x,v1.y,v1.z,v2.x,v2.y,v2.z);
		BYDumpInfo(string);

		Const2 = Const1 = Const = -QuadB/(2*QuadA);
		if(Const>1 || Const<0)
		{
			sprintf(string,"Const= %f is outside the bounds,\n",Const);
			BYDumpInfo(string);
		}

		BYDumpInfo("**************************\n\n");

	}
	else
	{
		SqrtDisc=sqrt(Disc);
		Const1=(-QuadB + SqrtDisc)/(2*QuadA);
		Const2=(-QuadB - SqrtDisc)/(2*QuadA);
		if(Const1>1 || Const1<0)
		{
			if(Const1>1&&Const1<1.0001)
			{
				Const1=1;
			}
			else
			{
				BYDumpInfo("\n**************************\n");
				sprintf(string,"Const1= %f is outside the bounds\n",Const1);
				BYDumpInfo(string);
				sprintf(string,"QuadA = %f, QuadB = %f, QuadC = %f\n",QuadA,QuadB,QuadC);
				BYDumpInfo(string);
				sprintf(string,"sqrtDisc = %f\n",SqrtDisc);
				BYDumpInfo(string);
				sprintf(string,"m1 = %f, m2 = %f\n",m1,m2);
				BYDumpInfo(string);
				sprintf(string, "v1 = (%.3f, %.3f, %.3f), v2 = (%.3f, %.3f, %.3f)\n",v1.x,v1.y,v1.z,v2.x,v2.y,v2.z);
				BYDumpInfo(string);
				BYDumpInfo("**************************\n\n");
			}
		}
		if(Const2>1 || Const2<0)
		{
			BYDumpInfo("\n**************************\n");
			sprintf(string,"Const2= %f is outside the bounds\n",Const2);
			BYDumpInfo(string);
			sprintf(string,"QuadA = %f, QuadB = %f, QuadC = %f\n",QuadA,QuadB,QuadC);
			BYDumpInfo(string);
			sprintf(string,"sqrtDisc = %f\n",SqrtDisc);
			BYDumpInfo(string);
			sprintf(string,"m1 = %d, m2 = %d\n",m1,m2);
			BYDumpInfo(string);
			sprintf(string, "v1 = (%.3f, %.3f, %.3f), v2 = (%.3f, %.3f, %.3f)\n",v1.x,v1.y,v1.z,v2.x,v2.y,v2.z);
			BYDumpInfo(string);
			BYDumpInfo("**************************\n\n");
		}
		if(Const1<=Const2)
		{
			BYDumpInfo("\n**************************\n");
			sprintf(string,"Const1 = %f is smaller than Const2 = %f\n",Const1,Const2);
			BYDumpInfo(string);
			BYDumpInfo("**************************\n\n");
		}


		P1MAG1 = sqrt(Const1*(p1mag2 + (m1 / m2) * p2mag2));
		P2MAG1 = sqrt((1-Const1)*(p2mag2 + (m2 / m1) * p1mag2));

		P1MAG2 = sqrt(Const2*(p1mag2 + (m1 / m2) * p2mag2));
		P2MAG2 = sqrt((1-Const2)*(p2mag2 + (m2 / m1) * p1mag2));

		if(P1MAG1>=pmag && P1MAG1>P2MAG1)
			Case1 = 1;
		else if(P2MAG1>=pmag && P2MAG1>P1MAG1)
			Case1 = 2;
		else
			Case1 = 0;

		if(P1MAG2>=pmag && P1MAG2>P2MAG2)
			Case2 = 1;
		else if(P2MAG2>=pmag && P2MAG2>P1MAG2)
			Case2 = 2;
		else
			Case2 = 0;

//CASE 1 means m1|vp1| - m2|vp2| = p
//CASE 2 means m2|vp2| - m1|vp1| = p
//CASE 0 means m1|vp1| + m2|vp2| = p


		switch(Case1)
		{
			case 0:
				if(abs(P1MAG1 + P2MAG1 - pmag)>0.0001)
				{
					sprintf(string,"\n$$$$$$$$$$$$$$$$$\n");
					BYDumpInfo(string);
					sprintf(string,"PMags don't add up.  C1 = %f  Case = 0\n",Const1);
					BYDumpInfo(string);
					sprintf(string,"P1MAG1 = %f, P2MAG1 = %f, pmag = %f\n",P1MAG1,P2MAG1,pmag);
					BYDumpInfo(string);
					BYDumpInfo("$$$$$$$$$$$$$$$$$\n\n");

				}
				switch(Case2)
				{
					case 0:
						if(abs(P1MAG2 + P2MAG2 - pmag)>0.0001)
						{
							sprintf(string,"\n$$$$$$$$$$$$$$$$$\n");
							BYDumpInfo(string);
							sprintf(string,"PMags don't add up.  C2 = %f  Case = 0\n",Const2);
							BYDumpInfo(string);
							sprintf(string,"P1MAG2 = %f, P2MAG2 = %f, pmag = %f\n",P1MAG2,P2MAG2,pmag);
							BYDumpInfo(string);
							BYDumpInfo("$$$$$$$$$$$$$$$$$\n\n");

						}
						Const = (Const1 + Const2)/2;

					break;
					case 1:
						//Answer must be to the left of Const2.
						//Therefore, MaxC must be less than Const1.
						if(abs(P1MAG2 - P2MAG2 - pmag)>0.0001)
						{
							sprintf(string,"\n$$$$$$$$$$$$$$$$$\n");
							BYDumpInfo(string);
							sprintf(string,"PMags don't add up.  C2 = %f  Case = 1\n",Const2);
							BYDumpInfo(string);
							sprintf(string,"P1MAG2 = %f, P2MAG2 = %f, pmag = %f\n",P1MAG2,P2MAG2,pmag);
							BYDumpInfo(string);
							BYDumpInfo("$$$$$$$$$$$$$$$$$\n\n");

						}
						if(MaxC>Const1)
						{
							BYDumpInfo("\n&&&&&&&&&&&&&&&&&&&&&\n");
							BYDumpInfo("Case 0,1; MaxC>Const1.\n");
							BYDumpInfo("&&&&&&&&&&&&&&&&&&&&&\n\n");
						}
						Const = Const2/2;

					break;
					case 2:
						//Answer must be to the right of Const2.
						//So it's either between Const1 and 1 or between Const2 and Const1.
						if(abs(-P1MAG2 + P2MAG2 - pmag)>0.0001)
						{
							sprintf(string,"\n$$$$$$$$$$$$$$$$$\n");
							BYDumpInfo(string);
							sprintf(string,"PMags don't add up.  C2 = %f  Case = 2\n",Const2);
							BYDumpInfo(string);
							sprintf(string,"P1MAG2 = %f, P2MAG2 = %f, pmag = %f\n",P1MAG2,P2MAG2,pmag);
							BYDumpInfo(string);
							BYDumpInfo("$$$$$$$$$$$$$$$$$\n\n");

						}
						if(MaxC>Const1)
						{
							Const=(Const1+1)/2;
						}
						else
						{
							Const=(Const1+Const2)/2;
						}
					break;
				}
			break;
			case 1:
				if(abs(P1MAG1 - P2MAG1 - pmag)>0.0001)
				{
					sprintf(string,"\n$$$$$$$$$$$$$$$$$\n");
					BYDumpInfo(string);
					sprintf(string,"PMags don't add up.  C1 = %f  Case = 1\n",Const1);
					BYDumpInfo(string);
					sprintf(string,"P1MAG1 = %f, P2MAG1 = %f, pmag = %f\n",P1MAG1,P2MAG1,pmag);
					BYDumpInfo(string);
					BYDumpInfo("$$$$$$$$$$$$$$$$$\n\n");

				}
				switch(Case2)
				{
					case 0:
						if(abs(P1MAG2 + P2MAG2 - pmag)>0.0001)
						{
							sprintf(string,"\n$$$$$$$$$$$$$$$$$\n");
							BYDumpInfo(string);
							sprintf(string,"PMags don't add up.  C2 = %f  Case = 0\n",Const2);
							BYDumpInfo(string);
							sprintf(string,"P1MAG2 = %f, P2MAG2 = %f, pmag = %f\n",P1MAG2,P2MAG2,pmag);
							BYDumpInfo(string);
							BYDumpInfo("$$$$$$$$$$$$$$$$$\n\n");

						}
						if(MaxC>Const2)
						{
							Const=(Const1+Const2)/2;
						}
						else
						{
							Const=Const2/2;
						}
					break;
					case 1:
						if(abs(P1MAG2 - P2MAG2 - pmag)>0.0001)
						{
							sprintf(string,"\n$$$$$$$$$$$$$$$$$\n");
							BYDumpInfo(string);
							sprintf(string,"PMags don't add up.  C2 = %f  Case = 1\n",Const2);
							BYDumpInfo(string);
							sprintf(string,"P1MAG2 = %f, P2MAG2 = %f, pmag = %f\n",P1MAG2,P2MAG2,pmag);
							BYDumpInfo(string);
							BYDumpInfo("$$$$$$$$$$$$$$$$$\n\n");

						}
						BYDumpInfo("\n&&&&&&&&&&&&&&&&&&&&&\n");
						BYDumpInfo("Case 1,1; Bizarreness, this should never happen.\n");
						sprintf(string,"Const1 = %f, Const2 = %f\n",Const1,Const2);
						BYDumpInfo(string);
						sprintf(string,"P1MAG2 = %f, P2MAG2 = %f, pmag = %f\n",P1MAG2,P2MAG2,pmag);
						BYDumpInfo(string);
						sprintf(string,"P1MAG1 = %f, P2MAG1 = %f, pmag = %f\n",P1MAG1,P2MAG1,pmag);
						BYDumpInfo(string);

						BYDumpInfo("&&&&&&&&&&&&&&&&&&&&&\n\n");
						Const=MaxC;


					break;
					case 2:
						if(abs(-P1MAG2 + P2MAG2 - pmag)>0.0001)
						{
							sprintf(string,"\n$$$$$$$$$$$$$$$$$\n");
							BYDumpInfo(string);
							sprintf(string,"PMags don't add up.  C2 = %f  Case = 2\n",Const2);
							BYDumpInfo(string);
							sprintf(string,"P1MAG2 = %f, P2MAG2 = %f, pmag = %f\n",P1MAG2,P2MAG2,pmag);
							BYDumpInfo(string);
							BYDumpInfo("$$$$$$$$$$$$$$$$$\n\n");

						}
						Const=(Const1+Const2)/2;
					break;
				}

			break;
			case 2:
				if(abs(-P1MAG1 + P2MAG1 - pmag)>0.0001)
				{
					sprintf(string,"\n$$$$$$$$$$$$$$$$$\n");
					BYDumpInfo(string);
					sprintf(string,"PMags don't add up.  C1 = %f  Case = 2\n",Const1);
					BYDumpInfo(string);
					sprintf(string,"P1MAG1 = %f, P2MAG1 = %f, pmag = %f\n",P1MAG1,P2MAG1,pmag);
					BYDumpInfo(string);
					BYDumpInfo("$$$$$$$$$$$$$$$$$\n\n");

				}
				switch(Case2)
				{
					case 0:
						if(abs(P1MAG2 + P2MAG2 - pmag)>0.0001)
						{
							sprintf(string,"\n$$$$$$$$$$$$$$$$$\n");
							BYDumpInfo(string);
							sprintf(string,"PMags don't add up.  C2 = %f  Case = 0\n",Const2);
							BYDumpInfo(string);
							sprintf(string,"P1MAG2 = %f, P2MAG2 = %f, pmag = %f\n",P1MAG2,P2MAG2,pmag);
							BYDumpInfo(string);
							BYDumpInfo("$$$$$$$$$$$$$$$$$\n\n");

						}
						if(MaxC>Const2)
						{
							Const=(Const1+1)/2;

						}
						else
						{
							BYDumpInfo("\n&&&&&&&&&&&&&&&&&&&&&\n");
							BYDumpInfo("Case 2,0; MaxC<Const2.\n");
							BYDumpInfo("&&&&&&&&&&&&&&&&&&&&&\n\n");
							Const=MaxC;
						}
					break;
					case 1:
						if(abs(P1MAG2 - P2MAG2 - pmag)>0.0001)
						{
							sprintf(string,"\n$$$$$$$$$$$$$$$$$\n");
							BYDumpInfo(string);
							sprintf(string,"PMags don't add up.  C2 = %f  Case = 1\n",Const2);
							BYDumpInfo(string);
							sprintf(string,"P1MAG2 = %f, P2MAG2 = %f, pmag = %f\n",P1MAG2,P2MAG2,pmag);
							BYDumpInfo(string);
							BYDumpInfo("$$$$$$$$$$$$$$$$$\n\n");

						}
						BYDumpInfo("\n&&&&&&&&&&&&&&&&&&&&&\n");
						BYDumpInfo("Weirdness, this should never happen\n");
						BYDumpInfo("case 2,1\n");
						sprintf(string,"Const1 = %f, Const2 = %f\n",Const1,Const2);
						BYDumpInfo(string);
						sprintf(string,"P1MAG2 = %f, P2MAG2 = %f, pmag = %f\n",P1MAG2,P2MAG2,pmag);
						BYDumpInfo(string);
						sprintf(string,"P1MAG1 = %f, P2MAG1 = %f, pmag = %f\n",P1MAG1,P2MAG1,pmag);
						BYDumpInfo(string);

						BYDumpInfo("&&&&&&&&&&&&&&&&&&&&&\n\n");
						Const=MaxC;

					break;
					case 2:
						if(abs(-P1MAG2 + P2MAG2 - pmag)>0.0001)
						{
							sprintf(string,"\n$$$$$$$$$$$$$$$$$\n");
							BYDumpInfo(string);
							sprintf(string,"PMags don't add up.  C2 = %f  Case = 2\n",Const2);
							BYDumpInfo(string);
							sprintf(string,"P1MAG2 = %f, P2MAG2 = %f, pmag = %f\n",P1MAG2,P2MAG2,pmag);
							BYDumpInfo(string);
							BYDumpInfo("$$$$$$$$$$$$$$$$$\n\n");

						}
						BYDumpInfo("\n&&&&&&&&&&&&&&&&&&&&&\n");
						BYDumpInfo("Weirdness, this should never happen\n");
						BYDumpInfo("case 2,2\n");
						sprintf(string,"Const1 = %f, Const2 = %f\n",Const1,Const2);
						BYDumpInfo(string);
						sprintf(string,"P1MAG2 = %f, P2MAG2 = %f, pmag = %f\n",P1MAG2,P2MAG2,pmag);
						BYDumpInfo(string);
						sprintf(string,"P1MAG1 = %f, P2MAG1 = %f, pmag = %f\n",P1MAG1,P2MAG1,pmag);
						BYDumpInfo(string);

						BYDumpInfo("&&&&&&&&&&&&&&&&&&&&&\n\n");
						Const=MaxC;
					break;
				}
			break;
		}


/*
		sprintf(string,"",);
		BYDumpInfo(string);
			sprintf(string,"",);
			BYDumpInfo(string);
			sprintf(string,"",);
			BYDumpInfo(string);
			sprintf(string,"",);
			BYDumpInfo(string);
			sprintf(string,"",);
			BYDumpInfo(string);
			sprintf(string,"",);
			BYDumpInfo(string);
*/

	}

	

	// gives each particle 1/2 the total kinetic energy of the system 
	//p1pmag2 = (0.5) * (p1mag2 + (m1 / m2) * p2mag2);
	//p2pmag2 = (0.5) * (p2mag2 + (m2 / m1) * p1mag2);

	// gives each particle fraction of the total kinetic energy proportional to other mass
	//p1pmag2 = (m2/(m1+m2)) * (p1mag2 + (m1 / m2) * p2mag2);
	//p2pmag2 = (m1/(m1+m2)) * (p2mag2 + (m2 / m1) * p1mag2);
	p1pmag2 = Const*(p1mag2 + (m1 / m2) * p2mag2);
	p2pmag2 = (1-Const)*(p2mag2 + (m2 / m1) * p1mag2);

	// sets new momenta
	// find magnitudes of resulting p1 vector that are parallel (d) and perpendicular (c) to the total p vector.
	d = -0.5 * (p2pmag2 - p1pmag2 - pmag2) / pmag;
	if (p1pmag2 < d*d)	   // This check seems to be the crux of the matter --- how do I resolve when p1pmag2 < d*d ????
	{
		BYDumpInfo("God sucks rocks.\n");
		sprintf(string,"pmag = %.3f, p1pmag = %.3f, p2pmag = %.3f\n",pmag,sqrt(p1pmag2),sqrt(p2pmag2));
		BYDumpInfo(string);
		sprintf(string,"p1mag2 = %f, p2mag2 = %f, pmag2 = %f\n");
		BYDumpInfo(string);
		sprintf(string,"Const = %f, Const1 = %f, Const2 = %f\n",Const,Const1,Const2);
		BYDumpInfo(string);
		sprintf(string,"P1MAG2 = %f, P2MAG2 = %f, pmag = %f\n",P1MAG2,P2MAG2,pmag);
		BYDumpInfo(string);
		sprintf(string,"P1MAG1 = %f, P2MAG1 = %f, pmag = %f\n",P1MAG1,P2MAG1,pmag);
		BYDumpInfo(string);
		sprintf(string,"Case %d,%d\n",Case1,Case2);
		BYDumpInfo(string);

		// if the first division of total kinetic energy didn't work, try
      // an equal division.
      // gives each particle 1/2 the total kinetic energy of the system 
      p1pmag2 = (0.5) * (p1mag2 + (m1 / m2) * p2mag2);
      p2pmag2 = (0.5) * (p2mag2 + (m2 / m1) * p1mag2);

	   d = -0.5 * (p2pmag2 - p1pmag2 - pmag2) / pmag;
	   
	   // if it still isn't valid, use the kludged value.
      if (p1pmag2 < d*d)	   // This check seems to be the crux of the matter --- how do I resolve when p1pmag2 < d*d ????
		   d = (sqrt(p1pmag2) - 0.001);
	}

	c = sqrt(p1pmag2 - d * d);

	// find components of resulting p1 vector that are parallel 
	//and perpendicular to the total p vector.
	parallel.x = (p.x / pmag) * d;
	parallel.z = (p.z / pmag) * d;
	perpendicular.x = (-p.z / pmag) * c;
	perpendicular.z = ( p.x / pmag) * c;
	perpendicular.y = parallel.y = 0;

	// find the two possible solutions (a and b)
	p1pa.x = parallel.x + perpendicular.x;
	p1pa.z = parallel.z + perpendicular.z;

	p1pb.x = parallel.x - perpendicular.x;
	p1pb.z = parallel.z - perpendicular.z;

	p2pa.x = p.x - p1pa.x;
	p2pa.z = p.z - p1pa.z;
	p2pb.x = p.x - p1pb.x;
	p2pb.z = p.z - p1pb.z;
	
	// pick solution that points away from separation vector 
	//(so they bounce away from each other)
	
	if (p1pmag2 > p2pmag2)			// if p1p bigger, consider p1pa vs. p1pb
	{
		//RLVector reflect;
		dot1a = RLVectorDotProduct(&p1pa, &sep);
		dot1b = RLVectorDotProduct(&p1pb, &sep);

		if (dot1a < dot1b) 
		{
			p1p.x = p1pa.x;
			p1p.z = p1pa.z;
		}
		else
		{
			p1p.x = p1pb.x;
			p1p.z = p1pb.z;
		}
		p2p.x = p.x - p1p.x;
		p2p.z = p.z - p1p.z;
	}
	else
	{
		//RLVector reflect;
		dot2a = -RLVectorDotProduct(&p2pa, &sep);
		dot2b = -RLVectorDotProduct(&p2pb, &sep);

		if (dot2a < dot2b) 
		{
			p2p.x = p2pa.x;
			p2p.z = p2pa.z;
		}
		else
		{
			p2p.x = p2pb.x;
			p2p.z = p2pb.z;
		}
		p1p.x = p.x - p2p.x;
		p1p.z = p.z - p2p.z;
	}

	
	p1p.y = p2p.y = 0;

	// sets new velocities from new momenta
	if (m1) 
	{
		RLVectorScale(&(thisun->CollisionVector), &p1p, RLDivide(RLVal(1), m1));
	}
	if (m2) 
	{
		RLVectorScale(&(thatun->CollisionVector), &p2p, RLDivide(RLVal(1), m2));
	}

	// guess at appropriate spins from cross product of inital and final velocities
	RobotFallDownSpin = MonsterFallDownSpin = 0;
	if (RLVectorDotProduct(&v1, &v1) < RLVal(0.0001)) 
	{
		v1.x = sep.x;
		v1.z = sep.z;
	}
	if (RLVectorDotProduct(&v2, &v2) < RLVal(0.0001)) 
	{
		v2.x = -sep.x;
		v2.z = -sep.z;
	}
	if (thisun == &RobotData)
	{
		RLVectorNormalise(&v1);
		RobotFallDownSpin = RobotSpinMultiplier * RLDivide((RLMultiply(v1.z,thisun->CollisionVector.x) 
			- RLMultiply(v1.x,thisun->CollisionVector.z)),
			RLVectorModulus(&thisun->CollisionVector));
	}
	else if (thatun == &RobotData)
	{
		RLVectorNormalise(&v2);
		RobotFallDownSpin = RobotSpinMultiplier * RLDivide((RLMultiply(v2.z, thatun->CollisionVector.x) 
			- RLMultiply(v2.x,thatun->CollisionVector.z)),
			RLVectorModulus(&thatun->CollisionVector));
	}
	if (thisun == &MonsterData)
	{
		RLVectorNormalise(&v1);
		MonsterFallDownSpin = MonsterSpinMultiplier * RLDivide((RLMultiply(v1.z, thisun->CollisionVector.x) 
			- RLMultiply(v1.x ,thisun->CollisionVector.z)),
			RLVectorModulus(&thisun->CollisionVector));
	}
	else if (thatun == &MonsterData)
	{
		RLVectorNormalise(&v2);
		MonsterFallDownSpin = MonsterSpinMultiplier * RLDivide((RLMultiply(v2.z, 
			thatun->CollisionVector.x) 
			- RLMultiply(v2.x,thatun->CollisionVector.z)),
			RLVectorModulus(&thatun->CollisionVector));
	}
}



static void HandleMovingObjectCollision(MovingObjectData thisun,MovingObjectData thatun)
{
   RLVector position;
   RLFrame Scene;
   char OutputString[256];
   thisun->collisionflag = 1;
   thatun->collisionflag = 1;
   if(
	   ( (thisun == &MonsterData) && (thatun == &RobotData) ) ||
	   ( (thatun == &MonsterData) && (thisun == &RobotData) )
	   )
   {
	   thisun->collisionflag = 47;
	   thatun->collisionflag = 47;
   }
   
   ResolveMomentum(thisun, thatun);
   
   thisun->DamageIveTaken = thatun->DamageICause;
   thatun->DamageIveTaken = thisun->DamageICause;
   Scene = RLFrameGetScene(Robotframe);
   RLFrameGetPosition(Robotframe, Scene, &position);
//   sprintf(OutputString,"RobotMovementState = %d, RobotAnimationState = %d,\nRobotLife = %d, RobotEngy = %d\n",RobotMovementState ,RobotAnimationState ,RobotLife,RobotEngy);
//   OutputDebugString(OutputString);
//   sprintf(OutputString,"RobotPosition = %.3f, %.3f, %.3f\n",position.x,position.y,position.z);
//   OutputDebugString(OutputString);
//   sprintf(OutputString,"RobotCollision = %.3f, %.3f, %.3f\n\n",RobotData.CollisionVector.x,RobotData.CollisionVector.y,RobotData.CollisionVector.z);
//   OutputDebugString(OutputString);
//   sprintf(OutputString,"MonsterMovementState = %d, MonsterAnimationState = %d,\nMnstLife = %d, MnstEngy = %d\n\n",MonsterMovementState ,MonsterAnimationState ,MnstLife,MnstEngy);
 //  OutputDebugString(OutputString);

}
#define abs(x) ((x)>=0?(x):-(x))

static void HandleAttackCollision(MovingObjectData attacker,MovingObjectData attackee)
{
   if ((attackee == &RobotData) && ((RobotMovementState == RobotKnockDown) || 
	   (RobotMovementState == RobotKnockDownOnBuilding))) 
   {
	   return;
   }
   if ((attackee == &MonsterData) && ((MonsterAnimationState == MonsterKnockDown2) ||
	   (MonsterAnimationState == MonsterGetBackUp2))) 
   {
	   return;
   }
   if(attacker == &RobotData)
   {
	   if(attackee == &MonsterData)
		   attackee->collisionflag = 47;
	   else
		   attackee->collisionflag = 1;
   }
   else if(attacker == &MonsterData)
   {
	   if(attackee == &RobotData)
		   attackee->collisionflag = 47;
	   else
		   attackee->collisionflag = 1;
   }
   else
   {
	   attacker->collisionflag = 1;
	   attackee->collisionflag = 1;
   }

	ResolveMomentum(attacker, attackee);
   
   attackee->DamageIveTaken = attacker->DamageICause;
}


static void HandleBuildingCollision(MovingObjectData mover,
									visible_buildings *CollideBuildings)
{
//This is a skeleton function.  In the future I expect to use this function to
//place decals on buildings and get physically correct bounceback data
//from sides of buildings.  For now, it sets the building damage flags
//and tells you you've hit a building and what direction from you the 
//building was placed.

//In any case, it is limitted to objects whose x-z plane projection
//can be modeled convincingly as a square.  Things that are sigficantly
//longer than they are wide will need to be handled differently.

   int i;
   RLVector position;
   RLFrame Scene;
   for (i = 0; i < CollideBuildings->count; i++)
   {
      RLValue MaxBuildingX = (CollideBuildings->building_ptr[i]->building.max.x);
      RLValue MaxBuildingZ = (CollideBuildings->building_ptr[i]->building.max.z);
      RLValue MinBuildingX = (CollideBuildings->building_ptr[i]->building.min.x);
      RLValue MinBuildingZ = (CollideBuildings->building_ptr[i]->building.min.z);
      RLValue MaxBuildingY = (CollideBuildings->building_ptr[i]->building.max.y);
      RLValue MinBuildingY = (CollideBuildings->building_ptr[i]->building.min.y);
      if(!(MaxBuildingY<mover->CurrentVolume.min.y||
           MinBuildingY>mover->CurrentVolume.max.y))
      {//object isn't flying harmlessly over or under the building
         RLBox LastVolume;
         mover->collisionflag=2;
         LastVolume.min.x = mover->Volume.min.x + mover->CurrentPosition.x;
         LastVolume.max.x = mover->Volume.max.x + mover->CurrentPosition.x;
         LastVolume.min.y = mover->Volume.min.y + mover->CurrentPosition.y;
         LastVolume.max.y = mover->Volume.max.y + mover->CurrentPosition.y;
         LastVolume.min.z = mover->Volume.min.z + mover->CurrentPosition.z;
         LastVolume.max.z = mover->Volume.max.z + mover->CurrentPosition.z;

         if (mover->data != -1)	// not Robot or monster
		 {
             CollideBuildings->building_ptr[i]->cur_damage += 
				 mover->DamageICause;
		 }
		 else // Robot or monster
		 {
            CollideBuildings->building_ptr[i]->cur_damage += mover->DamageICause;
		 }
         if (CollideBuildings->building_ptr[i]->cur_damage >= 
			 CollideBuildings->building_ptr[i]->max_damage)
         {//if building gets destroyed.
             RLVector CollisionVector;
             CollisionVector.x = mover->ProjectedPosition.x-mover->CurrentPosition.x;
             CollisionVector.y = mover->ProjectedPosition.y-mover->CurrentPosition.y;
             CollisionVector.z = mover->ProjectedPosition.z-mover->CurrentPosition.z;
	         if (mover == &MonsterData) 
			 {
				 MnstEngy += RLMultiply(RLVal(5*655.36), 
					 CollideBuildings->building_ptr[i]->power_mon_amount);
				 YBPlay3DSound(EmPower, monstframe);
 
			 }
     	     Population -= CollideBuildings->building_ptr[i]->power_mon_amount * 1000;
   	         CowboyDeathMarch(CollideBuildings->building_ptr[i], &CollisionVector);
             mover->collisionflag = 0;
         }
         else if (mover->data != -1)
		 //if the object was simple, like a bullet, not complicated, like a Robot.
         {
         }
         else if (LastVolume.min.y > MaxBuildingY)//last frame the thing was above the building
         {
            if (LastVolume.min.x < MaxBuildingX && LastVolume.max.x > MinBuildingX &&
                LastVolume.min.z < MaxBuildingZ && LastVolume.max.z > MinBuildingZ)
            {//Last frame, the thing was directly above the building, and landed on top of it.
               RobotBuilding = CollideBuildings->building_ptr[i];
               mover->data = LandOnBuilding;
               mover->CollisionVector.x = mover->ProjectedPosition.x;
               mover->CollisionVector.y = MaxBuildingY - mover->Volume.min.y 
				     + BuildingBumpAmount;
               mover->CollisionVector.z = mover->ProjectedPosition.z;
            }
            else//the thing ran into one of the corners
            {
               if (MaxBuildingY > (mover->CurrentVolume.min.y + mover->CurrentVolume.max.y) / 2)
               {//Waist hit below top of building, we'll slide down the side.
                  mover->data = SlideDownSideOfBuilding;
                  if (LastVolume.min.x > MaxBuildingX)
                  {
                     if (LastVolume.min.z > MaxBuildingZ)
                     {
                        mover->CollisionVector.x = MaxBuildingX - 
							mover->Volume.min.x+ BuildingBumpAmount;
                        mover->CollisionVector.z = MaxBuildingZ - 
							mover->Volume.min.z+ BuildingBumpAmount;
                        mover->CollisionVector.y = mover->ProjectedPosition.y;
                     }
                     else if (LastVolume.max.z < MinBuildingZ)
                     {
                        mover->CollisionVector.x = MaxBuildingX - 
							mover->Volume.min.x+ BuildingBumpAmount;
                        mover->CollisionVector.z = MinBuildingZ - 
							mover->Volume.max.z- BuildingBumpAmount;
                        mover->CollisionVector.y = mover->ProjectedPosition.y;
                     }
                     else
                     {
                        mover->CollisionVector.x = MaxBuildingX - mover->Volume.min.x;
                        mover->CollisionVector.z = mover->ProjectedPosition.z;
                        mover->CollisionVector.y = mover->ProjectedPosition.y;
                     }
                  }
                  else if (LastVolume.max.x < MinBuildingX)
                  {
                     if (LastVolume.min.z > MaxBuildingZ)
                     {
                        mover->CollisionVector.x = MinBuildingX - 
							mover->Volume.max.x- BuildingBumpAmount;
                        mover->CollisionVector.z = MaxBuildingZ - 
							mover->Volume.min.z+ BuildingBumpAmount;
                        mover->CollisionVector.y = mover->ProjectedPosition.y;
                     }
                     else if (LastVolume.max.z<MinBuildingZ)
                     {
                        mover->CollisionVector.x = MinBuildingX - 
							mover->Volume.max.x- BuildingBumpAmount;
                        mover->CollisionVector.z = MinBuildingZ - 
							mover->Volume.max.z- BuildingBumpAmount;
                        mover->CollisionVector.y = mover->ProjectedPosition.y;
                     }
                     else
                     {
                        mover->CollisionVector.x = MinBuildingX - 
							mover->Volume.max.x- BuildingBumpAmount;
                        mover->CollisionVector.z = mover->ProjectedPosition.z;
                        mover->CollisionVector.y = mover->ProjectedPosition.y;
                     }
                  }
                  else if(LastVolume.min.z > MaxBuildingZ)
                  {
                        mover->CollisionVector.x = mover->ProjectedPosition.x;
                        mover->CollisionVector.z = MaxBuildingZ - 
							mover->Volume.min.z+ BuildingBumpAmount;
                        mover->CollisionVector.y = mover->ProjectedPosition.y;
                  }
                  else
                  {
                        mover->CollisionVector.x = mover->ProjectedPosition.x;
                        mover->CollisionVector.z = MinBuildingZ - 
							mover->Volume.max.z- BuildingBumpAmount;
                        mover->CollisionVector.y = mover->ProjectedPosition.y;
                  }
               }
               else if(MaxBuildingY>(RLMultiply(RLVal(0.9),mover->CurrentVolume.min.y) +
                                     RLMultiply(RLVal(0.1),mover->CurrentVolume.max.y) ))
               {//between the waist and the feet, fall forward
                  RobotBuilding = CollideBuildings->building_ptr[i];
                  mover->data=FallForwardOnBuilding;
                  mover->CollisionVector.x = mover->ProjectedPosition.x;
                  mover->CollisionVector.z = mover->ProjectedPosition.z;
                  mover->CollisionVector.y = MaxBuildingY;
               }
               else
               {//land at foot level, we'll assume you made your way onto the building with grace.
                  RobotBuilding = CollideBuildings->building_ptr[i];
                  mover->data = LandOnBuilding;
                  mover->CollisionVector.x = mover->ProjectedPosition.x;
                  mover->CollisionVector.z = mover->ProjectedPosition.z;
                  mover->CollisionVector.y = MaxBuildingY - mover->Volume.min.y  
					  + BuildingBumpAmount;
               }
            }
            
         }
         else//last frame the thing was below the top of the building, so ran into the side. (Or bottom, but I'll worry about that if I need to.)
         {
            if (MaxBuildingY < (mover->CurrentVolume.min.y 
				+ mover->CurrentVolume.max.y)/2)
            {//below the waist, fall forward
               RobotBuilding = CollideBuildings->building_ptr[i];
               mover->data = FallForwardOnBuilding;
               mover->CollisionVector.x = mover->ProjectedPosition.x;
               mover->CollisionVector.z = mover->ProjectedPosition.z;
               mover->CollisionVector.y = MaxBuildingY - mover->Volume.min.y 
				   + BuildingBumpAmount;
            }
            else
            {//even if the thing ran into the building at ground level, we'll let it slide down the building for one frame.
               RLValue Height = SpuddeMapHeight2(mover->ProjectedPosition.x, 
				   mover->ProjectedPosition.z);
               RLValue RobotHeight = mover->Volume.max.y - mover->Volume.min.y;
               if (mover->ProjectedPosition.y - Height >= RobotHeight/10)
               {
                  mover->data = SlideDownSideOfBuilding;
               }
               else
               {
                  mover->data = RunIntoBuilding;
                  mover->ProjectedPosition.y = Height;
               }
               if (LastVolume.min.x > MaxBuildingX)
				   //had greater x than building last time.
               {
                  if (LastVolume.min.z > MaxBuildingZ)
					  //had greater z than building last time, so hit corner.
                  {
                     mover->CollisionVector.x = MaxBuildingX - 
						 mover->Volume.min.x + BuildingBumpAmount;
                     mover->CollisionVector.z = MaxBuildingZ - 
						 mover->Volume.min.z+ BuildingBumpAmount;
                     mover->CollisionVector.y = mover->ProjectedPosition.y;
                  }
                  else if (LastVolume.max.z < MinBuildingZ)
					  //had smaller z than building, so hit corner.
                  {
                     mover->CollisionVector.x = MaxBuildingX - 
						 mover->Volume.min.x+ BuildingBumpAmount;
                     mover->CollisionVector.z = MinBuildingZ - 
						 mover->Volume.max.z- BuildingBumpAmount;
                     mover->CollisionVector.y = mover->ProjectedPosition.y;
                  }
                  else //z was inside the building, so hit x side, from above.
                  {
                     mover->CollisionVector.x = MaxBuildingX - 
						 mover->Volume.min.x+ BuildingBumpAmount;
                     mover->CollisionVector.z = mover->ProjectedPosition.z;
                     mover->CollisionVector.y = mover->ProjectedPosition.y;
                  }
               }
               else if (LastVolume.max.x < MinBuildingX)
				   //had less x than building last time
               {
                  if (LastVolume.min.z > MaxBuildingZ)
					  //had greater z than building last time, so hit corner
                  {
                     mover->CollisionVector.x = MinBuildingX - 
						 mover->Volume.max.x- BuildingBumpAmount;
                     mover->CollisionVector.z = MaxBuildingZ - 
						 mover->Volume.min.z+ BuildingBumpAmount;
                     mover->CollisionVector.y = mover->ProjectedPosition.y;
                  }
                  else if(LastVolume.max.z<MinBuildingZ)//had lesser z than building last time, so hit corner
                  {
                     mover->CollisionVector.x = MinBuildingX - mover->Volume.max.x- BuildingBumpAmount;
                     mover->CollisionVector.z = MinBuildingZ - mover->Volume.max.z- BuildingBumpAmount;
                     mover->CollisionVector.y = mover->ProjectedPosition.y;
                  }
                  else//z was inside the building, so hit x side from below.
                  {
                     mover->CollisionVector.x = MinBuildingX - mover->Volume.max.x- BuildingBumpAmount;
                     mover->CollisionVector.z = mover->ProjectedPosition.z;
                     mover->CollisionVector.y = mover->ProjectedPosition.y;
                  }
               }//to have gotten to this point, x must have been inside the building.
               else if(LastVolume.min.z>MaxBuildingZ)//had greater z than building last time
               {
                     mover->CollisionVector.x = mover->ProjectedPosition.x;
                     mover->CollisionVector.z = MaxBuildingZ - mover->Volume.min.z 
						 + BuildingBumpAmount;
                     mover->CollisionVector.y = mover->ProjectedPosition.y;
               }
               else //having eliminated 7 of other 8 zones, must have had lesser z than building last time.
               {
                     mover->CollisionVector.x = mover->ProjectedPosition.x;
                     mover->CollisionVector.z = MinBuildingZ - mover->Volume.max.z 
						 - BuildingBumpAmount;
                     mover->CollisionVector.y = mover->ProjectedPosition.y;
               }
            }
         }
      }
   }
}

extern HotSpot BombSpot;
extern HotSpot RobotHotSpots[5];

static int CheckCollisionSphereSphere(HotSpot *sphere1, HotSpot *sphere2)
{
   RLVector Difference, AttackPoint, GetHitPoint;
   RLValue dummy, MinDistance, Distance;

   RLFrameTransform(sphere1->position, &AttackPoint, &(sphere1->point1));
   RLFrameTransform(sphere2->position, &GetHitPoint, &(sphere2->point1));
   
   Difference.x = AttackPoint.x - GetHitPoint.x;
   Difference.y = AttackPoint.y - GetHitPoint.y;
   Difference.z = AttackPoint.z - GetHitPoint.z;
   Distance = RLVectorDotProduct(&Difference, &Difference);
   dummy = sphere1->radius + sphere2->radius;
   MinDistance = RLMultiply(dummy, dummy);
   if (MinDistance >= Distance)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

static int CheckCollisionSphereTube(HotSpot *sphere, HotSpot2 *tube)
{
   RLVector AttackPoint, AttackPoint2, GetHitPoint;
   RLVector U, V, close, Difference;
   RLValue dummy, denominator, numerator, cosine;
   RLValue Distance, MinDistance;


   RLFrameTransform(tube->position, &AttackPoint, &(tube->point1));
   RLFrameTransform(tube->position, &AttackPoint2, &(tube->point2));
   V.x = AttackPoint.x - AttackPoint2.x;
   V.y = AttackPoint.y - AttackPoint2.y;
   V.z = AttackPoint.z - AttackPoint2.z;
   denominator = RLVectorDotProduct(&V, &V);

   RLFrameTransform(sphere->position, &GetHitPoint,&(sphere->point1));
   U.x = GetHitPoint.x - AttackPoint2.x;
   U.y = GetHitPoint.y - AttackPoint2.y;
   U.z = GetHitPoint.z - AttackPoint2.z;
   numerator=RLVectorDotProduct(&U, &V);
   if (numerator < 0)//AttackPoint2 is closest.
   {
      close.x = AttackPoint2.x;
      close.y = AttackPoint2.y;
      close.z = AttackPoint2.z;
   }
   else if (numerator > denominator)//AttackPoint is closest
   {
      close.x = AttackPoint.x;
      close.y = AttackPoint.y;
      close.z = AttackPoint.z;
   }
   else//some point in between AttackPoint and AttackPoint2 is closest.
   {
      cosine = RLDivide(numerator, denominator);
      close.x = AttackPoint2.x + RLMultiply(cosine, V.x);
      close.y = AttackPoint2.y + RLMultiply(cosine, V.y);
      close.z = AttackPoint2.z + RLMultiply(cosine, V.z);   
   }
   
   Difference.x = close.x - GetHitPoint.x;
   Difference.y = close.y - GetHitPoint.y;
   Difference.z = close.z - GetHitPoint.z;
   Distance=RLVectorDotProduct(&Difference, &Difference);
   dummy = sphere->radius + tube->radius;
   MinDistance = RLMultiply(dummy, dummy);
   if (MinDistance >= Distance)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}


void ClockworkGod()
{
   int i, j, k, l;
   MovingObjectData thisun, thatun;
   extern RLFrame Wscene;

   for (i = 0; i < NumMovingObjects; ++i)
   {
      //step one, move the object.
      thisun = MovingObjects[i];
      thisun->MoveMe(thisun);

      //step two, check for building collisions.
#ifdef VISUAL_BBOX
	if (thisun == &RobotData)
	{
		RLFrameAddScale(Robotboxyframe, RLCombineReplace, 
			(RobotData.Volume.max.x-RobotData.Volume.min.x),
			(RobotData.Volume.max.y-RobotData.Volume.min.y),
			(RobotData.Volume.max.z-RobotData.Volume.min.z));
		RLFrameSetPosition(Robotboxyframe, Wscene, thisun->ProjectedPosition.x, thisun->ProjectedPosition.y, thisun->ProjectedPosition.z);
	}
	else if (thisun == &MonsterData)
	{
		RLFrameAddScale(monsterboxyframe, RLCombineReplace, 
			MonsterData.Volume.max.x-MonsterData.Volume.min.x,
			MonsterData.Volume.max.y-MonsterData.Volume.min.y,
			MonsterData.Volume.max.z-MonsterData.Volume.min.z);
		RLFrameSetPosition(monsterboxyframe, Wscene, thisun->ProjectedPosition.x, thisun->ProjectedPosition.y, thisun->ProjectedPosition.z);
	}
#endif
      thisun->CurrentVolume.min.x = thisun->Volume.min.x + thisun->ProjectedPosition.x;
      thisun->CurrentVolume.max.x = thisun->Volume.max.x + thisun->ProjectedPosition.x;
      thisun->CurrentVolume.min.y = thisun->Volume.min.y + thisun->ProjectedPosition.y;
      thisun->CurrentVolume.max.y = thisun->Volume.max.y + thisun->ProjectedPosition.y;
      thisun->CurrentVolume.min.z = thisun->Volume.min.z + thisun->ProjectedPosition.z;
      thisun->CurrentVolume.max.z = thisun->Volume.max.z + thisun->ProjectedPosition.z;
      GetBuildingsInArea(&CollideBuildings, thisun->CurrentVolume.min.x, 
		  thisun->CurrentVolume.min.z, thisun->CurrentVolume.max.x,
		  thisun->CurrentVolume.max.z);
      if (CollideBuildings.count)
      {
         HandleBuildingCollision(thisun,&CollideBuildings);
      }

      for (j = 0; j < i; ++j)
      {//I'm checking all the objects that come before the i'th
       //object, which have all already had their next positions
       //calculated.  This time, I just check bounding boxes.  Next pass
       //through I'll check the spheres and etc.

		   
		  //Add by Eric 11/12/96
		  if (GameStates.IsNetplay)
		  {
			  if (isHost)
		      {
				  //get rid of weapon collision with monster
			      if (i > 1 && j == 1)
				      j = 2;
		      }
		      else
		      {
				  //get rid of weapon collision with Robot
				  if (i > 1 && j == 0)
					  j = 1;

				  //get rid of monster collision with Robot
				  //if (i = 1 && j == 0)
				  //    break;
		      }
		  }
		  //end of Eric
		   
         thatun = MovingObjects[j];
         if (!(thisun->SafePassageIndex == thatun || thatun->SafePassageIndex == thisun))
         {
            if (!(
               (thisun->CurrentVolume.min.x > thatun->CurrentVolume.max.x)||
               (thisun->CurrentVolume.max.x < thatun->CurrentVolume.min.x)||
               (thisun->CurrentVolume.min.y > thatun->CurrentVolume.max.y)||
               (thisun->CurrentVolume.max.y < thatun->CurrentVolume.min.y)||
               (thisun->CurrentVolume.min.z > thatun->CurrentVolume.max.z)||
               (thisun->CurrentVolume.max.z < thatun->CurrentVolume.min.z)
               ))
            { 
				HandleMovingObjectCollision(thisun,thatun);
            }
         }

      }
   }

   for (i = 0; i < NumMovingObjects; i++)
   {
      thisun = MovingObjects[i];
      if (thisun->AnimateMe)
	  {
         thisun->AnimateMe();
	  }

      for (j = 0; j < i; ++j)
      {//check all the sphere vs. sphere stuff.  
       //Set all the collision flags, etc.
		   
		  //Add by Eric 11/12/96
		  if (GameStates.IsNetplay)
		  {
			  if (isHost)
		      {
				  //get rid of weapon collision with monster
			      if (i > 1 && j == 1)
				      j = 2;
		      }
		      else
		      {
				  //get rid of weapon collision with Robot
				  if (i > 1 && j == 0)
					  j = 1;

				  //get rid of monster collision with Robot
				  //if (i = 1 && j == 0)
				  //    break;
		      }
		  }
		  //end of Eric
		   
         thatun = MovingObjects[j];
         if (!(thisun->SafePassageIndex == thatun || thatun->SafePassageIndex == thisun))
         {

            for (k = 0; k < thatun->NumDefensiveSpheres; ++k)
            {
               for (l = 0; l < thisun->NumOffensiveSpheres; ++l)
			   {
                  if (CheckCollisionSphereSphere(thisun->OffensiveSphereList[l],
                                                thatun->DefensiveSphereList[k]))
				  {
                     HandleAttackCollision(thisun,thatun);			   
				  }
			   }
               for (l = 0; l < thisun->NumOffensiveTubes; ++l)
			   {
                  if (CheckCollisionSphereTube(thatun->DefensiveSphereList[k],
                                              thisun->OffensiveTubeList[l]))
				  {
                     HandleAttackCollision(thisun,thatun);
				  }
			   }
            }

            for (k = 0; k < thisun->NumDefensiveSpheres; ++k)
            {
               for (l=0; l<thatun->NumOffensiveSpheres; ++l)
			   {
                  if (CheckCollisionSphereSphere(thatun->OffensiveSphereList[l],
                                                thisun->DefensiveSphereList[k]))
			      {
			  	     HandleAttackCollision(thatun,thisun);
			      }
			   }
               for (l = 0; l < thatun->NumOffensiveTubes; ++l)
			   {
                  if (CheckCollisionSphereTube(thisun->DefensiveSphereList[k],
                                              thatun->OffensiveTubeList[l]))
                  {
                     HandleAttackCollision(thatun,thisun);
                  }
			   }
            }
         }
      }
   }

   for (i = 0; i < NumMovingObjects; ++i)
   {
      if(MovingObjects[i]->collisionflag)
	  {
         MovingObjects[i]->HandleMe(MovingObjects[i]);
	  }
      else
	  {
         RLFrameSetPosition(MovingObjects[i]->PositioningFrame,Wscene,
                            MovingObjects[i]->ProjectedPosition.x,
                            MovingObjects[i]->ProjectedPosition.y,
                            MovingObjects[i]->ProjectedPosition.z);
	  }
   }

   //Remove every object whose flag's been set.
   for (i = 0, j = 0; i < NumMovingObjects; ++i)
   {
      if (MovingObjects[i]->RemoveMeFlag == 0)
      {
         MovingObjects[j] = MovingObjects[i];
         j++;
      }
   }
   NumMovingObjects = j;
}


HotSpot RobotHotSpots[5];
HotSpot RobotHomerSpot;
HotSpot RobotRapidFireSpot[NumberOfSixShooters];
HotSpot RobotPeaShooterSpot[NumberOfPeaShooters];
HotSpot RobotCussinSpot[NumberOfSixShooters];
HotSpot NeallothRingsSpot[NumberOfSixShooters];
HotSpot2 RobotSwordSpots[2];
HotSpot MonsterHotSpots[4];
HotSpot2 MonsterTailSpots[1];
HotSpot2 MonsterZappaSpot;
HotSpot2 RobotZappaSpot;
HotSpot BombSpot;
RLFrame RLLoadXAFAsFrame(const char* s);
RLError RLLoadXAFAsList(const char* s, size_t*, RLObject**);

extern char RobotName[3];
void SetupHomerHotSpot()
{
   int i;
   RobotHomerData.Volume.max.x = -RLVal(0.2);
   RobotHomerData.Volume.max.y = -RLVal(0.2);
   RobotHomerData.Volume.max.z = -RLVal(0.2);
   RobotHomerData.Volume.min.x = RLVal(0.2);
   RobotHomerData.Volume.min.y = RLVal(0.2);
   RobotHomerData.Volume.min.z = RLVal(0.2);
   RobotHomerData.DamageICause = HomerDamage;
   RobotHomerData.PositioningFrame = Robotspew;
   RobotHomerData.NumOffensiveSpheres = 1;
   RobotHomerData.OffensiveSphereList[0] = &RobotHomerSpot;
   RobotHomerSpot.position = Robotspew;
   RobotHomerSpot.radius = HomerRadius;
   RobotHomerSpot.point1.x = 0;
   RobotHomerSpot.point1.y = 0;
   RobotHomerSpot.point1.z = 0;
   RobotHomerData.NumDefensiveSpheres = 0;
   RobotHomerData.NumOffensiveTubes = 0;
   RobotHomerData.AnimateMe = NULL;
	HomerOnScreen=0;

   RobotHomerData.MoveMe = HomingMotionFunction; //Hide by Helen

   /*
   //add by Helen 11/16/96
   if(GameStates.IsNetplay)
   {
	   if (PlayAsMonster)
       {
			if(LocalAIWorkingFlag)
	        {
		        RobotHomerData.MoveMe = LocalAIHomingLatencyFunction;
	        }

	   }
	   else
	   {
		   RobotHomerData.MoveMe = HomingMotionFunction;
	   }
   }
   else
   {
	   RobotHomerData.MoveMe = HomingMotionFunction;
   }
   //end Helen	
   */

   RobotHomerData.HandleMe = PlasmaGotHit;
   RobotHomerData.SafePassageIndex = &RobotData;

   for (i = 0; i < NumberOfSixShooters; ++i)
   {
      RobotRapidFireData[i].Volume.max.x = -RLVal(0.2);
      RobotRapidFireData[i].Volume.max.y = -RLVal(0.2);
      RobotRapidFireData[i].Volume.max.z = -RLVal(0.2);
      RobotRapidFireData[i].Volume.min.x = RLVal(0.2);
      RobotRapidFireData[i].Volume.min.y = RLVal(0.2);
      RobotRapidFireData[i].Volume.min.z = RLVal(0.2);
      RobotRapidFireData[i].DamageICause = RapidFireDamage;
      
	  RobotRapidFireData[i].PositioningFrame = SixShooter->particles[i]->frame;

	  SixShooter->particles[i]->active = 0;
      RobotRapidFireData[i].NumOffensiveSpheres = 1;
      RobotRapidFireData[i].OffensiveSphereList[0] = &(RobotRapidFireSpot[i]);
      RobotRapidFireSpot[i].position = SixShooter->particles[i]->frame;
      RobotRapidFireSpot[i].radius = RapidFireRadius;
      RobotRapidFireSpot[i].point1.x = 0;
      RobotRapidFireSpot[i].point1.y = 0;
      RobotRapidFireSpot[i].point1.z = 0;
      RobotRapidFireData[i].NumDefensiveSpheres = 0;
      RobotRapidFireData[i].NumOffensiveTubes = 0;
      RobotRapidFireData[i].AnimateMe = NULL;
      RobotRapidFireData[i].MoveMe = RapidFireMotionFunction; //Hide by Helen 11/16/96

	  /*
	  //add by Helen
	  if(GameStates.IsNetplay)
	  {
		  if (PlayAsMonster)
		  {
			  if(LocalAIWorkingFlag)
			  {
				  RobotRapidFireData[i].MoveMe = LocalAIRapidFireLatencyFunction;
			  }

		  }
		  else
		  {
			  RobotRapidFireData[i].MoveMe = RapidFireMotionFunction;	
		  }
	  }
	  else
	  {	
			RobotRapidFireData[i].MoveMe = RapidFireMotionFunction;	
	  }	
     //end Helen
	  */

      RobotRapidFireData[i].HandleMe = RapidFireGotHit;
      RobotRapidFireData[i].SafePassageIndex = &RobotData;
      RobotRapidFireData[i].data = i;
      RobotRapidFireData[i].mass = RLVal(75);
   }

   for (i = 0; i < NumberOfSixShooters; ++i)
   {
      RobotCussinData[i].Volume.max.x = -RLVal(0.2);
      RobotCussinData[i].Volume.max.y = -RLVal(0.2);
      RobotCussinData[i].Volume.max.z = -RLVal(0.2);
      RobotCussinData[i].Volume.min.x = RLVal(0.2);
      RobotCussinData[i].Volume.min.y = RLVal(0.2);
      RobotCussinData[i].Volume.min.z = RLVal(0.2);
      RobotCussinData[i].DamageICause = ConcussionDamage;
      RobotCussinData[i].PositioningFrame = Cussin->particles[i]->frame;
      Cussin->particles[i]->active = 0;
      RobotCussinData[i].NumOffensiveSpheres = 1;
      RobotCussinData[i].OffensiveSphereList[0] = &(RobotCussinSpot[i]);
      RobotCussinSpot[i].position = Cussin->particles[i]->frame;
      RobotCussinSpot[i].radius = ConcussionRadius;
      RobotCussinSpot[i].point1.x = 0;
      RobotCussinSpot[i].point1.y = 0;
      RobotCussinSpot[i].point1.z = 0;
      RobotCussinData[i].NumDefensiveSpheres = 0;
      RobotCussinData[i].NumOffensiveTubes = 0;
      RobotCussinData[i].AnimateMe = NULL;
      RobotCussinData[i].MoveMe = CussinMotionFunction;//Hide by Helen 11/16/96

	  /*
	  //add by Helen 11/16/96
      if(GameStates.IsNetplay)
	  {
		  if (PlayAsMonster)
		  {
			  if(LocalAIWorkingFlag)
		      {
				  RobotCussinData[i].MoveMe = LocalAICussinLatencyFunction;
			  }

		  }
		  else
		  {
			  RobotCussinData[i].MoveMe = CussinMotionFunction;
		  }
	  }
	  else
	  {
		  RobotCussinData[i].MoveMe = CussinMotionFunction;
	  }
      //end Helen
	  */

      RobotCussinData[i].HandleMe = CussinGotHit;
      RobotCussinData[i].SafePassageIndex = &RobotData;
      RobotCussinData[i].data = i;
	  RobotCussinData[i].mass = RobotCussinMass; //RLVal(25);
   }
}

void SetupZappaTube()
{
   ZappaOnScreen=0;
	MonsterZappaData.Volume.max.x = RLVal(1.0);
   MonsterZappaData.Volume.max.y = RLVal(1.0);
   MonsterZappaData.Volume.max.z = RLVal(1.0);
   MonsterZappaData.Volume.min.x = -RLVal(1.0);
   MonsterZappaData.Volume.min.y = -RLVal(1.0);
   MonsterZappaData.Volume.min.z = -RLVal(1.0);
   MonsterZappaData.DamageICause = MonsterZapDamage;
   MonsterZappaData.PositioningFrame = monstspew;
   MonsterZappaData.NumOffensiveSpheres = 0;
   MonsterZappaSpot.position = monstspew;
   MonsterZappaSpot.radius = MonsterZapRadius;
   MonsterZappaSpot.point1.x = 0;
   MonsterZappaSpot.point1.y = 0;
   MonsterZappaSpot.point1.z = 0;
   MonsterZappaSpot.point2.x = 0;
   MonsterZappaSpot.point2.y = 0;
   MonsterZappaSpot.point2.z = MonsterZapLength;

   MonsterZappaData.NumDefensiveSpheres = 0;
   MonsterZappaData.NumOffensiveTubes = 1;
   MonsterZappaData.OffensiveTubeList[0] = &MonsterZappaSpot;
   MonsterZappaData.AnimateMe = NULL;
   MonsterZappaData.MoveMe = ZappaMotionFunction;
   
   MonsterZappaData.HandleMe = ZappaGotHit;
   MonsterZappaData.SafePassageIndex = &MonsterData;
   MonsterZappaData.mass = MonsterZapMass;
   if (GameStates.CurrentLevel == NewYork)
   {
      int i;
      for(i = 0; i < NumberOfSixShooters; ++i)
      {
         NeallothRingsData[i].Volume.max.x = -RLVal(0.2);
         NeallothRingsData[i].Volume.max.y = -RLVal(0.2);
         NeallothRingsData[i].Volume.max.z = -RLVal(0.2);
         NeallothRingsData[i].Volume.min.x = RLVal(0.2);
         NeallothRingsData[i].Volume.min.y = RLVal(0.2);
         NeallothRingsData[i].Volume.min.z = RLVal(0.2);
         NeallothRingsData[i].DamageICause = NeallothRingsDamage;
         NeallothRingsData[i].PositioningFrame = NeallothRings->particles[i]->frame;
         NeallothRings->particles[i]->active = 0;
         NeallothRingsData[i].NumOffensiveSpheres = 1;
         NeallothRingsData[i].OffensiveSphereList[0] = &(NeallothRingsSpot[i]);
         NeallothRingsSpot[i].position = NeallothRings->particles[i]->frame;
         NeallothRingsSpot[i].radius = NeallothRingsRadius;
         NeallothRingsSpot[i].point1.x = 0;
         NeallothRingsSpot[i].point1.y = 0;
         NeallothRingsSpot[i].point1.z = 0;
         NeallothRingsData[i].NumDefensiveSpheres = 0;
         NeallothRingsData[i].NumOffensiveTubes = 0;
         NeallothRingsData[i].AnimateMe = NULL;
         NeallothRingsData[i].MoveMe = NRingsMotionFunction;
         NeallothRingsData[i].HandleMe = NRingsGotHit;
         NeallothRingsData[i].SafePassageIndex = &MonsterData;
         NeallothRingsData[i].data = i;
		 NeallothRingsData[i].mass = RLVal(125);
      }
   }
   else if (GameStates.CurrentLevel == Tokyo)
   {
      BombData.Volume.max.x = RLVal(0.4);
      BombData.Volume.max.y = RLVal(0.4);
      BombData.Volume.max.z = RLVal(0.4);
      BombData.Volume.min.x = -RLVal(0.4);
      BombData.Volume.min.y = -RLVal(0.4);
      BombData.Volume.min.z = -RLVal(0.4);
      BombData.PositioningFrame = BombSphere;
      BombData.NumOffensiveSpheres = 1;
      BombData.OffensiveSphereList[0] = &BombSpot;
      BombSpot.position = BombSphere;
      BombSpot.radius = GaingrisRadius;
      BombSpot.point1.x = 0;
      BombSpot.point1.y = 0;
      BombSpot.point1.z = 0;
      BombData.NumDefensiveSpheres = 0;
      BombData.NumOffensiveTubes = 0;
      BombData.AnimateMe = NULL;
      BombData.MoveMe = BombMotionFunction;
      BombData.HandleMe = BombGotHit;
      BombData.SafePassageIndex = &MonsterData;
      BombData.data = 0;
	  BombData.mass = RLVal(1500);
   }
   else if (GameStates.CurrentLevel == Rockies)
   {
      BombData.Volume.max.x = RLVal(0.4);
      BombData.Volume.max.y = RLVal(0.4);
      BombData.Volume.max.z = RLVal(0.4);
      BombData.Volume.min.x = -RLVal(0.4);
      BombData.Volume.min.y = -RLVal(0.4);
      BombData.Volume.min.z = -RLVal(0.4);
      BombData.DamageICause = KothosSnowballDamage;
      BombData.PositioningFrame = BombSphere;
      BombData.NumOffensiveSpheres = 1;
      BombData.OffensiveSphereList[0] = &BombSpot;
      BombSpot.position = BombSphere;
      BombSpot.radius = KothosSnowballInitRadius;
      BombSpot.point1.x = 0;
      BombSpot.point1.y = 0;
      BombSpot.point1.z = 0;
      BombData.NumDefensiveSpheres = 0;
      BombData.NumOffensiveTubes = 0;
      BombData.AnimateMe = NULL;
      BombData.MoveMe = SnowballMotionFunction;
      BombData.HandleMe = SnowballGotHit;
      BombData.SafePassageIndex = &MonsterData;
      BombData.data = 0;
	  BombData.mass = RLVal(70);
   }

   //in the process of converting from setting up the Robot homer hotspot to setting up the monster plasma hotspot.
}

RLTexture Robotzappatex, Robotzappatexmask;
RLIMSurfaceInfo Robotzappasurf;
RLFrame Robotzappaframe = 0;

void SetupRobotZappaTube()
{
   int i;
   extern ZappaData Robotzapdata[];
   extern RLColour theonlycolor;
   extern RLMaterial theonlymaterial;
   extern RLDevice Wdevice;


   for (i = 0; i < 6; i++) 
   {
	   RobotZappaHowLong[i] = RLVal(0);
	   RobotZappaData[i].Volume.max.x = RLVal(0.2);
	   RobotZappaData[i].Volume.max.y = RLVal(0.2);
	   RobotZappaData[i].Volume.max.z = RLVal(0.2);
	   RobotZappaData[i].Volume.min.x = -RLVal(0.2);
	   RobotZappaData[i].Volume.min.y = -RLVal(0.2);
	   RobotZappaData[i].Volume.min.z = -RLVal(0.2);
	   RobotZappaData[i].DamageICause = PeaShooterDamage;

      RobotZappaData[i].PositioningFrame = RLCreateFrame(behindthescene);

	   RobotZappaData[i].NumOffensiveSpheres = 0;
	   RobotZappaSpot.position = RobotZappaData[i].PositioningFrame;
	   RobotZappaSpot.radius = RobotZapRadius;
	   RobotZappaSpot.point1.x = 0;
	   RobotZappaSpot.point1.y = 0;
	   RobotZappaSpot.point1.z = 0;
	   RobotZappaSpot.point2.x = 0;
	   RobotZappaSpot.point2.y = 0;
	   RobotZappaSpot.point2.z = RLDivide(RobotZapLength,RLVal(2.0));

	   RobotZappaData[i].NumDefensiveSpheres = 0;
	   RobotZappaData[i].NumOffensiveTubes = 1;
	   RobotZappaData[i].OffensiveTubeList[0] = &RobotZappaSpot;
	   RobotZappaData[i].AnimateMe = NULL;
	   RobotZappaData[i].MoveMe = RobotZappaMotionFunction;//Hide by Helen 11/16/96

	   /*
	   //add by Helen 11/16/96
	   if(GameStates.IsNetplay)
	   {
		   if (PlayAsMonster)
		   {
			   if(LocalAIWorkingFlag)
			   {
			    	RobotZappaData[i].MoveMe = LocalAIZappaLatencyFunction;
			   }
	       }
		   else
		   {
			   RobotZappaData[i].MoveMe = RobotZappaMotionFunction;
		   }
	   }
	   else
	   {
		   RobotZappaData[i].MoveMe = RobotZappaMotionFunction;
	   }
	   //end Helen
	   */

	   RobotZappaData[i].HandleMe = RobotZappaGotHit;
	   RobotZappaData[i].SafePassageIndex = &RobotData;
	   RobotZappaData[i].mass = RLVal(50.0);

	   RobotZappaData[i].RemoveMeFlag = 1;
	   RobotZappaData[i].data = i;
	   
	   Robotzapdata[i].zucchini = CreateRobotZap(RobotZappaData[i].PositioningFrame, 
         (d3dapprs.transparency == FANCY || d3dapprs.transparency == SEMIFANCY || d3dapprs.transparency == TRANSLUCENT ?
         "peat.bmp" : "pea.bmp"));
	   
	   Robotzapdata[i].FarEnd.x = 0;
	   Robotzapdata[i].FarEnd.y = 0;
	   Robotzapdata[i].FarEnd.z = RLVal(3.5);
	   Robotzapdata[i].WhatDamage = 0;
   }
		


}



void InitRobotHotSpots()
{
	RLObject dummy;
	extern RLFrame Wscene;
#ifdef VisualRepresentation
    RLMesh Ball1, Ball2, Ball3, Ball4, Ball5, Ball6, Ball7, Ball8, Ball9;
	RLFrame frame1,frame2,frame3,frame4,frame5,frame6,frame7,frame8, frame9;
	RLFrame Scene;
	RLBox SphereBounds;
	RLValue width,dumwidth;

	Ball1 = RLLoadMesh("SPHERE0.x");
	Ball2 = RLLoadMesh("SPHERE0.x");
	Ball3 = RLLoadMesh("SPHERE0.x");
	Ball4 = RLLoadMesh("SPHERE0.x");
	Ball5 = RLLoadMesh("SPHERE0.x");
	Ball6 = RLLoadMesh("SPHERE0.x");
	Ball7 = RLLoadMesh("SPHERE0.x");
	Ball8 = RLLoadMesh("SPHERE0.x");
	Ball9 = RLLoadMesh("SPHERE0.x");
	RLMeshSetQuality(Ball1, RLRenderUnlitFlat);
	RLMeshSetQuality(Ball2, RLRenderUnlitFlat);
	RLMeshSetQuality(Ball3, RLRenderUnlitFlat);
	RLMeshSetQuality(Ball4, RLRenderUnlitFlat);
	RLMeshSetQuality(Ball5, RLRenderUnlitFlat);
	RLMeshSetQuality(Ball6, RLRenderUnlitFlat);
	RLMeshSetQuality(Ball7, RLRenderUnlitFlat);
	RLMeshSetQuality(Ball8, RLRenderUnlitFlat);
	RLMeshSetQuality(Ball9, RLRenderUnlitFlat);
	RLMeshGetBox(Ball1, &SphereBounds);
	width = (SphereBounds.max.x - SphereBounds.min.x) / 2;

#endif

	//The next section sets up the Robot's moving object data,
	//none of which depends on the particular Robot for now.
	//possible changes will make the number of defensive spheres depend on
	//a particular Robot, or the function to handle various things.
	SetupHomerHotSpot();
	SetupRobotZappaTube();
	RobotData.RemoveMeFlag = 0;
	RobotData.SafePassageIndex = NULL;
	RobotData.PositioningFrame = Robotframe;
	RobotData.NumOffensiveSpheres = 0;
	RobotData.NumOffensiveTubes = 0;
	RobotData.NumDefensiveSpheres = 3;
	RobotData.DefensiveSphereList[0] = &(RobotHotSpots[RobotChest]);
	RobotData.DefensiveSphereList[1] = &(RobotHotSpots[RobotPelvis]);
	RobotData.DefensiveSphereList[2] = &(RobotHotSpots[RobotHead]);
	RobotData.DamageICause = RobotMotionDamage;
	RobotData.DamageIveTaken = 0;
	RobotData.collisionflag = 0;
	RobotData.Volume.max.x = RobotBoxXZ[GameStates.CurrentRobot];
	RobotData.Volume.max.y = RobotHeight[GameStates.CurrentRobot];
	RobotData.Volume.max.z = RobotBoxXZ[GameStates.CurrentRobot];
	RobotData.Volume.min.x = -RobotBoxXZ[GameStates.CurrentRobot];
 	RobotData.Volume.min.y = 0;
	RobotData.Volume.min.z = -RobotBoxXZ[GameStates.CurrentRobot];

#ifdef VISUAL_BBOX
{
	RLIMSurfaceInfo boxysurf;
	extern RLMaterial theonlymaterial;
	extern RLDevice Wdevice;
	extern RLColour theonlycolor;
	RLTexture boxytex = RLLoadGif("sashld.gif", NULL);
	RLTexture boxytexmask = RLLoadGif("shield3m.gif", NULL);
	ApplyMask(boxytex, boxytexmask);
	RLIMInitialiseSurfaceInfo(Wdevice, theonlymaterial, theonlycolor, boxytex, &boxysurf);
	Robotboxyframe = RLCreateFrame(Wscene);
	LoadIntoDList("boxy.xaf", Robotboxyframe, boxytex, &boxysurf);
}
#endif

	RobotData.AnimateMe = thresh;
	RobotData.MoveMe = churn;
	RobotData.HandleMe = HandleRobotHit;
	RobotData.data = -1;

	if (GameStates.CurrentRobot == SabreRobot)
	{
		RobotChestName[5] = 's';
		RobotPelvisName[5] = 's';
		strcpy(RobotHeadName, "x3ds_shead");
		RobotRightFootName[5] = 's';
		RobotLeftFootName[5] = 's';
		strcpy(RobotRightSwordName, "x3ds_skatana");
		strcpy(RobotLeftSwordName, "x3ds_swakizashi");

		//WhichKindOfRobot = SabreStyle;
		RobotHotSpots[RobotChest].radius = RLVal(0.22);
		RobotHotSpots[RobotChest].point1.x = 0;
		RobotHotSpots[RobotChest].point1.y = 0;
		RobotHotSpots[RobotChest].point1.z = RLVal(-0.1);
		RobotHotSpots[RobotPelvis].radius = RLVal(0.27);
		RobotHotSpots[RobotPelvis].point1.x = 0;
		RobotHotSpots[RobotPelvis].point1.y = 0;
		RobotHotSpots[RobotPelvis].point1.z = RLVal(0.45);
		RobotSwordSpots[RobotRightSword].radius = RLVal(0.16);
		RobotSwordSpots[RobotRightSword].point1.x = 0;
		RobotSwordSpots[RobotRightSword].point1.y = 0;
		RobotSwordSpots[RobotRightSword].point1.z = 0;
		RobotSwordSpots[RobotRightSword].point2.x = 0;
		RobotSwordSpots[RobotRightSword].point2.y = 0;
		RobotSwordSpots[RobotRightSword].point2.z = RLVal(1.5);
		RobotSwordSpots[RobotLeftSword].radius = RLVal(0.16);
		RobotSwordSpots[RobotLeftSword].point1.x = 0;
		RobotSwordSpots[RobotLeftSword].point1.y = 0;
		RobotSwordSpots[RobotLeftSword].point1.z = 0;
		RobotSwordSpots[RobotLeftSword].point2.x = 0;
		RobotSwordSpots[RobotLeftSword].point2.y = 0;
		RobotSwordSpots[RobotLeftSword].point2.z = RLVal(0.8);
		RobotHotSpots[RobotHead].radius = RLVal(0.11);
		RobotHotSpots[RobotHead].point1.x=0;
		RobotHotSpots[RobotHead].point1.y = 0;
		RobotHotSpots[RobotHead].point1.z = 0;
		RobotHotSpots[RobotRightFoot].radius = RLVal(0.18);
		RobotHotSpots[RobotRightFoot].point1.x = 0;
		RobotHotSpots[RobotRightFoot].point1.y = 0;
		RobotHotSpots[RobotRightFoot].point1.z = 0;
		RobotHotSpots[RobotLeftFoot].radius = RLVal(0.18);
		RobotHotSpots[RobotLeftFoot].point1.x = 0;
		RobotHotSpots[RobotLeftFoot].point1.y = 0;
		RobotHotSpots[RobotLeftFoot].point1.z = 0;
	}
	else if (GameStates.CurrentRobot == StealthRobot)
	{
		RobotChestName[5] = 'l';
		RobotPelvisName[5] = 'l';
		strcpy(RobotHeadName, "x3ds_lhead");
		RobotRightFootName[5] = 'l';
		RobotLeftFootName[5] = 'l';
		strcpy(RobotRightSwordName, "x3ds_lkatana");
		strcpy(RobotLeftSwordName, "x3ds_lwakizashi");

		//WhichKindOfRobot = StealthStyle;
		RobotHotSpots[RobotChest].radius = RLVal(0.15);
		RobotHotSpots[RobotChest].point1.x = 0;
		RobotHotSpots[RobotChest].point1.y = 0;
		RobotHotSpots[RobotChest].point1.z = RLVal(-0.1);
		RobotHotSpots[RobotPelvis].radius = RLVal(0.15);
		RobotHotSpots[RobotPelvis].point1.x = 0;
		RobotHotSpots[RobotPelvis].point1.y = -RLVal(0.15);
		RobotHotSpots[RobotPelvis].point1.z = 0;
		RobotSwordSpots[RobotRightSword].radius = RLVal(0.20);
		RobotSwordSpots[RobotRightSword].point1.x = 0;
		RobotSwordSpots[RobotRightSword].point1.y = 0;
		RobotSwordSpots[RobotRightSword].point1.z = 0;
		RobotSwordSpots[RobotRightSword].point2.x = 0;
		RobotSwordSpots[RobotRightSword].point2.y = 0;
		RobotSwordSpots[RobotRightSword].point2.z = RLVal(1.01);
		RobotSwordSpots[RobotLeftSword].radius = RLVal(0.06);
		RobotSwordSpots[RobotLeftSword].point1.x = 0;
		RobotSwordSpots[RobotLeftSword].point1.y = 0;
		RobotSwordSpots[RobotLeftSword].point1.z = 0;
		RobotSwordSpots[RobotLeftSword].point2.x = 0;
		RobotSwordSpots[RobotLeftSword].point2.y = 0;
		RobotSwordSpots[RobotLeftSword].point2.z = RLVal(0.8);
		RobotHotSpots[RobotHead].radius = RLVal(0.09);
		RobotHotSpots[RobotHead].point1.x = 0;
		RobotHotSpots[RobotHead].point1.y = 0;
		RobotHotSpots[RobotHead].point1.z = 0;
		RobotHotSpots[RobotRightFoot].radius = RLVal(0.13);
		RobotHotSpots[RobotRightFoot].point1.x = 0;
		RobotHotSpots[RobotRightFoot].point1.y = 0;
		RobotHotSpots[RobotRightFoot].point1.z = 0;
		RobotHotSpots[RobotLeftFoot].radius = RLVal(0.13);
		RobotHotSpots[RobotLeftFoot].point1.x = 0;
		RobotHotSpots[RobotLeftFoot].point1.y = 0;
		RobotHotSpots[RobotLeftFoot].point1.z = 0;
	}
	else if(GameStates.CurrentRobot == MerRobot)
	{
		RobotChestName[5] = 'm';
		RobotPelvisName[5] = 'm';
		strcpy(RobotHeadName, "x3ds_mchest");
		RobotRightFootName[5] = 'm';
		RobotLeftFootName[5] = 'm';
		strcpy(RobotRightSwordName, "x3ds_mhook");
		strcpy(RobotLeftSwordName, "x3ds_mshooter");

		//WhichKindOfRobot = MerStyle;
		RobotHotSpots[RobotChest].radius = RLVal(0.44);
		RobotHotSpots[RobotChest].point1.x = 0;
		RobotHotSpots[RobotChest].point1.y = RLVal(0.04);
		RobotHotSpots[RobotChest].point1.z = 0;
		RobotHotSpots[RobotPelvis].radius = RLVal(0.45);
		RobotHotSpots[RobotPelvis].point1.x = 0;
		RobotHotSpots[RobotPelvis].point1.y = 0;
		RobotHotSpots[RobotPelvis].point1.z = RLVal(0.45);
		RobotSwordSpots[RobotRightSword].radius = RLVal(0.48);
		RobotSwordSpots[RobotRightSword].point1.x = 0;
		RobotSwordSpots[RobotRightSword].point1.y = 0;
		RobotSwordSpots[RobotRightSword].point1.z = 0;
		RobotSwordSpots[RobotRightSword].point2.x = 0;
		RobotSwordSpots[RobotRightSword].point2.y = RLVal(1.43);
		RobotSwordSpots[RobotRightSword].point2.z = 0;
		RobotSwordSpots[RobotLeftSword].radius = RLVal(0.08);
		RobotSwordSpots[RobotLeftSword].point1.x = 0;
		RobotSwordSpots[RobotLeftSword].point1.y = 0;
		RobotSwordSpots[RobotLeftSword].point1.z = 0;
		RobotSwordSpots[RobotLeftSword].point2.x = 0;
		RobotSwordSpots[RobotLeftSword].point2.y = RLVal(0.099);
		RobotSwordSpots[RobotLeftSword].point2.z = 0;
		RobotHotSpots[RobotHead].radius = RLVal(0.25);
		RobotHotSpots[RobotHead].point1.x = 0;
		RobotHotSpots[RobotHead].point1.y = 0;
		RobotHotSpots[RobotHead].point1.z = -RLVal(0.5);
		RobotHotSpots[RobotRightFoot].radius = RLVal(0.27);
		RobotHotSpots[RobotRightFoot].point1.x = 0;
		RobotHotSpots[RobotRightFoot].point1.y = 0;
		RobotHotSpots[RobotRightFoot].point1.z = 0;
		RobotHotSpots[RobotLeftFoot].radius = RLVal(0.27);
		RobotHotSpots[RobotLeftFoot].point1.x = 0;
		RobotHotSpots[RobotLeftFoot].point1.y = 0;
		RobotHotSpots[RobotLeftFoot].point1.z = 0;
	}
	else if (GameStates.CurrentRobot == KataRobot)
	{
		RobotChestName[5] = 'k';
		RobotPelvisName[5] = 'k';
		strcpy(RobotHeadName, "x3ds_khead");
		RobotRightFootName[5] = 'k';
		RobotLeftFootName[5] = 'k';
		strcpy(RobotRightSwordName, "x3ds_kkatana");
		strcpy(RobotLeftSwordName, "x3ds_kwakizashi");

		//WhichKindOfRobot = KataStyle;
		RobotHotSpots[RobotChest].radius = RLVal(0.22);
		RobotHotSpots[RobotChest].point1.x = 0;
		RobotHotSpots[RobotChest].point1.y = 0;
		RobotHotSpots[RobotChest].point1.z = RLVal(-0.1);
		RobotHotSpots[RobotPelvis].radius = RLVal(0.24);
		RobotHotSpots[RobotPelvis].point1.x = 0;
		RobotHotSpots[RobotPelvis].point1.y = -RLVal(0.35);
		RobotHotSpots[RobotPelvis].point1.z = 0;
		RobotSwordSpots[RobotRightSword].radius = RLVal(0.16);
		RobotSwordSpots[RobotRightSword].point1.x = 0;
		RobotSwordSpots[RobotRightSword].point1.y = 0;
		RobotSwordSpots[RobotRightSword].point1.z = 0;
		RobotSwordSpots[RobotRightSword].point2.x = 0;
		RobotSwordSpots[RobotRightSword].point2.y = 0;
		RobotSwordSpots[RobotRightSword].point2.z = RLVal(1.5);
		RobotSwordSpots[RobotLeftSword].radius = RLVal(0.16);
		RobotSwordSpots[RobotLeftSword].point1.x = 0;
		RobotSwordSpots[RobotLeftSword].point1.y = 0;
		RobotSwordSpots[RobotLeftSword].point1.z = 0;
		RobotSwordSpots[RobotLeftSword].point2.x = 0;
		RobotSwordSpots[RobotLeftSword].point2.y = 0;
		RobotSwordSpots[RobotLeftSword].point2.z = RLVal(0.8);
		RobotHotSpots[RobotHead].radius = RLVal(0.11);
		RobotHotSpots[RobotHead].point1.x = 0;
		RobotHotSpots[RobotHead].point1.y = 0;
		RobotHotSpots[RobotHead].point1.z = 0;
		RobotHotSpots[RobotRightFoot].radius = RLVal(0.18);
		RobotHotSpots[RobotRightFoot].point1.x = 0;
		RobotHotSpots[RobotRightFoot].point1.y = 0;
		RobotHotSpots[RobotRightFoot].point1.z = 0;
		RobotHotSpots[RobotLeftFoot].radius = RLVal(0.18);
		RobotHotSpots[RobotLeftFoot].point1.x = 0;
		RobotHotSpots[RobotLeftFoot].point1.y = 0;
		RobotHotSpots[RobotLeftFoot].point1.z = 0;
	}
	else if (GameStates.CurrentRobot == KaberRobot)
	{
		RobotChestName[5] = 'b';
		RobotPelvisName[5] = 'b';
		strcpy(RobotHeadName, "x3ds_bhead");
		RobotRightFootName[5] = 'b';
		RobotLeftFootName[5] = 'b';
		strcpy(RobotRightSwordName, "x3ds_claymore");
		strcpy(RobotLeftSwordName, "x3ds_bshooter");

		//WhichKindOfRobot = KaberStyle;
		RobotHotSpots[RobotChest].radius = RLVal(0.44);
		RobotHotSpots[RobotChest].point1.x = 0;
		RobotHotSpots[RobotChest].point1.y = 0;
		RobotHotSpots[RobotChest].point1.z = RLVal(0);
		RobotHotSpots[RobotPelvis].radius = RLVal(0.5);
		RobotHotSpots[RobotPelvis].point1.x = 0;
		RobotHotSpots[RobotPelvis].point1.y = -RLVal(0.45);
		RobotHotSpots[RobotPelvis].point1.z = 0;
		RobotSwordSpots[RobotRightSword].radius = RLVal(0.32);
		RobotSwordSpots[RobotRightSword].point1.x = 0;
		RobotSwordSpots[RobotRightSword].point1.y = 0;
		RobotSwordSpots[RobotRightSword].point1.z = 0;
		RobotSwordSpots[RobotRightSword].point2.x = 0;
		RobotSwordSpots[RobotRightSword].point2.y = RLVal(2.11);
		RobotSwordSpots[RobotRightSword].point2.z = 0;
		RobotSwordSpots[RobotLeftSword].radius = RLVal(0.12);
		RobotSwordSpots[RobotLeftSword].point1.x = 0;
		RobotSwordSpots[RobotLeftSword].point1.y = 0;
		RobotSwordSpots[RobotLeftSword].point1.z = 0;
		RobotSwordSpots[RobotLeftSword].point2.x = 0;
		RobotSwordSpots[RobotLeftSword].point2.y = RLVal(0.11);
		RobotSwordSpots[RobotLeftSword].point2.z = 0;
		RobotHotSpots[RobotHead].radius = RLVal(0.17);
		RobotHotSpots[RobotHead].point1.x = 0;
		RobotHotSpots[RobotHead].point1.y = 0;
		RobotHotSpots[RobotHead].point1.z = 0;
		RobotHotSpots[RobotRightFoot].radius = RLVal(0.27);
		RobotHotSpots[RobotRightFoot].point1.x = 0;
		RobotHotSpots[RobotRightFoot].point1.y = 0;
		RobotHotSpots[RobotRightFoot].point1.z = 0;
		RobotHotSpots[RobotLeftFoot].radius = RLVal(0.27);
		RobotHotSpots[RobotLeftFoot].point1.x = 0;
		RobotHotSpots[RobotLeftFoot].point1.y = 0;
		RobotHotSpots[RobotLeftFoot].point1.z = 0;
	}
	//else
	//{
		//WhichKindOfRobot = UnknownStyle;
	//}


	dummy = RLObjectFromName(RobotChestName);
	if (dummy)
	{
		if (SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, (void **) &(RobotHotSpots[RobotChest].position))))
		{
	#ifdef VisualRepresentation
		Scene = RLFrameGetScene(dummy);
		frame1 = RLCreateFrame(Scene);
		dumwidth = RLDivide(RobotHotSpots[RobotChest].radius, width);;
		RLMeshScale(Ball1, dumwidth, dumwidth, dumwidth);
		RobotHotSpots[RobotChest].BallColor=
			RLCreateColourRGBA(RLVal(0), RLVal(1), RLVal(0), RLVal(1));
		RLFrameAddVisual(frame1, Ball1);
		RobotHotSpots[RobotChest].BallFrame1 = frame1;
		RLFrameSetColour(RobotHotSpots[RobotChest].BallFrame1,
			RobotHotSpots[RobotChest].BallColor);
		RLFrameSetMaterialMode(RobotHotSpots[RobotChest].BallFrame1,
			RLMaterialFromFrame);
		RobotHotSpots[RobotChest].BallFrame2 = NULL;

		//LGH add release
		RLObjectDestroy (Scene);
		RLObjectDestroy (frame1);
	#endif      
		RobotHotSpots[RobotChest].position->lpVtbl->Release (RobotHotSpots[RobotChest].position);
		}
		dummy->lpVtbl->Release (dummy);
	}
	
	dummy = RLObjectFromName(RobotPelvisName);
	if (dummy)
	{
		if (SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, (void **) &(RobotHotSpots[RobotPelvis].position))))
		{
	#ifdef VisualRepresentation
		Scene = RLFrameGetScene(dummy);
		frame2 = RLCreateFrame(Scene);
		dumwidth = RLDivide(RobotHotSpots[RobotPelvis].radius, width);;
		RLMeshScale(Ball2, dumwidth, dumwidth, dumwidth);
		RobotHotSpots[RobotPelvis].BallColor=RLCreateColourRGBA(RLVal(0),RLVal(1),RLVal(1),RLVal(1));
		RLFrameAddVisual(frame2, Ball2);
		RobotHotSpots[RobotPelvis].BallFrame1 = frame2;
		RLFrameSetColour(RobotHotSpots[RobotPelvis].BallFrame1, 
			RobotHotSpots[RobotPelvis].BallColor);
		RLFrameSetMaterialMode(RobotHotSpots[RobotPelvis].BallFrame1,
			RLMaterialFromFrame);
		RobotHotSpots[RobotPelvis].BallFrame2 = NULL;

		//LGH add release
		RLObjectDestroy (Scene);
		RLObjectDestroy (frame2);
	#endif      
		RobotHotSpots[RobotPelvis].position->lpVtbl->Release (RobotHotSpots[RobotPelvis].position);
		}
		dummy->lpVtbl->Release (dummy);
	}

	dummy = RLObjectFromName(RobotRightSwordName);
	if (dummy)
	{
		if (SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, (void **) &(RobotSwordSpots[RobotRightSword].position))))
		{
	#ifdef VisualRepresentation
		Scene = RLFrameGetScene(dummy);
		frame3 = RLCreateFrame(Scene);
		dumwidth = RLDivide(RobotSwordSpots[RobotRightSword].radius,width);;
		RLMeshScale(Ball3, dumwidth, dumwidth, dumwidth);
		RobotSwordSpots[RobotRightSword].BallColor = 
			RLCreateColourRGBA(RLVal(1),RLVal(0),RLVal(0),RLVal(1));
		RLFrameAddVisual(frame3, Ball3);
		RobotSwordSpots[RobotRightSword].BallFrame1 = frame3;
		RLFrameSetColour(RobotSwordSpots[RobotRightSword].BallFrame1,
			RobotSwordSpots[RobotRightSword].BallColor);
		RLFrameSetMaterialMode(RobotSwordSpots[RobotRightSword].BallFrame1,
			RLMaterialFromFrame);

		frame4 = RLCreateFrame(Scene);
		RLMeshScale(Ball4, dumwidth, dumwidth, dumwidth);
		RLFrameAddVisual(frame4, Ball4);
		RobotSwordSpots[RobotRightSword].BallFrame2 = frame4;
		RLFrameSetColour(RobotSwordSpots[RobotRightSword].BallFrame2,
			RobotSwordSpots[RobotRightSword].BallColor);
		RLFrameSetMaterialMode(RobotSwordSpots[RobotRightSword].BallFrame2,
			RLMaterialFromFrame);

		//LGH add release
		RLObjectDestroy (Scene);
		RLObjectDestroy (frame3);
	#endif      
		RobotSwordSpots[RobotRightSword].position->lpVtbl->Release (RobotSwordSpots[RobotRightSword].position);
		}
		dummy->lpVtbl->Release (dummy);
	}
    dummy = RLObjectFromName(RobotLeftSwordName);
    if (dummy)
    {
		if (SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, (void **) &(RobotSwordSpots[RobotLeftSword].position))))
		{
	#ifdef VisualRepresentation
		Scene = RLFrameGetScene(dummy);
		frame5 = RLCreateFrame(Scene);
		dumwidth = RLDivide(RobotSwordSpots[RobotLeftSword].radius,width);;
		RLMeshScale(Ball5, dumwidth, dumwidth, dumwidth);
		RobotSwordSpots[RobotLeftSword].BallColor = 
			RLCreateColourRGBA(RLVal(1), RLVal(0), RLVal(0), RLVal(1));
		RLFrameAddVisual(frame5, Ball5);
		RobotSwordSpots[RobotLeftSword].BallFrame1 = frame5;
		RLFrameSetColour(RobotSwordSpots[RobotLeftSword].BallFrame1,
			RobotSwordSpots[RobotLeftSword].BallColor);
		RLFrameSetMaterialMode(RobotSwordSpots[RobotLeftSword].BallFrame1,
			RLMaterialFromFrame);

		frame6 = RLCreateFrame(Scene);
		RLMeshScale(Ball6, dumwidth, dumwidth, dumwidth);
		RLFrameAddVisual(frame6, Ball6);
		RobotSwordSpots[RobotLeftSword].BallFrame2 = frame6;
		RLFrameSetColour(RobotSwordSpots[RobotLeftSword].BallFrame2,
			RobotSwordSpots[RobotLeftSword].BallColor);
		RLFrameSetMaterialMode(RobotSwordSpots[RobotLeftSword].BallFrame2,
			RLMaterialFromFrame);

		//LGH add release
		RLObjectDestroy (Scene);
		RLObjectDestroy (frame5);
	#endif      

		RobotSwordSpots[RobotLeftSword].position->lpVtbl->Release (RobotSwordSpots[RobotLeftSword].position);
        }    
		dummy->lpVtbl->Release (dummy);
    }

    dummy = RLObjectFromName(RobotHeadName);
    if (dummy)
    {
		if(SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, (void **) &(RobotHotSpots[RobotHead].position))))
		{
#ifdef VisualRepresentation
      Scene = RLFrameGetScene(dummy);
      frame7 = RLCreateFrame(Scene);
      dumwidth = RLDivide(RobotHotSpots[RobotHead].radius, width);;
      RLMeshScale(Ball7, dumwidth, dumwidth, dumwidth);
      RobotHotSpots[RobotHead].BallColor = 
		  RLCreateColourRGBA(RLVal(0), RLVal(1), RLVal(1), RLVal(1));
      RLFrameAddVisual(frame7, Ball7);
      RobotHotSpots[RobotHead].BallFrame1 = frame7;
      RLFrameSetColour(RobotHotSpots[RobotHead].BallFrame1,
		  RobotHotSpots[RobotHead].BallColor);
      RLFrameSetMaterialMode(RobotHotSpots[RobotHead].BallFrame1, RLMaterialFromFrame);
      RobotHotSpots[RobotPelvis].BallFrame2 = NULL;

		//LGH add release
		RLObjectDestroy (Scene);
		RLObjectDestroy (frame7);
#endif      
		RobotHotSpots[RobotHead].position->lpVtbl->Release (RobotHotSpots[RobotHead].position);
		}
		dummy->lpVtbl->Release (dummy);
    }

    dummy = RLObjectFromName(RobotRightFootName);
    if (dummy)
    {
	    if (SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, (void **) &(RobotHotSpots[RobotRightFoot].position))))
		{
#ifdef VisualRepresentation
      Scene = RLFrameGetScene(dummy);
      frame8 = RLCreateFrame(Scene);
      dumwidth = RLDivide(RobotHotSpots[RobotRightFoot].radius, width);;
      RLMeshScale(Ball8,dumwidth,dumwidth, dumwidth);
      RobotHotSpots[RobotRightFoot].BallColor = 
		  RLCreateColourRGBA(RLVal(1), RLVal(1), RLVal(0), RLVal(1));
      RLFrameAddVisual(frame8, Ball8);
      RobotHotSpots[RobotRightFoot].BallFrame1 = frame8;
      RLFrameSetColour(RobotHotSpots[RobotRightFoot].BallFrame1, 
		  RobotHotSpots[RobotRightFoot].BallColor);
      RLFrameSetMaterialMode(RobotHotSpots[RobotRightFoot].BallFrame1,
		  RLMaterialFromFrame);
      RobotHotSpots[RobotRightFoot].BallFrame2 = NULL;

		//LGH add release
		RLObjectDestroy (Scene);
		RLObjectDestroy (frame8);
#endif      
		RobotHotSpots[RobotRightFoot].position->lpVtbl->Release (RobotHotSpots[RobotRightFoot].position);
	    }
		dummy->lpVtbl->Release (dummy);
    }

    dummy = RLObjectFromName(RobotLeftFootName);
    if (dummy)
    {
	    if (SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, (void **) &(RobotHotSpots[RobotLeftFoot].position))))
		{
#ifdef VisualRepresentation
      Scene = RLFrameGetScene(dummy);
      frame9 = RLCreateFrame(Scene);
      dumwidth = RLDivide(RobotHotSpots[RobotLeftFoot].radius,width);;
      RLMeshScale(Ball9, dumwidth, dumwidth, dumwidth);
      RobotHotSpots[RobotLeftFoot].BallColor = 
		  RLCreateColourRGBA(RLVal(1),RLVal(1),RLVal(0),RLVal(1));
      RLFrameAddVisual(frame9, Ball9);
      RobotHotSpots[RobotLeftFoot].BallFrame1 = frame9;
      RLFrameSetColour(RobotHotSpots[RobotLeftFoot].BallFrame1,
		  RobotHotSpots[RobotLeftFoot].BallColor);
      RLFrameSetMaterialMode(RobotHotSpots[RobotLeftFoot].BallFrame1,
		  RLMaterialFromFrame);
      RobotHotSpots[RobotRightFoot].BallFrame2 = NULL;

		//LGH add release
		RLObjectDestroy (Scene);
		RLObjectDestroy (frame9);
#endif      
		RobotHotSpots[RobotLeftFoot].position->lpVtbl->Release (RobotHotSpots[RobotLeftFoot].position);
		}
		dummy->lpVtbl->Release (dummy);
    }
}

void BootAllRobotFrames()
{
	RLObject dummy;
	RLFrame dummyframe;
	dummy = RLObjectFromName(RobotChestName);
	if (dummy)
	{
		if (SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, (void **) &(dummyframe))))
		{
			MDFreeD3DFrame(dummyframe);
		}
	}
	dummy = RLObjectFromName(RobotPelvisName);
	if (dummy)
	{
		if (SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, (void **) &(dummyframe))))
		{
			MDFreeD3DFrame(dummyframe);
		}
	}
	dummy = RLObjectFromName(RobotRightSwordName);
	if (dummy)
	{
		if (SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, (void **) &(dummyframe))))
		{
			MDFreeD3DFrame(dummyframe);
		}
	}
    dummy = RLObjectFromName(RobotLeftSwordName);
	if (dummy)
	{
		if (SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, (void **) &(dummyframe))))
		{
			MDFreeD3DFrame(dummyframe);
		}
	}
    dummy = RLObjectFromName(RobotHeadName);
	while(dummy)
	{
		int retval;
		retval = dummy->lpVtbl->Release(dummy);
		retval = dummy->lpVtbl->Release(dummy);
		dummy = RLObjectFromName(RobotHeadName);
	}
    dummy = RLObjectFromName(RobotRightFootName);
	if (dummy)
	{
		if (SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, (void **) &(dummyframe))))
		{
			MDFreeD3DFrame(dummyframe);
		}
	}
    dummy = RLObjectFromName(RobotLeftFootName);
	if (dummy)
	{
		if (SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, (void **) &(dummyframe))))
		{
			MDFreeD3DFrame(dummyframe);
		}
	}
}


void InitMonsterHotSpots()
{
	RLObject dummy;
	extern RLFrame Wscene;
#ifdef VisualRepresentation
    RLMesh Ball1,Ball2,Ball3,Ball4,Ball5,Ball6;

	RLFrame frame1,frame2,frame3,frame4,frame5,frame6;
	RLFrame Scene;
	RLBox SphereBounds;
	RLValue width,dumwidth;


	Ball1 = RLLoadMesh("SPHERE0.x");
	Ball2 = RLLoadMesh("SPHERE0.x");
	Ball3 = RLLoadMesh("SPHERE0.x");
	Ball4 = RLLoadMesh("SPHERE0.x");
	Ball5 = RLLoadMesh("SPHERE0.x");
	Ball6 = RLLoadMesh("SPHERE0.x");
	RLMeshSetQuality(Ball1, RLRenderUnlitFlat);
	RLMeshSetQuality(Ball2, RLRenderUnlitFlat);
	RLMeshSetQuality(Ball3, RLRenderUnlitFlat);
	RLMeshSetQuality(Ball4, RLRenderUnlitFlat);
	RLMeshSetQuality(Ball5, RLRenderUnlitFlat);
	RLMeshSetQuality(Ball6, RLRenderUnlitFlat);

	RLMeshGetBox(Ball1, &SphereBounds);
	width = (SphereBounds.max.x - SphereBounds.min.x)/2;

#endif
	//The next section sets up the monster's moving object data,
	//none of which depends on the particular monster for now.
	//possible changes will make the number of defensive spheres depend on
	//a particular monster, or the function to handle various things.
	SetupZappaTube();
	MonsterData.SafePassageIndex = NULL;
	MonsterData.RemoveMeFlag = 0;
	MonsterData.PositioningFrame = monstframe;

	MonsterData.NumOffensiveSpheres = 0;
	MonsterData.NumOffensiveTubes = 0;
	MonsterData.NumDefensiveSpheres = 2;
	MonsterData.DefensiveSphereList[0] = &(MonsterHotSpots[RoggoshBody]);
	MonsterData.DefensiveSphereList[1] = &(MonsterHotSpots[RoggoshHead]);
	MonsterData.DamageICause = MonsterMotionDamage;
	MonsterData.DamageIveTaken = 0;
	MonsterData.collisionflag = 0;

#ifdef VISUAL_BBOX
{
	RLIMSurfaceInfo boxysurf;
	extern RLMaterial theonlymaterial;
	extern RLDevice Wdevice;
	extern RLColour theonlycolor;
	RLTexture boxytex = RLLoadGif("sashld.gif", NULL);
	RLTexture boxytexmask = RLLoadGif("shield3m.gif", NULL);
	ApplyMask(boxytex, boxytexmask);
	RLIMInitialiseSurfaceInfo(Wdevice, theonlymaterial, theonlycolor, boxytex, &boxysurf);
	monsterboxyframe = RLCreateFrame(Wscene);
	LoadIntoDList("boxy.xaf", monsterboxyframe, boxytex, &boxysurf);
}
#endif

	MonsterData.data = -1;
	MonsterData.AnimateMe = tenderize;
	MonsterData.MoveMe = knead;
	MonsterData.HandleMe = HandleMonsterHit;

	switch(GameStates.CurrentLevel)
	{
	   case Trainer:
			strcpy(MonsterChestName, "x3ds_BODY");
			strcpy(MonsterHeadName, "x3ds_HEAD");
			strcpy(MonsterRightHandName, "x3ds_RITECLAW1");
			strcpy(MonsterLeftHandName, "x3ds_LEFTCLAW1");
			strcpy(MonsterWeaponName, "x3ds_PLASMATAIL");
			break;
	   case Mojave:
			strcpy(MonsterChestName, "x3ds_body");
			strcpy(MonsterHeadName, "x3ds_head");
			strcpy(MonsterRightHandName, "x3ds_riteclaw1");
			strcpy(MonsterLeftHandName, "x3ds_leftclaw1");
			strcpy(MonsterWeaponName, "x3ds_plasmatail");
	        break;
	   case Rockies:
			strcpy(MonsterChestName, "x3ds_chest");
			strcpy(MonsterHeadName, "x3ds_head");
			strcpy(MonsterRightHandName, "x3ds_head");
			strcpy(MonsterLeftHandName, "x3ds_head");
			strcpy(MonsterWeaponName, "x3ds_head");
	        break;
	   case Hawaii:
			strcpy(MonsterChestName, "x3ds_TCHEST");
			strcpy(MonsterHeadName, "x3ds_THEAD");
			strcpy(MonsterRightHandName, "x3ds_THEAD");
			strcpy(MonsterLeftHandName, "x3ds_THEAD");
			strcpy(MonsterWeaponName, "x3ds_TCHEST");
	        break;
	   case SanFrancisco:
			strcpy(MonsterChestName, "x3ds_shpelvis");
			strcpy(MonsterHeadName, "x3ds_shbodyhead");
			strcpy(MonsterRightHandName, "x3ds_shpelvis");
			strcpy(MonsterLeftHandName, "x3ds_shpelvis");
			strcpy(MonsterWeaponName, "x3ds_shbodyhead");
	        break;
	   case NewYork:
			strcpy(MonsterChestName, "x3ds_nchest");
			strcpy(MonsterHeadName, "x3ds_nhead");
			strcpy(MonsterRightHandName, "x3ds_nhead");
			strcpy(MonsterLeftHandName, "x3ds_nhead");
			strcpy(MonsterWeaponName, "x3ds_nhead");

	        break;
	   case Tokyo:
			strcpy(MonsterChestName, "x3ds_gpelvis");
			strcpy(MonsterHeadName, "x3ds_ghead");
			strcpy(MonsterRightHandName, "x3ds_gpelvis");
			strcpy(MonsterLeftHandName, "x3ds_ghead");
			strcpy(MonsterWeaponName, "x3ds_gstinger");

	        break;
	}

	dummy = RLObjectFromName(MonsterChestName);
	if (dummy)
	{
		if(SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, (void **) &(MonsterHotSpots[RoggoshBody].position))))
		{
			MonsterHotSpots[RoggoshBody].radius = RLVal(0.97);
			MonsterHotSpots[RoggoshBody].point1.x = 0;
			MonsterHotSpots[RoggoshBody].point1.y = RLVal(0);
			MonsterHotSpots[RoggoshBody].point1.z = 0;

		#ifdef VisualRepresentation
			Scene = RLFrameGetScene(dummy);
			frame1 = RLCreateFrame(Scene);
			dumwidth = RLDivide(MonsterHotSpots[RoggoshBody].radius,width);;
			RLMeshScale(Ball1, dumwidth, dumwidth, dumwidth);						
			MonsterHotSpots[RoggoshBody].BallColor = 
				RLCreateColourRGBA(RLVal(0),RLVal(1),RLVal(0),RLVal(1));
			RLFrameAddVisual(frame1, Ball1);
			MonsterHotSpots[RoggoshBody].BallFrame1 = frame1;
			RLFrameSetColour(MonsterHotSpots[RoggoshBody].BallFrame1,
				MonsterHotSpots[RoggoshBody].BallColor);
			RLFrameSetMaterialMode(MonsterHotSpots[RoggoshBody].BallFrame1,
				RLMaterialFromFrame);
			MonsterHotSpots[RoggoshBody].BallFrame2 = NULL;

			//LGH add release
			RLObjectDestroy (Scene);
			RLObjectDestroy (frame1);
		#endif      
			MonsterHotSpots[RoggoshBody].position->lpVtbl->Release (MonsterHotSpots[RoggoshBody].position);
		}
		dummy->lpVtbl->Release (dummy);
	}
	
	dummy = RLObjectFromName(MonsterHeadName);
	if(dummy)
	{
		if(SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, (void **) &(MonsterHotSpots[RoggoshHead].position))))
		{
		MonsterHotSpots[RoggoshHead].radius=RLVal(0.15);
		MonsterHotSpots[RoggoshHead].point1.x=0;
		MonsterHotSpots[RoggoshHead].point1.y=0;
		MonsterHotSpots[RoggoshHead].point1.z=0;
	#ifdef VisualRepresentation
		Scene=RLFrameGetScene(dummy);
		frame2=RLCreateFrame(Scene);
		dumwidth=RLDivide(MonsterHotSpots[RoggoshHead].radius,width);
        RLMeshScale(Ball2,dumwidth,dumwidth,dumwidth);
		MonsterHotSpots[RoggoshHead].BallColor=RLCreateColourRGBA(RLVal(0),RLVal(1),RLVal(0),RLVal(1));
		RLFrameAddVisual(frame2,Ball2);
		MonsterHotSpots[RoggoshHead].BallFrame1=frame2;
		RLFrameSetColour(MonsterHotSpots[RoggoshHead].BallFrame1,MonsterHotSpots[RoggoshHead].BallColor);
		RLFrameSetMaterialMode(MonsterHotSpots[RoggoshHead].BallFrame1,RLMaterialFromFrame);
		MonsterHotSpots[RoggoshHead].BallFrame2=NULL;

		//LGH add release
		RLObjectDestroy (Scene);
		RLObjectDestroy (frame2);
	#endif      
		MonsterHotSpots[RoggoshHead].position->lpVtbl->Release (MonsterHotSpots[RoggoshHead].position);
		}
		dummy->lpVtbl->Release (dummy);
	}

	dummy = RLObjectFromName(MonsterRightHandName);
	if (dummy)
	{
		if (SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, 
			(void **) &(MonsterHotSpots[RoggoshRightClaw].position))))
		{
			MonsterHotSpots[RoggoshRightClaw].radius = RLVal(0.22);
			MonsterHotSpots[RoggoshRightClaw].point1.x = 0;
			MonsterHotSpots[RoggoshRightClaw].point1.y = 0;
			MonsterHotSpots[RoggoshRightClaw].point1.z = RLVal(-0.22);
		#ifdef VisualRepresentation
			Scene = RLFrameGetScene(dummy);
			frame3 = RLCreateFrame(Scene);
			dumwidth = RLDivide(MonsterHotSpots[RoggoshRightClaw].radius,width);;
			RLMeshScale(Ball3, dumwidth, dumwidth, dumwidth);
			MonsterHotSpots[RoggoshRightClaw].BallColor = 
				RLCreateColourRGBA(RLVal(1),RLVal(1),RLVal(0),RLVal(1));
			RLFrameAddVisual(frame3, Ball3);
			MonsterHotSpots[RoggoshRightClaw].BallFrame1 = frame3;
			RLFrameSetColour(MonsterHotSpots[RoggoshRightClaw].BallFrame1,
				MonsterHotSpots[RoggoshRightClaw].BallColor);
			RLFrameSetMaterialMode(MonsterHotSpots[RoggoshRightClaw].BallFrame1,
				RLMaterialFromFrame);
			MonsterHotSpots[RoggoshRightClaw].BallFrame2 = NULL;

			//LGH add release
			RLObjectDestroy (Scene);
			RLObjectDestroy (frame3);
		#endif
			MonsterHotSpots[RoggoshRightClaw].position->lpVtbl->Release (MonsterHotSpots[RoggoshRightClaw].position);
		}
		dummy->lpVtbl->Release (dummy);
	}

	dummy = RLObjectFromName(MonsterLeftHandName);
	if (dummy)
	{
		if (SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, 
			(void **) &(MonsterHotSpots[RoggoshLeftClaw].position))))
		{
			MonsterHotSpots[RoggoshLeftClaw].radius = RLVal(0.22);
			MonsterHotSpots[RoggoshLeftClaw].point1.x = 0;
			MonsterHotSpots[RoggoshLeftClaw].point1.y = 0;
			MonsterHotSpots[RoggoshLeftClaw].point1.z = RLVal(-0.22);
		#ifdef VisualRepresentation
			Scene = RLFrameGetScene(dummy);
			frame4 = RLCreateFrame(Scene);
			dumwidth = RLDivide(MonsterHotSpots[RoggoshLeftClaw].radius,width);;
			RLMeshScale(Ball4, dumwidth, dumwidth, dumwidth);
			MonsterHotSpots[RoggoshLeftClaw].BallColor = 
				RLCreateColourRGBA(RLVal(1),RLVal(1),RLVal(0),RLVal(1));
			RLFrameAddVisual(frame4, Ball4);
			MonsterHotSpots[RoggoshLeftClaw].BallFrame1 = frame4;
			RLFrameSetColour(MonsterHotSpots[RoggoshLeftClaw].BallFrame1,
				MonsterHotSpots[RoggoshLeftClaw].BallColor);
			RLFrameSetMaterialMode(MonsterHotSpots[RoggoshLeftClaw].BallFrame1,
				RLMaterialFromFrame);
			MonsterHotSpots[RoggoshLeftClaw].BallFrame2 = NULL;

			//LGH add release
			RLObjectDestroy (Scene);
			RLObjectDestroy (frame4);
		#endif
			MonsterHotSpots[RoggoshLeftClaw].position->lpVtbl->Release (MonsterHotSpots[RoggoshLeftClaw].position);
		}
		dummy->lpVtbl->Release (dummy);
	}

	dummy=RLObjectFromName(MonsterWeaponName);
	if (dummy)
	{
		if (SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, 
			(void **) &(MonsterTailSpots[RoggoshTail].position))))
		{
			MonsterTailSpots[RoggoshTail].radius = RLVal(0.24);
			MonsterTailSpots[RoggoshTail].point1.x = 0;
			MonsterTailSpots[RoggoshTail].point1.y = 0;
			MonsterTailSpots[RoggoshTail].point1.z = RLVal(-0.15);
			MonsterTailSpots[RoggoshTail].point2.x = 0;
			MonsterTailSpots[RoggoshTail].point2.y = RLVal(0.2);;
			MonsterTailSpots[RoggoshTail].point2.z = RLVal(-0.30);

		#ifdef VisualRepresentation
			Scene = RLFrameGetScene(dummy);
			frame5 = RLCreateFrame(Scene);
			frame6 = RLCreateFrame(Scene);
			dumwidth = RLDivide(MonsterTailSpots[RoggoshTail].radius,width);;
			RLMeshScale(Ball5, dumwidth, dumwidth, dumwidth);
			MonsterTailSpots[RoggoshTail].BallColor = 
				RLCreateColourRGBA(RLVal(1),RLVal(0),RLVal(0),RLVal(1));
			RLFrameAddVisual(frame5, Ball5);
			MonsterTailSpots[RoggoshTail].BallFrame1 = frame5;
	//BSH add !
			RLMeshScale(Ball6, dumwidth, dumwidth, dumwidth);
			MonsterTailSpots[RoggoshTail].BallFrame2 = frame6;
			RLFrameSetColour(MonsterTailSpots[RoggoshTail].BallFrame2,
				MonsterTailSpots[RoggoshTail].BallColor);
			RLFrameSetMaterialMode(MonsterTailSpots[RoggoshTail].BallFrame2,
				RLMaterialFromFrame);
			RLFrameAddVisual(frame6, Ball6);

			//LGH add release
			RLObjectDestroy (Scene);
			RLObjectDestroy (frame5);
			RLObjectDestroy (frame6);
		#endif
			MonsterTailSpots[RoggoshTail].position->lpVtbl->Release (MonsterTailSpots[RoggoshTail].position);
		}
		dummy->lpVtbl->Release (dummy);
	}

#ifdef VisualRepresentation
	//LGH add release
	RLObjectDestroy (Ball2);
	RLObjectDestroy (Ball3);
	RLObjectDestroy (Ball4);
	RLObjectDestroy (Ball5);
	RLObjectDestroy (Ball6);
	RLObjectDestroy (SphereBounds);
#endif
}

void BootAllMonsterFrames()
{
	RLObject dummy;
	RLFrame dummyframe;
	dummy = RLObjectFromName(MonsterChestName);
	if (dummy)
	{
		if (SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, (void **) &(dummyframe))))
		{
			MDFreeD3DFrame(dummyframe);
		}
	}
	dummy = RLObjectFromName(MonsterHeadName);
	if (dummy)
	{
		if (SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, (void **) &(dummyframe))))
		{
			MDFreeD3DFrame(dummyframe);
		}
	}
	dummy = RLObjectFromName(MonsterRightHandName);
	if (dummy)
	{
		if (SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, (void **) &(dummyframe))))
		{
			MDFreeD3DFrame(dummyframe);
		}
	}
	dummy = RLObjectFromName(MonsterLeftHandName);
	if (dummy)
	{
		if (SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, (void **) &(dummyframe))))
		{
			MDFreeD3DFrame(dummyframe);
		}
	}
	dummy=RLObjectFromName(MonsterWeaponName);
	if (dummy)
	{
		if (SUCCEEDED(dummy->lpVtbl->QueryInterface(dummy,&IID_IDirect3DRMFrame, (void **) &(dummyframe))))
		{
			MDFreeD3DFrame(dummyframe);
		}
	}
}

void HandleMonsterHit(MovingObjectData movedata)
{
	RLFrame Scene = RLFrameGetScene(movedata->PositioningFrame);
	int BlockAmount = 0;
	int DamageAmount = 0;
	RLValue GroundHeight;
	extern RLValue MonsterTheta;
	extern RLValue MonsterTurnMaximum;
	extern RLValue MonsterFallDownSpin;
	DamageAmount = RLInt(RLDivide(RLVal(movedata->DamageIveTaken), MonsterArmor));
	movedata->DamageIveTaken = 0;

	if (movedata->collisionflag == 2)
	{//hit a building.
		YBPlay3DSound(MonsterGetHit, monstframe);
		movedata->ProjectedPosition.x = movedata->CollisionVector.x;
		movedata->ProjectedPosition.y = movedata->CollisionVector.y;
		movedata->ProjectedPosition.z = movedata->CollisionVector.z;
	}
	else if(movedata->collisionflag == 47)
	{//hit the Robot
		movedata->CollisionVector.y = 0;
		if (MonsterAnimationState == MonsterBlockMediumFreeze)
		{
			extern RLValue Fear;
			BlockAmount = DamageAmount/3;
			Fear -= BlockAmount;
		}
        else if(MonsterAnimationState == MonsterBlockMediumFirst||
                MonsterAnimationState == MonsterBlockMediumLast)
        {
			extern RLValue Fear;
            BlockAmount = DamageAmount / 10;
			Fear -= BlockAmount;
        }
		MnstLife -= DamageAmount;
		MnstEngy += BlockAmount*655;

		if(BlockAmount)
			YBPlay3DSound(EmPower, monstframe);
		if (MnstLife < 0)
		{ 
			MnstLife = 0;
		}

		//Add by Eric 11/12/96
		if (GameStates.IsNetplay)
		{
			if (MnstLife == 0)
			{
				if (!isHost)
				{
					MonstDeadTimes++;
	
					EventSndBuf.MsgId = NEW_MSG;
					EventSndBuf.Event = EVENT_CHARDEAD;
					EventSndBuf.Param = MonstDeadTimes;
				}
			}
		}
		//end of Eric

	//	if (DamageAmount)
		if(MonsterAnimationState == MonsterKnockDown2)
		{
			MonsterFallDownDirection.x += movedata->CollisionVector.x;
			MonsterFallDownDirection.y += movedata->CollisionVector.y;
			MonsterFallDownDirection.z += movedata->CollisionVector.z;
			MonsterSpeed = (RLVectorModulus(&MonsterFallDownDirection));
			movedata->ProjectedPosition.x += movedata->CollisionVector.x;
			movedata->ProjectedPosition.y += movedata->CollisionVector.y;
			movedata->ProjectedPosition.z += movedata->CollisionVector.z;
		}
		else
		{
			YBPlay3DSound(MonsterGetHit, monstframe);
			MonsterAnimationState = MonsterKnockDown2;
			MonsterTheta = MonsterFallDownSpin*MonsterTurnMaximum;
			MonsterAnimationFrame = RLVal(0);
			MonsterMovementState = MonsterKnockBackward;
			MonsterDistance = 0;
			MonsterNumMovementFrames = 0;

			MonsterFallDownDirection.x = movedata->CollisionVector.x;
			MonsterFallDownDirection.y = movedata->CollisionVector.y;
			MonsterFallDownDirection.z = movedata->CollisionVector.z;
			MonsterSpeed = (RLVectorModulus(&MonsterFallDownDirection));
			movedata->ProjectedPosition.x += movedata->CollisionVector.x;
			movedata->ProjectedPosition.y += movedata->CollisionVector.y;
			movedata->ProjectedPosition.z += movedata->CollisionVector.z;
		}
	}
	else
	{//Monster was hit by something other than a building or the Robot.
		movedata->CollisionVector.y = 0;
		if (MonsterAnimationState == MonsterBlockMediumFreeze)
		{
			extern RLValue Fear;
			BlockAmount = DamageAmount/3;
			Fear -= BlockAmount;
		}
        else if(MonsterAnimationState == MonsterBlockMediumFirst||
                MonsterAnimationState == MonsterBlockMediumLast)
        {
			extern RLValue Fear;
            BlockAmount = DamageAmount / 10;
			Fear -= BlockAmount;
        }
		MnstLife -= DamageAmount;
		MnstEngy += BlockAmount*655;
		if(BlockAmount)
			YBPlay3DSound(EmPower, monstframe);
		if (MnstLife < 0)
		{ 
			MnstLife = 0;
		}

		if ((DamageAmount < MonsterFalldownThreshold) && (MnstLife > DamageAmount))
		{
			if(MonsterAnimationState==MonsterKnockDown2)
			{
				MonsterFallDownDirection.x += movedata->CollisionVector.x;
				MonsterFallDownDirection.y += movedata->CollisionVector.y;
				MonsterFallDownDirection.z += movedata->CollisionVector.z;

				MonsterSpeed = (RLVectorModulus(&MonsterFallDownDirection));

				movedata->ProjectedPosition.x += movedata->CollisionVector.x;
				movedata->ProjectedPosition.y += movedata->CollisionVector.y;
				movedata->ProjectedPosition.z += movedata->CollisionVector.z;
			}
			else
			{
				YBPlay3DSound(MonsterGetHit, monstframe);
				MonsterAnimationFrame = RLVal(0);
				MonsterAnimationState = MonsterChestHitLeft2;
				MonsterMovementState = MonsterStopped;
//				MonsterMovementState = MonsterKnockBackward;
				MonsterDistance = 0;
				MonsterNumMovementFrames = 0;
				MonsterFallDownDirection.x = movedata->CollisionVector.x;
				MonsterFallDownDirection.y = movedata->CollisionVector.y;
				MonsterFallDownDirection.z = movedata->CollisionVector.z;
				MonsterSpeed = (RLVectorModulus(&MonsterFallDownDirection));
				movedata->ProjectedPosition.x += movedata->CollisionVector.x;
				movedata->ProjectedPosition.y += movedata->CollisionVector.y;
				movedata->ProjectedPosition.z += movedata->CollisionVector.z;
			}
		}
		else //Big damage, fall down go boom.
		{

			//Add by Eric 11/12/96
			if (GameStates.IsNetplay)
			{
				if (MnstLife == 0)
				{
					if (!isHost)
					{
						MonstDeadTimes++;
		
						EventSndBuf.MsgId = NEW_MSG;
						EventSndBuf.Event = EVENT_CHARDEAD;
						EventSndBuf.Param = MonstDeadTimes;
					}
				}
			}
			//end of Eric

		//	if (DamageAmount)
			if (BlockAmount)
			{
				YBPlay3DSound(MonsterGetHit, monstframe);
				movedata->ProjectedPosition.x = movedata->CurrentPosition.x;
				movedata->ProjectedPosition.y = movedata->CurrentPosition.y;
				movedata->ProjectedPosition.z = movedata->CurrentPosition.z;
			}
			else
			{
				if(MonsterAnimationState == MonsterKnockDown2)
				{
					MonsterFallDownDirection.x += movedata->CollisionVector.x;
					MonsterFallDownDirection.y += movedata->CollisionVector.y;
					MonsterFallDownDirection.z += movedata->CollisionVector.z;
					MonsterSpeed = (RLVectorModulus(&MonsterFallDownDirection));
					movedata->ProjectedPosition.x += movedata->CollisionVector.x;
					movedata->ProjectedPosition.y += movedata->CollisionVector.y;
					movedata->ProjectedPosition.z += movedata->CollisionVector.z;
				}
				else
				{
					YBPlay3DSound(MonsterGetHit, monstframe);
					MonsterAnimationState = MonsterKnockDown2;
					MonsterTheta = MonsterFallDownSpin*MonsterTurnMaximum;
					MonsterAnimationFrame = RLVal(0);
					MonsterMovementState = MonsterKnockBackward;
					MonsterDistance = 0;
					MonsterNumMovementFrames = 0;

					MonsterFallDownDirection.x = movedata->CollisionVector.x;
					MonsterFallDownDirection.y = movedata->CollisionVector.y;
					MonsterFallDownDirection.z = movedata->CollisionVector.z;
					MonsterSpeed = (RLVectorModulus(&MonsterFallDownDirection));
					movedata->ProjectedPosition.x += movedata->CollisionVector.x;
					movedata->ProjectedPosition.y += movedata->CollisionVector.y;
					movedata->ProjectedPosition.z += movedata->CollisionVector.z;
				}
			}
		}
	}

	movedata->collisionflag = 0;
	movedata->data = -1;
	GroundHeight = 
		SpuddeMapHeight2(movedata->ProjectedPosition.x,movedata->ProjectedPosition.z);
	if(movedata->ProjectedPosition.y < GroundHeight)
	{
		movedata->ProjectedPosition.y = GroundHeight;
	}
	RLFrameSetPosition(movedata->PositioningFrame,Scene,
					  movedata->ProjectedPosition.x,
					  movedata->ProjectedPosition.y,
					  movedata->ProjectedPosition.z);

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
}

void HandleRobotHit(MovingObjectData movedata)
{
	extern RLValue RobotFallDownSpin;
	extern RLValue RobotTurnMaximum;
	extern RLValue RobotTheta;
	RLFrame Scene = RLFrameGetScene(movedata->PositioningFrame);
	RLVector MonPos, RobotPos;
	RLVector RobotFace, RobotUp;
	int BlockAmount = 0;
	int DamageAmount = 0;
	RLValue length;
	RLValue GroundHeight;
	char OutputString[256];

	//DeactivateJets();

	if(movedata->collisionflag == 1)
	{//Didn't hit a building or the monster.
		//LGH add
		DeactivateJets();

		movedata->collisionflag = 0;
		movedata->CollisionVector.y = 0;
		DamageAmount = RLInt(RLDivide(RLVal(movedata->DamageIveTaken), RobotArmor));
		movedata->DamageIveTaken = 0;
			
		if (RobotAnimationState == RobotBlockMediumFreeze)
		{
			extern RLValue RobotBlockSphereHeight;
			extern int shielddlist;
			BlockAmount = DamageAmount;
			FlipTextureCoords(shielddlist, 1);// slap on "getting zapped" texture 
			RLFrameGetPosition(monstframe, Scene, &MonPos);
			RLFrameGetPosition(Robotframe, Scene, &RobotPos);
			RLFrameSetOrientation(RobotBlockSphere, Scene,
								  movedata->CollisionVector.x, 
								  movedata->CollisionVector.y, 
								  movedata->CollisionVector.z, 
								  0, 1, 0); 
			RLFrameSetRotation(RobotBlockSphere, RobotBlockSphere,
							   0, 0, 1, RLVal(0.50));
			RLFrameSetPosition(RobotBlockSphere, Robotframe,
							   0, RobotBlockSphereHeight, 0);
			BlockCountDown = 10;
		}
		else if(RobotAnimationState == RobotBlockMediumFirst||
				RobotAnimationState == RobotBlockMediumLast)
		{
			BlockAmount = DamageAmount/3;
		}
		if(BlockAmount > (RobotEngy/655))
		{
			BlockAmount = RobotEngy/655;
		}

		
		
		DamageAmount -= BlockAmount;
		RobotLife -= DamageAmount;
		RobotEngy -= BlockAmount * 655;

		if (RobotLife <= 0) 
		{
			YBPlay3DSound(RobotGetHit, Robotframe);
			RobotMovementState = RobotKnockDown;
			RobotDistance = 0;
			RobotNumMovementFrames = 0;
			RobotFallDownDirection.x = movedata->CollisionVector.x;
			RobotFallDownDirection.y = movedata->CollisionVector.y;
			RobotFallDownDirection.z = movedata->CollisionVector.z;
			RobotSpeed = (RLVectorModulus(&RobotFallDownDirection));
			movedata->ProjectedPosition.x += movedata->CollisionVector.x;
			movedata->ProjectedPosition.y += movedata->CollisionVector.y;
			movedata->ProjectedPosition.z += movedata->CollisionVector.z;
			if (RLVectorDotProduct(&RobotFace, &RobotFallDownDirection) < 0)
			{
				RobotAnimationState = RobotAcrobatic1;
			}
			else
			{
				RobotAnimationState = RobotAcrobatic2;
			}
			RobotTheta = RobotFallDownSpin*RobotTurnMaximum;
			RobotLife=0;
			GameStates.RobotLose=TRUE;
			if(GameStates.IsNetplay)
			{
				GameStates.IsRobotDead[GameStates.CurrentRobot]++;
			}
			else if(!(GameStates.IsTraining||GameStates.IsAutodemo))
			{
				GameStates.IsRobotDead[GameStates.CurrentRobot]=1;
			}
			//RobotData.RemoveMeFlag=1;
			//Add by Eric 11/12/96
			if (GameStates.IsNetplay)
			{
				if (isHost)
				{
					RobotDeadTimes++;

					EventSndBuf.MsgId = NEW_MSG;
					EventSndBuf.Event = EVENT_CHARDEAD;
					EventSndBuf.Param = RobotDeadTimes;
				}
			}
			//end of Eric

		
		}
		else if (DamageAmount)
		{//Some damage managed to get through the Robot's armor and shielding.
			if (
				RobotAnimationState == RobotBlockMediumFreeze ||
				RobotAnimationState == RobotBlockMediumFirst  ||
				RobotAnimationState == RobotBlockMediumLast
				)
			{//There was damage, but it was blocked partially.
				YBPlay3DSound(RobotGetHit, Robotframe);
				movedata->ProjectedPosition.x = 
					movedata->CurrentPosition.x + movedata->CollisionVector.x;
				movedata->ProjectedPosition.y = 
					movedata->CurrentPosition.y + movedata->CollisionVector.y;
				movedata->ProjectedPosition.z = 
					movedata->CurrentPosition.z + movedata->CollisionVector.z;

			}
			else
			{//There was damage, and no blocking
				if(RobotMovementState == RobotKnockDown || 
					RobotMovementState == RobotKnockDownOnBuilding)
				{//there was damage and no blocking, and the Robot's already falling.
					RobotFallDownDirection.x += movedata->CollisionVector.x;
					RobotFallDownDirection.y += movedata->CollisionVector.y;
					RobotFallDownDirection.z += movedata->CollisionVector.z;
					RobotSpeed = (RLVectorModulus(&RobotFallDownDirection));
					movedata->ProjectedPosition.x += movedata->CollisionVector.x;
					movedata->ProjectedPosition.y += movedata->CollisionVector.y;
					movedata->ProjectedPosition.z += movedata->CollisionVector.z;
				}
				else
				{//There was damage and no blocking, and the Robot's not falling down.
					YBPlay3DSound(RobotGetHit, Robotframe);
					RLFrameAddChild(behindthescene, RobotBlockSphere);
					RLFrameGetOrientation(Robotframe, Scene, &RobotFace, &RobotUp);

					RobotAnimationFrame = RLVal(0);
					if (RobotAnimationState != RobotPause1)
					{//if the Robot was blocking, we're not in this state.
						if(RobotMovementState<RobotWaitingOnBuilding)
						{
							RobotMovementState = RobotKnockDown;
						}
						else
						{
							RobotMovementState = RobotKnockDownOnBuilding;
						}
						RobotData.OffensiveTubeList[0]=NULL;
						RobotData.OffensiveTubeList[1]=NULL;
						RobotData.DamageICause=0;
						RobotData.NumOffensiveTubes=0;
					}
					RobotDistance = 0;
					RobotNumMovementFrames = 0;
					RobotFallDownDirection.x = movedata->CollisionVector.x;
					RobotFallDownDirection.y = movedata->CollisionVector.y;
					RobotFallDownDirection.z = movedata->CollisionVector.z;
					RobotSpeed = (RLVectorModulus(&RobotFallDownDirection));
					movedata->ProjectedPosition.x += movedata->CollisionVector.x;
					movedata->ProjectedPosition.y += movedata->CollisionVector.y;
					movedata->ProjectedPosition.z += movedata->CollisionVector.z;
					if (RobotAnimationState != RobotPause1)
					{
						if(RLVectorDotProduct(&RobotFace, &RobotFallDownDirection) < 0)
						{
							RobotAnimationState = RobotAcrobatic1;
						}
						else
						{
							RobotAnimationState = RobotAcrobatic2;
						}
						RobotTheta = RobotFallDownSpin*RobotTurnMaximum;
					}
				}
			}
		}
		else//We've been hit, but not damaged.
		{
			//OutputDebugString("I think we've got a winner.  Should be moving back.\n");
			//sprintf(OutputString,"Collision = %.3f, %.3f, %.3f\n",movedata->CollisionVector.x,movedata->CollisionVector.y,movedata->CollisionVector.z);
			//OutputDebugString(OutputString);
			YBPlay3DSound(RobotGetHit, Robotframe);
			if(RobotMovementState == RobotKnockDown || 
				RobotMovementState == RobotKnockDownOnBuilding)
			{//there was damage and no blocking, and the Robot's already falling.
				RobotFallDownDirection.x += movedata->CollisionVector.x;
				RobotFallDownDirection.y += movedata->CollisionVector.y;
				RobotFallDownDirection.z += movedata->CollisionVector.z;
				RobotSpeed = (RLVectorModulus(&RobotFallDownDirection));
				movedata->ProjectedPosition.x += movedata->CollisionVector.x;
				movedata->ProjectedPosition.y += movedata->CollisionVector.y;
				movedata->ProjectedPosition.z += movedata->CollisionVector.z;
			}
			else
			{
				movedata->ProjectedPosition.x = 
					movedata->CurrentPosition.x + movedata->CollisionVector.x;
				movedata->ProjectedPosition.y = 
					movedata->CurrentPosition.y + movedata->CollisionVector.y;
				movedata->ProjectedPosition.z = 
					movedata->CurrentPosition.z + movedata->CollisionVector.z;
				
				movedata->CurrentPosition.x = movedata->ProjectedPosition.x;
				movedata->CurrentPosition.y = movedata->ProjectedPosition.y;
				movedata->CurrentPosition.z = movedata->ProjectedPosition.z;
				
				RobotPosition.x = movedata->ProjectedPosition.x;
				RobotPosition.y = movedata->ProjectedPosition.y;
				RobotPosition.z = movedata->ProjectedPosition.z;
				if(RobotMovementState<RobotWaitingOnBuilding)
				{
					RobotMovementState=RobotWaiting;
				}
				else
				{
					RobotAnimationState=RobotWaitingOnBuilding;
				}
				RobotAnimationState=RobotPause1;
				RobotAnimationFrame=RLVal(0.0);
			}

		}
	}
	else if(movedata->collisionflag == 47)
	{//hit the monster.
		DeactivateJets();
		movedata->collisionflag = 0;
		if (RobotAnimationState == RobotBlockMediumFreeze)
		{
			extern RLValue RobotBlockSphereHeight;
			extern int shielddlist;
			BlockAmount = DamageAmount;
			FlipTextureCoords(shielddlist, 1);// slap on "getting zapped" texture 
			RLFrameGetPosition(monstframe, Scene, &MonPos);
			RLFrameGetPosition(Robotframe, Scene, &RobotPos);
			RLFrameSetOrientation(RobotBlockSphere, Scene,
								  movedata->CollisionVector.x, 
								  movedata->CollisionVector.y, 
								  movedata->CollisionVector.z, 
								  0, 1, 0); 
			RLFrameSetRotation(RobotBlockSphere, RobotBlockSphere,
							   0, 0, 1, RLVal(0.50));
			RLFrameSetPosition(RobotBlockSphere, Robotframe,
							   0, RobotBlockSphereHeight, 0);
			BlockCountDown = 10;
		}
		else if(RobotAnimationState == RobotBlockMediumFirst||
				RobotAnimationState == RobotBlockMediumLast)
		{
			BlockAmount = DamageAmount/3;
		}
		if(BlockAmount > (RobotEngy/655))
		{
			BlockAmount = RobotEngy/655;
		}

	
	
		DamageAmount -= BlockAmount;
		RobotLife -= DamageAmount;
		RobotEngy -= BlockAmount * 655;

		if (RobotLife <= 0) 
		{
			YBPlay3DSound(RobotGetHit, Robotframe);
			RobotMovementState = RobotKnockDown;
			RobotDistance = 0;
			RobotNumMovementFrames = 0;
			RobotFallDownDirection.x = movedata->CollisionVector.x;
			RobotFallDownDirection.y = movedata->CollisionVector.y;
			RobotFallDownDirection.z = movedata->CollisionVector.z;
			RobotSpeed = (RLVectorModulus(&RobotFallDownDirection));
			movedata->ProjectedPosition.x += movedata->CollisionVector.x;
			movedata->ProjectedPosition.y += movedata->CollisionVector.y;
			movedata->ProjectedPosition.z += movedata->CollisionVector.z;
			if (RLVectorDotProduct(&RobotFace, &RobotFallDownDirection) < 0)
			{
				RobotAnimationState = RobotAcrobatic1;
			}
			else
			{
				RobotAnimationState = RobotAcrobatic2;
			}
			RobotTheta = RobotFallDownSpin*RobotTurnMaximum;
			RobotLife=0;
			GameStates.RobotLose=TRUE;
			if(GameStates.IsNetplay)
			{
				GameStates.IsRobotDead[GameStates.CurrentRobot]++;
			}
			else if(!(GameStates.IsTraining||GameStates.IsAutodemo))
			{
				GameStates.IsRobotDead[GameStates.CurrentRobot]=1;
			}
			//RobotData.RemoveMeFlag=1;
			//Add by Eric 11/12/96
			if (GameStates.IsNetplay)
			{
				if (isHost)
				{
					RobotDeadTimes++;

					EventSndBuf.MsgId = NEW_MSG;
					EventSndBuf.Event = EVENT_CHARDEAD;
					EventSndBuf.Param = RobotDeadTimes;
				}
			}
			//end of Eric

		
		}
		else
		{//Robot's still alive
			if(RobotMovementState == RobotKnockDown || 
				RobotMovementState == RobotKnockDownOnBuilding)
			{//the Robot's already falling.
				RobotFallDownDirection.x += movedata->CollisionVector.x;
				RobotFallDownDirection.y += movedata->CollisionVector.y;
				RobotFallDownDirection.z += movedata->CollisionVector.z;
				RobotSpeed = (RLVectorModulus(&RobotFallDownDirection));
				movedata->ProjectedPosition.x += movedata->CollisionVector.x;
				movedata->ProjectedPosition.y += movedata->CollisionVector.y;
				movedata->ProjectedPosition.z += movedata->CollisionVector.z;
			}
			else
			{//the Robot's not falling down yet
				YBPlay3DSound(RobotGetHit, Robotframe);
				RLFrameAddChild(behindthescene, RobotBlockSphere);
				RLFrameGetOrientation(Robotframe, Scene, &RobotFace, &RobotUp);

				RobotAnimationFrame = RLVal(0);
				if(RobotMovementState<RobotWaitingOnBuilding)
				{
					RobotMovementState = RobotKnockDown;
				}
				else
				{
					RobotMovementState = RobotKnockDownOnBuilding;
				}
				RobotData.OffensiveTubeList[0]=NULL;
				RobotData.OffensiveTubeList[1]=NULL;
				RobotData.DamageICause=0;
				RobotData.NumOffensiveTubes=0;
				RobotDistance = 0;
				RobotNumMovementFrames = 0;
				RobotFallDownDirection.x = movedata->CollisionVector.x;
				RobotFallDownDirection.y = movedata->CollisionVector.y;
				RobotFallDownDirection.z = movedata->CollisionVector.z;
				RobotSpeed = (RLVectorModulus(&RobotFallDownDirection));
				movedata->ProjectedPosition.x += movedata->CollisionVector.x;
				movedata->ProjectedPosition.y += movedata->CollisionVector.y;
				movedata->ProjectedPosition.z += movedata->CollisionVector.z;
				if(RLVectorDotProduct(&RobotFace, &RobotFallDownDirection) < 0)
				{
					RobotAnimationState = RobotAcrobatic1;
				}
				else
				{
					RobotAnimationState = RobotAcrobatic2;
				}
				RobotTheta = RobotFallDownSpin*RobotTurnMaximum;
			}
		}

	}
	else
	{//hit a building, so go into code specific to buildings.
		movedata->collisionflag = 0;
		if (movedata->data == LandOnBuilding)
		{
			extern int RobotMidair;
			YBPlay3DSound(RobotFootStep, Robotframe);
			DeactivateJets();
			RobotMidair = 0;
			movedata->ProjectedPosition.x = movedata->CollisionVector.x;
			movedata->ProjectedPosition.y = movedata->CollisionVector.y;
			movedata->ProjectedPosition.z = movedata->CollisionVector.z;
			RobotAnimationState = RobotJumpStop;
			RobotMovementState = RobotStoppedOnBuilding;
			RobotOnBuilding = 1;
			movedata->data=-1;
		}
		else
		{
			YBPlay3DSound(RobotGetHit, Robotframe);
			RobotFallDownDirection.x = 
			movedata->CurrentPosition.x - movedata->ProjectedPosition.x;
			RobotFallDownDirection.y = 
			movedata->CurrentPosition.y - movedata->ProjectedPosition.y;
			RobotFallDownDirection.z = 
			movedata->CurrentPosition.z - movedata->ProjectedPosition.z;
			RLFrameGetOrientation(Robotframe, Scene, &RobotFace, &RobotUp);
			if (movedata->data == FallForwardOnBuilding)
			{
				DeactivateJets();
				movedata->ProjectedPosition.x = movedata->CollisionVector.x;
				movedata->ProjectedPosition.y = movedata->CollisionVector.y;
				movedata->ProjectedPosition.z = movedata->CollisionVector.z;
				RobotFallDownDirection.x = -RobotFallDownDirection.x;
				RobotFallDownDirection.y = -RobotFallDownDirection.y;
				RobotFallDownDirection.z = -RobotFallDownDirection.z;
				if(RLVectorDotProduct(&RobotFace,&RobotFallDownDirection) < 0)
				{
					RobotAnimationState = RobotAcrobatic2;
				}
				else
				{
					RobotAnimationState=RobotAcrobatic1;
				}
				RobotMovementState = RobotKnockDownOnBuilding;
				RobotOnBuilding = 1;
				movedata->data = -1;
			}
			else// movedata->data==SlideDownSideOfBuilding
			{
				RLVector testforbuildingbump;

				RobotData.OffensiveTubeList[0]=NULL;
				RobotData.OffensiveTubeList[1]=NULL;
				RobotData.DamageICause=0;
				RobotData.NumOffensiveTubes=0;
				RLVectorSubtract(&testforbuildingbump, 
								 &movedata->ProjectedPosition, 
								 &movedata->CollisionVector);
				movedata->ProjectedPosition.x = movedata->CollisionVector.x;
				movedata->ProjectedPosition.y = movedata->CollisionVector.y;
				movedata->ProjectedPosition.z = movedata->CollisionVector.z;
				if (RLVectorModulus(&testforbuildingbump) >= 
					RLMultiply(RobotMaxFVel3, DiffFrame)      ) 
				{
					//LGH add
					DeactivateJets();

					if (RLVectorDotProduct(&RobotFace,&RobotFallDownDirection) < 0)
					{
						RobotSlideNextAnimation = RobotAcrobatic1;
					}
					else
					{
						RobotSlideNextAnimation = RobotAcrobatic2;
					}
					RobotMovementState = RobotSlideDownBuildingSide;
					RobotAnimationState = RobotJumpFreeze;
					RobotAnimationFrame = RLVal(10);
					RobotVelocity.x = 0;
					RobotVelocity.z = 0;
					if (RobotVelocity.y > 0)
					{
						RobotYSpeed=0;
					}
					RobotVelocity.y = -1;
					RobotSpeed = 0;
				}
				movedata->data = -1;
			} 
		}
	}

	movedata->data = -1;
	GroundHeight = 
	SpuddeMapHeight2(movedata->ProjectedPosition.x,movedata->ProjectedPosition.z);
	if (movedata->ProjectedPosition.y < GroundHeight)
	{
		movedata->ProjectedPosition.y=GroundHeight;
	}
	RLFrameSetPosition(movedata->PositioningFrame,Scene,
	movedata->ProjectedPosition.x,
	movedata->ProjectedPosition.y,
	movedata->ProjectedPosition.z);

	RLFrameGetPosition(Robotframe,Scene,&RobotPos);
	//sprintf(OutputString,"Real Position = %.3f, %.3f, %.3f\n\n\n",RobotPos.x,RobotPos.y,RobotPos.z);
	//OutputDebugString(OutputString);

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
}

#ifdef Expressive
extern char buffer[];
char buffer1[128] = "";
char buffer2[128] = "";
char buffer3[128] = "";
#endif


void HomingMotionFunction(MovingObjectData movedata)
{
//modify by helen 11/16/96
	RLValue HomerCosine=cos(HomerAngle * DiffFrame);

	RLValue HomerSine=sin(HomerAngle * DiffFrame);
//end Helen
	RLVector Position1;
	RLVector Direction;
	RLValue Distance, Height;
	RLValue DesiredHeight;
	RLValue MonsterChestHeight;
	RLValue Sine;
	RLFrame Scene = RLFrameGetScene(movedata->PositioningFrame);
	RLFrameGetPosition(MonsterHotSpots[RoggoshBody].position,Scene, &Position1);
	MonsterChestHeight = Position1.y;
	movedata->CurrentPosition.x = movedata->ProjectedPosition.x;
	movedata->CurrentPosition.y = movedata->ProjectedPosition.y;
	movedata->CurrentPosition.z = movedata->ProjectedPosition.z;

	RLFrameGetPosition(monstframe, Scene, &Position1);

	Position1.x -= movedata->CurrentPosition.x;
	Position1.y -= movedata->CurrentPosition.y;
	Position1.z -= movedata->CurrentPosition.z;
	Sine = RLMultiply(Robotspewvelocity.x, Position1.z) - 
		RLMultiply(Position1.x, Robotspewvelocity.z);
	if (Sine > RLVal(HomerCloseEnough))
	{
		Robotspewvelocity.x = RLMultiply(HomerCosine, Robotspewvelocity.x) - 
			RLMultiply(HomerSine, Robotspewvelocity.z);
		Robotspewvelocity.z = RLMultiply(HomerCosine, Robotspewvelocity.z) + 
			RLMultiply(HomerSine, Robotspewvelocity.x);
	}
	else if(Sine < RLVal(-HomerCloseEnough))
	{
		Robotspewvelocity.x = RLMultiply(HomerCosine, Robotspewvelocity.x) + 
			RLMultiply(HomerSine, Robotspewvelocity.z);
		Robotspewvelocity.z = RLMultiply(HomerCosine, Robotspewvelocity.z) - 
			RLMultiply(HomerSine, Robotspewvelocity.x);
	}

	movedata->ProjectedPosition.x = 
		movedata->CurrentPosition.x + Robotspewvelocity.x * DiffFrame;
	movedata->ProjectedPosition.z = 
		movedata->CurrentPosition.z + Robotspewvelocity.z * DiffFrame;

	Height = 
		SpuddeMapHeight2(movedata->ProjectedPosition.x, movedata->ProjectedPosition.z);

	DesiredHeight = ( (CruisingLowerAltitude + Height > MonsterChestHeight)
					 ? CruisingLowerAltitude + Height : MonsterChestHeight);


	if (movedata->CurrentPosition.y > DesiredHeight + CruisingUpperAltitude)
	{
		Robotspewvelocity.y = -CruisingYVelocity*DiffFrame;
			
	}
	else if (movedata->CurrentPosition.y < DesiredHeight)
	{
		Robotspewvelocity.y = CruisingYVelocity*DiffFrame;
	}
	else
	{
		Robotspewvelocity.y = 0;
	}

	movedata->ProjectedPosition.y = movedata->CurrentPosition.y + Robotspewvelocity.y;

	if (HomerHowLong <= 0)
	{
		HomerOnScreen = 0;
		RLFrameAddChild(behindthescene, Robotspew);
		movedata->RemoveMeFlag = 1;
		HomerOnScreen = 0;
	}
	HomerHowLong-=DiffFrame;

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
}

void PlasmaGotHit(MovingObjectData movedata)
{
	RLFrame Scene = RLFrameGetScene(movedata->PositioningFrame);

	movedata->RemoveMeFlag = 1;
	RLFrameAddChild(behindthescene, Robotspew);
	RLFrameAddChild(Scene, Mexplode); 
	RLFrameSetPosition(Mexplode, Scene, 
		               movedata->ProjectedPosition.x,
					   movedata->ProjectedPosition.y,
					   movedata->ProjectedPosition.z);
	RLFrameSetOrientation(Mexplode, Scene, 0, 1, 0, 0, 0, 1);
	RLFrameSetVelocity(Mexplode, Scene,
		               movedata->CollisionVector.x, 
					   movedata->CollisionVector.y, 
					   movedata->CollisionVector.z);
	MXdata.OnScreen = 1;
	HomerOnScreen = 0;
	MXdata.HowLong = 10;
	ActivateParticleSystem(Robotexplosion, 16);
	ResetParticles(Robotexplosion);

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
}

void RapidFireMotionFunction(MovingObjectData movedata)
{
	RLFrame Scene = RLFrameGetScene(movedata->PositioningFrame);
	int i = movedata->data;
	RLVector dir,up;
	extern RLFrame Wcamera;

	movedata->CurrentPosition.x = movedata->ProjectedPosition.x;
	movedata->CurrentPosition.y = movedata->ProjectedPosition.y;
	movedata->CurrentPosition.z = movedata->ProjectedPosition.z;

	RLFrameSetOrientation(movedata->PositioningFrame,Wcamera, 
		                  RLVal(0), RLVal(0), RLVal(1), 
						  RLVal(0), RLVal(1), RLVal(0));

	movedata->ProjectedPosition.x = movedata->CurrentPosition.x + 
		SixShooterDirection[i].x * DiffFrame * RFSpeed;
	movedata->ProjectedPosition.y = movedata->CurrentPosition.y + 
		SixShooterDirection[i].y * DiffFrame * RFSpeed;
	movedata->ProjectedPosition.z = movedata->CurrentPosition.z + 
		SixShooterDirection[i].z * DiffFrame * RFSpeed;

	if (movedata->ProjectedPosition.y <
		 SpuddeMapHeight2(movedata->ProjectedPosition.x,
						  movedata->ProjectedPosition.z))
	{
		movedata->collisionflag = 1;
	}

	if (RapidFireHowLong[i] <= 0)
	{
		SixShooter->particles[i]->active = 0;
		movedata->RemoveMeFlag = 1;
	}
	RapidFireHowLong[i]-=DiffFrame;

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
}

void RapidFireGotHit(MovingObjectData movedata)
{
	RLFrame Scene = RLFrameGetScene(movedata->PositioningFrame);
	int i = movedata->data;

	movedata->RemoveMeFlag = 1;
	SixShooter->particles[i]->active = 0;
	RLFrameAddChild(Scene, Mexplode); 
	RLFrameSetPosition(Mexplode, Scene, 
		               movedata->ProjectedPosition.x,
					   movedata->ProjectedPosition.y,
					   movedata->ProjectedPosition.z);
	RLFrameSetOrientation(Mexplode, Scene, 0, 1, 0, 0, 0, 1);
	RLFrameSetVelocity(Mexplode, Scene, 
		               movedata->CollisionVector.x, 
					   movedata->CollisionVector.y, 
					   movedata->CollisionVector.z);
	MXdata.OnScreen = 1;
	MXdata.HowLong = 3;
	ActivateParticleSystem(Robotexplosion, 8);
	ResetParticles(Robotexplosion);

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
}


void CussinMotionFunction(MovingObjectData movedata)
{
	RLFrame Scene = RLFrameGetScene(movedata->PositioningFrame);
	int i = movedata->data;
	RLVector dir, up, pos;
	extern RLValue RobotConcussionMaxRadius;
	extern RLValue RobotConcussionMinRadius;
	extern RLValue RobotConcussionDuration;
	extern RLValue RobotConcussionSpeed;
	RLValue PercentDone = (RobotConcussionDuration-CussinHowLong[i])/RobotConcussionDuration;

	RLValue CussinScale = RLVal((RobotConcussionMaxRadius-RobotConcussionMinRadius)*PercentDone)+RobotConcussionMinRadius;
	RLFrameGetOrientation(movedata->PositioningFrame, Scene, &dir, &up);
	RLFrameGetPosition(movedata->PositioningFrame, Scene, &pos);
	RLVectorNormalise(&dir);
	RLVectorNormalise(&up);
	movedata->OffensiveSphereList[0]->radius = CussinScale/3;
	movedata->mass = RLDivide(RobotCussinMass, CussinScale);
	RLFrameSetOrientation(movedata->PositioningFrame, Scene,
	                      CussinWhichWay.x,CussinWhichWay.y,CussinWhichWay.z,
	                      CussinUp.x,CussinUp.y,CussinUp.z);
	RLFrameAddScale(movedata->PositioningFrame, RLCombineAfter, 
		CussinScale,CussinScale,CussinScale);
	RLFrameSetPosition(movedata->PositioningFrame, Scene, pos.x, pos.y, pos.z);

	movedata->CurrentPosition.x = movedata->ProjectedPosition.x;
	movedata->CurrentPosition.y = movedata->ProjectedPosition.y;
	movedata->CurrentPosition.z = movedata->ProjectedPosition.z;

	movedata->ProjectedPosition.x = movedata->CurrentPosition.x + 
		dir.x*DiffFrame*RobotConcussionSpeed;
	movedata->ProjectedPosition.y = movedata->CurrentPosition.y + 
		dir.y*DiffFrame*RobotConcussionSpeed;
	movedata->ProjectedPosition.z = movedata->CurrentPosition.z + 
		dir.z*DiffFrame*RobotConcussionSpeed;
	if (movedata->ProjectedPosition.y <
		 SpuddeMapHeight2(movedata->ProjectedPosition.x,
						  movedata->ProjectedPosition.z))
	{
		movedata->collisionflag = 1;
	}

	if (CussinHowLong[i] <= 0)
	{
		Cussin->particles[i]->active = 0;
		movedata->RemoveMeFlag = 1;
	}
	CussinHowLong[i] -= DiffFrame;

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
}

void CussinGotHit(MovingObjectData movedata)
{
	RLFrame Scene = RLFrameGetScene(movedata->PositioningFrame);
	int i = movedata->data;

	if (CussinHowLong[i] <= 0) 
	{
		movedata->RemoveMeFlag = 1;
		Cussin->particles[i]->active = 0;
		RLFrameAddChild(Scene, Mexplode); 
		RLFrameSetPosition(Mexplode, Scene, 
			               movedata->ProjectedPosition.x,
						   movedata->ProjectedPosition.y,
						   movedata->ProjectedPosition.z);
		RLFrameSetOrientation(Mexplode, Scene,0, 1, 0, 0, 0, 1);
		RLFrameSetVelocity(Mexplode, Scene, 
			               movedata->CollisionVector.x, 
						   movedata->CollisionVector.y, 
						   movedata->CollisionVector.z);
		MXdata.OnScreen = 1;
		MXdata.HowLong = 3;
	}
	ActivateParticleSystem(Robotexplosion, 16);
	ResetParticles(Robotexplosion);

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
}

void SnowballMotionFunction(MovingObjectData movedata)
{
	RLFrame Scene = RLFrameGetScene(movedata->PositioningFrame);
	RLVector pos, dir, up;
	RLVector AdjustedVelocity;
	RLValue SnowballScale = KothosSnowballInitRadius + 
						RLMultiply(BombHowLong,KothosSnowballGrowthRate);
	AdjustedVelocity.x = RLMultiply(KothosSnowballVelocity.x, DiffFrame);
	AdjustedVelocity.y = RLMultiply(KothosSnowballVelocity.y, DiffFrame);
	AdjustedVelocity.z = RLMultiply(KothosSnowballVelocity.z, DiffFrame);
	movedata->CurrentPosition.x = movedata->ProjectedPosition.x;
	movedata->CurrentPosition.y = movedata->ProjectedPosition.y;
	movedata->CurrentPosition.z = movedata->ProjectedPosition.z;
	SpuddeMoveOnGround(movedata, &AdjustedVelocity, &KSnowballGradientFactor);
	movedata->ProjectedPosition.y += SnowballScale;
	KothosSnowballVelocity.x = 
		RLDivide(movedata->ProjectedPosition.x-movedata->CurrentPosition.x,DiffFrame);
	KothosSnowballVelocity.z = 
		RLDivide(movedata->ProjectedPosition.z-movedata->CurrentPosition.z,DiffFrame);
	RLFrameGetPosition(movedata->PositioningFrame, Scene, &pos);
	movedata->OffensiveSphereList[0]->radius = SnowballScale;
	RLFrameAddScale(movedata->PositioningFrame, RLCombineReplace, 
		SnowballScale,SnowballScale,SnowballScale);
	RLFrameSetPosition(movedata->PositioningFrame, Scene, pos.x, pos.y, pos.z);

	BombHowLong += DiffFrame;
	if (BombHowLong >= KothosSnowballDuration)
	{
		movedata->collisionflag = 1;
	}

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
}



void BombMotionFunction(MovingObjectData movedata)
{
	RLFrame Scene = RLFrameGetScene(movedata->PositioningFrame);
	RLVector pos;
//	static int flipflop = 0;
//	extern int nukedlist;
	RLFrameGetPosition(movedata->PositioningFrame, Scene, &pos);
	movedata->OffensiveSphereList[0]->radius = GaingrisNukeInitRadius + 
		                             RLMultiply(BombHowLong,GaingrisNukeVelocity);
	if (movedata->OffensiveSphereList[0]->radius > GaingrisNukeMaxRadius) 
	{
		movedata->RemoveMeFlag	= 1;
	}
	RLFrameAddScale(movedata->PositioningFrame,RLCombineReplace,
				   movedata->OffensiveSphereList[0]->radius/1.317,
				   movedata->OffensiveSphereList[0]->radius/2.317,
				   movedata->OffensiveSphereList[0]->radius/1.317);
	RLFrameSetPosition(movedata->PositioningFrame, Scene, pos.x, pos.y, pos.z);
	BombData.Volume.max.x = 
		RLDivide(movedata->OffensiveSphereList[0]->radius,RLVal(1.414));
	BombData.Volume.max.y = 
		RLDivide(movedata->OffensiveSphereList[0]->radius,RLVal(1.414));
	BombData.Volume.max.z = 
		RLDivide(movedata->OffensiveSphereList[0]->radius,RLVal(1.414));
	BombData.Volume.min.x = 
		-RLDivide(movedata->OffensiveSphereList[0]->radius,RLVal(1.414));
	BombData.Volume.min.y = 
		-RLDivide(movedata->OffensiveSphereList[0]->radius,RLVal(1.414));
	BombData.Volume.min.z = 
		-RLDivide(movedata->OffensiveSphereList[0]->radius,RLVal(1.414));
   
	movedata->CurrentPosition.x = movedata->ProjectedPosition.x;
	movedata->CurrentPosition.y = movedata->ProjectedPosition.y;
	movedata->CurrentPosition.z = movedata->ProjectedPosition.z;
	BombHowLong += DiffFrame;
//	flipflop = (flipflop+1)&1;

	// slap on "getting zapped" texture 
//	FlipTextureCoords(nukedlist, flipflop);

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
}

void BombGotHit(MovingObjectData movedata)
{
	RLFrame Scene = RLFrameGetScene(movedata->PositioningFrame);
	RLFrameSetPosition(movedata->PositioningFrame, Scene, 
		               movedata->ProjectedPosition.x,
					   movedata->ProjectedPosition.y,
					   movedata->ProjectedPosition.z);
	movedata->collisionflag = 0;

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
}

void SnowballGotHit(MovingObjectData movedata)
{
	RLFrameAddChild(behindthescene, BombSphere);
	BombData.RemoveMeFlag = 1;
	BombData.collisionflag = 0;
}


void NRingsMotionFunction(MovingObjectData movedata)
{
	RLFrame Scene = RLFrameGetScene(movedata->PositioningFrame);
	int i = movedata->data;
	RLVector dir,up;
	RLFrameGetOrientation(movedata->PositioningFrame, Scene, &dir, &up);

	movedata->CurrentPosition.x = movedata->ProjectedPosition.x;
	movedata->CurrentPosition.y = movedata->ProjectedPosition.y;
	movedata->CurrentPosition.z = movedata->ProjectedPosition.z;

	movedata->ProjectedPosition.x = movedata->CurrentPosition.x + 
		                            dir.x * DiffFrame * NeallothRingsSpeed;
	movedata->ProjectedPosition.y = movedata->CurrentPosition.y + 
		                            dir.y * DiffFrame * NeallothRingsSpeed;
	movedata->ProjectedPosition.z = movedata->CurrentPosition.z + 
		                            dir.z * DiffFrame * NeallothRingsSpeed;
	if (movedata->ProjectedPosition.y <
		 SpuddeMapHeight2(movedata->ProjectedPosition.x,
						  movedata->ProjectedPosition.z)
	   )
	{
		movedata->collisionflag = 1;
	}
	if (NRingsHowLong[i] <= 0)
	{
		NeallothRings->particles[i]->active = 0;
		movedata->RemoveMeFlag = 1;
	}
	NRingsHowLong[i] -= DiffFrame;

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
}

void NRingsGotHit(MovingObjectData movedata)
{
	RLFrame Scene = RLFrameGetScene(movedata->PositioningFrame);
	int i = movedata->data;

	movedata->RemoveMeFlag = 1;
	NeallothRings->particles[i]->active = 0;

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
}


extern RLVector MonsterPlasmaDisplacement;
void ZappaMotionFunction(MovingObjectData movedata)
{
	RLFrame Scene = RLFrameGetScene(movedata->PositioningFrame);
	RLFrame Parent = RLFrameGetParent(movedata->PositioningFrame);

	RLFrameSetPosition(movedata->PositioningFrame,Parent,
		               MonsterPlasmaDisplacement.x,
					   MonsterPlasmaDisplacement.y,
					   MonsterPlasmaDisplacement.z);

	//maybe I should do a special building intersection check here.
	movedata->CurrentPosition.x = movedata->ProjectedPosition.x;
	movedata->CurrentPosition.y = movedata->ProjectedPosition.y;
	movedata->CurrentPosition.z = movedata->ProjectedPosition.z;
	RLFrameGetPosition(movedata->PositioningFrame, Scene, 
		               &movedata->ProjectedPosition);
	
	if(ZappaHowLong <= 0)
	{
		ZappaOnScreen = 0;
		RLFrameAddChild(behindthescene, monstspew);
		movedata->RemoveMeFlag = 1;
	}
	ZappaHowLong -= DiffFrame;

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
	RLObjectDestroy ((RLObject)Parent);
}

void LaunchVisorBeam()
{
	RLFrame WhereIsIt = RobotHotSpots[RobotHead].position;
	RLValue RobotZapRotation = RLVal(1.57);
	RLFrame Scene = RLFrameGetScene(WhereIsIt);
	int i, j;
//RLVector dummy;
	extern int Vmode;
	if(RobotEngy<PeaShooterEnergyMinimum && RobotAnimationState!=RobotPickUpObjectFreeze)
		return;

	i = 6;

	for (j = 0; j < 6; j++) 
	{
		if (RobotZappaHowLong[j] > RLVal(PeaShooterDuration-PeaShooterInterval)) 
		{
			return;
		}
		if (RobotZappaData[j].RemoveMeFlag) 
		{
			i = j;
		}
	}
	if (i == 6) 
	{
	  return;
	}

	RobotEngy -= PeaShooterEnergyDrain;
	RLFrameAddChild(Scene,RobotZappaData[i].PositioningFrame);
	RLFrameAddScale(RobotZappaData[i].PositioningFrame, RLCombineReplace, 
				  RLVal(0.1), RLVal(0.1), RLVal(0.5));
	RLFrameSetOrientation(RobotZappaData[i].PositioningFrame, Robotframe, 
						RLVal(0), RLVal(0), RLVal(-1), 
						RLVal(0), RLVal(1), RLVal(0));
	RLFrameSetPosition(RobotZappaData[i].PositioningFrame, WhereIsIt, 
					 RLVal(0), RLVal(0), RLVal(0));
	RLFrameGetPosition(RobotZappaData[i].PositioningFrame, Scene,
					 &RobotZappaData[i].ProjectedPosition);

	RobotZappaData[i].CurrentPosition.x = RobotZappaData[i].ProjectedPosition.x;
	RobotZappaData[i].CurrentPosition.y = RobotZappaData[i].ProjectedPosition.y;
	RobotZappaData[i].CurrentPosition.z = RobotZappaData[i].ProjectedPosition.z;
	RobotZappaData[i].RemoveMeFlag = 0;
	RobotZappaData[i].collisionflag = 0;
	AddMovingObject(&(RobotZappaData[i]));
	RobotZappaHowLong[i] = RLVal(PeaShooterDuration);

	RLFrameSetRotation(RobotZappaData[i].PositioningFrame, 
		               RobotZappaData[i].PositioningFrame, 
					   0, 0, RLVal(1), RobotZapRotation);
	YBPlay3DSound(RobotShoot, Robotframe);
	if (GameStates.CurrentLevel==Trainer) 
	{
		YBSetSubTitle1(Vmode, "VISOR BEAM", RGB(0, 255, 0));
	}

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
}

void RobotZappaMotionFunction(MovingObjectData movedata)
{
	RLVector dir, up, where,dummy;
	RLFrame Scene = RLFrameGetScene(movedata->PositioningFrame);
	int i = movedata->data;

	//maybe I should do a special building intersection check here.
	//RLFrameGetPosition(RobotZappaData[i].PositioningFrame,Scene, &where);
	RLFrameGetOrientation(RobotZappaData[i].PositioningFrame, Scene, &dir, &up);
	RLVectorNormalise(&dir);
	movedata->CurrentPosition.x = movedata->ProjectedPosition.x;
	movedata->CurrentPosition.y = movedata->ProjectedPosition.y;
	movedata->CurrentPosition.z = movedata->ProjectedPosition.z;

	movedata->ProjectedPosition.x = movedata->CurrentPosition.x +
		                            RLMultiply3(DiffFrame, RLVal(1.5), dir.x);
	movedata->ProjectedPosition.y = movedata->CurrentPosition.y + 
		                            RLMultiply3(DiffFrame, RLVal(1.5), dir.y);
	movedata->ProjectedPosition.z = movedata->CurrentPosition.z + 
		                            RLMultiply3(DiffFrame, RLVal(1.5), dir.z);
	RLFrameSetPosition(RobotZappaData[i].PositioningFrame, Scene, 
		               movedata->ProjectedPosition.x, 
					   movedata->ProjectedPosition.y, 
					   movedata->ProjectedPosition.z);

	if (movedata->ProjectedPosition.y <
        SpuddeMapHeight2(movedata->ProjectedPosition.x,
		movedata->ProjectedPosition.z)
	   )
	{
	    movedata->collisionflag=1;
	}
	if(RobotZappaHowLong[i] <= 0)
	{
		RLFrameAddChild(behindthescene, movedata->PositioningFrame);
		movedata->RemoveMeFlag = 1;
	}
	RobotZappaHowLong[i] -= DiffFrame;

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
}

void NewZappaCallBack(RLFrame frame,void *arg,D3DVALUE delta)
{
	//This function allows the zapper to stay on screen without
	//being a part of the collision detection process.  The spew has
	//used all of its force already, but we leave it around to look good.
	if (ZappaHowLong <= 0)
	{
		ZappaOnScreen = 0;
		RLFrameAddChild(behindthescene, monstspew);
		RLFrameRemoveCallback(frame, NewZappaCallBack, arg);
	}
	ZappaHowLong -= DiffFrame;
}

void ZappaGotHit(MovingObjectData movedata)
{
	RLFrameAddCallback(movedata->PositioningFrame, NewZappaCallBack, NULL);
	movedata->RemoveMeFlag = 1;
}

void RobotZappaGotHit(MovingObjectData movedata)
{
	extern RLFrame Wcamera;
	RLFrame Scene = RLFrameGetScene(movedata->PositioningFrame);
	int i = movedata->data;

	movedata->RemoveMeFlag = 1;
	RLFrameAddChild(behindthescene, movedata->PositioningFrame);
	RLFrameAddChild(Scene, Mexplode); 
	RLFrameSetPosition(Mexplode, Scene, movedata->ProjectedPosition.x,
		               movedata->ProjectedPosition.y, movedata->ProjectedPosition.z);
	RLFrameSetOrientation(Mexplode, Wcamera, 0, 1, 0, 0, 0, 1);
	RLFrameSetVelocity(Mexplode, Scene, movedata->CollisionVector.x, 
		               movedata->CollisionVector.y,  movedata->CollisionVector.z);
	MXdata.OnScreen = 1;
	MXdata.HowLong = 8;
	ActivateParticleSystem(Robotexplosion, 3);
	ResetParticles(Robotexplosion);
	RobotZappaHowLong[i] = RLVal(0);

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
}


void InitClockworkGod(void)
{
	MovingObjects[0] = &RobotData;
	MovingObjects[1] = &MonsterData;
	NumMovingObjects = 2;
}

int AddMovingObject(MovingObjectData newmover)
{
	if (NumMovingObjects >= MaxMovingObjects || NumMovingObjects < 0)
	{
		char bydump[128];
		sprintf(bydump, "NumMovingObjects = %d, MaxMovingObjects = %d\n\n",NumMovingObjects,MaxMovingObjects);
		BYDumpInfo("Arugula arugula chive chive");
		BYDumpInfo(bydump);
		return 0;
	}
	MovingObjects[NumMovingObjects++] = newmover;
	return 1;
}

void RemoveMovingObject(MovingObjectData oldmover)
{
	oldmover->RemoveMeFlag = 1;
}





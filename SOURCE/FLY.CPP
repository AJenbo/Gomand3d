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
$Header:   H:/pvcs/pvcsproj/gomand3d.prj/FLY.CPV   1.56   15 May 1997 14:05:36   Bruce  $

$Log:   H:/pvcs/pvcsproj/gomand3d.prj/FLY.CPV  $
*
*   Rev 1.56   15 May 1997 14:05:36   Bruce
*renamed Robotani* and Robotmov* to be
*robani* and robmov*
*
*   Rev 1.55   07 May 1997 14:23:32   Bruce
*morged versions 1.53.1.0 and 1.54
*
*   Rev 1.54   07 May 1997 13:13:12   Bruce
*changed from .x to .bin loading of models,
*added calls to delete the binaries after the
*models have been loaded.
*
*
*   Rev 1.53.1.0   24 Apr 1997 14:26:16   JEREMIAH
*Changed texture loading calls to 
*accomodate specification of texture 
*formats.
*
*   Rev 1.53   10 Apr 1997 11:07:16   JEREMIAH
*Load semitransparent resources for 
*SEMIFANCY transparency type.
*
*
*   Rev 1.52   28 Mar 1997 14:45:26   JEREMIAH
*Added secret code ~WETPIPE.
*
*   Rev 1.51   Mar 20 1997 14:10:28   JEREMIAH
*Added a PageUnlock to the cleanup code.
*
*   Rev 1.50   18 Mar 1997 15:56:06   BRUCE
*No more obliteration of models
*
*   Rev 1.49   18 Mar 1997 14:59:50   JEREMIAH
*Added pragmas to not optimize sections
*of code.
*
*   Rev 1.48   17 Mar 1997 20:35:02   BRUCE
*RenderingIsOk around Game Cleanup.
*Put pragmas around the game cleanup
*code to make sure that there's no 
*optimization going on that could change 
*the order of calls in the function, and put
*in many phantom printouts to try to figure
*out where the game was crashing on 
*exit.
*
*   Rev 1.47   17 Mar 1997 11:00:52   BRUCE
*If you quit a level, everything will be totally
*reset when you reenter the level.
*
*   Rev 1.46   14 Mar 1997 14:02:20   JEREMIAH
*Hooked lighting to detail level "highest"
*
*   Rev 1.45   12 Mar 1997 12:43:36   JEREMIAH
*Load new shield and 200 resources if
*semi-transparency is used.
*
*   Rev 1.44   12 Mar 1997 10:38:26   JEREMIAH
*Load Robot homers as transparent 
*objects.
*
*   Rev 1.43   07 Mar 1997 19:21:32   JEREMIAH
*Made sheilds transparent.
*
*   Rev 1.42   07 Mar 1997 13:52:24   JEREMIAH
*Added diagnostic function to BYDump
*the AE variables when F2 is pressed.
*
*   Rev 1.41   06 Mar 1997 14:39:28   JEREMIAH
*Replaced render calls to sprites/complex
*sprites with a call to move particles.
*
*   Rev 1.40   05 Mar 1997 12:38:40   BRUCE
*uncommented the lines that load the
*snowball's texture.
*
*   Rev 1.39   04 Mar 1997 16:05:56   BRUCE
*Removed crash on Esc or timeout in
*Autodemo if the MonsterZapper is 
*on screen.
*
*   Rev 1.38   03 Mar 1997 12:47:34   BRUCE
*fixed bug with keyboard input that didn't
*register keys which were being screened
*for their first time down.
*
*   Rev 1.37   28 Feb 1997 13:54:50   BO
*added code to detect key to toggle radar scale
*
*   Rev 1.36   27 Feb 1997 21:38:52   BRUCE
*If a key is pressed in Autodemo mode,
*the game leaves the 3dworld immediately
*and goes to the wrapper.
*
*   Rev 1.35   27 Feb 1997 20:02:40   BRUCE
*removed ProcessKeyUp
*put escape, y or n, and secret codes
*into BYKd3DGame instead,
*streamlined ProcessKeyDown somewhat
*
*   Rev 1.34   25 Feb 1997 14:07:24   JEREMIAH
*Debranched 1.33.1.0 to 1.34.
*
*   Rev 1.33.1.0   25 Feb 1997 13:58:58   JEREMIAH
*Added calls in the cleanup code to 
*remove Robot/monster animation/movement
*engines.
*
*   Rev 1.33   24 Feb 1997 17:06:12   TIM
*Set directional light to default on levels 4 & 5. Ambient light is the default light on levels 123
*
*   Rev 1.32   21 Feb 1997 16:08:52   JEREMIAH
*Murged 1.30.1.0 and 1.31.
*
*   Rev 1.30.1.0   21 Feb 1997 16:05:24   JEREMIAH
*Changed field of view for letterbox mode.
*
*   Rev 1.31   21 Feb 1997 15:59:48   TIM
*create light for any situation (directional light on f1 toggle)
*
*   Rev 1.30   20 Feb 1997 10:44:30   JEREMIAH
*Consolidated 3D movie global variables 
*into a structure. 
*
*   Rev 1.29   19 Feb 1997 17:54:38   JEREMIAH
*Added "TRIPWIRE" secret code to kill
*Robot on demand.
*
*   Rev 1.28   14 Feb 1997 19:32:14   BRUCE
*changed level to GameStates.CurrentLevel
*changed submonster to GameStates.CurrentSubmonster
*changed In3DMovie to GameStates.Is3DMovie
*changed AutoDemoFlag to GameStates.IsAutodemo
*changed netPlay to GameStates.IsNetplay
*
*
*   Rev 1.27   10 Feb 1997 12:21:48   JEREMIAH
*Changed by Bo.
*- added code in ProcessKeyDown function to jump out of the game in 
*autodemo mode when a user press anykey.
*
*
*   Rev 1.26   07 Feb 1997 17:20:54   JEREMIAH
*Undid the change in 1.24
*
*   Rev 1.25   07 Feb 1997 10:41:22   BRUCE
*Changed light color for trainer leve.
*
*   Rev 1.24   07 Feb 1997 08:44:02   BRUCE
*repositioned the destruction of monster's
*zapper to before the destruction of the monster,
*in case the monster was zapping at the
*time the level ended, which would cause
*a crash.  Should only have occurred in the
*autodemo, or when someone exits the level
*before it's finished.
*
*   Rev 1.23   06 Feb 1997 16:09:44   JEREMIAH
*Customized light colors for each level.
*Changed from parallel point to directional
*light source.
*
*   Rev 1.22   06 Feb 1997 08:15:42   BRUCE
*took control of whichRobot
*
*   Rev 1.21   02 Feb 1997 21:28:16   BRUCE
*morged tims and my changes.
*
*   Rev 1.20   31 Jan 1997 18:04:32   TIM
*Implemented F1 toggle for light
*
*
*   Rev 1.19.1.0   31 Jan 1997 15:42:58   BRUCE
*added calls to BootRobotFrames and
*BootMonsterFrames.
*
*   Rev 1.19   28 Jan 1997 14:03:22   TIM
*Added secret code to display frame rate
*
*   Rev 1.18   27 Jan 1997 10:39:56   JEREMIAH
*Fixed autodemo timeout.
*
*Changed calls to makedust() to reflect
*new method of particle system texture
*handling.
*
*   Rev 1.17   24 Jan 1997 10:45:02   JEREMIAH
*Moved cleanup calls out of frame callback
*and into the renderloop.
*
*   Rev 1.16   22 Jan 1997 13:17:16   JEREMIAH
*Cleared NextLevel flag in startup and 
*cleanup code.
*
*   Rev 1.15   22 Jan 1997 12:27:28   TIM
*No change
*
*
*   Rev 1.14   22 Jan 1997 11:48:14   JEREMIAH
*Added screen capture functions to the F2
*keypress.
*
*   Rev 1.13   14 Jan 1997 15:09:38   JEREMIAH
*Enabled netplay in its most rudimentary
*form.
*
*   Rev 1.12   08 Jan 1997 11:54:50   BRUCE
*changed jet left and jet right keyboard entry
*to remove shield+turn = jet left or right bug.
*
*   Rev 1.11   07 Jan 1997 17:12:58   JEREMIAH
*Modified FinalProcess() to correctly
*abstract input.
*
*Altered the calls to makedust() to share 
*one dust texture between two psystems.
*
*   Rev 1.10   07 Jan 1997 14:08:06   BRUCE
*fixed secret codes (I think) and may have 
*made improvements to handling of multiple
*key input.
*
*   Rev 1.9   20 Dec 1996 17:06:36   JEREMIAH
*Changed filenames of textures to match
*new filename conventions for level-specific
*palettes.
*
*   Rev 1.8   Dec 19 1996 10:41:00   JEREMIAH
*Changed by Tim.  Reads in snoball.x
*correctly.
*
*   Rev 1.7   18 Dec 1996 08:59:14   BRUCE
*removed reading of monster move and
*animation dat files from BuildScene, to
*account for different dat files for different
*submonsters.
*
*   Rev 1.6   16 Dec 1996 10:48:06   JEREMIAH
*Changed by ITC.  Added code for netplay.
*
*   Rev 1.5   13 Nov 1996 16:35:32   BO
* Found another place to exit to 2D, and add switch flag 
* for the game user interface.  Removed bBYRenderingOK
* = TRUE in these two places.
*
*   Rev 1.4   13 Nov 1996 15:55:38   BO
*add a switch flag to control the display of
*game user interface.
*
*   Rev 1.3   13 Nov 1996 09:46:46   BO
** change gdwKeys, CurrentCharacterInput as local variables
** remove input.h, add tkinput.h
** modified ProcessKeyDown and ProcessKeyUp so that they
*not be called in 2D wrapper,
** add FinalProcess to combine all input together
*
*
*
*   Rev 1.2   11 Nov 1996 11:26:56   JEREMIAH
*Changed by Dong Min (ITC).  Fixed minor
*bug with confirmation of exit.
*
*   Rev 1.1   08 Nov 1996 16:13:00   JEREMIAH
*Changed by Liu GuoHong (ITC).  Added
*calls to DirectInput keyboard input.
***********************************************************************/

#define INITGUID

#include "d3drmwin.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <direct.h>


//Add by Eric 11/12/96
#include <mmsystem.h>

char   Text1[] = "I miss your blasma, idiot!";
char   Text2[] = "Goman, I never want to see you again!";

extern "C"
{
    #include "netplay.h"

    extern int  RobotLife, MnstLife;
	extern int ZappaOnScreen;
   extern int wetpipe;

}
//end of Eric

extern "C"
{
	#include "global.h"
	#include "camera.h"
	#include "landscap.h"
	#include "clutter.h"
	#include "gosys.h"
	#include "boink.h"
	#include "mdtex.h"
	#include "cars.h"
	#include "keycom.h"
	#include "Robotmove.h"
	#include "Robotanim.h"
	#include "monmove.h"
	#include "monanim.h"
	#include "monthink.h"
	#include "plasma.h"
	#include "psystem.h"
	#include "spritlib.h"
	#include "building.h"
	#include "bldgboom.h"
	#include "mybuild.h"
	#include "imisc.h"
	#include "timing.h"
	#include "tekanim.h"
	#include "BinLoad.h"
	#include "ichars.h"
}
#include "tkinput.h"
#include "rmfull.h"
#include "fly.h"
#include "wrapper.h"
#include "byglobal.h"
#include "d3dappi.h"
  
extern "C"
{
	extern long int NewJoyAction;
//	extern int level;
	extern int Vmode;
	extern char DatPath[];
	extern char BmpPath[];
	extern char XafPath[];
	extern RLFrame badguyframe;
	extern RLFrame RobotBlockSphere;
	extern int shielddlist;
//	extern BOOL   AutoDemoFlag;    
	extern volatile long int InputInt, InputInt2, InputIntDevNull;
	extern volatile long int *InputIntPtr, *InputIntPtr2, *InputIntPtr3;	
	extern BOOL PlayAsMonster;
//	extern BOOL In3DMovie;
	extern Psystem *NeallothRings;
	extern RLFrame BombSphere;
	extern BOOL   KbFlag;
	extern iobjdlist* allmiscdlists[];
//	extern int submonster;
	extern visible_buildings missiontarget;
	extern RLFrame goodguyframe;
	extern RLFrame MonsterScaleFrame;
	extern Caminfo* camerastuff;


	HWND BYMainHwnd = NULL;
	HINSTANCE BYMainInstance = NULL;
	int NextLevel = 0;
	Psystem *PeaShooter = NULL;
	Psystem *SixShooter = NULL;
	Psystem *Cussin = NULL;
	PlasmaData Robotspewdata;
	ZappaData monstspewdata;
	ExplosionData MXdata, MonXdata;
	RLFrame Mexplode = NULL;
	RLFrame Monsplode = NULL;
	LPDIRECT3DRMFRAME RealLightFrame = NULL;  // frame for lights created by TIM
	LPDIRECT3DRMFRAME FullLightFrame = NULL;  // frame for lights created by TIM
	static BOOL bLightsOn = TRUE; // added by TIM for lighting toggle on F1


	Psystem *Robotexplosion = NULL;
	Psystem *monsterexplosion = NULL;
	Psystem *Robotdust = NULL; 				      
	Psystem *monstdust = NULL; 					 
	TEXTURESTRUCT  shieldtex;
	TEXTURESTRUCT  Robotzaptex;
	TEXTURESTRUCT  blasttex;
	TEXTURESTRUCT  snoballtex;

	
}
extern "C"
{
   extern int monthink;
   extern int sporehunt;
   extern void SwapRobotNMonster(int whichone);
   extern int MnstLife;
   extern struct _moving_object_data_      MonsterData; 
   extern int MnstEngy;
   extern int MeltAMonster(int alive);
   extern BOOL PlayAsMonster;
   extern int RobotEngy;
   extern BOOL PlayerHasWon;
}
 

extern "C" RLValue HuntDesire, MissionDesire, EvadeDesire, GenericDesire, DefendDesire;
extern "C" RLValue Rage, Fear, Boredom, Joy;


BOOL QHNetPlayWaitConnect();


_int64 gdwKeys;
static _int64 dwOldKeys = 0;

extern BOOL bBYRenderingIsOK;
char    whereincode[127];
//#define CurrentCharacterInput (*InputIntPtr)
long int CurrentCharacterInput;
long int CurKeyActions[28]=
{
	(COMMANDForward|COMMANDWeakShift),                     // A=0, walk forward
//    (COMMANDHighAttack|COMMANDStrongShift),                // B=12, plasma shuriken
	(COMMANDShuriken),
    //(COMMANDHighAttack|COMMANDWeakShift),                  // C=11, photon cannon 
	(COMMANDPhotonCannon),
    (COMMANDForward|COMMANDStrongShift),                   // D=5, fly
    0,                  // E
    (COMMANDJump),                                         // F=9, Jump
    (COMMANDCrouch),                                       // G=10, Crouch
    (COMMANDBack|COMMANDStrongShift),                      // H=3, thrust back
    0,                                                     // I
    (COMMANDLeft),                                         // J=6, turn left
    (COMMANDRight),                                        // K=7, turn right
    0, 0,                                                  // L, M
    (COMMANDHighAttack|COMMANDDefenseShift),               // N=8, shield
    0, 0, 0, 0,                                            // O,P,Q,R
    (COMMANDForward|COMMANDMediumShift),                   // S=4, run
    0, 0,                                                  // T,U
    //(COMMANDHighAttack|COMMANDMediumShift),                // V=14, plasma blades
	(COMMANDPlasmaBlades),
    0,                                                     // W
    //(COMMANDLowAttack|COMMANDWeakShift),                 // X=16, Concussion
	(COMMANDUltraBlast),
    0,													   //Y
    //(COMMANDLowAttack),                                                     //Z=Something, Visorbeam
	(COMMANDVisorBeam),
    (COMMANDJetLeft),									   // '<'=6, thrust left
    (COMMANDJetRight)									   // '>'=7, thrust right
};

typedef struct {
	LPDIRECT3DRMANIMATIONSET animset;
	D3DVALUE time;
} animationCallbackArgs;

extern "C"
{
	LPDIRECT3DRMFRAME Wscene = 0;
	LPDIRECT3DRMFRAME Wcamera = 0;
	LPDIRECT3DRMFRAME behindthescene = 0;
	LPDIRECT3DRMDEVICE Wdevice = 0;
	LPDIRECT3DRMVIEWPORT Wview = 0;
	LPDIRECT3DRMFRAME monstframe = NULL;
	LPDIRECT3DRMFRAME Robotframe = NULL;
	LPDIRECT3DRMFRAME Robotspew = NULL;
	LPDIRECT3DRMFRAME monstspew = NULL;
	animationCallbackArgs *RobotAni = NULL;
	animationCallbackArgs *MonstAni = NULL;
	//_int64	 gdwKeys;            // gameplay keys
	extern BOOL bAskQuit; 
}


void BYOBCleanSBuffer(void);
void BYOBGetSecretCode(DWORD wparam);
void BYOBSetSecretCode(void);

void ClearupKeyDownMessage(void);
void ClearupKeyUpMessage(void);

//New Direct keyboard process.
int SecretCode=0;
extern "C" short level_flag[7];

#pragma optimize( "", off)

BOOL BYKd3DGame(HWND win, UINT msg, WPARAM wparam, LPARAM lparam)
{

	if (msg==WM_KEYDOWN)
	{
		if (GameStates.IsAutodemo)
		{
			bBYRenderingIsOK = FALSE;
			bShowGameUI=FALSE;
			CleanupGame3DPart();
			AutoDemoNext=FALSE;		
			BYKbFrom3DTo2D(BYMainHwnd, NULL, NULL, NULL);

			QuitFlag = TRUE;
			bAskQuit = FALSE;		
			return TRUE;
		}

		
		
		if(wparam==VK_ESCAPE)
		{
			if (!GameStates.Is3DMovie) 
			{
				bAskQuit = TRUE;

				//Add by Eric 11/12/96
				if (GameStates.IsNetplay)
				{
					if (isIn3DGame)
					{
						EventSndBuf.MsgId = NEW_MSG;
						EventSndBuf.Event = EVENT_ESC;
					}
					else
					{
					//send EVENT_GOODBYE
					}
				}
			//end of Eric
			}
			else
			{
				Ending3DMovie.SegCountdown = RLVal(0.0);
			}

		}

	
		if (bAskQuit)
		{
			if (wparam == 'Y')
			{
				bBYRenderingIsOK = FALSE;
				bShowGameUI=FALSE;
				GameStates.LevelHonor[GameStates.CurrentLevel]=TRUE;
				GameStates.MonsterLose=FALSE;
				GameStates.RobotLose=FALSE;
				GameStates.IsMonsterDead[GameStates.CurrentLevel][Alpha]=FALSE;
				GameStates.IsMonsterDead[GameStates.CurrentLevel][Beta]=FALSE;
				GameStates.IsMonsterDead[GameStates.CurrentLevel][Gamma]=FALSE;
				GameStates.IsRobotDead[GameStates.CurrentRobot]=FALSE;
				GameStates.CurrentSubmonster=Alpha;
				Hours = Minutes = Seconds = Thousandths = 0;
				bBYRenderingIsOK = FALSE;
				CleanupGame3DPart();
				bBYRenderingIsOK = TRUE;
				level_flag[GameStates.CurrentLevel]=0;
				//bBYRenderingIsOK = TRUE;
				BYKbFrom3DTo2D(BYMainHwnd, NULL, NULL, NULL);

				QuitFlag = TRUE;
				bAskQuit = FALSE;
			}
			else if (wparam ==  'N')
			{
				bAskQuit = FALSE;
			}
		}
	
		//case VK_F6:
		//case 192://'~'
		if ( (wparam == VK_F6) || (wparam == 192) )
		{
			SecretCode=1;
			BYOBCleanSBuffer();
		}

		if (SecretCode) 
		{
			if(wparam>='A' && wparam<='Z')
				BYOBGetSecretCode(wparam);
			//BYOBGetSecretCode(wparam);
			//LGH modified.
		} 



	
	
	} 
	else if (msg==WM_KEYUP)
	{
		//case VK_F6:
		//case 192://'~'
		if ( (wparam == VK_F6) ||
			 (wparam == 192)  )
		{
			SecretCode=0;
			BYOBSetSecretCode();
		}

	
	} // end if WM_KEYUP
	return TRUE;
}
#pragma optimize( "", on)



static __int64 LetterMask = 
KEY_A |
KEY_B |
KEY_C |
KEY_D |
KEY_E |
KEY_F |
KEY_G |
KEY_H |
KEY_I |
KEY_J |
KEY_K |
KEY_L |
KEY_M |
KEY_N |
KEY_O |
KEY_P |
KEY_Q |
KEY_R |
KEY_S |
KEY_T |
KEY_U |
KEY_V |
KEY_W |
KEY_X |
KEY_Y |
KEY_Z ;


//void ProcessKeyUp ()
//{
//	dwOldKeys = gdwKeys;
//}

//New Direct keyboard process.
extern CDirectInput di;

void ProcessKeyDown (void)
{
//	unsigned long int keybit = 0;
	__int64 KeysPressed;
	if ((BYRender != Render3DWorld) || GameStates.IsAutodemo)
	{
		return;
	}

	CurrentCharacterInput=0;

	gdwKeys = di.ReadDIKdData(TRUE);
	KeysPressed = (~dwOldKeys) & gdwKeys;
	//DI_ReadKeys();




	//case VK_F12:
	if (KeysPressed & KEY_F12)
	{
		//YBshow = !YBshow;
		//ShowFPS = !ShowFPS;
	}

	//case VK_F11:
	if (KeysPressed & KEY_F11)
	{
		/*{
		FILE *shithead;
		char datname[16];
		sprintf(datname,"f:\\user\\bruce\\dat\\Robotmov%d.dat",GameStates.CurrentRobot);
		shithead=fopen(datname,"rt");
		if(shithead)
			GetRobotMovementInfo(shithead);
		if(shithead)
			fclose(shithead);

		DefineRobotMotionConstants();

		sprintf(datname,"f:\\user\\bruce\\dat\\Robotani%d.dat",GameStates.CurrentRobot);
		shithead=fopen(datname,"rt");
		if(shithead)
			GetRobotAnimInfo(shithead);
		if(shithead)
			fclose(shithead);
		DefineRobotAnimationConstants();

		sprintf(datname,"f:\\user\\bruce\\dat\\monmove%d.dat",GameStates.CurrentLevel);
		shithead=fopen(datname,"rt");
		if(shithead)
			GetMonsterMovementInfo(shithead);
		if(shithead)
			fclose(shithead);

		DefineMonsterMotionConstants();

		sprintf(datname,"f:\\user\\bruce\\dat\\monanim%d.dat",GameStates.CurrentLevel);
		shithead=fopen(datname,"rt");
		if(shithead)
			GetMonsterAnimInfo(shithead);
		if(shithead)
			fclose(shithead);

		DefineMonsterAnimationConstants();
		}
		YBShowStatus = (YBShowStatus+1)%3;
		if (YBShowStatus==0) {
			YBshow=TRUE;
			ShowSub=TRUE;
		}
		if (YBShowStatus==1) {
			ShowSub=FALSE;
		}
		if (YBShowStatus==2 && Vsize==4) {
			YBshow = FALSE;
		} else if (YBShowStatus==2) {
			YBshow=TRUE;
			ShowSub=TRUE;
		}*/
	}

	//case VK_SPACE:
	if (gdwKeys & KEY_SPACE)
	{
		KbFlag = TRUE;
		CurrentCharacterInput |= COMMANDVisorBeam;
	}

	//case VK_UP:
	if (gdwKeys & KEY_UP)
	{
		KbFlag = TRUE;
		CurrentCharacterInput |=COMMANDForward;
	}

	//case VK_DOWN:
	if (gdwKeys & KEY_DOWN)
	{
		KbFlag = TRUE;
		CurrentCharacterInput |=COMMANDBack;
	}

	//case VK_LEFT:
	if (gdwKeys & KEY_LEFT)
	{
		KbFlag = TRUE;
		CurrentCharacterInput |=COMMANDLeft;
	}

	//case VK_RIGHT:
	if (gdwKeys & KEY_RIGHT)
	{
		KbFlag = TRUE;
		CurrentCharacterInput |=COMMANDRight;
	}

	//case VK_PRIOR:
	if (gdwKeys & KEY_PRIOR)
	{
		KbFlag = TRUE;
		CurrentCharacterInput |=COMMANDJump;
	}

	//case VK_NEXT:
	if (gdwKeys & KEY_NEXT)
	{
		KbFlag = TRUE;
		CurrentCharacterInput |=COMMANDCrouch;
	}

	//case VK_HOME:
	if (gdwKeys & KEY_HOME)
	{
		KbFlag = TRUE;
		CurrentCharacterInput |=COMMANDHighAttack;
	}

	//case VK_END:
	if (gdwKeys & KEY_END)
	{
		KbFlag = TRUE;
		CurrentCharacterInput |=COMMANDLowAttack;
	}

	//case VK_SHIFT:
	if (gdwKeys & KEY_SHIFT)
	{
		KbFlag = TRUE;
		CurrentCharacterInput |=COMMANDWeakShift;
	}

	//case VK_CONTROL:
	if (gdwKeys & KEY_CONTROL)
	{
		KbFlag = TRUE;
		CurrentCharacterInput |=COMMANDMediumShift;
	}

	//case VK_TAB:
	if (gdwKeys & KEY_TAB)
	{
		KbFlag = TRUE;
		CurrentCharacterInput |=COMMANDStrongShift;
	}

	//case VK_INSERT:
	if (gdwKeys & KEY_INSERT)
	{
		KbFlag = TRUE;
		CurrentCharacterInput |=COMMANDDefenseShift;
	}

	//case VK_RETURN:
	if (gdwKeys & KEY_RETURN)
	{
		KbFlag = TRUE;
		CurrentCharacterInput |=COMMANDStart;
	}

	/* VK_0 thru VK_9 are the same as ASCII '0' thru '9' (0x30 - 0x39) */
	/* VK_A thru VK_Z are the same as ASCII 'A' thru 'Z' (0x41 - 0x5A) */

	if (KeysPressed & KEY_F2)
	{
#ifdef CAPBMP
		CaptureScreenImage();
      SaveScreenImage();
#endif
	}

	if (KeysPressed & KEY_F2)
	{
      char fps2[150];   

      BYDumpInfo("**********************************************\n");
      sprintf(fps2, "Robot Life: %d\n", RobotLife);        
      BYDumpInfo(fps2);
      sprintf(fps2, "Robot Energy: %d\n", RobotEngy);        
      BYDumpInfo(fps2);
      sprintf(fps2, "Monster Life: %d\n", MnstLife);        
      BYDumpInfo(fps2);
      sprintf(fps2, "Monster Energy: %d\n", MnstEngy);        
      BYDumpInfo(fps2);
      sprintf(fps2, "Hunt the Robot desire: %f\n", HuntDesire);        
      BYDumpInfo(fps2);
      sprintf(fps2, "Hunt the Robot desire: %f\n", HuntDesire);        
      BYDumpInfo(fps2);
      sprintf(fps2, "Mission target desire: %f\n", MissionDesire);        
      BYDumpInfo(fps2);
      sprintf(fps2, "Evade the Robot desire: %f\n", EvadeDesire);        
      BYDumpInfo(fps2);
      sprintf(fps2, "Generic building desire: %f\n", GenericDesire);        
      BYDumpInfo(fps2);
      sprintf(fps2, "Defense desire: %f\n", DefendDesire);        
      BYDumpInfo(fps2);
      sprintf(fps2, "Rage: %f\n", Rage);        
      BYDumpInfo(fps2);
      sprintf(fps2, "Fear: %f\n", Fear);        
      BYDumpInfo(fps2);
      sprintf(fps2, "Boredom: %f\n", Boredom);        
      BYDumpInfo(fps2);
      sprintf(fps2, "Joy: %f\n", Joy);        
      BYDumpInfo(fps2);
      BYDumpInfo("**********************************************\n");
   }

	if (KeysPressed & KEY_F1)
	{
		bLightsOn = !bLightsOn;
		if (bLightsOn){
			// move lights to behind the scene 
			behindthescene->AddChild(RealLightFrame); // add frame to the scene 
			Wscene->AddChild(FullLightFrame);
		}
		else{
			// move lights back into scene
			Wscene->AddChild(RealLightFrame); // add frame to the scene 
			behindthescene->AddChild(FullLightFrame); // add frame to the scene 

		}
	}





    //case 'A','B',...'Z':
	if (gdwKeys & LetterMask)
	{
		for (char j = 0; j < 26; j++)
		{
			//KEY_A = 0x080000
			if ((((__int64)0x080000) << j) & gdwKeys)
			{
				CurrentCharacterInput|=CurKeyActions[j];
			}
		}
		//CurrentCharacterInput|=CurKeyActions[(wparam-'A')];
		//LGH modified.
	}

	//case 188://'<'
	if (gdwKeys & KEY_188)
	{
		CurrentCharacterInput|=CurKeyActions[26];
	}

	//case 190://'>'
	if (gdwKeys & KEY_190)
	{
		CurrentCharacterInput|=CurKeyActions[27];
	}

	//case '1':
	if (KeysPressed & KEY_1)
	{
		if (!SecretCode)
		{
			camerastuff->method=POV;
			if (GameStates.CurrentLevel==Trainer) 
				YBSetSubTitle1(Vmode, "WATCHY FIRST-PERSON", RGB(0, 255, 0));
			ResetCameraTarget(camerastuff);
		}
		else
		{
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=6;
			if (GameStates.CurrentLevel==Trainer) 
				YBSetSubTitle1(Vmode, "WATCHY ALPHA CHRYSALIS VIEW", RGB(0, 255, 0));
//				extern visible_buildings missiontarget;
//				extern int submonster;
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=6;
			SetCameraTarget(camerastuff, (RLFrame)missiontarget.building_ptr[3]->rlframe);
		}
	}

	//case '2':
	if (KeysPressed & KEY_2)
	{
		if (!SecretCode)
		{
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=2;
			if (GameStates.CurrentLevel==Trainer) 
				YBSetSubTitle1(Vmode, "WATCHY OVER THE SHOULDER", RGB(0, 255, 0));
			ResetCameraTarget(camerastuff);
		}
		else
		{
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=6;
			if (GameStates.CurrentLevel==Trainer) 
				YBSetSubTitle1(Vmode, "WATCHY BETA CHRYSALIS VIEW", RGB(0, 255, 0));
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=6;
			SetCameraTarget(camerastuff, (RLFrame)missiontarget.building_ptr[4]->rlframe);
		}
	}

	//case '3':
	if (KeysPressed & KEY_3)
	{
		if (!SecretCode)
		{
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=4;
			if (GameStates.CurrentLevel==Trainer) 
				YBSetSubTitle1(Vmode, "WATCHY HIGH OVER THE SHOULDER", RGB(0, 255, 0));
			ResetCameraTarget(camerastuff);
		}
		else
		{
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=6;
			if (GameStates.CurrentLevel==Trainer) 
				YBSetSubTitle1(Vmode, "WATCHY GAMMA CHRYSALIS VIEW", RGB(0, 255, 0));
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=6;
			SetCameraTarget(camerastuff, (RLFrame)missiontarget.building_ptr[5]->rlframe);
		}
	}

	//case '4':
	if (KeysPressed & KEY_4)
	{
		if (!SecretCode)
		{
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=7;
			if (GameStates.CurrentLevel==Trainer) 
				YBSetSubTitle1(Vmode, "WATCHY LEFT SIDE", RGB(0, 255, 0));
			ResetCameraTarget(camerastuff);
		}
		else
		{
			if (GameStates.CurrentLevel==Trainer) 
				YBSetSubTitle1(Vmode, "WATCHY POWERUP #1 VIEW", RGB(0, 255, 0));
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=6;
			SetCameraTarget(camerastuff, PowerupFrame(0));
		}
	}

	//case '5':
	if (KeysPressed & KEY_5)
	{
		if (!SecretCode)
		{
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=8;
			if (GameStates.CurrentLevel==Trainer) 
				YBSetSubTitle1(Vmode, "WATCHY RIGHT SIDE", RGB(0, 255, 0));
			ResetCameraTarget(camerastuff);
		}
		else
		{
			if (GameStates.CurrentLevel==Trainer) 
				YBSetSubTitle1(Vmode, "WATCHY POWERUP #2 VIEW", RGB(0, 255, 0));
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=6;
			SetCameraTarget(camerastuff, PowerupFrame(1));
		}
	}

	//case '6':
	if (KeysPressed & KEY_6)
	{
		if (!SecretCode)
		{
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=3;
			if (GameStates.CurrentLevel==Trainer) 
				YBSetSubTitle1(Vmode, "WATCHY REVERSE VIEW", RGB(0, 255, 0));
			ResetCameraTarget(camerastuff);
		}
		else
		{
			if (GameStates.CurrentLevel==Trainer) 
				YBSetSubTitle1(Vmode, "WATCHY POWERUP #3 VIEW", RGB(0, 255, 0));
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=6;
			SetCameraTarget(camerastuff, PowerupFrame(2));
		}
	}

	//case '7':
	if (KeysPressed & KEY_7)
	{
		if (!SecretCode)
		{
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=5;
			if (GameStates.CurrentLevel==Trainer) 
				YBSetSubTitle1(Vmode, "WATCHY OVERHEAD", RGB(0, 255, 0));
			ResetCameraTarget(camerastuff);
		}
		else
		{
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=6;
			if (GameStates.CurrentLevel==Trainer) 
				YBSetSubTitle1(Vmode, "WATCHY MISSION TARGET #1 VIEW", RGB(0, 255, 0));
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=6;
			SetCameraTarget(camerastuff, (RLFrame)missiontarget.building_ptr[0]->rlframe);
		}
	}

	//case '8':
	if (KeysPressed & KEY_8)
	{
		if (!SecretCode)
		{
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=6;
			if (GameStates.CurrentLevel==Trainer) 
				YBSetSubTitle1(Vmode, "WATCHY AERIAL", RGB(0, 255, 0));
			ResetCameraTarget(camerastuff);
		}
		else
		{
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=6;
			if (GameStates.CurrentLevel==Trainer) 
				YBSetSubTitle1(Vmode, "WATCHY MISSION TARGET #2 VIEW", RGB(0, 255, 0));
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=6;
			SetCameraTarget(camerastuff, (RLFrame)missiontarget.building_ptr[1]->rlframe);
		}
	}

	//case '9':
	if (KeysPressed & KEY_9)
	{
		if (!SecretCode)
		{
			if (!GameStates.CurrentLevel==Trainer) 
				YBSetSubTitle1(Vmode, "WATCHY HAS LANDED", RGB(0, 255, 0));
			camerastuff->method=HUMANEYE;
		}
		else
		{
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=6;
			if (GameStates.CurrentLevel==Trainer) 
				YBSetSubTitle1(Vmode, "WATCHY MISSION TARGET #3 VIEW", RGB(0, 255, 0));
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=6;
			SetCameraTarget(camerastuff, (RLFrame)missiontarget.building_ptr[2]->rlframe);
		}
	}

	//case '0':
	if (KeysPressed & KEY_0)
	{
		if (!SecretCode)
		{
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=2;
			SetCameraTarget(camerastuff, badguyframe);
			if (GameStates.CurrentLevel==Trainer) 
				YBSetSubTitle1(Vmode, "WATCHY MONSTER VIEW", RGB(0, 255, 0));
		}
		else
		{
			camerastuff->method=SLUGDRIFT;
			camerastuff->zone=3;
			SetCameraTarget(camerastuff, badguyframe);
			if (GameStates.CurrentLevel==Trainer) 
				YBSetSubTitle1(Vmode, "WATCHY MONSTER VIEW", RGB(0, 255, 0));
		}
	}

	if (gdwKeys & KEY_SCALE)
	{
		bScaleRadar = !bScaleRadar;
	}
	dwOldKeys = gdwKeys;

}



void FinalProcess(void)
{
	*InputIntPtr = CurrentCharacterInput|di.GetDIMsAction()|NewJoyAction;
}
//CallBack For the Animation Etc.
static void movePlane(RLFrame plane, void *arg, D3DVALUE delta)
{
    RLFrame monframe=(RLFrame)arg;
	Ticket();
    
	if (GameStates.IsAutodemo && !GameStates.Is3DMovie)
	{
		InputIntPtr=				// Input stream from player
			&InputIntDevNull;			// Input stream to be ignored
		InputIntPtr2=				// Input stream from monster AE
			&InputInt2;					// Input stream to monster
		InputIntPtr3=				// Input stream from Robot AE
			&InputInt;					// Input stream to Robot
    	
    	cogitate();
		Robotruminate();
	}
	else
	if (GameStates.Is3DMovie)
	{
		InputIntPtr=				// Input stream from player
			&InputIntDevNull;			// Input stream to be ignored
		InputIntPtr2=				// Input stream from monster AE
			&InputInt2;					// Input stream to monster
		InputIntPtr3=				// Input stream from Robot AE
			&InputInt;					// Input stream to Robot
	}
	else
	{
		if ((PlayAsMonster) || (goodguyframe==monstframe)) 
		{
			InputIntPtr=				// Input stream from player
				&InputInt2;					// Input stream to monster
			InputIntPtr2=				// Input stream from monster AE
				&InputIntDevNull;			// Input stream to be ignored
			InputIntPtr3=				// Input stream from Robot AE
				&InputInt;					// Input stream to Robot
			//Robotruminate(); //Rem by Eric 11/12/96

			//Add by Eric 11/12/96
            if (!GameStates.IsNetplay)
			{
			    Robotruminate();             // close AI if net play. Sanfo 8.5
			}
			//end of Eric

		}
		else
		{
			InputIntPtr=				// Input stream from player
				&InputInt;					// Input stream to Robot
			InputIntPtr2=				// Input stream from monster AE
				&InputInt2;					// Input stream to monster
			InputIntPtr3=				// Input stream from Robot AE
				&InputIntDevNull;			// Input stream to be ignored
			//cogitate(); //Rem by Eric 11/12/9

			//Add by Eric 11/12/96
            if (!GameStates.IsNetplay)
			{
			    cogitate();                 // close AI if net play. Sanfo 8.5
			}
			//end of Eric

		}
	}
		
    ClockworkGod();
	RenderCharacters(camerastuff->method);
	MoveAllParticles();
}

extern LPDIRECT3DRM lpD3DRM;
BOOL
InitLight(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
           LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera)
{
	LPDIRECT3DRMLIGHT FullAmblight = NULL;
	LPDIRECT3DRMLIGHT RealAmblight = NULL;
	LPDIRECT3DRMLIGHT Dirlight = NULL;

	// make light frame
	FullLightFrame = RLCreateFrame(scene);
	RealLightFrame = RLCreateFrame(scene);


	

	// make full ambient light
	
	if(FAILED(lpD3DRM->CreateLightRGB(D3DRMLIGHT_AMBIENT, D3DVAL(1.0),
                          D3DVAL(1.0), D3DVAL(1.0), &FullAmblight)))
        goto generic_error;



	// make real ambient light
	// create directional light
	
    switch (GameStates.CurrentLevel) 
    {
    case Trainer:
 	   if(FAILED(lpD3DRM->CreateLightRGB(D3DRMLIGHT_AMBIENT, 
         D3DVAL(0.7), D3DVAL(0.7), D3DVAL(0.7), &RealAmblight)))
           goto generic_error;
      if(FAILED(lpD3DRM->CreateLightRGB(D3DRMLIGHT_DIRECTIONAL, 
          D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0), &Dirlight)))
           goto generic_error;
       break;
    case Mojave:
 	   if(FAILED(lpD3DRM->CreateLightRGB(D3DRMLIGHT_AMBIENT, 
         D3DVAL(0.7), D3DVAL(0.7), D3DVAL(0.7), &RealAmblight)))
           goto generic_error;
       if(FAILED(lpD3DRM->CreateLightRGB(D3DRMLIGHT_DIRECTIONAL, 
          D3DVAL(1.0), D3DVAL(0.25), D3DVAL(0.1), &Dirlight)))
           goto generic_error;
       break;
    case Rockies:
 	   if(FAILED(lpD3DRM->CreateLightRGB(D3DRMLIGHT_AMBIENT, 
         D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0), &RealAmblight)))
           goto generic_error;
       if(FAILED(lpD3DRM->CreateLightRGB(D3DRMLIGHT_DIRECTIONAL, 
          D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0), &Dirlight)))
           goto generic_error;
       break;
    case Hawaii:
 	   if(FAILED(lpD3DRM->CreateLightRGB(D3DRMLIGHT_AMBIENT, 
         D3DVAL(0.8), D3DVAL(0.8), D3DVAL(0.8), &RealAmblight)))
           goto generic_error;
       if(FAILED(lpD3DRM->CreateLightRGB(D3DRMLIGHT_DIRECTIONAL, 
          D3DVAL(1.0), D3DVAL(0.5), D3DVAL(0.0), &Dirlight)))
           goto generic_error;
       break;
    case SanFrancisco:
 	   if(FAILED(lpD3DRM->CreateLightRGB(D3DRMLIGHT_AMBIENT, 
         D3DVAL(0.6), D3DVAL(0.6), D3DVAL(0.6), &RealAmblight)))
           goto generic_error;
       if(FAILED(lpD3DRM->CreateLightRGB(D3DRMLIGHT_DIRECTIONAL, 
          D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0), &Dirlight)))
           goto generic_error;
       break;
    case NewYork:
 	   if(FAILED(lpD3DRM->CreateLightRGB(D3DRMLIGHT_AMBIENT, 
         D3DVAL(0.7), D3DVAL(0.7), D3DVAL(0.7), &RealAmblight)))
           goto generic_error;
       if(FAILED(lpD3DRM->CreateLightRGB(D3DRMLIGHT_DIRECTIONAL, 
          D3DVAL(1.0), D3DVAL(0.25), D3DVAL(0.0), &Dirlight)))
           goto generic_error;
       break;
    case Tokyo:
 	   if(FAILED(lpD3DRM->CreateLightRGB(D3DRMLIGHT_AMBIENT, 
         D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0), &RealAmblight)))
           goto generic_error;
       if(FAILED(lpD3DRM->CreateLightRGB(D3DRMLIGHT_DIRECTIONAL, 
          D3DVAL(0.0), D3DVAL(0.0), D3DVAL(0.0), &Dirlight)))
           goto generic_error;
       break;
    }
     if (FAILED(FullLightFrame->SetOrientation(scene, 
        D3DVAL(0.5), D3DVAL(1.0), D3DVAL(1.0), D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0)))) // set light's orientation
        goto generic_error;

    if (FAILED(RealLightFrame->AddLight(RealAmblight))) // add light to the frame
        goto generic_error;
	

    RealAmblight->Release;

    
    if (FAILED(RealLightFrame->AddLight(Dirlight)))
        goto generic_error;


    if (FAILED(FullLightFrame->AddLight(FullAmblight))) // add light to the frame
        goto generic_error;
	

    FullAmblight->Release;
	Dirlight->Release;

	if (detail == 5){								//directional light on 
		bLightsOn = TRUE;
		scene->AddChild(RealLightFrame);			// add frame to the scene 
		behindthescene->AddChild(FullLightFrame);	// add frame to the scene 
	}
	else {
		bLightsOn = FALSE;							// directional light off
		scene->AddChild(FullLightFrame);			// add frame to the scene 
		behindthescene->AddChild(RealLightFrame);	// add frame to the scene 
	}



	return TRUE;

generic_error:
    Dirlight->Release;
	RealAmblight->Release;
	FullAmblight->Release;
	Msg("There is one error in creating scene");
	return FALSE;
}


BOOL
BuildScene(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
           LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera)
{
	char   datname[127];
	FILE   *shithead;
	static LPTEXTURESTRUCT lpDustTexStruct;
	int ZapIndex;
	int SnowballIndex;
   

   if (VSize < 4)      // non-fullscreen
      view->SetField(0.5 * 0.75 * (GWinSize[RMode-1][VSize-1].right - GWinSize[RMode-1][VSize-1].left) / (GWinSize[RMode-1][VSize-1].bottom - GWinSize[RMode-1][VSize-1].top));
   else                 // fullscreen
      view->SetField(0.5 * 0.75 * (VM_W3D) / (VM_H3D));

   /*
   if (GameStates.IsNetplay)
   {
	  int i;
      GameStates.IsNetplay = FALSE;
      for (i=0;i<100000;i++) 
      {
         if (!QHNetPlayWaitConnect())
	      {
		      GameStates.IsNetplay = TRUE;
            break;
	      }
      }
   }
   */

	//Add by Eric 11/12/96
	//Waiting for another player setup !
	if (GameStates.IsNetplay && (!beSynchronous))
	{

      
      //It's temporary
		int    Robotselected = 0, monsterselected = 1;
		DWORD  starttime;
		BOOL   ret;

		
		starttime = GetTickCount();

		if (!isHost) 
		{
			//send level monster selected to Host
			sendDWORD((DWORD)monsterselected);

			//timeout is one second
			while (ret = isNotTimeout(starttime, 60000))
			{
				if (receiveDWORD((LPDWORD)(&Robotselected)))
					break;
				sendDWORD((DWORD)monsterselected);
			}

		}
		else
		{
			while (ret = isNotTimeout(starttime, 60000))
			{
				if (receiveDWORD((LPDWORD)(&monsterselected)))
					break;
			}

			//send which Robot Robot selected to Slave
			sendDWORD((DWORD)Robotselected);
		}

		if (!ret)
			DestroyWindow(BYMainHwnd);

		beSynchronous = TRUE;
	}//end of if (GameStates.IsNetplay && (!beSynchronous))
	if (GameStates.IsNetplay)
	{
		//isSelectedCharacter = TRUE;
		if (isHost)
		{
			//show picture waiting for monster
			EventSndBuf.MsgId = NEW_MSG;
			EventSndBuf.Event = EVENT_WHICHRobot;
			EventSndBuf.Param = (WORD)GameStates.CurrentRobot;
		}
		else
		{
			//show picture waiting for Robot
			EventSndBuf.MsgId = NEW_MSG;
			EventSndBuf.Event = EVENT_LEVEL;
			EventSndBuf.Param = (WORD)GameStates.CurrentLevel;
		}
	}
	//Only when the two players are all selected character.
	/*
   if (GameStates.IsNetplay)
	{
		if (isOpponentSend == FALSE)
		{
			return FALSE;
		}

		isOpponentSend = FALSE;
	}
   */
	isOpponentSend = FALSE;

	if (GameStates.IsNetplay || PlayAsMonster)
	{
		GameStates.CurrentSubmonster = Beta;
	}
	//end of Eric



	behindthescene = RLCreateFrame(NULL);
	Wdevice = dev;
	Wscene  = scene;
	Wcamera = camera;
	Wview   = view;
	
	// only create light if hardware accelerated*/
	//if (d3dappi.ThisDriver.bIsHardware){    

	//create light for any situation (directional light on f1 toggle)
		if (!InitLight(dev, view, scene, camera))
			return FALSE;
	//}

	InitSprites();
	InitAE();

	if(!InitRobotMotionEngine())
        goto generic_error;
	if(!InitRobotAnimationEngine())
        goto generic_error;
	if( !InitMonsterMotionEngine() )
        goto generic_error;
	if( !InitMonsterAnimationEngine() )
        goto generic_error;

    Robotframe=RLCreateFrame(Wscene);
	monstframe=RLCreateFrame(Wscene);
	Mexplode=RLCreateFrame(behindthescene);
	Monsplode=RLCreateFrame(behindthescene);


	InitClockworkGod();

	//Load altitude map
	strcpy(whereincode, "load altitude map"); 
	LoadMap(GameStates.CurrentLevel);

	//Set background (fog) color
	strcpy(whereincode, "set background"); 
	SetBackground(GameStates.CurrentLevel);
   SetupBackground();

	//Init Scrolly Background 
//	strcpy(whereincode, "init scrolly background"); 
//	BuildScrollScene(dev, view, scene, camera);

	//Setup constants for Robot and monster
	strcpy(whereincode, "setup constants"); 
	sprintf(datname,"%s\\robmov%d.dat",DatPath,GameStates.CurrentRobot+1);
	shithead=fopen(datname,"rt");
	if(shithead)
		GetRobotMovementInfo(shithead);
	if(shithead)
		fclose(shithead);
	DefineRobotMotionConstants();

	RobotSpeed      = RLVal(0.0);
	RobotYSpeed     = RLVal(0.0);
	RobotVelocity.x = RLVal(0.0);
	RobotVelocity.y = RLVal(0.0);
	RobotVelocity.z = RLVal(0.0);
	RobotMovementState=RobotAirborne;

	sprintf(datname,"%s\\robani%d.dat",DatPath,GameStates.CurrentRobot+1);
	shithead=fopen(datname,"rt");
	if(shithead)
		GetRobotAnimInfo(shithead);
	if(shithead)
		fclose(shithead);
	DefineRobotAnimationConstants();


	strcpy(whereincode, "create Robot/monstspew frames"); 
	monstspew = RLCreateFrame(behindthescene);
    Robotspew = RLCreateFrame(behindthescene);
	
	//Make Robot homers
	strcpy(whereincode, "make Robot homers"); 
	memset(&Robotzaptex, 0, sizeof(TEXTURESTRUCT));
	MyLoadTexture(dev, ConstructRobotName(GameStates.CurrentRobot, "zap.bmp"), &Robotzaptex, 4);
	ZapIndex = LoadIntoDList(ConstructRobotName(GameStates.CurrentRobot, "zap.x"), Robotspew, &Robotzaptex, "Transparent");
	DeleteBinary (allmiscdlists[ZapIndex]->builder);
	allmiscdlists[ZapIndex]->builder=NULL;

	//Make monster zappers
	strcpy(whereincode, "make monster zappers"); 
	monstspewdata.zucchini = CreateZap(monstspew);
	monstspewdata.FarEnd.x=RLVal(0);
	monstspewdata.FarEnd.y=RLVal(0);
	monstspewdata.FarEnd.z=RLVal(7);
	monstspewdata.WhatDamage=0;
	monstspewdata.zucchini->active = 1;
	monstspewdata.zucchini->plane->active = 1;

	//Make Robot sparkliesx
	strcpy(whereincode, "make Robot sparklies"); 
	MakeExplosion(&Robotexplosion, Mexplode, Wcamera);
	MXdata.plasm=Robotexplosion;
//	MonXdata.plasm=monsterexplosion;
//	RLFrameAddCallback(Robotframe,movePlane,(void*)monstframe);
	Robotframe->AddMoveCallback(movePlane,(void*)monstframe); 

	//Init Watchy
	strcpy(whereincode, "create camera info"); 
	CreateCameraInfo(&camerastuff, Robotframe, monstframe);

	//Make Robot shield
	strcpy(whereincode, "make Robot shield"); 
	RobotBlockSphere=RLCreateFrame(behindthescene);
	memset(&shieldtex, 0, sizeof(TEXTURESTRUCT));
	MyLoadTexture(dev, 
      ConstructRobotName(GameStates.CurrentRobot, 
      (d3dapprs.transparency == FANCY || d3dapprs.transparency == SEMIFANCY || d3dapprs.transparency == TRANSLUCENT ?
      "shlt.bmp" : "shld.bmp")),
      &shieldtex, 4);
	shielddlist = LoadIntoDList("shield.x",RobotBlockSphere, &shieldtex, "make transparent");
	DeleteBinary (allmiscdlists[shielddlist]->builder);
	allmiscdlists[shielddlist]->builder=NULL;

	//Make dust clouds
	strcpy(whereincode, "make dust clouds");
   lpDustTexStruct = LQHCreateTexture(Wdevice, ConstructLevelName("dusts.bmp"), 4);
	makedust(&Robotdust, Robotframe, Wcamera, &lpDustTexStruct);					//  +++ ADDED for PSYSTEM.C
	makedust(&monstdust, monstframe, Wcamera, &lpDustTexStruct);					//  +++ ADDED for PSYSTEM.C

	//Make Robot sprite weapons
	strcpy(whereincode, "make Robot sprite weapons"); 
	CreateSixPeaAndCussinShooter(&SixShooter, &PeaShooter, 
	   &Cussin, Wscene, 
      (d3dapprs.transparency == FANCY || d3dapprs.transparency == SEMIFANCY || d3dapprs.transparency == TRANSLUCENT ?
      "200t.bmp" : "200.bmp"));

	//Make some monster weapon for specific level
	strcpy(whereincode, "make some monster sprite weapons"); 
	if (GameStates.CurrentLevel==NewYork) 
	{
		CreateSonicShooter(&NeallothRings,Wscene,"lnnering.bmp");
		NeallothRings->active=2;
    } else if ((GameStates.CurrentLevel==Tokyo)) 
	{
		BombSphere=RLCreateFrame(behindthescene);
		memset(&blasttex, 0, sizeof(TEXTURESTRUCT));
		MyLoadTexture(dev, "ltganuke.bmp", &blasttex, 4);
		shielddlist = LoadIntoDList("shield.x",BombSphere, &blasttex, NULL);
		DeleteBinary (allmiscdlists[shielddlist]->builder);
		allmiscdlists[shielddlist]->builder=NULL;
	} else if ((GameStates.CurrentLevel==Rockies)) 
	{

		BombSphere=RLCreateFrame(behindthescene);
		memset(&snoballtex, 0, sizeof(TEXTURESTRUCT));
		MyLoadTexture(dev, ConstructLevelName("snobal.bmp"), &snoballtex, 1);
		SnowballIndex=LoadIntoDList("snoball.x", BombSphere, &snoballtex, NULL);
		DeleteBinary (allmiscdlists[SnowballIndex]->builder);
		allmiscdlists[SnowballIndex]->builder=NULL;
	}
	Cussin->active=2;
    SixShooter->active=2;

	//Place Robot
	strcpy(whereincode, "place Robot"); 
	PlaceRobot(GameStates.CurrentLevel);

	//Make cars
	//strcpy(whereincode, "make cars"); //Rem by Eric 11/12/96
	//MakeCars();						//Rem by Eric 11/12/96

	//Add by Eric 11/12/96
	if (!GameStates.IsNetplay)
	{
		strcpy(whereincode, "make cars"); 
		MakeCars();
	}
	//end of Eric

	//Init landscape
	init_iland(camera, scene);
	strcpy(whereincode, "init landscape"); 
	BuildLandScene(dev, view, scene, camera);

	//Init buildings 
	strcpy(whereincode, "init buildings"); 
	Building_Init(GameStates.CurrentLevel, dev, view, scene, camera);
	
	//Init monster soul sprite
	strcpy(whereincode, "init monster soul sprite, Called by ICHARS!"); 
	SpiritInit();

	//BSH add it in 9/2 !
	strcpy(whereincode, "load monster animations"); 
	LoadMonsterAnimations();

	//Place monster
	strcpy(whereincode, "place monster"); 
    PlaceMonster(GameStates.CurrentLevel, 1);	// must follow Building_Init() and InitConflagration()
	
	strcpy(whereincode, "load Robot animations"); 
	LoadRobotAnimations();

	//Init hotspots
	strcpy(whereincode, "Init hotspots"); 
	InitRobotHotSpots();
	InitMonsterHotSpots();

	bAskQuit=FALSE;
   NextLevel = 0;

	//Init Scrolly Background 
	//strcpy(whereincode, "init scrolly background"); 
	//BuildScrollScene(dev, view, scene, camera);

	return TRUE;
generic_error:
    BYDumpInfo("There is one error in building scene");
	return FALSE;
}

void ClearupKeyDownMessage()
{
   MSG msg;
   int Flag = 1;

   do 
   {
      if (PeekMessage(&msg,NULL,WM_KEYDOWN,WM_KEYDOWN,PM_REMOVE) == FALSE)
		  Flag = 0;
   } while (Flag);
}

void ClearupKeyUpMessage()
{
   MSG msg;
   int Flag = 1;

   do 
   {
      if (PeekMessage(&msg,NULL,WM_KEYUP,WM_KEYUP,PM_REMOVE) == FALSE)
		  Flag = 0;
   } while (Flag);
}



static void ObliterateModel(RLFrame parent)
{
	RLFrame* kids;
	int numkids;
	int i;

	RLFrameGetChildren(parent,&numkids,&kids);
	for(i=0;i<numkids;++i)
	{
		parent->DeleteChild(kids[i]);
	}

	if (numkids) RLFree(kids);
}

void ShitOut(char *out)
{
	//FILE *shithead;
   //shithead = fopen("shit.out","a");
	//fprintf(shithead,out);
	//fclose(shithead);
}

#pragma optimize( "", off)
BOOL CleanupGame3DPart()
{
	HRESULT rval;
   LPDIRECTDRAWSURFACE2 lpSurf2;

   rval = 
      d3dappi.lpBackBuffer->QueryInterface(IID_IDirectDrawSurface2, (LPVOID *)&lpSurf2);

   if(rval == DD_OK)
   {
      while (d3dappi.lpBackBuffer->GetBltStatus(DDGBS_ISBLTDONE) == DDERR_WASSTILLDRAWING)
         ;
      // Page Unlock
      rval = lpSurf2->PageUnlock(0);
   }
   if (lpSurf2) { lpSurf2->Release(); lpSurf2 = NULL; }

ShitOut("Inside CleanupGame3DPart\n");
	//Add by Eric 11/14/96
	if (GameStates.IsNetplay)
	{
		beSynchronous = FALSE;
		//isSelectedCharacter = FALSE;
		isIn3DGame = FALSE;
		*InputIntPtr = 0;
	}
	//end of Eric

	//clear Robot animations 
	strcpy(whereincode, "clear Robot animations"); 
ShitOut(whereincode);
ShitOut("\n");

	ClearRobotAnimations();
	
	//clear monster animations
	strcpy(whereincode, "clear monster animations"); 
ShitOut(whereincode);
ShitOut("\n");
	ClearMonsterAnimations();

	//remove callbacks 
	strcpy(whereincode, "remove callbacks"); 
ShitOut(whereincode);
ShitOut("\n");
	Robotframe->DeleteMoveCallback (dustcloud, (void*)Robotdust); 
	monstframe->DeleteMoveCallback (dustcloud, (void*)monstdust); 


	//destroy buildings 
	strcpy(whereincode, "destroy buildings"); 
ShitOut(whereincode);
ShitOut("\n");
	DelBuilding();

	//destroy conflagration for buildings 
	strcpy(whereincode, "destroy conflagration"); 
ShitOut(whereincode);
ShitOut("\n");
	DestroyConflagration();

	//DestroyAllParticleSystems
	strcpy(whereincode, "DestroyAllParticleSystems"); 
ShitOut(whereincode);
ShitOut("\n");
	DestroyAllParticleSystems();

	//DestroyAllCxSprites
	strcpy(whereincode, "DestroyAllCxSprites"); 
ShitOut(whereincode);
ShitOut("\n");
	DestroyAllCxSprites();

	//DestroyMiscDLists 
	strcpy(whereincode, "DestroyMiscDLists"); 
ShitOut(whereincode);
ShitOut("\n");
	DestroyMiscDLists();

	//DestroyJets 
//	strcpy(whereincode, "DestroyJets"); 
// 	DestroyJets();

	//DestroyDLists
	strcpy(whereincode, "DestroyDLists"); 
ShitOut(whereincode);
ShitOut("\n");
	DestroyDLists();

	//free all trees and poles
	strcpy(whereincode, "Destroy all trees and poles"); 
ShitOut(whereincode);
ShitOut("\n");
	FreeTreesPoles();

	//remove children of Robotframe
	strcpy(whereincode, "remove children of Robotframe"); 
ShitOut(whereincode);
ShitOut("\n");
	//ObliterateModel(Robotframe);

	if(ZappaOnScreen)
	{
		ZappaOnScreen = 0;
		behindthescene->AddChild(monstspew);

//		RLFrameAddChild(behindthescene, monstspew);
//	RLFrameRemoveCallback(frame, NewZappaCallBack, arg);
	}


	//remove children of monstframe
	strcpy(whereincode, "remove children of monstframe"); 
ShitOut(whereincode);
ShitOut("\n");
	//ObliterateModel(monstframe);

	//destroy camera callback, free camera info
	DestroyCameraInfo(&camerastuff);
	Wcamera->SetVelocity(Wscene, (float)0, (float)0, (float)0, FALSE);

	//remove more callbacks
	strcpy(whereincode, "remove more callbacks"); 
ShitOut(whereincode);
ShitOut("\n");
	Robotframe->DeleteMoveCallback (movePlane, (void*)monstframe); 

	//remove landscape
	strcpy(whereincode, "remove the landscape"); 
ShitOut(whereincode);
ShitOut("\n");
	DestroyILand();

	//remove scrolly background
	//strcpy(whereincode, "remove the scrolly background"); 
	//DestroyIScroll();

	strcpy(whereincode,"BootMonsterFrames");
ShitOut(whereincode);
ShitOut("\n");
	BootAllMonsterFrames();

	strcpy(whereincode,"BootRobotFrames");
ShitOut(whereincode);
ShitOut("\n");
	BootAllRobotFrames();


   NextLevel = 0;
ShitOut("losing light frames\n");
	MDFreeD3DFrame(RealLightFrame); // free light frame added by tim
	MDFreeD3DFrame(FullLightFrame); // free light frame added by tim
ShitOut("losing Monstspew\n");

 	MDFreeD3DFrame(monstspew);
ShitOut("losing Robotspew\n");
   MDFreeD3DFrame(Robotframe);
ShitOut("losing Monstframe\n");
    MDFreeD3DFrame(monstframe);
ShitOut("losing BehindTheScene\n");
    
	MDFreeD3DFrame(behindthescene);
ShitOut("losing map\n");
	FreeMap();
ShitOut("losing Turing Engines\n");

   DestroyRobotAnimationEngine();
   DestroyRobotMotionEngine();
   DestroyMonsterAnimationEngine();
   DestroyMonsterMotionEngine();
ShitOut("Returning from  CleanupGame3DPart\n\n");

	return TRUE;
}
#pragma optimize( "", on)


char SecretCodeBuffer[16];      
short SCodeIdx = 0;
char pSecretCodeArray[][16] = 
{
   "POWER",                                // 0
   "OWQUITIT",                             // 1
   "YOUTWIT",                              // 2
   "YOUPYRO",                              // 3
   "WIPEOUT",                              // 4
    "POWERUP",                              // 5
   "WOOPITUP",                             // 6
   "TRIPWIRE",                             // 7
   "WETPIPE",                              // 8
   "TRIPPERROPER",							// 9
   "QUIETRIOT",                            // 10
   "QUEERPOWER",                           // 11
   "TIEUPYOURPUPPY",                       // 12
   "TIREOUT",                              // 13 
   "TOWEROPOWER",                          // 14
   "WEIRTRIPPER",                          // 15
   "TRIPOUT",                              // 16
   "POURPOORPORE",                         // 17
   "TRYTOWRITEIT",                         // 18
   "POWERTIE",                             // 19
   "TYPEWRITER",                           // 20
   "TOERR",                                // 21
   "POTPOURRI",                            // 22
   "POWWOW",                               // 23
   "IOU",                                  // 24
   "YUPPYPYRE",                            // 25
   "POURITOUT",                            // 26
   "EWYUQ"                                 // 27
};
     
void BYOBCleanSBuffer(void)
{
   SecretCodeBuffer[0] = 0;
   SCodeIdx = 0;
}
 
void BYOBGetSecretCode(DWORD wparam)
{
   if (wparam<65 || wparam>90 || SCodeIdx>=15)
      return;

   SecretCodeBuffer[SCodeIdx++] = (char)wparam;
   SecretCodeBuffer[SCodeIdx] = 0;
}

void BYOBSetSecretCode(void)
{
   if (!strcmp(pSecretCodeArray[0], SecretCodeBuffer)) {	//POWER
      monthink++;
      if (monthink>1) monthink=0;
   }
   if (!strcmp(pSecretCodeArray[1], SecretCodeBuffer)) {   //OWQUITIT
      if (sporehunt) sporehunt = 0;
         else sporehunt = 1;
   }
   if (!strcmp(pSecretCodeArray[2], SecretCodeBuffer)) {   //YOUTWIT
      SwapRobotNMonster(1);
   }
   if (!strcmp(pSecretCodeArray[3], SecretCodeBuffer)) {   //YOUPYRO
      SwapRobotNMonster(0);
   }
   if (!strcmp(pSecretCodeArray[4], SecretCodeBuffer)) {   //WIPEOUT
      MnstLife=0;
      MonsterData.collisionflag=1;
      MonsterData.DamageIveTaken=100;
      MonsterData.CollisionVector.x=RLVal(1.0);
      MonsterData.CollisionVector.y=RLVal(0.0);
      MonsterData.CollisionVector.z=RLVal(0.0);
    }
   if (!strcmp(pSecretCodeArray[7], SecretCodeBuffer)) {   //TRIPWIRE
      RobotLife=0;
      RobotData.collisionflag=1;
      RobotData.DamageIveTaken=100;
      RobotData.CollisionVector.x=RLVal(0.01);
      RobotData.CollisionVector.y=RLVal(0.1);
      RobotData.CollisionVector.z=RLVal(0.0);
    }
    if (!strcmp(pSecretCodeArray[5], SecretCodeBuffer)) {   //POWERUP
        MnstEngy=65535;
    }
    if (!strcmp(pSecretCodeArray[15], SecretCodeBuffer)) {  //WEIRTRIPPER
        sporehunt=2;
    }
    if (!strcmp(pSecretCodeArray[27], SecretCodeBuffer)) {  //EWYUQ
        MeltAMonster(1);
    }
//	if (!strcmp(pSecretCodeArray[18], SecretCodeBuffer)) {	//TRYTOWRITEIT
//		ScreenCaptureFlag = !ScreenCaptureFlag;
//	}
	if ((PlayerHasWon) && 
      (!strcmp(pSecretCodeArray[25], SecretCodeBuffer))) {			//YUPPYPYRE
      SwapRobotNMonster(0);
      PlayAsMonster=TRUE;
   }
   if (!strcmp(pSecretCodeArray[19], SecretCodeBuffer)) {  //POWERTIE
      RobotEngy=65535;
   }
	// Tim's frame rate meter toggle (typewriter)
   if (!strcmp(pSecretCodeArray[20], SecretCodeBuffer)) {  //TYPEWRITER
      bFrameMeter = !bFrameMeter;
   }
   if (!strcmp(pSecretCodeArray[8], SecretCodeBuffer)) {  //WETPIPE
      wetpipe = !wetpipe;
   }
 
}
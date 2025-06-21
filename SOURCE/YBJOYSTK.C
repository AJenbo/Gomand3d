//*******************************************************************
// ybjoystk.c
//
// Copyright 1996 by 47-TEK, INC.  All rights reserved.
//
// Author:	Bo Yuan
// 
// Date:	08/16/96
//
// Description:   This module contains a set of functions to control
//              joysticks in the game.	
//
// Side effects:
//
// Class:
//
// Function:
//		BOOL BYSetUpJoyStick(HWND win, UINT devnum);
//		void BYReleaseJoystick(void);
//		BOOL BYJoyMoveHandler(void);
// 
// Notes:
//
// Update:
//
// Date			Name			Description
// ==================================================================
//
//*******************************************************************
#ifdef MINIWIN
#include "miniwin/windows.h"
#else
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#endif
#include <mmddk.h>
#include <malloc.h>

#include "d3dappi.h"
#include "rmdemo.h"
#include "rmfull.h"
#include "wrapper.h"
#include "byglobal.h"
#include "d3code.h"
#include "ybmid.h"
#include "ybsnd.h"

#include "ybjoystk.h"
#include "camera.h"

#define YB_SHIFTBIT			 11
#define YB_JOY_XRANGE        5
#define YB_JOY_YRANGE        5
#define YB_JOY_ZRANGE        5

// since microsoft didn't define all these buttons as the way I want, so
// I redefine them below.
#define BYJOY_BUTTON1	0x000001
#define BYJOY_BUTTON2	0x000002
#define BYJOY_BUTTON3	0x000004
#define BYJOY_BUTTON4	0x000008
#define BYJOY_BUTTON5	0x000010
#define BYJOY_BUTTON6	0x000020
#define BYJOY_BUTTON7	0x000040
#define BYJOY_BUTTON8	0x000080
#define BYJOY_BUTTON9	0x000100
#define BYJOY_BUTTONa	0x000200

#define BYJOYERR_NOPULGED_OR_NODRIVER 1
#define BYJOYERR_DEVNUM_IS_TOO_BIGGER 1+BYJOYERR_NOPULGED_OR_NODRIVER
#define BYJOYERR_NOCANDO              1+BYJOYERR_DEVNUM_IS_TOO_BIGGER
#define BYJOYERR_CANTOPENKEY          1+BYJOYERR_NOCANDO
#define BYJOYERR_CANTGETOEMKEY        1+BYJOYERR_CANTOPENKEY
#define BYJOYERR_CANTGETHWCFG         1+BYJOYERR_CANTGETOEMKEY
#define BYJOYERR_CANTGETDEVCAPS       1+BYJOYERR_CANTGETHWCFG
#define BYJOYERR_NOTCALIBRATED         1+BYJOYERR_CANTGETDEVCAPS

#define BY_TOTALCAMERA  4

extern Caminfo* camerastuff;
short camorder[BY_TOTALCAMERA] =
{
	2,1,3,8
};

short JoyCurrentCam = 0;
short JoyCamCount = 0;

MMRESULT JoyStatus;
int JoyStickType;
static JOYINFOEX jix;
static char szErr[256];
DWORD xd0, yd0, zd0, rd0, bd0, hd0;
BOOL bFindJoystick=FALSE;
BOOL bUseGameProfile=FALSE;
long int NewJoyAction=0;
static long int oldJoyAction=0;

long int JoyActions[30];
//*******************************************************************
// Name:	int BYSetUpJoyStick (HWND win, UINT devnum)
//
// Description:   Detect to see if joystick driver is installed, 
//              get joystick calibration information, set X, Y center
//              coordinates, set capture for the joystick, also
//              detect to see if it is MS Sidewinder 3D Pro. 
//
// Arguments:	HWND win	... Window applications' handler
//             UINT devnum ... joystick number
//
// Return:	0    -- set up successfully
//				else -- set up fails
//
// Side effects:
//
// Notes:
//
// Known restrictions:
//	   1. Can only detect Microsoft SideWinder3D joystick and view
//       all the other joysticks as "normal" joysticks which have
//       two buttons only.  To detect other joysticks, need to 
//       know the joysticks' VxD name.
// 
// Update:
// Date			Name			Description
// ==================================================================
//
//*******************************************************************

int BYSetUpJoyStick (HWND win, UINT devnum)
{
	char err[127];
	PTCHAR ppName;
	DWORD temp1;
	DWORD temp2;
	//
	HKEY  hKey;
	DWORD dwcb;
	LPJOYREGHWCONFIG jhwc;
	TCHAR szKey[REGSTR_MAX_VALUE_LENGTH];
	TCHAR szValue[REGSTR_MAX_VALUE_LENGTH];
	TCHAR szOEMKey[REGSTR_MAX_VALUE_LENGTH];
	TCHAR szOEMName[REGSTR_MAX_VALUE_LENGTH];
	JOYCAPS jc;
	JOYINFOEX pji;
	LONG lr;

	int ErrorCase = 0;

	ppName = NULL;
	szOEMKey[0] = '\0';
   JoyStickType = YB_NO_JOYSTICK;
         
	memset(&pji, 0, sizeof(JOYINFOEX));
   pji.dwSize = sizeof(JOYINFOEX);
   JoyStatus=joyGetPosEx(devnum, &pji);
	if (JoyStatus==JOYERR_UNPLUGGED || JoyStatus==MMSYSERR_NODRIVER)
	{
		ErrorCase = BYJOYERR_NOPULGED_OR_NODRIVER;
		goto HasError;
	}
   else if (JoyStatus)
   {
		ErrorCase = BYJOYERR_NOPULGED_OR_NODRIVER;
		goto HasError;
   }

	if ((devnum+1)>joyGetNumDevs())
	{
		ErrorCase = BYJOYERR_DEVNUM_IS_TOO_BIGGER;
		goto HasError;
	}

	// Open .. HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\
	//         MediaResources\joystick\msjstick.drv<0001>\CurrentJoystickSettings
	memset(&jc, 0, sizeof(JOYCAPS));
	JoyStatus = joyGetDevCaps(devnum, &jc, sizeof(jc));
	if (JoyStatus != JOYERR_NOERROR)
	{
		ErrorCase = BYJOYERR_CANTGETDEVCAPS;
		goto HasError;
	}

	sprintf(szKey, 
			  "%s\\%s\\%s",
			  REGSTR_PATH_JOYCONFIG,
			  jc.szRegKey,
			  REGSTR_KEY_JOYCURR);

	if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, (LPTSTR)&szKey, 0, KEY_ALL_ACCESS, &hKey))
	{
		ErrorCase = BYJOYERR_CANTOPENKEY;
		goto HasError;
	}

	// Get OEM Key name to szOEMKey, and get HW configuration to jhwc. 
	dwcb = sizeof(szOEMKey);
	sprintf(szValue, "Joystick%d%s", devnum+1, REGSTR_VAL_JOYOEMNAME);
	lr = RegQueryValueEx(hKey, szValue, 0, 0, (LPBYTE)&szOEMKey, (LPDWORD)&dwcb);
	RegCloseKey(hKey);
	if (lr != ERROR_SUCCESS)
	{
		ErrorCase = BYJOYERR_CANTGETOEMKEY;
		goto HasError;
	}

	jhwc=(LPJOYREGHWCONFIG)malloc(sizeof(JOYREGHWCONFIG));

	if (jhwc==NULL)
	{
		ErrorCase = BYJOYERR_NOCANDO;
		goto HasError;
	}

   sprintf(szValue, REGSTR_VAL_JOYNCONFIG, devnum+1);
   dwcb = sizeof(JOYREGHWCONFIG);
	lr = RegQueryValueEx(hKey, szValue, 0, NULL, (LPBYTE)jhwc, (LPDWORD)&dwcb);
	if (lr != ERROR_SUCCESS)
	{
		free(jhwc);
		ErrorCase = BYJOYERR_CANTGETHWCFG;
		goto HasError;
	}

	// Open OEK Key from ..
	//         HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\
	//         MediaProperties\PrivateProperties\joystick\OEM\    + oemname.
	sprintf(szKey, "%s\\%s", REGSTR_PATH_JOYOEM, szOEMKey);
	lr = RegOpenKeyEx(HKEY_LOCAL_MACHINE, szKey, 0, KEY_ALL_ACCESS, &hKey);
	if (lr != ERROR_SUCCESS)
	{
		free(jhwc);
		ErrorCase = BYJOYERR_NOCANDO;
		goto HasError;
	}

	// Get OEM name 
	dwcb = sizeof(szValue);
	lr = RegQueryValueEx(hKey, 
			               REGSTR_VAL_JOYOEMNAME, 
								0, 0, (LPBYTE)szOEMName, (LPDWORD)&dwcb);
	if (lr != ERROR_SUCCESS)
	{
		free(jhwc);
		ErrorCase = BYJOYERR_NOCANDO;
		goto HasError;
	}

	// new below: added by Bo on 2/11/97
	// My study shows Microsoft has changed its VxD for SideWinder3D Pro to MSGAME.VXD and
	// it also used for SideWinder Game Pad, so it is no longer appropreiate to use that to
	// test the existance of SideWinder3D Pro or SideWinder Game Pad, therefore I added the 
	// code below to do the test.
	if (!strcmp(_strlwr(szOEMName), "microsoft sidewinder 3d pro"))
	{
		BYDumpInfo("Detected microsoft sidewinder 3d pro");
      JoyStickType = YB_SIDEWINDER_3D_PRO;
	}
	else
	if (!strcmp(_strlwr(szOEMName), "microsoft sidewinder game pad"))
	{
		BYDumpInfo("Detected microsoft sidewinder game pad");
		JoyStickType = YB_SIDEWINDER_GAMEPAD;
	}
	else
	if (!strcmp(_strlwr(szOEMName), "creative labs blaster gamepad"))
	{
		BYDumpInfo("Detected creative labs blaster gamepad");
		JoyStickType = YB_CREATIVE_GAMEPAD;
	}
   else
	if ((!strcmp(_strlwr(szOEMName), "gravis grip")) &&
		 (jc.wNumButtons==10))
	{
		BYDumpInfo("Detected gravis grip");
		JoyStickType = YB_GRAVIS_GRIP;
	}
	else
	{
		BYDumpInfo("Detected generic joystick");
		JoyStickType = YB_GENERIC;
	}
	// new above: 2/11/97

   if (!ErrorCase)
   {
      if (jhwc->hwv.dwCalFlags)
      {
         temp1 = jhwc->hwv.jrvHardware.jpMax.dwX - jhwc->hwv.jrvHardware.jpMin.dwX;
		   temp2 = jhwc->hwv.jrvHardware.jpCenter.dwX-jhwc->hwv.jrvHardware.jpMin.dwX;
		   xd0 = ((65535/temp1)*temp2)>>YB_SHIFTBIT;
		   temp1 = jhwc->hwv.jrvHardware.jpMax.dwY - jhwc->hwv.jrvHardware.jpMin.dwY;
		   temp2 = jhwc->hwv.jrvHardware.jpCenter.dwY-jhwc->hwv.jrvHardware.jpMin.dwY;
		   yd0 = ((65535/temp1)*temp2)>>YB_SHIFTBIT;
      }
      else
      {
         JoyStickType = YB_NO_JOYSTICK;
		   ErrorCase = BYJOYERR_NOTCALIBRATED;
		   goto HasError;
      }
		if (JoyStickType == YB_SIDEWINDER_3D_PRO)
		{
			rd0 = (65535/2)>>YB_SHIFTBIT;
			temp1 = jhwc->hwv.jrvHardware.jpMax.dwZ - jhwc->hwv.jrvHardware.jpMin.dwZ;
			temp2 = jhwc->hwv.jrvHardware.jpCenter.dwZ-jhwc->hwv.jrvHardware.jpMin.dwZ;
			zd0 = ((65535/temp1)*temp2)>>YB_SHIFTBIT;
		}
		//bd0 = //jhwc->hws.dwNumButtons;
		bd0 = jc.wNumButtons;
		if (JoyStickType == YB_SIDEWINDER_GAMEPAD ||
          JoyStickType == YB_CREATIVE_GAMEPAD ||
          JoyStickType == YB_GRAVIS_GRIP ||
			 JoyStickType == YB_SIDEWINDER_3D_PRO)
		{
			tpjoycfg = 0;
			total_joycfg = 1;
			current_joycfg = 0;
			BYChangeJoystkActions();
		}
		else
		if (bd0>=9)
		{
			tpjoycfg = 0;
			total_joycfg = 1;
			current_joycfg = 0;
			BYChangeJoystkActions();
		}
		else
		if (bd0<=2)
		{
			tpjoycfg = 0;
			total_joycfg = 10;
			current_joycfg = 0;
			BYChangeJoystkActions();
		}
		else // if not 4 button, use 2 btn actions as default.
		if (bd0<=4)
		{
			tpjoycfg = 0;
			total_joycfg = 3;
			current_joycfg = 0;
			BYChangeJoystkActions();
		}

		memset(&jix, 0x00, sizeof(JOYINFOEX));
		jix.dwSize = sizeof(JOYINFOEX);
		jix.dwFlags = JOY_RETURNALL;
		strcpy(szErr, "");

		joySetCapture(win, devnum, 1, TRUE);
      JoyStatus=JOYERR_NOERROR;   
		free(jhwc);		
		bFindJoystick = TRUE;
		OutputDebugString("Joystick ok\n");
		BYDumpInfo("Joystick ok\n");
      return(0);
   }

HasError:

   switch(ErrorCase)
	{
   case BYJOYERR_CANTGETDEVCAPS:
		strcpy(err, "\nCan't get device caps");
		break;
	case BYJOYERR_CANTGETHWCFG:
		strcpy(err, "\nCan't get hardware configuration information");
		break;
   case BYJOYERR_NOPULGED_OR_NODRIVER:
		strcpy(err, "\nThe device is either not pluged, or no driver for it");
      break;
   case BYJOYERR_DEVNUM_IS_TOO_BIGGER:
		strcpy(err, "\nThe device number is too bigger");
      break;
   case BYJOYERR_NOCANDO:
      strcpy(err, "\nCan't do it");
      break;
   case BYJOYERR_CANTOPENKEY:
      strcpy(err, "\nCan't open a key");
      break;
   case BYJOYERR_CANTGETOEMKEY:
      strcpy(err, "\nCan't get OEM key");
      break;
   case BYJOYERR_NOTCALIBRATED:
      strcpy(err, "\nJoystick not calibrated");
      break;
   }
	//MessageBox(NULL, err, "ERROR_NOTICE", MB_ICONEXCLAMATION|MB_OK);
	OutputDebugString(err);
	BYDumpInfo(err);
   return(ErrorCase);

}

//*******************************************************************
// Name:	BYReleaseJoystick(void)
//
// Description:	Release joystick capture only if the joystick is 
//              captured before. 
//
// Arguments:	void
//
// Return:		void	
//				
// Side effects:
//
// Notes:
//
// Known restrictions:
// 
// Update:
// Date			Name			Description
// ==================================================================
//
//*******************************************************************
void BYReleaseJoystick(void)
{
	if (JoyStatus!=JOYERR_NOERROR) 
   {
      return;
   }
	joyReleaseCapture(JOYSTICKID1);
}

static DWORD xd;	// joystick x pos
static DWORD yd;	// joystick y pos
static DWORD zd;	// joystick z pos
static DWORD rd;	// joystick rotation
static DWORD bd;	// joystick button
static DWORD hd;	// joystick POV value

//*******************************************************************
// Name:	BOOL BYJoyMoveHandler(HWND hwnd)
//
// Description:	Handle joystick input information, decide which 
//              action should be done next
//
// Arguments:	HWND hwnd ... Windows application handler
//
// Return:  TRUE ...  if the call success
//          FALSE ... if joystick is not set up correctly, or
//                    if joyGetPosEx call returns any error	
//				
// Side effects:
//
// Notes:
//		The remout part at the bottom can be used for debugging
//      when it is not in exclusive video mode.
//
// Known restrictions:
//		1.	joystick actions can be modified, but the index for the
//          actions is hardcoded.
//		2.	This function is for joystick1 only.
//		3.	joystick x,y,z,r,h values are shifted by 11, that value
//			is hardcoded, but is it reasonable for all kinds of
//			joysticks?
//		4.	YB_JOY_XRANGE and YB_JOY_YRANGE can also be modified,
//			but again what is the reasonable value?
// 
// Update:
// Date			Name			Description
// ==================================================================
//
//*******************************************************************
BOOL BYJoyMoveHandler(void)	// Windows application handler
{
   long int tempAction=0;

	ISPAGE(pg_SHOW_GAME_SCREEN);

	if ((JoyStatus!=JOYERR_NOERROR) || (bUseGameProfile)) 
   {	
      return FALSE;
   }

	NewJoyAction = 0;
	tempAction = 0;

	switch(joyGetPosEx(JOYSTICKID1, &jix)) 
   {
	   case JOYERR_NOERROR:
		   break;
	   case MMSYSERR_NODRIVER:
		   strcpy(szErr, "The joystick driver is not present.");
         BYDumpInfo(szErr);
		   return FALSE;
	   case MMSYSERR_INVALPARAM:
		   strcpy(szErr, "An invalid parameter was passed.");
         BYDumpInfo(szErr);
		   return FALSE;
	   case MMSYSERR_BADDEVICEID:
		   strcpy(szErr, "The specified joystick identifier is invalid.");
         BYDumpInfo(szErr);
		   return FALSE;
	   case JOYERR_UNPLUGGED:
		   strcpy(szErr, "Your joystick is unplugged.");
         BYDumpInfo(szErr);
		   return FALSE;
	   default:
		   strcpy(szErr, "Unknown joystick error.");
         BYDumpInfo(szErr);
		   return FALSE;
	}


	if (JoyStickType == YB_SIDEWINDER_3D_PRO) 
   {
		xd = (jix.dwXpos) >> YB_SHIFTBIT;
		yd = (jix.dwYpos) >> YB_SHIFTBIT;
		zd = (jix.dwZpos) >> YB_SHIFTBIT;
 		bd = (jix.dwButtons);

		rd = (jix.dwRpos) >> YB_SHIFTBIT;
		hd = (jix.dwPOV)/100;

		//tempAction = InputInt;

		if (bd & BYJOY_BUTTON1)  
      {
			tempAction|=JoyActions[4];
      }
		if (bd & BYJOY_BUTTON2) 
      { 
         tempAction|=JoyActions[5];
		}
		if (bd & BYJOY_BUTTON3)
		{
			tempAction|=JoyActions[6];
		}
		if (bd & BYJOY_BUTTON4)
		{
			tempAction|=JoyActions[7];
		}
		if (bd & BYJOY_BUTTON5)
		{
			tempAction|=JoyActions[8];
		}
		if (bd & BYJOY_BUTTON6)
		{
			tempAction|=JoyActions[9];
		}
		if (bd & BYJOY_BUTTON7)
		{
			tempAction|=JoyActions[10];
		}
		if (bd & BYJOY_BUTTON8)
		{
			tempAction|=JoyActions[11];
		}

		if ((!(hd > 360)) && (camerastuff!=NULL))
		{
			//tempAction|=JoyActions[16];
			if (((hd <=45) && (hd >= 0)) || 
				 ((hd > 315) && (hd <= 360)))
			{
				// use camera 6
				JoyCurrentCam = 6;
				if (JoyCurrentCam != JoyCamCount)
				{
					JoyCamCount = JoyCurrentCam;
					camerastuff->method=SLUGDRIFT;
					camerastuff->zone=3;
					ResetCameraTarget(camerastuff);
				}
			}
			else
			if ((hd > 45) && (hd <= 135))
			{
				// use right camera = 4
				JoyCurrentCam = 4;
				if (JoyCurrentCam != JoyCamCount)
				{
					JoyCamCount = JoyCurrentCam;
					camerastuff->method=SLUGDRIFT;
					camerastuff->zone=7;
					ResetCameraTarget(camerastuff);
				}
			}
			else
			if ((hd <= 225) && (hd > 135))
			{
				// use camera 3
				JoyCurrentCam = 3;
				if (JoyCurrentCam != JoyCamCount)
				{
					JoyCamCount = JoyCurrentCam;
					camerastuff->method=SLUGDRIFT;
					camerastuff->zone=4;
					ResetCameraTarget(camerastuff);
				}
			}
			else
			if ((hd > 225) && (hd <= 315))
			{
				// use left camera = 5
				JoyCurrentCam = 5;
				if (JoyCurrentCam != JoyCamCount)
				{
					JoyCamCount = JoyCurrentCam;
					camerastuff->method=SLUGDRIFT;
					camerastuff->zone=8;
					ResetCameraTarget(camerastuff);
				}
			}
		}
		else if (camerastuff!=NULL)
		{
			// use default camera = 2
			JoyCurrentCam = 0;
			if (JoyCurrentCam != JoyCamCount)
			{
				JoyCamCount = JoyCurrentCam;
				camerastuff->method=SLUGDRIFT;
				camerastuff->zone=2;
				ResetCameraTarget(camerastuff);
			}
		}

		if (rd > (rd0+YB_JOY_XRANGE))
      {
         tempAction|=JoyActions[2];
      }

		if (rd < (rd0-YB_JOY_XRANGE)) 
      {
         tempAction|=JoyActions[0];
      }

		if (xd > (xd0+YB_JOY_XRANGE+5)) 
      {
			tempAction|=JoyActions[13];
      }

		if (xd < (xd0-YB_JOY_XRANGE-5)) 
      {
			tempAction|=JoyActions[12];
      }

		if (yd < (yd0-YB_JOY_YRANGE)) 
      {
			if (zd < (zd0-YB_JOY_ZRANGE))
			{
				tempAction|=JoyActions[15]; // fly
			}
			else
			if (zd > (zd0+YB_JOY_ZRANGE))
			{
				tempAction|=JoyActions[1];  // walk
			}
			else 
			{
				tempAction|=JoyActions[14]; // run
			}
      }

		if (yd > (yd0+YB_JOY_YRANGE)) 
      {
         tempAction|=JoyActions[3];
      }


		if (tempAction!=0) 
      {
			NewJoyAction = tempAction;
			oldJoyAction = tempAction;
		}
	} 
   else 
   { 
		xd = (jix.dwXpos) >> YB_SHIFTBIT;
		yd = (jix.dwYpos) >> YB_SHIFTBIT;
		bd = (jix.dwButtons);

		//tempAction = InputInt;
		if ((JoyStickType == YB_SIDEWINDER_GAMEPAD) || (JoyStickType == YB_CREATIVE_GAMEPAD))
		{
			// For this specific input device, its button labels
			// for BYJOY_BUTTON? are in the order of:
			// A, B, C, X, Y, Z, Left, Right, M, Start
			if ((bd & BYJOY_BUTTON1) && (bd & BYJOY_BUTTON2))
			{
				tempAction|=JoyActions[15];
			}
			else
			if ((bd & BYJOY_BUTTON2) && (bd & BYJOY_BUTTON3))
			{
				tempAction|=JoyActions[14];
			}
			else
			{
				if (bd & BYJOY_BUTTON1)
				{
					tempAction|=JoyActions[4];
				}

				if (bd & BYJOY_BUTTON2) 
				{ 
					tempAction|=JoyActions[5];
				}
			}

			if (bd & BYJOY_BUTTON3)
			{
				tempAction|=JoyActions[6];
			}
			if (bd & BYJOY_BUTTON4)
			{
				tempAction|=JoyActions[7];
			}
			if (bd & BYJOY_BUTTON5)
			{
				tempAction|=JoyActions[8];
			}
			if (bd & BYJOY_BUTTON6)
			{
				tempAction|=JoyActions[9];
			}
			if (bd & BYJOY_BUTTON7)
			{
				tempAction|=JoyActions[10];
			}
			if (bd & BYJOY_BUTTON8)
			{
				tempAction|=JoyActions[11];
			}

			if (bd & BYJOY_BUTTON9)
			{
				short rcam;
				JoyCamCount++;
				if (JoyCamCount>5)
				{
					JoyCamCount = 0;
					JoyCurrentCam++;
					JoyCurrentCam = JoyCurrentCam % BY_TOTALCAMERA;
					rcam = camorder[JoyCurrentCam];
					switch(rcam)
					{
					case 1:
						camerastuff->method=POV;
						//if (!level) YBSetSubTitle1(Vmode, "WATCHY FIRST-PERSON", RGB(0, 255, 0));
						ResetCameraTarget(camerastuff);
						break;
					case 2:
						camerastuff->method=SLUGDRIFT;
						camerastuff->zone=2;
						//if (!level) YBSetSubTitle1(Vmode, "WATCHY OVER THE SHOULDER", RGB(0, 255, 0));
						ResetCameraTarget(camerastuff);
						break;
					case 3:
						camerastuff->method=SLUGDRIFT;
						camerastuff->zone=4;
						//if (!level) YBSetSubTitle1(Vmode, "WATCHY HIGH OVER THE SHOULDER", RGB(0, 255, 0));
						ResetCameraTarget(camerastuff);
						break;
					case 8:
						camerastuff->method=SLUGDRIFT;
						camerastuff->zone=6;
						//if (!level) YBSetSubTitle1(Vmode, "WATCHY AERIAL", RGB(0, 255, 0));
						ResetCameraTarget(camerastuff);
						break;
					default:
						break;
					};
				}
			//	tempAction|=JoyActions[12];
			}
			//if (bd & BYJOY_BUTTONa)
			//{
			//	tempAction|=JoyActions[13];
			//}
		}
      else if (JoyStickType == YB_GRAVIS_GRIP)
		{
			// For this specific input device, its button labels
			// for BYJOY_BUTTON? are in the order of:
			// A, B, C, X, Y, Z, Left, Right, M, Start
			if ((bd & BYJOY_BUTTON1) && (bd & BYJOY_BUTTON2))
			{
				tempAction|=JoyActions[15];
			}
			else
			if ((bd & BYJOY_BUTTON2) && (bd & BYJOY_BUTTON3))
			{
				tempAction|=JoyActions[14];
			}
			else
			{
				if (bd & BYJOY_BUTTON1)
				{
					tempAction|=JoyActions[4];
				}

				if (bd & BYJOY_BUTTON2) 
				{ 
					tempAction|=JoyActions[5];
				}
			}

			if (bd & BYJOY_BUTTON3)
			{
				tempAction|=JoyActions[6];
			}
			if (bd & BYJOY_BUTTON4)
			{
				tempAction|=JoyActions[9];    // switched with button 6
			}
			if (bd & BYJOY_BUTTON5)
			{
				tempAction|=JoyActions[8];
			}
			if (bd & BYJOY_BUTTON6)
			{
				tempAction|=JoyActions[7];    // switched with button 4
			}
			if (bd & BYJOY_BUTTON7)
			{
				tempAction|=JoyActions[10];
			}
			if (bd & BYJOY_BUTTON8)
			{
				tempAction|=JoyActions[11];
			}

			if (bd & BYJOY_BUTTON9)
			{
				short rcam;
				JoyCamCount++;
				if (JoyCamCount>5)
				{
					JoyCamCount = 0;
					JoyCurrentCam++;
					JoyCurrentCam = JoyCurrentCam % BY_TOTALCAMERA;
					rcam = camorder[JoyCurrentCam];
					switch(rcam)
					{
					case 1:
						camerastuff->method=POV;
						//if (!level) YBSetSubTitle1(Vmode, "WATCHY FIRST-PERSON", RGB(0, 255, 0));
						ResetCameraTarget(camerastuff);
						break;
					case 2:
						camerastuff->method=SLUGDRIFT;
						camerastuff->zone=2;
						//if (!level) YBSetSubTitle1(Vmode, "WATCHY OVER THE SHOULDER", RGB(0, 255, 0));
						ResetCameraTarget(camerastuff);
						break;
					case 3:
						camerastuff->method=SLUGDRIFT;
						camerastuff->zone=4;
						//if (!level) YBSetSubTitle1(Vmode, "WATCHY HIGH OVER THE SHOULDER", RGB(0, 255, 0));
						ResetCameraTarget(camerastuff);
						break;
					case 8:
						camerastuff->method=SLUGDRIFT;
						camerastuff->zone=6;
						//if (!level) YBSetSubTitle1(Vmode, "WATCHY AERIAL", RGB(0, 255, 0));
						ResetCameraTarget(camerastuff);
						break;
					default:
						break;
					};
				}
			//	tempAction|=JoyActions[12];
			}
			//if (bd & BYJOY_BUTTONa)
			//{
			//	tempAction|=JoyActions[13];
			//}
		}
		else  // if not the MS Game Pad
		{
			if (bd & BYJOY_BUTTON1)
			{
				tempAction|=JoyActions[4];
			}

			if (bd & BYJOY_BUTTON2) 
			{ 
				tempAction|=JoyActions[5];
			}

			if (bd0>=4)
			{
				if (bd & BYJOY_BUTTON3)
				{
					tempAction|=JoyActions[6];
				}
				if (bd & BYJOY_BUTTON4)
				{
					tempAction|=JoyActions[7];
				}
			}
		} // end if not MS Game Pad

		if (xd > (xd0+YB_JOY_XRANGE)) 
      {
		
			if ((JoyStickType == YB_SIDEWINDER_GAMEPAD || 
				  JoyStickType == YB_CREATIVE_GAMEPAD || 
				  JoyStickType == YB_GRAVIS_GRIP)&&(bd & BYJOY_BUTTONa))
			{
				tempAction|=JoyActions[17];
			}
			else
			{ 
				tempAction|=JoyActions[2];
			}
      }

		if (xd < (xd0-YB_JOY_XRANGE)) 
      {
			
			if ((JoyStickType == YB_SIDEWINDER_GAMEPAD || 
				  JoyStickType == YB_CREATIVE_GAMEPAD || 
				  JoyStickType == YB_GRAVIS_GRIP)&&(bd & BYJOY_BUTTONa))
			{
				tempAction|=JoyActions[16];
			}
			else
			{ 
				tempAction|=JoyActions[0];
			}
      }

		//if (!(tempAction & JoyActions[5])) 
      //{
		if (yd < (yd0-YB_JOY_YRANGE)) 
      {
         tempAction|=JoyActions[1];
      }

		if (yd > (yd0+YB_JOY_YRANGE)) 
      {
			if ((JoyStickType == YB_SIDEWINDER_GAMEPAD || 
            JoyStickType == YB_CREATIVE_GAMEPAD || 
            JoyStickType == YB_GRAVIS_GRIP)&&
            (bd & BYJOY_BUTTONa))
			{
				tempAction|=JoyActions[18];
			}
			else
			{
				tempAction|=JoyActions[3];
			}
      }
		//}

		if (tempAction!=0) 
      {
			NewJoyAction = tempAction;
			oldJoyAction = tempAction;
		}
	}

	return TRUE;

exit_with_false:
	return FALSE;
}


// Not in use in the game
void YBDispJoyAction(HWND hwnd)
{
	HDC hDC;
	char cBuf[128];
	
	hDC = GetDC(hwnd);

	if (InputInt & JoyActions[0])
		TextOut(hDC, 0, 0, cBuf, wsprintf(cBuf, "<====="));
	else 
		TextOut(hDC, 0, 0, cBuf, wsprintf(cBuf, "             "));

	if (InputInt & JoyActions[1])
		TextOut(hDC, 0, 20, cBuf, wsprintf(cBuf, "^^^^^"));
	else 
		TextOut(hDC, 0, 20, cBuf, wsprintf(cBuf, "            "));

	if (InputInt & JoyActions[2])
		TextOut(hDC, 0, 40, cBuf, wsprintf(cBuf, "=====>"));
	else 
		TextOut(hDC, 0, 40, cBuf, wsprintf(cBuf, "            "));

	if (InputInt & JoyActions[3])
		TextOut(hDC, 0, 60, cBuf, wsprintf(cBuf, "VVVVVV"));
	else 
		TextOut(hDC, 0, 60, cBuf, wsprintf(cBuf, "            "));

	TextOut(hDC, 0, 100, cBuf, wsprintf(cBuf,
	"X0= %d, Y0=%d, R0=%d, B0=%x (hex), Hat0=%d ",	xd0, yd0, rd0, bd0, hd0));

	TextOut(hDC, 0, 140, cBuf, wsprintf(cBuf, "                                         "));
	TextOut(hDC, 0, 140, cBuf, wsprintf(cBuf,
	"Hd=%d, Xd= %d, Yd=%d, Rd=%d", hd, xd, yd, rd));

	TextOut(hDC, 0, 120, cBuf, wsprintf(cBuf, "                          "));
	TextOut(hDC, 0, 120, cBuf, wsprintf(cBuf, "Actions = %x", InputInt));

	ReleaseDC(hwnd, hDC); 
}

// Not in use in the game
BOOL YBGetJoystickInput(HWND hwnd)
{
	HDC hDC;
	char cBuf[128];

	if (JoyStatus!=JOYERR_NOERROR) 
   {
		return FALSE;
   }

	switch(joyGetPosEx(JOYSTICKID1, &jix)) 
   {
	   case JOYERR_NOERROR:
		   break;
	   case MMSYSERR_NODRIVER:
		   strcpy(szErr, "The joystick driver is not present.");
		   return FALSE;
	   case MMSYSERR_INVALPARAM:
		   strcpy(szErr, "An invalid parameter was passed.");
		   return FALSE;
	   case MMSYSERR_BADDEVICEID:
		   strcpy(szErr, "The specified joystick identifier is invalid.");
		   return FALSE;
	   case JOYERR_UNPLUGGED:
		   strcpy(szErr, "Your joystick is unplugged.");
		   return FALSE;
	   default:
		   strcpy(szErr, "Unknown joystick error.");
		   return FALSE;
	}

	//joyGetPos(JOYSTICKID1, &ji);
	hDC = GetDC(hwnd);
	TextOut(hDC, 0, 0, cBuf, wsprintf(cBuf,
	"Joystick X= %d, Y=%d, Z=%d, R=%d, B=%x (hex), Hat=%d ",
	jix.dwXpos, jix.dwYpos, jix.dwZpos, jix.dwRpos, jix.dwButtons, jix.dwPOV));
	ReleaseDC(hwnd, hDC);
}




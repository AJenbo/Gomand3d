#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

#include "d3dappi.h"
#include "rmdemo.h"
#include "rmfull.h"
#include "keycom.h"
#include "byglobal.h"
#include "wrapper.h"
#include "ybmouse.h"

extern volatile long int InputInt;

extern BOOL KbFlag;
extern BOOL JoyFlag;

#define MS_XSENSITIVITY  2
#define MS_YSENSITIVITY  2

#define MS_640X_MAX     619
#define MS_640X_MIN      20
#define MS_640Y_MAX     440
#define MS_640Y_MIN      40

#define MS_320X_MAX     299
#define MS_320X_MIN      20
#define MS_320Y_MAX     210
#define MS_320Y_MIN      30

short MsFlyFlag = 0;
short MsRotateFlag = 0;
static long int OldState=0;
int YBCursorShowed = 0;
RECT  OldDisplayMode; // left=0, top=0, right=width, buttom=height

long int MsMvActions[5] =
{
   0,
   (COMMANDRight),
   (COMMANDLeft),
   (COMMANDForward|COMMANDMediumShift),                   // S=4, run
   (COMMANDBack)
};

long int MsBtnActions[2] =
{
   (COMMANDVisorBeam),
   (COMMANDForward|COMMANDStrongShift)
};

long int MsBtnDefActions[2] =
{
   (COMMANDVisorBeam),
   (COMMANDForward|COMMANDStrongShift)
};

long int RobotActions[] =
{
   (COMMANDVisorBeam),
   (COMMANDForward|COMMANDStrongShift)
};

void YBConfigMouse(int BtnNo, long int Actions)
{
   if (BtnNo<0 || BtnNo > 2)
   {
      return;
   }
   if (BtnNo==0)
   {
      MsBtnActions[0]=MsBtnDefActions[0];
      MsBtnActions[1]=MsBtnDefActions[1];
   }
   else
   {
      MsBtnActions[BtnNo-1]=Actions;
   }
}

void BYSetCursorClipArea(void)
{
	RECT csrrc;

	if (!bUseDebug)
	{
		if (VMode3D != 1)
		{
			csrrc.top    = MS_640Y_MIN - 11;
			csrrc.left   = MS_640X_MIN;
			csrrc.right  = MS_640X_MAX + 1;
			csrrc.bottom = MS_640Y_MAX + 11;
		}
		else
		{
			csrrc.top    = MS_320Y_MIN - 11;
			csrrc.left   = MS_320X_MIN;
			csrrc.right  = MS_320X_MAX + 1;
			csrrc.bottom = MS_320Y_MAX + 11;
		}
		ClipCursor(&csrrc);
	}
}

void YBSaveCurrentDisplayMode(void)
{
   int  x, y;

   x = GetSystemMetrics(SM_CXSCREEN);
   y = GetSystemMetrics(SM_CYSCREEN);

   OldDisplayMode.left = 0;
   OldDisplayMode.top  = 0;
   OldDisplayMode.right = x;
   OldDisplayMode.bottom = y;
}

void YBRestoreClipArea(void)
{
   ClipCursor(&OldDisplayMode);
}

BOOL BYMs3DGame(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static POINT OldP, NewP;
	long int NewState=0;
	long int *Input;
	short i, j;

	ISPAGE(pg_SHOW_GAME_SCREEN);

   // i: 0=nothing, 1=right, 2=left
   // j: 0=nothing, 3=forward, 4=back
   if (KbFlag && JoyFlag)
   {
      return FALSE;
   }

	Input = &InputInt;

   GetCursorPos(&NewP);

	//_RPT2(_CRT_WARN, "new x = %d, old x = %d\n", NewP.x, OldP.x);

   if (NewP.x > (OldP.x+MS_XSENSITIVITY))
   {
      if (VMode3D!=1 && NewP.x>=MS_640X_MAX)
      {
			NewP.x = MS_640X_MIN+1;
			SetCursorPos(NewP.x, NewP.y);
		}
		else
		{
			if (VMode3D==1 && NewP.x>=MS_320X_MAX)
			{
				NewP.x = MS_320X_MIN+1;
				SetCursorPos(NewP.x, NewP.y);
			}
		}
		i = 1;	// right
	}
	else
	{
		if (NewP.x < (OldP.x-MS_XSENSITIVITY))
		{
			if (VMode3D!=1 && NewP.x<=MS_640X_MIN)
			{
            NewP.x = MS_640X_MAX-1;
            SetCursorPos(NewP.x, NewP.y);
         }
         else
         {
            if (VMode3D==1 && NewP.x<=MS_320X_MIN)
            {
               NewP.x = MS_320X_MAX-1;
               SetCursorPos(NewP.x, NewP.y);
            }
         }
			i = 2;  // left
      }
      else
      {
			i = 0;
      }
   }
	

   if (NewP.y > (OldP.y+MS_YSENSITIVITY))
   {
      if (VMode3D!=1 && NewP.y>=MS_640Y_MAX)
      {
         NewP.y = MS_640Y_MIN+1;
         SetCursorPos(NewP.x, NewP.y);
      }
      else
      {
         if (VMode3D==1 && NewP.y>=MS_320Y_MAX)
         {
            NewP.y = MS_320Y_MIN+1;
            SetCursorPos(NewP.x, NewP.y);
         }
      }
      j = 4;	// back
   }
   else
   {
      if (NewP.y < (OldP.y-MS_YSENSITIVITY))
      {
         if (VMode3D!=1 && NewP.y<=MS_640Y_MIN)
         {
            NewP.y = MS_640Y_MAX-1;
            SetCursorPos(NewP.x, NewP.y);
         }
         else
         {
            if (VMode3D==1 && NewP.y<=MS_320Y_MIN)
            {
               NewP.y = MS_320Y_MAX-1;
               SetCursorPos(NewP.x, NewP.y);
            }
         }
			j = 3;	// forward
      }
      else
      {
         j = 0;
      }
   }

   OldP.x = NewP.x;
   OldP.y = NewP.y;

   NewState = *Input;

   if (i==0 && !KbFlag)
   {
      NewState&=~MsMvActions[1];  // right
      NewState&=~MsMvActions[2];  // left
   }
   else
   {
		if (i!=0)
		{
			NewState = *Input;
			NewState |= MsMvActions[i];
		}
   } 

    /*
    if (!MsFlyFlag) {
        if (j==0 && !KbFlag && !JoyFlag) {
            NewState&=~MsMvActions[3];
            NewState&=~MsMvActions[4];
        } else
        if (j!=0) {
    		NewState = *Input;
    		NewState |= MsMvActions[j];
        }
    } */

   *Input   = NewState;
	//InputInt = *Input;
	return TRUE;
exit_with_false:
	return FALSE;
}


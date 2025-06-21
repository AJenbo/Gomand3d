//*******************************************************************
// tkinput.cpp
//
// Copyright 1996 by 47-TEK, INC.  All rights reserved.
//
// Author:	Bo Yuan
// 
// Date:	11/10/96
//
// Description:   This module contains CDirectInput class member
//                functions definition.  The functions are used
//                for the creation, deletion, and use of different
//                input devices such as mouse, keyboard.
// 
// Side effects:
//
// Class:
//
// Function:
// 
// Notes:
//
// Update:
//
// Date			Name			Description
//*******************************************************************
#include "d3dappi.h"
#include "rmdemo.h"
#include "rmfull.h"
#include "byglobal.h"
#include "wrapper.h"
#include "ybmm.h"
#include "tkinput.h"
#include <stdio.h>

CDirectInput::CDirectInput(void)
{
	bDI = bDIMsDev = bDIKdDev = FALSE;
	bDIMsAcquired = bDIKdAcquired = bDIMsCanDraw = FALSE;
	lpDIMsDev = lpDIKdDev = NULL;
	lpDI = NULL;
	TotalDevices = MsAniItemIdx = MsTotalAniItems = 0;
	MsTotalAnis = 0;
	MsSensitivity = MsNORMAL;
	MsAniSpeed = 1;
	MsX = 320;
	MsY = 240;
	MsAction4Wrapper = WP_NOTHING;
	msact = WP_NOTHING;
}

BOOL CDirectInput::CreateDI(HINSTANCE hinst, HWND hwnd)
{
	HRESULT hr;

	hInst = hinst;
	hWnd  = hwnd;
	
	hr = DirectInputCreate(hInst, DIRECTINPUT_VERSION, &lpDI, NULL);
	if (SUCCEEDED(hr)) 
	{
		bDI=TRUE;
	}
	return bDI;
}

BOOL CDirectInput::CreateDIMsDevice(BOOL FullyControl)
{
	HRESULT hr;

	if (!bDI || bDIMsDev || bDIMsAcquired)
	{
		return FALSE;
	}

	// Obtain an interface to the system mouse device.
	hr = lpDI->CreateDevice(GUID_SysMouse, &lpDIMsDev, NULL);

	if (FAILED(hr)) 
	{
		OutputDebugString("Create mouse device failed\n");
		return FALSE;
	}

	// Set the data format to "mouse format".
	// you need only set once
	hr = lpDIMsDev->SetDataFormat(&c_dfDIMouse);

	if (FAILED(hr)) 
	{
		OutputDebugString("SetDataFormat to mouse format failed\n");
		return FALSE;
	}

	// Set the cooperativity level.
	// In exclusive mode, the mouse cursor will be removed 
	// from the screen until the device is unacquired.
	if (FullyControl)
	{
		hr = lpDIMsDev->SetCooperativeLevel
			 (hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	}
	else
	{
		hr = lpDIMsDev->SetCooperativeLevel
			 (hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}

	if (FAILED(hr)) 
	{
		OutputDebugString("SetCooperativeLevel(SysMouse) failed\n");
		return FALSE;
	}

	// up to this point, the creation is successful, and then
	// we need to acquire the mouse
	bDIMsDev=TRUE;
	lpDIMsDev->Acquire();
	bDIMsAcquired = TRUE;
	return TRUE;
}

BOOL CDirectInput::CreateDIKdDevice(void)
{
	HRESULT hr;

	// Obtain an interface to the system keyboard device.
	hr = lpDI->CreateDevice(GUID_SysKeyboard, &lpDIKdDev, NULL);

	if (FAILED(hr)) 
	{
		OutputDebugString("Create keyboard device failed\n");
		return FALSE;
	}

	// Set the data format to "keyboard format".
	// you need only set once
	hr = lpDIKdDev->SetDataFormat(&c_dfDIKeyboard);

	if (FAILED(hr)) 
	{
		OutputDebugString("SetDataFormat to keyboard format failed\n");
		return FALSE;
	}

	// Set the cooperativity level.
	hr = lpDIKdDev->SetCooperativeLevel
         (hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	if (FAILED(hr)) 
	{
		OutputDebugString("SetCooperativeLevel(SysMouse) failed\n");
		return FALSE;
	}

	if (lpDIKdDev->Acquire()!=DI_OK)
	{
		OutputDebugString("Acquire keyboard device failed\n");
		bDIKdAcquired=FALSE;
		return FALSE;
	}
	bDIKdDev=TRUE;
	bDIKdAcquired=TRUE;
	return TRUE;
}

void CDirectInput::SetDIMsAction(long int *Action)
{
	for (short i=0; i<6; i++)
	{
		MsAction[i+1] = Action[i];
	}
}

void CDirectInput::SetDIMsSensitivity(MS_SENSITIVITY s)
{
	MsSensitivity = s;
}

void CDirectInput::ProcessDIMsData(BOOL bSwitch)
{
	HRESULT hRes;
	DIMOUSESTATE MsState;

	if (!lpDIMsDev || !bSwitch)
	{
		return;
	}

	hRes = lpDIMsDev->GetDeviceState(sizeof(DIMOUSESTATE), &MsState);
   if (hRes != DI_OK)
	{
      if (hRes == DIERR_INPUTLOST)
      {
         // we lost control of the keyboard, reacquire
         bDIMsAcquired = FALSE;
         if(SUCCEEDED(lpDIMsDev->Acquire()))
         {
            bDIMsAcquired = TRUE;
         }
      }
	} 
	else
	{
		if (bInWrapper)
		{
			ProcessMsData4Wrapper(MsState);
		}
		else
		{
			ProcessMsData4Game(MsState);
		}
	}
	//ShowMsMovement();
}

BOOL CDirectInput::MsLBtnDown(void)
{
	DIMOUSESTATE MsState;

	if (!lpDIMsDev)
	{
		return FALSE;
	}
	lpDIMsDev->GetDeviceState(sizeof(DIMOUSESTATE), &MsState);
	if (MsState.rgbButtons[0])
	{
		return TRUE;
	}
	else
		return FALSE;
}

void CDirectInput::ProcessMsData4Wrapper(DIMOUSESTATE MsState)
{
	if (MsState.lX==0 && MsState.lY==0)
	{
		msact = WP_NOTHING;
	   if (MsState.rgbButtons[0])
	   {
		   msact = WP_LBUTTONDOWN;
	   }
		return;
	}

	MsState.lX+=MsDxFuzz;	MsDxFuzz=0;
	MsState.lY+=MsDyFuzz;	MsDyFuzz=0;

	switch(MsSensitivity)
	{
	case MsHIGH:
		MsState.lX*=2;
		MsState.lY*=2;
		break;
	case MsLOW:
		MsDxFuzz = MsState.lX % 2;
		MsDyFuzz = MsState.lY % 2;
		MsState.lX /= 2;
		MsState.lY /= 2;
		break;
	case MsNORMAL:
	default:
		break;
	}

	MsX += MsState.lX;
	MsY += MsState.lY;

	if (MsX < MsXHot) MsX = MsXHot;
	if (MsY < MsYHot) MsY = MsYHot;
	if ((MsX + MsWidth - MsXHot) >= 640) MsX = 639 - MsWidth + MsXHot;
	if ((MsY + MsHeight - MsYHot) >= 480) MsY = 479 - MsHeight + MsYHot;

	msact = WP_MOUSEMOVE;

}

// Private member function
void CDirectInput::ProcessMsData4Game(DIMOUSESTATE MsState)
{
	if (MsState.lX==0 && MsState.lY==0)
	{
	   NewMsAction = MsAction[MSNOTHING];
	   if (MsState.rgbButtons[0])
	   {
		   NewMsAction |= MsAction[MSLBUTTON];
	   }
	   if (MsState.rgbButtons[1])
	   {
		   NewMsAction |= MsAction[MSRBUTTON];
	   }
		return;
	}

	MsState.lX+=MsDxFuzz;	MsDxFuzz=0;
	MsState.lY+=MsDyFuzz;	MsDyFuzz=0;

	switch(MsSensitivity)
	{
	case MsHIGH:
		MsState.lX*=2;
		MsState.lY*=2;
		break;
	case MsLOW:
		MsDxFuzz = MsState.lX % 2;
		MsDyFuzz = MsState.lY % 2;
		MsState.lX /= 2;
		MsState.lY /= 2;
		break;
	case MsNORMAL:
	default:
		break;
	}

	NewMsAction = MsAction[MSNOTHING];

	if (MsState.lX>0)
	{
		NewMsAction |= MsAction[MSRIGHT];
	} 
	if (MsState.lX<0)
	{
		NewMsAction |= MsAction[MSLEFT];
	}
	if (MsState.lY>0)
	{
		NewMsAction |= MsAction[MSBACK];
	}
	if (MsState.lY<0)
	{
		NewMsAction |= MsAction[MSFORWARD];
	}
	if (MsState.rgbButtons[0])
	{
		NewMsAction |= MsAction[MSLBUTTON];
	}
	if (MsState.rgbButtons[1])
	{
		NewMsAction |= MsAction[MSRBUTTON];
	}
}

// Private member function
void CDirectInput::ShowMsMovement(void)
{
	char s[127];

	if (NewMsAction==0)
		sprintf(s, "== 0");
   else
		sprintf(s, "==      %d", NewMsAction);
	SetWindowText(hWnd, s);
}

BOOL CDirectInput::CreateMsSurface(void)
{
	DDSURFACEDESC       ddsd;
	IDirectDrawSurface *pdds;
	short  vwidth, vheight;

	vwidth  = 100;
	vheight = 50;

	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwWidth  = vwidth;
	ddsd.dwHeight = vheight;

	if (d3dappi.lpDD->CreateSurface(&ddsd, &pdds, NULL) != DD_OK)
	{
		return FALSE;
	}

	lpMsSurface = pdds;
	return TRUE;
}

BOOL CDirectInput::LoadCursorBmp(char *szBitmap)
{
	HBITMAP             hbm;
	BITMAP              bm;
	IDirectDrawSurface *pdds;
	char                fullname[127];

	if (lpMsSurface == NULL)
	{
		return FALSE;
	}
	//BYClearOverlaySurface(OverlayNum);
	pdds = lpMsSurface;

	hbm = LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

	if (hbm == NULL) 
	{
		strcpy(fullname, WrapBmpPath);
		strcat(fullname, "\\");
		strcat(fullname, szBitmap);
		
		hbm = (HBITMAP)LoadImage(NULL, fullname, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	}

	if (hbm == NULL) 
	{
		BYDumpInfo("********************");
		BYDumpInfo("couldn't load cursor");
		BYDumpInfo(szBitmap);
		BYDumpInfo("or");
		BYDumpInfo(fullname);
		BYDumpInfo("********************");

		return FALSE;
   }
	GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap

	DDCopyBitmap(pdds, hbm, 0, 0, 0, 0);

	DeleteObject(hbm);
	return TRUE;
}

void CDirectInput::TurnOnMsCursor(BOOL b)
{
	bDIMsCanDraw = b;
}

void CDirectInput::SetMsTotalAnis(short total)
{
	MsTotalAnis = total;
}

void CDirectInput::DrawMsCursor(BOOL show)
{
	HRESULT ddrval;
	static int i=0;
	DWORD x, y;
	int j=0;

	if (lpMsSurface==NULL || !show ||
		 !bDIMsCanDraw || MsTotalAnis==0)
	{
		return;
	}
	x = MsX - MsXHot;
	y = MsY - MsYHot;
	while (1) 
	{
		ddrval = d3dappi.lpBackBuffer->BltFast(x, y, 
			lpMsSurface, &MsRect[MsAniItemIdx], MsDrawMode);
		if (ddrval==DD_OK) 
			break;
		else
		{
			if (ddrval==DDERR_SURFACELOST)
			{
				lpMsSurface->Restore();
			}
			else
			if (HandleException(ddrval))
			{
				if (j>10) break;
				j++;
			}
		}

	} 
	i = (i+1) % (MsAniSpeed+1);
	if (MsTotalAnis>1 && i==MsAniSpeed)
	{
		MsAniItemIdx = (MsAniItemIdx+1) % MsTotalAnis;
	}
}

void CDirectInput::SelectAniCursor(RECT *rc)
{
	MsRect = &(rc[0]);
}

void CDirectInput::SetMsCursorColorKey(BOOL b, COLORREF rgb)
{
	IDirectDrawSurface *pdds;

	if (b)
	{
		DDCOLORKEY ddck;
		pdds = lpMsSurface;
		ddck.dwColorSpaceLowValue = DDColorMatch(pdds, rgb);
		ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;
		pdds->SetColorKey(DDCKEY_SRCBLT, &ddck);
		MsDrawMode = DDBLTFAST_SRCCOLORKEY;
	} 
	else
	{
		MsDrawMode = DDBLTFAST_NOCOLORKEY;
	}
}

void CDirectInput::ReleaseMsSurface(void)
{
	RELEASE(lpMsSurface);
}

void CDirectInput::SetMsAniSpeed(short i)
{
	if (i>1)
	{
		MsAniSpeed = i;
	}
}

void CDirectInput::SetMsCursorInfo(int hotx, int hoty, int w, int h)
{
	MsXHot = hotx;
	MsYHot = hoty;
	MsWidth = w;
	MsHeight = h;
}

int CDirectInput::GetMsX(void)
{
	return MsX;
}

int CDirectInput::GetMsY(void)
{
	return MsY;
}

BOOL CDirectInput::ReacquireKdDevice(void)
{
	if (lpDIKdDev != NULL)
	{
		lpDIKdDev->Acquire();
	}
	else
	{
		// keyboard device has not been created.
		bDIKdAcquired = FALSE;
		return FALSE;
	}

	// if we get here, we are acquired again
	bDIKdAcquired = TRUE;
	return TRUE;
}

_int64 CDirectInput::ReadDIKdData(BOOL bSwitch)
{
	BYTE rgbKeybd[256];
	HRESULT hRes;

	if (!bDIKdAcquired || !bDIKdDev || !bDI)
	{
		return 0;
	}

   hRes = lpDIKdDev->GetDeviceState(sizeof(rgbKeybd), rgbKeybd);
   if (hRes != DI_OK)
	{
      if (hRes == DIERR_INPUTLOST)
      {
         // we lost control of the keyboard, reacquire
         bDIKdAcquired = FALSE;
         if(SUCCEEDED(lpDIKdDev->Acquire()))
         {
            bDIKdAcquired = TRUE;
         }
      }

      // failed to read the keyboard, just return
		return 0;
	}

	// reset key states
	InputKeys = InputKeys ^ InputKeys;

	// check & update key states
	if(rgbKeybd[DIK_F12] & 0x80)
		InputKeys |= KEY_F12;
	if(rgbKeybd[DIK_F11] & 0x80)
		InputKeys |= KEY_F11;
	if(rgbKeybd[DIK_SPACE] & 0x80)
	  InputKeys |= KEY_SPACE;
	if((rgbKeybd[DIK_UP] & 0x80) || (rgbKeybd[DIK_NUMPAD8] & 0x80))
	  InputKeys |= KEY_UP;
	if((rgbKeybd[DIK_DOWN] & 0x80) || (rgbKeybd[DIK_NUMPAD2] & 0x80))
	  InputKeys |= KEY_DOWN;
	if((rgbKeybd[DIK_LEFT] & 0x80) || (rgbKeybd[DIK_NUMPAD4] & 0x80))
	  InputKeys |= KEY_LEFT;
	if((rgbKeybd[DIK_RIGHT] & 0x80) || (rgbKeybd[DIK_NUMPAD6] & 0x80))
	  InputKeys |= KEY_RIGHT;
	if(rgbKeybd[DIK_PRIOR] & 0x80)
	  InputKeys |= KEY_PRIOR;
	if(rgbKeybd[DIK_NEXT] & 0x80)
	  InputKeys |= KEY_NEXT;
	if(rgbKeybd[DIK_HOME] & 0x80)
	  InputKeys |= KEY_HOME;
	if(rgbKeybd[DIK_END] & 0x80)
	  InputKeys |= KEY_END;
	if((rgbKeybd[DIK_LSHIFT] & 0x80) || (rgbKeybd[DIK_RSHIFT] & 0x80))
	  InputKeys |= KEY_SHIFT;
	if((rgbKeybd[DIK_LCONTROL] & 0x80) || (rgbKeybd[DIK_RCONTROL] & 0x80))
	  InputKeys |= KEY_CONTROL;
	if(rgbKeybd[DIK_TAB] & 0x80)
	  InputKeys |= KEY_TAB;
	if(rgbKeybd[DIK_INSERT] & 0x80)
	  InputKeys |= KEY_INSERT;
	if(rgbKeybd[DIK_RETURN] & 0x80)
	  InputKeys |= KEY_RETURN;
	if(rgbKeybd[DIK_F1] & 0x80)
		InputKeys |= KEY_F1;
	if(rgbKeybd[DIK_F2] & 0x80)
	  InputKeys |= KEY_F2;
	if(rgbKeybd[DIK_F6] & 0x80)
	  InputKeys |= KEY_F6;
	if(rgbKeybd[DIK_GRAVE] & 0x80)
	  InputKeys |= KEY_192;
	if(rgbKeybd[DIK_A] & 0x80)
	  InputKeys |= KEY_A;
	if(rgbKeybd[DIK_B] & 0x80)
	  InputKeys |= KEY_B;
	if(rgbKeybd[DIK_C] & 0x80)
	  InputKeys |= KEY_C;
	if(rgbKeybd[DIK_D] & 0x80)
	  InputKeys |= KEY_D;
	if(rgbKeybd[DIK_E] & 0x80)
	  InputKeys |= KEY_E;
	if(rgbKeybd[DIK_F] & 0x80)
	  InputKeys |= KEY_F;
	if(rgbKeybd[DIK_G] & 0x80)
	  InputKeys |= KEY_G;
	if(rgbKeybd[DIK_H] & 0x80)
	  InputKeys |= KEY_H;
	if(rgbKeybd[DIK_I] & 0x80)
	  InputKeys |= KEY_I;
	if(rgbKeybd[DIK_J] & 0x80)
	  InputKeys |= KEY_J;
	if(rgbKeybd[DIK_K] & 0x80)
	  InputKeys |= KEY_K;
	if(rgbKeybd[DIK_L] & 0x80)
	  InputKeys |= KEY_L;
	if(rgbKeybd[DIK_M] & 0x80)
	  InputKeys |= KEY_M;
	if(rgbKeybd[DIK_N] & 0x80)
	  InputKeys |= KEY_N;
	if(rgbKeybd[DIK_O] & 0x80)
	  InputKeys |= KEY_O;
	if(rgbKeybd[DIK_P] & 0x80)
	  InputKeys |= KEY_P;
	if(rgbKeybd[DIK_Q] & 0x80)
	  InputKeys |= KEY_Q;
	if(rgbKeybd[DIK_R] & 0x80)
	  InputKeys |= KEY_R;
	if(rgbKeybd[DIK_S] & 0x80)
	  InputKeys |= KEY_S;
	if(rgbKeybd[DIK_T] & 0x80)
	  InputKeys |= KEY_T;
	if(rgbKeybd[DIK_U] & 0x80)
	  InputKeys |= KEY_U;
	if(rgbKeybd[DIK_V] & 0x80)
	  InputKeys |= KEY_V;
	if(rgbKeybd[DIK_W] & 0x80)
	  InputKeys |= KEY_W;
	if(rgbKeybd[DIK_X] & 0x80)
	  InputKeys |= KEY_X;
	if(rgbKeybd[DIK_Y] & 0x80)
	  InputKeys |= KEY_Y;
	if(rgbKeybd[DIK_Z] & 0x80)
	  InputKeys |= KEY_Z;
	if(rgbKeybd[DIK_COMMA] & 0x80)
	  InputKeys |= KEY_188;
	if(rgbKeybd[DIK_PERIOD] & 0x80)
	  InputKeys |= KEY_190;
	if(rgbKeybd[DIK_1] & 0x80)
	  InputKeys |= KEY_1;
	if(rgbKeybd[DIK_2] & 0x80)
	  InputKeys |= KEY_2;
	if(rgbKeybd[DIK_3] & 0x80)
	  InputKeys |= KEY_3;
	if(rgbKeybd[DIK_4] & 0x80)
	  InputKeys |= KEY_4;
	if(rgbKeybd[DIK_5] & 0x80)
	  InputKeys |= KEY_5;
	if(rgbKeybd[DIK_6] & 0x80)
	  InputKeys |= KEY_6;
	if(rgbKeybd[DIK_7] & 0x80)
	  InputKeys |= KEY_7;
	if(rgbKeybd[DIK_8] & 0x80)
	  InputKeys |= KEY_8;
	if(rgbKeybd[DIK_9] & 0x80)
	  InputKeys |= KEY_9;
	if(rgbKeybd[DIK_0] & 0x80)
	  InputKeys |= KEY_0;
	if(rgbKeybd[DIK_ESCAPE] & 0x80)
	  InputKeys |= KEY_ESCAPE;
	if((rgbKeybd[DIK_EQUALS] & 0x80) || (rgbKeybd[DIK_ADD] & 0x80))
		InputKeys |= KEY_SCALE;
	return InputKeys;
}

void CDirectInput::SaveKeyAction(long int ka)
{
	if (!bDIKdAcquired || !bDIKdDev || !bDI)
	{
		return;
	}

	NewKdAction = ka;
}

long int CDirectInput::GetDIMsAction(void)
{
	return NewMsAction;
}

void CDirectInput::DeleteDIMsDevice(void)
{
	if (bDIMsAcquired)
	{
		lpDIMsDev->Unacquire();
		bDIMsAcquired = FALSE;
	}

	if (lpDIMsDev)   
	{
		lpDIMsDev->Release();
		lpDIMsDev = NULL;
		bDIMsDev = FALSE;
	}
}

void CDirectInput::DeleteDIKdDevice(void)
{
	if (bDIKdAcquired)
	{
		lpDIKdDev->Unacquire();
		bDIKdAcquired = FALSE;
	}

	if (lpDIKdDev)   
	{
		lpDIKdDev->Release();
		lpDIKdDev = NULL;
		bDIKdDev = FALSE;
	}
}

void CDirectInput::DeleteDI(void)
{
	if (lpDI) 
	{
		lpDI->Release();
		lpDI = NULL;
	}
}

CDirectInput::~CDirectInput()
{
	DeleteDIMsDevice();
	DeleteDIKdDevice();

	if (lpDI) 
	{
		lpDI->Release();
		lpDI = NULL;
	}
}
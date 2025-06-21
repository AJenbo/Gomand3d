//*******************************************************************
// ybjoystk.h
//
// Copyright 1996 by 47-TEK, INC.  All rights reserved.
//
// Author:	Bo Yuan
// 
// Date:	06/04/96
//
// Description:	Header file of "ybjoystk.c"
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

#ifndef __YBJOYSTK_H__
#define __YBJOYSTK_H__

#include <stdio.h>
#ifdef MINIWIN
#include "miniwin/windows.h"
#else#include <windows.h>
#include <windows.h>
#include <mmsystem.h>
#endif
//#include <mmddk.h>  
#include <regstr.h>
#include "keycom.h"

#ifdef __cplusplus
extern "C" {
#endif

#define YB_NO_JOYSTICK        0
#define YB_GENERIC            1
#define YB_SIDEWINDER_3D_PRO  2
#define YB_SIDEWINDER_GAMEPAD 3
#define YB_CREATIVE_GAMEPAD   4
#define YB_GRAVIS_GRIP        5

int BYSetUpJoyStick (HWND win, UINT devnum);
void BYReleaseJoystick(void);
BOOL BYJoyMoveHandler(void);
void YBDispJoyAction(HWND hwnd);

extern int JoyStickType;
#ifdef __cplusplus
};
#endif

#endif
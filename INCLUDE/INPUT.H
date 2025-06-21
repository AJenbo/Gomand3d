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
$Header:   H:/pvcs/pvcsproj/gomand3d.prj/INPUT.H_V   1.3   27 Feb 1997 20:03:36   BRUCE  $

$Log:   H:/pvcs/pvcsproj/gomand3d.prj/INPUT.H_V  $
 * 
 *    Rev 1.3   27 Feb 1997 20:03:36   BRUCE
 * removed ProcessKeyUp
 * 
 * 
 *    Rev 1.2   31 Jan 1997 18:20:12   TIM
 * added key f1 for lighting toggle
 * 
 *    Rev 1.1   08 Nov 1996 15:08:10   JEREMIAH
 *  
***********************************************************************/

#ifndef _INPUT_H
#define _INPUT_H

#include <dinput.h>

/*
 * keyboard commands
 */
//There are about 56 items
#define KEY_F12    		0x0000000000000001
#define KEY_F11    		0x0000000000000002
#define KEY_SPACE		0x0000000000000004
#define KEY_UP   		0x0000000000000008
#define KEY_DOWN 		0x0000000000000010
#define KEY_LEFT 		0x0000000000000020
#define KEY_RIGHT		0x0000000000000040
#define KEY_PRIOR		0x0000000000000080
#define KEY_NEXT 		0x0000000000000100
#define KEY_HOME 		0x0000000000000200
#define KEY_END  		0x0000000000000400
#define KEY_SHIFT		0x0000000000000800
#define KEY_CONTROL     0x0000000000001000
#define KEY_TAB    		0x0000000000002000
#define KEY_INSERT  	0x0000000000004000
#define KEY_RETURN  	0x0000000000008000
#define KEY_F2     		0x0000000000010000
#define KEY_F6     		0x0000000000020000
#define KEY_192    		0x0000000000040000
#define KEY_A     		0x0000000000080000
#define KEY_B     		0x0000000000100000
#define KEY_C     		0x0000000000200000
#define KEY_D     		0x0000000000400000
#define KEY_E     		0x0000000000800000
#define KEY_F     		0x0000000001000000
#define KEY_G     		0x0000000002000000
#define KEY_H     		0x0000000004000000
#define KEY_I     		0x0000000008000000
#define KEY_J     		0x0000000010000000
#define KEY_K     		0x0000000020000000
#define KEY_L     		0x0000000040000000
#define KEY_M     		0x0000000080000000
#define KEY_N     		0x0000000100000000
#define KEY_O     		0x0000000200000000
#define KEY_P     		0x0000000400000000
#define KEY_Q     		0x0000000800000000
#define KEY_R     		0x0000001000000000
#define KEY_S     		0x0000002000000000
#define KEY_T     		0x0000004000000000
#define KEY_U     		0x0000008000000000
#define KEY_V     		0x0000010000000000
#define KEY_W     		0x0000020000000000
#define KEY_X     		0x0000040000000000
#define KEY_Y     		0x0000080000000000
#define KEY_Z     		0x0000100000000000
#define KEY_188    		0x0000200000000000
#define KEY_190     	0x0000400000000000
#define KEY_1     		0x0000800000000000
#define KEY_2     		0x0001000000000000
#define KEY_3     		0x0002000000000000
#define KEY_4     		0x0004000000000000
#define KEY_5     		0x0008000000000000
#define KEY_6     		0x0010000000000000
#define KEY_7     		0x0020000000000000
#define KEY_8     		0x0040000000000000
#define KEY_9     		0x0080000000000000
#define KEY_0     		0x0100000000000000
#define KEY_ESCAPE 		0x0200000000000000
#define KEY_F1			0x0400000000000000


BOOL InitInput(HINSTANCE ghinst);
BOOL CALLBACK   DI_EnumDevProc(LPDIDEVICEINSTANCE lpdidi, LPVOID lpv);
void            DI_ReadKeys(void);
void            CleanupInput(void);
BOOL                    ReacquireInputDevices(void);

void ProcessKeyDown ();
//void ProcessKeyUp ();

#endif // _INPUT_H




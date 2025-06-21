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
$Header:   H:/pvcs/pvcsproj/gomand3d.prj/input.c_v   1.1   08 Nov 1996 15:08:08   JEREMIAH  $

$Log:   H:/pvcs/pvcsproj/gomand3d.prj/input.c_v  $
 * 
 *    Rev 1.1   08 Nov 1996 15:08:08   JEREMIAH
 * DirectInput keyboard handling.  Written
 * by Liu GuoHong.
***********************************************************************/

#include "input.h"

//extern HINSTANCE                ghinst;             // program instance
//extern HWND                     BYMainHwnd;              // app window handle
extern HWND BYMainHwnd;

static LPDIRECTINPUT            lpdi;               // DirectInput interface
static LPDIRECTINPUTDEVICE      lpdiKeyboard;           // keyboard device interface
static BOOL                     fKeybdAcquired;     // has the keyboard been acquired?

//extern DWORD                    gdwKeys;            // gameplay keys
extern _int64			          gdwKeys;            // gameplay keys

/*
*
* InitInput
*
* Initialize DirectInput objects & devices
*
*/
BOOL InitInput(HINSTANCE ghinst)
{
    GUID        guid = GUID_SysKeyboard;
   HRESULT  hRes;

    // try to create di object
    if(DirectInputCreate(ghinst, DIRECTINPUT_VERSION, &lpdi, NULL) != DI_OK)
    {
        //ShowError(IDS_DINPUT_ERROR_DIC);
        return FALSE;
    }


    // try to create keyboard device
        if(lpdi->lpVtbl->CreateDevice(lpdi, &guid, &lpdiKeyboard, NULL) !=DI_OK)
    {
        //ShowError(IDS_DINPUT_ERROR_CD);
        return FALSE;
    }

        // Tell DirectInput that we want to receive data in keyboard format
        if (lpdiKeyboard->lpVtbl->SetDataFormat(lpdiKeyboard, &c_dfDIKeyboard) != DI_OK)
        {
                //ShowError(IDS_DINPUT_ERROR_DF);
                return FALSE;
        }

        // set cooperative level
        if(lpdiKeyboard->lpVtbl->SetCooperativeLevel(lpdiKeyboard, BYMainHwnd,
                         DISCL_NONEXCLUSIVE | DISCL_FOREGROUND) != DI_OK)
    {
//        ShowError(IDS_DINPUT_ERROR_SP);
        return FALSE;
        }

    // try to acquire the keyboard
   hRes = lpdiKeyboard->lpVtbl->Acquire(lpdiKeyboard);
   if(SUCCEEDED(hRes))
   {
      // keyboard was acquired
      fKeybdAcquired = TRUE;
    }
   else
   {
      // keyboard was NOT acquired
      fKeybdAcquired = FALSE;
   }

    // if we get here, all objects were created successfully
    return TRUE;    
        
}


/*
*
* DI_ReadKeys
*
* Use DirectInput to read game-play keys
*
*/
void DI_ReadKeys(void)
{
    BYTE rgbKeybd[256];
   HRESULT hRes;

   hRes = lpdiKeyboard->lpVtbl->GetDeviceState(lpdiKeyboard, sizeof(rgbKeybd), rgbKeybd);
   if(hRes != DI_OK)
    {
      if(hRes == DIERR_INPUTLOST)
      {
         // we lost control of the keyboard, reacquire
         fKeybdAcquired = FALSE;
         if(SUCCEEDED(lpdiKeyboard->lpVtbl->Acquire(lpdiKeyboard)))
         {
            fKeybdAcquired = TRUE;
         }
      }

      // failed to read the keyboard, just return
        return;
    }

    // reset key states
    gdwKeys = gdwKeys ^ gdwKeys;

    // check & update key states
    if(rgbKeybd[DIK_F12] & 0x80)
        gdwKeys |= KEY_F12;
    if(rgbKeybd[DIK_F11] & 0x80)
        gdwKeys |= KEY_F11;
    if(rgbKeybd[DIK_SPACE] & 0x80)
        gdwKeys |= KEY_SPACE;
    if((rgbKeybd[DIK_UP] & 0x80) || (rgbKeybd[DIK_NUMPAD8] & 0x80))
        gdwKeys |= KEY_UP;
    if((rgbKeybd[DIK_DOWN] & 0x80) || (rgbKeybd[DIK_NUMPAD2] & 0x80))
        gdwKeys |= KEY_DOWN;
    if((rgbKeybd[DIK_LEFT] & 0x80) || (rgbKeybd[DIK_NUMPAD4] & 0x80))
        gdwKeys |= KEY_LEFT;
    if((rgbKeybd[DIK_RIGHT] & 0x80) || (rgbKeybd[DIK_NUMPAD6] & 0x80))
        gdwKeys |= KEY_RIGHT;
	if(rgbKeybd[DIK_PRIOR] & 0x80)
        gdwKeys |= KEY_PRIOR;
    if(rgbKeybd[DIK_NEXT] & 0x80)
        gdwKeys |= KEY_NEXT;
    if(rgbKeybd[DIK_HOME] & 0x80)
        gdwKeys |= KEY_HOME;
    if(rgbKeybd[DIK_END] & 0x80)
        gdwKeys |= KEY_END;
    if((rgbKeybd[DIK_LSHIFT] & 0x80) || (rgbKeybd[DIK_RSHIFT] & 0x80))
        gdwKeys |= KEY_SHIFT;
    if((rgbKeybd[DIK_LCONTROL] & 0x80) || (rgbKeybd[DIK_RCONTROL] & 0x80))
        gdwKeys |= KEY_CONTROL;
    if(rgbKeybd[DIK_TAB] & 0x80)
        gdwKeys |= KEY_TAB;
    if(rgbKeybd[DIK_INSERT] & 0x80)
        gdwKeys |= KEY_INSERT;
    if(rgbKeybd[DIK_RETURN] & 0x80)
        gdwKeys |= KEY_RETURN;
    if(rgbKeybd[DIK_F2] & 0x80)
        gdwKeys |= KEY_F2;
    if(rgbKeybd[DIK_F6] & 0x80)
        gdwKeys |= KEY_F6;
    if(rgbKeybd[DIK_GRAVE] & 0x80)
        gdwKeys |= KEY_192;
    if(rgbKeybd[DIK_A] & 0x80)
        gdwKeys |= KEY_A;
    if(rgbKeybd[DIK_B] & 0x80)
        gdwKeys |= KEY_B;
    if(rgbKeybd[DIK_C] & 0x80)
        gdwKeys |= KEY_C;
    if(rgbKeybd[DIK_D] & 0x80)
        gdwKeys |= KEY_D;
    if(rgbKeybd[DIK_E] & 0x80)
        gdwKeys |= KEY_E;
    if(rgbKeybd[DIK_F] & 0x80)
        gdwKeys |= KEY_F;
    if(rgbKeybd[DIK_G] & 0x80)
        gdwKeys |= KEY_G;
    if(rgbKeybd[DIK_H] & 0x80)
        gdwKeys |= KEY_H;
    if(rgbKeybd[DIK_I] & 0x80)
        gdwKeys |= KEY_I;
    if(rgbKeybd[DIK_J] & 0x80)
        gdwKeys |= KEY_J;
    if(rgbKeybd[DIK_K] & 0x80)
        gdwKeys |= KEY_K;
    if(rgbKeybd[DIK_L] & 0x80)
        gdwKeys |= KEY_L;
    if(rgbKeybd[DIK_M] & 0x80)
        gdwKeys |= KEY_M;
    if(rgbKeybd[DIK_N] & 0x80)
        gdwKeys |= KEY_N;
    if(rgbKeybd[DIK_O] & 0x80)
        gdwKeys |= KEY_O;
    if(rgbKeybd[DIK_P] & 0x80)
        gdwKeys |= KEY_P;
    if(rgbKeybd[DIK_Q] & 0x80)
        gdwKeys |= KEY_Q;
    if(rgbKeybd[DIK_R] & 0x80)
        gdwKeys |= KEY_R;
    if(rgbKeybd[DIK_S] & 0x80)
        gdwKeys |= KEY_S;
    if(rgbKeybd[DIK_T] & 0x80)
        gdwKeys |= KEY_T;
    if(rgbKeybd[DIK_U] & 0x80)
        gdwKeys |= KEY_U;
    if(rgbKeybd[DIK_V] & 0x80)
        gdwKeys |= KEY_V;
    if(rgbKeybd[DIK_W] & 0x80)
        gdwKeys |= KEY_W;
    if(rgbKeybd[DIK_X] & 0x80)
        gdwKeys |= KEY_X;
    if(rgbKeybd[DIK_Y] & 0x80)
        gdwKeys |= KEY_Y;
    if(rgbKeybd[DIK_Z] & 0x80)
        gdwKeys |= KEY_Z;
    if(rgbKeybd[DIK_COMMA] & 0x80)
        gdwKeys |= KEY_188;
    if(rgbKeybd[DIK_PERIOD] & 0x80)
        gdwKeys |= KEY_190;
    if(rgbKeybd[DIK_1] & 0x80)
        gdwKeys |= KEY_1;
    if(rgbKeybd[DIK_2] & 0x80)
        gdwKeys |= KEY_2;
    if(rgbKeybd[DIK_3] & 0x80)
        gdwKeys |= KEY_3;
    if(rgbKeybd[DIK_4] & 0x80)
        gdwKeys |= KEY_4;
    if(rgbKeybd[DIK_5] & 0x80)
        gdwKeys |= KEY_5;
    if(rgbKeybd[DIK_6] & 0x80)
        gdwKeys |= KEY_6;
    if(rgbKeybd[DIK_7] & 0x80)
        gdwKeys |= KEY_7;
    if(rgbKeybd[DIK_8] & 0x80)
        gdwKeys |= KEY_8;
    if(rgbKeybd[DIK_9] & 0x80)
        gdwKeys |= KEY_9;
    if(rgbKeybd[DIK_0] & 0x80)
        gdwKeys |= KEY_0;
    if(rgbKeybd[DIK_ESCAPE] & 0x80)
        gdwKeys |= KEY_ESCAPE;

}

/*
*
* CleanupInput
*
* Cleans up DirectInput objects
*
*/
void CleanupInput(void)
{
    if(fKeybdAcquired)
    {
        lpdiKeyboard->lpVtbl->Unacquire(lpdiKeyboard);
        fKeybdAcquired = FALSE;
    }

    if(lpdiKeyboard != NULL)
        lpdiKeyboard->lpVtbl->Release(lpdiKeyboard);

    if(lpdi!= NULL)
        lpdi->lpVtbl->Release(lpdi);
    
}


/*
*
* ReacquireInputDevices
*
* Reacquires DirectInput devices as needed
*
*/
BOOL ReacquireInputDevices(void)
{
    // try to acquire the keyboard
        if(lpdiKeyboard != NULL)
        {
                lpdiKeyboard->lpVtbl->Acquire(lpdiKeyboard);
         }
        else
        {
                // keyboard device has not been created.
                fKeybdAcquired = FALSE;
                return FALSE;
        }

        // if we get here, we are acquired again
        fKeybdAcquired = TRUE;
        return TRUE;
}













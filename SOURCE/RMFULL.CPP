//*******************************************************************
// rmfull.cpp
//
// Copyright 1996 by 47-TEK, INC.  All rights reserved.
//
// Author:	Bo Yuan
// 
// Date:	09/26/96
//
// Description:   This is the main program of the whole game.  It
//                contains modules to register, create window, to
//                set up DD, D3D system, etc. The definition for
//                program arguments are:
// 
//                #th argument   meaning
//                -----------------------------------------------
//                1st            level
//
//                2nd            1= 640x400x16 wrapper
//                               2= 640x400x8  wrapper
//                               3= 640x400x16 wrapper + autodemo
//                               4= 640x400x8  wrapper + autodemo
//                               5= debug mode wrapper
//                               6= debug mode wrapper + autodemo
//
//                3rd            1= 320x240x8  3d window
//                               other = 640x480x8 3d window when 
//                               it is not debug mode wrapper
//
//                4th            details
//                5th            playfrom 1=CD, 2=HD
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
// ==================================================================
/*
* $Header:   H:/pvcs/pvcsproj/gomand3d.prj/rmfull.cpv   1.34   May 07 1997 16:55:42   JEREMIAH  $
* $Log:   H:/pvcs/pvcsproj/gomand3d.prj/rmfull.cpv  $
*
*   Rev 1.34   May 07 1997 16:55:42   JEREMIAH
*Separated stretch flags into separate 
*structure.  Added bWillStretch.  Allowed
*stretch to be selectable from window size
*menu.
*
*   Rev 1.33   28 Apr 1997 17:28:44   JEREMIAH
*Added framemeter code to stretched 
*render loop.
*
*   Rev 1.32   28 Apr 1997 10:15:22   TIM
*Made mods for s3 stretch
*
*
*   Rev 1.31   08 Apr 1997 10:53:42   JEREMIAH
*Debranched 1.30.2.2.
*
*   Rev 1.30.2.2   08 Apr 1997 10:49:24   JEREMIAH
*Changed render loop to accommodate 
*new backgrounds.
*
*   Rev 1.30.2.1   28 Mar 1997 15:03:36   JEREMIAH
*Murged 1.30.2.0 and 1.30.1.0
*
*   Rev 1.30.2.0   27 Mar 1997 19:31:16   BRUCE
*put in check to prevent someone from 
*running more than one copy of Goman at
*a time.
*   Rev 1.30.1.0   28 Mar 1997 14:44:46   JEREMIAH
*Call RenderBackground() instead of 
*BYBlt3DBackground()
*
*   Rev 1.30   Mar 20 1997 14:09:48   JEREMIAH
*Reordered the PageLock, PageUnlock
*pairings to try to not break bus mastering.
*
*   Rev 1.29   18 Mar 1997 15:00:42   JEREMIAH
*Added pragmas to disable optimization 
*around order-critical code.
*
*   Rev 1.28   12 Mar 1997 16:07:36   JEREMIAH
*Reordered calls in render loop to try
*to take advantage of bus mastering.
*
*   Rev 1.27   06 Mar 1997 14:43:16   JEREMIAH
*Called pure IM render calls after Render().
*
*Added BeginScene() and EndScene().
*
*Added PageLock() and PageUnlock() to 
*attempt bus mastering.
*
*   Rev 1.26   27 Feb 1997 20:03:06   BRUCE
*removed ProcessKeyUp
*
*
*   Rev 1.25   24 Feb 1997 11:47:54   BO
*added code to release ms device and ms cursor
*buffer
*
*   Rev 1.24   14 Feb 1997 20:26:22   BRUCE
*changed In3DMovie to GameStates.Is3DMovie
*changed netPlay to GameStates.IsNetplay
*
*
*   Rev 1.23   05 Feb 1997 17:41:54   JEREMIAH
*Changed by Bo.
*- include "ybmid.h" head file
*- removed BYGetVideoMemoryInfo to use Spuude's function
*- added code to setup MIDI system at the beginning (WM_CREATE) and
*call to quit MIDI system at the end (WM_DESTROY) as an improvement to the MIDI system so that it setup, quit and play MIDI more 
*reasonablely.
*- removed traditional joystick message handler in windows procedure because we don't use it anyway in the game since we now use DirectInput joystick handler.
*
*- removed bSupportD3D because I use Spudde's function
*added code to handle non-default mode video memory variable for 
*freeware.
*
*- added code to handle mouse/joystick configuration
*modified keyboard message handlers for mouse/joystick configuration
*
*- removed a sound effect in mouse character selection because it may
*somehow turn off sound effect in the game.
*
*- modified code to remove two bugs in mode/window size selection menu. - rem out Time event handler for mouse/joystick configuration screen. - modified MidiCenter so that it works more reasonable
*- added code to play win/lose MIDI after game play
*- removed a few unused local variables in several functions
*
*
*
*   Rev 1.22   04 Feb 1997 16:20:32   JEREMIAH
*Added calls to DumpMemoryStatus().
*Fixed memory leak that occurs if level
*exits in middle of 3d movie.
*
*   Rev 1.21   31 Jan 1997 13:58:08   JEREMIAH
*Changed by Bo.
*Added 3 video mode options to compile
*freeware version.
*
*   Rev 1.20   29 Jan 1997 14:38:20   JEREMIAH
*Changed by Bo.
*Added 1-level freeware demo when 
*compiled with FREEWARE defined.
*
*   Rev 1.19   28 Jan 1997 14:04:22   TIM
*Calculate and display framerate on secret code Boolean
*
*   Rev 1.18   28 Jan 1997 10:26:46   JEREMIAH
*Changed by Bo.
*rem out BYJoyMoveHandler in main 
*windows procedure
*
*   Rev 1.17   24 Jan 1997 10:45:02   JEREMIAH
*Moved cleanup calls out of frame callback
*and into the renderloop.
*
*   Rev 1.16   22 Jan 1997 13:20:58   JEREMIAH
*Removed framerate printout and netplay
*status printout.
*
*   Rev 1.15   21 Jan 1997 10:33:26   TIM
*No change
*
*   Rev 1.14   09 Jan 1997 15:00:04   BO
*added a few calls for our new cursor
*
*   Rev 1.13   07 Jan 1997 10:20:04   BO
* 
*
*   Rev 1.12   16 Dec 1996 10:48:36   JEREMIAH
*Changed by ITC.  Added code for netplay.
*
*   Rev 1.11   03 Dec 1996 12:04:20   JEREMIAH
*Removed extraneous ForceUpdate()
*call.
*
*   Rev 1.10   13 Nov 1996 15:58:40   BO
* Add a switch flag to control the display of game user interface
*
*   Rev 1.9   13 Nov 1996 09:52:48   BO
** remove ybmouse.h + input.h
** remove all calls to old mouse functions
** add tkinput.h + fly.h + declaration for the
*new DirectInput class CDirectInput
** add new functions to process mouse and joystick
*input, and finally to put them together.
*
*   Rev 1.8   08 Nov 1996 15:54:58   JEREMIAH
*Changed by Liu GuoHong (ITC).  Added 
*calls to process DirectInput keyboard
*input.
*
*   Rev 1.6   Nov 05 1996 15:05:46   JEREMIAH
*Changed event loop to process up to,
*but no more than, 5 events.
*
*   Rev 1.5   Nov 01 1996 12:33:26   JEREMIAH
*Changed by Bo.  Removed extra 
*BYDumpInfo() calls.  Moved BYIniForWrapper()
*call.  Miscellaneous cleanup.
*
*   Rev 1.4   Nov 01 1996 10:53:52   JEREMIAH
*Rearranged Update and Clear calls to
*work with full-screen backgrounds.
*
*   Rev 1.3   Oct 24 1996 14:45:02   JEREMIAH
*Changed by Bo.  Removed YBConfigMouse
*call.
*
*   Rev 1.2   Oct 23 1996 12:44:56   JEREMIAH
*Fixed PVCS Header and Log formatting.
*
*   Rev 1.1   Oct 23 1996 12:39:42   JEREMIAH
*Removed BYDumpInfo() in render loop.
*Checked for NULL d3dapp during exit
*to avoid crash.
*/
//*******************************************************************
#include "rmfull.h"
#include "byglobal.h"
#include "global.h"
#include "wrapper.h"
#include "ybreg.h"
#include "ybmm.h"
#include "ybjoystk.h"
#include "tkinput.h"
#include "fly.h"
#include "netmenu.h"
#include "netinit2.h"
#include "netplay.h"
#include "ybmid.h"

extern "C"
{
	#include "input.h"
	#include "spritlib.h"
   #include "imisc.h"
   #include "clutter.h"
   extern D3DAppInfo d3dappi;
	extern int NextLevel;
   extern sStretchInfo sStretch;
//	extern BOOL In3DMovie;
	
}

// GLOBAL VARIABLES
//
char GameName[9] = "GoManD3D";
char GameVersion [5] = "V2.2";
BOOL bBYRenderingIsOK = FALSE;
BOOL bFrameMeter= FALSE; // New Global from Tim

D3DAppInfo* d3dapp = NULL;     // Pointer to read only collection of DD and D3D
                               // objects maintained by D3DApp 
rmfullglobals myglobs;         // collection of global variables 
LPDIRECT3DRM lpD3DRM;          // Direct3DRM object  
CDirectInput di;

// INTERNAL FUNCTION PROTOTYPES
//

static BOOL AppInit(HINSTANCE hInstance, LPSTR lpCmdLine);
static BOOL CreateD3DApp(LPSTR lpCmdLine);
static BOOL BeforeDeviceDestroyed(LPVOID lpContext);
static BOOL AfterDeviceCreated(int w, int h, LPDIRECT3DVIEWPORT* lpViewport,
                               LPVOID lpContext);
void CleanUpAndPostQuit(void);
void ReportD3DAppError(void);
static BOOL RenderLoop(void);
static BOOL RestoreSurfaces();
long FAR PASCAL 
WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
BOOL SetRenderState(void);
BOOL Render3DWorld(void);

/****************************************************************************/
/*                            WinMain                                       */
/****************************************************************************/
int PASCAL WinMain
(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
   int i;
/*
#ifdef FREEWARE
	if (!FindDirectX3a())
		return FALSE;
#endif
*/
	if(FindWindow("GoManD3D","GoManD3D"))
		return FALSE;

	BYSetUpSystemEnvironment(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	
	// Create the window and initialize all objects needed to begin rendering
	if (!AppInit(hInstance, lpCmdLine)) 
	{
		return FALSE;
	}

	BYSetupThings4Wrapper();

	while (!myglobs.bQuit) 
	{
      // Monitor the message queue -- handle up to 5 messages per loop
		for( i=0;(i<5) && (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)); i++)
		{
			if (msg.message == WM_QUIT) 
			{
				//CleanUpAndPostQuit();
				myglobs.bQuit = TRUE;
				break;
			}
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}

		di.ProcessDIMsData(TRUE);
		ProcessKeyDown ();
//		ProcessKeyUp ();
		BYJoyMoveHandler();
		BYMouseHandler[Page](BYMainHwnd);
		FinalProcess();

		if (RenderGame())
		{
			break;
		}
	}
	di.DeleteDIMsDevice();
	di.DeleteDIKdDevice();

	return msg.wParam;
}

//
BOOL Render3DWorld(void)
{
	static int failcount=0;

	// If the app is not about to quit, and D3D
	// has been initialized, we can render
	if (d3dapp->bRenderingIsOK && !myglobs.bQuit) 
	{

		// Attempt to render a frame, if it fails, take a note.  If
		// rendering fails more than twice, abort execution.
      if (!RenderLoop()) 
		{
          ++failcount;
          if (failcount == 3) 
			 {
              BYDumpInfo("Rendering has failed too many times.  Aborting execution.");
              CleanUpAndPostQuit();
              return FALSE;
          }
      } 
		
	}
	return TRUE;
}

/****************************************************************************/
/*             D3DApp Initialization and callback functions                 */
/****************************************************************************/
static BOOL AppInit(HINSTANCE hInstance, LPSTR lpCmdLine)
{
	WNDCLASS wc;
	int  x, y;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = GameName;
	if (!RegisterClass(&wc))
	{
		return FALSE;
	}

	BYIniForWrapper(hInstance);

	x = GetSystemMetrics(SM_CXSCREEN);
	y = GetSystemMetrics(SM_CYSCREEN);

	if (VM_FULLSCREEN == FALSE) 
	{
		x = (x-VM_W)/2;
		y = (y-VM_H)/2;

		myglobs.hWndMain = CreateWindowEx(
			WS_EX_APPWINDOW,
			GameName,
			GameName,
			WS_POPUP, 
			x, y,  
			VM_W, VM_H,  
			NULL,                               
			NULL,                              
			hInstance,                         
			NULL);      
	} 
	else 
	{
		myglobs.hWndMain = CreateWindowEx(
			WS_EX_APPWINDOW,
			GameName,
			GameName,  
			WS_POPUP,  
			0, 0,  
			x, y,  
			NULL,                             
			NULL,                              
			hInstance,                        
			NULL);                           
	}

	if (!myglobs.hWndMain)
	{
		BYDumpInfo("CreateWindowEx failed.");
		return FALSE;
	}
	BYMainHwnd = myglobs.hWndMain;

   ShowWindow(myglobs.hWndMain, SW_SHOWNORMAL);
	UpdateWindow(myglobs.hWndMain);

	if (bUseDebug)
	{
		// Create the D3DRM object which are initialized only when the program
		// starts
		if (!BYCreateD3DRMetc(myglobs.hWndMain))
		{
			return FALSE;
		}

		// Call D3DApp to initialize all DD and D3D objects necessary to render.
		// D3DApp will call the device creation callback which will initialize the
		// viewport and the sample's execute buffers.
		if (!CreateD3DApp(lpCmdLine))
		{
			return FALSE;
		}
		//Create the scene to be rendered by calling this sample's BuildScene

		if (!BuildScene(myglobs.dev, myglobs.view, myglobs.scene, myglobs.camera))
		{
			return FALSE;
		}
	}
	else
	{
		if (!BYCreateDDForWrapper(myglobs.hWndMain))
		{
			return FALSE;
		}
	}

	//Initialize the Direct Input.
	//InitInput (hInstance);
	di.CreateDI(hInstance, BYMainHwnd);
	di.CreateDIKdDevice();

	return TRUE;
}


// CreateD3DApp
// Create all DirectDraw and Direct3D objects necessary to begin rendering.
// Add the list of D3D drivers to the file menu.
//
static BOOL CreateD3DApp(LPSTR lpCmdLine)
{
	// Create all the DirectDraw and D3D objects neccesary to render.  The
	// AfterDeviceCreated callback function is called by D3DApp to create the
	// viewport and the example's execute buffers.

	if (!D3DAppCreateFromHWND(0, myglobs.hWndMain, AfterDeviceCreated,
								NULL, BeforeDeviceDestroyed, NULL, &d3dapp)) 
	{
		ReportD3DAppError();
		return FALSE;
	}

	return TRUE;
}

// AfterDeviceCreated
// D3DApp will call this function immediately after the D3D device has been
// created (or re-created).  D3DApp expects the D3D viewport to be created and
// returned.  In this case, we will return NULL because we only have a D3DRM
// viewport.  This is fine as long as we don't use any of the D3D viewport
// functionality of D3DApp.
BOOL AfterDeviceCreated
(int w, int h, LPDIRECT3DVIEWPORT* lplpViewport, LPVOID lpContext)
{
	HRESULT rval;
	int x0, y0, w0, h0;

	rval = lpD3DRM->CreateDeviceFromD3D(d3dapp->lpD3D, d3dapp->lpD3DDevice,
                                        &myglobs.dev);
	if (rval != D3DRM_OK) 
	{
		Msg("Creation of D3DRM device failed.\n%s", D3DAppErrorToString(rval));
		return FALSE;
	}

   // Create the D3DRM viewport using the camera frame.  Set the background
   // depth to a large number.  The width and height may be slightly
   // adjusted, so get them from the device to be sure.
	w0 = myglobs.dev->GetWidth();  
	h0 = myglobs.dev->GetHeight();  
	x0 = 0;  
	y0 = 0;  

	rval = lpD3DRM->CreateViewport(myglobs.dev, myglobs.camera, x0, y0, w0,
                                   h0, &myglobs.view);
	if (rval != D3DRM_OK) 
	{
		Msg("Failed to create the D3DRM viewport.\n%s",
				D3DAppErrorToString(rval));
		RELEASE(myglobs.dev);
		return FALSE;
	}
	rval = myglobs.view->SetBack(D3DVAL(5000.0));
	if (rval != D3DRM_OK) 
	{
		Msg("Failed to set the background depth of the D3DRM viewport.\n%s",
			D3DAppErrorToString(rval));
		RELEASE(myglobs.dev);
		RELEASE(myglobs.view);
		return FALSE;
   }
   //Set the render quality, fill mode, lighting state and color shade info
   if (!SetRenderState())
	{
		return FALSE;
	}
   //Return NULL for the viewport
   *lplpViewport = NULL;

	// Create and initialize the surfaces containing the frame rate and
   // window information
	InitFontAndTextBuffers();

	return TRUE;
}

//BeforeDeviceDestroyed
//D3DApp will call this function before the current D3D device is destroyed
//to give the app the opportunity to destroy objects it has created with the
//DD or D3D objects.
BOOL BeforeDeviceDestroyed(LPVOID lpContext)
{
	RELEASE(myglobs.view);
	RELEASE(myglobs.dev);
	return TRUE;
}

#pragma optimize( "", off)

/****************************************************************************/
/*                            Rendering loop                                */
/****************************************************************************/
// RenderLoop
// Render the next frame and update the window
static BOOL RenderLoop()
{
	D3DRECT extents[D3DAPP_MAXCLEARRECTS];
	int count;
	HRESULT rval;
	static BOOL b = FALSE; // Clear the second buffer on also
	LPDIRECTDRAWSURFACE2 lpSurf2;
	static int failcount=0;
	RECT        rcSource;
	RECT        rcDest;
	int			ddrval;



	//Tim Stretch: add a new "stretch render loop" in the stretchable case

	if (sStretch.bStretch)
	{
	
		// If all the DD and D3D objects have been initialized we can render
		if (d3dapp->bRenderingIsOK) 
		{
			   
			// If all the DD and D3D objects have been initialized we can render
				

			rcSource.left = 0;
			rcSource.top = 0;
			rcSource.right  = ((d3dapp->szClient.cx/2.0)-1);   //640;
			rcSource.bottom = ((d3dapp->szClient.cy/2.0)-1);  //480;

			rcDest.left = 0;
			rcDest.top = 0;
			rcDest.right = (d3dapp->szClient.cx-1);
			rcDest.bottom = (d3dapp->szClient.cy-1);



			// Restore any lost surfaces
			if (!RestoreSurfaces()) 
			{
				/*
				* Restoring surfaces sometimes fails because the surfaces cannot
				* yet be restored.  If this is the case, the error will show up
				* somewhere else and we should return success here to prevent
				* unnecessary error's being reported.
				*/
				return TRUE;
			}


			CalculateFrameRate();

			if (!bAskQuit)
			{
				rval = myglobs.scene->Move(D3DVAL(1.0));
				if (rval != D3DRM_OK) {
					Msg("Moving scene failed.\n%s", D3DAppErrorToString(rval));
					return FALSE;
				}
			}

			//rval = myglobs.view->Clear();


			//BYBlt3DBackground(TRUE);
			//if (d3dappi.ThisDriver.bIsHardware && vramsize > 2097152 )
			RenderBackgroundOn4MegAcc(TRUE);
			//RenderBackground(TRUE);


			rval = myglobs.view->Render(myglobs.scene);
			if (rval != D3DRM_OK) {
					Msg("Rendering scene failed.\n%s", D3DAppErrorToString(rval));
					return FALSE;
			}
			
			RenderAllMiscDLists();
			RenderAllParticles();
			RenderAllCxSprites();

			BYDisplayUI(bShowGameUI);

         // Tim Display frame rate
		   if (bFrameMeter)
	      {
				   count = 0;
				   if (!DisplayFrameRate(&count, &extents[0]))
				   {
					      //RELEASE(lpSurf2);
				         return FALSE;
				   }
		   }


			ddrval= d3dapp->lpBackBuffer2->UpdateOverlay(&rcSource, d3dapp->lpFrontBuffer, &rcDest, DDOVER_SHOW, 0);

			 //Flip the two  back buffers
			ddrval = d3dappi.lpBackBuffer->Flip(d3dappi.lpBackBuffer2, 1);

		}
		// Tim Stretch: this is the old non stretchable render loop
		if (NextLevel == 1)
		{
				//Add by Eric 11/15/96
				//if (!isOpponentSend)
				#ifdef _DEBUG
					DumpMemoryStatus("Before level cleanup");
				#endif
				if (GameStates.IsNetplay)
				{
					EventSndBuf.MsgId = NEW_MSG;
					EventSndBuf.Event = EVENT_EXITTOMENU;
					//beSynchronous = FALSE;
					//isSelectedCharacter = FALSE;
				}
				//isOpponentSend = FALSE;
				//end of Eric
			
				NextLevel = 0;
				QuitFlag = FALSE;
				bBYRenderingIsOK = FALSE;
				CleanupGame3DPart();
				bBYRenderingIsOK = TRUE;
				OutputDebugString("====================>>>>\n");
				BYKbFrom3DTo2D(BYMainHwnd, NULL, NULL, NULL);
				#ifdef _DEBUG
					DumpMemoryStatus("After level cleanup");
				#endif
		}

		return TRUE;


	}

	else

	{
	   rval = 
		  d3dappi.lpBackBuffer->QueryInterface(IID_IDirectDrawSurface2, (LPVOID *)&lpSurf2);

	   if(rval != DD_OK)
	   {
		  RELEASE(lpSurf2); 
		  return FALSE;
	   }

		// If all the DD and D3D objects have been initialized we can render
		if (d3dapp->bRenderingIsOK) 
		{
			// Restore any lost surfaces
			if (!RestoreSurfaces()) 
			{
				// Restoring surfaces sometimes fails because the surfaces cannot
				// yet be restored.  If this is the case, the error will show up
				// somewhere else and we should return success here to prevent
				// unnecessary error's being reported.
				return TRUE;
			}

			// Force an update of the entire client window if the resized flag is set
			if (myglobs.bResized || b)
				myglobs.view->ForceUpdate(0, 0, d3dapp->szClient.cx, d3dapp->szClient.cy);
				// Use b to makesure the second buffer is cleared also
				if (b)
				b = FALSE;
				if (myglobs.bResized)
				b = TRUE;

				// Tim Calculate the frame rate
				if (bFrameMeter){
					if (!CalculateFrameRate())
					return FALSE;
				}


			 // Page Lock
				// Tick the scene
				if (!bAskQuit)
				{
					rval = myglobs.scene->Move(D3DVAL(1.0));
					if (rval != D3DRM_OK) {
						Msg("Moving scene failed.\n%s", D3DAppErrorToString(rval));
				   RELEASE(lpSurf2);
						return FALSE;
					}
				}

			 if (!(d3dappi.ThisDriver.bIsHardware && vramsize > 2097152 ))
				RenderBackground(TRUE);

			rval = d3dappi.lpD3DDevice->BeginScene();
			if (rval != D3DRM_OK) {
				Msg("BeginScene() failed.\n%s", D3DAppErrorToString(rval));
				return FALSE;
			}
			 if (d3dappi.ThisDriver.bIsHardware && vramsize > 2097152 )
				RenderBackgroundOn4MegAcc(TRUE);

		   // Render the scene to the viewport
			rval = myglobs.view->Render(myglobs.scene);
			if (rval != D3DRM_OK) 
			{
				Msg("Rendering scene failed.\n%s", D3DAppErrorToString(rval));
				return FALSE;
			}

			 RenderAllMiscDLists();
			 RenderAllParticles();
			 RenderAllCxSprites();
			 rval = d3dappi.lpD3DDevice->EndScene();
			 if (rval != D3DRM_OK) 
			 {
				Msg("EndScene() failed.\n%s", D3DAppErrorToString(rval));
				return FALSE;
			 }
			 BYDisplayUI(bShowGameUI);
        
			 // Tim Display frame rate
			   if (bFrameMeter)
			 {
				   count = 0;
				   if (!DisplayFrameRate(&count, &extents[0]))
				{
					   RELEASE(lpSurf2);
				   return FALSE;
				}
			   }

			//Add by Eric 11/12/96
			if (GameStates.IsNetplay)
			{
				//DisplayNetPlayStatus();
				switch (DisplayDebugMsgFlag)
				{
					case 1:
						DisplayDebugMsgInfo();
						break;
					case 2:
						DisplayDebugMsgInfo2();
						break;
					default:
						break;
				}
			}
			 //end of Eric
			 // Blt or flip the back buffer to the front buffer.  If this fails,
			 // don't report an error.

			D3DAppShowBackBuffer(myglobs.bResized ? D3DAPP_SHOWALL : NULL);


			 // Reset the resize flag
			 myglobs.bResized = FALSE;
	   }
	   if (NextLevel == 1)
	   {
	#ifdef _DEBUG
	   DumpMemoryStatus("Before level cleanup");
	#endif
				//Add by Eric 11/15/96
				if (GameStates.IsNetplay)
				{
					EventSndBuf.MsgId = NEW_MSG;
					EventSndBuf.Event = EVENT_EXITTOMENU;
				}
				//end of Eric
			
				NextLevel = 0;
				QuitFlag = FALSE;
				bBYRenderingIsOK = FALSE;
				CleanupGame3DPart();
				bBYRenderingIsOK = TRUE;
				OutputDebugString("====================>>>>\n");
				BYKbFrom3DTo2D(BYMainHwnd, NULL, NULL, NULL);
	#ifdef _DEBUG
	   DumpMemoryStatus("After level cleanup");
	#endif
			}
	   RELEASE(lpSurf2);
	   return TRUE;
	}
}
#pragma optimize( "", on)

// RestoreSurfaces
// Restores any lost surfaces.  Returns TRUE if all surfaces are not lost and
// FALSE if one or more surfaces is lost and can not be restored at the
// moment.
static BOOL RestoreSurfaces()
{
    HRESULT d3drval;

    // Have D3DApp check all the surfaces it's in charge of
    if (!D3DAppCheckForLostSurfaces()) 
	{
		return FALSE;
    }
    // Check frame rate and info surfaces and re-write them if they
    // were lost.
    if (myglobs.lpFrameRateBuffer->IsLost() == DDERR_SURFACELOST) 
	 {
        d3drval = myglobs.lpFrameRateBuffer->Restore();
        if (d3drval != DD_OK) 
		  {
            return FALSE;
        }
        if (!WriteFrameRateBuffer(0.0f, 0))
            return FALSE;
    }
    if (myglobs.lpInfoBuffer->IsLost() == DDERR_SURFACELOST) 
	 {
        d3drval = myglobs.lpInfoBuffer->Restore();
        if (d3drval != DD_OK) 
		  {
            return FALSE;
        }
        if (!WriteInfoBuffer())
            return FALSE;
    }
    return TRUE;
}


/*************************************************************************
  Windows message handlers
 *************************************************************************/
long FAR PASCAL 
WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL bStop;
	LRESULT lresult;

	// Give D3DApp an opportunity to process any messages it MUST see in order
	// to perform it's function.
	if (!D3DAppWindowProc(&bStop, &lresult, hWnd, message, wParam, lParam)) 
	{
		ReportD3DAppError();
		CleanUpAndPostQuit();
		return 0;
	}

	// If bStop is set by D3DApp, the app should not process the message but
	// return lresult.
	if (bStop) return lresult;

	switch( message ) 
	{
	case WM_CREATE:
		BYSetUpJoyStick(hWnd, JOYSTICKID1);		// Hidden for integration -Spudde
		YBCreateEvent();
		YBSetupDMidi();
		break;

	case MM_MCINOTIFY:
		BYMciNotifyHandler(hWnd, message, wParam, lParam);
		break;

	case WM_TIMER:
		BYTimeHandler[Page](hWnd, message, wParam, lParam);
		break;

    case WM_COMMAND:
		BYPageHandler[Page](hWnd, message, wParam, lParam);
		BYSetPostPageSwitch(Page); 
		break;

	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		//BYMiceHandler[Page](hWnd, message, wParam, lParam);
		break;

	case WM_CHAR:
	case WM_KEYUP:
	case WM_KEYDOWN:
		BYKbrdHandler[Page](hWnd, message, wParam, lParam);
		return 0;

	case WM_DESTROY:
		YBQuitDMidi();
		//Add by Eric 11/12/96
		if (GameStates.IsNetplay)
		{
            DestroyPlayer(MyId);
             
            if (SimuMode)            //for simulation mode, kill timer.
            {
                KillTimer(NULL, TimerId);
            }

            if (isHost)
            {
                 Close();
            }
		}
		//end of Eric

		myglobs.hWndMain = NULL;
		bBYRenderingIsOK = FALSE;
		//d3dapp->bRenderingIsOK = FALSE;
		BYReleaseJoystick();
		di.ReleaseMsSurface();
		//CleanUpAndPostQuit();
		BYCleanUp();
		PostQuitMessage(0);
		break;

	//DirectInput must have this message process.
	case WM_ACTIVATE:
        /*
		{   
			LPDIRECT3DRMWINDEVICE windev;

            if (SUCCEEDED(info->dev->QueryInterface(IID_IDirect3DRMWinDevice, (void **) &windev)))
            {   if (FAILED(windev->HandleActivate(wparam)))
                    Msg("Failed to handle WM_ACTIVATE.\n");
                windev->Release();
            } else {
                Msg("Failed to create Windows device to handle WM_ACTIVATE.\n");
            }
        }
		*/

        //ReacquireInputDevices();
			di.ReacquireKdDevice();
		break;

	default:
		return( DefWindowProc(hWnd, message, wParam, lParam));
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}


/****************************************************************************/
/*                          Additional Functions                            */
/****************************************************************************/

// SetRenderState: 
// Set the render quality, dither toggle and shade info if any of them has changed
BOOL SetRenderState(void)
{
	HRESULT rval;

	// Set the number of buffers so D3DRM can keep track of extents properly
	rval = myglobs.dev->SetBufferCount(d3dapp->bFullscreen &&
                                       d3dapp->bBackBufferInVideo ? 2 : 1);
	if (rval != D3DRM_OK) 
	{
		Msg("Setting the buffer count failed.\n%s", D3DAppErrorToString(rval));
		return FALSE;
	}

   // Set the render quality (light toggle, fill mode, shade mode)
	if (myglobs.dev->GetQuality() != myglobs.RenderQuality) 
	{
		rval = myglobs.dev->SetQuality(myglobs.RenderQuality);
		if (rval != D3DRM_OK) 
		{
         Msg("Setting the render quality failed.\n%s",
                D3DAppErrorToString(rval));
         return FALSE;
		}
	}

   // Set dithering toggle
	if (myglobs.dev->GetDither() != myglobs.bDithering) 
	{
		rval = myglobs.dev->SetDither(myglobs.bDithering);
		if (rval != D3DRM_OK) 
		{
         Msg("Setting dither mode failed.\n%s", D3DAppErrorToString(rval));
         return FALSE;
		}
	}

   // Set the texture quality (point or linear filtering)
	if (myglobs.dev->GetTextureQuality() != myglobs.TextureQuality) 
	{
		rval = myglobs.dev->SetTextureQuality(myglobs.TextureQuality);
		if (rval != D3DRM_OK) 
		{
         Msg("Setting texture quality failed.\n%s",
             D3DAppErrorToString(rval));
         return FALSE;
		}
	}
   // Set shade info based on current bits per pixel
	switch (d3dapp->ThisMode.bpp) 
	{
	case 8:
		if (FAILED(myglobs.dev->SetShades(1)))
          goto shades_error;
      if (FAILED(lpD3DRM->SetDefaultTextureColors(256)))
          goto shades_error;
      if (FAILED(lpD3DRM->SetDefaultTextureShades(1)))
          goto shades_error;
      break;
  case 16:
      if (FAILED(myglobs.dev->SetShades(1)))
          goto shades_error;
      if (FAILED(lpD3DRM->SetDefaultTextureColors(65536)))
          goto shades_error;
      if (FAILED(lpD3DRM->SetDefaultTextureShades(1)))
          goto shades_error;
      break;
  case 24:
  case 32:
      if (FAILED(myglobs.dev->SetShades(256)))
          goto shades_error;
      if (FAILED(lpD3DRM->SetDefaultTextureColors(64)))
          goto shades_error;
      if (FAILED(lpD3DRM->SetDefaultTextureShades(256)))
          goto shades_error;
      break;
	}
	return TRUE;

shades_error:
    Msg("A failure occurred while setting color shade information.\n");
    return FALSE;
}

/****************************************************************************/
/*          Initialization, error reporting and release functions.          */
/****************************************************************************/
// CleanUpAndPostQuit
// Release all D3D objects, post a quit message and set the bQuit flag
void CleanUpAndPostQuit(void)
{
	if (myglobs.bQuit)
	{
		return;
	}
	if (!D3DAppDestroy())
	{
		ReportD3DAppError();
	}
	RELEASE(myglobs.scene);
	RELEASE(myglobs.camera);
	RELEASE(lpD3DRM);
	myglobs.bQuit = TRUE;
	PostQuitMessage( 0 );
}

// ReportD3DAppError
// Reports an error during a d3d app call.
void ReportD3DAppError(void)
{
   Msg("%s", D3DAppLastErrorString());
}

// Message output for error notification.
void __cdecl Msg( LPSTR fmt, ... )
{
	char buff[256];

	wvsprintf(buff, fmt, (char *)(&fmt+1));
	lstrcat(buff, "\r\n");
	OutputDebugString(buff);
}

// D3DRMErrorToString
// Allows the samples to return error strings.
char* D3DRMErrorToString(HRESULT error)
{
    return D3DAppErrorToString(error);
}
//
BOOL RenderGame(void)
{
	if (GameStates.IsNetplay)
	{
		ReceiveNetMessages();
		ProcessRcvMsgs();          //processing received messages.
		PrepareMsgToSend();        //prepare all messages to be sent.
		SendNetMessages();
	}

	if (GameStates.IsNetplay && Page == pg_GAMEPLAY && !beSynchronous)
	{
		;
	}
	else
	{
		if (bBYRenderingIsOK)
		{
			if (!BYRender())
			{
				return TRUE;
			}
		}
	}

	if (GameStates.IsNetplay)
      HasKey = FALSE;               // clear KB Input flag.
	return FALSE;
}
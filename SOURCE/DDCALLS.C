/*
$Header:   H:/pvcs/pvcsproj/gomand3d.prj/ddcalls.c_v   1.9   May 07 1997 16:55:40   JEREMIAH  $

$Log:   H:/pvcs/pvcsproj/gomand3d.prj/ddcalls.c_v  $
 * 
 *    Rev 1.9   May 07 1997 16:55:40   JEREMIAH
 * Separated stretch flags into separate 
 * structure.  Added bWillStretch.  Allowed
 * stretch to be selectable from window size
 * menu.
 * 
 *    Rev 1.8   28 Apr 1997 17:28:06   JEREMIAH
 * Fixed check for bStretch when attaching
 * ZBuffer.
 * 
 *    Rev 1.7   28 Apr 1997 10:15:06   TIM
 * Made mods for s3 stretch
 * 
 *    Rev 1.6   24 Feb 1997 11:40:48   BO
 * removed one bug which sets palette incorrectly.
 * 
 *    Rev 1.5   06 Feb 1997 08:15:08   BRUCE
 * removed uninteresting warning.
 * 
 *    Rev 1.4   17 Dec 1996 10:55:56   JEREMIAH
 * Changed by Bo.  Added support for 512
 * mode.
 * 
 *    Rev 1.3   03 Dec 1996 11:58:08   JEREMIAH
 * Added 512x384 resolutions to the allowable
 * resolution list.
 * 
 *    Rev 1.2   19 Nov 1996 13:32:50   JEREMIAH
 * Excluded 32-bit color modes as well as 
 * 24-bit color modes.
 * 
 *    Rev 1.1   Nov 01 1996 12:00:38   JEREMIAH
 * Changed by Bo.  Removed unused 
 * statements.
*/

#include "d3dappi.h"
#include "wrapper.h"
/***************************************************************************/
/*                         Direct Draw Creation                            */
/***************************************************************************/
/*
 * D3DAppIDDEnumCallback
 * Callback function used during enumeration of DirectDraw drivers.
 * During enumeration, if a 3D capable hardware device is found, it is 
 * created and *(LPDIRECTDRAW*)lpContext is set to it.  Otherwise, does
 * nothing.
 */
BOOL FAR PASCAL D3DAppIDDEnumCallback(GUID FAR* lpGUID, LPSTR lpDriverDesc,
                                      LPSTR lpDriverName, LPVOID lpContext)
{
    LPDIRECTDRAW lpDD;
    DDCAPS DriverCaps, HELCaps;

    /*
     * A NULL GUID* indicates the DirectDraw HEL which we are not interested
     * in at the moment.
     */
    if (lpGUID) {
        /*
         * Create the DirectDraw device using this driver.  If it fails,
         * just move on to the next driver.
         */
        if (FAILED(DirectDrawCreate(lpGUID, &lpDD, NULL))) {
            return DDENUMRET_OK;
        }
        /*
         * Get the capabilities of this DirectDraw driver.  If it fails,
         * just move on to the next driver.
         */
        memset(&DriverCaps, 0, sizeof(DDCAPS));
        DriverCaps.dwSize = sizeof(DDCAPS);
        memset(&HELCaps, 0, sizeof(DDCAPS));
        HELCaps.dwSize = sizeof(DDCAPS);
        if (FAILED(lpDD->lpVtbl->GetCaps(lpDD, &DriverCaps, &HELCaps))) {
            lpDD->lpVtbl->Release(lpDD);
            return DDENUMRET_OK;
        }
        if (DriverCaps.dwCaps & DDCAPS_3D) {
            /*
             * We have found a 3d hardware device.  Return the DD object
             * and stop enumeration.
             */
            d3dappi.bIsPrimary = FALSE;
            *(LPDIRECTDRAW*)lpContext = lpDD;
            return DDENUMRET_CANCEL;
        }       
        lpDD->lpVtbl->Release(lpDD);
    }
    return DDENUMRET_OK;
}

/****************************************************************************\
 * D3DAppICreateDD                                                           *
 * Creates the DirectDraw device and saves the current palette. If a 3D      *
 * capable DD driver is available, use it as the DD device, otherwise, use   *
 * the HEL.  It is assumed that a 3D capable DD hardware driver is not the   *
 * primary device and hence cannot operate in a window (ie it's a fullscreen *
 * only device displaying on a second monitor).  Valid flags:                *
 *     D3DAPP_ONLYDDEMULATION    Always use the DirectDraw HEL               *
\****************************************************************************/
BOOL D3DAppICreateDD(DWORD flags)
{
	HDC hdc;
	int i;
	LPDIRECTDRAW lpDD = NULL;

	// If we aren't forced to use the DirectDraw HEL, search for a 3D capable
	// DirectDraw hardware driver and create it.
	if (!(flags & D3DAPP_ONLYDDEMULATION)) 
	{
		LastError = DirectDrawEnumerate(D3DAppIDDEnumCallback, &lpDD);
		if (LastError != DD_OK) 
		{
			D3DAppISetErrorString("DirectDrawEnumerate failed.\n%s",
                                  D3DAppErrorToString(LastError));
         return FALSE;
		}
	}
    if (!lpDD) {
        /*
         * If we haven't created a hardware DD device by now, resort to HEL
         */
        d3dappi.bIsPrimary = TRUE;
        LastError = DirectDrawCreate(NULL, &d3dappi.lpDD, NULL);
        if (LastError != DD_OK) {
            D3DAppISetErrorString("DirectDrawCreate failed.\n%s",
                                  D3DAppErrorToString(LastError));
            return FALSE;
        }
    } else {
        d3dappi.lpDD = lpDD;
    }
    /*
     * Save the original palette for when we are paused.  Just in case we
     * start in a fullscreen mode, put them in ppe.
     */
    hdc = GetDC(NULL);
    GetSystemPaletteEntries(hdc, 0, (1 << 8),
                            (LPPALETTEENTRY)(&Originalppe[0]));
    for (i = 0; i < 256; i++)
        ppe[i] = Originalppe[i];
    ReleaseDC(NULL, hdc);
    return TRUE;
}

/***************************************************************************/
/*                   Enumerating the display modes                         */
/***************************************************************************/
/*
 * EnumDisplayModesCallback
 * Callback to save the display mode information.
 */
static HRESULT
CALLBACK EnumDisplayModesCallback(LPDDSURFACEDESC pddsd, LPVOID lpContext)
{
    /*
     * Very large resolutions cause problems on some hardware.  They are also
     * not very useful for real-time rendering.  We have chosen to disable
     * them by not reporting them as available.
     */
    if (pddsd->dwWidth > 1024 || pddsd->dwHeight > 768)
        return DDENUMRET_OK;

	if (pddsd->dwWidth != 640 && 
		 pddsd->dwWidth != 320 &&
		 pddsd->dwWidth != 512)
		return DDENUMRET_OK;	// BY BO

	if ((pddsd->ddpfPixelFormat.dwRGBBitCount==24) || (pddsd->ddpfPixelFormat.dwRGBBitCount==32))
		return DDENUMRET_OK;	// BY BO

    /*
     * Save this mode at the end of the mode array and increment mode count
     */
    d3dappi.Mode[d3dappi.NumModes].w = pddsd->dwWidth;
    d3dappi.Mode[d3dappi.NumModes].h = pddsd->dwHeight;
    d3dappi.Mode[d3dappi.NumModes].bpp = pddsd->ddpfPixelFormat.dwRGBBitCount;
    d3dappi.Mode[d3dappi.NumModes].bThisDriverCanDo = FALSE;
    d3dappi.NumModes++;
    if (d3dappi.NumModes == D3DAPP_MAXMODES)
        return DDENUMRET_CANCEL;
    else
        return DDENUMRET_OK;
}

/*
 * CompareModes
 * Compare two display modes during sorting.  Modes are sorted by depth and
 * then resolution.
 */
static int
_cdecl CompareModes(const void* element1, const void* element2) {
    D3DAppMode *lpMode1, *lpMode2;

    lpMode1 = (D3DAppMode*)element1;
    lpMode2 = (D3DAppMode*)element2;

    if (lpMode1->bpp > lpMode2->bpp)
        return -1;
    else if (lpMode2->bpp > lpMode1->bpp)
        return 1;
    else if (lpMode1->w > lpMode2->w)
        return -1;
    else if (lpMode2->w > lpMode1->w)
        return 1;
    else if (lpMode1->h > lpMode2->h)
        return -1;
    else if (lpMode2->h > lpMode1->h)
        return 1;
    else
        return 0;
}

/*
 * EnumerateDisplayModes
 * Generates the list of available display modes.
 */
BOOL D3DAppIEnumDisplayModes(void)
{
    int i;
//	 char ftp[127];
    /*
     * Get a list of available display modes from DirectDraw
     */
    d3dappi.NumModes = 0;
    LastError = d3dappi.lpDD->lpVtbl->EnumDisplayModes(d3dappi.lpDD, 0, NULL,
                                                0, EnumDisplayModesCallback);
    if(LastError != DD_OK ) {
        D3DAppISetErrorString("EnumDisplayModes failed.\n%s",
                              D3DAppErrorToString(LastError));
        d3dappi.NumModes = 0;
        return FALSE;
    }
    /*
     * Sort the list of display modes
     */
    qsort((void *)&d3dappi.Mode[0], (size_t)d3dappi.NumModes, sizeof(D3DAppMode),
          CompareModes);
    /*
     * Pick a default display mode.  640x480x16 is a very good mode for
     * rendering, so choose it over all others.  Otherwise, just take the
     * first one.  This selection may be overriden later if a driver is
     * created which cannot render in this mode.
     */
    d3dappi.CurrMode = 0;
    for (i = 0; i < d3dappi.NumModes; i++) 
	 {
        if (d3dappi.Mode[i].w == 640 && d3dappi.Mode[i].h == 480 &&
            d3dappi.Mode[i].bpp == 16)
		  {
            d3dappi.CurrMode = i;
		  }

    }
    memcpy(&d3dappi.ThisMode, &d3dappi.Mode[d3dappi.CurrMode],
           sizeof(D3DAppMode));
    return TRUE;
}

/***************************************************************************/
/*               Creating Front and Back Buffers (and misc surf funcs)     */
/***************************************************************************/
/*
 * D3DAppICreateSurface
 * Create a DirectDraw Surface of the given description.  Using this function
 * ensures that all surfaces end up in system memory if that option was set.
 * Returns the result of the CreateSurface call.
 */
HRESULT
D3DAppICreateSurface(LPDDSURFACEDESC lpDDSurfDesc,
                LPDIRECTDRAWSURFACE FAR *lpDDSurface) {
    HRESULT result;
    if (d3dappi.bOnlySystemMemory)
        lpDDSurfDesc->ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
    result = d3dappi.lpDD->lpVtbl->CreateSurface(d3dappi.lpDD, lpDDSurfDesc,
                                                 lpDDSurface, NULL);
    return result;
}

/*
 * D3DAppIGetSurfDesc
 * Get the description of the given surface.  Returns the result of the
 * GetSurfaceDesc call.
 */
HRESULT
D3DAppIGetSurfDesc(LPDDSURFACEDESC lpDDSurfDesc,LPDIRECTDRAWSURFACE lpDDSurf)
{
    HRESULT result;
    memset(lpDDSurfDesc, 0, sizeof(DDSURFACEDESC));
    lpDDSurfDesc->dwSize = sizeof(DDSURFACEDESC);
    result = lpDDSurf->lpVtbl->GetSurfaceDesc(lpDDSurf, lpDDSurfDesc);
    return result;
}

/*
 * D3DAppICreateBuffers
 * Creates the front and back buffers for the window or fullscreen case
 * depending on the bFullscreen flag.  In the window case, bpp is ignored.
 */
BOOL
D3DAppICreateBuffers(HWND hwnd, int w, int h, int bpp, BOOL bFullscreen)
{
    DDSURFACEDESC ddsd;
    DDSCAPS ddscaps;
	DDSCAPS theCAPS;


    /*
     * Release any old objects that might be lying around.  This should have
     * already been taken care of, but just in case...
     */
    RELEASE(lpClipper);
    RELEASE(d3dappi.lpBackBuffer);
	//Tim Stretch:
	if(sStretch.bStretch) RELEASE(d3dappi.lpBackBuffer2);

    RELEASE(d3dappi.lpFrontBuffer);
    /*
     * The size of the buffers is going to be w x h, so record it now
     */
    if (w < D3DAPP_WINDOWMINIMUM)
        w = D3DAPP_WINDOWMINIMUM;
    if (h < D3DAPP_WINDOWMINIMUM)
        h = D3DAPP_WINDOWMINIMUM;
    szBuffers.cx = w;
    szBuffers.cy = h;

    if (bFullscreen) 
	{

		//Tim Stretch: set up three stretch buffers

		if (sStretch.bStretch)

		{

			// Create the primary surface (YCbCr)


			// Set screen resolution (width x height x depth).
			/*
			gResult = gDirectDraw->SetDisplayMode (pel_width, pel_height, 
			pel_res);
			*/

			memset(&ddsd,0,sizeof(DDSURFACEDESC));

			ddsd.dwSize = sizeof(ddsd);
			ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH | DDSD_CAPS | 
			DDSD_BACKBUFFERCOUNT;
			ddsd.dwWidth = w/2;
			ddsd.dwHeight = h/2;
			ddsd.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_FLIP | 
			DDSCAPS_OVERLAY | DDSCAPS_COMPLEX | DDSCAPS_3DDEVICE;

			//ddsd.ddpfPixelFormat.dwSize   = sizeof (DDPIXELFORMAT); 
			//ddsd.ddpfPixelFormat.dwFlags  = DDPF_YUV | DDPF_FOURCC; 
			//ddsd.ddpfPixelFormat.dwFourCC = 0x32595559; 
			//'YUY2' ddsd.ddpfPixelFormat.dwYUVBitCount = 16;

			/*The following masks may not be required.

			ddsd.ddpfPixelFormat.dwYBitMask = 0xFF00FF00; 
			ddsd.ddpfPixelFormat.dwUBitMask = 0x00FF0000; 
			ddsd.ddpfPixelFormat.dwVBitMask = 0x00FF0000; 
			ddsd.ddpfPixelFormat.dwYUVAlphaBitMask = 0x00000000;
*/
			ddsd.dwBackBufferCount = 2; 
			LastError = d3dappi.lpDD->lpVtbl->CreateSurface(d3dappi.lpDD, &ddsd,
                                              &d3dappi.lpBackBuffer, NULL);

	
			if(LastError != DD_OK) {
				D3DAppISetErrorString("CreateSurface for fullscreen flipping surface failed.\n%s",
                                  D3DAppErrorToString(LastError));
				goto exit_with_error;
			}


			// Create the display buffer // 
			ddsd.dwFlags = DDSD_CAPS;
			ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | 
			DDSCAPS_VIDEOMEMORY;
			LastError = D3DAppICreateSurface(&ddsd, &d3dappi.lpFrontBuffer);

			if(LastError != DD_OK) {
				D3DAppISetErrorString("CreateSurface for fullscreen flipping surface failed.\n%s",
                                  D3DAppErrorToString(LastError));
				goto exit_with_error;
			}


			// Set up a second back buffer
		
			theCAPS.dwCaps = DDSCAPS_BACKBUFFER;
			LastError = d3dappi.lpBackBuffer->lpVtbl->GetAttachedSurface(d3dappi.lpBackBuffer, &theCAPS, &d3dappi.lpBackBuffer2); 
			if(LastError != DD_OK) {
				D3DAppISetErrorString("CreateSurface for fullscreen flipping surface failed.\n%s",
                                  D3DAppErrorToString(LastError));
				goto exit_with_error;
			}
			
			d3dappi.bBackBufferInVideo =
					  (ddsd.ddsCaps.dwCaps & DDSCAPS_VIDEOMEMORY) ? TRUE : FALSE;

		

			// Loop and display each BMP

		//	gResult = gPrimary->UpdateOverlay (&rcRect, gBack, &rcRect, 
		//	DDOVER_SHOW, NULL);

			// Check the flags returns by overlay function.

		//	check_updateoverlay ();
		//	CHECKRESULT ();


		}
		else 
		{
			/*
			 * Create a complex flipping surface for fullscreen mode with one
			 * back buffer.
			 */
			memset(&ddsd,0,sizeof(DDSURFACEDESC));
			ddsd.dwSize = sizeof( ddsd );
			ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
			ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP |
				DDSCAPS_3DDEVICE | DDSCAPS_COMPLEX;
			ddsd.dwBackBufferCount = 1;
			LastError = D3DAppICreateSurface(&ddsd, &d3dappi.lpFrontBuffer);
			if(LastError != DD_OK) {
				D3DAppISetErrorString("CreateSurface for fullscreen flipping surface failed.\n%s",
									  D3DAppErrorToString(LastError));
				goto exit_with_error;
			}
			/* 
			 * Obtain a pointer to the back buffer surface created above so we
			 * can use it later.  For now, just check to see if it ended up in
			 * video memory (FYI).
			 */
			ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
			LastError = d3dappi.lpFrontBuffer->lpVtbl->GetAttachedSurface(d3dappi.lpFrontBuffer, &ddscaps, &d3dappi.lpBackBuffer);
			if(LastError != DD_OK) {
				D3DAppISetErrorString("GetAttachedSurface failed to get back buffer.\n%s",
									  D3DAppErrorToString(LastError));
				goto exit_with_error;
			}
			LastError = D3DAppIGetSurfDesc(&ddsd, d3dappi.lpBackBuffer);
			if (LastError != DD_OK) {
				D3DAppISetErrorString("Failed to get surface description of back buffer.\n%s",
									  D3DAppErrorToString(LastError));
				goto exit_with_error;
			}
			d3dappi.bBackBufferInVideo =
					(ddsd.ddsCaps.dwCaps & DDSCAPS_VIDEOMEMORY) ? TRUE : FALSE;
		}
	}
    else 
	{
        /*
         * In the window case, create a front buffer which is the primary
         * surface and a back buffer which is an offscreen plane surface.
         */
        memset(&ddsd,0,sizeof(DDSURFACEDESC));
        ddsd.dwSize = sizeof(DDSURFACEDESC);
        ddsd.dwFlags = DDSD_CAPS;
        ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
        /*
         * If we specify system memory when creating a primary surface, we
         * won't get the actual primary surface in video memory.  So, don't
         * use D3DAppICreateSurface().
         */
        LastError = d3dappi.lpDD->lpVtbl->CreateSurface(d3dappi.lpDD,
                                        &ddsd, &d3dappi.lpFrontBuffer, NULL);
        if(LastError != DD_OK ) {
            D3DAppISetErrorString("CreateSurface for window front buffer failed.\n%s",
                                  D3DAppErrorToString(LastError));
            goto exit_with_error;
        }
        ddsd.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
        ddsd.dwWidth = w;
        ddsd.dwHeight = h;
        ddsd.ddsCaps.dwCaps= DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
        LastError = D3DAppICreateSurface(&ddsd, &d3dappi.lpBackBuffer);
        if (LastError != DD_OK) {
            D3DAppISetErrorString("CreateSurface for window back buffer failed.\n%s",
                                  D3DAppErrorToString(LastError));
            goto exit_with_error;
        }
        /*
         * Check to see if the back buffer is in video memory (FYI).
         */
        LastError = D3DAppIGetSurfDesc(&ddsd, d3dappi.lpBackBuffer);
        if (LastError != DD_OK) {
            D3DAppISetErrorString("Failed to get surface description for back buffer.\n%s",
                                  D3DAppErrorToString(LastError));
            goto exit_with_error;
        }
        d3dappi.bBackBufferInVideo =
                  (ddsd.ddsCaps.dwCaps & DDSCAPS_VIDEOMEMORY) ? TRUE : FALSE;
        /*
         * Create the DirectDraw Clipper object and attach it to the window
         * and front buffer.
         */
        LastError = d3dappi.lpDD->lpVtbl->CreateClipper(d3dappi.lpDD, 0,
                                                        &lpClipper, NULL);
        if(LastError != DD_OK ) {
            D3DAppISetErrorString("CreateClipper failed.\n%s",
                                  D3DAppErrorToString(LastError));
            goto exit_with_error;
        }
        LastError = lpClipper->lpVtbl->SetHWnd(lpClipper, 0, hwnd);
        if(LastError != DD_OK ) {
            D3DAppISetErrorString("Attaching clipper to window failed.\n%s",
                                  D3DAppErrorToString(LastError));
            goto exit_with_error;
        }
        LastError =
             d3dappi.lpFrontBuffer->lpVtbl->SetClipper(d3dappi.lpFrontBuffer,
                                                       lpClipper);
        if(LastError != DD_OK ) {
            D3DAppISetErrorString("Attaching clipper to front buffer failed.\n%s",
                                  D3DAppErrorToString(LastError));
            goto exit_with_error;
        }
		   D3DAppIClearBuffers();
    }

 
    return TRUE;

exit_with_error:
    RELEASE(d3dappi.lpFrontBuffer);
    RELEASE(d3dappi.lpBackBuffer);
	//Tim Stretch:
	if(sStretch.bStretch) RELEASE(d3dappi.lpBackBuffer2);

    RELEASE(lpClipper);
    return FALSE;
}

/*
 * D3DAppICheckForPalettized
 * If the front/back buffer is palettized, we need to create a palette.
 */
BOOL
D3DAppICheckForPalettized(void)
{
    DDSURFACEDESC ddsd;
    /*
     * Get the back buffer surface description and check to see if it's
     * palettized
     */
    LastError = D3DAppIGetSurfDesc(&ddsd, d3dappi.lpBackBuffer);
    if (LastError != DD_OK) {
        D3DAppISetErrorString("Failed to get surface description for back buffer for palettizing.\n%s",
                              D3DAppErrorToString(LastError));
        goto exit_with_error;
    }
    bPrimaryPalettized = 
        (ddsd.ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED8) ? TRUE : FALSE;

    if (bPrimaryPalettized) {
        int i;
        /*
         * Get the current palette.
         */
        HDC hdc = GetDC(NULL);
        GetSystemPaletteEntries(hdc, 0, (1 << 8), ppe);
        ReleaseDC(NULL, hdc);
        /*
         * Change the flags on the palette entries to allow D3D to change
         * some of them.  In the window case, we must not change the top and
         * bottom ten (system colors), but in a fullscreen mode we can have
         * all but the first and last.
         */
        if (!d3dappi.bFullscreen) {
            for (i = 0; i < 10; i++) ppe[i].peFlags = D3DPAL_READONLY;
            for (i = 10; i < 256 - 10; i++) ppe[i].peFlags = PC_RESERVED;
            for (i = 256 - 10; i < 256; i++) ppe[i].peFlags = D3DPAL_READONLY;
        } else {
				lpPalette=BYDDLoadPalette(d3dappi.lpDD);
        }
        /*
         * Create a palette using the old colors and new flags
         */

		  if (!d3dappi.bFullscreen)
		  {
			  LastError = d3dappi.lpDD->lpVtbl->CreatePalette(d3dappi.lpDD,
															 DDPCAPS_8BIT | DDPCAPS_INITIALIZE,
															 ppe, &lpPalette, NULL);
			  if (LastError != DD_OK) {
					D3DAppISetErrorString("CreatePalette failed.\n%s",
												 D3DAppErrorToString(LastError));
					goto exit_with_error;
			  }
		  }
        /*
         * Set this as the front and back buffers' palette
         */
		  /*
        LastError =
               d3dappi.lpFrontBuffer->lpVtbl->SetPalette(d3dappi.lpBackBuffer,
                                                        lpPalette);
        if(LastError != DD_OK ) {
            D3DAppISetErrorString("SetPalette failed on front buffer.\n%s",
                                  D3DAppErrorToString(LastError));
            goto exit_with_error;
        } */
        LastError =
               d3dappi.lpBackBuffer->lpVtbl->SetPalette(d3dappi.lpBackBuffer,
                                                        lpPalette);
        if(LastError != DD_OK ) 
		  {
            D3DAppISetErrorString("SetPalette failed on back buffer.\n%s",
                                  D3DAppErrorToString(LastError));
            goto exit_with_error;
        }
        LastError =
             d3dappi.lpFrontBuffer->lpVtbl->SetPalette(d3dappi.lpFrontBuffer,
                                                       lpPalette);
        if(LastError != DD_OK ) 
		  {
            D3DAppISetErrorString("SetPalette failed on front buffer.\n%s",
                                  D3DAppErrorToString(LastError));
            goto exit_with_error;
        }
        /*
         * The palette is now valid, so set it again on anyt WM_ACTIVATE
         */
        bPaletteActivate = TRUE;
    }
    return TRUE;
exit_with_error:
    RELEASE(lpPalette);
    return FALSE;
}

/***************************************************************************/
/*                           Creation of Z-Buffer                          */
/***************************************************************************/
/*
 * D3DAppICreateZBuffer
 * Create a Z-Buffer of the appropriate depth and attach it to the back
 * buffer.
 */
BOOL
D3DAppICreateZBuffer(int w, int h, int driver)
{
    DDSURFACEDESC ddsd;
    DWORD devDepth;
    /*
     * Release any Z-Buffer that might be around just in case.
     */
    RELEASE(d3dappi.lpZBuffer);
    
    /*
     * If this driver does not do z-buffering, don't create a z-buffer
     */
    if (!d3dappi.Driver[driver].bDoesZBuffer)
        return TRUE;

    memset(&ddsd, 0 ,sizeof(DDSURFACEDESC));
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS |
                   DDSD_ZBUFFERBITDEPTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER;
	
	//Tim Stretch: z buffer is also smaller with a stretch
	if (sStretch.bStretch)
	{
		ddsd.dwHeight = h/2;
		ddsd.dwWidth = w/2;
	}
	else
	{
		ddsd.dwHeight = h;
		ddsd.dwWidth = w;
	}

    /*
     * If this is a hardware D3D driver, the Z-Buffer MUST end up in video
     * memory.  Otherwise, it MUST end up in system memory.
     */
    if (d3dappi.Driver[driver].bIsHardware)
        ddsd.ddsCaps.dwCaps |= DDSCAPS_VIDEOMEMORY;
    else
        ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
    /*
     * Get the Z buffer bit depth from this driver's D3D device description
     */
    devDepth = d3dappi.Driver[driver].Desc.dwDeviceZBufferBitDepth;
    if (devDepth & DDBD_32)
        ddsd.dwZBufferBitDepth = 32;
    else if (devDepth & DDBD_24)
        ddsd.dwZBufferBitDepth = 24;
    else if (devDepth & DDBD_16)
        ddsd.dwZBufferBitDepth = 16;
    else if (devDepth & DDBD_8)
        ddsd.dwZBufferBitDepth = 8;
    else {
        D3DAppISetErrorString("Unsupported Z-buffer depth requested by device.\n");
        return FALSE;
    }
    LastError = d3dappi.lpDD->lpVtbl->CreateSurface(d3dappi.lpDD, &ddsd,
                                                    &d3dappi.lpZBuffer,
                                                    NULL);
    if(LastError != DD_OK) {
        D3DAppISetErrorString("CreateSurface for Z-buffer failed.\n%s",
                              D3DAppErrorToString(LastError));
        goto exit_with_error;
    }
    /*
     * Attach the Z-buffer to the back buffer so D3D will find it
     */

	  /*
     * Attach the Z-buffer to the back buffer so D3D will find it
     */


	   if (sStretch.bStretch)

		   LastError =
		      d3dappi.lpBackBuffer2->lpVtbl->AddAttachedSurface(d3dappi.lpBackBuffer2,
															d3dappi.lpZBuffer);
      else
         LastError =
		      d3dappi.lpBackBuffer->lpVtbl->AddAttachedSurface(d3dappi.lpBackBuffer,
															d3dappi.lpZBuffer);


		if(LastError != DD_OK) {
			D3DAppISetErrorString("AddAttachedBuffer failed for Z-Buffer.\n%s",
								  D3DAppErrorToString(LastError));
			goto exit_with_error;
		}
	
    /*
     * Find out if it ended up in video memory.
     */
    LastError = D3DAppIGetSurfDesc(&ddsd, d3dappi.lpZBuffer);
    if (LastError != DD_OK) {
        D3DAppISetErrorString("Failed to get surface description of Z buffer.\n%s",
                              D3DAppErrorToString(LastError));
        goto exit_with_error;
    }
    d3dappi.bZBufferInVideo =
                  (ddsd.ddsCaps.dwCaps & DDSCAPS_VIDEOMEMORY) ? TRUE : FALSE;
    if (d3dappi.Driver[driver].bIsHardware && !d3dappi.bZBufferInVideo) {
        D3DAppISetErrorString("Could not fit the Z-buffer in video memory for this hardware device.\n");
        goto exit_with_error;
    }

    return TRUE;

exit_with_error:
    RELEASE(d3dappi.lpZBuffer);
    return FALSE;
}

/***************************************************************************/
/*                             WM_SIZE Handler                             */
/***************************************************************************/
/*
 * D3DAppIHandleWM_SIZE
 * Processes the WM_SIZE message.  Resizes all the buffers and re-creates
 * device if necessary.
 */
BOOL
D3DAppIHandleWM_SIZE(LRESULT* lresult, HWND hwnd, UINT message,
                     WPARAM wParam, LPARAM lParam)
{
    int w, h, i;
    /*
     * If we have minimzied, take note and call the default window proc
     */
    if (wParam == SIZE_MINIMIZED) {
        d3dappi.bMinimized = TRUE;
        *lresult = DefWindowProc(hwnd, message, wParam, lParam);
        return TRUE;
    }
    /*
     * In fullscreen mode, restore our surfaces and let DDraw take
     * care of the rest.
     */
    if (d3dappi.bFullscreen) {
        D3DAppIValidateDirtyRects();
        D3DAppCheckForLostSurfaces();
        d3dappi.bMinimized = FALSE;
        *lresult = DefWindowProc(hwnd, message, wParam, lParam);
        return TRUE;
    }
    /*
     * If we are minimized, this is the un-minimized size message.
     */
    if (d3dappi.bMinimized) {
        /*
         * Restore our surfaces and update the dirty rectangle info
         */
        D3DAppIValidateDirtyRects();
        D3DAppCheckForLostSurfaces();
        d3dappi.bMinimized = FALSE;
        *lresult = DefWindowProc(hwnd, message, wParam, lParam);
        return TRUE;
    }
    /*
     * Since we are still here, this must be a regular, window resize
     * message.  A new viewport will definitely be needed, but the
     * device and buffers will only be re-created if they have gotten bigger
     * or change size by a very large amount.
     */
    D3DAppIGetClientWin(hwnd);
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    /*
     * If w and h are under the minimum, create buffers of the minimum size
     */
    if (w < D3DAPP_WINDOWMINIMUM)
        w = D3DAPP_WINDOWMINIMUM;
    if (h < D3DAPP_WINDOWMINIMUM)
        h = D3DAPP_WINDOWMINIMUM;
    /*
     * Destroy the viewport and all execute buffers
     */
    d3dappi.bRenderingIsOK = FALSE;
    ATTEMPT(D3DAppICallDeviceDestroyCallback());
    /*
     * Only create a new device and buffers if they changed significantly,
     * otherwise just make sure the old buffers aren't lost.
     */
    if ((w > szBuffers.cx || h > szBuffers.cy) ||
        (w < szBuffers.cx / 2 || h < szBuffers.cy / 2)) {
        /*
         * Release the device
         */
        RELEASE(d3dappi.lpD3DDevice);
        /*
         * Release the old buffers
         */
        RELEASE(d3dappi.lpZBuffer);
        RELEASE(lpPalette);
        RELEASE(lpClipper);
        RELEASE(d3dappi.lpBackBuffer);
		//Tim Stretch:
		if(sStretch.bStretch) RELEASE(d3dappi.lpBackBuffer2);

        RELEASE(d3dappi.lpFrontBuffer);
        /*
         * Create new ones
         */
        ATTEMPT(D3DAppICreateBuffers(hwnd, w, h, D3DAPP_BOGUS, FALSE));
        ATTEMPT(D3DAppICheckForPalettized());
        ATTEMPT(D3DAppICreateZBuffer(w, h, d3dappi.CurrDriver));
        /*
         * Create the driver
         */
        ATTEMPT(D3DAppICreateDevice(d3dappi.CurrDriver));
        /*
         * Since the driver did not change, the texture surfaces are still valid.
         * We just need to get new handles.
         */
        if (d3dappi.ThisDriver.bDoesTextures) {
            for (i = 0; i < d3dappi.NumTextures; i++) {
                D3DAppIGetTextureHandle(i);
            }
        }
    } else {
        D3DAppCheckForLostSurfaces();
    }
    /*
     * Call the device create callback to create the viewport, set the render
     * state and clear the dirty rectangle info
     */
    ATTEMPT(D3DAppICallDeviceCreateCallback(w, h));
    ATTEMPT(D3DAppISetRenderState());
    D3DAppIValidateDirtyRects();
    d3dappi.bRenderingIsOK = TRUE;
    /*
     * Call the default window proc
     */
    *lresult = DefWindowProc(hwnd, message, wParam, lParam);
    return TRUE;
exit_with_error:
    D3DAppICallDeviceDestroyCallback();
    RELEASE(d3dappi.lpD3DDevice);
    RELEASE(d3dappi.lpZBuffer);
    RELEASE(lpPalette);
    RELEASE(lpClipper);
    RELEASE(d3dappi.lpBackBuffer);
	//Tim Stretch:
	if(sStretch.bStretch) RELEASE(d3dappi.lpBackBuffer2);

    RELEASE(d3dappi.lpFrontBuffer);
    return FALSE;
}

/***************************************************************************/
/*              Setting the display mode and cooperative level             */
/***************************************************************************/
/*
 * D3DAppISetCoopLevel
 * Set the cooperative level to exclusive mode for fullscreen and normal for
 * a window.  Set the bIgnoreWM_SIZE flag because SetCooperativeLevel
 * generates a WM_SIZE message you do not have to resize the buffers on.
 */
BOOL
D3DAppISetCoopLevel(HWND hwnd, BOOL bFullscreen)
{
    if (bFullscreen) {
        bIgnoreWM_SIZE = TRUE;
      d3dappi.lpDD->lpVtbl->SetCooperativeLevel(d3dappi.lpDD,
																	hwnd, DDSCL_EXCLUSIVE | 
																	DDSCL_FULLSCREEN | 
																	DDSCL_ALLOWMODEX);

        bIgnoreWM_SIZE = FALSE;
        if(LastError != DD_OK ) {
            D3DAppISetErrorString("SetCooperativeLevel to fullscreen failed.\n%s",
                                  D3DAppErrorToString(LastError));
            return FALSE;
        }
        d3dappi.bFullscreen = TRUE;
    } else {
        bIgnoreWM_SIZE = TRUE;
        LastError = d3dappi.lpDD->lpVtbl->SetCooperativeLevel(d3dappi.lpDD,
                                                         hwnd, DDSCL_NORMAL);
        bIgnoreWM_SIZE = FALSE;
        if(LastError != DD_OK ) {
            D3DAppISetErrorString("SetCooperativeLevel to normal failed.\n%s",
                                  D3DAppErrorToString(LastError));
            return FALSE;
        }
        d3dappi.bFullscreen = FALSE;
    }
    return TRUE;
}

/*
 * D3DAppISetDisplayMode
 * Set the display mode to the given dimensions and bits per pixel.  The
 * bIgnoreWM_SIZE message is set because the display change generates a
 * WM_SIZE message which we don't want to resize the buffers on.
 */
BOOL
D3DAppISetDisplayMode(int w, int h, int bpp)
{
    d3dappi.ThisMode.w = w; d3dappi.ThisMode.h = h;
    d3dappi.ThisMode.bpp = bpp;
    bIgnoreWM_SIZE = TRUE;
    LastError = d3dappi.lpDD->lpVtbl->SetDisplayMode(d3dappi.lpDD, w, h,
                                                     bpp);
    bIgnoreWM_SIZE = FALSE;
    if(LastError != DD_OK ) {
        D3DAppISetErrorString("SetDisplayMode to %dx%dx%d failed\n%s",
                              w, h, bpp, D3DAppErrorToString(LastError));
        return FALSE;
    }
    return TRUE;
}

/*
 * D3DAppIRestoreDispMode
 * Restores the display mode to the current windows display mode.  The
 * bIgnoreWM_SIZE message is set because the display change generates a
 * WM_SIZE message which we don't want to resize the buffers on.
 */
BOOL
D3DAppIRestoreDispMode(void)
{
    bIgnoreWM_SIZE = TRUE;
    LastError = d3dappi.lpDD->lpVtbl->RestoreDisplayMode(d3dappi.lpDD);
    if (LastError != DD_OK) {
        D3DAppISetErrorString("RestoreDisplayMode failed.\n%s",
                              D3DAppErrorToString(LastError));
        return FALSE;
    }
    bIgnoreWM_SIZE = FALSE;
    return TRUE;
}

/*
 * D3DAppRememberWindowsMode
 * Record the current display mode in d3dappi.WindowsDisplay
 */
BOOL
D3DAppIRememberWindowsMode(void)
{
    DDSURFACEDESC ddsd;

    memset(&ddsd, 0, sizeof(DDSURFACEDESC));
    ddsd.dwSize = sizeof(DDSURFACEDESC);
    LastError = d3dappi.lpDD->lpVtbl->GetDisplayMode(d3dappi.lpDD, &ddsd);
    if (LastError != DD_OK) 
	 {
        D3DAppISetErrorString("Getting the current display mode failed.\n%s",
                              D3DAppErrorToString(LastError));
        return FALSE;
    }
    d3dappi.WindowsDisplay.w = ddsd.dwWidth;
    d3dappi.WindowsDisplay.h = ddsd.dwHeight;
    d3dappi.WindowsDisplay.bpp = ddsd.ddpfPixelFormat.dwRGBBitCount;
    return TRUE;
}

/***************************************************************************/
/*                          Misc DD Utilities                              */
/***************************************************************************/

/*
 * D3DAppIClearBuffers
 * Clear the front and back buffers to black
 */
BOOL
D3DAppIClearBuffers(void)
{
    DDSURFACEDESC ddsd;
    RECT dst;
    DDBLTFX ddbltfx;
    /*
     * Find the width and height of the front buffer by getting its
     * DDSURFACEDESC
     */
    if (d3dappi.lpFrontBuffer) {
        LastError = D3DAppIGetSurfDesc(&ddsd, d3dappi.lpFrontBuffer);
        if (LastError != DD_OK) {
            D3DAppISetErrorString("Failure getting the surface description of the front buffer before clearing.\n%s",
                                  D3DAppErrorToString(LastError));
            return FALSE;
        }
        /*
         * Clear the front buffer to black
         */
        memset(&ddbltfx, 0, sizeof(ddbltfx));
        ddbltfx.dwSize = sizeof(DDBLTFX);
        SetRect(&dst, 0, 0, ddsd.dwWidth, ddsd.dwHeight);
        LastError = d3dappi.lpFrontBuffer->lpVtbl->Blt(d3dappi.lpFrontBuffer,
                                                    &dst, NULL, NULL, 
                                                    DDBLT_COLORFILL | DDBLT_WAIT,
                                                    &ddbltfx);
//        if (LastError != DD_OK) {
//            D3DAppISetErrorString("Clearing the front buffer failed.\n%s",
//                                  D3DAppErrorToString(LastError));
//            return FALSE;
//        }
    }
    if (d3dappi.lpBackBuffer) {
        /*
         * Find the width and height of the back buffer by getting its
         * DDSURFACEDESC
         */
        LastError = D3DAppIGetSurfDesc(&ddsd, d3dappi.lpBackBuffer);
        if (LastError != DD_OK) {
            D3DAppISetErrorString("Failure while getting the surface description of the back buffer before clearing.\n%s",
                                  D3DAppErrorToString(LastError));
            return FALSE;
        }
        /*
         * Clear the back buffer to black
         */
        memset(&ddbltfx, 0, sizeof(ddbltfx));
        ddbltfx.dwSize = sizeof(DDBLTFX);
        SetRect(&dst, 0, 0, ddsd.dwWidth, ddsd.dwHeight);
        LastError = d3dappi.lpBackBuffer->lpVtbl->Blt(d3dappi.lpBackBuffer, &dst,
                                                     NULL, NULL,
                                                     DDBLT_COLORFILL | DDBLT_WAIT,
                                                     &ddbltfx);
        if (LastError != DD_OK) {
            D3DAppISetErrorString("Clearing the front buffer failed.\n%s",
                                  D3DAppErrorToString(LastError));
            return FALSE;
        }
    }
    return TRUE;
}

/*
 * D3DAppIBPPToDDBD
 * Convert an integer bit per pixel number to a DirectDraw bit depth flag
 */
DWORD
D3DAppIBPPToDDBD(int bpp)
{
    switch(bpp) {
        case 1:
            return DDBD_1;
        case 2:
            return DDBD_2;
        case 4:
            return DDBD_4;
        case 8:
            return DDBD_8;
        case 16:
            return DDBD_16;
        case 24:
            return DDBD_24;
        case 32:
            return DDBD_32;
        default:
            return (DWORD)D3DAPP_BOGUS;
    }
}

/*
 * D3DAppTotalVideoMemory
 * Returns the amount of total video memory supported (not free)
 */
DWORD
D3DAppTotalVideoMemory(void)
{
    DDCAPS DriverCaps, HELCaps;
    memset (&DriverCaps, 0, sizeof(DDCAPS));
    DriverCaps.dwSize = sizeof(DDCAPS);
    memset (&HELCaps, 0, sizeof(DDCAPS));
    HELCaps.dwSize = sizeof(DDCAPS);
    LastError = d3dappi.lpDD->lpVtbl->GetCaps(d3dappi.lpDD, &DriverCaps,
                                              &HELCaps);
    if (LastError != DD_OK) {
        D3DAppISetErrorString("Getting DD capabilities failed while checking total video memory.\n%s",
                              D3DAppErrorToString(LastError));
        return 0L;
    }
    if (DriverCaps.dwVidMemTotal)
        return DriverCaps.dwVidMemTotal;
    else
        return HELCaps.dwVidMemTotal;
}

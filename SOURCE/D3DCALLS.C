/*
* $Header:   H:/pvcs/pvcsproj/gomand3d.prj/d3dcalls.c_v   1.23   May 07 1997 16:55:40   JEREMIAH  $
* $Log:   H:/pvcs/pvcsproj/gomand3d.prj/d3dcalls.c_v  $
 * 
 *    Rev 1.23   May 07 1997 16:55:40   JEREMIAH
 * Separated stretch flags into separate 
 * structure.  Added bWillStretch.  Allowed
 * stretch to be selectable from window size
 * menu.
 * 
 *    Rev 1.22   28 Apr 1997 11:45:40   JEREMIAH
 * Merge of 1.20.1.0 and 1.21.
 * 
 *    Rev 1.21   28 Apr 1997 10:14:48   TIM
 * Made mods for s3 stretch
 * 
 *    Rev 1.20.1.0   24 Apr 1997 15:15:52   JEREMIAH
 * Check for and store pixel format for 4444
 * texture formats, and apply to textures
 * when applicable.
 * 
 *    Rev 1.20   10 Apr 1997 11:06:20   JEREMIAH
 * Added SEMIFANCY to the possible 
 * transparency types.
 * 
 *    Rev 1.19   08 Apr 1997 10:44:46   BRUCE
 * promoted 1.18.1.1 to 1.19
 * 
 *    Rev 1.18.1.1   07 Apr 1997 14:53:00   JEREMIAH
 * Added vramsize variable.
 * 
 * 
 *    Rev 1.18.1.0   24 Mar 1997 09:59:00   JEREMIAH
 * Made MMX default to 640x480x8 mode.
 * Patch until MMX works again.
 * 
 *    Rev 1.18   20 Mar 1997 14:13:54   BO
 * modified code to detect MMXchip and P6chip
 * 
 * 
 *    Rev 1.17   Mar 20 1997 14:08:18   JEREMIAH
 * Added more diagnostic BYDumps to 
 * the texture surface enumeration.
 * 
 *    Rev 1.16   18 Mar 1997 15:02:04   JEREMIAH
 * Fixed default mode selection.
 * 
 *    Rev 1.15   17 Mar 1997 15:17:42   JEREMIAH
 * Fixed definition of VRAM_range.
 * 
 *    Rev 1.14   14 Mar 1997 14:00:58   JEREMIAH
 * Added flag for 3d acceleration hw.
 * Removed check for P6 chip.
 * 
 *    Rev 1.13   13 Mar 1997 17:35:58   JEREMIAH
 * Integrated 1.8.1.0
 * 
 *    Rev 1.12   12 Mar 1997 13:28:30   JEREMIAH
 * Fixed default condition for transparency
 * style.
 * 
 *    Rev 1.11   12 Mar 1997 12:46:28   JEREMIAH
 * Set DEST_BLENDs to BLEND_ZERO
 * for non-semi-transparent styles.
 * 
 * Uses semi-transparency only with detail
 * levels 4 and 5.
 * 
 *    Rev 1.10   12 Mar 1997 10:36:28   JEREMIAH
 * Added function to set transparency style.
 * 
 *    Rev 1.9   06 Mar 1997 12:04:48   JEREMIAH
 * Check for 5551 texture pixel format.
 * 
 *    Rev 1.8   06 Feb 1997 08:14:48   BRUCE
 * removed uninteresting warning.
 * 
 *    Rev 1.8.1.0   26 Feb 1997 17:51:16   BO
 * modified setdefaultmode module, added code
 * to detect MMX chip.
 * 
 *    Rev 1.7   31 Jan 1997 13:58:06   JEREMIAH
 * Changed by Bo.
 * Added 3 video mode options to compile
 * freeware version.
 * 
 *    Rev 1.6   29 Jan 1997 17:31:44   TIM
 * Modified the memory detection modules to enumerate the dd device instead of the d3d device 
 * 
 *    Rev 1.5   28 Jan 1997 15:24:10   JEREMIAH
 * Examine video card to determine default
 * video mode.
 * 
 *    Rev 1.4   15 Nov 1996 12:13:34   JEREMIAH
 * Merge of 1.1.1.0 and 1.3.
 * 
 *    Rev 1.3   07 Nov 1996 15:55:46   JEREMIAH
 * Modified texture enumeration code.
 * 
 *    Rev 1.2   07 Nov 1996 15:30:22   JEREMIAH
 * Modified texture enumeration code.  
 * Picks lowest alpha value.
 * 
 *    Rev 1.1.1.0   15 Nov 1996 12:02:54   JEREMIAH
 * Changed by Liou GuoHong (ITC).  
 * Implemented copy mode for 8-bit rendering.
 * 
 *    Rev 1.1   Oct 23 1996 12:47:50   JEREMIAH
 * Hardcoded a check for unpalletized 
 * texture formats to be 16 bits to prevent
 * error if 24 bit texture formats are chosen.
 * 
*/

//#define INITGUID
#include <stdio.h>
#include "d3dappi.h"
#include "byglobal.h"
#include "ybmm.h"
#include "global.h"

int vramsize;
int forcedtransparency=-1;

/*
 * QuickDDEnumCallback
 * Callback function used during enumeration of DirectDraw drivers.
 * During enumeration, if a 3D capable hardware device is found, it is 
 * created and *(LPDIRECTDRAW*)lpContext is set to it.  Otherwise, does
 * nothing.
 */
BOOL FAR PASCAL QuickDDEnumCallback(GUID FAR* lpGUID, LPSTR lpDriverDesc,
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
            *(LPDIRECTDRAW*)lpContext = lpDD;
            return DDENUMRET_CANCEL;
        }       
        lpDD->lpVtbl->Release(lpDD);
    }
    return DDENUMRET_OK;
}

//static
int QuickD3DCheck()
{
   DDCAPS ddcaps,ddhelcaps;
    LPDIRECTDRAW lpDD;
    sStretch.bCanStretch = sStretch.bStretch = sStretch.bWillStretch = FALSE;

    LastError = DirectDrawCreate(NULL, &lpDD, NULL);
     if (LastError != DD_OK) {
         D3DAppISetErrorString("DirectDrawCreate failed.\n%s",
                               D3DAppErrorToString(LastError));
         BYDumpInfo("QuickD3DCheck():  DirectDrawCreate failed.");   
        goto exit_with_error;
     }

	LastError = DirectDrawEnumerate(QuickDDEnumCallback, &lpDD);
	if (LastError != DD_OK) 
	{
		D3DAppISetErrorString("DirectDrawEnumerate failed.\n%s",
                                  D3DAppErrorToString(LastError));
      BYDumpInfo("QuickD3DCheck():  DirectDrawEnumerate failed.");   
      goto exit_with_error;
	}
   

	//Tim system diagnostics: calculate video memory 
	ddcaps.dwSize = sizeof(DDCAPS);
	ddhelcaps.dwSize = sizeof(DDCAPS);
	if (FAILED(lpDD->lpVtbl->GetCaps(lpDD, &ddcaps, &ddhelcaps))) {
		lpDD->lpVtbl->Release(lpDD);
		D3DAppISetErrorString("DirectDraw GetCaps failed.\n%s",
                                  D3DAppErrorToString(LastError));
      BYDumpInfo("QuickD3DCheck():  DirectDraw GetCaps failed.");   
		goto exit_with_error;
	}
    RELEASE(lpDD);
	if (ddcaps.dwCaps & DDCAPS_3D) { // hardware accelerated
		hw3dacc = TRUE;
		sStretch.bCanStretch = FALSE;
		//Tim Stretch: if we can blit stretch with hardware.  
		if (ddcaps.dwCaps & DDCAPS_OVERLAYSTRETCH){
			sStretch.bCanStretch = TRUE;
//			return 5;
		}
		vramsize = ddcaps.dwVidMemTotal;
		if (vramsize > 2097152)   // if video memory is greater than 2 meg
			return 4;      // 4meg (or greater) accelerator
		else
			return 2;      // 2meg (or lesser) accelerator
	}
	else
   {
      vramsize = 0;
      hw3dacc = FALSE;
		return 1;
   }

   // output  result to dump file
//	sprintf(lpOutput, "Video memory free = %d\n", ddcaps.dwVidMemFree);
//	BYDumpInfo(lpOutput);

exit_with_error:
  
    RELEASE(lpDD);
    return -1;
}

#pragma optimize( "", off)

BOOL 
SetDefaultVideoMode()
{
   int vmode;
	int regEAX, regEDX;
   char tmp[256];

   vmode = QuickD3DCheck();
   //sprintf(tmp, "QuickD3DCheck() returned %d", vmode);
   //BYDumpInfo(tmp);

   // Commented out in case it breaks on Cyrex (or other non-Intel) - Spudde
   /*
	_asm
	{
		mov eax, 1
		_emit 0x0f
		_emit 0xa2
		mov regEAX, eax
		mov regEDX, edx  
	}
	//P5Chip  = (regEAX >> 8) & 0x000f;
	P6Chip  = (regEAX & 0x00000ff0)==0x0610;
	MMXChip = (regEDX & 0x00800000)==0x800000;
	*/
	P6Chip  = MMXChip = FALSE;


#ifdef FREEWARE
#ifdef USE320	
	vmode = 1;
#endif

#ifdef USE512
	vmode = 2;
#endif

#ifdef USE640
	vmode = 4;
#endif
	VRAM_Range = vmode;
#else
	if (vmode<2)
	{
		if (MMXChip) 
		{
			vmode = 3;
		}
/*
		else 
		if (P6Chip)
		{
			vmode = 3;
		}
*/
	}
	// the VRAM_Range for nonFREEWARE version change its
	// meaning here.  It will be used in SetShowScreenPara function
	// in the wrapper.cpp
	VRAM_Range = vmode;  
#endif

   switch (vmode)
   {
   case 1:
	   VM_W3D = 320;
	   VM_H3D = 240;
	   VM_BPP3D = 8;
      BYDumpInfo("Defaulted to 320x240x8");
      break;
   case 2:
	   VM_W3D = 512;
	   VM_H3D = 384;
	   VM_BPP3D = 16;
      BYDumpInfo("Defaulted to 512x384x16");
      break;
   case 3:
	   VM_W3D = 640;
	   VM_H3D = 480;
	   VM_BPP3D = 8;
      BYDumpInfo("Defaulted to 640x480x8");
      break;
   case 4:
	   VM_W3D = 640;
	   VM_H3D = 480;
	   VM_BPP3D = 16;
      BYDumpInfo("Defaulted to 640x480x16");
      break;

   default:
      BYDumpInfo("Didn't default to any mode");
      return FALSE;
   }
   /*
	{
		int l;
		l = strlen(BmpPath);
		while (l>0)
		{
			if (BmpPath[l-1]=='\\')
			{
				if (VM_W3D==640)
					strcpy(&BmpPath[l], "BMP640");
				else if (VM_W3D==512)
					strcpy(&BmpPath[l], "BMP512");
				else if (VM_W3D==320)
					strcpy(&BmpPath[l], "BMP320");

				break;
			}
			l--;
		}
	}
   */
   return TRUE;
}
#pragma optimize( "", on)

/***************************************************************************/
/*                            Creation of D3D                              */
/***************************************************************************/
BOOL
D3DAppICreateD3D(void)
{
    LastError = d3dappi.lpDD->lpVtbl->QueryInterface(d3dappi.lpDD,
                                    &IID_IDirect3D, (LPVOID*)&d3dappi.lpD3D);
    if (LastError != DD_OK) {
        D3DAppISetErrorString("Creation of IDirect3D failed.\n%s",
                              D3DAppErrorToString(LastError));
        goto exit_with_error;
    }
    return TRUE;
exit_with_error:
    return FALSE;
}


/***************************************************************************/
/*                           D3D Device Enumeration                        */
/***************************************************************************/
/*
 * enumDeviceFunc
 * Device enumeration callback.  Record information about the D3D device
 * reported by D3D.
 */
static HRESULT
WINAPI enumDeviceFunc(LPGUID lpGuid, LPSTR lpDeviceDescription,
                      LPSTR lpDeviceName, LPD3DDEVICEDESC lpHWDesc,
                      LPD3DDEVICEDESC lpHELDesc, LPVOID lpContext)
{
    lpContext = lpContext;
    /*
     * Don't accept any hardware D3D devices if emulation only option is set
     */
    if (lpHWDesc->dcmColorModel && d3dappi.bOnlyEmulation)
        return D3DENUMRET_OK;
    /*
     * Record the D3D driver's inforamation
     */
    memcpy(&d3dappi.Driver[d3dappi.NumDrivers].Guid, lpGuid, sizeof(GUID));
    lstrcpy(d3dappi.Driver[d3dappi.NumDrivers].About, lpDeviceDescription);
    lstrcpy(d3dappi.Driver[d3dappi.NumDrivers].Name, lpDeviceName);
    /*
     * Is this a hardware device or software emulation?  Checking the color
     * model for a valid model works.
     */
	BYDumpInfo(lpDeviceName);

    if (lpHWDesc->dcmColorModel) {
        d3dappi.Driver[d3dappi.NumDrivers].bIsHardware = TRUE;
        memcpy(&d3dappi.Driver[d3dappi.NumDrivers].Desc, lpHWDesc,
               sizeof(D3DDEVICEDESC));
    } else {
        d3dappi.Driver[d3dappi.NumDrivers].bIsHardware = FALSE;
        memcpy(&d3dappi.Driver[d3dappi.NumDrivers].Desc, lpHELDesc,
               sizeof(D3DDEVICEDESC));
    }
	if (d3dappi.Driver[d3dappi.NumDrivers].bIsHardware)
		BYDumpInfo("Is hardware");
	else
		BYDumpInfo("Is software");
    /*
     * Does this driver do texture mapping?
     */
    d3dappi.Driver[d3dappi.NumDrivers].bDoesTextures =
        (d3dappi.Driver[d3dappi.NumDrivers].Desc.dpcTriCaps.dwTextureCaps &
         D3DPTEXTURECAPS_PERSPECTIVE) ? TRUE : FALSE;

	if (d3dappi.Driver[d3dappi.NumDrivers].bDoesTextures)
		BYDumpInfo("Does textures");
	else
		BYDumpInfo("Doesn't do textures");
    /*
     * Can this driver use a z-buffer?
     */
    d3dappi.Driver[d3dappi.NumDrivers].bDoesZBuffer =
        d3dappi.Driver[d3dappi.NumDrivers].Desc.dwDeviceZBufferBitDepth
                ? TRUE : FALSE;
    /*
     * Can this driver render to the Windows display depth
     */
    d3dappi.Driver[d3dappi.NumDrivers].bCanDoWindow =
        (d3dappi.Driver[d3dappi.NumDrivers].Desc.dwDeviceRenderBitDepth &
         D3DAppIBPPToDDBD(d3dappi.WindowsDisplay.bpp)) ? TRUE : FALSE;
    if (!d3dappi.bIsPrimary)
        d3dappi.Driver[d3dappi.NumDrivers].bCanDoWindow = FALSE;

    d3dappi.NumDrivers++;
    if (d3dappi.NumDrivers == D3DAPP_MAXD3DDRIVERS)
        return (D3DENUMRET_CANCEL);
    return (D3DENUMRET_OK);
}

/*
 * D3DAppIEnumDrivers
 * Get the available drivers from Direct3D by enumeration.
 */
BOOL
D3DAppIEnumDrivers(void)
{
    d3dappi.NumDrivers = 0;
    LastError = d3dappi.lpD3D->lpVtbl->EnumDevices(d3dappi.lpD3D,
                                                   enumDeviceFunc, NULL);
    if (LastError != DD_OK) {
        D3DAppISetErrorString("Enumeration of drivers failed.\n%s",
                              D3DAppErrorToString(LastError));
        return FALSE;
    }
    d3dappi.CurrDriver = 0;
    return TRUE;
}

/***************************************************************************/
/*                    Enumeration of texure format                         */
/***************************************************************************/
/*
 * EnumTextureFormatsCallback
 * Record information about each texture format the current D3D driver can
 * support. Choose one as the default format (paletted formats are prefered)
 * and return it through lpContext.
 */
static HRESULT
CALLBACK EnumTextureFormatsCallback(LPDDSURFACEDESC lpDDSD, LPVOID lpContext)
{
    unsigned long m;
    int r, g, b, a;
    int *lpStartFormat = (int *)lpContext;
    char tmp[200];
    /*
     * Record the DDSURFACEDESC of this texture format
     */
    memset(&d3dappi.TextureFormat[d3dappi.NumTextureFormats], 0,
           sizeof(D3DAppTextureFormat));
    memcpy(&d3dappi.TextureFormat[d3dappi.NumTextureFormats].ddsd, lpDDSD,
           sizeof(DDSURFACEDESC));
    /*
     * Is this format palettized?  How many bits?  Otherwise, how many RGB
     * bits?
     */
    if (lpDDSD->ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED8) {
       BYDumpInfo("8-bit palettized texture format");
        d3dappi.TextureFormat[d3dappi.NumTextureFormats].bPalettized = TRUE;
        d3dappi.TextureFormat[d3dappi.NumTextureFormats].IndexBPP = 8;
    } else if (lpDDSD->ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED4) {
        d3dappi.TextureFormat[d3dappi.NumTextureFormats].bPalettized = TRUE;
        d3dappi.TextureFormat[d3dappi.NumTextureFormats].IndexBPP = 4;
/*
	} else if (lpDDSD->ddpfPixelFormat.dwFlags & DDPF_ALPHAPIXELS) {

				// The sample apps don't currently understand
                // the alpha bit - just filter this format
                // away for now.
                 

                return DDENUMRET_OK;
*/
    } else
    {
        d3dappi.TextureFormat[d3dappi.NumTextureFormats].bPalettized = FALSE;
        d3dappi.TextureFormat[d3dappi.NumTextureFormats].IndexBPP = 0;
		if (lpDDSD->ddpfPixelFormat.dwFlags & DDPF_ALPHAPIXELS) {
			for (a = 0, m = lpDDSD->ddpfPixelFormat.dwRGBAlphaBitMask; !(m & 1);
																	   a++, m >>= 1);
				for (a = 0; m & 1; a++, m >>= 1);
		} else a = 0;
        for (r = 0, m = lpDDSD->ddpfPixelFormat.dwRBitMask; !(m & 1);
                                                               r++, m >>= 1);
        for (r = 0; m & 1; r++, m >>= 1);
        for (g = 0, m = lpDDSD->ddpfPixelFormat.dwGBitMask; !(m & 1);
                                                               g++, m >>= 1);
        for (g = 0; m & 1; g++, m >>= 1);
        for (b = 0, m = lpDDSD->ddpfPixelFormat.dwBBitMask; !(m & 1);
                                                               b++, m >>= 1);
        for (b = 0; m & 1; b++, m >>= 1);
        d3dappi.TextureFormat[d3dappi.NumTextureFormats].RedBPP = r;
        d3dappi.TextureFormat[d3dappi.NumTextureFormats].GreenBPP = g;
        d3dappi.TextureFormat[d3dappi.NumTextureFormats].BlueBPP = b;
        d3dappi.TextureFormat[d3dappi.NumTextureFormats].AlphaBPP = a;
    }
    /*
     * If lpStarFormat is -1, this is the first format.  Select it.
     */
    sprintf(tmp, "Examining texture format:  %d%d%d%d",
        d3dappi.TextureFormat[d3dappi.NumTextureFormats].RedBPP,
        d3dappi.TextureFormat[d3dappi.NumTextureFormats].GreenBPP,
        d3dappi.TextureFormat[d3dappi.NumTextureFormats].BlueBPP,
        d3dappi.TextureFormat[d3dappi.NumTextureFormats].AlphaBPP);
    BYDumpInfo(tmp);

    if (*lpStartFormat == -1)
        *lpStartFormat = d3dappi.NumTextureFormats;

    /* 
     * If this format is paletted, select it.
     */
    if (d3dappi.TextureFormat[d3dappi.NumTextureFormats].bPalettized && bPrimaryPalettized) 
    {
       BYDumpInfo("Palletized!");
        *lpStartFormat = d3dappi.NumTextureFormats;
    } 
    else if (!(d3dappi.TextureFormat[d3dappi.NumTextureFormats].bPalettized) && !bPrimaryPalettized) 
    {
		//if (d3dappi.TextureFormat[d3dappi.NumTextureFormats].AlphaBPP > d3dappi.TextureFormat[*lpStartFormat].AlphaBPP)
		//if (d3dappi.TextureFormat[d3dappi.NumTextureFormats].AlphaBPP == 1)
       if (r+g+b+a == 16)     // if texture format is 16 bit
       {
         if (d3dappi.TextureFormat[d3dappi.NumTextureFormats].AlphaBPP == 1)
            *lpStartFormat = d3dappi.NumTextureFormats;
         if (d3dappi.TextureFormat[*lpStartFormat].AlphaBPP != 1)
            *lpStartFormat = d3dappi.NumTextureFormats;
          sprintf(tmp, "Considering texture format:  %d%d%d%d",
              d3dappi.TextureFormat[*lpStartFormat].RedBPP,
              d3dappi.TextureFormat[*lpStartFormat].GreenBPP,
              d3dappi.TextureFormat[*lpStartFormat].BlueBPP,
              d3dappi.TextureFormat[*lpStartFormat].AlphaBPP);
          BYDumpInfo(tmp);
       }
       if (r==4 && g==4 & b==4 && a==4)
       {
         memcpy(&d3dappi.TranspTextureFormat, &d3dappi.TextureFormat[d3dappi.NumTextureFormats],
            sizeof(D3DAppTextureFormat));
       }

    } 

    d3dappi.NumTextureFormats++;
    return DDENUMRET_OK;
}

/*
 * D3DAppIEnumTextureFormats
 * Get a list of available texture map formats from the Direct3D driver by
 * enumeration.  Choose a default format (paletted is prefered).
 */
BOOL
D3DAppIEnumTextureFormats(void)
{
    int StartFormat;
    char tmp[200];
    /*
     * Set the default format to -1 to let the callback know it's being 
     * called for the first time.
     */
    StartFormat = -1;
    d3dappi.NumTextureFormats = 0;
    memset(&d3dappi.TranspTextureFormat, 0, sizeof(D3DAppTextureFormat));
    LastError =
         d3dappi.lpD3DDevice->lpVtbl->EnumTextureFormats(d3dappi.lpD3DDevice,
                                                  EnumTextureFormatsCallback,
                                                  (LPVOID)&StartFormat);
    if (LastError != DD_OK) {
        D3DAppISetErrorString("Enumeration of texture formats failed.\n%s",
                              D3DAppErrorToString(LastError));
        return FALSE;
    }
    sprintf(tmp, "Chose texture format:  %d%d%d%d",
        d3dappi.TextureFormat[StartFormat].RedBPP,
        d3dappi.TextureFormat[StartFormat].GreenBPP,
        d3dappi.TextureFormat[StartFormat].BlueBPP,
        d3dappi.TextureFormat[StartFormat].AlphaBPP);
    BYDumpInfo(tmp);
    memcpy(&d3dappi.ThisTextureFormat, &d3dappi.TextureFormat[StartFormat],
           sizeof(D3DAppTextureFormat));
    d3dappi.CurrTextureFormat = StartFormat;
    return TRUE;
}

/***************************************************************************/
/*                               Device creation                           */
/***************************************************************************/
/*
 * D3DAppICreateDevice
 * Create the D3D device and enumerate the texture formats
 */
BOOL
D3DAppICreateDevice(int driver)
{
    RELEASE(d3dappi.lpD3DDevice);

    if (d3dappi.Driver[driver].bIsHardware && !d3dappi.bBackBufferInVideo) {
        D3DAppISetErrorString("Could not fit the rendering surfaces in video memory for this hardware device.\n");
        goto exit_with_error;
    }

    d3dappi.CurrDriver = driver;
    memcpy(&d3dappi.ThisDriver, &d3dappi.Driver[driver], sizeof(D3DAppD3DDriver));
    
	// Tim Stretch: Query 2nd back buffer if we can stretch
	if(sStretch.bStretch)
	{
		LastError =
           d3dappi.lpBackBuffer2->lpVtbl->QueryInterface(d3dappi.lpBackBuffer2,
                                                &d3dappi.Driver[driver].Guid,
                                              (LPVOID*)&d3dappi.lpD3DDevice);

	}
	else
	{
		LastError =
           d3dappi.lpBackBuffer->lpVtbl->QueryInterface(d3dappi.lpBackBuffer,
                                                &d3dappi.Driver[driver].Guid,
                                              (LPVOID*)&d3dappi.lpD3DDevice);
    }
	if (LastError != DD_OK) {
        D3DAppISetErrorString("Create D3D device failed.\n%s",
                              D3DAppErrorToString(LastError));
        goto exit_with_error;
    }
/*
    memset (&D3DHWDevDesc, 0, sizeof(D3DDEVICEDESC));
    D3DHWDevDesc.dwSize = sizeof(D3DDEVICEDESC);
    memset (&D3DHELDevDesc, 0, sizeof(D3DDEVICEDESC));
    D3DHELDevDesc.dwSize = sizeof(D3DDEVICEDESC);
    LastError = d3dappi.lpD3DDevice->lpVtbl->GetCaps(d3dappi.lpD3DDevice, &D3DHWDevDesc, &D3DHELDevDesc);
    if (LastError != DD_OK) {
        D3DAppISetErrorString("Getting D3D capabilities failed.\n%s",
                              D3DAppErrorToString(LastError));
        return 0L;
    }
*/
    d3dappi.CurrDriver = driver;
    d3dappi.NumTextureFormats = 0;
    if (d3dappi.Driver[driver].bDoesTextures) {
        if (!D3DAppIEnumTextureFormats())
            goto exit_with_error;
    }

    return TRUE;
exit_with_error:
    RELEASE(d3dappi.lpD3DDevice);
    return FALSE;
}

/***************************************************************************/
/*                      Setting the render state                           */
/***************************************************************************/
/*
 * D3DAppISetRenderState
 * Create and execute an execute buffer which will set the render state and
 * light state for the current viewport.
 */
extern int VM_W3D;
extern int VM_H3D;
extern int VM_BPP3D;

BOOL
D3DAppISetRenderState()
{
    D3DEXECUTEBUFFERDESC debDesc;
    D3DEXECUTEDATA d3dExData;
    LPDIRECT3DEXECUTEBUFFER lpD3DExCmdBuf = NULL;
    LPVOID lpBuffer, lpInsStart;
    size_t size;


    /*
     * If there is no D3D Viewport, we must return true because it is not
     * required.
     */
    if (!d3dappi.lpD3DViewport)
        return TRUE;
    /*
     * Create an execute buffer of the required size
     */
    size = 0;
    /*
	//Other person's code
	size += sizeof(D3DINSTRUCTION) * 3;
    size += sizeof(D3DSTATE) * 17;
	*/
	//Lgh added
    size += sizeof(D3DINSTRUCTION) * 4;
    size += sizeof(D3DSTATE) * 20;
    memset(&debDesc, 0, sizeof(D3DEXECUTEBUFFERDESC));
    debDesc.dwSize = sizeof(D3DEXECUTEBUFFERDESC);
    debDesc.dwFlags = D3DDEB_BUFSIZE;
    debDesc.dwBufferSize = size;
	//debDesc.dwCaps = D3DDEBCAPS_SYSTEMMEMORY;

    LastError =
        d3dappi.lpD3DDevice->lpVtbl->CreateExecuteBuffer(d3dappi.lpD3DDevice,
                                             &debDesc, &lpD3DExCmdBuf, NULL);
    if (LastError != D3D_OK) {
        D3DAppISetErrorString("CreateExecuteBuffer failed in SetRenderState.\n%s",
                              D3DAppErrorToString(LastError));
        goto exit_with_error;
    }
    /*
     * Lock the execute buffer so it can be filled
     */
    LastError = lpD3DExCmdBuf->lpVtbl->Lock(lpD3DExCmdBuf, &debDesc);
    if (LastError != D3D_OK) {
        D3DAppISetErrorString("Lock failed on execute buffer in SetRenderState.\n%s",
                              D3DAppErrorToString(LastError));
        goto exit_with_error;
    }
    memset(debDesc.lpData, 0, size);

    lpInsStart = debDesc.lpData;
    lpBuffer = lpInsStart;
    /*
     * Set render state
     */
	OP_STATE_RENDER(14, lpBuffer);
      STATE_DATA(D3DRENDERSTATE_SHADEMODE, d3dapprs.ShadeMode, lpBuffer);
      STATE_DATA(D3DRENDERSTATE_TEXTUREPERSPECTIVE, d3dapprs.bPerspCorrect,
                 lpBuffer);
      STATE_DATA(D3DRENDERSTATE_ZENABLE, d3dapprs.bZBufferOn &&
                                  d3dappi.ThisDriver.bDoesZBuffer, lpBuffer);
      STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE, d3dapprs.bZBufferOn, lpBuffer);
      STATE_DATA(D3DRENDERSTATE_ZFUNC, D3DCMP_LESSEQUAL, lpBuffer);
      STATE_DATA(D3DRENDERSTATE_TEXTUREMAG, d3dapprs.TextureFilter,lpBuffer);
      STATE_DATA(D3DRENDERSTATE_TEXTUREMIN, d3dapprs.TextureFilter,lpBuffer);
      STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND, d3dapprs.TextureBlend,
                 lpBuffer);
      STATE_DATA(D3DRENDERSTATE_FILLMODE, d3dapprs.FillMode, lpBuffer);
      STATE_DATA(D3DRENDERSTATE_DITHERENABLE, d3dapprs.bDithering, lpBuffer);
      STATE_DATA(D3DRENDERSTATE_SPECULARENABLE, d3dapprs.bSpecular,lpBuffer);
      STATE_DATA(D3DRENDERSTATE_ANTIALIAS, d3dapprs.bAntialiasing, lpBuffer);
      STATE_DATA(D3DRENDERSTATE_FOGENABLE, d3dapprs.bFogEnabled, lpBuffer);
      STATE_DATA(D3DRENDERSTATE_FOGCOLOR, d3dapprs.FogColor, lpBuffer);
    /*
     * Set light state
     */
    OP_STATE_LIGHT(3, lpBuffer);
      STATE_DATA(D3DLIGHTSTATE_FOGMODE, d3dapprs.bFogEnabled ?
                 d3dapprs.FogMode : D3DFOG_NONE, lpBuffer);
      STATE_DATA(D3DLIGHTSTATE_FOGSTART, *(unsigned long*)&d3dapprs.FogStart,
                 lpBuffer);
      STATE_DATA(D3DLIGHTSTATE_FOGEND, *(unsigned long*)&d3dapprs.FogEnd,
                 lpBuffer);

 	//Lgh added.
	if ((VM_W3D == 320) && (VM_H3D == 240) && (VM_BPP3D == 8))
	{
		OP_STATE_RENDER(3, lpBuffer);
			STATE_DATA(D3DRENDERSTATE_BLENDENABLE, TRUE, lpBuffer);
			STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_COPY, lpBuffer);	
			STATE_DATA(D3DRENDERSTATE_DESTBLEND, D3DBLEND_DESTALPHA, lpBuffer);	
	}
	else
	{
		OP_STATE_RENDER(1, lpBuffer);
			STATE_DATA(D3DRENDERSTATE_BLENDENABLE, TRUE, lpBuffer);
	}

    OP_EXIT(lpBuffer);

    LastError = lpD3DExCmdBuf->lpVtbl->Unlock(lpD3DExCmdBuf);
    if (LastError != D3D_OK) {
        D3DAppISetErrorString("Unlock failed on execute buffer in SetRenderState.\n%s",
                              D3DAppErrorToString(LastError));
        goto exit_with_error;
    }
    /*
     * Set the execute data and exectue the buffer
     */
    memset(&d3dExData, 0, sizeof(D3DEXECUTEDATA));
    d3dExData.dwSize = sizeof(D3DEXECUTEDATA);
    d3dExData.dwInstructionOffset = (ULONG) 0;
    d3dExData.dwInstructionLength = (ULONG) ((char*)lpBuffer -
                                                          (char*)lpInsStart);
    lpD3DExCmdBuf->lpVtbl->SetExecuteData(lpD3DExCmdBuf, &d3dExData);
    LastError = d3dappi.lpD3DDevice->lpVtbl->BeginScene(d3dappi.lpD3DDevice);
    if (LastError != D3D_OK) {
        D3DAppISetErrorString("BeginScene failed in SetRenderState.\n%s",
                              D3DAppErrorToString(LastError));
        goto exit_with_error;
    }
    LastError = d3dappi.lpD3DDevice->lpVtbl->Execute(d3dappi.lpD3DDevice,
                                                     lpD3DExCmdBuf,
                                                     d3dappi.lpD3DViewport,
                                                     D3DEXECUTE_UNCLIPPED);
    if (LastError != D3D_OK) {
        D3DAppISetErrorString("Execute failed in SetRenderState.\n%s",
                              D3DAppErrorToString(LastError));
        goto exit_with_error;
    }
    LastError = d3dappi.lpD3DDevice->lpVtbl->EndScene(d3dappi.lpD3DDevice);
    if (LastError != D3D_OK) {
        D3DAppISetErrorString("EndScene failed in SetRenderState.\n%s",
                              D3DAppErrorToString(LastError));
        goto exit_with_error;
    }
    /*
     * We are done with the execute buffer, so release it.
     */
    lpD3DExCmdBuf->lpVtbl->Release(lpD3DExCmdBuf);

    return TRUE;

exit_with_error:
    RELEASE(lpD3DExCmdBuf);
    return FALSE;
}

BOOL SetTransparencyStyle()
{
	char astring[8];

	sprintf(astring, "%d" , forcedtransparency);
	BYDumpInfo(astring);

	if (forcedtransparency>=0)
	{
		switch (forcedtransparency)
		{
		case 1:
			d3dapprs.transparency = FANCY;
			BYDumpInfo("Forced into:  Fancy type transparency");
			return TRUE;
		case 2:
			d3dapprs.transparency = SEMIFANCY;
			BYDumpInfo("Forced into:  Semifancy type transparency");
			return TRUE;
		case 3:
			d3dapprs.transparency = TRANSLUCENT;
			BYDumpInfo("Forced into:  Translucent type transparency");
			return TRUE;
		case 4:
			d3dapprs.transparency = NORMTRANSPARENT;
			BYDumpInfo("Forced into:  Normal type transparency");
			return TRUE;
		case 5:
			d3dapprs.transparency = ALTTRANSPARENT;
			BYDumpInfo("Forced into:  Alternative type transparency");
			return TRUE;
		case 0:
			d3dapprs.transparency = COLORKEY;
			BYDumpInfo("Forced into:  No transparency -- colorkey only");
			return TRUE;
		default:
			;
		}
	}
    if  (!(d3dappi.Driver[d3dappi.CurrDriver].Desc.dpcTriCaps.dwTextureCaps &
         D3DPTEXTURECAPS_ALPHA)) 
	{
       d3dapprs.transparency = COLORKEY;
       BYDumpInfo("No transparency -- colorkey only");
       return TRUE;
	}
	else
	{
		// make sure selected alpha blend capability is supported in hardware 

		// for simplest alpha translucency

		if  ((detail >= 4) &&
         (d3dappi.Driver[d3dappi.CurrDriver].Desc.dpcTriCaps.dwDestBlendCaps &
				D3DPBLENDCAPS_ONE) &&
			(d3dappi.Driver[d3dappi.CurrDriver].Desc.dpcTriCaps.dwDestBlendCaps &
				D3DPBLENDCAPS_INVSRCALPHA) &&
			(d3dappi.Driver[d3dappi.CurrDriver].Desc.dpcTriCaps.dwSrcBlendCaps &
				D3DPBLENDCAPS_SRCALPHA) &&
			(d3dappi.Driver[d3dappi.CurrDriver].Desc.dpcTriCaps.dwTextureBlendCaps &			
				D3DPTBLENDCAPS_MODULATEALPHA))
		{
         BYDumpInfo("Fancy type transparency");
         d3dapprs.transparency = FANCY;
         return TRUE;
      }
		else {
		if  ((detail >= 4) &&
		(d3dappi.Driver[d3dappi.CurrDriver].Desc.dpcTriCaps.dwDestBlendCaps &
			   D3DPBLENDCAPS_INVSRCALPHA) &&
		(d3dappi.Driver[d3dappi.CurrDriver].Desc.dpcTriCaps.dwSrcBlendCaps &
		   D3DPBLENDCAPS_SRCALPHA) &&
		(d3dappi.Driver[d3dappi.CurrDriver].Desc.dpcTriCaps.dwTextureBlendCaps &			
			D3DPTBLENDCAPS_MODULATEALPHA))
			{
				BYDumpInfo("Semifancy type transparency");
			   d3dapprs.transparency = SEMIFANCY;
			   return TRUE;
			}
			else 
         {
		   if  ((detail >= 4) &&
         (d3dappi.Driver[d3dappi.CurrDriver].Desc.dpcTriCaps.dwDestBlendCaps &
				D3DPBLENDCAPS_INVSRCALPHA) &&
			(d3dappi.Driver[d3dappi.CurrDriver].Desc.dpcTriCaps.dwSrcBlendCaps &
				D3DPBLENDCAPS_SRCALPHA)  && 
			   (d3dappi.Driver[d3dappi.CurrDriver].Desc.dpcTriCaps.dwSrcBlendCaps &
				   D3DPBLENDCAPS_ONE) &&
			   (d3dappi.Driver[d3dappi.CurrDriver].Desc.dpcTriCaps.dwTextureBlendCaps &			
				   D3DPTBLENDCAPS_MODULATE))
			   {
               BYDumpInfo("Translucent type transparency");
              d3dapprs.transparency = TRANSLUCENT;
              return TRUE;
			   }
		   else 
			   {	// tranparency  stuff
				   
				   // for simplest alpha transparency
				   if  ((d3dappi.Driver[d3dappi.CurrDriver].Desc.dpcTriCaps.dwDestBlendCaps &
						   D3DPBLENDCAPS_ZERO) &&
					   (d3dappi.Driver[d3dappi.CurrDriver].Desc.dpcTriCaps.dwSrcBlendCaps &
						   D3DPBLENDCAPS_ONE) &&
					   (d3dappi.Driver[d3dappi.CurrDriver].Desc.dpcTriCaps.dwTextureBlendCaps &
						   D3DPTBLENDCAPS_MODULATEALPHA))
				   {
                  BYDumpInfo("Normal type transparency");
                  d3dapprs.transparency = NORMTRANSPARENT;
                  return TRUE;
				   }
				   
				   else {
				   
					   // for alternative simplest alpha transparency
					   if  ((d3dappi.Driver[d3dappi.CurrDriver].Desc.dpcTriCaps.dwDestBlendCaps &
							   D3DPBLENDCAPS_ZERO) &&
						   (d3dappi.Driver[d3dappi.CurrDriver].Desc.dpcTriCaps.dwSrcBlendCaps &
							   D3DPBLENDCAPS_ONE) &&
						   (d3dappi.Driver[d3dappi.CurrDriver].Desc.dpcTriCaps.dwTextureBlendCaps &
							   D3DPTBLENDCAPS_MODULATE))
					   {
                     BYDumpInfo("Alternative type transparency");
                     d3dapprs.transparency = ALTTRANSPARENT;
                     return TRUE;
					   }
				   }
            }
			}
		}
   }
   BYDumpInfo("Default to colorkey only");
    d3dapprs.transparency = COLORKEY;
    return TRUE;
}
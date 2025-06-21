/*
* $Header:   H:/pvcs/pvcsproj/gomand3d.prj/d3dappi.h_v   1.6   May 07 1997 16:58:02   JEREMIAH  $
* $Log:   H:/pvcs/pvcsproj/gomand3d.prj/d3dappi.h_v  $
 * 
 *    Rev 1.6   May 07 1997 16:58:02   JEREMIAH
 * Separated stretch flags into separate 
 * structure.  Added bWillStretch.  Allowed
 * stretch to be selectable from window size
 * menu.
 * 
 * 
 *    Rev 1.5   28 Apr 1997 10:17:10   TIM
 * Made mods for s3 stretch
 * 
 *    Rev 1.4   28 Apr 1997 10:14:28   TIM
 *  
 * 
 *    Rev 1.3   10 Jan 1997 16:11:56   BO
 * moved one function prototype up to the 
 * _cplusplus area so that it could be also used 
 * by other C++ program.
 * 
 *    Rev 1.2   Oct 24 1996 14:37:42   JEREMIAH
 * Changed by Bo.  Added 
 * BYRestore2DSurfaces function prototype.
 * 
 *    Rev 1.1   Oct 23 1996 12:51:06   JEREMIAH
 * No code changes.
 */

#ifndef __D3DAPPI_H__
#define __D3DAPPI_H__

/*
 * INCLUDED HEADERS
 */

#ifdef MINIWIN
#include "miniwin/windows.h"
#else
#include <windows.h>
#include <windowsx.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <search.h>
#ifdef MINIWIN
#include "miniwin/ddraw.h"
#include "miniwin/d3d.h"
#else
#include <ddraw.h>
#include <d3d.h>
#endif
#include "d3dapp.h"
#include "d3dmacs.h"
#include "lclib.h"  /* lclib is a override for standard string lib */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * MACROS
 */
#undef ATTEMPT
#define ATTEMPT(x) if (!(x)) goto exit_with_error
#undef RELEASE
#define RELEASE(x) if (x) { x->lpVtbl->Release(x); x = NULL; }
#undef MAX
#define MAX(x, y) ((x) > (y)) ? (x) : (y)
#undef MIN
#define MIN(x, y) ((x) > (y)) ? (y) : (x)
#undef ZEROMEM
#define ZEROMEM(x) memset(&x, 0, sizeof(x))

/*
 * GLOBAL VARIABLES
 *    see d3dapp.c for descriptions
 */  
extern D3DAppInfo d3dappi;
extern sStretchInfo sStretch;
extern D3DAppRenderState d3dapprs;
extern BOOL bD3DAppInitialized;
extern HRESULT LastError;
extern LPDIRECTDRAWCLIPPER lpClipper;
extern LPDIRECTDRAWPALETTE lpPalette;
extern BOOL(*D3DDeviceDestroyCallback)(LPVOID);
extern LPVOID D3DDeviceDestroyCallbackContext;
extern BOOL(*D3DDeviceCreateCallback)(int, int, LPDIRECT3DVIEWPORT*, LPVOID);
extern LPVOID D3DDeviceCreateCallbackContext;
extern BOOL bPrimaryPalettized;
extern BOOL bPaletteActivate;
extern BOOL bIgnoreWM_SIZE;
extern PALETTEENTRY ppe[256];
extern PALETTEENTRY Originalppe[256];
extern char LastErrorString[256];
extern SIZE szLastClient;
extern SIZE szBuffers;
extern int NumDirtyClientRects, NumDirtyBackRects, NumDirtyZRects;
extern D3DRECT DirtyClient[D3DAPP_MAXCLEARRECTS];
extern D3DRECT DirtyBack[D3DAPP_MAXCLEARRECTS];
extern D3DRECT DirtyZ[D3DAPP_MAXCLEARRECTS];
extern D3DTEXTUREHANDLE MasterTextureHandle[D3DAPP_MAXTEXTURES];
extern int CallbackRefCount;
extern BOOL D3DAppIClearBuffers(void);
extern BOOL D3DAppICallDeviceDestroyCallback(void);
extern BOOL D3DAppISetCoopLevel(HWND hwnd, BOOL bFullscreen);
extern BOOL BYRestore2DSurfaces(void);
extern HRESULT D3DAppIGetSurfDesc(LPDDSURFACEDESC lpDDSurfDesc,
                           LPDIRECTDRAWSURFACE lpDDSurf);

#ifdef __cplusplus
};
#endif

/*
 * INTERNAL FUNCTION PROTOTYPES
 */
int QuickD3DCheck(void);
BOOL D3DAppISetRenderState(void);
BOOL D3DAppIEnumDrivers(void);
BOOL D3DAppIPickDriver(int* driver, DWORD depths);
BOOL D3DAppICreateD3D(void);
BOOL D3DAppIEnumTextureFormats(void);
BOOL D3DAppICreateZBuffer(int w, int h, int driver);
BOOL D3DAppICreateDevice(int driver);
BOOL D3DAppILoadTextureSurf(int n);
BOOL D3DAppIGetTextureHandle(int n);
BOOL D3DAppILoadAllTextures(void);
void D3DAppIReleaseTexture(int n);
void D3DAppIReleaseAllTextures(void);
BOOL D3DAppIReloadTextureSurf(int n);
//BOOL D3DAppISetCoopLevel(HWND hwnd, BOOL bFullscreen);
BOOL D3DAppISetDisplayMode(int w, int h, int bpp);
BOOL D3DAppICheckForPalettized(void);
BOOL D3DAppIRestoreDispMode(void);
BOOL D3DAppIVerifyDriverAndMode(int* lpdriver, int* lpmode);
BOOL D3DAppIFilterDrivers(int mode);
DWORD D3DAppTotalVideoMemory(void);
BOOL D3DAppIEnumDisplayModes(void);
BOOL D3DAppIPickDisplayMode(int* mode, DWORD depths);
BOOL D3DAppISetDispMode(int w, int h, int bpp);
BOOL D3DAppICreateDD(DWORD flags);
BOOL D3DAppIFilterDisplayModes(int driver);
HRESULT D3DAppICreateSurface(LPDDSURFACEDESC lpDDSurfDesc,
                LPDIRECTDRAWSURFACE FAR *lpDDSurface);
BOOL D3DAppICreateBuffers(HWND hwnd, int w, int h, int bpp,BOOL bFullscreen);
BOOL D3DAppIRememberWindowsMode(void);
//BOOL D3DAppIClearBuffers(void);
DWORD D3DAppIBPPToDDBD(int bpp);
void D3DAppIReleasePathList(void);
LPDIRECTDRAWSURFACE D3DAppILoadSurface(LPDIRECTDRAW lpDD, LPCSTR lpName,
                                       LPDDSURFACEDESC lpFormat,
                                       DWORD memoryflag);
void D3DAppISetClientSize(HWND hwnd, int w,int h,BOOL bReturnFromFullscreen);
void D3DAppIGetClientWin(HWND hwnd);
void D3DAppISetDefaults(void);
//BOOL D3DAppICallDeviceDestroyCallback(void);
BOOL D3DAppICallDeviceCreateCallback(int w, int h);
void D3DAppIMergeRectLists(int* dstnum, LPD3DRECT dst, int src1num,
                           LPD3DRECT src1, int src2num, LPD3DRECT src2);
void D3DAppICopyRectList(int* dstnum, LPD3DRECT dst, int srcnum,
                         LPD3DRECT src);
void D3DAppIValidateDirtyRects(void);
BOOL D3DAppIHandleWM_SIZE(LRESULT* lresult, HWND hwnd, UINT message,
                          WPARAM wParam, LPARAM lParam);
void D3DAppISetErrorString( LPSTR fmt, ... );

void __cdecl dpf( LPSTR fmt, ... );


#endif // __D3DAPPI_H__

/*
$Header:   H:/pvcs/pvcsproj/gomand3d.prj/rmfull.h_v   1.4   15 Jan 1997 13:45:34   TIM  $

$Log:   H:/pvcs/pvcsproj/gomand3d.prj/rmfull.h_v  $
 * 
 *    Rev 1.4   15 Jan 1997 13:45:34   TIM
 *  
 * 
 *    Rev 1.3   07 Jan 1997 09:32:58   BO
 * added new function for rendering game
 * 
 *    Rev 1.2   Nov 01 1996 12:35:20   JEREMIAH
 * Changed by Bo.  Added myglobs 
 * declaration.
 * 
 *    Rev 1.1   Oct 24 1996 14:39:16   JEREMIAH
 * Changed by Bo.  Added Render3DWorld
 * function prototype.
 */
#ifndef __RMFULL_H__
#define __RMFULL_H__

#ifdef MINIWIN
#include "miniwin/windows.h"
#include "miniwin/ddraw.h"
#include "miniwin/d3d.h"
#include "miniwin/direct.h"
#include "miniwin/d3drm.h"
#else
#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include <d3d.h>
#include <direct.h>
#include <d3drmwin.h>
#endif
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <search.h>
#include "d3dapp.h"         /* prototypes for D3D helper functions */
#include "rmdemo.h"         /* prototypes for functions to commumicate
                               with each sample */
#include "rmfullrc.h"       /* defines constants used in rmfull.rc */
#define START_WIN_SIZE 320  /* initial size of the window */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagrmfullglobals {
    HWND hWndMain;          /* application window handle */
    HINSTANCE hInstApp;     /* application instance for dialog boxes */

    LPDIRECT3DRMDEVICE dev;     /* Direct3DRM device */
    LPDIRECT3DRMVIEWPORT view;  /* Direct3DRM viewport through which we view
                                   the scene */
    LPDIRECT3DRMFRAME scene;    /* Master frame in which others are placed */
    LPDIRECT3DRMFRAME camera;   /* Frame describing the users POV */

    BOOL bSingleStepMode;        /* render one frame at a time */
    BOOL bDrawAFrame;            /* render on this pass of the main loop */
    BOOL bShowFrameRate;         /* show the frame rate at the top */
    BOOL bShowInfo;              /* show window information at the bottom */

    BOOL bResized; /* the window has resized or some other drastic change, the
                      entire client area should be cleared */
    BOOL bQuit;    /* program is about to terminate */

    BOOL bNoTextures;           /* this sample doesn't use any textures */
    BOOL bConstRenderQuality;   /* this sample is not constructed with
                                   MeshBuilders and so the RenderQuality
                                   cannot be changed */
    D3DRMRENDERQUALITY RenderQuality;   /* current shade mode, fill mode and
                                           lighting state */
    D3DRMTEXTUREQUALITY TextureQuality; /* current texture interpolation */
    BOOL bDithering;                    /* is dithering on? */
    BOOL bAntialiasing;                 /* is antialiasing on? */

    int mouse_buttons;          /* mouse button state */
    int mouse_x;                /* mouse cursor x position */
    int mouse_y;                /* mouse cursor y position */

    LPDIRECTDRAWSURFACE lpFrameRateBuffer; /* frame rate surface */
    LPDIRECTDRAWSURFACE lpInfoBuffer;      /* window info surface */
} rmfullglobals;

void __cdecl Msg( LPSTR fmt, ... );
/*
 * STATS.CPP FUNCTION PROTOTYPES
 */
BOOL InitFontAndTextBuffers(void);
BOOL WriteInfoBuffer(void);
BOOL WriteFrameRateBuffer(float fps, long tps);
void ResetFrameRate(void);
BOOL CalculateFrameRate();
BOOL DisplayFrameRate(int* count, LPD3DRECT lpExtents );

BOOL
AfterDeviceCreated(int w, int h, LPDIRECT3DVIEWPORT* lplpViewport, LPVOID lpContext);
BOOL BeforeDeviceDestroyed(LPVOID lpContext);
BOOL Render3DWorld(void);
extern rmfullglobals myglobs;          
extern BOOL RenderGame(void);

#ifdef __cplusplus
};
#endif

#endif // __RMFULL_H__

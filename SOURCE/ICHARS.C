/***********************************************************************\
 *    (C) Copyright 1995 by 47-TEK, Inc.							   *
 *																	   *
 *    This program is copyrighted by 47-TEK, Inc. and is  not licensed *
 *    to you under any conditions.  You may not distribute, duplicate, *
 *    or  publish the source code of this program in any form.  You	   *
 *    may  not incorporate this code in any form in derivative  works. *
 *     																   *
 *																	   *
 *    47-Tek is a registered trademark of 47-TEK, Inc.				   *
 *    47-TEK Specifically disclaims any implied Warranty of Mer-	   *
 *    chantability or fitness for a particular use. 47-TEK,  Inc.	   *
 *    does not Warrant that the operation of the program will be	   *
 *    uninterrupted or error free.									   *
 *																	   *
\***********************************************************************

Program:        Goman95
File:           ICHARS.C
Author:         Jeremiah Spudde Childs
Date:           10/11/95
Version:        version 1.0

Development Environment:   MSVC 2.0, Reality Lab 2.0 Beta 21 runtime dll
                           Reality Lab 2.0 Build 21.

************************************************************************
$Header:   H:/pvcs/pvcsproj/gomand3d.prj/ICHARS.C_V   1.22   14 Apr 1997 04:20:04   BRUCE  $

$Log:   H:/pvcs/pvcsproj/gomand3d.prj/ICHARS.C_V  $
 * 
 *    Rev 1.22   14 Apr 1997 04:20:04   BRUCE
 * removed scaleframe from the Robot.
 * 
 *    Rev 1.21   21 Mar 1997 15:34:04   JEREMIAH
 * Disabled texture blending for characters.
 * 
 *    Rev 1.20   21 Mar 1997 11:32:12   JEREMIAH
 * Force characters' execute buffers into
 * system memory.
 * 
 *    Rev 1.19   Mar 20 1997 17:13:22   JEREMIAH
 * Set zenable and zwriteenable to TRUE.
 * 
 *    Rev 1.18   12 Mar 1997 13:19:48   BRUCE
 * Used MarksLoadTexture instead of 
 * MyLoadTexture to load the monster's
 * texture maps.
 * 
 *    Rev 1.17   06 Mar 1997 14:49:02   JEREMIAH
 * Optimized execute buffers in 8-bit by 
 * changing from _TRANSFORMLIGHT to 
 * _TRANSFORM.
 * 
 *    Rev 1.16   25 Feb 1997 15:13:32   JEREMIAH
 * Fixed memory leak in reloading texture
 * for beta, gamma monsters.
 * 
 *    Rev 1.15   25 Feb 1997 14:00:44   JEREMIAH
 * Cleaned up arrays of frames for the 
 * characters' body parts.
 * 
 *    Rev 1.14   24 Feb 1997 15:18:32   JEREMIAH
 * Debranched 1.13.1.0 to 1.14.
 * 
 *    Rev 1.13.1.0   24 Feb 1997 12:53:24   JEREMIAH
 * Replaced sound effect for monster melting
 * with special melt sound effect instead of
 * spore splat.
 * 
 *    Rev 1.13   14 Feb 1997 19:44:40   BRUCE
 * removed _47TEK_RL_ code
 * removed _ITC_D3D_ conditional
 * changed level to GameStates.CurrentLevel
 * changed submonster to GameStates.CurrentSubmonster
 * changed In3DMovie to GameStates.Is3DMovie
 * 
 * removed 2 calls to 
 * D3DRENDERSTATE_TEXTUREMAG from 
 * the execute buffer which seemed to be
 * causing the Beta and Gamma monsters
 * to show up incompletely.
 * 
 *    Rev 1.12   07 Feb 1997 08:58:38   BRUCE
 * put a variable mormon in the 
 * createexecubebuffers function so that the
 * Robot could be shiny and the monster could
 * be matte.
 * set texture filtering to be on in accelerated
 * mode
 * set rendering to be gouraud in accelerated
 * mode.
 * 
 *    Rev 1.11   06 Feb 1997 08:17:30   BRUCE
 * took control of whichRobot,
 * removed uninteresting warning.
 * 
 *    Rev 1.10   04 Feb 1997 16:29:36   JEREMIAH
 * Skipped past revision 1.9.
 * Beta 1.02A seems to cause a fatal crash
 * that occurs at QueryInterface when loading
 * the generic building texture.  Reason 
 * unknown.
 * 
 * 
 *    Rev 1.8   22 Jan 1997 12:01:54   JEREMIAH
 * Speeded up monster melt.
 * 
 *    Rev 1.7   21 Jan 1997 10:33:40   TIM
 * No change
 * 
 *    Rev 1.6   06 Jan 1997 16:27:48   JEREMIAH
 * Reduced rampsize on all materials to 1
 * to eliminate palettizing pause bug.
 * 
 *    Rev 1.5   20 Dec 1996 17:06:38   JEREMIAH
 * Changed filenames of textures to match
 * new filename conventions for level-specific
 * palettes.
 * 
 *    Rev 1.4   17 Dec 1996 17:51:34   BRUCE
 * Changed by Tim.  Implemented fix for
 * beta/gamma monsters disappearing or 
 * stretching when retexturing.
 * Kluged by Bruce to trick PVCS into 
 * thinking this is not a branch.
 * 
 *    Rev 1.3.1.0   16 Dec 1996 17:21:44   JEREMIAH
 * Changed by Tim.  Implemented fix for
 * beta/gamma monsters disappearing or 
 * stretching when retexturing.
 * 
 *    Rev 1.3   15 Nov 1996 12:22:22   JEREMIAH
 * Changed by Liou GuoHong (ITC). 
 * Implemented copy mde for 8-bit rendering.

***********************************************************************/
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

#include <d3d.h>
#include "d3dmacs.h"
#include "rl2d3d.h"
#include "mdtex.h"
#include "BinLoad.h"
#include "tekanim.h"
#include "global.h"
#include "d3dappi.h"

#include "landscap.h"
#include "boink.h"
#include "ichars.h"
#include "psystem.h"
#include "spritlib.h"
#include "gosys.h"
#include "building.h"
#include "camera.h"
#include "timing.h"
#include "ybsnd.h"
#include "monmove.h"
#include "monanim.h"
#include "cars.h"


ichar imcharacters[2];

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

extern RLFrame Robotframe;
extern RLFrame monstframe;

extern RLDevice Wdevice;
extern RLFrame Wscene, behindthescene;
extern RLViewport Wview;

Psystem *SixShooter;

extern RLFrame Robotspew;
extern RLValue sealevel;
extern int Vmode;
//extern int level;
extern int MnstLife;
extern int MnstEngy;
extern int sporehunt;
extern RLVector monstorigin;
extern RLFrame MonsterScaleFrame;
extern RLFrame RobotBlockSphere;
extern struct _moving_object_data_ 	MonsterData; 


TEXTURESTRUCT				Robottexture, monsttextures, gloweything;
#define RobotTYPE			0
#define MONSTERTYPE			1
extern int MonsterMovementState;  
extern int MonsterAnimationState;

//int submonster = 0;
RLVector spiritvelocity, globalobjectivevector;
RLFrame spiritframe;
Psystem *spirits;
RLFrame oldtarget;


void CleanupObjectsForIchars (LPDIRECT3DRMOBJECT dev, void* arg)
{
    ipartdlist* thelist = (ipartdlist*) arg;

    if (thelist->eb) 
	{
        thelist->eb->lpVtbl->Release(thelist->eb);
		thelist->mat->lpVtbl->Release(thelist->mat);
        thelist->eb        = NULL;
    }
}

extern int VM_W3D;
extern int VM_H3D;
extern int VM_BPP3D;

BOOL CreateExecubeBufferForIchars (ipartdlist *thelist, LPDIRECT3DRMDEVICE dev, Handle hBin, int IsMonster)
{
    D3DEXECUTEBUFFERDESC desc;
    D3DEXECUTEDATA data;
    LPDIRECT3D lpD3D = NULL;
    LPDIRECT3DDEVICE lpD3DDev = NULL;
    LPDIRECT3DMATERIAL mat = NULL;
    LPDIRECT3DEXECUTEBUFFER eb = NULL;
    D3DMATERIALHANDLE hMat;
    D3DMATERIAL orange;
	DWORD size;
    void* p;
    LPVOID lpInsStart;
	HRESULT LastError;
//	LPD3DDEVICEDESC lpD3DHWDevDesc;
//	LPD3DDEVICEDESC lpD3DHELDevDesc;


	thelist->tcount = GetTCount (hBin, thelist->No) / sizeof(D3DTRIANGLE);
	thelist->vcount = GetVCount (hBin, thelist->No) / sizeof(D3DVERTEX);
// It is old code, Doom said it must be changed...
//	size = GetSize (hBin, thelist->No) + 
//		6 * sizeof(D3DINSTRUCTION) + 2 * sizeof(D3DSTATE) +
//		sizeof(D3DSTATUS) + sizeof(D3DPROCESSVERTICES);
// New code is added by BSH for Doom's Question...
	/*
	//Other person's code.
	size = GetSize (hBin, thelist->No) + 
		8 * sizeof(D3DINSTRUCTION) + 5 * sizeof(D3DSTATE) +
		sizeof(D3DSTATUS) + sizeof(D3DPROCESSVERTICES);
	*/
	//Lgh added.
	size = GetSize (hBin, thelist->No) + 
		9 * sizeof(D3DINSTRUCTION) + 13 * sizeof(D3DSTATE) +
		sizeof(D3DSTATUS) + sizeof(D3DPROCESSVERTICES);
//end...
    dev->lpVtbl->GetDirect3DDevice(dev, &lpD3DDev);
    if (!lpD3DDev)
	{
        goto generic_error;
	}
    if (FAILED(lpD3DDev->lpVtbl->GetDirect3D(lpD3DDev, &lpD3D)))
    {
		goto generic_error;
	}

    desc.dwSize = sizeof(desc);
    desc.dwFlags = D3DDEB_BUFSIZE | D3DDEB_CAPS;
    desc.dwBufferSize = size;
//	if (d3dappi.ThisDriver.Desc.dwDevCaps & D3DDEVCAPS_EXECUTESYSTEMMEMORY)
		desc.dwCaps = D3DDEBCAPS_SYSTEMMEMORY;
//	else
//		desc.dwCaps = D3DDEBCAPS_VIDEOMEMORY;
    
    if (((LastError = lpD3DDev->lpVtbl->CreateExecuteBuffer(lpD3DDev, &desc, &eb, NULL))) != DD_OK)
    {
		BYDumpInfo("Failed to CreateExecuteBuffer for Ichar");
		BYDumpInfo(D3DAppErrorToString(LastError));
		goto generic_error;
	}

    if (FAILED(lpD3D->lpVtbl->CreateMaterial(lpD3D, &mat, NULL)))
    {
		goto generic_error;
	}
    if (FAILED(mat->lpVtbl->GetHandle(mat, lpD3DDev, &hMat)))
	{
        goto generic_error;
	}
    memset(&orange, 0, sizeof(orange));
    orange.dwSize = sizeof(orange);
    orange.diffuse.r = D3DVAL(1.0);
    orange.diffuse.g = D3DVAL(1.0);
    orange.diffuse.b = D3DVAL(1.0);
    orange.ambient.r = D3DVAL(1.0);
    orange.ambient.g = D3DVAL(1.0);
    orange.ambient.b = D3DVAL(1.0);
	 if(IsMonster)
	 {
		 orange.specular.r=D3DVAL(0.0);
		 orange.specular.g=D3DVAL(0.0);
		 orange.specular.b=D3DVAL(0.0);
		 orange.emissive.r=D3DVAL(0.4);
		 orange.emissive.g=D3DVAL(0.4);
		 orange.emissive.b=D3DVAL(0.4);
		 orange.power=D3DVAL(0.0);
	 }
	 else
	 {
		 orange.specular.r=D3DVAL(1.0);
		 orange.specular.g=D3DVAL(0.25);
		 orange.specular.b=D3DVAL(0.0);
		 orange.emissive.r=D3DVAL(0.6);
		 orange.emissive.g=D3DVAL(0.6);
		 orange.emissive.b=D3DVAL(0.6);
		 orange.power=D3DVAL(60.0);
	 }
    orange.dwRampSize = 1;
	if (thelist->Parent == RobotTYPE)
	{
		orange.hTexture = imcharacters[RobotTYPE].lpTexture->hTex;	
	}
	else if (thelist->Parent == MONSTERTYPE)
	{
		orange.hTexture = imcharacters[MONSTERTYPE].lpTexture->hTex;
	}
    if (FAILED(mat->lpVtbl->SetMaterial(mat, &orange)))
	{
        goto generic_error;
	}
    if (FAILED(eb->lpVtbl->Lock(eb, &desc)))
    {
		goto generic_error;
	}
	p = (void*) ((char*) desc.lpData);

	memset(p, 0, size);
//BSH think this code has nothing, so close it...
//	thelist->Vertex = p;

	if ((p = LoadVertex(hBin, thelist->No, p)) == NULL) // Copy 'Spudde's code !
	{
		;
	}

    lpInsStart = p; // Be added by Doom !

    OP_STATE_LIGHT(1, p);
        STATE_DATA(D3DLIGHTSTATE_MATERIAL, hMat, p);
        
    OP_SET_STATUS(D3DSETSTATUS_ALL, D3DSTATUS_DEFAULT, 2048, 2048, 0, 0, p);
    
	if (VM_BPP3D == 8)
   {
    OP_PROCESS_VERTICES(1, p);
        PROCESSVERTICES_DATA(D3DPROCESSVERTICES_TRANSFORM,
                         0, GetVCount(hBin, thelist->No)/sizeof (D3DVERTEX), p);
   }
   else
   {
    OP_PROCESS_VERTICES(1, p);
        PROCESSVERTICES_DATA(D3DPROCESSVERTICES_TRANSFORMLIGHT,
                         0, GetVCount(hBin, thelist->No)/sizeof (D3DVERTEX), p);
   }
// Some new code be added by BSH for DongMing's question....
    OP_STATE_RENDER(1, p);
        STATE_DATA(D3DRENDERSTATE_SHADEMODE, d3dapprs.ShadeMode, p);

    OP_STATE_RENDER(3, p);
		STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE, orange.hTexture, p);	//Liou qinghua
        STATE_DATA(D3DRENDERSTATE_WRAPV, FALSE, p);
        STATE_DATA(D3DRENDERSTATE_WRAPU, FALSE, p);

 	//Lgh added.
	if ((VM_BPP3D == 8))
	{
		OP_STATE_RENDER(3, p);
			STATE_DATA(D3DRENDERSTATE_BLENDENABLE, FALSE, p);
			STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_COPY, p);	
			STATE_DATA(D3DRENDERSTATE_DESTBLEND, D3DBLEND_DESTALPHA, p);	
	}
	else
	{
		OP_STATE_RENDER(1, p);
			STATE_DATA(D3DRENDERSTATE_BLENDENABLE, FALSE, p);
	}
		OP_STATE_RENDER(2, p);
			STATE_DATA(D3DRENDERSTATE_ZENABLE, TRUE, p);
			STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE, TRUE, p);

	if (QWORD_ALIGNED(p)) 
	{
        OP_NOP(p);
    }

	OP_TRIANGLE_LIST( (int) GetTCount(hBin, thelist->No) / sizeof(D3DTRIANGLE), p);

//BSH think this code has nothing, so close it !
//	thelist->Triangle = p;

	if ((p = LoadTriangle(hBin, thelist->No, p)) == NULL) // Copy 'Spudde' code !
	{
		;
	}
    OP_EXIT(p);

    if (FAILED(eb->lpVtbl->Unlock(eb)))
    {
		goto generic_error;
	}

    data.dwSize              = sizeof(data);
    data.dwVertexOffset      = 0;
	data.dwVertexCount		 = GetVCount(hBin, thelist->No) / sizeof(D3DVERTEX);
    data.dwInstructionOffset = GetVCount(hBin,thelist->No);
// Be added for Doom...
    data.dwInstructionLength = (ULONG) ((char *)p - (char *)lpInsStart);
//	data.dwInstructionLength = size - data.dwInstructionOffset; // For Doom closing...
//  data.dwHVertexOffset     = 0; // For Doom closing...
    
	if (FAILED(eb->lpVtbl->SetExecuteData(eb, &data)))
    {   
		goto generic_error;
	}
    thelist->eb  = eb;
    thelist->mat = mat;
    if (FAILED(dev->lpVtbl->AddDestroyCallback(dev, CleanupObjectsForIchars, thelist)))
    {
		goto generic_error;
	}
    RELEASE(lpD3DDev);
    RELEASE(lpD3D);
    return TRUE;
generic_error:
    RELEASE(lpD3D);
    RELEASE(lpD3DDev);
    RELEASE(mat);
    RELEASE(eb);
    return FALSE;
}

BOOL ReplaceTextureForEB (ipartdlist *thelist)
{
    D3DEXECUTEBUFFERDESC desc;
    D3DEXECUTEDATA data;
    LPDIRECT3D lpD3D = NULL;
    LPDIRECT3DDEVICE lpD3DDev = NULL;
    LPDIRECT3DMATERIAL mat = NULL;
    LPDIRECT3DEXECUTEBUFFER eb = NULL;
    D3DMATERIALHANDLE hMat;
    D3DMATERIAL orange;
	DWORD size;
    void* p;
	DWORD Vsize, Tsize;
    LPVOID lpInsStart;

    Tsize = thelist->tcount * sizeof (D3DTRIANGLE);
	Vsize = thelist->vcount * sizeof (D3DVERTEX);
	eb	  = thelist->eb;
	mat   = thelist->mat;

//	size = Vsize + Tsize + 8 * sizeof(D3DINSTRUCTION) + 5 * sizeof(D3DSTATE) +
//		sizeof(D3DSTATUS) + sizeof(D3DPROCESSVERTICES);
	size = Vsize + Tsize + 
		9 * sizeof(D3DINSTRUCTION) + 13 * sizeof(D3DSTATE) +
		sizeof(D3DSTATUS) + sizeof(D3DPROCESSVERTICES);

    Wdevice->lpVtbl->GetDirect3DDevice(Wdevice, &lpD3DDev);
    if (!lpD3DDev)
	{
        goto generic_error;
	}
    if (FAILED(lpD3DDev->lpVtbl->GetDirect3D(lpD3DDev, &lpD3D)))
    {
		goto generic_error;
	}
    desc.dwSize = sizeof(desc);
    desc.dwFlags = D3DDEB_BUFSIZE | D3DDEB_CAPS;
    desc.dwBufferSize = size;
	desc.dwCaps = D3DDEBCAPS_SYSTEMMEMORY;
    if (FAILED(mat->lpVtbl->GetHandle(mat, lpD3DDev, &hMat)))
	{
        goto generic_error;
	}
    memset (&orange, 0, sizeof(orange));
    orange.dwSize = sizeof(orange);
    orange.diffuse.r = D3DVAL(1.0);
    orange.diffuse.g = D3DVAL(1.0);
    orange.diffuse.b = D3DVAL(1.0);
    orange.ambient.r = D3DVAL(1.0);
    orange.ambient.g = D3DVAL(1.0);
    orange.ambient.b = D3DVAL(1.0);
    orange.dwRampSize = 1;
	if (thelist->Parent == RobotTYPE)
	{
		orange.hTexture = imcharacters[RobotTYPE].lpTexture->hTex;
	}
	else if (thelist->Parent == MONSTERTYPE)
	{
		orange.hTexture = imcharacters[MONSTERTYPE].lpTexture->hTex;
	}
    if (FAILED(mat->lpVtbl->SetMaterial(mat, &orange)))
	{
        goto generic_error;
	}
    if (FAILED(eb->lpVtbl->Lock(eb, &desc)))
    {
		goto generic_error;
	}
	p = (void*) ((char*) desc.lpData + Vsize);

	lpInsStart = p; // Be added for Doom !

    OP_STATE_LIGHT(1, p);
        STATE_DATA(D3DLIGHTSTATE_MATERIAL, hMat, p);
        
    OP_SET_STATUS(D3DSETSTATUS_ALL, D3DSTATUS_DEFAULT, 2048, 2048, 0, 0, p);
    
	if (VM_BPP3D == 8)
   {
    OP_PROCESS_VERTICES(1, p);
        PROCESSVERTICES_DATA(D3DPROCESSVERTICES_TRANSFORM,
                         0, thelist->vcount, p);
   }
   else
   {
    OP_PROCESS_VERTICES(1, p);
        PROCESSVERTICES_DATA(D3DPROCESSVERTICES_TRANSFORMLIGHT,
                         0, thelist->vcount, p);
   }
// Some new code be added by BSH for Doom's question...
    OP_STATE_RENDER(1, p);
        STATE_DATA(D3DRENDERSTATE_SHADEMODE, d3dapprs.ShadeMode, p);

    OP_STATE_RENDER(3, p);
		STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE, orange.hTexture, p);	//Liou qinghua
        STATE_DATA(D3DRENDERSTATE_WRAPV, FALSE, p);
        STATE_DATA(D3DRENDERSTATE_WRAPU, FALSE, p);

    if (VM_BPP3D == 8)
	{
		OP_STATE_RENDER(3, p);
			STATE_DATA(D3DRENDERSTATE_BLENDENABLE, FALSE, p);
			STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_COPY, p);	
			STATE_DATA(D3DRENDERSTATE_DESTBLEND, D3DBLEND_DESTALPHA, p);	
	}
	else
	{
		OP_STATE_RENDER(1, p);
			STATE_DATA(D3DRENDERSTATE_BLENDENABLE, FALSE, p);
	}

		OP_STATE_RENDER(2, p);
			STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE, TRUE, p);
			STATE_DATA(D3DRENDERSTATE_ZENABLE, TRUE, p);

    if (QWORD_ALIGNED(p)) 
	{
        OP_NOP(p);
    }

	OP_TRIANGLE_LIST( (int) thelist->tcount, p);

	p = (void*) ((char*) p + Tsize);
    OP_EXIT(p);

    if (FAILED(eb->lpVtbl->Unlock(eb)))
    {
		goto generic_error;
	}

    data.dwSize              = sizeof(data);
    data.dwVertexOffset      = 0;
	data.dwVertexCount		 = thelist->vcount;
    data.dwInstructionOffset = Vsize;
// Be added for Doom...
    data.dwInstructionLength = (ULONG) ((char *)p - (char *)lpInsStart);
//	data.dwInstructionLength = size - data.dwInstructionOffset;
//    data.dwHVertexOffset     = 0;
  
	if (FAILED(eb->lpVtbl->SetExecuteData(eb, &data)))
    {   
		goto generic_error;
	}
    RELEASE(lpD3DDev);
    RELEASE(lpD3D);
    return TRUE;
generic_error:
    RELEASE(lpD3D);
    RELEASE(lpD3DDev);
    return FALSE;
}

BOOL RenderObjectForIchars(ipartdlist *thelist,  LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view)
{
//    D3DVERTEX* v;
    D3DEXECUTEBUFFERDESC desc;
    D3DEXECUTEDATA data;
    LPDIRECT3DDEVICE lpD3DDev = NULL;
    LPDIRECT3DVIEWPORT lpD3DView = NULL;
	HRESULT rval;

	// bCanShow is change by the function of RenderCharacters.
	if (imcharacters[thelist->Parent].bCanShow) 
	{
		dev->lpVtbl->GetDirect3DDevice(dev, &lpD3DDev);
		view->lpVtbl->GetDirect3DViewport(view, &lpD3DView);
		if (!lpD3DDev || !lpD3DView)
		{
			goto ret_with_error;
		}

		desc.dwSize = sizeof(desc);
		desc.dwFlags = 0;
/*    
		if (FAILED(thelist->eb->lpVtbl->Lock(thelist->eb, &desc)))
		{
			goto ret_with_error;
		}

		v = (D3DVERTEX*) desc.lpData;

		if (FAILED(thelist->eb->lpVtbl->Unlock(thelist->eb)))
		{
			goto ret_with_error;
		}22
*/
		if (FAILED(lpD3DDev->lpVtbl->Execute(lpD3DDev, thelist->eb, lpD3DView, D3DEXECUTE_CLIPPED)))
		{
			goto ret_with_error;
		}

		data.dwSize = sizeof data;

		if (FAILED(thelist->eb->lpVtbl->GetExecuteData(thelist->eb, &data)))
		{
			goto ret_with_error;
		}
	
		if ((data.dsStatus.drExtent.x1 == 2048) ||
			(data.dsStatus.drExtent.y1 == 2048))
		{
			return TRUE;
		}

		if (FAILED(rval = view->lpVtbl->ForceUpdate(view, data.dsStatus.drExtent.x1,
						  data.dsStatus.drExtent.y1,
						  data.dsStatus.drExtent.x2,
						  data.dsStatus.drExtent.y2)))
		{                      
			if (rval != D3DRMERR_BADVALUE)
			{
				goto ret_with_error;
			}
		}
		RELEASE(lpD3DDev);
		RELEASE(lpD3DView);
	}// endif (imcharacters[thelist->Parent].bCanShow)
	return TRUE;
ret_with_error:
    RELEASE(lpD3DDev);
    RELEASE(lpD3DView);
    return FALSE;
}

int ObjectCallbackForIchars(LPDIRECT3DRMUSERVISUAL uvis,
                 void* arg,
                 D3DRMUSERVISUALREASON reason,
                 LPDIRECT3DRMDEVICE dev,
                 LPDIRECT3DRMVIEWPORT view)
{
    ipartdlist *thelist = (ipartdlist*) arg;

    if (reason == D3DRMUSERVISUAL_CANSEE)
	{
		return TRUE;
	}
    if (reason == D3DRMUSERVISUAL_RENDER) 
	{
        if (!RenderObjectForIchars(thelist, dev, view))
		{
            return DDERR_GENERIC;
		}
        else
		{
            return D3D_OK;
		}
    }
    return 0;
}

void DestroyObjectForIchars (LPDIRECT3DRMOBJECT obj, void* arg)
{
    ipartdlist *thelist = (ipartdlist*) arg;

	if (Wdevice)
	{
		Wdevice->lpVtbl->DeleteDestroyCallback(Wdevice, CleanupObjectsForIchars, arg);
	}
	CleanupObjectsForIchars((LPDIRECT3DRMOBJECT)Wdevice, (void*) thelist);

//    free (thelist);
//	thelist = NULL;
}

// ****************************************************************
// Initialization Functions
// ****************************************************************
// called from init
extern char BmpPath[];
void ConstructDLists(RLFrame charframe, Handle hBin)
{
	int mormon;
	char TextureFileName[MAX_PATH];

	RLFrame parentframe = RLFrameGetParent(charframe);
	// determine if model is Robot or monster

    strcpy(TextureFileName, BmpPath);
    strcat(TextureFileName, "\\");

	mormon = -1;
	if (charframe == Robotframe) 
	{
		mormon = 0;
		memset(&imcharacters[mormon], 0, sizeof(ichar));
		imcharacters[mormon].bCanShow = FALSE; 
		MyLoadTexture(Wdevice, ConstructRobotName(GameStates.CurrentRobot, "191.bmp"), 
			&Robottexture, 0); // NEW add !
		imcharacters[mormon].lpTexture = &Robottexture;
	}
	else if (parentframe == monstframe) 
	{
		char monsttexname[16];
		mormon = 1;
		switch (GameStates.CurrentSubmonster) 
		{
			case Alpha:
				strcpy(monsttexname, "108b.bmp");
				break;
			case Beta:
				strcpy(monsttexname, "108.bmp");
				break;
			case Gamma:
				strcpy(monsttexname, "108r.bmp");
				break;
		}
		memset(&imcharacters[mormon], 0, sizeof(ichar));
		imcharacters[mormon].bCanShow = FALSE; 

		MyLoadTexture(Wdevice, ConstructLevelName(monsttexname), 
			&monsttextures, 0); // NEW add !
		imcharacters[mormon].lpTexture = &monsttextures;
	}
	// BIG GAMEPLAY QUESTION -- RESET SUBMONSTER OR NOT?
	//submonster = 0;
	if (mormon < 0) 
	{
		return;	// if neither then abort
	}

	imcharacters[mormon].firstipartdlist = NULL;	// terminate linked list
	
	StepDownHierarchy(hBin, charframe, mormon);			// enter recursion
}

RLFrame *framearray[2];

void StepDownHierarchy (Handle hBin, RLFrame parentframe, int mormon)
{
	unsigned int	parent;
	int				NoObj;
	//RLFrame			*frame;
    long			*CountObjects;
	char			*address;
	
  	CountObjects = (long*) hBin->BinaryStart; // reference BinLoad.c file...
	// Search hierarchy location...
	address =  (char *) ( ((sizeof(long)) * (( (*CountObjects) * 2) + 2)) + ( (char *) hBin->BinaryStart) ) ;
    framearray[mormon] = (RLFrame*) malloc (*CountObjects * sizeof(RLFrame));
    for (NoObj = 0; NoObj < *CountObjects; NoObj++)
	{
        framearray[mormon][NoObj] = RLCreateFrame(parentframe);
//		frame[NoObj]->lpVtbl->SetName(frame[NoObj], GetNameFromTreData(NoObj));
		if (parentframe == Robotframe)
		{
			framearray[mormon][NoObj]->lpVtbl->SetName(framearray[mormon][NoObj], GetRobotNameFromTreData(NoObj));
		}
		else
		{
			framearray[mormon][NoObj]->lpVtbl->SetName(framearray[mormon][NoObj], GetMonstNameFromTreData(NoObj));
		}
	}
	for (NoObj = 0; NoObj < *CountObjects; NoObj++) 
	{
		parent = *address;

		if(parent == 0)
		{
			 //In StepDownHierarchy, the code will be like this -Spudde
			 parentframe->lpVtbl->AddChild(parentframe, framearray[mormon][NoObj]);
		}
	    else
	    {
		    parent--;   // Set The Parent to the Correct Index into Array.
			// In StepDownHierarchy, the code will be like this -Spudde
			 parentframe->lpVtbl->AddChild(framearray[mormon][parent], framearray[mormon][NoObj]);
		}
		address += (sizeof(long));     // Point to the Next Compound Model Object in Heriarchy.
		MeshestoDList(hBin, framearray[mormon][NoObj], NoObj, mormon); // convert meshes to display lists
	}
}

BOOL MeshestoDList (Handle hBin, RLFrame frame, int NoObj, int mormon)
{
	ipartdlist *nextone;
    LPDIRECT3DRMUSERVISUAL uvis = NULL;

	// setup new node in linked list
	RLMalloc((void**)&nextone, sizeof(ipartdlist));
	memset (nextone, 0, sizeof (ipartdlist));
	nextone->nextpart = imcharacters[mormon].firstipartdlist;
	imcharacters[mormon].firstipartdlist = nextone;

	nextone->frame		= frame;
	nextone->freeframe	= RLCreateFrame(Wscene);
	nextone->Parent		= mormon;
	nextone->No 		= NoObj;

    CreateExecubeBufferForIchars (nextone, Wdevice, hBin, mormon);

    if (FAILED(lpD3DRM->lpVtbl->CreateUserVisual(lpD3DRM, ObjectCallbackForIchars, (void*) nextone, &uvis)))
    {
		goto ret_with_error;
	}
    if (FAILED(uvis->lpVtbl->AddDestroyCallback(uvis, DestroyObjectForIchars, (void*) nextone)))
    {
		goto ret_with_error;   
	}
	if (uvis)
	{
   	    nextone->frame->lpVtbl->AddVisual (nextone->frame, (LPDIRECT3DRMVISUAL)uvis);
		nextone->uvis = uvis;
	}

    RELEASE(uvis);
	return (TRUE);
ret_with_error:
	if (nextone)
	{
        free(nextone);
	}
    RELEASE(uvis);
    return FALSE;
}

void DestroyDLists(void)
{
	int mormon;

	for (mormon = 0; mormon < 2; mormon++) 
	{
		ReleaseOneTexture(imcharacters[mormon].lpTexture);
		imcharacters[mormon].lpTexture = NULL;
		KillAPart(imcharacters[mormon].firstipartdlist);
      free(framearray[mormon]);
	}
}

void KillAPart(ipartdlist *parts)
{
	ipartdlist *nextpart = parts->nextpart;
	// BSH write this code, old GOMAN95 don't use...
	if (parts->frame != parts->freeframe)
	{
		MDFreeD3DFrame (parts->freeframe);
		parts->freeframe = NULL;
		MDFreeD3DFrame (parts->frame);
		parts->frame = NULL;
	}
	else 
	{
		MDFreeD3DFrame (parts->freeframe);
		parts->freeframe = NULL;
	}
    free (parts);
	parts = NULL;
	if (nextpart) 
	{
		KillAPart (nextpart);
	}
}

// ****************************************************************
// Manipulation Functions
// ****************************************************************

// Be called by 'gosys.c' file.
int ExplodeARobot()
{
	int i;
	for(i = 0; i < SixShooter->properties->num; i++)
	{
		SixShooter->particles[i]->active = 0;
		SixShooter->particles[i]->plane->active = 0;//liou qinghua 96,09/04
	}
	return FlingAPart(imcharacters[0].firstipartdlist, 0);
}


int FlingAPart(ipartdlist *parts, int mormon)
{
	RLValue height;
	RLVector separation, velocity, parentplace, childplace;
	RLFrame parent, topframe = (mormon ? monstframe : Robotframe);

	SixShooter->active				 = 0;
	SixShooter->numonscreen			 = 0;
	//SixShooter->particles[0]->active = 0;
	//SixShooter->particles[0]->plane->active = 0;//liou qinghua 96,09/04

	if ((parts->frame) != parts->freeframe) 
	{
		parent = RLFrameGetParent(parts->frame);
		RLFrameGetPosition(parts->frame, Wscene, &childplace);
		RLFrameGetPosition(parent, Wscene, &parentplace);
		separation.x = childplace.x - parentplace.x;
		separation.y = childplace.y - parentplace.y;
		separation.z = childplace.z - parentplace.z;

		parts->freeframe->lpVtbl->AddVisual (parts->freeframe,
			(LPDIRECT3DRMVISUAL)(parts->uvis));
		parts->frame->lpVtbl->DeleteVisual (parts->frame, 
			(LPDIRECT3DRMVISUAL)(parts->uvis));

		parts->frame = parts->freeframe;
		SixShooter->active = 1;
		SixShooter->numonscreen = 1;
		RLFrameLookAt(Robotspew, SixShooter->camera, Wscene, RLConstrainY);
		SixShooter->particles[0]->active = 1;
		RLFrameSetPosition(Robotspew, Wscene, 
			childplace.x, childplace.y, childplace.z);
//Why...		
		RLFrameSetPosition (parts->frame, Wscene, 
			childplace.x, childplace.y, childplace.z);
//same GetPosition...

		RLFrameSetVelocity (parts->frame, Wscene, 
			RLVal(0.5 * separation.x), 
			RLVal(5.0 * separation.y), 
			RLVal(0.5 * separation.z));
		RLFrameSetRotation (parts->frame, Wscene, 
			separation.z, RLVal(0.0), separation.x, separation.y);
		return(1);
	} 
	else 
	{
		RLFrameGetVelocity (parts->frame, Wscene, &velocity);
		RLFrameGetPosition (parts->frame, Wscene, &separation);
		height = SpuddeMapHeight2 (separation.x, separation.z);
		if (height > separation.y) 
		{
			RLFrameSetPosition (parts->frame, Wscene, 
				separation.x, height + RLVal(0.001), separation.z);
			if (fabs(velocity.y) > RLVal(0.5)) 
			{
				velocity.y += RLVal(1.35 * fabs(velocity.y));
				velocity.x *= RLVal(0.35);
				velocity.z *= RLVal(0.35);
				YBPlay3DSound (Bounce, parts->frame);
				RLFrameSetRotation (parts->frame, Wscene, 
					velocity.z, RLVal(0.0), velocity.x, velocity.y);
			} 
			else 
			{
				velocity.y = RLVal (0.0);
				velocity.x = RLVal (0.0);
				velocity.z = RLVal (0.0);
				RLFrameSetRotation (parts->frame, Wscene, 
					RLVal(0.0), RLVal(1.0), RLVal(0.0), RLVal(0.0));
			}
		} 
		else 
		{
			velocity.y -= RLVal(0.02);
		}
		RLFrameSetVelocity (parts->frame, Wscene, velocity.x, velocity.y, velocity.z);
	}
	if (parts->nextpart) 
	{
		return FlingAPart (parts->nextpart, mormon);
	}
	else
	{
		return 0;
	}
}

extern struct _moving_object_data_ 	MonsterData; 
extern visible_buildings missiontarget;
struct _moving_object_data_ spiritdata;

// Be called by 'momanim2.c' file.
void KillSubMonster()
{
	visible_buildings theegg;

	FindOneBuilding (&theegg, 66 + GameStates.CurrentSubmonster + 1);
	if (theegg.count == 1) 
	{
		globalobjectivevector.x = RLVal(theegg.building_ptr[0]->x_world - LANDXCENTER);
		globalobjectivevector.y = RLVal(theegg.building_ptr[0]->y_world);
		globalobjectivevector.z = RLVal(theegg.building_ptr[0]->z_world - LANDZCENTER);
	}
	ReleaseSpirit();
}

void ReleaseSpirit()
{
	RLVector monstplace;
	RLValue mod;
	int wholemod;
	extern Caminfo* camerastuff;

	RLFrameAddChild (Wscene, spiritframe);
	RLFrameGetPosition (monstframe, Wscene, &monstplace);
	RLFrameSetPosition (spiritdata.PositioningFrame, Wscene, 
		monstplace.x, monstplace.y, monstplace.z);
	spiritdata.CurrentPosition.x = spiritdata.ProjectedPosition.x = monstplace.x;
	spiritdata.CurrentPosition.y = spiritdata.ProjectedPosition.y = monstplace.y;
	spiritdata.CurrentPosition.z = spiritdata.ProjectedPosition.z = monstplace.z;
	spiritvelocity.x = globalobjectivevector.x - spiritdata.CurrentPosition.x;
	spiritvelocity.y = globalobjectivevector.y - spiritdata.CurrentPosition.y;
	spiritvelocity.z = globalobjectivevector.z - spiritdata.CurrentPosition.z;
	mod = RLVectorModulus (&spiritvelocity);
	wholemod = RLInt(mod);
	spiritvelocity.x /= wholemod;
	spiritvelocity.y /= wholemod;
	spiritvelocity.z /= wholemod;
 	spiritdata.RemoveMeFlag = 0;
	oldtarget = RLFrameGetParent(camerastuff->target);
	if ((oldtarget == monstframe)) 
	{
		SetCameraTarget (camerastuff, spiritdata.PositioningFrame);
        camerastuff->method = SLUGDRIFT;
		camerastuff->zone = 6;
	}
	AddMovingObject(&spiritdata);
	KillAllBadCars();
}

//Be called by 'SpiritMotionFunction'.
void ResurectSubMonster()
{
	//submonster++;
	GameStates.CurrentSubmonster++;
	ReTextureMonster (&imcharacters[1]); // BSH new change ...
	MnstLife = 100;
	MnstEngy = 65536;
	// when we care, we'll call some setmonstermotionconstantsblahblahblah() function.
	MonsterMovementState = 0;
	MonsterAnimationState = 0;
	PlaceMonster (GameStates.CurrentLevel, 0);
}

void ReTextureMonster(ichar *imchars)
{
	char		monsttexname[16];
	ipartdlist	*thelist, *nextlist;

	switch (GameStates.CurrentSubmonster) 
	{
		case Alpha:
			strcpy(monsttexname, "108b.bmp");
			break;
		case Beta:
			strcpy(monsttexname, "108.bmp");
			break;
		case Gamma:
			strcpy(monsttexname, "108r.bmp");
			break;
	}

	if (imchars->lpTexture)
	{
		ReleaseOneTexture(imchars->lpTexture);
	}

	memset (imchars->lpTexture, 0, sizeof(TEXTURESTRUCT));
	MarksLoadTexture(Wdevice, ConstructLevelName(monsttexname), 
		imchars->lpTexture, 0); 

	thelist = imchars->firstipartdlist;
	nextlist = thelist->nextpart;
	while (thelist)
	{
		if (!ReplaceTextureForEB (thelist))
		{
			return ;
		}
		thelist = nextlist;
		if (nextlist)
		{
			nextlist = nextlist->nextpart;
		}
	}
}

void SpiritInit()
{
	spiritdata.Volume.max.x = RLVal(-257);
	spiritdata.Volume.max.y = RLVal(-257);
	spiritdata.Volume.max.z = RLVal(-258);
	spiritdata.Volume.min.x = RLVal(256.5);
	spiritdata.Volume.min.y = RLVal(256.1);
	spiritdata.Volume.min.z = RLVal(257);
	spiritdata.DamageICause = 0;
	if (RLObjectExists(spiritframe) == RLNoError)
	{
		spiritdata.PositioningFrame = spiritframe;
	}
	else
	{
		spiritdata.PositioningFrame = spiritframe = RLCreateFrame(Wscene);
	}
	spiritdata.NumOffensiveSpheres = 0;
	spiritdata.NumDefensiveSpheres = 0;
	spiritdata.NumOffensiveTubes = 0;
	spiritdata.AnimateMe = NULL;
	spiritdata.MoveMe = SpiritMotionFunction;
	spiritdata.HandleMe = SpiritCollisionFunction;
	spiritdata.SafePassageIndex = NULL;
	spiritdata.mass = RLVal(0);
	MakeSpiritSprite(&spirits, spiritframe, ConstructLevelName("glowy.bmp"));
}

void SpiritMotionFunction (MovingObjectData movedata)
{
	RLVector Position1;
	RLValue Height;
	RLFrame Scene = RLFrameGetScene(movedata->PositioningFrame);
	extern RLFrame Wcamera;
	extern Caminfo* camerastuff;
	extern RLFrame goodguyframe;
//	extern BOOL In3DMovie;

	movedata->CurrentPosition.x = movedata->ProjectedPosition.x;
	movedata->CurrentPosition.y = movedata->ProjectedPosition.y;
	movedata->CurrentPosition.z = movedata->ProjectedPosition.z;

	spirits->particles[0]->active = 1;
	MonsterData.RemoveMeFlag = 1;
	if (spirits->particles[0]->plane->y1 < RLVal(0.5)) 
	{
		spirits->particles[0]->plane->y1 += RLVal(0.5);
	}
	else 
	{
		spirits->particles[0]->plane->y1 -= RLVal(0.5);
	}
	if (spirits->particles[0]->plane->y2 < RLVal(0.5)) 
	{
		spirits->particles[0]->plane->y2 += RLVal(0.5);
	}
	else 
	{
		spirits->particles[0]->plane->y2 -= RLVal(0.5);
	}

	if (!GameStates.Is3DMovie) 
	{
		RLFrameAddScale(MonsterScaleFrame, RLCombineAfter, RLVal(1.0), RLVal(0.95), RLVal(1.0));
	}

	Position1.x = globalobjectivevector.x - movedata->CurrentPosition.x;
	Position1.y = globalobjectivevector.y - movedata->CurrentPosition.y;
	Position1.z = globalobjectivevector.z - movedata->CurrentPosition.z;

	if (RLFrameGetParent(camerastuff->target) == movedata->PositioningFrame) 
	{
		RLFrameSetOrientation (movedata->PositioningFrame, Wscene, 
			-Position1.x, RLVal(0), -Position1.z, RLVal(0), RLVal(1), RLVal(0));		
	}
	else
   	{
		RLFrameSetOrientation (movedata->PositioningFrame, Wcamera, 
			RLVal(0), RLVal(0), RLVal(1), RLVal(0), RLVal(1), RLVal(0));
	}

   	if ((!GameStates.Is3DMovie) && 
		(Position1.x * Position1.x + Position1.z * Position1.z < RLVal(4.0))) 
   	{
		MonsterData.RemoveMeFlag = 0;
		AddMovingObject (&MonsterData);
   		movedata->RemoveMeFlag = 1;
		ResurectSubMonster();
		spirits->particles[0]->active = 0;
		if ((oldtarget == monstframe)) 
		{
			SetCameraTarget (camerastuff, oldtarget);
			camerastuff->zone=2;
		}
	}
   movedata->ProjectedPosition.x = movedata->CurrentPosition.x + spiritvelocity.x;
   movedata->ProjectedPosition.z = movedata->CurrentPosition.z + spiritvelocity.z;
   Height = 
	   SpuddeMapHeight2(movedata->ProjectedPosition.x, movedata->ProjectedPosition.z);

   if (movedata->CurrentPosition.y > Height + RLVal(1.0))
   {
      spiritvelocity.y = ((Height + RLVal(1.0)) - movedata->CurrentPosition.y);
   }
   else if (movedata->CurrentPosition.y < Height + RLVal(0.5))
   {
      spiritvelocity.y = ((Height + RLVal(0.5)) - movedata->CurrentPosition.y);
   }
   else
   {
	   spiritvelocity.y = (float) 0;
   }
   movedata->ProjectedPosition.y = movedata->CurrentPosition.y + spiritvelocity.y;
}

void SpiritCollisionFunction(MovingObjectData movedata)
{
	;
}

//Be called by 'camera.c' file...
int MeltAMonster(int alive)
{
	RLVector wheresthemonster;
	
	sporehunt = 0;
	RLFrameGetPosition (monstframe, Wscene, &wheresthemonster);
	
	if (!(rand()&0x3)) 
	{
	//	YBPlay3DSound(Splat, monstframe);
      YBPlay3DSound(Melt, monstframe);
	}
	
	return MeltAPart (imcharacters[1].firstipartdlist, &wheresthemonster, alive);
}	

int MeltAPart(ipartdlist *parts, RLVector* modelposition, int alive)
{
	int						i, retval = 0;
	RLValue					groundheight;
	RLVector				ModelVector, WorldVector;
    D3DEXECUTEBUFFERDESC	desc;

	desc.dwSize = sizeof(desc);
	desc.dwFlags = 0;
	parts->eb->lpVtbl->Lock (parts->eb, &desc);
	parts->Vertex = (D3DVERTEX*) desc.lpData;

	for (i = 0; i < (int)parts->vcount; i++) 
	{
		// Note: the type of 'parts->Vertex' is D3DVertex, no D3DVector.
		ModelVector.x = parts->Vertex[i].x;
		ModelVector.y = parts->Vertex[i].y;
		ModelVector.z = parts->Vertex[i].z;

		// move vertex to world coords
		RLFrameTransform(parts->frame, &WorldVector, &ModelVector);
		parts->Vertex[i].x = WorldVector.x;
		parts->Vertex[i].y = WorldVector.y;
		parts->Vertex[i].z = WorldVector.z;
			
		// drop vertex down
		groundheight = 
			MAX (SpuddeMapHeight2(parts->Vertex[i].x, parts->Vertex[i].z), sealevel) 
			+ RLVal(0.01);

		if (parts->Vertex[i].y < groundheight) 
		{
			parts->Vertex[i].y = groundheight;
		}
		else 
			if ((rand()&0x3) != 0) 
		    {
				parts->Vertex[i].y = groundheight + 
					RLVal(0.97*(parts->Vertex[i].y) - groundheight);
		    }
		// move vertex back to frame coords
		if (parts->Vertex[i].y > groundheight + RLVal(0.02)) 
		{
			retval = 1;
		}

		WorldVector.x = parts->Vertex[i].x;
		WorldVector.y = parts->Vertex[i].y;
		WorldVector.z = parts->Vertex[i].z;
		RLFrameInverseTransform(parts->frame, &ModelVector, &WorldVector);
		parts->Vertex[i].x = ModelVector.x;
		parts->Vertex[i].y = ModelVector.y;
		parts->Vertex[i].z = ModelVector.z;
	}
// New code add by BSH for Doom...
	parts->eb->lpVtbl->Unlock(parts->eb);
// end...
	// go on to next part
	if (parts->nextpart) 
	{
		retval += MeltAPart(parts->nextpart, modelposition, alive);
	}
	return retval;
}


void MovePartToScene (ipartdlist *parts)
{
	int						i;
	RLVector				ModelVector, WorldVector;
    D3DEXECUTEBUFFERDESC	desc;

	parts->eb->lpVtbl->Lock (parts->eb, &desc);
	parts->Vertex = (D3DVERTEX*) desc.lpData;

	for (i = 0; i < (int)parts->vcount; i++) 
	{
		ModelVector.x = parts->Vertex[i].x;
		ModelVector.y = parts->Vertex[i].y;
		ModelVector.z = parts->Vertex[i].z;

		RLFrameTransform (parts->frame, &ModelVector, &WorldVector);
		RLFrameInverseTransform (monstframe, &WorldVector, &ModelVector);
		parts->Vertex[i].x = ModelVector.x;
		parts->Vertex[i].y = ModelVector.y;
		parts->Vertex[i].z = ModelVector.z;
	}
	parts->frame = monstframe;
	parts->eb->lpVtbl->Unlock(parts->eb);
}

void RenderCharacters (int method)
{  
	RLVector charplace;
	int goodguyidx, badguyidx;
	extern RLFrame goodguyframe;

	if (goodguyframe == Robotframe) 
	{
		goodguyidx = 0;
		badguyidx  = 1;
	} 
	else 
	{
		goodguyidx = 1;
		badguyidx  = 0;
	}		
	// for each character (Robot/monster) go through linked list of display lists
	// Robot
	if (method != POV)
	{
		imcharacters[goodguyidx].bCanShow = TRUE;
	}
	else 
	{
		imcharacters[goodguyidx].bCanShow = FALSE; //  BSH add, No render...
	}
	RLFrameGetPosition (imcharacters[badguyidx].firstipartdlist->frame, Wscene, 
		&charplace);
	if ((charplace.x <= cGlobals.xmax) && (charplace.x >= cGlobals.xmin) &&
		(charplace.z <= cGlobals.zmax) && (charplace.z >= cGlobals.zmin))
	{
		imcharacters[badguyidx].bCanShow = TRUE;
	}
	else 
	{
		imcharacters[badguyidx].bCanShow = FALSE; // BSH add, No render...
	}
}




void BSHTestingRetexture ()
{
	if (++GameStates.CurrentSubmonster >= Gamma)
	{
		GameStates.CurrentSubmonster = Alpha;
	}
	ReTextureMonster(&imcharacters[1]);
}

extern char XafPath[];
//	Be defined in Idiot.c file.
RLFrame LoadModel(char* filename, RLFrame parent)
{
   char ModelFileName[MAX_PATH];
   HANDLE hBin = NULL;
   RLFrame ExtraDummy = NULL;

   strcpy (ModelFileName, XafPath);
   strcat (ModelFileName, "\\");
   strcat (ModelFileName, filename);

   if (!(hBin = CreateBinary (ModelFileName)))
//   if (!(hBin = CreateBinary (filename)))
   {
	   BYDumpInfo("Couldn't create binary model");
   }
//   ExtraDummy = RLCreateFrame(parent);
//   RLFrameAddScale (ExtraDummy,RLCombineReplace,RLVal(1),RLVal(1),RLVal(1));
//   RLFrameSetPosition (ExtraDummy, parent, RLVal(0), RLVal(0), RLVal(0));
//   RLFrameSetOrientation (ExtraDummy, parent, RLVal(0), RLVal(0), RLVal(1), 
//	   RLVal(0), RLVal(1), RLVal(0));
   ConstructDLists (parent, hBin);
   DeleteBinary (hBin);  // Be called from BinLoad file...

   return ExtraDummy;
}

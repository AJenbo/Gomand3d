/*==========================================================================
 *
 *  Copyright (C) 1996 Inventec Corporation. All Rights Reserved.
 *
 *  File: lqhtex.cpp
 *
 *  Author: Liou Qing Hua 
 *
 *  Date:   1996,6,20
 *
$Header:   H:/pvcs/pvcsproj/gomand3d.prj/SPRITE.C_V   1.17   24 Apr 1997 14:26:22   JEREMIAH  $

$Log:   H:/pvcs/pvcsproj/gomand3d.prj/SPRITE.C_V  $
 * 
 *    Rev 1.17   24 Apr 1997 14:26:22   JEREMIAH
 * Changed texture loading calls to 
 * accomodate specification of texture 
 * formats.
 * 
 *    Rev 1.16   11 Apr 1997 14:32:44   JEREMIAH
 * Fixed minor bug in render states of 
 * translucent-type blending.
 * 
 *    Rev 1.15   10 Apr 1997 11:04:22   JEREMIAH
 * Added support for SEMIFANCY transparency
 * type.
 * 
 *    Rev 1.14   Mar 20 1997 17:24:18   JEREMIAH
 * Set zwriteenable on and off in FANCY-type
 * transparency. 
 * 
 *    Rev 1.13   12 Mar 1997 12:44:54   JEREMIAH
 * Set DEST_BLENDs to BLEND_ZERO
 * for non-semi-transparent styles.
 * 
 *    Rev 1.12   12 Mar 1997 10:37:14   JEREMIAH
 * Set transparency values according to 
 * transparency style.
 * 
 *    Rev 1.11   10 Mar 1997 13:25:02   JEREMIAH
 * Created glowing alpha blending.
 * 
 *    Rev 1.10   07 Mar 1997 14:53:48   JEREMIAH
 * Reversed the checks for MODULATEALPHA
 * and MODULATE.
 * 
 *    Rev 1.9   07 Mar 1997 14:08:38   TIM
 * Added get caps for alpha channel transparencies and translucencies ( only tested on Permedia)
 * 
 *    Rev 1.8   06 Mar 1997 14:41:52   JEREMIAH
 * Migrated render calls to pure IM, called
 * by RenderAllParticles() and RenderAllCxSprites().
 * 
 * 
 *    Rev 1.7   07 Feb 1997 09:05:18   BRUCE
 * set bilinear filtering off on the sprites.
 * 
 *    Rev 1.6   04 Feb 1997 16:34:40   JEREMIAH
 * Skipped past revision 1.5.
 * Beta 1.02A seems to cause a fatal crash
 * that occurs at QueryInterface when loading
 * the generic building texture.   Reason 
 * unknown.
 * 
 * 
 *    Rev 1.4   27 Jan 1997 10:40:52   JEREMIAH
 * Added extra level of indirection to particle
 * system textures to allow sharing textures.
 * 
 *    Rev 1.3   16 Jan 1997 09:46:36   TIM
 * Changed render state in 640 *480 to a simple Blend enable
 * 
 *    Rev 1.2   06 Jan 1997 16:27:50   JEREMIAH
 * Reduced rampsize on all materials to 1
 * to eliminate palettizing pause bug.
 * 
 *    Rev 1.1   15 Nov 1996 14:55:46   JEREMIAH
 * Changed by Liou GuoHong (ITC).
 * Implemented copy mode for 8-bit rendering.
 ***************************************************************************/
#include "rl2d3d.h"
#include "global.h"

#include <math.h>
#include <stdlib.h>
#ifdef MINIWIN
#include "miniwin/d3d.h"
#else
#include <d3d.h>
#endif
#include "d3dmacs.h"
#include "rmdemo.h"
#include "mdtex.h"

#ifdef MINIWIN
#include "miniwin/d3drm.h"
#include "miniwin/windows.h"
#else
#include <d3drmwin.h>
#include <windows.h>
#endif
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <direct.h>
#include "spritlib.h"
#include "d3dappi.h"
#include "tekmath.h"

extern LPDIRECT3DRMFRAME behindthescene;
extern LPDIRECT3DRMFRAME Wscene;
extern LPDIRECT3DRMDEVICE Wdevice;
extern LPDIRECT3DRMVIEWPORT Wview;
extern int Vmode;

#define MAX_NO_PSYSTEMS 50	   // particle systems (collection of 2d sprites)
								//Spudde define 70
#define MAX_NO_CXSPRITES 20   // complex sprites (2 perpendicular 2d structures in 3d world)
								//Spudde define 250,include trees and poles

Psystem* allpsystems[MAX_NO_PSYSTEMS];	   // pointers to the above
CxSprite* allcxsprites[MAX_NO_CXSPRITES];

unsigned char psystemcount;		// count of the above
unsigned char cxspritecount;

int initted =0;

#define RAND (rand())
#define IM

static D3DRMMATRIX4D TheRMMatrix;
static D3DMATRIX TheMatrix =
{
    D3DVAL(1.0), D3DVAL(0.0), D3DVAL(0.0), D3DVAL(0.0),
    D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0), D3DVAL(50.0),
    D3DVAL(0.0), D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0),
    D3DVAL(0.0), D3DVAL(51.0), D3DVAL(0.0), D3DVAL(1.0)
};
static D3DMATRIXHANDLE hTheMatrix;
static int TheMatrixOffset4,TheMatrixOffset8;


void ChangeTextureCoordinates(D3DVERTEX v[], Plane* plane)
{
	if (plane->num_triangles == 4)
	{
		v[0].tu = plane->x1;
		v[0].tv = plane->y1;
		v[1].tu = plane->x2;
		v[1].tv = plane->y1;
		v[2].tu = plane->x2;
		v[2].tv = plane->y2;
		v[3].tu = plane->x1;
		v[3].tv = plane->y2;
	}
	else if (plane->num_triangles == 8)
	{
		;
	}
}

void CreateRectangle(D3DVERTEX v[], Plane* plane)
{
	v[0].x  = plane->points[0].x;
	v[0].y  = plane->points[0].y;
	v[0].z  = plane->points[0].z;
    v[0].nx = D3DVAL(0);
    v[0].ny = D3DVAL(0);
    v[0].nz = D3DVAL(-1);
    v[0].tu = plane->x1;
    v[0].tv = plane->y1;
    
	v[1].x  = plane->points[1].x;
	v[1].y  = plane->points[1].y;
	v[1].z  = plane->points[1].z;
    v[1].nx = D3DVAL(0);
    v[1].ny = D3DVAL(0);
    v[1].nz = D3DVAL(-1);
    v[1].tu = plane->x2;
    v[1].tv = plane->y1;
    
	v[2].x  = plane->points[2].x;
	v[2].y  = plane->points[2].y;
	v[2].z  = plane->points[2].z;
    v[2].nx = D3DVAL(0);
    v[2].ny = D3DVAL(0);
    v[2].nz = D3DVAL(-1);
    v[2].tu = plane->x2;
    v[2].tv = plane->y2;
    
	v[3].x  = plane->points[3].x;
	v[3].y  = plane->points[3].y;
	v[3].z  = plane->points[3].z;
    v[3].nx = D3DVAL(0);
    v[3].ny = D3DVAL(0);
    v[3].nz = D3DVAL(-1);
    v[3].tu = plane->x1;
    v[3].tv = plane->y2;
}


void CreateTwoRectangle(D3DVERTEX v[], Plane* plane)
{
	v[0].x  = D3DVAL(0);
	v[0].y  = D3DVAL(0.5);
	v[0].z  = D3DVAL(0);
    v[0].nx = D3DVAL(0);
    v[0].ny = D3DVAL(0);
    v[0].nz = D3DVAL(-1);
    v[0].tu = D3DVAL(1.0);
    v[0].tv = D3DVAL(0);
    
	v[1].x  = D3DVAL(0);
	v[1].y  = D3DVAL(-0.5);
	v[1].z  = D3DVAL(0);
    v[1].nx = D3DVAL(0);
    v[1].ny = D3DVAL(0);
    v[1].nz = D3DVAL(-1);
    v[1].tu = D3DVAL(1.0);
    v[1].tv = D3DVAL(0.5);
    
	v[2].x  = D3DVAL(0);
	v[2].y  = D3DVAL(-0.5);
	v[2].z  = D3DVAL(7);
    v[2].nx = D3DVAL(0);
    v[2].ny = D3DVAL(0);
    v[2].nz = D3DVAL(-1);
    v[2].tu = D3DVAL(0);
    v[2].tv = D3DVAL(0.5);
    
	v[3].x  = D3DVAL(0);
	v[3].y  = D3DVAL(0.5);
	v[3].z  = D3DVAL(7);
    v[3].nx = D3DVAL(0);
    v[3].ny = D3DVAL(0);
    v[3].nz = D3DVAL(-1);
    v[3].tu = D3DVAL(0);
    v[3].tv = D3DVAL(0);

	v[4].x  = D3DVAL(0.5);
	v[4].y  = D3DVAL(0);
	v[4].z  = D3DVAL(0);
    v[4].nx = D3DVAL(0);
    v[4].ny = D3DVAL(1);
    v[4].nz = D3DVAL(-1);
    v[4].tu = D3DVAL(1);
    v[4].tv = D3DVAL(0.5);
    
	v[5].x  = D3DVAL(-0.5);
	v[5].y  = D3DVAL(0);
	v[5].z  = D3DVAL(0);
    v[5].nx = D3DVAL(0);
    v[5].ny = D3DVAL(1);
    v[5].nz = D3DVAL(-1);
    v[5].tu = D3DVAL(1.0);
    v[5].tv = D3DVAL(1.0);
    
	v[6].x  = D3DVAL(-0.5);
	v[6].y  = D3DVAL(0);
	v[6].z  = D3DVAL(7);
    v[6].nx = D3DVAL(0);
    v[6].ny = D3DVAL(1);
    v[6].nz = D3DVAL(-1);
    v[6].tu = D3DVAL(0);
    v[6].tv = D3DVAL(1.0);
    
	v[7].x  = D3DVAL(0.5);
	v[7].y  = D3DVAL(0);
	v[7].z  = D3DVAL(7.0);
    v[7].nx = D3DVAL(0);
    v[7].ny = D3DVAL(1);
    v[7].nz = D3DVAL(-1);
    v[7].tu = D3DVAL(0);
    v[7].tv = D3DVAL(0.5);
}


void CleanupPlaneObject(LPDIRECT3DRMOBJECT dev, void* arg)
{
    Plane* plane = (Plane*) arg;
	
    if (plane && plane->eb) 
	{
        plane->eb->lpVtbl->Release(plane->eb);
        plane->mat->lpVtbl->Release(plane->mat);
        plane->eb = NULL;
        plane->mat = NULL;
		plane->dev = NULL;
	}
}

void FreePlaneObject(Plane* plane)
{
    if (plane->eb)
	{
		plane->eb->lpVtbl->Release(plane->eb);
	}
    if (plane->mat) 
	{
		plane->mat->lpVtbl->Release(plane->mat);
	}
	if(plane->dev) 
	{
		plane->dev->lpVtbl->Release(plane->dev);
	}
    plane->eb = NULL;
    plane->mat = NULL;
	plane->dev = NULL;
	
	free(plane);
	plane = NULL;
}

/*
typedef struct _PlaneExecuteBuffer {
    D3DVERTEX           v[NUM_VERTICES];
    D3DINSTRUCTION      op_state_light1;
    D3DSTATE            state1;
    D3DINSTRUCTION      op_set_status;
    D3DSTATUS           setstatus1;
    D3DINSTRUCTION      op_process_vertices1;
    D3DPROCESSVERTICES  processvertices1;
    D3DINSTRUCTION      op_state_render;
    D3DSTATE            state2;
	D3DSTATE            state3;
    D3DINSTRUCTION      op_triangle_list;
    D3DTRIANGLE         tri[NUM_TRIANGLES];
    D3DINSTRUCTION      exit1;
} PlaneExecuteBuffer;
*/
extern int VM_W3D;
extern int VM_H3D;
extern int VM_BPP3D;

BOOL CreatePlaneObjects(Plane* plane, LPDIRECT3DRMDEVICE dev)
{
    D3DEXECUTEBUFFERDESC desc;
    D3DEXECUTEDATA data;
    LPDIRECT3D lpD3D = NULL;
    LPDIRECT3DDEVICE lpD3DDev = NULL;
    LPDIRECT3DMATERIAL mat = NULL;
    LPDIRECT3DEXECUTEBUFFER eb = NULL;
    D3DMATERIALHANDLE hMat;
    D3DMATERIAL mymat;
    void* p;
	D3DTRIANGLE* t;
    LPVOID lpBufStart, lpInsStart;
	int size;
	D3DVERTEX *v;

    RELEASE(plane->eb);

    dev->lpVtbl->GetDirect3DDevice(dev, &lpD3DDev);
    if (!lpD3DDev)
    {
		goto generic_error;
	}
   
   MAKE_MATRIX(lpD3DDev, hTheMatrix, TheMatrix);


	if (FAILED(lpD3DDev->lpVtbl->GetDirect3D(lpD3DDev, &lpD3D)))
	{
		goto generic_error;
	}

    size  = sizeof(D3DVERTEX) * plane->num_vertices; 
    size += sizeof(D3DINSTRUCTION) * 9;
    size += sizeof(D3DINSTRUCTION) * 1;   // for matrix multiply
    size += sizeof(D3DSTATE) * 22;
    size += sizeof(D3DSTATE) * 1;         // for matrix multiply
    size += sizeof(D3DSTATUS) * 1;
    size += sizeof(D3DPROCESSVERTICES) * 1;
    size += sizeof(D3DTRIANGLE) * plane->num_triangles;

    desc.dwSize = sizeof(desc);
    desc.dwFlags = D3DDEB_BUFSIZE | D3DDEB_CAPS;
    desc.dwBufferSize = size;
	desc.dwCaps = D3DDEBCAPS_SYSTEMMEMORY;
    if (FAILED(lpD3DDev->lpVtbl->CreateExecuteBuffer(lpD3DDev, &desc, &eb, NULL)))
    {
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

      memset(&mymat, 0, sizeof(mymat));
      mymat.dwSize = sizeof(mymat);
      if (d3dapprs.transparency==FANCY || d3dapprs.transparency==SEMIFANCY)
      {
         if (plane->transptype == BRIGHTTYPETRANSP)
         {
            mymat.ambient.r = mymat.diffuse.r = D3DVAL(1.0);
            mymat.ambient.g = mymat.diffuse.g = D3DVAL(1.0);
            mymat.ambient.b = mymat.diffuse.b = D3DVAL(1.0);
            mymat.ambient.a = mymat.diffuse.a = D3DVAL(0.5);
         }
         else
         {
            mymat.ambient.r = mymat.diffuse.r = D3DVAL(1.0);
            mymat.ambient.g = mymat.diffuse.g = D3DVAL(1.0);
            mymat.ambient.b = mymat.diffuse.b = D3DVAL(1.0);
            mymat.ambient.a = mymat.diffuse.a = D3DVAL(0.5);
         }
      } 
      else if (d3dapprs.transparency == TRANSLUCENT) 
      {
         if (plane->transptype == BRIGHTTYPETRANSP)
         {
            mymat.ambient.r = mymat.diffuse.r = D3DVAL(1.0);
            mymat.ambient.g = mymat.diffuse.g = D3DVAL(1.0);
            mymat.ambient.b = mymat.diffuse.b = D3DVAL(1.0);
            mymat.ambient.a = mymat.diffuse.a = D3DVAL(0.4);
         }
         else
         {
            mymat.ambient.r = mymat.diffuse.r = D3DVAL(0.8);
            mymat.ambient.g = mymat.diffuse.g = D3DVAL(0.8);
            mymat.ambient.b = mymat.diffuse.b = D3DVAL(0.8);
            mymat.ambient.a = mymat.diffuse.a = D3DVAL(0.5);
         }
      }
      else
      {
         mymat.ambient.r = D3DVAL(1.0);
         mymat.ambient.g = D3DVAL(1.0);
         mymat.ambient.b = D3DVAL(1.0);
         mymat.ambient.a = D3DVAL(1.0);
      }
      mymat.dwRampSize = 1;
      mymat.hTexture = plane->hTex;

    if (FAILED(mat->lpVtbl->SetMaterial(mat, &mymat)))
    {
		goto generic_error;
	}

    if (FAILED(eb->lpVtbl->Lock(eb, &desc)))
	{
		goto generic_error;
	}

    lpBufStart = desc.lpData;
    memset(lpBufStart, 0, size);

	v = (D3DVERTEX*) desc.lpData;
	
	if (plane->num_triangles == 4)
	{
		CreateRectangle(&v[0], plane);
	}
	else if (plane->num_triangles == 8)
	{
		CreateTwoRectangle(&v[0], plane);
	}

    p = (void*) ((char*) desc.lpData + plane->num_vertices * sizeof(D3DVERTEX));

    lpInsStart = p;

    OP_STATE_LIGHT(1, p);
        STATE_DATA(D3DLIGHTSTATE_MATERIAL, hMat, p);
        
    OP_SET_STATUS(D3DSETSTATUS_ALL, D3DSTATUS_DEFAULT, 2048, 2048, 0, 0, p);
	
	if (plane->num_triangles == 4)
		TheMatrixOffset4=((unsigned long) p)-((unsigned long)lpBufStart);
	else if (plane->num_triangles == 8)
	
	TheMatrixOffset8=((unsigned long) p)-((unsigned long)lpBufStart);
    OP_STATE_TRANSFORM(1, p);
        STATE_DATA(D3DTRANSFORMSTATE_WORLD, hTheMatrix, p);
    
    OP_PROCESS_VERTICES(1, p);
	if (VM_BPP3D == 8)
   {
        PROCESSVERTICES_DATA(D3DPROCESSVERTICES_TRANSFORM,
                         0, plane->num_vertices, p);
   }
   else
   {
        PROCESSVERTICES_DATA(D3DPROCESSVERTICES_TRANSFORMLIGHT,
                         0, plane->num_vertices, p);
   }

    OP_STATE_RENDER(1, p);
        STATE_DATA(D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT, p);

	OP_STATE_RENDER(5, p);//liou qinghua 9/17,96
		STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE, mymat.hTexture, p);
        STATE_DATA(D3DRENDERSTATE_WRAPV, FALSE, p);
        STATE_DATA(D3DRENDERSTATE_WRAPU, FALSE, p);
        STATE_DATA(D3DRENDERSTATE_TEXTUREMAG, d3dapprs.TextureFilter, p);
//        STATE_DATA(D3DRENDERSTATE_TEXTUREMIN, d3dapprs.TextureFilter, p);
		STATE_DATA(D3DRENDERSTATE_TEXTUREPERSPECTIVE, d3dapprs.bPerspCorrect, p);	//Bruce

	// check if alpha blending is enabled, if not then color keying
		
    if  (d3dapprs.transparency == COLORKEY) 
	{
		OP_STATE_RENDER(3, p);
			STATE_DATA(D3DRENDERSTATE_BLENDENABLE, TRUE, p);
			STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_COPY, p);
			STATE_DATA(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA, p);	
	}
	else
   {
	   // make sure selected alpha blend capability is supported in hardware 

	   OP_STATE_RENDER(1, p);
		   STATE_DATA(D3DRENDERSTATE_BLENDENABLE, TRUE, p);

	   // for simplest alpha translucency

	   if  (d3dapprs.transparency == FANCY)
	   {
         if (plane->transptype == BRIGHTTYPETRANSP)
         {
			         OP_STATE_RENDER(3, p);
				         STATE_DATA(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE,p);
				         STATE_DATA(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA,p);
				         STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATEALPHA, p);
         }
         else
         {
			         OP_STATE_RENDER(3, p);
				         STATE_DATA(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA,p);
				         STATE_DATA(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA,p);
				         STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATEALPHA, p);
         }
		   OP_STATE_RENDER(2, p);
			   STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE, FALSE, p);
			   STATE_DATA(D3DRENDERSTATE_ZENABLE, TRUE, p);
	   }
	   else 
	   if  (d3dapprs.transparency == SEMIFANCY)
	   {
			OP_STATE_RENDER(3, p);
            STATE_DATA(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA,p);
				STATE_DATA(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA,p);
				STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATEALPHA, p);
		   OP_STATE_RENDER(2, p);
			   STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE, FALSE, p);
			   STATE_DATA(D3DRENDERSTATE_ZENABLE, TRUE, p);
	   }
	   else 
	   if  (d3dapprs.transparency == TRANSLUCENT)
	   {
         if (plane->transptype == BRIGHTTYPETRANSP)
         {
			      OP_STATE_RENDER(3, p);
   //				         STATE_DATA(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE,p);
   //				         STATE_DATA(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA,p);
				   STATE_DATA(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE,p);
				   STATE_DATA(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA,p);
				   STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATE, p);
         }
         else
         {
			   OP_STATE_RENDER(3, p);
				   STATE_DATA(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA,p);
				   STATE_DATA(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA,p);
				   STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATE, p);
         }
	   }
	   else 
	   // for simplest alpha transparency
	   if  (d3dapprs.transparency == NORMTRANSPARENT)
	   {

		   OP_STATE_RENDER(3, p);
			   STATE_DATA(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO,p);
			   STATE_DATA(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE,p);
			   // note: this is not correct but the only way to work on all cards
			   STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATEALPHA, p);
	   }
	   else 
	   // for alternative simplest alpha transparency
	   if  (d3dapprs.transparency == ALTTRANSPARENT)
	   {

		   OP_STATE_RENDER(3, p);
			   STATE_DATA(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO,p);
			   STATE_DATA(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE,p);
			   STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATE, p);
	   }
   }
    /*
     * Make sure that the triangle data (not OP) will be QWORD aligned
     */
    if (QWORD_ALIGNED(p)) 
	{
        OP_NOP(p);
    }

	OP_TRIANGLE_LIST(plane->num_triangles, p);
        
    t = (D3DTRIANGLE*) p;
        
	if(plane->num_triangles == 4)
	{
        t->v1 = 0;
        t->v2 = 1;
        t->v3 = 3;
        t->wFlags = D3DTRIFLAG_EDGEENABLETRIANGLE;
        t++;

        t->v1 = 1;
        t->v2 = 2;
        t->v3 = 3;
        t->wFlags = D3DTRIFLAG_EDGEENABLETRIANGLE;
        t++;

        t->v1 = 1;
        t->v2 = 3;
        t->v3 = 2;
        t->wFlags = D3DTRIFLAG_EDGEENABLETRIANGLE;
        t++;

        t->v1 = 0;
        t->v2 = 3;
        t->v3 = 1;
        t->wFlags = D3DTRIFLAG_EDGEENABLETRIANGLE;
        t++;
	}	
	
	if(plane->num_triangles == 8)
	{
		t->v1 = 0;
		t->v2 = 1;
		t->v3 = 2;
		t->wFlags = D3DTRIFLAG_EDGEENABLETRIANGLE;
		t++;

		t->v1 = 0;
		t->v2 = 2;
		t->v3 = 3;
		t->wFlags = D3DTRIFLAG_EDGEENABLETRIANGLE;
		t++;

		t->v1 = 0;
		t->v2 = 3;
		t->v3 = 2;
		t->wFlags = D3DTRIFLAG_EDGEENABLETRIANGLE;
		t++;

		t->v1 = 0;
		t->v2 = 2;
		t->v3 = 1;
		t->wFlags = D3DTRIFLAG_EDGEENABLETRIANGLE;
		t++;

		t->v1 = 4;
		t->v2 = 5;
		t->v3 = 6;
		t->wFlags = D3DTRIFLAG_EDGEENABLETRIANGLE;
		t++;

		t->v1 = 4;
		t->v2 = 6;
		t->v3 = 7;
		t->wFlags = D3DTRIFLAG_EDGEENABLETRIANGLE;
		t++;

		t->v1 = 4;
		t->v2 = 7;
		t->v3 = 6;
		t->wFlags = D3DTRIFLAG_EDGEENABLETRIANGLE;
		t++;

		t->v1 = 4;
		t->v2 = 6;
		t->v3 = 5;
		t->wFlags = D3DTRIFLAG_EDGEENABLETRIANGLE;
		t++;
	}
    p = (char*) t;

    OP_EXIT(p);

    if (FAILED(eb->lpVtbl->Unlock(eb)))
	{
        goto generic_error;
	}

    data.dwSize = sizeof(data);
    data.dwVertexOffset = 0;
    data.dwVertexCount = plane->num_vertices;
    data.dwInstructionOffset = plane->num_vertices * sizeof(D3DVERTEX);
    data.dwInstructionLength = (ULONG) ((char *)p - (char *)lpInsStart);

    if (FAILED(eb->lpVtbl->SetExecuteData(eb, &data)))
	{
		goto generic_error;
	}

    plane->eb = eb;
    plane->mat = mat;
    plane->dev = dev;
	
    if (FAILED(dev->lpVtbl->AddDestroyCallback(dev, CleanupPlaneObject, plane)))
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

BOOL RenderPlane(Plane* plane, LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view, LPDIRECT3DRMFRAME theframe)
{
    D3DVERTEX* v;
    D3DEXECUTEBUFFERDESC desc;
    D3DEXECUTEDATA data;
    LPDIRECT3DDEVICE lpD3DDev = NULL;
    LPDIRECT3DVIEWPORT lpD3DView = NULL;
    void *ThisBetterWork;
	HRESULT rval;

	if(plane->active == FALSE)
	{
		return TRUE;
	}

    dev->lpVtbl->GetDirect3DDevice(dev, &lpD3DDev);
    view->lpVtbl->GetDirect3DViewport(view, &lpD3DView);
    if (!lpD3DDev || !lpD3DView)
	{
		goto ret_with_error;
	}

    desc.dwSize = sizeof(desc);
    desc.dwFlags = 0;
    
    if (FAILED(plane->eb->lpVtbl->Lock(plane->eb, &desc)))
        goto ret_with_error;
    v = (D3DVERTEX*) desc.lpData;
	
	ChangeTextureCoordinates(&v[0], plane);

   RecursivelyGetManyTransforms(theframe,TheRMMatrix);

   memcpy(&TheMatrix, TheRMMatrix, sizeof(D3DMATRIX));
                                
   lpD3DDev->lpVtbl->SetMatrix(lpD3DDev, hTheMatrix, &TheMatrix);

   if (plane->num_triangles == 4)
      ThisBetterWork=(void *)(((unsigned long)desc.lpData) + ((unsigned long)TheMatrixOffset4));
   else if (plane->num_triangles == 8)
      ThisBetterWork=(void *)(((unsigned long)desc.lpData) + ((unsigned long)TheMatrixOffset8));

   OP_STATE_TRANSFORM(1, ThisBetterWork);
   STATE_DATA(D3DTRANSFORMSTATE_WORLD, hTheMatrix, ThisBetterWork);

   
	if (FAILED(plane->eb->lpVtbl->Unlock(plane->eb)))
        goto ret_with_error;

   	if (FAILED(lpD3DDev->lpVtbl->Execute(lpD3DDev, plane->eb, lpD3DView, 
		D3DEXECUTE_CLIPPED)))	//New version
	{
		goto ret_with_error;
	}

      data.dwSize = sizeof data;
    if (FAILED(plane->eb->lpVtbl->GetExecuteData(plane->eb, &data)))
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
    return TRUE;
ret_with_error:
    RELEASE(lpD3DDev);
    RELEASE(lpD3DView);
    return FALSE;
}



int PlaneCallback(LPDIRECT3DRMUSERVISUAL uvis,
                 void* arg,
                 D3DRMUSERVISUALREASON reason,
                 LPDIRECT3DRMDEVICE dev,
                 LPDIRECT3DRMVIEWPORT view)
{				 
    Plane* plane = (Plane*) arg;

    if (plane->dev != dev) 
	{
		if (!CreatePlaneObjects(plane, dev))
		{
            return FALSE;
		}
    }

    if (reason == D3DRMUSERVISUAL_CANSEE)
	{
		return TRUE;
	}

    if (reason == D3DRMUSERVISUAL_RENDER) {
       //char OutputString[64];
       //sprintf(OutputString,"in uv, plane is %d\n",plane);
       //OutputDebugString(OutputString);
       /*
		if (!RenderPlane(plane, dev, view))
        {
			return DDERR_GENERIC;
		}
        else
		{
			return D3D_OK;
		}
      */
			return D3D_OK;
   }

    return 0;
}

void DestroyPlane(LPDIRECT3DRMOBJECT obj, void* arg)
{
    Plane* plane = (Plane*) arg;

    if (plane->dev)
	{
        plane->dev->lpVtbl->DeleteDestroyCallback(plane->dev, CleanupPlaneObject, arg);
	}
    CleanupPlaneObject((LPDIRECT3DRMOBJECT)plane->dev, (void*) plane);
	free(plane);
	plane = NULL;
}


int MallocPlane(Plane** plane)
{
    *plane = (Plane*)malloc(sizeof(Plane));
    if (!*plane)
	{
        goto ret_with_error;
    }
	memset(*plane, 0, sizeof(Plane));
	
	return TRUE;

ret_with_error:
    if (*plane)
	{
        free(*plane);
	}
	Msg("A failure occurred while malloc plane.\n");
	return FALSE;
}


LPDIRECT3DRMUSERVISUAL LQHCreateVisual(Plane *plane)
{
    LPDIRECT3DRMUSERVISUAL uvis = NULL;
	extern LPDIRECT3DRMDEVICE Wdevice;

	if(!plane->hTex)
	{
        goto ret_with_error;
	}
	if (!CreatePlaneObjects(plane, Wdevice))
	{
		goto ret_with_error;
	}

	if (FAILED(lpD3DRM->lpVtbl->CreateUserVisual(lpD3DRM, PlaneCallback, (void*) plane, &uvis)))
	{
		goto ret_with_error;
	}
	
	if (FAILED(uvis->lpVtbl->AddDestroyCallback(uvis, DestroyPlane, (void*) plane)))
	{
		goto ret_with_error;   
	}
	
    return uvis;

ret_with_error:
    RELEASE(uvis);
    return NULL;
}


LPTEXTURESTRUCT LQHCreateTexture(LPDIRECT3DRMDEVICE dev, LPSTR ppmfile, int transbits)
{
	LPTEXTURESTRUCT lpTexStruct;
	lpTexStruct = (TEXTURESTRUCT*)malloc(sizeof(TEXTURESTRUCT));
	memset (lpTexStruct, 0, sizeof(TEXTURESTRUCT));
	MyLoadTexture(dev, ppmfile, lpTexStruct, transbits);
	return lpTexStruct;
}


LPDIRECT3DRMFRAME LQHCreateTextureFrame(LPDIRECT3DRMFRAME parent, Plane* plane)
{
	LPDIRECT3DRMUSERVISUAL uvis = NULL;
	LPDIRECT3DRMFRAME frame = NULL;

	uvis = LQHCreateVisual(plane);
    if (!uvis)
        goto generic_error;

    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, parent, &frame)))
        goto generic_error;
	
	if (FAILED(frame->lpVtbl->AddVisual(frame, (LPDIRECT3DRMVISUAL)uvis)))
        goto generic_error;
	
    RELEASE(uvis);
	return frame;

generic_error:
    Msg("A failure occurred while creating the scene.\n");
	RELEASE(uvis);
	RELEASE(frame);
    return NULL;
}


void InitSprites()
{
	int i;
   
    // if already initialised then return
	if (initted) return;

	// set pointers to particle systems and complex sprites
  // initialize to NULL so only non-NULL values represent successfully
  // created structures.
	for (i = 0; i < MAX_NO_PSYSTEMS; i++) 
	{
		allpsystems[i] = NULL;
	}
	for (i = 0; i < MAX_NO_CXSPRITES; i++) 
	{
		allcxsprites[i] = NULL;
	}
	cxspritecount = 0;

	//set initted sprites to true
	initted = 1;
}


Sprite *CreateDisplayList(LPDIRECT3DRMFRAME parent, LPTEXTURESTRUCT lpTexStruct, Svis *visual)
{	
    Sprite *thesprite;

    // create space for the sprite structure
    thesprite = (Sprite*)malloc(sizeof(Sprite));
	
	MallocPlane(&(thesprite->plane));
	//thesprite->plane = MallocPlane();
	// set up the sprite variables

	thesprite->plane->hTex = lpTexStruct->hTex;
	thesprite->plane->x1 = visual->x1;
	thesprite->plane->x2 = visual->x2;
	thesprite->plane->y1 = visual->y1;
	thesprite->plane->y2 = visual->y2;
	thesprite->plane->num_vertices = 4;
	thesprite->plane->num_triangles = 4;

	// set up the vertices of the foursided sprite
	// setup sizes according to visual structure members
    thesprite->plane->points[0].x = D3DVAL(visual->sx/2.0);
    thesprite->plane->points[0].y = D3DVAL(visual->sy/2.0);
    thesprite->plane->points[0].z = D3DVAL(0.0);
    thesprite->plane->points[1].x = D3DVAL(-visual->sx/2.0);
    thesprite->plane->points[1].y = D3DVAL(visual->sy/2.0);
    thesprite->plane->points[1].z = D3DVAL(0.0);
    thesprite->plane->points[2].x = D3DVAL(-visual->sx/2.0);
    thesprite->plane->points[2].y = D3DVAL(-visual->sy/2.0);
    thesprite->plane->points[2].z = D3DVAL(0.0);
    thesprite->plane->points[3].x = D3DVAL(visual->sx/2.0);
    thesprite->plane->points[3].y = D3DVAL(-visual->sy/2.0);
    thesprite->plane->points[3].z = D3DVAL(0.0);

	/**************************
	the next variable must be 0! 1 is only test!
	****************************/
	thesprite->plane->active = 0;
	//***************************

   thesprite->plane->transptype = visual->transptype;

	thesprite->frame = LQHCreateTextureFrame(parent, thesprite->plane);

	thesprite->ttl = D3DVAL(-1.0);               // set time to live

    return thesprite;
}


// **************************************************************************
// Name:          CreateCxDisplayList
//
// Author:        Jeremiah "Spudde" Childs
// 
// Date:          1996.6.12
//
// Description:   Creates an immediate mode display list containing eight
//                  triangles that form a complex sprite, and puts the display 
//                  list into a CxSprite structure.
//
// Arguments:     RLFrame parent: (IN) RLFrame object that will contain the
//                  complex sprite.
//                RLTexture tex:  (IN) RLTexture to be applied to the complex
//                  sprite.
//                RLIMSurfaceInfo* surf:  (IN) pointer to RLIMSurfaceInfo
//                  structure.
//
// Return:        CxSprite*:  Pointer to structure that describes a complex 
//                  sprite object.
//
// Side Effects:	Allocates memory to create a CxSprite structure.  Creates
//                  an RLFrame object.  Allocates memory for display list.
//
// Notes:			    
//
// Known Restrictions:
//
// Error Number:
//
// Update:
// Date				Name			Description
// =========================================================================
//
// **************************************************************************

void CreateCxDisplayList(CxSprite *thesprite, 
				LPDIRECT3DRMFRAME parent, D3DTEXTUREHANDLE htex)
{
	int i;

	// When a complex sprite is created, a pointer to that object 
	// is added to a list of all complex sprites, so they may be 
	// destroyed all at once at the end of a level, rather than 
	// individually destroyed by the module that created it.

    for (i = 0; i < MAX_NO_CXSPRITES; i++) 
	{
		if (allcxsprites[i] == NULL) 
		{
			break;
		}
	}
    
	// if above loop has gone through entire list without finding an
  // unused element in the list, maximum number of complex sprites
  // has been reached, so return without creating
	if (i == MAX_NO_CXSPRITES) 
	{
		Msg("A failure occurred MAX_NO_CXSPRITES.\n");
	}
    
	thesprite->index = i;
    allcxsprites[thesprite->index] = thesprite;

	MallocPlane(&(thesprite->plane));
	//thesprite->plane = MallocPlane();

	// set up the sprite variables

	thesprite->plane->hTex = htex;
	
	thesprite->plane->num_vertices = 8;
	thesprite->plane->num_triangles = 8;

   thesprite->plane->transptype = BRIGHTTYPETRANSP;

	/**************************
	the next variable must be 0! 1 is only test!
	****************************/
	thesprite->plane->active = 0;
	//***************************

	thesprite->frame = LQHCreateTextureFrame(parent, thesprite->plane);

	// set up the sprite attributes

	thesprite->ttl = D3DVAL(-1.0);
	
	thesprite->active = 0;
		
//	return;
}



Sprite *CreateSprite(LPDIRECT3DRMFRAME parent, LPTEXTURESTRUCT lpTexStruct, Svis *visual)
{
    Sprite *thesprite;

//    if (!initted) InitSprites();

    thesprite = CreateDisplayList(parent, lpTexStruct, visual);

    return thesprite;
}


// **************************************************************************
// Name:          DestroySprite
//
// Author:        Jeremiah "Spudde" Childs
// 
// Date:          1996.6.12
//
// Description:		Destroy a sprite object.  Free all memory that was 
//                  allocated for it and destroy all RLObjects associated
//                  with it.
//
// Arguments:     Sprite *condemned:  (IN) pointer to sprite structure
//                  that is to be destroyed.
//
// Return:        None.
//
// Side Effects:  Frees memory and destroys RLObjects.
//
// Notes:			    
//
// Known Restrictions:
//
// Error Number:
//
// Update:
// Date				Name			Description
// =========================================================================
//
// **************************************************************************

void DestroySprite(Sprite *condemned)
{
//	LPDIRECT3DRMFRAME parent;
//	long i;
//	BOOL flag = TRUE;


	//RLIMFreeTriangles(Wdevice, condemned->triangles);
	
	//callback function as general function. Liou qinghua 9/12,96
	//Destroy plane of sprite.
	//FreePlaneObject(condemned->plane); 
	// Destroy RLObject of the frame
/*
	while (i = RLObjectGetReferenceCount((LPDIRECT3DRMOBJECT)(condemned->frame))) 
	{
		RLFrameRemoveChild(RLFrameGetParent(condemned->frame),
			condemned->frame);
	}
*/
	MDFreeD3DFrame(condemned->frame);
	/*
	while(flag)
	{
		refcount = (condemned->frame)->lpVtbl->Release(condemned->frame);
		if (refcount<=0)
			flag = FALSE;
	}
	condemned->frame->lpVtbl->GetParent(condemned->frame, &parent);
//	if (!parent) break;
	condemned->frame->lpVtbl->DeleteChild(parent, condemned->frame);
	RELEASE(parent);
	*/

	condemned->plane = NULL;

    free(condemned);
	condemned = NULL;
}

// **************************************************************************
// Name:          ActivateParticleSystem
//
// Author:        Jeremiah "Spudde" Childs
// 
// Date:          1996.6.12
//
// Description:   Function to turn a particular particle system on.
//
// Arguments:     Psystem *go:  (IN/OUT) pointer to particle system structure
//                  for the particle to be activated.
//                int ttl:  (IN) time to live.  If positive, the particle
//                  system will deactivate itself after that number of 
//                  frames.  If negative, the particle system will continue
//                  to be active until deactivated.
//
// Return:        None.
//
// Side Effects:  Affects the velocity of the RLFrames of the sprites.
//
// Notes:			    
//
// Known Restrictions:
//
// Error Number:
//
// Update:
// Date				Name			Description
// =========================================================================
//
// **************************************************************************
void ActivateParticleSystem(Psystem *go, int ttl)
{
    int i;
    LPDIRECT3DRMFRAME scene;

	// is already system active, set time to live of particle system
    if (go->active == 1) 
	{
		go->ttl = ttl;
		/*Liou 8.01*/
		for (i = 0; i < go->properties->num; i++) 
		{
			go->particles[i]->active = 1;
			go->particles[i]->plane->active = 1;
		}/**/
		return;
    }

	// set time to live
    go->frame->lpVtbl->GetScene(go->frame, &scene);
	go->ttl = ttl;
    
	// set atributes of the particle system
	for (i = 0; i < go->properties->num; i++) 
	{
		go->particles[i]->ttl = D3DDivide(D3DVAL(i), D3DVAL(go->properties->num));
		go->particles[i]->frame->lpVtbl->SetPosition(
			go->particles[i]->frame, go->frame,
			go->properties->origin.x,
			go->properties->origin.y,
			go->properties->origin.z);
		go->particles[i]->frame->lpVtbl->SetVelocity(go->particles[i]->frame, 
			scene, D3DVAL(0), D3DVAL(0), D3DVAL(0), TRUE);
		go->particles[i]->frame->lpVtbl->LookAt(go->particles[i]->frame, 
			go->camera, scene, D3DRMCONSTRAIN_Y);
    }

	// set active
    go->active = 1;
	for (i = 0; i < go->properties->num; i++) 
	{
		go->particles[i]->active = 1;
		go->particles[i]->plane->active = 1;
	}
	RELEASE(scene);
}

// **************************************************************************
// Name:          DeactivateParticleSystem
//
// Author:        Jeremiah "Spudde" Childs
// 
// Date:          1996.6.12
//
// Description:   Turns a particle system off.
//
// Arguments:     Psystem *go:  (IN/OUT) pointer to particle system structure
//                  for the particle to be activated.
//
// Return:        None.
//
// Side Effects:  None.
//
// Notes:			    
//
// Known Restrictions:
//
// Error Number:
//
// Update:
// Date				Name			Description
// =========================================================================
//
// **************************************************************************

void DeactivateParticleSystem(Psystem *go)
{
	int i;
	if (go->active)
	{
		go->active = 0;
		for (i = 0; i < go->properties->num; i++) 
		{
			go->particles[i]->plane->active = 0;
		}
	}
}


void CreateParticleSystem(Psystem *newsystem, LPDIRECT3DRMFRAME parent, LPDIRECT3DRMFRAME camera, 
						  Pprop *property, Svis *visual)
{
    int i;
    LPDIRECT3DRMFRAME scene;
	
	if (!initted) 
	{
		InitSprites();
	}

	// alocate memory for system
	//newsystem = (Psystem*)malloc(sizeof(Psystem));

	parent->lpVtbl->GetScene(parent, &scene);

    // set attribures
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, parent, &(newsystem->frame))))
        goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, newsystem->frame, &(newsystem->dummy))))
        goto generic_error;
	
	//newsystem->lpTexStruct = visual->lpTexStruct;
    newsystem->camera = camera;
    newsystem->properties = property;
    newsystem->numonscreen = property->num;
    newsystem->numonscreen = 0;
    
	/**************************
	the next variable must be 0! 1 is only test!
	****************************/
	newsystem->active = 0; 
	/****************************/

    // get available slot
	for (i = 0; i < MAX_NO_PSYSTEMS; i++) 
	{
		if (allpsystems[i]==NULL) break;
	}

	// if no slots available
    if (i == MAX_NO_PSYSTEMS) 
	{
		Msg("A failure occurred MAX_NO_PSYSTEMS.\n");
	}
    
    newsystem->index = i;
    allpsystems[newsystem->index] = newsystem;

	(newsystem->particles) = (Sprite**)malloc((newsystem->properties->num) * sizeof(Sprite*));

	// set attributes of each sprite in the system  
	for (i = 0; i < (newsystem->properties->num); i++)  
	{
		//newsystem->particles[i] = CreateSprite(newsystem->frame, newsystem->lpTexStruct, visual);
		newsystem->particles[i] = CreateDisplayList(newsystem->frame, *(newsystem->lplpTexStruct), visual);
		
		newsystem->particles[i]->ttl = D3DDivide(D3DVAL(i), D3DVAL(newsystem->properties->num));

		newsystem->particles[i]->frame->lpVtbl->SetRotation(
			newsystem->particles[i]->frame, newsystem->camera,
			D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL((RAND%(1<<16))/65536.0 - (RAND%(1<<16))/65536.0));
		newsystem->particles[i]->frame->lpVtbl->SetPosition(
			newsystem->particles[i]->frame, newsystem->frame,
			newsystem->properties->origin.x,
			newsystem->properties->origin.y,
			newsystem->properties->origin.z);

		/**************************
		the next variable must be 0! 1 is only test!
		****************************/
		newsystem->particles[i]->active = 0;
		newsystem->particles[i]->plane->active = 0;//Liou qinghua add
	}
	RELEASE(scene);  
	return;

generic_error:
    Msg("A failure occurred while creating the frame.\n");
	RELEASE(scene);  
	free(newsystem);
    return;
}


void swarmit(LPDIRECT3DRMFRAME frame, void* arg)
{
    Psystem* bee = (Psystem*) arg;
    LPDIRECT3DRMFRAME scene;
    D3DVECTOR deltav;
    D3DVECTOR bee_pos, bee_vel, wasp_pos;
    D3DVECTOR dist, alongpath;
    D3DVALUE distance;
    int i, j;

	frame->lpVtbl->GetScene(frame, &scene);
	// Not an immortal particle system
    if (bee->ttl >= 0) 
	{        
        // Particle system still has time to live
		if (bee->ttl > 0)
		{
			// Decrement time to live
			--(bee->ttl);
			
			// particles gradually appear on screen
			if (bee->numonscreen < bee->properties->num) 
			{
				// Need to add a particle
 				bee->particles[bee->numonscreen]->active = 1;

				//Liou qinghua add
				bee->particles[bee->numonscreen]->plane->active = 1;

				++(bee->numonscreen);
			}
		} 
		// particle system has *no* time to live
		else 
		{   
			// gradually decrease particles on screen
			if (bee->numonscreen > 0) 
			{
				--(bee->numonscreen);       // decrement # of particles onscreen
			}
			
			// remove last particle on list
			bee->particles[bee->numonscreen]->active = 0;

			//Liou qinghua add
			bee->particles[bee->numonscreen]->plane->active = 0;

			// if all particles removed
			if (bee->numonscreen == 0) 
			{        
				// deactivate particle system
				bee->active = 0;
				
				for(j = 0; j < bee->properties->num; j++)
				{
					bee->particles[j]->plane->active = 0;
				}//Liou qinghua add

				return;
			}
		}
    } 	
	else 	
	{
		// Need to add a particle (particles added one at a time)
		if (bee->numonscreen < bee->properties->num) 
		{
			bee->particles[bee->numonscreen]->active = 1;

			//Liou qinghua add
			bee->particles[bee->numonscreen]->plane->active = 1;
			++(bee->numonscreen);
		}
    }

	// choose a random particle on screen ( gives realism effect)
    i = RAND % (bee->numonscreen);

	// apply a perturbance force to it
    bee->particles[i]->frame->lpVtbl->GetVelocity(bee->particles[i]->frame, 
		scene, &bee_vel, TRUE);
    if (bee->properties->perterb.x) 
	{
    	bee_vel.x -= (D3DVALUE)((RAND%((int)(65536.0*bee->properties->perterb.x)))/65536.0);
    	bee_vel.x += (D3DVALUE)((RAND%((int)(65536.0*bee->properties->perterb.x)))/65536.0);    	
    }
    if (bee->properties->perterb.y) 
	{
    	bee_vel.y -= (D3DVALUE)((RAND%((int)(65536.0*bee->properties->perterb.y)))/65536.0);
    	bee_vel.y += (D3DVALUE)((RAND%((int)(65536.0*bee->properties->perterb.y)))/65536.0);
    }
    if (bee->properties->perterb.z) 
	{
    	bee_vel.z -= (D3DVALUE)((RAND%((int)(65536.0*bee->properties->perterb.z)))/65536.0);
    	bee_vel.z += (D3DVALUE)((RAND%((int)(65536.0*bee->properties->perterb.z)))/65536.0);
	}

	// set the new force (force = velocity)
    bee->particles[i]->frame->lpVtbl->SetVelocity(bee->particles[i]->frame, 
		scene, bee_vel.x, bee_vel.y, bee_vel.z, TRUE);

	// for each particle on screen
    for (i = 0; i < bee->numonscreen; i++) 
	{
		// Increment the particle's distance along path.
		if (bee->numonscreen == bee->properties->num) 
		{
			bee->particles[i]->ttl += bee->properties->speed;
		}

		// Check to see if the particle has exceeded its time to live
		// note : the particle has a time to live and the system has a time to live
		// DO NOT CONFUSE
		if (bee->particles[i]->ttl > D3DVAL(1.0)) 
		{
			// if it has, restart it from origin
			// give it full life again ( 0 full 1 none)
			bee->particles[i]->ttl -= D3DVAL(1.0);
			
			// set to origin
			bee->dummy->lpVtbl->SetPosition(bee->dummy, bee->frame,
				bee->properties->origin.x,
				bee->properties->origin.y,
				bee->properties->origin.z);
			
			bee->dummy->lpVtbl->GetPosition(bee->dummy, scene, &bee_pos);
			bee->particles[i]->frame->lpVtbl->SetPosition(
				bee->particles[i]->frame, scene,
				bee_pos.x, bee_pos.y, bee_pos.z);
			
			// set velocity to 0
			bee->particles[i]->frame->lpVtbl->SetVelocity(bee->particles[i]->frame, 
				scene, D3DVAL(0.0), D3DVAL(0.0), D3DVAL(0.0), TRUE);
			bee->particles[i]->frame->lpVtbl->AddScale(bee->particles[i]->frame, D3DRMCOMBINE_REPLACE,
				D3DVAL(1), D3DVAL(1), D3DVAL(1));
	
			// orient sprites to face camera
			if (bee->camera != NULL) 
			{
				bee->particles[i]->frame->lpVtbl->SetRotation(bee->particles[i]->frame,	
					bee->camera,D3DVAL(0.0), D3DVAL(0.0), D3DVAL(1), 
					D3DVAL(RAND%(1<<16)/65536.0 - RAND%(1<<16)/65536.0));
				bee->particles[i]->frame->lpVtbl->LookAt(bee->particles[i]->frame,
					bee->camera, scene, D3DRMCONSTRAIN_Y);
			}
		} 
		else 
		{
			// it still has time left
			if ((i > 1) && (i < bee->numonscreen - 1)) 
			{
				i += RAND & 1;
			}
			// record the bee's position and velocity
			bee->particles[i]->frame->lpVtbl->GetPosition(bee->particles[i]->frame,
				scene, &bee_pos);
			bee->particles[i]->frame->lpVtbl->GetVelocity(bee->particles[i]->frame,
				scene, &bee_vel, TRUE);
    
			// calculate position of center of attraction (how far along path)
			// and store it in wasp_pos
			D3DRMVectorScale(&alongpath, &(bee->properties->direction), 
				(bee->particles[i]->ttl));
			D3DRMVectorAdd(&alongpath, &(bee->properties->origin), &alongpath);
			bee->frame->lpVtbl->Transform(bee->frame, &wasp_pos, &alongpath);
    		
			// find distance from center of attraction( which is wasp
			// a point in 3-d space that is moving at a constant
			// velocity, from origin to destination
			D3DRMVectorSubtract(&dist, &wasp_pos, &bee_pos);
			distance = D3DRMVectorModulus(&dist);

			// use distance to determine force
			if (distance == 0) 
			{
				distance = D3DVAL(1);
			}
			else 
			{
				distance = D3DDivide(D3DVAL(1), distance);
			}
			D3DRMVectorScale(&deltav, &dist, 
				D3DMultiply(bee->properties->acc, distance));
			D3DRMVectorAdd(&bee_vel, &bee_vel, &deltav);

			// if velocity is greater than maxv, scale velocity by .5
			if (D3DRMVectorDotProduct(&bee_vel, &bee_vel) > 
				bee->properties->maxv * bee->properties->maxv )
			{
				D3DRMVectorScale(&bee_vel, &bee_vel, D3DVAL(0.5));
			}
			if (bee->properties->wind > D3DVAL(0.0)) 
			{
				bee_vel.z += 
				D3DMultiply(D3DMultiply(bee->particles[i]->ttl, 
				bee->properties->wind), bee->particles[i]->ttl);
			}
			// set new force (velocity)
			bee->particles[i]->frame->lpVtbl->SetVelocity(bee->particles[i]->frame,
				scene, bee_vel.x, bee_vel.y, bee_vel.z, TRUE);

			// if sprites are supposed to scale as well as move
			bee->particles[i]->frame->lpVtbl->AddScale(bee->particles[i]->frame,
				D3DRMCOMBINE_BEFORE, bee->properties->scalefactor, 
				bee->properties->scalefactor, bee->properties->scalefactor);
		}
    }
	RELEASE(scene);
}

// **************************************************************************
// Name:          DestroyParticleSystem
//
// Author:        Jeremiah "Spudde" Childs
// 
// Date:          1996.6.12
//
// Description:   Destroys a single particle system object.  Frees all memory 
//                  that was allocated for it and destroys all RLObjects 
//                  associated with it.  Destroys all sprites in particle
//                  system.
//
// Arguments:     Psystem ** condemned:  (IN) Pointer to pointer to structure
//                  for particle system to be destroyed.
//
// Return:        None.
//
// Side Effects:  Frees memory and destroys RLObjects.
//
// Notes:			    
//
// Known Restrictions:
//
// Error Number:
//
// Update:
// Date				Name			Description
// =========================================================================
//
// **************************************************************************

void DestroyParticleSystem(Psystem** condemned)
{
	int i;
//	LPDIRECT3DRMFRAME parent;
   LPTEXTURESTRUCT *lplptextstructdummy;

	// if system already gone
	if (*condemned == NULL)
	{
		return;
	}
	// if active then deactivate the system
	if ((*condemned)->active) 
	{
		DeactivateParticleSystem(*condemned);
	}
    for (i = 0; i < ((*condemned)->properties->num); i++) 
	{
		DestroySprite((*condemned)->particles[i]);
	}
    // free the particles and the properties
	free((*condemned)->properties);
    free((*condemned)->particles);
	/*
	while (i = RLObjectGetReferenceCount((LPDIRECT3DRMOBJECT)((*condemned)->dummy))) 
	{
		RLFrameRemoveChild(RLFrameGetParent((*condemned)->dummy),(*condemned)->dummy);
	}
	*/
	MDFreeD3DFrame((*condemned)->dummy);
	MDFreeD3DFrame((*condemned)->frame);
	/*
	while (i = RLObjectGetReferenceCount((LPDIRECT3DRMOBJECT)((*condemned)->frame))) 
	{
		RLFrameRemoveChild(RLFrameGetParent((*condemned)->frame),(*condemned)->frame);
	}*/
   // Intuitively obvious.  Proof is left as an exercise
   lplptextstructdummy = ((*condemned)->lplpTexStruct);
	if (*lplptextstructdummy) 
   {
      ReleaseOneTexture(*lplptextstructdummy);
	   free(*lplptextstructdummy);
	   *(lplptextstructdummy) = NULL;
   }

    free((*condemned));
    (*condemned) = NULL;
}	

// **************************************************************************
// Name:          DestroyAllParticleSystems
//
// Author:        Jeremiah "Spudde" Childs
// 
// Date:          1996.6.12
//
// Description:   Destroys all particle systems in list of particle system.
//
// Arguments:     None.
//
// Return:        None.
//
// Side Effects:  None.
//
// Notes:			    
//
// Known Restrictions:
//
// Error Number:
//
// Update:
// Date				Name			Description
// =========================================================================
//
// **************************************************************************

void DestroyAllParticleSystems()
{
	int i;
	for (i = 0; i < MAX_NO_PSYSTEMS; i++)
	{
		if (allpsystems[i] != NULL) 
		{
			DestroyParticleSystem(&allpsystems[i]);
		}
	}
}


// **************************************************************************
// Name:          DestroyAllCxSprites
//
// Author:        Jeremiah "Spudde" Childs
// 
// Date:          1996.6.12
//
// Description:   Destroys all complex sprite objects in list of complex
//                  sprites.  Frees all memory that was allocated for them 
//                  and destroy all RLObjects associated with them.
//
// Arguments:     None.
//
// Return:        None.
//
// Side Effects:  Frees memory and destroys RLObjects.
//
// Notes:			    
//
// Known Restrictions:
//
// Error Number:
//
// Update:
// Date				Name			Description
// =========================================================================
//
// **************************************************************************

void DestroyAllCxSprites()
{
	int i;
//	LPDIRECT3DRMFRAME parent;
	
	// When a complex sprite is created, a pointer to that object 
	// is added to a list of all complex sprites, so they may be 
	// destroyed all at once at the end of a level, rather than 
	// individually destroyed by the module that created it.
	
	for (i = 0; i < MAX_NO_CXSPRITES; i++)
	{
		if (allcxsprites[i] != NULL) 
		{ // if sprite exists
			
			// Destroy RLObject of the frame
			/*
			while (RLObjectGetReferenceCount((LPDIRECT3DRMOBJECT)(allcxsprites[i]->frame))) 
			{
				RLFrameRemoveChild(RLFrameGetParent(allcxsprites[i]->frame),allcxsprites[i]->frame);
			}*/
			MDFreeD3DFrame(allcxsprites[i]->frame);

			ReleaseOneTexture(allcxsprites[i]->lpTexStruct);
			free(allcxsprites[i]->lpTexStruct);
			allcxsprites[i]->lpTexStruct = NULL;

			free(allcxsprites[i]);
			allcxsprites[i]=NULL;
		}
	}
	//free all trees and poles
	//FreeTreesPoles();
}


// **************************************************************************
// Name:          ResetParticles
//
// Author:        Jeremiah "Spudde" Childs
// 
// Date:          1996.6.12
//
// Description:   Reorients all sprites in particle system to face the 
//                  camera.
//
// Arguments:     Psystem *tobereset:  (IN) Pointer to structure for 
//                  particle system to be reset.
//
// Return:        None.
//
// Side Effects:  Changes orientation of RLFrames of all sprites in 
//                  the particle system.
//
// Notes:			    
//
// Known Restrictions:
//
// Error Number:
//
// Update:
// Date				Name			Description
// =========================================================================
//
// **************************************************************************
void ResetParticles(Psystem *tobereset)
{
    int i;

    if (tobereset->active == 1) 
	{
	    //it should be to set plane->active = 1
		for(i = 0; i < tobereset->properties->num; i++)
		{
			tobereset->particles[i]->plane->active = 1;
		}
		for (i = 0; i < (tobereset->numonscreen); i++) 
		{
		    tobereset->particles[i]->frame->lpVtbl->LookAt(
				tobereset->particles[i]->frame,	tobereset->camera, 
				Wscene, D3DRMCONSTRAIN_Y); //goman
	    }
    }
}

// **************************************************************************
// Name:          RenderAllParticles
//
// Author:        Jeremiah "Spudde" Childs
// 
// Date:          1996.6.12
//
// Description:   Function that renders immediate mode geometry of all 
//                  active sprites in all active particle systems.  It also
//                  calls swarmit() to apply the force law to the particle
//                  system.
//
// Arguments:     None.
//
// Return:        None.
//
// Side Effects:  None.
//
// Notes:			    
//
// Known Restrictions:
//
// Error Number:
//
// Update:
// Date				Name			Description
// =========================================================================
//
// **************************************************************************

//void RenderAllParticles()
void MoveAllParticles()
{
    int i, j;

	// for each particle system
	for (i = 0; i < MAX_NO_PSYSTEMS; i++)
	{	
		//if p system exists 
		if (allpsystems[i] != NULL) 
		{
			for(j = 0; j < allpsystems[i]->properties->num; j++)
			{
				if (allpsystems[i]->particles[j]->active == 0) 
				{
					allpsystems[i]->particles[j]->plane->active = 0;
				}
			}//Liou qinghua add 96,08,07

			// if system is active
			if (allpsystems[i]->active) 
			{
				for(j = 0; j < allpsystems[i]->properties->num; j++)
				{
					if (allpsystems[i]->particles[j]->active) 
					{
						allpsystems[i]->particles[j]->plane->active = 1;
					}//Liou qinghua add

				}
				if (allpsystems[i]->active == 1) 
				{		
					// update the system
					swarmit(allpsystems[i]->frame, (allpsystems[i]));
				}
				

			}
		}
    }
}

void RenderAllParticles()
{
    int i, j;
    LPDIRECT3DDEVICE lpD3DDev = NULL;


	// for each particle system
	for (i = 0; i < MAX_NO_PSYSTEMS; i++)
	{	
		//if p system exists 
		if (allpsystems[i] != NULL) 
		{
			for(j = 0; j < allpsystems[i]->properties->num; j++)
			{
				if (allpsystems[i]->particles[j]->active == 0) 
				{
					allpsystems[i]->particles[j]->plane->active = 0;
				}
			}//Liou qinghua add 96,08,07

			// if system is active
			if (allpsystems[i]->active) 
			{
				for(j = 0; j < allpsystems[i]->properties->num; j++)
				{
					if (allpsystems[i]->particles[j]->active) 
					{
       //char OutputString[64];
       //sprintf(OutputString,"in RAPS, plane is %d\n",allpsystems[i]->particles[j]->plane);
       //OutputDebugString(OutputString);

                //Wdevice->lpVtbl->GetDirect3DDevice(Wdevice, &lpD3DDev);



						allpsystems[i]->particles[j]->plane->active = 1;
						RenderPlane(allpsystems[i]->particles[j]->plane, Wdevice, Wview, allpsystems[i]->particles[j]->frame);
					}//Liou qinghua add
				}
			}
		}
    }
}


void RenderAllCxSprites()
{
    int i;
	LPDIRECT3DRMFRAME scene;

	//for each complex sprite
	for (i = 0; i < MAX_NO_CXSPRITES; i++)
	{
		// if exists
		if (allcxsprites[i] != NULL) 
		{
			// if complex sprite in rendered scene
			allcxsprites[i]->frame->lpVtbl->GetScene(
				allcxsprites[i]->frame, &scene);
			if(scene == Wscene)
			{
				allcxsprites[i]->active = 1;
				allcxsprites[i]->plane->active = 1;
				RenderPlane(allcxsprites[i]->plane, Wdevice, Wview, allcxsprites[i]->frame);
			}
			else
			{
				allcxsprites[i]->active = 0;
				allcxsprites[i]->plane->active = 0;
			}
		}
	}
	RELEASE(scene);
}

/*
void RenderAllCxSprites()
{
//    RLIMFlag clip;
    int i, k;

	//for each complex sprite
	for (i = 0; i < MAX_NO_CXSPRITES; i++)
	{
		// if exists
		if (allcxsprites[i] != NULL) 
		{
			
			// if complex sprite in rendered scene
			if (RLFrameGetScene(allcxsprites[i]->frame) == Wscene) 
			{

				// transform the vertices
				clip = RLIMTransformVertices(
					Wview,
					allcxsprites[i]->frame,
					&(allcxsprites[i]->points[0].position),
					(cxdestination),
					sizeof(RLIMLightingPoint),
					sizeof(RLIMViewVertex),
					8,
					1);

				for (k=0;k<8;k++) 
				{
					cxdestination[k].tu = allcxsprites[i]->u[k];
					cxdestination[k].tv = allcxsprites[i]->v[k];
				}

        // check to see if colors need to be reinitialized
				if ((Vmode) && (!RLIMColourStillValid(Wview, (allcxsprites[i]->surf))))
 				
					// reinitialize colors
					RLIMColourMeshPoints
					(   Wview,
						(allcxsprites[i]->surf),
						&(cxdestination[0].colour),
						sizeof(RLIMViewVertex),
						8
					);

					// set texture
					RLIMSetCurrentFill(
					Wview,
					allcxsprites[i]->texture,
					0,
					0,
					0
					);

					// draw the triangles
					RLIMDrawTriangles(
					Wview,
					(allcxsprites[i]->triangles),
					sizeof(RLIMTriangle),
					8,
					RLIM_UNLIT_QUALITY,
					clip);
				
			}
		}
	}
}
*/
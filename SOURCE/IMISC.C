/***********************************************************************\
 *	  (C) Copyright 1995 by 47-TEK, Inc.							   *
 *																	   *
 *	  This program is copyrighted by 47-TEK, Inc. and is  not licensed *
 *	  to you under any conditions.	You may not distribute, duplicate, *
 *	  or  publish the source code of this program in any form.	You    *
 *	  may  not incorporate this code in any form in derivative	works. *
 *																	   *
 *																	   *
 *	  47-Tek is a registered trademark of 47-TEK, Inc.				   *
 *	  47-TEK Specifically disclaims any implied Warranty of Mer-	   *
 *	  chantability or fitness for a particular use. 47-TEK,  Inc.	   *
 *	  does not Warrant that the operation of the program will be	   *
 *	  uninterrupted or error free.									   *
 *																	   *
\***********************************************************************

Program:		Goman95
File:			IMISC.C
Author: 		Jeremiah Spudde Childs
Date:			10/24/95
Version:		version 1.0

Development Environment:   MSVC 2.0, Reality Lab 2.0 Beta 21 runtime dll
						   Reality Lab 2.0 Build 21.

************************************************************************
$Header:   H:/pvcs/pvcsproj/gomand3d.prj/IMISC.C_V   1.15   07 May 1997 13:08:38   Bruce  $

$Log:   H:/pvcs/pvcsproj/gomand3d.prj/IMISC.C_V  $
 * 
 *    Rev 1.15   07 May 1997 13:08:38   Bruce
 * removed ifdef _47TEK_RL_ crap, made 
 * extensive modifications to the loading
 * procedure so that .bin files can be loaded
 * instead of .x files.
 * 
 *	  Rev 1.14	 10 Apr 1997 11:04:22	JEREMIAH
 * Added support for SEMIFANCY transparency
 * type.
 * 
 *	  Rev 1.13	 Mar 20 1997 17:24:16	JEREMIAH
 * Set zwriteenable on and off in FANCY-type
 * transparency. 
 * 
 *	  Rev 1.12	 12 Mar 1997 12:44:32	JEREMIAH
 * Set DEST_BLENDs to BLEND_ZERO
 * for non-semi-transparent styles.
 * 
 *	  Rev 1.11	 12 Mar 1997 10:37:50	JEREMIAH
 * Set transparency values according to
 * transparency style.
 * 
 *	  Rev 1.10	 10 Mar 1997 13:24:54	JEREMIAH
 * Created glowing alpha blending.
 * 
 *	  Rev 1.9	07 Mar 1997 14:53:46   JEREMIAH
 * Reversed the checks for MODULATEALPHA
 * and MODULATE.
 * 
 *	  Rev 1.8	07 Mar 1997 14:07:54   TIM
 * Added get caps for transparency and translucency
 * (only tested on permedia)
 * 
 *	  Rev 1.7	06 Mar 1997 14:41:02   JEREMIAH
 * Migrated render call for miscellaneous
 * objects to pure IM, called by 
 * RenderAllMiscDLists().
 * 
 *	  Rev 1.6	04 Feb 1997 16:30:28   JEREMIAH
 * Skipped past revision 1.5.
 * Beta 1.02A seems to cause a fatal crash
 * that occurs at QueryInterface when loading
 * the generic building texture.  Reason 
 * unknown.
 * 
 * 
 *	  Rev 1.4	23 Jan 1997 11:57:52   BRUCE
 * added ByDumpInfo for bad file read.
 * 
 *	  Rev 1.3	Dec 19 1996 11:50:26   JEREMIAH
 * Correctly handles untextured 
 * miscellaneous objects.
 * 
 * 
 *	  Rev 1.2	Dec 19 1996 10:53:04   JEREMIAH
 * Handles untextured miscellaneous
 * objects.
 * 
 *	  Rev 1.1	15 Nov 1996 14:01:16   JEREMIAH
 * Changed by Liou GuoHong (ITC).  
 * Implemented copy mode for 8-bit rendering.

***********************************************************************/
#include <windows.h>
#include <stdio.h>


#include <d3d.h>
#include "d3dmacs.h"
#include "mdtex.h"
#include "rl2d3d.h"
#include "global.h"
#include "binload.h"

#include "imisc.h"
#include "tekmath.h"
#include "d3dappi.h"

static D3DRMMATRIX4D TheRMMatrix;
static D3DMATRIX TheMatrix =
{
	D3DVAL(1.0), D3DVAL(0.0), D3DVAL(0.0), D3DVAL(0.0),
	D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0), D3DVAL(50.0),
	D3DVAL(0.0), D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0),
	D3DVAL(0.0), D3DVAL(51.0), D3DVAL(0.0), D3DVAL(1.0)
};
static D3DMATRIXHANDLE hTheMatrix;
static int TheMatrixOffset;


iobjdlist* allmiscdlists[MAX_NO_MISCDLISTS];

unsigned char miscdlistcount = 0;

extern RLDevice Wdevice;
extern RLFrame Wscene;
extern RLViewport Wview;
extern int Vmode;

void KillAPart(iobjdlist *parts);


void CleanupObjects(LPDIRECT3DRMOBJECT dev, void* arg)
{
	iobjdlist* thelist = (iobjdlist*) arg;

	if (thelist->eb) 
	{
		thelist->eb->lpVtbl->Release(thelist->eb);
		thelist->mat->lpVtbl->Release(thelist->mat);

		if (thelist->NOparent == -1) 
		{
//			DeleteBinary (thelist->builder);  // Be called from BinLoad file...
//			thelist->builder->lpVtbl->Release(thelist->builder);
			if (thelist->lpTexture) ReleaseOneTexture(thelist->lpTexture);
		}
		thelist->eb = NULL;
		thelist->dev = NULL;
//		thelist->builder = NULL;
	}
}

extern int VM_W3D;
extern int VM_H3D;
extern int VM_BPP3D;

BOOL CreateObjects(iobjdlist *thelist, LPDIRECT3DRMDEVICE dev)
{
	D3DEXECUTEBUFFERDESC desc;
	D3DEXECUTEDATA data;
	LPDIRECT3D lpD3D = NULL;
	LPDIRECT3DDEVICE lpD3DDev = NULL;
	LPDIRECT3DMATERIAL mat = NULL;
	LPDIRECT3DEXECUTEBUFFER eb = NULL;
	D3DMATERIALHANDLE hMat;
	D3DMATERIAL orange;
	DWORD vsize, tsize, size;
	void* p;
	LPVOID lpBufStart, lpInsStart;

//	LPDIRECT3DRMMESHBUILDER builder = NULL;
//	D3DVECTOR *vertices = NULL, *normals = NULL;
	DWORD tcount = 0, vcount = 0, ncount = 0;
	DWORD face_data_size = 0;
//	DWORD *face_data = NULL, *temp;
//	WORD index;
	D3DVERTEX *TempVertex;
	D3DTRIANGLE *TempTriangle;

//	  RELEASE(thelist->eb);

//	builder = thelist->builder; 

//	if (FAILED(builder->lpVtbl->GetVertices(builder,
//		&vcount, NULL, &ncount, NULL,
//		&face_data_size, NULL)))
//	{
//		return FALSE;
//	}
	vsize = GetVCount (thelist->builder, 0);
	vcount=vsize/sizeof(D3DVERTEX);
	tsize = GetTCount (thelist->builder, 0);
	tcount=tsize/ sizeof(D3DTRIANGLE);
	
	thelist->tcount = tcount;
	thelist->vcount = vcount;

	//Lgh added
	
	if (thelist->bTransparent)
	{
		size = vsize + tsize +
			9 * sizeof(D3DINSTRUCTION) + 14 * sizeof(D3DSTATE) +
			sizeof(D3DSTATUS) + sizeof(D3DPROCESSVERTICES);
	}
	else 
	{
		size = vsize + tsize +
			8 * sizeof(D3DINSTRUCTION) + 14 * sizeof(D3DSTATE) +
			sizeof(D3DSTATUS) + sizeof(D3DPROCESSVERTICES);
	}
	size += sizeof(D3DINSTRUCTION) * 1;   // for matrix multiply
	size += sizeof(D3DSTATE) * 1;		  // for matrix multiply

	dev->lpVtbl->GetDirect3DDevice(dev, &lpD3DDev);
	if (!lpD3DDev)
	{
		goto generic_error;
	}
	if (FAILED(lpD3DDev->lpVtbl->GetDirect3D(lpD3DDev, &lpD3D)))
	{
		goto generic_error;
	}
   
	MAKE_MATRIX(lpD3DDev, hTheMatrix, TheMatrix);


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
	memset(&orange, 0, sizeof(orange));
	orange.dwSize = sizeof(orange);
	orange.ambient.r = orange.diffuse.r = D3DVAL(1.0);
	orange.ambient.g = orange.diffuse.g = D3DVAL(1.0);
	orange.ambient.b = orange.diffuse.b = D3DVAL(1.0);
	orange.ambient.a = orange.diffuse.a = D3DVAL(0.6);
	orange.dwRampSize = 1;
	 if (thelist->lpTexture) 
	   orange.hTexture = thelist->lpTexture->hTex;	
	else
	   orange.hTexture = 0L;

	if (FAILED(mat->lpVtbl->SetMaterial(mat, &orange)))
	{
		goto generic_error;
	}
	if (FAILED(eb->lpVtbl->Lock(eb, &desc)))
	{
		goto generic_error;
	}
	p = (void*) ((char*) desc.lpData);
	lpBufStart = desc.lpData;

	// Adding by Liou Song.
	memset(p, 0, size);
	TempVertex = p; 	 // BSH change Song's code !
	thelist->Vertex = p;

//	p = (void*) ((char*) desc.lpData + vsize);
	p = LoadVertex(thelist->builder, 0, p);

	lpInsStart = p;

	OP_STATE_LIGHT(1, p);
		STATE_DATA(D3DLIGHTSTATE_MATERIAL, hMat, p);
		
	OP_SET_STATUS(D3DSETSTATUS_ALL, D3DSTATUS_DEFAULT, 2048, 2048, 0, 0, p);

   thelist->matrixoffset=((unsigned long) p)-((unsigned long)lpBufStart);
	OP_STATE_TRANSFORM(1, p);
		STATE_DATA(D3DTRANSFORMSTATE_WORLD, hTheMatrix, p);
	
	
	OP_PROCESS_VERTICES(1, p);
	if (VM_BPP3D == 8)
   {
		PROCESSVERTICES_DATA(D3DPROCESSVERTICES_TRANSFORM, 0, vcount, p);
   }
   else
   {
		PROCESSVERTICES_DATA(D3DPROCESSVERTICES_TRANSFORMLIGHT, 0, vcount, p);
   }
	OP_STATE_RENDER(1, p);
		STATE_DATA(D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT, p);

   if (thelist->lpTexture) {
	  OP_STATE_RENDER(3, p);
			 STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE, thelist->lpTexture->hTex, p); //Liou qinghua
		   STATE_DATA(D3DRENDERSTATE_WRAPV, FALSE, p);
			STATE_DATA(D3DRENDERSTATE_BLENDENABLE, thelist->bTransparent, p);

   } else {
	  OP_STATE_RENDER(3, p);
			 STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE, 0L, p);	// Spudde
		   STATE_DATA(D3DRENDERSTATE_WRAPU, FALSE, p);
			STATE_DATA(D3DRENDERSTATE_BLENDENABLE, thelist->bTransparent, p);

   }

		// check if alpha blending is enabled, if not then color keying
		
	if	(d3dapprs.transparency == COLORKEY) 
	{
		OP_STATE_RENDER(3, p);
			STATE_DATA(D3DRENDERSTATE_BLENDENABLE, thelist->bTransparent, p);
			STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_COPY, p);
			STATE_DATA(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA, p);	
	}
	else
	{
		// make sure selected alpha blend capability is supported in hardware 

		OP_STATE_RENDER(1, p);
			STATE_DATA(D3DRENDERSTATE_BLENDENABLE, thelist->bTransparent, p);

		// for simplest alpha translucency

		if	(d3dapprs.transparency == FANCY)
		{

			OP_STATE_RENDER(5, p);
				STATE_DATA(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE,p);
				STATE_DATA(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA,p);
				STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATEALPHA, p);
			STATE_DATA(D3DRENDERSTATE_ZENABLE, TRUE, p);
			STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE, FALSE, p);
		}
		else 
		if	(d3dapprs.transparency == SEMIFANCY)
		{

			OP_STATE_RENDER(5, p);
			STATE_DATA(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA,p);
				STATE_DATA(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA,p);
				STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATEALPHA, p);
			STATE_DATA(D3DRENDERSTATE_ZENABLE, TRUE, p);
			STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE, FALSE, p);
		}
		else 
	  if  (d3dapprs.transparency == TRANSLUCENT)
		{

			OP_STATE_RENDER(3, p);
//						 STATE_DATA(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE,p);
//						 STATE_DATA(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA,p);
			STATE_DATA(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA,p);
			STATE_DATA(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE,p);
			STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATE, p);
//			 STATE_DATA(D3DRENDERSTATE_ZENABLE, TRUE, p);
//			  STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE, FALSE, p);
		}
		else 
	  // for simplest alpha transparency
		if	(d3dapprs.transparency == NORMTRANSPARENT)
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

	OP_TRIANGLE_LIST((WORD)tcount, p);
	TempTriangle	  = p;	  //// BSH change Song's code !
	thelist->Triangle = p;

//	p = (void*) ((char*)p + tsize);
	p = LoadTriangle(thelist->builder, 0, p);
	OP_EXIT(p);

	if (FAILED(eb->lpVtbl->Unlock(eb)))
	{
		goto generic_error;
	}

	data.dwSize 			 = sizeof(data);
	data.dwVertexOffset 	 = 0;
	data.dwVertexCount		 = vcount;
	data.dwInstructionOffset = vcount * sizeof(D3DVERTEX);
	data.dwInstructionLength = (ULONG) ((char *)p - (char *)lpInsStart);
//	  data.dwHVertexOffset	   = 0;
	
	if (FAILED(eb->lpVtbl->SetExecuteData(eb, &data)))
	{	
		goto generic_error;
	}

	thelist->eb  = eb;
	thelist->mat = mat;
	thelist->dev = dev;

	if (FAILED(dev->lpVtbl->AddDestroyCallback(dev, CleanupObjects, thelist)))
	{
		goto generic_error;
	}

	RELEASE(lpD3DDev);
	RELEASE(lpD3D);

	// Adding by Liou Song.
#if 0
	vertices   = calloc(vcount, sizeof(D3DVECTOR));
	normals    = calloc(ncount, sizeof(D3DVECTOR));
	face_data  = calloc(face_data_size, sizeof(DWORD));

	if (FAILED(builder->lpVtbl->GetVertices(builder,
		&vcount, vertices, &ncount, normals,
		&face_data_size, face_data)))
	{
		return FALSE;
	}

	for (index = 0; index < vcount; index++)
	{
		TempVertex[index].x  = vertices[index].x;
		TempVertex[index].y  = vertices[index].y;
		TempVertex[index].z  = vertices[index].z;
		TempVertex[index].nx = normals[index].x;
		TempVertex[index].ny = normals[index].y;
		TempVertex[index].nz = normals[index].z;
		builder->lpVtbl->GetTextureCoordinates(builder, index,
			&TempVertex[index].tu, &TempVertex[index].tv);
	}

	temp = face_data;

	for (index = 0; index < tcount; index++)
	{
		if ((WORD)(*temp++) != 3)
		{
			return FALSE;
		}
		TempTriangle[index].v1	   = (WORD)(*temp++);
		temp++;
		TempTriangle[index].v2	   = (WORD)(*temp++);
		temp++;
		TempTriangle[index].v3	   = (WORD)(*temp++);
		temp++;
		TempTriangle[index].wFlags = D3DTRIFLAG_EDGEENABLETRIANGLE; 
	}

	free(face_data);
	free(normals);
	free(vertices);
#endif
	return TRUE;
generic_error:
	RELEASE(lpD3D);
	RELEASE(lpD3DDev);
	RELEASE(mat);
	RELEASE(eb);
	return FALSE;
}


BOOL RenderObject(iobjdlist *thelist,  LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view)
{
	D3DVERTEX* v;
	D3DEXECUTEBUFFERDESC desc;
	D3DEXECUTEDATA data;
	LPDIRECT3DDEVICE lpD3DDev = NULL;
	LPDIRECT3DVIEWPORT lpD3DView = NULL;
	HRESULT rval;
	void *ThisBetterWork;


	if (thelist->dup != 2)
	{
		dev->lpVtbl->GetDirect3DDevice(dev, &lpD3DDev);
		view->lpVtbl->GetDirect3DViewport(view, &lpD3DView);
		if (!lpD3DDev || !lpD3DView)
		{
			goto ret_with_error;
		}

		desc.dwSize = sizeof(desc);
		desc.dwFlags = 0;
		if (FAILED(thelist->eb->lpVtbl->Lock(thelist->eb, &desc)))
		{
			goto ret_with_error;
		}
		v = (D3DVERTEX*) desc.lpData;

   RecursivelyGetManyTransforms(thelist->frame,TheRMMatrix);

   memcpy(&TheMatrix, TheRMMatrix, sizeof(D3DMATRIX));
								
   lpD3DDev->lpVtbl->SetMatrix(lpD3DDev, hTheMatrix, &TheMatrix);

	  ThisBetterWork=(void *)(((unsigned long)desc.lpData) + ((unsigned long)thelist->matrixoffset));

   OP_STATE_TRANSFORM(1, ThisBetterWork);
   STATE_DATA(D3DTRANSFORMSTATE_WORLD, hTheMatrix, ThisBetterWork);

		if (FAILED(thelist->eb->lpVtbl->Unlock(thelist->eb)))
		{
			goto ret_with_error;
		}

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
		return TRUE;
	ret_with_error:
		RELEASE(lpD3DDev);
		RELEASE(lpD3DView);
		return FALSE;
	}//if (thelist->Dup != 2)
}

int ObjectCallback(LPDIRECT3DRMUSERVISUAL uvis,
				 void* arg,
				 D3DRMUSERVISUALREASON reason,
				 LPDIRECT3DRMDEVICE dev,
				 LPDIRECT3DRMVIEWPORT view)
{
	iobjdlist *thelist = (iobjdlist*) arg;
	if (reason == D3DRMUSERVISUAL_CANSEE)
	{
		return TRUE;
	}
	if (reason == D3DRMUSERVISUAL_RENDER) 
	{
	   //if (!thelist->bTransparent) 
	   if (0)
	   {
		  if (!RenderObject(thelist, dev, view))
		   {
			   return DDERR_GENERIC;
		   }
		   else
		   {
			   return D3D_OK;
		   }
	   }
	   else
		 return D3D_OK;
	}
	return 0;
}

void DestroyObject(LPDIRECT3DRMOBJECT obj, void* arg)
{
	iobjdlist *thelist = (iobjdlist*) arg;

	if (thelist->dup != 2)
	{
		if (thelist->dev)
		{
			thelist->dev->lpVtbl->DeleteDestroyCallback(thelist->dev, CleanupObjects, arg);
		}
		CleanupObjects((LPDIRECT3DRMOBJECT)thelist->dev, (void*) thelist);
	}// BSH add it for using the function of 'DupDListForCopyUVis'
}

extern RLDevice Wdevice;
int MeshtoDList(Handle hTheMesh, LPTEXTURESTRUCT lpTexture, 
				LPDIRECT3DRMFRAME frame, BOOL bTransparent)
{
	iobjdlist *thelist;
	LPDIRECT3DRMUSERVISUAL uvis = NULL;

	// setup new node in linked list
	RLMalloc((void**)&thelist, sizeof(iobjdlist));
	memset(thelist, 0, sizeof(iobjdlist));
	allmiscdlists[miscdlistcount] = thelist;
	thelist->NOparent			  = -1;
	thelist->dup				  = 0;
	thelist->frame				  = frame;
	thelist->lpTexture			  = lpTexture;
	thelist->builder			  = hTheMesh;
	thelist->bTransparent		  = bTransparent;
//BSH add it in 96-9-6
	if (!CreateObjects (thelist, Wdevice))
	{
		return FALSE;
	}

	if (FAILED(lpD3DRM->lpVtbl->CreateUserVisual(lpD3DRM, ObjectCallback, (void*) thelist, &uvis)))
	{
		goto ret_with_error;
	}

	if (FAILED(uvis->lpVtbl->AddDestroyCallback(uvis, DestroyObject, (void*) thelist)))
	{
		goto ret_with_error;   
	}

	if (uvis)
	{
		frame->lpVtbl->AddVisual (frame, (LPDIRECT3DRMVISUAL)uvis);
		thelist->uvis = uvis;
	}

	RELEASE(uvis);
	return(miscdlistcount++);
ret_with_error:
	if (thelist)
	{
		free(thelist);
	}
	RELEASE(uvis);
	return miscdlistcount;
}

extern char XafPath[];
int LoadIntoDList (char* name, LPDIRECT3DRMFRAME parent, LPTEXTURESTRUCT lpTexture, void *surface)
{
	int index;
	LPDIRECT3DRMFRAME frame;
//	LPDIRECT3DRMMESHBUILDER builder = NULL;
	Handle hBin;
	char filename[MAX_PATH];
	BOOL bTransparent;
	char *where;

	if (surface)
	{
		bTransparent = TRUE;
	}
	else 
	{
		bTransparent = FALSE;
	}

	strcpy(filename, XafPath);
	strcat(filename, "\\");
	strcat(filename, name);
	where=strchr(filename,'.');
	if(where)
		*where=0;
	strcat(filename,".bin");

	lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, parent, &frame);
	if(!(hBin=CreateBinary(filename)))
	{
		BYDumpInfo("**********************************");
		BYDumpInfo("Couldn't create binary model for");
		BYDumpInfo(filename);
		BYDumpInfo("**********************************");
	}
	
//	if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &builder)))
//	{
//
//		BYDumpInfo("**********************************");
//		return FALSE;
//	}

//	if (FAILED(builder->lpVtbl->Load(builder, filename, NULL, D3DRMLOAD_FROMFILE, 
//		NULL, NULL)))
//	{
//		BYDumpInfo("**********************************");
//		BYDumpInfo("couldn't load file:");
//		BYDumpInfo(filename);
//
//		BYDumpInfo("**********************************");
//		return FALSE;
//	}

	index = MeshtoDList(hBin, lpTexture, frame, bTransparent);		

	RELEASE(frame);
	//	  RELEASE(builder);  Here I found mistake. Don't open it.
	return (index);
}

int DupDListForCopyUVis(int originaldlist, RLFrame parent)
{
	iobjdlist *thelist, *origdlist;

	// setup new node in linked list
	RLMalloc ((void**)&thelist, sizeof(iobjdlist));
	memset (thelist, 0, sizeof(iobjdlist));
	allmiscdlists[miscdlistcount] = thelist;
	origdlist					  = allmiscdlists[originaldlist];
	// if dup is 2, it mean: add other uvis to thelist's frame, it is new result.
	thelist->dup				  = 2; 
	thelist->frame				  = RLCreateFrame(parent);
	thelist->uvis				  = origdlist->uvis;
	thelist->bTransparent		  = origdlist->bTransparent;
	if (thelist->uvis)
	{
		thelist->frame->lpVtbl->AddVisual (thelist->frame, 
			(LPDIRECT3DRMVISUAL)thelist->uvis);
	}
	RELEASE(thelist->uvis);
	return(miscdlistcount++);
}

int DupDList (int originaldlist, RLFrame parent)
{
	iobjdlist *thelist, *origdlist;
	LPDIRECT3DRMUSERVISUAL uvis = NULL;

	// setup new node in linked list
	RLMalloc ((void**)&thelist, sizeof(iobjdlist));
	memset (thelist, 0, sizeof(iobjdlist));
	allmiscdlists[miscdlistcount] = thelist;
	origdlist					  = allmiscdlists[originaldlist];
	thelist->NOparent			  = originaldlist; // new !
	thelist->dup				  = 1;
	thelist->frame				  = RLCreateFrame(parent);
	thelist->lpTexture			  = origdlist->lpTexture;
	thelist->builder			  = origdlist->builder;

	thelist->mat				  = origdlist->mat;
	thelist->vcount 			  = origdlist->vcount;
	thelist->tcount 			  = origdlist->tcount;
	thelist->bTransparent = origdlist->bTransparent;

//BSH add it in 96-9-6
	if (!CreateObjects (thelist, Wdevice))
	{
		return FALSE;
	}

	if (FAILED(lpD3DRM->lpVtbl->CreateUserVisual(lpD3DRM, ObjectCallback, 
		(void*) thelist, &thelist->uvis)))
	{
		goto ret_with_error;
	}
	if (FAILED(thelist->uvis->lpVtbl->AddDestroyCallback(thelist->uvis, 
		DestroyObject, (void*) thelist)))
	{
		goto ret_with_error;   
	}
	if (thelist->uvis)
	{
		thelist->frame->lpVtbl->AddVisual (thelist->frame, 
			(LPDIRECT3DRMVISUAL)thelist->uvis);
	}

	RELEASE(thelist->uvis);// I don't know why after RELEASE uvis, the address of uservisual is zero.
	return(miscdlistcount++);
ret_with_error:
	if (thelist)
	{
		free(thelist);
	}
	RELEASE(thelist->uvis);
	return miscdlistcount;
}

void DestroyMiscDLists(void)
{
	for (; miscdlistcount > 0; miscdlistcount--) 
	{
		RLFrame parent = RLFrameGetParent(allmiscdlists[miscdlistcount-1]->frame);
		//RLFrame grandparent = RLFrameGetParent(parent);
		MDFreeD3DFrame (allmiscdlists[miscdlistcount-1]->frame);
		allmiscdlists[miscdlistcount-1]->frame = NULL;
		MDFreeD3DFrame (parent);
		parent = NULL;
		free(allmiscdlists[miscdlistcount-1]);
		allmiscdlists[miscdlistcount-1] = NULL;
	}
}

void RenderAllMiscDLists()
{
   int i;

   for (i=0; i<miscdlistcount; i++) 
   {
	  if (allmiscdlists[i] != NULL)
	  {
		 //if (allmiscdlists->bTransparent)
		 if (RLFrameGetScene(allmiscdlists[i]->frame) == Wscene)
		 {
			RenderObject(allmiscdlists[i], Wdevice, Wview);
		 }				 
	  }
   }
}

void FlipTextureCoords(int whichdlist, int whichside)
{
	int i;
// New code for Doom..., and BSH add it in 8/30 !	
	D3DEXECUTEBUFFERDESC desc;

	if (allmiscdlists[whichdlist]->eb == NULL) 
	{
		;
		return; 
	}

	desc.dwSize = sizeof(desc);
	desc.dwFlags = 0;
	allmiscdlists[whichdlist]->eb->lpVtbl->Lock(
				allmiscdlists[whichdlist]->eb, &desc);

	allmiscdlists[whichdlist]->Vertex = (D3DVERTEX*) desc.lpData;
//end...
	for (i = 0; i < (int)allmiscdlists[whichdlist]->vcount; i++)
	{	
		if ((whichside == 0) && (allmiscdlists[whichdlist]->Vertex[i].tu > 0.5))
		{
			allmiscdlists[whichdlist]->Vertex[i].tu -= RLVal(0.5);
		}
		if ((whichside == 1) && (allmiscdlists[whichdlist]->Vertex[i].tu < 0.5)) 
		{
			allmiscdlists[whichdlist]->Vertex[i].tu += RLVal(0.5);
		}
	}
// New code for Doom..., and BSH add it in 8/30 !	
	allmiscdlists[whichdlist]->eb->lpVtbl->Unlock(
				allmiscdlists[whichdlist]->eb);
//end...
}

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
File:           TWIST.C
Author:         Bo Yuan
Date:           09/26/95
Version:        version 1.2



************************************************************************
REVISION HISTORY        

$Header:   H:/pvcs/pvcsproj/gomand3d.prj/TWIST.C_V   1.16   07 May 1997 13:11:44   Bruce  $

$Log:   H:/pvcs/pvcsproj/gomand3d.prj/TWIST.C_V  $
 * 
 *    Rev 1.16   07 May 1997 13:11:44   Bruce
 * changed from .x to .bin loading of models.
 * 
 *    Rev 1.15   21 Mar 1997 15:35:30   JEREMIAH
 * Disabled texture blending for the buildings.
 * 
 *    Rev 1.14   Mar 20 1997 17:13:32   JEREMIAH
 * Set zenable and zwriteenable to TRUE.
 * 
 *    Rev 1.13   06 Mar 1997 14:49:26   JEREMIAH
 * Optimized execute buffers in 8-bit by 
 * changing from _TRANSFORMLIGHT to 
 * _TRANSFORM.
 * 
 * 
 *    Rev 1.12   25 Feb 1997 17:43:06   JEREMIAH
 * Fixed memory leaks in building code.
 * 
 *    Rev 1.11   24 Feb 1997 15:19:48   JEREMIAH
 * Debranched 1.10.1.0 to 1.11.
 * 
 *    Rev 1.10.1.0   21 Feb 1997 16:05:54   JEREMIAH
 * Do not clear level_flag after level.
 * 
 *    Rev 1.10   14 Feb 1997 20:04:30   BRUCE
 * removed _47TEK_RL_ code
 * removed _ITC_D3D_ conditional
 * changed g_level to GameStates.CurrentLevel
 * 
 * 
 *    Rev 1.9   07 Feb 1997 08:38:22   BRUCE
 * removed all the _47_RL_ code, and put in
 * Tim's changes to make the buildings
 * bilinear filtered.
 * 
 *    Rev 1.8   04 Feb 1997 16:35:22   JEREMIAH
 * Skipped past revision 1.7.
 * Beta 1.02A seems to cause a fatal crash
 * that occurs at QueryInterface when loading
 * the generic building texture.  Reason 
 * unknown.
 * 
 * 
 *    Rev 1.6   23 Jan 1997 12:12:20   BRUCE
 * added BYDumps for bad loading.
 * 
 *    Rev 1.5   06 Jan 1997 16:27:50   JEREMIAH
 * Reduced rampsize on all materials to 1
 * to eliminate palettizing pause bug.
 * 
 *    Rev 1.4   06 Jan 1997 13:45:48   JEREMIAH
 * Changed BmpLevelName() to 
 * ConstructLevelName() for loading of 
 * building textures.
 * 
 *    Rev 1.3   20 Dec 1996 17:06:42   JEREMIAH
 * Changed filenames of textures to match
 * new filename conventions for level-specific
 * palettes.
 * 
 *    Rev 1.2   15 Nov 1996 16:59:50   JEREMIAH
 * Changed by Liou GuoHong (ITC).
 * Implemented copy mode for 8-bit rendering.
 * 
 * 
 *    Rev 1.1   11 Nov 1996 11:36:06   JEREMIAH
 * Changed by Liu Song (ITC).  Fixed building
 * collision detection.
***********************************************************************/

// Adding by Liu Song
#include "rl2d3d.h"
#include "global.h"
#include "mybuild.h"
#include "bldgboom.h"
extern LPDIRECT3DRM lpD3DRM;
extern LPDIRECTDRAWCLIPPER lpDDClipper;
extern BOOL bQuit;
extern DWORD GSize;

DWORD TCount = 0,VCount = 0, NCount = 0;
D3DVERTEX *GVertices;
D3DTRIANGLE *GTriangles;


//extern int g_level;
extern char XafPath[];
extern char BmpPath[];
extern building_area *which1_bldg, *which2_bldg;
extern RLFrame behindthescene;

EbInfo GebInfo[GEB_COUNT]; // For generic building.
EbInfo SebInfo[SEB_COUNT]; // For specific building.
LPTEXTURESTRUCT lpTextureStruct[3];

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>


#include "building.h"
#include "landscap.h"
#include "gosys.h"
#include "d3dappi.h"
#include "binload.h"

#pragma warning( disable : 4244)

#define TOTAL_GVERTICES  20
#define TOTAL_GTRIANGLES 10

#ifndef LSMASK
extern cGlobalstype cGlobals;
extern RLFrame Wscene;
extern RLViewport Wview;
extern RLDevice Wdevice;
extern int Vmode;
#endif LSMASK

int vc;
static int YBBuildingFlag= 0;

GDPLIST* load_specific_building(int id, D3DTEXTUREHANDLE spectex, RLBox *thebox);

RLValue *Gu, *Gv;

RLBox boxes[6];
GDPLIST* specificdlists[7];


static bd_1sttime = 1;

GDPLIST gdlist;
static lvl_bldg_rsrcs kevin;
triangle_list lvl_tris;
visible_buildings vb;
D3DTEXTUREHANDLE specsurf, eggsurf;

char* ArtLevelName(char* name)
{
	static char filename[20];
	static char pathname[80];

	strcpy(pathname, XafPath);
	strcat(pathname, "\\");

	switch (GameStates.CurrentLevel) {
	case 0:
		strcpy(filename, "LX"); break;
	case 1:
		strcpy(filename, "LM"); break;
	case 2:
		strcpy(filename, "LR"); break;
	case 3:
		strcpy(filename, "LH"); break;
	case 4:
		strcpy(filename, "LS"); break;
	case 5:
		strcpy(filename, "LN"); break;
	case 6:
		strcpy(filename, "LT"); break;
	}

	strcat(filename, name);

	if ((name[0] == '6') && (name[1] == '6'))
	{
		filename[1] = '_';
		filename[4] = '_';
	}

	strcat(pathname, filename);

	return pathname;
}

char* BmpLevelName(char* name)
{
	static char filename[20];
	static char pathname[80];

//	strcpy(pathname, BmpPath);

	switch (GameStates.CurrentLevel) {
	case Trainer:
		strcpy(filename, "LX"); break;
	case Mojave:
		strcpy(filename, "LM"); break;
	case Rockies:
		strcpy(filename, "LR"); break;
	case Hawaii:
		strcpy(filename, "LH"); break;
	case SanFrancisco:
		strcpy(filename, "LS"); break;
	case NewYork:
		strcpy(filename, "LN"); break;
	case Tokyo:
		strcpy(filename, "LT"); break;
	}

	strcat(filename, name);

	strcpy(pathname, filename);

	return pathname;
}

char* PathName(char* name)
{
	static char pathname[80];

	strcpy(pathname, XafPath);
	strcat(pathname, "\\");

	strcat(pathname, name);
	return pathname;
}



//
RLIMTriangle *filltriangles(int building_num)
{
	return (NULL);
}

void GetSpecificBox(int building_num, RLBox *abox)
{
	int whichone;
	
	if (building_num==13) whichone=0;
	if (building_num==15) whichone=1;
	if (building_num==20) whichone=2;
	if (building_num==66) whichone=3;
	if (building_num==67) whichone=4;
	if (building_num==68) whichone=5;

	abox->min.x = boxes[whichone].min.x;
	abox->max.x = boxes[whichone].max.x;
	abox->min.y = RLVal(0);
	abox->max.y = boxes[whichone].max.y - boxes[whichone].min.y;
	abox->min.z = boxes[whichone].min.z;
	abox->max.z = boxes[whichone].max.z;
}



#include <math.h>
#include <stdlib.h>
#ifdef MINIWIN
#include "miniwin/d3d.h"
#else
#include <d3d.h>
#endif
#include "d3dmacs.h"
#include "rmdemo.h"
#include <stdio.h>
#include "mdtex.h"

//Liou qinghua add
//D3DTEXTUREHANDLE hTex[7];

void CleanupBuildingObjects(Building* building)
{
	if (building->eb)
	{
		RELEASE(building->eb);
		RELEASE(building->mat);
	   building->eb = NULL;
	   building->dev = NULL;
	}
   free(building);
}

extern int VM_W3D;
extern int VM_H3D;
extern int VM_BPP3D;

BOOL CreateBuildingObjects(Building* building, LPDIRECT3DRMDEVICE dev)
{
	D3DEXECUTEBUFFERDESC desc;
	D3DEXECUTEDATA data;
	LPDIRECT3D lpD3D = NULL;
	LPDIRECT3DDEVICE lpD3DDev = NULL;
	LPDIRECT3DMATERIAL mat = NULL;
	LPDIRECT3DEXECUTEBUFFER eb = NULL;
	D3DMATERIALHANDLE hMat;
	D3DMATERIAL orange;
	void* p;
	LPVOID lpBufStart, lpInsStart;
	EbInfo *ebInfo;

	DWORD vsize, tsize, size;
	static int count = 0;
	int scount;

	char fileExtension[SEB_COUNT][10] =
	{
		"113.bin",
		"115.bin",
		"120.bin",
		"66_.bin",
		"66_.bin",
		"66_.bin"
	};

	// To load .x file.
//	LPDIRECT3DRMMESHBUILDER builder = NULL;
	Handle hSpecificBuildingData=NULL;
	D3DVECTOR *vertices = NULL, *normals = NULL;
	DWORD tcount = 0, vcount = 0, ncount = 0;
	DWORD face_data_size = 0;
	DWORD *face_data = NULL;//, *temp;
	WORD index;

	RELEASE(building->eb);

	scount = count - GEB_COUNT;
	if(count < GEB_COUNT) // If count < GEB_COUNT, create execute buffer for generic building.
	{
		vcount =VCount;
		tcount =TCount;
		vsize = VCount * sizeof(D3DVERTEX);
		tsize = TCount * sizeof(D3DTRIANGLE);
		ebInfo = &GebInfo[count];
	}
	else // Else load specific building, and create execute buffer for it.
	{
		GDPLIST *sgdlist;
		int id[6] = {13, 15, 20, 66, 67, 68};


		hSpecificBuildingData=CreateBinary(ArtLevelName(fileExtension[scount]));
	
//	    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &builder)))
//			return FALSE;

//		if (FAILED(lpD3DRM->lpVtbl->AddSearchPath(lpD3DRM, PATH_X)))
//			return FALSE;

		// Runtime error --- Direct3DRM: D3DRMERR file cannot be opened
//		if (FAILED(builder->lpVtbl->Load(builder, ArtLevelName(filename[scount]),
//			NULL, D3DRMLOAD_FROMFILE, NULL, NULL)))
//		{
//			BYDumpInfo("**********************************");
//			BYDumpInfo("couldn't load file:");
//			BYDumpInfo(ArtLevelName(filename[scount]));
//
//			BYDumpInfo("**********************************");
//
//			return FALSE;
//		}
//
//		if (FAILED(builder->lpVtbl->GetVertices(builder,
//			&vcount, NULL, &ncount, NULL,
//			&face_data_size, NULL)))
//			return FALSE;
	
	

		vsize = GetVCount(hSpecificBuildingData,0);
		tsize = GetTCount(hSpecificBuildingData,0);
	
		vcount = vsize/sizeof(D3DVERTEX);
		tcount = tsize/sizeof(D3DTRIANGLE);
//		tcount = builder->lpVtbl->GetFaceCount(builder);
//		vsize = vcount * sizeof(D3DVERTEX);
//		tsize = tcount * sizeof(D3DTRIANGLE);
		ebInfo = &SebInfo[scount];

		sgdlist = malloc(sizeof(GDPLIST));
		sgdlist->vc = vcount;
		sgdlist->tc = tcount;
//		builder->lpVtbl->GetBox(builder, &boxes[scount]);
		kevin.bldg_rsrcs[scount + 1].displist = specificdlists[scount] = sgdlist;
		kevin.bldg_rsrcs[scount + 1].bldg_id = id[scount];
	}

	/*
	//LS's code:
	size = vsize + tsize +
  		9 * sizeof(D3DINSTRUCTION) + 7 * sizeof(D3DSTATE) +
		sizeof(D3DSTATUS) + sizeof(D3DPROCESSVERTICES);
	*/
	//Lgh added.
	size = vsize + tsize +
  		10 * sizeof(D3DINSTRUCTION) + 15 * sizeof(D3DSTATE) +
		sizeof(D3DSTATUS) + sizeof(D3DPROCESSVERTICES);
	if (!count) GSize = size;

	dev->lpVtbl->GetDirect3DDevice(dev, &lpD3DDev);
	if (!lpD3DDev)
	goto generic_error;
	if (FAILED(lpD3DDev->lpVtbl->GetDirect3D(lpD3DDev, &lpD3D)))
	goto generic_error;

	desc.dwSize = sizeof(desc);
	desc.dwFlags = D3DDEB_BUFSIZE | D3DDEB_CAPS;
	desc.dwBufferSize = size;
  	desc.dwCaps = D3DDEBCAPS_SYSTEMMEMORY;

	if (FAILED(lpD3DDev->lpVtbl->CreateExecuteBuffer(lpD3DDev, &desc, &eb, NULL)))
	goto generic_error;

	if (FAILED(lpD3D->lpVtbl->CreateMaterial(lpD3D, &mat, NULL)))
	goto generic_error;
	if (FAILED(mat->lpVtbl->GetHandle(mat, lpD3DDev, &hMat)))
	goto generic_error;

	memset(&orange, 0, sizeof(orange));
	orange.dwSize = sizeof(orange);
	orange.diffuse.r = D3DVAL(1.0);
	orange.diffuse.g = D3DVAL(1.0);
	orange.diffuse.b = D3DVAL(1.0);
	orange.ambient.r = D3DVAL(1.0);
	orange.ambient.g = D3DVAL(1.0);
	orange.ambient.b = D3DVAL(1.0);
	orange.dwRampSize = 1;
	orange.hTexture = ebInfo->hTex;

	if (FAILED(mat->lpVtbl->SetMaterial(mat, &orange)))
	goto generic_error;

	if (FAILED(eb->lpVtbl->Lock(eb, &desc)))
	goto generic_error;

	lpBufStart = desc.lpData;
	p = (void*) ((char*) desc.lpData);
	memset(p, 0, size);

	// Adding by Liou Song.
	ebInfo->v = p;
//	memcpy(p, GVertices, VCount * sizeof(D3DVERTEX));

	p = (void*) ((char*) desc.lpData + vsize);

	lpInsStart = p;

	OP_STATE_LIGHT(1, p);
	STATE_DATA(D3DLIGHTSTATE_MATERIAL, hMat, p);

	OP_SET_STATUS(D3DSETSTATUS_ALL, D3DSTATUS_DEFAULT, 2048, 2048, 0, 0, p);

	if ((VM_BPP3D == 8))
	{
	   OP_PROCESS_VERTICES(1, p);
	   PROCESSVERTICES_DATA(D3DPROCESSVERTICES_TRANSFORM, 0, vcount, p);
   }
   else
   {
	   OP_PROCESS_VERTICES(1, p);
	   PROCESSVERTICES_DATA(D3DPROCESSVERTICES_TRANSFORMLIGHT, 0, vcount, p);
   }
	OP_STATE_RENDER(1, p);
	STATE_DATA(D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT, p);

  	OP_STATE_RENDER(6, p);
	STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE, orange.hTexture, p);	//Liou qinghua
	STATE_DATA(D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE, p);	//Spudde
	STATE_DATA(D3DRENDERSTATE_WRAPV, FALSE, p);
	STATE_DATA(D3DRENDERSTATE_WRAPU, FALSE, p);
	STATE_DATA(D3DRENDERSTATE_TEXTUREMAG, d3dapprs.TextureFilter, p);
	STATE_DATA(D3DRENDERSTATE_TEXTUREMIN, d3dapprs.TextureFilter, p);

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
		STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE, TRUE, p);
		STATE_DATA(D3DRENDERSTATE_ZENABLE, TRUE, p);

/*
 * Make sure that the triangle data (not OP) will be QWORD aligned
 */

	if (QWORD_ALIGNED(p)) 
	{
		OP_NOP(p);
	}

	OP_TRIANGLE_LIST((WORD)tcount, p);

	// Adding by Liou Song.
	ebInfo->t = p;
//	memcpy(p, GTriangles, TCount * sizeof(D3DTRIANGLE));

	p = (void*) ((char*)p + tsize);

	OP_EXIT(p);

//	if (FAILED(eb->lpVtbl->Unlock(eb)))
	//	goto generic_error;

	data.dwSize = sizeof(data);
	data.dwVertexOffset = 0;
	data.dwVertexCount = vcount;
	data.dwInstructionOffset = vcount * sizeof(D3DVERTEX);
	data.dwInstructionLength = (ULONG) ((char *)p - (char *)lpInsStart);
//	data.dwHVertexOffset = 0;
	if (FAILED(eb->lpVtbl->SetExecuteData(eb, &data)))
	goto generic_error;

	ebInfo->eb = eb;

	building->eb = eb;
	building->mat = mat;
	building->dev = dev;
//	if (FAILED(dev->lpVtbl->AddDestroyCallback(dev, CleanupBuildingObjects, building)))
//	goto generic_error;

	RELEASE(lpD3DDev);
	RELEASE(lpD3D);

	// Adding by Liou Song.
	if(count >= GEB_COUNT) // If is specific
	{
//		vertices   = calloc(vcount, sizeof(D3DVECTOR));
//		normals    = calloc(ncount, sizeof(D3DVECTOR));
//		face_data  = calloc(face_data_size, sizeof(DWORD));
//		GVertices  = calloc(gdlist.vc, sizeof(D3DVERTEX));
//		GTriangles = calloc(gdlist.tc, sizeof(D3DTRIANGLE));

//		if (FAILED(builder->lpVtbl->GetVertices(builder,
//			&vcount, vertices, &ncount, normals,
//			&face_data_size, face_data)))
//			return FALSE;
//
		LoadVertex(hSpecificBuildingData,0,ebInfo->v);
		boxes[scount].min.x = RLVal(4000000000.0);
		boxes[scount].max.x = RLVal(-4000000000.0);
		boxes[scount].min.y = RLVal(4000000000.0);
		boxes[scount].max.y = RLVal(-4000000000.0);
		boxes[scount].min.z = RLVal(4000000000.0);
		boxes[scount].max.z = RLVal(-4000000000.0);
		for (index = 0; index < vcount; index++)
		{
			boxes[scount].min.x = MIN(boxes[scount].min.x,ebInfo->v[index].x);
			boxes[scount].max.x = MAX(boxes[scount].max.x,ebInfo->v[index].x);
			boxes[scount].min.y = MIN(boxes[scount].min.y,ebInfo->v[index].y);
			boxes[scount].max.y = MAX(boxes[scount].max.y,ebInfo->v[index].y);
			boxes[scount].min.z = MIN(boxes[scount].min.z,ebInfo->v[index].z);
			boxes[scount].max.z = MAX(boxes[scount].max.z,ebInfo->v[index].z);
//			ebInfo->v[index].x  = vertices[index].x;
//			ebInfo->v[index].y  = vertices[index].y - boxes[scount].min.y;
//			ebInfo->v[index].z  = vertices[index].z;
//			ebInfo->v[index].nx = normals[index].x;
//			ebInfo->v[index].ny = normals[index].y;
//			ebInfo->v[index].nz = normals[index].z;
//			builder->lpVtbl->GetTextureCoordinates(builder, index,
//				&ebInfo->v[index].tu, &ebInfo->v[index].tv);
		}
		for (index = 0; index < vcount; index++)
		{
			ebInfo->v[index].y  -= boxes[scount].min.y;
		}
		LoadTriangle(hSpecificBuildingData,0,ebInfo->t);

//
//		temp = face_data;
//		for (index = 0; index < tcount; index++)
//		{
//			if ((WORD)(*temp++) != 3)
//			{
//				return FALSE;
//			}
//
//			ebInfo->t[index].v1     = (WORD)(*temp++);
//			temp++;
//			ebInfo->t[index].v2     = (WORD)(*temp++);
//			temp++;
//			ebInfo->t[index].v3     = (WORD)(*temp++);
//			temp++;
//			ebInfo->t[index].wFlags = D3DTRIFLAG_EDGEENABLETRIANGLE; 
//		}

//
//		free(face_data);
//		free(normals);
//		free(vertices);
//
//	    RELEASE(builder);
		DeleteBinary(hSpecificBuildingData);
	}
	else
	{
//		memcpy(ebInfo[count].v, GVertices, VCount * sizeof(D3DVERTEX));
//		memcpy(ebInfo[count].t, GTriangles, TCount * sizeof(D3DTRIANGLE));
//		PlaceTriangles();	
//		PlaceVertices();
		if (count < 6) GebFill(count);
		if (count > 2)
		{
			int i;
			for (i = 0; i < (int)vcount; i++)
			{
				ebInfo->v[i].y = RLVal((rand() & 0xff ) / 1024.0);
			}
		}
		if (count == (GEB_COUNT - 1)) InfoFree();
	}
	count++;
	if (count == GEB_COUNT + SEB_COUNT)
		count = 0;

	if (FAILED(eb->lpVtbl->Unlock(eb)))
		goto generic_error;

	return TRUE;
	generic_error:
	RELEASE(lpD3D);
	RELEASE(lpD3DDev);
	RELEASE(mat);
	RELEASE(eb);
	return FALSE;
}


BOOL RenderBuilding(Building* building, LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view)
{
//	D3DVERTEX* v;
//	D3DEXECUTEBUFFERDESC desc;
	D3DEXECUTEDATA data;
	LPDIRECT3DDEVICE lpD3DDev = NULL;
	LPDIRECT3DVIEWPORT lpD3DView = NULL;
	HRESULT rval;

	/*
	if (building->dev != dev) {
	if (!CreateBuildingObjects(building, dev))
	return FALSE;
	}
	*/

	dev->lpVtbl->GetDirect3DDevice(dev, &lpD3DDev);
	view->lpVtbl->GetDirect3DViewport(view, &lpD3DView);
	if (!lpD3DDev || !lpD3DView)
	goto ret_with_error;

//	for (i = 0; i < MAX_BUILDINGS; i++)
//		if (!building->flames[i].valid)
//			InitFlame(&building->flames[i]);

	/*
	desc.dwSize = sizeof(desc);
	desc.dwFlags = 0;

	if (FAILED(building->eb->lpVtbl->Lock(building->eb, &desc)))
	goto ret_with_error;
	v = (D3DVERTEX*) desc.lpData;

	if (FAILED(building->eb->lpVtbl->Unlock(building->eb)))
	goto ret_with_error;
	*/

	if (FAILED(lpD3DDev->lpVtbl->Execute(lpD3DDev, building->eb, lpD3DView, D3DEXECUTE_CLIPPED)))
		goto ret_with_error;

	data.dwSize = sizeof data;
	if (FAILED(building->eb->lpVtbl->GetExecuteData(building->eb, &data)))
	goto ret_with_error;
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
			goto ret_with_error;
	}

	RELEASE(lpD3DDev);
	RELEASE(lpD3DView);
	return TRUE;
	ret_with_error:
	RELEASE(lpD3DDev);
	RELEASE(lpD3DView);
	return FALSE;
}

int BuildingCallback(LPDIRECT3DRMUSERVISUAL uvis,
	void* arg,
	D3DRMUSERVISUALREASON reason,
	LPDIRECT3DRMDEVICE dev,
	LPDIRECT3DRMVIEWPORT view)
{
	Building* building = (Building*) arg;

/*	if (building->dev != dev) {
		if (!CreateBuildingObjects(building, dev))
			return FALSE;
	}*/

	if (reason == D3DRMUSERVISUAL_CANSEE)
		return TRUE;

	if (reason == D3DRMUSERVISUAL_RENDER)
	{
	if (!RenderBuilding(building, dev, view))
		return DDERR_GENERIC;
	else
		return D3D_OK;
	}

	return 0;
}

void DestroyBuilding(LPDIRECT3DRMOBJECT obj, void* arg)
{
	Building* building = (Building*) arg;

	CleanupBuildingObjects(building);
}

BOOL CreateBuilding(EbInfo *buildingebinfo)
{
	Building* building;
	LPDIRECT3DRMUSERVISUAL uvis = NULL;

	building = (Building*)malloc(sizeof(Building));
	if (!building)
	goto ret_with_error;
	memset(building, 0, sizeof(Building));

	if (!CreateBuildingObjects(building, Wdevice))
		goto ret_with_error;

	if (FAILED(lpD3DRM->lpVtbl->CreateUserVisual(lpD3DRM, BuildingCallback, (void*) building, &uvis)))
	goto ret_with_error;
	//if (FAILED(uvis->lpVtbl->AddDestroyCallback(uvis, DestroyBuilding, (void*) building)))
	//goto ret_with_error;   

	buildingebinfo->uvis = uvis;
   buildingebinfo->building = building;
   
   return TRUE;
	ret_with_error:
	if (building)
	free(building);
	RELEASE(uvis);
	return FALSE;
}

LPTEXTURESTRUCT LSCreateTexture(LPDIRECT3DRMDEVICE dev, LPSTR ppmfile)
{
	LPTEXTURESTRUCT lpTexStruct;
	lpTexStruct = (TEXTURESTRUCT*)malloc(sizeof(TEXTURESTRUCT));
	memset (lpTexStruct, 0, sizeof(TEXTURESTRUCT));
	MyLoadTexture(dev, ppmfile, lpTexStruct, 0);
	return lpTexStruct;
}


BOOL
BuildTestScene(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
   LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera)
{
//	D3DRMRENDERQUALITY quality = D3DRMRENDER_GOURAUD;
//	LPDIRECT3DRMFRAME lights = NULL;
	LPDIRECT3DRMFRAME frame = NULL;
//	LPDIRECT3DRMLIGHT light1 = NULL;
//	LPDIRECT3DRMLIGHT light2 = NULL;
	LPDIRECT3DRMUSERVISUAL uvis = NULL;
	int i;
	
	//Liou qinghua add
	//LPTEXTURESTRUCT lpTextureStruct;	//Liou qinghua

//	if (FAILED(lpD3DRM->lpVtbl->AddSearchPath(lpD3DRM, PATH_PPM))) // Adding by Liou Song.
//		return FALSE;
	
	lpTextureStruct[0] = LSCreateTexture(dev, ConstructLevelName("105.bmp"));
	GebInfo[0].hTex = lpTextureStruct[0]->hTex;
	GebInfo[1].hTex = lpTextureStruct[0]->hTex;
	GebInfo[2].hTex = lpTextureStruct[0]->hTex;
	GebInfo[3].hTex = lpTextureStruct[0]->hTex;
	GebInfo[4].hTex = lpTextureStruct[0]->hTex;
	GebInfo[5].hTex = lpTextureStruct[0]->hTex;
	GebInfo[6].hTex = lpTextureStruct[0]->hTex;
	GebInfo[7].hTex = lpTextureStruct[0]->hTex;
	GebInfo[8].hTex = lpTextureStruct[0]->hTex;
	GebInfo[9].hTex = lpTextureStruct[0]->hTex;
	GebInfo[10].hTex = lpTextureStruct[0]->hTex;
	GebInfo[11].hTex = lpTextureStruct[0]->hTex;

	lpTextureStruct[1] = LSCreateTexture(dev, ConstructLevelName("106.bmp"));
	SebInfo[0].hTex = lpTextureStruct[1]->hTex;
	SebInfo[1].hTex = lpTextureStruct[1]->hTex;
	SebInfo[2].hTex = lpTextureStruct[1]->hTex;
	lpTextureStruct[2] = LSCreateTexture(dev, ConstructLevelName("egg.bmp"));
	SebInfo[3].hTex = lpTextureStruct[2]->hTex;
	SebInfo[4].hTex = lpTextureStruct[2]->hTex;
	SebInfo[5].hTex = lpTextureStruct[2]->hTex;

/*	for (i = 0; i < 7; i++)
	{
		lpTextureStruct = LSCreateTexture(dev, ppmfile[i]);
		hTex[i] = lpTextureStruct->hTex;
	}*/

	// Adding by Liou Song.
//	BuildingInfo();
#ifdef LSDEBUG
	OutPut();
#endif LSDEBUG

view = view;                /* not used */

/*	if (FAILED(dev->lpVtbl->SetQuality(dev, quality)))
		goto generic_error;
*/

/*
 * create a frame within the scene
 */
	if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &frame)))
		goto generic_error;

/*
 * add the building into the frame
 */
	/*for (i = 0; i < GEB_COUNT + SEB_COUNT; i++)
	{ // Adding by Liou Song.
		uvis = CreateBuilding();
		if (!uvis)
			goto generic_error;
		if (FAILED(frame->lpVtbl->AddVisual(frame, (LPDIRECT3DRMVISUAL)uvis)))
		break;
	}*/

	for (i = 0; i < GEB_COUNT; i++)
	{ // Adding by Liou Song.
		LPDIRECT3DRMFRAME frame;
      
      if (!CreateBuilding(&(GebInfo[i])))
         goto generic_error;

		uvis = GebInfo[i].uvis;
		if (!uvis)
			goto generic_error;

		lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, behindthescene, &GebInfo[i].frame);
		frame = GebInfo[i].frame;
		if (FAILED(frame->lpVtbl->AddVisual(frame, (LPDIRECT3DRMVISUAL)uvis)))
			goto generic_error;
	}

	for (i = 0; i < SEB_COUNT; i++)
	{ // Adding by Liou Song.
		LPDIRECT3DRMFRAME frame;

      if (!CreateBuilding(&(SebInfo[i])))
         goto generic_error;
		uvis = SebInfo[i].uvis;
		if (!uvis)
			goto generic_error;

		lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, behindthescene, &SebInfo[i].frame);
		frame = SebInfo[i].frame;
		if (FAILED(frame->lpVtbl->AddVisual(frame, (LPDIRECT3DRMVISUAL)uvis)))
			goto generic_error;
	}

	InitConflagration();
	AddBuilding(behindthescene);

	/*for (i = 0; i < GEB_COUNT; i++)
	{
		LPDIRECT3DRMFRAME frame;
		int x = (i - (GEB_COUNT - 1) / 2) * 10;

		frame = GebInfo[i].frame;
	//	scene->lpVtbl->AddChild(scene, frame);
		frame->lpVtbl->SetPosition(frame, scene, x, 4, -x);
	}

	for (i = 0; i < SEB_COUNT; i++)
	{
		LPDIRECT3DRMFRAME frame;
		int x = (i - (SEB_COUNT - 1) / 2) * 10;

		frame = SebInfo[i].frame;
	//	scene->lpVtbl->AddChild(scene, frame);
		frame->lpVtbl->SetPosition(frame, scene, x, -4, x);
	}*/

/*
 * set up the frames position, orientation and rotation
 */
/*    if (FAILED(camera->lpVtbl->SetPosition(camera, scene, D3DVAL(0), D3DVAL(0.5), -D3DVAL(10))))
goto generic_error;
if(FAILED(camera->lpVtbl->SetOrientation(camera, scene, D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(0),
   D3DVAL(1), D3DVAL(0))))
   goto generic_error;
*/
/*	if(FAILED(frame->lpVtbl->SetRotation(frame, scene, D3DVAL(0), D3DVAL(1), D3DVAL(0),
						D3DVAL(0.02))))
						goto generic_error;*/

	RELEASE(uvis);
	RELEASE(frame);
//	RELEASE(lights);
//	RELEASE(light1);
//	RELEASE(light2);
	return TRUE;
	generic_error:
//	RELEASE(lights);
	RELEASE(frame);
//	RELEASE(light1);
//	RELEASE(light2);
	RELEASE(uvis);
	return FALSE;
}

extern char XafPath[];

lvl_bldg_rsrcs *BuildingInfo(void)
{
//	LPDIRECT3DRMMESHBUILDER builder = NULL;
	Handle hGenericBuildingData=NULL;
	char filename[MAX_PATH];

	strcpy(filename, XafPath);
	strcat(filename, "\\box.bin");

	
	
	
//	D3DVECTOR *vertices = NULL, *normals = NULL;
//	DWORD fcount = 0, vcount = 0, ncount = 0;
//	DWORD face_data_size = 0;
//	DWORD *face_data = NULL, *p;
//	WORD index;

//	if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &builder)))
//	{
//		BYDumpInfo("******************");
//		BYDumpInfo("Couldn't create mesh for generic building.");
//		BYDumpInfo("******************");
//
//		return FALSE;
//	}

//	if (FAILED(lpD3DRM->lpVtbl->AddSearchPath(lpD3DRM, PATH_X)))
//		return FALSE;

//	if (FAILED(builder->lpVtbl->Load(builder, PathName("Box.X"), NULL, D3DRMLOAD_FROMFILE, NULL, NULL)))
//	{
//		BYDumpInfo("******************");
//		BYDumpInfo("Couldn't load file:");
//		BYDumpInfo(PathName("Box.X"));
//		BYDumpInfo("******************");
//		return FALSE;
//	}

//	fcount = builder->lpVtbl->GetFaceCount(builder);
//
//	if (FAILED(builder->lpVtbl->GetVertices(builder,
//		&vcount, NULL, &ncount, NULL,
//		&face_data_size, NULL)))
//	{
//		BYDumpInfo("******************");
//		BYDumpInfo("Couldn't create mesh for generic building.");
//		BYDumpInfo("******************");
//		return FALSE;
//	}

//	vertices   = calloc(vcount, sizeof(D3DVECTOR));
//	normals    = calloc(ncount, sizeof(D3DVECTOR));
//	face_data  = calloc(face_data_size, sizeof(DWORD));

//	GVertices  = calloc(vcount, sizeof(D3DVERTEX));
//	GTriangles = calloc(fcount, sizeof(D3DTRIANGLE));
//
//	if (FAILED(builder->lpVtbl->GetVertices(builder,
//		&vcount, vertices, &ncount, normals,
//		&face_data_size, face_data)))
//	{
//		BYDumpInfo("******************");
//		BYDumpInfo("Couldn't create mesh for generic building.");
//		BYDumpInfo("******************");
//		return FALSE;
//	}
//
//	for (index = 0; index < vcount; index++)
//	{
//		GVertices[index].x  = vertices[index].x;
//		GVertices[index].y  = vertices[index].y;
//		GVertices[index].z  = vertices[index].z;
//		GVertices[index].nx = normals[index].x;
//		GVertices[index].ny = normals[index].y;
//		GVertices[index].nz = normals[index].z;
//		builder->lpVtbl->GetTextureCoordinates(builder, index,
//			&GVertices[index].tu, &GVertices[index].tv);
//	}
//
//	p = face_data;
//	for (index = 0; index < fcount; index++)
//	{
///		if ((WORD)(*p++) != 3)
//		{
//			BYDumpInfo("******************");
//			BYDumpInfo("Couldn't create mesh for generic building.");
//			BYDumpInfo("******************");
//			return FALSE;
//		}
//
//		GTriangles[index].v1     = (WORD)(*p++);
//		p++;
//		GTriangles[index].v2     = (WORD)(*p++);
//		p++;
//		GTriangles[index].v3     = (WORD)(*p++);
//		p++;
//		GTriangles[index].wFlags = D3DTRIFLAG_EDGEENABLETRIANGLE; 
//	}
//
//	free(face_data);
//	free(normals);
//	free(vertices);
//
//	TCount = fcount;
//	VCount = vcount;
//	NCount = ncount;
//
//	builder->lpVtbl->Release(builder);
//	RELEASE(builder);

//	gdlist.vc = vcount;
//	gdlist.tc = fcount;

	hGenericBuildingData=CreateBinary(filename);
	
	VCount = GetVCount(hGenericBuildingData,0)/sizeof(D3DVERTEX);
	TCount = GetTCount(hGenericBuildingData,0)/sizeof(D3DTRIANGLE);
	gdlist.vc = VCount;
	gdlist.tc = TCount;

	GVertices  = calloc(gdlist.vc, sizeof(D3DVERTEX));
	GTriangles = calloc(gdlist.tc, sizeof(D3DTRIANGLE));

	LoadVertex(hGenericBuildingData,0,GVertices);
	LoadTriangle(hGenericBuildingData,0,GTriangles);
	
	kevin.bldg_rsrcs[0].displist = (GDPLIST *) &gdlist;
	kevin.bldg_rsrcs[0].bldg_id  = -1;
	kevin.count = 6;



	return (&kevin);
}


BOOL GebFill(int count)
{
	WORD i;
	float tu[GEB_COUNT] = {0.5, 0.0, 0.5};
	float tv[GEB_COUNT] = {0.0, 0.5, 0.5};
	EbInfo *ebInfo;

	ebInfo = &GebInfo[count];
	memcpy(ebInfo->v, GVertices, VCount * sizeof(D3DVERTEX));
	memcpy(ebInfo->t, GTriangles, TCount * sizeof(D3DTRIANGLE));
	for (i = 0; i < VCount - 12; i++)
	{
		ebInfo->v[i].tu += tu[count];
		ebInfo->v[i].tv += tv[count];
	}

	return TRUE;
}

BOOL AddBuilding(LPDIRECT3DRMFRAME scene)
{
	LPDIRECT3DRMFRAME frame;
	LPDIRECT3DRMUSERVISUAL uvis;
	int i, j, count;
	int num;
	building *bp;
	building_area *which_bldg;

	which_bldg = which1_bldg;
	for (i = 0; i < 256; i++)
	{
		count = which_bldg[i].count;
		bp = which_bldg[i].building_ptr;
		for (j = 0; j < count; j++)
		{
			int index;

			num = bp->building_num;
			if (num == -1)
			{

				if (bp->tv == 0.0)
					index = 0;
				else if (bp->tu == 0.0)
					index = 1;
				else
					index = 2;
  				// If the building is destroied.
  				if (bp->cur_damage >= bp->max_damage)
  					index += 3;
				uvis = GebInfo[index].uvis;
			}
			else
			{
  			/*	static int lastlevel = -1;
  				static int flag[6] = {0, 0, 0, 0, 0, 0};*/
				D3DRMBOX box; // To revise specific building box

  				GetSpecificBox(num, &box);
				bp->building.min.x += box.min.x;
				bp->building.min.y += box.min.y;
				bp->building.min.z += box.min.z;
				bp->building.max.x += box.max.x;
				bp->building.max.y += box.max.y;
  				bp->building.max.z += box.max.z;

				switch (num)
				{
					case 13:
						index = 0;
						break;
					case 15:
						index = 1;
						break;
					case 20:
						index = 2;
						break;
					case 66:
						index = 3;
						break;
					case 67:
						index = 4;
						break;
					case 68:
						index = 5;
						break;
				}

  			/*	if (lastlevel != g_level)
				{
					memset(flag, 0, 6 * sizeof(int));
					lastlevel = g_level;
				}

				if (!flag[index])
				{
					GetSpecificBox(num, &box);
					bp->building.min.x += box.min.x;
					bp->building.min.y += box.min.y;
					bp->building.min.z += box.min.z;
					bp->building.max.x += box.max.x;
					bp->building.max.y += box.max.y;
					bp->building.max.z += box.max.z;
					flag[index] = 1;
  				}*/

				uvis = SebInfo[index].uvis;
				bp->displist = specificdlists[index];
  				if (bp->cur_damage >= bp->max_damage)
  				{
  					int i;
  					D3DEXECUTEBUFFERDESC desc;
  
  					desc.dwSize = sizeof(desc);
  					desc.dwFlags = 0;
  					SebInfo[index].eb->lpVtbl->Lock(SebInfo[index].eb, &desc);
  					SebInfo[index].v = (void*) ((char*) desc.lpData);
  					for (i = 0; i < bp->displist->vc; i++)
  					{
  						SebInfo[index].v[i].y = RLVal((rand() & 0xff ) / 1024.0);
  					}
  					SebInfo[index].eb->lpVtbl->Unlock(SebInfo[index].eb);
  				}
			}
			frame = bp->rlframe;
		//	frame->lpVtbl->AddScale(frame, D3DRMCOMBINE_REPLACE, 1, 1, 1);
			scene->lpVtbl->AddChild(scene, frame);
			if (FAILED(frame->lpVtbl->AddVisual(frame, (LPDIRECT3DRMVISUAL)uvis)))
				return FALSE;
		//	frame->lpVtbl->SetPosition(frame, scene, bp->x_world, bp->y_world, bp->z_world);
			bp++;
		}
	}
	return TRUE;
}


BOOL DelBuilding(void)
{
	extern short level_flag[];
	LPDIRECT3DRMFRAME frame;
	int i, j;
	building *bp;
	building_area *which_bldg;
/*	LPDIRECT3DRMVISUALARRAY va;
	LPDIRECT3DRMVISUAL visual;
	LPDIRECT3DRMUSERVISUAL uvis;

	which_bldg = which1_bldg;
	for (i = 0; i < 256; i++)
	{
		int count;

		count = which_bldg[i].count;
		bp = which_bldg[i].building_ptr;
		for (j = 0; j < count; j++)
		{
			frame = bp->rlframe;
			frame->lpVtbl->GetVisuals(frame, &va);
			va->lpVtbl->GetElement(va, 0l, &visual);
			frame->lpVtbl->DeleteVisual(frame, visual);
			frame->lpVtbl->Release(frame);
			bp++;
		}
	}
	for (i = 0; i < GEB_COUNT; i++)
	{
		uvis = GebInfo[i].uvis;
		uvis->lpVtbl->Release(uvis);

	}
	for (i = 0; i < SEB_COUNT; i++)
	{
		uvis = SebInfo[i].uvis;
		uvis->lpVtbl->Release(uvis);
	}*/
	which_bldg = which1_bldg;
	for (i = 0; i < 256; i++)
	{
		int count;

		count = which_bldg[i].count;
		bp = which_bldg[i].building_ptr;
		for (j = 0; j < count; j++)
		{
			frame = bp->rlframe;
			MDFreeD3DFrame(frame);
			bp++;
		}
	}

	for (i = 0; i < GEB_COUNT; i++)
	{
      CleanupBuildingObjects(GebInfo[i].building);
		MDFreeD3DFrame(GebInfo[i].frame);
	}

	for (i = 0; i < SEB_COUNT; i++)
	{
      CleanupBuildingObjects(SebInfo[i].building);
		MDFreeD3DFrame(SebInfo[i].frame);
      free(specificdlists[i]);
	}

	for (i = 0; i < 3; i++)
	{
		ReleaseOneTexture(lpTextureStruct[i]);
      free(lpTextureStruct[i]);
	}

	//for (i = 0; i < 7; i++)
	//	level_flag[i] = 0;

	return TRUE;
}

void InfoFree(void)
{
	free(GVertices);
	free(GTriangles);
}

#ifdef LSDEBUG
void OutPut(void)
{
	FILE *fp;
	DWORD i;

	fp = fopen("out.txt", "wt");

	for (i = 0; i < VCount; i++)
	{
		fprintf(fp, "%f,%f,%f\n", GVertices[i].x, GVertices[i].y, GVertices[i].z);
	}

	fprintf(fp, "\n");

	for (i = 0; i < TCount; i++)
	{
		fprintf(fp, "%lu,%lu,%lu\n", GTriangles[i].v1, GTriangles[i].v2, GTriangles[i].v3);
	}

	fclose(fp);
}
#endif LSDEBUG

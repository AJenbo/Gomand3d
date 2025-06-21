/*==========================================================================
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
$Header:   H:/pvcs/pvcsproj/gomand3d.prj/LANDSCAP.C_V   1.21   27 Mar 1997 19:33:28   BRUCE  $

$Log:   H:/pvcs/pvcsproj/gomand3d.prj/LANDSCAP.C_V  $
 * 
 *    Rev 1.21   27 Mar 1997 19:33:28   BRUCE
 * moved call to edge of world sound into
 * this module, and made it looping rather
 * than called multiple times.
 * 
 *    Rev 1.20   21 Mar 1997 15:35:06   JEREMIAH
 * Disabled texture blending for the landscape.
 * 
 * 
 *    Rev 1.19   Mar 20 1997 17:13:26   JEREMIAH
 * Set zenable and zwriteenable to TRUE.
 * 
 *    Rev 1.18   07 Mar 1997 13:53:22   BRUCE
 * Detail 5 land is what used to be detail 4
 * land.  Detail 4 land is what used to be 
 * detail 3 land.
 * 
 *    Rev 1.17   06 Mar 1997 14:49:20   JEREMIAH
 * Optimized execute buffers in 8-bit by 
 * changing from _TRANSFORMLIGHT to 
 * _TRANSFORM.
 * 
 * Turned ground shading on.
 * 
 *    Rev 1.16   24 Feb 1997 15:17:02   JEREMIAH
 * Debranched 1.15.1.0 to 1.16.
 * 
 *    Rev 1.15.1.0   24 Feb 1997 15:05:40   JEREMIAH
 * Shrunk the size of the landbox for the 
 * trainer level.
 * 
 *    Rev 1.15   20 Feb 1997 11:21:02   JEREMIAH
 * Fixed the disappearing Edge of World
 * texture.
 * 
 *    Rev 1.14   14 Feb 1997 19:50:24   BRUCE
 * changed level to GameStates.CurrentLevel
 * changed land_level to GameStates.CurrentLevel
 * 
 * 
 *    Rev 1.13   07 Feb 1997 09:02:02   BRUCE
 * set ground shading calculations inside
 * #ifdef GroundShading
 * turned on 
 * fog, persp correct, gouraud, bilinear filtering
 * on accelerated cards.
 * 
 *    Rev 1.12   06 Feb 1997 16:10:54   JEREMIAH
 * Created correct surface normals for
 * landscape, but commented the change
 * out for now.
 * 
 *    Rev 1.11   04 Feb 1997 16:34:04   JEREMIAH
 * Skipped past revision 1.10.
 * Beta 1.02A seems to cause a fatal crash
 * that occurs at QueryInterface when loading
 * the generic building texture.  Reason 
 * unknown.
 * 
 * 
 *    Rev 1.9   06 Jan 1997 16:27:48   JEREMIAH
 * Reduced rampsize on all materials to 1
 * to eliminate palettizing pause bug.
 * 
 *    Rev 1.8   18 Dec 1996 19:31:28   BRUCE
 * integrated faster landscape with slower 
 * landscape (removed ISC speedups to fix
 * water on land bug.)
 * 
 *    Rev 1.6   12 Dec 1996 12:17:44   JEREMIAH
 * As identified by Tim, v1.5 of landscap.c
 * created bugs with the sealevel and the
 * building height.  This version is reverting
 * to v1.4.
 * 
 *    Rev 1.4   15 Nov 1996 14:47:10   JEREMIAH
 * Changed by Liou GuoHong (ITC).  
 * Implemented copy mode for 8-bit rendering.
 * 
 *    Rev 1.3   08 Nov 1996 16:11:30   JEREMIAH
 * Merge of 1.1.1.0 and 1.2.
 *
 ***************************************************************************/
#include <math.h>
#include <stdlib.h>
#include <d3d.h>
#include "d3dmacs.h"
#include "rmdemo.h"
#include "rmfull.h"
#include "landscap.h"
#include "mdtex.h"
#include "gosys.h"
#include "clutter.h"
#include "spritlib.h"
#include "building.h"
#include "psystem.h"

#include "rl2d3d.h"
#include "global.h"
#include "d3dappi.h"
#include "ybsnd.h"
#define CUINTSIZE 4

extern char* D3DAppErrorToString(HRESULT error);
extern void D3DAppISetErrorString( LPSTR fmt, ... );

extern LPDIRECT3DRMFRAME Wscene, Wcamera;
extern LPDIRECT3DRMDEVICE Wdevice;
extern LPDIRECT3DRMVIEWPORT Wview;
extern unsigned char detail;
//extern int level;
extern RLFrame Robotframe,monstframe;
extern RLFrame goodguyframe;

#define GroundShading

D3DRMBOX landbox;
D3DVALUE sealevel;
D3DVALUE SpuddeMonstersAltitudeWhenSwimming;
D3DVALUE SwimmingDepth=D3DVAL(0.25);
D3DVALUE landscale = D3DVAL(16.0);
//int land_level=-1;
int cuint=CUINTSIZE;
int cpx, cpz, cpxs, cpzs;
D3DVALUE texturecutoffs[4];
cGlobalstype cGlobals;
RLFrame cloudframe, edgeframe;

Psystem *clouds=NULL;
Psystem *edgeoworld=NULL;

void init_iland(LPDIRECT3DRMFRAME camera, LPDIRECT3DRMFRAME scene);
void CRight(int num);
void CLeft(int num);
void CForward(int num);
void CBackward(int num);
void ilandkontrol(LPDIRECT3DRMFRAME camera, LPVOID arg, D3DVALUE delta);
void ApplyGroundTextures(int x1, int z1, int x2, int z2);
void RotateFlipAndApplyTile(int whichway, int flip, int x1, int z1, int x2, int z2, D3DVALUE bu, D3DVALUE bv);
void PlaceCloud(int cloudID);
void UpdateClouds();

LPDIRECT3DRMFRAME	LandFrame = NULL;

LPDIRECT3DEXECUTEBUFFER landeb[9];
ULONG TriOffset[9];
int xmin[9], xmax[9], zmin[9], zmax[9];
int blocknum;
int b_num[9];

static Land *MyLand = NULL;
 
void AssignGroundTextures(PALETTEENTRY* pal)
// assign the different color's offset in the palette table 
{
	int i, texnum;
	BYTE r, g, b;

	texnum = 0;
	r = g = b = (BYTE)256;
	for (i=0;i<4;i++) 
		texturecutoffs[i] = D3DVAL(256.0);

	for (i=0;((i<256) && (texnum<4));i++) 
	{
		if ((r != pal->peRed) || (g != pal->peGreen) || (b != pal->peBlue)) 
		{
			texturecutoffs[texnum] = D3DVAL(i);
			texnum++;
		}
		r = pal->peRed;
		g = pal->peGreen;
		b = pal->peBlue;
		pal++;
	} //end for
	return;
}

void update_joints(int xl, int zl, int x, int z)
// updates the positions of the point clusters for the landscape
// xl, zl represent the array coordinates of the point cluster
// x, z are the altitude bitmap coordinates
{
	cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(xl),TOPOFCLUSTER(zl))].x =
		cGlobals.vertices[VERTEXINDEX(BOTTOMOFCLUSTER(xl),TOPOFCLUSTER(zl))].x = 
		cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(xl),BOTTOMOFCLUSTER(zl))].x = 
		cGlobals.vertices[VERTEXINDEX(BOTTOMOFCLUSTER(xl),BOTTOMOFCLUSTER(zl))].x = D3DVAL(x);

	cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(xl),TOPOFCLUSTER(zl))].z =
		cGlobals.vertices[VERTEXINDEX(BOTTOMOFCLUSTER(xl),TOPOFCLUSTER(zl))].z = 
		cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(xl),BOTTOMOFCLUSTER(zl))].z = 
		cGlobals.vertices[VERTEXINDEX(BOTTOMOFCLUSTER(xl),BOTTOMOFCLUSTER(zl))].z = D3DVAL(z);

	if ((MapHeight(x, z) <= sealevel)) 
	{
		cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(xl),TOPOFCLUSTER(zl))].y =
			cGlobals.vertices[VERTEXINDEX(BOTTOMOFCLUSTER(xl),TOPOFCLUSTER(zl))].y = 
			cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(xl),BOTTOMOFCLUSTER(zl))].y = 
			cGlobals.vertices[VERTEXINDEX(BOTTOMOFCLUSTER(xl),BOTTOMOFCLUSTER(zl))].y = sealevel;
	} 
	else 
	{
		cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(xl),TOPOFCLUSTER(zl))].y =
			cGlobals.vertices[VERTEXINDEX(BOTTOMOFCLUSTER(xl),TOPOFCLUSTER(zl))].y = 
			cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(xl),BOTTOMOFCLUSTER(zl))].y = 
			cGlobals.vertices[VERTEXINDEX(BOTTOMOFCLUSTER(xl),BOTTOMOFCLUSTER(zl))].y = MapHeight(x, z);
	}
	cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(xl),TOPOFCLUSTER(zl))].nx =
		cGlobals.vertices[VERTEXINDEX(BOTTOMOFCLUSTER(xl),TOPOFCLUSTER(zl))].nx = 
		cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(xl),BOTTOMOFCLUSTER(zl))].nx = 
		cGlobals.vertices[VERTEXINDEX(BOTTOMOFCLUSTER(xl),BOTTOMOFCLUSTER(zl))].nx =
#ifndef GroundShading
      D3DVAL(0.0);      // unshaded ground
#else
      (0.25*MapHeight(x-2,z)-0.25*MapHeight(x+2,z));      // proper shading on ground
#endif

	cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(xl),TOPOFCLUSTER(zl))].nz =
		cGlobals.vertices[VERTEXINDEX(BOTTOMOFCLUSTER(xl),TOPOFCLUSTER(zl))].nz = 
		cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(xl),BOTTOMOFCLUSTER(zl))].nz = 
		cGlobals.vertices[VERTEXINDEX(BOTTOMOFCLUSTER(xl),BOTTOMOFCLUSTER(zl))].nz = 
#ifndef GroundShading
      D3DVAL(0.0);      // unshaded ground
#else
      (0.25*MapHeight(x,z-2)-0.25*MapHeight(x,z+2));      // proper shading on ground
#endif

	cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(xl),TOPOFCLUSTER(zl))].ny =
		cGlobals.vertices[VERTEXINDEX(BOTTOMOFCLUSTER(xl),TOPOFCLUSTER(zl))].ny = 
		cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(xl),BOTTOMOFCLUSTER(zl))].ny = 
		cGlobals.vertices[VERTEXINDEX(BOTTOMOFCLUSTER(xl),BOTTOMOFCLUSTER(zl))].ny = D3DVAL(1.0);

}


void update_vertices(int xs, int zs, int x1, int x2, int z1, int z2)
// updates the triangle information for a patch of landscape
// xs and zs the are the array coordinates of a pair of triangles
// x1, x2, z1, z2 represent the point clusters of the corners of 
// a patch of landscap
{
	cGlobals.sections[SECTIONINDEX(xs,zs,0)].v3 =
		VERTEXINDEX(TOPOFCLUSTER(x1),TOPOFCLUSTER(z1));
	cGlobals.sections[SECTIONINDEX(xs,zs,0)].v2 =
		VERTEXINDEX(BOTTOMOFCLUSTER(x2),TOPOFCLUSTER(z1));
	cGlobals.sections[SECTIONINDEX(xs,zs,0)].v1 =
		VERTEXINDEX(BOTTOMOFCLUSTER(x2),BOTTOMOFCLUSTER(z2));
	cGlobals.sections[SECTIONINDEX(xs,zs,0)].wFlags = 
		D3DTRIFLAG_EDGEENABLETRIANGLE; 	

	cGlobals.sections[SECTIONINDEX(xs,zs,1)].v3 =
		VERTEXINDEX(BOTTOMOFCLUSTER(x2),BOTTOMOFCLUSTER(z2));
	cGlobals.sections[SECTIONINDEX(xs,zs,1)].v2 =
		VERTEXINDEX(TOPOFCLUSTER(x1),BOTTOMOFCLUSTER(z2));
	cGlobals.sections[SECTIONINDEX(xs,zs,1)].v1 =
		VERTEXINDEX(TOPOFCLUSTER(x1),TOPOFCLUSTER(z1));
	cGlobals.sections[SECTIONINDEX(xs,zs,1)].wFlags = 
		D3DTRIFLAG_EDGEENABLETRIANGLE; 	

	ApplyGroundTextures(x1, z1, x2, z2);  // apply texture coordinate of 
										  // one patch of landscap
}

void ApplyGroundTextures(int x1, int z1, int x2, int z2)
// calculate the way of texture mapping one patch of landscap,
// and apply texture coordinate of one patch of landscap
// x1, x2, z1, z2 represent the point clusters of the corners of 
// a patch of landscap
{
	int whichtile[4], basetile, transition_level, i;
	D3DVALUE patchheight[4];

	patchheight[0] = landscale*(cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(x1),TOPOFCLUSTER(z1))].y);
	patchheight[1] = landscale*(cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(x2),TOPOFCLUSTER(z1))].y);
	patchheight[2] = landscale*(cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(x1),TOPOFCLUSTER(z2))].y);
	patchheight[3] = landscale*(cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(x2),TOPOFCLUSTER(z2))].y);

	for (i=0;i<4;i++) 
	{
		if (patchheight[0] >= texturecutoffs[i]) whichtile[0] = i;  
		if (patchheight[1] >= texturecutoffs[i]) whichtile[1] = i;  
		if (patchheight[2] >= texturecutoffs[i]) whichtile[2] = i;  
		if (patchheight[3] >= texturecutoffs[i]) whichtile[3] = i;  
	} //end for

	basetile = MIN(whichtile[0], MIN(whichtile[1], MIN(whichtile[2], whichtile[3])));

	if (basetile <= 4) 
	{
		transition_level = (whichtile[0] + whichtile[1] + whichtile[2] + whichtile[3]) - (basetile*4);
		if ((transition_level == 0) || (transition_level >= 4)) 
		{
			if (basetile || GameStates.CurrentLevel<Hawaii) 
			{
				if (!basetile || (rand()&3))
					RotateFlipAndApplyTile(rand()&3, 0, x1, z1, x2, z2, D3DVAL(0.0), D3DVAL(basetile/4.0));
				else
					RotateFlipAndApplyTile(rand()&3, 0, x1, z1, x2, z2, D3DVAL(basetile/4.0), D3DVAL(0.75));
			} 
			else 
				RotateFlipAndApplyTile((rand()&1)<<1, 0, x1, z1, x2, z2, D3DVAL(0.0), D3DVAL(basetile/4.0));
		}

		if (transition_level == 1) 
		{
			if (whichtile[0] > basetile) 
			{
				RotateFlipAndApplyTile(0, 0, x1, z1, x2, z2, D3DVAL(0.25), D3DVAL(basetile/4.0));
			}
			if (whichtile[1] > basetile) 
			{
				RotateFlipAndApplyTile(3, 0, x1, z1, x2, z2, D3DVAL(0.25), D3DVAL(basetile/4.0));
			}
			if (whichtile[2] > basetile) 
			{
				RotateFlipAndApplyTile(1, 0, x1, z1, x2, z2, D3DVAL(0.25), D3DVAL(basetile/4.0));
			}
			if (whichtile[3] > basetile) 
			{
				RotateFlipAndApplyTile(2, 0, x1, z1, x2, z2, D3DVAL(0.25), D3DVAL(basetile/4.0));
			}
		}
		if (transition_level == 2) 
		{
			if ((whichtile[0] == basetile) && (whichtile[1] == basetile))
				RotateFlipAndApplyTile(2, 0, x1, z1, x2, z2, D3DVAL(0.75), D3DVAL(basetile/4.0));
			if ((whichtile[1] == basetile) && (whichtile[3] == basetile))
				RotateFlipAndApplyTile(1, 0, x1, z1, x2, z2, D3DVAL(0.75), D3DVAL(basetile/4.0));
			if ((whichtile[2] == basetile) && (whichtile[0] == basetile))
				RotateFlipAndApplyTile(3, 0, x1, z1, x2, z2, D3DVAL(0.75), D3DVAL(basetile/4.0));
			if ((whichtile[3] == basetile) && (whichtile[2] == basetile))
				RotateFlipAndApplyTile(0, 0, x1, z1, x2, z2, D3DVAL(0.75), D3DVAL(basetile/4.0));
		}
		if (transition_level == 3) 
		{
			if (whichtile[0] == basetile) 
				RotateFlipAndApplyTile(0, 0, x1, z1, x2, z2, D3DVAL(0.5), D3DVAL(basetile/4.0));
			if (whichtile[1] == basetile) 
				RotateFlipAndApplyTile(3, 0, x1, z1, x2, z2, D3DVAL(0.5), D3DVAL(basetile/4.0));
			if (whichtile[2] == basetile) 
				RotateFlipAndApplyTile(1, 0, x1, z1, x2, z2, D3DVAL(0.5), D3DVAL(basetile/4.0));
			if (whichtile[3] == basetile) 
				RotateFlipAndApplyTile(2, 0, x1, z1, x2, z2, D3DVAL(0.5), D3DVAL(basetile/4.0));
		}
	}

	PlantTree((int)cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(x1),TOPOFCLUSTER(z1))].x, 
		      (int)cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(x1),TOPOFCLUSTER(z1))].z);
	PlantPowerUp((int)cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(x1),TOPOFCLUSTER(z1))].x, 
				(int)cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(x1),TOPOFCLUSTER(z1))].z);
}


#define quarteroftheway 63.0/255.0 
#define noneoftheway 1.0/255.0
void RotateFlipAndApplyTile(int whichway, int flip, int x1, int z1, int x2, int z2, D3DVALUE bu, D3DVALUE bv)
// apply texture coordinate of one patch of landscap
// whichway is the way of texture mapping one patch of landscap
// flip is always zero
// x1, x2, z1, z2 represent the point clusters of the corners of 
// a patch of landscap
{
	D3DVALUE uoff[4], voff[4];

	{
		switch (whichway) 
		{
			case 2:
				uoff[0] = D3DVAL(noneoftheway);
				voff[0] = D3DVAL(noneoftheway);
				uoff[1] = D3DVAL( quarteroftheway);
				voff[1] = D3DVAL(noneoftheway);
				uoff[2] = D3DVAL(noneoftheway);
				voff[2] = D3DVAL( quarteroftheway);
				uoff[3] = D3DVAL( quarteroftheway);
				voff[3] = D3DVAL( quarteroftheway);
				break;
			case 1:
				uoff[0] = D3DVAL(noneoftheway);
				voff[0] = D3DVAL( quarteroftheway);
				uoff[1] = D3DVAL(noneoftheway);
				voff[1] = D3DVAL(noneoftheway);
				uoff[2] = D3DVAL( quarteroftheway);
				voff[2] = D3DVAL( quarteroftheway);
				uoff[3] = D3DVAL( quarteroftheway);
				voff[3] = D3DVAL(noneoftheway);
				break;
			case 0:
				uoff[0] = D3DVAL( quarteroftheway);
				voff[0] = D3DVAL( quarteroftheway);
				uoff[1] = D3DVAL(noneoftheway);
				voff[1] = D3DVAL( quarteroftheway);
				uoff[2] = D3DVAL( quarteroftheway);
				voff[2] = D3DVAL(noneoftheway);
				uoff[3] = D3DVAL(noneoftheway);
				voff[3] = D3DVAL(noneoftheway);
				break;
			case 3:
				uoff[0] = D3DVAL( quarteroftheway);
				voff[0] = D3DVAL(noneoftheway);
				uoff[1] = D3DVAL( quarteroftheway);
				voff[1] = D3DVAL( quarteroftheway);
				uoff[2] = D3DVAL(noneoftheway);
				voff[2] = D3DVAL(noneoftheway);
				uoff[3] = D3DVAL(noneoftheway);
				voff[3] = D3DVAL( quarteroftheway);
		}
		cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(x1),TOPOFCLUSTER(z1))].tu = D3DVAL(bu+uoff[0]);
		cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(x1),TOPOFCLUSTER(z1))].tv = D3DVAL(bv+voff[0]);
		cGlobals.vertices[VERTEXINDEX(BOTTOMOFCLUSTER(x2),TOPOFCLUSTER(z1))].tu = D3DVAL(bu+uoff[1]);
		cGlobals.vertices[VERTEXINDEX(BOTTOMOFCLUSTER(x2),TOPOFCLUSTER(z1))].tv = D3DVAL(bv+voff[1]);
		cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(x1),BOTTOMOFCLUSTER(z2))].tu = D3DVAL(bu+uoff[2]);
		cGlobals.vertices[VERTEXINDEX(TOPOFCLUSTER(x1),BOTTOMOFCLUSTER(z2))].tv = D3DVAL(bv+voff[2]);
		cGlobals.vertices[VERTEXINDEX(BOTTOMOFCLUSTER(x2),BOTTOMOFCLUSTER(z2))].tu = D3DVAL(bu+uoff[3]);
		cGlobals.vertices[VERTEXINDEX(BOTTOMOFCLUSTER(x2),BOTTOMOFCLUSTER(z2))].tv = D3DVAL(bv+voff[3]);
	} 
}

void DestroyILand()
{
  	Wcamera->lpVtbl->DeleteMoveCallback(Wcamera, ilandkontrol, (void*)NULL); 	

	MDFreeD3DFrame(LandFrame); 
	MyLand->dev = NULL;
    MyLand->view = NULL;
	ReleaseOneTexture(&MyLand->tex);
	RELEASE(MyLand->mat);
	free(MyLand);
}

void init_iland(LPDIRECT3DRMFRAME camera, LPDIRECT3DRMFRAME scene)
// initialise the lanscap
{
    D3DVECTOR campos;
	int i;

	memset(landeb, 0, 9 * sizeof(LPDIRECT3DEXECUTEBUFFER));
	memset(TriOffset, 0, 9 * sizeof(ULONG));
	
	for (i = 0; i < 9; i++)
		b_num[i] = i;

	if (detail==1) {
		cpx = cpz = 8;
		blocknum = 1;
	} else if (detail==2) {
		cpx = cpz = 10;
		blocknum = 1;
	} else if (detail==3) {
		cpx = cpz = 12;
		blocknum = 1;
	} else if (detail==4) {
		cpx = cpz = 12;
		blocknum = 1;
	} else if (detail==5) {
		cpx = cpz = 16;
		blocknum = 1;
	}
	cpxs = cpx-1;
	cpzs = cpz-1;

	sealevel = D3DVAL(-1.0);
    switch (GameStates.CurrentLevel) {
	    case Mojave:
			landscale = D3DVAL(32.0);
			break;
	    case Rockies:
	    	landscale == D3DVAL(16.0);
			break;
	    case Hawaii:
			landscale = D3DVAL(32.0);
			break;
	    case SanFrancisco:
			landscale = D3DVAL(32.0);
			break;
	    case NewYork:
			landscale = D3DVAL(32.0);
			break;
	    case Tokyo:
			landscale = D3DVAL(32.0);
			break;
	}
	sealevel = D3DDivide(D3DVAL(texturecutoffs[1]-0.1),landscale);
    if (GameStates.CurrentLevel < Hawaii) {
		sealevel = D3DVAL(-1.0);
	}
	SpuddeMonstersAltitudeWhenSwimming=sealevel-SwimmingDepth;

    camera->lpVtbl->GetPosition(camera, scene, &campos);
    cGlobals.oldcamerax = cGlobals.camerax = cuint*((int)(campos.x)/cuint);
    cGlobals.oldcameraz = cGlobals.cameraz = cuint*((int)(campos.z)/cuint);

    cGlobals.zstripmin = 0;
    cGlobals.zlinemin = 0;
    cGlobals.xstripmin = 0;
    cGlobals.xlinemin = 0;
    cGlobals.zstripmax = cpzs-1;
    cGlobals.zlinemax = cpz-1;
    cGlobals.xstripmax = cpxs-1;
    cGlobals.xlinemax = cpx-1;

	if (blocknum == 1)
	{
		xmin[0] = cGlobals.camerax - (cpx*cuint/2);
		zmin[0] = cGlobals.cameraz - (cpz*cuint/2);
		xmax[0] = xmin[0] + cpxs*cuint;
		zmax[0] = zmin[0] + cpzs*cuint;
	}
	else if (blocknum == 4)
	{
		xmin[0] = cGlobals.camerax - cpxs * cuint;
		zmin[0] = cGlobals.cameraz - cpzs * cuint;
		xmax[0] = xmin[0] + cpxs * cuint;
		zmax[0] = zmin[0] + cpzs * cuint;

		xmin[1] = xmin[0] + cpxs * cuint;
		zmin[1] = zmin[0] ;
		xmax[1] = xmax[0] + cpxs * cuint;
		zmax[1] = zmax[0] ;

		xmin[2] = xmin[0] ;
		zmin[2] = zmin[0] + cpzs * cuint;
		xmax[2] = xmax[0] ;
		zmax[2] = zmax[0] + cpzs * cuint;

		xmin[3] = xmin[0] + cpxs * cuint;
		zmin[3] = zmin[0] + cpzs * cuint;
		xmax[3] = xmax[0] + cpxs * cuint;
		zmax[3] = zmax[0] + cpzs * cuint;
	}
	else if (blocknum == 9)
	{
		xmin[0] = cGlobals.camerax - (cpx*cuint/2) - cpxs*cuint;
		zmin[0] = cGlobals.cameraz - (cpz*cuint/2) - cpzs*cuint;
		xmax[0] = xmin[0] + cpxs*cuint;
		zmax[0] = zmin[0] + cpzs*cuint;

		xmin[1] = xmin[0] + cpxs * cuint;
		zmin[1] = zmin[0] ;
		xmax[1] = xmax[0] + cpxs * cuint;
		zmax[1] = zmax[0] ;

		xmin[2] = xmin[0] + 2 * cpxs * cuint;
		zmin[2] = zmin[0] ;
		xmax[2] = xmax[0] + 2 * cpxs * cuint;
		zmax[2] = zmax[0] ;

		xmin[3] = xmin[0] ;
		zmin[3] = zmin[0] + cpzs * cuint;
		xmax[3] = xmax[0] ;
		zmax[3] = zmax[0] + cpzs * cuint;

		xmin[4] = xmin[0] + cpxs * cuint;
		zmin[4] = zmin[0] + cpzs * cuint;
		xmax[4] = xmax[0] + cpxs * cuint;
		zmax[4] = zmax[0] + cpzs * cuint;

		xmin[5] = xmin[0] + 2 * cpxs * cuint;
		zmin[5] = zmin[0] + cpzs * cuint;
		xmax[5] = xmax[0] + 2 * cpxs * cuint;
		zmax[5] = zmax[0] + cpzs * cuint;

		xmin[6] = xmin[0] ;
		zmin[6] = zmin[0] + 2 * cpzs * cuint;
		xmax[6] = xmax[0] ;
		zmax[6] = zmax[0] + 2 * cpzs * cuint;

		xmin[7] = xmin[0] + cpxs * cuint;
		zmin[7] = zmin[0] + 2 * cpzs * cuint;
		xmax[7] = xmax[0] + cpxs * cuint;
		zmax[7] = zmax[0] + 2 * cpzs * cuint;

		xmin[8] = xmin[0] + 2 * cpxs * cuint;
		zmin[8] = zmin[0] + 2 * cpzs * cuint;
		xmax[8] = xmax[0] + 2 * cpxs * cuint;
		zmax[8] = zmax[0] + 2 * cpzs * cuint;
	}

	cGlobals.xmin = xmin[0];
	cGlobals.zmin = zmin[0];
	cGlobals.xmax = xmax[blocknum-1];
	cGlobals.zmax = zmax[blocknum-1];

	if (GameStates.CurrentLevel == Trainer)         // special case
   {
      landbox.min.x = D3DVAL(-LANDXCENTER+39+5);
	   landbox.min.z = D3DVAL(-LANDZCENTER+41+5);
	   landbox.max.x = D3DVAL(-LANDXCENTER+221-5);
	   landbox.max.z = D3DVAL(-LANDZCENTER+220-5);
   } else
   {
      landbox.min.x = D3DVAL(-LANDXCENTER+2);
	   landbox.min.z = D3DVAL(-LANDZCENTER+2);
	   landbox.max.x = D3DVAL(LANDXSIZE-LANDXCENTER-2);
	   landbox.max.z = D3DVAL(LANDZSIZE-LANDZCENTER-2);
   }

	MapTrees();
	CreatePowerUps();

	//if (RLObjectExists(edgeframe) != RLNoError) 
	edgeframe = RLCreateFrame(scene);
	makeedges (&edgeoworld, edgeframe, camera);

	/* Remove clouds now that backgrounds are in
   if (RLObjectExists(cloudframe) != RLNoError) 
		cloudframe = RLCreateFrame(scene);
	RLFrameSetPosition(cloudframe, scene, RLVal(0.0), RLVal(-5.0), RLVal(0.0));
	makeclouds(&clouds, cloudframe, camera, (detail==1 ? 1 :cpx/4));
	for (i=0;i<(clouds->properties->num);i++) {
		PlaceCloud(i);
		RLFrameSetOrientation(clouds->particles[i]->frame, Wscene, 
			RLVal(0.0), RLVal(-1.0), RLVal(0.0), RLVal(0.0), RLVal(0.0), RLVal(1.0));
		RLFrameSetRotation(clouds->particles[i]->frame, Wscene, 
			RLVal(0.0), RLVal(1.0), RLVal(0.0), RLVal(0.0));
	}
   */
}


// to move vertical strip to the right
void CRight(int num)      
{
    int zstriploop, zlineloop, i, ii;

    xmin[num]+=cuint;
    xmax[num]+=cuint;

    ii = 0;
    zlineloop = cGlobals.zlinemin;
    for (i=0; i<cpz; i++) {
		update_joints(cGlobals.xlinemin, zlineloop, xmax[num], ii+zmin[num]);
		zlineloop = INCMOD(zlineloop, cpz);
    	ii+=cuint;
    }

    zlineloop = cGlobals.zlinemin;
    zstriploop = cGlobals.zstripmin;
    for (i=0; i<cpzs; i++) {
		update_vertices(cGlobals.xstripmin, zstriploop, cGlobals.xlinemax, cGlobals.xlinemin, zlineloop, INCMOD(zlineloop, cpz));
		zlineloop = INCMOD(zlineloop, cpz);
		zstriploop = INCMOD(zstriploop, cpzs);
    }
}


// to move strip to the left
void CLeft(int num)
{
    int zstriploop, zlineloop, i, ii;
	xmin[num]-=cuint;
	xmax[num]-=cuint;

    ii = 0;
	zlineloop = cGlobals.zlinemin;
	for (i=0; i<cpz; i++) {
		update_joints(cGlobals.xlinemax, zlineloop, xmin[num], ii+zmin[num]);
	    zlineloop = INCMOD(zlineloop, cpz);
        ii+=cuint;
	}

	zlineloop = cGlobals.zlinemin;
	zstriploop = cGlobals.zstripmin;
	for (i=0; i<cpzs; i++) {
		update_vertices(cGlobals.xstripmax, zstriploop, cGlobals.xlinemax, cGlobals.xlinemin, zlineloop, INCMOD(zlineloop, cpz));
		zlineloop = INCMOD(zlineloop, cpz);
		zstriploop = INCMOD(zstriploop, cpzs);
	}
}


// to move horizontal strip to the top
void CForward(int num)
{
    int xstriploop, xlineloop, i, ii;
	zmin[num]+=cuint;
	zmax[num]+=cuint;

   ii = 0;
	xlineloop = cGlobals.xlinemin;
	for (i=0; i<cpx; i++) {
		update_joints(xlineloop, cGlobals.zlinemin, xmin[num]+ii, zmax[num]);
	    xlineloop = INCMOD(xlineloop, cpx);
       ii+=cuint;
	}

	xlineloop = cGlobals.xlinemin;
	xstriploop = cGlobals.xstripmin;
	for (i=0; i<cpxs; i++) {
		update_vertices(xstriploop, cGlobals.zstripmin, xlineloop, INCMOD(xlineloop, cpx), cGlobals.zlinemax, cGlobals.zlinemin);
		xlineloop = INCMOD(xlineloop, cpx);
		xstriploop = INCMOD(xstriploop, cpxs);
	}
}

// to move strip to the bottom
void CBackward(int num)
{
    int xstriploop, xlineloop, i, ii;
	
	zmin[num]-=cuint;
	zmax[num]-=cuint;

    ii = 0;
	xlineloop = cGlobals.xlinemin;
	for (i=0; i<cpx; i++) {
		update_joints(xlineloop, cGlobals.zlinemax, xmin[num]+ii, zmin[num]);
	    xlineloop = INCMOD(xlineloop, cpx);
       ii+=cuint;
	}

	xlineloop = cGlobals.xlinemin;
	xstriploop = cGlobals.xstripmin;
	for (i=0; i<cpxs; i++) {
		update_vertices(xstriploop, cGlobals.zstripmax, xlineloop, INCMOD(xlineloop, cpx), cGlobals.zlinemax, cGlobals.zlinemin);
		xlineloop = INCMOD(xlineloop, cpx);
		xstriploop = INCMOD(xstriploop, cpxs);
	}
}


void ilandkontrol(LPDIRECT3DRMFRAME camera, LPVOID arg, D3DVALUE delta)
// moving landscap accroding to the moving of camera
{
	D3DVECTOR campos, camdir, camup;
	D3DVECTOR Robotpos;
    int i, cstep = cuint/2;
    D3DEXECUTEBUFFERDESC desc;
	int num;

   camera->lpVtbl->GetPosition(camera, cGlobals.scene, &campos);
   camera->lpVtbl->GetOrientation(camera, cGlobals.scene, &camdir, &camup);
   D3DRMVectorNormalise(&camdir);
   cGlobals.camerax = (int)(campos.x+cpx*camdir.x*cuint*0.45);
   cGlobals.cameraz = (int)(campos.z+cpz*camdir.z*cuint*0.45);

    for (i=0;i<5;i++) { 
       // Five loops through to make sure landscape 
       // keeps up with the camera

		if (cGlobals.camerax > cGlobals.oldcamerax+cstep) {
			for (num = 0; num < blocknum; num++)
			{
				desc.dwSize = sizeof(desc);
				desc.dwFlags = 0;
				if (FAILED(landeb[num]->lpVtbl->Lock(landeb[num], &desc)))
				{
					goto ret_with_error;
				}

				cGlobals.vertices = (D3DVERTEX*) desc.lpData;
				cGlobals.sections = (D3DTRIANGLE*)((char*) desc.lpData + TriOffset[num]);
				
				CRight(num);

				if (FAILED(landeb[num]->lpVtbl->Unlock(landeb[num])))
				{
					goto ret_with_error;
				}
			}
			
			cGlobals.xlinemax = cGlobals.xlinemin;
			cGlobals.xlinemin = INCMOD(cGlobals.xlinemin, cpx);
			cGlobals.xstripmax = cGlobals.xstripmin;
			cGlobals.xstripmin = INCMOD(cGlobals.xstripmin, cpxs);

			(cGlobals.xmin)+=cuint;
			(cGlobals.xmax)+=cuint;
			(cGlobals.oldcamerax)+=cuint;
		}


		if (cGlobals.camerax < cGlobals.oldcamerax-cstep) {
			for (num = 0; num < blocknum; num++)
			{
				desc.dwSize = sizeof(desc);
				desc.dwFlags = 0;
				if (FAILED(landeb[num]->lpVtbl->Lock(landeb[num], &desc)))
				{
					goto ret_with_error;
				}

				cGlobals.vertices = (D3DVERTEX*) desc.lpData;
				cGlobals.sections = (D3DTRIANGLE*)((char*) desc.lpData + TriOffset[num]);
				
				CLeft(num);

				if (FAILED(landeb[num]->lpVtbl->Unlock(landeb[num])))
				{
					goto ret_with_error;
				}
			}
			
			cGlobals.xlinemin = cGlobals.xlinemax;
			cGlobals.xlinemax = DECMOD(cGlobals.xlinemax, cpx);
			cGlobals.xstripmin = cGlobals.xstripmax;
			cGlobals.xstripmax = DECMOD(cGlobals.xstripmax, cpxs);

			(cGlobals.xmin)-=cuint;
			(cGlobals.xmax)-=cuint;
			(cGlobals.oldcamerax)-=cuint;
		}
		

		if (cGlobals.cameraz > cGlobals.oldcameraz+cstep) {
			for (num = 0; num < blocknum; num++)
			{
				desc.dwSize = sizeof(desc);
				desc.dwFlags = 0;
				if (FAILED(landeb[num]->lpVtbl->Lock(landeb[num], &desc)))
				{
					goto ret_with_error;
				}

				cGlobals.vertices = (D3DVERTEX*) desc.lpData;
				cGlobals.sections = (D3DTRIANGLE*)((char*) desc.lpData + TriOffset[num]);
				
				CForward(num);

				if (FAILED(landeb[num]->lpVtbl->Unlock(landeb[num])))
				{
					goto ret_with_error;
				}
			}
			
			cGlobals.zlinemax = cGlobals.zlinemin;
			cGlobals.zlinemin = INCMOD(cGlobals.zlinemin, cpz);
			cGlobals.zstripmax = cGlobals.zstripmin;
			cGlobals.zstripmin = INCMOD(cGlobals.zstripmin, cpzs);

			(cGlobals.zmin)+=cuint;
			(cGlobals.zmax)+=cuint;
			(cGlobals.oldcameraz)+=cuint;
		}
		

		if (cGlobals.cameraz < cGlobals.oldcameraz-cstep) {
			for (num = 0; num < blocknum; num++)
			{
				desc.dwSize = sizeof(desc);
				desc.dwFlags = 0;
				if (FAILED(landeb[num]->lpVtbl->Lock(landeb[num], &desc)))
				{
					goto ret_with_error;
				}

				cGlobals.vertices = (D3DVERTEX*) desc.lpData;
				cGlobals.sections = (D3DTRIANGLE*)((char*) desc.lpData + TriOffset[num]);
				
				CBackward(num);

				if (FAILED(landeb[num]->lpVtbl->Unlock(landeb[num])))
				{
					goto ret_with_error;
				}
			}
			
			cGlobals.zlinemin = cGlobals.zlinemax;
			cGlobals.zlinemax = DECMOD(cGlobals.zlinemax, cpz);
			cGlobals.zstripmin = cGlobals.zstripmax;
			cGlobals.zstripmax = DECMOD(cGlobals.zstripmax, cpzs);

			(cGlobals.zmin)-=cuint;
			(cGlobals.zmax)-=cuint;
			(cGlobals.oldcameraz)-=cuint;
		}
	}

    update_vis_bldgs(cGlobals.scene,   
			MAX(-LANDXCENTER, cGlobals.xmin),
            MAX(-LANDZCENTER, cGlobals.zmin),
			MIN(LANDXSIZE-LANDXCENTER, cGlobals.xmax),
			MIN(LANDZSIZE-LANDZCENTER, cGlobals.zmax) ); 
	
	RLFrameGetPosition(goodguyframe, Wscene, &Robotpos);
	if ((Robotpos.x > LANDXSIZE-LANDXCENTER - cpx) || (Robotpos.x < -LANDXCENTER + cpx)) 
	{
		if(!edgeoworld->particles[0]->active)
		{
			edgeoworld->particles[0]->active = 1;
			YBPlay3DSound(EdgeOWorld, goodguyframe);
		}
		RLFrameSetPosition(edgeoworld->particles[0]->frame, Wscene, 
			RLVal(((Robotpos.x > LANDXSIZE-LANDXCENTER - cpx) ? LANDXSIZE-LANDXCENTER+1 : -LANDXCENTER-1 )),
			Robotpos.y+RLVal(2.5),
			Robotpos.z);
	} 
	else 
	{
		edgeoworld->particles[0]->active = 0;
	}

	if ((Robotpos.z > LANDZSIZE-LANDZCENTER - cpz) || (Robotpos.z < -LANDZCENTER + cpz)) 
	{
		if(!edgeoworld->particles[1]->active)
		{
			edgeoworld->particles[1]->active = 1;
			YBPlay3DSound(EdgeOWorld, goodguyframe);
		}
		RLFrameSetPosition(edgeoworld->particles[1]->frame, Wscene, 
			Robotpos.x,
			Robotpos.y+RLVal(2.5),
			RLVal(((Robotpos.z > LANDZSIZE-LANDZCENTER - cpz) ? LANDZSIZE-LANDZCENTER+1 : -LANDZCENTER-1 )));
	} 
	else
	{
		edgeoworld->particles[1]->active = 0;
		if(!edgeoworld->particles[0]->active)
			BYOBStopSound(EdgeOWorld);
	}

	RemoveTrees(cGlobals.xmin, cGlobals.zmin, cGlobals.xmax, cGlobals.zmax);
	RemovePowerUps(cGlobals.xmin, cGlobals.zmin, cGlobals.xmax, cGlobals.zmax);
 	//UpdateClouds(); 

	return;
ret_with_error:
	Msg("There is one ERROR in RenderLand(...) function");
    return;
}


void PlaceCloud(int cloudID)
{
	RLValue xcoord, ycoord, zcoord, xextent, zextent;

	xextent = zextent = RLVal(2.0*cpx*cuint);

	xcoord = cGlobals.camerax - xextent/2 + RLVal((rand()&0xffff)/65536.0*(xextent));
	zcoord = cGlobals.cameraz - zextent/2 + RLVal((rand()&0xffff)/65536.0*(zextent));
	ycoord = SpuddeMapHeight2(xcoord, zcoord) + RLVal(5.0) + RLVal((rand()&0xffff)/65536.0*0.5);
	RLFrameSetPosition(clouds->particles[cloudID]->frame, Wscene, xcoord, ycoord, zcoord);
	RLFrameSetVelocity(clouds->particles[cloudID]->frame, Wscene, RLVal(0), RLVal(0), RLVal(0.4*(rand()&0xffff)/65536.0));
}

void UpdateClouds()
{
	RLValue xextent, zextent;
	RLVector cloudpos;
	int i;

	xextent = zextent = RLVal(2.0*cpx*cuint);

	for (i=0;i<(clouds->properties->num);i++) {
		RLFrameGetPosition(clouds->particles[i]->frame, Wscene, &cloudpos);
		if (cloudpos.x > cGlobals.camerax + xextent/2) {
			cloudpos.x = cGlobals.camerax - xextent/2;
			cloudpos.z = cGlobals.cameraz - zextent/2 + RLVal((rand()&0xffff)/65536.0*(zextent)*(zextent));
			cloudpos.x = MAX(-LANDXSIZE, MIN(cloudpos.x, LANDXSIZE));
			cloudpos.z = MAX(-LANDZSIZE, MIN(cloudpos.z, LANDZSIZE));
			cloudpos.y = SpuddeMapHeight2(cloudpos.x, cloudpos.z) + RLVal(5.0) + RLVal((rand()&0xffff)/65536.0);
			RLFrameSetPosition(clouds->particles[i]->frame, Wscene, cloudpos.x, cloudpos.y, cloudpos.z);
			RLFrameSetVelocity(clouds->particles[i]->frame, Wscene, RLVal(0), RLVal(0), RLVal(0.4*(rand()&0xffff)/65536.0));
			break;
		}
		if (cloudpos.x < cGlobals.camerax - xextent/2) {
			cloudpos.x = cGlobals.camerax + xextent/2;
			cloudpos.z = cGlobals.cameraz - zextent/2 + RLVal((rand()&0xffff)/65536.0*(zextent));
			cloudpos.x = MAX(-LANDXSIZE, MIN(cloudpos.x, LANDXSIZE));
			cloudpos.z = MAX(-LANDZSIZE, MIN(cloudpos.z, LANDZSIZE));
			cloudpos.y = SpuddeMapHeight2(cloudpos.x, cloudpos.z) + RLVal(5.0) + RLVal((rand()&0xffff)/65536.0);
			RLFrameSetPosition(clouds->particles[i]->frame, Wscene, cloudpos.x, cloudpos.y, cloudpos.z);
			RLFrameSetVelocity(clouds->particles[i]->frame, Wscene, RLVal(0), RLVal(0), RLVal(0.4*(rand()&0xffff)/65536.0));
			break;
		}
		if (cloudpos.z > cGlobals.cameraz + zextent/2) {
			cloudpos.x = cGlobals.camerax - xextent/2 + RLVal((rand()&0xffff)/65536.0*(xextent));
			cloudpos.z = cGlobals.cameraz - zextent/2;
			cloudpos.x = MAX(-LANDXSIZE, MIN(cloudpos.x, LANDXSIZE));
			cloudpos.z = MAX(-LANDZSIZE, MIN(cloudpos.z, LANDZSIZE));
			cloudpos.y = SpuddeMapHeight2(cloudpos.x, cloudpos.z) + RLVal(5.0) + RLVal((rand()&0xffff)/65536.0);
			RLFrameSetPosition(clouds->particles[i]->frame, Wscene, cloudpos.x, cloudpos.y, cloudpos.z);
			RLFrameSetVelocity(clouds->particles[i]->frame, Wscene, RLVal(0), RLVal(0), RLVal(0.4*(rand()&0xffff)/65536.0));
			break;
		}
		if (cloudpos.z < cGlobals.cameraz - zextent/2) {
			cloudpos.x = cGlobals.camerax - xextent/2 + RLVal((rand()&0xffff)/65536.0*(xextent));
			cloudpos.z = cGlobals.cameraz + zextent/2;
			cloudpos.y = SpuddeMapHeight2(cloudpos.x, cloudpos.z) + RLVal(5.0) + RLVal((rand()&0xffff)/65536.0);
			cloudpos.x = MAX(-LANDXSIZE, MIN(cloudpos.x, LANDXSIZE));
			cloudpos.z = MAX(-LANDZSIZE, MIN(cloudpos.z, LANDZSIZE));
			RLFrameSetPosition(clouds->particles[i]->frame, Wscene, cloudpos.x, cloudpos.y, cloudpos.z);
			RLFrameSetVelocity(clouds->particles[i]->frame, Wscene, RLVal(0), RLVal(0), RLVal(0.4*(rand()&0xffff)/65536.0));
			break;
		}
	}
}


void CleanupLandObjects(LPDIRECT3DRMOBJECT dev, void* arg)
{
    int num = *(int *)arg;

    if(landeb[num]) {
        RELEASE(landeb[num]);
        landeb[num] = NULL;
    }
}

extern int VM_W3D;
extern int VM_H3D;
extern int VM_BPP3D;

BOOL CreateLandObjects(int iii, LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view)
{
    D3DEXECUTEBUFFERDESC desc;
    D3DEXECUTEDATA data;
    D3DMATERIALHANDLE hMat;
    LPDIRECT3D lpD3D = NULL;
    LPDIRECT3DDEVICE lpD3DDev = NULL;
    LPDIRECT3DEXECUTEBUFFER eb = NULL;
	LPVOID lpPointer;
    LPVOID lpBufStart, lpInsStart;
	int size;
	int ii, i, jj, j;
	int num = iii;

    dev->lpVtbl->GetDirect3DDevice(dev, &lpD3DDev);
    if (!lpD3DDev)
        goto generic_error;
    if (FAILED(lpD3DDev->lpVtbl->GetDirect3D(lpD3DDev, &lpD3D)))
        goto generic_error;

    if (FAILED(MyLand->mat->lpVtbl->GetHandle(MyLand->mat, lpD3DDev, &hMat)))
        goto generic_error;

    size  = sizeof(D3DVERTEX) * 4 * cpx * cpz; 
    //DongMing's code:
	//size += sizeof(D3DINSTRUCTION) * 9;
    //size += sizeof(D3DSTATE) * 6;
    //Lgh added.
	size += sizeof(D3DINSTRUCTION) * 10;
    size += sizeof(D3DSTATE) * 19;
    size += sizeof(D3DSTATUS) * 1;
    size += sizeof(D3DPROCESSVERTICES) * 1;
    size += sizeof(D3DTRIANGLE) * 2 * cpxs * cpzs;

    desc.dwSize = sizeof(desc);
    desc.dwFlags = D3DDEB_BUFSIZE;
    desc.dwBufferSize = size;
    
    if (FAILED(lpD3DDev->lpVtbl->CreateExecuteBuffer(lpD3DDev, &desc, &eb, NULL)))
        goto generic_error;
    
	if (FAILED(eb->lpVtbl->Lock(eb, &desc)))
        goto generic_error;
   
    lpBufStart = desc.lpData;
    memset(lpBufStart, 0, size);
    lpPointer = lpBufStart;

	cGlobals.vertices = (D3DVERTEX*) desc.lpData;
    ii = 0;
    for (i=cGlobals.xlinemin; i<=cGlobals.xlinemax; i++) 
	{
		jj = 0;
	    for (j=cGlobals.zlinemin; j<=cGlobals.zlinemax; j++) 
		{
			update_joints(i, j, xmin[num]+ii, zmin[num]+jj);
			jj+=cuint;
	    }
		ii+=cuint;
    }

    lpPointer = (void*) ((char*) desc.lpData + 4 * cpx * cpz * sizeof(D3DVERTEX));

    lpInsStart = lpPointer;
    OP_STATE_LIGHT(4, lpPointer);
        STATE_DATA(D3DLIGHTSTATE_MATERIAL, hMat, lpPointer);
		  STATE_DATA(D3DLIGHTSTATE_FOGMODE, d3dapprs.bFogEnabled ?
                 d3dapprs.FogMode : D3DFOG_NONE, lpPointer);
		  STATE_DATA(D3DLIGHTSTATE_FOGSTART, *(unsigned long*)&d3dapprs.FogStart,
                 lpPointer);
		  STATE_DATA(D3DLIGHTSTATE_FOGEND, *(unsigned long*)&d3dapprs.FogEnd,
                 lpPointer);



	OP_SET_STATUS(D3DSETSTATUS_ALL, D3DSTATUS_DEFAULT, 2048, 2048, 0, 0, lpPointer);
    
	if ((VM_BPP3D == 8))
   {
       OP_PROCESS_VERTICES(1, lpPointer);
           PROCESSVERTICES_DATA(D3DPROCESSVERTICES_TRANSFORM ,
                            0, 4 * cpx * cpz, lpPointer);
    OP_STATE_RENDER(1, lpPointer);
        STATE_DATA(D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD, lpPointer);
   }
   else
   {
       OP_PROCESS_VERTICES(1, lpPointer);
           PROCESSVERTICES_DATA(D3DPROCESSVERTICES_TRANSFORMLIGHT ,
                            0, 4 * cpx * cpz, lpPointer);
    OP_STATE_RENDER(1, lpPointer);
        STATE_DATA(D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD, lpPointer);
        //STATE_DATA(D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT, lpPointer);
		//STATE_DATA(D3DRENDERSTATE_SHADEMODE, d3dapprs.ShadeMode, lpPointer);
   }

	OP_STATE_RENDER(8, lpPointer);
        STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE, MyLand->tex.hTex, lpPointer);
        STATE_DATA(D3DRENDERSTATE_WRAPV, FALSE, lpPointer);
        STATE_DATA(D3DRENDERSTATE_WRAPU, FALSE, lpPointer);
		  STATE_DATA(D3DRENDERSTATE_TEXTUREPERSPECTIVE, d3dapprs.bPerspCorrect, lpPointer);	//Bruce
		  STATE_DATA(D3DRENDERSTATE_TEXTUREMAG, d3dapprs.TextureFilter,lpPointer);
		  STATE_DATA(D3DRENDERSTATE_TEXTUREMIN, d3dapprs.TextureFilter,lpPointer);
//		  STATE_DATA(D3DRENDERSTATE_ANTIALIAS, d3dapprs.bAntiAliasing,lpPointer);
		  STATE_DATA(D3DRENDERSTATE_FOGENABLE, d3dapprs.bFogEnabled,lpPointer);
		  STATE_DATA(D3DRENDERSTATE_FOGCOLOR, d3dapprs.FogColor,lpPointer);

	if ((VM_BPP3D == 8))
	{
		OP_STATE_RENDER(3, lpPointer);
			STATE_DATA(D3DRENDERSTATE_BLENDENABLE, FALSE, lpPointer);
			STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_COPY, lpPointer);	
			STATE_DATA(D3DRENDERSTATE_DESTBLEND, D3DBLEND_DESTALPHA, lpPointer);	
	}
	else
	{
		OP_STATE_RENDER(2, lpPointer);
			STATE_DATA(D3DRENDERSTATE_BLENDENABLE, FALSE, lpPointer);
			STATE_DATA(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE, lpPointer);
		//	STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_DECAL,lpPointer);

	}
		OP_STATE_RENDER(2, lpPointer);
			STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE, TRUE, lpPointer);
			STATE_DATA(D3DRENDERSTATE_ZENABLE, TRUE, lpPointer);

    /*
     * Make sure that the triangle data (not OP) will be QWORD aligned
     */
    if (QWORD_ALIGNED(lpPointer)) {
        OP_NOP(lpPointer);
    }
	
	OP_TRIANGLE_LIST(2 * cpxs * cpzs, lpPointer);

	TriOffset[num] = (ULONG) ((char *)lpPointer - (char *)desc.lpData);

	cGlobals.sections = (D3DTRIANGLE*)lpPointer;
    for (i=cGlobals.xstripmin; i<=cGlobals.xstripmax; i++) 
	{
	    for (j=cGlobals.zstripmin; j<=cGlobals.zstripmax; j++) 
		{
			update_vertices(i, j, i, i+1, j, j+1);
	    }
    }

    lpPointer = (void*) ((char*) lpPointer + 2 * cpxs * cpzs * sizeof(D3DTRIANGLE));
 		
	OP_EXIT(lpPointer);

    if (FAILED(eb->lpVtbl->Unlock(eb)))
        goto generic_error;

    data.dwSize = sizeof(data);
    data.dwVertexOffset = 0;
    data.dwVertexCount = 4 * cpx * cpz;
    data.dwInstructionOffset = 4 * cpx * cpz * sizeof(D3DVERTEX);
    data.dwInstructionLength = (ULONG) ((char *)lpPointer - (char *)lpInsStart);
    if (FAILED(eb->lpVtbl->SetExecuteData(eb, &data)))
        goto generic_error;

    if (FAILED(dev->lpVtbl->AddDestroyCallback(dev, CleanupLandObjects, (void *)&b_num[num])))
        goto generic_error;

    landeb[num]  = eb;

    RELEASE(lpD3DDev);
    RELEASE(lpD3D);
    return TRUE;
generic_error:
    RELEASE(lpD3D);
    RELEASE(lpD3DDev);
    RELEASE(eb);
    return FALSE;
}

BOOL RenderLand(int num, LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view)
{
//    D3DEXECUTEBUFFERDESC desc;
    D3DEXECUTEDATA data;
    LPDIRECT3DDEVICE lpD3DDev = NULL;
    LPDIRECT3DVIEWPORT lpD3DView = NULL;
    HRESULT     rval;

    dev->lpVtbl->GetDirect3DDevice(dev, &lpD3DDev);
    view->lpVtbl->GetDirect3DViewport(view, &lpD3DView);
    if (!lpD3DDev || !lpD3DView)
    {
		goto ret_with_error;
	}

	if (FAILED(rval = lpD3DDev->lpVtbl->Execute(lpD3DDev, landeb[num], lpD3DView, D3DEXECUTE_CLIPPED)))
    {
		D3DAppISetErrorString("Execute ERROR!\n%s", D3DAppErrorToString(rval));
		goto ret_with_error;
	}

    data.dwSize = sizeof data;
    if (FAILED(landeb[num]->lpVtbl->GetExecuteData(landeb[num], &data)))
	{
        goto ret_with_error;
	}

	if(data.dsStatus.drExtent.x1 == 2048 || data.dsStatus.drExtent.y1 == 2048) 
		return TRUE;                  

	if ((data.dsStatus.drExtent.x1 == 2048) ||
		(data.dsStatus.drExtent.y1 == 2048))
	{
		return TRUE;
	}

    if (FAILED(rval = view->lpVtbl->ForceUpdate(view,
					  data.dsStatus.drExtent.x1,
                      data.dsStatus.drExtent.y1,
                      data.dsStatus.drExtent.x2,
                      data.dsStatus.drExtent.y2)))
	{
 		if (rval != D3DRMERR_BADVALUE)//Add by DOM 
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

int LandCallback(LPDIRECT3DRMUSERVISUAL uvis,
                 void* arg,
                 D3DRMUSERVISUALREASON reason,
                 LPDIRECT3DRMDEVICE dev,
                 LPDIRECT3DRMVIEWPORT view)
{
    int num = *((int*) arg);

    if (reason == D3DRMUSERVISUAL_CANSEE)
        return TRUE;

    if (reason == D3DRMUSERVISUAL_RENDER) {
        if (!RenderLand(num, dev, view))
            return DDERR_GENERIC;
        else
            return D3D_OK;
    }

    return 0;
}

void DestroyLand(LPDIRECT3DRMOBJECT obj, void* arg)
{
    if (MyLand->dev)
        MyLand->dev->lpVtbl->DeleteDestroyCallback(MyLand->dev, CleanupLandObjects, arg);
    CleanupLandObjects((LPDIRECT3DRMOBJECT)MyLand->dev, arg);
    MDFreeD3DFrame(edgeframe);

}


BOOL InitTexandMat(Land* land, LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view)
{
    LPDIRECT3D lpD3D = NULL;
    LPDIRECT3DDEVICE lpD3DDev = NULL;
    LPDIRECT3DMATERIAL mat = NULL;
    D3DMATERIAL orange;

    dev->lpVtbl->GetDirect3DDevice(dev, &lpD3DDev);
    if (!lpD3DDev)
        goto generic_error;
    if (FAILED(lpD3DDev->lpVtbl->GetDirect3D(lpD3DDev, &lpD3D)))
        goto generic_error;

	memset(&land->tex, 0, sizeof(TEXTURESTRUCT));
	MyLoadTexture(dev, ConstructLevelName("102.bmp"), &land->tex, 0);

    if (FAILED(lpD3D->lpVtbl->CreateMaterial(lpD3D, &mat, NULL)))
        goto generic_error;

    memset(&orange, 0, sizeof(orange));
    orange.dwSize = sizeof(orange);
    orange.diffuse.r = (D3DVALUE)1.0;
    orange.diffuse.g = (D3DVALUE)1.0;
    orange.diffuse.b = (D3DVALUE)1.0;
    orange.diffuse.a = (D3DVALUE)1.0;
    orange.ambient.r = (D3DVALUE)1.0;
    orange.ambient.g = (D3DVALUE)1.0;
    orange.ambient.b = (D3DVALUE)1.0;
    orange.specular.r = (D3DVALUE)1.0;
    orange.specular.g = (D3DVALUE)1.0;
    orange.specular.b = (D3DVALUE)1.0;
    orange.power = (float)20.0;
    orange.dwRampSize = 1;
    orange.hTexture = land->tex.hTex;

    if (FAILED(mat->lpVtbl->SetMaterial(mat, &orange)))
        goto generic_error;

	land->mat = mat;
    land->dev  = dev;
	land->view = view;

    RELEASE(lpD3DDev);
    RELEASE(lpD3D);
    return TRUE;
generic_error:
    RELEASE(lpD3D);
    RELEASE(lpD3DDev);
    RELEASE(mat);
    return FALSE;
}


LPDIRECT3DRMUSERVISUAL CreateLand(int i)
{
    LPDIRECT3DRMUSERVISUAL uvis = NULL;
	int num = i;

	if (FAILED(lpD3DRM->lpVtbl->CreateUserVisual(lpD3DRM, LandCallback, (void*)&b_num[num], &uvis)))
        goto ret_with_error;

	if (FAILED(uvis->lpVtbl->AddDestroyCallback(uvis, DestroyLand, (void*)&b_num[num])))
        goto ret_with_error;   
    return uvis;
ret_with_error:
    if (MyLand)
    {
		free(MyLand);
		MyLand = NULL;
	}
    RELEASE(uvis);
    return NULL;
}


BOOL
BuildLandScene(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
           LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera)
{
    D3DRMRENDERQUALITY quality = D3DRMRENDER_GOURAUD;
    LPDIRECT3DRMFRAME frame = NULL;
    LPDIRECT3DRMUSERVISUAL uvis = NULL;
	int i;

    if (FAILED(dev->lpVtbl->SetQuality(dev, quality)))
        goto generic_error;

	/*
     * create a frame within the scene
     */
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &frame)))
        goto generic_error;

	cGlobals.camera = camera;
	cGlobals.scene = scene;

    MyLand = (Land*)malloc(sizeof(Land));
    if (!MyLand)
        goto generic_error;
    memset(MyLand, 0, sizeof(Land));

	if (!InitTexandMat(MyLand, Wdevice, Wview))
        goto generic_error;

	for (i = 0; i < blocknum; i++)
	{
		if (!CreateLandObjects(i, Wdevice, Wview))
			goto generic_error;

		uvis = CreateLand(i);
		if (!uvis)
			goto generic_error;

		if (FAILED(frame->lpVtbl->AddVisual(frame, (LPDIRECT3DRMVISUAL)uvis)))
			goto generic_error;
    }

  	Wcamera->lpVtbl->AddMoveCallback(Wcamera, ilandkontrol, (void*)NULL); 	

	LandFrame = frame;

    RELEASE(uvis);
    RELEASE(frame);
    return TRUE;
generic_error:
    RELEASE(uvis);
    RELEASE(frame);
    return FALSE;
}

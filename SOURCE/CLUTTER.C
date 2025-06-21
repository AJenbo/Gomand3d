/***********************************************************************
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

Program:        Goman95
File:           clutter.c
Author:         J. Spudde Childs
Date:           11/30/95
Version:        1.1



************************************************************************
REVISION HISTORY        (Add Edits and History to top of list).

* $Header:   H:/pvcs/pvcsproj/gomand3d.prj/CLUTTER.C_V   1.21   13 May 1997 17:12:58   Jeremiah  $
* $Log:   H:/pvcs/pvcsproj/gomand3d.prj/CLUTTER.C_V  $
 * 
 *    Rev 1.21   13 May 1997 17:12:58   Jeremiah
 * Fixed background coordinates for small
 * and medium window sizes in blitted
 * background.
 * 
 *    Rev 1.20   13 May 1997 11:25:20   Jeremiah
 * Fixed stretch case for blitted background.
 * 
 *    Rev 1.19   12 May 1997 17:04:40   Jeremiah
 * Changed bCanStretch to bStretch.
 * 
 *    Rev 1.18   12 May 1997 11:53:28   Jeremiah
 * Separated stretch flags into separate 
 * structure.  
 * Eliminated warnings.
 * 
 *    Rev 1.17   07 May 1997 14:35:06   Bruce
 * morged versions 1.15.2.1 and 1.16
 * 
 *    Rev 1.16   07 May 1997 13:06:24   Bruce
 * changed from .x to .bin loading of models,
 * added a call to delete the binary after the
 * models have been loaded.
 * 
 *    Rev 1.15.2.1   28 Apr 1997 12:35:44   JEREMIAH
 * Merge of 1.15.1.0 and 1.15.2.0.
 * 
 *    Rev 1.15.2.0   28 Apr 1997 10:12:44   TIM
 * Mode mods for s3 stretch
 * 
 *    Rev 1.15.1.0   17 Apr 1997 10:19:30   JEREMIAH
 * Extended polygon background to 250
 * units in z, instead of 50.
 * 
 * 
 *    Rev 1.15   14 Apr 1997 17:38:44   JEREMIAH
 * Fixed bug in coordinates of background
 * in windowed modes.
 * 
 *    Rev 1.14   08 Apr 1997 10:50:36   JEREMIAH
 * Added textured backgrounds. 
 * 
 *    Rev 1.13   28 Mar 1997 15:00:52   JEREMIAH
 * Murged 1.11.1.0 and 1.12
 * 
 *    Rev 1.11.1.0   27 Mar 1997 19:32:24   BRUCE
 * made the flying sound a looping sound
 * instead of a sound that's played multiple
 * times.
 * 
 *    Rev 1.12   28 Mar 1997 14:46:16   JEREMIAH
 * Separated background function into a
 * function that calculates the coordinates
 * and a function that blits the background.
 * 
 *    Rev 1.11   13 Mar 1997 17:33:58   JEREMIAH
 * Changed display list dup function call
 * so user visuals would be created for each
 * powerup.
 * 
 *    Rev 1.10   12 Mar 1997 10:07:46   JEREMIAH
 * Load powerups as transparent.
 * 
 *    Rev 1.9   03 Mar 1997 17:51:42   BRUCE
 * made radar in relation to goodguyframe,
 * so when playing as monster, radar is
 * correct.
 * 
 * 
 *    Rev 1.8   18 Feb 1997 17:03:40   JEREMIAH
 * Removed unused code for scrolling 
 * horizon strips.
 * 
 *    Rev 1.7   14 Feb 1997 19:25:18   BRUCE
 * removed _47TEK_RL_ code
 * removed _ITC_D3D_ conditional
 * changed level to GameStates.CurrentLevel
 * changed levelwereon to GameStates.CurrentLevel
 * changed land_level to GameStates.CurrentLevel
 * changed submonster to GameStates.CurrentSubmonster
 * changed In3DMovie to GameStates.Is3DMovie
 * changed AutoDemoFlag to GameStates.IsAutodemo
 * 
 * 
 *    Rev 1.6   06 Feb 1997 08:13:46   BRUCE
 * took control of whichRobot
 * 
 *    Rev 1.5   06 Jan 1997 18:19:32   BO
 *  
 * 
 *    Rev 1.4   06 Jan 1997 16:27:46   JEREMIAH
 * Reduced rampsize on all materials to 1
 * to eliminate palettizing pause bug.
 * 
 *    Rev 1.3   20 Dec 1996 17:06:36   JEREMIAH
 * Changed filenames of textures to match
 * new filename conventions for level-specific
 * palettes.
 * 
 *    Rev 1.2   16 Dec 1996 10:48:04   JEREMIAH
 * Changed by ITC.  Added code for netplay.
 * 
 *    Rev 1.1   08 Nov 1996 11:36:40   JEREMIAH
 * Changed by Liou GuoHong (ITC).  In first
 * person camera, turn off jets when going
 * backwards.

***********************************************************************/

#include <math.h>
#include <stdlib.h>

#include "clutter.h"
#include "spritlib.h"
#include "byglobal.h"


#include "gosys.h"
#include "landscap.h"
#include "boink.h"
#include "imisc.h"
#include "camera.h"

#include <d3d.h>
#include "d3dmacs.h"
#include "mdtex.h"
#include "rl2d3d.h"
#include "d3dapp.h"
#include "rmfull.h"
#include "global.h"
#include "ybsnd.h"

#include "d3dappi.h"
#include "wrapper.h"

//Add by Eric 11/13/96
#include "netplay.h"
//end of Eric

extern char* D3DAppErrorToString(HRESULT error);
extern void D3DAppISetErrorString( LPSTR fmt, ... );

//extern int level;
//int levelwereon;
extern RLFrame behindthescene, Wscene, Wcamera;
extern RLDevice Wdevice;
extern RLViewport Wview;
extern int Vmode;
extern int Vsize;
extern RLColour theonlycolor;
extern RLMaterial theonlymaterial;
extern iobjdlist* allmiscdlists[];

LPDIRECT3DRMFRAME ScrollyScene; 
LPDIRECT3DRMFRAME ScrollyCamera;
//extern int land_level;

#define MAX_NO_TREES_ONSCREEN 50
#define MAX_NO_POWERUPS	10

typedef struct _mysprite {
	LPDIRECT3DRMFRAME frame;
	unsigned char flag1;
	unsigned char flag2;
} MySprite;


MySprite* trees[MAX_NO_TREES_ONSCREEN];
MySprite* poles[MAX_NO_TREES_ONSCREEN];

unsigned char treemap[LANDXSIZE*LANDZSIZE/8];
unsigned char polemap[LANDXSIZE*LANDZSIZE/8];
RLTexture treetex, poletex;


typedef struct _powerupdata {
	RLFrame frame;
	RLFrame rotframe;
	int flag1;
	int flag2;
	int active;
	int dlistidx;
} PowerUpData;

static PowerUpData powerups[MAX_NO_POWERUPS];

RLValue prob[7][4] =
	{
		RLVal(0.0), RLVal(0.00), RLVal(0.00), RLVal(0.00),
		RLVal(0.0), RLVal(0.05), RLVal(0.01), RLVal(0.00),
		RLVal(0.0), RLVal(0.10), RLVal(0.05), RLVal(0.00),
		RLVal(0.0), RLVal(0.05), RLVal(0.00), RLVal(0.05),
		RLVal(0.0), RLVal(0.0), RLVal(0.00), RLVal(0.15),
		RLVal(0.0), RLVal(0.00), RLVal(0.00), RLVal(0.10),
		RLVal(0.0), RLVal(0.00), RLVal(0.00), RLVal(0.10),
	};

int PowerUpPlace[7][MAX_NO_POWERUPS][2] =
	{

		 179, 97,    131, 180,    79, 163,   0, 0 ,   0, 0 ,  0, 0 ,   0, 0 ,   0, 0 ,   0, 0 ,   0, 0 , 
		 103, 91,    149, 236,    168, 168,   0, 0 ,   0, 0 ,  0, 0 ,   0, 0 ,   0, 0 ,   0, 0 ,   0, 0 , 
		 208, 101,   121, 161,   201, 138,   0, 0 ,   0, 0 ,  0, 0 ,   0, 0 ,   0, 0 ,   0, 0 ,   0, 0 , 
		 171, 65,   111, 171,   68, 157,   0, 0 ,   0, 0 ,  0, 0 ,   0, 0 ,   0, 0 ,   0, 0 ,   0, 0 , 
		 112, 81 ,   93, 225,   27, 144 ,   0, 0 ,   0, 0 ,  0, 0 ,   0, 0 ,   0, 0 ,   0, 0 ,   0, 0 , 
		 98, 201 ,   66, 118,   158, 55,   0, 0 ,   0, 0 ,  0, 0 ,   0, 0 ,   0, 0 ,   0, 0 ,   0, 0 , 
		 140, 108,   35, 61,   106, 139,   0, 0 ,   0, 0 ,  0, 0 ,   0, 0 ,   0, 0 ,   0, 0 ,   0, 0  
	}; 

int NumPowerUp[7] = { 3, 3, 3, 3, 3, 3, 3 };
int nexttree, nextpole;



TEXTURESTRUCT TreeTex;
TEXTURESTRUCT PoleTex;
//????
extern LPDIRECT3DRMDEVICE GWdevice;
extern LPDIRECT3DRMFRAME GWcamera;
//Plane* plane;

Plane* TreePlane;
Plane* PolePlane;

// **********************************************************
// Name:		LQHCreatePoleFrame
//		
// Author:		LiuQingHua					
//
// Date:		1996.8                      
//
// Description: Create the pole frame
//
// Arguments:		None
//
// Return:			None
//
// Side Effects:	None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

BOOL LQHCreatePoleFrame(LPDIRECT3DRMFRAME parent,D3DTEXTUREHANDLE htex)
{
	LPDIRECT3DRMUSERVISUAL uvis = NULL;
	int i;

	MallocPlane(&PolePlane);
	memset(PolePlane, 0, sizeof(Plane));

	PolePlane->hTex = htex;
	
	PolePlane->num_vertices = 8;
	PolePlane->num_triangles = 8;

	PolePlane->active = 1;

	uvis = LQHCreateVisual(PolePlane);
    
	if (!uvis)
        goto generic_error;

	for (i = 0; i < MAX_NO_TREES_ONSCREEN; i++) 
	{
		poles[i] = (MySprite*)malloc(sizeof(MySprite));
		if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, parent, &(poles[i]->frame))))
			goto generic_error;
	
		if(FAILED(poles[i]->frame->lpVtbl->AddVisual(poles[i]->frame, (LPDIRECT3DRMVISUAL)uvis)))
			goto generic_error;
	}

	RELEASE(uvis);
    return TRUE;

generic_error:
    Msg("A failure occurred while creating the scene.\n");
	RELEASE(uvis);
    return FALSE;
}

// **********************************************************
// Name:		LQHCreateTreeFrame
//		
// Author:		LiuQingHua					
//
// Date:		1996.8                      
//
// Description: Create the tree frame
//
// Arguments:		None
//
// Return:			None
//
// Side Effects:	None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

BOOL LQHCreateTreeFrame(LPDIRECT3DRMFRAME parent, D3DTEXTUREHANDLE htex)
{
	LPDIRECT3DRMUSERVISUAL uvis = NULL;
	int i;

	MallocPlane(&TreePlane);
	memset(TreePlane, 0, sizeof(Plane));

	TreePlane->hTex = htex;
	
	TreePlane->num_vertices = 8;
	TreePlane->num_triangles = 8;

	TreePlane->active = 1;

	uvis = LQHCreateVisual(TreePlane);
    
	if (!uvis)
        goto generic_error;

	for (i = 0; i < MAX_NO_TREES_ONSCREEN; i++) 
	{
		trees[i] = (MySprite*)malloc(sizeof(MySprite));
		if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, parent, &(trees[i]->frame))))
			goto generic_error;
	
		if(FAILED(trees[i]->frame->lpVtbl->AddVisual(trees[i]->frame, (LPDIRECT3DRMVISUAL)uvis)))
			goto generic_error;
	}

	RELEASE(uvis);
    return TRUE;

generic_error:
    Msg("A failure occurred while creating the scene.\n");
	RELEASE(uvis);
    return FALSE;
}

// **********************************************************
// Name:		FreeTreesPoles     
//		
// Author:		Spudde     				
//
// Date:		1996.8                      
//
// Description: Free the resource occupied by trees and poles
//
// Arguments:		None
//
// Return:			None
//
// Side Effects:	None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void FreeTreesPoles()
{
	int i;

	for (i=0;i<MAX_NO_TREES_ONSCREEN;i++) 
	{
		MDFreeD3DFrame(trees[i]->frame);
		MDFreeD3DFrame(poles[i]->frame);
		free(trees[i]);
		free(poles[i]);
		trees[i] = NULL;
		poles[i] = NULL;
	}
	ReleaseOneTexture(&TreeTex);
	ReleaseOneTexture(&PoleTex);
}

// **********************************************************
// Name:		CreateTrees
//		
// Author:		Spudde					
//
// Date:		1996.8                      
//
// Description: Create the trees
//
// Arguments:		None
//
// Return:			None
//
// Side Effects:	None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void CreateTrees(int numtrees, RLFrame parent)
{
	int i;
	static j = 0;

    LPDIRECT3DRMFRAME frame = NULL;
    LPDIRECT3DRMMATERIAL mat = NULL;

	for (i=0;i<LANDXSIZE*LANDZSIZE/8; i++) {
		treemap[i] = 0;
		polemap[i] = 0;
	}

	memset(&TreeTex, 0, sizeof(TEXTURESTRUCT));
	MyLoadTexture(Wdevice, ConstructLevelName("tree.bmp"), &TreeTex, 1);
	
	memset(&PoleTex, 0, sizeof(TEXTURESTRUCT));
	MyLoadTexture(Wdevice, ConstructLevelName("pole.bmp"), &PoleTex, 1);


	LQHCreateTreeFrame(parent, TreeTex.hTex);
	LQHCreatePoleFrame(parent, PoleTex.hTex);

	nexttree = 0;
}

// **********************************************************
// Name:		MapTrees
//		
// Author:		Spudde					
//
// Date:		1996.8                      
//
// Description: Create and map the trees into the scene
//
// Arguments:		None
//
// Return:			None
//
// Side Effects:	None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void MapTrees()
{
	int i, j, whichtile, whichtileside[4], x, z, deltax, deltaz;
	RLValue altitude, n;

	CreateTrees(MAX_NO_TREES_ONSCREEN, behindthescene);
	
	for (x=0;x<LANDXSIZE;x++)
		for (z=0;z<LANDZSIZE;z++) 
		{
			altitude = landscale*MapHeight(x-LANDXCENTER, z-LANDZCENTER);
			for (i=0;i<4;i++)
				if (altitude >= texturecutoffs[i]) whichtile = i;

			for(j=0;j<4;j++) 
			{
				if (j==0) { deltax = 1; deltaz = 0; }
				if (j==1) { deltax = 0; deltaz = 1; }
				if (j==2) { deltax = -1; deltaz = 0; }
				if (j==3) { deltax = 0; deltaz = -1; }
				altitude = landscale*MapHeight(x+deltax-LANDXCENTER, z+deltaz-LANDZCENTER);
				for (i=0;i<4;i++)
					if (altitude >= texturecutoffs[i]) whichtileside[j] = i;
			}
			
			n = RLVal((rand()%256)/256.0);
			if ((detail!=1) && (n < prob[GameStates.CurrentLevel][whichtile]))
				treemap[LANDXSIZE/8*z + x/8] |= 1<<(x&7);

			
			switch (GameStates.CurrentLevel) 
			{
				case Trainer:
					break;
				case Mojave:
				case Rockies:
					if ((whichtile == 0) && ((whichtileside[0] == 1) && (whichtileside[1] == 1)))
						polemap[LANDXSIZE/8*z + x/8] |= 1<<(x&7);
					if ((whichtile == 0) && ((whichtileside[2] == 1) && (whichtileside[3] == 1)))
						polemap[LANDXSIZE/8*z + x/8] |= 1<<(x&7);
					break;
				case Hawaii:
					if ((whichtile == 2) && 
						(((whichtileside[0] == 1) && (whichtileside[1] == 1)) || 
						 ((whichtileside[2] == 1) && (whichtileside[3] == 1))))
						polemap[LANDXSIZE/8*z + x/8] |= 1<<(x&7);
					break;
				case SanFrancisco:
					if ((whichtile == 2) && 
						(((whichtileside[0] == 1) && (whichtileside[1] == 1)) || 
						 ((whichtileside[2] == 1) && (whichtileside[3] == 1))))
						polemap[LANDXSIZE/8*z + x/8] |= 1<<(x&7);
					else	
					if ((whichtile == 2) && ((whichtileside[0] == 1) || (whichtileside[1] == 1) || (whichtileside[2] == 1) || (whichtileside[3] == 1)))
						treemap[LANDXSIZE/8*z + x/8] |= 1<<(x&7);
					break;
				case NewYork:
					if ((whichtile == 2) && 
						(((whichtileside[0] == 1) && (whichtileside[1] == 1)) || 
						 ((whichtileside[2] == 1) && (whichtileside[3] == 1))))
						polemap[LANDXSIZE/8*z + x/8] |= 1<<(x&7);
					break;
				case Tokyo:
					
					if ((whichtile == 2) && 
						(((whichtileside[0] == 1) && (whichtileside[1] == 1)) || 
						 ((whichtileside[2] == 1) && (whichtileside[3] == 1))))
						polemap[LANDXSIZE/8*z + x/8] |= 1<<(x&7);
					break;
			}
		}
}

// **********************************************************
// Name:		AddPole
//		
// Author:		Spudde					
//
// Date:		1996.8                      
//
// Description: Add poles into the scene
//
// Arguments:		None
//
// Return:			None
//
// Side Effects:	None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void AddPole(int x, int z)
{
	int xi, zi;

	xi=x+LANDXCENTER;
	zi=z+LANDZCENTER;
	
	if (xi<0) return;
	if (xi>=LANDXSIZE) return;
	if (zi<0) return;
	if (zi>=LANDZSIZE) return;
	
	polemap[LANDXSIZE/8*zi + xi/8] |= 1<<(xi&7);
}

// **********************************************************
// Name:		PlantTree   
//		
// Author:		Spudde					
//
// Date:		1996.8                      
//
// Description: Set the position of trees
//
// Arguments:		None
//
// Return:			None
//
// Side Effects:	None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void PlantTree(int x, int z)
{
	int i, xi, zi;

	xi=x+LANDXCENTER;
	zi=z+LANDZCENTER;

	if (xi<0) return;
	if (xi>=LANDXSIZE) return;
	if (zi<0) return;
	if (zi>=LANDZSIZE) return;
	
	if (treemap[LANDXSIZE/8*zi + xi/8] & (1<<(xi&7))) 
	{
		if (nexttree != -1) {
			RLFrameAddChild(Wscene, trees[nexttree]->frame);
			RLFrameSetOrientation(trees[nexttree]->frame, Wscene,
				RLVal(0.0), RLVal(1.0), RLVal(0.0), RLVal(0.0), RLVal(0.0), RLVal(1.0));
				RLFrameAddScale(trees[nexttree]->frame, RLCombineAfter, RLVal(1), RLVal(0.12+0.01*((x*z*treemap[LANDXSIZE/8*zi + xi/8])&7)), RLVal(1));
			RLFrameSetPosition(trees[nexttree]->frame, Wscene,
				RLVal(x), MapHeight(x, z), RLVal(z));
			trees[nexttree]->flag1 = xi;
			trees[nexttree]->flag2 = zi;
			nexttree = -1;

		} else {
			for (i=0;i<MAX_NO_TREES_ONSCREEN;i++) {
				if (RLFrameGetParent(trees[i]->frame) == behindthescene) {
			        RLFrameAddChild(Wscene, trees[i]->frame);
					RLFrameSetOrientation(trees[i]->frame, Wscene,
						RLVal(0.0), RLVal(1.0), RLVal(0.0), RLVal(0.0), RLVal(0.0), RLVal(1.0));
						RLFrameAddScale(trees[i]->frame, RLCombineAfter, RLVal(1), RLVal(0.12+0.01*((x*z*treemap[LANDXSIZE/8*zi + xi/8])&7)), RLVal(1));
					RLFrameSetPosition(trees[i]->frame, Wscene,
						RLVal(x), MapHeight(x, z), RLVal(z));
					trees[i]->flag1 = xi;
					trees[i]->flag2 = zi;
					return;
				}
			}
		}
	}
	//if (levelwereon>=4) {
		if (polemap[LANDXSIZE/8*zi + xi/8] & (1<<(xi&7))) {
			if (nextpole != -1) {
				RLFrameAddChild(Wscene, poles[nextpole]->frame);
				RLFrameSetOrientation(poles[nextpole]->frame, Wscene,
					RLVal(0.0), RLVal(1.0), RLVal(0.0), RLVal(0.0), RLVal(0.0), RLVal(1.0));
				RLFrameAddScale(poles[nextpole]->frame, RLCombineAfter, RLVal(1), RLVal(0.15), RLVal(1));
				RLFrameSetPosition(poles[nextpole]->frame, Wscene,
					RLVal(x), MapHeight(x, z), RLVal(z));
				poles[nextpole]->flag1 = xi;
				poles[nextpole]->flag2 = zi;
				nextpole = -1;
			} else {
				for (i=0;i<MAX_NO_TREES_ONSCREEN;i++) {
					if (RLFrameGetParent(poles[i]->frame) == behindthescene) {
						RLFrameAddChild(Wscene, poles[i]->frame);
						RLFrameSetOrientation(poles[i]->frame, Wscene,
							RLVal(0.0), RLVal(1.0), RLVal(0.0), RLVal(0.0), RLVal(0.0), RLVal(1.0));
						RLFrameAddScale(poles[i]->frame, RLCombineAfter, RLVal(1), RLVal(0.15), RLVal(1));
						RLFrameSetPosition(poles[i]->frame, Wscene,
							RLVal(x), MapHeight(x, z), RLVal(z));
						poles[i]->flag1 = xi;
						poles[i]->flag2 = zi;
						return;
					}
				}
			}
		}
	//}
}

// **********************************************************
// Name:		RemoveTrees 
//		
// Author:		Spudde					
//
// Date:		1996.8                      
//
// Description: Remove the trees from the scene
//
// Arguments:		None
//
// Return:			None
//
// Side Effects:	None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void RemoveTrees(int x0, int z0, int x1, int z1)
{
	int i;
	
	x0+=LANDXCENTER;
	x1+=LANDXCENTER;
	z0+=LANDZCENTER;
	z1+=LANDZCENTER;

	if (x0<0) x0 = 0;
	if (x0>=LANDXSIZE) x0 = LANDXSIZE-1;
	if (x1<0) x1 = 0;
	if (x1>=LANDXSIZE) x1 = LANDXSIZE-1;
	if (z0<0) z0 = 0;
	if (z0>=LANDZSIZE) z0 = LANDZSIZE-1;
	if (z1<0) z1 = 0;
	if (z1>=LANDZSIZE) z1 = LANDZSIZE-1;
	
	for (i=0;i<MAX_NO_TREES_ONSCREEN;i++) {
		if (RLFrameGetParent(trees[i]->frame) == Wscene) 
			if ((trees[i]->flag1 < x0) || (trees[i]->flag2 < z0) ||
				(trees[i]->flag1 > x1) || (trees[i]->flag2 > z1)) {
				RLFrameAddChild( behindthescene, trees[i]->frame);
				nexttree = i;
			}
	}
	//if (levelwereon>=4) {
		for (i=0;i<MAX_NO_TREES_ONSCREEN;i++) {
			if (RLFrameGetParent(poles[i]->frame) == Wscene) 
				if ((poles[i]->flag1 < x0) || (poles[i]->flag2 < z0) ||
					(poles[i]->flag1 > x1) || (poles[i]->flag2 > z1)) {
					RLFrameAddChild( behindthescene, poles[i]->frame);
					nextpole = i;
					return;
				}
		}
	//}
}


 
TEXTURESTRUCT PowerTex;

// **********************************************************
// Name:		CreatePowerUps
//		
// Author:		Spudde					
//
// Date:		1996.8                      
//
// Description: Create the powerups
//
// Arguments:		None
//
// Return:			None
//
// Side Effects:	None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void CreatePowerUps()
{
	int i;

//	levelwereon = GameStates.CurrentLevel;

	MyLoadTexture(Wdevice, ConstructLevelName("power.bmp"), &PowerTex, 0);
	
	for (i=0;i<MAX_NO_POWERUPS;i++)	
	{
		powerups[i].frame = RLCreateFrame(behindthescene);
		powerups[i].rotframe = RLCreateFrame(powerups[i].frame);
		if (i==0) 
		{
			powerups[i].dlistidx = LoadIntoDList("powerup.x", powerups[i].rotframe, &PowerTex, "transparent");
		}
		else 
		{
			//powerups[i].dlistidx = DupDListForCopyUVis (powerups[0].dlistidx, powerups[i].rotframe);
			powerups[i].dlistidx = DupDList(powerups[0].dlistidx, powerups[i].rotframe);
			allmiscdlists[powerups[i].dlistidx]->builder=NULL;
		}
		powerups[i].flag1 = cuint*(PowerUpPlace[GameStates.CurrentLevel][i][1]/cuint);
		powerups[i].flag2 = cuint*(PowerUpPlace[GameStates.CurrentLevel][i][0]/cuint);
		powerups[i].active = (i<NumPowerUp[GameStates.CurrentLevel]);
	}
	DeleteBinary (allmiscdlists[powerups[0].dlistidx]->builder);
	allmiscdlists[powerups[0].dlistidx]->builder=NULL;

}

// **********************************************************
// Name:		PlantPowerUp
//		
// Author:		Spudde					
//
// Date:		1996.8                      
//
// Description: Plant the powerups in the scene
//
// Arguments:		None
//
// Return:			None
//
// Side Effects:	None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void PlantPowerUp(int x, int z)
{
	int i, xi, zi;

	xi=(x+LANDXCENTER)/cuint;
	zi=(z+LANDZCENTER)/cuint;
	
	if (xi<0) return;
	if (xi>=LANDXSIZE) return;
	if (zi<0) return;
	if (zi>=LANDZSIZE) return;

	for (i=0;i<NumPowerUp[GameStates.CurrentLevel];i++) {
		if ((powerups[i].active) && ((powerups[i].flag1)/cuint == xi) && ((powerups[i].flag2)/cuint == zi)) {
			if (RLFrameGetParent(powerups[i].frame) == behindthescene) {
				RLFrameAddChild(Wscene, powerups[i].frame);
				RLFrameAddChild(powerups[i].frame, powerups[i].rotframe);
				RLFrameSetPosition(powerups[i].rotframe, powerups[i].frame,
					RLVal(0), RLVal(0.06), RLVal(0));
				RLFrameSetRotation(powerups[i].rotframe, powerups[i].frame, 
					RLVal(0.0), RLVal(1.0), RLVal(0.0), RLVal(3.141592654/2.0));
				RLFrameSetPosition(powerups[i].frame, Wscene,
					RLVal(x), MapHeight(x, z), RLVal(z));

				return;
			}
		}
	}
}

// **********************************************************
// Name:		RemovePowerUps
//		
// Author:		Spudde					
//
// Date:		1996.8                      
//
// Description: Remove the powerups from the scene
//
// Arguments:		None
//
// Return:			None
//
// Side Effects:	None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void RemovePowerUps(int x0, int z0, int x1, int z1)
{
	RLVector p;
	extern RLFrame Robotframe;
	extern TARGET targets[];
	int i;
	RLFrame parent_frame;

	x0 += LANDXCENTER;
	x1 += LANDXCENTER;
	z0 += LANDZCENTER;
	z1 += LANDZCENTER;

	if (x0<0) x0 = 0;
	if (x0>=LANDXSIZE) x0 = LANDXSIZE-1;
	if (x1<0) x1 = 0;
	if (x1>=LANDXSIZE) x1 = LANDXSIZE-1;
	if (z0<0) z0 = 0;
	if (z0>=LANDZSIZE) z0 = LANDZSIZE-1;
	if (z1<0) z1 = 0;
	if (z1>=LANDZSIZE) z1 = LANDZSIZE-1;

	for (i=0;i<NumPowerUp[GameStates.CurrentLevel];i++) {
		p.x = RLVal(powerups[i].flag1 - LANDXCENTER);
		p.z = RLVal(powerups[i].flag2 - LANDZCENTER);
		p.y = RLVal(0);

		{
			extern RLFrame goodguyframe;

//			if (PlayAsMonster)
//			{
//				RLFrameInverseTransform(monstframe, &(p), &(p));
//			}
//			else
//			{
//				RLFrameInverseTransform(goodguyframe, &(p), &(p));
//			}

			//RLFrameGetPosition(powerups[i].frame,goodguyframe,&(p));
         RLFrameInverseTransform(goodguyframe, &(p), &(p));
		}
		//end of Eric

	    targets[i+4].p.x = p.x;
	    targets[i+4].p.y = p.y;
	    targets[i+4].p.z = p.z;
	    targets[i+4].life = powerups[i].active;
	    targets[i+4].type = 2;
		parent_frame = RLFrameGetParent(powerups[i].frame);
		if (parent_frame == Wscene) 
			if ((powerups[i].flag1 < x0) || (powerups[i].flag2 < z0) ||
				(powerups[i].flag1 > x1) || (powerups[i].flag2 > z1)) {
				RLFrameAddChild( behindthescene, powerups[i].frame);
				//return;
			}
	}

	//LGH add release
	RLObjectDestroy((RLObject)parent_frame);
}

// **********************************************************
// Name:		PowerUpHere
//		
// Author:		Spudde					
//
// Date:		1996.8                      
//
// Description: At this place Robot can add power
//
// Arguments:		None
//
// Return:			None
//
// Side Effects:	None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

int PowerUpHere(RLFrame Robotishere)
{
	int i;
	RLVector position;
	RLValue xi, zi;

	RLFrameGetPosition(Robotishere, Wscene, &position);
	xi=position.x+RLVal(LANDXCENTER);
	zi=position.z+RLVal(LANDZCENTER);
	
	if (xi<0) return(0);
	if (xi>=LANDXSIZE) return(0);
	if (zi<0) return(0);
	if (zi>=LANDZSIZE) return(0);
	
	for (i=0;i<NumPowerUp[GameStates.CurrentLevel];i++) {
		if ((powerups[i].active) && (fabs(powerups[i].flag1 - xi) < RLVal(4.0)) && (fabs(powerups[i].flag2 - zi) < RLVal(4.0))) {
			RLFrameAddChild( behindthescene, powerups[i].frame);
			powerups[i].active = 0;

			//Add by Eric 11/13/96
			if (GameStates.IsNetplay)
			{
				EventSndBuf.MsgId = NEW_MSG;
		        EventSndBuf.Event = EVENT_POWERUP;
		        //EventSndBuf.Param = (WORD)i;
			}
			//end of Eric

			return(1);
		}
	}
	return(0);
}

// **********************************************************
// Name:		PowerupFrame
//		
// Author:		Spudde					
//
// Date:		1996.8                      
//
// Description: Set the position of powerup
//
// Arguments:		None
//
// Return:			None
//
// Side Effects:	None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

RLFrame PowerupFrame(int i)
{
	int x, z;

	x = powerups[i].flag1 - LANDXCENTER;
	z = powerups[i].flag2 - LANDZCENTER;
	RLFrameSetPosition(powerups[i].frame, Wscene,
		RLVal(x), MapHeight(x, z), RLVal(z));

	return powerups[i].frame;
}



RLValue TheHorizon;	 

typedef struct _SCROLL {
	LPDIRECT3DRMFRAME scene;
	LPDIRECT3DRMFRAME camera;
    LPDIRECT3DRMDEVICE dev;
	LPDIRECT3DRMVIEWPORT view;
    LPDIRECT3DEXECUTEBUFFER eb;
	TEXTURESTRUCT tex;
    LPDIRECT3DMATERIAL mat;
} SCROLL;

static SCROLL *MyScroll = NULL;
#define SCROLLY_NUM_VERTICES 7

RLValue screenx;
RLValue screeny;
RLValue zdepth, hdepth;
D3DTLVERTEX horizondestination[6];
LPDIRECT3DRMFRAME	BackgroundFrame = NULL;
int wetpipe=0, oldwetpipe=0;

extern int cpx, cpz;
extern RLViewport Wview;

static int CalculateBackgroundCoords(RECT* P_gamewindow, RECT *srcrect, DWORD *destx, DWORD *desty)
{
   int gamewinheight, gamewinwidth;

	RLVector at, up;
	RLValue angle;
	int isclipped;
	RLVector place;
	RLVector4d place4d;

   extern RLFrame Wscene;
   extern RLFrame Wcamera;
   extern RLValue sealevel;

   gamewinwidth = P_gamewindow->right - P_gamewindow->left;
   gamewinheight = P_gamewindow->bottom - P_gamewindow->top;

   Wcamera->lpVtbl->GetOrientation(Wcamera, Wscene, &at, &up);
   Wcamera->lpVtbl->GetPosition(Wcamera, Wscene, &place);

   at.y = RLVal(0.0);
   RLVectorNormalise(&at);
   place.x += RLVal(3.0*(cpx+cpz)*at.x);
   place.z += RLVal(3.0*(cpx+cpz)*at.z);
   place.y = sealevel;

	Wview->lpVtbl->Transform(Wview, &place4d, &place);
	TheHorizon = place4d.y / place4d.w;
   if (place4d.w < 0.0)
      TheHorizon = -TheHorizon;
	place4d.y = (VM_H3D/2)*place4d.w;
	//RLViewportInverseTransform(Wview, &place, &place4d);

    if (at.x != 0.0) 
	{
		angle = RLMultiply(RLVal(4.0/6.28318530718), 
		                   RLVal(atan(-at.z/at.x)));
	}
	 else
	 {
		if (at.x * at.z < 0) 
		{
			angle = RLVal(-1.0);
		}
		else
		{
			angle = RLVal(1.0);
		}
	 }
    if (angle< RLVal(0.0))
       angle += RLVal(1.0);
   
	isclipped = 0;
   

   if ((TheHorizon > P_gamewindow->top) && (TheHorizon < P_gamewindow->bottom))  // Horizon is on screen
   {
      srcrect->top = P_gamewindow->bottom - (long)TheHorizon;
      srcrect->bottom = gamewinheight;

      // Blit right section of bitmap onto left side of screen (for wraparound)
         //srcrect->left = (long)(((float)gamewinwidth)*angle);
         //srcrect->right = gamewinwidth;
         srcrect->left = 0;
         srcrect->right = (long)(((float)gamewinwidth)*angle);

      *destx = P_gamewindow->left + (gamewinwidth - srcrect->right);
      *desty = P_gamewindow->top;

      return 2;      // ABOVE
   }
   else
   {
      if (TheHorizon >= P_gamewindow->bottom)  // Horizon is below bottom of screen
      {
         if (TheHorizon - P_gamewindow->bottom >= gamewinheight) 
         {
            return 4;   // WAY BELOW
         }
         srcrect->top = 0;
         srcrect->bottom = gamewinheight - ((long)TheHorizon - P_gamewindow->bottom);

         // Blit right section of bitmap onto left side of screen 
         srcrect->left = 0;
         srcrect->right = (long)(((float)gamewinwidth)*angle);
         
         *destx = P_gamewindow->left + (gamewinwidth - srcrect->right);
         *desty = (unsigned long)TheHorizon - gamewinheight;
         return 3;      // BELOW
      }
      else
      {
         // Horizon is above the top of the screen
        return 1;       // WAY ABOVE
      }
   }
  return 0;
}

D3DMATERIAL topbackmat, bottombackmat, midbackmat;
TEXTURESTRUCT  backtex;
static D3DEXECUTEBUFFERDESC backflatdebDesc, backimgdebDesc;
static D3DEXECUTEDATA backflatExData, backimgExData;
static LPDIRECT3DEXECUTEBUFFER lpbackflatExBuf, lpbackimgExBuf;

void SetupBackground()
{
   RECT    *P_gamewindow, fullrect;
   LPDIRECT3DDEVICE lpD3DDev = d3dappi.lpD3DDevice;
   IDirect3DMaterial* lpbackmat=NULL;
   //D3DMATERIALHANDLE midbackmathandle;
   DWORD size;
   LPVOID lpBufStart, lpInsStart, lpPointer;
   D3DTLVERTEX backflat[4], backimg[4];

   wetpipe = oldwetpipe = 0;

   if (VSize < 4) 
      P_gamewindow = &(GWinSize[RMode-1][VSize-1]);
   else
   {
      P_gamewindow = &fullrect;
      P_gamewindow->top = 0;
      P_gamewindow->bottom = VM_H3D;
      P_gamewindow->left = 0;
      P_gamewindow->right = VM_W3D;
   }

   memset(&topbackmat, 0, sizeof(D3DMATERIAL));
   memset(&bottombackmat, 0, sizeof(D3DMATERIAL));
   memset(&midbackmat, 0, sizeof(D3DMATERIAL));
   bottombackmat.dwSize = topbackmat.dwSize = midbackmat.dwSize = sizeof(D3DMATERIAL);
   bottombackmat.ambient.a = topbackmat.ambient.a = (D3DVALUE)0.664;
   bottombackmat.diffuse.a = topbackmat.diffuse.a = (D3DVALUE)0.664;
   bottombackmat.specular.r = topbackmat.specular.r = midbackmat.specular.r = (D3DVALUE)0.0;
   bottombackmat.specular.g = topbackmat.specular.g = midbackmat.specular.g = (D3DVALUE)0.0;
   bottombackmat.specular.b = topbackmat.specular.b = midbackmat.specular.b = (D3DVALUE)0.0;
   bottombackmat.power = topbackmat.power = midbackmat.power = (float)0.0;
   bottombackmat.dwRampSize = topbackmat.dwRampSize = midbackmat.dwRampSize = 1;
   bottombackmat.hTexture = topbackmat.hTexture = 0L;
	midbackmat.ambient.r = midbackmat.diffuse.r = (D3DVALUE)1.0; 
	midbackmat.ambient.g = midbackmat.diffuse.g = (D3DVALUE)1.0; 
	midbackmat.ambient.b = midbackmat.diffuse.b = (D3DVALUE)1.0;
	midbackmat.ambient.a = midbackmat.diffuse.a = (D3DVALUE)0.964;

   switch (GameStates.CurrentLevel)
   {
      case Trainer:
	      topbackmat.ambient.r = topbackmat.diffuse.r = (D3DVALUE)0.0; // 0/255
	      topbackmat.ambient.g = topbackmat.diffuse.g = (D3DVALUE)0.0; // 0/255
	      topbackmat.ambient.b = topbackmat.diffuse.b = (D3DVALUE)0.0; // 0/255
		   bottombackmat.ambient.r = bottombackmat.diffuse.r = (D3DVALUE)0.0; // 0/255
		   bottombackmat.ambient.g = bottombackmat.diffuse.g = (D3DVALUE)0.0; // 0/255
		   bottombackmat.ambient.b = bottombackmat.diffuse.b = (D3DVALUE)0.0; // 0/255
         break;
      case Mojave:
	      topbackmat.ambient.r = topbackmat.diffuse.r = (D3DVALUE)(30.0/255.0);  //0.11373; // 29/255
	      topbackmat.ambient.g = topbackmat.diffuse.g = (D3DVALUE)(12.0/255.0);  //0.04314; // 11/255
	      topbackmat.ambient.b = topbackmat.diffuse.b = (D3DVALUE)(153.0/255.0);  //0.59608; // 152/255
		   bottombackmat.ambient.r = bottombackmat.diffuse.r = (D3DVALUE)(184.0/255.0); //0.71764; // 183/255
		   bottombackmat.ambient.g = bottombackmat.diffuse.g = (D3DVALUE)(182.0/255.0); //0.71764; // 183/255
		   bottombackmat.ambient.b = bottombackmat.diffuse.b = (D3DVALUE)(131.0/255.0); //0.51373; // 131/255
         break;
      case Rockies:
	      topbackmat.ambient.r = topbackmat.diffuse.r = (D3DVALUE)0.07451; // 19/255
	      topbackmat.ambient.g = topbackmat.diffuse.g = (D3DVALUE)0.11373; // 29/255
	      topbackmat.ambient.b = topbackmat.diffuse.b = (D3DVALUE)0.67059; // 171/255
		   bottombackmat.ambient.r = bottombackmat.diffuse.r = (D3DVALUE)0.93725; // 239/255
		   bottombackmat.ambient.g = bottombackmat.diffuse.g = (D3DVALUE)0.96863; // 247/255
		   bottombackmat.ambient.b = bottombackmat.diffuse.b = (D3DVALUE)1.00000; // 255/255
         break;
      case Hawaii:
	      topbackmat.ambient.r = topbackmat.diffuse.r = (D3DVALUE)0.32941; // 84/255
	      topbackmat.ambient.g = topbackmat.diffuse.g = (D3DVALUE)0.44706; // 114/255
	      topbackmat.ambient.b = topbackmat.diffuse.b = (D3DVALUE)0.67059; // 173/255
		   bottombackmat.ambient.r = bottombackmat.diffuse.r = (D3DVALUE)0.06275; // 16/255
		   bottombackmat.ambient.g = bottombackmat.diffuse.g = (D3DVALUE)0.19216; // 49/255
		   bottombackmat.ambient.b = bottombackmat.diffuse.b = (D3DVALUE)0.58039; // 148/255
         break;
      case SanFrancisco:
	      topbackmat.ambient.r = topbackmat.diffuse.r = (D3DVALUE)0.21176; // 54/255
	      topbackmat.ambient.g = topbackmat.diffuse.g = (D3DVALUE)0.28235; // 72/255
	      topbackmat.ambient.b = topbackmat.diffuse.b = (D3DVALUE)0.77647; // 198/255
		   bottombackmat.ambient.r = bottombackmat.diffuse.r = (D3DVALUE)0.27843; // 71/255
		   bottombackmat.ambient.g = bottombackmat.diffuse.g = (D3DVALUE)0.27843; // 71/255
		   bottombackmat.ambient.b = bottombackmat.diffuse.b = (D3DVALUE)0.24314; // 62/255
         break;
      case NewYork:
	      topbackmat.ambient.r = topbackmat.diffuse.r = (D3DVALUE)0.12549; // 32/255
	      topbackmat.ambient.g = topbackmat.diffuse.g = (D3DVALUE)0.00000; // 0/255
	      topbackmat.ambient.b = topbackmat.diffuse.b = (D3DVALUE)0.00000; // 0/255
		   bottombackmat.ambient.r = bottombackmat.diffuse.r = (D3DVALUE)0.09412; // 24/255
		   bottombackmat.ambient.g = bottombackmat.diffuse.g = (D3DVALUE)0.10196; // 26/255
		   bottombackmat.ambient.b = bottombackmat.diffuse.b = (D3DVALUE)0.09804; // 25/255
         break;
      case Tokyo:
	      topbackmat.ambient.r = topbackmat.diffuse.r = (D3DVALUE)0.03922; // 10/255
	      topbackmat.ambient.g = topbackmat.diffuse.g = (D3DVALUE)0.07059; // 18/255
	      topbackmat.ambient.b = topbackmat.diffuse.b = (D3DVALUE)0.07451; // 19/255
		   bottombackmat.ambient.r = bottombackmat.diffuse.r = (D3DVALUE)0.03529; // 9/255
		   bottombackmat.ambient.g = bottombackmat.diffuse.g = (D3DVALUE)0.06667; // 17/255
		   bottombackmat.ambient.b = bottombackmat.diffuse.b = (D3DVALUE)0.06667; // 17/255
         break;
   }
   if (d3dappi.ThisDriver.bIsHardware && vramsize > 2097152 )
   //if (d3dappi.ThisDriver.bIsHardware)
   {
		char backname[32];
		
		midbackmat.ambient.r = midbackmat.diffuse.r = (D3DVALUE)1.0; 
		midbackmat.ambient.g = midbackmat.diffuse.g = (D3DVALUE)1.0; 
		midbackmat.ambient.b = midbackmat.diffuse.b = (D3DVALUE)1.0; 
		midbackmat.ambient.a = midbackmat.diffuse.a = (D3DVALUE)0.964; 
		/*
      if (VM_W3D==320)
		{
			strcpy(backname, "back10.bmp");
		}
		else
		if (VM_W3D==640)
		{
			strcpy(backname, "back20.bmp");
		}
      else
		if (VM_W3D==512)
		{
			strcpy(backname, "back30.bmp");
		}
      */
		strcpy(backname, "back.bmp");
	   //backname[5] += VSize-1;    // makes "back10.bmp", "back11.bmp", etc.
      memset(&backtex, 0, sizeof(TEXTURESTRUCT));
	   MyLoadTexture(Wdevice, ConstructLevelName(backname), &backtex, 1);
//	   MyLoadTexture(Wdevice, ConstructLevelName("sa191.bmp"), &backtex, 0);
      /*
      midbackmat.hTexture = backtex.hTex;

		if (FAILED(lpbackmat->lpVtbl->SetMaterial(lpbackmat, &midbackmat)))
			goto generic_error;
		if (FAILED(lpbackmat->lpVtbl->GetHandle(lpbackmat, lpD3DDev, &midbackmathandle)))
			goto generic_error;
      */

       /*
        * Setup vertices
        */
       memset(&backflat[0], 0, sizeof(D3DTLVERTEX) * 4);
       /* V 0 */
       backflat[0].sx = D3DVAL(P_gamewindow->left);
       backflat[0].sy = D3DVAL(P_gamewindow->top);
       backflat[0].sz = D3DVAL(250.0);
       backflat[0].rhw = D3DVAL(0.004);

       backflat[0].color = 
          D3DRGBA(midbackmat.ambient.r, midbackmat.ambient.g, midbackmat.ambient.b, midbackmat.ambient.a);
       backflat[0].specular = RGB_MAKE(0, 0, 0);
       backflat[0].tu = D3DVAL(0.0);
       backflat[0].tv = D3DVAL(0.0);
       /* V 1 */
       backflat[1].sx = D3DVAL(P_gamewindow->right);
       backflat[1].sy = D3DVAL(P_gamewindow->top);
       backflat[1].sz = D3DVAL(250.0);
       backflat[1].rhw = D3DVAL(0.004);
       backflat[1].color = 
                    D3DRGBA(midbackmat.ambient.r, midbackmat.ambient.g, midbackmat.ambient.b, midbackmat.ambient.a);
       backflat[1].specular = RGB_MAKE(0, 0, 0);
       backflat[1].tu = D3DVAL(1.0);
       backflat[1].tv = D3DVAL(1.0);
       /* V 2 */
       backflat[2].sx = D3DVAL(P_gamewindow->left);
       backflat[2].sy = D3DVAL((P_gamewindow->top+P_gamewindow->bottom)/2.0);
       backflat[2].sz = D3DVAL(250.0);
       backflat[2].rhw = D3DVAL(0.004);
       backflat[2].color = 
                    D3DRGBA(midbackmat.ambient.r, midbackmat.ambient.g, midbackmat.ambient.b, midbackmat.ambient.a);
       backflat[2].specular = RGB_MAKE(0, 0, 0);
       backflat[2].tu = D3DVAL(0.0);
       backflat[2].tv = D3DVAL(1.0);
       /* V 3 */
       backflat[3].sx = D3DVAL(P_gamewindow->right);
       backflat[3].sy = D3DVAL((P_gamewindow->top+P_gamewindow->bottom)/2.0);
       backflat[3].sz = D3DVAL(250.0);
       backflat[3].rhw = D3DVAL(0.004);
       backflat[3].color = 
                    D3DRGBA(midbackmat.ambient.r, midbackmat.ambient.g, midbackmat.ambient.b, midbackmat.ambient.a);
       backflat[3].specular = RGB_MAKE(0, 0, 0);
       backflat[3].tu = D3DVAL(0.0);
       backflat[3].tv = D3DVAL(0.0);
       /*
        * Create an execute buffer
        */
       size = sizeof(D3DTLVERTEX) * 4;
       size += sizeof(D3DINSTRUCTION) * 6;
       size += sizeof(D3DSTATE) * 8;
       size += sizeof(D3DPROCESSVERTICES);
       size += sizeof(D3DTRIANGLE) * 2;
       memset(&backflatdebDesc, 0, sizeof(D3DEXECUTEBUFFERDESC));
       backflatdebDesc.dwSize = sizeof(D3DEXECUTEBUFFERDESC);
       backflatdebDesc.dwFlags = D3DDEB_BUFSIZE;
       backflatdebDesc.dwBufferSize = size;
       if (lpD3DDev->lpVtbl->CreateExecuteBuffer(lpD3DDev, &backflatdebDesc, &lpbackflatExBuf,
                                              NULL) != D3D_OK) {
           goto generic_error;
       }
       if (lpbackflatExBuf->lpVtbl->Lock(lpbackflatExBuf, &backflatdebDesc) != D3D_OK) {
           goto generic_error;
       }
       lpBufStart = backflatdebDesc.lpData;
       memset(lpBufStart, 0, size);
       lpPointer = lpBufStart;

       /*
        * Copy vertices to execute buffer
        */
       //VERTEX_DATA(&backflat[0], 4, lpPointer);
       memcpy(lpPointer, &backflat[0], sizeof(D3DTLVERTEX) * (4)); 
       lpPointer = (void *)(((LPD3DTLVERTEX) (lpPointer)) + (4));
       /*
        * Setup instructions in execute buffer
        */
       lpInsStart = lpPointer;
       OP_STATE_RENDER(6, lpPointer);
            STATE_DATA(D3DRENDERSTATE_BLENDENABLE, FALSE, lpPointer);
            STATE_DATA(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA,lpPointer);
            STATE_DATA(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA,lpPointer);
            STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATEALPHA, lpPointer);
            STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE, 0L, lpPointer);
            STATE_DATA(D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT, lpPointer);
			   //STATE_DATA(D3DRENDERSTATE_ZWRITEENABLE, FALSE, lpPointer);
			   //STATE_DATA(D3DRENDERSTATE_ZENABLE, FALSE, lpPointer);
       OP_PROCESS_VERTICES(1, lpPointer);
           PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY |
                             D3DPROCESSVERTICES_UPDATEEXTENTS, 0, 4, lpPointer);
       /*
        * Make sure that the triangle data (not OP) will be QWORD aligned
        */
       if (QWORD_ALIGNED(lpPointer)) {
           OP_NOP(lpPointer);
       }
       OP_TRIANGLE_LIST(2, lpPointer);
           ((LPD3DTRIANGLE)lpPointer)->v1 = 0;
           ((LPD3DTRIANGLE)lpPointer)->v2 = 1;
           ((LPD3DTRIANGLE)lpPointer)->v3 = 2;
           ((LPD3DTRIANGLE)lpPointer)->wFlags = D3DTRIFLAG_EDGEENABLETRIANGLE;
           lpPointer = ((char*)lpPointer) + sizeof(D3DTRIANGLE);
           ((LPD3DTRIANGLE)lpPointer)->v1 = 1;
           ((LPD3DTRIANGLE)lpPointer)->v2 = 3;
           ((LPD3DTRIANGLE)lpPointer)->v3 = 2;
           ((LPD3DTRIANGLE)lpPointer)->wFlags = D3DTRIFLAG_EDGEENABLETRIANGLE;
           lpPointer = ((char*)lpPointer) + sizeof(D3DTRIANGLE);

       OP_EXIT(lpPointer);
       /*
        * Setup the execute data
        */
       lpbackflatExBuf->lpVtbl->Unlock(lpbackflatExBuf);
       memset(&backflatExData, 0, sizeof(D3DEXECUTEDATA));
       backflatExData.dwSize = sizeof(D3DEXECUTEDATA);
       backflatExData.dwVertexCount = NUM_VERTICES;
       backflatExData.dwInstructionOffset = (ULONG) ((char *)lpInsStart - (char *)lpBufStart);
       backflatExData.dwInstructionLength = (ULONG) ((char *)lpPointer - (char *)lpInsStart);
       lpbackflatExBuf->lpVtbl->SetExecuteData(lpbackflatExBuf, &backflatExData);

       /*
        * Setup vertices
        */
       memset(&backimg[0], 0, sizeof(D3DTLVERTEX) * 4);
       /* V 0 */
       backimg[0].sx = D3DVAL(P_gamewindow->left);
       backimg[0].sy = D3DVAL((P_gamewindow->top+P_gamewindow->bottom)/2.0);
       backimg[0].sz = D3DVAL(250.0);
       backimg[0].rhw = D3DVAL(0.004);
       backimg[0].color = 
                    D3DRGBA(midbackmat.ambient.r, midbackmat.ambient.g, midbackmat.ambient.b, midbackmat.ambient.a);
       backimg[0].specular = RGB_MAKE(0, 0, 0);
       backimg[0].tu = D3DVAL(0.01);
       backimg[0].tv = D3DVAL(0.0);
       /* V 1 */
       backimg[1].sx = D3DVAL(P_gamewindow->right);
       backimg[1].sy = D3DVAL((P_gamewindow->top+P_gamewindow->bottom)/2.0);
       backimg[1].sz = D3DVAL(250.0);
       backimg[1].rhw = D3DVAL(0.004);
       backimg[1].color = 
                    D3DRGBA(midbackmat.ambient.r, midbackmat.ambient.g, midbackmat.ambient.b, midbackmat.ambient.a);
       backimg[1].specular = RGB_MAKE(0, 0, 0);
       backimg[1].tu = D3DVAL(0.5);
       backimg[1].tv = D3DVAL(0.0);
       /* V 2 */
       backimg[2].sx = D3DVAL(P_gamewindow->left);
       backimg[2].sy = D3DVAL(P_gamewindow->bottom);
       backimg[2].sz = D3DVAL(250.0);
       backimg[2].rhw = D3DVAL(0.004);
       backimg[2].color = 
                    D3DRGBA(midbackmat.ambient.r, midbackmat.ambient.g, midbackmat.ambient.b, midbackmat.ambient.a);
       backimg[2].specular = RGB_MAKE(0, 0, 0);
       backimg[2].tu = D3DVAL(0.01);
       backimg[2].tv = D3DVAL(1.0);
       /* V 3 */
       backimg[3].sx = D3DVAL(P_gamewindow->right);
       backimg[3].sy = D3DVAL(P_gamewindow->bottom);
       backimg[3].sz = D3DVAL(250.0);
       backimg[3].rhw = D3DVAL(0.004);
       backimg[3].color = 
                    D3DRGBA(midbackmat.ambient.r, midbackmat.ambient.g, midbackmat.ambient.b, midbackmat.ambient.a);
       backimg[3].specular = RGB_MAKE(0, 0, 0);
       backimg[3].tu = D3DVAL(0.5);
       backimg[3].tv = D3DVAL(1.0);
       /*
        * Create an execute buffer
        */
       size = sizeof(D3DTLVERTEX) * 4;
       size += sizeof(D3DINSTRUCTION) * 6;
       size += sizeof(D3DSTATE) * 8;
       size += sizeof(D3DPROCESSVERTICES);
       size += sizeof(D3DTRIANGLE) * 2;
       memset(&backimgdebDesc, 0, sizeof(D3DEXECUTEBUFFERDESC));
       backimgdebDesc.dwSize = sizeof(D3DEXECUTEBUFFERDESC);
       backimgdebDesc.dwFlags = D3DDEB_BUFSIZE;
       backimgdebDesc.dwBufferSize = size;
       if (lpD3DDev->lpVtbl->CreateExecuteBuffer(lpD3DDev, &backimgdebDesc, &lpbackimgExBuf,
                                              NULL) != D3D_OK) {
           goto generic_error;
       }
       if (lpbackimgExBuf->lpVtbl->Lock(lpbackimgExBuf, &backimgdebDesc) != D3D_OK) {
           goto generic_error;
       }
       lpBufStart = backimgdebDesc.lpData;
       memset(lpBufStart, 0, size);
       lpPointer = lpBufStart;

       /*
        * Copy vertices to execute buffer
        */
       //VERTEX_DATA(&backimg[0], 4, lpPointer);
       memcpy(lpPointer, &backimg[0], sizeof(D3DTLVERTEX) * (4)); 
       lpPointer = (void *)(((LPD3DTLVERTEX) (lpPointer)) + (4));
       /*
        * Setup instructions in execute buffer
        */
       lpInsStart = lpPointer;
       OP_STATE_RENDER(8, lpPointer);
            STATE_DATA(D3DRENDERSTATE_BLENDENABLE, FALSE, lpPointer);
            STATE_DATA(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA,lpPointer);
            STATE_DATA(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA,lpPointer);
            STATE_DATA(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATEALPHA, lpPointer);
            STATE_DATA(D3DRENDERSTATE_TEXTUREHANDLE, backtex.hTex, lpPointer);
            STATE_DATA(D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT, lpPointer);
            STATE_DATA(D3DRENDERSTATE_WRAPU, FALSE, lpPointer);
            STATE_DATA(D3DRENDERSTATE_WRAPV, FALSE, lpPointer);
       OP_PROCESS_VERTICES(1, lpPointer);
           PROCESSVERTICES_DATA(D3DPROCESSVERTICES_COPY |
                             D3DPROCESSVERTICES_UPDATEEXTENTS, 0, 4, lpPointer);
       /*
        * Make sure that the triangle data (not OP) will be QWORD aligned
        */
       if (QWORD_ALIGNED(lpPointer)) {
           OP_NOP(lpPointer);
       }
       OP_TRIANGLE_LIST(2, lpPointer);
           ((LPD3DTRIANGLE)lpPointer)->v1 = 0;
           ((LPD3DTRIANGLE)lpPointer)->v2 = 1;
           ((LPD3DTRIANGLE)lpPointer)->v3 = 2;
           ((LPD3DTRIANGLE)lpPointer)->wFlags = D3DTRIFLAG_EDGEENABLETRIANGLE;
           lpPointer = ((char*)lpPointer) + sizeof(D3DTRIANGLE);
           ((LPD3DTRIANGLE)lpPointer)->v1 = 1;
           ((LPD3DTRIANGLE)lpPointer)->v2 = 3;
           ((LPD3DTRIANGLE)lpPointer)->v3 = 2;
           ((LPD3DTRIANGLE)lpPointer)->wFlags = D3DTRIFLAG_EDGEENABLETRIANGLE;
           lpPointer = ((char*)lpPointer) + sizeof(D3DTRIANGLE);

       OP_EXIT(lpPointer);
       /*
        * Setup the execute data
        */
       if (FAILED(lpbackimgExBuf->lpVtbl->Unlock(lpbackimgExBuf)))
          goto generic_error;
       memset(&backimgExData, 0, sizeof(D3DEXECUTEDATA));
       backimgExData.dwSize = sizeof(D3DEXECUTEDATA);
       backimgExData.dwVertexCount = NUM_VERTICES;
       backimgExData.dwInstructionOffset = (ULONG) ((char *)lpInsStart - (char *)lpBufStart);
       backimgExData.dwInstructionLength = (ULONG) ((char *)lpPointer - (char *)lpInsStart);
       lpbackimgExBuf->lpVtbl->SetExecuteData(lpbackimgExBuf, &backimgExData);
   }


   RELEASE(lpD3DDev);
   RELEASE(lpbackmat);
   return;

generic_error:
   
   RELEASE(lpD3DDev);
   RELEASE(lpbackmat);
   RELEASE(lpbackflatExBuf);
   RELEASE(lpbackimgExBuf);
   return;
}

void RenderBackground(BOOL show)
{
   DWORD   dx, dy;
   HRESULT ddrval, rval;
   RECT    *P_gamewindow, fullrect, srcrect;
   int     j;
   LPDIRECT3DVIEWPORT lpD3DView = NULL;
   LPDIRECT3DDEVICE lpD3DDev = d3dappi.lpD3DDevice;
   LPDIRECT3D lpD3D = NULL;
   D3DRECT clrrect;

   D3DMATERIALHANDLE backmathandle;
   IDirect3DMaterial* lpbackmat;

   extern RLFrame Wscene;
   extern RLFrame Wcamera;
   extern RLValue sealevel;

   if (VSize < 4) 
      P_gamewindow = &(GWinSize[RMode-1][VSize-1]);
   else
   {
		if (sStretch.bStretch)
		{
			P_gamewindow = &fullrect;
			P_gamewindow->top = 0;
			P_gamewindow->bottom = VM_H3D/2 - 1;
			P_gamewindow->left = 0;
			P_gamewindow->right = VM_W3D/2 - 1;


		}
		else
		{
			P_gamewindow = &fullrect;
			P_gamewindow->top = 0;
			P_gamewindow->bottom = VM_H3D;
			P_gamewindow->left = 0;
			P_gamewindow->right = VM_W3D;
		}
	}

   clrrect.x1 = P_gamewindow->left;
   clrrect.x2 = P_gamewindow->right;
   clrrect.y1 = P_gamewindow->top;
   clrrect.y2 = P_gamewindow->bottom;
   rval = myglobs.view->lpVtbl->GetDirect3DViewport(myglobs.view, &lpD3DView);
   if (rval != D3DRM_OK) {
      BYDumpInfo(D3DAppErrorToString(rval));
      return;
   }

   rval = lpD3DView->lpVtbl->Clear(lpD3DView, 1, &clrrect, D3DCLEAR_ZBUFFER);
   if (rval != D3DRM_OK) {
      BYDumpInfo(D3DAppErrorToString(rval));
      return;
   }
   /*
   if (wetpipe)
   {
      RELEASE(lpD3DView);
      return;
   }
   */


    if (!lpD3DDev)
        goto generic_error;
    if (FAILED(lpD3DDev->lpVtbl->GetDirect3D(lpD3DDev, &lpD3D)))
        goto generic_error;

    if (FAILED(lpD3D->lpVtbl->CreateMaterial(lpD3D, &lpbackmat, NULL)))
        goto generic_error;

    if (!wetpipe)
    {
      switch (CalculateBackgroundCoords(P_gamewindow, &srcrect, &dx, &dy))
      {
         case 1:
			   if (FAILED(lpbackmat->lpVtbl->SetMaterial(lpbackmat, &bottombackmat)))
				   goto generic_error;
			   if (FAILED(lpbackmat->lpVtbl->GetHandle(lpbackmat, lpD3DDev, &backmathandle)))
				   goto generic_error;
			   if (FAILED(lpD3DView->lpVtbl->SetBackground(lpD3DView, backmathandle)))
				   goto generic_error;
            clrrect.x1 = P_gamewindow->left;
            clrrect.x2 = P_gamewindow->right;
            clrrect.y1 = P_gamewindow->top;
            clrrect.y2 = P_gamewindow->bottom;
            rval = lpD3DView->lpVtbl->Clear(lpD3DView, 1, &clrrect, D3DCLEAR_TARGET);
            if (rval != D3DRM_OK) {
               BYDumpInfo(D3DAppErrorToString(rval));
               return;
            }
            break;

         case 2:
            if (FAILED(lpbackmat->lpVtbl->SetMaterial(lpbackmat, &bottombackmat)))
               goto generic_error;
            if (FAILED(lpbackmat->lpVtbl->GetHandle(lpbackmat, lpD3DDev, &backmathandle)))
               goto generic_error;
            if (FAILED(lpD3DView->lpVtbl->SetBackground(lpD3DView, backmathandle)))
               goto generic_error;
	        clrrect.x1 = P_gamewindow->left;
	        clrrect.x2 = P_gamewindow->right;
	        clrrect.y1 = dy;
	        clrrect.y2 = P_gamewindow->bottom;
	        rval = lpD3DView->lpVtbl->Clear(lpD3DView, 1, &clrrect, D3DCLEAR_TARGET);
	        if (rval != D3DRM_OK) {
	           BYDumpInfo(D3DAppErrorToString(rval));
		       return;
	        }
			   j=0;
			   while(1)   // Ten chances to blit
			   {
				   if (sStretch.bStretch)
				   {
					   ddrval = d3dappi.lpBackBuffer2->lpVtbl->BltFast(d3dappi.lpBackBuffer2, dx, dy, 
        							 lpDDSOverlay[1], &srcrect, DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
					   if (ddrval==DD_OK) 
						   break;
					   else
					   {
						   if (j>10) break;
						   j++;
					   }
					}
					else
					{
				      ddrval = d3dappi.lpBackBuffer->lpVtbl->BltFast(d3dappi.lpBackBuffer, dx, dy, 
        					        lpDDSOverlay[1], &srcrect, DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
				      if (ddrval==DD_OK) 
					      break;
				      else
				      {
					      if (j>10) break;
					      j++;
				      }
               }
			   } 
            // Blit left section of bitmap onto right side of screen (for wraparound)
            //srcrect.left = srcrect.right-1;
            //srcrect.right = P_gamewindow->right-1;
            srcrect.left = srcrect.right-1;
            srcrect.right = (P_gamewindow->right - P_gamewindow->left) - 1;
		      dx = P_gamewindow->left;
			   j=0;
			   while(1)   // Ten chances to blit
			   {
				   if (sStretch.bStretch)
				   {
					   ddrval = d3dappi.lpBackBuffer2->lpVtbl->BltFast(d3dappi.lpBackBuffer2, dx, dy, 
        							 lpDDSOverlay[1], &srcrect, DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
					   if (ddrval==DD_OK) 
						   break;
					   else
					   {
						   if (j>10) break;
						   j++;
					   }
					}
					else
					{
						ddrval = d3dappi.lpBackBuffer->lpVtbl->BltFast(d3dappi.lpBackBuffer, dx, dy, 
        				         lpDDSOverlay[1], &srcrect, DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
						if (ddrval==DD_OK) 
						   break;
						else
						{
						   if (j>10) break;
						   j++;
						}
					}
			   }
            break;
      
         case 3:
            if (FAILED(lpbackmat->lpVtbl->SetMaterial(lpbackmat, &topbackmat)))
               goto generic_error;
            if (FAILED(lpbackmat->lpVtbl->GetHandle(lpbackmat, lpD3DDev, &backmathandle)))
               goto generic_error;
            if (FAILED(lpD3DView->lpVtbl->SetBackground(lpD3DView, backmathandle)))
               goto generic_error;
	        clrrect.x1 = P_gamewindow->left;
	        clrrect.x2 = P_gamewindow->right-1;
	        clrrect.y1 = P_gamewindow->top;
	        clrrect.y2 = dy;
	        rval = lpD3DView->lpVtbl->Clear(lpD3DView, 1, &clrrect, D3DCLEAR_TARGET);
	        if (rval != D3DRM_OK) {
	           BYDumpInfo(D3DAppErrorToString(rval));
		       return;
	        }
			   j=0;
			   while(1)   // Ten chances to blit
			   {
				   if (sStretch.bStretch)
				   {
					   ddrval = d3dappi.lpBackBuffer2->lpVtbl->BltFast(d3dappi.lpBackBuffer2, dx, dy, 
        							 lpDDSOverlay[1], &srcrect, DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
					   if (ddrval==DD_OK) 
						   break;
					   else
					   {
						   if (j>10) break;
						   j++;
					   }
					}
					else
					{
						ddrval = d3dappi.lpBackBuffer->lpVtbl->BltFast(d3dappi.lpBackBuffer, dx, dy, 
        				lpDDSOverlay[1], &srcrect, DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
						if (ddrval==DD_OK) 
						   break;
						else
						{
						   if (j>10) break;
						   j++;
						}


					}

			  } 
            // Blit left section of bitmap onto right side of screen (for wraparound)
            //srcrect.left = srcrect.right-1;
            //srcrect.right = P_gamewindow->right-1;
            srcrect.left = srcrect.right-1;
            srcrect.right = (P_gamewindow->right - P_gamewindow->left) - 1;
		      dx = P_gamewindow->left;
			   j=0;
			   while(1)   // Ten chances to blit
			   {
				   if (sStretch.bStretch)
				   {
					   ddrval = d3dappi.lpBackBuffer2->lpVtbl->BltFast(d3dappi.lpBackBuffer2, dx, dy, 
        							 lpDDSOverlay[1], &srcrect, DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
					   if (ddrval==DD_OK) 
						   break;
					   else
					   {
						   if (j>10) break;
						   j++;
					   }
					}
					else
					{
						ddrval = d3dappi.lpBackBuffer->lpVtbl->BltFast(d3dappi.lpBackBuffer, dx, dy, 
        				lpDDSOverlay[1], &srcrect, DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
						if (ddrval==DD_OK) 
						   break;
						else
						{
						   if (j>10) break;
						   j++;
						}


					}

			   }
            break;
      
         case 4:
			   if (FAILED(lpbackmat->lpVtbl->SetMaterial(lpbackmat, &topbackmat)))
				   goto generic_error;
			   if (FAILED(lpbackmat->lpVtbl->GetHandle(lpbackmat, lpD3DDev, &backmathandle)))
				   goto generic_error;
			   if (FAILED(lpD3DView->lpVtbl->SetBackground(lpD3DView, backmathandle)))
				   goto generic_error;
            clrrect.x1 = P_gamewindow->left;
            clrrect.x2 = P_gamewindow->right-1;
            clrrect.y1 = P_gamewindow->top;
            clrrect.y2 = P_gamewindow->bottom-1;
            rval = lpD3DView->lpVtbl->Clear(lpD3DView, 1, &clrrect, D3DCLEAR_TARGET);
            if (rval != D3DRM_OK) {
               BYDumpInfo(D3DAppErrorToString(rval));
               return;
            }
            break;
      }
   }

   myglobs.view->lpVtbl->ForceUpdate(myglobs.view, 
      clrrect.x1, clrrect.y1, clrrect.x2, clrrect.y2);


   RELEASE(lpD3DView);
   RELEASE(lpD3DDev);
   RELEASE(lpD3D);
   RELEASE(lpbackmat);
   return;

generic_error:

   RELEASE(lpD3DDev);
   RELEASE(lpD3D);
   RELEASE(lpbackmat);
   RELEASE(lpD3DView);
   return;
}

void RenderBackgroundOn4MegAcc(BOOL show)
{
   DWORD   dx, dy;
   HRESULT rval;
   RECT    *P_gamewindow, fullrect, srcrect;
   LPDIRECT3DDEVICE lpD3DDev = d3dappi.lpD3DDevice;
   LPDIRECT3D lpD3D = NULL;
   D3DRECT clrrect;
	D3DEXECUTEBUFFERDESC desc;
	D3DTLVERTEX *v;
   LPDIRECT3DVIEWPORT lpD3DView = NULL;

   extern RLFrame Wscene;
   extern RLFrame Wcamera;
   extern RLValue sealevel;

   if (VSize < 4) 
      P_gamewindow = &(GWinSize[RMode-1][VSize-1]);
   else
   {
      P_gamewindow = &fullrect;
      P_gamewindow->top = 0;
      P_gamewindow->bottom = VM_H3D;
      P_gamewindow->left = 0;
      P_gamewindow->right = VM_W3D;
   }

   clrrect.x1 = P_gamewindow->left;
   clrrect.x2 = P_gamewindow->right;
   clrrect.y1 = P_gamewindow->top;
   clrrect.y2 = P_gamewindow->bottom;

   //myglobs.view->lpVtbl->Clear(myglobs.view);
   rval = myglobs.view->lpVtbl->GetDirect3DViewport(myglobs.view, &lpD3DView);
   if (rval != D3DRM_OK) {
      BYDumpInfo(D3DAppErrorToString(rval));
      return;
   }

   rval = lpD3DView->lpVtbl->Clear(lpD3DView, 1, &clrrect, D3DCLEAR_ZBUFFER);
   if (rval != D3DRM_OK) {
      BYDumpInfo(D3DAppErrorToString(rval));
      return;
   }

   if (!lpD3DDev)
        goto generic_error;
    if (FAILED(lpD3DDev->lpVtbl->GetDirect3D(lpD3DDev, &lpD3D)))
        goto generic_error;


      switch (CalculateBackgroundCoords(P_gamewindow, &srcrect, &dx, &dy))
      {
         LPVOID lpPointer;
         int gwinwid, gwinhit;

         case 1:  // looking down only at ground background color
            desc.dwSize = sizeof(D3DEXECUTEBUFFERDESC);
            desc.dwFlags = 0;
	         if (FAILED(lpbackflatExBuf->lpVtbl->Lock(lpbackflatExBuf, &desc)))
	            goto generic_error;
	         
            v = (D3DTLVERTEX*) desc.lpData;
            v->color = 
              D3DRGBA(bottombackmat.ambient.r, bottombackmat.ambient.g, bottombackmat.ambient.b, bottombackmat.ambient.a);
            v->sx = D3DVAL(P_gamewindow->left);
            v->sy = D3DVAL(P_gamewindow->top);
            
            v++;
            v->color = 
              D3DRGBA(bottombackmat.ambient.r, bottombackmat.ambient.g, bottombackmat.ambient.b, bottombackmat.ambient.a);
            v->sx = D3DVAL(P_gamewindow->right);
            v->sy = D3DVAL(P_gamewindow->top);
            
            v++;
            v->color = 
              D3DRGBA(bottombackmat.ambient.r, bottombackmat.ambient.g, bottombackmat.ambient.b, bottombackmat.ambient.a);
            v->sx = D3DVAL(P_gamewindow->left);
            v->sy = D3DVAL(P_gamewindow->bottom);
            
            v++;
            v->color = 
              D3DRGBA(bottombackmat.ambient.r, bottombackmat.ambient.g, bottombackmat.ambient.b, bottombackmat.ambient.a);
            v->sx = D3DVAL(P_gamewindow->right);
            v->sy = D3DVAL(P_gamewindow->bottom);

            v++;
            lpPointer = (void *)(((LPD3DINSTRUCTION) v) + 1);
            if (wetpipe) 
            {
               STATE_DATA(D3DRENDERSTATE_BLENDENABLE, TRUE, lpPointer);
            }
            else
            {
               STATE_DATA(D3DRENDERSTATE_BLENDENABLE, FALSE, lpPointer);
            }
	         if (FAILED(lpbackflatExBuf->lpVtbl->Unlock(lpbackflatExBuf)))
	            goto generic_error;

	         if (FAILED(lpD3DDev->lpVtbl->Execute(lpD3DDev, lpbackflatExBuf, lpD3DView, D3DEXECUTE_UNCLIPPED)))
		         goto generic_error;
            
            break;
         case 2:
            dy = P_gamewindow->bottom - srcrect.top;
            gwinwid = P_gamewindow->right - P_gamewindow->left;
            gwinhit = P_gamewindow->bottom - P_gamewindow->top;

            desc.dwSize = sizeof(D3DEXECUTEBUFFERDESC);
            desc.dwFlags = 0;
	         if (FAILED(lpbackflatExBuf->lpVtbl->Lock(lpbackflatExBuf, &desc)))
	            goto generic_error;
	         
            v = (D3DTLVERTEX*) desc.lpData;
            v->color = 
                    D3DRGBA(bottombackmat.ambient.r, bottombackmat.ambient.g, bottombackmat.ambient.b, bottombackmat.ambient.a);
            v->sx = D3DVAL(P_gamewindow->left);
            v->sy = D3DVAL(dy);
            
            v++;
            v->color = 
                    D3DRGBA(bottombackmat.ambient.r, bottombackmat.ambient.g, bottombackmat.ambient.b, bottombackmat.ambient.a);
            v->sx = D3DVAL(P_gamewindow->right);
            v->sy = D3DVAL(dy);
            
            v++;
            v->color = 
                    D3DRGBA(bottombackmat.ambient.r, bottombackmat.ambient.g, bottombackmat.ambient.b, bottombackmat.ambient.a);
            v->sx = D3DVAL(P_gamewindow->left);
            v->sy = D3DVAL(P_gamewindow->bottom);
            
            v++;
            v->color = 
                    D3DRGBA(bottombackmat.ambient.r, bottombackmat.ambient.g, bottombackmat.ambient.b, bottombackmat.ambient.a);
            v->sx = D3DVAL(P_gamewindow->right);
            v->sy = D3DVAL(P_gamewindow->bottom);
            
            v++;
            lpPointer = (void *)(((LPD3DINSTRUCTION) v) + 1);
            if (wetpipe) 
            {
               STATE_DATA(D3DRENDERSTATE_BLENDENABLE, TRUE, lpPointer);
            }
            else
            {
               STATE_DATA(D3DRENDERSTATE_BLENDENABLE, FALSE, lpPointer);
            }

            if (FAILED(lpbackflatExBuf->lpVtbl->Unlock(lpbackflatExBuf)))
	            goto generic_error;

	         if (FAILED(lpD3DDev->lpVtbl->Execute(lpD3DDev, lpbackflatExBuf, lpD3DView, D3DEXECUTE_UNCLIPPED)))
		         goto generic_error;

	         if (FAILED(lpbackimgExBuf->lpVtbl->Lock(lpbackimgExBuf, &desc)))
	            goto generic_error;
	         
            v = (D3DTLVERTEX*) desc.lpData;
            v->sx = D3DVAL(P_gamewindow->left);
            v->sy = D3DVAL(P_gamewindow->top);
            v->color = 
                    D3DRGBA(D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0), D3DVAL(0.1));
            v->tu = D3DVAL(1.0) - D3DVAL(dx)/D3DVAL(gwinwid);
            v->tv = D3DVAL(1.0) - D3DVAL(dy - P_gamewindow->top)/D3DVAL(gwinhit);
            
            v++;
            v->sx = D3DVAL(P_gamewindow->right);
            v->sy = D3DVAL(P_gamewindow->top);
            v->color = 
                    D3DRGBA(D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0), D3DVAL(0.1));
            v->tu = D3DVAL(1.0) - D3DVAL(dx)/D3DVAL(gwinwid) + D3DVAL(1.0);
            v->tv = D3DVAL(1.0) - D3DVAL(dy - P_gamewindow->top)/D3DVAL(gwinhit);
            
            v++;
            v->sx = D3DVAL(P_gamewindow->left);
            v->sy = D3DVAL(dy);
            v->color = 
                    D3DRGBA(D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0), D3DVAL(0.1));
            v->tu = D3DVAL(1.0)- D3DVAL(dx)/D3DVAL(gwinwid);
            v->tv = D3DVAL(1.0) - D3DVAL(1.0/256.0);
            
            v++;
            v->sx = D3DVAL(P_gamewindow->right);
            v->sy = D3DVAL(dy);
            v->color = 
                    D3DRGBA(D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0), D3DVAL(0.1));
            v->tu = D3DVAL(1.0) - D3DVAL(dx)/D3DVAL(gwinwid) + D3DVAL(1.0);
            v->tv = D3DVAL(1.0) - D3DVAL(1.0/256.0);

            v++;
            lpPointer = (void *)(((LPD3DINSTRUCTION) v) + 1);
            if (wetpipe) 
            {
               STATE_DATA(D3DRENDERSTATE_BLENDENABLE, TRUE, lpPointer);
            }
            else
            {
               STATE_DATA(D3DRENDERSTATE_BLENDENABLE, FALSE, lpPointer);
            }

            if (FAILED(lpbackimgExBuf->lpVtbl->Unlock(lpbackimgExBuf)))
	            goto generic_error;

	         if (FAILED(lpD3DDev->lpVtbl->Execute(lpD3DDev, lpbackimgExBuf, lpD3DView, D3DEXECUTE_UNCLIPPED)))
		         goto generic_error;
            
            break;
      
         case 3:
             gwinwid = P_gamewindow->right - P_gamewindow->left;
            gwinhit = P_gamewindow->bottom - P_gamewindow->top;
           desc.dwSize = sizeof(D3DEXECUTEBUFFERDESC);
            desc.dwFlags = 0;
 	         if (FAILED(lpbackflatExBuf->lpVtbl->Lock(lpbackflatExBuf, &desc)))
	            goto generic_error;
	         
            v = (D3DTLVERTEX*) desc.lpData;
            v->color = 
                    D3DRGBA(topbackmat.ambient.r, topbackmat.ambient.g, topbackmat.ambient.b, topbackmat.ambient.a);
            v->sx = D3DVAL(P_gamewindow->left);
            v->sy = D3DVAL(P_gamewindow->top);
            
            v++;
            v->color = 
                    D3DRGBA(topbackmat.ambient.r, topbackmat.ambient.g, topbackmat.ambient.b, topbackmat.ambient.a);
            v->sx = D3DVAL(P_gamewindow->right);
            v->sy = D3DVAL(P_gamewindow->top);
            
            v++;
            v->color = 
                    D3DRGBA(topbackmat.ambient.r, topbackmat.ambient.g, topbackmat.ambient.b, topbackmat.ambient.a);
            v->sx = D3DVAL(P_gamewindow->left);
            v->sy = D3DVAL(dy);
            
            v++;
            v->color = 
                    D3DRGBA(topbackmat.ambient.r, topbackmat.ambient.g, topbackmat.ambient.b, topbackmat.ambient.a);
            v->sx = D3DVAL(P_gamewindow->right);
            v->sy = D3DVAL(dy);

            v++;
            lpPointer = (void *)(((LPD3DINSTRUCTION) v) + 1);
            if (wetpipe) 
            {
               STATE_DATA(D3DRENDERSTATE_BLENDENABLE, TRUE, lpPointer);
            }
            else
            {
               STATE_DATA(D3DRENDERSTATE_BLENDENABLE, FALSE, lpPointer);
            }

            if (FAILED(lpbackflatExBuf->lpVtbl->Unlock(lpbackflatExBuf)))
	            goto generic_error;

	         if (FAILED(lpD3DDev->lpVtbl->Execute(lpD3DDev, lpbackflatExBuf, lpD3DView, D3DEXECUTE_UNCLIPPED)))
		         goto generic_error;

	         if (FAILED(lpbackimgExBuf->lpVtbl->Lock(lpbackimgExBuf, &desc)))
	            goto generic_error;
	         
            v = (D3DTLVERTEX*) desc.lpData;
            v->sx = D3DVAL(P_gamewindow->left);
            v->sy = D3DVAL(dy);
            v->color = 
                    D3DRGBA(D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0), D3DVAL(0.1));
            v->tu = D3DVAL(1.0) - D3DVAL(dx)/D3DVAL(gwinwid);
            v->tv = D3DVAL(0.0) + D3DVAL(1.0/256.0);
            
            v++;
            v->sx = D3DVAL(P_gamewindow->right);
            v->sy = D3DVAL(dy);
            v->color = 
                    D3DRGBA(D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0), D3DVAL(0.1));
            v->tu = D3DVAL(1.0) - D3DVAL(dx)/D3DVAL(gwinwid)+D3DVAL(1.0);
            v->tv = D3DVAL(0.0) + D3DVAL(1.0/256.0);

            v++;
            v->sx = D3DVAL(P_gamewindow->left);
            v->sy = D3DVAL(P_gamewindow->bottom);
            v->color = 
                    D3DRGBA(D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0), D3DVAL(0.1));
            v->tu = D3DVAL(1.0) - D3DVAL(dx)/D3DVAL(gwinwid);
            v->tv = D3DVAL(1.0) - D3DVAL(dy - P_gamewindow->top)/D3DVAL(gwinhit);
            
            v++;
            v->sx = D3DVAL(P_gamewindow->right);
            v->sy = D3DVAL(P_gamewindow->bottom);
            v->color = 
                    D3DRGBA(D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0), D3DVAL(0.1));
            v->tu = D3DVAL(1.0) - D3DVAL(dx)/D3DVAL(gwinwid) + D3DVAL(1.0);
            v->tv = D3DVAL(1.0) - D3DVAL(dy - P_gamewindow->top)/D3DVAL(gwinhit);

            v++;
            lpPointer = (void *)(((LPD3DINSTRUCTION) v) + 1);
            if (wetpipe) 
            {
               STATE_DATA(D3DRENDERSTATE_BLENDENABLE, TRUE, lpPointer);
            }
            else
            {
               STATE_DATA(D3DRENDERSTATE_BLENDENABLE, FALSE, lpPointer);
            }

            if (FAILED(lpbackimgExBuf->lpVtbl->Unlock(lpbackimgExBuf)))
	            goto generic_error;

	         if (FAILED(lpD3DDev->lpVtbl->Execute(lpD3DDev, lpbackimgExBuf, lpD3DView, D3DEXECUTE_UNCLIPPED)))
		         goto generic_error;
            
            break;
     
         case 4:  // looking up only at sky background color
            desc.dwSize = sizeof(D3DEXECUTEBUFFERDESC);
            desc.dwFlags = 0;
	         if (FAILED(lpbackflatExBuf->lpVtbl->Lock(lpbackflatExBuf, &desc)))
	            goto generic_error;
	         
            v = (D3DTLVERTEX*) desc.lpData;
            v->color = 
                    D3DRGBA(topbackmat.ambient.r, topbackmat.ambient.g, topbackmat.ambient.b, topbackmat.ambient.a);
            v->sx = D3DVAL(P_gamewindow->left);
            v->sy = D3DVAL(P_gamewindow->top);
            
            v++;
            v->color = 
                    D3DRGBA(topbackmat.ambient.r, topbackmat.ambient.g, topbackmat.ambient.b, topbackmat.ambient.a);
            v->sx = D3DVAL(P_gamewindow->right);
            v->sy = D3DVAL(P_gamewindow->top);
           
            v++;
            v->color = 
                    D3DRGBA(topbackmat.ambient.r, topbackmat.ambient.g, topbackmat.ambient.b, topbackmat.ambient.a);
            v->sx = D3DVAL(P_gamewindow->left);
            v->sy = D3DVAL(P_gamewindow->bottom);
            
            v++;
            v->color = 
                    D3DRGBA(topbackmat.ambient.r, topbackmat.ambient.g, topbackmat.ambient.b, topbackmat.ambient.a);
            v->sx = D3DVAL(P_gamewindow->right);
            v->sy = D3DVAL(P_gamewindow->bottom);

            v++;
            lpPointer = (void *)(((LPD3DINSTRUCTION) v) + 1);
            if (wetpipe) 
            {
                  STATE_DATA(D3DRENDERSTATE_BLENDENABLE, TRUE, lpPointer);
            }
            else
            {
                  STATE_DATA(D3DRENDERSTATE_BLENDENABLE, FALSE, lpPointer);
            }

            if (FAILED(lpbackflatExBuf->lpVtbl->Unlock(lpbackflatExBuf)))
	            goto generic_error;

	         if (FAILED(lpD3DDev->lpVtbl->Execute(lpD3DDev, lpbackflatExBuf, lpD3DView, D3DEXECUTE_UNCLIPPED)))
		         goto generic_error;
            
            break;
      }

   rval = lpD3DView->lpVtbl->Clear(lpD3DView, 1, &clrrect, D3DCLEAR_ZBUFFER);
   if (rval != D3DRM_OK) {
      BYDumpInfo(D3DAppErrorToString(rval));
      return;
   }

   oldwetpipe = wetpipe;
   RELEASE(lpD3DDev);
   RELEASE(lpD3D);
   RELEASE(lpD3DView);
   return;

generic_error:

   oldwetpipe = wetpipe;
   RELEASE(lpD3DDev);
   RELEASE(lpD3D);
   RELEASE(lpD3DView);
   return;
}


// **********************************************************
// Name:		UpdateVertex
//		
// Author:		LiuGuoHong					
//
// Date:		1996.8                      
//
// Description: Update the vertex of background
//
// Arguments:		None
//
// Return:			None
//
// Side Effects:	None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void UpdateVertex(SCROLL *Scroll, D3DTLVERTEX *SrcVertex)
{
	RLVector at, up;
	RLValue angle;
	extern int cpx;
	int i, isclipped;
	RLVector place;
	RLVector4d place4d;
	static D3DVIEWPORT view_vata;
	
    extern RLFrame Wscene; // = Scroll->scene;
	extern RLFrame Wcamera; // = Scroll->camera;
	extern RLViewport Wview; // = Scroll->view;
	RLValue sealevel = RLVal(-1.0);

	RLFrameGetOrientation(Wcamera, Wscene, &at, &up);
	RLFrameGetPosition(Wcamera, Wscene, &place);

	at.y = RLVal(0.0);
	RLVectorNormalise(&at);
	place.x += RLVal(1.5*(cpx+cpz)*at.x);
	place.z += RLVal(1.5*(cpx+cpz)*at.z);
    place.y = sealevel;

	RLViewportTransform(Wview, &place4d, &place);
	TheHorizon = place4d.y / place4d.w;
	place4d.y = (screeny/2)*place4d.w;
	RLViewportInverseTransform(Wview, &place, &place4d);

	zdepth = RLVal(0.9999);
    if (at.x != 0.0) 
	{
		angle = RLMultiply(RLVal(256.0*4.0/6.28318530718), 
		                   RLVal(atan(-at.z/at.x)));
	}
	 else
	 {
		if (at.x * at.z < 0) 
		{
			angle = RLVal(-256.0*4.0/4.0);
		}
		else
		{
			angle = RLVal(256.0*4.0/4.0);
		}
	 }
   
    angle /= RLVal(256.0);

	isclipped = 0;

	horizondestination[0].tu = angle;
	horizondestination[0].tv = RLVal(0.0);
	horizondestination[0].sx = RLVal(0.0);
	horizondestination[0].sy = RLVal(TheHorizon - 32.0);
	horizondestination[0].sz = zdepth;
	if ((horizondestination[0].sy < 0) || 
		(horizondestination[0].sy > screeny))	
	{
		isclipped = 1;
	}

	horizondestination[1].tu = RLVal(angle+0.5);
	horizondestination[1].tv = RLVal(0.0);
	horizondestination[1].sx = screenx;
	horizondestination[1].sy = RLVal(TheHorizon - 32.0);
	horizondestination[1].sz = zdepth;
	if ((horizondestination[1].sy < 0) || 
		(horizondestination[1].sy > screeny))	
	{
		isclipped = 1;
	}

	horizondestination[2].tu = angle;
	horizondestination[2].tv = RLVal(0.9999);
	horizondestination[2].sx = RLVal(0.0);
	horizondestination[2].sy = TheHorizon;
	horizondestination[2].sz = zdepth;
	if ((horizondestination[2].sy < 0) || 
		(horizondestination[2].sy > screeny))	
	{
		isclipped = 1;
	}

	horizondestination[3].tu = RLVal(angle+0.5);
	horizondestination[3].tv = RLVal(0.9999);
	horizondestination[3].sx = screenx;
	horizondestination[3].sy = TheHorizon;
	horizondestination[3].sz = zdepth;
	if ((horizondestination[3].sy < 0) || 
		(horizondestination[3].sy > screeny))	
	{
		isclipped = 1;
	}

	horizondestination[4].tu = angle;
	horizondestination[4].tv = RLVal(0.9999);
	horizondestination[4].sx = RLVal(0.0);
	horizondestination[4].sy = RLVal(MAX(screeny, 
									horizondestination[2].sy+1.0));
	horizondestination[4].sz = zdepth;
	if ((horizondestination[4].sy < 0) || 
		(horizondestination[4].sy > screeny))	
	{
		isclipped = 1;
	}

	horizondestination[5].tu = RLVal(angle+0.5);
	horizondestination[5].tv = RLVal(0.9999);
	horizondestination[5].sx = screenx;
	horizondestination[5].sy = RLVal(MAX(screeny, 
									horizondestination[3].sy+1.0));
	horizondestination[5].sz = zdepth;
	if ((horizondestination[5].sy < 0) || 
		(horizondestination[5].sy > screeny))
	{
		isclipped = 1;
	}

	if (isclipped) 
	{
		if (TheHorizon > screeny / 2)
		{
			for (i=0;i<6;i++) 
			{
				horizondestination[0].sx = RLVal(0.0);
				if ((TheHorizon - 32.0) <= screeny)
				{
					horizondestination[0].sy = RLVal(TheHorizon - 32.0);
				}
				else
				{
					horizondestination[0].sy = screeny;
				}
				horizondestination[0].sz = RLVal(0.9999);
				
				horizondestination[1].sx = screenx;
				if ((TheHorizon - 32.0) <= screeny)
				{
					horizondestination[1].sy = RLVal(TheHorizon - 32.0);
				}
				else
				{
					horizondestination[1].sy = screeny;
				}
				horizondestination[1].sz = RLVal(0.9999);
				
				horizondestination[2].sx = RLVal(0.0);
				horizondestination[2].sy = screeny;
				horizondestination[2].sz = RLVal(0.9999);

				horizondestination[3].sx = screenx;
				horizondestination[3].sy = screeny;
				horizondestination[3].sz = RLVal(0.9999);

				horizondestination[4].sx = RLVal(0.0);
				horizondestination[4].sy = screeny;
				horizondestination[4].sz = RLVal(0.9999);

				horizondestination[5].sx = screenx;
				horizondestination[5].sy = screeny;
				horizondestination[5].sz = RLVal(0.9999);
			}
		}

		else
		{
			for (i=0;i<6;i++) 
			{
				horizondestination[0].sx = RLVal(0.0);
				horizondestination[0].sy = RLVal(0.0);
				horizondestination[0].sz = RLVal(0.9999);
				
				horizondestination[1].sx = screenx;
				horizondestination[1].sy = RLVal(0.0);
				horizondestination[1].sz = RLVal(0.9999);
				
				horizondestination[2].sx = RLVal(0.0);
				if (TheHorizon >= 1.0)
				{
					horizondestination[2].sy = TheHorizon;
				}
				else 
				{
					horizondestination[2].sy = RLVal(1.0);
				}
				horizondestination[2].sz = RLVal(0.9999);

				horizondestination[3].sx = screenx;
				if (TheHorizon >= 1.0)
				{
					horizondestination[3].sy = TheHorizon;
				}
				else 
				{
					horizondestination[3].sy = RLVal(1.0);
				}
				horizondestination[3].sz = RLVal(0.9999);

				horizondestination[4].sx = RLVal(0.0);
				horizondestination[4].sy = screeny;
				horizondestination[4].sz = RLVal(0.9999);

				horizondestination[5].sx = screenx;
				horizondestination[5].sy = screeny;
				horizondestination[5].sz = RLVal(0.9999);
			}
		}
	}

	for (i = 0; i < 6; i++)
	{
	   SrcVertex[i].sx = horizondestination[i].sx;
	   SrcVertex[i].sy = horizondestination[i].sy;
	   SrcVertex[i].sz = horizondestination[i].sz;
       SrcVertex[i].rhw = D3DVAL(1.0);
	   SrcVertex[i].color = RGBA_MAKE(1, 1, 1, 100);
       SrcVertex[i].specular = RGB_MAKE(1, 1, 1);
	   SrcVertex[i].tu = horizondestination[i].tu;
	   SrcVertex[i].tv = horizondestination[i].tv;
	}
}



// **********************************************************
// Name:		DestroyIScroll
//		
// Author:		LiuGuoHong					
//
// Date:		1996.8                      
//
// Description: Release resource occupied by background
//
// Arguments:		None
//
// Return:			None
//
// Side Effects:	None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void DestroyIScroll()
{
	MDFreeD3DFrame(BackgroundFrame); 
}

extern HotSpot RobotHotSpots[];
int jetindex;
RLFrame jetframe;


// **********************************************************
// Name:		InitJets
//		
// Author:		LiuGuoHong					
//
// Date:		1996.8                      
//
// Description: Init the jets objects
//
// Arguments:		None
//
// Return:			None
//
// Side Effects:	None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void InitJets(LPTEXTURESTRUCT jettex, void *arg)
{
	extern iobjdlist* allmiscdlists[];

	arg = arg;		
	jetframe = RLCreateFrame(behindthescene);
	jetindex = LoadIntoDList("jetflame.x", jetframe, jettex, "NeedTransparent");
	DeleteBinary (allmiscdlists[jetindex]->builder);
	allmiscdlists[jetindex]->builder=NULL;

}

// **********************************************************
// Name:		DestroyJets
//		
// Author:		LiuGuoHong					
//
// Date:		1996.8                      
//
// Description: Destroy jets
//
// Arguments:		None
//
// Return:			None
//
// Side Effects:	None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void DestroyJets()
{
	RLFrame ParentFrame = NULL;
	if ((ParentFrame = RLFrameGetParent(jetframe)))
	{
		RLFrameRemoveChild(ParentFrame, jetframe);
		
		//LGH add release
		RLObjectDestroy ((RLObject)ParentFrame);
	}
}

// **********************************************************
// Name:		ActivateJets
//		
// Author:		LiuGuoHong					
//
// Date:		1996.8                      
//
// Description: Activate the jets
//
// Arguments:		None
//
// Return:			None
//
// Side Effects:	None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

Caminfo* camerastuff;

void ActivateJets(int whichway)
{
	RLVector shoulder[4] =
		{
			{RLVal(0.55), RLVal(0), RLVal(-0.1)},		// Saber
			{RLVal(0.5), RLVal(0), RLVal(-0.1)},		// Stealth
			{RLVal(0.95), RLVal(0), RLVal(-0.3)},		// Mer
			{RLVal(0.55), RLVal(0), RLVal(-0.1)}		// Kata
		};

	if (RLFrameGetScene(jetframe) == Wscene) return;

	RLFrameAddChild(RobotHotSpots[RobotChest].position, jetframe);
	YBPlay3DSound(RobotJets, RobotHotSpots[RobotChest].position);
	switch (whichway) {
		case JETFORWARD:	
			if (GameStates.CurrentRobot != KaberRobot) {
				RLFrameSetPosition(jetframe, RobotHotSpots[RobotChest].position, 
					RobotHotSpots[RobotChest].point1.x, RobotHotSpots[RobotChest].point1.y+RLVal(0.25), RobotHotSpots[RobotChest].point1.z);
				RLFrameSetOrientation(jetframe, RobotHotSpots[RobotChest].position, RLVal(0), RLVal(1), RLVal(0), RLVal(0), RLVal(0), RLVal(1));
			} else {
				RLFrameSetPosition(jetframe, RobotHotSpots[RobotChest].position, 
					RobotHotSpots[RobotChest].point1.x, RobotHotSpots[RobotChest].point1.y, RobotHotSpots[RobotChest].point1.z+RLVal(0.25));
				RLFrameSetOrientation(jetframe, RobotHotSpots[RobotChest].position, RLVal(0), RLVal(0), RLVal(1), RLVal(0), RLVal(1), RLVal(0));
			}
		break;
		case JETBACK:	
			if (camerastuff->method==POV)
			{
				DeactivateJets ();
				break;
			}

			if (GameStates.CurrentRobot != KaberRobot) {
				RLFrameSetPosition(jetframe, RobotHotSpots[RobotChest].position, 
					RobotHotSpots[RobotChest].point1.x, RobotHotSpots[RobotChest].point1.y-RLVal(0.25), RobotHotSpots[RobotChest].point1.z);
				RLFrameSetOrientation(jetframe, RobotHotSpots[RobotChest].position, RLVal(0), RLVal(-1), RLVal(0), RLVal(0), RLVal(0), RLVal(1));
			} else {
				RLFrameSetPosition(jetframe, RobotHotSpots[RobotChest].position, 
					RobotHotSpots[RobotChest].point1.x, RobotHotSpots[RobotChest].point1.y, RobotHotSpots[RobotChest].point1.z-RLVal(0.25));
				RLFrameSetOrientation(jetframe, RobotHotSpots[RobotChest].position, RLVal(0), RLVal(0), RLVal(-1), RLVal(0), RLVal(1), RLVal(0));
			}
		break;
		case JETRIGHT:	
			if (GameStates.CurrentRobot != KaberRobot) {
				RLFrameSetPosition(jetframe, RobotHotSpots[RobotChest].position, 
					RobotHotSpots[RobotChest].point1.x+shoulder[GameStates.CurrentRobot].x, RobotHotSpots[RobotChest].point1.y, RobotHotSpots[RobotChest].point1.z+shoulder[GameStates.CurrentRobot].z);
				RLFrameSetOrientation(jetframe, RobotHotSpots[RobotChest].position, RLVal(1), RLVal(0), RLVal(0), RLVal(0), RLVal(0), RLVal(1));
			} else {
				RLFrameSetPosition(jetframe, RobotHotSpots[RobotChest].position, 
					RobotHotSpots[RobotChest].point1.x+RLVal(1.0), RobotHotSpots[RobotChest].point1.y+RLVal(0.6), RobotHotSpots[RobotChest].point1.z-RLVal(0.1));
				RLFrameSetOrientation(jetframe, RobotHotSpots[RobotChest].position, RLVal(1), RLVal(0), RLVal(0), RLVal(0), RLVal(1), RLVal(0));
			}
		break;
		case JETLEFT:	
			if (GameStates.CurrentRobot != KaberRobot) {
				RLFrameSetPosition(jetframe, RobotHotSpots[RobotChest].position, 
					RobotHotSpots[RobotChest].point1.x-shoulder[GameStates.CurrentRobot].x, RobotHotSpots[RobotChest].point1.y, RobotHotSpots[RobotChest].point1.z+shoulder[GameStates.CurrentRobot].z);
				RLFrameSetOrientation(jetframe, RobotHotSpots[RobotChest].position, RLVal(-1), RLVal(1), RLVal(0), RLVal(0), RLVal(0), RLVal(1));
			} else {
				RLFrameSetPosition(jetframe, RobotHotSpots[RobotChest].position, 
					RobotHotSpots[RobotChest].point1.x-RLVal(1.0), RobotHotSpots[RobotChest].point1.y+RLVal(0.6), RobotHotSpots[RobotChest].point1.z-RLVal(0.1));
				RLFrameSetOrientation(jetframe, RobotHotSpots[RobotChest].position, RLVal(-1), RLVal(0), RLVal(0), RLVal(0), RLVal(1), RLVal(0));
			}
		break;

	}
	RLFrameAddCallback(jetframe, Jetflamer, (void*) &jetindex);
}

// **********************************************************
// Name:		DeactivateJets
//		
// Author:		LiuGuoHong					
//
// Date:		1996.8                      
//
// Description: Deactivate the jets
//
// Arguments:		None
//
// Return:			None
//
// Side Effects:	None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void DeactivateJets()
{
	if (RLFrameGetScene(jetframe) == behindthescene) return;

	RLFrameAddChild(behindthescene, jetframe);
	RLFrameRemoveCallback(jetframe, Jetflamer, (void*) &jetindex);
	BYOBStopSound(RobotJets);
}


// **********************************************************
// Name:		JetFlamer
//		
// Author:		LiuGuoHong					
//
// Date:		1996.8                      
//
// Description: Callback function of rendering jets
//
// Arguments:		None
//
// Return:			None
//
// Side Effects:	None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void Jetflamer(RLFrame theframe, void* arg,D3DVALUE delta)	
{
	int *jetidx = arg;
	int i;

	for (i = 0; i < (int)(allmiscdlists[*jetidx]->vcount); i++) 
	{
		if ((allmiscdlists[*jetidx]->Vertex[i].x) && 
			(allmiscdlists[*jetidx]->Vertex[i].x)) 
		{
			allmiscdlists[*jetidx]->Vertex[i].z = 
				RLVal(0.5176188) + RLDivide((rand()&0xff), RLVal(256));
			if (allmiscdlists[*jetidx]->Vertex[i].x < 0)
			{
				allmiscdlists[*jetidx]->Vertex[i].x = 
				-(RLVal(0.5176188) + RLDivide((rand()&0x1f), RLVal(256)));
			}
			else
			{
				allmiscdlists[*jetidx]->Vertex[i].x = 
					RLVal(0.5176188) + RLDivide((rand()&0x1f), RLVal(256));
			}
			if (allmiscdlists[*jetidx]->Vertex[i].y < 0)
			{
				allmiscdlists[*jetidx]->Vertex[i].y = -(RLVal(0.5176188) + RLDivide((rand()&0x1f), RLVal(256)));
			}
			else
			{
				allmiscdlists[*jetidx]->Vertex[i].y = RLVal(0.5176188) + RLDivide((rand()&0x1f), RLVal(256));
			}
		}
	}
}



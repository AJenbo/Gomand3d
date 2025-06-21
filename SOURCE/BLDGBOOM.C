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
$Header:   H:/pvcs/pvcsproj/gomand3d.prj/BLDGBOOM.C_V   1.10   24 Apr 1997 14:26:12   JEREMIAH  $

$Log:   H:/pvcs/pvcsproj/gomand3d.prj/BLDGBOOM.C_V  $
 * 
 *    Rev 1.10   24 Apr 1997 14:26:12   JEREMIAH
 * Changed texture loading calls to 
 * accomodate specification of texture 
 * formats.
 * 
 *    Rev 1.9   10 Apr 1997 11:03:32   JEREMIAH
 * Load semitransparent resources for 
 * SEMIFANCY transparency type.
 * 
 *    Rev 1.8   21 Mar 1997 11:30:30   JEREMIAH
 * Reversed the order of the init of smoke and fire
 * so smoke wouldn't occlude fire on the ati.
 * 
 *    Rev 1.7   12 Mar 1997 12:36:58   JEREMIAH
 * Load new fire resource if semi-transparency
 * is used.
 * 
 *    Rev 1.6   21 Feb 1997 15:58:44   BRUCE
 * put honor into gamestates, made one honor
 * for each level.
 * 
 *    Rev 1.5   14 Feb 1997 19:12:14   BRUCE
 * removed 47TEK_RL stuff
 * removed g_level
 * replaced In3dMovie with global thingy.
 * 
 *    Rev 1.4   27 Jan 1997 10:40:50   JEREMIAH
 * Added extra level of indirection to particle
 * system textures to allow sharing textures.
 * 
 *    Rev 1.3   22 Jan 1997 18:10:34   TIM
 * Make fire and smoke only load once
 * 
 *    Rev 1.2   20 Dec 1996 17:06:40   JEREMIAH
 * Changed filenames of textures to match
 * new filename conventions for level-specific
 * palettes.
 * 
 *    Rev 1.1   Oct 21 1996 13:06:10   JEREMIAH
 * Patched error from attempt at texture 
 * sharing in fire and smoke particle 
 * systems.
***********************************************************************/

// Adding by Liu Song
#include "rl2d3d.h"
#include "wrapper.h"
#include "mybuild.h"
#include "global.h"
#include "d3dappi.h"
DWORD GSize;
extern LPDIRECT3DRM lpD3DRM;
extern LPDIRECTDRAWCLIPPER lpDDClipper;
extern BOOL bQuit;
extern DWORD TCount, VCount, NCount;
extern D3DVERTEX *GVertices;
extern D3DTRIANGLE *GTriangles;
//extern int g_level;

extern EbInfo GebInfo[GEB_COUNT];
extern EbInfo SebInfo[SEB_COUNT];

#pragma warning( disable : 4113)

#ifdef MINIWIN
#include "miniwin/windows.h"
#else
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#endif


#include "landscap.h"
#include "building.h"
#include "spritlib.h"
#include "psystem.h"
#include "gosys.h"
#include "bldgboom.h"
#include "ybsnd.h"
#include "stdlib.h"

#define MAX_DEAD_BUILDINGS 6

#define INFERNO_TIME (20*30)

#define FIRE_START_TIME (INFERNO_TIME - 0.0*30)
#define SMOKE_START_TIME (INFERNO_TIME - 0.5*30)
#define FIRE_END_TIME (INFERNO_TIME - 6*30)

#define CRUMPLE_START_TIME (INFERNO_TIME - 0.75*30)
#define CRUMPLE_END_TIME (INFERNO_TIME - 4*30)

extern RLFrame Wscene, Wcamera, behindthescene;
//extern GDPLIST gdlist;
static GDPLIST* failed = NULL;

typedef struct
{
	int slot;
	int flag;
	building *building;
} Crumple;
Crumple crumples[MAX_DEAD_BUILDINGS];

typedef struct _scortchedearth {
	RLFrame spot;
	RLValue countdown;
	Psystem *fire;
	Psystem *smoke;
	RLVector collision;
	int *damage;
	GDPLIST *gdlist;
	RLValue bldgscale;
	int crumpleflag;
	Crumple *crumple;
} ScorchedEarth;

static ScorchedEarth ScorchedList[MAX_DEAD_BUILDINGS];
int crumpling=0;
D3DTEXTUREHANDLE firetex, smoketex, firetexmask, smoketexmask;

void InitConflagration()
{
	int i;
	static LPTEXTURESTRUCT lpFireTexStruct, lpSmokeTexStruct;
	extern RLDevice Wdevice;


//void makefire(Psystem** fire, LPDIRECT3DRMFRAME theframe, 
//				LPDIRECT3DRMFRAME camera, LPSTR ppmfile);
//void makesmoke(Psystem** smoke, LPDIRECT3DRMFRAME theframe, 
//				LPDIRECT3DRMFRAME camera, LPSTR ppmfile);
	
	// Should preload single set of textures and share between all fire/smoke psystems
	// Need to fix ReleaseOneTexture() to make it work, however.
	lpFireTexStruct = LQHCreateTexture(Wdevice, ConstructLevelName(
      (d3dapprs.transparency == FANCY || d3dapprs.transparency == SEMIFANCY || d3dapprs.transparency == TRANSLUCENT ?
      "firet.bmp" : "fire.bmp")), 4);
	lpSmokeTexStruct = LQHCreateTexture(Wdevice, ConstructLevelName("smoke.bmp"), 1);
	for (i = 0; i < MAX_DEAD_BUILDINGS; i++) 
	{
		ScorchedList[i].countdown = RLVal(0.0);
		ScorchedList[i].crumpleflag = 0;
		ScorchedList[i].spot = RLCreateFrame(behindthescene);

		makesmoke(&(ScorchedList[i].smoke), ScorchedList[i].spot, Wcamera, 
			&lpSmokeTexStruct);
		makefire(&(ScorchedList[i].fire), ScorchedList[i].spot, Wcamera, 
			&lpFireTexStruct);
	}
}

//##ifndef LSMASK
void CowboyDeathMarch(building *DeadBuilding,RLVector *CollisionVector)
{
	int i, slot, mincount;
	RLValue x, z;

	slot  =  MAX_DEAD_BUILDINGS;
	// Find next free slot for inferno
	mincount = INFERNO_TIME;
	for (i=0;i<MAX_DEAD_BUILDINGS;i++) {
		if (ScorchedList[i].countdown < mincount) {
			slot = i;
			mincount = (int)ScorchedList[i].countdown;
		}
	}
	
	if (slot==MAX_DEAD_BUILDINGS) return;

	ScorchedList[slot].crumple = crumples + slot;
	ScorchedList[slot].crumple->building = DeadBuilding;
	ScorchedList[slot].crumple->slot = slot;
	ScorchedList[slot].crumple->flag = 0;

	RLFrameAddChild(Wscene, ScorchedList[slot].spot);
	x = DeadBuilding->x_world - RLVal(LANDXCENTER);
	z = DeadBuilding->z_world - RLVal(LANDZCENTER);
	RLFrameSetPosition(ScorchedList[slot].spot, Wscene,
		    x, SpuddeMapHeight2(x, z), z);
	ScorchedList[slot].collision.x = CollisionVector->x;
	ScorchedList[slot].collision.y = CollisionVector->y;
	ScorchedList[slot].collision.z = CollisionVector->z;
	ScorchedList[slot].crumpleflag = 2;
	DeadBuilding->cur_damage = DeadBuilding->max_damage;
	ScorchedList[slot].damage = &(DeadBuilding->cur_damage);
	ScorchedList[slot].countdown = RLVal(INFERNO_TIME);
	if (DeadBuilding->building_num != -1) {
		char text[80];
		extern int Vmode;
		extern char monstername[7][16];
		extern char targetname[7][3][32];
//		extern int honor;
//		extern BOOL In3DMovie;

		YBPlay3DSound(BigBuildingBoom, ScorchedList[slot].spot);
		if (DeadBuilding->building_num <66) {
			if (DeadBuilding->building_num == 13) 
				sprintf(text, "THE %s HAS BEEN DESTROYED!", targetname[GameStates.CurrentLevel][0]);
			else if (DeadBuilding->building_num == 15) 
				sprintf(text, "THE %s HAS BEEN DESTROYED!", targetname[GameStates.CurrentLevel][1]);
			else if (DeadBuilding->building_num == 20) 
				sprintf(text, "THE %s HAS BEEN DESTROYED!", targetname[GameStates.CurrentLevel][2]);
			YBSetSubTitle2(Vmode, text, RGB(0, 0, 255));
			if (GameStates.CurrentLevel!=Trainer && !GameStates.Is3DMovie)
			{
				if (GameStates.LevelHonor[GameStates.CurrentLevel]) 
					failed=DeadBuilding->displist;
				GameStates.LevelHonor[GameStates.CurrentLevel] = FALSE;
			}
		} else {
			if (DeadBuilding->building_num == 66) 
				sprintf(text, "%s ALPHA HAS HATCHED!", monstername[GameStates.CurrentLevel]);
			else if (DeadBuilding->building_num == 67) 
				sprintf(text, "%s BETA HAS HATCHED!", monstername[GameStates.CurrentLevel]);
			else if (DeadBuilding->building_num == 68) 
				sprintf(text, "%s GAMMA HAS HATCHED!", monstername[GameStates.CurrentLevel]);
			YBSetSubTitle3((short)Vmode, text, RGB(255, 0, 0));
		}
	}
	else
		YBPlay3DSound(SmallBldgBoom, ScorchedList[slot].spot);

	ScorchedList[slot].gdlist = DeadBuilding->displist;
	if (DeadBuilding->building_num < 0) ScorchedList[slot].bldgscale = RLMultiply(RLVal(DeadBuilding->scale), RLVal(1));
	else ScorchedList[slot].bldgscale = RLMultiply(RLVal(DeadBuilding->building.max.y), RLVal(-1));
	if ((DeadBuilding->building_num < 0))
		if (rand()&1) YBPlay3DSound(Screams1, ScorchedList[slot].spot);
		else YBPlay3DSound(Screams2, ScorchedList[slot].spot);
	RLFrameAddCallback(ScorchedList[slot].spot, Scorch, (void*) &ScorchedList[slot]);
}

void Scorch(RLFrame frame, void* arg)
{
	ScorchedEarth* inferno = (ScorchedEarth*) arg;
	// RLVector urhere;
	extern RLValue DiffFrame;

	if (inferno->countdown > RLVal(0)) {
		inferno->countdown-=DiffFrame;
		if ((inferno->countdown < FIRE_START_TIME) && (inferno->countdown > SMOKE_START_TIME)/**/ && !(inferno->fire->active)/**/) {
/**/			ActivateParticleSystem(inferno->fire, -1);
	    	inferno->fire->properties->scalefactor = RLVal(1.25);
	    	//inferno->fire->properties->speed = RLVal( 0.12);
		    inferno->fire->properties->direction.y = RLVal(80.0);
		    inferno->fire->properties->origin.x = RLVal(0.0);
		    inferno->fire->properties->origin.y = RLVal(0.0);
		    inferno->fire->properties->origin.z = RLVal(0.0);/**/
/*
			RLFrameGetPosition(Wcamera, inferno->fire->frame, &urhere);
	    	inferno->fire->properties->scalefactor = RLVal(1.5);
		    inferno->fire->properties->origin.x = RLVal(0.0);
		    inferno->fire->properties->origin.y = RLVal(0.0);
		    inferno->fire->properties->origin.z = RLVal(0.0);
		    inferno->fire->properties->direction.x = urhere.x;
		    inferno->fire->properties->direction.y = urhere.y;
		    inferno->fire->properties->direction.z = urhere.z;
*/
		}
/**/		if (inferno->fire->properties->scalefactor > RLVal(0.9)) 
			inferno->fire->properties->scalefactor *= RLVal(1) - RLMultiply(DiffFrame, RLVal(0.0030));
/**/		//inferno->fire->properties->scalefactor -= RLMultiply3(DiffFrame, RLVal(0.1), RLVal(FIRE_START_TIME - FIRE_END_TIME));
/**/		if ((inferno->countdown < SMOKE_START_TIME)) {
			ActivateParticleSystem(inferno->smoke, -1);
		    inferno->smoke->properties->direction.y = RLVal(80.0);
		    inferno->smoke->properties->origin.x = RLVal(0.0);
		    inferno->smoke->properties->origin.y = RLVal(0.0);
		    inferno->smoke->properties->origin.z = RLVal(0.0);/**/
/*
		    inferno->fire->properties->origin.x = RLVal(0.0);
		    inferno->fire->properties->origin.y = RLVal(-1.0);
		    inferno->fire->properties->origin.z = RLVal(0.0);
		    inferno->fire->properties->direction.x = RLVal(0.0);
		    inferno->fire->properties->direction.y = RLVal(200.0);
		    inferno->fire->properties->direction.z = RLVal(0.0);
	    	inferno->fire->properties->scalefactor = RLVal( 0.865);
*/
/**/		}/**/
		if ((inferno->countdown <= CRUMPLE_START_TIME) && (inferno->crumpleflag)) {
			if (inferno->crumpleflag == 2)
	            YBPlay3DSound(Crumble, inferno->spot);
	            //if (inferno->bldgscale > RLVal(0)) 
	         	//   YBPlay3DSound(SmallBldgBoom, inferno->spot);
			    //  else 
			 	//      YBPlay3DSound(BigBuildingBoom, inferno->spot);

			inferno->crumpleflag = CrumpleBuilding(inferno->gdlist, 
				(RLVector*)(inferno->crumple),
				inferno->bldgscale,
				RLVal(CRUMPLE_START_TIME)-inferno->countdown);
			if (inferno->crumpleflag == 0) {
				FinishDestroyingBuilding(inferno->gdlist, inferno->damage);
				if (failed==inferno->gdlist) {
					YBPlaySound(Failure);
					failed = NULL;
				}
			}
		}

/**/		if (inferno->countdown < FIRE_END_TIME)
			DeactivateParticleSystem(inferno->fire);

		if ((inferno->countdown > FIRE_END_TIME) && (inferno->countdown < FIRE_START_TIME) && !(rand()&0x7))
			YBPlay3DSound(FireFireFire, inferno->fire->frame);/**/

		{
			RLVector place;
			RLVector4d place4d;
			extern RLValue TheHorizon;
			extern RLViewport Wview;

/**/			RLFrameGetPosition(inferno->spot, Wscene, &place);
			if ((place.x > cGlobals.xmax) || (place.x < cGlobals.xmin) || (place.z > cGlobals.zmax) || (place.z < cGlobals.zmin)) {
				RLViewportTransform(Wview, &place4d, &place);
				place4d.y = TheHorizon*place4d.w;
				RLViewportInverseTransform(Wview, &place, &place4d);
			}
			RLFrameSetPosition(inferno->smoke->frame, Wscene, place.x, place.y, place.z);
			RLFrameSetPosition(inferno->fire->frame, Wscene, place.x, place.y, place.z);
/**/		}
	} else {
		DeactivateParticleSystem(inferno->smoke);
		RLFrameAddChild(behindthescene, frame);
		RLFrameRemoveCallback(frame, Scorch, inferno);
		inferno->countdown = RLVal(0);
	}
}

int CrumpleBuilding(GDPLIST* gdlist, RLVector* collision, RLValue scale, RLValue count)
{
	extern RLValue DiffFrame;
	int i, flag;
	RLValue oomph = RLMultiply3(DiffFrame, RLVal(count), RLVal(0.02));

	D3DEXECUTEBUFFERDESC desc;
	EbInfo *ebInfo;
	Crumple *crumple;
	crumple = (void*)collision;

	crumpling = 1;

	flag = 0;

	if (scale > RLVal(0)) 
	{	// Generic Building
		LPDIRECT3DRMFRAME frame;
		EbInfo *temp, *info;

		ebInfo = GebInfo + crumple->slot +6;
		if (crumple->building->tv == 0.0)
			temp = &GebInfo[0];
		else if (crumple->building->tu == 0.0)
			temp = &GebInfo[1];
		else
			temp = &GebInfo[2];
		info = temp + 3;
		frame = crumple->building->rlframe;

		desc.dwSize = sizeof(desc);
		desc.dwFlags = 0;
		ebInfo->eb->lpVtbl->Lock(ebInfo->eb, &desc);
		ebInfo->v = (void*) ((char*) desc.lpData);
		desc.dwSize = sizeof(desc);
		desc.dwFlags = 0;
		info->eb->lpVtbl->Lock(info->eb, &desc);
		info->v = (void*) ((char*) desc.lpData);

		if (!crumple->flag)
		{
			desc.dwSize = sizeof(desc);
			desc.dwFlags = 0;
			temp->eb->lpVtbl->Lock(temp->eb, &desc);
			temp->v = (void*) ((char*) desc.lpData);
			memcpy(ebInfo->v, temp->v, GSize);
			temp->eb->lpVtbl->Unlock(temp->eb);
			frame->lpVtbl->AddVisual(frame, (LPDIRECT3DRMVISUAL)ebInfo->uvis);
			frame->lpVtbl->DeleteVisual(frame, (LPDIRECT3DRMVISUAL)temp->uvis);
			crumple->flag = 1;
		}

		for (i=0; i<gdlist->vc; i++)
		{
			if (ebInfo->v[i].y <= info->v[i].y)
				continue;
			if (rand() & 3)
			{
				if (ebInfo->v[i].ny > RLVal(0.5))
				{
					if (ebInfo->v[i].y > RLDivide(RLVal(oomph), scale))
					{
						ebInfo->v[i].y -= RLDivide(RLVal(oomph), scale);
						flag = 1;
					}
					else
					{
						ebInfo->v[i].y = RLDivide(RLVal(rand()&0x1f), (RLVal(1024)));
					}
				}
				else
				{
					if (ebInfo->v[i].y > RLDivide(RLVal(oomph), scale))
					{
						flag = 1;
						ebInfo->v[i].x += RLMultiply3(DiffFrame, ebInfo->v[i].x, -RLVal(0.001));
						ebInfo->v[i].z += RLMultiply3(DiffFrame, ebInfo->v[i].z, -RLVal(0.001));
						ebInfo->v[i].y -= RLDivide(RLVal(oomph), scale);
					}
					else
					{
						ebInfo->v[i].y = RLDivide(RLVal(rand()&0x1f), (RLVal(1024)));
					}
				}
			}
		} 
		info->eb->lpVtbl->Unlock(info->eb);
		if (!flag)
		{
			temp += 3;
		/*	desc.dwSize = sizeof(desc);
			desc.dwFlags = 0;
			temp->eb->lpVtbl->Lock(temp->eb, &desc);
			temp->v = (void*) ((char*) desc.lpData);
			memcpy(temp->v, ebInfo->v, GSize);
			temp->eb->lpVtbl->Unlock(temp->eb);
		*/	frame->lpVtbl->AddVisual(frame, (LPDIRECT3DRMVISUAL)temp->uvis);
			frame->lpVtbl->DeleteVisual(frame, (LPDIRECT3DRMVISUAL)ebInfo->uvis);
		}
		ebInfo->eb->lpVtbl->Unlock(ebInfo->eb);
	}
	else 
	{	// Specific building
		int num;

		switch (crumple->building->building_num)
		{
		case 13:
			num = 0;
			break;
		case 15:
			num = 1;
			break;
		case 20:
			num = 2;
			break;
		case 66:
			num = 3;
			break;
		case 67:
			num = 4;
			break;
		case 68:
			num = 5;
			break;
		}
		ebInfo = &SebInfo[num];

		desc.dwSize = sizeof(desc);
		desc.dwFlags = 0;
		ebInfo->eb->lpVtbl->Lock(ebInfo->eb, &desc);
		ebInfo->v = (void*) ((char*) desc.lpData);

		for (i=0; i<gdlist->vc; i++)
		{
			if (rand()&3)
			{
				if (ebInfo->v[i].ny > RLVal(0.5))
				{
					if (ebInfo->v[i].y > RLMultiply(RLVal(oomph), RLVal(1)))
					{
						ebInfo->v[i].y -= RLMultiply(RLVal(oomph), RLVal(1));
						flag = 1;
					}
					else
					{
						ebInfo->v[i].y = RLDivide(RLVal(rand() & 0x1f), (RLVal(1024)));
					}
				}
				else
				{
					if (ebInfo->v[i].y > RLMultiply(RLVal(oomph), RLVal(1)))
					{
						flag = 1;
						ebInfo->v[i].x += RLMultiply3(DiffFrame, ebInfo->v[i].x, -RLVal(0.001));
						ebInfo->v[i].z += RLMultiply3(DiffFrame, ebInfo->v[i].z, -RLVal(0.001));
						ebInfo->v[i].y -= RLMultiply(RLVal(oomph), RLVal(1));
					}
					else
					{
						ebInfo->v[i].y = RLDivide(RLVal(rand()&0x1f), (RLVal(1024)));
					}
				}
			}
		} 
		if (!flag)
		{
		//	int i;
			for (i = 0; i < gdlist->vc; i++)
			{
				ebInfo->v[i].y = RLVal((rand() & 0xff ) / 1024.0);
			}
		}
		ebInfo->eb->lpVtbl->Unlock(ebInfo->eb);
	}
	return flag;
}


void FinishDestroyingBuilding(GDPLIST *gdlist, int *thisdamage)
{
	(*thisdamage)++;
	crumpling = 0;
}


void DestroyConflagration()
{
	int i;

	for (i=0;i<MAX_DEAD_BUILDINGS;i++) {
		if (ScorchedList[i].fire->active) 
			DeactivateParticleSystem(ScorchedList[i].fire);
		if (ScorchedList[i].smoke->active) 
			DeactivateParticleSystem(ScorchedList[i].smoke);
		if (ScorchedList[i].countdown) 
			RLFrameRemoveCallback(ScorchedList[i].spot, Scorch, (void*) &ScorchedList[i]);
		//DestroyParticleSystem(&(ScorchedList[i].fire));
		//DestroyParticleSystem(&(ScorchedList[i].smoke));
		RLFrameRemoveChild(RLFrameGetParent(ScorchedList[i].spot), ScorchedList[i].spot);
	}
}
//##endif LSMASK

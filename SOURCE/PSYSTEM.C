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
File:           psystem.c
Author:         J. Spudde Childs
Date:           9-27-95
Version:        1.05



************************************************************************
REVISION HISTORY        (Add Edits and History to top of list).

Edited By:      Jeremiah Spudde Childs
Edited Date:    11/17/95
Changes:
                Changed Version number to 1.05.
                Added CreateSmoke().  Added initialization of wind member
				of properties structures for all psystems.


Edited By:      Jeremiah Spudde Childs
Edited Date:    11/14/95
Changes:
                Added CreateFire().  Modified CreateSixShooter() to be a particle system.

Edited By:      Bruce Abe
Edited Date:    11/07/95
Changes:
                added an #include "boink.h" because Robotmove and monmove require it.

Edited By:      Jeremiah Spudde Childs
Edited Date:    10/24/95
Changes:
                changed VERSION_NUMBER from 1.03 to 1.04.
				Changed CreateZap() to be a CxSprite and added makeclouds() function.

Edited By:      Jeremiah Spudde Childs
Edited Date:    10/2/95
Changes:
                changed VERSION_NUMBER from 1.02 to 1.03.
				Added CreateSixShooter() function.

Edited By:      Jeremiah Spudde Childs
Edited Date:    10/2/95
Changes:
                changed VERSION_NUMBER from 1.01 to 1.02.
				modified makedust(), MakePlasma(), CreateZap(), MakeExplosion(),
				to add opacity maps to the textures to accomidate using quads
				instead of decals for the particle systems.

***********************************************************************

Edited By:      Jeremiah Spudde Childs
Edited Date:    9/28/95
Changes:
                changed VERSION_NUMBER from 1.001 to 1.01.
				modified makedust(), MakePlasma(), CreateZap(), MakeExplosion(),
				to call ReplaceGif() if texture has already been loaded.

***********************************************************************


Edited By:      Jeremiah Spudde Childs
Edited Date:    9/28/95
Changes:
                changed VERSION_NUMBER from 1.0 to 1.001.
				added #include "loadgif.h"

***********************************************************************/
#ifdef MINIWIN
#include "miniwin/d3drm.h"
#else
#include <d3drmwin.h>
#endif
#include "mdtex.h"
#include "spritlib.h"
#include "psystem.h"
#include "boink.h"
#include "Robotmove.h"
#include "monmove.h"
#include "gosys.h"
#include "clutter.h"
#include "global.h"
#include "d3dappi.h"

extern LPDIRECT3DRMFRAME Wscene;
extern LPDIRECT3DRMFRAME behindthescene;
extern LPDIRECT3DRMFRAME Robotframe;
extern LPDIRECT3DRMFRAME monstframe;
extern LPDIRECT3DRMFRAME Wcamera;
extern LPDIRECT3DRMDEVICE Wdevice;

#ifdef _47TEK_RL_
	void dustcloud(LPDIRECT3DRMFRAME dustmaker, void* arg);
#endif

#ifdef _ITC_D3D_
	void dustcloud(LPDIRECT3DRMFRAME dustmaker, void* arg, RLValue delta);
#endif
/*
void ApplyMask(RLTexture texture, RLTexture masktexture)
{
	RLImage* maskimg;

	maskimg = RLTextureGetImage(masktexture);
	RLTextureSetOpacity(texture, maskimg);
}

*/
/*
int MallocPsytem(Psystem** psystem)
{
    *psystem = (Psystem*)malloc(sizeof(Psystem));
    if (!*psystem)
	{
        goto ret_with_error;
    }
	memset(*psystem, 0, sizeof(Psystem));
	
	return TRUE;

ret_with_error:
    if (*psystem)
	{
        free(*psystem);
	}
	return FALSE;
}
*/

void makedust(Psystem** dust, LPDIRECT3DRMFRAME theframe, 
			  LPDIRECT3DRMFRAME camera, LPTEXTURESTRUCT *lplpDustTexStruct)
{
    static Pprop* dustpr;
    Svis *dustvis;
	int i;

	dustpr = (Pprop*)malloc(sizeof(Pprop));

	dustpr->perterb.x = D3DVAL(0.2);
	dustpr->perterb.y = D3DVAL(0.1);
	dustpr->perterb.z = D3DVAL(0.2);
	dustpr->speed = D3DVAL(0.25);
	dustpr->origin.x = D3DVAL(0);
	dustpr->origin.y = D3DVAL(0);
	dustpr->origin.z = D3DVAL(0);
	dustpr->direction.x = D3DVAL(0);
	dustpr->direction.y = D3DVAL(0.5);
	dustpr->direction.z = D3DVAL(1.0);
	dustpr->scalefactor = D3DVAL(1.2);
	dustpr->wind = D3DVAL(0.25);
	dustpr->acc = D3DVAL(0x4000/65536.0);
	dustpr->maxv = D3DVAL(0x10000/65536.0);
	dustpr->num = 4;
   if (detail==5) dustpr->num += 2;

	dustvis = (Svis*)malloc(sizeof(Svis));

	dustvis->sx = D3DVAL(0.4);
	dustvis->sy = D3DVAL(0.4);
	dustvis->x1 = (float)0.0;
	dustvis->y1 = (float)0.0;
	dustvis->x2 = D3DVAL(1.0);
	dustvis->y2 = D3DVAL(0.25);
   dustvis->transptype = DARKTYPETRANSP;

	// alocate memory for system
	*dust = (Psystem*)malloc(sizeof(Psystem));

	(*dust)->lplpTexStruct = lplpDustTexStruct;   //LQHCreateTexture(Wdevice, ConstructLevelName(ppmfile));
	CreateParticleSystem(*dust, theframe, camera, dustpr, dustvis);

	//RLFrameAddCallback(theframe, dustcloud, (void*) *dust);
	theframe->lpVtbl->AddMoveCallback(theframe, dustcloud, (void*) *dust);

	for (i = 0; i < dustpr->num; i++) 
	{
		(*dust)->particles[i]->flag1 = 0;
	}
	/*
	//for testing which psystem 96.08.15
	for (i = 0; i < dustpr->num; i++) 
	{
		strcpy((*dust)->particles[i]->plane->name, "dust");
	}*/
	/////////////////////////////////////
	//ReleaseOneTexture(dustvis->lpTexStruct);
	//free(dustvis->lpTexStruct);
	free(dustvis);
}


void MakeExplosion(Psystem** explo, LPDIRECT3DRMFRAME theframe, 
				   LPDIRECT3DRMFRAME camera)
{
    static Pprop *Explodepr;
    static Svis *Explodevis;
    static LPTEXTURESTRUCT lptexturestructure = NULL;
	//int i;

	Explodepr = (Pprop*)malloc(sizeof(Pprop));
    Explodepr->perterb.x = D3DVAL(104801/65536.0);//tempdata; //D3DVALUE(104801/65536.0);
    Explodepr->perterb.y = D3DVAL(104801/65536.0);
    Explodepr->perterb.z = D3DVAL(104801/65536.0);
    Explodepr->speed = D3DVAL(752.6/65536.0);
    Explodepr->origin.x = D3DVAL(0);
    Explodepr->origin.y = D3DVAL(0);
    Explodepr->origin.z = D3DVAL(0);
    Explodepr->direction.x = D3DVAL(0.0);
    Explodepr->direction.y = D3DVAL(0.0);
    Explodepr->direction.z = D3DVAL(188789/65536.0);
    Explodepr->scalefactor = D3DVAL(54784/65536.0);
	Explodepr->wind = D3DVAL(0.0);
    Explodepr->acc = D3DVAL(8704/65536.0);
    Explodepr->maxv = D3DVAL(0x10000/65536.0);
    Explodepr->num = 10;

	Explodevis = (Svis*)malloc(sizeof(Svis));

    Explodevis->sx = D3DVAL(1.5);
    Explodevis->sy = D3DVAL(1.5);
    Explodevis->x1 = D3DVAL(0);
    Explodevis->y1 = D3DVAL(0);
    Explodevis->x2 = D3DVAL(1);
    Explodevis->y2 = D3DVAL(1);
    Explodevis->transptype = BRIGHTTYPETRANSP;
	
	*explo = (Psystem*)malloc(sizeof(Psystem));

	(*explo)->lplpTexStruct = &lptexturestructure;
   lptexturestructure = LQHCreateTexture(Wdevice, ConstructRobotName(GameStates.CurrentRobot, 
      (d3dapprs.transparency == FANCY || d3dapprs.transparency == SEMIFANCY || d3dapprs.transparency == TRANSLUCENT ?
      "spkt.bmp" : "spk.bmp")), 4);

    CreateParticleSystem(*explo, theframe, camera, Explodepr, Explodevis);
	/*
	//for testing which psystem 96.08.15
	for (i = 0; i < Explodepr->num; i++) 
	{
		strcpy((*explo)->particles[i]->plane->name, "explode");
	}*/
	/////////////////////////////////////
	//ReleaseOneTexture(Explodevis->lpTexStruct);
	//free(Explodevis->lpTexStruct);
	free(Explodevis);
}


#ifdef _47TEK_RL_
	void dustcloud(LPDIRECT3DRMFRAME dustmaker, void* arg)
#endif

#ifdef _ITC_D3D_
	void dustcloud(LPDIRECT3DRMFRAME dustmaker, void* arg, RLValue delta)
#endif
{
	Psystem* dust = (Psystem*) arg;
	int isdusty, i, tile;
	D3DVECTOR place;
	extern D3DVALUE texturecutoffs[], landscale;
	D3DVALUE offset;

    if (dustmaker == Robotframe) 
    {
		isdusty = ((RobotMovementState != RobotWaiting) && (RobotMovementState != RobotJumping) && (RobotMovementState != RobotAirborne) && (RobotMovementState != RobotStopped) && (RobotMovementState != RobotWaitingOnBuilding));
	}
	else 
	{
		isdusty = ((MonsterMovementState != MonsterWaiting) && (MonsterMovementState != MonsterJumping) && (MonsterMovementState != MonsterAirborne) && (MonsterMovementState != MonsterStopped));
	}
	if (isdusty) 
	{
		if (dust->active != 1) 
		{
			ActivateParticleSystem(dust, -1);
		}
		if ((((dustmaker == Robotframe) && ((RobotMovementState < RobotFDecelerating) || (RobotMovementState > RobotWaitingOnBuilding && RobotMovementState < RobotFDeceleratingOnBuilding) )) || 
   		((dustmaker == monstframe) && (MonsterMovementState < MonsterFDecelerating)))) 
		{
       		dust->properties->direction.z = D3DVAL(1); 
		} 
		else 
		{
			dust->properties->direction.z = D3DVAL(-1); 
		}
	} 
	else 
	{
	   if ((dust->active == 1) && (dust->ttl == -1)) 
	   {
		   dust->ttl = 1;
	   }
    }

	dustmaker->lpVtbl->GetPosition(dustmaker, Wscene, &place);
	
	tile = 0;
	for (i = 0; i < 4; i++) 
	{
		if (landscale * place.y >= texturecutoffs[i]) 
		{
			tile = i;  
		}
	}
	if (tile != dust->particles[0]->flag1) 
	{
		offset = D3DDivide(D3DVAL(tile - dust->particles[0]->flag1), D3DVAL(4));
		for (i=0;i<dust->properties->num;i++) 
		{
			//dust->particles[i]->v1 += offset;	//Dongmin will modify
			//dust->particles[i]->v2 += offset;
			dust->particles[i]->plane->x1 = D3DVAL(0);
			dust->particles[i]->plane->x2 = D3DVAL(1);
			dust->particles[i]->plane->y1 = D3DVAL(tile * 0.25);
			dust->particles[i]->plane->y2 = D3DVAL((tile + 1) * 0.25);
			dust->particles[i]->flag1 = tile;
		}
	}
}


CxSprite* CreateZap(LPDIRECT3DRMFRAME parent)
{
	CxSprite* zap;
	//LPTEXTURESTRUCT lpTexStruct;

/*	
    if (RLObjectExists(monstzaptex) == RLNoError)
		ReplaceGif(monstzaptex, ConstructMonsterName("zap.gif"));
	else
    	monstzaptex = RLLoadGif(ConstructMonsterName("zap.gif"), NULL);
    if (RLObjectExists(monstzaptexmask) == RLNoError)
		ReplaceGif(monstzaptexmask, ConstructMonsterName("map.gif"));
	else {
    	monstzaptexmask = RLLoadGif(ConstructMonsterName("map.gif"), NULL);
		ApplyMask(monstzaptex, monstzaptexmask);
		RLIMInitialiseSurfaceInfo(Wdevice, theonlymaterial, theonlycolor, monstzaptex, &monstzapsurf);
	}
*/
// create space for the complex sprite structure
	zap = (CxSprite*)malloc(sizeof(CxSprite));

	zap->lpTexStruct = LQHCreateTexture(Wdevice, ConstructLevelName(ConstructMonsterName("zap.bmp")), 1);
	CreateCxDisplayList(zap, parent, zap->lpTexStruct->hTex);
	/*
	//for testing which psystem 96.08.15
	strcpy(zap->plane->name, "monzap");
	/////////////////////////////////////
	*/
	//ReleaseOneTexture(lpTexStruct);
	//free(lpTexStruct);
	return(zap);
}

CxSprite* CreateRobotZap(LPDIRECT3DRMFRAME parent, LPSTR ppmfile)
{
	CxSprite* zap;
	//LPTEXTURESTRUCT lpTexStruct;

	// create space for the complex sprite structure
	zap = (CxSprite*)malloc(sizeof(CxSprite));

	zap->lpTexStruct = LQHCreateTexture(Wdevice, 
		ConstructRobotName(GameStates.CurrentRobot, ppmfile), 4);
	CreateCxDisplayList(zap, parent, zap->lpTexStruct->hTex);
	/*
	//for testing which psystem 96.08.15
	strcpy(zap->plane->name, "Robotzap");
	/////////////////////////////////////
	*/
	//ReleaseOneTexture(lpTexStruct);
	//free(lpTexStruct);
	return(zap);
}


void CreateSonicShooter(Psystem** sixshooter, LPDIRECT3DRMFRAME theframe, 
						LPSTR ppmfile)
{
    Svis *bulletvis;
    static Pprop* sixshooterpr;
    static LPTEXTURESTRUCT lptexturestructure = NULL;
	int i;

	bulletvis = (Svis*)malloc(sizeof(Svis));
	/*
    if (RLObjectExists(sonictex) == RLNoError)
		ReplaceGif(sonictex, bitmap);
	else
    	sonictex = RLLoadGif(bitmap, NULL);
    if (RLObjectExists(sonictexmask) == RLNoError)
		ReplaceGif(sonictexmask, mask);
	else {
    	sonictexmask = RLLoadGif(mask, NULL);
		ApplyMask(sonictex, sonictexmask);
		RLIMInitialiseSurfaceInfo(Wdevice, theonlymaterial, theonlycolor, sonictex, &(sonicsurface));
	}
	*/

	*sixshooter = (Psystem*)malloc(sizeof(Psystem));

	(*sixshooter)->lplpTexStruct = &lptexturestructure;
   lptexturestructure = LQHCreateTexture(Wdevice, ppmfile, 4);


    bulletvis->sx = D3DVAL(0.4);
    bulletvis->sy = D3DVAL(0.4);
    bulletvis->x1 = D3DVAL(0.0);
    bulletvis->y1 = D3DVAL(0.0);
    bulletvis->x2 = D3DVAL(1.0);
    bulletvis->y2 = D3DVAL(1.0);
    bulletvis->transptype = BRIGHTTYPETRANSP;

	sixshooterpr = (Pprop*)malloc(sizeof(Pprop));

    sixshooterpr->perterb.x = D3DVAL(0.0);
    sixshooterpr->perterb.y = D3DVAL(0.0);
    sixshooterpr->perterb.z = D3DVAL(0.0);
    sixshooterpr->speed = D3DVAL(0.0);
    sixshooterpr->origin.x = D3DVAL(0);
    sixshooterpr->origin.y = D3DVAL(0);
    sixshooterpr->origin.z = D3DVAL(0);
    sixshooterpr->direction.x = D3DVAL(0);
    sixshooterpr->direction.y = D3DVAL(0.5);
    sixshooterpr->direction.z = D3DVAL(1.0);
    sixshooterpr->scalefactor = D3DVAL(1.1);
    sixshooterpr->acc = D3DVAL(0.0);
    sixshooterpr->maxv = D3DVAL(0.0);
    sixshooterpr->num = NumberOfSixShooters;

    CreateParticleSystem(*sixshooter, theframe, Wcamera, sixshooterpr, bulletvis);
	
	(*sixshooter)->active = 2; 			// set to 2 to prevent DestroyParticleSystem() from trying to remove a nonexistent callback
	(*sixshooter)->numonscreen = (*sixshooter)->properties->num;
	for (i = 0; i < (*sixshooter)->properties->num;i++) 
	{
		(*sixshooter)->particles[i]->active = 0;
		(*sixshooter)->particles[i]->plane->active = 0;
		(*sixshooter)->particles[i]->frame->lpVtbl->SetRotation(
			(*sixshooter)->particles[i]->frame,
			Wscene, 
			D3DVAL(0), D3DVAL(1), D3DVAL(0), D3DVAL(0));
	}
	//ReleaseOneTexture(bulletvis->lpTexStruct);
	//free(bulletvis->lpTexStruct);
	free(bulletvis);	
}


TEXTURESTRUCT bullettex;

void CreateSixPeaAndCussinShooter(Psystem **sixshooter, Psystem** peashooter, Psystem **cussin, 
								  LPDIRECT3DRMFRAME theframe, LPSTR ppmfile)
{
    Svis *bulletvis;
    static Pprop *peashooterpr, *cussinpr;
    static LPTEXTURESTRUCT lptexturestructure1 = NULL;
    static LPTEXTURESTRUCT lptexturestructure2 = NULL;
	int i;

	bulletvis = (Svis*)malloc(sizeof(Svis));
	/*
    if (RLObjectExists(bullettex) == RLNoError)
		ReplaceGif(bullettex, ConstructRobotName(GameStates.CurrentRobot, suffix));
	else
    	bullettex = RLLoadGif(ConstructRobotName(GameStates.CurrentRobot, suffix), NULL);
    if (RLObjectExists(bullettexmask) == RLNoError)
		ReplaceGif(bullettexmask, ConstructRobotName(GameStates.CurrentRobot, masksuffix));
	else {
    	bullettexmask = RLLoadGif(ConstructRobotName(GameStates.CurrentRobot, masksuffix), NULL);
		ApplyMask(bullettex, bullettexmask);
		RLIMInitialiseSurfaceInfo(Wdevice, theonlymaterial, theonlycolor, bullettex, &(bulletsurface));
	}
	*/
	*sixshooter = (Psystem*)malloc(sizeof(Psystem));
	//*peashooter = (Psystem*)malloc(sizeof(Psystem));
	*cussin = (Psystem*)malloc(sizeof(Psystem));

	(*sixshooter)->lplpTexStruct = &lptexturestructure1;
   lptexturestructure1 = LQHCreateTexture(Wdevice, ConstructRobotName(GameStates.CurrentRobot, ppmfile), 4);
	//(*peashooter)->lpTexStruct = LQHCreateTexture(Wdevice, ConstructRobotName(GameStates.CurrentRobot, ppmfile));
	(*cussin)->lplpTexStruct = &lptexturestructure2;
   lptexturestructure2 = LQHCreateTexture(Wdevice, ConstructRobotName(GameStates.CurrentRobot, ppmfile), 4);

	memset(&bullettex, 0, sizeof(TEXTURESTRUCT));
	MyLoadTexture(Wdevice, ConstructRobotName(GameStates.CurrentRobot, ppmfile), &bullettex, 4);


// peashooter
    bulletvis->sx = D3DVAL(0.1);
    bulletvis->sy = D3DVAL(0.1);
    bulletvis->x1 = D3DVAL(0.0);
    bulletvis->y1 = D3DVAL(0.0);
    bulletvis->x2 = D3DVAL(1.0);
    bulletvis->y2 = D3DVAL(1.0);
    bulletvis->transptype = BRIGHTTYPETRANSP;

    peashooterpr = (Pprop*)malloc(sizeof(Pprop));

    peashooterpr->perterb.x = D3DVAL(0.0);
    peashooterpr->perterb.y = D3DVAL(0.0);
    peashooterpr->perterb.z = D3DVAL(0.0);
    peashooterpr->speed = D3DVAL(0.0);
    peashooterpr->origin.x = D3DVAL(0);
    peashooterpr->origin.y = D3DVAL(0);
    peashooterpr->origin.z = D3DVAL(0);
    peashooterpr->direction.x = D3DVAL(0);
    peashooterpr->direction.y = D3DVAL(0.5);
    peashooterpr->direction.z = D3DVAL(1.0);
    peashooterpr->scalefactor = D3DVAL(1.1);
    peashooterpr->acc = D3DVAL(0.0);
    peashooterpr->maxv = D3DVAL(0.0);
    peashooterpr->num = NumberOfPeaShooters;


// sixshooter
    bulletvis->sx = D3DVAL(1.0);
    bulletvis->sy = D3DVAL(1.0);
    bulletvis->transptype = BRIGHTTYPETRANSP;

    CreateParticleSystem(*sixshooter, theframe, Wcamera, peashooterpr, bulletvis);
	
	(*sixshooter)->active = 2; 			// set to 2 to prevent DestroyParticleSystem() from trying to remove a nonexistent callback
	(*sixshooter)->numonscreen = (*sixshooter)->properties->num;
	for (i = 0; i < (*sixshooter)->properties->num; i++) 
	{
		(*sixshooter)->particles[i]->active = 0;
		(*sixshooter)->particles[i]->frame->lpVtbl->SetRotation(
			(*sixshooter)->particles[i]->frame, Wscene, 
			D3DVAL(0), D3DVAL(1), D3DVAL(0), D3DVAL(0));
	}
	/*
	//for testing which psystem 96.08.15
	for (i = 0; i < peashooterpr->num; i++) 
	{
		strcpy((*sixshooter)->particles[i]->plane->name, "sixshoot");
	}
	/////////////////////////////////////
	*/
// cussin
    bulletvis->sx = D3DVAL(0.4);
    bulletvis->sy = D3DVAL(0.4);
    bulletvis->transptype = BRIGHTTYPETRANSP;

	cussinpr = (Pprop*)malloc(sizeof(Pprop));

    cussinpr->perterb.x = D3DVAL(0.0);
    cussinpr->perterb.y = D3DVAL(0.0);
    cussinpr->perterb.z = D3DVAL(0.0);
    cussinpr->speed = D3DVAL(0.0);
    cussinpr->origin.x = D3DVAL(0);
    cussinpr->origin.y = D3DVAL(0);
    cussinpr->origin.z = D3DVAL(0);
    cussinpr->direction.x = D3DVAL(0);
    cussinpr->direction.y = D3DVAL(0.5);
    cussinpr->direction.z = D3DVAL(1.0);
    cussinpr->scalefactor = D3DVAL(1.1);
    cussinpr->acc = D3DVAL(0.0);
    cussinpr->maxv = D3DVAL(0.0);
    cussinpr->num = NumberOfSixShooters;

    CreateParticleSystem(*cussin, theframe, Wcamera, cussinpr, bulletvis);
	
	(*cussin)->active = 2; 			// set to 2 to prevent DestroyParticleSystem() from trying to remove a nonexistent callback
	(*cussin)->numonscreen = (*cussin)->properties->num;
	for (i = 0; i < (*cussin)->properties->num; i++) 
	{
		(*cussin)->particles[i]->active = 0;
		(*cussin)->particles[i]->plane->active = 0;
		(*cussin)->particles[i]->frame->lpVtbl->SetRotation(
			(*cussin)->particles[i]->frame,
			Wscene, 
			D3DVAL(0), D3DVAL(1), D3DVAL(0), D3DVAL(0));
	}
	/*
	//for testing which psystem 96.08.15
	for (i = 0; i < peashooterpr->num; i++) 
	{
		strcpy((*cussin)->particles[i]->plane->name, "cussion");
	}*/
	/////////////////////////////////////

	//InitJets(bulletvis->lpTexStruct, NULL);
	//InitJets((*sixshooter)->lpTexStruct, NULL);
	InitJets(&bullettex, NULL);
	//ReleaseOneTexture(bulletvis->lpTexStruct);
	//free(bulletvis->lpTexStruct);
	free(bulletvis);	
}


void makeclouds(Psystem** cloud, LPDIRECT3DRMFRAME theframe, 
				LPDIRECT3DRMFRAME camera, int numclouds)
{
    static Pprop* cloudpr;
    Svis *cloudvis;
    static LPTEXTURESTRUCT lptexturestructure = NULL;
	int i;

	cloudpr = (Pprop*)malloc(sizeof(Pprop));

    cloudpr->perterb.x = D3DVAL(0.0);
    cloudpr->perterb.y = D3DVAL(0.0);
    cloudpr->perterb.z = D3DVAL(0.0);
    cloudpr->speed = D3DVAL(0.0);
    cloudpr->origin.x = D3DVAL(0);
    cloudpr->origin.y = D3DVAL(0);
    cloudpr->origin.z = D3DVAL(0);
    cloudpr->direction.x = D3DVAL(0);
    cloudpr->direction.y = D3DVAL(0.5);
    cloudpr->direction.z = D3DVAL(1.0);
    cloudpr->scalefactor = D3DVAL(1.0);
	cloudpr->wind = D3DVAL(0.0);
    cloudpr->acc = D3DVAL(0.0);
    cloudpr->maxv = D3DVAL(0.0);
    cloudpr->num = numclouds;

	cloudvis = (Svis*)malloc(sizeof(Svis));
	/*
    if (RLObjectExists(cloudtex) == RLNoError)
		ReplaceGif(cloudtex, ConstructLevelName("cloud.gif"));
	else
    	cloudtex = RLLoadGif(ConstructLevelName("cloud.gif"), NULL);
    if (RLObjectExists(cloudtexmask) == RLNoError)
		ReplaceGif(cloudtexmask, ("cloudmap.gif"));
	else {
    	cloudtexmask = RLLoadGif(("cloudmap.gif"), NULL);
		ApplyMask(cloudtex, cloudtexmask);
		RLIMInitialiseSurfaceInfo(Wdevice, theonlymaterial, theonlycolor, cloudtex, &(cloudsurface));
	}
	*/
	
	*cloud = (Psystem*)malloc(sizeof(Psystem));

	(*cloud)->lplpTexStruct = &lptexturestructure;
   lptexturestructure = LQHCreateTexture(Wdevice, ConstructLevelName("cloud.bmp"), 4);

    cloudvis->sx = D3DVAL(10.0);
    cloudvis->sy = D3DVAL(10.0);
    cloudvis->x1 = D3DVAL(0.0);
    cloudvis->y1 = D3DVAL(0.0);
    cloudvis->x2 = D3DVAL(1.0);
    cloudvis->y2 = D3DVAL(1.0);

    CreateParticleSystem(*cloud, theframe, camera, cloudpr, cloudvis);
	(*cloud)->active = 2; 			// set to 2 to prevent DestroyParticleSystem() from trying to remove a nonexistent callback
	(*cloud)->numonscreen = (*cloud)->properties->num;
	for (i = 0; i < (*cloud)->properties->num; i++) 
	{
		(*cloud)->particles[i]->active = 1;
		(*cloud)->particles[i]->plane->active = 1;
	}	
	/*
	//for testing which psystem 96.08.15
	for (i = 0; i < cloudpr->num; i++) 
	{
		strcpy((*cloud)->particles[i]->plane->name, "cloud");
	}
	/////////////////////////////////////
	*/
	//ReleaseOneTexture(cloudvis->lpTexStruct);
	//free(cloudvis->lpTexStruct);
	free(cloudvis);
}


void makeedges(Psystem** edge, LPDIRECT3DRMFRAME theframe, LPDIRECT3DRMFRAME camera)
{
    static Pprop* edgepr;
    Svis* edgevis;
    static LPTEXTURESTRUCT lptexturestructure = NULL;
	int i;

	edgepr = (Pprop*)malloc(sizeof(Pprop));

    edgepr->perterb.x = D3DVAL(0.0);
    edgepr->perterb.y = D3DVAL(0.0);
    edgepr->perterb.z = D3DVAL(0.0);
    edgepr->speed = D3DVAL(0.0);
    edgepr->origin.x = D3DVAL(0);
    edgepr->origin.y = D3DVAL(0);
    edgepr->origin.z = D3DVAL(0);
    edgepr->direction.x = D3DVAL(0);
    edgepr->direction.y = D3DVAL(0.5);
    edgepr->direction.z = D3DVAL(1.0);
    edgepr->scalefactor = D3DVAL(1.0);
	edgepr->wind = D3DVAL(0.0);
    edgepr->acc = D3DVAL(0.0);
    edgepr->maxv = D3DVAL(0.0);
    edgepr->num = 2;

	edgevis = (Svis*)malloc(sizeof(Svis));

    /*
    if (RLObjectExists(edgetex) != RLNoError)
    	edgetex = RLLoadGif(("edge.gif"), NULL);
    if (RLObjectExists(edgetexmask) != RLNoError) {
    	edgetexmask = RLLoadGif(("edgem.gif"), NULL);
		ApplyMask(edgetex, edgetexmask);
		RLIMInitialiseSurfaceInfo(Wdevice, theonlymaterial, theonlycolor, edgetex, &(edgesurface));
	}
	*/

	*edge = (Psystem*)malloc(sizeof(Psystem));

	(*edge)->lplpTexStruct = &lptexturestructure;
   lptexturestructure = LQHCreateTexture(Wdevice, ConstructLevelName(
      (d3dapprs.transparency == FANCY || d3dapprs.transparency == SEMIFANCY || d3dapprs.transparency == TRANSLUCENT ?
      "edget.bmp" : "edge.bmp")), 4);

    edgevis->sx = D3DVAL(5.0);
    edgevis->sy = D3DVAL(2.5);
    edgevis->x1 = D3DVAL(0.0);
    edgevis->y1 = D3DVAL(0.0);
    edgevis->x2 = D3DVAL(1.0);
    edgevis->y2 = D3DVAL(1.0);
    edgevis->transptype = BRIGHTTYPETRANSP;

    CreateParticleSystem(*edge, theframe, camera, edgepr, edgevis);
	(*edge)->active = 2; 			// set to 2 to prevent DestroyParticleSystem() from trying to remove a nonexistent callback
	(*edge)->numonscreen = (*edge)->properties->num;
	for (i = 0; i < (*edge)->properties->num; i++) 
	{
		(*edge)->particles[i]->active = 0;
		(*edge)->particles[i]->plane->active = 0;
		(*edge)->particles[i]->frame->lpVtbl->SetOrientation(
			(*edge)->particles[i]->frame, Wscene, 
			D3DVAL((i==0)), D3DVAL(0.0), D3DVAL((i==1)), 
			D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0));
		(*edge)->particles[i]->frame->lpVtbl->SetRotation(
			(*edge)->particles[i]->frame, Wscene, 
			D3DVAL((i==0)), D3DVAL(0.0), D3DVAL((i==1)), D3DVAL(3.141592654));
	}
	/*
	//for testing which psystem 96.08.15
	for (i = 0; i < edgepr->num; i++) 
	{
		strcpy((*edge)->particles[i]->plane->name, "edge");
	}
	/////////////////////////////////////
	*/
	//ReleaseOneTexture(edgevis->lpTexStruct);
	//free(edgevis->lpTexStruct);
	free(edgevis);
}

void makefire(Psystem** fire, LPDIRECT3DRMFRAME theframe, 
			  LPDIRECT3DRMFRAME camera, LPTEXTURESTRUCT *lplpFireTexStruct)
{
    static Pprop* firepr;
    Svis *firevis;
	//int i;

	firepr = (Pprop*)malloc(sizeof(Pprop));

	firepr->perterb.x = D3DVAL( 1.56);
	firepr->perterb.y = D3DVAL( 0.78);
	firepr->perterb.z = D3DVAL( 1.56);
	firepr->speed = D3DVAL( 0.16);
	firepr->origin.x = D3DVAL(0);
	firepr->origin.y = D3DVAL(-1.0);
	firepr->origin.z = D3DVAL(0);
	firepr->direction.x = D3DVAL(0.0);
	firepr->direction.y = D3DVAL( 200.0);
	firepr->direction.z = D3DVAL(0.0);
	firepr->scalefactor = D3DVAL( 0.865);
	firepr->wind = D3DVAL(0.25);
	firepr->acc = D3DVAL( 0.90625);
	firepr->maxv = D3DVAL(2.0);
	firepr->num = 5;
   if (detail==5) firepr->num += 3;

	firevis = (Svis*)malloc(sizeof(Svis));
	
	*fire = (Psystem*)malloc(sizeof(Psystem));

	//(*fire)->lpTexStruct = LQHCreateTexture(Wdevice, ppmfile);
	(*fire)->lplpTexStruct = lplpFireTexStruct;
	
	firevis->sx = D3DVAL(4.0);
	firevis->sy = D3DVAL(4.0);
	firevis->x1 = D3DVAL(0.0);
	firevis->y1 = D3DVAL(0.0);
	firevis->x2 = D3DVAL(1.0);
	firevis->y2 = D3DVAL(1.0);
   firevis->transptype = BRIGHTTYPETRANSP;

	CreateParticleSystem(*fire, theframe, camera, firepr, firevis);
	//(*fire)->active = 1;

	/*
	//for testing which psystem 96.08.15
	for (i = 0; i < firepr->num; i++) 
	{
		strcpy((*fire)->particles[i]->plane->name, "fire");
	}
	/////////////////////////////////////
	*/
	//ReleaseOneTexture(firevis->lpTexStruct);
	//free(firevis->lpTexStruct);
	free(firevis);
}

void makesmoke(Psystem** smoke, LPDIRECT3DRMFRAME theframe, 
			   LPDIRECT3DRMFRAME camera, LPTEXTURESTRUCT *lplpSmokeTexStruct)
{
    static Pprop* smokepr;
    Svis *smokevis;
	//int i;

	smokepr = (Pprop*)malloc(sizeof(Pprop));

	smokepr->perterb.x = D3DVAL( 1.0);
	smokepr->perterb.y = D3DVAL( 2.50);
	smokepr->perterb.z = D3DVAL( 1.0);
	smokepr->speed = D3DVAL(0.10);
	smokepr->origin.x = D3DVAL(0);
	smokepr->origin.y = D3DVAL(-1.0);
	smokepr->origin.z = D3DVAL(0);
	smokepr->direction.x = D3DVAL(0.0);
	smokepr->direction.y = D3DVAL(100.0);
	smokepr->direction.z = D3DVAL(0.0);
	smokepr->scalefactor = D3DVAL(1.15);
	smokepr->wind = D3DVAL(1.0);
	smokepr->acc = D3DVAL(0.5);
	smokepr->maxv = D3DVAL(1.0);
	smokepr->num = 5;
   if (detail==5) smokepr->num += 3;

	smokevis = (Svis*)malloc(sizeof(Svis));
	
	*smoke = (Psystem*)malloc(sizeof(Psystem));

	//(*smoke)->lpTexStruct = LQHCreateTexture(Wdevice, ppmfile);
	(*smoke)->lplpTexStruct = lplpSmokeTexStruct;

	smokevis->sx = D3DVAL(1.5);
	smokevis->sy = D3DVAL(1.5);
	smokevis->x1 = D3DVAL(0.0);
	smokevis->y1 = D3DVAL(0.0);
	smokevis->x2 = D3DVAL(1.0);
	smokevis->y2 = D3DVAL(1.0);
   smokevis->transptype = DARKTYPETRANSP;

	CreateParticleSystem(*smoke, theframe, camera, smokepr, smokevis);
	//(*smoke)->active = 1;

	/*
	//for testing which psystem 96.08.15
	for (i = 0; i < smokepr->num; i++) 
	{
		strcpy((*smoke)->particles[i]->plane->name, "smoke");
	}
	/////////////////////////////////////
	*/
	//ReleaseOneTexture(smokevis->lpTexStruct);
	//free(smokevis->lpTexStruct);
	free(smokevis);
}


void MakeSplat(Psystem** splat, LPDIRECT3DRMFRAME theframe, LPDIRECT3DRMFRAME camera)
{
    static Pprop *splatpr;
    static Svis *splatvis;
    static LPTEXTURESTRUCT lptexturestructure = NULL;
	//int i;

	splatpr = (Pprop*)malloc(sizeof(Pprop));

    splatpr->perterb.x = D3DVAL(0.05);
    splatpr->perterb.y = D3DVAL(0.05);
    splatpr->perterb.z = D3DVAL(0.05);
    splatpr->speed = D3DVAL(0.05);
    splatpr->origin.x = D3DVAL(0);
    splatpr->origin.y = D3DVAL(0);
    splatpr->origin.z = D3DVAL(0);
    splatpr->direction.x = D3DVAL(0.0);
    splatpr->direction.y = D3DVAL(0.0);
    splatpr->direction.z = D3DVAL(-5.0);
    splatpr->scalefactor = D3DVAL(1.35);
    //splatpr->scalefactor = D3DVAL(0.5);
	splatpr->wind = D3DVAL(1.0);
    splatpr->acc = D3DVAL(0.2);
    splatpr->maxv = D3DVAL(0.2);
    splatpr->num = 3;

	splatvis = (Svis*)malloc(sizeof(Svis));
	/*
    if (RLObjectExists(splattex) == RLNoError)
		ReplaceGif(splattex, ConstructLevelName("spore.gif"));
	else
    	splattex = RLLoadGif(ConstructLevelName("spore.gif"), NULL);
    if (RLObjectExists(splattexmask) == RLNoError)
		ReplaceGif(splattexmask, "gutsmap.gif");
	else {
    	splattexmask = RLLoadGif("gutsmap.gif", NULL);
	 	ApplyMask(splattex, splattexmask);
		RLIMInitialiseSurfaceInfo(Wdevice, theonlymaterial, theonlycolor, splattex, &(splatsurface));
	}*/
	
	*splat = (Psystem*)malloc(sizeof(Psystem));

	//(*splat)->lpTexStruct = LQHCreateTexture(Wdevice, ConstructLevelName("spore.bmp"));
	(*splat)->lplpTexStruct = &lptexturestructure;
   lptexturestructure = LQHCreateTexture(Wdevice, ConstructLevelName("guts.bmp"), 4);//Liou qinghua 9/9,96

    splatvis->sx = D3DVAL(0.5);
    splatvis->sy = D3DVAL(0.5);
    splatvis->x1 = D3DVAL(0.0);
    splatvis->y1 = D3DVAL(0.0);
    splatvis->x2 = D3DVAL(1.0);
    splatvis->y2 = D3DVAL(1.0);
    splatvis->transptype = DARKTYPETRANSP;

    CreateParticleSystem(*splat, theframe, camera, splatpr, splatvis);
	/*
	//for testing which psystem 96.08.15
	for (i = 0; i < splatpr->num; i++) 
	{
		strcpy((*splat)->particles[i]->plane->name, "splat");
	}
	/////////////////////////////////////
	*/
	//ReleaseOneTexture(splatvis->lpTexStruct);
	//free(splatvis->lpTexStruct);
	free(splatvis);
}


void MakeSpiritSprite(Psystem** spirits, LPDIRECT3DRMFRAME theframe, LPSTR  suffix)
{
    Svis *spiritvis;
    static Pprop* spiritpr;
    static LPTEXTURESTRUCT lptexturestructure = NULL;
	int i;

	spiritvis = (Svis*)malloc(sizeof(Svis));
	
	/*
    if (RLObjectExists(spirittex) != RLNoError)
    	spirittex = RLLoadGif(suffix, NULL);
    if (RLObjectExists(spirittexmask) != RLNoError) {
    	spirittexmask = RLLoadGif(masksuffix, NULL);
		ApplyMask(spirittex, spirittexmask);
		RLIMInitialiseSurfaceInfo(Wdevice, theonlymaterial, theonlycolor, spirittex, &(spiritsurface));
	}
	*/
	*spirits = (Psystem*)malloc(sizeof(Psystem));

	(*spirits)->lplpTexStruct = &lptexturestructure;
   lptexturestructure = LQHCreateTexture(Wdevice, suffix, 4);

    spiritvis->sx = D3DVAL(5.0);
    spiritvis->sy = D3DVAL(5.0);
    spiritvis->x1 = D3DVAL(0.0);
    spiritvis->y1 = D3DVAL(0.0);
    spiritvis->x2 = D3DVAL(1.0);
    spiritvis->y2 = D3DVAL(0.5);
    spiritvis->transptype = BRIGHTTYPETRANSP;

	spiritpr = (Pprop*)malloc(sizeof(Pprop));

    spiritpr->perterb.x = D3DVAL(0.0);
    spiritpr->perterb.y = D3DVAL(0.0);
    spiritpr->perterb.z = D3DVAL(0.0);
    spiritpr->speed = D3DVAL(0.0);
    spiritpr->origin.x = D3DVAL(0);
    spiritpr->origin.y = D3DVAL(0);
    spiritpr->origin.z = D3DVAL(0);
    spiritpr->direction.x = D3DVAL(0);
    spiritpr->direction.y = D3DVAL(0.5);
    spiritpr->direction.z = D3DVAL(1.0);
    spiritpr->scalefactor = D3DVAL(1.1);
    spiritpr->acc = D3DVAL(0.0);
    spiritpr->maxv = D3DVAL(0.0);
    spiritpr->num = 1;

    CreateParticleSystem(*spirits, theframe, Wcamera, spiritpr, spiritvis);
	(*spirits)->active = 2; 			// set to 2 to prevent DestroyParticleSystem() from trying to remove a nonexistent callback
	(*spirits)->numonscreen = (*spirits)->properties->num;
	
	for (i = 0; i < (*spirits)->properties->num; i++) 
	{
		(*spirits)->particles[i]->active = 0;
		(*spirits)->particles[i]->plane->active = 0;
		(*spirits)->particles[i]->frame->lpVtbl->SetRotation(
			(*spirits)->particles[i]->frame,
			Wscene, 
			D3DVAL(0), D3DVAL(1), D3DVAL(0), D3DVAL(0));
	}
	/*
	//for testing which psystem 96.08.15
	for (i = 0; i < spiritpr->num; i++) 
	{
		strcpy((*spirits)->particles[i]->plane->name, "spirit");
	}
	/////////////////////////////////////
	*/
	//ReleaseOneTexture(spiritvis->lpTexStruct);
	//free(spiritvis->lpTexStruct);
	free(spiritvis);	
}

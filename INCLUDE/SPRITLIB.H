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
File:           spritlib.h
Author:         Jeremiah Spudde Childs
Date:           9-27-95
Version:        1.0


************************************************************************

Program:        Goman95
File:           spritlib.h
Re_Writer:      Liu Qinghua (Lawrence)
Date:           6-30-96
Version:        1.0



************************************************************************

************************************************************************
REVISION HISTORY        (Add Edits and History to top of list).

Edited By:      
Edited Date:    
Changes:

***********************************************************************/
#ifndef _SPRITLIB_H_
#define _SPRITLIB_H_

#include "mdtex.h"

#ifdef __cplusplus
extern "C"{
#endif

#define NUM_VERTICES	4
#define NUM_TRIANGLES	2
#define MAXNUM_VERTICES		8
#define MAXNUM_TRIANGLES	4


typedef struct _Plane {
    unsigned char active;
	int num_vertices;
	int num_triangles;

	D3DVALUE x1;
	D3DVALUE x2;
	D3DVALUE y1;
	D3DVALUE y2;

	D3DVERTEX points[NUM_VERTICES];

	D3DTEXTUREHANDLE hTex;
	LPDIRECT3DRMDEVICE dev;
    LPDIRECT3DEXECUTEBUFFER eb;
    LPDIRECT3DMATERIAL mat;
    short transptype;
//	LPDIRECT3DRMFRAME frame;
//	unsigned char name[8];	//just for testing
} Plane;

#define BRIGHTTYPETRANSP 1
#define DARKTYPETRANSP 2

typedef struct _svis {
    //LPTEXTURESTRUCT	lpTexStruct;
	D3DVALUE sx;
    D3DVALUE sy;
    D3DVALUE x1;
    D3DVALUE y1;
    D3DVALUE x2;
    D3DVALUE y2;
    short transptype;
} Svis;

typedef struct _sprite {
	LPDIRECT3DRMFRAME frame;
    Plane*   plane; 
	D3DVALUE ttl;
	unsigned char active;
	unsigned char flag1;
	unsigned char flag2;
	D3DVALUE sx;
	D3DVALUE sy;
} Sprite;

typedef struct _cxsprite {
	LPDIRECT3DRMFRAME frame;
	Plane*   plane; 
	LPTEXTURESTRUCT	lpTexStruct;
	D3DVALUE ttl;
	int index;
	unsigned char active;
	unsigned char flag1;
	unsigned char flag2;
	D3DVALUE u[8];
	D3DVALUE v[8];
	D3DVALUE sx;
	D3DVALUE sy;
} CxSprite;


typedef struct _pprop {
	int num;
	D3DVECTOR origin;
	D3DVECTOR direction;
	D3DVALUE  maxv;
	D3DVALUE  acc;
	D3DVECTOR perterb;
	D3DVALUE  speed;
	D3DVALUE  scalefactor;
	D3DVALUE  wind;
} Pprop;

typedef struct _psystem {
	LPDIRECT3DRMFRAME frame;
	LPDIRECT3DRMFRAME dummy;
	Sprite **particles;
	Pprop *properties;
	int ttl;
	unsigned char numonscreen;
	unsigned char active;
	unsigned char index;
	LPTEXTURESTRUCT *lplpTexStruct;
	LPDIRECT3DRMFRAME camera;
} Psystem;


void DestroyPlane(LPDIRECT3DRMOBJECT obj, void* arg);
LPDIRECT3DRMUSERVISUAL LQHCreateVisual(Plane *plane);
int MallocPlane(Plane** plane);

LPTEXTURESTRUCT LQHCreateTexture(LPDIRECT3DRMDEVICE dev, LPSTR ppmfile, int transbits);
LPDIRECT3DRMFRAME LQHCreateTextureFrame(LPDIRECT3DRMFRAME parent, Plane* plane);
void InitSprites();
Sprite *CreateDisplayList(LPDIRECT3DRMFRAME parent, LPTEXTURESTRUCT lpTexStruct, Svis *visual);
void CreateCxDisplayList(CxSprite *thesprite, 
	LPDIRECT3DRMFRAME parent, D3DTEXTUREHANDLE htex);

Sprite *CreateSprite(LPDIRECT3DRMFRAME parent, LPTEXTURESTRUCT lpTexStruct, Svis *visual);

void DestroySprite(Sprite *condemned);
void ActivateParticleSystem(Psystem *go, int ttl);
void DeactivateParticleSystem(Psystem *go);

void CreateParticleSystem(Psystem *newsystem, LPDIRECT3DRMFRAME parent, LPDIRECT3DRMFRAME camera, 
						  Pprop *property, Svis *visual);

void swarmit(LPDIRECT3DRMFRAME frame, void* arg);
void DestroyParticleSystem(Psystem** condemned);
void DestroyAllParticleSystems();
void DestroyAllCxSprites();
void ResetParticles(Psystem *tobereset);
void MoveAllParticles();
void RenderAllParticles();
void RenderAllCxSprites();

#ifdef __cplusplus
};
#endif

#endif

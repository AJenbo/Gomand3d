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
File:           clutter.h
Author:         J. Spudde Childs
Date:           12/04/95
Version:        1.0



************************************************************************
REVISION HISTORY        (Add Edits and History to top of list).

Edited By:      Jeremiah Spudde Childs
Edited Date:    
Changes:
                changed 

***********************************************************************/
#ifndef _CLUTTER_H_
#define	_CLUTTER_H_

#define JETFORWARD 0
#define JETBACK 1
#define JETLEFT 2
#define JETRIGHT 3

#include "rl2d3d.h"
#include "mdtex.h"

#ifdef __cplusplus
extern "C" {
#endif

void CreateTrees(int numtrees, RLFrame parent);
void MapTrees();
void AddPole(int x, int z);
void PlantTree(int x, int z);
void RemoveTree(int x, int z);
void RemoveTrees(int x0, int z0, int x1, int z1);

void CreatePowerUps();
void PlantPowerUp(int x, int z);
void RemovePowerUps(int x0, int z0, int x1, int z1);
int PowerUpHere(RLFrame Robotishere);
RLFrame PowerupFrame(int i);
void DestroyJets();
void ActivateJets(int whichway);
void DeactivateJets();
 
void Jetflamer(RLFrame theframe, void* arg,D3DVALUE delta);	

#include "d3dtypes.h"
#ifdef MINIWIN
#include "miniwin/d3d.h"
#include "miniwin/d3drm.h"
#else
#include <d3d.h>
#include <d3drmwin.h>
#endif
void InitJets(LPTEXTURESTRUCT jettex, void *arg);
void FreeTreesPoles(void);

void SetupBackground();
void RenderBackground(BOOL show);
void RenderBackgroundOn4MegAcc(BOOL show);

#ifdef __cplusplus
};
#endif

#endif




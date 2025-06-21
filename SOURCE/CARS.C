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
File:           CARS.C
Author:         Jeremiah Spudde Childs
Date:           12/12/95
Version:        version 1.0

Development Environment:   MSVC 2.0, Reality Lab 2.0 Beta 21 runtime dll
                           Reality Lab 2.0 Build 21.

************************************************************************
REVISION HISTORY        

Edited By:      
Edited Date:    10/24/95
Changes:
            Changed ...

***********************************************************************/
#include <stdio.h>
#include <math.h>
#include "rl2d3d.h"
#include "boink.h"
#include "gosys.h"
#include "timing.h"
#include "building.h"
#include "ybsnd.h"
#include "spritlib.h"
#include "psystem.h"
#include "Robotanim.h"
#include "camera.h"
#include "imisc.h"
#include "global.h"
#include <d3d.h>
#include "d3dmacs.h"
#include "mdtex.h"

#define PADDING RLVal(4.0)
//#define BUILDINGLIMIT (4.25)
//#define BUILDINGSIZE (4.0)

void GoodCarMotionFunction(MovingObjectData movedata);
void BadCarMotionFunction(MovingObjectData movedata);
void GoodCarGotHit(MovingObjectData movedata);
void BadCarGotHit(MovingObjectData movedata);
int AvoidBuildings(RLVector car, RLVector* force);

extern RLFrame Robotframe, monstframe, Wscene, behindthescene, Wcamera;
extern RLVector monstorigin, Robotorigin;
extern RLValue RobotMaxFVel2, sealevel;
extern struct _moving_object_data_ 	RobotData; 
extern struct _moving_object_data_ 	MonsterData; 
extern TARGET targets[];
extern iobjdlist* allmiscdlists[];

#define MAXNOCARS 10
int numgoodcars, numbadcars;

typedef struct _carlist {
	struct _moving_object_data_ CarData;
	RLFrame carframe;
	RLFrame cartarget;
	int cardlistid;
} Carlist;

Carlist  goodcarlist[MAXNOCARS];
Carlist  badcarlist[MAXNOCARS];
HotSpot	 goodcarhotspot[MAXNOCARS];
HotSpot	 badcarhotspot[MAXNOCARS];

Psystem *splat=NULL;
RLFrame splatframe;
int sporehunt;


TEXTURESTRUCT CarTex;
TEXTURESTRUCT SporeTex;

extern LPDIRECT3DRMDEVICE Wdevice;
extern LPDIRECT3DRMFRAME Wcamera;

// **********************************************************
// Name:		MakeCars 						
//		
// Author:		LiuGuoHong      			
//
// Date:		1996.8                      
//
// Description: Create the cars         
//
// Arguments:	None
//
// Return:		None
//
// Side Effects:None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void MakeCars ()
{	
    int i;
    RLVector position,
             newdir,
             up;
//    extern int level;
    extern RLDevice Wdevice;
	extern short  SysDifficulty;
    //if (level <4) numgoodcars = level+3;
    //else numgoodcars = level*3;
    numgoodcars = 4;
	if(SysDifficulty==1)
		numbadcars = 1;
	else if(SysDifficulty==2)
		numbadcars = 3;
	else if(SysDifficulty==3)
		numbadcars = 7;
    sporehunt = 0;
    RLFrameGetPosition(Robotframe, Wscene, &position);
    position.y += RLVal(3.0);
    RLFrameGetOrientation (Robotframe, Wscene, &newdir, &up);
    for (i=0;i<numgoodcars;i++)
    {
        goodcarlist[i].carframe = RLCreateFrame(Wscene);
        //if (level != 3)
        {
           if (i)
           {
               goodcarlist[i].cardlistid = DupDList (goodcarlist[0].cardlistid, goodcarlist[i].carframe);
				allmiscdlists[goodcarlist[i].cardlistid]->builder=NULL;
               //goodcarlist[i].cardlistid = DupDListForCopyUVis (goodcarlist[0].cardlistid, goodcarlist[i].carframe);
           }
           else
           {
				memset(&CarTex, 0, sizeof(TEXTURESTRUCT));
				MyLoadTexture(Wdevice, ConstructLevelName("car.bmp"), &CarTex, 1);
				goodcarlist[0].cardlistid = LoadIntoDList (ConstructLevelName ("car.x"), goodcarlist[0].carframe, &CarTex, NULL);
           }
        }

        goodcarlist[i].CarData.Volume.max.x = RLVal (0.05);
        goodcarlist[i].CarData.Volume.max.y = RLVal (0.05);
        goodcarlist[i].CarData.Volume.max.z = RLVal (0.05);
        goodcarlist[i].CarData.Volume.min.x = -RLVal (0.05);
        goodcarlist[i].CarData.Volume.min.y = -RLVal (0.05);
        goodcarlist[i].CarData.Volume.min.z = -RLVal (0.05);
        goodcarlist[i].CarData.DamageICause = 0;
        goodcarlist[i].CarData.PositioningFrame = goodcarlist[i].carframe;
        goodcarlist[i].CarData.NumOffensiveSpheres = 0;
        goodcarlist[i].CarData.NumDefensiveSpheres = 0;
        goodcarlist[i].CarData.NumOffensiveTubes = 0;
        goodcarlist[i].CarData.AnimateMe = NULL;
        goodcarlist[i].CarData.MoveMe = GoodCarMotionFunction;
        goodcarlist[i].CarData.HandleMe = GoodCarGotHit;
        goodcarlist[i].CarData.SafePassageIndex = &RobotData;
        goodcarlist[i].CarData.data = i;
        goodcarlist[i].CarData.mass = RLVal (15);

        if (GameStates.CurrentLevel != Hawaii)//Boats/sharks move differently from cars.
        {
           goodcarlist[i].CarData.ProjectedPosition.x = position.x;
           goodcarlist[i].CarData.ProjectedPosition.y = SpuddeMapHeight2 (position.x, position.z) + i * 2;
           goodcarlist[i].CarData.ProjectedPosition.z = position.z;
        }
        else
        {
           goodcarlist[i].CarData.ProjectedPosition.x = RLVal((i&1) ? - 120 : 120);
           goodcarlist[i].CarData.ProjectedPosition.y = RLVal(sealevel + 0.1);
           goodcarlist[i].CarData.ProjectedPosition.z = RLVal((i&2) ? -120 : 120);
        }
        RLFrameSetPosition(goodcarlist[i].carframe,Wscene,goodcarlist[i].CarData.ProjectedPosition.x,goodcarlist[i].CarData.ProjectedPosition.y,goodcarlist[i].CarData.ProjectedPosition.z);
        RLFrameSetOrientation(goodcarlist[i].carframe,Wscene,-newdir.x,-newdir.y,-newdir.z,up.x,up.y,up.z);

        goodcarlist[i].CarData.RemoveMeFlag = 0;
        goodcarlist[i].CarData.collisionflag = 0;
        goodcarlist[i].CarData.DamageICause = 1;
        goodcarlist[i].cartarget = monstframe;
        AddMovingObject(&(goodcarlist[i].CarData));
    }
	DeleteBinary (allmiscdlists[goodcarlist[0].cardlistid]->builder);
	allmiscdlists[goodcarlist[0].cardlistid]->builder=NULL;

    RLFrameGetPosition (monstframe, Wscene, &position);
    position.y += RLVal (10.0);
    RLFrameGetOrientation (Robotframe, Wscene, &newdir, &up);
    for (i = 0; i < numbadcars; i++)
    {
        badcarlist[i].carframe = RLCreateFrame (Wscene);
        if (i)
        {
            badcarlist[i].cardlistid = DupDList (badcarlist[0].cardlistid, badcarlist[i].carframe);
			allmiscdlists[badcarlist[i].cardlistid]->builder=NULL;
        }
        else
        {
			memset(&SporeTex, 0, sizeof(TEXTURESTRUCT));
			MyLoadTexture(Wdevice, ConstructLevelName("spore.bmp"), &SporeTex, 0);
			badcarlist[0].cardlistid = LoadIntoDList (ConstructLevelName ("spore.x"), badcarlist[0].carframe, &SporeTex, NULL);
        }
        badcarlist[i].CarData.Volume.max.x = RLVal(0.05);
        badcarlist[i].CarData.Volume.max.y = RLVal(0.05);
        badcarlist[i].CarData.Volume.max.z = RLVal(0.05);
        badcarlist[i].CarData.Volume.min.x = -RLVal(0.05);
        badcarlist[i].CarData.Volume.min.y = -RLVal(0.05);
        badcarlist[i].CarData.Volume.min.z = -RLVal(0.05);
        badcarlist[i].CarData.DamageICause = 1;
        badcarlist[i].CarData.PositioningFrame = badcarlist[i].carframe;
        //SixShooter->particles[i]->active=0;
		//badcarlist[i].CarData.NumOffensiveSpheres=0;
        badcarlist[i].CarData.NumOffensiveSpheres = 1;
        badcarlist[i].CarData.OffensiveSphereList[0] = &badcarhotspot[i];
        badcarhotspot[i].position = badcarlist[i].carframe;
        badcarhotspot[i].radius = RLVal(0.5);
        badcarhotspot[i].point1.x = RLVal(0);
        badcarhotspot[i].point1.y = RLVal(0);
        badcarhotspot[i].point1.z = RLVal(0);
        //badcarlist[i].CarData.OffensiveSphereList=NULL;
        //RobotRapidFireSpot[i].position=SixShooter->particles[i]->frame;
        //RobotRapidFireSpot[i].radius=0.7;
        //RobotRapidFireSpot[i].point1.x=0;
        //RobotRapidFireSpot[i].point1.y=0;
        //RobotRapidFireSpot[i].point1.z=0;
        badcarlist[i].CarData.NumDefensiveSpheres = 1;
        badcarlist[i].CarData.DefensiveSphereList[0] = &badcarhotspot[i];
        badcarlist[i].CarData.NumOffensiveTubes = 0;
        badcarlist[i].CarData.AnimateMe = NULL;
        badcarlist[i].CarData.MoveMe = BadCarMotionFunction;
        badcarlist[i].CarData.HandleMe = BadCarGotHit;
		  badcarlist[i].CarData.SafePassageIndex=&MonsterData;
        badcarlist[i].CarData.data = i;
        badcarlist[i].CarData.mass = RLVal(25);

        RLFrameSetPosition (badcarlist[i].carframe, Wscene, position.x, position.y + i * 2, position.z);
        RLFrameSetOrientation (badcarlist[i].carframe, Wscene, newdir.x, newdir.y, newdir.z, up.x, up.y, up.z);
        badcarlist[i].CarData.ProjectedPosition.x = position.x;
        badcarlist[i].CarData.ProjectedPosition.y = position.y;
        badcarlist[i].CarData.ProjectedPosition.z = position.z;
        badcarlist[i].CarData.RemoveMeFlag = 0;
        badcarlist[i].CarData.collisionflag = 0;
        badcarlist[i].CarData.DamageICause = 10;
        badcarlist[i].cartarget = monstframe;
        AddMovingObject ( &(badcarlist[i].CarData) );
    }
	DeleteBinary (allmiscdlists[badcarlist[0].cardlistid]->builder);
	allmiscdlists[badcarlist[0].cardlistid]->builder=NULL;
        
    if (RLObjectExists(splatframe) == RLBadObject) 
    {
		splatframe = RLCreateFrame (Wscene);
    }  
	MakeSplat(&splat, splatframe, Wcamera);
}

// **********************************************************
// Name:		LaunchAllBadCars    
//		
// Author:		Spudde      			
//
// Date:		1996.8                      
//
// Description: Launch all bad cars to fly
//
// Arguments:	None
//
// Return:		None
//
// Side Effects:None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void LaunchAllBadCars()
{
	int i;

	for (i=0;i<numbadcars;i++) {
		if ((badcarlist[i].CarData.collisionflag) || (badcarlist[i].CarData.RemoveMeFlag))
			AddMovingObject(&(badcarlist[i].CarData));
		badcarlist[i].CarData.RemoveMeFlag=0;
		badcarlist[i].CarData.collisionflag=0;
		RLFrameSetPosition(badcarlist[i].CarData.PositioningFrame, Wscene, monstorigin.x+RLVal(1.5+i*3), monstorigin.y+RLVal(1.5+i*3), monstorigin.z+RLVal(1.5+i*3));
		RLFrameSetOrientation(badcarlist[i].CarData.PositioningFrame, Wscene, RLVal(0.01), RLVal(-1.0), RLVal(0.01), RLVal(0.0), RLVal(1.0), RLVal(0.0));
		badcarlist[i].CarData.ProjectedPosition.x = monstorigin.x+RLVal(1.5+i*3);
		badcarlist[i].CarData.ProjectedPosition.y = monstorigin.y+RLVal(1.5+i*3);
		badcarlist[i].CarData.ProjectedPosition.z = monstorigin.z+RLVal(1.5+i*3);
		RLFrameAddChild(Wscene, badcarlist[i].CarData.PositioningFrame);
	}
}

// **********************************************************
// Name:		KillAllBadCars                    
//		
// Author:		Spudde      			
//
// Date:		1996.8                      
//
// Description: Destroy all bad cars                           
//
// Arguments:	None
//
// Return:		None
//
// Side Effects:None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void KillAllBadCars()
{
	int i;

	for (i=0;i<numbadcars;i++) {
		badcarlist[i].CarData.collisionflag=1;
		RLFrameAddChild(behindthescene, badcarlist[i].CarData.PositioningFrame);
	}
}

// **********************************************************
// Name:		KillAllGoodCars                    
//		
// Author:		Spudde      			
//
// Date:		1996.8                      
//
// Description: Destroy all good cars                           
//
// Arguments:	None
//
// Return:		None
//
// Side Effects:None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void KillAllGoodCars()
{
	int i;

	for (i=0;i<numgoodcars;i++) {
		goodcarlist[i].CarData.collisionflag=1;
		RLFrameAddChild(behindthescene, goodcarlist[i].CarData.PositioningFrame);
	}
}

// **********************************************************
// Name:		GoodCarMotionFunction                    
//		
// Author:		Spudde      			
//
// Date:		1996.8                      
//
// Description: How to move the good cars.                           
//
// Arguments:	MovingObjectData movedata	
//
// Return:		None
//
// Side Effects:None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void GoodCarMotionFunction(MovingObjectData movedata)
{
	RLFrame Scene=RLFrameGetScene(movedata->PositioningFrame);
	int i=movedata->data;
	RLVector dir,up, monstpos, wannago, antibuildingforce;
	//RLValue wannagobad;
	RLValue RFSpeed = RLMultiply(RLVal(0.1), (RLVal(1)+RLMultiply(RLVal(1.0), RLVal((double)i/numgoodcars))));
	//extern Caminfo* camerastuff;
//	extern int level;
   RLValue caryclearance = RLVal(2.0);

	if (GameStates.CurrentLevel==Hawaii) RFSpeed = RLDivide(RFSpeed, RLVal(4.0));//Boats/sharks move differently from cars.

	RLFrameGetOrientation(movedata->PositioningFrame,Scene,&dir,&up);


	movedata->CurrentPosition.x=movedata->ProjectedPosition.x;
	movedata->CurrentPosition.y=movedata->ProjectedPosition.y;
	movedata->CurrentPosition.z=movedata->ProjectedPosition.z;

	if (goodcarlist[i].cartarget == monstframe) 
	{
		extern struct _moving_object_data_ MonsterData;

		RLFrameGetPosition(goodcarlist[i].cartarget, Scene, &monstpos);
		wannago.x = (movedata->ProjectedPosition.x - monstpos.x);
		wannago.z = (movedata->ProjectedPosition.z - monstpos.z);
		wannago.y = RLVal(movedata->ProjectedPosition.y - (MonsterData.Volume.max.y+caryclearance));
		if (RLVectorDotProduct(&wannago, &wannago) < RLMultiply(MonsterData.Volume.max.y+RLVal(2.0), MonsterData.Volume.max.y+RLVal(2.0)))
			goodcarlist[i].cartarget = Robotframe;
	} 
	else
	{
		RLFrameGetPosition(goodcarlist[i].cartarget, Scene, &monstpos);
		wannago.x = (movedata->ProjectedPosition.x - monstpos.x);
		wannago.z = (movedata->ProjectedPosition.z - monstpos.z);
		wannago.y = RLVal(movedata->ProjectedPosition.y - (monstpos.y+1.0));
		if (RLVectorDotProduct(&wannago, &wannago) < RLVal(4.0))
			goodcarlist[i].cartarget = monstframe;
	}
	//wannago.y = RLDivide(wannago.y, RLMultiply(wannago.x, wannago.x) + RLMultiply(wannago.z, wannago.z));

	//wannagobad = MAX(MIN(RLDivide(RLVal(16*16), RLMultiply(wannago.x, wannago.x) + RLMultiply(wannago.z, wannago.z)), RLVal(RFSpeed)), RLVal(0.25));

	RLVectorNormalise(&wannago);
	dir.x += RLMultiply(RLVal(0.25/(i+1)),wannago.x);
	dir.y += RLMultiply(RLVal(0.5),wannago.y);
	dir.z += RLMultiply(RLVal(0.25/(i+1)),wannago.z);

	if (GameStates.CurrentLevel==Hawaii)//Boats/sharks move differently from cars.
	{
		RLVector coastalcorrection;
		RLValue temp, veeramount;

		dir.y = RLVal(0);

		GetGradient(&coastalcorrection, movedata->CurrentPosition.x, movedata->CurrentPosition.z);
		temp = coastalcorrection.z;
		coastalcorrection.z = -coastalcorrection.x;
		coastalcorrection.x = temp;
		
		if (RLVectorDotProduct(&coastalcorrection, &wannago) < RLVal(0))
		{
			coastalcorrection.x = -coastalcorrection.x;
			coastalcorrection.z = -coastalcorrection.z;
		}
		veeramount = RLDivide(RLVal(1), fabs(SpuddeMapHeight2(movedata->CurrentPosition.x, movedata->CurrentPosition.z)));
		dir.x += RLMultiply(coastalcorrection.x, veeramount);
		dir.z += RLMultiply(coastalcorrection.z, veeramount);
	}
	else
	{
		if (AvoidBuildings(movedata->CurrentPosition, &antibuildingforce)) {
			dir.x -= RFSpeed*antibuildingforce.x;
			dir.y -= RFSpeed*antibuildingforce.y;
			dir.z -= RFSpeed*antibuildingforce.z;
		}
		dir.y -= RLDivide(RLVal(0.5), 
			(movedata->CurrentPosition.y - SpuddeMapHeight2(movedata->CurrentPosition.x, movedata->CurrentPosition.z) + RLVal(0.2)));

	}

	RLVectorNormalise(&dir);

	//if(movedata->CurrentPosition.y<
	//SpuddeMapHeight2(movedata->CurrentPosition.x, movedata->CurrentPosition.z)+RLVal(0.5))

	RLFrameSetOrientation(movedata->PositioningFrame,Wscene,dir.x,dir.y,dir.z,RLVal(0),RLVal(1),RLVal(0));

	movedata->ProjectedPosition.x=movedata->CurrentPosition.x - dir.x*DiffFrame*RFSpeed;
	movedata->ProjectedPosition.y=movedata->CurrentPosition.y - dir.y*DiffFrame*RFSpeed;
	movedata->ProjectedPosition.z=movedata->CurrentPosition.z - dir.z*DiffFrame*RFSpeed;

	//if ((level!=3))
	//{ 
	//	RLFrameSetOrientation(movedata->PositioningFrame,Wscene,dir.x,RLVal(0),dir.z,RLVal(0),RLVal(1),RLVal(0));
	//	movedata->ProjectedPosition.y=SpuddeMapHeight2(movedata->ProjectedPosition.x,movedata->ProjectedPosition.z)+0.4;
	//}
	if(movedata->ProjectedPosition.y<SpuddeMapHeight2(movedata->ProjectedPosition.x,movedata->ProjectedPosition.z)+0.2)
	  movedata->collisionflag=1;

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
}

// **********************************************************
// Name:		BadCarMotionFunction                    
//		
// Author:		Spudde      			
//
// Date:		1996.8                      
//
// Description: How to move the bad car in the air                           
//
// Arguments:	MovingObjectData movedata
//
// Return:		None
//
// Side Effects:None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void BadCarMotionFunction(MovingObjectData movedata)
{
	RLFrame Scene=RLFrameGetScene(movedata->PositioningFrame);
	int i=movedata->data;
	RLVector dir,up, Robotpos, wannago, antibuildingforce, p;
	RLValue wannagobad, RFSpeed = RLMultiply(RLVal(0.3), (RLVal(1)+RLMultiply(RLVal(2.0), RLVal((double)i/numbadcars))));
	extern RLFrame goodguyframe;

    RLFrameGetPosition(movedata->PositioningFrame, goodguyframe, &p);
    if (i<((numbadcars>3)?3:numbadcars) ) {
	    targets[i+1].p.x = p.x;
	    targets[i+1].p.y = p.y;
	    targets[i+1].p.z = p.z;
	    targets[i+1].life = 1;
	    targets[i+1].type = 4;
	}

	RLFrameGetOrientation(movedata->PositioningFrame,Scene,&dir,&up);
	RLFrameGetPosition(Robotframe, Scene, &Robotpos);

	movedata->CurrentPosition.x=movedata->ProjectedPosition.x;
	movedata->CurrentPosition.y=movedata->ProjectedPosition.y;
	movedata->CurrentPosition.z=movedata->ProjectedPosition.z;

	switch (sporehunt) {
		case 0:
			wannago.x = (movedata->ProjectedPosition.x - Robotpos.x);
			wannago.y = RLMultiply((movedata->ProjectedPosition.y - (Robotpos.y+RLVal(1.0))),RLVal(4.0));
			wannago.z = (movedata->ProjectedPosition.z - Robotpos.z);
			if (RobotAnimationState==RobotBlockMediumFreeze) {
				wannago.x = -wannago.x;
				wannago.z = -wannago.z;
			}
			break;
		case 1:
			wannago.x = RLVal(rand()%LANDXSIZE - LANDXCENTER);
			wannago.y = movedata->ProjectedPosition.y;
			wannago.z = RLVal(rand()%LANDZSIZE - LANDZCENTER);
			break;
		case 2:
			RLFrameGetPosition(monstframe, Scene, &Robotpos);
			wannago.x = (movedata->ProjectedPosition.x - Robotpos.x);
			wannago.y = RLMultiply((movedata->ProjectedPosition.y - (Robotpos.y+RLVal(1.0))),RLVal(8.0));
			wannago.z = (movedata->ProjectedPosition.z - Robotpos.z);
			break;
		}		

	wannagobad = MAX(MIN(RLDivide(RLVal(16*16), RLMultiply(wannago.x, wannago.x) + RLMultiply(wannago.z, wannago.z)), RLVal(RFSpeed)), RLVal(0.25));

	RLVectorNormalise(&wannago);
	dir.x += RLMultiply(RLVal(0.25/(i+1)),wannago.x);
	dir.y += RLMultiply(RLVal(0.5),wannago.y);
	dir.z += RLMultiply(RLVal(0.25/(i+1)),wannago.z);

	dir.y -= RLDivide(RLVal(0.5), 
		(movedata->CurrentPosition.y - SpuddeMapHeight2(movedata->CurrentPosition.x, movedata->CurrentPosition.z) + RLVal(0.2)));

	if (AvoidBuildings(movedata->CurrentPosition, &antibuildingforce)) {
		dir.x -= RFSpeed*antibuildingforce.x;
		dir.y -= RFSpeed*antibuildingforce.y;
		dir.z -= RFSpeed*antibuildingforce.z;
	}

	RLVectorNormalise(&dir);

	//if(movedata->CurrentPosition.y<
	//  SpuddeMapHeight2(movedata->CurrentPosition.x, movedata->CurrentPosition.z)+RLVal(0.5))

	RLFrameSetOrientation(movedata->PositioningFrame,Wscene,dir.x,dir.y,dir.z,up.x,up.y,up.z);

	movedata->ProjectedPosition.x=movedata->CurrentPosition.x - dir.x*DiffFrame*RFSpeed*wannagobad;
	movedata->ProjectedPosition.y=movedata->CurrentPosition.y - dir.y*DiffFrame*RFSpeed*wannagobad;
	movedata->ProjectedPosition.z=movedata->CurrentPosition.z - dir.z*DiffFrame*RFSpeed*wannagobad;

	/*
	if (AvoidBuildings(movedata->ProjectedPosition, &antibuildingforce)) {
		movedata->ProjectedPosition.x += antibuildingforce.x;
		movedata->ProjectedPosition.y += antibuildingforce.y;
		movedata->ProjectedPosition.z += antibuildingforce.z;
	}
	*/

	if(movedata->ProjectedPosition.y<
	     SpuddeMapHeight2(movedata->ProjectedPosition.x,movedata->ProjectedPosition.z))
	  movedata->collisionflag=1;

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
}

// **********************************************************
// Name:		GoodCarGotHit                    
//		
// Author:		Spudde      			
//
// Date:		1996.8                      
//
// Description: Process the hit of good car                           
//
// Arguments:	MovingObjectData movedata
//
// Return:		None
//
// Side Effects:None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void GoodCarGotHit(MovingObjectData movedata)
{
	RLFrame Scene=RLFrameGetScene(movedata->PositioningFrame);
	int i=movedata->data;
//	extern int level;

	if (GameStates.CurrentLevel!=Hawaii) {//Boats/sharks move differently from cars.
		RLFrameSetPosition(movedata->PositioningFrame, Scene, Robotorigin.x, Robotorigin.y+RLVal(3.5+i*2), Robotorigin.z);
		movedata->ProjectedPosition.x = Robotorigin.x;
		movedata->ProjectedPosition.y = Robotorigin.y+RLVal(3.5+i*2);
		movedata->ProjectedPosition.z = Robotorigin.z;
	}
	else
	{
		goodcarlist[i].CarData.ProjectedPosition.x=RLVal((i&1) ? -120 : 120);
		goodcarlist[i].CarData.ProjectedPosition.y=RLVal(sealevel+0.1);
		goodcarlist[i].CarData.ProjectedPosition.z=RLVal((i&2) ? -120 : 120);
		RLFrameSetPosition(goodcarlist[i].carframe,Wscene,goodcarlist[i].CarData.ProjectedPosition.x,goodcarlist[i].CarData.ProjectedPosition.y,goodcarlist[i].CarData.ProjectedPosition.z);
	}
	RLFrameSetOrientation(movedata->PositioningFrame, Scene, RLVal(0.01), RLVal(1.0), RLVal(0.01), RLVal(0.0), RLVal(1.0), RLVal(0.0));
	movedata->collisionflag=0;

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
}

// **********************************************************
// Name:		BadCarGotHit                    
//		
// Author:		Spudde      			
//
// Date:		1996.8                      
//
// Description: Process the hit of bad car                           
//
// Arguments:	MovingObjectData movedata
//
// Return:		None
//
// Side Effects:None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void BadCarGotHit(MovingObjectData movedata)
{
	RLFrame Scene=RLFrameGetScene(movedata->PositioningFrame);
	int i=movedata->data;
	extern int monthink;

	YBPlay3DSound(Splat, movedata->PositioningFrame);
	RLFrameAddChild(Wscene,splatframe); 
	RLFrameSetPosition(splatframe,movedata->PositioningFrame,RLVal(0), RLVal(0), RLVal(0));
	RLFrameSetOrientation(splatframe,movedata->PositioningFrame,RLVal(0),RLVal(1),RLVal(0),RLVal(0),RLVal(0),RLVal(1));
	RLFrameSetVelocity(splatframe,Wscene,RLVal(0),RLVal(0),RLVal(0));
	ActivateParticleSystem(splat, 8);

	RLFrameSetPosition(movedata->PositioningFrame, Scene, monstorigin.x+RLVal(1.5+i*3), monstorigin.y+RLVal(1.5+i*3), monstorigin.z+RLVal(1.5+i*3));
	RLFrameSetOrientation(movedata->PositioningFrame, Scene, RLVal(0.01), RLVal(-1.0), RLVal(0.01), RLVal(0.0), RLVal(1.0), RLVal(0.0));
	movedata->ProjectedPosition.x = monstorigin.x+RLVal(1.5+i*3);
	movedata->ProjectedPosition.y = monstorigin.y+RLVal(1.5+i*3);
	movedata->ProjectedPosition.z = monstorigin.z+RLVal(1.5+i*3);
	//movedata->collisionflag=1;
	//movedata->RemoveMeFlag=1;
   if (!GameStates.Is3DMovie)
   {
	   movedata->collisionflag=0;
	   movedata->RemoveMeFlag=0;
   }
   else
   {
	   movedata->collisionflag=1;
      movedata->RemoveMeFlag=1;
      RLFrameAddChild(behindthescene, movedata->PositioningFrame);
      if (i<3) 
         targets[i+1].life = 0;
   }
	
    /*
	if (monthink>2)				// change monthink to difficulty level variable
	{
		int j, test=0;
		for (j=0;j<numbadcars;j++) 
			test |= targets[i+1].life;
		if (test) 
			LaunchAllBadCars();
	}
   */

	//LGH add release
	RLObjectDestroy ((RLObject)Scene);
}

// **********************************************************
// Name:		AvoidBuildings                    
//		
// Author:		Spudde      			
//
// Date:		1996.8                      
//
// Description: Make the cars avoid to collide with buildings                           
//
// Arguments:	RLVector car
//				RLVector* force
//
// Return:		None
//
// Side Effects:None
//
// Notes:		   
//
// Known restrictions:  None
//
// Error Number:No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

int AvoidBuildings(RLVector car, RLVector* force)
{
	visible_buildings Nearby;  // Structure of Nearby Buildings.
	int i;
	RLVector bldgspot, oneforce; 
	RLVector separation, proximity, direction;
	// separation is the vector from car to the building's center
	// direction is the vector along which the force will be applied 
	//		(generally from car to the nearest edge of a building)
	// proximity is the vector that determines the distance to be fed
	// 		into the inverse square law to determine the 'oomph' of the
	//		force.
	RLValue dist2, oomph, padding = PADDING;
	RLValue BuildingSize;
	RLValue BuildingSizePlus;

	force->x = force->y = force->z = RLVal(0.0);
	GetBuildingsInArea(&Nearby, car.x-padding, car.z-padding, car.x+padding, car.z+padding);
	for (i=0; i<Nearby.count; i++)
	{

		oneforce.x = oneforce.y = oneforce.z = RLVal(0.0);
		BuildingSize = ((Nearby.building_ptr[i]->building.max.x - Nearby.building_ptr[i]->building.min.x)/2)+.5;
		BuildingSizePlus = BuildingSize+.25;
		RLFrameGetPosition(Nearby.building_ptr[i]->rlframe, Wscene, &bldgspot);
		separation.x = car.x - (Nearby.building_ptr[i]->x_world - RLVal(LANDXCENTER));
		separation.y = car.y;// - SpuddeMapHeight2(Nearby.building_ptr[i]->x_world - RLVal(LANDXCENTER), Nearby.building_ptr[i]->z_world - RLVal(LANDZCENTER));
		separation.z = car.z - (Nearby.building_ptr[i]->z_world - RLVal(LANDZCENTER));
		
		if (separation.y < RLVal(Nearby.building_ptr[i]->building.max.y + 1.0)) 
		{
			// below the top of the building
			direction.y = separation.y = proximity.y = RLVal(0.0);
			if ((fabs(separation.x) <= RLVal(BuildingSizePlus)) && (fabs(separation.z) > RLVal(BuildingSizePlus))) {
				// outside building, off from z direction
				direction.x = RLVal(0.0);
				if (separation.z > 0) direction.z = separation.z - RLVal(BuildingSize);
				else direction.z = separation.z + RLVal(BuildingSize);
				// direction is vector from wall to car
				proximity.x = direction.x;
				proximity.z = direction.z;
				proximity.y = separation.y;
			}
			if ((fabs(separation.x) > RLVal(BuildingSizePlus)) && (fabs(separation.z) <= RLVal(BuildingSizePlus))) {
				// outside building, off from x direction
				direction.z = RLVal(0.0);
				if (separation.x > 0) direction.x = separation.x - RLVal(BuildingSize);
				else direction.x = separation.x + RLVal(BuildingSize);
				// direction is vector from wall to car
				proximity.x = direction.x;
				proximity.z = direction.z;
				proximity.y = separation.y;
			}
			if ((fabs(separation.x) > RLVal(BuildingSizePlus)) && (fabs(separation.z) > RLVal(BuildingSizePlus))) {
				// outside building, off from corner
				if (separation.x > 0) direction.x = separation.x - RLVal(BuildingSize);
				else direction.x = separation.x + RLVal(BuildingSize);
				if (separation.z > 0) direction.z = separation.z - RLVal(BuildingSize);
				else direction.z = separation.z + RLVal(BuildingSize);
				// direction is vector from corner to car
				proximity.x = direction.x;
				proximity.z = direction.z;
				proximity.y = separation.y;
			}
			if ((fabs(separation.x) <= RLVal(BuildingSizePlus)) && (fabs(separation.z) <= RLVal(BuildingSizePlus))) 
			{
			// inside building!!!
				if (separation.y < RLVal(Nearby.building_ptr[i]->building.max.y + 1.0)) {
						proximity.x = direction.x = separation.x/RLVal(BuildingSize*2);
						proximity.z = direction.z = separation.z/RLVal(BuildingSize*2);
						proximity.y = direction.y = RLVal(0.0); //(RLVal(Nearby.building_ptr[i]->scale) - separation.y)/RLVal(BuildingSize*2);
					// direction is vector from center to car
				} else {
					// should never reach this code
					direction.x = separation.x;
					direction.z = separation.z;
					//direction.y = separation.y;
					if (separation.x > 0) proximity.x = RLVal(BuildingSize) - separation.x;
					else proximity.x = -RLVal(BuildingSize) - separation.x;
					if (separation.z > 0) proximity.z = RLVal(BuildingSize) - separation.z;
					else proximity.z = -RLVal(BuildingSize) - separation.z;
					//proximity.x = direction.x / RLVal(5.0);
					//proximity.z = direction.z / RLVal(5.0);
					/*
					direction.x = direction.z = proximity.x = proximity.z = RLVal(0.0);
					direction.z = proximity.z = (separation.y - RLVal(Nearby.building_ptr[i]->scale));
					*/
				}
			}
		} else {
			// over top of building
			proximity.x = direction.x = separation.x/RLVal(BuildingSize*2);
			proximity.z = direction.z = separation.z/RLVal(BuildingSize*2);
			direction.y = (separation.y - RLVal(Nearby.building_ptr[i]->building.max.y))/RLVal(BuildingSize*2);
			// direction is vector from center to car
			proximity.y = RLVal(0.0);
		}
		RLVectorNormalise(&direction);
		dist2 = RLVectorDotProduct(&proximity, &proximity);
	    if (dist2) {
	    	oomph = RLDivide(RLMultiply(RLVal(0.1),BuildingSize), dist2);
	    	RLVectorScale(&oneforce, &direction, oomph);
			force->x += oneforce.x;
			force->y += RLVal(Nearby.building_ptr[i]->building.max.y) * RLVal(0.5) * oneforce.y ;
			force->z += oneforce.z;
		}

//		if(Nearby.building_ptr[i]->building_num != -1)
//		{
//			char Info[256];
//			sprintf(Info,"Spore is near specific building %d",Nearby.building_ptr[i]->building_num);
//			BYDumpInfo(Info);
//			sprintf(Info,"bbox = (%f, %f, %f), (%f, %f, %f)",
//				Nearby.building_ptr[i]->building.max.x,
//				Nearby.building_ptr[i]->building.max.y,
//				Nearby.building_ptr[i]->building.max.z,
//				Nearby.building_ptr[i]->building.min.x,
//				Nearby.building_ptr[i]->building.min.y,
//				Nearby.building_ptr[i]->building.min.z);
//			BYDumpInfo(Info);
//			sprintf(Info, "Additional force = (%f, %f, %f)",oneforce.x,RLMultiply3(RLVal(Nearby.building_ptr[i]->building.max.y), RLVal(0.5), (oneforce.y)),oneforce.z);
//			BYDumpInfo(Info);
//			sprintf(Info,"oneforce.y = %f\n",oneforce.y);
//			BYDumpInfo(Info);
//		}
	
	}
	return(Nearby.count);
}

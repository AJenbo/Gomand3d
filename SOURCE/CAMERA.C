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
File:           camera.c
Author:         J. Spudde Childs
Date:           9-26-95
Version:        1.3



************************************************************************
REVISION HISTORY        (Add Edits and History to top of list).

Edited By:      Jeremiah Spudde Childs
Edited Date:    10/23/95
Changes:
                changed VERSION_NUMBER from 1.21 to 1.3.
                Added code (and states) for Watchy to navigate the cities.
				Still needs bug fixing when Watchy accidentally enters a building.


Edited By:      Jeremiah Spudde Childs
Edited Date:    10/4/95
Changes:
                changed VERSION_NUMBER from 1.2 to 1.21.
                Made minor bug fix to POV code that keeps it in POV mode.


Edited By:      Jeremiah Spudde Childs
Edited Date:    9/30/95
Changes:
                changed VERSION_NUMBER from 1.1 to 1.2.
                Added camera sweetspot of POV that gives a first-person, 
                point of view for the camera.


Edited By:      Jeremiah Spudde Childs
Edited Date:    9/29/95
Changes:
                changed VERSION_NUMBER from 1.0 to 1.1.
                Added camera method of CIRCLE that orbits about a point 
				(in this case, the dead Robot or monster).  Also has a 
				countdown timer for the circling death view before it signals
				the end of the level.


***********************************************************************/


#include "rl2d3d.h"
#include "wrapper.h"

#include <math.h>

#include "camera.h"
#include "gosys.h"
#include "landscap.h"
#include "Robotanim.h"
#include "timing.h"
#include "boink.h"
#include "monanim.h"
#include "building.h"
#include "ichars.h"
#include "global.h"
#include "Robotmove.h"
#include "monmove.h"

//#define padding RLVal(6.0)
#define PADDING RLVal(4.0)
#define BUILDINGLIMIT (4.25)
#define BUILDINGSIZE (4.0)

extern  short   SysWatchyStyle;
extern  RLValue sealevel;
extern  RLFrame Wcamera, Wscene;
extern  unsigned long int looptime;
//extern  int     level;
extern  int     RobotLife;
extern  int     MnstLife;
extern  RLFrame monstframe;
extern  RLFrame Robotframe;
//extern  int     Vsize;
//extern  unsigned short RobotStatus[5];
extern  int     autodemo;
//extern  int     submonster;
extern  HotSpot RobotHotSpots[];
static  RLValue autocountdown = RLVal(200);
static  RLValue targetspeed2;
static  int     cameramode = 8;
static  int     camerarolling=0;
RLFrame goodguyframe;
RLFrame badguyframe;
RLFrame targetframe;
int     countdown;


void DestroyCameraInfo(Caminfo** camstuff)
{
	RLFrameRemoveCallback(Wcamera, cameraalg, (void*)*camstuff);
	MDFreeD3DFrame((*camstuff)->target);
	(*camstuff)->target = NULL;
	free(*camstuff);
	*camstuff = NULL;
	camerarolling = 0;
}


// **************************************************************************
// Name:			    CreateCameraInfo
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.4
//
// Description:		Creates and initializes a Caminfo structure and 
//						      initializes global variables
//
// Arguments:		Caminfo** camstuff: (OUT) double pointer to structure 
//					          containing data for the camera movement
//				    RLFrame Robotframe:  (IN) the frame used to position the 
//                                           Robot
//				    RLFrame monstframe: (IN) the frame used to position the 
//				                              monster
//
// Return:			none
//
// Side Effects:	Assigns global variables of badguyframe, goodguyframe,
//						      and targetframe.  Sets callback to camera's frame.
//						      Initializes global variables camerarolling, 
//						      countdown, autocountdown, and cameramode.
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
#include "byglobal.h"

void CreateCameraInfo(Caminfo** camstuff, RLFrame Robotframe, RLFrame monstframe)
{

    // camerarolling is a flag that is true if the camera has already been 
    // created and initialized
	if (!camerarolling) 
	{
	    RLMalloc((void**)camstuff, sizeof(Caminfo));
	    badguyframe = monstframe;
	    targetframe = goodguyframe = Robotframe;
	}

	if (PlayAsMonster)
	{
		goodguyframe = monstframe;
		targetframe = badguyframe = Robotframe;
	}
	else
	{
		targetframe = goodguyframe = Robotframe;
		badguyframe = monstframe;
	}
    
    // fill in structure, setting initial conditions
	(*camstuff)->target = RLCreateFrame(targetframe);
  
    (*camstuff)->current = BEHINDRIGHT;   // level is initialized with
    (*camstuff)->next = BEHINDRIGHT;      // BEHINDRIGHT sweetspot
  
    (*camstuff)->method = WATCHDROP;      // level is initialized with 
                                          // WATCHDROP movement method
	
	(*camstuff)->zone = 2;                // level is initialized with zone of
                                          // 2 (zone is the fine control of
                                          // the sweetspot location
  
    (*camstuff)->velocity.x = RLVal(0.0); // level is initialized with no
    (*camstuff)->velocity.y = RLVal(0.0); // velocity
    (*camstuff)->velocity.z = RLVal(0.0);
                        
    // sets the callback to control the camera
	RLFrameAddCallback(Wcamera, cameraalg, (void*) *camstuff);
	
	// camera data has been created and initialized
	camerarolling = 1;
	// indicates that there is no countdown in effect
	countdown = -1;
	
	// for autodemo mode, the countdown value is set to 350/30 seconds.
	autocountdown = RLVal(350); 
	// for autodemo mode, the camera starts looping through camera modes 
	// starting in mode number 8
	cameramode = 8;
}

// **************************************************************************
// Name:			    cameraalg
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.4
//
// Description:		

// 					This code moves the camera acording to its movement state
//							Callback to camera frame.  Calls all functions that 
//					        control camera motion.
//
// Arguments:		RLFrame cam:  (IN) RLFrame containing the camera
//					void* arg:  (IN/OUT) void pointer to be cast as pointer to
//						    Caminfo structure.  Some members are used as input, 
//                          others are set as output.
//
// Return:			none
//
// Side Effects:	Calls HandleDeath() to check for character deaths.
//						      sets global variable of targetspeed2.
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


void cameraalg(RLFrame cam, void* arg, RLValue delta)
{
    Caminfo* camstuff = (Caminfo*) arg; // pointer to camera data
    RLVector camera_delta;              // world coordinate vector from Robot to camera
    RLVector sweetspot;                 // world coordinate vector that the camera will look toword
	RLVector target;                    // world coordinate vector that the camera will move toword
	RLVector oldtarget;                 // last frame target vector 
	RLVector camplace;                  // world coordinate vector of location of the camera
	RLVector oldvel;                    // last frame velocity of the camera
    RLValue  groundheight, groundmove;  //
    RLFrame  scene = RLFrameGetScene(cam);
//	extern BOOL   AutoDemoFlag;    
    
    RLFrameGetPosition(Wcamera, scene, &camplace);
    
    // function to determine if a character has been killed
	if (!HandleDeath())
	{
		if (GameStates.IsAutodemo) AutoCameras(camstuff);
	}
    
    
    // groundheight is the greater of sealevel or the ground height at x and z coordinates
    groundheight = MAX(SpuddeMapHeight2(camplace.x, camplace.z), sealevel);

    if ((groundheight + GROUNDCLEARANCE) > camplace.y) 
	{
		groundmove = RLMultiply((groundheight + GROUNDCLEARANCE - camplace.y ), RLMultiply(DiffFrame, RLVal(0.1)));
    } 
    else 
    {
		if (camplace.y > cpx / 2) 
		{ 
			RLFrameGetVelocity(Wcamera, Wscene, &oldvel);
			groundmove = RLMultiply(RLVal(-0.75), oldvel.y);
		} 
		else 
		{
			groundmove = RLVal(0.0);
		}
    }
    
                                   
    // fill in method and sweetspot values of camstuff for this frame
	PickMethodAndSpots(camstuff, &sweetspot, &target, camplace); 

    // SLIDE TARGET TO NEW LOCATION
    // (Move it 1/4 of dist from old to new for smooth transitions)
    RLFrameGetPosition(camstuff->target, Wscene, &oldtarget);
	targetspeed2 = 
		RLMultiply((target.x - oldtarget.x), (target.x - oldtarget.x)) +
		RLMultiply((target.z - oldtarget.z), (target.z - oldtarget.z));
    EaseInto(&target, &oldtarget, &target, RLVal(0.25));

	RLFrameSetPosition(camstuff->target, Wscene, target.x, target.y, target.z);

    RLFrameGetPosition(Wcamera, targetframe, &camera_delta);

	//  apply movement algorithm according to the movement method flag
    switch (camstuff->method) 
	{
	    case HOLD:
	    	camera_hold(camstuff, groundmove);
			break;
	    case SLUGDRIFT:
	    	camera_slugdrift(camstuff, &sweetspot, &camera_delta, groundmove);
			break;
	    case POV:
	    	camera_pov(camstuff, &sweetspot, &camera_delta, groundmove);
			break;
	    case CIRCLE:
	    	camera_circle(camstuff, &sweetspot, &camera_delta, groundmove);
			break;
	    case DRIFT:
	    	camera_drift(camstuff, &sweetspot, &camera_delta, groundmove);
			break;
	    case CITYLIFE:
	    	camera_bigcity(camstuff, &sweetspot, &camera_delta, groundmove, camplace);
			break;
	    case WATCHDROP:
	    	camera_watchdrop(camstuff, &camplace, groundheight);
			break;
	    case HUMANEYE:
	    	camera_humaneye(camstuff, &camplace, groundheight);
			break;
	    case WATCHMELT:
	    	camera_watchmelt(camstuff, &camplace, groundheight);
			break;
	}
    
    // point the camera at the target
    RLFrameLookAt(Wcamera, camstuff->target, scene, RLConstrainZ);
    camstuff->current = camstuff->next;
}

// **************************************************************************
// Name:			    PickMethodAndSpots
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.4
//
// Description:		Sets vectors sweetspot and target vectors basen on the view type.  Calls PickNextSweetSpot()
//                  and PickMethod(), then sets vectors.
//
// Arguments:	    Caminfo* camstuff:  (IN/OUT) pointer to camera data 
//                               structure.  Some members are used as input, 
//                               others are set as output.
//				    RLVector *sweetspot:  (OUT) world coordinate vector
//                               that the camera will move toward
//                  RLVector *target:  (OUT) world coordinate vector
//                               that the camera will look toward
//                  RLVector camplace: (IN) world coordinate vector of the 
//                               location of the camera
//
// Return:			none
//
// Side Effects:	Calls HandleDeath() to check for character deaths.
//						      sets global variable of targetspeed2.
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

void PickMethodAndSpots(Caminfo* camstuff, RLVector *sweetspot, RLVector *target, RLVector camplace) 
{
    // DETERMINE MOVEMENT METHOD
	RLValue  dist2;
	RLVector chrsep, targetcenter;
   int fallingdown = 0;
    
    // we are finding the distance^2 between the players
    RLFrameGetPosition(badguyframe, goodguyframe, &chrsep);
    chrsep.y = RLVal(0.0);
    dist2 = RLVectorDotProduct(&chrsep, &chrsep);
    
    // get new sweetspot 
	camstuff->next = PickNextSweetSpot(camstuff, dist2, camplace, chrsep);
    // get new movement mode 
	camstuff->method = PickMethod(camstuff, dist2);


	//  if the next view type is behind the Robot
    if ((camstuff->next == BEHINDRIGHT) || (camstuff->next == BEHINDLEFT) || (camstuff->next == BIGCITY)) 
	{
      float multiplier;

      if (camstuff->next == BEHINDRIGHT) 
		{
			multiplier = D3DVAL(-1.0);
		}
		else if (camstuff->next == BEHINDLEFT) 
		{
			multiplier = D3DVAL(1.0);
		}
      else
		{
			multiplier = D3DVAL(-0.25);
		}

        
        // if Robot is the target of the camera, assign the center of the 
        // Robot's chest as the sweetspot in Robotframe coordinates.  if monster
        // is the target of the camera, assign the center of the monster's head
        // as the sweetspot in Robotframe coordinates.  Otherwise
        // set it to be at the center of the target frame with altitude of 1.0
        // Code below will adjust it from there.
		if (targetframe == Robotframe) 
		{
			RLFrameGetPosition(RobotHotSpots[RobotChest].position, targetframe, &targetcenter);
			targetcenter.x += RobotHotSpots[RobotChest].point1.x;
			targetcenter.y += RobotHotSpots[RobotChest].point1.y;
			targetcenter.z += RobotHotSpots[RobotChest].point1.z;
		} 
		else if (targetframe == monstframe)
		{
			RLFrameGetPosition(MonsterHotSpots[RoggoshHead].position, targetframe, &targetcenter);
			targetcenter.x += MonsterHotSpots[RoggoshHead].point1.x;
			targetcenter.y += MonsterHotSpots[RoggoshHead].point1.y;
			targetcenter.z += MonsterHotSpots[RoggoshHead].point1.z;
		} 
      else
      {
         targetcenter.x = D3DVAL(0.0);
			targetcenter.y = D3DVAL(1.0);
			targetcenter.z = D3DVAL(0.0);
      }
      sweetspot->x = targetcenter.x;
      sweetspot->y = targetcenter.y;
      sweetspot->z = targetcenter.z;
		
		// calculate position of sweetspot based on zone. zone is the fine
        // control over the location of the sweetspot.
		switch (camstuff->zone) 
		{
			case 2:     // Behind -- currently key '2'
				sweetspot->x += D3DVAL(0.9 * multiplier);
				sweetspot->y += D3DVAL(1.0);	
				sweetspot->z += D3DVAL(3.0);
				break;
			case 3:        // In front -- currently key '6' 
				sweetspot->x += D3DVAL(0.25 * multiplier);
				sweetspot->y += D3DVAL(0.2);	
            sweetspot->z += D3DVAL(-6.0);
            if (targetframe == Robotframe)
               sweetspot->z += D3DVAL(-RobotSpeed * DiffFrame * 5.0);
            else if (targetframe == monstframe)
               sweetspot->z += D3DVAL(-MonsterSpeed * DiffFrame * 5.0);
				break;
			case 4:        // Behind and a little above -- currently key '3'
				sweetspot->x += D3DVAL(1.5 * multiplier);
				sweetspot->y += D3DVAL(2.0);	
				sweetspot->z += D3DVAL(4.0);
				break;
			case 5:        // Overhead -- currently key '7'
				sweetspot->x += D3DVAL(0.0);
				sweetspot->y += D3DVAL(16.0);	
				sweetspot->z += D3DVAL(2.5);
				break;
			case 6:        // Far behind and above -- currently key '8'
				sweetspot->x += D3DVAL(2.0 * multiplier);
				sweetspot->y += D3DVAL(16.0);         
				sweetspot->z += D3DVAL(16.0);       
				break;
			case 7:        // On the left size -- currently key '4'
				sweetspot->x -= RLVal(4.0);
				sweetspot->y += RLVal(2.5);	
				sweetspot->z += RLVal(4.0);
				break;
			case 8:        // On the right size -- currently key '5'
				sweetspot->x += RLVal(4.0);
				sweetspot->y += RLVal(2.5);	
				sweetspot->z += RLVal(4.0);
				break;
		}  
		
		// calculate new target position based on zone/
		switch (camstuff->zone) 
		{
			case 2:     // Behind -- currently key '2'              
				target->x = D3DVAL(0.0);
            target->y = targetcenter.y+D3DVAL(0.5);
            target->z = D3DVAL(-1.5);
				break;
			case 3:        // In front -- currently key '6'
				target->x = D3DVAL(0.0);
				target->y = targetcenter.y;
				target->z = D3DVAL(4.0);
				break;
			case 4:        // Behind and a little above -- currently key '3'
				target->x = D3DVAL(0.0);
				target->y = targetcenter.y;
				target->z = D3DVAL(-0.85);
				break;
			case 5:        // Overhead -- currently key '7'
				target->x = D3DVAL(0.0);
				target->y = targetcenter.y;
            target->z = D3DVAL(0.5);
				break;
			case 6:        // Far behind and above -- currently key '8'
				target->x = D3DVAL(0.0);
				target->y = targetcenter.y;
				target->z = RLVal((-2.0));
				break;
			case 7:        // On the left size -- currently key '4'
				target->x = D3DVAL(0.0);
				target->y = targetcenter.y;
				target->z = D3DVAL(-0.5);
				break;
			case 8:        // On the right size -- currently key '5'
				target->x = D3DVAL(0.0);
				target->y = targetcenter.y;
				target->z = D3DVAL(-0.5);
				break;
		}  
	   if((goodguyframe == Robotframe) && (RobotMovementState == RobotKnockDown || RobotMovementState == RobotKnockDownOnBuilding))
         fallingdown = 1;
	   if((goodguyframe == monstframe) && (MonsterMovementState == MonsterKnockBackward))
         fallingdown = 1;
      if (fallingdown)
         target->z = D3DVAL(0.0);
		// convert from target coord system to world coord system
		RLFrameTransform(targetframe, target, target);
    }
    
    
    // if sweetspot is set to look at characters from a side view (as in
    // fighting games)
    if (camstuff->next == SIDERIGHT)  
	{   
		
		// the sweetspot is set to the right side of the players
		sweetspot->x = chrsep.z * 2 + chrsep.x / 2;
		sweetspot->y = RLVal(0.25);
		sweetspot->z = -chrsep.x * 2 + chrsep.z /  2;
		
		// target lies midway between the players
		target->x =  chrsep.x / 2;
		target->y =  RLVal(1.8);
		target->z =  chrsep.z / 2; 
		
		// convert from target coord system to world coord system
		RLFrameTransform(targetframe, target, target);
    }                             
    
    if (camstuff->next == SIDELEFT)  
	{    
	    // same as above but to the left
		sweetspot->x = (-chrsep.z * 2 + chrsep.x / 2);
		sweetspot->y = RLVal(0.25);
		sweetspot->z = (chrsep.x * 2 + chrsep.z / 2);
	
		// target lies midway between the players
		target->x =  chrsep.x / 2;
		target->y =  RLVal(1.8);
		target->z =  chrsep.z / 2;
	
		// convert from target coord system to world coord system
		RLFrameTransform(targetframe, target, target);
    }               
    
	// if camera is in first-person mode, the camera should reside inside
    // the character
	if (camstuff->next == INSIDE) 
	{     
        // if Robot is the target of the camera, assign the center of the 
        // Robot's chest as the sweetspot in Robotframe coordinates.  Otherwise
        // set it to be at the center of the target frame with altitude of 1.0
        // Code below will adjust it from there.
		if (targetframe == Robotframe) 
		{
			RLFrameGetPosition(RobotHotSpots[RobotChest].position, targetframe, sweetspot);
			sweetspot->x += RobotHotSpots[RobotChest].point1.x;
			sweetspot->y += RobotHotSpots[RobotChest].point1.y;
			sweetspot->z += RobotHotSpots[RobotChest].point1.z;
		} 
		if (targetframe == monstframe) 
		{
			RLFrameGetPosition(RobotHotSpots[RobotChest].position, targetframe, sweetspot);
			sweetspot->x += MonsterHotSpots[RoggoshBody].point1.x;
			sweetspot->y += MonsterHotSpots[RoggoshBody].point1.y;
			sweetspot->z += MonsterHotSpots[RoggoshBody].point1.z;
		} 
		else 
		{
			sweetspot->x = RLVal(0);
			sweetspot->y = RLVal(1);
			sweetspot->z = RLVal(0);
		}
		target->x =  RLVal(0);
		target->y =  sweetspot->y;
		target->z =  RLVal(-15.0);
		// convert from target coord system to world coord system
		RLFrameTransform(targetframe, target, target);
      if (camstuff->current != INSIDE)
         RLFrameSetPosition(Wcamera, targetframe, sweetspot->x, sweetspot->y, sweetspot->z);
    }

	// if the sweetspot is set to cirle around the character
	if ((camstuff->next == CIRCLING))    
	{   
		// if the Robot is dead 
		//if (RobotLife == 0)    
      if (targetframe == monstframe)
		{
			// set the target at the body of the monster
			RLFrameGetPosition(MonsterHotSpots[RoggoshBody].position, Wscene, target);
		}
		else 
		{
			// set the target at the body of the Robot
			RLFrameGetPosition(RobotHotSpots[RobotChest].position, Wscene, target);
		}
	} 

	// if the sweetspot is set to have landed on the ground
	if ((camstuff->next == ONTHEGROUND))  
	{   
		// if the focus is the Robot coord system
		if (targetframe == Robotframe) 
		{
			//set the target to the Robot chest center. 
			RLFrameGetPosition(RobotHotSpots[RobotChest].position, Wscene, target);
		}
		else 
		{
			//set the target to the monster body center. 
			RLFrameGetPosition(MonsterHotSpots[RoggoshBody].position, Wscene, target);
		}
	} 
    
    // if the method has been set to cut to a view that watches the monster
    // melt while the Robot does a taunt behind it
	if ((camstuff->method == WATCHMELT) && (GameStates.CurrentSubmonster == Gamma)) 
	
	{
		target->x =  chrsep.x / 2;
		target->y =  chrsep.y / 2 + RLVal(1.25); // 1.25 units above the character's
                                             // RLFrame which is centered at its
                                             // feet
		target->z =  chrsep.z / 2;
		RLFrameTransform(targetframe, target, target);
	}
}

// **************************************************************************
// Name:			    PickNextSweetSpot
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.4
//
// Description:		Finds the next sweetspot type based on the current movement
//                  method type or sweetspot type

// Arguments:		Caminfo* camstuff:  (IN/OUT) pointer to camera data 
//                           structure.  Some members are used as input, 
//                           others are set as output.
//				    RLValue dist2:  (IN) square of distance from Robot to 
//                           monster
//                  RLVector camplace:  (IN) world coordinate vector of camera
//                           location
//                  RLVector chrsep:  (IN) location of badguyframe in 
//                           goodguyframe coordinates.  Relative separation of 
//                           characters.
//
// Return:			int:  flag for type of sweetspot to be used next
//
// Side Effects:	none
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

int PickNextSweetSpot(Caminfo* camstuff, RLValue dist2, RLVector camplace, RLVector chrsep)
{
	RLVector Robotplace;

	if (camstuff->method == CIRCLE)   return CIRCLING;
	if (camstuff->method == POV) 	  return INSIDE;
	if (camstuff->method == HUMANEYE) return ONTHEGROUND;

	// if the there are buildings within 10.0 units of the Robot
	RLFrameGetPosition(targetframe, Wscene, &Robotplace);
	if (CountBuildings(Robotplace, RLVal(10.0))) 
	{
		return BIGCITY ; 
	}
	
	// To exit first-person mode
	// if current view was for first person, but camstuff->method != POV (see 
    // above) then set sweetspot to BEHINDRIGHT.
	if (camstuff->current == INSIDE)
	{
		return(BEHINDRIGHT);
	}
	
	// SysWatchyStyle is an obsolete variable to control "Watchy mode"
    // this condition would apply to camera that switches views based on the
    // location of the characters, not on user input.
	if ((SysWatchyStyle ==0) || (camstuff->next == SIDERIGHT) || (camstuff->next == SIDELEFT)|| (camstuff->current == SIDERIGHT) || (camstuff->current == SIDELEFT)) 
	{
		
		// if the characters are far apart, move to behind the Robot.
		if (dist2 > RLVal(144.0)) 
		{
			if ((camstuff->current != BEHINDRIGHT) && (camstuff->current != BEHINDLEFT)) 
			{
				return(PickABack(camstuff));
			} 
			else
			{
				return(camstuff->current);
			}
		}
        // if the characters are close together, move to side view of both
        // characters
		if (dist2 < RLVal(100.0)) 
		{
			if ((camstuff->current != SIDERIGHT) && (camstuff->current != SIDELEFT)) 
			{
				return(PickASide(camstuff, chrsep));
			} 
			else
			{
				return(camstuff->current);
			}
		}
	}   
	
	// if no other mode has been chosen then it should be behind the character
    // if not currently behind the character, it should go behind on either the
    // right or left
	if ((camstuff->current != BEHINDRIGHT) && (camstuff->current != BEHINDLEFT)) 
	{
		return(PickABack(camstuff));
	}
	// if nothing else was chosen, use the previous sweetspot
	return(camstuff->current);
}

// **************************************************************************
// Name:			    PickASide
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.5
//
// Description:		Chooses between the right and left side of the Robot
//                  for a side view, based on the number of buildings
//                  near each potential sweetspot.  The side with fewer
//                  buildings is chosen to minimize possibility of
//                  having the camera move inside a building.
//
// Arguments:		Caminfo* camstuff:  (IN/OUT) pointer to camera data 
//                           structure.  Some members are used as input, 
//                           others are set as output.
//                  RLVector chrsep:  (IN) location of badguyframe in 
//                           goodguyframe coordinates.  Relative separation of 
//                           characters.
//
// Return:			int:  sweetspot flag (SIDERIGHT or SIDELEFT) to be used
//
// Side Effects:	none
//
// Notes:			
//
// Known Restrictions:
//                Hardcoded radius of 9.0 passed to CountBuildings().
//
// Error Number:
//
// Update:
// Date				Name			Description
// =========================================================================
//
// **************************************************************************

int PickASide(Caminfo* camstuff, RLVector chrsep)
{
	RLVector rightvec, leftvec;
	
	// a vector in targetframe coordinates that is to the left of the 
    // characters
	leftvec.x = (-chrsep.z * 2 + chrsep.x / 2);
	leftvec.y = RLVal(0.25);
	leftvec.z = chrsep.x * 2 + chrsep.z / 2;
    
	// a vector in targetframe coordinates that is to the right of the 
    // characters
	rightvec.x = +(chrsep.z * 2 + chrsep.x / 2);
	rightvec.y = RLVal(0.25);
	rightvec.z = -chrsep.x * 2 + chrsep.z / 2;
    
    // convert from targetframe coordinates to world coordinates
	RLFrameTransform(targetframe, &(leftvec), &(leftvec));
	RLFrameTransform(targetframe, &(rightvec), &(rightvec));
    
    // select a view to the side with less buildings
	if (CountBuildings(leftvec, RLVal(9.0)) < CountBuildings(rightvec, RLVal(9.0)))
	{
		return(SIDELEFT);
	}
	else
	{
		return(SIDERIGHT);
	}
}


// **************************************************************************
// Name:			    PickABack
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.5
//
// Description:		Chooses between the right and left side of the Robot
//                  for a view from behind the character, based on the 
//                  number of buildings near each potential sweetspot.  
//                  The side with fewer buildings is chosen to minimize 
//                  possibility of having the camera move inside a building.
//
// Arguments:		Caminfo* camstuff:  (IN) pointer to camera data structure
//
// Return:			int:  sweetspot flag (BEHINDRIGHT or BEHINDLEFT) to be used
//
// Side Effects:	None.
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

int PickABack(Caminfo* camstuff)
{
	RLVector rightvec, leftvec;
	
	
	// a vector in targetframe coordinates that is behind and to the left of 
	// the character
	leftvec.x = RLVal(0.7);
	leftvec.y = RLVal(0.65);
	leftvec.z = RLVal(3.0);
    
	// a vector in targetframe coordinates that is behind and to the right 
	// of the character
	rightvec.x = RLVal(-0.7);
	rightvec.y = RLVal(0.65);
	rightvec.z = RLVal(3.0);
    
    // convert from targetframe coordinates to world coordinates
	RLFrameTransform(targetframe, &(leftvec), &(leftvec));
	RLFrameTransform(targetframe, &(rightvec), &(rightvec));
    
    // pick a view with fewer buildings
	if (CountBuildings(leftvec, PADDING) < CountBuildings(rightvec, PADDING))
	{
		return(BEHINDLEFT);
	}
	else
	{
		return(BEHINDRIGHT);
	}
}

// **************************************************************************
// Name:			    PickMethod
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.5
//
// Description:		Chooses movement method.
//
// Arguments:		Caminfo* camstuff:  (IN) pointer to camera data structure
//                  RLValue dist2:  (IN) square of distance from Robot to monster
//
// Return:			int:  Movement method.  SLUGDRIFT method is default.
//
// Side Effects:	None
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

int PickMethod(Caminfo* camstuff, RLValue dist2)
{
	//if ((MonsterAnimationState == MonsterAllDead) || (RobotLife == 0)) return(CIRCLE);
	//if (HandleDeath()) return(CIRCLE);
	//if (MonsterAnimationState == MonsterAllDead)
	//		return(WATCHMELT);
	if (camstuff->method == CIRCLE) return(CIRCLE);
	if (camstuff->method == POV)    return(POV);
	if (camstuff->method == WATCHDROP) return(WATCHDROP);
	if (camstuff->method == HUMANEYE) return(HUMANEYE);
	if (camstuff->next == BIGCITY) return(CITYLIFE);
	
	//if (dist2 < RLVal(4.0)) return(HOLD);
    return(SLUGDRIFT);
}

// **************************************************************************
// Name:			    camera_hold
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.4
//
// Description:		Function for movement method HOLD.  Scales down 
//                  the velocity of the camera.
//
// Arguments:	    Caminfo* camstuff:  (IN) pointer to camera data structure
//                  RLValue groundmove:  (IN) additional velocity change in the
//                          y-direction required to move the camera above the
//                          landscape.
//
// Return:			  None.
//
// Side Effects:	Sets velocity of camera frame.
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

void camera_hold(Caminfo* camstuff, RLValue groundmove)
{
	RLVector oldvel;
    
    // get the camera velocity
	RLFrameGetVelocity(Wcamera, camstuff->target, &oldvel); 
	
	// scale velocity down by factor of 1/8 and reapply
	RLFrameSetVelocity(Wcamera, camstuff->target,
	DiffFrame * (oldvel.x) / 8, 
	DiffFrame * ((oldvel.y) / 8 + groundmove),
	DiffFrame * (oldvel.z) / 8);
}

// **************************************************************************
// Name:			    camera_slugdrift
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.4
//
// Description:		Function for movement method SLUGDRIFT.  Moves the camera 
//                  toward the sweetspot vector.  Change in camera velocity 
//                  proportional to the distance from the sweetspot vector.
//                  Velocity changes are smoothed by a function call to 
//                  EaseInto().
//
// Arguments:		Caminfo* camstuff:  (IN) pointer to camera data structure
//                  RLVector* sweetspot:  (IN) pointer to world coordinate 
//                            vector to the sweetspot (location the camera will move 
//                            toward).
//                  RLVector* camera_delta:  (IN) pointer to vector of the 
//                            location of the camera with respect to the targetframe.
//                  RLValue groundmove:  (IN) additional velocity change in the
//                            y-direction required to move the camera above the
//                            landscape.
//
// Return:			None.
//
// Side Effects:	Sets velocity of camera frame.
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


void camera_slugdrift(Caminfo* camstuff, RLVector* sweetspot, RLVector* camera_delta, RLValue groundmove)
{
	RLVector distance, move, oldvel, newvel;
	RLValue dist2, r2best;
	extern int cuint;
   int fallingdown = 0;
   
    r2best = RLVal(0.25); // radius of sweetspot sphere
    
    // calculate the square of the distance between camera and sweetspot
	RLVectorSubtract(&distance, sweetspot, camera_delta);
	dist2 = RLVectorDotProduct(&distance, &distance);
    
    // if outside sweetspot sphere

	if((goodguyframe == Robotframe) && (RobotMovementState == RobotKnockDown || RobotMovementState == RobotKnockDownOnBuilding))
      fallingdown = 1;
	if((goodguyframe == monstframe) && (MonsterMovementState == MonsterKnockBackward))
      fallingdown = 1;

   if ((dist2 > r2best) && !fallingdown)
	{ 
		// calculate new velocity based on the separation
		
	    RLVectorScale(&move, &distance, DiffFrame * (RLVal(0.08)));
	    RLFrameGetVelocity(Wcamera, camstuff->target, &oldvel);
	    RLFrameSetVelocity(Wcamera, Wscene, RLVal(0.0), RLVal(0.0), RLVal(0.0));
		
		// smooth the changes
		EaseInto(&newvel, &oldvel, &move, (targetspeed2 > RLVal(1) ? RLDivide(RLVal(0.25), targetspeed2) : RLVal(0.4)));
		
		// this moves camera away from ground
		newvel.y += groundmove;
		
		// make sure that the camera cannot move farther than the land polygon size
		// This needs a function to access land data instead of cuint
		if (newvel.x > 0.75 * cuint) 
		{  
			// cuint is the land polygon size
			RLVectorScale(&newvel, &newvel, RLDivide(0.75 * cuint, newvel.x));
			if (groundmove == RLVal(0.0)) 
			{
				newvel.y -= RLMultiply(DiffFrame, RLVal(0.09));
			}
		}
		if (newvel.z > 0.75 * cuint) 
		{
			RLVectorScale(&newvel, &newvel, RLDivide(0.75 * cuint, newvel.z));
			if (groundmove == RLVal(0.0)) newvel.y -= RLMultiply(DiffFrame, RLVal(0.09));
		}
		
		// set the new camera velocity
	    RLFrameSetVelocity(Wcamera, camstuff->target,
			newvel.x,
			newvel.y,
			newvel.z);
	} 
	else 
	{  
	    // set velocity to 0 if inside the sphere
	    RLFrameSetVelocity(Wcamera, camstuff->target, RLVal(0.0), RLVal(0.0), RLVal(0.0));
	}
}

// **************************************************************************
// Name:			    camera_bigcity
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.4
//
// Description:		Function for movement method BIGCITY.  Moves the camera 
//                  toward the sweetspot vector.  Change in camera velocity 
//                  proportional to the distance from the sweetspot vector.
//                  Velocity changes are smoothed by a function call to 
//                  EaseInto().  Camera is moved away from buildings by
//                  using the results from a call to GetAntiBuildingForce().
//
// Arguments:		Caminfo* camstuff:  (IN) pointer to camera data structure
//                  RLVector* sweetspot:  (IN) pointer to world coordinate 
//                            vector to the sweetspot (location the camera will move 
//                            toward).
//                  RLVector* camera_delta:  (IN) pointer to vector of the 
//                            location of the camera with respect to the targetframe.
//                  RLValue groundmove:  (IN) additional velocity change in the
//                            y-direction required to move the camera above the
//                            landscape.
//                  RLVector camplace: (IN) world coordinate vector of the 
//                            location of the camera
//
// Return:			None.
//
// Side Effects:	Sets velocity of camera frame.
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

void camera_bigcity(Caminfo* camstuff, RLVector* sweetspot, RLVector* camera_delta, RLValue groundmove, RLVector camplace)
{
	RLVector distance, move, oldvel, newvel, flatsep, antibuildingforce;
	RLValue dist2, r2best, sep2, sep;
	extern int cuint;
   int fallingdown = 0;

	if((goodguyframe == Robotframe) && (RobotMovementState == RobotKnockDown || RobotMovementState == RobotKnockDownOnBuilding))
      fallingdown = 1;
	if((goodguyframe == monstframe) && (MonsterMovementState == MonsterKnockBackward))
      fallingdown = 1;

    // sweetspot sphere radius
    r2best = RLVal(0.1);
                              
    // camera position in local coords                          
	flatsep.x = camera_delta->x;
	flatsep.z = camera_delta->z;
	flatsep.y = RLVal(0.0);
    
    // distance^2
	sep2 = RLVectorDotProduct(&flatsep, &flatsep);
	// distance between camera and parent coords
	sep = RLVal(sqrt(sep2));
    
    // distance between camera and sweetspot
	RLVectorSubtract(&distance, sweetspot, camera_delta);
	dist2 = RLVectorDotProduct(&distance, &distance);
    
    // if camera is outside sweetspot sphere
   if ((dist2 > r2best) && !fallingdown)
	{        
	    // calculate new velocity vector based on distance between camera and sspot
	    RLVectorScale(&move, &distance, DiffFrame * (RLVal(0.07)));
		
		// if the target is moving too fast, then the camera must be raised
        // in altitude to keep from going through hills and buildings
		if (targetspeed2 > RLVal(1)) 
		{
			if (sep2 < RLVal(4)) move.y += RLVal(0.1)   * (RLVal(4)-sep2);
			if ((sep > RLVal(6))) move.y += RLVal(0.03) * (RLVal(sep)-RLVal(6));
	    }
	    
	    // get old velocity from the camera
	    RLFrameGetVelocity(Wcamera, camstuff->target, &oldvel);
	    // set to zero
	    RLFrameSetVelocity(Wcamera, Wscene, RLVal(0.0), RLVal(0.0), RLVal(0.0));
		
		//EaseInto(&newvel, &oldvel, &move, RLVal(0.25));
		EaseInto(&newvel, &oldvel, &move, (targetspeed2 > RLVal(1) ? RLDivide(RLVal(0.25), targetspeed2) : RLVal(0.35)));
		
		//add ground movement to the y component
		newvel.y += groundmove;
	    //newvel.x = (move.x + 3*oldvel.x)/4;
		//newvel.y = ((move.y + 3*oldvel.y)/4 + groundmove);
		//newvel.z = (move.z + 3*oldvel.z)/4;
		
		
		// make sure camera doesn't move futher than one land unit in x and z component
		if (newvel.x > 0.75 * cuint) 
		{
			RLVectorScale(&newvel, &newvel, RLDivide(0.75 * cuint, newvel.x));
			if (groundmove == RLVal(0.0)) 
			{
				newvel.y -= RLMultiply(DiffFrame, RLVal(0.09));
			}
		} 
		if (newvel.z > 0.75 * cuint) 
		{
			RLVectorScale(&newvel, &newvel, RLDivide(0.75 * cuint, newvel.z));
			if (groundmove == RLVal(0.0)) 
			{
				newvel.y -= RLMultiply(DiffFrame, RLVal(0.09));
			}
		}
	    
	    // set new velocity to camera
	    RLFrameSetVelocity(Wcamera, camstuff->target,
			newvel.x,
			newvel.y,
			newvel.z);
	} 
	else 
	{  
	    // set velocity to 0 if in sphere
	    RLFrameSetVelocity(Wcamera, camstuff->target, RLVal(0.0), RLVal(0.0), RLVal(0.0));
	}
    
    // get velocity vector for building avoidance
	GetAntiBuildingForce(camplace, &antibuildingforce);
	
	// add to camera velocity
	RLFrameGetVelocity(Wcamera, Wscene, &oldvel);
	RLFrameSetVelocity(Wcamera, Wscene,
	    oldvel.x + antibuildingforce.x,
	    oldvel.y + antibuildingforce.y,
	    oldvel.z + antibuildingforce.z);
}
// **************************************************************************
// Name:			    camera_pov
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.4
//
// Description:		Function for movement method POV.  Moves the camera 
//                  toward the sweetspot vector.  Change in camera velocity 
//                  proportional to the distance from the sweetspot vector.
//                  Velocity changes are smoothed by a function call to 
//                  EaseInto().  Movement is similar to slugdrift, but has
//                  much greater acceleration.
//
// Arguments:	    Caminfo* camstuff:  (IN) pointer to camera data structure
//                  RLVector* sweetspot:  (IN) pointer to world coordinate 
//                            vector to the sweetspot (location the camera will move 
//                            toward).
//                  RLVector* camera_delta:  (IN) pointer to vector of the 
//                            location of the camera with respect to the targetframe.
//                  RLValue groundmove:  (IN) additional velocity change in the
//                            y-direction required to move the camera above the
//                            landscape.
//
// Return:		    None.
//
// Side Effects:	Sets velocity of camera frame.
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


void camera_pov(Caminfo* camstuff, RLVector* sweetspot, RLVector* camera_delta, RLValue groundmove)
{
	RLVector distance, move, oldvel, newvel;
	RLValue dist2, r2best;
    
    // sweet spot sphere radius
    r2best = RLVal(0.25);

	// square of distance between sspot and camera
	RLVectorSubtract(&distance, sweetspot, camera_delta);
	dist2 = RLVectorDotProduct(&distance, &distance);
    
    //get cuurent velocity and set camera velocity to 0 
    RLFrameGetVelocity(Wcamera, camstuff->target, &oldvel);
    RLFrameSetVelocity(Wcamera, Wscene, RLVal(0.0), RLVal(0.0), RLVal(0.0));
    
    // 
    
    // mew velocity based on distance
    RLVectorScale(&move, &distance, DiffFrame * RLVal(0.7));
	
	newvel.x = RLVal((1 * move.x + oldvel.x) / 2.0);
	newvel.y = RLVal((1 * move.y + oldvel.y) / 2.0 + groundmove);
	newvel.z = RLVal((1 * move.z + oldvel.z) / 2.0);
	
	
	// dont move faster than the ground polygon dimensions
	if (newvel.x > 0.75 * cuint) 
	{
			RLVectorScale(&newvel, &newvel, RLDivide(0.75 * cuint, newvel.x));
			if (groundmove == RLVal(0.0)) 
			{
				newvel.y -= RLMultiply(DiffFrame, RLVal(0.05));
			}
	} 
	else 
	{
			if (newvel.z > 0.75 * cuint) 
			{
				RLVectorScale(&newvel, &newvel, RLDivide(0.75 * cuint, newvel.z));
				if (groundmove == RLVal(0.0)) 
				{
					newvel.y -= RLMultiply(DiffFrame, RLVal(0.05));
				}
			}
	}       
	
	// set the new velocity
	
    RLFrameSetVelocity(Wcamera, camstuff->target,
		newvel.x,
		newvel.y,
		newvel.z);
	/*
    RLFrameSetVelocity(Wcamera, camstuff->target,
		(1*move.x+oldvel.x)/2.0,
		(1*move.y+oldvel.y)/2.0,
		(1*move.z+oldvel.z)/2.0);
	*/
}

// **************************************************************************
// Name:			    camera_circle
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.6
//
// Description:		Function for movement method CIRCLE.  Moves the camera 
//                  in an orbit around the targetframe.  Camera velocity 
//                  is increased in the direction from the camera to the
//                  targetframe and increased in the direction perpendicular
//                  to the direction from the camera to the targetframe.
//                  Velocity changes are smoothed by a function call to 
//                  EaseInto().
//
// Arguments:		Caminfo* camstuff:  (IN) pointer to camera data structure
//                  RLVector* sweetspot:  (IN) pointer to world coordinate 
//                            vector to the sweetspot (location the camera will move 
//                            toward).
//                  RLVector* camera_delta:  (IN) pointer to vector of the 
//                            location of the camera with respect to the targetframe.
//                  RLValue groundmove:  (IN) additional velocity change in the
//                            y-direction required to move the camera above the
//                            landscape.
//
// Return:			None.
//
// Side Effects:	Sets velocity of camera frame.
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

void camera_circle(Caminfo* camstuff, RLVector* sweetspot, RLVector* camera_delta, RLValue groundmove)
{
	extern RLValue MonsterScaleFactor;
	RLVector target, distance, up, move, pull, oldvel, newvel, antibuildingforce;
	RLValue kludge, pullforce, dist, dist2, bestorbit;
	
	// calculate the best orbit depending on the size of the monster
	if (MnstLife == 0)  // if the monster is the dead
	{
		bestorbit = RLMultiply(BESTORBIT, MonsterScaleFactor);
	}
	else 
	{
		bestorbit = BESTORBIT;
	}
		
    // get position of target in world coords
	RLFrameGetPosition(camstuff->target, Wscene, &target);
	
	//set new height to target
	target.y += RLVal(0.5);
    
    // get position of the camera in world
    RLFrameGetPosition(Wcamera, Wscene, camera_delta); 
    
    // calc distance between camera and target
	RLVectorSubtract(&distance, &target, camera_delta);
	dist2 = RLVectorDotProduct(&distance, &distance);
	dist = RLVectorModulus(&distance);
    
    // this is confusing 
	up.x = up.z = RLVal(0.0); 
	pullforce = RLDivide(RLMultiply(DiffFrame, RLVal(1.0)), bestorbit * bestorbit);
	up.y = RLDivide(RLMultiply(DiffFrame, RLVal(-0.2)), sqrt(bestorbit));
	dist /= bestorbit * bestorbit;
	kludge = RLMultiply(RLVal(1.0), RLDivide(dist, sqrt(dist * dist + up.y * up.y)));
	pullforce *= (kludge);    
	
	// make distance a normal vector
	RLVectorNormalise(&distance);
	RLVectorCrossProduct(&move, &distance, &up);
	
	// this is also confusing
	RLVectorScale(&pull, &distance, pullforce);
  	RLFrameGetVelocity(Wcamera, Wscene, &oldvel);
  	RLFrameSetVelocity(Wcamera, Wscene, RLVal(0.0), RLVal(0.0), RLVal(0.0));
	move.x += pull.x; 
	move.y += pull.y; 
	move.z += pull.z; 
	EaseInto(&newvel, &oldvel, &move, RLVal(0.125));
	newvel.y += RLMultiply(groundmove, RLVal(0.5)) - RLDivide(RLVal(0.01), dist);
  
    // set new velocity to camera
  	RLFrameSetVelocity(Wcamera, Wscene,
		newvel.x, newvel.y, newvel.z);
	//	((pull.x + move.x) + 15*oldvel.x)/16,
	//	(((pull.y + move.y) + 15*oldvel.y)/16 + RLMultiply(groundmove, RLVal(0.5)) - RLDivide(RLVal(0.01), dist)),
	//	((pull.z + move.z) + 15*oldvel.z)/16);

	//if ((countdown > 100) || (countdown < 0)) countdown = 100;
	//countdown--;
	//if (countdown == 0) {
	//	NextLevel=1;
		//if (level!=0) { 
		//	if (MnstLife == 0) {
		//		level++;
		//		submonster = 0;
		//	} 
		//	if (RobotLife == 0)
		//		RobotStatus[GameStates.CurrentRobot] = 0;
		//} else level++;
	//}
	GetAntiBuildingForceCircle(*camera_delta, &antibuildingforce);
	RLFrameGetVelocity(Wcamera, Wscene, &oldvel);
	RLFrameSetVelocity(Wcamera, Wscene,
	    oldvel.x + antibuildingforce.x,
	    oldvel.y + antibuildingforce.y,
	    oldvel.z + antibuildingforce.z);
}

// **************************************************************************
// Name:			    camera_drift
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.6
//
// Description:		Obsolete function for obsolete movement method DRIFT.  
//                  Moves the camera toward the sweetspot vector.  Change 
//                  in camera velocity proportional to the distance from the 
//                  sweetspot vector.  Movement is similar to slugdrift, but 
//                  velocity changes are not smoothed.
//
// Arguments:		Caminfo* camstuff:  (IN) pointer to camera data structure
//                  RLVector* sweetspot:  (IN) pointer to world coordinate 
//                            vector to the sweetspot (location the camera will 
//                            move toward).
//                  RLVector* camera_delta:  (IN) pointer to vector of the 
//                            location of the camera with respect to the 
//                            targetframe.
//                  RLValue groundmove:  (IN) additional velocity change in the
//                            y-direction required to move the camera above the
//                            landscape.
//
// Return:			None.
//
// Side Effects:	Sets velocity of camera frame.
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

void camera_drift(Caminfo* camstuff, RLVector* sweetspot, RLVector* camera_delta, RLValue groundmove)
{
	RLVector distance, oldvel, delta, move;
	RLValue dist2, r2best;
    
    // radius of sweetspot sphere
    r2best = RLVal(0.25);
    
    // calculate distance squared
	RLVectorSubtract(&distance, sweetspot, camera_delta);
	dist2 = RLVectorDotProduct(&distance, &distance);
    
    // if outside sweetspot sphere
	if (dist2 > r2best) 
	{
	    
	    // scale distance vector
	    RLVectorScale(&move, &distance, RLVal(0.25));
	   
	    //RLFrameGetVelocity(camera, camstuff->target, &oldvel);
	    oldvel.x = camstuff->velocity.x;
	    oldvel.y = camstuff->velocity.y;
	    oldvel.z = camstuff->velocity.z;
	   
	    //RLFrameSetVelocity(camera, scene, 0, 0, 0);
	    //RLFrameSetVelocity(camera, camstuff->target,
		//(move.x), (groundmove + move.y), (move.z));
	    RLFrameGetPosition(Wcamera, camstuff->target, &delta);
	    RLFrameSetPosition(Wcamera, camstuff->target, 
		delta.x + move.x,
		delta.y + move.y + groundmove,
		delta.z + move.z);
	    camstuff->velocity.x = move.x;
	    camstuff->velocity.y = move.y + groundmove;
	    camstuff->velocity.z = move.z;
	} 
	else 
	{
	    //RLFrameSetVelocity(camera, camstuff->target, 0, 0, 0);
	    camstuff->velocity.x = RLVal(0.0);
	    camstuff->velocity.y = RLVal(0.0);
	    camstuff->velocity.z = RLVal(0.0);
	}
}

// **************************************************************************
// Name:			    camera_watchdrop
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.6
//
// Description:		Function for movement method WATCHDROP.  Keeps the camera
//                  stationary until the Robot leaves the jumping state
//                  that it is initialized in for the opening drop-in
//                  sequence.
//
// Arguments:		Caminfo* camstuff:  (IN) pointer to camera data structure
//                  RLVector* camplace:  (IN) pointer to vector of the 
//                            location of the camera in world coordinates.
//                  RLValue groundheight:  (IN) height of the landscape 
//                            directly under the camera
//
// Return:			None.
//
// Side Effects:	Sets velocity of camera frame.
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

void camera_watchdrop(Caminfo* camstuff, RLVector *camplace, RLValue groundheight)
{
	RLVector Robotpos, Robotup, Robotpoint;
	
	targetframe = Robotframe;
	
	// set camera velocity to 0
	RLFrameSetVelocity(Wcamera, Wscene,	RLVal(0.0), RLVal(0.0), RLVal(0.0));
	
	// get unit vectors in up and forward direction
	RLFrameGetOrientation(goodguyframe, Wscene, &Robotpoint, &Robotup);
	
	// get position of the Robot
	RLFrameGetPosition(goodguyframe, Wscene, &Robotpos);
    
    // invert x and z to get side view of Robot, place camera 5 units to side 
	camplace->x = Robotpos.x + 5 * Robotpoint.z;
	camplace->z = Robotpos.z - 5 * Robotpoint.x;
	camplace->y = MAX(sealevel, SpuddeMapHeight2(camplace->x, camplace->z)) + GROUNDCLEARANCE;

	RLFrameSetPosition(Wcamera, Wscene, camplace->x, camplace->y, camplace->z);
    
    // after jump down move to slugdrift mode
	if (((RobotAnimationState != RobotJumpStop) && (RobotAnimationState != RobotJumpLast) && (RobotAnimationState != RobotJumpFreeze)) || (goodguyframe == monstframe))
	{
		targetframe = goodguyframe;
		camstuff->method = SLUGDRIFT;
		RLFrameAddChild(goodguyframe, camstuff->target);
      if (goodguyframe == monstframe)
		   RLFrameSetPosition(camstuff->target, goodguyframe, RLVal(0), RLVal(0), RLVal(0));
		RLFrameSetOrientation(camstuff->target, goodguyframe, RLVal(0), RLVal(0), RLVal(1), 
			                                                  RLVal(0), RLVal(1), RLVal(0));
	}
}
// **************************************************************************
// Name:			    camera_humaneye
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.6
//
// Description:		Function for movement method HUMANEYE.  Slows the 
//                  velocity of the camera to a stop and drops it
//                  to the landscape.  The camera continues to look
//                  at the targetframe.
//
// Arguments:		Caminfo* camstuff:  (IN) pointer to camera data structure
//                  RLVector* camplace:  (IN) pointer to vector of the 
//                            location of the camera in world coordinates.
//                  RLValue groundheight:  (IN) height of the landscape 
//                            directly under the camera
//
// Return:			None.
//
// Side Effects:	Sets velocity of camera frame.
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


void camera_humaneye(Caminfo* camstuff, RLVector *camplace, RLValue groundheight)
{
/*
	RLVector Robotpos, Robotup, Robotpoint;
	
	RLFrameSetVelocity(Wcamera, Wscene,	RLVal(0.0), RLVal(0.0), RLVal(0.0));
	RLFrameGetOrientation(targetframe, Wscene, &Robotpoint, &Robotup);
	RLFrameGetPosition(targetframe, Wscene, &Robotpos);

	camplace->x = Robotpos.x - 5*Robotpoint.x;
	camplace->z = Robotpos.z - 5*Robotpoint.z;
	camplace->y = MAX(sealevel, SpuddeMapHeight2(camplace->x, camplace->z)) + GROUNDCLEARANCE;

	RLFrameSetPosition(Wcamera, Wscene, camplace->x, camplace->y, camplace->z);
	camstuff->method = HOLD;
*/
	RLVector oldvel;

	RLFrameGetVelocity(Wcamera, camstuff->target, &oldvel);
	
	// scale velocity down by a factor of 8
	RLFrameSetVelocity(Wcamera, camstuff->target,
	    DiffFrame * (oldvel.x) / 8,
	    DiffFrame * ((oldvel.y) /32) + RLMultiply((groundheight + RLVal(0.375) - camplace->y ), RLMultiply(DiffFrame, RLVal(0.1))),
	    DiffFrame * (oldvel.z) / 8);

}

// **************************************************************************
// Name:			    camera_watchmelt
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.6
//
// Description:		Obsolete function for obsolete movement method WATCHMELT.  
//                  Moves the camera instantly to a point beyond the monster, 
//                  looking back toward the Robot, so the monster would melt
//                  in the foreground and the Robot would do its glory 
//                  animation in the background.  The camera velocity is set
//                  to zero.
//
// Arguments:		Caminfo* camstuff:  (IN) pointer to camera data structure
//                  RLVector* camplace:  (IN) pointer to vector of the 
//                            location of the camera in world coordinates.
//                  RLValue groundheight:  (IN) height of the landscape 
//                            directly under the camera
//
// Return:		    None.
//
// Side Effects:	Sets velocity of camera frame.  Changes the position of
//                  the camera frame.
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


void camera_watchmelt(Caminfo* camstuff, RLVector *camplace, RLValue groundheight)
{
	RLVector chrsep;
	
	/*
	if (MnstLife == 0) {
		if (submonster < 2) {
			//if (MonsterAnimationState == MonsterDontGetBackUp2) KillSubMonster();
			return;
		}
		else MeltAMonster();
	}

    if (MnstLife) return;
	*/
	//MeltAMonster();
    
    
    // get separation vector of two players
    RLFrameGetPosition(badguyframe, goodguyframe, &chrsep);
    
    // sets camera just past the monster, so the monster is melting in
    // the foreground and the Robot is taunting in the background
	camplace->x = RLMultiply(RLVal(1.4), chrsep.x) - RLMultiply(RLVal(0.15), chrsep.z);
	camplace->z = RLMultiply(RLVal(1.4), chrsep.z) + RLMultiply(RLVal(0.15), chrsep.x);

		// convert from target coord system to world coord system
	RLFrameTransform(goodguyframe, (camplace), (camplace));
	  // set camera altitude to GROUNDCLEARANCE units above the landscape
	camplace->y = MAX(SpuddeMapHeight2(camplace->x, camplace->z), sealevel) + GROUNDCLEARANCE;
    
    // set velocity to 0 and watch the melt
	RLFrameSetVelocity(Wcamera, Wscene,	RLVal(0.0), RLVal(0.0), RLVal(0.0));
	RLFrameSetPosition(Wcamera, Wscene, camplace->x, camplace->y, camplace->z);

		//if ((countdown > 100) || (countdown < 0)) countdown = 100;
		//countdown--;
		//if (countdown == 0) {
		//	NextLevel=1;
			//if (level!=0) { 
			//	if (MnstLife == 0) {
			//		level++;
			//		submonster = 0;
			//	} 
			//	if (RobotLife==0)
			//		GameStates.IsRobotDead[GameStates.CurrentRobot] = 1;
			//} else level++;
	//	}
}

// **************************************************************************
// Name:			    CountBuildings
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.6
//
// Description:		Finds the number of buildings in a square defined by a 
//                  center and a radius.
//
// Arguments:		RLVector center:  (IN) Vector of the center of the square
//                           to check for buildings
//                  RLValue radius:  (IN) Radius of the square to check for
//                           buildings.
//
// Return:		    int:  number of buildings in square
//
// Side Effects:	None.
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


int CountBuildings(RLVector center, RLValue radius)
{
	visible_buildings Nearby;  // Structure of Nearby Buildings.
    
    // fills up function Nearby with count info. In building sub-system 
	GetBuildingsInArea(&Nearby, 
		               center.x - radius, 
					   center.z - radius, 
					   center.x + radius, 
					   center.z + radius);
	
	return(Nearby.count);
}

// **************************************************************************
// Name:			    GetAntiBuildingForce
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.6
//
// Description:		Finds the force necessary to push the camera away from 
//                  nearby buildings, allowing the camera to move through
//                  city areas without moving inside buildings.  For each
//                  nearby building, the distance from the nearest wall to
//                  the camera is found, and the force is inversely 
//                  proportional to the the square of that distance.
//
// Arguments:		RLVector watchy:  (IN) Vector to the location of the 
//                           camera in world coordinates.
//                  RLVector* force:  (OUT) Vector of the force necessary to 
//                           push the camera away from nearby buildings.
//
// Return:			int:  number of buildings near camera
//
// Side Effects:	None.
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


int GetAntiBuildingForce(RLVector watchy, RLVector* force)
{
	visible_buildings Nearby;  // Structure of Nearby Buildings.
	int i;
	RLVector bldgspot, oneforce; 
	RLVector separation, proximity, direction;
	// separation is the vector from watchy to the building's center
	//
	// direction is the vector along which the force will be applied 
	// (generally from watchy to the nearest edge of a building)
	//
	// proximity is the vector that determines the distance to be fed
	// into the inverse square law to determine the 'oomph' of the
	// force.                             
	
	RLValue dist2, oomph, padding = PADDING;

	force->x = force->y = force->z = RLVal(0.0);

	// fill up Nearby.count
	GetBuildingsInArea(&Nearby, 
		               watchy.x - padding, 
					   watchy.z - padding, 
					   watchy.x + padding, 
					   watchy.z + padding);
	
	for (i = 0; i < Nearby.count; i++)
	{
		// set forces to null
		oneforce.x = oneforce.y = oneforce.z = RLVal(0.0);
		
		// get position of the building
		RLFrameGetPosition(Nearby.building_ptr[i]->rlframe, Wscene, &bldgspot);
		
		//vector from camera to building center
		separation.x = watchy.x - (Nearby.building_ptr[i]->x_world - RLVal(LANDXCENTER));
		separation.y = watchy.y - SpuddeMapHeight2(Nearby.building_ptr[i]->x_world - RLVal(LANDXCENTER), Nearby.building_ptr[i]->z_world - RLVal(LANDZCENTER));
		separation.z = watchy.z - (Nearby.building_ptr[i]->z_world - RLVal(LANDZCENTER));
		
		
		if (separation.y < RLVal(Nearby.building_ptr[i]->scale + 1.0)) 
		{
			
			// below the top of the building
			direction.y = separation.y = proximity.y = RLVal(0.0);
			
			if ((fabs(separation.x) <= RLVal(BUILDINGLIMIT)) && (fabs(separation.z) > RLVal(BUILDINGLIMIT))) 
			{
			
				// outside building, off from z direction
				direction.x = RLVal(0.0);
				if (separation.z > 0) 
				{
					direction.z = separation.z - RLVal(BUILDINGSIZE);
				}
				else
				{
					direction.z = separation.z + RLVal(BUILDINGSIZE);
				}
			
				// direction is vector from wall to watchy
				proximity.x = direction.x;
				proximity.z = direction.z;
				proximity.y = separation.y;
			}
			
			if ((fabs(separation.x) > RLVal(BUILDINGLIMIT)) && (fabs(separation.z) <= RLVal(BUILDINGLIMIT))) 
			{
			
				// outside building, off from x direction
				direction.z = RLVal(0.0);
				if (separation.x > 0) 
				{
					direction.x = separation.x - RLVal(BUILDINGSIZE);
				}
				else
				{
					direction.x = separation.x + RLVal(BUILDINGSIZE);
				}
			
				// direction is vector from wall to watchy
				proximity.x = direction.x;
				proximity.z = direction.z;
				proximity.y = separation.y;
			}
			
			if ((fabs(separation.x) > RLVal(BUILDINGLIMIT)) && (fabs(separation.z) > RLVal(BUILDINGLIMIT))) 
			{
			
				// outside building, off from corner
				if (separation.x > 0) 
				{
					direction.x = separation.x - RLVal(BUILDINGSIZE);
				}
				else
				{
					direction.x = separation.x + RLVal(BUILDINGSIZE);
				}
				if (separation.z > 0) 
				{
					direction.z = separation.z - RLVal(BUILDINGSIZE);
				}
				else
				{
					direction.z = separation.z + RLVal(BUILDINGSIZE);
				}
			
				// direction is vector from corner to watchy
				proximity.x = direction.x;
				proximity.z = direction.z;
				proximity.y = separation.y;
			}
			
			if ((fabs(separation.x) <= RLVal(BUILDINGLIMIT)) && (fabs(separation.z) <= RLVal(BUILDINGLIMIT))) 
			{
			
				// inside building!!!
				if (separation.y < RLVal(Nearby.building_ptr[i]->scale + 1.0)) 
				{
					proximity.x = direction.x = separation.x / RLVal(BUILDINGSIZE * 2);
					proximity.z = direction.z = separation.z / RLVal(BUILDINGSIZE * 2);
					proximity.y = direction.y = RLVal(0.0); //(RLVal(Nearby.building_ptr[i]->scale) - separation.y)/RLVal(BUILDINGSIZE*2);
					// direction is vector from center to watchy
				
				} 
				else 
				{
					// should never reach this code
					direction.x = separation.x;
					direction.z = separation.z;
				
					//direction.y = separation.y;
					if (separation.x > 0) 
					{
						proximity.x = RLVal(BUILDINGSIZE) - separation.x;
					}
					else
					{
						proximity.x = -RLVal(BUILDINGSIZE) - separation.x;
					}
					if (separation.z > 0) 
					{
						proximity.z = RLVal(BUILDINGSIZE) - separation.z;
					}
					else
					{
						proximity.z = -RLVal(BUILDINGSIZE) - separation.z;
					}
					//proximity.x = direction.x / RLVal(5.0);
					//proximity.z = direction.z / RLVal(5.0);
					/*
					direction.x = direction.z = proximity.x = proximity.z = RLVal(0.0);
					direction.z = proximity.z = (separation.y - RLVal(Nearby.building_ptr[i]->scale));
					*/
				}
			}
		} 
		else 
		{
			// over top of building
			proximity.x = direction.x = separation.x / RLVal(BUILDINGSIZE * 2);
			proximity.z = direction.z = separation.z / RLVal(BUILDINGSIZE * 2);
			direction.y = (separation.y - RLVal(Nearby.building_ptr[i]->scale)) / RLVal(BUILDINGSIZE * 2);
			
			// direction is vector from center to watchy
			//proximity.y = RLVal(0.0);
			proximity.y = RLDivide(direction.y, RLVal(2));
		}   
		
		// calculate the forces
		RLVectorNormalise(&direction);
		dist2 = RLVectorDotProduct(&proximity, &proximity);
	    if (dist2) 
		{
	    	oomph = RLDivide(RLMultiply3(DiffFrame,RLVal(0.001),padding), dist2);
	    	RLVectorScale(&oneforce, &direction, oomph);
	    	
	    	// increment the forces from each building
			force->x += oneforce.x;
			force->y += RLMultiply3(RLVal(Nearby.building_ptr[i]->scale), RLVal(0.5), (oneforce.y));
			force->z += oneforce.z;
		}
	}
	return(Nearby.count);
}

// **************************************************************************
// Name:			    GetAntiBuildingForceCircle
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.6
//
// Description:		Finds the force necessary to push the camera away from 
//                  nearby buildings, allowing the camera to move through
//                  city areas without moving inside buildings.  For each
//                  nearby building, the distance from the center to
//                  the camera is found, and the force is inversely 
//                  proportional to the the square of that distance.
//                  Similar to GetAntiBuildingForce, except it is used 
//                  when the camera is using CIRCLE movement method, 
//                  the check for building proximity is less rigorous, 
//                  and the force pushes the camera higher over the
//                  top of buildings.
//
// Arguments:		RLVector watchy:  (IN) Vector to the location of the 
//                           camera in world coordinates.
//                  RLVector* force:  (OUT) Vector of the force necessary to 
//                           push the camera away from nearby buildings.
//
// Return:			int:  number of buildings near camera
//
// Side Effects:	None.
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

int GetAntiBuildingForceCircle(RLVector watchy, RLVector* force)
{
	visible_buildings Nearby;  // Structure of Nearby Buildings.
	int i;
	RLVector bldgspot, oneforce; 
	RLVector separation, proximity, direction;
	// separation is the vector from watchy to the building's center
	//
	// direction is the vector along which the force will be applied 
	// (generally from watchy to the nearest edge of a building)
	//
	// proximity is the vector that determines the distance to be fed
	// into the inverse square law to determine the 'oomph' of the
	// force.                             
			
	RLValue dist2, oomph, padding = RLVal(25.0);

	force->x = force->y = force->z = RLVal(0.0);
	direction.x = direction.z = RLVal(0.0);
	direction.y = RLVal(1.0);
   
	GetBuildingsInArea(&Nearby, 
		               watchy.x - padding, 
					   watchy.z - padding, 
					   watchy.x + padding, 
					   watchy.z + padding);
	
	for (i = 0; i < Nearby.count; i++)
	{
		oneforce.x = oneforce.y = oneforce.z = RLVal(0.0);
		
		// distance from camera to the center of the buildings
		RLFrameGetPosition(Nearby.building_ptr[i]->rlframe, Wscene, &bldgspot);
		separation.x = watchy.x - (Nearby.building_ptr[i]->x_world - RLVal(LANDXCENTER));
		separation.y = watchy.y - SpuddeMapHeight2(Nearby.building_ptr[i]->x_world - RLVal(LANDXCENTER), Nearby.building_ptr[i]->z_world - RLVal(LANDZCENTER));
		separation.z = watchy.z - (Nearby.building_ptr[i]->z_world - RLVal(LANDZCENTER));
		
		// (separation.y < RLVal(Nearby.building_ptr[i]->scale + 3.0)) {
			proximity.x = separation.x / RLVal(BUILDINGSIZE * 2);
			proximity.z = separation.z / RLVal(BUILDINGSIZE * 2);
			proximity.y = separation.y;
		//} else {
		//	// over top of building
		//	proximity.x = separation.x/RLVal(BUILDINGSIZE*2);
		//	proximity.z = separation.z/RLVal(BUILDINGSIZE*2);
		//	proximity.y = (separation.y - RLVal(Nearby.building_ptr[i]->scale))/RLVal(BUILDINGSIZE/2);
		//	proximity.y = RLVal(0.0);
		//}         
		
		// calculate the forces
		dist2 = RLVectorDotProduct(&proximity, &proximity);
	    if (dist2) 
		{
	    	oomph = RLDivide(RLMultiply3(DiffFrame,RLVal(0.001),padding), dist2);
	    	RLVectorScale(&oneforce, &direction, oomph);
	    	
	    	// increment the forces from each building
			force->x += oneforce.x;
			force->y += RLMultiply3(RLVal(Nearby.building_ptr[i]->scale), RLVal(0.75), (oneforce.y));
			force->z += oneforce.z;
		}
	}
	return(Nearby.count);
}

// **************************************************************************
// Name:			    SetCameraTarget
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.6
//
// Description:		Assigns a new RLFrame to the targetframe, allowing the 
//                  camera to use the same methods to look at any
//                  character or object in the game.
//
// Arguments:		Caminfo* camstuff:  (IN) pointer to camera data structure
//                  RLFrame targframe:  (IN) new RLFrame for the camera to
//                          look at.
//
// Return:			None.
//
// Side Effects:	Assigns a new value to the global variable targetframe.
//                  Adds the new targetframe as a child of the target member
//                  of the camera info structure.  Sets the orientation of
//                  the target member of the camera info structure.
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


void SetCameraTarget(Caminfo* camstuff, RLFrame targframe)
{
	targetframe = targframe;
	RLFrameAddChild(targetframe, camstuff->target);
	RLFrameSetOrientation(camstuff->target, targetframe, RLVal(0), RLVal(0), RLVal(1), 
		                                                 RLVal(0), RLVal(1), RLVal(0));
}

// **************************************************************************
// Name:			    ResetCameraTarget
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.4
//
// Description:		Assigns the value of goodguyframe to the targetframe, 
//                  resetting the camera to look at the character currently
//                  being played by the user (Robot by default, monster if
//                  in PlayAsMonster mode).
//
// Arguments:		Caminfo* camstuff:  (IN) pointer to camera data structure
//
// Return:			None.
//
// Side Effects:	Assigns a new value to the global variable targetframe.
//                  Adds the new targetframe as a child of the target member
//                  of the camera info structure.  Sets the orientation of
//                  the target member of the camera info structure.
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

void ResetCameraTarget(Caminfo* camstuff)
{
	targetframe = goodguyframe;
	RLFrameAddChild(goodguyframe, camstuff->target);
	RLFrameSetOrientation(camstuff->target, goodguyframe, RLVal(0), RLVal(0), RLVal(1), 
		                                                  RLVal(0), RLVal(1), RLVal(0));
}

// **************************************************************************
// Name:			    EaseInto
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.6
//
// Description:		Interpolates between two vectors to provide smoothing of
//                  velocity changes.  Final velocity is a weighted sum of
//                  the old velocity and the new velocity, weighted by a
//                  scalar value.  
//
// Arguments:		RLVector* final:  (OUT) pointer to result vector.
//                  RLVector* original:  (IN) pointer to vector of old velocity.
//                  RLVector* extra:  (IN) pointer to vector of new velocity.
//                  RLValue amount:  (IN) scalar value that is the fraction of
//                          new velocity.
//
// Return:			None.
//
// Side Effects:	None.
//
// Notes:			Amount is greater if In3DMovie is true to speed up velocity
//                  changes when in end-of-level sequences.
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

void EaseInto(RLVector* final, RLVector* original, RLVector* extra, RLValue amount)
{
//    extern BOOL In3DMovie;

    amount *= RLDivide(DiffFrame, (GameStates.Is3DMovie ? RLVal(8.0) : RLVal(2.5)));

    final->x = RLMultiply(original->x, (RLVal(1) - amount)) + RLMultiply(extra->x, amount);
    final->y = RLMultiply(original->y, (RLVal(1) - amount)) + RLMultiply(extra->y, amount);
    final->z = RLMultiply(original->z, (RLVal(1) - amount)) + RLMultiply(extra->z, amount);
}


// **************************************************************************
// Name:			    AutoCameras
//
// Author:			  Jeremiah "Spudde" Childs
// 
// Date:			    1996.6.6
//
// Description:		Controls camera modes when in the autodemo.
//
// Arguments:		Caminfo* camstuff:  (OUT) pointer to camera data structure
//
// Return:			None.
//
// Side Effects:	Changes the global variables autocountdown and cameramode.
//                  May change the targetframe.  Prints camera mode 
//                  descriptions in scrolling text on screen.
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
 
void AutoCameras(Caminfo* camerastuff)
{
	extern int Vmode;

	autocountdown -= DiffFrame;			// decrement timer
	if (autocountdown < RLVal(0))
	{
		cameramode = (cameramode + 1) % 10;	// switch to next camera mode
		autocountdown = RLVal(10 * 30);	// set countdown timer to 10 seconds

		switch (cameramode)  
		{
		    case 1:
		        camerastuff->method = POV;
		        YBSetSubTitle1(Vmode, "WATCHY FIRST-PERSON", RGB(0, 255, 0));
				ResetCameraTarget(camerastuff);
		        break;
		    case 0:
		    case 2:
		        camerastuff->method = SLUGDRIFT;
			    camerastuff->zone = 2;
		        YBSetSubTitle1(Vmode, "WATCHY OVER THE SHOULDER", RGB(0, 255, 0));
			    ResetCameraTarget(camerastuff);
		        break;
		    case 3:
		        camerastuff->method = SLUGDRIFT;
			    camerastuff->zone = 4;
		        YBSetSubTitle1(Vmode, "WATCHY HIGH OVER THE SHOULDER", RGB(0, 255, 0));
			    ResetCameraTarget(camerastuff);
		        break;
		    case 4:
		        camerastuff->method = SLUGDRIFT;
			    camerastuff->zone = 7;
		        YBSetSubTitle1(Vmode, "WATCHY LEFT SIDE", RGB(0, 255, 0));
			    ResetCameraTarget(camerastuff);
		        break;
		    case 5:
		        camerastuff->method = SLUGDRIFT;
			    camerastuff->zone = 8;
		        YBSetSubTitle1(Vmode, "WATCHY RIGHT SIDE", RGB(0, 255, 0));
			    ResetCameraTarget(camerastuff);
		        break;
			case 6:
		        camerastuff->method = SLUGDRIFT;
			    camerastuff->zone = 3;
		        YBSetSubTitle1(Vmode, "WATCHY REVERSE VIEW", RGB(0, 255, 0));
			    ResetCameraTarget(camerastuff);
		        break;
			case 7:
		        camerastuff->method = SLUGDRIFT;
			    camerastuff->zone = 5;
		        YBSetSubTitle1(Vmode, "WATCHY OVERHEAD", RGB(0, 255, 0));
			    ResetCameraTarget(camerastuff);
		        break;
			case 8:
		        camerastuff->method = SLUGDRIFT;
			    camerastuff->zone = 6;
		        YBSetSubTitle1(Vmode, "WATCHY AERIAL", RGB(0, 255, 0));
			    ResetCameraTarget(camerastuff);
		        break;
		    case 9:
				{
					extern RLFrame badguyframe;

                    camerastuff->method = SLUGDRIFT;
					camerastuff->zone = 2;
					SetCameraTarget(camerastuff, badguyframe);
                    if (GameStates.CurrentLevel==Trainer) 
					{
						YBSetSubTitle1(Vmode, "WATCHY MONSTER VIEW", RGB(0, 255, 0));
					}
                    break;
				}
		}
	}
}

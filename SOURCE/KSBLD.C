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
File:           KSBLD.C
Author:         Kevin Shapiro
Date:           09/26/95
Version:        version 1.1



************************************************************************
REVISION HISTORY        

Edited By:      Bruce Abe
Edited Date:    10/20/95
Changes:    
            I added a check to see whether or not the building has been
            destroyed in the functions GetBuildingsInArea and 
            update_vis_bldgs.


Edited By:      Bruce Abe
Edited Date:    10/17/95
Changes:    
            changed version number from 1.0 to 1.1.
            The building initialization code now sets the bounding box
            of each building.  update_vis_bldgs now checks against the 
            bounding box rather than the center of the building.  There 
            is also a function GetBuildingsInArea which will be used for
            all kinds of building collision detection.  check_vis_bldgs 
            is now inside an ifdef, so if we don't want to print out 
            all that information each time through a level, we don't 
            have to.

Edited By:      Bruce Abe
Edited Date:    10/13/95
Changes:
            removed the call to s_update_vis_bldgs, and replaced with a 
            debugged version of update_vis_bldgs.  We no longer go through
            the array in the wrong order, and the code properly checks
            for buildings that aren't centered inside an area,
            but that overlap the area.


Edited By:      Bo Yuan
Edited Date:    10/02/95
Changes:
				added a condition to the creation of the buildings for 
				a defined level.  If that level has not been played 
				before, create tempframe, otherwise, just use the old
				ones.  This change was in function Building_Init.
				This is for memory safty purpose.

Edited By:      Bo Yuan
Edited Date:    09/28/95
Changes:
				changed function "Building_Init", input Level as integer
				than as char *.

***********************************************************************/

// Adding by Liu Song
#include "rl2d3d.h"
#define __RL_H__
#define __IMODE_H__
#include "mybuild.h"
#include "byglobal.h"
#include "viewer.h"

extern LPDIRECT3DRM lpD3DRM;
extern LPDIRECTDRAWCLIPPER lpDDClipper;
extern BOOL bQuit;
EbInfo ebInfo[7];

//#define printouts
#ifdef printouts
#include <stdio.h>
#endif
//#ifndef _KSBLDC_
//#define _KSBLDC_

//#pragma warning( disable : 4244)
#define BOXX_ADJUST 10
#define BOXZ_ADJUST 10

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// ********************************************
//
//  Include Debugger Defines.
//
// ********************************************
//
#define KSDEBUG 0


// ********************************************
//
//  Include Header Files
//
// ********************************************
//
#include "building.h"
#include "gosys.h"
#include "global.h"
// ********************************************
//
//  Define Needed Externals
//
// ********************************************
//


// ********************************************
//
//  Define Needed Global Variables
//
// ********************************************
//
char *g_Lvl="LM";
static int KS_status = 0;


#ifndef LSMASK
extern cGlobalstype cGlobals;           // Bo's Structure for min & max (X,Z)
#endif LSMASK
extern RLIMTriangle *filltriangles(int building_num);   // Bo's Function to Init a Triangle List Buffer and Return Address.
triangle_list   lvl_tris;               // Number of Slots for Triangle Lists.

extern RLDevice dev;
extern RLFrame behindthescene;

extern long int Population;
extern long int PrePopulation;


building_area *which1_bldg, *which2_bldg;   // Pointer to level Structure.
visible_buildings vis_bldgs;                // Structure of Visible Buildings.

//
short level_flag[7] =
{
	0, 0, 0, 0, 0, 0, 0
};

short bldg_strngth_mltplr[7] = 
{
   10, 10, 10, 10, 10, 10, 10
};

// ********************************************
//
//  Define Needed Routines
//
// ********************************************
//

void Building_Init(int Level, LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
           LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera)
{
    int indx1;
    int indx3;           // Counters.
    int counter1;
    int temp_bldg_id;
    int max_rsrcs;
    lvl_bldg_rsrcs *lvls_rsrcs;                 // Define Pointer to Bo's Returned Info.

    RLValue tempx, tempy, tempz;
    RLFrame tempframe;

   // Set building count to 0 to keep from removing nonexistant buildings.
   vis_bldgs.count = 0;


//  Set level to the Proper Number & Store Pointer to Level Struct.
//	Level = 0;
    if ((Level==0)){                // Level Mojave
//        g_level=Level;
        which1_bldg= &bldg_lvlLX[0][0];     // Point to Proper Building Struct.
    }else if (Level==1){             // Level Rocky Mountains
  //          g_level=Level;
            which1_bldg= &bldg_lvlLM[0][0];               // Point to Proper Building Struct.
    }else if (Level==2){             // Level Rocky Mountains
    //        g_level=Level;
            which1_bldg= &bldg_lvlLR[0][0];               // Point to Proper Building Struct.
        }else if (Level==3){         // Level Hawaii
      //          g_level=Level;
                which1_bldg= &bldg_lvlLH[0][0];           // Point to Proper Building Struct.
            }else if (Level==4){     // Level San Francisco
        //            g_level=Level;
                    which1_bldg= &bldg_lvlLS[0][0];       // Point to Proper Building Struct.
                }else if (Level==5){ // Level New York
          //              g_level=Level;
                        which1_bldg= &bldg_lvlLN[0][0];   // Point to Proper Building Struct.
                    }else{
            //            g_level=Level;              // Level Tokyo.
                        which1_bldg= &bldg_lvlLT[0][0];       // Point to Proper Building Struct.
                    }

	if (!level_flag[GameStates.CurrentLevel]) PrePopulation = 0;

//  Get The Resources from the CD.
	lvls_rsrcs = BuildingInfo();
#ifdef LSOUT
	InfoOutput();
#endif LSOUT


//  Assign Resource info to Every Building on Level.
    which2_bldg = which1_bldg;

    for (indx1=0; (indx1 < ((WORLD_SIZE>>RES_SHFT_DIVISOR)*(WORLD_SIZE>>RES_SHFT_DIVISOR))); indx1++, which2_bldg++)
    {
        counter1 = which2_bldg->count;
        for (indx3 = 0 ; (indx3 < counter1); indx3++)
        {
            temp_bldg_id = which2_bldg->building_ptr[indx3].building_num;
            for (max_rsrcs = 0; 
                 ((max_rsrcs < lvls_rsrcs->count)&&
                 (temp_bldg_id != lvls_rsrcs->bldg_rsrcs[max_rsrcs].bldg_id)); 
                 max_rsrcs++)
            {
            ;
            }
            // Set Not Visible at Startup.
            which2_bldg->building_ptr[indx3].visible = 0;
            // Set Not Damaged at Startup.
			if (!level_flag[GameStates.CurrentLevel]) {
				which2_bldg->building_ptr[indx3].cur_damage = 0;
				PrePopulation += which2_bldg->building_ptr[indx3].power_mon_amount * 1000;
			}
				which2_bldg->building_ptr[indx3].max_damage *= bldg_strngth_mltplr[GameStates.CurrentLevel];
            // Assign The Display List Pointer into the Building Structure.
            which2_bldg->building_ptr[indx3].displist = lvls_rsrcs->bldg_rsrcs[max_rsrcs].displist;

             // RLDDRAW_BLIT
            // Get a NEW RLFrame for the Building Structure.
            //which2_bldg->building_ptr[indx3].rlframe = RLCreateFrame(behindthescene);
//            if (!level_flag[g_level]) {
            	tempframe = RLCreateFrame(behindthescene);
               which2_bldg->building_ptr[indx3].rlframe = tempframe;
//			}
			tempframe = which2_bldg->building_ptr[indx3].rlframe;
			RLFrameAddScale(tempframe,RLCombineReplace, RLVal(1), RLVal(1), RLVal(1));

         tempx = (which2_bldg->building_ptr[indx3].x_world-RLVal(LANDXCENTER));
         tempz = (which2_bldg->building_ptr[indx3].z_world-RLVal(LANDZCENTER));
		   tempy = RLVal(which2_bldg->building_ptr[indx3].y_world);
         tempy = (RLVal(tempy)/landscale);
		tempy = MapHeight(RLInt(tempx), RLInt(tempz)); 
         RLFrameSetPosition(tempframe, scene, tempx, tempy, tempz);
         // See if Generic Building or Unique.
         if (which2_bldg->building_ptr[indx3].building_num == -1)
         {
             // Set Scale if building is Generic
             RLFrameAddScale(tempframe,RLCombineBefore, RLVal(1), RLVal(which2_bldg->building_ptr[indx3].scale), RLVal(1));
             which2_bldg->building_ptr[indx3].trilist = NULL;
             which2_bldg->building_ptr[indx3].building.max.y=tempy + RLVal(which2_bldg->building_ptr[indx3].scale);
             which2_bldg->building_ptr[indx3].building.min.y=tempy;
             which2_bldg->building_ptr[indx3].building.min.x=tempx-RLVal(3.5);
             which2_bldg->building_ptr[indx3].building.max.x=tempx+RLVal(3.5);
             which2_bldg->building_ptr[indx3].building.min.z=tempz-RLVal(3.5);
             which2_bldg->building_ptr[indx3].building.max.z=tempz+RLVal(3.5);
         }
         else//building is specific.
         {
             // Get and Assign a New Triangle List for the Building Structure.
             which2_bldg->building_ptr[indx3].trilist = filltriangles(which2_bldg->building_ptr[indx3].building_num);
             //need to get the bounding box, but it's going to be 
             //a different operation when Spudde is making all the 
             //immediate mode meshes anyways.
			 GetSpecificBox(which2_bldg->building_ptr[indx3].building_num, &which2_bldg->building_ptr[indx3].building);
             which2_bldg->building_ptr[indx3].trilist = NULL;
             which2_bldg->building_ptr[indx3].building.max.y/*+*/=tempy;
             which2_bldg->building_ptr[indx3].building.min.y/*+*/=tempy;
             which2_bldg->building_ptr[indx3].building.min.x/*+*/=tempx;
             which2_bldg->building_ptr[indx3].building.max.x/*+*/=tempx;
             which2_bldg->building_ptr[indx3].building.min.z/*+*/=tempz;
             which2_bldg->building_ptr[indx3].building.max.z/*+*/=tempz;
         }
        }
    }
	if (!level_flag[GameStates.CurrentLevel]) Population = PrePopulation;
	KS_status = 1;
	if (GameStates.CurrentLevel) 
		for (indx1=1;indx1<7;indx1++)
			level_flag[indx1] = (indx1==GameStates.CurrentLevel);

   bldg_strngth_mltplr[GameStates.CurrentLevel]=1;
	BuildTestScene(dev, view, scene, camera);
#ifdef LSOUT
	InfoOutput();
#endif LSOUT
}


void GetBuildingsInArea(visible_buildings *vis_bldgs, RLValue minx, RLValue minz, RLValue maxx, RLValue maxz)
{
   building_area *which2_bldg;   // Pointer to level Structure.
   int temp_minx, temp_minz, temp_maxx, temp_maxz;
   int area_minx, area_minz, area_maxx, area_maxz;
   int indx1, indx2, indx3;
   RLValue MaxBuildingX, MaxBuildingZ,MinBuildingX,MinBuildingZ;
   int counter2, counter3;
	if (!KS_status) return;

//minx,minz,maxx.maxz are the values we're going to check the
//building's bounding box against.


//temp* is expanded by boxadjust, which represents half the maximum 
//size of the buildings in the world.  This is used to determine which
//sections of the world we search, and in case a building is large enough
//that it's on the edge of one section and overlaps into another section,
//the adjustment makes sure we get it from either section.
	temp_minx = RLInt(MAX((minx+LANDXCENTER -BOXX_ADJUST), 0));
   temp_minz = RLInt(MAX((minz+LANDZCENTER -BOXZ_ADJUST), 0));
	temp_maxx = RLInt(MIN((maxx+LANDXCENTER +BOXX_ADJUST),LANDXSIZE-1));
	temp_maxz = RLInt(MIN((maxz+LANDZCENTER +BOXZ_ADJUST),LANDZSIZE-1));


//  Convert the current visible co-ordinates to Area Sections.
   area_minx = (temp_minx >> RES_SHFT_DIVISOR);    // Get Min X Section #.
   area_maxx = (temp_maxx >> RES_SHFT_DIVISOR);    // Get Max X Section #.
   area_minz = (temp_minz >> RES_SHFT_DIVISOR);    // Get Min Z Section #.
   area_maxz = (temp_maxz >> RES_SHFT_DIVISOR);    // Get Max Z Section #.

   counter3 = 0;           // Number of buildings
   which2_bldg = (which1_bldg
                  +((area_minx*(WORLD_SIZE>>RES_SHFT_DIVISOR))
                  +area_minz));
   for (indx2 = area_minx; (indx2 <= area_maxx); indx2++)
   {
      for (indx1 = area_minz; (indx1 <= area_maxz); indx1++)
      {
         counter2 = which2_bldg->count;
         for (indx3 = 0 ; (indx3 < counter2); indx3++)
         {
            if(which2_bldg->building_ptr[indx3].cur_damage < which2_bldg->building_ptr[indx3].max_damage)
            //check to see if the building is still standing, or has been destroyed.
            {
               MaxBuildingX = (which2_bldg->building_ptr[indx3].building.max.x);
               MaxBuildingZ = (which2_bldg->building_ptr[indx3].building.max.z);
               MinBuildingX = (which2_bldg->building_ptr[indx3].building.min.x);
               MinBuildingZ = (which2_bldg->building_ptr[indx3].building.min.z);

               if (
                   (minx <= MaxBuildingX) 
                && (maxx >= MinBuildingX) 
                && (minz <= MaxBuildingZ)  
                && (maxz >= MinBuildingZ)
                   )
               {
               //The building is in the specified area.

               //unlike with Kevin's code, there's no difference for
               //collision purposes whether you have a specific or
               //generic building, and we don't have to do all the stuff 
               //that makes the building visible.
                  vis_bldgs->building_ptr[counter3] = &which2_bldg->building_ptr[indx3];  // Addr of Building Structure.
                  counter3 +=1;       // one more building in area.
	         		if (counter3==MAXVISBLDGS ) {
	         			vis_bldgs->count = MAXVISBLDGS;
						return;
					}
               }
            }
         }
         which2_bldg++;
      }
      which2_bldg += ((WORLD_SIZE>>RES_SHFT_DIVISOR)-((area_maxz-area_minz)+1));
   }
   vis_bldgs->count = counter3;         // Total Number of Now Visible Buildings.

}

void update_vis_bldgs(RLFrame scene, int minx, int minz, int maxx, int maxz)
{
    int num_vis;
    int counter1;
    building *tempbuilding;
    RLFrame tempframe;

    int temp_minx, temp_minz, temp_maxx, temp_maxz;
    int area_minx, area_minz, area_maxx, area_maxz;

    int indx1, indx2, indx3;
    RLValue MaxBuildingX, MaxBuildingZ,MinBuildingX,MinBuildingZ;
    int counter2, counter3;
    int counter4;

	// display mission targets on radar.
	for (counter1=0;counter1<6;counter1++) {
		extern visible_buildings missiontarget;
		extern RLFrame Robotframe;
		extern TARGET targets[];
		extern RLFrame goodguyframe;

		RLVector p;
//		extern RLFrame monstframe;



 	    p.x = RLVal(missiontarget.building_ptr[counter1]->x_world-LANDXCENTER);
		p.z = RLVal(missiontarget.building_ptr[counter1]->z_world-LANDZCENTER);
		p.y = RLVal(0);

//		RLFrameInverseTransform(goodguyframe, &(p), &(p));
		RLFrameGetPosition(missiontarget.building_ptr[counter1]->rlframe,goodguyframe,&(p));
//		if (PlayAsMonster)
//		{
//			RLFrameInverseTransform(monstframe, &(p), &(p));
//		}
//		else
//		{
//			RLFrameInverseTransform(Robotframe, &(p), &(p));
//		}

		
		targets[counter1+7].p.x = p.x;
	    targets[counter1+7].p.y = p.y;
	    targets[counter1+7].p.z = p.z;
	    targets[counter1+7].life = (missiontarget.building_ptr[counter1]->cur_damage < missiontarget.building_ptr[counter1]->max_damage);
	    if (counter1<3) targets[counter1+7].type = 3;
		else targets[counter1+7].type = 5;
	}

	if (!KS_status) return;
//  Make all Old visible Buildings No Longer Visible.
    num_vis = vis_bldgs.count;          // Get Number of old Visible Buildings.
    for (counter1=0; (counter1 < num_vis); counter1++)
    {
        tempbuilding = vis_bldgs.building_ptr[counter1];    // Addr of Building Structure.
        tempframe = tempbuilding->rlframe;                  // Addr of buildings RLFrame.
        RLFrameAddChild(behindthescene, tempframe);         // Remove This Frame from render list.
        tempbuilding->visible = 0;      // Say Building No Longer Visible.
        if (tempbuilding->building_num == -1)
        {
            tempbuilding->trilist = NULL;   // Disconnect the Triangle List Buffer.
        }
    }


//  Get The Current Visible Screen Box. (Based on Camera Orientation & Position).

	temp_minx = MAX((minx+XZ_CONVERSION -BOXX_ADJUST), 0);
	temp_minz = MAX((minz+XZ_CONVERSION -BOXZ_ADJUST), 0);
	temp_maxx = MIN((maxx+XZ_CONVERSION +BOXX_ADJUST),WORLD_SIZE-1);
	temp_maxz = MIN((maxz+XZ_CONVERSION +BOXZ_ADJUST),WORLD_SIZE-1);

//  Convert the current visible co-ordinates to Area Sections.
    area_minx = (temp_minx >> RES_SHFT_DIVISOR);    // Get Min X Section #.
    area_maxx = (temp_maxx >> RES_SHFT_DIVISOR);    // Get Max X Section #.
    area_minz = (temp_minz >> RES_SHFT_DIVISOR);    // Get Min Z Section #.
    area_maxz = (temp_maxz >> RES_SHFT_DIVISOR);    // Get Max Z Section #.


//  Add The Visible Buildings to the scene.
    counter3 = 0;           // No Visible Buildings Yet.
    counter4 = 0;           // No Triangle Buffers Assigned Yet.
    which2_bldg = (which1_bldg
                  +((area_minx*(WORLD_SIZE>>RES_SHFT_DIVISOR))
                  +area_minz));
        for (indx2 = area_minx; (indx2 <= area_maxx); indx2++)
        {
    for (indx1 = area_minz; (indx1 <= area_maxz); indx1++)
    {
            counter2 = which2_bldg->count;
            for (indx3 = 0 ; (indx3 < counter2); indx3++)
            {
            //if(which2_bldg->building_ptr[indx3].cur_damage<=which2_bldg->building_ptr[indx3].max_damage)
            //check to see if the building is still standing, or has been destroyed 
            //(if statement commented out because destroyed buildings are still displayed).
            {
                MaxBuildingX = (which2_bldg->building_ptr[indx3].building.max.x);
                MaxBuildingZ = (which2_bldg->building_ptr[indx3].building.max.z);
                MinBuildingX = (which2_bldg->building_ptr[indx3].building.min.x);
                MinBuildingZ = (which2_bldg->building_ptr[indx3].building.min.z);

                if (
                   (minx <= MaxBuildingX) 
                && (maxx >= MinBuildingX) 
                && (minz <= MaxBuildingZ)  
                && (maxz >= MinBuildingZ)
                   )
                {
                    // If this is a GENERIC building.
                    if (which2_bldg->building_ptr[indx3].building_num == -1)
                    {
                        if (counter4 < MAXGENERICBLDGS)
                        {
                            // Assign a Triangle Buffer for this visible building.
                            which2_bldg->building_ptr[indx3].trilist = lvl_tris.bldgs_triangles[counter4].bldg_triangles;
                        }
                        counter4 +=1;       // One More Triangle Buffer Now Assigned.
                    }
					if (((which2_bldg->building_ptr[indx3].building_num == 13) || (which2_bldg->building_ptr[indx3].building_num == 15) || (which2_bldg->building_ptr[indx3].building_num == 20) || 
						 (which2_bldg->building_ptr[indx3].building_num == 66) || (which2_bldg->building_ptr[indx3].building_num == 67) || (which2_bldg->building_ptr[indx3].building_num == 68) || 
						((which2_bldg->building_ptr[indx3].building_num == -1) && (counter4 < MAXGENERICBLDGS)) ))
					{
                    // Assign The Frame and say its visible.
                    tempframe = which2_bldg->building_ptr[indx3].rlframe; // Addr of RLFrame.
                    RLFrameAddChild(scene, tempframe);      // Add This Frame to render list.
                    which2_bldg->building_ptr[indx3].visible = 1;              // Say Building Now Visible.
                    vis_bldgs.building_ptr[counter3] = &which2_bldg->building_ptr[indx3];  // Addr of Building Structure.
                    counter3 +=1;       // One More Building Now Visible.
                	}
                }
            }
            }
            which2_bldg++;
        }
        which2_bldg += ((WORLD_SIZE>>RES_SHFT_DIVISOR)-((area_maxz-area_minz)+1));
    }
    vis_bldgs.count = counter3;         // Total Number of Now Visible Buildings.

#if KSDEBUG
    if (counter4 < MAXGENERICBLDGS)
    {
        lvl_tris.count = counter4;     // Total Number of Triangle Lists Now Being Used.
    }
    else
    {
        lvl_tris.count = MAXGENERICBLDGS;   // Total Number of Triangle Lists Now Being Used.
        printf("\n\nMore Generic Buildings are visible then Triangle List Buffers Availabel.");
        printf("\nYou have tried to assign %d to many.",(counter4-MAXGENERICBLDGS));
        printf("\nThe Screen Box that contains the buildings has the following X & Z co-ordinates.");
        printf("\n==============================================================================");
        printf("\n|                                                                            |");
        printf("\n|     Minimum XZ: = %d,%d              Maximum XZ: = %d,%d                   |",minx, minz,  maxx, maxz);
        printf("\n|                                                                            |");
        printf("\n|----------------------------------------------------------------------------|");
        printf("\n|     XZ1: = %d,%d                       XZ2: = %d,%d                        |",minx, minz, maxx, minz);
        printf("\n|     XZ3: = %d,%d                       XZ4: = %d,%d                        |",minx, maxz, maxx, maxz);
        printf("\n|                                                                            |");
        printf("\n==============================================================================");
        printf("\n\n");
    }
#else
    lvl_tris.count = counter4;     // Total Number of Triangle Lists Now Being Used.
#endif

}

  
void FindOneBuilding(visible_buildings *single_building, int targetbldg)
{
   building_area *which2_bldg;   // Pointer to level Structure.
   int temp_minx, temp_minz, temp_maxx, temp_maxz;
   int area_minx, area_minz, area_maxx, area_maxz;
   int indx1, indx2, indx3;
   int counter2, counter3;
	if (!KS_status) return;

	single_building->count = 0;         // Total Number of Now Visible Buildings.
	if (targetbldg<=0) return;

//temp* is expanded by boxadjust, which represents half the maximum 
//size of the buildings in the world.  This is used to determine which
//sections of the world we search, and in case a building is large enough
//that it's on the edge of one section and overlaps into another section,
//the adjustment makes sure we get it from either section.
	temp_minx = 0;
	temp_minz = 0;
	temp_maxx = LANDXSIZE-1;
	temp_maxz = LANDZSIZE-1;


//  Convert the current visible co-ordinates to Area Sections.
   area_minx = (temp_minx >> RES_SHFT_DIVISOR);    // Get Min X Section #.
   area_maxx = (temp_maxx >> RES_SHFT_DIVISOR);    // Get Max X Section #.
   area_minz = (temp_minz >> RES_SHFT_DIVISOR);    // Get Min Z Section #.
   area_maxz = (temp_maxz >> RES_SHFT_DIVISOR);    // Get Max Z Section #.

   counter3 = 0;           // Number of buildings
   which2_bldg = (which1_bldg
                  +((area_minx*(WORLD_SIZE>>RES_SHFT_DIVISOR))
                  +area_minz));
   for (indx2 = area_minx; (indx2 <= area_maxx); indx2++)
   {
      for (indx1 = area_minz; (indx1 <= area_maxz); indx1++)
      {
         counter2 = which2_bldg->count;
         for (indx3 = 0 ; (indx3 < counter2); indx3++)
         {
            if(which2_bldg->building_ptr[indx3].building_num == targetbldg) {
                single_building->building_ptr[0] = &which2_bldg->building_ptr[indx3];  // Addr of Building Structure.
   				single_building->count = 1;         // Total Number of Now Visible Buildings.
			}
         }
         which2_bldg++;
      }
      which2_bldg += ((WORLD_SIZE>>RES_SHFT_DIVISOR)-((area_maxz-area_minz)+1));
   }
}


void FindSpecificBuildings(visible_buildings *specific_buildings)
{
   building_area *which2_bldg;   // Pointer to level Structure.
   int temp_minx, temp_minz, temp_maxx, temp_maxz;
   int area_minx, area_minz, area_maxx, area_maxz;
   int indx1, indx2, indx3;
   int counter2, counter3;
	if (!KS_status) return;

	specific_buildings->count = 0;         // Total Number of Now Visible Buildings.

//temp* is expanded by boxadjust, which represents half the maximum 
//size of the buildings in the world.  This is used to determine which
//sections of the world we search, and in case a building is large enough
//that it's on the edge of one section and overlaps into another section,
//the adjustment makes sure we get it from either section.
	temp_minx = 0;
	temp_minz = 0;
	temp_maxx = LANDXSIZE-1;
	temp_maxz = LANDZSIZE-1;


//  Convert the current visible co-ordinates to Area Sections.
   area_minx = (temp_minx >> RES_SHFT_DIVISOR);    // Get Min X Section #.
   area_maxx = (temp_maxx >> RES_SHFT_DIVISOR);    // Get Max X Section #.
   area_minz = (temp_minz >> RES_SHFT_DIVISOR);    // Get Min Z Section #.
   area_maxz = (temp_maxz >> RES_SHFT_DIVISOR);    // Get Max Z Section #.

   counter3 = 0;           // Number of buildings
   which2_bldg = (which1_bldg
                  +((area_minx*(WORLD_SIZE>>RES_SHFT_DIVISOR))
                  +area_minz));
   for (indx2 = area_minx; (indx2 <= area_maxx); indx2++)
   {
      for (indx1 = area_minz; (indx1 <= area_maxz); indx1++)
      {
         counter2 = which2_bldg->count;
         for (indx3 = 0 ; (indx3 < counter2); indx3++)
         {
            if(which2_bldg->building_ptr[indx3].building_num == 13) {
                specific_buildings->building_ptr[0] = &which2_bldg->building_ptr[indx3];  // Addr of Building Structure.
   				specific_buildings->count++;         // Total Number of Now Visible Buildings.
			}
            if(which2_bldg->building_ptr[indx3].building_num == 15) {
                specific_buildings->building_ptr[1] = &which2_bldg->building_ptr[indx3];  // Addr of Building Structure.
   				specific_buildings->count++;         // Total Number of Now Visible Buildings.
			}
            if(which2_bldg->building_ptr[indx3].building_num == 20) {
                specific_buildings->building_ptr[2] = &which2_bldg->building_ptr[indx3];  // Addr of Building Structure.
   				specific_buildings->count++;         // Total Number of Now Visible Buildings.
			}
            if(which2_bldg->building_ptr[indx3].building_num == 66) {
                specific_buildings->building_ptr[3] = &which2_bldg->building_ptr[indx3];  // Addr of Building Structure.
   				specific_buildings->count++;         // Total Number of Now Visible Buildings.
			}
            if(which2_bldg->building_ptr[indx3].building_num == 67) {
                specific_buildings->building_ptr[4] = &which2_bldg->building_ptr[indx3];  // Addr of Building Structure.
   				specific_buildings->count++;         // Total Number of Now Visible Buildings.
			}
            if(which2_bldg->building_ptr[indx3].building_num == 68) {
                specific_buildings->building_ptr[5] = &which2_bldg->building_ptr[indx3];  // Addr of Building Structure.
   				specific_buildings->count++;         // Total Number of Now Visible Buildings.
			}
         }
         which2_bldg++;
      }
      which2_bldg += ((WORLD_SIZE>>RES_SHFT_DIVISOR)-((area_maxz-area_minz)+1));
   }
}


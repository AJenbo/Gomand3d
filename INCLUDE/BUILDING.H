// Header file for Building Code Segment
// If this file has already been loaded 
// then don't load the file again.

#ifndef _BUILDING_H_
#define _BUILDING_H_


// ********************************************
//
//  Include Header Files
//
// ********************************************

#include "rl2d3d.h"

#include "landscap.h"

// ********************************************
//
// Define some values to make things easier to
// change later if necessary
//
// ********************************************
#define MAKERLVALUE        1  // RLValue conversion factor.
#define WORLD_SIZE LANDZSIZE	//256  // The World's current Width & Height in Units.
#define RES_SHFT_DIVISOR   4  // Value for dividing the 256 world resolution by Powers of 2.

#define MAXGENERICBLDGS   50  //16  // Maximum Number of Generic Building Triangle Lists.
#define MAXVISBLDGS       100  //25  // Maximum Number of Visible Buildings at 1 time.
#define MAXUNIQUEBLDGS    25  // Maximum Number of Visible Buildings at 1 time.
#define MAXTRIANLGES      40  // Maximum Number of Triangles for each Building.
#define XZ_CONVERSION     LANDZCENTER //127  // Add this value to get working building offsets.

// ********************************************
//
// Define Structures
//
// ********************************************

typedef struct _GDPLIST
{
    D3DTLVERTEX			*dstv;
    D3DTRIANGLE			*trig;
	D3DTEXTUREHANDLE	picture;
    int vc, tc;					//vertex and triangle counts??????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
    RLFrame frame1;
} GDPLIST;
// ********************************************

// ********************************************
//  Trianlge List Arrays for Buildings.
//

typedef struct _triangles_
{
    D3DTRIANGLE *bldg_triangles; // Number of Triangle Lists for Game Level.
}triangles;

typedef struct _triangles_list_
{
// Number of Used Entries.
// Number of Slots for Triangle Lists
	int count;                                  
	triangles   bldgs_triangles[MAXGENERICBLDGS]; 
//D3DTRIANGLE    *bldgs_triangles;           // Number of Slots for Triangle Lists.
}triangle_list;

// ********************************************


// ********************************************
//  Each Building has the information Structure below.
//
typedef struct _building_
{
    short visible;         // Is this Building Currently Visible or Not. (NO==0, YES!=0).
    int building_num;      // Which Building is being placed in the world.
    long scale;         // Scale factor for Generic Buildings.
    float tu;            // Texture Map U-Co-ordinate.
    float tv;            // Texture Map V-Co-ordinate.
    int cur_damage;        // Current Damage of Building.
    int max_damage;        // Maximum Damage this Building Can withstand.
    int power_mon_amount;  // Percentage of Power Monster Gets for Destroying Building.
    int power_Robot_amount; // Percentage of Power Robot Gets for Touching Building.

    long x_world;       // X-World Position of Building
    long z_world;       // Z-World Position of Building
    long dir;           // Direction in Radians that the Building is facing.
    long y_world;       // Y-Altitude of Building After the Altitude is Located.
    RLBox building;        // Min & Max X,Y,Z Values (As RLValues).
    RLFrame rlframe;       // This Buildings RLFrame.
    GDPLIST  *displist;    // Pointer To The Display List.
    D3DTRIANGLE *trilist; // Pointer to the Triangle list of this building.
}building;


typedef struct _building_area_
{
    int count;                  //  The Number of Buildings in that area.
    building *building_ptr;     //  An Array of building Pointers.
}building_area;
// ********************************************

// ********************************************
//  Array of Building ID's and Pointers to Display Lists of Each Resource.
//

typedef struct _bldg_rsrc_
{
    int bldg_id;        // Two Digit ID# of the Building that got Loaded.
    GDPLIST *displist;  // Pointer to Display List of Resource.
}bldg_rsrc;

typedef struct _lvl_bldg_rsrcs_
{
// Number of Buildings That Were Loaded for the Level.
// Pointers to Building Resource Structure
    int count;              
    bldg_rsrc bldg_rsrcs[MAXUNIQUEBLDGS];  

}lvl_bldg_rsrcs;
// ********************************************



// ********************************************
//  Array of Currently Visible Building Structures.
//
typedef struct _visible_buildings_
{
    int count;                              //  Number of Visible Buildings.
    building *building_ptr[MAXVISBLDGS];    //  Pointers to Buildings.

}visible_buildings;
// ********************************************


// ********************************************
//
//  Define ProtoTypes
//
// ********************************************

//void Building_Init(char *g_Lvl);     // g_Lvl is Global String for Game Level.
//void update_vis_bldgs(int minx, int minz, int maxx, int maxz);        // Update visible buildings.
//void Building_Init(char *g_Lvl, RLFrame scene);     // g_Lvl is Global String for Game Level.
//typedef struct _AppInfo AppInfo;
void Building_Init(int Level, LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
           LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera);     // g_Lvl is Global String for Game Level.
void GetBuildingsInArea(visible_buildings *vis_bldgs,//RLFrame scene, 
               RLValue minx, RLValue minz, RLValue maxx, RLValue maxz);
//takes all the buildings in the rectangle from (minx,minz) to (maxx,maxz)
//and returns the values in vis_bldgs, which you have to pass.
             
void update_vis_bldgs(RLFrame scene, int minx, int minz, int maxx, int maxz);        // Update visible buildings.
lvl_bldg_rsrcs *load_bldgs(RLDevice dev, int level_num);
void do_render1(RLViewport viewport, RLDevice device, visible_buildings vblg);
void BuildScene1(RLDevice dev, RLViewport view, RLFrame scene, RLFrame camera);
void FindOneBuilding(visible_buildings *vis_bldgs, int targetbldg);
void FindSpecificBuildings(visible_buildings *specific_buildings);
void GetSpecificBox(int building_num, RLBox *abox);

#endif

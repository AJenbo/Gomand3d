//****************************************
//       Art Placement Output File        
//                                        
//  Created by: txtcnvrt.exe    Ver: 1.0         
//   Date: Sep 12 1995     Time: 15:12:56                
//                                        
//                                        
//  This file is to be compiled into its  
// own entity and loaded for each level.  
//****************************************


#pragma warning( disable : 4244)

#ifdef _47TEK_RL_
#include "rl.h"                            
#include "IMode.h"      // Immediate Mode Stuff for LandScap.h         
#endif

#ifdef _ITC_D3D_
#include "rl2d3d.h"
#endif

#define WORLD_SIZE  256     // The World's current Width & Height in Units.                    
#define RES_SHFT_DIVISOR 4  // Value for dividing the 256 world resolution by Powers of 2.     


typedef struct _GDPLIST                                                                        
{                                                                                              
    RLIMLightingPoint *srcv;                                                                   
    RLIMViewVertex    *dstv;                                                                   
    RLIMTriangle      *trig;                                                                   
#ifdef _47TEK_RL_
    RLTexture         picture;                                                                 
#else
	D3DTEXTUREHANDLE  picture;
#endif _47TEK_RL_
    int vc, tc;                                                                                
    RLFrame frame1;                                                                            
#ifdef _47TEK_RL_
    RLIMSurfaceInfo sInfo;                                                                     
#endif _47TEK_RL_
} GDPLIST;                                                                                     

                                                                                     


typedef struct _building_                
{                                                                                             
    short visible;      // Is this Building Currently Visible or Not. (NO==0, YES!=0).         
    int building_num;   // Which Building is being placed in the world.                        
    long scale;      // Scale factor for Generic Buildings.                                 
    float tu;         // Texture Map U-Co-ordinate.                                          
    float tv;         // Texture Map V-Co-ordinate.                                          
    int cur_damage;     // Current Damage of Building.                                         
    int max_damage;     // Maximum Damage this Building Can withstand.                         
    int power_mon_amount;  // Percentage of Power Monster Gets for Destroying Building.        
    int power_Robot_amount; // Percentage of Power Robot Gets for Touching Building.             
    long x_world;    // X-World Position of Building                                        
    long z_world;    // Z-World Position of Building                                        
    long dir;              // Direction in Radians that the Building is facing.             
    long y_world;    // Y-Altitude of Building After the Altitude is Located.               
    RLBox building;     //  Min & Max X,Y,Z Values (As RLValues).                              
    RLFrame *rlframe;   //  This Buildings RLFrame.                                            
    GDPLIST *displist;  //  Pointer To The Display List.                                       
    RLIMTriangle    *trilist;   // Pointer to the Triangle list of this building.              
}building;                                                                                     


typedef struct _building_area_                                                                 
{                                                                                              
    int count;                  //  The Number of Buildings in that area.                      
    building *building_ptr;     //  An Array of building Pointers.                             
}building_area;                                                                                



//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN00[2]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,15,3,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,15,15,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x10x2[1]={
       { 0, 67,1,-0.003906,-0.003906,  0,9000,  0,  0,23,35,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x10xa[1]={
       { 0, -1,6,0.500000,0.500000,  0,  5,  2,  0,31,160,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x10xb[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  2,  0,23,180,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x10xe[1]={
       { 0, 20,1,-0.003906,-0.003906,  0, 40, 40,  0,19,229,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x20[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,35,11,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x20x1[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,35,23,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x20x2[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,35,35,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x20x3[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,39,59,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x20x4[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,39,71,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x20x9[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,43,148,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x20xa[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  2,  0,43,160,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x20xb[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  2,  0,35,180,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x20xc[2]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  2,  0,43,200,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,5,0.500000,0.000000,  0,  5,  2,  0,43,206,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x20xd[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  2,  0,43,212,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x30[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,59,3,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x30x1[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,59,27,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x30x2[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,59,39,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x30x3[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,51,59,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x30x4[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  3,  0,51,71,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x30x5[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,59,91,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x30x6[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,59,103,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x30xb[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,55,180,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x40[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,71,3,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x40x1[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,71,27,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x40x2[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  3,  0,71,39,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x40x3[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,71,59,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x40x4[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  3,  0,71,71,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x40x5[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,71,91,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x40x6[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,79,111,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x40x9[2]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,67,148,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,4,0.500000,0.000000,  0,  5,  2,  0,79,148,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x40xa[2]={
       { 0, -1,6,0.500000,0.500000,  0,  5,  2,  0,79,160,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,8,0.500000,0.500000,  0,  5,  2,  0,67,160,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x40xb[1]={
       { 0, -1,2,0.500000,0.500000,  0,  5,  2,  0,75,180,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x40xc[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  2,  0,75,200,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x40xd[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  2,  0,75,212,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x50[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,95,11,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x50x3[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,95,55,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x50x4[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,95,67,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x50x6[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,91,111,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x50xc[1]={
       { 0, -1,9,0.500000,0.500000,  0,  5,  2,  0,87,200,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x50xd[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  2,  0,87,212,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x50xe[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,83,232,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x50xf[1]={
       { 0, 66,1,-0.003906,-0.003906,  0,9000,  0,  0,83,247,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x60[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,107,11,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x60x6[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,111,111,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x60x9[2]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  2,  0,111,148,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,6,0.500000,0.000000,  0,  5,  2,  0,99,148,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x60xa[1]={
       { 0, -1,9,0.500000,0.500000,  0,  5,  2,  0,99,160,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x60xb[2]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  2,  0,99,180,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,6,0.500000,0.000000,  0,  5,  2,  0,107,180,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x60xc[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  2,  0,107,200,0,58,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x60xd[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  2,  0,107,220,0,67,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x60xf[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,107,240,0,71,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x70x1[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,119,31,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x70x5[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,119,91,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x70x6[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,123,111,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x70xb[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  2,  0,127,180,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x70xc[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  2,  0,127,200,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x70xd[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,127,220,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x70xf[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  2,  0,119,240,0,69,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x80[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,131,11,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x80x1[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,131,31,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x80x5[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  8,  0,131,91,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x80x6[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,135,111,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x80x9[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  2,  0,139,148,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x80xa[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  2,  0,139,160,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x80xd[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  2,  0,139,220,0,71,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x80xf[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  2,  0,139,240,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x90[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,155,11,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x90x3[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,155,55,0,64,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x90x4[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,155,67,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x90x6[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,155,111,0,58,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x90x9[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  2,  0,151,148,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x90xa[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  2,  0,159,168,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x90xb[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  2,  0,159,188,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x90xc[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  2,  0,147,200,0,58,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x90xd[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  2,  0,151,220,0,63,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0x90xf[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,159,240,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xa0[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,167,11,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xa0x2[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,175,47,0,59,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xa0x3[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,175,59,0,61,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xa0x4[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,175,71,0,60,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xa0x5[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,175,91,0,58,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xa0x6[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,175,103,0,58,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xa0xd[2]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  2,  0,166,220,0,62,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,5,0.500000,0.000000,  0,  5,  2,  0,167,208,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xb0[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,187,15,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xb0x1[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,187,27,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xb0x2[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  3,  0,187,47,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xb0x5[1]={
       { 0, 13,1,-0.003906,-0.003906,  0, 10, 10,  0,191,83,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xb0x9[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  2,  0,183,148,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xb0xa[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  2,  0,183,168,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xb0xb[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  2,  0,179,188,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xb0xd[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  2,  0,187,208,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xb0xe[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  2,  0,187,228,0,75,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xc0[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,207,7,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xc0x1[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,199,27,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xc0x2[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,207,47,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xc0x4[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,199,77,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xc0x6[2]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,195,107,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,207,107,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xc0x9[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  2,  0,203,148,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xc0xa[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  2,  0,195,168,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xc0xb[1]={
       { 0, -1,6,0.500000,0.500000,  0,  5,  2,  0,195,188,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xc0xd[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  2,  0,207,208,0,59,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xd0[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,219,7,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xd0x1[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  3,  0,219,19,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xd0x2[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,219,47,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xd0x4[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,211,71,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xd0x5[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,211,83,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xd0xe[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  2,  0,208,228,0,76,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xe0[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  3,  0,231,7,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xe0x1[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,239,27,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xe0x2[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  3,  0,231,47,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xe0x4[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,231,71,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xe0x5[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,231,83,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xe0x6[2]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,227,107,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,239,107,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xe0x9[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,231,151,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xe0xa[2]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  2,  0,231,160,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,231,168,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xe0xb[2]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  2,  0,231,176,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,231,184,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xe0xc[2]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  2,  0,231,192,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,231,200,0,59,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xe0xd[1]={
       { 0, 15,1,-0.003906,-0.003906,  0, 30, 30,  0,239,215,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLN0xf0[1]={
       { 0, 68,1,-0.003906,-0.003906,  0,9000,  0,  0,251,6,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };



building_area bldg_lvlLN[(WORLD_SIZE>>RES_SHFT_DIVISOR)][(WORLD_SIZE>>RES_SHFT_DIVISOR)]={{
       {2,bldgLN00},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {1,bldgLN0x10x2},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLN0x10xa},
       {1,bldgLN0x10xb},
       {0,NULL},
       {0,NULL},
       {1,bldgLN0x10xe},
       {0,NULL},},{
       {1,bldgLN0x20},
       {1,bldgLN0x20x1},
       {1,bldgLN0x20x2},
       {1,bldgLN0x20x3},
       {1,bldgLN0x20x4},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLN0x20x9},
       {1,bldgLN0x20xa},
       {1,bldgLN0x20xb},
       {2,bldgLN0x20xc},
       {1,bldgLN0x20xd},
       {0,NULL},
       {0,NULL},},{
       {1,bldgLN0x30},
       {1,bldgLN0x30x1},
       {1,bldgLN0x30x2},
       {1,bldgLN0x30x3},
       {1,bldgLN0x30x4},
       {1,bldgLN0x30x5},
       {1,bldgLN0x30x6},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLN0x30xb},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},},{
       {1,bldgLN0x40},
       {1,bldgLN0x40x1},
       {1,bldgLN0x40x2},
       {1,bldgLN0x40x3},
       {1,bldgLN0x40x4},
       {1,bldgLN0x40x5},
       {1,bldgLN0x40x6},
       {0,NULL},
       {0,NULL},
       {2,bldgLN0x40x9},
       {2,bldgLN0x40xa},
       {1,bldgLN0x40xb},
       {1,bldgLN0x40xc},
       {1,bldgLN0x40xd},
       {0,NULL},
       {0,NULL},},{
       {1,bldgLN0x50},
       {0,NULL},
       {0,NULL},
       {1,bldgLN0x50x3},
       {1,bldgLN0x50x4},
       {0,NULL},
       {1,bldgLN0x50x6},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLN0x50xc},
       {1,bldgLN0x50xd},
       {1,bldgLN0x50xe},
       {1,bldgLN0x50xf},},{
       {1,bldgLN0x60},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLN0x60x6},
       {0,NULL},
       {0,NULL},
       {2,bldgLN0x60x9},
       {1,bldgLN0x60xa},
       {2,bldgLN0x60xb},
       {1,bldgLN0x60xc},
       {1,bldgLN0x60xd},
       {0,NULL},
       {1,bldgLN0x60xf},},{
       {0,NULL},
       {1,bldgLN0x70x1},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLN0x70x5},
       {1,bldgLN0x70x6},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLN0x70xb},
       {1,bldgLN0x70xc},
       {1,bldgLN0x70xd},
       {0,NULL},
       {1,bldgLN0x70xf},},{
       {1,bldgLN0x80},
       {1,bldgLN0x80x1},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLN0x80x5},
       {1,bldgLN0x80x6},
       {0,NULL},
       {0,NULL},
       {1,bldgLN0x80x9},
       {1,bldgLN0x80xa},
       {0,NULL},
       {0,NULL},
       {1,bldgLN0x80xd},
       {0,NULL},
       {1,bldgLN0x80xf},},{
       {1,bldgLN0x90},
       {0,NULL},
       {0,NULL},
       {1,bldgLN0x90x3},
       {1,bldgLN0x90x4},
       {0,NULL},
       {1,bldgLN0x90x6},
       {0,NULL},
       {0,NULL},
       {1,bldgLN0x90x9},
       {1,bldgLN0x90xa},
       {1,bldgLN0x90xb},
       {1,bldgLN0x90xc},
       {1,bldgLN0x90xd},
       {0,NULL},
       {1,bldgLN0x90xf},},{
       {1,bldgLN0xa0},
       {0,NULL},
       {1,bldgLN0xa0x2},
       {1,bldgLN0xa0x3},
       {1,bldgLN0xa0x4},
       {1,bldgLN0xa0x5},
       {1,bldgLN0xa0x6},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {2,bldgLN0xa0xd},
       {0,NULL},
       {0,NULL},},{
       {1,bldgLN0xb0},
       {1,bldgLN0xb0x1},
       {1,bldgLN0xb0x2},
       {0,NULL},
       {0,NULL},
       {1,bldgLN0xb0x5},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLN0xb0x9},
       {1,bldgLN0xb0xa},
       {1,bldgLN0xb0xb},
       {0,NULL},
       {1,bldgLN0xb0xd},
       {1,bldgLN0xb0xe},
       {0,NULL},},{
       {1,bldgLN0xc0},
       {1,bldgLN0xc0x1},
       {1,bldgLN0xc0x2},
       {0,NULL},
       {1,bldgLN0xc0x4},
       {0,NULL},
       {2,bldgLN0xc0x6},
       {0,NULL},
       {0,NULL},
       {1,bldgLN0xc0x9},
       {1,bldgLN0xc0xa},
       {1,bldgLN0xc0xb},
       {0,NULL},
       {1,bldgLN0xc0xd},
       {0,NULL},
       {0,NULL},},{
       {1,bldgLN0xd0},
       {1,bldgLN0xd0x1},
       {1,bldgLN0xd0x2},
       {0,NULL},
       {1,bldgLN0xd0x4},
       {1,bldgLN0xd0x5},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLN0xd0xe},
       {0,NULL},},{
       {1,bldgLN0xe0},
       {1,bldgLN0xe0x1},
       {1,bldgLN0xe0x2},
       {0,NULL},
       {1,bldgLN0xe0x4},
       {1,bldgLN0xe0x5},
       {2,bldgLN0xe0x6},
       {0,NULL},
       {0,NULL},
       {1,bldgLN0xe0x9},
       {2,bldgLN0xe0xa},
       {2,bldgLN0xe0xb},
       {2,bldgLN0xe0xc},
       {1,bldgLN0xe0xd},
       {0,NULL},
       {0,NULL},},{
       {1,bldgLN0xf0},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},},
       };


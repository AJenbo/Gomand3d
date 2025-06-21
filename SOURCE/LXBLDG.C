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
     building bldgLX0x20x2[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,41,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,46,41,0,90,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x20x3[3]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,48,0,103,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,55,0,128,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,62,0,170,{{0,0,0},{0,0,0}},0,0,0},          // Building #-2
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x20x4[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,69,0,208,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,76,0,216,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x20x5[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,83,0,214,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,90,0,185,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x20x6[3]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,97,0,122,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,104,0,79,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,111,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-2
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x20x7[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,118,0,18,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,125,0,1,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x20x8[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,132,0,1,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,139,0,1,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x20x9[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,146,0,1,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,153,0,1,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x20xa[3]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,160,0,1,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,167,0,1,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,174,0,3,{{0,0,0},{0,0,0}},0,0,0},          // Building #-2
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x20xb[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,181,0,17,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,188,0,23,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x20xc[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,195,0,28,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,202,0,28,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x20xd[4]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,220,0,59,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,46,220,0,38,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,209,0,36,{{0,0,0},{0,0,0}},0,0,0},          // Building #-2
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,39,216,0,50,{{0,0,0},{0,0,0}},0,0,0},          // Building #-3
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x30x2[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,53,41,0,85,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,60,41,0,54,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x30xc[1]={
       { 0, 67,1,-0.003906,-0.003906,  0,9000,  0,  0,57,202,0,9,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x30xd[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,53,220,0,24,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,60,220,0,17,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x40x2[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,67,41,0,27,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,74,41,0,17,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x40x4[1]={
       { 0, 20,1,-0.003906,-0.003906,  0, 10, 10,  0,77,79,0,42,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x40x8[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,64,138,0,1,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x40x9[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,64,148,0,1,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x40xa[4]={
       { 0, -1,6,0.500000,0.500000,  0,  5,  6,  0,64,160,0,1,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,64,174,0,4,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       { 0, -1,4,0.500000,0.500000,  0,  5,  4,  0,76,160,0,1,{{0,0,0},{0,0,0}},0,0,0},          // Building #-2
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,76,174,0,4,{{0,0,0},{0,0,0}},0,0,0},          // Building #-3
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x40xb[2]={
       { 0, -1,10,0.500000,0.500000,  0,  5, 10,  0,64,190,0,16,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,76,190,0,20,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x40xd[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,67,220,0,13,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,74,220,0,22,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x50x2[3]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,81,41,0,21,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,88,41,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,95,41,0,35,{{0,0,0},{0,0,0}},0,0,0},          // Building #-2
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x50x7[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,94,112,0,19,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x50xa[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,90,174,0,4,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x50xb[1]={
       { 0, -1,6,0.500000,0.500000,  0,  5,  6,  0,90,190,0,31,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x50xd[3]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,81,220,0,33,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,88,220,0,54,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,95,220,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-2
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x60x2[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,102,41,0,11,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,109,41,0,14,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x60x5[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,110,92,0,1,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x60x7[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,110,118,0,11,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x60x9[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,110,154,0,1,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x60xb[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,106,190,0,51,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x60xd[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,102,220,0,82,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,109,220,0,93,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x70x2[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,116,41,0,15,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,123,41,0,20,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x70xc[1]={
       { 0, 13,1,-0.003906,-0.003906,  0, 10, 10,  0,127,199,0,1,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x70xd[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,116,220,0,83,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,123,220,0,48,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x80x2[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,130,41,0,25,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,137,41,0,42,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x80x3[1]={
       { 0, 66,1,-0.003906,-0.003906,  0,9000,  0,  0,133,57,0,24,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x80xd[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,130,220,0,26,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,137,220,0,17,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x90x2[3]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,144,41,0,115,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,151,41,0,172,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,158,41,0,119,{{0,0,0},{0,0,0}},0,0,0},          // Building #-2
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x90x7[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,144,118,0,8,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x90x9[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,144,154,0,4,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0x90xd[3]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,144,220,0,35,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,151,220,0,54,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,158,220,0,115,{{0,0,0},{0,0,0}},0,0,0},          // Building #-2
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xa0x2[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,165,41,0,71,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,172,41,0,29,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xa0x3[2]={
       { 0, -1,6,0.500000,0.500000,  0,  5,  6,  0,174,62,0,38,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,162,62,0,112,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xa0x9[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  4,  0,172,150,0,3,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xa0xc[1]={
       { 0, -1,4,0.500000,0.500000,  0,  5,  4,  0,172,202,0,254,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xa0xd[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,165,220,0,254,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,172,220,0,254,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xb0x2[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,179,41,0,22,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,186,41,0,40,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xb0x3[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,186,62,0,16,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xb0x4[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,186,74,0,21,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xb0x5[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,186,88,0,14,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xb0x9[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,190,150,0,30,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xb0xd[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,179,220,0,254,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,186,220,0,254,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xc0x2[3]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,193,41,0,71,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,200,41,0,60,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,207,41,0,24,{{0,0,0},{0,0,0}},0,0,0},          // Building #-2
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xc0x7[1]={
       { 0, 15,1,-0.003906,-0.003906,  0, 10, 10,  0,196,115,0,1,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xc0xc[1]={
       { 0, 68,1,-0.003906,-0.003906,  0,9000,  0,  0,200,202,0,254,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xc0xd[3]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,193,220,0,254,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,200,220,0,90,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,207,220,0,36,{{0,0,0},{0,0,0}},0,0,0},          // Building #-2
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xd0x2[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,214,41,0,4,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,41,0,1,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xd0x3[3]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,48,0,1,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,55,0,4,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,62,0,4,{{0,0,0},{0,0,0}},0,0,0},          // Building #-2
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xd0x4[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,69,0,7,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,76,0,9,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xd0x5[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,83,0,1,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,90,0,29,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xd0x6[3]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,97,0,21,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,104,0,20,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,111,0,10,{{0,0,0},{0,0,0}},0,0,0},          // Building #-2
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xd0x7[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,118,0,4,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,125,0,1,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xd0x8[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,132,0,1,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,139,0,11,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xd0x9[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,146,0,39,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,153,0,36,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xd0xa[3]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,160,0,39,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,167,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,174,0,49,{{0,0,0},{0,0,0}},0,0,0},          // Building #-2
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xd0xb[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,181,0,33,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,188,0,9,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xd0xc[2]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,195,0,7,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,202,0,12,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLX0xd0xd[4]={
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,214,220,0,13,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,220,0,9,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,209,0,16,{{0,0,0},{0,0,0}},0,0,0},          // Building #-2
       { 0, -1,10,0.000000,0.500000,  0,4000,  0,  0,221,216,0,8,{{0,0,0},{0,0,0}},0,0,0},          // Building #-3
       };



building_area bldg_lvlLX[(WORLD_SIZE>>RES_SHFT_DIVISOR)][(WORLD_SIZE>>RES_SHFT_DIVISOR)]={{
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
       {0,NULL},
       {0,NULL},},{
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
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {2,bldgLX0x20x2},
       {3,bldgLX0x20x3},
       {2,bldgLX0x20x4},
       {2,bldgLX0x20x5},
       {3,bldgLX0x20x6},
       {2,bldgLX0x20x7},
       {2,bldgLX0x20x8},
       {2,bldgLX0x20x9},
       {3,bldgLX0x20xa},
       {2,bldgLX0x20xb},
       {2,bldgLX0x20xc},
       {4,bldgLX0x20xd},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {2,bldgLX0x30x2},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLX0x30xc},
       {2,bldgLX0x30xd},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {2,bldgLX0x40x2},
       {0,NULL},
       {1,bldgLX0x40x4},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLX0x40x8},
       {1,bldgLX0x40x9},
       {4,bldgLX0x40xa},
       {2,bldgLX0x40xb},
       {0,NULL},
       {2,bldgLX0x40xd},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {3,bldgLX0x50x2},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLX0x50x7},
       {0,NULL},
       {0,NULL},
       {1,bldgLX0x50xa},
       {1,bldgLX0x50xb},
       {0,NULL},
       {3,bldgLX0x50xd},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {2,bldgLX0x60x2},
       {0,NULL},
       {0,NULL},
       {1,bldgLX0x60x5},
       {0,NULL},
       {1,bldgLX0x60x7},
       {0,NULL},
       {1,bldgLX0x60x9},
       {0,NULL},
       {1,bldgLX0x60xb},
       {0,NULL},
       {2,bldgLX0x60xd},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {2,bldgLX0x70x2},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLX0x70xc},
       {2,bldgLX0x70xd},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {2,bldgLX0x80x2},
       {1,bldgLX0x80x3},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {2,bldgLX0x80xd},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {3,bldgLX0x90x2},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLX0x90x7},
       {0,NULL},
       {1,bldgLX0x90x9},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {3,bldgLX0x90xd},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {2,bldgLX0xa0x2},
       {2,bldgLX0xa0x3},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLX0xa0x9},
       {0,NULL},
       {0,NULL},
       {1,bldgLX0xa0xc},
       {2,bldgLX0xa0xd},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {2,bldgLX0xb0x2},
       {1,bldgLX0xb0x3},
       {1,bldgLX0xb0x4},
       {1,bldgLX0xb0x5},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLX0xb0x9},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {2,bldgLX0xb0xd},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {3,bldgLX0xc0x2},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLX0xc0x7},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLX0xc0xc},
       {3,bldgLX0xc0xd},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {2,bldgLX0xd0x2},
       {3,bldgLX0xd0x3},
       {2,bldgLX0xd0x4},
       {2,bldgLX0xd0x5},
       {3,bldgLX0xd0x6},
       {2,bldgLX0xd0x7},
       {2,bldgLX0xd0x8},
       {2,bldgLX0xd0x9},
       {3,bldgLX0xd0xa},
       {2,bldgLX0xd0xb},
       {2,bldgLX0xd0xc},
       {4,bldgLX0xd0xd},
       {0,NULL},
       {0,NULL},},{
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
       {0,NULL},
       {0,NULL},},{
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
       {0,NULL},
       {0,NULL},},
       };


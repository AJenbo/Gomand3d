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
     building bldgLT00[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,7,7,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT00x1[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,7,27,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT00x2[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,7,39,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT00x4[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,7,75,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT00x5[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,7,87,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT00x8[2]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,11,131,0,36,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,11,143,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT00xa[2]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,11,163,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,9,0.500000,0.500000,  0,  5,  9,  0,11,175,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT00xc[2]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,11,195,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,11,207,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT00xf[1]={
       { 0, 68,1,-0.003906,-0.003906,  0,9000,  0,  0,9,248,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x10[2]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,19,7,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,31,7,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x10x1[2]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,19,27,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,31,27,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x10x2[2]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,19,39,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,31,39,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x10x4[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,27,75,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x10x5[1]={
       { 0, 15,1,-0.003906,-0.003906,  0, 24, 45,  0,27,87,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x10x8[2]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,23,131,0,36,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,23,143,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x10xa[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,23,163,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x10xb[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,31,187,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x10xc[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,31,207,0,68,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x20x5[2]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,47,83,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,47,95,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x20x8[1]={
       { 0, -1,9,0.500000,0.500000,  0,  5,  9,  0,43,143,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x20x9[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,43,155,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x20xa[1]={
       { 0, -1,7,0.500000,0.000000,  0,  5,  7,  0,43,175,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x20xb[1]={
       { 0, -1,9,0.500000,0.500000,  0,  5,  9,  0,43,187,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x20xc[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,43,207,0,60,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x30[2]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,51,15,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, 66,1,-0.003906,-0.003906,  0,9000,  0,  0,63,15,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x30x2[2]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,51,35,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,63,35,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x30x5[2]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,59,83,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,59,95,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x30x9[1]={
       { 0, -1,5,0.500000,0.500000,  0,  5,  5,  0,63,159,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x30xa[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,63,171,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x30xb[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,63,183,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x30xc[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,55,207,0,64,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x30xe[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,63,231,0,68,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x40x5[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,71,95,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x40xa[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,75,171,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x40xd[1]={
       { 0, -1,9,0.500000,0.500000,  0,  5,  9,  0,75,219,0,72,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x40xe[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  3,  0,75,231,0,68,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x40xf[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,75,247,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x50[2]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,83,3,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,83,15,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x50x1[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,83,27,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x50x2[2]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,83,47,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,95,47,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x50x3[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,95,59,0,54,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x50x6[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,91,103,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x50x7[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,91,115,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x50xd[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,87,219,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x50xe[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,87,231,0,63,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x50xf[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,87,247,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x60[2]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,103,3,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,103,15,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x60x1[1]={
       { 0, -1,9,0.500000,0.500000,  0,  5,  9,  0,103,27,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x60x2[1]={
       { 0, -1,9,0.500000,0.500000,  0,  5,  9,  0,107,47,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x60x3[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,107,59,0,54,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x60x6[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,111,111,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x60x7[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,111,123,0,0,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x60x8[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,111,143,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x60xa[2]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,111,163,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,6,0.500000,0.000000,  0,  5,  3,  0,111,175,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x60xe[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,107,227,0,79,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x60xf[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,99,247,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x70[2]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,115,3,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,115,15,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x70x1[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,115,27,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x70x6[1]={
       { 0, -1,7,0.500000,0.000000,  0,  5,  7,  0,123,111,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x70x7[1]={
       { 0, -1,9,0.500000,0.500000,  0,  5,  9,  0,123,123,0,0,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x70x8[1]={
       { 0, -1,9,0.500000,0.500000,  0,  5,  9,  0,123,143,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x70xa[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  3,  0,123,163,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x70xe[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,119,227,0,76,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x70xf[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,119,247,0,57,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x80x6[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,143,111,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x80x8[1]={
       { 0, -1,7,0.500000,0.000000,  0,  5,  7,  0,135,143,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x80xe[1]={
       { 0, -1,9,0.500000,0.500000,  0,  5,  9,  0,131,227,0,60,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x80xf[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,139,247,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x90[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,151,15,0,32,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x90x2[2]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,159,35,0,22,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,9,0.500000,0.500000,  0,  5,  9,  0,159,47,0,22,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x90x4[3]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,147,71,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,159,67,0,22,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       { 0, -1,9,0.500000,0.500000,  0,  5,  9,  0,159,79,0,22,{{0,0,0},{0,0,0}},0,0,0},          // Building #-2
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x90x5[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,158,91,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x90x6[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,155,111,0,0,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x90x8[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,147,143,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x90xc[1]={
       { 0, 13,1,-0.003906,-0.003906,  0, 15, 25,  0,151,203,0,32,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x90xd[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,151,215,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x90xe[1]={
       { 0, -1,9,0.500000,0.500000,  0,  5,  9,  0,151,235,0,32,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0x90xf[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,151,247,0,32,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xa0[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,163,15,0,54,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xa0x2[2]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,171,35,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,171,47,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xa0xd[1]={
       { 0, -1,7,0.500000,0.000000,  0,  5,  7,  0,171,223,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xa0xe[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,171,235,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xa0xf[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,171,247,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xb0[2]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,183,3,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,183,15,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xb0x2[2]={
       { 0, -1,7,0.500000,0.000000,  0,  5,  7,  0,183,35,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,183,47,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xb0x4[2]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  3,  0,179,67,0,22,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,179,79,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xb0xa[1]={
       { 0, -1,9,0.500000,0.500000,  0,  5,  9,  0,187,171,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xb0xb[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,187,183,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xb0xe[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,183,235,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xb0xf[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,183,247,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xc0x9[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,203,155,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xc0xa[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,207,175,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xc0xb[1]={
       { 0, -1,9,0.500000,0.500000,  0,  5,  9,  0,207,187,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xd0x8[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,215,135,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xd0x9[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,215,155,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xd0xa[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  3,  0,219,175,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xd0xb[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,219,187,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xd0xe[2]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,211,239,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,223,239,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xe0[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,227,7,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xe0x1[1]={
       { 0, 20,1,-0.003906,-0.003906,  0, 21, 35,  0,227,19,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xe0x2[2]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,227,39,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,239,39,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xe0x3[1]={
       { 0, -1,7,0.500000,0.000000,  0,  5,  7,  0,227,51,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xe0x4[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,227,71,0,0,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xe0x5[1]={
       { 0, -1,9,0.500000,0.500000,  0,  5,  9,  0,227,91,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xe0x6[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,227,103,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xe0x7[2]={
       { 0, -1,9,0.500000,0.500000,  0,  5,  9,  0,227,123,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,5,0.500000,0.000000,  0,  5,  3,  0,239,123,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xe0x8[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,227,135,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xe0x9[1]={
       { 0, -1,9,0.500000,0.500000,  0,  5,  9,  0,227,155,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xe0xa[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,239,175,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xe0xb[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,239,187,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xe0xc[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,239,199,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xe0xe[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,235,239,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xf0[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,247,7,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xf0x1[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,247,19,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xf0x3[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,247,59,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xf0x4[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,247,71,0,0,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xf0x5[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,247,91,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xf0x6[1]={
       { 0, -1,8,0.500000,0.500000,  0,  5,  8,  0,247,103,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xf0x8[1]={
       { 0, 67,1,-0.003906,-0.003906,  0,9000,  0,  0,247,143,0,55,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xf0x9[1]={
       { 0, -1,7,0.500000,0.000000,  0,  5,  7,  0,247,155,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLT0xf0xe[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,247,239,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };



building_area bldg_lvlLT[(WORLD_SIZE>>RES_SHFT_DIVISOR)][(WORLD_SIZE>>RES_SHFT_DIVISOR)]={{
       {1,bldgLT00},
       {1,bldgLT00x1},
       {1,bldgLT00x2},
       {0,NULL},
       {1,bldgLT00x4},
       {1,bldgLT00x5},
       {0,NULL},
       {0,NULL},
       {2,bldgLT00x8},
       {0,NULL},
       {2,bldgLT00xa},
       {0,NULL},
       {2,bldgLT00xc},
       {0,NULL},
       {0,NULL},
       {1,bldgLT00xf},},{
       {2,bldgLT0x10},
       {2,bldgLT0x10x1},
       {2,bldgLT0x10x2},
       {0,NULL},
       {1,bldgLT0x10x4},
       {1,bldgLT0x10x5},
       {0,NULL},
       {0,NULL},
       {2,bldgLT0x10x8},
       {0,NULL},
       {1,bldgLT0x10xa},
       {1,bldgLT0x10xb},
       {1,bldgLT0x10xc},
       {0,NULL},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {2,bldgLT0x20x5},
       {0,NULL},
       {0,NULL},
       {1,bldgLT0x20x8},
       {1,bldgLT0x20x9},
       {1,bldgLT0x20xa},
       {1,bldgLT0x20xb},
       {1,bldgLT0x20xc},
       {0,NULL},
       {0,NULL},
       {0,NULL},},{
       {2,bldgLT0x30},
       {0,NULL},
       {2,bldgLT0x30x2},
       {0,NULL},
       {0,NULL},
       {2,bldgLT0x30x5},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLT0x30x9},
       {1,bldgLT0x30xa},
       {1,bldgLT0x30xb},
       {1,bldgLT0x30xc},
       {0,NULL},
       {1,bldgLT0x30xe},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLT0x40x5},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLT0x40xa},
       {0,NULL},
       {0,NULL},
       {1,bldgLT0x40xd},
       {1,bldgLT0x40xe},
       {1,bldgLT0x40xf},},{
       {2,bldgLT0x50},
       {1,bldgLT0x50x1},
       {2,bldgLT0x50x2},
       {1,bldgLT0x50x3},
       {0,NULL},
       {0,NULL},
       {1,bldgLT0x50x6},
       {1,bldgLT0x50x7},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLT0x50xd},
       {1,bldgLT0x50xe},
       {1,bldgLT0x50xf},},{
       {2,bldgLT0x60},
       {1,bldgLT0x60x1},
       {1,bldgLT0x60x2},
       {1,bldgLT0x60x3},
       {0,NULL},
       {0,NULL},
       {1,bldgLT0x60x6},
       {1,bldgLT0x60x7},
       {1,bldgLT0x60x8},
       {0,NULL},
       {2,bldgLT0x60xa},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLT0x60xe},
       {1,bldgLT0x60xf},},{
       {2,bldgLT0x70},
       {1,bldgLT0x70x1},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLT0x70x6},
       {1,bldgLT0x70x7},
       {1,bldgLT0x70x8},
       {0,NULL},
       {1,bldgLT0x70xa},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLT0x70xe},
       {1,bldgLT0x70xf},},{
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLT0x80x6},
       {0,NULL},
       {1,bldgLT0x80x8},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLT0x80xe},
       {1,bldgLT0x80xf},},{
       {1,bldgLT0x90},
       {0,NULL},
       {2,bldgLT0x90x2},
       {0,NULL},
       {3,bldgLT0x90x4},
       {1,bldgLT0x90x5},
       {1,bldgLT0x90x6},
       {0,NULL},
       {1,bldgLT0x90x8},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLT0x90xc},
       {1,bldgLT0x90xd},
       {1,bldgLT0x90xe},
       {1,bldgLT0x90xf},},{
       {1,bldgLT0xa0},
       {0,NULL},
       {2,bldgLT0xa0x2},
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
       {1,bldgLT0xa0xd},
       {1,bldgLT0xa0xe},
       {1,bldgLT0xa0xf},},{
       {2,bldgLT0xb0},
       {0,NULL},
       {2,bldgLT0xb0x2},
       {0,NULL},
       {2,bldgLT0xb0x4},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLT0xb0xa},
       {1,bldgLT0xb0xb},
       {0,NULL},
       {0,NULL},
       {1,bldgLT0xb0xe},
       {1,bldgLT0xb0xf},},{
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLT0xc0x9},
       {1,bldgLT0xc0xa},
       {1,bldgLT0xc0xb},
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
       {1,bldgLT0xd0x8},
       {1,bldgLT0xd0x9},
       {1,bldgLT0xd0xa},
       {1,bldgLT0xd0xb},
       {0,NULL},
       {0,NULL},
       {2,bldgLT0xd0xe},
       {0,NULL},},{
       {1,bldgLT0xe0},
       {1,bldgLT0xe0x1},
       {2,bldgLT0xe0x2},
       {1,bldgLT0xe0x3},
       {1,bldgLT0xe0x4},
       {1,bldgLT0xe0x5},
       {1,bldgLT0xe0x6},
       {2,bldgLT0xe0x7},
       {1,bldgLT0xe0x8},
       {1,bldgLT0xe0x9},
       {1,bldgLT0xe0xa},
       {1,bldgLT0xe0xb},
       {1,bldgLT0xe0xc},
       {0,NULL},
       {1,bldgLT0xe0xe},
       {0,NULL},},{
       {1,bldgLT0xf0},
       {1,bldgLT0xf0x1},
       {0,NULL},
       {1,bldgLT0xf0x3},
       {1,bldgLT0xf0x4},
       {1,bldgLT0xf0x5},
       {1,bldgLT0xf0x6},
       {0,NULL},
       {1,bldgLT0xf0x8},
       {1,bldgLT0xf0x9},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLT0xf0xe},
       {0,NULL},},
       };


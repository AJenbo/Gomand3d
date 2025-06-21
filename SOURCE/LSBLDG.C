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
     building bldgLS00[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,11,11,0,79,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS00x1[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,11,31,0,90,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS00x3[1]={
       { 0, -1,1,0.000000,0.500000,  0,  5,  1,  0,11,51,0,110,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS00x4[1]={
       { 0, -1,5,0.500000,0.500000,  0,  5,  5,  0,7,67,0,82,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS00x5[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,7,87,0,70,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS00x6[1]={
       { 0, -1,5,0.500000,0.500000,  0,  5,  5,  0,11,108,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS00x7[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,11,119,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS00x9[1]={
       { 0, -1,2,0.500000,0.500000,  0,  5,  2,  0,5,155,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS00xa[1]={
       { 0, 13,1,-0.003906,-0.003906,  0,  5, 15,  0,14,160,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS00xf[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,15,247,0,78,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x10[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,23,11,0,86,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x10x1[1]={
       { 0, -1,6,0.500000,0.500000,  0,  5,  6,  0,23,31,0,116,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x10x3[1]={
       { 0, -1,6,0.500000,0.500000,  0,  5,  6,  0,23,51,0,144,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x10x4[2]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,19,67,0,113,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,4,0.500000,0.000000,  0,  5,  2,  0,21,71,0,119,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x10x5[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,19,87,0,83,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x10x6[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,31,111,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x10x7[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,31,123,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x20[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,35,11,0,92,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x20x1[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,43,31,0,159,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x20x3[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,43,51,0,175,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x20x4[1]={
       { 0, 67,1,-0.003906,-0.003906,  0,9000,  0,  0,34,69,0,128,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x20x5[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,39,91,0,75,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x20x6[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,43,111,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x20x7[1]={
       { 0, -1,6,0.500000,0.500000,  0,  5,  6,  0,43,123,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x20x9[1]={
       { 0, -1,6,0.500000,0.500000,  0,  5,  6,  0,39,155,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x20xa[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,39,175,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x20xb[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,39,187,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x20xc[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,43,199,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x20xd[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,35,219,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x20xe[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,35,231,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x20xf[1]={
       { 0, -1,5,0.500000,0.500000,  0,  5,  5,  0,35,247,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x30[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,55,11,0,99,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x30x1[1]={
       { 0, -1,5,0.500000,0.500000,  0,  5,  5,  0,63,31,0,121,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x30x2[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,63,43,0,108,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x30x4[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,51,71,0,89,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x30x5[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,51,91,0,71,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x30x6[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,63,111,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x30x7[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,63,123,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x30x9[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,51,155,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x30xa[1]={
       { 0, -1,6,0.500000,0.500000,  0,  5,  6,  0,51,175,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x30xb[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,51,187,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x30xf[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,55,247,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x40[2]={
       { 0, -1,6,0.500000,0.500000,  0,  5,  6,  0,67,11,0,107,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,79,11,0,89,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x40x4[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,71,71,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x40x5[1]={
       { 0, -1,5,0.500000,0.500000,  0,  5,  5,  0,71,91,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x40x9[1]={
       { 0, -1,5,0.500000,0.000000,  0,  5,  5,  0,71,155,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x40xb[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,68,176,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x40xf[1]={
       { 0, -1,6,0.500000,0.500000,  0,  5,  6,  0,67,247,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x50x1[1]={
       { 0, 20,1,-0.003906,-0.003906,  0, 20, 30,  0,81,28,0,93,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x50x2[1]={
       { 0, -1,5,0.500000,0.500000,  0,  5,  5,  0,83,43,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x50x4[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,83,71,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x50x5[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,83,91,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x50x6[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,83,111,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x50x7[1]={
       { 0, -1,4,0.500000,0.500000,  0,  5,  4,  0,83,123,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x50x9[1]={
       { 0, -1,6,0.500000,0.500000,  0,  5,  6,  0,83,155,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x50xb[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,83,176,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x50xf[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,87,247,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x60[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,99,11,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x60x1[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,103,31,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x60x2[2]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,100,43,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,103,39,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x60x4[1]={
       { 0, -1,1,0.000000,0.500000,  0,  5,  1,  0,103,71,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x60x5[1]={
       { 0, -1,6,0.500000,0.000000,  0,  5,  6,  0,103,91,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x60x6[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,103,111,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x60x8[1]={
       { 0, -1,4,0.500000,0.500000,  0,  5,  4,  0,102,138,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x60x9[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,103,159,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x60xa[1]={
       { 0, -1,1,0.000000,0.500000,  0,  5,  1,  0,103,175,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x60xf[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,107,247,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x70xe[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,119,235,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0x70xf[1]={
       { 0, -1,6,0.500000,0.500000,  0,  5,  6,  0,119,247,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xd0[1]={
       { 0, 66,1,-0.003906,-0.003906,  0,9000,  0,  0,221,15,0,13,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xd0xe[1]={
       { 0, 68,1,-0.003906,-0.003906,  0,9000,  0,  0,223,229,0,51,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xe0[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  2,  0,227,15,0,5,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xe0x2[2]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,227,35,0,25,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,239,35,0,5,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xe0x3[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,231,59,0,34,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xe0x4[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,231,79,0,34,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xe0x6[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,231,99,0,34,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xe0x7[1]={
       { 0, 15,1,-0.003906,-0.003906,  0, 15, 20,  0,228,122,0,41,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xe0x8[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,227,135,0,43,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xe0x9[1]={
       { 0, -1,5,0.500000,0.500000,  0,  5,  5,  0,227,155,0,43,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xe0xa[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,231,175,0,34,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xe0xc[2]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,231,195,0,34,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,231,207,0,65,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xe0xe[1]={
       { 0, -1,6,0.500000,0.500000,  0,  5,  6,  0,231,227,0,34,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xe0xf[1]={
       { 0, -1,4,0.500000,0.000000,  0,  5,  4,  0,231,247,0,34,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xf0[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,247,15,0,0,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xf0x3[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,243,59,0,5,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xf0x4[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,243,79,0,6,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xf0x6[1]={
       { 0, -1,6,0.500000,0.500000,  0,  5,  6,  0,243,99,0,7,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xf0x7[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,243,115,0,7,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xf0x8[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,247,135,0,0,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xf0x9[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,247,155,0,0,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLS0xf0xf[1]={
       { 0, -1,7,0.500000,0.500000,  0,  5,  7,  0,247,247,0,0,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };



building_area bldg_lvlLS[(WORLD_SIZE>>RES_SHFT_DIVISOR)][(WORLD_SIZE>>RES_SHFT_DIVISOR)]={{
       {1,bldgLS00},
       {1,bldgLS00x1},
       {0,NULL},
       {1,bldgLS00x3},
       {1,bldgLS00x4},
       {1,bldgLS00x5},
       {1,bldgLS00x6},
       {1,bldgLS00x7},
       {0,NULL},
       {1,bldgLS00x9},
       {1,bldgLS00xa},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLS00xf},},{
       {1,bldgLS0x10},
       {1,bldgLS0x10x1},
       {0,NULL},
       {1,bldgLS0x10x3},
       {2,bldgLS0x10x4},
       {1,bldgLS0x10x5},
       {1,bldgLS0x10x6},
       {1,bldgLS0x10x7},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},},{
       {1,bldgLS0x20},
       {1,bldgLS0x20x1},
       {0,NULL},
       {1,bldgLS0x20x3},
       {1,bldgLS0x20x4},
       {1,bldgLS0x20x5},
       {1,bldgLS0x20x6},
       {1,bldgLS0x20x7},
       {0,NULL},
       {1,bldgLS0x20x9},
       {1,bldgLS0x20xa},
       {1,bldgLS0x20xb},
       {1,bldgLS0x20xc},
       {1,bldgLS0x20xd},
       {1,bldgLS0x20xe},
       {1,bldgLS0x20xf},},{
       {1,bldgLS0x30},
       {1,bldgLS0x30x1},
       {1,bldgLS0x30x2},
       {0,NULL},
       {1,bldgLS0x30x4},
       {1,bldgLS0x30x5},
       {1,bldgLS0x30x6},
       {1,bldgLS0x30x7},
       {0,NULL},
       {1,bldgLS0x30x9},
       {1,bldgLS0x30xa},
       {1,bldgLS0x30xb},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLS0x30xf},},{
       {2,bldgLS0x40},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLS0x40x4},
       {1,bldgLS0x40x5},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLS0x40x9},
       {0,NULL},
       {1,bldgLS0x40xb},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLS0x40xf},},{
       {0,NULL},
       {1,bldgLS0x50x1},
       {1,bldgLS0x50x2},
       {0,NULL},
       {1,bldgLS0x50x4},
       {1,bldgLS0x50x5},
       {1,bldgLS0x50x6},
       {1,bldgLS0x50x7},
       {0,NULL},
       {1,bldgLS0x50x9},
       {0,NULL},
       {1,bldgLS0x50xb},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLS0x50xf},},{
       {1,bldgLS0x60},
       {1,bldgLS0x60x1},
       {2,bldgLS0x60x2},
       {0,NULL},
       {1,bldgLS0x60x4},
       {1,bldgLS0x60x5},
       {1,bldgLS0x60x6},
       {0,NULL},
       {1,bldgLS0x60x8},
       {1,bldgLS0x60x9},
       {1,bldgLS0x60xa},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLS0x60xf},},{
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
       {1,bldgLS0x70xe},
       {1,bldgLS0x70xf},},{
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
       {1,bldgLS0xd0},
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
       {1,bldgLS0xd0xe},
       {0,NULL},},{
       {1,bldgLS0xe0},
       {0,NULL},
       {2,bldgLS0xe0x2},
       {1,bldgLS0xe0x3},
       {1,bldgLS0xe0x4},
       {0,NULL},
       {1,bldgLS0xe0x6},
       {1,bldgLS0xe0x7},
       {1,bldgLS0xe0x8},
       {1,bldgLS0xe0x9},
       {1,bldgLS0xe0xa},
       {0,NULL},
       {2,bldgLS0xe0xc},
       {0,NULL},
       {1,bldgLS0xe0xe},
       {1,bldgLS0xe0xf},},{
       {1,bldgLS0xf0},
       {0,NULL},
       {0,NULL},
       {1,bldgLS0xf0x3},
       {1,bldgLS0xf0x4},
       {0,NULL},
       {1,bldgLS0xf0x6},
       {1,bldgLS0xf0x7},
       {1,bldgLS0xf0x8},
       {1,bldgLS0xf0x9},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLS0xf0xf},},
       };


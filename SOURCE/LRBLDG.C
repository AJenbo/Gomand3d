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
     building bldgLR0x10x1[1]={
       { 0, 66,1,-0.003906,-0.003906,  0,9000,  0,  0,16,22,0,17,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0x20xd[1]={
       { 0, 13,1,-0.003906,-0.003906,  0, 15, 25,  0,36,222,0,207,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0x30x2[2]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,51,47,0,2,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,60,47,0,2,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0x30x3[2]={
       { 0, -1,3,0.500000,0.500000,  0,  5,  3,  0,51,56,0,2,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,60,56,0,2,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0x30x4[2]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,51,65,0,2,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,2,0.500000,0.000000,  0,  5,  2,  0,61,65,0,2,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0x40x2[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,69,47,0,2,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0x40x3[1]={
       { 0, -1,2,0.500000,0.000000,  0,  5,  2,  0,69,56,0,2,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0x40x4[1]={
       { 0, -1,4,0.000000,0.500000,  0,  5,  4,  0,69,65,0,2,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0x70x1[1]={
       { 0, -1,3,0.500000,0.500000,  0,  5,  3,  0,124,29,0,206,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0x70x2[3]={
       { 0, -1,4,0.000000,0.500000,  0,  5,  4,  0,124,37,0,206,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,124,46,0,206,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,115,42,0,206,{{0,0,0},{0,0,0}},0,0,0},          // Building #-2
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0x70x3[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,124,55,0,206,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0x70x7[1]={
       { 0, 15,1,-0.003906,-0.003906,  0, 20, 34,  0,121,125,0,206,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0x80x2[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,133,42,0,206,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0x80xd[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,135,220,0,2,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0x90xd[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,144,220,0,2,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0xa0xe[1]={
       { 0, 68,1,-0.003906,-0.003906,  0,9000,  0,  0,174,224,0,7,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0xb0x6[1]={
       { 0, 20,1,-0.003906,-0.003906,  0, 30, 45,  0,183,102,0,2,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0xb0x7[2]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,182,117,0,2,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,191,117,0,2,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0xc0x6[1]={
       { 0, -1,3,0.500000,0.500000,  0,  5,  3,  0,200,108,0,2,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0xd0x6[2]={
       { 0, -1,2,0.500000,0.500000,  0,  5,  2,  0,210,99,0,2,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,2,0.500000,0.500000,  0,  5,  2,  0,210,108,0,2,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0xd0x7[1]={
       { 0, -1,2,0.500000,0.000000,  0,  5,  2,  0,210,117,0,2,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLR0xe0xa[1]={
       { 0, 67,1,-0.003906,-0.003906,  0,9000,  0,  0,238,166,0,16,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };



building_area bldg_lvlLR[(WORLD_SIZE>>RES_SHFT_DIVISOR)][(WORLD_SIZE>>RES_SHFT_DIVISOR)]={{
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
       {1,bldgLR0x10x1},
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
       {1,bldgLR0x20xd},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {2,bldgLR0x30x2},
       {2,bldgLR0x30x3},
       {2,bldgLR0x30x4},
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
       {1,bldgLR0x40x2},
       {1,bldgLR0x40x3},
       {1,bldgLR0x40x4},
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
       {1,bldgLR0x70x1},
       {3,bldgLR0x70x2},
       {1,bldgLR0x70x3},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLR0x70x7},
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
       {1,bldgLR0x80x2},
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
       {1,bldgLR0x80xd},
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
       {1,bldgLR0x90xd},
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
       {1,bldgLR0xa0xe},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLR0xb0x6},
       {2,bldgLR0xb0x7},
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
       {1,bldgLR0xc0x6},
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
       {2,bldgLR0xd0x6},
       {1,bldgLR0xd0x7},
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
       {1,bldgLR0xe0xa},
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


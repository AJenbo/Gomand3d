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


#include "rl2d3d.h"

#define WORLD_SIZE  256     // The World's current Width & Height in Units.                    
#define RES_SHFT_DIVISOR 4  // Value for dividing the 256 world resolution by Powers of 2.     


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
    struct _GDPLIST *displist;  //  Pointer To The Display List.                                       
    RLIMTriangle    *trilist;   // Pointer to the Triangle list of this building.              
}building;                                                                                     


typedef struct _building_area_                                                                 
{                                                                                              
    int count;                  //  The Number of Buildings in that area.                      
    building *building_ptr;     //  An Array of building Pointers.                             
}building_area;                                                                                



//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x10x7[1]={
       { 0, 67,1,-0.003906,-0.003906,  0,9000,  0,  0,16,113,0,132,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x20x1[1]={
       { 0, 20,1,-0.003906,-0.003906,  0, 20, 40,  0,33,27,0,9,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x20xe[1]={
       { 0, 66,1,-0.003906,-0.003906,  0,9000,  0,  0,32,228,0,69,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x40x7[1]={
       { 0, -1,2,0.500000,0.000000,  0,  5,  2,  0,71,123,0,38,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x40x8[2]={
       { 0, -1,4,0.500000,0.500000,  0,  5,  4,  0,73,131,0,41,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,4,0.500000,0.500000,  0,  5,  4,  0,75,139,0,43,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x40x9[1]={
       { 0, -1,2,0.500000,0.000000,  0,  5,  2,  0,76,154,0,48,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x40xa[2]={
       { 0, -1,4,0.500000,0.500000,  0,  5,  4,  0,75,163,0,51,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,2,0.500000,0.000000,  0,  5,  2,  0,75,171,0,53,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x50x5[2]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,85,85,0,27,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,85,93,0,29,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x50x6[2]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,81,103,0,32,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,2,0.500000,0.000000,  0,  5,  2,  0,89,103,0,32,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x50xb[2]={
       { 0, -1,2,0.500000,0.000000,  0,  5,  2,  0,85,186,0,58,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,94,190,0,59,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x60x4[2]={
       { 0, -1,3,0.000000,0.000000,  0,  5,  3,  0,97,72,0,23,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,111,78,0,24,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x60x5[2]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,97,80,0,25,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,97,89,0,28,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x60x6[3]={
       { 0, -1,3,0.500000,0.500000,  0,  5,  3,  0,97,96,0,30,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,4,0.500000,0.500000,  0,  5,  4,  0,97,103,0,32,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       { 0, -1,2,0.500000,0.000000,  0,  5,  2,  0,105,103,0,32,{{0,0,0},{0,0,0}},0,0,0},          // Building #-2
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x60xb[1]={
       { 0, -1,2,0.500000,0.000000,  0,  5,  2,  0,103,188,0,58,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x70x4[1]={
       { 0, -1,2,0.500000,0.000000,  0,  5,  2,  0,120,78,0,24,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x70x5[2]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,113,91,0,28,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,121,91,0,28,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x70x6[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,122,103,0,32,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x70x8[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,122,140,0,44,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x70x9[2]={
       { 0, -1,4,0.500000,0.500000,  0,  5,  4,  0,119,149,0,46,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,127,149,0,46,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x70xb[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,124,180,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x80x4[2]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,128,78,0,24,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,2,0.500000,0.500000,  0,  5,  2,  0,137,78,0,24,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x80x5[2]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,129,91,0,28,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,137,91,0,28,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x80x6[2]={
       { 0, -1,2,0.500000,0.000000,  0,  5,  2,  0,134,103,0,32,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,4,0.500000,0.500000,  0,  5,  4,  0,142,103,0,32,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x80x8[1]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,135,140,0,44,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x80x9[2]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,135,149,0,46,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,2,0.500000,0.000000,  0,  5,  2,  0,143,149,0,46,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x80xb[2]={
       { 0, -1,2,0.500000,0.000000,  0,  5,  2,  0,133,180,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,4,0.500000,0.500000,  0,  5,  4,  0,141,180,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x90x5[1]={
       { 0, -1,4,0.500000,0.500000,  0,  5,  4,  0,156,91,0,28,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x90x6[2]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,150,103,0,32,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,158,103,0,32,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x90x8[1]={
       { 0, 68,1,-0.003906,-0.003906,  0,9000,  0,  0,154,128,0,40,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0x90xb[2]={
       { 0, -1,4,0.500000,0.500000,  0,  5,  4,  0,149,180,0,69,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,157,180,0,56,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0xa0x5[1]={
       { 0, -1,2,0.500000,0.000000,  0,  5,  2,  0,165,95,0,30,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0xa0x6[1]={
       { 0, -1,2,0.500000,0.000000,  0,  5,  2,  0,166,103,0,32,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0xa0x9[1]={
       { 0, -1,2,0.500000,0.000000,  0,  5,  2,  0,166,157,0,49,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0xa0xa[2]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,166,165,0,51,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,168,173,0,54,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0xb0x1[1]={
       { 0, 13,1,-0.003906,-0.003906,  0, 10, 15,  0,177,22,0,7,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0xb0x6[2]={
       { 0, -1,4,0.500000,0.500000,  0,  5,  4,  0,177,99,0,31,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,2,0.500000,0.000000,  0,  5,  2,  0,182,109,0,34,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0xb0x7[2]={
       { 0, -1,2,0.500000,0.000000,  0,  5,  2,  0,188,116,0,36,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,2,0.500000,0.000000,  0,  5,  2,  0,182,125,0,69,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0xb0x8[1]={
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,182,132,0,69,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0xd0x6[2]={
       { 0, -1,3,0.000000,0.500000,  0,  5,  3,  0,215,111,0,35,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       { 0, -1,3,0.500000,0.000000,  0,  5,  3,  0,223,111,0,35,{{0,0,0},{0,0,0}},0,0,0},          // Building #-1
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0xe0x7[1]={
       { 0, -1,2,0.000000,0.500000,  0,  5,  2,  0,231,112,0,66,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };

//     vis,  bldnum,  scale,  tu,  tv,  idmg,  mdmg,  monpwr,  Robotpwr,  x,  z,  dir,  y,  bm1x,  bm1y,  bm1z,  bm2x,  bm2y,  bm2z,  rl,  disp,  trilist
     building bldgLH0xe0xb[1]={
       { 0, 15,1,-0.003906,-0.003906,  0, 15, 20,  0,231,189,0,69,{{0,0,0},{0,0,0}},0,0,0},          // Building #-0
       };



building_area bldg_lvlLH[(WORLD_SIZE>>RES_SHFT_DIVISOR)][(WORLD_SIZE>>RES_SHFT_DIVISOR)]={{
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
       {1,bldgLH0x10x7},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {1,bldgLH0x20x1},
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
       {1,bldgLH0x20xe},
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
       {1,bldgLH0x40x7},
       {2,bldgLH0x40x8},
       {1,bldgLH0x40x9},
       {2,bldgLH0x40xa},
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
       {2,bldgLH0x50x5},
       {2,bldgLH0x50x6},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {2,bldgLH0x50xb},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {2,bldgLH0x60x4},
       {2,bldgLH0x60x5},
       {3,bldgLH0x60x6},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLH0x60xb},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLH0x70x4},
       {2,bldgLH0x70x5},
       {1,bldgLH0x70x6},
       {0,NULL},
       {1,bldgLH0x70x8},
       {2,bldgLH0x70x9},
       {0,NULL},
       {1,bldgLH0x70xb},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {2,bldgLH0x80x4},
       {2,bldgLH0x80x5},
       {2,bldgLH0x80x6},
       {0,NULL},
       {1,bldgLH0x80x8},
       {2,bldgLH0x80x9},
       {0,NULL},
       {2,bldgLH0x80xb},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLH0x90x5},
       {2,bldgLH0x90x6},
       {0,NULL},
       {1,bldgLH0x90x8},
       {0,NULL},
       {0,NULL},
       {2,bldgLH0x90xb},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLH0xa0x5},
       {1,bldgLH0xa0x6},
       {0,NULL},
       {0,NULL},
       {1,bldgLH0xa0x9},
       {2,bldgLH0xa0xa},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},},{
       {0,NULL},
       {1,bldgLH0xb0x1},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {2,bldgLH0xb0x6},
       {2,bldgLH0xb0x7},
       {1,bldgLH0xb0x8},
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
       {2,bldgLH0xd0x6},
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
       {1,bldgLH0xe0x7},
       {0,NULL},
       {0,NULL},
       {0,NULL},
       {1,bldgLH0xe0xb},
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


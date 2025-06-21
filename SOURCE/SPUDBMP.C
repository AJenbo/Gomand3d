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
File:           spudbmp.c
Author:         Bruce Abe
Date:           9-29-95
Version:        1.0



************************************************************************
REVISION HISTORY        (Add Edits and History to top of list).

Edited By:      editors_name.here
Edited Date:    edited_date.here
Changes:
                changed VERSION_NUMBER from THIS to THAT.
                changed this item from this to that.
                changed that item from that to that.


***********************************************************************/

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

#include "rl2d3d.h"

#include "stdio.h"
#include "keycom.h"
#include "spudbmp.h"
#include "landscap.h"
#include "gosys.h"
#include "ybsnd.h"
#include "boink.h"
#include "building.h" 

#define abs(x) ((x) > 0 ? (x) : -(x))
//#ifdef __psx__
//#define RLInt(x) ((x)/65536)
//#endif
//#define BuildingDistance RLVal(0.5)
//visible_buildings CollideBuildings;  // Structure of Collision Buildings.

//const RLValue CloseQuarters=RLVal(5);
//RLValue MinDistanceFromRobotToMonster = RLVal(3);

RLValue MaxHeightDifference = RLVal(3.0);
//RLValue MapHeight(int x, int y);			//  +++ ADDED for LANDSCAP.C

/*
void SpuddeCheckSlopeWalking(int x1, int y1, int x2, int y2, int *x3, int *y3)
{
   int xlength=abs(x2-x1);
   int ylength=abs(y2-y1);
   int OrigHeight=SpuddeMapHeight(x1,y1);
   int CurrentHeight;
   int PaceThrough;
   int raiselevel;
   int remainder;
   int HopThrough;
   int Hopped;
   int half;
   if(xlength>ylength)
   {
      half=xlength/2;
      //This is so I can tell which direction in the pixmap I should move when Bresenham's algorithm
      //tells me to go.
      if(y1<y2)
         raiselevel=256;
      else
         raiselevel=-256;
      HopThrough=y1*256;
      remainder=0;
      if(x1<x2)
      {
         for(PaceThrough=x1;PaceThrough<x2;)
         {
            ++PaceThrough;
            remainder+=ylength;
            if(remainder>half)
            {
               remainder-=xlength;
               HopThrough+=raiselevel;
               Hopped=1;
            }
            else
               Hopped=0;
            CurrentHeight=SpuddeMapHeight1(PaceThrough+HopThrough);
            if(CurrentHeight-OrigHeight>MaxHeightDifference)
            {
               PaceThrough--;
               if(Hopped)
               {
                  HopThrough-=raiselevel;
               }
               break;
            }
         }
      }
      else
      {
         for(PaceThrough=x1;PaceThrough>x2;)
         {
            --PaceThrough;
            remainder+=ylength;
            if(remainder>half)
            {
               remainder-=xlength;
               HopThrough+=raiselevel;
               Hopped=1;
            }
            else
               Hopped=0;
            CurrentHeight=SpuddeMapHeight1(PaceThrough+HopThrough);
            if(CurrentHeight-OrigHeight>MaxHeightDifference)
            {
               PaceThrough++;
               if(Hopped)
               {
                  HopThrough-=raiselevel;
               }
               break;
            }
         }
      }
   }
   else//ylength>xlength
   {
      int FinalY=y2*256;
      half=ylength/2;
      //This is so I can tell which direction in the pixmap I should move when Bresenham's algorithm
      //tells me which direction to go.
      if(x1<x2)
         raiselevel=1;
      else
         raiselevel=0;
      PaceThrough=x1;
      remainder=0;
      if(y1>y2)
      {
         for(HopThrough=y1*256;HopThrough>FinalY;)
         {
            HopThrough-=256;
            remainder+=xlength;
            if(remainder>half)
            {
               remainder-=ylength;
               if(raiselevel)
                  PaceThrough++;
               else
                  PaceThrough--;
               Hopped=1;
            }
            else
               Hopped=0;
            CurrentHeight=SpuddeMapHeight1(PaceThrough+HopThrough);
            if(CurrentHeight-OrigHeight>MaxHeightDifference)
            {
               if(Hopped)
               {
                  if(raiselevel)
                  {
                     PaceThrough--;
                  }
                  else
                  {
                     PaceThrough++;
                  }
               }
               HopThrough+=256;
               break;
            }
         }
      }
      else
      {
         for(HopThrough=y1*256;HopThrough<FinalY;)
         {
            HopThrough+=256;
            remainder+=xlength;
            if(remainder>half)
            {
               remainder-=ylength;
               if(raiselevel)
                  PaceThrough++;
               else
                  PaceThrough--;
               Hopped=1;
            }
            else
               Hopped=0;
            CurrentHeight=SpuddeMapHeight1(PaceThrough+HopThrough);
            if(CurrentHeight-OrigHeight>MaxHeightDifference)
            {
               if(Hopped)
               {
                  if(raiselevel)
                  {
                     PaceThrough--;
                  }
                  else
                  {
                     PaceThrough++;
                  }
               }
               HopThrough-=256;
               break;
            }
         }
      }
   }
   //At this point, PaceThrough is the last cool x position, and HopThrough is the last cool y position times 256.
   *x3=PaceThrough;
   *y3=HopThrough/256;
}

int SpuddeCheckSlopeAirborne(int x1, int y1, RLValue Height1, int x2, int y2, RLValue Height2, int *x3, int *y3, RLValue *Height3)
{//This function returns 1 if the object collided with the side of the wall, -1 if it landed, 0 if it's still airborne.
   int xlength=abs(x2-x1);
   int ylength=abs(y2-y1);
   RLValue CurrentMapHeight;//The height of the map here.
   RLValue LastMapHeight=SpuddeMapHeight(x1,y1);
   RLValue ObjectHeight;//The height of the object.
   RLValue LastObjectHeight=Height1;
   RLValue t,invt;
   int XWalk;
   int raiselevel;
   int remainder;
   int YWalk;
   int Hopped;
   int half;
   int bonk=0;

   if(xlength>ylength)
   {
      half=xlength/2;
      //This is so I can tell which direction in the pixmap I should move when Bresenham's algorithm
      //tells me to go.
      if(y1<y2)
         raiselevel=1;
      else
         raiselevel=-1;
      YWalk=y1;
      remainder=0;
      if(x1<x2)
      {
         for(XWalk=x1;XWalk<x2;)
         {
            ++XWalk;
            remainder+=ylength;
            if(remainder>half)
            {
               remainder-=xlength;
               YWalk+=raiselevel;
               Hopped=1;
            }
            else
               Hopped=0;
            CurrentMapHeight=SpuddeMapHeight1(XWalk+(YWalk*256));
            t=RLDivide(RLVal(XWalk-x1) , RLVal(x2-x1) );
            invt=RLDivide(RLVal(x2-XWalk), RLVal(x2-x1));
            ObjectHeight=RLMultiply(t,Height2) + RLMultiply(invt,Height1);
            if(CurrentMapHeight>ObjectHeight)
            {
               XWalk--;
               if(Hopped)
               {
                  YWalk-=raiselevel;
               }
               //Check to see if heights are discontinuous.
               if(CurrentMapHeight-LastMapHeight>MaxHeightDifference)
                  bonk=1;
               else
                  bonk=-1;
               break;
            }
            LastMapHeight=CurrentMapHeight;
            LastObjectHeight=ObjectHeight;
         }
      }
      else
      {
         for(XWalk=x1;XWalk>x2;)
         {
            --XWalk;
            remainder+=ylength;
            if(remainder>half)
            {
               remainder-=xlength;
               YWalk+=raiselevel;
               Hopped=1;
            }
            else
               Hopped=0;
            CurrentMapHeight=SpuddeMapHeight1(XWalk+(YWalk*256));
            t=RLDivide(RLVal(XWalk-x1) , RLVal(x2-x1) );
            invt=RLDivide(RLVal(x2-XWalk), RLVal(x2-x1));
            ObjectHeight=RLMultiply(t,Height2) + RLMultiply(invt,Height1);

            if(CurrentMapHeight>ObjectHeight)
            {
               XWalk++;
               if(Hopped)
               {
                  YWalk-=raiselevel;
               }
               //Check to see if heights are discontinuous.
               if(CurrentMapHeight-LastMapHeight>MaxHeightDifference)
                  bonk=1;
               else bonk=-1;
               break;
            }
            LastMapHeight=CurrentMapHeight;
            LastObjectHeight=ObjectHeight;
         }
      }
   }
   else//ylength>xlength
   {
      int FinalY=y2;
      half=ylength/2;
      //This is so I can tell which direction in the pixmap I should move when Bresenham's algorithm
      //tells me which direction to go.
      if(x1<x2)
         raiselevel=1;
      else
         raiselevel=0;
      XWalk=x1;
      remainder=0;
      if(y1>y2)
      {
         for(YWalk=y1;YWalk>FinalY;)
         {
            YWalk--;
            remainder+=xlength;
            if(remainder>half)
            {
               remainder-=ylength;
               if(raiselevel)
                  XWalk++;
               else
                  XWalk--;
               Hopped=1;
            }
            else
               Hopped=0;
            CurrentMapHeight=SpuddeMapHeight1(XWalk+(YWalk*256));
            t=RLDivide(RLVal(YWalk-y1) , RLVal(y2-y1) );
            invt=RLDivide(RLVal(y2-YWalk), RLVal(y2-y1));
            ObjectHeight=RLMultiply(t,Height2) + RLMultiply(invt,Height1);
            if(CurrentMapHeight>ObjectHeight)
            {
               if(Hopped)
               {
                  if(raiselevel)
                  {
                     XWalk--;
                  }
                  else
                  {
                     XWalk++;
                  }
               }
               YWalk++;
               //Check to see if heights are discontinuous.
               if(CurrentMapHeight-LastMapHeight>MaxHeightDifference)
                  bonk=1;
               else bonk=-1;
               break;
            }
            LastMapHeight=CurrentMapHeight;
            LastObjectHeight=ObjectHeight;
         }
      }
      else
      {
      
         for(YWalk=y1;YWalk<FinalY;)
         {
            YWalk++;
            remainder+=xlength;
            if(remainder>half)
            {
               remainder-=ylength;
               if(raiselevel)
                  XWalk++;
               else
                  XWalk--;
               Hopped=1;
            }
            else
               Hopped=0;
            CurrentMapHeight=SpuddeMapHeight1(XWalk+(YWalk*256));
            t=RLDivide(RLVal(YWalk-y1) , RLVal(y2-y1) );
            invt=RLDivide(RLVal(y2-YWalk), RLVal(y2-y1));
            ObjectHeight=RLMultiply(t,Height2) + RLMultiply(invt,Height1);
            if(CurrentMapHeight>ObjectHeight)
            {
               if(Hopped)
               {
                  if(raiselevel)
                  {
                     XWalk--;
                  }
                  else
                  {
                     XWalk++;
                  }
               }
               YWalk--;
               //Check to see if heights are discontinuous.
               if(CurrentMapHeight-LastMapHeight>MaxHeightDifference)
                  bonk=1;
               else bonk=-1;
               break;
            }
            LastMapHeight=CurrentMapHeight;
            LastObjectHeight=ObjectHeight;
         }
      }
   }
   //At this point, PaceThrough is the last cool x position, and YWalk is the last cool y position.
   *x3=XWalk;
   *y3=YWalk;
   *Height3=LastObjectHeight;
   return bonk;
}
*/

RLValue GradX(RLValue x, RLValue z)
{
   return SpuddeMapHeight2(x + RLVal(0.5), z) - SpuddeMapHeight2(x - RLVal(0.5), z);
}

RLValue GradZ(RLValue x, RLValue z)
{
   return SpuddeMapHeight2(x, z + RLVal(0.5)) - SpuddeMapHeight2(x, z - RLVal(0.5));
}

void GetGradient(RLVector* gradient, RLValue x, RLValue z)
{
	gradient->x = GradX(x, z);
	gradient->z = GradZ(x, z);
	gradient->y = RLVal(1);
}

int SpuddeMoveOnGround(MovingObjectData moveme, RLVector *velocity, RLValue *Gravity)
{
//   RLValue OldHeight;
   int midair = 0;
   int HitObstacle = 0;
   RLVector   position;
   extern RLFrame Robotframe;
//   RLVector   OpPosition;
//   RLVector   Difference;
//   RLValue  NormSquare;
   RLFrame scene = RLFrameGetScene(moveme->PositioningFrame);
//   int x1,y1,x2,y2,x3,y3;
   RLValue X1, Y1, Z1, X2, Y2, Z2;//,X3,Y3,Z3;
   RLVector gradient;
   RLValue denominator, ForceX, ForceZ, dummy;
//   if(moveme->PositioningFrame==Robotframe)
//      Gravity=-0.3;
   RLFrameGetPosition(moveme->PositioningFrame, scene, &position);
   X1 = position.x;
   Z1 = position.z;
   Y1 = position.y;
   moveme->CurrentPosition.x = X1;
   moveme->CurrentPosition.y = Y1;
   moveme->CurrentPosition.z = Z1;
   if(*Gravity == 0)
   {
	  X2 = X1+velocity->x;
	  Z2 = Z1+velocity->z;
   }
   else
   {
      GetGradient(&gradient, X1, Z1);
      //gradient.x = GradX(X1,Z1);
	  //gradient.z = GradZ(X1,Z1);
	  //gradient.y=1;
	  denominator = RLVectorModulus(&gradient);
	  dummy = RLDivide(*Gravity, denominator);
	  ForceX = RLMultiply(gradient.x, dummy);
	  ForceZ = RLMultiply(gradient.z, dummy);

	  X2 = X1 + velocity->x + ForceX;
	  Z2 = Z1 + velocity->z + ForceZ;
   }

	if ((X2 > landbox.max.x) || (X2 < landbox.min.x) || (Z2 < landbox.min.z) || (Z2 > landbox.max.z)) 
	{
       if(X2 > landbox.max.x)
       {
          X2 = landbox.max.x;
	   }
       if(X2 < landbox.min.x)
	   {
          X2 = landbox.min.x;
	   }
       if(Z2 < landbox.min.z)
	   {
          Z2 = landbox.min.z;
	   }
       if(Z2 > landbox.max.z)
	   {
          Z2 = landbox.max.z;
	   }
	}


   Y2 = SpuddeMapHeight2(X2, Z2);
/*   if(Y2-Y1>MaxHeightDifference)
   {
      HitObstacle=2;
      moveme->ProjectedPosition.x=X1;
      moveme->ProjectedPosition.y=Y1;
      moveme->ProjectedPosition.z=Z1;
      moveme->collisionflag=1;
      moveme->CollisionVector.x=X1-X2;
      moveme->CollisionVector.y=Y1-Y2;
      moveme->CollisionVector.z=Z1-Z2;
   }
   else if (Y1-Y2>MaxHeightDifference)
   {
      midair=1;
      moveme->ProjectedPosition.x=X2;
      moveme->ProjectedPosition.y=Y1;
      moveme->ProjectedPosition.z=Z2;
   }
   else
   {*/
      moveme->ProjectedPosition.x = X2;
      moveme->ProjectedPosition.y = Y2;
      moveme->ProjectedPosition.z = Z2;
   /*}*/

   return midair|HitObstacle;
}

int SpuddeMoveInAir(MovingObjectData moveme, RLVector *velocity)
{
   int airborne = 1;
   int HitObstacle = 0;
//   int x1,y1,x2,y2,x3,y3;
   RLValue X1, Y1, Z1, X2, Y2, Z2, h1, h3;
//   RLValue h2=RLVal(0.0);
   RLFrame scene = RLFrameGetScene(moveme->PositioningFrame);
   RLVector   position;
  // RLVector   OpPosition;
//   RLVector   Difference;
//   RLValue  NormSquare;

   RLFrameGetPosition(moveme->PositioningFrame, scene, &position);
//   RLFrameGetPosition(Opposition,scene,&OpPosition);
   X1 = position.x;
   Y1 = position.y;
   Z1 = position.z;
   moveme->CurrentPosition.x = X1;
   moveme->CurrentPosition.y = Y1;
   moveme->CurrentPosition.z = Z1;
   X2 = X1 + velocity->x;
   Y2 = Y1 + velocity->y;
   Z2 = Z1 + velocity->z;
   if(X2 > landbox.max.x)
   {
      X2 = landbox.max.x;
   }
   if(X2 < landbox.min.x)
   {
      X2 = landbox.min.x;
   }
   if(Z2 < landbox.min.z)
   {
      Z2 = landbox.min.z;
   }
   if(Z2 > landbox.max.z)
   {
      Z2 = landbox.max.z;
   }
   h3 = SpuddeMapHeight2(X2, Z2);
   h3 = h3 - Y2;
  // h3=h3;


   if(h3 < RLVal(0.0))//still airborne
   {
      moveme->ProjectedPosition.x = X2;
      moveme->ProjectedPosition.y = Y2;
      moveme->ProjectedPosition.z = Z2;

   }
   else
   {
      if(h3 > MaxHeightDifference)
      {
         HitObstacle = 2;
         moveme->ProjectedPosition.x = X1;
         moveme->ProjectedPosition.z = Z1;
         moveme->ProjectedPosition.y = Y1;
      }
      else
      {
         airborne = 0;
         h1 = Y1 - SpuddeMapHeight2(X1, Z1);
         moveme->ProjectedPosition.x = (h1 * X2 + h3 * X1) / (h1 + h3);
         moveme->ProjectedPosition.z = (h1* Z2 + h3 * Z1) / (h1 + h3);
         moveme->ProjectedPosition.y = SpuddeMapHeight2(moveme->ProjectedPosition.x, moveme->ProjectedPosition.z);
      }
   }


   return (airborne | HitObstacle);
}


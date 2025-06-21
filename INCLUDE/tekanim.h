/***********************************************************************
        (C) Copyright 1996 by 47-TEK, Inc.

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

Program:        goman.exe
File:           TekAnim.h
Author:         Bruce Abe
Date:           June 13, 1996



   Update:
   Date		      Name		   Description
   ====================================================

   July 9, 1996   Bruce Abe   Removed 
            #ifdef KevinIsntFinishedYet's from the file.


************************************************************************
$Header:   H:/pvcs/pvcsproj/gomand3d.prj/tekanim.h_v   1.0   Oct 18 1996 16:16:00   JEREMIAH  $


$Log:   H:/pvcs/pvcsproj/gomand3d.prj/tekanim.h_v  $
 * 
 *    Rev 1.0   Oct 18 1996 16:16:00   JEREMIAH
 *  
 * 
 *    Rev 1.0   21 Feb 1996 16:06:24   KEVIN
 *  


***********************************************************************/

#ifndef __TEKANIM_H__
#define __TEKANIM_H__



//*******************************
//*****                     *****
//*****     Header Files    *****
//*****                     *****
//*******************************

#ifdef MINIWIN
#include "miniwin/d3drm.h"
#else
#include <d3drmwin.h>
#endif

//*******************************
//*****                     *****
//***** MACROS              *****
//*****                     *****
//*******************************

#undef RELEASE
#ifdef __cplusplus
#define RELEASE(x) if (x != NULL) {x->Release(); x = NULL;}
#else
#define RELEASE(x) if (x != NULL) {x->lpVtbl->Release(x); x = NULL;}
#endif
//*******************************
//*****                     *****
//*****      Typedefs       *****
//*****                     *****
//*******************************

typedef unsigned char * DataPointer;

//*******************************
//*****                     *****
//*****      Structures     *****
//*****                     *****
//*******************************

//The following structures define the way animation data will be stored.
//They are designed with the goal of keeping the size of the data in memory
//to a minimum, to ease the use by the animation code of the program, and
//to be a direct overlay of the way the data is stored in binary files,
//to make loading and initialization as easy and quick as possible.

//A Scale Keyframe stores the information of how one body part is scaled
//at one time in an animation.
typedef struct _scale_keyframe_
{
   D3DVALUE Time;               //Animation Frame Number
   D3DVALUE x;                  //X Scale value
   D3DVALUE y;                  //Y Scale value
   D3DVALUE z;                  //Z Scale value
}ScaleKeyframe;

//A Rotation Keyframe stores the information of how one body part is
//oriented at one time in an animation.
typedef struct _rotation_keyframe_
{
    D3DVALUE Time;              //Animation Frame Number
    D3DRMQUATERNION Quaternion; //Orientation, stored in Quaternion form.
}RotationKeyframe;

//A Position Keyframe stores the information of how one body part is 
//positioned at one time in an animation.
typedef struct _position_keyframe_
{
   D3DVALUE Time;               //Animation Frame Number
   D3DVALUE x;                  //X Position value
   D3DVALUE y;                  //Y Position value
   D3DVALUE z;                  //Z Position value
}PositionKeyframe;


//An AnimationComponent stores all the animation information for one body
//part of a model, for one animation.
typedef struct _animation_component_
{
   PositionKeyframe *Positions; //Array of Position Keyframes
   unsigned long PositionNumber;//Number of Position Keyframe array elements
   RotationKeyframe *Rotations; //Array of Rotation Keyframes
   unsigned long RotationNumber;//Number of Rotation Keyframe array elements
   ScaleKeyframe    *Scales;    //Array of Scale Keyframes
   unsigned long ScaleNumber;   //Number of Scale Keyframe array elements
}AnimationComponent;

//A TekAnimation stores all the animation information for one complete 
//model, for one animation.
typedef struct _tek_animation_
{
   D3DVALUE AnimationLength;            //Length of the animation, in frames.
   unsigned long NumberOfParts;         //Number of body parts in the model.
   AnimationComponent **AnimationData;  //Array of Animation Components, one
                                        //for each body part.
}TekAnimation;

//A PackedAnimation stores all the animation information for one model and
//for one collection of animations.
typedef struct _packed_animations_
{
   TekAnimation **Animations;       //In the packed animation file, this
                                    //actually stores the file creator ID.
                                    //This is used by the packing tool in
                                    //case it is asked to pack a file which
                                    //has already been packed.  This is of
                                    //no use inside the game, so we instead
                                    //use this memory space as a pointer to
                                    //the array of animations that will 
                                    //follow.

   unsigned long NumberOfAnimations;//This stores the number of items stored
                                    //in the packed animation file.

//The next data in the file will be the array of pointers to animations,
//then the array of animation ID's.  There is a small amount of additional
//information after that, but it is of no use to us currently.  Animations
//will be set to point to the array of pointers to animations.
}PackedAnimations;

//The hierarchical model structure stores an array of pointers to the frames
//used to position individual body parts.  The array is stored in the same
//order as the array of animation components, so we can easily apply each
//animation component to the correct body part's frame.
typedef struct _hierarchical_model_
{
   LPDIRECT3DRMFRAME     *ObjectCoordinates;  // This array stores the 
                                              //positioning info of the 
                                              //parts of the model

   unsigned long          ObjectNumber;       // This is the number of 
                                              //elements in the above array
}HierarchicalModel;



//*******************************
//*****                     *****
//*****      Variables      *****
//*****                     *****
//*******************************

//These variables are here temporarily, for testing purposes.
//The actual game will not have these variables.
extern HierarchicalModel *SabreHierarchy;
extern DataPointer SabreData;



//*******************************
//*****                     *****
//*****      Prototypes     *****
//*****                     *****
//*******************************

//This function takes a pointer to raw data that has been read in
//from a packed animation file.  It processes the data into a collection
//of animations, which remain in the same place in memory as the raw
//data.  It returns the number of animations in the packed animation.
int PreprocessPackedAnimation(
         LPDIRECT3DRMFRAME pParentFrame, //root of the model these animations
                                         //belong to.

         unsigned long *packedanimation);//pointer to the raw data to be 
                                         //preprocessed.  The processed
                                         //data will be stored in the same
                                         //memory as the raw data.

//This function takes a pointer to raw data that has been read in from
//an animation file, or as part of a packed animation file.  It processes
//the data into an animation, which remains in the same place in memory
//as the raw data.
void PreprocessAnimation(
         unsigned long *animation);      //pointer to the raw data to be 
                                         //preprocessed.  The processed
//This function is temporary, until we have a way to store hierarchical
//information in a file.  It uses a global variable containing a list of 
//body part names in the order the parts will be stored in the animation
//file.  It searches through the tree rooted at ParentFrame for the body
//parts with the correct names, stores these into another global variable
//containing the Hierarchical model.
void PreprocessSabreHierarchy(
         LPDIRECT3DRMFRAME ParentFrame); //The base frame of the model

//This function takes a model, an animation, and a frame of that animation,
//and positions the model accordingly.
void TekApplyAnimation(
         HierarchicalModel *model,       //Array of body part frames.
         TekAnimation *KSAnim,           //Array of animation components.
         D3DVALUE time);                 //Which frame of the animation to 
                                         //play.

//This function searches a frame tree for a subframe with a specified name.
LPDIRECT3DRMFRAME 
      FindSubframeByName(
          LPDIRECT3DRMFRAME pParent, //pointer to the base frame
          char *pName);              //name string we're trying to match.
//This function open the file named pName, mallocs enough space in pData,
//and puts the file into the space created.  It returns 0 if unsuccessful,
//1 if successful.

int
LoadPackedAnimation(
                    char *pName,          //file name string
                    DataPointer *pData);  //pointer which will be set to 
                                          //point to space which will 
                                          //contain the file.
unsigned char *GetMonstNameFromTreData (int Num);
void GetMonstObjInfo (unsigned long int *pPackedAnimation);
unsigned char *GetRobotNameFromTreData (int Num);
void GetRobotObjInfo (unsigned long int *pPackedAnimation);

#endif

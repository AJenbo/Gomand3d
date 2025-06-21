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

Program:        Goman
File:           TekAnim.c
Author:         Bruce Abe
Date:           June 22, 1996

// Description:	This module contains code for utilizing 47-Tek's
//		            animation file format in conjunction with D3D.  It
//		            contains code for reading in packed animations and
//                preprocessing them, and for playing an animation with
//                a hierarchical model.  It also contains temporary code
//                to create a hierarchical model from hand-written data
//                about SabreRobot's model.
//
// Side Effects:	
//
// Function:	   AnimatePart
//                TekApplyAnimation
//                
//                FindSubframeByName
//                ProcessHierarchy
//                
//                PreprocessAnimation
//                PreprocessPackedAnimation
//                LoadPackedAnimation
//
// Notes:		   This module is now complete, up to bug fixes or changes
//                in the animation version.
//
// Update:
// Date		Name		Description
// ====================================================

   July 9, 1996
            Bruce Abe
            Removed #ifdef KevinIsntFinishedYet's from the file.
//
//
// Known restrictions:
//		The packed animation reader assumes that the file types contained
//    in the packed file will be one model hierarchy file (a .tre file)
//    followed by animations.  The data format has been designed with the 
//    assumption that different types of files can be packed together, but 
//    the reader doesn't currently support this feature.
//
// Known bugs:	



************************************************************************


***********************************************************************/






//*******************************
//*****                     *****
//*****     Header Files    *****
//*****                     *****
//*******************************
#include "tekanim.h"  /* anim data structures  */
#include <stdio.h>
#include <io.h>
#include <FCNTL.H>


/***********************************************************************/
extern int NumParts;
extern char PartNames[][19];
HierarchicalModel *SabreHierarchy;





// **********************************************************
// Name:		AnimatePart
//
// Author:	Bruce Abe
//
// Date:		June 22, 1996
//
// Description:	This function takes an animation component and a time.
//                It interpolates linearly between the keyframes closest
//                to that time, for scale, position, and orientation.  (It
//                uses a spherical linear interpolation for orientation.)
//                From these 3 factors, it then creates a transformation,
//                which it applies to the frame that's also passed in.
//
// Arguments:	   transform is the model's frame of reference.
//                anim is the animation component.
//                frame is the frame of the animation to play.
//
// Return:	      None.
//
// Side Effects:	
//
// Notes:		   
//
//    I'll step through each of the keyframes until I get one whose time 
//    value is greater than the frame I want.  If the first frame is the 
//    one, then I take that as the interpolated position by itself.  If 
//    there isn't one, then I take the last keyframe as the interpolated 
//    value.  (No attempt is made to extrapolate.)  If in between, then I 
//    interpolate between the first point whose time is greater than the 
//    frame I want, and the one before it.  The keyframes must be arranged
//    in ascending order, so these will be the times closest to the one I 
//    want.  
//
//    I interpolate based on the formula 
//          x(t) = (X1*(T2-t) + X2*(T1-t))/(T2-T1)
//
// Known restrictions:
//		            
// Error Number:	No errors are returned.  
//
// Update:
// Date		      Name		   Description
// ====================================================
// July 9, 1996   Bruce Abe   Removed code which converted times to floats,
//                            because the current animation file converter
//                            correctly stores times as floats.
// **********************************************************

static void 
AnimatePart(
    LPDIRECT3DRMFRAME pTransform,//The frame which must be positioned.
    AnimationComponent *pAnim,   //The animation
    D3DVALUE fFrame)             //The current animation frame.
{
   D3DVECTOR interpolatedScale;     //stores the current scale value.
   D3DVECTOR interpolatedPosition;  //stores the current position.
   D3DRMQUATERNION interpolatedQuaternion;//stores the current orientation.

   int i;                        //counter
   int numberOfKeys;             //Number of Keyframes of each type.
   int done;                     //Have I found the correct answer yet?
   D3DRMMATRIX4D matrix;         //The orientation matrix made from the 
                                 //quaternion, then put into pTransform.

   
   
//The first step is to get the interpolated position, scale, and rotations.

//interpolate position information
   numberOfKeys = pAnim->PositionNumber;
   done = 0;
   if (pAnim->Positions[0].Time > fFrame)
   {
      interpolatedPosition.x = pAnim->Positions[0].x;
      interpolatedPosition.y = pAnim->Positions[0].y;
      interpolatedPosition.z = pAnim->Positions[0].z;
      done = 1;
   }
   else
   {
      for (i = 1; ((i < numberOfKeys) && (!done)); ++i)
      {
         if (pAnim->Positions[i].Time > fFrame)
         {
            done = 1;
            interpolatedPosition.x = D3DDivide(
                  D3DMultiply(fFrame - pAnim->Positions[i - 1].Time, 
                              pAnim->Positions[i].x) +
                  D3DMultiply(pAnim->Positions[i].Time - fFrame, 
                              pAnim->Positions[i - 1].x),
                  pAnim->Positions[i].Time - pAnim->Positions[i - 1].Time);
            
            interpolatedPosition.y = D3DDivide(
                  D3DMultiply(fFrame - pAnim->Positions[i - 1].Time, 
                              pAnim->Positions[i].y) +
                  D3DMultiply(pAnim->Positions[i].Time - fFrame, 
                              pAnim->Positions[i - 1].y),
                  pAnim->Positions[i].Time - pAnim->Positions[i - 1].Time);
            
            interpolatedPosition.z = D3DDivide(
                  D3DMultiply(fFrame - pAnim->Positions[i - 1].Time, 
                              pAnim->Positions[i].z) +
                  D3DMultiply(pAnim->Positions[i].Time - fFrame, 
                              pAnim->Positions[i - 1].z),
                  pAnim->Positions[i].Time - pAnim->Positions[i - 1].Time);
         }

      }

      if (!done)
      {
         numberOfKeys--;
         interpolatedPosition.x = pAnim->Positions[numberOfKeys].x;
         interpolatedPosition.y = pAnim->Positions[numberOfKeys].y;
         interpolatedPosition.z = pAnim->Positions[numberOfKeys].z;
      }
   }

   
//interpolate quaternion information.
   done = 0;
   numberOfKeys = pAnim->RotationNumber;
   if (pAnim->Rotations[0].Time > fFrame)
   {
      interpolatedQuaternion.v.x = pAnim->Rotations[0].Quaternion.v.x;
      interpolatedQuaternion.v.y = pAnim->Rotations[0].Quaternion.v.y;
      interpolatedQuaternion.v.z = pAnim->Rotations[0].Quaternion.v.z;
      interpolatedQuaternion.s   = pAnim->Rotations[0].Quaternion.s;
      done = 1;
   }
   else
   {
      for (i = 1; ((i < numberOfKeys) && (!done)); ++i)
      {
         if (pAnim->Rotations[i].Time > fFrame)
         {
            D3DVALUE alpha;
            alpha = (fFrame - pAnim->Rotations[i - 1].Time) / 
                 (pAnim->Rotations[i].Time - pAnim->Rotations[i - 1].Time);
            D3DRMQuaternionSlerp(&interpolatedQuaternion, 
                                 &pAnim->Rotations[i - 1].Quaternion,
                                 &pAnim->Rotations[i].Quaternion,
                                 alpha);

            done = 1;
         }
      }
   
      if (!done)
      {
         numberOfKeys--;
         
         interpolatedQuaternion.v.x = 
                  pAnim->Rotations[numberOfKeys].Quaternion.v.x;
         
         interpolatedQuaternion.v.y = 
                  pAnim->Rotations[numberOfKeys].Quaternion.v.y;
         
         interpolatedQuaternion.v.z = 
                  pAnim->Rotations[numberOfKeys].Quaternion.v.z;
         
         interpolatedQuaternion.s   = 
                  pAnim->Rotations[numberOfKeys].Quaternion.s;
      }
   }

//interpolate scale information.
   numberOfKeys = pAnim->ScaleNumber;
   done = 0;
   if (pAnim->Scales[0].Time > fFrame)
   {
      interpolatedScale.x = pAnim->Scales[0].x;
      interpolatedScale.y = pAnim->Scales[0].y;
      interpolatedScale.z = pAnim->Scales[0].z;
      done = 1;
   }
   else
   {
      for (i = 1; ((i < numberOfKeys) && (!done)); ++i)
      {
         if (pAnim->Scales[i].Time > fFrame)
         {
            done = 1;
            interpolatedScale.x = D3DDivide(
                  D3DMultiply(fFrame - pAnim->Scales[i - 1].Time, 
                              pAnim->Scales[i].x) +
                  D3DMultiply(pAnim->Scales[i].Time - fFrame, 
                              pAnim->Scales[i - 1].x),
                  pAnim->Scales[i].Time - pAnim->Scales[i - 1].Time);
            
            interpolatedScale.y = D3DDivide(
                  D3DMultiply(fFrame - pAnim->Scales[i - 1].Time, 
                              pAnim->Scales[i].y) +
                  D3DMultiply(pAnim->Scales[i].Time - fFrame, 
                              pAnim->Scales[i - 1].y),
                  pAnim->Scales[i].Time - pAnim->Scales[i - 1].Time);
   
            interpolatedScale.z = D3DDivide(
                  D3DMultiply(fFrame - pAnim->Scales[i - 1].Time, 
                              pAnim->Scales[i].z) +
                  D3DMultiply(pAnim->Scales[i].Time - fFrame, 
                              pAnim->Scales[i - 1].z),
                  pAnim->Scales[i].Time - pAnim->Scales[i - 1].Time);
         }

      }
      
      if (!done)
      {
         numberOfKeys--;
         interpolatedScale.x = pAnim->Scales[numberOfKeys].x;
         interpolatedScale.y = pAnim->Scales[numberOfKeys].y;
         interpolatedScale.z = pAnim->Scales[numberOfKeys].z;
      }
   }

   
//The second step is to turn these values for a scale, a position, and a rotation,
//   into a matrix representing those operations.
   
   D3DRMMatrixFromQuaternion(matrix, &interpolatedQuaternion);
   
   pTransform->lpVtbl->AddTransform(pTransform, D3DRMCOMBINE_REPLACE, 
                               matrix);
   
   pTransform->lpVtbl->AddScale(pTransform, D3DRMCOMBINE_AFTER, 
                               interpolatedScale.x, 
                               interpolatedScale.y, 
                               interpolatedScale.z);

   pTransform->lpVtbl->AddTranslation(pTransform, D3DRMCOMBINE_AFTER, 
                               interpolatedPosition.x, 
                               interpolatedPosition.y, 
                               interpolatedPosition.z);
}

// **********************************************************
// Name:		TekApplyAnimation
//
// Author:	Bruce Abe
//
// Date:		June 22, 1996
//
// Description:	This function takes a pointer to a hierarchical model,
//                and a pointer to an animation, and a time.  It then sets
//                the transformations of each subframe of the hierarchical
//                model according to the animation and the time (frame of
//                the animation) by calling AnimatePart for each body part.
//
// Arguments:	   model is the hierarchical model.
//                KSAnim is the animation, in Kevin Shapiro format.
//                time is the frame of the animation to play.
//
// Return:	      None.
//
// Side Effects:	
//
// Notes:		   This function will apply animations to body parts.  If
//                there are more body parts in the model than in the 
//                animation, it will apply only as many animations as there
//                are animation body parts.  If there are more body parts in 
//                the animation than in the model, it will apply only as
//                many animations as there are model body parts.
//
// Known restrictions:
//		            
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************

void 
TekApplyAnimation(
    HierarchicalModel *pModel,   //pointer to the model to be animated.
    TekAnimation *pKSAnim,       //pointer to the animation to be applied.
    D3DVALUE fTime)              //animation frame
{
   int partNumber;         //counter
   int howMany;            //what we count to.
   
   howMany=(pKSAnim->NumberOfParts > pModel->ObjectNumber) ? 
      pModel->ObjectNumber : pKSAnim->NumberOfParts;

   for (partNumber = 0; partNumber < howMany; ++partNumber)
   {
      AnimatePart(pModel->ObjectCoordinates[partNumber], 
                  pKSAnim->AnimationData[partNumber], fTime);
   }
}


// **********************************************************
// Name:		FindSubframeByName
//
// Author:	Bruce Abe
//
// Date:		June 22, 1996
//
// Description:	This function recursively searches through the hierarchy
//                of frames to find one frame whose name matches the given
//                string.  It is intended as an improvement of the D3D 
//                function GetNamedObject, because it returns only frames, 
//                not unknown object types, and because by passing the root 
//                frame, we can narrow the scope of the search.  (This 
//                makes it possible to have two different copies of a model 
//                loaded, and find a body part from the correct model.)
//
// Arguments:	   parent is the root frame of the hierarchy.
//                name is the string we're trying to match.
//
// Return:	      The first subframe with a matching name, or NULL if no
//                match was found.
//
// Side Effects:	
//
// Notes:		   
//
// Known restrictions:
//		            
// Error Number:	No errors are returned.  NULL is returned if unsuccessful
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************
LPDIRECT3DRMFRAME 
FindSubframeByName(
         LPDIRECT3DRMFRAME pParent,    //root of hierarchy
         char *pName)                  //name we're trying to match.
{
   LPDIRECT3DRMFRAMEARRAY kids;        //array of child frames.
   int numKids;                        //number of child frames.
   LPDIRECT3DRMFRAME child;            //individual child frame.
   LPDIRECT3DRMFRAME answer;           //return value.
   int i;                              //counter
   char name[256];                     //buffer to store frame's name.
   unsigned long int length = 256;     //length of the buffer.

   pParent->lpVtbl->GetName(pParent, &length, name);
   if (!strcmp(pName, name))
   {
      return pParent;
   }

   pParent->lpVtbl->GetChildren(pParent, &kids);
   numKids = kids->lpVtbl->GetSize(kids);
   
   for (i = 0; i < numKids; ++i)
   {
      kids->lpVtbl->GetElement(kids, i, &child);
      answer = FindSubframeByName(child, pName);
      RELEASE(child);
      if (answer)
      {
         RELEASE(kids);
         return answer;
      }
   }
   
   RELEASE(kids);
   return 0;
}

// **********************************************************
// Name:		ProcessHierarchy
//
// Author:	Bruce Abe
//
// Date:		June 22, 1996
//
// Description:	This function creates a hierarchical model from a base
//                frame and a file created with the tool 3ds47tre.exe.
//
// Arguments:	   pParentFrame is the root frame of the mesh's frame 
//                hierarchy.
//
// Return:	      The hierarchical model.
//
// Side Effects:	Allocates memory for the hierarchical model and for the 
//                frame pointers, and fills it with pointers to body part
//                frames.
//
// Notes:		   The first dword in the tree file contains the number of 
//                body parts as an integer.  It may be abandonned if we 
//                use a different method of reading in model files.
//
// Known restrictions: None
//		            
//
// Error Number:	No errors are returned.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************
int NumParts;
unsigned char *pNameStrList;

HierarchicalModel 
   *ProcessHierarchy(
         LPDIRECT3DRMFRAME pParentFrame,  //the root of the hierarchy.
         unsigned char *pNameList)        //data from a .tre file.
{
   int i;                        //counter
   int length;                   //length of the current object name.
   HierarchicalModel *hierarchy; //Hierarchical model to be created.
   unsigned long int *pointer;   //Used to get the number of parts.
   int numParts;                 //number of parts.

   pointer = (unsigned long int *)pNameList;
   numParts = *pointer;
   NumParts = numParts;			//LGH add.
   pointer++;
   pNameList = (unsigned char *)pointer;
   pNameStrList = pNameList;	//LGH add
   
   hierarchy = malloc(sizeof(HierarchicalModel));
   hierarchy->ObjectNumber = numParts;
   hierarchy->ObjectCoordinates = 
               malloc(sizeof(LPDIRECT3DRMFRAME) * numParts);

   for(i = 0; i < numParts; ++i)
   {
      hierarchy->ObjectCoordinates[i] =
                  FindSubframeByName(pParentFrame, pNameList);
      length = strlen(pNameList);
      pNameList += length + 1;
   }
   return hierarchy;
}


// **********************************************************
// Name:		PreprocessAnimation
//
// Author:	Bruce Abe
//
// Date:		June 22, 1996
//
// Description:	This function takes raw data read in (typically)
//                as part of a packed animation and changes all the offsets
//                into pointers.  
//                
//
// Arguments:	   animation is a pointer to the raw data.  The data will be
//                processed in place, so it also will be the pointer to the
//                finished data at the completion of the function.
//
// Return:	      None
//
// Side Effects:	rearranges the order of data.
//
// Notes:		   
//       I keep all my pointers as pointers to u_long's so that I can skip 
//       over the next 4 bytes with a ++.  Kevin's tool stores offsets, 
//       which is the number of bytes forward you have to go from the 
//       current position to get to the relevant section.
//       To convert this offset to a pointer to that section, you therefore
//       have to add its position to the number stored at that position.
//       Since I'm using the pointers as pointers to longs, the procedure 
//       for converting an offset to a pointer is:
//                (*ptr) = ((u_long)ptr + (*ptr);
//       that is, what the pointer points to is set equal to the original 
//       offset (*ptr) plus the position of the data, converted to an 
//       unsigned long.
//
// Known restrictions:
//		            
//
// Error Number:	No errors are returned.
//
// Update:
// Date		      Name		   Description
// ====================================================
// July 9, 1996   Bruce Abe   Removed temporary code that rearranged data
//                            order, because Kevin's tool works correctly 
//                            now.
// **********************************************************

void PreprocessAnimation(unsigned long int *pAnimation)
{
   unsigned long int *here;      //pointer used to run through the 
                                 //animation header.
   unsigned long int *there;     //pointer used to run through the 
                                 //each animation component.
   unsigned int i;               //counter used to go through each 
                                 //animation component.

   unsigned long int count;      //number of animation components.

   here = pAnimation + 1;

   //skip over the number of frames in the animation.

   count=*here;
   here++;
   //skip past the number of objects, storing result.
   (*here) = ((unsigned long int)here) + 4;
   here++;
   //this is a pointer to the following data structure, which we'll access
   //as an array of AnimationComponents.
   for (i = 0; i < count; i++)
   {

      // *here is the offset to the i'th object.
      (*here) = ((unsigned long int)here) + (*here);
      // *here is now a pointer to the i'th object
      there = (unsigned long int *)(*here);
      //here is in the anim header.  there = *here is a pointer to the ith offset.


      //there points into the header.
      // *there is an offset to the position keyframe information.
      (*there) = ((unsigned long int)there) + (*there);
      // *there is now a pointer to the position keyframes.
      there++;
      // *there is the number of position keyframes.
      there++;
      // *there is an offset to the rotation keyframes.

      (*there) = ((unsigned long int)there) + (*there);
      // *there is now a pointer to the rotation keyframes.
      there++;
      // *there is now the number of rotations there are.
      there++;
      // *there is an offset to the scale keyframes.
      (*there) = ((unsigned long int)there) + (*there);
      // *there is now a pointer to the scale keyframes.
      there++;
      here++;//go to the next object offset.
   }
}

// **********************************************************
// Name:		PreprocessPackedAnimation
//
// Author:	Bruce Abe
//
// Date:		June 22, 1996
//
// Description:	This function takes raw data read in from a file
//                containing data which has been packed together using
//                pck47anm.exe, and changes offsets to data into pointers
//                to data.  
//
// Arguments:	   packedanimation is a pointer to the raw data.  The data 
//                will be processed in place, so it also will be the 
//                pointer to the finished data at the completion of the 
//                function.
//
// Return:	      Returns the number of animations that were loaded in.
//
// Side Effects:	None
//
// Notes:		   
//       I keep all my pointers as pointers to u_long's so that I can skip 
//       over the next 4 bytes with a ++.  Kevin's tools store offsets, 
//       which is the number of bytes forward you have to go from the 
//       current position to get to the relevant section.
//       To convert this offset to a pointer to that section, you therefore
//       have to add its position to the number stored at that position.
//       Since I'm using the pointers as pointers to longs, the procedure 
//       for converting an offset to a pointer is:
//                (*ptr) = ((u_long)ptr + (*ptr);
//       that is, what the pointer points to is set equal to the original 
//       offset (*ptr) plus the position of the data, converted to an 
//       unsigned long.
//
// Known restrictions:
//		            This function is currently usable only for 
//                files which have animations packed into them.  The file 
//                spec's have been written with the intention of packing
//                various kinds of data, but we don't distinguish types of
//                data and use different processing on each type of data
//                currently.
//
// Error Number:	No errors are returned.
//
// Update:
// Date		      Name		   Description
// ====================================================
// July 9,1996    Bruce Abe   set the return value to be the number of 
//                            animations processed.
// **********************************************************

int 
PreprocessPackedAnimation(
   LPDIRECT3DRMFRAME pParentFrame,
   unsigned long int *pPackedAnimation)//pointer to raw data, to be processed
{
   int i, count;     //i is a counter, count is what i counts to.
   
   //This sets the first element to be a pointer to the id's.
   *pPackedAnimation = ((unsigned long int)pPackedAnimation) + 8;

   
   pPackedAnimation++;
   count = *pPackedAnimation;
   pPackedAnimation++;
   *pPackedAnimation = ((unsigned long int)pPackedAnimation) + 
                                         *pPackedAnimation;
   // Turn the offset to the first file to a pointer to the first file.

   SabreHierarchy=ProcessHierarchy(
      pParentFrame,
      (unsigned char *)*pPackedAnimation);

   pPackedAnimation++;

   for (i = 1; i < count; ++i)
   {
      *pPackedAnimation = ((unsigned long int)pPackedAnimation) + 
                                            *pPackedAnimation;

      // Turn the offset to the first file to a pointer to the first file.
      PreprocessAnimation((unsigned long int *)*pPackedAnimation);
      pPackedAnimation++;
   }
   return (count - 1);
}

// **********************************************************
// Name:		LoadPackedAnimation
//
// Author:	Bruce Abe
//
// Date:		July 9, 1996
//
// Description:	This function takes a string which contains the name of
//                a file, and a pointer.  The function creates space in
//                memory for the file, reads it in to that space, and sets
//                the pointer to point to that space.
//
// Arguments:	   pName is the name of the file, a 0 terminated string.
//                pData is a pointer to a pointer.  The pointer will be 
//                set to point to the data that's read in.
//
// Return:	      Returns 0 for failure, 1 for success.
//
// Side Effects:	Allocates memory for the file.
//
// Notes:		   
//
// Known restrictions:
//
// Error Number:	0 for failure, 1 for success.
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************
extern char XafPath[];
int
LoadPackedAnimation(
                    char *name, 
                    DataPointer *pData)
{
   char pName[MAX_PATH];	
   int NumRead;
   int fh, FileLength;

   strcpy(pName, XafPath);
   strcat(pName, "\\");
   strcat(pName, name);

   if (*pData)
   {
      free(*pData);
   }
   fh = _open(pName, _O_RDONLY | _O_BINARY);
   if (fh != -1)
   {
      FileLength=_filelength(fh);
      *pData=(DataPointer)malloc(FileLength);
      if(*pData)
      {
         NumRead=_read(fh, *pData, FileLength);
         if(NumRead != FileLength)
         {
            printf("something wrong");
            _close(fh);
            free(*pData);
            return 0;
         }
      }
      else 
      {
         _close(fh);
         return 0;
      }
      _close(fh);
   }
   else
   {
      return 0;
   }
   return 1;
}

// **********************************************************
// Name:		GetRobotObjInfo
//
// Author:		LiouGuoHong
//
// Date:		August 30, 1996
//
// Description:	Get object information, for preparing to gain
//				the name of every part of model.
//			    
// Arguments:	pPackedAnimation
//              pointer to raw data, to be processed
//
// Return:	    void
//
// Side Effects:	
//
// Notes:		   
//
// Known restrictions:
//
// Error Number:	
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************
int RobotNumParts;
unsigned char *pRobotNameStrList;

void GetRobotObjInfo (
   unsigned long int *pPackedAnimation)//pointer to raw data, to be processed
{
   unsigned long int *pointer;
	unsigned long int adr;

   pPackedAnimation += 2;
   adr = ((unsigned long int)pPackedAnimation) + *pPackedAnimation;
                         
   pointer = (unsigned long int *)adr;
   RobotNumParts = *pointer;
   pointer++;
   pRobotNameStrList = (unsigned char *)pointer;
}

// **********************************************************
// Name:		GetRobotNameFromTreData
//
// Author:		LiouGuoHong
//
// Date:		August 30, 1996
//
// Description:	Get name of every part of model.
//			    
// Arguments:	Num
//              The index to one part of model.
//
// Return:	    The name string
//
// Side Effects:	
//
// Notes:		   
//
// Known restrictions:
//
// Error Number:	
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************
unsigned char *GetRobotNameFromTreData (int Num)
{
   int i = 0;
   int length;
   unsigned char *pNameList = pRobotNameStrList;

   while (1) 
   {
      if (i >= Num)
	  {
		  break;
	  }
	  length = strlen(pNameList);
	  pNameList += length + 1;
	  i++;
   }

   return pNameList; 
}

// **********************************************************
// Name:		GetMonstObjInfo
//
// Author:		LiouGuoHong
//
// Date:		August 30, 1996
//
// Description:	Get object information, for preparing to gain
//				the name of every part of model.
//			    
// Arguments:	pPackedAnimation
//              pointer to raw data, to be processed
//
// Return:	    void
//
// Side Effects:	
//
// Notes:		   
//
// Known restrictions:
//
// Error Number:	
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************
int MonstNumParts;
unsigned char *pMonstNameStrList;

void GetMonstObjInfo (
   unsigned long int *pPackedAnimation)//pointer to raw data, to be processed
{
   unsigned long int *pointer;
	unsigned long int adr;

   pPackedAnimation += 2;
   adr = ((unsigned long int)pPackedAnimation) + *pPackedAnimation;
                         
   pointer = (unsigned long int *)adr;
   MonstNumParts = *pointer;
   pointer++;
   pMonstNameStrList = (unsigned char *)pointer;
}

// **********************************************************
// Name:		GetMonstNameFromTreData
//
// Author:		LiouGuoHong
//
// Date:		August 30, 1996
//
// Description:	Get name of every part of model.
//			    
// Arguments:	Num
//              The index to one part of model.
//
// Return:	    The name string
//
// Side Effects:	
//
// Notes:		   
//
// Known restrictions:
//
// Error Number:	
//
// Update:
// Date		Name		Description
// ====================================================
//
// **********************************************************
unsigned char *GetMonstNameFromTreData (int Num)
{
   int i = 0;
   int length;
   unsigned char *pNameList = pMonstNameStrList;

   while (1) 
   {
      if (i >= Num)
	  {
		  break;
	  }
	  length = strlen(pNameList);
	  pNameList += length + 1;
	  i++;
   }

   return pNameList; 
}


//**************************************************************************
// loadanim.c
//
// (c) Copyright Inventec(Tian Jin) 1996. All rights reserved.
//
// Author:      Sanfo
//
// Date:        1996
//
// Description: (1) Create AnimationSet and load animation file(*.x)
//
// Notes:       (1) Used only in Direct 3D version of Goman95
//              (2) Need Robotframe & lpD3DRM as global variables.
//
// Update:
//
//**************************************************************************
#include <windows.h>
#include "rl2d3d.h"

#ifdef __cplusplus
extern "C"{
#endif

#include "tekanim.h"

extern PackedAnimations *TekRobotAnims;
extern int TekRobotNumAnims;
extern PackedAnimations *TekMonsterAnims;
extern int TekMonsterNumAnims;
RLAnimationSet LoadAnim(char *filename);

#ifdef __cplusplus
}
#endif


//**************************************************************************
// Name:        LoadAnim()

// Author:      Sanfo

// Date:        Aug 1996

// Description: Get one animation from a animation package.
//              this is for .BIN version of animation
// Arguments:   

// Return:      

//**************************************************************************

int RobotTable[21]   = { 0  , 101, 103, 109, 110, 
                        111, 112, 113, 114, 115,
                        116, 117, 118, 119, 120,
                        121, 124, 131, 139, 150,
                        149};

int MonsterTable[17] = {0,   101, 103, 104, 109,
                        110, 115, 116, 117, 125,
                        128, 136, 143, 147, 145,
                        126, 111};

RLAnimationSet LoadAnim(char *filename)
{
    char charname[3];
    char serialno[4];
    int  number;
    int  index;
    
    strncpy(charname, filename, 2);     // get charactor name, "SA", "TO"...
    strncpy(serialno, filename+2, 3);   // get serial number, "101", "102"...
    charname[2]=0;
    serialno[3]=0;

    if( stricmp(charname, "SA")==0 ||
        stricmp(charname, "ST")==0 ||
        stricmp(charname, "ME")==0 ||
        stricmp(charname, "KA")==0 ||
        stricmp(charname, "KB")==0 )
    // it is a Robot
    {
        number = atoi(serialno);

        for(index=0; index<=21; index++)
            if( RobotTable[index] == number )
                break;
        
        return index > TekRobotNumAnims ? NULL : TekRobotAnims->Animations[index];
    }

    // it must be a monster
    number = atoi(serialno);
    
    for(index=0; index<=17; index++)
            if( MonsterTable[index] == number )
                break;
        
    return index > TekMonsterNumAnims ? NULL : TekMonsterAnims->Animations[index];
}


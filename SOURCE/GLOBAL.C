#ifdef MINIWIN
#include "miniwin/windows.h"
#else
#include <windows.h>
#endif
#include <stdio.h>

#include "rl2d3d.h"
#include "camera.h"
#include "plasma.h"
#include "gosys.h"
#include "global.h"

extern volatile long int InputInt, InputInt2, InputIntDevNull;
volatile long int *InputIntPtr = &InputInt, 
				*InputIntPtr2= &InputInt2, 
				*InputIntPtr3= &InputIntDevNull;	
Caminfo* camerastuff;
RLFrame MonsterScaleFrame;
BOOL   KbFlag = FALSE;
int Vmode = 320;
int Vsize = 2;
TARGET targets[15];
Psystem *NeallothRings;
ZappaData Robotzapdata[6];
int shielddlist, nukedlist;
sGameVariables GameStates=
{
	-1,									//level
	-1,									//Robot
	Alpha,								//submonster
	0,									//score
	0,									//hours
	0,									//minutes
	0,									//seconds
	{FALSE, FALSE, FALSE, FALSE, FALSE},//RobotDead
	{
		{FALSE, FALSE, FALSE},			//MonsterDead
		{FALSE, FALSE, FALSE},
		{FALSE, FALSE, FALSE},
		{FALSE, FALSE, FALSE},
		{FALSE, FALSE, FALSE},
		{FALSE, FALSE, FALSE},
		{FALSE, FALSE, FALSE}
	},
	{TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE},	//levelhonor
	FALSE,										//monsterlose
	FALSE,										//Robotlose
	FALSE,										//3dmovie
	FALSE,										//autodemo
	FALSE,										//training
	FALSE,										//game
	FALSE										//netplay
};
void MDFreeD3DFrame(LPDIRECT3DRMFRAME frame)
{
	LPDIRECT3DRMFRAME parent = NULL;
	BOOL flag = TRUE;
	ULONG refcount;

	if(!frame)
		return ;

	while(flag)
	{
		refcount = frame->lpVtbl->Release(frame);
		if (refcount <= 1)
			flag = FALSE;
	}
	frame->lpVtbl->GetParent(frame, &parent);

	if(parent)
	{
		parent->lpVtbl->DeleteChild(parent, frame);
		RELEASE(parent);
	}
	frame = NULL;
}
 
 
void YBPlayEndingMidi(short Idx)
{
	;
}

void YBTextOut(HWND win, char *str, char *font, RECT p1)
{
	;
}



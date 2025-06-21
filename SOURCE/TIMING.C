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
File:           timing.c
Author:         Bruce Abe
Date:           9-26-95
Version:        1.0



************************************************************************
REVISION HISTORY        (Add Edits and History to top of list).

Edited By:      Bruce Abe
Edited Date:    10-19-95
Changes:
                removed undocumented Frames Per Second calculations,
                changed the initial times to positive values, either 
                of which changes would put an end to the bug that 
                caused the game to crash on startup sometimes.

***********************************************************************/
#include "rl2d3d.h"
//#include "rl.h"
#include <time.h>
#ifdef MINIWIN
#include "miniwin/windows.h"
#else
#include <windows.h>
#endif
#include <stdio.h>

#include "timing.h"
#include "keycom.h"
#include "global.h"
extern void YBTextOut(HWND win, char *str, char *font, RECT p1);
//extern BOOL In3DMovie;

unsigned char Hours,Minutes,Seconds;
unsigned int Thousandths;
unsigned char AverageTimePerFrame;
unsigned char FramesPerSecond;
unsigned char framecounter=0;

static unsigned char TimeBuffer[16];
static unsigned char TBIndex;
static unsigned int TBTotal;
static unsigned char currenttime;
static unsigned char lasttime;
static HWND Twin;

extern RLValue DiffFrame;
extern RLValue Turbo;

void RestartTimer(HWND win)
{
   int i;
//   FILE *shithead;
//   shithead=fopen("shit.out","a");

   Twin=win;
   Hours=0;
   Minutes=0;
   Seconds=0;
   Thousandths=0;
   AverageTimePerFrame=0;
   for(i=0;i<16;++i)
   {
      TimeBuffer[i]=10;
//      fprintf(shithead,"Timebuffer[%d] = %d\n",i,TimeBuffer[i]);
   }
   TBIndex=0;
   TBTotal=160;
   DiffFrame=(float)0.0;
   lasttime=(unsigned char)clock();
//   fprintf(shithead,"TBTotal = %d\n",TBTotal);
//   fclose(shithead);
}

void PauseTimer()
{
}

void UnPauseTimer()
{
   lasttime=(unsigned char)clock();
}

unsigned char Ticket()
{
   RLValue temp;
//   FILE *shithead;
   if (GameStates.Is3DMovie) return 0;

   currenttime=(unsigned char)clock();
   TBTotal-=TimeBuffer[TBIndex];
   TimeBuffer[TBIndex]=currenttime-lasttime;
   lasttime=currenttime;
   TBTotal+=TimeBuffer[TBIndex];
   Thousandths+=TimeBuffer[TBIndex];
//   shithead=fopen("shit.out","a");
//   fprintf(shithead,"total = %d, newtime = %u ",TBTotal,TimeBuffer[TBIndex]);
//   fprintf(shithead,"currenttime = %d, lasttime = %d\n",currenttime,lasttime);
//   fclose(shithead);
   TBIndex++;
   if(TBIndex == 16)
      TBIndex=0;
   if(Thousandths>=1000)
   {
      Seconds++;
      Thousandths-=1000;
      FramesPerSecond=framecounter;
      framecounter=1;
      if(Seconds>=60)
      {
         Seconds-=60;
         Minutes++;
         if(Minutes>=60)
         {
            Minutes-=60;
            Hours++;
         }
      }
   }
   else
   {
      framecounter++;
   }
   AverageTimePerFrame=TBTotal>>4;
   temp=RLVal(30*AverageTimePerFrame) * Turbo;
   DiffFrame= temp/CLOCKS_PER_SEC;
   return AverageTimePerFrame;
   
}

void DispFPS(void)
{
	char value[127];
	RECT p1;

	//if (!Tflag) return;

	p1.top    = 10;
	p1.left   = 30;
	p1.right  = 140;
	p1.bottom = 25;

	sprintf(value, "FPS = %02d", FramesPerSecond);
	YBTextOut(Twin, value, "Times New Roman", p1);
}



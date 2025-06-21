/***********************************************************************\
 *    (C) Copyright 1995 by 47-TEK, Inc.							   *
 *																	   *
 *    This program is copyrighted by 47-TEK, Inc. and is  not licensed *
 *    to you under any conditions.  You may not distribute, duplicate, *
 *    or  publish the source code of this program in any form.  You	   *
 *    may  not incorporate this code in any form in derivative  works. *
 *     																   *
 *																	   *
 *    47-Tek is a registered trademark of 47-TEK, Inc.				   *
 *    47-TEK Specifically disclaims any implied Warranty of Mer-	   *
 *    chantability or fitness for a particular use. 47-TEK,  Inc.	   *
 *    does not Warrant that the operation of the program will be	   *
 *    uninterrupted or error free.									   *
 *																	   *
\***********************************************************************

Program:        Goman95
File:           RADAR.C
Author:         Bo Yuan
Date:           09/26/95
Version:        version 1.0



************************************************************************
REVISION HISTORY        

Edited By:      Bo Yuan
Edited Date:    10/03/95
Changes:
				* changed target indicator from "+" to ".", found out
				  I forget to create compatible bitmap before.	Also,
				  modified rectangle calculation in UpdateRadar.

***********************************************************************/

#ifdef MINIWIN
#include "miniwin/windows.h"
#else
#include <windows.h>
#endif

#include "rl2d3d.h"
/*
#include <rl.h>
#include <rlwin.h>
*/

#include "radar.h"

extern RLFrame Robotframe;
extern RLFrame monstframe;
extern void YBTextOut(HWND win, char *str, char *font, RECT p1);

static int x0  = 283;
static int y0  = 40;

static int tx0 = 283;
static int ty0 = 40;
static int tx1 = 283;
static int ty1 = 40;
//static int tw = 2;
//static int th = 2;
//static int tww = 5;
//static int thh = 5;
static HWND mainwin=NULL;

#define X0 283
#define Y0 40


void DrawRadar(HWND win)
{
	HPEN   hNewPen, hOldPen;
	static int status = 0;
	static HDC hdcMem;
	HDC hDC;
//	RECT rect;
	static HBITMAP hbitmap;

	if (!status)
	{ // the first time
		mainwin = win;
		hDC = GetDC(win);
		// create a memory device
		hdcMem    = CreateCompatibleDC(hDC);
		// create a shit memory to store bitmap information
		// I forget this before!!!
		hbitmap   = CreateCompatibleBitmap(hDC, 2, 2);
		SelectObject(hdcMem, hbitmap);
		// copy hDC to hdcMem
		BitBlt(hdcMem, 0, 0, 2, 2, hDC, X0-1, Y0-1, SRCCOPY); 
		ReleaseDC(win, hDC);
		status = 1;
	}
	
	hDC = GetDC(win);
	// recover old background bitmap
	BitBlt(hDC, tx0-1, ty0-1, 2, 2, hdcMem, 0, 0, SRCCOPY);
	// store new background bitmap
	BitBlt(hdcMem, 0, 0, 2, 2, hDC, tx1-1, ty1-1, SRCCOPY);
	// draw new point, its width has to be 2, or you can see the point
	hNewPen = CreatePen(PS_SOLID, 2, RGB(255,0,0));
	hOldPen = SelectObject(hDC, hNewPen);
	MoveToEx(hDC, tx1, ty1, NULL);
	LineTo(hDC, tx1, ty1);
	SelectObject(hDC, hOldPen);
	DeleteObject(hNewPen);
	ReleaseDC (win, hDC);

	tx0 = tx1;
	ty0 = ty1;

}

void UpdateRadar(HWND win)
{
	RECT rect;
    
	rect.left = min(tx0, tx1)-1;
	rect.top  = min(ty0, ty1)-1;
	rect.right = max(tx0, tx1)+1;
	rect.bottom = max(ty0, ty1)+1;
 	InvalidateRect(win, &rect, FALSE);
}

void CalRadar(void)
{
	RLVector p;
	int dx, dy;
//	int px, py;
//	char str[256];
//	RECT p1;
//#define LDEBUG

	RLFrameGetPosition(monstframe, Robotframe, &p);
	//dx = (p.x * 100)/127;
	//dy = (p.z * 100)/127;
	dx = (int)(-(p.x * 20) / 127);
	dy = (int)((p.z * 20) / 127);

#ifdef LDEBUG
	p1.left = 10;
	p1.top  = 40;
	p1.right  = 100;
	p1.bottom = 60;
	wsprintf(str, "dx = %d   dy = %d\n", dx, dy);
	YBTextOut(mainwin, str, "Times New Roman", p1);
#endif

	//tx1 = x0 + (dx * 20) / 127;
	//ty1 = y0 + (dy * 20) / 127;
	tx1 = X0 + dx;
	ty1 = Y0 + dy;
	//if (tx1!=tx0 || ty1!=ty0)
		SendMessage(mainwin, WM_COMMAND, 0, 0L);
}


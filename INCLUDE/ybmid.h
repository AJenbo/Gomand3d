//*******************************************************************
// ybmid.h
//
// Copyright 1996 by 47-TEK, INC.  All rights reserved.
//
// Author:	Bo Yuan
// 
// Date:	06/04/96
//
// Description:	Header file of "ybmid.c"
//
// Side effects:
//
// Class:
//
// Function:
//		void YBSetupDMidi(void);
//		void YBQuitDMidi(void);
//		void YBCreateEvent(void);
//		BOOL YBPlayDMidi(void);
//		BOOL YBStopDMidi(WPARAM wParam);
//		void YBSetMidiVolume(int Value);
//		void YBLoadDMidi(char *filename);
//
//		BOOL YBSetLoopDMidi(BOOL v);
//		BOOL StreamBufferSetup( void );
//		void CALLBACK MidiProc( HMIDIIN hMidi, UINT uMsg, DWORD dwInstance,
//	            DWORD dwParam1, DWORD dwParam2 );
//		void FreeBuffers( void );
// 
// Notes:
//
// Update:
//
// Date			Name			Description
// ==================================================================
//
//*******************************************************************
#ifndef __YBMID_H__
#define __YBMID_H__

#include <windows.h>
#include <windowsx.h>
#include <memory.h>
#include <mmreg.h>

#include "midstuff.h"
//#include "mstream.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MMV_INCREASE 601
#define MMV_DECREASE 602
#define MID_TMP_CHANGE 10
#define MID_VOL_CHANGE 100

extern void YBSetMidVolume(int Value);
extern void YBSetupDMidi(void);
extern void YBQuitDMidi(void);
extern void YBCreateEvent(void);
extern BOOL YBPlayDMidi(void);
extern BOOL YBStopDMidi(WPARAM wParam);
extern void YBSetMidiVolume(int Value);
extern void YBLoadDMidi(char *filename);

extern BOOL YBSetLoopDMidi(BOOL v);
extern void BYChangeMidTempo(int direction);
extern void BYChangeMidVolume(int direction);

extern void FreeBuffers( void );
extern void YBResumeMidiPlay(void);
extern void YBPauseMidiPlay(void);

#ifdef __cplusplus
};
#endif

BOOL StreamBufferSetup( void );
void CALLBACK MidiProc( HMIDIIN hMidi, UINT uMsg, DWORD dwInstance,
            DWORD dwParam1, DWORD dwParam2 );

#endif __YBMID_H__
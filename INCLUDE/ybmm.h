//****************************************************************************
// ybmm.h
//
// Copyright 1996 by 47-TEK, INC.  All rights reserved.
//
// Author:	Bo Yuan
// 
// Date:	06/06/96
//
// Description:	Header file of "ybmm.c"
//
// Side effects:
//
// Class:
//
// Function:
// 
//    BOOL YBGetAllPath(HINSTANCE hInst, short mode);
//    void YBReportError(int i, char *inputstr);
//    BOOL YBGetExeFullPathnName 
//          (HINSTANCE hInst, LPSTR FullPath, LPSTR ExeName);
//    BOOL YBGetFullFileName 
//          (LPSTR FullPath, LPSTR FileName, LPSTR fname, LPSTR Ext);
//    BOOL YBGetFilePath 
//          (LPSTR lpApplicationName, LPSTR lpFileType, LPSTR lpDefaultPath,
//    LPSTR lpReturnedFullPath, int nMaxReturnSize, LPSTR lpIniFileName);
//    void YBPlayMidi(LPSTR MidiName, HWND hWnd);
//    void YBStopMidi(LPSTR MidiName, HWND hWnd);
//    void YBCleanUpMidi (HWND hWnd);
//    HWND PlayAVI 
//          (HWND hWnd, LPSTR AviName, LPSTR AliaName, int WinNo, RECT rt);
//    void CloseAVI(HWND hWnd, LPSTR AliaName);
//    void YBPlayWave(LPSTR WaveName, HWND hWnd);
//    void YBStopWave(LPSTR MidiName, HWND hWnd);
//    void YBCleanUpWave (HWND hWnd);
//    BOOL YBGetAllAbsPath(HINSTANCE hInst, short mode, char newver[]);
//    BOOL YBGetGMPath(short vmode, char newver[]);
//
// Notes:
//
// Update:
//
// Date			Name			Description
// ===========================================================================
//
//****************************************************************************

#ifndef __YBMM_H__
#define __YBMM_H__

#ifdef MINIWIN
#include "miniwin/windows.h"
#else
#include <windows.h>
#include <mmsystem.h>
#endif
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

extern char BmpPath[127];
extern char WrapBmpPath[127];
extern char WrapSnd1[127];
extern char WrapSnd2[127];
extern char CDDriveLetter;
extern BOOL bMidiFlag;

BOOL YBGetAllPath(HINSTANCE hInst, short mode);
BYOBGetBitmapPath(short mode);
void YBReportError(int i, char *inputstr);
BOOL YBGetExeFullPathnName (HINSTANCE hInst, LPSTR FullPath, LPSTR ExeName);
BOOL YBGetFullFileName (LPSTR FullPath, LPSTR FileName, LPSTR fname, LPSTR Ext);
BOOL YBGetFilePath (LPSTR lpApplicationName, LPSTR lpFileType, LPSTR lpDefaultPath,
LPSTR lpReturnedFullPath, int nMaxReturnSize, LPSTR lpIniFileName);
void YBPlayMidi(LPSTR MidiName, HWND hWnd);
void YBStopMidi(LPSTR MidiName, HWND hWnd);
void YBCleanUpMidi (HWND hWnd);
HWND PlayAVI (HWND hWnd, LPSTR AviName, LPSTR AliaName, int WinNo, RECT rt);
void CloseAVI(HWND hWnd, LPSTR AliaName);
void YBPlayWave(LPSTR WaveName, HWND hWnd);
void YBStopWave(LPSTR MidiName, HWND hWnd);
void YBCleanUpWave (HWND hWnd);
BOOL YBGetAllAbsPath(HINSTANCE hInst, short mode, char newver[]);
BOOL YBGetGMPath(short vmode, char newver[]);
char GetCDROMDriveLetter();
#ifdef __cplusplus
};
#endif

#endif __YBMM_H__
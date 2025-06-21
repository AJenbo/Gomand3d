//*******************************************************************
// ybsnd.h
//
// Copyright 1996 by 47-TEK, INC.  All rights reserved.
//
// Author:	Bo Yuan
// 
// Date:	06/19/96
//
// Description:	Header file of "ybsnd.c"
//
// Side effects:
//
// Class:
//
// Function:
//    long FAR PASCAL WndProc(HWND, unsigned, WPARAM, LPARAM);
//    long FAR PASCAL DLGHelpAbout(HWND, UINT, WPARAM, LPARAM);
//    long FAR PASCAL DLGOutputBufferType(HWND, UINT, WPARAM, LPARAM);
//    long FAR PASCAL DLGCheckLatency(HWND, UINT, WPARAM, LPARAM);
//    BOOL ClassInit(HANDLE);
//    void PD_FileOpen(HWND);
//    BOOL OpenFileDialog(HWND, LPSTR, int *);
//    BOOL IsValidWave(LPSTR);
//    int CreateControl(HWND, FILEINFO *, DWORD, DWORD, DWORD);
//    void GetNextControlCoords(FILEINFO *, int *, int *);
//    int AddToList(FILEINFO *, FILEINFO *);
//    int FreeAllList(HWND, FILEINFO *);
//    int RemoveFromList(FILEINFO *, FILEINFO *);
//    int GetNumControls(FILEINFO *);
//    int StartDSound(HWND, FILEINFO *);
//    int StopDSound(HWND, FILEINFO *);
//    int StopAllDSounds(HWND, FILEINFO *);
//    BOOL UIMainWindowVSBHandler(HWND, WPARAM, LPARAM); 
//    BOOL UIMainWindowHSBHandler(HWND, WPARAM, LPARAM); 
//    BOOL UIMainWindowCMDHandler(HWND, WPARAM, LPARAM); 
//    BOOL UIMainWindowTimerHandler(HWND, WPARAM, LPARAM); 
//    void SetAllText(FILEINFO *);
//    void UpdateLRVolume(FILEINFO *);
//    void AppDestroy(HWND);
//    void AppInit(HWND);
//    int NewDirectSoundBuffer(FILEINFO *);
//    int ReleaseDirectSoundBuffer(FILEINFO *);
//    int ChangeOutputPan(FILEINFO *);
//    int ChangeOutputFreq(FILEINFO *);
//    int ChangeOutputVol(FILEINFO *);
//    int FormatToIndex(HWND, FILEINFO *);
//    int IndexToFormat(HWND, FILEINFO *, int);
//    void YBSetUpSoundSystem(HWND hWnd);
//    void YBLoadSounds(HWND hWnd, int Level, int Robot);
//    BOOL YBPlaySound(int idx);
//    BOOL YBPlay3DSound(int idx, RLFrame noisyguy);
//    void YBUnLoadSoundSystem( HWND hWnd );
//    BOOL YBChangeVolume(int idx, int diff);
//    BOOL YBChangePan(int idx, int diff);
// 
// Notes:
//
// Update:
//
// Date			Name			Description
// ==================================================================
//
//*******************************************************************
#ifndef __YBSND_H__
#define __YBSND_H__

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stdio.h>
#include <mmreg.h>
#include <msacm.h>
#include <dsound.h>
//#include <rl.h>
//#include <rlwin.h>
#include "rmdemo.h"
#include "d3d.h"

#include "wassert.h"
#include "wave.h"

// If this is defined, then an extra text string under the filename will show
// if the file is stopped or playing.

#define SHOWSTATUS


typedef enum SoundList
{
	RobotSomething,
	RobotShoot,
	RobotGetHit,
	RobotFootStep,
	RobotJets,
	RobotFallDown,
	MonsterSomethin,
	MonsterTailZap,
	MonsterGetHit,
	MonsterFootStep,
	MonsterWail,
	MonsterFallDown,
	SmallBldgBoom,
	BigBuildingBoom,
	Crumble,
	EdgeOWorld,
	Splat,
	Splash,
	FireFireFire,
	Bounce,
	SwordSwish,
	Failure,
	Screams1,
	Screams2,
	Applause,
	Melt,
	RobotClick,
	EmPower,
	MAXCONTROLS
}SoundIndex;



// Error codes.
#define ER_OUTOFMEMORY                  0xd100      // Out of memory.
#define ER_CANNOTALLOCATEDC             0xd101      // Cannot get a DC.
#define ER_CANNOTRELEASEDC              0xd102
#define ER_APIFAILED                    0xd103      // A general API failed.
#define ER_CANNOTCREATEWINDOW           0xd104      // Cannot create a window.

#define ER_BADROUTINEPARAM              0xd200      // Bad parameter for procedure call.
#define ER_TIMERALLOC                   0xd201      // Timer alloc error.


// For setting the ranges on the freq, vol, etc.
// dwFreq*FREQMUL+FREQADD = # to show on screen.

#define FREQMUL                 (100)                   
#define FREQADD                 (4000)

#define MINFREQ_TB              0
#define MAXFREQ_TB              512
#define MINPAN_TB               0
#define MIDPAN_TB                               400
#define MAXPAN_TB                               800
#define SHIFTPAN_TB                             (-400)
#define MULTPAN_TB                              (10L)
#define MINPAN_VAL                              (-400)
#define MIDPAN_VAL              0
#define MAXPAN_VAL                              400
#define MINVOL_TB               0
#define MAXVOL_TB                               400
#define SHIFTVOL_TB                             (-400)
#define MULTVOL_TB                              (10L)
#define MINVOL_VAL                              -400
#define MAXVOL_VAL              0

// Id code deltas
#define idFreqTB                1
#define idPanTB                 2
#define idVolLTB                3
#define idVolRTB                4
#define idVolMTB                5
#define idLoopedBN              6
#define idPlayBN                7
#define idRemoveBN              8

// UI stuff.

#define DX_WIN_BORDER           30
#define DY_WIN_BORDER           30
#define DX_MINWINDOW            640
#define DY_MINWINDOW            500

#define DX_CONTROLSPACING       150
#define DY_CONTROLSPACING       0

#define DX_LINEEDGE             (DX_CONTROLSPACING - 20)
#define DY_LINEEDGE             (1)


#define COX_STARTCONTROL        (20)
#define COY_STARTCONTROL        (10)

#define DX_TEXTSPACING          5
#define DY_TEXTSPACING          10

#define DX_LOOPEDSPACING        0
#define DY_LOOPEDSPACING        -6 //2

#define DX_STATUSSPACING        0

#ifdef SHOWSTATUS
#define DY_STATUSSPACING        8
#else
#define DY_STATUSSPACING        0
#endif


#define DX_FREQSPACING          0
#define DY_FREQSPACING          10

#define DY_PANSPACING           10
#define DY_VOLSPACING           10

#define DX_FILENAME_TXT         120
#define DX_STATUS_TXT           120
#define DX_FREQ_TXT             100
#define DX_PAN_TXT              100
#define DX_VOL_TXT              100
#define DX_LOOPED_TXT           100

#define DX_FREQ_TB              130
#define DY_FREQ_TB              40
#define DX_PAN_TB               130
#define DY_PAN_TB               40
#define DX_VOL_TB               40
#define DY_VOL_TB               100
#define DX_VOLSPACING_TB        5

#define DX_VOLURobotAR           15
#define DY_VOLSPACINGY          -5

#define DX_BUTTONSPACING        61  //80
#define DY_BUTTONSPACING        10
#define DY_BEFOREFIRSTBUTTON    18  //22  //31
#define DY_BETWEENBUTTONS       5

#define DX_FRAMEEDGE            10
#define DY_FRAMEEDGE            10
#define DX_FRAMEEDGEINNER       4           

#define DSBSIZE                 0x10000

// To check for stopping of sounds, a timer is set...use this for the rate.
#define TIMERPERIOD             500 //100             // In milliseconds

// In Options/Output Type, there are strings to pick the format...Here are the number of them.
#define C_DROPDOWNPCMFORMATS    16

typedef struct _fileinfo
    {
    BYTE                *pbData;        // Pointer to actual data of file.
    UINT                cbSize;         // Size of data.
    WAVEFORMATEX    *pwfx;          // Pointer to waveformatex structure.

    DWORD               dwFreq;         // Frequency.
    DWORD               dwPan;          // Panning info.
    DWORD               dwVol;          // Total volume.
    BOOL                fLooped;        // Looped?

    BOOL                fPlaying;       // Is this one playing?
    BOOL                fLost;          // Is this one lost?
    BOOL                fHardware;      // Is this a hardware buffer?

    int         cox;            // Coordinates of where the structure is
    int         coy;            // printed.

    // HWND's needed.
    HWND                hWndFileName_TXT;   // Filename text string.
    HWND                hWndFreq_TB;        // Trackbar handle.
    HWND                hWndFreq_TXT;       // Text string for freq.
    HWND                hWndPan_TB;         // Trackbar handle.
    HWND                hWndPan_TXT;        // Text string for pan.
    HWND                hWndVol_TXT;        // Text string for volume.
    HWND                hWndVolL_TB;        // Trackbar for volume left.
    HWND                hWndVolR_TB;        // Trackbar for volume right.
    HWND                hWndVolM_TB;        // Main volume.
    HWND                hWndLooped_BN;      // Looped
    HWND                hWndPlay_BN;        // Play
    HWND                hWndRemove_BN;      // Remove.
    
    HWND                hWndFileName_EDGE;  // The line under filename.
    HWND                hWndLooped_EDGE;    // The line under looped.
    HWND                hWndFreq_EDGE;      // The line under freq.
    HWND                hWndPan_EDGE;       // The line under pan.
    HWND                hWndVol_EDGE;       // The line under volume.
    HWND                hWndWhole_EDGE;     // The whole surrounding edge.
    HWND                hWndVolL_TXT;       // For the L
    HWND                hWndVolR_TXT;       // For the R

    #ifdef SHOWSTATUS
    HWND                hWndStatus_TXT;     // For status.
    HWND                hWndStatus_EDGE;
    HWND                hWndPlayPosition_TXT;
    HWND                hWndPlayPosition_EDGE;
    HWND                hWndWritePosition_TXT;
    HWND                hWndWritePosition_EDGE;
    #endif

    LPDIRECTSOUNDBUFFER pDSB;               // Pointer to direct sound buffer.

    int                 nFileName;          // Index to filename, not including dir.
    char                szFileName[MAX_PATH];
    struct _fileinfo    *pNext;             // Pointer to next file.

    } FILEINFO;

long FAR PASCAL WndProc(HWND, unsigned, WPARAM, LPARAM);
long FAR PASCAL DLGHelpAbout(HWND, UINT, WPARAM, LPARAM);
long FAR PASCAL DLGOutputBufferType(HWND, UINT, WPARAM, LPARAM);
long FAR PASCAL DLGCheckLatency(HWND, UINT, WPARAM, LPARAM);

BOOL ClassInit(HANDLE);
void PD_FileOpen(HWND);
BOOL OpenFileDialog(HWND, LPSTR, int *);
BOOL IsValidWave(LPSTR);

int CreateControl(HWND, FILEINFO *, DWORD, DWORD, DWORD);
void GetNextControlCoords(FILEINFO *, int *, int *);
int AddToList(FILEINFO *, FILEINFO *);
int FreeAllList(HWND, FILEINFO *);
int RemoveFromList(FILEINFO *, FILEINFO *);
int GetNumControls(FILEINFO *);
int StartDSound(HWND, FILEINFO *);
int StopDSound(HWND, FILEINFO *);
int StopAllDSounds(HWND, FILEINFO *);

BOOL UIMainWindowVSBHandler(HWND, WPARAM, LPARAM); 
BOOL UIMainWindowHSBHandler(HWND, WPARAM, LPARAM); 
BOOL UIMainWindowCMDHandler(HWND, WPARAM, LPARAM); 
BOOL UIMainWindowTimerHandler(HWND, WPARAM, LPARAM); 
void SetAllText(FILEINFO *);
void UpdateLRVolume(FILEINFO *);

void AppDestroy(HWND);
//void AppInit(HWND);

int NewDirectSoundBuffer(FILEINFO *);
int ReleaseDirectSoundBuffer(FILEINFO *);
int ChangeOutputPan(FILEINFO *);
int ChangeOutputFreq(FILEINFO *);
int ChangeOutputVol(FILEINFO *);

int FormatToIndex(HWND, FILEINFO *);
int IndexToFormat(HWND, FILEINFO *, int);
//
//
#ifdef __cplusplus
extern "C" {
#endif

extern float MaxSFXValue;
extern BOOL YBSndSilence;
void YBSetUpSoundSystem(HWND hWnd);
void YBLoadSounds(HWND hWnd, int Level, int Robot);
BOOL YBPlaySound(int idx);
//BOOL YBPlay3DSound(int idx, RLFrame noisyguy);
BOOL YBPlay3DSound(int idx, LPDIRECT3DRMFRAME noisyguy);
BOOL BYOBStopSound(int idx);
void YBUnLoadSoundSystem( HWND hWnd );
BOOL YBChangeVolume(int idx, int diff);
BOOL YBChangePan(int idx, int diff);
#ifdef __cplusplus
};
#endif

#endif  __YBSND_H__


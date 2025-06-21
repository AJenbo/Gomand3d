//*******************************************************************
// ybsnd.c
//
// Copyright 1996 by 47-TEK, INC.  All rights reserved.
//
// Author:	Bo Yuan
// 
// Date:	06/19/96
//
// Description:   This module contains a set of functions to control
//              sound play in the game.	
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
#include <direct.h>
#include "ybsnd.h"

extern char WavPath[127];
//extern RLFrame Robotframe;
//extern RLFrame monstframe;
extern LPDIRECT3DRMFRAME Robotframe;
extern LPDIRECT3DRMFRAME monstframe;
extern HWND  hWndMain;

BOOL   YBUnLoadAlready = TRUE;
BOOL   YBSndSilence = FALSE;

float  MaxSFXValue=(float)400.0;

int    YBPan;
char   value[MAX_PATH]="";
int  Total = 14;
static int SndFlag = 1;
HWND   hWndMain = NULL;
FILEINFO  FileInfoFirst;        // Start of linked list.

char            szFreq[]        = "Freq";
char            szPan[]         = "Pan";
char            szVolume[]      = "Volume";
char            szLooped[]      = "Looped";
char            szPlay[]        = "Play";
char            szStop[]        = "Stop";
char            szRemove[]      = "Close";

char *rgszTypes[C_DROPDOWNPCMFORMATS] = 
    {                                       // Index
    "8.000 kHz, 8-Bit, Mono",               // 0
    "8.000 kHz, 8-Bit, Stereo",             // 1
    "8.000 kHz, 16-Bit, Mono",              // 2
    "8.000 kHz, 16-Bit, Stereo",            // 3
    "11.025 kHz, 8-Bit, Mono",              // 4
    "11.025 kHz, 8-Bit, Stereo",            // 5
    "11.025 kHz, 16-Bit, Mono",             // 6
    "11.025 kHz, 16-Bit, Stereo",           // 7
    "22.050 kHz, 8-Bit, Mono",              // 8
    "22.050 kHz, 8-Bit, Stereo",            // 9
    "22.050 kHz, 16-Bit, Mono",             // 10
    "22,050 kHz, 16-Bit, Stereo",           // 11
    "44.100 kHz, 8-Bit, Mono",              // 12
    "44.100 kHz, 8-Bit, Stereo",            // 13
    "44.100 kHz, 16-Bit, Mono",             // 14
    "44.100 kHz, 16-Bit, Stereo"            // 15
    };                                      

BOOL                    rgfcoxAvail[MAXCONTROLS];

LPDIRECTSOUND           gpds            = NULL;
DWORD           dwTimer         = 0;        // Timer handle.
GUID                    guID;
BOOL                    fEnumDrivers = FALSE;

char MnstWav[7][6][10] = 
{
	{
		"TR101.WAV",
		"TR103.WAV",
		"TR106.WAV",
		"TR107.WAV",
		"TR109.WAV",
		"TR113.wav"
	},

	{
		"RO101.WAV",
		"RO103.WAV",
		"RO106.WAV",
		"RO107.WAV",
		"RO109.WAV",
		"RO113.wav"
	},

	{
		"KO101.WAV",
		"KO103.WAV",
		"KO106.WAV",
		"KO107.WAV",
		"KO109.WAV",
		"KO113.wav"
	},

	{
		"TO101.WAV",
		"TO103.WAV",
		"TO106.WAV",
		"TO107.WAV",
		"TO109.WAV",
		"TO113.wav"
	},

	{
		"SH101.WAV",
		"SH103.WAV",
		"SH106.WAV",
		"SH107.WAV",
		"SH109.WAV",
		"SH113.wav"
	},

	{
		"NE101.WAV",
		"NE103.WAV",
		"NE106.WAV",
		"NE107.WAV",
		"NE109.WAV",
		"NE113.wav"
	},			   

	{
		"GA101.WAV",
		"GA103.WAV",
		"GA106.WAV",
		"GA107.WAV",
		"GA109.WAV",
		"GA113.wav"
	}
};

char RobotWav[5][6][10] =
{
   {"SA101.WAV",
    "SA103.WAV",
	"SA106.WAV",
	"SA107.WAV",
	"SA111.WAV",
	"SA113.WAV"},
			   
   {"ST101.WAV",
    "ST103.WAV",
	"ST106.WAV",
	"ST107.WAV",
	"ST111.WAV",
	"ST113.WAV"},

   {"ME101.WAV",
    "ME103.WAV",
	"ME106.WAV",
	"ME107.WAV",
	"ME111.WAV",
	"ME113.WAV"},
   
   {"KT101.WAV",
    "KT103.WAV",
	"KT106.WAV",
	"KT107.WAV",
	"KT111.WAV",
	"KT113.WAV"},

   {"KB101.WAV",
    "KB103.WAV",
	"KB106.WAV",
	"KB107.WAV",
	"KB111.WAV",
	"KB113.WAV"}

};

char LevelWav[7][3][10] = 
{
   {"M0101.WAV",
    "M0102.WAV",
    "M0103.WAV"},
    
   {"M1101.WAV",
    "M1102.WAV",
    "M1103.WAV"},
    
   {"M2101.WAV",
    "M2102.WAV",
    "M2103.WAV"},

   {"M3101.WAV",
    "M3102.WAV",
    "M3103.WAV"},

   {"M4101.WAV",
    "M4102.WAV",
    "M4103.WAV"},

   {"M5101.WAV",
    "M5102.WAV",
    "M5103.WAV"},

   {"M6101.WAV",
    "M6102.WAV",
    "M6103.WAV"}

};
char EveryLevelWav[13][12] = 
{
    "EOW.WAV",
    "SPLTY.WAV",
    "SPLSH3.WAV",
    "FIRE.WAV",
    "BNCY.WAV",
    "SWRD.WAV",
	"FAILED2.WAV",
	"SCREAM1.WAV",
	"SCREAM2.WAV",
	"MX020.WAV",
   "MELT.WAV",
   "empty.wav",
   "MPWR.WAV"
};

//****************************************************************************
// Name:	void YBSetUpSoundSystem(HWND hWnd)
//
// Description:	This function sets up direct sound system for the game, it
//              defines the sound file format, frequency, volume, creates
//              a direct sound device, sets cooperative level, and then 
//              creates the primary sound buffer.
//
// Arguments:	HWND hWnd
//
// Return:		void 
//				
// Side effects:
//
// Notes:
//       This function is modified based on original MS DirectSound code.
//
// Known restrictions:
// 
// Update:
// Date			Name			Description
// ===========================================================================
//
//****************************************************************************
void YBSetUpSoundSystem(HWND hWnd)					
{

    UINT            cT;
    DSBUFFERDESC        dsbd;
    HRESULT         hr;
    MMRESULT        mmr;
    DWORD           dw;

    // Set up the global window handle.
    hWndMain = hWnd;

    // Set up the file info header
    FileInfoFirst.pNext = NULL;
    FileInfoFirst.pwfx = NULL;
    FileInfoFirst.cox = COX_STARTCONTROL;
    FileInfoFirst.coy = COY_STARTCONTROL;

    // Clear the coordinate buffer.  Used to find the next available
    // position to use for a new control.  -1 is the invalid value.
    for (cT=0; cT<MAXCONTROLS; cT++)
        rgfcoxAvail[cT] = FALSE;

    // Setup the timer...
    if ((dwTimer = SetTimer(hWnd, 1, TIMERPERIOD, NULL)) == 0)
        {
        hr = ER_TIMERALLOC;
        //MessageBox(hWnd, "Cannot allocate timer, aborting",
        //       "App Error", MB_OK|MB_ICONSTOP);
        goto ERROR_DONE_ROUTINE;
        }

    // Now set up all the direct sound stuff...

    // Get the largest waveformatex structure.
    if ((mmr = acmMetrics(NULL, ACM_METRIC_MAX_SIZE_FORMAT, &dw)) != 0)    
    {
        hr = mmr;
        //MessageBox(hWnd, "ACM Metrics failed, aborting",
        //       "App Error", MB_OK|MB_ICONSTOP);
        goto ERROR_DONE_ROUTINE;
    }


    // Setup the format, frequency, volume, etc.
    if ((FileInfoFirst.pwfx = GlobalAllocPtr(GPTR, dw)) == NULL)
    {
        //MessageBox(hWnd, "Memory startup error.",
        //             " Out of Memory", MB_OK|MB_ICONSTOP);
        goto ERROR_DONE_ROUTINE;
    }



    FileInfoFirst.pwfx->wFormatTag = WAVE_FORMAT_PCM;
    FileInfoFirst.pwfx->nChannels = 2;
    FileInfoFirst.pwfx->nSamplesPerSec = 22050;
    FileInfoFirst.pwfx->nAvgBytesPerSec = 22050*2*2;
    FileInfoFirst.pwfx->nBlockAlign = 4;
    FileInfoFirst.pwfx->wBitsPerSample = 16;
    FileInfoFirst.pwfx->cbSize = 0;
    
#ifdef STARTEIGHTBITS

    FileInfoFirst.pwfx->wFormatTag = WAVE_FORMAT_PCM;
    FileInfoFirst.pwfx->nChannels = 2;
    FileInfoFirst.pwfx->nSamplesPerSec = 22050;
    FileInfoFirst.pwfx->nAvgBytesPerSec = 22050*1*2;
    FileInfoFirst.pwfx->nBlockAlign = 2;
    FileInfoFirst.pwfx->wBitsPerSample = 8;
    FileInfoFirst.pwfx->cbSize = 0;


#endif
#ifdef STARTMONO    
    FileInfoFirst.pwfx->wFormatTag = WAVE_FORMAT_PCM;
    FileInfoFirst.pwfx->nChannels = 1;
    FileInfoFirst.pwfx->nSamplesPerSec = 22050;
    FileInfoFirst.pwfx->nAvgBytesPerSec = 22050*1*2;
    FileInfoFirst.pwfx->nBlockAlign = 2;
    FileInfoFirst.pwfx->wBitsPerSample = 16;
    FileInfoFirst.pwfx->cbSize = 0;
#endif
    
    // Optionally enumerate DSOUND devices and allow the user to pick one...

    /*if(( fEnumDrivers = (BOOL)GetProfileInt( "DSSHOW", "EnumDrivers", FALSE ))
           != FALSE )  {
        if( !DoDSoundEnumerate( &guID )) {
            hr = DirectSoundCreate( &guID, &gpds, NULL );
        } else {
            hr = DirectSoundCreate( NULL, &gpds, NULL );
    }
    } else { */
        hr = DirectSoundCreate( NULL, &gpds, NULL );
    //}
    
    if( hr != DS_OK )
        {
        //MessageBox(hWnd, "Direct Sound Creation Failed",
        //   "Critical Error", MB_OK|MB_ICONSTOP);
        goto ERROR_DONE_ROUTINE;         
        }

    // Note we need to set the level to be priority to set the
    // format of the primary buffer
    if(( hr = gpds->lpVtbl->SetCooperativeLevel( gpds,
                                              hWndMain,
                                              DSSCL_PRIORITY )) != DS_OK )
        {
        //MessageBox(hWnd, "Direct Sound Set Cooperative Level Failed",
        //   "Critical Error", MB_OK|MB_ICONSTOP);
        goto ERROR_DONE_ROUTINE;         
        }

    // Set up the primary direct sound buffer.
    memset(&dsbd, 0, sizeof(DSBUFFERDESC));
    dsbd.dwSize                 = sizeof(DSBUFFERDESC);
    dsbd.dwFlags                = DSBCAPS_PRIMARYBUFFER;
    
    if ((hr = gpds->lpVtbl->CreateSoundBuffer(gpds,
                          &dsbd,
                          &(FileInfoFirst.pDSB),
                          NULL )) != 0)
    {
    //MessageBox(hWnd, "Cannot create primary buffer",
    //           "Direct Sound Error", MB_OK|MB_ICONSTOP);
    goto ERROR_DONE_ROUTINE;
    }

    IDirectSoundBuffer_Play(FileInfoFirst.pDSB, 0, 0, DSBPLAY_LOOPING);

    //UpdateMainStatus();
SndFlag = 1;

    goto DONE_ROUTINE;

ERROR_DONE_ROUTINE: 
   // PostMessage(hWnd, WM_CLOSE, 0, 0);
        SndFlag = 0;		// new new

DONE_ROUTINE:
    return; 

}

//****************************************************************************
// Name:	void YBFileOpen( HWND hWnd, char *filename )
//
// Description:	This function is used to load a wav file into a new memory
//              buffer.  
//
// Arguments:	HWND hWnd   ... handler of the windows application
//             char *filename ... wave file name
//
// Return:		void 
//				
// Side effects:
//
// Notes:
//       This function is modified based on original MS DirectSound code.
//
// Known restrictions:
// 
// Update:
// Date			Name			Description
// ===========================================================================
//
//****************************************************************************
void YBFileOpen( HWND hWnd, char *filename )
{

	char            szFileName[MAX_PATH];
	UINT            cSamples;
	FILEINFO        *pFileInfo = NULL;
	int             nFileName;
	int				nFileIndex;

	nFileIndex = GetNumControls(&FileInfoFirst);
    if (nFileIndex >= MAXCONTROLS)
    {
	    //MessageBox(hWnd, "No more controls allowed",
        //           "Hold on a sec...", MB_OK);
	    return;
    }

    // Allocate the memory for the structure.
    if ((pFileInfo = GlobalAllocPtr(GPTR, sizeof(FILEINFO))) == NULL)
    {
        //MessageBox(hWnd, "Cannot add this file",
        //       "Out of Memory", MB_OK|MB_ICONSTOP);
        goto ERROR_DONE_ROUTINE;
    }
	if((nFileIndex == RobotJets) || (nFileIndex == EdgeOWorld))
		pFileInfo->fLooped=TRUE;
	else
		pFileInfo->fLooped=FALSE;

    pFileInfo->pbData   = NULL;
    pFileInfo->pwfx     = NULL;
    pFileInfo->pDSB     = NULL;
	// New New
	pFileInfo->dwVol    = (DWORD) MaxSFXValue;
	pFileInfo->dwPan    = 400;
	//
	strcpy(szFileName, filename);
    strcpy(pFileInfo->szFileName, szFileName);

    if (WaveLoadFile(szFileName, &pFileInfo->cbSize, 
            &cSamples, &pFileInfo->pwfx, &pFileInfo->pbData) != 0)
    {
        //MessageBox(hWnd, "Bad wave file or file too big to fit in memory",
                //"Cannot load wave", MB_OK|MB_ICONSTOP);
        //        filename, MB_OK|MB_ICONSTOP);
        goto ERROR_DONE_ROUTINE;
    }

    //GetNextControlCoords(&FileInfoFirst,
    //                 &pFileInfo->cox, &pFileInfo->coy);

    if (NewDirectSoundBuffer(pFileInfo) != 0)
    {
        //MessageBox(hWnd, "Cannot create new buffer",
        //       "Direct Sound Error", MB_OK|MB_ICONSTOP);
        goto ERROR_DONE_ROUTINE;
    }
        
    // Ok, now we can release the memory for the wave file,
    // its copied into the
    // direct sound secondary buffer.
    Assert(pFileInfo->pbData != NULL);
	/*
    if (pFileInfo->pbData != NULL)
    {
        GlobalFree(pFileInfo->pbData);
        pFileInfo->pbData = NULL;
    }
	*/

    // If we fail after this, make sure to update the list!!!
    if (AddToList(&FileInfoFirst, pFileInfo) != 0)
    {
        //MessageBox(hWnd, "Cannot add file to list",
        //           "Out of Memory", MB_OK|MB_ICONSTOP);
        goto ERROR_DONE_ROUTINE;
    }

    pFileInfo->nFileName = nFileName;
    //CreateControl(hWnd, pFileInfo, pFileInfo->pwfx->nSamplesPerSec,
    //          (MAXPAN_TB-MINPAN_TB)/2, MINVOL_TB );
    ChangeOutputVol(pFileInfo);
    //ChangeOutputFreq(pFileInfo);
    ChangeOutputPan(pFileInfo);
    //UpdateMainStatus();

    goto DONE_ROUTINE;
           
ERROR_DONE_ROUTINE:
    if (pFileInfo != NULL)
    {
        
    ReleaseDirectSoundBuffer(pFileInfo);

    if (pFileInfo->pwfx != NULL)
    {
        GlobalFree(pFileInfo->pwfx);
            
    }
    if (pFileInfo->pbData != NULL)
    {
        GlobalFree(pFileInfo->pbData);          
    }

    GlobalFreePtr(pFileInfo);
    pFileInfo = NULL;
    }

DONE_ROUTINE:
    return;

}

//****************************************************************************
// Name:	BOOL YBPlaySound(int idx)
//
// Description:	This function plays a sound indicated by the index value,
//                'idx'.  If it is a sound for movement, it will emulate a 3D
//                sound placement by changing sound volume or pans.
//
// Arguments:	int idx ... index value of a sound.
//
// Return:		BOOL 
//				
// Side effects:
//
// Notes:
//       This function is modified based on original MS DirectSound code.
//
// Known restrictions:
// 
// Update:
// Date			Name			Description
// ===========================================================================
//
//****************************************************************************
BOOL YBPlaySound(int idx)
{
    BOOL        fReturn     = FALSE;
    FILEINFO    *pFileInfo;
    FILEINFO    *pFileInfoNext;
//    DWORD       dwLooping;
	int i;
//	RLVector    p;
	D3DVECTOR    p;
	float       vol=(float)0.0;
	float       pnn=(float)0.0;
	int         volume=0;
	int         pnnpnn=0;

//                
	if (!SndFlag || YBSndSilence) return FALSE;

    pFileInfo = FileInfoFirst.pNext;

	for (i=0; i<idx; i++) {
		pFileInfoNext= pFileInfo->pNext;
		pFileInfo = pFileInfoNext;
	}
//
	if (idx>=6 && idx<11) {
		//RLFrameGetPosition(monstframe, Robotframe, &p);
		monstframe->lpVtbl->GetPosition(monstframe, Robotframe, &p);
		vol = p.z;
		pnn = p.x;

		if (vol<0) vol=-vol;
			vol = MaxSFXValue - (vol*MaxSFXValue)/(float)256.0;
		volume = (int)vol;
		pFileInfo->dwVol = volume;
		volume = 0;
		YBChangeVolume(idx, volume);

		if (pnn>0) { // monster is on the right side
			pnn = ((pnn*MaxSFXValue)/(float)256.0) + MaxSFXValue;
			pnnpnn = (int)pnn;
			pFileInfo->dwPan = pnnpnn;
			YBChangePan(idx, 0);
		}
		if (pnn<0) {
			pnn = MaxSFXValue + ((pnn*MaxSFXValue)/(float)256.0);
			pnnpnn = (int)pnn;
			pFileInfo->dwPan = pnnpnn;
			YBChangePan(idx, 0);
		}
	//sprintf(value, "pan = %+4.3f", pnn);
	//sprintf(value, "dwVol = %+4.3f, ", vol);
	//SetWindowText( hWndMain, value);

	}
	//YBPan = pFileInfo->dwPan;
	//sprintf(value, "dwVol = %d    dwPan = %d", pFileInfo->dwVol, YBPan);
	//SetWindowText( hWndMain, value);

    if (StartDSound(hWndMain, pFileInfo) == 0) {
        fReturn = TRUE;
    }
    
    fReturn = TRUE;
    
}

BOOL YBPlay3DSound(int idx, LPDIRECT3DRMFRAME noisyguy)
{
    FILEINFO    *pFileInfo;
    FILEINFO    *pFileInfoNext;
	int i;
	D3DVECTOR    p, splashdetect;
	D3DVALUE		dist2;
	float       vol=(float)0.0;
	float       pnn=(float)0.0;
	int         volume=0;
	int         pnnpnn=0;
	extern		LPDIRECT3DRMFRAME Wcamera, Wscene;
	extern		D3DVALUE	sealevel;

	if (!SndFlag || YBSndSilence) 
		return FALSE;

	if ((idx==RobotFootStep) || (idx==MonsterFootStep)) 
	{
		noisyguy->lpVtbl->GetPosition(noisyguy, Wscene, &splashdetect);
		if (splashdetect.y < sealevel) idx = Splash;
	}
    pFileInfo = FileInfoFirst.pNext;

	for (i=0; i<idx; i++) 
	{
		pFileInfoNext= pFileInfo->pNext;
		pFileInfo = pFileInfoNext;
	}

	noisyguy->lpVtbl->GetPosition(noisyguy, Wcamera, &p);
	dist2 = D3DRMVectorDotProduct(&p, &p);
	if (dist2>4096)//(64*64)) 
		return FALSE;
	
	p.y = D3DVAL(0.0);
	vol = D3DDivide(D3DVAL((32*32)*MaxSFXValue), dist2);
	if (vol>MaxSFXValue) vol = MaxSFXValue;

	volume = (int)vol;
	pFileInfo->dwVol = volume;
	volume = 0;
	YBChangeVolume(idx, volume);

	D3DRMVectorNormalize(&p);

	pnn = ((p.x) + (float)1.0) * (float)400.0;

	pnnpnn = (int)pnn;
	pFileInfo->dwPan = pnnpnn;
	YBChangePan(idx, 0);

    if (StartDSound(hWndMain, pFileInfo) == 0) 
	{
		return TRUE;
    }
	else
		return FALSE;

}

BOOL BYOBStopSound(int idx)
{
    FILEINFO    *pFileInfo;
    FILEINFO    *pFileInfoNext;
	int i;
	float       vol=(float)0.0;
	float       pnn=(float)0.0;
	int         volume=0;

	if (!SndFlag || YBSndSilence) return FALSE;

    pFileInfo = FileInfoFirst.pNext;

	for (i=0; i<idx; i++) 
	{
		pFileInfoNext= pFileInfo->pNext;
		pFileInfo = pFileInfoNext;
	}
	if (pFileInfo->fPlaying) 
		StopDSound(hWndMain, pFileInfo);
	else
		return FALSE;
    
	return TRUE;   
}

//****************************************************************************
// Name:	BOOL YBChangeVolume(int idx, int diff)
//
// Description:	This function is used to change the volume of a sound
//
// Arguments:	int idx ... index value of that sound
//             int diff ... sound volume
//
// Return:		BOOL 
//				
// Side effects:
//
// Notes:
//       This function is modified based on original MS DirectSound code.
//
// Known restrictions:
// 
// Update:
// Date			Name			Description
// ===========================================================================
//
//****************************************************************************
BOOL YBChangeVolume(int idx, int diff)
{
    BOOL        fReturn     = FALSE;
    FILEINFO    *pFileInfo;
    FILEINFO    *pFileInfoNext;
//    DWORD       dwLooping;
	int i;

//
	if (!SndFlag) return FALSE;

    pFileInfo = FileInfoFirst.pNext;

	for (i=0; i<idx; i++) {
		pFileInfoNext= pFileInfo->pNext;
		pFileInfo = pFileInfoNext;
	}
//
	if (pFileInfo->dwVol>400 || 
	    pFileInfo->dwVol<0   ||
	    (pFileInfo->dwVol==0 && diff<0)) {
		return FALSE;
	}

	pFileInfo->dwVol = pFileInfo->dwVol + diff;
	if (pFileInfo->dwVol>400) 
		pFileInfo->dwVol = 400;
	if (pFileInfo->dwVol<=0)
		pFileInfo->dwVol = 0;

	ChangeOutputVol(pFileInfo);

	//if (idx>6 && idx<11) {
	//   sprintf(value, "%d", pFileInfo->dwVol);
	//   SetWindowText( hWndMain, value);
	//   ;
	//}
    fReturn = TRUE;
    
}

//****************************************************************************
// Name:	BOOL YBChangePan(int idx, int diff)
//
// Description:	This function is used to change the pan value of a sound
//
// Arguments:	int idx ... index value of that sound
//             int diff ... pan value
//
// Return:		BOOL 
//				
// Side effects:
//
// Notes:
//       This function is modified based on original MS DirectSound code.
//
// Known restrictions:
// 
// Update:
// Date			Name			Description
// ===========================================================================
//
//****************************************************************************
BOOL YBChangePan(int idx, int diff)
{
    BOOL        fReturn     = FALSE;
    FILEINFO    *pFileInfo;
    FILEINFO    *pFileInfoNext;
//    DWORD       dwLooping;
	int i;

	// Note:   
	// 		diff > 0, left channel volume increase
	//      diff < 0, right channel volume increse
	//
	if (!SndFlag) 
	{
		return FALSE;
	}
    pFileInfo = FileInfoFirst.pNext;

	for (i=0; i<idx; i++) {
		pFileInfoNext= pFileInfo->pNext;
		pFileInfo = pFileInfoNext;
	}
//
	if (pFileInfo->dwPan>800 || 
	    pFileInfo->dwPan<0   ||
	    (pFileInfo->dwPan==0 && diff<0)) {
		return FALSE;
	}

	pFileInfo->dwPan = pFileInfo->dwPan + diff;
	if (pFileInfo->dwPan>800) 
		pFileInfo->dwPan = 800;
	if (pFileInfo->dwPan<=0)
		pFileInfo->dwPan = 0;

	YBPan = pFileInfo->dwPan;
	//sprintf(value, "dwPan = %d", YBPan);
	//SetWindowText( hWndMain, value);
	ChangeOutputPan(pFileInfo);

    fReturn = TRUE;
    
}

//****************************************************************************
// Name:	void YBLoadSounds(HWND hWnd, int Level, int Robot)
//
// Description:	This function is used to load all the sound files for a
//                particular Robot at a particular game level.
//
// Arguments:	HWND hWnd   ... handler of the windows application
//             int level ... game level
//             int Robot ... index value of a Robot
//
// Return:		void 
//				
// Side effects:
//
// Notes:
//
// Known restrictions:
// 
// Update:
// Date			Name			Description
// ===========================================================================
//
//****************************************************************************
void YBLoadSounds(HWND hWnd, int Level, int Robot)
{
    int i, j;
	char filename[127];

	if (!SndFlag) return;

	if (Level<0 || Level>6) return;

	j = Level;

	// load Robot wav files
	for (i=0; i<6; i++) {
		strcpy(filename, WavPath);
		strcat(filename, "\\");
		strcat(filename, RobotWav[Robot][i]);
		//YBFileOpen(hWnd, WavFiles[i]);
		YBFileOpen(hWnd, filename);
	}

	// load mnst wav files
	for (i=0; i<6; i++) {
		strcpy(filename, WavPath);
		strcat(filename, "\\");
		strcat(filename, MnstWav[j][i]);
		//YBFileOpen(hWnd, WavFiles[i]);
		YBFileOpen(hWnd, filename);
	}

	// load level wav files
	for (i=0; i<3; i++) {
		strcpy(filename, WavPath);
		strcat(filename, "\\");
		strcat(filename, LevelWav[j][i]);
		//YBFileOpen(hWnd, WavFiles[i]);
		YBFileOpen(hWnd, filename);
	}

	for (i=0; i<13; i++) {
		strcpy(filename, WavPath);
		strcat(filename, "\\");
		strcat(filename, EveryLevelWav[i]);
		YBFileOpen(hWnd, filename);
	}
    YBUnLoadAlready = FALSE;
}



/*  This routine will initialize a new direct sound buffer,
    set the data in the buffer, 
    set the rate, format, etc...

    Input:
        pFileInfo   -   Pointer to file info with all
        nessecary info filled, 
        like pbData, cbData, etc...

    Output:
        0 if successful, else the error code.

*/

int NewDirectSoundBuffer(
                    FILEINFO *pFileInfo
                    )
{

    DSBUFFERDESC        dsbd;
    DSBCAPS         dsbc;
    HRESULT         hr;
    BYTE            *pbData         = NULL;
    BYTE            *pbData2        = NULL;
    DWORD           dwLength;
    DWORD           dwLength2;

    // Set up the direct sound buffer. 
    memset(&dsbd, 0, sizeof(DSBUFFERDESC));
    dsbd.dwSize                 = sizeof(DSBUFFERDESC);
    dsbd.dwFlags                = 0;
    dsbd.dwFlags                |= DSBCAPS_STATIC;
    dsbd.dwFlags                |= DSBCAPS_CTRLDEFAULT;
    dsbd.dwBufferBytes               = pFileInfo->cbSize;
    dsbd.lpwfxFormat            = pFileInfo->pwfx;
    if ((hr = gpds->lpVtbl->CreateSoundBuffer(gpds,
                          &dsbd,
                          &(pFileInfo->pDSB),
                          NULL )) != 0)
        {
        goto ERROR_IN_ROUTINE;
        }

    // Ok, lock the sucker down, and copy the memory to it.
    if ((hr = pFileInfo->pDSB->lpVtbl->Lock(pFileInfo->pDSB,
                        0,
                        pFileInfo->cbSize,
                        &pbData,
                        &dwLength,
                        &pbData2,
                        &dwLength2,
                                            0L)) != 0)
    {
    goto ERROR_IN_ROUTINE;
    }

    Assert(pbData != NULL);
    memcpy(pbData, pFileInfo->pbData, pFileInfo->cbSize);

    // Ok, now unlock the buffer, we don't need it anymore.
    if ((hr = pFileInfo->pDSB->lpVtbl->Unlock(pFileInfo->pDSB,
                                              pbData, pFileInfo->cbSize,
                                              NULL, 0)) != 0)
    {
    goto ERROR_IN_ROUTINE;
    }

    pbData = NULL;

    if ((hr = pFileInfo->pDSB->lpVtbl->SetVolume(pFileInfo->pDSB,
            MAXVOL_VAL)) != 0)
    {
    goto ERROR_IN_ROUTINE;
    }

    if ((hr = pFileInfo->pDSB->lpVtbl->SetPan(pFileInfo->pDSB,
            MIDPAN_VAL)) != 0)
    {
    goto ERROR_IN_ROUTINE;
    }

    dsbc.dwSize = sizeof(dsbc);
    if (hr = IDirectSoundBuffer_GetCaps(pFileInfo->pDSB, &dsbc))
    {
    goto ERROR_IN_ROUTINE;
    }

    if (dsbc.dwFlags & DSBCAPS_LOCHARDWARE) {
    pFileInfo->fHardware = TRUE;
    } else {
    pFileInfo->fHardware = FALSE;
    }

    goto DONE_ROUTINE;

ERROR_IN_ROUTINE:
    if (pbData != NULL)
    {
    hr = pFileInfo->pDSB->lpVtbl->Unlock(pFileInfo->pDSB, pbData,
                                                pFileInfo->cbSize, NULL, 0);
    pbData = NULL;
    }

    if (pFileInfo->pDSB != NULL)
    {
    pFileInfo->pDSB->lpVtbl->Release(pFileInfo->pDSB);
    pFileInfo->pDSB = NULL;
    }
    
DONE_ROUTINE:

    return(hr); 

}

/*  This routine will release a direct sound buffer,
    freeing up memory, resources, 
    whatever.

    Input:
        pFileInfo   -   Pointer to the file info,
                with the proper stuff set.

    Output: 
        0 if successful, else the error code.

*/
int ReleaseDirectSoundBuffer( FILEINFO *pFileInfo )
{

    if (pFileInfo->pDSB != NULL)
    {
    pFileInfo->pDSB->lpVtbl->Release(pFileInfo->pDSB);
    pFileInfo->pDSB = NULL; 
    }

    return(0);

}

/*  This routine will find the next x and y coordinates to
    write the control to.
    The rgfcoxAvail is an array of booleans.
    If false, then the index can be 
    used as an x coordinate.

    Input:
        pFileInfoHead - Header of the linked list.
        pcox, pcoy    - Filled upon return with next
                coordinates to use.
        
    Output:
        Only pcox and pcoy change.
        
*/
        

/*  This will add to the linked list of FileInfo's.
    The FileInfo's keep track of the
    files loaded, and this is done in a linked list format

    Input:
        pFileInfoHead   -   Top of linked list.
        pFileInfo   -   Pointer to entry to add.

    Output:
        0 if successful, else the error code.

*/      

int AddToList(
                    FILEINFO *pFileInfoHead, 
                    FILEINFO *pFileInfo
                    )
{

    pFileInfo->pNext = NULL;    
    pFileInfo->fPlaying = FALSE;

    while (pFileInfoHead->pNext != NULL)
        {
        pFileInfoHead = pFileInfoHead->pNext;
        }

    pFileInfoHead->pNext = pFileInfo;

    return(0);

}

/*  This routine will get the number of controls in the window.
    Can be used to determine new size of window.

    Input:
        pFileInfoHead           -   Header of linked list.

    Output:
        # of controls.

*/

int GetNumControls( FILEINFO *pFileInfoHead )
{

    int cT  = 0;

    while (pFileInfoHead->pNext != NULL)
    {
    pFileInfoHead = pFileInfoHead->pNext;
    cT++;
    }

    return(cT);

}

/*  This routine will free the whole linked list in pFileInfoFirst,
    including all the
    memory used by the wave file, waveformatex structure, etc.

*/
int FreeAllList(
                    HWND hWnd, 
                    FILEINFO *pFileInfoFirst
                    )
{

    FILEINFO        *pFileInfo, *pFileNext;
    UINT        cT;

    Assert(pFileInfoFirst != NULL);
    pFileInfo = pFileInfoFirst->pNext;

    while (pFileInfo != NULL)
    {
    ReleaseDirectSoundBuffer(pFileInfo);
    GlobalFreePtr(pFileInfo->pwfx);
    GlobalFreePtr(pFileInfo->pbData);
    pFileNext = pFileInfo->pNext;
    GlobalFreePtr(pFileInfo);
    pFileInfo = pFileNext;
    }

    for (cT=0; cT<MAXCONTROLS; cT++)
    rgfcoxAvail[cT] = FALSE;



    return(0);          


}

/*  This routine will remove an entry from the list, i.e. will remove
    pFileInfo and all its allocated memory from the list pointed by the header
    by pFileInfoHead

    Input:
        pFileInfo               -   Pointer to entry to remove.
        pFileInfoHead           -   Head, first entry.

    Output:
        0 if successful, else the error.

*/
int RemoveFromList(
                    FILEINFO *pFileInfo, 
                    FILEINFO *pFileInfoHead
                    )
{

    FILEINFO        *pFileNext;

    Assert(pFileInfoHead != NULL);

    // This used to be pFileInfoHead != NULL
    while (pFileInfoHead->pNext != NULL)
        {
        if (pFileInfoHead->pNext == pFileInfo)
            {
            Assert(pFileInfo->cox/DX_CONTROLSPACING < MAXCONTROLS);
            rgfcoxAvail[pFileInfo->cox/DX_CONTROLSPACING] = FALSE;
           
            DestroyWindow(pFileInfo->hWndFileName_TXT); 
            DestroyWindow(pFileInfo->hWndFreq_TB);      
            DestroyWindow(pFileInfo->hWndFreq_TXT);     
            DestroyWindow(pFileInfo->hWndPan_TB);           
            DestroyWindow(pFileInfo->hWndPan_TXT);      
            DestroyWindow(pFileInfo->hWndVol_TXT);      
            DestroyWindow(pFileInfo->hWndVolL_TB);      
            DestroyWindow(pFileInfo->hWndVolR_TB);      
            DestroyWindow(pFileInfo->hWndVolM_TB);      
            DestroyWindow(pFileInfo->hWndLooped_BN);        
            DestroyWindow(pFileInfo->hWndPlay_BN);      
            DestroyWindow(pFileInfo->hWndRemove_BN);
            DestroyWindow(pFileInfo->hWndFileName_EDGE);
            DestroyWindow(pFileInfo->hWndLooped_EDGE);  
            DestroyWindow(pFileInfo->hWndFreq_EDGE);        
            DestroyWindow(pFileInfo->hWndPan_EDGE);     
            DestroyWindow(pFileInfo->hWndVol_EDGE);     
            DestroyWindow(pFileInfo->hWndWhole_EDGE);       
            DestroyWindow(pFileInfo->hWndVolL_TXT);     
            DestroyWindow(pFileInfo->hWndVolR_TXT);     
            #ifdef SHOWSTATUS
            DestroyWindow(pFileInfo->hWndStatus_TXT);
            DestroyWindow(pFileInfo->hWndStatus_EDGE);
            DestroyWindow(pFileInfo->hWndPlayPosition_TXT);
            DestroyWindow(pFileInfo->hWndPlayPosition_EDGE);
            DestroyWindow(pFileInfo->hWndWritePosition_TXT);
            DestroyWindow(pFileInfo->hWndWritePosition_EDGE);
            #endif




            GlobalFree(pFileInfoHead->pNext->pwfx);
            GlobalFree(pFileInfoHead->pNext->pbData);
            pFileNext = pFileInfoHead->pNext->pNext;
            GlobalFreePtr(pFileInfoHead->pNext);
            pFileInfoHead->pNext = pFileNext;                                                         
            break;
            }
        pFileInfoHead = pFileInfoHead->pNext;
        }

    return(0);
}


/*  This function will determine if the filename passed
    in is a valid wave for this
    app, that is a PCM wave.

    Input:
        pszFileName -   FileName to check.

    Output:
        FALSE if not a valid wave, TRUE if it is.
    
*/
BOOL IsValidWave(
                    LPSTR       pszFileName
                    )

{ 
    BOOL            fReturn     = FALSE;
    int             nError      = 0;
    HMMIO           hmmio;
    MMCKINFO        mmck;
    WAVEFORMATEX    *pwfx;

    if ((nError = WaveOpenFile(pszFileName, &hmmio, &pwfx, &mmck)) != 0)
        {       
        goto ERROR_IN_ROUTINE;
        }

    if (pwfx->wFormatTag != WAVE_FORMAT_PCM) 
        {
        goto ERROR_IN_ROUTINE;
        }

    WaveCloseReadFile(&hmmio, &pwfx);

    fReturn = TRUE;

ERROR_IN_ROUTINE:
    return(fReturn);    

}


//  This routine will start a sound to be played.  
//
//    Input:
//        hWnd        -   Of parent window.
//        pFileInfo   -   Pointer to file to start,
//                which is loaded and the
//                data is filled in the structure,
//                such as pbData, 
//                etc.
//
//    Output:
//        0 if successful, else the error code.
//

int StartDSound (HWND hWnd, FILEINFO *pFileInfo)
{

    DWORD    dwLooped;
    DWORD    dwStatus = 0;
    HRESULT  hr       = 0;

    // Already playing?

    // Start sound here....
    dwLooped = 0;
    if (pFileInfo->fLooped) {
	    dwLooped = DSBPLAY_LOOPING;
    }
    

    if ((hr = pFileInfo->pDSB->lpVtbl->GetStatus(pFileInfo->pDSB,
                         &dwStatus)) == 0)
    {
	    if ((dwStatus&DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
	    {
	        // Don't bother playing, just restart
	        if ((hr = pFileInfo->pDSB->lpVtbl->SetCurrentPosition(
	            pFileInfo->pDSB, 0)) != 0)
	        {
		        MessageBox(hWnd, "Cannot set current position",
	               "Direct Sound Error", MB_OK);
	        }
	    }
    // Yes gotos are bad but this is real life not school.
	    else goto PLAY_THE_THING;           
    }
    else
    {
PLAY_THE_THING:
	    if ((hr = pFileInfo->pDSB->lpVtbl->Play(pFileInfo->pDSB,
	                                            0, 0, dwLooped)) != 0)
	    {
		    MessageBox(hWnd, "Cannot start playing",
	           "Direct Sound Error", MB_OK);
	    }
	    else
		    pFileInfo->fPlaying = TRUE;
    }

    return(hr);


}

/*  This routine will stop a sound which is playing.

    Input:
        hWnd        - Of parent window.
        pFileInfo       - Pointer to file to stop playing.

    Output:
        0 if successful, else the error code.

*/
int StopDSound(     HWND hWnd, 
            FILEINFO *pFileInfo
            )

{
    HRESULT     hr          = 0;

    if (!pFileInfo->fPlaying)
    return(0);
           

    // Stop sound here...
    if ((hr = pFileInfo->pDSB->lpVtbl->Stop(pFileInfo->pDSB)) != 0) 
    {
    MessageBox(hWnd, "Cannot stop sound",
           "Direct Sound Error", MB_OK);        
    }
    else
    pFileInfo->fPlaying = FALSE;    

    return(hr);

}

/*  This routine will stop all the sounds which are playing.

    Input:
        hWnd        - Of parent window.
        pFileInfo   - Pointer to file to stop playing.
                (i.e. the head)

    Output:
        0 if successful, else the error code.

*/
int StopAllDSounds(
                    HWND hWnd, 
                    FILEINFO *pFileInfo
                    )

{

    while (pFileInfo->pNext != NULL)
        {
        StopDSound(hWnd, pFileInfo->pNext);
        pFileInfo = pFileInfo->pNext;       
        }

    return(0);

}


/*  This routine will update the left and right
    volume according to main volume 
    and pan.

    Input:
        pFileInfo   - Pointer to fileinfo to update.

    Output:
        Nothing worth using.
                    

*/
void UpdateLRVolume(
                    FILEINFO *pFileInfo
                    )
{

    int             volLeft, volRight;

    if (pFileInfo->dwPan < MIDPAN_TB)
    {
    volLeft = pFileInfo->dwVol;
    volRight = (((int)pFileInfo->dwPan)
            *(int)pFileInfo->dwVol)/((int)MIDPAN_TB);
    }
    else
    {
    volLeft = ((((int)pFileInfo->dwPan - MAXPAN_TB)*-1)
           *(int)pFileInfo->dwVol)/((int)MIDPAN_TB);
    volRight = pFileInfo->dwVol;
    }

        

    SendMessage(pFileInfo->hWndVolL_TB, TBM_SETPOS, TRUE, MAXVOL_TB-volLeft);
    SendMessage(pFileInfo->hWndVolR_TB, TBM_SETPOS, TRUE, MAXVOL_TB-volRight);
    
        

}

//
int ChangeOutputPan(FILEINFO *pFileInfo)
{
    HRESULT  hr = 0;

	// dwPan maximum value = 800
	// dwPan minimum value = 0
	// Note:
	// real pan maximum value = 4000
	// real pan manimum value = -4000
	// However, since this piece of code is simplified from GDK's
	// sample code "dsshow", it uses control bars.  I don't want
	// to change too much about the code, so I leave the code
	// about control bar here.  In this case, I still use their
	// value for the range of dwPan.  But just remeber the real
	// pan range so that you can use it in the future.
	// - Bo Yuan
	// 
    // Change PAN val  since TB does not go full range
    if ((hr = pFileInfo->pDSB->lpVtbl->SetPan(pFileInfo->pDSB,
        (((pFileInfo->dwPan) + SHIFTPAN_TB) * MULTPAN_TB) )) != 0)
    {
        goto ERROR_DONE_ROUTINE;
    }

ERROR_DONE_ROUTINE:
    return(hr);

}

/*  This will change the output freq for a certain FILEINFO.  This is 
    done by sending messages to the direct sound driver 

    Input:  
        pFileInfo                   -   FileInfo to set.  This must contain the
                                        freq value to set.

    Output:
        0 if successful, else the error code.

*/
int ChangeOutputFreq(FILEINFO *pFileInfo)
{
    HRESULT  hr = 0;

    if ((hr = pFileInfo->pDSB->lpVtbl->SetFrequency(pFileInfo->pDSB, 
                  pFileInfo->dwFreq*FREQMUL+FREQADD)) != 0)
    {
        goto ERROR_DONE_ROUTINE;
    }

ERROR_DONE_ROUTINE:
    return(hr);

}

//
int ChangeOutputVol(FILEINFO *pFileInfo)
{
    HRESULT     hr      = 0;

	// dwVol maximum value = 400
	// dwVol minimum value = 0
	// Note:
	// real volume maximum value = 0
	// real volume manimum value = -4000
	// However, since this piece of code is simplified from GDK's
	// sample code "dsshow", it uses control bars.  I don't want
	// to change too much about the code, so I leave the code
	// about control bar here.  In this case, I still use their
	// value for the range of dwVol.  But just remeber the real
	// volume range so that you can use it in the future.
	// - Bo Yuan
	// 
    // Shift VOLUME val by 4 bits since TB does not go full range
    if ((hr = pFileInfo->pDSB->lpVtbl->SetVolume(pFileInfo->pDSB,
        (((pFileInfo->dwVol) + SHIFTVOL_TB) * MULTVOL_TB) )) != 0)
    {
        goto ERROR_DONE_ROUTINE;
    }

ERROR_DONE_ROUTINE:
    return(hr);

}


/*  This routine will determine the output format in
    terms of an integer from the
    current output rate, type, etc.
    stored in the direct sound routines.   Integer
    values designate the string # in rgszTypes,
    i.e. index 0 is 8000kHz, 8 bit mono, 
    etc...

    Input:
        hWnd    - Handle of the current window.
        pFileInfo   - Pointer to the file info to retrieve the format for.

    Output:
        The index of the format, LB_ERR if undetermined.

*/
int FormatToIndex(
                    HWND        hWnd, 
                    FILEINFO    *pFileInfo
                    )

{

    WAVEFORMATEX    wfx;
    DWORD       dwWaveStyle;
    DWORD       dwSize;
    int         nError              = 0;

    // Get the format.
    if ((nError = pFileInfo->pDSB->lpVtbl->GetFormat(pFileInfo->pDSB,
            &wfx, sizeof(wfx), &dwSize)) != 0)
    {
    goto ERROR_IN_ROUTINE;
    }
    if( dwSize > sizeof( wfx ) ) {
    nError = DSERR_GENERIC;
    goto ERROR_IN_ROUTINE;
    }


    // Change wfx to an integer.
    // Assume theres an error and check all parameters to 
    // see if its valid.
    nError = LB_ERR;
    dwWaveStyle = 0;

    if (wfx.wFormatTag != WAVE_FORMAT_PCM)
           goto ERROR_IN_ROUTINE;

    // Check the channels
    if (wfx.nChannels == 1);
    else if (wfx.nChannels == 2)
    dwWaveStyle |= 1;
    else
    goto ERROR_IN_ROUTINE;

    // Check the bits...
    if (wfx.wBitsPerSample == 8);
    else if (wfx.wBitsPerSample == 16)
    dwWaveStyle |= 2;
    else
    goto ERROR_IN_ROUTINE;
    
    // Check the rate.
    if (wfx.nSamplesPerSec == 8000);
    else if (wfx.nSamplesPerSec == 11025)
    dwWaveStyle |= 4;
    else if (wfx.nSamplesPerSec == 22050)
    dwWaveStyle |= 8;
    else if (wfx.nSamplesPerSec == 44100)
    dwWaveStyle |= 12;
    else
    goto ERROR_IN_ROUTINE;
    
    nError = (int)dwWaveStyle;

ERROR_IN_ROUTINE:
    return(nError);
}


/*  This will convert an index (from a list box for instance)
    to a format by passing
    in the format to direct sound.

    Input:
        hWnd        -   Handle to window.
        pFileInfo   -   Pointer to current file info.
        index       -   Index value to convert to a
                    waveformat structure.

    Output:
        0 if successful, else the error code.

*/
int IndexToFormat(
                    HWND        hWnd, 
                    FILEINFO    *pFileInfo,
                    int         index
                    )

{

    int         nError      = 0;


    pFileInfo->pwfx->wFormatTag = WAVE_FORMAT_PCM;

    pFileInfo->pwfx->nChannels = 2;                                     // Assume stereo.
    if ((index%2) == 0)
    pFileInfo->pwfx->nChannels = 1;                                 // Its mono.
        
    // Assume 16 bit    
    pFileInfo->pwfx->nBlockAlign = 2*pFileInfo->pwfx->nChannels;
    pFileInfo->pwfx->wBitsPerSample = 16;
    if ((index%4) < 2) {
    // Its 8 bit.
    pFileInfo->pwfx->nBlockAlign = 1*pFileInfo->pwfx->nChannels;
    pFileInfo->pwfx->wBitsPerSample = 8;
    }
    
    pFileInfo->pwfx->nSamplesPerSec = 44100;    // Assume 44.1 kHz
    if (index < 4)
        pFileInfo->pwfx->nSamplesPerSec = 8000;
    else if (index < 8)
        pFileInfo->pwfx->nSamplesPerSec = 11025;
    else if (index < 12)
        pFileInfo->pwfx->nSamplesPerSec = 22050;
    
    
    pFileInfo->pwfx->nAvgBytesPerSec = pFileInfo->pwfx->nSamplesPerSec *
                       pFileInfo->pwfx->nBlockAlign;                                        
    pFileInfo->pwfx->cbSize = 0;

    if ((nError = pFileInfo->pDSB->lpVtbl->SetFormat(pFileInfo->pDSB,
                        pFileInfo->pwfx)) != DS_OK)         {
        MessageBox(hWnd, "Cannot set format buffer",
           "Direct Sound Error", MB_OK);
    goto ERROR_DONE_ROUTINE;

    }

ERROR_DONE_ROUTINE:
    return(nError);

}


//****************************************************************************
// Name:	void YBUnLoadSoundSystem( HWND hWnd )
//
// Description:	This function is used to unload the direct sound system.
//                It stops all sounds, frees sound file lists, destroys
//                direct sound buffers and object.
//
// Arguments:	HWND hWnd   ... handler of the windows application
//
// Return:		void 
//				
// Side effects:
//
// Notes:
//       This function is modified based on original MS DirectSound code.
//
// Known restrictions:
// 
// Update:
// Date			Name			Description
// ===========================================================================
//
//****************************************************************************
void YBUnLoadSoundSystem( HWND hWnd )
{

    HRESULT     hr = 0;

    if (YBUnLoadAlready)
        return;

    if (!SndFlag)       // new modification: 02/07/96
        return;

    if (dwTimer != 0)
    {
    KillTimer(hWnd, dwTimer);
    dwTimer = 0;
    }


    StopAllDSounds(hWnd, &FileInfoFirst);
    FreeAllList(hWnd, &FileInfoFirst);


    // Destroy the direct sound buffer.
    if(FileInfoFirst.pDSB != NULL) 
    {
    IDirectSoundBuffer_Stop(FileInfoFirst.pDSB);
    IDirectSoundBuffer_Release(FileInfoFirst.pDSB);
        FileInfoFirst.pDSB = NULL;
    }

    // Destroy the direct sound object.
    if (gpds != NULL)
    {
    IDirectSound_Release(gpds);
    gpds = NULL;
    }

    if (FileInfoFirst.pwfx != NULL)
    {
    GlobalFreePtr(FileInfoFirst.pwfx);
    FileInfoFirst.pwfx = NULL;
    }

    if (FileInfoFirst.pbData != NULL)
    {
    GlobalFreePtr(FileInfoFirst.pbData);
    FileInfoFirst.pbData = NULL;
    }
    
    WriteProfileString( "DSSHOW", "EnumDrivers", fEnumDrivers ? "1" : "0" );
    YBUnLoadAlready = TRUE;
}

// This function is not used in the game.
void YBUnLoadSoundSystem1( HWND hWnd )
{
    HRESULT hr = 0;

	if (!SndFlag) return;

    if (dwTimer != 0)
    {
	    KillTimer(hWnd, dwTimer);
	    dwTimer = 0;
    }

    StopAllDSounds(hWnd, &FileInfoFirst);
    FreeAllList(hWnd, &FileInfoFirst);

    // Destroy the direct sound buffer.
    if(FileInfoFirst.pDSB != NULL) 
    {
        FileInfoFirst.pDSB->lpVtbl->Release(FileInfoFirst.pDSB);
        FileInfoFirst.pDSB = NULL;
    }

    // Destroy the direct sound object.
    if (gpds != NULL)
    {
	    gpds->lpVtbl->Release(gpds);
	    gpds = NULL;
    }
    
    if (FileInfoFirst.pwfx != NULL)
    {
	    GlobalFreePtr(FileInfoFirst.pwfx);
	    FileInfoFirst.pwfx = NULL;
    }

    WriteProfileString( "DSSHOW", "EnumDrivers", fEnumDrivers ? "1" : "0" );
}

/*
void YBUnLoadSounds(HWND hWnd)
{
    HRESULT     hr = 0;

	if (!flag) return;

    if (dwTimer != 0)
    {
	    KillTimer(hWnd, dwTimer);
	    dwTimer = 0;
    }


    StopAllDSounds(hWnd, &FileInfoFirst);
    FreeAllList(hWnd, &FileInfoFirst);


    // Destroy the direct sound buffer.
    if(FileInfoFirst.pDSB != NULL) 
    {
    IDirectSoundBuffer_Stop(FileInfoFirst.pDSB);
    IDirectSoundBuffer_Release(FileInfoFirst.pDSB);
        FileInfoFirst.pDSB = NULL;
    }

}
*/

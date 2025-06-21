#ifdef MINIWIN
#include "miniwin/windows.h"
#else
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#endif
#include <memory.h>
#include <mmreg.h>

#include "midstuff.h"
#include "mstream.h"

char szAppTitle[64]="MIDI test";

extern char szAppTitle[64];
extern char szFileBuffer[64];
extern char szFileTitle[64];
extern char szTempo[64];
extern char szVolume[64];
extern char szProgress[64];
extern char szTemp[256];
extern char szDebug[256];

extern HWND hWndMain, hWndProg;
extern hWndProgText;
extern HINSTANCE hInst;
extern HMIDISTRM    hStream;
extern long MidVolume;

extern BOOL bFileOpen, bPlaying, bPaused, bInsertTempo;
extern int  nTextControlHeight;
extern DWORD    dwBufferTickLength, dwTempoMultiplier, dwCurrentTempo;
extern DWORD    dwProgressBytes, dwVolumePercent, dwVolCache[NUM_CHANNELS];

#ifdef DEBUG
extern HWND hWndList;
#endif


/********************************************************************************/
/* UpdateFromControls()                                                         */
/*                                                                              */
/*    This function gets all the required values from the DirectSoundBuffer and */
/* updates the screen interface controls.                                       */
/*                                                                              */
/********************************************************************************/
void UpdateFromControls( void )
{
	dwVolumePercent = MidVolume;
	if( hStream )
		SetAllChannelVolumes( dwVolumePercent );

	bInsertTempo = TRUE;
	return;
}


/****************************************************************************/
/* ErrorMessageBox()                                                        */
/*                                                                          */
/*   A little routine to load error messages from the string resource table */
/* and pop them up in a MessageBox() for the world to see. The dwMBFlags    */
/* parameter allows the caller to specify the type of icon to use.          */
/*                                                                          */
/****************************************************************************/
void ErrorMessageBox( UINT uID, DWORD dwMBFlags )
{
	//LoadString( hInst, uID, szTemp, sizeof(szTemp));
	//MessageBox( GetActiveWindow(), szTemp, szAppTitle, MB_OK | dwMBFlags );
#ifdef DEBUG
	//wsprintf( szDebug, "General error: %s", szTemp );
	//DebugPrint( szDebug );
#endif
}


/****************************************************************************/
/* MidiErrorMessageBox()                                                    */
/*                                                                          */
/*   Calls the midiOutGetErrorText() function and displays the text which   */
/* corresponds to a midi subsystem error code.                              */
/*                                                                          */
/****************************************************************************/
void MidiErrorMessageBox( MMRESULT mmr )
{
	//midiOutGetErrorText( mmr, szTemp, sizeof(szTemp));
	//MessageBox( GetActiveWindow(), szTemp, szAppTitle,
	//				MB_OK | MB_ICONSTOP );
#ifdef DEBUG
	//wsprintf( szDebug, "Midi subsystem error: %s", szTemp );
	//DebugPrint( szDebug );
#endif
}

/****************************************************************************/
/* SetAllChannelVolumes()                                                   */
/*                                                                          */
/*   Given a percent in tenths of a percent, sets volume on all channels to */
/* reflect the new value.                                                   */
/****************************************************************************/
void SetAllChannelVolumes( DWORD dwVolumePercent )
{
//	DWORD	dwEvent, dwVol;
	DWORD   dwStatus, idx;
	DWORD   v1, v2, v3, RealVol;
	MMRESULT    mmrRetVal;

	//if( !bPlaying )
	//return;


	for( idx = 0, dwStatus = MIDI_CTRLCHANGE; idx < NUM_CHANNELS; idx++,
                                dwStatus++ )
	{
		v3 = MidVolume / 10;
		v1 = v3 % 101;
		v2 = (DWORD) (v1*(0xffff))/100;
		RealVol = ((DWORD)v2<<16|v2);

		if (( mmrRetVal = midiOutSetVolume(hStream, (DWORD)RealVol)) != MMSYSERR_NOERROR)
		{
			//MidiErrorMessageBox( mmrRetVal );
			return;
		}
	}

}


/****************************************************************************/
/* SetChannelVolume()                                                       */
/*                                                                          */
/*   Given a percent in tenths of a percent, sets volume on a specified     */
/* channel to reflect the new value.                                        */
/****************************************************************************/
void SetChannelVolume( DWORD dwChannel, DWORD dwVolumePercent )
{
	DWORD dwEvent, dwVol;
	MMRESULT mmrRetVal;

	//if ( !bPlaying )
	//	return;

	dwVol = ( dwVolCache[dwChannel] * dwVolumePercent ) / 1000;
	dwEvent = MIDI_CTRLCHANGE | dwChannel | ((DWORD)MIDICTRL_VOLUME << 8)
                            | ((DWORD)dwVol << 16);
	if (( mmrRetVal = midiOutShortMsg( (HMIDIOUT)hStream, dwEvent ))
                            != MMSYSERR_NOERROR )
	{
		//MidiErrorMessageBox( mmrRetVal );
		return;
	}
}

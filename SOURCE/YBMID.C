//*******************************************************************
// ybmid.c
//
// Copyright 1996 by 47-TEK, INC.  All rights reserved.
//
// Author:	Bo Yuan
// 
// Date:	01/14/97
//
// Description:	This module contains a set of functions to control
//              MIDI play in the game.	
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
#include "ybmid.h"
#include "mstream.h"
#include "global.h"

extern INFILESTATE ifs;
extern char MidPath[127];

BOOL MidFlag=TRUE;
DWORD dwBufferTickLength, dwTempoMultiplier=100, dwCurrentTempo, dwProgressBytes;
CONVERTINFO  ciStreamBuffers[NUM_STREAM_BUFFERS];
DWORD dwVolCache[NUM_CHANNELS];
int nCurrentBuffer;
long nEmptyBuffers;
BOOL bBuffersPrepared = FALSE;
HMIDISTRM    hStream;
BOOL bFileOpen = FALSE;
BOOL bPlaying = FALSE;
BOOL bPaused = FALSE;
BOOL bLooped = FALSE;
UINT uMIDIDeviceID = MIDI_MAPPER;
DWORD dwVolumePercent;
HANDLE hBufferReturnEvent;
UINT uCallbackStatus;
MMRESULT mmrRetVal;
char szFileBuffer[MAX_PATH];

long MidTempo = 100;
long MidVolume = 1000;

//*******************************************************************
// Name:	YBSetMidiVolume(int Value)
//
// Description: Set midi volume for all the channels.  If the input 
//              value is beyond the range or MidFlag is FALSE, then
//              don't set the volume.  If the Midi system is not set
//              up yet, then don't set the volume.
//
// Arguments:	int Value	... volume value (0 ~ 1000)
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
// ==================================================================
//
//*******************************************************************
void YBSetMidiVolume(int Value)
{
	if (Value>VOL_TB_MAX || Value<VOL_TB_MIN)
	{
		return;
	}

	if (!MidFlag)
	{
		return;
	}

	MidVolume = Value;
	UpdateFromControls();
}

//*******************************************************************
// Name:	BOOL YBSetLoopDMidi(BOOL v)
//
// Description:	Set the midi loop flag with the value of v. 
//
// Arguments:	BOOL v ... TRUE = loop, FALSE = not loop
//
// Return:		BOOL v
//                      
// Side effects:
//
// Notes:
//
// Known restrictions:
// 
// Update:
// Date			Name			Description
// ==================================================================
//
//*******************************************************************
BOOL YBSetLoopDMidi(BOOL v)   // v = TRUE = loop; v = FALSE = not loop
{
	bLooped = v;
	return (bLooped);
}

//*******************************************************************
// Name:	void YBSetupDMidi(void)
//
// Description:	This function calls function 'UpdateFromControls'
//             to initial values of Tempo and volume, then set up
//             the midi system.
//
// Arguments:	void
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
// ==================================================================
//
//*******************************************************************
void YBSetupDMidi(void)
{
   UpdateFromControls();

   if (!MidFlag) 
   {
      return;
   }

   if ((mmrRetVal = midiStreamOpen(&hStream,
                    &uMIDIDeviceID,
                    (DWORD)1, (DWORD)MidiProc,
                    (DWORD)0,
                    CALLBACK_FUNCTION)) != MMSYSERR_NOERROR)
   {
      ;
   }
}

//*******************************************************************
// Name:	void YBQuitDMidi(void)
//
// Description:	If the MIDI system is on, free streaming buffer,
//                close MIDI system, set streaming handler to NULL.
//                
// Arguments:	void
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
// ==================================================================
//
//*******************************************************************
void YBQuitDMidi(void)
{
   if (!MidFlag)
   {
      return;
   }

   FreeBuffers();

   if (hStream)
   {
      if ((mmrRetVal = midiStreamClose(hStream)) != MMSYSERR_NOERROR)
      {
         MidiErrorMessageBox(mmrRetVal);
      }
      hStream = NULL;
   }

   CloseHandle(hBufferReturnEvent);
}

//*******************************************************************
// Name:	void YBCreateEvent(void)
//
// Description:  If MIDI system is on, create an MIDI event for MIDI
//               event procedure.
//                
//                
// Arguments:	void
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
// ==================================================================
//
//*******************************************************************
void YBCreateEvent(void)
{
   if (!MidFlag) 
   {
      return;
   }

   hBufferReturnEvent = 
		CreateEvent(NULL, FALSE, FALSE, "Wait For Buffer Return");
}

//
//*******************************************************************
// Name:	void YBLoadDMidi(char *filename)
//
// Description:  If MIDI system is on, load the MIDI file into the
//               stream buffer, and set bFileOpen flag.
//                
// Arguments:	char *filename ... MIDI file name
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
// ==================================================================
//
//*******************************************************************

void YBLoadDMidi(char *filename)
{
   if (!MidFlag) 
   {
      return;
   }

   strcpy(szFileBuffer, MidPath);
   strcat(szFileBuffer, "\\");
   strcat(szFileBuffer, filename);

   if (!StreamBufferSetup())
   {
      bFileOpen = TRUE;
   }
   else
   {
	   BYDumpInfo("*****************");
	   BYDumpInfo("Couldn't open the midi:");
	   BYDumpInfo(szFileBuffer);
	   BYDumpInfo("*****************");
	   
		bFileOpen = FALSE;

   }
}

//*******************************************************************
// Name:	BOOL YBPlayDMidi(void)
//
// Description:	If MIDI system doesn't set up yet, do nothing
//                Play MIDI if the MIDI file is loaded already.
//                
// Arguments:	void
//
// Return:		BOOL
//                      
// Side effects:
//
// Notes:
//
// Known restrictions:
// 
// Update:
// Date			Name			Description
// ==================================================================
//
//*******************************************************************
BOOL YBPlayDMidi(void)
{
   if (!MidFlag) 
   {
      return FALSE;
   }

   if (bFileOpen)
   {
      uCallbackStatus = 0;
      if ((mmrRetVal = midiStreamRestart(hStream))
			 != MMSYSERR_NOERROR)
		{
			MidiErrorMessageBox( mmrRetVal );
			return FALSE;
		}
      bPlaying = TRUE;
   }
	return TRUE;
} 

//*******************************************************************
// Name:	BOOL YBStopDMidi(WPARAM wParam)
//
// Description:	If MIDI system doesn't set up yet, do nothing
//                If MIDI file is open or is played, stop it, reset
//                MIDI, free buffer.
//                
// Arguments:	wParam
//
// Return:		BOOL
//                      
// Side effects:
//
// Notes:
//
// Known restrictions:
// 
// Update:
// Date			Name			Description
// ==================================================================
//
//*******************************************************************
BOOL YBStopDMidi(WPARAM wParam)
{
	MMRESULT    mmrRetVal;

   if (!MidFlag) return FALSE;

   if (bFileOpen || bPlaying
                 || (uCallbackStatus != STATUS_CALLBACKDEAD))
   {
      bPlaying = bPaused = FALSE;
      if (uCallbackStatus != STATUS_CALLBACKDEAD && 
          uCallbackStatus != STATUS_WAITINGFOREND)
      {
         uCallbackStatus = STATUS_KILLCALLBACK;
      }

      if ((mmrRetVal = midiStreamStop(hStream))
                        != MMSYSERR_NOERROR)
      {
         MidiErrorMessageBox(mmrRetVal);
			return FALSE;
      }

      if ((mmrRetVal = midiOutReset((HMIDIOUT)hStream))
                        != MMSYSERR_NOERROR)
      {
         MidiErrorMessageBox(mmrRetVal);
			return FALSE;
      }

      // Wait for the callback thread to release this thread, which it 
      // will do by calling SetEvent() once all buffers are returned to it
      if (WaitForSingleObject(hBufferReturnEvent,
                    DEBUG_CALLBACK_TIMEOUT)
                           == WAIT_TIMEOUT)
      {
         // Note, this is a risky move because the callback may be genuinely
         // busy, but when we're debugging, it's safer and faster than 
         // freezing the application, which leaves the MIDI device locked
         // up and forces a system reset...
         uCallbackStatus = STATUS_CALLBACKDEAD;
      }
   }

   if (uCallbackStatus == STATUS_CALLBACKDEAD)
   {
      uCallbackStatus = 0;
      if (bFileOpen)
      {
         ConverterCleanup();
         FreeBuffers();
         if (hStream)
         {
            if ((mmrRetVal = midiStreamClose(hStream))
                          != MMSYSERR_NOERROR)
            {
               MidiErrorMessageBox(mmrRetVal);
            }
            hStream = NULL;
         }
         bFileOpen = FALSE;
      }
                
      if (!(HIWORD(wParam) & MSTREAM_STOPF_NOREOPEN))
      {
         if (StreamBufferSetup())
         {
            // Error setting up for MIDI file
            // Notification is already taken care of...
            return FALSE;
         }
         else
         {
            bFileOpen = TRUE;
         }
      }
   }
	return TRUE;
}

//*******************************************************************
// Name:	BOOL StreamBufferSetup(void)
//
// Description:	This opens a MIDI stream buffer if that buffer is
//             not opened yet, then load the MIDI file into memory
//             and perform necessary initialization for MIDI play,
//             set properties and values for MIDI play, and then
//             begin to play.
//               
//                
// Arguments:	void
//
// Return:		BOOL 
//                      
// Side effects:
//
// Notes:
//
// Known restrictions:
// 
// Update:
// Date			Name			Description
// ==================================================================
//
//*******************************************************************
BOOL StreamBufferSetup(void)
{
   int     nChkErr;
   BOOL    bFoundEnd = FALSE;
   DWORD   dwConvertFlag, idx;

   MIDIPROPTIMEDIV mptd;

   if (!hStream) 
   {
      if ((mmrRetVal = midiStreamOpen(&hStream,
                    &uMIDIDeviceID,
                    (DWORD)1, (DWORD)MidiProc,
                    (DWORD)0,
                    CALLBACK_FUNCTION)) != MMSYSERR_NOERROR)
      {
         MidiErrorMessageBox(mmrRetVal);
         return(TRUE);
      }
   }

   for (idx = 0; idx < NUM_STREAM_BUFFERS; idx++)
   {
      ciStreamBuffers[idx].mhBuffer.dwBufferLength = OUT_BUFFER_SIZE;
      if ((ciStreamBuffers[idx].mhBuffer.lpData
         = GlobalAllocPtr(GHND, OUT_BUFFER_SIZE)) == NULL)
      {
        // Buffers we already allocated will be killed by WM_DESTROY
        // after we fail on the create by returning with -1
        return(-1);
      }
   }

   if (ConverterInit(szFileBuffer))
   {
      return(TRUE);
   }

   // Initialize the volume cache array to some pre-defined value
   for (idx = 0; idx < NUM_CHANNELS; idx++)
   {
      dwVolCache[idx] = VOL_CACHE_INIT;
   }

   mptd.cbStruct = sizeof(mptd);
   mptd.dwTimeDiv = ifs.dwTimeDivision;
   if ((mmrRetVal = midiStreamProperty(hStream, (LPBYTE)&mptd,
                        MIDIPROP_SET | MIDIPROP_TIMEDIV))
                                != MMSYSERR_NOERROR)
   {
      MidiErrorMessageBox(mmrRetVal);
      ConverterCleanup();
      return(TRUE);
   }

   nEmptyBuffers = 0;
   dwConvertFlag = CONVERTF_RESET;

   for (nCurrentBuffer = 0; nCurrentBuffer < NUM_STREAM_BUFFERS;
                                    nCurrentBuffer++)
   {
      // Tell the converter to convert up to one entire buffer's length of output
      // data. Also, set a flag so it knows to reset any saved state variables it
      // may keep from call to call.
      ciStreamBuffers[nCurrentBuffer].dwStartOffset = 0;
      ciStreamBuffers[nCurrentBuffer].dwMaxLength = OUT_BUFFER_SIZE;
      ciStreamBuffers[nCurrentBuffer].tkStart = 0;
      ciStreamBuffers[nCurrentBuffer].bTimesUp = FALSE;

      if ((nChkErr = ConvertToBuffer(dwConvertFlag,
                    &ciStreamBuffers[nCurrentBuffer]))
                                != CONVERTERR_NOERROR)
      {
         if (nChkErr == CONVERTERR_DONE)
         {
            bFoundEnd = TRUE;
         }
         else
         {
            ConverterCleanup();
            return( TRUE );
         }
      }
      ciStreamBuffers[nCurrentBuffer].mhBuffer.dwBytesRecorded
                = ciStreamBuffers[nCurrentBuffer].dwBytesRecorded;

      if (!bBuffersPrepared)
      {
         if ((mmrRetVal = midiOutPrepareHeader((HMIDIOUT)hStream,
                    &ciStreamBuffers[nCurrentBuffer].mhBuffer,
                    sizeof(MIDIHDR))) != MMSYSERR_NOERROR)
         {
            MidiErrorMessageBox(mmrRetVal);
            ConverterCleanup();
            return(TRUE);
         }
      }

      if ((mmrRetVal = midiStreamOut(hStream,
                 &ciStreamBuffers[nCurrentBuffer].mhBuffer,
                 sizeof(MIDIHDR))) != MMSYSERR_NOERROR)
      {
         MidiErrorMessageBox(mmrRetVal);
         break;
      }
      dwConvertFlag = 0;

      if (bFoundEnd)
         break;
   }  // end of for loop

   bBuffersPrepared = TRUE;
   nCurrentBuffer = 0;
   UpdateFromControls();
   return(FALSE);
}

//*******************************************************************
// Name:		void FreeBuffers( void )
//
// Description:	This function frees MIDI stream buffers.
//               
// Arguments:	void
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
// ==================================================================
//
//*******************************************************************

void FreeBuffers( void )
{
	DWORD   idx;
	MMRESULT    mmrRetVal;

	if( bBuffersPrepared )
	{
		for( idx = 0; idx < NUM_STREAM_BUFFERS; idx++ )
			if(( mmrRetVal = midiOutUnprepareHeader((HMIDIOUT)hStream,
                &ciStreamBuffers[idx].mhBuffer,
                sizeof(MIDIHDR)))
                        != MMSYSERR_NOERROR )
			{
				MidiErrorMessageBox( mmrRetVal );
			}
		bBuffersPrepared = FALSE;
	}

	// Free our stream buffers...
	for( idx = 0; idx < NUM_STREAM_BUFFERS; idx++ )
		if( ciStreamBuffers[idx].mhBuffer.lpData )
		{
			GlobalFreePtr( ciStreamBuffers[idx].mhBuffer.lpData );
			ciStreamBuffers[idx].mhBuffer.lpData = NULL;
		}
}

//*******************************************************************
// Name: void CALLBACK MidiProc( HMIDIIN hMidi, UINT uMsg, 
//                               DWORD dwInstance,
//                               DWORD dwParam1, DWORD dwParam2 )
//
// Description:	This function handles all the MIDI events/messages.
//               
// Arguments:	void
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
// ==================================================================
//
//*******************************************************************
void CALLBACK MidiProc( HMIDIIN hMidi, UINT uMsg, DWORD dwInstance,
								DWORD dwParam1, DWORD dwParam2 )
{
	static int nWaitingBuffers = 0;
	MIDIEVENT *pme;
	MIDIHDR *pmh;

	int nChkErr;


	switch( uMsg )
	{
	case MOM_DONE:
		if( uCallbackStatus == STATUS_CALLBACKDEAD )
			return;

		nEmptyBuffers++;

		if( uCallbackStatus == STATUS_WAITINGFOREND )
		{
			if( nEmptyBuffers < NUM_STREAM_BUFFERS )
			{
            return;
			}
			else
			{
            uCallbackStatus = STATUS_CALLBACKDEAD;
            //PostMessage( hWndMain, WM_COMMAND,
            //        MAKEWPARAM( IDC_STOP, 0 ), 0L );
				YBStopDMidi(0);
            SetEvent( hBufferReturnEvent );
            return;
			}
		}

		// This flag is set whenever the callback is waiting for all buffers to
		// come back.
		if( uCallbackStatus == STATUS_KILLCALLBACK )
		{
			// Count NUM_STREAM_BUFFERS-1 being returned for the last time
			if( nEmptyBuffers < NUM_STREAM_BUFFERS )
			{
				return;
			}
			// Then send a stop message when we get the last buffer back...
			else
			{
            // Change the status to callback dead
            uCallbackStatus = STATUS_CALLBACKDEAD;
            SetEvent( hBufferReturnEvent );
            return;
			}
		}

		dwProgressBytes
			+= ciStreamBuffers[nCurrentBuffer].mhBuffer.dwBytesRecorded;

///////////////////////////////////////////////////////////////////////////////
// Fill an available buffer with audio data again...

		if( bPlaying && nEmptyBuffers )
		{
			ciStreamBuffers[nCurrentBuffer].dwStartOffset = 0;
			ciStreamBuffers[nCurrentBuffer].dwMaxLength = OUT_BUFFER_SIZE;
			ciStreamBuffers[nCurrentBuffer].tkStart = 0;
			ciStreamBuffers[nCurrentBuffer].dwBytesRecorded = 0;
			ciStreamBuffers[nCurrentBuffer].bTimesUp = FALSE;

			if(( nChkErr = ConvertToBuffer( 0,
                        &ciStreamBuffers[nCurrentBuffer] ))
                                != CONVERTERR_NOERROR )
			{
            if( nChkErr == CONVERTERR_DONE )
            {
            // Don't include this one in the count
					nWaitingBuffers = NUM_STREAM_BUFFERS - 1;
					uCallbackStatus = STATUS_WAITINGFOREND;
					return;
            }
            else
            {
					ConverterCleanup();
					return;
            }
         }

			ciStreamBuffers[nCurrentBuffer].mhBuffer.dwBytesRecorded
                = ciStreamBuffers[nCurrentBuffer].dwBytesRecorded;


			if(( mmrRetVal = midiStreamOut( (HMIDIOUT)hStream,
                    &ciStreamBuffers[nCurrentBuffer].mhBuffer,
                    sizeof(MIDIHDR))) != MMSYSERR_NOERROR )
			{
            MidiErrorMessageBox( mmrRetVal );
            ConverterCleanup();
            return;
			}

			nCurrentBuffer = ( nCurrentBuffer + 1 ) % NUM_STREAM_BUFFERS;
			nEmptyBuffers--;
		}
		break;

	case MOM_POSITIONCB:
		pmh = (MIDIHDR *)dwParam1;
		pme = (MIDIEVENT *)(pmh->lpData + pmh->dwOffset);
		if( MIDIEVENT_TYPE( pme->dwEvent ) == MIDI_CTRLCHANGE )
		{
			if( MIDIEVENT_DATA1( pme->dwEvent ) == MIDICTRL_VOLUME_LSB )
			{
            break;
			}
			if( MIDIEVENT_DATA1( pme->dwEvent ) != MIDICTRL_VOLUME )
            break;

			// Mask off the channel number and cache the volume data byte
			dwVolCache[ MIDIEVENT_CHANNEL( pme->dwEvent )]
                    = MIDIEVENT_VOLUME( pme->dwEvent );
			// Post a message so that the main program knows to counteract
			// the effects of the volume event in the stream with its own
			// generated event which reflects the proper trackbar position.
			SetChannelVolume(MIDIEVENT_CHANNEL(pme->dwEvent), dwVolumePercent);
		}
		break;

	default:
		break;
	}

	return;
}

//*******************************************************************
// Name: void BYChangeMidTempo(int direction)
//
// Description:	This function changes the Midi Tempo
//               
// Arguments:	direction
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
// ==================================================================
//
//*******************************************************************
void BYChangeMidTempo(int direction)
{
	long  lDelta;

	if (!MidFlag)
	{
		return;
	}

	lDelta = 0;
	if (direction==MMV_DECREASE)
	{
		if( MidTempo >= TEMPO_MIN+MID_TMP_CHANGE )
			 lDelta = - MID_TMP_CHANGE;
	}
	else if (direction==MMV_INCREASE)
	{
      if( MidTempo <= TEMPO_MAX-MID_TMP_CHANGE )
          lDelta = MID_TMP_CHANGE;
	} else
	{
		lDelta = 0;
	}

	if( lDelta )
	{
		dwTempoMultiplier = (DWORD)( MidTempo + lDelta );
	}
	else
	{
		dwTempoMultiplier = (DWORD) MidTempo;
	}

	UpdateFromControls();
}

//*******************************************************************
// Name: void BYChangeMidVolume(int direction)
//
// Description:	This function changes the Midi volume
//               
// Arguments:	direction
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
// ==================================================================
//
//*******************************************************************
void BYChangeMidVolume(int direction)
{
	long lDelta;

	if (!MidFlag)
	{
		return;
	}

	lDelta = 0;
	if (direction==MMV_DECREASE)
	{
		if( MidVolume >= VOL_TB_MIN+MID_VOL_CHANGE )
			 lDelta = - MID_VOL_CHANGE;
	}
	else if (direction==MMV_INCREASE)
	{
      if (MidVolume <= VOL_TB_MAX-MID_VOL_CHANGE)
          lDelta = MID_VOL_CHANGE;
	} else
	{
		lDelta = 0;
	}

	MidVolume += lDelta;
	UpdateFromControls();
}


void YBPauseMidiPlay(void)
{
	midiStreamPause( hStream );
}

void YBResumeMidiPlay(void)
{
	midiStreamRestart( hStream );
}

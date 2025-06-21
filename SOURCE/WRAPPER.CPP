/*
$Header:   H:/pvcs/pvcsproj/gomand3d.prj/WRAPPER.CPV   1.96   16 May 1997 00:12:32   Bruce  $

$Log:   H:/pvcs/pvcsproj/gomand3d.prj/WRAPPER.CPV  $
*
*   Rev 1.96   16 May 1997 00:12:32   Bruce
*changed BYForceUpdate so that it works
*when NOT full screen rather than when
*it IS full screen.  Then, since it didn't
*seem to do anything, I commented out
*the call to BYForceUpdate.
*
*   Rev 1.95   15 May 1997 17:52:38   Jeremiah
*Set detail level for autodemo to be highest
*on accelerator cards.
*
*Disabled lowest, low, and medium detail
*levels for hardware accelerator cards.
*
*   Rev 1.94   13 May 1997 17:15:06   Jeremiah
*Fixed conditions for stretch blit option 
*to exclude 640x480x8 mode.
*
*   Rev 1.93   13 May 1997 11:26:54   Jeremiah
*Ensured stretch is only available in 
*640x480x16 mode (not 640x480x8).
*
*   Rev 1.92   May 07 1997 16:55:44   JEREMIAH
*Separated stretch flags into separate 
*structure.  Added bWillStretch.  Allowed
*stretch to be selectable from window size
*menu.
*
*   Rev 1.91   28 Apr 1997 12:05:18   JEREMIAH
*Merge of 1.89.1.1 and 1.90.
*
*   Rev 1.89.1.1   28 Apr 1997 11:47:18   JEREMIAH
*Extended time for display final screen
*in demo versions so user can read ad.
*
*   Rev 1.89.1.0   23 Apr 1997 14:47:42   JEREMIAH
*Fixed freeware version.  
*
*   Rev 1.90   28 Apr 1997 10:15:42   TIM
*Made mods for s3 stretch
*
*   Rev 1.89   08 Apr 1997 10:52:08   JEREMIAH
*If textured backgrounds are to be used,
*don't load backgrounds into overlay.
*
*   Rev 1.88   02 Apr 1997 13:05:30   BRUCE
*Released D3D object as well as the buffers
*for the frame rate and info, to get rid of 
*memory fragmentation.
*
*removed the autodemo bug that caused 
*the Robot to explode on entry, by resetting
*Robotlose and monsterlose when going
*to the wrapper.
*
*   Rev 1.87   28 Mar 1997 14:44:06   JEREMIAH
*Moved the background function to clutter.c
*
*
*   Rev 1.86   24 Mar 1997 09:55:58   JEREMIAH
*Removed mmx from the conditions
*allowing 640x480x16 mode.
*Patch until mmx works.
*
*   Rev 1.85   Mar 20 1997 17:12:24   JEREMIAH
*Moved horizon further out.
*
*   Rev 1.84   20 Mar 1997 11:21:34   BO
*1. patch a "hole" in trainer menu display,
*    though that bug is mysterily fixed.
*2. loop autodemo for debug version, but play
*    only one round for release version.
*
*   Rev 1.83   18 Mar 1997 10:00:04   JEREMIAH
*Added diagnostic bydumps to the mode
*finding function.
*
*   Rev 1.82   17 Mar 1997 15:33:32   JEREMIAH
*Load new bitmap (wr139) for in joystick config
*screen if no joystick attached.
*
*   Rev 1.81   17 Mar 1997 15:16:32   JEREMIAH
*Added separate joystick types for 
*Creative gamepad and Gravis Grip.
*
*   Rev 1.80   17 Mar 1997 11:01:50   BRUCE
*The time from the trainer level no longer
*carries over into the next level.
*
*   Rev 1.79   14 Mar 1997 14:25:34   JEREMIAH
*Changed by Bo.
*- fixed the exit bug in training mission
*- modified code to only play one round autodemo
*
*
*   Rev 1.78   14 Mar 1997 13:58:56   JEREMIAH
*Fixed default detail settings.
*
*   Rev 1.77   12 Mar 1997 14:38:14   JEREMIAH
*Temporarily set default detail level to
*3 for all configurations.
*
*   Rev 1.76   12 Mar 1997 14:24:38   JEREMIAH
*modified modules to play credit and ending avis according to the 
*new game flow.
*
*   Rev 1.75   12 Mar 1997 12:35:34   JEREMIAH
*Set default detail level to 4 if in a 16-bit
*mode.  When MMX is properly checked
*for, the default detail level will be 4 if
*d3d hw acceleration is used, 3 if no hw
*acceleration.
*
*   Rev 1.74   11 Mar 1997 19:30:00   BRUCE
*fixed possible bug in ChooseLoadUser menu,
*added a message box telling the user that 
*his cd wasn't detected, and asking him to
*please try again.
*
*   Rev 1.73   07 Mar 1997 13:50:58   JEREMIAH
*Added diagnostic function to display 
*AE variables.
*
*   Rev 1.72   03 Mar 1997 21:46:02   BRUCE
*Smoothed out life and power bar 
*movement, and tied them in with frame
*rate.
*
*   Rev 1.71   03 Mar 1997 18:30:56   BRUCE
*put in a check to see if the midis' path
*has been set to NULL.  If so, midis aren't
*played.
*
*   Rev 1.70   03 Mar 1997 17:52:56   BRUCE
*made radar in relation to goodguyframe,
*so when playing as monster, radar is
*correct.
*
*
*   Rev 1.69   28 Feb 1997 13:56:28   BO
*modified radar display function to let user 
*use "="/"+" to toggle and control radar scale
*
*   Rev 1.68   28 Feb 1997 10:58:50   BO
*fixed a bug which happens when you ESC
*from game in 320 mode to the Robot screen
*
*   Rev 1.67   27 Feb 1997 16:50:52   BO
*modified joystick configuration module to
*give user a way to block our action definitions
*for MS game pad and joystick. 
*
*   Rev 1.66   27 Feb 1997 09:26:04   BO
*1. added code to stop movie play
*2. added code to stop ending screen display
*3. modified video mode filtering module
*
*
*   Rev 1.65   25 Feb 1997 17:37:24   BRUCE
*morged versions 1.64 and 1.63.1.0
*
*   Rev 1.63.1.0   25 Feb 1997 17:16:02   BRUCE
*replaced OverallScore with
*GameStates.Score
*Put time totals into GameStates.
*
*
*   Rev 1.64   25 Feb 1997 15:20:12   BO
*modified code to display different bmps for
*different input devices correctly.
*
*   Rev 1.63   25 Feb 1997 11:27:12   BO
*1. added page control flag for final thank you page
*2. added page, timer handler of that page
*3. modified timer handler of final win for middle
*    win only
*4. reactivate snd effect for Robot selection and
*    added code to shut off snd play before going
*    to the game
*5. added code to display different bmps for 
*    different input devices in option menu
*6. removed bmps and replaced with 3 avis for
*    final win, middle win and lose game
*7. added keyboard handler for final win page
*8. modified MCI notification module for 3 new
*    avi play.
*9. modified 640 mode timer and population 
*    text positions
*10. added code to scale radar
*
*   Rev 1.62   21 Feb 1997 16:05:28   BRUCE
*moved honor into GameStates,
*made separate honors for each level.
*
*   Rev 1.61   21 Feb 1997 13:05:26   BRUCE
*when you win or lose the game and decide
*not to quit, we now reset all the gamestate
*variables.
*
*   Rev 1.60   20 Feb 1997 14:13:40   JEREMIAH
*Murged 1.59 and 1.58.1.0 - 1.58.5.0
*
*   Rev 1.59   20 Feb 1997 13:44:30   BRUCE
*Removed bug where Autodemo would 
*advance the submonster flag, and that 
*would affect gameplay.
*
*Removed the switch to NetShowScore
*
*reset RobotLose variable after Robot's
*done losing.
*
*   Rev 1.58.1.0   18 Feb 1997 15:53:54   JEREMIAH
*Disabled netplay.
*
*   Rev 1.58.2.0   18 Feb 1997 17:05:30   JEREMIAH
*Removed "white flash" bug and "line
*of pixels" bug from scrolling background
*code.
*
*   Rev 1.58.3.0   19 Feb 1997 11:57:14   JEREMIAH
*Fixed GameStates initialization for
*freeware versions.
*
*   Rev 1.58.4.0   19 Feb 1997 15:39:50   JEREMIAH
*Fixed GameStates initialization for
*freeware versions.
*
*   Rev 1.58.5.0   20 Feb 1997 13:33:28   JEREMIAH
*Improved motion of power/life bars.
*
*   Rev 1.58   14 Feb 1997 23:57:30   BRUCE
*morged versions 1.54.1.0 and 1.57
*
*   Rev 1.54.1.0   14 Feb 1997 22:59:14   BRUCE
*moved definition of LevelSoFar to here
*replaced AutoDemoFlag with GameStates.IsAutodemo
*replaced netPlay with GameStates.IsNetplay
*replaced PlayMode with GameStates.IsTraining
*replaced submonster with GameStates.CurrentSubmonster
*replaced OldLevel and level with GameStates.CurrentLevel
*created enum BmpIndex, and changed
*many BmpFile[?] to take enum values
*rather than integers.
*
*   Rev 1.57   14 Feb 1997 16:37:14   JEREMIAH
*Changed by Bo.
*- include ybjoystk.h
*- added calls to clean up background before intro, credit and 
*ending movies play.
*- changed BYChangeJoystkActions function to assign actions 
*specifically defined for MS digital joystick and game pad.
*
*
*   Rev 1.56   14 Feb 1997 15:37:32   JEREMIAH
*Added text display function for pg_NET_WAIT_FOR_JOIN.
*
*Improved menu flow for selecting sessions.
*
*   Rev 1.55   14 Feb 1997 11:42:34   JEREMIAH
*Added new pages NET_WAIT_FOR_JOIN,
*NET_WAIT_FOR_OPPONENT, NET_SHOW_SCORE,
*NET_OPPONENT_LEFT, and NET_ERROR.
*
*Activated NET_WAIT_FOR_JOIN,
*NET_WAIT_FOR_OPPONENT, and
*NET_SHOW_SCORE with placeholder
*graphics and no text.
*
*   Rev 1.54   10 Feb 1997 12:26:22   JEREMIAH
*Changed by Bo.
*- added display control flags for intro movie
*- defined page and keyboard handler for intro movie
*- modified Goman title screen keyboard handler so that when press 
*anykey, it will turn off autodemo mode and play the intro movie.
*- modified Goman timer event handler so that when the timer reach 
*to about 30 seconds, it turns on the autodemo mode
*- added intro movie page and keyboard handlers
*- modified and added code to play win/lose midi for game exit (not 
*for each level)
*- modified function BYDecide2DAfterGame so that it jumps to play 
*intro movie if the autodemo mode is stoped by a user's input
*- modified functions to play credit and ending movie so that these 
*movies be played in full screen mode.
*- modified ShowNewThankyou function to reset some important 
*variables, and then jump to final exit screen, i.e., ask if want to exit.
*- modified MCI event handler for intro movie so that it will close 
*the avi and create ms device correctly and then jump to the main menu.
*- added code to stop midi play before playing credit movie.
*- modified AviLevel's default value
*- modified page pg_READY_TO_GO's page handler's definition - modified page pg_READY_TO_GO's time handler's definition - added more security to TimeGomanTitle function
*- save and restore level value in training mode
*
*
*   Rev 1.53   Feb 07 1997 12:20:26   JEREMIAH
*Added 512x384x16 autodemo.
*
*   Rev 1.52   06 Feb 1997 16:11:32   JEREMIAH
*Fixed game flow problem when entering
*and exiting the trainer level.
*
*   Rev 1.51   06 Feb 1997 08:31:32   BRUCE
*took control of whichRobot
*
*   Rev 1.50   05 Feb 1997 18:47:42   BRUCE
*morged version 1.49 and 1.48.1.0
*
*   Rev 1.49   05 Feb 1997 18:26:26   BRUCE
*got rid of boring warnings.
*
*   Rev 1.48.1.0   05 Feb 1997 18:25:08   JEREMIAH
*Changed by Bo.
*Updated mouse/joystick reconfig pages
*and changed some midi stuff.
*
*   Rev 1.48   05 Feb 1997 16:39:30   JEREMIAH
*Added DumpMemoryStatus calls. 
*
*   Rev 1.47   04 Feb 1997 16:17:48   JEREMIAH
*Added calls to DumpMemoryStatus().
*
*   Rev 1.46   Feb 02 1997 00:42:18   BRUCE
*In ongoing war with bo, changed thanku.bmp
*back to wr133.bmp
*
*   Rev 1.45   31 Jan 1997 17:03:58   JEREMIAH
*Release ZBuffer.
*
*   Rev 1.44   31 Jan 1997 15:44:00   BRUCE
*call to BYOBGetBitmapPath rather than
*doing string manipulation of the BMPPath
*variable
*
*   Rev 1.43   31 Jan 1997 13:58:10   JEREMIAH
*Changed by Bo.
*Added 3 video mode options to compile
*freeware version.
*
*   Rev 1.42   31 Jan 1997 10:17:54   JEREMIAH
*Added memory status printouts.
*
*   Rev 1.41   30 Jan 1997 15:57:16   JEREMIAH
*Changed "thanku.bmp" to "wr133.bmp"
*in last question page.
*
*   Rev 1.40   29 Jan 1997 18:51:54   JEREMIAH
*Fixed bug that prevented autodemo and
*training level from running.
*
*   Rev 1.39   29 Jan 1997 15:35:54   BRUCE
*merged 1.38 and 1.37.1.0
*
*   Rev 1.37.1.0   29 Jan 1997 15:17:14   BRUCE
*added call to get the cd drive letter, and
*inside #ifdef CDRequired, returned if the
*cd wasn't there.
*
*   Rev 1.38   29 Jan 1997 14:38:30   JEREMIAH
*Changed by Bo.
*Added 1-level freeware demo when 
*compiled with FREEWARE defined.
*
*   Rev 1.37   28 Jan 1997 16:38:40   JEREMIAH
*Fixed incorrect naming conventions for
*l?map.bmp.
*
*   Rev 1.36   28 Jan 1997 15:24:12   JEREMIAH
*Examine video card to determine default
*video mode.
*
*   Rev 1.35   28 Jan 1997 12:34:54   JEREMIAH
*Updated filename of exit spash screen
*to wr133.bmp
*
*   Rev 1.34   28 Jan 1997 10:31:08   JEREMIAH
*Changed by Bo.
*add two variable declaration AviLevel, 
*and bAviTimer add more control flag 
*setttings for mission AVI play and last 
*question screen, add KillTimer in 
*KdGomanTitle, removed a bug in 
*NetConnection mouse selection code, 
*resume Snd calls for menu selection, add 
*Page handlers for mission AVI play and 
*last question screen.
*
*   Rev 1.33   27 Jan 1997 18:01:24   JEREMIAH
*Setup correct filenames for 512 mode
*backgrounds. 
*
*   Rev 1.32   27 Jan 1997 10:38:26   JEREMIAH
*Fixed autodemo logic.
*
*   Rev 1.31   23 Jan 1997 12:45:50   BRUCE
*put in ByDump for bad palette load.
*
*   Rev 1.30   23 Jan 1997 12:21:54   BRUCE
*added BYDump for page loading.
*
*   Rev 1.29   22 Jan 1997 17:42:24   JEREMIAH
*Exit out of BYDumpInfo if in release version.
*
*   Rev 1.28   22 Jan 1997 14:32:34   JEREMIAH
*Fixed flow of wrapper when exiting a 
*netplay level.
*
*   Rev 1.27   17 Jan 1997 14:29:00   JEREMIAH
*Merge of 1.26.2.1.1.1 and 1.26.2.3
*
*   Rev 1.26.2.1.1.1   16 Jan 1997 09:47:12   TIM
*Made sure overlays were placed in system memory
*
*   Rev 1.26.2.1.1.0   15 Jan 1997 12:21:50   BO
*modified for new MIDI code
*
*   Rev 1.26.2.1   10 Jan 1997 16:13:58   BO
*added two functions for screen capture &
*added several relevant variables definitions
*
*   Rev 1.26.2.3   17 Jan 1997 12:06:42   JEREMIAH
*Added code to display session selection
*menu.
*
*Fixed monster selection menu.
*
*   Rev 1.26.2.2   14 Jan 1997 15:08:32   JEREMIAH
*Enabled netplay in its most rudimentary
*form.
*
*   Rev 1.26.2.1   10 Jan 1997 16:13:58   BO
*added two functions for screen capture &
*added several relevant variables definitions
*
*   Rev 1.26.2.0   10 Jan 1997 11:23:10   BO
*Added code to turn on/off cursor in several
*cases such as mission bmp display.
*
*Added code to recreate mouse device and
*load cursor bmp and setup paras for cursor
*display.
*
*Removed PostMessage statement in 
*KdModifyTopList function to remove a
*crash bug when we try to enter names in
*top list screen.  This bug was created by
*ITC team.
*
*   Rev 1.26.1.0   09 Jan 1997 15:01:32   BO
*modified all the mouse handlers so that 
*they use new function prototype, and mouse
*data directly obtained from DirectInput
*
*   Rev 1.26   08 Jan 1997 19:17:16   JEREMIAH
*Minor bug fixes for netplay selection.
*
*
*   Rev 1.25   08 Jan 1997 17:15:06   BO
*I thought I have fixed blt problem. please
*double check and confirm it.
*
*   Rev 1.24   08 Jan 1997 14:47:46   BO
*fixed mission string display in mission
*score screen
*
*   Rev 1.23   07 Jan 1997 17:27:28   BO
*further modified overlay draw function to
*fix blit bug
*
*   Rev 1.22   07 Jan 1997 15:42:20   BO
*modified blt while loop
*modified function for screen & resolution
*selection
*
*   Rev 1.21   07 Jan 1997 13:33:36   BO
*modified 3d background blt function so that 
*it covers both normal and abnormal cases.
*
*   Rev 1.19   Jan 06 1997 18:25:20   JEREMIAH
*Changed color of level 1's backgrounds
*to match palettized background files.
*
*   Rev 1.18   06 Jan 1997 13:46:38   JEREMIAH
*Turned off scrolling text to test palette
*pause. 
*
*   Rev 1.17   20 Dec 1996 17:24:40   JEREMIAH
*Changed filenames of textures to match
*new filename conventions for level-specific
*palettes.
*Changed defaults for missing command
*line parameters to start in 320 mode.
*
*   Rev 1.16   Dec 19 1996 10:59:00   JEREMIAH
*Fixed minor bugs and cleaned up code
*a bit in BYBlt3DBackground().
*
*   Rev 1.15   17 Dec 1996 17:17:26   JEREMIAH
*Fixed backgrounds for small window sizes.
*
*
*   Rev 1.14   16 Dec 1996 10:48:08   JEREMIAH
*Changed by ITC.  Added code for netplay.
*
*   Rev 1.13   03 Dec 1996 14:42:48   JEREMIAH
*Added capability for 512x384x16 resolution
*and optimized clears for full-screen
*backgrounds.
*
*   Rev 1.12   14 Nov 1996 15:55:02   BO
* 1. deleted some unused function calls
* 2. added code and tried to solve the flashing problem
*     happened in game exit
* 3. added code, made sure keyboard handler for 
*     next mission bmp display will only be called
*     after the bmp is displayed
* 4. moved timer handler for next mission up
* 5. turn on the frame meter 
*
*   Rev 1.11   13 Nov 1996 17:49:46   BO
* 
*
*   Rev 1.10   13 Nov 1996 16:00:32   BO
* Define and set a switch flag for the display of game user interface
*
*   Rev 1.9   13 Nov 1996 09:55:26   BO
** remove ybmouse.h and all old mouse function calls
** add CDirectInput di, + calls to create new
*DirectInput mouse device, delete mouse
*device and set mouse actions
*
*   Rev 1.8   07 Nov 1996 15:27:12   BO
*modified BYLineEditor and let a user to
*enter letters and numbers.
*
*   Rev 1.7   07 Nov 1996 15:01:16   BO
*Removed an extra YBunloadsound in
*function BYDecide2DAftergame
*
*   Rev 1.6   07 Nov 1996 12:32:04   JEREMIAH
*Changed default video mode from 
*640x480x8 to 640x480x16.
*
*   Rev 1.5   Nov 05 1996 15:08:18   JEREMIAH
*Fixed incorrect case for bits per pixel.
*
*   Rev 1.4   Nov 05 1996 09:58:08   JEREMIAH
*Changed by Bo.  Many changes.
*/
#include <windows.h>
#include <windowsx.h>
#include <winver.h>
#include <mmsystem.h>
//#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "rl2d3d.h"

#include "d3dappi.h"
#include "rmdemo.h"
#include "rmfull.h"
#include "byglobal.h"
#include "wrapper.h"
#include "ybreg.h"
#include "ybmm.h"
#include "d3code.h"
#include "ybmid.h"
#include "ybsnd.h"
#include "fly.h"
#include "tkinput.h"
#include "mstream.h"

//Add by Eric 11/12/96
extern "C" 
{
	#include "netplay.h"
}
//end of Eric
#include "netmenu.h"
#include "netinit2.h"


extern "C"
{
#include "keycom.h"
#include "timing.h"
#include "gosys.h"
#include "camera.h"
#include "monanim.h"
}

#include "global.h"
#include "byglobal.h"
#include "camera.h"
#include "rl2d3d.h"

#include "rmfull.h"
#include "wrapdata.h"
#include "ybjoystk.h"

#define WIN32_LEAN_AND_MEAN

extern "C" TARGET targets[];
extern "C" Caminfo* camerastuff;
extern "C" RLFrame badguyframe;
extern "C" RLFrame goodguyframe;

extern CDirectInput di;

extern BOOL bBYRenderingIsOK;
extern char GameVersion [5];
extern void ReportD3DAppError(void);
extern void CleanUpAndPostQuit(void);
extern BOOL Render3DWorld(void);
extern D3DAppInfo* d3dapp;        
extern rmfullglobals myglobs; 

int vmode;	// new 12/10 by Bo
int VSize;
int LevelSoFar;
int Page = pg_START;
int OldPage = pg_START;
BOOL bInWrapper = TRUE;
BOOL bUseDebug = FALSE;
BOOL bCall3DOnce = TRUE;
BOOL bCall2DOnce = TRUE;
BOOL bScaleRadar = FALSE;
HCURSOR mycursor;
BOOL bShowGameUI=FALSE;
int AviLevel = -1;
BOOL bAviTimer = FALSE;

int  VRAM_Range = 1;
extern "C" int forcedtransparency;

#define PG_BACK -99

LPDIRECTDRAWSURFACE     lpDDSOverlay[3];  
LPDIRECTDRAWSURFACE     lpDDSText;
  
MsgHandler BYPageHandler[TOTALPAGE];
MsgHandler BYTimeHandler[TOTALPAGE];
MsgHandler BYKbrdHandler[TOTALPAGE];
MsgHandler BYMiceHandler[TOTALPAGE];
MsHandler  BYMouseHandler[TOTALPAGE];
TxtHandler BYDisplayText=BYDisplayStr;

GameUIDisplay BYDisplayMeter;
//GameUIDisplay BYDisplayRadar;
GameUIDisplay BYDisplayTimer;
GameUIDisplay BYDisplaySubTitle;
GameUIDisplay BYDisplayAimQuit;

CleanUpCall BYCleanUp;

void YBDefDisplayUI(BOOL show);
RECT AviSize = {30, 106, 320, 240};

// 1st idx ... video mode,  2nd idx ... 3d window size
// ---------------------------------------------------
// 0       ... 320x240      0       ... smallest size
// 1       ... 640x480      1       ... middle size
//                          2       ... letter box size
// 2       ... 512x384
RECT GWinSize[3][3] =
{
	// for 640x480 mode
   160,120,480,360,  
	98,106,537,373,
	0,100,639,380,
	// for 320x240 mode
   76,56,242,186,
	46,56,270,186,
	0,56,319,186,
	// for 512x384 mode
	130,116,383,267,
	75,84,430,301,
	0,84,511,301
};

#define MID_PLAY 601
#define MID_STOP 602
#define MID_SILENT 603

short  MidCmd = MID_STOP;
short  MidSts = MID_STOP;
short  MidNewIdx = 99;
short  MidOldIdx = 99;

int  S1Idx=0;
int  S2Idx=0;
int  S3Idx=0;
int  *S1xy, *S2xy, *S3xy, *S4xy, *S5xy;
RECT *S1rect, *S2rect, *S3rect, *S4rect, *S5rect;
BOOL *S1ItemFlag, *S2ItemFlag, *S3ItemFlag, *S4ItemFlag, *S5ItemFlag;
short S1TotalItems, S1OldIdx, S1NewIdx;
short S2TotalItems, S2OldIdx, S2NewIdx;
short S3TotalItems, S3OldIdx, S3NewIdx;
short S4TotalItems, S4OldIdx, S4NewIdx;
short S5TotalItems, S5OldIdx, S5NewIdx;
short *S5face;
short msact;

DWORD MSDrawMode = DDBLTFAST_NOCOLORKEY;

DWORD S1DrawMode = DDBLTFAST_NOCOLORKEY;
DWORD S2DrawMode = DDBLTFAST_NOCOLORKEY;
DWORD S3DrawMode = DDBLTFAST_NOCOLORKEY;
DWORD S4DrawMode = DDBLTFAST_NOCOLORKEY;
DWORD S5DrawMode = DDBLTFAST_NOCOLORKEY;

int Rx0, Ry0, Rxy;
//short  TotalTargets=14;
//short  ScaleFactor=2;

HFONT hGameFont, hSystemFont;
HBRUSH hGameBrush[2], hSystemBrush;
HPEN  hGamePen[6], hSystemPen;

BOOL EditMode = FALSE;
int RMode;

short MvInBefore = 0;

#define LINE_BUFFER_SIZE 12

char YBLineBuffer[LINE_BUFFER_SIZE];
char *OldTextPtr;
static short ChrIdx=0;
static short StrIdx=0;
static short StrLen=0;
int  TotalString = 0;
char  *TextPtr[20];
short *TextPos[20];
COLORREF *TextCol;
int  StringFrame = 0;
extern "C" RLValue AutoCountdown;

int RobotMatchTable[6] = { MerRobot, SabreRobot, StealthRobot, KataRobot, KaberRobot, -1 };

#define TOTALVMODE     8 

int VideoModeSetting[TOTALVMODE][3] =
{
	640, 480, 16, 
	640, 400, 16, 
	640, 480, 8, 
	640, 400, 8, 
	320, 240, 8, 
	320, 200, 8,
	800, 600, 16,
	800, 600, 8
};
//Liou qinghua add 1996,10,28
//#define RobotNUM     5
//#define MONSTERNUM  7
extern BOOL bSelectRobot, bSelectMonster, bMonsterMenu;
extern BOOL bConnectFlag;
extern "C"
{
BOOL QHNetPlaySelect(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL SetDefaultVideoMode();
}

extern BOOL QHRenderNetPlayMenu(void);
extern BOOL QHRenderWaitConnectBefore3D();
extern BOOL JSCSwappedSelectionInfo();

void QHDrawOverLay(short OverlayNum, BOOL show);
int QHSelectCharMenuFromKBD(WORD wparam);
int QHMsChooseCharMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL ScreenCaptureFlag = FALSE;
//Liou qinghua end
#ifdef CAPBMP
	unsigned char ImageBuffer[307200];  // =640x480, need initialize to zero
	size_t ImgBufSize;
	BOOL ImageFlag = FALSE;
	unsigned char *ImagePtr=NULL;
#endif
//
// SYSTEM FUNCTIONS
//

	
	
BOOL BYSetUpSystemEnvironment
(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
   hPrevInstance;
   BOOL retval;

   int inputvalue;
   int i;
   CDDriveLetter=GetCDROMDriveLetter();
#ifdef CDRequired
   while(!CDDriveLetter)
   {
	   int returnValue;
	   returnValue = MessageBox(NULL,
		   "We did not detect your Goman cd.\nPlease insert your cd in your cd drive.",
		   "CD Missing!",
		   MB_RETRYCANCEL);
	   if(returnValue == IDCANCEL)
			return FALSE;
	   CDDriveLetter=GetCDROMDriveLetter();
   }
#endif
   
   
#ifdef _DEBUG
   DumpMemoryStatus("Before wrapper");
#endif

   retval = SetDefaultVideoMode();

	// LEVEL input
	GameStates.CurrentLevel = lpCmdLine[0]-'0';
   if (GameStates.CurrentLevel<Trainer || GameStates.CurrentLevel>Tokyo)
   {
      GameStates.CurrentLevel = Mojave;
   }
   for(i=Mojave;i<GameStates.CurrentLevel;++i)
   {
	   GameStates.IsMonsterDead[i][Alpha]=1;
	   GameStates.IsMonsterDead[i][Beta]=1;
	   GameStates.IsMonsterDead[i][Gamma]=1;
   }


	// MODE input
	inputvalue = lpCmdLine[1]-48;

#ifdef FREEWARE
	if (inputvalue==1 || inputvalue==3)
		VRAM_Range = 1;
	if (inputvalue==2 || inputvalue==4)
		VRAM_Range = 4;
	if (inputvalue==7)
		VRAM_Range = 2;
#endif

	switch(inputvalue)
	{
	case 1:
		VM_W3D = 320; 
		VM_H3D = 240; 
		VM_BPP3D = 8;  
		break;
	case 2:
		VM_W3D = 640;
		VM_H3D = 480; 
		//VM_W3D = 512;
		//VM_H3D = 384; 
		VM_BPP3D = 16; 	
		break;
	case 3:
		VM_W3D = 320; 
		VM_H3D = 240; 
		VM_BPP3D = 8; 
      GameStates.IsAutodemo = TRUE;		
		break;
	case 4:
		VM_W3D = 640;
		VM_H3D = 480; 
		VM_BPP3D = 16; 	
      GameStates.IsAutodemo = TRUE;		
		break;
	case 5:
		bUseDebug = TRUE;
		VM_W = VideoModeSetting[1][0];
		VM_H = VideoModeSetting[1][1];
		VM_BPP = VideoModeSetting[1][2];
		VM_FULLSCREEN = FALSE;
		break;
	case 6:
		bUseDebug = TRUE;
		VM_W = VideoModeSetting[1][0];
		VM_H = VideoModeSetting[1][1];
		VM_BPP = VideoModeSetting[1][2];
		VM_FULLSCREEN = FALSE;
      GameStates.IsAutodemo = TRUE;
		break;
	case 7:
		VM_W3D = 512; 
		VM_H3D = 384; 
		VM_BPP3D = 16;  
		break;
	case 8:
		VM_W3D = 512; 
		VM_H3D = 384; 
		VM_BPP3D = 16;  
      GameStates.IsAutodemo = TRUE;
		break;
	default:
      if (!retval)      // set defaults from d3d accelerator config
      {
		   VM_W3D = 320;        // if that failed, use 320x240x8
		   VM_H3D = 240; 
		   VM_BPP3D = 8; 	
      }
		break;
	} 

	if (!bUseDebug)
	{
		VM_W = 640;
		VM_H = 480;
		VM_BPP = VideoModeSetting[0][2];
		VM_FULLSCREEN = TRUE;
	}

	// 3D WINDOW SIZE input
	inputvalue = lpCmdLine[2]-48;
	switch(inputvalue)
	{
	case 1:
	case 2:
	case 3:
	case 4:
		VSize = inputvalue;
		break;
	default:
		VSize = 4;
		break;		
	};

	lpCmdLine[0] = 0;
	lpCmdLine[1] = 0;
   lpCmdLine[2] = 0;

   inputvalue = lpCmdLine[3]-48;
   if ( inputvalue<0 || inputvalue>5 ) 
   {
      if (hw3dacc == TRUE)
         detail = 4;
      else
         detail = 3;
   }
   else
   {
      detail = inputvalue;
   }

	// 5th para = playfrom HD/CD  1=CD, 2=HD
	inputvalue = lpCmdLine[4]-48;
	if ( inputvalue<0 || inputvalue>2 ) 
   {
      playfrom = 1;
   }
	else
   {
		playfrom = inputvalue;
   }

	forcedtransparency = lpCmdLine[5] - 48;
	//int auto1;
	//auto1  = lpCmdLine[2]-48;
	//if (auto1==0)
	//	AutoDemoFlag = TRUE;
   
	if (GameStates.IsNetplay)
	{
		inputvalue = lpCmdLine[5] - 48;
		if (inputvalue < 1 || inputvalue > 3)    //simualte mode
		{
			SimuMode = 0;
		}
		else
		{
			SimuMode = inputvalue;
		}
	}

	if (lpCmdLine[3]=='m' || lpCmdLine[3]=='M')
	{
		PlayAsMonster = 1;
	}
	else
	{
		PlayAsMonster = 0;
	}


	//net play will reset PlayAsMonster correctly.
	GameStates.IsNetplay       = FALSE;
	beSynchronous = FALSE;

	if (!BYTestRegisterOrNot(GameVersion))
		BYRegisterGame(GameVersion);

	    if (!YBGetAllPath(hInstance, VM_W3D))
		{
	        return FALSE;
		}
	total_mscfg=10;
	current_mscfg = tpmscfg = 0;
	BYChangeMouseActions();

	return TRUE;
}

BOOL BYSetupThings4Wrapper(void)
{
	BYSetBmpFiles();

	BYRender  = Render2DWorld;
	BYCleanUp = BYExitFromMainMenu;

	BYSetPageHandler();
	BYSetTimeHandler();
	BYSetKbrdHandler();
	BYSetMiceHandler();

	InitNetPlayMenu();			// 01.03
	InitSelectMonsterMenu();	// 01.03
	GetProvider();					// 01.03

	BYSetPostPageSwitch(Page); 

	BYTurnToNextNPage(Page, 1);
	PostMessage(BYMainHwnd, WM_COMMAND, Page, 0L);

//	OldLevel = GameStates.CurrentLevel;
	return TRUE;
}

BOOL BYCreate3Overlays(short mode, short size)
{
	DDSURFACEDESC       ddsd;
	IDirectDrawSurface *pdds;
	short  vwidth, vheight;

	if (lpDDSOverlay[0]!=NULL ||
	    lpDDSOverlay[1]!=NULL ||
	    lpDDSOverlay[2]!=NULL ) 
	{
        return FALSE;
	}

	switch(mode)
	{
	case 800:
		vwidth = 800;
		vheight = 600;
		break;
	case 640:
		vwidth = 640;
		vheight = 610;
		break;
	case 512:
		vwidth = 512;
		vheight = 384;
		break;
	case 320:
		vwidth = 320;
		vheight = 305;
		break;
	}

	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY;
	ddsd.dwWidth  = vwidth;
	ddsd.dwHeight = vheight;

	if (d3dappi.lpDD->CreateSurface(&ddsd, &pdds, NULL) != DD_OK)
        return FALSE;

	lpDDSOverlay[0] = pdds;

	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY;
	ddsd.dwWidth  = vwidth;
	ddsd.dwHeight = vheight;

    if (d3dappi.lpDD->CreateSurface(&ddsd, &pdds, NULL) != DD_OK)
        return FALSE;

	lpDDSOverlay[1] = pdds;

	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY;
	ddsd.dwWidth  = vwidth;
	ddsd.dwHeight = vheight;

	if (d3dappi.lpDD->CreateSurface(&ddsd, &pdds, NULL) != DD_OK)
        return FALSE;

	lpDDSOverlay[2] = pdds;
	return TRUE;
}

void BYClearOverlaySurface(short OverlayNum)
{
	IDirectDrawSurface *pdds;
	DDSURFACEDESC       ddsd;
	HDC                 hdc;
	HRESULT             hr;
	HPEN                hNewPen, hOldPen;
	HBRUSH              hNewBsh, hOldBsh;

	pdds = lpDDSOverlay[(OverlayNum-1)];

	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
	pdds->GetSurfaceDesc(&ddsd);

	if ((hr = pdds->GetDC(&hdc)) == DD_OK)
	{
		hNewPen = GetStockObject( NULL_PEN );
		hNewBsh = GetStockObject( BLACK_BRUSH );
		hOldPen = SelectObject(hdc, hNewPen);
		hOldBsh = SelectObject(hdc, hNewBsh);
		Rectangle(hdc, 0, 0, (ddsd.dwWidth+1), (ddsd.dwHeight+1));
		SelectObject(hdc, hOldPen);
		SelectObject(hdc, hOldBsh);
		pdds->ReleaseDC(hdc);
	}
}

IDirectDrawSurface * BYLoadOverlay(short OverlayNum, LPCSTR szBitmap)
{
	HBITMAP             hbm;
	BITMAP              bm;
	IDirectDrawSurface *pdds;
	char                fullname[127];
	char StupidIdiot[128];

	BYClearOverlaySurface(OverlayNum);
	pdds = lpDDSOverlay[(OverlayNum-1)];

	hbm = LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

	if (hbm == NULL) 
	{
		if (bInWrapper)
		{
			strcpy(fullname, WrapBmpPath);
		}
		else
		{
			strcpy(fullname, BmpPath);
		}
		strcat(fullname, "\\");
		strcat(fullname, szBitmap);
		
		hbm = (HBITMAP)LoadImage(NULL, fullname, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	}

	if (hbm == NULL) 
	{
		BYDumpInfo("****************************");
		sprintf(StupidIdiot,"Couldn't find file %s or",szBitmap);
		BYDumpInfo(StupidIdiot);
		BYDumpInfo(fullname);
		BYDumpInfo("****************************");
		return NULL;
   }
	GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap

	DDCopyBitmap(pdds, hbm, 0, 0, 0, 0);

	DeleteObject(hbm);

	return pdds;
}

HRESULT DDCopyBitmap(IDirectDrawSurface *pdds, HBITMAP hbm, int x, int y, int dx, int dy)
{
    HDC                 hdcImage;
    HDC                 hdc;
    BITMAP              bm;
    DDSURFACEDESC       ddsd;
    HRESULT             hr;

    if (hbm == NULL || pdds == NULL)
        return E_FAIL;

    //
    // make sure this surface is restored.
    //
    pdds->Restore();

    //
    //  select bitmap into a memoryDC so we can use it.
    //
    hdcImage = CreateCompatibleDC(NULL);
    SelectObject(hdcImage, hbm);

    //
    // get size of the bitmap
    //
    GetObject(hbm, sizeof(bm), &bm);    // get size of bitmap
    dx = dx == 0 ? bm.bmWidth  : dx;    // use the passed size, unless zero
    dy = dy == 0 ? bm.bmHeight : dy;

    //
    // get size of surface.
    //
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
    pdds->GetSurfaceDesc(&ddsd);

    if ((hr = pdds->GetDC(&hdc)) == DD_OK)
    {
        StretchBlt(hdc, 0, 0, dx, dy, hdcImage, x, y, dx, dy, SRCCOPY);
//        StretchBlt(hdc, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcImage, x, y, dx, dy, SRCCOPY);
        pdds->ReleaseDC(hdc);
    }

    DeleteDC(hdcImage);

    return hr;
}

void BYClearBackSurface(void)
{
	IDirectDrawSurface *pdds;
	DDSURFACEDESC       ddsd;
	HDC                 hdc;
	HRESULT             hr;
	HPEN                hNewPen, hOldPen;
	HBRUSH              hNewBsh, hOldBsh;

	pdds = d3dappi.lpBackBuffer;

	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
	pdds->GetSurfaceDesc(&ddsd);

	if ((hr = pdds->GetDC(&hdc)) == DD_OK)
	{
		hNewPen = GetStockObject( NULL_PEN );
		hNewBsh = GetStockObject( BLACK_BRUSH );
		hOldPen = SelectObject(hdc, hNewPen);
		hOldBsh = SelectObject(hdc, hNewBsh);
		Rectangle(hdc, 0, 0, (ddsd.dwWidth+1), (ddsd.dwHeight+1));
		SelectObject(hdc, hOldPen);
		SelectObject(hdc, hOldBsh);
		pdds->ReleaseDC(hdc);
	}
}

BOOL Render2DWorld(void)
{
	if (!BYRestore2DSurfaces())
	{
		return FALSE;
	}
	
	/*
   BYDrawOverLay(1, DDmode1);
	BYDrawOverLay(2, DDmode2);
	BYDrawOverLay(3, DDmode3);
   */

	//Tim Stretch: added triple buffer overlay function for stretch rendering
	if(!bMonsterMenu) 
	{
		if (sStretch.bStretch)
		{

			OverlayToTriBuff(1, DDmode1);
			OverlayToTriBuff(2, DDmode2);
			OverlayToTriBuff(3, DDmode3);


		}
		else
		{
			BYDrawOverLay(1, DDmode1);
			BYDrawOverLay(2, DDmode2);
			BYDrawOverLay(3, DDmode3);
		}
	}
	else
	{
		QHDrawOverLay(1, DDmode1);
		QHDrawOverLay(2, DDmode2);
		QHDrawOverLay(3, DDmode3);
	}

	BYDisplayText(DDtext, EditMode);
#ifndef FREEWARE
	di.DrawMsCursor(bInWrapper);
#endif
	BYSurfaceBlt(DDmode0);  

	return TRUE;
}


/*
/////Liou qinghua render 1996,11,12
BOOL Render2DWorld(void)
{
	if (!BYRestore2DSurfaces())
	{
		return FALSE;
	}
	if(!bMonsterMenu) //Liou qinghua add the condition 1996,11.21
	{
		BYDrawOverLay(1, DDmode1);
		BYDrawOverLay(2, DDmode2);
		BYDrawOverLay(3, DDmode3);
	}
	else
	{
		QHDrawOverLay(1, DDmode1);
		QHDrawOverLay(2, DDmode2);
		QHDrawOverLay(3, DDmode3);
	}
	
	if(DDmode1) //Liou qinghua add 96,11,12
	{
		QHRenderNetPlayMenu();
	}
	BYDisplayText(DDtext, EditMode);
	BYSurfaceBlt(DDmode0);  

	return TRUE;
}
*/
/////////Liou qinghua end///////////////


BOOL RenderNothing(void)
{
	return TRUE;
}

// return TRUE when we need to wait
BOOL HandleException(HRESULT value)
{
	BOOL retval=FALSE;
	int i=0;

	switch(value)
	{
	case DDERR_EXCEPTION:
		i = 1;
		break;
	case DDERR_GENERIC:
		i = 2;
		break;
	case DDERR_INVALIDOBJECT:
		i = 3;
		break;
	case DDERR_INVALIDPARAMS:
		i = 4;
		break;
	case DDERR_INVALIDRECT:
		i = 5;
		break;
	case DDERR_NOBLTHW:
		i = 6;
		break;
	case DDERR_SURFACEBUSY:
		i = 7;
		break;
	case DDERR_SURFACELOST:
		i = 8;
		break;
	case DDERR_UNSUPPORTED:
		i = 9;
		break;
	default:
		i = 10;
		break;
	}
	return retval;
}

void BYDrawOverLay(short OverlayNum, BOOL show)
{
	int i, j;
	HRESULT ddrval;
	IDirectDrawSurface *pdds;

	if (!show) return;

	j = 0;
	pdds = lpDDSOverlay[(OverlayNum-1)];
	
	if (OverlayNum==1) 
	{
		while(1)
		{
			ddrval = d3dappi.lpBackBuffer->BltFast(S1xy[S1Idx*2], S1xy[S1Idx*2+1], 
					   pdds, &S1rect[S1Idx], S1DrawMode);
			if (ddrval==DD_OK) 
				break;
			else
			{
				if (HandleException(ddrval))
				{
					if (j>10) break;
					j++;
				}
			}
		} 
	} else 
	if (OverlayNum==2) 
	{
		for (i=0; i<S2TotalItems; i++) 
		{
			if (S2ItemFlag[i]) 
			{
				while (1)
				{
					ddrval = d3dappi.lpBackBuffer->BltFast(S2xy[i*2], S2xy[i*2+1], 
								pdds, &S2rect[i], S2DrawMode);
					if (ddrval==DD_OK) 
						break;
					else
					{
						if (HandleException(ddrval))
						{
							if (j>10) break;
							j++;
						}
					}
				} 
			}
		}
	} else
	if (OverlayNum==3) 
	{
		for (i=0; i<S3TotalItems; i++) 
		{
			if (S3ItemFlag[i]) 
			{
				while(1)//for (j=0; j<10; j++) // 5 chances to blit
				{
					ddrval = d3dappi.lpBackBuffer->BltFast(S3xy[i*2], S3xy[i*2+1], 
								pdds, &S3rect[i], S3DrawMode);
					if (ddrval==DD_OK) 
						break;
					else
					{
						if (HandleException(ddrval))
						{
							if (j>10) break;
							j++;
						}
					}
				} 
			}
		}
	}

}

//Tim Stretch: added triple buffer overlay function for stretch rendering

void OverlayToTriBuff(short OverlayNum, BOOL show)
{
	int i, j;
	HRESULT ddrval;
	IDirectDrawSurface *pdds;

	S1rect = &(Map320x240.src);

	if (!show) return;

	j = 0;
	pdds = lpDDSOverlay[(OverlayNum-1)];
	
	if (OverlayNum==1) 
	{
		while(1)
		{
			ddrval = d3dappi.lpBackBuffer2->BltFast(S1xy[S1Idx*2], S1xy[S1Idx*2+1], 
					   pdds, &S1rect[S1Idx], S1DrawMode);
			if (ddrval==DD_OK) 
				break;
			else
			{
				if (HandleException(ddrval))
				{
					if (j>10) break;
					j++;
				}
			}
		} 
	} else 
	if (OverlayNum==2) 
	{
		for (i=0; i<S2TotalItems; i++) 
		{
			if (S2ItemFlag[i]) 
			{
				while (1)
				{
					ddrval = d3dappi.lpBackBuffer2->BltFast(S2xy[i*2], S2xy[i*2+1], 
								pdds, &S2rect[i], S2DrawMode);
					if (ddrval==DD_OK) 
						break;
					else
					{
						if (HandleException(ddrval))
						{
							if (j>10) break;
							j++;
						}
					}
				} 
			}
		}
	} else
	if (OverlayNum==3) 
	{
		for (i=0; i<S3TotalItems; i++) 
		{
			if (S3ItemFlag[i]) 
			{
				while(1)//for (j=0; j<10; j++) // 5 chances to blit
				{
					ddrval = d3dappi.lpBackBuffer2->BltFast(S3xy[i*2], S3xy[i*2+1], 
								pdds, &S3rect[i], S3DrawMode);
					if (ddrval==DD_OK) 
						break;
					else
					{
						if (HandleException(ddrval))
						{
							if (j>10) break;
							j++;
						}
					}
				} 
			}
		}
	}

}

//  ---------------------------------------------
//  BLIT BACKSURFACE TO PRIMARY SURFACE
//
//  YBSurfaceBlt blits fast bitmap from backsurface to primary surface.
//  The backsurface is always be the same size as the primary surface.
//  For the difference between 640x480 and 640x400 video mode, it 
//  depends on the DrawOverlayX to figure out drawing on the backsurface
//  correctly at the right position with the right size.
void BYSurfaceBlt(BOOL show)
{
	HRESULT ddrval;
	RECT    front, back, rcSource, rcDest;
	//DDBLTFX bltfx;
	//RECT    r;

	//Tim Stretch: set the coordinates of the back and front buffers

	rcSource.left = 0;
	rcSource.top = 0;
	rcSource.right  = 319;   //640;
	rcSource.bottom = 239;  //480;

	rcDest.left = 0;
	rcDest.top = 0;
	rcDest.right = 639;
	rcDest.bottom = 479;


	if (!show) return;

	if (VM_FULLSCREEN==FALSE) {
        SetRect(&back, 0, 0, d3dappi.szClient.cx, d3dappi.szClient.cy);
        SetRect(&front,
                d3dappi.pClientOnPrimary.x, d3dappi.pClientOnPrimary.y,
                d3dappi.szClient.cx + d3dappi.pClientOnPrimary.x,
                d3dappi.szClient.cy + d3dappi.pClientOnPrimary.y);

		d3dappi.lpFrontBuffer->Blt(&front, d3dappi.lpBackBuffer,
                                   &back, DDBLT_WAIT, NULL);
	} 
	else
    {
		//Tim Stretch: added stretch rendering to the front buffer

		if (sStretch.bStretch)
			ddrval= d3dapp->lpBackBuffer2->UpdateOverlay(&rcSource, d3dapp->lpFrontBuffer, &rcDest, DDOVER_SHOW, 0);
		else
		{

			do {
        		ddrval = d3dappi.lpFrontBuffer->BltFast(0, 0,
        			d3dappi.lpBackBuffer, NULL, DDBLTFAST_NOCOLORKEY);
			} while (ddrval == DDERR_WASSTILLDRAWING);
		}

    } 
}

void BYReleaseAllOverlays(void)
{
	RELEASE(lpDDSOverlay[0]);
	RELEASE(lpDDSOverlay[1]);
	RELEASE(lpDDSOverlay[2]);
}

int BYGetRealMode(int *vmode_w, int *vmode_h, int *vmode_bpp)
{
	int i; 
	int ModeIdx=-1;
   char tmp[80];

   sprintf(tmp, "Looking for %dx%dx%d", *vmode_w, *vmode_h, *vmode_bpp);
   BYDumpInfo(tmp);
	for (i = 0; i < d3dappi.NumModes; i++) 
	{
      sprintf(tmp, "Checking %dx%dx%d", 
         d3dappi.Mode[i].w, d3dappi.Mode[i].h, d3dappi.Mode[i].bpp);
      BYDumpInfo(tmp);
		if (d3dappi.Mode[i].w == *vmode_w && 
			d3dappi.Mode[i].h == *vmode_h &&
			d3dappi.Mode[i].bpp == *vmode_bpp)
		{
			BYDumpInfo("Got it");
         ModeIdx = i;
			break;
		}
	}
	if (i>=d3dappi.NumModes && *vmode_bpp==16)
	{
		for (i = 0; i < d3dappi.NumModes; i++) 
		{
         sprintf(tmp, "Checking %dx%dx%d", 
            d3dappi.Mode[i].w, d3dappi.Mode[i].h, d3dappi.Mode[i].bpp);
         BYDumpInfo(tmp);
			if (d3dappi.Mode[i].w == *vmode_w && 
				d3dappi.Mode[i].h == *vmode_h &&
				d3dappi.Mode[i].bpp == 8)
			{
				*vmode_bpp = 8;
			   BYDumpInfo("Got it");
				ModeIdx = i;
				break;
			}
		}
	}

	return ModeIdx;
}


BOOL BYChooseTextSurface(short TextSurface)
{
	BOOL retval = TRUE;

	switch(TextSurface) {
	case 0:
		lpDDSText = d3dappi.lpBackBuffer;
		break;
	case 1:
		lpDDSText = lpDDSOverlay[0];
		break;
	case 2:
		lpDDSText = lpDDSOverlay[1];
		break;
	case 3:
		lpDDSText = lpDDSOverlay[2];
		break;
	default:
		retval = FALSE;
		break;
	};
	return retval;
}  

HFONT BYSelectFont (HDC hdc, char *FontName, short w, short h)
{         
   DWORD dwAspectMatch = 1L;    //0L;
   LOGFONT lf;

   lf.lfHeight         = h; //12;    //18;
   lf.lfWidth          = w;     // 7; 
   lf.lfEscapement     = 0;
   lf.lfOrientation    = 0;   
   lf.lfWeight         = FW_BOLD; //700;
   lf.lfItalic         = 0;
   lf.lfUnderline      = 0;
   lf.lfStrikeOut      = 0; 
   lf.lfCharSet        = ANSI_CHARSET;
   lf.lfOutPrecision   = OUT_DEFAULT_PRECIS;
   lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;      
   lf.lfQuality        = DEFAULT_QUALITY;
   lf.lfPitchAndFamily = VARIABLE_PITCH|FF_ROMAN;  //0xF0;
   lstrcpy(lf.lfFaceName, FontName);

   return (CreateFontIndirect(&lf));
   
} 

void BYDisplayStr(BOOL show, short ifsave)
{
	char fps[100];
	HDC  hDC;
	int  i;
	IDirectDrawSurface *pdds;
	HFONT hOldFont, hNewFont;

	if (show) 
	{
		pdds = lpDDSText;

		if (pdds->GetDC(&hDC)==DD_OK) 
		{
			SetBkColor(hDC, RGB(0, 0, 0));
			SetBkMode(hDC, TRANSPARENT);
			for (i=0; i<TotalString; i++) 
			{
				if (TextPos[i][3]==0) 
				{
					hNewFont = GetStockObject(ANSI_FIXED_FONT);
					hOldFont = SelectObject(hDC, hNewFont);
				} 
				else 
				{
					hNewFont = BYSelectFont(hDC, "System", 0, TextPos[i][3]);
					hOldFont = SelectObject(hDC, hNewFont);
				}
				SetTextColor(hDC, TextCol[i]);
				SetTextAlign(hDC, TextPos[i][2]); 
				sprintf(fps, TextPtr[i]);
				TextOut(hDC, TextPos[i][0], TextPos[i][1], fps, lstrlen(fps));
				if (TextPos[i][3]==0) 
				{
					SelectObject(hDC, hOldFont);
				} 
				else 
				{
					SelectObject(hDC, hOldFont);
					DeleteObject(hNewFont);
				}
         }
			SetTextColor(hDC, RGB(0, 255, 0));
         if (ifsave) 
			{
				hNewFont = GetStockObject(ANSI_FIXED_FONT);
				hOldFont = SelectObject(hDC, hNewFont);

				sprintf(fps, "-");
				TextOut(hDC, (TextPos[StrIdx][0]+ChrIdx*8),
							  (TextPos[StrIdx][1]+8), fps, lstrlen(fps));
				SelectObject(hDC, hOldFont);
         }

			SetBkColor(hDC, RGB(100, 100, 100));
			SetBkMode(hDC, OPAQUE);
			pdds->ReleaseDC(hDC);
		}
	}
}

//
// SYSTEM FUNCTIONS: ENDING
//

int BYSelectARobot(void)
{
    int i;
    unsigned int seed;

//    PlayMode = SYS_REAL_GAME;
	GameStates.IsTraining=FALSE;

    seed = (unsigned int)GetCurrentTime();
    srand(seed);
    for (;;) {
        i = (rand()%5);
        //j = RobotMatchTable[i];
        if (!GameStates.IsRobotDead[i])
            return i;
    }
}

//
//#define NUM_BMPS  46 //Rem by Eric

//Add by Eric 11/15/96
#define NUM_BMPS  58
//end of Eric 

enum BmpIndex
{
	MainBackground=0,
	MainForeground,
	OptionMenuBackground,
	OptionMenuForeground,
	CharacterMenuBackground,
	CharacterMenuSmallForeground=5,
	CharacterMenuBigForeground,
	MovieMenuBackground,
	MovieMenuForeground,
	LoadSaveMenuBackground,
	LoadSaveMenuForeground=10,
	GameUserInterfaceBackground,
	WinnerPopulationBackground,
	LoserPopulationBackground,
	AskQuit,
	KeyboardConfigurationBackground=15,
	SplashScreen,
	RobotDestroyed,
	SabreRobotDestroyed=17,
	StealthRobotDestroyed=18,
	MerRobotDestroyed=19,
	KataRobotDestroyed=20,
	KaberRobotDestroyed=21,
	LevelLaunch,
	MojaveLaunch=22,
	RockiesLaunch=23,
	HawaiiLaunch=24,
	SanFranciscoLaunch=25,
	NewYorkLaunch=26,
	TokyoLaunch=27,
	WorldSaved,
	TrainerVictory,
	LevelInfo,
	MojaveInfo=30,
	RockiesInfo=31,
	HawaiiInfo=32,
	SanFranciscoInfo=33,
	NewYorkInfo=34,
	TokyoInfo=35,
	NonExistentBitmap,
	YouBetterNotBeUsingThisBitmapOrHeadsAreGunnaRoll,
	MouseConfiguration,
	JoystickConfiguration,
	EmptyTotalVictory=40,
	HonorableTotalVictory,
	TrainerLaunch,
	HonorableVictory,
	EmptyVictory,
	ThankU=45,
	MonsterDead,
	RoggoshDead=46,
	KothosDead=47,
	TolgoDead=48,
	ShagtoqDead=49,
	NeallothDead=50,
	GaingrisDead=51,
	MonsterVictory,
	RoggoshVictory=52,
	KothosVictory=53,
	TolgoVictory=54,
	ShagtoqVictory=55,
	NeallothVictory=56,
	GaingrisVictory=57
};

char Bmp640[NUM_BMPS][10] =
{
    "WR101.BMP",  // 0 main menu background
    "WR102.BMP",  // 1 main menu foreground
    "WR103.BMP",  // 2 option menu background
    "WR104.BMP",  // 3 option menu foreground
    "WR105.BMP",  // 4 char menu background
    "WR106.BMP",  // 5 char menu small foreground
    "WR107.BMP",  // 6 char menu big foreground
    "WR108.BMP",  // 7 movie menu background
    "WR109.BMP",  // 8 movie menu foreground
    "WR110.BMP",  // 9 load/save menu background
    "WR111.BMP",  // 10 load/save menu foreground
    "WR112.BMP",  // 11 game user interface background
    "WR115.BMP",  // 12 winner population background
    "WR116.BMP",  // 13 loser population background   
    "WR120.BMP",  // 14 ask quit
    "WR121.BMP",  // 15 keyboard configuration background 
    "WR100.BMP",  // 16 splash = goman title  
    "SA000.BMP",  // 17 
    "ST000.BMP",  // 18
    "ME000.BMP",  // 19
    "KA000.BMP",  // 20
    "KB000.BMP",  // 21
    "LMMAP.BMP",  // 22
    "LRMAP.BMP",  // 23
    "LHMAP.BMP",  // 24
    "LSMAP.BMP",  // 25
    "LNMAP.BMP",  // 26
    "LTMAP.BMP",  // 27
    "WR125.BMP",  // 28, THE END
    "WR113.BMP",  // 29, ready to go
    "WR001.BMP",  // 30,
    "WR002.BMP",  // 31,
    "WR003.BMP",  // 32,
    "WR004.BMP",  // 33,
    "WR005.BMP",  // 34,
    "WR006.BMP",  // 35,
    "WR123.BMP",  // 36,
    "         ",  // ?
    "WR126.BMP",  // 38,
    "WR127.BMP",  // 39,
    "WR128.BMP",  // 40,
    "WR129.BMP",  // 41,
    "LVMAP.BMP",  // 42
	"WR130.BMP",  // 43, glory
	"WR131.BMP",  // 44, empty
	"WR132.BMP",  // 45, thank you
	//Add by Eric 11/15/96
	"WR661.BMP",  // 46-51 monster dead and to menu
	"WR662.BMP",
	"WR663.BMP",
	"WR664.BMP",
	"WR665.BMP",
	"WR666.BMP",
	"WR671.BMP",  // 52-57 monster defeat the me.
	"WR672.BMP",
	"WR673.BMP",
	"WR674.BMP",
	"WR675.BMP",
	"WR676.BMP"	  //57
	//end of Eric
};

char *BmpFile[NUM_BMPS];

void BYSetBmpFiles(void)
{
	int i;

	for (i=0; i<NUM_BMPS; i++)
		BmpFile[i] = (char *) &(Bmp640[i]);
}

// bBYPageSwitch's values must be in the same order as pages defined in #define pg_...
BOOL bBYPageSwitch[TOTALPAGE][4] =
{
//  primary, overlay1, overlay2, overlay3 surface turn-on switchers
//  It is very important to keep the following settings for
//  different screens in the same order as they are defined
//  in wrapper.h !!!
	TRUE, FALSE, FALSE, FALSE,  // start
	TRUE, TRUE, FALSE, FALSE,   // goman title
	TRUE, TRUE, TRUE, FALSE,    // main menu
	TRUE, TRUE, FALSE, FALSE,   // nextmission
	TRUE, TRUE, TRUE, TRUE,     // char menu
	TRUE, TRUE, TRUE, FALSE,    // movie menu 
	FALSE, FALSE, FALSE, FALSE, // aviplay_delay 
	TRUE, TRUE, TRUE, TRUE,     // train menu
	TRUE, TRUE, TRUE, FALSE,    // option menu
	TRUE, TRUE, FALSE, FALSE,   // mouse configuration
	TRUE, TRUE, FALSE, FALSE,   // joystick configuration
	TRUE, TRUE, TRUE, FALSE,    // load menu
	TRUE, TRUE, TRUE, FALSE,    // save menu
	TRUE, TRUE, FALSE, FALSE,   // kbd menu
	TRUE, FALSE, FALSE, FALSE,  // 3D example
	TRUE, FALSE, FALSE, FALSE,  // decide lose status
	TRUE, TRUE, FALSE, FALSE,   // lose one Robot
	TRUE, TRUE, FALSE, FALSE,   // lose all Robot
	FALSE, FALSE, FALSE, FALSE, // play avi
	TRUE, TRUE, FALSE, FALSE,   // avi bmp
	TRUE, FALSE, FALSE, FALSE,	 // decide M3 status
	TRUE, TRUE, FALSE, FALSE,   // M3 lose bmp
	FALSE, FALSE, FALSE, FALSE, // back to main
	TRUE, FALSE, FALSE, FALSE,  // M3 restall
	TRUE, TRUE, FALSE, FALSE,   // M3 win bmp
	FALSE, FALSE, FALSE, FALSE, // set char timer
	FALSE, FALSE, FALSE, FALSE, // M3 select a Robot
	FALSE, FALSE, FALSE, FALSE, // switch from 3D to 2D
	FALSE, FALSE, FALSE, FALSE, // show next demo
	FALSE, FALSE, FALSE, FALSE, // decide 2D after game
	FALSE, FALSE, FALSE, FALSE, // unload real game
	FALSE, FALSE, FALSE, FALSE, // decide win status
	TRUE, TRUE, FALSE, FALSE,   // show win final
	TRUE, TRUE, FALSE, FALSE,   // show win in the middle
	TRUE, TRUE, FALSE, FALSE,   // show ready to go
	TRUE, TRUE, FALSE, FALSE,   // show population
	TRUE, TRUE, FALSE, FALSE,   // show top 3
	FALSE, FALSE, FALSE, FALSE, // show credits
	TRUE, TRUE, FALSE, FALSE,   // modify top3 list
	FALSE, FALSE, FALSE, FALSE, // show end movie
	TRUE, TRUE, FALSE, FALSE,   // show new thank you
	TRUE, FALSE, FALSE, FALSE,   // final exit
	TRUE, TRUE, FALSE, FALSE,    // show game screen
	FALSE, FALSE, FALSE, FALSE,  // set up sound system 
	FALSE, FALSE, FALSE, FALSE,  // enter 3d world delay
	FALSE, FALSE, FALSE, FALSE,  // from 3d to 2d
	FALSE, FALSE, FALSE, FALSE,  // mission avi
	TRUE, TRUE, FALSE, FALSE,    // last question
	// === below are pages specific for freeware only!!
	//TRUE, TRUE, FALSE, FALSE,   // start splash
	TRUE, TRUE, FALSE, FALSE,   // get d3d info
	TRUE, TRUE, FALSE, FALSE,   // choose mode
	FALSE, FALSE, FALSE, FALSE, // switch to 3d
	//TRUE, TRUE, TRUE, TRUE,     // play 3d game
	//FALSE, FALSE, FALSE, FALSE, // switch to 2d
	TRUE, TRUE, FALSE, FALSE,    // ending splash
	// === above are pages specific for freeware only!!
   FALSE, FALSE, FALSE, FALSE,   // pg_END
	FALSE, FALSE, FALSE, FALSE,   // intro movie
	TRUE, TRUE, FALSE, FALSE,   // net wait for join
	TRUE, TRUE, FALSE, FALSE,   // net wait for opponent
	TRUE, TRUE, FALSE, FALSE,   // net show score
	TRUE, TRUE, FALSE, FALSE,   // net oppoent has left the game
	TRUE, TRUE, FALSE, FALSE,   // net generic error screen
	TRUE, TRUE, FALSE, FALSE    // final thank you
};

void BYSetPostPageSwitch(int page) 
{

	DDmode0 = bBYPageSwitch[page][0];
	DDmode1 = bBYPageSwitch[page][1];
	DDmode2 = bBYPageSwitch[page][2];
	DDmode3 = bBYPageSwitch[page][3];
}

void BYSetPrePageSwitch(int prepage, int postpage) 
{
	// make sure a surface switcher will not turn on before we
	// load bitmap files to that surface.
	DDmode0 = bBYPageSwitch[prepage][0] & bBYPageSwitch[postpage][0];
	DDmode1 = bBYPageSwitch[prepage][1] & bBYPageSwitch[postpage][1];
	DDmode2 = bBYPageSwitch[prepage][2] & bBYPageSwitch[postpage][2];
	DDmode3 = bBYPageSwitch[prepage][3] & bBYPageSwitch[postpage][3];
}


BOOL BYTurnToNextNPage(int page, int offset)
{
	Page = page + offset;
	return TRUE;
}

short BYGetFirstActiveItem(BOOL *Sflags, short Total)
{
	int i=0;
	for (i=0; i<Total; i++)
		if (Sflags[i]) break;
	return i;
}



void BYSetLevelSoFar(int level)
{
	LevelSoFar = level;
	
}

// KEYBOARD INPUT SELECTION 
void YBControlSFX(short direction)
{
	int KnobPos;	
	 
	if (direction==1) 
	{
		SFXValue+=5;
		if (SFXValue>100) SFXValue = 100;
		MaxSFXValue = (float) SFXValue*(float)4.0;
		KnobPos = (BarLength*SFXValue/100)+BarStartP;
		O2OptionMenuMap.des[17][0] = KnobPos;
		O2OptionMenuMap.des[15][0] = KnobPos;
		// call direct sound control function
   } else 
	if (direction==2) 
	{
		SFXValue-=5;
		if (SFXValue<0) SFXValue = 0;
		if (SFXValue==0) YBSndSilence=TRUE;
		else YBSndSilence=FALSE;
		MaxSFXValue = (float) SFXValue*(float)4.0;
		KnobPos = (BarLength*SFXValue/100)+BarStartP;
		O2OptionMenuMap.des[17][0] = KnobPos;
		O2OptionMenuMap.des[15][0] = KnobPos;
		// call direct sound control function
	}
}

int YBControlMID(short direction)
{
	int KnobPos;	
	 
	if (direction==1) { // increase midi volume
		MidValue+=5;
		if (MidValue>100) MidValue = 100;
        YBSetMidiVolume((MidValue*10));

		KnobPos = (BarLength*MidValue/100)+BarStartP;
        O2OptionMenuMap.des[18][0] = KnobPos;
        O2OptionMenuMap.des[16][0] = KnobPos;
		// call direct sound control function
    } else if (direction==2) { // reduce midi volume
		MidValue-=5;
		if (MidValue<0) MidValue = 0;
        YBSetMidiVolume((MidValue*10));

		KnobPos = (BarLength*MidValue/100)+BarStartP;
        O2OptionMenuMap.des[18][0] = KnobPos;
        O2OptionMenuMap.des[16][0] = KnobPos;
		// call direct sound control function
	}
    return MidValue;
}



int BYSelectTrainMenuFromKBD(WORD wparam)
{
	int j=0;

	switch(wparam) {
	case VK_ESCAPE:
		j = PG_BACK;
		break;
	case VK_UP:
	case VK_LEFT:
		S2NewIdx--;
		S2NewIdx = (5+S2NewIdx) % 5;
		break;

	case VK_DOWN:
	case VK_RIGHT:
		S2NewIdx++;
		S2NewIdx = S2NewIdx%5;
		break;

	case VK_RETURN:
		sndPlaySound(WrapSnd1, SND_ASYNC);
		j = 1;
		break;
	}
	if (S2OldIdx!=S2NewIdx) {
		S2ItemFlag[S2NewIdx]=1;
		S2ItemFlag[S2OldIdx]=0;
		S2OldIdx=S2NewIdx;
	}
	S3NewIdx = S2NewIdx;

	if (j>0) {
		GameStates.CurrentRobot = RobotMatchTable[S2NewIdx];
		return (S2NewIdx+j);
	}
	else
		return j;
}


void BYSetPageHandler(void)
{
	int i;

	for (i=0; i<TOTALPAGE; i++)
		BYPageHandler[i]=NULL;

	BYPageHandler[pg_SHOW_GOMAN_TITLE] = BYShowGomanTitle;
	BYPageHandler[pg_SHOW_MAIN_MENU]   = BYShowMainMenu;
	BYPageHandler[pg_SHOW_NEXTMISSION] = BYShowNextMission;
	BYPageHandler[pg_SHOW_CHAR_MENU]   = BYShowCharMenu;
	BYPageHandler[pg_SHOW_MOVIE_MENU]  = BYShowMovieMenu;
	BYPageHandler[pg_SHOW_TRAIN_MENU]  = BYShowTrainMenu;
	BYPageHandler[pg_SHOW_OPTION_MENU] = BYShowOptionMenu;
	BYPageHandler[pg_SHOW_MOUSECFG]    = BYShowMouseConFig;
	BYPageHandler[pg_SHOW_JOYSKCFG]    = BYShowJoystickConFig;
	BYPageHandler[pg_SHOW_LOAD_MENU]   = BYShowLoadMenu;
	BYPageHandler[pg_SHOW_SAVE_MENU]   = BYShowSaveMenu;
	BYPageHandler[pg_SHOW_KBD_MENU]    = BYShowKbdConfigure;
	BYPageHandler[pg_SHOW_3D_SAMPLE]   = BYShow3DExample;
	BYPageHandler[pg_DECIDE_LOSESTATUS]  = BYDecideLoseStatus;
	BYPageHandler[pg_SHOW_LOSE_ONE]    = BYShowLoseOne;
	BYPageHandler[pg_SHOW_LOSE_ALL]    = BYShowLoseAll;
	BYPageHandler[pg_AVIPLAY_DELAY]    = BYShowAviDelay;
	BYPageHandler[pg_PLAY_MOVIE]       = BYShowPlayMovie;
	BYPageHandler[pg_SHOW_AVI_BMP]     = BYShowAviBmp;
	BYPageHandler[pg_M3_SHOWLOSEBMP]   = BYShowM3LoseBmp;
	BYPageHandler[pg_M3_BACKTOMAIN]    = BYBackToMain;
	BYPageHandler[pg_DECIDE_M3STATUS]  = BYDecideMode3Status;
	BYPageHandler[pg_M3_RESTOREALL]    = BYM3RestoreAll;
	BYPageHandler[pg_M3_SHOWWINBMP]    = BYShowM3WinBmp;
	BYPageHandler[pg_M3_SELECTARobot]   = BYM3SelectARobot;
	BYPageHandler[pg_NEXT_AUTODEMO]    = BYShowNextDemo;
	BYPageHandler[pg_DECIDE2D_AFTGAME] = BYDecide2DAfterGame;
	BYPageHandler[pg_UNLOAD_REALGAME]  = BYUnloadRealGame;
	BYPageHandler[pg_DECIDE_WINSTATUS] = BYDecideWinStatus;
	BYPageHandler[pg_REAL_WONFINAL]    = BYShowWonFinal;
	BYPageHandler[pg_REAL_WONMIDDLE]   = BYShowWonMiddle;
	BYPageHandler[pg_END_OF_TRAIN]      = BYEndOfTraining;
	BYPageHandler[pg_SHOW_POPULATION]  = BYShowPopulation;
	BYPageHandler[pg_SHOW_TOP3]        = BYShowTop3;
	BYPageHandler[pg_SHOW_CREDITS]     = BYShowCredits;
	BYPageHandler[pg_END_MOVIE]        = BYShowEndingMovie;
	BYPageHandler[pg_NEW_THANKYOU]     = BYShowNewThankYou;
	BYPageHandler[pg_FINAL_EXIT]       = BYFinalExit;
	BYPageHandler[pg_SHOW_GAME_SCREEN] = BYShowGameScreen;
	BYPageHandler[pg_SETUP_SNDSYSTEM]  = BYSetUpSoundSystem;
	BYPageHandler[pg_ENTER3D_DELAY]    = BYDoEnter3DDelay;
	BYPageHandler[pg_FROM_3D_TO_2D]    = BYSwitchFrom3DTo2D;
	BYPageHandler[pg_MISSION_AVI]      = BYMissionAvi;
	BYPageHandler[pg_LAST_QUESTION]    = BYLastQuestion;
	BYPageHandler[pg_INTRO_MOVIE]      = BYIntroMovie;
	BYPageHandler[pg_NET_WAIT_FOR_JOIN]      = JSCNetWaitForJoin;
	BYPageHandler[pg_NET_WAIT_FOR_OPPONENT]      = JSCNetWaitForOpponent;
	BYPageHandler[pg_NET_SHOW_SCORE]   = JSCNetShowScore;
	BYPageHandler[pg_NET_OPPONENT_LEFT]= JSCNetOpponentLeft;
	BYPageHandler[pg_NET_ERROR]        = JSCNetErrorScreen;
	BYPageHandler[pg_THANKYOU]         = BYThankYou;

#ifdef FREEWARE
	BYPageHandler[pg_GET_D3DINFO]  = BYGetD3DInfo;
	BYPageHandler[pg_SWITCH_TO_3D] = BYSwitchTo3D;
	BYPageHandler[pg_CHOOSE_MODE]  = BYModeSelection;
	BYPageHandler[pg_ENDING_SPLASH] = BYEndingSplash;
#endif
}

void BYSetTimeHandler(void)
{
	int i;

	for (i=0; i<TOTALPAGE; i++)
	{
		BYTimeHandler[i]=BYDefaultHandler;
	}

	BYTimeHandler[pg_SHOW_GOMAN_TITLE] = BYTimeGomanTitle;
	BYTimeHandler[pg_SHOW_NEXTMISSION] = BYTimeNextMission;
	//BYTimeHandler[pg_SHOW_MOUSECFG]    = BYTimeShowMouseOrConfigure;
	//BYTimeHandler[pg_SHOW_JOYSKCFG]    = BYTimeShowMouseOrConfigure;
	BYTimeHandler[pg_AVIPLAY_DELAY]    = BYTimeAviDelay;
	BYTimeHandler[pg_M3_SHOWLOSEBMP]   = BYTimeM3WinOrLoseBmp;
	BYTimeHandler[pg_M3_SHOWWINBMP]    = BYTimeM3WinOrLoseBmp;
	BYTimeHandler[pg_SET_CHAR_TIMER]   = BYTimeSetChar;
	BYTimeHandler[pg_NEXT_AUTODEMO]    = BYTimeShowNextDemo;
	//BYTimeHandler[pg_REAL_WONFINAL]    = BYTimeShowWon;
	BYTimeHandler[pg_REAL_WONMIDDLE]   = BYTimeShowWon;
	BYTimeHandler[pg_END_OF_TRAIN]      = BYTimeReadyToGo;
	BYTimeHandler[pg_SHOW_POPULATION]  = BYTimeShowPopulation;
	BYTimeHandler[pg_SHOW_TOP3]        = BYTimeShowTop3;
	BYTimeHandler[pg_NEW_THANKYOU]     = BYTimeNewThankYou;
	BYTimeHandler[pg_SHOW_GAME_SCREEN] = BYTimeGameScreen;
	BYTimeHandler[pg_ENTER3D_DELAY]    = BYTimeEnterDelay;
	BYTimeHandler[pg_FROM_3D_TO_2D]    = BYTimeFrom3DTo2D;
	BYTimeHandler[pg_NET_WAIT_FOR_JOIN]    = JSCTimeNetWaitForJoin;
	BYTimeHandler[pg_NET_WAIT_FOR_OPPONENT]    = JSCTimeNetWaitForOpponent;
	BYTimeHandler[pg_NET_SHOW_SCORE]    = JSCTimeNetShowScore;
	BYTimeHandler[pg_NET_OPPONENT_LEFT] = JSCTimeNetOpponentLeft;
	BYTimeHandler[pg_NET_ERROR]         = JSCTimeNetErrorScreen;
	BYTimeHandler[pg_THANKYOU]         = BYTimeThankYou;

}

void BYSetKbrdHandler(void)
{
	int i;

	for (i=0; i<TOTALPAGE; i++)
	{
		BYKbrdHandler[i]=BYDefaultHandler; 
	}

	BYKbrdHandler[pg_SHOW_GOMAN_TITLE]  = BYKdGomanTitle;
	BYKbrdHandler[pg_SHOW_MAIN_MENU]    = BYKdMainMenu;
	BYKbrdHandler[pg_SHOW_CHAR_MENU]    = BYKdCharMenu;
	BYKbrdHandler[pg_SHOW_MOVIE_MENU]   = BYKdMovieMenu;
	BYKbrdHandler[pg_SHOW_TRAIN_MENU]   = BYKdTrainMenu;
	BYKbrdHandler[pg_SHOW_NEXTMISSION]  = BYKdNextMission;
	BYKbrdHandler[pg_SHOW_OPTION_MENU]  = BYKdOptionMenu;
	BYKbrdHandler[pg_SHOW_LOAD_MENU]    = BYKdShowLoadMenu;
	BYKbrdHandler[pg_SHOW_SAVE_MENU]    = BYKdShowSaveMenu;
	BYKbrdHandler[pg_PLAY_MOVIE]        = BYKdPlayMovie;
	BYKbrdHandler[pg_MISSION_AVI]       = BYKdMissionAvi;
	BYKbrdHandler[pg_LAST_QUESTION]     = BYKdLastQuestion;
	BYKbrdHandler[pg_INTRO_MOVIE]       = BYKdIntroMovie;
	BYKbrdHandler[pg_NET_WAIT_FOR_JOIN]       = JSCKdNetWaitForJoin;
	BYKbrdHandler[pg_NET_WAIT_FOR_OPPONENT]       = JSCKdNetWaitForOpponent;
	BYKbrdHandler[pg_NET_SHOW_SCORE]          = JSCKdNetShowScore;
	BYKbrdHandler[pg_NET_OPPONENT_LEFT]       = JSCKdNetOpponentLeft;
	BYKbrdHandler[pg_NET_ERROR]               = JSCKdNetErrorScreen;
#ifdef FREEWARE
	BYKbrdHandler[pg_CHOOSE_MODE]   = BYKdModeSelection;
	BYKbrdHandler[pg_ENDING_SPLASH] = BYKdEndingSplash;
#endif
}

void BYSetMiceHandler(void)
{
	int i;

	for (i=0; i<TOTALPAGE; i++)
	{
		BYMiceHandler[i]=BYDefaultHandler;
		BYMouseHandler[i] = BYDefaultMsHandler;
	}
}

// WM_COMMAND MESSAGE HANDLERS
// GOMAN TITLE: BEGINNING
// GOMAN TITLE SUBFUNCTIONS
void BYSetO1MainMenuB(void)
{
	S1Idx = 0;
	S1xy = &(MappingCor.des[0]);
	S1rect = &(MappingCor.src);
}  

// !!!!!!
// GOMAN TITLE MAIN FUNCTIONS
BOOL BYShowGomanTitle(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_GOMAN_TITLE);

   RestartTimer(myglobs.hWndMain);

	ShowCursor(FALSE);

	if (!GameStates.IsAutodemo)
	{
		MidCmd = MID_PLAY;
		MidNewIdx = 7;
		BYMidiCenter();
	}

	BYLoadOverlay(1, BmpFile[SplashScreen]);  // Load GoMan title bitmap file
	BYSetO1MainMenuB();             // Set display coordinates for overlay 1.
	bBYRenderingIsOK = TRUE;        // Enable rendering

	nTimer = SetTimer(win, 2, 6000, NULL);  

	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYKdGomanTitle(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISKEYDOWN(msg);
	ISPAGE(pg_SHOW_GOMAN_TITLE);

	if (wParam==VK_ESCAPE)
	{
		MidCmd = MID_STOP;
		BYMidiCenter();
		KillTimer(win, nTimer);

		//Add by Eric 11/15/96
		if (GameStates.IsNetplay)
		{
			EventSndBuf.MsgId = NEW_MSG;
			EventSndBuf.Event = EVENT_GOODBYE;
		}
		//end of Eric

		PostMessage(win, WM_DESTROY, 0, 0L);
	} 
	else
	{
		KillTimer(win, nTimer);  
		if (GameStates.IsAutodemo) 
		{
			GameStates.IsAutodemo = FALSE;
			GameStates.CurrentLevel = Mojave;
         if (hw3dacc == TRUE)
            detail = 4;
         else
            detail = 3;
		} 

#ifndef FREEWARE

		BYSetPrePageSwitch(Page, pg_INTRO_MOVIE); 	
		Page = pg_INTRO_MOVIE;
		PostMessage(win, WM_COMMAND, Page, 0L);
#else
		
		BYSetPrePageSwitch(Page, pg_GET_D3DINFO); 	
		Page = pg_GET_D3DINFO;
		PostMessage(win, WM_COMMAND, Page, 0L);
#endif
	}
	return TRUE;
	exit_with_false:
	return FALSE;
}

BOOL BYTimeGomanTitle(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static short ct=0;

	ISPAGE(pg_SHOW_GOMAN_TITLE);
//	IS_WRAPPER_TIMER(wParam);

	IS_WRAPPER_TIMER(wParam);

#ifndef FREEWARE
	if (ct<5) 
	{
		ct++;
		return FALSE;
	}
	else
	{
		KillTimer(win, nTimer);
		ct = 0;
//		PlayMode = SYS_REAL_GAME;
      if (hw3dacc == TRUE)
         detail = 5;
      else
         detail = 3;
      GameStates.IsAutodemo = TRUE;
		GameStates.IsTraining=FALSE;
		AutoDemoNext = TRUE;		
	}
#else
	KillTimer(win, nTimer);
#endif

	if (GameStates.IsAutodemo) 
	{
		GameStates.CurrentRobot = BYSelectARobot();
		BYSetPrePageSwitch(Page, pg_ENTER3D_DELAY); 
		Page = pg_ENTER3D_DELAY;
		PostMessage(win, WM_COMMAND, Page, 0L);
		AutoCountdown = RLVal(60);  
   }                              
	else
	{
#ifndef FREEWARE
		di.CreateDIMsDevice(TRUE);
	
		di.CreateMsSurface();
		di.LoadCursorBmp("cursor.bmp");
		di.SetMsCursorColorKey(TRUE, RGB(0,0,0));
		di.SelectAniCursor(ani_cursor);
		di.SetMsTotalAnis(1);
		di.SetMsAniSpeed(1);
		di.SetMsCursorInfo(8, 8, 16, 16);

		di.TurnOnMsCursor(TRUE);
	
		BYSetPrePageSwitch(Page, pg_SHOW_MAIN_MENU); 
		Page = pg_SHOW_MAIN_MENU;
		PostMessage(win, WM_COMMAND, Page, 0L);
#else
		BYSetPrePageSwitch(Page, pg_GET_D3DINFO); 
		Page = pg_GET_D3DINFO;
		PostMessage(win, WM_COMMAND, Page, 0L);
#endif
	}
	return TRUE;

exit_with_false:
	return FALSE;
}

// GOMAN TITLE: ENDING

// INTRO MOVIE: BEGINING
BOOL BYIntroMovie(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int i;
	ISPAGE(pg_INTRO_MOVIE);
	GameStates.CurrentSubmonster=Alpha;
	for( i=Mojave;i<=Tokyo;++i)
	{
		if(!GameStates.IsMonsterDead[i][Gamma])
		{
			GameStates.CurrentLevel=i;
			break;
		}
	}


	MidCmd = MID_STOP;
	BYMidiCenter();
	BYClearOverlaySurface(1);
	BYBlitOnToP(1, TRUE);

	PlayAVI(win, AVIFiles[0], "movie1", 0, AviSize);

	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYKdIntroMovie(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
   ISKEYDOWN(msg);
	ISPAGE(pg_INTRO_MOVIE);

	CloseAVI(win, "movie1");
	SetCursor(NULL);

	di.CreateDIMsDevice(TRUE);

	di.CreateMsSurface();
	di.LoadCursorBmp("cursor.bmp");
	di.SetMsCursorColorKey(TRUE, RGB(0,0,0));
	di.SelectAniCursor(ani_cursor);
	//di.SetMsTotalAnis(7);
	//di.SetMsAniSpeed(3);
	//di.SetMsCursorInfo(5, 5, 10, 10);
	di.SetMsTotalAnis(1);
	di.SetMsAniSpeed(1);
	di.SetMsCursorInfo(8, 8, 16, 16);

	di.TurnOnMsCursor(TRUE);

	BYSetPrePageSwitch(Page, pg_SHOW_MAIN_MENU); 	
	Page = pg_SHOW_MAIN_MENU;
	PostMessage(win, WM_COMMAND, Page, 0L);

	return TRUE;

exit_with_false:
	return FALSE;
}

void JSCDisplayWaitingToJoin(BOOL show, short mode)
{
	char fps[100];
	HDC  hDC;
	IDirectDrawSurface *pdds;
	HFONT hOldFont, hNewFont;

	if (show) 
	{
		pdds = lpDDSText;
		if (pdds==NULL) 
		{
			return;
		}

		if (pdds->GetDC(&hDC)==DD_OK) 
		{
			SetBkColor(hDC, RGB(0, 0, 0));
			SetBkMode(hDC, TRANSPARENT);

         hNewFont = BYSelectFont(hDC, "System", 0, 100);
			hOldFont = SelectObject(hDC, hNewFont);
			
         SetTextColor(hDC, RGB(0,0,0));
			SetTextAlign(hDC, TA_CENTER);

         sprintf(fps, "Waiting for");
        	TextOut(hDC, 320, 120, fps, lstrlen(fps));
        	sprintf(fps, "opponent to join");
        	TextOut(hDC, 320, 200, fps, lstrlen(fps));

         SelectObject(hDC, hOldFont);
			DeleteObject(hNewFont);

			SetBkColor(hDC, RGB(100, 100, 100));
			SetBkMode(hDC, OPAQUE);
			pdds->ReleaseDC(hDC);
		}
	}
}



BOOL JSCNetWaitForJoin(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_NET_WAIT_FOR_JOIN);

	BYLoadOverlay(1, BmpFile[13]);
	BYSetO1MainMenuB();
	BYChooseTextSurface(0);		// choose back surface
	BYDisplayText = JSCDisplayWaitingToJoin;
	DDtext = TRUE;
	EditMode = FALSE;
	nTimer = SetTimer(win, 2, 100, NULL);

   return TRUE;

exit_with_false:
	return FALSE;
}

BOOL JSCKdNetWaitForJoin(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
   ISKEYDOWN(msg);
	ISPAGE(pg_NET_WAIT_FOR_JOIN);

	if (wParam==VK_ESCAPE)
	{
		// An extra-harsh standin.  Game will exit entirely with ESC.  
      // Eventually, it will return to normal mode.
      MidCmd = MID_STOP;
		BYMidiCenter();
		KillTimer(win, nTimer);
		
		if (GameStates.IsNetplay)
		{
			EventSndBuf.MsgId = NEW_MSG;
			EventSndBuf.Event = EVENT_GOODBYE;
		}

		PostMessage(win, WM_DESTROY, 0, 0L);
	} 
	return TRUE;
exit_with_false:
	return FALSE;
}


BOOL JSCTimeNetWaitForJoin(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_NET_WAIT_FOR_JOIN);
	IS_WRAPPER_TIMER(wParam);

   if (!JSCHasPlayerJoined())
   {
	   nTimer = SetTimer(win, 2, 100, NULL);
      return FALSE;
   }

   KillTimer(win, nTimer);

   //BYDisplayText = JSCDisplayWaitingToJoin;
	DDtext = FALSE;
	EditMode = FALSE;

   BYSetPrePageSwitch(Page, pg_SHOW_CHAR_MENU); 	
	Page = pg_SHOW_CHAR_MENU;
	PostMessage(win, WM_COMMAND, Page, 0L);

	return TRUE;

exit_with_false:
	return FALSE;
}


BOOL JSCNetWaitForOpponent(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_NET_WAIT_FOR_OPPONENT);

	BYLoadOverlay(1, BmpFile[13]);
	BYSetO1MainMenuB();
	//SetPopuText();
	//DisplayText = BYDisplayPopu;
	//text = TRUE;
	//itMode = FALSE;
	nTimer = SetTimer(win, 2, 100, NULL);

   return TRUE;

exit_with_false:
	return FALSE;
}

BOOL JSCKdNetWaitForOpponent(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
   ISKEYDOWN(msg);
	ISPAGE(pg_NET_WAIT_FOR_OPPONENT);

	if (wParam==VK_ESCAPE)
	{
		MidCmd = MID_STOP;
		BYMidiCenter();
		KillTimer(win, nTimer);
		
		//Add by Eric 11/15/96
		if (GameStates.IsNetplay)
		{
			EventSndBuf.MsgId = NEW_MSG;
			EventSndBuf.Event = EVENT_GOODBYE;
		}
		//end of Eric

		PostMessage(win, WM_DESTROY, 0, 0L);
	} 
	return TRUE;
exit_with_false:
	return FALSE;
}


BOOL JSCTimeNetWaitForOpponent(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_NET_WAIT_FOR_OPPONENT);
	IS_WRAPPER_TIMER(wParam);

   if (!JSCSwappedSelectionInfo())
   {
	   nTimer = SetTimer(win, 2, 100, NULL);
      return FALSE;
   }
	KillTimer(win, nTimer);

   BYSetPrePageSwitch(Page, pg_ENTER3D_DELAY); 	
	Page = pg_ENTER3D_DELAY;
	PostMessage(win, WM_COMMAND, Page, 0L);

	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL JSCNetShowScore(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_NET_SHOW_SCORE);

	BYLoadOverlay(1, BmpFile[13]);
	BYSetO1MainMenuB();

   nTimer = SetTimer(win, 2, 6000, NULL);

   return TRUE;

exit_with_false:
	return FALSE;
}

BOOL JSCKdNetShowScore(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
   ISKEYDOWN(msg);
	ISPAGE(pg_NET_SHOW_SCORE);

	if (wParam==VK_ESCAPE)
	{
		MidCmd = MID_STOP;
		BYMidiCenter();
		KillTimer(win, nTimer);
		
		//Add by Eric 11/15/96
		if (GameStates.IsNetplay)
		{
			EventSndBuf.MsgId = NEW_MSG;
			EventSndBuf.Event = EVENT_GOODBYE;
		}
		//end of Eric

		PostMessage(win, WM_DESTROY, 0, 0L);
	} 
	return TRUE;
exit_with_false:
	return FALSE;
}


BOOL JSCTimeNetShowScore(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_NET_SHOW_SCORE);
	IS_WRAPPER_TIMER(wParam);

	KillTimer(win, nTimer);

   BYSetPrePageSwitch(Page, pg_SHOW_CHAR_MENU); 	
	Page = pg_SHOW_CHAR_MENU;
	PostMessage(win, WM_COMMAND, Page, 0L);

	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL JSCNetOpponentLeft(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_NET_OPPONENT_LEFT);

	BYLoadOverlay(1, BmpFile[13]);
	BYSetO1MainMenuB();
	nTimer = SetTimer(win, 2, 100, NULL);

   return TRUE;

exit_with_false:
	return FALSE;
}

BOOL JSCKdNetOpponentLeft(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
   ISKEYDOWN(msg);
	ISPAGE(pg_NET_OPPONENT_LEFT);

	if (wParam==VK_ESCAPE)
	{
		MidCmd = MID_STOP;
		BYMidiCenter();
		KillTimer(win, nTimer);
		
		//Add by Eric 11/15/96
		if (GameStates.IsNetplay)
		{
			EventSndBuf.MsgId = NEW_MSG;
			EventSndBuf.Event = EVENT_GOODBYE;
		}
		//end of Eric

		PostMessage(win, WM_DESTROY, 0, 0L);
	} 
	return TRUE;
exit_with_false:
	return FALSE;
}


BOOL JSCTimeNetOpponentLeft(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_NET_OPPONENT_LEFT);
	IS_WRAPPER_TIMER(wParam);

   if (!JSCSwappedSelectionInfo())
   {
	   nTimer = SetTimer(win, 2, 100, NULL);
      return FALSE;
   }
   else
		KillTimer(win, nTimer);

   BYSetPrePageSwitch(Page, pg_ENTER3D_DELAY); 	
	Page = pg_ENTER3D_DELAY;
	PostMessage(win, WM_COMMAND, Page, 0L);

	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL JSCNetErrorScreen(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_NET_ERROR);

	BYLoadOverlay(1, BmpFile[13]);
	BYSetO1MainMenuB();
	//SetPopuText();
	//DisplayText = BYDisplayPopu;
	//text = TRUE;
	//itMode = FALSE;
	nTimer = SetTimer(win, 2, 100, NULL);

   return TRUE;

exit_with_false:
	return FALSE;
}

BOOL JSCKdNetErrorScreen(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
   ISKEYDOWN(msg);
	ISPAGE(pg_NET_ERROR);

	if (wParam==VK_ESCAPE)
	{
		MidCmd = MID_STOP;
		BYMidiCenter();
		KillTimer(win, nTimer);
		
		//Add by Eric 11/15/96
		if (GameStates.IsNetplay)
		{
			EventSndBuf.MsgId = NEW_MSG;
			EventSndBuf.Event = EVENT_GOODBYE;
		}
		//end of Eric

		PostMessage(win, WM_DESTROY, 0, 0L);
	} 
	return TRUE;
exit_with_false:
	return FALSE;
}


BOOL JSCTimeNetErrorScreen(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_NET_ERROR);
	IS_WRAPPER_TIMER(wParam);

   if (!JSCSwappedSelectionInfo())
   {
	   nTimer = SetTimer(win, 2, 100, NULL);
      return FALSE;
   }
   else
		KillTimer(win, nTimer);

   BYSetPrePageSwitch(Page, pg_ENTER3D_DELAY); 	
	Page = pg_ENTER3D_DELAY;
	PostMessage(win, WM_COMMAND, Page, 0L);

	return TRUE;

exit_with_false:
	return FALSE;
}



// INTRO MOVIE: ENDING
// MAIN MENU: BEGINNING
// MAIN MENU SUB_FUNCTIONS
void BYSetO2MainMenuF(void)
{
	S2xy  = &(O2MainMenuMap.des[0][0]);
	S2rect = &(O2MainMenuMap.src[0]);
	
	S2TotalItems = O2MainMenuMap.titem;
	
	S2ItemFlag = &(O2MainMenuMap.flag[0]);
	S2OldIdx = S2NewIdx = BYGetFirstActiveItem(S2ItemFlag, 6);
}

int BYMsChooseMainMenu(void)
{
	POINT p;
	int i;

	p.x = (LONG) di.GetMsX();
	p.y = (LONG) di.GetMsY();
	
	for (i=0; i<6; i++) 
	{
	    if (PtInRect(&(MsMainMenuRect[i]), p)) break;
	}
	//if (i<6 && i>=0)                         // With netplay option 
	if (i<6 && i>=0 && i!=3 && i!=4)           // Without netplay option
	{
		S2NewIdx = i;
		if (S2OldIdx!=S2NewIdx) 
		{
			S2ItemFlag[S2NewIdx] = 1;
			S2ItemFlag[S2OldIdx] = 0;
			S2OldIdx = S2NewIdx;
		}
		if (msact==WP_LBUTTONDOWN)
		{
			//sndPlaySound(WrapSnd1, SND_ASYNC);
			return (S2NewIdx+1);
		}
	}
	return 0;
}

int JSCMsChooseNetSession(void)
{
	POINT p;
	int i;

	p.x = (LONG) di.GetMsX();
	p.y = (LONG) di.GetMsY();
	
	for (i=0; i<nSessionId - 1; i++) 
	{
	    if (PtInRect(&(MsNetMenuRect[i]), p)) break;
	}

	if (i<nSessionId - 1) 
	{
		WhichSession = i;
		if (msact==WP_LBUTTONDOWN)
		{
			return 1;
		}
	}
	return 0;
}


int BYMsChooseNetConnection(void)
{
	POINT p;
	int i;

	p.x = (LONG) di.GetMsX();
	p.y = (LONG) di.GetMsY();
	
	for (i=0; i<total_cntion; i++) 
	{
	    if (PtInRect(&(MsNetMenuRect[i]), p)) break;
	}

	if (i<total_cntion && i>=0) 
	{
		curt_cntion = i;
		if (msact==WP_LBUTTONDOWN)
		{
			return 1;
		}
	}
	return 0;
}

int BYChooseNetConnection(WORD wparam)
{
	int i=0;

	switch(wparam)
	{
	case VK_ESCAPE:
		i = PG_BACK;
		break;
	case VK_DOWN:
		if (curt_cntion<(total_cntion-1))
			curt_cntion++;
		else
			curt_cntion=0;
		break;
	case VK_UP:
		if (curt_cntion>0)
			curt_cntion--;
		else
			curt_cntion=total_cntion-1;
		break;
	case VK_RETURN:
		i = 1;
		break;
	}
	return i;
}

int BYSelectTitleMenuFromKBD(WORD wparam)
{
	int j=0;

	switch(wparam) 
	{
	case VK_ESCAPE:
		j = PG_BACK;
		break;
	case VK_DOWN:
	case VK_RIGHT:
		//if (S2NewIdx==3 || S2NewIdx==4)      // With netplay option
      if (S2NewIdx==2)                       // Without netplay option
		{
			S2NewIdx = 5;
		}
		else
		{
			S2NewIdx++;
			S2NewIdx = S2NewIdx % 6;
		}
		break;

	case VK_UP:
	case VK_LEFT:
		//if (S2NewIdx==3 || S2NewIdx==4)      // With netplay option
		if (S2NewIdx==5)                       // Without netplay option
		{
			S2NewIdx = 2;
		}
		else
		{
			if (S2NewIdx==5)
			{
				S2NewIdx = 2;
			}
			else
			{
				S2NewIdx--;
				S2NewIdx = (6+S2NewIdx) % 6;
			}
		}
		break;

      /*
	case VK_RIGHT:
	case VK_LEFT:
		if (S2NewIdx==3)
		{
			S2NewIdx = 4;
		}
		else
		{
			if (S2NewIdx==4)
			{
				S2NewIdx = 3;
			}
		}
		break;
      */

	case VK_RETURN:
		sndPlaySound(WrapSnd1, SND_ASYNC);
		j = 1;
		break;
	}
	if (S2OldIdx!=S2NewIdx) 
	{
		S2ItemFlag[S2NewIdx]=1;
		S2ItemFlag[S2OldIdx]=0;
		S2OldIdx=S2NewIdx;
        //sndPlaySound(WrapSnd1, SND_ASYNC);
	}
	if (j>0) 
		return (S2NewIdx+j);
	else
		return j;
}

short BYFindNextOptionItem3(short s, short e)
{
	short i;

	for (i=s; i<=e; i++) {
		if (O2OptionMenuMap.iflag[i])
			break;
	}
	return i;
}

void BYResetOptionMenuIdx(void)
{
	S2OldIdx = S2NewIdx = BYFindNextOptionItem3(0,2);
}

void BYSaveRestoreS2Idx(short mode)
{
    static short s2new = BYFindNextOptionItem3(0,2);
    static short s2old = BYFindNextOptionItem3(0,2);

    if (mode) {
        s2new = S2NewIdx;
        s2old = S2OldIdx;
    } else {
        S2NewIdx = s2new;
        S2OldIdx = s2old;
    }
}

// MAIN MENU MAIN FUNCTIONS
BOOL BYShowMainMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_MAIN_MENU);

	MidCmd = MID_PLAY;
	MidNewIdx = 7;
	BYMidiCenter();

	
	BYLoadOverlay(1, BmpFile[MainBackground]);
	BYLoadOverlay(2, BmpFile[MainForeground]);
	BYSetO1MainMenuB();
	BYSetO2MainMenuF();
	
	BYDisplayText = ShowNetConnections;
	bBYRenderingIsOK = TRUE; 

	di.TurnOnMsCursor(TRUE);

	BYMouseHandler[pg_SHOW_MAIN_MENU] = BYMsMainMenu;
	
	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYKdMainMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	short retval;

	ISKEYDOWN(msg);
	ISPAGE(pg_SHOW_MAIN_MENU);

	if (msg==WM_CHAR)
	{
		return FALSE;
	}

	if (!bInNetplayMenu)
	{
		retval=BYSelectTitleMenuFromKBD(wParam);
		if (retval==PG_BACK) 
		{
			di.TurnOnMsCursor(FALSE);

			BYSetPrePageSwitch(Page, pg_LAST_QUESTION); 
			Page = pg_LAST_QUESTION;
			PostMessage(win, WM_COMMAND, Page, 0L);

		} else
		if (retval==1) 
		{
			BYSetPrePageSwitch(Page, pg_SHOW_NEXTMISSION); 
			Page = pg_SHOW_NEXTMISSION;
			PostMessage(win, WM_COMMAND, Page, 0L);
		} else 
		if (retval==6) 
		{
 			BYSetPrePageSwitch(Page, pg_SHOW_OPTION_MENU); 
			Page = pg_SHOW_OPTION_MENU;
			SendMessage(win, WM_COMMAND, Page, 0L);
		} else 
		if (retval==3) 
		{
			BYSetPrePageSwitch(Page, pg_SHOW_TRAIN_MENU);
			Page = pg_SHOW_TRAIN_MENU;
			PostMessage(win, WM_COMMAND, Page, 0L);
		} else
		if (retval==2) 
		{
			BYSetPrePageSwitch(Page, pg_SHOW_MOVIE_MENU); 
			BYSetLevelSoFar(GameStates.CurrentLevel);
			Page = pg_SHOW_MOVIE_MENU;
			PostMessage(win, WM_COMMAND, Page, 0L);
		} else
		if (retval==4 || retval==5)
		{
			if (total_cntion)
			{
				bInNetplayMenu = TRUE;
				DDtext = TRUE;
				if (retval==4)
					S_NPMenu.ConIdx = 0;
				else
					S_NPMenu.ConIdx = 1;
			}
			else
			{
				; // TODO: display error message
			}

		}
	} 
	else	// bInNetplayMenu is TRUE
	{
      if (!bSessionList)
      {
			retval = BYChooseNetConnection(wParam);
			if (retval==1)
			{
				if (valid_cntion[curt_cntion]==1)
					S_NPMenu.isModem = TRUE;
				if (valid_cntion[curt_cntion]==2)
					S_NPMenu.isIPX = TRUE;
				if (valid_cntion[curt_cntion]==3)
					S_NPMenu.isInter = TRUE;
				if (valid_cntion[curt_cntion]==4)
					S_NPMenu.isSerial = TRUE;


				// Start netplay
				if (S_NPMenu.ConIdx == 0) 
				{
					di.TurnOnMsCursor(FALSE);
					ShowCursor(TRUE);

					isHost = TRUE;
					PlayAsMonster = FALSE;
					S_NPMenu.NetIdx = valid_cntion[curt_cntion]-1;
					if (!CreateSession() || !CreatePlayer(MASTERNAME))
					{
						;	// TODO: error message
					}

				   S_NPMenu.isCreate = TRUE;
				   S_NPMenu.isRobot = TRUE;
				   InitMsgBuf();
			      
               GameStates.IsNetplay = TRUE;

			      DDtext = FALSE;
			      bInNetplayMenu = FALSE;

               //BYSetPrePageSwitch(Page, pg_SHOW_CHAR_MENU); 	
		         //Page = pg_SHOW_CHAR_MENU;
		         //PostMessage(win, WM_COMMAND, Page, 0L);
               BYSetPrePageSwitch(Page, pg_NET_WAIT_FOR_JOIN); 	
		         Page = pg_NET_WAIT_FOR_JOIN;
		         PostMessage(win, WM_COMMAND, Page, 0L);
			}
			else  // join netplay
			{
            S_NPMenu.NetIdx = valid_cntion[curt_cntion]-1;
				if (!HowManySessions())
					return FALSE;

               bSessionList = TRUE;
           	   BYDisplayText = ShowSessionList;
			}
		}
		else if (retval==PG_BACK)
		{
			DDtext = FALSE;
			bInNetplayMenu = FALSE;
		}
	}
	else
      {  // bSessionList = True;
         retval = QHSelectSessionFromKBD(wParam);
         if ((retval == 1) && (WhichSession != -1))
         {
               S_NPMenu.KeyState = 1;
			      isHost = FALSE;
			      PlayAsMonster = TRUE;
			      if(!GetGame(WhichSession) || !CreatePlayer(SLAVENAME))
			      {
				      return FALSE;
			      }
			      
			      S_NPMenu.isConnect = TRUE;
			      S_NPMenu.isMonster = TRUE;
			      bSessionList = FALSE;
			      
			      InitMsgBuf();

               PlayAsMonster = TRUE;
               bMonsterMenu = TRUE;

               GameStates.IsNetplay = TRUE;

			      DDtext = FALSE;
			      bInNetplayMenu = FALSE;

               BYSetPrePageSwitch(Page, pg_SHOW_CHAR_MENU); 	
		         Page = pg_SHOW_CHAR_MENU;
		         PostMessage(win, WM_COMMAND, Page, 0L);
         }
         else if ((retval == PG_BACK) || (WhichSession != -1))
         {
            bSessionList = FALSE;
	         BYDisplayText = ShowNetConnections;
         } 
      }
	}
	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYMsMainMenu(HWND win)
{
	short retval;

	ISPAGE(pg_SHOW_MAIN_MENU);

	if (!bInNetplayMenu)
	{
		switch(msact) 
		{
		case WP_MOUSEMOVE:
			BYMsChooseMainMenu();
			break;
		case WP_LBUTTONDOWN:
			retval=BYMsChooseMainMenu();
			if (retval==PG_BACK) 
			{		
				//Add by Eric 11/15/96
				if (GameStates.IsNetplay)
				{
					EventSndBuf.MsgId = NEW_MSG;
					EventSndBuf.Event = EVENT_GOODBYE;
				}
				//end of Eric

				PostMessage(win, WM_DESTROY, 0, 0L);
			} else
			if (retval==1) 
			{
				sndPlaySound(WrapSnd1, SND_ASYNC);
				BYSetPrePageSwitch(Page, pg_SHOW_NEXTMISSION); 
				Page = pg_SHOW_NEXTMISSION;
				PostMessage(win, WM_COMMAND, Page, 0L);
			} else 
			if (retval==6) 
			{
				sndPlaySound(WrapSnd1, SND_ASYNC);
 				BYSetPrePageSwitch(Page, pg_SHOW_OPTION_MENU); 
				//BYResetOptionMenuIdx();
				//BYSaveRestoreS2Idx(1);
				Page = pg_SHOW_OPTION_MENU;
				SendMessage(win, WM_COMMAND, Page, 0L);
			} else 
			if (retval==3) 
			{
				sndPlaySound(WrapSnd1, SND_ASYNC);
    			BYSetPrePageSwitch(Page, pg_SHOW_TRAIN_MENU);
				Page = pg_SHOW_TRAIN_MENU;
				PostMessage(win, WM_COMMAND, Page, 0L);
			} else
			if (retval==2) 
			{
				sndPlaySound(WrapSnd1, SND_ASYNC);
				BYSetPrePageSwitch(Page, pg_SHOW_MOVIE_MENU); 
				BYSetLevelSoFar(GameStates.CurrentLevel);
				Page = pg_SHOW_MOVIE_MENU;
				PostMessage(win, WM_COMMAND, Page, 0L);
			} else
			if (retval==4 || retval==5)
			{
				sndPlaySound(WrapSnd1, SND_ASYNC);
				if (total_cntion)
				{
					bInNetplayMenu = TRUE;
					DDtext = TRUE;
					if (retval==4)
						S_NPMenu.ConIdx = 0;
					else
						S_NPMenu.ConIdx = 1;
				}
				else
				{
					; // TODO: display error message
				}
			}
			break;
		} // end of switch
	}
	else	// bInNetplayMenu is TRUE
	{
		// TODO: 
		retval = BYMsChooseNetConnection();
		if (retval==1)
		{

			if (valid_cntion[curt_cntion]==1)
				S_NPMenu.isModem = TRUE;
			if (valid_cntion[curt_cntion]==2)
				S_NPMenu.isIPX = TRUE;
			if (valid_cntion[curt_cntion]==3)
				S_NPMenu.isInter = TRUE;
			if (valid_cntion[curt_cntion]==4)
				S_NPMenu.isSerial = TRUE;


			// Start netplay
			if (S_NPMenu.ConIdx == 0) 
			{
				di.TurnOnMsCursor(FALSE);
				ShowCursor(TRUE);

				isHost = TRUE;
				PlayAsMonster = FALSE;
            S_NPMenu.NetIdx = valid_cntion[curt_cntion]-1;
				if (!CreateSession() || !CreatePlayer(MASTERNAME))
				{
					;	// TODO: error message
				}

				ShowCursor(FALSE);
				di.TurnOnMsCursor(TRUE);

				S_NPMenu.isCreate = TRUE;
				S_NPMenu.isRobot = TRUE;
				InitMsgBuf();

            BYSetPrePageSwitch(Page, pg_NET_WAIT_FOR_JOIN); 	
		      Page = pg_NET_WAIT_FOR_JOIN;
		      PostMessage(win, WM_COMMAND, Page, 0L);
			}
			else  // join netplay
			{
            S_NPMenu.NetIdx = valid_cntion[curt_cntion]-1;
				if (!HowManySessions())
					return FALSE;
            retval = JSCMsChooseNetSession();
            if ((retval == 1) && (WhichSession != -1))
            {
               S_NPMenu.KeyState = 1;
			      isHost = FALSE;
			      PlayAsMonster = TRUE;
			      if(!GetGame(WhichSession) || !CreatePlayer(SLAVENAME))
			      {
				      return FALSE;
			      }
			      
			      S_NPMenu.isConnect = TRUE;
			      S_NPMenu.isMonster = TRUE;
			      bSessionList = FALSE;
			      
			      InitMsgBuf();

               bSessionList = TRUE;
               PlayAsMonster = TRUE;
               bMonsterMenu = TRUE;
               BYSetPrePageSwitch(Page, pg_SHOW_CHAR_MENU); 	
		         Page = pg_SHOW_CHAR_MENU;
		         PostMessage(win, WM_COMMAND, Page, 0L);
			   }

			   DDtext = FALSE;
			   bInNetplayMenu = FALSE;
         }


		}
		else if (retval==PG_BACK)
		{
			DDtext = FALSE;
			bInNetplayMenu = FALSE;
		}
	}

	return TRUE;
exit_with_false:
	return FALSE;
}
// MAIN MENU: ENDING

// MOVIE MENU: BEGINNING
// MOVIE MENU SUB_FUNCTIONS
void BYSetO2MovieMenuF(void)
{
    S2xy  = &(O2MovieMenuMap.des[0][0]);
    S2rect = &(O2MovieMenuMap.src[0]);
    S2TotalItems = O2MovieMenuMap.titem;
	S2ItemFlag = &(O2MovieMenuMap.flag[0]);
	S2OldIdx = S2NewIdx = BYGetFirstActiveItem(S2ItemFlag, 7);
}

int BYMsChooseMovieMenu(void)
{
	POINT p;
	int i;
	RECT rr = {19, 60, 535, 356};

	p.x = (LONG) di.GetMsX();
	p.y = (LONG) di.GetMsY();
	
	if (msact==WP_MOUSEMOVE) 
	{
		if (PtInRect(&rr, p))
			MvInBefore=1;

		if (!PtInRect(&rr, p) && MvInBefore) 
			return 0; 
	}
    
	for (i=0; i<8; i++) {
	    if (PtInRect(&(MsMovieMenuRect[i]), p)) break;
	}

	if ((i<7 && i>=0 && i<=LevelSoFar) || i==7) {
		S2NewIdx = i;
		if (S2OldIdx!=S2NewIdx) {
			S2ItemFlag[S2NewIdx] = 1;
			S2ItemFlag[S2OldIdx] = 0;
			S2OldIdx = S2NewIdx;
		}
		if (msact==WP_LBUTTONDOWN)
		{
			sndPlaySound(WrapSnd1, SND_ASYNC);
			return (S2NewIdx+1);
		}
	}
	if (msact==WP_LBUTTONDOWN)
	{
		return 0;
	} 
	else
	{    
		return 1;

	}
}

int BYSelectMovieMenuFromKBD(WORD wparam)
{
	int j=0;

	switch(wparam) {
	case VK_ESCAPE:
		j = PG_BACK;
		break;
	case VK_UP:
	case VK_LEFT:
        if (S2NewIdx==0)
            S2NewIdx=7;
        else {
		    S2NewIdx--;
    		S2NewIdx = (7+S2NewIdx) % 7;
    		while (S2NewIdx>LevelSoFar) {
    			S2NewIdx--;
    			S2NewIdx = (7+S2NewIdx) % 7;
    		}
        }
		break;

	case VK_DOWN:
	case VK_RIGHT:
        if (S2NewIdx>=7)
            S2NewIdx=0;
        else
		    S2NewIdx++;	
		if (S2NewIdx>LevelSoFar)
		    S2NewIdx=7;

		break;

	case VK_RETURN:
       sndPlaySound(WrapSnd1, SND_ASYNC);
	    j = 1;
		break;
	}
	if (S2OldIdx!=S2NewIdx) {
		S2ItemFlag[S2NewIdx]=1;
		S2ItemFlag[S2OldIdx]=0;
		S2OldIdx=S2NewIdx;
	}
	if (j>0) 
		return (S2NewIdx+j);
	else
		return j;
}                                                 

// MOVIE MENU MAIN FUNCTIONS
BOOL BYShowMovieMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_MOVIE_MENU);

	MidCmd = MID_PLAY;
	MidNewIdx = 7;
	BYMidiCenter();

	//if (VMode==5 || VMode==6) return FALSE;	
	MvInBefore = 0;
	BYLoadOverlay(1, BmpFile[MovieMenuBackground]);   
	BYLoadOverlay(2, BmpFile[MovieMenuForeground]);   
	BYSetO2MovieMenuF();

	BYMouseHandler[pg_SHOW_MOVIE_MENU] = BYMsMovieMenu;

	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYKdMovieMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	short retval;

   ISKEYDOWN(msg);
	ISPAGE(pg_SHOW_MOVIE_MENU);

	if (msg==WM_CHAR)
	{
		return FALSE;
	}

	retval=BYSelectMovieMenuFromKBD(wParam);
	if (retval==PG_BACK) {
		BYSetPrePageSwitch(Page, pg_SHOW_MAIN_MENU); 
		Page = pg_SHOW_MAIN_MENU;
		PostMessage(win, WM_COMMAND, Page, 0L);
    } else 
	if (retval>0) {
		whichavi = retval;
		BYSetPrePageSwitch(Page, pg_AVIPLAY_DELAY); 	
		Page = pg_AVIPLAY_DELAY; //PLAY_MOVIE;
		PostMessage(win, WM_COMMAND, Page, 0L);
	}
	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYMsMovieMenu(HWND win)
{
	ISPAGE(pg_SHOW_MOVIE_MENU);

	switch(msact) 
	{
	case WP_MOUSEMOVE:
		if (!BYMsChooseMovieMenu()) {
			BYSetPrePageSwitch(Page, pg_SHOW_MAIN_MENU); 	
			Page = pg_SHOW_MAIN_MENU; 
			PostMessage(win, WM_COMMAND, Page, 0L);
		}
		break;
	case WP_LBUTTONDOWN:
		whichavi=BYMsChooseMovieMenu();
		if (whichavi) {
			sndPlaySound(WrapSnd1, SND_ASYNC);
			BYSetPrePageSwitch(Page, pg_AVIPLAY_DELAY); 	
			Page = pg_AVIPLAY_DELAY; //PLAY_MOVIE;
			PostMessage(win, WM_COMMAND, Page, 0L);
		}
		break;
	}
	return TRUE;
exit_with_false:
	return FALSE;
}

// MOVIE MENU: ENDING

// CHAR MENU: BEGINNING
// CHAR MENU SUB_FUNCTIONS
void BYSetO2CharMenuF(void)
{
	int i, idx;

	S2xy  = &(O2CharMenuMap.des[0][0]);
	S2rect = &(O2CharMenuMap.src[0]);
	S2TotalItems = O2CharMenuMap.titem;
	S2ItemFlag = &(O2CharMenuMap.flag[0]);
	//S2OldIdx = S2NewIdx = BYGetFirstActiveItem(S2ItemFlag, 4);

	for (i=0; i<5; i++)
	{
		S2ItemFlag[i] = 0;
	}

	for (i=0; i<5; i++) 
	{
		idx = RobotMatchTable[i];
		if (!GameStates.IsRobotDead[idx]) 
		{
			S2OldIdx = S2NewIdx = i;
			break;
		}
	}
	S2ItemFlag[S2OldIdx] = 1;
}

void BYSetO3CharMenuF(void)
{
    S3xy  = &(O3CharMenuMap.des[0][0]);
    S3rect = &(O3CharMenuMap.src[0]);
    S3TotalItems = O3CharMenuMap.titem;
    S3ItemFlag = &(O2CharMenuMap.flag[0]);

    //for (i=0; i<5; i++)
    //    S3ItemFlag[i] = 0;

    //for (i=0; i<5; i++) {
    //    idx = RobotMatchTable[i] - 1;
    //    if (RobotStatus[idx]) {
	//        S3OldIdx = S3NewIdx = i;
	//        break;
	//    }
    //}
    S3ItemFlag[S2OldIdx] = 1;
    S3OldIdx = S3NewIdx = S2OldIdx;
    //S3OldIdx = S3NewIdx = YBGetFirstActiveItem(S2Flag1, 5);
}

int BYSelectCharMenuFromKBD(WORD wparam)
{
	int idx;
	int j=0;

	switch(wparam) 
	{
	case VK_ESCAPE:
		j = PG_BACK;
		break;
	case VK_UP:
	case VK_LEFT:
		if(GameStates.IsNetplay && bSelectRobot) break; //Liou qinghua add 1996,11,16
		S2NewIdx--;
		S2NewIdx = (5+S2NewIdx) % 5;
		idx = RobotMatchTable[S2NewIdx];
		if(!GameStates.IsNetplay) //The condition added by Liou qinghua 1996,11,16
		{            //in order to select anyone of Robots.  
			while (GameStates.IsRobotDead[idx]) {
    			S2NewIdx--;
    			S2NewIdx = (5+S2NewIdx) % 5;
				idx = RobotMatchTable[S2NewIdx];
			}
		}
		break;

	case VK_DOWN:
	case VK_RIGHT:
		if(GameStates.IsNetplay && bSelectRobot) break; //Liou qinghua add 1996,11,16
		S2NewIdx++;
		S2NewIdx = S2NewIdx%5;
		idx = RobotMatchTable[S2NewIdx];
		if(!GameStates.IsNetplay) //The condition added by Liou qinghua 1996,11,16
		{            //in order to select anyone of Robots.  
			while (GameStates.IsRobotDead[idx]) {
    			S2NewIdx++;
    			S2NewIdx = S2NewIdx % 5;
				idx = RobotMatchTable[S2NewIdx];
			}
		}
		break;

	case VK_RETURN:
		if(GameStates.IsNetplay && bSelectRobot) break; //Liou qinghua add 1996,11,16
      sndPlaySound(WrapSnd1, SND_ASYNC);
		j = 1;
		if(GameStates.IsNetplay) bSelectRobot = TRUE; //Liou qinghua add 1996,11,12
		break;
	}
	if (S2OldIdx!=S2NewIdx) {
		S2ItemFlag[S2NewIdx]=1;
		S2ItemFlag[S2OldIdx]=0;
		S2OldIdx=S2NewIdx;
        //sndPlaySound(WrapSnd1, SND_ASYNC);
	}
	S3NewIdx = S2NewIdx;

	if (j>0) {
        idx = RobotMatchTable[S2NewIdx];
        if (!GameStates.IsRobotDead[idx]) {
    		GameStates.CurrentRobot = idx;
    		return (S2NewIdx+j);
        } else {
            j = 0;
            return j;
        } 
	}
	else
		return j;
}

int BYMsChooseCharMenu(void)
{
	POINT p;
	int i, idx;

	if(GameStates.IsNetplay && bSelectRobot) return 0; //Liou qinghua add 1996,11,16

	p.x = (LONG) di.GetMsX();
	p.y = (LONG) di.GetMsY();

	for (i=0; i<5; i++) {
	    if (PtInRect(&(MsCharMenuRect[i]), p)) break;
	}
	if (i<5 && i>=0) 
	{
		S2NewIdx = i;
		idx = RobotMatchTable[S2NewIdx];

		if(!GameStates.IsNetplay) //The condition added by Liou qinghua 1996,11,16
		{            //in order to select anyone of Robots.  
			if (S2OldIdx!=S2NewIdx && (!GameStates.IsRobotDead[idx])) {
				S2ItemFlag[S2NewIdx] = 1;
				S2ItemFlag[S2OldIdx] = 0;
				S2OldIdx = S2NewIdx;
				S3NewIdx = S2NewIdx;
				//sndPlaySound(WrapSnd1, SND_ASYNC);
				return 0;
			} else 
		if (msact==WP_LBUTTONDOWN && (!GameStates.IsRobotDead[idx])) {
				GameStates.CurrentRobot = RobotMatchTable[S2NewIdx];
				//bSelectRobot = TRUE; //Liou qinghua add 1996,11,12
				sndPlaySound(WrapSnd1, SND_ASYNC);
				return 1;
			}
		}
		else         //The condition added by Liou qinghua 1996,11,16
		{            //in order to select anyone of Robots.  
			if (S2OldIdx!=S2NewIdx) 
			{
				S2ItemFlag[S2NewIdx] = 1;
				S2ItemFlag[S2OldIdx] = 0;
				S2OldIdx = S2NewIdx;
				S3NewIdx = S2NewIdx;
				//sndPlaySound(WrapSnd1, SND_ASYNC);
				return 0;
			} 
			else if (msact==WP_LBUTTONDOWN) 
			{
				GameStates.CurrentRobot = RobotMatchTable[S2NewIdx];
				bSelectRobot = TRUE; //Liou qinghua add 1996,11,12
				//sndPlaySound(WrapSnd1, SND_ASYNC);
	   			return 1;
			}
		}
	} 
	return 0;	
}

// CHAR MENU MAIN FUNCTIONS
BOOL BYShowCharMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_CHAR_MENU);
	
	di.TurnOnMsCursor(TRUE);

	MidCmd = MID_PLAY;
	MidNewIdx = 7;
	BYMidiCenter();
	//Liou qinghua add///////////////////
	if(PlayAsMonster)
	{
		//bQHSelectMonster = TRUE;
		BYLoadOverlay(1, "WR600.BMP");  // CHAR background
		BYLoadOverlay(2, "WR601.BMP");  // height light
		BYLoadOverlay(3, "WR602.BMP");  // describe
		
	}
	////////////////////////////////////
	else
	{
		BYLoadOverlay(1, BmpFile[CharacterMenuBackground]);  // CHAR background
		BYLoadOverlay(2, BmpFile[CharacterMenuBigForeground]);  // CHAR foreground 1
		BYLoadOverlay(3, BmpFile[CharacterMenuSmallForeground]);  // CHAR foreground 2
	}
	BYSetO1MainMenuB();
	BYSetO2CharMenuF();
	BYSetO3CharMenuF();
	bBYRenderingIsOK = TRUE; 

	BYMouseHandler[pg_SHOW_CHAR_MENU] = BYMsCharMenu;

	return TRUE;

exit_with_false:
	return FALSE;
}


BOOL BYMsCharMenu(HWND win)
{
	ISPAGE(pg_SHOW_CHAR_MENU);

	//Liou qinghua modified 1996,11,12
	if(!PlayAsMonster)
	{
		if(GameStates.IsNetplay && bSelectRobot) return TRUE; //Liou qinghua add 1996,11,16
		switch(msact) 
		{
		case WP_MOUSEMOVE:
	    BYMsChooseCharMenu();
			break;
		case WP_LBUTTONDOWN:
			if (BYMsChooseCharMenu()==1) 
			{
				//BYSetPrePageSwitch(Page, pg_SHOW_GAME_SCREEN); 
				//Page = pg_SHOW_GAME_SCREEN;
				//PostMessage(win, WM_COMMAND, Page, 0L);
				if(!GameStates.IsNetplay)//Liou qinghua add 96,11,13
				{
//					PlayMode = SYS_REAL_GAME;
					GameStates.IsTraining=FALSE;

					BYSetPrePageSwitch(Page, pg_ENTER3D_DELAY); 
					Page = pg_ENTER3D_DELAY;
					PostMessage(win, WM_COMMAND, Page, 0L);
				}
			}
			break;
		}
		return TRUE;
	}
	else
	{
		if(GameStates.IsNetplay && bSelectMonster) return TRUE; //Liou qinghua add 1996,11,16
		switch(msact) //Guatemalan insanity code.  What the heck happens here?
		{
//			PlayMode = SYS_REAL_GAME;
			GameStates.IsTraining=FALSE;

			if(!GameStates.IsNetplay)//Liou qinghua add 96,11,13
			{
				BYSetPrePageSwitch(Page, pg_ENTER3D_DELAY); 
				Page = pg_ENTER3D_DELAY;
				PostMessage(win, WM_COMMAND, Page, 0L);
			}
		}
	}
	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYKdCharMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	short retval;

   ISKEYDOWN(msg);
	ISPAGE(pg_SHOW_CHAR_MENU);

	if (msg==WM_CHAR)
	{
		return FALSE;
	}
	//Liou qinghua changed 1996,11,12
	//retval=BYSelectCharMenuFromKBD(wParam);
	if(!PlayAsMonster)
	{
		retval=BYSelectCharMenuFromKBD(wParam);
	}
	else
	{
		retval=QHSelectCharMenuFromKBD(wParam);
	}
	/////////////////////////////////////////

	if (retval==PG_BACK) 
	{
		BYSetPrePageSwitch(Page, pg_SHOW_MAIN_MENU); 
		Page = pg_SHOW_MAIN_MENU;
		PostMessage(win, WM_COMMAND, Page, 0L);
	} 
	else 
	if (retval)
	{
//		PlayMode = SYS_REAL_GAME;
		GameStates.IsTraining=FALSE;
//		OldLevel = GameStates.CurrentLevel;
		//Liou qinghua turn off 199,11,13
		if(!GameStates.IsNetplay)//Liou qinghua add 96,11,13
		{
			BYSetPrePageSwitch(Page, pg_ENTER3D_DELAY); 
			Page = pg_ENTER3D_DELAY;
			PostMessage(win, WM_COMMAND, Page, 0L);
		}
      else
		{
			BYSetPrePageSwitch(Page, pg_NET_WAIT_FOR_OPPONENT); 
			Page = pg_NET_WAIT_FOR_OPPONENT;
			PostMessage(win, WM_COMMAND, Page, 0L);
		}
	} 
	return TRUE;

exit_with_false:
	return FALSE;
}


// CHAR MENU: ENDING

// TRAIN MENU: BEGINNING
// TRAIN MENU SUB_FUNCTIONS
int BYMsChooseTrainMenu(void)
{
	POINT p;
	int i;

	p.x = (LONG) di.GetMsX();
	p.y = (LONG) di.GetMsY();

	for (i=0; i<5; i++) {
	    if (PtInRect(&(MsCharMenuRect[i]), p)) break;
	}
	if (i<5 && i>=0) {
		S2NewIdx = i;
		if (S2OldIdx!=S2NewIdx) {
			S2ItemFlag[S2NewIdx] = 1;
			S2ItemFlag[S2OldIdx] = 0;
			S2OldIdx = S2NewIdx;
			S3NewIdx = S2NewIdx;
		}
		if (msact==WP_LBUTTONDOWN)
		{
			//sndPlaySound(WrapSnd1, SND_ASYNC);
			GameStates.CurrentRobot = RobotMatchTable[S2NewIdx];
	   		return (1);
		}
	}
	return 0;
}

// TRAIN MENU MAIN FUNCTIONS
BOOL BYShowTrainMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_TRAIN_MENU);

	MidCmd = MID_PLAY;
	MidNewIdx = 7;
	BYMidiCenter();

	BYLoadOverlay(1, BmpFile[CharacterMenuBackground]);  // CHAR background
	BYLoadOverlay(2, BmpFile[CharacterMenuBigForeground]);  // CHAR foreground 1
	BYLoadOverlay(3, BmpFile[CharacterMenuSmallForeground]);  // CHAR foreground 2
	BYSetO1MainMenuB();
	BYSetO2CharMenuF();
	BYSetO3CharMenuF();

	BYMouseHandler[pg_SHOW_TRAIN_MENU] = BYMsTrainMenu;

	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYKdTrainMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	short retval;

   ISKEYDOWN(msg);
	ISPAGE(pg_SHOW_TRAIN_MENU);

	if (msg==WM_CHAR)
	{
		return FALSE;
	}

	retval=BYSelectTrainMenuFromKBD(wParam);
	if (retval==PG_BACK) {
		BYSetPrePageSwitch(Page, pg_SHOW_MAIN_MENU); 
		Page = pg_SHOW_MAIN_MENU;
		PostMessage(win, WM_COMMAND, Page, 0L);
    } 
	else 
	if (retval)
	{
		PreserveForTrainer();
		GameStates.CurrentLevel = Trainer;
		// stop midi
//		PlayMode = SYS_TRAINING;
		GameStates.IsTraining=TRUE;

		BYSetPrePageSwitch(Page, pg_ENTER3D_DELAY); 
		Page = pg_ENTER3D_DELAY;
		PostMessage(win, WM_COMMAND, Page, 0L);

		//nTimer = SetTimer(win, 2, 1000, NULL);
		;
	} 
	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYMsTrainMenu(HWND win)
{
	ISPAGE(pg_SHOW_TRAIN_MENU);

	switch(msact) 
	{
	case WP_MOUSEMOVE:
		BYMsChooseTrainMenu();
		break;
	case WP_LBUTTONDOWN:
		if (BYMsChooseTrainMenu()==1) 
		{
			sndPlaySound(WrapSnd1, SND_ASYNC);
		   PreserveForTrainer();
			GameStates.CurrentLevel = Trainer;
			// stop midi
//			PlayMode = SYS_TRAINING;
			GameStates.IsTraining=TRUE;

			BYSetPrePageSwitch(Page, pg_ENTER3D_DELAY); 
			Page = pg_ENTER3D_DELAY;
			PostMessage(win, WM_COMMAND, Page, 0L);
		}
		break;
	}
	return TRUE;

exit_with_false:
	return FALSE;
}

// TRAIN MENU: ENDING

// OPTION MENU: BEGINNING
// OPTION MENU SUB_FUNCTIONS
void BYSetO2OptionMenuF(void)
{	
	S2xy  = &(O2OptionMenuMap.des[0][0]);
	S2rect = &(O2OptionMenuMap.src[0]);
	S2TotalItems = O2OptionMenuMap.titem;
	S2ItemFlag = &(O2OptionMenuMap.oflag[0]);
	S3ItemFlag = &(O2OptionMenuMap.iflag[0]);  
}

short YBFindMndIdx(int i)
{
	short idx;

	switch(i) 
	{
	case 0:
	case 1:
	case 2:
		idx = 0;
		break;
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		idx = 1;
		break;
	case 8:
	case 9:
		idx = i-5;
		break;
	case 10:
	case 11:
	case 12:
		idx = 2;
		break;
		break;
	case 13:
	case 14:
	case 15:
	case 16:
		idx = i-8;
		break;
	}
	return idx;    
}

void YBFindStartNEnd(short i, short *s, short *e)
{
    switch(i) {
    case 0:
    case 1:
    case 2:
        *s = 0;
        *e = 2;
        break;
    case 3:
    case 4:
    case 5:
	case 6:
	case 7:
      //if (hw3dacc == TRUE)
      //   *s = 6;
      //else
        *s = 3;

        *e = 7;
        break;
    case 10:
    case 11:
    case 12:
        *s = 10;
        *e = 12;
        break;
    case 8:
    case 9:
    case 13:
    case 14:
        break;
    }
}

short YBFindNextOptionItem3(short s, short e)
{
	short i;

	for (i=s; i<=e; i++) {
		if (S3ItemFlag[i])
			break;
	}
	return i;
}


int BYSelectOptionMenuFromKBD(WORD wparam)
{
	int j=0;
	short idx;

	switch(wparam) 
	{
	case VK_ESCAPE:
		j = PG_BACK;
		DDtext = FALSE;
		bInWSize = FALSE;
		bInVModeMenu = FALSE;
		break;
	case VK_UP:
		switch(S2OldIdx) 
		{
		case 0:
		case 1:
		case 2:
			S2ItemFlag[S2OldIdx] = 0;
			S2ItemFlag[20] = 1;
			S2OldIdx = S2NewIdx = 20;
			DDtext = TRUE;
			bInWSize = TRUE;
			break;

		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			S2ItemFlag[S2OldIdx] = 0;
			idx = BYFindNextOptionItem3(0, 2);
			S2ItemFlag[idx] = 1;
			S2OldIdx = S2NewIdx = idx;
			break;

		case 8:
			S2ItemFlag[S2OldIdx] = 0;
			S2ItemFlag[15] = 1;
			S2ItemFlag[17] = 0;
			idx = BYFindNextOptionItem3(3, 7);
			S2ItemFlag[idx] = 1;
			S2OldIdx = S2NewIdx = idx;
			break;

		case 9:
			S2ItemFlag[S2OldIdx] = 0;
			S2ItemFlag[15] = 0;
			S2ItemFlag[16] = 1;
			S2ItemFlag[17] = 1;
			S2ItemFlag[18] = 0;
			S2ItemFlag[8] = 1;
			S2OldIdx = S2NewIdx = 8;
			break;

		case 10:
		case 11:
		case 12:
			S2ItemFlag[S2OldIdx] = 0;
			S2ItemFlag[16] = 0;
			S2ItemFlag[18] = 1;
			S2ItemFlag[9] = 1;
			S2OldIdx = S2NewIdx = 9;
			break;

		case 13:
		case 14:
			S2ItemFlag[S2OldIdx] = 0;
			idx = BYFindNextOptionItem3(10, 12);
			S2ItemFlag[idx] = 1;
			S2OldIdx = S2NewIdx = idx;
			break;
		case 19:
			S2ItemFlag[S2OldIdx] = 0;
			S2ItemFlag[14] = 1;
			S2OldIdx = S2NewIdx = 14;
			DDtext = FALSE;
			bInVModeMenu = FALSE;
			tpmode = current_mode;
			break;
		case 20:
			S2ItemFlag[S2OldIdx] = 0;
			S2ItemFlag[19] = 1;
			S2OldIdx = S2NewIdx = 19;
			bInVModeMenu=TRUE;
			bInWSize = FALSE;
			tpsize = current_size;
			break;
		};
        //sndPlaySound(WrapSnd1, SND_ASYNC);
		break; // end of switch VK_UP

	case VK_DOWN:
		switch(S2OldIdx) {
		case 0:
		case 1:
		case 2:
			S2ItemFlag[S2OldIdx] = 0;
			idx = BYFindNextOptionItem3(3, 7);
			S2ItemFlag[idx] = 1;
			S2OldIdx = S2NewIdx = idx;
			break;
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			S2ItemFlag[S2OldIdx] = 0;
			S2ItemFlag[8] = 1;
			S2ItemFlag[17] = 1;
			S2ItemFlag[15] = 0;
			S2OldIdx = S2NewIdx = 8;
			break;
		case 8:
			S2ItemFlag[8] = 0;
			S2ItemFlag[9] = 1;
			S2ItemFlag[15] = 1;
			S2ItemFlag[17] = 0;
			S2ItemFlag[16] = 0;
			S2ItemFlag[18] = 1;
			S2OldIdx = S2NewIdx = 9;
			break;
		case 9:
			S2ItemFlag[9] = 0;
			S2ItemFlag[16] = 1;
			S2ItemFlag[18] = 0;
			idx = BYFindNextOptionItem3(10, 12);
			S2ItemFlag[idx] = 1;
			S2OldIdx = S2NewIdx = idx;
			break;

		case 10:
		case 11:
		case 12:
			S2ItemFlag[S2OldIdx] = 0;
			S2ItemFlag[13] = 1;
			S2OldIdx = S2NewIdx = 13;
			break;
		case 13:
		case 14:
			S2ItemFlag[S2OldIdx] = 0;
			idx = BYFindNextOptionItem3(19, 20);
			S2ItemFlag[idx] = 1;
			S2OldIdx = S2NewIdx = idx;
			DDtext= TRUE;
			bInVModeMenu = TRUE;
			break;
		case 19:
			S2ItemFlag[S2OldIdx] = 0;
			S2ItemFlag[20] = 1;
			S2OldIdx = S2NewIdx = 20;
			bInVModeMenu = FALSE;
			bInWSize = TRUE;
			tpmode = current_mode;
			break;
		case 20:
			S2ItemFlag[S2OldIdx] = 0;
			idx = BYFindNextOptionItem3(0, 2);
			S2ItemFlag[idx] = 1;
			S2OldIdx = S2NewIdx = idx;
			DDtext = FALSE;
			bInWSize = FALSE;
			tpsize = current_size;
			break;
		};
        //sndPlaySound(WrapSnd1, SND_ASYNC);
		break; // end of switch VK_DOWN

	case VK_LEFT:
		switch(S2OldIdx) {
		case 19:
			tpmode = (tpmode-1+total_modes) % total_modes;
			break;
		case 20:
			tpsize = (tpsize-1+4) % 4;
			break;
		case 0:
			S2ItemFlag[S2OldIdx] = 0;
			S2NewIdx = 2;
			S2ItemFlag[S2NewIdx] = 1;
			S2OldIdx = S2NewIdx;
			break;

		case 1:
		case 2:
		case 4:
		case 5:
		case 7:
		case 11:
		case 12:
		case 14:
         S2ItemFlag[S2OldIdx] = 0;
         S2NewIdx--;
         S2ItemFlag[S2NewIdx] = 1;
         S2OldIdx = S2NewIdx;
         break;

      case 6:
         if (hw3dacc == TRUE)
         {
            S2ItemFlag[S2OldIdx] = 0;
            S2NewIdx = 7;
            S2ItemFlag[S2NewIdx] = 1;
            S2OldIdx = S2NewIdx;
         }
         else
         {
            S2ItemFlag[S2OldIdx] = 0;
            S2NewIdx--;
            S2ItemFlag[S2NewIdx] = 1;
            S2OldIdx = S2NewIdx;
         }
         break;

		case 3:
         S2ItemFlag[S2OldIdx] = 0;
         S2NewIdx = 7;
         S2ItemFlag[S2NewIdx] = 1;
         S2OldIdx = S2NewIdx;
         break;

		case 8:
			YBControlSFX(2);
			break;

		case 9:  // lower MIDI volume
         if (MidValue==0)
			{
				break;
			}
         else
			if (!YBControlMID(2))    //left: if MidValue==0 then
         {
				if (MidSts == MID_PLAY)     //      if status == still play a midi
				{
					//YBStopDMidi(0);          //      then stop it.
					//YBQuitDMidi();
					//MidNewIdx = 99;
					//MidOldIdx = 99;
					YBPauseMidiPlay();
					MidSts = MID_SILENT;
				}
         }
			break;

		case 10:
         S2ItemFlag[S2OldIdx] = 0;
         S2NewIdx = 12;
         S2ItemFlag[S2NewIdx] = 1;
         S2OldIdx = S2NewIdx;
         break;

		case 13:
         S2ItemFlag[S2OldIdx] = 0;
         S2NewIdx = 14;
         S2ItemFlag[S2NewIdx] = 1;
         S2OldIdx = S2NewIdx;
         break;
		}
        //sndPlaySound(WrapSnd1, SND_ASYNC);			
		break;

	case VK_RIGHT:
		switch(S2OldIdx) {
		case 19:
			tpmode = (tpmode+1) % total_modes;
			break;
		case 20:
			tpsize = (tpsize+1) % 4;
			break;
		case 0:
		case 1:
		case 3:
		case 4:
		case 5:
		case 6:
		case 10:
		case 11:
		case 13:
			S2ItemFlag[S2OldIdx] = 0;
			S2NewIdx++;
			S2ItemFlag[S2NewIdx] = 1;
			S2OldIdx = S2NewIdx;
			break;

		case 2:
         S2ItemFlag[S2OldIdx] = 0;
         S2NewIdx = 0;
         S2ItemFlag[S2NewIdx] = 1;
         S2OldIdx = S2NewIdx;
         break;

		case 7:
         S2ItemFlag[S2OldIdx] = 0;
         if (hw3dacc == TRUE)
            S2NewIdx = 6;
         else
            S2NewIdx = 3;
         S2ItemFlag[S2NewIdx] = 1;
         S2OldIdx = S2NewIdx;
         break;

		case 12:
         S2ItemFlag[S2OldIdx] = 0;
         S2NewIdx = 10;
         S2ItemFlag[S2NewIdx] = 1;
         S2OldIdx = S2NewIdx;
         break;

		case 14:
         S2ItemFlag[S2OldIdx] = 0;
         S2NewIdx = 13;
         S2ItemFlag[S2NewIdx] = 1;
         S2OldIdx = S2NewIdx;
         break; 

		case 8:
			YBControlSFX(1);
			break;

		case 9: // increace midi volume
            
         if (MidValue==0 && MidSts==MID_SILENT) 
			{
				//YBCreateEvent();
				//YBSetupDMidi();
				//YBLoadDMidi(MIDFiles[7]);
				//YBSetLoopDMidi(TRUE);
				//YBControlMID(1);
				//YBPlayDMidi();
				YBResumeMidiPlay();

				MidOldIdx = MidNewIdx = 7;
				MidSts = MID_PLAY;
         } else 
				YBControlMID(1); 
			break;

		}
        //sndPlaySound(WrapSnd1, SND_ASYNC);			
		break;
  
	case VK_RETURN:
		sndPlaySound(WrapSnd1, SND_ASYNC);
		switch(S2OldIdx) {
		case 19:
			current_mode = tpmode;
			VM_W3D = d3dappi.Mode[inner_mode[current_mode]].w; 
			VM_H3D = d3dappi.Mode[inner_mode[current_mode]].h; 
			VM_BPP3D = d3dappi.Mode[inner_mode[current_mode]].bpp;  
         if (VM_W3D != 640 || VM_BPP3D != 16) 
         {
            if (sStretch.bWillStretch)
            {
               sStretch.bWillStretch = FALSE;
               VSize = 1;
            }
         }
         else
         {
            if (VSize == 1)
            {
               sStretch.bWillStretch = TRUE;
               VSize = 4;
            }
         }
			BYOBGetBitmapPath(VM_W3D);
			break;
		case 20:
			current_size = tpsize;
			if (current_size>=0 && current_size<=3)
				VSize = current_size+1;
         if (current_size == 0 && sStretch.bCanStretch && VM_W3D == 640 && VM_BPP3D == 16)
         {
            VSize = 4;
            sStretch.bWillStretch = TRUE;
         }
         else
         {
            sStretch.bWillStretch = FALSE;
         }
			BYOBGetBitmapPath(VM_W3D);
			break;
		case 0:
		case 1:
		case 2:
			idx = BYFindNextOptionItem3(0, 2);
			S2ItemFlag[idx] = 0;
			S3ItemFlag[idx] = 0;
			S2ItemFlag[S2NewIdx] = 1;
			S3ItemFlag[S2NewIdx] = 1;
			SysDifficulty = S2OldIdx+1;
			break;
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			idx = BYFindNextOptionItem3(3, 7);
			S2ItemFlag[idx] = 0;
			S3ItemFlag[idx] = 0;
			S2ItemFlag[S2NewIdx] = 1;
			S3ItemFlag[S2NewIdx] = 1;
			SysWatchyStyle = S2OldIdx-2;
			detail = (unsigned char)SysWatchyStyle;
			newland = 1;
			break;
		case 10:
		case 11:
		case 12:
			idx = BYFindNextOptionItem3(10, 12);
			S2ItemFlag[idx] = 0;
			S3ItemFlag[idx] = 0;
			S2ItemFlag[S2NewIdx] = 1;
			S3ItemFlag[S2NewIdx] = 1;
			break;
		};
        //sndPlaySound(WrapSnd1, SND_ASYNC);
		j = 1;
		break; 
	}

	if (j>0) 
		return (S2NewIdx+j);
	else  
		return j;
}

void YBControlSFXwMouse(short x)
{
	int KnobPos;	
	
	if (x<=BarStartP || x>=(BarLength+BarStartP)) 
	{
	    return;
	}
	
	KnobPos = x;
	O2OptionMenuMap.des[17][0] = KnobPos;
	O2OptionMenuMap.des[15][0] = KnobPos;
	SFXValue = (KnobPos-BarStartP)*100/BarLength;
	if (SFXValue>100) SFXValue = 100;
	if (SFXValue<0) SFXValue = 0;
	if (SFXValue==0) YBSndSilence=TRUE;
	else YBSndSilence=FALSE;
	MaxSFXValue = (float)SFXValue*(float)4.0;		     
}

void YBControlMIDwMouse(short x)
{
	int KnobPos;	
	
	if (x<=BarStartP || x>=(BarLength+BarStartP)) 
	    return;

	KnobPos = O2OptionMenuMap.des[18][0];

	// raise MIDI volume
	if (KnobPos==BarStartP && x>KnobPos) 
	{
		if (MidValue==0 && MidSts==MID_SILENT) 
		{
			KnobPos = x;
			if (KnobPos<BarStartP)
				KnobPos = BarStartP;
			if (KnobPos>(BarLength+BarStartP))
				KnobPos = (BarLength+BarStartP);
			O2OptionMenuMap.des[18][0] = KnobPos;
			O2OptionMenuMap.des[16][0] = KnobPos;
			MidValue = (KnobPos-BarStartP)*100/BarLength;
			if (MidValue>100) MidValue = 100;
			if (MidValue<0) MidValue = 0;
			//YBSetupDMidi();
			//YBCreateEvent();
			//YBLoadDMidi(MIDFiles[7]);
			//YBPlayDMidi();
			YBResumeMidiPlay();
			YBSetMidiVolume((MidValue*10));
			//YBSetLoopDMidi(TRUE);
			//MidOldIdx = MidNewIdx = 7;
			MidSts = MID_PLAY;
			return;
        }  
	}

	// lower MIDI volume
	if (x<=BarStartP && MidValue!=0) 
	{
		KnobPos = x;
		if (KnobPos<BarStartP)
			KnobPos = BarStartP;
		if (KnobPos>(BarLength+BarStartP))
			KnobPos = (BarLength+BarStartP);
		O2OptionMenuMap.des[18][0] =	KnobPos;
		O2OptionMenuMap.des[16][0] = KnobPos;
		MidValue = (KnobPos-BarStartP)*100/BarLength;
		if (MidValue>100) MidValue = 100;
		if (MidValue<0) MidValue = 0;
		if (MidSts == MID_PLAY) 
		{   
			YBPauseMidiPlay();
			//YBStopDMidi(0);          
			//YBQuitDMidi();
			//MidNewIdx = 99;
			//MidOldIdx = 99;
			MidSts = MID_SILENT;
		}
		return;
	}

	KnobPos = x;
	if (KnobPos<BarStartP)
		KnobPos = BarStartP;
	if (KnobPos>(BarLength+BarStartP))
		KnobPos = (BarLength+BarStartP);

	O2OptionMenuMap.des[18][0] = KnobPos;
	O2OptionMenuMap.des[16][0] = KnobPos;
	MidValue = (KnobPos-BarStartP)*100/BarLength;
	if (MidValue>100) MidValue = 100;
	if (MidValue<0) MidValue = 0;
	YBSetMidiVolume((MidValue*10));

}

short YBDecideOptionMenuFromMouse(void)
{
	POINT p;
	int i, j, k, idx;
	short row, col, s, e;
	char method;
	short retval = 0;

	p.x = (LONG) di.GetMsX();
	p.y = (LONG) di.GetMsY();
	
	for (i=0; i<17; i++) 
	{
	    if (PtInRect(&(OptionMenuRect[i]), p)) break;
	}


	if (bInVModeMenu && total_modes)
	{
		for (j=0; j<total_modes; j++)
		{
			if (PtInRect(&(ModeSizeAreas[j]), p)) 
			{
				tpmode = j;
				current_mode = tpmode;
				VM_W3D = d3dappi.Mode[inner_mode[current_mode]].w; 
				VM_H3D = d3dappi.Mode[inner_mode[current_mode]].h; 
				VM_BPP3D = d3dappi.Mode[inner_mode[current_mode]].bpp;  
            if (VM_W3D != 640) 
            {
               if (sStretch.bWillStretch)
               {
                  sStretch.bWillStretch = FALSE;
                  VSize = 1;
               }
            }
            else
            {
               if (VSize == 1)
               {
                  sStretch.bWillStretch = TRUE;
                  VSize = 4;
               }
            }
				BYOBGetBitmapPath(VM_W3D);
				break;
			}
		}
	}

	if (bInWSize)
	{
		for (k=0; k<4; k++)
		{
			if (PtInRect(&(ModeSizeAreas[k]), p)) 
			{
				tpsize = k;
				current_size = tpsize;
				if (current_size>=0 && current_size<=3)
					VSize = current_size+1;			
            if (current_size == 0 && sStretch.bCanStretch && VM_W3D == 640)
            {
               VSize = 4;
               sStretch.bWillStretch = TRUE;
            }
            else
            {
               sStretch.bWillStretch = FALSE;
            }
				BYOBGetBitmapPath(VM_W3D);
				break;
			}
		}
	}

	if (i<0 || i>16)
	{
        return 0;
	}

	if (S2OldIdx>16)
		row = YBFindMndIdx(S2OldIdx-4);
	else
		row = YBFindMndIdx(S2OldIdx);
	col = YBFindMndIdx(i);

	method = MethodTable[row][col];

	switch(method) 
	{
	case 'A':
		YBFindStartNEnd(i, &s, &e);
		idx = YBFindNextOptionItem3(s, e);
		S2ItemFlag[idx] = 0;
		S3ItemFlag[idx] = 0;
		S2ItemFlag[i] = 1;
		S3ItemFlag[i] = 1;
		S2OldIdx = S2NewIdx = i;
		if (i>=0 && i<=2) SysDifficulty = (i+1);
		if (i>=3 && i<=7) 
		{
         SysWatchyStyle = (i-2);
			if (hw3dacc == TRUE && SysWatchyStyle < 4)
            SysWatchyStyle = 4;
			detail = (unsigned char)SysWatchyStyle;
			newland = 1;
		}
		if (i>=10 && i<=12)
         retval = i+1;
		break;
	case 'B':
		S2ItemFlag[S2OldIdx]=0;
		YBFindStartNEnd(i, &s, &e);
		idx = YBFindNextOptionItem3(s, e);
		S3ItemFlag[idx] = 0;
		S2ItemFlag[i] = 1;
		S3ItemFlag[i] = 1;
		S2OldIdx = S2NewIdx = i;
		break;
	case 'C':
		S2ItemFlag[S2OldIdx] = 0;
		S2ItemFlag[i] = 1;
		S2OldIdx = S2NewIdx = i;
		break;
	case 'D':
		if (i==8) 
		{
			S2ItemFlag[15] = 0;
			S2ItemFlag[16] = 1;
			S2ItemFlag[17] = 1;
			S2ItemFlag[18] = 0;
			YBControlSFXwMouse((short)p.x);
			break;
		}
		if (i==9) 
		{
			S2ItemFlag[15] = 1;
			S2ItemFlag[16] = 0;
			S2ItemFlag[17] = 0;
			S2ItemFlag[18] = 1;
			YBControlMIDwMouse((short)p.x);
			break;
		}
		break;
	case 'E':
		retval = (i+1);
		break;
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
		break;
	}
	sndPlaySound(WrapSnd1, SND_ASYNC);

	return (retval);
}

void YBSelectOptionMenuFromMouse()
{
	POINT p;
	int i,j,k; 
	short row, col;	 
	char method;

	p.x = (LONG) di.GetMsX();
	p.y = (LONG) di.GetMsY();
	
	for (i=0; i<17; i++) 
	{
	    if (PtInRect(&(OptionMenuRect[i]), p)) break;
	}

	if (bInVModeMenu && total_modes)
	{
		for (j=0; j<total_modes; j++)
		{
			if (PtInRect(&(ModeSizeAreas[j]), p)) 
			{
				tpmode = j;
				break;
			}
		}
	}

	if (bInWSize)
	{
		for (k=0; k<4; k++)
		{
			if (PtInRect(&(ModeSizeAreas[k]), p)) 
			{
				tpsize = k;
				break;
			}
		}
	}

	if (i<0 || i>16)
	{
        return;
	}
   if (hw3dacc && (i>=3 && i <= 5))
      return;

	if (S2OldIdx>16)
		row = YBFindMndIdx(S2OldIdx-4);
	else
		row = YBFindMndIdx(S2OldIdx);
	col = YBFindMndIdx(i);

	method = MethodTable[row][col];

	switch(method) {
	case 'A':
		S2ItemFlag[S2OldIdx] = 0;
		S2ItemFlag[i] = 1;
		S2OldIdx = S2NewIdx = i;
		break;
	case 'B':
		S2ItemFlag[S2OldIdx]=0;
		S2ItemFlag[i] = 1;
		S2OldIdx = S2NewIdx = i;
		break;
	case 'C':
		S2ItemFlag[S2OldIdx] = 0;
		S2ItemFlag[i] = 1;
		S2OldIdx = S2NewIdx = i;
		break;
	case 'D':
		if (!di.MsLBtnDown()) 
		{
			S2ItemFlag[15] = 1;    // idx 13, 14 = turn off
			S2ItemFlag[16] = 1;
			S2ItemFlag[17] = 0;    // idx 15, 16 = turn on
			S2ItemFlag[18] = 0;
			break;
		}
		if (i==8) 
		{
			S2ItemFlag[15] = 0;
			S2ItemFlag[16] = 1;
			S2ItemFlag[17] = 1;
			S2ItemFlag[18] = 0;
			YBControlSFXwMouse((short)p.x);
			break;
		}
		if (i==9) 
		{
			S2ItemFlag[15] = 1;
			S2ItemFlag[16] = 0;  // 14 = turn on
			S2ItemFlag[17] = 0;
			S2ItemFlag[18] = 1;  // 16 = turn on
			YBControlMIDwMouse((short)p.x);      
			break;
		}
		break;
	case 'E':
		break;
	case 'F':
		i += 4;
		S2ItemFlag[S2OldIdx] = 0;
		S2ItemFlag[i] = 1;
		S2OldIdx = S2NewIdx = i;
		DDtext = TRUE;
		bInVModeMenu = TRUE;
		break;
	case 'G':
		i += 4;
		S2ItemFlag[S2OldIdx] = 0;
		S2ItemFlag[i] = 1;
		S2OldIdx = S2NewIdx = i;
		DDtext = TRUE;
		bInWSize = TRUE;
		break;
	case 'H':
		i += 4;
		S2ItemFlag[S2OldIdx] = 0;
		S2ItemFlag[15] = 1;
		S2ItemFlag[17] = 0;
		S2ItemFlag[i] = 1;
		S2OldIdx = S2NewIdx = i;
		DDtext = TRUE;
		bInVModeMenu = TRUE;
		break;
	case 'I':
		i += 4;
		S2ItemFlag[S2OldIdx] = 0;
		S2ItemFlag[15] = 1;
		S2ItemFlag[17] = 0;
		S2ItemFlag[i] = 1;
		S2OldIdx = S2NewIdx = i;
		DDtext = TRUE;
		bInWSize = TRUE;
		break;
	case 'J':
		i += 4;
		S2ItemFlag[S2OldIdx] = 0;
		S2ItemFlag[16] = 1;
		S2ItemFlag[18] = 0;
		S2ItemFlag[i] = 1;
		S2OldIdx = S2NewIdx = i;
		DDtext = TRUE;
		bInVModeMenu = TRUE;
		break;
	case 'K':
		i += 4;
		S2ItemFlag[S2OldIdx] = 0;
		S2ItemFlag[16] = 1;
		S2ItemFlag[18] = 0;
		S2ItemFlag[i] = 1;
		S2OldIdx = S2NewIdx = i;
		DDtext = TRUE;
		bInWSize = TRUE;
		break;
	case 'L':
		S2ItemFlag[S2OldIdx] = 0;
		S2ItemFlag[i] = 1;
		S2OldIdx = S2NewIdx = i;
		DDtext = FALSE;
		bInVModeMenu = FALSE;
		tpmode = current_mode;
		break;
	case 'M':
		S2ItemFlag[S2OldIdx] = 0;
		S2ItemFlag[i] = 1;
		S2OldIdx = S2NewIdx = i;
		DDtext = FALSE;
		bInWSize = FALSE;
		tpsize = current_size;
		break;
	case 'N':
		i += 4;
		S2ItemFlag[S2OldIdx] = 0;
		S2ItemFlag[i] = 1;
		S2OldIdx = S2NewIdx = i;
		bInVModeMenu = FALSE;
		bInWSize = TRUE;
		tpmode = current_mode;
		break;
	case 'O':
		i += 4;
		S2ItemFlag[S2OldIdx] = 0;
		S2ItemFlag[i] = 1;
		S2OldIdx = S2NewIdx = i;
		bInWSize = FALSE;
		bInVModeMenu = TRUE;
		tpsize = current_size;
		break;
	case 'P':
		S2ItemFlag[S2OldIdx] = 0;
		S2ItemFlag[17] = 1;
		S2ItemFlag[15] = 0;
		S2ItemFlag[i] = 1;
		S2OldIdx = S2NewIdx = i;
		bInVModeMenu = FALSE;
		tpmode = current_mode;
		break;
	case 'Q':
		S2ItemFlag[S2OldIdx] = 0;
		S2ItemFlag[16] = 0;
		S2ItemFlag[18] = 1;
		S2ItemFlag[i] = 1;
		S2OldIdx = S2NewIdx = i;
		bInVModeMenu = FALSE;
		tpmode = current_mode;
		break;
	case 'R':
		S2ItemFlag[S2OldIdx] = 0;
		S2ItemFlag[17] = 1;
		S2ItemFlag[15] = 0;
		S2ItemFlag[i] = 1;
		S2OldIdx = S2NewIdx = i;
		bInWSize = FALSE;
		tpsize = current_size;
		break;
	case 'S':
		S2ItemFlag[S2OldIdx] = 0;
		S2ItemFlag[16] = 0;
		S2ItemFlag[18] = 1;
		S2ItemFlag[i] = 1;
		S2OldIdx = S2NewIdx = i;
		bInWSize = FALSE;
		tpsize = current_size;
		break;
	}
}

// OPTION MENU MAIN FUNCTIONS
BOOL BYShowOptionMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_OPTION_MENU);
   int idx;

	di.TurnOnMsCursor(TRUE);

	BYLoadOverlay(1, BmpFile[OptionMenuBackground]);
	BYLoadOverlay(2, BmpFile[OptionMenuForeground]);
	BYSetO2OptionMenuF();
	BYSaveRestoreS2Idx(0);       // restore S2NewIdx, S2OldIdx value
   for (idx=3;idx<=7;idx++)
      S3ItemFlag[idx] = (idx==(detail+2));

	KnobLength = 7;
	BarLength  = 84 - KnobLength;
	BarStartP  = 311;
	O2OptionMenuMap.des[17][0] = 
      O2OptionMenuMap.des[15][0] = 
      (BarLength*SFXValue/100)+BarStartP;
	O2OptionMenuMap.des[16][0] = 
      O2OptionMenuMap.des[18][0] = 
      (BarLength*MidValue/100)+BarStartP;

	BYDisplayText = ShowScreenSettings;
	SetShowScreenPara();
	BYMouseHandler[pg_SHOW_OPTION_MENU] = BYMsOptionMenu;
	
	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYKdOptionMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int retval;

   ISKEYDOWN(msg);
	ISPAGE(pg_SHOW_OPTION_MENU);

	if (msg==WM_CHAR)
	{
		return FALSE;
	}

		retval=BYSelectOptionMenuFromKBD(wParam);
		
		switch(retval) {
		case PG_BACK:
			BYSaveRestoreS2Idx(1);
			BYSetPrePageSwitch(Page, pg_SHOW_MAIN_MENU); 
			Page = pg_SHOW_MAIN_MENU;
			PostMessage(win, WM_COMMAND, Page, 0L);
			break;
		case 11:
			BYSetPrePageSwitch(Page, pg_SHOW_JOYSKCFG); 
			BYSaveRestoreS2Idx(1);
			Page = pg_SHOW_JOYSKCFG;
			PostMessage(win, WM_COMMAND, Page, 0L);
			break;
		case 12:
			BYSetPrePageSwitch(Page, pg_SHOW_MOUSECFG); 
			BYSaveRestoreS2Idx(1);
			Page = pg_SHOW_MOUSECFG;
			PostMessage(win, WM_COMMAND, Page, 0L);
			break;
		case 13:
        BYSaveRestoreS2Idx(1);
        Page = pg_SHOW_KBD_MENU;
        PostMessage(win, WM_COMMAND, Page, 0L);
        break;
		case 14:
			BYSetPrePageSwitch(Page, pg_SHOW_LOAD_MENU); 
			BYSaveRestoreS2Idx(1);
			Page = pg_SHOW_LOAD_MENU;
			PostMessage(win, WM_COMMAND, Page, 0L);
			break;
		case 15:
			BYSetPrePageSwitch(Page, pg_SHOW_SAVE_MENU); 
			BYSaveRestoreS2Idx(1);
			Page = pg_SHOW_SAVE_MENU;
			PostMessage(win, WM_COMMAND, Page, 0L);
			break;
		} 
	
	return TRUE;

exit_with_false:
	return FALSE;
}


BOOL BYMsOptionMenu(HWND win)
{
	short retval;

	ISPAGE(pg_SHOW_OPTION_MENU);

	switch(msact) 
	{
	case WP_MOUSEMOVE:
		YBSelectOptionMenuFromMouse();
		break;
	case WP_LBUTTONDOWN:
		retval = YBDecideOptionMenuFromMouse();
		if (retval==11) 
		{
			BYSetPrePageSwitch(Page, pg_SHOW_JOYSKCFG); 
			BYSaveRestoreS2Idx(1);
			Page = pg_SHOW_JOYSKCFG;
			PostMessage(win, WM_COMMAND, Page, 0L);
			break;
		} 
		else
		if (retval==12) 
		{
			BYSetPrePageSwitch(Page, pg_SHOW_MOUSECFG); 
			BYSaveRestoreS2Idx(1);
			Page = pg_SHOW_MOUSECFG;
			PostMessage(win, WM_COMMAND, Page, 0L);
			break;
        } 
		else
        if (retval==13) {
			BYSaveRestoreS2Idx(1);
			Page = pg_SHOW_KBD_MENU;
			PostMessage(win, WM_COMMAND, Page, 0L);
			break;
        } 
		else
        if (retval==14) 
		{
			BYSetPrePageSwitch(Page, pg_SHOW_LOAD_MENU); 
			BYSaveRestoreS2Idx(1);
			Page = pg_SHOW_LOAD_MENU;
			PostMessage(win, WM_COMMAND, Page, 0L);
			break;
        } 
		else
		if (retval==15) 
		{
			BYSetPrePageSwitch(Page, pg_SHOW_SAVE_MENU); 
			BYSaveRestoreS2Idx(1);
			Page = pg_SHOW_SAVE_MENU;
			PostMessage(win, WM_COMMAND, Page, 0L);
			break;
        }    
        break;
	}

	return TRUE;

exit_with_false:
	return FALSE;
}
// OPTION MENU: ENDING

// LOAD MENU:  BEGINNING
// LOAD MENU:  SUB_FUNCTIONS
void BYSetO2LoadMenuF(void)
{
    S2xy  = &(O2LoadMenuMap.des[0][0]);
    S2rect = &(O2LoadMenuMap.src[0]);
    S2TotalItems = O2LoadMenuMap.titem;
	S2ItemFlag = &(O2LoadMenuMap.flag[0]);
	for (short i=0; i<S2TotalItems; i++)
	{
		S2ItemFlag[i] = 0;
	}
	S2ItemFlag[0] = 1;
	S2OldIdx = S2NewIdx = 0;
	S2ItemFlag[10] = 1;
	S2ItemFlag[11] = 0;
	TotalString = O2LoadMenuMap.tstring;
}

void BYSetLoadText(char newver[])
{   
    short i;

    YBLoadAllUserRecord(newver);

    for (i=0; i<TotalString; i++) {
        TextPtr[i] = urec[i].name;
        TextPos[i] = &(O2LoadMenuMap.tpos[i][0]);
    }
    TextCol = &(O2LoadMenuMap.tcol[0]);
}

int BYMsChooseLoadMenu(void)
{
	POINT p;
	int i;

	p.x = (LONG) di.GetMsX();
	p.y = (LONG) di.GetMsY();

	for (i=0; i<10; i++) {
	    if (PtInRect(&(MsLoadNSaveMenuRect[i]), p)) break;
	}
	if (i<10 && i>=0) {
		S2NewIdx = i;
		if (S2OldIdx!=S2NewIdx) {
			S2ItemFlag[S2NewIdx] = 1;
			S2ItemFlag[S2OldIdx] = 0;
			S2OldIdx = S2NewIdx;
            //sndPlaySound(WrapSnd1, SND_ASYNC);
		}
		if (msact==WP_LBUTTONDOWN)
		{
			sndPlaySound(WrapSnd1, SND_ASYNC);
			return (S2NewIdx+1);
		}

	}
	return 0;
}

int BYSelectLoadMenuFromKBD(WORD wparam)
{
	int j=0;

    switch(wparam) {
	case VK_ESCAPE:
		j = PG_BACK;
		break;
	case VK_LEFT:
	case VK_UP:
		S2NewIdx--;
		S2NewIdx = (10+S2NewIdx) % 10;
		break;
	case VK_RIGHT:
	case VK_DOWN:
		S2NewIdx++;
		S2NewIdx = S2NewIdx%10;
		break;

	case VK_RETURN:
        //sndPlaySound(WrapSnd1, SND_ASYNC);
	    j = 1;
		break;
	}
	if (S2OldIdx!=S2NewIdx) {
		S2ItemFlag[S2NewIdx] = 1;
		S2ItemFlag[S2OldIdx] = 0;
		S2OldIdx=S2NewIdx;
        //sndPlaySound(WrapSnd1, SND_ASYNC);
	}
	if (j>0) 
		return (S2NewIdx+j);
	else
		return j;
}

// LOAD MENU MAIN_FUNCTIONS
BOOL BYShowLoadMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_LOAD_MENU);

	BYLoadOverlay(1, BmpFile[LoadSaveMenuBackground]);
	BYLoadOverlay(2, BmpFile[LoadSaveMenuForeground]);
	BYSetO2LoadMenuF();
	BYSetLoadText(GameVersion);
	BYChooseTextSurface(0);		// choose back surface
	BYDisplayText = BYDisplayStr;
	EditMode = FALSE;
	DDtext = TRUE;

	BYMouseHandler[pg_SHOW_LOAD_MENU] = BYMsLoadMenu;

	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYKdShowLoadMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	short retval;

   ISKEYDOWN(msg);
	ISPAGE(pg_SHOW_LOAD_MENU);

	if (msg==WM_CHAR)
	{
		return FALSE;
	}

    retval = BYSelectLoadMenuFromKBD(wParam);
	if (retval==PG_BACK)
	{
		BYSetPrePageSwitch(Page, pg_SHOW_OPTION_MENU); 	
        DDtext  = FALSE;
        Page = pg_SHOW_OPTION_MENU;
        PostMessage(win, WM_COMMAND, Page, 0L);
	}
	else
    if (retval) 
	{
        YBLoadUserRecord(retval, GameVersion);
        YBConfirmLoad(retval);
        DDtext  = FALSE;
		BYSetPrePageSwitch(Page, pg_SHOW_OPTION_MENU); 	
        Page = pg_SHOW_OPTION_MENU;
        PostMessage(win, WM_COMMAND, Page, 0L);
    }
	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYMsLoadMenu(HWND win)
{
	short retval;

	ISPAGE(pg_SHOW_LOAD_MENU);

	switch(msact) 
	{
	case WP_MOUSEMOVE:
        BYMsChooseLoadMenu();
		break;
	case WP_LBUTTONDOWN:
		retval = BYMsChooseLoadMenu();
        if (retval)
		{
			YBLoadUserRecord(retval, GameVersion);
			YBConfirmLoad(retval);
			DDtext  = FALSE;
			BYSetPrePageSwitch(Page, pg_SHOW_OPTION_MENU); 	
			Page = pg_SHOW_OPTION_MENU;
			PostMessage(win, WM_COMMAND, Page, 0L);
        }
        break;
    }
	return TRUE;

exit_with_false:
	return FALSE;
}
// LOAD MENU: ENDING

// SAVE MENU: BEGINNING
// SAVE MENU SUBFUNCTIONS
void BYSetO2SaveMenuF(void)
{
    S2xy  = &(O2LoadMenuMap.des[0][0]);
    S2rect = &(O2LoadMenuMap.src[0]);
    S2TotalItems = O2LoadMenuMap.titem;
	S2ItemFlag = &(O2LoadMenuMap.flag[0]);
	for (short i=0; i<S2TotalItems; i++)
	{
		S2ItemFlag[i] = 0;
	}
	S2ItemFlag[0] = 1;
	S2OldIdx = S2NewIdx = 0;
    S2ItemFlag[10] = 0;  // turn on SAVE light
	S2ItemFlag[11] = 1;
	TotalString = O2LoadMenuMap.tstring;
}

void BYSetSavePara(void)
{
    StrIdx = 0;
    OldTextPtr = urec[0].name;
    strcpy(YBLineBuffer, "");
    strcpy(YBLineBuffer, TextPtr[StrIdx]);
    OldTextPtr = TextPtr[StrIdx];
    TextPtr[StrIdx] = YBLineBuffer;
    StrLen = lstrlen(YBLineBuffer);
}

short BYLineEditor(HWND win, UINT msg, WPARAM wparam)
{
	short retval=0;
	UINT ccode;
    
	if (msg==WM_KEYDOWN) 
	{
		switch(wparam) 
		{
		case VK_ESCAPE:
			retval = PG_BACK;
			break;
		case VK_SPACE:
			if (ChrIdx<(LINE_BUFFER_SIZE-2))
			{
				YBLineBuffer[ChrIdx++] = (char)wparam;
				YBLineBuffer[ChrIdx] = 0;
			}
         break;
		case VK_UP:
         TextPtr[StrIdx] = OldTextPtr;
         StrIdx--;
         StrIdx = (10+StrIdx)%10;
         strcpy(YBLineBuffer, "");
         strcpy(YBLineBuffer, TextPtr[StrIdx]);
         OldTextPtr = TextPtr[StrIdx];
         TextPtr[StrIdx] = YBLineBuffer;
         StrLen = lstrlen(YBLineBuffer);
         ChrIdx = 0;
         S2NewIdx--;
         S2NewIdx = (10+S2NewIdx) % 10;
         break;
		case VK_DOWN:
         TextPtr[StrIdx] = OldTextPtr;
         StrIdx++;
         StrIdx = StrIdx%10;
         strcpy(YBLineBuffer, "");
         strcpy(YBLineBuffer, TextPtr[StrIdx]);
         OldTextPtr = TextPtr[StrIdx];
         TextPtr[StrIdx] = YBLineBuffer;
         StrLen = lstrlen(YBLineBuffer);
         ChrIdx = 0;
         S2NewIdx++;
         S2NewIdx = S2NewIdx % 10;
         break;
		case VK_RETURN:
         strcpy(urec[StrIdx].name, YBLineBuffer);
         //sndPlaySound(WrapSnd1, SND_ASYNC);
         retval = 1;
         //save now
         break;

		case VK_LEFT:
		case VK_BACK:
         if (ChrIdx>0) 
			{
				ChrIdx--;
			}
			break;
		case VK_RIGHT:
			if (ChrIdx<(LINE_BUFFER_SIZE-2) && ChrIdx<lstrlen(YBLineBuffer))
			{
				ChrIdx++;
			}
         break;
		default:
			ccode = MapVirtualKey(wparam, 2);
			if (isalnum(ccode) && (ChrIdx<(LINE_BUFFER_SIZE-2))) 
			{
				YBLineBuffer[ChrIdx++] = (char)wparam;
				YBLineBuffer[ChrIdx] = 0;
			}
			break;
		}
	}; // end if msg==WM_KEYDOWN 

    
	if (S2OldIdx!=S2NewIdx) 
	{
		S2ItemFlag[S2NewIdx] = 1;
		S2ItemFlag[S2OldIdx] = 0;
		S2OldIdx=S2NewIdx;
	}
	// Now it's WM_CHAR msg
	//InvalidateRect(win, NULL, TRUE);
	if (retval>0) 
	{
		return (retval+StrIdx);
	}
	else
	{
		return retval;
	}
}

int BYMsChooseSaveMenu(void)
{
	POINT p;
	int i;

	p.x = (LONG) di.GetMsX();
	p.y = (LONG) di.GetMsY();

    	
	for (i=0; i<10; i++) {
	    if (PtInRect(&(MsLoadNSaveMenuRect[i]), p)) break;
	}
	if (i<10 && i>=0) {
		S2NewIdx = i;
		if (S2OldIdx!=S2NewIdx) {
			S2ItemFlag[S2NewIdx] = 1;
			S2ItemFlag[S2OldIdx] = 0;
            TextPtr[S2OldIdx] = OldTextPtr;
            StrIdx = S2NewIdx;
            strcpy(YBLineBuffer, "");
            strcpy(YBLineBuffer, TextPtr[StrIdx]);
            OldTextPtr = TextPtr[StrIdx];
            TextPtr[StrIdx] = YBLineBuffer;
            StrLen = lstrlen(YBLineBuffer);
            ChrIdx = 0;
			S2OldIdx = S2NewIdx;
            //sndPlaySound(WrapSnd1, SND_ASYNC);
		}
		if (msact==WP_LBUTTONDOWN)
		{
			strcpy(urec[StrIdx].name, YBLineBuffer);
			sndPlaySound(WrapSnd1, SND_ASYNC);
			return (StrLen+1);
		}
	}
	return 0;
}

// SAVE MENU MAIN FUNCTIONS
BOOL BYShowSaveMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_SAVE_MENU);

	BYLoadOverlay(1, BmpFile[LoadSaveMenuBackground]);
	BYLoadOverlay(2, BmpFile[LoadSaveMenuForeground]);
	BYSetO2SaveMenuF();
	BYSetLoadText(GameVersion); // ??????????????????
	BYSetSavePara();
	BYChooseTextSurface(0);		// choose back surface
    
	BYDisplayText = BYDisplayStr;
	EditMode = TRUE;
	DDtext = TRUE;

	BYMouseHandler[pg_SHOW_SAVE_MENU] = BYMsSaveMenu;

	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYKdShowSaveMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	short retval;

   ISKEYDOWN(msg);
	ISPAGE(pg_SHOW_SAVE_MENU);

	retval = BYLineEditor(win, msg, wParam);
	if (retval==PG_BACK)
	{
		BYSetPrePageSwitch(Page, pg_SHOW_OPTION_MENU); 	
		DDtext  = FALSE;
		EditMode = FALSE;
		Page = pg_SHOW_OPTION_MENU;
		PostMessage(win, WM_COMMAND, Page, 0L);
	}
	else
	if (retval) 
	{
		YBSaveUserRecord(retval, GameVersion);

		BYSetPrePageSwitch(Page, pg_SHOW_OPTION_MENU); 	
		DDtext  = FALSE;
		EditMode = FALSE;
		Page = pg_SHOW_OPTION_MENU;
		PostMessage(win, WM_COMMAND, Page, 0L);
	};
	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYMsSaveMenu(HWND win)
{
	int retval;

	ISPAGE(pg_SHOW_SAVE_MENU);

	switch(msact) 
	{
	case WP_MOUSEMOVE:
		BYMsChooseSaveMenu();
		break;
	case WP_LBUTTONDOWN:
		if (retval=BYMsChooseSaveMenu())
		{
			YBSaveUserRecord(retval, GameVersion);

			BYSetPrePageSwitch(Page, pg_SHOW_OPTION_MENU); 	
			DDtext  = FALSE;
			EditMode = FALSE;
			Page = pg_SHOW_OPTION_MENU;
			PostMessage(win, WM_COMMAND, Page, 0L);
		}
		break;
	}
	return TRUE;

exit_with_false:
	return FALSE;
}
// SAVE MENU: ENDING

// MOUSE CONFIGURATION: BEGINNING
// MOUES CONFIGURATION: SUB FUNCTIONS
/*
BOOL BYTimeShowMouseOrConfigure(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	IS_WRAPPER_TIMER(wParam);

	KillTimer(win, nTimer);
	Page = pg_SHOW_OPTION_MENU;
	PostMessage(win, WM_COMMAND, Page, 0L);
	return TRUE;

exit_with_false:
	return FALSE;
}*/

// MOUSE CONFIGURATION: MAIN FUNCTIONS
BOOL BYShowMouseConFig(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_MOUSECFG);

	di.TurnOnMsCursor(FALSE);

	BYLoadOverlay(1, BmpFile[MouseConfiguration]);
	BYSetO1MainMenuB();
	BYDisplayText = ShowMouseSettings;
	DDtext = TRUE;
	BYKbrdHandler[pg_SHOW_MOUSECFG] = BYKdChooseMouseCfg;

	return TRUE;

exit_with_false:
	return FALSE;
}
// MOUSE CONFIGURATION: ENDING

// JOYSTICK CONFIGURATION: BEGINNING
// JOYSTICK CONFIGURATION: MAIN FUNCTIONS
BOOL BYShowJoystickConFig(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_JOYSKCFG);

	di.TurnOnMsCursor(FALSE);

	if (JoyStickType==YB_SIDEWINDER_3D_PRO)
	{
		BYLoadOverlay(1, "wr134.bmp");
	}
	else
	if (JoyStickType==YB_SIDEWINDER_GAMEPAD)
	{
		BYLoadOverlay(1, "wr135.bmp");
	}
	else
	if (JoyStickType==YB_CREATIVE_GAMEPAD)
	{
		BYLoadOverlay(1, "wr137.bmp");
	}
	else
	if (JoyStickType==YB_GRAVIS_GRIP)
	{
		BYLoadOverlay(1, "wr138.bmp");
	}
	else
	if (JoyStickType==YB_GENERIC)
	{
		if (bd0<=2)
			BYLoadOverlay(1, "wr127.bmp");
		else if (bd0>=4 && bd0<=8)
			BYLoadOverlay(1, "wr127.bmp");
		else 
			BYLoadOverlay(1, "wr136.bmp");
	}
   else if (!bFindJoystick)
   {
      BYLoadOverlay(1, "wr139.bmp");         // No joystick
   }
	
	BYSetO1MainMenuB();
	if (!((JoyStickType==YB_SIDEWINDER_3D_PRO) ||
         (JoyStickType==YB_GRAVIS_GRIP) || 
         (JoyStickType==YB_CREATIVE_GAMEPAD) || 
	     (JoyStickType==YB_SIDEWINDER_GAMEPAD)))
	{
	}
	BYDisplayText = ShowJoystkSettings;
	DDtext = TRUE;
	BYKbrdHandler[pg_SHOW_JOYSKCFG] = BYKdChooseJoystkCfg;
	return TRUE;

exit_with_false:
	return FALSE;
}
// JOYSTICK CONFIGURATION: ENDING

BOOL BYMidiCenter(void)
{

	if(!bMidiFlag)
		return FALSE;

	if (MidSts == MID_SILENT) 
	{
		return FALSE;
	}

	if (MidCmd == MID_PLAY) 
	{
		if (MidSts == MID_PLAY && MidOldIdx==MidNewIdx) 
		{
         return FALSE;
		} 
		else 
		{
         if (MidSts == MID_PLAY && MidOldIdx!=MidNewIdx) 
			{
				YBStopDMidi(MAKEWPARAM(0,MSTREAM_STOPF_NOREOPEN));
				//YBQuitDMidi();
         } 
         //YBCreateEvent();
         //YBSetupDMidi();
         YBLoadDMidi(MIDFiles[MidNewIdx]);
         YBSetLoopDMidi(TRUE);
         YBSetMidiVolume((MidValue*10));
         YBPlayDMidi();
         MidOldIdx = MidNewIdx;
         MidSts = MID_PLAY;
			//if (YBReachMidEnd==FALSE) 
			//{
			//	YBReachMidEnd=TRUE;
			//}
		}
	} 
	else
	if (MidCmd == MID_STOP) 
	{
		if (MidSts == MID_PLAY) 
		{
			YBStopDMidi(MAKEWPARAM(0,MSTREAM_STOPF_NOREOPEN));
         //YBQuitDMidi();
		}
		MidNewIdx = 99;
		MidOldIdx = 99;
		MidSts = MID_STOP;
	}
	return TRUE;
}

// KEYBOARD CONFIGURATION: BEGINNING
// KEYBOARD CONFIGURATION: SUB FUNCTIONS
BOOL Flash = FALSE;
BOOL GetKeyFlag = FALSE;

BOOL FindDispStr(short idx)
{
    BOOL retval = TRUE;

    if (KeyData.currentkey[idx]>='A' && KeyData.currentkey[idx]<='Z') {
        KeyData.displaykey[idx][0] = (char)KeyData.currentkey[idx];
        KeyData.displaykey[idx][1] = (char)0;
        goto HELL;
    };

    switch (KeyData.currentkey[idx]) {
    case 188:
        strcpy(&(KeyData.displaykey[idx][0]), "<");
        break;

    case 190:
        strcpy(&(KeyData.displaykey[idx][0]), ">");
        break;

    default:
        KeyData.displaykey[idx][0] = 0;
        retval = FALSE;
        break;
    };
HELL:
    return retval;
}

void MakeDispList(void)
{
    short i;
    for (i=0; i<17; i++) {
        FindDispStr(i);
    }
}

BOOL KeyNotUsedBefore(WPARAM wparam, short *idx)
{
    BOOL retval=TRUE;
    short i;

    for (i=0; i<17; i++) {
        if (wparam==KeyData.currentkey[i]) {
            *idx = i;
            retval = FALSE;
        }
    }
    return retval;
}

short ReConfigKeys(HWND win, UINT msg, WPARAM wparam)
{
                     
	short retval, j;
	                              
	j = 0;
		                              
    switch(wparam) {
    case VK_DOWN:
    case VK_RIGHT: 
    	if (!GetKeyFlag) { 
    		StrIdx++;
    		StrIdx = StrIdx%TotalString;
    	} 
    	break;
    case VK_UP:
    case VK_LEFT:       
    	if (!GetKeyFlag) {  
    		StrIdx--;
    		StrIdx = (TotalString+StrIdx)%TotalString;
    	}         
    	break;    
        
    case VK_RETURN:
        //sndPlaySound(WrapSnd1, SND_ASYNC);
        GetKeyFlag = TRUE;                      
        break;
        
    case VK_ESCAPE:       
    	GetKeyFlag = FALSE;
        //YBSetKeyActions(); 
    	j = 1;
    	break; 
    
    case 'A':
    case 'B':
	case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
    case 188:
    case 190:
    	if (GetKeyFlag) {
    		if (KeyNotUsedBefore(wparam, &retval)) {
    			KeyData.currentkey[StrIdx]=wparam;
                FindDispStr(StrIdx);
    			GetKeyFlag=FALSE;
    		} else if (KeyData.currentkey[StrIdx]==wparam) {
                GetKeyFlag=FALSE;
            } else {                              // in case the key is used
    			KeyData.currentkey[StrIdx]=wparam;         // already, clean the key, 
                FindDispStr(StrIdx);              // assignment for the old
    			KeyData.currentkey[retval]=0;              // action, try to get new key for it.
    			StrIdx = retval;                  
    		}  
    	}
        break;

    default: 
        break;
    };

	return j;        
}

void BYSetKeyConfigPara(void)
{
    short i;

    TotalString = KeyData.tstring-1;
    MakeDispList();
    for (i=0; i<TotalString; i++) {
        TextPtr[i] = KeyData.displaykey[i];
        TextPos[i] = &(KeyData.kpos[i][0]);
    }
    StrIdx = 0;
    ChrIdx = 0;
	BYChooseTextSurface(0);		// choose back surface
}

void BYDisplayKeys(BOOL show, short mode)
{
	char fps[100], fps1[20], fps2[20];
	HDC  hDC;
	int  i;
	IDirectDrawSurface *pdds;
	HFONT hOldFont, hNewFont;
	char *ptr; 
	long ii;
	static short jj=0;
    
	if (show) 
	{
		pdds = lpDDSText;

		if (pdds==NULL) 
			return;

		if (pdds->GetDC(&hDC)==DD_OK) 
		{
			hNewFont = GetStockObject(ANSI_FIXED_FONT);
			hOldFont = SelectObject(hDC, hNewFont);

			SetBkColor(hDC, RGB(0, 0, 0));
			SetBkMode(hDC, TRANSPARENT);
			SetTextColor(hDC, RGB(255, 255, 255));
			SetTextAlign(hDC, TA_CENTER);
			for (i=0; i<TotalString; i++) 
			{
				if (i==StrIdx && GetKeyFlag) 
				{
               ;
				} 
				else 
				{
					if (i==StrIdx) 
                  SetTextColor(hDC, RGB(0, 255, 0));
        			sprintf(fps, TextPtr[i]);  
					ptr=strchr(fps, '_');
					if (ptr!=NULL) 
					{
						strcpy(fps1, fps);
						fps1[(ptr-fps)] = 0;
						ii = (ptr-fps+1);
						strcpy(fps2, &fps[ii]);
						TextOut(hDC, TextPos[i][0], TextPos[i][1], fps1, lstrlen(fps1));
						TextOut(hDC, TextPos[i][0], TextPos[i][1]+15, fps2, lstrlen(fps2));
					} else 
            		TextOut(hDC, TextPos[i][0], TextPos[i][1], fps, lstrlen(fps));
						if (i==StrIdx)
                     SetTextColor(hDC, RGB(255, 255, 255));
				} // end if (i==StrIdx && GetKeyFlag)
         }
			SetTextColor(hDC, RGB(255, 0, 0));
         jj++;
         jj = jj%20;
         if (jj==0) Flash=!Flash;

         if (GetKeyFlag && Flash) 
			{
				sprintf(fps, "?");
				TextOut(hDC, (TextPos[StrIdx][0]+ChrIdx*8),
								(TextPos[StrIdx][1]), fps, lstrlen(fps));
         }

			SetBkColor(hDC, RGB(100, 100, 100));
			SetBkMode(hDC, OPAQUE);
			SelectObject(hDC, hOldFont);
			pdds->ReleaseDC(hDC);
		}
	}
}  

// KEYBOARD CONFIGURATION: MAIN FUNCTIONS
BOOL BYShowKbdConfigure(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_KBD_MENU);

	di.TurnOnMsCursor(FALSE);

	BYLoadOverlay(1, BmpFile[KeyboardConfigurationBackground]);
	BYSetKeyConfigPara();
	BYDisplayText = BYDisplayKeys;
	DDtext   = TRUE;
	EditMode = FALSE;
	BYKbrdHandler[pg_SHOW_KBD_MENU] = BYKdKbdConfigure;

	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYKdKbdConfigure(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	short retval;

   ISKEYDOWN(msg);
	ISPAGE(pg_SHOW_KBD_MENU);

	retval = ReConfigKeys(win, msg, wParam);
    if (retval) 
	{
       int i;
       extern long int CurKeyActions[28]; 
       DDtext  = FALSE;
		BYSetPrePageSwitch(Page, pg_SHOW_OPTION_MENU); 	
        Page = pg_SHOW_OPTION_MENU;

      for(i=0;i<28;++i)
      {
         CurKeyActions[i]=0;
      }

      if(KeyData.currentkey[0]>187)
      {
         if(KeyData.currentkey[0]==188)
         {
            CurKeyActions[26]=(COMMANDForward|COMMANDWeakShift);
         }
         else
         {
            CurKeyActions[27]=(COMMANDForward|COMMANDWeakShift);
         }
      }
      else
      {
         CurKeyActions[KeyData.currentkey[0]-'A']=(COMMANDForward|COMMANDWeakShift);
      }
      if(KeyData.currentkey[1]>187)
      {
         if(KeyData.currentkey[1]==188)
         {
            CurKeyActions[26]=(COMMANDLeft);
         }
         else
         {
            CurKeyActions[27]=(COMMANDLeft);
         }
      }
      else
      {
         CurKeyActions[KeyData.currentkey[1]-'A']=(COMMANDLeft);
      }
      if(KeyData.currentkey[2]>187)
      {
         if(KeyData.currentkey[2]==188)
         {
            CurKeyActions[26]=(COMMANDRight);
         }
         else
         {
            CurKeyActions[27]=(COMMANDRight);
         }
      }
      else
      {
         CurKeyActions[KeyData.currentkey[2]-'A']=(COMMANDRight);
      }
      if(KeyData.currentkey[3]>187)
      {
         if(KeyData.currentkey[3]==188)
         {
            CurKeyActions[26]=(COMMANDBack|COMMANDStrongShift);
         }
         else
         {
            CurKeyActions[27]=(COMMANDBack|COMMANDStrongShift);
         }
      }
      else
      {
         CurKeyActions[KeyData.currentkey[3]-'A']=(COMMANDBack|COMMANDStrongShift);
      }
      if(KeyData.currentkey[4]>187)
      {
         if(KeyData.currentkey[4]==188)
         {
            CurKeyActions[26]=(COMMANDForward|COMMANDMediumShift);
         }
         else
         {
            CurKeyActions[27]=(COMMANDForward|COMMANDMediumShift);
         }
      }
      else
      {
         CurKeyActions[KeyData.currentkey[4]-'A']=(COMMANDForward|COMMANDMediumShift);
      }
      if(KeyData.currentkey[5]>187)
      {
         if(KeyData.currentkey[5]==188)
         {
            CurKeyActions[26]=(COMMANDForward|COMMANDStrongShift);
         }
         else
         {
            CurKeyActions[27]=(COMMANDForward|COMMANDStrongShift);
         }
      }
      else
      {
         CurKeyActions[KeyData.currentkey[5]-'A']=(COMMANDForward|COMMANDStrongShift);
      }
      if(KeyData.currentkey[6]>187)
      {
         if(KeyData.currentkey[6]==188)
         {
            CurKeyActions[26]=(COMMANDLeft|COMMANDStrongShift|COMMANDDefenseShift) ;
         }
         else
         {
            CurKeyActions[27]=(COMMANDLeft|COMMANDStrongShift|COMMANDDefenseShift) ;
         }
      }
      else
      {
         CurKeyActions[KeyData.currentkey[6]-'A']=(COMMANDLeft|COMMANDStrongShift|COMMANDDefenseShift);
      }
      if(KeyData.currentkey[7]>187)
      {
         if(KeyData.currentkey[7]==188)
         {
            CurKeyActions[26]=(COMMANDRight|COMMANDStrongShift|COMMANDDefenseShift );
         }
         else
         {
            CurKeyActions[27]=(COMMANDRight|COMMANDStrongShift|COMMANDDefenseShift );
         }
      }
      else
      {
         CurKeyActions[KeyData.currentkey[7]-'A']=(COMMANDRight|COMMANDStrongShift|COMMANDDefenseShift);
      }
      if(KeyData.currentkey[8]>187)
      {
         if(KeyData.currentkey[8]==188)
         {
            CurKeyActions[26]=(COMMANDHighAttack|COMMANDDefenseShift);
         }
         else
         {
            CurKeyActions[27]=(COMMANDHighAttack|COMMANDDefenseShift);
         }
      }
      else
      {
         CurKeyActions[KeyData.currentkey[8]-'A']=(COMMANDHighAttack|COMMANDDefenseShift);
      }
      if(KeyData.currentkey[9]>187)
      {
         if(KeyData.currentkey[9]==188)
         {
            CurKeyActions[26]=(COMMANDJump);
         }
         else
         {
            CurKeyActions[27]=(COMMANDJump);
         }
      }
      else
      {
         CurKeyActions[KeyData.currentkey[9]-'A']=(COMMANDJump);
      }
      if(KeyData.currentkey[10]>187)
      {
         if(KeyData.currentkey[10]==188)
         {
            CurKeyActions[26]=(COMMANDCrouch);
         }
         else
         {
            CurKeyActions[27]=(COMMANDCrouch);
         }
      }
      else
      {
         CurKeyActions[KeyData.currentkey[10]-'A']=(COMMANDCrouch);
      }
      if(KeyData.currentkey[11]>187)
      {
         if(KeyData.currentkey[11]==188)
         {
            CurKeyActions[26]=(COMMANDVisorBeam);
         }
         else
         {
            CurKeyActions[27]=(COMMANDVisorBeam);
         }
      }
      else
      {
         CurKeyActions[KeyData.currentkey[11]-'A']=(COMMANDVisorBeam);
      }
      if(KeyData.currentkey[12]>187)
      {
         if(KeyData.currentkey[12]==188)
         {
            CurKeyActions[26]=(COMMANDShuriken);
         }
         else
         {
            CurKeyActions[27]=(COMMANDShuriken);
         }
      }
      else
      {
         CurKeyActions[KeyData.currentkey[12]-'A']=(COMMANDShuriken);
      }
      if(KeyData.currentkey[13]>187)
      {
         if(KeyData.currentkey[13]==188)
         {
            CurKeyActions[26]=COMMANDPhotonCannon;
         }
         else
         {
            CurKeyActions[27]=COMMANDPhotonCannon;
         }
      }
      else
      {
         CurKeyActions[KeyData.currentkey[13]-'A']=COMMANDPhotonCannon;
      }
      if(KeyData.currentkey[14]>187)
      {
         if(KeyData.currentkey[14]==188)
         {
            CurKeyActions[26]=(COMMANDPlasmaBlades);
         }
         else
         {
            CurKeyActions[27]=(COMMANDPlasmaBlades);
         }
      }
      else
      {
         CurKeyActions[KeyData.currentkey[14]-'A']=(COMMANDPlasmaBlades);
      }
      if(KeyData.currentkey[15]>187)
      {
         if(KeyData.currentkey[15]==188)
         {
            CurKeyActions[26]=(COMMANDUltraBlast);
         }
         else
         {
            CurKeyActions[27]=(COMMANDUltraBlast);
         }
      }
      else
      {
         CurKeyActions[KeyData.currentkey[15]-'A']=(COMMANDUltraBlast);
      }
        PostMessage(win, WM_COMMAND, Page, 0L);
    }
	return TRUE;

exit_with_false:
	return FALSE;
}
// KEYBOARD CONFIGURATION: ENDING

BOOL BYShowPlayMovie(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_PLAY_MOVIE);

	MidCmd = MID_STOP;
	BYMidiCenter();
	PlayAVI(win, AVIFiles[(whichavi-1)], "movie1", 1, AviSize);
	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYShowAviBmp(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_AVI_BMP);

	BYLoadOverlay(1, BmpFile[LevelInfo+whichavi-2]);
	BYKbrdHandler[pg_SHOW_AVI_BMP] = BYKdShowAviBmp;
	return TRUE;

exit_with_false:
	return FALSE;
}

// GAME SCREEN: BEGINNING
// GAME SCREEN: MAIN FUNCTIONS
BOOL BYShowGameScreen(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char tempfile[127];

	ISPAGE(pg_SHOW_GAME_SCREEN);

	bBYRenderingIsOK = FALSE;

#ifdef FREEWARE
	GameStates.IsTraining=FALSE;
#endif
	//MidCmd = MID_STOP;
	//BYMidiCenter();
	if (GameStates.IsTraining)
		strcpy(tempfile, BmpFile[TrainerLaunch]);
	else
		strcpy(tempfile, BmpFile[LevelLaunch+GameStates.CurrentLevel-1]);
	switch(VM_W3D)
	{
	case 640:
		if (sStretch.bStretch)
			BYSetO1To320x240();
		else
			BYSetO1To640x480();
		break;
	case 512:
	   BYSetO1To512x384();
		break;
	case 320:
		BYSetO1To320x240();
		break;
	}
	BYLoadOverlay(1, tempfile);

	BYRender = Render2DWorld;
	bBYRenderingIsOK = TRUE;
	
	nTimer = SetTimer(win, 2, 100, NULL);
//	nTimer = SetTimer(win, 2, 6000, NULL);

	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYTimeGameScreen(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_GAME_SCREEN);
	IS_WRAPPER_TIMER(wParam);

	KillTimer(win, nTimer);

	switch (VM_W3D) 
	{
	case 640:
		BYLoadOverlay(1, ConstructLevelName(BmpFile[GameUserInterfaceBackground]));
		BYSetO1To640x480();
		break;
	case 512:
		BYLoadOverlay(1, ConstructLevelName(BmpFile[GameUserInterfaceBackground]));
		BYSetO1To512x384();
		break;
	case 320:
		BYLoadOverlay(1, ConstructLevelName("WS112.BMP"));
		BYSetO1To320x240();
		break;
	}
	
	if (!BuildScene(myglobs.dev, myglobs.view, myglobs.scene, myglobs.camera))
	{
		return FALSE;
	}
	
	if (VSize!=4)
	{
		BYBlitOnToP(1, TRUE);
		BYDrawOverLay(1, TRUE);
	}

#ifdef CAPBMP
	DDSURFACEDESC ddsd;
	HRESULT hres;

	ddsd.dwSize = sizeof(ddsd);
	while ((hres = d3dappi.lpBackBuffer->Lock(NULL, &ddsd, 0, NULL)) == DDERR_WASSTILLDRAWING)
        ;
	if (hres == DD_OK)
	{
		ImagePtr  = (unsigned char *)ddsd.lpSurface;    
		d3dappi.lpBackBuffer->Unlock(NULL);
	}
/*
   if (D3DAppIGetSurfDesc(&ddsd, d3dappi.lpBackBuffer)==DD_OK)
	{
		ImagePtr = (unsigned char *)ddsd.lpSurface;
	} else
		ImageFlag = TRUE; */
	ImgBufSize = VM_W3D*VM_H3D;
	memset((unsigned char*)ImageBuffer, 0, 307200);
#endif

	//di.TurnOnMsCursor(FALSE);
	di.CreateDIMsDevice(TRUE);
	di.SetDIMsAction(MsActions);

	bBYRenderingIsOK = FALSE;
	BYRender = Render3DWorld;
	d3dapp->bRenderingIsOK = TRUE;
	bBYRenderingIsOK = TRUE;

	//Add by Eric 11/14/96
	if (GameStates.IsNetplay)
	{
		isIn3DGame = TRUE;
	}
	//end of Eric

	BYKbrdHandler[pg_SHOW_GAME_SCREEN] = BYKd3DGame;  
	bShowGameUI=TRUE;

#ifdef _DEBUG
//   DumpMemoryStatus("After loading level");
#endif

	return TRUE;

exit_with_false:
	return FALSE;
}
// GAME SCREEN: ENDING


// SET UP SOUND SYSTEM: BEGINNING
BOOL BYSetUpSoundSystem(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SETUP_SNDSYSTEM);

	YBSetUpSoundSystem(win);
   YBLoadSounds(win, GameStates.CurrentLevel, GameStates.CurrentRobot);

    MidCmd = MID_PLAY;
    MidNewIdx = GameStates.CurrentLevel - 1;
    if(MidNewIdx<0)
       MidNewIdx=6;
    BYMidiCenter();

	BYKbrdHandler[pg_SHOW_3D_SAMPLE] = BYDefaultHandler;  
	BYSetPrePageSwitch(Page, pg_SHOW_3D_SAMPLE); 
   Page = pg_SHOW_3D_SAMPLE;
	PostMessage(win, WM_COMMAND, Page, 0L);

	return TRUE;

exit_with_false:
	return FALSE;
}
// SET UP SOUND SYSTEM: ENDING

BOOL BYShow3DExample(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_3D_SAMPLE);
	SAMEPAGE();

	bBYRenderingIsOK = FALSE;

#ifdef _DEBUG
   {
      char tempbuffer[80];
      BYDumpInfo("#####################################################");
      sprintf(tempbuffer, "              Level #%d", GameStates.CurrentLevel);
      BYDumpInfo(tempbuffer);
      BYDumpInfo("#####################################################");
      DumpMemoryStatus("Before loading level");
   }
#endif   // _DEBUG
	
	//BYKbrdHandler[pg_SHOW_3D_SAMPLE] = BYDefaultHandler;  
	if (bUseDebug)
	{
		BYLoadOverlay(3, BmpFile[NonExistentBitmap]);  
		BYSetUIDumpCo();

		BYRender = Render3DWorld;
		d3dapp->bRenderingIsOK = TRUE;
		bBYRenderingIsOK = TRUE;

		//Add by Eric 11/14/96
		if (GameStates.IsNetplay)
		{
			isIn3DGame = TRUE;
		}
		//end of Eric

	}
	else
	{
		bInWrapper = FALSE;
		di.TurnOnMsCursor(FALSE);
		di.ReleaseMsSurface();
		di.DeleteDIMsDevice();

		BYExitFromMainMenu();

		BYSelectRMode();

		BYIniFor3DGame();

		if (!BYCreateD3DRMetc(myglobs.hWndMain))
		{
			return FALSE;
		}

		if (!BYCreateDDDFor3DGame(0, myglobs.hWndMain, BYAfterDeviceCreated,
										NULL, BYPreDeviceDestroyed, NULL, &d3dapp)) 
		{
			BYDumpInfo(D3DAppLastErrorString());
			return FALSE;
		}

		//bInWrapper = FALSE;

		if (VM_W3D==320)
		{
			char backname[32];

			strcpy(backname, "back10.bmp");
			backname[5] += VSize-1;    // makes "back10.bmp", "back11.bmp", etc.

         //if (!(d3dappi.ThisDriver.bIsHardware && vramsize > 2097152 ))
			   BYLoadOverlay(2, ConstructLevelName(backname));
         //else
         //   lpDDSOverlay[1]=NULL;
			BYLoadOverlay(3, ConstructLevelName("WS120.BMP")); 
		}
		else
		if (VM_W3D==640)
		{
			char backname[32];

			strcpy(backname, "back20.bmp");
			backname[5] += VSize-1;    // makes "back20.bmp", "back21.bmp", etc.

         //if (!(d3dappi.ThisDriver.bIsHardware && vramsize > 2097152 ))
		      BYLoadOverlay(2, ConstructLevelName(backname));
			if (sStretch.bWillStretch)
		 		BYLoadOverlay(3, ConstructLevelName("WS120.BMP")); 
			else
				BYLoadOverlay(3, ConstructLevelName(BmpFile[AskQuit])); 
		}
      else
		if (VM_W3D==512)
		{
			char backname[32];

			strcpy(backname, "back30.bmp");
			backname[5] += VSize-1;    // makes "back30.bmp", "back31.bmp", etc.

         //if (!(d3dappi.ThisDriver.bIsHardware && vramsize > 2097152 ))
			   BYLoadOverlay(2, ConstructLevelName(backname));
         //else
         //   lpDDSOverlay[1]=NULL;
			BYLoadOverlay(3, ConstructLevelName(BmpFile[AskQuit]));  
		}
		BYSetUIDumpCo();

		BYSetPrePageSwitch(Page, pg_SHOW_GAME_SCREEN); 
		Page = pg_SHOW_GAME_SCREEN;
		PostMessage(win, WM_COMMAND, Page, 0L); 
	}
	return TRUE;

exit_with_false:
	return FALSE;
} 

BOOL BYKbFrom3DTo2D(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	BYSetPrePageSwitch(Page, pg_FROM_3D_TO_2D); 
	Page = pg_FROM_3D_TO_2D;
	PostMessage(win, WM_COMMAND, Page, 0L);
	return TRUE;
}

#ifndef FREEWARE
// Before call this function, you need to release all your 3D stuff safely!
BOOL BYSwitchFrom3DTo2D(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_FROM_3D_TO_2D);
   SAMEPAGE();


	bBYRenderingIsOK = FALSE;
	BYClearOverlaySurface(1);
	BYBlitOnToP(1, TRUE);
	   	//Tim Stretch: do not stretch in wrapper
	if (sStretch.bStretch == FALSE)
		BYDrawOverLay(1, TRUE);
	//bBYRenderingIsOK = FALSE;

	di.DeleteDIMsDevice();

	YBUnLoadSoundSystem(win);
	BYRestoreGDIobjects();

	BYKbrdHandler[pg_SHOW_3D_SAMPLE] = BYDefaultHandler;  

	if (bUseDebug)
	{
		BYRender = Render2DWorld;
	   nTimer = SetTimer(win, 2, 50, NULL);       
	}
	else
	{
		BYCleanUp3DSysStuff();

		if (!BYCreateDDForWrapper(myglobs.hWndMain))
		{
			return FALSE;
		}

		di.CreateDIMsDevice(TRUE);
	
		di.CreateMsSurface();
		di.LoadCursorBmp("cursor.bmp");
		di.SetMsCursorColorKey(TRUE, RGB(0,0,0));
		di.SelectAniCursor(ani_cursor);
		//di.SetMsTotalAnis(7);
		//di.SetMsAniSpeed(3);
		//di.SetMsCursorInfo(5, 5, 10, 10);
		di.SetMsTotalAnis(1);
		di.SetMsAniSpeed(1);
		di.SetMsCursorInfo(8, 8, 16, 16);

		di.TurnOnMsCursor(FALSE);

		bInWrapper = TRUE;

		BYRender = Render2DWorld;
		BYCleanUp = BYExitFromMainMenu;
	   nTimer = SetTimer(win, 2, 50, NULL);       
	}
	//bBYRenderingIsOK = TRUE;

	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYTimeFrom3DTo2D(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_FROM_3D_TO_2D);
	IS_WRAPPER_TIMER(wParam);

	KillTimer(win, nTimer);
	BYSetPrePageSwitch(Page, pg_DECIDE2D_AFTGAME); 
	Page = pg_DECIDE2D_AFTGAME;
	PostMessage(BYMainHwnd, WM_COMMAND, Page, 0L);

	return TRUE;

exit_with_false:
	return FALSE;
}
#endif

BOOL BYLoseAllRobot(void)
{
    BOOL retval = TRUE;
    short i;

    for (i=SabreRobot; i<=KaberRobot; i++)
        //if (RobotStatus[i]) retval = FALSE;
		if(!GameStates.IsRobotDead[i]) 
			return FALSE;
    return retval;  // TRUE for lose all
} 

BOOL BYDecideLoseStatus(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_DECIDE_LOSESTATUS);

	if (!BYLoseAllRobot()) 
	{
		BYSetPrePageSwitch(Page, pg_SHOW_LOSE_ONE); 
		Page = pg_SHOW_LOSE_ONE;
		PostMessage(win, WM_COMMAND, Page, 0L);
	}
	else
	{
		BYSetPrePageSwitch(Page, pg_SHOW_LOSE_ALL); 
		Page = pg_SHOW_LOSE_ALL;
		PostMessage(win, WM_COMMAND, Page, 0L);
	}
	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYShowLoseOne(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_LOSE_ONE);

	BYLoadOverlay(1, BmpFile[RobotDestroyed+GameStates.CurrentRobot]);
	BYSetO1MainMenuB();
	BYKbrdHandler[pg_SHOW_LOSE_ONE] = BYKdLoseOne;
	bBYRenderingIsOK = TRUE;
	GameStates.RobotLose=FALSE;

	return TRUE;
exit_with_false:
	return FALSE;
}

char lpstrGameOver[20]="GAME OVER";
short gm640[1][4] =
{
	320, 160, TA_CENTER, 100
};

COLORREF gmcol[1] =
{
    RGB(0, 255, 0)
};

void BYSetGameOverText(void)
{   
	short i;

	TotalString = 1;

	TextPtr[0] = lpstrGameOver;

	for (i=0; i<TotalString; i++) 
	{
		TextPos[i] = &(gm640[i][0]);
	}
	TextCol = gmcol;
	StringFrame = 0;
	//TextSurface = 0;
	BYChooseTextSurface(0);

}

void BYDisplayGameOver(BOOL show, short mode)
{
	char fps[100];
	HDC  hDC;
	int  i;
	IDirectDrawSurface *pdds;
	HFONT hOldFont, hNewFont;
	long int t;

	if (show) 
	{
		pdds = lpDDSText;
		if (pdds==NULL) 
		{
			return;
		}
		if (StringFrame < 40) 
		{
			StringFrame++;
		}
		t = StringFrame;
		t = t % 40;

		if (pdds->GetDC(&hDC)==DD_OK) 
		{
			SetBkColor(hDC, RGB(0, 0, 0));
			SetBkMode(hDC, TRANSPARENT);
         for (i=0; i<TotalString; i++) 
			{
				if (TextPos[i][3]==0) 
				{
					hNewFont = GetStockObject(ANSI_FIXED_FONT);
					hOldFont = SelectObject(hDC, hNewFont);
				} else {
					hNewFont = BYSelectFont(hDC, "System", 0, TextPos[i][3]);
					hOldFont = SelectObject(hDC, hNewFont);
				}
				SetTextColor(hDC, TextCol[i]);
				SetTextAlign(hDC, TextPos[i][2]);
				if (StringFrame<i && i>7) 
				{ 
					; 
				} 
				else 
				{
        			sprintf(fps, TextPtr[i]);
        			TextOut(hDC, TextPos[i][0], TextPos[i][1], fps, lstrlen(fps));
				}
				if (TextPos[i][3]==0) 
				{
					SelectObject(hDC, hOldFont);
				} 
				else 
				{
					SelectObject(hDC, hOldFont);
					DeleteObject(hNewFont);
				}
         }
			SetTextColor(hDC, RGB(0, 255, 0));
         if (mode) 
			{
             hNewFont = GetStockObject(ANSI_FIXED_FONT);
             hOldFont = SelectObject(hDC, hNewFont);

             sprintf(fps, "-");
             TextOut(hDC, (TextPos[StrIdx][0]+ChrIdx*8),
                          (TextPos[StrIdx][1]+8), fps, lstrlen(fps));
             SelectObject(hDC, hOldFont);
         }

			SetBkColor(hDC, RGB(100, 100, 100));
			SetBkMode(hDC, OPAQUE);
			pdds->ReleaseDC(hDC);
		}
	}
}

BOOL BYShowLoseAll(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_LOSE_ALL);

	MidCmd = MID_STOP;
	BYMidiCenter();

	BYClearOverlaySurface(1);
	BYBlitOnToP(1, TRUE);
	DDtext = FALSE;

	PlayAVI(win, AVIFiles[11], "movie1", 0, AviSize); 

	BYKbrdHandler[pg_SHOW_LOSE_ALL]  = BYKdLoseAll;

	//bBYRenderingIsOK = TRUE;

	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYKdLoseAll(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_LOSE_ALL);
	SAMEPAGE();

	//DDtext  = FALSE;
	//BYDisplayText = BYDisplayStr;
	//BYClearBackSurface();
	//BYSurfaceBlt(DDmode0);
	CloseAVI(win, "movie1");

//	BYSetPrePageSwitch(Page, pg_SHOW_CREDITS); 	
//	Page = pg_SHOW_CREDITS;
//	PostMessage(win, WM_COMMAND, Page, 0L);
	BYSetPrePageSwitch(Page, pg_NEW_THANKYOU);
	Page = pg_NEW_THANKYOU;
	PostMessage(win, WM_COMMAND, Page, 0L);

	bBYRenderingIsOK = TRUE;

	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYDecideMode3Status(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_DECIDE_M3STATUS);

	//YBResetToNormalDD(Vmode);

	if (MonsterAnimationState == MonsterAllDead)
	{
//		for (short i=0; i<5; i++)
//		{
//			RobotStatus[i] = 1;
//		}
		GameStates.CurrentSubmonster=Alpha;
		BYSetPrePageSwitch(Page, pg_M3_SHOWLOSEBMP); 
		Page = pg_M3_SHOWLOSEBMP;
		PostMessage(win, WM_COMMAND, Page, 0L);
	} 
	else 
	{   
		if (BYLoseAllRobot()) 
		{
			BYSetPrePageSwitch(Page, pg_M3_RESTOREALL); 
			Page = pg_M3_RESTOREALL;
			PostMessage(win, WM_COMMAND, Page, 0L);
		} 
		else 
		{	/*Rem by Eric 11/15/96
			BYSetPrePageSwitch(Page, pg_M3_SELECTARobot); 
			Page = pg_M3_SELECTARobot;
			PostMessage(win, WM_COMMAND, Page, 0L);
			*///end of Eric

			//Add by Eric 11/15/96
			//this position should select a monster.
			//if press ESC when select monster or Robot
			//display monster victory bmp
			if (GameStates.IsNetplay)
			{
				BYSetPrePageSwitch(Page, pg_M3_SHOWWINBMP); 
				Page = pg_M3_SHOWWINBMP;
				PostMessage(win, WM_COMMAND, Page, 0L);
			}
			else
			{
				BYSetPrePageSwitch(Page, pg_M3_SELECTARobot); 
				Page = pg_M3_SELECTARobot;
				PostMessage(win, WM_COMMAND, Page, 0L);
			}
			//end of Eric
		} 
	}

	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYShowM3LoseBmp(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_M3_SHOWLOSEBMP);

	//BYLoadOverlay(1, BmpFile[LoserPopulationBackground]); //Rem by Eric 11/15/96
	//BYSetO1MainMenuB();			 //Rem by Eric 11/15/96

	//Add by Eric 11/15/96
	if (GameStates.IsNetplay)
	{
		BYLoadOverlay(1, BmpFile[MonsterDead + GameStates.CurrentLevel - 1]);
		BYSetO1MainMenuB();
		//BYSetPopuText();
		//BYDisplayText = BYDisplayPopu;
		//DDtext = TRUE;
		//EditMode = FALSE;
	}
	else
	{
		BYLoadOverlay(1, BmpFile[LoserPopulationBackground]);
		BYSetO1MainMenuB();
	}
	//end of Eric
	
	bBYRenderingIsOK = TRUE;

	nTimer = SetTimer(win, 2, 6000, NULL); 
	
	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYShowM3WinBmp(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_M3_SHOWWINBMP);

	//BYLoadOverlay(1, BmpFile[28]);//Rem by Eric 11/15/96
	//BYSetO1MainMenuB();			//Rem by Eric 11/15/96

	//Add by Eric 11/15/96
	if (GameStates.IsNetplay)
	{
		BYLoadOverlay(1, BmpFile[MonsterVictory + GameStates.CurrentLevel - 1]);
		BYSetO1MainMenuB();
		//BYSetPopuText();
		//BYDisplayText = BYDisplayPopu;
		//DDtext = TRUE;
		//EditMode = FALSE;
	}
	else
	{
		BYLoadOverlay(1, BmpFile[WorldSaved]);
		BYSetO1MainMenuB();
	}
	//end of Eric
	
	bBYRenderingIsOK = TRUE;

	nTimer = SetTimer(win, 2, 6000, NULL);
	return TRUE;
exit_with_false:
	return FALSE;
}


BOOL BYBackToMain(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_M3_BACKTOMAIN);

	GameStates.CurrentLevel = Mojave;
//	OldLevel= GameStates.CurrentLevel;
   if (!GameStates.IsNetplay)
   {
	   BYSetPrePageSwitch(Page, pg_SHOW_MAIN_MENU); 
	   Page = pg_SHOW_MAIN_MENU;
   }
   else
   {
	   BYSetPrePageSwitch(Page, pg_NET_SHOW_SCORE); 
	   Page = pg_NET_SHOW_SCORE;
   }
	PostMessage(win, WM_COMMAND, Page, 0L);
	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYM3RestoreAll(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
//	short i;

	ISPAGE(pg_M3_RESTOREALL);

//	for (i=0; i<5; i++)
//	{
//		RobotStatus[i] = 1;
//	}
	GameStates.CurrentSubmonster=Alpha;
	if (GameStates.CurrentLevel>Tokyo) 
	{
		BYSetPrePageSwitch(Page, pg_M3_SHOWWINBMP); 
		Page = pg_M3_SHOWWINBMP;
		PostMessage(win, WM_COMMAND, Page, 0L);
	}
	else 
	{
		GameStates.CurrentLevel++;
		BYSetPrePageSwitch(Page, pg_M3_SELECTARobot); 
		Page = pg_M3_SELECTARobot;
		PostMessage(win, WM_COMMAND, Page, 0L);
	}
	return TRUE;
exit_with_false:
	return FALSE;
}

// !!!!!!
BOOL BYM3SelectARobot(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_M3_SELECTARobot);

	GameStates.CurrentRobot = BYSelectARobot();
	BYSetPrePageSwitch(Page, pg_ENTER3D_DELAY); 
	Page = pg_ENTER3D_DELAY;
	PostMessage(win, WM_COMMAND, Page, 0L);

	//Page = pg_SET_CHAR_TIMER;
	//nTimer = SetTimer(win, 2, 1000, NULL);

	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYShowAviDelay(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_AVIPLAY_DELAY);

	nTimer = SetTimer(win, 2, 500, NULL);  // next=pg_PLAY_MOVIE
	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYDecide2DAfterGame(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_DECIDE2D_AFTGAME);

	MidCmd = MID_STOP;
	BYMidiCenter();

	if (GameStates.IsNetplay)
   {
      //InitSelectMonsterMenu();
	   bSelectRobot = FALSE;
	   bSelectMonster = FALSE;
	   KillTimer(win, nTimer);
		if(PlayAsMonster)
		{
			bMonsterMenu = TRUE;
			BYSetPrePageSwitch(Page, pg_DECIDE_M3STATUS); 	
    		Page = pg_DECIDE_M3STATUS;
    		PostMessage(win, WM_COMMAND, Page, 0L);
		}
      else
      {
	      //BYSetPrePageSwitch(Page, pg_SHOW_CHAR_MENU); 	
	      //Page = pg_SHOW_CHAR_MENU;
					BYSetPrePageSwitch(Page, pg_UNLOAD_REALGAME); 	
    				Page = pg_UNLOAD_REALGAME;
	      PostMessage(win, WM_COMMAND, Page, 0L);
      }
      return TRUE;   // Do I want to return out of this function here or not?
   }	   

	//YBUnLoadSoundSystem(win);

	//YBSetDrawMode(1, 0);

	if (GameStates.IsAutodemo && !AutoDemoNext) 
	{
		GameStates.IsAutodemo = FALSE;
		GameStates.CurrentLevel = Mojave;
		GameStates.RobotLose=FALSE;
		GameStates.MonsterLose=FALSE;
		/*
		//Add by Eric 11/15/96
		if (GameStates.IsNetplay)
		{
			EventSndBuf.MsgId = NEW_MSG;
			EventSndBuf.Event = EVENT_GOODBYE;
		}
		//end of Eric

		PostMessage(win, WM_DESTROY, 0, 0L); 
		*/
		BYSetPrePageSwitch(Page, pg_INTRO_MOVIE); 
		Page = pg_INTRO_MOVIE;
		PostMessage(win, WM_COMMAND, Page, 0L);

	}
	else
	{
		if (GameStates.IsAutodemo) 
		{
//			BYSetPrePageSwitch(Page, pg_NEXT_AUTODEMO); 	
//			Page = pg_NEXT_AUTODEMO;
			GameStates.RobotLose=FALSE;
			GameStates.MonsterLose=FALSE;
			GameStates.CurrentLevel++;
			if (GameStates.CurrentLevel>Tokyo) 
			{
				GameStates.CurrentLevel = Mojave;
#ifndef FREEWARE
#ifdef _DEBUG
				BYSetPrePageSwitch(Page, pg_SHOW_GOMAN_TITLE); 	
				Page = pg_SHOW_GOMAN_TITLE;
				PostMessage(win, WM_COMMAND, Page, 0L);
#else
				BYSetPrePageSwitch(Page, pg_INTRO_MOVIE); 	
				Page = pg_INTRO_MOVIE;
				PostMessage(win, WM_COMMAND, Page, 0L);
#endif
#else
				BYSetPrePageSwitch(Page, pg_GET_D3DINFO); 	
				Page = pg_GET_D3DINFO;
				PostMessage(win, WM_COMMAND, Page, 0L);
#endif
			}
			else
			{
				BYSetPrePageSwitch(Page, pg_SHOW_GOMAN_TITLE); 
				Page = pg_SHOW_GOMAN_TITLE;
				PostMessage(win, WM_COMMAND, Page, 0L);
			}
		}
		else
		{
			if (PlayAsMonster) 
			{
				BYSetPrePageSwitch(Page, pg_DECIDE_M3STATUS); 	
    			Page = pg_DECIDE_M3STATUS;
    			PostMessage(win, WM_COMMAND, Page, 0L);
			} 
			else // !(PlayAsMonster)
			{
				if (!GameStates.IsTraining) 
				{
					BYSetPrePageSwitch(Page, pg_UNLOAD_REALGAME); 	
    				Page = pg_UNLOAD_REALGAME;
    				PostMessage(win, WM_COMMAND, Page, 0L);
				} 
				else 
				{  
					DDtext  = FALSE;
//					RestoreFromTrainer();

					BYSetPrePageSwitch(Page, pg_END_OF_TRAIN); 	
    				Page = pg_END_OF_TRAIN;
    				PostMessage(win, WM_COMMAND, Page, 0L);

				} 
			} // end if !(PlayAsMonster)
		} // end if !(AutoDemoFlag && AutoDemoNext) 
	} // end if !(AutoDemoFlag && !AutoDemoNext)
//	bBYRenderingIsOK = TRUE;

	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYShowNextDemo(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_NEXT_AUTODEMO);
	//YBResetToNormalDD(Vmode);

	GameStates.CurrentLevel++;
	if (GameStates.CurrentLevel>Tokyo) 
	{
		GameStates.CurrentLevel = Mojave;
/*
		AutoDemoFlag = FALSE;
		AutoDemoNext = FALSE;
		
		//Add by Eric 11/15/96
		if (GameStates.IsNetplay)
		{
			EventSndBuf.MsgId = NEW_MSG;
			EventSndBuf.Event = EVENT_GOODBYE;
		}
		//end of Eric

		PostMessage(win, WM_DESTROY, 0, 0L);
	} 
	else
	{
		nTimer = SetTimer(win, 2, 100, NULL);   // 1000
*/
	}
	nTimer = SetTimer(win, 2, 100, NULL);   // 1000
	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYUnloadRealGame(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_UNLOAD_REALGAME);

	if (QuitFlag) 
	{
		QuitFlag = FALSE;   
		/*
		BYSetPrePageSwitch(Page, pg_SHOW_MAIN_MENU); 
		Page = pg_SHOW_MAIN_MENU;
		PostMessage(win, WM_COMMAND, Page, 0L);
		*/
		BYSetPrePageSwitch(Page, pg_SHOW_CHAR_MENU); 	
		Page = pg_SHOW_CHAR_MENU;
		PostMessage(win, WM_COMMAND, Page, 0L);

		//bBYRenderingIsOK = TRUE; 

		//di.TurnOnMsCursor(TRUE);

	}
	else 
	if (GameStates.RobotLose) 
	{
		BYSetPrePageSwitch(Page, pg_DECIDE_LOSESTATUS); 
		Page = pg_DECIDE_LOSESTATUS;
		PostMessage(win, WM_COMMAND, Page, 0L);
	}
	else
	{
		/* Rem by Eric 11/18/96
		BYSetPrePageSwitch(Page, pg_DECIDE_WINSTATUS); 
		Page = pg_DECIDE_WINSTATUS;
		PostMessage(win, WM_COMMAND, Page, 0L);
		*/
//GameStates.IsNetplay
		//Add by Eric 11/18/96
		if (GameStates.IsNetplay)
		{
	      if (!GameStates.RobotLose) 
	      {
			   BYSetPrePageSwitch(Page, pg_REAL_WONMIDDLE); 
			   Page = pg_REAL_WONMIDDLE;
			   PostMessage(win, WM_COMMAND, Page, 0L);
         }
         else
         {
		      BYSetPrePageSwitch(Page, pg_DECIDE_LOSESTATUS); 
		      Page = pg_DECIDE_LOSESTATUS;
		      PostMessage(win, WM_COMMAND, Page, 0L);
         }
		}
		else
		{
			BYSetPrePageSwitch(Page, pg_DECIDE_WINSTATUS); 
			Page = pg_DECIDE_WINSTATUS;
			PostMessage(win, WM_COMMAND, Page, 0L);
		}
		//end of Eric
	}
	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYDecideWinStatus(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_DECIDE_WINSTATUS);

	if (GameStates.CurrentLevel==Tokyo) 
	{
		BYSetPrePageSwitch(Page, pg_REAL_WONFINAL); 
		Page = pg_REAL_WONFINAL;
		PostMessage(win, WM_COMMAND, Page, 0L);
	}
	else
	{
		BYSetPrePageSwitch(Page, pg_REAL_WONMIDDLE); 
		Page = pg_REAL_WONMIDDLE;
		PostMessage(win, WM_COMMAND, Page, 0L);
	}
	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYShowWonFinal(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	BOOL honor=TRUE;
	int i;

	ISPAGE(pg_REAL_WONFINAL);

	for(i=Mojave;i<=Tokyo;++i)
	{
		if(!GameStates.LevelHonor[i])
			honor=FALSE;
	}

	MidCmd = MID_STOP;
	BYMidiCenter();

	BYClearOverlaySurface(1);
	BYBlitOnToP(1, TRUE);
	DDtext = FALSE;

	if (honor)  
	{
		PlayAVI(win, AVIFiles[9], "movie1", 0, AviSize); 
	}
   else
	{
		PlayAVI(win, AVIFiles[10], "movie1", 0, AviSize); 
	}
	//bBYRenderingIsOK = TRUE;
	BYKbrdHandler[pg_REAL_WONFINAL]  = BYKdWonFinal;

	//nTimer = SetTimer(win, 2, 6000, NULL);
	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYKdWonFinal(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
   ISKEYDOWN(msg);
   ISPAGE(pg_REAL_WONFINAL);

	CloseAVI(win, "movie1");

	if (GameStates.IsNetplay)
	{
		BYSetPrePageSwitch(Page, pg_NET_SHOW_SCORE); 	
		Page = pg_NET_SHOW_SCORE;
		PostMessage(win, WM_COMMAND, Page, 0L);
	}
	else
	{
		BYSetPrePageSwitch(Page, pg_SHOW_POPULATION); 
		Page = pg_SHOW_POPULATION;
		PostMessage(win, WM_COMMAND, Page, 0L);
	}
	bBYRenderingIsOK = TRUE;

	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYShowWonMiddle(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_REAL_WONMIDDLE);

	if (GameStates.LevelHonor[GameStates.CurrentLevel])  
	{
		BYLoadOverlay(1, BmpFile[HonorableVictory]);
	}
   else
	{
		BYLoadOverlay(1, BmpFile[EmptyVictory]);
	}
	BYSetO1MainMenuB();
	bBYRenderingIsOK = TRUE;

	nTimer = SetTimer(win, 2, 6000, NULL);
	return TRUE;
exit_with_false:
	return FALSE;
}

// Page READY_TO_GO is now only for training mission
BOOL BYEndOfTraining(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int i;
	ISPAGE(pg_END_OF_TRAIN);
	GameStates.CurrentLevel=Trainer;
	for(i=Tokyo;i>=Mojave;--i)
	{
		if(!GameStates.IsMonsterDead[i][2])
			GameStates.CurrentLevel = i;
	}

	if (GameStates.MonsterLose) 
	{
		GameStates.MonsterLose=0;
		GameStates.RobotLose=0;
		GameStates.IsTraining=0;
		BYLoadOverlay(1, BmpFile[TrainerVictory]);
		BYSetO1MainMenuB();
		bBYRenderingIsOK = TRUE;        // Enable rendering

		nTimer = SetTimer(win, 2, 6000, NULL);
	}
	else
	{
		GameStates.MonsterLose=0;
		GameStates.RobotLose=0;
		GameStates.IsTraining=0;
		/*
		BYSetPrePageSwitch(Page, pg_SHOW_MAIN_MENU); 	
		Page = pg_SHOW_MAIN_MENU;
		PostMessage(win, WM_COMMAND, Page, 0L);
		*/
		BYSetPrePageSwitch(Page, pg_SHOW_TRAIN_MENU); //pg_SHOW_CHAR_MENU); 	
		Page = pg_SHOW_TRAIN_MENU;   //pg_SHOW_CHAR_MENU;
		PostMessage(win, WM_COMMAND, Page, 0L);

		bBYRenderingIsOK = TRUE; 

		di.TurnOnMsCursor(TRUE);

	}
	Hours = 0;
	Minutes = 0;
	Seconds = 0;
	Thousandths = 0;

	return TRUE;
exit_with_false:
	return FALSE;
}

// Page READY_TO_GO is now only for training mission
BOOL BYTimeReadyToGo(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_END_OF_TRAIN);
	IS_WRAPPER_TIMER(wParam);

	KillTimer(win, nTimer);
	
	/*
	di.CreateDIMsDevice(TRUE);

	di.CreateMsSurface();
	di.LoadCursorBmp("cursor.bmp");
	di.SetMsCursorColorKey(TRUE, RGB(0,0,0));
	di.SelectAniCursor(ani_cursor);
	//di.SetMsTotalAnis(7);
	//di.SetMsAniSpeed(3);
	//di.SetMsCursorInfo(5, 5, 10, 10);
	di.SetMsTotalAnis(1);
	di.SetMsAniSpeed(1);
	di.SetMsCursorInfo(8, 8, 16, 16);

	di.TurnOnMsCursor(TRUE); */

	BYSetPrePageSwitch(Page, pg_SHOW_MAIN_MENU); 	
	Page = pg_SHOW_MAIN_MENU;
	PostMessage(win, WM_COMMAND, Page, 0L);

	return TRUE;
exit_with_false:
	return FALSE;
}
//
short ppos[14][4] =
{
    10, 10, TA_LEFT, 30, 10, 40, TA_LEFT, 30, 
    70, 90, TA_LEFT, 30, 
    10, 130, TA_LEFT, 30, 10, 170, TA_LEFT, 30, 
    10, 190, TA_LEFT, 30,
    10, 230, TA_LEFT, 30, 10, 260, TA_LEFT, 30,

    120, 10, TA_LEFT, 30,
    300, 40, TA_RIGHT, 30,
    300, 130, TA_RIGHT, 30,
    300, 170, TA_RIGHT, 30,
    300, 230, TA_RIGHT, 30,
    300, 260, TA_RIGHT, 30
};

short ppos320[14][4] =
{
    5, 5, TA_LEFT, 15, 5, 20, TA_LEFT, 15, 
    35, 45, TA_LEFT, 15, 
    5, 65, TA_LEFT, 15, 5, 85, TA_LEFT, 15, 
    5, 95, TA_LEFT, 15,
    5, 115, TA_LEFT, 15, 5, 130, TA_LEFT, 15,

    60, 5, TA_LEFT, 15,
    150, 20, TA_RIGHT, 15,
    150, 65, TA_RIGHT, 15,
    150, 85, TA_RIGHT, 15,
    150, 115, TA_RIGHT, 15,
    150, 130, TA_RIGHT, 15
};

COLORREF pcol[14] =
{
    RGB(0, 255, 0),
    RGB(0, 255, 0),
    RGB(0, 255, 0),
    RGB(0, 255, 0),
    RGB(0, 255, 0),
    RGB(0, 255, 0),
    RGB(0, 255, 0),
    RGB(0, 255, 0),

    RGB(255, 255, 255),
    RGB(255, 255, 255),
    RGB(255, 255, 255),
    RGB(255, 255, 255),
    RGB(255, 255, 255),
    RGB(255, 255, 255)
};


char MissionTitle[20]="Mission:";
char PrePopuTitle[20]="Population:";
char AFTMATHTitle[20]="AFTERMATH";
char AftPopuTitle[20]="Population:";
char TimeTitle[20]="Time:";
char ScoreTitle[20]="Score:";
char OverallTitle[20]="Overall:";
char Line[40]="_________________________";

char MissionString[6][16]=
{
    "Mojave Desert  ",
    "Rocky Mountains",
    "Hawaii         ",
    "San Francisco  ",
    "New York       ",
    "Tokyo          "
};

char PrePopuString[30];
char AftPopuString[30];
char TimeString[30]="10:00";
char ScoreString[20]="1222";
char OverallString[20]="6666666";

//long int PrePopulation = 1000000;
long int AftPopulation = 730000;
long int UserScore = 0;
unsigned char H0=0;
unsigned char M0=0;
unsigned char S0=0;
//unsigned char H1, M1, S1;


void BYSetPopuText()
{   
	short i;

	if(!GameStates.IsTraining)
	{
		GameStates.Seconds+=Seconds;
		while(GameStates.Seconds>60)
		{
			GameStates.Minutes+=1;
			GameStates.Seconds-=60;
		}
		GameStates.Minutes+=Minutes;
		while(GameStates.Minutes>60)
		{
			GameStates.Hours+=1;
			GameStates.Minutes-=60;
		}

		GameStates.Hours+=Hours;
	}
//	H1 = GameStates.Hours;
//	M1 = GameStates.Minutes;
//	S1 = GameStates.Seconds;
	AftPopulation = Population;

//	if (S1<S0) 
//	{
//		S1 = 60 + S1 - S0;
//		M1--;
//	} else
//		S1 = S1 - S0;
//
//	if (M1<M0) 
//	{
//		M1 = 60 + M1 - M0;
//		H1--;
//	} else 
//		M1 = M1 - M0;
//
//	H0 = Hours;
//	M0 = Minutes;
//	S0 = Seconds;

//	UserScore = AftPopulation; // - (H1*10000+M1*100+S1);
	GameStates.Score+=AftPopulation;

	TotalString = 14;

	TextPtr[0] = MissionTitle;
	TextPtr[1] = PrePopuTitle;
	TextPtr[2] = AFTMATHTitle;
	TextPtr[3] = AftPopuTitle;
	TextPtr[4] = TimeTitle;
	TextPtr[5] = Line;
	TextPtr[6] = ScoreTitle;
	TextPtr[7] = OverallTitle;

	TextPtr[8] = &(MissionString[(GameStates.CurrentLevel-1)][0]);
	sprintf(PrePopuString, "%d", PrePopulation);
	TextPtr[9] = PrePopuString;
	sprintf(AftPopuString, "%d", AftPopulation);
	TextPtr[10] = AftPopuString;
	sprintf(TimeString, "%02d:%02d:%02d", GameStates.Hours,GameStates.Minutes,GameStates.Seconds);
	Hours=Minutes=Seconds=0;

	TextPtr[11] = TimeString;
	sprintf(ScoreString, "%d", AftPopulation/*UserScore*/);
	TextPtr[12] = ScoreString;
	sprintf(OverallString, "%d", GameStates.Score);
	TextPtr[13] = OverallString;

	for (i=0; i<TotalString; i++) 
	{
		TextPos[i] = &(ppos[i][0]);
	}
	TextCol = pcol;
	StringFrame = 0;
	//TextSurface = 0;
	BYChooseTextSurface(0);
}

void BYDisplayPopu(BOOL show, short mode)
{
	char fps[100];
	HDC  hDC;
	int  i;
	IDirectDrawSurface *pdds;
	HFONT hOldFont, hNewFont;
	long int t;

	if (show) 
	{
		pdds = lpDDSText;

		if (pdds==NULL) 
			return;

		if (StringFrame < 40) 
			StringFrame++;
		t = StringFrame;
		t = t % 40;

		if (pdds->GetDC(&hDC)==DD_OK) 
		{

			SetBkColor(hDC, RGB(0, 0, 0));
			SetBkMode(hDC, TRANSPARENT);
			for (i=0; i<TotalString; i++) 
			{
				if (TextPos[i][3]==0) 
				{
					hNewFont = GetStockObject(ANSI_FIXED_FONT);
					hOldFont = SelectObject(hDC, hNewFont);
				} 
				else 
				{
					hNewFont = BYSelectFont(hDC, "System", 0, TextPos[i][3]);
					hOldFont = SelectObject(hDC, hNewFont);
				}
				SetTextColor(hDC, TextCol[i]);
				SetTextAlign(hDC, TextPos[i][2]);
            if (StringFrame<i && i>7) { ; } 
            else 
				{
        			sprintf(fps, TextPtr[i]);
        			TextOut(hDC, TextPos[i][0], TextPos[i][1], fps, lstrlen(fps));
            }
				if (TextPos[i][3]==0) 
				{
					SelectObject(hDC, hOldFont);
            } 
				else 
				{
					SelectObject(hDC, hOldFont);
					DeleteObject(hNewFont);
            }
         }
			SetTextColor(hDC, RGB(0, 255, 0));
         if (mode) 
			{
				hNewFont = GetStockObject(ANSI_FIXED_FONT);
				hOldFont = SelectObject(hDC, hNewFont);

				sprintf(fps, "-");
				TextOut(hDC, (TextPos[StrIdx][0]+ChrIdx*8),
							  (TextPos[StrIdx][1]+8), fps, lstrlen(fps));
				SelectObject(hDC, hOldFont);
			}

			SetBkColor(hDC, RGB(100, 100, 100));
			SetBkMode(hDC, OPAQUE);
			pdds->ReleaseDC(hDC);
		}
	}
}

BOOL BYShowPopulation(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_POPULATION);

	if (GameStates.RobotLose)
	{
		BYLoadOverlay(1, BmpFile[LoserPopulationBackground]);
	}
	else
	{
		BYLoadOverlay(1, BmpFile[WinnerPopulationBackground]);
//		GameStates.CurrentLevel++;
	}
	BYSetO1MainMenuB();
	BYSetPopuText();
	BYDisplayText = BYDisplayPopu;
	DDtext = TRUE;
	EditMode = FALSE;
	nTimer = SetTimer(win, 2, 6000, NULL);
	if(!GameStates.RobotLose)
	{
		GameStates.CurrentLevel++;
		GameStates.CurrentSubmonster=Alpha;
		GameStates.MonsterLose=0;
	}
	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL  StrFlash;

short spos[13][4] =
{
    60, 10, TA_LEFT, 30, 
    
	10, 60, TA_LEFT, 30,     50, 60, TA_LEFT, 30,   
	350, 60, TA_RIGHT, 30,   470, 60, TA_RIGHT, 30,
    
	10, 100, TA_LEFT, 30,    50, 100, TA_LEFT, 30,  
	350, 100, TA_RIGHT, 30,  470, 100, TA_RIGHT, 30, 

    10, 140, TA_LEFT, 30,    50, 140, TA_LEFT, 30,  
	350, 140, TA_RIGHT, 30,  470, 140, TA_RIGHT, 30,      
};

COLORREF scol[13] =
{
    RGB(0, 255, 0),
    RGB(255, 0, 0), RGB(255, 255, 0), RGB(255, 255, 255), RGB(255, 255, 255),
    RGB(255, 0, 0), RGB(255, 255, 0), RGB(255, 255, 255), RGB(255, 255, 255),
    RGB(255, 0, 0), RGB(255, 255, 0), RGB(255, 255, 255), RGB(255, 255, 255)
};

char Top3Title[]= "TOP THREE SCORES";
             
void BYSetTop3ScreenPara(short idx)
{
    short i, j;

    TotalString = 13;

    j = 0;
    TextPtr[j++] = Top3Title;
    for (i=0; i<3; i++) {
        TextPtr[j++] = tmp3[i].No;
        TextPtr[j++] = tmp3[i].name;
        TextPtr[j++] = tmp3[i].score;
        TextPtr[j++] = tmp3[i].time;
    }

    for (i=0; i<TotalString; i++) 
	{
        TextPos[i] = &(spos[i][0]);
    }
    TextCol = scol;
    StringFrame = 0;
    //TextSurface = 0;
	BYChooseTextSurface(0);
    StrFlash = FALSE;
    ChrIdx = 0;
    //
    if (idx>0) 
	{
        StrIdx = 4*idx-2;
        strcpy(YBLineBuffer, "?");
        OldTextPtr = TextPtr[StrIdx];
        TextPtr[StrIdx] = YBLineBuffer;
        StrLen = lstrlen(YBLineBuffer);
    }
}

void BYDisplayTop3(BOOL show, short mode)
{
	char fps[100];
	HDC  hDC;
	int  i;
	IDirectDrawSurface *pdds;
	HFONT hOldFont, hNewFont;
	static int jj=0;

	if (show) 
	{
		pdds = lpDDSText;

		if (pdds==NULL) 
		{
			return;
		}

		if (pdds->GetDC(&hDC)==DD_OK) 
		{
			SetBkColor(hDC, RGB(0, 0, 0));
			SetBkMode(hDC, TRANSPARENT);
			jj++;
			jj = jj%20;
			if (jj==0) StrFlash=!StrFlash;

			for (i=0; i<TotalString; i++) 
			{
				if (TextPos[i][3]==0) 
				{
					hNewFont = GetStockObject(ANSI_FIXED_FONT);
					hOldFont = SelectObject(hDC, hNewFont);
				} 
				else 
				{
					hNewFont = BYSelectFont(hDC, "System", 0, TextPos[i][3]);
					hOldFont = SelectObject(hDC, hNewFont);
				}
				SetTextColor(hDC, TextCol[i]);
				SetTextAlign(hDC, TextPos[i][2]); 
				sprintf(fps, TextPtr[i]);
				if (!(mode && (i==StrIdx) && StrFlash))
				{
        			TextOut(hDC, TextPos[i][0], TextPos[i][1], fps, lstrlen(fps));
				}
				if (TextPos[i][3]==0) 
				{
					SelectObject(hDC, hOldFont);
				} 
				else 
				{
					SelectObject(hDC, hOldFont);
					DeleteObject(hNewFont);
				}
         } // end of for loop
			SetBkColor(hDC, RGB(100, 100, 100));
			SetBkMode(hDC, OPAQUE);
			pdds->ReleaseDC(hDC);
		}
	}
}


BOOL BYShowTop3(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	short retval;

	ISPAGE(pg_SHOW_TOP3);

	BYLoadOverlay(1, BmpFile[WinnerPopulationBackground]);
	BYSetO1MainMenuB();
	YBLoadAllTopRecord(GameVersion);
	retval = YBReachTop3(GameStates.Score);
	BYSetTop3ScreenPara(retval);
	BYDisplayText = BYDisplayTop3;
	if (retval) 
	{
		//LSmode = 1;
		EditMode = TRUE;
		Page = pg_MODIFY_TOPLIST;
		BYKbrdHandler[pg_MODIFY_TOPLIST] = BYKdModifyTopList;
	} 
	else 
	{
		EditMode = FALSE;
		//LSmode = 0;
		nTimer = SetTimer(win, 2, 6000, NULL);
		BYKbrdHandler[pg_SHOW_TOP3] = BYKdShowTop3;
	}
	DDtext  = TRUE;

	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYShowCredits(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_CREDITS);

	MidCmd = MID_STOP;
	BYMidiCenter();
	BYClearOverlaySurface(1);
	BYBlitOnToP(1, TRUE);

	DDtext = FALSE;
	AviSize.top = 80;   //60;
	AviSize.left = 160; //150;
	PlayAVI(win, AVIFiles[7], "movie1", 0, AviSize); 
	BYKbrdHandler[pg_SHOW_CREDITS] = BYKdCreditMovie;

	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYKdCreditMovie(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISKEYDOWN(msg);
	ISPAGE(pg_SHOW_CREDITS);

	CloseAVI(win, "movie1");
	Page = pg_END_MOVIE; 
	PostMessage(win, WM_COMMAND, Page, 0L);

	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYShowEndingMovie(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_END_MOVIE);

	PlayAVI(win, AVIFiles[8], "movie1", 0, AviSize);
	BYKbrdHandler[pg_END_MOVIE] = BYKdEndingMovie;

	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYKdEndingMovie(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISKEYDOWN(msg);
	ISPAGE(pg_END_MOVIE);

	CloseAVI(win, "movie1");
	BYSetPrePageSwitch(Page, pg_NEW_THANKYOU);
	Page = pg_NEW_THANKYOU;
	PostMessage(win, WM_COMMAND, Page, 0L);

	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYShowNewThankYou(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int i,j;

	ISPAGE(pg_NEW_THANKYOU);

	/*
	BYLoadOverlay(1, BmpFile[45]);
	BYSetO1MainMenuB();
	nTimer = SetTimer(win, 2, 6000, NULL);
	*/
	DDtext  = FALSE;
	BYDisplayText = BYDisplayStr;
	for (i=SabreRobot; i<=KaberRobot; i++)
	{
		GameStates.IsRobotDead[i] = 0;
	}
	for (i=Trainer; i<=Tokyo; i++)
	{
		for(j=Alpha;j<=Gamma;++j)
		{
			GameStates.IsMonsterDead[i][j] = 0;
		}
		GameStates.LevelHonor[i]=TRUE;
	}
	GameStates.CurrentLevel = Mojave;
	GameStates.CurrentSubmonster=Alpha;
	GameStates.Score=0;
	GameStates.CurrentRobot=-1;
	GameStates.MonsterLose=0;
	GameStates.RobotLose=0;
	GameStates.IsAutodemo=0;
	GameStates.IsTraining=0;
	GameStates.Is3DMovie=0;
	GameStates.IsNetplay=0;
	GameStates.Hours=0;
	GameStates.Minutes=0;
	GameStates.Seconds=0;
//	OldLevel = GameStates.CurrentLevel;

	BYSetPrePageSwitch(Page, pg_LAST_QUESTION); 
	Page = pg_LAST_QUESTION;
	PostMessage(win, WM_COMMAND, Page, 0L);

	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYFinalExit(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
//	short i;

	ISPAGE(pg_FINAL_EXIT);

	DDtext  = FALSE;
	BYDisplayText = BYDisplayStr;
//	for (i=0; i<5; i++)
//	{
//		RobotStatus[i] = 1;
//	}
	GameStates.CurrentLevel = Mojave;
//	OldLevel = GameStates.CurrentLevel;
	//MidCmd = MID_STOP;
	//PostMessage(win, WM_COMMAND, pg_MIDI_CENTER, 0L);
		
	//Add by Eric 11/15/96
	if (GameStates.IsNetplay)
	{
		EventSndBuf.MsgId = NEW_MSG;
		EventSndBuf.Event = EVENT_GOODBYE;
	}
	//end of Eric

	PostMessage(win, WM_DESTROY, 0, 0L);
	return TRUE;
exit_with_false:
	return FALSE;
}
// WM_KEYDOWN MESSAGE HANDLERS



BOOL BYKdPlayMovie(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
   ISKEYDOWN(msg);
   ISPAGE(pg_PLAY_MOVIE);

   CloseAVI(win, "movie1");
   BYSetPrePageSwitch(Page, pg_SHOW_MOVIE_MENU);
   Page = pg_SHOW_MOVIE_MENU;
   PostMessage(win, WM_COMMAND, Page, 0L);
   return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYKdNextMission(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_NEXTMISSION);
   ISKEYDOWN(msg);


	if (msg==WM_CHAR)
	{
		return FALSE;
	}

	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYKdShowMouseOrConfigure(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
   ISKEYDOWN(msg);

	if (Page != pg_SHOW_MOUSECFG && 
		 Page != pg_SHOW_JOYSKCFG)
		 return FALSE;

	if (msg==WM_CHAR)
	{
		return FALSE;
	}

	KillTimer(win, nTimer);
	Page = pg_SHOW_OPTION_MENU;
	PostMessage(win, WM_COMMAND, Page, 0L);
	return TRUE;
exit_with_false:
	return FALSE;
}



BOOL BYKdLoseOne(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_LOSE_ONE);
   SAMEPAGE();

	BYSetPrePageSwitch(Page, pg_SHOW_CHAR_MENU); 	
	Page = pg_SHOW_CHAR_MENU;
	DDtext  = FALSE;
	BYDisplayText = BYDisplayStr;
	PostMessage(win, WM_COMMAND, Page, 0L);
	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYKbdDefault(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
		
	//Add by Eric 11/15/96
	if (GameStates.IsNetplay)
	{
		EventSndBuf.MsgId = NEW_MSG;
		EventSndBuf.Event = EVENT_GOODBYE;
	}
	//end of Eric

	PostMessage(win, WM_DESTROY, 0, 0L);
	return TRUE;
}

BOOL BYKdShowAviBmp(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
   ISKEYDOWN(msg);
	ISPAGE(pg_SHOW_AVI_BMP);

	BYSetPrePageSwitch(Page, pg_SHOW_MOVIE_MENU); 	
    Page = pg_SHOW_MOVIE_MENU;
    PostMessage(win, WM_COMMAND, Page, 0L);
	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYKdShowTop3(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_TOP3);
	SAMEPAGE();

	KillTimer(win, nTimer);
	DDtext = FALSE;

	BYClearBackSurface();
	BYSurfaceBlt(DDmode0);
	BYSetPrePageSwitch(Page, pg_SHOW_CREDITS); 	
	Page = pg_SHOW_CREDITS;
	PostMessage(win, WM_COMMAND, Page, 0L);
	return TRUE;
exit_with_false:
	return FALSE;
}

short YBScoreSplash(HWND win, UINT msg, WPARAM wparam)
{
	short retval=0;

	if (msg==WM_CHAR) 
	{
		if (isalnum((char)wparam) && (ChrIdx<(8-2))) 
		{
			if (isalpha((char)wparam)) 
			{
				YBLineBuffer[ChrIdx++] = toupper((char)wparam);
			}
			else
			{
				YBLineBuffer[ChrIdx++] = (char)wparam;
			}
            YBLineBuffer[ChrIdx] = 0;
		}
	} // end if msg==WM_CHAR

	if (msg==WM_KEYDOWN) 
	{
		switch(wparam) 
		{
		case VK_ESCAPE:
			retval = 99;
			break;
		case VK_SPACE:
			YBLineBuffer[ChrIdx++] = (char)wparam;
			YBLineBuffer[ChrIdx] = 0;
			break;
		case VK_RETURN:
			strcpy(OldTextPtr, YBLineBuffer);
			//sndPlaySound(WrapSnd1, SND_ASYNC);
			retval = 1;
			//save now
			break;

		case VK_LEFT:
		case VK_BACK:
			if (ChrIdx>0) 
			{
				ChrIdx--;
				YBLineBuffer[ChrIdx] = 0;
				if (YBLineBuffer[0]==0)
					YBLineBuffer[0]='?';
			}
			break;
		case VK_RIGHT:
			if (ChrIdx<(8-2))
				ChrIdx++;
			break;
		}
	}; // end if msg==WM_KEYDOWN 
    
	return retval;
} 

BOOL BYKdModifyTopList(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{ 
	short retval;
// case pg_MODIFY_TOPLIST:  // WM_CHAR
	retval = YBScoreSplash(win, msg, wParam);
	if (retval==PG_BACK)
	{
		EditMode = FALSE;
		DDtext   = FALSE;
		BYClearBackSurface();
		BYSurfaceBlt(DDmode0);
		BYSetPrePageSwitch(Page, pg_SHOW_CREDITS); 
		Page = pg_SHOW_CREDITS;
		PostMessage(win, WM_COMMAND, Page, 0L);
	} 
	else
	if (retval)
	{
		EditMode = FALSE;
		DDtext   = FALSE;

		YBConfirmTopValue();
		YBSaveAllTopRecord(GameVersion);
		BYClearBackSurface();
		BYSurfaceBlt(DDmode0);
		BYSetPrePageSwitch(Page, pg_SHOW_CREDITS); 
		Page = pg_SHOW_CREDITS;
		PostMessage(win, WM_COMMAND, Page, 0L);
	}

// WM_TIMER MESSAGE HANDLERS

	//Liou qinghua add 1996,11,15
	if(PlayAsMonster)
	{
		bMonsterMenu = TRUE;
	}
	/////////////////////////////Liou
	//PostMessage(win, WM_COMMAND, Page, 0L);

	return TRUE;

//exit_with_false:
//	return FALSE;
}


BOOL BYTimeAviDelay(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_AVIPLAY_DELAY);
	IS_WRAPPER_TIMER(wParam);

	KillTimer(win, nTimer);
	BYSetPrePageSwitch(Page, pg_PLAY_MOVIE); 	
	Page = pg_PLAY_MOVIE;
	PostMessage(win, WM_COMMAND, Page, 0L);
	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYTimeM3WinOrLoseBmp(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	IS_WRAPPER_TIMER(wParam);

	KillTimer(win, nTimer);
	BYSetPrePageSwitch(Page, pg_M3_BACKTOMAIN); 
	Page = pg_M3_BACKTOMAIN;
	PostMessage(win, WM_COMMAND, Page, 0L);
	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYTimeSetChar(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SET_CHAR_TIMER);
	IS_WRAPPER_TIMER(wParam);

	KillTimer(win, nTimer);

	BYSetPrePageSwitch(Page, pg_SHOW_GAME_SCREEN); 
	Page = pg_SHOW_GAME_SCREEN;
	PostMessage(win, WM_COMMAND, Page, 0L);

	//Below are just a substitute, which should be removed from the real game
	//BYSetPrePageSwitch(Page, pg_SHOW_MAIN_MENU); 
	//Page = pg_SHOW_MAIN_MENU;
	//PostMessage(win, WM_COMMAND, Page, 0L);
	//Above are just a substitue, which should be removed from the real game
	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYTimeShowNextDemo(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_NEXT_AUTODEMO);
	IS_WRAPPER_TIMER(wParam);

	KillTimer(win, nTimer);
	BYSetPrePageSwitch(Page, pg_SHOW_GOMAN_TITLE); 
	Page = pg_SHOW_GOMAN_TITLE;
	PostMessage(win, WM_COMMAND, Page, 0L);
	return TRUE;

exit_with_false:
	return FALSE;
}


BOOL BYTimeShowWon(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	IS_WRAPPER_TIMER(wParam);
	ISPAGE(pg_REAL_WONMIDDLE);

	// Rem by Eric 11/18/96
	//KillTimer(win, nTimer);
	//BYSetPrePageSwitch(Page, pg_SHOW_POPULATION); 
	//Page = pg_SHOW_POPULATION;
	//PostMessage(win, WM_COMMAND, Page, 0L);
	//

	//Add by Eric 11/18/96
	if (GameStates.IsNetplay)
	{
		KillTimer(win, nTimer);
		//BYSetPrePageSwitch(Page, pg_SHOW_MAIN_MENU); 	
		//Page = pg_SHOW_MAIN_MENU;
		BYSetPrePageSwitch(Page, pg_NET_SHOW_SCORE); 	
		Page = pg_NET_SHOW_SCORE;
		PostMessage(win, WM_COMMAND, Page, 0L);
	}
	else
	{
		KillTimer(win, nTimer);
		BYSetPrePageSwitch(Page, pg_SHOW_POPULATION); 
		Page = pg_SHOW_POPULATION;
		PostMessage(win, WM_COMMAND, Page, 0L);
	}
	//end of Eric

	return TRUE;

exit_with_false:
	return FALSE;
} 


BOOL BYTimeShowPopulation(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_POPULATION);
	IS_WRAPPER_TIMER(wParam);

	KillTimer(win, nTimer);
	DDtext = FALSE;
	if (GameStates.CurrentLevel > Tokyo) 
	{
		BYSetPrePageSwitch(Page, pg_SHOW_TOP3); 
		Page = pg_SHOW_TOP3;
		PostMessage(win, WM_COMMAND, Page, 0L);
	}
	else 
	{
		BYSetPrePageSwitch(Page, pg_SHOW_NEXTMISSION); 
		Page = pg_SHOW_NEXTMISSION;
		PostMessage(win, WM_COMMAND, Page, 0L);
	}
	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYTimeShowTop3(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_TOP3);
	IS_WRAPPER_TIMER(wParam);

	KillTimer(win, nTimer);
	DDtext = FALSE;
	BYClearBackSurface();
	BYSurfaceBlt(DDmode0);
	BYSetPrePageSwitch(Page, pg_SHOW_CREDITS); 
	Page = pg_SHOW_CREDITS;
	PostMessage(win, WM_COMMAND, Page, 0L);
	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYTimeNewThankYou(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_NEW_THANKYOU);
	IS_WRAPPER_TIMER(wParam);

	KillTimer(win, nTimer);
	BYSetPrePageSwitch(Page, pg_FINAL_EXIT); 
	Page = pg_FINAL_EXIT;
	PostMessage(win, WM_COMMAND, Page, 0L);
	return TRUE;

exit_with_false:
	return FALSE;
}
//
BOOL BYDefaultHandler(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

BOOL BYDefaultMsHandler(HWND win)
{
	return TRUE;
}

// ENTER3D DELAY BEGIN
BOOL BYDoEnter3DDelay(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_ENTER3D_DELAY);

	MidCmd = MID_STOP;
	BYMidiCenter();
	
	nTimer = SetTimer(win, 2, 500, NULL);
//	nTimer = SetTimer(win, 2, 1000, NULL);

	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYTimeEnterDelay(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_ENTER3D_DELAY);
	IS_WRAPPER_TIMER(wParam);

	sndPlaySound(NULL, SND_ASYNC);

/*
   if (GameStates.IsNetplay && !JSCSwappedSelectionInfo())
   {
	   nTimer = SetTimer(win, 2, 100, NULL);
      return FALSE;
   }
   else
		KillTimer(win, nTimer);
*/

	Page = pg_SETUP_SNDSYSTEM;
	PostMessage(win, WM_COMMAND, Page, 0L);
	return TRUE;

exit_with_false:
	return FALSE;
}

// ENTER3D DELAY END
// MCI EVENT HANDLER
BOOL BYMciNotifyHandler(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (wParam) 
	{
	case MCI_NOTIFY_SUCCESSFUL:
		if (Page == pg_INTRO_MOVIE)
		{
			CloseAVI(win, "movie1");
			ShowCursor(FALSE);

			di.CreateDIMsDevice(TRUE);
		
			di.CreateMsSurface();
			di.LoadCursorBmp("cursor.bmp");
			di.SetMsCursorColorKey(TRUE, RGB(0,0,0));
			di.SelectAniCursor(ani_cursor);
			//di.SetMsTotalAnis(7);
			//di.SetMsAniSpeed(3);
			//di.SetMsCursorInfo(5, 5, 10, 10);
			di.SetMsTotalAnis(1);
			di.SetMsAniSpeed(1);
			di.SetMsCursorInfo(8, 8, 16, 16);

			di.TurnOnMsCursor(TRUE);

			BYSetPrePageSwitch(Page, pg_SHOW_MAIN_MENU); 	
			Page = pg_SHOW_MAIN_MENU;
			PostMessage(win, WM_COMMAND, Page, 0L);
		}
		else
		if (Page == pg_MISSION_AVI)
		{
			CloseAVI(win, "movie1");
			if(PlayAsMonster)
			{
				bMonsterMenu = TRUE;
			}
			BYSetPrePageSwitch(Page, pg_SHOW_CHAR_MENU); 	
			Page = pg_SHOW_CHAR_MENU;
			PostMessage(win, WM_COMMAND, Page, 0L);
		}
		else
		if (Page == pg_PLAY_MOVIE) 
		{
			CloseAVI(win, "movie1");
			if (whichavi!=1 && whichavi!=8)
			{
	    		BYSetPrePageSwitch(Page, pg_SHOW_AVI_BMP);
				Page = pg_SHOW_AVI_BMP;
			}
			else
			{
    			BYSetPrePageSwitch(Page, pg_SHOW_MOVIE_MENU);
				Page = pg_SHOW_MOVIE_MENU;
			}
			PostMessage(win, WM_COMMAND, Page, 0L);
		}
		else
		if (Page == pg_REAL_WONFINAL)
		{
			CloseAVI(win, "movie1");

			if (GameStates.IsNetplay)
			{
				BYSetPrePageSwitch(Page, pg_NET_SHOW_SCORE); 	
				Page = pg_NET_SHOW_SCORE;
				PostMessage(win, WM_COMMAND, Page, 0L);
				bBYRenderingIsOK = TRUE;
			}
			else
			{
				BYSetPrePageSwitch(Page, pg_SHOW_POPULATION); 
				Page = pg_SHOW_POPULATION;
				PostMessage(win, WM_COMMAND, Page, 0L);
				bBYRenderingIsOK = TRUE;
			}
		}
		else
		if (Page == pg_SHOW_LOSE_ALL)
		{
			CloseAVI(win, "movie1");

			BYSetPrePageSwitch(Page, pg_SHOW_CREDITS); 	
			Page = pg_SHOW_CREDITS;
			PostMessage(win, WM_COMMAND, Page, 0L);
			bBYRenderingIsOK = TRUE;
		}
		else
      if (Page == pg_SHOW_CREDITS) 
		{  // any key
			CloseAVI(win, "movie1");
			Page = pg_END_MOVIE; 
			PostMessage(win, WM_COMMAND, Page, 0L);
		}
		else
		if (Page == pg_END_MOVIE) 
		{
			CloseAVI(win, "movie1");
			BYSetPrePageSwitch(Page, pg_NEW_THANKYOU);
			Page = pg_NEW_THANKYOU;
			PostMessage(win, WM_COMMAND, Page, 0L);
			break;
		}
		break;
	}
	return TRUE;
}
 
BOOL BYShowNextMission(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_NEXTMISSION);

	di.TurnOnMsCursor(FALSE);

	BYLoadOverlay(1, BmpFile[(GameStates.CurrentLevel+LevelInfo-1)]);
	BYSetO1MainMenuB();
	//nTimer = SetTimer(win, 2, 6000, NULL);

	if (AviLevel!=GameStates.CurrentLevel)
	{	
		MidCmd = MID_STOP;
		BYMidiCenter();
	   nTimer = SetTimer(win, 2, 500, NULL);
		bAviTimer = TRUE;
	}
	else
	{
		if(PlayAsMonster)
		{
			bMonsterMenu = TRUE;
		}

		BYSetPrePageSwitch(Page, pg_SHOW_CHAR_MENU); 	
		Page = pg_SHOW_CHAR_MENU;
		PostMessage(win, WM_COMMAND, Page, 0L);
	}

	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYTimeNextMission(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SHOW_NEXTMISSION);
	IS_WRAPPER_TIMER(wParam);

	KillTimer(win, nTimer);
	BYSetPrePageSwitch(Page, pg_MISSION_AVI); 	
	Page = pg_MISSION_AVI;
	PostMessage(win, WM_COMMAND, Page, 0L);

	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYMissionAvi(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_MISSION_AVI);

	if (AviLevel!=GameStates.CurrentLevel)
	{
		bAviTimer = FALSE;
		PlayAVI(win, AVIFiles[GameStates.CurrentLevel], "movie1", 2, AviSize);
		AviLevel = GameStates.CurrentLevel;		
	}

	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYKdMissionAvi(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_MISSION_AVI);
   ISKEYDOWN(msg);

	if (msg==WM_CHAR)
	{
		return FALSE;
	}

	if (!bAviTimer)
	{
		CloseAVI(win, "movie1");
		if(PlayAsMonster)
		{
			bMonsterMenu = TRUE;
		}
		BYSetPrePageSwitch(Page, pg_SHOW_CHAR_MENU); 	
		Page = pg_SHOW_CHAR_MENU;
		PostMessage(win, WM_COMMAND, Page, 0L);
	} 

	return TRUE;
exit_with_false:
	return FALSE;
}

//
IDirectDrawPalette * BYDDLoadPalette(IDirectDraw *pdd)
{
    IDirectDrawPalette* ddpal;
    int                 i;
    PALETTEENTRY        ape[256];
    FILE    *in;

	char  filename[127];

	strcpy(filename, BmpPath);
	strcat(filename, "\\");
	strcat(filename, ConstructLevelName("pal.act"));
	
	in = fopen(filename, "rb");

    if (in == NULL) 
	{
		BYDumpInfo("********************");
		BYDumpInfo("couldn't load palette:");
		BYDumpInfo(filename);
		BYDumpInfo("*********************");
    	return NULL;
	}
    
    for (i=0; i<256; i++)
    {
	    fread(&(ape[i].peRed), sizeof(unsigned char), 1, in);
	    fread(&(ape[i].peGreen), sizeof(unsigned char), 1, in);
	    fread(&(ape[i].peBlue), sizeof(unsigned char), 1, in);
		 //ape[i].peFlags = PC_RESERVED;
		 ape[i].peFlags = D3DPAL_READONLY; //NULL;
    }

	fclose(in);

    pdd->CreatePalette(DDPCAPS_8BIT, ape, &ddpal, NULL);
	if(!ddpal)
	{
		BYDumpInfo("********************");
		BYDumpInfo("couldn't create palette from:");
		BYDumpInfo(filename);
		BYDumpInfo("*********************");
	}

    return ddpal;
}

//
COLORREF ColorSet[6][2] =
{
    RGB(255, 255, 255),   // text
    RGB(255, 255, 0),     // number
    RGB(0, 255, 0),
    RGB(255, 0, 0),
    RGB(255, 0, 0),
    RGB(0, 255, 0),
    RGB(255, 0, 0),
    RGB(0, 255, 0),
    RGB(255, 255, 0),
    RGB(0, 255, 0),
    RGB(255, 0, 0),
    RGB(0, 255, 0)
};

int TimePopuCo[3][4] =
{
   // debug mode display starting coordinates
   10, 1,   // timer
   580, 1,  // population
   // 640x480
   10, 1,   // timer
   580, 1,  // population
   // 320x240
   10, 1,   // timer
   255, 1   // population 268,1
};

extern "C" RLValue HuntDesire, MissionDesire, EvadeDesire, GenericDesire, DefendDesire;
extern "C" int MonsterGoal;
extern "C" RLValue Rage, Fear, Boredom, Joy;

#define HuntRobot 0
#define HuntMissionBuilding 1
#define HuntAnyBuilding 2
#define EvadeRobot 3
#define DefendAgainstRobot 4

void JSCShowAEInfo(BOOL show)
{
	char fps2[150]; 
	HDC  hDC;
	IDirectDrawSurface *pdds;

	if (show) 
	{
		//sprintf(fps4, "%07d", Population);
		//sprintf(fps5, "x");

		pdds = d3dappi.lpBackBuffer;  

		if (pdds->GetDC(&hDC)==DD_OK) 
		{
			SetBkColor(hDC, NULL);
			SetBkMode(hDC, TRANSPARENT);
         
         sprintf(fps2, "Hunt the Robot desire: %f", HuntDesire);        
         if (MonsterGoal==HuntRobot)
            SetTextColor(hDC, RGB(255, 0, 0));
         else
            SetTextColor(hDC, RGB(255, 255, 255));
			TextOut(hDC, 20, 40, fps2, lstrlen(fps2));

         sprintf(fps2, "Mission target desire: %f", MissionDesire);        
         if (MonsterGoal==HuntMissionBuilding)
            SetTextColor(hDC, RGB(255, 0, 0));
         else
            SetTextColor(hDC, RGB(255, 255, 255));
			TextOut(hDC, 20, 60, fps2, lstrlen(fps2));

         sprintf(fps2, "Evade the Robot desire: %f", EvadeDesire);        
         if (MonsterGoal==EvadeRobot)
            SetTextColor(hDC, RGB(255, 0, 0));
         else
            SetTextColor(hDC, RGB(255, 255, 255));
			TextOut(hDC, 20, 80, fps2, lstrlen(fps2));

         sprintf(fps2, "Generic building desire: %f", GenericDesire);        
         if (MonsterGoal==HuntAnyBuilding)
            SetTextColor(hDC, RGB(255, 0, 0));
         else
            SetTextColor(hDC, RGB(255, 255, 255));
			TextOut(hDC, 20, 100, fps2, lstrlen(fps2));

         sprintf(fps2, "Defense desire: %f", DefendDesire);        
         if (MonsterGoal==DefendAgainstRobot)
            SetTextColor(hDC, RGB(255, 0, 0));
         else
            SetTextColor(hDC, RGB(255, 255, 255));
			TextOut(hDC, 20, 120, fps2, lstrlen(fps2));

         if (RMode == 1)
         {
            sprintf(fps2, "Rage: %f", Rage);        
            SetTextColor(hDC, RGB(0, 255, 0));
			   TextOut(hDC, 480, 40, fps2, lstrlen(fps2));

            sprintf(fps2, "Fear: %f", Fear);        
            SetTextColor(hDC, RGB(0, 255, 0));
			   TextOut(hDC, 480, 60, fps2, lstrlen(fps2));

            sprintf(fps2, "Boredom: %f", Boredom);        
            SetTextColor(hDC, RGB(0, 255, 0));
			   TextOut(hDC, 480, 80, fps2, lstrlen(fps2));

            sprintf(fps2, "Joy: %f", Joy);        
            SetTextColor(hDC, RGB(0, 255, 0));
			   TextOut(hDC, 480, 100, fps2, lstrlen(fps2));
         }
         pdds->ReleaseDC(hDC);
		}
	}
}

void YBShowTimer320(BOOL show)
{
	char fps2[15], fps4[15], fps5[15]; 
	HDC  hDC;
	IDirectDrawSurface *pdds;
	short TimerX, TimerY, PopuX, PopuY;
	static long popu=0;

	TimerX =  TimePopuCo[RMode][0];    
	TimerY =  TimePopuCo[RMode][1];
	PopuX  =  TimePopuCo[RMode][2];
	PopuY  =  TimePopuCo[RMode][3];

	if (!ShowTimer) 
	{
		return;
	}

	if (YBTimerFlag && show) 
	{
		sprintf(fps2, "%02d:%02d:%02d", Hours,Minutes,Seconds);        
		sprintf(fps4, "%07d", Population);
		sprintf(fps5, "x");

		if (sStretch.bStretch)
				pdds = d3dappi.lpBackBuffer2;  
		else
			pdds = d3dappi.lpBackBuffer;  

		if (pdds->GetDC(&hDC)==DD_OK) 
		{
			SetBkColor(hDC, NULL);
			SetBkMode(hDC, TRANSPARENT);
			if (GameStates.CurrentLevel==Trainer)
			{
			    SetTextColor(hDC, ColorSet[0][0]);
			}
         else
			{
			    SetTextColor(hDC, ColorSet[(GameStates.CurrentLevel-1)][1]);
			}
			TextOut(hDC, TimerX, TimerY, fps2, lstrlen(fps2));
         TextOut(hDC, PopuX, PopuY, fps4, lstrlen(fps4));
			pdds->ReleaseDC(hDC);
		}
	}
}
//
void YBShowTimer512(BOOL show)
{
   char fps2[15], fps4[15], fps5[5];
   HDC  hDC;
   IDirectDrawSurface *pdds;
   short TimerX, TimerY, PopuX, PopuY;
   static long popu=0;

   TimerX = 10;  
   TimerY = 1; 
   PopuX  = 450;  
   PopuY  = 1;  

   if (YBTimerFlag && show) 
   {
      //sprintf(fps1, "TIME:");
      sprintf(fps2, "%02d:%02d:%02d", Hours,Minutes,Seconds);
      //sprintf(fps3, "POPULATION:");
      sprintf(fps4, "%07d", Population);
      sprintf(fps5, "x");

      pdds = d3dappi.lpBackBuffer;  

      if (pdds->GetDC(&hDC)==DD_OK) 
      {
         SetBkColor(hDC, NULL);
         SetBkMode(hDC, TRANSPARENT);
         SetTextColor(hDC, RGB(255, 255, 255));
         //TextOut(hDC, TimerX, TimerY, fps1, lstrlen(fps1));
         //TextOut(hDC, PopuX, PopuY, fps3, lstrlen(fps3));
         SetTextColor(hDC, RGB(255, 255, 0));
         TextOut(hDC, TimerX, TimerY, fps2, lstrlen(fps2));
         TextOut(hDC, PopuX, PopuY, fps4, lstrlen(fps4));
         pdds->ReleaseDC(hDC);
		}
	}
}

//
void YBShowTimer640(BOOL show)
{
   char fps1[15], fps2[15], fps3[15], fps4[15], fps5[5];
   HDC  hDC;
   IDirectDrawSurface *pdds;
   short TimerX, TimerY, PopuX, PopuY;
   static long popu=0;

   TimerX = 10;  //548;  
   TimerY = 6; 
   PopuX  = 548;  
   PopuY  = 6;   //35;  

   if (YBTimerFlag && show) 
   {
      sprintf(fps1, "TIME:");
      sprintf(fps2, "%02d:%02d:%02d", Hours,Minutes,Seconds);
      sprintf(fps3, "POPULATION:");
      sprintf(fps4, "%07d", Population);
      sprintf(fps5, "x");

      pdds = d3dappi.lpBackBuffer;    

      if (pdds->GetDC(&hDC)==DD_OK) 
      {
         SetBkColor(hDC, NULL);
         SetBkMode(hDC, TRANSPARENT);
         SetTextColor(hDC, RGB(255, 255, 255));
         TextOut(hDC, TimerX, TimerY, fps1, lstrlen(fps1));
         TextOut(hDC, PopuX, PopuY, fps3, lstrlen(fps3));
         SetTextColor(hDC, RGB(255, 255, 0));
         TextOut(hDC, TimerX, TimerY+11, fps2, lstrlen(fps2));
         TextOut(hDC, PopuX, PopuY+11, fps4, lstrlen(fps4));
         pdds->ReleaseDC(hDC);
		}
	}
}

//
void YBSetSubTitle1(int Vmode, char *str1, COLORREF color)
{
	// Vmode is obsolete

    // subl = subtitle's length
    // subc = subtitle's color
    // subt = subtitle's display counter
    // substart = subtitle's start position
    // subx, suby = subtitle's current position

	strcpy(sSubTitle1, str1);
	subl1 = lstrlen(sSubTitle1); 
	subActualLength1 = subl1*8; 
	subc1 = color; 
	subt1 = 0;

	if (subl1==0)
	{
		return;
	}

	switch (VM_W3D)
	{
	case 640:
		if (VSize==4)
		{
			subx1 = 640;
			suby1 = 440; //356;
			substart = 640;
		}
		else
		{
			subx1 = 487;
			suby1 = 430; //356;
			substart = 487;
		}
		break;
	case 512:
		if (VSize==4)
		{
			subx1 = 512;
			suby1 = 340;
			substart = 512;
		}
		else
		{
			subx1 = 390;
			suby1 = 340; //356;
			substart = 487;
		}
		break;
	case 320:
		subx1 = 320;
		suby1 = 192;
		substart = 320;
		break;
	}
}

void YBSetSubTitle2(int Vmode, char *str2, COLORREF color)
{
	// Vmode is obsolete

	strcpy(sSubTitle2, str2);
	subl2 = lstrlen(sSubTitle2); 
	subActualLength2 = subl2*8;       
	subc2 = color; 
	subt2 = 0;
         
	if (subl2==0)
	{
		return;
	}

	switch(VM_W3D)
	{
	case 640:
		if (VSize==4)
		{
			subx2 = 640;
			suby2 = 450; 
			substart = 640;
		}
		else
		{
			subx2 = 487;
			suby2 = 442; //367;
			substart = 487;
		}
		break;
	case 512:
		if (VSize==4)
		{
			subx2 = 512;
			suby2 = 352;
			substart = 512;
		}
		else
		{
			subx2 = 390;
			suby2 = 352; //356;
			substart = 487;
		}
		break;
	case 320:
		subx2 = 320;
		suby2 = 203;
		substart = 320;
		break;
	}
          
}

void YBSetSubTitle3(int Vmode, char *str3, COLORREF color)
{
	// Vmode is obsolete

	strcpy(sSubTitle3, str3);
	subl3 = lstrlen(sSubTitle3); 
	subActualLength3 = subl3*8;       
	subc3 = color;
	subt3 = 0;
          
	if (subl3==0)
	{
		return;
	}

	switch(VM_W3D)
	{
	case 640:
		if (VSize==4)
		{
			subx3 = 640;
			suby3 = 460;//378;
			substart = 640;
		}
		else
		{
			subx3 = 487;
			suby3 = 454;//378;
			substart = 487;
		}
		break;
	case 512:
		if (VSize==4)
		{
			subx3 = 512;
			suby3 = 364;
			substart = 512;
		}
		else
		{
			subx3 = 390;
			suby3 = 364; //356;
			substart = 487;
		}
		break;
	case 320:
		subx3 = 320; //243;
		suby3 = 214;
		substart = 320;
		break;
	}

}

void YBDisplaySubTitle(BOOL show)
{
	HDC  hDC;
	IDirectDrawSurface *pdds;
	BOOL turnon;
	RECT v6rc = {154,429,486,471};
	RECT v5rc = {122,343,390,377};

	if (!ShowSub || !show)
	{
		return;
	}

	turnon = (subt1<2 || subt2<2 || subt3<2);
	if (!turnon && VM_W3D==320)
	{
		YBTimerFlag = TRUE;               
	}
 
	if (fgShowSubTitle || turnon) 
	{
		pdds = d3dappi.lpBackBuffer;

    	if (pdds->GetDC(&hDC)==DD_OK) 
		{
			SelectObject(hDC, hGameFont);
			SetBkColor(hDC, NULL);
			SetBkMode(hDC, TRANSPARENT);
			SetTextColor(hDC, subc1);
			if (VM_W3D==640 && VSize!=4)
			{
				ExtTextOut(hDC, subx1, suby1, ETO_CLIPPED, 
					        &v6rc, sSubTitle1, subl1, NULL);
			}
			else
			if (VM_W3D==512 && VSize!=4)
			{
				ExtTextOut(hDC, subx1, suby1, ETO_CLIPPED, 
					        &v5rc, sSubTitle1, subl1, NULL);
			}
			else
			{
				TextOut(hDC, subx1, suby1, sSubTitle1, subl1);
			}
			SetTextColor(hDC, subc2);
			if (VM_W3D==640 && VSize!=4)
			{
				ExtTextOut(hDC, subx2, suby2, ETO_CLIPPED, 
					        &v6rc, sSubTitle2, subl2, NULL);
			}
			else
			if (VM_W3D==512 && VSize!=4)
			{
				ExtTextOut(hDC, subx2, suby2, ETO_CLIPPED, 
					        &v5rc, sSubTitle2, subl2, NULL);
			}
			else
			{
				TextOut(hDC, subx2, suby2, sSubTitle2, subl2);
			}
			SetTextColor(hDC, subc3);
			if (VM_W3D==640 && VSize!=4)
			{
				ExtTextOut(hDC, subx3, suby3, ETO_CLIPPED, 
					        &v6rc, sSubTitle3, subl3, NULL);
			}
			else
			if (VM_W3D==512 && VSize!=4)
			{
				ExtTextOut(hDC, subx3, suby3, ETO_CLIPPED, 
					        &v5rc, sSubTitle3, subl3, NULL);
			}
			else
			{
				TextOut(hDC, subx3, suby3, sSubTitle3, subl3);
			}
			pdds->ReleaseDC(hDC);
    	} 
		else
		{
			BYDumpInfo("Cannot get DC");
		}
		if (subt1<2) subx1-=2;
		if (subt2<2) subx2-=2;
		if (subt3<2) subx3-=2; 

		if ((subx1+subActualLength1)<0 && subt1<2) 
		{
			subx1 = substart;
			subt1++;
		}
		if ((subx2+subActualLength2)<0 && subt2<2) 
		{
			subx2 = substart;
			subt2++;
		}
		if ((subx3+subActualLength3)<0 && subt3<2) 
		{
			subx3 = substart;
			subt3++;
		}
		if (subt1>=2 && subt2>=2 && subt3>=2)
		{
			//DumpFlag[1] = 0;
		}
	} 
}
//
typedef struct _METER_
{
   RECT size;
   RECT cval;  // current value
   short cRed, cGreen, cBlue;
   short ilife;
   int olife;
} METER;

static METER m320[4] =
{
   0, 143, 52, 144, 0, 143, 52, 144, 255, 255, 255, 100, 100,
   0, 143, 52, 144, 0, 143, 52, 144, 255, 255, 255, 100, 65536,
   0, 145, 52, 146, 0, 145, 52, 146, 255,   0,   0, 100, 100,
   0, 145, 52, 146, 0, 145, 52, 146, 255,   0,   0, 100, 65536
};

static METER m512[4] = 
{
   0, 43, 85, 46, 0, 43, 85, 46, 255, 255, 255, 100, 100,
   0, 43, 85, 46, 0, 43, 85, 46, 255, 255, 255, 100, 65536,
   0, 47, 85, 50, 0, 47, 85, 50, 255,   0,   0, 100, 100,
   0, 47, 85, 50, 0, 47, 85, 50, 255,   0,   0, 100, 65536
};

static METER m640[4] = 
{
   0, 43, 105, 46, 0, 43, 105, 46, 255, 255, 255, 100, 100,
   0, 43, 105, 46, 0, 43, 105, 46, 255, 255, 255, 100, 65536,
   0, 47, 105, 50, 0, 47, 105, 50, 255,   0,   0, 100, 100,
   0, 47, 105, 50, 0, 47, 105, 50, 255,   0,   0, 100, 65536
};

#define START3_POS 1
#define START5_POS 1
#define START6_POS 1
#define RIGHT3_POS 189
#define RIGHT5_POS 318
#define RIGHT6_POS 399

char fpS1[20], fpS2[20], fpS3[20], fpS4[20];
char fpS5[20], fpS6[20], fpS7[20], fpS8[20];

void YBDisplayMeter640(BOOL show)
{
   short i, j;
	short Epsilon, Delta, MaxBarMovement;
   IDirectDrawSurface *pdds;
   HDC  hDC;
	HRESULT ddrval;

   if (!show || !ShowMeter) 
   {
      return;
   }
 	MaxBarMovement=(short)DiffFrame;

   m640[0].olife = RobotLife;
   m640[1].olife = (RobotEngy*100)/65536;
   m640[2].olife = MnstLife;
   m640[3].olife = (MnstEngy*100)/65536;
        
   pdds = d3dappi.lpBackBuffer;   

   if (pdds->GetDC(&hDC)==DD_OK) 
   {
		SetBkColor(hDC, NULL);
      SetBkMode(hDC, TRANSPARENT);
      SetTextColor(hDC, RGB(255, 255, 255));
      TextOut(hDC, 90, 2, fpS1, lstrlen(fpS1));
      TextOut(hDC, 90, 20, fpS2, lstrlen(fpS2));
      //TextOut(hDC, 135, 35, fpS3, lstrlen(fpS3));
      TextOut(hDC, 396, 2, fpS4, lstrlen(fpS4));
      TextOut(hDC, 396, 20, fpS5, lstrlen(fpS5));
      //TextOut(hDC, 396, 35, fpS6, lstrlen(fpS6));
      pdds->ReleaseDC(hDC);
	}


   for (i=0; i<4; i++) 
   {
		m640[i].ilife = ((m640[i].size.right-m640[i].size.left)*m640[i].olife)/100;

      if (i==0 || i==1) 
      {
			Delta=(m640[i].ilife+m640[i].size.left)-m640[i].cval.right;
			if (Delta>0)
			{
				Epsilon=(Delta+1)/2;
				if(Epsilon>MaxBarMovement)
					Epsilon=MaxBarMovement;
				m640[i].cval.right+=Epsilon;
			}
			else 
         {
				if (Delta<0)
				{
					Epsilon=(-Delta) + 1;
					Epsilon/=2;
					if(Epsilon>MaxBarMovement)
						Epsilon=MaxBarMovement;
					m640[i].cval.right-=MaxBarMovement;
				}
         }
			if (m640[i].cval.right>=m640[i].size.left && 
				m640[i].cval.right<=m640[i].size.right)
			{
				//OutputDebugString("*\n");
				if (m640[i].cval.right<=0)
				{
					//_RPT2(_CRT_WARN, "m640[%d].cval.right = %\n", 
					//	   i, m640[i].cval.right);
					Dump640.flag[START6_POS+i]=0;
				}
				else
				{
					Dump640.src[START6_POS+i].right = m640[i].cval.right;
					Dump640.flag[START6_POS+i]=1;
				}
			}
      }
 
      if (i==2 || i==3) 
      {
			Delta=(m640[i].size.right-m640[i].ilife)-m640[i].cval.left;
			if (Delta>0)
			{
				Epsilon=(Delta+1)/2;
				if(Epsilon>MaxBarMovement)
					Epsilon=MaxBarMovement;
				m640[i].cval.left+=Epsilon;
			}
			else 
			{
				if (Delta<0)
				{
					Epsilon=(-Delta) + 1;
					Epsilon/=2;
					if(Epsilon>MaxBarMovement)
						Epsilon=MaxBarMovement;
					m640[i].cval.left-=Epsilon;
				}
			}
         if (m640[i].cval.left>=m640[i].size.left && 
				m640[i].cval.left<=m640[i].size.right) 
			{
				if (m640[i].cval.left>=m640[i].size.right)
				{
					Dump640.flag[START6_POS+i] = 0;
				}
				else
				{
					Dump640.src[START6_POS+i].left = m640[i].cval.left;
					Dump640.des[START6_POS+i][0] = RIGHT6_POS+m640[i].cval.left;
					Dump640.flag[START6_POS+i] = 1;
				}
         }
      }	 
    } // end for loop 

	for (i=0; i<S4TotalItems; i++) 
	{
		if (S4ItemFlag[i]) 
		{
    		while(1) 
			{
        		ddrval = d3dappi.lpBackBuffer->BltFast(S4xy[i*2], S4xy[i*2+1], 
        		           lpDDSOverlay[2], &S4rect[i], S4DrawMode);
        		if (ddrval==DD_OK) 
					break;
				else
				{
					if (HandleException(ddrval))
					{
						if (j>5) 
							break;
						j++;
					}
				}

		   } 
		}
   } 
}
//
void YBDisplayMeter512(BOOL show)
{
   short i, j;
	short Epsilon, Delta, MaxBarMovement;
   IDirectDrawSurface *pdds;
   HDC  hDC;
	HRESULT ddrval;

   if (!show || !ShowMeter) 
   {
      return;
   }
	MaxBarMovement=(short)DiffFrame;
 
	j = 0;
	m512[0].olife = RobotLife;
	m512[1].olife = (RobotEngy*100)/65536;
	m512[2].olife = MnstLife;
	m512[3].olife = (MnstEngy*100)/65536;
        
   pdds = d3dappi.lpBackBuffer;   

   if (pdds->GetDC(&hDC)==DD_OK) 
   {
		SetBkColor(hDC, NULL);
      SetBkMode(hDC, TRANSPARENT);
      SetTextColor(hDC, RGB(255, 255, 255));
      TextOut(hDC, 88, 2, fpS1, lstrlen(fpS1));
      TextOut(hDC, 88, 18, fpS2, lstrlen(fpS2));
      //TextOut(hDC, 135, 35, fpS3, lstrlen(fpS3));
      TextOut(hDC, 316, 2, fpS4, lstrlen(fpS4));
      TextOut(hDC, 316, 18, fpS5, lstrlen(fpS5));
      //TextOut(hDC, 396, 35, fpS6, lstrlen(fpS6));
      pdds->ReleaseDC(hDC);
	}


   for (i=0; i<4; i++) 
   {
		m512[i].ilife = ((m512[i].size.right-m512[i].size.left)*m512[i].olife)/100;

      if (i==0 || i==1) 
      {
			Delta = (m512[i].ilife+m512[i].size.left)-m512[i].cval.right;
			if (Delta>0)
			{
				Epsilon=(Delta+1)/2;
				if(Epsilon>MaxBarMovement)
					Epsilon=MaxBarMovement;
				m512[i].cval.right+=Epsilon;
			}
			else 
			{
				if (Delta<0)
				{
					Epsilon=(-Delta) + 1;
					Epsilon/=2;
					if(Epsilon>MaxBarMovement)
						Epsilon=MaxBarMovement;
					m512[i].cval.right-=Epsilon;
				}
			}
			if (m512[i].cval.right>=m512[i].size.left && 
				m512[i].cval.right<=m512[i].size.right)
			{
				if (m512[i].cval.right<=0)
				{
					//_RPT2(_CRT_WARN, "m512[%d].cval.right = %\n", 
					//	   i, m512[i].cval.right);
					Dump512.flag[START5_POS+i]=0;
				}
				else
				{
					Dump512.src[START5_POS+i].right = m512[i].cval.right;
					Dump512.flag[START5_POS+i]=1;
				}
			}
      }
 
      if (i==2 || i==3) 
      {
			Delta=(m512[i].size.right-m512[i].ilife)-m512[i].cval.left;
			if (Delta>0)
			{
				Epsilon=(Delta+1)/2;
				if(Epsilon>MaxBarMovement)
					Epsilon=MaxBarMovement;
				m512[i].cval.left+=Epsilon;
			}
			else 
			{
				if (Delta<0)
				{
					Epsilon=(-Delta) + 1;
					Epsilon/=2;
					if(Epsilon>MaxBarMovement)
						Epsilon=MaxBarMovement;
					m512[i].cval.left-=Epsilon;
				}
			}
         if (m512[i].cval.left>=m512[i].size.left && 
				m512[i].cval.left<=m512[i].size.right) 
			{
				if (m512[i].cval.left>=m512[i].size.right)
				{
					Dump512.flag[START5_POS+i] = 0;
				}
				else
				{
					Dump512.src[START5_POS+i].left = m512[i].cval.left;
					Dump512.des[START5_POS+i][0] = RIGHT5_POS+m512[i].cval.left;
					Dump512.flag[START5_POS+i] = 1;
				}
         }
      }	 
    } // end for loop 

	for (i=0; i<S4TotalItems; i++) 
	{
		if (S4ItemFlag[i]) 
		{
    		while (1) 
			{
        		ddrval = d3dappi.lpBackBuffer->BltFast(S4xy[i*2], S4xy[i*2+1], 
        		           lpDDSOverlay[2], &S4rect[i], S4DrawMode);
        		if (ddrval==DD_OK) 
					break;
				else
				{
					if (HandleException(ddrval))
					{
						if (j>5) break;
						j++;
					}
				}
		   } 
		}
   } 
}

//
void YBDisplayMeter320(BOOL show)
{
	short i, j;
	short Epsilon, Delta, MaxBarMovement;
	HRESULT ddrval;

   if (!show || !ShowMeter) 
   {
      return;
   }
	MaxBarMovement=(short)DiffFrame;

	j = 0;
	m320[0].olife = RobotLife;
	m320[1].olife = (RobotEngy*100)/65536;
	m320[2].olife = MnstLife;
	m320[3].olife = (MnstEngy*100)/65536; 

 
	for (i=0; i<4; i++) 
	{
		m320[i].ilife = ((m320[i].size.right-m320[i].size.left)*m320[i].olife)/100;

		if (i==0 || i==1) // Robot life and energy bar
		{
			Delta = (m320[i].ilife+m320[i].size.left)-m320[i].cval.right;
			if (Delta>0)
			{
				Epsilon=(Delta+1)/2;
				if(Epsilon>MaxBarMovement)
					Epsilon=MaxBarMovement;
				m320[i].cval.right+=Epsilon;
			}
			else
			{
				if (Delta<0)
				{
					Epsilon=(-Delta) + 1;
					Epsilon/=2;
					if(Epsilon>MaxBarMovement)
						Epsilon=MaxBarMovement;
					m320[i].cval.right-=Epsilon;
				}
			}
			if (m320[i].cval.right>=m320[i].size.left && 
				m320[i].cval.right<=m320[i].size.right)
			{
				if (m320[i].cval.right<=0)
				{
					Dump320.flag[START3_POS+i]=0;
				}
				else
				{
					Dump320.src[START3_POS+i].right = m320[i].cval.right;
					Dump320.flag[START3_POS+i]=1;
				}
			}
		}

		if (i==2 || i==3) 
		{
			Delta=(m320[i].size.right-m320[i].ilife)-m320[i].cval.left;
			if (Delta>0)
			{
				Epsilon=(Delta+1)/2;
				if(Epsilon>MaxBarMovement)
					Epsilon=MaxBarMovement;
				m320[i].cval.left+=Epsilon;
			}
			else
			{
				if (Delta<0)
				{
					Epsilon=(-Delta) + 1;
					Epsilon/=2;
					if(Epsilon>MaxBarMovement)
						Epsilon=MaxBarMovement;
					m320[i].cval.left-=Epsilon;
				}
			}
         if (m320[i].cval.left>=m320[i].size.left && 
				m320[i].cval.left<=m320[i].size.right) 
			{
				if (m320[i].cval.left>=m320[i].size.right)
				{
					Dump320.flag[START3_POS+i] = 0;
				}
				else
				{
					Dump320.src[START3_POS+i].left = m320[i].cval.left;
					Dump320.des[START3_POS+i][0] = RIGHT3_POS+m320[i].cval.left;
					Dump320.flag[START3_POS+i] = 1;
				}
         }
		}
	 
	} // end for loop        
    
	for (i=0; i<S4TotalItems; i++) 
	{
		if (S4ItemFlag[i]) 
		{
    		while(1) // 5 chances to blit
			{

				if (sStretch.bStretch == TRUE)
				{

        			ddrval = d3dappi.lpBackBuffer2->BltFast(S4xy[i*2], S4xy[i*2+1], 
        					   lpDDSOverlay[2], &S4rect[i], S4DrawMode);
        			if (ddrval==DD_OK) 
						break;
					else
					{
						if (HandleException(ddrval))
						{
							if (j>5) 
								break;
							j++;
						}
					}

				}
				else
				{

        			ddrval = d3dappi.lpBackBuffer->BltFast(S4xy[i*2], S4xy[i*2+1], 
        					   lpDDSOverlay[2], &S4rect[i], S4DrawMode);
        			if (ddrval==DD_OK) 
						break;
					else
					{
						if (HandleException(ddrval))
						{
							if (j>5) 
								break;
							j++;
						}
					}
				}
		   } 
		}
	} 

}


/*
O1MAPCOR Aim[3] =	
{
//	305,225,128,0,158,30,	// 0 = 640x480
	145,105,135,0,166,31,
	145,105,135,0,166,31,	// 1 = 320x240
	241,177,128,0,158,30		// 2 = 512x384
};

O1MAPCOR Qit[3] =	
{
//	261,221,0,0,118,38,		// 0 = 640x480
	101,101,0,0,118,38,		// 1 = 320x240
	101,101,0,0,118,38,		// 1 = 320x240
	197,173,0,0,118,38		// 2 = 512x384
};
*/

O1MAPCOR Aim[3] =	
{
	305,225,128,0,158,30,	// 0 = 640x480
	145,105,135,0,166,31,	// 1 = 320x240
	241,177,128,0,158,30		// 2 = 512x384
};

O1MAPCOR Qit[3] =	
{
	261,221,0,0,118,38,		// 0 = 640x480
	101,101,0,0,118,38,		// 1 = 320x240
	197,173,0,0,118,38		// 2 = 512x384
};

void YBShowAimorQuit(BOOL show)
{
	HRESULT ddrval;
	RECT aa = {0,0,118,38};
	int  vmd, j;

	if (camerastuff==NULL)
		return;

	j = 0;
	vmd = RMode - 1;
	if (camerastuff->method==POV)
	{
	   while (1) 
		{
		   	if (sStretch.bStretch)
			{
				ddrval = d3dappi.lpBackBuffer2->BltFast(Aim[vmd].des[0], Aim[vmd].des[1], 
        		lpDDSOverlay[2], &(Aim[vmd].src), S4DrawMode);
        		if (ddrval==DD_OK) 
					break;
				else
				{
					if (j>5) break;
					j++;
				}
			}
			else
			{
        		ddrval = d3dappi.lpBackBuffer->BltFast(Aim[vmd].des[0], Aim[vmd].des[1], 
        				  lpDDSOverlay[2], &(Aim[vmd].src), S4DrawMode);
        		if (ddrval==DD_OK) 
					break;
				else
				{
					if (j>5) break;
					j++;
				}
			}
	   }
	}

	j = 0;
	if (bAskQuit)
	{
		while (1) 
		{

		   	if (sStretch.bStretch)
			{
				ddrval = d3dappi.lpBackBuffer2->BltFast(Aim[vmd].des[0], Qit[vmd].des[1], 
        		lpDDSOverlay[2], &(Qit[vmd].src), S4DrawMode);
        		if (ddrval==DD_OK) 
					break;
				else
				{
					if (j>5) break;
					j++;
				}
			}
			else
			{
        		ddrval = d3dappi.lpBackBuffer->BltFast(Aim[vmd].des[0], Qit[vmd].des[1], 
        				  lpDDSOverlay[2], &(Qit[vmd].src), S4DrawMode);
        		if (ddrval==DD_OK) 
					break;
				else
				{
					if (j>5) break;
					j++;
				}
			}

		} 	
	}
}



void BYSelectRMode(void)
{
	if (bUseDebug)
	{
		RMode = 0;
	}
	else
	{
		if (VM_W3D==640)
		{
			// Tim stretch:  set virtual 320*240 mode
			if (sStretch.bWillStretch)
				RMode = 2;
			else
				RMode = 1;
		}
		else
		if (VM_W3D==320)
		{
			RMode = 2;
		}
		else
		if (VM_W3D==512)
		{
			RMode = 3;
		}
	}
}

//
void BYDisplayUI(BOOL show) 
{
   //int i;

	BYRepaintBack(show);

   BYDisplayMeter(show);
   BYDisplayRadar(show);
   BYDisplayAimQuit(show);
   BYDisplayTimer(show);
   BYDisplaySubTitle(0);
   //JSCShowAEInfo(show);

	//BYForceUpdate(show);
   
   //for (i=0; i<TOTAL_REFRESH_AREA; i++)
   //{
   //   myglobs.view->ForceUpdate(ra[RMode][i].left, ra[RMode][i].top, 
   //                             ra[RMode][i].right, ra[RMode][i].bottom);
   //}

}

//
DWORD DDColorMatch(IDirectDrawSurface *pdds, COLORREF rgb)
{
    COLORREF rgbT;
    HDC hdc;
    DWORD dw = CLR_INVALID;
    DDSURFACEDESC ddsd;
    HRESULT hres;

    //
    //  use GDI SetPixel to color match for us
    //
    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
        rgbT = GetPixel(hdc, 0, 0);             // save current pixel value
        SetPixel(hdc, 0, 0, rgb);               // set our value
        pdds->ReleaseDC(hdc);
    }

    //
    // now lock the surface so we can read back the converted color
    //
    ddsd.dwSize = sizeof(ddsd);
    while ((hres = pdds->Lock(NULL, &ddsd, 0, NULL)) == DDERR_WASSTILLDRAWING)
        ;

    if (hres == DD_OK)
    {
        dw  = *(DWORD *)ddsd.lpSurface;                     // get DWORD
        dw &= (1 << ddsd.ddpfPixelFormat.dwRGBBitCount)-1;  // mask it to bpp
        pdds->Unlock(NULL);
    }

    //
    //  now put the color that was there back.
    //
    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
        SetPixel(hdc, 0, 0, rgbT);
        pdds->ReleaseDC(hdc);
    }

    return dw;
}
//
HRESULT  BYSetColorKey(IDirectDrawSurface *pdds, COLORREF rgb)
{
    DDCOLORKEY ddck;

//    ddck.dwColorSpaceLowValue = DDColorMatch(lpDDSOverlay[0], rgb);
    ddck.dwColorSpaceLowValue = DDColorMatch(pdds, rgb);
    ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;
    return pdds->SetColorKey(DDCKEY_SRCBLT, &ddck);
}

void BYSetUIDumpCo(void)
{
	BYSetColorKey(lpDDSOverlay[2], RGB(0,0,0));

   BYSetupGDIobjects();

   BYSetupGDIobjects();

	if (VM_W3D==320) 
	{
		Rx0 = 161;    
		Ry0 = 24;     
		Rxy = 10;
      
		S4xy   = &(Dump320.des[0][0]);
		S4rect = &(Dump320.src[0]);
		S4TotalItems=Dump320.titem;  
		S4ItemFlag = &(Dump320.flag[0]);
		S4DrawMode = DDBLTFAST_SRCCOLORKEY;
      
		/* Used when the ALT_TAB problem really been solved
		S5xy   = &(rp320.des[0][0]);
		S5rect = &(rp320.src[0]);
		S5TotalItems = rp320.titem;
		S5ItemFlag = &(rp320.flag[0]);
		S5face = &(rp320.face[0]); */

		if (VSize==1)
		{
			S5xy   = &(rp320_1.des[0][0]);
			S5rect = &(rp320_1.src[0]);
			S5TotalItems = rp320_1.titem;
			S5ItemFlag = &(rp320_1.flag[0]);
			S5face = &(rp320_1.face[0]); 
		}

		if (VSize==2)
		{
			S5xy   = &(rp320_2.des[0][0]);
			S5rect = &(rp320_2.src[0]);
			S5TotalItems = rp320_2.titem;
			S5ItemFlag = &(rp320_2.flag[0]);
			S5face = &(rp320_2.face[0]); 
		}

		if (VSize==3)
		{
			S5xy   = &(rp320_3.des[0][0]);
			S5rect = &(rp320_3.src[0]);
			S5TotalItems = rp320_3.titem;
			S5ItemFlag = &(rp320_3.flag[0]);
			S5face = &(rp320_3.face[0]); 
		}

		BYDisplayMeter = YBDisplayMeter320;
      BYDisplayTimer = YBShowTimer320;
      BYDisplaySubTitle = YBDisplaySubTitle; 
		BYDisplayAimQuit  = YBShowAimorQuit;
	}

	if (VM_W3D==512)
	{
		Rx0 = 255; //313;    
		Ry0 = 41; //38;     
		Rxy = 20;

		S4xy   = &(Dump512.des[0][0]);
		S4rect = &(Dump512.src[0]);
		S4TotalItems = Dump512.titem;
		S4ItemFlag = &(Dump512.flag[0]);
		S4DrawMode = DDBLTFAST_SRCCOLORKEY;

		S5xy   = &(rp512.des[0][0]);
		S5rect = &(rp512.src[0]);
		S5TotalItems = rp512.titem;
		S5ItemFlag = &(rp512.flag[0]);
		S5face = &(rp512.face[0]);

      sprintf(fpS1, "Robot LIFE");
      sprintf(fpS2, "Robot WEAPONS");
      sprintf(fpS3, "SECTOR:");
      sprintf(fpS4, "MONSTER LIFE");
      sprintf(fpS5, "MONSTER WEAPONS");
      sprintf(fpS6, "SECTOR:");
      
	   BYSetColorKey(lpDDSOverlay[1], RGB(0,0,0));
      
		BYDisplayMeter = YBDisplayMeter512;
      BYDisplayTimer = YBShowTimer512;
      BYDisplaySubTitle = YBDisplaySubTitle;
		BYDisplayAimQuit  = YBShowAimorQuit;
	}
   
	if (VM_W3D==640)
	{

		if (sStretch.bStretch)
		{

		Rx0 = 161;    
		Ry0 = 24;     
		Rxy = 10;
      
		S4xy   = &(Dump320.des[0][0]);
		S4rect = &(Dump320.src[0]);
		S4TotalItems=Dump320.titem;  
		S4ItemFlag = &(Dump320.flag[0]);
		S4DrawMode = DDBLTFAST_SRCCOLORKEY;
      
		/* Used when the ALT_TAB problem really been solved
		S5xy   = &(rp320.des[0][0]);
		S5rect = &(rp320.src[0]);
		S5TotalItems = rp320.titem;
		S5ItemFlag = &(rp320.flag[0]);
		S5face = &(rp320.face[0]); */

		if (VSize==1)
		{
			S5xy   = &(rp320_1.des[0][0]);
			S5rect = &(rp320_1.src[0]);
			S5TotalItems = rp320_1.titem;
			S5ItemFlag = &(rp320_1.flag[0]);
			S5face = &(rp320_1.face[0]); 
		}

		if (VSize==2)
		{
			S5xy   = &(rp320_2.des[0][0]);
			S5rect = &(rp320_2.src[0]);
			S5TotalItems = rp320_2.titem;
			S5ItemFlag = &(rp320_2.flag[0]);
			S5face = &(rp320_2.face[0]); 
		}

		if (VSize==3)
		{
			S5xy   = &(rp320_3.des[0][0]);
			S5rect = &(rp320_3.src[0]);
			S5TotalItems = rp320_3.titem;
			S5ItemFlag = &(rp320_3.flag[0]);
			S5face = &(rp320_3.face[0]); 
		}

		BYDisplayMeter = YBDisplayMeter320;
      BYDisplayTimer = YBShowTimer320;
      BYDisplaySubTitle = YBDisplaySubTitle; 
		BYDisplayAimQuit  = YBShowAimorQuit;

		}
		else
		{
		
		Rx0 = 313;    
		Ry0 = 38;     
		Rxy = 20;

		S4xy   = &(Dump640.des[0][0]);
		S4rect = &(Dump640.src[0]);
		S4TotalItems = Dump640.titem;
		S4ItemFlag = &(Dump640.flag[0]);
		S4DrawMode = DDBLTFAST_SRCCOLORKEY;

		S5xy   = &(rp640.des[0][0]);
		S5rect = &(rp640.src[0]);
		S5TotalItems = rp640.titem;
		S5ItemFlag = &(rp640.flag[0]);
		S5face = &(rp640.face[0]);

      sprintf(fpS1, "MAIN POWER");
      sprintf(fpS2, "WEAPONS-THRUSTERS");
      sprintf(fpS3, "SECTOR:");
      sprintf(fpS4, "MONSTER LIFE");
      sprintf(fpS5, "PLASMA WEAPONS");
      sprintf(fpS6, "SECTOR:");
      
	   BYSetColorKey(lpDDSOverlay[1], RGB(0,0,0));

		S5xy   = &(rp640.des[0][0]);
		S5rect = &(rp640.src[0]);
		S5TotalItems = rp640.titem;
		S5ItemFlag = &(rp640.flag[0]);
		S5face = &(rp640.face[0]);

      sprintf(fpS1, "MAIN POWER");
      sprintf(fpS2, "WEAPONS-THRUSTERS");
      sprintf(fpS3, "SECTOR:");
      sprintf(fpS4, "MONSTER LIFE");
      sprintf(fpS5, "PLASMA WEAPONS");
      sprintf(fpS6, "SECTOR:");
      
	   BYSetColorKey(lpDDSOverlay[1], RGB(0,0,0));
      
		BYDisplayMeter = YBDisplayMeter640;
      BYDisplayTimer = YBShowTimer640;
      BYDisplaySubTitle = YBDisplaySubTitle;
		BYDisplayAimQuit  = YBShowAimorQuit;
		}
	}
}

BOOL BYDumpInfo(char *s)
{
	FILE *fp;
#ifdef NDEBUG
   return FALSE;
#endif

	fp = fopen("bydump.txt", "a+");

	if (fp) 
	{
		fprintf(fp, "%s\n", s);
		fclose(fp);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void YBDefDisplayUI(BOOL show)
{
   return;
}

//
void BYExitFromMainMenu(void)
{
	bBYRenderingIsOK = FALSE;
	BYReleaseAllOverlays();	
	RELEASE(lpPalette);
	RELEASE(d3dappi.lpBackBuffer);
	RELEASE(d3dappi.lpFrontBuffer);
	RELEASE(d3dappi.lpDD);
}

void BYCleanUp3DSysStuff(void)
{
   ATTEMPT(D3DAppISetCoopLevel(myglobs.hWndMain, FALSE));   // makes palette change -- looks ugly -Spudde

	ATTEMPT(D3DAppICallDeviceDestroyCallback());
	if (d3dappi.bFullscreen) 
	{
		ATTEMPT(D3DAppIClearBuffers());
	}
	BYReleaseAllOverlays();
	RELEASE(d3dappi.lpD3DDevice);
	RELEASE(lpPalette);
	RELEASE(lpClipper);
	if (sStretch.bStretch) 	RELEASE(d3dappi.lpBackBuffer2);

	RELEASE(d3dappi.lpBackBuffer);
	RELEASE(d3dappi.lpFrontBuffer);
	RELEASE(d3dappi.lpZBuffer);
	RELEASE(d3dappi.lpD3D);
    RELEASE(myglobs.lpInfoBuffer);
    RELEASE(myglobs.lpFrameRateBuffer);
	RELEASE(d3dappi.lpDD);
exit_with_error:
	;
}

BOOL BYCreateD3DRMetc(HWND win)
{
	HRESULT rval;

	// Create the D3DRM object
	rval = Direct3DRMCreate(&lpD3DRM);
	if (rval != D3DRM_OK) 
	{
		BYDumpInfo("Failed to create Direct3DRM object.\n");
		return FALSE;
	}
	// Create the master scene frame and camera frame
	rval = lpD3DRM->CreateFrame(NULL, &myglobs.scene);
	if (rval != D3DRM_OK) 
	{
		BYDumpInfo("Failed to create the master scene frame.\n");
		return FALSE;
	}
	rval = lpD3DRM->CreateFrame(myglobs.scene, &myglobs.camera);
	if (rval != D3DRM_OK) 
	{
		BYDumpInfo("Failed to create the camera's frame.\n");
		return FALSE;
	}
	rval = myglobs.camera->SetPosition(myglobs.scene, D3DVAL(0.0), D3DVAL(0.0), D3DVAL(0.0));
	if (rval != D3DRM_OK) 
	{
		BYDumpInfo("Failed to position the camera in the frame.\n");
		return FALSE;
	}
	return TRUE;
}

BOOL BYPreDeviceDestroyed(LPVOID lpContext)
{
    RELEASE(myglobs.view);
    RELEASE(myglobs.dev);
    return TRUE;
}

// This function is only used in non-debuging mode
BOOL BYAfterDeviceCreated
(int w, int h, LPDIRECT3DVIEWPORT* lplpViewport, LPVOID lpContext)
{
	HRESULT rval;
	int x0, y0, w0, h0, vmd;

	rval = lpD3DRM->CreateDeviceFromD3D(d3dapp->lpD3D, d3dapp->lpD3DDevice,
                                        &myglobs.dev);
	if (rval != D3DRM_OK) 
	{
		BYDumpInfo(D3DAppErrorToString(rval));
		return FALSE;
	}
	// Create the D3DRM viewport using the camera frame.  Set the background
	// depth to a large number.  The width and height may be slightly
	// adjusted, so get them from the device to be sure.
	if (VSize==4)
	{
		w0 = myglobs.dev->GetWidth(); ///2;
		h0 = myglobs.dev->GetHeight(); ///2;
		x0 = 0; //w0/2;
		y0 = 0; //h0/2;
	}
	else
	{
		vmd = RMode-1;
		x0 = GWinSize[vmd][VSize-1].left;
		y0 = GWinSize[vmd][VSize-1].top;
		w0 = GWinSize[vmd][VSize-1].right-GWinSize[vmd][VSize-1].left;
		h0 = GWinSize[vmd][VSize-1].bottom-GWinSize[vmd][VSize-1].top;
	}

	rval = lpD3DRM->CreateViewport(myglobs.dev, myglobs.camera, x0, y0, w0,
                                   h0, &myglobs.view);
	if (rval != D3DRM_OK) 
	{
		BYDumpInfo(D3DAppErrorToString(rval));
		RELEASE(myglobs.dev);
		return FALSE;
	}
	rval = myglobs.view->SetBack(D3DVAL(5000.0));
	if (rval != D3DRM_OK) 
	{
		BYDumpInfo(D3DAppErrorToString(rval));
		RELEASE(myglobs.dev);
		RELEASE(myglobs.view);
		return FALSE;
	}
   //Set the render quality, fill mode, lighting state and color shade info
	if (!BYSetRenderState())
	{
		return FALSE;
	}

   //Return NULL for the viewport
	*lplpViewport = NULL;
	//Create and initialize the surfaces containing the frame rate and
	// window information
	InitFontAndTextBuffers();

	return TRUE;
}

BOOL BYSetRenderState(void)
{
    HRESULT rval;
    /*
     * Set the number of buffers so D3DRM can keep track of extents properly
     */
    rval = myglobs.dev->SetBufferCount(d3dapp->bFullscreen &&
                                       d3dapp->bBackBufferInVideo ? 2 : 1);
    if (rval != D3DRM_OK) {
        BYDumpInfo(D3DAppErrorToString(rval));
        return FALSE;
    }
    /*
     * Set the render quality (light toggle, fill mode, shade mode)
     */
    if (myglobs.dev->GetQuality() != myglobs.RenderQuality) 
	 {
        rval = myglobs.dev->SetQuality(myglobs.RenderQuality);
        if (rval != D3DRM_OK) 
		  {
            BYDumpInfo(D3DAppErrorToString(rval));
            return FALSE;
        }
    }
    /*
     * Set dithering toggle
     */
    if (myglobs.dev->GetDither() != myglobs.bDithering) 
	 {
        rval = myglobs.dev->SetDither(myglobs.bDithering);
        if (rval != D3DRM_OK) 
		  {
            BYDumpInfo(D3DAppErrorToString(rval));
            return FALSE;
        }
    }
    /*
     * Set the texture quality (point or linear filtering)
     */
    if (myglobs.dev->GetTextureQuality() != myglobs.TextureQuality) 
	 {
        rval = myglobs.dev->SetTextureQuality(myglobs.TextureQuality);
        if (rval != D3DRM_OK) 
		  {
            BYDumpInfo(D3DAppErrorToString(rval));
            return FALSE;
        }
    }
    /*
     * Set shade info based on current bits per pixel
     */
    switch (d3dapp->ThisMode.bpp) {
        case 8:
            if (FAILED(myglobs.dev->SetShades(1)))
                goto shades_error;
            if (FAILED(lpD3DRM->SetDefaultTextureShades(1)))
                goto shades_error;
            if (FAILED(lpD3DRM->SetDefaultTextureColors(256)))
                goto shades_error;
            break;
        case 16:
            if (FAILED(myglobs.dev->SetShades(1)))
                goto shades_error;
            if (FAILED(lpD3DRM->SetDefaultTextureColors(65536)))
                goto shades_error;
            if (FAILED(lpD3DRM->SetDefaultTextureShades(1)))
                goto shades_error;
            break;
        case 24:
        case 32:
            if (FAILED(myglobs.dev->SetShades(1)))
                goto shades_error;
            if (FAILED(lpD3DRM->SetDefaultTextureColors(65536)))
                goto shades_error;
            if (FAILED(lpD3DRM->SetDefaultTextureShades(1)))
                goto shades_error;
            break;
    }
    return TRUE;
shades_error:
    BYDumpInfo("A failure occurred while setting color shade information.\n");
    return FALSE;
}

void
InitGlobals(void)
{
   // d3dapp = NULL;
   // memset(&myglobs, 0, sizeof(myglobs));
   // myglobs.bShowFrameRate = FALSE; //TRUE;
   // myglobs.bShowInfo = FALSE;      //TRUE;
    myglobs.RenderQuality = D3DRMLIGHT_ON | D3DRMFILL_SOLID |
                            D3DRMSHADE_GOURAUD;
    myglobs.TextureQuality = D3DRMTEXTURE_NEAREST;
}

void BYIniFor3DGame(void)
{
	Defaults defaults;

	InitGlobals();
	defaults.bNoTextures = myglobs.bNoTextures;
	defaults.bConstRenderQuality = myglobs.bConstRenderQuality;
	defaults.bResizingDisabled = FALSE;
	lstrcpy(defaults.Name, "D3DRM Example");
	//OverrideDefaults(&defaults);
	myglobs.bNoTextures = defaults.bNoTextures;
	myglobs.bConstRenderQuality = defaults.bConstRenderQuality;
}

void BYIniForWrapper(HINSTANCE hInstance)
{
	d3dapp = NULL;
	memset(&myglobs, 0, sizeof(myglobs));
	myglobs.bShowFrameRate = TRUE;
	myglobs.bShowInfo      = FALSE;
	myglobs.hInstApp = hInstance;
}


void BYSetO1To640x480(void)
{
	S1Idx = 0;
	S1xy = &(Map640x480.des[0]);
	S1rect = &(Map640x480.src);
}  

void BYSetO1To512x384(void)
{
	S1Idx = 0;
	S1xy = &(Map512x384.des[0]);
	S1rect = &(Map512x384.src);
}  

void BYSetO1To320x240(void)
{
	S1Idx = 0;
	S1xy = &(Map320x240.des[0]);
	S1rect = &(Map320x240.src);
}  

//
void BYDisplayRadar(BOOL show)
{
	static int tx1, ty1;
	RLVector p, p1;
	int dx, dy, dz, i, sx, sz;
	IDirectDrawSurface *pdds;
	HDC  hDC;
	RLVector p2 = {(float)1.0, (float)0.0, (float)0.0};
	double cosx;

	if (!show || !ShowRadar) 
	{
		return;
	}

	if (monstframe==NULL || Robotframe==NULL)
	{
		return;
	}
   if (sStretch.bStretch)
		  pdds = d3dappi.lpBackBuffer2;  
	else
		 pdds = d3dappi.lpBackBuffer;  

	pdds->GetDC(&hDC);

	//RLFrameGetPosition(monstframe, Robotframe, &p); //Rem by Eric 11/12/96

	//Add by Eric 11/12/96
//	if (PlayAsMonster)
//	{
//		RLFrameGetPosition(Robotframe, monstframe, &p);
//	}
//	else
//	{
//		RLFrameGetPosition(monstframe, Robotframe, &p);
//	}

	//end of Eric
	RLFrameGetPosition(badguyframe,goodguyframe,&p);

	targets[0].p.x = p.x;
	targets[0].p.y = p.y;
	targets[0].p.z = p.z;
	targets[0].life = 1;
	targets[0].type = 1;
	
	if (VM_W3D==640 || VM_W3D==512) 
	{
		if (sStretch.bStretch == TRUE)

			{
				//Rxy = ScaleFactor*5;       // 40 - 10
				ScaleFactor = 2; 
				Rxy = ScaleFactor*5;       // 40 - 10

				dx = (int)(-(p.x*(float)Rxy)/127.0);
				dz = (int)((p.z*(float)Rxy)/127.0);
				dy = (int)sqrt(double(dx*dx+dz*dz));
				
				if (bScaleRadar)
				{
					if (dy<=4) ScaleFactor = 8;
					else
					if (dy<=9) ScaleFactor = 4;
					Rxy = ScaleFactor*5;       // 40 - 10
				}

				for (i=0; i<TotalTargets; i++) 
				{
					p.x = targets[i].p.x;
					p.y = (float)0.0;
					p.z = targets[i].p.z;

					dx = (int)(-(p.x*(float)Rxy)/127.0);
					dz = (int)((p.z*(float)Rxy)/127.0);
					dy = (int)sqrt(double(dx*dx+dz*dz));

				 if (targets[i].life==1 && dy<=21) 
					{
						tx1 = Rx0 + dx;
						ty1 = Ry0 + dz;
						if (targets[i].type>0 && targets[i].type<6)
						{
							SelectObject(hDC, hGamePen[targets[i].type-1]);
						}

						MoveToEx(hDC, tx1, ty1, NULL);
						LineTo(hDC, tx1, ty1);
					} // endif target alive and within the range
					if (targets[i].type==1 && targets[i].life==1) 
					{
						//RLFrameGetPosition(monstframe, Robotframe, &p1); //Rem by Eric 11/12/96

						//Add by Eric 11/12/96
		//				if (PlayAsMonster)
		//				{
		//					RLFrameGetPosition(Robotframe, monstframe, &p1);
		//				}
		//				else
		//				{
		//					RLFrameGetPosition(monstframe, Robotframe, &p1);
		//				}

						//end of Eric
						RLFrameGetPosition(badguyframe,goodguyframe,&p1);

						p1.x = -p1.x;
						RLVectorNormalise(&p1);
						cosx = RLVectorDotProduct(&p1, &p2);

						sx = (int)(21.0*cosx);
						sz = (int)sqrt(double(21*21-sx*sx));
						if (p1.z<0)
							sz = -sz;

						tx1 = Rx0 + sx;
						ty1 = Ry0 + sz;

						SelectObject(hDC, hGamePen[5]);
						MoveToEx(hDC, tx1, ty1, NULL);
						LineTo(hDC, tx1, ty1);
					}
				} // end for all the targets
			} // endif vmode=320



		else
		{
			ScaleFactor = 2;
			Rxy = ScaleFactor*10;
			dx = (int)(-(p.x*(float)Rxy)/127.0);
			dz = (int)((p.z*(float)Rxy)/127.0);
			dy = (int)sqrt(double(dx*dx+dz*dz));

			if (bScaleRadar)
			{
				if (dy<=9) ScaleFactor = 8;
				else
				if (dy<=19) ScaleFactor = 4;
				Rxy = ScaleFactor*10;   
			}

			for (i=0; i<TotalTargets; i++) 
			{
				p.x = targets[i].p.x;
				p.y = (float)0.0;
				p.z = targets[i].p.z;

				dx = (int)(-(p.x*(float)Rxy)/127.0);
				dz = (int)((p.z*(float)Rxy)/127.0);
				dy = (int)sqrt(double(dx*dx+dz*dz));

			 if (targets[i].life==1 && dy<=42) 
				{
					tx1 = Rx0 + dx;
					ty1 = Ry0 + dz;

					if (targets[i].type>0 && targets[i].type<6)
					{
						SelectObject(hDC, hGamePen[targets[i].type-1]);
					}
					MoveToEx(hDC, tx1, ty1, NULL);
					LineTo(hDC, tx1, ty1);
				} // endif target alive and within the range
				if (targets[i].type==1 && targets[i].life==1) 
				{
					//RLFrameGetPosition(monstframe, Robotframe, &p1); //Rem by Eric 11/12/96

					//Add by Eric
	//				if (PlayAsMonster)
	//				{
	///					RLFrameGetPosition(Robotframe, monstframe, &p1);
	//				}
	//				else
	//				{
	//					RLFrameGetPosition(monstframe, Robotframe, &p1);
	//				}
					//end of Eric
					RLFrameGetPosition(badguyframe,goodguyframe,&p1);

					p1.x = -p1.x;
					RLVectorNormalise(&p1);
					cosx = RLVectorDotProduct(&p1, &p2);

					sx = (int)(38.0*cosx);
					sz = (int)sqrt(double(38*38-sx*sx));
					if (p1.z<0)
						sz = -sz;

					tx1 = Rx0 + sx;
					ty1 = Ry0 + sz;

					SelectObject(hDC, hGamePen[5]);
					MoveToEx(hDC, tx1, ty1, NULL);
					LineTo(hDC, tx1, ty1);
				}

			} // end for all the targets
		}
	} // endif vmode=640
	else
	//
	if (VM_W3D==320) 
	{
		//Rxy = ScaleFactor*5;       // 40 - 10
		ScaleFactor = 2; 
		Rxy = ScaleFactor*5;       // 40 - 10

		dx = (int)(-(p.x*(float)Rxy)/127.0);
		dz = (int)((p.z*(float)Rxy)/127.0);
		dy = (int)sqrt(double(dx*dx+dz*dz));
		
		if (bScaleRadar)
		{
			if (dy<=4) ScaleFactor = 8;
			else
			if (dy<=9) ScaleFactor = 4;
			Rxy = ScaleFactor*5;       // 40 - 10
		}

		for (i=0; i<TotalTargets; i++) 
		{
			p.x = targets[i].p.x;
			p.y = (float)0.0;
			p.z = targets[i].p.z;

			dx = (int)(-(p.x*(float)Rxy)/127.0);
			dz = (int)((p.z*(float)Rxy)/127.0);
			dy = (int)sqrt(double(dx*dx+dz*dz));

         if (targets[i].life==1 && dy<=21) 
			{
				tx1 = Rx0 + dx;
				ty1 = Ry0 + dz;
				if (targets[i].type>0 && targets[i].type<6)
				{
					SelectObject(hDC, hGamePen[targets[i].type-1]);
				}

				MoveToEx(hDC, tx1, ty1, NULL);
				LineTo(hDC, tx1, ty1);
			} // endif target alive and within the range
			if (targets[i].type==1 && targets[i].life==1) 
			{
				//RLFrameGetPosition(monstframe, Robotframe, &p1); //Rem by Eric 11/12/96

				//Add by Eric 11/12/96
//				if (PlayAsMonster)
//				{
//					RLFrameGetPosition(Robotframe, monstframe, &p1);
//				}
//				else
//				{
//					RLFrameGetPosition(monstframe, Robotframe, &p1);
//				}

				//end of Eric
				RLFrameGetPosition(badguyframe,goodguyframe,&p1);

				p1.x = -p1.x;
				RLVectorNormalise(&p1);
				cosx = RLVectorDotProduct(&p1, &p2);

				sx = (int)(21.0*cosx);
				sz = (int)sqrt(double(21*21-sx*sx));
				if (p1.z<0)
					sz = -sz;

				tx1 = Rx0 + sx;
				ty1 = Ry0 + sz;

				SelectObject(hDC, hGamePen[5]);
				MoveToEx(hDC, tx1, ty1, NULL);
				LineTo(hDC, tx1, ty1);
			}
		} // end for all the targets
	} // endif vmode=320

	pdds->ReleaseDC(hDC);
}

//
// TEST FOR 3D BACKGROUND
//
BOOL BYClipBackground(RECT *rc, DWORD *dx, DWORD *dy)
{
	int vmd, dxx, dyy, dw, dh;
	DWORD w,h;

	if (VSize==4)
	{
		return TRUE;
	}
	vmd = RMode-1;
	w = rc->right - rc->left;
	h = rc->bottom - rc->top;
	if (*dx>=(unsigned long)GWinSize[vmd][VSize-1].right ||
		 (*dx+w)<=(unsigned long)GWinSize[vmd][VSize-1].left ||
		 *dy>=(unsigned long)GWinSize[vmd][VSize-1].bottom ||
		 (*dy+h)<=(unsigned long)GWinSize[vmd][VSize-1].top)
	{
		return FALSE;
	}
	// from here, I assume that there is an intersection
	// between the game window and blit area, so we need
	// to adjust the real blit coordinates
	dxx = GWinSize[vmd][VSize-1].left - *dx;
	dyy = GWinSize[vmd][VSize-1].top - *dy;
	dw  = *dx + w - GWinSize[vmd][VSize-1].right;
	dh  = *dy + h - GWinSize[vmd][VSize-1].bottom;
	if (dxx>0)
	{
		*dx = GWinSize[vmd][VSize-1].left;
		rc->left = rc->left + dxx;
	}
	if (dyy>0)
	{
		*dy = GWinSize[vmd][VSize-1].top;
		rc->top = rc->top + dyy;
	}
	if (dw>0)
	{
		rc->right = rc->right - dw;
	}
	if (dh>0)
	{
		rc->bottom = rc->bottom - dh;
	}
	return TRUE;
}

// SET UP GDI OBJECTS
void BYSetupGDIobjects(void)
{
	HDC  hDC;
	IDirectDrawSurface *pdds;

	pdds = d3dappi.lpBackBuffer;  

	if (pdds->GetDC(&hDC)==DD_OK) 

	{
		hGameFont = BYSelectFont(hDC, "System", 0, 14);
		hSystemFont = SelectObject(hDC, hGameFont);
		if (VM_W3D==640)
		{
			hGameBrush[0] = CreateSolidBrush(RGB(0,255,0));
			hGameBrush[1] = CreateSolidBrush(RGB(255,0,0));	
			hSystemBrush = SelectObject(hDC, hGameBrush[0]);
		}
		hGamePen[0] = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));  
		hGamePen[1] = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		hGamePen[2] = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		hGamePen[3] = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
		hGamePen[4] = CreatePen(PS_SOLID, 2, RGB(255, 0, 255)); 
		hGamePen[5] = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
		hSystemPen = SelectObject(hDC, hGamePen[0]);

		pdds->ReleaseDC(hDC);
	}
}

void BYRestoreGDIobjects(void)
{
	HDC  hDC;
	IDirectDrawSurface *pdds;

	pdds = d3dappi.lpBackBuffer;  

	if (pdds->GetDC(&hDC)==DD_OK) 
	{
		SelectObject(hDC, hSystemFont);
		SelectObject(hDC, hSystemPen);
		if (VM_W3D==640)
		{
			SelectObject(hDC, hSystemBrush);
		}
		pdds->ReleaseDC(hDC);
	}

}

void BYBlitOnToP(short OverlayNum, BOOL show)
{
	int i, j;
	HRESULT ddrval;
	IDirectDrawSurface *pdds;
	
	if (!show) return;

	j = 0;
	pdds = lpDDSOverlay[(OverlayNum-1)];

	if (OverlayNum==1) 
	{
		while(1) // 5 chances to blit 
		{
			ddrval = d3dappi.lpFrontBuffer->BltFast(S1xy[S1Idx*2], S1xy[S1Idx*2+1], 
					   pdds, &S1rect[S1Idx], S1DrawMode);
			if (ddrval==DD_OK) 
				break;
			else
			{
				if (j>5) break;
				j++;
			}
		} 
	} else 
	if (OverlayNum==2) 
	{
		for (i=0; i<S2TotalItems; i++) 
		{
			if (S2ItemFlag[i]) 
			{
				while(1) // 5 chances to blit
				{
					ddrval = d3dappi.lpFrontBuffer->BltFast(S2xy[i*2], S2xy[i*2+1], 
								pdds, &S2rect[i], S2DrawMode);
					if (ddrval==DD_OK) 
						break;
					else
					{
						if (j>5) break;
						j++;
					}
				} 
			}
		}
	} else
	if (OverlayNum==3) 
	{
		for (i=0; i<S3TotalItems; i++) 
		{
			if (S3ItemFlag[i]) 
			{
				while(1) // 5 chances to blit
				{
					ddrval = d3dappi.lpFrontBuffer->BltFast(S3xy[i*2], S3xy[i*2+1], 
								pdds, &S3rect[i], S3DrawMode);
					if (ddrval==DD_OK) 
						break;
					else
					{
						if (j>5) break;
						j++;
					}
				} 
			}
		}
	}
}

//
BOOL BYRepaintBack(BOOL show)
{
   short i, j;
	HRESULT ddrval;

	if (!show || VSize==4)
	{
		return FALSE;
	}

	j=0;
	for (i=0; i<S5TotalItems; i++) 
	{
		if (S5ItemFlag[i]) 
		{
    		while(1) // 5 chances to blit
			{
        		ddrval = d3dappi.lpBackBuffer->BltFast(S5xy[i*2], S5xy[i*2+1], 
        		           lpDDSOverlay[S5face[i]], &S5rect[i], S5DrawMode);
        		if (ddrval==DD_OK) 
					break;
				else
				{
					if (j>5) break;
					j++;
				}

		   } 
		}
   }
	return TRUE;
}

//
BOOL BYTestBars(BOOL show)
{
	static BOOL bmLife=TRUE;
	static BOOL bmEngy=TRUE;
	static BOOL bnLife=TRUE;
	static BOOL bnEngy=TRUE;

	if (RobotLife<0 || RobotLife>100 ||
		 MnstLife<0 || MnstLife>100 ||
		 RobotEngy<0 || RobotEngy>65536 ||
		 MnstEngy<0 || MnstEngy>65536)
	{
		return FALSE;
	}

	if (!show)
	{
		return TRUE;
	}

	if (bmLife) 
	{
		RobotLife--;
		if (RobotLife<=0) 
		{
			RobotLife = 0;
			bmLife = FALSE;
		}
	}
	else
	{
		RobotLife++;
		if (RobotLife>=100) 
		{
			RobotLife = 100;
			bmLife = TRUE;
		}
	}
	
   //
	if (bmEngy) 
	{
		if ((RobotEngy-600)<=0) 
		{
			RobotEngy = 0;
			bmEngy = FALSE;
		}
		else
		{
			RobotEngy-=600;
		}
	}
	else
	{
		if ((RobotEngy+600)>=65536)
		{
			RobotEngy = 65536;
			bmEngy = TRUE;
		}
		else
		{
			RobotEngy+=600;
		}
	} 
	
   //
	if (bnLife) 
	{
		MnstLife--;
		if (MnstLife<=0) 
		{
			MnstLife = 0;
			bnLife = FALSE;
		}
	}
	else
	{
		MnstLife++;
		if (MnstLife>=100) 
		{
			MnstLife = 100;
			bnLife = TRUE;
		}
	}

	if (bnEngy) 
	{
		if ((MnstEngy-600)<=0) 
		{
			MnstEngy = 0;
			bnEngy = FALSE;
		}
		else
		{
			MnstEngy-=600;
		}
	}
	else
	{
		if ((MnstEngy+600)>=65536) 
		{
			MnstEngy = 65536;
			bnEngy = TRUE;
		}
		else
		{
			MnstEngy+=600;
		}
	} 
	return TRUE;
}

BOOL BYTestTimePopu(BOOL show)
{
      //sprintf(fps2, "%02d:%02d:%02d", Hours,Minutes,Seconds);
	return TRUE;
}

BOOL BYForceUpdate(BOOL show)
{
	int i;

	if (VSize==4)
		return FALSE;

   for (i=0; i<TOTAL_REFRESH_AREA; i++)
   {
      myglobs.view->ForceUpdate(ra[RMode][i].left, ra[RMode][i].top, 
                                ra[RMode][i].right, ra[RMode][i].bottom);
   }
	return TRUE;
}

//
void ShowNetConnections(BOOL show, short mode)
{
   HDC  hDC;
   IDirectDrawSurface *pdds;
   short i, j, px, py;

   if (show) 
   {
      pdds = d3dappi.lpBackBuffer; 
		if (pdds==NULL)
			return;

		px = 300;
		py = 405;

      if (pdds->GetDC(&hDC)==DD_OK) 
      {
         SetBkColor(hDC, NULL);
         SetBkMode(hDC, TRANSPARENT);
			for (i=0; i<total_cntion; i++)
			{
				j = valid_cntion[i];
				if (i!=curt_cntion)
				{
					SetTextColor(hDC, RGB(0, 0, 255));
				}
				else
				{	
					SetTextColor(hDC, RGB(255, 255, 255));
				}
				TextOut(hDC, px, py, net_cntion[j], lstrlen(net_cntion[j]));
				py += 15;
			}
         pdds->ReleaseDC(hDC);
		}
	}
}

//
//
void ShowSessionList(BOOL show, short mode)
{
   HDC  hDC;
   IDirectDrawSurface *pdds;
   short i, px, py;
   char blank[] = "                   ";
   char nosession[] = "No sessions available";

   if (show) 
   {
      pdds = d3dappi.lpBackBuffer; 
		if (pdds==NULL)
			return;

		px = 300;
		py = 405;

      if (pdds->GetDC(&hDC)==DD_OK) 
      {
         SetBkColor(hDC, NULL);
         SetBkMode(hDC, TRANSPARENT);
         if (nSessionId)
         {
			   for (i=0; i<4; i++)
			   {
				   if (i!=WhichSession)
				   {
					   SetTextColor(hDC, RGB(0, 0, 255));
				   }
				   else
				   {	
					   SetTextColor(hDC, RGB(255, 255, 255));
				   }
				   if (i<nSessionId) 
                  TextOut(hDC, px, py, S_lpDPGameDesc[i]->SessionName, lstrlen(S_lpDPGameDesc[i]->SessionName));
               else
                  TextOut(hDC, px, py, blank, lstrlen(blank));
				   py += 15;
			   }
         }
         else
         {
				SetTextColor(hDC, RGB(255, 0, 0));
            TextOut(hDC, px, py, nosession, lstrlen(nosession));
            WhichSession = -1;
         }

         pdds->ReleaseDC(hDC);
		}
	}
}

int P5Chip, P6Chip, MMXChip, hw3dacc;

void SetShowScreenPara(void)
{
	int i, j;

	j = 0;
	total_modes = 0;
	current_mode = 0;
	if (VSize>=1 && VSize<=4)
		current_size = VSize-1;
	else
		current_size = 0;

   if (VSize == 4 && sStretch.bWillStretch)
      current_size = 0;

	// initialize valid_mode
	for (i=0; i<d3dappi.NumModes; i++)
	{
		if (d3dappi.Mode[i].w == 640 && d3dappi.Mode[i].h == 480)
		{
			if ((d3dappi.Mode[i].bpp == 16))
			{
            if ((hw3dacc && VRAM_Range==4))   // only if d3d accelerators w/4meg VRAM
            {
				   valid_mode[j] = 0;
				   inner_mode[j++] = i;
				   total_modes++;
            }
			}
			else if (d3dappi.Mode[i].bpp == 8)
			{
				valid_mode[j] = 1;
				inner_mode[j++] = i;
				total_modes++;
			}
		}

		if (d3dappi.Mode[i].w == 512 && d3dappi.Mode[i].h == 384)
		{
			if ((d3dappi.Mode[i].bpp == 16) && hw3dacc)
			{
				valid_mode[j] = 2;
				inner_mode[j++] = i;
				total_modes++;
			}
			/*
			else if (d3dappi.Mode[i].bpp == 8)
			{
				valid_mode[j] = 3;
				inner_mode[j++] = i;
				total_modes++;
			}
			*/
		}
		if (d3dappi.Mode[i].w == 320 && d3dappi.Mode[i].h == 240)
		{
			/*
			if (d3dappi.Mode[i].bpp == 16)
			{
				valid_mode[j] = 4;
				inner_mode[j++] = i;
				total_modes++;
			}
			else if (d3dappi.Mode[i].bpp == 8)
			*/
			if (d3dappi.Mode[i].bpp == 8)
			{
				valid_mode[j] = 5;
				inner_mode[j++] = i;
				total_modes++;
			}
		}
	} // for loop

	// initialize current_mode value
	for (i=0; i<d3dappi.NumModes; i++)
	{
		if (d3dappi.Mode[i].w == VM_W3D &&
			 d3dappi.Mode[i].h == VM_H3D &&
			 d3dappi.Mode[i].bpp == VM_BPP3D)
		{
			j = i;
			break;
		}
	}

	for (i=0; i<total_modes; i++)
	{
		if (inner_mode[i]==j)
		{
			current_mode = i;
			break;
		}
	}

	tpmode = current_mode;
	tpsize = current_size;
	if (S2NewIdx==20)
	{
		bInWSize = TRUE;
		DDtext = TRUE;
	}
	else if (S2NewIdx==19)
	{
		bInVModeMenu = TRUE;
		DDtext = TRUE;
	}
}


void ShowScreenSettings(BOOL show, short mode)
{
	HDC  hDC;
//	HFONT htpFont;
	IDirectDrawSurface *pdds;
	short i1, j1, px1, py1, ix, iy;

   if (show) 
   {
      pdds = d3dappi.lpBackBuffer; 
		if (pdds==NULL)
			return;

		px1 = 300;
		py1 = 405;
		ix = iy = 0;


		if (bInVModeMenu) 
		{
			if (pdds->GetDC(&hDC)==DD_OK) 
			{
				SetBkColor(hDC, NULL);
				SetBkMode(hDC, TRANSPARENT);
				for (i1=0; i1<total_modes; i1++)
				{
					j1 = valid_mode[i1];
					if (i1==tpmode)
					{
						SetTextColor(hDC, RGB(255, 255, 255));
					}
					else if (i1==current_mode)
					{
						SetTextColor(hDC, RGB(0, 255, 0));
					}
					else 
					{	
						SetTextColor(hDC, RGB(0, 0, 255));
					}
					TextOut(hDC, px1, py1, video_modes[j1], lstrlen(video_modes[j1]));
					ix++;
					if (ix>=2)
					{
						ix = 0;
						px1 = 300;
						py1 += 15;
					}
					else
					{
						px1 += 150;
					}
				}
				if (bErrMsg)
					TextOut(hDC, 300, 460, ErrMsg, lstrlen(ErrMsg));
				pdds->ReleaseDC(hDC);
			} 
		} // if bInVModeMenu
		else
		if (bInWSize)
		{
			if (pdds->GetDC(&hDC)==DD_OK) 
			{
				SetBkColor(hDC, NULL);
				SetBkMode(hDC, TRANSPARENT);
				for (i1=0; i1<4; i1++)
				{
					if (i1==tpsize)
					{
						SetTextColor(hDC, RGB(255, 255, 255));
					}
					else if (i1==current_size)
					{
						SetTextColor(hDC, RGB(0, 255, 0));
					}
					else
					{	
						SetTextColor(hDC, RGB(0, 0, 255));
					}
					if (i1 == 0 && sStretch.bCanStretch && VM_W3D == 640 && VM_BPP3D == 16)
                  TextOut(hDC, px1, py1, window_sizes[4], lstrlen(window_sizes[4]));
               else
                  TextOut(hDC, px1, py1, window_sizes[i1], lstrlen(window_sizes[i1]));
					ix++;
					if (ix>=2)
					{
						ix = 0;
						px1 = 300;
						py1 += 15;
					}
					else
					{
						px1 += 150;
					}
				}
				if (bErrMsg)
					TextOut(hDC, 300, 460, ErrMsg, lstrlen(ErrMsg));
				pdds->ReleaseDC(hDC);
			} 
		}
	} // if show
}

// New on 1/10/97
#ifdef CAPBMP
BOOL SaveScreenImage(void)
{
	FILE *fp;
	char fname[20]="IMAGE";
	static short i=1;
	char tname[10], fullname[127];

	strcpy(fullname, BmpPath);
	strcat(fullname, "\\");
	strcat(fullname, fname);

	sprintf(tname, "%d", i);
	strcat(fullname, tname);
	strcat(fullname, ".RAW");

	fp = fopen(fullname, "wb");
	if (fp!=NULL) 
	{
		fwrite((unsigned char*)ImageBuffer, sizeof(unsigned char), ImgBufSize, fp);
		fclose(fp);
		i++;
		ImageFlag = FALSE;
		return TRUE;
	} else
		return FALSE;
}

BOOL CaptureScreenImage(void)
{
	DDSURFACEDESC ddsd1;
	HRESULT       ddrval;

	if (ImageFlag) 
		return FALSE;
	else 
		ImageFlag = TRUE;

	_fmemcpy((unsigned char *)ImageBuffer, ImagePtr, ImgBufSize); 
	return TRUE;
}
#endif

BOOL BYLastQuestion(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_LAST_QUESTION);

	BYLoadOverlay(1, "wr133.bmp");
	BYSetO1MainMenuB();

	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYKdLastQuestion(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{

	ISKEYDOWN(msg);
	ISPAGE(pg_LAST_QUESTION);

	switch(wParam) 
	{
	case 'Y':
	case 'y':
	case VK_ESCAPE:
		/*
		MidCmd = MID_STOP;
		BYMidiCenter();
		
		//Add by Eric 11/15/96
		if (netPlay)
		{
			EventSndBuf.MsgId = NEW_MSG;
			EventSndBuf.Event = EVENT_GOODBYE;
		}
		//end of Eric

		PostMessage(win, WM_DESTROY, 0, 0L);
		*/
		BYSetPrePageSwitch(Page, pg_THANKYOU); 	
		Page = pg_THANKYOU;
		PostMessage(win, WM_COMMAND, Page, 0L);
		break;
	case 'N':
	case 'n':
		BYSetPrePageSwitch(Page, pg_SHOW_MAIN_MENU); 	
		Page = pg_SHOW_MAIN_MENU;
		PostMessage(win, WM_COMMAND, Page, 0L);
		di.TurnOnMsCursor(TRUE);
		break;
	default:
		break;
	}
	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYThankYou(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_THANKYOU);

	bBYRenderingIsOK = TRUE;        // Enable rendering
	BYLoadOverlay(1, "wr132.bmp");
	BYSetO1MainMenuB();

#ifdef FREEWARE
	nTimer = SetTimer(win, 2, 20000, NULL);  
	BYKbrdHandler[pg_THANKYOU]  = BYKdThankYou;
#else  // FREEWARE
	nTimer = SetTimer(win, 2, 5000, NULL);  
	BYKbrdHandler[pg_THANKYOU]  = BYKdThankYou;
#endif // FREEWARE

	return TRUE;

exit_with_false:
	return FALSE;

}

BOOL BYKdThankYou(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISKEYDOWN(msg);
	ISPAGE(pg_THANKYOU);

	KillTimer(win, nTimer);
	MidCmd = MID_STOP;
	BYMidiCenter();
	PostMessage(win, WM_DESTROY, 0, 0L);

	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYTimeThankYou(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_THANKYOU);
	IS_WRAPPER_TIMER(wParam);

	KillTimer(win, nTimer);
	MidCmd = MID_STOP;
	BYMidiCenter();
		
	//Add by Eric 11/15/96
	/*
	if (GameStates.isNetplay)
	{
		EventSndBuf.MsgId = NEW_MSG;
		EventSndBuf.Event = EVENT_GOODBYE;
	}
	*/
	//end of Eric

	PostMessage(win, WM_DESTROY, 0, 0L);

	return TRUE;

exit_with_false:
	return FALSE;
}

// 1/30/97
BOOL BYKdChooseMouseCfg(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int i=0;

	ISKEYDOWN(msg);
	ISPAGE(pg_SHOW_MOUSECFG);

	if (msg==WM_CHAR)
	{
		return FALSE;
	}

	switch(wParam)
	{
	case VK_ESCAPE:
		DDtext = FALSE;
		Page = pg_SHOW_OPTION_MENU;
		PostMessage(win, WM_COMMAND, Page, 0L);
		break;
	case VK_DOWN:
	case VK_RIGHT:
		if (tpmscfg<(total_mscfg-1))
			tpmscfg++;
		else
			tpmscfg=0;
		break;
	case VK_UP:
	case VK_LEFT:
		if (tpmscfg>0)
			tpmscfg--;
		else
			tpmscfg=total_mscfg-1;
		break;
	case VK_RETURN:
		sndPlaySound(WrapSnd1, SND_ASYNC);
		current_mscfg = tpmscfg;
		BYChangeMouseActions();
		di.SetDIMsAction(MsActions);
		Page = pg_SHOW_OPTION_MENU;
		PostMessage(win, WM_COMMAND, Page, 0L);
		break;
	}
	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYKdChooseJoystkCfg(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int i=0;

	ISKEYDOWN(msg);
	ISPAGE(pg_SHOW_JOYSKCFG);

	if (msg==WM_CHAR)
	{
		return FALSE;
	}

	if (!bFindJoystick)
	{
		if (wParam==VK_ESCAPE)
		{
			DDtext = FALSE;
			Page = pg_SHOW_OPTION_MENU;
			PostMessage(win, WM_COMMAND, Page, 0L);
		}
		return FALSE;
	}

	switch(wParam)
	{
	case VK_F1:
		if ((JoyStickType==YB_SIDEWINDER_3D_PRO) ||
			 (JoyStickType==YB_SIDEWINDER_GAMEPAD))
		{
			bUseGameProfile = !bUseGameProfile;
		}
		break;
	case VK_ESCAPE:
		DDtext = FALSE;
		Page = pg_SHOW_OPTION_MENU;
		PostMessage(win, WM_COMMAND, Page, 0L);
		break;
	case VK_DOWN:
	case VK_RIGHT:
		if (tpjoycfg<(total_joycfg-1))
			tpjoycfg++;
		else
			tpjoycfg=0;
		break;
	case VK_UP:
	case VK_LEFT:
		if (tpjoycfg>0)
			tpjoycfg--;
		else
			tpjoycfg=total_joycfg-1;
		break;
	case VK_RETURN:
		sndPlaySound(WrapSnd1, SND_ASYNC);
		current_joycfg = tpjoycfg;
		BYChangeJoystkActions();
		Page = pg_SHOW_OPTION_MENU;
		PostMessage(win, WM_COMMAND, Page, 0L);
		break;
	}
	return TRUE;

exit_with_false:
	return FALSE;
}

void ShowJoystkSettings(BOOL show, short mode)
{
	HDC  hDC;
//	HFONT htpFont;
	IDirectDrawSurface *pdds;
	short i1, j1, px1, py1, k1;
	char sUseProfile[] = "F1 - USE GAME PROFILER: ";

   if (show && bFindJoystick) 
   {
      pdds = d3dappi.lpBackBuffer; 
		if (pdds==NULL)
			return;

		px1 = 50;
		py1 = 30;

		if (pdds->GetDC(&hDC)==DD_OK) 
		{
			SetBkColor(hDC, NULL);
			SetBkMode(hDC, TRANSPARENT);
			// display configuration string -- not meaningful 
			//for (i1=0; i1<total_joycfg; i1++)
			//{
			if ((JoyStickType==YB_SIDEWINDER_3D_PRO) ||
				 (JoyStickType==YB_SIDEWINDER_GAMEPAD))
			{
				SetTextColor(hDC, RGB(0, 0, 255));
				TextOut(hDC, 285, 415, sUseProfile, lstrlen(sUseProfile));
				SetTextColor(hDC, RGB(0, 255, 0));

				if (bUseGameProfile)
					TextOut(hDC, 480, 415, "YES", 3);
				else
					TextOut(hDC, 480, 415, "NO", 2);
			}
			else if (JoyStickType==YB_GENERIC)
			{
				i1=tpjoycfg;
				if (tpjoycfg==current_joycfg)
				{
					SetTextColor(hDC, RGB(0, 255, 0));
				}
				else 
				{
					SetTextColor(hDC, RGB(0, 0, 255));
				}
				if (bd0>=4)
					TextOut(hDC, 460, 198, CfgString[i1], lstrlen(CfgString[i1]));
				else
					TextOut(hDC, 460, 67, CfgString[i1], lstrlen(CfgString[i1]));
				//	py1 += 15;
				//} // end for loop
				// display joystk btns' configuration
				//SetTextColor(hDC, RGB(255, 255, 255));
				if (bd0==4 || bd0==8) k1 = 8;
				else k1 = 6;
				if (bd0>=4)
				{
					for (i1=4; i1<k1; i1++)
					{
						j1 = Joy4btnConfig[tpjoycfg][i1];
						TextOut(hDC, JoyCfgPos[i1][0], JoyCfgPos[i1][1], 
								  ActString[j1], lstrlen(ActString[j1]));
					}
				} 
				else
				{
					for (i1=4; i1<k1; i1++)
					{
						j1 = Joy2btnConfig[tpjoycfg][i1];
						TextOut(hDC, JoyCfgPos[i1-2][0], JoyCfgPos[i1-2][1], 
								  ActString[j1], lstrlen(ActString[j1]));
					}
				} 

				if (bErrMsg)
					TextOut(hDC, 300, 460, ErrMsg, lstrlen(ErrMsg));
			}
			pdds->ReleaseDC(hDC);
		} 
	} // if show
}

void ShowMouseSettings(BOOL show, short mode)
{
	HDC  hDC;
//	HFONT htpFont;
	IDirectDrawSurface *pdds;
	short i1, j1, px1, py1;

   if (show) 
   {
      pdds = d3dappi.lpBackBuffer; 
		if (pdds==NULL)
			return;

		px1 = 50;
		py1 = 30;

		if (pdds->GetDC(&hDC)==DD_OK) 
		{
			SetBkColor(hDC, NULL);
			SetBkMode(hDC, TRANSPARENT);
			// display configuration string -- not meaningful 
			//for (i1=0; i1<total_mscfg; i1++)
			//{
			i1 = tpmscfg;
			if (tpmscfg==current_mscfg)
			{
				SetTextColor(hDC, RGB(0, 255, 0));
			}
			else 
			{
				SetTextColor(hDC, RGB(0, 0, 255));
			}
			TextOut(hDC, 464, 77, CfgString[i1], lstrlen(CfgString[i1]));
			//	py1 += 15;
			//} // end for loop

			//SetTextColor(hDC, RGB(255, 255, 255));
			for (i1=4; i1<6; i1++)
			{
				j1 = MsConfig[tpmscfg][i1];
				TextOut(hDC, MsCfgPos[i1][0], MsCfgPos[i1][1], 
					     ActString[j1], lstrlen(ActString[j1]));
			}

			if (bErrMsg)
				TextOut(hDC, 300, 460, ErrMsg, lstrlen(ErrMsg));
			pdds->ReleaseDC(hDC);
		} 
	} // if show
}

void BYChangeJoystkActions()
{
	int i;

	memset(JoyActions, 0, 30);
	if (JoyStickType == YB_SIDEWINDER_3D_PRO)
	{
		for (i=0; i<17; i++)
		{
			JoyActions[i] = ActTable[Joy8btnConfig[current_joycfg][i]];
		}		
	}
	else
	if (JoyStickType == YB_SIDEWINDER_GAMEPAD || JoyStickType == YB_CREATIVE_GAMEPAD || JoyStickType == YB_GRAVIS_GRIP)
	{
		for (i=0; i<19; i++)
		{
			JoyActions[i] = ActTable[Joy10btnConfig[current_joycfg][i]];
		}
	}
	else
	if (bd0>=9)
	{
		for (i=0; i<19; i++)
		{
			JoyActions[i] = ActTable[Joy10btnConfig[current_joycfg][i]];
		}
	}
	else
	if (bd0>=4 && bd0<=8)
	{
		for (i=0; i<8; i++)
		{
			JoyActions[i] = ActTable[Joy4btnConfig[current_joycfg][i]];
		}
	}
	else
	{
		for (i=0; i<6; i++)
		{
			JoyActions[i] = ActTable[Joy2btnConfig[current_joycfg][i]];
		}
	}
}

void BYChangeMouseActions()
{
	int i;

	for (i=0; i<6; i++)
	{
		MsActions[i] = ActTable[MsConfig[current_mscfg][i]];
	}
}

// freeware functions below
#ifdef FREEWARE
BOOL BYGetD3DInfo(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_GET_D3DINFO);

//	if (VRAM_Range==1 || !bSupportD3D)
#ifdef USE320
	BYSetPrePageSwitch(Page, pg_SWITCH_TO_3D); 
	Page = pg_SWITCH_TO_3D;
	PostMessage(win, WM_COMMAND, Page, 0L);
#else // USE320
#ifdef USE512
	BYSetPrePageSwitch(Page, pg_SWITCH_TO_3D); 
	Page = pg_SWITCH_TO_3D;
	PostMessage(win, WM_COMMAND, Page, 0L);
#else // USE512
#ifdef USE640
	BYSetPrePageSwitch(Page, pg_SWITCH_TO_3D); 
	Page = pg_SWITCH_TO_3D;
	PostMessage(win, WM_COMMAND, Page, 0L);
#else // USE640
   BYSetPrePageSwitch(Page, pg_CHOOSE_MODE); 
	Page = pg_CHOOSE_MODE;
	PostMessage(win, WM_COMMAND, Page, 0L); 
#endif // USE640
#endif // USE512
#endif // USE320

	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYSwitchTo3D(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_SWITCH_TO_3D);

//	whichRobot = 1;
   GameStates.CurrentRobot=SabreRobot;

   MidCmd = MID_STOP;
	BYMidiCenter();

	YBSetUpSoundSystem(win);
	YBLoadSounds(win, GameStates.CurrentLevel, GameStates.CurrentRobot);
	MidCmd = MID_PLAY;
	MidNewIdx = GameStates.CurrentLevel - 1;
	BYMidiCenter();

	bBYRenderingIsOK = FALSE;
	
	int mode;

	bInWrapper = FALSE;
	//di.DeleteDIMsDevice();

	BYExitFromMainMenu();

	BYSelectRMode();

	BYIniFor3DGame();

	if (!BYCreateD3DRMetc(myglobs.hWndMain))
	{
		return FALSE;
	}

	if (!BYCreateDDDFor3DGame(0, myglobs.hWndMain, BYAfterDeviceCreated,
									NULL, BYPreDeviceDestroyed, NULL, &d3dapp)) 
	{
		BYDumpInfo(D3DAppLastErrorString());
		return FALSE;
	}

	if (VM_W3D==320)
	{
		char backname[32];

		strcpy(backname, "back10.bmp");
		backname[5] += VSize-1;    // makes "back10.bmp", "back11.bmp", etc.

		BYLoadOverlay(2, ConstructLevelName(backname));
		BYLoadOverlay(3, ConstructLevelName("WS120.BMP")); 
	}
	else
	if (VM_W3D==640)
	{
		char backname[32];

		strcpy(backname, "back20.bmp");
		backname[5] += VSize-1;    // makes "back10.bmp", "back11.bmp", etc.

		BYLoadOverlay(2, ConstructLevelName(backname));
		BYLoadOverlay(3, ConstructLevelName(BmpFile[AskQuit]));  
	}
	else
	if (VM_W3D==512)
	{
		char backname[32];

		strcpy(backname, "back30.bmp");
		backname[5] += VSize-1;    // makes "back10.bmp", "back11.bmp", etc.

		BYLoadOverlay(2, ConstructLevelName(backname));
		BYLoadOverlay(3, ConstructLevelName(BmpFile[AskQuit]));  
	}
	BYSetUIDumpCo();

	BYSetPrePageSwitch(Page, pg_SHOW_GAME_SCREEN); 
	Page = pg_SHOW_GAME_SCREEN;
	PostMessage(win, WM_COMMAND, Page, 0L); 
	return TRUE;

exit_with_false:
	return FALSE;

}

BOOL BYModeSelection(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_CHOOSE_MODE);

	BYLoadOverlay(1, BmpFile[MainBackground]); 
	SetShowScreenPara();
	BYDisplayText = ShowScreenSettings;
	DDtext = TRUE;
	bInVModeMenu = TRUE;

	return TRUE;
exit_with_false:
	return FALSE;
}
int BYSelectModeFromKBD(WORD wparam)
{
	int j=0;

	switch(wparam) 
	{
	case VK_DOWN:
	case VK_RIGHT:
		tpmode = (tpmode+1) % total_modes;
		break;
	case VK_UP:
	case VK_LEFT:
		tpmode = (tpmode-1+total_modes) % total_modes;
		break;
	case VK_RETURN:
		sndPlaySound(WrapSnd1, SND_ASYNC);
		current_mode = tpmode;
		VM_W3D = d3dappi.Mode[inner_mode[current_mode]].w; 
		VM_H3D = d3dappi.Mode[inner_mode[current_mode]].h; 
		VM_BPP3D = d3dappi.Mode[inner_mode[current_mode]].bpp;  
		{
			int i, l;
			l = strlen(BmpPath);
			while (l>0)
			{
				if (BmpPath[l-1]=='\\')
				{
					if (VM_W3D==640)
						strcpy(&BmpPath[l], "BMP640");
					else if (VM_W3D==512)
						strcpy(&BmpPath[l], "BMP512");
					else if (VM_W3D==320)
						strcpy(&BmpPath[l], "BMP320");

					break;
				}
				l--;
			}
		}
      if (VM_W3D != 640) 
      {
         if (sStretch.bWillStretch)
         {
            sStretch.bWillStretch = FALSE;
            VSize = 1;
         }
      }
      else
      {
         if (VSize == 1)
         {
            sStretch.bWillStretch = TRUE;
            VSize = 4;
         }
      }

		BYOBGetBitmapPath(VM_W3D);
		j = 1;
		break;
	case VK_ESCAPE:
		j = PG_BACK;
		break;
	}
	return j;
}

BOOL BYKdModeSelection
(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	short retval;

   ISKEYDOWN(msg);
	ISPAGE(pg_CHOOSE_MODE);

	if (msg==WM_CHAR)
	{
		return FALSE;
	}
	retval=BYSelectModeFromKBD(wParam);
	if (retval==PG_BACK) 
	{
		DDtext = FALSE;
		BYDisplayText=BYDisplayStr;
		bInVModeMenu = FALSE;
		MidCmd = MID_STOP;
		BYMidiCenter();
		PostMessage(win, WM_DESTROY, 0, 0L);
		return FALSE;
	}
	else if (retval>=1 && retval<=3)
	{
		DDtext = FALSE;
		BYDisplayText=BYDisplayStr;
		bInVModeMenu = FALSE;
		BYSetPrePageSwitch(Page, pg_SWITCH_TO_3D); 
		Page = pg_SWITCH_TO_3D;
		PostMessage(win, WM_COMMAND, Page, 0L);
	}
	return TRUE;
exit_with_false:
	return FALSE;
}

// Before call this function, you need to release all your 3D stuff safely!
BOOL BYSwitchFrom3DTo2D(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_FROM_3D_TO_2D);
   SAMEPAGE();
	//Tim Stretch: do not stretch in wrapper
	sStretch.bStretch = FALSE;

	bBYRenderingIsOK = FALSE;
	BYClearOverlaySurface(1);
	BYBlitOnToP(1, TRUE);
	BYDrawOverLay(1, TRUE);
	//bBYRenderingIsOK = FALSE;

	di.DeleteDIMsDevice();

	YBUnLoadSoundSystem(win);
	BYRestoreGDIobjects();

	//BYKbrdHandler[pg_SHOW_3D_SAMPLE] = BYDefaultHandler;  

	int mode;

	BYCleanUp3DSysStuff();

	if (!BYCreateDDForWrapper(myglobs.hWndMain))
	{
		return FALSE;
	}

	///di.CreateDIMsDevice(TRUE);
	//di.TurnOnMsCursor(FALSE);

	bInWrapper = TRUE;

	BYRender = Render2DWorld;
	BYCleanUp = BYExitFromMainMenu;
	nTimer = SetTimer(win, 2, 50, NULL);       

	return TRUE;
exit_with_false:
	return FALSE;
}

BOOL BYTimeFrom3DTo2D(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_FROM_3D_TO_2D);
	IS_WRAPPER_TIMER(wParam);

	KillTimer(win, nTimer);
	//BYSetPrePageSwitch(Page, pg_ENDING_SPLASH); 
	//Page = pg_ENDING_SPLASH;
	BYSetPrePageSwitch(Page, pg_THANKYOU);                    
	Page = pg_THANKYOU;
	PostMessage(BYMainHwnd, WM_COMMAND, Page, 0L);

	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYEndingSplash(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ISPAGE(pg_ENDING_SPLASH);

	BYLoadOverlay(1, "wr133.bmp");  // Load GoMan title bitmap file
	BYSetO1MainMenuB();             // Set display coordinates for overlay 1.
	bBYRenderingIsOK = TRUE;        // Enable rendering
	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL BYKdEndingSplash(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
   ISKEYDOWN(msg);
	ISPAGE(pg_ENDING_SPLASH);

	GameStates.CurrentLevel = Mojave;
	if (wParam==VK_ESCAPE || wParam=='Y' || wParam=='y')
	{
		PostMessage(win, WM_DESTROY, 0, 0L);
	} 
	else if (wParam=='N' || wParam=='n')
	{
	   int i, j;

      for (i=SabreRobot; i<=KaberRobot; i++)
	   {
		   GameStates.IsRobotDead[i] = 0;
	   }
	   for (i=Trainer; i<=Tokyo; i++)
	   {
		   for(j=Alpha;j<=Gamma;++j)
		   {
			   GameStates.IsMonsterDead[i][j] = 0;
		   }
		   GameStates.LevelHonor[i]=TRUE;
	   }
	   GameStates.CurrentLevel = Mojave;
	   GameStates.CurrentSubmonster=Alpha;
	   GameStates.Score=0;
	   GameStates.CurrentRobot=-1;
	   GameStates.MonsterLose=0;
	   GameStates.RobotLose=0;
	   GameStates.IsAutodemo=0;
	   GameStates.IsTraining=0;
	   GameStates.Is3DMovie=0;
	   GameStates.IsNetplay=0;
	   GameStates.Hours=0;
	   GameStates.Minutes=0;
	   GameStates.Seconds=0;
		BYSetPrePageSwitch(Page, pg_SHOW_GOMAN_TITLE);                    
		Page = pg_SHOW_GOMAN_TITLE;
		//BYSetPrePageSwitch(Page, pg_THANKYOU);                    
		//Page = pg_THANKYOU;
		PostMessage(BYMainHwnd, WM_COMMAND, Page, 0L);
	}
	return TRUE;

exit_with_false:
	return FALSE;
}

BOOL FindDirectX3a(void)
{
	int i, j;
	DWORD m;
	char **vv, *v;
	OFSTRUCT offile;
	char wdir[255], fversion[1000];

	i = GetSystemDirectory(wdir, sizeof(wdir));
	if (i<=0)
	{
		MessageBox(NULL, "This game runs under Windows95", "ERROR", MB_OK);
		return FALSE;
	}

	strcat(wdir, "\\DDRAW.DLL");
	if (OpenFile(wdir, &offile, OF_EXIST)==HFILE_ERROR)
	{
		MessageBox(NULL, "Please install DirectX first, then install this game", "ERROR", MB_OK);
		return FALSE;
	}

	i = GetFileVersionInfoSize(wdir, &m);

	if (!GetFileVersionInfo(wdir, 0, i, fversion))
	{
		MessageBox(NULL, "Cannot get DirectX information", "ERROR", MB_OK);
		return FALSE;
	}

	VerQueryValue(fversion, 
		TEXT("\\StringFileInfo\\040904E4\\FileVersion"), (void **)&v, (unsigned int *)&i);
	
	//v = *vv;
	for (j=0; j<i; j++)
		wdir[j] = v[j];

	if (!strcmp(wdir, "4.04.00.0068"))
	{
		//MessageBox(NULL, "DirectX 3 is found", "INFORMATION", MB_OK);
		return TRUE;
	}
	else if (!strcmp(wdir, "4.03.00.1096"))
	{
		MessageBox(NULL, "DirectX 2 is found, but you need to install DirectX 3a", "WARNING", MB_OK);
		return FALSE;
	} 
	else if (!strcmp(wdir, "4.02.0095"))
	{
		MessageBox(NULL, "DirectX 1 is found, but you need to install DirectX 3a", "WARNING", MB_OK);
		return FALSE;
	}
	return FALSE;
}

#endif // FREEWARE
// freeware functions above

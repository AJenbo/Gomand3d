/*
$Header:   H:/pvcs/pvcsproj/gomand3d.prj/BYGLOBAL.H_V   1.16   07 Apr 1997 14:54:34   JEREMIAH  $

$Log:   H:/pvcs/pvcsproj/gomand3d.prj/BYGLOBAL.H_V  $
 * 
 *    Rev 1.16   07 Apr 1997 14:54:34   JEREMIAH
 * Added vramsize variable.
 * 
 *    Rev 1.15   14 Mar 1997 14:00:14   JEREMIAH
 * Added hw3dacc variable.
 * 
 *    Rev 1.14   28 Feb 1997 13:54:16   BO
 * added extern BOOL bScaleRadar
 * 
 *    Rev 1.13   27 Feb 1997 16:44:34   BO
 * defined an extern variable for game pad control
 * 
 *    Rev 1.12   26 Feb 1997 17:50:14   BO
 * added 3 extern variables definition
 * 
 *    Rev 1.11   14 Feb 1997 20:28:20   BRUCE
 * changed level to GameStates.CurrentLevel
 * changed OldLevel to GameStates.CurrentLevel
 * changed AutoDemoFlag to GameStates.IsAutodemo
 * changed PlayMode to GameStates.IsTraining
 * changed netPlay to GameStates.IsNetplay
 * 
 * 
 *    Rev 1.10   06 Feb 1997 08:08:52   BRUCE
 * Globally took over control of which Robot.
 * 
 *    Rev 1.9   05 Feb 1997 17:40:46   JEREMIAH
 * Changed by Bo.
 * added a few extern varaible definitions
 * 
 * 
 *    Rev 1.8   31 Jan 1997 13:58:06   JEREMIAH
 * Changed by Bo.
 * Added 3 video mode options to compile
 * freeware version.
 * 
 *    Rev 1.7   10 Jan 1997 16:10:44   BO
 * added ScreenCaptureFlag extern definition
 * 
 *    Rev 1.6   09 Jan 1997 14:59:38   BO
 * added a few extern definition
 * 
 *    Rev 1.5   07 Jan 1997 09:34:26   BO
 * moved several global variables declarations
 * to this file
 * 
 *    Rev 1.4   17 Dec 1996 11:22:12   JEREMIAH
 * Changed by Bo.  Added support for 512
 * mode.
 * 
 *    Rev 1.3   13 Nov 1996 16:03:56   BO
 *  declare extern BOOL bShowGameUI
 * 
 *    Rev 1.2   Nov 01 1996 11:25:32   JEREMIAH
 * Changed by Bo.  Added variable 
 * declarations.
 * 
 *    Rev 1.1   Oct 24 1996 14:36:32   JEREMIAH
 * Changed by Bo.  Added bBYRenderingIsOK
 * declaration.

*/

#ifndef __BYGLOBAL_H__
#define __BYGLOBAL_H__
 
#ifdef __cplusplus
extern "C" {
#endif

#define SYS_REAL_GAME  1
#define SYS_TRAINING   2
#define SYS_QUITTOMAIN 3

typedef BOOL (*FunctionCall) (void);
typedef void (*GameUIDisplay) (BOOL show);

extern HWND BYMainHwnd;
extern HINSTANCE BYMainInstance;
//extern int VMode;
extern int VM_W;
extern int VM_H;
extern int VM_BPP;
extern int VM_W3D;
extern int VM_H3D;
extern int VM_BPP3D;
extern int VSize;
extern BOOL VM_FULLSCREEN;
//extern int level, OldLevel, , 
extern int whichavi, LevelSoFar;
extern short SFXValue;
extern short MidValue;
//extern unsigned short RobotStatus[5];
extern unsigned char Hours;
extern unsigned char Minutes;
extern unsigned char Seconds;
extern FunctionCall BYRender;
extern BOOL DDmode0, DDmode1, DDmode2, DDmode3, DDtext;
extern WORD nTimer; 
//extern BOOL AutoDemoFlag;
extern BOOL AutoDemoNext;
//extern short PlayMode;
extern BOOL QuitFlag;

extern short MidCmd;
extern short MidSts;
extern short MidNewIdx;
extern short MidOldIdx;
extern short KnobLength;
extern short BarLength;
extern short BarStartP;

extern BOOL bBYRenderingIsOK;
extern BOOL YBReachMidEnd;
extern short  TotalTargets;
extern short  ScaleFactor;
extern short  playfrom;
extern RECT GWinSize[3][3];
extern BOOL bShowGameUI;
extern int RMode;
extern BOOL bAskQuit; 
extern BOOL PlayAsMonster;	
extern WORD SimuMode;
extern UINT TimerId;
extern int DisplayDebugMsgFlag;
//extern int netPlay;
extern int isHost;
extern int HasKey;
extern int beSynchronous;
extern unsigned long  MyId;

extern short valid_cntion[10];
extern short total_cntion;
extern BOOL bInWrapper;
extern short msact;
extern BOOL ScreenCaptureFlag;
extern int  VRAM_Range;  // added by Bo on 1/29/97
extern short	total_joycfg;  // added by Bo on 1/30/97
extern short	current_joycfg; // added by Bo on 1/30/97
extern short current_mscfg; // added by Bo on 1/30/
extern short tpjoycfg, tpmscfg; // added by Bo on 1/30
extern DWORD bd0;
extern long int JoyActions[];
extern BOOL bFindJoystick;
extern int P5Chip, P6Chip, MMXChip, hw3dacc, vramsize;
extern BOOL bUseGameProfile;
extern BOOL bScaleRadar;

#ifdef __cplusplus
};
#endif

#endif __BYGLOBAL_H__

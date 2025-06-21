#ifndef __WRAPPER_H__
#define __WRAPPER_H__
 
#define pg_START             0
#define pg_SHOW_GOMAN_TITLE  1+pg_START
#define pg_SHOW_MAIN_MENU    1+pg_SHOW_GOMAN_TITLE
#define pg_SHOW_NEXTMISSION  1+pg_SHOW_MAIN_MENU
#define pg_SHOW_CHAR_MENU    1+pg_SHOW_NEXTMISSION
#define pg_SHOW_MOVIE_MENU   1+pg_SHOW_CHAR_MENU
#define pg_AVIPLAY_DELAY     1+pg_SHOW_MOVIE_MENU 
#define pg_SHOW_TRAIN_MENU   1+pg_AVIPLAY_DELAY
#define pg_SHOW_OPTION_MENU  1+pg_SHOW_TRAIN_MENU
#define pg_SHOW_MOUSECFG     1+pg_SHOW_OPTION_MENU
#define pg_SHOW_JOYSKCFG     1+pg_SHOW_MOUSECFG
#define pg_SHOW_LOAD_MENU    1+pg_SHOW_JOYSKCFG
#define pg_SHOW_SAVE_MENU    1+pg_SHOW_LOAD_MENU
#define pg_SHOW_KBD_MENU     1+pg_SHOW_SAVE_MENU
#define pg_SHOW_3D_SAMPLE    1+pg_SHOW_KBD_MENU
#define pg_DECIDE_LOSESTATUS 1+pg_SHOW_3D_SAMPLE
#define pg_SHOW_LOSE_ONE     1+pg_DECIDE_LOSESTATUS
#define pg_SHOW_LOSE_ALL     1+pg_SHOW_LOSE_ONE
#define pg_PLAY_MOVIE        1+pg_SHOW_LOSE_ALL
#define pg_SHOW_AVI_BMP      1+pg_PLAY_MOVIE
#define pg_DECIDE_M3STATUS   1+pg_SHOW_AVI_BMP
#define pg_M3_SHOWLOSEBMP    1+pg_DECIDE_M3STATUS
#define pg_M3_BACKTOMAIN     1+pg_M3_SHOWLOSEBMP
#define pg_M3_RESTOREALL	 1+pg_M3_BACKTOMAIN
#define pg_M3_SHOWWINBMP     1+pg_M3_RESTOREALL
#define pg_SET_CHAR_TIMER    1+pg_M3_SHOWWINBMP
#define pg_M3_SELECTARobot    1+pg_SET_CHAR_TIMER
#define pg_SWITCH_3DTO2D     1+pg_M3_SELECTARobot
#define pg_NEXT_AUTODEMO     1+pg_SWITCH_3DTO2D
#define pg_DECIDE2D_AFTGAME  1+pg_NEXT_AUTODEMO
#define pg_UNLOAD_REALGAME   1+pg_DECIDE2D_AFTGAME
#define pg_DECIDE_WINSTATUS  1+pg_UNLOAD_REALGAME
#define pg_REAL_WONFINAL     1+pg_DECIDE_WINSTATUS
#define pg_REAL_WONMIDDLE    1+pg_REAL_WONFINAL
#define pg_END_OF_TRAIN      1+pg_REAL_WONMIDDLE
#define pg_SHOW_POPULATION   1+pg_END_OF_TRAIN
#define pg_SHOW_TOP3         1+pg_SHOW_POPULATION
#define pg_SHOW_CREDITS      1+pg_SHOW_TOP3
#define pg_MODIFY_TOPLIST    1+pg_SHOW_CREDITS
#define pg_END_MOVIE         1+pg_MODIFY_TOPLIST
#define pg_NEW_THANKYOU      1+pg_END_MOVIE
#define pg_FINAL_EXIT        1+pg_NEW_THANKYOU
#define pg_SHOW_GAME_SCREEN  1+pg_FINAL_EXIT
#define pg_SETUP_SNDSYSTEM   1+pg_SHOW_GAME_SCREEN
#define pg_ENTER3D_DELAY     1+pg_SETUP_SNDSYSTEM
#define pg_FROM_3D_TO_2D     1+pg_ENTER3D_DELAY
#define pg_MISSION_AVI       1+pg_FROM_3D_TO_2D
#define pg_LAST_QUESTION     1+pg_MISSION_AVI
// below are definitions used for freeware only!!
#define pg_GET_D3DINFO       1+pg_LAST_QUESTION
#define pg_CHOOSE_MODE       1+pg_GET_D3DINFO
#define pg_SWITCH_TO_3D      1+pg_CHOOSE_MODE
#define pg_ENDING_SPLASH     1+pg_SWITCH_TO_3D
#define pg_END               1+pg_ENDING_SPLASH
// above are definitions used for freeware only!!
// hey, I already put pg_END above, now it looks like
// there will never be an end of this game?!
#define pg_INTRO_MOVIE       1+pg_END
#define pg_NET_WAIT_FOR_JOIN 1+pg_INTRO_MOVIE
#define pg_NET_WAIT_FOR_OPPONENT 1+pg_NET_WAIT_FOR_JOIN
#define pg_NET_SHOW_SCORE    1+pg_NET_WAIT_FOR_OPPONENT
#define pg_NET_OPPONENT_LEFT 1+pg_NET_SHOW_SCORE
#define pg_NET_ERROR         1+pg_NET_OPPONENT_LEFT 
#define pg_THANKYOU          1+pg_NET_ERROR
#define TOTALPAGE            1+pg_THANKYOU

#define WP_NOTHING           100
#define WP_MOUSEMOVE         101
#define WP_LBUTTONDOWN       102

#ifdef __cplusplus
extern "C" {
#endif

extern int Page;
extern int OldPage;
extern LPDIRECTDRAWSURFACE     lpDDSOverlay[3];

extern HCURSOR mycursor;
extern BOOL bShowCursor;

#undef ISPAGE
#define ISPAGE(x) if (Page!=x) goto exit_with_false

#undef SAMEPAGE
#define SAMEPAGE() if (OldPage==Page) goto exit_with_false; else OldPage=Page

#undef ISKEYDOWN
#define ISKEYDOWN(x) if (x!=WM_KEYDOWN) goto exit_with_false

#undef IS_WRAPPER_TIMER
#define IS_WRAPPER_TIMER(x) if (x!=2) goto exit_with_false

typedef BOOL (*MsgHandler) (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
typedef void (*TxtHandler) (BOOL show, short mode);
typedef void (*CleanUpCall) (void);
typedef BOOL (*MsHandler) (HWND win);

extern CleanUpCall BYCleanUp;
extern MsgHandler BYPageHandler[];
extern MsgHandler BYTimeHandler[];
extern MsgHandler BYKbrdHandler[];
extern MsgHandler BYMiceHandler[];
extern BOOL bUseDebug;
extern MsHandler BYMouseHandler[];

BOOL BYSetUpSystemEnvironment
(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
BOOL BYSetupThings4Wrapper(void);

BOOL BYCreate3Overlays(short mode, short size);
void BYClearOverlaySurface(short OverlayNum);
HRESULT DDCopyBitmap(IDirectDrawSurface *pdds, HBITMAP hbm, int x, int y, int dx, int dy);
void BYDrawOverLay(short OverlayNum, BOOL show);
void OverlayToTriBuff(short OverlayNum, BOOL show); //Tim Stretch: for blitting to tri buffer

void BYSurfaceBlt(BOOL show);
void BYClearOverlaySurface(short OverlayNum);
IDirectDrawSurface * BYLoadOverlay(short OverlayNum, LPCSTR szBitmap);
BOOL Render2DWorld(void);
void BYReleaseAllOverlays(void);
int BYGetRealMode(int *vmode_w, int *vmode_h, int *vmode_bpp);
void BYSetBmpFiles(void);
IDirectDrawPalette * BYDDLoadPalette(IDirectDraw *pdd);
void BYDisplayUI(BOOL show); 
void BYSetUIDumpCo(void);
void YBShowAimorQuit(BOOL show);
HRESULT  BYSetColorKey(IDirectDrawSurface *pdds, COLORREF rgb);

BOOL BYTurnToNextNPage(int page, int offset);
BOOL BYChooseTextSurface(short TextSurface);
void BYDisplayStr(BOOL show, short ifsave);

void BYSetPageHandler(void);
void BYSetTimeHandler(void);
void BYSetKbrdHandler(void);
void BYSetMiceHandler(void);

void BYSetPrePageSwitch(int prepage, int postpage); 
void BYSetPostPageSwitch(int page); 

BOOL BYDefaultHandler(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL BYShowGomanTitle(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowMainMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowMovieMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowOptionMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowNextMission(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowCharMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowTrainMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowMouseConFig(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowJoystickConFig(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowLoadMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowSaveMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowKbdConfigure(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowAviDelay(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowPlayMovie(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowAviBmp(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL BYShow3DExample(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL BYDecideLoseStatus(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowLoseOne(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowLoseAll(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYDecideMode3Status(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowM3WinBmp(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowM3LoseBmp(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYBackToMain(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYM3RestoreAll(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYM3SelectARobot(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYSwitchFrom3DTo2D(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowNextDemo(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYDecide2DAfterGame(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYUnloadRealGame(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYDecideWinStatus(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowWonFinal(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowWonMiddle(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYEndOfTraining(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowPopulation(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowTop3(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowCredits(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowEndingMovie(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYShowNewThankYou(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYFinalExit(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYMidiCenter(void);
BOOL BYShowGameScreen(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYSetUpSoundSystem(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYDoEnter3DDelay(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYMissionAvi(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYLastQuestion(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYIntroMovie(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL JSCNetWaitForJoin(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL JSCNetWaitForOpponent(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL JSCNetShowScore(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL JSCNetOpponentLeft(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL JSCNetErrorScreen(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYThankYou(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);

// WM_KEYDOWN MESSAGE HANDLERS
BOOL BYKdGomanTitle(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdMainMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdMovieMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdOptionMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdCharMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdTrainMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdNextMission(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdShowMouseOrConfigure(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdShowLoadMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdShowSaveMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdDoNothing(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKbdDefault(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdMissionAvi(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL BYKdLoseOne(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdKbdConfigure(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdShowAviBmp(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdShowTop3(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdModifyTopList(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdPlayMovie(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKbFrom3DTo2D(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdLoseAll(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdLastQuestion(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdIntroMovie(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL JSCKdNetWaitForJoin(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL JSCKdNetWaitForOpponent(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL JSCKdNetShowScore(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL JSCKdNetOpponentLeft(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL JSCKdNetErrorScreen(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdWonFinal(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdCreditMovie(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdEndingMovie(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdThankYou(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);

// WM_TIMER MESSAGE HANDLERS
BOOL BYTimeGomanTitle(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYTimeNextMission(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYTimeShowMouseOrConfigure(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYTimeAviDelay(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYTimeM3WinOrLoseBmp(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYTimeSetChar(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYTimeShowNextDemo(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYTimeShowWon(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYTimeShowPopulation(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYTimeShowTop3(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYTimeNewThankYou(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYTimeGameScreen(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYTimeEnterDelay(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYTimeFrom3DTo2D(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYTimeReadyToGo(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL JSCTimeNetWaitForJoin(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL JSCTimeNetWaitForOpponent(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL JSCTimeNetShowScore(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL JSCTimeNetOpponentLeft(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL JSCTimeNetErrorScreen(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYTimeThankYou(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);

// WM_MOUSE MESSAGE HANDLERS
BOOL BYMsMainMenu(HWND win);
BOOL BYMsCharMenu(HWND win);
BOOL BYMsTrainMenu(HWND win);
BOOL BYMsMovieMenu(HWND win);
BOOL BYMsLoadMenu(HWND win);
BOOL BYMsSaveMenu(HWND win);
BOOL BYMsOptionMenu(HWND win);

//
BOOL BYMciNotifyHandler(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
//
void YBSetSubTitle1(int Vmode, char *str1, COLORREF color);
// Vmode is obsolete
void YBSetSubTitle2(int Vmode, char *str1, COLORREF color);
// Vmode is obsolete
void YBSetSubTitle3(int Vmode, char *str1, COLORREF color);
// Vmode is obsolete


BOOL BYDumpInfo(char *s);
void BYSelectRMode(void);
void BYExitFromMainMenu(void);
BOOL BYCreateD3DRMetc(HWND win);
BOOL BYSetRenderState(void);
BOOL BYAfterDeviceCreated
(int w, int h, LPDIRECT3DVIEWPORT* lplpViewport, LPVOID lpContext);
BOOL BYPreDeviceDestroyed(LPVOID lpContext);
void BYIniFor3DGame(void);
void BYIniForWrapper(HINSTANCE hInstance);
void BYCleanUp3DSysStuff(void);

void BYShowCursor(void);
void BYHideCursor(void);
void BYSetO1To640x480(void);
void BYSetO1To512x384(void);
void BYSetO1To320x240(void);
void BYDisplayRadar(BOOL show);
void BYBlt3DBackground(BOOL show);
void BYSetupGDIobjects(void);
void BYRestoreGDIobjects(void);
void BYBlitOnToP(short OverlayNum, BOOL show);

BOOL BYRepaintBack(BOOL show);
BOOL BYTestBars(BOOL show);
BOOL BYForceUpdate(BOOL show);
BOOL GetVModeIndx(int *mode);
void ShowNetConnections(BOOL show, short mode);
void ShowSessionList(BOOL show, short mode);
void SetShowScreenPara(void);
void ShowScreenSettings(BOOL show, short mode);
DWORD DDColorMatch(IDirectDrawSurface *pdds, COLORREF rgb);
BOOL BYDefaultMsHandler(HWND win);
BOOL HandleException(HRESULT value);
BOOL BYGetVideoMemoryInfo(void);

#ifdef CAPBMP
BOOL SaveScreenImage(void);
BOOL CaptureScreenImage(void);
#endif
//
BOOL FindDirectX3a(void);

#ifdef FREEWARE
BOOL BYGetD3DInfo(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYSwitchTo3D(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYEndingSplash(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYModeSelection(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdEndingSplash(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdModeSelection(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

BOOL BYKdChooseJoystkCfg(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL BYKdChooseMouseCfg(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
void ShowJoystkSettings(BOOL show, short mode);
void ShowMouseSettings(BOOL show, short mode);
void BYChangeJoystkActions();
void BYChangeMouseActions();

#ifdef __cplusplus
};
#endif

#endif
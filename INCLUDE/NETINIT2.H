#ifndef __NETINIT2_H__
#define __NETINIT2_H__

#ifdef __cplusplus
extern "C" {
#endif

extern int NetMenuState;
extern short nSessionId;
extern short WhichSession;
extern BOOL bSessionList;
extern S_NetPlayMenu S_NPMenu;
extern BOOL  bErrMsg;
extern char  ErrMsg[127];

extern BOOL GetProvider();
extern BOOL CreateSession();
extern BOOL GetGame(short);
extern BOOL HowManySessions();
extern BOOL CreatePlayer(LPSTR lpPlayerName);
extern  int  SelectGameMode( HWND);
extern int QHSelectSessionFromKBD(WPARAM wParam);
extern S_SESSIONDESC2*  S_lpDPGameDesc[MAX_SESSIONS];
extern BOOL JSCHasPlayerJoined();

#ifdef __cplusplus
};
#endif

#endif __NETINIT2_H__
#ifndef __NETMENU_H__
#define __NETMENU_H__

#define PG_BACK -99
#define PROTOCOLFAIL   -11
#define CREATEFAIL     -22
#define COMMUNICATIONFAIL -33
#define GETGAMEFAIL    -44
#define TRYFAIL        -55

#define MAX_PROTOCOLS   8
#define MAX_SESSIONS    4
#define NAME_SIZE       20

#define MID_PLAY 601
#define MID_STOP 602
#define MID_SILENT 603

#define RobotNUM     5
#define MONSTERNUM  6

typedef struct _NetPlayMenu_
{
	//BOOL isSigle;
	BOOL isMulti;
	BOOL isModem;
	BOOL isIPX;
	BOOL isInter;
	BOOL isSerial;
	BOOL isCreate;
	BOOL isConnect;
	BOOL isNetMenu;
	BOOL isRobot;	//Netplay will give it true
	BOOL isMonster; //Netplay will give it true
	BOOL isPlay;	//begin play.
//	int  NetSuccess;//-1,failed, 1, success.
	int  ModeIdx;
	int  NetIdx;
	int  ConIdx;
	int  KeyState;
} S_NetPlayMenu;

typedef struct _S_SESSIONDESC2 {
	DWORD dwSize;
	char  SessionName[NAME_SIZE];
	GUID  Application;
	GUID  Instance;
}S_SESSIONDESC2;


/*
struct ITC_PLAYERDESC2 {
	DWORD dwSize;
	char  PlayerName[NAME_SIZE];
	DPID  PlayerId;
};
*/
#ifdef __cplusplus
extern "C" {
#endif

extern void InitNetPlayMenu();
extern void InitSelectMonsterMenu();
extern void DisplayDebugMsgInfo();
extern void DisplayDebugMsgInfo2();
extern void DisplayNetPlayStatus();

#ifdef __cplusplus
};
#endif

#endif __NETMENU_H__
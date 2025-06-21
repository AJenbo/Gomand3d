//**************************************************************************
// netmenu.cpp
//
// Copyright Inventec(Tian Jin) 1996. All rights reserved.
//
// Author:      Liu Qinghua
//
// Date:        1996, 11. 20
//
// Description: Draw a dialogue Box of net play for Goman95 DirectX 3.0 version.
//              Many functions are reference of YuanBo's Wrapper.spp.
// Notes:       The functions QHRenderNetPlayMenu(void) and QHDrawOverLay 
//              will be added to YBRender2DWorld() function.
//              
//
// Update:
//
//**************************************************************************


#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <math.h>

#include "d3dappi.h"
#include "rmdemo.h"
#include "rmfull.h"
#include "byglobal.h"
#include "wrapper.h"
//#include "ybmid.h"
//#include "ybsnd.h"
//#include "keycom.h"
//#include "netplay.h"
#include "netmenu.h"
#include "netinit2.h"
#include "netplay.h"
#include "global.h"

//Add by Eric 11/12/96
extern "C" 
{

    extern CHARSPECDATA  CharSpecData;
    extern CHARSPECDATA  CharSpecSndData;
	extern D3DVECTOR     YBRobotPos;
	extern D3DVECTOR     YBMonstPos;

	extern   D3DVALUE RobotSpeed,      MonsterSpeed,
		              RobotDistance,   MonsterDistance;
	extern   int      RobotEngy,       MnstEngy,
		              RobotLife,       MnstLife;

	extern   int      RobotMovementState,  MonsterMovementState,
		              RobotAnimationState, MonsterAnimationState;
	extern   D3DVALUE RobotAnimationFrame, MonsterAnimationFrame;

	extern   int   *InputIntPtr;          // Input stream from player
	extern   int   *InputIntPtr2;          // Input stream from player
	extern   int   *InputIntPtr3;          // Input stream from player
	extern   int   Vmode;
}
//end of Eric

extern short  MidCmd;
extern short  MidSts;
extern LPDIRECTDRAWSURFACE     lpDDSText;
extern LPDIRECTDRAWSURFACE     lpDDSOverlay[3];  
extern HFONT BYSelectFont (HDC hdc, char *FontName, short w, short h);

extern "C"
{
	//extern BOOL isHost;
	//extern BOOL beSynchronous;
	extern BOOL bSessionList;
	extern short WhichSession;
	extern short nSessionId ;
	extern S_SESSIONDESC2*  S_lpDPGameDesc[MAX_SESSIONS];
	extern BOOL sendDWORD(DWORD dwSnd);
	extern BOOL receiveDWORD(LPDWORD lpdwRcv);
}

void InitSelectMonsterMenu();
BOOL QHWaitAnotherPlayer();
BOOL QHRenderWaitConnectBefore3D();

BOOL bSelectRobot = FALSE;
BOOL bSelectMonster = FALSE;
BOOL bMonsterMenu = FALSE;
BOOL bConnectFlag = FALSE;

//BOOL bRenderMenu = TRUE;

//The follow data are prepared for draw netplay menu.
char sDialogue1[3][20] = {"GameMode", "SinglePlayer", "MultiPlayer"};
char sDialogue2[5][20] = {"Choose Connection", "Modem Connect",
						   "WinSock IPX", "Internet", "Serial"};
char sDialogue3[3][30] = {"Create or Connect Game?",
                          "Create", "Connect"};

WORD wDialogueBox[4] = {0, 0, 100, 20};
WORD wDialogue1Pos[4][2] = {265, 90,
                            250, 125,
							250, 150};

WORD wDialogue2Pos[5][2] = {250, 90,
                            260, 125,
							260, 150,
                            260, 175,
                            260, 200};

WORD wDialogue3Pos[3][2] = {200, 100,
                            200, 150,
                            330, 150};

WORD wBoxPosX, wBoxPosY;

////////////////////////////////////
   //extern "C"
   //{
   //}
   //extern int GameStates.CurrentRobot;
///////////////////////////////////

void InitNetPlayMenu()
{
///////////////////////////////////	
   //PlayAsMonster = TRUE; //Only for testing! Liou
   //GameStates.CurrentRobot = 1;
   //level = 1;
/////////////////////////////////////
	//S_NPMenu.isSigle   = FALSE;
	S_NPMenu.isMulti   = FALSE;
	S_NPMenu.isModem   = FALSE;
	S_NPMenu.isIPX     = FALSE;
	S_NPMenu.isInter   = FALSE;
	S_NPMenu.isSerial  = FALSE;
	S_NPMenu.isCreate  = FALSE;
	S_NPMenu.isConnect = FALSE;
	S_NPMenu.isNetMenu = TRUE;
	S_NPMenu.isRobot    = FALSE;//Netplay will give it true
	S_NPMenu.isMonster = FALSE;//Netplay will give it true
	S_NPMenu.isPlay    = FALSE;//begin play.
	//S_NPMenu.NetSuccess = 0;   //-1,failed, 1, success.
	S_NPMenu.ModeIdx = 0;
	S_NPMenu.NetIdx  = 0;
	S_NPMenu.ConIdx  = 0;
	S_NPMenu.KeyState = 1;
} 

/***************************************************************************
// Name:        QHNetPlayFirstDialogue()

// Author:      Liu Qinghua

// Date:        1996, 11.20

// Description: Draw dialogue box to select GameMode, Protocol, 
                StartOrJoin .

// Arguments:   No

// Return:      TRUE : success to render.
				FALSE: failure.
                     
****************************************************************************/


BOOL QHNetPlayFirstDialogue()
{
   HBRUSH hNewBrush, hOldBrush;
   HFONT hNewFont, hOldFont;
   IDirectDrawSurface *pdds;
   HDC  hDC;
   int i;
   
   pdds = d3dappi.lpBackBuffer; //lpDDSOver1;  
   if (pdds->GetDC(&hDC)==DD_OK) 
   {
	  if(!S_NPMenu.isMulti)
	  {
		  hNewFont = GetStockObject(ANSI_FIXED_FONT);
			  //BYSelectFont(hDC, "System", 5, 11);

		  SelectObject(hDC, hNewFont);
		  SetBkColor(hDC, NULL);
		  SetBkMode(hDC, TRANSPARENT);
		  SetTextColor(hDC, RGB(255, 255, 255));

		  hNewBrush = CreateSolidBrush (RGB(0, 0, 255));
		  hOldBrush = SelectObject (hDC, hNewBrush);
      
		  //Rectangle(hDC, 200, 120, 300,150);
		  wBoxPosX = wDialogue1Pos[S_NPMenu.ModeIdx + 1][0] - 5;
		  wBoxPosY = wDialogue1Pos[S_NPMenu.ModeIdx + 1][1] - 4;

		  Rectangle(hDC, wDialogueBox[0] + wBoxPosX,
						 wDialogueBox[1] + wBoxPosY,
						 wDialogueBox[2] + wBoxPosX,
						 wDialogueBox[3] + wBoxPosY);


		  TextOut(hDC, wDialogue1Pos[0][0], wDialogue1Pos[0][1], 
				  sDialogue1[0], lstrlen(sDialogue1[0]));
		  TextOut(hDC, wDialogue1Pos[0][0] - 10, wDialogue1Pos[0][1] + 5, 
				  "__________", 10);
		  TextOut(hDC, wDialogue1Pos[1][0], wDialogue1Pos[1][1], 
				  sDialogue1[1], lstrlen(sDialogue1[1]));
		  TextOut(hDC, wDialogue1Pos[2][0], wDialogue1Pos[2][1], 
				  sDialogue1[2], lstrlen(sDialogue1[2]));			
	  }
	  else
	  {
		  if(!S_NPMenu.isModem && !S_NPMenu.isIPX && 
			  !S_NPMenu.isInter && !S_NPMenu.isSerial)
		  {
			  hNewFont = GetStockObject(ANSI_FIXED_FONT);
				  //BYSelectFont(hDC, "System", 5, 11);

			  SelectObject(hDC, hNewFont);
			  SetBkColor(hDC, NULL);
			  SetBkMode(hDC, TRANSPARENT);
			  SetTextColor(hDC, RGB(255, 255, 255));

			  hNewBrush = CreateSolidBrush (RGB(0, 0, 255));
			  hOldBrush = SelectObject (hDC, hNewBrush);
      
			  //Rectangle(hDC, 200, 120, 300,150);
			  wBoxPosX = wDialogue2Pos[S_NPMenu.NetIdx + 1][0] - 5;
			  wBoxPosY = wDialogue2Pos[S_NPMenu.NetIdx + 1][1] - 4;

			  Rectangle(hDC, wDialogueBox[0] + wBoxPosX,
							 wDialogueBox[1] + wBoxPosY,
							 wDialogueBox[2] + wBoxPosX + 10,
							 wDialogueBox[3] + wBoxPosY);
			  for(i = 0; i < 5; i++)
			  {
				  TextOut(hDC, wDialogue2Pos[i][0], wDialogue2Pos[i][1], 
					  sDialogue2[i], lstrlen(sDialogue2[i]));
			  }
			  TextOut(hDC, wDialogue2Pos[0][0], wDialogue2Pos[0][1] + 5, 
				  "_________________", 17);
		  }
		  else
		  {
			  hNewFont = GetStockObject(ANSI_FIXED_FONT);
				  //BYSelectFont(hDC, "System", 5, 11);

			  SelectObject(hDC, hNewFont);
			  SetBkColor(hDC, NULL);
			  SetBkMode(hDC, TRANSPARENT);
			  SetTextColor(hDC, RGB(255, 255, 255));

			  hNewBrush = CreateSolidBrush (RGB(0, 0, 255));
			  hOldBrush = SelectObject (hDC, hNewBrush);
      
			  //Rectangle(hDC, 200, 120, 300,150);
			  wBoxPosX = wDialogue3Pos[S_NPMenu.ConIdx + 1][0] - 5;
			  wBoxPosY = wDialogue3Pos[S_NPMenu.ConIdx + 1][1] - 4;

			  Rectangle(hDC, wDialogueBox[0] + wBoxPosX,
							 wDialogueBox[1] + wBoxPosY,
							 wDialogueBox[2] + wBoxPosX - 20,
							 wDialogueBox[3] + wBoxPosY);
			  for(i = 0; i < 3; i++)
			  {
				  TextOut(hDC, wDialogue3Pos[i][0], wDialogue3Pos[i][1], 
					  sDialogue3[i], lstrlen(sDialogue3[i]));
			  }
			  TextOut(hDC, wDialogue3Pos[0][0], wDialogue3Pos[0][1] + 10, 
				  "_______________________", 23);
		  }
	  }

	  SelectObject(hDC, hOldFont);
      DeleteObject(hNewFont);
      
	  SelectObject (hDC, hOldBrush);
      DeleteObject (hNewBrush);
      
	  pdds->ReleaseDC(hDC);
	  return TRUE;
   }
   return FALSE;
}

/***************************************************************************
// Name:        QHNetPlaySelectSession()

// Author:      Liu Qinghua

// Date:        1996, 11.20

// Description: Draw session list. It can list 10 sessions mostly,
                you can select a session to join. 

// Arguments:   No

// Return:      TRUE : success to render.
				FALSE: failure.
                     
****************************************************************************/


WORD DataX = 150;
WORD DataY = 15;
WORD SessionListX = 200;
WORD SessionListY = 100;
char SessionListHead[20] = "Select A Session";

BOOL QHNetPlaySelectSession()
{
   HBRUSH hNewBrush, hOldBrush;
   HFONT hNewFont, hOldFont;
   IDirectDrawSurface *pdds;
   HDC  hDC;
   int i;
   
   pdds = d3dappi.lpBackBuffer; //lpDDSOver1;  
   if (pdds->GetDC(&hDC)==DD_OK) 
   {
	  if(bSessionList)
	  {
		  hNewFont = GetStockObject(ANSI_FIXED_FONT);
			  //BYSelectFont(hDC, "System", 5, 11);

		  SelectObject(hDC, hNewFont);
		  SetBkColor(hDC, NULL);
		  SetBkMode(hDC, TRANSPARENT);
		  SetTextColor(hDC, RGB(255, 255, 255));

		  //hNewBrush = CreateSolidBrush (RGB(0, 255, 0));
		  //hOldBrush = SelectObject (hDC, hNewBrush);
      
		  //Rectangle(hDC, SessionListX - 15, SessionListY - 2 * DataY ,
		//				SessionListX + DataX + 10, SessionListY + 11 * DataY);
	    //  SelectObject (hDC, hOldBrush);
        //  DeleteObject (hNewBrush);

		  hNewBrush = CreateSolidBrush (RGB(0, 0, 255));
		  hOldBrush = SelectObject (hDC, hNewBrush);
      
		  Rectangle(hDC, SessionListX - 5, SessionListY + WhichSession * DataY + 2,
						SessionListX + DataX - 7, SessionListY + (WhichSession + 1) * DataY) + 2;

		  TextOut(hDC, SessionListX, SessionListY - DataY - 10,
				  SessionListHead, lstrlen(SessionListHead));
		  TextOut(hDC, SessionListX , SessionListY - 20,
				  "_________________", 17);
		 
		  for(i = 0; i < nSessionId; i++)
		  {
		     TextOut(hDC, SessionListX, SessionListY + i * DataY + 2,
				  //SessionName[i], lstrlen(SessionName[i]));
				  S_lpDPGameDesc[i]->SessionName,
				  lstrlen(S_lpDPGameDesc[i]->SessionName));
			 TextOut(hDC, SessionListX, SessionListY + (i + 1) * DataY - 10,
				  "_________________", 17);
		  }
	  }

	  SelectObject(hDC, hOldFont);
      DeleteObject(hNewFont);
      
	  SelectObject (hDC, hOldBrush);
      DeleteObject (hNewBrush);
      
	  pdds->ReleaseDC(hDC);
	  return TRUE;
   }
   return FALSE;
}


/***************************************************************************
// Name:        QHNetPlayWaitConnect()

// Author:      Liu Qinghua

// Date:        1996, 11.20

// Description: Draw some strings, tell player what you play as.

// Arguments:   No

// Return:      TRUE : success to render.
				FALSE: failure.
                     
****************************************************************************/

char sConnecting[7][20] = {"Connecting",
                           "Connecting .",
						   "Connecting ..",
						   "Connecting ...",
						   "Connecting ....",
						   "Connecting .....",
						   "Connecting ......"};

char sBeforePlay[2][50] = {
	"You Play As Robot, Now Waiting For Monster!",
	"You Play As Monster, Now Waiting Fighting!"
};

BOOL QHNetPlayWaitConnect()
{
//   HFONT hNewFont, hOldFont;
//   IDirectDrawSurface *pdds;
//   HDC  hDC;
   static int count_connect = 0;
   static int counter = 0;  //This is only to imitate connection, 

   
   //pdds = d3dappi.lpBackBuffer; //lpDDSOver1;  

   //if (pdds->GetDC(&hDC)==DD_OK) 
   {
      /*
	  hNewFont = //GetStockObject(ANSI_FIXED_FONT);
		  BYSelectFont(hDC, "System", 10, 18);

	  SelectObject(hDC, hNewFont);
	  SetBkColor(hDC, NULL);
	  SetBkMode(hDC, TRANSPARENT);
	  SetTextColor(hDC, RGB(255, 255, 0));
     

	  if(!S_NPMenu.isPlay)
	  {
		  if(S_NPMenu.isRobot)
		  {
			 TextOut(hDC, 200, 150, sBeforePlay[0], lstrlen(sBeforePlay[0]));
		  }
		  else if(S_NPMenu.isMonster)
		  {
			 TextOut(hDC, 200, 150, sBeforePlay[1], lstrlen(sBeforePlay[1]));
		  }

		  //TextOut(hDC, 250, 200, sConnecting[count_connect], lstrlen(sConnecting[count_connect]));
      }
      */
	  count_connect++;
	  if(count_connect > 6) count_connect = 0;
		
	  int    opponent;
     
		
	  if (isHost) 
	  {
		 //send level monster selected to Host
		 //if(GameStates.CurrentRobot < SabreRobot || GameStates.CurrentRobot >KaberRobot) return FALSE;
		 sendDWORD((DWORD)S_NPMenu.isCreate);
		 if (receiveDWORD((LPDWORD)(&opponent)))
		 {
			S_NPMenu.isPlay = TRUE;
		 }
	  }
	  else
	  {
		 sendDWORD((DWORD)S_NPMenu.isConnect);
		 if (receiveDWORD((LPDWORD)(&opponent)))
		 {	
			S_NPMenu.isPlay = TRUE;
		 }
	  }
	
   
      if(counter >= 30) 
      {
	     S_NPMenu.isPlay = TRUE;
      }
	  counter ++;
	  ///////////////////////// end
	  //SelectObject(hDC, hOldFont);
      //DeleteObject(hNewFont);
      
	  //pdds->ReleaseDC(hDC);
	  return TRUE;
   }

   return FALSE;
}

/***************************************************************************
// Name:        QHNetPlayFailMessage()

// Author:      Liu Qinghua

// Date:        1996, 11.20

// Description: Draw failure message. It may be failure to create
                netplay, the function tells you where is the problem.

// Arguments:   No

// Return:      TRUE : success to render.
				FALSE: failure.
                     
****************************************************************************/

char sNetPlayFail[6][50] = {
	"Can't Enumerate protocol,",
	"Can't create DirectPlay,",
	"Can't establish communication,",
	"No player created,",
	"Can't create player,",
	"Try again or press 'ESC' key to exit !"
};

BOOL QHNetPlayFailMessage()
{
   HFONT hNewFont, hOldFont;
   IDirectDrawSurface *pdds;
   HDC  hDC;

   pdds = d3dappi.lpBackBuffer; //lpDDSOver1;  

   if (pdds->GetDC(&hDC)==DD_OK) 
   {
	  hNewFont = //GetStockObject(ANSI_FIXED_FONT);
		  BYSelectFont(hDC, "System", 10, 18);

	  SelectObject(hDC, hNewFont);
	  SetBkColor(hDC, NULL);
	  SetBkMode(hDC, TRANSPARENT);
	  SetTextColor(hDC, RGB(255, 255, 0));

      switch(S_NPMenu.KeyState)
	  {
	  case PROTOCOLFAIL:
   	     TextOut(hDC, 210, 170, sNetPlayFail[0], lstrlen(sNetPlayFail[0]));
		 TextOut(hDC, 210, 190, sNetPlayFail[5], lstrlen(sNetPlayFail[5]));
         break;
	  case CREATEFAIL:
   	     TextOut(hDC, 210, 170, sNetPlayFail[1], lstrlen(sNetPlayFail[1]));
		 TextOut(hDC, 210, 190, sNetPlayFail[5], lstrlen(sNetPlayFail[5]));
         break;
	  case COMMUNICATIONFAIL:
   	     TextOut(hDC, 210, 170, sNetPlayFail[2], lstrlen(sNetPlayFail[2]));
		 TextOut(hDC, 210, 190, sNetPlayFail[5], lstrlen(sNetPlayFail[5]));
         break;
	  case GETGAMEFAIL:
   	     TextOut(hDC, 210, 170, sNetPlayFail[3], lstrlen(sNetPlayFail[3]));
		 TextOut(hDC, 210, 190, sNetPlayFail[5], lstrlen(sNetPlayFail[5]));
         break;
	  case TRYFAIL:
   	     TextOut(hDC, 200, 150, sNetPlayFail[4], lstrlen(sNetPlayFail[4]));
		 TextOut(hDC, 200, 170, sNetPlayFail[5], lstrlen(sNetPlayFail[5]));
         break;
	  }
	  ///////////////////////// end
	  SelectObject(hDC, hOldFont);
      DeleteObject(hNewFont);
      
	  pdds->ReleaseDC(hDC);
	  return TRUE;
   }
   return FALSE;
}

/***************************************************************************
// Name:        QHRenderNetPlayMenu(void)

// Author:      Liu Qinghua

// Date:        1996, 11.20

// Description: This is the main function to render netplay menu, it
                will add to the function YBRender2DWorld.

// Arguments:   No

// Return:      TRUE : success to render.
				FALSE: failure.
                     
****************************************************************************/

BOOL QHRenderNetPlayMenu(void)
{
	static int count;
	static BOOL bInitmenu = FALSE;

	//if(!bRenderMenu) return TRUE; //96,11.21
	
	if(!bInitmenu)
	{
		InitNetPlayMenu();
		InitSelectMonsterMenu();		
		bInitmenu = TRUE;
	}
	//if(!S_NPMenu.isNetMenu) return TRUE;
	if(S_NPMenu.isNetMenu) 
	{
		if(S_NPMenu.isCreate || S_NPMenu.isConnect)
		{
			if(!QHNetPlayWaitConnect())
			{
				return FALSE;
			}
		}
		else //96,11.01
		{
			if(!bSessionList)
			{
				if(!QHNetPlayFirstDialogue()) 
				{
					return FALSE;
				}
			}
			else
			{
				if(!QHNetPlaySelectSession())
				{
					return FALSE;
				}
			}
		}
		if(S_NPMenu.isPlay)
		{
			S_NPMenu.isNetMenu = FALSE;
			KillTimer(BYMainHwnd, nTimer);  
			BYSetPrePageSwitch(Page, pg_SHOW_MAIN_MENU); 	
			BYSetPostPageSwitch(Page);
			Page = pg_SHOW_MAIN_MENU;
			BYSetPostPageSwitch(Page);
			PostMessage(BYMainHwnd, WM_COMMAND, Page, 0L);
		}
	}

	if(S_NPMenu.KeyState < 0)
	{
		QHNetPlayFailMessage();
	}
	///////////////////////////96,11,21
	if(!bConnectFlag)
	{
		if(bSelectRobot || bSelectMonster)
		{
			if(!QHRenderWaitConnectBefore3D())
				return FALSE;
		}
	}
	////////////////////////////////////
	return TRUE;
}

/////////////////////////////////////////
//The follow is to select a monster

int  QHS2xy[MONSTERNUM][2] = { //height light,
	134, 0, 293, 0, 452, 0, 134, 199, 293, 198, 453, 198
};

/*
int  QHS3xy[MONSTERNUM][2] = {
	45, 354, 45, 356, 45, 358, 45, 356, 45, 358, 45, 356
};
*/
int  QHS3xy[MONSTERNUM][2] = {
	41, 376, 41, 376, 41, 376, 41, 376, 41, 376, 41, 376
};

RECT QHS2rect[MONSTERNUM] = {
	134, 0, 288, 183,
	293, 0, 441, 183,
	452, 0, 600, 183,
	134, 199, 283, 353,
	293, 198, 445, 361,
	453, 198, 602, 359
};
    
RECT QHS3rect[MONSTERNUM] = {
/*	0, 0, 126, 45,
	0, 49, 126, 91,
	0, 103, 128, 144,
	0, 156, 92, 199,
	0, 211, 122, 252,
	0, 265, 128, 308,*/
	0, 0, 559, 45,
	0, 49, 559, 91,
	0, 103, 559, 144,
	0, 156, 559, 199,
	0, 211, 559, 252,
	0, 265, 559, 308,
};

RECT QHMsCharMenuRect[MONSTERNUM] =
{
	121, 0, 290, 190,
	291, 0, 450, 190,
	451, 0, 600, 190,
	121, 191, 290, 380,
	291, 191, 450, 380,
	451, 191, 600, 380

};

short QHS2NewIdx = 0, QHS3NewIdx = 0;
short QHS2TotalItems = MONSTERNUM;
short QHS3TotalItems = MONSTERNUM;
BOOL QHS2ItemFlag[MONSTERNUM];
BOOL QHS3ItemFlag[MONSTERNUM];

//Yuan Bo 's variables, defined in Wrapper.cpp ///////

extern LPDIRECTDRAWSURFACE     lpDDSOverlay[3];  
extern int  S1Idx;
//extern int  S2Idx;
//extern int  S3Idx;
extern int  *S1xy;//, *S2xy, *S3xy, *S4xy;
extern RECT *S1rect;//, *S2rect, *S3rect, *S4rect;
extern BOOL *S1ItemFlag;//, *S2ItemFlag, *S3ItemFlag, *S4ItemFlag;
extern short S1TotalItems, S1OldIdx, S1NewIdx;
//extern short S2TotalItems, S2OldIdx, S2NewIdx;
//extern short S3TotalItems, S3OldIdx, S3NewIdx;
////////////////////////////////////////////////////////////////

void InitSelectMonsterMenu()
{
	int i;
	bSelectRobot = FALSE;
	bSelectMonster = FALSE;
	bMonsterMenu = FALSE;
	bConnectFlag = FALSE;
	QHS2NewIdx = 0;
	QHS3NewIdx = 0;
	
	QHS2ItemFlag[0] = TRUE;
	QHS3ItemFlag[0] = TRUE;
	for(i = 1; i < MONSTERNUM; i++)
	{
		QHS2ItemFlag[i] = FALSE;
		QHS3ItemFlag[i] = FALSE;
	}
}


/***************************************************************************
// Name:        QHSelectCharMenuFromKBD(WORD wparam)

// Author:      Liu Qinghua

// Date:        1996, 11.20

// Description: This is a keyboard control function, to select a
                monster.

// Arguments:   wparam:

// Return:      0:
				1: Press Enter key.
                     
****************************************************************************/

int QHSelectCharMenuFromKBD(WORD wparam)
{
	int j=0;
	int i;
	//int idx;

	switch(wparam) 
	{
	case VK_ESCAPE:
		bMonsterMenu = FALSE;
		j = PG_BACK;
		break;
	case VK_UP:
		if(bSelectMonster) break;
		switch (QHS2NewIdx)
		{
		case 0:
			QHS2NewIdx = 3;
			break;
		case 1:
			QHS2NewIdx = 4;
			break;
		case 2:
			QHS2NewIdx = 5;
			break;
		case 3:
			QHS2NewIdx = 0;
			break;
		case 4:
			QHS2NewIdx = 1;
			break;
		case 5:
			QHS2NewIdx = 2;
			break;
		}
		break;

	case VK_LEFT:
		if(bSelectMonster) break;
		if(QHS2NewIdx <= 0)
		{
			QHS2NewIdx = MONSTERNUM - 1;
		}
		else
		{
			QHS2NewIdx--;
		}
		break;

	case VK_DOWN:
		if(bSelectMonster) break;
		switch (QHS2NewIdx)
		{
		case 0:
			QHS2NewIdx = 3;
			break;
		case 1:
			QHS2NewIdx = 4;
			break;
		case 2:
			QHS2NewIdx = 5;
			break;
		case 3:
			QHS2NewIdx = 0;
			break;
		case 4:
			QHS2NewIdx = 1;
			break;
		case 5:
			QHS2NewIdx = 2;
			break;
		}
		break;

	case VK_RIGHT:
		if(bSelectMonster) break;
		if(QHS2NewIdx >= (MONSTERNUM - 1))
		{
			QHS2NewIdx = 0;
		}
		else
		{
			QHS2NewIdx++;
		}
		break;

	case VK_RETURN:
        //sndPlaySound(WrapSnd1, SND_ASYNC);
		if(bSelectMonster) break;
	    j = 1;
		GameStates.CurrentLevel = QHS2NewIdx + 1;
		//GameStates.CurrentRobot = 1;	//Liou :will be got from recieving message 
		bSelectMonster = TRUE;//FALSE;//Liou qinghua add
		break;
	}

	for(i = 0; i < MONSTERNUM; i++)
	{
		QHS2ItemFlag[i] = FALSE;
		QHS3ItemFlag[i] = FALSE;
	}
	QHS3NewIdx = QHS2NewIdx;
	QHS2ItemFlag[QHS2NewIdx] = TRUE;
	QHS3ItemFlag[QHS2NewIdx] = TRUE;

	return j;
}

/***************************************************************************
// Name:        int QHMsChooseCharMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)

// Author:      Liu Qinghua

// Date:        1996, 11.20

// Description: This is a mouse control function, to select a
                monster.

// Arguments:   

// Return:      0 : 
				1 :Bottom down
                     
****************************************************************************/

int QHMsChooseCharMenu(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	POINT p;
	int i;//, idx;
	int j = 0;

	//if(bSelectMonster) return j;
	p.x = LOWORD(lParam);  // horizontal position of cursor  
	p.y = HIWORD(lParam);  // vertical position of cursor    
	
	for (i=0; i<MONSTERNUM; i++) {
	    if (PtInRect(&(QHMsCharMenuRect[i]), p)) break;
		
	}
	if(i == MONSTERNUM ) return j;
	QHS2NewIdx = i;
	
	/*
	if(p.y < QHMsCharMenuRect[0].bottom)
	{
		if(p.x < QHMsCharMenuRect[0].right)
			QHS2NewIdx = 0;
		else if(p.x < QHMsCharMenuRect[1].right)
			QHS2NewIdx = 1;
		else if(p.x < QHMsCharMenuRect[2].right)
			QHS2NewIdx = 2;
	}
	else 
	{
		if(p.x < QHMsCharMenuRect[3].right)
			QHS2NewIdx = 3;
		else if(p.x < QHMsCharMenuRect[4].right)
			QHS2NewIdx = 4;
		else if(p.x < QHMsCharMenuRect[5].right)
			QHS2NewIdx = 5;
	//	else if(p.x < QHMsCharMenuRect[6].right)
	//		QHS2NewIdx = 6;
	}
	*/
	for(i = 0; i < MONSTERNUM; i++)
	{
		QHS2ItemFlag[i] = FALSE;
		QHS3ItemFlag[i] = FALSE;
	}
	QHS3NewIdx = QHS2NewIdx;
	QHS2ItemFlag[QHS2NewIdx] = TRUE;
	QHS3ItemFlag[QHS2NewIdx] = TRUE;
	
	if (msg==WM_LBUTTONDOWN) 
	{
		GameStates.CurrentLevel = QHS2NewIdx + 1;
		//GameStates.CurrentRobot = 1;	//Liou:will be got from recieving message 
		j = 1;
		bSelectMonster = TRUE;//FALSE;//Liou qinghua add
	}

	return j;	
}

/***************************************************************************
// Name:        QHDrawOverLay(short OverlayNum, BOOL show)

// Author:      Liu Qinghua

// Date:        1996, 11.20

// Description: This is a render overlay function , refrence of YuanBo's
                YBDrawOverlay() function . When render selecting monster
				bitmap, the function will be called.

// Arguments:   OverlayNum:
				show:

// Return:      No.
				
                     
****************************************************************************/

void QHDrawOverLay(short OverlayNum, BOOL show)
{
	int i;
	HRESULT ddrval;
	IDirectDrawSurface *pdds;

	if (!show) return;

	pdds = lpDDSOverlay[(OverlayNum-1)];
	
	if (OverlayNum==1) 
	{
		while (1) 
		{
			ddrval = d3dappi.lpBackBuffer->BltFast(S1xy[S1Idx*2], S1xy[S1Idx*2+1], 
					   pdds, &S1rect[S1Idx], DDBLTFAST_NOCOLORKEY);
			if (ddrval==DD_OK) break;
		} 
	} 
	else if (OverlayNum==2) 
	{
		for (i=0; i < QHS2TotalItems; i++) 
		{
			if (QHS2ItemFlag[i]) 
			{
				while (1) 
				{
					ddrval = d3dappi.lpBackBuffer->BltFast(QHS2xy[i][0], QHS2xy[i][1], 
					   pdds, &QHS2rect[i], DDBLTFAST_NOCOLORKEY);
					if (ddrval==DD_OK) 
						break;
				} 
			}
		}
	} 
	else if (OverlayNum==3) 
	{
		for (i=0; i<QHS3TotalItems; i++) 
		{
			if (QHS3ItemFlag[i]) 
			{
				while (1) 
				{
					ddrval = d3dappi.lpBackBuffer->BltFast(QHS3xy[i][0], QHS3xy[i][1], 
					   pdds, &QHS3rect[i], DDBLTFAST_NOCOLORKEY);
					if (ddrval==DD_OK) 
						break;
				} 
			}
		}
	}
}

/***************************************************************************
// Name:        QHRenderWaitConnectBefore3D()

// Author:      Liu Qinghua

// Date:        1996, 11.20

// Description: Draw waitting strings. If there is not another player
                start or join the session, you will wait for ever.

// Arguments:   OverlayNum:
				show:

// Return:      TRUE: success
				FALSE:failed.				
                     
****************************************************************************/

BOOL QHRenderWaitConnectBefore3D()
{
    HFONT hNewFont, hOldFont;
    IDirectDrawSurface *pdds;
    HDC  hDC;
    static int count_connect = 0;
    static int counter = 0;  //This is only to imitate connection, 

    pdds = d3dappi.lpBackBuffer; //lpDDSOver[0];  
	//pdds = lpDDSText;
	
	if(QHWaitAnotherPlayer())
	{
		InitSelectMonsterMenu();
		BYSetPrePageSwitch(Page, pg_ENTER3D_DELAY); 
		Page = pg_ENTER3D_DELAY;
		PostMessage(BYMainHwnd, WM_COMMAND, Page, 0L);
	}
    
	if (pdds->GetDC(&hDC)==DD_OK) 
    {
		hNewFont = //GetStockObject(ANSI_FIXED_FONT);
		  BYSelectFont(hDC, "System", 10, 18);

		SelectObject(hDC, hNewFont);
		SetBkColor(hDC, NULL);
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(255, 255, 0));

		//if(counter < 50)
		if(!bConnectFlag)
		{
			if(bSelectRobot)
			{
			    TextOut(hDC, 200, 150, sBeforePlay[0], lstrlen(sBeforePlay[0]));
			}
			if(bSelectMonster)
			{
			    TextOut(hDC, 200, 150, sBeforePlay[1], lstrlen(sBeforePlay[1]));
			}

			TextOut(hDC, 250, 200, sConnecting[count_connect], lstrlen(sConnecting[count_connect]));
		}
		count_connect++;
		if(count_connect > 6) count_connect = 0;

		SelectObject(hDC, hOldFont);
		DeleteObject(hNewFont);
      
		pdds->ReleaseDC(hDC);
		return TRUE;
    }
    return FALSE;
}

/***************************************************************************
// Name:        QHWaitAnotherPlayer()

// Author:      Liu Qinghua

// Date:        1996, 11.20

// Description: If the player play as Robot, he will send which Robot message
				to the others, and recieve a level message. Else,
                send level and recieve which Robot message.

// Arguments:   OverlayNum:
				show:

// Return:      TRUE: success
				FALSE:failed.				
                     
****************************************************************************/

BOOL QHWaitAnotherPlayer()
{
  //Waiting for another player setup !
	//It's temporary
	//int    opponent;
	
	isSelectedCharacter = TRUE;

	if (isHost) 
	{
		
		EventSndBuf.MsgId = NEW_MSG;
		EventSndBuf.Event = EVENT_WHICHRobot;
		EventSndBuf.Param = (WORD)GameStates.CurrentRobot;

		if (isOpponentSend)
		{
			bConnectFlag = TRUE;
			beSynchronous = TRUE;
			isOpponentSend = FALSE;
			return TRUE;
		}
		
		/*
		//send level monster selected to Host
		//if(GameStates.CurrentRobot < SabreRobot || GameStates.CurrentRobot >KaberRobot) return FALSE;
		sendDWORD((DWORD)GameStates.CurrentRobot);
		if (receiveDWORD((LPDWORD)(&opponent)))
		{
			//sendDWORD((DWORD)GameStates.CurrentRobot);
			level = opponent;
			bConnectFlag = TRUE;
			beSynchronous = TRUE;
		//	bRenderMenu = FALSE; //96,11.21
			return TRUE;
		} */
		
	}
	else
	{
		
		EventSndBuf.MsgId = NEW_MSG;
		EventSndBuf.Event = EVENT_LEVEL;
		EventSndBuf.Param = (WORD)GameStates.CurrentLevel;

		if (isOpponentSend)
		{
			bConnectFlag = TRUE;
			beSynchronous = TRUE;
			isOpponentSend = FALSE;
			return TRUE;
		}
		
		/*
		if(level < 0 && level > 6) return FALSE;

		sendDWORD((DWORD)level);
		if (receiveDWORD((LPDWORD)(&opponent)))
		{	
			GameStates.CurrentRobot = opponent;
			bConnectFlag = TRUE;
			beSynchronous = TRUE;
		//	bRenderMenu = FALSE; //96,11.21
			return TRUE;
		}
		*/
	}
    return FALSE;
}


/***************************************************************************
// Name:        JSCSwappedSelectionInfo()

// Author:      Jeremiah "Spudde" Childs

// Date:        1997, 1.13

// Description:Similar to QHWaitAnotherPlayer() 
               If the player play as Robot, he will send which Robot message
				   to the others, and recieve a level message. Else,
                send level and recieve which Robot message.

// Arguments:   

// Return:      TRUE: success -- players have communicated level and Robot info
				    FALSE:failed -- still waiting for level and Robot info
                     
****************************************************************************/

BOOL JSCSwappedSelectionInfo()
{
  //Waiting for another player setup !
	{
		ReceiveNetMessages();
		ProcessRcvMsgs();          //processing received messages.
		PrepareMsgToSend();        //prepare all messages to be sent.
		SendNetMessages();
	}

   isSelectedCharacter = TRUE;

	if (isHost) 
	{
		EventSndBuf.MsgId = NEW_MSG;
		EventSndBuf.Event = EVENT_WHICHRobot;
		EventSndBuf.Param = (WORD)GameStates.CurrentRobot;

		if (isOpponentSend)
		{
			bConnectFlag = TRUE;
			beSynchronous = TRUE;
			isOpponentSend = FALSE;
			return TRUE;
		}
	}
	else
	{
		EventSndBuf.MsgId = NEW_MSG;
		EventSndBuf.Event = EVENT_LEVEL;
		EventSndBuf.Param = (WORD)GameStates.CurrentLevel;

		if (isOpponentSend)
		{
			bConnectFlag = TRUE;
			beSynchronous = TRUE;
			isOpponentSend = FALSE;
			return TRUE;
		}
	}
    return FALSE;
}


//Add by Eric 11/12/96
void DisplayDebugMsgInfo()
{
	HDC    hDC;
    IDirectDrawSurface *pdds;
    HFONT hNewFont;
	int  i,j;
	char Text[4][3][30];
	char Other[3][7][30];


    pdds = d3dappi.lpBackBuffer; //lpDDSOver1;  

	if (pdds->GetDC(&hDC)==DD_OK) 
	{

	    SetBkColor(hDC, RGB(0, 0, 0));
		SetBkMode(hDC, TRANSPARENT);

        hNewFont = GetStockObject(ANSI_FIXED_FONT);
        SelectObject(hDC, hNewFont);

		SetTextColor(hDC, RGB(0, 255, 0));
		SetTextAlign(hDC, TA_LEFT);//TA_CENTER);

		sprintf(Text[0][0],"Robot.x = %f;\n",YBRobotPos.x);
		sprintf(Text[0][1],"Robot.y = %f;\n",YBRobotPos.y);
		sprintf(Text[0][2],"Robot.z = %f;\n",YBRobotPos.z);

		sprintf(Text[1][0],"Mnst.x = %f;\n",YBMonstPos.x);
		sprintf(Text[1][1],"Mnst.y = %f;\n",YBMonstPos.y);
		sprintf(Text[1][2],"Mnst.z = %f;\n",YBMonstPos.z);

		sprintf(Text[2][0],"Recv.x = %f;\n",CharSpecData.CurPos.x);
		sprintf(Text[2][1],"Recv.y = %f;\n",CharSpecData.CurPos.y);
		sprintf(Text[2][2],"Recv.z = %f;\n",CharSpecData.CurPos.z);

		sprintf(Text[3][0],"Send.x = %f;\n",CharSpecSndData.CurPos.x);
		sprintf(Text[3][1],"Send.y = %f;\n",CharSpecSndData.CurPos.y);
		sprintf(Text[3][2],"Send.z = %f;\n",CharSpecSndData.CurPos.z);


		for (i = 0; i < 4; i++)
			for (j = 0; j < 3; j++)
	    		TextOut(hDC, 0, 50+40*i+10*j, Text[i][j], lstrlen(Text[i][j]));

		sprintf(Other[0][0],"RobotSped = %f;\n",RobotSpeed);
		sprintf(Other[0][1],"RobotDist = %f;\n",RobotDistance);
		sprintf(Other[0][2],"RobotEngy = %d;\n",RobotEngy);
		sprintf(Other[0][3],"RobotLife = %d;\n",RobotLife);
		sprintf(Other[0][4],"RobotMove = %d;\n",RobotMovementState);
		sprintf(Other[0][5],"RobotAStt = %d;\n",RobotAnimationState);
		sprintf(Other[0][6],"RobotAFrm = %f;\n",RobotAnimationFrame);

		sprintf(Other[1][0],"MnstSped = %f;\n",MonsterSpeed);
		sprintf(Other[1][1],"MnstDist = %f;\n",MonsterDistance);
		sprintf(Other[1][2],"MnstEngy = %d;\n",MnstEngy);
		sprintf(Other[1][3],"MnstLife = %d;\n",MnstLife);
		sprintf(Other[1][4],"MnstMove = %d;\n",MonsterMovementState);
		sprintf(Other[1][5],"MnstAStt = %d;\n",MonsterAnimationState);
		sprintf(Other[1][6],"MnstAFrm = %f;\n",MonsterAnimationFrame);

		sprintf(Other[2][0],"RecvSped = %f;\n",CharSpecData.CurSpeed);
		sprintf(Other[2][1],"RecvDist = %f;\n",CharSpecData.CurDistance);
		sprintf(Other[2][2],"RecvEngy = %d;\n",CharSpecData.CurEnergy);
		sprintf(Other[2][3],"RecvLife = %d;\n",CharSpecData.CurLife);
		sprintf(Other[2][4],"RecvMove = %d;\n",CharSpecData.CurMovState);
		sprintf(Other[2][5],"RecvAStt = %d;\n",CharSpecData.CurAniState);
		sprintf(Other[2][6],"RecvAFrm = %f;\n",CharSpecData.CurAniFrame);

		for (i = 0; i < 3; i++)
			for (j = 0; j < 7; j++)
	    		TextOut(hDC, 160, 80*i+10*j, Other[i][j], lstrlen(Other[i][j]));

        DeleteObject(hNewFont);
		pdds->ReleaseDC(hDC);
	}
}

void DisplayDebugMsgInfo2()
{
	HDC    hDC;
    IDirectDrawSurface *pdds;
    HFONT hNewFont;
	int  i;
	char test[2][40];

    pdds = d3dappi.lpBackBuffer; //lpDDSOver1;  

	if (pdds->GetDC(&hDC)==DD_OK) 
	{

	    SetBkColor(hDC, RGB(0, 0, 0));
		SetBkMode(hDC, TRANSPARENT);

        hNewFont = GetStockObject(ANSI_FIXED_FONT);
        SelectObject(hDC, hNewFont);

		SetTextColor(hDC, RGB(0, 255, 0));
		SetTextAlign(hDC, TA_LEFT);//TA_CENTER);

		if (PlayAsMonster)
		{
			sprintf(test[0],"RobotInput = %d;\n", *InputIntPtr3);
		}
		else
		{
			sprintf(test[0],"MnstInput = %d;\n", *InputIntPtr2);
		}
		sprintf(test[1],"MyInput   = %d;\n", *InputIntPtr);

		for (i = 0; i < 2; i++)
   			TextOut(hDC, 0, 60+10*i, test[i], lstrlen(test[i]));

        DeleteObject(hNewFont);
		pdds->ReleaseDC(hDC);
	}
}


void DisplayNetPlayStatus()
{
	HDC    hDC;
    IDirectDrawSurface *pdds;
    HFONT hNewFont;
//	int  i;
	char test[2][15];

    pdds = d3dappi.lpBackBuffer; //lpDDSOver1;  

	if (pdds->GetDC(&hDC)==DD_OK) 
	{

	    SetBkColor(hDC, RGB(0, 0, 0));
		SetBkMode(hDC, TRANSPARENT);

        hNewFont = GetStockObject(ANSI_FIXED_FONT);
        SelectObject(hDC, hNewFont);

		SetTextColor(hDC, RGB(0, 255, 0));
		SetTextAlign(hDC, TA_LEFT);//TA_CENTER);

		sprintf(test[0],"Robot dead: %02d\n", RobotDeadTimes);
		sprintf(test[1],"Monst dead: %02d\n", MonstDeadTimes);

		TextOut(hDC, 0, 50, test[0], lstrlen(test[0]));

		//TextOut(hDC, (Vmode==320) ? 160:320, 60, test[1], lstrlen(test[1]));
		TextOut(hDC, Vmode/2, 50, test[1], lstrlen(test[1]));

        DeleteObject(hNewFont);
		pdds->ReleaseDC(hDC);
	}
}

//end of Eric

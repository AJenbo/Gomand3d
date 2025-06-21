//**************************************************************************
// netinit2.c
//
// (c) Copyright Inventec(Tian Jin) 1996. All rights reserved.
//
// Author:      Liu Qinghua
//
// Date:        1996, 11. 20
//
// Description:  Control dialogue box of net play for Goman95 DirectX 3.0 version.
//               Create NetPlay .
// Notes:        Sanfo had writed the file in DirectX 2.0 version, 
//               I re_write the file, use windows GDI draw dialogue box,
//               
// Update:
//
//**************************************************************************

#ifdef MINIWIN
#include "miniwin/windows.h"
#else
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#endif
#include <math.h>

#include "d3dappi.h"
#include "rmdemo.h"
#include "rmfull.h"
#include "byglobal.h"
#include "wrapper.h"

#include "ybmid.h"
#include "ybsnd.h"
#include "keycom.h"

#include "netplay.h"
#include "netmenu.h"
#include "netinit2.h"

#include "global.h"

//BOOL            beSynchronous = FALSE;
BOOL            answerHereIAm = FALSE;      //for host answer HereIAm message.
//BOOL            netPlay       = FALSE;      //multi player on net.
BOOL            isHost        = FALSE;
BOOL  bErrMsg = FALSE;
char  ErrMsg[127]="";

LPDIRECTPLAY2A  lpDPId   = NULL;     // DirectPlay Object
HANDLE          dphEvent = NULL;
LPGUID          lpGameGuid[MAX_PROTOCOLS];           // pointer of NETPLAY_DRIVER_GUID
BYTE            CommBuff[256];       //message buffer

int NetMenuState   = 0;
				//1   // GameMode
				//2   //ChooseProtocol
				//3	  //Start or Join Game
				//4   //List Session
BOOL bSessionList = FALSE;
short            nProtocolId = 0;
short            nSessionId = 0;
short            WhichSession = -1;

S_NetPlayMenu    S_NPMenu;
S_SESSIONDESC2*  S_lpDPGameDesc[MAX_SESSIONS];


////////////////Yuan Bo define
extern HWND BYMainHwnd;
extern short  MidCmd;
extern short  MidSts;
/////////////////////////////

/***************************************************************************
// Name:        ReturnMode()

// Author:      Liu Qinghua

// Date:        1996, 11.20

// Description: Inintialize the variables in struct menu when return 
                selecting GameMode because of failure creating NetPlay.

// Arguments:   No

// Return:      No
				
                     
****************************************************************************/

void ReturnMode()
{
	//S_NPMenu.isSigle   = FALSE;
	S_NPMenu.isMulti   = FALSE;
	S_NPMenu.isModem   = FALSE;
	S_NPMenu.isIPX     = FALSE;
	S_NPMenu.isInter   = FALSE;
	S_NPMenu.isSerial  = FALSE;
	S_NPMenu.isCreate  = FALSE;
	S_NPMenu.isConnect = FALSE;
	S_NPMenu.isNetMenu = TRUE;
	S_NPMenu.isRobot    = FALSE;
	S_NPMenu.isMonster = FALSE;
	S_NPMenu.isPlay    = FALSE;
//	S_NPMenu.NetSuccess = 0;   
	S_NPMenu.ModeIdx = 0;
	S_NPMenu.NetIdx  = 0;
	S_NPMenu.ConIdx  = 0;
	beSynchronous = FALSE;
    answerHereIAm = FALSE;     
    GameStates.IsNetplay       = FALSE;     
    isHost        = FALSE;
} 

/***************************************************************************
// Name:        InitMySessions()

// Author:      Liu Qinghua

// Date:        1996, 11.20

// Description: Inintialize the variables in struct S_SESSIONDESC2 ,
                the struct is used to load SessionDesc data.

// Arguments:   No

// Return:      No
				
                     
****************************************************************************/

void InitMySessions()
{
	int index;
	for (index = 0; index < MAX_SESSIONS; index ++)
    {
		S_lpDPGameDesc[index] = (S_SESSIONDESC2 *)LocalAlloc(LPTR,sizeof(S_SESSIONDESC2));
		memset(S_lpDPGameDesc[index],0x00,sizeof(S_SESSIONDESC2));
    }
}

/***************************************************************************
// Name:        int QHSelectModeFromKBD(WORD wParam)

// Author:      Liu Qinghua

// Date:        1996, 11.20

// Description: Select GameMode, if selec Sigle, go into sigle game,
                if select Multi, netplay game. Enmurate protocol function 
//				will be called.

// Arguments:   wParam

// Return:      1:Enter the next select menu.
//				-99: exit the game.
				
****************************************************************************/

int QHSelectModeFromKBD(WPARAM wParam)
{
	int j = 1;    

    switch(wParam) 
	{
	
		case VK_ESCAPE:
			 j = PG_BACK;
			 break;

		case VK_DOWN:
		case VK_RIGHT:
			if(S_NPMenu.ModeIdx == 0) 
				S_NPMenu.ModeIdx = 1;
			else 
				S_NPMenu.ModeIdx = 0;
			break;

		case VK_UP:
		case VK_LEFT:
			if(S_NPMenu.ModeIdx == 0) 
				S_NPMenu.ModeIdx = 1;
			else 
				S_NPMenu.ModeIdx = 0;
			break;

		case VK_RETURN:
			S_NPMenu.KeyState = j;
			NetMenuState = 1;
			if(S_NPMenu.ModeIdx == 0) 
			{
				//S_NPMenu.isSigle = TRUE;
				//GameStates.IsNetplay = FALSE; //Liou qinghua 96,11.04
				S_NPMenu.isPlay = TRUE;
			}
			else 
			{
				S_NPMenu.isMulti = TRUE;
				if(!GetProvider())
				{
					//j = PROVIDERFAIL;
					break;
				}
			}
			break;
	}
	return j;
}

/***************************************************************************
// Name:        QHSelectProtocolFromKBD(WORD wParam)

// Author:      Liu Qinghua

// Date:        1996, 11.20

// Description: Select protocol, 
                
//				

// Arguments:   wParam

// Return:      1:Enter the next select menu.
//				-99: exit the game.
				
****************************************************************************/

int QHSelectProtocolFromKBD(WPARAM wParam)
{
	int j = 1;    

    switch(wParam) 
	{
	
		case VK_ESCAPE:
			 j = PG_BACK;
			 break;

		case VK_DOWN:
		case VK_RIGHT:
			if(S_NPMenu.NetIdx < 3) 
				S_NPMenu.NetIdx++;
			else 
				S_NPMenu.NetIdx = 0;
			break;

		case VK_UP:
		case VK_LEFT:
			if(S_NPMenu.NetIdx > 0) 
				S_NPMenu.NetIdx--;
			else 
				S_NPMenu.NetIdx = 3;
			break;

		case VK_RETURN:
			S_NPMenu.KeyState = j;
			NetMenuState = 2;
			if(S_NPMenu.NetIdx == 0) 
			{
				S_NPMenu.isModem = TRUE;
			}
			else if(S_NPMenu.NetIdx == 1) 
			{
				S_NPMenu.isIPX = TRUE;
			}
			else if(S_NPMenu.NetIdx == 2) 
			{
				S_NPMenu.isInter = TRUE;
			}
			else
			{
				S_NPMenu.isSerial = TRUE;
			}
			break;
	}

	return j;
}

/***************************************************************************
// Name:        QHSelectConnectFromKBD(WORD wParam)

// Author:      Liu Qinghua

// Date:        1996, 11.20

// Description: Select Start or Join the game. 

// Arguments:   wParam

// Return:      1:Enter the next select menu.
//				-99: exit the game.
				
****************************************************************************/

int QHSelectConnectFromKBD(WPARAM wParam)
{
	int j = 1;    

    switch(wParam) 
	{
	
		case VK_ESCAPE:
			 j = PG_BACK;
			 break;

		case VK_DOWN:
		case VK_RIGHT:
			if(S_NPMenu.ConIdx == 0) 
				S_NPMenu.ConIdx = 1;
			else 
				S_NPMenu.ConIdx = 0;
			break;

		case VK_UP:
		case VK_LEFT:
			if(S_NPMenu.ConIdx == 0) 
				S_NPMenu.ConIdx = 1;
			else 
				S_NPMenu.ConIdx = 0;
			break;

		case VK_RETURN:
			S_NPMenu.KeyState = j;
			NetMenuState = 3;
			
			GameStates.IsNetplay = TRUE;
			if(S_NPMenu.ConIdx == 0) 
			{
				isHost = TRUE;
				PlayAsMonster = FALSE;
				if(!CreateSession() || !CreatePlayer(MASTERNAME))
				{
					break;
				}

				S_NPMenu.isCreate = TRUE;
				S_NPMenu.isRobot = TRUE;
				InitMsgBuf();
			}
			else 
			{
				if(!HowManySessions())
					break;
				bSessionList = TRUE;
			}
	}

	return j;
}


/***************************************************************************
// Name:        QHSelectSessionFromKBD(WORD wParam)

// Author:      Liu Qinghua

// Date:        1996, 11.20

// Description: Select a session in the session list.

// Arguments:   wParam

// Return:      1:Enter the next select menu.
//				-99: exit the game.
				
****************************************************************************/

int QHSelectSessionFromKBD(WPARAM wParam)
{
	int j = 1;    

    switch(wParam) 
	{
	
		case VK_ESCAPE:
			 j = PG_BACK;
			 break;

		case VK_DOWN:
		case VK_RIGHT:
         j = 0;
			if(WhichSession < nSessionId - 1) 
				WhichSession ++;
			else 
				WhichSession = 0;
			break;

		case VK_UP:
		case VK_LEFT:
         j = 0;
			if(WhichSession > 0) 
				WhichSession --;
			else 
				WhichSession = nSessionId - 1;
			break;

		case VK_RETURN:
			S_NPMenu.KeyState = j;
			NetMenuState = 4;
         /*
			isHost = FALSE;
			PlayAsMonster = TRUE;
			if(!GetGame(WhichSession) || !CreatePlayer(SLAVENAME))
			{
				break;
			}
			
			S_NPMenu.isConnect = TRUE;
			S_NPMenu.isMonster = TRUE;
			bSessionList = FALSE;
			
			InitMsgBuf();
         */
			break;
	}

	return j;
}


/***************************************************************************
// Name:        QHNetPlaySelect(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)

// Author:      Liu Qinghua

// Date:        1996, 11.18

// Description: Main control function to press a key. the function will

//              be called in  Wrapper.cpp.

// Arguments:   wParam

// Return:      TRUE: success.
//				FALSE:failure.
				
****************************************************************************/

//96,11,18
BOOL QHNetPlaySelect(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int j = 1;

	if ( S_NPMenu.KeyState != PROTOCOLFAIL && S_NPMenu.KeyState != CREATEFAIL)
	{
		if (!S_NPMenu.isCreate && !S_NPMenu.isConnect)
		{
			switch(NetMenuState)
			{
			case 0:
				j = QHSelectModeFromKBD(wParam);
				break;

			case 1:
				j = QHSelectProtocolFromKBD(wParam);
				break;

			case 2:
				j = QHSelectConnectFromKBD(wParam);
				break;
			
			case 3:
				if(S_NPMenu.isCreate) break;
				j = QHSelectSessionFromKBD(wParam);
				break;
			
			}
		}
	}
	if (j == PG_BACK)
	{
		MidCmd = MID_STOP;
		S_NPMenu.KeyState = PG_BACK;
		BYMidiCenter();
		KillTimer(win, nTimer);  
		PostMessage(win, WM_DESTROY, 0, 0L);
	}
	/*
	if(S_NPMenu.isSigle)
	{
	   S_NPMenu.isNetMenu = FALSE;
	   KillTimer(win, nTimer);  
	   BYSetPrePageSwitch(Page, pg_SHOW_MAIN_MENU); 	
	   Page = pg_SHOW_MAIN_MENU;
	   PostMessage(win, WM_COMMAND, Page, 0L);
	} 
	*/
	return TRUE;
}


/***************************************************************************
// Name:        HRESULT DPlayCreate(LPGUID lpGuid)

// Author:      Liu Qinghua

// Date:        1996, 11.18

// Description: The function is copied from ccom.c in SDK.

//              used to create a LPDIRECTPLAY2(A) object.

// Arguments:   wParam

// Return:      DP_OK: success.
//				!DP_OK:failure.
				
****************************************************************************/

HRESULT DPlayCreate(LPGUID lpGuid)
{
    HRESULT hr=E_FAIL;
    LPDIRECTPLAY lpDP=NULL;

    // create a DirectPlay1 interface
    if ((hr = DirectPlayCreate(lpGuid, &lpDP, NULL)) == DP_OK)
    {
        if (lpDP)
        {
            // query for a DirectPlay2(A) interface
#ifdef UNICODE
            hr = IDirectPlay_QueryInterface(lpDP,&IID_IDirectPlay2,(LPVOID *)&lpDPId);
#else
            hr = IDirectPlay_QueryInterface(lpDP,&IID_IDirectPlay2A,(LPVOID *)&lpDPId);
#endif
            // no longer need the DirectPlay1 interface
            IDirectPlay_Release(lpDP);
        }
    }

    return hr;
}

/***************************************************************************
// Name:        EnumSP(LPGUID lpGuid,LPSTR lpDesc,DWORD dwMajorVersion,DWORD dwMinorVersion,LPVOID lpv)

// Author:      Liu Qinghua

// Date:        1996, 11.18

// Description: Enumerate all communication protocol. This is a callback

//				function.              

// Arguments:   

// Return:      TRUE: continue enumeration.
//				FALSE:stop enumeration.
				
****************************************************************************/

static BOOL CALLBACK EnumSP(LPGUID lpGuid,LPSTR lpDesc,DWORD dwMajorVersion,DWORD dwMinorVersion,LPVOID lpv)
{
   if (nProtocolId >= MAX_PLAYER)
   {
          return FALSE;
   }
   if (strstr(_strlwr(lpDesc),"modem") != NULL)
   {
          lpGameGuid[0] = lpGuid;
			 valid_cntion[total_cntion++] = 1;
//		  isModem = TRUE;
   }
   else if (strstr(_strlwr(lpDesc),"ipx") != NULL)
   {
          lpGameGuid[1] = lpGuid;
			 valid_cntion[total_cntion++] = 2;
//		  isIPX = TRUE;
   }
   else if (strstr(_strlwr(lpDesc),"internet") != NULL)
   {
          lpGameGuid[2] = lpGuid;
			 valid_cntion[total_cntion++] = 3;
//		  isInter = TRUE;
   }
   else if (strstr(_strlwr(lpDesc),"serial") != NULL)
   {
          lpGameGuid[3] = lpGuid;
			 valid_cntion[total_cntion++] = 4;
//		  isInter = TRUE;
   }
   return TRUE;
}

//DWORD dwQHSession[MAX_SESSIONS];

/***************************************************************************
// Name:        EnumSession(...)

// Author:      Liu Qinghua

// Date:        1996, 11.18

// Description: Enumerate all sessions in net. If sessions exceed 10,

//				will ignore. This is callback function             

// Arguments:   

// Return:      TRUE: continue enumeration.
//				FALSE:stop enumeration.
				
****************************************************************************/

static BOOL WINAPI EnumSession(LPCDPSESSIONDESC2 lpDPGameDesc,
							   LPDWORD lpdwTimeOut,DWORD dwFlags,
							   LPVOID lpContext)
{
   short sLength;
   if (nSessionId >= MAX_SESSIONS)
   {
       return FALSE;
   }

   if (dwFlags & DPESC_TIMEDOUT) 
   {
           return FALSE;
   }
   
   if (lpDPGameDesc)
   {
	   S_lpDPGameDesc[nSessionId]->dwSize = lpDPGameDesc->dwSize;
	   memcpy(&S_lpDPGameDesc[nSessionId]->Application,&lpDPGameDesc->guidApplication,sizeof(GUID));
	   memcpy(&S_lpDPGameDesc[nSessionId]->Instance,&lpDPGameDesc->guidInstance,sizeof(GUID));
	   sLength = strlen(lpDPGameDesc->lpszSessionNameA);
	   if (sLength < NAME_SIZE)
	   {
		   memcpy(S_lpDPGameDesc[nSessionId]->SessionName,lpDPGameDesc->lpszSessionNameA,sLength);
		   //strcpy(SessionName[nSessionId], lpDPGameDesc->lpszSessionNameA);
		   nSessionId ++;
         WhichSession = 0;    // Initialize to first session if there are any available.
		   return TRUE;
	   }
   }
   return FALSE;
}


int SelectGameMode(HWND Ignored)
{
   return 0;
}

short GetProtocol(short m_nProtocol) 
{
	return m_nProtocol;
}

BOOL GetProvider()
{
   HRESULT lt;
   lt = DirectPlayEnumerate(EnumSP,(LPVOID)BYMainHwnd);  
  
   if (lt != DP_OK)
   {
		//MessageBox(BYMainHwnd,"Can't Enumerate protocols!","Error",MB_OK);
		S_NPMenu.KeyState = PROTOCOLFAIL;
		return FALSE;
   }
   return TRUE;
}


/***************************************************************************
// Name:        CreateSession()

// Author:      Liu Qinghua

// Date:        1996, 11.18

// Description: Create a session. If a player select "Create" button, 

//				he will start a session, and play as Robot.

// Arguments:   No.

// Return:      TRUE: success.
//				FALSE:failure.
				
****************************************************************************/

BOOL CreateSession()
{
	DPSESSIONDESC2 dpDesc;
	HRESULT hr;
   static char username[256];
   DWORD usernamesize = 256;
	
	if (lpDPId == NULL)
	{
		nProtocolId = S_NPMenu.NetIdx;
		//hr = DirectPlayCreate(lpGameGuid[nProtocolId],&lpDPId,NULL);
		hr = DPlayCreate(lpGameGuid[nProtocolId]);
		if (hr != DP_OK)
		{
			//MessageBox(BYMainHwnd,"Can't Create Player!","Error",MB_OK);
			strcpy(ErrMsg, "Can't Create Player!");
			S_NPMenu.KeyState = CREATEFAIL;
			bErrMsg=TRUE;
			return FALSE;
		}
	}
	if (lpDPId == NULL)
	{
       //MessageBox(BYMainHwnd, "Can not create direct player!","Error",MB_OK);
       strcpy(ErrMsg,  "Can not create direct player!");
		 S_NPMenu.KeyState = CREATEFAIL;
		 bErrMsg=TRUE;
	    return FALSE;
	}

	memset(&dpDesc, 0x00, sizeof(DPSESSIONDESC2));
	dpDesc.dwSize = sizeof(DPSESSIONDESC2);
	dpDesc.dwMaxPlayers = MAX_PLAYER;
	dpDesc.dwFlags = DPSESSION_MIGRATEHOST | DPSESSION_KEEPALIVE;
	dpDesc.guidApplication = GOMAN95_GUID;
	//dpDesc.guidApplication = GUID_NULL;
   GetUserName(username, &usernamesize);
   strcat(username, "'s Goman");
	dpDesc.lpszSessionNameA = username;

	if ((hr = lpDPId->lpVtbl->Open(lpDPId, &dpDesc, DPOPEN_CREATE)) != DP_OK)
	{	/*
          switch(hr)
		  {
		  case DPERR_ACTIVEPLAYERS:
			  break;
		  case DPERR_GENERIC:
			  break;
		  case DPERR_INVALIDOBJECT:
			  break;
		  case DPERR_INVALIDPARAMS:
			  break;
	    }*/

		lpDPId->lpVtbl->Release(lpDPId);
		lpDPId = NULL;
		S_NPMenu.KeyState = COMMUNICATIONFAIL;
		ReturnMode();
		return(FALSE);
	}

	return TRUE;
}


/***************************************************************************
// Name:        HowManySessions()

// Author:      Liu Qinghua

// Date:        1996, 11.18

// Description: Get all sessions in the net.

//				

// Arguments:   No.

// Return:      TRUE: success.
//				FALSE:failure.
				
****************************************************************************/

BOOL HowManySessions()
{
	DPSESSIONDESC2 dpDesc;
	HRESULT hr;

	InitMySessions();
	if (lpDPId == NULL)
	{
		nProtocolId = S_NPMenu.NetIdx;
		hr = DPlayCreate(lpGameGuid[nProtocolId]);
		if (hr != DP_OK)
		{
			MessageBox(BYMainHwnd,"Can't Create Player!","Error",MB_OK);
			S_NPMenu.KeyState = CREATEFAIL;
			return FALSE;
		}
	}
	if (lpDPId == NULL)
	{
		MessageBox(BYMainHwnd, "Can not create direct player!","Error",MB_OK);
		S_NPMenu.KeyState = CREATEFAIL;
		return FALSE;
	}
    
	memset(&dpDesc, 0x00, sizeof(DPSESSIONDESC2));
	dpDesc.dwSize = sizeof(dpDesc);
	dpDesc.guidApplication = GOMAN95_GUID;
	//dpDesc.guidApplication = GUID_NULL;

		// enum sessions with 5 second timeout
	lpDPId->lpVtbl->EnumSessions(lpDPId, &dpDesc, (DWORD)0, EnumSession, (LPVOID) BYMainHwnd, DPENUMSESSIONS_AVAILABLE);
	return TRUE;
}

/***************************************************************************
// Name:        GetGame(short index)

// Author:      Liu Qinghua

// Date:        1996, 11.18

// Description: Join a session. If a player select "Connect" botton,
//				he may select a session from the session list. he will
//				play as Monster.

// Arguments:   index: the index number in session list(0--9).

// Return:      TRUE: success.
//				FALSE:failure.
				
****************************************************************************/

BOOL GetGame(short index)
{
    DPSESSIONDESC2 dpDesc;
    HRESULT hr;

	memset(&dpDesc, 0x00, sizeof(DPSESSIONDESC2));
    dpDesc.dwSize = sizeof(dpDesc);

    if (S_lpDPGameDesc[index]->dwSize != 0)
	{
        if (strlen(S_lpDPGameDesc[index]->SessionName) != 0)
        {
            memcpy(&dpDesc.guidInstance,&S_lpDPGameDesc[index]->Instance,sizeof(GUID));

			if ((hr = lpDPId->lpVtbl->Open(lpDPId, &dpDesc, DPOPEN_JOIN)) != DP_OK)
			{
				lpDPId->lpVtbl->Release(lpDPId);
				lpDPId = NULL;
				S_NPMenu.KeyState = GETGAMEFAIL;
				//ReturnCreateOrConnect();
				ReturnMode();
				return(FALSE);
			}
			return TRUE;
		}
	}
	return FALSE;
}

/***************************************************************************
// Name:        CreatePlayer(LPSTR lpPlayerName)

// Author:      Liu Qinghua

// Date:        1996, 11.18

// Description: Create a player.

// Arguments:   lpPlayerName: the name the player name. Now I set all
//				players have a same name "ITC_RD7 NetPlay". In the future,
//				I will write some code, each player can input his name.
// Return:      TRUE: success.
//				FALSE:failure.
				
****************************************************************************/

BOOL CreatePlayer(LPSTR lpPlayerName)
{
	DPNAME dpName;
	HRESULT lt;
	memset(&dpName,0x00,sizeof(DPNAME));
	dpName.dwSize = sizeof(DPNAME);
	dpName.lpszShortNameA = lpPlayerName;
	dpName.lpszLongNameA = NULL;
	if (lpDPId)
	{
		lt = lpDPId->lpVtbl->CreatePlayer(lpDPId, &MyId, &dpName,
			  dphEvent, NULL, 0, 0);
        if (lt != DP_OK)
        {/*
			switch(lt)
			{
			case DPERR_CANTADDPLAYER:
				break;
			case DPERR_CANTCREATEPLAYER:
				break;
			case DPERR_GENERIC:
				break;
			case DPERR_INVALIDOBJECT:
				break;
			case DPERR_INVALIDPARAMS:
				break;
			case DPERR_NOCONNECTION:
				break;
			}*/
		
			lpDPId->lpVtbl->Close(lpDPId);
			lpDPId->lpVtbl->Release(lpDPId);
			lpDPId = NULL;
			S_NPMenu.KeyState = TRYFAIL;
			ReturnMode();
			return(FALSE);
        }
        return TRUE;
   }
   return FALSE;
}

/***************************************************************************
// Name:        DestroyPlayer(DPID pidID)

// Author:      Liu Qinghua

// Date:        1996, 11.18

// Description: Destroy a player.

// Arguments: pidID: A player's ID. 

// Return:      No.
//				
				
****************************************************************************/

void DestroyPlayer(DPID pidID)
{
    if (lpDPId)
       lpDPId->lpVtbl->DestroyPlayer( lpDPId, pidID );
}

/***************************************************************************
// Name:        Close()

// Author:      Liu Qinghua

// Date:        1996, 11.18

// Description: Close NetPlay.

// Arguments:   No.

// Return:      No.
//				
				
****************************************************************************/

void Close()
{
    lpDPId->lpVtbl->Close(lpDPId);
}



static int numberofnetplayers;

BOOL WINAPI CountPlayersCallbackFunction(DPID dpId, DWORD dwPlayerType, LPCDPNAME lpName,
    DWORD dwFlags, LPVOID lpContext)
{
   numberofnetplayers++;  
   return TRUE;
}


BOOL JSCHasPlayerJoined()
{
   numberofnetplayers=0;
   if (!lpDPId)
      return FALSE;
   lpDPId->lpVtbl->EnumPlayers(lpDPId, lpGameGuid[nProtocolId], CountPlayersCallbackFunction,
      NULL, 0);
   if (numberofnetplayers==2)
      return TRUE;
   else
      return FALSE;
}



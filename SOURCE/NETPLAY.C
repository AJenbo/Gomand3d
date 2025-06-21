//***********************************************************************//
// File Name: NETPLAY.C
// Author   : Lu Fengshun
// Date     : 1996.8.16
// Function : Netplay functions.
// Notes:       
// Update:
//
//***********************************************************************//

#include <stdio.h>

#include "netplay.h"
#include "boink.h"
#include "keycom.h"
#include "byglobal.h"
#include "monanim.h"
#include "building.h"
#include "global.h"


#define  __INTEL_CPU__
#define  LATENCY_TIME   200

int      RobotDeadTimes = 0;
int      MonstDeadTimes = 0;
int      DisplayDebugMsgFlag = 0;
BOOL     beSynchronous = FALSE;
BOOL     isIn3DGame = FALSE;
BOOL     isOpponentSend = FALSE;
BOOL     isSelectedCharacter = FALSE;
BOOL     isOpponentKeyUp = FALSE;
BOOL     CharSpecMsgCanBeTransmitted = FALSE;

extern   HWND  BYMainHwnd;   
//extern   BOOL  In3DMovie;
//extern   int   level;
extern   short Page;
extern   short Vmode;
extern   int   NextLevel;
extern   int   *InputIntPtr;          // Input stream from player
extern   int   *InputIntPtr2;         // Input stream from monster AE
extern   int   *InputIntPtr3;         // Input stream from Robot AE
extern   BOOL  KbFlag;
extern   BOOL  bBYRenderingIsOK;

extern   LPDIRECT3DRMFRAME  Robotframe,      monstframe;
extern   D3DVECTOR RobotVelocity,   MonsterVelocity;
extern   D3DVALUE  RobotSpeed,      MonsterSpeed,
                   RobotDistance,   MonsterDistance;
extern   int       RobotEngy,       MnstEngy,
                   RobotLife,       MnstLife;

extern   int       RobotMovementState,  MonsterMovementState,
                   RobotAnimationState, MonsterAnimationState;
extern   D3DVALUE  RobotAnimationFrame, MonsterAnimationFrame;


extern building* GetBuilding(int x, int z);
extern BOOL BYKbFrom3DTo2D(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);
extern BOOL CleanupGame3DPart();
extern int  PowerUpHere(RLFrame Robotishere);
extern void YBSetSubTitle1(int mode, char *str1, COLORREF color);
//end by Eric

//extern   LPDIRECTDRAWSURFACE   lpDDSBack;      // DirectDraw back surface

BOOL bAskQuit = FALSE;


 
//-------------------------------------------------------------------------
//global variables.
//-------------------------------------------------------------------------

//each kind of message, need two buffers: send buffer and receive buffer.

//for Input message
INPUTMSG      InputSndBuf;

INPUTPOOL     InputPool[MAX_POOL];
INPUTPOOL     * InputFirst;
INPUTPOOL     * InputLast;

//for Event message
KEYEVENTMSG   EventSndBuf;
KEYEVENTMSG   EventRcvBuf;
 
//for CharSpec message
CHARSPECMSG   CharSpecSndBuf;
CHARSPECMSG   CharSpecRcvBuf;

CHARSPECDATA  CharSpecData;
CHARSPECDATA  CharSpecSndData;
D3DVECTOR     YBRobotPos;
D3DVECTOR     YBMonstPos;

//for Weapon message
WEAPONSPECMSG WeaponSpecSndBuf;
WEAPONSPECMSG WeaponSpecRcvBuf;

//for Text message
TEXTMSG       TextSndBuf;
TEXTMSG       TextRcvBuf;



//Packet Data Buffer:
BYTE   CommBuf[MAX_COMBUF_LEN];

WORD   MaxBytes = 40;            //just for testing.

BOOL   HasKey = FALSE;

//Message prams:
DPID  MyId = 0;                  //my player ID.  

DPID  ToId = 0;                  //send to name server.

DPID  FromId;                    //for more than 2 palyers use.

WORD  TimeStamp;

BYTE  MsgSeqNo = 0;



//buffers for simulation:
//#define _SIMULATE_         1

 
 
SIMUPARAM  SimuArray[MAX_SIMU_BUFFER];

  
WORD   SimuMode = 0;

UINT   TimerId = 0;

WORD   WrongOrderNo = 0;

//#endif


//type converting functions 

void VectorFtoW(WORDVECTOR * wv, D3DVECTOR * fv)
{
    wv->x = FTOW(fv->x);
    wv->y = FTOW(fv->y);
    wv->z = FTOW(fv->z);
}

void VectorWtoF(D3DVECTOR * fv, WORDVECTOR * wv)
{
    fv->x = WTOF(wv->x);
    fv->y = WTOF(wv->y);
    fv->z = WTOF(wv->z);
}


void VectorFtoB(BYTEVECTOR * bv, D3DVECTOR * fv)
{
    bv->x = FTOB(fv->x);
    bv->y = FTOB(fv->y);
    bv->z = FTOB(fv->z);
}

void VectorBtoF(D3DVECTOR * fv, BYTEVECTOR * bv)
{
    fv->x = BTOF(bv->x);
    fv->y = BTOF(bv->y);
    fv->z = BTOF(bv->z);
}




//initializing buffers
void InitMsgBuf()
{
   int i;
   
   InputSndBuf.MsgId = OLD_MSG;
   
   
   //init input pool as a loop link buffer.
   InputFirst = &InputPool[0];
   InputLast = &InputPool[0];

   for (i = 0; i < MAX_POOL; i ++)
   {
      InputPool[i].InputRcvBuf.MsgId = OLD_MSG;
      
      if (i < (MAX_POOL - 1))
      {
         InputPool[i].Next = &InputPool[i + 1];
      }
      else                        //last one, ptr to first.
      {
         InputPool[i].Next = &InputPool[0];
      }
   }

   /*
   if (isHost)
   {
       EventSndBuf.MsgId = OLD_MSG;
   }
   else
   {
       EventSndBuf.MsgId = NEW_MSG;
       EventSndBuf.Event = EVENT_HEREIAM;
	  //EventSndBuf.Param = level;
   }
   */ 

   EventSndBuf.MsgId = OLD_MSG;
   EventRcvBuf.MsgId = OLD_MSG;
 
   CharSpecSndBuf.MsgId = OLD_MSG;
   CharSpecRcvBuf.MsgId = OLD_MSG;

   WeaponSpecSndBuf.MsgId = OLD_MSG;
   WeaponSpecRcvBuf.MsgId = OLD_MSG;

   TextSndBuf.MsgId = OLD_MSG;
   TextRcvBuf.MsgId = OLD_MSG;

   for (i = 0; i < MAX_SIMU_BUFFER; i++)
   {
       ResetSimuArray(i);
   } 
   return;
}



//receive all messages in DPLAY Queue
void ReceiveNetMessages()
{
   HRESULT status;
   DWORD   wbufLen;
   DPID    fromId; 
   DPID    rcvId;
   LPDWORD   lpSysMsg;
   //static    UINT      NoMessageTimerId = 0;

   if (lpDPId == NULL)
   {
      return;
   }

   while (1)
   {
      wbufLen = MAX_COMBUF_LEN;
      status = lpDPId->lpVtbl->Receive(lpDPId, &fromId, &rcvId, 
                                       DPRECEIVE_ALL, CommBuf, &wbufLen);

	/*
	//It's will be exit when no messages received 60 seconds
	if (status == DPERR_NOMESSAGES)
	{
	    if (NoMessageTimerId == 0)
		{
		    NoMessageTimerId = 
		   	    SetTimer(NULL, 0, 60000, (TIMERPROC)&Timer3Func);
		}
	}
	else
	{
	    if (NoMessageTimerId != 0)
		{
			KillTimer(NULL, NoMessageTimerId);
		}
	}
	*/

      switch (status)
      {
         case DP_OK:
			 //it's system message
              if (0 == fromId)
              {	 
				  
				  lpSysMsg = (LPDWORD)CommBuf;
				  switch (*lpSysMsg)
				  {
				  case DPSYS_DELETEPLAYER:
					  // the other player has been exit !
					  // exit to win95.
					  PostMessage(BYMainHwnd, WM_DESTROY, 0, 0L);
					  break;
				  case DPSYS_ADDPLAYER:
					  // add an other player !
					  break;
				  default:
					  break;
				  }
				  
              }
              else
              {
                 //put message into the proper buffer;
                 EvaluateMessage(fromId, wbufLen);
              }
              
              break;
      
         default:

              return;

      }
   }
}


//put received messages into ReceiveBuffer
void EvaluateMessage(DPID fromId, DWORD len)
{
   int     i;
   BYTE  * lpcommBuf;

   LPMSGHEADER      lpmsgHdr;
   LPKEYEVENTMSG    lpkeyEventMsg;
   LPINPUTMSG       lpinputMsg;
   LPCHARSPECMSG    lpcharSpecMsg;
   //LPWEAPONSPECMSG  lpweaponSpecMsg;
   LPTEXTMSG        lptextMsg;
   BYTE             MsgIdAdd;

   #ifdef _FILEOUTPUTNETMSG_
   BYTE msgOut[256];
   BYTE lowByte;
   BYTE hiByte;
   #endif
   
   lpmsgHdr = (LPMSGHEADER)CommBuf;          //get message header ptr.

   if (lpmsgHdr->MsgNum <= 0 || lpmsgHdr->MsgNum > MAX_MSG_TYPES)
   {
      return;             //do nothing, this is a invalid packet.
   }

    
   //note the MsgSeqNo is wraparound, eg. 254, 255, 0, 1, 2...
   if (lpmsgHdr->MsgSeqNo != (BYTE)(MsgSeqNo + 1))
   {
      //MsgMissing = TRUE;
   
      //two possible kind of message: valid or invaild(missed).
      if (IsPrevMsg((short)lpmsgHdr->MsgSeqNo, (short)MsgSeqNo))
      {
         return;             //wrong order or duplicated message, ignore it.
      }
       
   }
   
   
   //FromId = fromId;                          //for > 2 player use.

   TimeStamp = lpmsgHdr->TimeStamp;          //save packet timestamp.

   MsgSeqNo = lpmsgHdr->MsgSeqNo;            //save packet sequence NO.

   lpcommBuf = CommBuf + sizeof(MSGHEADER);  //get first message ptr.


   //unpack the packet, put messages into their buffers.
   for (i = 0; i < lpmsgHdr->MsgNum; i++)
   {
	  MsgIdAdd = lpcommBuf[0];
      switch(lpcommBuf[0] & 0x0F)
      {
		 
         case MSG_EVENT:                     //0x1

              EventRcvBuf.MsgId = NEW_MSG;   //set new message id.
              
              lpkeyEventMsg = (LPKEYEVENTMSG)lpcommBuf;
              
              EventRcvBuf.Event = lpkeyEventMsg->Event;
              EventRcvBuf.Param = lpkeyEventMsg->Param;
              
              lpcommBuf += sizeof(KEYEVENTMSG); //move ptr to next message.
               
              break;
		   
                            
         case MSG_INPUT:                     //0x2
			  /*
              InputLast->InputRcvBuf.MsgId = NEW_MSG; //set new message id.
              lpinputMsg = (LPINPUTMSG)lpcommBuf;
              InputLast->InputRcvBuf.Input = lpinputMsg->Input;
              lpcommBuf += sizeof(INPUTMSG);          //move ptr to next message.
              */
			#ifdef __INTEL_CPU__
              InputLast->InputRcvBuf.MsgId = NEW_MSG; //set new message id.
              lpinputMsg = (LPINPUTMSG)lpcommBuf;
              InputLast->InputRcvBuf.Input = lpinputMsg->Input;
              InputLast->InputRcvBuf.Input >>= 8;
			  isOpponentKeyUp = MsgIdAdd >> 4;
              lpcommBuf += sizeof(INPUTMSG);          //move ptr to next message.
			#endif

			#ifdef __MOTOROLA_CPU__
              InputLast->InputRcvBuf.MsgId = NEW_MSG; //set new message id.
              lpinputMsg = (LPINPUTMSG)lpcommBuf;
              InputLast->InputRcvBuf.Input = lpinputMsg->Input;
              InputLast->InputRcvBuf.Input &= 0x00FFFFFF;
			  isOpponentKeyUp = MsgIdAdd >> 4;
              lpcommBuf += sizeof(INPUTMSG);          //move ptr to next message.
			#endif


              if (InputLast->Next != InputFirst)
              {
                  InputLast = InputLast->Next;
              }
              else
              {
                  //INPUT POOL is not enough. clear the oldest input. 
				  //it exist in the faster computer. Eric
				  InputFirst = InputFirst->Next;
				  InputLast  = InputLast->Next;
              }

              break;
           
   
         case MSG_CHARSPEC:                  //0x3
         	
              CharSpecRcvBuf.MsgId = NEW_MSG;//set new message id.

              lpcharSpecMsg = (LPCHARSPECMSG)lpcommBuf;
             
              //this can implement by using memcpy, just for clear here.              
          	  
			  CharSpecRcvBuf.Position       = lpcharSpecMsg->Position;        
              CharSpecRcvBuf.Direction      = lpcharSpecMsg->Direction;       
              //CharSpecRcvBuf.Up             = lpcharSpecMsg->Up;       
              CharSpecRcvBuf.Velocity       = lpcharSpecMsg->Velocity;
              CharSpecRcvBuf.Speed          = lpcharSpecMsg->Speed;           
              CharSpecRcvBuf.Distance       = lpcharSpecMsg->Distance;
              CharSpecRcvBuf.Energy         = lpcharSpecMsg->Energy;          
              CharSpecRcvBuf.Life           = lpcharSpecMsg->Life;            
              CharSpecRcvBuf.MovementState  = lpcharSpecMsg->MovementState;
              CharSpecRcvBuf.AnimationState = lpcharSpecMsg->AnimationState;
              CharSpecRcvBuf.AnimationFrame = lpcharSpecMsg->AnimationFrame;
              
			  //memcpy(&CharSpecRcvBuf,lpcharSpecMsg,sizeof(CHARSPECMSG));
              lpcommBuf += sizeof(CHARSPECMSG); //move ptr to next message.
			  
              break;



         case MSG_WEAPONSPEC:                //0x4
         
              /*
              InputRcvBuf.MsgId = NEW_MSG;   //set new message id.

              lpinputMsg = (LPINPUTMSG)lpcommBuf;
              
              InputRcvBuf.Input = lpinputMsg->Input;
              
              lpcommBuf += sizeof(WEAPONMSG); //move ptr to next message.
              */
              break;

         case MSG_TEXT:                      //0x5
         
              TextRcvBuf.MsgId = NEW_MSG;    //set new message id.

              lptextMsg = (LPTEXTMSG)lpcommBuf;
              
              if (strlen((char *)lptextMsg->Text) >= MAX_TEXT_LEN)
              {
                 break;                      //ignore the text message.
              }

              strcpy((char *)TextRcvBuf.Text, (char *)lptextMsg->Text);
              
              lpcommBuf += strlen(lptextMsg->Text);  //move ptr to next message.
              
              break;



         default:
              i = 10;        //data error!, stop.
              break;
      }
   }

   //write received messages into Debug Window;
   //#ifdef _MSGOUT_     
	#ifdef _FILEOUTPUTNETMSG_
   for (i = 0; i < (lpcommBuf - CommBuf); i ++)
   {
      lowByte = CommBuf[i] & 0xf;
      hiByte = (CommBuf[i] >> 4) & 0xf;
      
      msgOut[i * 2] = (char)((hiByte <= 0x9)? (hiByte + '0') : (hiByte + 'a' - 0xa));
      msgOut[i * 2 + 1] = (char)((lowByte <= 0x9)? (lowByte + '0') : (lowByte + 'a' - 0xa));
   }

   msgOut[i * 2] = '\0';
   
   OutputDebugString("\n!! Receive !!");
   OutputDebugString(msgOut);
   //#endif
   {
		 FILE *fp;

		 if (isHost)
		 {
		     fp = fopen("C:\\RobotRCV.MSG", "a+");
			 fprintf(fp, "%s%s", "\nRCV:", msgOut);  
		 }
		 else
		 {
			 fp = fopen("C:\\MONSTRCV.MSG", "a+");
			 fprintf(fp, "%s%s", "\nRCV:", msgOut);  
		 }

	     fclose(fp);
   }
	#endif //_FILEOUTPUTNETMSG_
}


//check if newMsgNo is before oldMsgNo
BOOL IsPrevMsg(short newMsgNo, short oldMsgNo)
{
   newMsgNo -= oldMsgNo;

   if ((newMsgNo > 0 && newMsgNo < 127) || (newMsgNo < - 127))
   {
      return FALSE;       //newMsg is later than oldMsg;
   }

   return TRUE;           //newMsg is missed msg.
}




//processing received messages
void ProcessRcvMsgs()
{
   extern RLValue SegCountdown;
   //process Event Message:
   if (EventRcvBuf.MsgId == NEW_MSG)
   {

      switch(EventRcvBuf.Event)
      {
         case EVENT_HEREIAM:

              if (isHost)
              {
                  //EventSndBuf.MsgId = NEW_MSG;
                  //EventSndBuf.Event = EVENT_HEREIAM;
                    
                  //beSynchronous = TRUE;           // start playing from now.
                    
              }
              else
              {
                  //beSynchronous = TRUE;           // start playing from now.
                  EventSndBuf.MsgId = OLD_MSG;    // stop sending only when received echo.
              }
        
              break;


         case EVENT_GOODBYE:

			  PostMessage(BYMainHwnd, WM_DESTROY, 0, 0L);
			  //DestroyWindow(BYMainHwnd);

              break;


         case EVENT_ESC:

			  if (!GameStates.Is3DMovie) 
			  {
				  bAskQuit = TRUE;
				  isOpponentSend = TRUE;
			  }

			  break;

         case EVENT_EXITTOMENU:
           /*
			  In3DMovie = 0;
			  NextLevel = 0;
			  bBYRenderingIsOK = FALSE;
			  if (isIn3DGame) 
              CleanupGame3DPart();
			  bBYRenderingIsOK = TRUE;
			  BYKbFrom3DTo2D(BYMainHwnd, 0L, 0L, 0L);
           */
            Ending3DMovie.SegCountdown = RLVal(0.0);
			  if (isIn3DGame) 
			     NextLevel = 1;
			  //QuitFlag = TRUE;
			  bAskQuit = FALSE;

			  //NextLevel = 1;
			  //In3DMovie = 0;
			  //isOpponentSend = TRUE;
			  break;

         case EVENT_YES:
			  
			  bBYRenderingIsOK = FALSE;
			  CleanupGame3DPart();
			  bBYRenderingIsOK = TRUE;
			  BYKbFrom3DTo2D(BYMainHwnd, 0L, 0L, 0L);

			  QuitFlag = TRUE;
			  bAskQuit = FALSE;

			  isOpponentSend = FALSE;
			  //beSynchronous = FALSE;
			  //isSelectedCharacter = FALSE;

			  break;

         case EVENT_NO:

			  bAskQuit = FALSE;

			  isOpponentSend = FALSE;

			  break;


         case EVENT_POWERUP:

			  PowerUpHere(Robotframe);

			  break;

         case EVENT_BUILDING:

			  break;

         case EVENT_WHICHRobot:

			  GameStates.CurrentRobot = (int)EventRcvBuf.Param;
			  isOpponentSend = TRUE;
			  if (beSynchronous)
			  {
				  isOpponentSend = FALSE;
			  }

			  break;

         case EVENT_LEVEL:

			  GameStates.CurrentLevel = (int)EventRcvBuf.Param;
			  isOpponentSend = TRUE;
			  if (beSynchronous)
			  {
				  isOpponentSend = FALSE;
			  }

			  break;

         case EVENT_CHARDEAD:

			  if (isHost)
			  {
				  MnstLife = 0;
				  MonsterAnimationState = MonsterAllDead;
				  MonstDeadTimes++;
              if (!(MonsterData.collisionflag))
              {
                  MonsterData.collisionflag=1;
                  MonsterData.DamageIveTaken=100;
                  MonsterData.CollisionVector.x=RLVal(1.0);
                  MonsterData.CollisionVector.y=RLVal(0.0);
                  MonsterData.CollisionVector.z=RLVal(0.0);
              }
				  //if (MonstDeadTimes != EventRcvBuf.Param)
					//  MonstDeadTimes = EventRcvBuf.Param;
			  }
			  else
			  {
				  RobotLife = 0;
				  RobotDeadTimes++;
              if (!(RobotData.collisionflag))
              {
                  RobotData.collisionflag=1;
                  RobotData.DamageIveTaken=100;
                  RobotData.CollisionVector.x=RLVal(1.0);
                  RobotData.CollisionVector.y=RLVal(0.0);
                  RobotData.CollisionVector.z=RLVal(0.0);
              }
				  //DestroyWindow(BYMainHwnd);
				  //if (RobotDeadTimes != EventRcvBuf.Param)
					//  RobotDeadTimes = EventRcvBuf.Param;
			  }

			  bAskQuit = FALSE;
			  isOpponentSend = FALSE;

              break;
      }
      
      EventRcvBuf.MsgId = OLD_MSG;
   }
   
   
   if (isIn3DGame)
   {
	   //process Input Message:
	   if (InputFirst->InputRcvBuf.MsgId == NEW_MSG)
	   {
		  if (isHost)
	      {
		      *InputIntPtr2 = InputFirst->InputRcvBuf.Input; // set monster
	      }
		  else
	      {   
		     *InputIntPtr3 = InputFirst->InputRcvBuf.Input; // set Robot
	      }
		
	      InputFirst->InputRcvBuf.MsgId = OLD_MSG;
		  
	      InputFirst = InputFirst->Next;             //to next input buffer.
	   }
	   else
	   {
		  if (isHost)
	      {	 
			  //if set it equal to zero, make the jet and protected ring error.
			  if (isOpponentKeyUp)
			  {
			      *InputIntPtr2 = 0;                      // clear monster input
			  }
	      }
		  else
	      {  
			  if (isOpponentKeyUp)
			  {
				  *InputIntPtr3 = 0;                      // clear Robot input
			  }
		  }
	   }

	   //process CharSpec Message:
	   if (CharSpecRcvBuf.MsgId == NEW_MSG)
	   {
		   ConvertCharSpecData();  
	  	   CharSpecRcvBuf.MsgId = OLD_MSG;
	   }
   
	   //process WeaponSpec Message:
	   if (WeaponSpecRcvBuf.MsgId == NEW_MSG)
	   {

	   }
   
	   //process Text Message:
	   if (TextRcvBuf.MsgId == NEW_MSG)
	   {
		   YBSetSubTitle1(Vmode, TextRcvBuf.Text, RGB(0, 255, 0));
	       TextRcvBuf.MsgId = OLD_MSG;
	   }
   }
   
   return;
}


//Convert CharSpecMsg into RL format for LocalAi use.
void ConvertCharSpecData()
{
    LPDIRECT3DRMFRAME     scene;
	D3DVECTOR up;

	up.x = (float)0;
	up.y = (float)1;
	up.z = (float)0;

	Robotframe->lpVtbl->GetScene(Robotframe, &scene);
	//scene = Wscene;

   CharSpecData.MsgId = NEW_MSG;

   VectorWtoF(&CharSpecData.CurPos, &CharSpecRcvBuf.Position);
   VectorWtoF(&CharSpecData.CurVelocity, &CharSpecRcvBuf.Velocity);
   VectorBtoF(&CharSpecData.CurDir, &CharSpecRcvBuf.Direction);
   //VectorBtoF(&CharSpecData.CurUp, &CharSpecRcvBuf.Up);

   CharSpecData.CurSpeed    = WTOF(CharSpecRcvBuf.Speed);
   CharSpecData.CurDistance = WTOF(CharSpecRcvBuf.Distance);
   CharSpecData.CurEnergy   = WTOI(CharSpecRcvBuf.Energy);
   CharSpecData.CurLife     = CTOI(CharSpecRcvBuf.Life);

   CharSpecData.CurMovState = CTOI(CharSpecRcvBuf.MovementState);
   CharSpecData.CurAniState = CTOI(CharSpecRcvBuf.AnimationState);
   CharSpecData.CurAniFrame = WTOF(CharSpecRcvBuf.AnimationFrame);

   
   if (isHost)
   {   
       monstframe->lpVtbl->SetOrientation(monstframe, scene,
		   CharSpecData.CurDir.x,
		   CharSpecData.CurDir.y,
		   CharSpecData.CurDir.z,
		   up.x, up.y, up.z);
	   monstframe->lpVtbl->SetPosition(monstframe, scene, 
		   CharSpecData.CurPos.x, 
		   CharSpecData.CurPos.y, 
		   CharSpecData.CurPos.z);
	   MnstEngy        = CharSpecData.CurEnergy;
	   MnstLife	   	   = CharSpecData.CurLife;
	   
	   if (isOpponentKeyUp)
	   {
		   monstframe->lpVtbl->SetVelocity(monstframe, scene,
		       CharSpecData.CurVelocity.x, 
			   CharSpecData.CurVelocity.y, 
		       CharSpecData.CurVelocity.z, 
			   FALSE);
	   	 
	       //MonsterVelocity = CharSpecData.CurVelocity;

		   MonsterSpeed    = CharSpecData.CurSpeed;
	       MonsterDistance = CharSpecData.CurDistance;
   
		   MonsterMovementState  = CharSpecData.CurMovState;
	       MonsterAnimationState = CharSpecData.CurAniState;
		   MonsterAnimationFrame = CharSpecData.CurAniFrame;
	   } 
   }
   else
   {
       Robotframe->lpVtbl->SetOrientation(Robotframe, scene,
		   CharSpecData.CurDir.x,
		   CharSpecData.CurDir.y,
		   CharSpecData.CurDir.z,
		   up.x, up.y, up.z);
	   Robotframe->lpVtbl->SetPosition(Robotframe, scene, 
		   CharSpecData.CurPos.x, 
		   CharSpecData.CurPos.y, 
		   CharSpecData.CurPos.z);
	   RobotEngy     = CharSpecData.CurEnergy;
	   RobotLife		= CharSpecData.CurLife;
	   
	   if (isOpponentKeyUp)
	   {
		   Robotframe->lpVtbl->SetVelocity(Robotframe, scene,
		       CharSpecData.CurVelocity.x, 
			   CharSpecData.CurVelocity.y, 
			   CharSpecData.CurVelocity.z, 
				FALSE);
		   
		   //RobotVelocity = CharSpecData.CurVelocity;

		   RobotSpeed    = CharSpecData.CurSpeed;
		   RobotDistance = CharSpecData.CurDistance;
   
		   RobotMovementState  = CharSpecData.CurMovState;
		   RobotAnimationState = CharSpecData.CurAniState;
		   RobotAnimationFrame = CharSpecData.CurAniFrame;
	   } 
   }
   
}

               
//prepare new message to send(if has)
void PrepareMsgToSend()
{
   //no need to set InputMsg and EventMsg buffer.

	if (isIn3DGame)
	{
		//set CharSpecMsg buffer:
	    GetCharSpecData();

	    //set WeaponSpecMsg buffer:
	    GetWeaponSpecData();
	}
   //set TextMsg buffer:
   
   return;

}


void GetCharSpecData()
{
    D3DVECTOR    dir, up, pos;//, vel;
    LPDIRECT3DRMFRAME     scene;


	//scene = Wscene;
	Robotframe->lpVtbl->GetScene(Robotframe, &scene);
 
    // write MovingSpecData.
    
    if (isHost)
    {
        Robotframe->lpVtbl->GetOrientation(Robotframe, scene, &dir, &up);
		Robotframe->lpVtbl->GetPosition(Robotframe, scene, &pos);
		//Robotframe->lpVtbl->GetVelocity(Robotframe, scene, &vel, FALSE);
		CharSpecSndData.CurPos      = pos;
		CharSpecSndData.CurVelocity = RobotVelocity;
		CharSpecSndData.CurDir      = dir;
		//CharSpecSndData.CurUp       = up;
		CharSpecSndData.CurSpeed    = RobotSpeed;
		CharSpecSndData.CurDistance = RobotDistance;
		CharSpecSndData.CurEnergy   = RobotEngy;
		CharSpecSndData.CurLife     = RobotLife;
		CharSpecSndData.CurMovState = RobotMovementState;
		CharSpecSndData.CurAniState = RobotAnimationState;
		CharSpecSndData.CurAniFrame = RobotAnimationFrame;
	}
    else
    {
	    monstframe->lpVtbl->GetOrientation(monstframe, scene, &dir, &up);
		monstframe->lpVtbl->GetPosition(monstframe, scene, &pos);
		//monstframe->lpVtbl->GetVelocity(monstframe, scene, &vel, FALSE);
		CharSpecSndData.CurPos      = pos;
		CharSpecSndData.CurVelocity = MonsterVelocity;
		CharSpecSndData.CurDir      = dir;
		//CharSpecSndData.CurUp       = up;
		CharSpecSndData.CurSpeed    = MonsterSpeed;
		CharSpecSndData.CurDistance = MonsterDistance;
		CharSpecSndData.CurEnergy   = MnstEngy;
		CharSpecSndData.CurLife     = MnstLife;
		CharSpecSndData.CurMovState = MonsterMovementState;
		CharSpecSndData.CurAniState = MonsterAnimationState;
		CharSpecSndData.CurAniFrame = MonsterAnimationFrame;
   }

	//Only for debuging
	Robotframe->lpVtbl->GetPosition(Robotframe, scene, &pos);
	YBRobotPos  = pos;
	monstframe->lpVtbl->GetPosition(monstframe, scene, &pos);
	YBMonstPos = pos;

    VectorFtoW(&CharSpecSndBuf.Position, &CharSpecSndData.CurPos);
    VectorFtoW(&CharSpecSndBuf.Velocity, &CharSpecSndData.CurVelocity);
    VectorFtoB(&CharSpecSndBuf.Direction, &CharSpecSndData.CurDir);
    //VectorFtoB(&CharSpecSndBuf.Up, &CharSpecSndData.CurUp);
    CharSpecSndBuf.Speed          = FTOW(CharSpecSndData.CurSpeed);
    CharSpecSndBuf.Distance       = FTOW(CharSpecSndData.CurDistance);

	if (CharSpecSndData.CurEnergy > 65535)
		CharSpecSndData.CurEnergy = 65535;
	if (CharSpecSndData.CurEnergy < 0)
		CharSpecSndData.CurEnergy = 0;
    CharSpecSndBuf.Energy         = ITOW(CharSpecSndData.CurEnergy);
    CharSpecSndBuf.Life           = ITOC(CharSpecSndData.CurLife);
    CharSpecSndBuf.MovementState  = ITOC(CharSpecSndData.CurMovState);
    CharSpecSndBuf.AnimationState = ITOC(CharSpecSndData.CurAniState);
    CharSpecSndBuf.AnimationFrame = FTOW(CharSpecSndData.CurAniFrame);
   
   CharSpecSndBuf.MsgId = NEW_MSG;

   return;
}


void GetWeaponSpecData()
{
   return;
}


//adding a message header for the packet
void AddMsgHeader(BYTE * lpcommBuf, BYTE msgSeqNo, BYTE msgNum)
{
   WORD         timeStamp;
   DWORD        time;
   LPMSGHEADER  lpmsgHdr;

   
   lpmsgHdr = (LPMSGHEADER)lpcommBuf;

   lpmsgHdr->MsgSeqNo = msgSeqNo;
   lpmsgHdr->MsgNum = msgNum;

   time = GetTickCount();
   timeStamp = (WORD)(time & 0xFFFF);
   lpmsgHdr->TimeStamp = timeStamp;

   return;
}



//pack Event message 
BOOL GetEventMsg(BYTE * lpcommBuf)
{
   LPKEYEVENTMSG  lpeventMsg;
   static int     Delay = 0;

   if (EventSndBuf.MsgId == OLD_MSG)   
   {
      return FALSE;
   }
   /*
   if (!isIn3DGame)
   {
		Delay ++;

		//if ((isHost == FALSE) && Delay < 50)      //not send next event too soon for player as monster, 
		if (Delay < 50)
		{
		   return FALSE;
		}
   
		Delay = 0;
   }
   */   
   lpeventMsg = (LPKEYEVENTMSG)lpcommBuf;

   lpeventMsg->MsgId = MSG_EVENT;
   lpeventMsg->Event = EventSndBuf.Event;
   lpeventMsg->Param = EventSndBuf.Param;

   EventSndBuf.MsgId = OLD_MSG;

   if (!isIn3DGame)
   {
	   //repeat sending before reponse.
	   if (!isHost)               //slave stop send only when received replay.
	   {
		   //EventSndBuf.MsgId = NEW_MSG;
	   }
   }

   return TRUE;
}
 


//pack Input message 
BOOL GetInputMsg(BYTE * lpcommBuf)
{
   LPINPUTMSG   lpinputMsg;
   DWORD        input  = 0;
   static DWORD NoKeyInputTimes = 0;
   BYTE         isKeyUp;
 
   
   if (!beSynchronous)
   {
       return FALSE;
   }

   //if (!KbFlag)
   if (*InputIntPtr == 0)
   {
	   isKeyUp = 1;
   	   NoKeyInputTimes++;

	   if (NoKeyInputTimes > 1)
	   {
		   CharSpecMsgCanBeTransmitted = TRUE;
		   //When the key is up, only send keyup info.
		   return FALSE;
	   }

   }
   else
   {
	   isKeyUp = 0;
	   NoKeyInputTimes = 0;
	   CharSpecMsgCanBeTransmitted = FALSE;
   }

   if (*InputIntPtr > 0x00FFFFFF)
   {
		 *InputIntPtr = 0;
   }


#ifdef __INTEL_CPU__
   //if input = 0x12345678. after transmit to BYTE* queue is = 78653412
   //only in intel CPU. if in Power PC , it's will be error. Eric
   input = *InputIntPtr;
   input <<= 8;
   input |= MSG_INPUT;
   input |= isKeyUp << 4;
#endif


#ifdef __MOTOROLA_CPU__
   input = MSG_INPUT;
   input |= isKeyUp << 4;
   input <<= 24;
   input |= *InputIntPtr;
#endif


   lpinputMsg = (LPINPUTMSG)lpcommBuf;
   lpinputMsg->Input = input;

   return TRUE;
}


//pack CharSpec message 
BOOL GetCharSpecMsg(BYTE * lpcommBuf)
{
   LPCHARSPECMSG  lpcharSpecMsg;

   if (!beSynchronous)
   {
       return FALSE;
   }

   //if (*InputIntPtr)
   //{
//	   return FALSE;
   //}
   
   if (CharSpecSndBuf.MsgId == OLD_MSG)     
   {
      return FALSE;
   }

   lpcharSpecMsg = (LPCHARSPECMSG)lpcommBuf;

   lpcharSpecMsg->MsgId          = MSG_CHARSPEC;
   
   lpcharSpecMsg->Position       = CharSpecSndBuf.Position;        
   lpcharSpecMsg->Direction      = CharSpecSndBuf.Direction;       
   //lpcharSpecMsg->Up             = CharSpecSndBuf.Up;       
   lpcharSpecMsg->Velocity       = CharSpecSndBuf.Velocity;
   lpcharSpecMsg->Speed          = CharSpecSndBuf.Speed;           
   lpcharSpecMsg->Distance       = CharSpecSndBuf.Distance;
   lpcharSpecMsg->Energy         = CharSpecSndBuf.Energy;          
   lpcharSpecMsg->Life           = CharSpecSndBuf.Life;            
   lpcharSpecMsg->MovementState  = CharSpecSndBuf.MovementState;
   lpcharSpecMsg->AnimationState = CharSpecSndBuf.AnimationState;
   lpcharSpecMsg->AnimationFrame = CharSpecSndBuf.AnimationFrame;

   CharSpecSndBuf.MsgId = OLD_MSG;

   return TRUE;

}



//pack WeaponSpec message 
BOOL GetWeaponSpecMsg(BYTE * lpcommBuf)
{
   if (!beSynchronous)
   {
       return FALSE;
   }

   return FALSE;
}


//pack Text message 
BOOL GetTextMsg(BYTE * lpcommBuf)
{
   LPTEXTMSG  lptextMsg;

   if (!beSynchronous)
   {
       return FALSE;
   }

   if (TextSndBuf.MsgId == OLD_MSG)     
   {
      return FALSE;
   }

  
   lptextMsg = (LPTEXTMSG)lpcommBuf;
  
   lptextMsg->MsgId = MSG_TEXT;
  
   strcpy(lptextMsg->Text, TextSndBuf.Text);
  
   TextSndBuf.MsgId = OLD_MSG;
        

   return TRUE;
}



// Issues need to be considere :
/*
 - Frame Rate may vary 

 - Bandwidth may vary

 - Send Bytes / Per Second should be adjusted any time.
 
 - Message Priority:

   Input, Event           | high
   CharSpec, WeaponSpec   |
   Text                   v low

*/
   

void SendNetMessages()
{
   static BYTE  MsgSeqNo = 0;
   static BOOL  OverSending = FALSE;
   static short OverSendingBytes = 0;
  
   BOOL         status;
   short int    sendBytes;
   short int    keyBytes;
   BYTE         msgNum;
   BYTE         keyMsgNum;
   BYTE        *lpcommBuf;

   #ifdef _FILEOUTPUTNETMSG_
   int          i;            //only for debugging.
   BYTE         hiByte;
   BYTE         lowByte;
   char         msgOut[512];
   #endif

   sendBytes = 0;
   keyBytes = 0;
   msgNum = 0;
   keyMsgNum = 0;
   lpcommBuf = CommBuf;
   
   //skip msg header;
   sendBytes += sizeof(MSGHEADER);
   lpcommBuf += sizeof(MSGHEADER);

   
   //get all kinds of messages into CommBuf;
   status = GetEventMsg(lpcommBuf);
   if (status)
   {
      //WaitingforEventAck = TRUE;
      msgNum ++;
      sendBytes += sizeof(KEYEVENTMSG);
      lpcommBuf += sizeof(KEYEVENTMSG);
   }
   
   
   //only in 3d scene, character's data can be transmitted.
   if (isIn3DGame)
   {
	   status = GetInputMsg(lpcommBuf);
	   if (status)
	   {
		  //WaitingforInputAck = TRUE;
	      msgNum ++;
		  sendBytes += sizeof(INPUTMSG);
	      lpcommBuf += sizeof(INPUTMSG);
	   }
	 
	   keyMsgNum = msgNum;
	   keyBytes = sendBytes;     // Input and Event messages bytes.

	   status = GetCharSpecMsg(lpcommBuf);
	   if (status)
	   {
		  msgNum ++;
	      sendBytes += sizeof(CHARSPECMSG);
	      lpcommBuf += sizeof(CHARSPECMSG);
	   }
 
   
	   status = GetWeaponSpecMsg(lpcommBuf);
	   if (status)
	   {
		  msgNum ++;
	      sendBytes += sizeof(WEAPONSPECMSG);
		  lpcommBuf += sizeof(WEAPONSPECMSG);
		}

   
	   status = GetTextMsg(lpcommBuf);
	   if (status)
	   {
		  msgNum ++;
	      sendBytes += strlen(TextSndBuf.Text) + 2; //add '\0' and MsgId size;
		  lpcommBuf += strlen(TextSndBuf.Text) + 2;
	   }
   }
   
   if (msgNum == 0)                //no message to be sent.
   {
      return;
   }
 
 
   //all messages to be sent are already in lpCommBuf;

   if (!OverSending)           
   {
      MsgSeqNo ++;
      AddMsgHeader(CommBuf, MsgSeqNo, msgNum);

      //no last frame left bytes left to be sent.
      if (SimuMode != 0)
      {
         status = SimuSend(MyId, ToId, DPSEND_TRYONCE, CommBuf, sendBytes);
      }
      else
      {
         status = lpDPId->lpVtbl->Send(lpDPId, MyId, ToId, DPSEND_TRYONCE,
                                       CommBuf, sendBytes);
      }
      
      if (sendBytes > MaxBytes)     
      {
         OverSending = TRUE;
         OverSendingBytes = sendBytes - MaxBytes;
      }
   }
   else            //last frame had left bytes to be sent.
   {
      //all bytes could be sent in this frame 
      //or not to many bytes exceeded. (left to send in next frame)
      OverSendingBytes += sendBytes - MaxBytes;

      if (OverSendingBytes <= ALLOW_OVER_BYTES)  
      {
         MsgSeqNo ++;
         AddMsgHeader(CommBuf, MsgSeqNo, msgNum);
         
         if (SimuMode != 0)
         {
            status = SimuSend(MyId, ToId, DPSEND_TRYONCE, CommBuf, sendBytes);
         }
         else
         {
            status = lpDPId->lpVtbl->Send(lpDPId, MyId, ToId, DPSEND_TRYONCE,
                                          CommBuf, sendBytes);
         }

         if (OverSendingBytes <= 0)
         {
            OverSending = FALSE;
            OverSendingBytes = 0;
         }
      
         //auto adjust the number of bytes/frame.
         if (status == DP_OK)   //no message still in DP queue,
         {
            MaxBytes += 4;      //add the number of Bytes/frame.
         }
         else
         {
            if (status > 1)     //more than 1 message still in DP queue.
            {                                       
               MaxBytes -= 4;   //reduce the number of Bytes/frame;
            }
         }                      

		#ifdef _FILEOUTPUTNETMSG_

		 {
			 FILE *fp;

		     fp = fopen("C:\\MaxBytes.TXT", "a+");
			 fprintf(fp, "\nMaxBytes = %d", MaxBytes);  
		     fclose(fp);
		 }
		#endif //_FILEOUTPUTNETMSG_


  }  
      else        //could not send all bytes, only consider Input & Event.
      {  
         if (keyMsgNum > 0)  
         {
            msgNum = keyMsgNum;         //only for debugging;
            sendBytes = keyBytes;       //only for debugging;

            MsgSeqNo ++;
            AddMsgHeader(CommBuf, MsgSeqNo, keyMsgNum);

            if (SimuMode != 0)
            {
               status = SimuSend(MyId, ToId, DPSEND_TRYONCE, CommBuf, keyBytes);
            }
            else
            {
               status = lpDPId->lpVtbl->Send(lpDPId, MyId, ToId, 
                                             DPSEND_TRYONCE, CommBuf, keyBytes);
            }

            OverSendingBytes += keyBytes - sendBytes;
            if (OverSendingBytes < 0)
            {  
               OverSending = FALSE;
               OverSendingBytes = 0;
            }
         }  
      }
   }

   //#ifdef _MSGOUT_         //write messages into Debug Window;
	#ifdef _FILEOUTPUTNETMSG_
   if (msgNum != 0)
   {
      for (i = 0; i < sendBytes; i ++)
      {
         lowByte = CommBuf[i] & 0xf;

         hiByte = (CommBuf[i] >> 4) & 0xf;
      
         msgOut[i * 2] = (char)((hiByte <= 0x9)? (hiByte + '0') : (hiByte + 'a' - 0xa));
         msgOut[i * 2 + 1] = (char)((lowByte <= 0x9)? (lowByte + '0') : (lowByte + 'a' - 0xa));
      }

      msgOut[i * 2] = '\0';
   
      OutputDebugString("\n!! Send !!");
      OutputDebugString(msgOut);

   }

	  {
		 FILE *fp;

		 if (isHost)
		 {
		     fp = fopen("C:\\RobotSND.MSG", "a+");
			 fprintf(fp, "%s%s", "\nSND:", msgOut);  
		 }
		 else
		 {
			 fp = fopen("C:\\MONSTSND.MSG", "a+");
			 fprintf(fp, "%s%s", "\nSND:", msgOut);  
		 }

	     fclose(fp);
      }
   //#endif
	#endif //_FILEOUTPUTNETMSG_

   return;
}   
   

//#ifdef _SIMULATE_

//Simulate the Internet with LAN.
//Errors      : 1/10 message lost.
//Latency     : 220 ms one way.
//Wrong Order : 1/100 wrong order.
      
HRESULT SimuSend(DPID myId, DPID toId, DWORD flag,
                 LPVOID commBuf, DWORD size)
{
    short    randNum;
    int      i;
    HRESULT  status;
    static   int cont = 0;

    switch (SimuMode)
    {
       case  MISSING:
             
             //miss 3 message continuously.
             if (cont != 0)
             {
                cont --;
                return DP_OK;
             }

             //miss message randomly.
             randNum = (short)(rand() % MAX_RAND);

             if (10 == randNum)
             {
                cont = 3;
                return DP_OK;
             }    
             else
             {
                status = lpDPId->lpVtbl->Send(lpDPId, myId, toId, 
                                              flag, commBuf, size);
                return status;
             }


       case LATENCY:
		    
            for (i = 0; i < MAX_SIMU_BUFFER; i++)
            {
               if (SimuArray[i].full == FALSE)
               {
                   SimuArray[i].time = GetTickCount();
                   memcpy(SimuArray[i].Buff, commBuf, size);
                   SimuArray[i].size = size;             
				   SimuArray[i].full = TRUE;             
				   break;
               }
            }
             
            for (i = 0; i < MAX_SIMU_BUFFER; i++)
            {
               if (SimuArray[i].full == TRUE)
               {
				   if (LatencyTimeOut(i))
				   {
			           lpDPId->lpVtbl->Send(lpDPId, MyId, ToId, DPSEND_TRYONCE, 
                               SimuArray[i].Buff, SimuArray[i].size);

					   ResetSimuArray(i);
				   }
               }
            }
			/*
            if (i == MAX_SIMU_BUFFER)      //no room for this message;
            {
                return DPERR_BUSY;
            }
            */ 
            return DP_OK;

	   
       case  WRONGORDER:

             if (WrongOrderNo > 0)
             {
                if (0 <= (-- WrongOrderNo))
                { 
                   lpDPId->lpVtbl->Send(lpDPId, myId, toId, flag, 
                                        SimuArray[0].Buff, SimuArray[i].size);
                }
             }

             randNum = (short)(rand() % (MAX_RAND * 10));

             if (20 == randNum)   //save into buffer for later send;
             {
                WrongOrderNo = 3;
                memcpy(SimuArray[0].Buff, commBuf, size);
                SimuArray[0].size = size;
             }    
             else                 //send as normal;
             {
                status = lpDPId->lpVtbl->Send(lpDPId, myId, toId, 
                                              flag, commBuf, size);
                return status;
             }

             return DP_OK;
    	
    }

    return DP_OK;
}



BOOL sendDWORD(DWORD dwSnd)
{
	HRESULT state;

	memset(CommBuf,0x00,sizeof(DWORD));
	*(LPDWORD)CommBuf = dwSnd;

    state = lpDPId->lpVtbl->Send(lpDPId, MyId, ToId, DPSEND_TRYONCE, 
                                 CommBuf, sizeof(DWORD));

	if (state == DP_OK)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL receiveDWORD(LPDWORD lpdwRcv)
{
    DPID    fromId; 
    DPID    rcvId;
    DWORD   wbufLen;
	HRESULT state;

	memset(CommBuf,0x00,sizeof(DWORD));
	wbufLen = MAX_COMBUF_LEN;
    state = lpDPId->lpVtbl->Receive(lpDPId, &fromId, &rcvId, 
                                       DPRECEIVE_ALL, (LPVOID)CommBuf, &wbufLen);
	if (state == DP_OK)
	{
		if (0 != fromId)
		{
		   *lpdwRcv = *(LPWORD)CommBuf;
		   return TRUE;
		}
	}
	return FALSE;
}


VOID  CALLBACK Timer3Func(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{

	//Exit to win95
	//KillTimer(BYMainHwnd, timerId)
	DestroyWindow(BYMainHwnd);
    //SendMessage(BYMainHwnd, WM_CLOSE, 0, 0L);
	//PostMessage(BYMainHwnd, WM_KEYUP, VK_ESCAPE, 0L);
}

BOOL isNotTimeout(DWORD starttime, DWORD timeout)
{
	DWORD nowtime;

	nowtime = GetTickCount();

	if (nowtime - starttime < timeout)
	{
		//not timeout
		return TRUE;
	}
	else
	{
		//timeout
		return FALSE;
	}
}

VOID ResetSimuArray(int num)
{
	SimuArray[num].full = FALSE;
	SimuArray[num].time = 0;
	SimuArray[num].size = 0;
}

BOOL LatencyTimeOut(int num)
{
	DWORD nowtime;

	nowtime = GetTickCount();

	if (nowtime - SimuArray[num].time > LATENCY_TIME)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
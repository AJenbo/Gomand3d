//***********************************************************************//
// File Name: NETPLAY.H
// Author   : Lu Fengshun
// Date     : 1996.8.16
// Function : Netplay functions.
// Notes:       
// Update:
//***********************************************************************//

#ifndef __NETPLAY_H__
#define __NETPLAY_H__

#include <dplay.h>
#include <d3dtypes.h>



//define all consts
#define MAX_PLAYER      2
//#define SESSIONNAME     "ITC-RD7 Net Goman"
#define FORMALNAME      "Goman Player"
#define MASTERNAME      "Master"
#define SLAVENAME       "Slave"


#define  pg_GAMEPLAY   0x2A


//float - word (float range -128 - 127)
#define FTOW(f)     (WORD)((f + 128.0) * 255.0)
#define WTOF(w)     (float)((WORD)(w) / 255.0 - 128.0)


//float - byte (float range -1 - 1)
#define FTOB(f)     (BYTE)((f + 1.0) * 127.0)
#define BTOF(b)     (float)((BYTE)(b) / 127.0 - 1.0)


//char - byte  (char  range -128 - 127)
#define CTOB(i)     (BYTE)(i)
#define BTOC(b)     (int)(b)

//int - byte   (int   range 0 - 65536)
//#define ITOB(i)     (BYTE)((i) / 257.0)
//#define BTOI(b)     (int) ((b) * 257.0)
#define ITOC(i)     (char)(i)
#define CTOI(b)     (int) (b)

//int-WORD
#define ITOW(i)     (WORD)(i)
#define WTOI(b)     (int)(b)


// UUID code 99530400-ebbb-11cf-a918-0000e807f41a
DEFINE_GUID(GOMAN95_GUID,0x99530400,0xebbb,0x11cf,0xa9,0x18,0x00,0x00,0xe8,0x07,0xf4,0x1a);


typedef struct _BYTEVECTOR
{
   BYTE        x;
   BYTE        y;
   BYTE        z;
}  BYTEVECTOR;


typedef struct _WORDVECTOR
{
   WORD        x;
   WORD        y;
   WORD        z;
}  WORDVECTOR;



//----------------------------------------------------------
// communication packet structures
//----------------------------------------------------------

#define   MAX_COMBUF_LEN     256
#define   MAX_TEXT_LEN       80
#define   ALLOW_OVER_BYTES   10    //bytes allowed to send on next frame. 
#define   MAX_POOL           6 

// define message header

typedef struct _MSGHEADER
{
   WORD   TimeStamp;      //Time stamp when msg was sent.
   BYTE   MsgSeqNo;       //Message sequence No. sent by this Player.
                          //used to check msg missing or worng order.
   BYTE   MsgNum;         //How many object msgs in the packet?
}  MSGHEADER, *LPMSGHEADER;


//the format of a packet is:
//   MsgHeader
//   Msg1
//   Msg2
//   ...


//define message id in global buffers.
#define   NEW_MSG          0xFF
#define   OLD_MSG          0x0


//define four types message id:
#define   MAX_MSG_TYPES    5

#define   MSG_EVENT        0x1
#define   MSG_INPUT        0x2
#define   MSG_CHARSPEC     0x3
#define   MSG_WEAPONSPEC   0x4
#define   MSG_TEXT         0x5

//define EVENT messages id

#define   EVENT_HEREIAM    0x11    //a new comer add in.
#define   EVENT_GOODBYE    0x22    //one player will exit game.
#define   EVENT_CHARDEAD   0x33
#define   EVENT_ESC   	   0x44
#define   EVENT_YES   	   0x55
#define   EVENT_NO		   0x66
#define   EVENT_POWERUP	   0x77
#define   EVENT_BUILDING   0x88
#define   EVENT_WHICHRobot  0x99
#define   EVENT_LEVEL      0xAA
#define   EVENT_EXITTOMENU 0xBB


//define EVENT message structure:

typedef struct _KEYEVENTMSG
{
   BYTE   MsgId;          //which kind of message.
   BYTE   Event;          //which kind of event.
   WORD   Param;          //some event has parameter
}  KEYEVENTMSG, *LPKEYEVENTMSG;


//define BUILDING message structure:
typedef struct _BUILDINGMSG
{
   BYTE   MsgId;          //which kind of message.
   BYTE   x_world;      
   BYTE   z_world;
}  BUILDINGMSG, *LPBUILDINGMSG;

//LS complete it.
//WhichBuilding SearchBuilding(building.x_world, building.z_world);



//define INPUT message structure:

typedef struct _INPUTDATA
{
   BYTE   MsgId;          //which kind of message.
   DWORD  Input;          //Input data.
}  INPUTDATA, *LPINPUTDATA;

typedef union _INPUTMSG
{
   BYTE   MsgId;          //which kind of message.
   DWORD  Input;          //Input data.
}  INPUTMSG, *LPINPUTMSG;

 
typedef struct _InputPool * lpInputPool;

typedef struct _InputPool
{
   lpInputPool Next; 
   INPUTDATA    InputRcvBuf;
}  INPUTPOOL;


//define Character's SPEC message structure:

typedef struct _CHARSPECMSG
{
   BYTE        MsgId;           //which kind of message.
   WORDVECTOR  Position;        //range from -127.0 ~ 128.0
   BYTEVECTOR  Direction;       //range from -1 ~ 1.
   //BYTEVECTOR  Up;              //range from -1 ~ 1.
   //BYTE        Theta;         //reserved byte.
   WORDVECTOR  Velocity;
   WORD        Speed;           //max range 15000/65536.0 for RobotMaxFVel4
   WORD        Distance;
   //BYTE        Energy;          //range 0 - 65536
   WORD        Energy;          //range 0 - 65536
   char        Life;            //range 0 - 100
   char        MovementState;
   char        AnimationState;
   WORD        AnimationFrame;

}  CHARSPECMSG, *LPCHARSPECMSG;  //26 bytes.


//define D3D format Character SPEC data, for compensiting use:

typedef struct _CHARSPECDATA
{
   BYTE         MsgId;           
   D3DVECTOR    CurPos;    
   D3DVECTOR    CurDir;       
   //D3DVECTOR    CurUp;       
   D3DVECTOR    CurVelocity;
   D3DVALUE     CurSpeed;   
   D3DVALUE     CurDistance;
   int          CurEnergy;        
   int          CurLife;           
   int          CurMovState;
   int          CurAniState;
   D3DVALUE     CurAniFrame;

}  CHARSPECDATA, *LPCHARSPECDATA; 


//define Weapon's SPEC message structure:

typedef struct _WEAPONSPECMSG
{
   BYTE        MsgId;           //which kind of message.
   //.....       to be defined
}  WEAPONSPECMSG, *LPWEAPONSPECMSG;

//----------------------------------------------------------
// various weapons
//----------------------------------------------------------

enum { weaponHomer, weaponRapidFire, weaponCussin, weaponRings, weaponBomb, weaponZappa };

typedef struct _WEAPONHEADER_MSG
{
    BYTE            MsgCode;
    BYTE            WhoIAm;
    BYTE            Total;
} WEAPONHEADER_MSG, *LPWEAPONHEADER_MSG;

typedef struct _Homer_WeaponInfo
{
    BYTE            Weapon;
    WORDVECTOR      Position;
    WORDVECTOR      RobotSpewVelocity;
    WORD            HomerHowLong;
} Homer_WeaponInfo;




//define TEXT message structure:

typedef struct _TEXTMSG
{
   BYTE   MsgId;                 //which kind of message.
   BYTE   Text[MAX_TEXT_LEN];
}  TEXTMSG, *LPTEXTMSG;


//#ifdef _SIMULATE_

#define   MAX_SIMU_BUFFER  10
#define   sCount_NO        3           //5 * 55 = 275 ms;

#define   MAX_RAND         20

#define   MISSING          1
#define   LATENCY          2
#define   WRONGORDER       3


typedef struct _SIMUPARAM
{
	BOOL  full;
	DWORD time;
    DWORD size;
    BYTE  Buff[MAX_COMBUF_LEN];
}  SIMUPARAM, LPSIMUPARAM;

 
 
//----------------------------------------------------------
// global variables
//----------------------------------------------------------
extern LPDIRECTPLAY2A lpDPId;
extern DPID          dcoID;
extern DPID			 MyId;
extern BOOL          beSynchronous;
//extern BOOL        answerHereIAm;
//extern BOOL          netPlay;
extern BOOL          isHost;
extern BOOL          HasKey;
extern int           DisplayDebugMsgFlag;
extern BOOL          isIn3DGame;


extern INPUTMSG      InputSndBuf;
extern INPUTMSG      InputRcvBuf;

extern KEYEVENTMSG   EventRcvBuf;
 
extern CHARSPECMSG   CharSpecSndBuf;
extern CHARSPECMSG   CharSpecRcvBuf;

extern WEAPONSPECMSG WeaponSpecSndBuf;
extern WEAPONSPECMSG WeaponSpecRcvBuf;

extern TEXTMSG       TextSndBuf;
extern TEXTMSG       TextRcvBuf;

//extern BYTE     whoIAm;
//extern BYTE     youAre;

//----------------------------------------------------------
// function declaration
//----------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

extern int           RobotDeadTimes;
extern int           MonstDeadTimes;
extern BOOL          isSelectedCharacter;
extern BOOL          isOpponentSend;
extern KEYEVENTMSG   EventSndBuf;

void DestroyPlayer(DPID pidID);
void Close();


void InitMsgBuf(void);
void EvaluateMessage(DPID fromID, DWORD len);
BOOL IsPrevMsg(short newMsgNo, short oldMsgNo);
void GetCharSpecData(void);
void GetWeaponSpecData(void);
void ProcessRcvMsgs(void);
void ConvertCharSpecData(void);
void PrepareMsgToSend(void);
void SendNetMessages(void);
void ReceiveNetMessages(void);
void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nEvent, DWORD dwTime);
void AddMsgHeader(BYTE * lpcommBuf, BYTE msgSeqNo, BYTE msgNum);
BOOL GetEventMsg(BYTE * lpcommBuf);
BOOL GetInputMsg(BYTE * lpcommBuf);
BOOL GetCharSpecMsg(BYTE * lpcommBuf);
BOOL GetWeaponSpecMsg(BYTE * lpcommBuf);
BOOL GetTextMsg(BYTE * lpcommBuf);
 
HRESULT SimuSend(DPID From, DPID To, DWORD flag, LPVOID Buf, DWORD size);

BOOL isNotTimeout(DWORD starttime, DWORD timeout);
VOID CALLBACK Timer3Func(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
BOOL sendDWORD(DWORD);
BOOL receiveDWORD(LPDWORD);
VOID ResetSimuArray(int num);
BOOL LatencyTimeOut(int num);

#ifdef __cplusplus
};
#endif

#endif //__NETPLAY_H__
////////////////////////// End of this file ///////////////////////////////


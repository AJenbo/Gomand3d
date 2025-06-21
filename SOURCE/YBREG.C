//*******************************************************************
// ybreg.c
//
// Copyright 1996 by 47-TEK, INC.  All rights reserved.
//
// Author:	Bo Yuan
// 
// Date:	06/07/96
//
// Description:   This module contains a set of functions to control
//              joysticks in the game.	
//
// Side effects:
//
// Class:
//
// Function:
//		BOOL YBSetUpJoyStick(HWND win);
//		void YBReleaseJoystick(void);
//		BOOL YBJoyMoveHandler(void);
//		BOOL YBGetDefaultJoyPos(void);
// 
// Notes:
//
// Update:
//
// Date			Name			Description
// ==================================================================
//
//*******************************************************************

#include <windows.h>
#include <stdio.h>

#include "ybreg.h"
#include "byglobal.h"
#include "global.h"

// This is the structure of information about GoMan95 
// in the system database.
// --------------------------------------------------
// Main RegKey: 47TEK,INC\\WIN95GOMAN\\V1.3
// SubKeys    :
//				[USER0]
//				[.....]
//				[USER9]
//				[SYSTEM] 
// Data structures:  
//		[USER?]
//			name	ascii
//			level	word
//			score	dword
//          DWC     dword
//          sfx     dword
//          mid     dword
//          Robot    dword
//          hour    dword
//          minute  dword
//          second  dword
//		[TOP?]
//			name   ascii
//          score  dword
//	

//extern unsigned short S3Flag2[17];
//extern short SFXValue;
//extern short MidValue;
//extern int   level;
//extern unsigned short RobotStatus[5];
//extern unsigned char Hours;
//extern unsigned char Minutes;
//extern unsigned char Seconds;

//long int OverallScore;

unsigned short OptOFlag[17];
unsigned short OptIFlag[17];

static char MainRegKey[] = "47TEK,INC.\\WIN95GOMAN\\";
static char UserKeys[10][6] = 
{
	"USER0",
	"USER1",
	"USER2",
	"USER3",
	"USER4",
	"USER5",
	"USER6",
	"USER7",
	"USER8",
	"USER9"
};

static char TopUser[3][5] =
{
    "TOP1",
    "TOP2",
    "TOP3"
};

char SystemKey[] = "SYSTEM";

USERREC urec[10];
TOPREC  top3[3];
TOPSTRREC  tmp3[3];
short     RankIdx;
long int  RankScore;

//****************************************************************************
// Name:	BOOL YBRegisterGame(char newver[])
//
// Description:	This function creates main key and its subkeys for GOMAN 
//              and initializes value for subkeys.  These keys are actually
//              variables which contain information about user records and
//              system information.  These keys are stored in Windows system
//              database.  The information included are:
//              game name, level, score, sound volume, midi volume, detail &
//              difficulty level, 10 user records (name, score, time).
//
// Arguments:	char newver[] ... version of this game
//
// Return:		BOOL 
//				
// Side effects:
//             If a user knows how to change contents in the register 
//             database, then he will be able to change the above 
//             information.
//
// Notes:
//
// Known restrictions:
// 
// Update:
// Date			Name			Description
// ===========================================================================
//
//****************************************************************************
BOOL BYRegisterGame(char newver[])
{
	HKEY hMainKey, hKey;
	long retval;
	DWORD value = 0;
	int i;
	char fullkey[127];
	char SubKey[127];

	strcpy(fullkey, MainRegKey);
	strcat(fullkey, newver);

	retval=RegCreateKeyEx(HKEY_CURRENT_USER, fullkey, 0, NULL, 
				REG_OPTION_VOLATILE, KEY_SET_VALUE, NULL, &hMainKey, NULL);
	if (retval==ERROR_SUCCESS) {
		for (i=0; i<10; i++) {
			strcpy(SubKey, fullkey);
			strcat(SubKey, "\\");
			strcat(SubKey, UserKeys[i]);
	        if (RegCreateKeyEx(HKEY_CURRENT_USER, SubKey, 0, NULL, 
	            REG_OPTION_VOLATILE, KEY_SET_VALUE, NULL, &hKey, NULL)
	            ==ERROR_SUCCESS) 
	        {
				RegSetValueEx(hKey, "name", 0, REG_SZ, (PBYTE)"", 1);
				RegSetValueEx(hKey, "level", 0, REG_DWORD, 
								(PBYTE)&value, sizeof(DWORD));
				RegSetValueEx(hKey, "score", 0, REG_DWORD, 
								(PBYTE)&value, sizeof(DWORD));
                RegSetValueEx(hKey, "DWC", 0, REG_DWORD,
                                (PBYTE)&value, sizeof(DWORD));
                RegSetValueEx(hKey, "sfx", 0, REG_DWORD,
                                (PBYTE)&value, sizeof(DWORD));
                RegSetValueEx(hKey, "mid", 0, REG_DWORD,
                                (PBYTE)&value, sizeof(DWORD));
                RegSetValueEx(hKey, "Robot", 0, REG_DWORD,
                                (PBYTE)&value, sizeof(DWORD));
                RegSetValueEx(hKey, "hur", 0, REG_DWORD,
                                (PBYTE)&value, sizeof(DWORD));
                RegSetValueEx(hKey, "min", 0, REG_DWORD,
                                (PBYTE)&value, sizeof(DWORD));
                RegSetValueEx(hKey, "sec", 0, REG_DWORD,
                                (PBYTE)&value, sizeof(DWORD));
                                
				RegCloseKey(hKey);
			}
		} // end of for "user record" loop
        for (i=0; i<3; i++) {
			strcpy(SubKey, fullkey);
			strcat(SubKey, "\\");
			strcat(SubKey, TopUser[i]);
	        if (RegCreateKeyEx(HKEY_CURRENT_USER, SubKey, 0, NULL, 
	            REG_OPTION_VOLATILE, KEY_SET_VALUE, NULL, &hKey, NULL)
	            ==ERROR_SUCCESS) 
	        {
				RegSetValueEx(hKey, "name", 0, REG_SZ, (PBYTE)"", 1);
				RegSetValueEx(hKey, "score", 0, REG_DWORD, 
								(PBYTE)&value, sizeof(DWORD));
                RegSetValueEx(hKey, "hur", 0, REG_DWORD,
                                (PBYTE)&value, sizeof(DWORD));
                RegSetValueEx(hKey, "min", 0, REG_DWORD,
                                (PBYTE)&value, sizeof(DWORD));
                RegSetValueEx(hKey, "sec", 0, REG_DWORD,
                                (PBYTE)&value, sizeof(DWORD));
				RegCloseKey(hKey);
			}
        } // end of for "top 3 record" loop
		RegCloseKey(hMainKey);
		return TRUE;
	} else
		return FALSE;

}

//****************************************************************************
// Name:	BOOL YBTestRegisterOrNot(char newver[])
//
// Description:	This function tests to see if we install the same game
//              before by trying to open a specified subkey, thus this will
//              also test the version of the game.
//
// Arguments:	char newver[] ... version of this game
//
// Return:		BOOL = TRUE ... yes, registered before.
//				
// Side effects:
//
// Notes:
//
// Known restrictions:
// 
// Update:
// Date			Name			Description
// ===========================================================================
//
//****************************************************************************
BOOL BYTestRegisterOrNot(char newver[])
{
	HKEY hKey;
	char fullkey[127];

	strcpy(fullkey, MainRegKey);
	strcat(fullkey, newver);
	strcat(fullkey, "\\TOP1");

	if (RegOpenKeyEx(HKEY_CURRENT_USER, fullkey, 0, 
		KEY_QUERY_VALUE, &hKey)==ERROR_SUCCESS) {
		RegCloseKey(hKey);
		return TRUE;
	} else
		return FALSE;
}

//****************************************************************************
// Name:	BOOL YBLoadUserRecord(short i, char newver[])
//
// Description:	This function load a user record from the system database,
//              it assumes that we register our game already, or get FALSE
//
// Arguments:	short i ... index of user records
//             char newver[] ... version of this game
//
// Return:		BOOL = TRUE ... load successfully.
//				
// Side effects:
//
// Notes:
//
// Known restrictions:
// 
// Update:
// Date			Name			Description
// ===========================================================================
//
//****************************************************************************
BOOL YBLoadUserRecord(short i, char newver[])
{
	int   idx, ii;
	char  SubKey[127], RegName[127], fullkey[127];
	HKEY  hKey;
	DWORD RegLevel, RegScore, RegDWC, RegSfx, RegMid, RegRobot;
    DWORD RegHour, RegMinute, RegSecond;
	DWORD NameSize  = 127;
	DWORD DWSize = 4;

	strcpy(fullkey, MainRegKey);
	strcat(fullkey, newver);

	idx = i-1;
	if (idx>9 || idx < 0)
		return FALSE;
	else {
		strcpy(SubKey, fullkey);
		strcat(SubKey, "\\");
		strcat(SubKey, UserKeys[idx]);
		if (RegOpenKeyEx(HKEY_CURRENT_USER, SubKey, 0, 
			KEY_QUERY_VALUE, &hKey)==ERROR_SUCCESS) {

			RegQueryValueEx(hKey, "name", NULL, NULL, 
			 				 (PBYTE)&RegName, &NameSize);
			RegQueryValueEx(hKey, "level", NULL, NULL, 
			 				 (PBYTE)&RegLevel, &DWSize);
			RegQueryValueEx(hKey, "score", NULL, NULL, 
			 				 (PBYTE)&RegScore, &DWSize);
			RegQueryValueEx(hKey, "DWC", NULL, NULL, 
			 				 (PBYTE)&RegDWC, &DWSize);
			RegQueryValueEx(hKey, "sfx", NULL, NULL, 
			 				 (PBYTE)&RegSfx, &DWSize);
			RegQueryValueEx(hKey, "mid", NULL, NULL, 
			 				 (PBYTE)&RegMid, &DWSize);
			RegQueryValueEx(hKey, "Robot", NULL, NULL, 
			 				 (PBYTE)&RegRobot, &DWSize);
			RegQueryValueEx(hKey, "hur", NULL, NULL, 
			 				 (PBYTE)&RegHour, &DWSize);
			RegQueryValueEx(hKey, "min", NULL, NULL, 
			 				 (PBYTE)&RegMinute, &DWSize);
			RegQueryValueEx(hKey, "sec", NULL, NULL, 
			 				 (PBYTE)&RegSecond, &DWSize);

			strcpy(urec[idx].name, RegName);
			urec[idx].level = (short) RegLevel;
			urec[idx].score = (int) RegScore;
            urec[idx].DWC   = (short) RegDWC;
            urec[idx].sfx   = (short) RegSfx;
            urec[idx].mid   = (short) RegMid;
            urec[idx].mch   = (short) RegRobot;
            urec[idx].hour  = (short) RegHour;
            urec[idx].minute = (short) RegMinute;
            urec[idx].second = (short) RegSecond;
			RegCloseKey(hKey);

            for (ii=0; ii<=5; ii++) {
                if (urec[idx].DWC & (1<<ii)) {
                    OptIFlag[ii] = 1;
                } else 
                    OptIFlag[ii] = 0;
            }
            for (ii=6; ii<=8; ii++) {
                if (urec[idx].DWC & (1<<ii)) {
                    OptIFlag[ii+2] = 1;
                } else
                    OptIFlag[ii+2] = 0;
            }

			return TRUE;
		} else 
			return FALSE;
	}
}

//****************************************************************************
// Name:	void YBConfirmLoad(short idx)
//
// Description:	This function is called after a game player decides to
//              load that record from the system database to different global
//              variables, and constructs Robot status from a Robot variable. If
//              the user record is empty, it will not load the record.  
//
// Arguments:	short idx ... index of user records
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
// ===========================================================================
//
//****************************************************************************
void YBConfirmLoad(short idx)
{
    if (idx>9 || idx <0)
        return;

    if (!strcmp(urec[(idx-1)].name, ""))
        return;

    GameStates.CurrentLevel = urec[(idx-1)].level;
    SFXValue = urec[(idx-1)].sfx;
    MidValue = urec[(idx-1)].mid;
    GameStates.Score = urec[(idx-1)].score;
    GameStates.Hours = (unsigned char)urec[(idx-1)].hour;
    GameStates.Minutes = (unsigned char)urec[(idx-1)].minute;
    GameStates.Seconds = (unsigned char)urec[(idx-1)].second;
    YBRegRobotToRobotStatus(idx);
}

//****************************************************************************
// Name:	void YBRegRobotToRobotStatus(short idx)
//
// Description:	This function converts the value of Robot's variable in a
//              user record to Robot status of the particular game session.
//
// Arguments:	short idx ... index of user records
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
// ===========================================================================
//
//****************************************************************************
void YBRegRobotToRobotStatus(short idx)
{
    unsigned short RegRobot;
    
    RegRobot = urec[(idx-1)].mch; 
    GameStates.IsRobotDead[0] = ((RegRobot & 0x10) >> 4); 
    GameStates.IsRobotDead[1] = ((RegRobot & 0x8) >> 3); 
    GameStates.IsRobotDead[2] = ((RegRobot & 0x4) >> 2); 
    GameStates.IsRobotDead[3] = ((RegRobot & 0x2) >> 1); 
    GameStates.IsRobotDead[4] = ((RegRobot & 0x1)); 
}

//****************************************************************************
// Name:	void YBRegRobotToRobotStatus(short idx)
//
// Description:	This function converts Robot status of the current game
//              to the value of Robot's variable in a user record.
//
// Arguments:	short idx ... index of user records
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
// ===========================================================================
//
//****************************************************************************
void YBRobotStatusToRegRobot(short idx)
{
    unsigned short RegRobot;

    RegRobot  = 0;
    RegRobot  = ((GameStates.IsRobotDead[0]&0xff) << 4);
    RegRobot |= ((GameStates.IsRobotDead[1]&0xff) << 3);
    RegRobot |= ((GameStates.IsRobotDead[2]&0xff) << 2);
    RegRobot |= ((GameStates.IsRobotDead[3]&0xff) << 1);
    RegRobot |= ((GameStates.IsRobotDead[4]&0xff));
    urec[idx].mch = RegRobot;
}

//****************************************************************************
// Name: BOOL YBSaveUserRecord(short i, char newver[])
//
// Description:	This function saves a user record to the system's database,
//              if not registered, return FALSE.
//
// Arguments:	short i ... index of user records
//             char newver[] ... version of the game
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
// ===========================================================================
//
//****************************************************************************
BOOL YBSaveUserRecord(short i, char newver[])
{
	int   idx, ii;
	char  SubKey[127], RegName[127], fullkey[127];
	HKEY  hKey;
	DWORD RegLevel, RegScore, RegDWC, RegSfx, RegMid, RegRobot;
    DWORD RegHour, RegMinute, RegSecond;
	DWORD NameSize  = 127;
	DWORD DWSize = 4;

	strcpy(fullkey, MainRegKey);
	strcat(fullkey, newver);

	idx = i-1;
	if (idx>9 || idx < 0)
		return FALSE;
	else {
        urec[idx].DWC = 0;

        for (ii=0; ii<=5; ii++) {
            if (OptOFlag[ii])
                urec[idx].DWC |= (1<<ii);
        }

        for (ii=8; ii<=10; ii++) {
            if (OptOFlag[ii])
                urec[idx].DWC |= (1<<(ii-2));
        }

        
        urec[idx].level = GameStates.CurrentLevel;        
        urec[idx].sfx = SFXValue;
        urec[idx].mid = MidValue;
        urec[idx].score = GameStates.Score;
        urec[idx].hour = GameStates.Hours;
        urec[idx].minute = GameStates.Minutes;
        urec[idx].second = GameStates.Seconds;
        YBRobotStatusToRegRobot((short)idx);
        RegRobot = urec[idx].mch;

		strcpy(SubKey, fullkey);
		strcat(SubKey, "\\");
		strcat(SubKey, UserKeys[idx]);
		if (RegOpenKeyEx(HKEY_CURRENT_USER, SubKey, 0, 
			KEY_SET_VALUE, &hKey)==ERROR_SUCCESS) {

			strcpy(RegName, urec[idx].name);
			RegLevel = urec[idx].level;
			RegScore = urec[idx].score;
            RegDWC   = urec[idx].DWC;
            RegSfx   = urec[idx].sfx;
            RegMid   = urec[idx].mid;
            RegHour  = urec[idx].hour;
            RegMinute = urec[idx].minute;
            RegSecond = urec[idx].second;

			RegSetValueEx(hKey, "name", 0, REG_SZ, (PBYTE)&RegName, sizeof(RegName)+1);
			RegSetValueEx(hKey, "level", 0, REG_DWORD, 
			                    (PBYTE)&RegLevel, sizeof(DWORD));
			RegSetValueEx(hKey, "score", 0, REG_DWORD, 
			                    (PBYTE)&RegScore, sizeof(DWORD));
			RegSetValueEx(hKey, "DWC", 0, REG_DWORD, 
			                    (PBYTE)&RegDWC, sizeof(DWORD));
			RegSetValueEx(hKey, "sfx", 0, REG_DWORD, 
			                    (PBYTE)&RegSfx, sizeof(DWORD));
			RegSetValueEx(hKey, "mid", 0, REG_DWORD, 
			                    (PBYTE)&RegMid, sizeof(DWORD));
			RegSetValueEx(hKey, "Robot", 0, REG_DWORD, 
			                    (PBYTE)&RegRobot, sizeof(DWORD));
			RegSetValueEx(hKey, "hur", 0, REG_DWORD, 
			                    (PBYTE)&RegHour, sizeof(DWORD));
			RegSetValueEx(hKey, "min", 0, REG_DWORD, 
			                    (PBYTE)&RegMinute, sizeof(DWORD));
			RegSetValueEx(hKey, "sec", 0, REG_DWORD, 
			                    (PBYTE)&RegSecond, sizeof(DWORD));
			RegCloseKey(hKey);
			return TRUE;
		} else 
			return FALSE;
	}
}

//****************************************************************************
// Name: BOOL YBLoadAllUserRecord(char newver[])
//
// Description:	This function loads all the ten user records from the
//              system database.
//
// Arguments:	char newver[] ... version of the game
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
// ===========================================================================
//
//****************************************************************************
BOOL YBLoadAllUserRecord(char newver[])
{
	short i;

	for (i=1; i<=10; i++) {
		if (!YBLoadUserRecord(i, newver))
			return FALSE;
	}
    RankIdx = 99;
    RankScore = 0;
	return TRUE;
}

//****************************************************************************
// Name: BOOL YBSaveAllUserRecord(char newver[])
//
// Description:	This function saves all the ten user records to the
//              system database.
//
// Arguments:	char newver[] ... version of the game
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
// ===========================================================================
//
//****************************************************************************
BOOL YBSaveAllUserRecord(char newver[])
{
	short i;

	for (i=1; i<=10; i++) {
		if (!YBSaveUserRecord(i, newver))
			return FALSE;
	}
	return TRUE;
}

//****************************************************************************
// Name: BOOL YBIfRMInstalled(void)
//
// Description:	This function checks to see if RM's DLL is installed or not.
//
// Arguments:	void
//
// Return:		BOOL 
//				
// Side effects:
//
// Notes:
//       Since RenderMorphics (RM)'s new DLL may be installed with a new
//       version number, you need to make sure that the RMKey1 is right for
//       the latest RM's DLL.
// 
// Known restrictions:
// 
// Update:
// Date			Name			Description
// ===========================================================================
//
//****************************************************************************
BOOL YBIfRMInstalled(void)
{
	char RMKey1[] = "SOFTWARE\\MICROSOFT\\REALITY LAB\\2.0";
	char SystemKey[127];
	char version[127];
	HKEY hKey;
	DWORD dwSize = 100;

	strcpy(SystemKey, RMKey1);
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, SystemKey, 0, 
            KEY_QUERY_VALUE, &hKey)==ERROR_SUCCESS) {

        RegQueryValueEx(hKey, "Version", NULL, NULL, 
                         (PBYTE)&version, &dwSize);
		RegCloseKey(hKey);
		strupr(version);
		if (!strcmp(version, "BUILD 21"))
			return TRUE;
	}
	return FALSE;
}

//****************************************************************************
// Name: BOOL YBDeleteValue(char *SubKey, char *ValueName, char newver[])
//
// Description:	This function deletes variables of the specified subkey
//
// Arguments:	char *SubKey  ... subkey
//             char *ValueName ... variable defined under that subkey.
//             char newver[] ... version of the game
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
// ===========================================================================
//
//****************************************************************************
BOOL YBDeleteValue(char *SubKey, char *ValueName, char newver[])
{
	char FullKey[127];
	HKEY hKey;

	if (!strcmp(SubKey, "")) {
		strcpy(FullKey, MainRegKey);
		strcat(FullKey, newver);
	} else {
		strcpy(FullKey, MainRegKey);
		strcat(FullKey, newver);
		strcat(FullKey, "\\");
		strcat(FullKey, SubKey);
	}

	if (RegOpenKeyEx(HKEY_CURRENT_USER, FullKey, 0, 
		KEY_SET_VALUE, &hKey)==ERROR_SUCCESS) {
		if (RegDeleteValue(hKey, ValueName)==ERROR_SUCCESS) {
			RegCloseKey(hKey);
			return TRUE;
		}
		RegCloseKey(hKey);
	}
	return FALSE;
}

// ========================================================== ABOUT TOP 3
//****************************************************************************
// Name: BOOL YBLoadOneTopRecord(short i, char newver[])
//
// Description:	This function load a top user record from the system 
//             database, it assumes that we register our game already, or 
//             get FALSE.
//
// Arguments:	short i  ... which one in the top 3 records
//             char newver[] ... version of the game
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
// ===========================================================================
//
//****************************************************************************
BOOL YBLoadOneTopRecord(short i, char newver[])
{
	int   idx;
	char  SubKey[127], RegName[127], fullkey[127];
	HKEY  hKey;
	DWORD RegScore;
    DWORD RegHour, RegMinute, RegSecond;
	DWORD NameSize  = 127;
	DWORD DWSize = 4;

	strcpy(fullkey, MainRegKey);
	strcat(fullkey, newver);

	idx = i-1;
	if (idx>3 || idx < 0)
		return FALSE;
	else {
		strcpy(SubKey, fullkey);
		strcat(SubKey, "\\");
		strcat(SubKey, TopUser[idx]);
		if (RegOpenKeyEx(HKEY_CURRENT_USER, SubKey, 0, 
			KEY_QUERY_VALUE, &hKey)==ERROR_SUCCESS) {

			RegQueryValueEx(hKey, "name", NULL, NULL, 
			 				 (PBYTE)&RegName, &NameSize);
			RegQueryValueEx(hKey, "score", NULL, NULL, 
			 				 (PBYTE)&RegScore, &DWSize);
			RegQueryValueEx(hKey, "hur", NULL, NULL, 
			 				 (PBYTE)&RegHour, &DWSize);
			RegQueryValueEx(hKey, "min", NULL, NULL, 
			 				 (PBYTE)&RegMinute, &DWSize);
			RegQueryValueEx(hKey, "sec", NULL, NULL, 
			 				 (PBYTE)&RegSecond, &DWSize);
			strcpy(top3[idx].name, RegName);
			top3[idx].score = (int) RegScore;
            top3[idx].hour = (short) RegHour;
            top3[idx].minute = (short) RegMinute;
            top3[idx].second = (short) RegSecond;
			RegCloseKey(hKey);

			return TRUE;
		} else 
			return FALSE;
	}
}
 
//****************************************************************************
// Name: BOOL YBLoadAllTopRecord(char newver[])
//
// Description:	This function loads 3 top user records from the system
//              database, and then sort them according to their score value.
//
// Arguments:	char newver[] ... version of the game
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
// ===========================================================================
//
//****************************************************************************
BOOL YBLoadAllTopRecord(char newver[])
{
    short i, j;
    char tempname[127];
    DWORD tempscore;
    short temphour, tempminute, tempsecond;

    for (i=1; i<=3; i++) {
        if (!YBLoadOneTopRecord(i, newver))
            return FALSE;
    }
    for (i=0; i<2; i++) 
        for (j=i+1; j<3; j++) {
            if (top3[i].score<top3[j].score) {
                strcpy(tempname, top3[j].name);
                tempscore = top3[j].score;
                temphour = top3[j].hour;
                tempminute = top3[j].minute;
                tempsecond = top3[j].second;
                strcpy(top3[j].name, top3[i].name);
                strcpy(top3[i].name, tempname);
                top3[j].score = top3[i].score;
                top3[j].hour  = top3[i].hour;
                top3[j].minute = top3[i].minute;
                top3[j].second = top3[i].second;
                top3[i].score = tempscore;
                top3[i].hour  = temphour;
                top3[i].minute = tempminute;
                top3[i].second = tempsecond;
            }
        }
    for (i=0; i<3; i++) {
        strcpy(tmp3[i].name, top3[i].name);
        sprintf(tempname, "%d", top3[i].score);
        strcpy(tmp3[i].score, tempname);
        sprintf(tempname, "%02d:%02d:%02d", top3[i].hour, top3[i].minute, top3[i].second);
        strcpy(tmp3[i].time, tempname);
    }
    strcpy(tmp3[0].No, "1.");
    strcpy(tmp3[1].No, "2.");
    strcpy(tmp3[2].No, "3.");
    return TRUE;
}

//****************************************************************************
// Name: BOOL YBSaveTopRecord(short i, char newver[])
//
// Description:	This function saves a top user record in the system's
//              database. If not registered, return FALSE.
//
// Arguments:	short i ... index of the records
//             char newver[] ... version of the game.
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
// ===========================================================================
//
//****************************************************************************
BOOL YBSaveTopRecord(short i, char newver[])
{
	int   idx;
	char  SubKey[127], RegName[127], fullkey[127];
	HKEY  hKey;
	DWORD RegScore;
    DWORD RegHour, RegMinute, RegSecond;
	DWORD NameSize  = 127;
	DWORD DWSize = 4;

	strcpy(fullkey, MainRegKey);
	strcat(fullkey, newver);

	idx = i-1;
	if (idx>3 || idx < 0)
		return FALSE;
	else {
		strcpy(SubKey, fullkey);
		strcat(SubKey, "\\");
		strcat(SubKey, TopUser[idx]);
		if (RegOpenKeyEx(HKEY_CURRENT_USER, SubKey, 0, 
			KEY_SET_VALUE, &hKey)==ERROR_SUCCESS) {

			strcpy(RegName, top3[idx].name);
			RegScore = top3[idx].score;
            RegHour  = top3[idx].hour;
            RegMinute = top3[idx].minute;
            RegSecond = top3[idx].second;
			RegSetValueEx(hKey, "name", 0, REG_SZ, (PBYTE)&RegName, sizeof(RegName)+1);
			RegSetValueEx(hKey, "score", 0, REG_DWORD, 
			                    (PBYTE)&RegScore, sizeof(DWORD));
			RegSetValueEx(hKey, "hur", 0, REG_DWORD, 
			                    (PBYTE)&RegHour, sizeof(DWORD));
			RegSetValueEx(hKey, "min", 0, REG_DWORD, 
			                    (PBYTE)&RegMinute, sizeof(DWORD));
			RegSetValueEx(hKey, "sec", 0, REG_DWORD, 
			                    (PBYTE)&RegSecond, sizeof(DWORD));
			RegCloseKey(hKey);
			return TRUE;
		} else 
			return FALSE;
	}
}

//****************************************************************************
// Name: BOOL YBSaveAllTopRecord(char newver[])
//
// Description:	This function saves 3 top user records in the system's
//              database. If not registered, return FALSE.
//
// Arguments:	 char newver[] ... version of the game.
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
// ===========================================================================
//
//****************************************************************************
BOOL YBSaveAllTopRecord(char newver[])
{
	short i;

	for (i=1; i<=3; i++) {
		if (!YBSaveTopRecord(i, newver))
			return FALSE;
	}
	return TRUE;
}

//****************************************************************************
// Name: short YBReachTop3(long int s)
//
// Description:	This function tests to see if the input score 's' reaches
//              the top 3 score.  If yes, reorganize the order, return index
//              to indicate where the new record should be placed, or return
//              0 when the score 's' is smaller than any of these scores.
//
// Arguments:	long int s ... score to be tested.
//            
// Return:		short ... where to put the new record in these three positions.
//				
// Side effects:
//
// Notes:
//
// Known restrictions:
// 
// Update:
// Date			Name			Description
// ===========================================================================
//
//****************************************************************************
short YBReachTop3(long int s)
{
    short i, j;

    j = 0;
    for (i=0; i<3; i++) {
        if (s>top3[i].score) {
            RankIdx = i;
            RankScore = s;
            j = i+1;
            break;
        }
    }
    if (j>0) {
        for (i=1; i>=RankIdx; i--) {
            strcpy(tmp3[i+1].name, tmp3[i].name);
            strcpy(tmp3[i+1].score, tmp3[i].score);
            strcpy(tmp3[i+1].time, tmp3[i].time);
        }
        sprintf(tmp3[RankIdx].score, "%d", s);
    }
    return j;
}

//****************************************************************************
// Name: void YBConfirmTopValue(void)
//
// Description:	This function copies top 3 records to their global variables
//              in order to save them later.
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
// ===========================================================================
//
//****************************************************************************
void YBConfirmTopValue(void)
{
    short i;

    for (i=1; i>=RankIdx; i--) {
        strcpy(top3[i+1].name, top3[i].name);
        top3[i+1].score = top3[i].score;
        top3[i+1].hour  = top3[i].hour;
        top3[i+1].minute = top3[i].minute;
        top3[i+1].second = top3[i].second;
    }
    strcpy(top3[RankIdx].name, tmp3[RankIdx].name);
    top3[RankIdx].score = RankScore;
    top3[RankIdx].hour = GameStates.Hours;
    top3[RankIdx].minute = GameStates.Minutes;
    top3[RankIdx].second = GameStates.Seconds;
}

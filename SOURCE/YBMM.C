//****************************************************************************
// ybmm.c
//
// Copyright 1996 by 47-TEK, INC.  All rights reserved.
//
// Author:	Bo Yuan
// 
// Date:	06/07/96
//
// Description:   This module contains a set of functions about multimedia
//              play in the game.
//
// Side effects:
//
// Class:
//
// Function:
//    BOOL YBGetAllPath(HINSTANCE hInst, short mode);
//    void YBReportError(int i, char *inputstr);
//    BOOL YBGetExeFullPathnName 
//          (HINSTANCE hInst, LPSTR FullPath, LPSTR ExeName);
//    BOOL YBGetFullFileName 
//          (LPSTR FullPath, LPSTR FileName, LPSTR fname, LPSTR Ext);
//    void YBGetFilePath 
//          (LPSTR lpApplicationName, LPSTR lpFileType, LPSTR lpDefaultPath,
//    LPSTR lpReturnedFullPath, int nMaxReturnSize, LPSTR lpIniFileName);
//    void YBPlayMidi(LPSTR MidiName, HWND hWnd);
//    void YBStopMidi(LPSTR MidiName, HWND hWnd);
//    void YBCleanUpMidi (HWND hWnd);
//    HWND PlayAVI 
//          (HWND hWnd, LPSTR AviName, LPSTR AliaName, int WinNo, RECT rt);
//    void CloseAVI(HWND hWnd, LPSTR AliaName);
//    void YBPlayWave(LPSTR WaveName, HWND hWnd);
//    void YBStopWave(LPSTR MidiName, HWND hWnd);
//    void YBCleanUpWave (HWND hWnd);
//    BOOL YBGetAllAbsPath(HINSTANCE hInst, short mode, char newver[]);
//    BOOL YBGetGMPath(short vmode, char newver[]);
// 
// Notes:
//
// Update:
//
// Date			Name			Description
// ===========================================================================
//
//****************************************************************************

#include "ybmm.h"  // YB multimedia header file
#include "byglobal.h"
#include "d3dappi.h"

// Local constants
#define ERR_READFAIL    1
#define MAX_PATH_LENGTH 127
#define MAIN_X	0
#define MAIN_Y	0

// Local variables
char ExePath[127];
char HDPath[127];
char MidPath[127];
char WavPath[127];
char AviPath[127];
char BmpPath[127];
char WrapBmpPath[127];
char XafPath[127];
char DatPath[127];
char IniFile[127];
char ExeName[127];
char CurMidName[256];
char CurWavName[256];
char WrapSnd1[127];
char WrapSnd2[127];
char CDDriveLetter=0;
BOOL bMidiFlag;


char GetCDROMDriveLetter()
{
	int i;
	char p[5];
	char Name[]="c:\\DAT\\license.txt";
	FILE *shithead;

	p[1]=':';
	p[2]=0;
	for (i=0; i<26; i++)
	{
		p[0] = 'A'+i;
		if (GetDriveType(p)==DRIVE_CDROM)
		{
			Name[0]=p[0];
			shithead=fopen(Name,"r");
			if(shithead)
			{
				fclose(shithead);
				return p[0];
			}
		}
	}
	return 0;
}


// This function is not called in the game
BOOL YBPlayFromHD(void)
{
	char DXKey1[] = "47TEK,INC.\\WIN95GOMAN\\V1.5";
	char SystemKey[127];
	char pmode[127];
	HKEY hKey;
	DWORD dwSize = 100;

	strcpy(SystemKey, DXKey1);
	if (RegOpenKeyEx(HKEY_CURRENT_USER, SystemKey, 0,
            KEY_QUERY_VALUE, &hKey)==ERROR_SUCCESS) {

        RegQueryValueEx(hKey, "PLAYHD", NULL, NULL,
                         (PBYTE)&pmode, &dwSize);
		RegCloseKey(hKey);
		strupr(pmode);
		if (!strcmp(pmode, "YES"))
		    return TRUE;
        else
            return FALSE;
	}
	return FALSE;
}

//****************************************************************************
// Name:	BOOL YBGetGMPath(short vmode, char newver[])
//
// Description:   This function gets the game path from the system database.
//
// Arguments:	short vmode ... video mode
//             char newver[] ... version of the game
//
// Return:	BOOL
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
BOOL YBGetGMPath(short vmode, char newver[])
{
   char DXKey1[] = "47TEK,INC.\\WIN95GOMAN\\";
   char SystemKey[127];
   char gpath[127];
   HKEY hKey;
   DWORD dwSize = 100;

	strcpy(SystemKey, DXKey1);
	strcat(SystemKey, newver);

	if (RegOpenKeyEx(HKEY_CURRENT_USER, SystemKey, 0,
            KEY_QUERY_VALUE, &hKey)==ERROR_SUCCESS) 
   {
		if (vmode==320)
			RegQueryValueEx(hKey, "GMPATH", NULL, NULL,
							 (PBYTE)&gpath, &dwSize);
		else
			RegQueryValueEx(hKey, "GM640PATH", NULL, NULL,
							 (PBYTE)&gpath, &dwSize);
		RegCloseKey(hKey);
        strcpy(ExePath, gpath);
		return TRUE;
	}
	return FALSE;
}

//****************************************************************************
// Name:	BOOL YBGetAllPath(HINSTANCE hInst, short mode)
//
// Description:   This function is called when a user wants to play the game
//              from the HD.  It finds out paths for different kinds of 
//              resource files in the game by first getting the application's
//              path and name, and then reading the INI file and constructing
//              paths of other resource files.
//
// Arguments:	HINSTANCE hInst ... application's instance handler
//             short mode ... video mode
//
// Return:	BOOL
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
BOOL YBGetAllPath(HINSTANCE hInst, short mode)
{
   MEMORYSTATUS ms;
   char *end;

	if (!YBGetExeFullPathnName(hInst, ExePath, ExeName)) {
	   YBReportError(ERR_READFAIL, ".EXE");
	   return FALSE;
	}
	if (!YBGetFullFileName(ExePath, ExeName, IniFile, ".ini")) {
	   YBReportError(ERR_READFAIL, ".INI");
	   return FALSE;
	}
	if(!YBGetFilePath("SYSPATH", "MIDS", "", MidPath, MAX_PATH_LENGTH, IniFile))
		return FALSE;

	end=strrchr(MidPath,'\\');
	if(end)
		bMidiFlag=strcmp(end,"\\NULL");
	else
		bMidiFlag=TRUE;

	if(!YBGetFilePath("SYSPATH", "AVIS", "", AviPath, MAX_PATH_LENGTH, IniFile))
		return FALSE;
	if(!YBGetFilePath("SYSPATH", "XAFS", "", XafPath, MAX_PATH_LENGTH, IniFile))
		return FALSE;
#ifdef FREEWARE
	if(!YBGetFilePath("SYSPATH", "DATS", "", DatPath, MAX_PATH_LENGTH, IniFile))
		return FALSE;
#else
	if(!YBGetFilePath("SYSPATH", "MaximumSewage", "", DatPath, MAX_PATH_LENGTH, IniFile))
		return FALSE;
	if(DatPath[0]==0)
	{
		strcpy(DatPath,"d:\\dat");
		DatPath[0]=CDDriveLetter;
	}
#endif
	if(!YBGetFilePath("SYSPATH", "640BMPS", "", WrapBmpPath, MAX_PATH_LENGTH, IniFile))
		return FALSE;
	if(!BYOBGetBitmapPath(mode))
		return FALSE;
	
#ifdef FREEWARE	
	if(!YBGetFilePath("SYSPATH", "8WAVS", "", WavPath, MAX_PATH_LENGTH, IniFile))
		return FALSE;
#else //FREEWARE
	GlobalMemoryStatus(&ms);
	if (ms.dwTotalPhys>=20000000)
	{
		if(!YBGetFilePath("SYSPATH", "16WAVS", "", WavPath, MAX_PATH_LENGTH, IniFile))
		   if(!YBGetFilePath("SYSPATH", "8WAVS", "", WavPath, MAX_PATH_LENGTH, IniFile))
			   return FALSE;
	}
	else
	{
		if(!YBGetFilePath("SYSPATH", "8WAVS", "", WavPath, MAX_PATH_LENGTH, IniFile))
		   if(!YBGetFilePath("SYSPATH", "16WAVS", "", WavPath, MAX_PATH_LENGTH, IniFile))
			   return FALSE;
	}
#endif //FREEWARE
	strcpy(WrapSnd1, WavPath);
	strcat(WrapSnd1, "\\wr101.wav");

	return TRUE;
}

BOOL BYOBGetBitmapPath(short mode)
{
	switch(mode)
	{
	case 640:
		if (VM_BPP3D==16)
		{
			// Tim Stretch: this case is inserted for the stretch 16 bit stretched files
			if (sStretch.bWillStretch)
			{
				if(!YBGetFilePath("SYSPATH", "16GOART320", "", BmpPath, MAX_PATH_LENGTH, IniFile))
					return FALSE;
				if(!YBGetFilePath("SYSPATH", "HD640", "", HDPath, MAX_PATH_LENGTH, IniFile))
					return FALSE;
				break;


			}
			else
			{
				if(!YBGetFilePath("SYSPATH", "640BMPS", "", BmpPath, MAX_PATH_LENGTH, IniFile))
					return FALSE;
				if(!YBGetFilePath("SYSPATH", "HD640", "", HDPath, MAX_PATH_LENGTH, IniFile))
					return FALSE;
			}
		}
		else // now we assume it is 8 bit.
		{
			if(!YBGetFilePath("SYSPATH", "8GOART640", "", BmpPath, MAX_PATH_LENGTH, IniFile))
				return FALSE;
			if(!YBGetFilePath("SYSPATH", "HD6408", "", HDPath, MAX_PATH_LENGTH, IniFile))
				return FALSE;
		}
		break;
	case 512:
		if(!YBGetFilePath("SYSPATH", "512BMPS", "", BmpPath, MAX_PATH_LENGTH, IniFile))
			return FALSE;
		if(!YBGetFilePath("SYSPATH", "HD512", "", HDPath, MAX_PATH_LENGTH, IniFile))
			return FALSE;
		break;
	case 320:
		
		
			if(!YBGetFilePath("SYSPATH", "320BMPS", "", BmpPath, MAX_PATH_LENGTH, IniFile))
				return FALSE;
			if(!YBGetFilePath("SYSPATH", "HD320", "", HDPath, MAX_PATH_LENGTH, IniFile))
				return FALSE;
			break;
		
	}
	return TRUE;
}


//****************************************************************************
// Name:	void YBReportError(int i, char *inputstr)
//
// Description:   This function pops up a message box with different 
//              error messages based on the inputed error code and
//              information.
//
// Arguments:	error_code  ...  error code
//             inputstr    ...  information
//
// Return:	void
//				
// Side effects:
//                When it is in exclusive video mode, the message box
//                may stop the game from running, you may even not be
//                able to see the message box when it is in MODEX.
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
void YBReportError(int error_code,  // error code
                   char *inputstr)  // file name or other error message.
{
   char str[256];

   switch(error_code) 
   {
      case ERR_READFAIL:
         strcpy(str, "Cannot open the file:");
         strcat(str, inputstr);
         break;
   };
   MessageBox(NULL, str, "ERROR", MB_OK);
   return;
}

//****************************************************************************
// Name:	BOOL YBGetExeFullPathnName
//       (HINSTANCE hInst, LPSTR FullPath, LPSTR ExeName)
//
// Description:   This function gets exe name and full path through 
//              parameters ExeName and FULLPath 
//
// Arguments:	HINSTANCE hInst ... Application instance handler
//             LPSTR     FullPath ... points to FULLPath string
//             LPSTR     ExeName  ... points to ExeName string
//
// Return:	void
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
BOOL YBGetExeFullPathnName(HINSTANCE hInst,  // Application instance handler
                           LPSTR FullPath,   // points to FULLPath string
                           LPSTR ExeName)    // points to ExeName string
{         
   int i, j, k;
      
   i = GetModuleFileName(hInst, FullPath, MAX_PATH_LENGTH);

   if (i==0) 
   {
      return FALSE;
   }
   j = i;
   while (FullPath[i] != '\\') 
   {
      i--;
   }
   // Get exe name
   for (k=0; k<(j-i); k++) 
   {
      if (FullPath[k+i+1]=='.') 
      {
         ExeName[k] = '\0';
         break;
      }
      ExeName[k] = FullPath[k+i+1];
   }
   // Get exe full path
   FullPath[i] = '\0';
     
   return TRUE;
}

//****************************************************************************
// Name:	BOOL YBGetFullFileName 
//       (LPSTR FullPath, LPSTR FileName, LPSTR fname, LPSTR Ext)
//
// Description:   This function constructs a full file name (including its
//              full path), then tries to open it.
//
// Arguments:	
//             LPSTR     FullPath ... points to FULLPath string
//             LPSTR     FileName ... points to ExeName string
//             LPSTR     fname    ... final file name
//             LPSTR     Ext      ... extension of the file
//
// Return:	BOOL = TRUE ... if that file exists.
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
BOOL YBGetFullFileName 
(LPSTR FullPath, LPSTR FileName, LPSTR fname, LPSTR Ext)
{  
   FILE *fp;
         
   strcpy(fname, FullPath);
   strcat(fname, "\\");
   strcat(fname, FileName);
   strcat(fname, Ext);
   fp = fopen(fname,"r");
   if (fp==NULL)
      return FALSE;
   return TRUE;
}

//****************************************************************************
// Name:	BOOL YBGetFilePath 
//       (LPSTR lpApplicationName, LPSTR lpFileType, LPSTR lpDefaultPath,
//       LPSTR lpReturnedFullPath, int nMaxReturnSize, LPSTR lpIniFileName)
//
// Description:   This function gets the right path string for the given file
//              type defined in the application's profile (INI file)
//
// Arguments:	
//             LPSTR lpApplicationName ... points to section name
//             LPSTR lpFileType ... points to type name
//             LPSTR lpDefaultPath ... points to the default path name
//             LPSTR lpReturnedFullPath ... points to the returned full name
//             LPSTR nMaxReturnSize ... size of the return string buffer
//             LPSTR lpIniFileName ... points to the INI file name
//
// Return:	BOOL
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
BOOL YBGetFilePath 
(LPSTR lpApplicationName, LPSTR lpFileType, LPSTR lpDefaultPath,
LPSTR lpReturnedFullPath, int nMaxReturnSize, LPSTR lpIniFileName)
{
   char retpath[256];
   char *realpath;

   GetPrivateProfileString
	   (lpApplicationName, lpFileType, lpDefaultPath,
	    retpath, nMaxReturnSize, lpIniFileName);
   if(retpath[0]=='[')
   {
	   realpath=strchr(retpath,']');
	   realpath[0]=CDDriveLetter;
	   strncpy(lpReturnedFullPath, realpath, nMaxReturnSize);
	   if(!CDDriveLetter)
		   return FALSE;

   }
   else
   {
	   strncpy(lpReturnedFullPath, retpath, nMaxReturnSize);
   }
   return TRUE;
}

// not used in the game
void YBPlayMidi(LPSTR MidiName, HWND hWnd)
{
   char CmdString[256], FName[256];
   char  cReturn [256];    
   
   strcpy(FName, MidPath);
   strcat(FName, "\\");
   strcat(FName, MidiName);
   strcpy(CurMidName, FName);

   wsprintf((LPSTR)CmdString,"open %s", FName);
   mciSendString ((LPSTR)CmdString, cReturn, 256, hWnd);
   //wsprintf((LPSTR)CmdString,"play %s", FName);
   wsprintf((LPSTR)CmdString,"play %s notify", FName);
   mciSendString ((LPSTR)CmdString, cReturn, 256, hWnd);   
}

// not used in the game
void YBStopMidi(LPSTR MidiName, HWND hWnd)
{
   char CmdString[256], FName[256];
   char  cReturn [256];    
   
   strcpy(FName, MidPath);
   strcat(FName, "\\");
   strcat(FName, MidiName);

   wsprintf((LPSTR)CmdString,"stop %s", FName);
   mciSendString ((LPSTR)CmdString, cReturn, 256, hWnd); 
   wsprintf((LPSTR)CmdString,"close %s wait", FName);
   mciSendString ((LPSTR)CmdString, cReturn, 256, hWnd);   
  
}    

// not used in the game
void YBCleanUpMidi (HWND hWnd)
{
   char CmdString[256], cReturn[256];
   
   wsprintf((LPSTR)CmdString, "close %s", CurMidName);
   mciSendString ((LPSTR)CmdString, cReturn, 256, hWnd);
}

DWORD oldvol;
//****************************************************************************
// Name:	HWND PlayAVI
//       (HWND hWnd, LPSTR AviName, LPSTR AliaName, int WinNo, RECT rt)
//
// Description:   This function builds the full name for the AVI file,
//              builds MCI strings for open and play an AVI file, opens
//              an AVI window in the desired place, then play it.
//
// Arguments:	
//             HWND  hWnd ... handler of the window
//             LPSTR AviName ... name of the AVI file
//             int WinNo ... controls AVI window type (full screen or not)
//             RECT rt ... defines the AVI window area
//
// Return:	HWND ... handler of the AVI window
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
HWND PlayAVI
(HWND hWnd, LPSTR AviName, LPSTR AliaName, int WinNo, RECT rt)
{           

	DWORD dw;
	HWND  hAvi=NULL;
	char  CmdString[100], Cwindow[100], Cstatus[100], Cplay[100];
	char  cReturn[256], FName[100];
   int   x0, y0;
   RECT  r;

	waveOutGetVolume((HWAVEOUT)1, &oldvol);
	waveOutSetVolume((HWAVEOUT)1, 0x8080);

	strcpy(FName, AviPath);
	strcat(FName, "\\");                               
	strcat(FName, AviName);
                            
	wsprintf((LPSTR)CmdString, 
	"open %s alias %s style child parent %d", FName, AliaName, hWnd);
	wsprintf((LPSTR)Cwindow, "window %s", AliaName);   
	wsprintf((LPSTR)Cstatus, "status %s window handle", AliaName);   
	wsprintf((LPSTR)Cplay, "play %s notify", AliaName);   
        
	if (mciSendString((LPSTR)CmdString, NULL, 0, NULL) == 0) {
   
		mciSendString((LPSTR)Cwindow, cReturn, 128, hWnd);

		if ((dw = mciSendString((LPSTR)Cstatus, 
			(LPSTR)CmdString, sizeof(CmdString),NULL)) == 0L)
			hAvi = (HWND)atoi(CmdString); 
   
        //x0 = (GetSystemMetrics(SM_CXSCREEN)-MAIN_W)/2;
		//y0 = (GetSystemMetrics(SM_CYSCREEN)-MAIN_H)/2;

		GetClientRect(hWnd, &r);
		
		if (WinNo==0)
		{
			x0 = (r.right - 512)/2;
			y0 = (r.bottom - 384)/2;
			MoveWindow(hAvi, x0, y0, 512, 384, TRUE);
		}
		else if (WinNo==2)
		{
			r.left = 10;
			r.top = 15;
			r.right = 320;
			r.bottom = 240;
			MoveWindow(hAvi, r.left, r.top, r.right, r.bottom, TRUE);
		}
		else
		{
			MoveWindow(hAvi, rt.left, rt.top, rt.right, rt.bottom, TRUE);
		}
      	//MoveWindow(hAvi, 0, 0, MAIN_W, MAIN_H, TRUE);

		mciSendString((LPSTR)Cplay, cReturn, 128, hWnd);
   }       

   return (hAvi);                          
}

//****************************************************************************
// Name:	void CloseAVI(HWND hWnd, LPSTR AliaName)
//
// Description:   This function stops and closes an AVI file.
//
// Arguments:	
//             HWND  hWnd ... handler of the window
//             LPSTR AviName ... name of the AVI file
//
// Return:	void
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
void CloseAVI(HWND hWnd, LPSTR AliaName)
{ 
   char  Cclose[100], cReturn[256];

   wsprintf((LPSTR)Cclose, "close %s wait", AliaName);
   mciSendString ((LPSTR)Cclose, cReturn, 128, hWnd);
	waveOutSetVolume((HWAVEOUT)1, oldvol);
} 

// not used in the game
void YBPlayWave(LPSTR WaveName, HWND hWnd)
{
   char CmdString[256], FName[256];
   char  cReturn [256];    
   
   strcpy(FName, WavPath);
   strcat(FName, "\\");
   strcat(FName, WaveName);
   strcpy(CurWavName, FName);

   wsprintf((LPSTR)CmdString,"open %s", FName);
   mciSendString ((LPSTR)CmdString, cReturn, 256, hWnd);
   wsprintf((LPSTR)CmdString,"play %s", FName);
   mciSendString ((LPSTR)CmdString, cReturn, 256, hWnd);   
}

// not used in the game
void YBStopWave(LPSTR WaveName, HWND hWnd)
{
   char CmdString[256], FName[256];
   char  cReturn [256];    
   
   strcpy(FName, WavPath);
   strcat(FName, "\\");
   strcat(FName, WaveName);

   wsprintf((LPSTR)CmdString,"stop %s", FName);
   mciSendString ((LPSTR)CmdString, cReturn, 256, hWnd); 
   wsprintf((LPSTR)CmdString,"close %s wait", FName);
   mciSendString ((LPSTR)CmdString, cReturn, 256, hWnd);   
  
}    

// not used in the game
void YBCleanUpWave (HWND hWnd)
{
   char CmdString[256], cReturn[256];
   
   wsprintf((LPSTR)CmdString, "close %s", CurWavName);
   mciSendString ((LPSTR)CmdString, cReturn, 256, hWnd);
}


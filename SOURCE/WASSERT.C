/*==========================================================================
 *
 *  Copyright (C) 1995 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       wassert.c
 *  Content:    Windows assert handler
 *              You must externally define hWndMain and szAppName for this
 *              to work.
 *
 ***************************************************************************/


#ifdef MINIWIN
#include "miniwin/windows.h"
#else
#include <windows.h>
#endif

extern HWND hWndMain;

char WinAppName[32]="WinClassName";
#include "wassert.h"


#ifdef ASSERT
void AssertFail(char szErr[], char szFileName[], int nLine, char szMessage[])
    {
    char szT[256];

    if (szMessage != NULL)
        wsprintf(szT, "Assert(%s);\nFile %s, line %d.  %s", szErr, szFileName, nLine, szMessage);
    else 
        wsprintf(szT, "Assert(%s);\nFile %s, line %d.", szErr, szFileName, nLine);
    switch (MessageBox(hWndMain, szT, WinAppName, MB_ABORTRETRYIGNORE | MB_ICONSTOP | MB_APPLMODAL))
        {
        case IDABORT:
            SendMessage(hWndMain, WM_CLOSE, 0, 0);
        case IDRETRY:
            _asm int 3;
            // Fall Through //
        case IDIGNORE:
            break;

        } // switch
    } // AssertFail


#endif // ASSERT


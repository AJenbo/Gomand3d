#include <windows.h>
#include <windowsx.h>
#include <dinput.h>
#include <ddraw.h>

#ifndef __TKINPUT_H__
#define __TKINPUT_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * keyboard commands
 */
//There are about 56 items
#define KEY_F12    		0x0000000000000001
#define KEY_F11    		0x0000000000000002
#define KEY_SPACE			0x0000000000000004
#define KEY_UP   			0x0000000000000008
#define KEY_DOWN 			0x0000000000000010
#define KEY_LEFT 			0x0000000000000020
#define KEY_RIGHT			0x0000000000000040
#define KEY_PRIOR			0x0000000000000080
#define KEY_NEXT 			0x0000000000000100
#define KEY_HOME 			0x0000000000000200
#define KEY_END  			0x0000000000000400
#define KEY_SHIFT			0x0000000000000800
#define KEY_CONTROL     0x0000000000001000
#define KEY_TAB    		0x0000000000002000
#define KEY_INSERT  		0x0000000000004000
#define KEY_RETURN  		0x0000000000008000
#define KEY_F2     		0x0000000000010000
#define KEY_F6     		0x0000000000020000
#define KEY_192    		0x0000000000040000
#define KEY_A     		0x0000000000080000
#define KEY_B     		0x0000000000100000
#define KEY_C     		0x0000000000200000
#define KEY_D     		0x0000000000400000
#define KEY_E     		0x0000000000800000
#define KEY_F     		0x0000000001000000
#define KEY_G     		0x0000000002000000
#define KEY_H     		0x0000000004000000
#define KEY_I     		0x0000000008000000
#define KEY_J     		0x0000000010000000
#define KEY_K     		0x0000000020000000
#define KEY_L     		0x0000000040000000
#define KEY_M     		0x0000000080000000
#define KEY_N     		0x0000000100000000
#define KEY_O     		0x0000000200000000
#define KEY_P     		0x0000000400000000
#define KEY_Q     		0x0000000800000000
#define KEY_R     		0x0000001000000000
#define KEY_S     		0x0000002000000000
#define KEY_T     		0x0000004000000000
#define KEY_U     		0x0000008000000000
#define KEY_V     		0x0000010000000000
#define KEY_W     		0x0000020000000000
#define KEY_X     		0x0000040000000000
#define KEY_Y     		0x0000080000000000
#define KEY_Z     		0x0000100000000000
#define KEY_188    		0x0000200000000000
#define KEY_190     		0x0000400000000000
#define KEY_1     		0x0000800000000000
#define KEY_2     		0x0001000000000000
#define KEY_3     		0x0002000000000000
#define KEY_4     		0x0004000000000000
#define KEY_5     		0x0008000000000000
#define KEY_6     		0x0010000000000000
#define KEY_7     		0x0020000000000000
#define KEY_8     		0x0040000000000000
#define KEY_9     		0x0080000000000000
#define KEY_0     		0x0100000000000000
#define KEY_ESCAPE 		0x0200000000000000
#define KEY_F1			   0x0400000000000000
#define KEY_SCALE       0x0800000000000000

typedef enum MS_SENSITIVITY
{
	MsLOW=-1, MsNORMAL=0, MsHIGH=1
};

typedef enum MS_MOVEMENT
{
	MSNOTHING, MSLEFT, MSFORWARD, MSRIGHT, MSBACK,
	MSLBUTTON, MSRBUTTON
};

typedef void (*Function) (void);

class CDirectInput
{
private:
	HWND                 hWnd;
	HINSTANCE            hInst;
	LPDIRECTINPUT        lpDI;			// points to a DI object
	LPDIRECTINPUTDEVICE  lpDIMsDev;		// points to a DI mouse device
	LPDIRECTINPUTDEVICE  lpDIKdDev;		// points to a DI keyboard device
	LPDIRECTINPUTDEVICE  *lpDIOther;
	LPDIRECTDRAWSURFACE	lpMsSurface;	// mouse surface

	BOOL                 bDI;			// create the DI object OK?
	BOOL                 bDIMsDev;		// create the DI mouse device OK?
	BOOL                 bDIKdDev;		// create the DI keyboard device OK?
	BOOL                 *bDIOtherDevs;	// create other devices OK?	
	BOOL                 bDIMsAcquired;	// acquired mouse already?
	BOOL                 bDIKdAcquired;	// acquired keyboard already?
	BOOL                 bDIMsCanDraw;  // control cursor drawing
	short                TotalDevices;	// total number of device found

	LONG                 OldMsX;
	LONG                 OldMsY;
	long int             MsAction[7];	// index        mapto
	                                    // ------------------------------
	                                    //   0          nothing
	                                    //   1          X<0
	                                    //   2          X>0
	                                    //   3          Y<0
	                                    //   4          Y>0
	                                    //   5          left button
	                                    //   6          right button
	long int             OldMsAction;
	long int             NewMsAction;
	long int             OldKdAction;
	long int             NewKdAction;
	MS_SENSITIVITY       MsSensitivity;
	int                  MsX;
	int                  MsY;
	int                  MsDxFuzz;
	int                  MsDyFuzz;
	int                  MsXHot;
	int                  MsYHot;
	int                  MsWidth;
	int                  MsHeight;
	RECT						*MsRect;
	short                MsTotalAnis;
	short                MsTotalAniItems;
	DWORD						MsDrawMode;
	short                MsAniItemIdx;
	short                MsAniSpeed;
	short                MsAction4Wrapper;

	_int64					InputKeys;
	//void ProcessMsData(DIMOUSESTATE MsState);
	void ProcessMsData4Game(DIMOUSESTATE MsState);
	void ProcessMsData4Wrapper(DIMOUSESTATE MsState);
	void ShowMsMovement(void);
public:
	CDirectInput(void);
	BOOL CreateDI(HINSTANCE hinst, HWND hwnd);
	BOOL CreateDIKdDevice(void);
	BOOL CreateDIMsDevice(BOOL FullyControl);
	void SetDIMsAction(long int *Action);
	void SetDIMsSensitivity(MS_SENSITIVITY s);
	//void ReadDIMsData(BOOL bSwitch);
	void ProcessDIMsData(BOOL bSwitch);
	long int GetDIMsAction(void);
	BOOL CreateMsSurface(void);
	BOOL LoadCursorBmp(char *filename);
	void DrawMsCursor(BOOL show);
	void TurnOnMsCursor(BOOL b);
	void SetMsCursorColorKey(BOOL b, COLORREF rgb);
	void SetMsTotalAnis(short total);
	void SelectAniCursor(RECT *rc);
	void ClearMsSurface(void);
	void ReleaseMsSurface(void);
	void SetMsAniSpeed(short i);
	void SetMsCursorInfo(int hotx, int hoty, int w, int h);
	int  GetMsX(void);
	int  GetMsY(void);
	BOOL MsLBtnDown(void);

	_int64 ReadDIKdData(BOOL bSwitch);
	BOOL ReacquireKdDevice(void);
	void SaveKeyAction(long int ka);

	void DeleteDIKdDevice(void);
	void DeleteDIMsDevice(void);
	void DeleteDI(void);
	~CDirectInput();
};

#ifdef __cplusplus
};
#endif

#endif __TKINPUT_H__
#ifndef _FLY_H_
#define _FLY_H_

#include "tkinput.h"

#ifdef __cplusplus
extern "C" {
#endif

BOOL InitLight(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
           LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera);
BOOL BuildScene(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
           LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera);
BOOL BYKd3DGame(HWND win, UINT msg, WPARAM wparam, LPARAM lParam);

BOOL CleanupGame3DPart(void);
void ClearupKeyDownMessage(void);
void ProcessKeyDown ();
//void ProcessKeyUp ();
void FinalProcess(void);

#ifdef __cplusplus
};
#endif

#endif
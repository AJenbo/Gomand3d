#ifndef __YBMOUSE_H__
#define __YBMOUSE_H__

#ifdef __cplusplus
extern "C" {
#endif

void YBConfigMouse(int BtnNo, long int Actions);
void BYSetCursorClipArea(void);
void YBSaveCurrentDisplayMode(void);
void YBRestoreClipArea(void);
BOOL BYMs3DGame(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);

#ifdef __cplusplus
};
#endif

#endif
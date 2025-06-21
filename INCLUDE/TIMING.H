#include <windows.h>

extern unsigned char Hours,Minutes,Seconds;
extern unsigned int Thousandths;
extern unsigned char AverageTimePerFrame;
extern D3DVALUE DiffFrame;

void RestartTimer(HWND win);
void PauseTimer();
void UnPauseTimer();
unsigned char Ticket();
 void DispFPS(void);


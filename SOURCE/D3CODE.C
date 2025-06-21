#ifdef MINIWIN
#include "miniwin/windows.h"
#else
#include <windows.h>
#endif
#include "rmdemo.h"
#include "d3code.h"

BOOL ShowMeter=TRUE;
BOOL ShowRadar=TRUE;
BOOL ShowTimer=TRUE;
BOOL ShowSub=TRUE;
BOOL YBTimerFlag=TRUE;

char  sSubTitle1[100], sSubTitle2[100], sSubTitle3[100];
BOOL  fgShowSubTitle = FALSE;
short subx1,suby1,subx2,suby2,subx3,suby3;
short subl1, subl2, subl3;
short subActualLength1,subActualLength2,subActualLength3;
COLORREF subc1, subc2, subc3;
unsigned short subt1, subt2, subt3;
unsigned short substart;

int MonsterAnimationState=0;
//int submonster=0;
//int honor=0;
int RobotLife=100;
int MnstLife=100;
//int RobotEngy=100;
//int MnstEngy=100;

long int Population=100;
//long int PrePopulation=0;
//long int OverallScore=0;
short SysDifficulty = 2;
short SysWatchyStyle = 1;
unsigned char detail;
int newland;
LPDIRECT3DRMFRAME Wcamera, Wscene;
LPDIRECT3DRMFRAME Robotframe;
LPDIRECT3DRMFRAME monstframe;
D3DVALUE	sealevel;
volatile long int InputInt;

//TARGET targets[15];
short  TotalTargets=14;
short  ScaleFactor=2;
short  playfrom;
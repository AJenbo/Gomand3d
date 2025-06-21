#ifndef __D3CODE_H__
#define __D3CODE_H__

#ifdef __cplusplus
extern "C" {
#endif

extern BOOL ShowMeter;
extern BOOL ShowRadar;
extern BOOL ShowTimer;
extern BOOL ShowSub;
extern BOOL YBTimerFlag;

extern char  sSubTitle1[100], sSubTitle2[100], sSubTitle3[100];
extern BOOL  fgShowSubTitle;
extern short subx1,suby1,subx2,suby2,subx3,suby3;
extern short subl1, subl2, subl3;
extern short subActualLength1,subActualLength2,subActualLength3;
extern COLORREF subc1, subc2, subc3;
extern unsigned short subt1, subt2, subt3;
extern unsigned short substart;

extern int MonsterAnimationState;
//extern int submonster;
extern BOOL PlayAsMonster;
//extern int honor;
extern int RobotLife;
extern int MnstLife;
extern int RobotEngy;
extern int MnstEngy;
extern long int Population;
extern long int PrePopulation;
//extern long int OverallScore;
extern short SysDifficulty;
extern short SysWatchyStyle;
extern unsigned char detail;
extern int newland;
extern LPDIRECT3DRMFRAME Wcamera, Wscene;
extern LPDIRECT3DRMFRAME Robotframe;
extern LPDIRECT3DRMFRAME monstframe;
extern D3DVALUE	sealevel;
extern volatile long int InputInt;
extern short playfrom;

#ifdef __cplusplus
};
#endif

#endif __D3CODE_H__
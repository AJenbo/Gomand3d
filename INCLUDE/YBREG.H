//*******************************************************************
// ybreg.h
//
// Copyright 1996 by 47-TEK, INC.  All rights reserved.
//
// Author:	Bo Yuan
// 
// Date:	06/07/96
//
// Description:	Header file of "ybreg.c"
//
// Side effects:
//
// Class:
//
// Function:
//    BOOL YBRegisterGame(char newver[]);
//    BOOL YBTestRegisterOrNot(char newver[]);
//    BOOL YBLoadUserRecord(short i, char newver[]);
//    BOOL YBSaveUserRecord(short i, char newver[]);
//    BOOL YBLoadAllUserRecord(char newver[]);
//    BOOL YBSaveAllUserRecord(char newver[]);
//    void YBConfirmLoad(short idx);
//    BOOL YBLoadTopRecord(short i, char newver[]);
//    BOOL YBSaveTopRecord(short i, char newver[]);
//    BOOL YBLoadAllTopRecord(char newver[]);
//    BOOL YBSaveAllTopRecord(char newver[]);
//    short YBReachTop3(long int s);
//    void YBConfirmTopValue(void);
//    void YBRegRobotToRobotStatus(short idx);
//    void YBRobotStatusToRegRobot(short idx);
// 
// Notes:
//
// Update:
//
// Date			Name			Description
// ==================================================================
//
//*******************************************************************
#ifndef __YBREG_H__
#define __YBREG_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _USERREC_
{
	char  name[12];
	short level;
	short submonster;
	int   score;
    short DWC;
    short sfx;
    short mid;
    short mch;
    short hour;
    short minute;
    short second;
} USERREC;

typedef struct _TOPREC_
{
    char name[12];
    int score;
    short hour;
    short minute;
    short second;
} TOPREC;

typedef struct _TOPSTRREC_
{
    char No[5];
    char name[12];
    char score[20];
    char time[20];
} TOPSTRREC;

extern USERREC urec[10];
extern TOPSTRREC tmp3[3];

BOOL BYRegisterGame(char newver[]);
BOOL BYTestRegisterOrNot(char newver[]);

BOOL YBLoadUserRecord(short i, char newver[]);
BOOL YBSaveUserRecord(short i, char newver[]);
BOOL YBLoadAllUserRecord(char newver[]);
BOOL YBSaveAllUserRecord(char newver[]);

void YBConfirmLoad(short idx);

BOOL YBLoadTopRecord(short i, char newver[]);
BOOL YBSaveTopRecord(short i, char newver[]);
BOOL YBLoadAllTopRecord(char newver[]);
BOOL YBSaveAllTopRecord(char newver[]);
short YBReachTop3(long int s);
void YBConfirmTopValue(void);
void YBRegRobotToRobotStatus(short idx);
void YBRobotStatusToRegRobot(short idx);

#ifdef __cplusplus
};
#endif

#endif __YBREG_H__


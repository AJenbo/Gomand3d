#ifndef _SPUDBMP_H_
#define _SPUDBMP_H_

#include "boink.h"

#ifdef __cplusplus
extern "C" {
#endif

//void SpuddeCheckSlopeWalking(int x1, int y1, int x2, int y2, int *x3, int *y3, unsigned char *bitmap);
//void SpuddeGetWorldPosition(int x, int y, RLValue *X, RLValue *Z);
//RLValue SpuddeMapHeight(int x, int y, unsigned char *bitmap);
//void SpuddeGetBMPPosition(int *x, int *y, RLValue X, RLValue Z);
//int SpuddeCheckSlopeAirborne(int x1, int y1, RLValue Height1, int x2, int y2, RLValue Height2, int *x3, int *y3, RLValue *Height3, unsigned char *bitmap);
void GetGradient(RLVector* gradient, RLValue x, RLValue z);
int SpuddeMoveInAir(MovingObjectData moveme,RLVector *velocity);
int SpuddeMoveOnGround(MovingObjectData moveme, RLVector *velocity, RLValue *gravity);

extern RLValue MaxHeightDifference;

#ifdef __cplusplus
;
#endif

#endif
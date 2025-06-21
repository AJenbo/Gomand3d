#ifndef _CAMERA_H_
#define _CAMERA_H_

//#include "rl.h"
#include "rl2d3d.h"

//#define GROUNDCLEARANCE (RLVal(5))
//#define GROUNDCLEARANCE (RLVal(1.15))
#define GROUNDCLEARANCE (RLVal(1.5))
#define BESTORBIT (RLVal(3.5))

#undef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#undef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// movement methods
#define DRIFT 1
#define SLUGDRIFT 2
#define CUT 3
#define HALFCUT 4
#define HOLD 5
#define THREEQUARTERCUT 6
#define CIRCLE 7
#define POV 8
#define CITYLIFE 9
#define WATCHDROP 10
#define WATCHMELT 11
#define HUMANEYE 12

// sweet spots
#define BEHINDLEFT 1
#define BEHINDRIGHT 2
#define SIDELEFT 3
#define SIDERIGHT 4
#define INSIDE 5
#define CIRCLING 6
#define BIGCITY 7
#define ONTHEGROUND 8

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _caminfo {
	RLFrame target;
	int zone;
	int current;
	int next;
	int method;
	RLVector velocity;
} Caminfo;

extern Caminfo* camerastuff;

void DestroyCameraInfo(Caminfo** camstuff);
void CreateCameraInfo(Caminfo**, RLFrame Robotframe, RLFrame monstframe);
void cameraalg(RLFrame cam, void* arg, RLValue delta);
void PickMethodAndSpots(Caminfo* camstuff, RLVector *sweetspot, RLVector *target, RLVector camplace);
int  PickNextSweetSpot(Caminfo* camstuff, RLValue dist2, RLVector camplace, RLVector chrsep);
int  PickMethod(Caminfo* camstuff, RLValue dist2);
int  PickASide(Caminfo* camstuff, RLVector chrsep);
int  PickABack(Caminfo* camstuff);
void camera_hold(Caminfo* camstuff, RLValue groundmove);
void camera_slugdrift(Caminfo* camstuff, RLVector* sweetspot, RLVector* camera_delta, RLValue groundmove);
void camera_pov(Caminfo* camstuff, RLVector* sweetspot, RLVector* camera_delta, RLValue groundmove);
void camera_circle(Caminfo* camstuff, RLVector* sweetspot, RLVector* camera_delta, RLValue groundmove);
void camera_drift(Caminfo* camstuff, RLVector* sweetspot, RLVector* camera_delta, RLValue groundmove);
void camera_bigcity(Caminfo* camstuff, RLVector* sweetspot, RLVector* camera_delta, RLValue groundmove, RLVector camplace);
void camera_watchdrop(Caminfo* camstuff, RLVector *camplace, RLValue groundheight);
void camera_humaneye(Caminfo* camstuff, RLVector *camplace, RLValue groundheight);
void camera_watchmelt(Caminfo* camstuff, RLVector *camplace, RLValue groundheight);
int  CountBuildings(RLVector center, RLValue radius);
int  GetAntiBuildingForce(RLVector watchy, RLVector* force);
int  GetAntiBuildingForceCircle(RLVector watchy, RLVector* force);
void SetCameraTarget(Caminfo* camstuff, RLFrame targframe);
void ResetCameraTarget(Caminfo* camstuff);
void EaseInto(RLVector* final, RLVector* original, RLVector* extra, RLValue amount);
void AutoCameras();

#ifdef __cplusplus
};
#endif

#endif
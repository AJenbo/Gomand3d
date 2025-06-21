#ifndef _MYBUILD_H_
#define _MYBUILD_H_

#include "building.h"

//#define MAX_BUILDINGS	30
//#define PATH_X			"D:\\X"
#define GEB_COUNT 12
#define SEB_COUNT 6

typedef struct _Building {
    //D3DVECTOR position[MAX_BUILDINGS];
    LPDIRECT3DRMDEVICE dev;
    LPDIRECT3DEXECUTEBUFFER eb;
    LPDIRECT3DMATERIAL mat;
} Building;

typedef struct 
{
	D3DVERTEX *v;
	D3DTRIANGLE *t;
	D3DTEXTUREHANDLE hTex;
    LPDIRECT3DEXECUTEBUFFER eb;
	LPDIRECT3DRMUSERVISUAL uvis;
	LPDIRECT3DRMFRAME frame;
   Building *building;
} EbInfo;

extern building_area    bldg_lvlLX[(LANDXSIZE>>RES_SHFT_DIVISOR)][(LANDZSIZE>>RES_SHFT_DIVISOR)];     // Point to Proper Building Struct.
extern building_area    bldg_lvlLM[(LANDXSIZE>>RES_SHFT_DIVISOR)][(LANDZSIZE>>RES_SHFT_DIVISOR)];     // Point to Proper Building Struct.
extern building_area    bldg_lvlLR[(LANDXSIZE>>RES_SHFT_DIVISOR)][(LANDZSIZE>>RES_SHFT_DIVISOR)];     // Point to Proper Building Struct.
extern building_area    bldg_lvlLH[(LANDXSIZE>>RES_SHFT_DIVISOR)][(LANDZSIZE>>RES_SHFT_DIVISOR)];     // Point to Proper Building Struct.
extern building_area    bldg_lvlLS[(LANDXSIZE>>RES_SHFT_DIVISOR)][(LANDZSIZE>>RES_SHFT_DIVISOR)];     // Point to Proper Building Struct.
extern building_area    bldg_lvlLN[(LANDXSIZE>>RES_SHFT_DIVISOR)][(LANDZSIZE>>RES_SHFT_DIVISOR)];     // Point to Proper Building Struct.
extern building_area    bldg_lvlLT[(LANDXSIZE>>RES_SHFT_DIVISOR)][(LANDZSIZE>>RES_SHFT_DIVISOR)];     // Point to Proper Building Struct.

BOOL
BuildTestScene(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
           LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera);

BOOL CreateBuilding(EbInfo *buildingebinfo);

int BuildingCallback(LPDIRECT3DRMUSERVISUAL uvis,
                 void* arg,
                 D3DRMUSERVISUALREASON reason,
                 LPDIRECT3DRMDEVICE dev,
                 LPDIRECT3DRMVIEWPORT view);

BOOL RenderBuilding(Building* building,
				LPDIRECT3DRMDEVICE dev,
				LPDIRECT3DRMVIEWPORT view);

BOOL CreateBuildingObjects(Building* building, LPDIRECT3DRMDEVICE dev);
void CleanupBuildingObjects(Building* building);
void DestroyBuilding(LPDIRECT3DRMOBJECT obj, void* arg);
BOOL DelBuilding(void);

lvl_bldg_rsrcs *BuildingInfo(void);
//BOOL PlaceVertices(void);
//BOOL PlaceTriangles(void);
BOOL GebFill(int count);
BOOL AddBuilding(LPDIRECT3DRMFRAME scene);
void InfoFree(void);
#ifdef LSDEBUG
void OutPut(void);
#endif LSDEBUG

#endif _MYBUILD_H_

#ifndef _ICHARS_H_
#define _ICHARS_H_

#include "windows.h"
#include "rl2d3d.h"
#include "binload.h"

typedef struct _ipartdlist 
{
	int 					Parent;
	int 					No;
	DWORD					tcount; 
	DWORD					vcount;
	D3DVERTEX				*Vertex;
	D3DTRIANGLE 			*Triangle;

	LPDIRECT3DRMUSERVISUAL	uvis;
	LPDIRECT3DEXECUTEBUFFER eb;
	LPDIRECT3DMATERIAL		mat;
	RLFrame 				frame, freeframe;
	struct _ipartdlist* 	nextpart;
} ipartdlist;

typedef struct _ichar 
{
	RLFrame 				camera, scene; 
	ipartdlist* 			firstipartdlist;
	LPDIRECT3DRMUSERVISUAL	uvis;
	LPTEXTURESTRUCT 		lpTexture;
	BOOL					bCanShow;
} ichar;

typedef struct _idim 
{
	RLBox bounds;
	int numvertices;
} idim;

extern ichar imcharacters[2];
extern idim ichardims[2];

// ****************************************************************
// Initialization Functions
// ****************************************************************
void ConstructDLists(RLFrame charframe, Handle hBin);
BOOL MeshestoDList (Handle hBin, RLFrame frame, int NoObj, int mormon);
void StepDownHierarchy (Handle hBin, RLFrame parentframe, int mormon);
// ****************************************************************
// Cleanup Functions
// ****************************************************************
void DestroyDLists(void);
void KillAPart(ipartdlist *parts);
// ****************************************************************
// Manipulation Functions
// ****************************************************************
void SetRobotRenderQuality(RLRenderQuality quality);
int ExplodeARobot();
int FlingAPart(ipartdlist *parts, int mormon);
void KillSubMonster();
int MeltAMonster(int alive);
int MeltAPart(ipartdlist *parts, RLVector* modelposition, int alive);
void MovePartToScene(ipartdlist *parts);
void ReleaseSpirit();
void ResurectSubMonster();
void ReTextureMonster(ichar *imchars);
void SpiritInit();
void SpiritCollisionFunction(MovingObjectData movedata);
void SpiritMotionFunction(MovingObjectData movedata);
// ****************************************************************
// Rendering Functions
// ****************************************************************
void RenderCharacters(int method);
void RenderAPart(ipartdlist *parts, RLRenderQuality quality);
RLFrame LoadModel(char* filename, RLFrame parent);

#endif
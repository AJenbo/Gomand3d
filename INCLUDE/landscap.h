#ifndef _LANDSCAP_H_
#define _LANDSCAP_H_

#ifdef MINIWIN
#include "miniwin/d3d.h"
#include "miniwin/d3drm.h"
#else
#include <d3d.h>
#include <d3drmwin.h>
#endif
#include "d3dtypes.h"
#include "mdtex.h"

#define LANDXSIZE 256
#define LANDZSIZE 256

#define LANDXCENTER (LANDXSIZE>>1)
#define LANDZCENTER (LANDZSIZE>>1)

#define INCMOD(x, m) (((x)+1)%(m))
#define DECMOD(x, m) (((x)+(m)-1)%(m))

#define BOTTOMOFCLUSTER(a) (((a)*2-1+cpx*2)%(cpx*2))
#define ENDOFCLUSTERX(a) (((a)*2-1+cpx*2)%(cpx*2))
#define ENDOFCLUSTERZ(a) (((a)*2-1+cpz*2)%(cpz*2))
#define TOPOFCLUSTER(a) ((a)*2)
#define JOINTINDEX(a, b) (cpz*(a) + (b))
#define VERTEXINDEX(a, b) (2*cpz*(a) + (b))
#define SECTIONINDEX(a, b, c) (2*(cpzs*(a) + (b)) + (c))

#ifdef __cplusplus
extern "C" {
#endif

extern D3DRMBOX landbox;
extern D3DVALUE landscale;
extern D3DVALUE texturecutoffs[4];

typedef struct _cGlobals {
	D3DVERTEX *vertices;
	D3DTRIANGLE *sections;
	int xmin, xmax, zmin, zmax;
	int zstripmin, zlinemin, zstripmax, zlinemax;
	int xstripmin, xlinemin, xstripmax, xlinemax;
	LPDIRECT3DRMFRAME scene, camera;
	int  camerax, cameraz, oldcamerax, oldcameraz;
} cGlobalstype;

typedef struct _Land {
    LPDIRECT3DRMDEVICE dev;
	LPDIRECT3DRMVIEWPORT view;
    LPDIRECT3DEXECUTEBUFFER eb;
	TEXTURESTRUCT tex;
    LPDIRECT3DMATERIAL mat;
} Land;

extern cGlobalstype cGlobals;
extern int cuint, cpx, cpz, cpxs, cpzs;

void init_iland(LPDIRECT3DRMFRAME camera, LPDIRECT3DRMFRAME scene);
BOOL BuildLandScene(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,\
					LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera);
void AssignGroundTextures(PALETTEENTRY* pal);
void DestroyILand(void);

#ifdef __cplusplus
};
#endif

#endif 
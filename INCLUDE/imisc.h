#include "rl2d3d.h"
#include "mdtex.h"
#include "binload.h"

#define MAX_NO_MISCDLISTS 70

typedef struct _iobjdlist 
{
	BOOL		bTransparent;
	int			NOparent;
	DWORD		tcount; 
	DWORD		vcount;
    D3DVERTEX	*Vertex;
    D3DTRIANGLE *Triangle;

    LPDIRECT3DRMDEVICE			dev;
    LPDIRECT3DRMUSERVISUAL		uvis;
    LPDIRECT3DEXECUTEBUFFER		eb;
    LPDIRECT3DMATERIAL			mat;
	LPTEXTURESTRUCT				lpTexture;
	Handle		builder;
    RLFrame frame;
	int dup;
   int matrixoffset;
} iobjdlist;

typedef struct _Message 
{
    LPDIRECT3DRMDEVICE dev;
    LPDIRECT3DEXECUTEBUFFER eb;
    LPDIRECT3DMATERIAL mat;
	D3DTEXTUREHANDLE hTex;
//	LPDIRECT3DRMMESHBUILDER builder;
} Message;



/*
// Be called by this file.
int MeshtoDList (RLObject themesh, RLTexture thetexture, RLIMSurfaceInfo *surface);
int DupDList(int originaldlist, RLFrame parent); // Be called by cars and clutter files.
void DestroyMiscDLists (void);     // Be called by IDIOT file.
void FlipTextureCoords (int whichdlist, int whichside);// Be called by boink2 and Robotani2 files.
void RenderAllMiscDLists();// Be called by IDIOT file.

//Be called by cars file, now don't call by the function of 'MakeCars'
RLTexture DListGetTexture(int whichdlist);
void DListSetTexture(int whichdlist, RLTexture tex); // Don't used.
SwitchTextures(RLTexture newtex, int whichdlist) // as same.
*/

int LoadIntoDList (char* filename, LPDIRECT3DRMFRAME parent, LPTEXTURESTRUCT lpTexture, void *surface);
int MeshtoDList(Handle hTheMesh, LPTEXTURESTRUCT lpTexture, 
				LPDIRECT3DRMFRAME frame, BOOL bTransparent);
int DupDList(int originaldlist, RLFrame parent);
int DupDListForCopyUVis(int originaldlist, RLFrame parent); // It's new code is writed in 8/9.
void FlipTextureCoords(int whichdlist, int whichside);
void DestroyMiscDLists(void);
void RenderAllMiscDLists(void);

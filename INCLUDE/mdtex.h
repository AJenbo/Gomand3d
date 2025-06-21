#ifndef _MDTEX_H_
#define _MDTEX_H_

#include "rmdemo.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct _TEXTURESTRUCT {
    LPDIRECTDRAWSURFACE lpSrcTextureSurf;
    LPDIRECT3DTEXTURE   lpSrcTexture;
    D3DTEXTUREHANDLE    hTex;
} TEXTURESTRUCT, *LPTEXTURESTRUCT;

extern BOOL MyLoadTexture(LPDIRECT3DRMDEVICE dev, LPSTR filename, LPTEXTURESTRUCT lptexstruct, int transflag);
extern BOOL MarksLoadTexture(LPDIRECT3DRMDEVICE dev, LPSTR filename, LPTEXTURESTRUCT lptexstruct, int transflag);
extern void ReleaseOneTexture(LPTEXTURESTRUCT lptexstruct);
extern BOOL MyReplaceTexture(LPDIRECT3DRMDEVICE dev, LPSTR filename, LPTEXTURESTRUCT lptexstruct, int transflag);

//HRESULT LastError;
//char LastErrorString[256];
//char* D3DAppErrorToString(HRESULT error);
//void D3DAppISetErrorString( LPSTR fmt, ... );

#ifdef __cplusplus
};
#endif

#endif
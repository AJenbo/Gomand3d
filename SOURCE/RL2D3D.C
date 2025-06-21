//**************************************************************************
// rl2d3d.c
//
// (c) Copyright Inventec(Tian Jin) 1996. All rights reserved.
//
// Author:      RD7 & AR
//
// Date:        1996
//
// Description: (1) Type and function redefinition from Rendermorphic library
//                  to Direct3D.
//              (2) If both _DEBUG and _MSGOUT defined, some error message
//                  will be output to a file named rl2d3d.out if error occurs.
//              (3) A external global variable lpD3DRM needed to create frame...
//
// Notes:       Only for Direct 3D version of Goman
//
// Update:
//
//**************************************************************************
#ifdef _ITC_D3D_

#include <malloc.h>
#include "rl2d3d.h"

#ifdef _DEBUG
#include <stdio.h>
#define MSGFILE   "rl2d3d.out"
static FILE   *msgout;
#endif

static HRESULT      result;
static size_t       _totalallocated = 0; //if RLMalloc called, increase by 1,
                                         //if RLFree called, decrease by 1.
extern LPDIRECT3DRM lpD3DRM;

//**************************************************************************
// Name:        RLMalloc & RLFree & RLGetTotalAllocated

// Author:      Sanfo

// Date:        June 1996

// Description: Allocated a block of memory and return it's address through
//              the inputed pointer.

// Arguments:   (1) void** p_return --- input pointer, should be passed 
//                                      without initialization.
//              (2) size_t size --- memory size.

// Return:      Error code.

//**************************************************************************
RLError RLMalloc(void** p_return, size_t size)
{
	void *p;
	p = malloc(size);
	if(p == NULL)
		return D3DRMERR_BADALLOC;
	*p_return = p;

	_totalallocated += 1;

	return D3DRM_OK;
}

void RLFree(void* p)
{
	size_t size = sizeof(p);

	if( p != NULL )
		free(p);

	_totalallocated -= 1;
}

size_t RLGetTotalAllocated(void)
{
	return _totalallocated;
}


RLObject RLObjectFromName(const char* name)
{
	LPDIRECT3DRMOBJECT  object;

	result = lpD3DRM->lpVtbl->GetNamedObject (lpD3DRM, name, &object);

#if defined (_DEBUG) && defined (_MSGOUT)
	if( FAILED(result) )
	{
		msgout = fopen(MSGFILE, "at");
		fprintf(msgout, "Error RLObjectFromName : %s \n", name);
		fclose(msgout);
		return NULL;
	}
#endif

	return object;
}

RLError RLObjectDestroy(RLObject object)
{
	object->lpVtbl->Release(object);
	return D3DRM_OK;
}


RLFrame RLCreateFrame(RLFrame parent)
{
	static RLFrame target;

	result = lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, parent, &target);

#if defined (_DEBUG) && defined (_MSGOUT)
	if( FAILED(result) )
	{
		msgout = fopen(MSGFILE, "at");
		fprintf(msgout, "Error RLCreateFrame : %s\n", DirectXErrorToString(result));
		fclose(msgout);
		return NULL;
	}
#endif

	return target;
}

const char* RLObjectGetClassName(RLObject object)
{
	static char name[256];
	DWORD       len = 256;

	result = object->lpVtbl->GetClassName(object, &len, (LPSTR)name);

#if defined (_DEBUG) && defined (_MSGOUT)
	if( FAILED(result) )
	{
		msgout = fopen(MSGFILE, "at");
		fprintf(msgout, "Error RLObjectGetClassName : %s\n", DirectXErrorToString(result));
		fclose(msgout);
		return NULL;
	}
#endif

	return name;
}

RLFrame RLFrameGetScene(RLFrame frame)
{
	RLFrame scene;
	result = frame->lpVtbl->GetScene( frame, &scene );

#if defined (_DEBUG) && defined (_MSGOUT)
	if( FAILED(result) )
	{
		msgout = fopen(MSGFILE, "at");
		fprintf(msgout, "Error RLFrameGetScene %s\n", DirectXErrorToString(result));
		fclose(msgout);
		return NULL;
	}
#endif

	return scene;
}

RLFrame RLFrameGetParent(RLFrame frame )
{
	RLFrame parent;

	result = frame->lpVtbl->GetParent( frame, &parent );

#if defined (_DEBUG) && defined (_MSGOUT)
	if( FAILED(result) )
	{
		msgout = fopen(MSGFILE, "at");
		fprintf(msgout, "Error RLFrameGetParent %s\n", DirectXErrorToString(result));
		fclose(msgout);
		return NULL;
	}
#endif

	return parent;
}

//**************************************************************************
// Name:        RLFrameGetVisuals()

// Author:      Sanfo

// Date:        June 1996

// Description: Get a visual array contained in a frame.

// Arguments:   (1) RLFrame frame --- frame which contains visuals.
//              (2) int *count ---- visual counts will be returned.
//              (3) RLVisual **visuals --- visuals array obtained from frame.
//                                         passed before initialization.

// Notes:       visuals must be freed with RLFree after this function is called.

// Return:      Error code.

//**************************************************************************
RLError RLFrameGetVisuals (RLFrame frame, int * count, RLVisual ** visuals)
{
	LPDIRECT3DRMVISUALARRAY lpVisualArray;
	RLVisual  visual = NULL;
	int i,size;

	result = frame->lpVtbl->GetVisuals( frame, &lpVisualArray );
#if defined (_DEBUG) && defined (_MSGOUT)
	if( FAILED(result) )
	{
		msgout = fopen(MSGFILE, "at");
		fprintf(msgout, "Error GetVisuals in RLFrameGetVisuals %s\n", DirectXErrorToString(result));
		fclose(msgout);
		return result;
	}
#endif
	size = lpVisualArray->lpVtbl->GetSize( lpVisualArray );

	DirectX_CHECK( RLMalloc((void **)visuals, size*sizeof(RLVisual)) );

	*count = size;

	for(i=0; i<size; ++i)
	{
		DirectX_CHECK(lpVisualArray->lpVtbl->GetElement(lpVisualArray, i, &visual));
		(*visuals)[i] = visual;
	}

	return D3DRM_OK;
}

//**************************************************************************
// Name:        RLFrameGetChildren()

// Author:      Sanfo

// Date:        June 1996

// Description: Get a child frame array contained in a frame.

// Arguments:   (1) RLFrame parent --- frame which contains sub-frames.
//              (2) int *count ---- children counts will be returned.
//              (3) RLFrame **children --- child frame array obtained from frame.
//                                         passed before initialization.

// Notes:       children must be freed with RLFree after this function is called.

// Return:      Error code.

//**************************************************************************
RLError RLFrameGetChildren(RLFrame parent, int * count, RLFrame ** children)
{
	LPDIRECT3DRMFRAMEARRAY lpFrameArray;
	RLFrame frame = NULL;
	int i,size;

	result = parent->lpVtbl->GetChildren( parent, &lpFrameArray );
#if defined (_DEBUG) && defined (_MSGOUT)
	if( FAILED(result) )
	{
		msgout = fopen(MSGFILE, "at");
		fprintf(msgout, "Error GetChildren in RLFrameGetChildren %s\n", DirectXErrorToString(result));
		fclose(msgout);
		return result;
	}
#endif

	size = lpFrameArray->lpVtbl->GetSize( lpFrameArray );

	DirectX_CHECK( RLMalloc((void **)children, size*sizeof(RLFrame)) );

	*count = size;

	for(i=0; i<size; ++i)
	{
		DirectX_CHECK( lpFrameArray->lpVtbl->GetElement(lpFrameArray, i, &frame) );
		(*children)[i] = frame;
	}

	return D3DRM_OK;
}

RLMaterial RLFaceGetMaterial(RLFace face)
{
	static RLMaterial mat;
	result = face->lpVtbl->GetMaterial( face, &mat );

#if defined (_DEBUG) && defined (_MSGOUT)
	if( FAILED(result) )
	{
		msgout = fopen(MSGFILE, "at");
		fprintf(msgout, "Error RLFaceGetMaterial : %s\n", DirectXErrorToString(result));
		fclose(msgout);
		return NULL;
	}
#endif

	return mat;
}


RLMesh RLLoadMesh(const char *name)
{
	LPDIRECT3DRMMESHBUILDER meshbuilder;

	lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &meshbuilder);
	result = meshbuilder->lpVtbl->Load(meshbuilder,
									   (LPVOID)name, NULL,
									   D3DRMLOAD_FROMFILE,
									   NULL, NULL);

#if defined (_DEBUG) && defined (_MSGOUT)
	if( FAILED(result) )
	{
		meshbuilder->lpVtbl->Release(meshbuilder);

		msgout = fopen(MSGFILE, "at");
		fprintf(msgout, "Error RLLoadMesh %s : %s\n", name, DirectXErrorToString(result));
		fclose(msgout);
		return NULL;
	}
#endif

	return meshbuilder;
}

//**************************************************************************
// Name:        RLMeshGetFaces()

// Author:      Sanfo

// Date:        June 1996

// Description: Get a face array contained in a mesh.

// Arguments:   (1) RLMesh mesh --- input mesh.
//              (2) int *count ---- faces counts will be returned.
//              (3) RLFace **faces --- faces will be returned.
//                                     passed before initialization.

// Notes:       faces must be freed with RLFree after this function is called.

// Return:      Error code.

//**************************************************************************
RLError RLMeshGetFaces(RLMesh mesh, int* count, RLFace** faces)
{
	LPDIRECT3DRMFACEARRAY lpFaceArray;
	RLFace  face = NULL;
	int i,size;

	result = mesh->lpVtbl->GetFaces( mesh, &lpFaceArray );

#if defined (_DEBUG) && defined (_MSGOUT)
	if( FAILED(result) )
	{
		msgout = fopen(MSGFILE, "at");
		fprintf(msgout, "Error GetFaces in RLMeshGetFaces : %s\n", DirectXErrorToString(result));
		fclose(msgout);
		return result;
	}
#endif

	size = lpFaceArray->lpVtbl->GetSize( lpFaceArray );

	DirectX_CHECK( RLMalloc((void **)faces, size*sizeof(RLFace)) );

	*count = size;

	for(i=0; i<size; ++i)
	{
		DirectX_CHECK( lpFaceArray->lpVtbl->GetElement(lpFaceArray, i, &face) );
		(*faces)[i] = face;
	}

	return D3DRM_OK;
}

//**************************************************************************
// Name:        RLMeshGetVertices()

// Author:      Sanfo

// Date:        July 1996

// Description: Get face data from a mesh

// Arguments:   (1) RLMesh --- input mesh
//              (2) int *vertex_count --- vertex count will be returned.
//              (3) RLVector **vertices --- vertices array will be returned.
//              (4) int *normal_count --- normal count will be returned.
//              (5) RLVector **normals --- normals array will be returned.
//              (6) int **face_data --- face data will be returned.

// Notes:       all memory must be freed with RLFree after this function is called

// Return:      Error code.

//**************************************************************************
RLError RLMeshGetVertices(RLMesh mesh,
						  int* vertex_count, RLVector** vertices,
						  int* normal_count, RLVector** normals,
						  int** face_data)
{
    DWORD vcount=0, ncount=0, facesize=0, *pFacedata=NULL;
    RLVector *pVertices=NULL, *pNormals=NULL;

    //call this first to get proper memory size will be allocated.
    DirectX_CHECK(mesh->lpVtbl->GetVertices(mesh, &vcount,   pVertices,
                                                  &ncount,   pNormals,
                                                  &facesize, pFacedata));

    //allocate memory for each memory block    
    DirectX_CHECK( RLMalloc(&pVertices, vcount*sizeof(RLVector)) );
    DirectX_CHECK( RLMalloc(&pNormals,  ncount*sizeof(RLVector)) );
    DirectX_CHECK( RLMalloc(&pFacedata, facesize*sizeof(DWORD)) );

    //call again to get vertices, normals and face data
    DirectX_CHECK(mesh->lpVtbl->GetVertices(mesh, &vcount,   pVertices,
                                                  &ncount,   pNormals,
                                                  &facesize, pFacedata));
    *vertex_count = (int)vcount;
    *normal_count = (int)ncount;
    *vertices = pVertices;
    *normals  = pNormals;
    *face_data= (int *)pFacedata;

	return D3DRM_OK;
}


RLError RLMeshSetColour(RLMesh mesh, RLColour color)
{
	result = mesh->lpVtbl->SetColor (mesh, color);

	return result;
}

void RLTextureSetDefaultShades(int shades)
{
    lpD3DRM->lpVtbl->SetDefaultTextureShades(lpD3DRM, (DWORD)shades);
}

RLTexture RLLoadTexture(const char * fileName)
{
    RLTexture lpTexture = NULL;

    DirectX_CHECK(lpD3DRM->lpVtbl->LoadTexture(lpD3DRM, fileName, &lpTexture));

    return lpTexture;
}

RLMaterial RLCreateMaterial(RLValue ks, RLValue power)
{
    RLMaterial lpMat = NULL;

    DirectX_CHECK(lpD3DRM->lpVtbl->CreateMaterial(lpD3DRM, power, &lpMat));

    return (lpMat);
}

RLViewport RLCreateViewport(RLDevice dev, RLFrame camera,
                            int x, int y, int width, int height)
{
    LPDIRECT3DRMVIEWPORT lpViewport = NULL;

    DirectX_CHECK(lpD3DRM->lpVtbl->CreateViewport(lpD3DRM, dev, camera, 
                                                  (DWORD)x, (DWORD)y, 
                                                  (DWORD)width, (DWORD)height, 
                                                  &lpViewport));
    return lpViewport;
}
 

void RLTextureSetDefaultColours(int colors)
{
    lpD3DRM->lpVtbl->SetDefaultTextureColors(lpD3DRM, (DWORD)colors);
}

RLColour RLCreateColourRGBA(RLValue red, RLValue green, RLValue blue, RLValue alpha)
{
	RLColour color = D3DRMCreateColorRGBA(red, green, blue, alpha);
	return color;
}

//**************************************************************************
// Name:        DirectXErrorToString()

// Author:      Sample code from DXSDK viewer

// Date:        June 1996

// Description: Returns a pointer to a string describing the given error code.
//              contain DirectDraw, Direct3D R-Mode and Direct3D I-Mode errors.

// Arguments:   HRESULT error --- error code.

// Return:      Error string.

//**************************************************************************
char* DirectXErrorToString(HRESULT error)
{
	switch(error)
	{
		case DD_OK:
			/* Also includes D3D_OK and D3DRM_OK */
			return "No error.\0";
		case DDERR_ALREADYINITIALIZED:
			return "This object is already initialized.\0";
		case DDERR_BLTFASTCANTCLIP:
			return "Return if a clipper object is attached to the source surface passed into a BltFast call.\0";
		case DDERR_CANNOTATTACHSURFACE:
			return "This surface can not be attached to the requested surface.\0";
		case DDERR_CANNOTDETACHSURFACE:
			return "This surface can not be detached from the requested surface.\0";
		case DDERR_CANTCREATEDC:
			return "Windows can not create any more DCs.\0";
		case DDERR_CANTDUPLICATE:
			return "Can't duplicate primary & 3D surfaces, or surfaces that are implicitly created.\0";
		case DDERR_CLIPPERISUSINGHWND:
			return "An attempt was made to set a cliplist for a clipper object that is already monitoring an hwnd.\0";
		case DDERR_COLORKEYNOTSET:
			return "No src color key specified for this operation.\0";
		case DDERR_CURRENTLYNOTAVAIL:
			return "Support is currently not available.\0";
		case DDERR_DIRECTDRAWALREADYCREATED:
			return "A DirectDraw object representing this driver has already been created for this process.\0";
		case DDERR_EXCEPTION:
			return "An exception was encountered while performing the requested operation.\0";
		case DDERR_EXCLUSIVEMODEALREADYSET:
			return "An attempt was made to set the cooperative level when it was already set to exclusive.\0";
		case DDERR_GENERIC:
			return "Generic failure.\0";
		case DDERR_HEIGHTALIGN:
			return "Height of rectangle provided is not a multiple of reqd alignment.\0";
		case DDERR_HWNDALREADYSET:
			return "The CooperativeLevel HWND has already been set. It can not be reset while the process has surfaces or palettes created.\0";
		case DDERR_HWNDSUBCLASSED:
			return "HWND used by DirectDraw CooperativeLevel has been subclassed, this prevents DirectDraw from restoring state.\0";
		case DDERR_IMPLICITLYCREATED:
			return "This surface can not be restored because it is an implicitly created surface.\0";
		case DDERR_INCOMPATIBLEPRIMARY:
			return "Unable to match primary surface creation request with existing primary surface.\0";
		case DDERR_INVALIDCAPS:
			return "One or more of the caps bits passed to the callback are incorrect.\0";
		case DDERR_INVALIDCLIPLIST:
			return "DirectDraw does not support the provided cliplist.\0";
		case DDERR_INVALIDDIRECTDRAWGUID:
			return "The GUID passed to DirectDrawCreate is not a valid DirectDraw driver identifier.\0";
		case DDERR_INVALIDMODE:
			return "DirectDraw does not support the requested mode.\0";
		case DDERR_INVALIDOBJECT:
			return "DirectDraw received a pointer that was an invalid DIRECTDRAW object.\0";
		case DDERR_INVALIDPARAMS:
			return "One or more of the parameters passed to the function are incorrect.\0";
		case DDERR_INVALIDPIXELFORMAT:
			return "The pixel format was invalid as specified.\0";
		case DDERR_INVALIDPOSITION:
			return "Returned when the position of the overlay on the destination is no longer legal for that destination.\0";
		case DDERR_INVALIDRECT:
			return "Rectangle provided was invalid.\0";
		case DDERR_LOCKEDSURFACES:
			return "Operation could not be carried out because one or more surfaces are locked.\0";
		case DDERR_NO3D:
			return "There is no 3D present.\0";
		case DDERR_NOALPHAHW:
			return "Operation could not be carried out because there is no alpha accleration hardware present or available.\0";
		case DDERR_NOBLTHW:
			return "No blitter hardware present.\0";
		case DDERR_NOCLIPLIST:
			return "No cliplist available.\0";
		case DDERR_NOCLIPPERATTACHED:
			return "No clipper object attached to surface object.\0";
		case DDERR_NOCOLORCONVHW:
			return "Operation could not be carried out because there is no color conversion hardware present or available.\0";
		case DDERR_NOCOLORKEY:
			return "Surface doesn't currently have a color key\0";
		case DDERR_NOCOLORKEYHW:
			return "Operation could not be carried out because there is no hardware support of the destination color key.\0";
		case DDERR_NOCOOPERATIVELEVELSET:
			return "Create function called without DirectDraw object method SetCooperativeLevel being called.\0";
		case DDERR_NODC:
			return "No DC was ever created for this surface.\0";
		case DDERR_NODDROPSHW:
			return "No DirectDraw ROP hardware.\0";
		case DDERR_NODIRECTDRAWHW:
			return "A hardware-only DirectDraw object creation was attempted but the driver did not support any hardware.\0";
		case DDERR_NOEMULATION:
			return "Software emulation not available.\0";
		case DDERR_NOEXCLUSIVEMODE:
			return "Operation requires the application to have exclusive mode but the application does not have exclusive mode.\0";
		case DDERR_NOFLIPHW:
			return "Flipping visible surfaces is not supported.\0";
		case DDERR_NOGDI:
			return "There is no GDI present.\0";
		case DDERR_NOHWND:
			return "Clipper notification requires an HWND or no HWND has previously been set as the CooperativeLevel HWND.\0";
		case DDERR_NOMIRRORHW:
			return "Operation could not be carried out because there is no hardware present or available.\0";
		case DDERR_NOOVERLAYDEST:
			return "Returned when GetOverlayPosition is called on an overlay that UpdateOverlay has never been called on to establish a destination.\0";
		case DDERR_NOOVERLAYHW:
			return "Operation could not be carried out because there is no overlay hardware present or available.\0";
		case DDERR_NOPALETTEATTACHED:
			return "No palette object attached to this surface.\0";
		case DDERR_NOPALETTEHW:
			return "No hardware support for 16 or 256 color palettes.\0";
		case DDERR_NORASTEROPHW:
			return "Operation could not be carried out because there is no appropriate raster op hardware present or available.\0";
		case DDERR_NOROTATIONHW:
			return "Operation could not be carried out because there is no rotation hardware present or available.\0";
		case DDERR_NOSTRETCHHW:
			return "Operation could not be carried out because there is no hardware support for stretching.\0";
		case DDERR_NOT4BITCOLOR:
			return "DirectDrawSurface is not in 4 bit color palette and the requested operation requires 4 bit color palette.\0";
		case DDERR_NOT4BITCOLORINDEX:
			return "DirectDrawSurface is not in 4 bit color index palette and the requested operation requires 4 bit color index palette.\0";
		case DDERR_NOT8BITCOLOR:
            return "DirectDrawSurface is not in 8 bit color mode and the requested operation requires 8 bit color.\0";
        case DDERR_NOTAOVERLAYSURFACE:
            return "Returned when an overlay member is called for a non-overlay surface.\0";
        case DDERR_NOTEXTUREHW:
            return "Operation could not be carried out because there is no texture mapping hardware present or available.\0";
        case DDERR_NOTFLIPPABLE:
            return "An attempt has been made to flip a surface that is not flippable.\0";
        case DDERR_NOTFOUND:
			return "Requested item was not found.\0";
        case DDERR_NOTLOCKED:
            return "Surface was not locked.  An attempt to unlock a surface that was not locked at all, or by this process, has been attempted.\0";
        case DDERR_NOTPALETTIZED:
            return "The surface being used is not a palette-based surface.\0";
        case DDERR_NOVSYNCHW:
            return "Operation could not be carried out because there is no hardware support for vertical blank synchronized operations.\0";
        case DDERR_NOZBUFFERHW:
            return "Operation could not be carried out because there is no hardware support for zbuffer blitting.\0";
        case DDERR_NOZOVERLAYHW:
			return "Overlay surfaces could not be z layered based on their BltOrder because the hardware does not support z layering of overlays.\0";
		case DDERR_OUTOFCAPS:
			return "The hardware needed for the requested operation has already been allocated.\0";
		case DDERR_OUTOFMEMORY:
			return "DirectDraw does not have enough memory to perform the operation.\0";
		case DDERR_OUTOFVIDEOMEMORY:
			return "DirectDraw does not have enough memory to perform the operation.\0";
		case DDERR_OVERLAYCANTCLIP:
			return "The hardware does not support clipped overlays.\0";
		case DDERR_OVERLAYCOLORKEYONLYONEACTIVE:
			return "Can only have ony color key active at one time for overlays.\0";
		case DDERR_OVERLAYNOTVISIBLE:
			return "Returned when GetOverlayPosition is called on a hidden overlay.\0";
		case DDERR_PALETTEBUSY:
			return "Access to this palette is being refused because the palette is already locked by another thread.\0";
		case DDERR_PRIMARYSURFACEALREADYEXISTS:
			return "This process already has created a primary surface.\0";
		case DDERR_REGIONTOOSMALL:
			return "Region passed to Clipper::GetClipList is too small.\0";
		case DDERR_SURFACEALREADYATTACHED:
			return "This surface is already attached to the surface it is being attached to.\0";
		case DDERR_SURFACEALREADYDEPENDENT:
			return "This surface is already a dependency of the surface it is being made a dependency of.\0";
		case DDERR_SURFACEBUSY:
			return "Access to this surface is being refused because the surface is already locked by another thread.\0";
		case DDERR_SURFACEISOBSCURED:
			return "Access to surface refused because the surface is obscured.\0";
		case DDERR_SURFACELOST:
			return "Access to this surface is being refused because the surface memory is gone. The DirectDrawSurface object representing this surface should have Restore called on it.\0";
		case DDERR_SURFACENOTATTACHED:
			return "The requested surface is not attached.\0";
		case DDERR_TOOBIGHEIGHT:
			return "Height requested by DirectDraw is too large.\0";
		case DDERR_TOOBIGSIZE:
			return "Size requested by DirectDraw is too large, but the individual height and width are OK.\0";
		case DDERR_TOOBIGWIDTH:
			return "Width requested by DirectDraw is too large.\0";
		case DDERR_UNSUPPORTED:
			return "Action not supported.\0";
		case DDERR_UNSUPPORTEDFORMAT:
			return "FOURCC format requested is unsupported by DirectDraw.\0";
		case DDERR_UNSUPPORTEDMASK:
			return "Bitmask in the pixel format requested is unsupported by DirectDraw.\0";
		case DDERR_VERTICALBLANKINPROGRESS:
			return "Vertical blank is in progress.\0";
		case DDERR_WASSTILLDRAWING:
			return "Informs DirectDraw that the previous Blt which is transfering information to or from this Surface is incomplete.\0";
		case DDERR_WRONGMODE:
			return "This surface can not be restored because it was created in a different mode.\0";
		case DDERR_XALIGN:
			return "Rectangle provided was not horizontally aligned on required boundary.\0";
		case D3DERR_BADMAJORVERSION:
			return "D3DERR_BADMAJORVERSION\0";
		case D3DERR_BADMINORVERSION:
			return "D3DERR_BADMINORVERSION\0";
		case D3DERR_EXECUTE_LOCKED:
			return "D3DERR_EXECUTE_LOCKED\0";
		case D3DERR_EXECUTE_NOT_LOCKED:
			return "D3DERR_EXECUTE_NOT_LOCKED\0";
		case D3DERR_EXECUTE_CREATE_FAILED:
			return "D3DERR_EXECUTE_CREATE_FAILED\0";
		case D3DERR_EXECUTE_DESTROY_FAILED:
			return "D3DERR_EXECUTE_DESTROY_FAILED\0";
		case D3DERR_EXECUTE_LOCK_FAILED:
			return "D3DERR_EXECUTE_LOCK_FAILED\0";
		case D3DERR_EXECUTE_UNLOCK_FAILED:
			return "D3DERR_EXECUTE_UNLOCK_FAILED\0";
		case D3DERR_EXECUTE_FAILED:
			return "D3DERR_EXECUTE_FAILED\0";
		case D3DERR_EXECUTE_CLIPPED_FAILED:
			return "D3DERR_EXECUTE_CLIPPED_FAILED\0";
		case D3DERR_TEXTURE_NO_SUPPORT:
			return "D3DERR_TEXTURE_NO_SUPPORT\0";
		case D3DERR_TEXTURE_NOT_LOCKED:
			return "D3DERR_TEXTURE_NOT_LOCKED\0";
		case D3DERR_TEXTURE_LOCKED:
			return "D3DERR_TEXTURELOCKED\0";
		case D3DERR_TEXTURE_CREATE_FAILED:
			return "D3DERR_TEXTURE_CREATE_FAILED\0";
		case D3DERR_TEXTURE_DESTROY_FAILED:
			return "D3DERR_TEXTURE_DESTROY_FAILED\0";
		case D3DERR_TEXTURE_LOCK_FAILED:
			return "D3DERR_TEXTURE_LOCK_FAILED\0";
		case D3DERR_TEXTURE_UNLOCK_FAILED:
			return "D3DERR_TEXTURE_UNLOCK_FAILED\0";
		case D3DERR_TEXTURE_LOAD_FAILED:
			return "D3DERR_TEXTURE_LOAD_FAILED\0";
		case D3DERR_MATRIX_CREATE_FAILED:
			return "D3DERR_MATRIX_CREATE_FAILED\0";
		case D3DERR_MATRIX_DESTROY_FAILED:
			return "D3DERR_MATRIX_DESTROY_FAILED\0";
		case D3DERR_MATRIX_SETDATA_FAILED:
			return "D3DERR_MATRIX_SETDATA_FAILED\0";
		case D3DERR_SETVIEWPORTDATA_FAILED:
			return "D3DERR_SETVIEWPORTDATA_FAILED\0";
		case D3DERR_MATERIAL_CREATE_FAILED:
			return "D3DERR_MATERIAL_CREATE_FAILED\0";
		case D3DERR_MATERIAL_DESTROY_FAILED:
			return "D3DERR_MATERIAL_DESTROY_FAILED\0";
		case D3DERR_MATERIAL_SETDATA_FAILED:
			return "D3DERR_MATERIAL_SETDATA_FAILED\0";
		case D3DERR_LIGHT_SET_FAILED:
			return "D3DERR_LIGHT_SET_FAILED\0";
		case D3DRMERR_BADOBJECT:
			return "D3DRMERR_BADOBJECT\0";
		case D3DRMERR_BADTYPE:
			return "D3DRMERR_BADTYPE\0";
		case D3DRMERR_BADALLOC:
			return "D3DRMERR_BADALLOC\0";
		case D3DRMERR_FACEUSED:
			return "D3DRMERR_FACEUSED\0";
		case D3DRMERR_NOTFOUND:
			return "D3DRMERR_NOTFOUND\0";
		case D3DRMERR_NOTDONEYET:
			return "D3DRMERR_NOTDONEYET\0";
		case D3DRMERR_FILENOTFOUND:
			return "The file was not found.\0";
		case D3DRMERR_BADFILE:
			return "D3DRMERR_BADFILE\0";
		case D3DRMERR_BADDEVICE:
			return "D3DRMERR_BADDEVICE\0";
		case D3DRMERR_BADVALUE:
			return "D3DRMERR_BADVALUE\0";
		case D3DRMERR_BADMAJORVERSION:
			return "D3DRMERR_BADMAJORVERSION\0";
		case D3DRMERR_BADMINORVERSION:
			return "D3DRMERR_BADMINORVERSION\0";
		case D3DRMERR_UNABLETOEXECUTE:
			return "D3DRMERR_UNABLETOEXECUTE\0";
		default:
			return "Unrecognized error value.\0";
		}
}

static void directx_check(HRESULT res)
{
#ifdef _DEBUG
	if( FAILED(res) )
	{
		msgout = fopen("goman95.deb", "at");
		fprintf(msgout, "Error : %s\n", DirectXErrorToString(res) );
		fclose (msgout);
	}
#endif //_DEBUG
}

long RLObjectGetReferenceCount(RLObject object)
{
	if (!object)
	{
		return 0;
	}
	object->lpVtbl->AddRef(object);
	return object->lpVtbl->Release(object);
}

#endif //_ITC_D3D_
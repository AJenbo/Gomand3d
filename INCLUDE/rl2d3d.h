//**************************************************************************
// rl2d3d.h
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
//
// Update:
//
//**************************************************************************
#ifndef _RL2D3D_H__
#define _RL2D3D_H__

#if !defined _47TEK_RL_ && !defined	_ITC_D3D_
#error Specify a platform RL or D3D first
#endif


/**************************************************************************
 *
 *	RenderMorphics version of GoMan
 *
 *************************************************************************/

#ifdef _47TEK_RL_

#ifndef __RL_H__
#include <rl.h>
#endif

//#ifndef __RLWIN_H__
//#include <rlwin.h>
//#endif

#endif //_47TEK_RL_


/**************************************************************************
 *
 *	Direct3D version of GoMan
 *
 *************************************************************************/
#ifdef _ITC_D3D_

#ifndef __D3DRMWIN_H__
#ifdef MINIWIN
#include "miniwin/d3drm.h"
#else
#include <d3drmwin.h>
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "tekanim.h"

static void directx_check(HRESULT);	        //type out error message to GOMAN95.DEB
char* DirectXErrorToString(HRESULT);    	//convert error code to error string.

#ifdef _DEBUG
#define DirectX_CHECK(result)    directx_check(result)
#else
#define DirectX_CHECK(result)
#endif

/*
 * objects redefined from RL to D3D
 */
typedef LPDIRECT3DRMOBJECT	        RLObject;
typedef LPDIRECT3DRMDEVICE	        RLDevice;
typedef LPDIRECT3DRMVIEWPORT        RLViewport;
typedef LPDIRECT3DRMFRAME	        RLFrame;
typedef LPDIRECT3DRMVISUAL	        RLVisual;
typedef LPDIRECT3DRMMESHBUILDER     RLMesh;
typedef LPDIRECT3DRMFACE	        RLFace;
typedef LPDIRECT3DRMLIGHT	        RLLight;
typedef LPDIRECT3DRMTEXTURE	        RLTexture;
typedef LPDIRECT3DRMMATERIAL		RLMaterial;
typedef LPDIRECT3DRMANIMATION		RLAnimation;
//typedef LPDIRECT3DRMANIMATIONSET	RLAnimationSet;
typedef TekAnimation                *RLAnimationSet;

typedef D3DLIGHTINGELEMENT	RLIMLightingPoint;
typedef D3DTLVERTEX			RLIMViewVertex;
typedef D3DTRIANGLE 		RLIMTriangle;
typedef DDSURFACEDESC		RLIMSurfaceInfo;
typedef D3DVALUE			RLIM16Value;

#define RLNoError					D3DRM_OK
/*
 * type redefined from RL to D3D
 */
typedef HRESULT		        		RLError;
typedef D3DVALUE	        		RLValue;
typedef D3DCOLOR            		RLColour;
typedef D3DVECTOR	        		RLVector;
typedef D3DRMVECTOR4D               RLVector4d;
typedef D3DRMBOX	        		RLBox;
typedef D3DRMIMAGE	        		RLImage;
typedef D3DRMMATRIX4D				RLMatrix4d;
typedef D3DRMCOMBINETYPE            RLCombineType; 
typedef D3DRMRENDERQUALITY			RLRenderQuality;
typedef D3DRMPALETTEENTRY			RLPaletteEntry;
typedef D3DRMFRAMECONSTRAINT 		RLFrameConstraint;
typedef D3DRMFRAMEMOVECALLBACK  	RLFrameCallback;



/*
 * macro redefine from RL to D3D
 */
#define RLVal(x)	        		D3DVAL(x)
#define RLInt(x)	        		(int)(x)
#define RLFloat(x)	        		(float)(x)
#define RLDivide(a,b)       		D3DDivide((a), (b))
#define RLMultiply(a,b)	    		D3DMultiply((a), (b))
#define RLMultiply3(a,b,c)  		D3DMultiply(D3DMultiply((a), (b)), (c))


/*
 * enumation redefined from RL to D3D
 */
//RLCombineType
#define RLCombineReplace 			D3DRMCOMBINE_REPLACE
#define RLCombineBefore  			D3DRMCOMBINE_BEFORE
#define RLCombineAfter   			D3DRMCOMBINE_AFTER

#define RLConstrainX	   			D3DRMCONSTRAIN_X
#define RLConstrainY				D3DRMCONSTRAIN_Y
#define RLConstrainZ				D3DRMCONSTRAIN_Z

#define RLColourRGB                 D3DCOLOR_RGB
#define RLColourRamp                D3DCOLOR_MONO 

#define RLRenderUnlitFlat           D3DRMRENDER_UNLITFLAT

#define RLBadObject                 D3DRMERR_BADOBJECT

#define RLMaterialFromMesh          D3DRMMATERIAL_FROMMESH
#define RLMaterialFromParent        D3DRMMATERIAL_FROMPARENT
#define RLMaterialFromFrame         D3DRMMATERIAL_FROMFRAME

#define RLPaletteFree               D3DRMPALETTE_FREE
#define RLPaletteReadOnly           D3DRMPALETTE_READONLY

#define _RLPaletteEntry             _D3DRMPALETTEENTRY


/*
 * functions redefined from RL to D3D
 */
#define	RLVectorModulus(v) \
		D3DRMVectorModulus(v)

#define RLVectorNormalise(v) \
		D3DRMVectorNormalise(v)

#define RLVectorScale(d, s, factor) \
		D3DRMVectorScale((d), (s), (factor))

#define RLVectorDotProduct(v1, v2) \
		D3DRMVectorDotProduct((v1), (v2))

#define	RLVectorSubtract(d, s1, s2) \
        D3DRMVectorSubtract((d), (s1), (s2))

#define RLVectorCrossProduct(d, s1, s2)	\
        D3DRMVectorCrossProduct((d), (s1), (s2))

#define RLVectorAdd(v, v1, v2) \
		D3DRMVectorAdd((v), (v1), (v2))

#define RLVectorReflect(v, v1, v2) \
		D3DRMVectorReflect((v), (v1), (v2))

#define RLCreateColourRGB(red, green, blue) \
        D3DRMCreateColorRGB((red), (green), (blue)) 

//for X file only
//#define RLAnimationSetSetTime(anim, time) \
//		(anim)->lpVtbl->SetTime((anim),(time))

#define RLFaceGetTextureCoordinates(face, which, u, v) \
		(face)->lpVtbl->GetTextureCoordinates((face), (which), (u), (v))

#define RLFaceGetColour(face) \
		(face)->lpVtbl->GetColor(face)

#define RLFrameGetVelocity(frame, scene, vector) \
		(frame)->lpVtbl->GetVelocity((frame), (scene), (vector), FALSE)

#define RLFrameSetVelocity(frame, scene, x, y, z) \
		(frame)->lpVtbl->SetVelocity((frame), (scene), (x), (y), (z), FALSE)

#define RLFrameGetOrientation(frame, reference, dir, up) \
		(frame)->lpVtbl->GetOrientation((frame), (reference), (dir), (up))

#define RLFrameSetOrientation(frame, reference, dx, dy, dz, ux, uy, uz) \
		(frame)->lpVtbl->SetOrientation((frame), (reference), \
										(dx), (dy), (dz), (ux), (uy), (uz))

#ifdef __cplusplus
#define RLFrameGetPosition(frame, reference, position) \
		(frame)->GetPosition((reference), (position))
#else
#define RLFrameGetPosition(frame, reference, position) \
		(frame)->lpVtbl->GetPosition((frame), (reference), (position))
#endif //__cplusplus

#define RLFrameSetPosition(frame, reference, x, y, z) \
		(frame)->lpVtbl->SetPosition((frame), (reference), (x), (y), (z))

#define RLFrameSetRotation(frame, reference, x, y, z, theta) \
		(frame)->lpVtbl->SetRotation((frame), (reference), (x), (y), (z), (theta))

#define RLFrameAddChild(frame, child) \
		(frame)->lpVtbl->AddChild((frame), (child))

#define RLFrameRemoveChild(frame, child) \
		(frame)->lpVtbl->DeleteChild((frame), (child))

#define RLFrameAddTransform(frame, combine, matrix) \
		(frame)->lpVtbl->AddTransform((frame), (combine), (matrix))

#define RLFrameAddScale(frame, combine, sx, sy, sz) \
		(frame)->lpVtbl->AddScale((frame), (combine), (sx), (sy), (sz))

#define RLFrameLookAt(frame, target, ref, constraint) \
		(frame)->lpVtbl->LookAt((frame), (target), (ref), (constraint))

#define RLFrameAddCallback(frame,fn,arg) \
		(frame)->lpVtbl->AddMoveCallback((frame), (fn), (arg))

#define RLFrameRemoveCallback(frame, fn, arg) \
		(frame)->lpVtbl->DeleteMoveCallback((frame), (fn), (arg))

#define RLFrameRemoveVisual(frame, visual) \
		(frame)->lpVtbl->DeleteVisual((frame), (visual))

#define RLSceneSetBackgroundRGB(frame, red, green, blue) \
		(frame)->lpVtbl->SetSceneBackgroundRGB((frame), (red), (green), (blue))

#define RLFrameTransform(frame, dest, source) \
		(frame)->lpVtbl->Transform((frame), (dest), (source))

#define RLFrameInverseTransform(frame, dest, source) \
		(frame)->lpVtbl->InverseTransform((frame), (dest), (source))

#define RLFrameAddVisual(frame, visual) \
		(frame)->lpVtbl->AddVisual((frame), (visual))

#define RLFrameSetColour(frame, colour) \
		(frame)->lpVtbl->SetColor((frame), (colour))

#define RLFrameSetMaterialMode(frame, mode) \
		(frame)->lpVtbl->SetMaterialMode((frame), (mode))

#define RLFrameMove(frame) \
        (frame)->lpVtbl->Move(frame, (D3DVALUE)1.0)

#define RLMeshGetBox(mesh, box) \
		(mesh)->lpVtbl->GetBox((mesh), (box))

#define RLMeshScale(mesh, sx, sy, sz) \
		(mesh)->lpVtbl->Scale((mesh), (sx), (sy), (sz))

#define RLMeshSetQuality(mesh, quality) \
		(mesh)->lpVtbl->SetQuality((mesh), (quality))

#define RLMeshGetFaceCount(mesh) \
		(mesh)->lpVtbl->GetFaceCount(mesh)

#define RLMeshGetVertexCount(mesh) \
		(mesh)->lpVtbl->GetVertexCount(mesh)

#define RLMeshSetColourRGB(mesh, red, green, blue) \
        (mesh)->lpVtbl->SetColorRGB(mesh, red, green, blue)

#define RLObjectExists(object) \
        (((object) == NULL) ? D3DRMERR_BADOBJECT : D3DRM_OK)

#define RLTextureSetShades(texture, shades) \
		(texture)->lpVtbl->SetShades((texture), (shades))

#define RLViewportTransform(view, dest, src) \
		(view)->lpVtbl->Transform((view), (dest), (src))

#define RLViewportInverseTransform(view, dest, src) \
		(view)->lpVtbl->InverseTransform((view), (dest), (src))

#define RLViewportGetX(view) \
        (int) (view)->lpVtbl->GetX(view)

#define RLViewportGetY(view) \
        (int) (view)->lpVtbl->GetY(view)

#define RLViewportGetWidth(view) \
        (int) (view)->lpVtbl->GetWidth(view)

#define RLViewportGetHeight(view) \
        (int) (view)->lpVtbl->GetHeight(view)

#define RLViewportForceUpdate(view, x1, y1, x2, y2) \
        (view)->lpVtbl->ForceUpdate(view, (DWORD)x1, (DWORD)y1, (DWORD)x2, (DWORD)y2)

#define RLViewportClear(view) \
        (view)->lpVtbl->Clear(view) 

#define RLViewportRender(view, scene) \
        (view)->lpVtbl->Render(view, scene) 

#define RLViewportSetBack(view, back) \
        (view)->lpVtbl->SetBack((view), (back))

#define RLWinHandlePaint(dev, hdc) \
        ((dev)->lpVtbl->HandlePaint((dev), (hdc))

#define RLDeviceUpdate(dev) \
        (dev)->lpVtbl->Update(dev)

#define RLDeviceGetWidth(dev) \
        (int) (dev)->lpVtbl->GetWidth(dev)

#define RLDeviceGetHeight(dev) \
        (int) (dev)->lpVtbl->GetHeight(dev)

#define RLDeviceSetShades(dev, shades) \
        (dev)->lpVtbl->SetShades((dev), (shades))

#define RLDeviceSetDither(dev, bDither) \
        (dev)->lpVtbl->SetDither((dev), (bDither))

#define RLDeviceSetQuality(dev, quality) \
        (dev)->lpVtbl->SetQuality(dev, quality)

/*
 * functions substitution with another function
 */

RLError 	RLMalloc( void** p_return, size_t size );
void 		RLFree( void* p );
size_t		RLGetTotalAllocated( void );

RLObject 	RLObjectFromName( const char* name );
RLError		RLObjectDestroy( RLObject object );
RLFrame		RLCreateFrame(RLFrame parent);

const char*	RLObjectGetClassName( RLObject object );
long 		RLObjectGetReferenceCount(RLObject object);

RLFrame		RLFrameGetParent( RLFrame frame );
RLFrame		RLFrameGetScene ( RLFrame frame );
RLError 	RLFrameGetVisuals (RLFrame frame, int * count, RLVisual** visuals);
RLError 	RLFrameGetChildren(RLFrame parent,int * count, RLFrame ** children);

RLMaterial 	RLFaceGetMaterial( RLFace face );
RLTexture   RLLoadTexture(const char * fileName);
void        RLTextureSetDefaultShades(int shades);
RLMaterial  RLCreateMaterial(RLValue ks, RLValue power);
void        RLTextureSetDefaultColours(int colors);
RLViewport  RLCreateViewport(RLDevice dev, RLFrame camera,
                             int x, int y, int width, int height);

RLMesh 		RLLoadMesh( const char *name );
RLError		RLMeshSetColour( RLMesh, RLColour );
RLError		RLMeshGetFaces ( RLMesh mesh, int* count, RLFace** faces );
RLError		RLMeshGetVertices(  RLMesh mesh,
								int* vertex_count, RLVector** vertices,
								int* normal_count, RLVector** normals,
								int** face_data );

RLColour 	RLCreateColourRGBA(	RLValue red, RLValue green,
								RLValue blue, RLValue alpha);

#ifdef __cplusplus
};
#endif

#endif //_ITC_D3D_

#endif //_RL2D3D_H__
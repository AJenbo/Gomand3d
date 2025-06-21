/*==========================================================================
$Header:   H:/pvcs/pvcsproj/gomand3d.prj/rmdemo.h_v   1.1   07 Nov 1996 10:53:44   JEREMIAH  $

$Log:   H:/pvcs/pvcsproj/gomand3d.prj/rmdemo.h_v  $
 * 
 *    Rev 1.1   07 Nov 1996 10:53:44   JEREMIAH
 * Cleaned up unused function prototype.
 ***************************************************************************/
#ifndef __RMDEMO_H__
#define __RMDEMO_H__

#include "d3drmwin.h"
#include "d3drm.h"
#include "rmerror.h"

#undef RELEASE
#ifdef __cplusplus
#define RELEASE(x) if (x != NULL) {x->Release(); x = NULL;}
#else
#define RELEASE(x) if (x != NULL) {x->lpVtbl->Release(x); x = NULL;}
#endif

#ifdef __cplusplus
extern "C" {
#endif
    /*
     * A copy of LPDIRECT3DRM for use by the examples.
     */
    extern LPDIRECT3DRM lpD3DRM;
    /*
     * Builds the scene.
     */
    BOOL BuildScene(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view, LPDIRECT3DRMFRAME scene,
                        LPDIRECT3DRMFRAME camera);

    /*
     * Allows each example to begin with different defaults
     */
    typedef struct Defaultstag {
        BOOL bNoTextures;
        BOOL bResizingDisabled;
        BOOL bConstRenderQuality;
        char Name[50];
    } Defaults;
    //void OverrideDefaults(Defaults* defaults);

#ifdef __cplusplus
};
#endif

#endif  //__RMDEMO_H__


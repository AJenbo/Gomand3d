#pragma once

#include "d3drmmesh_impl.h"
#include "mathutils.h"
#include "miniwin/d3drm.h"
#include "miniwin/miniwindevice.h"
#include "structs.h"

#include <SDL3/SDL.h>

#define NO_TEXTURE_ID 0xffffffff

static_assert(sizeof(D3DRMVERTEX) == 32);

struct SceneLight {
	FColor color;
	D3DVECTOR position;
	float positional = 0.f; // position is valid if 1.f
	D3DVECTOR direction;
	float directional = 0.f; // direction is valid if 1.f
};
static_assert(sizeof(SceneLight) == 48);

struct Plane {
	D3DVECTOR normal;
	float d;
};

class Direct3DRMRenderer : public IDirect3DDevice2 {
public:
	virtual void PushLights(const SceneLight* vertices, size_t count) = 0;
	virtual void SetProjection(const D3DRMMATRIX4D& projection, D3DVALUE front, D3DVALUE back) = 0;
	virtual void SetFrustumPlanes(const Plane* frustumPlanes) = 0;
	virtual Uint32 GetTextureId(IDirect3DRMTexture* texture) = 0;
	virtual Uint32 GetMeshId(IDirect3DRMMesh* mesh, const MeshGroup* meshGroup) = 0;
	DWORD GetWidth() { return m_width; }
	DWORD GetHeight() { return m_height; }
	virtual void GetDesc(D3DDEVICEDESC* halDesc, D3DDEVICEDESC* helDesc) = 0;
	virtual const char* GetName() = 0;
	virtual HRESULT BeginFrame() = 0;
	virtual void EnableTransparency() = 0;
	virtual void SubmitDraw(
		DWORD meshId,
		const D3DRMMATRIX4D& modelViewMatrix,
		const Matrix3x3& normalMatrix,
		const Appearance& appearance
	) = 0;
	virtual HRESULT FinalizeFrame() = 0;
	virtual bool ConvertEventToRenderCoordinates(SDL_Event* event) { return true; }
	virtual void Clear(float r, float g, float b) = 0;
	virtual void Flip() = 0;
	virtual void Draw2DImage(Uint32 textureId, const SDL_Rect& srcRect, const SDL_Rect& dstRect) = 0;
	virtual void Download(SDL_Surface* target) = 0;

protected:
	DWORD m_width, m_height;
};

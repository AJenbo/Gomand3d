#pragma once

#include "d3drmrenderer.h"
#include "d3drmtexture_impl.h"
#include "ddraw_impl.h"

#include <SDL3/SDL.h>
#include <cstddef>
#include <vector>

DEFINE_GUID(SOFTWARE_GUID, 0x682656F3, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02);

struct TextureCache {
	Direct3DRMTextureImpl* texture;
	Uint8 version;
	SDL_Surface* cached;
};

struct MeshCache {
	const MeshGroup* meshGroup;
	int version;
	bool flat;
	std::vector<D3DRMVERTEX> vertices;
	std::vector<uint16_t> indices;
};

class Direct3DRMSoftwareRenderer : public Direct3DRMRenderer {
public:
	Direct3DRMSoftwareRenderer(DWORD width, DWORD height);
	~Direct3DRMSoftwareRenderer() override;
	void PushLights(const SceneLight* vertices, size_t count) override;
	Uint32 GetTextureId(IDirect3DRMTexture* texture) override;
	Uint32 GetMeshId(IDirect3DRMMesh* mesh, const MeshGroup* meshGroup) override;
	void SetProjection(const D3DRMMATRIX4D& projection, D3DVALUE front, D3DVALUE back) override;
	void SetFrustumPlanes(const Plane* frustumPlanes) override;
	void GetDesc(D3DDEVICEDESC* halDesc, D3DDEVICEDESC* helDesc) override;
	const char* GetName() override;
	HRESULT BeginFrame() override;
	void EnableTransparency() override;
	void SubmitDraw(
		DWORD meshId,
		const D3DRMMATRIX4D& modelViewMatrix,
		const Matrix3x3& normalMatrix,
		const Appearance& appearance
	) override;
	HRESULT FinalizeFrame() override;
	void Clear(float r, float g, float b) override;
	void Flip() override;
	void Draw2DImage(Uint32 textureId, const SDL_Rect& srcRect, const SDL_Rect& dstRect) override;
	void Download(SDL_Surface* target) override;

private:
	void ClearZBuffer();
	void DrawTriangleProjected(
		const D3DRMVERTEX& v0,
		const D3DRMVERTEX& v1,
		const D3DRMVERTEX& v2,
		const Appearance& appearance
	);
	void DrawTriangleClipped(const D3DRMVERTEX (&v)[3], const Appearance& appearance);
	void ProjectVertex(const D3DVECTOR& v, D3DRMVECTOR4D& p) const;
	Uint32 BlendPixel(Uint8* pixelAddr, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	SDL_Color ApplyLighting(const D3DVECTOR& position, const D3DVECTOR& normal, const Appearance& appearance);
	void AddTextureDestroyCallback(Uint32 id, IDirect3DRMTexture* texture);
	void AddMeshDestroyCallback(Uint32 id, IDirect3DRMMesh* mesh);

	DWORD m_width;
	DWORD m_height;
	SDL_Surface* m_renderedImage;
	SDL_Palette* m_palette;
	const SDL_PixelFormatDetails* m_format;
	int m_bytesPerPixel;
	std::vector<SceneLight> m_lights;
	std::vector<TextureCache> m_textures;
	std::vector<MeshCache> m_meshs;
	D3DVALUE m_front;
	D3DVALUE m_back;
	Matrix3x3 m_normalMatrix;
	D3DRMMATRIX4D m_projection;
	std::vector<float> m_zBuffer;
	std::vector<D3DRMVERTEX> m_transformedVerts;
	Plane m_frustumPlanes[6];
};

inline static void Direct3DRMSoftware_EnumDevice(LPD3DENUMDEVICESCALLBACK cb, void* ctx)
{
	Direct3DRMRenderer* device = nullptr;
	device = new Direct3DRMSoftwareRenderer(640, 480);
	EnumDevice(cb, ctx, device, SOFTWARE_GUID);
	delete device;
}

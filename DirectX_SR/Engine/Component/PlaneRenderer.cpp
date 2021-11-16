#include "pch.h"
#include "PlaneRenderer.h"
#include "Quad.h"
#include "Texture.h"
#include "Transform.h"

namespace ce
{
	PlaneRenderer::PlaneRenderer(LPDIRECT3DDEVICE9 pDevice, Texture* texture, int x, int z) noexcept :
		Renderer(pDevice),
		_quad(nullptr),
		_x(x),
		_z(z)
	{
		if (texture != nullptr)
			_material.SetMainTexture(texture);
	}

	void PlaneRenderer::Init(void) noexcept
	{
		_owner->SetLayer(GameObjectLayer::BACKGROUND);

		float x2 = 1, y2 = 1;

		if (_material.GetMainTexture() != nullptr)
		{
			x2 = _material.GetMainTexture()->Width();
			y2 = _material.GetMainTexture()->Height();
		}

		_quad = new Quad(_x, _z, _x, _z);
		_quad->Open(_pDevice);

		_transform = _owner->GetTransform();
	}

	void PlaneRenderer::Render(void) noexcept
	{
		_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

		_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
		_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

		DWORD cull = 0;
		//_pDevice->GetRenderState(D3DRS_CULLMODE, &cull);
		_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		_pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
		//_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		//_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		//_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		//_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		//_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		//_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		//_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		//_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		//_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

		//_pDevice->SetTextureStageState(0, D3DTSS_CONSTANT, _material.GetColor());
		//_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CONSTANT);
		//_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		//_pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);


		_pDevice->SetTransform(D3DTS_WORLD, &_transform->GetWorldMatrix());

		_material.Render(_pDevice);
		_quad->Render(_pDevice);

		//_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		//_pDevice->SetRenderState(D3DRS_CULLMODE, cull);
	}
	
	void PlaneRenderer::Release(void) noexcept
	{
		delete _quad;
		_quad = nullptr;
	}

	void PlaneRenderer::SetTexture(Texture* texture) noexcept
	{
		_material.SetMainTexture(texture);

		float x2 = 1, y2 = 1;

		if (texture != nullptr)
		{
			x2 = _material.GetMainTexture()->Width();
			y2 = _material.GetMainTexture()->Height();
		}

		_quad->Close();
		_quad->SetInterval(_x, _z);
		_quad->SetMaxUV(_x, _z);

		_quad->Open(_pDevice);
	}

	void PlaneRenderer::SetColor(D3DXCOLOR c) noexcept
	{
		_material.SetColor(c);
	}
}
#include "pch.h"
#include "SpriteRenderer.h"
#include "Quad.h"
#include "Texture.h"
#include "Transform.h"

namespace ce
{
	SpriteRenderer::SpriteRenderer(LPDIRECT3DDEVICE9 pDevice, Texture* texture, bool lightEnable) noexcept :
		Renderer(pDevice),
		_quad(nullptr),
		_lightEnable(lightEnable)
	{
		if (texture != nullptr)
			_material.SetMainTexture(texture);
	}

	void SpriteRenderer::Init(void) noexcept
	{
		_owner->SetLayer(GameObjectLayer::ALPHA);

		float x = 1, y = 1;
		float x2 = 1, y2 = 1;

		if (_material.GetMainTexture() != nullptr)
		{
			x = _material.GetMainTexture()->LoadedWidth();
			y = _material.GetMainTexture()->LoadedHeight();

			x2 = _material.GetMainTexture()->Width();
			y2 = _material.GetMainTexture()->Height();
		}

		_quad = new Quad(x2 / 100.f, y2 / 100.f, x2 / x, y2 / y);
		_quad->Open(_pDevice);
		
		_transform = _owner->GetTransform();
	}

	void SpriteRenderer::Render(void) noexcept
	{
		//_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		//_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

		_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
		_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

		DWORD flag = 0;
		_pDevice->GetRenderState(D3DRS_LIGHTING, &flag);

		if (_lightEnable == false)
			_pDevice->SetRenderState(D3DRS_LIGHTING, false);

		_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		_pDevice->SetTransform(D3DTS_WORLD, &_transform->GetWorldMatrix());

		_material.Render(_pDevice);
		_quad->Render(_pDevice);

		_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		_pDevice->SetRenderState(D3DRS_LIGHTING, flag);
	}

	void SpriteRenderer::Release(void) noexcept
	{
		delete _quad;
		_quad = nullptr;
	}

	void SpriteRenderer::SetTexture(Texture* texture) noexcept
	{
		_material.SetMainTexture(texture);

		float x = 1, y = 1;
		float x2 = 1, y2 = 1;

		if (texture != nullptr)
		{
			x = _material.GetMainTexture()->LoadedWidth();
			y = _material.GetMainTexture()->LoadedHeight();

			x2 = _material.GetMainTexture()->Width();
			y2 = _material.GetMainTexture()->Height();
		}

		_quad->Close();
		_quad->SetInterval(x2, y2);
		_quad->SetMaxUV(x2 / x, y2 / y);

		_quad->Open(_pDevice);
	}

	void SpriteRenderer::SetColor(D3DXCOLOR c) noexcept
	{
		_material.SetColor(c);
	}
}
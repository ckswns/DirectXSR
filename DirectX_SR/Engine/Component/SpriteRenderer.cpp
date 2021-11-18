#include "pch.h"
#include "SpriteRenderer.h"
#include "Quad.h"
#include "Texture.h"
#include "Transform.h"
#include "GameObject.h"

namespace ce
{
	SpriteRenderer::SpriteRenderer(LPDIRECT3DDEVICE9 pDevice, Texture* texture, bool lightEnable, DWORD cullingOption) noexcept :
		Renderer(pDevice),
		_quad(nullptr),
		_lightEnable(lightEnable),
		_cullOption(cullingOption)
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
		_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
		_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

		DWORD flag = 0, cull = 0;
		_pDevice->GetRenderState(D3DRS_LIGHTING, &flag);
		_pDevice->GetRenderState(D3DRS_CULLMODE, &cull);

		if (_lightEnable == false)
			_pDevice->SetRenderState(D3DRS_LIGHTING, false);

		_pDevice->SetRenderState(D3DRS_CULLMODE, _cullOption);
		//_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		//_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		//_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		_pDevice->SetRenderState(D3DRS_ALPHAREF, 50);

		//_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		//_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		//_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		//_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		//_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

		_pDevice->SetTextureStageState(0, D3DTSS_CONSTANT, _material.GetColor());
		//_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CONSTANT);
		//_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		//_pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);


		_pDevice->SetTransform(D3DTS_WORLD, &_transform->GetWorldMatrix());

		_material.Render(_pDevice);
		_quad->Render(_pDevice);

		_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		//_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		//_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		_pDevice->SetRenderState(D3DRS_LIGHTING, flag);
		_pDevice->SetRenderState(D3DRS_CULLMODE, cull);
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
		_quad->SetInterval(x2 / 100.f, y2 / 100.f);
		_quad->SetMaxUV(x2 / x, y2 / y);

		_quad->Open(_pDevice);
	}

	void SpriteRenderer::SetColor(D3DXCOLOR c) noexcept
	{
		_material.SetColor(c);
	}
}
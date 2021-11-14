#include "pch.h"
#include "SpriteRenderer.h"
#include "Quad.h"
#include "Texture.h"
#include "Transform.h"

namespace ce
{
	SpriteRenderer::SpriteRenderer(LPDIRECT3DDEVICE9 pDevice, Texture* texture) noexcept :
		Renderer(pDevice),
		_quad(nullptr)
	{
		if (texture != nullptr)
			_material.SetMainTexture(texture);
	}

	void SpriteRenderer::Init(void) noexcept
	{
		_owner->SetLayer(GameObjectLayer::ALPHA);

		float x = 1, y = 1;

		if (_material.GetMainTexture() != nullptr)
		{
			x = _material.GetMainTexture()->Width() / 100.f;
			y = _material.GetMainTexture()->Height() / 100.f;
		}

		_quad = new Quad(x, y);
		_quad->Open(_pDevice);

		_transform = _owner->GetTransform();
	}

	void SpriteRenderer::Render(void) noexcept
	{
		_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		_pDevice->SetTransform(D3DTS_WORLD, &_transform->GetWorldMatrix());

		_material.Render(_pDevice);
		_quad->Render(_pDevice);

		_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
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
		
		if (texture != nullptr)
		{
			x = _material.GetMainTexture()->Width() / 100.f;
			y = _material.GetMainTexture()->Height() / 100.f;
		}

		_quad->Close();
		_quad->SetInterval(x, y);
		_quad->Open(_pDevice);
	}

	void SpriteRenderer::SetColor(D3DXCOLOR c) noexcept
	{
		_material.SetColor(c);
	}
}
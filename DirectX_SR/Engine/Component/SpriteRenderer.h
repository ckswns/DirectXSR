#pragma once
#include "Renderer.h"

namespace ce
{
	class Transform;
	class Texture;
	class Quad;

	class SpriteRenderer : public Renderer
	{
	public:		explicit	SpriteRenderer(void) noexcept = delete;
	public:		explicit	SpriteRenderer(LPDIRECT3DDEVICE9 pDevice, Texture* texture = nullptr, bool lightEnable = true, DWORD cullingOption = D3DCULL_CCW) noexcept;
	public:		virtual		~SpriteRenderer(void) noexcept { __noop; }

	public:		void		Init(void) noexcept override;
	public:		void		Render(void) noexcept override;
	public:		void		Release(void) noexcept override;

	public:		void		SetTexture(Texture* texture) noexcept;
	public:		void		SetColor(D3DXCOLOR c) noexcept;

	private:	bool		_lightEnable = true;
	private:	Quad*		_quad;
	private:	Transform*	_transform;
	private:	DWORD		_cullOption;
	};
}

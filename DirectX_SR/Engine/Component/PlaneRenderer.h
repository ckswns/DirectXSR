#pragma once
#include "Renderer.h"

namespace ce
{
	class Transform;
	class Texture;
	class Quad;

	class PlaneRenderer : public Renderer
	{
	public:		explicit	PlaneRenderer(void) noexcept = delete;
	public:		explicit	PlaneRenderer(LPDIRECT3DDEVICE9 pDevice, Texture* texture = nullptr, int x = 1, int z = 1) noexcept;
	public:		virtual		~PlaneRenderer(void) noexcept { __noop; }

	public:		void		Init(void) noexcept override;
	public:		void		Render(void) noexcept override;
	public:		void		Release(void) noexcept override;

	public:		void		SetTexture(Texture* texture) noexcept;
	public:		void		SetColor(D3DXCOLOR c) noexcept;

	private:	Quad*		_quad;
	private:	Transform*	_transform;
	private:	float		_x;
	private:	float		_z;
	};
}

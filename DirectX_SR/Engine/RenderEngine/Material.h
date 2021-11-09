#pragma once
#include "Texture.h"

namespace ce
{
	class Material
	{
	public:		explicit				Material(void) noexcept;
	public:		virtual					~Material(void) noexcept { __noop; }

	public:		void					SetColor(D3DCOLORVALUE c) noexcept { _mat.Diffuse = c; }

	public:		D3DCOLORVALUE			GetColor(void) const noexcept { return _mat.Diffuse; }

	public:		void					SetTexture(Texture* pTexture) noexcept;
	public:		Texture*				GetTexture() noexcept { return _texture; }
	public:		const D3DMATERIAL9&		GetNativeMaterial(void) const noexcept { return _mat; }

	public:		void					Render(LPDIRECT3DDEVICE9 pDevice) noexcept;

	private:	D3DMATERIAL9			_mat;
	private:	Texture*				_texture;
	};
}

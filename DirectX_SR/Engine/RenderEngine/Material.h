#pragma once
#include "Texture.h"

namespace ce
{
	class Material
	{
	public:		explicit				Material(void) noexcept;
	public:		virtual					~Material(void) noexcept { __noop; }

	public:		void					SetColor(D3DXCOLOR c) noexcept;
	public:		void					SetColor(D3DCOLORVALUE c) noexcept { _mat.Diffuse = c; }
	public:		D3DXCOLOR				GetColor(void) const noexcept;

	public:		void					SetTextures(const Texture::TList& textures) noexcept;
	public:		Texture*				GetTexture(uint32 index) noexcept;

	public:		void					SetMainTexture(Texture* pTexture) noexcept;
	public:		Texture*				GetMainTexture(void) const noexcept;

	public:		int						GetTextureLength(void) const noexcept { return _textures.size(); }

	public:		const D3DMATERIAL9&		GetNativeMaterial(void) const noexcept { return _mat; }

	public:		void					Render(LPDIRECT3DDEVICE9 pDevice) noexcept;

	private:	D3DMATERIAL9			_mat;
	private:	Texture::TList			_textures;
	};
}

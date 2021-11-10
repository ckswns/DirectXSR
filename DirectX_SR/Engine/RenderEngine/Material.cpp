#include "pch.h"
#include "Material.h"
#include "Assertion.h"

namespace ce
{
	Material::Material(void) noexcept 
	{
		//ZeroMemory(&_mat, sizeof(D3DXMATERIAL));

		_mat.Diffuse.r = 1;
		_mat.Diffuse.g = 1;
		_mat.Diffuse.b = 1;
		_mat.Diffuse.a = 1;
	}

	void Material::SetColor(D3DXCOLOR c) noexcept
	{
		_mat.Diffuse.r = c.r / 255.f;
		_mat.Diffuse.g = c.g / 255.f;
		_mat.Diffuse.b = c.b / 255.f;
		_mat.Diffuse.a = c.a / 255.f;
	}

	D3DXCOLOR Material::GetColor(void) const noexcept
	{
		return D3DXCOLOR(_mat.Diffuse.r * 255,
						_mat.Diffuse.g * 255,
						_mat.Diffuse.b * 255,
						_mat.Diffuse.a	* 255
					);
	}

	void Material::SetTextures(const Texture::TList& textures) noexcept
	{
		_textures.assign(textures.begin(), textures.end());
	}

	Texture* Material::GetTexture(uint32 index) noexcept
	{
		if (_textures.size() <= index)
		{
			CE_ASSERT("ckswns", "배열의 크기를 초과하는 요청입니다");
			return nullptr;
		}

		return _textures[index];
	}

	void Material::SetMainTexture(Texture* pTexture) noexcept
	{
		if (_textures.empty())
			_textures.push_back(pTexture);
		else
			_textures[0] = pTexture;
	}

	Texture* Material::GetMainTexture(void) const noexcept
	{
		if(_textures.empty())
			return nullptr;

		return _textures[0];
	}

	void Material::Render(LPDIRECT3DDEVICE9 pDevice) noexcept
	{
		if (pDevice == nullptr)
			CE_ASSERT("ckswns", "Devcie객체가 nullptr입니다");

		if (_textures.empty())
			pDevice->SetTexture(0, nullptr);
		else
		{
			for (int i = 0; i < _textures.size(); i++)
				pDevice->SetTexture(i, _textures[i]->GetTexturePTR());
		}

		pDevice->SetMaterial(&_mat);
	}
}

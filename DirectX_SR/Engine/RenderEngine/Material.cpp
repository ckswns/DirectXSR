#include "pch.h"
#include "Material.h"
#include "Assertion.h"

namespace ce
{
	Material::Material(void) noexcept 
	{
		//ZeroMemory(&_mat, sizeof(D3DXMATERIAL));

		_mat.Diffuse.r = /*_mat.Ambient.r = */1;
		_mat.Diffuse.g = /*_mat.Ambient.g = */1;
		_mat.Diffuse.b = /*_mat.Ambient.b = */1;
		_mat.Diffuse.a = /*_mat.Ambient.a = */1;
	}

	void Material::SetColor(D3DXCOLOR c) noexcept
	{
		_mat.Diffuse.r = /*_mat.Ambient.r = */c.r;
		_mat.Diffuse.g = /*_mat.Ambient.g = */c.g;
		_mat.Diffuse.b = /*_mat.Ambient.b = */c.b;
		_mat.Diffuse.a = /*_mat.Ambient.a = */c.a;
	}

	D3DXCOLOR Material::GetColor(void) const noexcept
	{
		return D3DCOLOR_RGBA(
						(long)(_mat.Diffuse.r * 255),
						(long)(_mat.Diffuse.g * 255),
						(long)(_mat.Diffuse.b * 255),
						(long)(_mat.Diffuse.a * 255)
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
			CE_ASSERT("ckswns", "�迭�� ũ�⸦ �ʰ��ϴ� ��û�Դϴ�");
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
			CE_ASSERT("ckswns", "Devcie��ü�� nullptr�Դϴ�");

		if (_textures.empty())
			pDevice->SetTexture(0, nullptr);
		else
		{
			for (int i = 0; i < _textures.size(); i++)
			{
				if(_textures[i] == nullptr)
					pDevice->SetTexture(i, nullptr);
				else
					pDevice->SetTexture(i, _textures[i]->GetTexturePTR());
			}
		}

		pDevice->SetMaterial(&_mat);
	}

	void Material::Render(LPDIRECT3DDEVICE9 pDevice, int index) noexcept
	{
		if (pDevice == nullptr)
			CE_ASSERT("ckswns", "Devcie��ü�� nullptr�Դϴ�");

		if (_textures.size() <= index)
			CE_ASSERT("ckswns", "�ε����� �迭�� ������ ������ϴ�.");

		if (_textures[index] == nullptr)
			pDevice->SetTexture(index, nullptr);
		else
			pDevice->SetTexture(index, _textures[index]->GetTexturePTR());

		pDevice->SetMaterial(&_mat);
	}
}

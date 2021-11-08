#include "pch.h"
#include "Material.h"
#include "Assertion.h"

namespace ce
{
	Material::Material(void) noexcept 
	{
		ZeroMemory(&_mat, sizeof(D3DXMATERIAL));

		_mat.Diffuse.r = 1;
		_mat.Diffuse.g = 1;
		_mat.Diffuse.b = 1;
		_mat.Diffuse.a = 1;
	}

	void Material::SetTexture(Texture* pTexture) noexcept
	{
		_texture = pTexture;
	}

	void Material::Render(LPDIRECT3DDEVICE9 pDevice) noexcept
	{
		if (pDevice == nullptr)
			CE_ASSERT("ckswns", "Devcie객체가 nullptr입니다");

		if (_texture != nullptr)
			pDevice->SetTexture(0, _texture->GetTexturePTR());
		else
			pDevice->SetTexture(0, nullptr);
		pDevice->SetMaterial(&_mat);
	}
}

#include "pch.h"
#include "../Base/Assertion.h"
#include "Texture.h"

namespace ce
{
	bool Texture::Init(LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR filePath) noexcept
	{
		if (FAILED(D3DXCreateTextureFromFileA(pd3dDevice, filePath, &_pTexture)))
		{
			_pTexture = NULL;

			CE_ASSERT("ckswns", "텍스쳐 생성에 실패하였습니다!");
			return false;
		}

		_filePathA = filePath; 
		_filePathW.assign(_filePathA.begin(), _filePathA.end());

		return true;
	}

	void Texture::Release(void) noexcept
	{
		if (_pTexture)
		{
			_pTexture->Release();
			_pTexture = nullptr;
		}
	}

	uint32 Texture::Width(void) const noexcept
	{
		D3DSURFACE_DESC desc;

		_pTexture->GetLevelDesc(0, &desc);
		return desc.Width;
	}

	uint32 Texture::Height(void) const noexcept
	{
		D3DSURFACE_DESC desc;

		_pTexture->GetLevelDesc(0, &desc);
		return desc.Height;
	}

	Texture::~Texture(void) noexcept
	{
		if (_pTexture != nullptr)
			_pTexture->Release();
	}
}
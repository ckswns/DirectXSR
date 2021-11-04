#include "pch.h"
#include "../Base/Assertion.h"
#include "Texture.h"

namespace ce
{
	bool Texture::Init(LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR filePath) noexcept
	{
		_filePathA = filePath;
		_filePathW.assign(_filePathA.begin(), _filePathA.end());

		size_t split = _filePathA.find('.');
		std::string fileExtension = _filePathA.substr(split);

		if (fileExtension == ".dds")
		{
			if (FAILED(D3DXCreateCubeTextureFromFileA(pd3dDevice, filePath, (LPDIRECT3DCUBETEXTURE9*)&_pTexture)))
			{
				_pTexture = NULL;

				CE_ASSERT("ckswns", "텍스쳐 생성에 실패하였습니다!");
				return false;
			}

			_type = Texture::Type::CUBE;
		}
		else
		{
			if (FAILED(D3DXCreateTextureFromFileA(pd3dDevice, filePath, (LPDIRECT3DTEXTURE9*)&_pTexture)))
			{
				_pTexture = NULL;

				CE_ASSERT("ckswns", "텍스쳐 생성에 실패하였습니다!");
				return false;
			}

			_type = Texture::Type::DEFAULT;
		}

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

		if(_type == Type::DEFAULT)
			static_cast<LPDIRECT3DTEXTURE9>(_pTexture)->GetLevelDesc(0, &desc);
		else
			static_cast<LPDIRECT3DCUBETEXTURE9>(_pTexture)->GetLevelDesc(0, &desc);
		return desc.Width;
	}

	uint32 Texture::Height(void) const noexcept
	{
		D3DSURFACE_DESC desc;

		if (_type == Type::DEFAULT)
			static_cast<LPDIRECT3DTEXTURE9>(_pTexture)->GetLevelDesc(0, &desc);
		else
			static_cast<LPDIRECT3DCUBETEXTURE9>(_pTexture)->GetLevelDesc(0, &desc);

		return desc.Height;
	}

	Texture::~Texture(void) noexcept
	{
		if (_pTexture != nullptr)
			_pTexture->Release();
	}
}
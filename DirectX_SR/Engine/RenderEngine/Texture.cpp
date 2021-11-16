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
				if (FAILED(D3DXGetImageInfoFromFileA(filePath, &_imgInfo)))
				{
					CE_ASSERT("ckswns", "텍스쳐의 정보를 읽어오는데 실패하였습니다");
					return false;
				}
				_type = Texture::Type::CUBE;

		}
		else
		{
			if (FAILED(D3DXCreateTextureFromFileExA(
				pd3dDevice
				, filePath
				, D3DX_DEFAULT
				, D3DX_DEFAULT
				, 1
				, 0
				, D3DFMT_UNKNOWN
				, D3DPOOL_MANAGED
				, D3DX_FILTER_NONE
				, D3DX_FILTER_NONE
				, D3DCOLOR_RGBA(255, 0, 255, 0)
				, &_imgInfo
				, NULL
				, (LPDIRECT3DTEXTURE9*)&_pTexture
			)))
			{
				_pTexture = NULL;

				CE_ASSERT("ckswns", "텍스쳐 생성에 실패하였습니다!");
				return false;
			}
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

	uint32 Texture::LoadedWidth(void) const noexcept
	{
		D3DSURFACE_DESC desc;

		if(_type == Type::DEFAULT)
			static_cast<LPDIRECT3DTEXTURE9>(_pTexture)->GetLevelDesc(0, &desc);
		else
			static_cast<LPDIRECT3DCUBETEXTURE9>(_pTexture)->GetLevelDesc(0, &desc);
		return desc.Width;
	}

	uint32 Texture::LoadedHeight(void) const noexcept
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
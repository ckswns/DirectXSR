#include "pch.h"
#include "TextureAsset.h"
#include "Texture.h"
#include "D3D9Device.h"

namespace ce
{
	TextureAsset::TextureAsset(void) noexcept :
		Asset(AssetType::TEXTURE)
	{
	}

	bool TextureAsset::Load(std::string _filePath) noexcept
	{
		Texture* tex = new Texture();
		bool result = tex->Init(D3D9Device::Instance()->GetDevice(), _filePath.c_str());
		_data = (void*)tex;

		return result;
	}

	void TextureAsset::Release(void) noexcept
	{
		Texture* data = reinterpret_cast<Texture*>(_data);
		data->Release();
		delete data;
		data = nullptr;
		_data = nullptr;
	}
}
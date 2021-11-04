#pragma once

#ifndef __TEXTURE_ASSET_H__
#define __TEXTURE_ASSET_H__

#include "Asset.h"

namespace ce
{
	class TextureAsset : public Asset
	{
	public:		explicit	TextureAsset(void) noexcept;
	public:		virtual		~TextureAsset(void) noexcept { __noop; }

	public:		bool		Load(std::string _filePath) noexcept override;
	public:		void		Release(void) noexcept override;
	};
}

#endif
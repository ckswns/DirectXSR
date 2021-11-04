#pragma once

#ifndef __TEXT_ASSET_H__
#define __TEXT_ASSET_H__

#include "Asset.h"

namespace ce
{
	class TextAsset : public Asset
	{
	public:	explicit	TextAsset(void) noexcept;
	public:	virtual		~TextAsset(void) noexcept { __noop; }

	public:	bool		Load(std::string _filePath) noexcept override;
	public:	void		Release(void) noexcept override;
	};
}

#endif
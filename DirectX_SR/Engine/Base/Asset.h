#pragma once

#ifndef __ASSET_H__
#define __ASSET_H__

namespace ce
{
	enum class AssetType
	{
		TEXTURE,
		AUDIO,
		TEXT,
		END
	};

	class Asset
	{
	public:		explicit			Asset(AssetType _type) noexcept : _eType(_type), _strKey(""), _strFilePath(""), _data(nullptr) { __noop; }
	public:		virtual				~Asset() noexcept { __noop; }

	public:		virtual bool		Load(std::string _filePath) noexcept PURE;
	public:		virtual void		Release(void) noexcept PURE;

	public:		void*				GetData(void) const noexcept { return _data; }
	public:		AssetType			GetAssetType(void) const noexcept { return _eType; }

	protected:	void*				_data;
	protected:	AssetType			_eType;
	protected:	std::string			_strKey;
	protected:	std::string			_strFilePath;
	};
}
#endif

#pragma once
#include "SingletonBase.h"
#include "Asset.h"

namespace ce
{
	class AssetManager : public SingletonBase<AssetManager>
	{
	private:	explicit				AssetManager(void) noexcept;
	private:	virtual					~AssetManager(void) noexcept;

	public:		using					AssetMap = std::unordered_map<std::string, Asset*>;
	public:		using					CONST_REF_CSVDATA = const std::vector<std::vector<std::string>>&;
	public:		using					CONST_PTR_CSVDATA = const std::vector<std::vector<std::string>>*;

	public:		void					Release(void) noexcept;

	public:		void					LoadAssetFolder(std::string _assetFolderPath, std::string* showingStr = nullptr) noexcept;

	public:		bool					GetLoadingState(void) const noexcept { return _bWhileLoading; }
	public:		float					GetLoadingProgress(void) const noexcept { return _fLoadProgress; }

	public:		const AssetMap&			GetCSVAssetMap(void) const noexcept { return _mapAsset[static_cast<int>(AssetType::TEXT)]; }
	public:		const AssetMap&			GetAudioAssetMap(void) const noexcept { return _mapAsset[static_cast<int>(AssetType::AUDIO)]; }
	public:		const AssetMap&			GetSpriteAssetMap(void) const noexcept { return _mapAsset[static_cast<int>(AssetType::TEXTURE)]; }

	//public:		Sprite*					GetSpriteData(std::string _key) noexcept;
	public:		CONST_PTR_CSVDATA		GetCSVData(std::string _key) noexcept;
	//public:		FMOD::Sound*			GetAudioData(std::string _key) noexcept;

	private:	bool					LoadAssetAsync(std::string _assetFolderPath, std::string* showingStr) noexcept;
		   
	private:	AssetMap				_mapAsset[static_cast<int>(AssetType::END)];

	private:	bool					_bWhileLoading;
	private:	float					_fLoadProgress;

	private:	friend					SingletonBase<AssetManager>;
	};
}

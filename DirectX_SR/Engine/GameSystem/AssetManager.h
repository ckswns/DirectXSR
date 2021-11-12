#pragma once
#include "SingletonBase.h"
#include "Asset.h"

namespace ce
{
	class Texture;
	class AudioAsset;

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

#ifdef __USE_FMOD__
	public:		AudioAsset*				GetAudioAsset(std::string _key) noexcept;
#endif
	public:		const AssetMap&			GetCSVAssetMap(void) const noexcept { return _mapAsset[static_cast<int>(AssetType::TEXT)]; }
	public:		const AssetMap&			GetAudioAssetMap(void) const noexcept { return _mapAsset[static_cast<int>(AssetType::AUDIO)]; }
	public:		const AssetMap&			GetTextureAssetMap(void) const noexcept { return _mapAsset[static_cast<int>(AssetType::TEXTURE)]; }

	public:		Texture*				GetTextureData(std::string _key) noexcept;
	public:		CONST_PTR_CSVDATA		GetCSVData(std::string _key) noexcept;

#ifdef __USE_FMOD__
	public:		FMOD::Sound*			GetAudioData(std::string _key) noexcept;
#endif
	private:	bool					LoadAssetAsync(std::string _assetFolderPath, std::string* showingStr) noexcept;
		   
	private:	AssetMap				_mapAsset[static_cast<int>(AssetType::END)];

	private:	bool					_bWhileLoading;
	private:	float					_fLoadProgress;

	private:	friend					SingletonBase<AssetManager>;
	};
}

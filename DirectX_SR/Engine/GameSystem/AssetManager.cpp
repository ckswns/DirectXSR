#include "pch.h"
#include "AssetManager.h"
#include <filesystem>
#include "AudioAsset.h"
#include "TextureAsset.h"
#include "TextAsset.h"
#include <thread>
#include "FMODManager.h"
#include "Assertion.h"

namespace fs = std::filesystem;

namespace ce
{
	AssetManager::AssetManager(void) noexcept
	{
	}

	AssetManager::~AssetManager(void) noexcept
	{
	}

	void AssetManager::Release(void) noexcept
	{
		for (int i = 0; i < static_cast<int>(AssetType::END); i++)
		{
			for (auto iter = _mapAsset[i].begin(); iter != _mapAsset[i].end(); iter++)
			{
				iter->second->Release();
				delete iter->second;
				iter->second = nullptr;
			}

			_mapAsset[i].clear();
		}
	}

	void AssetManager::LoadAssetFolder(std::string _assetFolderPath, std::string* showingStr) noexcept
	{
		_bWhileLoading = true;

		std::thread loading(&AssetManager::LoadAssetAsync, this, _assetFolderPath, showingStr);
		loading.detach();
	}

	AssetManager::CONST_PTR_CSVDATA AssetManager::GetCSVData(std::string _key) noexcept
	{
		return CONST_PTR_CSVDATA();
	}

	bool AssetManager::LoadAssetAsync(std::string _assetFolderPath, std::string* showingStr) noexcept
	{
#ifdef __USE_FMOD__
		FMOD::System* audioSystem = FMODManager::Instance()->GetSystem();
#endif
		std::mutex m;
		m.lock();

		float fileCount = std::distance(fs::recursive_directory_iterator(_assetFolderPath), fs::recursive_directory_iterator{});
		float loadCount = 0;

		for (auto& entry : fs::recursive_directory_iterator(_assetFolderPath))
		{
			loadCount++;

			_fLoadProgress = loadCount / fileCount;

			if (entry.is_directory())
				continue;

			std::string filePath = entry.path().u8string();
			size_t split = filePath.find('.');

			std::string fileExtension = filePath.substr(split);
			AssetType type = AssetType::END;

			if (fileExtension == ".png"
				|| fileExtension == ".bmp"
				|| fileExtension == ".jpg"
				|| fileExtension == ".jpeg"
				|| fileExtension == ".dds"
				|| fileExtension == ".tga")
			{
				type = AssetType::TEXTURE;
			}

			else if (fileExtension == ".csv"
				|| fileExtension == ".txt")
			{
				type = AssetType::TEXT;
			}

			else if (fileExtension == ".wav"
				|| fileExtension == ".mp3"
				|| fileExtension == ".ogg")
			{
				type = AssetType::AUDIO;
			}

			else
			{
				continue;
			}

			Asset* asset = nullptr;

			if (showingStr != nullptr)
				(*showingStr) = entry.path().u8string();

			switch (type)
			{
			case AssetType::TEXTURE:
				asset = new TextAsset();

				if (static_cast<TextureAsset*>(asset)->Load(entry.path().u8string()) == false)
				{
					CE_ASSERT("ckswns", "TextureAsset asset의 로딩에 실패하였습니다");
					return false;
				}

				_mapAsset[static_cast<int>(AssetType::TEXTURE)].insert(std::make_pair(entry.path().u8string(), asset));

				break;

			case AssetType::AUDIO:
#ifdef __USE_FMOD__
				asset = new AudioAsset(audioSystem);

				if (static_cast<AudioAsset*>(asset)->Load(entry.path().u8string()) == false)
				{
					CE_ASSERT("ckswns", "audio asset의 로딩에 실패하였습니다");
					return false;
				}

				_mapAsset[static_cast<int>(AssetType::AUDIO)].insert(std::make_pair(entry.path().u8string(), asset));
#endif
				break;

			case AssetType::TEXT:
				asset = new TextAsset();

				if (static_cast<TextAsset*>(asset)->Load(entry.path().u8string()) == false)
				{
					CE_ASSERT("ckswns", "csv asset의 로딩에 실패하였습니다");
					return false;
				}

				_mapAsset[static_cast<int>(AssetType::TEXT)].insert(std::make_pair(entry.path().u8string(), asset));

				break;

			default:
				delete asset;
				continue;
			}
		}

		m.unlock();

		_bWhileLoading = false;

		return true;
	}
}
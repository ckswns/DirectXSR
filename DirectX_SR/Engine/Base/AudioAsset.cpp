#include "pch.h"
#include "AudioAsset.h"
#include "Assertion.h"

#ifdef	__USE_FMOD__

namespace ce
{
	AudioAsset::AudioAsset(FMOD::System* pSystem) noexcept :
		Asset(AssetType::AUDIO),
		_pFMODSystem(pSystem)
	{
	}

	bool AudioAsset::ReLoad(bool is3D) noexcept
	{
		_is3D = is3D;
		if(_data)
			reinterpret_cast<FMOD::Sound*>(_data)->release();

		return Load(_filePath);
	}

	bool AudioAsset::Load(std::string filePath) noexcept
	{
		if (_pFMODSystem == nullptr)
		{
			CE_ASSERT("ckswns", "FMOD::System은 nullptr일 수 없습니다!");
			return false;
		}

		_filePath = filePath;

		FMOD::Sound* sound;

		FMOD_RESULT fr;
		
		if(_is3D)		
			fr = _pFMODSystem->createStream(filePath.c_str(), FMOD_3D, nullptr, &sound);
		else
			fr = _pFMODSystem->createStream(filePath.c_str(), FMOD_DEFAULT, nullptr, &sound);

		if (fr != FMOD_RESULT::FMOD_OK)
		{
			CHAR errMsg[128];
			sprintf_s(errMsg, 128, "createStream에 실패하였습니다. \n ERR Code : %d", (int)fr);

			CE_ASSERT("ckswns", errMsg);
			return false;
		}

		_data = sound;

		return true;
	}

	void AudioAsset::Release(void) noexcept
	{
		if (_data != nullptr)
		{
			reinterpret_cast<FMOD::Sound*>(_data)->release();
			_data = nullptr;
		}
	}

	AudioAsset* AudioAsset::Clone(bool is3D) const noexcept
	{
		AudioAsset* clone = new AudioAsset(_pFMODSystem);
		clone->_filePath = _filePath;
		clone->ReLoad(is3D);

		return clone;
	}
}

#endif
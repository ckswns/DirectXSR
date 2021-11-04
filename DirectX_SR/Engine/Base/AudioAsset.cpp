#include "pch.h"
#include "AudioAsset.h"
#include "Assertion.h"

#ifdef	__USE_FMOD__

namespace ce
{
	AudioAsset::AudioAsset(FMOD::System* pSystem, bool is3DSound) noexcept :
		Asset(AssetType::AUDIO),
		_pFMODSystem(pSystem),
		_b3DSound(is3DSound)
	{
	}

	bool AudioAsset::Load(std::string _filePath) noexcept
	{
		if (_pFMODSystem == nullptr)
		{
			CE_ASSERT("ckswns", "FMOD::System은 nullptr일 수 없습니다!");
			return false;
		}

		FMOD::Sound* sound;

		FMOD_RESULT fr;
		FMOD_MODE mode;

		if (_b3DSound)
			mode |= FMOD_3D;
		else
			mode |= FMOD_2D;

		mode |= FMOD_CREATESTREAM;

		if (_filePath.find("loop") == std::string::npos)
			mode |= FMOD_LOOP_NORMAL;
		else
			mode |= FMOD_LOOP_OFF;

		fr = _pFMODSystem->createStream(_filePath.c_str(), mode, nullptr, &sound);

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
}

#endif
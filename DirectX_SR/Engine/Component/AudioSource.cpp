#include "pch.h"
#include "AudioSource.h"
#include "ConstValues.h"
#include "Assertion.h"
#include "AudioAsset.h"
#include "Transform.h"
#include "FMODManager.h"

#ifdef __USE_FMOD__

namespace ce
{
	AudioSource::AudioSource(void) noexcept :
		Component(COMPONENT_ID::AUDIOSOURCE),
		_bLoop(false),
		_fVolume(0.5f),
		_b3DSound(true)
	{
	}

	AudioSource::~AudioSource(void) noexcept
	{
	}

	void AudioSource::Init(void) noexcept
	{
		_pTransform = _owner->GetTransform();
		_pSystem = FMODManager::Instance()->GetSystem();

		if (_pSystem == nullptr)
			CE_ASSERT("ckswns", "FMOD::System이 초기화 되지 않았습니다!");
		if (_pTransform == nullptr)
			CE_ASSERT("ckswns", "Owner의 Transform을 얻어오는데 실패하였습니다");
	}

	void AudioSource::Update(float) noexcept
	{
		if (_bLoop == true)
		{
			if (IsPlaying() == false)
				Play();
		}

		if (_b3DSound == false)
			return;

		D3DXVECTOR3 position = _pTransform->GetWorldPosition();
		FMOD_VECTOR fPosition = { position.x, position.y, position.z };

		_pChannel->set3DAttributes(&fPosition, 0);
	}

	void AudioSource::Release(void) noexcept
	{
		if (_pChannel)
		{
			_pChannel->stop();
			_pChannel = nullptr;
		}

		_pSystem = nullptr;
	}

	bool AudioSource::LoadAudio(AudioAsset* asset) noexcept
	{
		if (asset->GetAssetType() != AssetType::AUDIO)
		{
			CE_ASSERT("ckswns", "Asset타입이 오디오가 아닙니다.");
			return false;
		}

		_pSound = reinterpret_cast<FMOD::Sound*>(asset->GetData());
		_asset = asset;

		return true;
	}

	//bool AudioSource::LoadAudio(FMOD::Sound* sound) noexcept
	//{
	//	if (sound == nullptr)
	//	{
	//		CE_ASSERT("ckswns", "Sound는 nullptr일 수 없습니다");
	//		return false;
	//	}

	//	_pSound = sound;

	//	return true;
	//}

	void AudioSource::Play(void) noexcept
	{
		bool isPlaying = false;
		_pChannel->isPlaying(&isPlaying);

		if (isPlaying)
			_pChannel->stop();

		_pSystem->playSound(_pSound, NULL, false, &_pChannel);
	}

	void AudioSource::Stop(void) noexcept
	{
		_pChannel->stop();
	}

	void AudioSource::Pause(void) noexcept
	{
		_pChannel->setPaused(true);
	}

	void AudioSource::Resume(void) noexcept
	{
		_pChannel->setPaused(false);
	}

	void AudioSource::SetVolume(float volume) noexcept
	{
		_pChannel->setVolume(volume);
	}

	bool AudioSource::IsPlaying(void) noexcept
	{
		bool isPlaying = false;
		_pChannel->isPlaying(&isPlaying);

		return isPlaying;
	}

	void AudioSource::SetSoundWorld(bool is3D) noexcept
	{
		if (_b3DSound == is3D)
			return;

		bool isPlaying = IsPlaying();

		_b3DSound = is3D;

		_pChannel->stop();
		_pSound->release();

		_asset->ReLoad(is3D);
		_pSound = reinterpret_cast<FMOD::Sound*>(_asset->GetData());

		if (isPlaying)
			Play();
	}
}

#endif
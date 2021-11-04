#include "pch.h"
#include "AudioSource.h"
#include "ConstValues.h"
#include "Assertion.h"
#include "AudioAsset.h"

#ifdef __USE_FMOD__

namespace ce
{
	AudioSource::AudioSource(GameObject* owner) noexcept :
		Component(owner, COMPONENT_ID::AUDIOSOURCE)
	{
	}

	AudioSource::~AudioSource(void) noexcept
	{
	}

	void AudioSource::FixedUpdate(float) noexcept
	{
		__noop;
	}

	void AudioSource::Update(float) noexcept
	{
		__noop;
	}

	void AudioSource::LateUpdate(float) noexcept
	{
		__noop;
	}

	void AudioSource::Render(float) noexcept
	{
		__noop;
	}

	void AudioSource::Release(void) noexcept
	{
		if (_pChannel)
		{
			_pChannel->stop();
			//free(m_pChannel);
			_pChannel = nullptr;
		}

		_pSystem = nullptr;
	}

	bool AudioSource::LoadAudio(Asset* asset) noexcept
	{
		if (asset->GetAssetType() != AssetType::AUDIO)
		{
			CE_ASSERT("ckswns", "AssetŸ���� ��ġ���� �ʽ��ϴ�!");
			return false;
		}

		_pSound = reinterpret_cast<FMOD::Sound*>(asset->GetData());

		return true;
	}

	bool AudioSource::LoadAudio(FMOD::Sound* sound) noexcept
	{
		if (sound == nullptr)
		{
			CE_ASSERT("ckswns", "Sound�� nullptr�� �� �����ϴ�");
			return false;
		}

		_pSound = sound;

		return true;
	}

	void AudioSource::Play(bool BGM) noexcept
	{
		bool isPlaying = false;
		_pChannel->isPlaying(&isPlaying);

		if (isPlaying)
			_pChannel->stop();

		_pSystem->playSound(_pSound, NULL, false, &_pChannel);

		//if (BGM)
		//	_pChannel->setVolume(SOUNDMANAGER->m_fBGMVolume);
		//else
		//	_pChannel->setVolume(SOUNDMANAGER->m_fEffectVolume);
	}

	void AudioSource::Stop(void) noexcept
	{

	}

	void AudioSource::Pause(void) noexcept
	{

	}

	void AudioSource::Resume(void) noexcept
	{

	}

	void AudioSource::SetVolume(float volume) noexcept
	{

	}

	bool AudioSource::IsPlaying(void) noexcept
	{
		return false;
	}

}

#endif
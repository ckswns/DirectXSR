#pragma once
#include "Component.h"

#ifdef __USE_FMOD__

namespace ce
{
	class Asset;
	class GameObject;

	class AudioSource : public Component
	{
	public:		explicit				AudioSource(void) = delete;
	public:		explicit				AudioSource(GameObject* owner) noexcept;
	public:		virtual					~AudioSource(void) noexcept;

	public:		void					FixedUpdate(float) noexcept override;
	public:		void					Update(float) noexcept override;
	public:		void					LateUpdate(float) noexcept override;
	public:		void					Render(float) noexcept override;
	public:		void					Release(void) noexcept override;

	public:		bool					LoadAudio(Asset* asset) noexcept;
	public:		bool					LoadAudio(FMOD::Sound* sound) noexcept;

	public:		void					Play(bool BGM = false) noexcept;
	public:		void					Stop(void) noexcept;
	public:		void					Pause(void) noexcept;
	public:		void					Resume(void) noexcept;
	public:		FMOD::Channel*			GetChanel(void) noexcept { return _pChannel; }

	public:		float					GetVolume(void) const noexcept { return _fVolume; }
	public:		void					SetVolume(float volume) noexcept;
	public:		bool					IsPlaying(void) noexcept;

	private:	bool					_bLoop;
	private:	float					_fVolume;

	private:	FMOD::ChannelGroup*		_pChannelGroup;
	private:	FMOD::Channel*			_pChannel;
	private:	FMOD::Sound*			_pSound;
	private:	FMOD::System*			_pSystem;
	};
}

#endif
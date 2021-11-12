#pragma once
#include "Component.h"

#ifdef __USE_FMOD__

namespace ce
{
	class AudioAsset;
	class GameObject;
	class Transform;

	class AudioSource : public Component
	{
	public:		explicit				AudioSource(void) noexcept;
	public:		virtual					~AudioSource(void) noexcept;

	public:		void					Init(void) noexcept;
	public:		void					FixedUpdate(float) noexcept override { __noop; }
	public:		void					Update(float) noexcept override;
	public:		void					LateUpdate(float) noexcept override { __noop; }
	public:		void					Render(void) noexcept override { __noop; }
	public:		void					Release(void) noexcept override;

	public:		bool					LoadAudio(AudioAsset* asset) noexcept;

	public:		void					Play(void) noexcept;
	public:		void					Stop(void) noexcept;
	public:		void					Pause(void) noexcept;
	public:		void					Resume(void) noexcept;

	public:		FMOD::Channel*			GetChanel(void) noexcept { return _pChannel; }

	public:		float					GetVolume(void) const noexcept { return _fVolume; }
	public:		void					SetVolume(float volume) noexcept;
	public:		bool					IsPlaying(void) noexcept;

	public:		void					SetLoop(bool loop) noexcept { _bLoop = loop; }
	public:		bool					GetIsLoop(void) const noexcept { return _bLoop; }

	public:		void					SetSoundWorld(bool is3D) noexcept;
	public:		bool					GetSoundWorld(void) const noexcept { return _b3DSound; }

	private:	bool					_bLoop;
	private:	bool					_b3DSound = true;
	private:	float					_fVolume;

	private:	FMOD::ChannelGroup*		_pChannelGroup;
	private:	FMOD::Channel*			_pChannel;
	private:	FMOD::Sound*			_pSound;
	private:	FMOD::System*			_pSystem;

	private:	AudioAsset*				_asset;

	private:	Transform*				_pTransform;
	};
}

#endif
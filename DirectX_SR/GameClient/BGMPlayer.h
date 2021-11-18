#pragma once
#include "Behaviour.h"

namespace ce 
{
	class AudioSource;
	class AudioAsset;
}

class BGMPlayer : public Behaviour
{
public:		explicit			BGMPlayer(void) noexcept;
public:		virtual				~BGMPlayer(void) noexcept { __noop; }

public:		void				Start(void) noexcept override;
public:		void				Update(float) noexcept override;

public:		void				SetBGM(AudioAsset* data);
public:		void				SetVolume(float volume) noexcept;

private:	float				_volume = 1.0f;

public:		static BGMPlayer*	Instance(void) noexcept;

private:	AudioSource*		_audio;
private:	static BGMPlayer*	_player;
};


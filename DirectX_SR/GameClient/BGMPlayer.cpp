#include "pch.h"
#include "BGMPlayer.h"
#include "AudioSource.h"
#include "Assertion.h"
#include "AudioSource.h"
#include "AudioAsset.h"

BGMPlayer* BGMPlayer::_player = nullptr;

BGMPlayer::BGMPlayer(void) noexcept
{
	if (_player == nullptr)
		_player = this;
	else
		CE_ASSERT("ckswns", "BGMPlayer는 하나만 존재 할 수 있습니다");
}

void BGMPlayer::Start(void) noexcept
{

}

void BGMPlayer::Update(float) noexcept
{

}

void BGMPlayer::SetBGM(AudioAsset* data)
{
	_audio->LoadAudio(data);
	_audio->SetLoop(true);
	_audio->SetSoundWorld(false);
	_audio->SetVolume(_volume);
	_audio->Play();
}

void BGMPlayer::SetVolume(float volume) noexcept
{
	_volume = volume;
	_audio->SetVolume(_volume);
}

BGMPlayer* BGMPlayer::Instance(void) noexcept
{
	if (_player == nullptr)
	{
		_player = new BGMPlayer();

		GameObject* obj = GameObject::Instantiate();
		obj->SetDontDestroy(true);
		obj->AddComponent(_player);
		_player->_audio = static_cast<AudioSource*>(obj->AddComponent(new AudioSource()));
		_player->_audio->Init();
	}

	return _player;
}

#include "pch.h"
#include "Animator.h"
#include "Animation.h"
#include "Assertion.h"

namespace ce
{
	Animator::Animator(bool playOnAwake) noexcept :
		Component(COMPONENT_ID::ANIMATOR),
		_bPlayOnAwake(playOnAwake),
		_currentAni(nullptr),
		_currentAniName("")
	{

	}

	void Animator::Init(void) noexcept
	{

	}

	void Animator::Update(float fElapsedTime) noexcept
	{
		if (_currentAni)
			_currentAni->Update(fElapsedTime);
	}

	void Animator::Render(void) noexcept
	{

	}

	void Animator::Release(void) noexcept
	{
		for (auto iter = _mapAnim.begin(); iter != _mapAnim.end();)
		{
			delete iter->second;
			iter = _mapAnim.erase(iter);
		}

		_mapAnim.clear();
	}

	bool Animator::InsertAnimation(std::string key, Animation* ani) noexcept
	{
		auto iter = _mapAnim.find(key);

		if (iter != _mapAnim.end())
		{
			CE_ASSERT("ckswns", "Animator에 삽입을 시도한 키가 이미 존재합니다");
			return false; 
		}

		_mapAnim.insert(std::make_pair(key, ani));

		if (_mapAnim.size() == 1)
		{
			_currentAni = ani;
			_currentAniName = key;

			if (_bPlayOnAwake)
				_currentAni->Play();
		}

		return true;
	}

	bool Animator::SetAnimation(std::string key) noexcept
	{
		auto iter = _mapAnim.find(key);

		if (iter != _mapAnim.end())
		{
			if (_currentAni)
				_currentAni->Stop();

			_currentAni = iter->second;
			_currentAniName = iter->first;

			if (_bPlayOnAwake)
				_currentAni->Play();

			return true;
		}

		return false;
	}

	bool Animator::Play(std::string key) noexcept
	{
		if (key.empty())
		{
			if (_currentAni)
			{
				_currentAni->Play();
				return true;
			}

			return false;
		}

		auto iter = _mapAnim.find(key);

		if (iter != _mapAnim.end())
		{
			if (_currentAni)
				_currentAni->Stop();

			_currentAni = iter->second;
			_currentAniName = iter->first;

			_currentAni->Play();

			return true;
		}

		return false;
	}

	void Animator::Stop(void) noexcept
	{
		if (_currentAni)
			_currentAni->Stop();
	}

	void Animator::Resume(void) noexcept
	{
		if (_currentAni)
			_currentAni->Resume();
	}

	void Animator::Pause(void) noexcept
	{
		if (_currentAni)
			_currentAni->Pause();
	}

	bool Animator::GetCurrentAnimationEnd(void) noexcept
	{
		if (_currentAni)
			return _currentAni->IsEnd();

		return false;
	}

	std::string Animator::GetCurrentAnimationName(void) const noexcept
	{
		return _currentAniName;
	}

	Animation* Animator::GetAnimationByKey(std::string key) noexcept
	{
		auto iter = _mapAnim.find(key);

		if (iter != _mapAnim.end())
			return iter->second;

		return nullptr;
	}
}
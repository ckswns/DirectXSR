#include "pch.h"
#include "TimeManager.h"

namespace ce
{
	TimeManager::TimeManager(void) noexcept :
		_prevFrame(),
		_currFrame(),
		_fDeltaTime(0),
		_fTimeScale(1),
		_fFPS(60),
		_fFPSTime(0),
		_nFPSCount(0),
		_nTempFPSCount(0),
		_bLockFrame(false)
	{
	}

	bool TimeManager::Init(void) noexcept
	{
		_fTimeScale = 1;
		_fDeltaTime = 0;

		_prevFrame = std::chrono::system_clock::now();
		_currFrame = std::chrono::system_clock::now();

		return true;
	}

	void TimeManager::Update(void) noexcept
	{
		_currFrame = std::chrono::system_clock::now();
		std::chrono::duration<float> t = _currFrame - _prevFrame;
		_fDeltaTime = t.count();

		_prevFrame = _currFrame;

		_fFPSTime += _fDeltaTime;
		_nTempFPSCount++;

		if (_nTempFPSCount >= _fFPS)
		{
			//m_bLockFrame = TRUE;
		}

		if (_fFPSTime >= 1.0f)
		{
			_bLockFrame = false;
			_nFPSCount = _nTempFPSCount;
			_nTempFPSCount = 0;
			_fFPSTime = 0;
		}
	}

	float TimeManager::GetDeltaTime(void) const noexcept
	{
		return _fDeltaTime * _fTimeScale;
	}

	float TimeManager::GetUnScaledDeltaTime(void) const noexcept
	{
		return _fDeltaTime;
	}

	void TimeManager::SetTimeScale(float scale) noexcept
	{
		if (scale > 0)
			_fTimeScale = scale;
	}

	void TimeManager::SetFPS(float fps) noexcept
	{
		if (fps > 0)
			_fFPS = fps;
	}

	bool TimeManager::FrameLock(void) const noexcept
	{
		return _bLockFrame;
	}
}
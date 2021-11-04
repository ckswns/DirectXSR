#pragma once
#include "SingletonBase.h"

namespace ce
{
	class TimeManager : public SingletonBase<TimeManager>
	{
	private:	explicit	TimeManager(void) noexcept;
	private:	virtual		~TimeManager(void) noexcept { __noop; }

	public:		bool		Init(void) noexcept;
	public:		void		Update(void) noexcept;
	public:		float		GetDeltaTime(void) const noexcept;
	public:		float		GetUnScaledDeltaTime(void) const noexcept;

	public:		void		SetTimeScale(float scale) noexcept;

	public:		void		SetFPS(float fps) noexcept;
	public:		bool		FrameLock(void) const noexcept;
	public:		int			GetFPSCount(void) const noexcept { return _nFPSCount; }

	private:	using		CHRONO = std::chrono::system_clock::time_point;

	private:	CHRONO		_prevFrame;
	private:	CHRONO		_currFrame;

	private:	float		_fDeltaTime;
	private:	float		_fTimeScale;
	private:	float		_fFPSTime;
	private:	float		_fFPS;

	private:	bool		_bLockFrame;
	private:	int			_nTempFPSCount;
	private:	int			_nFPSCount;

	private:	friend		SingletonBase<TimeManager>;
	};
}

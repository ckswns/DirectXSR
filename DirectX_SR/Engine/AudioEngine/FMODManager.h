#pragma once
#include "SingletonBase.h"

#define SOUNDBUFFER 100


#ifdef	__USE_FMOD__

namespace ce
{
	class FMODManager : public SingletonBase<FMODManager>
	{
	public:		explicit		FMODManager() noexcept;
	public:		virtual			~FMODManager() noexcept { __noop; }

	public:		bool			Init(void) noexcept;
	public:		void			Update(void) noexcept;
	public:		void			Release(void) noexcept;

	public:		FMOD::System*	GetSystem(void) noexcept { return _pFMODSystem; }

	private:	FMOD::System*	_pFMODSystem;
	private:	float			_fBGMVolume = 1;
	private:	float			_fEffectVolume = 1;
	};
}

#endif
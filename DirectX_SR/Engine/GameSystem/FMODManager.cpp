#include "pch.h"
#include "FMODManager.h"

#ifdef	__USE_FMOD__

namespace ce
{
	FMODManager::FMODManager() noexcept :
		_pFMODSystem(nullptr)
	{
	}

	bool FMODManager::Init(void) noexcept
	{
		if (FMOD::System_Create(&_pFMODSystem) != FMOD_RESULT::FMOD_OK)
			return false;

		_pFMODSystem->init((int)SOUNDBUFFER, FMOD_INIT_NORMAL, 0);

		return true;
	}

	void FMODManager::Update(void) noexcept
	{
		_pFMODSystem->update();
	}

	void FMODManager::Release(void) noexcept
	{
		if (_pFMODSystem != nullptr)
		{
			_pFMODSystem->release();
			_pFMODSystem->close();
		}
	}
}

#endif
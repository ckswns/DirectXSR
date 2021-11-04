#pragma once
#include "Asset.h"

#ifdef	__USE_FMOD__

namespace ce
{
	class AudioAsset : public Asset
	{
	public:		explicit		AudioAsset(void) = delete;
	public:		explicit		AudioAsset(FMOD::System* pSystem, bool is3DSound = true) noexcept;
	public:		virtual			~AudioAsset(void) noexcept { __noop; }

	public:		bool			Load(std::string _filePath) noexcept override;
	public:		void			Release(void) noexcept override;

	private:	FMOD::System*	_pFMODSystem;
	private:	bool			_b3DSound;
	};
}

#endif

#pragma once
#include "Asset.h"

#ifdef	__USE_FMOD__

namespace ce
{
	class AudioAsset : public Asset
	{
	public:		explicit			AudioAsset(void) = delete;
	public:		explicit			AudioAsset(FMOD::System* pSystem) noexcept;
	public:		virtual				~AudioAsset(void) noexcept { __noop; }

	public:		bool				ReLoad(bool is3D) noexcept;
	public:		bool				Load(std::string _filePath) noexcept override;
	public:		void				Release(void) noexcept override;
		  
	public:		const std::string&	GetFilePath(void) const noexcept { return _filePath; }
	public:		AudioAsset*			Clone(bool is3D) const noexcept;

	private:	bool				_is3D = true;
	private:	FMOD::System*		_pFMODSystem;
	private:	std::string			_filePath;
	};
}

#endif

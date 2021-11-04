#pragma once
#include "../Base/TypeDefine.h"

namespace ce
{
	class Texture
	{
	public:		explicit				Texture(void) noexcept { __noop; }
	public:		virtual					~Texture(void) noexcept;

	public:		using					TList = std::vector<Texture*>;

	public:		bool					Init(LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR filePath) noexcept;
	public:		void					Release(void) noexcept;

	public:		uint32					Width(void) const noexcept;
	public:		uint32					Height(void) const noexcept;

	public:		std::string				GetFilePathA(void) const noexcept { return _filePathA; }
	public:		std::wstring			GetFilePathW(void) const noexcept { return _filePathW; }

	public:		LPDIRECT3DTEXTURE9		GetTexturePTR(void) noexcept { return _pTexture; }

	private:	std::wstring			_filePathW;
	private:	std::string				_filePathA;

	private:	LPDIRECT3DTEXTURE9		_pTexture;
	};
}

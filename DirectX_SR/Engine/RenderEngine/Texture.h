#pragma once
#include "../Base/TypeDefine.h"
#include "INoncopyable.h"

namespace ce
{
	class Texture : public INoncopyable
	{
	public:		enum class				Type
										{
											DEFAULT,
											CUBE
										};

	public:		explicit				Texture(void) noexcept { __noop; }
	public:		virtual					~Texture(void) noexcept;

	public:		using					TList = std::vector<Texture*>;

	public:		bool					Init(LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR filePath) noexcept;
	public:		void					Release(void) noexcept;

	public:		uint32					Width(void) const noexcept { return _imgInfo.Width; }
	public:		uint32					Height(void) const noexcept { return _imgInfo.Height; }

	public:		uint32					LoadedWidth(void) const noexcept;
	public:		uint32					LoadedHeight(void) const noexcept;

	public:		std::string				GetFilePathA(void) const noexcept { return _filePathA; }
	public:		std::wstring			GetFilePathW(void) const noexcept { return _filePathW; }

	public:		IDirect3DBaseTexture9*	GetTexturePTR(void) noexcept { return _pTexture; }

	public:		Texture::Type			GetType(void) const noexcept { return _type; }

	private:	std::wstring			_filePathW;
	private:	std::string				_filePathA;

	private:	D3DXIMAGE_INFO			_imgInfo;
	private:	IDirect3DBaseTexture9*	_pTexture;
	private:	Texture::Type			_type;
	};
}

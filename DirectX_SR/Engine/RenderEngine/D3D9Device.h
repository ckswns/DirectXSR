#pragma once

#include "../Base/SingletonBase.h"
#include "../Base/TypeDefine.h"

namespace ce
{
	class D3D9Device : public SingletonBase<D3D9Device>
	{
	private:	explicit			D3D9Device() noexcept;
	private:	virtual				~D3D9Device() noexcept { __noop; }

	public:		bool				Init(HWND hWnd, uint16 winWidth, uint16 winHeight, D3DXCOLOR clearColor = D3DCOLOR_ARGB(255, 0, 0, 255),
											const char* fontFilePath = "", const char* fontFaceName = "") noexcept;
	public:		void				Begin(void) noexcept;
	public:		void				End(void) noexcept;
	public:		void				UIBegin(void) noexcept;
	public:		void				UIEnd(void) noexcept;
	public:		void				Release(void) noexcept;

	public:		LPDIRECT3DDEVICE9	GetDevice(void) noexcept { return _pDevice; }

	public:		uint32				GetWindowWidth(void) const noexcept { return _windowWidth; }
	public:		uint32				GetWindowHeight(void) const noexcept { return _windowHeight; }

	public:		POINT				GetWindowSize(void) const noexcept { return POINT{ (long)_windowWidth, (long)_windowHeight }; }
	
	public:		LPD3DXSPRITE		GetSprite(void) noexcept { return _pSprite; }
	public:		LPD3DXFONT			GetFont(void) noexcept { return _pFont; }

	private:	LPDIRECT3D9			_pSDK;
	private:	LPDIRECT3DDEVICE9	_pDevice;
	private:	LPD3DXSPRITE		_pSprite;
	private:	LPD3DXFONT			_pFont;

	private:	D3DXCOLOR			_nClearColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	private:	uint32				_windowWidth;
	private:	uint32				_windowHeight;

	private:	friend				SingletonBase<D3D9Device>;
	};
}

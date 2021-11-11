#pragma once
#include "INoncopyable.h"
#include "Scene.h"

namespace ce
{
	class GameController : public INoncopyable
	{
	public:		explicit		GameController() noexcept;
	public:		virtual 		~GameController() noexcept { __noop; }

	public:		bool			Init(HWND hWnd, const Scene::KEY_VALUE_LIST& scenes, uint32 winX, uint32 winY,
										const char* fontFilePath = "", const char* fontFaceName = "") noexcept;

	public:		void			GetWndMsg(UINT message, WPARAM wParam, LPARAM lParam) noexcept;
	public:		void			Update(void) noexcept;
	public:		void			Render(void) noexcept;
	public:		void			Release(void) noexcept;

	public:		static HWND		GetHandle(void) noexcept { return _hWnd; }
	private:	static HWND		_hWnd;
	};
}


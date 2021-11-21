#pragma once
#include "SingletonBase.h"
#include "TypeDefine.h"

namespace ce
{
	class Input final : public SingletonBase<Input>
	{
	public:		enum class KeyState
				{
					UP,
					DOWN,
					PRESS,
				};

	private:	explicit		Input(void) noexcept;
	private:	virtual			~Input(void) noexcept { _hWnd = nullptr; }

	public:		void			Init(HWND hWnd) noexcept { _hWnd = hWnd; }
	public:		void			Update(void) noexcept;
	public:		bool			GetKeyUp(uint8 key) noexcept;
	public:		bool			GetKeyDown(uint8 key) noexcept;
	public:		bool			GetKeyStay(uint8 key) noexcept;

	public:		D3DXVECTOR3		GetMousePosition(void) const noexcept;

	public:		void			GetWndMsgXXX(UINT message, WPARAM wParam, LPARAM lParam) noexcept;
	public:		void			SetInputBlockState(bool b) noexcept { _block = b; }

	private:	KeyState		_eState[255] = {};
	private:	HWND			_hWnd;

	private:	bool			_block = false;
	private:	friend			SingletonBase<Input>;
	};
}

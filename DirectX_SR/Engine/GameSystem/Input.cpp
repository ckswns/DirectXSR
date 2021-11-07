#include "pch.h"
#include "Input.h"

namespace ce
{
	Input::Input(void) noexcept
	{
		ZeroMemory(_bState, sizeof(_bState));
	}

	void Input::Update(void) noexcept
	{
	}

	bool Input::GetKeyUp(uint8 key) noexcept
	{
		if (_bState[key] && !(::GetAsyncKeyState(key) & 0x8000))
		{
			_bState[key] = !_bState[key];
			return true;
		}

		if (!_bState[key] && (::GetAsyncKeyState(key) & 0x8000))
			_bState[key] = !_bState[key];

		return false;
	}

	bool Input::GetKeyDown(uint8 key) noexcept
	{
		if (!_bState[key] && (::GetAsyncKeyState(key) & 0x8000))
		{
			_bState[key] = !_bState[key];
			return true;
		}

		if (_bState[key] && !(::GetAsyncKeyState(key) & 0x8000))
			_bState[key] = !_bState[key];

		return false;
	}

	bool Input::GetKeyStay(uint8 key) noexcept
	{
		if (::GetAsyncKeyState(key) & 0x8000)
			return true;

		return false;
	}

	void Input::GetWndMsgXXX(UINT message, WPARAM wParam, LPARAM lParam) noexcept
	{

	}
}
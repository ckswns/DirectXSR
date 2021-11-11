#include "pch.h"
#include "Input.h"

namespace ce
{
	Input::Input(void) noexcept
	{

	}

	void Input::Update(void) noexcept
	{
		for (int i = 0; i < 255; i++)
		{
			if (_eState[i] == KeyState::DOWN)
				_eState[i] = KeyState::PRESS;
		}
	}

	bool Input::GetKeyUp(uint8 key) noexcept
	{
		if (!(::GetAsyncKeyState(key) & 0x8000))
		{
			_eState[key] = KeyState::UP;
			return true;
		}

		return false;
	}

	bool Input::GetKeyDown(uint8 key) noexcept
	{
		if (_eState[key] == KeyState::UP && (::GetAsyncKeyState(key) & 0x8000))
		{
			_eState[key] = KeyState::DOWN;
			return true;
		}

		if (!::GetAsyncKeyState(key) & 0x8000)
			_eState[key] = KeyState::UP;

		return false;
	}

	bool Input::GetKeyStay(uint8 key) noexcept
	{
		if ((_eState[key] == KeyState::PRESS) && (::GetAsyncKeyState(key) & 0x8000))
			return true;

		if (!::GetAsyncKeyState(key) & 0x8000)
			_eState[key] = KeyState::UP;

		return false;
	}

	void Input::GetWndMsgXXX(UINT message, WPARAM wParam, LPARAM lParam) noexcept
	{

	}
}
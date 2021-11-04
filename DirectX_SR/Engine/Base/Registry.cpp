#include "pch.h"
#include "Registry.h"

namespace ce
{
	bool Registry::Open(HKEY rootKey, const char* subKey) noexcept
	{
		if (!subKey)
			return false;

		if (_isOpen)
			return false;

		if (RegOpenKeyExA(rootKey, subKey, 0, KEY_ALL_ACCESS | KEY_WOW64_64KEY, &_rootKey) != ERROR_SUCCESS)
			return false;

		_isOpen = true;

		return true;
	}

	bool Registry::Close(void) noexcept
	{
		if (RegCloseKey(_rootKey) != ERROR_SUCCESS)
			return false;

		_isOpen = false;

		return true;
	}

	bool Registry::CreateKey(HKEY rootKey, const char* subKey) noexcept
	{
		if (!subKey)
			return false;

		if (_isOpen)
			return false;

		if (RegCreateKeyA(rootKey, subKey, &_rootKey) != ERROR_SUCCESS)
			return false;

		_isOpen = true;

		return true;
	}

	bool Registry::DeleteKey(HKEY rootKey, const char* subKey) noexcept
	{
		if (!subKey)
			return false;

		if (RegDeleteKeyA(rootKey, subKey) != ERROR_SUCCESS)
			return false;

		return true;
	}

	bool Registry::SetValue(const char* valueName, const char* value) noexcept
	{
		if (!valueName || !value)
			return false;

		if (!_isOpen)
			return false;

		if (RegSetValueExA(_rootKey, valueName, 0, REG_SZ, (byte*)value, (DWORD)strlen(value) * sizeof(char))
			!= ERROR_SUCCESS)
			return false;

		return true;
	}

	bool Registry::SetValue(const char* valueName, DWORD value) noexcept
	{
		if (!valueName)
			return false;

		if (!_isOpen)
			return false;

		if (RegSetValueExA(_rootKey, valueName, 0, REG_DWORD, (byte*)&value, sizeof(DWORD))
			!= ERROR_SUCCESS)
			return false;

		return true;
	}

	bool Registry::SetValueBinary(const char* valueName, byte* value, DWORD byteLength) noexcept
	{
		if (!valueName)
			return false;

		if (!_isOpen)
			return false;

		if (RegSetValueExA(_rootKey, valueName, 0, REG_BINARY, value, byteLength)
			!= ERROR_SUCCESS)
			return false;

		return true;
	}

	bool Registry::SetValueForMultiSz(const char* valueName, const char* value, DWORD byteLength) noexcept
	{
		if (!valueName || !value)
			return false;

		if (!_isOpen)
			return false;

		if (RegSetValueExA(_rootKey, valueName, 0, REG_MULTI_SZ, (byte*)value, byteLength)
			!= ERROR_SUCCESS)
			return false;

		return true;
	}

	bool Registry::GetValue(const char* valueName, const char* value, LPDWORD bufferLength) noexcept
	{
		DWORD ValueType = 0;

		if (!valueName || !value || !bufferLength)
			return false;

		if (!_isOpen)
			return false;

		if (RegQueryValueExA(_rootKey, valueName, 0, &ValueType, (byte*)value, bufferLength)
			!= ERROR_SUCCESS)
			return false;

		return true;
	}

	bool Registry::GetValue(const char* valueName, LPDWORD value) noexcept
	{
		DWORD	ValueType = 0;
		DWORD	BufferLength = sizeof(DWORD);

		if (!valueName || !value)
			return false;

		if (!_isOpen)
			return false;

		if (RegQueryValueExA(_rootKey, valueName, 0, &ValueType, (byte*)value, &BufferLength)
			!= ERROR_SUCCESS)
			return false;

		return true;
	}

	bool Registry::DeleteValue(const char* valueName) noexcept
	{
		if (!valueName)
			return false;

		if (!_isOpen)
			return false;

		if (RegDeleteValueA(_rootKey, valueName) != ERROR_SUCCESS)
			return false;

		return true;
	}
}
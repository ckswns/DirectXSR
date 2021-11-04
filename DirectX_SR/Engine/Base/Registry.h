#pragma once
#include "TypeDefine.h"

namespace ce
{
	class Registry final
	{
	public:		explicit	Registry(void) noexcept : _rootKey(nullptr), _isOpen(false) { __noop; }
	public:					~Registry(void) noexcept { __noop; }

	public:		bool		Open(HKEY rootKey, const char* subKey) noexcept;
	public:		bool		Close(void) noexcept;

	public:		bool		CreateKey(HKEY rootKey, const char* subKey) noexcept;
	public:		bool		DeleteKey(HKEY rootKey, const char* subKey) noexcept;

	public:		bool		SetValue(const char* valueName, const char* value) noexcept;
	public:		bool		SetValue(const char* valueName, DWORD value) noexcept;
	public:		bool		SetValueBinary(const char* valueName, byte* value, DWORD byteLength) noexcept;
	public:		bool		SetValueForMultiSz(const char* valueName, const char* value, DWORD byteLength) noexcept;

	public:		bool		GetValue(const char* valueName, const char* value, LPDWORD bufferLength) noexcept;
	public:		bool		GetValue(const char* valueName, LPDWORD value) noexcept;

	public:		bool		DeleteValue(const char* valueName) noexcept;

	public:		HKEY		GetRootKey(void) noexcept { return _rootKey; }

	private:	HKEY		_rootKey;
	private:	bool		_isOpen;
	};
}

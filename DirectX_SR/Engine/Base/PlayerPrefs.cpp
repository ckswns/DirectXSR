#include "pch.h"
#include "PlayerPrefs.h"
#include <atlconv.h>
#include "Assertion.h"

namespace ce
{
	PlayerPrefs::PlayerPrefs(void) noexcept
	{
		if (_registry.Open(HKEY_LOCAL_MACHINE, PLAYERPREFS_REG_SUBKEY) == false)
		{
			if (_registry.CreateKey(HKEY_LOCAL_MACHINE, PLAYERPREFS_REG_SUBKEY) == false)
			{
				CE_ASSERT("ckswns", "PlayerPrefs가 레지스트리 열기및 생성에 실패하였습니다");
			}
		}
		else
		{
			DWORD bufferLength = 0;

			if (bufferLength > 0)
			{
				int64 result = ERROR_SUCCESS;
				
				char valueName[MAX_PATH];
				char buffer[MAX_PATH];
				DWORD size = MAX_PATH;

				for (DWORD i = 0; result == ERROR_SUCCESS; i++)
				{
					result = RegEnumValueA(_registry.GetRootKey(), i, valueName, &size, NULL, NULL, NULL, NULL);

					if (result == ERROR_SUCCESS)
					{
						if (_registry.GetValue(valueName, buffer, &size))
						{
							PrefsData data;
							memcpy(&data, buffer, sizeof(PrefsData));
							_mapData.insert(std::make_pair(valueName, data));
						}
					}
				}
			}
		}
	}

	void PlayerPrefs::DeleteAll(void) noexcept
	{
		_mapData.clear();
		if (_registry.DeleteKey(HKEY_LOCAL_MACHINE, PLAYERPREFS_REG_SUBKEY))
		{
			CE_ASSERT("ckswns", "PlayerPrefs가 레지스트리 키 삭제에 실패하였습니다");
		}
	}

	void PlayerPrefs::DeleteKey(const char* key) noexcept
	{
		auto iter = _mapData.find(std::string(key));

		if (iter != _mapData.end())
		{
			_mapData.erase(iter);
			_registry.DeleteValue(key);
		}
	}

	float PlayerPrefs::GetFloat(const char* key, float defaultValue) noexcept
	{
		auto iter = _mapData.find(key);

		if (iter == _mapData.end())
			return defaultValue;

		if ((iter->second)._eType != DataType::FLOAT)
			return defaultValue;

		return (iter->second)._float;
	}

	int PlayerPrefs::GetInt(const char* key, int defaultValue) noexcept
	{
		auto iter = _mapData.find(key);

		if (iter == _mapData.end())
			return defaultValue;

		if ((iter->second)._eType != DataType::INT)
			return defaultValue;

		return (iter->second)._int;
	}

	std::string PlayerPrefs::GetString(const char* key, const char* defaultValue) noexcept
	{
		auto iter = _mapData.find(key);

		if (iter == _mapData.end())
			return defaultValue;

		if ((iter->second)._eType != DataType::STRING)
			return defaultValue;

		return (iter->second)._string;
	}

	bool PlayerPrefs::HasKey(const char* key) noexcept
	{
		auto iter = _mapData.find(key);

		if (iter == _mapData.end())
			return false;

		return true;
	}

	bool PlayerPrefs::Save(void) noexcept
	{
		for (auto iter = _mapData.begin(); iter != _mapData.end(); iter++)
		{
			if (_registry.SetValueBinary((iter->first.c_str()), (byte*)(&(iter->second)), sizeof(PrefsData)) == false)
				return false;
		}

		return true;
	}

	void PlayerPrefs::SetFloat(const char* key, float value) noexcept
	{
		auto iter = _mapData.find(key);

		if (iter == _mapData.end())
		{
			_mapData.insert(std::make_pair(key, PrefsData(value)));
		}
		else
		{
			(iter->second)._float = value;
			(iter->second)._eType = DataType::FLOAT;
		}
	}

	void PlayerPrefs::SetInt(const char* key, int value) noexcept 
	{
		auto iter = _mapData.find(key);

		if (iter == _mapData.end())
		{
			_mapData.insert(std::make_pair(key, PrefsData(value)));
		}
		else
		{
			(iter->second)._int = value;
			(iter->second)._eType = DataType::INT;
		}
	}

	void PlayerPrefs::SetString(const char* key, const char* value) noexcept
	{
		auto iter = _mapData.find(key);

		if (iter == _mapData.end())
		{
			_mapData.insert(std::make_pair(key, PrefsData(value)));
		}
		else
		{
			memcpy((iter->second)._string, value, strlen(value) + 1);
			(iter->second)._eType = DataType::STRING;
		}
	}
}
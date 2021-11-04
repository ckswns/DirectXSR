#pragma once
#include "SingletonBase.h"
#include "Registry.h"

#define PLAYERPREFS_REG_SUBKEY "CE_PLAYER_PREFS_REG"
#define PLAYERPREFS_STR_MAXSIZE 128

namespace ce
{
	class PlayerPrefs final : public SingletonBase<PlayerPrefs>
	{
	private:	explicit		PlayerPrefs(void) noexcept;
	private:					~PlayerPrefs(void) noexcept { __noop; }

	private:	enum class		DataType
				{
					INT,
					FLOAT,
					STRING,
					END
				};

	private:	struct			PrefsData
				{
				explicit		PrefsData() noexcept : _eType(DataType::END) { __noop; }
				explicit		PrefsData(int intData) noexcept :
									_int(intData), _eType(DataType::INT) { __noop; }
				explicit		PrefsData(float floatData) noexcept :
									_float(floatData), _eType(DataType::FLOAT) { __noop; }
				explicit		PrefsData(const char* strData) noexcept :
									_eType(DataType::STRING) { strcpy_s(_string, PLAYERPREFS_STR_MAXSIZE, strData); }

				union
				{
					int			_int;
					float		_float;
					char		_string[PLAYERPREFS_STR_MAXSIZE];
				};

				DataType		_eType;
				};

	public:		void			DeleteAll(void) noexcept;
	public:		void			DeleteKey(const char* key) noexcept;

	public:		float			GetFloat(const char* key, float defaultValue = 0) noexcept;
	public:		int				GetInt(const char* key, int defaultValue = 0) noexcept;
	public:		std::string		GetString(const char* key, const char* defaultValue = "") noexcept;

	public:		bool			HasKey(const char* key) noexcept;
	public:		bool			Save(void) noexcept;

	public:		void			SetFloat(const char* key, float value) noexcept;
	public:		void			SetInt(const char* key, int value) noexcept;
	public:		void			SetString(const char* key, const char* value) noexcept;

	private:	using			DATA_MAP = std::unordered_map<std::string, PrefsData>;

	private:	DATA_MAP		_mapData;
	private:	Registry		_registry;

	private:	friend			SingletonBase<PlayerPrefs>;
	};
}

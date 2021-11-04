#pragma once
#include "../Base/SingletonBase.h"

namespace ce
{
	struct INIDATA
	{
		std::string section;
		std::string key;
		std::string value;
	};

	class INIManager : public SingletonBase<INIManager>
	{
	private:	explicit		INIManager(void) noexcept { __noop; }
	private:	virtual			~INIManager(void) noexcept { __noop; }

	private:	using			VecIniData = std::vector<INIDATA>;
	private:	using			VecIniDataIter = std::vector<INIDATA>::iterator;
	private:	using			VecIniDatas = std::vector<VecIniData>;
	private:	using			VecIniDatasIter = std::vector<VecIniData>::iterator;

	public:		void			AddData(std::string section, std::string key, std::string value);
	public:		void			SaveIni(std::string fileName);
	public:		std::string		LoadDataString(std::string fileName, std::string section, std::string key);
	public:		int				LoadDataInteger(std::string fileName, std::string section, std::string key);

	private:	VecIniDatas		m_vIniData;

	private:	friend			SingletonBase<INIManager>;
	};
}

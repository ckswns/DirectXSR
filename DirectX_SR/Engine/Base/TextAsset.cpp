#include "pch.h"
#include "TextAsset.h"
#include "../Base/Parser.h"

namespace ce
{
	TextAsset::TextAsset(void) noexcept :
		Asset(AssetType::TEXT)
	{
	}

	bool TextAsset::Load(std::string _filePath) noexcept
	{
		PARSER::CSV_DATA* data = new PARSER::CSV_DATA();
		PARSER::CSVParser parser;
		parser(_filePath, data);
		_data = data;

		return true;
	}

	void TextAsset::Release(void) noexcept
	{
		PARSER::CSV_DATA* ptr = reinterpret_cast<PARSER::CSV_DATA*>(_data);
		delete ptr;
		ptr = nullptr;
		_data = nullptr;
	}
}
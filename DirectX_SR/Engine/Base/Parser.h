#pragma once

#ifndef __PARSER_H__
#define __PARSER_H__

#ifndef OUT
#define OUT
#endif

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <istream>
#include <assert.h>
#include <atlconv.h>

namespace ce
{
	namespace PARSER
	{
		using CSV_DATA = std::vector<std::vector<std::string>>;
		using CSV_ROW_DATA = std::vector<std::string>;

		class CSVParser
		{
		public:		void operator()(std::string _filePath, OUT CSV_DATA* _pData) noexcept
					{
						std::wifstream file;
						file.open(_filePath);
						assert(!file.fail() && "파일이 경로에 존재하지 않습니다");

						while (file.good())
						{
							_pData->push_back(CSV_ROW_DATA());

							ReadRow(file, ',', (*_pData)[_pData->size() - 1]);
						}
					}

		private:	void ReadRow(std::wifstream& _file, char _spliter, OUT CSV_ROW_DATA& _rowData) noexcept
					{
						std::wstringstream ss;
						bool inquotes = false;

						while (_file.good())
						{
							wchar_t c = _file.get();
							if (!inquotes && c == '"')
								inquotes = true;
							else if (inquotes && c == '"')
							{
								if (_file.peek() == '"')
									ss << (wchar_t)_file.get();
								else
									inquotes = false;
							}
							else if (!inquotes && c == _spliter)
							{
								std::string temp = strconv(ss.str());
								_rowData.push_back(temp);

								ss.str(L"");
							}
							else if (!inquotes && (c == '\r' || c == '\n'))
							{
								if (_file.peek() == '\n')
									_file.get();
								std::string temp = strconv(ss.str());
								_rowData.push_back(temp);

								return;
							}
							else
							{
								ss << c;
							}
						}
					}

		private:	std::string strconv(const std::wstring& _src)
					{
						USES_CONVERSION;

						return std::string(W2A(_src.c_str()));
					}
		};
	}
}

#endif
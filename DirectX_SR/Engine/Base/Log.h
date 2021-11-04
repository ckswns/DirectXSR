#pragma once

#ifndef __LOG_H__
#define __LOG_H__

#include <chrono>
#include <ctime>   
#include <fstream>
#include <iostream>

namespace ce
{
	namespace Log
	{
		static bool WriteLog(const char* filePath, const char* str)
		{
			auto now = std::chrono::system_clock::now();
			std::time_t time = std::chrono::system_clock::to_time_t(now);

			std::ofstream file(filePath, std::ios::app);

			if (file.is_open()) 
			{
				char tmBuff[30];
				ctime_s(tmBuff, sizeof(tmBuff), &time);

				file << "date : " << tmBuff;
				file << str;
				file.close();
				
				return true;
			}

			return false;
		}
	}
}

#endif
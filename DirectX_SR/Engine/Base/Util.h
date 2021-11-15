#pragma once

#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdlib.h>
#include <random>
#include <ctime>
#include <vector>
#include <sstream>

namespace ce
{
	namespace Random
	{
		static int GetValue(int maxValue, int minValue = 0) noexcept
		{
			static bool isInit = false;

			if (!isInit)
			{
				std::srand(static_cast<unsigned int>(std::time(NULL)));
				isInit = true;
			}

			return (std::rand() % (maxValue - minValue)) + minValue;
		}
	}

	namespace Util
	{
		static std::vector<std::string> Split(std::string input, char delimiter) {

			std::vector<std::string> result;
			std::stringstream ss(input);
			std::string temp;

			while (getline(ss, temp, delimiter)) {
				result.push_back(temp);
			}

			return result;
		}
	}
}
#endif
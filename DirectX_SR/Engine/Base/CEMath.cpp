#include "pch.h"
#include "CEMath.h"
#include <math.h>
#include <stdlib.h>
#include <random>
#include <ctime>

namespace ce
{
    namespace CE_MATH
    {
		static bool randomInit = false;

        bool equl_f(const float lhs, const float rhs) noexcept
        {
            return std::fabs(lhs - rhs) < FLOAT_EPSILON ? true : false;
        }

        int Random(int max) noexcept
        {
			if (!randomInit)
			{
				std::srand(static_cast<unsigned int>(std::time(NULL)));
				randomInit = true;
			}

			return std::rand() % (max);
        }

        int Random(int min, int max) noexcept
        {
			if (!randomInit)
			{
				std::srand(static_cast<unsigned int>(std::time(NULL)));
				randomInit = true;
			}

			return (std::rand() % (max - min)) + min;
        }
    }
}
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

		float GetAngle(float startX, float startY, float endX, float endY)
		{
			float x = endX - startX;
			float y = endY - startY;

			float distance = sqrtf(x * x + y * y);
			float angle = acos(x / distance);

			if (endY > startY)
			{
				angle = PI2 - angle;
				if (angle >= PI2) angle -= PI2;
			}

			return angle;
		}
    }
}
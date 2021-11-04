#pragma once

namespace ce
{
	namespace CE_MATH
	{
		constexpr float				PI = 3.141592654f;
		constexpr float				PI2 = (PI * 2);

		constexpr float				PI_2 = (PI / 2);
		constexpr float				PI_4 = (PI / 4);
		constexpr float				PI_8 = (PI / 8);
		constexpr float				PI_16 = (PI / 16);
		constexpr float				PI_32 = (PI / 32);

		constexpr float				FLOAT_EPSILON = 0.001f;

		bool	equl_f(const float lhs, const float rhs) noexcept;

		int		Random(int max) noexcept;
		int		Random(int min, int max) noexcept;

	}
}

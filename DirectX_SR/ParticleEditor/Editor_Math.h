#pragma once
#ifndef __EDITOR_MATH_H__
#define __EDITOR_MATH_H__

inline float SignedRandomf(float max)noexcept
{
	if (max < 1) return max;

	float f = ce::CE_MATH::Random(1000);
	f *= 0.001f;

	float value = ce::CE_MATH::Random((max*2));
	if (value >= max)
	{
		value -= max;
		value *= -1;
		value -= f;
	}
	else
		value += f;
	return value;

}

inline float UnsignedRandomf(float max)noexcept
{
	if (max < 1) return max;

	float f = ce::CE_MATH::Random(1000);
	f *= 0.001f;

	float value = ce::CE_MATH::Random(max);

	return value + f;
}

#endif // !__EDITOR_MATH_H__

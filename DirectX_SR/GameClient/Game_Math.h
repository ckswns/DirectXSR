#pragma once
#ifndef __GAME_MATH_H__
#define __GAME_MATH_H__

//���� ����(absTolerance) ������ �� �� 
inline int CompareFloatAbsoulte(float a, float b, float absTolerance = 0.3f)
{
	float diff = a - b;
	if (fabs(diff) <= absTolerance)
		return 0;
	return (diff > 0) ? 1 : -1;
}

inline float SignedRandomf(float max)noexcept
{
	if (max < 1) return max;

	float f = ce::CE_MATH::Random(1000);
	f *= 0.001f;

	float value = ce::CE_MATH::Random(-max,max);
	if (value <0)
	{
		value -= f;
	}
	else
		value += f;
	return value;

}

//��ȣ���� float ����
inline float UnsignedRandomf(float max)noexcept
{
	if (max < 1) return max;

	float f = ce::CE_MATH::Random(1000);
	f *= 0.001f;

	float value = ce::CE_MATH::Random(max);

	return value + f;
}

#endif // !__GAME_MATH_H__
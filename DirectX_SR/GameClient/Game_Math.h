#pragma once
#ifndef __GAME_MATH_H__
#define __GAME_MATH_H__

//오차 범위(absTolerance) 내에서 값 비교 
inline int CompareFloatAbsoulte(float a, float b, float absTolerance = 0.3f)
{
	float diff = a - b;
	if (fabs(diff) <= absTolerance)
		return 0;
	return (diff > 0) ? 1 : -1;
}


#endif // !__GAME_MATH_H__
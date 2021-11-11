#include "pch.h"
#include "CETween.h"
#include "CEMath.h"
#include <math.h>

namespace ce
{
	namespace CETween
	{
		float Lerp(float from, float to, float t, EaseType easeType) noexcept
		{
			float time = GetEaseTime(t, easeType);
			return from * (1 - time) + to * time;
		}

		float easeLiner(float t) noexcept
		{
			return t;
		}

		float easeInSine(float t) noexcept
		{
			return 1 - cosf((t * CE_MATH::PI) / 2.f);
		}

		float easeOutSine(float t) noexcept
		{
			return sinf((t * CE_MATH::PI) / 2.f);
		}

		float easeInOutSine(float t) noexcept
		{
			return -(cosf(CE_MATH::PI * t) - 1) / 2.f;
		}

		float easeInQuad(float t) noexcept
		{
			return t * t;
		}

		float easeOutQuad(float t) noexcept
		{
			return 1 - (1 - t) * (1 - t);
		}

		float easeInOutQuad(float t) noexcept
		{
			return t < 0.5f ? 2 * t * t : 1 - powf(-2 * t + 2, 2) / 2.f;
		}

		float easeInCubic(float t) noexcept
		{
			return t * t * t;
		}

		float easeOutCubic(float t) noexcept
		{
			return 1 - powf(1 - t, 3);
		}

		float easeInOutCubic(float t) noexcept
		{
			return t < 0.5f ? 4 * t * t * t : 1 - powf(-2 * t + 2, 3) / 2.f;
		}

		float easeInQuart(float t) noexcept
		{
			return t * t * t * t;
		}

		float easeOutQuart(float t) noexcept
		{
			return 1 - powf(1 - t, 4);
		}

		float easeInOutQuart(float t) noexcept
		{
			return t < 0.5f ? 8 * t * t * t * t : 1 - powf(-2 * t + 2, 4) / 2.f;
		}

		float easeInQuint(float t) noexcept
		{
			return t * t * t * t * t;
		}

		float easeOutQuint(float t) noexcept
		{
			return 1 - powf(1 - t, 5);
		}

		float easeInOutQuint(float t) noexcept
		{
			return t < 0.5f ? 16 * t * t * t * t * t : 1 - powf(-2 * t + 2, 5) / 2.f;
		}

		float easeInExpo(float t) noexcept
		{
			return t == 0 ? 0 : powf(2, 10 * t - 10);
		}

		float easeOutExpo(float t) noexcept
		{
			return t == 1 ? 1 : 1 - powf(2, -10 * t);
		}

		float easeInOutExpo(float t) noexcept
		{
			return t == 0
				? 0
				: t == 1
				? 1
				: t < 0.5f ? powf(2, 20 * t - 10) / 2.f
				: (2 - pow(2, -20 * t + 10)) / 2.f;
		}

		float easeInCirc(float t) noexcept
		{
			return 1 - sqrtf(1 - powf(t, 2));
		}

		float easeOutCirc(float t) noexcept
		{
			return sqrtf(1 - powf(t - 1, 2));
		}

		float easeInOutCirc(float t) noexcept
		{
			return t < 0.5f
				? (1 - sqrtf(1 - powf(2 * t, 2))) / 2.f
				: (sqrtf(1 - powf(-2 * t + 2, 2)) + 1) / 2.f;
		}

		float easeInBack(float t) noexcept
		{
			const float c1 = 1.70158f;
			const float c3 = c1 + 1;

			return c3 * t * t * t - c1 * t * t;
		}

		float easeOutBack(float t) noexcept
		{
			const float c1 = 1.70158f;
			const float c3 = c1 + 1;

			return 1 + c3 * powf(t - 1, 3) + c1 * powf(t - 1, 2);
		}

		float easeInOutBack(float t) noexcept
		{
			const float c1 = 1.70158f;
			const float c2 = c1 * 1.525f;

			return t < 0.5f
				? (powf(2 * t, 2) * ((c2 + 1) * 2 * t - c2)) / 2.f
				: (powf(2 * t - 2, 2) * ((c2 + 1) * (t * 2 - 2) + c2) + 2) / 2.f;
		}

		float easeInElastic(float t) noexcept
		{
			const float c4 = (2 * CE_MATH::PI) / 3.f;

			return t == 0
				? 0
				: t == 1
				? 1
				: -powf(2, 10 * t - 10) * sinf((t * 10 - 10.75f) * c4);
		}

		float easeOutElastic(float t) noexcept
		{
			const float c4 = (2 * CE_MATH::PI) / 3.f;

			return t == 0
				? 0
				: t == 1
				? 1
				: powf(2, -10 * t) * sinf((t * 10 - 0.75f) * c4) + 1;
		}

		float easeInOutElastic(float t) noexcept
		{
			const float c5 = (2 * CE_MATH::PI) / 4.5f;

			return t == 0
				? 0
				: t == 1
				? 1
				: t < 0.5f
				? -(powf(2, 20 * t - 10) * sinf((20 * t - 11.125f) * c5)) / 2.f
				: (powf(2, -20 * t + 10) * sinf((20 * t - 11.125f) * c5)) / 2.f + 1;
		}

		float easeInBounce(float t) noexcept
		{
			return 1 - easeOutBounce(1 - t);
		}

		float easeOutBounce(float t) noexcept
		{
			const float n1 = 7.5625f;
			const float d1 = 2.75f;

			if (t < 1 / d1) {
				return n1 * t * t;
			}
			else if (t < 2 / d1) {
				return n1 * (t -= 1.5 / d1) * t + 0.75f;
			}
			else if (t < 2.5f / d1) {
				return n1 * (t -= 2.25f / d1) * t + 0.9375f;
			}
			else {
				return n1 * (t -= 2.625f / d1) * t + 0.984375f;
			}
		}

		float easeInOutBounce(float t) noexcept
		{
			return t < 0.5f
				? (1 - easeOutBounce(1 - 2 * t)) / 2.f
				: (1 + easeOutBounce(2 * t - 1)) / 2.f;
		}

		float GetEaseTime(float t, EaseType easeType) noexcept
		{
			switch (easeType)
			{
			case EaseType::easeLiner:
				return easeLiner(t);
				break;

			case EaseType::easeInSine:
				return easeInSine(t);
				break;

			case EaseType::easeOutSine:
				return easeOutSine(t);
				break;

			case EaseType::easeInOutSine:
				return easeInOutSine(t);
				break;

			case EaseType::easeInQuad:
				return easeInQuad(t);
				break;

			case EaseType::easeOutQuad:
				return easeOutQuad(t);
				break;

			case EaseType::easeInOutQuad:
				return easeInOutQuad(t);
				break;

			case EaseType::easeInCubic:
				return easeInCubic(t);
				break;

			case EaseType::easeOutCubic:
				return easeOutCubic(t);
				break;

			case EaseType::easeInOutCubic:
				return easeInOutCubic(t);
				break;

			case EaseType::easeInQuart:
				return easeInQuart(t);
				break;

			case EaseType::easeOutQuart:
				return easeOutQuart(t);
				break;

			case EaseType::easeInOutQuart:
				return easeInOutQuart(t);
				break;

			case EaseType::easeInQuint:
				return easeInQuint(t);
				break;

			case EaseType::easeOutQuint:
				return easeOutQuint(t);
				break;

			case EaseType::easeInOutQuint:
				return easeInOutQuint(t);
				break;

			case EaseType::easeInExpo:
				return easeInExpo(t);
				break;

			case EaseType::easeOutExpo:
				return easeOutExpo(t);
				break;

			case EaseType::easeInOutExpo:
				return easeInOutExpo(t);
				break;

			case EaseType::easeInCirc:
				return easeInCirc(t);
				break;

			case EaseType::easeOutCirc:
				return easeOutCirc(t);
				break;

			case EaseType::easeInOutCirc:
				return easeInOutCirc(t);
				break;

			case EaseType::easeInBack:
				return easeInBack(t);
				break;

			case EaseType::easeOutBack:
				return easeOutBack(t);
				break;

			case EaseType::easeInOutBack:
				return easeInOutBack(t);
				break;

			case EaseType::easeInElastic:
				return easeInElastic(t);
				break;

			case EaseType::easeOutElastic:
				return easeOutElastic(t);
				break;

			case EaseType::easeInOutElastic:
				return easeInOutElastic(t);
				break;

			case EaseType::easeInBounce:
				return easeInBounce(t);
				break;

			case EaseType::easeOutBounce:
				return easeOutBounce(t);
				break;

			case EaseType::easeInOutBounce:
				return easeInOutBounce(t);
				break;

			default:
				return t;
				break;
			}
		}
	}
}
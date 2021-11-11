#pragma once

namespace ce
{
	namespace CETween
	{
		enum class EaseType
		{
			easeLiner,
			easeInSine,
			easeOutSine,
			easeInOutSine,
			easeInQuad,
			easeOutQuad,
			easeInOutQuad,
			easeInCubic,
			easeOutCubic,
			easeInOutCubic,
			easeInQuart,
			easeOutQuart,
			easeInOutQuart,
			easeInQuint,
			easeOutQuint,
			easeInOutQuint,
			easeInExpo,
			easeOutExpo,
			easeInOutExpo,
			easeInCirc,
			easeOutCirc,
			easeInOutCirc,
			easeInBack,
			easeOutBack,
			easeInOutBack,
			easeInElastic,
			easeOutElastic,
			easeInOutElastic,
			easeInBounce,
			easeOutBounce,
			easeInOutBounce
		};

		static float	Lerp(float from, float to, float t, EaseType easeType = EaseType::easeLiner) noexcept;
		static float	GetEaseTime(float t, EaseType easeType) noexcept;

		static float	easeLiner(float t) noexcept;
		static float	easeInSine(float t) noexcept;
		static float	easeOutSine(float t) noexcept;
		static float	easeInOutSine(float t) noexcept;
		static float	easeInQuad(float t) noexcept;
		static float	easeOutQuad(float t) noexcept;
		static float	easeInOutQuad(float t) noexcept;
		static float	easeInCubic(float t) noexcept;
		static float	easeOutCubic(float t) noexcept;
		static float	easeInOutCubic(float t) noexcept;
		static float	easeInQuart(float t) noexcept;
		static float	easeOutQuart(float t) noexcept;
		static float	easeInOutQuart(float t) noexcept;
		static float	easeInQuint(float t) noexcept;
		static float	easeOutQuint(float t) noexcept;
		static float	easeInOutQuint(float t) noexcept;
		static float	easeInExpo(float t) noexcept;
		static float	easeOutExpo(float t) noexcept;
		static float	easeInOutExpo(float t) noexcept;
		static float	easeInCirc(float t) noexcept;
		static float	easeOutCirc(float t) noexcept;
		static float	easeInOutCirc(float t) noexcept;
		static float	easeInBack(float t) noexcept;
		static float	easeOutBack(float t) noexcept;
		static float	easeInOutBack(float t) noexcept;
		static float	easeInElastic(float t) noexcept;
		static float	easeOutElastic(float t) noexcept;
		static float	easeInOutElastic(float t) noexcept;
		static float	easeInBounce(float t) noexcept;
		static float	easeOutBounce(float t) noexcept;
		static float	easeInOutBounce(float t) noexcept;
	};
}

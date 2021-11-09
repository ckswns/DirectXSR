#include "pch.h"
#include "RectTransform.h"

namespace ce
{
	namespace UI
	{
		RectTransform::RectTransform(void) noexcept :
			Component(CONST_VALUES::COMPONENT_ID::RECT_TRANSFORM),
			_pivot(),
			_width(0),
			_height(0)
		{
			_pivot.x = 0.0f;
			_pivot.y = 0.0f;
		}

		void RectTransform::Init(void) noexcept
		{
			_transform = _owner->GetTransform();
		}

		void RectTransform::Update(float) noexcept
		{

		}

		void RectTransform::Release(void) noexcept
		{

		}
	}
}
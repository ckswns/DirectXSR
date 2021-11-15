#include "pch.h"
#include "RectTransform.h"
#include "Transform.h"

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

		void RectTransform::LateUpdate(float) noexcept
		{
			D3DXVECTOR3 pos = _transform->GetWorldPosition();

			_pickingRect.left = pos.x - (_width * (_pivot.x));
			_pickingRect.right = pos.x + (_width * (1 - _pivot.x));
			_pickingRect.top = pos.y - (_height * (_pivot.y));
			_pickingRect.bottom = pos.y + (_height * (1 - _pivot.y));
		}
	}
}
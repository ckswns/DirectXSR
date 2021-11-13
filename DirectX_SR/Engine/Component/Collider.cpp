#include "pch.h"
#include "Collider.h"

namespace ce
{
	void Collider::Init(void) noexcept
	{
		_transform = _owner->GetTransform();
		Open();
	}

	void Collider::Release(void) noexcept
	{

		Close();
	}
}
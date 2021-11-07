#pragma once
#include "Collider.h"

namespace ce
{
	class SphereCollider : Collider
	{
	public:		explicit		SphereCollider(void) noexcept;
	public:		virtual			~SphereCollider(void) noexcept { __noop; }
	};
}

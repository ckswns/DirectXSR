#include "pch.h"
#include "Collider.h"

namespace ce
{
	Collider::Collider(void) noexcept :
		Component(COMPONENT_ID::COLLIDER)
	{
	}

	Collider::~Collider(void) noexcept
	{
		__noop;
	}

	void Collider::Init(void) noexcept
	{

	}

	void Collider::Update(float) noexcept
	{

	}

	void Collider::Render(void) noexcept
	{

	}

	void Collider::Release(void) noexcept
	{

	}
}
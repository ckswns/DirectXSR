#include "pch.h"
#include "Component.h"
#include "GameObject.h"

void ce::Component::RemoveComponent(void) noexcept
{
	if (_owner) { _owner->RemoveComponent(this); }
}
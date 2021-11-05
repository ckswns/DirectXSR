#include "pch.h"
#include "Behaviour.h"
#include "ConstValues.h"

namespace ce
{
	void Behaviour::Init(void) noexcept
	{
		transform = _owner->GetTransform();
		gameObject = _owner;
		Awake();
		Start();
	}

	void Behaviour::Render(void) noexcept
	{
#ifdef _DEBUG
		DbgRender();
#endif
	}
}
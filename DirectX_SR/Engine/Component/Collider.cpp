#include "pch.h"
#include "Collider.h"
#include "PhysicsManager.h"

namespace ce
{
	void Collider::Init(void) noexcept
	{
		_transform = _owner->GetTransform();
		PhysicsManager::Instance()->InsertColliderXXX(this);
		Open();
	}

	void Collider::Release(void) noexcept
	{
		PhysicsManager::Instance()->RemoveColliderXXX(this);
		Close();
	}

	void Collider::Update(float) noexcept
	{
#ifdef _DEBUG
		if (INPUT->GetKeyDown(VK_CAPITAL))
		{
			_showDbg = !_showDbg;
		}
#endif
	}
}
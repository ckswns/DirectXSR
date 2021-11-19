#include "pch.h"
#include "Collider.h"
#include "PhysicsManager.h"
#include "GameObject.h"

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
	void Collider::SetEnable(bool enable) noexcept
	{
		_bEnable = false;
		Rigidbody* rb = static_cast<Rigidbody*>(_owner->GetComponent(COMPONENT_ID::RIGIDBODY));
		if (rb == nullptr)
			return;

		Rigidbody::CollisionList& collList = const_cast<Rigidbody::CollisionList&>(rb->GetCollisionList());

		for (auto iter = collList.begin(); iter != collList.end();)
		{
			if ((*iter).first == this)
			{
				rb->GetGameObject()->OnCollisionExitXXX((*iter).first, (*iter).second);
				iter = collList.erase(iter);
			}
			else
				iter++;
		}
	}
}
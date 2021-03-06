#include "pch.h"
#include "Collider.h"
#include "PhysicsManager.h"
#include "GameObject.h"

namespace ce
{
#ifdef _DEBUG
	bool Collider::_showDbg = false;
#endif

	void Collider::Init(void) noexcept
	{
		_transform = _owner->GetTransform();
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
	void Collider::LateUpdate(float) noexcept
	{
		if (_bInserted == false)
		{
			PhysicsManager::Instance()->InsertColliderXXX(this);
			_bInserted = true;
		}

		if (_bEnbaleChanged)
		{
			_bEnbaleChanged = false;

			_bEnable = _bDirtEnable;

			if (_bDirtEnable == true)
				return;

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
					continue;
				}
				else
					iter++;
			}
		}
	}

	void Collider::SetEnable(bool enable) noexcept
	{
		if (_bEnable == enable)
			return;

		_bEnbaleChanged = true;
		_bDirtEnable = enable;
	}
}
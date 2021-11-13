#include "pch.h"
#include "PhysicsManager.h"
#include "Assertion.h"

namespace ce
{
	void PhysicsManager::Update(void) noexcept
	{

	}

	void PhysicsManager::Release(void) noexcept
	{
		_colliders.clear();
	}

	void PhysicsManager::InsertColliderXXX(Collider* collider) noexcept
	{
		auto iter = std::find(_colliders.begin(), _colliders.end(), collider);

		if (iter == _colliders.end())
			_colliders.push_back(collider);
		else
			CE_ASSERT("ckswns", "중복된 요청입니다");
	}

	void PhysicsManager::RemoveColliderXXX(Collider* collider) noexcept
	{
		auto iter = std::find(_colliders.begin(), _colliders.end(), collider);

		if (iter == _colliders.end())
		{
			CE_ASSERT("ckswns", "collider가 이미 container에 존재하지 않습니다.");
		}
		else
			_colliders.erase(iter);
	}
}
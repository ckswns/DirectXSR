#include "pch.h"
#include "PhysicsManager.h"
#include "Assertion.h"
#include "GameObject.h"

namespace ce
{
	void PhysicsManager::Update(void) noexcept
	{
		for (int i = 0; i < _rigidbodys.size(); i++)
		{
			if (_rigidbodys[i]->GetGameObject()->GetActive() == false)
				continue;

			if (_rigidbodys[i]->GetEnable() == false)
				continue;
			
			const Collider::TList& collidersR = _rigidbodys[i]->GetColliders();

			for (int j = 0; j < collidersR.size(); j++)
			{
				if (collidersR[j]->GetEnable() == false)
					continue;

				for (int k = 0; k < _colliders.size(); k++)
				{
					if (collidersR[j]->GetGameObject() == _colliders[k]->GetGameObject())
						continue;

					if (_colliders[k]->GetEnable() == false)
						continue;

					if (collidersR[j]->CheckCollision(_colliders[k]))
					{
						_rigidbodys[i]->OnCollideWith(collidersR[j], _colliders[k]);
					}
					else
					{
						_rigidbodys[i]->OnNotCollideWith(collidersR[j], _colliders[k]);
					}
				}
			}
		}
	}

	void PhysicsManager::Release(void) noexcept
	{
		_colliders.clear();
	}

	void PhysicsManager::InsertRigidbodyXXX(Rigidbody* rigidbody) noexcept
	{
		auto iter = std::find(_rigidbodys.begin(), _rigidbodys.end(), rigidbody);

		if (iter == _rigidbodys.end())
			_rigidbodys.push_back(rigidbody);
		else
			CE_ASSERT("ckswns", "중복된 요청입니다");
	}

	void PhysicsManager::RemoveRigidbodyXXX(Rigidbody* rigidbody) noexcept
	{
		auto iter = std::find(_rigidbodys.begin(), _rigidbodys.end(), rigidbody);

		if (iter == _rigidbodys.end())
		{
			//CE_ASSERT("ckswns", "Container에 Rigidbody가 이미 존재하지 않습니다.");
		}
		else
			_rigidbodys.erase(iter);
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
			//CE_ASSERT("ckswns", "collider가 이미 container에 존재하지 않습니다.");
		}
		else
			_colliders.erase(iter);
	}
}
#include "pch.h"
#include "PhysicsManager.h"
#include "Assertion.h"

namespace ce
{
	void PhysicsManager::Update(void) noexcept
	{
		for (int i = 0; i < _rigidbodys.size(); i++)
		{
			const Collider::TList& collidersR = _rigidbodys[i]->GetColliders();

			for (int j = 0; j < collidersR.size(); j++)
			{
				if (collidersR[j]->GetGameObject()->GetActive() == false)
					continue;

				for (int k = 0; k < _colliders.size(); k++)
				{
					if (collidersR[j]->GetGameObject() == _colliders[k]->GetGameObject())
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
			CE_ASSERT("ckswns", "�ߺ��� ��û�Դϴ�");
	}

	void PhysicsManager::RemoveRigidbodyXXX(Rigidbody* rigidbody) noexcept
	{
		auto iter = std::find(_rigidbodys.begin(), _rigidbodys.end(), rigidbody);

		if (iter == _rigidbodys.end())
		{
			CE_ASSERT("ckswns", "Container�� Rigidbody�� �̹� �������� �ʽ��ϴ�.");
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
			CE_ASSERT("ckswns", "�ߺ��� ��û�Դϴ�");
	}

	void PhysicsManager::RemoveColliderXXX(Collider* collider) noexcept
	{
		auto iter = std::find(_colliders.begin(), _colliders.end(), collider);

		if (iter == _colliders.end())
		{
			CE_ASSERT("ckswns", "collider�� �̹� container�� �������� �ʽ��ϴ�.");
		}
		else
			_colliders.erase(iter);
	}
}
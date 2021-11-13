#include "pch.h"
#include "Rigidbody.h"
#include "PhysicsManager.h"

namespace ce
{
	Rigidbody::Rigidbody(void) noexcept :
		Component(COMPONENT_ID::RIGIDBODY, true, true, COMPONENT_ID::COLLIDER),
		_force(),
		_gravity(0)
	{

	}

	void Rigidbody::Init(void) noexcept
	{
		if (_owner->HasComponent(COMPONENT_ID::COLLIDER) == false)
			CE_ASSERT("ckswns", "Rigidbody의 GameObject에 Collider가 없습니다");

		const std::vector<Component*>& components = _owner->GetComponents();
		
		for (int i = 0; i < components.size(); i++)
		{
			if (components[i]->GetID() == COMPONENT_ID::COLLIDER)
				_colliders.push_back(static_cast<Collider*>(components[i]));
		}

		PhysicsManager::Instance()->InsertRigidbodyXXX(this);
	}

	void Rigidbody::FixedUpdate(float) noexcept
	{
	}

	void Rigidbody::Update(float) noexcept
	{
		
	}

	void Rigidbody::LateUpdate(float) noexcept
	{
	}

	void Rigidbody::Render(void) noexcept
	{

	}

	void Rigidbody::Release(void) noexcept
	{
		PhysicsManager::Instance()->RemoveRigidbodyXXX(this);
	}

	void Rigidbody::AddForce(D3DXVECTOR3 force) noexcept
	{
		_force += force;
	}

	void Rigidbody::AddForce(float x, float y, float z) noexcept
	{
		_force += D3DXVECTOR3(x, y, z);
	}

	void Rigidbody::SetFreezePosition(bool freezeX, bool freezeY, bool freezeZ) noexcept
	{
		_bFreezePositionX = freezeX;
		_bFreezePositionY = freezeY;
		_bFreezePositionZ = freezeZ;
	}

	void Rigidbody::SetFreezeRotation(bool freezeX, bool freezeY, bool freezeZ) noexcept
	{
		_bFreezeRotationX = freezeX;
		_bFreezeRotationY = freezeY;
		_bFreezeRotationZ = freezeZ;
	}

	void Rigidbody::OnCollideWith(Collider* mine, Collider* other) noexcept
	{
		auto iter = std::find(_collisionList.begin(), _collisionList.end(), std::make_pair(mine, other));

		if (iter == _collisionList.end())
			_owner->OnCollisionEnterXXX(mine, other);
		else
			_owner->OnCollisionStayXXX(mine, other);
	}

	void Rigidbody::OnNotCollideWith(Collider* mine, Collider* other) noexcept
	{
		auto iter = std::find(_collisionList.begin(), _collisionList.end(), std::make_pair(mine, other));

		if (iter == _collisionList.end())
			return;

		_owner->OnCollisionExitXXX(mine, other);
		_collisionList.erase(iter);
	}
}
#pragma once
#include "Component.h"
#include "Collider.h"

namespace ce
{
	class Transform;

	class Rigidbody final : public Component
	{
	public:		using					TList = std::vector<Rigidbody*>;
	public:		using					CollisionList = std::vector<std::pair<Collider*, Collider*>>;
	public:		explicit				Rigidbody(void) noexcept;
	public:		virtual					~Rigidbody(void) noexcept { __noop; }

	public:		void					Init(void) noexcept override;
	public:		void					FixedUpdate(float) noexcept override;
	public:		void					Update(float) noexcept override;
	public:		void					LateUpdate(float) noexcept override;
	public:		void					Render(void) noexcept override;
	public:		void					Release(void) noexcept override;

	public:		void					AddForce(D3DXVECTOR3 force) noexcept;
	public:		void					AddForce(float x, float y, float z) noexcept;

	public:		void					SetFreezePosition(bool freezeX, bool freezeY, bool freezeZ) noexcept;
	public:		void					SetFreezeRotation(bool freezeX, bool freezeY, bool freezeZ) noexcept;

	public:		void					OnCollideWith(Collider* mine, Collider* other) noexcept;
	public:		void					OnNotCollideWith(Collider* mine, Collider* other) noexcept;

	public:		const Collider::TList&	GetColliders(void) const noexcept { return _colliders; }
	public:		const CollisionList&	GetCollisionList(void) const noexcept { return _collisionList; }

	private:	bool					_bFreezePositionX = false;
	private:	bool					_bFreezePositionY = false;
	private:	bool					_bFreezePositionZ = false;

	private:	bool					_bFreezeRotationX = false;
	private:	bool					_bFreezeRotationY = false;
	private:	bool					_bFreezeRotationZ = false;

	private:	float					_gravity;

	private:	D3DXVECTOR3				_force;
	private:	Transform*				_transform;

	private:	Collider::TList			_colliders;
	private:	CollisionList			_collisionList;
	};
}

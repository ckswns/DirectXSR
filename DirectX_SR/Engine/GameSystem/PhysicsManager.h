#pragma once
#include "SingletonBase.h"
#include "Collider.h"
#include "RigidBody.h"

namespace ce
{
	class PhysicsManager : public SingletonBase<PhysicsManager>
	{
	private:	explicit			PhysicsManager(void) noexcept { __noop; }
	public:		virtual				~PhysicsManager(void) noexcept { __noop; }

	public:		void				Update(void) noexcept;
	public:		void				Release(void) noexcept;

	public:		void				InsertRigidbodyXXX(Rigidbody* rigidbody) noexcept;
	public:		void				RemoveRigidbodyXXX(Rigidbody* rigidbody) noexcept;

	public:		void				InsertColliderXXX(Collider* collider) noexcept;
	public:		void				RemoveColliderXXX(Collider* collider) noexcept;

	private:	Collider::TList		_colliders;
	private:	Rigidbody::TList	_rigidbodys;

	private:	friend				SingletonBase<PhysicsManager>;
	};
}

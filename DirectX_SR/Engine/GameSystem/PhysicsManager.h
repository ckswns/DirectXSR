#pragma once
#include "SingletonBase.h"
#include "Collider.h"

namespace ce
{
	class PhysicsManager : public SingletonBase<PhysicsManager>
	{
	private:	explicit			PhysicsManager(void) noexcept;
	public:		virtual				~PhysicsManager(void) noexcept { __noop; }

	public:		void				Update(void) noexcept;
	public:		void				Release(void) noexcept;

	public:		void				InsertColliderXXX(Collider* collider) noexcept;
	public:		void				RemoveColliderXXX(Collider* collider) noexcept;

	private:	Collider::TList		_colliders;

	private:	friend				SingletonBase<PhysicsManager>;
	};
}

#pragma once
#include "Collider.h"

namespace ce
{
	class Transform;

	class SphereCollider : Collider
	{
	public:		explicit		SphereCollider(void) noexcept;
	public:		virtual			~SphereCollider(void) noexcept { __noop; }
	
	public:		void			Update(float) noexcept override;
	public:		void			Render(void) noexcept override;

	public:		bool			CheckCollision(Collider* rhs) noexcept override;
	public:		bool			CheckHitRaycast(const Ray& ray, RaycastHit& hit) noexcept override;

	private:	float			_radius;
	};
}

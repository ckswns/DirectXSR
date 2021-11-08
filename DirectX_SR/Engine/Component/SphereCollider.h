#pragma once
#include "Collider.h"

namespace ce
{
	class SphereCollider : Collider
	{
	public:		explicit		SphereCollider(void) noexcept;
	public:		virtual			~SphereCollider(void) noexcept { __noop; }
	
	public:		void			Init(void) noexcept override;
	public:		void			Update(float) noexcept override;
	public:		void			Render(void) noexcept override;
	public:		void			Release(void) noexcept override;
	public:		bool			CheckCollision(Collider* rhs) noexcept override;
	public:		bool			CheckHitRaycast(const Ray& ray, RaycastHit& hit) noexcept override;

	private:	float			_radius;
	};
}

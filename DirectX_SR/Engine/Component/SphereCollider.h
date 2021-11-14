#pragma once
#include "Collider.h"

namespace ce
{
	class Transform;

	class SphereCollider : public Collider
	{
	public:		explicit		SphereCollider(void) noexcept = delete;
	public:		explicit		SphereCollider(float radius, std::string tag = "") noexcept;
	public:		virtual			~SphereCollider(void) noexcept { __noop; }
	
	public:		void			Open(void) noexcept override final;
	public:		void			Close(void) noexcept override final;

	public:		void			Render(void) noexcept override;

	public:		bool			CheckCollision(Collider* rhs) const noexcept override;
	public:		bool			CheckHitRaycast(const Ray& ray, RaycastHit& hit) const noexcept override;

	public:		float			GetRadius(void) const noexcept { return _radius; }

	private:	float			_radius;
#ifdef _DEBUG
	private:	LPD3DXMESH		_dbgMesh;
#endif
	};
}

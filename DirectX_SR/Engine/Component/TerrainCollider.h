#pragma once
#include "Collider.h"

namespace ce
{
	class Terrain;

	class TerrainCollider : public Collider
	{
	public:		explicit		TerrainCollider(Terrain* terrain) noexcept;
	public:		virtual			~TerrainCollider(void) noexcept { __noop; }

	public:		void			Render(void) noexcept override;

	public:		void			Open(void) noexcept override;
	public:		void			Close(void) noexcept override;
	public:		bool			CheckCollision(Collider* rhs) const noexcept override;
	public:		bool			CheckHitRaycast(const Ray& ray, RaycastHit& hit) const noexcept override;

	private:	Terrain*		_terrain;
	};
}

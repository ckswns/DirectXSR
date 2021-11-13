#pragma once
#include "Collider.h"

namespace ce
{
	class Terrain;

	class TerrainCollider : public Collider
	{
	public:		explicit		TerrainCollider(Terrain* terrain) noexcept;
	public:		virtual			~TerrainCollider(void) noexcept { __noop; }

	public:		void			Update(float) noexcept override;
	public:		void			Render(void) noexcept override;

	public:		bool			CheckCollision(Collider* rhs) noexcept override;
	public:		bool			CheckHitRaycast(const Ray& ray, RaycastHit& hit) noexcept override;

	private:	Terrain*		_terrain;
	};
}

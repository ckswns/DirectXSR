#include "pch.h"
#include "TerrainCollider.h"
#include "Terrain.h"

namespace ce
{
	TerrainCollider::TerrainCollider(Terrain* terrain) noexcept :
		Collider(Collider::Type::TERRAIN, ""),
		_terrain(terrain)
	{

	}

	bool TerrainCollider::CheckCollision(Collider* rhs) const noexcept
	{
		return false;
	}

	bool TerrainCollider::CheckHitRaycast(const Ray& ray, RaycastHit& hit) const noexcept
	{
		return false;
	}

	void TerrainCollider::Render(void) noexcept
	{

	}

	void TerrainCollider::Open(void) noexcept
	{

	}

	void TerrainCollider::Close(void) noexcept
	{

	}

}
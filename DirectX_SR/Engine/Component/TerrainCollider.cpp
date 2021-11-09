#include "TerrainCollider.h"
#include "Terrain.h"

namespace ce
{
	TerrainCollider::TerrainCollider(Terrain* terrain) noexcept :
		Collider(Collider::Type::TERRAIN),
		_terrain(terrain)
	{

	}

	bool TerrainCollider::CheckCollision(Collider* rhs) noexcept
	{
		return true;
	}

	bool TerrainCollider::CheckHitRaycast(const Ray& ray, RaycastHit& hit) noexcept
	{

		return true;
	}

	void TerrainCollider::Init(void) noexcept
	{

	}

	void TerrainCollider::Update(float) noexcept
	{

	}

	void TerrainCollider::Render(void) noexcept
	{

	}

	void TerrainCollider::Release(void) noexcept
	{

	}
}
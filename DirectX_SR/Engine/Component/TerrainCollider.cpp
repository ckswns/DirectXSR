#include "pch.h"
#include "TerrainCollider.h"
#include "Terrain.h"
#include "Ray.h"
#include "Transform.h"

namespace ce
{
	TerrainCollider::TerrainCollider(Terrain* terrain, std::string tag) noexcept :
		Collider(Collider::Type::TERRAIN, tag),
		_terrain(terrain)
	{

	}

	bool TerrainCollider::CheckCollision(Collider* rhs) const noexcept
	{
		return false;
	}

	bool TerrainCollider::CheckHitRaycast(const Ray& ray, RaycastHit& hit) const noexcept
	{
		unsigned long dwCntX = _terrain->Get_VtxCntX();
		unsigned long dwCntZ = _terrain->Get_VtxCntZ();
		const	 D3DXVECTOR3* pTerrainVtxPos = _terrain->Get_VtxPos();

		unsigned long 	dwVtxIdx[3];
		float	fU, fV, fDist;

		for (unsigned long i = 0; i < dwCntZ - 1; ++i)
		{
			for (unsigned long j = 0; j < dwCntX - 1; ++j)
			{
				unsigned long	dwIndex = i * dwCntX + j;

				// 오른쪽 위
				dwVtxIdx[0] = dwIndex + dwCntX;
				dwVtxIdx[1] = dwIndex + dwCntX + 1;
				dwVtxIdx[2] = dwIndex + 1;

				if (D3DXIntersectTri(&pTerrainVtxPos[dwVtxIdx[1]],
					&pTerrainVtxPos[dwVtxIdx[0]],
					&pTerrainVtxPos[dwVtxIdx[2]],
					&ray._origin, &ray._dir,
					&fU, &fV, &fDist))
				{
					hit.collider = const_cast<TerrainCollider*>(this);
					hit.distance = fDist;
					hit.transform = _transform;
					hit.point = D3DXVECTOR3(pTerrainVtxPos[dwVtxIdx[1]].x + (pTerrainVtxPos[dwVtxIdx[0]].x - pTerrainVtxPos[dwVtxIdx[1]].x) * fU,
						0.f,
						pTerrainVtxPos[dwVtxIdx[1]].z + (pTerrainVtxPos[dwVtxIdx[2]].z - pTerrainVtxPos[dwVtxIdx[1]].z) * fV);
					return true;
				}

				// 왼쪽 아래
				dwVtxIdx[0] = dwIndex + dwCntX;
				dwVtxIdx[1] = dwIndex + 1;
				dwVtxIdx[2] = dwIndex;

				if (D3DXIntersectTri(&pTerrainVtxPos[dwVtxIdx[2]],
					&pTerrainVtxPos[dwVtxIdx[1]],
					&pTerrainVtxPos[dwVtxIdx[0]],
					&ray._origin, &ray._dir,
					&fU, &fV, &fDist))
				{
					hit.collider = const_cast<TerrainCollider*>(this);
					hit.distance = fDist;
					hit.transform = _transform;
					hit.point = D3DXVECTOR3(pTerrainVtxPos[dwVtxIdx[2]].x + (pTerrainVtxPos[dwVtxIdx[1]].x - pTerrainVtxPos[dwVtxIdx[2]].x) * fU,
						0.f,
						pTerrainVtxPos[dwVtxIdx[2]].z + (pTerrainVtxPos[dwVtxIdx[0]].z - pTerrainVtxPos[dwVtxIdx[2]].z) * fV);
					return true;
				}
			}
		}

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
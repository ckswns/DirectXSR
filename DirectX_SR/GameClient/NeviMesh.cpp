#include "pch.h"
#include "NeviMesh.h"
#include "Node.h"

NeviMesh::~NeviMesh() noexcept
{
	Release();
}

void NeviMesh::Init() noexcept
{
	int count = (_iSizeX-1) * (_iSizeY-1);
	Grid.resize(count);

	for (int z = 0; z < (_iSizeY-1); z++)
	{
		for (int x = 0; x < (_iSizeX-1); x++)
		{
			int idx = (z * (_iSizeX-1)) + x;
			int terrainIdx = (z * (_iSizeX)) + x;

			D3DXVECTOR3 worldPoint = _TerrainVtx[terrainIdx];
			worldPoint.x += 0.5f;
			worldPoint.z += 0.5f;
			bool walkable = true;
			Grid[idx] = new Node(walkable, worldPoint, x, z);
		}
	}

	SetNeighbours();
}

void NeviMesh::SetNeighbours() noexcept
{
	for (int z = 0; z < (_iSizeY-1); z++)
	{
		for (int x = 0; x < (_iSizeX-1); x++)
		{
			int idx = (z * (_iSizeX-1)) + x;


			//오른쪽
			if ((x + 1) < _iSizeX-1)
			{
				Grid[idx]->AddNeighbor(Grid[(idx+1)]);
				Grid[(idx+1)]->AddNeighbor(Grid[idx]);

				//오른대각 아래
				if ((z - 1) >= 0)
				{
					Grid[idx]->AddNeighbor(Grid[(idx - (_iSizeX -2))]);
					Grid[(idx - (_iSizeX -2))]->AddNeighbor(Grid[idx]);
				}

			}

			//아래 
			int bottomZ = z - 1;
			if (bottomZ >= 0)
			{
				Grid[idx]->AddNeighbor(Grid[(idx - (_iSizeX-1))]);
				Grid[(idx - (_iSizeX-1))]->AddNeighbor(Grid[idx]);

				//왼 대각 아래 
				if (x > 0)
				{
					Grid[idx]->AddNeighbor(Grid[(idx - (_iSizeX ))]);
					Grid[(idx - (_iSizeX ))]->AddNeighbor(Grid[idx]);
				}
			}
		}
	}
}

void NeviMesh::Release() noexcept
{
	for (size_t i = 0; i < Grid.size(); ++i)
	{
		if (Grid[i] != nullptr)
		{
			delete Grid[i];
			Grid[i] = nullptr;
		}
	}
	Grid.clear();
}

Node* NeviMesh::NodeFormPosition(D3DXVECTOR3 Pos) noexcept
{
	int x = floor(Pos.x);
	int z = floor(Pos.z);
	int idx = (z * (_iSizeX-1)) + x;

	if (x >= _iSizeX || z >= _iSizeY)
		return nullptr;

	return Grid[idx];
}

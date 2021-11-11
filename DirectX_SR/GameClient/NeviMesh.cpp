#include "pch.h"
#include "NeviMesh.h"
#include "Node.h"

void NeviMesh::Init() noexcept
{
	int count = (_iSizeX) * (_iSizeY );
	Grid.resize(count);

	for (int z = 0; z < (_iSizeY); z++)
	{
		for (int x = 0; x < (_iSizeX); x++)
		{
			int idx = (z * _iSizeX) + x;

			D3DXVECTOR3 worldPoint = _TerrainVtx[idx];
			worldPoint.x += 0.5f;
			worldPoint.z += 0.5f;

			bool walkable = true;
			Grid[idx] = new Node(walkable, worldPoint, x, z);

			if (x > 0)
			{
				Grid[idx]->AddNeighbor(Grid[(idx - 1)]);

				if (idx < (_iSizeX-1))
					Grid[(idx - 1)]->AddNeighbor(Grid[idx]);
			}
			if (z > 0)
			{
				Grid[idx]->AddNeighbor(Grid[(idx - (_iSizeX))]);
				if (z < (_iSizeY - 1))
					Grid[(idx - (_iSizeX))]->AddNeighbor(Grid[idx]);

			//		if (x != 0)
			//		{
			//			//왼 대각선 아래 
			//			Grid[idx]->AddNeighbor(Grid[(idx - (_iSizeX + 1))]);
			//			Grid[(idx - (_iSizeX + 1))]->AddNeighbor(Grid[idx]);

			//			//오른 대각 아래
			//			if (idx < (_iSizeX - 2)) 
			//			{
			//				Grid[idx]->AddNeighbor(Grid[(idx - (_iSizeX - 1))]);
			//				Grid[(idx - (_iSizeX - 1))]->AddNeighbor(Grid[idx]);
			//			}
			//		}
			}
		}
	}

//	SetNeighbours();
}

void NeviMesh::SetNeighbours() noexcept
{
	int CountZ = (_iSizeY - 1);
	int CountX = (_iSizeX - 1);

	for (int z = 0; z < CountZ; z++)
	{
		for (int x = 0; x < CountX; x++)
		{
			int idx = (z * CountX) + x;

			//오른쪽
			int rightX = x + 1;
			if (rightX < CountX)
			{
				Grid[idx]->AddNeighbor(Grid[(idx+1)]);
				Grid[(idx+1)]->AddNeighbor(Grid[idx]);

				//오른대각 아래
				if ((z - 1) >= 0)
				{
					Grid[idx]->AddNeighbor(Grid[(idx - (CountZ-1))]);
					Grid[(idx - (CountZ-1))]->AddNeighbor(Grid[idx]);
				}

			}

			//아래 
			int bottomZ = z - 1;
			if (bottomZ >= 0)
			{
				Grid[idx]->AddNeighbor(Grid[(idx - CountZ)]);
				Grid[(idx - CountZ)]->AddNeighbor(Grid[idx]);
			}
		}
	}
}

Node* NeviMesh::NodeFormPosition(D3DXVECTOR3 Pos) noexcept
{
	int x = floor(Pos.x);
	int z = floor(Pos.z);
	int idx = (z * _iSizeX) + x;

	if (x >= _iSizeX || z >= _iSizeY)
		return nullptr;

	return Grid[idx];
}

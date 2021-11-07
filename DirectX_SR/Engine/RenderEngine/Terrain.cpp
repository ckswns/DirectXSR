#include "pch.h"
#include "Terrain.h"

namespace ce
{
	Terrain::Terrain(uint16 width, uint16 height, float scaleFactor) noexcept :
		Mesh(scaleFactor),
		_width(width),
		_height(height)
	{

	}

	bool Terrain::Open(LPDIRECT3DDEVICE9 pDevice) noexcept
	{
		_nFVF = FVF_TEX;
		_nTriCnt = (_width - 1) * (_height - 1) * 2;
		_nVtxCnt = _width * _height;
		_nVtxSize = sizeof(VTXTEX);

		_idxFmt = D3DFMT_INDEX32;
		_nIdxSize = sizeof(INDEX32);

		float interval = _scaleFactor;

		if (Mesh::Open(pDevice) == false)
		{
			CE_ASSERT("ckswns", "Mesh::Open에 실패하였습니다");
		}

		VTXTEX* pVertex = nullptr;

		D3DXVECTOR3 e0, e1;
		D3DXVECTOR3 normal;

		uint64		index = 0;
		uint64		triCnt = 0;

		_pVB->Lock(0, 0, (void**)&pVertex, 0);

		for (uint64 i = 0; i < _height; ++i)
		{
			for (uint64 j = 0; j < _width; ++j)
			{
				index = i * _width + j;

				pVertex[index].vPosition = D3DXVECTOR3(float(j * interval),
														0,
														float(i * interval));
				pVertex[index].vTexUV = D3DXVECTOR2(float(j) / (_width - 1),
													float(i) / (_height - 1));
			}
		}

		INDEX32* pIndex = nullptr;

		_pIB->Lock(0, 0, (void**)&pIndex, 0);

		for (uint64 i = 0; i < _height - 1; ++i)
		{
			for (uint64 j = 0; j < _width - 1; ++j)
			{
				index = i * _width + j;

				pIndex[triCnt]._0 = index + _width;
				pIndex[triCnt]._1 = index + _width + 1;
				pIndex[triCnt]._2 = index + 1;
				triCnt++;

				pIndex[triCnt]._0 = index + _width;
				pIndex[triCnt]._1 = index + 1;
				pIndex[triCnt]._2 = index;
				triCnt++;
			}
		}

		//for (uint64 i = 0; i < triCnt; i++)
		//{
		//	e0 = pVertex[pIndex[i]._1].vPosition - pVertex[pIndex[i]._0].vPosition;
		//	e1 = pVertex[pIndex[i]._2].vPosition - pVertex[pIndex[i]._0].vPosition;

		//	D3DXVec3Cross(&normal, &e0, &e1);

		//	pVertex[pIndex[i]._0].vNormal += normal;
		//	pVertex[pIndex[i]._1].vNormal += normal;
		//	pVertex[pIndex[i]._2].vNormal += normal;
		//}

		//for (uint64 i = 0; i < _nVtxCnt; i++)
		//{
		//	D3DXVec3Normalize(&pVertex[i].vNormal, &pVertex[i].vNormal);
		//}

		_pVB->Unlock();
		_pIB->Unlock();

		return true;
	}
}
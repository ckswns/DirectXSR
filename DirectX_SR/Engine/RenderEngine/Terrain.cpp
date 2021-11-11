#include "pch.h"
#include "Terrain.h"
#include "Assertion.h"

namespace ce
{
	Terrain::Terrain(uint64 width, uint64 height, float scaleFactor) noexcept :
		Mesh(scaleFactor),
		_width(width),
		_height(height)
	{

	}

	bool Terrain::Open(LPDIRECT3DDEVICE9 pDevice) noexcept
	{
		_nFVF = FVF_TEX_NORM;
		_nTriCnt = (_width - 1) * (_height - 1) * 2;
		_nVtxCnt = _width * _height;
		_nVtxSize = sizeof(VTXTEXNORM);

		_idxFmt = D3DFMT_INDEX32;
		_nIdxSize = sizeof(INDEX32);

		float interval = _scaleFactor;

		if (Mesh::Open(pDevice) == false)
		{
			CE_ASSERT("ckswns", "Mesh::Open에 실패하였습니다");
		}

		VTXTEXNORM* pVertex = nullptr;

		D3DXVECTOR3 e0, e1;
		D3DXVECTOR3 normal;

		DWORD index = 0;

		_pVtxPos = new D3DXVECTOR3[_nVtxCnt];

		if (FAILED(_pVB->Lock(0, 0, (void**)&pVertex, 0)))
			CE_ASSERT("ckswns", "VtxBuffer::Lock 함수 호출에 실패하였습니다");

		for (DWORD z = 0; z < _height; ++z)
		{
			for (DWORD x = 0; x < _width; ++x)
			{
				index = z * _width + x;

				pVertex[index].vPosition = D3DXVECTOR3((x * interval), 0.f, (z * interval));
				pVertex[index].vTexUV = D3DXVECTOR2(float(z) / (_height - 1), float(x) / (_width - 1));

				_pVtxPos[index] = pVertex[index].vPosition;
			}
		}

		uint64 triCnt = 0;
		INDEX32* pIndex = nullptr;

		if (FAILED(_pIB->Lock(0, 0, (void**)&pIndex, 0)))
			CE_ASSERT("ckswns", "IdxBuffer::Lock 함수 호출에 실패하였습니다");

		for (DWORD z = 0; z < _height - 1; ++z)
		{
			for (DWORD x = 0; x < _width - 1; ++x)
			{
				index = z * _width + x;

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

		for (DWORD i = 0; i < triCnt; i++)
		{
			e0 = pVertex[pIndex[i]._1].vPosition - pVertex[pIndex[i]._0].vPosition;
			e1 = pVertex[pIndex[i]._2].vPosition - pVertex[pIndex[i]._0].vPosition;

			D3DXVec3Cross(&normal, &e0, &e1);

			pVertex[pIndex[i]._0].vNormal += normal;
			pVertex[pIndex[i]._1].vNormal += normal;
			pVertex[pIndex[i]._2].vNormal += normal;
		}

		for (DWORD i = 0; i < _nVtxCnt; i++)
		{
			D3DXVec3Normalize(&pVertex[i].vNormal, &pVertex[i].vNormal);
		}

		_pVB->Unlock();
		_pIB->Unlock();

		return true;
	}
}
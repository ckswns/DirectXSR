#include "pch.h"
#include "Cube.h"
#include "TypeDefine.h"
#include "Assertion.h"

namespace ce
{
	Cube::Cube(float scaleFactor) noexcept :
		Mesh(scaleFactor)
	{

	}

	bool Cube::Open(LPDIRECT3DDEVICE9 pDevice) noexcept
	{
		_nFVF = FVF_CUBE_NORM;
		_nTriCnt = 12;
		_nVtxCnt = 8;
		_nVtxSize = sizeof(VTXCUBENORM);

		_idxFmt = D3DFMT_INDEX16;
		_nIdxSize = sizeof(INDEX16);

		float interval = _scaleFactor * 0.5f;

		if (Mesh::Open(pDevice) == false)
		{
			CE_ASSERT("ckswns", "Mesh::Open에 실패하였습니다");
		}

		VTXCUBENORM* pVertex = nullptr;

		D3DXVECTOR3 e0, e1;
		D3DXVECTOR3 normal;

		_pVB->Lock(0, 0, (void**)&pVertex, 0);
		// 오른쪽 위
		pVertex[0].vPosition = D3DXVECTOR3(-interval, interval, -interval);
		pVertex[0].vTexUV = pVertex[0].vPosition;

		pVertex[1].vPosition = D3DXVECTOR3(interval, interval, -interval);
		pVertex[1].vTexUV = pVertex[1].vPosition;

		pVertex[2].vPosition = D3DXVECTOR3(interval, -interval, -interval);
		pVertex[2].vTexUV = pVertex[2].vPosition;

		pVertex[3].vPosition = D3DXVECTOR3(-interval, -interval, -interval);
		pVertex[3].vTexUV = pVertex[3].vPosition;

		pVertex[4].vPosition = D3DXVECTOR3(-interval, interval, interval);
		pVertex[4].vTexUV = pVertex[4].vPosition;

		pVertex[5].vPosition = D3DXVECTOR3(interval, interval, interval);
		pVertex[5].vTexUV = pVertex[5].vPosition;

		pVertex[6].vPosition = D3DXVECTOR3(interval, -interval, interval);
		pVertex[6].vTexUV = pVertex[6].vPosition;

		pVertex[7].vPosition = D3DXVECTOR3(-interval, -interval, interval);
		pVertex[7].vTexUV = pVertex[7].vPosition;

		INDEX16* pIndex = nullptr;

		_pIB->Lock(0, 0, (void**)&pIndex, 0);

		// X+
		pIndex[0]._0 = 1;
		pIndex[0]._1 = 5;
		pIndex[0]._2 = 6;

		e0 = pVertex[pIndex[0]._1].vPosition - pVertex[pIndex[0]._0].vPosition;
		e1 = pVertex[pIndex[0]._2].vPosition - pVertex[pIndex[0]._0].vPosition;

		D3DXVec3Cross(&normal, &e0, &e1);

		pVertex[pIndex[0]._0].vNormal += normal;
		pVertex[pIndex[0]._1].vNormal += normal;
		pVertex[pIndex[0]._2].vNormal += normal;

		pIndex[1]._0 = 1;
		pIndex[1]._1 = 6;
		pIndex[1]._2 = 2;

		e0 = pVertex[pIndex[1]._1].vPosition - pVertex[pIndex[1]._0].vPosition;
		e1 = pVertex[pIndex[1]._2].vPosition - pVertex[pIndex[1]._0].vPosition;

		D3DXVec3Cross(&normal, &e0, &e1);

		pVertex[pIndex[1]._0].vNormal += normal;
		pVertex[pIndex[1]._1].vNormal += normal;
		pVertex[pIndex[1]._2].vNormal += normal;

		// X-
		pIndex[2]._0 = 4;
		pIndex[2]._1 = 0;
		pIndex[2]._2 = 3;

		e0 = pVertex[pIndex[2]._1].vPosition - pVertex[pIndex[2]._0].vPosition;
		e1 = pVertex[pIndex[2]._2].vPosition - pVertex[pIndex[2]._0].vPosition;

		D3DXVec3Cross(&normal, &e0, &e1);

		pVertex[pIndex[2]._0].vNormal += normal;
		pVertex[pIndex[2]._1].vNormal += normal;
		pVertex[pIndex[2]._2].vNormal += normal;

		pIndex[3]._0 = 4;
		pIndex[3]._1 = 3;
		pIndex[3]._2 = 7;

		e0 = pVertex[pIndex[3]._1].vPosition - pVertex[pIndex[3]._0].vPosition;
		e1 = pVertex[pIndex[3]._2].vPosition - pVertex[pIndex[3]._0].vPosition;

		D3DXVec3Cross(&normal, &e0, &e1);

		pVertex[pIndex[3]._0].vNormal += normal;
		pVertex[pIndex[3]._1].vNormal += normal;
		pVertex[pIndex[3]._2].vNormal += normal;

		// Y+
		pIndex[4]._0 = 4;
		pIndex[4]._1 = 5;
		pIndex[4]._2 = 1;

		e0 = pVertex[pIndex[4]._1].vPosition - pVertex[pIndex[4]._0].vPosition;
		e1 = pVertex[pIndex[4]._2].vPosition - pVertex[pIndex[4]._0].vPosition;

		D3DXVec3Cross(&normal, &e0, &e1);

		pVertex[pIndex[4]._0].vNormal += normal;
		pVertex[pIndex[4]._1].vNormal += normal;
		pVertex[pIndex[4]._2].vNormal += normal;

		pIndex[5]._0 = 4;
		pIndex[5]._1 = 1;
		pIndex[5]._2 = 0;

		e0 = pVertex[pIndex[5]._1].vPosition - pVertex[pIndex[5]._0].vPosition;
		e1 = pVertex[pIndex[5]._2].vPosition - pVertex[pIndex[5]._0].vPosition;

		D3DXVec3Cross(&normal, &e0, &e1);

		pVertex[pIndex[5]._0].vNormal += normal;
		pVertex[pIndex[5]._1].vNormal += normal;
		pVertex[pIndex[5]._2].vNormal += normal;

		// Y-
		pIndex[6]._0 = 3;
		pIndex[6]._1 = 2;
		pIndex[6]._2 = 6;

		e0 = pVertex[pIndex[6]._1].vPosition - pVertex[pIndex[6]._0].vPosition;
		e1 = pVertex[pIndex[6]._2].vPosition - pVertex[pIndex[6]._0].vPosition;

		D3DXVec3Cross(&normal, &e0, &e1);

		pVertex[pIndex[6]._0].vNormal += normal;
		pVertex[pIndex[6]._1].vNormal += normal;
		pVertex[pIndex[6]._2].vNormal += normal;

		pIndex[7]._0 = 3;
		pIndex[7]._1 = 6;
		pIndex[7]._2 = 7;

		e0 = pVertex[pIndex[7]._1].vPosition - pVertex[pIndex[7]._0].vPosition;
		e1 = pVertex[pIndex[7]._2].vPosition - pVertex[pIndex[7]._0].vPosition;

		D3DXVec3Cross(&normal, &e0, &e1);

		pVertex[pIndex[7]._0].vNormal += normal;
		pVertex[pIndex[7]._1].vNormal += normal;
		pVertex[pIndex[7]._2].vNormal += normal;

		// Z+
		pIndex[8]._0 = 7;
		pIndex[8]._1 = 6;
		pIndex[8]._2 = 5;

		e0 = pVertex[pIndex[8]._1].vPosition - pVertex[pIndex[8]._0].vPosition;
		e1 = pVertex[pIndex[8]._2].vPosition - pVertex[pIndex[8]._0].vPosition;

		D3DXVec3Cross(&normal, &e0, &e1);

		pVertex[pIndex[8]._0].vNormal += normal;
		pVertex[pIndex[8]._1].vNormal += normal;
		pVertex[pIndex[8]._2].vNormal += normal;

		pIndex[9]._0 = 7;
		pIndex[9]._1 = 5;
		pIndex[9]._2 = 4;

		e0 = pVertex[pIndex[9]._1].vPosition - pVertex[pIndex[9]._0].vPosition;
		e1 = pVertex[pIndex[9]._2].vPosition - pVertex[pIndex[9]._0].vPosition;

		D3DXVec3Cross(&normal, &e0, &e1);

		pVertex[pIndex[9]._0].vNormal += normal;
		pVertex[pIndex[9]._1].vNormal += normal;
		pVertex[pIndex[9]._2].vNormal += normal;

		// Z-
		pIndex[10]._0 = 0;
		pIndex[10]._1 = 1;
		pIndex[10]._2 = 2;

		e0 = pVertex[pIndex[10]._1].vPosition - pVertex[pIndex[10]._0].vPosition;
		e1 = pVertex[pIndex[10]._2].vPosition - pVertex[pIndex[10]._0].vPosition;

		D3DXVec3Cross(&normal, &e0, &e1);

		pVertex[pIndex[10]._0].vNormal += normal;
		pVertex[pIndex[10]._1].vNormal += normal;
		pVertex[pIndex[10]._2].vNormal += normal;

		pIndex[11]._0 = 0;
		pIndex[11]._1 = 2;
		pIndex[11]._2 = 3;

		e0 = pVertex[pIndex[11]._1].vPosition - pVertex[pIndex[11]._0].vPosition;
		e1 = pVertex[pIndex[11]._2].vPosition - pVertex[pIndex[11]._0].vPosition;

		D3DXVec3Cross(&normal, &e0, &e1);

		pVertex[pIndex[11]._0].vNormal += normal;
		pVertex[pIndex[11]._1].vNormal += normal;
		pVertex[pIndex[11]._2].vNormal += normal;

		_pVB->Unlock();
		_pIB->Unlock();

		return true;
	}
}
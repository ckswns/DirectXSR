#include "pch.h"
#include "Quad.h"
#include "Assertion.h"

namespace ce
{
	Quad::Quad(float x, float y) noexcept :
		Mesh(1),
		_intvX(x),
		_intvY(y)
	{

	}

	bool Quad::Open(LPDIRECT3DDEVICE9 pDevice) noexcept
	{
		_nFVF = FVF_TEX_NORM;
		_nTriCnt = 2;
		_nVtxCnt = 4;
		_nVtxSize = sizeof(VTXTEXNORM);

		_idxFmt = D3DFMT_INDEX16;
		_nIdxSize = sizeof(INDEX16);

		if (Mesh::Open(pDevice) == false)
		{
			CE_ASSERT("ckswns", "Mesh::Open에 실패하였습니다");
		}

		VTXTEXNORM* pVertex = nullptr;

		D3DXVECTOR3 e0, e1;
		D3DXVECTOR3 normal;

		if (FAILED(_pVB->Lock(0, 0, (void**)&pVertex, 0)))
			CE_ASSERT("ckswns", "VtxBuffer::Lock 함수 호출에 실패하였습니다");

		pVertex[0].vPosition = D3DXVECTOR3(-0.5f * _intvX, 0.5f * _intvY, 0.f);
		pVertex[0].vTexUV = D3DXVECTOR2(0.f, 0.f);

		pVertex[1].vPosition = D3DXVECTOR3(0.5f * _intvX, 0.5f * _intvY, 0.f);
		pVertex[1].vTexUV = D3DXVECTOR2(1.f, 0.f);

		pVertex[2].vPosition = D3DXVECTOR3(0.5f * _intvX, -0.5f * _intvY, 0.f);
		pVertex[2].vTexUV = D3DXVECTOR2(1.f, 1.f);

		pVertex[3].vPosition = D3DXVECTOR3(-0.5f * _intvX, -0.5f * _intvY, 0.f);
		pVertex[3].vTexUV = D3DXVECTOR2(0.f, 1.f);


		INDEX16* pIndex = nullptr;

		if (FAILED(_pIB->Lock(0, 0, (void**)&pIndex, 0)))
			CE_ASSERT("ckswns", "IdxBuffer::Lock 함수 호출에 실패하였습니다");

		pIndex[0]._0 = 0;
		pIndex[0]._1 = 1;
		pIndex[0]._2 = 2;

		pIndex[1]._0 = 0;
		pIndex[1]._1 = 2;
		pIndex[1]._2 = 3;

		for (int i = 0; i < 2; i++)
		{
			e0 = pVertex[pIndex[i]._1].vPosition - pVertex[pIndex[i]._0].vPosition;
			e1 = pVertex[pIndex[i]._2].vPosition - pVertex[pIndex[i]._0].vPosition;

			D3DXVec3Cross(&normal, &e0, &e1);

			pVertex[pIndex[i]._0].vNormal += normal;
			pVertex[pIndex[i]._1].vNormal += normal;
			pVertex[pIndex[i]._2].vNormal += normal;
		}

		for (int i = 0; i < _nVtxCnt; i++)
		{
			D3DXVec3Normalize(&pVertex[i].vNormal, &pVertex[i].vNormal);
		}

		_pVB->Unlock();
		_pIB->Unlock();

		return true;
	}
}
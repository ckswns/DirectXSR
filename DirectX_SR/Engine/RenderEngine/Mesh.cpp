#include "pch.h"
#include "Mesh.h"
#include "Assertion.h"

namespace ce
{
	Mesh::Mesh(float scaleFactor) noexcept :
		_pVB(nullptr),
		_pIB(nullptr),
		_nVtxCnt(0),
		_nVtxSize(0),
		_nTriCnt(0),
		_nFVF(0),
		_scaleFactor(scaleFactor)
	{

	}

	bool Mesh::Open(LPDIRECT3DDEVICE9 pDevice) noexcept
	{
		if (FAILED(pDevice->CreateVertexBuffer(_nVtxSize * _nVtxCnt,
			0,
			_nFVF,
			D3DPOOL_MANAGED,
			&_pVB,
			NULL)))
		{
			return false;
		}

		if (FAILED(pDevice->CreateIndexBuffer(_nIdxSize * _nTriCnt,
			0,
			_idxFmt,
			D3DPOOL_MANAGED,
			&_pIB,
			NULL)))
		{
			return false;
		}

		_bOpen = true;

		return true;
	}

	void Mesh::Close(void) noexcept
	{
		if (_pVB)
			_pVB->Release();
		if (_pIB)
			_pIB->Release();
	}

	void Mesh::Render(LPDIRECT3DDEVICE9 pDevice) noexcept
	{
		if(_bOpen == false)
		{
			CE_ASSERT("ckswns", "Open()이 선행 호출되어야 합니다");
		}

		pDevice->SetStreamSource(0, _pVB, 0, _nVtxSize);
		pDevice->SetFVF(_nFVF);
		pDevice->SetIndices(_pIB);
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _nVtxCnt, 0, _nTriCnt);
	}
}

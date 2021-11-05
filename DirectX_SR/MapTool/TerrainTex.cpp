#include "pch.h"
#include "TerrainTex.h"
#include "Texture.h"

CTerrain::CTerrain(LPDIRECT3DDEVICE9& pGraphicDevconst, const DWORD& dwCntX, const DWORD& dwCntZ, const float& dwIntvX, const float& dwIntvZ, const DWORD& dwRoomNumber)
	: m_pGraphicDev(pGraphicDevconst), m_RoomNumber(dwRoomNumber)
	, m_dwVtxCntX(dwCntX), m_dwVtxCntZ(dwCntZ), m_dwVtxIntvX(dwIntvX), m_dwVtxIntvZ(dwIntvZ)
	, m_dwVtxCnt(0),m_dwVtxSize(0),m_dwTriCnt(0), m_dwFVF(0)
	, m_dwIdxSize(0), m_IdxFmt(D3DFMT_UNKNOWN)
	, m_pIB(nullptr), m_pVB(nullptr)
{
	//_eLayer = GameObjectLayer::BACKGROUND;
}

CTerrain::~CTerrain(void)
{
}

void CTerrain::Start(void) noexcept
{
	m_dwFVF = VTXTEX_FVF;
	m_dwTriCnt = (m_dwVtxCntX - 1) * (m_dwVtxCntZ - 1) * 2;
	m_dwVtxCnt = m_dwVtxCntX * m_dwVtxCntZ;
	m_dwVtxSize = sizeof(VTTEX);

	m_IdxFmt = D3DFMT_INDEX32;
	m_dwIdxSize = sizeof(IDX32);

	if (FAILED(m_pGraphicDev->CreateVertexBuffer(m_dwVtxSize * m_dwVtxCnt, 0, m_dwFVF, D3DPOOL_MANAGED, &m_pVB, NULL)))
		return;

	if (FAILED(m_pGraphicDev->CreateIndexBuffer(m_dwIdxSize * m_dwTriCnt, 0, m_IdxFmt, D3DPOOL_MANAGED, &m_pIB, NULL)))
		return;

	VTTEX* pVertex = nullptr;
	DWORD	dwIndex = 0;

	Texture* pTexture = new Texture();

	pTexture->Init(m_pGraphicDev, "Resource/Player0.jpg");
	m_pTexture = (LPDIRECT3DTEXTURE9)(pTexture->GetTexturePTR());

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	for (DWORD z = 0; z < m_dwVtxCntZ; ++z)
	{
		for (DWORD x = 0; x < m_dwVtxCntX; ++x)
		{
			dwIndex = z * m_dwVtxCntX + x;

			pVertex[dwIndex].vPosition = D3DXVECTOR3((x * m_dwVtxIntvX), 0.f, (z * m_dwVtxIntvZ));
			pVertex[dwIndex].vTexUV = D3DXVECTOR2(float(z) / (m_dwVtxCntZ - 1), float(x) / (m_dwVtxCntX - 1));
		}
	}
	m_pVB->Unlock();

	DWORD		dwTriCnt = 0;
	IDX32* pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	for (DWORD z = 0; z < m_dwVtxCntZ - 1; ++z)
	{
		for (DWORD x = 0; x < m_dwVtxCntX - 1; ++x)
		{
			dwIndex = z * m_dwVtxCntX + x;

			pIndex[dwTriCnt]._0 = dwIndex + m_dwVtxCntX;
			pIndex[dwTriCnt]._1 = dwIndex + m_dwVtxCntX + 1;
			pIndex[dwTriCnt]._2 = dwIndex + 1;
			dwTriCnt++;

			pIndex[dwTriCnt]._0 = dwIndex + m_dwVtxCntX;
			pIndex[dwTriCnt]._1 = dwIndex + 1;
			pIndex[dwTriCnt]._2 = dwIndex;
			dwTriCnt++;

		}
	}
	m_pIB->Unlock();
}

//bool CTerrain::Init(void) noexcept
//{
//	//m_dwFVF = VTXTEX_FVF;
//	//m_dwTriCnt = (m_dwVtxCntX - 1) * (m_dwVtxCntZ - 1) * 2;
//	//m_dwVtxCnt = m_dwVtxCntX * m_dwVtxCntZ;
//	//m_dwVtxSize = sizeof(VTTEX);
//
//	//m_IdxFmt = D3DFMT_INDEX32;
//	//m_dwIdxSize = sizeof(IDX32);
//
//	//if (FAILED(m_pGraphicDev->CreateVertexBuffer(m_dwVtxSize * m_dwVtxCnt, 0, m_dwFVF, D3DPOOL_MANAGED, &m_pVB, NULL)))
//	//	return false;
//
//	//if (FAILED(m_pGraphicDev->CreateIndexBuffer(m_dwIdxSize * m_dwTriCnt, 0, m_IdxFmt, D3DPOOL_MANAGED, &m_pIB, NULL)))
//	//	return false;
//
//	//VTTEX* pVertex = nullptr;
//	//DWORD	dwIndex = 0;
//
//	//Texture* pTexture = new Texture();
//
//	//pTexture->Init(m_pGraphicDev, "Resource/Player0.jpg");
//	//m_pTexture = pTexture->GetTexturePTR();
//
//	//m_pVB->Lock(0, 0, (void**)&pVertex, 0);
//
//	//for (DWORD z = 0; z < m_dwVtxCntZ; ++z)
//	//{
//	//	for (DWORD x = 0; x < m_dwVtxCntX; ++x)
//	//	{
//	//		dwIndex = z * m_dwVtxCntX + x;
//
//	//		pVertex[dwIndex].vPosition = D3DXVECTOR3((x * m_dwVtxIntvX), 0.f, (z * m_dwVtxIntvZ));
//	//		pVertex[dwIndex].vTexUV = D3DXVECTOR2(float(z) / (m_dwVtxCntZ - 1) , float(x) / (m_dwVtxCntX - 1));
//	//		//pVertex[dwIndex].vPos = D3DXVECTOR3((x * m_dwVtxIntvX), 0.f, (z * m_dwVtxIntvZ));
//	//		//pVertex[dwIndex].dwColor = D3DXCOLOR(0.5f, 1.f, 0.5f, 1.f);
//	//	}
//	//}
//	//m_pVB->Unlock();
//
//	//DWORD		dwTriCnt = 0;
//	//IDX32* pIndex = nullptr;
//
//	//m_pIB->Lock(0, 0, (void**)&pIndex, 0);
//
//	//for (DWORD z = 0; z < m_dwVtxCntZ - 1; ++z)
//	//{
//	//	for (DWORD x = 0; x < m_dwVtxCntX - 1; ++x)
//	//	{
//	//		dwIndex = z * m_dwVtxCntX + x;
//
//	//		pIndex[dwTriCnt]._0 = dwIndex + m_dwVtxCntX;
//	//		pIndex[dwTriCnt]._1 = dwIndex + m_dwVtxCntX + 1;
//	//		pIndex[dwTriCnt]._2 = dwIndex + 1;
//	//		dwTriCnt++;
//
//	//		pIndex[dwTriCnt]._0 = dwIndex + m_dwVtxCntX;
//	//		pIndex[dwTriCnt]._1 = dwIndex + 1;
//	//		pIndex[dwTriCnt]._2 = dwIndex;
//	//		dwTriCnt++;
//
//	//	}
//	//}
//	//m_pIB->Unlock();
//
//
//	return true;
//}

void CTerrain::Update(float fElapsedTime) noexcept
{
}

//void CTerrain::Render(void) noexcept
//{
//	m_pGraphicDev->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);
//	m_pGraphicDev->SetFVF(m_dwFVF);
//	m_pGraphicDev->SetIndices(m_pIB);
//	m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwVtxCnt, 0, m_dwTriCnt);
//
//	m_pGraphicDev->SetTexture(0, m_pTexture);
//}
//
//void CTerrain::Release(void) noexcept
//{
//}
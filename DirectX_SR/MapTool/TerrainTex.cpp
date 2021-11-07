#include "pch.h"
#include "TerrainTex.h"
#include "MainFrm.h"
#include "CForm.h"
#include "Transform.h"
#include "MapTab.h"

CTerrain::CTerrain(LPDIRECT3DDEVICE9 pGraphicDevconst
					, const DWORD& dwCntX, const DWORD& dwCntZ, const DWORD& dwRoomNumber
					, const int& dwMoveX, const int& dwMoveZ)
	: m_pGraphicDev(pGraphicDevconst)
	, m_RoomNumber(dwRoomNumber)
	, m_dwVtxCntX(dwCntX), m_dwVtxCntZ(dwCntZ)
	, m_dwVtxCnt(0),m_dwVtxSize(0),m_dwTriCnt(0), m_dwFVF(0)
	, m_dwIdxSize(0), m_IdxFmt(D3DFMT_UNKNOWN)
	, m_pIB(nullptr), m_pVB(nullptr)
	, _iCurrMovePositionX(dwMoveX), _iCurrMovePositionZ(dwMoveZ)
{
}

CTerrain::~CTerrain(void)
{
	delete[] _pVtxPos;
	_pVtxPos = nullptr;
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

	_pVtxPos = new D3DXVECTOR3[m_dwVtxCnt];

	Buffer_Init(_iCurrMovePositionX,_iCurrMovePositionZ);

	CMainFrame*		pMain = static_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CForm*			pFormView = static_cast<CForm*>(pMain->m_tMainSplitter.GetPane(0, 0));

	_pMaptab = static_cast<MapTab*>(pFormView->m_pMapTab);
	
}

void CTerrain::Update(float fElapsedTime) noexcept
{
	if (_bMoveCheck)
	{	
		_iCurrMovePositionX = _pMaptab->_iMoveX;
		_iCurrMovePositionZ = _pMaptab->_iMoveZ;

		Buffer_Init(_iCurrMovePositionX,_iCurrMovePositionZ);
		_bMoveCheck = false;
	}
}

void CTerrain::DbgRender(void) noexcept
{
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	if (m_pTexture != 0)
		m_pGraphicDev->SetTexture(0, m_pTexture->GetTexturePTR());

	m_pGraphicDev->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);
	m_pGraphicDev->SetFVF(m_dwFVF);
	m_pGraphicDev->SetIndices(m_pIB);
	m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwVtxCnt, 0, m_dwTriCnt);

	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void CTerrain::Set_Textureinfo(Texture* pTexture, std::string& strfilepath)
{
	if (m_pTexture)
		m_pTexture = nullptr;

	_strFilePath = strfilepath;
	m_pTexture = pTexture;
}

void CTerrain::Buffer_Init(const int& iMoveX, const int& iMoveZ)
{
	VTTEX* pVertex = nullptr;
	DWORD	dwIndex = 0;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	for (DWORD z = 0; z < m_dwVtxCntZ; ++z)
	{
		for (DWORD x = 0; x < m_dwVtxCntX; ++x)
		{
			dwIndex = z * m_dwVtxCntX + x;

			pVertex[dwIndex].vPosition = D3DXVECTOR3(float(x + iMoveX), 0.f, float(z + iMoveZ));

			_pVtxPos[dwIndex] = pVertex[dwIndex].vPosition;

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

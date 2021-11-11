#include "pch.h"
#include "FloorTerrain.h"
#include "MainFrm.h"
#include "CForm.h"
#include "CubeTab.h"
#include "MapTab.h"

FloorTerrain::FloorTerrain(DWORD wwidth, DWORD whegiht, float flength)
	:
	 _wWidth(wwidth), _wHeight(whegiht)
	, _wWidthVertices(0), _wHeightVertices(0)
	, _dwTotalVertices(0x00), _dwTotalIndices(0x00)
	, _fLength(flength)
	, _dwPolygonsCount(0)
	, _pVertices(nullptr)
	, _nCurSelIndex(0)
	, _fBrushSize(2.f), _fSmoothSize(1.f)
	, _blPickOK(false)
	, _vGetPos(D3DXVECTOR3(0.f, 0.f, 0.f))
	, _fGetU(0.f), _fGetV(0.f)
	, _blClicked(false)
	, _nTexPosX(0), _nTexPosY(0)
{
	for (int i = 0; i < 4; ++i)
		_pDrawIndex[i] = i;

	_TexAlphaSize = (uint64)((_wWidth * _wHeight) / 2 );
	_MiniAlphaSize = 128;
}
FloorTerrain::~FloorTerrain(void)
{
	Close();
}

bool FloorTerrain::Open(LPDIRECT3DDEVICE9 pDevice) noexcept
{
	_pGraphicDev = pDevice;
	if(!LoadTextures())
		return MessageBoxA(nullptr, "LoadTextureErr", "Err", MB_OK);

	//if (CreateAlphaMaps() == 0)
	//	return MessageBoxA(nullptr, "CreateAlphaMaps Err", "Err", MB_OK);

	if (!TerrainInit(_wWidth,_wHeight,1.f))
		return MessageBoxA(nullptr, "TerrainInit", "Err", MB_OK);

	return true;
}

void FloorTerrain::Close(void) noexcept
{
	_vecFilepath.swap(std::vector<std::string>());
	_vecFilepath.clear();
	//_vecFilepath.shrink_to_fit();

	SAFE_RELEASE_(_pBaseTexture);
	for (int i = 0; i < MAXTEXNUM; ++i)
	{
		SAFE_RELEASE_(_Tex[i].pTexture);
		SAFE_RELEASE_(_Tex[i].pAlphamap);
	}
	SAFE_RELEASE_(_pVB);
	SAFE_RELEASE_(_pIB);
	SAFE_DELETE_(_pVertices);
}

void FloorTerrain::Render(LPDIRECT3DDEVICE9 pDevice) noexcept
{
	_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	_pGraphicDev->SetRenderState(D3DRS_ZENABLE, TRUE);

	// Allow multiple passes to blend together correctly
	// 여러 패스가 올바르게 혼합되도록 허용

	_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	PickingProcess(g_rtMfc, g_MousePos);

	if (_blClicked)
		DrawAlphamaps(_nCurSelIndex);

	TerrainRender();
	AlphaTextureRender();
	MiniAlphaTextureRender();
	DrawPickCircle(30, _fSmoothSize, 0xffffff00);
	DrawPickCircle(30, _fBrushSize, 0xffff0000);

	_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	_pGraphicDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	_pGraphicDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	_pGraphicDev->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	//_pGraphicDev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE);
	//_pGraphicDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);
	//_pGraphicDev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
}

bool FloorTerrain::TerrainInit(DWORD wWidth, DWORD wHeight, float fLength)
{
	WORD x, y;

	_wWidth = wWidth;
	_wHeight = wHeight;
	_wWidthVertices = wWidth + 1;									//맵의 가로 정점수
	_wHeightVertices = wHeight + 1;									//맵의 세로 정점수
	_dwTotalVertices = _wWidthVertices * _wHeightVertices;			//맵의 전체정점수

	_fLength = fLength;

	//if(FAILED(D3DXCreateTextureFromFile(_pd3dDevice, chFileName, &_Texture)))
	//{ return false;}

	//ex)2*2		

	//		6---7---8
	//		| ＼| ＼|
	//		3---4---5
	//		| ＼| ＼|
	//		0---1---2

	//2.정점좌표,텍스쳐좌표 설정

	_pVertices = new CUSVTX[_dwTotalVertices];

	for (y = 0; y < _wHeightVertices; ++y)
	{
		for (x = 0; x < _wWidthVertices; ++x)
		{
			_pVertices[(y * _wWidthVertices) + x].vPosition.x = (float)(x); //+ _fLength;
			_pVertices[(y * _wWidthVertices) + x].vPosition.y = 0.0f;
			_pVertices[(y * _wWidthVertices) + x].vPosition.z = (float)(y); //+ _fLength;

			_pVertices[(y * _wWidthVertices) + x].vAplhaUV.x = (float)x / (float)_wWidth;
			_pVertices[(y * _wWidthVertices) + x].vAplhaUV.y = 1.0f - (float)y / (float)_wHeight;
			_pVertices[(y * _wWidthVertices) + x].vTextureUV.x = (float)x / (float)_wWidth;
			_pVertices[(y * _wWidthVertices) + x].vTextureUV.y = 1.0f - (float)y / (float)_wHeight;
		}
	}

	//3.정점버퍼 설정

	void* pVertices;

	if (FAILED(_pGraphicDev->CreateVertexBuffer(
		_dwTotalVertices * sizeof(CUSVTX),
		0,
		D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT,
		&_pVB,
		NULL)))
	{
		return false;
	}

	if (FAILED(_pVB->Lock(0, _dwTotalVertices * sizeof(CUSVTX), (void**)&pVertices, 0)))
	{
		return false;
	}

	memcpy(pVertices, _pVertices,
		_dwTotalVertices * sizeof(CUSVTX));
	_pVB->Unlock();


	//4.인덱스 설정

	int total_strips =
		_wWidthVertices - 1;
	int total_indexes_per_strip =
		_wWidthVertices << 1;

	// the total number of indices is equal
	// 인덱스의 총 개수는 같음
	// 
	// to the number of strips times the
	// 스트립 수 배
	// 
	// indices used per strip plus one
	// 스트립당 사용된 인덱스 + 1
	// 
	// degenerate triangle between each strip
	// 각 스트립 사이의 퇴화 삼각형
	_dwTotalIndices = (total_indexes_per_strip * total_strips) + (total_strips << 1) - 2;

	unsigned short* pIndexValues = new unsigned short[_dwTotalIndices];

	unsigned short* index = pIndexValues;
	unsigned short start_vert = 0;
	unsigned short lineStep = (unsigned short)(_fLength * _wHeightVertices);

	for (y = 0; y < total_strips; ++y)
	{
		unsigned short vert = start_vert;

		// create a strip for this row
		for (x = 0; x < _wWidthVertices; ++x)
		{
			*(index++) = vert;
			*(index++) = vert + lineStep;
			vert += 1;
		}
		start_vert += lineStep;

		if (y + 1 < total_strips)
		{
			// add a degenerate to attach to 
			// the next row
			*(index++) = (vert - 1) + lineStep;
			*(index++) = start_vert;
		}
	}

	_dwPolygonsCount = _dwTotalIndices - 2; //스트립으로 그릴때는 2를빼준다
	//인덱스버퍼설정
	if (FAILED(_pGraphicDev->CreateIndexBuffer(
		_dwTotalIndices * sizeof(WORD), 0,
		D3DFMT_INDEX16, D3DPOOL_DEFAULT, &_pIB, NULL)))
	{
		return false;
	}

	void* pIndices;
	_pIB->Lock(0, 0, (void**)&pIndices, 0);
	memcpy(pIndices, pIndexValues, _dwTotalIndices * sizeof(WORD));
	_pIB->Unlock();

	delete[]pIndexValues;

	return true;
}

void FloorTerrain::TerrainRender()
{
	D3DXMATRIXA16 matTemp;

	_pGraphicDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	_pGraphicDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);

	// Allow multiple passes to blend together correctly
	_pGraphicDev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	_pGraphicDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	_pGraphicDev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	_pGraphicDev->SetIndices(_pIB);
	_pGraphicDev->SetFVF(D3DFVF_CUSTOMVERTEX);

	_pGraphicDev->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
	_pGraphicDev->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	_pGraphicDev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	_pGraphicDev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	D3DXMatrixScaling(&matTemp, (float)_wWidth, (float)_wHeight, 1.0f);

	_pGraphicDev->SetTransform(D3DTS_TEXTURE0, &matTemp);

	//m_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );

	_pGraphicDev->SetTexture(0, _pBaseTexture);
	_pGraphicDev->SetStreamSource(0, _pVB, 0, sizeof(CUSVTX));
	_pGraphicDev->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,		//프리미티브타입
		0,
		0,
		_dwTotalVertices,
		0,
		_dwPolygonsCount
	);

	_pGraphicDev->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
}

void FloorTerrain::SetAlphaTex(IDirect3DTexture9* pTexture, IDirect3DTexture9* pTextureAlpha, int i)
{
	_Tex[i].pTexture = pTexture;
	_Tex[i].pAlphamap = pTextureAlpha;

	//memcpy(_Tex[i].pTexture, pTexture, sizeof(IDirect3DTexture9)); 
	//memcpy(_Tex[i].pAlphamap, pTextureAlpha, sizeof(IDirect3DTexture9));
}

bool FloorTerrain::LoadTextures()
{
	CMainFrame* pMain = static_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CForm* pFormView = static_cast<CForm*>(pMain->m_tMainSplitter.GetPane(0, 0));
	MapTab* pMaptab = pFormView->m_pMapTab;


	if (FAILED(D3DXCreateTextureFromFileA(_pGraphicDev,"Resource/Tile1.png", &_pBaseTexture)))
	{
		MessageBoxA(NULL, "Failed to load 'Tile1.png'", "Error", MB_OK);
		return FALSE;
	}
	_vecFilepath.emplace_back("Resource/Tile1.png");

	if (FAILED(D3DXCreateTextureFromFileA(_pGraphicDev,"Resource/Tile2.png", &_Tex[0].pTexture)))
	{
		MessageBoxA(NULL, "Failed to load 'Tile2.png'", "Error", MB_OK);
		return FALSE;
	}
	_vecFilepath.emplace_back("Resource/Tile2.png");

	if (FAILED(D3DXCreateTextureFromFileA(_pGraphicDev, "Resource/Tile3.png", &_Tex[1].pTexture))) 
	{
		MessageBoxA(NULL, "Failed to load 'Tile3.png'", "Error", MB_OK);
		return FALSE;
	}
	_vecFilepath.emplace_back("Resource/Tile3.png");

	if (FAILED(D3DXCreateTextureFromFileA(_pGraphicDev, "Resource/Tile4.png", &_Tex[2].pTexture))) 
	{
		MessageBoxA(NULL, "Failed to load 'Tile3.png'", "Error", MB_OK);
		return FALSE;
	}
	_vecFilepath.emplace_back("Resource/Tile4.png");

	if (FAILED(D3DXCreateTextureFromFileA(_pGraphicDev, "Resource/Tile5.png", &_Tex[3].pTexture))) 
	{
		MessageBoxA(NULL, "Failed to load 'Tile5.png'", "Error", MB_OK);
		return FALSE;
	}
	_vecFilepath.emplace_back("Resource/Tile5.png");

	CreateAlphaMaps();

	return true;
}

BOOL FloorTerrain::CreateAlphaMaps()
{
	for (int i = 0; i < MAXTEXNUM; ++i)
	{
		if (FAILED(_pGraphicDev->CreateTexture((UINT)_TexAlphaSize, (UINT)_TexAlphaSize, 1, 0, D3DFMT_A8R8G8B8,
			D3DPOOL_MANAGED, &_Tex[i].pAlphamap, NULL)))
			return MessageBoxA(NULL, "alphaTexture make error", "Error", MB_OK);

		D3DLOCKED_RECT		AlphaMap_Locked;

		memset(&AlphaMap_Locked, 0, sizeof(D3DLOCKED_RECT));

		if (FAILED(_Tex[i].pAlphamap->LockRect(0, &AlphaMap_Locked, NULL, 0)))
			return MessageBoxA(NULL, "alphaTexture Lock error", "Error", MB_OK);

		LPBYTE pDataDST = (LPBYTE)AlphaMap_Locked.pBits;

		for (int j = 0; j < _TexAlphaSize; ++j)
		{
			LPDWORD pDWordDST = (LPDWORD)(pDataDST + j * AlphaMap_Locked.Pitch);

			for (int i = 0; i < _TexAlphaSize; ++i)
			{
				*(pDWordDST + i) = 0x00000000;
			}
		}

		if (FAILED(_Tex[i].pAlphamap->UnlockRect(0)))
			return MessageBoxA(NULL, "alphaTexture UnLock error", "Error", MB_OK);
	}

	return TRUE;
}

BOOL FloorTerrain::IntersectTriangle(const D3DXVECTOR3& orig, const D3DXVECTOR3& dir, D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2, FLOAT* t, FLOAT* u, FLOAT* v)
{
	// Find vectors for two edges sharing vert0
	D3DXVECTOR3 edge1 = v1 - v0;
	D3DXVECTOR3 edge2 = v2 - v0;

	// Begin calculating determinant - also used to calculate U parameter
	D3DXVECTOR3 pvec;
	D3DXVec3Cross(&pvec, &dir, &edge2);

	// If determinant is near zero, ray lies in plane of triangle
	FLOAT det = D3DXVec3Dot(&edge1, &pvec);

	D3DXVECTOR3 tvec;
	if (det > 0)
	{
		tvec = orig - v0;
	}
	else
	{
		tvec = v0 - orig;
		det = -det;
	}

	if (det < 0.0001f)
		return FALSE;

	// Calculate U parameter and test bounds
	*u = D3DXVec3Dot(&tvec, &pvec);
	if (*u < 0.0f || *u > det)
		return FALSE;

	// Prepare to test V parameter
	D3DXVECTOR3 qvec;
	D3DXVec3Cross(&qvec, &tvec, &edge1);

	// Calculate V parameter and test bounds
	*v = D3DXVec3Dot(&dir, &qvec);
	if (*v < 0.0f || *u + *v > det)
		return FALSE;

	// Calculate t, scale parameters, ray intersects triangle
	*t = D3DXVec3Dot(&edge2, &qvec);
	FLOAT fInvDet = 1.0f / det;
	*t *= fInvDet;
	*u *= fInvDet;
	*v *= fInvDet;

	return TRUE;
}

void FloorTerrain::PickingProcess(RECT& rtRect, CPoint ptMouse/* float fCurPosX, float fCurPosY*/)
{
	D3DXVECTOR3 v, vOrg, vDir, vPicked;
	D3DXMATRIXA16 matWorld, matView, matProj;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);
	
	// Get Picking Ray.

	_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
	_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixInverse(&matWorld, NULL, &matView);


	/*rtRect.right = rtRect.right + 300;*/
	/*rtRect.left = rtRect.left + 300;*/

	FLOAT fWidth = FLOAT(rtRect.right - rtRect.left);
	FLOAT fHeight = FLOAT(rtRect.bottom - rtRect.top);

	v.x = (((ptMouse.x * 2.0f / fWidth) - 1.0f)) / matProj._11;
	v.y = (-((ptMouse.y * 2.0f / fHeight) - 1.0f)) / matProj._22;
	v.z = 1.0f;


	vDir.x = v.x * matWorld._11 + v.y * matWorld._21 + v.z * matWorld._31;
	vDir.y = v.x * matWorld._12 + v.y * matWorld._22 + v.z * matWorld._32;
	vDir.z = v.x * matWorld._13 + v.y * matWorld._23 + v.z * matWorld._33;

	vOrg.x = matWorld._41;
	vOrg.y = matWorld._42;
	vOrg.z = matWorld._43;


	D3DXVECTOR3 v0, v1, v2, v3;
	WORD x, y;
	float fDist;

	for (y = 0; y < _wHeight; ++y)
	{
		for (x = 0; x < _wWidth; ++x)
		{
			v0 = D3DXVECTOR3(_pVertices[y * _wWidthVertices + x].vPosition.x,
				_pVertices[y * _wWidthVertices + x].vPosition.y,
				_pVertices[y * _wWidthVertices + x].vPosition.z);

			v1 = D3DXVECTOR3(_pVertices[(y + 1) * _wWidthVertices + x].vPosition.x,
				_pVertices[(y + 1) * _wWidthVertices + x].vPosition.y,
				_pVertices[(y + 1) * _wWidthVertices + x].vPosition.z);

			v2 = D3DXVECTOR3(_pVertices[y * _wWidthVertices + (x + 1)].vPosition.x,
				_pVertices[y * _wWidthVertices + (x + 1)].vPosition.y,
				_pVertices[y * _wWidthVertices + (x + 1)].vPosition.z);

			v3 = D3DXVECTOR3(_pVertices[(y + 1) * _wWidthVertices + (x + 1)].vPosition.x,
				_pVertices[(y + 1) * _wWidthVertices + (x + 1)].vPosition.y,
				_pVertices[(y + 1) * _wWidthVertices + (x + 1)].vPosition.z);

			if (IntersectTriangle(vOrg, vDir,
				v0, v1, v2,
				&fDist, &_fGetU, &_fGetV))
			{
				//_vGetPos = vOrg + vDir * fDist;
				_vGetPos = PickingOnTerrain(ptMouse);
				_blPickOK = TRUE;
				break;
			}
			else if (IntersectTriangle(vOrg, vDir,
				v1, v3, v2,
				&fDist, &_fGetU, &_fGetV))
			{
				//_vGetPos = vOrg + vDir * fDist;
				_vGetPos = PickingOnTerrain(ptMouse);
				_blPickOK = TRUE;
				break;
			}
			else
				_blPickOK = FALSE;
		}
	}
	// 선생님 픽킹 성공 했을때 월드 좌표의 버텍스 좌표의 위치를 _vGetpos 에 넣어주고 _blPickok 던지고 실패하면 false 던지고
}

D3DXVECTOR3 FloorTerrain::PickingOnTerrain(CPoint point)
{
	CMainFrame* pMain = static_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CForm* pFormView = static_cast<CForm*>(pMain->m_tMainSplitter.GetPane(0, 0));
	CubeTab* pCubetab = pFormView->m_pCubeTab;

	//-----------------------------------------------------------------//
	D3DVIEWPORT9		ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));

	D3DXVECTOR3 vMousePos;
	D3D9DEVICE->GetDevice()->GetViewport(&ViewPort);

	vMousePos.x = (point.x) / (ViewPort.Width * 0.5f) - 1.f;
	vMousePos.y = point.y / -(ViewPort.Height * 0.5f) + 1.f;
	vMousePos.z = 0.f;

	D3DXMATRIX	matPorj;
	D3D9DEVICE->GetDevice()->GetTransform(D3DTS_PROJECTION, &matPorj);
	D3DXMatrixInverse(&matPorj, NULL, &matPorj);
	D3DXVec3TransformCoord(&vMousePos, &vMousePos, &matPorj);

	D3DXVECTOR3 vRayPos, vRayDir;

	vRayPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	vRayDir = vMousePos - vRayPos;

	D3DXMATRIX	matView;
	D3D9DEVICE->GetDevice()->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, NULL, &matView);

	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);

	D3DXMATRIX	matWorld;
	_pGraphicDev->GetTransform(D3DTS_WORLD, &matWorld);
	D3DXMatrixInverse(&matWorld, NULL, &matWorld);

	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matWorld);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matWorld);

	DWORD VtxX = _wWidthVertices;
	DWORD VtxZ = _wHeightVertices;

	DWORD dwVtxIndx[3];
	float fU, fV, fDist;

	for (DWORD z = 0; z < VtxZ - 1; ++z)
	{
		for (DWORD x = 0; x < VtxX - 1; ++x)
		{
			DWORD dwIndex = z * VtxX + x;

			dwVtxIndx[0] = dwIndex + VtxX;
			dwVtxIndx[1] = dwIndex + VtxX + 1;
			dwVtxIndx[2] = dwIndex + 1;

			if (D3DXIntersectTri(&_pVertices[dwVtxIndx[1]].vPosition, &_pVertices[dwVtxIndx[0]].vPosition, &_pVertices[dwVtxIndx[2]].vPosition
				, &vRayPos, &vRayDir, &fU, &fV, &fDist))
			{
				if (pFormView->m_iTabIndex == 1)
				{
					int iFloor = pCubetab->iFloor;

					return D3DXVECTOR3((_pVertices[dwVtxIndx[0]].vPosition.x + _pVertices[dwVtxIndx[2]].vPosition.x) * 0.5f
						, ((float)iFloor - 0.5f)
						, (_pVertices[dwVtxIndx[2]].vPosition.z + _pVertices[dwVtxIndx[1]].vPosition.z) * 0.5f);
				}
				else
				{
					return D3DXVECTOR3(_pVertices[dwVtxIndx[1]].vPosition.x + (_pVertices[dwVtxIndx[0]].vPosition.x - _pVertices[dwVtxIndx[1]].vPosition.x) * fU
						, 0.f
						, _pVertices[dwVtxIndx[1]].vPosition.z + (_pVertices[dwVtxIndx[2]].vPosition.z - _pVertices[dwVtxIndx[1]].vPosition.z) * fV);
				}
			}

			dwVtxIndx[0] = dwIndex + VtxX;
			dwVtxIndx[1] = dwIndex + 1;
			dwVtxIndx[2] = dwIndex;

			if (D3DXIntersectTri(&_pVertices[dwVtxIndx[2]].vPosition, &_pVertices[dwVtxIndx[1]].vPosition, &_pVertices[dwVtxIndx[0]].vPosition
				, &vRayPos, &vRayDir, &fU, &fV, &fDist))
			{
				if (pFormView->m_iTabIndex == 1)
				{
					int iFloor = pCubetab->iFloor;

					return D3DXVECTOR3((_pVertices[dwVtxIndx[0]].vPosition.x + _pVertices[dwVtxIndx[1]].vPosition.x) * 0.5f
						, ((float)iFloor - 0.5f)
						, (_pVertices[dwVtxIndx[0]].vPosition.z + _pVertices[dwVtxIndx[2]].vPosition.z) * 0.5f);
				}
				else
				{
					return D3DXVECTOR3(_pVertices[dwVtxIndx[2]].vPosition.x + (_pVertices[dwVtxIndx[1]].vPosition.x - _pVertices[dwVtxIndx[2]].vPosition.x) * fU
						, 0.f
						, _pVertices[dwVtxIndx[2]].vPosition.z + (_pVertices[dwVtxIndx[0]].vPosition.z - _pVertices[dwVtxIndx[1]].vPosition.z) * fV);
				}
			}
		}
	}
	return D3DXVECTOR3(0.f, 0.f, 0.f);
}

bool FloorTerrain::DrawAlphamaps(int nIndex)
{
	// 알파맵의 한 픽셀이 월드 상의 한점의 크기를 구한다.
	// 1.0f <-현재 사각형1개만그렸으므로
	//float		PixSize		= 1.0f/(float)TEXALPHASIZE;
	//float		PixSize = (float)MAPWIDTH / (float)TEXALPHASIZE;
	float		PixSize = (float)_wWidth / (float)_TexAlphaSize;

	//전역브러시 와 전역스무스는 현재 브러쉬할원의 지름을 넣기대문에 반지름을 사용해야한다.
	float 	    fHalfBrushSize = _fBrushSize / 2.0f;
	float		fHalfSmoothSize = _fSmoothSize / 2.0f;

	// 에디터의 원의 최대 크기에 한점의 크기를 나누워서
	// 몇픽셀을 에디터 하는지 크기를 구한다.
	float		EditSize = fHalfBrushSize / PixSize;

	float	PosU = _vGetPos.x / (float)(_wWidth);
	float	PosV = 1 - _vGetPos.z / (float)(_wHeight);
	//float	PosV = _vGetPos.z / (float)(MAPHEIGHT);


	_nTexPosX = int(PosU * _TexAlphaSize);
	_nTexPosY = int(PosV * _TexAlphaSize);

	int StartPosX = int(((_nTexPosX - EditSize) < 0) ? 0 : _nTexPosX - EditSize);
	int StartPosY = int(((_nTexPosY - EditSize) < 0) ? 0 : _nTexPosY - EditSize);
	int EndPosX = int(((_nTexPosX + EditSize) >= _TexAlphaSize) ? _TexAlphaSize - 1 : _nTexPosX + EditSize);
	int EndPosY = int(((_nTexPosY + EditSize) >= _TexAlphaSize) ? _TexAlphaSize - 1 : _nTexPosY + EditSize);

	DWORD dwChangeColor = 0x00;
	float Smooth = 0.0f;
	DWORD dwA = 0x00;

	D3DLOCKED_RECT		AlphaMap_Locked;

	memset(&AlphaMap_Locked, 0, sizeof(D3DLOCKED_RECT));

	if (FAILED(_Tex[nIndex].pAlphamap->LockRect(0, &AlphaMap_Locked, NULL, 0)))
	{
		MessageBoxA(NULL, "alphaTexture Lock error", "Error", MB_OK);
		return FALSE;
	}
	LPBYTE pDataDST = (LPBYTE)AlphaMap_Locked.pBits;

	for (int j = StartPosY; j <= EndPosY; ++j)
	{
		LPDWORD pDWordDST = (LPDWORD)(pDataDST + j * AlphaMap_Locked.Pitch);

		for (int i = StartPosX; i <= EndPosX; ++i)
		{
			D3DXVECTOR3 Pix = D3DXVECTOR3(i * PixSize, 0.0f, j * PixSize) -
				D3DXVECTOR3(_nTexPosX * PixSize, 0.0f, _nTexPosY * PixSize);

			float Len = D3DXVec3Length(&Pix);

			if (Len <= fHalfSmoothSize)
			{
				dwChangeColor = 0xFFFFFFFF;
			}
			else if (Len <= fHalfBrushSize)
			{
				// 최대사이즈에 포함될 우 최대사이즈까지의
				// 선영보간한 알파값을 구한다.
				Len -= fHalfSmoothSize;
				Smooth = fHalfBrushSize - fHalfSmoothSize;
				dwChangeColor = DWORD((Smooth - Len) / Smooth * 0xFF000000);
				dwA = (dwChangeColor & 0xFF000000) >> 24;
				dwChangeColor = (dwA << 24) | (dwA << 16) | (dwA << 8) | dwA;
			}
			else
			{
				continue;
			}

			*(pDWordDST + i) = (*(pDWordDST + i) < dwChangeColor) ? dwChangeColor : *(pDWordDST + i);
		}
	}

	if (FAILED(_Tex[nIndex].pAlphamap->UnlockRect(0)))
	{
		MessageBoxA(NULL, "alphaTexture UnLock error", "Error", MB_OK);
		return FALSE;
	}

	return true;
}

void FloorTerrain::DrawPickCircle(int Count, float size, D3DCOLOR Col)
{
	if (Count < 4) Count = 4;
	float Step = (D3DX_PI * 2) / Count;

	L3D				S_Line[2];
	D3DXVECTOR3     NewPos, Pos;
	D3DXMATRIXA16   matRot;

	Pos = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//size 도 원의 지름이 넘어오므로 반지름으로 만들어줘야한다
	size = size / 2.0f;

	S_Line[1].VPos = Pos * size + _vGetPos;
	S_Line[1].Col = S_Line[0].Col = Col;
	S_Line[1].VPos.y = 0.001f;
	_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	_pGraphicDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	_pGraphicDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);

	for (int i = 1; i < Count + 1; ++i) {
		S_Line[0].VPos = S_Line[1].VPos;

		D3DXMatrixRotationY(&matRot, i * Step);
		D3DXVec3TransformCoord(&NewPos, &Pos, &matRot);
		D3DXVec3Normalize(&NewPos, &NewPos);

		S_Line[1].VPos = (NewPos * size) + _vGetPos;
		S_Line[1].VPos.y = 0.001f;

		_pGraphicDev->SetFVF(D3DFVF_LINE3D);
		_pGraphicDev->DrawPrimitiveUP(D3DPT_LINELIST, 1, S_Line, sizeof(L3D));

		_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}
	_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void FloorTerrain::AlphaTextureRender()
{
	_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

	// Texture: take the color from the texture, take the alpha from the previous stage
	_pGraphicDev->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	_pGraphicDev->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	_pGraphicDev->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	_pGraphicDev->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_CURRENT);

	_pGraphicDev->SetIndices(_pIB);
	_pGraphicDev->SetFVF(D3DFVF_CUSTOMVERTEX);

	_pGraphicDev->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	_pGraphicDev->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	_pGraphicDev->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	// 0번 인덱스 알파 텍스쳐는 전체에 한번만 그려져야 하므로
	// 타일화 셋팅 하지 않음
	_pGraphicDev->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	_pGraphicDev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	_pGraphicDev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	_pGraphicDev->SetTextureStageState(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
	_pGraphicDev->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);
	_pGraphicDev->SetSamplerState(1, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	_pGraphicDev->SetSamplerState(1, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	D3DXMATRIXA16	matTemp;

	D3DXMatrixScaling(&matTemp, (float)_wWidth, (float)_wHeight, 1.0f);

	_pGraphicDev->SetTransform(D3DTS_TEXTURE0, &matTemp);
	_pGraphicDev->SetTransform(D3DTS_TEXTURE1, &matTemp);


	for (int i = 0; i < MAXTEXNUM; ++i)
	{
		_pGraphicDev->SetTexture(0, _Tex[_pDrawIndex[i]].pAlphamap);
		_pGraphicDev->SetTexture(1, _Tex[_pDrawIndex[i]].pTexture);
		_pGraphicDev->SetStreamSource(0, _pVB, 0, sizeof(CUSVTX));

		_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,_dwTotalVertices,0,_dwPolygonsCount);
	}

	_pGraphicDev->SetTextureStageState(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);

	// 멀티텍스쳐 0,1번 셋팅을 사용을 중지 한다.
	_pGraphicDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);
	_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	_pGraphicDev->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	_pGraphicDev->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	// 알파 사용을 중지 한다. 
	_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void FloorTerrain::MiniAlphaTextureRender()
{
	static float MiniAlphaTex[4][6] =
	{
		{ WINCX - _MiniAlphaSize,			0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
		{ WINCX,							0.0f, 0.0f, 1.0f, 1.0f, 0.0f },
		{ WINCX - _MiniAlphaSize, _MiniAlphaSize, 0.0f, 1.0f, 0.0f, 1.0f },
		{ WINCX,			   _MiniAlphaSize,	  0.0f, 1.0f, 1.0f, 1.0f },
	};

	_pGraphicDev->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
	_pGraphicDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	_pGraphicDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	_pGraphicDev->SetTexture(0, _Tex[_nCurSelIndex].pAlphamap);
	_pGraphicDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, MiniAlphaTex, sizeof(MiniAlphaTex[0]));
}

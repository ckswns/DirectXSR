#include "pch.h"
#include "FloorTerrain.h"

FloorTerrain::FloorTerrain(WORD wwith, WORD whegiht, float flength)
	:
	 _wWidth(wwith), _wHeight(whegiht)
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
}
FloorTerrain::~FloorTerrain(void)
{
}

bool FloorTerrain::Open(LPDIRECT3DDEVICE9 pDevice) noexcept
{
	_pGraphicDev = pDevice;
	if(!LoadTextures())
		return MessageBoxA(nullptr, "LoadTextureErr", "Err", MB_OK);

	if (CreateAlphaMaps() == 0)
		return MessageBoxA(nullptr, "CreateAlphaMaps Err", "Err", MB_OK);

	if (!TerrainInit())
		return MessageBoxA(nullptr, "TerrainInit", "Err", MB_OK);

	return true;
}

void FloorTerrain::Render(LPDIRECT3DDEVICE9 pDevice) noexcept
{
	//PickingProcess(g_rtMfc, g_MousePosX, g_MousePosY);
	//if (_blClicked)
	//	DrawAlphamaps(_nCurSelIndex);

	//Mesh::Render(pDevice);


	TerrainRender();
	AlphaTextureRender();
	MiniAlphaTextureRender();
	DrawPickCircle(30, _fSmoothSize, 0xffffff00);
	DrawPickCircle(30, _fBrushSize, 0xffff0000);
}

bool FloorTerrain::TerrainInit()
{
	WORD x, z;

	_wWidthVertices = _wWidth + 1;
	_wHeightVertices = _wHeight + 1;
	_dwTotalVertices = _wWidthVertices * _wHeightVertices;
	
	_pVertices = new CUSVTX[_dwTotalVertices];

	//memset(_pVertices, sizeof(CUSVTX) * _dwTotalVertices, NULL);

	WORD dwIndx = 0;
	for (z = 0; z < _wHeightVertices; ++z)
	{
		for (x = 0; x < _wWidthVertices; ++x)
		{
			dwIndx = (z * _wWidthVertices) + x;

			_pVertices[dwIndx].vPosition.x = float(x);
			_pVertices[dwIndx].vPosition.y = 0.f;
			_pVertices[dwIndx].vPosition.z = float(z);

			_pVertices[dwIndx].vAplhaUV.x = (float)x / (float)_wWidth; // Alpha U
			_pVertices[dwIndx].vAplhaUV.y = 1.0f - (float)z / (float)_wHeight; // Alpha V

			_pVertices[dwIndx].vTextureUV.x = (float)x / (float)_wWidth; // Texture U
			_pVertices[dwIndx].vTextureUV.y = 1.0f - (float)z / (float)_wHeight; // Texture V
		}
	}
	void* pVertices;

	if (FAILED(_pGraphicDev->CreateVertexBuffer(_dwTotalVertices * sizeof(CUSVTX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &_pVB, NULL)))
		return false;

	if (FAILED(_pVB->Lock(0, sizeof(CUSVTX) * _dwTotalVertices, (void**)&pVertices, 0)))
		return false;

	memcpy(pVertices, _pVertices, sizeof(CUSVTX) * _dwTotalVertices);
	_pVB->Unlock();

	//-----------------------------------------------------------------------------------//
	// 인덱스 버퍼 설정
	int totalStrips = _wWidthVertices - 1;
	int total_Indexes_per_strip = _wHeightVertices << 1;

	_dwTotalIndices = (total_Indexes_per_strip * totalStrips) + (totalStrips << 1) - 2;

	WORD*	pIndexValues = new WORD[_dwTotalIndices];
	WORD*	Index = pIndexValues;
	WORD	start_vertex = 0;
	WORD	linestep = (WORD)(_fLength * _wHeightVertices);

	for (z = 0; z < totalStrips; ++z)
	{
		WORD vertex = start_vertex;

		for (x = 0; x < _wWidthVertices; ++x)
		{
			*(Index++) = vertex;
			*(Index++) = vertex + linestep;
			//vertex += 1;
			vertex++;

		}
		start_vertex += linestep;

		if (z + 1 < totalStrips)
		{
			*(Index++) = (vertex - 1) + linestep;
			*(Index++) = start_vertex;
		}
	}

	_dwPolygonsCount = _dwTotalIndices - 2;

	if (FAILED(_pGraphicDev->CreateIndexBuffer(_dwTotalIndices * sizeof(WORD), 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &_pIB, NULL)))
		return false;

	void* pIndices;
	_pIB->Lock(0, 0, (void**)&pIndices, 0);
	memcpy(pIndices, pIndexValues , _dwTotalIndices * sizeof(WORD));
	_pIB->Unlock();

	delete[] pIndexValues;

	return true;
}

void FloorTerrain::TerrainRender()
{
	D3DXMATRIXA16 matTemp;

	_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	_pGraphicDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	_pGraphicDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);

	// Allow multiple passes to blend together correctly
	//여러 패스가 올바르게 혼합되도록 허용

	_pGraphicDev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	_pGraphicDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	_pGraphicDev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	_pGraphicDev->SetIndices(_pIB);
	_pGraphicDev->SetFVF(D3DFVF_CUSTOMVERTEX);

	_pGraphicDev->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
	_pGraphicDev->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	_pGraphicDev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	_pGraphicDev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	D3DXMatrixScaling(&matTemp, _wWidth, _wHeight, 1.0f);

	_pGraphicDev->SetTransform(D3DTS_TEXTURE0, &matTemp);

	//m_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );

	_pGraphicDev->SetTexture(0, _pBaseTexture);
	_pGraphicDev->SetStreamSource(0, _pVB, 0, sizeof(CUSVTX));
	_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, _dwTotalVertices, 0, _dwPolygonsCount);
	_pGraphicDev->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);

	//_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);
}

bool FloorTerrain::LoadTextures()
{
	if (FAILED(D3DXCreateTextureFromFileA(_pGraphicDev, "Resource/Tile1.png", &_pBaseTexture))) {
		MessageBoxA(NULL, "Failed to load 'Tile1.png'", "Error", MB_OK);
		return FALSE;
	}

	if (FAILED(D3DXCreateTextureFromFileA(_pGraphicDev, "Resource/Tile0.png", &_Tex[0].pTexture))) {
		MessageBoxA(NULL, "Failed to load 'Tile0.png'", "Error", MB_OK);
		return FALSE;
	}

	if (FAILED(D3DXCreateTextureFromFileA(_pGraphicDev, "Resource/Tile2.png", &_Tex[1].pTexture))) {
		MessageBoxA(NULL, "Failed to load 'Tile2.png'", "Error", MB_OK);
		return FALSE;
	}

	//if (FAILED(D3DXCreateTextureFromFileA(_pGraphicDev, "Resource/Tile3.png", &_Tex[2].pTexture))) {
	//	MessageBoxA(NULL, "Failed to load 'Tile3.png'", "Error", MB_OK);
	//	return FALSE;
	//}

	//if (FAILED(D3DXCreateTextureFromFileA(_pGraphicDev, "Resource/Tile4.png", &_Tex[3].pTexture))) {
	//	MessageBoxA(NULL, "Failed to load 'Tile4.png'", "Error", MB_OK);
	//	return FALSE;
	//}

	CreateAlphaMaps();

	return true;
}

BOOL FloorTerrain::CreateAlphaMaps()
{
	for (int i = 0; i < MAXTEXNUM; ++i)
	{
		if (FAILED(_pGraphicDev->CreateTexture(TEXALPHASIZE, TEXALPHASIZE, 1, 0, D3DFMT_A8R8G8B8,
			D3DPOOL_MANAGED, &_Tex[i].pAlphamap, NULL)))

			return MessageBoxA(NULL, "alphaTexture make error", "Error", MB_OK);

		D3DLOCKED_RECT		AlphaMap_Locked;

		memset(&AlphaMap_Locked, 0, sizeof(D3DLOCKED_RECT));

		if (FAILED(_Tex[i].pAlphamap->LockRect(0, &AlphaMap_Locked, NULL, 0)))
			return MessageBoxA(NULL, "alphaTexture Lock error", "Error", MB_OK);

		LPBYTE pDataDST = (LPBYTE)AlphaMap_Locked.pBits;

		for (int j = 0; j < TEXALPHASIZE; ++j)
		{
			LPDWORD pDWordDST = (LPDWORD)(pDataDST + j * AlphaMap_Locked.Pitch);

			for (int i = 0; i < TEXALPHASIZE; ++i)
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

void FloorTerrain::PickingProcess(RECT& rtRect, float fCurPosX, float fCurPosY)
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

	FLOAT fWidth = FLOAT(rtRect.right - rtRect.left);
	FLOAT fHeight = FLOAT(rtRect.bottom - rtRect.top);

	v.x = (((fCurPosX * 2.0f / fWidth) - 1.0f)) / matProj._11;
	v.y = (-((fCurPosY * 2.0f / fHeight) - 1.0f)) / matProj._22;
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

	for (y = 0; y < MAPHEIGHT; ++y)
	{
		for (x = 0; x < MAPWIDTH; ++x)
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
				_vGetPos = vOrg + vDir * fDist;
				_blPickOK = TRUE;
				break;
			}
			else if (IntersectTriangle(vOrg, vDir,
				v1, v3, v2,
				&fDist, &_fGetU, &_fGetV))
			{
				_vGetPos = vOrg + vDir * fDist;
				_blPickOK = TRUE;
				break;
			}
			else
				_blPickOK = FALSE;
		}
	}
}

bool FloorTerrain::DrawAlphamaps(int nIndex)
{
	// 알파맵의 한 픽셀이 월드 상의 한점의 크기를 구한다.
	// 1.0f <-현재 사각형1개만그렸으므로
	//float		PixSize		= 1.0f/(float)TEXALPHASIZE;
	float		PixSize = (float)MAPWIDTH / (float)TEXALPHASIZE;

	//전역브러시 와 전역스무스는 현재 브러쉬할원의 지름을 넣기대문에 반지름을 사용해야한다.
	float 	    fHalfBrushSize = _fBrushSize / 2.0f;
	float		fHalfSmoothSize = _fSmoothSize / 2.0f;

	// 에디터의 원의 최대 크기에 한점의 크기를 나누워서
	// 몇픽셀을 에디터 하는지 크기를 구한다.
	float		EditSize = fHalfBrushSize / PixSize;

	float	PosU = _vGetPos.x / (float)(MAPWIDTH);
	float	PosV = 1 - _vGetPos.z / (float)(MAPHEIGHT);
	//float	PosV = m_vGetPos.z / (float)(MAPHEIGHT);


	_nTexPosX = int(PosU * TEXALPHASIZE);
	_nTexPosY = int(PosV * TEXALPHASIZE);

	int StartPosX = int(((_nTexPosX - EditSize) < 0) ? 0 : _nTexPosX - EditSize);
	int StartPosY = int(((_nTexPosY - EditSize) < 0) ? 0 : _nTexPosY - EditSize);
	int EndPosX = int(((_nTexPosX + EditSize) >= TEXALPHASIZE) ? TEXALPHASIZE - 1 : _nTexPosX + EditSize);
	int EndPosY = int(((_nTexPosY + EditSize) >= TEXALPHASIZE) ? TEXALPHASIZE - 1 : _nTexPosY + EditSize);

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

	D3DXMatrixScaling(&matTemp, _wWidth, _wHeight, 1.0f);

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
		{ WINCX - MINIALPHASIZE,			0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
		{ WINCX,							0.0f, 0.0f, 1.0f, 1.0f, 0.0f },
		{ WINCX - MINIALPHASIZE, MINIALPHASIZE,	  0.0f, 1.0f, 0.0f, 1.0f },
		{ WINCX,			   MINIALPHASIZE,	  0.0f, 1.0f, 1.0f, 1.0f },
	};

	_pGraphicDev->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
	_pGraphicDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	_pGraphicDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	_pGraphicDev->SetTexture(0, _Tex[_nCurSelIndex].pAlphamap);
	_pGraphicDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, MiniAlphaTex, sizeof(MiniAlphaTex[0]));
}

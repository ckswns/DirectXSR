
// MapToolView.cpp: CMapToolView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MapTool.h"
#endif

#include "MainFrm.h"
#include "MapToolDoc.h"
#include "MapToolView.h"
#include "CForm.h"
#include "EditorCamera.h"
#include "INIManager.h"
#include "Terrain.h"
#include "CubeObject.h"
#include "Quad.h"
#include "Texture.h"
#include "MeshRenderer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapToolView
HWND g_hWnd;
IMPLEMENT_DYNCREATE(CMapToolView, CView)

BEGIN_MESSAGE_MAP(CMapToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMapToolView 생성/소멸

CMapToolView::CMapToolView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
}

CMapToolView::~CMapToolView()
{
}

BOOL CMapToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMapToolView 그리기

void CMapToolView::OnDraw(CDC* /*pDC*/)
{
	CMapToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMapToolView 인쇄

BOOL CMapToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMapToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMapToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMapToolView 진단

#ifdef _DEBUG
void CMapToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMapToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapToolDoc* CMapToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapToolDoc)));
	return (CMapToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMapToolView 메시지 처리기


void CMapToolView::OnInitialUpdate()
{
	//_CrtSetBreakAlloc(613);

	CView::OnInitialUpdate();

	//std::string strTest;
	//strTest = INIMANAGER->LoadDataString("Data/Cube", "Cube0", "filePath");
	//int i = 0;

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	g_hWnd = m_hWnd;
	CMainFrame* pMain = static_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	RECT rcMain = {};
	pMain->GetWindowRect(&rcMain);

	SetRect(&rcMain, 0, 0, rcMain.right - rcMain.left, rcMain.bottom - rcMain.top);
	RECT rcView{};
	GetClientRect(&rcView);

	int iGapX = rcMain.right - rcView.right;
	int iGapY = rcMain.bottom - rcView.bottom;
	pMain->SetWindowPos(nullptr, 0, 0, WINCX + iGapX, WINCY + iGapY, SWP_NOMOVE);

	Scene* pScene = new Scene();
	std::pair<std::string, Scene*> _Scene = std::make_pair("base", pScene);
	m_vecKeyValue.push_back(_Scene);

	g_pGameController = new GameController();

	g_pGameController->Init(g_hWnd, m_vecKeyValue, WINCX, WINCY);
	g_bInitGame = true;

	m_pGraphicDev = D3D9DEVICE->GetDevice();
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	GameObject* pGameObject;
	pGameObject = GameObject::Instantiate();
	pGameObject->AddComponent(new EditorCamera(g_hWnd,10));

	//pGameObject = GameObject::Instantiate();
	//
	//ce::Texture* test = new ce::Texture();

	//test->Init(m_pGraphicDev, "Resource/Tile0.png");
	//Mesh* mesh = new Quad();
	//mesh->Open(m_pGraphicDev);
	//MeshRenderer* mr = new MeshRenderer(m_pGraphicDev, mesh);
	//pGameObject->AddComponent(mr);
	//mr->GetMaterialPTR()->SetTexture(test);

	Mesh* mesh = new FloorTerrain(30, 30, 1.f);
	mesh->Open(m_pGraphicDev);
	MeshRenderer* mr = new MeshRenderer(m_pGraphicDev, mesh);
	pGameObject->AddComponent(mr);

}


void CMapToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMainFrame* pMain = static_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CForm*		pFormView = static_cast<CForm*>(pMain->m_tMainSplitter.GetPane(0, 0));
	MapTab*		pMaptab = pFormView->m_pMapTab;
	CubeTab*	pCubetab = pFormView->m_pCubeTab;

	int TerrainIndex = pFormView->m_pMapTab->m_RoomList.GetCurSel();

	if (TerrainIndex == -1)
	{
		MessageBoxA(nullptr, "룸번호를 선택해야 합니다.", "RoomNumber Error", MB_OK);
		return;
	}

	CTerrain* pTerrainCom = static_cast<CTerrain*>(pMaptab->_vecTerrain[TerrainIndex]->GetComponent(COMPONENT_ID::BEHAVIOUR));
	Transform* pTransform = pMaptab->_vecTerrain[TerrainIndex]->GetTransform();
	D3DXVECTOR3 vPickingPos = PickingOnTerrain(point, pTerrainCom, pTransform, TerrainIndex);

	if (pFormView->m_iTabIndex == 1 && vPickingPos.x != 0 && vPickingPos.z != 0)
	{
		int CubeIndex = pCubetab->_LoadList.GetCurSel();
		CString cstrTextureName = L"Cube";
		CString cstrIndex;
		cstrIndex.Format(_T("%d"), CubeIndex);
		cstrTextureName += cstrIndex;

		auto iter = pCubetab->_mapTex.find(cstrTextureName.GetString());

		if (iter != pCubetab->_mapTex.end())
		{
			GameObject* pGameObject = GameObject::Instantiate();
			Texture* pTex = pCubetab->_mapTex[cstrTextureName.GetString()].second;
			std::string filepath = pCubetab->_mapTex[cstrTextureName.GetString()].first;
			pGameObject->AddComponent(new CubeObject(pTex));
			pGameObject->GetTransform()->SetWorldPosition(vPickingPos);

			_vecCube.emplace_back(std::make_pair(pGameObject,std::make_pair(filepath, TerrainIndex)));
		}
		else
			return;
	}
}

D3DXVECTOR3 CMapToolView::PickingOnTerrain(CPoint point, CTerrain* pTerrainCom,Transform* pTransform,const int& iIndx)
{
	CMainFrame* pMain = static_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CForm* pFormView = static_cast<CForm*>(pMain->m_tMainSplitter.GetPane(0, 0));
	CubeTab* pCubeTab = pFormView->m_pCubeTab;

	//-----------------------------------------------------------------//
	D3DVIEWPORT9		ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));

	D3DXVECTOR3 vMousePos;
	D3D9DEVICE->GetDevice()->GetViewport(&ViewPort);

	vMousePos.x =(point.x) / (ViewPort.Width * 0.5f) - 1.f;
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
	matWorld = pTransform->GetWorldMatrix();
	D3DXMatrixInverse(&matWorld, NULL, &matWorld);
	
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matWorld);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matWorld);

	DWORD VtxX = pTerrainCom->Get_VtxCntX();
	DWORD VtxZ = pTerrainCom->Get_VtxCntZ();

	const D3DXVECTOR3* pTerrainVtxPos = pTerrainCom->Get_VtxPos();

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

			if (D3DXIntersectTri(&pTerrainVtxPos[dwVtxIndx[1]], &pTerrainVtxPos[dwVtxIndx[0]], &pTerrainVtxPos[dwVtxIndx[2]]
								, &vRayPos, &vRayDir, &fU, &fV, &fDist))
			{
	/*			return D3DXVECTOR3(pTerrainVtxPos[dwVtxIndx[1]].x + (pTerrainVtxPos[dwVtxIndx[0]].x - pTerrainVtxPos[dwVtxIndx[1]].x) * fU
					, 0.f
					, pTerrainVtxPos[dwVtxIndx[1]].z + (pTerrainVtxPos[dwVtxIndx[2]].z - pTerrainVtxPos[dwVtxIndx[1]].z) * fV);*/

				int iFloor = pCubeTab->iFloor;

				return D3DXVECTOR3((pTerrainVtxPos[dwVtxIndx[0]].x + pTerrainVtxPos[dwVtxIndx[2]].x) * 0.5f
					, ((float)iFloor - 0.5f)
					, (pTerrainVtxPos[dwVtxIndx[2]].z + pTerrainVtxPos[dwVtxIndx[1]].z) * 0.5f);
			}

			dwVtxIndx[0] = dwIndex + VtxX;
			dwVtxIndx[1] = dwIndex + 1;
			dwVtxIndx[2] = dwIndex;

			if (D3DXIntersectTri(&pTerrainVtxPos[dwVtxIndx[2]], &pTerrainVtxPos[dwVtxIndx[1]], &pTerrainVtxPos[dwVtxIndx[0]]
				, &vRayPos, &vRayDir, &fU, &fV, &fDist))
			{
				//return D3DXVECTOR3(pTerrainVtxPos[dwVtxIndx[2]].x + (pTerrainVtxPos[dwVtxIndx[1]].x - pTerrainVtxPos[dwVtxIndx[2]].x) * fU
				//					, 0.f
				//					, pTerrainVtxPos[dwVtxIndx[2]].z + (pTerrainVtxPos[dwVtxIndx[0]].z - pTerrainVtxPos[dwVtxIndx[1]].z) * fV);

				int iFloor = pCubeTab->iFloor;

				return D3DXVECTOR3((pTerrainVtxPos[dwVtxIndx[0]].x + pTerrainVtxPos[dwVtxIndx[1]].x) * 0.5f
									, ((float)iFloor - 0.5f)
									, (pTerrainVtxPos[dwVtxIndx[0]].z + pTerrainVtxPos[dwVtxIndx[2]].z) * 0.5f);
			}
		}
	}
	return D3DXVECTOR3(0.f,0.f,0.f);
}

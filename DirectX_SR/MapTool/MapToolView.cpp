
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
#include "Input.h"
#include "ObjectTab.h"

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
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
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

	GameObject* pGameObject;

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

	pGameObject = GameObject::Instantiate();
	pGameObject->AddComponent(new EditorCamera(g_hWnd,2));
}


void CMapToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// 큐브 피킹----------------------------------------------------------------//
	CMainFrame* pMain = static_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CForm*		pFormView = static_cast<CForm*>(pMain->m_tMainSplitter.GetPane(0, 0));
	CubeTab*	pCubetab = pFormView->m_pCubeTab;
	ObjectTab*	pObjtab = pFormView->m_pObjectTab;

	D3DXVECTOR3 vPickingPos = static_cast<FloorTerrain*>(_mesh)->Get_PickingPos();

	if (pFormView->m_iTabIndex == 1)
	{
		// Cube Picking
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

			_vecCube.emplace_back(pGameObject, filepath);
		}
	}
	else if (pFormView->m_iTabIndex == 2)
	{
		// Object Picking

		GameObject* pGameObject = GameObject::Instantiate();
		Texture* pTex = new Texture();
		pTex->Init(D3D9DEVICE->GetDevice(), "Resource/Tile1.png");

		std::string strSavename = CT2CA(pObjtab->_cstrKey);
		
		int icnt = pObjtab->_vecSaveName.size();

		if (strcmp("", strSavename.c_str()) == 0)
		{
			MessageBoxA(nullptr, "섹션키가 입력되있지 않습니다.", "Picking Err", MB_OK);
			return;
		}

		for (int i = 0; i < icnt; ++i)
		{
			if (strcmp(strSavename.c_str(), pObjtab->_vecSaveName[i].first.c_str()) == 0)
			{
				CString cstr;
				cstr.Format(_T("%d"), (_iETC + 1));

				UpdateData(TRUE);
				strSavename = CT2CA(pObjtab->_cstrKey + cstr);
				UpdateData(FALSE);
				_iETC++;
			}
		}
		Mesh* mesh = new Quad();
		mesh->Open(D3D9DEVICE->GetDevice());
		MeshRenderer* mr = new MeshRenderer(D3D9DEVICE->GetDevice(), mesh);
		mr->GetMaterialPTR()->SetTexture(pTex);
		pGameObject->GetTransform()->SetWorldPosition(vPickingPos);
		pGameObject->GetTransform()->Translate(0.f, 0.5f, 0.f);
		pGameObject->AddComponent(mr);
		pObjtab->_vecSaveName.emplace_back(std::make_pair(strSavename, std::make_pair(pGameObject, pTex)));
	}
	else
	{
		// Terrain Splatting 
		static_cast<FloorTerrain*>(_mesh)->SetClicked(TRUE);
	}

}

void CMapToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	g_MousePos = point;

	Invalidate(FALSE);
	//CView::OnMouseMove(nFlags, point);
}

void CMapToolView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if(_mesh != nullptr)
		static_cast<FloorTerrain*>(_mesh)->SetClicked(FALSE);

	CView::OnLButtonUp(nFlags, point);
}


void CMapToolView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (INPUT->GetKeyDown('Z') || INPUT->GetKeyDown('z'))
	{
		float BrushSize = static_cast<FloorTerrain*>(_mesh)->GetBrushSize();
		float SmoothSize = static_cast<FloorTerrain*>(_mesh)->GetSmoothSize();
		BrushSize -= 1.0f;
		static_cast<FloorTerrain*>(_mesh)->SetBrushSize(BrushSize);
		if (1.0f > BrushSize)
			static_cast<FloorTerrain*>(_mesh)->SetBrushSize(1.0f);

		if (BrushSize < SmoothSize)
			static_cast<FloorTerrain*>(_mesh)->SetBrushSize(SmoothSize);
	}

	if (INPUT->GetKeyDown('X') || INPUT->GetKeyDown('X'))
	{
		float BrushSize = static_cast<FloorTerrain*>(_mesh)->GetBrushSize();
		BrushSize += 1.0f;
		static_cast<FloorTerrain*>(_mesh)->SetBrushSize(BrushSize);
		if (5.0f < BrushSize)
			static_cast<FloorTerrain*>(_mesh)->SetBrushSize(5.0f);
	}

	if (INPUT->GetKeyDown('1'))
	{
		static_cast<FloorTerrain*>(_mesh)->SetCurSelIndex(0);
		for (int i = 0; i < MAXTEXNUM; ++i)
		{
			int* pIndex = static_cast<FloorTerrain*>(_mesh)->GetDrawIndex();

			if (i > 0 && static_cast<FloorTerrain*>(_mesh)->GetCurSelIndex() == pIndex[i])
			{
				int nTemp = pIndex[i];
				pIndex[i] = pIndex[i - 1];
				pIndex[i - 1] = nTemp;
				break;
			}
		}
	}
	if (INPUT->GetKeyDown('2'))
	{
		static_cast<FloorTerrain*>(_mesh)->SetCurSelIndex(1);
		for (int i = 0; i < MAXTEXNUM; ++i)
		{
			int* pIndex = static_cast<FloorTerrain*>(_mesh)->GetDrawIndex();

			if (i > 0 && static_cast<FloorTerrain*>(_mesh)->GetCurSelIndex() == pIndex[i])
			{
				int nTemp = pIndex[i];
				pIndex[i] = pIndex[i - 1];
				pIndex[i - 1] = nTemp;
				break;
			}
		}
	}
	if (INPUT->GetKeyDown('3'))
	{
		static_cast<FloorTerrain*>(_mesh)->SetCurSelIndex(2);
		for (int i = 0; i < MAXTEXNUM; ++i)
		{
			int* pIndex = static_cast<FloorTerrain*>(_mesh)->GetDrawIndex();

			if (i > 0 && static_cast<FloorTerrain*>(_mesh)->GetCurSelIndex() == pIndex[i])
			{
				int nTemp = pIndex[i];
				pIndex[i] = pIndex[i - 1];
				pIndex[i - 1] = nTemp;
				break;
			}
		}
	}
	if (INPUT->GetKeyDown('4'))
	{
		static_cast<FloorTerrain*>(_mesh)->SetCurSelIndex(3);
		for (int i = 0; i < MAXTEXNUM; ++i)
		{
			int* pIndex = static_cast<FloorTerrain*>(_mesh)->GetDrawIndex();

			if (i > 0 && static_cast<FloorTerrain*>(_mesh)->GetCurSelIndex() == pIndex[i])
			{
				int nTemp = pIndex[i];
				pIndex[i] = pIndex[i - 1];
				pIndex[i - 1] = nTemp;
				break;
			}
		}
	}


	Invalidate(false);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

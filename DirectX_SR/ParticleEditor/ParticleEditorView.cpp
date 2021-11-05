
// ParticleEditorView.cpp: CParticleEditorView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ParticleEditor.h"
#endif

#include "ParticleEditorDoc.h"
#include "ParticleEditorView.h"

#include "ToolScene.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CParticleEditorView

IMPLEMENT_DYNCREATE(CParticleEditorView, CView)

BEGIN_MESSAGE_MAP(CParticleEditorView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CParticleEditorView 생성/소멸

CParticleEditorView::CParticleEditorView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CParticleEditorView::~CParticleEditorView()
{
	g_pGameCtrl->Release();
}

BOOL CParticleEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CParticleEditorView 그리기

void CParticleEditorView::OnDraw(CDC* /*pDC*/)
{
	CParticleEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CParticleEditorView 인쇄

BOOL CParticleEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CParticleEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CParticleEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CParticleEditorView 진단

#ifdef _DEBUG
void CParticleEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CParticleEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CParticleEditorDoc* CParticleEditorView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CParticleEditorDoc)));
	return (CParticleEditorDoc*)m_pDocument;
}
#endif //_DEBUG

// CParticleEditorView 메시지 처리기

HWND g_hWnd;
GameController* g_pGameCtrl;
void CParticleEditorView::OnInitialUpdate()
{
//	CView::OnInitialUpdate();

	g_hWnd = m_hWnd;

	g_pGameCtrl = new GameController();

	std::vector<std::pair<std::string, Scene*>> scenes;
	scenes.push_back(std::pair("Tool", new ToolScene()));

	g_pGameCtrl->Init(g_hWnd, scenes, WINCX, WINCY);
}

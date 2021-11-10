// CForm.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "CForm.h"


// CForm

IMPLEMENT_DYNCREATE(CForm, CFormView)

CForm::CForm()
	: CFormView(IDD_Form)
{

}

CForm::~CForm()
{
	Safe_Delete(m_pMapTab);
	Safe_Delete(m_pObjectTab);
	Safe_Delete(m_pCubeTab);
}

void CForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabBox);
}

BEGIN_MESSAGE_MAP(CForm, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CForm::OnTcnSelchangeTab)
END_MESSAGE_MAP()


// CForm 진단

#ifdef _DEBUG
void CForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CForm 메시지 처리기

void CForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	SetScrollSizes(MM_TEXT, CSize(0, 0));

	m_TabBox.DeleteAllItems();

	m_TabBox.InsertItem(0, L"Map");
	m_TabBox.InsertItem(1, L"Cube");
	m_TabBox.InsertItem(2, L"Object");

	CRect temp_rect;
	m_TabBox.GetClientRect(&temp_rect);

	m_pMapTab = new MapTab;
	m_pMapTab->Create(IDD_MapTab, &m_TabBox);
	m_pMapTab->MoveWindow(5, 25, temp_rect.Width(), temp_rect.Height());
	m_pMapTab->ShowWindow(SW_SHOW);

	m_pCubeTab = new CubeTab;
	m_pCubeTab->Create(IDD_CubeTab, &m_TabBox);
	m_pCubeTab->MoveWindow(5, 25, temp_rect.Width(), temp_rect.Height());
	m_pCubeTab->ShowWindow(SW_HIDE);

	m_pObjectTab = new ObjectTab;
	m_pObjectTab->Create(IDD_ObjectTab, &m_TabBox);
	m_pObjectTab->MoveWindow(5, 25, temp_rect.Width(), temp_rect.Height());
	m_pObjectTab->ShowWindow(SW_HIDE);

	Invalidate(FALSE);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CForm::OnTcnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_iTabIndex = m_TabBox.GetCurSel();
	switch (m_iTabIndex)
	{
	case 0:
		m_pMapTab->ShowWindow(SW_SHOW);
		m_pObjectTab->ShowWindow(SW_HIDE);
		m_pCubeTab->ShowWindow(SW_HIDE);
		break;
	case 1:
		m_pMapTab->ShowWindow(SW_HIDE);
		m_pCubeTab->ShowWindow(SW_SHOW);
		m_pObjectTab->ShowWindow(SW_HIDE);
		break;
	case 2:
		m_pMapTab->ShowWindow(SW_HIDE);
		m_pCubeTab->ShowWindow(SW_HIDE);
		m_pObjectTab->ShowWindow(SW_SHOW);
		break;
	}

	*pResult = 0;
}

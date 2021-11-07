// ConeForm.cpp: 구현 파일
//

#include "pch.h"
#include "ParticleEditor.h"
#include "ConeForm.h"
#include "ParticleForm.h"
#include "BillBordParticle.h"
// ConeForm

IMPLEMENT_DYNCREATE(ConeForm, CFormView)

ConeForm::ConeForm()
	: CFormView(IDD_ConeForm)
	, _strRadius(_T("1"))
	, _strAngle(_T("25"))
{

}

ConeForm::~ConeForm()
{
}

void ConeForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RADIUS, _strRadius);
	DDX_Text(pDX, IDC_EDIT_ANGLE, _strAngle);
}

BEGIN_MESSAGE_MAP(ConeForm, CFormView)
	ON_EN_CHANGE(IDC_EDIT_RADIUS, &ConeForm::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_ANGLE, &ConeForm::OnEnChangeEdit)
END_MESSAGE_MAP()


// ConeForm 진단

#ifdef _DEBUG
void ConeForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void ConeForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// ConeForm 메시지 처리기

BOOL ConeForm::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void ConeForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	_pParticle = (static_cast<CParticleForm*>(GetParent()))->GetParticle();
}


void ConeForm::OnEnChangeEdit()
{
	UpdateData(TRUE);
	_pParticle->SetRadius(_ttof(_strRadius));
	_pParticle->SetAngle(_ttof(_strAngle));
}

void ConeForm::SetOption(float radius, float angle)
{
	_strRadius.Format(_T("%.1f"), radius);
	_strAngle.Format(_T("%.1f"), angle);
	UpdateData(FALSE);
}

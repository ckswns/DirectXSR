// SphereForm.cpp: 구현 파일
//

#include "pch.h"
#include "ParticleEditor.h"
#include "SphereForm.h"
#include "ParticleForm.h"
#include "BillBordParticle.h"
// SphereForm

IMPLEMENT_DYNCREATE(SphereForm, CFormView)

SphereForm::SphereForm()
	: CFormView(IDD_SphereForm)
	, _strRadius(_T("1"))
{

}

SphereForm::~SphereForm()
{
}

void SphereForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RADIUS, _strRadius);
}

BEGIN_MESSAGE_MAP(SphereForm, CFormView)
	ON_EN_CHANGE(IDC_EDIT_RADIUS, &SphereForm::OnEnChangeEditRadius)
END_MESSAGE_MAP()


// SphereForm 진단

#ifdef _DEBUG
void SphereForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void SphereForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// SphereForm 메시지 처리기


BOOL SphereForm::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void SphereForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	_pParticle = (static_cast<CParticleForm*>(GetParent()))->GetParticle();
}


void SphereForm::OnEnChangeEditRadius()
{
	UpdateData(TRUE);
	_pParticle->SetRadius(_ttof(_strRadius));
}

void SphereForm::SetRadius(float radius)
{
	_strRadius.Format(_T("%.1f"), radius);
	UpdateData(FALSE);
}

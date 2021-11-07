// BoxForm.cpp: 구현 파일
//

#include "pch.h"
#include "ParticleEditor.h"
#include "BoxForm.h"
#include "ParticleForm.h"

// BoxForm

IMPLEMENT_DYNCREATE(BoxForm, CFormView)

BoxForm::BoxForm()
	: CFormView(IDD_BoxForm)
	, _strX(_T("1"))
	, _strY(_T("1"))
	, _strZ(_T("1"))
{

}

BoxForm::~BoxForm()
{
}

void BoxForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, _strX);
	DDX_Text(pDX, IDC_EDIT_Y, _strY);
	DDX_Text(pDX, IDC_EDIT_Z, _strZ);
}

BEGIN_MESSAGE_MAP(BoxForm, CFormView)
	ON_EN_CHANGE(IDC_EDIT_X, &BoxForm::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_Y, &BoxForm::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_Z, &BoxForm::OnEnChangeEdit)
END_MESSAGE_MAP()


// BoxForm 진단

#ifdef _DEBUG
void BoxForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void BoxForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// BoxForm 메시지 처리기


BOOL BoxForm::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void BoxForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	_pParticle = (static_cast<CParticleForm*>(GetParent()))->GetParticle();

}


void BoxForm::OnEnChangeEdit()
{
	UpdateData(TRUE);
	_pParticle->SetBoxSize(Vector3(_ttof(_strX), _ttof(_strY), _ttof(_strZ)));
}

void BoxForm::SetBoxSize(float x, float y, float z)
{
	_strX.Format(_T("%.1f"), x);
	_strY.Format(_T("%.1f"), y);
	_strZ.Format(_T("%.1f"), z);

	UpdateData(FALSE);
}

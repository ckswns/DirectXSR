// ParticleForm.cpp: 구현 파일
//

#include "pch.h"
#include "ParticleEditor.h"
#include "ParticleForm.h"


// CParticleForm

IMPLEMENT_DYNCREATE(CParticleForm, CFormView)

CParticleForm::CParticleForm()
	: CFormView(IDD_ParticleForm)
{

}

CParticleForm::~CParticleForm()
{
}

void CParticleForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CParticleForm, CFormView)
END_MESSAGE_MAP()


// CParticleForm 진단

#ifdef _DEBUG
void CParticleForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CParticleForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CParticleForm 메시지 처리기

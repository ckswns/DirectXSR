#pragma once

// CParticleForm 폼 보기

class CParticleForm : public CFormView
{
	DECLARE_DYNCREATE(CParticleForm)

protected:										CParticleForm();           
protected:			virtual					~CParticleForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ParticleForm };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:			virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

protected:										DECLARE_MESSAGE_MAP()
};



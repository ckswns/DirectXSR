#pragma once

// BoxForm 폼 보기
#include "BillBordParticle.h"

class BoxForm : public CFormView
{
	DECLARE_DYNCREATE(BoxForm)

public:	BoxForm();
protected:
	virtual ~BoxForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BoxForm };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
public:	virtual void OnInitialUpdate();
public:	afx_msg void OnEnChangeEdit();

private:	CString _strX;
private:	CString _strY;
private:	CString _strZ;


private:	BillBordParticle* _pParticle;
};



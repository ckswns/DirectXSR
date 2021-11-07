#pragma once

// SphereForm 폼 보기

class BillBordParticle;
class SphereForm : public CFormView
{
	DECLARE_DYNCREATE(SphereForm)


public:	SphereForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
protected:	virtual ~SphereForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SphereForm };
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
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();

private:	BillBordParticle* _pParticle;
public:
	CString _strRadius;
	afx_msg void OnEnChangeEditRadius();
};



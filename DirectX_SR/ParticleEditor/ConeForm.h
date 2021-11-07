#pragma once

// ConeForm 폼 보기
class BillBordParticle;
class ConeForm : public CFormView
{
	DECLARE_DYNCREATE(ConeForm)


public:	ConeForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
protected:	virtual ~ConeForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ConeForm };
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

private:	BillBordParticle* _pParticle;


public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
	CString _strRadius;
	CString _strAngle;
	afx_msg void OnEnChangeEdit();
};



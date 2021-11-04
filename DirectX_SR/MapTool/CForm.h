#pragma once



// CForm 폼 보기

#include "MapTab.h"
#include "ObjectTab.h"
#include "CubeTab.h"

class CForm : public CFormView
{
	DECLARE_DYNCREATE(CForm)

protected:
	CForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Form };
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
	CTabCtrl	m_TabBox;
	MapTab*		m_pMapTab;
	ObjectTab*	m_pObjectTab;
	CubeTab*	m_pCubeTab;
	int			m_iTabIndex;

	virtual void OnInitialUpdate();
	afx_msg void OnTcnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
};



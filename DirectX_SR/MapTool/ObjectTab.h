#pragma once


// ObjectTab 대화 상자

class ObjectTab : public CDialog
{
	DECLARE_DYNAMIC(ObjectTab)

public:
	ObjectTab(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ObjectTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ObjectTab1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};

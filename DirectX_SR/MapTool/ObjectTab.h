#pragma once


// ObjectTab 대화 상자
#include "GameObject.h"
#include "Texture.h"

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
public:

	std::vector<std::pair<std::string,std::pair<GameObject*, Texture*>>> _vecSaveName;

	afx_msg void OnBnClickedPositionSave();
	afx_msg void OnBnClickedPositionLoad();
	CListBox _PickingList;

	CString _cstrKey;
	afx_msg void OnEnChangekey();


private: std::vector<std::string> Split(std::string input, char delimiter);
};

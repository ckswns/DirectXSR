#pragma once

#include "Texture.h"

// CubeTab 대화 상자

class CubeTab : public CDialog
{
	DECLARE_DYNAMIC(CubeTab)

public:
	CubeTab(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CubeTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CubeTab };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCreateCube();
	afx_msg void OnBnClickedDataSave();
	afx_msg void OnBnClickedDataLoad();
	float _fScaleX;
	float _fScaleY;
	float _fScaleZ;
	afx_msg void OnBnClickedScaleApply();

	GameObject*					_pGameObject;
	std::vector<GameObject*>	_vecObject;

	afx_msg void OnBnClickedScaleReset();
	CListBox _SaveList;
	CListBox _LoadList;
	CListBox _TextureList;

	uint8	_CubeNumber;
	afx_msg void OnBnClickedLoadTextureList();
	std::string		_strFilePath;
	std::map<std::wstring, std::pair<std::string, Texture*>> _mapTex;
	afx_msg void OnLbnSelchangeTextureSelect();
	Texture* _pTexture;
	afx_msg void OnLbnSelchangeSelectLoadObject();
};

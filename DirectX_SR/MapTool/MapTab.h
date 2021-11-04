#pragma once


// MapTab 대화 상자
#include "GameObject.h"
#include "TerrainTex.h"

class MapTab : public CDialog
{
	DECLARE_DYNAMIC(MapTab)

public:
	MapTab(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MapTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MapTab };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	DWORD	m_dwVtxZ;
	DWORD	m_dwVtxX;
	float	m_dwIntvX;
	float	m_dwIntvZ;
	DWORD	m_dwRoomNumber;
	CListBox m_RoomList;
	afx_msg void OnBnClickedCreateTerrain();
	afx_msg void OnBnClickedDeleteTerrain();

	std::unordered_map<DWORD, GameObject*>	m_mapTerrain;
	
	DWORD	m_dwLastNumber;
	DWORD	m_dwSelectNumber;

	void		Release();
};

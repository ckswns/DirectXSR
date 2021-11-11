#pragma once


// MapTab 대화 상자
#include "GameObject.h"
#include "TerrainTex.h"
#include "Texture.h"
#include "FloorTerrain.h"

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
	DWORD	m_dwRoomNumber;
	CListBox m_RoomList;
	afx_msg void OnBnClickedCreateTerrain();
	afx_msg void OnBnClickedDeleteTerrain();
	
	DWORD	m_dwLastNumber;
	DWORD	m_dwSelectNumber;

	std::string _strfilepath;

	void		Release();
	afx_msg void OnBnClickedTerrainTextureLoad();
	/*CListBox _TextureList;*/

	std::map<std::wstring, std::pair<std::string, Texture*>> _mapTex;

	std::vector<Texture*> _vecTex;
	afx_msg void OnLbnSelchangeSelectTexutrePath();

	//CEdit _EditMoveX;
	//CEdit _EditMoveZ;
	//CSpinButtonCtrl _SpinControlX;
	//CSpinButtonCtrl _SpinControlZ;
	/*virtual BOOL OnInitDialog();*/
	//afx_msg void OnDeltaposMoveTerrainX(NMHDR* pNMHDR, LRESULT* pResult);
	//afx_msg void OnDeltaposTerrainMoveZ(NMHDR* pNMHDR, LRESULT* pResult);

	//std::vector<std::pair<Texture*,GameObject*>>	_vecTerrain;
	/*std::vector<GameObject*>	_vecTerrain;*/
	std::vector<Mesh*>			_vecTerrain;
	int	_iIndex;

	int	_iMoveX;
	int	_iMoveZ;
	afx_msg void OnBnClickedSaveTerrain();
	afx_msg void OnBnClickedLoadTerrain();
	afx_msg void OnBnClickedAllFileLoad();
	afx_msg void OnBnClickedAllFileSave();
};

// MapTab.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "MapTab.h"
#include "afxdialogex.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "INIManager.h"
// MapTab 대화 상자

IMPLEMENT_DYNAMIC(MapTab, CDialog)

MapTab::MapTab(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MapTab, pParent)
	, m_dwVtxZ(0)
	, m_dwVtxX(0)
	, m_dwRoomNumber(0)
	, m_dwLastNumber(0), m_dwSelectNumber(0)
{
}

MapTab::~MapTab()
{
	Release();
}

void MapTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_dwVtxX);
	DDX_Text(pDX, IDC_EDIT2, m_dwVtxZ);
	DDX_Text(pDX, IDC_EDIT5, m_dwRoomNumber);
	DDX_Control(pDX, IDC_LIST1, m_RoomList);
	DDX_Control(pDX, IDC_LIST2, _TextureList);
	DDX_Control(pDX, IDC_EDIT3, _EditMoveX);
	DDX_Control(pDX, IDC_EDIT4, _EditMoveZ);
	DDX_Control(pDX, IDC_SPIN3, _SpinControlX);
	DDX_Control(pDX, IDC_SPIN2, _SpinControlZ);
}


BEGIN_MESSAGE_MAP(MapTab, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &MapTab::OnBnClickedCreateTerrain)
	ON_BN_CLICKED(IDC_BUTTON3, &MapTab::OnBnClickedDeleteTerrain)
	ON_BN_CLICKED(IDC_BUTTON1, &MapTab::OnBnClickedTerrainTextureLoad)
	ON_LBN_SELCHANGE(IDC_LIST2, &MapTab::OnLbnSelchangeSelectTexutrePath)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &MapTab::OnDeltaposMoveTerrainX)

	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &MapTab::OnDeltaposTerrainMoveZ)
	ON_BN_CLICKED(IDC_BUTTON4, &MapTab::OnBnClickedSaveTerrain)
	ON_BN_CLICKED(IDC_BUTTON7, &MapTab::OnBnClickedLoadTerrain)
	ON_LBN_SELCHANGE(IDC_LIST1, &MapTab::OnLbnSelchangeList1)
END_MESSAGE_MAP()


// MapTab 메시지 처리기

// SpinControl 초기값 셋팅
BOOL MapTab::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	_EditMoveX.SetWindowText(_T("0"));
	_EditMoveZ.SetWindowText(_T("0"));

	_SpinControlX.SetRange(-100, 100);
	_SpinControlX.SetPos(0);

	_SpinControlZ.SetRange(-100, 100);
	_SpinControlZ.SetPos(0);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void MapTab::Release()
{
	if (_mapTex.empty() == false)
	{
		for (auto iter = _mapTex.begin(); iter != _mapTex.end(); iter++)
		{
			if ((iter->second).second != nullptr)
				delete (iter->second).second;
		}
		_mapTex.clear();
	}

	//if (!_vecTerrain.empty())
	//{
	//	for (auto iter = _vecTerrain.begin(); iter != _vecTerrain.end(); iter++)
	//	{
	//		if (iter->first != nullptr)
	//			delete iter->first;
	//	}
	//	_vecTerrain.clear();
	//}

}

// 지형 생성
void MapTab::OnBnClickedCreateTerrain()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	//if (strcmp("", _strfilepath.c_str()) == 0)
	//{
	//	MessageBoxA(nullptr, "Texture 경로가 없습니다.", "FilePath Error", MB_OK);
	//	return;
	//}
	if (m_dwVtxX == 0 || m_dwVtxZ == 0)
	{
		MessageBoxA(nullptr, "VerTex 설정이 안되있습니다.", "VtxSetting Error", MB_OK);
		return;
	}

	GameObject* pGameObject;
	pGameObject = GameObject::Instantiate();

	//Texture* pTexture = new Texture();
	//pTexture->Init(D3D9DEVICE->GetDevice(), _strfilepath.c_str());
	//pGameObject->AddComponent(new CTerrain(D3D9DEVICE->GetDevice(), m_dwVtxX, m_dwVtxZ, m_dwRoomNumber, pTexture));
	pGameObject->AddComponent(new CTerrain(D3D9DEVICE->GetDevice(), m_dwVtxX, m_dwVtxZ, m_dwRoomNumber));
	m_dwLastNumber++;

	CString strNumber;
	strNumber.Format(_T("%d"), m_dwRoomNumber);
	m_RoomList.AddString(strNumber);

	//_vecTerrain.push_back(std::make_pair(nullptr,pGameObject));
	_vecTerrain.emplace_back(pGameObject);

	m_dwRoomNumber++;

	UpdateData(FALSE);
}

// 지형 목록 삭제
void MapTab::OnBnClickedDeleteTerrain()
{
	// TODO: 
}

// 지형 Texture File 불러오기
void MapTab::OnBnClickedTerrainTextureLoad()
{
	// TODO: Load Texture list

	_TextureList.ResetContent();

	if (_mapTex.empty() == false)
	{
		for (auto iter = _mapTex.begin(); iter != _mapTex.end(); iter++)
		{
			if ((iter->second).second != nullptr)
				delete (iter->second).second;
		}
		_mapTex.clear();
	}

	char szCurrentPath[MAX_PATH] = {};
	GetCurrentDirectoryA(MAX_PATH, szCurrentPath);
	std::string currPath = szCurrentPath;
	currPath += "/Resource";

	for (auto& entry : fs::directory_iterator(currPath))
	{
		if (entry.is_directory())
			continue;

		std::string filePath = entry.path().u8string();
		size_t split = filePath.find('.');
		std::string fileExtension = filePath.substr(split);

		if (fileExtension == ".jpg" || fileExtension == ".png")
		{
			split = filePath.find_last_of('\\');
			std::string tempStr = filePath.substr(split + 1);

			std::wstring temp;
			temp.assign(tempStr.begin(), tempStr.end());

			_TextureList.AddString(temp.c_str());

			std::string RealFilePath;
			split = filePath.find('/');

			RealFilePath = filePath.substr(split);
			split = RealFilePath.find('R');
			RealFilePath = RealFilePath.substr(split);

			Texture* tex = new Texture();
			tex->Init(D3D9DEVICE->GetDevice(), RealFilePath.c_str());

			_mapTex.insert(std::make_pair(temp, std::make_pair(RealFilePath, tex)));
		}
	}
}

// 지형 Texture 선택하기
void MapTab::OnLbnSelchangeSelectTexutrePath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int iIndexTexture = _TextureList.GetCurSel();

	int iIndexTerrain = m_RoomList.GetCurSel();

	if (iIndexTerrain == -1)
		return;

	CString cstrTextureName;
	_TextureList.GetText(iIndexTexture, cstrTextureName);

	auto iter = _mapTex.find(cstrTextureName.GetString());

	if (iter != _mapTex.end())
	{
		_strfilepath = _mapTex[cstrTextureName.GetString()].first;
		Texture* tex = _mapTex[cstrTextureName.GetString()].second;

		if (_vecTerrain[iIndexTerrain] != nullptr)
		{
			static_cast<CTerrain*>(_vecTerrain[iIndexTerrain]->GetComponent(COMPONENT_ID::BEHAVIOUR))->Set_Textureinfo(tex,_strfilepath);
		}
	}
}

// 지형 이동 X 방향 컨트롤러
void MapTab::OnDeltaposMoveTerrainX(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	int iIndex = m_RoomList.GetCurSel();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	_iMoveX = pNMUpDown->iPos + pNMUpDown->iDelta;

	if (-100 < _iMoveX && 100 > _iMoveX)
	{
		if (iIndex == -1)
			iIndex = 0;

		CString cstrValue;
		cstrValue.Format(_T("%d"), _iMoveX);
		_EditMoveX.SetWindowText(cstrValue);

		static_cast<CTerrain*>(_vecTerrain[iIndex]->GetComponent(COMPONENT_ID::BEHAVIOUR))->Set_MoveCheck();
	}
	*pResult = 0;
}

// 지형 이동 Z 방향 컨트롤러
void MapTab::OnDeltaposTerrainMoveZ(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	_iMoveZ = pNMUpDown->iPos + pNMUpDown->iDelta;

	if ((-100 < _iMoveZ) && (100 > _iMoveZ))
	{
		int iIndex = m_RoomList.GetCurSel();

		if (iIndex == -1)
			iIndex = 0;

		CString cstrValue;
		cstrValue.Format(_T("%d"), _iMoveZ);
		_EditMoveZ.SetWindowText(cstrValue);

		static_cast<CTerrain*>(_vecTerrain[iIndex]->GetComponent(COMPONENT_ID::BEHAVIOUR))->Set_MoveCheck();
	}
	*pResult = 0;
}


// 저장
void MapTab::OnBnClickedSaveTerrain()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iSectionNumber = 0;

	size_t objectsize = _vecTerrain.size();
	std::string	strobjectsize;
	strobjectsize = (std::to_string(objectsize));
	INIMANAGER->AddData("Start", "objectsize", strobjectsize);

	for (size_t t = 0; t < objectsize; t++)
	{
		CString strNumber;
		strNumber.Format(_T("%d"), iSectionNumber);
		CString cstrSection = L"Terrain";
		cstrSection += strNumber;
		std::string strSection;
		strSection = CT2CA(cstrSection);

		std::string	strVtxX;
		strVtxX = (std::to_string(static_cast<CTerrain*>(_vecTerrain[t]->GetComponent(COMPONENT_ID::BEHAVIOUR))->Get_VtxCntX()));
		INIMANAGER->AddData(strSection, "VertxX", strVtxX);

		std::string	strVtxZ;
		strVtxZ = (std::to_string(static_cast<CTerrain*>(_vecTerrain[t]->GetComponent(COMPONENT_ID::BEHAVIOUR))->Get_VtxCntZ()));
		INIMANAGER->AddData(strSection, "VertxZ", strVtxZ);

		std::string strRoomnumber;
		strRoomnumber = (std::to_string(static_cast<CTerrain*>(_vecTerrain[t]->GetComponent(COMPONENT_ID::BEHAVIOUR))->Get_RoomNumber()));
		INIMANAGER->AddData(strSection, "RoomNumber", strRoomnumber);

		std::string	strMoveX;
		strMoveX = (std::to_string(static_cast<CTerrain*>(_vecTerrain[t]->GetComponent(COMPONENT_ID::BEHAVIOUR))->Get_CurrtMovePosX()));
		INIMANAGER->AddData(strSection, "MoveX", strMoveX);

		std::string strMoveZ;
		strMoveZ = (std::to_string(static_cast<CTerrain*>(_vecTerrain[t]->GetComponent(COMPONENT_ID::BEHAVIOUR))->Get_CurrtMovePosZ()));
		INIMANAGER->AddData(strSection, "MoveZ", strMoveZ);
		INIMANAGER->AddData(strSection, "filepath", static_cast<CTerrain*>(_vecTerrain[t]->GetComponent(COMPONENT_ID::BEHAVIOUR))->Get_Filepath());
		iSectionNumber++;
	}
	INIMANAGER->SaveIni("Data/Terrain");
	MessageBoxA(nullptr, "저장 성공", "Success", MB_OK);
}


void MapTab::OnBnClickedLoadTerrain()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//if (_vecTerrain.empty() == false)
	//{
	//	for (size_t t = 0; t < _vecTerrain.size(); t++)
	//	{
	//		_vecTerrain[t]->GetComponent(COMPONENT_ID::BEHAVIOUR);
	//	}
	//}
	if (!_vecTerrain.empty())
	{
		MessageBoxA(nullptr, "Load 할 수 없습니다.", "Load Failed", MB_OK);
		return;
	}

	int iSectionNumber = 0;
	int iObjectSize = 0;
	std::string strobjectsize;
	strobjectsize = INIMANAGER->LoadDataString("Data/Terrain", "Start", "objectsize");
	iObjectSize = stoi(strobjectsize);
	
	std::string strSection = "Terrain";
	std::string strVtxX;
	std::string strVtxZ;
	std::string strRoomNumber;
	std::string strMoveX;
	std::string strMoveZ;
	std::string strfilepath;

	for (int i = 0; i < iObjectSize; i++)
	{
		std::string strSection = "Terrain";
		strSection += std::to_string(i);
		strVtxX = INIMANAGER->LoadDataString("Data/Terrain", strSection, "VertxX");
		strVtxZ = INIMANAGER->LoadDataString("Data/Terrain", strSection, "VertxZ");
		strRoomNumber = INIMANAGER->LoadDataString("Data/Terrain", strSection, "RoomNumber");
		strMoveX = INIMANAGER->LoadDataString("Data/Terrain", strSection, "MoveX");
		strMoveZ = INIMANAGER->LoadDataString("Data/Terrain", strSection, "MoveZ");
		strfilepath = INIMANAGER->LoadDataString("Data/Terrain", strSection, "filepath");
		
		DWORD VtxX = stoul(strVtxX);
		DWORD VtxZ = stoul(strVtxZ);
		DWORD Room = stoul(strRoomNumber);
		int MoveX = stoi(strMoveX);
		int MoveZ = stoi(strMoveZ);

		GameObject* pGameobject = GameObject::Instantiate();
		pGameobject->AddComponent(new CTerrain(D3D9DEVICE->GetDevice(), VtxX, VtxZ, Room, MoveX, _iMoveZ));
		
		Texture* tex = new Texture();
		tex->Init(D3D9DEVICE->GetDevice(), strfilepath.c_str());
		std::wstring temp;
		temp.assign(strRoomNumber.begin(), strRoomNumber.end());
		_mapTex.insert(std::make_pair(temp, std::make_pair(strfilepath, tex)));
		m_RoomList.AddString(temp.c_str());

		static_cast<CTerrain*>(pGameobject->GetComponent(COMPONENT_ID::BEHAVIOUR))->Set_Textureinfo(tex, _strfilepath);
		
		_vecTerrain.emplace_back(pGameobject);
	}
}

void MapTab::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	_iIndex = m_RoomList.GetCurSel();
}

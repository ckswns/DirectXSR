// MapTab.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "MapTab.h"
#include "afxdialogex.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "INIManager.h"
#include "Assertion.h"
#include "MainFrm.h"
#include "MapToolView.h"
#include "CForm.h"

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
	/*DDX_Control(pDX, IDC_LIST2, _TextureList);*/
	//DDX_Control(pDX, IDC_EDIT3, _EditMoveX);
	//DDX_Control(pDX, IDC_EDIT4, _EditMoveZ);
	//DDX_Control(pDX, IDC_SPIN3, _SpinControlX);
	//DDX_Control(pDX, IDC_SPIN2, _SpinControlZ);
}


BEGIN_MESSAGE_MAP(MapTab, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &MapTab::OnBnClickedCreateTerrain)
	ON_BN_CLICKED(IDC_BUTTON3, &MapTab::OnBnClickedDeleteTerrain)
	/*ON_BN_CLICKED(IDC_BUTTON1, &MapTab::OnBnClickedTerrainTextureLoad)
	ON_LBN_SELCHANGE(IDC_LIST2, &MapTab::OnLbnSelchangeSelectTexutrePath)*/
	/*ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &MapTab::OnDeltaposMoveTerrainX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &MapTab::OnDeltaposTerrainMoveZ)*/
	ON_BN_CLICKED(IDC_BUTTON4, &MapTab::OnBnClickedSaveTerrain)
	ON_BN_CLICKED(IDC_BUTTON7, &MapTab::OnBnClickedLoadTerrain)
	ON_BN_CLICKED(IDC_BUTTON9, &MapTab::OnBnClickedAllFileLoad)
	ON_BN_CLICKED(IDC_BUTTON10, &MapTab::OnBnClickedAllFileSave)
END_MESSAGE_MAP()


// MapTab 메시지 처리기

// SpinControl 초기값 셋팅
//BOOL MapTab::OnInitDialog()
//{
//	CDialog::OnInitDialog();
//
//	// TODO:  여기에 추가 초기화 작업을 추가합니다.
//
//	_EditMoveX.SetWindowText(_T("0"));
//	_EditMoveZ.SetWindowText(_T("0"));
//
//	_SpinControlX.SetRange(-100, 100);
//	_SpinControlX.SetPos(0);
//
//	_SpinControlZ.SetRange(-100, 100);
//	_SpinControlZ.SetPos(0);
//	return TRUE;  // return TRUE unless you set the focus to a control
//				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
//}

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
	
	if (!_vecTex.empty())
	{
		for_each(_vecTex.begin(), _vecTex.end(), Safe_Delete<Texture*>);
		_vecTex.clear();
	}
}

// 지형 생성
void MapTab::OnBnClickedCreateTerrain()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	//if (m_dwVtxX == 0 || m_dwVtxZ == 0)
	//{
	//	MessageBoxA(nullptr, "VerTex 설정이 안되있습니다.", "VtxSetting Error", MB_OK);
	//	return;
	//}

	//GameObject* pGameObject;
	//pGameObject = GameObject::Instantiate();

	//pGameObject->AddComponent(new CTerrain(D3D9DEVICE->GetDevice(), m_dwVtxX, m_dwVtxZ, m_dwRoomNumber));
	//m_dwLastNumber++;

	//CString strNumber;
	//strNumber.Format(_T("%d"), m_dwRoomNumber);
	//m_RoomList.AddString(strNumber);

	////_vecTerrain.push_back(std::make_pair(nullptr,pGameObject));
	//_vecTerrain.emplace_back(pGameObject);

	//m_dwRoomNumber++;

	CMainFrame* pMain = static_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMapToolView* pMapToolview = static_cast<CMapToolView*>(pMain->m_tMainSplitter.GetPane(0, 1));

	GameObject* pGameObject;
	pGameObject = GameObject::Instantiate();
	pMapToolview->_mesh = new FloorTerrain(m_dwVtxX, m_dwVtxZ);
	pMapToolview->_mesh->Open(D3D9DEVICE->GetDevice());
	MeshRenderer* mr = new MeshRenderer(D3D9DEVICE->GetDevice(), pMapToolview->_mesh);
	pGameObject->AddComponent(mr);

	_vecTerrain.emplace_back(pMapToolview->_mesh);
	UpdateData(FALSE);
}

// 지형 목록 삭제
void MapTab::OnBnClickedDeleteTerrain()
{
}

// 지형 Texture File 불러오기
//void MapTab::OnBnClickedTerrainTextureLoad()
//{
//	// TODO: Load Texture list
//
//	_TextureList.ResetContent();
//
//	if (_mapTex.empty() == false)
//	{
//		for (auto iter = _mapTex.begin(); iter != _mapTex.end(); iter++)
//		{
//			if ((iter->second).second != nullptr)
//				delete (iter->second).second;
//		}
//		_mapTex.clear();
//	}
//
//	char szCurrentPath[MAX_PATH] = {};
//	GetCurrentDirectoryA(MAX_PATH, szCurrentPath);
//	std::string currPath = szCurrentPath;
//	currPath += "/Resource";
//
//	for (auto& entry : fs::directory_iterator(currPath))
//	{
//		if (entry.is_directory())
//			continue;
//
//		std::string filePath = entry.path().u8string();
//		size_t split = filePath.find('.');
//		std::string fileExtension = filePath.substr(split);
//
//		if (fileExtension == ".jpg" || fileExtension == ".png")
//		{
//			split = filePath.find_last_of('\\');
//			std::string tempStr = filePath.substr(split + 1);
//
//			std::wstring temp;
//			temp.assign(tempStr.begin(), tempStr.end());
//
//			_TextureList.AddString(temp.c_str());
//
//			std::string RealFilePath;
//			split = filePath.find('/');
//
//			RealFilePath = filePath.substr(split);
//			split = RealFilePath.find('R');
//			RealFilePath = RealFilePath.substr(split);
//
//			Texture* tex = new Texture();
//			tex->Init(D3D9DEVICE->GetDevice(), RealFilePath.c_str());
//
//			_mapTex.insert(std::make_pair(temp, std::make_pair(RealFilePath, tex)));
//		}
//	}
//}

// 지형 Texture 선택하기
//void MapTab::OnLbnSelchangeSelectTexutrePath()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//
//	int iIndexTexture = _TextureList.GetCurSel();
//
//	int iIndexTerrain = m_RoomList.GetCurSel();
//
//	if (iIndexTerrain == -1)
//		return;
//
//	CString cstrTextureName;
//	_TextureList.GetText(iIndexTexture, cstrTextureName);
//
//	auto iter = _mapTex.find(cstrTextureName.GetString());
//
//	if (iter != _mapTex.end())
//	{
//		_strfilepath = _mapTex[cstrTextureName.GetString()].first;
//		Texture* tex = _mapTex[cstrTextureName.GetString()].second;
//
//		if (_vecTerrain[iIndexTerrain] != nullptr)
//		{
//			/*static_cast<CTerrain*>(_vecTerrain[iIndexTerrain]->GetComponent(COMPONENT_ID::BEHAVIOUR))->Set_Textureinfo(tex,_strfilepath);*/
//		}
//	}
//}

//// 지형 이동 X 방향 컨트롤러 
//void MapTab::OnDeltaposMoveTerrainX(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
//	int iIndex = m_RoomList.GetCurSel();
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//
//	_iMoveX = pNMUpDown->iPos + pNMUpDown->iDelta;
//
//	if (-100 < _iMoveX && 100 > _iMoveX)
//	{
//		if (iIndex == -1)
//			iIndex = 0;
//
//		CString cstrValue;
//		cstrValue.Format(_T("%d"), _iMoveX);
//		_EditMoveX.SetWindowText(cstrValue);
//
//		/*static_cast<CTerrain*>(_vecTerrain[iIndex]->GetComponent(COMPONENT_ID::BEHAVIOUR))->MoveCheck(true);*/
//	}
//	*pResult = 0;
//}
//
//// 지형 이동 Z 방향 컨트롤러
//void MapTab::OnDeltaposTerrainMoveZ(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	_iMoveZ = pNMUpDown->iPos + pNMUpDown->iDelta;
//
//	if ((-100 < _iMoveZ) && (100 > _iMoveZ))
//	{
//		int iIndex = m_RoomList.GetCurSel();
//
//		if (iIndex == -1)
//			iIndex = 0;
//
//		CString cstrValue;
//		cstrValue.Format(_T("%d"), _iMoveZ);
//		_EditMoveZ.SetWindowText(cstrValue);
//
//		/*static_cast<CTerrain*>(_vecTerrain[iIndex]->GetComponent(COMPONENT_ID::BEHAVIOUR))->MoveCheck(true);*/
//	}
//	*pResult = 0;
//}

// 저장 Terrain Splatting (INI)
void MapTab::OnBnClickedSaveTerrain()
{
	CMainFrame* pMain = static_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMapToolView* pMapToolview = static_cast<CMapToolView*>(pMain->m_tMainSplitter.GetPane(0, 1));

	std::string Section = "Terrain";
	std::vector<std::string> vecFilepath = static_cast<FloorTerrain*>(pMapToolview->_mesh)->Get_FilePath();

	std::string	strWidth;
	strWidth = std::to_string(static_cast<FloorTerrain*>(pMapToolview->_mesh)->Get_Width());
	INIMANAGER->AddData(Section, "MapWidth", strWidth);

	std::string	strHeight;
	strHeight = std::to_string(static_cast<FloorTerrain*>(pMapToolview->_mesh)->Get_Height());
	INIMANAGER->AddData(Section, "MapHeight", strHeight);

	std::string strBaseFilePath;
	strBaseFilePath = vecFilepath[0];
	INIMANAGER->AddData(Section, "Texture0", strBaseFilePath);

	int iAlphaMapSize =(int) vecFilepath.size();

	for (int i = 1; i < iAlphaMapSize; ++i)
	{
		CString cstrTerrainNumber;
		cstrTerrainNumber.Format(_T("%d"), i);
		std::string cstrTexture = "Texture";
		cstrTexture += CT2CA(cstrTerrainNumber);

		INIMANAGER->AddData(Section, cstrTexture, vecFilepath[i].c_str());
	}
	for (int i = 1; i < iAlphaMapSize; ++i)
	{
		CString cstrTerrainNumber;
		cstrTerrainNumber.Format(_T("%d"), i);
		std::string cstrAlphaMap = "AlphaMap";
		cstrAlphaMap += CT2CA(cstrTerrainNumber);
		std::string cstrAlphaMapSavName = "Data/AlphaMap";
		cstrAlphaMapSavName += CT2CA(cstrTerrainNumber + L".png");

		tTex TexInfo = static_cast<FloorTerrain*>(pMapToolview->_mesh)->Get_FloorTerrainTex(i - 1); // 알파맵 정보

		if (TexInfo.pAlphamap == nullptr)
			return;

		IDirect3DBaseTexture9* SaveAlpha = TexInfo.pAlphamap;

		if (FAILED(D3DXSaveTextureToFileA(cstrAlphaMapSavName.c_str(), D3DXIFF_PNG, SaveAlpha, NULL)))
		{
			MessageBoxA(nullptr, "AlphaMap Save Err", "AlphaMap SaveErr", MB_OK);
			return;
		}

		INIMANAGER->AddData(Section, cstrAlphaMap, cstrAlphaMapSavName);
	}
	INIMANAGER->SaveIni("Data/Terrain");

	MessageBoxA(nullptr, "Save Success", "Success", MB_OK);
}

// 불러오기 Terrain Splatting (INI)
void MapTab::OnBnClickedLoadTerrain()
{
	CMainFrame* pMain = static_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMapToolView* pMapToolview = static_cast<CMapToolView*>(pMain->m_tMainSplitter.GetPane(0, 1));

	std::string	strWidth;
	strWidth = INIMANAGER->LoadDataString("Data/Terrain", "Terrain1", "MapWidth");
	m_dwVtxX = stoi(strWidth);

	std::string	strHeight;
	strHeight = INIMANAGER->LoadDataString("Data/Terrain", "Terrain1", "MapHeight");
	m_dwVtxZ = stoi(strHeight);

	std::string strBaseFilePath;
	strBaseFilePath = INIMANAGER->LoadDataString("Data/Terrain", "Terrain1", "BaseTerrain");
	IDirect3DTexture9* pBaseTex;
	D3DXCreateTextureFromFileA(D3D9DEVICE->GetDevice(), strBaseFilePath.c_str(), &pBaseTex);
	
	GameObject* pGameObject = GameObject::Instantiate();
	Mesh* pMesh = new FloorTerrain(m_dwVtxX, m_dwVtxZ);
	pMapToolview->_mesh = pMesh;

	pMapToolview->_mesh->Open(D3D9DEVICE->GetDevice());
	static_cast<FloorTerrain*>(pMapToolview->_mesh)->SetBaseTex(pBaseTex);

	for (int i = 0; i < 4; ++i)
	{
		CString cstrTerrainNumber;
		cstrTerrainNumber.Format(_T("%d"), i + 1);
		std::string strSection = "Data/AlphaTerrain"; // 사용할 텍스쳐 경로
		strSection += CT2CA(cstrTerrainNumber + L".png"); // 파일 이미지
		std::string strkey = "TerrainAlphaMap";

		std::string strTexFilePath;
		strTexFilePath = INIMANAGER->LoadDataString("Data/Terrain", strSection, strkey);

		IDirect3DTexture9* pTexture = nullptr;
		IDirect3DTexture9* pAlphaMapTemp = nullptr;

		D3DXCreateTextureFromFileA(D3D9DEVICE->GetDevice(), strTexFilePath.c_str(),&pTexture);
		D3DXIMAGE_INFO tImageInfo;
		D3DXGetImageInfoFromFileA(strSection.c_str(), &tImageInfo);
		//D3DXCreateTextureFromFileA(D3D9DEVICE->GetDevice(), strSection.c_str(), &pAlphaMapTemp);
		D3DXCreateTextureFromFileExA(D3D9DEVICE->GetDevice()
									,strSection.c_str()
									,tImageInfo.Width
									,tImageInfo.Height
									,tImageInfo.MipLevels
									,0
									,tImageInfo.Format
									,D3DPOOL_MANAGED
									,D3DX_DEFAULT
									,D3DX_DEFAULT
									,0
									,nullptr
									,nullptr
									,&pAlphaMapTemp);

		static_cast<FloorTerrain*>(pMapToolview->_mesh)->SetAlphaTex(pTexture, pAlphaMapTemp,(i));
	}
	
	MeshRenderer* mr = new MeshRenderer(D3D9DEVICE->GetDevice(), pMapToolview->_mesh);
	pGameObject->AddComponent(mr);
	MessageBoxA(nullptr, "Load Success", "Success", MB_OK);
}

// 모든파일 불러오기
void MapTab::OnBnClickedAllFileLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pMain = static_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CForm* pForm = static_cast<CForm*>(pMain->m_tMainSplitter.GetPane(0, 0));

	OnBnClickedLoadTerrain();
	pForm->m_pCubeTab->OnBnClickedPickingLoad();
	pForm->m_pObjectTab->OnBnClickedPositionLoad();
}

// 모든파일 저장하기
void MapTab::OnBnClickedAllFileSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pMain = static_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CForm* pForm = static_cast<CForm*>(pMain->m_tMainSplitter.GetPane(0, 0));

	OnBnClickedSaveTerrain();
	pForm->m_pCubeTab->OnBnClickedPickingSave();
	pForm->m_pObjectTab->OnBnClickedPositionSave();

}

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

	int iAlphaMapSize = (int)vecFilepath.size();

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

	std::string strLoadPath = "Data/Terrain";
	std::string strSection = "Terrain";
	std::string strTexture = "Texture";
	std::string strAlphaMap = "AlphaMap";

	std::vector<std::string> vecTexture;
	std::vector<std::string> vecAlphaMap;

	m_dwVtxX = stoi(INIMANAGER->LoadDataString(strLoadPath, strSection, "MapWidth"));
	m_dwVtxZ = stoi(INIMANAGER->LoadDataString(strLoadPath, strSection, "MapHeight"));

	GameObject* pGameObject = GameObject::Instantiate();
	Mesh* pMesh = new FloorTerrain(m_dwVtxX, m_dwVtxZ);
	static_cast<FloorTerrain*>(pMesh)->Open(D3D9DEVICE->GetDevice());

	for (DWORD i = 0; i < 5; ++i)
	{
		vecTexture.emplace_back(INIMANAGER->LoadDataString(strLoadPath, strSection, strTexture + std::to_string(i)));
		vecAlphaMap.emplace_back(INIMANAGER->LoadDataString(strLoadPath, strSection, strAlphaMap + std::to_string(i + 1)));

		if (i == 0)
		{
			IDirect3DTexture9* pTexure = nullptr;
			D3DXCreateTextureFromFileA(D3D9DEVICE->GetDevice(), vecTexture[i].c_str(), &pTexure);
			static_cast<FloorTerrain*>(pMesh)->SetBaseTex(pTexure);
		}
		else
		{
			IDirect3DTexture9* pTexure = nullptr;
			IDirect3DTexture9* pAlphaMap = nullptr;
			D3DXCreateTextureFromFileA(D3D9DEVICE->GetDevice(), vecTexture[i].c_str(), &pTexure);
			//D3DXCreateTextureFromFileA(D3D9DEVICE->GetDevice(), vecAlphaMap[i].c_str(), &pAlphaMap);
			D3DXIMAGE_INFO tImageInfo;
			D3DXGetImageInfoFromFileA(vecAlphaMap[(i - 1)].c_str(), &tImageInfo);
			D3DXCreateTextureFromFileExA(D3D9DEVICE->GetDevice()
				, vecAlphaMap[(i - 1)].c_str()
				, tImageInfo.Width
				, tImageInfo.Height
				, tImageInfo.MipLevels
				, 0
				, tImageInfo.Format
				, D3DPOOL_MANAGED
				, D3DX_DEFAULT
				, D3DX_DEFAULT
				, 0
				, nullptr
				, nullptr
				, &pAlphaMap);

			static_cast<FloorTerrain*>(pMesh)->SetAlphaTex(pTexure, pAlphaMap, (i - 1));
		}
	}
	pMapToolview->_mesh = pMesh;
	MeshRenderer* pmr = new MeshRenderer(D3D9DEVICE->GetDevice(), static_cast<FloorTerrain*>(pMesh));
	pGameObject->AddComponent(pmr);

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

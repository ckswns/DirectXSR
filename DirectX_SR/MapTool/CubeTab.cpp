// CubeTab.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "CubeTab.h"
#include "afxdialogex.h"
#include "GameObject.h"
#include "Transform.h"
#include "CubeObject.h"
#include "INIManager.h"
#include "MeshRenderer.h"
#include "MainFrm.h"
#include "MapToolView.h"

// CubeTab 대화 상자
IMPLEMENT_DYNAMIC(CubeTab, CDialog)

CubeTab::CubeTab(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CubeTab, pParent)
	, _fScaleX(1.f)
	, _fScaleY(1.f)
	, _fScaleZ(1.f)
	, _CubeNumber(0)
	, iFloor(1)
{
}

CubeTab::~CubeTab()
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
}

void CubeTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, _fScaleX);
	DDX_Text(pDX, IDC_EDIT2, _fScaleY);
	DDX_Text(pDX, IDC_EDIT3, _fScaleZ);
	DDX_Control(pDX, IDC_LIST2, _SaveList);
	DDX_Control(pDX, IDC_LIST3, _TextureList);
	DDX_Control(pDX, IDC_LIST4, _LoadList);
	DDX_Text(pDX, IDC_EDIT4, iFloor);
}

BEGIN_MESSAGE_MAP(CubeTab, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CubeTab::OnBnClickedCreateCube)
	ON_BN_CLICKED(IDC_BUTTON1, &CubeTab::OnBnClickedDataSave)
	ON_BN_CLICKED(IDC_BUTTON4, &CubeTab::OnBnClickedDataLoad)
	ON_BN_CLICKED(IDC_BUTTON3, &CubeTab::OnBnClickedScaleApply)
	ON_BN_CLICKED(IDC_BUTTON5, &CubeTab::OnBnClickedScaleReset)
	ON_BN_CLICKED(IDC_BUTTON6, &CubeTab::OnBnClickedLoadTextureList)
	ON_LBN_SELCHANGE(IDC_LIST3, &CubeTab::OnLbnSelchangeTextureSelect)
	ON_LBN_SELCHANGE(IDC_LIST4, &CubeTab::OnLbnSelchangeSelectLoadObject)
	ON_BN_CLICKED(IDC_BUTTON7, &CubeTab::OnBnClickedPickingSave)
	ON_BN_CLICKED(IDC_BUTTON8, &CubeTab::OnBnClickedPickingLoad)
	ON_EN_CHANGE(IDC_EDIT4, &CubeTab::OnEnChangeCubeFloor)
END_MESSAGE_MAP()


// CubeTab 메시지 처리기


void CubeTab::OnBnClickedCreateCube()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	//GameObject* pGameObject;s
	_pGameObject = GameObject::Instantiate();
	_pGameObject->AddComponent(new CubeObject());

	UpdateData(FALSE);
}


void CubeTab::OnBnClickedDataSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.



	//CString strNumber;
	//strNumber.Format(_T("%d"), _CubeNumber);
	//TCHAR	szName[MAX_PATH] = L"Cube";
	//lstrcat(szName, strNumber);
	//_SaveList.AddString(szName);
	//_CubeNumber++;
}


void CubeTab::OnBnClickedDataLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CubeTab::OnBnClickedScaleApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	
	_pGameObject->GetTransform()->SetLocalScale(_fScaleX, _fScaleY, _fScaleZ);

	UpdateData(FALSE);
}


void CubeTab::OnBnClickedScaleReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (_pTexture == nullptr)
	{
		MessageBoxA(nullptr, "텍스트가 없습니다.", "Create Cube Error", MB_OK);
		return;
	}

	UpdateData(TRUE);

	//GameObject* pGameObject;s
	if (_pGameObject == nullptr)
	{
		_pGameObject = GameObject::Instantiate();
		_pGameObject->AddComponent(new CubeObject(_pTexture));
	}
	else
	{
		MeshRenderer* renderer = static_cast<MeshRenderer*>(_pGameObject->GetComponent(COMPONENT_ID::RENDERER));
		renderer->GetMaterialPTR()->SetTexture(_pTexture);
	}
	
	UpdateData(FALSE);
}

//	저장하기
void CubeTab::OnBnClickedDataSave()
{
	// TODO: 큐브 ini 저장

	int iIndex = _TextureList.GetCurSel();

	if (iIndex == -1)
	{
		MessageBoxA(nullptr, "목록이 비여있습니다.", "Save Error", MB_OK);
		return; 
	}
	//CString strObjectConun;

	CString strNumber;
	strNumber.Format(_T("%d"), _CubeNumber);

	CString strName = L"Cube";
	strName += strNumber;
	_SaveList.AddString(strName);
	_CubeNumber++;

	std::string strSection;
	strSection = CT2CA(strName);

	std::string  strScaleX;
	strScaleX = (std::to_string(_fScaleX));
	std::string  strScaleY;
	strScaleY = (std::to_string(_fScaleY));
	std::string  strScaleZ;
	strScaleZ = (std::to_string(_fScaleZ));

	//	섹션 / 키값(고정된 값) / 넣고자 하는 데이터
	INIMANAGER->AddData(/*섹션*/strSection, /*키값(고정값)*/"filePath", /*넣고 자 하는 데이터*/_strFilePath);
	INIMANAGER->AddData(strSection, "scaleX", strScaleX);
	INIMANAGER->AddData(strSection, "scaleY", strScaleY);
	INIMANAGER->AddData(strSection, "scaleZ", strScaleZ);
	INIMANAGER->SaveIni("Data/Cube");
}

//	불러오기
void CubeTab::OnBnClickedDataLoad()
{
	// TODO: 불러오기
	if (_pGameObject)
	{
		MeshRenderer* renderer = static_cast<MeshRenderer*>(_pGameObject->GetComponent(COMPONENT_ID::RENDERER));
		renderer->GetMaterialPTR()->SetTexture(nullptr);
	}

	if (_vecObject.empty() == false)
	{
		MessageBoxA(nullptr, "파일이 로드되어있습니다.", "Load Error", MB_OK);
		return;
	}

	int iCount = 0;
	while (true)
	{
		CString strNumber;
		strNumber.Format(_T("%d"), iCount);

		CString strName = L"Cube";
		strName += strNumber;

		std::string strSection;
		strSection = CT2CA(strName);

		std::string strLoadFilePath;
		strLoadFilePath = INIMANAGER->LoadDataString("Data/Cube", strSection,"filepath");

		if (strcmp("",strLoadFilePath.c_str()) == 0)
			break;

		std::string strLoadScaleX;
		strLoadScaleX = INIMANAGER->LoadDataString("Data/Cube", strSection, "scaleX");

		std::string strLoadScaleY;
		strLoadScaleY = INIMANAGER->LoadDataString("Data/Cube", strSection, "scaleY");

		std::string strLoadScaleZ;
		strLoadScaleZ = INIMANAGER->LoadDataString("Data/Cube", strSection, "scaleZ");

		_fScaleX = stof(strLoadScaleX);
		_fScaleY = stof(strLoadScaleY);
		_fScaleZ = stof(strLoadScaleZ);

		size_t split;
		split = strLoadFilePath.find('\\');

		std::string strKey;
		strKey = strLoadFilePath.substr(split);

		std::wstring wstrKey;
		wstrKey.assign(strKey.begin(), strKey.end());
		_LoadList.AddString(wstrKey.c_str());

		wstrKey.assign(strSection.begin(), strSection.end());

		Texture* pTexture = new Texture();
		pTexture->Init(D3D9DEVICE->GetDevice(), strLoadFilePath.c_str());

		_mapTex.insert(std::make_pair(wstrKey, std::make_pair(strLoadFilePath, pTexture)));

		GameObject* pGameObject = GameObject::Instantiate();
		pGameObject->GetTransform()->SetLocalScale(_fScaleX, _fScaleY, _fScaleZ);
		pGameObject->AddComponent(new CubeObject(pTexture));

		pGameObject->SetActive(false);
		_vecObject.emplace_back(pGameObject,0); // 고민 후 삭제

		iCount++;
	}

}

void CubeTab::OnLbnSelchangeSelectLoadObject()
{
	// TODO: Load Object Render Check

	//if (_vecObject.empty())
	//{
	//	MessageBoxA(nullptr, "Object 목록이 비였습니다.", "Object List Error", MB_OK);
	//	return;
	//}

	//int iIndex = _LoadList.GetCurSel();
	//size_t ObjectListSize = _vecObject.size();

	//for (size_t i = 0; i < ObjectListSize; i++)
	//{
	//	_vecObject[i]->SetActive(false);
	//}

	//_vecObject[iIndex]->SetActive(true);
}

void CubeTab::OnBnClickedScaleApply()
{
	// TODO: Scale 변화

	UpdateData(TRUE);
	
	if (_pGameObject == nullptr)
	{
		MessageBoxA(nullptr, "오브젝트가 없습니다.", "Scale Apply Error", MB_OK);
		return;
	}
	_pGameObject->GetTransform()->SetLocalScale(_fScaleX, _fScaleY, _fScaleZ);

	UpdateData(FALSE);
}


void CubeTab::OnBnClickedScaleReset()
{
	// TODO: Scale 초기화
	UpdateData(TRUE);

	if (_pGameObject == nullptr)
	{
		MessageBoxA(nullptr, "오브젝트가 없습니다.", "Scale Reset Error", MB_OK);
		return;
	}

	_fScaleX = 1.f;
	_fScaleY = 1.f;
	_fScaleZ = 1.f;

	_pGameObject->GetTransform()->SetLocalScale(_fScaleX, _fScaleY, _fScaleZ);

	UpdateData(FALSE);
}


void CubeTab::OnBnClickedLoadTextureList()
{
	// TODO: .dds 큐브 Texture 파일 정보

	if (_pGameObject)
	{
		MeshRenderer* renderer = static_cast<MeshRenderer*>(_pGameObject->GetComponent(COMPONENT_ID::RENDERER));
		renderer->GetMaterialPTR()->SetTexture(nullptr);
	}

	if (_mapTex.empty() == false)
	{
		for (auto iter = _mapTex.begin(); iter != _mapTex.end(); iter++)
		{
			if ((iter->second).second != nullptr)
				delete (iter->second).second;
		}

		_mapTex.clear();
	}
	
	_TextureList.ResetContent();

	TCHAR szFilePath[MAX_PATH] = L"";
	CFileDialog Dlg(true, L".dds", L"*.dds", OFN_ALLOWMULTISELECT);

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
		
		if (fileExtension == ".dds")
		{
			split = filePath.find_last_of('\\');
			std::string tempStr = filePath.substr(split);

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


void CubeTab::OnLbnSelchangeTextureSelect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int iIndex = _TextureList.GetCurSel();

	CString cstrTextureName;
	_TextureList.GetText(iIndex, cstrTextureName);

	auto iter = _mapTex.find(cstrTextureName.GetString());

	if (iter != _mapTex.end())
	{
		_pTexture = _mapTex[cstrTextureName.GetString()].second;
		_strFilePath = _mapTex[cstrTextureName.GetString()].first;
	}
	else
		_pTexture = nullptr;
}


void CubeTab::OnBnClickedPickingSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pMain = static_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMapToolView* pMapToolview = static_cast<CMapToolView*>(pMain->m_tMainSplitter.GetPane(0, 1));

	if (pMapToolview->_vecCube.empty())
	{
		MessageBoxA(nullptr, "저장할게 없습니다.", "Picking Save Error", MB_OK);
		return;
	}

	int tcubesize = (int)pMapToolview->_vecCube.size();
	std::string strCubeCnt;
	strCubeCnt = std::to_string(tcubesize);
	INIMANAGER->AddData("Start", "CubeCnt", strCubeCnt);

	for (int i = 0; i < tcubesize; i++)
	{
		CString strNumber;
		strNumber.Format(_T("%d"), i);

		CString strName = L"PickingCube";
		strName += strNumber;

		std::string strSection;
		strSection = CT2CA(strName);
		std::string filepath = pMapToolview->_vecCube[i].second.first;
		INIMANAGER->AddData(strSection, "filePath", filepath);

		D3DXVECTOR3 vScale = pMapToolview->_vecCube[i].first->GetTransform()->GetLocalScale();
		std::string  strScaleX;
		strScaleX = (std::to_string(vScale.x));
		INIMANAGER->AddData(strSection, "scaleX", strScaleX);

		std::string  strScaleY;
		strScaleY = (std::to_string(vScale.y));
		INIMANAGER->AddData(strSection, "scaleY", strScaleY);

		std::string  strScaleZ;
		strScaleZ = (std::to_string(vScale.z));
		INIMANAGER->AddData(strSection, "scaleZ", strScaleZ);

		D3DXVECTOR3 vworldpos = pMapToolview->_vecCube[i].first->GetTransform()->GetWorldPosition();
		std::string  strworldposX;
		strworldposX = (std::to_string(vworldpos.x));
		INIMANAGER->AddData(strSection, "worldposX", strworldposX);

		std::string  strworldposY;
		strworldposY = (std::to_string(vworldpos.y));
		INIMANAGER->AddData(strSection, "worldposY", strworldposY);

		std::string  strworldposZ;
		strworldposZ = (std::to_string(vworldpos.z));
		INIMANAGER->AddData(strSection, "worldposZ", strworldposZ);

		std::string strRoomnumber;
		strRoomnumber = (std::to_string(pMapToolview->_vecCube[i].second.second));
		INIMANAGER->AddData(strSection, "Room", strRoomnumber);
	}
	INIMANAGER->SaveIni("Data/PickingCube");
	MessageBoxA(nullptr, "PickingCube 저장 성공!", "PickingCube Save Success", MB_OK);
}


void CubeTab::OnBnClickedPickingLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pMain = static_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMapToolView* pMapToolview = static_cast<CMapToolView*>(pMain->m_tMainSplitter.GetPane(0, 1));

	if (!pMapToolview->_vecCube.empty())
	{
		MessageBoxA(nullptr, "이미 로드되어있습니다.", "Load Error", MB_OK);
		return;
	}
	std::string strStart;
	int objcnt = std::stoi(INIMANAGER->LoadDataString("Data/PickingCube", "Start", "CubeCnt"));

	int iKeyNumber = 0;

	for (int i = 0; i < objcnt; i++)
	{
		std::string strsection = "PickingCube";
		strsection += std::to_string(i);

		std::string strfilepath;
		strfilepath = INIMANAGER->LoadDataString("Data/PickingCube", strsection, "filePath");

		D3DXVECTOR3 vscale;
		vscale.x = stof(INIMANAGER->LoadDataString("Data/PickingCube", strsection, "scaleX"));
		vscale.y = stof(INIMANAGER->LoadDataString("Data/PickingCube", strsection, "scaleY"));
		vscale.z = stof(INIMANAGER->LoadDataString("Data/PickingCube", strsection, "scaleZ"));

		D3DXVECTOR3	vworldpos;
		vworldpos.x = stof(INIMANAGER->LoadDataString("Data/PickingCube", strsection, "worldposX"));
		vworldpos.y = stof(INIMANAGER->LoadDataString("Data/PickingCube", strsection, "worldposY"));
		vworldpos.z = stof(INIMANAGER->LoadDataString("Data/PickingCube", strsection, "worldposZ"));

		int	Roomnumber;
		Roomnumber = stoi(INIMANAGER->LoadDataString("Data/PickingCube", strsection, "Room"));

		GameObject* pGameObject = GameObject::Instantiate();
		pGameObject = GameObject::Instantiate();
		Texture* pTex = new Texture();
		pTex->Init(D3D9DEVICE->GetDevice(), strfilepath.c_str());

		size_t split;
		split = strfilepath.find('\\');
		std::string strKey;
		strKey = strfilepath.substr(split);
		std::wstring wstrKey;
		wstrKey.assign(strKey.begin(), strKey.end());

		wstrKey += std::to_wstring(iKeyNumber);

		_mapTex.insert(std::make_pair(wstrKey, std::make_pair(strfilepath, pTex))); // 삭제용

		pGameObject->AddComponent(new CubeObject(pTex));
		pGameObject->GetTransform()->SetLocalScale(vscale);
		pGameObject->GetTransform()->SetWorldPosition(vworldpos);

		/*_vecObject.emplace_back(pGameObject, Roomnumber);*/
		pMapToolview->_vecCube.emplace_back(pGameObject, std::make_pair(strfilepath, Roomnumber));

		iKeyNumber++;
	}

	MessageBoxA(nullptr, "Picking Cube 불러오기 성공!", "Load Success", MB_OK);
}


void CubeTab::OnEnChangeCubeFloor()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	iFloor;

	UpdateData(FALSE);
}

// ObjectTab.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "ObjectTab.h"
#include "afxdialogex.h"
#include "INIManager.h"
#include "Transform.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Quad.h"
#include "MainFrm.h"
#include "MapToolView.h"
#include <sstream>

// ObjectTab 대화 상자

IMPLEMENT_DYNAMIC(ObjectTab, CDialog)

ObjectTab::ObjectTab(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ObjectTab, pParent)
	, _cstrKey(_T(""))
{

}

ObjectTab::~ObjectTab()
{
	//for (int i = 0; i < (int)KIND::K_END; ++i)
	//{
	//	for (auto iter : _vecObjects[i])
	//	{
	//		if (iter.second.second != nullptr)
	//			delete iter.second.second;
	//	}
	//}

	if (!_vecSaveName.empty())
	{
		for (auto& iter : _vecSaveName)
		{
			if (iter.second.second != nullptr)
			{
				delete iter.second.second;
			}
		}
	}
}

void ObjectTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT4, _cstrKey);
}



BEGIN_MESSAGE_MAP(ObjectTab, CDialog)


	ON_BN_CLICKED(IDC_BUTTON3, &ObjectTab::OnBnClickedPositionSave)
	ON_BN_CLICKED(IDC_BUTTON9, &ObjectTab::OnBnClickedPositionLoad)
	ON_EN_CHANGE(IDC_EDIT4, &ObjectTab::OnEnChangekey)

END_MESSAGE_MAP()


// ObjectTab 메시지 처리기

void ObjectTab::OnBnClickedPositionSave()
{
	int iCnt = (int)_vecSaveName.size();
	
	std::string strNames;

	for (int i = 0; i < iCnt; ++i)
	{
		strNames += (_vecSaveName[i].first + ",");
		INIMANAGER->AddData("SectionNames", "Names", strNames);
	}

	for (int i = 0; i < iCnt; ++i)
	{
		std::string Section = _vecSaveName[i].first;
		std::string key = "";
		std::string Data;

		key = "worldX";
		Data = std::to_string((_vecSaveName[i].second.first)->GetTransform()->GetWorldPosition().x);
		INIMANAGER->AddData(Section, key, Data);

		key = "worldY";
		Data = std::to_string((_vecSaveName[i].second.first)->GetTransform()->GetWorldPosition().y);
		INIMANAGER->AddData(Section, key, Data);

		key = "worldZ";
		Data = std::to_string((_vecSaveName[i].second.first)->GetTransform()->GetWorldPosition().z);
		INIMANAGER->AddData(Section, key, Data);
	}
	INIMANAGER->SaveIni("Data/Object");

	MessageBoxA(nullptr, "Save Success", "Success", MB_OK);
}

std::vector<std::string> ObjectTab::Split(std::string input, char delimiter)
{
	std::vector<std::string> result;
	std::stringstream ss(input);
	std::string temp;

	while (getline(ss, temp, delimiter))
	{
		result.push_back(temp);
	}

	return result;
}

void ObjectTab::OnBnClickedPositionLoad()
{
	if (!_vecSaveName.empty())
	{
		MessageBoxA(nullptr, "로드 되어있습니다.", "Load Failed", MB_OK);
		return;
	}

	std::string filePath = "Data/Object";

	std::string strFileName = INIMANAGER->LoadDataString(filePath, "SectionNames", "Names");

	std::vector<std::string> section =	Split(strFileName, ',');

	int isize = section.size();

	for (int i = 0; i < isize; ++i)
	{
		GameObject* pGameObject = GameObject::Instantiate();

		Texture* pTex = new Texture();
		pTex->Init(D3D9DEVICE->GetDevice(), "Resource/Tile1.png");

		Mesh* pMesh = new Quad();
		pMesh->Open(D3D9DEVICE->GetDevice());

		MeshRenderer* pMr = new MeshRenderer(D3D9DEVICE->GetDevice(), pMesh);
		pMr->GetMaterialPTR()->SetMainTexture(pTex);

		float worldX = 0;
		float worldY = 0;
		float worldZ = 0;

		worldX = stof(INIMANAGER->LoadDataString(filePath, section[i], "worldX"));
		worldY = stof(INIMANAGER->LoadDataString(filePath, section[i], "worldY"));
		worldZ = stof(INIMANAGER->LoadDataString(filePath, section[i], "worldZ"));

		pGameObject->GetTransform()->SetWorldPosition(worldX, worldY, worldZ);
		pGameObject->AddComponent(pMr);

		_vecSaveName.emplace_back(std::make_pair(section[i],std::make_pair(pGameObject,pTex)));
	}


	MessageBoxA(nullptr, "Load Object Success", "Success", MB_OK);
}
void ObjectTab::OnEnChangekey()
{
	UpdateData(TRUE);
}

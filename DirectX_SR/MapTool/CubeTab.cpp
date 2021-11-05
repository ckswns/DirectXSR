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


// CubeTab 대화 상자

IMPLEMENT_DYNAMIC(CubeTab, CDialog)

CubeTab::CubeTab(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CubeTab, pParent)
	, _fScaleX(1.f)
	, _fScaleY(1.f)
	, _fScaleZ(1.f)
	, _CubeNumber(0)
{

}

CubeTab::~CubeTab()
{

}

void CubeTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, _fScaleX);
	DDX_Text(pDX, IDC_EDIT2, _fScaleY);
	DDX_Text(pDX, IDC_EDIT3, _fScaleZ);
	DDX_Control(pDX, IDC_LIST2, _SaveList);
	DDX_Control(pDX, IDC_LIST3, _TextureList);
}

BEGIN_MESSAGE_MAP(CubeTab, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CubeTab::OnBnClickedCreateCube)
	ON_BN_CLICKED(IDC_BUTTON1, &CubeTab::OnBnClickedDataSave)
	ON_BN_CLICKED(IDC_BUTTON4, &CubeTab::OnBnClickedDataLoad)
	ON_BN_CLICKED(IDC_BUTTON3, &CubeTab::OnBnClickedScaleApply)
	ON_BN_CLICKED(IDC_BUTTON5, &CubeTab::OnBnClickedScaleReset)
	ON_BN_CLICKED(IDC_BUTTON6, &CubeTab::OnBnClickedLoadTextureList)
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

	_fScaleX = 1.f;
	_fScaleY = 1.f;
	_fScaleZ = 1.f;

	_pGameObject->GetTransform()->SetLocalScale(_fScaleX, _fScaleY, _fScaleZ);

	UpdateData(FALSE);
}


void CubeTab::OnBnClickedLoadTextureList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	TCHAR szFilePath[MAX_PATH] = L"";
	CFileDialog Dlg(true, L"dds", L"*.dds", OFN_ALLOWMULTISELECT);

	WCHAR    strFile[512] = {};

	CString fileName;

	Dlg.m_ofn.lpstrFile = strFile;
	Dlg.m_ofn.lpstrFile = fileName.GetBuffer(512);
	Dlg.m_ofn.nMaxFile = sizeof(strFile);
	Dlg.m_ofn.nMaxFile = 512;

	GetCurrentDirectory(MAX_PATH, szFilePath);

	PathRemoveFileSpec(szFilePath);
	lstrcat(szFilePath, L"\\Resource");

	Dlg.m_ofn.lpstrInitialDir = szFilePath;

	CString test;

	if (IDOK == Dlg.DoModal())
	{
		POSITION pos(Dlg.GetStartPosition());
		while (pos)
		{
			//CString filename = Dlg.GetNextPathName(pos);
			CString strFilePath = Dlg.GetNextPathName(pos);
			test += strFilePath;

			lstrcpy(szFilePath, strFilePath);

			HANDLE hFile = CreateFile(strFilePath, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

			if (INVALID_HANDLE_VALUE == hFile)
				continue;

			TCHAR szCurrentPath[MAX_PATH] = {};
			GetCurrentDirectory(MAX_PATH, szCurrentPath);
			TCHAR szRelativePath[MAX_PATH] = {};

			PathRelativePathTo(szRelativePath, szCurrentPath, FILE_ATTRIBUTE_DIRECTORY, strFilePath.GetString(), FILE_ATTRIBUTE_DIRECTORY);

			CString wstrRelativePath = CString(szRelativePath);
			_TextureList.AddString(wstrRelativePath);
		}
		//int a = 0;
	}
}

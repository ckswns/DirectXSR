// CubeTab.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "CubeTab.h"
#include "afxdialogex.h"
#include "GameObject.h"
#include "Transform.h"
#include "CubeObject.h"


// CubeTab 대화 상자

IMPLEMENT_DYNAMIC(CubeTab, CDialog)

CubeTab::CubeTab(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CubeTab, pParent)
{

}

CubeTab::~CubeTab()
{

}

void CubeTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CubeTab, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CubeTab::OnBnClickedCreateCube)
END_MESSAGE_MAP()


// CubeTab 메시지 처리기


void CubeTab::OnBnClickedCreateCube()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	GameObject* pGameObject;
	pGameObject = GameObject::Instantiate();
	pGameObject->AddComponent(new CubeObject());

}

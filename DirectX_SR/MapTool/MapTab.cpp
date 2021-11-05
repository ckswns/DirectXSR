// MapTab.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "MapTab.h"
#include "afxdialogex.h"
#include "Transform.h"

// MapTab 대화 상자

IMPLEMENT_DYNAMIC(MapTab, CDialog)

MapTab::MapTab(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MapTab, pParent)
	, m_dwVtxZ(0)
	, m_dwVtxX(0)
	, m_dwIntvX(0)
	, m_dwIntvZ(0)
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
	DDX_Text(pDX, IDC_EDIT3, m_dwIntvX);
	DDX_Text(pDX, IDC_EDIT4, m_dwIntvZ);
	DDX_Text(pDX, IDC_EDIT5, m_dwRoomNumber);
	DDX_Control(pDX, IDC_LIST1, m_RoomList);
}


BEGIN_MESSAGE_MAP(MapTab, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &MapTab::OnBnClickedCreateTerrain)
	ON_BN_CLICKED(IDC_BUTTON3, &MapTab::OnBnClickedDeleteTerrain)
END_MESSAGE_MAP()


// MapTab 메시지 처리기

void MapTab::Release()
{

}

void MapTab::OnBnClickedCreateTerrain()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	LPDIRECT3DDEVICE9 pDevice = D3D9DEVICE->GetDevice();

	GameObject* pGameObject;
	pGameObject = GameObject::Instantiate();
	pGameObject->GetTransform()->SetLocalScale(1, 1, 1);
	pGameObject->AddComponent(new CTerrain(pDevice, m_dwVtxX, m_dwVtxZ, m_dwIntvX, m_dwIntvZ, m_dwRoomNumber));
	m_dwLastNumber++;

	CString strNumber;
	strNumber.Format(_T("%d"), m_dwRoomNumber);
	m_RoomList.AddString(strNumber);

	m_dwRoomNumber++;
	UpdateData(FALSE);

}


void MapTab::OnBnClickedDeleteTerrain()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다

}


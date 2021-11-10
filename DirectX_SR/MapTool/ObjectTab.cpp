// ObjectTab.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "ObjectTab.h"
#include "afxdialogex.h"


// ObjectTab 대화 상자

IMPLEMENT_DYNAMIC(ObjectTab, CDialog)

ObjectTab::ObjectTab(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ObjectTab, pParent)
{

}

ObjectTab::~ObjectTab()
{
}

void ObjectTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, _TextureList);
}



BEGIN_MESSAGE_MAP(ObjectTab, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &ObjectTab::OnBnClickedObjectTextureLoad)
END_MESSAGE_MAP()


// ObjectTab 메시지 처리기


void ObjectTab::OnBnClickedObjectTextureLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

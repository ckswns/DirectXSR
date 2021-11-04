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
}


BEGIN_MESSAGE_MAP(ObjectTab, CDialog)
END_MESSAGE_MAP()


// ObjectTab 메시지 처리기

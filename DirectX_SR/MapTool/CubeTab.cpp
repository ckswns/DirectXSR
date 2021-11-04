// CubeTab.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "CubeTab.h"
#include "afxdialogex.h"


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
END_MESSAGE_MAP()


// CubeTab 메시지 처리기

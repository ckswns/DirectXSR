// MapToolSubView.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "MapToolSubView.h"


// MapToolSubView

IMPLEMENT_DYNCREATE(MapToolSubView, CView)

MapToolSubView::MapToolSubView()
{

}

MapToolSubView::~MapToolSubView()
{
}

BEGIN_MESSAGE_MAP(MapToolSubView, CView)
END_MESSAGE_MAP()


// MapToolSubView 그리기

void MapToolSubView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// MapToolSubView 진단

#ifdef _DEBUG
void MapToolSubView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void MapToolSubView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// MapToolSubView 메시지 처리기


// MainFrm.h: CMainFrame 클래스의 인터페이스
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected:											CMainFrame() noexcept;
protected:											DECLARE_DYNCREATE(CMainFrame)

// 재정의입니다.
public:				virtual BOOL				PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:				virtual						~CMainFrame();

#ifdef _DEBUG
public:				virtual void					AssertValid() const;
public:				virtual void					Dump(CDumpContext& dc) const;
#endif

// 생성된 메시지 맵 함수
protected:			afx_msg int				OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:											DECLARE_MESSAGE_MAP()
private:				virtual BOOL				OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

private:				CSplitterWnd				_MainSplitter;

};



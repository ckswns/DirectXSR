
// ParticleEditorView.h: CParticleEditorView 클래스의 인터페이스
//

#pragma once

class CParticleEditorDoc;
class CParticleEditorView : public CView
{
protected:												CParticleEditorView() noexcept;
protected:												DECLARE_DYNCREATE(CParticleEditorView)

// 특성입니다.
public:				CParticleEditorDoc*			GetDocument() const;

public:				virtual void						OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
public:				virtual BOOL					PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:				virtual							~CParticleEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:												DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // ParticleEditorView.cpp의 디버그 버전
inline CParticleEditorDoc* CParticleEditorView::GetDocument() const
   { return reinterpret_cast<CParticleEditorDoc*>(m_pDocument); }
#endif



// MapToolView.h: CMapToolView 클래스의 인터페이스
//

#pragma once

#include "GameObject.h"
#include "TerrainTex.h"
#include "Scene.h"
#include "Transform.h"
#include "EditorCamera.h"
#include "Texture.h"
#include "FloorTerrain.h"


class CMapToolDoc;

class CMapToolView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMapToolView() noexcept;
	DECLARE_DYNCREATE(CMapToolView)

// 특성입니다.
public:
	CMapToolDoc* GetDocument() const;

// 작업입니다.
public:


private: LPDIRECT3DDEVICE9 m_pGraphicDev;

private: Scene::KEY_VALUE_LIST	m_vecKeyValue;
private: GameObject*			m_pCamera;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMapToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	std::vector<std::pair<GameObject*,std::string>> _vecCube;
	Mesh* _mesh = nullptr;
	
	CString _cstrPreKey;
	int _iETC = 0;

public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // MapToolView.cpp의 디버그 버전
inline CMapToolDoc* CMapToolView::GetDocument() const
   { return reinterpret_cast<CMapToolDoc*>(m_pDocument); }
#endif


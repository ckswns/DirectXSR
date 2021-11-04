
// ParticleEditorDoc.h: CParticleEditorDoc 클래스의 인터페이스
//


#pragma once


class CParticleEditorDoc : public CDocument
{
protected:												CParticleEditorDoc() noexcept;
protected:												DECLARE_DYNCREATE(CParticleEditorDoc)

public:				virtual BOOL					OnNewDocument();
public:				virtual void						Serialize(CArchive& ar);

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:				virtual							~CParticleEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 생성된 메시지 맵 함수
protected:												DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

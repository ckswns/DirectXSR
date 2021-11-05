#pragma once

// CParticleForm 폼 보기

#include "BillBordParticle.h"
#include "ColorDlg.h"
class CParticleForm : public CFormView
{
	DECLARE_DYNCREATE(CParticleForm)

protected:										CParticleForm();           
protected:			virtual					~CParticleForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ParticleForm };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:			virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
protected:										DECLARE_MESSAGE_MAP()
public:	virtual void OnInitialUpdate();

public:	afx_msg void OnBnClickedLoop();
public:	afx_msg void OnBnClickedPlay();
public:	afx_msg void OnChangeEditCtrl();
public:	afx_msg void OnBnClickedBtnSelectcolor();

private:				BillBordParticle*					_pParticle;



private:	CString _strDuration;
private:	CString _strLifeTime;
private:	CString _strSpeed;
private:	CString _strSize;
private:	CString _strGravity;
	   CString _strR;
	   CString _strG;
	   CString _strB;
	   CString _strA;

private: ColorDlg* _ColorDlg;


public:
	CString _strMax;
	CString _strEmitRate;
	afx_msg void OnBnClickedStop();
};



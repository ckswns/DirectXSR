#pragma once

// CParticleForm 폼 보기

#include "BillBordParticle.h"
#include "ColorDlg.h"

class BoxForm;
class SphereForm;
class ConeForm;
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

public:	afx_msg void OnBnClickedPlay();
public:  afx_msg void OnBnClickedStop();

public:	afx_msg void OnBnClickedLoop();
public:	afx_msg void OnChangeEditCtrl();
public:	afx_msg void OnBnClickedBtnSelectcolor();

public:  afx_msg void OnEnChangeEditColor();

public:  afx_msg void OnCbnSelchangeShapecombo();


public: BillBordParticle* GetParticle() { return _pParticle; }
private: void				AllocForms();
private: void				ShowForm(int idx);

private:	BoxForm*				_pBoxForm;
private: SphereForm*			_pSphereForm;
private: ConeForm*				_pConeForm;

private:	BillBordParticle*		_pParticle;

private: CString					 _strDuration;
private: CString					 _strLifeTime;
private: CString					 _strSpeed;
private: CString					 _strSize;
private: CString					 _strGravity;
private: CString					 _strMax;
private: CString					 _strEmitRate;

private: CString					 _strR;
private: CString					 _strG;
private: CString					 _strB;
private: CString					 _strA;
private: ColorDlg*				 _ColorDlg;

private: CComboBox			 _ComboBox;

public:
	afx_msg void OnBnClickedChkAwake();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnLoad();
};



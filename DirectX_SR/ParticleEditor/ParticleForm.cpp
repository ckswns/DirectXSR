// ParticleForm.cpp: 구현 파일
//

#include "pch.h"
#include "ParticleEditor.h"
#include "ParticleForm.h"

#include "ParticleSys.h"
#include "Transform.h"
#include "BoxForm.h"
#include "SphereForm.h"
#include "ConeForm.h"
// CParticleForm

IMPLEMENT_DYNCREATE(CParticleForm, CFormView)

CParticleForm::CParticleForm()
	: CFormView(IDD_ParticleForm), _pBoxForm(nullptr)
	, _strDuration(_T("5"))	, _strLifeTime(_T("5")), _strSpeed(_T("1"))	, _strSize(_T("0.2"))
	, _strGravity(_T("0")), _strMax(_T("50")), _strEmitRate(_T("5"))
	, _strR(_T("255")), _strG(_T("255")), _strB(_T("255")), _strA(_T("255"))
{
	__noop;
}

CParticleForm::~CParticleForm()
{
	//_pBoxForm->DestroyWindow();
	_pBoxForm = nullptr;

//	_pSphereForm->DestroyWindow();
	_pSphereForm = nullptr;

//	_pConeForm->DestroyWindow();
	_pConeForm = nullptr;
}

void CParticleForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DURATION, _strDuration);
	DDX_Text(pDX, IDC_EDIT_LIFETIME, _strLifeTime);
	DDX_Text(pDX, IDC_EDIT_SPEED, _strSpeed);
	DDX_Text(pDX, IDC_EDIT_SIZE, _strSize);
	DDX_Text(pDX, IDC_EDIT_GRAVITY, _strGravity);
	DDX_Text(pDX, IDC_EDIT_R, _strR);
	DDX_Text(pDX, IDC_EDIT_G, _strG);
	DDX_Text(pDX, IDC_EDIT_B, _strB);
	DDX_Text(pDX, IDC_EDIT_A, _strA);
	DDX_Text(pDX, IDC_EDIT_MAXPARTICLES, _strMax);
	DDX_Text(pDX, IDC_EDIT_EMITRATE, _strEmitRate);
	DDX_Control(pDX, IDC_SHAPECOMBO, _ComboBox);

}

BEGIN_MESSAGE_MAP(CParticleForm, CFormView)
	ON_BN_CLICKED(IDC_CHK_LOOP, &CParticleForm::OnBnClickedLoop)
	ON_BN_CLICKED(IDC_Play, &CParticleForm::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_BTN_SELECTCOLOR, &CParticleForm::OnBnClickedBtnSelectcolor)
	ON_BN_CLICKED(IDC_STOP, &CParticleForm::OnBnClickedStop)

	ON_EN_CHANGE(IDC_EDIT_DURATION, &CParticleForm::OnChangeEditCtrl)
	ON_EN_CHANGE(IDC_EDIT_LIFETIME, &CParticleForm::OnChangeEditCtrl)
	ON_EN_CHANGE(IDC_EDIT_SPEED, &CParticleForm::OnChangeEditCtrl)
	ON_EN_CHANGE(IDC_EDIT_SIZE, &CParticleForm::OnChangeEditCtrl)
	ON_EN_CHANGE(IDC_EDIT_GRAVITY, &CParticleForm::OnChangeEditCtrl)
	ON_EN_CHANGE(IDC_EDIT_MAXPARTICLES, &CParticleForm::OnChangeEditCtrl)
	ON_EN_CHANGE(IDC_EDIT_EMITRATE, &CParticleForm::OnChangeEditCtrl)

	ON_EN_CHANGE(IDC_EDIT_R, &CParticleForm::OnEnChangeEditColor)
	ON_EN_CHANGE(IDC_EDIT_G, &CParticleForm::OnEnChangeEditColor)
	ON_EN_CHANGE(IDC_EDIT_B, &CParticleForm::OnEnChangeEditColor)
	ON_EN_CHANGE(IDC_EDIT_A, &CParticleForm::OnEnChangeEditColor)
	ON_CBN_SELCHANGE(IDC_SHAPECOMBO, &CParticleForm::OnCbnSelchangeShapecombo)
	ON_BN_CLICKED(IDC_CHK_AWAKE, &CParticleForm::OnBnClickedChkAwake)
END_MESSAGE_MAP()

// CParticleForm 진단

#ifdef _DEBUG
void CParticleForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CParticleForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

// CParticleForm 메시지 처리기

void CParticleForm::OnBnClickedLoop()
{
	if (IsDlgButtonChecked(IDC_CHK_LOOP))
		_pParticle->SetLoop(true);
	else
		_pParticle->SetLoop(false);
}

void CParticleForm::OnBnClickedPlay()
{
	_pParticle->Play();
}

void CParticleForm::OnBnClickedStop()
{
	_pParticle->Stop();
}


void CParticleForm::OnInitialUpdate()
{
//	CFormView::OnInitialUpdate();

	CheckDlgButton(IDC_CHK_LOOP, TRUE);
	CheckDlgButton(IDC_CHK_AWAKE, TRUE);

	_strDuration = "5";
	_strLifeTime = "5";
	_strSpeed = "1";
	_strSize = "0.2";
	_strGravity = "0";

	_strR = "255";
	_strG = "255";
	_strB = "255";
	_strA = "255";
	UpdateData(FALSE);

	_ComboBox.AddString(L"Box");
	_ComboBox.AddString(L"Cone");
	_ComboBox.AddString(L"Sphere");
	AllocForms();

	_ColorDlg = new ColorDlg(this);

	GameObject* pGameObj;
	pGameObj = GameObject::Instantiate();
	pGameObj->GetTransform()->SetWorldPosition(0.f, 0, 5.f);
	pGameObj->AddComponent(new ParticleSys());

	SCENEMANAGER->GetActiveScene()->InsertGameObject(pGameObj);

	_pParticle = static_cast<BillBordParticle*>(pGameObj->GetComponent(COMPONENT_ID::RENDERER));
}


void CParticleForm::OnChangeEditCtrl()
{
	UpdateData(TRUE);
	_pParticle->SetDuration((float)_ttof(_strDuration));
	_pParticle->SetLifeTime((float)_ttof(_strLifeTime));
	_pParticle->SetSpeed((float)_ttof(_strSpeed));
	_pParticle->SetSize((float)_ttof(_strSize));
	_pParticle->SetGravity((float)_ttof(_strGravity));
	_pParticle->SetEmitRate((float)_ttof(_strEmitRate));
	_pParticle->SetMaxParticles((float)_ttof(_strMax));
}


void CParticleForm::OnBnClickedBtnSelectcolor()
{
	if (_ColorDlg->DoModal() == IDOK)
	{
		COLORREF color = _ColorDlg->GetColor();
		_strR.Format(L"%u",GetRValue(color));
		_strG.Format(L"%u", GetGValue(color));
		_strB.Format(L"%u", GetBValue(color));
		UpdateData(FALSE);

		float value =(1.f / 255.f);
		float a = (float)_ttof(_strA) * value;
		float r = (float)_ttof(_strR)* value;
		float g = (float)_ttof(_strG)* value;
		float b = (float)_ttof(_strB)* value;

	//	D3DXCOLOR d3dColor = (a, r,g , b);
		_pParticle->SetColor(D3DXCOLOR( r, g, b,a));
	}
}

void CParticleForm::OnEnChangeEditColor()
{
	UpdateData(TRUE);
	float value = (1.f / 255.f);
	float a = (float)_ttof(_strA)*value ;
	float r = (float)_ttof(_strR);
	float g = (float)_ttof(_strG);
	float b = (float)_ttof(_strB);

//	_ColorDlg->SetCurrentColor(color);
	_ColorDlg->m_cc.rgbResult = RGB(r, g, b);

	_pParticle->SetColor(D3DXCOLOR(r * value, g * value, b * value, a));
}

void CParticleForm::OnCbnSelchangeShapecombo()
{
	int iCurSel = _ComboBox.GetCurSel();
	_pParticle->SetShap(iCurSel);
	ShowForm(iCurSel);
}

void CParticleForm::AllocForms()
{
	CCreateContext context;
	ZeroMemory(&context, sizeof(context));

	CRect rect;
	GetDlgItem(IDC_STATIC_RECT)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	_pBoxForm = new BoxForm();
	_pBoxForm->Create(NULL, NULL, WS_CHILD, rect, this, IDD_BoxForm,&context);
	_pBoxForm->OnInitialUpdate();
	_pBoxForm->ShowWindow(SW_HIDE);

	_pSphereForm = new SphereForm();
	_pSphereForm->Create(NULL, NULL, WS_CHILD, rect, this, IDD_SphereForm, &context);
	_pSphereForm->OnInitialUpdate();
	_pSphereForm->ShowWindow(SW_HIDE);

	_pConeForm = new ConeForm;
	_pConeForm->Create(NULL, NULL, WS_CHILD, rect, this, IDD_ConeForm, &context);
	_pConeForm->OnInitialUpdate();
	_pConeForm->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC_RECT)->DestroyWindow();
}

void CParticleForm::ShowForm(int idx)
{
	switch (idx)
	{
	case 0:
		_pBoxForm->ShowWindow(SW_SHOW);
		_pSphereForm->ShowWindow(SW_HIDE);
		_pConeForm->ShowWindow(SW_HIDE);
		break;
	case 1:
		_pBoxForm->ShowWindow(SW_HIDE);
		_pSphereForm->ShowWindow(SW_HIDE);
		_pConeForm->ShowWindow(SW_SHOW);
		break;
	case 2:
		_pBoxForm->ShowWindow(SW_HIDE);
		_pSphereForm->ShowWindow(SW_SHOW);
		_pConeForm->ShowWindow(SW_HIDE);
		break;
	}
}


void CParticleForm::OnBnClickedChkAwake()
{
	if (IsDlgButtonChecked(IDC_CHK_AWAKE))
		_pParticle->SetPlayOnAWake(true);
	else
		_pParticle->SetPlayOnAWake(false);
}

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
	ON_BN_CLICKED(IDC_BTN_SAVE, &CParticleForm::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CParticleForm::OnBnClickedBtnLoad)
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

void CParticleForm::OnBnClickedChkAwake()
{
	if (IsDlgButtonChecked(IDC_CHK_AWAKE))
		_pParticle->SetPlayOnAWake(true);
	else
		_pParticle->SetPlayOnAWake(false);
}

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
	_pParticle->SetShape(iCurSel);
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


void CParticleForm::OnBnClickedBtnSave()
{
	TCHAR szFilePath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szFilePath);
	PathRemoveFileSpec(szFilePath);
	lstrcat(szFilePath, L"\\Data\\Particle");

	CFileDialog Dlg(false, L".dat", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("DAT 파일 (*.dat)|*.dat|"),NULL);
	Dlg.m_ofn.lpstrInitialDir = szFilePath;

	if (Dlg.DoModal() == IDOK)
	{
		CString strFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(strFilePath, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD dwByte = 0;

		//Play on Awake
		bool awake = _pParticle->IsPlayOnAWake();
		WriteFile(hFile, &awake, sizeof(bool), &dwByte, nullptr);
		//Loop
		bool loop = _pParticle->IsLoop();
		WriteFile(hFile, &loop, sizeof(bool), &dwByte, nullptr);
		//Duration
		float duration = _pParticle->GetDuration();
		WriteFile(hFile, &duration, sizeof(float), &dwByte, nullptr);
		//Speed
		float speed = _pParticle->GetSpeed();
		WriteFile(hFile, &speed, sizeof(float), &dwByte, nullptr);
		//Gravity
		float gravity = _pParticle->GetGravity();
		WriteFile(hFile, &gravity, sizeof(float), &dwByte, nullptr);
		//EmitRate
		float emitRate = _pParticle->GetEmitRate();
		WriteFile(hFile, &emitRate, sizeof(float), &dwByte, nullptr);
		//MaxParticle
		int maxParticle = _pParticle->GetMaxParticles();
		WriteFile(hFile, &maxParticle, sizeof(int), &dwByte, nullptr);

		//Shape
		int shape = _pParticle->GetShape();
		WriteFile(hFile, &shape, sizeof(int), &dwByte, nullptr);
		//BoxSize
		D3DXVECTOR3 box = _pParticle->GetBoxSize();
		WriteFile(hFile, &box, sizeof(D3DXVECTOR3), &dwByte, nullptr);
		//Radius
		float radius = _pParticle->GetRadius();
		WriteFile(hFile, &radius, sizeof(float), &dwByte, nullptr);
		//Angle
		float angle = _pParticle->GetAngle();
		WriteFile(hFile, &angle, sizeof(float), &dwByte, nullptr);

		const PARTICLE_ATRRI* orign = _pParticle->GetOrign();
		//lifeTime
		float lifeTime = orign->_fLifeTime;
		WriteFile(hFile, &lifeTime, sizeof(float), &dwByte, nullptr);
		//Size
		float size = orign->_fSize;
		WriteFile(hFile, &size, sizeof(float), &dwByte, nullptr);
		//Color
		unsigned long color = orign->_dwColor;
		WriteFile(hFile, &color, sizeof(unsigned long), &dwByte, nullptr);
		/*
		//_fHeight
		TexturPath?
		*/

		CloseHandle(hFile);
	}

}

void CParticleForm::OnBnClickedBtnLoad()
{
	TCHAR szFilePath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szFilePath);
	PathRemoveFileSpec(szFilePath);
	lstrcat(szFilePath, L"\\Data\\Particle");

	CFileDialog Dlg(true, L".dat", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("DAT 파일 (*.dat)|*.dat|"), NULL);
	Dlg.m_ofn.lpstrInitialDir = szFilePath;

	if (Dlg.DoModal() == IDOK)
	{
		CString strFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(strFilePath, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD dwByte = 0;

		//Play on Awake
		bool awake;
		if (!ReadFile(hFile, &awake, sizeof(bool), &dwByte, nullptr))
			MessageBoxW( L"Failed", L"Play On Awake Load Error", MB_OK);
		_pParticle->SetPlayOnAWake(awake);
		CheckDlgButton(IDC_CHK_AWAKE, awake);
		//Loop
		bool loop;
		if (!ReadFile(hFile, &loop, sizeof(bool), &dwByte, nullptr))
			MessageBoxW(L"Failed", L"Loop Load Error", MB_OK);
		_pParticle->SetLoop(loop);
		CheckDlgButton(IDC_CHK_LOOP, loop);
		//Duration
		float duration;
		if (!ReadFile(hFile, &duration, sizeof(float), &dwByte, nullptr))
			MessageBoxW(L"Failed", L"Duration Load Error", MB_OK);
		_pParticle->SetDuration(duration);
		_strDuration.Format(_T("%.1f"), duration);
		//Speed
		float speed;
		if(!ReadFile(hFile, &speed, sizeof(float), &dwByte, nullptr))
			MessageBoxW(L"Failed", L"Speed Load Error", MB_OK);
		_pParticle->SetSpeed(speed);
		_strSpeed.Format(_T("%.2f"), speed);
		//Gravity
		float gravity = _pParticle->GetGravity();
		if(!ReadFile(hFile, &gravity, sizeof(float), &dwByte, nullptr))
			MessageBoxW(L"Failed", L"Gravity Load Error", MB_OK);
		_pParticle->SetGravity(gravity);
		_strGravity.Format(_T("%f"), gravity);
		//EmitRate
		float emitRate = _pParticle->GetEmitRate();
		if(!ReadFile(hFile, &emitRate, sizeof(float), &dwByte, nullptr))
			MessageBoxW(L"Failed", L"EmitRate Load Error", MB_OK);
		_pParticle->SetEmitRate(emitRate);
		_strEmitRate.Format(_T("%.1f"), emitRate);
		//MaxParticle
		int maxParticle;
		if(!ReadFile(hFile, &maxParticle, sizeof(int), &dwByte, nullptr))
			MessageBoxW(L"Failed", L"MaxParticles Load Error", MB_OK);
		_pParticle->SetMaxParticles(maxParticle);
		_strMax.Format(_T("%d"), maxParticle);

		//Shape
		int shape;
		if(!ReadFile(hFile, &shape, sizeof(int), &dwByte, nullptr))
			MessageBoxW(L"Failed", L"Shape Load Error", MB_OK);
		_pParticle->SetShape(shape);
		_ComboBox.SetCurSel(shape);
		ShowForm(shape);

		//BoxSize
		D3DXVECTOR3 box;
		if(!ReadFile(hFile, &box, sizeof(D3DXVECTOR3), &dwByte, nullptr))
			MessageBoxW(L"Failed", L"BoxSize Load Error", MB_OK);
		_pParticle->SetBoxSize(box);
		_pBoxForm->SetBoxSize(box.x, box.y, box.z);

		//Radius
		float radius;
		if(!ReadFile(hFile, &radius, sizeof(float), &dwByte, nullptr))
			MessageBoxW(L"Failed", L"Radius Load Error", MB_OK);
		_pParticle->SetRadius(radius);
		//Angle
		float angle;
		if(!ReadFile(hFile, &angle, sizeof(float), &dwByte, nullptr))
			MessageBoxW(L"Failed", L"Angle Load Error", MB_OK);
		_pParticle->SetAngle(angle);

		if (shape == 1) //Cone
		{
			_pConeForm->SetOption(radius, angle);
		}
		else if (shape == 2) //Sphere
		{
			_pSphereForm->SetRadius(radius);
		}

		//lifeTime
		float lifeTime;
		if(!ReadFile(hFile, &lifeTime, sizeof(float), &dwByte, nullptr))
			MessageBoxW(L"Failed", L"LifeTime Load Error", MB_OK);
		_pParticle->SetLifeTime(lifeTime);
		_strLifeTime.Format(_T("%.1f"), lifeTime);
		//Size
		float size;
		if(!ReadFile(hFile, &size, sizeof(float), &dwByte, nullptr))
			MessageBoxW(L"Failed", L"ParticleSize Load Error", MB_OK);
		_pParticle->SetSize(size);
		_strSize.Format(_T("%.3f"), size);
		//Color
		unsigned long color;
		if(!ReadFile(hFile, &color, sizeof(unsigned long), &dwByte, nullptr))
			MessageBoxW(L"Failed", L"Color Load Error", MB_OK);
		_pParticle->SetColor(color);

		D3DXCOLOR dxColor = (D3DXCOLOR)color;
		_strR.Format(_T("%d"),(int)(dxColor.r*255));
		_strG.Format(_T("%d"),(int)(dxColor.g * 255));
		_strB.Format(_T("%d"),(int)(dxColor.b * 255));
		_strA.Format(_T("%d"),(int)(dxColor.a * 255));

		/*
		//_fHeight
		TexturPath?
		*/

		UpdateData(FALSE);
		OnEnChangeEditColor();

		CloseHandle(hFile);

	}
}

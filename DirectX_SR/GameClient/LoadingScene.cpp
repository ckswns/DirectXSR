#include "pch.h"
#include "LoadingScene.h"
#include "ManagerDef.h"
#include "Image.h"
#include "GameObject.h"
#include "RectTransform.h"
#include "Transform.h"
#include "Animation.h"
#include "Animator.h"
#include "Button.h"
#include "Text.h"
#include "AudioAsset.h"
#include "AudioSource.h"
#include "AudioListener.h"
#include "TopBar.h"
#include "DbgShowFrame.h"

using namespace ce::UI;

LoadingScene::LoadingScene(void) noexcept
{

}

bool LoadingScene::Init(void) noexcept
{	
	_texBg = new ce::Texture();
	_texBg->Init(D3D9DEVICE->GetDevice(), "Asset/UI/black.png");

	_texProgressBarFront = new ce::Texture();
	_texProgressBarFront->Init(D3D9DEVICE->GetDevice(), "Asset/UI/slider_fill.png");

	_texProgressBarBack = new ce::Texture();
	_texProgressBarBack->Init(D3D9DEVICE->GetDevice(), "Asset/UI/slider_frame.png");

	GameObject* obj = GameObject::Instantiate();
	obj->AddComponent(new Image(_texBg));
	obj->SetSortOrder(0);

	RectTransform* rt = static_cast<RectTransform*>(obj->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
	rt->SetWidth(WINCX);
	rt->SetHeight(WINCY);

	_imgProgressFront = static_cast<Image*>(new Image(_texProgressBarFront));

	//obj = GameObject::Instantiate();
	//obj->AddComponent(new Text("test!!!!!", D3DCOLOR_ARGB(255, 255, 0, 0)));
	//rt = static_cast<RectTransform*>(obj->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
	//rt->SetWidth(100);
	//rt->SetHeight(30);
	//obj->SetSortOrder(10);
	//obj->GetTransform()->SetWorldPosition(100, 50, 0);


	obj = GameObject::Instantiate();
	obj->AddComponent(_imgProgressFront);
	obj->SetSortOrder(2);

	rt = static_cast<RectTransform*>(obj->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
	rt->SetPivot(D3DXVECTOR2(0.5f, 0.5f));
	rt->SetWidth(rt->GetWidth() * 0.35f);
	rt->SetHeight(rt->GetHeight() * 0.35f);
	obj->GetTransform()->SetWorldPosition(WINCX / 2, WINCY - 150, 0);

	obj = GameObject::Instantiate();
	obj->AddComponent(new Image(_texProgressBarBack));
	obj->SetSortOrder(1);

	rt = static_cast<RectTransform*>(obj->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
	rt->SetPivot(D3DXVECTOR2(0.5f, 0.5f));
	obj->GetTransform()->SetWorldPosition(WINCX / 2, WINCY - 150, 0);
	rt->SetWidth(rt->GetWidth() * 0.35f);
	rt->SetHeight(rt->GetHeight() * 0.35f);

	std::vector<float> vf;
	std::vector<Texture*> vt;

	for (int i = 1; i <= 15; i++)
	{
		char str[256];
		sprintf_s(str, 256, "Asset/UI/Logo/%d.png", i);
		_logo[i - 1] = new Texture();
		_logo[i - 1]->Init(D3D9DEVICE->GetDevice(), str);

		vf.push_back(0.05f);
		vt.push_back(_logo[i - 1]);
	}

	Animation* ani = new Animation(vf, vt, true);

	obj = GameObject::Instantiate();
	Image* img = static_cast<Image*>(obj->AddComponent(new Image(_logo[0])));
	//Button<LoadingScene>* btn = static_cast<Button<LoadingScene>*>(obj->AddComponent(new Button<LoadingScene>(this)));
	//btn->onMouseUp += &LoadingScene::Test;
	obj->SetSortOrder(3);

	Animator* animator =  static_cast<Animator*>(obj->AddComponent(new Animator(true)));
	ani->SetMaterial(img->GetMaterialPTR());
	animator->InsertAnimation("default", ani);

	rt = static_cast<RectTransform*>(obj->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
	rt->SetPivot(D3DXVECTOR2(0.5f, 0.5f));

	obj->GetTransform()->SetWorldPosition(WINCX / 2, WINCY / 3, 0);

	_imgLogo = static_cast<Image*>(obj->GetComponent(COMPONENT_ID::IMAGE));

	obj = GameObject::Instantiate();
	obj->AddComponent(new TopBar(g_hWnd));
	ASSETMANAGER->LoadAssetFolder("Asset");

	obj = GameObject::Instantiate();
	obj->AddComponent(new DbgShowFrame());
	obj->SetDontDestroy(true);
	return true;
}

void LoadingScene::FixedUpdate(float fElapsedTime) noexcept
{

}

void LoadingScene::Update(float fElapsedTime) noexcept
{
	_imgProgressFront->SetFillAmount(ASSETMANAGER->GetLoadingProgress());

	if (!ASSETMANAGER->GetLoadingState())
	{
		GAMEDATAMANAGER->Init();
		SCENEMANAGER->LoadScene("Town_01");
	}
}

void LoadingScene::LateUpdate(float fElapsedTime) noexcept
{

}

void LoadingScene::Render(float fElapsedTime) noexcept
{

}

void LoadingScene::Release(void) noexcept
{
	if (_texProgressBarBack)
	{
		_texProgressBarBack->Release();
		delete _texProgressBarBack;
		_texProgressBarBack = nullptr;
	}

	if (_texProgressBarFront)
	{
		_texProgressBarFront->Release();
		delete _texProgressBarFront;
		_texProgressBarFront = nullptr;
	}

	if (_texBg)
	{
		_texBg->Release();
		delete _texBg;
		_texBg = nullptr;
	}
	for (int i = 0; i < 15; i++)
	{
		if (_logo[i])
		{
			_logo[i]->Release();
			delete _logo[i];
			_logo[i] = nullptr;
		}
	}
}

//void LoadingScene::Test(void) noexcept
//{
//	GameObject* obj = GameObject::Instantiate();
//	AudioSource* as = static_cast<AudioSource*>(obj->AddComponent(new AudioSource()));
//	as->LoadAudio(ASSETMANAGER->GetAudioData("Asset\\Audio\\DiabloInit.wav"));
//	as->SetLoop(true);
//	as->Play();
//}

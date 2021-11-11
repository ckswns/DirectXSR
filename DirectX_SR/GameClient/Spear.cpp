#include "pch.h"
#include "Spear.h"
#include "Transform.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Animation.h"
#include "SpearTrail.h"
//Spear::Spear(D3DXVECTOR3 dir) noexcept
//	:_fMaxDist(7.f), _fDist(0), _fSpeed(3.f), _vDir(dir)
//{	__noop;	}

void Spear::Start(void) noexcept
{
	//_pTrans = GetGameObject()->GetTransform();
	//_vDir -= _pTrans->GetWorldPosition();
	//D3DXVec3Normalize(&_vDir, &_vDir);

	Texture* _texture = new ce::Texture();
	_texture->Init(D3D9DEVICE->GetDevice(), "Asset/Player/BoneSpear/Spear/0.png");

	SpriteRenderer* sr = new SpriteRenderer(D3D9DEVICE->GetDevice(), _texture);
	GetGameObject()->AddComponent(sr);

	Animator* pAnimator = new Animator(true);
	GetGameObject()->AddComponent(pAnimator);

	std::vector<Texture*> TList;
	std::vector<float>		FrameTime;
	Animation* ani;
	//Spear
	for (int i = 0; i < 6; i++)
	{
		char str[256];
		sprintf_s(str, 256, "Asset/Player/BoneSpear/Spear/%d.png", i);
		_texture = new Texture();
		_texture->Init(D3D9DEVICE->GetDevice(), str);

		TList.push_back(_texture);
		FrameTime.push_back(0.1f);
	}

	ani = new Animation(FrameTime, TList, true);
	ani->SetMaterial(sr->GetMaterialPTR());
	pAnimator->InsertAnimation("Spear", ani);

	TList.clear();
	FrameTime.clear();

	//GameObject* pTrail = GameObject::Instantiate();
	//pTrail->AddComponent(new SpearTrail());
	//pTrail->GetTransform()->SetParent(GetGameObject()->GetTransform());
	//pTrail->GetTransform()->SetLocalPosition(-_vDir);
}

void Spear::Update(float fElapsedTime) noexcept
{
	
}



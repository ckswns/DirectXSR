#include "pch.h"
#include "Skeleton.h"
#include "Transform.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Animation.h"

Skeleton::Skeleton() noexcept
	:_tStat(70,10,5)
{
}

void Skeleton::Start(void) noexcept
{
	_bOnce = false;

	_pTrans = static_cast<Transform*>(GetGameObject()->GetTransform());

	SpriteRenderer* sr = new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Player\\Skeleton.png"));
	gameObject->AddComponent(sr);

	_pAnimator = new Animator(false);
	gameObject->AddComponent(_pAnimator);
	InitAnimation(sr);
}

void Skeleton::Update(float fElapsedTime) noexcept
{
	if (_bOnce)
	{
		if (_pAnimator->GetCurrentAnimationEnd())
		{
			_pAnimator->Play("Stand");
			_bOnce = false;
		}
	}

	if (_bDestroy)
	{
		if (_pAnimator->GetCurrentAnimationEnd())
		{
			GetGameObject()->SetActive(false);
		}
	}

	//플레이어와 거리확인
	D3DXVECTOR3 vDir = _pOwnerTrans->GetWorldPosition() - _pTrans->GetWorldPosition();
	if (D3DXVec3Length(&vDir) >= 10.f)
	{
		//많이 멀어진 경우 주변으로 순간이동 
		float fX = CE_MATH::Random(-2,2) + _pOwnerTrans->GetWorldPosition().x;
		float fZ = CE_MATH::Random(-2,2) + _pOwnerTrans->GetWorldPosition().z;

		_pTrans->SetWorldPosition(fX, _pOwnerTrans->GetWorldPosition().y, fZ);
	}

	//돌아다님
	//몬스터 발견 시 공격(죽일때까지 공격)

}

void Skeleton::Create(Transform* trans)
{
	_pOwnerTrans = trans;
	GetGameObject()->SetActive(true);
	_bOnce = true;
	_pAnimator->Play("Create");
}

void Skeleton::Destroy()
{
	_bDestroy = true;
	_pAnimator->Play("Dead");
}

void Skeleton::InitAnimation(SpriteRenderer* sr)
{
	std::vector<Texture*> TList;
	std::vector<float>		FrameTime;
	Texture* _pTexture;
	Animation* ani;

	//Create
	{
		for (int i = 0; i < 10; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Player\\Skill\\Skeleton\\stand_8\\00%d.bmp", i);
			//sprintf_s(str, 256, "Asset\\Player\\Skill\\Skeleton\\create\\%d.tga", i);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.1f);
		}

		ani = new Animation(FrameTime, TList, false);
		ani->SetMaterial(sr->GetMaterialPTR());
		_pAnimator->InsertAnimation("Create", ani);

		TList.clear();
		FrameTime.clear();
	}

	//Stand
	{
		for (int i = 0; i < 8; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Player\\Skill\\Skeleton\\stand_8\\stand_%d.png", i);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.5f);
		}

		ani = new Animation(FrameTime, TList, true);
		ani->SetMaterial(sr->GetMaterialPTR());
		_pAnimator->InsertAnimation("Stand", ani);

		TList.clear();
		FrameTime.clear();
	}

	//Walk
	{
		for (int i = 0; i < 8; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Player\\Skill\\Skeleton\\walk_8\\%d.png", i);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.1f);
		}

		ani = new Animation(FrameTime, TList, true);
		ani->SetMaterial(sr->GetMaterialPTR());
		_pAnimator->InsertAnimation("Walk", ani);

		TList.clear();
		FrameTime.clear();
	}

	//Attack
	{
		for (int i = 0; i < 16; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Player\\Skill\\Skeleton\\attack_8\\%d.png", i);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.1f);
		}

		ani = new Animation(FrameTime, TList, false);
		ani->SetMaterial(sr->GetMaterialPTR());
		_pAnimator->InsertAnimation("Attack", ani);

		TList.clear();
		FrameTime.clear();
	}
	//Dead
	{
		for (int i = 0; i < 19; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Player\\Skill\\Skeleton\\death\\%d.png", i);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.1f);
		}

		ani = new Animation(FrameTime, TList, false);
		ani->SetMaterial(sr->GetMaterialPTR());
		_pAnimator->InsertAnimation("Dead", ani);

		TList.clear();
		FrameTime.clear();
	}
}
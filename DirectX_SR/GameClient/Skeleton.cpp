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

	Texture* _texture = new ce::Texture();
	_texture->Init(D3D9DEVICE->GetDevice(), "Asset/Player/Skeleton.png");

	SpriteRenderer* sr = new SpriteRenderer(D3D9DEVICE->GetDevice(), _texture);
	GetGameObject()->AddComponent(sr);

	_pAnimator = new Animator(false);
	GetGameObject()->AddComponent(_pAnimator);
	SetAnimation(sr);
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

	//�÷��̾�� �Ÿ�Ȯ��
	D3DXVECTOR3 vDir = _pOwnerTrans->GetWorldPosition() - _pTrans->GetWorldPosition();
	if (D3DXVec3Length(&vDir) >= 10.f)
	{
		//���� �־��� ��� �ֺ����� �����̵� 
		float fX = CE_MATH::Random(-3,3) + _pOwnerTrans->GetWorldPosition().x;
		float fZ = CE_MATH::Random(-3,3) + _pOwnerTrans->GetWorldPosition().z;

		_pTrans->SetWorldPosition(fX, _pOwnerTrans->GetWorldPosition().y, fZ);
	}

	//���ƴٴ�
	//���� �߰� �� ����(���϶����� ����)

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

void Skeleton::SetAnimation(SpriteRenderer* sr)
{
	std::vector<Texture*> TList;
	std::vector<float>		FrameTime;
	Texture* _pTexture;
	Animation* ani;

	//Create
	{
		for (int i = 0; i < 12; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset/Player/Skeleton/create/%d.png", i);
			_pTexture = new Texture();
			_pTexture->Init(D3D9DEVICE->GetDevice(), str);

			TList.push_back(_pTexture);
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
			sprintf_s(str, 256, "Asset/Player/Skeleton/stand_8/stand_%d.png", i);
			_pTexture = new Texture();
			_pTexture->Init(D3D9DEVICE->GetDevice(), str);

			TList.push_back(_pTexture);
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
			sprintf_s(str, 256, "Asset/Player/Skeleton/walk_8/%d.png", i);
			_pTexture = new Texture();
			_pTexture->Init(D3D9DEVICE->GetDevice(), str);

			TList.push_back(_pTexture);
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
			sprintf_s(str, 256, "Asset/Player/Skeleton/attack_8/%d.png", i);
			_pTexture = new Texture();
			_pTexture->Init(D3D9DEVICE->GetDevice(), str);

			TList.push_back(_pTexture);
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
			sprintf_s(str, 256, "Asset/Player/Skeleton/death/%d.png", i);
			_pTexture = new Texture();
			_pTexture->Init(D3D9DEVICE->GetDevice(), str);

			TList.push_back(_pTexture);
			FrameTime.push_back(0.1f);
		}

		ani = new Animation(FrameTime, TList, false);
		ani->SetMaterial(sr->GetMaterialPTR());
		_pAnimator->InsertAnimation("Dead", ani);

		TList.clear();
		FrameTime.clear();
	}
}
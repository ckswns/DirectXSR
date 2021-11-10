#include "pch.h"
#include "Player.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Quad.h"
#include "Texture.h"
#include "Animation.h"
#include "Animator.h"
#include "Skill.h"

void Player::Start(void) noexcept
{
	_bAtt = false;
	_bMove = false;

	_fSpeed = 5.f;
	_fRunSpeed = _fSpeed + 2.f;

	_pSkills.resize(SKILL_END);

	_pTrans = static_cast<Transform*>(GetGameObject()->GetTransform());

	Quad* quad = new Quad(4, 4);
	quad->Open(D3D9DEVICE->GetDevice());
	MeshRenderer* mr = new MeshRenderer(D3D9DEVICE->GetDevice(), quad);
	GetGameObject()->AddComponent(mr);

	_pAnimator = new Animator(true);
	GetGameObject()->AddComponent(_pAnimator);
	SetAnimation(mr);
}

void Player::Update(float fElapsedTime) noexcept
{
	if (_bMove)
	{
		D3DXVECTOR3 vDir = _vDest - _pTrans->GetWorldPosition();

		if (D3DXVec3Length(&vDir) <= 1.f)
		{
			_bMove = false;
			_pAnimator->SetAnimation("Stand");
			if (_bAtt)
				Attack(_vDest);
		}
		else 
		{
			D3DXVec3Normalize(&vDir, &vDir);

			_pTrans->Translate(vDir * _fSpeed* fElapsedTime);
		}
	}
}

void Player::SetAnimation(MeshRenderer* mr)
{
	std::vector<Texture*> TList;
	std::vector<float>		FrameTime;
	Texture* _pTexture;
	Animation* ani;

	//Stand
	{
		for (int i = 0; i < 8; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset/Player/stand_8/%d.png", i);
			_pTexture = new Texture();
			_pTexture->Init(D3D9DEVICE->GetDevice(), str);

			TList.push_back(_pTexture);
			FrameTime.push_back(0.5f);
		}

		ani = new Animation(FrameTime, TList, true);
		ani->SetMaterial(mr->GetMaterialPTR());
		_pAnimator->InsertAnimation("Stand", ani);

		TList.clear();
		FrameTime.clear();
	}

	//Walk
	{
		for (int i = 0; i < 8; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset/Player/walk_8/%d.png", i);
			_pTexture = new Texture();
			_pTexture->Init(D3D9DEVICE->GetDevice(), str);

			TList.push_back(_pTexture);
			FrameTime.push_back(0.1f);
		}

		ani = new Animation(FrameTime, TList, true);
		ani->SetMaterial(mr->GetMaterialPTR());
		_pAnimator->InsertAnimation("Walk", ani);

		TList.clear();
		FrameTime.clear();
	}

	//Attack
	{
		for (int i = 0; i < 19; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset/Player/attack_8/%d.png", i);
			_pTexture = new Texture();
			_pTexture->Init(D3D9DEVICE->GetDevice(), str);

			TList.push_back(_pTexture);
			FrameTime.push_back(0.1f);
		}

		ani = new Animation(FrameTime, TList, true);
		ani->SetMaterial(mr->GetMaterialPTR());
		_pAnimator->InsertAnimation("Attack", ani);

		TList.clear();
		FrameTime.clear();
	}
}

void Player::UsingSkill(SKILL_ID id)
{
	_pSkills[id]->Using();
}

void Player::Attack(D3DXVECTOR3 _vMonsterPos)
{	
	_bAtt = true;

//적과 거리가 가까운가?
	D3DXVECTOR3 vDir = _vMonsterPos - _pTrans->GetWorldPosition();
	if (D3DXVec3Length(&vDir) <= 2.f)
	{
		// >> 공격
		// 공격 애니메이션
		
		_pAnimator->SetAnimation("Attack");
		// 소리 
		//충돌판정
	}
	else 
	{
		_vDest = _vMonsterPos;
		_bMove = true;
		_pAnimator->SetAnimation("Walk");
	}

}

void Player::Move(D3DXVECTOR3 dest)
{
	_bAtt = false;
	_vDest = dest; 
	_bMove = true;
	_pAnimator->SetAnimation("Walk");
}
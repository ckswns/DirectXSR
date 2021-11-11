#include "pch.h"
#include "Player.h"

#include "Transform.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "Animation.h"
#include "Animator.h"

#include "PathFinding.h"
#include "Node.h"

#include "Skill.h"
#include "RaiseSkeleton.h"
#include "BoneSpear.h"

Player::Player(PathFinding* pf) noexcept
	:_pPathFinding(pf) 
{
	_tStat = new STAT(100, 100, 50);
}

void Player::Start(void) noexcept
{
	_bAtt = false;
	_bMove = false;
	_bFind = false;

	_bRun = false;
	_fSpeed =3.f;
	_fRunSpeed = 5.f;

	_pSkills.reserve(SKILL_END);
	_pSkills.push_back(new RaiseSkeleton());
	_pSkills.push_back(new BoneSpear());

	GetGameObject()->SetDontDestroy(true);

	_pTrans = static_cast<Transform*>(GetGameObject()->GetTransform());

	/*Quad* quad = new Quad(4, 4);
	quad->Open(D3D9DEVICE->GetDevice());
	MeshRenderer* mr = new MeshRenderer(D3D9DEVICE->GetDevice(), quad);
	GetGameObject()->AddComponent(mr);*/

	Texture* _texture = new ce::Texture();
	_texture->Init(D3D9DEVICE->GetDevice(), "Asset/Player/Player.png");

	SpriteRenderer* sr = new SpriteRenderer(D3D9DEVICE->GetDevice(), _texture);
	GetGameObject()->AddComponent(sr);

	_pAnimator = new Animator(true);
	GetGameObject()->AddComponent(_pAnimator);
	SetAnimation(sr);
}

void Player::Update(float fElapsedTime) noexcept
{
	if (INPUT->GetKeyDown('Z') || INPUT->GetKeyStay('Z'))
	{
		_bRun = true;
	}
	else 
	{
		if(_bRun)
			_bRun = false;
	}

	if (_bMove)
	{
		if (_bFind) 
		{
			if (!_pPath.empty())
			{
				std::list<Node*>::iterator iter = _pPath.begin();

				D3DXVECTOR3 vDir = (*iter)->GetPos() - _pTrans->GetWorldPosition();
				vDir.y = 0;

				if (D3DXVec3Length(&vDir) < 1.f)
				{
					_pPath.pop_front();
				}
				else
				{
					D3DXVec3Normalize(&vDir, &vDir);

					if (_bRun) 
					{
						//���¹̳� ������ ����
						if (_tStat->_fStamina > 0)
							_tStat->_fStamina -= fElapsedTime;
	
						if (_tStat->_fStamina <= 0)
						{
							_tStat->_fStamina = 0;
							vDir *= (_fSpeed * fElapsedTime);
						}
						else
							vDir *= (_fRunSpeed * fElapsedTime);
					}
					else
					{
						vDir *= (_fSpeed * fElapsedTime);
					}

					_pTrans->Translate(vDir );
				}
			}
			else
			{
				_pPath.clear();

				_bFind = false;
				_bMove = false;
				_pAnimator->SetAnimation("Stand");
				if (_bAtt)
					Attack(_vDest);
			}
		}
		/*
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
		*/
	}
}

void Player::SetAnimation(SpriteRenderer* sr)
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
			sprintf_s(str, 256, "Asset/Player/walk_8/%d.png", i);
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
		ani->SetMaterial(sr->GetMaterialPTR());
		_pAnimator->InsertAnimation("Attack", ani);

		TList.clear();
		FrameTime.clear();
	}
}

void Player::UsingSkill(SKILL_ID id, D3DXVECTOR3 vPos)
{
	for (auto pSkill : _pSkills)
	{
		if (pSkill->GetSkillID() == id)
		{
			if (_tStat->_iMP >= pSkill->GetUsingMp())
				pSkill->Using(vPos, _pTrans);

			break;
		}
	}
//	_pSkills[id]->Using(vPos,_pTrans);
}

void Player::Attack(D3DXVECTOR3 _vMonsterPos)
{	
	_bAtt = true;

//���� �Ÿ��� ����?
	D3DXVECTOR3 vDir = _vMonsterPos - _pTrans->GetWorldPosition();
	if (D3DXVec3Length(&vDir) <= 2.f)
	{
		// >> ����
		// ���� �ִϸ��̼�
		_pAnimator->SetAnimation("Attack");
		// �Ҹ� 
		//�浹����
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

	_bFind =_pPathFinding->FindPath(_pTrans->GetWorldPosition(),dest);
	_pPath = (_pPathFinding->GetPath());
}
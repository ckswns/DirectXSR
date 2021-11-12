#include "pch.h"
#include "Player.h"

#include "Transform.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "Animation.h"
#include "Animator.h"
#include "AudioListener.h"

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

	GetGameObject()->AddComponent(new AudioListener());

	SpriteRenderer* sr = new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Player\\Player.png"));
	GetGameObject()->AddComponent(sr);

	_pAnimator = new Animator(true);
	GetGameObject()->AddComponent(_pAnimator);
	InitAnimation(sr);
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
						//스태미나 게이지 감소
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
	}
}

void Player::OnDestroy(void) noexcept
{
	delete _tStat;
	_tStat = nullptr;

	for (size_t i = 0; i < _pSkills.size(); ++i)
	{
		if (_pSkills[i] != nullptr)
		{
			delete _pSkills[i];
			_pSkills[i] = nullptr;
		}
	}
}

void Player::InitAnimation(SpriteRenderer* sr)
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
			sprintf_s(str, 256, "Asset\\Player\\stand_8\\%d.png", i);

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
			sprintf_s(str, 256, "Asset\\Player\\walk_8\\%d.png", i);

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
		for (int i = 0; i < 19; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Player\\attack_8\\%d.png", i);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
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
			int SkillMp = pSkill->GetUsingMp();
			if (_tStat->_iMP >= SkillMp)
			{
				pSkill->Using(vPos, _pTrans);
				_tStat->_iMP -= SkillMp;
			}
			break;
		}
	}
//	_pSkills[id]->Using(vPos,_pTrans);
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

	_bFind =_pPathFinding->FindPath(_pTrans->GetWorldPosition(),dest);
	_pPath = (_pPathFinding->GetPath());
}

float Player::GetHPPer()
{
	float per = 1.f / (_tStat->_fMaxHp);
	per *= _tStat->_fHp;
	return per;
}

float Player::GetMPPer()
{
	float per = 1.f / (_tStat->_iMaxMp);
	per *= _tStat->_iMP;
	return per;
}

float Player::GetStaminaPer()
{
	float per = 1.f / (_tStat->_fMaxStamina);
	per *= _tStat->_fStamina;
	return per;
}

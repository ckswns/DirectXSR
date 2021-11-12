#include "pch.h"
#include "Player.h"

#include "Transform.h"
#include "SpriteRenderer.h"
#include "Animation.h"
#include "Animator.h"
#include "AudioListener.h"

#include "PathFinding.h"
#include "FSMState.h"
#include "PlayerStand.h"
#include "PlayerMove.h"
#include "PlayerAttack.h"

#include "Skill.h"
#include "RaiseSkeleton.h"
#include "BoneSpear.h"

Player::Player(PathFinding* pf) noexcept
	:_pPathFinding(pf),_eCurState(PLAYER_END)
{
	_tStat = new STAT(100, 100, 50);

	_pSkills.reserve(SKILL_END);
	_pSkills.push_back(new RaiseSkeleton());
	_pSkills.push_back(new BoneSpear());
}

void Player::Start(void) noexcept
{
	_bAtt = false;
	_bMove = false;

	_bRun = false;
	_fSpeed =3.f;
	_fRunSpeed = 5.f;

	GetGameObject()->SetDontDestroy(true);

	_pTrans = static_cast<Transform*>(GetGameObject()->GetTransform());

	GetGameObject()->AddComponent(new AudioListener());

	SpriteRenderer* sr = new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Player\\Player.png"));
	GetGameObject()->AddComponent(sr);

	_pAnimator = new Animator(true);
	GetGameObject()->AddComponent(_pAnimator);
	InitAnimation(sr);

	InitState();
	SetState(PLAYER_STAND);
}

void Player::Update(float fElapsedTime) noexcept
{
	_pFSM[_eCurState]->Update(fElapsedTime);
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
	_pSkills.clear();

	for (size_t i = 0; i < _pFSM.size(); ++i)
	{
		if (_pFSM[i] != nullptr)
		{
			delete _pFSM[i];
			_pFSM[i] = nullptr;
		}
	}
	_pFSM.clear();
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

		ani = new Animation(FrameTime, TList);
		ani->SetMaterial(sr->GetMaterialPTR());
		_pAnimator->InsertAnimation("Attack", ani);

		TList.clear();
		FrameTime.clear();
	}
}

void Player::InitState()
{
	_pFSM.reserve(PLAYER_END);
	_pFSM.push_back(new PlayerStand(_pAnimator));
	_pFSM.push_back(new PlayerMove(this,_pAnimator, _pTrans, _pPathFinding, _fSpeed));
	_pFSM.push_back(new PlayerAttack(this,_pAnimator, _pTrans));
}

void Player::SetState(PLAYER_STATE newState, D3DXVECTOR3 vTarget, bool bAtt)
{
	_eCurState = newState;
	
	if (vTarget != D3DXVECTOR3(0, -5, 0))
		_pFSM[_eCurState]->SetTarget(vTarget);

	if (bAtt)
	{
		static_cast<PlayerMove*>(_pFSM[_eCurState])->SetAtt();
	}

	_pFSM[_eCurState]->Start();
	
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
}

bool Player::IsRunning(float fElapsedTime)
{
	float after = _tStat->_fStamina - (fElapsedTime * _fRunSpeed);
	if (after < 0) 
	{
		//_tStat->_fStamina = 0;
		return false;
	}
	_tStat->_fStamina = after;
	return true;
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

#include "pch.h"
#include "Player.h"

#include "Transform.h"
#include "SpriteRenderer.h"
#include "Material.h"
#include "Animation.h"
#include "Animator.h"
#include "BoxCollider.h"
#include "AudioListener.h"
#include "BoxCollider.h"

#include "PathFinding.h"
#include "PlayerFSMState.h"
#include "PlayerStand.h"
#include "PlayerMove.h"
#include "PlayerAttack.h"
#include "PlayerSkill.h"

#include "Skill.h"
#include "RaiseSkeleton.h"
#include "BoneSpear.h"

Player::Player(PathFinding* pf) noexcept
	:_pPathFinding(pf), _eCurState(PLAYER_END), _bFPV(false)
{
	_tStat = new STAT(100, 100, 50);

	_pSkills.reserve(SKILL_END);
	_pSkills.push_back(new RaiseSkeleton());
	_pSkills.push_back(new BoneSpear());

	static_cast<RaiseSkeleton*>(_pSkills[RAISE_SKELETON])->SetPathFinding(pf);
}

void Player::Start(void) noexcept
{
	_fRecovery = 1.f;

	_fSpeed =3.f;
	_fRunSpeed = 5.f;

	GetGameObject()->SetDontDestroy(true);

	_pTrans = static_cast<Transform*>(GetGameObject()->GetTransform());

	//gameObject->AddComponent(new AudioListener());
	_pCollider = new BoxCollider(D3DXVECTOR3(1, 1, 0.5f));
	gameObject->AddComponent(_pCollider);

	SpriteRenderer* sr = new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Player\\Player.png"));
	gameObject->AddComponent(sr);

	_pAnimator = new Animator(true);
	gameObject ->AddComponent(_pAnimator);
	InitAnimation(sr);

	InitState();
	SetState(PLAYER_STAND,FRONT);
}

void Player::Update(float fElapsedTime) noexcept
{
	_pFSM[_eCurState]->Update(fElapsedTime);

	_tStat->Recovery(_fRecovery * fElapsedTime);
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
	std::vector<float>	FrameTime;
	Material* material = sr->GetMaterialPTR();
	Animation* ani;

	for (int folder = 0; folder < 15; folder += 2) {

		//Stand
		for (int i = 0; i < 8; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Player\\stand_%d\\%d.png", folder, i);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.5f);
		}

		ani = new Animation(FrameTime, TList, true);
		ani->SetMaterial(material);
		std::string name = "Stand_" + std::to_string(folder);
		_pAnimator->InsertAnimation(name, ani);

		TList.clear();
		FrameTime.clear();

		//Walk
		for (int i = 0; i < 8; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Player\\walk_%d\\%d.png",folder, i);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.07f);
		}

		ani = new Animation(FrameTime, TList, true);
		ani->SetMaterial(material);
		_pAnimator->InsertAnimation("Walk_" + std::to_string(folder), ani);

		TList.clear();
		FrameTime.clear();

		//Run
		for (int i = 0; i < 8; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Player\\dash_%d\\%d.png", folder, i);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.05f);
		}

		ani = new Animation(FrameTime, TList, true);
		ani->SetMaterial(material);
		_pAnimator->InsertAnimation("Run_" + std::to_string(folder), ani);

		TList.clear();
		FrameTime.clear();

		//Attack
		for (int i = 0; i < 19; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Player\\attack_%d\\%d.png",folder, i);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.1f);
		}

		ani = new Animation(FrameTime, TList);
		ani->SetMaterial(material);
		_pAnimator->InsertAnimation("Attack_" + std::to_string(folder), ani);

		TList.clear();
		FrameTime.clear();

		//Skill
		for (int i = 0; i < 16; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Player\\skill_%d\\%d.png", folder, i);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.1f);
		}

		ani = new Animation(FrameTime, TList);
		ani->SetMaterial(material);
		_pAnimator->InsertAnimation("Skill_" + std::to_string(folder), ani);

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
	_pFSM.push_back(new PlayerSkill(this, _pAnimator, _pTrans));
}

void Player::SetFPV()
{
	//1ÀÎÄª > 3ÀÎÄª
	if (_bFPV)
	{
		_bFPV = false;
		_pTrans->SetLocalEulerAngle(0, 0, 0);
	}
	else //3ÀÎÄª > 1ÀÎÄª
	{
		SetState(_eCurState, BACK);
		_pFSM[_eCurState]->Start();
		_bFPV = true;
	}

	for (int i = 0; i < PLAYER_END; i++)
	{
		if(_bFPV)
			_pFSM[i]->SetDir(BACK);

		_pFSM[i]->SetFPV(_bFPV);
	}
		
}

void Player::SetState(PLAYER_STATE newState,DIR eDir,D3DXVECTOR3 vTarget, bool bAtt)
{
	if (vTarget != D3DXVECTOR3(0, -5, 0))
		_pFSM[newState]->SetTarget(vTarget);

	if (bAtt)
	{
		static_cast<PlayerMove*>(_pFSM[newState])->SetAtt();
	}

	/*if(!_bFPV)
		_pFSM[newState]->SetDir(eDir);
	
	if (_eCurState != newState) 
	{
		_eCurState = newState;
		_pFSM[_eCurState]->Start();
	}*/

	if (!_bFPV)
	{
		_pFSM[newState]->SetDir(eDir);

		_eCurState = newState;
		_pFSM[_eCurState]->Start();
	}
	else if (_eCurState != newState)
	{
		_eCurState = newState;
		_pFSM[_eCurState]->Start();
	}


}

void Player::UsingSkill(SKILL_ID id, D3DXVECTOR3 vPos)
{
	for (auto pSkill : _pSkills)
	{
		if (pSkill->GetSkillID() == id)
		{
			int SkillMp = pSkill->GetUsingMp();
			if (_tStat->_fMP >= SkillMp)
			{
				SetState(PLAYER_SKILL, DIR_END, vPos);
				pSkill->Using(vPos, _pTrans,_bFPV);
			//	_tStat->_fMP -= SkillMp;
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
	float per = 1.f / (_tStat->_fMaxMp);
	per *= _tStat->_fMP;
	return per;
}

float Player::GetStaminaPer()
{
	float per = 1.f / (_tStat->_fMaxStamina);
	per *= _tStat->_fStamina;
	return per;
}

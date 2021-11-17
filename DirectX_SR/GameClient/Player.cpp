#include "pch.h"
#include "Player.h"

#include "Transform.h"
#include "SpriteRenderer.h"
#include "Material.h"
#include "Animation.h"
#include "Animator.h"
#include "SphereCollider.h"
#include "Rigidbody.h"
#include "AudioListener.h"
#include "AudioSource.h"

#include "PathFinding.h"
#include "InputHandler.h"

#include "PlayerFSMState.h"
#include "PlayerStand.h"
#include "PlayerMove.h"
#include "PlayerAttack.h"
#include "PlayerSkill.h"
#include "PlayerDamaged.h"

#include "Skill.h"
#include "RaiseSkeleton.h"
#include "BoneSpear.h"
#include "PoisonNova.h"

#include "Light.h"

Player::Player(PathFinding* pf) noexcept
	:_pPathFinding(pf), _eCurState(PLAYER_END), _bFPV(false)
{
	_tStat = new STAT(100, 100, 50);

	_pSkills.reserve(SKILL_END);
	_pSkills.push_back(new RaiseSkeleton());
	_pSkills.push_back(new BoneSpear());
	_pSkills.push_back(new PoisonNova());

	_pInputHandler = new InputHandler(this);
}

void Player::Start(void) noexcept
{
	_fRecovery = 1.f;

	_fSpeed =3.f;
	_fRunSpeed = 5.f;

	gameObject->SetDontDestroy(true);
	gameObject->SetTag(GameObjectTag::PLAYER);

	_pTrans = static_cast<Transform*>(GetGameObject()->GetTransform());
	_pInputHandler->Start();

	static_cast<RaiseSkeleton*>(_pSkills[RAISE_SKELETON])->SetPathFinding(_pPathFinding);

	gameObject->AddComponent(new AudioListener());
	_pAudioSource = new AudioSource();
	gameObject->AddComponent(_pAudioSource);
	_pManaSound[0] = ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Player\\INeedMana.mp3");
	_pManaSound[1] = ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Player\\MoreMana.mp3");
	_pManaSound[2] = ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Player\\LowMana.mp3");
	_pDamagedSound[0] = ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Player\\Damaged1.wav");
	_pDamagedSound[1] = ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Player\\Damaged2.wav");
	_pDamagedSound[2] = ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Player\\Damaged3.wav");

	_pCollider = new SphereCollider(0.3f, "hitbox");
	gameObject->AddComponent(_pCollider);
	gameObject->AddComponent(new Rigidbody());

	SpriteRenderer* sr = new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Player\\Player.png"),false);
	gameObject->AddComponent(sr);

	_pAnimator = new Animator(true);
	gameObject ->AddComponent(_pAnimator);
	InitAnimation(sr);

	D3DCOLORVALUE c;
	c.a = 1;
	c.r = 1;
	c.g = 1;
	c.b = 1;
	gameObject->AddComponent(new Light(Light::Type::POINT, D3D9DEVICE->GetDevice(), c, 20, 0, 0, 0.02f));
	gameObject->AddComponent(new Light(Light::Type::POINT, D3D9DEVICE->GetDevice(), c, 100, 2.f));

	InitState();
	SetState(PLAYER_STAND,FRONT);
}

void Player::FixedUpdate(float fElapsedTime) noexcept
{
	if(_bCollWithObstacle == false)
		_prevPos = transform->GetWorldPosition();

	_bCollWithObstacle = false;
}

void Player::Update(float fElapsedTime) noexcept
{
	_pInputHandler->Update(fElapsedTime);

	_pFSM[_eCurState]->Update(fElapsedTime);

	_tStat->Recovery(_fRecovery * fElapsedTime);
}

void Player::OnDestroy(void) noexcept
{
	delete _tStat;
	_tStat = nullptr;

	_pInputHandler->OnDestroy();
	delete _pInputHandler;
	_pInputHandler = nullptr;

	delete _pPathFinding;
	_pPathFinding = nullptr;

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

	for (int i = 0; i < 3; i++)
	{
		_pManaSound[i] = nullptr;
		_pDamagedSound[i] = nullptr;
	}
}

void Player::OnCollisionEnter(Collider* mine, Collider* other) noexcept
{
	if (other->GetGameObject()->GetTag() == GameObjectTag::OBSTACLE)
	{
		if (mine->GetTag() == "hitbox")
		{
			transform->SetWorldPosition(_prevPos);
			_bCollWithObstacle = true;
		}
	}
}

void Player::OnCollisionStay(Collider* mine, Collider* other) noexcept
{
	if (other->GetGameObject()->GetTag() == GameObjectTag::OBSTACLE)
	{
		if (mine->GetTag() == "hitbox")
		{
			transform->SetWorldPosition(_prevPos);
			_bCollWithObstacle = true;
		}
	}
}

void Player::OnCollisionExit(Collider* mine, Collider* other) noexcept
{

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
			FrameTime.push_back(0.3f);
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
			FrameTime.push_back(0.08f);
		}

		ani = new Animation(FrameTime, TList);
		ani->SetMaterial(material);
		_pAnimator->InsertAnimation("Skill_" + std::to_string(folder), ani);

		TList.clear();
		FrameTime.clear();

		//Damaged
		for (int i = 0; i < 7; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Player\\damage_%d\\%d.png", folder, i);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.08f);
		}

		ani = new Animation(FrameTime, TList);
		ani->SetMaterial(material);
		_pAnimator->InsertAnimation("Damaged_" + std::to_string(folder), ani);

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
	_pFSM.push_back(new PlayerDamaged(this, _pAnimator, _pTrans));
}

void Player::SetFPV()
{
	//1인칭>3인칭
	if (_bFPV)
	{
		_bFPV = false;
		_pTrans->SetLocalEulerAngle(0, 0, 0);
	}
	else //3인칭>1인칭
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

//stand,move,skill,Damaged
void Player::SetState(PLAYER_STATE newState,DIR eDir,D3DXVECTOR3 vTarget)
{
	if (vTarget != D3DXVECTOR3(0, -5, 0))
		_pFSM[newState]->SetTarget(vTarget);

	if (!_bFPV)
	{
		if(newState == PLAYER_MOVE)
			static_cast<PlayerMove*>(_pFSM[newState])->SetAtt(false);

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

//attack,move
void Player::SetState(PLAYER_STATE newState, Transform* targetTrans, bool bAtt)
{
	if (!_bFPV)
	{
		_pFSM[newState]->SetTargetTrans(targetTrans);

		if (bAtt)
			static_cast<PlayerMove*>(_pFSM[newState])->SetAtt(bAtt);
	
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
				_tStat->_fMP -= SkillMp;
			}
			else
			{
				int num = CE_MATH::Random(3);
				_pAudioSource->LoadAudio(_pManaSound[num]);
				_pAudioSource->Play();
			}
			break;
		}
	}
}

void Player::GetHit(float fDamage,D3DXVECTOR3 vPos)
{
	_tStat->_fHp -= fDamage;
	if (_tStat->_fHp < 0)
	{
		//죽음

		//다시시작 
	}
	else
	{
		int num = CE_MATH::Random(3);
		_pAudioSource->LoadAudio(_pDamagedSound[num]);
		_pAudioSource->Play();
		//피격 모션 vPos = 때린 몬스터 위치 
		SetState(PLAYER_DAMAGED,DIR_END, vPos);
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


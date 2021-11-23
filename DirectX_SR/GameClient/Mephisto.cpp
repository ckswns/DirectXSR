#include "pch.h"
#include "Mephisto.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "BillboardObj.h"
#include "SphereCollider.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Player.h"
#include "PathFinding.h"
#include "AudioSource.h"
#include "AudioAsset.h"
#include "MonsterHPBar.h"
#include "Lightning.h"
#include "Missile.h"
#include "AudioSource.h"


Mephisto::Mephisto(PathFinding* pf, D3DXVECTOR3 bornPos) noexcept
	:_pathFinder(pf), _bornPosition(bornPos),
	_dirtyState(false), _usingSkill(false), _fDeltaTime(0),
	_fAttackRange(1.5), _fLightningRange(4), _fMisslieRange(7),
	_fCoolDown(3), _bLightningCool(true)
{
}

void Mephisto::Awake(void) noexcept
{
	_state = Actor::State::IDLE;
	memcpy(&_data, &GAMEDATAMANAGER->GetActorData("Mephisto"), sizeof(Actor::Data));
}

void Mephisto::Start(void) noexcept
{
	gameObject->SetTag(GameObjectTag::MONSTER);

	_currentHP = _data.maxHP;

	_spriteRenderer = new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Mephisto\\Idle\\0\\0.png"));
	gameObject->AddComponent(_spriteRenderer);

	gameObject->AddComponent(new BillboardObj());
	_hitBox = static_cast<SphereCollider*>(gameObject->AddComponent(new SphereCollider(0.3f,"Monster")));
	gameObject->AddComponent(new Rigidbody());

	_animator = new Animator(true);
	InitAnimation();
	gameObject->AddComponent(_animator);

	GameObject* player = GameObject::FindObjectByTag(GameObjectTag::PLAYER);
	if (player == nullptr)
		CE_ASSERT("ckswns", "Player가 존재하지 않습니다.");
	_player = player->GetComponent<Player>(COMPONENT_ID::BEHAVIOUR);

	GameObject* lightningObj = GameObject::Instantiate();
	_lightning = new Lightning(_data.damageMin, _data.damageMax);
	lightningObj->AddComponent(_lightning);
	lightningObj->GetTransform()->SetParent(transform);
	lightningObj->SetActive(false);

	gameObject->GetTransform()->SetWorldPosition(_bornPosition);

	_pAudioSource = new AudioSource();
	gameObject->AddComponent(_pAudioSource);
	_pInitSound = ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Monster\\Mephisto\\Init.wav");
	_pDeathSound = ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Monster\\Mephisto\\death.wav");
	for (int i = 0; i < 4; i++) 
	{
		_pAttackSound[i] = ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Monster\\Mephisto\\attack"+ std::to_string(i+1) +".wav");
		_pDamagedSound[i] = ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Monster\\Mephisto\\gethit" + std::to_string(i+1) + ".wav");
	}


}

void Mephisto::FixedUpdate(float fElapsedTime) noexcept
{
	if (_bIntro)
	{
		if (_animator->GetCurrentAnimationEnd())
		{
			D3DXVECTOR3 pos = transform->GetWorldPosition();
			transform->SetWorldPosition(pos.x, 0.7f, pos.z);
			_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Idle_0")->GetTexture()[0]);
			_animator->SetAnimation("Idle_0");
			_bIntro = false;
		}
	}

	if (_bIntroDone == false)
		return;

	D3DXVECTOR3 vDir = _player->GetTransform()->GetWorldPosition() - transform->GetWorldPosition();
	float dis = D3DXVec3Length(&vDir);
	switch (_state)
	{
	case Actor::State::IDLE:
	
		if (dis < _fMisslieRange)
		{
			_state = Actor::State::ATTAK;
			_dirtyState = true;
			if (dis > _fAttackRange)
			{
				if (dis < _fLightningRange)
				{
					if (_bLightningCool)
						_usingSkill = true;
					else
					{
						_usingSkill = false;
						if (_pathFinder->FindPath(transform->GetWorldPosition(), _player->GetTransform()->GetWorldPosition()))
						{
							_state = Actor::State::MOVE;
							_dirtyState = true;
						}
					}
				}
				else
					_usingSkill = true;
			}
			else
				_usingSkill = false;
			break;
		}
		else if (dis <= _data.aggroDistance)
		{
			if (_pathFinder->FindPath(transform->GetWorldPosition(), _player->GetTransform()->GetWorldPosition()))
			{
				_state = Actor::State::MOVE;
				_dirtyState = true;
			}
		}
		break;
	case Actor::State::ATTAK:
		if (_animator->GetCurrentAnimationEnd())
		{
			_dirtyState = true;
			if (_usingSkill)
				_usingSkill = false;
			_state = Actor::State::IDLE;
		}
		break;
	case Actor::State::HIT:
		if (_animator->GetCurrentAnimationEnd())
		{
			_state = Actor::State::IDLE;
		}
		break;
	case Actor::State::DIE:
		if (_animator->GetCurrentAnimationEnd())
		{
			_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Dead")->GetTexture()[0]);
			_animator->SetAnimation("Dead");
			_state = Actor::State::END;
		}
		break;
	case Actor::State::MOVE:
		if (dis < _fMisslieRange)
		{
			_state = Actor::State::ATTAK;
			_dirtyState = true;
			if (dis > _fAttackRange)
			{
				if (dis < _fLightningRange)
				{
					if (_bLightningCool)
						_usingSkill = true;
					else 
					{
						_usingSkill = false;
						if (_pathFinder->FindPath(transform->GetWorldPosition(), _player->GetTransform()->GetWorldPosition()))
						{
							_state = Actor::State::MOVE;
							_dirtyState = true;
						}
					}
				}
				else
					_usingSkill = true;
			}
			else
				_usingSkill = false;
			break;
		}
		else if (dis <= _data.aggroDistance)
		{
			if (_pathFinder->FindPath(transform->GetWorldPosition(), _player->GetTransform()->GetWorldPosition()))
				_state = Actor::State::MOVE;
		}
		else if (_pathFinder->GetPath().empty())
		{
			_state = Actor::State::IDLE;
			_dirtyState = true;
		}
		break;
	
	}
}

void Mephisto::Update(float fElapsedTime) noexcept
{
	if (_bIntroDone == false)
		return;

	if (!_bLightningCool) 
	{
		if (_fDeltaTime >= _fCoolDown)
		{
			_fDeltaTime = _fCoolDown;
			_bLightningCool = true;
		}
		else
			_fDeltaTime += fElapsedTime;
	}

	switch (_state)
	{
	case Actor::State::IDLE:
		break;
	case Actor::State::MOVE:
		if (!_pathFinder->GetPath().empty())
		{
			D3DXVECTOR3 vDist = _player->GetTransform()->GetWorldPosition() - transform->GetWorldPosition();
			float dis = D3DXVec3Length(&vDist);
			if (dis > _data.aggroDistance)
			{
				_pathFinder->FindPath(transform->GetWorldPosition(), _bornPosition);
			}

			std::list<Node*>& path = const_cast<std::list<Node*>&>(_pathFinder->GetPath());

			if (path.begin() == path.end())
				return;

			std::list<Node*>::iterator iter = path.begin();

			D3DXVECTOR3 vDir = (*iter)->GetPos() - transform->GetWorldPosition();
			vDir.y = 0;

			Direction dir = GetDirect(transform->GetWorldPosition(), (*iter)->GetPos());
			int iDir = static_cast<int>(dir);

			if (_dir != dir)
				_animator->SetAnimation("Walk_" + std::to_string(iDir));

			_dir = dir;

			if (D3DXVec3Length(&vDir) < 0.1f)
			{
				path.pop_front();
				if (path.empty())
				{
					path.clear();
					_state = Actor::State::IDLE;
					_dirtyState = true;
				}
			}
			else
			{
				transform->Translate(vDir * _data.moveSpeed * fElapsedTime);
			}
		}
		break;
	case Actor::State::ATTAK:
	case Actor::State::HIT:
	case Actor::State::DIE:
		if (_animator->GetCurrentAnimationEnd())
			_bDeadAniDone = true;
	default:
		break;
	}
}

void Mephisto::LateUpdate(float fElapsedTime) noexcept
{
	if (_bIntroDone == false)
		return;

	if (_dirtyState == false)
		return;

	_dirtyState = false;

	switch (_state)
	{
	case Actor::State::IDLE:
		_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Idle_0")->GetTexture()[0]);
		_animator->SetAnimation("Idle_" + std::to_string(static_cast<int>(_dir)));
		break;
	case Actor::State::MOVE:
		_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Walk_0")->GetTexture()[0]);
		_animator->SetAnimation("Walk_" + std::to_string(static_cast<int>(_dir)));
		break;
	case Actor::State::ATTAK:
	{
		Direction dir = GetDirect(transform->GetWorldPosition(), _player->GetTransform()->GetWorldPosition());
		int iDir = static_cast<int>(dir);
		_dir = dir;
		if (_usingSkill)
		{
			_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Skill_0")->GetTexture()[0]);
			_animator->SetAnimation("Skill_" + std::to_string(static_cast<int>(_dir)));
		}
		else
		{
			_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Attack_0")->GetTexture()[0]);
			_animator->SetAnimation("Attack_" + std::to_string(static_cast<int>(_dir)));
		}
	}
	break;
	case Actor::State::HIT:
		_spriteRenderer->SetTexture(_animator->GetAnimationByKey("GetHit_0")->GetTexture()[0]);
		_animator->SetAnimation("GetHit_" + std::to_string(static_cast<int>(_dir)));
		break;
	case Actor::State::DIE:
		_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Death_0")->GetTexture()[0]);
		_animator->SetAnimation("Death_" + std::to_string(static_cast<int>(_dir)));
		break;
	default:
		break;
	}
}

void Mephisto::OnDestroy(void) noexcept
{
	if (MonsterHPBar::Instance()->GetMonster() == this)
	{
		MonsterHPBar::Instance()->SetMonster(nullptr);
	}
	if (_pathFinder)
	{
		delete _pathFinder;
		_pathFinder = nullptr;
	}
}

void Mephisto::GetHit(int damage) noexcept
{
	if (_state == Actor::State::DIE)
		return;

	_currentHP -= damage;

	if (_currentHP <= 0)
	{
		_pAudioSource->LoadAudio(_pDeathSound);
		_pAudioSource->Play();
		_state = Actor::State::DIE;
		_hitBox->SetEnable(false);
		_currentHP = 0;
		_dirtyState = true;

		if (MonsterHPBar::Instance()->GetMonster() == this)
			MonsterHPBar::Instance()->SetMonster(nullptr);
	}
	else
	{
		int num = CE_MATH::Random(4);
		_pAudioSource->LoadAudio(_pDamagedSound[num]);
		_pAudioSource->Play();
		_state = Actor::State::HIT;
		_dirtyState = true;

		MonsterHPBar::Instance()->SetMonster(this);
	}
}

void Mephisto::OnAnimationEvent(std::string str) noexcept
{
	if (!_bIntroDone) return;

	if (_animator->GetCurrentAnimationName().find("Skill") != std::string::npos)
	{
		UsingSkill();
	}
	else if (_animator->GetCurrentAnimationName().find("Attack") != std::string::npos)
	{
		if (!_usingSkill) 
		{
			int num = CE_MATH::Random(4);
			_pAudioSource->LoadAudio(_pAttackSound[num]);
			_pAudioSource->Play();
			_player->GetHit(CE_MATH::Random(_data.damageMin, _data.damageMax), transform->GetWorldPosition());
		}
	}
}

void Mephisto::UsingSkill()
{
	if (!_usingSkill) return;

	D3DXVECTOR3 vDir = _player->GetTransform()->GetWorldPosition() - transform->GetWorldPosition();
	vDir.y = 0;
	float dis = D3DXVec3Length(&vDir);
	D3DXVec3Normalize(&vDir, &vDir);
	if (_bLightningCool && dis < _fLightningRange)
	{
		_bLightningCool = false;
		_fDeltaTime = 0;
	
		//번개 
		float angle = GetAngle(vDir);
		_lightning->GetTransform()->SetWorldPosition(transform->GetWorldPosition() + (vDir*1.2f));
		_lightning->Using(_dir, vDir);
	}
	else
	{
		//미사일 
		float angle = GetAngle(vDir);
		GameObject* missile = GameObject::Instantiate();
		missile->GetTransform()->SetWorldPosition(transform->GetWorldPosition());
		missile->GetTransform()->SetLocalEulerAngle(0, 0, angle);
		missile->AddComponent(new Missile(_data.damageMin, _data.damageMax, vDir));
	}
	_usingSkill = false;
}

void Mephisto::Intro(void) noexcept
{
	_animator->Play("Attack_0");
	D3DXVECTOR3 pos = transform->GetWorldPosition();
	transform->SetWorldPosition(pos.x, 1, pos.z);
	_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Attack_0")->GetTexture()[0]);
	_bIntro = true;
	_pAudioSource->LoadAudio(_pInitSound);
	_pAudioSource->Play();
}

float Mephisto::GetAngle(D3DXVECTOR3 vDir)
{
	D3DXMATRIX worldMat = transform->GetWorldMatrix();
	D3DXVECTOR3 vLook;
	vLook.x = worldMat.m[2][0];
	vLook.y = worldMat.m[2][1];
	vLook.z = worldMat.m[2][2];

	D3DXVECTOR3 vUp;
	vUp.x = worldMat.m[1][0];
	vUp.y = worldMat.m[1][1];
	vUp.z = worldMat.m[1][2];

	float angle = D3DXVec3Dot(&vLook, &vDir);
	angle = acosf(angle);

	D3DXVECTOR3 vCross = *D3DXVec3Cross(&vCross, &vDir, &vLook);
	float dot = D3DXVec3Dot(&vCross, &vUp);
	if (dot < 0)
		angle *= -1;

	return angle;
}

void Mephisto::InitAnimation()
{
	std::vector<Texture*> TList;
	std::vector<float>	FrameTime;
	Animation* ani;

	for (int folder = 0; folder < 8; folder++)
	{
		//Idle
		for (int i = 0; i < 13; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Actor\\Monster\\Mephisto\\Idle\\%d\\%d.png", folder, i);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.1f);
		}

		ani = new Animation(FrameTime, TList, true);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Idle_" + std::to_string(folder), ani);

		TList.clear();
		FrameTime.clear();

		//Walk
		for (int i = 0; i < 13; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Actor\\Monster\\Mephisto\\Walk\\%d\\%d.png", folder, i);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.1f);
		}

		ani = new Animation(FrameTime, TList, true);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Walk_" + std::to_string(folder), ani);

		TList.clear();
		FrameTime.clear();

		//Attack
		for (int i = 0; i < 18; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Actor\\Monster\\Mephisto\\Attack\\%d\\%d.png", folder, i);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.08f);
		}

		ani = new Animation(FrameTime, TList, false);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		ani->AddEvent(Animation::EventData(6, "attack", this->gameObject));
		_animator->InsertAnimation("Attack_" + std::to_string(folder), ani);

		TList.clear();
		FrameTime.clear();

		//Skill
		for (int i = 0; i < 17; i++)
		{
			int index = i + (folder * 17);
			char str[256];
			sprintf_s(str, 256, "Asset\\Actor\\Monster\\Mephisto\\Skill\\%d.png", index);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.05f);
		}
		ani = new Animation(FrameTime, TList, false);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		ani->AddEvent(Animation::EventData(6, "skill", this->gameObject));
		_animator->InsertAnimation("Skill_" + std::to_string(folder), ani);

		TList.clear();
		FrameTime.clear();

		//GetHit
		for (int i = 0; i < 6; i++)
		{
			int index = i + (folder * 6);
			char str[256];
			sprintf_s(str, 256, "Asset\\Actor\\Monster\\Mephisto\\GetHit\\%d.png", index);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.1f);
		}
		ani = new Animation(FrameTime, TList, false);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("GetHit_" + std::to_string(folder), ani);

		TList.clear();
		FrameTime.clear();

		//Death
		for (int i = 0; i < 25; i++)
		{
			int index = i + (folder * 25);
			char str[256];
			sprintf_s(str, 256, "Asset\\Actor\\Monster\\Mephisto\\Death\\%d.png", index);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.1f);
		}

		ani = new Animation(FrameTime, TList, false);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Death_" + std::to_string(folder), ani);

		TList.clear();
		FrameTime.clear();

	}

	//Dead
	for (int i = 0; i < 8; i++)
	{
		char str[256];
		sprintf_s(str, 256, "Asset\\Actor\\Monster\\Mephisto\\Dead\\%d.png", i);

		TList.push_back(ASSETMANAGER->GetTextureData(str));
		FrameTime.push_back(0.1f);
	}
	ani = new Animation(FrameTime, TList, false);
	ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
	_animator->InsertAnimation("Dead", ani);

	TList.clear();
	FrameTime.clear();

	_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Idle_0")->GetTexture()[0]);
	_animator->SetAnimation("Idle_0");
}

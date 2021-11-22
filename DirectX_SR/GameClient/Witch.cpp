#include "pch.h"
#include "Witch.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "BillboardObj.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Player.h"
#include "Vector3.h"
#include "PathFinding.h"
#include "AudioSource.h"
#include "AudioAsset.h"
#include "MonsterHPBar.h"
#include "FireBall.h"

Witch::Witch(PathFinding* pf, D3DXVECTOR3 bornPos) noexcept :
	_pathFinder(pf),
	_bornPosition(bornPos)
{
}

void Witch::Awake(void) noexcept
{
	_state = Actor::State::IDLE;
	memcpy(&_data, &GAMEDATAMANAGER->GetActorData("Witch"), sizeof(Actor::Data));
}

void Witch::Start(void) noexcept
{
	_spriteRenderer = static_cast<SpriteRenderer*>(gameObject->AddComponent(new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Witch\\Idle\\0.png"))));
	gameObject->AddComponent(new BillboardObj());
	_hitBox = static_cast<BoxCollider*>(gameObject->AddComponent(new BoxCollider(D3DXVECTOR3(0.5f, 1, 0.5f), D3DXVECTOR3(0, 0, 0), "Monster")));
	gameObject->AddComponent(new Rigidbody());

	_animator = new Animator(true);

	std::vector<float> frameTime;
	std::vector<Texture*> frameTex;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int index = i * 9 + j;

			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Witch\\Idle\\" + std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(frameTime, frameTex, true);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Idle_" + std::to_string(i), ani);

		frameTime.clear();
		frameTex.clear();
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int index = i * 9 + j ;

			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Witch\\Walk\\" + std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(frameTime, frameTex, true);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Walk_" + std::to_string(i), ani);

		frameTime.clear();
		frameTex.clear();
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int index = i * 8 + j;
			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Witch\\Attack\\" + std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(frameTime, frameTex, false);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Attack_" + std::to_string(i), ani);
		ani->AddEvent(Animation::EventData(6, "attack", this->gameObject));

		frameTime.clear();
		frameTex.clear();
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			int index = i * 17 + j;
			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Witch\\Death\\" + std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(frameTime, frameTex, false);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());

		_animator->InsertAnimation("Death_" + std::to_string(i), ani);

		frameTime.clear();
		frameTex.clear();
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			int index = i * 5 + j;
			frameTime.push_back(0.2f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Witch\\Skill\\" + std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(frameTime, frameTex, false);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());

		_animator->InsertAnimation("Skill_" + std::to_string(i), ani);

		frameTime.clear();
		frameTex.clear();
	}

	_animator->SetAnimation("Idle_0");
	_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Idle_0")->GetTexture()[0]);

	gameObject->AddComponent(_animator);
	gameObject->SetTag(GameObjectTag::MONSTER);

	GameObject* player = GameObject::FindObjectByTag(GameObjectTag::PLAYER);
	if (player == nullptr)
		CE_ASSERT("ckswns", "Player가 존재하지 않습니다.");

	const std::vector<Component*>& components = player->GetComponents();

	for (auto iter = components.begin(); iter != components.end(); iter++)
	{
		if ((*iter)->GetID() == COMPONENT_ID::BEHAVIOUR)
		{
			Player* p = dynamic_cast<Player*>((*iter));

			if (p != nullptr)
			{
				_player = p;
				break;
			}
		}
	}

	gameObject->GetTransform()->SetWorldPosition(_bornPosition);

	_currentHP = _data.maxHP;

	_attackAudio = static_cast<AudioSource*>(gameObject->AddComponent(new AudioSource()));
	_getHitAudio = static_cast<AudioSource*>(gameObject->AddComponent(new AudioSource()));
	_deadAudio = static_cast<AudioSource*>(gameObject->AddComponent(new AudioSource()));
	_skillAudio = static_cast<AudioSource*>(gameObject->AddComponent(new AudioSource()));
	_hitEffectAudio = static_cast<AudioSource*>(gameObject->AddComponent(new AudioSource()));

	_attackAudio->Init();
	_getHitAudio->Init();
	_deadAudio->Init();
	_skillAudio->Init();
	_hitEffectAudio->Init();

	_attackAudio->SetSoundWorld(true);
	_getHitAudio->SetSoundWorld(true);
	_deadAudio->SetSoundWorld(true);
	_skillAudio->SetSoundWorld(true);
	_hitEffectAudio->SetSoundWorld(true);

	_attackAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Monster\\Witch\\witchAttack.wav"));
	_getHitAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Monster\\Witch\\witchGetHit.wav"));
	_deadAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Monster\\Witch\\witchDeath.wav"));
	_skillAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Monster\\Witch\\witchSkill.wav"));
	_hitEffectAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Effect\\Blunt_GetHit.wav"));
}

void Witch::FixedUpdate(float fElapsedTime) noexcept
{
	Vector3 dis = transform->GetWorldPosition() - _player->GetTransform()->GetWorldPosition();

	switch (_state)
	{
	case Actor::State::IDLE:

		if (dis.Length() < 0.7f && dis.Length() > 0.6f && !_SkillCheck)
		{
			 _state = Actor::State::ATTAK;
			 _dirtyState = true;
			 _SkillCheck = true;
			 return;
		}
		else if (dis.Length() < 0.2f)
		{
			_state = Actor::State::ATTAK;
			_dirtyState = true;
			return;
		}
		else if (dis.Length() <= _data.aggroDistance)
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
			if (_SkillCheck)
			{
				// FireBall 생성
				D3DXVECTOR3 firedir;
				firedir = CaculateDir(_dir);

				GameObject* temp = GameObject::Instantiate();
				temp->AddComponent(new FireBall(transform->GetWorldPosition() + (firedir * 0.05f), firedir, static_cast<int>(_dir)));
				_fDeltaTime = 0;
			}
			_state = Actor::State::IDLE;
			_SkillCheck = false;
		}
		break;
	case Actor::State::HIT:
		_fDeltaTime += fElapsedTime;

		if (_fDeltaTime > 0.5f)
		{
			_state = State::IDLE;
			_fDeltaTime = 0;
			_dirtyState = true;
			_spriteRenderer->SetColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		break;
	case Actor::State::DIE:
		if (_animator->GetCurrentAnimationEnd())
		{
			if (_fDeltaTime < 1)
			{
				_fDeltaTime += fElapsedTime;
				if (_fDeltaTime > 1)
					gameObject->Destroy();
			}
			else
			{
				gameObject->Destroy();
			}
		}
		break;
	case Actor::State::MOVE:
		if (dis.Length() < 0.7f && dis.Length() > 0.6f && !_SkillCheck)
		{
			_state = Actor::State::ATTAK;
			_dirtyState = true;
			_SkillCheck = true;
			return;
		}
		else if (dis.Length() < 0.2f)
		{
			_state = Actor::State::ATTAK;
			_dirtyState = true;
			return;
		}
		else if (dis.Length() <= _data.aggroDistance)
		{
			if (_pathFinder->FindPath(transform->GetWorldPosition(), _player->GetTransform()->GetWorldPosition()))
			{
				_state = Actor::State::MOVE;
			}
		}
		else if (_pathFinder->GetPath().empty())
		{
			_state = Actor::State::IDLE;
			_dirtyState = true;
		}
		break;
	}
}

void Witch::Update(float fElapsedTime) noexcept
{
	switch (_state)
	{
	case Actor::State::IDLE:
		break;
	case Actor::State::MOVE:
		if (!_pathFinder->GetPath().empty())
		{
			Vector3 dis = transform->GetWorldPosition() - _player->GetTransform()->GetWorldPosition();

			if (dis.Length() > _data.aggroDistance)
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
		break;
	case Actor::State::HIT:
		break;
	case Actor::State::DIE:
		break;
	default:
		break;
	}
}

void Witch::LateUpdate(float fElapsedTime) noexcept
{
	if (_dirtyState == false)
		return;

	_dirtyState = false;

	switch (_state)
	{
	case Actor::State::IDLE:
		_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Idle_0")->GetTexture()[0]);
		_animator->SetAnimation("Idle_" + std::to_string(static_cast<int>(_dir)));
		_animator->Play();
		break;
	case Actor::State::MOVE:
		_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Walk_0")->GetTexture()[0]);
		_animator->SetAnimation("Walk_" + std::to_string(static_cast<int>(_dir)));
		_animator->Play();
		break;
	case Actor::State::ATTAK:
		if (_SkillCheck)
		{
			_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Skill_0")->GetTexture()[0]);
			_animator->SetAnimation("Skill_" + std::to_string(static_cast<int>(_dir)));
			_skillAudio->Play();
		}
		else
		{
			_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Attack_0")->GetTexture()[0]);
			_animator->SetAnimation("Attack_" + std::to_string(static_cast<int>(_dir)));
			_attackAudio->Play();
		}
		_animator->Play();
		break;
	case Actor::State::HIT:
		_animator->Stop();
		break;
	case Actor::State::DIE:
		_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Death_0")->GetTexture()[0]);
		_animator->SetAnimation("Death_" + std::to_string(static_cast<int>(_dir)));
		_animator->Play();
		break;
	default:
		break;
	}
}

void Witch::OnDestroy(void) noexcept
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

void Witch::OnCollisionEnter(Collider* mine, Collider* other) noexcept
{

}

void Witch::OnCollisionStay(Collider* mine, Collider* other) noexcept
{

}

void Witch::OnCollisionExit(Collider* mine, Collider* other) noexcept
{

}

void Witch::GetHit(int damage) noexcept
{
	if (_state == Actor::State::DIE)
		return;

	_currentHP -= damage;

	if (_currentHP <= 0)
	{
		_state = Actor::State::DIE;
		_hitBox->SetEnable(false);
		_currentHP = 0;
		_spriteRenderer->SetColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		_dirtyState = true;
		_fDeltaTime = 0;

		_deadAudio->Play();
		if (MonsterHPBar::Instance()->GetMonster() == this)
			MonsterHPBar::Instance()->SetMonster(nullptr);
	}
	else
	{
		_state = Actor::State::HIT;
		_animator->Stop();
		_spriteRenderer->SetColor(D3DCOLOR_ARGB(255, 255, 0, 0));
		_dirtyState = true;
		_fDeltaTime = 0;

		_getHitAudio->Play();
		MonsterHPBar::Instance()->SetMonster(this);
	}
}

void Witch::OnAnimationEvent(std::string str) noexcept
{
	Vector3 dis = transform->GetWorldPosition() - _player->GetTransform()->GetWorldPosition();

	if (dis.Length() < 0.2f)
	{
		_player->GetHit(Random::GetValue(_data.damageMax, _data.damageMin), transform->GetWorldPosition());
		_hitEffectAudio->Play();
	}
}

D3DXVECTOR3 Witch::CaculateDir(Actor::Direction dir) const noexcept
{
	D3DXVECTOR3 result;

	switch (dir)
	{
	case Actor::Direction::DOWN:
		result = { 0, 0, -1 };
		break;
	case Actor::Direction::LEFT_DOWN:
		result = { -1, 0, -1 };
		break;
	case Actor::Direction::LEFT:
		result = { -1, 0, 0 };
		break;
	case Actor::Direction::LEFT_UP:
		result = { -1, 0, 1 };
		break;
	case Actor::Direction::UP:
		result = { 0, 0, 1 };
		break;
	case Actor::Direction::RIGHT_UP:
		result = { 1, 0, 1 };
		break;
	case Actor::Direction::RIGHT:
		result = { 1, 0, 0 };
		break;
	case Actor::Direction::RIGHT_DOWN:
		result = { 1, 0, -1 };
		break;
	default:
		result = { 0, 0, 0 };
		break;
	}

	D3DXVec3Normalize(&result, &result);

	return result;
}


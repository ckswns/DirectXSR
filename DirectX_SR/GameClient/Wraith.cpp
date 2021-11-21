#include "pch.h"
#include "Wraith.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "BillboardObj.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Transform.h"
#include "Camera.h"
#include "RigidBody.h"
#include "Player.h"
#include "Vector3.h"
#include "PathFinding.h"
#include "AudioSource.h"
#include "AudioAsset.h"
#include "MonsterHPBar.h"

Wraith::Wraith(PathFinding* pf, D3DXVECTOR3 bornPos) noexcept :
	_pathFinder(pf),
	_bornPosition(bornPos)
{
}

void Wraith::Awake(void) noexcept
{
	_state = Actor::State::IDLE;
	memcpy(&_data, &GAMEDATAMANAGER->GetActorData("Wraith"), sizeof(Actor::Data));
}

void Wraith::Start(void) noexcept
{
	_spriteRenderer = static_cast<SpriteRenderer*>(gameObject->AddComponent(new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Wraith\\Idle\\0.png"))));
	gameObject->AddComponent(new BillboardObj());
	_hitBox = static_cast<BoxCollider*>(gameObject->AddComponent(new BoxCollider(D3DXVECTOR3(0.5f, 1, 0.5f), D3DXVECTOR3(0, 0, 0), "Monster")));
	gameObject->AddComponent(new Rigidbody());

	_animator = new Animator(true);

	std::vector<float> frameTime;
	std::vector<Texture*> frameTex;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int index = i * 8 + j;

			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Wraith\\Idle\\" + std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(frameTime, frameTex, true);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Idle_" + std::to_string(i), ani);

		frameTime.clear();
		frameTex.clear();
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			int index = i * 10 + j ;

			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Wraith\\Walk\\" + std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(frameTime, frameTex, true);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Walk_" + std::to_string(i), ani);

		frameTime.clear();
		frameTex.clear();
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			int index = i * 14 + j;
			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Wraith\\Attack\\" + std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(frameTime, frameTex, false);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Attack_" + std::to_string(i), ani);
		ani->AddEvent(Animation::EventData(9, "attack", this->gameObject));

		frameTime.clear();
		frameTex.clear();
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			int index = i * 20 + j;
			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Wraith\\Death\\" + std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(frameTime, frameTex, false);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());

		_animator->InsertAnimation("Death_" + std::to_string(i), ani);

		frameTime.clear();
		frameTex.clear();
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int index = i * 4 + j;
			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Wraith\\Hit\\" + std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(frameTime, frameTex, false);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());

		_animator->InsertAnimation("Hit_" + std::to_string(i), ani);

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
	_hitEffectAudio = static_cast<AudioSource*>(gameObject->AddComponent(new AudioSource()));

	_attackAudio->Init();
	_getHitAudio->Init();
	_deadAudio->Init();
	_hitEffectAudio->Init();

	_attackAudio->SetSoundWorld(true);
	_getHitAudio->SetSoundWorld(true);
	_deadAudio->SetSoundWorld(true);
	_hitEffectAudio->SetSoundWorld(true);

	_attackAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Monster\\Cow\\CowAttack.mp3"));
	_getHitAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Monster\\Cow\\CowGetHit.mp3"));
	_deadAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Monster\\Cow\\CowDead.mp3"));
	_hitEffectAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Effect\\Blunt_GetHit.wav"));
}

void Wraith::FixedUpdate(float fElapsedTime) noexcept
{
	Vector3 dis = transform->GetWorldPosition() - _player->GetTransform()->GetWorldPosition();

	switch (_state)
	{
	case Actor::State::IDLE:

		if (dis.Length() < 0.5f)
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
			_state = Actor::State::IDLE;

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
		if (dis.Length() < 0.5f)
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

void Wraith::Update(float fElapsedTime) noexcept
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

void Wraith::LateUpdate(float fElapsedTime) noexcept
{
	if (_dirtyState == false)
		return;

	_dirtyState = false;

	switch (_state)
	{
	case Actor::State::IDLE:
		_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Idle_" + std::to_string(static_cast<int>(_dir)))->GetTexture()[0]);
		_animator->SetAnimation("Idle_" + std::to_string(static_cast<int>(_dir)));
		_animator->Play();
		break;
	case Actor::State::MOVE:
		_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Walk_" + std::to_string(static_cast<int>(_dir)))->GetTexture()[0]);
		_animator->SetAnimation("Walk_" + std::to_string(static_cast<int>(_dir)));
		_animator->Play();
		break;
	case Actor::State::ATTAK:
		_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Attack_" + std::to_string(static_cast<int>(_dir)))->GetTexture()[0]);
		_animator->SetAnimation("Attack_" + std::to_string(static_cast<int>(_dir)));
		_animator->Play();
		_attackAudio->Play();
		break;
	case Actor::State::HIT:
		_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Hit_" + std::to_string(static_cast<int>(_dir)))->GetTexture()[0]);
		_animator->SetAnimation("Hit_" + std::to_string(static_cast<int>(_dir)));
		_animator->Play();
		break;
	case Actor::State::DIE:
		_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Death_" + std::to_string(static_cast<int>(_dir)))->GetTexture()[0]);
		_animator->SetAnimation("Death_" + std::to_string(static_cast<int>(_dir)));
		_animator->Play();
		break;
	default:
		break;
	}
}

void Wraith::OnDestroy(void) noexcept
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

void Wraith::OnCollisionEnter(Collider* mine, Collider* other) noexcept
{

}

void Wraith::OnCollisionStay(Collider* mine, Collider* other) noexcept
{

}

void Wraith::OnCollisionExit(Collider* mine, Collider* other) noexcept
{

}

void Wraith::GetHit(int damage) noexcept
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

void Wraith::OnAnimationEvent(std::string str) noexcept
{
	Vector3 dis = transform->GetWorldPosition() - _player->GetTransform()->GetWorldPosition();

	if (dis.Length() < 0.7f)
	{
		_player->GetHit(Random::GetValue(_data.damageMax, _data.damageMin), transform->GetWorldPosition());
		_hitEffectAudio->Play();
	}
}


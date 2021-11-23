#include "pch.h"
#include "Orc.h"
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
#include "Gold.h"

Orc::Orc(PathFinding* pf, D3DXVECTOR3 bornPos) noexcept :
	_pathFinder(pf),
	_bornPosition(bornPos)
{
}

void Orc::Awake(void) noexcept
{
	_state = Actor::State::IDLE;
	memcpy(&_data, &GAMEDATAMANAGER->GetActorData("Orc"), sizeof(Actor::Data));
}

void Orc::Start(void) noexcept
{
	_spriteRenderer = static_cast<SpriteRenderer*>(gameObject->AddComponent(new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Orc\\Idle\\1.png"))));
	gameObject->AddComponent(new BillboardObj());
	_hitBox = static_cast<BoxCollider*>(gameObject->AddComponent(new BoxCollider(D3DXVECTOR3(0.5f, 1, 0.5f), D3DXVECTOR3(0, 0, 0), "Monster")));
	gameObject->AddComponent(new Rigidbody());
	//gameObject->GetTransform()->SetLocalPosition(0, 0.7f, 0);

	_animator = new Animator(true);

	std::vector<float> frameTime;
	std::vector<Texture*> frameTex;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int index = i * 8 + j + 1;

			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Orc\\Idle\\" + std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(frameTime, frameTex, true);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Idle_" + std::to_string(i), ani);

		frameTime.clear();
		frameTex.clear();
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int index = i * 8 + j + 1;

			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Orc\\Walk\\" + std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(frameTime, frameTex, true);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Walk_" + std::to_string(i), ani);

		frameTime.clear();
		frameTex.clear();
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			int index = i * 15 + j + 1;
			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Orc\\Attack\\" + std::to_string(index) + ".png"));
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
		for (int j = 0; j < 23; j++)
		{
			int index = i * 23 + j + 1;
			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Orc\\Death\\" + std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(frameTime, frameTex, false);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());

		_animator->InsertAnimation("Death_" + std::to_string(i), ani);

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

void Orc::FixedUpdate(float fElapsedTime) noexcept
{
	D3DXVECTOR3 target = _player->GetTransform()->GetWorldPosition();
	D3DXVECTOR3 mine = transform->GetWorldPosition();

	target.y = 0;
	mine.y = 0;

	float dis = Vector3::Distance(target, mine);

	switch (_state)
	{
	case Actor::State::IDLE:

		if (dis < 1.f)
		{
			_state = Actor::State::ATTAK;
			_dirtyState = true;
			return;
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
				{
					GameObject* pobj = GameObject::Instantiate();
					pobj->AddComponent(new Gold());
					pobj->GetTransform()->SetWorldPosition(transform->GetWorldPosition());
					gameObject->Destroy();
				}
			}
			else
			{
				GameObject* pobj = GameObject::Instantiate();
				pobj->AddComponent(new Gold());
				pobj->GetTransform()->SetWorldPosition(transform->GetWorldPosition());
				gameObject->Destroy();
			}
		}
		break;
	case Actor::State::MOVE:
		if (dis < 1)
		{
			_state = Actor::State::ATTAK;
			_dirtyState = true;

			return;
		}
		else if (dis <= _data.aggroDistance)
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

void Orc::Update(float fElapsedTime) noexcept
{
	switch (_state)
	{
	case Actor::State::IDLE:
		break;
	case Actor::State::MOVE:
		if (!_pathFinder->GetPath().empty())
		{
			D3DXVECTOR3 target = _player->GetTransform()->GetWorldPosition();
			D3DXVECTOR3 mine = transform->GetWorldPosition();

			target.y = 0;
			mine.y = 0;

			float dis = Vector3::Distance(target, mine);

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
		break;
	case Actor::State::HIT:
		break;
	case Actor::State::DIE:
		break;
	default:
		break;
	}
}

void Orc::LateUpdate(float fElapsedTime) noexcept
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
		_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Attack_0")->GetTexture()[0]);
		_animator->SetAnimation("Attack_" + std::to_string(static_cast<int>(_dir)));
		_animator->Play();
		_attackAudio->Play();
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

void Orc::OnDestroy(void) noexcept
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

void Orc::OnCollisionEnter(Collider* mine, Collider* other) noexcept
{
}

void Orc::OnCollisionStay(Collider* mine, Collider* other) noexcept
{
}

void Orc::OnCollisionExit(Collider* mine, Collider* other) noexcept
{
}

void Orc::GetHit(int damage) noexcept
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

void Orc::OnAnimationEvent(std::string str) noexcept
{
	D3DXVECTOR3 target = _player->GetTransform()->GetWorldPosition();
	D3DXVECTOR3 mine = transform->GetWorldPosition();

	target.y = 0;
	mine.y = 0;

	float dis = Vector3::Distance(target, mine);

	if (dis < 1)
	{
		_player->GetHit(Random::GetValue(_data.damageMax, _data.damageMin), transform->GetWorldPosition());
		_hitEffectAudio->Play();
	}
}

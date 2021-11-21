#include "pch.h"
#include "Diablo.h"
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
#include "LightningBreath.h"
#include "CETween.h"
#include "FireWall.h"

Diablo::Diablo(PathFinding* pf, Player* player) noexcept :
	_pathFinder(pf),
	_player(player)
{
}

void Diablo::Awake(void) noexcept
{
	_state = Actor::State::IDLE;
	memcpy(&_data, &GAMEDATAMANAGER->GetActorData("Diablo"), sizeof(Actor::Data));
}

void Diablo::Start(void) noexcept
{
	_fireAudio = static_cast<AudioSource*>(gameObject->AddComponent(new AudioSource()));
	_breathAudio = static_cast<AudioSource*>(gameObject->AddComponent(new AudioSource()));
	_castAudio = static_cast<AudioSource*>(gameObject->AddComponent(new AudioSource()));
	_initAudio = static_cast<AudioSource*>(gameObject->AddComponent(new AudioSource()));
	_laughAudio = static_cast<AudioSource*>(gameObject->AddComponent(new AudioSource()));
	_attackAudio = static_cast<AudioSource*>(gameObject->AddComponent(new AudioSource()));
	_getHitAudio = static_cast<AudioSource*>(gameObject->AddComponent(new AudioSource()));
	_deadAudio = static_cast<AudioSource*>(gameObject->AddComponent(new AudioSource()));
	_hitEffectAudio = static_cast<AudioSource*>(gameObject->AddComponent(new AudioSource()));

	_fireAudio->Init();
	_breathAudio->Init();
	_castAudio->Init();
	_initAudio->Init();
	_laughAudio->Init();
	_attackAudio->Init();
	_getHitAudio->Init();
	_deadAudio->Init();
	_hitEffectAudio->Init();

	_fireAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Diablo\\DiabloSkill1.wav"));
	_breathAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Diablo\\DiabloBreath.wav"));
	_castAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Diablo\\DiabloCast.wav"));
	_initAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Diablo\\DiabloInit.wav"));
	_laughAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Diablo\\DiabloLaugh.wav"));
	_attackAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Diablo\\DiabloAttack.wav"));
	_getHitAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Diablo\\DiabloHit.wav"));
	_deadAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Diablo\\DiabloDead.wav"));
	_hitEffectAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Effect\\Blunt_GetHit.wav"));

	_fireAudio->SetSoundWorld(true);
	_breathAudio->SetSoundWorld(true);
	_castAudio->SetSoundWorld(true);
	_initAudio->SetSoundWorld(false);
	_laughAudio->SetSoundWorld(true);
	_attackAudio->SetSoundWorld(true);
	_getHitAudio->SetSoundWorld(true);
	_deadAudio->SetSoundWorld(true);
	_hitEffectAudio->SetSoundWorld(true);

	_spriteRenderer = new SpriteRenderer(D3D9DEVICE->GetDevice(),
		ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Diablo\\Idle\\1.png"));
	gameObject->AddComponent(_spriteRenderer);
	_hitBox = static_cast<BoxCollider*>(gameObject->AddComponent(
		new BoxCollider(D3DXVECTOR3(0.5f, 1, 0.5f), D3DXVECTOR3(0, 0, 0), "Monster")));
	gameObject->AddComponent(new Rigidbody());

	_animator = new Animator(true);

	std::vector<float> vFrame;
	std::vector<Texture*> vTex;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			int index = i * 12 + j + 1;

			vFrame.push_back(0.1f);
			vTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Diablo\\Idle\\"
				+ std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(vFrame, vTex, true);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Idle_" + std::to_string(i), ani);

		vFrame.clear();
		vTex.clear();
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			int index = i * 12 + j + 1;

			vFrame.push_back(0.1f);
			vTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Diablo\\Walk\\"
				+ std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(vFrame, vTex, true);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Walk_" + std::to_string(i), ani);

		vFrame.clear();
		vTex.clear();
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 22; j++)
		{
			int index = i * 22 + j + 1;

			vFrame.push_back(0.1f);
			vTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Diablo\\Run\\"
				+ std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(vFrame, vTex, true);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Run_" + std::to_string(i), ani);

		vFrame.clear();
		vTex.clear();
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			int index = i * 20 + j + 1;

			vFrame.push_back(0.1f);
			vTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Diablo\\Attack\\"
				+ std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(vFrame, vTex, false);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Attack_" + std::to_string(i), ani);
		ani->AddEvent(13, "Attack", gameObject);
		vFrame.clear();
		vTex.clear();
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int index = i * 9 + j + 1;

			if (j == 4)
				vFrame.push_back(0.5f);
			else
				vFrame.push_back(0.1f);
			vTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Diablo\\Block\\"
				+ std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(vFrame, vTex, false);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Attack2_" + std::to_string(i), ani);
		ani->AddEvent(6, "Attack2", gameObject);

		vFrame.clear();
		vTex.clear();
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			int index = i * 17 + j + 1;

			vFrame.push_back(0.1f);
			vTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Diablo\\Breath\\"
				+ std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(vFrame, vTex, false);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Breath_" + std::to_string(i), ani);

		vFrame.clear();
		vTex.clear();
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			int index = i * 18 + j + 1;

			vFrame.push_back(0.1f);
			vTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Diablo\\Skill3\\"
				+ std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(vFrame, vTex, false);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Breath2_" + std::to_string(i), ani);

		vFrame.clear();
		vTex.clear();
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			int index = i * 16 + j + 1;

			vFrame.push_back(0.1f);
			vTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Diablo\\Skill4\\"
				+ std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(vFrame, vTex, false);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		ani->AddEvent(11, "Skill3", gameObject);
		_animator->InsertAnimation("Cast_" + std::to_string(i), ani);
		
		vFrame.clear();
		vTex.clear();
	}

	for (int i = 1; i <= 33; i++)
	{
		vFrame.push_back(0.1f);
		vTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Diablo\\Death\\0\\"
			+ std::to_string(i) + ".png"));
	}

	for (int i = 1; i <= 76; i++)
	{
		vFrame.push_back(0.1f);
		vTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Diablo\\Death\\1\\"
			+ std::to_string(i) + ".png"));
	}

	for (int i = 1; i <= 33; i++)
	{
		vFrame.push_back(0.1f);
		vTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Diablo\\Death\\2\\"
			+ std::to_string(i) + ".png"));
	}

	Animation* ani = new Animation(vFrame, vTex, false);
	ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
	_animator->InsertAnimation("Death", ani);

	vFrame.clear();
	vTex.clear();

	_animator->SetAnimation("Idle_0");
	gameObject->AddComponent(_animator);
	gameObject->SetTag(GameObjectTag::MONSTER);

	_currentHP = _data.maxHP;

	gameObject->AddComponent(new BillboardObj());
}

void Diablo::FixedUpdate(float fElapsedTime) noexcept
{
	if (_bIntro)
	{
		if (_animator->GetCurrentAnimationEnd())
		{
			D3DXVECTOR3 pos = transform->GetWorldPosition();
			transform->SetWorldPosition(pos.x, 0.4f, pos.z);
			_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Idle_0")->GetTexture()[0]);
			_animator->SetAnimation("Idle_0");
			_bIntro = false;
		}
	}

	if (_bIntroDone == false)
		return;

	Vector3 mine = transform->GetWorldPosition();
	Vector3 playerPos = _player->GetTransform()->GetWorldPosition();

	mine._y = 0;
	playerPos._y = 0;

	float dis = Vector3::Distance(mine, playerPos);

	switch (_state)
	{
	case Actor::State::IDLE:		
		if (dis < 3 &&
			(_currentSkill1CoolTime >= _skill1CoolTime ||
			 _currentSkill3CoolTime >= _skill3CoolTime))
		{
			if (_currentSkill1CoolTime >= _skill1CoolTime)
			{
				_currentSkill1CoolTime = 0;
				_eAttackState = AttackState::Skill1;
			}
			else if (_currentSkill3CoolTime >= _skill3CoolTime)
			{
				_currentSkill3CoolTime = 0;
				_eAttackState = AttackState::Skill3;
			}

			_fDeltaTime = 0;
			_state = Actor::State::ATTAK;
			_dirtyState = true;
			return;
		}
		else if (dis < 1)
		{
			if (_currentSkill2CoolTime >= _skill2CoolTime)
			{
				_currentSkill2CoolTime = 0;
				_eAttackState = AttackState::Skill2;
			}
			else
			{
				_eAttackState = AttackState::Default;
			}
			_state = Actor::State::ATTAK;
			_dirtyState = true;
			return;
		}
		else 
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
		_state = State::IDLE;
		break;

	case Actor::State::DIE:
		if (_animator->GetCurrentAnimationEnd())
			_bDeadAniDone = true;
		break;

	case Actor::State::MOVE:
		if (dis < 1.f)
		{
			_state = Actor::State::IDLE;
			_dirtyState = true;

			return;
		}
		else 
		{
			_pathFinder->FindPath(transform->GetWorldPosition(), _player->GetTransform()->GetWorldPosition());
		}
		break;
	}
}

void Diablo::Update(float fElapsedTime) noexcept
{
	if (_bIntroDone == false)
		return;

	_currentSkill1CoolTime += fElapsedTime;
	_currentSkill2CoolTime += fElapsedTime;
	_currentSkill3CoolTime += fElapsedTime;

	int curFrame = _animator->GetCurrentFrame();

	switch (_state)
	{
	case Actor::State::IDLE:
		break;
	case Actor::State::MOVE:
		if (!_pathFinder->GetPath().empty())
		{
			Vector3 dis = transform->GetWorldPosition() - _player->GetTransform()->GetWorldPosition();

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
		switch (_eAttackState)
		{
		case Diablo::AttackState::Default:
			break;
		case Diablo::AttackState::Skill1:
			if (curFrame >= 7 && curFrame <= 14)
			{
				if (_fDeltaTime >= 0.1f)
				{
					D3DXVECTOR3 breathDir;
					breathDir = CaculateDir(_dir);

					GameObject* temp = GameObject::Instantiate();
					temp->AddComponent(new LightningBreath(transform->GetWorldPosition() + (breathDir * 0.05f),
						breathDir,
						static_cast<int>(_dir)));
					_fDeltaTime = 0;
				}
				else
				{
					_fDeltaTime += fElapsedTime;
				}
			}
			break;
		case Diablo::AttackState::Skill2:
			//if (curFrame >= 9 && curFrame <= 14)
			//{
			//	if (_fDeltaTime >= 0.1f)
			//	{
			//		D3DXVECTOR3 breathDir;
			//		float angle = 0;

			//		switch (_dir)
			//		{
			//		case Actor::Direction::DOWN:
			//			angle = CETween::Lerp(225, 270, 1 - ((curFrame - 9) / 5.f));
			//			break;
			//		case Actor::Direction::LEFT_DOWN:
			//			angle = CETween::Lerp(180, 225, 1 - ((curFrame - 9) / 5.f));
			//			break;
			//		case Actor::Direction::LEFT:
			//			angle = CETween::Lerp(135, 180, 1 - ((curFrame - 9) / 5.f));
			//			break;
			//		case Actor::Direction::LEFT_UP:
			//			angle = CETween::Lerp(90, 135, 1 - ((curFrame - 9) / 5.f));
			//			break;
			//		case Actor::Direction::UP:
			//			angle = CETween::Lerp(45, 90, 1 - ((curFrame - 9) / 5.f));
			//			break;
			//		case Actor::Direction::RIGHT_UP:
			//			angle = CETween::Lerp(0, 45, 1 - ((curFrame - 9) / 5.f));
			//			break;
			//		case Actor::Direction::RIGHT:
			//			angle = CETween::Lerp(315, 360, 1 - ((curFrame - 9) / 5.f));
			//			break;
			//		case Actor::Direction::RIGHT_DOWN:
			//			angle = CETween::Lerp(270, 315, 1 - ((curFrame - 9) / 5.f));
			//			break;
			//		default:
			//			break;
			//		}

			//		angle = D3DXToRadian(angle);

			//		breathDir = { sinf(angle), 0, cosf(angle) };
			//		D3DXVec3Normalize(&breathDir, &breathDir);

			//		GameObject* temp = GameObject::Instantiate();
			//		temp->AddComponent(new LightningBreath(transform->GetWorldPosition() + (breathDir * 0.05f),
			//			breathDir,
			//			static_cast<int>(_dir)));
			//		_fDeltaTime = 0;
			//	}
			//	else
			//	{
			//		_fDeltaTime += fElapsedTime;
			//	}
			//}
			break;
		case Diablo::AttackState::Skill3:
			break;
		default:
			break;
		}
		break;
	case Actor::State::HIT:
		break;
	case Actor::State::DIE:
		break;
	default:
		break;
	}
}

void Diablo::LateUpdate(float fElapsedTime) noexcept
{
	if (_bIntroDone == false)
		return;

	if (_bColorChanged)
	{
		_fColorChageTime += fElapsedTime;
		if (_fColorChageTime > 1)
		{
			_bColorChanged = false;
			_spriteRenderer->SetColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}

	if (_dirtyState)
	{
		_dirtyState = false;

		D3DXVECTOR3 pos = transform->GetWorldPosition();

		switch (_state)
		{
		case Actor::State::IDLE:
			transform->SetWorldPosition(pos.x, 0.7f, pos.z);
			_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Idle_0")->GetTexture()[0]);
			_animator->SetAnimation("Idle_" + std::to_string(static_cast<int>(_dir)));
			_animator->Play();
			break;
		case Actor::State::MOVE:
			transform->SetWorldPosition(pos.x, 0.9f, pos.z);
			_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Walk_0")->GetTexture()[0]);
			_animator->SetAnimation("Walk_" + std::to_string(static_cast<int>(_dir)));
			_animator->Play();
			break;
		case Actor::State::ATTAK:
			switch (_eAttackState)
			{
			case Diablo::AttackState::Default:
				transform->SetWorldPosition(pos.x, 1.f, pos.z);
				_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Attack_0")->GetTexture()[0]);
				_animator->SetAnimation("Attack_" + std::to_string(static_cast<int>(_dir)));
				_animator->Play();
				_attackAudio->Play();
				break;
			case Diablo::AttackState::Skill1:
				transform->SetWorldPosition(pos.x, 1.f, pos.z);
				_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Breath_0")->GetTexture()[0]);
				_animator->SetAnimation("Breath_" + std::to_string(static_cast<int>(_dir)));
				_animator->Play();
				_breathAudio->Play();
				break;
			case Diablo::AttackState::Skill2:
				transform->SetWorldPosition(pos.x, 1.f, pos.z);
				_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Attack2_0")->GetTexture()[0]);
				_animator->SetAnimation("Attack2_" + std::to_string(static_cast<int>(_dir)));
				_animator->Play();
				_attackAudio->Play();
				break;
			case Diablo::AttackState::Skill3:
				transform->SetWorldPosition(pos.x, 1.f, pos.z);
				_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Cast_0")->GetTexture()[0]);
				_animator->SetAnimation("Cast_" + std::to_string(static_cast<int>(_dir)));
				_animator->Play();
				_laughAudio->Play();
				break;
			default:
				break;
			}
			break;
		case Actor::State::HIT:
			transform->SetWorldPosition(pos.x, 1.f, pos.z);
			_animator->Stop();
			break;
		case Actor::State::DIE:
			transform->SetWorldPosition(pos.x, 1.4f, pos.z);
			_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Death")->GetTexture()[0]);
			_animator->SetAnimation("Death");
			_animator->Play();
			break;
		default:
			break;
		}
	}
	else if (_prevDirection != _dir)
	{
		_prevDirection = _dir;
		int frame = _animator->GetCurrentFrame();

		switch (_state)
		{
		case Actor::State::IDLE:
			_animator->SetAnimation("Idle_" + std::to_string(static_cast<int>(_dir)));
			_animator->Play();
			break;
		case Actor::State::MOVE:
			_animator->SetAnimation("Walk_" + std::to_string(static_cast<int>(_dir)));
			_animator->Play();
			break;
		default:
			break;
		}

		_animator->SetFrame(frame);
	}
}

void Diablo::OnDestroy(void) noexcept
{
	if (_pathFinder)
	{
		delete _pathFinder;
		_pathFinder = nullptr;
	}
}

void Diablo::OnCollisionEnter(Collider* mine, Collider* other) noexcept
{
}

void Diablo::OnCollisionStay(Collider* mine, Collider* other) noexcept
{
}

void Diablo::OnCollisionExit(Collider* mine, Collider* other) noexcept
{
}

void Diablo::GetHit(int damage) noexcept
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

		_deadAudio->Play();
		if (MonsterHPBar::Instance()->GetMonster() == this)
			MonsterHPBar::Instance()->SetMonster(nullptr);
	}
	else
	{
		_fColorChageTime = 0;
		_bColorChanged = true;
		_spriteRenderer->SetColor(D3DCOLOR_ARGB(255, 0, 0, 255));
		_getHitAudio->Play();
		MonsterHPBar::Instance()->SetMonster(this);
	}
}

void Diablo::OnAnimationEvent(std::string str) noexcept
{
	if (str == "Skill3")
	{
		DoSkill3();
	}
	else if (str == "Attack")
	{
		Vector3 mine = transform->GetWorldPosition();
		Vector3 playerPos = _player->GetTransform()->GetWorldPosition();

		mine._y = 0;
		playerPos._y = 0;

		float dis = Vector3::Distance(mine, playerPos);

		if (dis < 1)
			_player->GetHit(Random::GetValue(_data.damageMin, _data.damageMax), transform->GetWorldPosition());
	}
	else if (str == "Attack2")
	{
		Vector3 mine = transform->GetWorldPosition();
		Vector3 playerPos = _player->GetTransform()->GetWorldPosition();

		mine._y = 0;
		playerPos._y = 0;

		float dis = Vector3::Distance(mine, playerPos);

		if (dis < 1)
			_player->GetHit(Random::GetValue(_data.damageMin, _data.damageMax) * 2, transform->GetWorldPosition());
	}
}

void Diablo::Intro(void) noexcept
{
	_animator->Play("Attack_0");
	D3DXVECTOR3 pos = transform->GetWorldPosition();
	transform->SetWorldPosition(pos.x, 1, pos.z);
	_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Attack_0")->GetTexture()[0]);
	_bIntro = true;
	_initAudio->Play();
}

void Diablo::DoSkill3(void) noexcept
{
	D3DXVECTOR3 breathDir;
	float angle = 0;

	for (int i = 0; i < 8; i++)
	{
		angle = D3DXToRadian(45 * i);

		breathDir = { sinf(angle), 0, cosf(angle) };
		D3DXVec3Normalize(&breathDir, &breathDir);

		GameObject* temp = GameObject::Instantiate();
		temp->AddComponent(new FireWall(transform->GetWorldPosition(),
			breathDir));
	}
}

D3DXVECTOR3 Diablo::CaculateDir(Actor::Direction dir) const noexcept
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

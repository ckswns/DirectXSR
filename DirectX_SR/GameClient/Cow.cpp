#include "pch.h"
#include "Cow.h"
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

Cow::Cow(PathFinding* pf, D3DXVECTOR3 bornPos) noexcept :
	_pathFinder(pf),
	_bornPosition(bornPos)
{
}

void Cow::Awake(void) noexcept
{
	_state = Actor::State::IDLE;
	memcpy(&_data, &GAMEDATAMANAGER->GetActorData("Cow"), sizeof(Actor::Data));
}

void Cow::Start(void) noexcept
{
	_spriteRenderer = static_cast<SpriteRenderer*>(gameObject->AddComponent(new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Cow\\Idle\\1.png"))));
	gameObject->AddComponent(new BillboardObj());
	gameObject->AddComponent(new BoxCollider(D3DXVECTOR3(0.5f, 1, 0.5f)));
	gameObject->AddComponent(new Rigidbody());
	//gameObject->GetTransform()->SetLocalPosition(0, 0.7f, 0);

	_animator = new Animator(true);

	std::vector<float> frameTime;
	std::vector<Texture*> frameTex;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			int index = i * 10 + j + 1;

			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Cow\\Idle\\" + std::to_string(index) + ".png"));
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
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Cow\\Walk\\" + std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(frameTime, frameTex, true);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Walk_" + std::to_string(i), ani);

		frameTime.clear();
		frameTex.clear();
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			int index = i * 19 + j + 1;
			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Cow\\Attack\\" + std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(frameTime, frameTex, true);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Attack_" + std::to_string(i), ani);

		frameTime.clear();
		frameTex.clear();
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			int index = i * 14 + j + 1;
			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Cow\\Death\\" + std::to_string(index) + ".png"));
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

}

void Cow::FixedUpdate(float fElapsedTime) noexcept
{
	Vector3 dis = transform->GetWorldPosition() - _player->GetTransform()->GetWorldPosition();
	
	if (dis.Length() <= _data.aggroDistance)
	{
		if (_pathFinder->FindPath(transform->GetWorldPosition(), _player->GetTransform()->GetWorldPosition()))
		{
			_state = Actor::State::MOVE;
		}
	}
}

void Cow::Update(float fElapsedTime) noexcept
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

			Direction dir =  GetDirect(transform->GetWorldPosition(), (*iter)->GetPos());
			int iDir = static_cast<int>(dir);

			if(_dir != dir)
				_animator->SetAnimation("Walk_" + std::to_string(iDir));

			_dir = dir;

			if (D3DXVec3Length(&vDir) < 0.1f)
			{
				path.pop_front();
				if (path.empty())
				{
					path.clear();
					_state = Actor::State::IDLE;
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

void Cow::LateUpdate(float fElapsedTime) noexcept
{

}

void Cow::OnDestroy(void) noexcept
{
	if (_pathFinder)
	{
		delete _pathFinder;
		_pathFinder = nullptr;
	}
}

void Cow::OnCollisionEnter(Collider* mine, Collider* other) noexcept
{

}

void Cow::OnCollisionStay(Collider* mine, Collider* other) noexcept
{

}

void Cow::OnCollisionExit(Collider* mine, Collider* other) noexcept
{

}

void Cow::GetHit(float damage) noexcept
{

}



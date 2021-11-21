#include "pch.h"
#include "FireWall.h"
#include "Collider.h"
#include "Player.h"
#include "Animation.h"
#include "Animator.h"
#include "SpriteRenderer.h"
#include "EffectRenderer.h"
#include "Transform.h"
#include "SphereCollider.h"
#include "BillboardObj.h"
#include "RigidBody.h"

FireWall::FireWall(D3DXVECTOR3 pos, D3DXVECTOR3 vDir) noexcept :
	_startPos(pos),
	_vDir(vDir)
{
}

void FireWall::Awake(void) noexcept
{
	transform->SetWorldPosition(_startPos);

	gameObject->AddComponent(new BillboardObj());
	gameObject->AddComponent(new SphereCollider(0.3f));
	gameObject->AddComponent(new Rigidbody());

	SpriteRenderer* sr = static_cast<SpriteRenderer*>(gameObject->AddComponent(new SpriteRenderer(D3D9DEVICE->GetDevice())));
	sr->SetTexture(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Diablo\\FireWall\\1.png"));

	_animator = new Animator(true);

	std::vector<float> vFrame;
	std::vector<Texture*> vTex;

	for (int i = 1; i < 21; i++)
	{
		vFrame.push_back(0.025f);
		vTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Diablo\\FireWall\\" + std::to_string(i) + ".png"));
	}

	Animation* ani = new Animation(vFrame, vTex, true);
	ani->SetMaterial(sr->GetMaterialPTR());
	_animator->InsertAnimation("Idle", ani);

	gameObject->AddComponent(_animator);
	_animator->SetAnimation("Idle");
	_animator->Play();

	_player = GameObject::FindObjectByTag(GameObjectTag::PLAYER)->GetComponent<Player>(COMPONENT_ID::BEHAVIOUR);
}

void FireWall::Start(void) noexcept
{
}

void FireWall::Update(float fElapsedTime) noexcept
{
	_lastElapsedTime = fElapsedTime;
	transform->Translate(_vDir * _speed * fElapsedTime);

	_deltaTime += fElapsedTime;

	if (_deltaTime > 3)
		gameObject->Destroy();
}

void FireWall::OnDestroy(void) noexcept
{
}

void FireWall::OnCollisionEnter(Collider* mine, Collider* other) noexcept
{
}

void FireWall::OnCollisionStay(Collider* mine, Collider* other) noexcept
{
	if (other->GetTag() == "hitbox" && other->GetGameObject()->GetTag() == GameObjectTag::PLAYER)
	{
		_player->GetHit(5 * _lastElapsedTime, transform->GetWorldPosition());
		//gameObject->Destroy();
	}
}

void FireWall::OnCollisionExit(Collider* mine, Collider* other) noexcept
{
}

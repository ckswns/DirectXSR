#include "pch.h"
#include "LightningBreath.h"
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

LightningBreath::LightningBreath(D3DXVECTOR3 pos, D3DXVECTOR3 vDir, int dir) :
	_startPos(pos),
	_dir(dir),
	_vDir(vDir)
{
}

void LightningBreath::Awake(void) noexcept
{
	transform->SetWorldPosition(_startPos);
	transform->SetLocalScale(0.5f, 0.5f, 0.5f);

	gameObject->AddComponent(new BillboardObj());
	gameObject->AddComponent(new SphereCollider(0.1f));
	gameObject->AddComponent(new Rigidbody());

	EffectRenderer* er = static_cast<EffectRenderer*>(gameObject->AddComponent(new EffectRenderer()));
	er->SetTexture(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Diablo\\Lightning\\" + std::to_string(_dir) + "\\0.png"));

	_animator = new Animator(true);

	std::vector<float> vFrame;
	std::vector<Texture*> vTex;

	for (int i = 0; i < 15; i++)
	{
		vFrame.push_back(0.05f);
		vTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Diablo\\Lightning\\"
			+ std::to_string(_dir) + "\\" + std::to_string(i) + ".png"));
	}

	Animation* ani = new Animation(vFrame, vTex, true);
	ani->SetMaterial(er->GetMaterialPTR());
	_animator->InsertAnimation("Idle", ani);

	gameObject->AddComponent(_animator);
	_animator->SetAnimation("Idle");
	_animator->Play();

	_player = GameObject::FindObjectByTag(GameObjectTag::PLAYER)->GetComponent<Player>(COMPONENT_ID::BEHAVIOUR);
	gameObject->SetLayer(GameObjectLayer::EFFECT);
}

void LightningBreath::Start(void) noexcept
{
}

void LightningBreath::Update(float fElapsedTime) noexcept
{
	_lastElapsedTime = fElapsedTime;
	transform->Translate(_vDir * _speed * fElapsedTime);

	_deltaTime += fElapsedTime;

	if (_deltaTime > 3)
		gameObject->Destroy();
}

void LightningBreath::OnDestroy(void) noexcept
{
}

void LightningBreath::OnCollisionEnter(Collider* mine, Collider* other) noexcept
{

}

void LightningBreath::OnCollisionStay(Collider* mine, Collider* other) noexcept
{
	if (other->GetTag() == "hitbox" && other->GetGameObject()->GetTag() == GameObjectTag::PLAYER)
	{
		_player->GetHit(5 * _lastElapsedTime, transform->GetWorldPosition());
		//gameObject->Destroy();
	}
}

void LightningBreath::OnCollisionExit(Collider* mine, Collider* other) noexcept
{
}

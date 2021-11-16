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

void Cow::Awake(void) noexcept
{
	memcpy(&_data, &GAMEDATAMANAGER->GetActorData("Cow"), sizeof(Actor::Data));
}

void Cow::Start(void) noexcept
{
	_spriteRenderer = static_cast<SpriteRenderer*>(gameObject->AddComponent(new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Cow\\Idle\\1.png"))));
	gameObject->AddComponent(new BillboardObj());
	gameObject->AddComponent(new BoxCollider(D3DXVECTOR3(0.5f, 1, 0.5f)));
	gameObject->AddComponent(new Rigidbody());
	gameObject->GetTransform()->SetLocalPosition(0, 0.6f, 0);

	_animator = new Animator(true);

	std::vector<float> frameTime;
	std::vector<Texture*> frameTex;

	{
		for (int i = 1; i <= 10; i++)
		{
			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Cow\\Idle\\" + std::to_string(i) + ".png"));
		}

		Animation* ani = new Animation(frameTime, frameTex, true);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Idle", ani);

		frameTime.clear();
		frameTex.clear();
	}

	{
		for (int i = 1; i <= 8; i++)
		{
			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Cow\\Walk\\" + std::to_string(i) + ".png"));
		}

		Animation* ani = new Animation(frameTime, frameTex, true);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Walk", ani);

		frameTime.clear();
		frameTex.clear();
	}

	{
		for (int i = 1; i <= 19; i++)
		{
			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Cow\\Attack\\" + std::to_string(i) + ".png"));
		}

		Animation* ani = new Animation(frameTime, frameTex, true);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());

		_animator->InsertAnimation("Attack", ani);

		frameTime.clear();
		frameTex.clear();
	}

	{
		for (int i = 1; i <= 14; i++)
		{
			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Cow\\Death\\" + std::to_string(i) + ".png"));
		}

		Animation* ani = new Animation(frameTime, frameTex, false);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());

		_animator->InsertAnimation("Death", ani);

		frameTime.clear();
		frameTex.clear();
	}

	_animator->SetAnimation("Idle");
	_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Idle")->GetTexture()[0]);

	gameObject->AddComponent(_animator);
	gameObject->SetTag(GameObjectTag::MONSTER);

	GameObject* player = GameObject::FindObjectByTag(GameObjectTag::PLAYER);
}

void Cow::FixedUpdate(float fElapsedTime) noexcept
{

}

void Cow::Update(float fElapsedTime) noexcept
{
	//static float a = 255;

	//if (a > 0)
	//	a -= (fElapsedTime * 0.1f);
	//else
	//	a = 0;
	//_spriteRenderer->SetColor(D3DCOLOR_ARGB((int)a, 255, 255, 255)); // 알파 변경 테스트
}

void Cow::LateUpdate(float fElapsedTime) noexcept
{

}

void Cow::OnDestroy(void) noexcept
{

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



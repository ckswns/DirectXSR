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

void Cow::Awake(void) noexcept
{
	memcpy(&_data, &GAMEDATAMANAGER->GetActorData("Cow"), sizeof(Actor::Data));
}

void Cow::Start(void) noexcept
{
	SpriteRenderer* sr = static_cast<SpriteRenderer*>(gameObject->AddComponent(new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Cow\\Idle\\1.png"))));
	gameObject->AddComponent(new BillboardObj());
	gameObject->AddComponent(new BoxCollider(D3DXVECTOR3(0.5f, 1, 0.5f)));
	gameObject->GetTransform()->SetLocalPosition(0, 0.6f, 0);

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
		ani->SetMaterial(sr->GetMaterialPTR());
		_animator->InsertAnimation("Idle_" + std::to_string(i), ani);

		frameTime.clear();
		frameTex.clear();
	}

	gameObject->AddComponent(_animator);
}

void Cow::FixedUpdate(float fElapsedTime) noexcept
{

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

void Cow::Update(float fElapsedTime) noexcept
{

}

void Cow::GetHit(float damage) noexcept
{

}

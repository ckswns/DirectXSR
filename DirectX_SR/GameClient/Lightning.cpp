#include "pch.h"
#include "Lightning.h"
#include "Animation.h"
#include "Animator.h"
#include "BoxCollider.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "RigidBody.h"
#include "BillboardObj.h"
#include "Player.h"
#include "Transform.h"
#include "AudioSource.h"
void Lightning::Start(void) noexcept
{
	SpriteRenderer* sr= static_cast<SpriteRenderer*>(D3D9DEVICE->GetDevice(),gameObject->AddComponent(new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Mephisto\\Lightning\\0.png"))));
//	gameObject->AddComponent(new BillboardObj());
	gameObject->AddComponent(new BoxCollider(D3DXVECTOR3(0.3f, 1, 1)));
	gameObject->AddComponent(new Rigidbody());

	_pAnimator = new Animator(true);
	gameObject->AddComponent(_pAnimator);
	std::vector<float> frameTime;
	std::vector<Texture*> frameTex;

	for (int i = 0; i < 8; i++)
	{
		char str[256];
		sprintf_s(str, 256, "Asset\\Actor\\Monster\\Mephisto\\Lightning\\%d.png", i);;

		frameTex.push_back(ASSETMANAGER->GetTextureData(str));
		frameTime.push_back(0.05f);
	}

	Animation* ani = new Animation(frameTime, frameTex, false);
	ani->SetMaterial(sr->GetMaterialPTR());
	_pAnimator->InsertAnimation("Lightning", ani);
	_pAnimator->SetAnimation("Lightning");

	frameTime.clear();
	frameTex.clear();


	_audio = static_cast<AudioSource*>(gameObject->AddComponent(new AudioSource()));
	_audio->Init();
	_audio->SetSoundWorld(true);
	_audio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Monster\\Mephisto\\Lightning.wav"));
	
}

void Lightning::Update(float fElapsedTime) noexcept
{
	if (_pAnimator->GetCurrentAnimationEnd()) 
	{
		_audio->Stop();
		gameObject->SetActive(false);
	}
}

void Lightning::OnEnable(void) noexcept
{
	_pAnimator->Play();
//	_pAnimator->SetAnimation("Lightning");
	_audio->Play();
}

void Lightning::OnCollisionEnter(Collider* mine, Collider* other) noexcept
{
	if (other->GetGameObject()->GetTag() == GameObjectTag::PLAYER && other->GetTag() == "hitbox")
	{
		other->GetGameObject()->GetComponent<Player>(COMPONENT_ID::BEHAVIOUR)->GetHit(Random::GetValue(_fMinDamage, _fMaxDamage), GetTransform()->GetWorldPosition());
	}
}

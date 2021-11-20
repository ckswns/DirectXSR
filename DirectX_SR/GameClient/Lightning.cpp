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
	_bHit = false;
	SpriteRenderer* sr= static_cast<SpriteRenderer*>(gameObject->AddComponent(new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Mephisto\\Lightning\\0.png"))));
//	gameObject->AddComponent(new BillboardObj());
	_collider = static_cast<BoxCollider*>(gameObject->AddComponent(new BoxCollider(D3DXVECTOR3(2, 1, 2))));
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
		frameTime.push_back(0.08f);
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
		_collider->SetEnable(false);
		gameObject->SetActive(false);
		//_bHit = false;
	}
}

void Lightning::Using()
{
	_collider->SetEnable(true);
	gameObject->SetActive(true);
	_pAnimator->Play();
	_audio->Play();
}

void Lightning::OnCollisionEnter(Collider* mine, Collider* other) noexcept
{
	if (other->GetGameObject()->GetTag() == GameObjectTag::PLAYER && other->GetTag() == "hitbox")
	{
		other->GetGameObject()->GetComponent<Player>(COMPONENT_ID::BEHAVIOUR)->GetHit(Random::GetValue(_fMinDamage, _fMaxDamage), GetTransform()->GetWorldPosition());
		//_bHit = true;
	}
}

//void Lightning::OnCollisionStay(Collider* mine, Collider* other) noexcept
//{
//	if (other->GetGameObject()->GetTag() == GameObjectTag::PLAYER && other->GetTag() == "hitbox")
//	{
//		if (!_bHit)
//		{
//			_bHit = true;
//			other->GetGameObject()->GetComponent<Player>(COMPONENT_ID::BEHAVIOUR)->GetHit(Random::GetValue(_fMinDamage, _fMaxDamage), GetTransform()->GetWorldPosition());
//		}
//	}
//}

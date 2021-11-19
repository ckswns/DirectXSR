#include "pch.h"
#include "Missile.h"
#include "Animation.h"
#include "Animator.h"
#include "SphereCollider.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "RigidBody.h"
#include "BillboardObj.h"
#include "Player.h"
#include "Transform.h"
#include "AudioSource.h"

void Missile::Start(void) noexcept
{
	_fDelta = 0;
	_bMoving = true;

	_spriteRenderer = static_cast<SpriteRenderer*>(gameObject->AddComponent(new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Mephisto\\Misslie\\0.png"))));
	gameObject->AddComponent(new BillboardObj());
	gameObject->AddComponent(new SphereCollider(0.3f));
	gameObject->AddComponent(new Rigidbody());

	_pAnimator = new Animator(true);
	gameObject->AddComponent(_pAnimator);
	std::vector<float> frameTime;
	std::vector<Texture*> frameTex;

	for (int i = 0; i < 10; i++)
	{
		char str[256];
		sprintf_s(str, 256, "Asset\\Actor\\Monster\\Mephisto\\Misslie\\%d.png", i);
		frameTex.push_back(ASSETMANAGER->GetTextureData(str));
		frameTime.push_back(0.05f);
	}
	Animation* ani = new Animation(frameTime, frameTex, true);
	ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
	_pAnimator->InsertAnimation("Missile", ani);

	for (int i = 0; i < 12; i++)
	{
		char str[256];
		sprintf_s(str, 256, "Asset\\Actor\\Monster\\Mephisto\\MisslieExplosion\\%d.png", i);
		frameTex.push_back(ASSETMANAGER->GetTextureData(str));
		frameTime.push_back(0.05f);
	}
	ani = new Animation(frameTime, frameTex, false);
	ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
	_pAnimator->InsertAnimation("Explosion", ani);

	frameTime.clear();
	frameTex.clear();

	_audio = static_cast<AudioSource*>(gameObject->AddComponent(new AudioSource()));
	_audio->Init();
	_audio->SetSoundWorld(true);
	_audio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Monster\\Mephisto\\Misslie.wav"));
	_audio->Play();

	_pAnimator->SetAnimation("Missile");

}

void Missile::Update(float fElapsedTime) noexcept
{
	if (_bMoving) 
	{
		if (_fDelta >= 3)
		{
			_fDelta = 3;
			gameObject->Destroy();
			return;
		}
		else
		{
			_fDelta += fElapsedTime;
			GetTransform()->Translate(_vDir * 3 * fElapsedTime);
		}
	}
	else 
	{
		if (_pAnimator->GetCurrentAnimationName() == "Explosion")
		{
			if (_pAnimator->GetCurrentAnimationEnd())
				gameObject->Destroy();
		}
	}
}

void Missile::OnCollisionEnter(Collider* mine, Collider* other) noexcept
{
	if (other->GetGameObject()->GetTag() == GameObjectTag::PLAYER && other->GetTag() == "hitbox")
	{
		other->GetGameObject()->GetComponent<Player>(COMPONENT_ID::BEHAVIOUR)->GetHit(Random::GetValue(_fMinDamage, _fMaxDamage), GetTransform()->GetWorldPosition());
		
		_bMoving = false;
		_spriteRenderer->SetTexture(_pAnimator->GetAnimationByKey("Explosion")->GetTexture()[0]);
		_pAnimator->SetAnimation("Explosion");
		
		_audio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Monster\\Mephisto\\MisslieExplosion.wav"));
		_audio->Play();
	}
}

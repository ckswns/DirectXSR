#include "pch.h"
#include "Lightning.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "BillboardObj.h"
#include "Transform.h"
#include "AudioSource.h"
#include "LightningCollider.h"

void Lightning::Start(void) noexcept
{
	_spriteRenderer = static_cast<SpriteRenderer*>(gameObject->AddComponent(new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Mephisto\\RedLightningHose\\0\\0.png"))));
		gameObject->AddComponent(new BillboardObj());

	gameObject->SetTag(GameObjectTag::MONSTER);

	_pAnimator = new Animator(true);
	gameObject->AddComponent(_pAnimator);
	std::vector<float> frameTime;
	std::vector<Texture*> frameTex;

	for (int folder = 0; folder < 8; folder++)
	{
		for (int i = 0; i < 15; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Actor\\Monster\\Mephisto\\RedLightningHose\\%d\\%d.png",folder, i);

			frameTex.push_back(ASSETMANAGER->GetTextureData(str));
			frameTime.push_back(0.05f);
		}

		Animation* ani = new Animation(frameTime, frameTex, false);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_pAnimator->InsertAnimation("Lightning_"+std::to_string(folder), ani);

		frameTime.clear();
		frameTex.clear();
	}
	_pAnimator->SetAnimation("Lightning_0");


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
		_lCollider->GetGameObject()->Destroy();
		_lCollider = nullptr;
	}
}

void Lightning::Using(Actor::Direction dir, D3DXVECTOR3 vDir)
{
	gameObject->SetActive(true);

	GameObject* obj = GameObject::Instantiate();
	_lCollider = new LightningCollider(_fMinDamage,_fMaxDamage);
	obj->AddComponent(_lCollider);
	obj->GetTransform()->SetParent(GetTransform());
	obj->GetTransform()->SetLocalPosition(vDir);

	std::string name = "Lightning_" + std::to_string((int)dir);
	_spriteRenderer->SetTexture(_pAnimator->GetAnimationByKey(name)->GetTexture()[0]);
	_pAnimator->SetAnimation(name);
	_audio->Play();
}


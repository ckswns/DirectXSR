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

	_fireAudio->SetSoundWorld(true);
	_breathAudio->SetSoundWorld(true);
	_castAudio->SetSoundWorld(true);
	_initAudio->SetSoundWorld(true);
	_laughAudio->SetSoundWorld(true);
	_attackAudio->SetSoundWorld(true);
	_getHitAudio->SetSoundWorld(true);
	_deadAudio->SetSoundWorld(true);
	_hitEffectAudio->SetSoundWorld(true);

	_fireAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Diablo\\DiabloSkill1.wav"));
	_breathAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Diablo\\DiabloBreath.wav"));
	_castAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Diablo\\DiabloCast.wav"));
	_initAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Diablo\\DiabloInit.wav"));
	_laughAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Diablo\\DiabloLaugh.wav"));
	_attackAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Diablo\\DiabloAttack.wav"));
	_getHitAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Diablo\\DiabloHit.wav"));
	_deadAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Diablo\\DiabloDead.wav"));
	_hitEffectAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Effect\\Blunt_GetHit.wav"));

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

		Animation* ani = new Animation(vFrame, vTex, true);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Attack_" + std::to_string(i), ani);

		vFrame.clear();
		vTex.clear();
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int index = i * 9 + j + 1;

			vFrame.push_back(0.1f);
			vTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Diablo\\Block\\"
				+ std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(vFrame, vTex, true);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Attack2_" + std::to_string(i), ani);

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

		Animation* ani = new Animation(vFrame, vTex, true);
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

		Animation* ani = new Animation(vFrame, vTex, true);
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

		Animation* ani = new Animation(vFrame, vTex, true);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
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

	Animation* ani = new Animation(vFrame, vTex, true);
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
}

void Diablo::Update(float fElapsedTime) noexcept
{
}

void Diablo::LateUpdate(float fElapsedTime) noexcept
{
}

void Diablo::OnDestroy(void) noexcept
{
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
}

void Diablo::OnAnimationEvent(std::string str) noexcept
{
}

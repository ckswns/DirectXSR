#include "pch.h"
#include "FireBall.h"
#include "SpriteRenderer.h"
#include "Animation.h"
#include "Animator.h"
#include "BillboardObj.h"
#include "BoxCollider.h"
#include "Texture.h"
#include "Transform.h"
//#include "R"

FireBall::FireBall(Actor::Direction tDir, D3DXVECTOR3 vdir, D3DXVECTOR3 vpos) noexcept
	: _fSpeed(3.f) ,_tdir(tDir), _fangle(0), _fDeltaTime(0), _vdir(vdir),_vpos(vpos)
{
}

void FireBall::Start(void) noexcept
{
	transform->SetWorldPosition(_vpos);
	_spriteRenderer = static_cast<SpriteRenderer*>(gameObject->AddComponent(new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Witch\\FireBall\\0.png"))));
	gameObject->AddComponent(new BillboardObj());
	_hitBox = static_cast<BoxCollider*>(gameObject->AddComponent(new BoxCollider(D3DXVECTOR3(0.5f, 1, 0.5f), D3DXVECTOR3(0, 0, 0), "FireBall")));
	/*gameObject->AddComponent(new Rigidbody());*/

	_animator = new Animator(true);

	std::vector<float> frameTime;
	std::vector<Texture*> frameTex;
	
	_vdir.y = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			int index = i * 14 + j;

			frameTime.push_back(0.1f);
			frameTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Actor\\Monster\\Witch\\FireBall\\" + std::to_string(index) + ".png"));
		}

		Animation* ani = new Animation(frameTime, frameTex, true);
		ani->SetMaterial(_spriteRenderer->GetMaterialPTR());
		_animator->InsertAnimation("Fire_" + std::to_string(i), ani);

		frameTime.clear();
		frameTex.clear();
	}

	_spriteRenderer->SetTexture(_animator->GetAnimationByKey("Fire_" + std::to_string(static_cast<int>(_tdir)))->GetTexture()[0]);
	_animator->SetAnimation("Fire_" + std::to_string(static_cast<int>(_tdir)));

	gameObject->AddComponent(_animator);
	gameObject->SetTag(GameObjectTag::OBJECT);

	_animator->Play();
}

void FireBall::Update(float fElapsedTime) noexcept
{
	transform->Translate(_vdir * fElapsedTime * _fSpeed);

	if (_fDeltaTime < 3)
	{
		_fDeltaTime += fElapsedTime;

		if (_fDeltaTime > 3)
			gameObject->Destroy();
	}
	else
	{
		gameObject->Destroy();
	}
}

void FireBall::OnCollisionEnter(Collider* mine, Collider* other) noexcept
{
}

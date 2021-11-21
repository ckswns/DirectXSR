#include "pch.h"
#include "Portal.h"
#include "SpriteRenderer.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"
#include "BillboardObj.h"
#include "SphereCollider.h"
#include "Ray.h"
#include "Camera.h"
#include "ParticleRenderer.h"
#include "FadeController.h"

Portal::Portal(const char* key) noexcept :
	_sceneKey(key)
{

}

void Portal::Start(void) noexcept
{
	std::vector<float> vFrame;
	std::vector<Texture*> vTex;

	for (int i = 1; i <= 30; i++)
	{
		vFrame.push_back(0.1f);
		vTex.push_back(ASSETMANAGER->GetTextureData("Asset\\Portal\\" + std::to_string(i) + ".png"));
	}

	Animation* ani = new Animation(vFrame, vTex, true);
	Animator* anim = new Animator();
	SpriteRenderer* sr = new SpriteRenderer(D3D9DEVICE->GetDevice(), vTex[0], false, D3DCULL_NONE);
	ani->SetMaterial(sr->GetMaterialPTR());
	anim->InsertAnimation("idle", ani);
	anim->SetAnimation("idle");
	gameObject->AddComponent(sr);
	gameObject->AddComponent(anim);
	gameObject->AddComponent(new BillboardObj());
	anim->Play();
	gameObject->AddComponent(new SphereCollider(0.5f, "portal"));

	GameObject* player = GameObject::FindObjectByTag(GameObjectTag::PLAYER);
	if(player != nullptr)
		_player = player->GetTransform();
	//gameObject->AddComponent(new ParticleRenderer(D3D9DEVICE->GetDevice(), "Asset\\Data\\portal.dat"));
}

void Portal::Update(float) noexcept
{
	if (_player == nullptr)
	{
		GameObject* player = GameObject::FindObjectByTag(GameObjectTag::PLAYER);
		if (player != nullptr)
			_player = player->GetTransform();
		else
			return;
	}

	if (_changeScene)
	{
		if (FadeController::IsEnd())
			SCENEMANAGER->LoadScene(_sceneKey);
	}
	else if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		D3DXVECTOR3 player = _player->GetWorldPosition();
		D3DXVECTOR3 mine = transform->GetWorldPosition();
		
		player.y = 0;
		mine.y = 0;

		D3DXVECTOR3 temp = (player - mine);
		float dis = D3DXVec3Length(&temp);

		if (dis > 1.f)
		{
			return;
		}

		Ray ray = Camera::GetMainCamera()->ScreenPointToRay(INPUT->GetMousePosition());
		RaycastHit hit;

		if (Physics::Raycast(ray, hit, GameObjectLayer::ALPHA))
		{
			if (hit.collider->GetTag() == "portal")
			{
				_changeScene = true;
				FadeController::FadeOut(3);
			}
		}
	}
}

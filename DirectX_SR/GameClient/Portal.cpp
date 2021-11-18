#include "pch.h"
#include "Portal.h"
#include "SpriteRenderer.h"
#include "Animation.h"
#include "Animator.h"
#include "Texture.h"
#include "BillboardObj.h"
#include "SphereCollider.h"
#include "Ray.h"

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
}

void Portal::Update(float) noexcept
{

}

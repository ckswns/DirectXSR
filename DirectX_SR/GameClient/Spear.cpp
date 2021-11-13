#include "pch.h"
#include "Spear.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Animation.h"

void Spear::Start(void) noexcept
{
	SpriteRenderer* sr = new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Player\\Skill\\BoneSpear\\Spear\\0.png"));
	gameObject ->AddComponent(sr);

	Animator* pAnimator = new Animator(true);
	gameObject->AddComponent(pAnimator);

	std::vector<Texture*> TList;
	std::vector<float>		FrameTime;
	Animation* ani;
	//Spear
	for (int i = 0; i < 6; i++)
	{
		char str[256];
		sprintf_s(str, 256, "Asset\\Player\\Skill\\BoneSpear\\Spear\\%d.png", i);;

		TList.push_back(ASSETMANAGER->GetTextureData(str));
		FrameTime.push_back(0.1f);
	}

	ani = new Animation(FrameTime, TList, true);
	ani->SetMaterial(sr->GetMaterialPTR());
	pAnimator->InsertAnimation("Spear", ani);

	TList.clear();
	FrameTime.clear();
}




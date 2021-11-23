#include "pch.h"
#include "Gold.h"
#include "SphereCollider.h"
#include "SpriteRenderer.h"
#include "Animation.h"
#include "Animator.h"
#include "Transform.h"
#include "Slot.h"
Gold::Gold() noexcept
{
	_tInvenItem = new ITEMDATA();
	_tInvenItem->sellgold = CE_MATH::Random(50, 100);
}

void Gold::Start(void) noexcept
{
	gameObject->SetTag(GameObjectTag::OBJECT);
	gameObject->SetName("Gold");

	gameObject->AddComponent(new SphereCollider(0.5f));
	SpriteRenderer* sr = new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Item\\Gold\\0.png"));
	gameObject->AddComponent(sr);

	Animator* pAnimator = new Animator(true);
	gameObject->AddComponent(pAnimator);

	std::vector<Texture*> TList;
	std::vector<float>	FrameTime;
	Material* material = sr->GetMaterialPTR();

	for (int i = 0; i < 17; i++)
	{
		char str[256];
		sprintf_s(str, 256, "Asset\\Item\\Gold\\%d.png", i);

		TList.push_back(ASSETMANAGER->GetTextureData(str));
		FrameTime.push_back(0.05f);
	}

	Animation* ani = new Animation(FrameTime, TList, false);
	ani->SetMaterial(material);
	pAnimator->InsertAnimation(_tInvenItem->name, ani);

	TList.clear();
	FrameTime.clear();

	//Item::Start();
}

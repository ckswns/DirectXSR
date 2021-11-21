#include "pch.h"
#include "Gold.h"
#include "BoxCollider.h"
#include "SpriteRenderer.h"
#include "Animation.h"
#include "Animator.h"
#include "Transform.h"
#include "Slot.h"
Gold::Gold() noexcept
{
	_tInvenItem = new INVENITEMINFO((int)Slot::SLOTTYPE::END, CE_MATH::Random(100, 300));
	_tInvenItem->_eitemID = (int)ITEM_ID::EQUIP;
	_tInvenItem->_strName = "Gold";
}

void Gold::Start(void) noexcept
{
	gameObject->SetTag(GameObjectTag::OBJECT);
	gameObject->SetName("Gold");

	gameObject->AddComponent(new BoxCollider(D3DXVECTOR3(0.3f, 0.5f, 0.3f), D3DXVECTOR3(0, -0.5f, 0)));
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
	pAnimator->InsertAnimation(_tInvenItem->_strName, ani);

	TList.clear();
	FrameTime.clear();

	Item::Start();
}

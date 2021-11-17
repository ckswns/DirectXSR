#include "pch.h"
#include "PlateArmor.h"
#include "BoxCollider.h"
#include "SpriteRenderer.h"
#include "Animation.h"
#include "Animator.h"
#include "Transform.h"
#include "Slot.h"
PlateArmor::PlateArmor() noexcept
{
	_tInvenItem._eitemID = (int)ITEM_ID::EQUIP;
	_tInvenItem._eSlotType = (int)Slot::SLOTTYPE::BODY;
	_tInvenItem._strName = "Plate Armor";
//	_tInvenItem._strInvenImgPath = "Asset\\UI\\Inventory\\Mp";
	_tInvenItem._iValue = 500;
}

void PlateArmor::Start(void) noexcept
{
	gameObject->SetTag(GameObjectTag::OBJECT);
	gameObject->SetName("Item");

	gameObject->AddComponent(new BoxCollider(D3DXVECTOR3(0.3f, 0.5f, 0.3f), D3DXVECTOR3(0, -0.5f, 0)));
	SpriteRenderer* sr = new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Item\\PlateArmor\\0.png"));
	gameObject->AddComponent(sr);

	Animator* pAnimator = new Animator(true);
	gameObject->AddComponent(pAnimator);

	std::vector<Texture*> TList;
	std::vector<float>	FrameTime;
	Material* material = sr->GetMaterialPTR();

	for (int i = 0; i < 17; i++)
	{
		char str[256];
		sprintf_s(str, 256, "Asset\\Item\\PlateArmor\\%d.png", i);

		TList.push_back(ASSETMANAGER->GetTextureData(str));
		FrameTime.push_back(0.05f);
	}

	Animation* ani = new Animation(FrameTime, TList, false);
	ani->SetMaterial(material);
	pAnimator->InsertAnimation(_tInvenItem._strName, ani);

	TList.clear();
	FrameTime.clear();

	Item::Start();
}

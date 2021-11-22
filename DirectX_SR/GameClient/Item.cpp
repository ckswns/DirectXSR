#include "pch.h"
#include "Item.h"
#include "SphereCollider.h"
#include "SpriteRenderer.h"
#include "Animation.h"
#include "Animator.h"
#include "Transform.h"

Item::Item(ITEMDATA* item, D3DXVECTOR3 vPlayerPos) noexcept
	:_tInvenItem(item), _vPlayerPos(vPlayerPos)
{
}
void Item::Start(void) noexcept
{
	gameObject->SetTag(GameObjectTag::OBJECT);
	gameObject->SetName("Item");

	gameObject->AddComponent(new SphereCollider(0.3f));
	
	std::string strPath(_tInvenItem->imgPath);
	SpriteRenderer* sr = new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData(strPath +"0.png"));
	gameObject->AddComponent(sr);

	Animator* pAnimator = new Animator(true);
	gameObject->AddComponent(pAnimator);

	std::vector<Texture*> TList;
	std::vector<float>	FrameTime;
	Material* material = sr->GetMaterialPTR();

	for (int i = 0; i < 17; i++)
	{
		std::string aniPath = strPath + std::to_string(i) + ".png";

		TList.push_back(ASSETMANAGER->GetTextureData(aniPath));
		FrameTime.push_back(0.05f);
	}

	Animation* ani = new Animation(FrameTime, TList, false);
	ani->SetMaterial(material);
	pAnimator->InsertAnimation(_tInvenItem->name, ani);

	D3DXVECTOR3 pos;
	pos.x = CE_MATH::Random(_vPlayerPos.x - 1, _vPlayerPos.x + 1);
	pos.y = 1;
	pos.z = CE_MATH::Random(_vPlayerPos.z - 1, _vPlayerPos.z + 1);

	GetTransform()->SetWorldPosition(pos);

	TList.clear();
	FrameTime.clear();
}

#include "pch.h"
#include "StoreNPC.h"
#include "Animation.h"
#include "Animator.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "RectTransform.h"
#include "StoreWnd.h"
void StoreNPC::Start(void) noexcept
{
	SpriteRenderer* sr = new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Player\\Player.png"), false);
	gameObject->AddComponent(sr);
	Animator* pAnimator = new Animator(true);
	gameObject->AddComponent(pAnimator);

	std::vector<Texture*> TList;
	std::vector<float>	FrameTime;
	Material* material = sr->GetMaterialPTR();

	for (int i = 0; i < 13; i++)
	{
		char str[256];
		sprintf_s(str, 256, "Asset\\NPC\\8\\%d.png", i);

		TList.push_back(ASSETMANAGER->GetTextureData(str));
		FrameTime.push_back(0.3f);
	}

	Animation* ani = new Animation(FrameTime, TList, true);
	ani->SetMaterial(material);
	std::string name = "Stand";
	pAnimator->InsertAnimation(name, ani);

	TList.clear();
	FrameTime.clear();

	_pStoreWndObj = GameObject::Instantiate();
	//_pStoreWnd = new StoreWnd();
	_pStoreWndObj->AddComponent(new StoreWnd());
	_pStoreWndObj->SetActive(false);

}

void StoreNPC::OnClick()
{
	//»óÁ¡ ¶ç¿ì±â 
	_pStoreWndObj->SetActive(true);

}

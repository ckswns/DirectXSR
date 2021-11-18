#include "pch.h"
#include "StoreNPC.h"
#include "Animation.h"
#include "Animator.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "StoreWnd.h"
#include "GameObject.h"
#include "Player.h"

void StoreNPC::Start(void) noexcept
{
	gameObject->SetName("StoreNPC");
	gameObject->AddComponent(new BoxCollider(D3DXVECTOR3(0.5, 1, 0.5)));

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

	GameObject * pStoreWndObj = GameObject::Instantiate();
	_pStoreWnd = new StoreWnd();
	pStoreWndObj->AddComponent(_pStoreWnd);
	pStoreWndObj->SetActive(false);

}

void StoreNPC::OnClick(Player* player)
{
	//»óÁ¡ ¶ç¿ì±â 
	_pStoreWnd->Open(player->GetInventory());

}

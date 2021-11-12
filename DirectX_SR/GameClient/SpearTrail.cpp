#include "pch.h"
#include "SpearTrail.h"
#include "GameObject.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Animation.h"
SpearTrail::SpearTrail(float AniTime) noexcept
	:_fAniTime(AniTime)
{
}
void SpearTrail::Start(void) noexcept
{
	SpriteRenderer* sr = new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Player\\BoneSpear\\Trail\\0.png"));
	GetGameObject()->AddComponent(sr);

	Animator* pAnimator = new Animator(true);
	GetGameObject()->AddComponent(pAnimator);

	std::vector<Texture*> TList;
	std::vector<float>		FrameTime;
	Animation* ani;
	//Spear
	for (int i = 0; i < 9; i++)
	{
		char str[256];
		sprintf_s(str, 256, "Asset\\Player\\BoneSpear\\Trail\\%d.png", i);

		TList.push_back(ASSETMANAGER->GetTextureData(str));
		FrameTime.push_back(_fAniTime);
	}

	ani = new Animation(FrameTime, TList, true);
	ani->SetMaterial(sr->GetMaterialPTR());
	pAnimator->InsertAnimation("Trail", ani);

	TList.clear();
	FrameTime.clear();
}

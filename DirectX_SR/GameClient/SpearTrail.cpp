#include "pch.h"
#include "SpearTrail.h"
#include "GameObject.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Animation.h"
SpearTrail::SpearTrail(float AniTime, DIR eDir) noexcept
	:_fAniTime(AniTime), _eDir(eDir)
{
}
void SpearTrail::Start(void) noexcept
{
	SpriteRenderer* sr = new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Player\\Skill\\BoneSpear\\Trail\\0\\0.png"),true,false);
	gameObject->AddComponent(sr);

	Animator* pAnimator = new Animator(true);
	gameObject->AddComponent(pAnimator);

	std::vector<Texture*> TList;
	std::vector<float>		FrameTime;
	Animation* ani;

	int folder = ((int)_eDir * 2);
	for (int i = 0; i < 9; i++)
	{
		char str[256];
		sprintf_s(str, 256, "Asset\\Player\\Skill\\BoneSpear\\Trail\\%d\\%d.png", folder, i);

		TList.push_back(ASSETMANAGER->GetTextureData(str));
		FrameTime.push_back(_fAniTime);
	}

	ani = new Animation(FrameTime, TList, true);
	ani->SetMaterial(sr->GetMaterialPTR());
	pAnimator->InsertAnimation("Trail_" + std::to_string(folder), ani);

	TList.clear();
	FrameTime.clear();
}


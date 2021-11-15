#include "pch.h"
#include "PoisonProjectile.h"
#include "Transform.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Animation.h"

PoisonProjectile::PoisonProjectile(D3DXVECTOR3 dir,int iAniNum) noexcept
	:_fMaxDist(5.f), _fDist(0), _fSpeed(3.f), _vDir(dir),_iAniNum(iAniNum)
{
}

void PoisonProjectile::Start(void) noexcept
{
	_pTrans = GetGameObject()->GetTransform();
	SpriteRenderer* sr = new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Player\\Skill\\PoisonNova\\0\\0.png"));
	gameObject->AddComponent(sr);

	Animator* pAnimator = new Animator(true);
	gameObject->AddComponent(pAnimator);

	std::vector<Texture*> TList;
	std::vector<float>		FrameTime;
	Animation* ani;

	for (int i = 0; i < 30; i++)
	{
		char str[256];
		sprintf_s(str, 256, "Asset\\Player\\Skill\\PoisonNova\\%d\\%d.png",_iAniNum, i);

		TList.push_back(ASSETMANAGER->GetTextureData(str));
		FrameTime.push_back(0.05f);
	}
	std::string aniName = "PoisonNova_" + std::to_string(_iAniNum);

	ani = new Animation(FrameTime, TList, false);
	ani->SetMaterial(sr->GetMaterialPTR());
	pAnimator->InsertAnimation(aniName, ani);

	TList.clear();
	FrameTime.clear();

	pAnimator->Play(aniName);

}

void PoisonProjectile::Update(float fElapsedTime) noexcept
{
	if (_fDist >= _fMaxDist)
	{
		gameObject->Destroy();
	}
	else
	{
		_fDist += (fElapsedTime * _fSpeed);
		_pTrans->Translate(_vDir * fElapsedTime * _fSpeed);
	}
}

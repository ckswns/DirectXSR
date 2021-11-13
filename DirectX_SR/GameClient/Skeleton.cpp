#include "pch.h"
#include "Skeleton.h"
#include "Transform.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Animation.h"

#include "FSMState.h"
#include "SkeletonCreate.h"
#include "SkeletonStand.h"
#include "SkeletonMove.h"
#include "SkeletoneAttack.h"
#include "SkeletonDead.h"

Skeleton::Skeleton() noexcept
	:_tStat(70, 10, 5), _eCurState(SK_END), _fSpeed(3.f)
{
}

void Skeleton::Start(void) noexcept
{
	_bOnce = false;

	_pTrans = static_cast<Transform*>(GetGameObject()->GetTransform());

	SpriteRenderer* sr = new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Player\\Skeleton.png"));
	gameObject->AddComponent(sr);

	_pAnimator = new Animator(true);
	gameObject->AddComponent(_pAnimator);
	InitAnimation(sr);
	InitState();
}

void Skeleton::Update(float fElapsedTime) noexcept
{
	_pFSM[_eCurState]->Update(fElapsedTime);
}

void Skeleton::Create(Transform* trans)
{
	_pOwnerTrans = trans;
	gameObject->SetActive(true);

	SetState(SK_CREATE);
}

void Skeleton::SetState(SK_STATE newState, DIR eDir, D3DXVECTOR3 vTarget, bool bAtt)
{
	_eCurState = newState;

	if (vTarget != D3DXVECTOR3(0, -5, 0))
		_pFSM[_eCurState]->SetTarget(vTarget);

	if (bAtt)
	{
		static_cast<SkeletonMove*>(_pFSM[_eCurState])->SetAtt();
	}

	if(eDir != DIR_END)
		_pFSM[_eCurState]->SetDir(eDir);
	_pFSM[_eCurState]->Start();
}

void Skeleton::SetPathFinding(PathFinding* pf)
{
	if (_pPathFinding != pf)
	{
		_pPathFinding = pf;
		_pFSM[SK_MOVE] = new SkeletonMove(_pAnimator, _pTrans, _pOwnerTrans, _pPathFinding, _fSpeed);
	}
}

void Skeleton::InitAnimation(SpriteRenderer* sr)
{
	std::vector<Texture*> TList;
	std::vector<float>		FrameTime;
	Texture* _pTexture;
	Animation* ani;

	//Create
	{
		for (int i = 0; i < 12; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Player\\Skill\\Skeleton\\create\\%d.png", i);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.1f);
		}

		ani = new Animation(FrameTime, TList, false);
		ani->SetMaterial(sr->GetMaterialPTR());
		_pAnimator->InsertAnimation("Create", ani);

		TList.clear();
		FrameTime.clear();
	}

	for (int folder = 0; folder < 15; folder += 2)
	{
		//Stand
		for (int i = 0; i < 8; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Player\\Skill\\Skeleton\\stand_%d\\%d.png",folder, i);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.5f);
		}
		ani = new Animation(FrameTime, TList, true);
		ani->SetMaterial(sr->GetMaterialPTR());
		_pAnimator->InsertAnimation("Stand_"+std::to_string(folder), ani);

		TList.clear();
		FrameTime.clear();


		//Walk

		for (int i = 0; i < 8; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Player\\Skill\\Skeleton\\walk_%d\\%d.png",folder, i);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.07f);
		}

		ani = new Animation(FrameTime, TList, true);
		ani->SetMaterial(sr->GetMaterialPTR());
		_pAnimator->InsertAnimation("Walk_" + std::to_string(folder), ani);

		TList.clear();
		FrameTime.clear();


		//Attack

		for (int i = 0; i < 16; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Player\\Skill\\Skeleton\\attack_%d\\%d.png",folder, i);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.05f);
		}

		ani = new Animation(FrameTime, TList, false);
		ani->SetMaterial(sr->GetMaterialPTR());
		_pAnimator->InsertAnimation("Attack_" + std::to_string(folder), ani);

		TList.clear();
		FrameTime.clear();
	}
	//Dead
	{
		for (int i = 0; i < 19; i++)
		{
			char str[256];
			sprintf_s(str, 256, "Asset\\Player\\Skill\\Skeleton\\death\\%d.png", i);

			TList.push_back(ASSETMANAGER->GetTextureData(str));
			FrameTime.push_back(0.1f);
		}

		ani = new Animation(FrameTime, TList, false);
		ani->SetMaterial(sr->GetMaterialPTR());
		_pAnimator->InsertAnimation("Dead", ani);

		TList.clear();
		FrameTime.clear();
	}
}

void Skeleton::InitState()
{
	_pFSM.reserve(SK_END);
	_pFSM.push_back(new SkeletonCreate(_pAnimator));
	_pFSM.push_back(new SkeletonStand(_pAnimator,_pTrans, _pOwnerTrans));
	_pFSM.push_back(new SkeletonMove(_pAnimator, _pTrans, _pOwnerTrans, _pPathFinding, _fSpeed));
	_pFSM.push_back(new SkeletoneAttack(_pAnimator, _pTrans));
	_pFSM.push_back(new SkeletonDead(_pAnimator,gameObject));
}

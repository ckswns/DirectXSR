#include "pch.h"
#include "Skeleton.h"
#include "Transform.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Animation.h"
#include "BoxCollider.h"
#include "RigidBody.h"
#include "AudioSource.h"

#include "FSMState.h"
#include "SkeletonCreate.h"
#include "SkeletonStand.h"
#include "SkeletonMove.h"
#include "SkeletoneAttack.h"
#include "SkeletonDead.h"
#include "RaiseSkeleton.h"

#include "Camera.h"
#include "TargetCamera.h"
#include "GameObject.h"
#include "SphereCollider.h"

Skeleton::Skeleton(RaiseSkeleton* skill) noexcept
	:_pSkill(skill), _tStat(70, 10, 5), _eCurState(SK_END), _fSpeed(3.f), _bOnce(false),
	_fDeltaTime(0), _fSpawnTime(10), _bDestroy(false)
{
}

void Skeleton::Start(void) noexcept
{
	_pTrans = static_cast<Transform*>(GetGameObject()->GetTransform());

	SphereCollider* trigger = new SphereCollider(2, "Trigger");
	gameObject->AddComponent(trigger);
	gameObject->AddComponent(new Rigidbody());

	_pRaiseAudio = static_cast<AudioSource*>(gameObject->AddComponent(new AudioSource()));
	_pRaiseAudio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Player\\skeletonraise.wav"));

	_spriteRenderer = new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\Player\\Skeleton.png"),true,false);
	gameObject->AddComponent(_spriteRenderer);

	_pAnimator = new Animator(true);
	gameObject->AddComponent(_pAnimator);
	InitAnimation(_spriteRenderer);
	InitState();
}

void Skeleton::Update(float fElapsedTime) noexcept
{
	if (!_bDestroy) 
	{
		_fDeltaTime += fElapsedTime;
		if (_fDeltaTime >= _fSpawnTime)
		{
			_bDestroy = true;
			SetState(SK_DEAD);
			_pSkill->DestroySekelton();
		}
	}
	if (_pCamera->IsFPV())
	{
		_bOnce = true;
		D3DXVECTOR3 Bill = Camera::GetMainCamera()->GetTransform()->GetBillboardEulerAngleY();
		_pTrans->SetLocalEulerAngle(Bill);
	}
	else if (_bOnce)
	{
		_bOnce = false;
		D3DXVECTOR3 Bill = Camera::GetMainCamera()->GetTransform()->GetBillboardEulerAngleY();
		_pTrans->SetLocalEulerAngle(Bill);
	}

	_pFSM[_eCurState]->Update(fElapsedTime);

	if (_prevAniName != _pAnimator->GetCurrentAnimationName())
	{
		_prevAniName = _pAnimator->GetCurrentAnimationName();
		_spriteRenderer->SetTexture(_pAnimator->GetAnimationByKey(_prevAniName)->GetTexture()[0]);
	}
}

void Skeleton::OnDestroy(void) noexcept
{
	for (size_t i = 0; i < _pFSM.size(); ++i)
	{
		if (_pFSM[i] != nullptr)
		{
			delete _pFSM[i];
			_pFSM[i] = nullptr;
		}
	}
	_pFSM.clear();
}

void Skeleton::Create(Transform* trans)
{
	if (!_pCamera)
	{
		_pCamera = static_cast<TargetCamera*>(Camera::GetMainCamera()->GetGameObject()->GetComponent(COMPONENT_ID::BEHAVIOUR));
	}

	_pOwnerTrans = trans;
	gameObject->SetActive(true);

	_fDeltaTime = 0;
	_bDestroy = false;

	_pFSM[SK_STAND] = new SkeletonStand(_pAnimator, _pTrans, _pOwnerTrans);
	_pFSM[SK_MOVE] = new SkeletonMove(_pAnimator, _pTrans, _pOwnerTrans, _pPathFinding, _fSpeed);

	_pRaiseAudio->Play();

	SetState(SK_CREATE);
}

void Skeleton::SetState(SK_STATE newState, DIR eDir, D3DXVECTOR3 vTarget)
{
	_eCurState = newState;

	if (vTarget != D3DXVECTOR3(0, -5, 0))
		_pFSM[_eCurState]->SetTarget(vTarget);

	if (newState == SK_MOVE)
	{
		static_cast<SkeletonMove*>(_pFSM[_eCurState])->SetAtt(false);
		_pFSM[_eCurState]->SetTargetTrans(nullptr);
	}

	if (eDir != DIR_END)
		_pFSM[_eCurState]->SetDir(eDir);

	_pFSM[_eCurState]->Start();
}

void Skeleton::SetState(SK_STATE newState, Transform* targetTrans, bool bAtt)
{
	_eCurState = newState;

	_pFSM[_eCurState]->SetTargetTrans(targetTrans);

	if (bAtt)
	{
		static_cast<SkeletonMove*>(_pFSM[_eCurState])->SetAtt(bAtt);
	}

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

void Skeleton::OnCollisionEnter(Collider* mine, Collider* other) noexcept
{
	if (_eCurState != SK_ATTACK) 
	{
		if (mine->GetTag() == "Trigger" && other->GetTag() == "Monster")
		{

			SetState(SK_STATE::SK_ATTACK, other->GetTransform());
		}
	}

}

void Skeleton::OnCollisionStay(Collider* mine, Collider* other) noexcept
{
	if (_eCurState != SK_ATTACK)
	{
		if (mine->GetTag() == "Trigger" && other->GetTag() == "Monster")
		{

			SetState(SK_STATE::SK_ATTACK, other->GetTransform());
		}
	}
}

void Skeleton::InitAnimation(SpriteRenderer* sr)
{
	std::vector<Texture*> TList;
	std::vector<float>		FrameTime;
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

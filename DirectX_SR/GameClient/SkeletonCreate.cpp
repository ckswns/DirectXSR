#include "pch.h"
#include "SkeletonCreate.h"
#include "Skeleton.h"
#include "Animator.h"
#include "GameObject.h"

void SkeletonCreate::Start() noexcept
{
	_pSk = static_cast<Skeleton*>(_pAnimator->GetGameObject()->GetComponent(COMPONENT_ID::BEHAVIOUR));
	_pAnimator->SetAnimation("Create");
}

void SkeletonCreate::Update(float fElapsedTime) noexcept
{
	if (_pAnimator->GetCurrentAnimationEnd())
	{
		_pSk->SetState(SK_STAND, FRONT);
	}
}

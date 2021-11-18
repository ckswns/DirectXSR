#include "pch.h"
#include "SkeletonDead.h"
#include "Transform.h"
#include "Animator.h"
#include "GameObject.h"

void SkeletonDead::Start() noexcept
{
	_pAnimator->Play("Dead");
}

void SkeletonDead::Update(float fElapsedTime) noexcept
{
	if (_pAnimator->GetCurrentAnimationEnd())
	{
		_pGameObj->SetActive(false);
	}
}

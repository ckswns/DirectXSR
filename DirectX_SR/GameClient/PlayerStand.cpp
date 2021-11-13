#include "pch.h"
#include "PlayerStand.h"
#include "Animator.h"

void PlayerStand::Start() noexcept
{
	_pAnimator->SetAnimation("Stand_" + std::to_string(_iDir));
}

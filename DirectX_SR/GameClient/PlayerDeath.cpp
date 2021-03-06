#include "pch.h"
#include "PlayerDeath.h"
#include "Player.h"
#include "Animator.h"
#include "Transform.h"

void PlayerDeath::Start() noexcept
{
	if (!_bFPV)
	{
		_eDir = GetDirect(_pTrans->GetWorldPosition(), _vTarget);
		_iDir = (int)_eDir * 2;
	}
	_pAnimator->SetAnimation("Death_" + std::to_string(_iDir));
}

void PlayerDeath::Update(float fElapsedTime) noexcept
{
	if (_pAnimator->GetCurrentAnimationEnd())
	{
		_pPlayer->SetState(PLAYER_END, _eDir);
	}
}

#include "pch.h"
#include "PlayerDamaged.h"
#include "Player.h"
#include "Animator.h"
#include "Transform.h"

void PlayerDamaged::Start() noexcept
{
	if (!_bFPV)
	{
		_eDir = GetDirect(_pTrans->GetWorldPosition(), _vTarget);
		_iDir = (int)_eDir * 2;
	}
	_pAnimator->SetAnimation("Damaged_" + std::to_string(_iDir));
}

void PlayerDamaged::Update(float fElapsedTime) noexcept
{
	if (_pAnimator->GetCurrentAnimationEnd())
	{
		//Stand·Î º¯°æ 
		_pPlayer->SetState(PLAYER_STAND, _eDir);
	}
}

#include "pch.h"
#include "PlayerSkill.h"
#include "Player.h"
#include "Transform.h"
#include "Animator.h"

void PlayerSkill::Start() noexcept
{
	if (!_bFPV)
	{
		_eDir = GetDirect(_pTrans->GetWorldPosition(), _vTarget);
		_iDir = (int)_eDir * 2;
	}

	_pAnimator->SetAnimation("Skill_" + std::to_string(_iDir));
}

void PlayerSkill::Update(float fElapsedTime) noexcept
{
	if (_pAnimator->GetCurrentAnimationEnd())
	{
		//Stand·Î º¯°æ 
		_pPlayer->SetState(PLAYER_STAND, _eDir);
	}
}

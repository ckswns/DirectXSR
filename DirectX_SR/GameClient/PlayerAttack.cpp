#include "pch.h"
#include "PlayerAttack.h"
#include "Player.h"
#include "Transform.h"
#include "Animator.h"

void PlayerAttack::Start() noexcept
{
	D3DXVECTOR3 vDir = _vTarget - _pTrans->GetWorldPosition();
	if (D3DXVec3Length(&vDir) <= 2.f)
	{
		_pAnimator->SetAnimation("Attack");
		// 소리 
		//충돌판정
	}
	else
	{
		//이동으로 바꿈 
		_pOwner->SetState(PLAYER_MOVE, _vTarget, true);
	}
}

void PlayerAttack::Update(float fElapsedTime) noexcept
{
	if (_pAnimator->GetCurrentAnimationEnd())
	{
		//Stand로 변경 
		_pOwner->SetState(PLAYER_STAND);
	}
}

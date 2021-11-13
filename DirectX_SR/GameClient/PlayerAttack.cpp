#include "pch.h"
#include "PlayerAttack.h"
#include "Player.h"
#include "Transform.h"
#include "Animator.h"

void PlayerAttack::Start() noexcept
{
	_pPlayer = static_cast<Player*>(_pTrans->GetGameObject()->GetComponent(COMPONENT_ID::BEHAVIOUR));

	D3DXVECTOR3 vDir = _vTarget - _pTrans->GetWorldPosition();
	if (D3DXVec3Length(&vDir) <= 1.5f)
	{
		if (_eDir == PLAYER_END) 
		{
			_eDir = GetDirect(_pTrans->GetWorldPosition(), _vTarget);
			_iDir = (int)_eDir * 2;
		}
		_pAnimator->SetAnimation("Attack_"+ std::to_string(_iDir));

		// 소리 
		//충돌판정
	}
	else
	{
		//이동으로 바꿈 
		_pPlayer->SetState(PLAYER_MOVE,_eDir,_vTarget, true);
		_eDir = DIR_END;
	}
}

void PlayerAttack::Update(float fElapsedTime) noexcept
{
	if (_pAnimator->GetCurrentAnimationEnd())
	{
		//Stand로 변경 
		_pPlayer->SetState(PLAYER_STAND, _eDir);
	}
}

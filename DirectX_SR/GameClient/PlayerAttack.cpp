#include "pch.h"
#include "PlayerAttack.h"
#include "Player.h"
#include "Transform.h"
#include "Animator.h"

void PlayerAttack::Start() noexcept
{
	if (!_bFPV)
	{
		D3DXVECTOR3 vDir = _vTarget - _pTrans->GetWorldPosition();
		if (D3DXVec3Length(&vDir) <= 1.5f)
		{
			if (_eDir == PLAYER_END)
			{
				_eDir = GetDirect(_pTrans->GetWorldPosition(), _vTarget);
				_iDir = (int)_eDir * 2;
			}
			_pAnimator->SetAnimation("Attack_" + std::to_string(_iDir));

			// �Ҹ� 
			//�浹����
		}
		else
		{
			//�̵����� �ٲ� 
			_pPlayer->SetState(PLAYER_MOVE, _eDir, _vTarget, true);
			_eDir = DIR_END;
		}
	}
	else 
	{
		_pAnimator->SetAnimation("Attack_0");
		// �Ҹ� 
		//�浹����
	}
}

void PlayerAttack::Update(float fElapsedTime) noexcept
{
	if (_pAnimator->GetCurrentAnimationEnd())
	{
		//Stand�� ���� 
		_pPlayer->SetState(PLAYER_STAND, _eDir);
	}
}

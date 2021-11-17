#include "pch.h"
#include "PlayerAttack.h"
#include "Player.h"
#include "Transform.h"
#include "Animator.h"
#include "Ray.h"
void PlayerAttack::Start() noexcept
{
	if (!_bFPV)
	{
		D3DXVECTOR3 vDir = _pTargetTrans->GetWorldPosition() - _pTrans->GetWorldPosition();
		vDir.y = 0;
		if (D3DXVec3Length(&vDir) <= 1)
		{
			_eDir = GetDirect(_pTrans->GetWorldPosition(), _pTargetTrans->GetWorldPosition());
			_iDir = (int)_eDir * 2;
			_pAnimator->SetAnimation("Attack_" + std::to_string(_iDir));

			// �Ҹ� 
			//�浹����
			// _pPlayer->GetAtt();

			_pTargetTrans = nullptr;
		}
		else
		{
			//�̵����� �ٲ� 
			_pPlayer->SetState(PLAYER_MOVE, _pTargetTrans, true);
			_eDir = DIR_END;
		}
	}
	else 
	{
		_pAnimator->SetAnimation("Attack_0");
		// �Ҹ� 
		// �Ÿ� üũ 
		_pPlayer->SetAttCollider(true);
		//���� ������
		//_pPlayer->GetAtt();

	}
}

void PlayerAttack::Update(float fElapsedTime) noexcept
{
	if (_pAnimator->GetCurrentAnimationEnd())
	{
		if(_bFPV)
			_pPlayer->SetAttCollider(false);
		//Stand�� ���� 
		_pPlayer->SetState(PLAYER_STAND, _eDir);
	}
}

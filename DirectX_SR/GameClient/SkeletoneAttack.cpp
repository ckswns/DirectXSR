#include "pch.h"
#include "SkeletoneAttack.h"
#include "Skeleton.h"
#include "Transform.h"
#include "Animator.h"

void SkeletoneAttack::Start() noexcept
{
	_pSk = static_cast<Skeleton*>(_pTrans->GetGameObject()->GetComponent(COMPONENT_ID::BEHAVIOUR));

	D3DXVECTOR3 vDir = _vTarget - _pTrans->GetWorldPosition();
	if (D3DXVec3Length(&vDir) <= 1.5f)
	{
		if (_eDir == SK_END)
		{
			_eDir = GetDirect(_pTrans->GetWorldPosition(), _vTarget);
			_iDir = (int)_eDir * 2;
		}
		_pAnimator->SetAnimation("Attack_" + std::to_string(_iDir));

		// 소리 
		//충돌판정
	}
	else
	{
		//이동으로 바꿈 
		_pSk->SetState(SK_MOVE, _eDir, _vTarget, true);
		_eDir = DIR_END;
	}
}

void SkeletoneAttack::Update(float fElapsedTime) noexcept
{
	if (_pAnimator->GetCurrentAnimationEnd())
	{
		//Stand로 변경 
		_pSk->SetState(SK_STAND, _eDir);
	}
}

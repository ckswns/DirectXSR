#include "pch.h"
#include "SkeletoneAttack.h"
#include "Skeleton.h"
#include "Transform.h"
#include "Animator.h"
#include "GameObject.h"
#include "Actor.h"
void SkeletoneAttack::Start() noexcept
{
	if(!_pSk)
		_pSk = static_cast<Skeleton*>(_pTrans->GetGameObject()->GetComponent(COMPONENT_ID::BEHAVIOUR));

	D3DXVECTOR3 vDir = _pTargetTrans->GetWorldPosition() - _pTrans->GetWorldPosition();
	vDir.y = 0;
	if (D3DXVec3Length(&vDir) < 1)
	{

		_eDir = GetDirect(_pTrans->GetWorldPosition(), _pTargetTrans->GetWorldPosition());
		_iDir = (int)_eDir * 2;

		_pAnimator->SetAnimation("Attack_" + std::to_string(_iDir));

		// 소리 

		if (_pTargetTrans->GetGameObject() != nullptr)
			_pTargetTrans->GetGameObject()->GetComponent<Actor>(COMPONENT_ID::BEHAVIOUR)->GetHit(2);
		else
		{
			_pTargetTrans = nullptr;
			_pSk->SetState(SK_STAND, _eDir);
		}
	}
	else
	{
		//이동으로 바꿈 
		_pSk->SetState(SK_MOVE, _pTargetTrans, true);
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

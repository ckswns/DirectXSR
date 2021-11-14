#include "pch.h"
#include "SkeletonStand.h"
#include "Skeleton.h"
#include "Animator.h"
#include "Transform.h"

void SkeletonStand::Start() noexcept
{
	_fCurTime = 0;
	_fStandTime = UnsignedRandomf(1);
	_pAnimator->SetAnimation("Stand_" + std::to_string(_iDir));
	_pSk = static_cast<Skeleton*>(_pTrans->GetGameObject()->GetComponent(COMPONENT_ID::BEHAVIOUR));
}

void SkeletonStand::Update(float fElapsedTime) noexcept
{
	_fCurTime += fElapsedTime;

	if (_fCurTime >= _fStandTime)
	{
		_pSk->SetState(SK_MOVE);
	}

	//플레이어와 거리확인
	D3DXVECTOR3 vDir = _pPlayerTrans->GetWorldPosition() - _pTrans->GetWorldPosition();
	if (D3DXVec3Length(&vDir) >= 10.f)
	{
		//많이 멀어진 경우 주변으로 순간이동 
		float fX = CE_MATH::Random(-1, 1) + _pPlayerTrans->GetWorldPosition().x;
		float fZ = CE_MATH::Random(-1, 1) + _pPlayerTrans->GetWorldPosition().z;

		_pTrans->SetWorldPosition(fX, _pPlayerTrans->GetWorldPosition().y, fZ);
	}

}

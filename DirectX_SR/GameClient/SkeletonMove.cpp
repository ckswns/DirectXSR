#include "pch.h"
#include "SkeletonMove.h"
#include "Skeleton.h"
#include "Transform.h"
#include "Animator.h"
#include "PathFinding.h"
#include "Node.h"
#include "GameObject.h"

SkeletonMove::SkeletonMove(Animator* pAnim, Transform* trans, Transform* playerTrans, PathFinding* pf, float speed) noexcept
	:FSMState(pAnim, trans), _pPlayerTrans(playerTrans), _pPathFinding(pf), _fSpeed(speed), _bAtt(false)
{	__noop;	}

void SkeletonMove::Start() noexcept
{
	if (_pTargetTrans != nullptr)
	{
		_vTarget = _pTargetTrans->GetWorldPosition();
	}
	else if (_vTarget.y == 5)
	{
		_vTarget.x = _pTrans->GetWorldPosition().x + SignedRandomf(2);
		_vTarget.y = _pTrans->GetWorldPosition().y;
		_vTarget.z = _pTrans->GetWorldPosition().z + SignedRandomf(2);
	}

	_eDir = GetDirect(_pTrans->GetWorldPosition(), _vTarget);
	_iDir = (int)_eDir * 2;

	_pSk = static_cast<Skeleton*>(_pTrans->GetGameObject()->GetComponent(COMPONENT_ID::BEHAVIOUR));
	_pAnimator->SetAnimation("Walk_"+std::to_string(_iDir));

	if (_pPathFinding->FindPath(_pTrans->GetWorldPosition(), _vTarget))
	{
		_pPath = (_pPathFinding->GetPath());
		_bFinding = true;
	}
	else
		_pSk->SetState(SK_STAND, _eDir);
}

void SkeletonMove::Update(float fElapsedTime) noexcept
{
	//플레이어와 거리확인
	D3DXVECTOR3 vDir = _pPlayerTrans->GetWorldPosition() - _pTrans->GetWorldPosition();
	if (D3DXVec3Length(&vDir) >= 10.f)
	{
		//많이 멀어진 경우 주변으로 순간이동 
		float fX = CE_MATH::Random(-1, 1) + _pPlayerTrans->GetWorldPosition().x;
		float fZ = CE_MATH::Random(-1, 1) + _pPlayerTrans->GetWorldPosition().z;

		_pTrans->SetWorldPosition(fX, _pPlayerTrans->GetWorldPosition().y, fZ);
		_vTarget.y = 5;
		_pSk->SetState(SK_STAND, _eDir);
	}

	// 길찾기 중이 아닐 때 
	if (!_bFinding)
	{
		D3DXVECTOR3 vDir;
		if(_pTargetTrans != nullptr)
			vDir = _pTargetTrans->GetWorldPosition() - _pTrans->GetWorldPosition();
		else
			vDir = _vTarget - _pTrans->GetWorldPosition();
		vDir.y = 0;

		if (D3DXVec3Length(&vDir) < 0.5f)
		{
			_vTarget.y = 5;
			//공격이였으면 공격으로 돌아가기
			if (_bAtt)
			{
				_bAtt = false;
				_pSk->SetState(SK_ATTACK, _pTargetTrans);
				_pTargetTrans = nullptr;
			}
			else
				_pSk->SetState(SK_STAND, _eDir);
		}
		else
		{
			D3DXVec3Normalize(&vDir, &vDir);
			_pTrans->Translate(vDir * _fSpeed * fElapsedTime);
		}
	}
	else if(!_pPath.empty())
	{
		std::list<Node*>::iterator iter = _pPath.begin();

		D3DXVECTOR3 vDir = (*iter)->GetPos() - _pTrans->GetWorldPosition();
		vDir.y = 0;

		if (D3DXVec3Length(&vDir) < 0.5f)
		{
			_pPath.pop_front();

			if (_pPath.empty())	//A* 종료
			{
				_bFinding = false;
				_vTarget.y = 5;
				if (_bAtt)
				{
					_bAtt = false;
					_pSk->SetState(SK_ATTACK,_pTargetTrans);
					_pTargetTrans = nullptr;
				}
				else
					_pSk->SetState(SK_STAND, _eDir);
			}
		}
		else
		{
			D3DXVec3Normalize(&vDir, &vDir);
			_pTrans->Translate(vDir* _fSpeed * fElapsedTime);
		}
	}
	else
	{
		_pSk->SetState(SK_STAND, _eDir);
	}
}

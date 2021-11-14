#include "pch.h"
#include "SkeletonMove.h"
#include "Skeleton.h"
#include "Transform.h"
#include "Animator.h"
#include "PathFinding.h"
#include "Node.h"

SkeletonMove::SkeletonMove(Animator* pAnim, Transform* trans, Transform* playerTrans, PathFinding* pf, float speed) noexcept
	:FSMState(pAnim, trans), _pPlayerTrans(playerTrans), _pPathFinding(pf), _fSpeed(speed), _bAtt(false)
{	__noop;	}

void SkeletonMove::Start() noexcept
{
	_bFinding = false;

	if (_vTarget.y == 5)
	{
		_vTarget.x = SignedRandomf(1.f);
		_vTarget.y = 0;
		_vTarget.z = SignedRandomf(1.f);
	}

	_eDir = GetDirect(_pTrans->GetWorldPosition(), _vTarget);
	_iDir = (int)_eDir * 2;

	_pSk = static_cast<Skeleton*>(_pTrans->GetGameObject()->GetComponent(COMPONENT_ID::BEHAVIOUR));
	_pAnimator->SetAnimation("Walk_"+std::to_string(_iDir));
//	_pPathFinding->FindPath(_pTrans->GetWorldPosition(), _vTarget);
//	_pPath = (_pPathFinding->GetPath());
}

void SkeletonMove::Update(float fElapsedTime) noexcept
{
	//�÷��̾�� �Ÿ�Ȯ��
	D3DXVECTOR3 vDir = _pPlayerTrans->GetWorldPosition() - _pTrans->GetWorldPosition();
	if (D3DXVec3Length(&vDir) >= 10.f)
	{
		//���� �־��� ��� �ֺ����� �����̵� 
		float fX = CE_MATH::Random(-1, 1) + _pPlayerTrans->GetWorldPosition().x;
		float fZ = CE_MATH::Random(-1, 1) + _pPlayerTrans->GetWorldPosition().z;

		_pTrans->SetWorldPosition(fX, _pPlayerTrans->GetWorldPosition().y, fZ);
		_pSk->SetState(SK_STAND, _eDir);
	}

	if (!_bAtt)
	{
		//�ֺ��� ���� �ֳ� Ž��
		//���� ��� ���� ��� 
	}

	// ��ã�� ���� �ƴ� �� 
	if (!_bFinding)
	{
		D3DXVECTOR3 vDir = _vTarget - _pTrans->GetWorldPosition();
		vDir.y = 0;
		if (D3DXVec3Length(&vDir) < 0.5f)
		{
			//�����̿����� �������� ���ư���
			if (_bAtt)
			{
				_bAtt = false;
				_pSk->SetState(SK_ATTACK, _eDir, _vTarget);
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
	else
	{
		std::list<Node*>::iterator iter = _pPath.begin();

		D3DXVECTOR3 vDir = (*iter)->GetPos() - _pTrans->GetWorldPosition();
		vDir.y = 0;

		if (D3DXVec3Length(&vDir) < 0.5f)
		{
			_pPath.pop_front();
			
			if (_pPath.empty())	//A* ����
				_bFinding = false;
		}
		else
		{
			D3DXVec3Normalize(&vDir, &vDir);
			_pTrans->Translate(vDir* _fSpeed * fElapsedTime);
		}
	}
}

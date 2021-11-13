#include "pch.h"
#include "PlayerMove.h"
#include "Player.h"
#include "Transform.h"
#include "Animator.h"
#include "PathFinding.h"
#include "Node.h"

PlayerMove::PlayerMove(Animator* pAnim, Transform* trans, PathFinding* pf, float speed) noexcept
	:FSMState(pAnim, trans), _pPathFinding(pf), _fSpeed(speed), _fRunSpeed(_fSpeed + 2)
{
	__noop;
}

void PlayerMove::Start() noexcept
{
	_bFinding = false;

	_eDir = GetDirect(_pTrans->GetWorldPosition(), _vTarget);
	_iDir = (int)_eDir * 2;
	_strRun = "Run_" + std::to_string(_iDir);
	_strWalk = "Walk_" + std::to_string(_iDir);

	_pPlayer = static_cast<Player*>(_pTrans->GetGameObject()->GetComponent(COMPONENT_ID::BEHAVIOUR));
	_pAnimator->SetAnimation(_strWalk);
//	_pPathFinding->FindPath(_pTrans->GetWorldPosition(), _vTarget);
//	_pPath = (_pPathFinding->GetPath());
}

void PlayerMove::Update(float fElapsedTime) noexcept
{
	if (INPUT->GetKeyDown('Z') || INPUT->GetKeyStay('Z'))
	{
		_bRun = true;
	}
	else
	{
		if (_bRun)
			_bRun = false;
	}

	// 추후 장애물이 있을경우만 A* 사용으로 변경해야함 
	if (!_bFinding)
	{
		D3DXVECTOR3 vDir = _vTarget - _pTrans->GetWorldPosition();
		vDir.y = 0;
		if (D3DXVec3Length(&vDir) < 0.5f)
		{
			//공격이였으면 공격으로 돌아가기
			if (_bAtt)
			{
				_bAtt = false;
				_pPlayer->SetState(PLAYER_ATTACK, _eDir, _vTarget);
			}
			else
				_pPlayer->SetState(PLAYER_STAND, _eDir);
		}
		else 
		{
			Move(*D3DXVec3Normalize(&vDir, &vDir), fElapsedTime);
		}
	}
	else if (!_pPath.empty())
	{
		std::list<Node*>::iterator iter = _pPath.begin();

		D3DXVECTOR3 vDir = (*iter)->GetPos() - _pTrans->GetWorldPosition();
		vDir.y = 0;

		if (D3DXVec3Length(&vDir) < 0.5f)
		{
			_pPath.pop_front();
			if (_pPath.empty()) 
			{
				_pPath.clear();
				_bFinding = false;
			}
		}
		else
		{
			Move(*D3DXVec3Normalize(&vDir, &vDir),fElapsedTime);
		}
	}

}

void PlayerMove::Move(D3DXVECTOR3 vDir, float fElapsedTime)
{
	if (_bRun && _pPlayer->IsRunning(fElapsedTime))
	{
		if (_pAnimator->GetCurrentAnimationName() != _strRun)
			_pAnimator->SetAnimation(_strRun);

		vDir *= (_fRunSpeed * fElapsedTime);
	}
	else
	{
		if (_pAnimator->GetCurrentAnimationName() != _strWalk)
			_pAnimator->SetAnimation(_strWalk);

		vDir *= (_fSpeed * fElapsedTime);
	}
	_pTrans->Translate(vDir);
}

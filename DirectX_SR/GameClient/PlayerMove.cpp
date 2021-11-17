#include "pch.h"
#include "PlayerMove.h"
#include "Player.h"
#include "Transform.h"
#include "Animator.h"
#include "PathFinding.h"
#include "Node.h"
#include "Ray.h"

PlayerMove::PlayerMove(Player* player, Animator* pAnim, Transform* trans, PathFinding* pf, float speed) noexcept
	:PlayerFSMState(player, pAnim, trans), _pPathFinding(pf), _fSpeed(speed),
	_fRunSpeed(_fSpeed + 2), _bAtt(false), _bFinding(false), _bRun(false)
{
	__noop;
}

void PlayerMove::Start() noexcept
{
	if (!_bFPV)
	{
		if (_pTargetTrans != nullptr)
		{
			_vTarget = _pTargetTrans->GetWorldPosition();
		}

		_eDir = GetDirect(_pTrans->GetWorldPosition(), _vTarget);
		_iDir = (int)_eDir * 2;
	}
	_strRun = "Run_" + std::to_string(_iDir);
	_strWalk = "Walk_" + std::to_string(_iDir);

	_pAnimator->SetAnimation(_strWalk);

	if (!_bFPV) 
	{
		if (_pPathFinding->FindPath(_pTrans->GetWorldPosition(), _vTarget))
		{
			_pPath = (_pPathFinding->GetPath());
			_bFinding = true;
		}
	}
}

void PlayerMove::Update(float fElapsedTime) noexcept
{
	if (INPUT->GetKeyDown('Z') || INPUT->GetKeyStay('Z'))
	{
		if(_pPlayer->GetStaminaPer() > 0.1f)
			_bRun = true;
	}
	else
	{
		if (_bRun)
			_bRun = false;
	}

	if (_bFPV)
		Move(_vTarget, fElapsedTime);
	else
		TPVUpdate(fElapsedTime);
}

void PlayerMove::TPVUpdate(float fElapsedTime)
{
	if (!_bFinding)
	{
		D3DXVECTOR3 vDir = _vTarget - _pTrans->GetWorldPosition();
		vDir.y = 0;
		 if (D3DXVec3Length(&vDir) < 0.1f)
		{
			//공격이였으면 공격으로 돌아가기
			if (_bAtt)
			{
				_bAtt = false;
				_pPlayer->SetState(PLAYER_ATTACK, _pTargetTrans);
				_pTargetTrans = nullptr;
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

		if (D3DXVec3Length(&vDir) < 0.1f)
		{
			_pPath.pop_front();
			if (_pPath.empty())
			{
				_pPath.clear();
				_bFinding = false;

				if (_bAtt)
				{
					_bAtt = false;
					_pPlayer->SetState(PLAYER_ATTACK, _pTargetTrans);
					_pTargetTrans = nullptr;
				}
				else
					_pPlayer->SetState(PLAYER_STAND, _eDir);
			}
		}
		else
		{
			Move(*D3DXVec3Normalize(&vDir, &vDir), fElapsedTime);
		}
	}
	else
	{
		_pPlayer->SetState(PLAYER_STAND, _eDir);
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
		_bRun = false;
		if (_pAnimator->GetCurrentAnimationName() != _strWalk)
			_pAnimator->SetAnimation(_strWalk);

		vDir *= (_fSpeed * fElapsedTime);
	}
	_pTrans->Translate(vDir);
}

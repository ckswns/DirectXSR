#include "pch.h"
#include "PlayerMove.h"
#include "Player.h"
#include "Transform.h"
#include "Animator.h"
#include "PathFinding.h"
#include "Node.h"

PlayerMove::PlayerMove(Player* owner, Animator* pAnim, Transform* trans, PathFinding* pf, float speed) noexcept
	:FSMState(owner, pAnim, trans), _pPathFinding(pf), _fSpeed(speed), _fRunSpeed(_fSpeed + 2)
{
	__noop;
}

void PlayerMove::Start() noexcept
{
	_pAnimator->SetAnimation("Walk");
	_pPathFinding->FindPath(_pTrans->GetWorldPosition(), _vTarget);
	_pPath = (_pPathFinding->GetPath());
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

	if (!_pPath.empty())
	{
		std::list<Node*>::iterator iter = _pPath.begin();

		D3DXVECTOR3 vDir = (*iter)->GetPos() - _pTrans->GetWorldPosition();
		vDir.y = 0;

		if (D3DXVec3Length(&vDir) < 1.f)
		{
			_pPath.pop_front();
		}
		else
		{
			D3DXVec3Normalize(&vDir, &vDir);
			
			if (_bRun&& _pOwner->IsRunning(fElapsedTime))
			{
				vDir *= (_fRunSpeed * fElapsedTime);
			}
			else
				vDir *= (_fSpeed * fElapsedTime);

			_pTrans->Translate(vDir);
		}
	}
	else
	{
		_pPath.clear();

		//공격이였으면 공격으로 돌아가기
		if (_bAtt) 
		{
			_bAtt = false;
			_pOwner->SetState(PLAYER_ATTACK);
		}
		else
			_pOwner->SetState(PLAYER_STAND);

	}
}

#pragma once

namespace ce
{
	class Transform;
	class Animator;
}
class Player;
class FSMState abstract
{
public:		explicit			FSMState() noexcept = delete;
public:		explicit			FSMState(Player* owner,Animator* pAnim, Transform* trans = nullptr) noexcept
													:_pOwner(owner), _pAnimator(pAnim), _pTrans(trans) { __noop; }
public:		virtual				~FSMState() noexcept { __noop; }

public:		virtual void		Start() noexcept =0;
public:		virtual void		Update(float fElapsedTime) noexcept =0;

public:		void				SetTarget(D3DXVECTOR3 target) { _vTarget = target; }
public:		void				SetDir(DIR eDir) { _eDir = eDir; _iDir = (int)_eDir * 2; }

protected:	DIR GetDirect(D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd);

protected:	Player*				_pOwner;
protected:	Animator*			_pAnimator;
protected:	Transform*			_pTrans;
protected:	D3DXVECTOR3			_vTarget;

protected:	int					_iDir;
protected:	DIR					_eDir;
};

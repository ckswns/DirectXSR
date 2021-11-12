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
public:		virtual			~FSMState() noexcept { __noop; }

public:		virtual void		Start() noexcept =0;
public:		virtual void		Update(float fElapsedTime) noexcept =0;

public:		void				SetTarget(D3DXVECTOR3 target) { _vTarget = target; }

protected:		Player* _pOwner;
protected: Animator*		_pAnimator;
protected: Transform*		_pTrans;
protected: D3DXVECTOR3	_vTarget;
};

#pragma once

namespace ce
{
	class Transform;
	class Animator;
	class SphereCollider;
}

class FSMState abstract
{
public:		explicit			FSMState() noexcept = delete;
public:		explicit			FSMState(Animator* pAnim, Transform* trans = nullptr) noexcept
													:_pAnimator(pAnim), _pTrans(trans),_vTarget(D3DXVECTOR3(0,5,0)), _pTargetTrans(nullptr), _eDir(DIR_END){ __noop; }
public:		virtual				~FSMState() noexcept { __noop; }

public:		virtual void		Start() noexcept =0;
public:		virtual void		Update(float fElapsedTime) noexcept =0;

public:		void				SetTarget(D3DXVECTOR3 target) { _vTarget = target; }
public:		void				SetTargetTrans(Transform* hit) { _pTargetTrans = hit; }
public:		void				SetDir(DIR eDir) { _eDir = eDir; _iDir = (int)_eDir * 2; }

protected:	DIR					GetDirect(D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd);

protected:	Animator*			_pAnimator;
protected:	Transform*			_pTrans;
protected:	D3DXVECTOR3			_vTarget;
protected:	Transform*			_pTargetTrans;

protected:	int					_iDir;
protected:	DIR					_eDir;
};

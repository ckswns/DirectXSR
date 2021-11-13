#pragma once
#include "FSMState.h"

class Skeleton;
class SkeletonStand : public FSMState
{
public:		explicit			SkeletonStand() noexcept = delete;
public:		explicit			SkeletonStand(Animator* pAnim,Transform* pTrans, Transform* playerTrans) noexcept 
											:FSMState(pAnim, pTrans), _pPlayerTrans(playerTrans) { __noop; }
public:		virtual				~SkeletonStand() noexcept { __noop; }

public:		virtual void		Start() noexcept;
public:		virtual void		Update(float fElapsedTime) noexcept;

private:	Skeleton*			_pSk;
private:	float				_fStandTime;
private:	float				_fCurTime;

private:	Transform*			_pPlayerTrans;
};


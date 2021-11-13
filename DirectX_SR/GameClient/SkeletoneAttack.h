#pragma once
#include "FSMState.h"

class Skeleton;
class SkeletoneAttack : public FSMState
{
public:		explicit			SkeletoneAttack() noexcept = delete;
public:		explicit			SkeletoneAttack(Animator* pAnim, Transform* trans = nullptr) noexcept
                                        :FSMState(pAnim, trans) { __noop; }
public:		virtual				~SkeletoneAttack() noexcept { __noop; }

public:		virtual void		Start() noexcept;
public:		virtual void		Update(float fElapsedTime) noexcept;

private:    Skeleton*           _pSk;
};


#pragma once
#include "FSMState.h"

class Skeleton;
class SkeletonCreate : public FSMState
{
public:		explicit			SkeletonCreate() noexcept = delete;
public:		explicit			SkeletonCreate(Animator* pAnim) noexcept :FSMState(pAnim){ __noop; }
public:		virtual				~SkeletonCreate() noexcept { __noop; }

public:		virtual void		Start() noexcept;
public:		virtual void		Update(float fElapsedTime) noexcept;

private:	Skeleton*			_pSk;
};


#pragma once
#include "FSMState.h"

namespace ce
{
	class GameObject;
}
class SkeletonDead : public FSMState
{
public:		explicit			SkeletonDead() noexcept = delete;
public:		explicit			SkeletonDead(Animator* pAnim,GameObject* pObj) noexcept :FSMState(pAnim), _pGameObj(pObj){ __noop; }
public:		virtual				~SkeletonDead() noexcept { __noop; }

public:		virtual void		Start() noexcept;
public:		virtual void		Update(float fElapsedTime) noexcept;

private:	GameObject*			_pGameObj;
};


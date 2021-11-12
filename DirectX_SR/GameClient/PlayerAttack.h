#pragma once
#include "FSMState.h"
class PlayerAttack :  public FSMState
{
public:		explicit			PlayerAttack() noexcept = delete;
public:		explicit			PlayerAttack(Player* owner,Animator* pAnim, Transform* trans = nullptr) noexcept
														:FSMState(owner,pAnim,trans) { __noop; }
public:		virtual			~PlayerAttack() noexcept { __noop; }

public:		virtual void		Start() noexcept;
public:		virtual void		Update(float fElapsedTime) noexcept;
};


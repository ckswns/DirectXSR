#pragma once
#include "FSMState.h"
class PlayerStand :	public FSMState
{
public:		explicit			PlayerStand() noexcept = delete;
public:		explicit			PlayerStand(Animator* pAnim) noexcept :FSMState(pAnim) { __noop; }
public:		virtual				~PlayerStand() noexcept { __noop; }

public:		virtual void		Start() noexcept;
public:		virtual void		Update(float fElapsedTime) noexcept { __noop; }
};


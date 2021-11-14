#pragma once
#include "PlayerFSMState.h"

class PlayerStand :	public PlayerFSMState
{
public:		explicit			PlayerStand() noexcept = delete;
public:		explicit			PlayerStand(Animator* pAnim) noexcept :PlayerFSMState(nullptr,pAnim) { __noop; }
public:		virtual				~PlayerStand() noexcept { __noop; }

public:		virtual void		Start() noexcept;
public:		virtual void		Update(float fElapsedTime) noexcept { __noop; }
};


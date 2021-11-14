#pragma once
#include "PlayerFSMState.h"

class PlayerAttack :  public PlayerFSMState
{
public:		explicit			PlayerAttack() noexcept = delete;
public:		explicit			PlayerAttack(Player* player,Animator* pAnim, Transform* trans) noexcept
														:PlayerFSMState(player,pAnim,trans) { __noop; }
public:		virtual				~PlayerAttack() noexcept { __noop; }

public:		virtual void		Start() noexcept;
public:		virtual void		Update(float fElapsedTime) noexcept;
};


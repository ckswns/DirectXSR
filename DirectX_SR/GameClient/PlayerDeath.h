#pragma once
#include "PlayerFSMState.h"
class PlayerDeath : public PlayerFSMState
{
public:		explicit			PlayerDeath() noexcept = delete;
public:		explicit			PlayerDeath(Player* player, Animator* pAnim,Transform* pTrans) noexcept
									:PlayerFSMState(player,pAnim, pTrans) { __noop; }
public:		virtual				~PlayerDeath() noexcept { __noop; }

public:		virtual void		Start() noexcept;
public:		virtual void		Update(float fElapsedTime) noexcept;
};


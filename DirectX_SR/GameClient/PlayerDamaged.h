#pragma once
#include "PlayerFSMState.h"
class PlayerDamaged : public PlayerFSMState
{
public:		explicit			PlayerDamaged() noexcept = delete;
public:		explicit			PlayerDamaged(Player* player, Animator* pAnim,Transform* pTrans) noexcept
									:PlayerFSMState(player,pAnim, pTrans) { __noop; }
public:		virtual				~PlayerDamaged() noexcept { __noop; }

public:		virtual void		Start() noexcept;
public:		virtual void		Update(float fElapsedTime) noexcept;
};


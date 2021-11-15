#pragma once
#include "PlayerFSMState.h"
class PlayerSkill : public PlayerFSMState
{
public:		explicit			PlayerSkill() noexcept = delete;
public:		explicit			PlayerSkill(Player* player, Animator* pAnim, Transform* trans) noexcept
											:PlayerFSMState(player, pAnim, trans) {	__noop; }
public:		virtual				~PlayerSkill() noexcept { __noop; }

public:		virtual void		Start() noexcept;
public:		virtual void		Update(float fElapsedTime) noexcept;

};


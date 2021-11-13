#pragma once
#include "FSMState.h"

class Player;
class PlayerAttack :  public FSMState
{
public:		explicit			PlayerAttack() noexcept = delete;
public:		explicit			PlayerAttack(Animator* pAnim, Transform* trans = nullptr) noexcept
														:FSMState(pAnim,trans) { __noop; }
public:		virtual				~PlayerAttack() noexcept { __noop; }

public:		virtual void		Start() noexcept;
public:		virtual void		Update(float fElapsedTime) noexcept;

private:	Player* _pPlayer;
};


#pragma once
#include "FSMState.h"

class Player;
class PlayerFSMState : public FSMState
{
public:		explicit			PlayerFSMState() noexcept = delete;
public:		explicit			PlayerFSMState(Player* player, Animator* pAnim, Transform* trans = nullptr) noexcept
												:FSMState(pAnim,trans),_pPlayer(player){ __noop; }
public:		virtual				~PlayerFSMState() noexcept { __noop; }

public:		void				SetFPV(bool fpv) { _bFPV = fpv; }

protected:	Player*				_pPlayer;
protected:  bool				_bFPV;
};


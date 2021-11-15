#pragma once
#include "Behaviour.h"

namespace ce
{
	class Transform;
	class Animator;
	class BoxCollider;
	class SpriteRenderer;
}

class Skill;
class PathFinding;
class InputHandler;
class PlayerFSMState;
class Player : public Behaviour
{
private:	using		VEC_FSM = std::vector<PlayerFSMState*>;

public:		explicit				Player() noexcept = delete;
public:		explicit				Player(PathFinding* pf) noexcept;
public:		virtual					~Player(void) noexcept { __noop; }

public:		virtual void			Start(void) noexcept;
public:		virtual void			Update(float fElapsedTime) noexcept;
public:		virtual void			OnDestroy(void) noexcept;

private:	void					InitAnimation(SpriteRenderer* mr);
private:	void					InitState();

public:		void					SetFPV();
public:		void					SetState(PLAYER_STATE newState,DIR eDir,D3DXVECTOR3 vTarget = D3DXVECTOR3(0,-5,0),bool bAtt = false);
public:		void					UsingSkill(SKILL_ID id,D3DXVECTOR3 vPos);

public:		bool					IsRunning(float fElapsedTime);

public:		float					GetHPPer();
public:		float					GetMPPer();
public:		float					GetStaminaPer();

public:		InputHandler*			GetInpuHandler() { return _pInputHandler; }

private:	Transform*				_pTrans;
private:	Animator*				_pAnimator;
private:	BoxCollider*			_pCollider;

private:	InputHandler*			_pInputHandler;

private:	VEC_FSM					_pFSM;
private:	PLAYER_STATE			_eCurState;

private:	PathFinding*			_pPathFinding;

private:	STAT*					_tStat;
private:	std::vector<Skill*>		_pSkills;

private:	bool					_bFPV;
private:	float					_fRecovery;
private:	float					_fSpeed;
private:	float					_fRunSpeed;

};


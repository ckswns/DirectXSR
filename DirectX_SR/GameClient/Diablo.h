#pragma once
#include "Actor.h"

class Player;
class PathFinding;
class NaviMesh;

namespace ce
{
	class SpriteRenderer;
	class AudioSource;
}

class Diablo : public Actor
{
private:	enum class			AttackState
			{
				Default,
				Skill1,
				Skill2,
				Skill3
			};

public:		explicit			Diablo(PathFinding* pf, Player* player) noexcept;
public:		virtual				~Diablo(void) noexcept { __noop; }

public:		void				Awake(void) noexcept override;
public:		void				Start(void) noexcept override;
public:		void				FixedUpdate(float fElapsedTime) noexcept override;
public:		void				Update(float fElapsedTime) noexcept override;
public:		void				LateUpdate(float fElapsedTime) noexcept override;
public:		void				OnDestroy(void) noexcept override;

public:		void				OnCollisionEnter(Collider* mine, Collider* other) noexcept override;
public:		void				OnCollisionStay(Collider* mine, Collider* other) noexcept override;
public:		void				OnCollisionExit(Collider* mine, Collider* other) noexcept override;

public:		void				GetHit(int damage) noexcept override;

public:		void				OnAnimationEvent(std::string str) noexcept override;
public:		void				Intro(void) noexcept;
public:		void				IntroDone(void) noexcept { _bIntroDone = true; }

public:		void				DoSkill3(void) noexcept;
public:		bool				GetDead(void) const noexcept { return _bDeadAniDone; }

private:	D3DXVECTOR3			CaculateDir(Actor::Direction dir) const noexcept;

private:	SpriteRenderer*		_spriteRenderer;
private:	Player*				_player;
private:	PathFinding*		_pathFinder;

private:	AudioSource*		_fireAudio;
private:	AudioSource*		_breathAudio;
private:	AudioSource*		_castAudio;
private:	AudioSource*		_initAudio;
private:	AudioSource*		_laughAudio;
private:	AudioSource*		_attackAudio;
private:	AudioSource*		_getHitAudio;
private:	AudioSource*		_deadAudio;
private:	AudioSource*		_hitEffectAudio;

private:	AttackState			_eAttackState = AttackState::Default;
private:	Direction			_prevDirection = Actor::Direction::DOWN;

private:	bool				_bIntroDone = false;
private:	bool				_bIntro = false;
private:	bool				_dirtyState = false;
private:	bool				_bColorChanged = false;
private:	bool				_bDeadAniDone = false;

private:	float				_fColorChageTime = 0;
private:	float				_fDeltaTime = 0;

private:	float				_currentSkill1CoolTime = 2;
private:	float				_currentSkill2CoolTime = 1;
private:	float				_currentSkill3CoolTime = 0;

private:	const float			_skill1CoolTime = 15;
private:	const float			_skill2CoolTime = 10;
private:	const float			_skill3CoolTime = 20;
};


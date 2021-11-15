#pragma once
#include "Behaviour.h"

class Actor : public Behaviour
{
public:		enum class Direction
			{
				DOWN,
				LEFT_DOWN,
				LEFT,
				LEFT_UP,
				UP,
				RIGHT_UP,
				RIGHT,
				RIGHT_DOWN
			};

public:		enum class State
			{
				IDLE,
				FOLLOW,
				ATTAK,
				HIT,
				DIE
			};

public:		explicit		Actor(void) noexcept;
public:		virtual			~Actor(void) noexcept { __noop; }


public:		virtual void	GetHit(float damage) noexcept PURE;

protected:	float			_maxHP;
protected:	float			_aggroDistance;
protected:	float			_moveSpeed;
protected:	float			_damageMin;
protected:	float			_damageMax;

protected:	Direction		_dir;
protected:	Collider*		_hitBox;
protected:	Collider*		_attackBox;
};


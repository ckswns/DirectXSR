#pragma once
#include "Behaviour.h"

namespace ce
{
	class Animator;
}

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

public:		struct Data
			{
				float		maxHP;
				float		aggroDistance;
				float		moveSpeed;
				float		damageMin;
				float		damageMax;
			};

public:		explicit		Actor(void) noexcept;
public:		virtual			~Actor(void) noexcept { __noop; }


public:		virtual void	GetHit(float damage) noexcept PURE;

protected:	Data			_data;
protected:	Direction		_dir;
protected:	Collider*		_hitBox;
protected:	Collider*		_attackBox;

protected:	Animator*		_animator;
};


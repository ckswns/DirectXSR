#pragma once
#include "Behaviour.h"

namespace ce
{
	class Animator;
	class SpriteRenderer;
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
				MOVE,
				ATTAK,
				HIT,
				DIE,
				END
			};

public:		struct Data
			{
				char		name[128];
				int			maxHP;
				float		aggroDistance;
				float		moveSpeed;
				float		damageMin;
				float		damageMax;
			};

public:		explicit		Actor(void) noexcept;
public:		virtual			~Actor(void) noexcept { __noop; }


public:		virtual void	GetHit(int damage) noexcept PURE;
protected:	Direction		GetDirect(D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd);

public:		const Data&		GetData(void) noexcept { return _data; }
public:		int				GetCurrentHp(void) noexcept { return _currentHP; }

protected:	int				_currentHP;
protected:	Data			_data;
protected:	Direction		_dir;
protected:	State			_state;

protected:	Collider*		_hitBox;
protected:	Collider*		_attackBox;

protected:	Animator*		_animator;

protected:	SpriteRenderer* _spriteRenderer;
};


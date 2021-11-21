#pragma once
#include "Behaviour.h"

namespace ce
{
	class Animator;
}

class Player;

class FireWall : public Behaviour
{
public:		explicit		FireWall(D3DXVECTOR3 pos, D3DXVECTOR3 vDir) noexcept;
public:		virtual			~FireWall(void) noexcept { __noop; }

public:		void			Awake(void) noexcept override;
public:		void			Start(void) noexcept override;
public:		void			Update(float) noexcept override;
public:		void			OnDestroy(void) noexcept override;

public:		void			OnCollisionEnter(Collider* mine, Collider* other) noexcept override;
public:		void			OnCollisionStay(Collider* mine, Collider* other) noexcept override;
public:		void			OnCollisionExit(Collider* mine, Collider* other) noexcept override;

private:	D3DXVECTOR3		_startPos;
private:	D3DXVECTOR3		_vDir;

private:	float			_speed = 3;
private:	float			_deltaTime = 0;
private:	float			_lastElapsedTime = 0;

private:	Animator*		_animator;
private:	Player*			_player;
};


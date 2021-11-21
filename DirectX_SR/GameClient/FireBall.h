#pragma once
#include "Behaviour.h"
#include "Actor.h"

namespace ce
{
	class Animator;
}

class Player;

class FireBall : public Behaviour
{
public:		explicit		FireBall(void) = delete;
public:		explicit		FireBall(D3DXVECTOR3 pos, D3DXVECTOR3 vDir, int dir);

public:		void			Awake(void) noexcept override;
public:		void			Start(void) noexcept override;
public:		void			Update(float) noexcept override;
public:		void			OnDestroy(void) noexcept override;

public:		void			OnCollisionEnter(Collider* mine, Collider* other) noexcept override;
public:		void			OnCollisionStay(Collider* mine, Collider* other) noexcept override;
public:		void			OnCollisionExit(Collider* mine, Collider* other) noexcept override;

private:	D3DXVECTOR3		_startPos;
private:	D3DXVECTOR3		_vDir;
private:	int				_dir;

private:	float			_speed = 3;
private:	float			_deltaTime = 0;
private:	float			_lastElapsedTime = 0;

private:	Animator* _animator;
private:	Player* _player;
};


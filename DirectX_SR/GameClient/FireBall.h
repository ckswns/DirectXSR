#pragma once
#include "Behaviour.h"
#include "Actor.h"

namespace ce
{
	class SpriteRenderer;
	class Animator;
}

class FireBall : public Behaviour
{
public: explicit FireBall() = delete;
public: explicit FireBall(Actor::Direction tDir, D3DXVECTOR3 vdir , D3DXVECTOR3 vpos) noexcept;
public: virtual ~FireBall() noexcept { __noop; };

public:	void Start(void) noexcept override;
public: void Update(float fElapsedTime) noexcept override;
public: void OnCollisionEnter(Collider* mine, Collider* other) noexcept override;

private: Collider* _hitBox;
private: float				_fSpeed;
private: Actor::Direction	_tdir;

private: D3DXVECTOR3		_vTargetpos;
private: D3DXVECTOR3		_vpos;
private: D3DXVECTOR3		_vdir;

private: SpriteRenderer*	_spriteRenderer;
private: Animator*			_animator;
private: float				_fDeltaTime = 0;
private: float				_fangle;

};


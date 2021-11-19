#pragma once
#include "Behaviour.h"

namespace ce
{
	class Animator;
	class AudioSource;
	namespace UI
	{
		class SpriteRenderer;
	}
}
class Missile : public Behaviour
{
public:		explicit		Missile(float minDamage, float maxDamage,D3DXVECTOR3 vDir) noexcept
									:_fMinDamage(minDamage), _fMaxDamage(maxDamage), _vDir(vDir){__noop;}
public:		virtual			~Missile(void) noexcept { __noop; }

public:		virtual void			Start(void) noexcept override;
public:		virtual void			Update(float fElapsedTime) noexcept override;

public:		virtual void			OnCollisionEnter(Collider* mine, Collider* other) noexcept override;

private:	bool			_bMoving;
private:	float			_fDelta;
private:	float			_fMinDamage;
private:	float			_fMaxDamage;
private:	D3DXVECTOR3		_vDir;
private:	Animator*		_pAnimator;
private:	AudioSource*	_audio;
private:	SpriteRenderer* _spriteRenderer;
};


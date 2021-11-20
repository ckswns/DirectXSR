#pragma once
#include "Behaviour.h"

namespace ce
{
	class Animator;
	class AudioSource;
	class SpriteRenderer;
}
class LightningCollider;
class Lightning : public Behaviour
{
public:		explicit		Lightning(float minDamage,float maxDamage) noexcept
										:_fMinDamage(minDamage), _fMaxDamage(maxDamage)	{ __noop; }
public:		virtual			~Lightning(void) noexcept { __noop; }

public:		virtual void			Start(void) noexcept override;
public:		virtual void			Update(float fElapsedTime) noexcept override;

public:		void					Using(Actor::Direction dir, D3DXVECTOR3 vDir);

private:	float				_fMinDamage;
private:	float				_fMaxDamage;
private:	Animator*			_pAnimator;
private:	AudioSource*		_audio;
private:	SpriteRenderer*		_spriteRenderer;
private:	LightningCollider*	_lCollider;
};


#pragma once
#include "Behaviour.h"

namespace ce
{
	class Animator;
	class AudioSource;
}
class Lightning : public Behaviour
{
public:		explicit		Lightning(float minDamage,float maxDamage) noexcept
										:_fMinDamage(minDamage), _fMaxDamage(maxDamage)	{ __noop; }
public:		virtual			~Lightning(void) noexcept { __noop; }

public:		virtual void			Start(void) noexcept override;
public:		virtual void			Update(float fElapsedTime) noexcept override;

public:		virtual void			OnEnable(void) noexcept override;
public:		virtual void			OnCollisionEnter(Collider* mine, Collider* other) noexcept override;

private:	float			_fMinDamage;
private:	float			_fMaxDamage;
private:	Animator*		_pAnimator;
private:	AudioSource* _audio;
};


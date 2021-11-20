#pragma once
#include "Behaviour.h"
class LightningCollider :public Behaviour
{
public:		explicit			LightningCollider(float minDamage, float maxDamage)noexcept 
													:_fMinDamage(minDamage), _fMaxDamage(maxDamage) { __noop; }
public:		virtual				~LightningCollider()noexcept { __noop; }

public:		virtual void		Start() noexcept;
public:		virtual void		Update(float)noexcept { __noop; }

public:		virtual void		OnCollisionEnter(Collider* mine, Collider* other) noexcept override;

private:	float				_fMinDamage;
private:	float				_fMaxDamage;
};


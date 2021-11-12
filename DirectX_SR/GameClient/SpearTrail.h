#pragma once
#include "Behaviour.h"
class SpearTrail : public Behaviour
{
public:		explicit			SpearTrail() noexcept { __noop; }
public:		explicit			SpearTrail(float AniTime) noexcept;
public:		virtual				~SpearTrail(void) noexcept { __noop; }

public:		virtual void		Start(void) noexcept;
public:		virtual void		Update(float fElapsedTime) noexcept { __noop; }

private:	float				_fAniTime;

};


#pragma once

#include "Behaviour.h"
class ParticleSys:public Behaviour
{
public:		explicit					ParticleSys() noexcept { __noop; }
public:		virtual					~ParticleSys(void) noexcept { __noop; }

public:		virtual void				Start(void) noexcept override;
public:		virtual void				Update(float fElapsedTime) noexcept override { __noop; }
};


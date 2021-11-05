#pragma once
#include "Behaviour.h"

class DirectionLight : public Behaviour
{
public:		explicit	DirectionLight(void) noexcept { __noop; }
public:		virtual		~DirectionLight(void) noexcept { __noop; }

public:		void		Start(void) noexcept override;
public:		void		Update(float fElapsedTime) noexcept override;
};


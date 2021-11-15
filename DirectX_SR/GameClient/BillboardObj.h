#pragma once
#include "Behaviour.h"

class BillboardObj : public Behaviour
{
public:		explicit		BillboardObj(void) noexcept { __noop; }
public:		virtual			~BillboardObj(void) noexcept { __noop; }


public:		void			Start(void) noexcept override;
public:		void			Update(float) noexcept override;

};


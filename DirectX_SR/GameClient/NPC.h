#pragma once
#include "Behaviour.h"
class NPC : public Behaviour
{
public:		explicit				NPC() noexcept { __noop; }
public:		virtual					~NPC(void) noexcept { __noop; }

public:		virtual void			OnClick() = 0;
};


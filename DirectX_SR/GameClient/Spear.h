#pragma once
#include "Behaviour.h"

namespace ce
{
	class Transform;
}
class Spear : public Behaviour
{
public:		explicit			Spear()noexcept { __noop; }
public:		virtual				~Spear(void) noexcept { __noop; }

public:		virtual void		Start(void) noexcept;
public:		virtual void		Update(float fElapsedTime) noexcept { __noop; }
	
public:		void				OnCollisionEnter(Collider* mine, Collider* other) noexcept override;
};


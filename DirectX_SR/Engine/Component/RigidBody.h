#pragma once
#include "Component.h"

namespace ce
{
	class RigidBody : public Component
	{
	public:		explicit		RigidBody(void) noexcept;
	public:		virtual			~RigidBody(void) noexcept { __noop; }

	public:		void			Init(void) noexcept override;
	public:		void			Update(float) noexcept override;
	public:		void			Render(void) noexcept override;
	public:		void			Release(void) noexcept override;
	};
}

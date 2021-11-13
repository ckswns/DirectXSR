#pragma once
#include "Component.h"

namespace ce
{
	class Rigidbody : public Component
	{
	public:		explicit		Rigidbody(void) noexcept;
	public:		virtual			~Rigidbody(void) noexcept { __noop; }

	public:		void			Init(void) noexcept override;
	public:		void			Update(float) noexcept override;
	public:		void			Render(void) noexcept override;
	public:		void			Release(void) noexcept override;
	};
}

#pragma once
#include "Component.h"

namespace ce
{
	class Collider : public Component
	{
	public:		explicit	Collider(void) noexcept;
	public:		virtual		~Collider(void) noexcept;

	public:		void		Init(void) noexcept override;
	public:		void		Update(float) noexcept override;
	public:		void		Render(void) noexcept override;
	public:		void		Release(void) noexcept override;
	};
}

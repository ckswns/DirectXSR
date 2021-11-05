#pragma once
#include "Component.h"

namespace ce
{
	class Terrain : public Component
	{
	public:		explicit	Terrain(void) noexcept;
	public:		virtual		~Terrain(void) noexcept { __noop; }



	};
}

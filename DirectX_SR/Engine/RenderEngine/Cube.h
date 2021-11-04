#pragma once
#include "Mesh.h"

namespace ce
{
	class Cube : public Mesh
	{
	public:		explicit	Cube(float scaleFactor = 1) noexcept;
	public:		virtual		~Cube(void) noexcept { __noop; }

	public:		bool		Open(LPDIRECT3DDEVICE9 pDevice) noexcept override;
	};
}

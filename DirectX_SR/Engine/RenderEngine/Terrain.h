#pragma once
#include "Component.h"
#include "Mesh.h"

namespace ce
{
	class Terrain : public Mesh
	{
	public:		explicit	Terrain(uint64 width, uint64 height, float scaleFactor = 1) noexcept;
	public:		virtual		~Terrain(void) noexcept { __noop; }

	public:		bool		Open(LPDIRECT3DDEVICE9 pDevice) noexcept override;

	private:	uint64		_width;
	private:	uint64		_height;
	};
}

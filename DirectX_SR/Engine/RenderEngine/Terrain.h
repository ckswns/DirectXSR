#pragma once
#include "Component.h"
#include "Mesh.h"

namespace ce
{
	class Terrain : public Mesh
	{
	public:		explicit	Terrain(uint16 width, uint16 height, float scaleFactor = 1) noexcept;
	public:		virtual		~Terrain(void) noexcept { __noop; }

	public:		bool		Open(LPDIRECT3DDEVICE9 pDevice) noexcept override;

	private:	uint16		_width;
	private:	uint16		_height;
	};
}

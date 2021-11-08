#pragma once
#include "Mesh.h"

namespace ce
{
	class Quad : public Mesh
	{
	public:		explicit	Quad(float x = 1, float y = 1) noexcept;
	public:		virtual		~Quad(void) noexcept { __noop; }

	public:		bool		Open(LPDIRECT3DDEVICE9 pDevice) noexcept override;

	private:	float		_intvX;
	private:	float		_intvY;
	};
}

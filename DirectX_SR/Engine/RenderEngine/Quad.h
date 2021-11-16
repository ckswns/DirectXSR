#pragma once
#include "Mesh.h"

namespace ce
{
	class Quad : public Mesh
	{
	public:		explicit	Quad(float x = 1, float y = 1, float uMax = 1, float vMax = 1) noexcept;
	public:		virtual		~Quad(void) noexcept { __noop; }

	public:		bool		Open(LPDIRECT3DDEVICE9 pDevice) noexcept override;

	public:		void		SetInterval(float x, float y) noexcept { _intvX = x, _intvY = y; }
	public:		void		SetMaxUV(float u, float v) noexcept { _maxU = u, _maxV = v; }

	private:	float		_intvX;
	private:	float		_intvY;

	private:	float		_maxU;
	private:	float		_maxV;
	};
}

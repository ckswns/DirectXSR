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

	public:		uint64	Get_VtxCntX() { return _width; }
	public:		uint64	Get_VtxCntZ() { return _height; }
	public:		D3DXVECTOR3* Get_VtxPos(void) { return _pVtxPos; }

	private:	uint64		_width;
	private:	uint64		_height;

	private: D3DXVECTOR3* _pVtxPos;
	};
}

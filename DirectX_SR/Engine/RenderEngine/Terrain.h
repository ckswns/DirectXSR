#pragma once
#include "Component.h"
#include "Mesh.h"

namespace ce
{
	class Terrain : public Mesh
	{
	public:		explicit				Terrain(uint64 width, uint64 height, float scaleFactor = 1) noexcept;
	public:		virtual					~Terrain(void) noexcept { if (_pVtxPos) delete[] _pVtxPos; }

	public:		bool					Open(LPDIRECT3DDEVICE9 pDevice) noexcept override;

	public:		LPDIRECT3DINDEXBUFFER9	GetIndexBuffer(void) noexcept { return _pIB; }
	public:		LPDIRECT3DVERTEXBUFFER9	GetVtxBuffer(void) noexcept { return _pVB; }

	public:		uint64					GetFVF(void) const noexcept { return _nFVF; }
	public:		uint64					GetVtxSize(void) const noexcept { return _nVtxSize; }
	public:		uint64					GetVtxCnt(void) const noexcept { return _nVtxCnt; }
	public:		uint64					GetTriCnt(void) const noexcept { return _nTriCnt; }

	public:		uint64					Get_VtxCntX() { return _width; }
	public:		uint64					Get_VtxCntZ() { return _height; }
	public:		D3DXVECTOR3*			Get_VtxPos(void) { return _pVtxPos; }

	private:	uint64					_width;
	private:	uint64					_height;

	private:	D3DXVECTOR3*			_pVtxPos;
	};
}

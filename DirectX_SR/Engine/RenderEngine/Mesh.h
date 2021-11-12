#pragma once
#include "TypeDefine.h"

namespace ce
{
	class Mesh abstract
	{
	protected:	explicit				Mesh(float scaleFactor = 1) noexcept;
	public:								~Mesh(void) noexcept { __noop; }

	public:		virtual bool			Open(LPDIRECT3DDEVICE9 pDevice) noexcept;
	public:		virtual void			Close(void) noexcept;
	public:		virtual void			Render(LPDIRECT3DDEVICE9 pDevice) noexcept;

	protected:	uint64					_nVtxCnt;
	protected:	uint64					_nVtxSize;
	protected:	uint64					_nTriCnt;
	protected:	uint64					_nFVF;
	protected:	uint64					_nIdxSize;

	protected:	bool					_bOpen = false;
	protected:	float					_scaleFactor = 1;

	protected:	D3DFORMAT				_idxFmt;

	protected:	LPDIRECT3DVERTEXBUFFER9	_pVB;
	protected:	LPDIRECT3DINDEXBUFFER9	_pIB;
	};
}

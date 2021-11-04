#pragma once

#include "Vector3.h"
#include "Matrix4x4.h"
#include "Texture.h"
#include "TypeDefine.h"

namespace ce
{
	class Sprite
	{
	public:		explicit				Sprite(void) noexcept { __noop; }
	public:		virtual					~Sprite(void) noexcept { __noop; }

	//public:		bool					Init(LPDIRECT3DDEVICE9 pd3dDevice, LPCWSTR texture, Vector3 pivot = { 0, 0, 0 }) noexcept;
	//public:		bool					Init(LPDIRECT3DDEVICE9 pd3dDevice, LPCWSTR texture, FLOAT pivotX, FLOAT pivotY) noexcept; //center: 0 ~ 1

	//public:		void					Render(const Matrix4x4& world, D3DCOLOR Color = 0xFFFFFFFF) noexcept;
	//public:		void					Render(const Matrix4x4& world, uint32 nSrcPosX, uint32 nSrcPosY, uint32 nWidth, uint32 nHeight, D3DCOLOR Color = 0xFFFFFFFF) noexcept;
	//public:		void					Render(const Matrix4x4& world, const RECT& SrcRect, D3DCOLOR Color = 0xFFFFFFFF) noexcept;
	//public:		void					Render(const Matrix4x4& world, const RECT& SrcRect, uint32 scrollX, D3DCOLOR Color = 0xFFFFFFFF) noexcept;

	//public:		void					Release() noexcept;

	//public:		uint32					Width() const noexcept { return _imgInfo.Width; }
	//public:		uint32					Height() const noexcept { return _imgInfo.Height; }

	//public:		const Vector3&			GetCenter() const noexcept { return _vPivot; }
	//public:		void					SetCenter(Vector3 pivot) noexcept { _vPivot = pivot; }

	//public:		std::string				GetFilePath(void) const noexcept { return _filePathA; }

	//public:		void					SetOrgPivot(uint32 x, uint32 y) noexcept { _vOrgPivot = POINT(x, y); }
	//public:		const D3DXVECTOR2		GetOrgPivot(void) const noexcept { return _vOrgPivot; }

	//public:		LPDIRECT3DTEXTURE9		GetTexture(void) noexcept { return _pTexture; }
	//public:		const RECT&				GetSrcRect(void) const noexcept { return _srcRect; }

	//private:	std::wstring			_filePath;
	//private:	std::string				_filePathA;
	//private:	LPD3DXSPRITE			_pSprite = nullptr;
	//private:	LPDIRECT3DTEXTURE9		_pTexture = nullptr;
	//private:	D3DXIMAGE_INFO			_imgInfo;

	//private:	POINT					_vOrgPivot = { 0, 0 };
	//private:	Vector3					_vPivot = { 0, 0, 0 };
	//private:	RECT					_srcRect;
	};
}

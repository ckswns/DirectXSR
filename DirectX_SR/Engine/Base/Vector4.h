#pragma once

namespace ce
{
	class Vector3;

	class Vector4 final
	{
	public:						Vector4() noexcept;
	public:						Vector4(float x, float y, float z, float w) noexcept;
	public:						Vector4(const D3DXVECTOR4& v) noexcept;
	public:						~Vector4() noexcept;

	public:		Vector4			operator+=(const Vector4& rhs) noexcept;
	public:		Vector4			operator-=(const Vector4& rhs) noexcept;
	public:		Vector4			operator*=(float rhs) noexcept;
	public:		Vector4			operator/=(float rhs) noexcept;

	public:		Vector4			operator+(const Vector4& rhs) noexcept;
	public:		Vector4			operator-(const Vector4& rhs) noexcept;
	public:		Vector4			operator*(float rhs) noexcept;
	public:		Vector4			operator/(float rhs) noexcept;

	public:		bool			operator==(const Vector4& rhs) const noexcept;
	public:		bool			operator!=(const Vector4& rhs) const noexcept;

	public:		Vector3			ToVector3(void) const noexcept;
	public:		D3DXVECTOR4		ConvertD3DXVec4(void) const noexcept;

	public:		float			_x;
	public:		float			_y;
	public:		float			_z;
	public:		float			_w;
	};
}
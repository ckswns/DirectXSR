#include "pch.h"
#include "Vector4.h"
#include "Vector3.h"
#include "CEMath.h"

namespace ce
{
	Vector4::Vector4() noexcept :
		_x(0), _y(0),
		_z(0), _w(0)
	{
	}

	Vector4::Vector4(float x, float y, float z, float w) noexcept :
		_x(x), _y(y),
		_z(z), _w(w)
	{
	}

	Vector4::Vector4(const D3DXVECTOR4& v) noexcept :
		_x(v.x), _y(v.y),
		_z(v.z), _w(v.w)
	{
	}

	Vector4::~Vector4() noexcept
	{
	}

	Vector4 Vector4::operator+=(const Vector4& rhs) noexcept
	{
		_x += rhs._x;
		_y += rhs._y;
		_z += rhs._z;
		_w += rhs._w;

		return *this;
	}

	Vector4 Vector4::operator-=(const Vector4& rhs) noexcept
	{
		_x -= rhs._x;
		_y -= rhs._y;
		_z -= rhs._z;
		_w -= rhs._w;

		return *this;
	}

	Vector4 Vector4::operator*=(float rhs) noexcept
	{
		_x *= rhs;
		_y *= rhs;
		_z *= rhs;
		_w *= rhs;

		return *this;
	}

	Vector4 Vector4::operator/=(float rhs) noexcept
	{
		_x /= rhs;
		_y /= rhs;
		_z /= rhs;
		_w /= rhs;

		return *this;
	}

	Vector4 Vector4::operator+(const Vector4& rhs) noexcept
	{
		return Vector4(_x + rhs._x, _y + rhs._y, _z + rhs._z, _w + rhs._w);
	}

	Vector4 Vector4::operator-(const Vector4& rhs) noexcept
	{
		return Vector4(_x - rhs._x, _y - rhs._y, _z - rhs._z, _w - rhs._w);
	}

	Vector4 Vector4::operator*(float rhs) noexcept
	{
		return Vector4(_x * rhs, _y * rhs, _z * rhs, _w * rhs);
	}

	Vector4 Vector4::operator/(float rhs) noexcept
	{
		return Vector4(_x / rhs, _y / rhs, _z / rhs, _w / rhs);
	}

	bool Vector4::operator==(const Vector4& rhs) const noexcept
	{
		if (CE_MATH::equl_f(_x, rhs._x) && CE_MATH::equl_f(_y, rhs._y) && CE_MATH::equl_f(_z, rhs._z) && CE_MATH::equl_f(_w, rhs._w))
			return true;

		return false;
	}

	bool Vector4::operator!=(const Vector4& rhs) const noexcept
	{
		if (!CE_MATH::equl_f(_x, rhs._x) || !CE_MATH::equl_f(_y, rhs._y) || !CE_MATH::equl_f(_z, rhs._z) || !CE_MATH::equl_f(_w, rhs._w))
			return true;

		return false;
	}

	Vector3 Vector4::ToVector3(void) const noexcept
	{
		return Vector3(_x, _y, _z);
	}

	D3DXVECTOR4 Vector4::ConvertD3DXVec4(void) const noexcept
	{
		return D3DXVECTOR4(_x, _y, _z, _w);
	}
}
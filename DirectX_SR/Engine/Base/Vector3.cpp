#include "pch.h"
#include <cmath>
#include <limits>
#include "Vector3.h"
#include "Vector4.h"
#include "CEMath.h"

namespace ce
{
	const Vector3 Vector3::back = Vector3(0, 0, -1);
	const Vector3 Vector3::down = Vector3(0, -1, 0);
	const Vector3 Vector3::foward = Vector3(0, 0, 1);
	const Vector3 Vector3::left = Vector3(-1, 0, 0);
	const Vector3 Vector3::one = Vector3(1, 1, 1);
	const Vector3 Vector3::right = Vector3(1, 0, 0);
	const Vector3 Vector3::up = Vector3(0, 1, -1);
	const Vector3 Vector3::zero = Vector3(0, 0, 0);


	Vector3::Vector3(void) noexcept :
		_x(0),
		_y(0),
		_z(0)
	{
	}

	Vector3::Vector3(float x, float y, float z) noexcept :
		_x(x),
		_y(y),
		_z(z)
	{
	}

	Vector3::Vector3(const D3DXVECTOR3& v) noexcept :
		_x(v.x),
		_y(v.y),
		_z(v.z)
	{
	}

	Vector3::~Vector3() noexcept
	{
	}

	Vector3::operator Vector4(void) const noexcept
	{
		return Vector4(_x, _y, _z, 0);
	}

	Vector3::operator D3DXVECTOR3(void) const noexcept
	{
		return D3DXVECTOR3(_x, _y, _z);
	}

#ifdef __USE_FMOD__
	Vector3::operator FMOD_VECTOR(void) const noexcept
	{
		return { _x, _y, _z };
	}
#endif
	Vector3 Vector3::operator+(void) const noexcept
	{
		return *this;
	}

	Vector3 Vector3::operator-(void) const noexcept
	{
		return Vector3(-_x, -_y, -_z);
	}

	Vector3 Vector3::operator+=(const Vector3& rhs) noexcept
	{
		_x += rhs._x;
		_y += rhs._y;
		_z += rhs._z;

		return *this;
	}

	Vector3 Vector3::operator-=(const Vector3& rhs) noexcept
	{
		_x -= rhs._x;
		_y -= rhs._y;
		_z -= rhs._z;

		return *this;
	}

	Vector3 Vector3::operator*=(float rhs) noexcept
	{
		_x *= rhs;
		_y *= rhs;
		_z *= rhs;

		return *this;
	}

	Vector3 Vector3::operator/=(float rhs) noexcept
	{
		_x /= rhs;
		_y /= rhs;
		_z /= rhs;

		return *this;
	}

	Vector3 Vector3::operator+(const Vector3& rhs) const noexcept
	{
		return Vector3(_x + rhs._x, _y + rhs._y, _z + rhs._z);
	}

	Vector3 Vector3::operator-(const Vector3& rhs) const noexcept
	{
		return Vector3(_x - rhs._x, _y - rhs._y, _z - rhs._z);
	}

	Vector3 Vector3::operator*(float rhs) const noexcept
	{
		return Vector3(_x * rhs, _y * rhs, _z * rhs);
	}

	Vector3 Vector3::operator/(float rhs) const noexcept
	{
		return Vector3(_x / rhs, _y / rhs, _z / rhs);
	}

	bool Vector3::operator==(const Vector3& rhs) const noexcept
	{
		if (CE_MATH::equl_f(_x, rhs._x) && CE_MATH::equl_f(_y, rhs._y) && CE_MATH::equl_f(_z, rhs._z))
			return true;

		return false;
	}

	bool Vector3::operator!=(const Vector3& rhs) const noexcept
	{
		if (!CE_MATH::equl_f(_x, rhs._x) || !CE_MATH::equl_f(_y, rhs._y) || !CE_MATH::equl_f(_z, rhs._z))
			return true;

		return false;
	}

	float Vector3::Length(void) noexcept
	{
		return std::sqrtf(((_x * _x) + (_y * _y) * (_z * _z)));
	}

	float Vector3::SqrLength(void) noexcept
	{
		return ((_x * _x) + (_y * _y) * (_z * _z));
	}

	float Vector3::Distance(const D3DXVECTOR3& lhs, const D3DXVECTOR3& rhs) noexcept
	{
		D3DXVECTOR3 temp = (lhs - rhs);
		return D3DXVec3Length(&temp);
	}

	float Vector3::Angle(const Vector3& lhs, const Vector3& rhs) noexcept
	{
		Vector3 cross = Cross(lhs, rhs);
		return std::atan2f(cross.Length(), Dot(lhs, rhs));
	}

	float Vector3::Dot(const Vector3& lhs, const Vector3& rhs) noexcept
	{
		return (lhs._x * rhs._x) + (lhs._y * rhs._y) + (lhs._z * rhs._z);
	}

	Vector3 Vector3::Cross(const Vector3& lhs, const Vector3& rhs) noexcept
	{
		return Vector3((lhs._y * rhs._z) - (lhs._z * rhs._y), (lhs._z * rhs._x) - (lhs._x * rhs._z), (lhs._x * rhs._y) - (lhs._y * rhs._x));
	}

	Vector3 Vector3::Lerp(const Vector3& lhs, const Vector3& rhs, float t) noexcept
	{
		return Vector3(lhs._x * (1 - t) + rhs._x * t, lhs._y * (1 - t) + rhs._y * t, lhs._z * (1 - t) + rhs._z * t);
	}

	Vector3 Vector3::SmoothDamp(const Vector3& current, const Vector3& target, OUT Vector3& currentVelocity, float smoothTime, float deltaTime) noexcept
	{
		return Vector3();
	}

	Vector3 Vector3::LookAt(const Vector3& current, const Vector3& target) noexcept
	{
		return Vector3(target._x - current._x, target._y - current._y, target._z - current._z).Nomalize();
	}

	Vector3& Vector3::Nomalize(void) noexcept
	{
		*this /= Length();

		return *this;
	}

	Vector3 Vector3::Nomalized(void) noexcept
	{
		Vector3 temp = Vector3(*this);

		temp /= Length();

		return temp;
	}

	Vector4 Vector3::ToVector4(void) noexcept
	{
		return Vector4(_x, _y, _z, 0);
	}

	std::string Vector3::ToString(void) noexcept
	{
		char str[128];

		sprintf_s(str, 128, "(%s,%s,%s)", std::to_string(_x).c_str(), std::to_string(_y).c_str(), std::to_string(_z).c_str());

		return std::string(str);
	}

	D3DXVECTOR3 Vector3::ConvertD3DXVec3(void) const noexcept
	{
		return D3DXVECTOR3(_x, _y, _z);
	}
}
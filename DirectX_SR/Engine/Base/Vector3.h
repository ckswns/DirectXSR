#pragma once
#include "Vector4.h"

#ifndef OUT
#define OUT
#endif

namespace ce
{
	class Vector4;

	class Vector3 final
	{
	public:								Vector3(void) noexcept;
	public:								Vector3(float x, float y, float z) noexcept;
	public:								Vector3(const D3DXVECTOR3& v) noexcept;
	public:								~Vector3() noexcept;

	public:								operator Vector4(void) const noexcept;
	public:								operator D3DXVECTOR3(void) const noexcept;

#ifdef __USE_FMOD__
	public:								operator FMOD_VECTOR(void) const noexcept;
#endif

	public:		Vector3					operator+(void) const noexcept;
	public:		Vector3					operator-(void) const noexcept;

	public:		Vector3					operator+=(const Vector3& rhs) noexcept;
	public:		Vector3					operator-=(const Vector3& rhs) noexcept;
	public:		Vector3					operator*=(float rhs) noexcept;
	public:		Vector3					operator/=(float rhs) noexcept;

	public:		Vector3					operator+(const Vector3& rhs) const noexcept;
	public:		Vector3					operator-(const Vector3& rhs) const noexcept;
	public:		Vector3					operator*(float rhs) const noexcept;
	public:		Vector3					operator/(float rhs) const noexcept;

	public:		bool					operator==(const Vector3& rhs) const noexcept;
	public:		bool					operator!=(const Vector3& rhs) const noexcept;

	public:		float					Length(void) noexcept;
	public:		float					SqrLength(void) noexcept;

	public:		Vector3&				Nomalize(void) noexcept;
	public:		Vector3					Nomalized(void) noexcept;
	public:		Vector4					ToVector4(void) noexcept;

	public:		std::string				ToString(void) noexcept;

	public:		D3DXVECTOR3				ConvertD3DXVec3(void) const noexcept;

	public:		static float			Distance(const Vector3& lhs, const Vector3& rhs) noexcept;
	public:		static float			Angle(const Vector3& lhs, const Vector3& rhs) noexcept;
	public:		static float			Dot(const Vector3& lhs, const Vector3& rhs) noexcept;

	public:		static Vector3			Cross(const Vector3& lhs, const Vector3& rhs) noexcept;
	public:		static Vector3			Lerp(const Vector3& lhs, const Vector3& rhs, float t) noexcept;//t = 0~1, 0 = lhs, 1 = rhs, 0.5 = half
	public:		static Vector3			SmoothDamp(const Vector3& current, const Vector3& target, OUT Vector3& currentVelocity, float smoothTime, float deltaTime) noexcept;
	public:		static Vector3			LookAt(const Vector3& current, const Vector3& target) noexcept;

	public:		float					_x;
	public:		float					_y;
	public:		float					_z;

	public:		static const Vector3	back;
	public:		static const Vector3	down;
	public:		static const Vector3	foward;
	public:		static const Vector3	left;
	public:		static const Vector3	one;
	public:		static const Vector3	right;
	public:		static const Vector3	up;
	public:		static const Vector3	zero;
	};
}
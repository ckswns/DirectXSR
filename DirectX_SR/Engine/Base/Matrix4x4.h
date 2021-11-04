#pragma once

#include "TypeDefine.h"
#include "Vector3.h"

#ifndef OUT
#define OUT
#endif

namespace ce
{
	class Matrix4x4 final
	{
	public:								Matrix4x4(void) noexcept;
	public:								~Matrix4x4(void) noexcept;

	public:								Matrix4x4(const float m11, const float m12, const float m13, const float m14
												, const float m21, const float m22, const float m23, const float m24
												, const float m31, const float m32, const float m33, const float m34
												, const float m41, const float m42, const float m43, const float m44
												) noexcept;
	public:								Matrix4x4(const Matrix4x4& rhs) noexcept;

	public:								operator D3DXMATRIX(void) noexcept;

	public:		float&					operator() (uint row, uint col) noexcept;
	public:		float					operator() (uint row, uint col) const noexcept;

	public:		Matrix4x4&				operator*=(const Matrix4x4& rhs) noexcept;
	public:		Matrix4x4&				operator+=(const Matrix4x4& rhs) noexcept;
	public:		Matrix4x4&				operator-=(const Matrix4x4& rhs) noexcept;

	public:		Matrix4x4&				operator*=(float rhs) noexcept;
	public:		Matrix4x4&				operator/=(float rhs) noexcept;

	public:		Matrix4x4				operator*(const Matrix4x4& rhs) const noexcept;
	public:		Matrix4x4				operator+(const Matrix4x4& rhs) const noexcept;
	public:		Matrix4x4				operator-(const Matrix4x4& rhs) const noexcept;

	public:		Matrix4x4				operator*(float rhs) const noexcept;
	public:		Matrix4x4				operator/(float rhs) const noexcept;

	public:		bool					operator==(const Matrix4x4& rhs) const noexcept;
	public:		bool					operator!=(const Matrix4x4& rhs) const noexcept;

	public:		Vector3					Left(void) const noexcept;
	public:		Vector3					Right(void) const noexcept;
	public:		Vector3					Up(void) const noexcept;
	public:		Vector3					Down(void) const noexcept;
	public:		Vector3					Foward(void) const noexcept;
	public:		Vector3					Back(void) const noexcept;
	public:		Vector3					Position(void) const noexcept;
	public:		Vector3					Scale(void) const noexcept;

	public:		Matrix4x4&				Transpose(void) noexcept;
	public:		Matrix4x4&				Inverse(void) noexcept;			

	public:		static Matrix4x4		Translation(const Vector3& pos) noexcept;
	public:		static Matrix4x4		Scaling(const Vector3& scale) noexcept;
	public:		static Matrix4x4		RotationX(const float angle) noexcept;
	public:		static Matrix4x4		RotationY(const float angle) noexcept;
	public:		static Matrix4x4		RotationZ(const float angle) noexcept;
	public:		static Matrix4x4		RotationAxix(const Vector3& axis, const float angle) noexcept;
	public:		static Matrix4x4		RotationYawPitchRoll(const float y, const float x, const float z) noexcept;
		  
	public:		static Matrix4x4		LookAtLH(const Vector3& eye, const Vector3& at, const Vector3& up = Vector3::up) noexcept;
	public:		static Matrix4x4		LookRotationLH(const Vector3& eye, const Vector3& at, const Vector3& up = Vector3::up) noexcept;
	public:		static Matrix4x4		PerspectiveLH(const float width, const float height, const float near, const float far) noexcept;
	public:		static Matrix4x4		PerspectiveFovLH(const float fovY, const float aspect, const float near, const float far) noexcept;
	public:		static Matrix4x4		OrthoLH(const float width, const float height, const float near, const float far) noexcept;

	public:		static Matrix4x4&		Identity(OUT Matrix4x4& mat) noexcept;

	public:		static const Matrix4x4	zero;
	public:		static const Matrix4x4	identity;

	public:		union
				{
					struct
					{
						float			_11, _12, _13, _14;
						float			_21, _22, _23, _24;
						float			_31, _32, _33, _34;
						float			_41, _42, _43, _44;
					};
					float m[4][4];
				};
	};
}

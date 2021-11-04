#include "pch.h"
#include "Matrix4x4.h"
#include "Vector3.h"
#include <math.h>
#include "ConstValues.h"
#include "CEMath.h"

namespace ce
{
	const Matrix4x4 Matrix4x4::zero(0.0f, 0.0f, 0.0f, 0.0f,
									0.0f, 0.0f, 0.0f, 0.0f,
									0.0f, 0.0f, 0.0f, 0.0f,
									0.0f, 0.0f, 0.0f, 0.0f);

	const Matrix4x4 Matrix4x4::identity(1.0f, 0.0f, 0.0f, 0.0f,
										0.0f, 1.0f, 0.0f, 0.0f,
										0.0f, 0.0f, 1.0f, 0.0f,
										0.0f, 0.0f, 0.0f, 1.0f);

	Matrix4x4::Matrix4x4() noexcept :
		_11(0), _12(0), _13(0), _14(0),
		_21(0), _22(0), _23(0), _24(0),
		_31(0), _32(0), _33(0), _34(0),
		_41(0), _42(0), _43(0), _44(0)
	{
	}

	Matrix4x4::~Matrix4x4() noexcept
	{
	}

	Matrix4x4::Matrix4x4(	const float m11, const float m12, const float m13, const float m14,
							const float m21, const float m22, const float m23, const float m24,
							const float m31, const float m32, const float m33, const float m34,
							const float m41, const float m42, const float m43, const float m44) noexcept :
		_11(m11), _12(m12), _13(m13), _14(m14),
		_21(m21), _22(m22), _23(m23), _24(m24),
		_31(m31), _32(m32), _33(m33), _34(m34),
		_41(m41), _42(m42), _43(m43), _44(m44)
	{
	}

	Matrix4x4::Matrix4x4(const Matrix4x4& rhs) noexcept
	{
		memcpy((void*)m, (void*)rhs.m, sizeof(m));
	}

	Matrix4x4::operator D3DXMATRIX(void) noexcept
	{
		return D3DXMATRIX(	_11, _12, _13, _14,
							_21, _22, _23, _24,
							_31, _32, _33, _34,
							_41, _42, _43, _44);
	}

	float& Matrix4x4::operator()(uint row, uint col) noexcept
	{
		return m[row][col];
	}

	float Matrix4x4::operator()(uint row, uint col) const noexcept
	{
		return m[row][col];
	}

	Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& rhs) noexcept
	{
		_11 = _11 * rhs._11 + _12 * rhs._21 + _13 * rhs._31 + _14 * rhs._41;
		_12 = _11 * rhs._12 + _12 * rhs._22 + _13 * rhs._32 + _14 * rhs._42;
		_13 = _11 * rhs._13 + _12 * rhs._23 + _13 * rhs._33 + _14 * rhs._43;
		_14 = _11 * rhs._14 + _12 * rhs._24 + _13 * rhs._34 + _14 * rhs._44;
		_21 = _21 * rhs._11 + _22 * rhs._21 + _23 * rhs._31 + _24 * rhs._41;
		_22 = _21 * rhs._12 + _22 * rhs._22 + _23 * rhs._32 + _24 * rhs._42;
		_23 = _21 * rhs._13 + _22 * rhs._23 + _23 * rhs._33 + _24 * rhs._43;
		_24 = _21 * rhs._14 + _22 * rhs._24 + _23 * rhs._34 + _24 * rhs._44;
		_31 = _31 * rhs._11 + _32 * rhs._21 + _33 * rhs._31 + _34 * rhs._41;
		_32 = _31 * rhs._12 + _32 * rhs._22 + _33 * rhs._32 + _34 * rhs._42;
		_33 = _31 * rhs._13 + _32 * rhs._23 + _33 * rhs._33 + _34 * rhs._43;
		_34 = _31 * rhs._14 + _32 * rhs._24 + _33 * rhs._34 + _34 * rhs._44;
		_41 = _41 * rhs._11 + _42 * rhs._21 + _43 * rhs._31 + _44 * rhs._41;
		_42 = _41 * rhs._12 + _42 * rhs._22 + _43 * rhs._32 + _44 * rhs._42;
		_43 = _41 * rhs._13 + _42 * rhs._23 + _43 * rhs._33 + _44 * rhs._43;
		_44 = _41 * rhs._14 + _42 * rhs._24 + _43 * rhs._34 + _44 * rhs._44;

		return *this;
	}

	Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& rhs) noexcept
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] += rhs.m[i][j];
			}
		}

		return *this;
	}

	Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& rhs) noexcept
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] -= rhs.m[i][j];
			}
		}

		return *this;
	}

	Matrix4x4& Matrix4x4::operator*=(float rhs) noexcept
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] *= rhs;
			}
		}

		return *this;
	}

	Matrix4x4& Matrix4x4::operator/=(float rhs) noexcept
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] /= rhs;
			}
		}

		return *this;
	}

	Matrix4x4 Matrix4x4::operator*(const Matrix4x4& rhs) const noexcept
	{
		Matrix4x4 mat;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					mat.m[i][j] += (m[i][j] * rhs.m[k][j]);
				}
			}
		}

		return mat;
	}

	Matrix4x4 Matrix4x4::operator+(const Matrix4x4& rhs) const noexcept
	{
		Matrix4x4 mat;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				mat.m[i][j] = m[i][j] + rhs.m[i][j];
			}
		}

		return mat;
	}

	Matrix4x4 Matrix4x4::operator-(const Matrix4x4& rhs) const noexcept
	{
		Matrix4x4 mat;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				mat.m[i][j] = m[i][j] - rhs.m[i][j];
			}
		}

		return mat;
	}

	Matrix4x4 Matrix4x4::operator*(float rhs) const noexcept
	{
		Matrix4x4 mat;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				mat.m[i][j] = m[i][j] * rhs;
			}
		}

		return mat;
	}

	Matrix4x4 Matrix4x4::operator/(float rhs) const noexcept
	{
		Matrix4x4 mat;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				mat.m[i][j] = m[i][j] / rhs;
			}
		}

		return mat;
	}

	bool Matrix4x4::operator==(const Matrix4x4& rhs) const noexcept
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (!CE_MATH::equl_f(m[i][j], rhs.m[i][j]))
				{
					return false;
				}
			}
		}

		return true;
	}

	bool Matrix4x4::operator!=(const Matrix4x4& rhs) const noexcept
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (!CE_MATH::equl_f(m[i][j], rhs.m[i][j]))
				{
					return true;
				}
			}
		}

		return false;
	}

	Vector3 Matrix4x4::Left(void) const noexcept
	{
		return Vector3(-_11, -_12, -_13);
	}

	Vector3 Matrix4x4::Right(void) const noexcept
	{
		return Vector3(_11, _12, _13);
	}

	Vector3 Matrix4x4::Up(void) const noexcept
	{
		return Vector3(_21, _22, _23);
	}

	Vector3 Matrix4x4::Down(void) const noexcept
	{
		return Vector3(-_21, -_22, -_23);
	}

	Vector3 Matrix4x4::Foward(void) const noexcept
	{
		return Vector3(_31, _32, _33);
	}

	Vector3 Matrix4x4::Back(void) const noexcept
	{
		return Vector3(-_31, -_32, -_33);
	}

	Vector3 Matrix4x4::Position(void) const noexcept
	{
		return Vector3(_41, _42, _43);
	}

	Vector3 Matrix4x4::Scale(void) const noexcept
	{
		return Vector3();
	}

	Matrix4x4& Matrix4x4::Transpose(void) noexcept
	{
		float temp;

		temp = m[0][1];
		m[0][1] = m[1][0];
		m[1][0] = temp;

		temp = m[0][2];
		m[0][2] = m[2][0];
		m[2][0] = temp;

		temp = m[1][2];
		m[1][2] = m[2][1];
		m[2][1] = temp;

		temp = m[0][3];
		m[0][3] = m[3][0];
		m[3][0] = temp;

		temp = m[1][3];
		m[1][3] = m[3][1];
		m[3][1] = temp;

		temp = m[2][3];
		m[2][3] = m[3][2];
		m[3][2] = temp;

		return *this;
	}

	Matrix4x4& Matrix4x4::Inverse(void) noexcept
	{
		// TODO: insert return statement here
		return *this;
	}

	Matrix4x4 Matrix4x4::Translation(const Vector3& pos) noexcept
	{
		return				Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f
									, 0.0f, 1.0f, 0.0f, 0.0f
									, 0.0f, 0.0f, 1.0f, 0.0f
									, pos._x, pos._y, pos._z, 1.0f);
	}

	Matrix4x4 Matrix4x4::Scaling(const Vector3& scale) noexcept
	{
		return				Matrix4x4(scale._x, 0.0f, 0.0f, 0.0f
									, 0.0f, scale._y, 0.0f, 0.0f
									, 0.0f, 0.0f, scale._z, 0.0f
									, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	Matrix4x4 Matrix4x4::RotationX(const float angle) noexcept
	{
		const float cos = std::cosf(angle);
		const float sin = std::sinf(angle);

		return				Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f
									, 0.0f, cos, sin, 0.0f
									, 0.0f, -sin, cos, 0.0f
									, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	Matrix4x4 Matrix4x4::RotationY(const float angle) noexcept
	{
		const float cos = std::cosf(angle);
		const float sin = std::sinf(angle);

		return				Matrix4x4(cos, 0.0f, -sin, 0.0f
									, 0.0f, 1.0f, 0.0f, 0.0f
									, sin, 0.0f, cos, 0.0f
									, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	Matrix4x4 Matrix4x4::RotationZ(const float angle) noexcept
	{
		const float cos = std::cosf(angle);
		const float sin = std::sinf(angle);

		return				Matrix4x4(cos, sin, 0.0f, 0.0f
									, -sin, cos, 0.0f, 0.0f
									, 0.0f, 0.0f, 1.0f, 0.0f
									, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	Matrix4x4 Matrix4x4::RotationAxix(const Vector3& axis, const float angle) noexcept
	{
		const float x = axis._x;
		const float y = axis._y;
		const float z = axis._z;
		const float xx = x * x;
		const float yy = y * y;
		const float zz = z * z;
		const float xy = x * y;
		const float xz = x * z;
		const float yz = y * z;
		const float cos = std::cosf(angle);
		const float sin = std::sinf(angle);

		return				Matrix4x4(xx + cos * (1.0f - xx), xy - cos * xy + sin * z, xz - cos * xz - sin * y, 0.0f
									, xy - cos * xy - sin * z, yy + cos * (1.0f - yy), yz - cos * yz + sin * x, 0.0f
									, xz - cos * xz + sin * y, yz - cos * yz - sin * x, zz + cos * (1.0f - zz), 0.0f
									, 0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Matrix4x4 Matrix4x4::RotationYawPitchRoll(const float y, const float x, const float z) noexcept
	{
		const Matrix4x4 matYaw = RotationY(y);
		const Matrix4x4 matPitch = RotationX(x);
		const Matrix4x4 matRoll = RotationZ(z);

		return matRoll * matPitch * matYaw;
	}

	Matrix4x4 Matrix4x4::LookAtLH(const Vector3& eye, const Vector3& at, const Vector3& up) noexcept
	{
		return Matrix4x4();
	}

	Matrix4x4 Matrix4x4::LookRotationLH(const Vector3& eye, const Vector3& at, const Vector3& up) noexcept
	{
		return Matrix4x4();
	}

	Matrix4x4 Matrix4x4::PerspectiveLH(const float width, const float height, const float znear, const float zfar) noexcept
	{
		const float range = zfar / (zfar - znear);
		return				Matrix4x4(2.0f * znear / width, 0.0f, 0.0f, 0.0f
									, 0.0f, 2.0f * znear / height, 0.0f, 0.0f
									, 0.0f, 0.0f, range, 1.0f
									, 0.0f, 0.0f, -znear * range, 0.0f);
	}

	Matrix4x4 Matrix4x4::PerspectiveFovLH(const float fovY, const float aspect, const float znear, const float zfar) noexcept
	{
		const float d = 1.0f / std::tan(fovY * 0.5f);
		const float q = zfar / (zfar - znear);

		return				Matrix4x4(d / aspect, 0.0f, 0.0f, 0.0f
									, 0.0f, d, 0.0f, 0.0f
									, 0.0f, 0.0f, q, 1.0f
									, 0.0f, 0.0f, -q * znear, 0.0f);
	}

	Matrix4x4 Matrix4x4::OrthoLH(const float width, const float height, const float znear, const float zfar) noexcept
	{
		const float range = 1.0f / (zfar - znear);

		return				Matrix4x4(2.0f / width, 0.0f, 0.0f, 0.0f
									, 0.0f, 2.0f / height, 0.0f, 0.0f
									, 0.0f, 0.0f, range, 0.0f
									, 0.0f, 0.0f, -znear * range, 1.0f);
	}

	Matrix4x4& Matrix4x4::Identity(OUT Matrix4x4& mat) noexcept
	{
		memcpy((void*)&mat, (void*)&Matrix4x4::identity, sizeof(Matrix4x4));

		return mat;
	}
}
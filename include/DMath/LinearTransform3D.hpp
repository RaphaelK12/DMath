#pragma once

#include "Setup.hpp"

#include "Matrix/Matrix.hpp"
#include "Vector/Vector.hpp"
#include "UnitQuaternion.hpp"
#include "Enum.hpp"
#include "Trigonometric.hpp"

#include <exception>
#include <string_view>
#include <cassert>

namespace Math
{
	namespace LinearTransform3D
	{
		[[nodiscard]] constexpr Matrix<4, 3> Multiply(const Matrix<4, 3>& left, const Matrix<4, 3>& right);
		[[nodiscard]] constexpr Matrix4x4 AsMat4(const Matrix<4, 3>& input);

		[[nodiscard]] constexpr Matrix4x4 Translate(float x, float y, float z);
		[[nodiscard]] constexpr Matrix4x4 Translate(const Vector3D& input);
		[[nodiscard]] constexpr Matrix<4, 3> Translate_Reduced(float x, float y, float z);
		[[nodiscard]] constexpr Matrix<4, 3> Translate_Reduced(const Vector3D& input);

		constexpr void AddTranslation(Matrix4x4& matrix, float x, float y, float z);
		constexpr void AddTranslation(Matrix4x4& matrix, const Vector3D& input);
		constexpr void AddTranslation(Matrix<4, 3>& matrix, float x, float y, float z);
		constexpr void AddTranslation(Matrix<4, 3>& matrix, const Vector3D& input);

		template<AngleUnit angleUnit = Setup::defaultAngleUnit>
		[[nodiscard]] Matrix3x3 Rotate(ElementaryAxis axis, float amount);
		template<AngleUnit angleUnit = Setup::defaultAngleUnit>
		[[nodiscard]] Matrix4x4 Rotate_Homo(ElementaryAxis axis, float amount);
		template<AngleUnit angleUnit = Setup::defaultAngleUnit>
		[[nodiscard]] Matrix3x3 Rotate(float x, float y, float z);
		template<AngleUnit angleUnit = Setup::defaultAngleUnit>
		[[nodiscard]] Matrix3x3 Rotate(const Vector3D& angles);
		template<AngleUnit angleUnit = Setup::defaultAngleUnit>
		[[nodiscard]] Matrix3x3 Rotate(const Vector3D& axis, float amount);
		[[nodiscard]] constexpr Matrix4x4 Rotate_Homo(const UnitQuaternion<>& quat);
		[[nodiscard]] constexpr Matrix<4, 3> Rotate_Reduced(const UnitQuaternion<>& quat);

		[[nodiscard]] constexpr Matrix3x3 Scale(float x, float y, float z);
		[[nodiscard]] constexpr Matrix3x3 Scale(const Vector3D& input);
		[[nodiscard]] constexpr Matrix4x4 Scale_Homo(float x, float y, float z);
		[[nodiscard]] constexpr Matrix4x4 Scale_Homo(const Vector3D& input);
		[[nodiscard]] constexpr Matrix<4, 3> Scale_Reduced(float x, float y, float z);
		[[nodiscard]] constexpr Matrix<4, 3> Scale_Reduced(const Vector3D& input);

		[[nodiscard]] Matrix4x4 LookAt_LH(const Vector3D& position, const Vector3D& forward, const Vector3D& upVector);
		[[nodiscard]] Matrix4x4 LookAt_RH(const Vector3D& position, const Vector3D& forward, const Vector3D& upVector);

		template<typename T = float>
		[[nodiscard]] Matrix<4, 4, T> Perspective_RH_ZO(T fovY, T aspectRatio, T zNear, T zFar);
		template<typename T = float>
		[[nodiscard]] Matrix<4, 4, T> Perspective_RH_NO(T fovY, T aspectRatio, T zNear, T zFar);
		template<typename T = float>
		[[nodiscard]] Matrix<4, 4, T> Perspective(API3D api, T fovY, T aspectRatio, T zNear, T zFar);

		template<typename T = float>
		[[nodiscard]] Matrix<4, 4, T> Orthographic_RH_ZO(T left, T right, T bottom, T top, T zNear, T zFar);
		template<typename T = float>
		[[nodiscard]] Matrix<4, 4, T> Orthographic_RH_NO(T left, T right, T bottom, T top, T zNear, T zFar);
		template<typename T = float>
		[[nodiscard]] Matrix<4, 4, T> Orthographic(API3D api, T left, T right, T bottom, T top, T zNear, T zFar);
	}

	namespace LinTran3D = LinearTransform3D;
}

constexpr Math::Matrix<4, 3> Math::LinearTransform3D::Multiply(const Matrix<4, 3>& left, const Matrix<4, 3>& right)
{
	Math::Matrix<4, 3> newMatrix{};
	for (size_t x = 0; x < 3; x++)
	{
		for (size_t y = 0; y < 3; y++)
		{
			Math::Matrix<4, 3>::ValueType dot{};
			for (size_t i = 0; i < 3; i++)
				dot += left[i][y] * right[x][i];
			newMatrix[x][y] = dot;
		}
	}

	for (size_t y = 0; y < 3; y++)
	{
		Math::Matrix<4, 3>::ValueType dot{};
		for (size_t i = 0; i < 3; i++)
			dot += left[i][y] * right[3][i];
		dot += left[3][y];
		newMatrix[3][y] = dot;
	}

	return newMatrix;
}

constexpr Math::Matrix4x4 Math::LinearTransform3D::AsMat4(const Math::Matrix<4, 3>& input)
{
	Matrix4x4 newMat{};

	for (size_t x = 0; x < 4; x++)
	{
		for (size_t y = 0; y < 3; y++)
			newMat.At(x, y) = input.At(x, y);
	}

	newMat.Back() = 1;
	return newMat;
}


constexpr Math::Matrix4x4 Math::LinearTransform3D::Translate(float x, float y, float z)
{
	return Matrix4x4
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x, y, z, 1
	};
}

constexpr Math::Matrix4x4 Math::LinearTransform3D::Translate(const Vector3D& input) 
{
	return Translate(input.x, input.y, input.z);
}

constexpr Math::Matrix<4, 3> Math::LinearTransform3D::Translate_Reduced(float x, float y, float z)
{
	return Matrix<4, 3>
	{
		1, 0, 0,
		0, 1, 0,
		0, 0, 1,
		x, y, z,
	};
}

constexpr Math::Matrix<4, 3> Math::LinearTransform3D::Translate_Reduced(const Vector3D & input) { return Translate_Reduced(input.x, input.y, input.z); }

constexpr void Math::LinearTransform3D::AddTranslation(Matrix4x4& matrix, float x, float y, float z)
{
	matrix[3][0] = x;
	matrix[3][1] = y;
	matrix[3][2] = z;
}

constexpr void Math::LinearTransform3D::AddTranslation(Matrix4x4& matrix, const Vector3D& input)
{
	AddTranslation(matrix, input.x, input.y, input.z);
}

constexpr void Math::LinearTransform3D::AddTranslation(Matrix<4, 3>& matrix, float x, float y, float z)
{
	matrix[3][0] = x;
	matrix[3][1] = y;
	matrix[3][2] = z;
}

constexpr void Math::LinearTransform3D::AddTranslation(Matrix<4, 3>& matrix, const Vector3D& input) { AddTranslation(matrix, input.x, input.y, input.z); }

template<Math::AngleUnit angleUnit>
Math::Matrix4x4 Math::LinearTransform3D::Rotate_Homo(ElementaryAxis axis, float amount)
{
	assert(axis == Math::ElementaryAxis::X || axis == Math::ElementaryAxis::Y || axis == Math::ElementaryAxis::Z);
	const float cos = Cos<angleUnit>(amount);
	const float sin = Sin<angleUnit>(amount);
	switch (axis)
	{
	case ElementaryAxis::X:
		return Matrix4x4
		({
			1, 0, 0, 0,
			0, cos, sin, 0,
			0, -sin, cos, 0,
			0, 0, 0, 1
		});
	case ElementaryAxis::Y:
		return Matrix4x4
		({
			cos, 0, -sin, 0,
			0, 1, 0, 0,
			sin, 0, cos, 0,
			0, 0, 0, 1
		});
	default:
		return Matrix4x4
		({
			cos, sin, 0, 0,
			-sin, cos, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		});
	};
}

template<Math::AngleUnit angleUnit>
Math::Matrix3x3 Math::LinearTransform3D::Rotate(float x, float y, float z)
{
	return Rotate<angleUnit>(ElementaryAxis::Z, z) * Rotate<angleUnit>(ElementaryAxis::Y, y) * Rotate<angleUnit>(ElementaryAxis::X, x);
}

template<Math::AngleUnit angleUnit>
Math::Matrix3x3 Math::LinearTransform3D::Rotate(const Vector3D& angles)
{
	return Rotate<angleUnit>(angles.x, angles.y, angles.z);
}

template<Math::AngleUnit angleUnit>
Math::Matrix3x3 Math::LinearTransform3D::Rotate(const Vector3D& axisInput, float amount)
{
	Vector3D axis = axisInput.GetNormalized();
	const float cos = Cos<angleUnit>(amount);
	const float sin = Sin<angleUnit>(amount);
	return Matrix3x3
	{
		cos + Sqrd(axis.x)*(1 - cos), axis.x*axis.y*(1 - cos) - axis.z*sin, axis.x*axis.z*(1 - cos) + axis.y*sin,
		axis.y*axis.x*(1 - cos) + axis.z*sin, cos + Sqrd(axis.y)*(1 - cos), axis.y*axis.z*(1 - cos) - axis.x*sin,
		axis.z*axis.x*(1 - cos) - axis.y*sin, axis.z*axis.y*(1 - cos) + axis.x*sin, cos + Sqrd(axis.z)*(1 - cos)
	}.GetTransposed();
}

constexpr Math::Matrix4x4 Math::LinearTransform3D::Rotate_Homo(const UnitQuaternion<>& quat)
{
	return static_cast<Math::Matrix4x4>(quat);
}

constexpr Math::Matrix<4, 3> Math::LinearTransform3D::Rotate_Reduced(const UnitQuaternion<>& quat)
{
	return static_cast<Math::Matrix<4, 3>>(quat);
}

constexpr Math::Matrix3x3 Math::LinearTransform3D::Scale(float x, float y, float z)
{
	return Matrix3x3
	({
		x, 0, 0,
		0, y, 0,
		0, 0, z
	});
}

constexpr Math::Matrix3x3 Math::LinearTransform3D::Scale(const Vector3D& input)
{
	return Scale(input.x, input.y, input.z);
}

constexpr Math::Matrix4x4 Math::LinearTransform3D::Scale_Homo(float x, float y, float z)
{
	return Matrix4x4
	({
		 x, 0, 0, 0,
		 0, y, 0, 0,
		 0, 0, z, 0,
		 0, 0, 0, 1
	});
}

constexpr Math::Matrix4x4 Math::LinearTransform3D::Scale_Homo(const Math::Vector3D &input)
{
	return Scale_Homo(input.x, input.y, input.z);
}

constexpr Math::Matrix<4, 3> Math::LinearTransform3D::Scale_Reduced(float x, float y, float z)
{
	return Matrix<4, 3>
	({
		x, 0, 0,
		0, y, 0,
		0, 0, z,
		0, 0, 0,
	});
}

constexpr Math::Matrix<4, 3> Math::LinearTransform3D::Scale_Reduced(const Vector3D& input) { return Scale_Reduced(input.x, input.y, input.z); }

inline Math::Matrix4x4 Math::LinearTransform3D::LookAt_LH(const Vector3D& position, const Vector3D& forward, const Vector3D& upVector)
{
	Vector3D zAxis = (forward - position).GetNormalized();
	Vector3D xAxis = Vector3D::Cross(upVector, zAxis).GetNormalized();
	Vector3D yAxis = Vector3D::Cross(zAxis, xAxis);
	return Matrix4x4
	({
		xAxis.x, yAxis.x, zAxis.x, 0,
		xAxis.y, yAxis.y, zAxis.y, 0,
		xAxis.z, yAxis.z, zAxis.z, 0,
		-Vector3D::Dot(xAxis, position), -Vector3D::Dot(yAxis, position), -Vector3D::Dot(zAxis, position), 1
	});
}

inline Math::Matrix4x4 Math::LinearTransform3D::LookAt_RH(const Vector3D& position, const Vector3D& forward, const Vector3D& upVector)
{
	Vector3D zAxis = (position - forward).GetNormalized();
	Vector3D xAxis = Vector3D::Cross(upVector, zAxis).GetNormalized();
	Vector3D yAxis = Vector3D::Cross(zAxis, xAxis);
	return Matrix4x4
	({
		xAxis.x, yAxis.x, zAxis.x, 0,
		xAxis.y, yAxis.y, zAxis.y, 0,
		xAxis.z, yAxis.z, zAxis.z, 0,
		-Vector3D::Dot(xAxis, position), -Vector3D::Dot(yAxis, position), -Vector3D::Dot(zAxis, position), 1
	});
}

template<typename T>
inline Math::Matrix<4, 4, T> Math::LinearTransform3D::Perspective_RH_ZO(T fovY, T aspectRatio, T zNear, T zFar)
{
	static_assert
	(
		std::is_floating_point<T>(),
		"DMath error. Template argument T in Math::LinearTransform3D::PerspectiveRH_ZO must be floating point type."
	);

	const T tanHalfFovy = Tan<AngleUnit::Degrees>(fovY / 2);
	return Matrix<4, 4, T>
	({
		1 / (aspectRatio * tanHalfFovy), 0, 0, 0,
		0, 1 / tanHalfFovy, 0, 0,
		0, 0, zFar / (zNear - zFar), -1,
		0, 0, -(zFar * zNear) / (zFar - zNear), 0
	});
}

template<typename T>
inline Math::Matrix<4, 4, T> Math::LinearTransform3D::Perspective_RH_NO(T fovY, T aspectRatio, T zNear, T zFar)
{
	static_assert
	(
		std::is_floating_point<T>(),
		"DMath error. Template argument T in Math::LinearTransform3D::PerspectiveRH_NO must be floating point type."
	);

	const T tanHalfFovy = Tan<AngleUnit::Degrees>(fovY / 2);
	return Matrix<4, 4, T>
	({
		1 / (aspectRatio * tanHalfFovy), 0, 0, 0,
		0, 1 / tanHalfFovy, 0, 0,
		0, 0, -(zFar + zNear) / (zFar - zNear), -1,
		0, 0, -(2 * zFar * zNear) / (zFar - zNear), 0
	});
}

template<typename T>
inline Math::Matrix<4, 4, T> Math::LinearTransform3D::Perspective(API3D api, T fovY, T aspectRatio, T zNear, T zFar)
{
	static_assert
	(
		std::is_floating_point<T>(),
		"DMath error. Template argument T in Math::LinearTransform3D::Perspective must be floating point type."
	);

	switch (api)
	{
	case API3D::OpenGL:
		return Perspective_RH_NO<T>(fovY, aspectRatio, zNear, zFar);
	case API3D::Vulkan:
		return Perspective_RH_ZO<T>(fovY, aspectRatio, zNear, zFar);
	default:
		assert(false);
		return {};
	}
}

template<typename T>
Math::Matrix<4, 4, T> Math::LinearTransform3D::Orthographic_RH_ZO(T left, T right, T bottom, T top, T zNear, T zFar)
{
	static_assert
	(
		std::is_floating_point<T>(),
		"DMath error. Template argument T in Math::LinearTransform3D::Orthographic_RH_ZO must be floating point type."
	);

	return Matrix<4, 4, T>
	({
		2 / (right - left), 0, 0, 0,
		0, 2 / (top - bottom), 0, 0,
		0, 0, -(1 / (zFar - zNear)), 0,
		-(right + left) / (right - left), -(top + bottom) / (top - bottom), -zNear / (zFar - zNear), 1
	});
}

template<typename T>
Math::Matrix<4, 4, T> Math::LinearTransform3D::Orthographic_RH_NO(T left, T right, T bottom, T top, T zNear, T zFar)
{
	static_assert
	(
		std::is_floating_point<T>(),
		"DMath error. Template argument T in Math::LinearTransform3D::Orthographic_RH_NO must be floating point type."
	);

	return Matrix<4, 4, T>
	({
		2 / (right - left), 0, 0, 0,
		0, 2 / (top - bottom), 0, 0,
		0, 0, -(2 / (zFar - zNear)), 0,
		-(right + left) / (right - left), -(top + bottom) / (top - bottom), -zNear / (zFar - zNear), 1
	});
}

template<typename T>
[[nodiscard]] Math::Matrix<4, 4, T> Math::LinearTransform3D::Orthographic(API3D api, T left, T right, T bottom, T top, T zNear, T zFar)
{
	static_assert
	(
		std::is_floating_point<T>(),
		"DMath error. Template argument T in Math::LinearTransform3D::Orthographic must be floating point type."
	);

	switch (api)
	{
	case API3D::OpenGL:
		return Orthographic_RH_NO<T>(left, right, bottom, top, zNear, zFar);
	case API3D::Vulkan:
		return Orthographic_RH_ZO<T>(left, right, bottom, top, zNear, zFar);
	default:
		assert(false);
		return {};
	}
}
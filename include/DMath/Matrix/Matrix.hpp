#pragma once

#include "MatrixBase.hpp"
#include "MatrixBaseSquare.hpp"

#include <initializer_list>
#include <sstream>

namespace Math
{
	template<size_t length, typename T>
	struct Vector;

	namespace detail
	{
		namespace Matrix
		{
			using DefaultValueType = float;
		}
	}

	using Matrix2x2 = Matrix<2, 2, float>;
	using Matrix2x2Int = Matrix<2, 2, uint32_t>;
	using Matrix3x3 = Matrix<3, 3, float>;
	using Matrix3x3Int = Matrix<3, 3, uint32_t>;
	using Matrix4x4 = Matrix<4, 4, float>;
	using Matrix4x4Int = Matrix<4, 4, uint32_t>;

	template<size_t width, size_t height, typename T = detail::Matrix::DefaultValueType>
	struct Matrix : public std::conditional_t<width == height, detail::MatrixBaseSquare<width, T>, detail::MatrixBase<width, height, T>>
	{
	public:
		using ParentType = std::conditional_t<width == height, detail::MatrixBaseSquare<width, T>, detail::MatrixBase<width, height, T>>;
		using ValueType = T;

		[[nodiscard]] constexpr T& At(size_t i)
		{
#if defined( _MSC_VER )
			__assume(i < width * height);
#endif
			assert(i < width * height);
			return data[i];
		}
		[[nodiscard]] constexpr const T& At(size_t i) const
		{
#if defined( _MSC_VER )
			__assume(i < width * height);
#endif
			assert(i < width * height);
			return data[i];
		}
		[[nodiscard]] constexpr T& At(size_t x, size_t y)
		{
#if defined( _MSC_VER )
			__assume(i < width && i < height);
#endif
			assert(x < width && y < height);
			return data[x * height + y];
		}
		[[nodiscard]] constexpr const T& At(size_t x, size_t y) const
		{
#if defined( _MSC_VER )
			__assume(i < width && i < height);
#endif
			assert(x < width && y < height);
			return data[x * height + y];
		}

		[[nodiscard]] constexpr T& Back()
		{
			return data.back();
		}
		[[nodiscard]] constexpr const T& Back() const
		{
			return data.back();
		}
		[[nodiscard]] constexpr T* GetData()
		{
			return data.data();
		}
		[[nodiscard]] constexpr const T* GetData() const
		{
			return data.data();
		}

		[[nodiscard]] constexpr Matrix<height, width, T> GetTransposed() const
		{
			Matrix<height, width, T> temp;
			for (size_t x = 0; x < width; x++)
			{
				for (size_t y = 0; y < height; y++)
					temp[x][y] = (*this)[y][x];
			}
			return temp;
		}

		constexpr void SwapRows(size_t row1, size_t row2)
		{
#if defined( _MSC_VER )
			__assume(row1 < height && row2 < height);
#endif
			assert(row1 < height && row2 < height);
			for (size_t x = 0; x < width; x++)
				std::swap((*this)[x][row1], (*this)[x][row2]);
		}

		constexpr void SwapColumns(size_t column1, size_t column2)
		{
#if defined( _MSC_VER )
			__assume(column1 < width && column2 < width);
#endif
			assert(column1 < width && column2 < width);
			for (size_t y = 0; y < height; y++)
				std::swap((*this)[column1][y], (*this)[column2][y]);
		}

		[[nodiscard]] std::string ToString() const
		{
			std::stringstream stream;
			if constexpr (std::is_floating_point<T>::value)
			{
				stream.precision(4);
				stream.flags(std::ios::fixed);
			}

			for (size_t y = 0; y < height; y++)
			{
				for (size_t x = 0; x < width; x++)
				{
					if constexpr (std::is_same<char, T>() || std::is_same<unsigned char, T>())
						stream << +(*this)[x][y];
					else
						stream << (*this)[x][y];
					if (x < width - 1)
						stream << ", ";
				}
				if (y < height - 1)
					stream << std::endl;
			}
			return stream.str();
		}

		[[nodiscard]] static constexpr Matrix<width, height, T> SingleValue(const T& input)
		{
			Matrix<width, height, T> returnMatrix;
			for (size_t i = 0; i < width * height; i++)
				returnMatrix.data[i] = input;
			return returnMatrix;
		}
		[[nodiscard]] static constexpr Matrix<width, height, T> Zero() 
		{
			return Matrix<width, height, T>{};
		}
		[[nodiscard]] static constexpr Matrix<width, height, T> One() 
		{ 
			Matrix<width, height, T> returnMatrix;
			for (size_t i = 0; i < width * height; i++)
				returnMatrix.data[i] = T(1);
			return returnMatrix;
		}

		[[nodiscard]] constexpr Matrix<width, height, T> operator+(const Matrix<width, height, T>& rhs) const
		{
			Matrix<width, height, T> newMatrix;
			for (size_t i = 0; i < width * height; i++)
				newMatrix.data[i] = data[i] + rhs.data[i];
			return newMatrix;
		}
		constexpr Matrix<width, height, T>& operator+=(const Matrix<width, height, T>& rhs)
		{
			for (size_t i = 0; i < width * height; i++)
				data[i] += rhs.data[i];
			return *this;
		}
		[[nodiscard]] constexpr Matrix<width, height, T> operator-(const Matrix<width, height, T>& rhs) const
		{
			Matrix<width, height, T> newMatrix;
			for (size_t i = 0; i < width * height; i++)
				newMatrix.data[i] = data[i] - rhs.data[i];
			return newMatrix;
		}
		constexpr Matrix<width, height, T>& operator-=(const Matrix<width, height, T>& rhs)
		{
			for (size_t i = 0; i < width * height; i++)
				data[i] -= rhs.data[i];
			return *this;
		}
		[[nodiscard]] constexpr Matrix<width, height, T> operator-() const
		{
			Matrix<width, height, T> newMatrix;
			for (size_t i = 0; i < width * height; i++)
				newMatrix.data[i] = -data[i];
			return newMatrix;
		}
		template<size_t widthB>
		[[nodiscard]] constexpr Matrix<widthB, height, T> operator*(const Matrix<widthB, width, T>& right) const
		{
			Matrix<widthB, height, T> newMatrix{};
			for (size_t x = 0; x < widthB; x++)
			{
				for (size_t y = 0; y < height; y++)
				{
					T dot{};
					for (size_t i = 0; i < width; i++)
						dot += (*this)[i][y] * right[x][i];
					newMatrix[x][y] = dot;
				}
			}
			return newMatrix;
		}
		[[nodiscard]] constexpr Vector<height, T> operator*(const Vector<width, T>& right) const
		{
			Vector<height, T> newVector;
			for (size_t y = 0; y < height; y++)
			{
				T dot{};
				for (size_t i = 0; i < width; i++)
					dot += (*this)[i][y] * right[i];
				newVector[y] = dot;
			}
			return newVector;
		}
		constexpr Matrix<width, height, T>& operator*=(const T& right)
		{
			for (size_t i = 0; i < width * height; i++)
				data[i] *= right;
			return *this;
		}
		[[nodiscard]] constexpr bool operator==(const Matrix<width, height, T>& right) const
		{
			for (size_t i = 0; i < width * height; i++)
			{
				if (data[i] != right.data[i])
					return false;
			}
			return true;
		}
		[[nodiscard]] constexpr bool operator!=(const Matrix<width, height, T>& right) const
		{
			for (size_t i = 0; i < width * height; i++)
			{
				if (data[i] != right.data[i])
					return true;
			}
			return false;
		}
		[[nodiscard]] constexpr T* operator[](size_t index)
		{
#if defined( _MSC_VER )
			__assume(index < height);
#endif
			return data.data() + (index * height);
		}
		[[nodiscard]] constexpr const T* operator[](size_t index) const
		{
#if defined( _MSC_VER )
			__assume(index < height);
#endif
			return data.data() + (index * height);
		}
	};

	template<size_t width, size_t height, typename T>
	[[nodiscard]] constexpr auto operator*(const Matrix<width, height, T>& lhs, const T& rhs)
	{
		Matrix<width, height, T> newMatrix;
		for (size_t i = 0; i < width * height; i++)
			newMatrix.data[i] = lhs.data[i] * rhs;
		return newMatrix;
	}

	template<size_t width, size_t height, typename T>
	[[nodiscard]] constexpr auto operator*(const T& left, const Matrix<width, height, T>& right)
	{
		Matrix<width, height, T> newMatrix;
		for (size_t i = 0; i < width * height; i++)
			newMatrix.data[i] = left * right.data[i];
		return newMatrix;
	}
}
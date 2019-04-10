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
		using LengthType = size_t;
		using ValueType = T;
		[[nodiscard]] static constexpr size_t GetWidth();
		[[nodiscard]] static constexpr size_t GetHeight();
		[[nodiscard]] static constexpr size_t GetLinearLength();
		[[nodiscard]] static constexpr bool IsSquare();

		[[nodiscard]] constexpr Matrix<height, width, T> GetTransposed() const;

		constexpr void SwapRows(size_t row1, size_t row2);
		constexpr void SwapColumns(size_t column1, size_t column2);

		[[nodiscard]] std::string ToString() const;

		[[nodiscard]] static constexpr Matrix<width, height, T> SingleValue(const T& input);
		[[nodiscard]] static constexpr Matrix<width, height, T> Zero();
		[[nodiscard]] static constexpr Matrix<width, height, T> One();

		constexpr T& Front();
		constexpr const T& Front() const;
		constexpr T& Back();
		constexpr const T& Back() const;
		constexpr T* Data();
		constexpr const T* Data() const;

		template<typename U>
		[[nodiscard]] constexpr auto operator+(const Matrix<width, height, U>& right) const;
		template<typename U>
		constexpr Matrix<width, height, T>& operator+=(const Matrix<width, height, U>& right);
		template<typename U>
		[[nodiscard]] constexpr auto operator-(const Matrix<width, height, U>& right) const;
		template<typename U>
		constexpr Matrix<width, height, T>& operator-=(const Matrix<width, height, U>& right);
		[[nodiscard]] constexpr auto operator-() const;
		template<size_t widthB, typename U>
		[[nodiscard]] constexpr auto operator*(const Matrix<widthB, width, U>& right) const;
		template<typename U>
		[[nodiscard]] constexpr auto operator*(const Vector<width, U>& right) const;
		constexpr Matrix<width, height, T>& operator*=(const T& right);
		template<typename U>
		[[nodiscard]] constexpr bool operator==(const Matrix<width, height, U>& right) const;
		template<typename U>
		[[nodiscard]] constexpr bool operator!=(const Matrix<width, height, U>& right) const;
	};

	template<size_t width, size_t height, typename T>
	constexpr size_t Matrix<width, height, T>::GetWidth() { return width; }

	template<size_t width, size_t height, typename T>
	constexpr size_t Matrix<width, height, T>::GetHeight() { return height; }

	template<size_t width, size_t height, typename T>
	constexpr size_t Matrix<width, height, T>::GetLinearLength() { return width * height; }

	template<size_t width, size_t height, typename T>
	constexpr bool Matrix<width, height, T>::IsSquare() { return width == height; }

	template<size_t width, size_t height, typename T>
	constexpr Matrix<height, width, T> Matrix<width, height, T>::GetTransposed() const
	{
		Matrix<height, width, T> temp{};
		for (size_t x = 0; x < width; x++)
		{
			for (size_t y = 0; y < height; y++)
				temp[x][y] = (*this)[y][x];
		}
		return temp;
	}

	template<size_t width, size_t height, typename T>
	constexpr void Matrix<width, height, T>::SwapRows(size_t row1, size_t row2)
	{
		for (size_t x = 0; x < width; x++)
			std::swap((*this)[x][row1], (*this)[x][row2]);
	}

	template<size_t width, size_t height, typename T>
	constexpr void Matrix<width, height, T>::SwapColumns(size_t column1, size_t column2)
	{
		for (size_t y = 0; y < height; y++)
			std::swap((*this)[column1][y], (*this)[column2][y]);
	}

	template<size_t width, size_t height, typename T>
	std::string Matrix<width, height, T>::ToString() const
	{
		std::stringstream stream;
		stream.precision(4);
		stream.flags(std::ios::fixed);
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

	template<size_t width, size_t height, typename T>
	constexpr Matrix<width, height, T> Matrix<width, height, T>::SingleValue(const T& input)
	{
		Matrix<width, height, T> returnMatrix{};
		for (auto& item : returnMatrix)
			item = input;
		return returnMatrix;
	}

	template<size_t width, size_t height, typename T>
	constexpr Matrix<width, height, T> Matrix<width, height, T>::Zero() { return Matrix<width, height, T>::SingleValue(T()); }

	template<size_t width, size_t height, typename T>
	constexpr Matrix<width, height, T> Matrix<width, height, T>::One() { return Matrix<width, height, T>::SingleValue(T(1)); }

	template<size_t width, size_t height, typename T>
	constexpr T& Matrix<width, height, T>::Front() { return this->data.front(); }

	template<size_t width, size_t height, typename T>
	constexpr const T & Matrix<width, height, T>::Front() const { return this->data.front(); }

	template<size_t width, size_t height, typename T>
	constexpr T& Matrix<width, height, T>::Back() { return this->data.back(); }

	template<size_t width, size_t height, typename T>
	constexpr const T& Matrix<width, height, T>::Back() const { return this->data.back(); }

	template<size_t width, size_t height, typename T>
	constexpr T* Matrix<width, height, T>::Data() { return this->data.data(); }

	template<size_t width, size_t height, typename T>
	constexpr const T* Matrix<width, height, T>::Data() const { return this->data.data(); }

	template<size_t width, size_t height, typename T>
	template<typename U>
	constexpr auto Matrix<width, height, T>::operator+(const Matrix<width, height, U>& right) const
	{
		using ReturnType = decltype(this->At(0) + right.At(0));
		Matrix<width, height, ReturnType> newMatrix{};
		for (size_t i = 0; i < width * height; i++)
			newMatrix.At(i) = this->At(i) + right.At(i);
		return newMatrix;
	}

	template<size_t width, size_t height, typename T>
	template<typename U>
	constexpr Matrix<width, height, T>& Matrix<width, height, T>::operator+=(const Matrix<width, height, U>& right)
	{
		for (size_t i = 0; i < width * height; i++)
			this->At(i) += right.At(i);
		return *this;
	}

	template<size_t width, size_t height, typename T>
	template<typename U>
	constexpr auto Matrix<width, height, T>::operator-(const Matrix<width, height, U>& right) const
	{
		using ReturnType = decltype(this->At(0) - right.At(0));
		Matrix<width, height, ReturnType> newMatrix{};
		for (size_t i = 0; i < width * height; i++)
			newMatrix.At(i) = this->At(i) - right.At(i);
		return newMatrix;
	}

	template<size_t width, size_t height, typename T>
	template<typename T2>
	constexpr Matrix<width, height, T>& Matrix<width, height, T>::operator-=(const Matrix<width, height, T2>& right)
	{
		for (size_t i = 0; i < width * height; i++)
			this->At(i) -= right.At(i);
		return *this;
	}

	template<size_t width, size_t height, typename T>
	constexpr auto Matrix<width, height, T>::operator-() const
	{
		constexpr bool unsignedTest = std::is_unsigned_v<T>;
		using ReturnType = std::conditional_t<unsignedTest, std::make_signed_t<T>, T>;
		Matrix<width, height, ReturnType> newMatrix{};
		for (size_t i = 0; i < width * height; i++)
		{
			if constexpr (unsignedTest)
				newMatrix.At(i) = -static_cast<ReturnType>(this->At(i));
			else
				newMatrix.At(i) = -this->At(i);
		}
		return newMatrix;
	}

	template<size_t width, size_t height, typename T>
	template<size_t widthB, typename U>
	constexpr auto Matrix<width, height, T>::operator*(const Matrix<widthB, width, U>& right) const
	{
		using ReturnType = std::common_type_t<T, U>;
		Matrix<widthB, height, ReturnType> newMatrix{};
		for (size_t x = 0; x < widthB; x++)
		{
			for (size_t y = 0; y < height; y++)
			{
				ReturnType dot{};
				for (size_t i = 0; i < width; i++)
					dot += (*this)[i][y] * right[x][i];
				newMatrix[x][y] = dot;
			}
		}
		return newMatrix;
	}

	template<size_t width, size_t height, typename T>
	template<typename U>
	constexpr auto Matrix<width, height, T>::operator*(const Vector<width, U>& right) const
	{
		using ReturnType = std::common_type_t<T, U>;
		Math::Vector<height, ReturnType> newVector;
		for (size_t y = 0; y < height; y++)
		{
			ReturnType dot = 0;
			for (size_t i = 0; i < width; i++)
				dot += (*this)[i][y] * right[i];
			newVector[y] = dot;
		}
		return newVector;
	}

	template<size_t width, size_t height, typename T, typename U>
	[[nodiscard]] constexpr auto operator*(const Matrix<width, height, T>& left, const U& right)
	{
		using ReturnType = decltype(left.At(0) * right);
		Matrix<width, height, ReturnType> newMatrix;
		for (size_t i = 0; i < width * height; i++)
			newMatrix.At(i) = left.At(i) * right;
		return newMatrix;
	}

	template<size_t width, size_t height, typename T, typename U>
	[[nodiscard]] constexpr auto operator*(const U& left, const Matrix<width, height, T>& right)
	{
		using ReturnType = decltype(left * right.At(0));
		Matrix<width, height, ReturnType> newMatrix{};
		for (size_t i = 0; i < width * height; i++)
			newMatrix.At(i) = left * right.At(i);
		return newMatrix;
	}

	template<size_t width, size_t height, typename T>
	constexpr Matrix<width, height, T>& Matrix<width, height, T>::operator*=(const T& right)
	{
		for (auto& item : *this)
			item *= right;
		return *this;
	}

	template<size_t width, size_t height, typename T>
	template<typename T2>
	constexpr bool Matrix<width, height, T>::operator==(const Matrix<width, height, T2>& right) const
	{
		for (size_t i = 0; i < width * height; i++)
		{
			if (this->At(i) != right.At(i))
				return false;
		}
		return true;
	}

	template<size_t width, size_t height, typename T>
	template<typename T2>
	constexpr bool Matrix<width, height, T>::operator!=(const Matrix<width, height, T2>& right) const
	{
		return !((*this) == right);
	}
}
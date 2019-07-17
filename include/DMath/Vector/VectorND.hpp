#pragma once

#include "Core.hpp"

#include <array>

namespace Math
{
	template<size_t length, typename T>
	struct Vector;

	template<size_t length, typename T = float>
	struct Vector
	{
		using ValueType = T;
		using IteratorType = Iterators::VectorIterator<4, T>;
		using ConstIteratorType = Iterators::VectorConstIterator<4, T>;
		static constexpr size_t dimCount = length;

		std::array<T, length> data;

		[[nodiscard]] constexpr T& At(size_t index)
		{
#if defined( _MSC_VER )
			__assume(index < dimCount);
#endif
			return const_cast<T&>(std::as_const(*this).At(index));
		}

		[[nodiscard]] constexpr const T& At(size_t index) const
		{
#if defined( _MSC_VER )
			__assume(index < dimCount);
#endif
			assert(index < dimCount);
			return data.at(index);
		}

		[[nodiscard]] static constexpr T Dot(const Vector<length, T>& lhs, const Vector<length, T>& rhs)
		{
			T sum = T(0);
			for (size_t i = 0; i < length; i++)
				sum += lhs[i] * rhs[i];
		}

		[[nodiscard]] constexpr T* GetData()
		{
			return data.data();
		}

		[[nodiscard]] constexpr const T* GetData() const
		{
			return data.data();
		}

		[[nodiscard]] auto GetNormalized() const -> Vector<length, typename std::conditional<std::is_integral<T>::value, float, T>::type>
		{
			using ReturnValueType = typename std::conditional<std::is_integral<T>::value, float, T>::type;
			const auto& magnitude = Magnitude();
			Vector<length, ReturnValueType> temp;
			for (size_t i = 0; i < length; i++)
				temp[i] = data[i] / magnitude;
			return temp;
		}

		[[nodiscard]] auto Magnitude() const -> typename std::conditional<std::is_integral<T>::value, float, T>::type
		{
			if constexpr (std::is_integral<T>::value)
			{
				T sumSqrd = T(0);
				for (size_t i = 0; i < length; i++)
				{
					const T& temp = data[i];
					sumSqrd = temp * temp;
				}
				return Sqrt(float(sumSqrd));
			}
			else
			{
				T sumSqrd = T(0);
				for (size_t i = 0; i < length; i++)
				{
					const T& temp = data[i];
					sumSqrd = temp * temp;
				}
				return Sqrt(sumSqrd);
			}
		}

		[[nodiscard]] constexpr T MagnitudeSqrd() const
		{
			T sumSqrd = T(0);
			for (size_t i = 0; i < length; i++)
			{
				const T& temp = data[i];
				sumSqrd = temp * temp;
			}
			return sumSqrd;
		}

		void Normalize()
		{
			static_assert(std::is_floating_point<T>::value, "Cannot normalize an integral vector.");
			const auto& magnitude = Magnitude();
			for (size_t i = 0; i < length; i++)
				data[i] /= magnitude;
		}

		[[nodiscard]] std::string ToString() const
		{
			std::ostringstream stream;

			if constexpr (std::is_floating_point<T>::value)
			{
				stream.flags(std::ios::fixed);
				stream.precision(4);
			}

			stream << '(';
			for (size_t i = 0; i < length; i++)
			{
				if constexpr (std::is_same<char, T>::value || std::is_same<unsigned char, T>::value)
					stream << +data[i];
				else
					stream << data[i];

				if (i < length - 1)
					stream << ", ";
			}
			stream << ')';
			return stream.str();
		}

		[[nodiscard]] static constexpr Vector<length, T> SingleValue(const T& input)
		{
			Vector<length, T> temp;
			for (size_t i = 0; i < length; i++)
				data[i] = input;
			return temp;
		}
		[[nodiscard]] static constexpr Vector<length, T> Zero()
		{
			return Vector<length, T>{};
		}
		[[nodiscard]] static constexpr Vector<length, T> One()
		{
			Vector<length, T> temp;
			for (size_t i = 0; i < length; i++)
				data[i] = T(1);
			return temp;
		}

		constexpr Vector<length, T>& operator+=(const Vector<length, T>& rhs)
		{
			for (size_t i = 0; i < length; i++)
				data[i] += rhs[i];
			return *this;
		}
		constexpr Vector<4, T>& operator-=(const Vector<4, T>& rhs)
		{
			for (size_t i = 0; i < length; i++)
				data[i] -= rhs[i];
			return *this;
		}
		constexpr Vector<4, T>& operator*=(const T& rhs)
		{
			for (size_t i = 0; i < length; i++)
				data[i] *= rhs;
			return *this;
		}
		[[nodiscard]] constexpr Vector<length, T> operator+(const Vector<length, T>& rhs) const
		{
			Vector<length, T> returnValue;
			for (size_t i = 0; i < length; i++)
				returnValue[i] = data[i] + rhs[i];
			return returnValue;
		}
		[[nodiscard]] constexpr Vector<length, T> operator-(const Vector<length, T>& rhs) const
		{
			Vector<length, T> returnValue;
			for (size_t i = 0; i < length; i++)
				returnValue[i] = data[i] - rhs[i];
			return returnValue;
		}
		[[nodiscard]] constexpr Vector<length, T> operator-() const
		{
			Vector<length, T> returnValue;
			for (size_t i = 0; i < length; i++)
				returnValue[i] = -data[i];
			return returnValue;
		}
		[[nodiscard]] constexpr bool operator==(const Vector<length, T>& rhs) const
		{
			for (size_t i = 0; i < length; i++)
			{
				if (data[i] != rhs[i])
					return false;
			}
			return true;
		}
		[[nodiscard]] constexpr bool operator!=(const Vector<length, T>& rhs) const
		{
			for (size_t i = 0; i < length; i++)
			{
				if (data[i] != rhs[i])
					return true;
			}
			return false;
		}
		[[nodiscard]] constexpr T& operator[](size_t index)
		{
#if defined( _MSC_VER )
			__assume(index < dimCount);
#endif
			return const_cast<T&>(std::as_const(*this)[index]);
		}
		[[nodiscard]] constexpr const T& operator[](size_t index) const
		{
#if defined( _MSC_VER )
			__assume(index < dimCount);
#endif
			assert(index < dimCount);
			return data[index];
		}
		template<typename U>
		[[nodiscard]] constexpr explicit operator Vector<length, U>() const
		{
			static_assert(std::is_convertible<T, U>::value, "Can't convert to this type.");
			
			Vector<length, U> returnValue;
			for (size_t i = 0; i < length; i++)
				returnValue[i] = static_cast<U>(data[i]);
			return returnValue;
		}
	};

	template<size_t length, typename T>
	constexpr Vector<length, T> operator*(const Vector<length, T>& lhs, const T& rhs)
	{
		Vector<length, T> returnValue;
		for (size_t i = 0; i < length; i++)
			returnValue[i] = lhs.data[i] * rhs;
		return returnValue;
	}

	template<size_t length, typename T>
	constexpr Vector<length, T> operator*(const T& lhs, const Vector<length, T>& rhs)
	{
		Vector<length, T> returnValue;
		for (size_t i = 0; i < length; i++)
			returnValue[i] = lhs * rhs.data[i];
		return returnValue;
	}
}
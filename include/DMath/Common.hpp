#pragma once

#include <cmath>
#include <algorithm>

#include <type_traits>

namespace Math
{
	template<typename T>
	[[nodiscard]] auto Abs(T input)
	{
		static_assert(std::is_arithmetic_v<T>, "Input of Math::Abs must be of numeric type.");
		return std::abs(input);
	}
	
	template<typename T>
	[[nodiscard]] auto Ceil(T input)
	{
		static_assert(std::is_arithmetic_v<T>, "Input of Math::Ceil must be of numeric type.");
		return std::ceil(input);
	}

	template<typename T>
	[[nodiscard]] auto CeilToNearestMultiple(T value, T multiple)
	{
		static_assert(std::is_integral_v<T> && std::is_unsigned_v<T>, "Input of Math::CeilToNearestMultiple must be of unsigned integral type.");
		if (value > multiple)
			return value - (value % multiple);
		else
			return value + multiple - (value % multiple);
	}

	template<typename T>
	[[nodiscard]] constexpr T Clamp(T value, T min, T max)
	{
		static_assert(std::is_arithmetic_v<T>, "Input of Math::Clamp must be of numeric type.");
		return std::clamp(value, min, max);
	}

	template<typename T>
	[[nodiscard]] auto Floor(T input)
	{
		static_assert(std::is_arithmetic_v<T>, "Input of Math::Floor must be of numeric type.");
		return std::floor(input);
	}

	template<typename T>
	[[nodiscard]] auto Hypot(T x, T y)
	{
		return std::hypot(x, y);
	}

	template<typename T>
	[[nodiscard]] auto Hypot(T x, T y, T z)
	{
		return std::hypot(x, y, z);
	}

	template<typename T1, typename T2, typename T3>
	[[nodiscard]] constexpr auto Lerp(T1 input1, T2 input2, T3 delta)
	{
		static_assert(std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2> && std::is_arithmetic_v<T3>, "Input of Math::Lerp must be of numeric type.");
		using ReturnType = std::common_type_t<T1, T2, T3>;
		if constexpr (std::is_same_v<ReturnType, decltype((input2 - input1) * delta + input1)>)
			return (input2 - input1) * delta + input1;
		else
			return static_cast<std::make_signed_t<ReturnType>>((input2 - input1) * delta + input1);
	}

	template<typename T, typename U>
	[[nodiscard]] constexpr auto Min(T a, U b)
	{
		static_assert(std::is_arithmetic<T>() && std::is_arithmetic<U>(), "Error. Template arguments of Math::Min must be arithmetic types.");
		using CommonType = typename std::common_type_t<T, U>;
		return std::min(static_cast<CommonType>(a), static_cast<CommonType>(b));
	}

	template<typename T, typename U>
	[[nodiscard]] constexpr auto Max(T a, U b)
	{
		static_assert(std::is_arithmetic<T>() && std::is_arithmetic<U>(), "Error. Template arguments of Math::Min must be arithmetic types.");
		using CommonType = typename std::common_type_t<T, U>;
		return std::max(static_cast<CommonType>(a), static_cast<CommonType>(b));
	}

	template<typename T1, typename T2>
	[[nodiscard]] auto Pow(T1 coefficient, T2 exponent)
	{
		static_assert(std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2>, "Input of Math::Pow must be of numeric type.");
		return std::pow(coefficient, exponent);
	}

	template<typename T>
	[[nodiscard]] auto Round(T input)
	{
		static_assert(std::is_arithmetic_v<T>, "Input of Math::Round must be of numeric type.");
		return std::round(input);
	}

	template<typename T>
	[[nodiscard]] constexpr auto Sqrd(T input)
	{
		static_assert(std::is_arithmetic_v<T>, "Input of Math::Sqrd must be of numeric type.");
		return input * input;
	}

	template<typename T>
	[[nodiscard]] auto Sqrt(T input)
	{
		static_assert(std::is_arithmetic_v<T>, "Input of Math::Sqrt must be of numeric type.");
		return std::sqrt(input);
	}

	template<typename T>
	[[nodiscard]] auto Truncate(T input)
	{
		static_assert(std::is_arithmetic_v<T>, "Input of Math::Truncate must be of numeric type.");
		return std::trunc(input);
	}
}
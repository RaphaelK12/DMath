#pragma once

#include "MatrixBase.hpp"
#include "../Trait.hpp"

#include <initializer_list>
#include <optional>

namespace Math
{
	template<size_t width, size_t height, typename T>
	struct Matrix;

	namespace detail
	{
		template<size_t width, size_t height, typename T>
		struct MatrixBase;

		template<size_t width, typename T>
		struct MatrixBaseSquare : public MatrixBase<width, width, T>
		{
		public:
			using ParentType = MatrixBase<width, width, T>;

			[[nodiscard]] constexpr Math::Matrix<width, width, T> GetAdjugate() const
			{
				Math::Matrix<width, width, T> newMatrix;
				for (size_t x = 0; x < width; x++)
				{
					int8_t factor = (!(x % 2)) * 2 - 1;
					for (size_t y = 0; y < width; y++)
					{
						newMatrix[y][x] = factor * this->GetMinor(x, y).GetDeterminant();
						factor = -factor;
					}
				}
				return newMatrix;
			}

			[[nodiscard]] constexpr T GetDeterminant() const
			{
				if constexpr (width >= 3)
				{
					T determinant = T();
					int8_t factor = -1;
					for (size_t x = 0; x < width; x++)
					{
						factor = -factor;
						if (data[x * width] == T(0))
							continue;
						determinant += factor * data[x * width] * GetMinor(x, 0).GetDeterminant();
					}
					return determinant;
				}
				else if constexpr (width == 2)
					return data[0] * data[height + 1] - data[height] * data[1];
				else if constexpr (width == 1)
					return data[0];
				else
					return 1;
			}

			[[nodiscard]] constexpr std::optional<Math::Matrix<width, width, T>> GetInverse() const
			{
				const Math::Matrix<width, width, T> adjugate = GetAdjugate();
				T determinant = T();
				for (size_t x = 0; x < width; x++)
					determinant += data[x * width] * adjugate[0][x];
				if (!(determinant == T()))
				{
					for (size_t i = 0; i < width * width; i++)
						adjugate.data[i] /= determinant;
					return adjugate;
				}
				else
					return {};
			}

			constexpr void Transpose()
			{
				for (size_t x = 1; x < width; x++)
				{
					for (size_t y = 0; y < x; y++)
						std::swap(data[x * width + y], data[y * width + x]);
				}
			}

			[[nodiscard]] static constexpr Math::Matrix<width, width, T> Identity()
			{
				Math::Matrix<width, width, T> temp{};
				for (size_t x = 0; x < width; x++)
					temp.data[x * width + x] = T(1);
				return temp;
			}

			[[nodiscard]] constexpr bool IsSingular() const
			{
				return GetDeterminant() == T(0);
			}
		};
	}
}
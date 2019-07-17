#pragma once

#include "../Trait.hpp"

#include <string>
#include <type_traits>
#include <initializer_list>
#include <iterator>
#include <array>
#include <cassert>

namespace Math
{
	template<size_t width, size_t height, typename T>
	struct Matrix;

	namespace detail
	{
		template<size_t width, size_t height, typename T>
		struct MatrixBase
		{
		public:
			static constexpr bool isColumnMajor = true;

			std::array<T, width * height> data;

			[[nodiscard]] constexpr Math::Matrix<width - 1, height - 1, T> GetMinor(size_t columnIndexToSlice, size_t rowIndexToSlice) const
			{
#if defined( _MSC_VER )
				__assume(columnIndexToSlice < width && rowIndexToSlice < height);
#endif
				assert(columnIndexToSlice < width && rowIndexToSlice < height);

				Math::Matrix<width - 1, height - 1, T> newMatrix;
				for (size_t x = 0; x < width; x++)
				{
					if (x == columnIndexToSlice)
						continue;

					for (size_t y = 0; y < height; y++)
					{
						if (y == rowIndexToSlice)
							continue;

						newMatrix[x < columnIndexToSlice ? x : x - 1][y < rowIndexToSlice ? y : y - 1] = data[x * height + y];
					}
				}
				return newMatrix;
			}
		};
	}
}
#pragma once

#include "../Common.hpp"
#include "../Matrix/Matrix.hpp"
#include "../Vector/Vector.hpp"

#include <array>
#include <cassert>
#include <initializer_list>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

namespace Math
{
	template<size_t length, typename T>
	struct Vector;

	namespace Iterators
	{
		template<size_t length, typename T>
		class VectorIterator
		{
		private:
			static_assert(length > 0, "Length must be non-zero.");

			Vector<length, T>& obj;
			size_t index;

		public:
			constexpr VectorIterator(Vector<length, T>& obj, size_t index) :
				obj(obj),
				index(index)
			{
				if (index > length)
					index = length;
			}

			static constexpr VectorIterator<length, T> Begin(Vector<length, T>& obj)
			{
				return VectorIterator<length, T>{ obj, 0 };
			}

			static constexpr VectorIterator<length, T> ReverseBegin(Vector<length, T>& obj)
			{
				return VectorIterator<length, T>{ obj, length - 1 };
			}

			static constexpr VectorIterator<length, T> End(Vector<length, T>& obj) 
			{
				return VectorIterator<length, T>{ obj, length };
			}

			[[nodiscard]] constexpr T& operator*() const
			{
				assert(index < length);
				return obj[index];
			}
			constexpr VectorIterator<length, T>& operator++()
			{
				if (index < length)
					index++;
				return *this;
			}
			constexpr VectorIterator<length, T> operator++(int)
			{
				VectorIterator<length, T> old = *this;
				if (index < length)
					index++;
				return old;
			}
			constexpr VectorIterator<length, T>& operator--() 
			{
				if (index == 0)
					index = length;
				else
					index--;
				return *this; 
			}
			constexpr VectorIterator<length, T> operator--(int)
			{
				VectorIterator<length, T> old = *this;
				if (index == 0)
					index = length;
				else
					index--;
				return old;
			}
			constexpr bool operator==(const VectorIterator<length, T>& right) const 
			{ 
				return &obj == &right.obj && index == right.index; 
			}
			constexpr bool operator!=(const VectorIterator<length, T>& right) const 
			{
				return &obj != &right.obj || index != right.index; 
			}
		};

		template<size_t length, typename T>
		class VectorConstIterator
		{
		private:
			static_assert(length > 0, "Length must be non-zero.");

			const Vector<length, T>& obj;
			size_t index;

		public:
			constexpr VectorConstIterator(const Vector<length, T>& obj, size_t index) :
				obj(obj),
				index(index)
			{
				if (index > length)
					index = length;
			}

			static constexpr VectorConstIterator<length, T> Begin(const Vector<length, T>& obj)
			{
				return VectorConstIterator<length, T>{ obj, 0 };
			}

			static constexpr VectorConstIterator<length, T> ReverseBegin(const Vector<length, T>& obj)
			{
				return VectorConstIterator<length, T>{ obj, length - 1 };
			}

			static constexpr VectorConstIterator<length, T> End(const Vector<length, T>& obj)
			{
				return VectorConstIterator<length, T>{ obj, length };
			}

			[[nodiscard]] constexpr const T& operator*() const
			{
				assert(index < length);
				return obj[index];
			}
			constexpr VectorConstIterator<length, T>& operator++()
			{
				if (index < length)
					index++;
				return *this;
			}
			constexpr VectorConstIterator<length, T> operator++(int)
			{
				VectorConstIterator<length, T> old = *this;
				if (index < length)
					index++;
				return old;
			}
			constexpr VectorConstIterator<length, T>& operator--()
			{
				if (index == 0)
					index = length;
				else
					index--;
				return *this;
			}
			constexpr VectorConstIterator<length, T> operator--(int)
			{
				VectorConstIterator<length, T> old = *this;
				if (index == 0)
					index = length;
				else
					index--;
				return old;
			}
			constexpr bool operator==(const VectorConstIterator<length, T>& right) const
			{
				return &obj == &right.obj && index == right.index;
			}
			constexpr bool operator!=(const VectorConstIterator<length, T>& right) const
			{
				return &obj != &right.obj || index != right.index;
			}
		};
	}
}
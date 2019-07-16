#include "DMath/Vector/Vector.hpp"

Math::Vector<2, double> Test(size_t count)
{
	Math::Vector<2, double> a;

	Math::Vector<2, double> b;

	Math::Vector<2, double> c;

	for (size_t i = 0; i < count; i++)
		c = a + b;

	return c;
}
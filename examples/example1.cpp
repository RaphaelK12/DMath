#include "DMath/Vector/Vector.hpp"
#include "DMath/Matrix/Matrix.hpp"

#include <chrono>
#include <iostream>

int main()
{
	Math::Vector<2, double> a{ 5.555555, 6.555555 };

	const Math::Vector<2, int> b{ 5, 6 };

	const Math::Vector<3, float> c;

	Math::Matrix4x4 d;

	Math::Matrix4x4 e;

	auto f = d + e;

	for (auto i = a.crbegin(); i != a.cend(); i--)
	{
		std::cout << *i << std::endl;
	}
}
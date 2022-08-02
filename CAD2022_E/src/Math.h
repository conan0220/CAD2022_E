#pragma once

#include <cmath>

namespace math
{
	const float pi = 3.141592653589793238462643383279502884;

	float Rounding(float num, const int& index);

	int BinarySearch(int* list, int listSize, int target, int low, int high);
}

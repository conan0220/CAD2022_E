#include "Math.h"

namespace math
{
    float Rounding(float num, const int& index)
    {
        bool isNegative = false; // whether is negative number or not
        if (num < 0) // if this number is negative, then convert to positive number
        {
            isNegative = true;
            num *= -1;
        }
        if (index >= 0)
        {
            int multiplier;
            multiplier = pow(10, index);
            num = (int)(num * multiplier + 0.5) / (multiplier * 1.0);
        }
        if (isNegative) // if this number is negative, then convert to negative number
            num *= -1;
        return num;
    }

    int BinarySearch(int* list, int listSize, int target, int low, int high)
    {
        int num = 0;
        while (true)
        {
            num = (low + high) / 2;
            listSize = high - low + 1;
            if (listSize == 0)
                return -1;
            if (list[num] == target)
                return num;
            else if (list[num] > target)
                high = num - 1;
            else if (list[num] < target)
                low = num + 1;
        }
        return -1;
    }
}

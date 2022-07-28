#include "Math.h"

void rounding(float& num, const int& index)
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
}

float _rounding(float num, const int& index)
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
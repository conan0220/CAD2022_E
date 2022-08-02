#include "Arc.h"

void Arc::CalculateAngle()
{
    this->angle = CalculateArcAngle(startAngle, endAngle);
    if (n1.x == n2.x && n1.y == n2.y)
    {
        this->angle = 2 * math::pi;
    }
}

void Arc::CalArea()
{
    float temp = math::pi * radius * radius;
    this->area = temp * (angle / (2 * math::pi));
}

float Arc::CalculateAngle(const Node& center, const Node& n)
{
    float x = n.x - center.x;
    float y = n.y - center.y;
    float z = sqrt(x * x + y * y);
    float angle = math::Rounding(asinf(abs(y) / z), 4);

    if (angle == 0 && x == 0)
        angle = math::Rounding(math::pi / 2, 4);

    if (x >= 0 && y >= 0)             // first quadrant
        angle = angle;
    else if (x < 0 && y >= 0)         // second quadrant
        angle = math::pi - angle;
    else if (x < 0 && y < 0)         // third quadrant
        angle += math::pi;
    else if (x >= 0 && y < 0)        // forth quadrant
        angle = 2 * math::pi - angle;

    return angle;
}

float Arc::CalculateArcAngle(const float startAngle, const float endAngle)
{
    float angle = abs(endAngle - startAngle);

    if (angle <= 2 * math::pi - angle)
        return angle;
    else
        return 2 * math::pi - angle;
}
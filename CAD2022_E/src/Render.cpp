#include "Render.h"
#include "Math.h"

#include <iostream>

float& GetScaling() { return scaling; }

float& GetXDisplacement() { return xDisplacement; }

float& GetYDisplacement() { return yDisplacement; }

void RenderLine(const Node& n1, const Node& n2)
{
    glBegin(GL_LINES);
    glVertex2f((n1.x + xDisplacement) * scaling, (n1.y + yDisplacement) * scaling);
    glVertex2f((n2.x + xDisplacement) * scaling, (n2.y + yDisplacement) * scaling);
    glEnd();
}

void RenderArc(const Node& center, float r, float startAngle, float endAngle, bool direction, int numSegments)
{
    float arcAngle = CalArcAngle(startAngle, endAngle);
    if (direction)
    {
        startAngle = endAngle;
        arcAngle = 2 * pi - arcAngle;
    }
    
    float theta = arcAngle / float(numSegments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open

    float tangetial_factor = tanf(theta);

    float radial_factor = cosf(theta);


    float x = r * cosf(startAngle);//we now start at the start angle
    float y = r * sinf(startAngle);

    glBegin(GL_LINE_STRIP);//since the arc is not a closed curve, this is a strip now
    for (int ii = 0; ii < numSegments; ii++)
    {
        glVertex2f((x + center.x + xDisplacement) * scaling, (y + center.y + yDisplacement) * scaling);

        float tx = -y;
        float ty = x;

        x += tx * tangetial_factor;
        y += ty * tangetial_factor;

        x *= radial_factor;
        y *= radial_factor;
    }
    glEnd();
}

float CalculateAngle(const Node& center, const Node& n)
{
    float x = n.x - center.x;
    float y = n.y - center.y;
    float z = sqrt(x * x + y * y);
    float angle = _rounding(asinf(abs(y) / z), 4);
    
    if (angle == 0 && x == 0)
        angle = _rounding(pi / 2, 4);

    if (x >= 0 && y >= 0)             // first quadrant
        angle = angle;
    else if (x < 0 && y >= 0)        // second quadrant
        angle = pi - angle;
    else if (x < 0 && y < 0)        // third quadrant
        angle += 180;
    else if (x >= 0 && y < 0)        // forth quadrant
        angle = 2 * pi - angle;

    return angle;
}

float CalArcAngle(const float startAngle, const float endAngle)
{
    float angle = abs(endAngle - startAngle);
    if (angle <= 2 * pi - angle)
        return angle;
    else
        return 2 * pi - angle;
}

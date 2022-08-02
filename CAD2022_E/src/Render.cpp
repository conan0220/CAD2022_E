#include "Render.h"
#include "Math.h"
#include "Camera.h"

#include <iostream>

void RenderPoint(const Node& n)
{
    glBegin(GL_POINTS);
    glVertex2f((n.x - Camera::x) * Camera::scaling, (n.y - Camera::y) * Camera::scaling);
    glEnd();
}

void RenderLine(const Node& n1, const Node& n2)
{
    glBegin(GL_LINES);
    glVertex2f((n1.x - Camera::x) * Camera::scaling, (n1.y - Camera::y) * Camera::scaling);
    glVertex2f((n2.x - Camera::x) * Camera::scaling, (n2.y - Camera::y) * Camera::scaling);
    glEnd();
}

void RenderArc(const Arc& arc, int numSegments)
{
    float startAngle = arc.startAngle;
    if (arc.direction)
    {
        startAngle = arc.endAngle;
    }

    float theta = arc.angle / float(numSegments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open

    float tangetial_factor = tanf(theta);

    float radial_factor = cosf(theta);


    float x = arc.radius * cosf(startAngle);//we now start at the start angle
    float y = arc.radius * sinf(startAngle);

    glBegin(GL_LINE_STRIP);//since the arc is not a closed curve, this is a strip now
    for (int ii = 0; ii < numSegments; ii++)
    {
        glVertex2f((x + arc.center.x - Camera::x) * Camera::scaling, (y + arc.center.y - Camera::y) * Camera::scaling);

        float tx = -y;
        float ty = x;

        x += tx * tangetial_factor;
        y += ty * tangetial_factor;

        x *= radial_factor;
        y *= radial_factor;
    }
    glEnd();
}

void RenderText(const std::string text, const float x, const float y)
{

}




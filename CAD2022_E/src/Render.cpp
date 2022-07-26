#include "Render.h"

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
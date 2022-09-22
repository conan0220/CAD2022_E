#include "Base.h"

float Base::assemblygap = 0;
float Base::coppergap = 0;
float Base::silkscreenlen = 0;

void Base::operator += (const Line& line)
{
	lines += line;
}

void Base::operator += (const Arc& arc)
{
	arcs += arc;
}

float Base::CalculateDeterminant(const Node& n1, const Node& n2) const
{
	return n1.x * n2.y - n1.y * n2.x;
}






#pragma once

#include "Node.h"
#include "Math.h"

struct Arc
{
	// constructor
	Arc() {}
	// direction: Clockwise --> true | Counterclockwise --> false
	Arc(const Node& n1, const Node& n2, const Node& center, const bool direction)	
		: n1(n1), n2(n2), center(center), direction(direction) 
	{
		this->radius = sqrt(pow(n1.x - center.x, 2.0f) + pow(n1.y - center.y, 2.0f));
		rounding(this->radius, 4);
	}

	// data
	Node n1;
	Node n2;
	Node center;
	bool direction = true;
	float radius = 0;
};
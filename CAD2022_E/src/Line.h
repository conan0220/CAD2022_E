#pragma once

#include "Node.h"
#include "Math.h"

struct Line
{
	// constructor
	Line() {}
	Line(const Node& n1, const Node& n2)
		: n1(n1), n2(n2) 
	{
		this->length = sqrt(pow(n1.x - n2.x, 2.0f) + pow(n1.y - n2.y, 2.0f));
	}

	// data
	Node n1;
	Node n2;
	float length = 0;
};
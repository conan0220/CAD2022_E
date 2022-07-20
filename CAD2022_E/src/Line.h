#pragma once

#include "Node.h"

#include <iostream>

struct Line
{
	// constructor
	Line() {}
	Line(const Node& n1, const Node& n2)
		: n1(n1), n2(n2) 
	{
		SetDistance();
	}

	// function
	void SetDistance() 
	{
		length = std::sqrt(std::pow(n1.x - n2.x, 2.0f) + std::pow(n1.y - n2.y, 2.0f));
	}
	/*inline const Node& GetN1()
	{
		return n1;
	}
	inline const Node& GetN2()
	{
		return n2;
	}*/

	// data
	Node n1;
	Node n2;
	float length = 0;
};
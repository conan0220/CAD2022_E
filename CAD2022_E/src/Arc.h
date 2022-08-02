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
		math::Rounding(this->radius, 4);
		this->startAngle = CalculateAngle(center, n1);
		this->endAngle = CalculateAngle(center, n2);
		CalculateAngle();
		CalArea();
	}

	// function
	void CalculateAngle();
	void CalArea();

	float CalculateAngle(const Node& center, const Node& n);
	float CalculateArcAngle(const float startAngle, const float endAngle);

	// data
	Node n1;
	Node n2;
	Node center;
	bool direction = true;
	float radius = 0;
	float startAngle = 0;
	float endAngle = 0;
	float angle = 0;
	float area = 0;
};
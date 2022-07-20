#pragma once

struct Node
{
	// constructor
	Node() {}
	Node(const float& x, const float& y)
		: x(x), y(y) {}

	// data
	float x = 0, y = 0;
};
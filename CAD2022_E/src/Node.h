#pragma once

struct Node
{
	// constructor
	Node() {}
	Node(const float& x, const float& y)
		: x(x), y(y) {}

	// operator
	bool operator == (const Node& node) const;

	// data
	float x = 0, y = 0;
};
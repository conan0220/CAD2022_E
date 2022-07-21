#pragma once

#include "Line.h"
#include "Arc.h"
#include "DataStructure/Vector.h"


class Base
{
public:
	// constructor
	Base() {}

	// function

	// operator
	void operator += (const Line& line);
	void operator += (const Arc& arc);

	// data
	Vector<Line> lines;
	Vector<Arc> arcs;

	static float assemblygap;
	static float coppergap;
	static float silkscreenlen;

private:

};
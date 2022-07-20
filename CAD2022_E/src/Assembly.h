#pragma once

#include "Base.h"
#include "DataStructure/Vector.h"
#include "Line.h"

class Assembly : protected Base
{
public:
	// constructor
	Assembly() {}

	// function
	const Vector<Line>& GetLines() { return lines; }
	
	// operator
	void operator += (const Line& line);

	// data
	Vector<Line> lines;
private:

};
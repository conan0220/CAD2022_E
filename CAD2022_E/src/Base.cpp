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

float Base::CalculateArea() const
{
	float total = 0;
	int lineIndex = 0;
	int arcIndex = 0;
	bool lastIsLine = isLineFirst;
	
	if (isLineFirst)
	{
		total += CalculateDeterminant(lines[lineIndex].n1, lines[lineIndex].n2);
		lineIndex += 1;
	}
	else if (!isLineFirst)
	{
		total += CalculateDeterminant(arcs[arcIndex].n1, arcs[arcIndex].center);
		total += CalculateDeterminant(arcs[arcIndex].center, arcs[arcIndex].n2);
		if (arcs[arcIndex].direction)
			total += arcs[arcIndex].area;
		else if (!arcs[arcIndex].direction)
			total -= arcs[arcIndex].area;
		arcIndex += 1;
	}

	for (int i = 1; i < lines.GetSize() + arcs.GetSize(); i++)
	{
		if (lastIsLine)
		{
			if (lines[lineIndex - 1].n2 == lines[lineIndex].n1)
			{
				total += CalculateDeterminant(lines[lineIndex].n1, lines[lineIndex].n2);
				lineIndex < lines.GetSize() - 1 ? lineIndex += 1 : NULL;
				lastIsLine = true;
			}
			else if (lines[lineIndex - 1].n2 == arcs[arcIndex].n1)
			{
				total += CalculateDeterminant(arcs[arcIndex].n1, arcs[arcIndex].center);
				total += CalculateDeterminant(arcs[arcIndex].center, arcs[arcIndex].n2);
				if (arcs[arcIndex].direction)
					total += arcs[arcIndex].area;
				else if (!arcs[arcIndex].direction)
					total -= arcs[arcIndex].area;
				arcIndex < arcs.GetSize() - 1 ? arcIndex += 1 : NULL;
				lastIsLine = false;
			}
		}
		else if (!lastIsLine)
		{
			if (arcs[arcIndex - 1].n2 == lines[lineIndex].n1)
			{
				total += CalculateDeterminant(lines[lineIndex].n1, lines[lineIndex].n2);
				lineIndex < lines.GetSize() - 1 ? lineIndex += 1 : NULL;
				lastIsLine = true;
			}
			else if (arcs[arcIndex - 1].n2 == arcs[arcIndex].n1)
			{
				total += CalculateDeterminant(arcs[arcIndex].n1, arcs[arcIndex].center);
				total += CalculateDeterminant(arcs[arcIndex].center, arcs[arcIndex].n2);
				if (arcs[arcIndex].direction)
					total += arcs[arcIndex].area;
				else if (!arcs[arcIndex].direction)
					total -= arcs[arcIndex].area;
				arcIndex < arcs.GetSize() - 1 ? arcIndex += 1 : NULL;
				lastIsLine = false;
			}
		}
	}
	return abs(math::Rounding(total / 2, 4));
}

float Base::CalculateDeterminant(const Node& n1, const Node& n2) const
{
	return n1.x * n2.y - n1.y * n2.x;
}






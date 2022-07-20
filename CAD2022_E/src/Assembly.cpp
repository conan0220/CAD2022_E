#include "Assembly.h"

void Assembly::operator+=(const Line& line)
{
	lines += line;
}
#include "Application.h"
#include "Base.h"
#include "Timer.h"
#include "Arc.h"

Application::Application()
{
	std::string filepath;
	std::cout << "input filepath: ";
	std::cin >> filepath;
	filepath.insert(0, "res/");
	input.ReadFile(filepath);

	ProcessInput();
}

void Application::ProcessInput()
{
	Timer timer;
	// 0 --> assembly | 1 --> copper
	int present = NULL;
	for (int i = 0; i < input.GetText().GetSize(); i++)
	{
		if (IsLine(i))
		{
			const Vector<float>& temp = input.GetFloatInLine(i);
			if (present == 1)
				coppers[coppers.GetSize() - 1] += Line(Node(temp[0], temp[1]), Node(temp[2], temp[3]));
			else if (present == 0)
				assembly += Line(Node(temp[0], temp[1]), Node(temp[2], temp[3]));
		}
		else if (IsArc(i))
		{
			const Vector<float>& temp = input.GetFloatInLine(i);
			if (present == 1)
				coppers[coppers.GetSize() - 1] += Arc(Node(temp[0], temp[1]), Node(temp[2], temp[3]), Node(temp[4], temp[5]), !IsCounterClockwise(i));
			else if (present == 0)
				assembly += Arc(Node(temp[0], temp[1]), Node(temp[2], temp[3]), Node(temp[4], temp[5]), !IsCounterClockwise(i));
		}
		else if (IsCoppergap(i))
		{
			Base::coppergap = input.GetFloatInLine(i)[0];
		}
		else if (IsCopper(i)) 
		{
			present = 1;
			coppers += Copper();
		}
		else if (IsAssemblygap(i))
		{
			Base::assemblygap = input.GetFloatInLine(i)[0];
		}
		else if (IsAssembly(i))
		{
			present = 0;
		}
		else if (IsSilkscreenlen(i))
		{
			Base::silkscreenlen = input.GetFloatInLine(i)[0];
		}
		
		
	}
}

inline bool Application::IsAssemblygap(const int& line) const
{
	return input.IsStringInLine("assemblygap", line);
}

inline bool Application::IsCoppergap(const int& line) const
{
	return input.IsStringInLine("coppergap", line);
}

inline  bool Application::IsSilkscreenlen(const int& line) const
{
	return input.IsStringInLine("silkscreenlen", line);
}

inline bool Application::IsAssembly(const int& line) const
{
	return input.IsStringInLine("assembly", line);
}

inline bool Application::IsCopper(const int& line) const
{
	return input.IsStringInLine("copper", line);
}

inline bool Application::IsLine(const int& line) const
{
	return input.IsStringInLine("line", line);
}

inline bool Application::IsArc(const int& line) const
{
	return input.IsStringInLine("arc", line);
}

inline bool Application::IsCounterClockwise(const int& line) const
{
	return input.IsStringInLine("CCW", line);
}

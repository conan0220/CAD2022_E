#include "Application.h"
#include "Base.h"

#include <iostream>

Application::Application()
{
	std::string filepath;
	std::cout << "input filepath: ";
	std::cin >> filepath;
	filepath.insert(0, "res/");
	input.ReadFile(filepath);

	ProcessInput();
	
	for (const auto& line : assembly.lines)
	{
		std::cout << "(x1:" << line.n1.x << ", y1:" << line.n1.y;
		std::cout << ", x2:" << line.n2.x << ", y2:" << line.n2.y << ")";
		std::cout << std::endl;
	}
}

void Application::ProcessInput()
{
	// 0 --> assembly | 1 --> copper
	int present = NULL;
	for (int i = 0; i < input.GetText().GetSize(); i++)
	{
		if (IsCoppergap(i))
		{
			Base::GetCoppergap() = input.GetFloatInLine(i)[0];
		}
		else if (IsCopper(i))
		{
			present = 1;
		}
		else if (IsLine(i))
		{
			const auto& temp = input.GetFloatInLine(i);
			if (present == 1)
				continue;
			else if (present == 0)
				assembly += Line(Node(temp[0], temp[1]), Node(temp[2], temp[3]));
			
		}
		else if (IsAssemblygap(i))
		{
			Base::GetAssemblygap() = input.GetFloatInLine(i)[0];
		}
		else if (IsAssembly(i))
		{
			present = 0;
		}
		else if (IsSilkscreenlen(i))
		{
			Base::GetSilkscreenlen() = input.GetFloatInLine(i)[0];
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

inline bool Application::IsLine(const int& line) const
{
	return input.IsStringInLine("line", line);
}

bool Application::IsCopper(const int& line) const
{
	return input.IsStringInLine("copper", line);
}

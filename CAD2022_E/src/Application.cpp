#include "Application.h"
#include "Base.h"
#include "Timer.h"
#include "Arc.h"
#include "Render.h"

#include <thread>
#include <conio.h>

static bool isRenderRunning = true;

Application::Application()
{
	std::string filepath;
	std::cout << "input filepath: ";
	std::cin >> filepath;
	filepath.insert(0, "res/");
	input.ReadFile(filepath);

	ProcessInput();
	std::thread ThreadRender(&Application::Render, this);
	ThreadRender.join();
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

void Application::Render() 
{
	GetScaling() = 0.1;
	std::thread ThreadGetKeyEvent(&Application::GetKeyEvent, this);
	ThreadGetKeyEvent.detach();

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
	{
		std::cerr << "[Error]: Failed to init";
		exit(EXIT_FAILURE);
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(720, 680, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cerr << "Error!" << std::endl;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window) && isRenderRunning)
	{

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		RenderAssembly();
		RenderCopper();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
}

void Application::RenderAssembly() const
{
	for (const Line& line : assembly.lines)
	{
		RenderLine(line.n1, line.n2);
	}
}

void Application::RenderCopper() const
{
	for (const auto& copper : coppers)
	{
		for (const Line& line : copper.lines)
		{
			RenderLine(line.n1, line.n2);
		}
	}
}

void Application::GetKeyEvent()
{
	int ch;
	while (true)
	{
		if (_kbhit())
		{
			ch = _getch();
			//std::cout << ch << std::endl;
			if (ch == 61)						// plus
				GetScaling() += 0.01;
			else if (ch == 45)					// minus
				GetScaling() -= 0.01;
			else if (ch == 72)					// up
				GetYDisplacement() -= 0.05;
			else if (ch == 80)					// down
				GetYDisplacement() += 0.05;
			else if (ch == 77)					// right
				GetXDisplacement() -= 0.05;
			else if (ch == 75)					// left
				GetXDisplacement() += 0.05;
			else if (ch == 27)					// ESC
				isRenderRunning = false;
		}
		if (!isRenderRunning)
			break;
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

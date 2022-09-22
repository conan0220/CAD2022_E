#include "Application.h"
#include "Base.h"
#include "Timer.h"
#include "Arc.h"
#include "Event.h"
#include "Control.h"
#include "Camera.h"

#include <thread>


Application::Application()
{
	Running::isRenderRunning = true;

	std::string filePath;
	std::cout << "input filepath: ";
	std::cin >> filePath;
	filePath.insert(0, "res/Input/");
	input.ReadFile(filePath);

	ProcessInput();
	std::cout << "Assembly area: " << assembly.CalculateArea() << std::endl;
	//ProcessOutput();
	//GenerateOutput();
	ReadExistOutputFile();
	std::thread ThreadRender(&Application::Render, this);
	ThreadRender.join();
}

void Application::ProcessInput()
{
	Timer timer;
	/* present:	0 --> assembly | 1 --> copper	*/
	int present = NULL;

	for (int i = 0; i < input.GetText().GetSize(); i++)
	{
		if (IsLine(i, input))
		{
			const Vector<float>& temp = input.GetFloatInLine(i);
			if (present == 1)
			{
				if (coppers[coppers.GetSize() - 1].lines.GetSize() == 0 && coppers[coppers.GetSize() - 1].arcs.GetSize() == 0)
					coppers[coppers.GetSize() - 1].isLineFirst = true;
				coppers[coppers.GetSize() - 1] += Line(Node(temp[0], temp[1]), Node(temp[2], temp[3]));
			}
			else if (present == 0)
			{
				if (assembly.lines.GetSize() == 0 && assembly.arcs.GetSize() == 0)
					assembly.isLineFirst = true;
				assembly += Line(Node(temp[0], temp[1]), Node(temp[2], temp[3]));
			}
				
		}
		else if (IsArc(i, input))
		{
			const Vector<float>& temp = input.GetFloatInLine(i);
			if (present == 1)
			{
				if (coppers[coppers.GetSize() - 1].lines.GetSize() == 0 && coppers[coppers.GetSize() - 1].arcs.GetSize() == 0)
					coppers[coppers.GetSize() - 1].isLineFirst = false;
				coppers[coppers.GetSize() - 1] += Arc(Node(temp[0], temp[1]), Node(temp[2], temp[3]), Node(temp[4], temp[5]), !IsCounterClockwise(i, input));
			}
			else if (present == 0)
			{
				if (assembly.lines.GetSize() == 0 && assembly.arcs.GetSize() == 0)
					assembly.isLineFirst = false;
				assembly += Arc(Node(temp[0], temp[1]), Node(temp[2], temp[3]), Node(temp[4], temp[5]), !IsCounterClockwise(i, input));
			}
				
		}
		else if (IsCoppergap(i, input))
		{
			Base::coppergap = input.GetFloatInLine(i)[0];
		}
		else if (IsCopper(i, input))
		{
			present = 1;
			coppers += Copper();
		}
		else if (IsAssemblygap(i, input))
		{
			Base::assemblygap = input.GetFloatInLine(i)[0];
		}
		else if (IsAssembly(i, input))
		{
			present = 0;
		}
		else if (IsSilkscreenlen(i, input))
		{
			Base::silkscreenlen = input.GetFloatInLine(i)[0];
		}
		
	}
}

void Application::ProcessOutput()
{
	
}

void Application::GenerateOutput()
{
	std::string filePath = "res/Output/Result.txt";
	std::ofstream ofs;
	ofs.open(filePath);
	if (ofs.is_open())
	{
		for (const Silkscreen& silkscreen : silkscreens)
		{
			ofs << "silkscreen" << std::endl;
			
			// 按照連續線段的順序寫入Result.txt
		}
		ofs.close();
	}
	else
	{
		std::cerr << "Failed to open file.\n";
		exit(EXIT_FAILURE);
	}
	
}

void Application::GenerateScore()
{
}

void Application::ReadExistOutputFile()
{
	silkscreens.RemoveAll();
	std::string filePath = "res/Output/Result.txt";
	output.ReadFile(filePath);

	for (int i = 0; i < output.GetText().GetSize(); i++)
	{
		if (IsLine(i, output))
		{
			const Vector<float>& temp = output.GetFloatInLine(i);
			silkscreens[silkscreens.GetSize() - 1] += Line(Node(temp[0], temp[1]), Node(temp[2], temp[3]));
		}
		else if (IsArc(i, output))
		{
			const Vector<float>& temp = output.GetFloatInLine(i);
			silkscreens[silkscreens.GetSize() - 1] += Arc(Node(temp[0], temp[1]), Node(temp[2], temp[3]), Node(temp[4], temp[5]), !IsCounterClockwise(i, output));
		}
		else if (IsSilkscreen(i, output))
		{
			silkscreens += Silkscreen();
		}
	}
}

void Application::Render() 
{
	GLFWwindow* window;

	Camera::scaling = 0.1;

	/* Initialize the library */
	if (!glfwInit()) 
	{
		std::cerr << "[Error]: Failed to init";
		exit(EXIT_FAILURE);
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(windowWidth, windowHeight, "Canvas", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	KeyEvent(window);
	MouseButtonEvent(window);
	CursorPositionEvent(window);

	std::thread ThreadCommandEvent(CommandEvent);
	ThreadCommandEvent.detach();

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cerr << "Error!" << std::endl;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window) && Running::isRenderRunning)
	{

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		RenderAssembly(Display::assembly);
		RenderCopper(Display::copper);
		RenderSilkscreen(Display::silkscreen);
		Camera::Render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
}

void Application::RenderAssembly(bool display) const
{
	if (display)
	{
		glColor3f(0.0f, 0.0f, 1.0f);
		for (const Line& line : assembly.lines)
		{
			RenderLine(line.n1, line.n2);
		}
		for (const Arc& arc : assembly.arcs)
		{
			RenderArc(arc, 1000);
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
}

void Application::RenderCopper(bool display) const
{
	if (display)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		for (const Copper& copper : coppers)
		{
			for (const Line& line : copper.lines)
			{
				RenderLine(line.n1, line.n2);
			}
			for (const Arc& arc : copper.arcs)
			{
				RenderArc(arc, 1000);
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
}

void Application::RenderSilkscreen(bool display) const
{
	if (display)
	{
		glColor3f(1.0f, 1.0f, 0.0f);
		for (const Silkscreen& silkscreen : silkscreens)
		{
			for (const Line& line : silkscreen.lines)
			{
				RenderLine(line.n1, line.n2);
			}
			for (const Arc& arc : silkscreen.arcs)
			{
				RenderArc(arc, 1000);
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
}


inline bool Application::IsAssemblygap(const int& line, const Text& text) const
{
	return text.IsStringInLine("assemblygap", line);
}

inline bool Application::IsCoppergap(const int& line, const Text& text) const
{
	return text.IsStringInLine("coppergap", line);
}

inline  bool Application::IsSilkscreenlen(const int& line, const Text& text) const
{
	return text.IsStringInLine("silkscreenlen", line);
}

inline bool Application::IsAssembly(const int& line, const Text& text) const
{
	return text.IsStringInLine("assembly", line);
}

inline bool Application::IsCopper(const int& line, const Text& text) const
{
	return text.IsStringInLine("copper", line);
}

inline bool Application::IsLine(const int& line, const Text& text) const
{
	return text.IsStringInLine("line", line);
}

inline bool Application::IsArc(const int& line, const Text& text) const
{
	return text.IsStringInLine("arc", line);
}

inline bool Application::IsCounterClockwise(const int& line, const Text& text) const
{
	return text.IsStringInLine("CCW", line);
}

inline bool Application::IsSilkscreen(const int& line, const Text& text) const
{
	return text.IsStringInLine("silkscreen", line);
}

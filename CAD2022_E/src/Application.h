#pragma once

#include "Text.h"
#include "Assembly.h"

class Application
{
public:
	// constuctor
	Application();
	~Application() {};

private:
	// function
	void ProcessInput();

	bool IsAssemblygap(const int& line) const;
	bool IsCoppergap(const int& line) const;
	bool IsSilkscreenlen(const int& line) const;
	bool IsAssembly(const int& line) const;
	bool IsLine(const int& line) const;
	bool IsCopper(const int& line) const;

	Text input;
	Assembly assembly;
};
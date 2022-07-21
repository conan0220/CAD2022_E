#pragma once

#include "Text.h"
#include "Assembly.h"
#include "Copper.h"

class Application
{
public:
	// constuctor
	Application();
	~Application() {};

private:
	// function
	void ProcessInput();

	inline bool IsAssemblygap(const int& line) const;
	inline bool IsCoppergap(const int& line) const;
	inline bool IsSilkscreenlen(const int& line) const;
	inline bool IsAssembly(const int& line) const;
	inline bool IsCopper(const int& line) const;
	inline bool IsLine(const int& line) const;
	inline bool IsArc(const int& line) const;
	inline bool IsCounterClockwise(const int& line) const;
	
	// data
	Text input;
	Assembly assembly;
	Vector<Copper> coppers;
};
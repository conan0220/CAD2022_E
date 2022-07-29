#pragma once

#include "Text.h"
#include "Assembly.h"
#include "Copper.h"
#include "Silkscreen.h"
#include "Render.h"



class Application
{
public:
	// constuctor
	Application();
	~Application() {};

private:
	// function
	void ProcessInput();
	void ProcessOutput();
	void GenerateOutput();
	void GenerateScore();
	void ReadExistOutputFile();
	void Render();

	void RenderAssembly(bool display) const;
	void RenderCopper(bool display) const;
	void RenderSilkscreen(bool display) const;

	void KeyEvent(GLFWwindow* window);
	void CommandEvent();

	static void KeyCallBack(GLFWwindow* window, int key, int scanCode, int action, int mods);

	inline bool IsAssemblygap(const int& line, const Text& text) const;
	inline bool IsCoppergap(const int& line, const Text& text) const;
	inline bool IsSilkscreenlen(const int& line, const Text& text) const;
	inline bool IsAssembly(const int& line, const Text& text) const;
	inline bool IsCopper(const int& line, const Text& text) const;
	inline bool IsLine(const int& line, const Text& text) const;
	inline bool IsArc(const int& line, const Text& text) const;
	inline bool IsCounterClockwise(const int& line, const Text& text) const;
	inline bool IsSilkscreen(const int& line, const Text& text) const;
	
	// data
	Text input;
	Text output;
	Assembly assembly;
	Vector<Copper> coppers;
	Vector<Silkscreen> silkscreens;
};
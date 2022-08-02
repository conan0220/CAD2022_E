#pragma once

#include "Render.h"

static float cursorX = 0;
static float cursorY = 0;

void KeyEvent(GLFWwindow* window);

void MouseButtonEvent(GLFWwindow* window);

void CursorPositionEvent(GLFWwindow* window);

void CommandEvent();

static void KeyCallBack(GLFWwindow* window, int key, int scanCode, int action, int mods);

static void MouseButtonCallBack(GLFWwindow* window, int button, int action, int mods);

static void CursorPositionCallBack(GLFWwindow* window, double xpos, double ypos);
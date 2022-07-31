#pragma once
#include "Node.h"

#include <iostream>

#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

void RenderPoint(const Node& n);

void RenderLine(const Node& n1, const Node& n2);

void RenderArc(const Node& center, float r, float startAngle, float endAngle, bool direction, int numSegments);

void RenderText(const std::string text, const float x, const float y);

float CalculateAngle(const Node& center, const Node& n);

float CalculateArcAngle(const float startAngle, const float endAngle);
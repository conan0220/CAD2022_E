#pragma once
#include "Node.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static float scaling = 1.0f;
static float xDisplacement = 0.0f;
static float yDisplacement = 0.0f;

float& GetScaling();
float& GetXDisplacement();
float& GetYDisplacement();

void RenderLine(const Node& n1, const Node& n2);

void RenderArc(const Node& center, float r, float startAngle, float endAngle, bool direction, int numSegments);

float CalculateAngle(const Node& center, const Node& n);

float CalArcAngle(const float startAngle, const float endAngle);
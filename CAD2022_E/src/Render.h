#pragma once
#include "Node.h"
#include "Arc.h"

#include <iostream>

#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

static int windowWidth = 720;
static int windowHeight = 720;

void RenderPoint(const Node& n);

void RenderLine(const Node& n1, const Node& n2);

void RenderArc(const Arc& arc, int numSegments);

void RenderText(const std::string text, const float x, const float y);


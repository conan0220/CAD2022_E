#include "Event.h"
#include "Control.h"
#include "Camera.h"

#include <iostream>

/*	drop displacement velocity by scaling elevate	*/
void KeyEvent(GLFWwindow* window)
{
	glfwSetKeyCallback(window, KeyCallBack);
}

 /*	it would be best to use thread	*/
void CommandEvent()
{
	std::string command = "";
	while (true)
	{
		std::cout << "[cmd]: ";
		std::cin >> command;
		if (command == "assembly.off")
			Display::assembly = false;
		else if (command == "assembly.on")
			Display::assembly = true;
		else if (command == "copper.off")
			Display::copper = false;
		else if (command == "copper.on")
			Display::copper = true;
		else if (command == "silkscreen.off")
			Display::silkscreen = false;
		else if (command == "silkscreen.on")
			Display::silkscreen = true;
		else if (command == "camera.off")
			Display::aim = false;
		else if (command == "camera.on")
			Display::aim = true;
		else if (command == "get.camera.scaling")
			std::cout << "camera.scaling: " << Camera::scaling << std::endl;
		else if (command == "get.camera.x")
			std::cout << "camera.x: " << Camera::x << std::endl;
		else if (command == "get.camera.y")
			std::cout << "camera.y: " << Camera::y << std::endl;
		else if (command == "get.camera.velocity")
			std::cout << "camera.velocity: " << Camera::velocity << std::endl;
		else if (command == "modify.camera.scaling")
		{
			std::cout << "camera.scaling --> ";
			std::cin >> Camera::scaling;
		}
		else if (command == "modify.camera.x")
		{
			std::cout << "camera.x --> ";
			std::cin >> Camera::x;
		}
		else if (command == "modify.camera.y")
		{
			std::cout << "camera.y --> ";
			std::cin >> Camera::y;
		}
		else if (command == "modify.camera.velocity")
		{
			std::cout << "camera.velocity --> ";
			std::cin >> Camera::velocity;
		}
		else if (command == "init.camera")
		{
			Camera::scaling = 1.0f;
			Camera::x = 0.0f;
			Camera::y = 0.0f;
		}
		else if (command == "close")
		{
			Running::isRenderRunning = false;
			break;
		}
		else if (command == "?")
		{
			std::cout << "Legal command -->" << std::endl << std::endl;
			std::cout << "1. assembly.off | assembly.on | copper.off | copper.on | silkscreen.off | silkscreen.on | camera.off | camera.on" << std::endl << std::endl;
			std::cout << "2. get.camera.scaling | get.camera.x | get.camera.y | get.camera.velocity" << std::endl << std::endl;
			std::cout << "3. modify.camera.scaling | modify.camera.x | modify.camera.y | modify.camera.velocity" << std::endl << std::endl;
			std::cout << "4. init.camera" << std::endl << std::endl;
			std::cout << "5. close" << std::endl;
		}
		else
		{
			std::cout << "[Error]: illegal command" << std::endl;
		}
		std::cout << std::endl;
	}
}

void KeyCallBack(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	//std::cout << key << std::endl;
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		if (key == GLFW_KEY_MINUS)
			Camera::scaling *= 0.9f;
		else if (key == GLFW_KEY_EQUAL)
			Camera::scaling *= 1.1f;
		else if (key == GLFW_KEY_UP)
			Camera::y += Camera::velocity / Camera::scaling;
		else if (key == GLFW_KEY_DOWN)
			Camera::y -= Camera::velocity / Camera::scaling;
		else if (key == GLFW_KEY_LEFT)
			Camera::x -= Camera::velocity / Camera::scaling;
		else if (key == GLFW_KEY_RIGHT)
			Camera::x += Camera::velocity / Camera::scaling;
		else if (key == GLFW_KEY_ESCAPE)
			Running::isRenderRunning = false;
	}

}
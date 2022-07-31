#include "Camera.h"
#include "Render.h"
#include "Control.h"

float Camera::scaling = 1.0f;
float Camera::x = 0.0f;
float Camera::y = 0.0f;
float Camera::velocity = .1f;

void Camera::Render()
{
	RenderAim(Display::aim);
}

void Camera::RenderAim(bool display)
{
	if (display)
	{
		glColor3f(1.0f, 0.0f, 0.0f);

		glBegin(GL_LINES);
		glVertex2f(-.05f, 0.0f);
		glVertex2f(.05f, 0.0f);
		//glEnd();

		//glBegin(GL_LINES);
		glVertex2f(0.0f, -.05f);
		glVertex2f(0.0f, .05f);
		glEnd();

		glColor3f(1.0f, 1.0f, 1.0f);
	}
}



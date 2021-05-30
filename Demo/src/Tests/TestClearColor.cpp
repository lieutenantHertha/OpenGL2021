#include "TestClearColor.h"

TestClearColor::TestClearColor()
	:m_clearColor{0.2f, 0.3f, 0.8f, 1.0f}
{
}

TestClearColor::~TestClearColor()
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void TestClearColor::OnRender()
{
	GLCall(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void TestClearColor::OnImguiRender()
{
	// Configuration of current test
	ImGui::ColorEdit4("Color", m_clearColor);
}

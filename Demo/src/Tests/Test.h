#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include <GL/glew.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Renderer.h"


class Test {
public:
	Test() = default;
	virtual ~Test() {};
	virtual void OnUpdate(float deltaTime) {};
	virtual void OnRender() {};
	virtual void OnImguiRender() {};

public:
	static void ImGuiBegin(const char* labelName);
	static void ImGuiEnd();
};

class TestMenu : public Test {
private:
	Test*& m_Current;
	std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;

public:
	TestMenu(Test*& current);
	~TestMenu();
	void OnImguiRender() override;
	template<typename TestType>
	void LoadTest(const std::string& name);
};

template<typename TestType>
void TestMenu::LoadTest(const std::string& name)
{
	m_Tests.push_back({ name, []() {return new TestType(); } });
}
